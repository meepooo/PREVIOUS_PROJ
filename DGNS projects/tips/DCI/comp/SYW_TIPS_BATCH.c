/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V3.0.00
操作系统:AIX5.3
文件名称:SYW_TIPS_BATCH.ec
文件描述:TIPS批量交易
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
EXEC SQL INCLUDE  "../eh/tips_pljydj.eh";批量交易登记表
EXEC SQL INCLUDE  "../eh/tips_ssplpcdj.eh";税收批量批次登记表
EXEC SQL INCLUDE  "../eh/tips_ssplksfmx.eh";税收批量扣税费明细表
EXEC SQL INCLUDE  "../eh/tips_ssplzfksf.eh";税收批量止付扣税费表
EXEC SQL INCLUDE  "../eh/tips_pzsj.eh";凭证数据表
*/

/* add dci 20141103 */
#include "../eh/tips_pljydj.h"/*批量交易登记表 */
#include "../eh/tips_ssplpcdj.h"/*税收批量批次登记表 */
#include "../eh/tips_ssplksfmx.h"/*税收批量扣税费明细表 */
#include "../eh/tips_ssplzfksf.h"/*税收批量止付扣税费表 */
#include "../eh/tips_pzsj.h"/*凭证数据表 */
#include "../eh/DRC/tips_taxtypemx_drc.h"/* 税种明细表 */
/* end add dci 20141103 */

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )

#define FILE_BEGIN "BEGIN"
#define FILE_END "END"

#ifndef __TIPS_GENFILE_
#define __TIPS_GENFILE_
typedef struct TDB_GENFILE
{
    HXMLTREE lXmlhandle ;        /* 全局XML树句柄 */
    char zwrq[8+1] ;            /* 帐务日期 */
    char pljylsh[8+1] ;          /* 批量交易流水号 */
    char plpch[5+1] ;         /* 批量批次号 */
    char resicxp[30+1];        /* ICXP报文名称 */
    FILE *fp;                    /* 文件指针 */
}SDB_GENFILE;
#endif

/* 登记凭证信息 */
/* 2014年12月20日DCI改造 */
int prv_tips_InitPZSJ_pl(HXMLTREE lXmlhandle, SDB_TIPS_SSPLKSFMX stPlksfmx)
{
		/* add dci 20141103 
    EXEC SQL BEGIN DECLARE SECTION;
         SDB_TIPS_PZSJ stPzsj;
    EXEC SQL END DECLARE SECTION;
    */
    
    /* add DCI 20141103 */
    char sBuf[256];/* 临时变量 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		SDB_TIPS_PZSJ stPzsj;
		SDB_TIPS_PLJYDJ stPljydj;
		int iRet=0;
/* end add dci 20141103 */
        
    /* 查询批量交易登记表信息 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj\
    	 where zwrq='%s' and pljylsh='%s'",stPlksfmx.zwrq, stPlksfmx.pljylsh);     
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24279, "initPlksfmx查询批量交易登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end add dci 20141103 */
    
    
    memset(&stPzsj, 0x00, sizeof(stPzsj));
    
    pstrcopy(stPzsj.zwrq, stPlksfmx.zwrq, sizeof(stPzsj.zwrq));
    stPzsj.zhqzlsh = stPlksfmx.plmxxh;
    pstrcopy(stPzsj.jyrq, stPlksfmx.workdate, sizeof(stPzsj.jyrq));
    pstrcopy(stPzsj.dqdh, stPlksfmx.dqdh, sizeof(stPzsj.dqdh));
    pstrcopy(stPzsj.jgdh, stPlksfmx.jgdh, sizeof(stPzsj.jgdh));
    pstrcopy(stPzsj.jygy, stPlksfmx.jygy, sizeof(stPzsj.jygy));
    pstrcopy(stPzsj.zddh, stPlksfmx.zddh, sizeof(stPzsj.zddh));
    pstrcopy(stPzsj.msgno, "3102", sizeof(stPzsj.msgno));/* 报文编号 */
    pstrcopy(stPzsj.entrustdate, stPlksfmx.entrustdate, sizeof(stPzsj.entrustdate));
    pstrcopy(stPzsj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stPzsj.taxorgcode));
    pstrcopy(stPzsj.packno, stPlksfmx.packno, sizeof(stPzsj.packno));
    pstrcopy(stPzsj.trano, stPlksfmx.trano, sizeof(stPzsj.trano));
    pstrcopy(stPzsj.payeebankno, stPlksfmx.payeebankno, sizeof(stPzsj.payeebankno));
    pstrcopy(stPzsj.payeename, stPljydj.payeename, sizeof(stPzsj.payeename));
    
    pstrcopy(stPzsj.paybkcode, stPlksfmx.paybkcode, sizeof(stPzsj.paybkcode));
    pstrcopy(stPzsj.payopbkcode, stPlksfmx.payopbkcode, sizeof(stPzsj.payopbkcode));
    pstrcopy(stPzsj.payacct, stPlksfmx.payacct, sizeof(stPzsj.payacct));
    pstrcopy(stPzsj.handorgname, stPlksfmx.handorgname, sizeof(stPzsj.handorgname));
    stPzsj.jyje=stPlksfmx.jyje;
    pstrcopy(stPzsj.corpcode, "", sizeof(stPzsj.corpcode));
    pstrcopy(stPzsj.taxvouno, stPlksfmx.taxvouno, sizeof(stPzsj.taxvouno));
    pstrcopy(stPzsj.taxpaycode, stPlksfmx.taxpaycode, sizeof(stPzsj.taxpaycode));
    stPzsj.pzlx[0]='1';
    stPzsj.dycs=0;
    stPzsj.dzbz[0]='0';
    pstrcopy(stPzsj.pzsjwjm, stPlksfmx.spxx, sizeof(stPzsj.pzsjwjm));
    /* add by lijn 20140825 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyqd", sBuf)
    pstrcopy(stPzsj.jyqd, sBuf, sizeof(stPzsj.jyqd));
    pstrcopy(stPzsj.zjrq      , stPlksfmx.zjrq      , sizeof(stPzsj.zjrq      ));
    pstrcopy(stPzsj.zjsj      , stPlksfmx.zjsj      , sizeof(stPzsj.zjsj      ));
    pstrcopy(stPzsj.zjlsh     , stPlksfmx.zjlsh     , sizeof(stPzsj.zjlsh     ));
    if(strcmp(stPlksfmx.czbd,"7")==0)
    	pstrcopy(stPzsj.jyzt      , "0"      , sizeof(stPzsj.jyzt      ));
    else
    	pstrcopy(stPzsj.jyzt      , "1"      , sizeof(stPzsj.jyzt      ));
    stPzsj.hxdzbz[0]='0';
    pstrcopy(stPzsj.qsbz      , stPlksfmx.qsbz      , sizeof(stPzsj.qsbz      ));
    pstrcopy(stPzsj.taxpayname, stPlksfmx.taxpayname, sizeof(stPzsj.taxpayname));
    pstrcopy(stPzsj.qspch			, ""			, sizeof(stPzsj.qspch			));
    pstrcopy(stPzsj.chkdate   , stPlksfmx.chkdate   , sizeof(stPzsj.chkdate   ));
    pstrcopy(stPzsj.chkacctord, stPlksfmx.chkacctord, sizeof(stPzsj.chkacctord));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/req/khjg",sBuf)       
    pstrcopy(stPzsj.opbankno   , sBuf   , sizeof(stPzsj.opbankno   ));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/req/khjgmc",sBuf) 
    pstrcopy(stPzsj.opbankname,  sBuf   , sizeof(stPzsj.opbankname));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/req/khh",sBuf) 
    pstrcopy(stPzsj.khh,  sBuf   , sizeof(stPzsj.khh));
    
    prv_get_dxje(stPzsj.jyje,sBuf);
    pstrcopy(stPzsj.chjyje,  sBuf   , sizeof(stPzsj.chjyje));
    /* add by lijn 20140825 */
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_pzsj", SD_TIPS_PZSJ, NUMELE(SD_TIPS_PZSJ), &stPzsj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	/* DCIRollback();   */
    	
    	LOG(LM_STD,Fmtmsg("新增凭证信息失败,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")        
        return -1;
    }
    /* end dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL INSERT INTO tips_pzsj VALUES(:stPzsj);
    if ( SQLERR )
    {
        LOG(LM_STD,Fmtmsg("新增凭证信息失败,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")        
        return -1;
    }
    */
    LOG(LM_STD,Fmtmsg("新增凭证信息成功,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"INFO")      
    return 0;    
    
}

/*
 *   委托关系校验 mod by tuql 20090909 校验通过后返回地区代号及机构代号 
 */
int prv_tips_ChkWtgx(char *prono, char *payacct, char *taxpaycode, char *dqdh, char *jgdh, char *payopbkcode/* add by sunpj 20090909 */,char *payacct2/* add by liurj 20180713 */)
{
	/* add dci 20141103 
EXEC SQL BEGIN DECLARE SECTION;*/
	   char sProtocolNo[60+1];
	   char sPayAcct[32+1];
	   char sWtgxzt[1+1];
	   char sYzbz[1+1];
	   char sTaxPayCode[20+1];
	   char sDqdh[10+1];/* add by tuql 20090909 */
	   char sJgdh[10+1];/* add by tuql 20090909 */	   
	   char sPayOpBkCode[12+1];/* add by sunpj 20090909 */	
	   char sPayAcct2[32+1]; /* add by liurj 20180713 */
	/* add dci 20141103 
EXEC SQL END DECLARE SECTION;*/
	
		/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
	
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    pstrcopy(sProtocolNo, prono, sizeof(sProtocolNo));/* 协议书号 */
    pstrcopy(sPayAcct, payacct, sizeof(sPayAcct));/* 付款人账号 */
    trim(sProtocolNo);trim(sPayAcct);
    
    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sYzbz, 0x00, sizeof(sYzbz));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    memset(sDqdh, 0x00, sizeof(sDqdh));
    memset(sJgdh, 0x00, sizeof(sJgdh));
	memset(sPayOpBkCode, 0x00, sizeof(sPayOpBkCode));
	memset(sPayAcct2, 0x00, sizeof(sPayAcct2));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
	snprintf( sSql1, sizeof(sSql1), "select wtgxzt, yzbz, taxpaycode, djdqdh, djjgdh, payopbkcode, payacct2 FROM tips_wtgxdj\
	WHERE protocolno ='%s' AND payacct ='%s'",sProtocolNo,sPayAcct);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")        
		iRet = DBSelectToMultiVar(sErrmsg, sSql1, &sWtgxzt, &sYzbz, &sTaxPayCode, &sDqdh, &sJgdh, &sPayOpBkCode, &sPayAcct2);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        LOG(LM_STD,Fmtmsg("查询委托关系失败protocolno[%s], payacct[%s]", sProtocolNo, sPayAcct),"INFO")
     		return -1;	
        
    }
    if ( iRet == 0 )
    {
        /*关系未找到,不返回错  */
     	return 1;
    }


    /* end dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL SELECT wtgxzt, yzbz, taxpaycode, djdqdh, djjgdh 
         INTO :sWtgxzt, :sYzbz, :sTaxPayCode, :sDqdh, :sJgdh
         FROM tips_wtgxdj
         WHERE  protocolno = :sProtocolNo
           AND  payacct = :sPayAcct;        
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {        
    	LOG(LM_STD,Fmtmsg("查询委托关系失败protocolno[%s], payacct[%s]", sProtocolNo, sPayAcct),"INFO")
     	return -1;
    }
    if ( SQLNOTFOUND_TIPS )
    {     
        /*关系未找到,不返回错  
     	return 1;
    }
    */
  
    if(sWtgxzt[0]!='0')	  		
    {
        /*委托关系异常*/  
        return 2;
    }

    if(sYzbz[0]!='1')	  		
    {
        /*关系未验证*/  
        return 3;
    }
    trim(sTaxPayCode);
    /* Linux系统下若为sizeof(taxpaycode), 则不能传回 */
    pstrcopy(taxpaycode, sTaxPayCode, sizeof(sTaxPayCode));
    trim(sDqdh);
    trim(sJgdh);
    pstrcopy(dqdh, sDqdh, sizeof(sDqdh));
    pstrcopy(jgdh, sJgdh, sizeof(sJgdh));
	pstrcopy(payopbkcode, sPayOpBkCode, sizeof(sPayOpBkCode));
	pstrcopy(payacct2,sPayAcct2,sizeof(sPayAcct2));
    return 0;	
}	

/* 把获取的入帐文件信息放到XML树中 */
int prv_tips_PutKsfmxToXml(HXMLTREE lXmlhandle, SDB_TIPS_SSPLKSFMX stPlksfmx, char *sKeyCode)
{
   /* 在MXL树中初始化一些值，以便能生成请求主机文件 */ 
   char sBuf[256];
   /* 初始化 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/qzlsh","")/* 前置流水号 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zczh","")/* 转入帐号 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zrzh","")/* 转入帐号 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/jyje","")/* 交易金额 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zydm","")/* 摘要代码 */
   /* 赋值 */
   memset(sBuf, 0x00, sizeof(sBuf));
   snprintf(sBuf, sizeof(sBuf), "%d", stPlksfmx.plmxxh);
   COMP_SOFTSETXML("/hxxt/qqzjwj/qzlsh",sBuf)/* 前置流水号 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zczh",stPlksfmx.payacct)/* 转出帐号 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zrzh",stPlksfmx.dfzh)/* 转入帐号 */
   memset(sBuf, 0x00, sizeof(sBuf));
   snprintf(sBuf, sizeof(sBuf), "%.2f", stPlksfmx.jyje);
   COMP_SOFTSETXML("/hxxt/qqzjwj/jyje",sBuf)/* 交易金额 */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zydm", sKeyCode)/* 摘要代码 */
      
   return 0 ; 
}
/* 
 * 生成请求主机入帐文件
 */
int prv_tips_GenZjFile(SDB_GENFILE stGenZjFile)
{
    /* add dci  20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_SSPLKSFMX   stPlksfmx;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
    EXEC SQL END DECLARE SECTION;
    */
    int i;
    int iflag;
    int iret=-1;
    char sLine[1024];
    /* SDB_ZjIniCfg stZjIniCfg ; */    
    
		/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;
		SDB_TIPS_SSPLKSFMX   stPlksfmx;
		char sZwrq[8+1];
    char sPljylsh[8+1];
    char sPlpch[5+1];
	char sSql[1024+1];
	char sKeyCode[3+1];
		int iRet=0;
/* end add dci 20141103 */
      
    /* 获取生成入帐文件时的基本配置信息 
    memset(&stZjIniCfg, 0x00, sizeof(stZjIniCfg));
    iret=prv_plhk_GetZjIniCfg( &stZjIniCfg);
    */
    memset(sZwrq, 0x00, sizeof(sZwrq));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    pstrcopy(sZwrq, stGenZjFile.zwrq, sizeof(sZwrq));
    pstrcopy(sPljylsh, stGenZjFile.pljylsh, sizeof(sPljylsh));
    pstrcopy(sPlpch, stGenZjFile.plpch, sizeof(sPlpch));
           
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT * FROM  tips_ssplksfmx\
    	WHERE zwrq = '%s' and pljylsh = '%s' and plpch = '%s' ORDER BY plmxxh",sZwrq,sPljylsh,sPlpch); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(stGenZjFile.lXmlhandle,36001, "打开游标失败");
        LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile打开cur_ksfmx_rzfile失败"),"ERROR");
        return -1;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        
        iflag=-1;
        LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile从cur_ksfmx_rzfile获取数据失败"),"ERROR");
        
    }
		
    for (i=1,iflag=0;;i++)
    {
    		memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    		memset(sLine, 0x00, sizeof(sLine));
				iRet = DBFetch(cur, SD_TIPS_SSPLKSFMX,NUMELE(SD_TIPS_SSPLKSFMX),&stPlksfmx, sErrmsg );
				
				if ( iRet < 0 )
        {  
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        	
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile从cur_ksfmx_rzfile获取数据失败"),"ERROR");
        	break;
        }
        if ( iRet == 0 )
          break;

		/**摘要码生成 add by sunpj 20170712**/
		memset(sSql, 0x00, sizeof(sSql));
		memset(sKeyCode, 0x00, sizeof(sKeyCode));
		sprintf(sSql, "select decode(taxorgtype,'1','111','2','112','3','999','4','234','5','109','999') from tips_taxcodeinfo where taxorgcode='%s'"
		            , stPlksfmx.taxorgcode);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO")
		iRet = DBSelectToVarChar(sErrmsg, sKeyCode, sSql);
		if (0 > iRet || 0 == iRet)
		{
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]", DCILastError() ,iRet),"ERROR")
			strcpy(sKeyCode, "054");
		}

      	
      	iret=prv_tips_PutKsfmxToXml(stGenZjFile.lXmlhandle, stPlksfmx, sKeyCode);                      
        iret=SBATCH_FuncICXPPKG(stGenZjFile.lXmlhandle, stGenZjFile.resicxp, sLine);
        if (iret < 0)
        {  
            iflag=-2; 
            break;  
        }	
        fprintf(stGenZjFile.fp,"%s\n",sLine);                     
      	                
    }
    
    DCIFreeCursor(cur);
    
    /* end dci 20141103 */
    /* dci mod 20141103    
    EXEC SQL DECLARE cur_ksfmx_rzfile CURSOR for 
        SELECT * FROM  tips_ssplksfmx 
        WHERE zwrq = :sZwrq 
         AND  pljylsh = :sPljylsh
         AND  plpch = :sPlpch
         ORDER BY plmxxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_ksfmx_rzfile;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ksfmx_rzfile",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(stGenZjFile.lXmlhandle,36001, "打开游标失败");
        LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile打开cur_ksfmx_rzfile失败"),"ERROR");
        return -1;
    }
    /*开始循环
    for (i=1,iflag=0;;i++)
    {
        memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
        memset(sLine, 0x00, sizeof(sLine));
        EXEC SQL FETCH cur_ksfmx_rzfile INTO :stPlksfmx;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_ksfmx_rzfile", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile从cur_ksfmx_rzfile获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
        /*将记录内容放到XML树   
        iret=prv_tips_PutKsfmxToXml(stGenZjFile.lXmlhandle, stPlksfmx);                      
        iret=SBATCH_FuncICXPPKG(stGenZjFile.lXmlhandle, stGenZjFile.resicxp, sLine);
        if (iret < 0)
        {  
            iflag=-2; 
            break;  
        }	
        fprintf(stGenZjFile.fp,"%s\n",sLine);
    }	
    EXEC SQL CLOSE cur_ksfmx_rzfile; 
    */   
    /* EXEC SQL FREE  cur_ksfmx_rzfile; */
     
    if (iflag < 0)
    {
        fpub_SetMsg(stGenZjFile.lXmlhandle,36002,"生成请求主机文件失败");
        LOG(LM_STD,Fmtmsg("生成请求主机文件失败iflag=[%d]",iflag),"ERROR");
        return -2;
    }
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitPLJYDJ
组件名称: 初始化批量交易登记表
组件功能: 
  插入批量交易登记表；
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
批量交易登记表	tips_pljydj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月09日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPLJYDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[256];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        int iCount=0;
        char sPljydm[60+1];
    EXEC SQL END   DECLARE SECTION;
    */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;
  	SDB_TIPS_PLJYDJ stPljydj;
    int iCount=0;
    char sPljydm[60+1];
		int iRet=0;
