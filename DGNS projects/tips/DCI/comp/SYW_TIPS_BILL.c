/*******************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V3.0.00
操作系统:AIX5.3
文件名称:SYW_TIPS_BILL.ec
文件描述:TIPS凭单组件集
项 目 组:TIPS专用前置产品组
程 序 员:Tuql
发布日期:
修    订:
修改日期:  
*********************************************************************/
/*
总体说明:

函数说明
组件函数名称                 组件名称                      发布日期  程序员 修改日期 修改人

*/

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include "gaps_head.h"
/* mod dci 20141103
EXEC SQL INCLUDE  "gaps_head.eh";
EXEC SQL INCLUDE  "../eh/tips_pzsj.eh"; 凭证数据 */

#include  "../eh/tips_pzsj.h"  

/*#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )*/

/* 获得凭证序号 */
int prv_tips_genpzxh(HXMLTREE lXmlhandle, char *sDqdh,char *sZwrq,char *sMsgno, char *sPzxh)
{
    int iRet=0;
    char sYwlx[10];
    char sTmp[30];
    char sLx[2];
    
    memset(sYwlx,0,sizeof(sYwlx));
    memset(sTmp,0,sizeof(sTmp));
    memset(sPzxh,0,sizeof(sPzxh));
    memset(sLx,0,sizeof(sLx));
    
    if (strncmp(sMsgno,"3001",4)==0)
    {
    	sprintf(sLx,"%s","1");
    }
    else if (strncmp(sMsgno,"1008",4)==0)
    {
    	sprintf(sLx,"%s","2");
    }
    else
    {
    	sprintf(sLx,"%s","3");
    }	
    
    sprintf(sYwlx,"%s","29");
    iRet = prv_GenSerino(lXmlhandle,sTmp, sizeof(sTmp));
    if (iRet < 0)
    {
    	LOG(LM_STD,Fmtmsg("中间业务平台系统故障,fpub_GenSSERIAL_byZwrq失败 [%d]", iRet),"ERROR");
    	return -1;
    }
  
    memcpy(sPzxh,sDqdh,2);
    memcpy(sPzxh+2,sZwrq,8);
    memcpy(sPzxh+10,sLx,1);
    memcpy(sPzxh+11,sTmp,8);  
    
    return 0;    	
}


/* 取征收机关名称 */
int getTaxOrgName(char *code, char *name)
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char orgcode[12+1];
         char orgname[60+1];
    /*EXEC SQL END DECLARE SECTION; */
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;

    memset(orgcode,0x00,sizeof(orgcode));
    memset(orgname,0x00,sizeof(orgname));
    
    pstrcopy(orgcode,code, sizeof(orgcode));

		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select taxorgname from tips_taxcodeinfo \
    	where taxorgcode=%s",orgcode);     	
    iRet = DBSelectToVar(sErrmsg, &orgname, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        return -1;   
    }

		/* end add dci 20141103 */
		
		/* mod dci 20141103
    EXEC SQL SELECT taxorgname into :orgname
      FROM tips_taxcodeinfo 
      WHERE taxorgcode=:orgcode;
    SQLERRLOG(LM_STD,Fmtmsg("取征收机关名称出错sqlcode=[%d]",sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
      return -1;
    }
    */
    			            	    	
    trim(orgname);
    strcpy(name,orgname); 
    return 0;
}

/* 取付款开户行名称 */
int getOpBankName(char *code, char *name)
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char orgcode[12+1];
         char orgname[60+1];
    /*EXEC SQL END DECLARE SECTION;*/
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
    
    memset(orgcode,0x00,sizeof(orgcode));
    memset(orgname,0x00,sizeof(orgname));
    
    pstrcopy(orgcode, code, sizeof(orgcode));
    
    /* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select jgmc from tips_jgdhdj \
    	where khqshh=%s",orgcode);     	
    iRet = DBSelectToVar(sErrmsg, &orgname, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        return -1;   
    }

		/* end add dci 20141103 */
		
		/* mod dci 20141103
    EXEC SQL SELECT jgmc INTO :orgname
         FROM tips_jgdhdj 
         WHERE khqshh=:orgcode;    
    SQLERRLOG(LM_STD,Fmtmsg("取支付行名称出错sqlcode=[%d]",sqlca.sqlcode), "ERROR")
    if ( SQLERR )
    {
      return -1;
    }			            
    */
        	
    trim(orgname);
    strcpy(name,orgname); 
    return 0;
}

