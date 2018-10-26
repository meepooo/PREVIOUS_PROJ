/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V3.0.00
操作系统:AIX5.3
文件名称:SYW_TIPS_FUNDRT.sqc
文件描述:TIPS资金汇划交易
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
EXEC SQL INCLUDE  "../eh/tips_sszjhhls.eh";/* 税收资金汇划流水表 
EXEC SQL INCLUDE  "../eh/tips_sszjhhlspz.eh";/* 税收资金汇划流水表凭证 
*/

#include "../eh/tips_sszjhhls.h"/* 税收资金汇划流水表 */
#include "../eh/tips_sszjhhlspz.h"/* 税收资金汇划流水表凭证 */

/*EXEC SQL BEGIN DECLARE SECTION;*/
typedef struct TDB_ZJHHDZ
{
	char zjrq[8+1];/*核心日期*/
	char zjlsh[32+1];/*核心流水号*/
	char chkdate[8+1];/*对帐批次*/
	char chkacctord[4+1];/*对帐批次*/
	char paybkcode[12+1];/*付款行行号*/ 
	char payacct[32+1];/*付款人账号*/
	char payeebankno[12+1];/*收款行行号*/  
	char payeeacct[32+1];/*被冲正标志*/
	double jyje;/*交易金额*/
	char qzrq[8+1];/*前置日期*/
	int qzlsh;/*前置流水号*/
}SDB_ZJHHDZ;
/*EXEC SQL END DECLARE SECTION;*/

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )
/*****************************************
记录资金汇划对帐日志的函数

*****************************************/
int LOG_ZJHHDZ(char *sTransCode,char *buf)
{
  char sfile[200];
  FILE *fp;
  
  memset(sfile, 0x00, sizeof(sfile));
  sprintf(sfile,"%s/file/tips/chkacct/ZJHHDZ_%s_%s.log",getenv("HOME"),sTransCode,GetSysDate());
  if ((fp=fopen(sfile,"a+")) ==  NULL )	
    return -1;
  fprintf(fp," %s\n",buf);
  fclose(fp); 
  return 0;	
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitHHLS
组件名称: 初始实时汇划流水
组件功能: 
    初始实时汇划流水
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
tips_sszjhhls  税收资金汇划流水表

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年12月23日
修改日期: 2014年12月20日DCI改造
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitHHLS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103 
    EXEC SQL BEGIN DECLARE SECTION;
         SDB_TIPS_SSZJHHLS stZjhhls;
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
  	
  	SDB_TIPS_SSZJHHLS stZjhhls;
  	char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
    fpub_InitSoComp(lXmlhandle);

    memset(&stZjhhls, 0x00, sizeof(stZjhhls));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "帐务日期")
    pstrcopy( stZjhhls.zwrq, sBuf, sizeof(stZjhhls.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "综合前置流水号")
    stZjhhls.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("初始实时汇划流水表 帐务日期[%s],综合前置流水号[%d]", 
        stZjhhls.zwrq, stZjhhls.zhqzlsh), fpub_GetCompname(lXmlhandle));    

		/* add dci 20141103 */
		iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		/* end dci */
		
    /* 3.对帐日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkDate", sBuf)
    pstrcopy( stZjhhls.chkdate, sBuf, sizeof(stZjhhls.chkdate));
    if ( stZjhhls.chkdate[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("对帐日期不能为空"));
        LOG(LM_STD,Fmtmsg("对帐日期不能为空, chkdate=[%s]", stZjhhls.chkdate),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 4.对帐批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy( stZjhhls.chkacctord, sBuf, sizeof(stZjhhls.chkacctord));
    if ( stZjhhls.chkacctord[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("对帐批次号不能为空"));
        LOG(LM_STD,Fmtmsg("对帐批次号不能为空, chkacctord=[%s]", stZjhhls.chkacctord),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 5.付款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy( stZjhhls.paybkcode, sBuf, sizeof(stZjhhls.paybkcode));
    if ( stZjhhls.paybkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("付款行行号不能为空"));
        LOG(LM_STD,Fmtmsg("付款行行号不能为空, paybkcode=[%s]", stZjhhls.paybkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 6.收款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy( stZjhhls.payeebankno, sBuf, sizeof(stZjhhls.payeebankno));
    if ( stZjhhls.payeebankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("收款行行号不能为空"));
        LOG(LM_STD,Fmtmsg("收款行行号不能为空, payeebankno=[%s]", stZjhhls.payeebankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 7.付款开户行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy( stZjhhls.payopbkcode, sBuf, sizeof(stZjhhls.payopbkcode));
    if ( stZjhhls.payopbkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("付款开户行行号不能为空"));
        LOG(LM_STD,Fmtmsg("付款开户行行号不能为空, payopbkcode=[%s]", stZjhhls.payopbkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 8.付款人账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy( stZjhhls.payacct, sBuf, sizeof(stZjhhls.payacct));
    if ( stZjhhls.payacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("付款人账号不能为空"));
        LOG(LM_STD,Fmtmsg("付款人账号不能为空, payacct=[%s]", stZjhhls.payacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 9.付款人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkName", sBuf)
    pstrcopy( stZjhhls.paybkname, sBuf, sizeof(stZjhhls.paybkname));
    if ( stZjhhls.paybkname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24279, Fmtmsg("付款人名称不能为空"));
        LOG(LM_STD,Fmtmsg("付款人名称不能为空, paybkname=[%s]", stZjhhls.paybkname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 10.收款开户行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOpBankNo", sBuf)
    pstrcopy( stZjhhls.payeeopbankno, sBuf, sizeof(stZjhhls.payeeopbankno));
    if ( stZjhhls.payeeopbankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24280, Fmtmsg("收款开户行行号不能为空"));
        LOG(LM_STD,Fmtmsg("收款开户行行号不能为空, payeeopbandno=[%s]", stZjhhls.payeeopbankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 11.收款人账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy( stZjhhls.payeeacct, sBuf, sizeof(stZjhhls.payeeacct));
    if ( stZjhhls.payeeacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24281, Fmtmsg("收款人账号不能为空"));
        LOG(LM_STD,Fmtmsg("收款人账号不能为空, payeeacct=[%s]", stZjhhls.payeeacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 12.收款人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankName", sBuf)
    pstrcopy( stZjhhls.payeebankname, sBuf, sizeof(stZjhhls.payeebankname));
    if ( stZjhhls.payeebankname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24282, Fmtmsg("收款人名称不能为空"));
        LOG(LM_STD,Fmtmsg("收款人名称不能为空, payeebankname=[%s]", stZjhhls.payeebankname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 13.对帐类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctType", sBuf)
    pstrcopy( stZjhhls.chkaccttype, sBuf, sizeof(stZjhhls.chkaccttype));
    if ( stZjhhls.chkaccttype[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24283, Fmtmsg("对帐类型不能为空"));
        LOG(LM_STD,Fmtmsg("对帐类型不能为空, payeeacct=[%s]", stZjhhls.chkaccttype),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 14.批次笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllNum", sBuf)
    stZjhhls.allnum = atoi(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24284, Fmtmsg("批次笔数不能为空"));
        LOG(LM_STD,Fmtmsg("批次笔数不能为空, allnum=[%d]", stZjhhls.allnum),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 15.批次金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllAmt", sBuf)
    stZjhhls.allamt=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24285, Fmtmsg("批次金额不能为空"));
        LOG(LM_STD,Fmtmsg("批次金额不能为空, allamt=[%.2f]", stZjhhls.allamt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }   
    
    /* 16.交易笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jybs", sBuf)
    stZjhhls.jybs = atoi(sBuf);
    if ( sBuf[0] == '\0' )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24286, Fmtmsg("交易笔数不能为空"));
        LOG(LM_STD,Fmtmsg("交易笔数不能为空, jybs=[%d]", stZjhhls.jybs),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 17.交易金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyje", sBuf)
    stZjhhls.jyje=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24287, Fmtmsg("交易金额不能为空"));
        LOG(LM_STD,Fmtmsg("交易金额不能为空, jyje=[%.2f]", stZjhhls.jyje),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 18.附言 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/addword", sBuf)
    pstrcopy(stZjhhls.addword, sBuf, sizeof(stZjhhls.addword));
    if ( stZjhhls.addword[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24288, Fmtmsg("附言不能为空"));
        LOG(LM_STD,Fmtmsg("附言不能为空, addword=[%s]", stZjhhls.addword),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 19.交易日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyrq", sBuf)
    pstrcopy(stZjhhls.jyrq, sBuf, sizeof(stZjhhls.jyrq));
    if ( stZjhhls.jyrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24289, Fmtmsg("交易日期不能为空"));
        LOG(LM_STD,Fmtmsg("交易日期不能为空, jyrq=[%s]", stZjhhls.jyrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 20.交易时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jysj", sBuf)
    pstrcopy(stZjhhls.jysj, sBuf, sizeof(stZjhhls.jysj));
    if ( stZjhhls.jysj[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24290, Fmtmsg("交易时间不能为空"));
        LOG(LM_STD,Fmtmsg("交易时间不能为空, jysj=[%s]", stZjhhls.jysj),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 21.清算日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(stZjhhls.qsrq, sBuf, sizeof(stZjhhls.qsrq));
    if ( stZjhhls.qsrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24291, Fmtmsg("清算日期不能为空"));
        LOG(LM_STD,Fmtmsg("清算日期不能为空, qsrq=[%s]", stZjhhls.qsrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 22.清算流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qslsh", sBuf)
    stZjhhls.qslsh=atoi(sBuf);
    if ( stZjhhls.qslsh == 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24292, Fmtmsg("清算流水号不能为空"));
        LOG(LM_STD,Fmtmsg("清算流水号不能为空, qslsh=[%d]", stZjhhls.qslsh),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 23.业务种类 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ywzl", sBuf)
    pstrcopy(stZjhhls.ywzl, sBuf, sizeof(stZjhhls.ywzl));
    if ( stZjhhls.ywzl[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24293, Fmtmsg("业务种类不能为空"));
        LOG(LM_STD,Fmtmsg("业务种类不能为空, ywzl=[%s]", stZjhhls.ywzl),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 24.汇划次数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hhcs", sBuf)
    stZjhhls.hhcs=atoi(sBuf);

    /* 25.主机日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stZjhhls.zjrq, sBuf, sizeof(stZjhhls.zjrq));

    /* 26.主机时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stZjhhls.zjsj, sBuf, sizeof(stZjhhls.zjsj));

    /* 27.主机流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stZjhhls.zjlsh, sBuf, sizeof(stZjhhls.zjlsh));

    /* 28.交易状态 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stZjhhls.jyzt, sBuf, sizeof(stZjhhls.jyzt));
    if ( stZjhhls.jyzt[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24298, Fmtmsg("交易状态不能为空"));
        LOG(LM_STD,Fmtmsg("交易状态不能为空, jyzt=[%s]", stZjhhls.jyzt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 29.响应码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xym", sBuf)
    pstrcopy(stZjhhls.xym, sBuf, sizeof(stZjhhls.xym));
    if ( stZjhhls.xym[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24299, Fmtmsg("响应码不能为空"));
        LOG(LM_STD,Fmtmsg("响应码不能为空, xym=[%s]", stZjhhls.xym),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 30.响应信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xyxx", sBuf)
    pstrcopy(stZjhhls.xyxx, sBuf, sizeof(stZjhhls.xyxx));
    if ( stZjhhls.xyxx[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24300, Fmtmsg("响应信息不能为空"));
        LOG(LM_STD,Fmtmsg("响应信息不能为空, xyxx=[%s]", stZjhhls.xyxx),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 31.清算标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stZjhhls.qsbz, sBuf, sizeof(stZjhhls.qsbz));
    if ( stZjhhls.qsbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24301, Fmtmsg("清算标志不能为空"));
        LOG(LM_STD,Fmtmsg("清算标志不能为空, qsbz=[%s]", stZjhhls.qsbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 32.对账标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stZjhhls.dzbz, sBuf, sizeof(stZjhhls.dzbz));
    if ( stZjhhls.dzbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("对账标志不能为空"));
        LOG(LM_STD,Fmtmsg("对账标志不能为空, dzbz=[%s]", stZjhhls.dzbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 32.手工修改信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sgxgxx", sBuf)
    pstrcopy(stZjhhls.sgxgxx, sBuf, sizeof(stZjhhls.sgxgxx));

    /* 33.备用字段 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/byzd", sBuf)
    pstrcopy(stZjhhls.byzd, sBuf, sizeof(stZjhhls.byzd));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_sszjhhls", SD_TIPS_SSZJHHLS, NUMELE(SD_TIPS_SSZJHHLS), &stZjhhls, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24308, "初始化税收资金汇划流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("初始化税收资金汇划流水表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL; 
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
    EXEC SQL INSERT INTO tips_sszjhhls  VALUES (:stZjhhls);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24308, "初始化税收资金汇划流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("初始化税收资金汇划流水表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	    
		*/
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}    

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdZJHH
组件名称: 更新资金实时汇划表
组件功能: 
  更新资金实时汇划表状态
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
税收资金汇划流水表	tips_sszjhhls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年12月23日
修改日期: 2014年12月20日DCI改造，待测试
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdZJHH(HXMLTREE lXmlhandle)
{	
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sZwrq[8+1];
         int iZhqzlsh;
         char sJyzt[1+1];/* 交易状态 */
         char sQsrq[8+1];/* 清算日期 */
         int iQslsh;/* 清算流水号 */
         char sZjrq[8+1];/* 主机日期 */
         char sZjsj[8+1];/* 主机时间 */
         char sZjlsh[32+1];/* 主机流水号 */
         char sXym[5+1];/* 响应码 */
         char sXyxx[60+1];/* 响应信息 */
    /*EXEC SQL END DECLARE SECTION;*/
    
    char sBuf[256];
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
  	
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(10);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "账务日期")
    pstrcopy( sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "综合前置流水号")
    iZhqzlsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJyzt, 0x00, sizeof(sJyzt));
    COMP_GETPARSEPARAS(3, sBuf, "交易状态")
    pstrcopy( sJyzt, sBuf, sizeof(sJyzt));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_GETPARSEPARAS(4, sBuf, "清算日期")
    pstrcopy( sQsrq, sBuf, sizeof(sQsrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iQslsh=0;
    COMP_GETPARSEPARAS(5, sBuf, "清算流水号")
    iQslsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjrq, 0x00, sizeof(sZjrq));
    COMP_GETPARSEPARAS(6, sBuf, "主机日期")
    pstrcopy( sZjrq, sBuf, sizeof(sZjrq));       

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjsj, 0x00, sizeof(sZjsj));
    COMP_GETPARSEPARAS(7, sBuf, "主机时间")
    pstrcopy( sZjsj, sBuf, sizeof(sZjsj));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjlsh, 0x00, sizeof(sZjlsh));
    COMP_GETPARSEPARAS(8, sBuf, "主机流水号")
    pstrcopy( sZjlsh, sBuf, sizeof(sZjlsh));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXym, 0x00, sizeof(sXym));
    COMP_GETPARSEPARAS(9, sBuf, "响应码")
    pstrcopy( sXym, sBuf, sizeof(sXym));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXyxx, 0x00, sizeof(sXyxx));
    COMP_GETPARSEPARAS(10, sBuf, "响应信息")
    pstrcopy( sXyxx, sBuf, sizeof(sXyxx));
    
    LOG(LM_STD,Fmtmsg("更新资金实时汇划表开始处理...帐务日期[%s]前置流水号=[%d]交易状态=[%s]",sZwrq, iZhqzlsh, sJyzt),"INFO")
    LOG(LM_STD,Fmtmsg("清算日期[%s]清算流水号=[%d]主机日期=[%s]主机时间=[%s]主机流水号[%s]", sQsrq, iQslsh, sZjrq, sZjsj, sZjlsh),"INFO")
    LOG(LM_STD,Fmtmsg("响应码=[%s]响应信息[%s]", sXym, sXyxx),"INFO")
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhls \
    		set jyzt  ='%s',\
    				hhcs  =hhcs + 1,\
    				qsrq  ='%s',\
    				qslsh =%d,\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s',\
    				xym   ='%s',\
    				xyxx  ='%s' \
    			where zwrq='%s' and zhqzlsh=%d" \
             ,sJyzt  \
             ,sQsrq  \
             ,iQslsh \
             ,sZjrq  \
             ,sZjsj  \
             ,sZjlsh \
             ,sXym   \
             ,sXyxx  \
             ,sZwrq  \
             ,iZhqzlsh);   
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = DCIExecuteDirect(sSql1);	 
         
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "实时资金实时汇划表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("实时资金实时汇划表失败"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24286, "更新失败-->实时资金实时汇划表记录未找到");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("更新失败-->实时资金实时汇划表记录未找到"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;		
    }	

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_sszjhhls
    	   SET jyzt = :sJyzt,
    	       hhcs = hhcs + 1,
    	       qsrq = :sQsrq,
    	       qslsh = :iQslsh,
    	       zjrq = :sZjrq,
    	       zjsj = :sZjsj,
    	       zjlsh = :sZjlsh,
    	       xym = :sXym,
    	       xyxx = :sXyxx
         WHERE zwrq = :sZwrq 
           AND zhqzlsh = :iZhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "实时资金实时汇划表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("实时资金实时汇划表失败"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND )	
    {
         fpub_SetMsg(lXmlhandle, 24286, "更新失败-->实时资金实时汇划表记录未找到");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("更新失败-->实时资金实时汇划表记录未找到"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    */   
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_ZJHH
组件名称: 资金汇划(多笔)
组件功能: 
  资金汇划
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
税收资金汇划流水表	tips_sszjhhls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年12月25日
修改日期: 2014年12月20日DCI改造
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_ZJHH(HXMLTREE lXmlhandle)
{	
    int iParas;
    //EXEC SQL BEGIN DECLARE SECTION;
         char sZwrq[8+1];
         int iZhqzlsh;
         char sJyzt[1+1];
         int iCount;
    //EXEC SQL END DECLARE SECTION;
    char sBuf[256];
    char sSubFlow[256];
    int iflag ;
    int iAll;
    int iSucc;
    int iFail;
      	
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1);
    
    memset(sSubFlow, 0x00, sizeof(sSubFlow));
    COMP_GETPARSEPARAS(1, sSubFlow, "资金汇划流程")
    trim(sSubFlow);
    
    LOG(LM_STD,Fmtmsg("资金汇划开始处理...实时汇划流程=[%s]",sSubFlow),"INFO")
   
    iCount = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_sszjhhls \
    	where jyzt in ('1', '2') AND jyje > 0.00");   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")        	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "查询税收资金汇划流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询税收资金汇划流水表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;    
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_sszjhhls
         WHERE jyzt in ('1', '2')
           AND jyje > 0.00;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "查询税收资金汇划流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询税收资金汇划流水表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
    if ( iCount < 1 )
    {
         fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "当前没需要处理的资金汇划记录");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
         LOG(LM_STD, Fmtmsg("当前没需要处理的资金汇划记录"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_SUCC ;        
    }
    
    LOG(LM_STD, Fmtmsg("当前需要处理的资金汇划记录共[%d]条", iCount), fpub_GetCompname(lXmlhandle))	
	   
    /* 设置业务明细块 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select zwrq, zhqzlsh, jyzt from tips_sszjhhls \
    	where jyzt in ('1', '2') AND jyje > 0.00");  
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
   	
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL DECLARE cur_zjhhls CURSOR for 
         SELECT zwrq, zhqzlsh, jyzt
         FROM tips_sszjhhls
         WHERE jyzt in ('1', '2')
           AND jyje > 0.00;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_zjhhls;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_zjhhls",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24311, "打开游标cur_zjhhls失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开cur_zjhhls游标失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*开始循环*/
    iSucc = 0;
    iFail = 0;
    /* add dci 20141103 */
    for (iAll=0,iflag=0;;iAll++)
    {
        memset(sZwrq, 0x00, sizeof(sZwrq));
        iZhqzlsh=0;
        memset(sJyzt, 0x00, sizeof(sJyzt));
        iRet = DCIFetch(cur);
             
        if ( iRet < 0 )
        {  
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("从cur_zjhhls游标获取数据失败"),"ERROR");
        	break;
        }
        if ( iRet ==0 )
          break;
          
        sprintf( sZwrq, "%s", DCIFieldAsString( cur, 0 ) );
				iZhqzlsh = atoi(DCIFieldAsString( cur, 1 )) ;
				sprintf( sJyzt, "%s", DCIFieldAsString( cur, 2 ) );

        trim(sZwrq);
        trim(sJyzt);
              
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf),"%d", iZhqzlsh);
        COMP_SOFTSETXML("/tips/zhqzlsh", sBuf)
        COMP_SOFTSETXML("/tips/jyzt", sJyzt)
              
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("调资金汇划主流程系统错误"),"ERROR");
        	break;
        }
        
        /*判断子流程是否处理成功 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*返回2失败,其它均为成功 */
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("调资金汇划主流程失败"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    DCIFreeCursor(cur);
    /* end add dci 20141103 */

    /* mod dci 20141103 
    for (iAll=0,iflag=0;;iAll++)
    {
        memset(sZwrq, 0x00, sizeof(sZwrq));
        iZhqzlsh=0;
        memset(sJyzt, 0x00, sizeof(sJyzt));
        EXEC SQL FETCH cur_zjhhls INTO :sZwrq, :iZhqzlsh, :sJyzt;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_zjhhls", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("从cur_zjhhls游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;

        trim(sZwrq);
        trim(sJyzt);
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf),"%d", iZhqzlsh);
        COMP_SOFTSETXML("/tips/zhqzlsh", sBuf)
        COMP_SOFTSETXML("/tips/jyzt", sJyzt)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("调资金汇划主流程系统错误"),"ERROR");
        	break;
        }
        
        /*判断子流程是否处理成功
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*返回2失败,其它均为成功
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("调资金汇划主流程失败"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    EXEC SQL CLOSE cur_zjhhls; 
    */
       
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"并发处理资金汇划失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("并发处理资金汇划失败iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    fpub_SetMsg(lXmlhandle,0,"并发处理资金汇划结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("并发处理资金汇划结束,共[%d]笔,成功[%d]笔,失败[%d]笔",
        iAll, iSucc, iFail), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
} 

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_ZJHHDZ
组件名称: 资金汇划对账(一天)
 
