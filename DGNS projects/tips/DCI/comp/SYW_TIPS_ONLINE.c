/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V3.0.00
操作系统:AIX5.3
文件名称:SYW_TIPS_ONLINE.ec
文件描述:TIPS单笔实时交易
项 目 组:TIPS专用前置产品组
程 序 员:Tuql
发布日期:
修    订:
修改日期:20141103 leejn mod DCI
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
EXEC SQL INCLUDE  "../eh/tips_drls.eh";/* 当日流水 
EXEC SQL INCLUDE  "../eh/tips_yhsbcx.eh";/* 银行申报查询 
EXEC SQL INCLUDE  "../eh/tips_wtgxdj.eh";/* 委托关系登记 
EXEC SQL INCLUDE  "../eh/tips_pzsj.eh";/* 凭证数据表 
EXEC SQL INCLUDE  "../eh/tips_zygsbw.eh";/* 自由格式报文 
EXEC SQL INCLUDE  "../eh/tips_taxtypemx.eh";*/

/* add dci 20141103 */
#include "../eh/tips_drls.h"/* 当日流水 */
#include "../eh/tips_yhsbcx.h"/* 银行申报查询 */
#include "../eh/tips_wtgxdj.h"/* 委托关系登记 */
#include "../eh/tips_wtgxdjlsls.h"/* 委托关系登记历史流水 */
#include "../eh/tips_pzsj.h"/* 凭证数据表 */
#include "../eh/tips_zygsbw.h"/* 自由格式报文 */
#include "../eh/tips_taxtypemx.h" 
/* end add dci 20141103 */

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )

int sQj2Bj(char s[200] , char *st);


/* 登记凭证信息--实时单笔 */
int prv_tips_InitPZSJ_db(HXMLTREE lXmlhandle, SDB_TIPS_DRLS stDrls)
{
    /* add dci 20141103 
    EXEC SQL BEGIN DECLARE SECTION;
         SDB_TIPS_PZSJ stPzsj;
    EXEC SQL END DECLARE SECTION;
    */
    
    char sBuf[256];/* 临时变量 */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;		
    SDB_TIPS_PZSJ stPzsj;
		/* end add dci 20141103 */    
    
    memset(&stPzsj, 0x00, sizeof(stPzsj));
    
    pstrcopy(stPzsj.zwrq, stDrls.zwrq, sizeof(stPzsj.zwrq));
    stPzsj.zhqzlsh = stDrls.zhqzlsh;
    pstrcopy(stPzsj.jyrq, stDrls.workdate, sizeof(stPzsj.jyrq));
    pstrcopy(stPzsj.dqdh, stDrls.dqdh, sizeof(stPzsj.dqdh));
    pstrcopy(stPzsj.jgdh, stDrls.jgdh, sizeof(stPzsj.jgdh));
    pstrcopy(stPzsj.jygy, stDrls.jygy, sizeof(stPzsj.jygy));
    pstrcopy(stPzsj.zddh, stDrls.zddh, sizeof(stPzsj.zddh));
    pstrcopy(stPzsj.msgno, stDrls.msgno, sizeof(stPzsj.msgno));/* 报文编号 */
    pstrcopy(stPzsj.entrustdate, stDrls.entrustdate, sizeof(stPzsj.entrustdate));
    pstrcopy(stPzsj.taxorgcode, stDrls.taxorgcode, sizeof(stPzsj.taxorgcode));
    pstrcopy(stPzsj.packno, stDrls.trano, sizeof(stPzsj.packno));
    pstrcopy(stPzsj.trano, stDrls.trano, sizeof(stPzsj.trano));
    pstrcopy(stPzsj.payeebankno, stDrls.payeebankno, sizeof(stPzsj.payeebankno));
    pstrcopy(stPzsj.payeename, stDrls.payeename, sizeof(stPzsj.payeename));
    pstrcopy(stPzsj.paybkcode, stDrls.paybkcode, sizeof(stPzsj.paybkcode));
    pstrcopy(stPzsj.payopbkcode, stDrls.payopbkcode, sizeof(stPzsj.payopbkcode));
    pstrcopy(stPzsj.payacct, stDrls.payacct, sizeof(stPzsj.payacct));
    pstrcopy(stPzsj.handorgname, stDrls.handorgname, sizeof(stPzsj.handorgname));
    stPzsj.jyje=stDrls.jyje;
    pstrcopy(stPzsj.corpcode, "", sizeof(stPzsj.corpcode));
    pstrcopy(stPzsj.taxvouno, stDrls.taxvouno, sizeof(stPzsj.taxvouno));
    pstrcopy(stPzsj.taxpaycode, stDrls.taxpaycode, sizeof(stPzsj.taxpaycode));
    stPzsj.pzlx[0]='1';
    stPzsj.dycs=0;
    stPzsj.dzbz[0]='0';
    pstrcopy(stPzsj.pzsjwjm, stDrls.spxx, sizeof(stPzsj.pzsjwjm));
    /* add by lijn 20140825 */
    pstrcopy(stPzsj.jyqd, stDrls.jyqd, sizeof(stPzsj.jyqd));
    pstrcopy(stPzsj.zjrq      , stDrls.zjrq      , sizeof(stPzsj.zjrq      ));
    pstrcopy(stPzsj.zjsj      , stDrls.zjsj      , sizeof(stPzsj.zjsj      ));
    pstrcopy(stPzsj.zjlsh     , stDrls.zjlsh     , sizeof(stPzsj.zjlsh     ));
    pstrcopy(stPzsj.jyzt      , stDrls.jyzt      , sizeof(stPzsj.jyzt      ));
    stPzsj.hxdzbz[0]='0';
    pstrcopy(stPzsj.qsbz      , stDrls.qsbz      , sizeof(stPzsj.qsbz      ));
  	pstrcopy(stPzsj.taxpayname, stDrls.taxpayname, sizeof(stPzsj.taxpayname));
    pstrcopy(stPzsj.qspch			, ""			, sizeof(stPzsj.qspch			));
    pstrcopy(stPzsj.chkdate   , stDrls.chkdate   , sizeof(stPzsj.chkdate   ));
    pstrcopy(stPzsj.chkacctord, stDrls.chkacctord, sizeof(stPzsj.chkacctord));
    
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
		LOG(LM_STD,Fmtmsg("taxpayname[%s], taxpayname=[%s]",stPzsj.taxpayname, stDrls.taxpayname),"ERROR")
    /* end add 20140825 */
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_pzsj", SD_TIPS_PZSJ, NUMELE(SD_TIPS_PZSJ), &stPzsj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	LOG(LM_STD,Fmtmsg("新增凭证信息失败,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("新增凭证信息失败"),
            fpub_GetCompname(lXmlhandle))
    }   
    /* end add dci 20141103 */
     
    /* DCI MOD 20141103 
    EXEC SQL INSERT INTO tips_pzsj VALUES(:stPzsj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))    
    if ( SQLERR )
    {
        LOG(LM_STD,Fmtmsg("新增凭证信息失败,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")        
        return -1;
    }
    */
    
    return 0;    
}