/* 税务凭证 */
int prv_tips_swpz(HXMLTREE lXmlhandle,FILE *fp,char *sZwrq,char *stmproot,SDB_TIPS_PZSJ *stPzsj,int iNum)
{
    char sSpFile[256];/* 税票文件 */
    char sBuf[256];
    char stmpnode[256];
    char *sbufsp;/* 动态分配内存 */
    char sPzxh[30];/* 保存凭证序号 */
    char sSysDate[8+1];
    char sSysTime[6+1];
    double dTmpAmt=0.00;
    int i;
    int k;
    int iRet = 0;
    int iFlag=0;
    int iProjectNum=0;
    int ilen=0, ilen2=0;
    struct stat struStat;
    FILE *fp2;
	    
	/*获得系统日期和时间*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSysDate, 0x00, sizeof(sSysDate)); 
    COMP_SOFTGETXML("/sys/sysdate",sBuf);
    pstrcopy(sSysDate, sBuf, sizeof(sSysDate));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML("/sys/systime",sBuf);
    pstrcopy(sSysTime, sBuf, sizeof(sSysTime));

    xml_DelElement( lXmlhandle,stmproot); /*删除不成功不影响结果*/
    COMP_SOFTSETXML(stmproot,"");
    
    /* 拼接税票文件全路径 */
    trim(stPzsj->pzsjwjm);
    memset(sSpFile, 0x00, sizeof(sSpFile));
    snprintf(sSpFile, sizeof(sSpFile), "%s/file/tips/spxx/%s", getenv("HOME"), stPzsj->pzsjwjm);
    trim(sSpFile);
    LOG(LM_DEBUG,Fmtmsg("税票全路径[%s]", sSpFile),fpub_GetCompname(lXmlhandle))
    /* 打开税票文件 */
    if((fp2=fopen(sSpFile,"r"))==NULL)
    {        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开税票信息文件失败[%s]", strerror(errno)),
            fpub_GetCompname(lXmlhandle))	  	
    }
    /* 按税票信息文件的1.5倍申请内存 */ 
    fstat(fileno(fp2), &struStat);
    ilen = struStat.st_size;
    ilen2 = ilen * 1.5;
    if((sbufsp=malloc(ilen2))==NULL)
    {
        fclose(fp2);        
        LOGRET(-2,LM_STD,Fmtmsg("申请动态内存失败"),fpub_GetCompname(lXmlhandle))	 	  	
    }
    memset(sbufsp, 0x00, sizeof(sbufsp));
    /* 读取税票信息文件内容 */
    fread(sbufsp,ilen,1,fp2);
    fclose(fp2);
    sbufsp[ilen]=0x00;    
    /*将税票信息导入节点*/
    if(strlen(stmproot)==0)
    	strcmp(stmproot,"/tmpnode");
    if (xml_ImportXMLString(lXmlhandle, sbufsp, stmproot, 0 )==-1)
    {
        xml_DelElement(lXmlhandle,stmproot); /*删除不成功不影响结果*/
        free(sbufsp);
        LOGRET(-3,LM_STD,Fmtmsg("取原交易数据包失败,写入XML失败,msg[%s]",
            GETXMLERR),fpub_GetCompname(lXmlhandle))
    }
    free(sbufsp);		 
    /*获得明细节点个数*/
    iProjectNum=0;
    memset(stmpnode,0x00,sizeof(stmpnode));
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(stmpnode,sizeof(stmpnode),"%s/Payment%s/TaxTypeNum",stmproot,trim(stPzsj->msgno));
    COMP_SOFTGETXML(stmpnode,sBuf);
    iProjectNum = atoi(sBuf);
    /*14条明细为一个凭单，如果超过14条，则分单打印*/

    for(i=0;;i++)
    {
LOG(LM_DEBUG,Fmtmsg("---------iProjectNum[%d]-------------",iProjectNum),fpub_GetCompname(lXmlhandle))
        if (iProjectNum <= 0) 
   	    {
   	        break;
   	    }
        fprintf(fp,"\n\n\n");

        /* 获取凭证序号 */
        memset(sPzxh,0,sizeof(sPzxh));
/*        iRet = prv_tips_genpzxh(lXmlhandle,stPzsj->dqdh,sZwrq,stPzsj->msgno,sPzxh);*/
        sprintf(sPzxh,"%ld",stPzsj->zhqzlsh);

        trim(sPzxh);
        fprintf(fp,"                                       电子缴税付款凭证 \n\n");
        fprintf(fp,"      转账日期：%4.4s年%2.2s月%2.2s日                                                 凭证字号： %s         \n",
            stPzsj->zwrq,stPzsj->zwrq+4,stPzsj->zwrq+6,sPzxh); 
        /*纳税人全称及标示*/
        memset(stmpnode,0x00,sizeof(stmpnode));
        memset(sBuf,0x00,sizeof(sBuf));
        snprintf(stmpnode,sizeof(stmpnode),"%s/Payment%s/TaxPayName",stmproot,trim(stPzsj->msgno));
        COMP_SOFTGETXML(stmpnode,sBuf);
        fprintf(fp,"      纳税人全称及纳税人识别号： %s",sBuf);
        memset(stmpnode,0x00,sizeof(stmpnode));
        memset(sBuf,0x00,sizeof(sBuf));
        snprintf(stmpnode,sizeof(stmpnode),"%s/Payment%s/TaxPayCode",stmproot,trim(stPzsj->msgno));
        COMP_SOFTGETXML(stmpnode,sBuf);
        fprintf(fp,"%s\n" ,sBuf);
        /*付款人全称*/
        fprintf(fp,"      付款人全称：%s\n",trim(stPzsj->handorgname));
        /*付款人账号,征收机关名称*/
        memset(sBuf, 0x00, sizeof(sBuf));
        getTaxOrgName(stPzsj->taxorgcode,sBuf);
        if (strlen(stPzsj->payacct) == 0 )
        {
          fprintf(fp,"      付款人账号：%-44.44s        征收机关名称：%s\n","现金",sBuf);
        }
        else
        {
        	fprintf(fp,"      付款人账号：%-44.44s        征收机关名称：%s\n",trim(stPzsj->payacct),sBuf);
        }
        /*付款人开户银行,收款国库(银行)名称*/
        memset(sBuf,0x00,sizeof(sBuf));
        getOpBankName(stPzsj->payopbkcode,sBuf);
        fprintf(fp,"      付款人开户银行：%-44.44s    收款国库名称：%-40.40s\n",sBuf,trim(stPzsj->payeename));
        /*金额小写，缴款书交易流水号*/
        fprintf(fp,"      金额小写：￥%-44.2f        缴款书交易流水号： %s\n",stPzsj->jyje,trim(stPzsj->trano));
        /*大写、税票号码*/
        memset(sBuf,0x00,sizeof(sBuf));
LOG(LM_DEBUG,Fmtmsg("---------[%.2lf]-------------",stPzsj->jyje),fpub_GetCompname(lXmlhandle))
        prv_get_dxje(stPzsj->jyje,sBuf);
LOG(LM_DEBUG,Fmtmsg("---------[%s]-------------",sBuf),fpub_GetCompname(lXmlhandle))
        fprintf(fp,"      金额大写：%-50.50s              税票号码：  %s\n",sBuf,trim(stPzsj->taxvouno));
        fprintf(fp,"\n");
        fprintf(fp,"      税费种名称                        所属日期                                 实缴金额\n");
  	  
        for(k=1;k<=14;k++)
        {
            if (k<=iProjectNum)
            {
                /*设置TaxTypeName 税种名称*/
                memset(stmpnode,0x00,sizeof(stmpnode));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(stmpnode,sizeof(stmpnode),"%s/Payment%s/TaxTypeList%s|%d/TaxTypeName",
                    stmproot,trim(stPzsj->msgno),trim(stPzsj->msgno),i*14+k);
                COMP_SOFTGETXML(stmpnode,sBuf);
                fprintf(fp,"      %-30.30s",sBuf);
                /*设置TaxStartDate 税款所属日期起*/
                memset(stmpnode,0x00,sizeof(stmpnode));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(stmpnode,sizeof(stmpnode),"%s/Payment%s/TaxTypeList%s|%d/TaxStartDate",
                    stmproot,trim(stPzsj->msgno),trim(stPzsj->msgno),i*14+k);
                COMP_SOFTGETXML(stmpnode,sBuf);
                fprintf(fp,"      %-8.8s",sBuf);
                /*设置TaxEndDate 税款所属日期止*/
                memset(stmpnode,0x00,sizeof(stmpnode));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(stmpnode,sizeof(stmpnode),"%s/Payment%s/TaxTypeList%s|%d/TaxEndDate",
                    stmproot,trim(stPzsj->msgno),trim(stPzsj->msgno),i*14+k);
                COMP_SOFTGETXML(stmpnode,sBuf);
                fprintf(fp,"-%-8.8s  ",sBuf);
                /*设置TaxTypeAmt 税种金额*/
                dTmpAmt = 0.00;
                memset(stmpnode,0x00,sizeof(stmpnode));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(stmpnode,sizeof(stmpnode),"%s/Payment%s/TaxTypeList%s|%d/TaxTypeAmt",
                    stmproot,trim(stPzsj->msgno),trim(stPzsj->msgno),i*14+k);
                COMP_SOFTGETXML(stmpnode,sBuf);
                dTmpAmt = atof(sBuf);
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sBuf, sizeof(sBuf), "￥%.2f",dTmpAmt);
                fprintf(fp,"    %30.30s          \n",sBuf);
            }
            else
            {
                fprintf(fp,"\n");
            }
        }
        if ( iNum == 1 )
        		fprintf(fp,"       第 %3d 次打印   打印时间： %-4.4s年%-2.2s月%-2.2s日    第一联 作付款行记账凭证     记账：     复核： \n\n",
            	stPzsj->dycs+1,sSysDate,sSysDate+4,sSysDate+6);
        else
        {
        		fprintf(fp,"       第 %3d 次打印   打印时间： %-4.4s年%-2.2s月%-2.2s日    第二联 作纳税人缴税回单     记账：     复核： \n",
            	stPzsj->dycs+1,sSysDate,sSysDate+4,sSysDate+6);
            fprintf(fp,"\f");
        }