组件功能: 
    资金汇划对账(一天)
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

主要操作库表:
  表名              操作
税收资金汇划流水表	tips_sszjhhls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年12月25日
修改日期: 2014年12月20日DCI改造，待测试
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_ZJHHDZ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION;*/
         SDB_ZJHHDZ stZjhhdz;
         SDB_TIPS_SSZJHHLS stZjhhls;
         char sDzrq[8+1];
         int iCount;
    /*EXEC SQL END DECLARE SECTION;*/
    
    char sBuf[256];
	int i;
	int iRet=0;
	int iFlag=0;
	char sMxFileName[256];
	char sLine[1024];
	char sResIcxp[256];
	int iQzdnum = 0;     /*前置多的记录数*/
	int iZjdnum = 0;    /*主机多的记录数*/    
    FILE *fp;

		char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;
		
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMxFileName, 0x00, sizeof(sMxFileName));
    COMP_GETPARSEPARAS(1, sBuf, "对账明细文件")
    pstrcopy(sMxFileName, sBuf, sizeof(sMxFileName));
    trim(sMxFileName);            
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sResIcxp, 0x00, sizeof(sResIcxp));
    COMP_GETPARSEPARAS(2, sBuf, "明细文件ICXP配置")
    pstrcopy(sResIcxp, sBuf, sizeof(sResIcxp));
    trim(sResIcxp); 
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDzrq, 0x00, sizeof(sDzrq));
    COMP_GETPARSEPARAS(3, sBuf, "对账日期")
    pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
    trim(sDzrq); 
    
    LOG(LM_STD,Fmtmsg("资金汇划对账开始处理..."),fpub_GetCompname(lXmlhandle))  
    LOG(LM_STD,Fmtmsg("对账日期[%s],对账明细文件[%s],明细文件ICXP配置[%s]",
        sDzrq, sMxFileName, sResIcxp),fpub_GetCompname(lXmlhandle))  
		
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "UPDATE tips_sszjhhls SET dzbz='0',qsbz='0' \
    		WHERE chkdate ='%s'",sDzrq);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                 	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24422, "更新税收资金汇划流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新税收资金汇划流水表失败"),
            fpub_GetCompname(lXmlhandle))       
    }
    
		/* end add dci 20141103 */
		
		/* mod dci 20141103 
    EXEC SQL UPDATE tips_sszjhhls SET dzbz='0',qsbz='0'
         WHERE chkdate = :sDzrq;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24422, "更新税收资金汇划流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新税收资金汇划流水表失败"),
            fpub_GetCompname(lXmlhandle))        
    }           
		*/
		
    /*先打开明细文件,校验*/
    fp = fopen(sMxFileName,"r");
    if ( fp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24422, "打开资金汇划对账文件失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("打开资金汇划对账文件失败[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
    /*文件体处理*/
    for (iFlag=0,i=1; ;i++)
    {   	
        memset(sLine,0x00,sizeof(sLine));
        memset(sBuf, 0x00, sizeof(sBuf));  
        COMP_SOFTSETXML("/tips/zjhhdz/zjrq", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/zjlsh", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/ChkDate", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/ChkAcctOrd", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayBkCode", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayAcct", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayeeBankNo", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayeeAcct", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/jyje", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/qzrq", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/qzlsh", sBuf)
        if (fgets(sLine,sizeof(sLine),fp) == NULL)
            break;                   /*文件结束 跳出*/
        trim(sLine);
        if ( i==1 || strlen(sLine) < 30 )
            continue;               /*遇到对帐文件开头或空行,跳过*/
        sLine[strlen(sLine)-1]=0;   /*去除最后一个换行符*/
        if (strcmp(sLine,"END") == 0 )
            break;                   /*遇到对帐文件结束符*/
        iRet=SBATCH_FuncICXPUPKG(lXmlhandle,sResIcxp,sLine,strlen(sLine));
        if (iRet < 0)
        { 
            iFlag = -1; 
            break; 
        }	
        memset(&stZjhhdz, 0x00, sizeof(stZjhhdz));
        /* 主机日期 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/zjrq", sBuf)
        pstrcopy(stZjhhdz.zjrq, sBuf, sizeof(stZjhhdz.zjrq));
        /* 主机流水号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/zjlsh", sBuf)
        pstrcopy(stZjhhdz.zjlsh, sBuf, sizeof(stZjhhdz.zjlsh));
        /* 对账日期 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/ChkDate", sBuf)
        pstrcopy(stZjhhdz.chkdate, sBuf, sizeof(stZjhhdz.chkdate));
        /* 对账批次号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/ChkAcctOrd", sBuf)
        pstrcopy(stZjhhdz.chkacctord, sBuf, sizeof(stZjhhdz.chkacctord));
        /*  付款行行号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayBkCode", sBuf)
        pstrcopy(stZjhhdz.paybkcode, sBuf, sizeof(stZjhhdz.paybkcode));
        /* 付款人账号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayAcct", sBuf)
        pstrcopy(stZjhhdz.payacct, sBuf, sizeof(stZjhhdz.payacct));
        /* 收款行行号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayeeBankNo", sBuf)
        pstrcopy(stZjhhdz.payeebankno, sBuf, sizeof(stZjhhdz.payeebankno));
        /* 收款人账号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayeeAcct", sBuf)
        pstrcopy(stZjhhdz.payeeacct, sBuf, sizeof(stZjhhdz.payeeacct));
        /* 交易金额 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/jyje", sBuf)
        stZjhhdz.jyje=atof(sBuf);
        /* 前置日期 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/qzrq", sBuf)
        pstrcopy(stZjhhdz.qzrq, sBuf, sizeof(stZjhhdz.qzrq));
        /* 前置流水号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/qzlsh", sBuf)
        stZjhhdz.qzlsh=atoi(sBuf);
        /*从资金汇划流水表中取帐务日期及前置流水号相同的记录*/
        
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "UPDATE tips_sszjhhls SET dzbz='1',qsbz='1' \
    			WHERE zwrq='%s' AND  zhqzlsh=%d AND  jyzt='5' AND  jyje=%.2f",\
    			stZjhhdz.qzrq,stZjhhdz.qzlsh,stZjhhdz.jyje);
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")             	
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        	LOG(LM_STD,Fmtmsg("更新当日流水表失败,帐务日期[%s],前置流水号[%d]", 
                stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
            iFlag = -9;
            break;    
    		}
    		/*如果找不到，则从有单边帐,核心成功,前置失败 */
     		if( iRet == 0 ) 
        {   
  		  	iZjdnum ++;
    	  	LOG_ZJHHDZ("zjhhdz",Fmtmsg("-->主机成功,前置失败：前置日期[%s],前置流水[%d],主机日期[%s],主机流水[%s]金额[%.2f],解决办法：查原因,重做资金汇划及对账",
    	  	    	  	stZjhhdz.qzrq,stZjhhdz.qzlsh,stZjhhdz.zjrq,stZjhhdz.zjlsh,stZjhhdz.jyje));        
            /*从资金汇划流水表中取帐务日期及前置流水号相同的记录 */
          memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "UPDATE tips_sszjhhls SET dzbz='3',qsbz='0' \
    				WHERE zwrq='%s' AND  zhqzlsh=%d",\
    				stZjhhdz.qzrq,stZjhhdz.qzlsh);               	
    			iRet = DCIExecuteDirect(sSql1);	   
    			if ( iRet < 0 )
    			{
                LOG(LM_STD,Fmtmsg("更新资金汇划流水表失败,帐务日期[%s],前置流水号[%d]", 
                    stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
                iFlag = -9;
                break;
     	    }    	  

        }/* 主机成功,前置失败 */            
    
        /* end add dci 20141103 */
        
        /* mod dci 20141103 
     	EXEC SQL UPDATE tips_sszjhhls 
			 SET dzbz='1',
			     qsbz='1'
			 WHERE  zwrq=:stZjhhdz.qzrq
			   AND  zhqzlsh=:stZjhhdz.qzlsh
			   AND  jyzt='5'
               AND  jyje=:stZjhhdz.jyje ;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
  	 	if(SQLERR)
  	 	{
            LOG(LM_STD,Fmtmsg("更新当日流水表失败,帐务日期[%s],前置流水号[%d]", 
                stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
            iFlag = -9;
            break;
     	}
     	/*如果找不到，则从有单边帐,核心成功,前置失败
     	if( SQLNOTFOUND_TIPS ) 
        {   
  		  	iZjdnum ++;
    	  	LOG_ZJHHDZ("zjhhdz",Fmtmsg("-->主机成功,前置失败：前置日期[%s],前置流水[%d],主机日期[%s],主机流水[%s]金额[%.2f],解决办法：查原因,重做资金汇划及对账",
    	  	    	  	stZjhhdz.qzrq,stZjhhdz.qzlsh,stZjhhdz.zjrq,stZjhhdz.zjlsh,stZjhhdz.jyje));        
            /*从资金汇划流水表中取帐务日期及前置流水号相同的记录
     	    EXEC SQL UPDATE tips_sszjhhls 
		    	 SET dzbz='3',
		    	     qsbz='0'
		    	 WHERE  zwrq=:stZjhhdz.qzrq
		    	   AND  zhqzlsh=:stZjhhdz.qzlsh;
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
  	 	    if(SQLERR)
  	 	    {
                LOG(LM_STD,Fmtmsg("更新资金汇划流水表失败,帐务日期[%s],前置流水号[%d]", 
                    stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
                iFlag = -9;
                break;
     	    }    	  	
        }/* 主机成功,前置失败 */                
    }/* for (iFlag=0,i=1; ;i++)文件体处理 */    
    
    fclose(fp);
    if (iFlag < 0)
    { 
        fpub_SetMsg(lXmlhandle,24423,Fmtmsg("资金汇划对账失败"));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("资金汇划对账失败,ret[%d]..",iFlag),"ERROR");
    }
    /*判断是否还有未核对的前置流水--前置多*/
    iCount = 0;
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_sszjhhls \
    	where chkdate = '%s' AND jyzt='5' AND dzbz = '0' AND qsbz = '0'",sDzrq);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle,24424,Fmtmsg("查询资金汇划表失败"));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询资金汇划表失败"),"ERROR");  
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount 
         FROM  tips_sszjhhls
     	 WHERE chkdate = :sDzrq
     	   AND jyzt='5'
           AND dzbz = '0'
           AND qsbz = '0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    { 
        fpub_SetMsg(lXmlhandle,24424,Fmtmsg("查询资金汇划表失败"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询资金汇划表失败"),"ERROR");
    }
    */
    
    if( iCount > 0 )
    {
        iQzdnum = iQzdnum + iCount; /* 前置多计数器++ */
        /* 把前置多的流水记录对帐标志改为2,并写到对帐不平文件中 */
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_sszjhhls \
    			where chkdate = '%s' AND jyzt='5' AND dzbz = '0' AND qsbz = '0'",sDzrq); 
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
        EXEC SQL DECLARE cur_zjhhdz CURSOR for 
            SELECT *
            FROM  tips_sszjhhls 
            WHERE chkdate = :sDzrq
              AND jyzt='5'
              AND dzbz = '0'
              AND qsbz = '0';
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
        
        EXEC SQL OPEN cur_zjhhdz;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_zjhhdz",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle,24425, "打开游标失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("HXDZ打开cur_drls_hxdz_cur游标失败"),
                fpub_GetCompname(lXmlhandle))
        }
        */
                  
        /*开始循环*/
        for (i=1,iFlag=0;;i++)
        {
            memset(&stZjhhls, 0x00, sizeof(stZjhhls));
            /* add dci 20141103 */
            iRet = DBFetch(cur, SD_TIPS_SSZJHHLS,NUMELE(SD_TIPS_SSZJHHLS),&stZjhhls, sErrmsg );
						if ( iRet < 0 )
            {  
            	iFlag=-1;
            	LOG(LM_STD,Fmtmsg("从cur_zjhhdz游标获取数据失败"),"ERROR");
            	break;
            }
            if ( iRet == 0 )
              break;
            /* end add dci 20141103 */
            
            /* mod dci 20141103 
            EXEC SQL FETCH cur_zjhhdz INTO :stZjhhls;     
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_zjhhdz",sqlca.sqlcode),"ERROR");
            if ( SQLERR )
            {  
            	iFlag=-1;
            	LOG(LM_STD,Fmtmsg("从cur_zjhhdz游标获取数据失败"),"ERROR");
            	break;
            }
            if ( SQLNOTFOUND )
              break;
            */  
            
            trim(stZjhhls.zjlsh);  
    	  		LOG_ZJHHDZ("zjhhdz",Fmtmsg("-->前置成功,主机失败：帐务日期[%s],前置流水[%d],主机日期[%s],主机流水号[%s]金额[%.2f],解决办法：查原因,重做资金汇划及对账",
    	  	  	stZjhhls.zwrq,stZjhhls.zhqzlsh,stZjhhls.zjrq,stZjhhls.zjlsh,stZjhhls.jyje));
            /*更新该流水明细状态为前置多*/
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhls \
    							set dzbz='2' \
    							where zwrq='%s' and zhqzlsh=%d" \
    							,stZjhhls.zwrq  \
    							,stZjhhls.zhqzlsh  );
               	
        		iRet = DCIExecuteDirect(sSql1);	 
        		if ( iRet < 0 )
        		{
            	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
            	
            	LOG(LM_STD,Fmtmsg("更新资金汇划表失败,帐务日期[%s],前置流水号[%d]", 
                    stZjhhls.zwrq, stZjhhls.zhqzlsh),"ERROR")   
                iFlag = -5;
                break; 
        		}

            /* end add dci 20141103 */
            
            /* mod dci 20141103 
            EXEC SQL UPDATE tips_sszjhhls 
                 SET dzbz='2'
                 WHERE zwrq=:stZjhhls.zwrq
                   AND zhqzlsh=:stZjhhls.zhqzlsh;
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
            if(SQLERR)
            {
                LOG(LM_STD,Fmtmsg("更新资金汇划表失败,帐务日期[%s],前置流水号[%d]", 
                    stZjhhls.zwrq, stZjhhls.zhqzlsh),"ERROR")   
                iFlag = -5;
                break; 
            }
            */
        }/* for (i=1,iFlag=0;;i++) */ 
        /* add dci 20141103 */
        DCIFreeCursor(cur);
        /* end add dci 20141103 */
        
        /* mod dci 20141103   
        EXEC SQL CLOSE cur_zjhhdz; */
        
        if (iFlag < 0)
        {
            fpub_SetMsg(lXmlhandle,24426,"处理资金汇划对帐时前置成功主机失败的情况失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("处理资金汇划对帐时前置成功主机失败的情况失败iflag=[%d]",iFlag),
                fpub_GetCompname(lXmlhandle))
        }

    }/* if( iCount > 0 )与核心对账前置多的情况 */    
    LOG(LM_DEBUG,Fmtmsg("资金汇划对账结束,主机多[%d]笔, 前置多[%d]笔", 
        iZjdnum, iQzdnum), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle, 0, "资金汇划对账结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitHHLSPZ
组件名称: 初始实时汇划流水
组件功能: 
    初始实时汇划流水
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
tips_sszjhhls  税收资金汇划流水表

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年12月23日
修改日期: 2014年12月20日DCI改造，待测试
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitHHLSPZ(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         SDB_TIPS_SSZJHHLSPZ stZjhhlspz;
    /*EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
  	
    fpub_InitSoComp(lXmlhandle);

    memset(&stZjhhlspz, 0x00, sizeof(stZjhhlspz));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "帐务日期")
    pstrcopy( stZjhhlspz.zwrq, sBuf, sizeof(stZjhhlspz.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "清算批次号")
    pstrcopy( stZjhhlspz.qspch, sBuf, sizeof(stZjhhlspz.qspch));
           
    LOG(LM_STD,Fmtmsg("初始实时汇划流水凭证表 帐务日期[%s],清算批次号[%s]", 
        stZjhhlspz.zwrq, stZjhhlspz.qspch), fpub_GetCompname(lXmlhandle));    
		
		/* 2.前置流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    stZjhhlspz.zhqzlsh = atoi(sBuf);
    
    /* 3.对帐日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkDate", sBuf)
    pstrcopy( stZjhhlspz.chkdate, sBuf, sizeof(stZjhhlspz.chkdate));
    if ( stZjhhlspz.chkdate[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("对帐日期不能为空"));
        LOG(LM_STD,Fmtmsg("对帐日期不能为空, chkdate=[%s]", stZjhhlspz.chkdate),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 4.对帐批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy( stZjhhlspz.chkacctord, sBuf, sizeof(stZjhhlspz.chkacctord));
    if ( stZjhhlspz.chkacctord[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("对帐批次号不能为空"));
        LOG(LM_STD,Fmtmsg("对帐批次号不能为空, chkacctord=[%s]", stZjhhlspz.chkacctord),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 5.付款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy( stZjhhlspz.paybkcode, sBuf, sizeof(stZjhhlspz.paybkcode));
    if ( stZjhhlspz.paybkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("付款行行号不能为空"));
        LOG(LM_STD,Fmtmsg("付款行行号不能为空, paybkcode=[%s]", stZjhhlspz.paybkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 6.收款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy( stZjhhlspz.payeebankno, sBuf, sizeof(stZjhhlspz.payeebankno));
    if ( stZjhhlspz.payeebankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("收款行行号不能为空"));
        LOG(LM_STD,Fmtmsg("收款行行号不能为空, payeebankno=[%s]", stZjhhlspz.payeebankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 7.付款开户行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy( stZjhhlspz.payopbkcode, sBuf, sizeof(stZjhhlspz.payopbkcode));
    if ( stZjhhlspz.payopbkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("付款开户行行号不能为空"));
        LOG(LM_STD,Fmtmsg("付款开户行行号不能为空, payopbkcode=[%s]", stZjhhlspz.payopbkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 8.付款人账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy( stZjhhlspz.payacct, sBuf, sizeof(stZjhhlspz.payacct));
    if ( stZjhhlspz.payacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("付款人账号不能为空"));
        LOG(LM_STD,Fmtmsg("付款人账号不能为空, payacct=[%s]", stZjhhlspz.payacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 9.付款人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkName", sBuf)
    pstrcopy( stZjhhlspz.paybkname, sBuf, sizeof(stZjhhlspz.paybkname));
    if ( stZjhhlspz.paybkname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24279, Fmtmsg("付款人名称不能为空"));
        LOG(LM_STD,Fmtmsg("付款人名称不能为空, paybkname=[%s]", stZjhhlspz.paybkname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 10.收款开户行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOpBankNo", sBuf)
    pstrcopy( stZjhhlspz.payeeopbankno, sBuf, sizeof(stZjhhlspz.payeeopbankno));
    if ( stZjhhlspz.payeeopbankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24280, Fmtmsg("收款开户行行号不能为空"));
        LOG(LM_STD,Fmtmsg("收款开户行行号不能为空, payeeopbandno=[%s]", stZjhhlspz.payeeopbankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 11.收款人账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy( stZjhhlspz.payeeacct, sBuf, sizeof(stZjhhlspz.payeeacct));
    if ( stZjhhlspz.payeeacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24281, Fmtmsg("收款人账号不能为空"));
        LOG(LM_STD,Fmtmsg("收款人账号不能为空, payeeacct=[%s]", stZjhhlspz.payeeacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 12.收款人名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankName", sBuf)
    pstrcopy( stZjhhlspz.payeebankname, sBuf, sizeof(stZjhhlspz.payeebankname));
    if ( stZjhhlspz.payeebankname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24282, Fmtmsg("收款人名称不能为空"));
        LOG(LM_STD,Fmtmsg("收款人名称不能为空, payeebankname=[%s]", stZjhhlspz.payeebankname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 13.对帐类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctType", sBuf)
    pstrcopy( stZjhhlspz.chkaccttype, sBuf, sizeof(stZjhhlspz.chkaccttype));
    if ( stZjhhlspz.chkaccttype[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24283, Fmtmsg("对帐类型不能为空"));
        LOG(LM_STD,Fmtmsg("对帐类型不能为空, payeeacct=[%s]", stZjhhlspz.chkaccttype),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 14.批次笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllNum", sBuf)
    stZjhhlspz.allnum = atoi(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24284, Fmtmsg("批次笔数不能为空"));
        LOG(LM_STD,Fmtmsg("批次笔数不能为空, allnum=[%d]", stZjhhlspz.allnum),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 15.批次金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllAmt", sBuf)
    stZjhhlspz.allamt=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24285, Fmtmsg("批次金额不能为空"));
        LOG(LM_STD,Fmtmsg("批次金额不能为空, allamt=[%.2f]", stZjhhlspz.allamt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }   
    
    /* 16.交易笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jybs", sBuf)
    stZjhhlspz.jybs = atoi(sBuf);
    if ( sBuf[0] == '\0' )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24286, Fmtmsg("交易笔数不能为空"));
        LOG(LM_STD,Fmtmsg("交易笔数不能为空, jybs=[%d]", stZjhhlspz.jybs),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 17.交易金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyje", sBuf)
    stZjhhlspz.jyje=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24287, Fmtmsg("交易金额不能为空"));
        LOG(LM_STD,Fmtmsg("交易金额不能为空, jyje=[%.2f]", stZjhhlspz.jyje),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 18.附言 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/addword", sBuf)
    pstrcopy(stZjhhlspz.addword, sBuf, sizeof(stZjhhlspz.addword));
    if ( stZjhhlspz.addword[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24288, Fmtmsg("附言不能为空"));
        LOG(LM_STD,Fmtmsg("附言不能为空, addword=[%s]", stZjhhlspz.addword),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 19.交易日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyrq", sBuf)
    pstrcopy(stZjhhlspz.jyrq, sBuf, sizeof(stZjhhlspz.jyrq));
    if ( stZjhhlspz.jyrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24289, Fmtmsg("交易日期不能为空"));
        LOG(LM_STD,Fmtmsg("交易日期不能为空, jyrq=[%s]", stZjhhlspz.jyrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 20.交易时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jysj", sBuf)
    pstrcopy(stZjhhlspz.jysj, sBuf, sizeof(stZjhhlspz.jysj));
    if ( stZjhhlspz.jysj[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24290, Fmtmsg("交易时间不能为空"));
        LOG(LM_STD,Fmtmsg("交易时间不能为空, jysj=[%s]", stZjhhlspz.jysj),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 21.清算日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(stZjhhlspz.qsrq, sBuf, sizeof(stZjhhlspz.qsrq));
    if ( stZjhhlspz.qsrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24291, Fmtmsg("清算日期不能为空"));
        LOG(LM_STD,Fmtmsg("清算日期不能为空, qsrq=[%s]", stZjhhlspz.qsrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 22.清算流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qslsh", sBuf)
    stZjhhlspz.qslsh=atoi(sBuf);
    if ( stZjhhlspz.qslsh == 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24292, Fmtmsg("清算流水号不能为空"));
        LOG(LM_STD,Fmtmsg("清算流水号不能为空, qslsh=[%d]", stZjhhlspz.qslsh),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 23.业务种类 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ywzl", sBuf)
    pstrcopy(stZjhhlspz.ywzl, sBuf, sizeof(stZjhhlspz.ywzl));
    if ( stZjhhlspz.ywzl[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24293, Fmtmsg("业务种类不能为空"));
        LOG(LM_STD,Fmtmsg("业务种类不能为空, ywzl=[%s]", stZjhhlspz.ywzl),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 24.汇划次数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hhcs", sBuf)
    stZjhhlspz.hhcs=atoi(sBuf);

    /* 25.主机日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stZjhhlspz.zjrq, sBuf, sizeof(stZjhhlspz.zjrq));

    /* 26.主机时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stZjhhlspz.zjsj, sBuf, sizeof(stZjhhlspz.zjsj));

    /* 27.主机流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stZjhhlspz.zjlsh, sBuf, sizeof(stZjhhlspz.zjlsh));

    /* 28.交易状态 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stZjhhlspz.jyzt, sBuf, sizeof(stZjhhlspz.jyzt));
    if ( stZjhhlspz.jyzt[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24298, Fmtmsg("交易状态不能为空"));
        LOG(LM_STD,Fmtmsg("交易状态不能为空, jyzt=[%s]", stZjhhlspz.jyzt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 29.响应码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xym", sBuf)
    pstrcopy(stZjhhlspz.xym, sBuf, sizeof(stZjhhlspz.xym));
    if ( stZjhhlspz.xym[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24299, Fmtmsg("响应码不能为空"));
        LOG(LM_STD,Fmtmsg("响应码不能为空, xym=[%s]", stZjhhlspz.xym),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 30.响应信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xyxx", sBuf)
    pstrcopy(stZjhhlspz.xyxx, sBuf, sizeof(stZjhhlspz.xyxx));
    if ( stZjhhlspz.xyxx[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24300, Fmtmsg("响应信息不能为空"));
        LOG(LM_STD,Fmtmsg("响应信息不能为空, xyxx=[%s]", stZjhhlspz.xyxx),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 31.清算标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stZjhhlspz.qsbz, sBuf, sizeof(stZjhhlspz.qsbz));
    if ( stZjhhlspz.qsbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24301, Fmtmsg("清算标志不能为空"));
        LOG(LM_STD,Fmtmsg("清算标志不能为空, qsbz=[%s]", stZjhhlspz.qsbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 32.对账标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stZjhhlspz.dzbz, sBuf, sizeof(stZjhhlspz.dzbz));
    if ( stZjhhlspz.dzbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("对账标志不能为空"));
        LOG(LM_STD,Fmtmsg("对账标志不能为空, dzbz=[%s]", stZjhhlspz.dzbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 32.手工修改信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sgxgxx", sBuf)
    pstrcopy(stZjhhlspz.sgxgxx, sBuf, sizeof(stZjhhlspz.sgxgxx));

    /* 33.备用字段 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/byzd", sBuf)
    pstrcopy(stZjhhlspz.byzd, sBuf, sizeof(stZjhhlspz.byzd));
    
    /* 34.清算批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qspch", sBuf)
    pstrcopy(stZjhhlspz.qspch, sBuf, sizeof(stZjhhlspz.qspch));
    
    /* 35.打印次数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dycs", sBuf)
    stZjhhlspz.dycs=0;
    
    /* 36.交易类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qjylx", sBuf)
    pstrcopy(stZjhhlspz.qjylx, sBuf, sizeof(stZjhhlspz.qjylx));
        
    /* 37.清算类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qslx", sBuf)
    pstrcopy(stZjhhlspz.qslx, sBuf, sizeof(stZjhhlspz.qslx));    
		
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_sszjhhlspz", SD_TIPS_SSZJHHLSPZ, NUMELE(SD_TIPS_SSZJHHLSPZ), &stZjhhlspz, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
			fpub_SetMsg(lXmlhandle, 24308, "初始化税收资金汇划流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("初始化税收资金汇划流水表失败"), fpub_GetCompname(lXmlhandle))
        
        return COMPRET_FAIL;  
    }

		/* end add dci 20141103 */ 
		/* mod dci 20141103 
    EXEC SQL INSERT INTO tips_sszjhhlspz  VALUES (:stZjhhlspz);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24308, "初始化税收资金汇划流水表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("初始化税收资金汇划流水表失败"), fpub_GetCompname(lXmlhandle))
        
        return COMPRET_FAIL;         
    }	    
    */

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}   


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdZJHHPZ
组件名称: 更新资金实时汇划表
组件功能: 
  更新资金实时汇划表状态
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
税收资金汇划流水表	tips_sszjhhls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年12月23日
修改日期: 2014年12月20日DCI改造，待测试
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdZJHHPZ(HXMLTREE lXmlhandle)
{	
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sZwrq[8+1];
         int iZhqzlsh;
         char sJyzt[1+1];/* 交易状态 */
         char sQsrq[8+1];/* 清算日期 */
         int iQslsh;/* 清算流水号 */
         char sZjrq[8+1];/* 主机日期 */
         char sZjsj[8+1];/* 主机时间 */
         char sZjlsh[32+1];/* 主机流水号 */
         char sXym[5+1];/* 响应码 */
         char sXyxx[60+1];/* 响应信息 */
         char	sQspch[32+1];
         char sQsbz[1+1];
    /*EXEC SQL END DECLARE SECTION;*/
    
    char sBuf[256];
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
  	
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(12);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "账务日期")
    pstrcopy( sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "综合前置流水号")
    iZhqzlsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJyzt, 0x00, sizeof(sJyzt));
    COMP_GETPARSEPARAS(3, sBuf, "交易状态")
    pstrcopy( sJyzt, sBuf, sizeof(sJyzt));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_GETPARSEPARAS(4, sBuf, "清算日期")
    pstrcopy( sQsrq, sBuf, sizeof(sQsrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iQslsh=0;
    COMP_GETPARSEPARAS(5, sBuf, "清算流水号")
    iQslsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjrq, 0x00, sizeof(sZjrq));
    COMP_GETPARSEPARAS(6, sBuf, "主机日期")
    pstrcopy( sZjrq, sBuf, sizeof(sZjrq));       

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjsj, 0x00, sizeof(sZjsj));
    COMP_GETPARSEPARAS(7, sBuf, "主机时间")
    pstrcopy( sZjsj, sBuf, sizeof(sZjsj));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjlsh, 0x00, sizeof(sZjlsh));
    COMP_GETPARSEPARAS(8, sBuf, "主机流水号")
    pstrcopy( sZjlsh, sBuf, sizeof(sZjlsh));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXym, 0x00, sizeof(sXym));
    COMP_GETPARSEPARAS(9, sBuf, "响应码")
    pstrcopy( sXym, sBuf, sizeof(sXym));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXyxx, 0x00, sizeof(sXyxx));
    COMP_GETPARSEPARAS(10, sBuf, "响应信息")
    pstrcopy( sXyxx, sBuf, sizeof(sXyxx));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQspch, 0x00, sizeof(sQspch));
    COMP_GETPARSEPARAS(11, sBuf, "清算批次号")
    pstrcopy( sQspch, sBuf, sizeof(sQspch));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsbz, 0x00, sizeof(sQsbz));
    COMP_GETPARSEPARAS(12, sBuf, "清算标识")
    pstrcopy( sQsbz, sBuf, sizeof(sQsbz));
    
    LOG(LM_STD,Fmtmsg("更新资金实时汇划表开始处理...帐务日期[%s]前置流水号=[%d]交易状态=[%s]",sZwrq, iZhqzlsh, sJyzt),"INFO")
    LOG(LM_STD,Fmtmsg("清算日期[%s]清算流水号=[%d]主机日期=[%s]主机时间=[%s]主机流水号[%s]", sQsrq, iQslsh, sZjrq, sZjsj, sZjlsh),"INFO")
    LOG(LM_STD,Fmtmsg("响应码=[%s]响应信息[%s]", sXym, sXyxx),"INFO")
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhls \
    		set jyzt  ='%s',\
    				hhcs  =hhcs + 1,\
    				qsrq  ='%s',\
    				qslsh =%d,\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s',\
    				xym   ='%s',\
    				xyxx  ='%s',\
    				qsbz  ='%s'\
    			where zwrq='%s' and zhqzlsh=%d", \
      sJyzt ,sQsrq  ,iQslsh ,sZjrq  ,sZjsj  ,sZjlsh ,sXym   ,sXyxx  ,sQsbz  ,sZwrq  ,iZhqzlsh);   
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "实时资金实时汇划凭证表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("实时资金实时汇划凭证表失败"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24286, "更新失败-->实时资金实时汇划凭证表记录未找到");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("更新失败-->实时资金实时汇划表记凭证录未找到"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;		
    }	
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhlspz \
    		set jyzt  ='%s',\
    				hhcs  =hhcs + 1,\
    				qsrq  ='%s',\
    				qslsh =%d,\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s',\
    				xym   ='%s',\
    				xyxx  ='%s',\
    				qsbz  ='%s'\
    			where byzd ='%s' " \
             ,sJyzt  \
             ,sQsrq  \
             ,iQslsh \
             ,sZjrq  \
             ,sZjsj  \
             ,sZjlsh \
             ,sXym   \
             ,sXyxx  \
             ,sQsbz  \
             ,sQspch);   

    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "实时资金实时汇划凭证表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("实时资金实时汇划凭证表失败"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24286, "更新失败-->实时资金实时汇划凭证表记录未找到");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("更新失败-->实时资金实时汇划表记凭证录未找到"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;		
    }	
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_sszjhhlspz
    	   SET jyzt = :sJyzt,
    	       hhcs = hhcs + 1,
    	       qsrq = :sQsrq,
    	       qslsh = :iQslsh,
    	       zjrq = :sZjrq,
    	       zjsj = :sZjsj,
    	       zjlsh = :sZjlsh,
    	       xym = :sXym,
    	       xyxx = :sXyxx,
    	       qsbz = :sQsbz
         WHERE zwrq = :sZwrq 
           AND qspch = :sQspch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "实时资金实时汇划凭证表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("实时资金实时汇划凭证表失败"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND )	
    {
         fpub_SetMsg(lXmlhandle, 24286, "更新失败-->实时资金实时汇划凭证表记录未找到");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("更新失败-->实时资金实时汇划表记凭证录未找到"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	  
    
    EXEC SQL UPDATE tips_sszjhhls
    	SET jyzt = :sJyzt,
    	       hhcs = hhcs + 1,
    	       qsrq = :sQsrq,
    	       qslsh = :iQslsh,
    	       zjrq = :sZjrq,
    	       zjsj = :sZjsj,
    	       zjlsh = :sZjlsh,
    	       xym = :sXym,
    	       xyxx = :sXyxx,
    	       qsbz = :sQsbz
         WHERE byzd = :sQspch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")       	
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "实时资金实时汇划表失败"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("实时资金实时汇划表失败"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND )	
    {
         fpub_SetMsg(lXmlhandle, 24286, "更新失败-->实时资金实时汇划表记录未找到");
         EXEC SQL rollback;
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("更新失败-->实时资金实时汇划表记录未找到"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    */ 
           	
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 