/*
  生成协议书编号；使用xh2字段
  4位年份+8位序号
*/
int prv_tips_genxh2(int ioffset, char *szwrq, char *sxh_ret)
{
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
      char sxh[40],sxh_upd[40];
    /* EXEC SQL END DECLARE SECTION; add dci 20141103 */
    char sxh_new[40];
    int inum=0;
    
    int iRet;
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
    char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/  
    
    if (strlen(szwrq)!=8)  
    {
        LOG(LM_STD,Fmtmsg("传入的帐务日期格式不正确,szwrq[%s]",szwrq),"ERROR")
        return -9;
    }	
    /*   EXEC SQL BEGIN WORK;*/
  	/* mod 20141103 
    EXEC SQL lock table tips_sfxyxh in exclusive mode;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
        LOG(LM_STD,Fmtmsg("加锁序号表失败[tips_sfxyxh],sqlcode[%d]",sqlca.sqlcode),"ERROR")
        EXEC SQL rollback WORK;
        return -1;
    }
    EXEC SQL select xh2 into :sxh from tips_sfxyxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if((SQLERR) || ( SQLNOTFOUND_TIPS ))
    {
        LOG(LM_STD,Fmtmsg("取当前序号号失败[tips_sfxyxh],sqlcode[%d]",sqlca.sqlcode),"ERROR") 
        EXEC SQL rollback WORK;
        return -1;
    }
    trim(sxh);
    if (strlen(sxh)!=12)   			          /*没产生过
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else  if ( memcmp(sxh,szwrq,4)!=0 )	  /*非当年
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else
    {
       sprintf(sxh_new,"%012.0f",atof(sxh)+1);
    }	   
    sprintf(sxh_upd,"%012.0f",atof(sxh_new)+ioffset-1);	 
    EXEC SQL update tips_sfxyxh set xh2 = :sxh_upd;
    if ( SQLUPDATEERR )
    {
        LOG(LM_DEBUG,Fmtmsg("更新序号2失败[tips_sfxyxh],xh[%s],xh_new[%s],sqlcode[%d]",
                  sxh,sxh_new,sqlca.sqlcode),"ERROR") 
        EXEC SQL rollback WORK;
        return -1;
    }
    EXEC SQL COMMIT WORK;
    if ( SQLERR )
    {
      LOG(LM_STD,Fmtmsg("生成序号2COMMIT失败,sqlcode[%d]",sqlca.sqlcode),"ERROR");
      EXEC SQL rollback WORK; 
      return -1;	
    }
    /* end 	mod 20141103 */
    
    /* DCI add 20141103 */
    iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
			
			LOG(LM_STD,Fmtmsg("DCIBegin"),"ERROR");
			return COMPRET_FAIL;
		}

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "lock table tips_sfxyxh in exclusive mode");     	
    iRet = DCIExecuteDirect(sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        LOG(LM_STD,Fmtmsg("加锁序号表失败[tips_sfxyxh]"),"ERROR")
        DCIRollback();
        return -1;
        
    }
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select xh2 from tips_sfxyxh");     	
    iRet = DBSelectToVar(sErrmsg, &sxh, sSql1);
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        LOG(LM_STD,Fmtmsg("取当前序号号失败[tips_sfxyxh]"),"ERROR") 
        DCIRollback();
        return -1;
    }
        
    trim(sxh);
    if (strlen(sxh)!=12)   			          /*没产生过 */
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else  if ( memcmp(sxh,szwrq,4)!=0 )	  /*非当年 */
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else
    {
       sprintf(sxh_new,"%012.0f",atof(sxh)+1);
    }	   
    sprintf(sxh_upd,"%012.0f",atof(sxh_new)+ioffset-1);
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sfxyxh set xh2 ='%s'",sxh_upd);     	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        DCIRollback();
        
        LOG(LM_DEBUG,Fmtmsg("更新序号2失败[tips_sfxyxh],xh[%s],xh_new[%s]",
                  sxh,sxh_new),"ERROR") 
        return -1;
    }
    iRet =DCICommit();
    /* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("生成序号2COMMIT失败"),"ERROR");
      DCIRollback(); 
      return -1;	
    }
    */
    strcpy(sxh_ret,sxh_new);
    LOG(LM_STD,Fmtmsg("生成序号2成功,编号[%s]-[%s]",sxh_new,sxh_upd),"INFO");
    return 0;
}


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_YzcxSFXY
组件名称: 验证与撤销三方协议
组件功能: 
  验证与撤销三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月20日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_YzcxSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sTaxOrgCode[12+1];/* 征收机关代码 */
	    char sTaxOrgCode_t[12+1];/* 征收机关代码 */
        char sPayBkCode[12+1];/* 付款行行号 */
		char sPayBkCode_t[12+1];/* 付款行行号 */
        char sPayAcct[32+1];/* 付款账号 */
		char sPayAcct_t[32+1];/* 付款账号 */
    	char sProtocolNo[60+1];/* 协议书号 */
        char sProtocolNo_t[60+1];/* 协议书号 */

		char sHandOrgName[200+1];/* 缴款单位名称 */
        char sHandOrgName_t[200+1];/* 缴款单位名称 */

		char sTaxPayCode[20+1];/* 纳税人编码 */
        char sTaxPayCode_t[20+1];/* 纳税人编码 */
        char sWtgxzt[1+1];/* 委托关系状态 */
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sVCSign[1+1];/* 验证标志 */
    char sYzxgrq[8+1];
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(7);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(2, sBuf, "付款行行号")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(4, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
    COMP_GETPARSEPARAS(5, sBuf, "缴款单位名称")
    pstrcopy(sHandOrgName, sBuf, sizeof(sHandOrgName));
    trim(sHandOrgName);
    memset(sBuf, 0x00, sizeof(sBuf));
    sQj2Bj(sHandOrgName,sBuf);
    memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
    strcpy(sHandOrgName,sBuf);
    LOG(LM_STD,Fmtmsg("缴款单位名称_t[%s]", sHandOrgName), fpub_GetCompname(lXmlhandle))    
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    COMP_GETPARSEPARAS(6, sBuf, "纳税人编码")
    pstrcopy(sTaxPayCode, sBuf, sizeof(sTaxPayCode));
    trim(sTaxPayCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sVCSign, 0x00, sizeof(sVCSign));
    COMP_GETPARSEPARAS(7, sBuf, "验证标志")
    pstrcopy(sVCSign, sBuf, sizeof(sVCSign));
    trim(sVCSign); 

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYzxgrq, 0x00, sizeof(sYzxgrq));
	COMP_SOFTGETXML("/tips/zwrq", sBuf);
	trim(sBuf);
	pstrcopy(sYzxgrq, sBuf, sizeof(sYzxgrq));
	
    LOG(LM_STD,Fmtmsg("验证撤销三方协议开始处理... 征收机关代码[%s],付款行行号[%s],付款账号[%s]", 
        sTaxOrgCode, sPayBkCode, sPayAcct), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],缴款单位名称[%s],纳税人编码[%s],验证标志[%s]", 
        sProtocolNo, sHandOrgName, sTaxPayCode, sVCSign), fpub_GetCompname(lXmlhandle))        

    /* 查询客户委托关系 */
    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sProtocolNo_t, 0x00, sizeof(sProtocolNo_t));
    memset(sHandOrgName_t, 0x00, sizeof(sHandOrgName_t));
    memset(sTaxPayCode_t, 0x00, sizeof(sTaxPayCode_t));
    
    /* add DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT taxorgcode,paybkcode,payacct,wtgxzt, protocolno,handorgname, taxpaycode FROM tips_wtgxdj\
    	WHERE protocolno ='%s'", sProtocolNo);     	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,sTaxOrgCode_t,sPayBkCode_t,sPayAcct_t,sWtgxzt, sProtocolNo_t,sHandOrgName_t,sTaxPayCode_t);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("查询委托关系登记表失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记表失败"), 
            fpub_GetCompname(lXmlhandle));	
        
    }
    if ( iRet == 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("三方协议未签约"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议未签约"), 
            fpub_GetCompname(lXmlhandle));     
    }
    /* end add DCI 20141103 */  
    
    /* DCI MOD 20141103 
    EXEC SQL SELECT wtgxzt, protocolno, to_single_byte(handorgname), taxpaycode
         INTO :sWtgxzt, :sProtocolNo_t, :sHandOrgName_t, :sTaxPayCode_t
         FROM tips_wtgxdj
         WHERE taxorgcode = :sTaxOrgCode
           AND paybkcode = :sPayBkCode
           AND payacct = :sPayAcct
           AND protocolno = :sProtocolNo;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("查询委托关系登记表失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记表失败"), 
            fpub_GetCompname(lXmlhandle));	
    }
    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("三方协议未签约或征收机关代号、付款账号不符."));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议未签约或征收机关代号、付款账号不符."), 
            fpub_GetCompname(lXmlhandle));        
    }
    */

	trim(sTaxOrgCode_t);
	trim(sPayBkCode_t);
	trim(sPayAcct_t);
    trim(sWtgxzt);
	trim(sProtocolNo_t);
    trim(sHandOrgName_t);
    trim(sTaxPayCode_t);
    LOG(LM_STD,Fmtmsg("征收机关代码_t[%s],付款行行号_t[%s],付款账户_t[%s],协议书号_t[%s],缴款单位名称_t[%s],纳税人编码_t[%s]", 
        sTaxOrgCode_t,sPayBkCode_t,sPayAcct_t,sProtocolNo_t, sHandOrgName_t, sTaxPayCode_t), fpub_GetCompname(lXmlhandle))    

    /* 判断委托关系状态 */
    if ( sWtgxzt[0]=='1' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24348, Fmtmsg("三方协议被撤销"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议被撤销"), 
            fpub_GetCompname(lXmlhandle));         
    }        
    if ( sWtgxzt[0]=='2' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24349, Fmtmsg("三方协议被锁定"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议被锁定"), 
            fpub_GetCompname(lXmlhandle));         
    }
    if ( sWtgxzt[0]!='0' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24350, Fmtmsg("三方协议状态异常"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议状态异常"), 
            fpub_GetCompname(lXmlhandle));         
    }

	if (strcmp(sTaxOrgCode_t, sTaxOrgCode) != 0) {
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("征收机关不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关不一致"), 
            fpub_GetCompname(lXmlhandle)); 
	}
	if (strcmp(sPayBkCode_t, sPayBkCode) != 0) {
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("付款行行号不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号不一致"), 
            fpub_GetCompname(lXmlhandle)); 
	}
	if (strcmp(sPayAcct_t, sPayAcct) != 0) {
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("付款账户不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款账户不一致"), 
            fpub_GetCompname(lXmlhandle)); 
	}
	
    /* 判断协议书号是否一致 */
    if ( strcmp(sProtocolNo, sProtocolNo_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("协议书号不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("协议书号不一致"), 
            fpub_GetCompname(lXmlhandle));         
    }    
    /* 判断缴款单位名称是否一致 */
    if ( strcmp(sHandOrgName, sHandOrgName_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24352, Fmtmsg("缴款单位名称不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("缴款单位名称不一致"), 
            fpub_GetCompname(lXmlhandle));
    }
    /* 判断纳税人编码是否一致 
    if ( strcmp(sTaxPayCode, sTaxPayCode_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24353, Fmtmsg("纳税人编码不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人编码不一致"), 
            fpub_GetCompname(lXmlhandle));
    }*/
    
    /* DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    
		if (sVCSign[0]=='0')/* 验证 */
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='1',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
        	sYzxgrq,sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);    	
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 || iRet == 0)/* add 20141215 iRet=0也认为更新不成功 */
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        		        
        			fpub_SetMsg(lXmlhandle, 24354, "更新委托关系登记表失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新委托关系登记表失败"),
                 fpub_GetCompname(lXmlhandle))
    		}
        LOG(LM_STD,Fmtmsg("三方协议验证通过"), fpub_GetCompname(lXmlhandle))
    }else
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='2',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
        	sYzxgrq,sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);     	
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    		iRet = DCIExecuteDirect(sSql1);	        	 
    		if ( iRet < 0 || iRet == 0)/* add 20141215 iRet=0也认为更新不成功 */
    		{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        		        
        			fpub_SetMsg(lXmlhandle, 24354, "更新委托关系登记表失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新委托关系登记表失败"),
                 fpub_GetCompname(lXmlhandle))
    		}
        LOG(LM_STD,Fmtmsg("三方协议撤销通过"), fpub_GetCompname(lXmlhandle))        
    } 
    /* END DCI 20141103 */
    
    /* 根据验证撤销标志更新处理 
    if (sVCSign[0]=='0')/* 验证 
    {
        EXEC SQL UPDATE tips_wtgxdj
             SET  yzbz='1'
            WHERE taxorgcode = :sTaxOrgCode
              AND paybkcode = :sPayBkCode
              AND payacct = :sPayAcct
           		AND protocolno = :sProtocolNo;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )	
        {
             fpub_SetMsg(lXmlhandle, 24354, "更新委托关系登记表失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新委托关系登记表失败"),
                 fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("三方协议验证通过"), fpub_GetCompname(lXmlhandle))
    }else
    {
        EXEC SQL UPDATE tips_wtgxdj
             SET  yzbz='2'
            WHERE taxorgcode = :sTaxOrgCode
              AND paybkcode = :sPayBkCode
              AND payacct = :sPayAcct           
           		AND protocolno = :sProtocolNo;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )	
        {
             fpub_SetMsg(lXmlhandle, 24354, "更新委托关系登记表失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新委托关系登记表失败"),
                 fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("三方协议撤销通过"), fpub_GetCompname(lXmlhandle))        
    }  
    */
          
    fpub_SetMsg(lXmlhandle, 0, "三方协议验证与撤销处理成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("三方协议验证与撤销处理成功"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_JySFXY
组件名称: 校验三方协议
组件功能: 
  校验三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月20日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_JySFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sTaxOrgCode[12+1];/* 征收机关代码 */
        char sPayBkCode[12+1];/* 付款行行号 */
        char sPayAcct[32+1];/* 付款账号 */
        char sWtgxzt[1+1];/* 委托关系状态 */
        char sYzbz[1+1];/* 验证标志 */
        char sTaxPayCode[20+1];/* 纳税人编码 */
        char sProtocolNo[60+1];/* 协议书号 */
        char sDqdh[10+1];/* 地区代号 add by tuql 20090909*/
        char sJgdh[10+1];/* 机构代号 add by tuql 20090909*/
        char sPayAcct2[32+1];/* 付款账号2 add by liurj 20180713 */
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sMsgNo[4+1];/* 报文编号 */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(5);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(2, sBuf, "付款行行号")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(4, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgNo, 0x00, sizeof(sMsgNo));
    COMP_GETPARSEPARAS(5, sBuf, "报文编号")
    pstrcopy(sMsgNo, sBuf, sizeof(sMsgNo));
    trim(sMsgNo);

    LOG(LM_STD,Fmtmsg("校验三方协议开始处理... 征收机关代码[%s],付款行行号[%s],付款账号[%s]", 
        sTaxOrgCode, sPayBkCode, sPayAcct), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],报文编号[%s]", sProtocolNo, sMsgNo), fpub_GetCompname(lXmlhandle)) 

    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sYzbz, 0x00, sizeof(sYzbz));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    memset(sDqdh, 0x00, sizeof(sDqdh));
    memset(sJgdh, 0x00, sizeof(sJgdh));
    memset(sPayAcct2, 0x00, sizeof(sPayAcct2)); /*add by liurj 20180713*/
    
    /* DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    if ( sProtocolNo[0]=='\0' )
    {
    	/* modefied by liurj 20180713 增加查询字段payacct2 */
    	snprintf( sSql1, sizeof(sSql1), "SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh, payacct2 FROM tips_wtgxdj \
    		WHERE payacct='%s' and paybkcode='%s'",sPayAcct,sPayBkCode);     
        
    }else
    {
    	/* 20150730 修改为同时校验协议号、付款账号 */
    	/* modefied by liurj 20180713 增加查询字段payacct2 */
      snprintf( sSql1, sizeof(sSql1), "SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh, payacct2 FROM tips_wtgxdj \
    		WHERE protocolno='%s' and payacct='%s' and paybkcode='%s'",sProtocolNo,sPayAcct,sPayBkCode); 
         
    }  
         
   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
    /* modefied by liurj 20180713 增加查询字段payacct2 */
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sWtgxzt, &sYzbz, &sTaxPayCode, &sDqdh, &sJgdh, &sPayAcct2);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("查询委托关系登记表失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记表失败"), 
            fpub_GetCompname(lXmlhandle));	
        
    }
    if ( iRet == 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("三方协议未签约"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议未签约"), 
            fpub_GetCompname(lXmlhandle));     
    }
    /* end add DCI 20141103 */
    
    /* MOD DCI 20141103
    if ( sProtocolNo[0]=='\0' )
    {
        EXEC SQL SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh
             INTO :sWtgxzt, :sYzbz, :sTaxPayCode, :sDqdh, :sJgdh
             FROM tips_wtgxdj
             WHERE  payacct=:sPayAcct;
    }else
    {
        EXEC SQL SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh
             INTO :sWtgxzt, :sYzbz, :sTaxPayCode, :sDqdh, :sJgdh
             FROM tips_wtgxdj
             WHERE  payacct=:sPayAcct
               AND  protocolno=:sProtocolNo;
    }        
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 99003, Fmtmsg("查询委托关系登记表失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记表失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("三方协议未签约"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议未签约"), 
            fpub_GetCompname(lXmlhandle));        
    }
    */
    
    trim(sWtgxzt);trim(sYzbz);trim(sTaxPayCode);
    LOG(LM_STD,Fmtmsg("委托关系状态[%s],验证状态[%s],纳税人编码_t[%s]", 
        sWtgxzt, sYzbz, sTaxPayCode), fpub_GetCompname(lXmlhandle)) 

    /* 判断委托关系状态 */
    if ( sWtgxzt[0]=='2' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("三方协议被撤销"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议被撤销"), 
            fpub_GetCompname(lXmlhandle));         
    }        
    if ( sWtgxzt[0]=='3' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("三方协议被锁定"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议被锁定"), 
            fpub_GetCompname(lXmlhandle));         
    }
    if ( sWtgxzt[0]!='0' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("三方协议状态异常"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议状态异常"), 
            fpub_GetCompname(lXmlhandle));         
    }
    /* 判断委托关系验证标志 */
    if ( sYzbz[0]!='1' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("三方协议未验证或已撤销"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议未验证或已撤销"), 
            fpub_GetCompname(lXmlhandle));         
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "/tips/MSG/Payment%s/TaxPayCode", sMsgNo);
    trim(sBuf);
    COMP_SOFTSETXML(sBuf, sTaxPayCode) 
    COMP_SOFTSETXML("/tips/TaxPayCode", sTaxPayCode)
    
    /* add by tuql 20090910 将签约时的地区代号更新到表中去 */
    COMP_SOFTSETXML("/tips/djdqdh", sDqdh)
    COMP_SOFTSETXML("/tips/djjgdh", sJgdh)
    
    /* add by liurj 20180713 将三方协议表中的payacct2保存到节点 */
    COMP_SOFTSETXML("/tips/PayAcct2", sPayAcct2)
    
    fpub_SetMsg(lXmlhandle, 0, "校验三方协议成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("校验三方协议成功"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InsDRLS
组件名称: 登记当日流水
组件功能: 
  登记当日流水
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_drls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月23日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InsDRLS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
         SDB_TIPS_DRLS stDrls;
         char sKhh[12+1];
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */ 

    char sBuf[256];
    char sInsDrls[1+1];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
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

    memset(&stDrls, 0x00, sizeof(stDrls));
    /* 1.帐务日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zwrq", sBuf)
    pstrcopy(stDrls.zwrq, sBuf, sizeof(stDrls.zwrq));
    if (stDrls.zwrq[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24119, "账务日期不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("账务日期不能为空"), 
            fpub_GetCompname(lXmlhandle))         
    }        
    /* 2.综合前置流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    if (sBuf[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24120, "综合前置流水号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("综合前置流水号不能为空"), 
            fpub_GetCompname(lXmlhandle))         
    }    
    stDrls.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("登记当日流水开始处理...帐务日期[%s]综合前置流水号[%d]",
        stDrls.zwrq, stDrls.zhqzlsh),"INFO");

    /* 3.交易渠道 mod by tuql 20090505 修改为从/pub/subsysname中取值*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/subsysname", sBuf)
    pstrcopy(stDrls.jyqd, sBuf, sizeof(stDrls.jyqd));
    /* 4.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.workdate, sBuf, sizeof(stDrls.workdate));
    /* 5.委托日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy(stDrls.entrustdate, sBuf, sizeof(stDrls.entrustdate));
    if (stDrls.entrustdate[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24121, "委托日期不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("委托日期不能为空"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 6.征收机关代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(stDrls.taxorgcode, sBuf, sizeof(stDrls.taxorgcode));
    if (stDrls.taxorgcode[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24122, "征收机关代码不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("征收机关代码不能为空"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 7.交易流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo", sBuf)
    pstrcopy(stDrls.trano, sBuf, sizeof(stDrls.trano));
    if (stDrls.trano[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24123, "交易流水号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("交易流水号不能为空"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 8.报文编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MsgNo", sBuf)
    pstrcopy(stDrls.msgno, sBuf, sizeof(stDrls.msgno));
    if (stDrls.msgno[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24124, "报文编号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("报文编号不能为空"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 9.委托日期2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate2", sBuf)
    pstrcopy(stDrls.entrustdate2, sBuf, sizeof(stDrls.entrustdate2));
    /* 10.交易流水号2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo2", sBuf)
    pstrcopy(stDrls.trano2, sBuf, sizeof(stDrls.trano2));
    /* 11.综合前置流水号2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh2", sBuf)
    stDrls.zhqzlsh2=atoi(sBuf);
    /* 12.对账日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.chkdate, sBuf, sizeof(stDrls.chkdate));
    /* 13.对账批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy(stDrls.chkacctord, sBuf, sizeof(stDrls.chkacctord));
    /* 14.经收类别 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandleType", sBuf)
    pstrcopy(stDrls.handletype, sBuf, sizeof(stDrls.handletype));
    /* 15.国库代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TreCode", sBuf)
    pstrcopy(stDrls.trecode, sBuf, sizeof(stDrls.trecode));
    /* 16.收款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy(stDrls.payeebankno, sBuf, sizeof(stDrls.payeebankno));
    /* 17.收款单位代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOrgCode", sBuf)
    pstrcopy(stDrls.payeeorgcode, sBuf, sizeof(stDrls.payeeorgcode));
    
    /* 18.收款人帐号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy(stDrls.payeeacct, sBuf, sizeof(stDrls.payeeacct));
    /* 19.收款人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeName", sBuf)
    pstrcopy(stDrls.payeename, sBuf, sizeof(stDrls.payeename));
    trim(stDrls.payeename);
    /* 20.付款行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy(stDrls.paybkcode, sBuf, sizeof(stDrls.paybkcode));
    /* 21.付款开户行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy(stDrls.payopbkcode, sBuf, sizeof(stDrls.payopbkcode));
    /* 22.协议书号 add by tuql 20091112*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ProtocolNo", sBuf)
    pstrcopy(stDrls.protocolno, sBuf, sizeof(stDrls.protocolno));
    
    /* 23.付款人帐号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy(stDrls.payacct, sBuf, sizeof(stDrls.payacct));
    /* 24.缴款单位名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandOrgName", sBuf)
    pstrcopy(stDrls.handorgname, sBuf, sizeof(stDrls.handorgname));
    trim(stDrls.handorgname);
    /* 25.贷方账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dfzh", sBuf)
    pstrcopy(stDrls.dfzh, sBuf, sizeof(stDrls.dfzh));
    trim(stDrls.dfzh);
    /* 26.交易金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraAmt", sBuf)
    stDrls.jyje=atof(sBuf);
    /* 27.税票号码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxVouNo", sBuf)
    pstrcopy(stDrls.taxvouno, sBuf, sizeof(stDrls.taxvouno));
    
    /* 28.地区代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djdqdh", sBuf)
    pstrcopy(stDrls.dqdh, sBuf, sizeof(stDrls.dqdh));
    trim(stDrls.dqdh);
    /* 29.机构代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djjgdh", sBuf)
    pstrcopy(stDrls.jgdh, sBuf, sizeof(stDrls.jgdh));
    trim(stDrls.jgdh);
   
    /*memset(sKhh, 0x00, sizeof(sKhh));
    付款开户行清算行号
    EXEC SQL SELECT jgdh INTO :sKhh 
	     FROM  tips_jgdhdj  
	     WHERE khqshh=:stDrls.payopbkcode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "查询机构代号登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询机构代号登记表失败"),
            fpub_GetCompname(lXmlhandle))
    }*/   
     
    /* 30.交易柜员 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stDrls.jygy, sBuf, sizeof(stDrls.jygy));
    trim(stDrls.jygy);
    /* 31.终端代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stDrls.zddh, sBuf, sizeof(stDrls.zddh));
    trim(stDrls.zddh);
    /* 32.交易日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stDrls.jyrq, sBuf, sizeof(stDrls.jyrq));
    /* 33.交易时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stDrls.jysj, sBuf, sizeof(stDrls.jysj));
    /* 34.主机日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stDrls.zjrq, sBuf, sizeof(stDrls.zjrq));
    /* 35.主机时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stDrls.zjsj, sBuf, sizeof(stDrls.zjsj));
    /* 36.主机流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stDrls.zjlsh, sBuf, sizeof(stDrls.zjlsh));
    trim(stDrls.zjlsh);
    /* 37.主机响应码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxym", sBuf)
    pstrcopy(stDrls.zjxym, sBuf, sizeof(stDrls.zjxym));
    /* 38.主机响应信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxyxx", sBuf)
    pstrcopy(stDrls.zjxyxx, sBuf, sizeof(stDrls.zjxyxx));
    trim(stDrls.zjxyxx);
    /* 39.手续费 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sxf", sBuf)
    stDrls.sxf=atof(sBuf);
    /* 40.帐户余额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhye", sBuf)
    stDrls.zhye=atof(sBuf);
    /* 41.响应码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respcode", sBuf)
    pstrcopy(stDrls.xym, sBuf, sizeof(stDrls.xym));
    /* 42.响应信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respmsg", sBuf)
    pstrcopy(stDrls.xyxx, sBuf, sizeof(stDrls.xyxx));
    trim(stDrls.xyxx);
    /* 43.交易状态 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stDrls.jyzt, sBuf, sizeof(stDrls.jyzt));
    if (stDrls.jyzt[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24125, "交易状态不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("交易状态不能为空"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 44.对帐标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stDrls.dzbz, sBuf, sizeof(stDrls.dzbz));
    if (stDrls.dzbz[0]=='\0')
    {
        strcpy(stDrls.dzbz, "00");
    }    
    /* 45.清算标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stDrls.qsbz, sBuf, sizeof(stDrls.qsbz));
    if (stDrls.qsbz[0]=='\0')
    {
        stDrls.qsbz[0]='0';
    }
    /* 46.扩展标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/kzbz", sBuf)
    pstrcopy(stDrls.kzbz, sBuf, sizeof(stDrls.kzbz));
    /* 47.纳税人编码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayCode", sBuf)
    pstrcopy(stDrls.taxpaycode, sBuf, sizeof(stDrls.taxpaycode));
    /* 48.纳税人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName", sBuf)
    trim(sBuf);
    pstrcopy(stDrls.taxpayname, sBuf, sizeof(stDrls.taxpayname));
    /* 49.税票信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/spxx", sBuf)
    pstrcopy(stDrls.spxx, sBuf, sizeof(stDrls.spxx));
    /* 50.备用字段 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/czyhbz", sBuf)
    pstrcopy(stDrls.byzd, sBuf, sizeof(stDrls.byzd));
    
    /* ADD DCI 20141103 */
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_drls", SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	    	
    	memset(sInsDrls, 0x00, sizeof(sInsDrls));
      sInsDrls[0]='0';
      COMP_SOFTSETXML("/tips/insdrls", sInsDrls)
      fpub_SetMsg(lXmlhandle, 24112, "登记当日流水表失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InsDRLS登记当日流水表失败"), 
            fpub_GetCompname(lXmlhandle))        
    }
    
    
    iRet =DCICommit();
    /* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("登记当日流水表失败"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InsDRLS登记当日流水表失败"), 
            fpub_GetCompname(lXmlhandle))    
    }
    */

		/* end add DCI 20141103 */
		
    /* DCI MOD 20141103 
    EXEC SQL INSERT INTO tips_drls  VALUES (:stDrls);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        memset(sInsDrls, 0x00, sizeof(sInsDrls));
        sInsDrls[0]='0';
        COMP_SOFTSETXML("/tips/insdrls", sInsDrls)
        fpub_SetMsg(lXmlhandle, 24112, "登记当日流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InsDRLS登记当日流水表失败"), 
            fpub_GetCompname(lXmlhandle))        
    }    
    EXEC SQL COMMIT; /*事务提交
    */ 
    
    memset(sInsDrls, 0x00, sizeof(sInsDrls));
    sInsDrls[0]='1';
    COMP_SOFTSETXML("/tips/insdrls", sInsDrls)
    fpub_SetMsg(lXmlhandle, 0, "登记当日流水表成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("登记当日流水表成功"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdDRLS
组件名称: 更新当日流水
组件功能: 
  更新当日流水
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_drls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月23日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdDRLS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
         SDB_TIPS_DRLS stDrls;
         char sKhh[12+1];
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */ 

    char sBuf[256];
    char sInsDrls[1+1];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
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

    memset(&stDrls, 0x00, sizeof(stDrls));
    /* 1.帐务日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zwrq", sBuf)
    pstrcopy(stDrls.zwrq, sBuf, sizeof(stDrls.zwrq));    
    /* 2.综合前置流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    stDrls.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("更新当日流水开始处理...帐务日期[%s]综合前置流水号[%d]",
        stDrls.zwrq, stDrls.zhqzlsh),"INFO");
		
	  memset(sBuf, 0x00, sizeof(sBuf));
	  memset(sInsDrls, 0x00, sizeof(sInsDrls));
	  COMP_SOFTGETXML("/tips/insdrls", sBuf)
	  sInsDrls[0]=sBuf[0];
	  /* 若标记为0或为空,则不更新原流水 */
	  if (sInsDrls[0]=='0'||sInsDrls[0]=='\0')
	  {
          fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
          LOG(LM_STD,Fmtmsg("新增当日流水失败不必更新流水,跳过"), fpub_GetCompname(lXmlhandle))
          return COMPRET_SUCC;						
	  }	
    /* 3.交易渠道 mod by tuql 20090505 修改为从/pub/subsysname中取值*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/subsysname", sBuf)
    pstrcopy(stDrls.jyqd, sBuf, sizeof(stDrls.jyqd));
    /* 4.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.workdate, sBuf, sizeof(stDrls.workdate));
    /* 5.委托日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy(stDrls.entrustdate, sBuf, sizeof(stDrls.entrustdate));
    /* 6.征收机关代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(stDrls.taxorgcode, sBuf, sizeof(stDrls.taxorgcode));
    /* 7.交易流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo", sBuf)
    pstrcopy(stDrls.trano, sBuf, sizeof(stDrls.trano));
    /* 8.报文编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MsgNo", sBuf)
    pstrcopy(stDrls.msgno, sBuf, sizeof(stDrls.msgno));
    /* 9.委托日期2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate2", sBuf)
    pstrcopy(stDrls.entrustdate2, sBuf, sizeof(stDrls.entrustdate2));
    /* 10.交易流水号2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo2", sBuf)
    pstrcopy(stDrls.trano2, sBuf, sizeof(stDrls.trano2));
    /* 11.综合前置流水号2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh2", sBuf)
    stDrls.zhqzlsh2=atoi(sBuf);
    /* 12.对账日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.chkdate, sBuf, sizeof(stDrls.chkdate));
    /* 13.对账批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy(stDrls.chkacctord, sBuf, sizeof(stDrls.chkacctord));
    /* 12.经收类别 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandleType", sBuf)
    pstrcopy(stDrls.handletype, sBuf, sizeof(stDrls.handletype));
    /* 13.国库代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TreCode", sBuf)
    pstrcopy(stDrls.trecode, sBuf, sizeof(stDrls.trecode));
    /* 14.收款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy(stDrls.payeebankno, sBuf, sizeof(stDrls.payeebankno));
    /* 15.收款单位代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOrgCode", sBuf)
    pstrcopy(stDrls.payeeorgcode, sBuf, sizeof(stDrls.payeeorgcode));
    /* 16.协议书号 add by tuql 20091112*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ProtocolNo", sBuf)
    pstrcopy(stDrls.protocolno, sBuf, sizeof(stDrls.protocolno));
    /* 16.收款人帐号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy(stDrls.payeeacct, sBuf, sizeof(stDrls.payeeacct));
    /* 17.收款人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeName", sBuf)
    pstrcopy(stDrls.payeename, sBuf, sizeof(stDrls.payeename));
    trim(stDrls.payeename);
    /* 18.付款行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy(stDrls.paybkcode, sBuf, sizeof(stDrls.paybkcode));
    /* 19.付款开户行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy(stDrls.payopbkcode, sBuf, sizeof(stDrls.payopbkcode));
    /* 20.付款人帐号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy(stDrls.payacct, sBuf, sizeof(stDrls.payacct));
    /* 21.缴款单位名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandOrgName", sBuf)
    pstrcopy(stDrls.handorgname, sBuf, sizeof(stDrls.handorgname));
    trim(stDrls.handorgname);
    /* 22.贷方账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dfzh", sBuf)
    pstrcopy(stDrls.dfzh, sBuf, sizeof(stDrls.dfzh));
    trim(stDrls.dfzh);
    /* 22.交易金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraAmt", sBuf)
    stDrls.jyje=atof(sBuf);
    /* 23.税票号码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxVouNo", sBuf)
    pstrcopy(stDrls.taxvouno, sBuf, sizeof(stDrls.taxvouno));
    /* 24.地区代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djdqdh", sBuf)/* mod by tuql 20090909 由dqdh-->djdqdh */
    pstrcopy(stDrls.dqdh, sBuf , sizeof(stDrls.dqdh));
    trim(stDrls.dqdh);
    /* 25.机构代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djjgdh", sBuf)
    pstrcopy(stDrls.jgdh, sBuf, sizeof(stDrls.jgdh));
    trim(stDrls.jgdh);
    /*付款开户行清算行号
    EXEC SQL SELECT jgdh INTO :sKhh 
	     FROM  tips_jgdhdj  
	     WHERE khqshh=:stDrls.payopbkcode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "查询机构代号登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询机构代号登记表失败"),
            fpub_GetCompname(lXmlhandle))
    }*/    
    /* 26.交易柜员 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stDrls.jygy, sBuf, sizeof(stDrls.jygy));
    trim(stDrls.jygy);
    /* 27.终端代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stDrls.zddh, sBuf, sizeof(stDrls.zddh));
    trim(stDrls.zddh);
    /* 28.交易日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stDrls.jyrq, sBuf, sizeof(stDrls.jyrq));
    /* 29.交易时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stDrls.jysj, sBuf, sizeof(stDrls.jysj));
    /* 30.主机日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stDrls.zjrq, sBuf, sizeof(stDrls.zjrq));
    /* 31.主机时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stDrls.zjsj, sBuf, sizeof(stDrls.zjsj));
    /* 32.主机流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stDrls.zjlsh, sBuf, sizeof(stDrls.zjlsh));
    trim(stDrls.zjlsh);
    /* 33.主机响应码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxym", sBuf)
    pstrcopy(stDrls.zjxym, sBuf, sizeof(stDrls.zjxym));
    /* 34.主机响应信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxyxx", sBuf)
    pstrcopy(stDrls.zjxyxx, sBuf, sizeof(stDrls.zjxyxx));
    trim(stDrls.zjxyxx);
    /* 35.手续费 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sxf", sBuf)
    stDrls.sxf=atof(sBuf);
    /* 36.帐户余额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhye", sBuf)
    stDrls.zhye=atof(sBuf);
    /* 37.响应码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respcode", sBuf)
    pstrcopy(stDrls.xym, sBuf, sizeof(stDrls.xym));
    /* 38.响应信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respmsg", sBuf)
    pstrcopy(stDrls.xyxx, sBuf, sizeof(stDrls.xyxx));
    trim(stDrls.xyxx);
    /* 39.交易状态 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stDrls.jyzt, sBuf, sizeof(stDrls.jyzt));
    /* 40.对帐标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stDrls.dzbz, sBuf, sizeof(stDrls.dzbz));
    /* 41.清算标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stDrls.qsbz, sBuf, sizeof(stDrls.qsbz));
    /* 42.扩展标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/kzbz", sBuf)
    pstrcopy(stDrls.kzbz, sBuf, sizeof(stDrls.kzbz));
    /* 43.纳税人编码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayCode", sBuf)
    pstrcopy(stDrls.taxpaycode, sBuf, sizeof(stDrls.taxpaycode));
    /* 43.纳税人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName", sBuf)
    pstrcopy(stDrls.taxpayname, sBuf, sizeof(stDrls.taxpayname));
    /* 44.税票信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/spxx", sBuf)
    pstrcopy(stDrls.spxx, sBuf, sizeof(stDrls.spxx));
    /* 45.备用字段 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/byzd", sBuf)
    pstrcopy(stDrls.byzd, sBuf, sizeof(stDrls.byzd));

		/* add dci 20141103 */
		
		memset( sSql1, 0x00, sizeof( sSql1 ) );
		    snprintf( sSql1, sizeof(sSql1), "zwrq ='%s' AND zhqzlsh =%d", stDrls.zwrq, stDrls.zhqzlsh); 
		LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))    
    iRet = DBUpdate("tips_drls", SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls, sSql1, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24113, "更新当日流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("UpdDRLS更新当日流水表失败"), 
            fpub_GetCompname(lXmlhandle))        
    }
    
    iRet =DCICommit();
    /* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"), 
            fpub_GetCompname(lXmlhandle))    
    }
    */
		/* end dci 20141103 */

		/* DCI MOD 20141103 
    EXEC SQL UPDATE tips_drls
         SET jyqd = :stDrls.jyqd,
             workdate = :stDrls.workdate,
             entrustdate = :stDrls.entrustdate,
             taxorgcode = :stDrls.taxorgcode,
             trano = :stDrls.trano,
             msgno = :stDrls.msgno,
             entrustdate2 = :stDrls.entrustdate2,
             trano2 = :stDrls.trano2,
             zhqzlsh2 = :stDrls.zhqzlsh2,
             chkdate = :stDrls.chkdate,
             chkacctord = :stDrls.chkacctord,                
             handletype = :stDrls.handletype,
             trecode = :stDrls.trecode,
             payeebankno = :stDrls.payeebankno,
             payeeorgcode = :stDrls.payeeorgcode,
             payeeacct = :stDrls.payeeacct,
             payeename = :stDrls.payeename,
             paybkcode = :stDrls.paybkcode,
             payopbkcode = :stDrls.payopbkcode,
             protocolno = :stDrls.protocolno,/* add by tuql 20091112 
             payacct = :stDrls.payacct,
             handorgname = :stDrls.handorgname,
             dfzh = :stDrls.dfzh,
             jyje = :stDrls.jyje,
             taxvouno = :stDrls.taxvouno,
             dqdh = :stDrls.dqdh,
             jgdh = :stDrls.jgdh,
             jygy = :stDrls.jygy,
             zddh = :stDrls.zddh,
             jyrq = :stDrls.jyrq,
             jysj = :stDrls.jysj,
             zjrq = :stDrls.zjrq,
             zjsj = :stDrls.zjsj,
             zjlsh = :stDrls.zjlsh,
             zjxym = :stDrls.zjxym,
             zjxyxx = :stDrls.zjxyxx,
             sxf = :stDrls.sxf,
             zhye = :stDrls.zhye,
             xym = :stDrls.xym,
             xyxx = :stDrls.xyxx,
             jyzt = :stDrls.jyzt,
             dzbz = :stDrls.dzbz,
             qsbz = :stDrls.qsbz,
             kzbz = :stDrls.kzbz,
             taxpaycode = :stDrls.taxpaycode,
             taxpayname = :stDrls.taxpayname,
             spxx = :stDrls.spxx
             /*byzd = :stDrls.byzd
         WHERE zwrq = :stDrls.zwrq
           AND zhqzlsh = :stDrls.zhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24113, "更新当日流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("UpdDRLS更新当日流水表失败"), 
            fpub_GetCompname(lXmlhandle))        
    }

    EXEC SQL COMMIT;  /*事务提交*/
    /* fpub_SetMsg(lXmlhandle, 0, "更新当日流水表成功"); */
    /* END DCI MOD 20141103 */
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新当日流水表成功"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitYHSBCX
组件名称: 初始化银行申报查询表数据
组件功能: 
  初始化银行申报查询表数据
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
银行申报查询表	tips_yhsbcx

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月24日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitYHSBCX(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 
         SDB_TIPS_YHSBCX stYhsbcx;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_YHSBCX stYhsbcx;
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle); 
    
    memset(&stYhsbcx, 0x00, sizeof(stYhsbcx));
    /* 1.帐务日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zwrq", sBuf)
    pstrcopy(stYhsbcx.zwrq, sBuf, sizeof(stYhsbcx.zwrq));
    /* 2.综合前置流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    stYhsbcx.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("初始化银行申报查询表数据 帐务日期[%s],综合前置流水号[%d]", 
        stYhsbcx.zwrq, stYhsbcx.zhqzlsh), fpub_GetCompname(lXmlhandle));
    
    /* 3.交易渠道 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jyqd", sBuf)
    pstrcopy(stYhsbcx.jyqd, sBuf, sizeof(stYhsbcx.jyqd));
    /* 4.地区代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh", sBuf)
    pstrcopy(stYhsbcx.dqdh, sBuf, sizeof(stYhsbcx.dqdh));
    /* 5.机构代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jgdh", sBuf)
    pstrcopy(stYhsbcx.jgdh, sBuf, sizeof(stYhsbcx.jgdh));
    /* 6.交易柜员 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stYhsbcx.jygy, sBuf, sizeof(stYhsbcx.jygy));
    /* 7.终端代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stYhsbcx.zddh, sBuf, sizeof(stYhsbcx.zddh));
    /* 8.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/HEAD/WorkDate", sBuf)
    pstrcopy(stYhsbcx.workdate, sBuf, sizeof(stYhsbcx.workdate));
    /* 9.交易日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stYhsbcx.jyrq, sBuf, sizeof(stYhsbcx.jyrq));
    /* 10.交易时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stYhsbcx.jysj, sBuf, sizeof(stYhsbcx.jysj));
    /* 11.商业银行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/BankNo", sBuf)
    pstrcopy(stYhsbcx.bankno, sBuf, sizeof(stYhsbcx.bankno));
    /* 12.委托日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/EntrustDate", sBuf)
    pstrcopy(stYhsbcx.entrustdate, sBuf, sizeof(stYhsbcx.entrustdate));
    /* 13.查询序号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/QueryNo", sBuf)
    pstrcopy(stYhsbcx.queryno, sBuf, sizeof(stYhsbcx.queryno));
    /* 14.付款开户行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/PayOpBkCode", sBuf)
    pstrcopy(stYhsbcx.payopbkcode, sBuf, sizeof(stYhsbcx.payopbkcode));
    /* 15.开户行名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/BankName", sBuf)
    pstrcopy(stYhsbcx.bankname, sBuf, sizeof(stYhsbcx.bankname));
    /* 16.征收机关代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/TaxOrgCode", sBuf)
    pstrcopy(stYhsbcx.taxorgcode, sBuf, sizeof(stYhsbcx.taxorgcode));
    /* 17.企业代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/CorpCode", sBuf)
    pstrcopy(stYhsbcx.corpcode, sBuf, sizeof(stYhsbcx.corpcode));
    /* 18.纳税人编码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/TaxPayCode", sBuf)
    pstrcopy(stYhsbcx.taxpaycode, sBuf, sizeof(stYhsbcx.taxpaycode));
    /* 19.外部申报电子序号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/OuterLevyNo", sBuf)
    pstrcopy(stYhsbcx.outerlevyno, sBuf, sizeof(stYhsbcx.outerlevyno));
    /* 20.附言 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AddWord", sBuf)
    pstrcopy(stYhsbcx.addword, sBuf, sizeof(stYhsbcx.addword));
    /* 21.交易金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyje", sBuf)
    stYhsbcx.jyje=atof(sBuf);
    /* 23.交易明细数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/DetailNum", sBuf)
    stYhsbcx.detailnum = atoi(sBuf);
    /* 24.处理结果 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Result", sBuf)
    pstrcopy(stYhsbcx.result, sBuf, sizeof(stYhsbcx.result));
    /* 25.税票信息文件名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/spxxwjm", sBuf)
    pstrcopy(stYhsbcx.spxxwjm, sBuf, sizeof(stYhsbcx.spxxwjm));
		      
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_yhsbcx", SD_TIPS_YHSBCX, NUMELE(SD_TIPS_YHSBCX), &stYhsbcx, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24233, "初始化银行申报查询表数据失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("初始化银行申报查询表数据失败"), fpub_GetCompname(lXmlhandle))      
    }
		/* end add dci 20141103 */
		
		/* dci mod 20141103 
    EXEC SQL INSERT INTO tips_yhsbcx  VALUES (:stYhsbcx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24233, "初始化银行申报查询表数据失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("初始化银行申报查询表数据失败"), fpub_GetCompname(lXmlhandle))      
    }	 
    */   

    fpub_SetMsg(lXmlhandle, 0, "初始化银行申报查询表数据成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("初始化银行申报查询表数据成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_GenSBCXHZ
组件名称: 生成申报查询回执
组件功能: 
  生成申报查询回执
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
发布日期: 2009年02月24日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_GenSBCXHZ(HXMLTREE lXmlhandle)
{
    int iParas;
    int iflag=0;
    int iCount=0;
    int smcount=0;
    char sBuf[256];/* 临时变量 */
    char sBuf2[256];
    char sBuf3[256];
    char szBuf[256];
    char sRoot[256];
    char sFileName[256];
    double dTaxAmt=0.00;
    double dTaxAmt2=0.00;
    FILE *fp;    
    int i;
    int iret=0;
    int j;

    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")  
    #endif
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 

    memset(sRoot,0,sizeof(sRoot));
    memset(sBuf,0,sizeof(sBuf));
    memset(sBuf2,0,sizeof(sBuf2));
    memset(sBuf3,0,sizeof(sBuf3));
    memset(szBuf,0,sizeof(szBuf));
    
    COMP_PARACOUNTCHK(1)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"文件名");
    pstrcopy(sFileName, sBuf, sizeof(sFileName));
    trim(sFileName);

    /*新建文件*/
    fp=fopen(sFileName,"w");
    if ( fp == NULL )
    {
        fclose(fp);
        fpub_SetMsg(lXmlhandle, 24234, "建立申报查询回执文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("建立申报查询回执文件失败[%s]", strerror(errno)), 
            fpub_GetCompname(lXmlhandle))      
    }
    
    /*生成文件头*/
    fprintf(fp,"                     银行端申报查询回执\n\n");    
    /********************获取申报回执报文数据******************************/
    /*商业银行行号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/BankNo",sBuf)
    trim(sBuf);
    /*原委托日期*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/OriEntrustDate",sBuf2)
    trim(sBuf2);
    /*原查询序号*/
    memset(szBuf, 0x00, sizeof(szBuf));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/OriQueryNo",szBuf)
    trim(szBuf);
    fprintf(fp," 商业银行行号: %-12.12s   原委托日期: %-8.8s  原查询序号: %-8.8s \n",sBuf,sBuf2,szBuf);

    /*处理结果*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/Result",sBuf)
    trim(sBuf);
    /*附言*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/AddWord",sBuf2)
    trim(sBuf2);
    fprintf(fp,"     处理结果: %-5.5s          附言: %s \n",sBuf,sBuf2);

    /*征收机关代码*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/TaxOrgCode",sBuf)
    trim(sBuf);
    /*企业代码*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/CorpCode",sBuf2)
    trim(sBuf2);
    /*纳税人编码*/
    memset(szBuf, 0x00, sizeof(szBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/TaxPayCode",szBuf)
    trim(szBuf);
    fprintf(fp," 征收机关代码: %-12.12s   企业代码: %-20.20s\n",sBuf,sBuf2);
    fprintf(fp,"   纳税人编码: %-20.20s \n\n",szBuf);

    /*外部申报电子序号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/OuterLevyNo",sBuf)
    trim(sBuf);
    /*交易金额*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/TraAmt",sBuf2)
    dTaxAmt=atof(sBuf2);
    /*明细条数*/
    memset(szBuf, 0x00, sizeof(szBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/DetailNum",szBuf)
    iCount=atoi(szBuf);
    fprintf(fp," 外部申报电子序号: %-20.20s  交易金额: %.2f  明细条数: %s \n\n",sBuf,dTaxAmt,szBuf);
   
    /*循环取税种明细信息*/
    for(i=1; i<=iCount; i++)
    {
        /*税种代码*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxTypeCode",i);
        COMP_SOFTGETXML(sRoot,sBuf)
        trim(sBuf);
        /*税种名称*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf2, 0x00, sizeof(sBuf2));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxTypeName",i);
        COMP_SOFTGETXML(sRoot,sBuf2)
        trim(sBuf2);
        /*税款所属类型*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(szBuf, 0x00, sizeof(szBuf));   	  
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxType",i);
        COMP_SOFTGETXML(sRoot,szBuf)
        trim(szBuf);
        memset(sBuf3, 0x00, sizeof(sBuf3));
        if ( strcmp(szBuf,"1") == 0 )
          strcpy(sBuf3,"当期收入");
        else if ( strcmp(szBuf,"2") == 0 )
          strcpy(sBuf3,"补缴欠税");
        else if ( strcmp(szBuf,"3") == 0 )
          strcpy(sBuf3,"三代结缴(委托代征、代扣、代售)");
        else if ( strcmp(szBuf,"4") == 0 )
          strcpy(sBuf3,"检查补税");
        trim(sBuf3);  
        fprintf(fp," 税种代码: %-10.10s  税种名称: %s  税款所属类型: %s \n",sBuf,sBuf2,sBuf3);
        /*税款起始日期*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxStartDate",i);
        COMP_SOFTGETXML(sRoot,sBuf)
        trim(sBuf);
        /*税款终止日期*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf2, 0x00, sizeof(sBuf2));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxEndDate",i);
        COMP_SOFTGETXML(sRoot,sBuf2)
        trim(sBuf2);
        /*明细条数*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(szBuf, 0x00, sizeof(szBuf));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/DetailNum",i);
        COMP_SOFTGETXML(sRoot,szBuf)
        smcount=atoi(szBuf);
        fprintf(fp," 税款起始日期: %-8.8s  税款终止日期: %-8.8s 明细条数: %s\n",sBuf,sBuf2,szBuf);
   	  
        /*再循环取税目明细信息*/
        for(j=1; j<=smcount; j++)
        {
            /*税目代码*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxSubjectCode",i,j);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            /*课税数量*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf2, 0x00, sizeof(sBuf2));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxNumber",i,j);
            COMP_SOFTGETXML(sRoot,sBuf2)
            trim(sBuf2);
            /*课税金额*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf3, 0x00, sizeof(sBuf3));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxAmt",i,j);
            COMP_SOFTGETXML(sRoot,sBuf3)
            dTaxAmt=atof(sBuf3);
            /*实缴税额*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(szBuf, 0x00, sizeof(szBuf));            
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/FactTaxAmt",i,j);
            COMP_SOFTGETXML(sRoot,szBuf)
            dTaxAmt2=atof(szBuf);
            fprintf(fp,"     税目代码: %s    课税数量: %s    课税金额: %.2f  实缴税额: %.2f \n\n",sBuf,sBuf2,dTaxAmt,dTaxAmt2);
        }
    }
    /*关闭文件指针*/
    fclose(fp);

    fpub_SetMsg(lXmlhandle, 0, "生成申报查询回执成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("生成申报查询回执成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_Cov1009TO2090
组件名称: 将原税票信息1009节点转换到2090节点上
组件功能: 
  将原税票信息1009节点转换到2090节点上
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
发布日期: 2009年02月24日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_Cov1009TO2090(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[256];
    char sTmpNode[255];
    char sNodeTmpRoot[56];
    char sNodeMXRoot[56];
    int i;
    int k;
    int ilen;
    int iflag1;
    int iflag2;
    double dSumFactTaxAmt=0.00;
    int iProjectNum=0;
    int iDetailNum=0;
    
    fpub_InitSoComp(lXmlhandle);

    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(2)
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sNodeTmpRoot, 0x00, sizeof(sNodeTmpRoot));
    COMP_GETPARSEPARAS(1,sBuf,"1009明细存放节点"); 
    pstrcopy(sNodeTmpRoot, sBuf, sizeof(sNodeTmpRoot));
    trim(sNodeTmpRoot);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sNodeMXRoot, 0x00, sizeof(sNodeMXRoot));
    COMP_GETPARSEPARAS(2,sBuf,"2090明细存放节点");
    pstrcopy(sNodeMXRoot, sBuf, sizeof(sNodeMXRoot)); 
    trim(sNodeMXRoot);
    
    LOG(LM_STD,Fmtmsg("  -->将原税票信息1009节点转换到2090节点上,1009存放节点[%s],2090存放节点[%d]",
        sNodeTmpRoot,sNodeMXRoot),fpub_GetCompname(lXmlhandle));   

    /*获得明细节点个数*/
    iProjectNum=0;
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTmpNode,0x00,sizeof(sTmpNode));
    snprintf(sTmpNode,sizeof(sTmpNode),"%s/DetailNum",sNodeTmpRoot);
    COMP_SOFTGETXML(sTmpNode,sBuf);
    iProjectNum = atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("  -->取子节点[%s]个数[%d]",sTmpNode,iProjectNum),fpub_GetCompname(lXmlhandle));
    
    /*循环获得税种明细*/
    for (i=1,iflag1=0;i<=iProjectNum;i++)
    {
        /*设置ProjectId 项目序号*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/ProjectId",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/ProjectId",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*设置TaxTypeCode 税种代码*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxTypeCode",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxTypeCode",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*设置TaxStartDate 税款所属日期起*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxStartDate",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxStartDate",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*设置TaxEndDate 税款所属日期止*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxEndDate",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxEndDate",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*设置TaxType 税款类型*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxType",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxType",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*获取DetailNum 明细条数*/
        iDetailNum=0;
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/DetailNum",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        iDetailNum = atoi(sBuf);
        /*循环设置税目明细*/
        dSumFactTaxAmt = 0.00;
        for (k=1,iflag2=0;k<=iDetailNum;k++)
        {
            /*获取FactTaxAmt 实缴税额*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/FactTaxAmt",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            dSumFactTaxAmt = dSumFactTaxAmt + atof(sBuf);
        }
        /*设置TaxTypeAmt 税种金额*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxTypeAmt",sNodeMXRoot,i);
        snprintf(sBuf, sizeof(sBuf), "%.2f", dSumFactTaxAmt);
        COMP_HARDSETXML(sTmpNode,sBuf); 
        
        /*设置DetailNum 明细条数*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/DetailNum",sNodeMXRoot,i);     
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%d", iDetailNum);
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*循环设置税目明细*/
        for (k=1,iflag2=0;k<=iDetailNum;k++)
        {
            /*设置DetailNo 明细序号*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/DetailNo",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/DetailNo",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);       
            /*设置TaxSubjectCode 税目代码*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxSubjectCode",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxSubjectCode",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
            /*设置TaxNumber 课税数量*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxNumber",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxNumber",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
            /*设置TaxAmt 计税金额*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxAmt",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxAmt",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
            /*设置FactTaxAmt 实缴税额*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/FactTaxAmt",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/FactTaxAmt",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
        }               
    }    
    fpub_SetMsg(lXmlhandle, 0, "生成申报查询回执成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("生成申报查询回执成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_QrySFXY
组件名称: 查询三方协议
组件功能: 
  查询三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年3月3日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_QrySFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sSql[512];
        char sProtocolNo[60+1];/* 协议书号 */
        char sTaxOrgCode[12+1];/* 征收机关代码 */
        char sTaxPayCode[20+1];/* 纳税人编码 */
        char sPayAcct[32+1];/* 付款账号 */
        char sPayBkCode[12+1];/* 付款行行号 */
        char sHandOrgName[200+1];/* 缴款单位名称 */
        char sGxdjrq[8+1];/* 关系登记日期 */
        char sYzbz[1+1];/* 验证标志 */
        SDB_TIPS_WTGXDJ stWtgxdj;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    int iCount;
    int i, iflag;
    FILE *fp;
    char sFileName[256];
    char sSysDate[8+1];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */		
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(5);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    COMP_GETPARSEPARAS(3, sBuf, "纳税人编码")
    pstrcopy(sTaxPayCode, sBuf, sizeof(sTaxPayCode));
    trim(sTaxPayCode);    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(4, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct); 
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    COMP_GETPARSEPARAS(5, sBuf, "文件名称")
    pstrcopy(sFileName, sBuf, sizeof(sFileName));
    trim(sFileName);

    LOG(LM_STD,Fmtmsg("查询三方协议开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],纳税人编码[%s],付款账号[%s]", 
        sProtocolNo, sTaxOrgCode, sTaxPayCode, sPayAcct),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("文件名称[%s]", sFileName),fpub_GetCompname(lXmlhandle))

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(sSysDate, sBuf, sizeof(sSysDate));

    fp = fopen(sFileName,"w");
    if ( fp == NULL )
    {
        fpub_SetMsg(lXmlhandle,24311,"打开文件失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开文件失败errinfo=[%s]",strerror(errno)),"ERROR");
    }   

    /*打印文件头*/
    fprintf(fp,"                               TIPS三方协议查询\n");
    fprintf(fp,"                                                                                                查询时间：%8.8s\n",sSysDate);
    
    fprintf(fp,"|三方协议书号|征收机关代码| 付款行行号 |     纳税人编码     |    账户代号      |         客户名称         |建立时间| 验证标志 |\n");

 	iCount = 0;
 	memset(sSql, 0x00, sizeof(sSql));
 	snprintf(sSql, sizeof(sSql),"select protocolno,taxorgcode,paybkcode,taxpaycode,payacct,handorgname,gxdjrq,yzbz from tips_wtgxdj where 1=1");
 	if ( strlen(sProtocolNo) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and protocolno='%s'",sProtocolNo);
 	if ( strlen(sTaxOrgCode) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and taxorgcode='%s'",sTaxOrgCode);
 	if ( strlen(sTaxPayCode) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and taxpaycode='%s'",sTaxPayCode);
 	if ( strlen(sPayAcct) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and payacct='%s'",sPayAcct);
 	snprintf(sSql+strlen(sSql),sizeof(sSql)," order by protocolno ");
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
    memset(&stWtgxdj, 0x00, sizeof(stWtgxdj));
		iRet = DBFetch(cur, SD_TIPS_WTGXDJ,NUMELE(SD_TIPS_WTGXDJ),&stWtgxdj, sErrmsg );
    while( iRet > 0 )
    {
        iCount ++;
        memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
        memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
        memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
        memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
        memset(sPayAcct, 0x00, sizeof(sPayAcct));
        memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
        memset(sGxdjrq, 0x00, sizeof(sGxdjrq));
        memset(sYzbz, 0x00, sizeof(sYzbz));
        
        pstrcopy(sProtocolNo,stWtgxdj.protocolno,sizeof(sProtocolNo));
        trim(sProtocolNo);
        pstrcopy(sTaxOrgCode,stWtgxdj.taxorgcode,sizeof(sTaxOrgCode));
        trim(sTaxOrgCode);
        pstrcopy(sPayBkCode,stWtgxdj.paybkcode,sizeof(sPayBkCode));
        trim(sPayBkCode);
        pstrcopy(sTaxPayCode,stWtgxdj.taxpaycode,sizeof(sTaxPayCode));
        trim(sTaxPayCode);
        pstrcopy(sPayAcct,stWtgxdj.payacct,sizeof(sPayAcct));
        trim(sPayAcct);
        pstrcopy(sHandOrgName,stWtgxdj.handorgname,sizeof(sHandOrgName));
        trim(sHandOrgName);
        pstrcopy(sGxdjrq,stWtgxdj.gxdjrq,sizeof(sGxdjrq));
        trim(sGxdjrq);
        pstrcopy(sYzbz,stWtgxdj.yzbz,sizeof(sYzbz));
        trim(sYzbz);
        
        memset(sBuf, 0x00, sizeof(sBuf));        
        if ( sYzbz[0]=='0' )
            strcpy(sBuf,"未验证"); 
        else if ( sYzbz[0]=='1' )
            strcpy(sBuf,"已验证通过");
        else
            strcpy(sBuf,"被撤销");
        
        fprintf(fp,"|%-12.12s|%-12.12s|%-12.12s|%-20.20s|%-18.18s|%-26.26s|%-8.8s|%-10.10s|\n",
            sProtocolNo,sTaxOrgCode,sPayBkCode,sTaxPayCode,sPayAcct,sHandOrgName,sGxdjrq,sBuf);  
            
        memset(&stWtgxdj, 0x00, sizeof(stWtgxdj));
				iRet = DBFetch(cur, SD_TIPS_WTGXDJ,NUMELE(SD_TIPS_WTGXDJ),&stWtgxdj, sErrmsg );                
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
            
	/* dci mod 20141103 
 	/*prepare*
    EXEC SQL PREPARE sql_qrysfxy FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrysfxy",sqlca.sqlcode),"ERROR");    
    /*declare*
    EXEC SQL DECLARE cur_wtgxdj_qry CURSOR for sql_qrysfxy;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_wtgxdj_qry",sqlca.sqlcode),"ERROR");

    EXEC SQL OPEN cur_wtgxdj_qry;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_wtgxdj_qry", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fclose(fp);
        fpub_SetMsg(lXmlhandle,24312, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("QrySFXY打开cur_wtgxdj_qry游标失败"),
            fpub_GetCompname(lXmlhandle))
    }

    /*开始循环*
    for (i=0,iflag=0;;i++)
    {
        memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
        memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
        memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
        memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
        memset(sPayAcct, 0x00, sizeof(sPayAcct));
        memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
        memset(sGxdjrq, 0x00, sizeof(sGxdjrq));
        memset(sYzbz, 0x00, sizeof(sYzbz));
        
        EXEC SQL FETCH cur_wtgxdj_qry INTO :sProtocolNo, :sTaxOrgCode, :sPayBkCode, :sTaxPayCode, :sPayAcct, :sHandOrgName, :sGxdjrq, :sYzbz;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_wtgxdj_qry",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("QrySFXY从cur_wtgxdj_qry游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
          
        trim(sProtocolNo);
        trim(sTaxOrgCode);
        trim(sPayBkCode);
        trim(sTaxPayCode);
        trim(sPayAcct);
        trim(sHandOrgName);
        trim(sGxdjrq);
        trim(sYzbz);
        memset(sBuf, 0x00, sizeof(sBuf));        
        if ( sYzbz[0]=='0' )
            strcpy(sBuf,"未验证"); 
        else if ( sYzbz[0]=='1' )
            strcpy(sBuf,"已验证通过");
        else
            strcpy(sBuf,"被撤销");
        
        fprintf(fp,"|%-12.12s|%-12.12s|%-12.12s|%-20.20s|%-18.18s|%-26.26s|%-8.8s|%-10.10s|\n",
            sProtocolNo,sTaxOrgCode,sPayBkCode,sTaxPayCode,sPayAcct,sHandOrgName,sGxdjrq,sBuf);                  
     }     
    EXEC SQL CLOSE cur_wtgxdj_qry;    
    /* EXEC SQL FREE  cur_wtgxdj_qry; */
    fclose(fp); 
    
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"生成查询三方协议回执文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("生成查询三方协议回执文件失败iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    
    if ( i == 0 )
    {
        fpub_SetMsg(lXmlhandle,24314,"无法查到相关的三方协议信息");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("无法查到相关的三方协议信息"),
            fpub_GetCompname(lXmlhandle))        
    }
    
    fpub_SetMsg(lXmlhandle, 0, "查询三方协议关系成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("查询三方协议关系成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_DelSFXY
组件名称: 撤销三方协议
组件功能: 
  撤销三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：
   前提条件：建立、删除前、完成对账号上送主机的校验
        
        删除
          根据协议书号、查询三方协议内容
             校验三方协议字段：征收机关代号、纳税人账号、支付行行号是否和前台传送的一致
             更新协议书的委托关系状态-->1,返回成功。

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年3月3日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_DelSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sProtocolNo[60+1];/* 协议书号 */
        char sTaxOrgCode[12+1];/* 征收机关代码 */
        char sPayAcct[32+1];/* 付款账号 */
        SDB_TIPS_WTGXDJ stWtgxdj;
        SDB_TIPS_WTGXDJ stWtgxdj1;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);

    LOG(LM_STD,Fmtmsg("撤销三方协议开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct),fpub_GetCompname(lXmlhandle))

		/*
    memset(&stWtgxdj, 0x00, sizeof(stWtgxdj));
    EXEC SQL SELECT * INTO :stWtgxdj
         FROM tips_wtgxdj
		     WHERE protocolno=:sProtocolNo
           AND taxorgcode=:sTaxOrgCode
           AND payacct=:sPayAcct;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))
    }

    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetMsg(lXmlhandle, 24317, "委托关系未建立");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("委托关系未建立"),
            fpub_GetCompname(lXmlhandle))
    } 
    */
    /* add DCI 20141103 */
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    memset( &stWtgxdj, 0x00, sizeof( &stWtgxdj ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT PROTOCOLNO, TAXORGCODE, PAYBKCODE, PAYACCT, BANKPROTOCOLNO, TAXPAYCODE, \
    		PAYOPBKCODE, TAXPAYNAME, HANDORGNAME, KHH, WTGXZT, GXDJRQ, DJLSH, DJDQDH, DJJGDH, DJJYGY, DJZDDH, XGRQ, \
    		XGLSH, XGDQDH, XGJGDH, XGJYGY, XGZDDH, KZBZ, YZBZ, YZXGRQ, BYZD, OPBANKNO \
    		FROM  tips_wtgxdj WHERE \
    		protocolno='%s' AND taxorgcode='%s' AND payacct='%s'",sProtocolNo,sTaxOrgCode,sPayAcct);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))  
    /*iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_WTGXDJ, NUMELE(SD_TIPS_WTGXDJ), &stWtgxdj);*/
         
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,stWtgxdj.protocolno,stWtgxdj.taxorgcode,\
    stWtgxdj.paybkcode,stWtgxdj.payacct,stWtgxdj.bankprotocolno,stWtgxdj.taxpaycode,stWtgxdj.payopbkcode,\
    stWtgxdj.taxpayname,stWtgxdj.handorgname,stWtgxdj.khh,stWtgxdj.wtgxzt,stWtgxdj.gxdjrq,stWtgxdj.djlsh,\
    stWtgxdj.djdqdh,stWtgxdj.djjgdh,stWtgxdj.djjygy,stWtgxdj.djzddh,stWtgxdj.xgrq,stWtgxdj.xglsh,\
    stWtgxdj.xgdqdh,stWtgxdj.xgjgdh,stWtgxdj.xgjygy,stWtgxdj.xgzddh,stWtgxdj.kzbz,stWtgxdj.yzbz,stWtgxdj.yzxgrq,\
    stWtgxdj.byzd,stWtgxdj.opbankno);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24317, "委托关系未建立");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("委托关系未建立"),
            fpub_GetCompname(lXmlhandle))    
    }
    /* end add DCI 20141103 */   
    
    /*已验证的协议不能删除--BEGIN 20120804 wangw*/
    if ( strncmp(stWtgxdj.yzbz,"0",1) )   
    {
        fpub_SetMsg(lXmlhandle, 24320, "已验证的协议不能删除");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("已验证的协议不能删除"),
            fpub_GetCompname(lXmlhandle))
    }
    /*已验证的协议不能删除--END 20120804 wangw*/
		
    /*修改流水号 */
    COMP_SOFTGETXML("/pub/zhqzlsh",stWtgxdj.xglsh);
    /*修改日期 */
    COMP_SOFTGETXML("/sys/sysdate",stWtgxdj.xgrq);
    /*修改机构代号 */
    COMP_SOFTGETXML("/pub/jgdh",stWtgxdj.xgjgdh);
    /*修改地区代号 */
    COMP_SOFTGETXML("/pub/dqdh",stWtgxdj.xgdqdh);
    /*修改交易柜员 */
    COMP_SOFTGETXML("/pub/jygy",stWtgxdj.xgjygy);
    
    /*插入记录到历史委托关系表 */	
    /*	
    EXEC SQL INSERT INTO tips_wtgxdjlsls VALUES(:stWtgxdj); 
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24318, "插入历史委托记录失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入历史委托记录失败"),
            fpub_GetCompname(lXmlhandle))
    }*/
    /* add DCI 20141103 */
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdjlsls", SD_TIPS_WTGXDJLSLS, NUMELE(SD_TIPS_WTGXDJLSLS), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24318, "插入历史委托记录失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入历史委托记录失败"),
            fpub_GetCompname(lXmlhandle))
    }
    /* end add DCI 20141103*/
    
    /* 删除三方协议 */
    /* DCI MOD 20141103
    EXEC SQL delete FROM tips_wtgxdj 
         WHERE protocolno=:sProtocolNo
           AND taxorgcode=:sTaxOrgCode
           AND payacct=:sPayAcct;        
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24319, "删除三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除三方协议失败"),
            fpub_GetCompname(lXmlhandle))
    }*/
    
    /* ADD DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "delete FROM  tips_wtgxdj WHERE \
    		protocolno='%s' AND taxorgcode='%s' AND payacct='%s'",sProtocolNo,sTaxOrgCode,sPayAcct);
    iRet = DCIExecuteDirect(sSql1);
    if( iRet < 0 )
    {
    		fpub_SetMsg(lXmlhandle, 24319, "删除三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除三方协议失败"),
            fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "删除三方协议成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("删除三方协议成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_AddSFXY
组件名称: 签约三方协议
组件功能: 
  签约三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：
   前提条件：建立、删除前、完成对账号上送主机的校验
        1 建立
          征收机关校验
          查询征收机关、纳税人账号、支付行行号记录是否存在。
            存在->判断协议书号是否和前台传送的一致，
                     一致，修改委托关系状态->0，返回成功
                     不一致,交易失败，征收机关、纳税人账号、支付行行号对应关系已存在。                                                      
            不存在，继续
          查询协议书号在数据库中是否已存在、
            存在->交易失败,协议书对应的征收机关、纳税人账号、支付行行号记录不符。 
            不存在->新增三方协议。

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年3月3日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_AddSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sProtocolNo[60+1];/* 协议书号 */
        char sTaxOrgCode[12+1];/* 征收机关代码 */
        char sPayAcct[32+1];/* 付款账号 */
        char sPayBkCode[12+1];/* 付款行行号 */
        char sPayOpBkCode[12+1];/* 付款开户行号 */
        char sYzbz_tmp[1+1];
        SDB_TIPS_WTGXDJ stWtgxdj;
        SDB_TIPS_WTGXDJ stWtgxdj1;
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */  
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "付款行行号")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("签约三方协议开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s],付款行行号[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))
				
    /* 查询征收机关是否存在 */
    /* mod DCI 注释20141103
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_taxcodeinfo  
	     WHERE taxorgcode=:sTaxOrgCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24321, "查询征收机关代码失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询征收机关代码失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "征收机关代码不存在");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码不存在"),
            fpub_GetCompname(lXmlhandle))        
    }*/
    /* add DCI 20141103 */
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_taxcodeinfo WHERE taxorgcode='%s'",sTaxOrgCode);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24321, "查询征收机关代码失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询征收机关代码失败"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "征收机关代码不存在");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码不存在"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* end add DCI 20141103 */    

    /* 查询付款行行号是否存在 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_qshdj  
	     WHERE paybkcode=:sPayBkCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24323, "查询商业银行清算行登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询商业银行清算行登记表失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款行行号未初始化");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号未初始化"),
            fpub_GetCompname(lXmlhandle))        
    }*/
    /* add DCI 20141103 */
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_qshdj WHERE paybkcode='%s'",sPayBkCode);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24323, "查询商业银行清算行登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询商业银行清算行登记表失败"),
            fpub_GetCompname(lXmlhandle))
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款行行号未初始化");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号未初始化"),
            fpub_GetCompname(lXmlhandle)) 
    }
    /* end add DCI 20141103 */ 

    /* 查询是否已签约 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_wtgxdj  
	     WHERE taxorgcode=:sTaxOrgCode
	       AND paybkcode=:sPayBkCode
	       AND payacct=:sPayAcct;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount != 0 )
    {
        fpub_SetMsg(lXmlhandle, 24325, "三方协议已存在,签约失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("3三方协议已存在,签约失败"),
            fpub_GetCompname(lXmlhandle))        
    }*/    

    /* 查询是否已签约 */
    /*iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_wtgxdj  
	     WHERE protocolno=:sProtocolNo;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount > 0 )
    {
			  EXEC SQL SELECT yzbz INTO :sYzbz_tmp 
				     FROM  tips_wtgxdj  
				     WHERE protocolno=:sProtocolNo;
				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
				trim(sYzbz_tmp); 
		    if( strcmp(sYzbz_tmp,"2")==0 )
		    {
				    EXEC SQL delete FROM tips_wtgxdj 
				         WHERE protocolno=:sProtocolNo;        
				    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR"); 
				    if ( SQLERR )
				    {
				        fpub_SetMsg(lXmlhandle, 24319, "删除三方协议失败");
				        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除三方协议失败"),
				            fpub_GetCompname(lXmlhandle))
				    }
		    }   
				else
				{
		        fpub_SetMsg(lXmlhandle, 24325, "三方协议已存在,签约失败");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1三方协议已存在,签约失败"),
		            fpub_GetCompname(lXmlhandle))        
				}
    }*/
    /* add DCI 20141103 */
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT count(*) FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);     	
    iRet = DBSelectToVar( sErrmsg, &iCount, sSql1) ; 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))
    }
    if ( iCount > 0 )
    {
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "SELECT yzbz FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);     	
    		iRet = DBSelectToVar( sErrmsg, &sYzbz_tmp, sSql1) ;    		 
        trim(sYzbz_tmp); 
		    if( strcmp(sYzbz_tmp,"2")==0 )
        {
        	memset( sSql1, 0x00, sizeof( sSql1 ) );
        	snprintf( sSql1, sizeof(sSql1), "delete FROM tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
        	iRet = DCIExecuteDirect(sSql1);
	     		if ( iRet < 0 )
	     		{
	     			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        		
	     			fpub_SetMsg(lXmlhandle, 24319, "删除三方协议失败");
				    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				    LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除三方协议失败"),
				            fpub_GetCompname(lXmlhandle))
	     		}
	     	}
	     	else
				{
		        fpub_SetMsg(lXmlhandle, 24325, "三方协议已存在,签约失败");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议已存在,签约失败"),
		            fpub_GetCompname(lXmlhandle))        
				}     	
    }
    /* end add DCI 20141103 */ 

    /*协议书号未曾使用,开始增加三方协议*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    /* 生成银行协议书序号 */
    iRet = 0;
    memset(sBankProNo,0x00,sizeof(sBankProNo));
    iRet = prv_tips_genxh2(1,sBuf,sBankProNo);
    if (iRet < 0)
    {
        fpub_SetMsg(lXmlhandle, 24326, "生成银行内部协议号失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("生成银行内部协议号失败"),
            fpub_GetCompname(lXmlhandle)) 
    }
    trim(sBankProNo);
		COMP_SOFTSETXML("/tips/BANKProtocolNo",sBankProNo)
		
    memset(&stWtgxdj,0,sizeof(stWtgxdj));
      
    /*银行协议书号*/
    pstrcopy(stWtgxdj.bankprotocolno,sBankProNo,sizeof(stWtgxdj.bankprotocolno));
    /*委托关系状态*/ 
    stWtgxdj.wtgxzt[0]='0';
    /*协议书号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/ProtocolNo",sBuf)
    pstrcopy(stWtgxdj.protocolno, sBuf, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "协议书号为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("协议书号为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*征收机关代码*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode",sBuf)
    pstrcopy(stWtgxdj.taxorgcode, sBuf, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "征收机关代码为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*纳税人编码*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人编码为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人编码为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*纳税人名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
     if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人名称为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人名称为空"),
            fpub_GetCompname(lXmlhandle))        
    }
   /*缴款单位名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
     if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "缴款单位名称为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("缴款单位名称为空"),
            fpub_GetCompname(lXmlhandle))        
    }
   /* 付款行行号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode",sBuf)
    pstrcopy(stWtgxdj.paybkcode, sBuf, sizeof(stWtgxdj.paybkcode));
     if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款行行号为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号为空"),
            fpub_GetCompname(lXmlhandle))        
    }
   /* 付款帐户*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct",sBuf)
    pstrcopy(stWtgxdj.payacct, sBuf, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款帐户为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款帐户为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*客户代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));
    /*关系登记日期*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/gxdjrq",sBuf)		/* 20150803 /tips/zwrq 修改为/tips/gxdjrq */
    pstrcopy(stWtgxdj.gxdjrq, sBuf, sizeof(stWtgxdj.gxdjrq));
    
    /*登记流水号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.djlsh, sBuf, sizeof(stWtgxdj.djlsh));
    /*机构代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.djjgdh, sBuf, sizeof(stWtgxdj.djjgdh));
    /*地区代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.djdqdh, sBuf, sizeof(stWtgxdj.djdqdh));
    /*交易柜员*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.djjygy, sBuf, sizeof(stWtgxdj.djjygy));
    /*终端代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.djzddh, sBuf, sizeof(stWtgxdj.djzddh));
    /*扩展标志*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* 帐户类型 */  
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }else
        stWtgxdj.kzbz[0]='0'; 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* 钞汇标志 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }else
        stWtgxdj.kzbz[1]='0';
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* 卡折标志 P：账户 C：卡 默认是账户P add 20140901 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }else
        stWtgxdj.kzbz[2]='P'; 
    strcat(stWtgxdj.kzbz, "00000");
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s],kzbz[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, stWtgxdj.kzbz),fpub_GetCompname(lXmlhandle))    

    /*验证标志*/
    stWtgxdj.yzbz[0]='0';
    /*客户号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/khh",sBuf);
    pstrcopy(stWtgxdj.khh,sBuf,sizeof(stWtgxdj.khh)); 
    /*付款开户行机构号--20120829 wangw*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 
    /*备注--开户行机构号 管理台查询协议用 add 20150710 */
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    /*备注--开户行名称
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips_host/resp/khhmc",sBuf)
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));*/
    
    /*付款开户行行号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhhh",sBuf);
    pstrcopy(stWtgxdj.payopbkcode,sBuf,sizeof(stWtgxdj.payopbkcode));
    
    /*操作标识
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/czbz", sBuf)/* 操作标识 
    pstrcopy(stWtgxdj.czbz,sBuf,sizeof(stWtgxdj.czbz));
    
    EXEC SQL INSERT INTO tips_wtgxdjlsls VALUES(:stWtgxdj); 
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24318, "插入历史委托记录失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入历史委托记录失败"),
            fpub_GetCompname(lXmlhandle))
    }*/ 
        
    /*新增三方协议*/
    /* mod dci 20141103 
    EXEC SQL INSERT INTO tips_wtgxdj VALUES(:stWtgxdj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24327, "新增三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("新增三方协议失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdj", SD_TIPS_WTGXDJ, NUMELE(SD_TIPS_WTGXDJ), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24327, "新增三方协议失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("新增三方协议失败"),
            fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "签约三方协议成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("签约三方协议成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitPZSJ_DB
组件名称: 登记凭证数据信息(单笔)
组件功能: 
  登记凭证数据信息(单笔)
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：


组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_drls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年3月10日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPZSJ_DB(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        SDB_TIPS_DRLS stDrls;
        SDB_TIPS_TAXTYPEMX stTaxtypemx;
        char sZwrq[8+1];/* 账务日期 */
        int iZhqzlsh;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sRoot[256];
    int  iCount=0,i;
    char sXmlNodePath[200];
    char sTaxInfoPath[200];
    char sPayment3102[10240];
    int iret;
    FILE *fp;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		char sProtocolno[61];
		char sSpxx[41];
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "账务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "综合前置流水号")
    iZhqzlsh = atoi(sBuf);

    LOG(LM_STD,Fmtmsg("登记凭证数据信息(单笔)开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("账务日期[%s],综合前置流水号[%d]", 
        sZwrq, iZhqzlsh),fpub_GetCompname(lXmlhandle))

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
		memset( &stDrls, 0x00, sizeof( &stDrls ) );
		snprintf( sSql1, sizeof(sSql1), "select * from tips_drls where zwrq='%s' and zhqzlsh=%d",sZwrq,iZhqzlsh); 
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))    
    /*iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls);*/
       
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,
&stDrls.zwrq         ,
&stDrls.zhqzlsh      ,
&stDrls.jyqd         ,
&stDrls.workdate     ,
&stDrls.entrustdate  ,
&stDrls.taxorgcode   ,
&stDrls.trano        ,
&stDrls.msgno        ,
&stDrls.entrustdate2 ,
&stDrls.trano2       ,
&stDrls.zhqzlsh2     ,
&stDrls.chkdate      ,
&stDrls.chkacctord   ,
&stDrls.handletype   ,
&stDrls.trecode      ,
&stDrls.payeebankno  ,
&stDrls.payeeorgcode ,
&stDrls.payeeacct    ,
&stDrls.payeename    ,
&stDrls.paybkcode    ,
&stDrls.payopbkcode  ,
&stDrls.protocolno   ,
&stDrls.payacct      ,
&stDrls.handorgname  ,
&stDrls.dfzh         ,
&stDrls.jyje         ,
&stDrls.taxvouno     ,
&stDrls.dqdh         ,
&stDrls.jgdh         ,
&stDrls.jygy         ,
&stDrls.zddh         ,
&stDrls.jyrq         ,
&stDrls.jysj         ,
&stDrls.zjrq         ,
&stDrls.zjsj         ,
&stDrls.zjlsh        ,
&stDrls.zjxym        ,
&stDrls.zjxyxx       ,
&stDrls.sxf          ,
&stDrls.zhye         ,
&stDrls.xym          ,
&stDrls.xyxx         ,
&stDrls.jyzt         ,
&stDrls.dzbz         ,
&stDrls.qsbz         ,
&stDrls.kzbz         ,
&stDrls.taxpaycode   ,
&stDrls.taxpayname   ,
&stDrls.spxx         ,
&stDrls.byzd          );
        
    LOG(LM_STD,Fmtmsg("ZWRQ         [%s]",stDrls.zwrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH      [%d]",stDrls.zhqzlsh     ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYQD         [%s]",stDrls.jyqd        ),"INFO") 
    LOG(LM_STD,Fmtmsg("WORKDATE     [%s]",stDrls.workdate    ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE  [%s]",stDrls.entrustdate ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXORGCODE   [%s]",stDrls.taxorgcode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO        [%s]",stDrls.trano       ),"INFO") 
    LOG(LM_STD,Fmtmsg("MSGNO        [%s]",stDrls.msgno       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE2 [%s]",stDrls.entrustdate2),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO2       [%s]",stDrls.trano2      ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH2     [%d]",stDrls.zhqzlsh2    ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKDATE      [%s]",stDrls.chkdate     ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKACCTORD   [%s]",stDrls.chkacctord  ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDLETYPE   [%s]",stDrls.handletype  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRECODE      [%s]",stDrls.trecode     ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEBANKNO  [%s]",stDrls.payeebankno ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEORGCODE [%s]",stDrls.payeeorgcode),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEACCT    [%s]",stDrls.payeeacct   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEENAME    [%s]",stDrls.payeename   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYBKCODE    [%s]",stDrls.paybkcode   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYOPBKCODE  [%s]",stDrls.payopbkcode ),"INFO") 
    LOG(LM_STD,Fmtmsg("PROTOCOLNO   [%s]",stDrls.protocolno  ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYACCT      [%s]",stDrls.payacct     ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDORGNAME  [%s]",stDrls.handorgname ),"INFO") 
    LOG(LM_STD,Fmtmsg("DFZH         [%s]",stDrls.dfzh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYJE         [%f]",stDrls.jyje        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXVOUNO     [%s]",stDrls.taxvouno    ),"INFO") 
    LOG(LM_STD,Fmtmsg("DQDH         [%s]",stDrls.dqdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JGDH         [%s]",stDrls.jgdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYGY         [%s]",stDrls.jygy        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZDDH         [%s]",stDrls.zddh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYRQ         [%s]",stDrls.jyrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYSJ         [%s]",stDrls.jysj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJRQ         [%s]",stDrls.zjrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJSJ         [%s]",stDrls.zjsj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJLSH        [%s]",stDrls.zjlsh       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYM        [%s]",stDrls.zjxym       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYXX       [%s]",stDrls.zjxyxx      ),"INFO") 
    LOG(LM_STD,Fmtmsg("SXF          [%f]",stDrls.sxf         ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHYE         [%f]",stDrls.zhye        ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYM          [%s]",stDrls.xym         ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYXX         [%s]",stDrls.xyxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYZT         [%s]",stDrls.jyzt        ),"INFO") 
    LOG(LM_STD,Fmtmsg("DZBZ         [%s]",stDrls.dzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("QSBZ         [%s]",stDrls.qsbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("KZBZ         [%s]",stDrls.kzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYCODE   [%s]",stDrls.taxpaycode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYNAME   [%s]",stDrls.taxpayname  ),"INFO") 
    LOG(LM_STD,Fmtmsg("SPXX         [%s]",stDrls.spxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("BYZD         [%s]",stDrls.byzd        ),"INFO") 
    
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24201, "查询当日流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
		/* end add dci */
		
		/* dci mod 20141103 
    memset(&stDrls, 0x00, sizeof(stDrls));    
    EXEC SQL SELECT * INTO :stDrls
        FROM tips_drls
        WHERE  zwrq = :sZwrq
          AND  zhqzlsh = :iZhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24201, "查询当日流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
    
    /* 税票信息 */
    memset(sPayment3102, 0x00, sizeof(sPayment3102));
    memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
    /* mod by tuql 20090505 由支持单一的3001修改为支持3001或1008 */
    if (strcmp(stDrls.msgno, "3001") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment3001");   
    
        if ( (iret=xml_ExportXMLString(lXmlhandle,sPayment3102,sizeof(sPayment3102),sXmlNodePath,1 )) == -1 )
        {
             fpub_SetMsg(lXmlhandle, 24211, "获取税票信息失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("获取税票信息失败[%s]", sXmlNodePath), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;        
        }
        /* 把税票信息存放到文件中去 */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));/* 存放的文件名 */
        snprintf(sXmlNodePath, sizeof(sXmlNodePath), "spxx_%s_%d",sZwrq, iZhqzlsh);
        trim(sXmlNodePath);
        snprintf(sTaxInfoPath, sizeof(sTaxInfoPath), "%s/file/tips/spxx/%s", getenv("HOME"), sXmlNodePath);
        fp = fopen(sTaxInfoPath, "w+");
        if ( fp==NULL )
        {
             fpub_SetMsg(lXmlhandle, 24212, "打开税票信息文件失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("打开税票信息文件失败"), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;        
        }
        fprintf(fp, "%s\n", sPayment3102); 
        fclose(fp);
        
        pstrcopy(stDrls.spxx, sXmlNodePath, sizeof(stDrls.spxx));        
        COMP_SOFTSETXML("/tips/spxx", sXmlNodePath)

		    /*明细条数*/
		    memset(sBuf, 0x00, sizeof(sBuf));
		    COMP_SOFTGETXML("/tips/MSG/Payment3001/TaxTypeNum",sBuf)
		    iCount=atoi(sBuf);
		   
		    /*循环取税种明细信息*/
		    for(i=1; i<=iCount; i++)
		    {
		    	  
		        memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
    				pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
    				pstrcopy(stTaxtypemx.jylsh, stDrls.trano, sizeof(stTaxtypemx.jylsh));
    				pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));
    				LOG(LM_STD,Fmtmsg("jyrq[%s]",stTaxtypemx.jyrq),fpub_GetCompname(lXmlhandle))
    				LOG(LM_STD,Fmtmsg("jylsh[%s]",stTaxtypemx.jylsh),fpub_GetCompname(lXmlhandle))

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment3001/TaxTypeList3001|%d/ProjectId",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeName",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));   	  
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxStartDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxEndDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeAmt",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypeamt, sBuf, sizeof(stTaxtypemx.taxtypeamt));
						
						LOG(LM_STD,Fmtmsg("i[%d],jyrq[%s],jylsh[%s],projectid[%s]",i,stTaxtypemx.jyrq,stTaxtypemx.jylsh,stTaxtypemx.projectid),"INFO") 
						/* add dci 20141103 */
						memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					fpub_SetMsg(lXmlhandle, 24327, "插入税种明细表失败");
      				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入税种明细表失败"),
            		fpub_GetCompname(lXmlhandle))
    				}
						/* end dci 20141103*/
						
						/* mod dci 20141103
						EXEC SQL INSERT INTO TIPS_TAXTYPEMX	VALUES(:stTaxtypemx);
				    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
				    if ( SQLERR )
				    {
				         fpub_SetMsg(lXmlhandle, 24201, "插入税种明细表失败");
				         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				         LOG(LM_STD, Fmtmsg("插入税种明细表失败"), fpub_GetCompname(lXmlhandle))	
				         return COMPRET_FAIL ;        
				    }
				    */
				                
		    }
		    
		    /* add dci 20141103 只有3001报文需要更新tips_drls的spxx 20141204修改 
		    1008的报文申报时就已经生成税票并写入tips_drls的spxx
		    */      
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_drls set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);     	
    		LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        	fpub_SetMsg(lXmlhandle, 24201, "更新当日流水表失败");
         	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         	LOG(LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))	
         	return COMPRET_FAIL ;        
    		}
    		/* end add dci 20141103 */
		    
    }else if (strcmp(stDrls.msgno, "1008") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment1008");  
        
		    /*明细条数*/
		    memset(sBuf, 0x00, sizeof(sBuf));
		    COMP_SOFTGETXML("/tips/MSG/Payment1008/TaxTypeNum",sBuf)
		    iCount=atoi(sBuf);
		   
		    /*循环取税种明细信息*/
		    for(i=1; i<=iCount; i++)
		    {
						LOG(LM_STD,Fmtmsg("插入税种明细表开始..."),fpub_GetCompname(lXmlhandle))
		        memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
    				pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
    				pstrcopy(stTaxtypemx.jylsh, stDrls.trano, sizeof(stTaxtypemx.jylsh));
    				pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/ProjectId",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeName",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));   	  
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxStartDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxEndDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeAmt",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypeamt, sBuf, sizeof(stTaxtypemx.taxtypeamt));

						LOG(LM_STD,Fmtmsg("插入税种明细表开始..."),fpub_GetCompname(lXmlhandle))
						
						/* add dci 20141103 */
						memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					fpub_SetMsg(lXmlhandle, 24327, "插入税种明细表失败");
      				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入税种明细表失败"),
            		fpub_GetCompname(lXmlhandle))
    				}
						/* end dci 20141103*/
						
						/* dci mod 20141103
				    EXEC SQL INSERT INTO TIPS_TAXTYPEMX	VALUES(:stTaxtypemx);
				    LOG(LM_STD,Fmtmsg("插入税种明细表开始...111"),fpub_GetCompname(lXmlhandle))
				    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
				    if ( SQLERR )
				    {
				         fpub_SetMsg(lXmlhandle, 24201, "插入税种明细表失败");
				         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				         LOG(LM_STD, Fmtmsg("插入税种明细表失败"), fpub_GetCompname(lXmlhandle))	
				         return COMPRET_FAIL ;        
				    }   
				    */         
		    }

    }else
    {
         fpub_SetMsg(lXmlhandle, 24211, Fmtmsg("不支持此报文编号[%s]的实时凭证", stDrls.msgno));
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("不支持此报文编号[%s]的实时凭证", stDrls.msgno), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }            
    
    /* 插入单笔凭证数据 */
    LOG(LM_STD,Fmtmsg("插入凭证数据开始"),fpub_GetCompname(lXmlhandle))       
    iret = prv_tips_InitPZSJ_db(lXmlhandle, stDrls);
    if ( iret < 0 )
    {
         fpub_SetMsg(lXmlhandle, 24213, "新增凭证信息失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("新增凭证信息失败[%d]", iret), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    LOG(LM_STD,Fmtmsg("插入凭证数据结束"),fpub_GetCompname(lXmlhandle))  
            
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_drls \
    		set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")            	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24201, "更新当日流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    
    iRet =DCICommit();
    /* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"), 
            fpub_GetCompname(lXmlhandle))    
    }
    */
    
    /* end dci */
    
    /* dci mod 20141103
    EXEC SQL UPDATE tips_drls
        SET spxx=:stDrls.spxx
        WHERE  zwrq = :sZwrq
          AND  zhqzlsh = :iZhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24201, "更新当日流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }         
    */
       
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("登记凭证数据信息(单笔)处理结束"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;       
}


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_Init2090FromSblr
组件名称: 根据申报录入数据生成2090准备数据
组件功能: 
   
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

日志信息: 
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息
  
主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 金融·产品三部
程 序 员: xiahl
发布日期: 2005-10-24 20:13
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_Init2090FromSblr(HXMLTREE lXmlhandle)
{
   char sbuf[255],snode_dataroot[255],snode_mxroot[50],sbuf2[255];
   char stmpnode[255];
   int ilen,iParas,iProjectNum=0,iDetailNum=0;
   int i,k,iflag1,iflag2;
   double dSumFactTaxAmt=0.00,tmpAmt=0.00;
   
   fpub_InitSoComp(lXmlhandle);
   
#ifdef DEBUG
   LOG(LM_STD,Fmtmsg("  根据申报录入数据生成2090准备数据开始-->"),"INFO");
#endif

   /*获取组件参数  --S*/
   COMP_PARACOUNTCHK(3)
   
   /*XML源值*/
   COMP_GETPARSEPARAS(1,snode_dataroot,"明细录入存放根节点");
   COMP_GETPARSEPARAS(2,snode_mxroot,"2090明细存放节点");	
   /*获得明细节点个数*/
   iProjectNum=0;
   COMP_SOFTGETXML("/tips/DetailNum",sbuf);
   iProjectNum = atoi(sbuf);
   
   LOG(LM_STD,Fmtmsg("  -->取子节点/tips/jls个数[%d]",iProjectNum),"INFO");
   
   if (iProjectNum == 0)
   {
   		 LOG(LM_STD,Fmtmsg("  -->申报明细记录不能为0!"),"ERROR");
		   fpub_SetCompStatus(lXmlhandle,1);
		   fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申报明细记录不能为0!"));
		   return 1;
   }
   
   /*循环获得税种明细*/
   for (i=1,iflag1=0;i<=iProjectNum;i++)
   {
   	  /*设置ProjectId 项目序号*/
   	  memset(sbuf,0,sizeof(sbuf));
   	  sprintf(sbuf,"%d",i);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/ProjectId",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*设置TaxTypeCode 税种代码*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_TYPE_CODE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxTypeCode",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 

      
      /*设置TaxStartDate 税款所属日期起*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/BUSS_START_DATE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxStartDate",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*设置TaxEndDate 税款所属日期止*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/BUSS_END_DATE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxEndDate",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*设置TaxType 税款类型*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_TYPE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxType",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*设置TaxTypeAmt 税种金额*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_TYPE_AMT",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
      tmpAmt = atof(sbuf);
      memset(sbuf,0,sizeof(sbuf));
      sprintf(sbuf,"%.2f",tmpAmt);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxTypeAmt",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf);
      dSumFactTaxAmt = dSumFactTaxAmt + atof(sbuf); 
      /*设置DetailNum 明细条数 */
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_GL_NUM",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
      iDetailNum = atoi(sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/DetailNum",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*循环设置税目明细*/
      for (k=1,iflag2=0;k<=iDetailNum;k++)
      {
          /*设置DetailNo 明细序号*/
          memset(sbuf,0,sizeof(sbuf));
          sprintf(sbuf,"%d",k);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/DetailNo",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);       
          /*设置TaxSubjectCode 税目代码*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/TAX_GL_CODE",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxSubjectCode",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);
          /*设置TaxNumber 课税数量*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/NUM",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxNumber",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);
          /*设置TaxAmt 计税金额*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/DUE_FEE",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
          tmpAmt = atof(sbuf);
          memset(sbuf,0,sizeof(sbuf));
          sprintf(sbuf,"%.2f",tmpAmt);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxAmt",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);
          /*设置FactTaxAmt 实缴税额*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/ACT_ACCEPT_AMT",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
          tmpAmt = atof(sbuf);
          memset(sbuf,0,sizeof(sbuf));
          sprintf(sbuf,"%.2f",tmpAmt);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/FactTaxAmt",snode_mxroot,i,k);
          COMP_HARDSETXML(stmpnode,sbuf);
      }
   }
   
   /*传出交易金额*/
   COMP_GETPARSEPARAS(3,sbuf,"传出交易金额节点");
   memset(sbuf2,0,sizeof(sbuf2));
   sprintf(sbuf2,"%.2f",dSumFactTaxAmt);
   COMP_HARDSETXML(sbuf,sbuf2);
   
   fpub_SetCompStatus(lXmlhandle,0);
   LOG(LM_STD,Fmtmsg("  根据申报录入数据生成2090准备数据成功-->"),"INFO");
   return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdSFXY
组件名称: 修改三方协议
组件功能: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：
   前提条件：建立、删除前、完成对账号上送主机的校验        1 建立

          查询协议书号在数据库中是否已存在、
            存在->验证协议书对应的征收机关、纳税人账号、支付行行号记录是否相符，不符的交易失败，符合的更新。 
            不存在->交易失败

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记	tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年8月3日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sProtocolNo[60+1];/* 协议书号 */
        char sProtocolno_tmp[60+1];/* 协议书号 */
        char sTaxOrgCode[12+1];/* 征收机关代码 */
        char sPayAcct[32+1];/* 付款账号 */
        char sPayBkCode[12+1];/* 付款行行号 */
        char sPayOpBkCode[12+1];/* 付款行行号 */
        SDB_TIPS_WTGXDJ stWtgxdj;
        SDB_TIPS_WTGXDJ stWtgxdj1;
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    int iret;
    
    /* add DCI 20141103 */
    char sSql1[1024];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
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

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "付款行行号")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("签约三方协议开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s],付款行行号[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))

    /* 查询是否已签约 */
    /* add dci 20141103 */
    
    memset(&stWtgxdj1, 0x00, sizeof(stWtgxdj1));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select yzbz from tips_wtgxdj where protocolno='%s' ",sProtocolNo);     	
    iRet = DBSelectToVar(sErrmsg, &stWtgxdj1.yzbz, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))   
    }
    if( iRet == 0)
    {
        fpub_SetMsg(lXmlhandle, 24325, "三方协议不存在,请用签约交易");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议不存在,请用签约交易"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* end add dci 20141103 */
    /* mod dci 20141103 
    memset(&stWtgxdj1, 0x00, sizeof(stWtgxdj1));
    EXEC SQL SELECT * INTO :stWtgxdj1 
	     FROM  tips_wtgxdj  
	     WHERE protocolno=:sProtocolNo;
		SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( SQLNOTFOUND )
    {
        fpub_SetMsg(lXmlhandle, 24325, "三方协议不存在,请用签约交易");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议不存在,请用签约交易"),
            fpub_GetCompname(lXmlhandle))        
    }
    */

    LOG(LM_STD,Fmtmsg("验证标志[%s]...",stWtgxdj1.yzbz),fpub_GetCompname(lXmlhandle))
    if( strcmp(stWtgxdj1.yzbz,"0") )
    {
        fpub_SetMsg(lXmlhandle, 24327, "该三方协议已验证或撤销，不能修改");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("该三方协议已验证或撤销，不能修改"),
            fpub_GetCompname(lXmlhandle))
    }    

    /* 查询是否已签约 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_wtgxdj  
	     WHERE taxorgcode=:sTaxOrgCode
	       AND paybkcode=:sPayBkCode
	       AND payacct=:sPayAcct;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount != 0 )
    {
			    EXEC SQL SELECT protocolno INTO :sProtocolno_tmp 
				     FROM  tips_wtgxdj  
				     WHERE taxorgcode=:sTaxOrgCode
				       AND paybkcode=:sPayBkCode
				       AND payacct=:sPayAcct;
				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
				trim(sProtocolno_tmp); 
		    if( strcmp(sProtocolno_tmp,sProtocolNo) )
		    {
		        fpub_SetMsg(lXmlhandle, 24325, "此账户已经和此征收机关有对应关系,不能重复签约");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("此账户已经和此征收机关有对应关系,不能重复签约"),
		            fpub_GetCompname(lXmlhandle))        
		    }   
    }*/    
    
    /* 查询征收机关是否存在 */
    /* mod dci 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_taxcodeinfo  
	     WHERE taxorgcode=:sTaxOrgCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24321, "查询征收机关代码失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询征收机关代码失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "征收机关代码不存在");
        LOG(LM_STD,Fmtmsg("iCount[%d],taxorgcode[%s]...",iCount,sTaxOrgCode),fpub_GetCompname(lXmlhandle))
        EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_taxcodeinfo  
	     WHERE taxorgcode=:sTaxOrgCode;
	     	LOG(LM_STD,Fmtmsg("iCount[%d],taxorgcode[%s]...",iCount,sTaxOrgCode),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码不存在"),
            fpub_GetCompname(lXmlhandle))        
    }    
		*/
    /* 查询付款行行号是否存在 */
    /* mod dci 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_qshdj  
	     WHERE paybkcode=:sPayBkCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24323, "查询商业银行清算行登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询商业银行清算行登记表失败"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款行行号未初始化");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号未初始化"),
            fpub_GetCompname(lXmlhandle))        
    }
		*/
		   
    /*开始修改三方协议*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    iret = 0;

    memset(&stWtgxdj,0,sizeof(stWtgxdj));
      

    /*委托关系状态*/ 
    stWtgxdj.wtgxzt[0]='0';
    /*协议书号*/
    pstrcopy(stWtgxdj.protocolno, sProtocolNo, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "协议书号为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("协议书号为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*征收机关代码*/
    pstrcopy(stWtgxdj.taxorgcode, sTaxOrgCode, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "征收机关代码为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码为空"),
            fpub_GetCompname(lXmlhandle))        
    }
   /*纳税人编码*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人编码为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人编码为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*纳税人名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
    if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人名称为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人名称为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*缴款单位名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
    if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "缴款单位名称为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("缴款单位名称为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* 付款行行号*/
    pstrcopy(stWtgxdj.paybkcode, sPayBkCode, sizeof(stWtgxdj.paybkcode));
    if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款行行号为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* 付款帐户*/ 
    pstrcopy(stWtgxdj.payacct, sPayAcct, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款帐户为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款帐户为空"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*客户代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));
    /*关系修改日期*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/xgrq",sBuf)		/* 20150803 /tips/zwrq 修改为/tips/xgrq */
    pstrcopy(stWtgxdj.xgrq, sBuf, sizeof(stWtgxdj.xgrq));
    
    /*修改流水号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.xglsh, sBuf, sizeof(stWtgxdj.xglsh));
    /*修改机构代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.xgjgdh, sBuf, sizeof(stWtgxdj.xgjgdh));
    /*修改地区代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.xgdqdh, sBuf, sizeof(stWtgxdj.xgdqdh));
    /*修改交易柜员*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.xgjygy, sBuf, sizeof(stWtgxdj.xgjygy));
    /*修改终端代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.xgzddh, sBuf, sizeof(stWtgxdj.xgzddh));
    /*扩展标志*/
    
    /*扩展标志 edit 20140901 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* 帐户类型 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }else
        stWtgxdj.kzbz[0]='0'; 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* 钞汇标志 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }else
        stWtgxdj.kzbz[1]='0';
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* 卡折标志 add 20140901 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }else
        stWtgxdj.kzbz[2]='C'; 
    strcat(stWtgxdj.kzbz, "00000");   
    /*客户号 重复20140808删除*/
    /*memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/khh",sBuf);
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));*/
    /*付款开户行行号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhhh",sBuf);
    pstrcopy(stWtgxdj.payopbkcode, sBuf, sizeof(stWtgxdj.payopbkcode));
    /*付款开户行机构号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 
    /*备注--开户行机构号 管理台查询协议用 add 20150710 */
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    /*备注--开户行名称
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips_host/resp/khhmc",sBuf)
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));*/
    /*验证标志*/
    stWtgxdj.yzbz[0]='0';
        
    /*付款开户行
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/tamc/req/fkkhhhh",sBuf);
    pstrcopy(stWtgxdj.payopbkcode, sBuf, sizeof(stWtgxdj.payopbkcode));*/

    /*付款开户行机构号
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/tamc/req/bz",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    LOG(LM_STD,Fmtmsg("sPayOpBkCode[%s]byzd[%s]...",stWtgxdj.payopbkcode,stWtgxdj.byzd),fpub_GetCompname(lXmlhandle))
		pstrcopy(stWtgxdj.payopbkcode,sPayOpBkCode,sizeof(stWtgxdj.payopbkcode)); */
		
    /*更新三方协议*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj  \
    		set	taxorgcode='%s'  \
						,paybkcode='%s'  \
						,payacct='%s'    \
						,taxpaycode='%s' \
						,payopbkcode='%s'\
						,taxpayname='%s' \
						,handorgname='%s'\
						,byzd='%s'       \
						,khh='%s'        \
						,xgrq='%s'       \
						,xglsh='%s'      \
						,xgdqdh='%s'     \
						,xgjgdh='%s'     \
						,xgjygy='%s'     \
						,xgzddh='%s'     \
						,opbankno='%s'   \
    			where protocolno='%s'" \
    			,stWtgxdj.taxorgcode   \
    			,stWtgxdj.paybkcode    \
    			,stWtgxdj.payacct      \
    			,stWtgxdj.taxpaycode   \
          ,stWtgxdj.payopbkcode  \
          ,stWtgxdj.taxpayname   \
          ,stWtgxdj.handorgname  \
          ,stWtgxdj.byzd         \
          ,stWtgxdj.khh          \
          ,stWtgxdj.xgrq         \
          ,stWtgxdj.xglsh        \
          ,stWtgxdj.xgdqdh       \
          ,stWtgxdj.xgjgdh       \
          ,stWtgxdj.xgjygy       \
          ,stWtgxdj.xgzddh       \
          ,stWtgxdj.opbankno     \
          ,sProtocolNo);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24327, "修改三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("修改三方协议失败"),
            fpub_GetCompname(lXmlhandle))
    }
		iRet =DCICommit();
		/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      fpub_SetMsg(lXmlhandle, 24327, "修改三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("修改三方协议失败"),
            fpub_GetCompname(lXmlhandle))  
    }
    */

    /* end dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_wtgxdj 
    		set taxorgcode= :stWtgxdj.taxorgcode,
    				paybkcode= :stWtgxdj.paybkcode,
    				payacct= :stWtgxdj.payacct,
    				taxpaycode= :stWtgxdj.taxpaycode,
    				payopbkcode= :stWtgxdj.payopbkcode,
    				taxpayname= :stWtgxdj.taxpayname,
    				handorgname= :stWtgxdj.handorgname,
    				byzd= :stWtgxdj.byzd,
    				khh= :stWtgxdj.khh,
    				xgrq= :stWtgxdj.xgrq,
    				xglsh= :stWtgxdj.xglsh,
    				xgdqdh= :stWtgxdj.xgdqdh,
    				xgjgdh= :stWtgxdj.xgjgdh,
    				xgjygy= :stWtgxdj.xgjygy,
    				xgzddh= :stWtgxdj.xgzddh,
    				opbankno= :stWtgxdj.opbankno
    			where protocolno=:sProtocolNo;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24327, "修改三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("修改三方协议失败"),
            fpub_GetCompname(lXmlhandle))
    }
    
    EXEC SQL COMMIT;  /*事务提交
    */
    fpub_SetMsg(lXmlhandle, 0, "修改三方协议成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("修改三方协议成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_XIBTZPD
组件名称: 调帐判断
组件功能: 
  调帐判断
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月1日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_XIBTZPD(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sTzlx[1+1];/* 调帐类型 */
        char sYzwrq[8+1];/* 账务日期 */
        char sDzjg[10+1];/* 对账结果 */
        long	dYqzlsh=0;
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("调帐判断开始"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"调帐类型");
    trim(sBuf);
    strcpy(sTzlx,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"原账务日期");
    trim(sBuf);
    strcpy(sYzwrq,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"原前置流水号");
    dYqzlsh = atol(sBuf);
    
    /*查询对账不平登记表--修改为查询原实时或批量流水--20120830 wangw*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT dzbz from tips_drls where zwrq='%s' and zhqzlsh=%d",sYzwrq,dYqzlsh);     	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
    iRet = DBSelectToVar(sErrmsg, &sDzjg, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")         
        
        fpub_SetMsg(lXmlhandle, 24327, "查询当日流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询当日流水表失败"),
            fpub_GetCompname(lXmlhandle))
    }
		
		/*未查到当日流水时再查当日批量扣税明细 */
    if ( iRet == 0)
    {
    	memset( sSql1, 0x00, sizeof( sSql1 ) );
    	snprintf( sSql1, sizeof(sSql1), "SELECT kzbz from tips_ssplksfmx where zwrq='%s' and plmxxh=%d",sYzwrq,dYqzlsh);  
    	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  	
    	iRet = DBSelectToVar(sErrmsg, &sDzjg, sSql1);    	
	    if ( iRet < 0 )
	    {
	    		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
	    		
	        fpub_SetMsg(lXmlhandle, 24327, "查询批量扣税明细表失败");
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询批量扣税明细表失败"),
	            fpub_GetCompname(lXmlhandle))
	    }   
	    if ( iRet == 0 )
	    {
        fpub_SetMsg(lXmlhandle, 24327, "未查到对应不平明细");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("未查到对应不平明细"),
            fpub_GetCompname(lXmlhandle))
      }
    }
    /* end dci 20141103 */
    
		/* EXEC SQL SELECT dzjg into :sDzjg from  tips_dzbpdj
    	WHERE zwrq = :sYzwrq and zhqzlsh = :dYqzlsh ; */
    /* mod dci 20141103
    EXEC SQL SELECT dzbz into :sDzjg from  tips_drls
    	WHERE zwrq = :sYzwrq and zhqzlsh = :dYqzlsh ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24327, "查询当日流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询当日流水表失败"),
            fpub_GetCompname(lXmlhandle))
    }   

    /*未查到当日流水时再查当日批量扣税明细
    if ( SQLNOTFOUND )
    {
    	EXEC SQL SELECT kzbz into :sDzjg from  tips_ssplksfmx
    		WHERE zwrq = :sYzwrq and plmxxh = :dYqzlsh ;
	    if ( SQLERR )
	    {
	        fpub_SetMsg(lXmlhandle, 24327, "查询批量扣税明细表失败");
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询批量扣税明细表失败"),
	            fpub_GetCompname(lXmlhandle))
	    }   
	    if ( SQLNOTFOUND )
	    {
        fpub_SetMsg(lXmlhandle, 24327, "未查到对应不平明细");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("未查到对应不平明细"),
            fpub_GetCompname(lXmlhandle))
      }
    }
    */   

    /*对账结果为TIPS多的，不允许冲正*/
    if (( sDzjg[1] == '3'||sDzjg[0] == '2') && sTzlx[0] == '1' )
    {
        fpub_SetMsg(lXmlhandle, 24327, "对账结果为TIPS多或核心少的，不能冲正");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("对账结果为TIPS多或核心少的，不能冲正"),
            fpub_GetCompname(lXmlhandle))
    }   
    
    /*对账结果为核心多的，不允许补帐*/
    if (( sDzjg[0] == '3'||sDzjg[1] == '2') && sTzlx[0] == '0' )
    {
        fpub_SetMsg(lXmlhandle, 24327, "对账结果为核心多或TIPS少的，不能补帐");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("对账结果为核心多或TIPS少的，不能补帐"),
            fpub_GetCompname(lXmlhandle))
    }   

    fpub_SetMsg(lXmlhandle, 0, "调帐判断成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("调帐判断成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    



/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_XIBLSH
组件名称: 生成发核心流水号
组件功能: 
  生成发核心流水号
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月1日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_XIBLSH(HXMLTREE lXmlhandle)
{
    int iParas;
    char sZhqzlsh[8+1];/* 前置流水号 */
    char sZwrq[8+1];/* 账务日期 */
    char sHxlsh[15+1];/* 对账结果 */
    long	dQzlsh=0;
    char sBuf[256];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("生成发核心流水号开始"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"账务日期");
    trim(sBuf);
    strcpy(sZwrq,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"前置流水号");
    trim(sBuf);
    strcpy(sZhqzlsh,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"输出节点");
    trim(sBuf);
    strcpy(sNode,sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memcpy(sBuf,"TASK",4);
    memcpy(sBuf+4,sZwrq+2,6);

    if(strlen(sZhqzlsh)<5)
    {
	    dQzlsh = atol(sZhqzlsh);    
	    sprintf(sHxlsh,"%s%05.5d%",sBuf,dQzlsh);
  	}
  	else
  		sprintf(sHxlsh,"%s%5.5s%",sBuf,sZhqzlsh);
  		
LOG(LM_STD,Fmtmsg("----------serial_no[%s]-------------",sHxlsh), fpub_GetCompname(lXmlhandle));
		
    COMP_SOFTSETXML(sNode, sHxlsh)

    fpub_SetMsg(lXmlhandle, 0, "生成发核心流水号");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("生成发核心流水号"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_XIBYWLSH
组件名称: 生成业务流水号
组件功能: 
  生成发核心流水号
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月1日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_XIBYWLSH(HXMLTREE lXmlhandle)
{
    int iParas;
    char sZhqzlsh[8+1];/* 前置流水号 */
    char sZwrq[8+1];/* 账务日期 */
    char sHxlsh[15+1];/* 对账结果 */
    long	dQzlsh=0;
    char sBuf[256];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("生成业务流水号开始"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"账务日期");
    trim(sBuf);
    strcpy(sZwrq,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"前置流水号");
    trim(sBuf);
    strcpy(sZhqzlsh,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"输出节点");
    trim(sBuf);
    strcpy(sNode,sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memcpy(sBuf,"TIPS",4);
    memcpy(sBuf+4,sZwrq+2,6);

    if(strlen(sZhqzlsh)<5)
    {
	    dQzlsh = atol(sZhqzlsh);    
	    sprintf(sHxlsh,"%s%05.5d%",sBuf,dQzlsh);
  	}
  	else
  		sprintf(sHxlsh,"%s%5.5s%",sBuf,sZhqzlsh);
  		
LOG(LM_STD,Fmtmsg("----------serial_no[%s]-------------",sHxlsh), fpub_GetCompname(lXmlhandle));
		
    COMP_SOFTSETXML(sNode, sHxlsh)

    fpub_SetMsg(lXmlhandle, 0, "生成发核心流水号");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("生成发核心流水号"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_XIBFLOOR
组件名称: 朝下取整
组件功能: 
  朝下取整，若正好除尽，取整-1
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月1日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_XIBFLOOR(HXMLTREE lXmlhandle)
{
    int iParas;
    int iBcs=0;      /* 被除数 */
    int iCs;          /* 除数 */
    int iShang;
    char sBuf[256];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("生成向下取整数开始"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"被除数");
    trim(sBuf);
    iBcs=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"除数");
    trim(sBuf);
    iCs=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"输出节点");
    trim(sBuf);
    strcpy(sNode,sBuf);
    
    if(iCs==0)
    {
	    fpub_SetMsg(lXmlhandle, 0, "生成向下取整数失败");
	    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	    LOG(LM_STD,Fmtmsg("生成向下取整数失败"), fpub_GetCompname(lXmlhandle));
    }
LOG(LM_STD,Fmtmsg("----------iShang[%d]-------------",iShang), fpub_GetCompname(lXmlhandle));

		/*modify bu wangw 20120913 如果正好除尽，取整-1，避免循环次数错*/
		if(iBcs%iCs == 0 )    	
    	iShang = floor(iBcs/iCs)-1;
    else
    	iShang = floor(iBcs/iCs);
LOG(LM_STD,Fmtmsg("----------iShang[%d]-------------",iShang), fpub_GetCompname(lXmlhandle));
		sprintf(sBuf,"%d",iShang);
    
    COMP_SOFTSETXML(sNode, sBuf)

    fpub_SetMsg(lXmlhandle, 0, "生成向下取整数成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("生成向下取整数成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    

/*Add by wangw 20120906 转换全角字符为半角，以便于忽略全角字符*/
int sQj2Bj(char s[200],char *st)
{
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sQj[200+1];
        char sBj[200+1];
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		/* end add dci 20141103 */

    memset(sQj,0,sizeof(sQj));
    memset(sBj,0,sizeof(sBj));
    strcpy(sQj,s);
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "drop table qj2bj" );
               	
    iRet = DCIExecuteDirect(sSql1);	 
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "create table qj2bj (  	string	char(200)  )" );
               	
    iRet = DCIExecuteDirect(sSql1);	
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        LOG(LM_STD,Fmtmsg("建临时表qj2bj失败"),"ERROR")
       return -1;
    }
		
		memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "insert into qj2bj values ('%s')",sQj);
    iRet = DCIExecuteDirect(sSql1);	
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      LOG(LM_STD,Fmtmsg("插入临时表qj2bj失败"),"ERROR")
       return -1;
    }
		
		memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), " select to_single_byte(string) from qj2bj where string='%s'",sQj);     	
    iRet = DBSelectToVar(sErrmsg, &sBj, sSql1);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      LOG(LM_STD,Fmtmsg("查询临时表qj2bj失败"),"ERROR")
       return -1;
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL drop table qj2bj;
    EXEC SQL create table qj2bj
    (
    	string	char(200)
    );
    if ( SQLERR )
    {
	     LOG(LM_STD,Fmtmsg("建临时表qj2bj失败,sqlcode[%d]",sqlca.sqlcode),"ERROR")
       return -1;
    }
    
    EXEC SQL insert into qj2bj values (:sQj);
    if ( SQLERR )
    {
	     LOG(LM_STD,Fmtmsg("插入临时表qj2bj失败,sqlcode[%d]",sqlca.sqlcode),"ERROR")
       return -1;
    }
    
    EXEC SQL select to_single_byte(string) into :sBj from qj2bj where string=:sQj;
    if ( SQLERR )
    {
	     LOG(LM_STD,Fmtmsg("查询临时表qj2bj失败,sqlcode[%d]",sqlca.sqlcode),"ERROR")
       return -1;
    }
    */
    trim(sBj);
    strcpy(st,sBj);	
    
    return 0 ;
}