/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif    

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "帐务日期")
    pstrcopy( stPljydj.zwrq, sBuf, sizeof(stPljydj.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "批量交易流水号")
    pstrcopy( stPljydj.pljylsh, sBuf, sizeof(stPljydj.pljylsh));
    
    LOG(LM_STD,Fmtmsg("初始化批量交易登记表 帐务日期[%s],批量交易流水号[%s]", 
        stPljydj.zwrq, stPljydj.pljylsh), fpub_GetCompname(lXmlhandle));
		
		/* add dci 20141103 */
		iCount=0;
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_pljydj\
    	 where zwrq='%s' and pljylsh=%d",stPljydj.zwrq,stPljydj.pljylsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("查询批量交易登记表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	  
    }
		/* end dci 20141103 */
		/* dci mod 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_pljydj
         WHERE zwrq = :stPljydj.zwrq
           AND pljylsh = :stPljydj.pljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("查询批量交易登记表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* 判断本批量包是否重复 */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("本批量包已登记"));
        LOG(LM_STD,Fmtmsg("InitPLJYDJ本批量包已登记"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }   
    
    /* 2.批量交易代码
    EXEC SQL SELECT b.num_desc INTO :sPljydm
         FROM tips_taxcodeinfo a, tips_codelist b
         WHERE a.taxorgcode = :stPljydj.orgcode
           AND b.code_name = 'tipspljydm'
           AND a.taxorgtype = b.num;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR || SQLNOTFOUND_TIPS || sPljydm[0]=='\0')
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("批量交易代码不能为空"));
        LOG(LM_STD,Fmtmsg("获取批量交易代码失败或批量交易代码为空"), fpub_GetCompname(lXmlhandle));
        return COMPRET_FAIL;
    }*/
    memset(sPljydm, 0x00, sizeof(sPljydm));    
    pstrcopy(stPljydj.pljydm, "SWPKS", sizeof(stPljydj.pljydm));
    COMP_SOFTSETXML("/tips/pljydm", stPljydj.pljydm)

    /* 4.批次总笔数 */
    stPljydj.pczbs = 0 ;

    /* 5.委托日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy( stPljydj.entrustdate, sBuf, sizeof(stPljydj.entrustdate));
    if ( stPljydj.entrustdate[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("外围主键不能为空"));
        LOG(LM_STD,Fmtmsg("委托日期不能为空, entrustdate=[%s]", stPljydj.entrustdate),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    } 
    
    /* 6.征收机关代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy( stPljydj.orgcode, sBuf, sizeof(stPljydj.orgcode));    
    if ( stPljydj.orgcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("征收机关代码不能为空"));
        LOG(LM_STD,Fmtmsg("征收机关代码不能为空, orgcode=[%s]", stPljydj.orgcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 7.包流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PackNo", sBuf)
    pstrcopy( stPljydj.packno, sBuf, sizeof(stPljydj.packno));       
    if ( stPljydj.packno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24286, Fmtmsg("包流水号不能为空"));
        LOG(LM_STD,Fmtmsg("包流水号不能为空, packno=[%s]", stPljydj.packno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

		/* add dci 20141103 */
		iCount=0;
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_pljydj\
    	 where entrustdate='%s' and orgcode='%s' and packno='%s'",stPljydj.entrustdate,stPljydj.orgcode,stPljydj.packno);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("查询批量交易登记表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	  
    }
    /* end add dci 20141103 */
    
		/* mod dci 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_pljydj
         WHERE entrustdate = :stPljydj.entrustdate
           AND orgcode = :stPljydj.orgcode
           AND packno = :stPljydj.packno;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("查询批量交易登记表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* 判断本批量包是否重复 */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("本批量包已登记"));
        LOG(LM_STD,Fmtmsg("InitPLJYDJ本批量包已登记"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }

    /* 8.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stPljydj.workdate, sBuf, sizeof(stPljydj.workdate));
    
    /* 9.总笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllNum", sBuf)
    stPljydj.allnum = atoi(sBuf);

    /* 10.总金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllAmt", sBuf)
    stPljydj.allamt = atof(sBuf);
    
    /* 11经收类别(1)|收款行行号(12)|收款单位代码(12)|收款人账号(12)|收款人名称(60)|付款行行号(12)|
     */
    /* 11.1经收类别 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandleType", sBuf)
    stPljydj.handletype[0] = sBuf[0];
    
    /* 11.2收款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy(stPljydj.payeebankno, sBuf, sizeof(stPljydj.payeebankno)); 
    trim(stPljydj.payeebankno);
    
    /* 11.3收款单位代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOrgCode", sBuf)
    pstrcopy(stPljydj.payeeorgcode, sBuf, sizeof(stPljydj.payeeorgcode)); 
    trim(stPljydj.payeeorgcode);
    
    /* 11.4收款人账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy(stPljydj.payeeacct, sBuf, sizeof(stPljydj.payeeacct)); 
    trim(stPljydj.payeeacct);
        
    /* 11.5收款人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeName", sBuf)
    pstrcopy(stPljydj.payeename, sBuf, sizeof(stPljydj.payeename)); 
    trim(stPljydj.payeename);

    /* 11.6付款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy(stPljydj.paybkcode, sBuf, sizeof(stPljydj.paybkcode)); 
    trim(stPljydj.paybkcode);               
		
		/* 对账日期 add 20150730 */
		memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stPljydj.chkdate, sBuf, sizeof(stPljydj.chkdate));
    
    /* 12.入帐总笔数 */
    stPljydj.rzzbs = 0 ;
    /* 13.入帐总金额 */
    stPljydj.rzzje = 0.0 ;
    /* 14.止付总笔数 */
    stPljydj.zfzbs = 0 ;    
    /* 15.止付总金额 */
    stPljydj.zfzje = 0.0 ;    
    /* 16.响应码 */
    stPljydj.xym[0] = '0' ;    
    /* 17.响应信息 */
    pstrcopy(stPljydj.xyxx, "批量交易初始化", sizeof(stPljydj.xyxx));    
    /* 18.操作步点 */
    stPljydj.czbd[0] = '1' ;    
    /* 19.完成标志 */
    stPljydj.wcbz[0] = '9' ;
    /* 20.处理起始日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stPljydj.clqsrq, sBuf, sizeof(stPljydj.clqsrq));    
    /* 21.处理起始时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stPljydj.clqssj, sBuf, sizeof(stPljydj.clqssj));
    /* 22.处理结束日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stPljydj.cljsrq, sBuf, sizeof(stPljydj.cljsrq));
    /* 23.处理结束时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stPljydj.cljssj, sBuf,sizeof(stPljydj.cljssj));
    /* 24.扩展标志 */
    pstrcopy(stPljydj.kzbz, "00000000",sizeof(stPljydj.kzbz));
    /* 25.备用字段 */
		
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_pljydj", SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	/* DCIRollback();   */
    	
    	fpub_SetMsg(lXmlhandle, 24276, "InitPLJYDJ初始化批量交易登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLJYDJ初始化批量交易登记表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;      
    }

		/* end dci 20141103 */
		/* mod dci 20141103 
    EXEC SQL INSERT INTO tips_pljydj  VALUES (:stPljydj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24276, "InitPLJYDJ初始化批量交易登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLJYDJ初始化批量交易登记表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	   
    */ 

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;        
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitPLKSFMX
组件名称: 初始化税收批量扣税费明细表
组件功能: 
  初始化税收批量扣税费明细表
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
批量交易登记表	tips_ssplksfmx

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月10日
修改日期: 2014年12月20日DCI改造
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPLKSFMX(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
      SDB_TIPS_PLJYDJ stPljydj;
      SDB_TIPS_SSPLKSFMX stPlksfmx;
      char sZwrq[8+1];
      char sPljylsh[8+1];
      char sPayBkCode[12+1];
      char sDfzh[20+1];
      char sDqdh[10+1];
      char sJgdh[10+1];
      char sTaxPayCode[20+1];
      int iCount;
    EXEC SQL END   DECLARE SECTION;    
    */
    int i,j;
    int iflag;
    int iret;
    char sBuf[256];
    char sXmlNodePath[40+1+20];
    char sTaxInfoPath[256];
    char sPayment3102[10240];
    FILE *fp;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_PLJYDJ stPljydj;
      SDB_TIPS_SSPLKSFMX stPlksfmx;
      SDB_TIPS_TAXTYPEMX stTaxtypemx;
      char sZwrq[8+1];
      char sPljylsh[8+1];
      char sPayBkCode[12+1];
      char sDfzh[20+1];
      char sDqdh[10+1];
      char sJgdh[10+1];
      char sTaxPayCode[20+1];
      char sPayAcct2[32+1]; /*add by liurj 20180713*/
      int iCount;
      int iTaxTypeNum=0;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));  
    COMP_GETPARSEPARAS(1, sBuf, "帐务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2, sBuf, "批量交易流水号")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));  

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxInfoPath, 0x00, sizeof(sTaxInfoPath));
    COMP_GETPARSEPARAS(3, sBuf, "存入税票路径")
    pstrcopy(sTaxInfoPath, sBuf, sizeof(sTaxInfoPath));
        
    LOG(LM_STD,Fmtmsg("初始化税收批量扣税费明细表开始..."),"INFO")
    LOG(LM_STD,Fmtmsg("帐务日期[%s], 批量流水号[%s],税票路径[%s]", 
        sZwrq, sPljylsh, sTaxInfoPath),"INFO")  

    /*判断批量扣税费明细表中是否已有记录*/
    /* add dci 20141103 */
    iCount=0;
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplksfmx\
    	 where zwrq='%s' and pljylsh='%s'",sZwrq,sPljylsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24277, "initPlksfmx查询批量扣税费明细记录出错");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx查询批量扣税费明细记录出错"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end dci 20141103 */
    /* mod dci 20141103
    iCount =0;
    EXEC SQL SELECT count(*) INTO :iCount
    	 FROM  tips_ssplksfmx
         WHERE zwrq = :sZwrq 
           AND pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24277, "initPlksfmx查询批量扣税费明细记录出错");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx查询批量扣税费明细记录出错"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    */
    if (iCount > 0)
    {
         fpub_SetMsg(lXmlhandle, 24278, "initPlksfmx校验错,批量扣税费明细表已有数据");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx校验错,批量扣税费明细表已有数据"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;	    	 
    }
    
    /* 查询批量交易登记表信息 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj\
    	 where zwrq='%s' and pljylsh='%s'",sZwrq,sPljylsh);     
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*   	      	
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);
		*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24279, "initPlksfmx查询批量交易登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end add dci 20141103 */
    /* mod dci 20141103 
    memset(&stPljydj, 0x00, sizeof(stPljydj));
    EXEC SQL SELECT * INTO :stPljydj
             FROM   tips_pljydj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
         fpub_SetMsg(lXmlhandle, 24279, "initPlksfmx查询批量交易登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    */
		LOG(LM_STD,Fmtmsg("sZwrq[%s]sPljylsh[%s]...",sZwrq,sPljylsh),fpub_GetCompname(lXmlhandle))
    /*根据付款行行号从商业银行清算行登记表查询贷方帐号*/
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    pstrcopy(sPayBkCode, stPljydj.paybkcode, sizeof(sPayBkCode));
    memset(sDfzh, 0x00, sizeof(sDfzh));
    memset(sDqdh, 0x00, sizeof(sDqdh));
    memset(sJgdh, 0x00, sizeof(sJgdh));
    
    /* add dci 20141103 */
    /* 获取贷方账号 */
	/*
    memset( sSql1, 0x00, sizeof( sSql1 ) );       
    snprintf( sSql1, sizeof(sSql1), "select dfzh from tips_qshdj\
    	 where paybkcode='%s'",sPayBkCode);   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          	    	
    iRet =DBSelectToMultiVar(sErrmsg, sSql1, sDfzh);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx查询贷方账号失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx查询贷方账号失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx清算行信息未初始化");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx清算行信息未初始化"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }* del by sunpj 20170706/
    /* add dci 20141103 */
        
    /* mod dci 20141103
    EXEC SQL SELECT dfzh, dqdh, jgdh 
         INTO :sDfzh, :sDqdh, :sJgdh 
         FROM tips_qshdj 
         WHERE paybkcode = :sPayBkCode;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx查询贷方账号失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx查询贷方账号失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }
    if ( SQLNOTFOUND_TIPS )
    {
         fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx清算行信息未初始化");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx清算行信息未初始化"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }
    */
    
    trim(sDfzh);
    trim(sDqdh);
    trim(sJgdh);
    /* 开始事务 
    EXEC SQL BEGIN WORK ; */
       
    memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    pstrcopy(stPlksfmx.zwrq, stPljydj.zwrq, sizeof(stPlksfmx.zwrq)); /* 帐务日期 */
    pstrcopy(stPlksfmx.pljydm, stPljydj.pljydm, sizeof(stPlksfmx.pljydm));/* 批量交易代码 */
    pstrcopy(stPlksfmx.pljylsh, stPljydj.pljylsh, sizeof(stPlksfmx.pljylsh));/* 批量交易流水号 */
    pstrcopy(stPlksfmx.plpch, "00000", sizeof(stPlksfmx.plpch));/* 批量批次号 */
    stPlksfmx.clcs = 0 ;/* 处理次数 */
    pstrcopy(stPlksfmx.workdate, stPljydj.workdate, sizeof(stPlksfmx.workdate));/* 工作日期 */
    pstrcopy(stPlksfmx.chkdate, stPljydj.chkdate, sizeof(stPlksfmx.chkdate));/* 工作日期 */ 
    pstrcopy(stPlksfmx.entrustdate, stPljydj.entrustdate, sizeof(stPlksfmx.entrustdate));/* 委托日期 */
    pstrcopy(stPlksfmx.taxorgcode, stPljydj.orgcode, sizeof(stPlksfmx.taxorgcode));/* 征收机关代码 */
    pstrcopy(stPlksfmx.packno, stPljydj.packno, sizeof(stPlksfmx.packno));/* 包流水号 */
    pstrcopy(stPlksfmx.paybkcode, stPljydj.paybkcode, sizeof(stPlksfmx.paybkcode));/* 付款行行号 */
    /*pstrcopy(stPlksfmx.dqdh, sDqdh, sizeof(stPlksfmx.dqdh));*/ /* 地区代号 mod 20150720 */
    /*pstrcopy(stPlksfmx.jgdh, sJgdh, sizeof(stPlksfmx.jgdh));*/ /* 机构代号 mod 20150720 */
    /* 回执期限 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ReturnTerm",sBuf)
    stPlksfmx.returnterm=atoi(sBuf);
    pstrcopy(stPlksfmx.payeebankno, stPljydj.payeebankno, sizeof(stPlksfmx.payeebankno));
    stPlksfmx.czbd[0]='0';/* 操作步点 */
    stPlksfmx.qsbz[0]='0';/* 清算标志 0-未清算 */
    pstrcopy(stPlksfmx.kzbz, "00000000", sizeof(stPlksfmx.kzbz));
    LOG(LM_STD,Fmtmsg("帐务日期[%s], 批量交易代码[%s], 批量交易流水号[%s]", 
        stPlksfmx.zwrq, stPlksfmx.pljydm, stPlksfmx.pljylsh),"INFO")
    LOG(LM_STD,Fmtmsg("委托日期[%s], 征收机关代码[%s], 包流水号[%s]", 
        stPlksfmx.entrustdate, stPlksfmx.taxorgcode, stPlksfmx.packno),"INFO") 
    
    for ( i=1; i<= stPljydj.allnum; i++ )
    {
        iflag=0;
        stPlksfmx.plmxxh=0;
        memset(stPlksfmx.trano, 0x00, sizeof(stPlksfmx.trano));
        memset(stPlksfmx.protocolno, 0x00, sizeof(stPlksfmx.protocolno));
        memset(stPlksfmx.dfzh, 0x00, sizeof(stPlksfmx.dfzh));
        memset(stPlksfmx.payopbkcode, 0x00, sizeof(stPlksfmx.payopbkcode));
        memset(stPlksfmx.payacct, 0x00, sizeof(stPlksfmx.payacct));
        memset(stPlksfmx.handorgname, 0x00, sizeof(stPlksfmx.handorgname));
        memset(stPlksfmx.taxvouno, 0x00, sizeof(stPlksfmx.taxvouno));
        stPlksfmx.jyje=0.00;
        memset(stPlksfmx.xym, 0x00, sizeof(stPlksfmx.xym));
        memset(stPlksfmx.xyxx, 0x00, sizeof(stPlksfmx.xyxx));
        memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
        stPlksfmx.czbd[0]='0';
        memset(stPlksfmx.taxpaycode, 0x00, sizeof(stPlksfmx.taxpaycode));
        memset(stPlksfmx.spxx, 0x00, sizeof(stPlksfmx.spxx));
        
        /* add by tuql 20090909 */
        memset(stPlksfmx.dqdh, 0x00, sizeof(stPlksfmx.dqdh));
        memset(stPlksfmx.jgdh, 0x00, sizeof(stPlksfmx.jgdh));
        
        /* 批量明细序号, 应该获取综合前置流水号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        iret=prv_GenSerino(lXmlhandle, sBuf, sizeof(sBuf));
        if ( iret <= 0 )
        {        
            LOG(LM_STD,Fmtmsg("获取新的综合前置流水号失败[%d]", iret),"ERROR")   
            iflag = -1;
            break;	
        }
        stPlksfmx.plmxxh=iret;
        LOG(LM_STD,Fmtmsg("批量明细序号[%d]",stPlksfmx.plmxxh),"INFO")
        /* 交易流水号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TraNo", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.trano, sBuf, sizeof(stPlksfmx.trano));
        /* 协议书号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/ProtocolNo", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.protocolno, sBuf, sizeof(stPlksfmx.protocolno));  
                      
        /* 付款开户行行号 
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/PayOpBkCode", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.payopbkcode, sBuf, sizeof(stPlksfmx.payopbkcode)); del by sunpj 20170706*/
        /* 付款账号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/PayAcct", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.payacct, sBuf, sizeof(stPlksfmx.payacct));
        /* 缴款单位名称 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/HandOrgName", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.handorgname, sBuf, sizeof(stPlksfmx.handorgname));
        /* 纳税人名称 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxPayName", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.taxpayname, sBuf, sizeof(stPlksfmx.taxpayname));
        /* 税票号码 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxVouNo", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.taxvouno, sBuf, sizeof(stPlksfmx.taxvouno));
        /* 交易金额 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TraAmt", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        stPlksfmx.jyje=atof(sBuf);
        /* 响应码 */
        stPlksfmx.xym[0]='0';
        /* 响应信息 */
        strcpy(stPlksfmx.xyxx, "批量落地成功");
        trim(stPlksfmx.xyxx);
        
        /* 检查委托关系并获得纳税人编码、实扣账号 mod by tuql 20090909 增加返回地区代号及机构代号*/
        LOG(LM_STD,Fmtmsg("调用委托关系检查函数开始......"),"INFO")
        memset(sPayAcct2, 0x00, sizeof(sPayAcct2));
        
        iret = prv_tips_ChkWtgx( stPlksfmx.protocolno, 
                                 stPlksfmx.payacct, 
                                 sTaxPayCode,
                                 stPlksfmx.dqdh,
                                 stPlksfmx.jgdh,
                                 stPlksfmx.payopbkcode,
                                 sPayAcct2
                                );
        LOG(LM_STD,Fmtmsg("付款行行号[%s], 清算行号[%s], 机构代号[%s]", 
        stPlksfmx.paybkcode, sPayBkCode, stPlksfmx.jgdh),"INFO")     
        if ( iret < 0 )
        {   
            iflag = -2;
            LOG(LM_STD,Fmtmsg("调委托关系检查函数失败[%d]", iret),"ERROR")
            break;                
        }
        if ( iret == 1 )
        {
            pstrcopy(stPlksfmx.xym, "24009", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"三方协议不存在",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='8';/* 操作步点 8-委托关系不存在 */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -3;
                break;	
    				}
            /* end dci 20141103 */
            
            /* mod dci 20141103 
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -3;
                break;	
            }
            */
            continue ;            
        }                                
        if ( iret == 2 )
        {
            pstrcopy(stPlksfmx.xym, "24009", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"三方协议状态异常",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='8';/* 操作步点 8-委托关系异常 */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -4;
                break;	
    				}
    				/* end add dci 20141103 */
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -4;
                break;	
            }
            */
            continue ;            
        }
        if ( iret == 3 )
        {
            pstrcopy(stPlksfmx.xym, "24009", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"三方协议未验证",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='8';/* 操作步点 8-三方协议未验证 */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					    	
    					LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -5;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -5;
                break;	
            }
            */
            continue ;            
        } 
        trim(sTaxPayCode);

        /* 将委托关系登记表中的付款人账号2写入相应结点,并更改明细表中付款人账号为付款人账号2 add by liurj 20180713*/
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/PayAcct2", i);
        COMP_SOFTSETXML(sXmlNodePath, sPayAcct2)
        memset(stPlksfmx.payacct, 0x00, sizeof(stPlksfmx.payacct));
        pstrcopy(stPlksfmx.payacct, sPayAcct2, sizeof(stPlksfmx.payacct));
            
		/* 获取副清算行行号、贷方账号 */
		trim(stPlksfmx.payopbkcode);
		memset( sSql1, 0x00, sizeof( sSql1 ) );       
		snprintf( sSql1, sizeof(sSql1), "select dfzh from tips_qshdj\
		                 where paybkcode='%s'",stPlksfmx.payopbkcode);   
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          	    	
		iRet =DBSelectToMultiVar(sErrmsg, sSql1, &sDfzh);
		if ( iRet < 0 )
		{
		    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
		    
		    fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx查询贷方账号失败");
		    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		    LOG(LM_STD, Fmtmsg("initPlksfmx查询贷方账号失败"), fpub_GetCompname(lXmlhandle))	
		    return COMPRET_FAIL ; 
		}
		if ( iRet == 0 )
		{
		    LOG(LM_STD, Fmtmsg("initPlksfmx清算行信息未初始化"), fpub_GetCompname(lXmlhandle))	
		}
		
        /* 将委托关系登记表中的纳税人编号写入相应结点 */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        sprintf(sBuf,"/tips/MSG/Payment3102|%d/TaxPayCode", i);
        COMP_SOFTSETXML(sXmlNodePath, sTaxPayCode)
        pstrcopy(stPlksfmx.taxpaycode, sTaxPayCode, sizeof(stPlksfmx.taxpaycode));
        
        
        
        /* 税票信息 */
        memset(sPayment3102, 0x00, sizeof(sPayment3102));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        sprintf(sXmlNodePath,"/tips/MSG/Payment3102|%d",i);
        if ( (iret=xml_ExportXMLString(lXmlhandle,sPayment3102,sizeof(sPayment3102),sXmlNodePath,1 )) == -1 )
        {
            pstrcopy(stPlksfmx.xym, "24282", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"获取税票信息失败",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='2';/* 操作步点 2-被作废 */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					    	
    					LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -6;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103 
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -6;
                break;	
            }
            */
            continue ;                            
        }
        
        /* 把税票信息存放到文件中去 */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));/* 存放的文件名 */
        snprintf(sXmlNodePath, sizeof(sXmlNodePath), "spxx_%s_%d",stPlksfmx.zwrq, stPlksfmx.plmxxh);
        trim(sXmlNodePath);
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%s%s", sTaxInfoPath, sXmlNodePath);
        fp = fopen(sBuf, "w+");
        if ( fp==NULL )
        {
            LOG(LM_STD,Fmtmsg("保存税票信息失败 文件全路径[%s]", sBuf),"ERROR")   
            LOG(LM_STD,Fmtmsg("出错信息[%s]", strerror(errno)),"ERROR")   
            pstrcopy(stPlksfmx.xym, "24283", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"打开税票信息文件失败",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='2';/* 操作步点 2-被作废 */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -7;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -7;
                break;	
            }
            */
            continue ;              
        }
        fprintf(fp, "%s\n", sPayment3102); 
        fclose(fp);
        pstrcopy(stPlksfmx.spxx, sXmlNodePath, sizeof(stPlksfmx.spxx));                
        /* 贷方账号 */
        pstrcopy(stPlksfmx.dfzh, sDfzh, sizeof(stPlksfmx.dfzh));/* 贷方帐号 */
        if( strlen(stPlksfmx.dfzh)==0)
        {
            pstrcopy(stPlksfmx.xym, "24281", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"支付行贷方账号为空",sizeof(stPlksfmx.xyxx));    
            stPlksfmx.czbd[0]='2';/* 操作步点 2-被作废 */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -8;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -8;
                break;	
            }
            */
            continue ;
        }
        
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    		if( iRet < 0 )
    		{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				/* DCIRollback();   */
    	
    				LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
            iflag = -9;
            break;	
    		}
    				/* end add dci 20141103 */
        /* mod dci 20141103
        EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {        
            LOG(LM_STD,Fmtmsg("插入批量扣税费表出错 交易流水号[%s]", stPlksfmx.trano),"ERROR")   
            iflag = -9;
            break;	
        }
        */
        
        /*插入完每条批量明细数据之后，插入该条明细数据的税种明细，东莞个性化20171028*/
        /*该条明细的税种条数*/
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeNum", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        iTaxTypeNum=atoi(sBuf);
        
        for(j=1; j<=iTaxTypeNum; j++)
        {        
        		memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
        		pstrcopy(stTaxtypemx.jyrq, stPlksfmx.zwrq, sizeof(stTaxtypemx.jyrq));
        		//pstrcopy(stTaxtypemx.jylsh, itoa(stPlksfmx.plmxxh), sizeof(stTaxtypemx.jylsh));
        		sprintf(stTaxtypemx.jylsh, "%s", itoa(stPlksfmx.plmxxh));
        		pstrcopy(stTaxtypemx.spxx, stPlksfmx.spxx, sizeof(stTaxtypemx.spxx));
        		
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/ProjectId", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
        		
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxTypeName", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));
        		
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxStartDate", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
            
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxEndDate", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));            

        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxTypeAmt", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            stTaxtypemx.taxtypeamt = atof(sBuf);
            
            memset( sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                
                fpub_SetMsg(lXmlhandle, 24327, "插入税种明细表失败");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                iflag = -9;
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入税种明细表失败"),fpub_GetCompname(lXmlhandle))
                break;
            }                		
        }
        /*该条批量明细的税种明细插入完成*/
        
    }    
    if ( iflag < 0 )
    {
        /* EXEC SQL ROLLBACK WORK;*/
        LOG(LM_STD,Fmtmsg("  -->批量扣税费数据落地失败,ret[%d]..",iflag),"ERROR"); 
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("批量扣税费数据落地失败"));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
   
    /*全局提交 */
    /*iRet =DCICommit();
    if ( iRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	      
       	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("数据库操作失败"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */

    /* mod dci 20141103
    /* EXEC SQL COMMIT WORK;    
    if ( SQLERR )  
    {
       LOG(LM_STD,Fmtmsg("提交数据库失败sqlcode[%d]",sqlca.sqlcode),"ERROR");
       /* EXEC SQL ROLLBACK WORK; 
       fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("数据库操作失败"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPRET_FAIL;    	
    }*/
            
    LOG(LM_STD,Fmtmsg("批量扣税费数据落地成功"),"INFO"); 
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC; 
}    
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdPLJYDJ
组件名称: 更新批量交易登记表状态
组件功能: 
  更新批量交易登记表状态
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
批量交易登记表	tips_pljydj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月10日
修改日期: 2014年12月20日DCI改造
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdPLJYDJ(HXMLTREE lXmlhandle)
{
	
    int iParas;
    char sBuf[200+1];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
    EXEC SQL END   DECLARE SECTION;
    */
  	
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		SDB_TIPS_PLJYDJ stPljydj;		
		int iRet=0;
/* end add dci 20141103 */
  	
  	iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}

    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(6);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "账务日期")
    pstrcopy( stPljydj.zwrq, sBuf, sizeof(stPljydj.zwrq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "批量交易流水号")
    pstrcopy( stPljydj.pljylsh, sBuf, sizeof(stPljydj.pljylsh));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "操作步点")
    pstrcopy( stPljydj.czbd, sBuf, sizeof(stPljydj.czbd));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "完成标志")
    pstrcopy( stPljydj.wcbz, sBuf, sizeof(stPljydj.wcbz));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(5, sBuf, "响应码")
    pstrcopy( stPljydj.xym, sBuf, sizeof(stPljydj.xym));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(6, sBuf, "响应信息")
    pstrcopy( stPljydj.xyxx, sBuf, sizeof(stPljydj.xyxx));       
    
    /*22.处理结束日期*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate",sBuf)
    pstrcopy(stPljydj.cljsrq,sBuf,sizeof(stPljydj.cljsrq));
    /*23.处理结束时间*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime",sBuf)
    pstrcopy(stPljydj.cljssj,sBuf,sizeof(stPljydj.cljssj));
    
    /* add dci 20141103 */
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    		set	czbd   ='%s',\
    				wcbz   ='%s',\
    				xym    ='%s',\
    				xyxx   ='%s',\
    				cljsrq ='%s',\
    				cljssj ='%s' \
    			where zwrq='%s' and pljylsh='%s'" \
    			,stPljydj.czbd  \
    			,stPljydj.wcbz  \
    			,stPljydj.xym   \
    			,stPljydj.xyxx  \
          ,stPljydj.cljsrq\
          ,stPljydj.cljssj,stPljydj.zwrq,stPljydj.pljylsh);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                 	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
        fpub_SetMsg(lXmlhandle, 24285, "更新批量登记表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ更新批量登记表失败zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24285, "更新失败-->批量登记表记录未找到");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ更新批量登记表失败zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    iRet =DCICommit();
    /* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
    if ( iRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */
    /* end add dci 20141103 */
    /* mod dci 20141103
    EXEC SQL UPDATE tips_pljydj
    	   SET czbd = :stPljydj.czbd,
    	       wcbz = :stPljydj.wcbz,
    	       xym = :stPljydj.xym,
    	       xyxx = :stPljydj.xyxx,
    	       cljsrq = :stPljydj.cljsrq,
    	       cljssj = :stPljydj.cljssj
         WHERE zwrq = :stPljydj.zwrq 
           AND pljylsh = :stPljydj.pljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "更新批量登记表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ更新批量登记表失败zwrq[%s],pljylsh[%s],sqlcode[%d]", stPljydj.zwrq,stPljydj.pljylsh,sqlca.sqlcode),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND_TIPS )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "更新失败-->批量登记表记录未找到");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ更新批量登记表失败zwrq[%s],pljylsh[%s],sqlcode[%d]", stPljydj.zwrq,stPljydj.pljylsh,sqlca.sqlcode),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    */	   
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_ChkPLJYDJ
组件名称: 检查批量交易操作步点状态
组件功能: 
  检查批量交易操作步点状态
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  1                  记录重复
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
批量交易登记表	tips_pljydj


项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月10日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_ChkPLJYDJ(HXMLTREE lXmlhandle)
{	
    int iParas;
    char sBuf[200+1];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        char sCzbd[30],sWcbz[30];
    EXEC SQL END   DECLARE SECTION;
  	*/
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		SDB_TIPS_PLJYDJ stPljydj;
        char sCzbd[30],sWcbz[30];
		int iRet=0;
/* end add dci 20141103 */
  	
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "账务日期")
    pstrcopy( stPljydj.zwrq, sBuf, sizeof(stPljydj.zwrq));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "批量交易流水号")
    pstrcopy( stPljydj.pljylsh, sBuf, sizeof(stPljydj.pljylsh));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "检验步点")
    pstrcopy( stPljydj.czbd, sBuf, sizeof(stPljydj.czbd));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT czbd,wcbz FROM tips_pljydj\
    	where zwrq='%s' and pljylsh='%s'",stPljydj.zwrq, stPljydj.pljylsh);     
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sCzbd, &sWcbz);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24271, "查询批量交易表出错");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("chkPLJYDJ查询批量交易表出错zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
            fpub_GetCompname(lXmlhandle))	
        
    }
    if ( iRet == 0 )
    {
        /*如果没有找到，则属于未初始化阶段，0.mod by tuql 20090614 由0更改为1*/
    		pstrcopy(sCzbd,"1",sizeof(sCzbd));
    }

    /* end dci 20141103 */
    
    /* mod dci 20141103
    memset(sCzbd,0,sizeof(sCzbd));
    EXEC SQL SELECT czbd,wcbz INTO :sCzbd,:sWcbz
    	   FROM  tips_pljydj
         WHERE zwrq = :stPljydj.zwrq 
           AND pljylsh = :stPljydj.pljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )	
    {
        fpub_SetMsg(lXmlhandle, 24271, "查询批量交易表出错");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("chkPLJYDJ查询批量交易表出错zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
            fpub_GetCompname(lXmlhandle))	
    }	   
    if ( SQLNOTFOUND_TIPS )
    {
    	/*如果没有找到，则属于未初始化阶段，0.mod by tuql 20090614 由0更改为1
    	pstrcopy(sCzbd,"1",sizeof(sCzbd));
    }
    */
    
    trim(sCzbd);
    trim(sWcbz);
    if (strncmp(sCzbd,stPljydj.czbd,1) != 0)
    {
        fpub_SetMsg(lXmlhandle, 24287,Fmtmsg("操作步点不符"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("校验操作步点不一致zwrq[%s],pljylsh[%s],chkCzbd[%s],dbCzbd[%s]", 
            stPljydj.zwrq,stPljydj.pljylsh,stPljydj.czbd,sCzbd),
        fpub_GetCompname(lXmlhandle))	
    }
    
    if (sWcbz[0]=='9')
    {
        fpub_SetMsg(lXmlhandle, 24288, "本批量交易正在处理中");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("本批量交易正在处理中zwrq[%s],pljylsh[%s],sWcbz[%s]", 
            stPljydj.zwrq,stPljydj.pljylsh,sWcbz),
        fpub_GetCompname(lXmlhandle))	
    }
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitPLPCDJ
组件名称: 初始化批量批次登记表
  
