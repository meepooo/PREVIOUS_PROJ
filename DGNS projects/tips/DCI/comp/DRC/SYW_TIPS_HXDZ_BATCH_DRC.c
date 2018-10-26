/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V3.0.00
  操作系统:AIX5.3
  文件名称:SYW_TIPS_HXDZ_BATCH_DRC.ec
  文件描述:TIPS对帐交易组件集
  项 目 组:TIPS专用前置产品组
  程 序 员:刘如杰
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
  
#include  "../../eh/tips_ssplksfmx.h"
#include  "../../eh/tips_pljydj.h"
#include  "../../eh/tips_dzbpdj.h"

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_HXDZ_PL
  组件名称: TIPS核心对账批量处理

  组件功能: 
  TIPS核心对账对批量扣税明细的处理
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  批量明细添加到不平明细登记表成功
  -1　　　　　　　　 批量明细处理失败

  主要操作库表:
  表名              操作
  批量扣税明细表    tips_ssplksfmx
  批量交易登记表    tips_pljydj
  对账不平登记表    tips_dzbpdj

  项 目 组: TIPS专用前置产品组
  程 序 员: 刘如杰
  发布日期: 2017年06月16日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_HXDZ_PL(HXMLTREE lXmlhandle)
{
    int iParas;
    int iSqlRet = 0;
    int iRet = 0;        /* 子函数的返回结果 */
    char cCountNum[12+1];   /* 当天没有取回结果的批量包扣款成功的记录条数 */
    int iCountNum = 0;
    
    char cSql[1024+1];   /* SQL语句 */
    char cDzrq[8+1];     /* 对账日期 */
    char cPljylsh[8+1];   /* 批量交易流水号 */
    char cTmp[128+1];
    char cErrmsg[256+1];
    

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_HXDZ_PL...处理开始"), "INFO") 
    
    COMP_PARACOUNTCHK(2);
    
    memset(cTmp, 0x00, sizeof(cTmp)); 
    memset(cDzrq, 0x00, sizeof(cDzrq));   
    COMP_GETPARSEPARAS(1, cTmp, "对账日期");
    pstrcopy(cDzrq, cTmp, sizeof(cDzrq)); 
    LOG(LM_DEBUG, Fmtmsg("对账日期[%s]", cDzrq), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp)); 
    memset(cPljylsh, 0x00, sizeof(cPljylsh));   
    COMP_GETPARSEPARAS(2, cTmp, "批量交易流水号");
    pstrcopy(cPljylsh, cTmp, sizeof(cPljylsh)); 
    LOG(LM_DEBUG, Fmtmsg("批量交易流水号[%s]", cPljylsh), "INFO") 
    
    memset(cSql, 0x00, sizeof(cSql)); 
    memset(cErrmsg, 0x00, sizeof(cErrmsg));   
    sprintf(cSql, "select count(*) from tips_ssplksfmx where zwrq='%s' and pljylsh='%s' and czbd='7'", cDzrq, cPljylsh);
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO");
    iSqlRet = DBSelectToVarChar(cErrmsg, cCountNum, cSql);
   /* iSqlRet = DCIExecuteDirect(cSql); */
    if (0 > iSqlRet)
    	{
    		LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 100001, "查询批量扣税费明细表失败");
        return COMPRET_FAIL;
    	}
    else 
    	{
    		iCountNum = atoi(cCountNum);
    		if (0 == iCountNum)
    		{
    			LOG(LM_STD, Fmtmsg("该批次没有扣款成功的明细，全部缺省前置与核心对平"), "INFO")
        	memset(cSql, 0x00, sizeof(cSql));
    			sprintf(cSql, "update tips_pljydj set czbd='7',wcbz='2',xyxx='日切后核心对账才取回结果，不发回执强制跳7' where zwrq='%s' and pljylsh=%s", cDzrq, cPljylsh);
    			LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO");
    			iSqlRet = DCIExecuteDirect(cSql);
    			if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "更新批量交易登记表完成标志失败");
						LOG(LM_STD,Fmtmsg("[update...sql][%s]", cSql),"ERROR");
						return -1;
					}	
					LOG(LM_STD, Fmtmsg("更新批量交易登记表,完成标志成功"), "INFO")
    		}
   		 else
    		{
    			LOG(LM_STD, Fmtmsg("该批次存在扣款成功的明细，全部当作核心多处理"), "INFO")
    			iRet = djdzbpdjb(lXmlhandle, cDzrq, cPljylsh, iCountNum);
    			if (0 != iRet)
    				{
    					LOG(LM_STD, Fmtmsg("登记对账不平明细表失败"), "ERROR")
        			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        			fpub_SetMsg(lXmlhandle, 100001, "登记对账不平明细表失败");
        			return COMPRET_FAIL;
    				}
    		}
    	}
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
       
}