/*        fprintf(fp,"\n"); */
        iProjectNum = iProjectNum - 14;
    }      	    

    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_GenBILL
组件名称: 生成税费凭单
组件功能: 
  生成税费凭单
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年03月5日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_GenBILL(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sPayAcct[32];/* 付款账号 */
         char sQsrq[8+1];/* 起始日期 */
         char sZzrq[8+1];/* 终止日期 */
         char sDqdh[10+1];/* 地区代号 */
         char sJgdh[10+1];/* 机构代号 */
         char sSql[512];
         SDB_TIPS_PZSJ stPzsj;
    /*EXEC SQL END   DECLARE SECTION;*/

    char sBuf[256];
    char sTmpBuf[256];
    char sFile[256];/*扣税文件名*/
    char stmproot[256];
    char stmpnode[256];
    char sGenPdfs[1+1];
    char sEntrustDate[8+1];/* 委托日期 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sTraNo[8+1];
    int  i;
    int  k;
    FILE *fp;
    char sJygy[16+1];/* 交易柜员 */
    char sZwrq[30];/*账务日期*/
    double dTmpAmt=0.00;
    int  iFlag=0;
    int  iSumCount=0;
    int  iProjectNum=0;
	int iret = 0;
	int iflag = 1;
	
		/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
	            
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("生成凭单开始处理... "), fpub_GetCompname(lXmlhandle))

    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(5)
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1,sBuf,"账务日期");
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJygy, 0x00, sizeof(sJygy));
    COMP_GETPARSEPARAS(2,sBuf,"交易柜员");
    pstrcopy(sJygy, sBuf, sizeof(sJygy));
    trim(sJygy);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile, 0x00, sizeof(sFile));
    COMP_GETPARSEPARAS(3,sBuf,"凭单文件名");
    pstrcopy(sFile, sBuf, sizeof(sFile));
    trim(sFile);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(stmproot, 0x00, sizeof(stmproot));
    COMP_GETPARSEPARAS(4,sBuf,"明细临时根节点");
    pstrcopy(stmproot, sBuf, sizeof(stmproot));
    trim(stmproot);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sGenPdfs, 0x00, sizeof(sGenPdfs));
    COMP_GETPARSEPARAS(5,sBuf,"生成凭单方式");
    pstrcopy(sGenPdfs, sBuf, sizeof(sGenPdfs));
    trim(sGenPdfs);        

    LOG(LM_STD,Fmtmsg("交易柜员[%s],账务日期[%s],生成凭单方式[%s],凭单文件名[%s]",
        sJygy, sZwrq, sGenPdfs, sFile), fpub_GetCompname(lXmlhandle))
    
    memset(sSql, 0x00, sizeof(sSql));
    if ( sGenPdfs[0]=='1')/* 凭付款账号 */
    {
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sPayAcct, 0x00, sizeof(sPayAcct));	
        COMP_SOFTGETXML("/tips/PayAcct", sBuf)
        pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
        trim(sPayAcct);
        
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sQsrq, 0x00, sizeof(sQsrq));
        COMP_SOFTGETXML("/tips/qsrq", sBuf)
        pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
        
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sZzrq, 0x00, sizeof(sZzrq));
        COMP_SOFTGETXML("/tips/zzrq", sBuf)
        pstrcopy(sZzrq, sBuf, sizeof(sZzrq)); 
               
        snprintf(sSql, sizeof(sSql), "select * from tips_pzsj where zwrq>='%s' and zwrq<='%s' and payacct='%s' and dzbz='1'", 
            sQsrq, sZzrq, sPayAcct);
    }else if ( sGenPdfs[0]=='0')/* 机构, 批量凭单 */
    {
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sQsrq, 0x00, sizeof(sQsrq));
        COMP_SOFTGETXML("/tips/qsrq", sBuf)
        pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
        
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sZzrq, 0x00, sizeof(sZzrq));
        COMP_SOFTGETXML("/tips/zzrq", sBuf)
        pstrcopy(sZzrq, sBuf, sizeof(sZzrq)); 
        
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sDqdh, 0x00, sizeof(sDqdh));
        COMP_SOFTGETXML("/pub/dqdh", sBuf)
        pstrcopy(sDqdh, sBuf, sizeof(sDqdh));
        
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sJgdh, 0x00, sizeof(sJgdh));
        COMP_SOFTGETXML("/pub/jgdh", sBuf)
        pstrcopy(sJgdh, sBuf, sizeof(sJgdh)); 
        
        snprintf(sSql, sizeof(sSql), "select * from tips_pzsj where zwrq>='%s' and zwrq<='%s' and dqdh='%s' and jgdh='%s' and dycs<5 and dzbz='1' ", 
            sQsrq, sZzrq, sDqdh, sJgdh);              
    }else if ( sGenPdfs[0]=='2')/* 实时，银行端缴款 */
    {
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sEntrustDate, 0x00, sizeof(sEntrustDate));
        COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
        pstrcopy(sEntrustDate, sBuf, sizeof(sEntrustDate));
        
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
        COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
        pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode)); 
        
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sTraNo, 0x00, sizeof(sTraNo));
        COMP_SOFTGETXML("/tips/TraNo", sBuf)
        pstrcopy(sTraNo, sBuf, sizeof(sTraNo));
        
        snprintf(sSql, sizeof(sSql), "select * from tips_pzsj where entrustdate='%s' and taxorgcode='%s' and trano='%s' ", 
            sEntrustDate, sTaxOrgCode, sTraNo);        
    }else
    {
        fpub_SetMsg(lXmlhandle,24411, "生成凭单方式不符");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("生成凭单方式不符"),
            fpub_GetCompname(lXmlhandle))        
    }                
 	trim(sSql);
 	LOG(LM_STD,Fmtmsg("sSql[%s]",sSql),fpub_GetCompname(lXmlhandle));

	/* add dci 20141103 */
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  }
  if (DCIExecute(cur) == -1)
  {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  }
	/* end add dci 20141103 */
	
	/* mod dci 20141103
 	/*prepare
    EXEC SQL PREPARE sql_qrypdsj FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrypdsj",sqlca.sqlcode),"ERROR");    
    /*declare
    EXEC SQL DECLARE cur_pzsj_zh CURSOR for sql_qrypdsj;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_pzsj_zh",sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_pzsj_zh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_pzsj_zh", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24409, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH打开cur_pzsj_zh游标失败"),
            fpub_GetCompname(lXmlhandle))
    } 
    */

    fp=fopen(sFile,"w");
    if ( fp == NULL )
    {
        /* add dci 20141103 */
        DCIFreeCursor(cur);
        /* end add dci 20141103 */
        
        /* mod dci 20141103 
        EXEC SQL CLOSE cur_pzsj_zh;
        */
        /* EXEC SQL FREE  cur_pzsj_zh;  */      
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("打开凭单文件失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH打开凭单文件失败[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle));
    }
    LOG(LM_STD,Fmtmsg("sFile[%s]",sFile),fpub_GetCompname(lXmlhandle));
    /*开始循环*/
    /* add dci 20141103 */
    memset(&stPzsj, 0x00, sizeof(stPzsj));		
    while(1)
    {
    		
    		memset(&stPzsj, 0x00, sizeof(stPzsj));
    		iRet = DBFetch(cur, SD_TIPS_PZSJ,NUMELE(SD_TIPS_PZSJ),&stPzsj, sErrmsg );
				if ( iRet < 0 )
		    {
		        fpub_SetMsg(lXmlhandle,24409, "查税票信息失败");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查税票信息失败"),
		            fpub_GetCompname(lXmlhandle))
		    } 
		    if ( iRet == 0 )
            break;
        
		    /*
    		iRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);    		
    		if ( iRet < 0 )
        {  
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        	
        	iFlag=-1;
        	LOG(LM_STD,Fmtmsg("GenBILLZH从cur_pzsj_zh游标获取数据失败"),"ERROR");
        	break;
        }
        
        if ( iRet == 0 )
            break;
        
        i=0;
    		sprintf( stPzsj.zwrq, "%s", DCIFieldAsString( cur, i++ ) ); 
        stPzsj.zhqzlsh=atoi(DCIFieldAsString( cur, i++ ) );         
        sprintf( stPzsj.jyrq        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.dqdh        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jgdh        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jygy        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zddh        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.msgno       , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.entrustdate , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxorgcode  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.packno      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.trano       , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payeebankno , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payeename   , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.paybkcode   , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payopbkcode , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payacct     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.handorgname , "%s", DCIFieldAsString( cur, i++ ) );
				stPzsj.jyje = atof(DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.corpcode    , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxvouno    , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxpaycode  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.pzlx        , "%s", DCIFieldAsString( cur, i++ ) );
				stPzsj.dycs = atoi(DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.dzbz        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.pzsjwjm     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jyqd        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zjrq        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zjsj        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zjlsh       , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jyzt        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.hxdzbz      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.qsbz        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxpayname  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.qspch				, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.chkdate     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.chkacctord	, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.opbankno		, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.opbankname  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.khh					, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.chjyje			, "%s", DCIFieldAsString( cur, i++ ) );
    		*/
    		LOG(LM_STD,Fmtmsg("zwrq[%s],zhqzlsh[%d],pzlx[%s]",stPzsj.zwrq,stPzsj.zhqzlsh,stPzsj.pzlx),fpub_GetCompname(lXmlhandle));
                        
        /*生成凭证 */
        iret = 0;
        if ( stPzsj.pzlx[0]=='1' || stPzsj.pzlx[0]=='2')
        {
            /* 税务凭证 */
            iret = prv_tips_swpz(lXmlhandle,fp,sZwrq,stmproot,&stPzsj,1);    
        }else if (stPzsj.pzlx[0]=='6')
        {
            /* 社保凭证 暂不支持 */
            LOG(LM_STD,Fmtmsg("目前暂不支持社保凭证zwrq[%s]zhqzlsh[%d]",
                stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle)) 
        }else
        {
            /* 其他类型的凭证 暂不开发 */
            LOG(LM_STD,Fmtmsg("目前暂不支持其他类型凭证zwrq[%s]zhqzlsh[%d]",
                stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle))
        }            
        
        if (iret < 0)
        {
        	 LOG(LM_STD,Fmtmsg("生成凭证失败prv_tips_swpz=[%d]",iret),"ERROR");
        	 iFlag = -2;
        	 break;
        }            
        
        /*更新打印次数 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_pzsj "
    			"set  dycs = dycs + 1 "
    			"where zwrq='%s' and zhqzlsh='%d'",stPzsj.zwrq ,stPzsj.zhqzlsh);
               	
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		LOG(LM_STD,Fmtmsg("更新凭证打印次数失败"),"ERROR");
        		iFlag = -3;
        		break;
    		}
            
    }
    
    fclose(fp);
    DCIFreeCursor(cur);
    /* end dci 20141103 */
    
    /* mod dci 20141103
    for (i=1,iFlag=0;;i++)
    {
        memset(&stPzsj, 0x00, sizeof(stPzsj));
        
        EXEC SQL FETCH cur_pzsj_zh INTO :stPzsj;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_pzsj_zh",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iFlag=-1;
        	LOG(LM_STD,Fmtmsg("GenBILLZH从cur_pzsj_zh游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
            break;

        /*生成凭证
        iret = 0;
        if ( stPzsj.pzlx[0]=='1' || stPzsj.pzlx[0]=='2')
        {
            /* 税务凭证 
            iret = prv_tips_swpz(lXmlhandle,fp,sZwrq,stmproot,&stPzsj,1);    
        }else if (stPzsj.pzlx[0]=='6')
        {
            /* 社保凭证 暂不支持
            LOG(LM_STD,Fmtmsg("目前暂不支持社保凭证zwrq[%s]zhqzlsh[%d]",
                stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle)) 
        }else
        {
            /* 其他类型的凭证 暂不开发
            LOG(LM_STD,Fmtmsg("目前暂不支持其他类型凭证zwrq[%s]zhqzlsh[%d]",
                stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle))
        }            
        
        if (iret < 0)
        {
        	 LOG(LM_STD,Fmtmsg("生成凭证失败prv_tips_swpz=[%d]",iret),"ERROR");
        	 iFlag = -2;
        	 break;
        }
        

        /*更新打印次数
        EXEC SQL UPDATE tips_pzsj
             SET  dycs = dycs + 1
             WHERE  zwrq=:stPzsj.zwrq
               AND  zhqzlsh=:stPzsj.zhqzlsh;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERR");
        if (SQLERR)
        {    
        	LOG(LM_STD,Fmtmsg("更新凭证打印次数失败"),"ERROR");
        	iFlag = -3;
        	break;
        }
    }
    fclose(fp);
    EXEC SQL CLOSE cur_pzsj_zh;
    */
   /*  EXEC SQL FREE  cur_pzsj_zh; */   
    
    if (iFlag < 0)
    {
        fpub_SetMsg(lXmlhandle,24410, "生成凭单失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH生成凭单失败"),
            fpub_GetCompname(lXmlhandle))
    }
    LOG(LM_DEBUG,Fmtmsg("生成凭单处理结束"), fpub_GetCompname(lXmlhandle));      	 
    fpub_SetMsg(lXmlhandle, 0, "生成凭单处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_XIBPLGenBILL
组件名称: 按机构生成税票打印文件
组件功能: 
  按机构生成税票打印文件
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_XIBPLGenBILL(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sPayAcct[32];/* 付款账号 */
         char sZwrq[8+1];/* 账务日期 */
         char sDqdh[10+1];/* 地区代号 */
         char sJgdh[10+1];/* 机构代号 */
         char sSql[512];
         SDB_TIPS_PZSJ stPzsj;
    /*EXEC SQL END   DECLARE SECTION;*/

    char sBuf[256];
    char sTmpBuf[256];
    char sFile[256],sFilePath[256];/*扣税文件名*/
    char stmproot[256];
    char stmpnode[256];
    char sGenPdfs[1+1];
    char sEntrustDate[8+1];/* 委托日期 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sTraNo[8+1];
    int  i;
    int  k;
    FILE *fp;
    char sJygy[16+1];/* 交易柜员 */
    double dTmpAmt=0.00;
    int  iFlag=0;
    int  iSumCount=0;
    int  iProjectNum=0;
	int iret = 0;
	int iflag = 1;
	
		char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur,cur1;
		int iRet=0;
	            
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("生成机构打印税票开始处理... "), fpub_GetCompname(lXmlhandle))

    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(1)
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1,sBuf,"账务日期");
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));

    LOG(LM_STD,Fmtmsg("账务日期[%s]开始生成税票打印文件......",
        sZwrq), fpub_GetCompname(lXmlhandle))
    
    /* add dci 20141103 */
    iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select jgdh from tips_jgdhdj"); 
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,36001, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ打开cur_ksfmx_plhz游标失败"),
            fpub_GetCompname(lXmlhandle))
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL DECLARE cur_jgdh_sel CURSOR for 
    	select jgdh from tips_jgdhdj; 
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_jgdh_sel",sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_jgdh_sel;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_jgdh_sel", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24409, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH打开cur_jgdh_sel游标失败"),
            fpub_GetCompname(lXmlhandle))
    } 
    */
    
    while(1)
    {
    		/* add dci 20141103 */
    		iRet = DCIFetch(cur);
				if ( iRet < 0 )
        {  
        	iFlag=-1;
        	LOG(LM_STD,Fmtmsg("GenBILLZH从cur_jgdh_sel游标获取数据失败"),"ERROR");
        	break;
        }
        if ( iRet == 0 )
            break;
            
    		memset(sJgdh, 0x00, sizeof(sJgdh));
    		strncpy( sJgdh, DCIFieldAsString(cur, 0 ), sizeof( sZwrq ) );
    		/* end dci 20141103 */
    		
    		/* mod dci 20141103
        EXEC SQL FETCH cur_jgdh_sel INTO :sJgdh;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_jgdh_sel",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iFlag=-1;
        	LOG(LM_STD,Fmtmsg("GenBILLZH从cur_jgdh_sel游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
            break;
				*/
				
	    	trim(sJgdh);
	    	LOG(LM_STD,Fmtmsg("机构[%s]生成税票文件",sJgdh),"ERROR");
	    	/*declare modify by wangw 20120911 去掉日期限制*/
	    	/* add dci 20141103 */
	    	memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select * from tips_pzsj \
	    		where jgdh='%s' and dycs=0 and dzbz='1'",sJgdh);
    		if ((cur1 = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        		return COMPRET_FAIL;
    		}
    		if (DCIExecute(cur1) == -1)
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        		DCIFreeCursor(cur);
        		fpub_SetMsg(lXmlhandle,36001, "打开游标失败");
        		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ打开cur_ksfmx_plhz游标失败"),
            fpub_GetCompname(lXmlhandle))
    		}
	    	/* end dci 20141103 */
	    
	    /* mod dci 20141103 
	    EXEC SQL DECLARE cur_plpzsj_zh CURSOR for 
	    	select * from tips_pzsj 
	    		where jgdh=:sJgdh and dycs=0 and dzbz='1';
	    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_plpzsj_zh",sqlca.sqlcode),"ERROR");
	    
	    EXEC SQL OPEN cur_plpzsj_zh;
	    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_plpzsj_zh", sqlca.sqlcode),"ERROR");
	    if ( SQLERR )
	    {
	        fpub_SetMsg(lXmlhandle,24409, "打开游标失败");
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH打开cur_plpzsj_zh游标失败"),
	            fpub_GetCompname(lXmlhandle))
	    } 
			*/
			
	    sprintf(sFilePath,"%s/file/download/%s",getenv("HOME"),sZwrq);
	    sprintf(sFile,"%s/sp_print_%s_%s",sFilePath,sJgdh,sZwrq);
	    if(access(sFilePath,0))
	    {
	    	memset(sTmpBuf,0,sizeof(sTmpBuf));
	    	sprintf(sTmpBuf,"mkdir %s",sFilePath);
	    	system(sTmpBuf);
	    }
	    	
	    fp=fopen(sFile,"w");
	    if ( fp == NULL )
	    {
	        /* add dci 20141103 */
	        DCIFreeCursor(cur1);
	        /* end dci 20141103 */
	        
	        /* mod dci 20141103 
	        EXEC SQL CLOSE cur_pzsj_zh;
	        */
	        
	        /* EXEC SQL FREE  cur_pzsj_zh;  */      
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("打开凭单文件失败"));
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH打开凭单文件失败[%s]", 
	            strerror(errno)), fpub_GetCompname(lXmlhandle));
	    }
	
	    /*开始循环*/
	    for (i=1,iFlag=0;;i++)
	    {
	        memset(&stPzsj, 0x00, sizeof(stPzsj));
	        /* add dci 20141103 */
	        
	        /* end add dci 20141103 */
	        iRet = DBFetch(cur1, SD_TIPS_PZSJ,NUMELE(SD_TIPS_PZSJ),&stPzsj, sErrmsg );
					if ( iRet < 0 )
					{
						iFlag=-1;
	        	LOG(LM_STD,Fmtmsg("GenBILLZH从cur_pzsj_zh游标获取数据失败"),"ERROR");
	        	break;
					}
					if ( iRet == 0 )
					{
						break;
					}
	        /* mod dci 20141103 
	        EXEC SQL FETCH cur_plpzsj_zh INTO :stPzsj;     
	        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_plpzsj_zh",sqlca.sqlcode),"ERROR");
	        if ( SQLERR )
	        {  
	        	iFlag=-1;
	        	LOG(LM_STD,Fmtmsg("GenBILLZH从cur_pzsj_zh游标获取数据失败"),"ERROR");
	        	break;
	        }
	        if ( SQLNOTFOUND )
	            break;
	        */
	
	        /*生成凭证*/
	        iret = 0;
	        if ( stPzsj.pzlx[0]=='1' || stPzsj.pzlx[0]=='2')
	        {
	            /* 税务凭证 */
        			sprintf(stmproot,"/tmproot");
	            iret = prv_tips_swpz(lXmlhandle,fp,sZwrq,stmproot,&stPzsj,1);    
	            iret = prv_tips_swpz(lXmlhandle,fp,sZwrq,stmproot,&stPzsj,2);    
	        }else if (stPzsj.pzlx[0]=='6')
	        {
	            /* 社保凭证 暂不支持*/
	            LOG(LM_STD,Fmtmsg("目前暂不支持社保凭证zwrq[%s]zhqzlsh[%d]",
	                stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle)) 
	        }else
	        {
	            /* 其他类型的凭证 暂不开发*/
	            LOG(LM_STD,Fmtmsg("目前暂不支持其他类型凭证zwrq[%s]zhqzlsh[%d]",
	                stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle))
	        }            
	        
	        if (iret < 0)
	        {
	        	 LOG(LM_STD,Fmtmsg("生成凭证失败prv_tips_swpz=[%d]",iret),"ERROR");
	        	 iFlag = -2;
	        	 break;
	        }
	
	        /*更新打印次数 */
	        /* add dci 20141103 */
	        
        	memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_pzsj "
    				"set  dycs = dycs + 1 "
    					"where zwrq='%s' and zhqzlsh='%d'",stPzsj.zwrq ,stPzsj.zhqzlsh);
               	
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		LOG(LM_STD,Fmtmsg("更新凭证打印次数失败"),"ERROR");
        		iFlag = -3;
        		break;
    			}
    			
    			iRet =DCICommit();
    			/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
    			if ( iRet < 0 )
    			{
      			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      			DCIRollback();
      			
       			fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交事务失败！"));
       			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       			return COMPRET_FAIL;     
    			}
    			*/
    			
    			/* end add dci */
	        
	        /* mod dci 20141103
	        EXEC SQL UPDATE tips_pzsj
	             SET  dycs = dycs + 1
	             WHERE  zwrq=:stPzsj.zwrq
	               AND  zhqzlsh=:stPzsj.zhqzlsh;
	        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERR");
	        if (SQLERR)
	        {    
	        	LOG(LM_STD,Fmtmsg("更新凭证打印次数失败"),"ERROR");
	        	iFlag = -3;
	        	break;
	        }
			    EXEC SQL COMMIT;  /*提交*/
			    
	    }
	    fclose(fp);
	    /* add dci 20141103 */
	    DCIFreeCursor(cur1);
	    /* end add dci 20141103 */
	    
	    /* mod dci 20141103 
	    EXEC SQL CLOSE cur_plpzsj_zh;
	    */
	    
   		/*  EXEC SQL FREE  cur_pzsj_zh; */  
	    if (iFlag < 0)
	    {
	        fpub_SetMsg(lXmlhandle,24410, "生成凭单失败");
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH生成凭单失败"),
	            fpub_GetCompname(lXmlhandle))
	    }
   	} 
	  /* add dci 20141103 */
	  DCIFreeCursor(cur);
	  /* end add dci 20141103 */
	    
	  /* mod dci 20141103 
	  EXEC SQL CLOSE cur_jgdh_sel;
	  */
    
    LOG(LM_DEBUG,Fmtmsg("生成凭单处理结束"), fpub_GetCompname(lXmlhandle));      	 
    fpub_SetMsg(lXmlhandle, 0, "生成凭单处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_XIBDBGenBILL
组件名称: 单笔生成税票打印文件
组件功能: 
  单笔生成税票打印文件
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_XIBDBGenBILL(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sZwrq[8+1];/* 账务日期 */
         char sFkzh[32+1];/* 付款账号 */
         char sNsrbm[20+1];/* 纳税人编码 */
         char sSphm[20+1];/* 税票号码 */
         SDB_TIPS_PZSJ stPzsj;
         char sSql[512];
    /*EXEC SQL END   DECLARE SECTION;*/

    char sBuf[256];
    char sTmpBuf[256];
    char sFile[256];/*扣税文件名*/
    char stmproot[256];
    char stmpnode[256];
    char sGenPdfs[1+1];
    char sEntrustDate[8+1];/* 委托日期 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sTraNo[8+1];
    int  i;
    int  k;
    FILE *fp;
    char sJygy[16+1];/* 交易柜员 */
    double dTmpAmt=0.00;
    int  iFlag=0;
    int  iSumCount=0;
    int  iProjectNum=0;
		int iret = 0;
		int iflag = 1;
		
		char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;
		int iRet=0;
		
		iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
	            
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("单笔打印税票开始处理... "), fpub_GetCompname(lXmlhandle))

    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(4)
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1,sBuf,"付款账号");
    pstrcopy(sFkzh, sBuf, sizeof(sFkzh));
    trim(sFkzh);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sNsrbm, 0x00, sizeof(sNsrbm));
    COMP_GETPARSEPARAS(2,sBuf,"纳税人编码");
    pstrcopy(sNsrbm, sBuf, sizeof(sNsrbm));
    trim(sNsrbm);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSphm, 0x00, sizeof(sSphm));
    COMP_GETPARSEPARAS(3,sBuf,"税票号码");
    pstrcopy(sSphm, sBuf, sizeof(sSphm));
    trim(sSphm);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile, 0x00, sizeof(sFile));
    COMP_GETPARSEPARAS(4,sBuf,"税票文件");
    pstrcopy(sFile, sBuf, sizeof(sFile));
    trim(sSphm);

    LOG(LM_STD,Fmtmsg("付款账号[%s],纳税人编码[%s],税票号码[%s],税票文件[%s]开始生成税票打印文件......",
        sFkzh,sNsrbm, sSphm,sFile), fpub_GetCompname(lXmlhandle))
    
    /* 20150729 直接参数传入
  	sprintf(sFile,"%s/file/bill/%s_%s",getenv("HOME"),sNsrbm,sSphm);*/
    fp=fopen(sFile,"w");
    if ( fp == NULL )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("打开凭单文件失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenBILLZH打开凭单文件失败[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle));
    }
		
    /*declare*/
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select * from tips_pzsj where payacct='%s' and taxpaycode='%s' and taxvouno='%s'", sFkzh, sNsrbm, sSphm);
    LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO")