组件参数: 
序号 参数名称   资源类别       缺省值   是否可空  参数说明


组件结果状态: 
  结果状态码         结果说明
  0                  正常
  -1　　　　　　　　 失败　　
日志信息: 
  日志级别           日志宏

主要操作库表:
  表名                     操作
 gapsywk:tips_pljydj       更新
 gapsywk:tips_ssplksfmx    更新
 gapsywk:tips_ssplpcdj     更新

使用限制:
   本组件只针对第一次批量提交的主机文件生成
   一个批量只有一个文件(或一个主体文件，其余为辅助文件)的情况；	

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPLPCDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPlpch[5+1];
        char sPljylsh[8+1];
        int iZbs=0;
        int iCount=0;
        double dZje=0.0;
    EXEC SQL END   DECLARE SECTION;	
    */
    SDB_GENFILE stGenZjFile;
    char sBuf[256];
    char sTmpBuf[256];
    char sFile_short[60+1];
    char sFile_ret[60+1];
    char sNode_zbs[100];
    int  i;
    int  iret;
    int  iflag;
    int  j;
  
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPlpch[5+1];
        char sPljylsh[8+1];
        int iZbs=0;
        int iCount=0;
        double dZje=0.0;
        char cZbs[16+1];
        char cZje[32+1];
		int iRet=0;
