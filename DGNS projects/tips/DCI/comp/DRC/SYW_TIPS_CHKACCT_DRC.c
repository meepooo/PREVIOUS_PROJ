/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V3.0.00
  操作系统:AIX5.3
  文件名称:SYW_TIPS_CHKACCT_DRC.ec
  文件描述:TIPS对帐交易组件集
  项 目 组:TIPS专用前置产品组
  程 序 员:sunpj
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

#include  "../../eh/tips_drls.h"   
#include  "../../eh/tips_ssplksfmx.h"
#include  "../../eh/tips_pljydj.h"
#include  "../../eh/tips_dzbpdj.h"

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_RZTZ
  组件名称: TIPS日终调账

  组件功能: 
  TIPS日终调账
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  1                  需上核心调账
  0                  调账成功
  -1　　　　　　　　 调账失败

  主要操作库表:
  表名              操作
  当日流水表        tips_drls
  批量扣税明细表    tips_ssplksfmx
  批量交易登记表    tips_pljydj
  对账不平登记表    tips_dzbpdj

  项 目 组: TIPS专用前置产品组
  程 序 员: sunpj
  发布日期: 2017年04月26日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_RZTZ(HXMLTREE lXmlhandle)
{
    int iParas;
    int iSqlRet = 0;
    int iRet = 0;
    
    char cTranDate[8+1]; /* 原交易日期 */
    char cTranSeq[16+1]; /* 原交易流水 */
    char cChkType[1+1];  /* 对账类型 */
    char cChgDate[8+1];  /* 处理日期 */
    char cChgTime[6+1];  /* 处理时间 */
    char cChgSeq[16+1];  /* 处理流水 */
    char cChgFlag[4+1];  /* 调账标志 0-调账 1-手工调账 */
    char cIsBatch[1+1];  /* 批量扣税费标志 */
    char cChkFlag[1+1];  /* 流水表对账标志 */
    char cSql[1024+1];   /* SQL语句 */
    char cTmp[128+1];
    char cErrmsg[256+1];
    
    SDB_TIPS_DRLS stDrls;
    SDB_TIPS_SSPLKSFMX stPlksfmx;
    SDB_TIPS_DZBPDJ stDzbpdj;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_RZTZ...处理开始"), "INFO") 
    
    COMP_PARACOUNTCHK(4);
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cTranDate, 0x00, sizeof(cTranDate));
    COMP_GETPARSEPARAS(1, cTmp, "原交易日期");
    pstrcopy(cTranDate, cTmp, sizeof(cTranDate));
    LOG(LM_DEBUG, Fmtmsg("原交易日期[%s]", cTranDate), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cTranSeq, 0x00, sizeof(cTranSeq));
    COMP_GETPARSEPARAS(2, cTmp, "原交易流水");
    pstrcopy(cTranSeq, cTmp, sizeof(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("原交易流水[%s]", cTranSeq), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cChkType, 0x00, sizeof(cChkType));
    COMP_GETPARSEPARAS(3, cTmp, "对账类型");
    pstrcopy(cChkType, cTmp, sizeof(cChkType));
    LOG(LM_DEBUG, Fmtmsg("对账类型[%s]", cChkType), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cChgFlag, 0x00, sizeof(cChgFlag));
    COMP_GETPARSEPARAS(4, cTmp, "调账标志");
    pstrcopy(cChgFlag, cTmp, sizeof(cChgFlag));
    LOG(LM_DEBUG, Fmtmsg("调账标志[%s]", cChgFlag), "INFO") 
    
    memset(cSql, 0x00, sizeof(cSql));
    memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
    sprintf(cSql, "select * from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                , cTranDate, atol(cTranSeq), cChkType);
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("查询不平明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "查询不平明细表失败");
        return -1;
    }
    else if(0 == iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("对账不平信息不存在"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "对账不平信息不存在，请确认");
        return -1;
    }
    if (0 == memcmp(stDzbpdj.clzt, "3", 1))
    {
        LOG(LM_STD, Fmtmsg("已调帐"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "已调帐");
        return -1;
    }
    else if (0 == memcmp(stDzbpdj.clzt, "9", 1))
    {
        LOG(LM_STD, Fmtmsg("处理中..."), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "处理中，请确认");
        return -1;
    }
    else if (0 == memcmp(stDzbpdj.clzt, "0", 1))
    {
        trim(stDzbpdj.jyzh);
        if (0 == strlen(stDzbpdj.jyzh) && 0 == memcmp(cChgFlag, "ZCTZ", 4))
        {
            LOG(LM_STD, Fmtmsg("现金交易必须手工调账"), "ERROR")
            memset(cSql, 0x00, sizeof(cSql));
            memset(cChgDate, 0x00, sizeof(cChgDate));
        		memset(cChgTime, 0x00, sizeof(cChgTime));
        		memset(cChgSeq, 0x00, sizeof(cChgSeq));
       			COMP_SOFTGETXML("/pub/zwrq", cChgDate);
        		COMP_SOFTGETXML("/sys/systime", cChgTime);
        		COMP_SOFTGETXML("/pub/zhqzlsh", cChgSeq);
						sprintf(cSql, "update tips_dzbpdj set clrq='%s',clsj='%s',cllsh=%ld, clzt='1' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                ,cChgDate, cChgTime, atol(cChgSeq), cTranDate, atol(cTranSeq), cChkType);
    				LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    				iSqlRet = DCIExecuteDirect(cSql);
    				if (0 > iSqlRet)
    				{
        			LOG(LM_STD, Fmtmsg("更新对账不平表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
       				fpub_SetCompStatus(lXmlhandle, -1);
        			fpub_SetMsg(lXmlhandle, 100001, "更新对账不平表失败");
       				return -1;
    				}
    				iSqlRet = DCICommit();
    				if ( iSqlRet < 0 )
   					 {
      					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      					DCIRollback();     	
    				  	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
  				     	return COMPRET_FAIL;     
   					 }
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "现金交易请用手工调账");
            return -1;
        }
        if (0 != strlen(stDzbpdj.jyzh) && 0 == memcmp(cChgFlag, "SGTZ", 4))
        {
            LOG(LM_STD, Fmtmsg("该交易不可手工调账"), "ERROR")
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "该交易不可手工调账,请先调账");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        memset(cChgDate, 0x00, sizeof(cChgDate));
        memset(cChgTime, 0x00, sizeof(cChgTime));
        memset(cChgSeq, 0x00, sizeof(cChgSeq));
        COMP_SOFTGETXML("/pub/zwrq", cChgDate);
        COMP_SOFTGETXML("/sys/systime", cChgTime);
        COMP_SOFTGETXML("/pub/zhqzlsh", cChgSeq);
        sprintf(cSql, "update tips_dzbpdj set clrq='%s',clsj='%s',cllsh=%ld,clzt='9' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                    , cChgDate, cChgTime, atol(cChgSeq), cTranDate, atol(cTranSeq), cChkType);
        pstrcopy(stDzbpdj.clrq, cChgDate, sizeof(stDzbpdj.clrq));
        stDzbpdj.cllsh=atol(cChgSeq);
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    } 
    else
    {
    	  trim(stDzbpdj.jyzh);
        if (0 == strlen(stDzbpdj.jyzh) && 0 == memcmp(cChgFlag, "ZCTZ", 4))
        {
            LOG(LM_STD, Fmtmsg("现金交易必须手工调账"), "ERROR")
            memset(cSql, 0x00, sizeof(cSql));
            memset(cChgDate, 0x00, sizeof(cChgDate));
        		memset(cChgTime, 0x00, sizeof(cChgTime));
        		memset(cChgSeq, 0x00, sizeof(cChgSeq));
       			COMP_SOFTGETXML("/pub/zwrq", cChgDate);
        		COMP_SOFTGETXML("/sys/systime", cChgTime);
        		COMP_SOFTGETXML("/pub/zhqzlsh", cChgSeq);
						sprintf(cSql, "update tips_dzbpdj set clrq='%s',clsj='%s',cllsh=%ld, clzt='1' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                ,cChgDate, cChgTime, atol(cChgSeq), cTranDate, atol(cTranSeq), cChkType);
    				LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    				iSqlRet = DCIExecuteDirect(cSql);
    				if (0 > iSqlRet)
    				{
        			LOG(LM_STD, Fmtmsg("更新对账不平表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
       				fpub_SetCompStatus(lXmlhandle, -1);
        			fpub_SetMsg(lXmlhandle, 100001, "更新对账不平表失败");
       				return -1;
    				}
    				iSqlRet = DCICommit();
    				if ( iSqlRet < 0 )
   					 {
      					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      					DCIRollback();     	
    				  	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
  				     	return COMPRET_FAIL;     
   					 }
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "现金交易请用手工调账");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='9' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                    , cTranDate, atol(cTranSeq), cChkType);
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    }
    iSqlRet = DCIExecuteDirect(cSql);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("更新对账不平表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "更新对账不平表失败");
        return -1;
    }
    /*modify by liurj 20181018 add commit begin*/
	iSqlRet = DCICommit();
	if ( iSqlRet < 0 )
	{
	  LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
	  DCIRollback();
	  fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
	  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	  return COMPRET_FAIL;
	}
    /*modify by liurj 20181018 add commit end*/

    
    /* 查询原交易信息 */
    memset(cSql, 0x00, sizeof(cSql));
    sprintf(cSql, "select * from tips_drls where zwrq='%s' and zhqzlsh=%ld", cTranDate, atol(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("查询当日流水表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "查询当日流水表失败");
        return -1;
    }
    else if (0 == iSqlRet)
    {
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select * from tips_ssplksfmx where zwrq='%s' and plmxxh=%ld", cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
        iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
        if(0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("查询批量明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
            return -1;
        }
        else if(0 == iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("原交易信息不存在"), "ERROR")
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "原交易信息不存在，请确认");
            return -1;
        }
        strcpy(cIsBatch, "Y");
        memcpy(cChkFlag, stPlksfmx.kzbz, 2);
        memcpy(stDrls.workdate, stPlksfmx.workdate, sizeof(stDrls.workdate));
        memcpy(stDrls.paybkcode, stPlksfmx.paybkcode, sizeof(stDrls.paybkcode));
        memcpy(stDrls.payeebankno, stPlksfmx.payeebankno, sizeof(stDrls.payeebankno));
        COMP_SOFTSETXML("/tips/ylsxx/msgno", "3102");
    }
    else
    {
        strcpy(cIsBatch, "N");
        memcpy(cChkFlag, stDrls.dzbz, 2);
        COMP_SOFTSETXML("/tips/ylsxx/msgno", stDrls.msgno);
    }
    
    LOG(LM_STD, Fmtmsg("对账类型[%s]...对账结果[%s]...流水表对账标志[%s]", stDzbpdj.dzlx, stDzbpdj.dzjg, cChkFlag), "ERROR")
    if (0 == memcmp(stDzbpdj.dzlx, "1", 1) && 0 == memcmp(stDzbpdj.dzjg, "2", 1))
    {
        //核心对账 前置多
        iRet = prv_rztz_qzdz(lXmlhandle, 1, cIsBatch, stDrls.workdate, stDrls.paybkcode
                              , stDrls.payeebankno, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("调账失败...[%d]", iRet), "ERROR")
            return -1;
        }
    }
    else if (0 == memcmp(stDzbpdj.dzlx, "1", 1) && 0 == memcmp(stDzbpdj.dzjg, "3", 1))
    {
        //核心对账 核心多
        iRet = prv_rztz_hxdz(lXmlhandle, cIsBatch, stDrls.workdate, stDrls.paybkcode
                              , stDrls.payeebankno, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("调账失败...[%d]", iRet), "ERROR")
            return -1;
        }
    }
    else if ((0 == memcmp(stDzbpdj.dzlx, "2", 1) || 0 == memcmp(stDzbpdj.dzlx, "3", 1))
             && 0 == memcmp(stDzbpdj.dzjg + 1, "2", 1))
    {
        //人行对账 前置多
        iRet = prv_rztz_qzdz(lXmlhandle, 2, cIsBatch, stDrls.workdate, stDrls.paybkcode
                              , stDrls.payeebankno, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("调账失败...[%d]", iRet), "ERROR")
            return -1;
        }
    }
    else if ((0 == memcmp(stDzbpdj.dzlx, "2", 1) || 0 == memcmp(stDzbpdj.dzlx, "3", 1))
             && 0 == memcmp(stDzbpdj.dzjg + 1, "3", 1))
    {
        //人行对账 人行多
        iRet = prv_rztz_rhdz(lXmlhandle, cIsBatch, stDrls.workdate, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("调账失败...[%d]", iRet), "ERROR")
            return iRet;
        }
    }
    else
    {
        LOG(LM_STD, Fmtmsg("该交易未对账或已对平"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "该交易未对账或已对平");
        return -1;
    }
    
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips_host/req/jydm", cTmp);
    LOG(LM_DEBUG, Fmtmsg("调账类型[%s]调账标志[%s]", cChgFlag, cTmp), "INFO")
    if (0 == memcmp(cChgFlag, "ZCTZ", 4) && 0 == memcmp(cTmp, "dbzz", 4))
    {
        COMP_SOFTSETXML("/tips/dzbpxx/detail/clrq", stDzbpdj.zwrq);
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "%d", stDzbpdj.zhqzlsh);
        COMP_SOFTSETXML("/tips/dzbpxx/detail/cllsh", cTmp);
    }
    else
    {
        COMP_SOFTSETXML("/tips/dzbpxx/detail/clrq", stDzbpdj.clrq);
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "%d", stDzbpdj.cllsh);
        COMP_SOFTSETXML("/tips/dzbpxx/detail/cllsh", cTmp);
    }
    COMP_SOFTSETXML("/tips/dzbpxx/detail/paybkcode", stDzbpdj.paybkcode);
    COMP_SOFTSETXML("/tips/dzbpxx/detail/jyzh", stDzbpdj.jyzh);
    COMP_SOFTSETXML("/tips/dzbpxx/detail/dfzh", stDzbpdj.dfzh);
    memset(cTmp, 0x00, sizeof(cTmp));
    sprintf(cTmp, "%.2f", stDzbpdj.jyje);
    COMP_SOFTSETXML("/tips/dzbpxx/detail/jyje", cTmp);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_RZTZ...处理结束"), "INFO") 
    return iRet;
}

int prv_rztz_hxdz(HXMLTREE lXmlhandle, char *cIsBatch, char *cChkDate
                   , char *cPayBkCode, char *cPayeeBankNo
                   , char *cTranDate, char *cTranSeq)
{
    int iSqlRet = 0;
    
    char cSql[1024+1];  /* SQL语句 */
    char cChkRlt[2+1];  /* 对账结果 */
    char cErrmsg[256+1];
    char cChkAcctOrd[4+1];/* 对账批次号 */
    
    memset(cChkRlt, 0x00, sizeof(cChkRlt));
    memset(cSql, 0x00, sizeof(cSql));
    sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='3' and (clzt='0' or clzt='1')"
                 , cTranDate, atol(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("查询对账不平明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "查询对账不平明细表失败");
        return -1;
    }
    if (0 == iSqlRet)
    {
        /* 到tips_ssdzplt表中去查询此工作日是否已对帐 */
        memset(cChkAcctOrd, 0x00, sizeof(cChkAcctOrd));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select chkacctord from tips_ssdzplt where chkdate='%s' and paybkcode='%s'"
                " and payeebankno='%s' and chkaccttype='1'", cChkDate, cPayBkCode, cPayeeBankNo);
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
        iSqlRet = DBSelectToVar(cErrmsg, cChkAcctOrd, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("查询TIPS对账表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询TIPS对账表失败");
            return -1;
        }
        if (0 == iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("本条记录,由于核心多,未与TIPS对账,暂不处理."), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "TIPS未对账，暂不处理");
            return -1;
        }
        LOG(LM_STD, Fmtmsg("本条记录,由于核心多,前置与TIPS都失败,需上核心抹账处理."), "ERROR")
        COMP_SOFTSETXML("/tips_host/req/jydm", "dbmz");
        COMP_SOFTSETXML("/tips/xyxx", "被日终抹帐");
        COMP_SOFTSETXML("/tips/jyzt", "3");
        return 1;
        
    }
    
    trim(cChkRlt);
    if (0 == memcmp(cChkRlt + 1, "3", 1)) /* 若对账结果为93-与TIPS对账,他方多,只需将原流水状态更改为成功 */
    {
        LOG(LM_STD,Fmtmsg("本条记录,由于核心多,TIPS也多,需将原流水状态更改为成功即可."),"INFO");
        
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='3' where zwrq='%s' and zhqzlsh=%ld"
                    , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("更新对账不平表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "更新对账不平表失败");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            sprintf(cSql, "update tips_ssplksfmx set kzbz='11'||substr(kzbz,3,6),czbd='7' where zwrq='%s' and plmxxh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        else
        {
            sprintf(cSql, "update tips_drls set dzbz='11',jyzt='0' where zwrq='%s' and zhqzlsh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("更新流水表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "更新流水表失败");
            return -1;
        }
        return 0;
    }
    else /* 若对账结果为92-与TIPS对账,我方多 */
    {
        LOG(LM_STD,Fmtmsg("TIPS对账结果[%c]", cChkRlt[1]),"INFO");
        fpub_SetMsg(lXmlhandle, 100001, "系统错误，无法调账，请确认");
        return -1;
    }
    
    return 0;
}

int prv_rztz_rhdz(HXMLTREE lXmlhandle, char *cIsBatch, char *cChkDate
                   , char *cTranDate, char *cTranSeq)
{
    int iSqlRet = 0;
    char cErrmsg[256+1];
    
    char cSql[1024+1];  /* SQL语句 */
    char cChkRlt[2+1];  /* 对账结果 */
    char cBuf[256];
    char cIniFile[256];
    char cIsPldz[1+1];/* 核心批量是否参与对账 */
    char cChkState[1+1];
    
    if (0 == memcmp(cIsBatch, "Y", 1))
    {
        memset(cIniFile, 0x00, sizeof(cIniFile));
        snprintf(cIniFile, sizeof(cIniFile), "%s/etc/tips.ini", getenv("HOME"));
        memset(cBuf, 0x00, sizeof(cBuf));
        memset(cIsPldz, 0x00, sizeof(cIsPldz));
        if(ExGetCfgItem(cIniFile, "HXDZ", "PLDZ", cBuf,sizeof(cBuf))<0)
        {
            cBuf[0]='1';/* 1-参加(缺省) */
        }
        pstrcopy(cIsPldz, cBuf, sizeof(cIsPldz));

        if (0 == memcmp(cIsPldz, "0", 1))/* 核心批量不参与对帐,此时需上送核心补账 */
        {
            LOG(LM_STD,Fmtmsg("本条记录,由于TIPS多,前置与核心不对账,缺省对平,需上核心补账处理."),"INFO");
            COMP_SOFTSETXML("/tips_host/req/jydm", "dbzz");
            COMP_SOFTSETXML("/tips/xyxx", "被日终补帐");
            COMP_SOFTSETXML("/tips/jyzt", "4");
            return 1;
        }
    }
    
    memset(cChkRlt, 0x00, sizeof(cChkRlt));
    memset(cSql, 0x00, sizeof(cSql));
    sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='1' and (clzt='0' or clzt='1')"
                 , cTranDate, atol(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("查询对账不平明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "查询对账不平明细表失败");
        return -1;
    }
    else if (0 == iSqlRet)
    {
        /* 到tips_checkresult表中去查询此工作日是否已对帐 */
        memset(cChkState, 0x00, sizeof(cChkState));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select checkstate from tips_checkresult where checkdate='%s' and checksystem='00' and checkstate='0'", cChkDate);
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
        iSqlRet = DBSelectToVar(cErrmsg, cChkState, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("查询核心对账表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询核心对账表失败");
            return -1;
        }
        if (0 == iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("本条记录,由于TIPS多,未与核心对账,暂不处理."), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "核心未对账，暂不处理");
            return -1;
        }
        LOG(LM_STD, Fmtmsg("本条记录,由于TIPS多,前置与核心都失败,需上核心补帐处理."), "ERROR")
        COMP_SOFTSETXML("/tips_host/req/jydm", "dbzz");
        COMP_SOFTSETXML("/tips/xyxx", "被日终补帐");
        COMP_SOFTSETXML("/tips/jyzt", "4");
        return 1;
    }
    
    trim(cChkRlt);
    if (0 == memcmp(cChkRlt, "3", 1)) /* 若对账结果为39-与核心对账,核心多,只需将原流水状态更改为成功 */
    {
        LOG(LM_STD,Fmtmsg("本条记录,由于核心多,TIPS也多,需将原流水状态更改为成功即可."),"INFO");
        
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='3' where zwrq='%s' and zhqzlsh=%ld"
                    , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("更新对账不平表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "更新对账不平表失败");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            sprintf(cSql, "update tips_ssplksfmx set kzbz='11'||substr(kzbz,3,6),czbd='7' where zwrq='%s' and plmxxh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        else
        {
            sprintf(cSql, "update tips_drls set dzbz='11',jyzt='0' where zwrq='%s' and zhqzlsh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("更新流水表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "更新流水表失败");
            return -1;
        }
        return 0;
    }
    else /* 若对账结果为29-与核心对账,前置多 */
    {
        LOG(LM_STD,Fmtmsg("核心对账结果[%c]", cChkRlt[0]),"INFO");
        fpub_SetMsg(lXmlhandle, 100001, "系统错误，无法调账，请确认");
        return -1;
    }
    
    return 0;
}

int prv_rztz_qzdz(HXMLTREE lXmlhandle, int iChkType, char *cIsBatch
                   , char *cChkDate , char *cPayBkCode, char *cPayeeBankNo
                   , char *cTranDate, char *cTranSeq)
{
    int iSqlRet = 0;
    int iIsFailed = 0;
    
    char cSql[1024+1];  /* SQL语句 */
    char cChkRlt[2+1];  /* 对账结果 */
    char cBuf[256];
    char cIniFile[256];
    char cIsPldz[1+1];/* 核心批量是否参与对账 */
    char cChkState[1+1];
    char cErrmsg[256+1];
    char cChkAcctOrd[4+1];/* 对账批次号 */
    
    if (1 == iChkType)/* 与核心对账 前置多 */
    {
        memset(cChkRlt, 0x00, sizeof(cChkRlt));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='3' and (clzt='0' or clzt='1')"
                     , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
        iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("查询对账不平明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询对账不平明细表失败");
            return -1;
        }
        if (0 == iSqlRet)
        {
            /* 到tips_ssdzplt表中去查询此工作日是否已对帐 */
            memset(cChkAcctOrd, 0x00, sizeof(cChkAcctOrd));
            memset(cSql, 0x00, sizeof(cSql));
            sprintf(cSql, "select chkacctord from tips_ssdzplt where chkdate='%s' and paybkcode='%s'"
                    " and payeebankno='%s' and chkaccttype='1'", cChkDate, cPayBkCode, cPayeeBankNo);
            LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
            iSqlRet = DBSelectToVar(cErrmsg, cChkAcctOrd, cSql);
            if (0 > iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("查询TIPS对账表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "查询TIPS对账表失败");
                return -1;
            }
            if (0 == iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("本条记录,由于前置多,未与TIPS对账,暂不处理."), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "TIPS未对账，暂不处理");
                return -1;
            }
            LOG(LM_STD, Fmtmsg("本条记录,由于TIPS、前置多,核心未记账,需上核心补帐处理."), "ERROR")
            COMP_SOFTSETXML("/tips_host/req/jydm", "dbzz");
            COMP_SOFTSETXML("/tips/xyxx", "被日终补帐");
            COMP_SOFTSETXML("/tips/jyzt", "4");
            return 1;
        }
        
        trim(cChkRlt);
        if (0 == memcmp(cChkRlt + 1, "2", 1))/* 若对账结果为92-与TIPS对账,前置多 */
        {
            LOG(LM_STD,Fmtmsg("本条记录,由于前置多,TIPS、核心未记账,需将原流水状态更改为失败即可."),"INFO");
            iIsFailed = 1;
        }
        else
        {
            LOG(LM_STD,Fmtmsg("TIPS对账结果[%c]", cChkRlt[1]),"INFO");
            fpub_SetMsg(lXmlhandle, 100001, "系统错误，无法调账，请确认");
            return -1;
        }
    }
    else /* 与TIPS对账 前置多 */
    {
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            memset(cIniFile, 0x00, sizeof(cIniFile));
            snprintf(cIniFile, sizeof(cIniFile), "%s/etc/tips.ini", getenv("HOME"));
            memset(cBuf, 0x00, sizeof(cBuf));
            memset(cIsPldz, 0x00, sizeof(cIsPldz));
            if(ExGetCfgItem(cIniFile, "HXDZ", "PLDZ", cBuf,sizeof(cBuf))<0)
            {
                cBuf[0]='1';/* 1-参加(缺省) */
            }
            pstrcopy(cIsPldz, cBuf, sizeof(cIsPldz));
    
            if (0 == memcmp(cIsPldz, "0", 1))/* 核心批量不参与对帐,此时需上送核心抹账 */
            {
                LOG(LM_STD,Fmtmsg("本条记录,由于TIPS无,前置与核心不对账,缺省对平,需上核心抹账处理."),"INFO");               
                COMP_SOFTSETXML("/tips_host/req/jydm", "dbmz");
                COMP_SOFTSETXML("/tips/xyxx", "被日终抹帐");
                COMP_SOFTSETXML("/tips/jyzt", "3");
                return 1;
            }
        }
        
        memset(cChkRlt, 0x00, sizeof(cChkRlt));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='1' and (clzt='0' or clzt='1')"
                     , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
        iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("查询对账不平明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询对账不平明细表失败");
            return -1;
        }
        else if (0 == iSqlRet)
        {
            /* 到tips_checkresult表中去查询此工作日是否已对帐 */
            memset(cChkState, 0x00, sizeof(cChkState));
            memset(cSql, 0x00, sizeof(cSql));
            sprintf(cSql, "select checkstate from tips_checkresult where checkdate='%s' and checksystem='00' and checkstate='0'", cChkDate);
            LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
            iSqlRet = DBSelectToVar(cErrmsg, cChkState, cSql);
            if (0 > iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("查询核心对账表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "查询核心对账表失败");
                return -1;
            }
            if (0 == iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("本条记录,由于TIPS少，前置多,未与核心对账,暂不处理."), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "核心未对账，暂不处理");
                return -1;
            }
            LOG(LM_STD, Fmtmsg("本条记录,由于TIPS未记账，前置、核心多帐账,需上核心抹账处理."), "ERROR")     
            COMP_SOFTSETXML("/tips_host/req/jydm", "dbmz");
            COMP_SOFTSETXML("/tips/xyxx", "被日终抹帐");
            COMP_SOFTSETXML("/tips/jyzt", "3");
            return 1;
        }
        
        trim(cChkRlt);
        if (0 == memcmp(cChkRlt, "2", 1))/* 若对账结果为29-与核心对账,前置多 */
        {
            LOG(LM_STD,Fmtmsg("本条记录,由于前置多,TIPS、核心未记账,需将原流水状态更改为失败即可."),"INFO");
            iIsFailed = 1;
        }
        else
        {
            LOG(LM_STD,Fmtmsg("核心对账结果[%c]", cChkRlt[0]),"INFO");
            fpub_SetMsg(lXmlhandle, 100001, "系统错误，无法调账，请确认");
            return -1;
        }
    }
    
    if (1 == iIsFailed)
    {
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='3' where zwrq='%s' and zhqzlsh=%ld"
                    , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("更新对账不平表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "更新对账不平表失败");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            sprintf(cSql, "update tips_ssplksfmx set kzbz='11'||substr(kzbz,3,6),czbd='8' where zwrq='%s' and plmxxh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        else
        {
            sprintf(cSql, "update tips_drls set dzbz='11',jyzt='1' where zwrq='%s' and zhqzlsh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("更新流水表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "更新流水表失败");
            return -1;
        }
    }
    
    return 0;
}