/*    EXEC SQL DECLARE cur_dbpzsj CURSOR for select * from tips_pzsj 
    		where payacct=:sFkzh and taxpaycode=:sNsrbm and taxvouno=:sSphm; */
    
    /* add dci 20141103 */
		if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  	{
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  	}
  	if (DCIExecute(cur) == -1)
  	{
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  	}
	/* end add dci 20141103 */
    /* mod dci 20141103 
 	/*prepare
    EXEC SQL PREPARE sql_qrydbsj FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrydbsj",sqlca.sqlcode),"ERROR");    
    EXEC SQL DECLARE cur_dbpzsj CURSOR for sql_qrydbsj;
    EXEC SQL OPEN cur_dbpzsj;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_pzsj_zh", sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24409, "查税票信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查税票信息失败"),
            fpub_GetCompname(lXmlhandle))
    } 
    */

    while(1)
    {
    	  memset(&stPzsj, 0x00, sizeof(stPzsj));
				
				/* add dci 20141103 */
				iRet = DBFetch(cur, SD_TIPS_PZSJ,NUMELE(SD_TIPS_PZSJ),&stPzsj, sErrmsg );
				if ( iRet < 0 )
		    {
		        fpub_SetMsg(lXmlhandle,24409, "查税票信息失败");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查税票信息失败"),
		            fpub_GetCompname(lXmlhandle))
		    } 
		    if ( iRet == 0 )
		    {
		    	break;
		    } 	
				/* mod dci 20141103 
		    EXEC SQL FETCH cur_dbpzsj into :stPzsj ;     
		    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dbpzsj_zh",sqlca.sqlcode),"ERROR");
		    if ( SQLERR )
		    {
		        fpub_SetMsg(lXmlhandle,24409, "查税票信息失败");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查税票信息失败"),
		            fpub_GetCompname(lXmlhandle))
		    } 
		    if ( SQLNOTFOUND )
		    {
		    	break;
		    } 
		    */
    	
	    /*生成凭证*/
	    if ( stPzsj.pzlx[0]=='1' || stPzsj.pzlx[0]=='2')
	    {
	        /* 税务凭证 */
	        sprintf(stmproot,"/tmproot");
	        iret = prv_tips_swpz(lXmlhandle,fp,stPzsj.zwrq,stmproot,&stPzsj,1);    
	        iret = prv_tips_swpz(lXmlhandle,fp,stPzsj.zwrq,stmproot,&stPzsj,2);    
	    }else if (stPzsj.pzlx[0]=='6')
	    { 
	        /* 社保凭证 暂不支持*/
	        LOG(LM_STD,Fmtmsg("目前暂不支持社保凭证zwrq[%s]zhqzlsh[%d]",
	            stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle)) 
	    }else
	    {
	        /* 其他类型的凭证 暂不开发*/
	        LOG(LM_STD,Fmtmsg("目前暂不支持其他类型凭证zwrq[%s]zhqzlsh[%d]",
	            stPzsj.zwrq, stPzsj.zhqzlsh), fpub_GetCompname(lXmlhandle))
	    }

	    /*更新打印次数*/
	    /* add dci 20141103 */
	    
      memset( sSql1, 0x00, sizeof( sSql1 ) );
    	snprintf( sSql1, sizeof(sSql1), "update tips_pzsj "
    				"set  dycs = dycs + 1 "
    					"where zwrq='%s' and zhqzlsh='%d'",stPzsj.zwrq ,stPzsj.zhqzlsh);
               	
    	iRet = DCIExecuteDirect(sSql1);	 
    	if ( iRet < 0 )
    	{
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
      
      	LOG(LM_STD,Fmtmsg("更新凭证打印次数失败"),"ERROR");
      	iFlag = -3;
      	break;
    	}
    	
    	iRet =DCICommit();
    	/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  */
    	if ( iRet < 0 )
    	{
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交事务失败！"));
      	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      	return COMPRET_FAIL;     
    	}
    	
    	
    	/* end add dci 20141103 */
    	
	    /* mod dci 20141103 
	    EXEC SQL UPDATE tips_pzsj
	         SET  dycs = dycs + 1
	         WHERE  zwrq=:stPzsj.zwrq
	           AND  zhqzlsh=:stPzsj.zhqzlsh;
	    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERR");
	    if (SQLERR)
	    {
	        fpub_SetMsg(lXmlhandle,24409, "更新凭证打印次数失败");
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新凭证打印次数失败"),
	            fpub_GetCompname(lXmlhandle))
	    } 
			EXEC SQL COMMIT;  /*提交*/
			
			
	  }            
    fclose(fp);
    /* add dci 20141103 */
    DCIFreeCursor(cur);
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL CLOSE cur_dbpzsj;
    */    
   
   COMP_SOFTSETXML("/pub/wjbz", "1")
   COMP_SOFTSETXML("/pub/wjmc", sFile)
    
    LOG(LM_DEBUG,Fmtmsg("生成凭单处理结束"), fpub_GetCompname(lXmlhandle));      	 
    fpub_SetMsg(lXmlhandle, 0, "生成凭单处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
    