/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
  
    COMP_PARACOUNTCHK(6);
  
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(1,sBuf,"帐务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2,sBuf,"批量交易流水号")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    trim(sPljylsh);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    COMP_GETPARSEPARAS(3,sBuf,"批量批次号")
    pstrcopy(sPlpch, sBuf, sizeof(sPlpch));
    trim(sPlpch);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile_short, 0x00, sizeof(sFile_short));
    COMP_GETPARSEPARAS(4,sBuf,"主机入帐文件名")
    pstrcopy(sFile_short, sBuf, sizeof(sFile_short));
    trim(sFile_short);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile_ret, 0x00, sizeof(sFile_ret));
    COMP_GETPARSEPARAS(5,sBuf,"主机返回文件名")
    pstrcopy(sFile_ret, sBuf, sizeof(sFile_ret));
    trim(sFile_ret);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sNode_zbs, 0x00, sizeof(sNode_zbs));
    COMP_GETPARSEPARAS(6,sBuf,"返回批次总笔数")
    pstrcopy(sNode_zbs, sBuf, sizeof(sNode_zbs));
    trim(sNode_zbs);
    
    LOG(LM_STD,Fmtmsg("账务日期[%s],批量交易流水号[%s],批量批次号[%s]",sZwrq,sPljylsh,sPlpch),"INFO");
    LOG(LM_STD,Fmtmsg("请求主机文件名[%s],主机返回文件名[%s]",sFile_short, sFile_ret),"INFO");

		/* add dci 20141103 */
		memset(&stPljydj, 0x00, sizeof(stPljydj));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT * FROM tips_pljydj\
    	where zwrq='%s' and pljylsh='%s'",sZwrq, sPljylsh);  
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*   
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24271, "查询批量登记记录出错");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ查询批量登记记录出错"),
               fpub_GetCompname(lXmlhandle))	
        
    }
    /* end dci 20141103 */
    
		/* mod dci 20141103 
    memset(&stPljydj, 0x00, sizeof(stPljydj));  
    EXEC SQL SELECT * INTO :stPljydj 
         FROM  tips_pljydj 
         WHERE zwrq = :sZwrq 
           AND pljylsh = :sPljylsh ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ) ) 
    {
           fpub_SetMsg(lXmlhandle, 24271, "查询批量登记记录出错");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ查询批量登记记录出错"),
               fpub_GetCompname(lXmlhandle))	
    }	 
    */
  
  /*状态检查 因为是第一个批次，所以必须满足*/
  /*1 pljydj表中的pczbs必须为0 */
  if (stPljydj.pczbs > 0)
  {
  	 fpub_SetMsg(lXmlhandle, 24293, "批次校验异常，已有批次记录");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ状态校验异常，已有批次记录"),
         fpub_GetCompname(lXmlhandle))	
  }
   /*2 plpcdj表中没有对应的批次记录 */
  iCount = 0;
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
  snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_ssplpcdj \
  where zwrq='%s' and pljylsh='%s'",sZwrq , sPljylsh);   	
  iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
  if ( iRet < 0 )
  {
  	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
		
		fpub_SetMsg(lXmlhandle, 24294, "查询批量批次登记表失败");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ查询批量批次登记表失败"),
         fpub_GetCompname(lXmlhandle))	
        
	}
   
  /* end add dci 20141103 */
  /* mod dci 20141103
  EXEC SQL SELECT count(*) INTO :iCount 
       FROM  tips_ssplpcdj
       WHERE zwrq = :sZwrq 
         AND pljylsh = :sPljylsh ;
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
  if ( SQLERR ) 
  {
     fpub_SetMsg(lXmlhandle, 24294, "查询批量批次登记表失败");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ查询批量批次登记表失败"),
         fpub_GetCompname(lXmlhandle))	
  }	 
  */
    
  if ( iCount > 0 )
  {
     fpub_SetMsg(lXmlhandle, 24293, "批次校验异常，已有批次记录");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,
         Fmtmsg("initPLPCDJ批次表中已有记录，异常icount[%d]",iCount),
         fpub_GetCompname(lXmlhandle))	  	
  }
  /*3 plksfmx表中没有状态是6-上送主机，等待结果返回的记录*/
  iCount = 0;  
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
  snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_ssplksfmx \
  where zwrq='%s' and pljylsh='%s' and czbd = '6'",sZwrq , sPljylsh);   	
  iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
  if ( iRet < 0 )
  {
  	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
		
		fpub_SetMsg(lXmlhandle, 24277, "查询批量扣税费明细表失败");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ查询批量扣税费明细表失败"),
         fpub_GetCompname(lXmlhandle))	
        
	}
  /* end dci 20141103 */
  
  /* mod dci 20141103  
  EXEC SQL SELECT count(*) INTO :iCount 
       FROM  tips_ssplksfmx
       WHERE zwrq = :sZwrq 
         AND pljydm = :sPljylsh 
         AND czbd = '6';
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
  if ( SQLERR ) 
  {
     fpub_SetMsg(lXmlhandle, 24277, "查询批量扣税费明细表失败");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ查询批量扣税费明细表失败"),
         fpub_GetCompname(lXmlhandle))	
  }	   
  */
  
  if ( iCount > 0 )
  {
     fpub_SetMsg(lXmlhandle, 16999, "扣税费明细表中已有记录上送主机，异常");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,
        Fmtmsg("initPLPCDJ扣税费明细表中已有记录上送主机，异常icount[%d]",iCount),
        fpub_GetCompname(lXmlhandle))	  	
  }  

  /* 开始事务 
  EXEC SQL BEGIN WORK ;   */      
  
  /*插入批量批次登记信息*/
  memset(&stPlpcdj,0x00,sizeof(stPlpcdj));
  pstrcopy(stPlpcdj.zwrq, stPljydj.zwrq, sizeof(stPlpcdj.zwrq)); 
  pstrcopy(stPlpcdj.pljydm, stPljydj.pljydm, sizeof(stPlpcdj.pljydm)); 
  pstrcopy(stPlpcdj.pljylsh, stPljydj.pljylsh, sizeof(stPlpcdj.pljylsh));
  pstrcopy(stPlpcdj.plpch, sPlpch, sizeof(stPlpcdj.plpch));     
  stPlpcdj.pclsh = stPljydj.pczbs + 1;     /* 批次流水号 =1 */ 
  stPlpcdj.ykbs=0;
  stPlpcdj.ykje=0.00;
  stPlpcdj.skbs=0;
  stPlpcdj.skje=0.00;
  stPlpcdj.zjsbbs=0;
  pstrcopy(stPlpcdj.xym, "00", sizeof(stPlpcdj.xym));
  pstrcopy(stPlpcdj.xyxx, "数据准备完成,本批次开始处理", sizeof(stPlpcdj.xyxx));  
  stPlpcdj.czbd[0] = '1';                    /* 批量交易初始化 */
    
  memset(sBuf, 0x00, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/sysdate",sBuf);
  pstrcopy(stPlpcdj.clqsrq, sBuf, sizeof(stPlpcdj.clqsrq)); /*处理起始日期*/
  pstrcopy(stPlpcdj.cljsrq, sBuf, sizeof(stPlpcdj.cljsrq)); /*处理结束日期*/
  
  memset(sBuf, 0x00, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/systime",sBuf);
  pstrcopy(stPlpcdj.clqssj, sBuf, sizeof(stPlpcdj.clqssj));/*处理起始时间*/
  pstrcopy(stPlpcdj.cljssj, sBuf, sizeof(stPlpcdj.cljssj));/*处理结束时间*/
  pstrcopy(stPlpcdj.qqzjwjm, sFile_short, sizeof(stPlpcdj.qqzjwjm));/* 请求主机文件名 */
  pstrcopy(stPlpcdj.zjjgwjm, sFile_ret, sizeof(stPlpcdj.zjjgwjm));/* 主机结果文件名 */

	/* add dci 20141103 */
	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_ssplpcdj", SD_TIPS_SSPLPCDJ, NUMELE(SD_TIPS_SSPLPCDJ), &stPlpcdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	/* DCIRollback(); */
    	
        fpub_SetMsg(lXmlhandle, 24296, "插入批量批次表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ插入批量批次表失败"),
            fpub_GetCompname(lXmlhandle))		
    }

	/* end dci 20141103 */
	/* mod dci 20141103 
  EXEC SQL INSERT INTO tips_ssplpcdj VALUES ( :stPlpcdj );
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
  if ( SQLERR )
  {
  	    /* EXEC SQL ROLLBACK WORK; 
        fpub_SetMsg(lXmlhandle, 24296, "插入批量批次表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ插入批量批次表失败"),
            fpub_GetCompname(lXmlhandle))		
  }	     
  */
  
  /* 更新批量扣税费明细表中准备入账的记录 */
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx set plpch = '%s',clcs  = clcs + 1 \
    where zwrq='%s' and pljylsh='%s' and czbd = '0'",sPlpch, sZwrq , sPljylsh);   	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24297, "更新批量扣税费明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ更新批量扣税费明细表失败"),
            fpub_GetCompname(lXmlhandle))		     
    }
  /* end add dci 20141103 */
  
  /* mod dci 20141103
  EXEC SQL UPDATE tips_ssplksfmx
       SET plpch = :sPlpch,
           clcs  = clcs + 1
       WHERE zwrq = :sZwrq 
         AND pljylsh = :sPljylsh
         AND czbd ='0';              /*操作步点 0 入账准备
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
  if ( SQLERR ) 
  {
  	   /*  EXEC SQL ROLLBACK WORK; 
        fpub_SetMsg(lXmlhandle, 24297, "更新批量扣税费明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ更新批量扣税费明细表失败"),
            fpub_GetCompname(lXmlhandle))		
  }
  */
  /*统计本批次需要处理的总笔数、总金额*/
  iZbs = 0;
  dZje = 0.0;  
  
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
	snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    	where zwrq='%s' and pljylsh='%s' and plpch = '%s'",sZwrq , sPljylsh, sPlpch);  
  LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs, &cZje);
    iZbs=atoi(cZbs);
    dZje=atof(cZje);

    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
          fpub_SetMsg(lXmlhandle, 24298, "统计批次应扣笔数、应扣金额失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("initPLPCDJ统计批次应扣笔数、应扣金额失败"),
            fpub_GetCompname(lXmlhandle))		     
    }

  /* end add dci 20141103 */
  /* mod dci 20141103
   
  EXEC SQL SELECT COUNT(*), nvl(SUM(jyje), 0.00) INTO :iZbs,:dZje 
       FROM tips_ssplksfmx
       WHERE zwrq = :sZwrq 
        AND  pljylsh = :sPljylsh 
        AND  plpch = :sPlpch;     
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");       
  if ( SQLERR )
  {
  	 /*   EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24298, "统计批次应扣笔数、应扣金额失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("initPLPCDJ统计批次应扣笔数、应扣金额失败"),
            fpub_GetCompname(lXmlhandle))		
  }	
  */    
  LOG(LM_STD,Fmtmsg("当前批次需处理的总应扣笔数[%d],总应扣金额[%.2f]",iZbs,dZje),"INFO");

  /*修改批次登记信息*/
  stPlpcdj.ykbs = iZbs;
  stPlpcdj.ykje = dZje;
  
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplpcdj set ykbs = %d,ykje=%f \
    where zwrq='%s' and pljylsh='%s' and plpch = '%s'", stPlpcdj.ykbs, stPlpcdj.ykje, sZwrq , sPljylsh,sPlpch);   	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet ==0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "更新批量批次表失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ更新批量批次表失败"),
          fpub_GetCompname(lXmlhandle))	  
    }
  /* end add dci 20141103 */
  /* mod dci 20141103 
  EXEC SQL UPDATE tips_ssplpcdj 
       SET ykbs  = :stPlpcdj.ykbs,
           ykje  = :stPlpcdj.ykje           
      WHERE zwrq  = :sZwrq 
        AND pljylsh = :sPljylsh
        AND plpch = :sPlpch ;
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");   
  if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
  {
  	 /*  EXEC SQL ROLLBACK WORK;
      fpub_SetMsg(lXmlhandle, 24299, "更新批量批次表失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ更新批量批次表失败"),
          fpub_GetCompname(lXmlhandle))		
  }	
  */     
  
  /*修改批量交易登记信息*/
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj set pczbs = pczbs + 1 \
    where zwrq='%s' and pljylsh='%s' ", sZwrq , sPljylsh);   	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet ==0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "更新批量登记信息失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ更新批量登记信息失败"),
          fpub_GetCompname(lXmlhandle))		
    }
  /* end dci 20141103 */
  /* mod dci 20141103 
  EXEC SQL UPDATE tips_pljydj 
       SET pczbs = pczbs + 1         /*批次总笔数 与批次登记表中的pclsh同步
       WHERE zwrq = :sZwrq 
         AND pljylsh =:sPljylsh;
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");   
  if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
  {
  	/*  EXEC SQL ROLLBACK WORK;
      fpub_SetMsg(lXmlhandle, 24285, "更新批量登记信息失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ更新批量登记信息失败"),
          fpub_GetCompname(lXmlhandle))		
   }
   */
   
   /*非全局事务，内部提交
   EXEC SQL COMMIT WORK;
   if ( SQLERR )  
   {
      LOG(LM_STD,Fmtmsg("提交数据库失败sqlcode=[%d]",sqlca.sqlcode),"ERROR");
      EXEC SQL ROLLBACK WORK;
      fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("数据库操作失败"));
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;    	
   } */ 
   
   /*写回总笔数*/
   memset(sBuf, 0x00, sizeof(sBuf));
   sprintf(sBuf,"%ld",iZbs);
   COMP_HARDSETXML(sNode_zbs, sBuf);

   /*写回总金额 mod by tuql 20090908 */
   memset(sBuf, 0x00, sizeof(sBuf));
   sprintf(sBuf,"%15.2f",dZje);
   COMP_HARDSETXML("/tips/pczje", sBuf);
   
   LOG(LM_STD,Fmtmsg("初始化批量批次结束..."),"INFO");
   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   return COMPRET_FAIL;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdPLPCDJ
组件名称: 更新批量批次登记表状态
组件功能: 
  更新批量批次登记表状态
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  1                  记录重复
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
批量交易登记表	tips_ssplpcdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdPLPCDJ(HXMLTREE lXmlhandle)
{
	
    int iParas;
    char sBuf[200+1];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
    EXEC SQL END   DECLARE SECTION;
  	*/
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		SDB_TIPS_SSPLPCDJ stPlpcdj;
		int iRet=0;
/* end add dci 20141103 */
  	
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPlpcdj, 0x00, sizeof(stPlpcdj));
    COMP_PARACOUNTCHK(6);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "账务日期")
    pstrcopy( stPlpcdj.zwrq, sBuf, sizeof(stPlpcdj.zwrq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "批量交易流水号")
    pstrcopy( stPlpcdj.pljylsh, sBuf, sizeof(stPlpcdj.pljylsh));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "批量批次号")
    pstrcopy( stPlpcdj.plpch, sBuf, sizeof(stPlpcdj.plpch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "操作步点")
    pstrcopy( stPlpcdj.czbd, sBuf, sizeof(stPlpcdj.czbd));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(5, sBuf, "响应码")
    pstrcopy( stPlpcdj.xym, sBuf, sizeof(stPlpcdj.xym));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(6, sBuf, "响应信息")
    pstrcopy( stPlpcdj.xyxx, sBuf, sizeof(stPlpcdj.xyxx));
       
    
    /*20.处理结束日期*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate",sBuf)
    pstrcopy(stPlpcdj.cljsrq,sBuf,sizeof(stPlpcdj.cljsrq));
    /*21.处理结束时间*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime",sBuf)
    pstrcopy(stPlpcdj.cljssj,sBuf,sizeof(stPlpcdj.cljssj));
     
    /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplpcdj \
    set czbd = '%s' \
       ,xym   ='%s' \
       ,xyxx  ='%s' \
       ,cljsrq='%s' \
       ,cljssj='%s' \
    		where zwrq='%s' and pljylsh='%s' and plpch='%s'", \
    		stPlpcdj.czbd,            \
        stPlpcdj.xym,             \
        stPlpcdj.xyxx,            \
        stPlpcdj.cljsrq,          \
        stPlpcdj.cljssj,\
   			stPlpcdj.zwrq , stPlpcdj.pljylsh, stPlpcdj.plpch);   	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet ==0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "更新批量批次表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("updPLPCDJ更新批量批次表失败"),
            fpub_GetCompname(lXmlhandle))	
    }
  /* end dci 20141103 */
  	/* mod dci 20141103
    EXEC SQL UPDATE tips_ssplpcdj
         SET czbd = :stPlpcdj.czbd,
             xym = :stPlpcdj.xym,
             xyxx = :stPlpcdj.xyxx,
             cljsrq = :stPlpcdj.cljsrq,
             cljssj = :stPlpcdj.cljssj
        WHERE zwrq = :stPlpcdj.zwrq 
          AND pljylsh = :stPlpcdj.pljylsh
          AND plpch = :stPlpcdj.plpch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if ((SQLERR) || (SQLNOTFOUND_TIPS) )	
    {
        fpub_SetMsg(lXmlhandle, 24299, "更新批量批次表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("updPLPCDJ更新批量批次表失败"),
            fpub_GetCompname(lXmlhandle))	
    }	   
    */

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_GenQQZJWJ
组件名称:生成主机入帐文件

  
组件参数: 
序号 参数名称   资源类别       缺省值   是否可空  参数说明


组件结果状态: 
  结果状态码         结果说明
  0                  正常
  -1　　　　　　　　 失败　　
日志信息: 
  日志级别           日志宏

主要操作库表:
  表名                     操作
 gapsywk:tips_pljydj       更新
 gapsywk:tips_ssplksfmx    更新
 gapsywk:tips_ssplpcdj     更新

使用限制:
   主机入帐文件生成

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月12日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_GenQQZJWJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
    /* add dci 20141103
    EXEC SQL END   DECLARE SECTION;	*/
    FILE *fp1;
    SDB_GENFILE stGenZjFile;
    char sBuf[254];
    char sFile[100];
    char sTmpBuf[254];
    char sResIcxp[30];
    char sResIcxpH[30];
    int  i;
    int  iret;
    int  iflag;
    int  j;
    ICXPCFG SBwpz;
  
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
  
    COMP_PARACOUNTCHK(5);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(1,sBuf,"帐务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2,sBuf,"批量交易流水号")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    COMP_GETPARSEPARAS(3,sBuf,"批量批次号")
    pstrcopy(sPlpch, sBuf, sizeof(sPlpch));
      
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile, 0x00, sizeof(sFile));
    COMP_GETPARSEPARAS(4,sBuf,"请求主机文件名")
    pstrcopy(sFile, sBuf, sizeof(sFile));
    trim(sFile);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sResIcxp, 0x00, sizeof(sResIcxp));
    COMP_GETPARSEPARAS(5,sBuf,"ICXP配置名称")
    pstrcopy(sResIcxp, sBuf, sizeof(sResIcxp));
    
    LOG(LM_STD,Fmtmsg("帐务日期[%s],批量交易流水号[%s],批量批次号[%s],生成文件[%s]....",
        sZwrq,sPljylsh,sPlpch,sFile),"INFO");

    /*校验ICXP报文配置资源是否存在*/
    if( fpub_GetIcxpCfg(lXmlhandle ,(ICXPCFG *)&SBwpz,sResIcxp)!= MID_SYS_SUCC ) 
    {
        fpub_SetMsg(lXmlhandle, 36003, "配置资源不存在");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("ICXP报文配置资源不存在[%s]", sResIcxp),"ERROR");
        return COMPRET_FAIL;
    }
    
    /*先建文件,校验*/
    fp1 = fopen(sFile,"w+");
    if ( fp1 == NULL )
    {
        fpub_SetMsg(lXmlhandle,36004,"打开文件失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("打开文件失败errinfo=[%s]",strerror(errno)),"ERROR");
        return COMPRET_FAIL;
    }
  
    memset(&stGenZjFile, 0x00, sizeof(stGenZjFile));
    stGenZjFile.lXmlhandle = lXmlhandle;
    pstrcopy(stGenZjFile.zwrq, sZwrq, sizeof(stGenZjFile.zwrq));
    pstrcopy(stGenZjFile.pljylsh, sPljylsh, sizeof(stGenZjFile.pljylsh));
    pstrcopy(stGenZjFile.plpch, sPlpch, sizeof(stGenZjFile.plpch));
    pstrcopy(stGenZjFile.resicxp, sResIcxp, sizeof(stGenZjFile.resicxp));
    stGenZjFile.fp = fp1;
    
    /* 生成入帐文件 */
    /* fprintf(fp1, "%s\n", FILE_BEGIN); */
    iret=prv_tips_GenZjFile( stGenZjFile );
    if( iret < 0 )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fclose(fp1);
        return COMPRET_FAIL;         
    }
    /* fprintf(fp1, "%s\n", FILE_END);  */
    fclose(fp1);
     
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_ClZJJGWJ
组件名称: 处理主机结果文件
组件功能: 处理主机结果文件

  
组件参数: 
序号 参数名称   资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  正常
  -1　　　　　　　　 失败　　

主要操作库表:
  表名                     操作
 gapsywk:tips_pljydj       更新
 gapsywk:tips_ssplksfmx    更新
 gapsywk:tips_ssplpcdj     更新

使用限制:
   处理主机结果文件处理

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月12日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_ClZJJGWJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
        char sSysdate[8+1];
        char sSystime[6+1];
        char sResHxxtResp[30+1];/*核心响应码配置   
        int iClsbbs=0;/* 平台处理失败笔数 
        int iZjsbbs = 0;/* 主机处理异常失败笔数
        int iZbsSucc = 0;
        double dZjeSucc = 0.00;
        char sFileErr[256];
        char sBuf[256];
        char sZjxym[18+1];/* add by tuql 20090908 
    EXEC SQL END   DECLARE SECTION;	
    */
    FILE *fp1, *fperr;
    char sFile[256];
    char sLine[1024];
    char sResIcxp[30+1];
    int  i;
    int  iret;
    int  iflag;
    ICXPCFG SBwpz;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/                  
    char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
    SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
        char sSysdate[8+1];
        char sSystime[6+1];
        char sResHxxtResp[30+1];/*核心响应码配置 */  
        int iClsbbs=0;/* 平台处理失败笔数 */
        int iZjsbbs = 0;/* 主机处理异常失败笔数 */
        int iZbsSucc = 0;
        double dZjeSucc = 0.00;
        char cClsbbs[16+1];/* 平台处理失败笔数 */
        char cZjsbbs[16+1];/* 主机处理异常失败笔数 */
        char cZbsSucc[16+1];
        char cZjeSucc[32+1];
        char sFileErr[256];
        char sBuf[256];
        char sZjxym[18+1];/* add by tuql 20090908 */
		int iRet=0;