int djdzbpdjb(HXMLTREE lXmlhandle, char* cDzrq, char* cPljylsh, int iCountNum) 
{
    int iSqlRet = 0;
    int iFlag = 0;
	  char cSql[1024+1];   /* SQL语句 */
    char cTmp[128+1];
    char cErrmsg[256+1];	
    

    SDB_TIPS_SSPLKSFMX stPlksfmx;  //SD_TIPS_SSPLKSFMX
    SDB_TIPS_DZBPDJ stDzbpdj;    //SD_TIPS_DZBPDJ
    int rows = 1;
    for (rows=1; rows<=iCountNum; ++rows)
    {
    	memset(cSql, 0x00, sizeof(cSql));
    	memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    	memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
    	memset(cErrmsg, 0x00, sizeof(cErrmsg));
    	sprintf(cSql, "select * from (select ta.*,rownumber()over(order by ta.plmxxh asc) as rownum from tips_ssplksfmx as ta where ta.zwrq='%s' and ta.pljylsh='%s' and ta.czbd='7') as a where a.rownum=%d"
                , cDzrq, cPljylsh, rows);
    	LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    	iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
    	if (0 > iSqlRet)
    	{
        LOG(LM_STD, Fmtmsg("查询批量扣税费明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "查询批量扣税费明细表失败");
        return -1;
    	}
    	else if(0 == iSqlRet)
    	{
        LOG(LM_STD, Fmtmsg("批量扣税费明细不存在"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "批量扣税费明细不存在，请确认");
        return -1;
    	}
    	else
    	{
    		/*这里把查询的结果赋给对账不平的结构体，然后再插入对账不平明细表*/
    		trim(stPlksfmx.payeebankno);
    		trim(stPlksfmx.payacct);
    		pstrcopy(stDzbpdj.zwrq, stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));
    		stDzbpdj.zhqzlsh = stPlksfmx.plmxxh;  /*批量明细序号*/
    		pstrcopy(stDzbpdj.workdate, stPlksfmx.workdate, sizeof(stDzbpdj.workdate));
    		pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));
				pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));
				pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));
				stDzbpdj.dzlx[0] = '1';
				pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));
				pstrcopy(stDzbpdj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stDzbpdj.taxorgcode));
				pstrcopy(stDzbpdj.entrustdate, stPlksfmx.entrustdate, sizeof(stDzbpdj.entrustdate));
				pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));
				pstrcopy(stDzbpdj.chkdate, stPlksfmx.chkdate, sizeof(stDzbpdj.chkdate));  /*暂时这样取*/
				pstrcopy(stDzbpdj.chkacctord, stPlksfmx.chkacctord, sizeof(stDzbpdj.chkacctord));/*暂时这样取*/
				pstrcopy(stDzbpdj.payeebankno, stPlksfmx.payeebankno, sizeof(stDzbpdj.payeebankno));
				pstrcopy(stDzbpdj.paybkcode, stPlksfmx.paybkcode, sizeof(stDzbpdj.paybkcode));
				/*stDzbpdj.czyh 操作员号 为空
				  stDzbpdj.jyqd 交易渠道 为空*/
				pstrcopy(stDzbpdj.jyrq, stPlksfmx.zwrq, sizeof(stDzbpdj.jyrq));
				pstrcopy(stDzbpdj.jysj, stPlksfmx.zjsj, sizeof(stDzbpdj.jysj));
				pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));
				pstrcopy(stDzbpdj.khmc, stPlksfmx.handorgname, sizeof(stDzbpdj.khmc));
				pstrcopy(stDzbpdj.jyzh, stPlksfmx.payacct, sizeof(stDzbpdj.jyzh));
				/*stDzbpdj.zhzl 帐户种类 为空 */
				pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				stDzbpdj.jyje = stPlksfmx.jyje;
				pstrcopy(stDzbpdj.reason_info, "前置<->主机;批量主机多", sizeof(stDzbpdj.reason_info));
				pstrcopy(stDzbpdj.dzjg, "39", sizeof(stDzbpdj.dzjg));
				stDzbpdj.clzt[0]='0';
				stDzbpdj.jdbz[0]='1';
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				/*stDzbpdj.clzjlsh 处理主机流水号 为空 */
				pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
				pstrcopy(stDzbpdj.kzbz, stPlksfmx.kzbz, sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.byzd, stPlksfmx.packno, sizeof(stDzbpdj.byzd));
				
				iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, cErrmsg);
				if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "插入对帐不平明细登记表失败");
						LOG(LM_STD,Fmtmsg("插入对帐登记表失败"),"ERROR");
						iFlag = -1;
						break;
					}	
    	}
    }
    LOG(LM_STD, Fmtmsg("登记对账不平明细表成功"), "INFO")
    if (0 == iFlag)
    {
    	/* 这里更新批量交易登记表,完成标志为成功及批量扣税费明细表的扩展标志 */
    	memset(cSql, 0x00, sizeof(cSql));
    	sprintf(cSql, "update tips_pljydj set czbd='7',wcbz='2',xyxx='日切后核心对账才取回结果，不发回执强制跳7' where zwrq='%s' and pljylsh=%s", cDzrq, cPljylsh);
    	LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO");
    	iSqlRet = DCIExecuteDirect(cSql);
    	if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "更新批量交易登记表完成标志及操作步点失败");
						LOG(LM_STD,Fmtmsg("[update...sql][%s]", cSql),"ERROR");
						return -1;
					}	
			LOG(LM_STD, Fmtmsg("更新批量交易登记表,完成标志为成功，操作步点为7"), "INFO")
			memset(cSql, 0x00, sizeof(cSql));		
			sprintf(cSql, "update tips_ssplksfmx set kzbz='39'||substr(kzbz,3,6) where zwrq='%s' and pljylsh='%s' and czbd='7'", cDzrq, cPljylsh);
    	LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO");
    	iSqlRet = DCIExecuteDirect(cSql);
    	if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "更新批量扣税费明细表标志失败");
						LOG(LM_STD,Fmtmsg("[update...sql][%s]", cSql),"ERROR");
						return -1;
					}
			LOG(LM_STD, Fmtmsg("批量扣税费明细表的扩展标志成功"), "INFO")			
    }
    return 0;
}