/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
  
    COMP_PARACOUNTCHK(7);
      
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));  
    COMP_GETPARSEPARAS(1,sBuf,"帐务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2,sBuf,"批量交易流水号")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    COMP_GETPARSEPARAS(3,sBuf,"批量批次号")
    pstrcopy(sPlpch, sBuf, sizeof(sPlpch));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile, 0x00, sizeof(sFile));
    COMP_GETPARSEPARAS(4,sBuf,"入帐结果文件名")
    pstrcopy(sFile, sBuf, sizeof(sFile));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileErr, 0x00, sizeof(sFileErr));
    COMP_GETPARSEPARAS(5,sBuf,"错误信息文件")
    pstrcopy(sFileErr, sBuf, sizeof(sFileErr));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sResIcxp, 0x00, sizeof(sResIcxp));
    COMP_GETPARSEPARAS(6,sBuf,"入账文件格式配置")
    pstrcopy(sResIcxp, sBuf, sizeof(sResIcxp));
  
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sResHxxtResp, 0x00, sizeof(sResHxxtResp));  
    COMP_GETPARSEPARAS(7,sBuf,"核心响应资源名称")
    pstrcopy(sResHxxtResp, sBuf, sizeof(sResHxxtResp));
    
    LOG(LM_STD,Fmtmsg("处理主机结果文件开始，核心响应资源名称[%s]入帐结果文件名[%s]....",sResHxxtResp, sFile),"INFO");
    LOG(LM_STD,Fmtmsg("帐务日期[%s],批量交易代码[%s],批量批次号[%s]",sZwrq,sPljylsh,sPlpch),"INFO");
    
    memset(sSysdate, 0x00, sizeof(sSysdate));
    memset(sSystime, 0x00, sizeof(sSystime));
    COMP_SOFTGETXML("/sys/sysdate", sSysdate);
    COMP_SOFTGETXML("/sys/systime", sSystime);
    	     
    /*查询批量交易登记信息*/
    memset(&stPljydj, 0x00, sizeof(stPljydj));
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj \
    where zwrq='%s' and pljylsh='%s'",sZwrq, sPljylsh);  
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24271, "查询批量交易登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ查询批量交易信息失败"),
            fpub_GetCompname(lXmlhandle))	     
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT * INTO :stPljydj
             FROM   tips_pljydj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
        fpub_SetMsg(lXmlhandle, 24271, "查询批量交易登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ查询批量交易信息失败"),
            fpub_GetCompname(lXmlhandle))	
    }
    */
    
    /*查询批次登记信息*/
    memset(&stPlpcdj, 0x00, sizeof(stPlpcdj));
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_ssplpcdj \
    	where zwrq='%s' and pljylsh='%s' and plpch='%s'",sZwrq, sPljylsh,sPlpch);   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( sSql1, SD_TIPS_SSPLPCDJ, NUMELE(SD_TIPS_SSPLPCDJ), &stPlpcdj);
    /*  	
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPlpcdj.zwrq,&stPlpcdj.pljydm,&stPlpcdj.pljylsh,\
    	&stPlpcdj.plpch,&stPlpcdj.pclsh,&stPlpcdj.ykbs,&stPlpcdj.ykje,&stPlpcdj.skbs,&stPlpcdj.skje,\
    	&stPlpcdj.zjsbbs,&stPlpcdj.qqzjwjm,&stPlpcdj.zjjgwjm,&stPlpcdj.xym,&stPlpcdj.xyxx,&stPlpcdj.czbd,\
    	&stPlpcdj.clqsrq,&stPlpcdj.clqssj,&stPlpcdj.cljsrq,&stPlpcdj.cljssj,&stPlpcdj.byzd );*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24294, "查询批量批次登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ClZJJGWJ查询批量批次登记表失败"),
            fpub_GetCompname(lXmlhandle))	   
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT * INTO :stPlpcdj
             FROM   tips_ssplpcdj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh
               AND  plpch = :sPlpch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
        fpub_SetMsg(lXmlhandle, 24294, "查询批量批次登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ClZJJGWJ查询批量批次登记表失败"),
            fpub_GetCompname(lXmlhandle))	
    }
    */   
           
    fp1=fopen(sFile,"r");
    if (fp1==NULL)
    {
        fpub_SetMsg(lXmlhandle, 36004, "打开文件出错");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ打开主机结果文件出错errinfo=[%s]",strerror(errno)),
            fpub_GetCompname(lXmlhandle))	
    }
  
    /** 文件头尾检查 **/
    /* mod by leejn 20141231 
    fseek(fp1,-4L,2);
    memset(sLine, 0x00, sizeof(sLine));
    if (fgets(sLine,sizeof(sLine),fp1) != NULL)
    {
        if (strncmp(sLine,"END",3) != 0)    输入文件的最后一行为：END
        {
            fclose(fp1);
            fpub_SetMsg(lXmlhandle, 36007, "校验文件尾错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,
                Fmtmsg("ClZJJGWJ校验主机结果文件尾错sline[%s]",sLine),
                fpub_GetCompname(lXmlhandle))	
        }
    }else
    {
        fclose(fp1);
        fpub_SetMsg(lXmlhandle, 36008, "文件为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ主机结果文件为空,无文件尾"),
            fpub_GetCompname(lXmlhandle))	
    }

    fseek(fp1,0L,0);   指针移至文件头 
    memset(sLine, 0, sizeof(sLine));
    if (fgets(sLine,sizeof(sLine),fp1)!=NULL)
    {
        if (strncmp(sLine,"BEGIN",5) != 0)  输入文件第一行内容应为：BEGIN
        {
            fclose(fp1);
            fpub_SetMsg(lXmlhandle, 36009, "校验文件头错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ校验文件头错"),
                fpub_GetCompname(lXmlhandle))	
        }
    }
    else
    {
        fclose(fp1);
        fpub_SetMsg(lXmlhandle, 36008, "文件为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ主机结果文件为空,无文件头"),
            fpub_GetCompname(lXmlhandle))	
    }
    */

    /*打开错误信息文件*/
    fperr=fopen(sFileErr, "a+");
    if (fperr==NULL)
    {
       fclose(fp1);
       fpub_SetMsg(lXmlhandle, 36004, "打开文件出错");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ打开主机结果失败文件出错errinfo[%s]",strerror(errno)),
           fpub_GetCompname(lXmlhandle))	
    }
    fprintf(fperr, "主机结果文件处理失败信息:帐务日期[%s]批量交易流水号[%s]批次号[%s]文件名[%s]\n", sZwrq,sPljylsh,sPlpch,sFile);
      	
      	
    /* 开始事务  
    EXEC SQL BEGIN WORK ;*/ 
      
    /*文件体处理*/
    for (iflag=0,i=1; ;i++)
    {
        memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
        memset(sLine, 0x00, sizeof(sLine));
        if (fgets(sLine,sizeof(sLine),fp1)	== NULL)
           break;
        if (strncmp(sLine, "END", 3) == 0)
        {   
           break;      
        }   
        sLine[strlen(sLine)-1]=0;   /*去除最后一个换行符*/
        iret = 0 ;
        iret=SBATCH_FuncICXPUPKG(lXmlhandle,sResIcxp,sLine,strlen(sLine));
        if (iret < 0)
        { 
           iflag = -1; 
           break; 
        }	

        /*在此进行本地数据表的更新*/             
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/qzlsh", sBuf);
        stPlksfmx.plmxxh = atoi(sBuf); /* 批量明细序号 */        
				
				/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select * from tips_ssplksfmx \
    			where zwrq='%s' and pljylsh='%s' and plpch='%s' and plmxxh=%d",\
    			sZwrq, sPljylsh,sPlpch, stPlksfmx.plmxxh);     	
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    		iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
    		/*
    		iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPlksfmx.zwrq,&stPlksfmx.pljydm,&stPlksfmx.pljylsh,\
    		 &stPlksfmx.plpch,&stPlksfmx.plmxxh,&stPlksfmx.clcs,&stPlksfmx.workdate,&stPlksfmx.entrustdate,\
    		 &stPlksfmx.taxorgcode,&stPlksfmx.packno,&stPlksfmx.returnterm,&stPlksfmx.chkdate,&stPlksfmx.chkacctord,\
    		 &stPlksfmx.trano,&stPlksfmx.protocolno,&stPlksfmx.dfzh,&stPlksfmx.paybkcode,&stPlksfmx.payopbkcode,\
    		 &stPlksfmx.payacct,&stPlksfmx.payeebankno,&stPlksfmx.handorgname,&stPlksfmx.taxvouno,&stPlksfmx.jyje,\
    		 &stPlksfmx.sxf,&stPlksfmx.zhye,&stPlksfmx.je2,&stPlksfmx.zjrq,&stPlksfmx.zjsj,&stPlksfmx.zjlsh,\
    		 &stPlksfmx.dqdh,&stPlksfmx.jgdh,&stPlksfmx.jygy,&stPlksfmx.zddh,&stPlksfmx.czbd,&stPlksfmx.qsbz,\
    		 &stPlksfmx.xym,&stPlksfmx.xyxx,&stPlksfmx.kzbz,&stPlksfmx.taxpaycode,&stPlksfmx.taxpayname,&stPlksfmx.spxx,\
    		 &stPlksfmx.byzd );  */  		
    		if ( iRet < 0 || iRet == 0)
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        		LOG(LM_STD,Fmtmsg("ZjjgwjCl查询失败plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -3;  
            break; 
    		}
    		/* end add dci 20141103 */
    
				/* mod dci 20141103 
        EXEC SQL SELECT * INTO :stPlksfmx
             FROM tips_ssplksfmx
             WHERE zwrq  = :sZwrq
              AND pljylsh = :sPljylsh
              AND plpch = :sPlpch 
              AND plmxxh = :stPlksfmx.plmxxh;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        { 
            LOG(LM_STD,Fmtmsg("ZjjgwjCl查询失败plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -3;  
            break; 
        }
        */
        
        memset(sBuf, 0x00, sizeof(sBuf));     
        COMP_SOFTGETXML("/hxxt/zjjgwj/zczh", sBuf);
        pstrcopy(stPlksfmx.payacct, sBuf, sizeof(stPlksfmx.payacct)); /* 扣款帐号 */
        
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/jyje", sBuf);
        stPlksfmx.jyje = atof(sBuf);   /* 应扣金额 */
        
        /* add by tuql 20090908 主机响应码可能超出5位 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sZjxym, 0x00, sizeof(sZjxym));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjxym", sBuf);
        /*pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym)); 响应码*/
        pstrcopy(sZjxym, sBuf, sizeof(sZjxym)); /*响应码*/
        trim(sZjxym);

        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zhye", sBuf);
        stPlksfmx.zhye=atof(sBuf); /*账户余额*/

        memset(sBuf, 0x00, sizeof(sBuf));     
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjrq", sBuf);
        pstrcopy(stPlksfmx.zjrq, sBuf, sizeof(stPlksfmx.zjrq)); /* 主机日期 */
        
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjsj", sBuf);
        pstrcopy(stPlksfmx.zjsj, sBuf, sizeof(stPlksfmx.zjsj));  /* 主机时间 */
        
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjlsh", sBuf);
        pstrcopy(stPlksfmx.zjlsh, sBuf, sizeof(stPlksfmx.zjlsh)); /*主机流水号*/
        trim(stPlksfmx.zjlsh);       

        /* 获取响应信息 */
        memset(stPlksfmx.xyxx, 0x00, sizeof(stPlksfmx.xyxx));
        memset(sBuf, 0x00, sizeof(sBuf));

        /* add dci 20141103 */
        /* 产品中无此表，使用中可根据核心响应码、响应信息定义
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT orespcode, respmsg FROM trc_respcodecfg\
    			WHERE resname='%s' AND irespcode ='%s'",sResHxxtResp,sZjxym);     
    		iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sResHxxtResp, &sZjxym);
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        	LOG(LM_STD,Fmtmsg("ZjjgwjCl处理失败plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -5;  
            break;
        
    		}
    		if ( iRet == 0)
    		{
        	 把更新出错的记录写到批量更新失败文件中 
            pstrcopy(stPlksfmx.xyxx, "未知错误", sizeof(stPlksfmx.xyxx));
            pstrcopy(stPlksfmx.xym, "99004", sizeof(stPlksfmx.xym));      	
        }else
        {
            trim(stPlksfmx.xyxx);
            memset(stPlksfmx.xym, 0x00, sizeof(stPlksfmx.xym));
            trim(sBuf);
            pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym));            
        } 	
        */
        /* end add dci 20141103 */
        
        /* mod dci 20141103
        EXEC SQL SELECT orespcode, respmsg INTO :sBuf, :stPlksfmx.xyxx
             FROM trc_respcodecfg
             WHERE resname = :sResHxxtResp
               AND irespcode=:sZjxym;/* mod by tuql 20090908 AND irespcode=:stPlksfmx.xym; 
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        { 
            LOG(LM_STD,Fmtmsg("ZjjgwjCl处理失败plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -5;  
            break; 
        } 
        
        if ( SQLNOTFOUND_TIPS )
        {
        	 把更新出错的记录写到批量更新失败文件中 
            pstrcopy(stPlksfmx.xyxx, "未知错误", sizeof(stPlksfmx.xyxx));
            pstrcopy(stPlksfmx.xym, "99004", sizeof(stPlksfmx.xym));      	
        }else
        {
            trim(stPlksfmx.xyxx);
            memset(stPlksfmx.xym, 0x00, sizeof(stPlksfmx.xym));
            trim(sBuf);
            pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym));            
        } 
        */                  

        /* 响应码为零，即扣款成功,反之为失败 mod by tuql 20090908*/
		/*将主机响应码转换为平台内部批量明细交易状态标志*/
		memset(sBuf, 0x00, sizeof(sBuf));
		LOG(LM_DEBUG, Fmtmsg("begin fpub_GetRespInValue src[%s]", sZjxym), "INFO");
		fpub_GetRespOutValue(lXmlhandle, "xym_tips_hxxt2tips", sZjxym, 1, sBuf, sizeof(sBuf)-1);
		LOG(LM_DEBUG,  Fmtmsg("end fpub_GetRespInValue dst[%s]", sBuf), "INFO");
		trim(sBuf);
		pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym));
		COMP_SOFTGETXML(XMLNM_RESPMSG, stPlksfmx.xyxx);
		if (atoi(stPlksfmx.xym) == 90000)
        {
            stPlksfmx.czbd[0]='7';
        }else
        {
            stPlksfmx.czbd[0]='8';
        } 
		
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    		set	xym   ='%s',\
    				xyxx  ='%s',\
    				jyje  =%0.2f,\
    				czbd  ='%s',\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s' \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'\
    			  AND plpch  ='%s'\
    			  AND plmxxh =%d\
    			  AND payacct='%s'",\
    			  stPlksfmx.xym ,stPlksfmx.xyxx,stPlksfmx.jyje,stPlksfmx.czbd,stPlksfmx.zjrq\
          ,stPlksfmx.zjsj,stPlksfmx.zjlsh,sZwrq,sPljylsh,sPlpch,stPlksfmx.plmxxh,stPlksfmx.payacct);
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")       	
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		LOG(LM_STD,Fmtmsg("ZjjgwjCl处理失败plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -2;  
            break; 
    		}
    		if( iRet == 0)
    		{
    		 		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        		/* 把更新出错的记录写到批量更新失败文件中 */
            iClsbbs++;
            LOG(LM_STD,Fmtmsg("更新失败,本地数据未找到对应记录[%ld],[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            fprintf(fperr, "%s|更新失败,本地数据未找到对应记录\n", sLine); 
            continue;      	
    		}	
        /* end add dci 20141103 */
        /* mod dci 20141103        
        EXEC SQL UPDATE tips_ssplksfmx 
            SET  xym      = :stPlksfmx.xym,
                 xyxx     = :stPlksfmx.xyxx,
                 jyje     = :stPlksfmx.jyje,   
                 czbd     = :stPlksfmx.czbd,
                 zjrq     = :stPlksfmx.zjrq,
                 zjsj     = :stPlksfmx.zjsj,   
                 zjlsh    = :stPlksfmx.zjlsh  
            WHERE zwrq  = :sZwrq
              AND pljylsh = :sPljylsh
              AND plpch = :sPlpch 
              AND plmxxh = :stPlksfmx.plmxxh 
              AND payacct  = :stPlksfmx.payacct;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        { 
            LOG(LM_STD,Fmtmsg("ZjjgwjCl处理失败plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -2;  
            break; 
        }
        
        if ( SQLNOTFOUND_TIPS )
        {
        	/* 把更新出错的记录写到批量更新失败文件中 
            iClsbbs++;
            LOG(LM_STD,Fmtmsg("更新失败,本地数据未找到对应记录[%ld],[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            fprintf(fperr, "%s|更新失败,本地数据未找到对应记录\n", sLine); 
            continue;      	
        } 
        */
        /* 如主机扣款成功,则把税票信息登记到tips_pzsj表中去 */
        if(atoi(stPlksfmx.xym)==90000)
        {
            iret = prv_tips_InitPZSJ_pl(lXmlhandle, stPlksfmx); 
            if ( iret != 0 )
            {
                LOG(LM_STD,Fmtmsg("ZjjgwjCl新增凭证信息失败plmxxh[%ld][%s],ret=[%d]", stPlksfmx.plmxxh, stPlksfmx.payacct, iret),"ERROR");
                iflag = -4;  
                continue;            
            }
        }    
        
        
    }
    fclose(fp1);
    fclose(fperr);
	
    if (iflag < 0)
    {
        /* EXEC SQL ROLLBACK WORK; */
        fpub_SetMsg(lXmlhandle, 36009, "更新主机结果信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("ClZJJGWJ更新主机结果信息失败iflag[%d]",iflag),
            fpub_GetCompname(lXmlhandle))	
    }  
    
    /*一次更新本批次所有响应信息
    EXEC SQL UPDATE tips_ssplksfmx SET tips_ssplksfmx.xyxx = 
         (
            SELECT respmsg FROM trc_respcodecfg b
            WHERE tips_ssplksfmx.xym = b.orespcode
              AND b.resname = :sResHxxtResp
         )
         WHERE zwrq = :sZwrq
           AND pljylsh = :sPljylsh
           AND plpch = :sPlpch ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 36008, "更新主机响应码出错");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ更新主机响应码出错"),
           fpub_GetCompname(lXmlhandle))		
    }*/
    
    /* mod by tuql 20090909 将36012响应码改成99004 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    		SET  xym      = '99004',             \
    			xyxx     = '主机没返回批扣结果',\
    			czbd     = '8'    				       \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'\
    			  AND plpch  ='%s'\
    			  AND czbd = '6'",\
    			  sZwrq ,sPljylsh ,sPlpch);               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
       	fpub_SetMsg(lXmlhandle, 36009, "更新主机结果信息失败");
       	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ更新主机结果信息失败"),
           fpub_GetCompname(lXmlhandle))		
    }    
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_ssplksfmx 
        SET  xym      = '99004',
             xyxx     = '主机没返回批扣结果',
             czbd     = '8'
        WHERE zwrq  = :sZwrq
          AND pljylsh = :sPljylsh
          AND plpch = :sPlpch 
          AND czbd = '6';     
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")    
    if ( SQLERR )
    {
       /* EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 36009, "更新主机结果信息失败");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ更新主机结果信息失败"),
           fpub_GetCompname(lXmlhandle))		
    }
    */    	       
    /*统计 实扣笔数、实扣金额*/
    iZbsSucc = 0;
    dZjeSucc = 0.00;
    /* add dci 20141103 */
  	memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    	where zwrq='%s' and pljylsh='%s' and plpch = '%s' AND czbd = '7'",sZwrq , sPljylsh, sPlpch);  
	LOG(LM_DEBUG, Fmtmsg("sql [%s]", sSql1), "INFO");
	iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,cZbsSucc, cZjeSucc);
    iZbsSucc=atoi(cZbsSucc);
    dZjeSucc=atof(cZjeSucc);

    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24277, "查询批量扣税费明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ统计实扣笔数、金额失败"),
            fpub_GetCompname(lXmlhandle))			     
    }

  	/* end add dci 20141103 */
    /* mod dci 20141103
    EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00) INTO :iZbsSucc,:dZjeSucc
    	 FROM tips_ssplksfmx
        WHERE zwrq  = :sZwrq 
          AND pljylsh = :sPljylsh
          AND plpch = :sPlpch
          AND czbd = '7';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        /* EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24277, "查询批量扣税费明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ统计实扣笔数、金额失败"),
            fpub_GetCompname(lXmlhandle))				
    }	   
  	*/
  	
    /*统计 主机处理异常失败笔数......*/
    iZjsbbs = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM tips_ssplksfmx \
    	where zwrq='%s' and pljylsh='%s' and plpch = '%s' AND xym in ('-9999','-9998','1644')",\
    	sZwrq , sPljylsh, sPlpch);  
    iRet = DBSelectToVar(sErrmsg,&iZjsbbs, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24277, "查询批量扣税费明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ统计主机处理异常失败笔数失败"),
            fpub_GetCompname(lXmlhandle))				     
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103  
    EXEC SQL SELECT COUNT(*) INTO :iZjsbbs
    	 FROM tips_ssplksfmx
        WHERE zwrq  = :sZwrq 
          AND pljylsh = :sPljylsh
          AND plpch = :sPlpch
          AND xym in ('-9999','-9998','1644') ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        /* EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24277, "查询批量扣税费明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ统计主机处理异常失败笔数失败"),
            fpub_GetCompname(lXmlhandle))				
    }	       
    */
    
  	/*更新批次登记表信息*/
  	/* add dci 20141103 */
  	memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_ssplpcdj \
    		SET skbs  = skbs + %d,\
           	skje  = skje + %f,\
           	cljsrq = '%s',    \
           	cljssj = '%s',    \
           	zjsbbs = %d    \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'\
    			  AND plpch  ='%s'",\
    				iZbsSucc \
    			,dZjeSucc\
    			,sSysdate  \
          ,sSystime \
          ,iZjsbbs  \
    			,sZwrq    \
    			,sPljylsh \
    			,sPlpch   );               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "更新批量批次表失败");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ更新批量批次表失败"),
           fpub_GetCompname(lXmlhandle))				
    }    
  /* end dci 20141103 */
  /* mod dci 20141103
  EXEC SQL UPDATE tips_ssplpcdj 
       SET skbs  = skbs + :iZbsSucc,     /* 实扣笔数 
           skje  = skje + :dZjeSucc,     /* 实扣金额 
           cljsrq = :sSysdate,          /* 处理结束日期 
           cljssj = :sSystime,          /* 处理结束时间 
           zjsbbs = :iZjsbbs           /* 主机处理失败笔数 
      WHERE zwrq  = :sZwrq 
        AND pljylsh = :sPljylsh
        AND plpch = :sPlpch ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
    {
      /*  EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 24299, "更新批量批次表失败");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ更新批量批次表失败"),
           fpub_GetCompname(lXmlhandle))		
    }	
    */     
    
    /*更新批量登记表信息*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    		SET rzzbs  = rzzbs + %d, \
           rzzje  = rzzje + %f,  \
           cljsrq = '%s',   \
           cljssj = '%s'    \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'",\
    				iZbsSucc \
    			,dZjeSucc\
    			,sSysdate  \
          ,sSystime \
          ,sZwrq    \
    			,sPljylsh );               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "更新批量批次表失败");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ更新批量批次表失败"),
           fpub_GetCompname(lXmlhandle))				
    } 
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_pljydj 
         SET rzzbs  = rzzbs + :iZbsSucc,     /* 入帐总笔数        
             rzzje  = rzzje + :dZjeSucc,     /* 入帐总金额                 
             cljsrq = :sSysdate,            /* 处理结束日期    
             cljssj = :sSystime            /* 处理结束时间 
        WHERE zwrq  = :sZwrq  
          AND pljylsh = :sPljylsh ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
    {
       /*  EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24285, "更新批量登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ更新批量登记表失败"),
            fpub_GetCompname(lXmlhandle))	
    }
    */
 	     
    /*非全局事务，内部提交
    EXEC SQL COMMIT WORK;
    if ( SQLERR )  
    {
       LOG(LM_STD,Fmtmsg("数据库提交失败sqlcode=[%d]",sqlca.sqlcode),"ERROR");
       EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("数据库操作失败"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPRET_FAIL;    	
    }*/
    
    LOG(LM_STD,Fmtmsg("处理主机结果文件结束...."),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_GenPLKSFHZ
组件名称: 生成批量扣税费回执
组件功能: 生成批量扣税费回执

  
组件参数: 
序号 参数名称   资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  正常
  -1　　　　　　　　 失败　　

主要操作库表:
    表名              操作
    tips_ssplksfmx    查询


使用限制:
   处理主机结果文件处理

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月12日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_GenPLKSFHZ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sTraNo[8+1];/* 交易流水号 
        double dSkje;
        char sTaxVouNo[18+1];/* 税票号码 
        char sXym[5+1];/* 响应码 
        char sXyxx[60+1];/* 响应信息 
    EXEC SQL END   DECLARE SECTION;
    */
  	
    char sBuf[256];
    char sTmpBuf[256];
  	int i;
  	int iflag;
  	
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;
		SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sTraNo[8+1];/* 交易流水号 */
        double dSkje;
        char sTaxVouNo[18+1];/* 税票号码 */
        char sXym[5+1];/* 响应码 */
        char sXyxx[60+1];/* 响应信息 */
		int iRet=0;
/* end add dci 20141103 */
  	
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "帐务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));  
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2, sBuf, "批量交易流水号")
    pstrcopy( sPljylsh, sBuf, sizeof(sPljylsh));
    
    LOG(LM_STD,Fmtmsg("生成批量扣税费回执开始处理...帐务日期[%s]批量交易流水号[%s]",
        sZwrq, sPljylsh),"INFO");
        
    /*查询批量交易登记信息*/
    memset(&stPljydj, 0x00, sizeof(stPljydj));
    /* add dci 20141103 */
    
    /* end dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj \
    	where zwrq='%s' and pljylsh='%s'",sZwrq , sPljylsh); 	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*   
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);*/
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24271, "查询批量交易登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ查询批量交易信息失败"),
            fpub_GetCompname(lXmlhandle))	    
    }

    /* mod dci 20141103 
    EXEC SQL SELECT * INTO :stPljydj
             FROM   tips_pljydj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
        fpub_SetMsg(lXmlhandle, 24271, "查询批量交易登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ查询批量交易信息失败"),
            fpub_GetCompname(lXmlhandle))	
    }    
    */
    
    /* 设置批量头数据项 */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/PayBkCode",stPljydj.paybkcode);/* 付款行行号 */
    COMP_HARDSETXML("/tips/PayBkCode",stPljydj.paybkcode);
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/EntrustDate",sZwrq);/* tips专用前置帐务日期 */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/PackNo",sPljylsh); /*返回的包流水号*/
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/OriTaxOrgCode",stPljydj.orgcode);/* 原征收机关代码 */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/OriEntrustDate",stPljydj.entrustdate);/* 原委托日期 */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/OriPackNo",stPljydj.packno);/* 原包流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%d",stPljydj.allnum);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/AllNum",sBuf);/* 总笔数 */
    
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%.2f",stPljydj.allamt);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/AllAmt",sBuf);/* 总金额 */
    
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%d",stPljydj.rzzbs);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/SuccNum",sBuf);/* 成功笔数 */
    
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%.2f",stPljydj.rzzje);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/SuccAmt",sBuf);/* 成功金额 */ 
    
    memset(sBuf, 0x00, sizeof(sBuf));
    if (   stPljydj.wcbz[0]=='0'
         ||stPljydj.wcbz[0]=='1'
         ||stPljydj.wcbz[0]=='2'
         ||stPljydj.wcbz[0]=='9'
        )
       strcpy(sBuf,"90000");
    else
       strcpy(sBuf,"24020");
  
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/Result",sBuf);
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/AddWord",trim(stPljydj.xyxx));
    
    /* 设置业务明细块 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT trano, jyje, taxvouno, xym, xyxx FROM  tips_ssplksfmx\
    	WHERE zwrq = '%s' and pljylsh = '%s' ORDER BY plmxxh",sZwrq,sPljylsh); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("OPEN CUR sSql1[%s]...",sSql1),"INFO")   
    if (DCIExecute(cur) == -1)
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
    EXEC SQL DECLARE cur_ksfmx_plhz CURSOR for 
        SELECT trano, jyje, taxvouno, xym, xyxx
        FROM  tips_ssplksfmx 
        WHERE zwrq = :sZwrq 
         AND  pljylsh = :sPljylsh
         ORDER BY plmxxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_ksfmx_plhz;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ksfmx_plhz",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,36001, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ打开cur_ksfmx_plhz游标失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*开始循环*/ 
    /* add dci 20141103 */
    
		for (i=1,iflag=0;;i++)
    {
    		    	
        memset(sTraNo, 0x00, sizeof(sTraNo));
        memset(sTaxVouNo, 0x00, sizeof(sTaxVouNo));
        memset(sXym, 0x00, sizeof(sXym));
        memset(sXyxx, 0x00, sizeof(sXyxx));
        dSkje = 0.00 ;
                
        iRet = DCIFetch(cur);
        if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        	
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("GenPLKFSHZ从cur游标获取数据失败"),"ERROR");
        	break;
    		}  
    		if ( iRet == 0 )
          break;       
        
        strncpy( sTraNo, DCIFieldAsString(cur, 0 ), sizeof( sTraNo ) );
        dSkje = atof( DCIFieldAsString(cur, 1 ) );
        strncpy( sTaxVouNo, DCIFieldAsString(cur, 2 ), sizeof( sTaxVouNo ) );
        strncpy( sXym, DCIFieldAsString(cur, 3 ), sizeof( sXym ) );
        strncpy( sXyxx, DCIFieldAsString(cur, 4 ), sizeof( sXyxx ) );           
        
        trim(sTraNo);
        trim(sTaxVouNo);
        trim(sXym);
        trim(sXyxx);
            
        /*将记录内容放到XML树 */
        /* 交易流水号 */
        memset(sBuf, 0x00, sizeof(sBuf));     
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/OriTraNo",i);
     	  COMP_SOFTSETXML(sBuf,sTraNo);
     	  /* 交易金额 */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TraAmt",i);
     	  sprintf(sTmpBuf,"%.2f",dSkje);
     	  COMP_SOFTSETXML(sBuf,sTmpBuf);
     	  /* 税票号码 */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxVouNo",i);
     	  COMP_SOFTSETXML(sBuf,sTaxVouNo);
     	  /* 扣税费日期 */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxDate",i);
     	  COMP_SOFTSETXML(sBuf,sZwrq);   /*扣税日期应为后台的帐务日期*/
     	  /* 处理结果--响应码 */ 
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/Result",i);
     	  COMP_SOFTSETXML(sBuf, sXym);
     	  /* 附言--响应信息 */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/AddWord",i);
     	  COMP_SOFTSETXML(sBuf,sXyxx);                        
       
    }
    

		DCIFreeCursor(cur);
   	/* end add dci 20141103 */
   	
    /* mod dci 20141103 
    for (i=1,iflag=0;;i++)
    {
        memset(sTraNo, 0x00, sizeof(sTraNo));
        memset(sTaxVouNo, 0x00, sizeof(sTaxVouNo));
        memset(sXym, 0x00, sizeof(sXym));
        memset(sXyxx, 0x00, sizeof(sXyxx));
        dSkje = 0.00 ;
        
        EXEC SQL FETCH cur_ksfmx_plhz INTO :sTraNo, :dSkje, :sTaxVouNo, :sXym, :sXyxx;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_ksfmx_plhz", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("GenPLKFSHZ从cur_ksfmx_plhz游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
        /*将记录内容放到XML树
        /* 交易流水号 
        memset(sBuf, 0x00, sizeof(sBuf));     
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/OriTraNo",i);
     	COMP_SOFTSETXML(sBuf,sTraNo);
     	/* 交易金额 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TraAmt",i);
     	sprintf(sTmpBuf,"%.2f",dSkje);
     	COMP_SOFTSETXML(sBuf,sTmpBuf);
     	/* 税票号码 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxVouNo",i);
     	COMP_SOFTSETXML(sBuf,sTaxVouNo);
     	/* 扣税费日期 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxDate",i);
     	COMP_SOFTSETXML(sBuf,sZwrq);   /*扣税日期应为后台的帐务日期*/
     	/* 处理结果--响应码 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/Result",i);
     	COMP_SOFTSETXML(sBuf, sXym);
     	/* 附言--响应信息 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/AddWord",i);
     	COMP_SOFTSETXML(sBuf,sXyxx);        	
        
    }	
    EXEC SQL CLOSE cur_ksfmx_plhz;    
    /* EXEC SQL FREE  cur_ksfmx_plhz; 
    */
     
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,36010,"生成批量扣税费回执");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("生成批量扣税费回执iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }            
    LOG(LM_STD,Fmtmsg("生成批量扣税费回执结束"),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;

}

/************************************************************************
动态组件函数定义
函数名称: SYW_TIPS_ZfChkPLJYDJ
名称: 校验止付原包或者原交易是否存在
输入接口：
输出接口： 
  0 -- 校验成功
  1 -- 原包不存在
  2 -- 原交易不存在
 -1 -- 系统错误
 
组件功能: 
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
批量交易登记表	tips_pljydj
批量扣税费明细表 tips_ssplksfmx

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月16日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_ZfChkPLJYDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
        char sTaxOrgCode[12+1];
        char sOriEntrustDate[8+1];
        char sOriPackNo[8+1];
        char sOriTraNo[8+1];
        char sStopType[1+1];
        int  iCount=0;
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    int i,iret=0;
    int iflag=0;
    char sBuf[256];
	
		char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
	fpub_InitSoComp(lXmlhandle);
	
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")  
    #endif
   
    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(5)
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1,sBuf,"征收机关代码");
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sOriEntrustDate, 0x00, sizeof(sOriEntrustDate));
    COMP_GETPARSEPARAS(2,sBuf,"原委托日期");
    pstrcopy(sOriEntrustDate, sBuf, sizeof(sOriEntrustDate));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sOriPackNo, 0x00, sizeof(sOriPackNo));
    COMP_GETPARSEPARAS(3,sBuf,"原包流水号");
    pstrcopy(sOriPackNo, sBuf, sizeof(sOriPackNo));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sOriTraNo, 0x00, sizeof(sOriTraNo));
    COMP_GETPARSEPARAS(4,sBuf,"原交易流水号");
    pstrcopy(sOriTraNo, sBuf, sizeof(sOriTraNo));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sStopType, 0x00, sizeof(sStopType));
    COMP_GETPARSEPARAS(5,sBuf,"止付类型");
    pstrcopy(sStopType, sBuf, sizeof(sStopType));
    
    LOG(LM_STD,Fmtmsg("校验止付请求包开始处理..."), fpub_GetCompname(lXmlhandle)) 
    LOG(LM_STD,Fmtmsg("征收机关代码[%s],原委托日期[%s],原包流水号[%s],原交易流水号[%s],止付类型[%s]...",
        sTaxOrgCode, sOriEntrustDate, sOriPackNo, sOriTraNo, sStopType), fpub_GetCompname(lXmlhandle))    
    
    iCount = -1 ;
    if ( sStopType[0] == '1')/* 整包止付 */
    {
    		/* add dci 20141103 */
    		
				memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_pljydj\
    	 		where orgcode='%s' and entrustdate='%s' and packno='%s'",sTaxOrgCode,sOriEntrustDate,sOriPackNo);     	
    		iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ查询止付原包或交易出错"),fpub_GetCompname(lXmlhandle));	
    		}
    		/* end add dci 20141103 */
    		/* mod dci 20141103 
        EXEC SQL SELECT COUNT(*) INTO :iCount
             FROM tips_pljydj
             WHERE orgcode=:sTaxOrgCode
               AND entrustdate=:sOriEntrustDate
               AND packno=:sOriPackNo;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ查询止付原包或交易出错"),fpub_GetCompname(lXmlhandle));	
        }
        */
        
        if ( iCount < 1 )
        {
            fpub_SetMsg(lXmlhandle, 94055, "原止付包不存在");
            fpub_SetCompStatus(lXmlhandle, 1);
            LOGRET(COMPRET_FAIL,LM_STD,"ZfChkPLJYDJ原止付包不存在",fpub_GetCompname(lXmlhandle));
        }
    }else/* 单笔止付 */
    {
    		/* add dci 20141103 */
    		
				memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplksfmx\
    	 		where taxorgcode='%s' and entrustdate='%s' and packno='%s' and trano='%s'",sTaxOrgCode,sOriEntrustDate,sOriPackNo,sOriTraNo);     	
    		iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ查询止付原包或交易出错"),fpub_GetCompname(lXmlhandle));	
    		}
    		/* end add dci 20141103 */
    		
    		/* mod dci 20141103 
        EXEC SQL SELECT COUNT(*) INTO :iCount
             FROM tips_ssplksfmx
             WHERE taxorgcode=:sTaxOrgCode
               AND entrustdate=:sOriEntrustDate
               AND packno=:sOriPackNo
               AND trano=:sOriTraNo;        
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ查询止付原包或交易出错"),fpub_GetCompname(lXmlhandle));	
        }
        */
        if ( iCount < 1 )
        {
            fpub_SetMsg(lXmlhandle, 94054, "原止付交易不存在");
            fpub_SetCompStatus(lXmlhandle, 1);
            LOGRET(COMPRET_FAIL,LM_STD,"ZfChkPLJYDJ原止付交易不存在",fpub_GetCompname(lXmlhandle));
        }
    }
    LOG(LM_STD,Fmtmsg("校验止付请求包成功..."),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;    
                
}

/************************************************************************
动态组件函数定义
函数名称: SYW_TIPS_InitPLZFKSF
名称: 初始化批量止付扣税费
 
组件功能: 初始化批量止付扣税费
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
税收批量止付扣税费	tips_ssplzfksf

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月16日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPLZFKSF(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        int iCount;
        SDB_TIPS_SSPLZFKSF stPlzfksf ;
    EXEC SQL END DECLARE SECTION;
    */
    int i;
    int iRet=0;
    int iFlag=0;
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		
		int iCount;
        SDB_TIPS_SSPLZFKSF stPlzfksf ;
		/* end add dci 20141103 */
    
	fpub_InitSoComp(lXmlhandle);
	
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")  
    #endif
   
    memset(&stPlzfksf, 0x00, sizeof(stPlzfksf));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "帐务日期")
    pstrcopy( stPlzfksf.zwrq, sBuf, sizeof(stPlzfksf.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "批量止付流水号")
    pstrcopy( stPlzfksf.plzflsh, sBuf, sizeof(stPlzfksf.plzflsh));
    
    LOG(LM_STD,Fmtmsg("初始化批量止付扣税费表 帐务日期[%s],批量止付流水号[%s]", 
        stPlzfksf.zwrq, stPlzfksf.plzflsh), fpub_GetCompname(lXmlhandle));

    iCount = 0 ;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplzfksf\
    	 		where zwrq='%s' and plzflsh='%s'",stPlzfksf.zwrq,stPlzfksf.plzflsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("查询批量止付扣税费表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplzfksf
         WHERE zwrq = :stPlzfksf.zwrq
           AND plzflsh = :stPlzfksf.plzflsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("查询批量止付扣税费表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* 判断本批量包是否重复 */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24303, Fmtmsg("本止付包已登记-前置内部批量止付流水号重复"));
        LOG(LM_STD,Fmtmsg("InitPLZFKSF本止付包已登记-前置内部批量止付流水号重复"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }
    
    /* 3.征收机关代码  */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(stPlzfksf.taxorgcode, sBuf, sizeof(stPlzfksf.taxorgcode));
    /* 4.委托日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy(stPlzfksf.entrustdate, sBuf, sizeof(stPlzfksf.entrustdate));
    /* 5.止付申请序号  */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/StopNo", sBuf)
    pstrcopy(stPlzfksf.stopno, sBuf, sizeof(stPlzfksf.stopno));
    
    iCount = 0 ;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplzfksf\
    	 		where taxorgcode='%s' and plzflsh='%s' and stopno='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.entrustdate,stPlzfksf.stopno);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("查询批量止付扣税费表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplzfksf
         WHERE taxorgcode=:stPlzfksf.taxorgcode
           AND entrustdate=:stPlzfksf.entrustdate
           AND stopno=:stPlzfksf.stopno;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("查询批量止付扣税费表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* 判断本批量包是否重复 */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24303, Fmtmsg("本止付包已登记-止付申请序号重复"));
        LOG(LM_STD,Fmtmsg("InitPLZFKSF本止付包已登记-止付申请序号重复"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }
            
    /* 6.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stPlzfksf.workdate, sBuf, sizeof(stPlzfksf.workdate));
    /* 7.原委托日期  */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriEntrustDate", sBuf)
    pstrcopy(stPlzfksf.orientrustdate, sBuf, sizeof(stPlzfksf.orientrustdate));
    /* 8.原包流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriPackNo", sBuf)
    pstrcopy(stPlzfksf.oripackno, sBuf, sizeof(stPlzfksf.oripackno));
    iCount = 0 ;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplzfksf\
    	 		where taxorgcode='%s' and orientrustdate='%s' and oripackno='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.orientrustdate,stPlzfksf.oripackno);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("查询批量止付扣税费表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplzfksf
         WHERE taxorgcode=:stPlzfksf.taxorgcode
           AND orientrustdate=:stPlzfksf.orientrustdate
           AND oripackno=:stPlzfksf.oripackno;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("查询批量止付扣税费表失败"));
        LOG(LM_STD,Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* 判断本批量包是否重复 */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24303, Fmtmsg("本止付包已登记-不允许对同一扣款包重复止付"));
        LOG(LM_STD,Fmtmsg("InitPLZFKSF本止付包已登记-不允许对同一扣款包重复止付"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }
    /* 9.原交易流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriTraNo", sBuf)
    pstrcopy(stPlzfksf.oritrano, sBuf, sizeof(stPlzfksf.oritrano));
    /* 10.止付类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/StopType", sBuf)
    pstrcopy(stPlzfksf.stoptype, sBuf, sizeof(stPlzfksf.stoptype));
    /* 11.总笔数 12.总金额  */
    if (stPlzfksf.stoptype[0]=='1')/* 整包止付 */
    {
    		/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select allnum, allamt, zwrq, pljylsh from tips_pljydj\
    	 		where orgcode='%s' and entrustdate='%s' and packno='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.orientrustdate,stPlzfksf.oripackno);     	
    		/* iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allnum,stPlzfksf.allamt,stPlzfksf.yzwrq,stPlzfksf.ypljylsh); */
    		iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allnum,&stPlzfksf.allamt,stPlzfksf.yzwrq,stPlzfksf.ypljylsh);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF查询止付原包或交易出错"),
                fpub_GetCompname(lXmlhandle))	
    		}
    		/* end add dci 20141103 */
    		
    		/* mod dci 20141103
        EXEC SQL SELECT allnum, allamt, zwrq, pljylsh 
             INTO :stPlzfksf.allnum, :stPlzfksf.allamt, :stPlzfksf.yzwrq, :stPlzfksf.ypljylsh
             FROM tips_pljydj
             WHERE orgcode=:stPlzfksf.taxorgcode
               AND entrustdate=:stPlzfksf.orientrustdate
               AND packno=:stPlzfksf.oripackno;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF查询止付原包或交易出错"),
                fpub_GetCompname(lXmlhandle))	
        } 
        */        
    }else
    {
    		/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select jyje, zwrq, pljylsh, plmxxh from tips_ssplksfmx\
    	 		where taxorgcode='%s' and entrustdate='%s' and packno='%s' and trano='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.orientrustdate,stPlzfksf.oripackno,stPlzfksf.oritrano);     	
    	/*	iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allamt, &stPlzfksf.yzwrq, &stPlzfksf.ypljylsh, &stPlzfksf.yplmxxh);*/
    		iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allamt, stPlzfksf.yzwrq, stPlzfksf.ypljylsh, &stPlzfksf.yplmxxh);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF查询止付原包或交易出错"),
                fpub_GetCompname(lXmlhandle))	
    		}
    		/* end add dci 20141103 */
    		
    		/* mod dci 20141103 
        EXEC SQL SELECT jyje, zwrq, pljylsh, plmxxh
             INTO :stPlzfksf.allamt, :stPlzfksf.yzwrq, :stPlzfksf.ypljylsh, :stPlzfksf.yplmxxh
             FROM tips_ssplksfmx
             WHERE taxorgcode=:stPlzfksf.taxorgcode
               AND entrustdate=:stPlzfksf.orientrustdate
               AND packno=:stPlzfksf.oripackno
               AND trano=:stPlzfksf.oritrano;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "查询止付原包或交易出错");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF查询止付原包或交易出错"),
                fpub_GetCompname(lXmlhandle))	
        }
        */
        stPlzfksf.allnum = 1 ;        
    }        

    /* 17.当前状态 */
    stPlzfksf.dqzt[0]='0';
    /* 18.响应码 */
    pstrcopy(stPlzfksf.xym, "00000", sizeof(stPlzfksf.xym));
    /* 19.响应信息 */
    pstrcopy(stPlzfksf.xyxx, "止付包登记成功", sizeof(stPlzfksf.xyxx));
    /* 20.扩展标志 */
    pstrcopy(stPlzfksf.kzbz, "00000000", sizeof(stPlzfksf.kzbz));
    /* 21.止付原因 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/StopReason", sBuf)
    pstrcopy(stPlzfksf.stopreason, sBuf, sizeof(stPlzfksf.stopreason));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_ssplzfksf", SD_TIPS_SSPLZFKSF, NUMELE(SD_TIPS_SSPLZFKSF), &stPlzfksf, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	DCIRollback();   
    	
    	fpub_SetMsg(lXmlhandle, 24306, "登记批量止付失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLZFKSF登记批量止付失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	  
    
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL INSERT INTO tips_ssplzfksf  VALUES (:stPlzfksf);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24306, "登记批量止付失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLZFKSF登记批量止付失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	  
    */  

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;        
}

/************************************************************************
动态组件函数定义
函数名称: SYW_TIPS_ClPLZFKSF
名称: 处理批量止付扣税费
 
组件功能: 处理批量止付扣税费
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
税收批量止付扣税费	tips_ssplzfksf

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月16日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_ClPLZFKSF(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
         char sYzwrq[8+1];/* 原帐务日期 */
         char sYpljylsh[8+1];/* 原批量交易流水号 */
         char sCzbd[1+1];/* 操作步点 */
         char sWcbz[1+1];/* 完成标志 */
         int iYplmxxh;
         char sSysDate[8+1];/* 系统日期 */
         char sSysTime[6+1];/* 系统时间 */
         int iZfbs;/* 止付金额 */
         double dZfje;/* 止付笔数 */ 
         char sJyCzbd[1+1];/* 交易操作步点 */
         char sJyXym[5+1];/* 交易响应码 */ 
         int iSuccNum=0; 
         double dSuccAmt=0.00; 
         char sXym[5+1];
         char sXyxx[60+1]; 
         char sDqzt[1+1];/* 当前状态 */  
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sStopType[1+1];/* 止付类型 */
    char sStopAnswerPath[60];/* 止付应答结点 */
    char sAddWordPath[60];/* 附言结点 */
    int iStopResult;
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
    int iRet=0;
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("处理批量止付扣税费开始..."), fpub_GetCompname(lXmlhandle))
    
    COMP_PARACOUNTCHK(6);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sYzwrq, 0x00, sizeof(sYzwrq));
    COMP_GETPARSEPARAS(1, sBuf, "原帐务日期")
    pstrcopy( sYzwrq, sBuf, sizeof(sYzwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sYpljylsh, 0x00, sizeof(sYpljylsh));
    COMP_GETPARSEPARAS(2, sBuf, "原批量交易流水号")
    pstrcopy( sYpljylsh, sBuf, sizeof(sYpljylsh)); 
    trim(sYpljylsh);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iYplmxxh=0;
    COMP_GETPARSEPARAS(3, sBuf, "原批量明细序号")
    iYplmxxh=atoi(sBuf);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sStopType, 0x00, sizeof(sStopType));
    COMP_GETPARSEPARAS(4, sBuf, "止付类型")
    pstrcopy( sStopType, sBuf, sizeof(sStopType)); 
    trim(sStopType);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sStopAnswerPath, 0x00, sizeof(sStopAnswerPath));
    COMP_GETPARAS(5, sBuf, "止付应答")
    pstrcopy( sStopAnswerPath, sBuf, sizeof(sStopAnswerPath)); 
    trim(sStopAnswerPath);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sAddWordPath, 0x00, sizeof(sAddWordPath));
    COMP_GETPARAS(6, sBuf, "附言")
    pstrcopy( sAddWordPath, sBuf, sizeof(sAddWordPath)); 
    trim(sAddWordPath);
            
    LOG(LM_STD,Fmtmsg("原帐务日期[%s],原批量交易流水号[%s],原批量明细序号[%d],止付类型[%s]...", 
        sYzwrq, sYpljylsh, iYplmxxh, sStopType), fpub_GetCompname(lXmlhandle))

    memset(sCzbd, 0x00, sizeof(sCzbd));
    memset(sWcbz, 0x00, sizeof(sWcbz));
    iZfbs=0;
    dZfje=0.00;
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select czbd, wcbz, allnum, allamt from tips_pljydj\
    	 		where zwrq='%s' and pljylsh='%s'",sYzwrq,sYpljylsh);     	
    iRet = DBSelectToMultiVar(sErrmsg,sSql1, &sCzbd, &sWcbz, &iZfbs, &dZfje);
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 99003, "查询原包步点及完成标志失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF查询原包步点及完成标志失败"),
            fpub_GetCompname(lXmlhandle))
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT czbd, wcbz, allnum, allamt
         INTO :sCzbd, :sWcbz, :iZfbs, :dZfje
         FROM tips_pljydj
         WHERE zwrq=:sYzwrq
           AND pljylsh=:sYpljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR || SQLNOTFOUND_TIPS )
    {
        fpub_SetMsg(lXmlhandle, 99003, "查询原包步点及完成标志失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF查询原包步点及完成标志失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    if ( sWcbz[0]=='9' )/* 完成标志 9-整包正在处理中 */
    {
        fpub_SetMsg(lXmlhandle, 99090, "原包/交易正在处理中,不能止付");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF原包/交易正在处理中,不能止付"),
            fpub_GetCompname(lXmlhandle))       
    }

    memset(sSysDate, 0x00, sizeof(sSysDate));
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML("/sys/sysdate", sSysDate)
    COMP_SOFTGETXML("/sys/systime", sSysTime)

    /* 开始事务 
    EXEC SQL BEGIN WORK ;   */ 

    /* 更新原整包为正在处理中 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    				SET wcbz='9' \
    			where zwrq='%s' and pljylsh='%s'" \
    			,sYzwrq  ,sYpljylsh);
               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        fpub_SetMsg(lXmlhandle, 99003, "更新批量交易登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量交易登记表失败"),
            fpub_GetCompname(lXmlhandle)) 	
    }
    /* end dci 20141103 */    
    
    /* mod dci 20141103 
    EXEC SQL UPDATE tips_pljydj SET wcbz='9'
         WHERE zwrq=:sYzwrq
           AND pljylsh=:sYpljylsh;        
    if ( SQLERR )	
    {
         /* EXEC SQL ROLLBACK WORK;
         fpub_SetMsg(lXmlhandle, 99003, "更新批量交易登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量交易登记表失败"),
            fpub_GetCompname(lXmlhandle)) 	
    }
    */
    
    iSuccNum=0;
    dSuccAmt=0.00;
    iStopResult=0;
    memset(sDqzt, 0x00, sizeof(sDqzt));
    memset(sXym, 0x00, sizeof(sXym));
    memset(sXyxx, 0x00, sizeof(sXyxx));        
    if ( sStopType[0]=='1' )/* 整包止付 */
    {
        if ( sCzbd[0]=='2' )
        {
            iSuccNum=iZfbs;
            dSuccAmt=dZfje;
            sWcbz[0]='3';
            sDqzt[0]='1';
            iStopResult=1;/* 止付成功 */
            pstrcopy(sXym, "24020", sizeof(sXym));
            pstrcopy(sXyxx, "整包被止付成功", sizeof(sXyxx));
            /* 更新原包批量扣税费明细表的相关记录 */
            /* add dci 20141103 */
    				memset( sSql1, 0x00, sizeof( sSql1 ) );
    				snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    								SET czbd='1',\
                     xym='%s',\
                     xyxx='%s'\
    								where zwrq='%s' and pljylsh='%s'" \
    								,sXym, sXyxx, sYzwrq ,sYpljylsh);
               	
    				iRet = DCIExecuteDirect(sSql1);	 
    				if ( iRet < 0 )
    				{
        			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        			fpub_SetMsg(lXmlhandle, 99003, "更新批量扣税费明细表失败");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量扣税费明细表失败"),
                     fpub_GetCompname(lXmlhandle))	
    				}
    				/* end add dci 20141103 */
    
            /* mod dci 20141103
            EXEC SQL UPDATE tips_ssplksfmx
                 SET czbd='1',
                     xym=:sXym,
                     xyxx=:sXyxx
                WHERE zwrq=:sYzwrq
                  AND pljylsh=:sYpljylsh;                     
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
            if (SQLERR)	
            {
                /* EXEC SQL ROLLBACK WORK;
                 fpub_SetMsg(lXmlhandle, 99003, "更新批量扣税费明细表失败");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量扣税费明细表失败"),
                     fpub_GetCompname(lXmlhandle))	
            }
            */
        }else
        {
            iSuccNum=0;
            dSuccAmt=0.00;
            sDqzt[0]='2';/* 2-处理失败 */
            pstrcopy(sXym, "99090", sizeof(sXym));
            pstrcopy(sXyxx, "止付失败,已扣款", sizeof(sXyxx)); 
            iStopResult=2;/* 止付失败-已扣款 */            
        }      
    }else
    {
        /* 查询原交易的操作步点及交易金额 */
        dZfje=0.00;
        memset(sJyCzbd, 0x00, sizeof(sJyCzbd));
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT jyje, czbd FROM tips_ssplksfmx \
    				where zwrq='%s' and pljylsh='%s' and plmxxh = '%d'",sYzwrq , sYpljylsh, iYplmxxh);  
    		iRet = DBSelectToMultiVar(sErrmsg, sSql1,&dZfje, &sJyCzbd);
    		if ( iRet < 0 || iRet == 0)
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        		fpub_SetMsg(lXmlhandle, 99003, "查询原包步点及完成标志失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF查询原包步点及完成标志失败"),
                fpub_GetCompname(lXmlhandle))		     
    		}
        /* end add dci 20141103 */
        
        /* mod dci 20141103 
        EXEC SQL SELECT jyje, czbd INTO :dZfje, :sJyCzbd
             FROM tips_ssplksfmx
            WHERE zwrq=:sYzwrq
              AND pljylsh=:sYpljylsh
              AND plmxxh=:iYplmxxh;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR || SQLNOTFOUND_TIPS )
        {
           /* EXEC SQL ROLLBACK WORK; 
            fpub_SetMsg(lXmlhandle, 99003, "查询原包步点及完成标志失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF查询原包步点及完成标志失败"),
                fpub_GetCompname(lXmlhandle))
        }
        */
        
        if( sCzbd[0]=='2' )/* 此处为批量交易登记表的操作步点来判断，尚未扣款 */
        {
            iStopResult=1;/* 止付成功 */
            sJyCzbd[0]='1';/* 交易操作步点 1-被止付 */
            sDqzt[0]='1';/* 1-止付成功 */
            iSuccNum=1;
            dSuccAmt=dZfje;
            pstrcopy(sXym, "24020", sizeof(sXym));
            pstrcopy(sXyxx, "此扣税费交易被止付", sizeof(sXyxx));
            /* add dci 20141103 */
    				memset( sSql1, 0x00, sizeof( sSql1 ) );
    				snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    								SET czbd='1',\
                     xym='%s',\
                     xyxx='%s'\
    								where zwrq='%s' and pljylsh='%s' and plmxxh=%d" \
    								,sXym, sXyxx, sYzwrq  ,sYpljylsh, iYplmxxh);
               	
    				iRet = DCIExecuteDirect(sSql1);	 
    				if ( iRet < 0 )
    				{
        			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        			fpub_SetMsg(lXmlhandle, 99003, "更新批量扣税费明细表失败");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量扣税费明细表失败"),
                     fpub_GetCompname(lXmlhandle))		
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103 
            EXEC SQL UPDATE tips_ssplksfmx
                 SET czbd=:sJyCzbd,
                     xym=:sXym,
                     xyxx=:sXyxx
                WHERE zwrq=:sYzwrq
                  AND pljylsh=:sYpljylsh
                  AND plmxxh=:iYplmxxh;                     
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
            if (SQLERR)	
            {
                /* EXEC SQL ROLLBACK WORK; 
                 fpub_SetMsg(lXmlhandle, 99003, "更新批量扣税费明细表失败");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量扣税费明细表失败"),
                     fpub_GetCompname(lXmlhandle))	
             
            }
            */
            
        }else
        {
            iStopResult=2;/* 止付失败 */
            iSuccNum=0;
            dSuccAmt=0.00;
            sDqzt[0]='2';/* 2-处理失败 */
            pstrcopy(sXym, "99090", sizeof(sXym));
            pstrcopy(sXyxx, "止付失败,已扣款", sizeof(sXyxx));   
        }                
    }
    /* 更新批量交易登记表 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    								SET zfzbs=%d,\
                        zfzje=%f,\
                        wcbz='%s',\
                        cljsrq='%s',\
                        cljssj='%s',\
                        xym='%s',\
                        xyxx='%s'\
                        where zwrq='%s' and pljylsh='%s'", \
    								iSuccNum,dSuccAmt,sWcbz,sSysDate,sSysTime,sXym,sXyxx,sYzwrq ,sYpljylsh);
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        fpub_SetMsg(lXmlhandle, 99003, "更新批量登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量交易登记表失败"),
             fpub_GetCompname(lXmlhandle))	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL UPDATE tips_pljydj 
         SET zfzbs=:iSuccNum,
             zfzje=:dSuccAmt,
             wcbz=:sWcbz,/* 完成标志 
             cljsrq=:sSysDate,
             cljssj=:sSysTime,
             xym=:sXym,
             xyxx=:sXyxx
         WHERE zwrq=:sYzwrq
           AND pljylsh=:sYpljylsh;            
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR)	
    {
        /* EXEC SQL ROLLBACK WORK; 
         fpub_SetMsg(lXmlhandle, 99003, "更新批量登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量交易登记表失败"),
             fpub_GetCompname(lXmlhandle))	
    } 
    */
               
    /* 更新批量扣税费止付表 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplzfksf \
    								SET num_succ=%d,\
                        amt_succ=%f,\
                        clrq='%s',\
                        clsj='%s',\
             						dqzt='%s',\
             						xym='%s',\
                        xyxx='%s'\
    								where yzwrq='%s' and ypljylsh='%s'", \
    								iSuccNum,dSuccAmt,sSysDate,sSysTime,sDqzt,sXym,sXyxx,sYzwrq , sYpljylsh);
    									
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        fpub_SetMsg(lXmlhandle, 99003, "更新批量止付扣税费表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量止付扣税费表失败"),
             fpub_GetCompname(lXmlhandle))
    }
    /* end add dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL UPDATE tips_ssplzfksf
         SET num_succ=:iSuccNum,
             amt_succ=:dSuccAmt,
             clrq=:sSysDate,
             clsj=:sSysTime,
             dqzt=:sDqzt,
             xym=:sXym,
             xyxx=:sXyxx   
        WHERE yzwrq=:sYzwrq
          AND ypljylsh=:sYpljylsh;            
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR || SQLNOTFOUND_TIPS)	
    {
       /*  EXEC SQL ROLLBACK WORK;
         fpub_SetMsg(lXmlhandle, 99003, "更新批量止付扣税费表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF更新批量止付扣税费表失败"),
             fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*全局提交
    EXEC SQL COMMIT WORK;
    if ( SQLERR )  
    {
       LOG(LM_STD,Fmtmsg("数据库提交失败sqlcode=[%d]",sqlca.sqlcode),"ERROR");
       /* EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 99003,Fmtmsg("数据库操作失败"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPRET_FAIL;    	
    }    
    */
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf, "%d", iStopResult);
    COMP_SOFTSETXML(sStopAnswerPath, sBuf) 
    COMP_SOFTSETXML(sAddWordPath, sXyxx)
    LOG(LM_STD,Fmtmsg("处理批量止付扣税费结束,止付应答[%d](1-成功,2-失败),附言[%s]...", 
        iStopResult, sXyxx),"INFO"); 
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;

}


/************************************************************************
动态组件函数定义
函数名称: SYW_TIPS_PLKSF
名称: 并发批量扣税费交易
 
组件功能: 并发批量扣税费交易
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
批量交易登记表	tips_pljydj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年03月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_PLKSF(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
         int iCount ;
         char sZwrq[8+1];/* 帐务日期 */
         char sPljylsh[8+1];/* 批量交易流水号 */
         char sCzbd[1+1];/* 操作步点 */
         char sWcbz[1+1];/* 完成标志 */ 
         char sWorkDate[8+1];/* 工作日期 */
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sSubFlow[100];
    int iflag=0 ;
    int iAll = 0;
    int iSucc;
    int iFail;
	int iPEruptCnt = 10;
	int iPCount = 0;
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;
		int iRet=0;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSubFlow, 0x00, sizeof(sSubFlow));
    COMP_GETPARSEPARAS(1, sBuf, "内部子流程")
    pstrcopy(sSubFlow, sBuf, sizeof(sSubFlow));
    trim(sSubFlow);

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tipsx/receipt/plks/peruptcnt", sBuf);
	trim(sBuf);
	if ( strlen(sBuf) > 0 ) {
		iPEruptCnt = atoi(sBuf);
		if ( 0 == iPEruptCnt ) {
			iPEruptCnt = 10;
		}
	}
    LOG(LM_STD,Fmtmsg("并发处理批量扣税费开始,批量扣税费主流程[%s]...", sSubFlow), fpub_GetCompname(lXmlhandle))
    
    memset(sWorkDate, 0x00, sizeof(sWorkDate));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select workdate from tips_nbcsb	where 1=1"); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          	
    iRet = DBSelectToVar(sErrmsg, &sWorkDate, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "查询内部参数表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询内部参数表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;              
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT workdate INTO :sWorkDate
         FROM tips_nbcsb
         WHERE 1=1;
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "查询内部参数表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询内部参数表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
        
    iCount = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_pljydj\
    	where workdate='%s' and wcbz in ('0', '3') 	AND czbd in ('2', '3', '4', '5', '6')",sWorkDate);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);    	
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "查询批量交易登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_pljydj
         WHERE workdate=:sWorkDate
           AND wcbz in ('0', '3')
           AND czbd in ('2', '3', '4', '5', '6');
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "查询批量交易登记表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询批量交易登记表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
    
    if ( iCount < 1 )
    {
         fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "当前没需要处理的批量扣税费交易");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
         LOG(LM_STD, Fmtmsg("当前没需要处理的批量扣税费交易"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_SUCC ;        
    }
    
    LOG(LM_STD, Fmtmsg("当前需要处理的批量扣税费交易共[%d]条", iCount), fpub_GetCompname(lXmlhandle))	
    
    /* 开始触发需处理的批量扣税费交易*/
    /* 设置业务明细块 */    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT zwrq, pljylsh FROM  tips_pljydj\
    	where workdate='%s' and wcbz in ('0', '3') \
           AND czbd in ('2', '3', '4', '5', '6') ORDER BY zwrq, pljylsh desc",sWorkDate);
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

    /* end dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL DECLARE cur_pljydj_plksf CURSOR for 
        SELECT zwrq, pljylsh
        FROM  tips_pljydj 
         WHERE workdate=:sWorkDate
           AND wcbz in ('0', '3')
           AND czbd in ('2', '3', '4', '5', '6');
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_pljydj_plksf;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_pljydj_plksf",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,36001, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("PLKSF打开cur_pljydj_plksf游标失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*开始循环*/
    iSucc = 0;
    iFail = 0;
	iAll = 0;
    /* add dci 20141103 */        
	iRet = DCIFetch(cur);
	/**begin 添加批次并发控制 add by zhangl 20161026 */
	iPCount = 1;
	/**end 添加批次并发控制*/
    while( iRet > 0 )
    {
    		memset(sZwrq, 0x00, sizeof(sZwrq));
    		memset(sPljylsh, 0x00, sizeof(sPljylsh));
    		
        strncpy( sZwrq, DCIFieldAsString(cur, 0 ), sizeof( sZwrq ) );
        strncpy( sPljylsh, DCIFieldAsString(cur, 1 ), sizeof( sPljylsh ) );
                   
        trim(sZwrq);
        trim(sPljylsh);
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        iAll++;
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费主流程系统错误"),"ERROR");
        	break;
        }
        
		
        /*判断子流程是否处理成功 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*返回2失败,其它均为成功 */
        {
        	iFail ++;
        	/* iflag=-3; */
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费主流程失败"),"ERROR");
        	continue;
        }
        iSucc++;

		/**begin 添加批次并发控制 add by zhangl 20161026 */
		if ( ++iPCount > iPEruptCnt ) { /*该次自动任务并发处理完毕，退出*/
			break;
		}
		/**end 添加批次并发控制*/
        
		iRet = DCIFetch(cur);               
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }   

		DCIFreeCursor(cur);
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    for (iAll=0,iflag=0;;iAll++)
    {
        memset(sZwrq, 0x00, sizeof(sZwrq));
        memset(sPljylsh, 0x00, sizeof(sPljylsh));
        
        EXEC SQL FETCH cur_pljydj_plksf INTO :sZwrq, :sPljylsh;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_pljydj_plksf", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("PLKSF从cur_pljydj_plksf游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;

        trim(sZwrq);
        trim(sPljylsh);
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费主流程系统错误"),"ERROR");
        	break;
        }
        
        /*判断子流程是否处理成功
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*返回2失败,其它均为成功
        {
        	iFail ++;
        	/* iflag=-3; 
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费主流程失败"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    EXEC SQL CLOSE cur_pljydj_plksf;
    */
        
    /* EXEC SQL FREE  cur_pljydj_plksf;*/
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"并发处理批量扣税费失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("并发处理批量扣税费失败iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("并发处理批量扣税费结束,共[%d]笔,成功[%d]笔,失败[%d]笔",
        iAll, iSucc, iFail), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}


/************************************************************************
动态组件函数定义
函数名称: SYW_TIPS_PLKSF_P2D
名称: 并发批量扣税费交易(批拆单)
 
组件功能: 并发批量扣税费交易(批拆单)
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
批量交易登记表	tips_pljydj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年03月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_PLKSF_P2D(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
         int iCount ;
         char sZwrq[8+1];/* 帐务日期 */
         char sPljylsh[8+1];/* 批量交易流水号 */
         char sCzbd[1+1];/* 操作步点 */
         char sWcbz[1+1];/* 完成标志 */ 
         char sWorkDate[8+1];/* 工作日期 */
         int iZbs;
         char cZbs[16+1];
         double dZje;
         char cZje[32+1];
         int iPlmxxh;/* 批量明细序号 */
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sSubFlow[100];
    int iflag=0 ;
    int iAll=0;
    int iSucc=0;
    int iFail=0;
	int iEruptCnt = 10;
	int iEruptStep = 0;
	int iEruptSnd = 2;
	
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;
		int iRet=0;
		
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSubFlow, 0x00, sizeof(sSubFlow));
    COMP_GETPARSEPARAS(1, sBuf, "内部子流程")
    pstrcopy(sSubFlow, sBuf, sizeof(sSubFlow));
    trim(sSubFlow);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(2,sBuf,"帐务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(3,sBuf,"批量交易流水号")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    trim(sPljylsh);

	/*获取连续并发个数，默认为10*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tipsx/receipt/plks/eruptcnt", sBuf);
	trim(sBuf);
	if (strlen(sBuf) > 0) {
		iEruptCnt = atoi(sBuf);
		if ( 0 == iEruptCnt) {
			iEruptCnt = 10;
		}
	}
	/*获取并发中断时间长度， 默认为2s*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tipsx/receipt/plks/eruptsnd", sBuf);
	trim(sBuf);
	if (strlen(sBuf) > 0) {
		iEruptSnd = atoi(sBuf);
		if ( 0 == iEruptSnd ) {
			iEruptSnd = 2;
		} 
	}
	
    LOG(LM_STD,Fmtmsg("批量扣税费(批拆单)开始,帐务日期[%s],批量交易流水号[%s]流程[%s],...", 
        sZwrq, sPljylsh, sSubFlow), fpub_GetCompname(lXmlhandle))
        
    iCount = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_ssplksfmx \
     where zwrq='%s' and pljylsh=%s and czbd='0'",sZwrq,sPljylsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "查询批量扣税费明细表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplksfmx
         WHERE zwrq=:sZwrq
           AND pljylsh=:sPljylsh
           AND czbd='0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "查询批量扣税费明细表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
        
    if ( iCount < 1 )
    {
        iZbs = 0;
        dZje = 0.0;  
        iCount = 0;
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM tips_ssplksfmx \
    			where zwrq='%s' and pljylsh='%s' and czbd='6'",sZwrq , sPljylsh); 
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")       
    		/*iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&iZbs, &dZje);*/
    		iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs);
    		iZbs=atoi(cZbs);
    		
    		if ( iRet < 0 )
    		{
        	   fpub_SetMsg(lXmlhandle, 24310, "查询批量扣税费明细表失败");
		         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		         LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
		         return COMPRET_FAIL ;            
    		}
    		if ( iCount > 0 )
        {
					    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
					    LOG(LM_STD,Fmtmsg("还有未处理完的记录"), fpub_GetCompname(lXmlhandle))
					    return COMPRET_SUCC;
        }
        
        /* end add dci 20141103 */
        
        /* mod dci 20141103  
		    EXEC SQL SELECT COUNT(*) INTO :iCount
		         FROM tips_ssplksfmx
		         WHERE zwrq=:sZwrq
		           AND pljylsh=:sPljylsh
		           AND czbd='6';
		    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
		    if ( SQLERR )
		    {
		         fpub_SetMsg(lXmlhandle, 24310, "查询批量扣税费明细表失败");
		         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		         LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
		         return COMPRET_FAIL ;        
		    }
				if ( iCount > 0 )
        {
					    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
					    LOG(LM_STD,Fmtmsg("还有未处理完的记录"), fpub_GetCompname(lXmlhandle))
					    return COMPRET_SUCC;
        }
        */
        
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    			where zwrq='%s' and pljylsh='%s' and czbd='7'",sZwrq , sPljylsh); 
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")       
    		/*iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&iZbs, &dZje);*/
    		iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs, &cZje);
    		iZbs=atoi(cZbs);
    		dZje=atof(cZje);
    		
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
          fpub_SetMsg(lXmlhandle, 24311, "查询批量扣税费明细表失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;          
    		}
        /* end add dci 20141103 */
        
        /* mod dci 20141103  
        EXEC SQL SELECT COUNT(*), nvl(SUM(jyje), 0.00) INTO :iZbs,:dZje 
             FROM tips_ssplksfmx
             WHERE zwrq=:sZwrq
               AND pljylsh=:sPljylsh
               AND czbd='7';
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
        if ( SQLERR )
        {
             fpub_SetMsg(lXmlhandle, 24311, "查询批量扣税费明细表失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;        
        }
        */
        
        /*修改批量交易登记信息*/
        /* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    			SET rzzbs  = rzzbs + %d,  \
           		rzzje  = rzzje + %.2f  \
           	WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'",\
    			iZbs \
    			,dZje\
          ,sZwrq    \
    			,sPljylsh );
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                     	
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 || iRet == 0)
    		{
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        	fpub_SetMsg(lXmlhandle, 24285, "更新批量登记信息失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新批量登记信息失败"),
                fpub_GetCompname(lXmlhandle))			
    		} 
    		/* end add dci 20141103 */
    		
        /* mod dci 20141103 
        EXEC SQL UPDATE tips_pljydj 
             SET rzzbs = :iZbs,         /*入帐总笔数
                 rzzje = :dZje
             WHERE zwrq = :sZwrq 
               AND pljylsh =:sPljylsh;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");   
        if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
        {
            fpub_SetMsg(lXmlhandle, 24285, "更新批量登记信息失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新批量登记信息失败"),
                fpub_GetCompname(lXmlhandle))		
         }       
        */
        iRet =DCICommit();
        /* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  */
        if ( iRet < 0 )
        {
      	  LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	  DCIRollback();
      	
      	  fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       	  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	  return COMPRET_FAIL;     
        }
        
                  
        fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "当前该批量没需要上送核心扣款的记录");
        fpub_SetCompStatus(lXmlhandle, 1);
        LOG(LM_STD, Fmtmsg("当前该批量没需要上送核心扣款的记录"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_SUCC ;        
    }
    
    LOG(LM_STD, Fmtmsg("当前该批量需要拆单上送核心扣款的记录共[%d]条", iCount), fpub_GetCompname(lXmlhandle))	
    
    /* 开始触发需处理的批量扣税费交易*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT plmxxh FROM  tips_ssplksfmx\
    	where zwrq='%s' and pljylsh='%s' and czbd='0'",sZwrq , sPljylsh);  
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
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

    /* end dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL DECLARE cur_plksfmx_p2d CURSOR for 
        SELECT plmxxh
        FROM tips_ssplksfmx
         WHERE zwrq=:sZwrq
           AND pljylsh=:sPljylsh
           AND czbd='0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_plksfmx_p2d;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_plksfmx_p2d",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,36001, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("PLKSF打开cur_plksfmx_p2d游标失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*开始循环*/
    iSucc = 0;
    iFail = 0;
    /* add dci 20141103 */
	LOG(LM_DEBUG, Fmtmsg("并发个数[%d], 停顿时间[%d]s", iEruptCnt, iEruptSnd), "INFO");
    for (iAll=0,iflag=0;;iAll++)
    {
    	/*异步call并发流量控制 begin 20161019  add by zhangl*/

		if (++iEruptStep > iEruptCnt) {
			iEruptStep = 0;
			sleep(iEruptSnd);
		}

		/*异步call并发流量控制 end 20161019  add by zhangl*/
		
        iPlmxxh=0;
        
        iRet = DCIFetch(cur);
        if ( iRet < 0 )
    		{
         	iflag=-1;
        	LOG(LM_STD,Fmtmsg("PLKSF从cur_plksfmx_p2d游标获取数据失败"),"ERROR");
        	break;
        }
        if ( iRet == 0 )
          break;
        
        iPlmxxh= atoi( DCIFieldAsString(cur, 0 ) );	
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%d", iPlmxxh);
        COMP_SOFTSETXML("/tips/plmxxh", sBuf)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费(批拆单)系统错误"),"ERROR");
        	break;
        }
        
        /*判断子流程是否处理成功 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*返回2失败,其它均为成功 */
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费(批拆单)失败"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    DCIFreeCursor(cur);

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    for (iAll=0,iflag=0;;iAll++)
    {
        iPlmxxh=0;
        
        EXEC SQL FETCH cur_plksfmx_p2d INTO :iPlmxxh;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_plksfmx_p2d", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("PLKSF从cur_plksfmx_p2d游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND_TIPS )
          break;
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%d", iPlmxxh);
        COMP_SOFTSETXML("/tips/plmxxh", sBuf)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费(批拆单)系统错误"),"ERROR");
        	break;
        }
        
        /*判断子流程是否处理成功
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*返回2失败,其它均为成功
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("PLKSF调批量扣税费(批拆单)失败"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    EXEC SQL CLOSE cur_plksfmx_p2d;    
    */
    
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"并发处理批量扣税费(批拆单)失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("并发处理批量扣税费(批拆单)失败iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("并发处理批量扣税费(批拆单)结束,共[%d]笔,成功[%d]笔,失败[%d]笔",
        iAll, iSucc, iFail), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
函数名称: SYW_TIPS_InitPZSJ_P2D
名称: 初始化凭证数据(批拆单)
 
组件功能: 初始化凭证数据(批拆单)
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
批量扣税费明细表	tips_ssplksfmx

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年03月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPZSJ_P2D(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103 
EXEC SQL BEGIN DECLARE SECTION;*/
         SDB_TIPS_SSPLKSFMX stPlksfmx;
         char sZwrq[8+1];
         int iPlmxxh;/* 批量明细序号 */
    /* add dci 20141103 
EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    int iRet=0;
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
    
    COMP_PARACOUNTCHK(2);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(1,sBuf,"帐务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iPlmxxh=0;
    COMP_GETPARSEPARAS(2,sBuf,"批量明细序号")
    iPlmxxh=atoi(sBuf);

    LOG(LM_STD,Fmtmsg("初始化凭证数据(批拆单)开始,帐务日期[%s],批量明细序号[%d]...", 
        sZwrq, iPlmxxh), fpub_GetCompname(lXmlhandle))
        
    memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_ssplksfmx where zwrq='%s' and plmxxh=%d",sZwrq,iPlmxxh);     	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
    /*
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPlksfmx.zwrq,&stPlksfmx.pljydm,&stPlksfmx.pljylsh,\
    		 &stPlksfmx.plpch,&stPlksfmx.plmxxh,&stPlksfmx.clcs,&stPlksfmx.workdate,&stPlksfmx.entrustdate,\
    		 &stPlksfmx.taxorgcode,&stPlksfmx.packno,&stPlksfmx.returnterm,&stPlksfmx.chkdate,&stPlksfmx.chkacctord,\
    		 &stPlksfmx.trano,&stPlksfmx.protocolno,&stPlksfmx.dfzh,&stPlksfmx.paybkcode,&stPlksfmx.payopbkcode,\
    		 &stPlksfmx.payacct,&stPlksfmx.payeebankno,&stPlksfmx.handorgname,&stPlksfmx.taxvouno,&stPlksfmx.jyje,\
    		 &stPlksfmx.sxf,&stPlksfmx.zhye,&stPlksfmx.je2,&stPlksfmx.zjrq,&stPlksfmx.zjsj,&stPlksfmx.zjlsh,\
    		 &stPlksfmx.dqdh,&stPlksfmx.jgdh,&stPlksfmx.jygy,&stPlksfmx.zddh,&stPlksfmx.czbd,&stPlksfmx.qsbz,\
    		 &stPlksfmx.xym,&stPlksfmx.xyxx,&stPlksfmx.kzbz,&stPlksfmx.taxpaycode,&stPlksfmx.taxpayname,&stPlksfmx.spxx,\
    		 &stPlksfmx.byzd );*/    
    LOG(LM_STD,Fmtmsg("stPlksfmx[%s][%s][%s][%s][%d][%d][%s][%s][%s][%s][%d][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s]\n \
    [%f][%f][%f][%f][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s]\n",\
    			stPlksfmx.zwrq,stPlksfmx.pljydm,stPlksfmx.pljylsh,\
    		 stPlksfmx.plpch,stPlksfmx.plmxxh,stPlksfmx.clcs,stPlksfmx.workdate,stPlksfmx.entrustdate,\
    		 stPlksfmx.taxorgcode,stPlksfmx.packno,stPlksfmx.returnterm,stPlksfmx.chkdate,stPlksfmx.chkacctord,\
    		 stPlksfmx.trano,stPlksfmx.protocolno,stPlksfmx.dfzh,stPlksfmx.paybkcode,stPlksfmx.payopbkcode,\
    		 stPlksfmx.payacct,stPlksfmx.payeebankno,stPlksfmx.handorgname,stPlksfmx.taxvouno,stPlksfmx.jyje,\
    		 stPlksfmx.sxf,stPlksfmx.zhye,stPlksfmx.je2,stPlksfmx.zjrq,stPlksfmx.zjsj,stPlksfmx.zjlsh,\
    		 stPlksfmx.dqdh,stPlksfmx.jgdh,stPlksfmx.jygy,stPlksfmx.zddh,stPlksfmx.czbd,stPlksfmx.qsbz,\
    		 stPlksfmx.xym,stPlksfmx.xyxx,stPlksfmx.kzbz,stPlksfmx.taxpaycode,stPlksfmx.taxpayname,stPlksfmx.spxx,\
    		 stPlksfmx.byzd),"INFO")
  
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "查询批量扣税费明细表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;          
    }

    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT * INTO :stPlksfmx
         FROM tips_ssplksfmx
         WHERE zwrq=:sZwrq
           AND plmxxh=:iPlmxxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "查询批量扣税费明细表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }    
    */
		
		iRet = 0;
		
    iRet = prv_tips_InitPZSJ_pl(lXmlhandle, stPlksfmx);
    if ( iRet != 0 )
    {
         fpub_SetMsg(lXmlhandle, 24310, "新增凭证信息失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("新增凭证信息失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;            
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("初始化凭证数据(批拆单)结束"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

