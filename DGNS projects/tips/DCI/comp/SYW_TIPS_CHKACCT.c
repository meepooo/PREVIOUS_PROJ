/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V3.0.00
  操作系统:AIX5.3
  文件名称:SYW_TIPS_CHKACCT.ec
  文件描述:TIPS对帐交易组件集
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

#include  "../eh/tips_ssdzmx.h"  
#include  "../eh/tips_ssdzplt.h"
#include  "../eh/tips_drls.h"   
#include  "../eh/tips_ssplksfmx.h"
#include  "../eh/tips_dzbpdj.h"
/*#include  "../eh/tips_xibhxmx.h"  */
#include  "../eh/tips_dzjgxx.h" 
#include  "../eh/tips_gkzfh2qsh.h"
#include  "../eh/tips_hxdzmx.h"

/*
#define SQLNOTFOUND_TIPS ( \
(sqlca.sqlcode == 100) \
|| (sqlca.sqlcode == 1403) \
|| (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
) 

/* add by tuql 20091108 用于更新对账不平明细*/
typedef struct TDB_DZBPMX
{
	char yzwrq[8+1];/*原帐务日期*/
	int  yqzlsh;/* 原前置流水号 */
	char clzt[1+1];/* 处理状态 */
	char clxx[50+1];/* 处理信息 */
	char yclzt[1+1];/* 原处理状态 */
	char dzlx[1+1];/* 对账类型 */
}SDB_DZBPMX; 

/* add by tuql 20091108 用于更新对账不平明细*/
typedef struct TDB_MZ
{
	HXMLTREE lXmlhandle; /* XML树句柄 */
	char yzwrq[8+1];/*原帐务日期*/
	int  yqzlsh;/* 原前置流水号 */
	char ymsgno[4+1];/* 原交易代码 */
	double mzje;/* 抹账金额 */
	char pljylsh[8+1];/* 批量交易流水号 */
	char plpch[8+1];/* 批量批次号 */
	char dzbz[1+1];/* 对账标志 */
}SDB_MZ;

/* 记与TIPS对税收账时，TIPS无前置有的记录 */
int LOG_SSTIPS(char *sTransCode,char *buf,char *sFkhh,char *sDzrq)
{
	char sfile[256];
	FILE *fp;

	memset(sfile, 0x00, sizeof(sfile));
	snprintf(sfile,sizeof(sfile),"%s/file/tips/chkacct/chkSSTIPS_%s_%s_%s.txt",getenv("HOME"),sTransCode,sDzrq,sFkhh);
	if ((fp=fopen(sfile,"a+")) ==  NULL )	
	{      
		return -1;
	}
	trim(buf);
	fprintf(fp," %s\n",buf);
	fclose(fp); 
	return 0;	
}

/*****************************************
  记录对帐日志的函数2

 *****************************************/
int LOG_TiaoZ(char *sTransCode,char *buf)
{
	char sfile[200];
	FILE *fp;

	memset(sfile, 0x00, sizeof(sfile));
	sprintf(sfile,"%s/file/tips/chkacct/TiaoZ_%s_%s.log",getenv("HOME"),sTransCode,GetSysDate());
	if ((fp=fopen(sfile,"a+")) ==  NULL )	
		return -1;
	fprintf(fp," %s\n",buf);
	fclose(fp); 
	return 0;	
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_RegDZPKG
  组件名称: 登记税费票对账包
  组件功能: 
  登记税费票对账包
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

  主要操作库表:
  表名              操作
  税收对账批量头	tips_ssdzplt
  税收对账明细信息 tips_ssdzmxxx

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年02月25日
  修改日期: 20141105 DCI改造工作
  修改日期: 20141220DCI改造，已测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_RegDZPKG(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;  //noted by chenxm 20141104
	SDB_TIPS_SSDZMX  desc_ssdzmx[100];
	SDB_TIPS_SSDZPLT stDzplt;
	SDB_TIPS_SSDZMX stDzmx;
	int iCount ;
	//EXEC SQL END   DECLARE SECTION; //noted by chenxm 20141104
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char sroot1[256];
	char sXml[256];
	int i;
	int iret = 0;
	int iflag = 1;
	int iRet = -1;
	int iSqlRet = -1;

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("登记税费票对账包开始处理... "), fpub_GetCompname(lXmlhandle))

		/*************************获取对帐批量头数据***************************/    
		memset(&stDzplt, 0x00, sizeof(stDzplt)); 
	/*账务日期*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/zwrq",sBuf)
		pstrcopy(stDzplt.zwrq,sBuf,sizeof(stDzplt.zwrq));
	/*综合前置流水号*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/pub/zhqzlsh",sBuf)
		stDzplt.zhqzlsh=atoi(sBuf);
	/*工作日期*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/WorkDate",sBuf)
		pstrcopy(stDzplt.workdate,sBuf,sizeof(stDzplt.workdate));
	/*付款行行号*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/PayBkCode",sBuf)
		pstrcopy(stDzplt.paybkcode,sBuf,sizeof(stDzplt.paybkcode));
	/*收款行行号*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/PayeeBankNo",sBuf)
		pstrcopy(stDzplt.payeebankno,sBuf,sizeof(stDzplt.payeebankno));
	/*对账日期*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChkDate",sBuf)
		pstrcopy(stDzplt.chkdate,sBuf,sizeof(stDzplt.chkdate));
	/*对账批次*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChkAcctOrd",sBuf)
		pstrcopy(stDzplt.chkacctord,sBuf,sizeof(stDzplt.chkacctord));
	/*上一对账批次*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/PriorChkAcctOrd",sBuf)
		pstrcopy(stDzplt.priorchkacctord,sBuf,sizeof(stDzplt.priorchkacctord));
	/*对账类型*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChkAcctType",sBuf)
		pstrcopy(stDzplt.chkaccttype,sBuf,sizeof(stDzplt.chkaccttype));
	/*总笔数*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/AllNum",sBuf)
		stDzplt.allnum=atoi(sBuf);
	/*总金额*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/AllAmt",sBuf)
		stDzplt.allamt=atof(sBuf);
	/*子包总数*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChildPackNum",sBuf)
		stDzplt.childpacknum=atoi(sBuf);
	/*本包序号*/
	memset(sBuf, 0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/tips/CurPackNo",sBuf)
		stDzplt.curpackno=atoi(sBuf);
	/*本包笔数*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("CurPackNum",sBuf)
		stDzplt.curpacknum=atoi(sBuf);
	/*本包金额*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("CurPackAmt",sBuf)
		stDzplt.curpackamt=atof(sBuf);    

	LOG(LM_DEBUG,Fmtmsg("对账日期[%s],对账批次[%s],本包序号[%d]",
				stDzplt.chkdate, stDzplt.chkacctord, stDzplt.curpackno),"DEBUG");

	/************************检查数据库表中是否存在该对帐包记录********************/
	iCount = 0 ;

	//add by chenxm 20141104 DCI改造工作
	memset(sSql1, 0x00, sizeof(sSql1));
	memset(sTemp, 0x00, sizeof(sTemp));
	
	sprintf(sSql1, "SELECT count(*) FROM tips_ssdzplt WHERE chkdate='%s' and chkacctord ='%s'\
		and curpackno ='%d' and paybkcode ='%s' and payeebankno='%s'",stDzplt.chkdate,\
		stDzplt.chkacctord, stDzplt.curpackno, stDzplt.paybkcode, stDzplt.payeebankno);
	
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
	iSqlRet = DBSelectToVarChar(sErrmsg, sTemp, sSql1);
	if( iSqlRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24356, Fmtmsg("查询税收对帐批量头表失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询税收对帐批量头表失败"),fpub_GetCompname(lXmlhandle)); 
	}
	iCount = atol(sTemp);
	// add end 

	// noted by chenxm  20141104 DCI改造工作
	//EXEC SQL SELECT COUNT(*) INTO :iCount 
	//    FROM tips_ssdzplt 
	//    WHERE chkdate=:stDzplt.chkdate           /*对账日期*/
	//      AND chkacctord=:stDzplt.chkacctord     /*对账批次*/
	//      AND curpackno=:stDzplt.curpackno       /*本包序号*/
	//      AND paybkcode=:stDzplt.paybkcode       /*付款行行号*/
	//      AND payeebankno=:stDzplt.payeebankno ; /*收款行行号*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  /if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24356, Fmtmsg("查询税收对帐批量头表失败"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询税收对帐批量头表失败"), 
	  fpub_GetCompname(lXmlhandle));        
	  }
	//noded end 

	 */
	if ( iCount != 0 )   /*有记录已经存在不必再插数据库表*/
	{
		iflag = 1;  /*1--有记录存在跳过插记录动作程序结束*/
		LOG(LM_STD,Fmtmsg("税费票明细对帐数据包已存在,跳过"), 
				fpub_GetCompname(lXmlhandle));
		/* mod by tuql 20100129 可能先到重对报文,后commit delete的情况
		   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		   fpub_SetMsg(lXmlhandle, 24357, Fmtmsg("税费票明细对帐数据包已存在,跳过"));
		   LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询税收对帐批量头表失败"), 
		   fpub_GetCompname(lXmlhandle));
		 */
	}else
		iflag = 0 ;

	if ( iflag == 0 )  /*0--表示数据库表中未有该包记录允许插入*/
	{

		/*EXEC SQL BEGIN WORK;  事务开始*/
		/*赋值根节点*/
		memset(sroot1, 0x00, sizeof(sroot1));
		strcpy(sroot1,"/tips/MSG/BankCompare3111");

		// add by chenxm 20141104 DCI改造工作 
		iSqlRet = DCIBegin();
		if( iSqlRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
	  
	  //add by lrj 20180912 重发对账申请原表已有数据导致入表失败
	  memset(sSql1, 0x00, sizeof(sSql1));
	
	  sprintf(sSql1, "DELETE FROM tips_ssdzmx WHERE chkdate='%s' and chkacctord ='%s'\
		and curpackno ='%d' and paybkcode ='%s' and payeebankno='%s'",stDzplt.chkdate,\
		stDzplt.chkacctord, stDzplt.curpackno, stDzplt.paybkcode, stDzplt.payeebankno);
	  LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
	  iSqlRet = DCIExecuteDirect(sSql1);
	  if( iSqlRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
    /*end add by lrj 20180912 重发对账申请原表已有数据导致入表失败*/
	  
		/*登记对帐明细表数据*/
		for (i=1;i<=stDzplt.curpacknum;i++)
		{
			memset(&stDzmx, 0x00, sizeof(stDzmx));
			/*************************获取对帐明细数据***************************/
			/*账务日期*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/zwrq",sBuf)
				pstrcopy(stDzmx.zwrq,sBuf,sizeof(stDzmx.zwrq));
			/*综合前置流水号*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/zhqzlsh",sBuf)
				stDzmx.zhqzlsh=atoi(sBuf);
			/*工作日期*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/WorkDate",sBuf)
				pstrcopy(stDzmx.workdate,sBuf,sizeof(stDzmx.workdate));
			/*对账日期*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/ChkDate",sBuf)
				pstrcopy(stDzmx.chkdate,sBuf,sizeof(stDzmx.chkdate));
			/*对账批次*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/ChkAcctOrd",sBuf)
				pstrcopy(stDzmx.chkacctord,sBuf,sizeof(stDzmx.chkacctord));
			/*本包序号*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/CurPackNo",sBuf) //modified by lrj 20180912
				stDzmx.curpackno=atoi(sBuf);            
			/*付款开户行行号*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/PayOpBkCode",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.payopbkcode,sBuf,sizeof(stDzmx.payopbkcode));    
			/*付款行行号*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/PayBkCode",sBuf)
				pstrcopy(stDzmx.paybkcode,sBuf,sizeof(stDzmx.paybkcode));
			/*收款行行号*/
			COMP_SOFTGETXML("/tips/PayeeBankNo",sBuf)
				pstrcopy(stDzmx.payeebankno,sBuf,sizeof(stDzmx.payeebankno));
			/*付款账户*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/PayAcct",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.payacct,sBuf,sizeof(stDzmx.payacct));
			/*单位名称*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/HandOrgName",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.handorgname,sBuf,sizeof(stDzmx.handorgname));          
			/*原征收机关代码*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriTaxOrgCode",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.oritaxorgcode,sBuf,sizeof(stDzmx.oritaxorgcode));            
			if (stDzmx.oritaxorgcode[0] == '\0')
			{
				/* EXEC SQL ROLLBACK WORK;*/
				fpub_SetMsg(lXmlhandle, 24358, Fmtmsg("共[%d]条数据,第[%d]条对账数据不存在", stDzplt.curpacknum, i));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				LOG(LM_STD, Fmtmsg("原征收机关[%s],原委托日期[%s],原包流水号[%s],原交易流水号[%s]", 
							stDzmx.oritaxorgcode, stDzmx.orientrustdate, stDzmx.oripackno, stDzmx.oritrano), 
						fpub_GetCompname(lXmlhandle))
					LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("共[%d]条数据,第[%d]条对账数据不存在", stDzplt.curpacknum, i), 
							fpub_GetCompname(lXmlhandle))                
			}
			/*原委托日期*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriEntrustDate",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.orientrustdate,sBuf,sizeof(stDzmx.orientrustdate));
			/*原包流水号*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriPackNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.oripackno,sBuf,sizeof(stDzmx.oripackno));
			/*原交易流水号*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriTraNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.oritrano,sBuf,sizeof(stDzmx.oritrano));
			/*交易金额*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/TraAmt",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				stDzmx.traamt=atof(sBuf);
			/*税票号码*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/TaxVouNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.taxvouno,sBuf,sizeof(stDzmx.taxvouno));
			/*纳税人名称*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/TaxPayName",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.taxpayname,sBuf,sizeof(stDzmx.taxpayname));
			/*协议书号*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/ProtocolNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.protocolno,sBuf,sizeof(stDzmx.protocolno));          

			/*登记对账明细信息表*/
			// add by chenxm 20141104 DCI改造工作 
			//snprintf(sTable, "%s", "tips_ssdzmx");
			
			iSqlRet = DBInsert("tips_ssdzmx", SD_TIPS_SSDZMX, NUMELE(SD_TIPS_SSDZMX), &stDzmx, sErrmsg);
			if( iSqlRet < 0 )
			{
				/*DCIRollback(); */
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				fpub_SetMsg(lXmlhandle, 24358, "登记对帐明细信息失败");
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				LOG(LM_STD, Fmtmsg("原征收机关[%s],原委托日期[%s],原包流水号[%s],原交易流水号[%s]", 
							stDzmx.oritaxorgcode, stDzmx.orientrustdate, stDzmx.oripackno, stDzmx.oritrano), 
						fpub_GetCompname(lXmlhandle))
				
				LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记对帐明细信息失败"), fpub_GetCompname(lXmlhandle))	        
			}

			/*
			   EXEC SQL INSERT INTO tips_ssdzmx  VALUES(:stDzmx);
			   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
			   if ( SQLERR )
			   {*/
			/*  EXEC SQL ROLLBACK WORK;*/
			/*fpub_SetMsg(lXmlhandle, 24358, "登记对帐明细信息失败");
			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			  LOG(LM_STD, Fmtmsg("原征收机关[%s],原委托日期[%s],原包流水号[%s],原交易流水号[%s]", 
			  stDzmx.oritaxorgcode, stDzmx.orientrustdate, stDzmx.oripackno, stDzmx.oritrano), 
			  fpub_GetCompname(lXmlhandle))
			  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记对帐明细信息失败"), 
			  fpub_GetCompname(lXmlhandle))
			  }*/
		}

		/*登记对账批量头表*/

		iSqlRet = DBInsert("tips_ssdzplt", SD_TIPS_SSDZPLT, NUMELE(SD_TIPS_SSDZPLT), &stDzplt, sErrmsg);
		if( iSqlRet < 0 )
		{
			/*DCIRollback(); */
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			fpub_SetMsg(lXmlhandle, 24359, "登记对帐批量头信息失败");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			
			LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记对帐批量头信息失败"),fpub_GetCompname(lXmlhandle))
		}

		/*
		   EXEC SQL INSERT INTO tips_ssdzplt VALUES(:stDzplt);
		   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
		   if ( SQLERR )
		   {*/
		/*  EXEC SQL ROLLBACK WORK; */  /*
										   fpub_SetMsg(lXmlhandle, 24359, "登记对帐批量头信息失败");
										   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
										   LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记对帐批量头信息失败"), 
										   fpub_GetCompname(lXmlhandle))
										   }

		/*事务提交结束
		EXEC SQL COMMIT WORK;
		/*SQLERRLOG(LM_STD,Fmtmsg("数据库提交失败sqlcode=[%d]",sqlca.sqlcode),"ERROR");
		if ( SQLERR )  
		{
		EXEC SQL ROLLBACK WORK;
		fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("数据库操作失败"));
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return COMPRET_FAIL;    	
		} */       
		iSqlRet=DCICommit();
		/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
		if ( iSqlRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */
	}
	fpub_SetMsg(lXmlhandle, 0, "登记税费票对账包成功");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	LOG(LM_STD,Fmtmsg("登记税费票对账包成功"), fpub_GetCompname(lXmlhandle));
	return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_ChkSSDZBZT
  组件名称: 判断税收对帐包状态
  组件功能: 
  判断税收对帐包状态
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

  主要操作库表:
  表名              操作
  税收对账批量头	tips_ssdzplt
  税收对账明细信息 tips_ssdzmxxx

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年02月25日
  修改日期: 20141105 DCI改造工作
  修改日期: 20141220DCI改造，已测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_ChkSSDZBZT(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;  //noted by chenxm 20141104
	int iCountPkg;/*包数量*/
	int iCountMxbs;/*包明细中收到的总笔数*/
	double dTraamt;/*明细交易总金额*/
	char cCountMxbs[16+1];
	char cTraamt[32+1];
	char sChkDate[8+1];/* 对账日期 */
	char sChkAcctOrd[4+1];/* 对账批次号 */
	char sPayBkCode[12+1];/* 清算行行号 */
	char sPayeeBankNo[12+1];/* 收款行行号 */
	//EXEC SQL END   DECLARE SECTION;  //noted by chenxm 20141104

	char sSql1[1024];
	char sErrmsg[256];
	char sBuf[256];
	char sTemp[128];
	
	int iRet = -1;  // added by chenxm 20141104 DCI改造工作
	int i;
	int iret=0;
	int iTmp;
	int iFlag=0;
	int iZbs;/* 总笔数 */
	int iChildPackNum;/*子包数*/
	double dZje;/*总金额*/
	char sZje[32];/* add by tuql 20090910 */
	char sTraamt[32];/* add by tuql 20090910 */

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("判断税收对帐包状态开始处理... "), fpub_GetCompname(lXmlhandle))

		COMP_PARACOUNTCHK(7)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"对账日期");
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"对账批次号");
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(3,sBuf,"子包数");
	iChildPackNum = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(4,sBuf,"本次对账总笔数");
	iZbs = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(5,sBuf,"本次对账总金额");
	dZje = atof(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(6,sBuf,"付款行行号");
	pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayeeBankNo, 0x00,sizeof(sPayeeBankNo));
	COMP_GETPARSEPARAS(7,sBuf,"收款行行号");
	pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo));

	LOG(LM_STD,Fmtmsg("对账日期[%s],对账批次号[%s],子包数[%d]",sChkDate, sChkAcctOrd, iChildPackNum),
			fpub_GetCompname(lXmlhandle))
		LOG(LM_STD,Fmtmsg("付款行行号[%s],收款行行号[%s]", sPayBkCode, sPayeeBankNo),
				fpub_GetCompname(lXmlhandle))

		/*获得对账日期、对账批次号内所有已经收到包的数量*/
		iCountPkg = 0 ;
	//added by chenxm 20141104 DCI改造工作 
	memset(sSql1, 0x00, sizeof(sSql1));
	memset(sTemp, 0x00, sizeof(sTemp));
	sprintf(sSql1, "select count(*) from tips_ssdzplt where chkdate = '%s' and chkacctord ='%s'\
			and paybkcode ='%s' and payeebankno='%s'", sChkDate,sChkAcctOrd,sPayBkCode,sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iRet = DBSelectToVarChar(sErrmsg, sTemp, sSql1);
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
		
		fpub_SetMsg(lXmlhandle, 24356, "查询税收对帐批量头表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("查询本对账日本批次已经收到包的数量失败"), fpub_GetCompname(lXmlhandle))
	}		
	iCountPkg = atol(sTemp);
	/*
	   EXEC SQL SELECT COUNT(*) INTO :iCountPkg
	   FROM tips_ssdzplt 
	   WHERE chkdate = :sChkDate  *//*对账日期*/
	// AND chkacctord  = :sChkAcctOrd /*对账批次*/
	// AND paybkcode = :sPayBkCode   /*付款行行号*/
	// AND payeebankno = :sPayeeBankNo ;  /*收款行行号*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24356, "查询税收对帐批量头表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("查询本对账日本批次已经收到包的数量失败"), 
	  fpub_GetCompname(lXmlhandle))
	  }	
	 */
	/*判断收到的包数量是否等于子包数量，如果不等，则返回组件状态1 表示该批次包还未收全*/
	if (iChildPackNum != iCountPkg)
	{
		LOG(LM_STD,Fmtmsg("  -->本批次对账包未全收妥，不进行对账处理"),"ERROR");
		fpub_SetCompStatus(lXmlhandle,1);
		return 0 ;
	}
	/*获得对账日期、对账批次号内所有已经收到的明细数据的数量和交易金额总计*/
	/* added by chenxm 20141104 DCI改造工作*/
	memset(sTemp, 0x00, sizeof(sTemp));
	sprintf(sSql1, "select count(*),SUM(traamt) from tips_ssdzmx where chkdate = '%s' and chkacctord ='%s' "
			"and paybkcode ='%s' and payeebankno='%s'", sChkDate,sChkAcctOrd,sPayBkCode,sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
	iRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cCountMxbs, &cTraamt);	
	iCountMxbs=atoi(cCountMxbs);
	dTraamt=atof(cTraamt);
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
		
		fpub_SetMsg(lXmlhandle, 24360, "查询税收对帐明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("查询本对账日本批次所有已经收到明细的数量、交易金额合计失败"), fpub_GetCompname(lXmlhandle))
	}

	/* noded by chenxm 20141104 DCI改造工作
	   EXEC SQL SELECT COUNT(*),NVL(SUM(traamt),0.00) 
INTO :iCountMxbs,:dTraamt
FROM tips_ssdzmx
WHERE chkdate = :sChkDate  /*对账日期*/
	// AND chkacctord  = :sChkAcctOrd /*对账批次*/
	// AND paybkcode = :sPayBkCode   /*清算行行号*/
	// AND payeebankno = :sPayeeBankNo ;  /*收款行行号*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24360, "查询税收对帐明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("查询本对账日本批次所有已经收到明细的数量、交易金额合计失败"), 
	  fpub_GetCompname(lXmlhandle))
	  }	  

	 */
	/*判断收到的明细数量是否等于包明细数量，如果不等，则返回失败，该包处理失败！*/
	if (iZbs != iCountMxbs)
	{
		fpub_SetMsg(lXmlhandle, 24361, "本批次包明细数量和包头定义的明细数量不符");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		/* add by tuql 20090910 将包明细累计数量打印到日志中*/
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("本批次包明细数量和包头定义的明细数量不符zbs[%d],count[%d]", iZbs ,iCountMxbs), 
				fpub_GetCompname(lXmlhandle))
	}  
	/*判断收到的明细交易合计是否等于包明细交易合计，如果不等，则返回失败，该包处理失败！*/
	memset(sZje, 0x00, sizeof(sZje));
	memset(sTraamt, 0x00, sizeof(sTraamt));
	snprintf(sZje, sizeof(sZje), "%15.2f", dZje);
	snprintf(sTraamt, sizeof(sTraamt), "%15.2f", dTraamt);
	trim(sZje);
	trim(sTraamt);
	/* if (dZje != dTraamt) */    
	if (strcmp(sZje, sTraamt)!=0)
	{
		fpub_SetMsg(lXmlhandle, 24362, "本批次包明细金额合计和包头定义的总金额不符");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		/* add by tuql 20090910 将包明细累计金额打印到日志中*/
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("本批次包明细金额合计和包头定义的总金额不符zje[%s]sumje[%s]", sZje, sTraamt), 
				fpub_GetCompname(lXmlhandle))
	}
	fpub_SetMsg(lXmlhandle, 0, "判断税收对帐包状态结束");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	LOG(LM_STD,Fmtmsg("判断税收对帐包状态结束"), fpub_GetCompname(lXmlhandle));
	return COMPRET_SUCC;

}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_ChkSSTIPS
  组件名称: 与TIPS对税收实时、批量账
  组件功能: 
  与TIPS对税收实时、批量账
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败
  1                  银行多
  2                  TIPS多
  3                  TIPS多、银行多　

  主要操作库表:
  表名              操作
  税收对账批量头	tips_ssdzplt
  税收对账明细信息 tips_ssdzmxxx

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年02月25日
  修改日期: 2010年01月04日 1.0.5.0
  修改原因：1.0.5.0 增加自动划款后,需将对账结果状态赋给/tips/chktipszt结点
  修改日期: 20141220DCI改造，已测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_ChkSSTIPS(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	int iCount;
	char sChkDate[8+1];/* 对账日期 */
	char sChkAcctType[1+1];/* 对账类型 */
	char sChkAcctOrd[4+1];/* 对账批次 */
	char sPayBkCode[12+1];/* 付款行行号 */
	char sPayeeBankNo[12+1];/* 收款行行号 */
	char sEntrustDate[8+1];/* 委托日期 */
	char sTaxOrgCode[12+1];/* 征收机关代码 */
	char sPackNo[8+1];/* 包流水号 */
	SDB_TIPS_SSDZMX stDzmx;/* 对账明细信息 */
	SDB_TIPS_DRLS stDrls;
	SDB_TIPS_SSPLKSFMX stPlksfmx;
	SDB_TIPS_DZBPDJ stDzbpdj;
	SDB_TIPS_DZJGXX stDzjgxx;  /*  add 20140901 */
	//EXEC SQL END   DECLARE SECTION;

	char sSql1[1024];  /* add by chenxm 20141105*/
	char sErrmsg[256];
	char sTemp[128];
	
	int iSqlRet=-1;

	char sBuf[256];
	char sRjbpFile[256];
	int i;
	int iRet=0;
	int iflag;
	int iTpnum=0;/* Tips总笔数 */
	int iTpdnum=0;/* TIPS方多计数器 */
	int iBkdnum=0; /* 银行多的计数器 */

	/* add 20140901 */
	double dTpamt = 0.00; /* TIPS总金额 */
	int iQznum = 0; /* TIPS前置总笔数 */
	double dQzamt = 0.00; /* TIPS前置总金额 */

	double dTpdamt = 0.00; /* TIPS前置多总金额 */
	double dBkdamt = 0.00; /* 银行多总金额 */    
	/* end add 20140901 */

	FILE *fp;
	CURSOR cur; /* add by chenxm DCI改造工作 20141105 */
	CURSOR cur1;
	CURSOR cur2;
	CURSOR cur3;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(5)
		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"对账日期"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	trim(sChkDate);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"对账批次");
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd)); 
	trim(sChkAcctOrd);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(3,sBuf,"付款行行号"); 
	pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
	trim(sPayBkCode);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
	COMP_GETPARSEPARAS(4,sBuf,"收款行行号");
	pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo)); 
	trim(sPayeeBankNo);    

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctType, 0x00, sizeof(sChkAcctType));
	COMP_GETPARSEPARAS(5,sBuf,"对账类型");
	pstrcopy(sChkAcctType, sBuf, sizeof(sChkAcctType)); 
	trim(sChkAcctType); 

	LOG(LM_STD,Fmtmsg("与TIPS对税收账开始处理,对账日期[%s],对账批次[%s],对账类型[%s]",
				sChkDate,sChkAcctOrd, sChkAcctType),fpub_GetCompname(lXmlhandle));     
	LOG(LM_STD,Fmtmsg("付款行行号[%s],收款行行号[%s]",
				sPayBkCode, sPayeeBankNo),fpub_GetCompname(lXmlhandle));

	/* 对表进行初始化,使其可以重复对账 */
	/* add by chenxm 20141105 DCI改造工作 */
	iSqlRet = DCIBegin();
	if( iSqlRet < 0 )
	{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
	}
		
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_drls SET qsbz='0', dzbz=substr(dzbz,1,1)||'0' WHERE chkdate ='%s' "
			"and chkacctord ='%s' and paybkcode = '%s' and payeebankno='%s' and msgno in ('3001', '1008')",
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
	iSqlRet = DCIExecuteDirect( sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("更新当日流水表失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle));
	}
	
	/* add end by chenxm */

	/*EXEC SQL UPDATE tips_drls SET qsbz='0', dzbz=substr(dzbz,1,1)||'0'
	  WHERE chkdate = :sChkDate 
	  AND chkacctord = :sChkAcctOrd
	  AND paybkcode = :sPayBkCode
	  AND payeebankno = :sPayeeBankNo
	  AND msgno in ('3001', '1008');*/
	/* mod by tuql 20091112  AND jyzt = '0' ; 
	   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	   if ( SQLERR )
	   {
	   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	   fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("更新当日流水表失败"));
	   LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新当日流水表失败"), 
	   fpub_GetCompname(lXmlhandle));
	   }
	 */

	/* add by chenxm 20141105 DCI改造工作 */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz=substr(kzbz,1,1)||'0'||substr(kzbz,3,6), qsbz='0' "
			"where chkdate ='%s' and chkacctord = '%s' and paybkcode='%s' and payeebankno = '%s'",
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect( sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("更新批量扣税费明细表失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle));
	}
	/* add end by chenxm */

	/*EXEC SQL UPDATE tips_ssplksfmx SET kzbz=substr(kzbz,1,1)||'0'||substr(kzbz,3,6), qsbz='0'
	  WHERE chkdate = :sChkDate 
	  AND chkacctord = :sChkAcctOrd
	  AND paybkcode = :sPayBkCode
	  AND payeebankno = :sPayeeBankNo;*/
	/* mod by tuql 20091112  AND czbd = '7'; */ 
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	  if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("更新批量扣税费明细表失败"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新批量扣税费明细表失败"), 
	  fpub_GetCompname(lXmlhandle));
	  } */       

	/* add by chenxm 20141105 DCI改造工作 */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_pljydj SET kzbz=substr(kzbz,1,1)||'00'||substr(kzbz,4,5) "
			"where chkdate ='%s' and chkacctord = '%s' and paybkcode='%s' and payeebankno = '%s' and czbd = '7'",
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect( sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("更新批量交易登记表表失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新批量交易登记表表失败"), fpub_GetCompname(lXmlhandle));
	}
	/* add end by chenxm */

	/*EXEC SQL UPDATE tips_pljydj SET kzbz=substr(kzbz,1,1)||'00'||substr(kzbz,4,5)
	  WHERE chkdate = :sChkDate 
	  AND chkacctord = :sChkAcctOrd
	  AND paybkcode = :sPayBkCode
	  AND payeebankno = :sPayeeBankNo
	  AND czbd = '7'; 
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	  if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("更新批量交易登记表表失败"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新批量交易登记表表失败"), 
	  fpub_GetCompname(lXmlhandle));
	  }*/

	/* add by chenxm 20141105 DCI改造工作 */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzbpdj where chkdate ='%s' and chkacctord = '%s' "
			"and paybkcode='%s' and payeebankno = '%s' AND dzlx in ('2', '3') AND clzt= '0'",
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect( sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("删除对账不平登记表记录失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除对账不平登记表记录失败"), fpub_GetCompname(lXmlhandle));
	}
	/* add end by chenxm */

	/*EXEC SQL delete FROM tips_dzbpdj
	  WHERE chkdate = :sChkDate
	  AND chkacctord = :sChkAcctOrd
	  AND paybkcode = :sPayBkCode
	  AND payeebankno = :sPayeeBankNo
	  AND dzlx in ('2', '3')
	  AND clzt= '0';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	  if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("删除对账不平登记表记录失败"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除对账不平登记表记录失败"), 
	  fpub_GetCompname(lXmlhandle));
	  }*/

	/* 循环读取tips_ssdzmxxx表记录,与tips_drls、tips_ssplksfmx表勾对 */
	/* add by chenxm 20141105 DCI改造工作 */	
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT * FROM  tips_ssdzmx where chkdate ='%s' and chkacctord ='%s'\
		and paybkcode ='%s' and payeebankno='%s' ORDER BY curpackno,oritrano",\
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRiSqlRetet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}
	//add end by chenxm 20141105

	/*EXEC SQL DECLARE cur_dzmxxx_tipsdz CURSOR for 
	  SELECT * FROM  tips_ssdzmx 
	  WHERE chkdate = :sChkDate 
	  AND chkacctord = :sChkAcctOrd
	  AND paybkcode = :sPayBkCode
	  AND payeebankno = :sPayeeBankNo
	  ORDER BY curpackno,oritrano;/* 包序号,原交易流水号 *//*
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));

	EXEC SQL OPEN cur_dzmxxx_tipsdz;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzmxxx_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	if ( SQLERR )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("打开游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开cur_dzmxxx_tipsdz游标失败"), 
				fpub_GetCompname(lXmlhandle));
	}        */

	/*开始循环勾对*/
	iflag=0;
	for (i=1,iTpnum=0;;i++)
	{
		memset(&stDzmx, 0x00, sizeof(stDzmx));
		iSqlRet = DBFetch(cur, SD_TIPS_SSDZMX, NUMELE(SD_TIPS_SSDZMX), &stDzmx, sErrmsg);
		/*EXEC SQL FETCH cur_dzmxxx_tipsdz INTO :stDzmx;  
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzmxxx_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{ 
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			iflag=-1;
			LOG(LM_STD,Fmtmsg("从cur_dzmxxx_tipsdz获取数据失败"),fpub_GetCompname(lXmlhandle));
			break;
		}
		/*if ( SQLNOTFOUND )*/
		if(iSqlRet == 0)
			break;

		iTpnum ++;
		/* add 20140901 */
		dTpamt = dTpamt + stDzmx.traamt;  /* tips明细对账总金额 */

		/* end add 20140901 */

		trim(stDzmx.orientrustdate);
		trim(stDzmx.oritaxorgcode);
		trim(stDzmx.payeebankno);
		trim(stDzmx.paybkcode);
		trim(stDzmx.oritrano);
		trim(stDzmx.payacct);
		/*更新当日流水表中委托日期及交易流水号相同的记录*/
		/* add by chenxm 20141105 DCI改造工作 */
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET dzbz=substr(dzbz,1,1)||'1', chkdate = '%s', chkacctord = '%s' "
				"where entrustdate='%s' and taxorgcode = '%s' and trano ='%s' and payeebankno='%s' and paybkcode ='%s' "
				"and jyje = %0.2f and msgno in ('3001', '1008') AND jyzt='0' and qsbz='0'", sChkDate, sChkAcctOrd, 
				stDzmx.orientrustdate, stDzmx.oritaxorgcode,stDzmx.oritrano,stDzmx.payeebankno,stDzmx.paybkcode,stDzmx.traamt);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		iSqlRet = DCIExecuteDirect( sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
			LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
						stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
			LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
						stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
			iflag = -2;
			break;
		}
		/* add end by chenxm */

		/* EXEC SQL UPDATE tips_drls 
		/*  SET dzbz=substr(dzbz,1,1)||'1',           设置对账标志第二位为已和TIPS对平
		chkdate = :sChkDate,         对账日期
		chkacctord = :sChkAcctOrd    对账批次
		WHERE  entrustdate=:stDzmx.orientrustdate   委托日期 
		AND  taxorgcode=:stDzmx.oritaxorgcode        征收机关代码 
		AND  trano=:stDzmx.oritrano                交易流水号 
		AND  msgno in ('3001', '1008')            报文编号 3001实扣 1008银缴 
		AND  payeebankno=:stDzmx.payeebankno      收款行行号 
		AND  paybkcode=:stDzmx.paybkcode          付款行行号 
		AND  jyzt='0'                             交易状态 0 成功 
		AND	dzbz[2]='0'                          对账标志 
		AND  qsbz='0'                             清算标志 
		AND  jyje=:stDzmx.traamt;                 交易金额  
		SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
		if ( SQLERR )
		{
		LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
		LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
		stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
		LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
		stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
		iflag = -2;
		break;
		}*/
		/* 要是没找到,则到批量扣税费明细表中查找更新 */
		/*if ( SQLNOTFOUND_TIPS )*/

		if(iSqlRet == 0 )
		{
			/* add by chenxm 20141105 DCI改造工作 */
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),\
			 chkdate = '%s', chkacctord = '%s' where entrustdate='%s' and taxorgcode = '%s' \
			 and packno ='%s' and trano ='%s' and payeebankno='%s' and paybkcode ='%s' \
			 and jyje = %0.2f and czbd='7' and qsbz='0'", \
			 sChkDate, sChkAcctOrd, stDzmx.orientrustdate, stDzmx.oritaxorgcode,stDzmx.oripackno,\
			 stDzmx.oritrano,stDzmx.payeebankno,stDzmx.paybkcode,stDzmx.traamt);  /*stDzmx.payacct不参与比对 by liurj 20180720*/
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet = DCIExecuteDirect( sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				LOG(LM_STD,Fmtmsg("更新批量扣税费表失败"),"ERROR");
				LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
							stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
				LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
							stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
				iflag = -3;
				break;
			}
			/* add end by chenxm */

			/* EXEC SQL UPDATE tips_ssplksfmx 
			//SET kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),                  设置对账标志第二位为已和TIPS对平
			//     chkdate = :sChkDate,         对账日期
			//     chkacctord = :sChkAcctOrd    对账批次
			// WHERE  entrustdate=:stDzmx.orientrustdate   委托日期 
			//   AND  taxorgcode=:stDzmx.oritaxorgcode      征收机关代码 
			//   AND  packno=:stDzmx.oripackno                包流水号 add by tuql 20090506
			//   AND  trano=:stDzmx.oritrano                交易流水号 
			//   AND  payeebankno=:stDzmx.payeebankno      收款行行号 
			//  AND  paybkcode=:stDzmx.paybkcode          付款行行号 
			//   AND  payacct=:stDzmx.payacct              付款账号 
			//   AND  czbd='7'                            操作步点 7 成功 
			AND	kzbz[2]='0'                          对账标志 0与TIPS未对账
			AND  qsbz='0'                            清算标志 
			AND  jyje=:stDzmx.traamt;                 交易金额 
			SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
			if ( SQLERR )
			{
			LOG(LM_STD,Fmtmsg("更新批量扣税费表失败"),"ERROR");
			LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
			stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
			LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
			stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
			iflag = -3;
			break;
			}*/

			/*批量扣税费明细表也没有找到的记录记到对帐不符表*/
			/*if( SQLNOTFOUND_TIPS )*/
			if(iSqlRet == 0)
			{
				iRet = 2;   /*组件返回状态2 对帐不符*/
				iTpdnum ++; /*TIPS方多计数器*/
				memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
				/*pstrcopy(stDzbpdj.zwrq, GetSysDate(), sizeof(stDzbpdj.zwrq)); 保存为对账日期*/
				pstrcopy(stDzbpdj.zwrq, sChkDate, sizeof(stDzbpdj.zwrq));
				stDzbpdj.zhqzlsh = 0;
				/******begin add by tuql 20091009 增加查询tips_drls及tips_ssplksfmx两表并赋值 ******/
				memset(&stDrls, 0x00, sizeof(stDrls));

				/* add by chenxm 20141105 DCI改造工作 */
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT * FROM tips_drls where entrustdate='%s' and taxorgcode ='%s' "
						"and trano='%s' and msgno in ('3001', '1008')",stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oritrano);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
				iSqlRet = prv_SelMulToStruct( &sSql1, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls);
				/*iSqlRet =DBSelectToMultiVar(sErrmsg, sSql1, &stDrls);*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
					
					LOG(LM_STD,Fmtmsg("查询当日流水表失败"),"ERROR");
					LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
								stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
					iflag = -32;
					break;
				}
				/* add end by chenxm */

				//EXEC SQL SELECT * INTO :stDrls 
				//   FROM tips_drls
				//    WHERE entrustdate=:stDzmx.orientrustdate  /* 委托日期 */
				//      AND  taxorgcode=:stDzmx.oritaxorgcode       /* 征收机关代码 */
				//       AND  trano=:stDzmx.oritrano               /* 交易流水号 */
				//       AND  msgno in ('3001', '1008');           /* 报文编号 3001实扣 1008银缴 */
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
				  if ( SQLERR )
				  {
				  LOG(LM_STD,Fmtmsg("查询当日流水表失败"),"ERROR");
				  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
				  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
				  iflag = -32;
				  break;
				  }*/

				//if( SQLNOTFOUND_TIPS )/* 在当日流水中找不到 */
				if(iSqlRet == 0)
				{
					memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));

					/* add by chenxm 20141105 DCI改造工作 */
					memset(sSql1, 0x00, sizeof(sSql1));
					sprintf(sSql1, "SELECT * FROM tips_ssplksfmx where entrustdate='%s' and taxorgcode ='%s' "
							"and packno='%s' and trano ='%s'",stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oripackno,stDzmx.oritrano);
					LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
					/*iSqlRet =DBSelectToMultiVar(sErrmsg, sSql1, &stPlksfmx);*/
					iSqlRet = prv_SelMulToStruct( &sSql1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("查询批量扣税费表失败"),"ERROR");
						LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
									stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
						iflag = -33;
						break;
					}
					/*add end by chenxm */

					//EXEC SQL SELECT * INTO :stPlksfmx
					//     FROM tips_ssplksfmx
					//     WHERE  entrustdate=:stDzmx.orientrustdate  /* 委托日期 */
					//       AND  taxorgcode=:stDzmx.oritaxorgcode       /* 征收机关代码 */
					//       AND  packno=:stDzmx.oripackno               /* 包流水号 */
					//       AND  trano=:stDzmx.oritrano;               /* 交易流水号 */                         
					/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
					  if ( SQLERR )
					  {
					  LOG(LM_STD,Fmtmsg("查询批量扣税费表失败"),"ERROR");
					  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
					  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
					  iflag = -33;
					  break;
					  }*/
					if( iSqlRet ==0 )/* 在批量明细表中找不到,什么都不做 */
					{
						;
					}else
					{
						/******begin add by tuql 20091112 增加更新tips_ssplksfmx两表 ******/
						/* add by chenxm 20141105 DCI改造工作 */
						memset(sSql1, 0x00, sizeof(sSql1));
						sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz=substr(kzbz,1,1)||'3'||substr(kzbz,3,6),chkdate='%s',chkacctord='%s' \
								where entrustdate='%s' and taxorgcode ='%s' and packno='%s' and trano ='%s'",\
								sChkDate,sChkAcctOrd,stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oripackno,stDzmx.oritrano);
						LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
						iSqlRet =DCIExecuteDirect(sSql1);
						if(iSqlRet < 0)
						{
							LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

							LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
							LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
										stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
							iflag = -35;
							break;
						}
						/*add end by chenxm */

						//EXEC SQL UPDATE tips_ssplksfmx 
						//     SET kzbz=substr(kzbz,1,1)||'3'||substr(kzbz,3,5),                 /*设置对账标志第二位为已和TIPS对平*/
						//         chkdate = :sChkDate,         /*对账日期*/
						//         chkacctord = :sChkAcctOrd    /*对账批次*/
						//     WHERE  entrustdate=:stDzmx.orientrustdate  /* 委托日期 */
						//       AND  taxorgcode=:stDzmx.oritaxorgcode       /* 征收机关代码 */
						//       AND  packno=:stDzmx.oripackno               /* 包流水号 add by tuql 20090506*/
						//       AND  trano=:stDzmx.oritrano;               /* 交易流水号 */
						/*if ( SQLERR )
						  {
						  LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
						  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
						  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
						  iflag = -35;
						  break;
						  }*/
						/******end add by tuql 20091112 增加更新tips_drls及tips_ssplksfmx两表 ******/        
						pstrcopy(stDzbpdj.zwrq, stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));/* 帐务日期 */
						stDzbpdj.zhqzlsh = stPlksfmx.plmxxh ;
						pstrcopy(stDzbpdj.workdate, stPlksfmx.workdate, sizeof(stDzbpdj.workdate));/* 工作日期 */
						pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));/* 地区代号 */
						pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));/* 机构代号 */
						pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));/* 交易柜员 */
						pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));/* 终端代号 */
						pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));/* 主机流水号 */
						pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));/* 贷方帐号 */
						pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));/* 交易名称 */
						pstrcopy(stDzbpdj.jyzh, stPlksfmx.payacct, sizeof(stDzbpdj.jyzh));/* 交易账号  add by liurj 20180719 */
					}                
				}else
				{
					/******begin add by tuql 20091112 增加更新tips_drls及tips_ssplksfmx两表 ******/
					/* add by chenxm 20141105 DCI改造工作 */
					memset(sSql1, 0x00, sizeof(sSql1));
					sprintf(sSql1, "UPDATE tips_drls SET dzbz=substr(dzbz,1,1)||'3',chkdate='%s',chkacctord='%s' "
							"where entrustdate='%s' and taxorgcode ='%s' and trano ='%s' and msgno in ('3001', '1008')",
							sChkDate,sChkAcctOrd,stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oripackno,stDzmx.oritrano);
					LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
					iSqlRet =DCIExecuteDirect(sSql1);
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
						LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
									stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
						iflag = -34;
						break;
					}
					/*add end by chenxm */

					//EXEC SQL UPDATE tips_drls 
					//     SET dzbz=substr(dzbz,1,1)||'3',           /*设置对账标志第二位为TIPS方多*/
					//         chkdate = :sChkDate,         /*对账日期*/
					//         chkacctord = :sChkAcctOrd    /*对账批次*/
					//     WHERE  entrustdate=:stDzmx.orientrustdate  /* 委托日期 */
					//       AND  taxorgcode=:stDzmx.oritaxorgcode       /* 征收机关代码 */
					//       AND  trano=:stDzmx.oritrano               /* 交易流水号 */
					//      AND  msgno in ('3001', '1008');           /* 报文编号 3001实扣 1008银缴 */
					/*if ( SQLERR )
					  {
					  LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
					  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
					  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
					  iflag = -34;
					  break;
					  }
					 */
					/******end add by tuql 20091112 增加更新tips_drls及tips_ssplksfmx两表 ******/
					pstrcopy(stDzbpdj.zwrq, stDrls.zwrq, sizeof(stDzbpdj.zwrq));/* 帐务日期 */
					stDzbpdj.zhqzlsh = stDrls.zhqzlsh ;
					pstrcopy(stDzbpdj.workdate, stDrls.workdate, sizeof(stDzbpdj.workdate));/* 工作日期 */
					pstrcopy(stDzbpdj.dqdh, stDrls.dqdh, sizeof(stDzbpdj.dqdh));/* 地区代号 */
					pstrcopy(stDzbpdj.jgdh, stDrls.jgdh, sizeof(stDzbpdj.jgdh));/* 机构代号 */
					pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));/* 交易柜员 */
					pstrcopy(stDzbpdj.zddh, stDrls.zddh, sizeof(stDzbpdj.zddh));/* 终端代号 */
					pstrcopy(stDzbpdj.zjlsh, stDrls.zjlsh, sizeof(stDzbpdj.zjlsh));/* 主机流水号 */
					pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));/* 贷方帐号 */                    
					pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDzbpdj.jymc));/* 交易名称,交易代码 */
					pstrcopy(stDzbpdj.jyzh, stDrls.payacct, sizeof(stDzbpdj.jyzh));/* 交易账号  add by liurj 20180719 */
				}        
				/******end add by tuql 20091009 增加查询tips_drls及tips_ssplksfmx两表并赋值 ******/
				if(sChkAcctType[0]== '0')
					stDzbpdj.dzlx[0]='2';
				else
					stDzbpdj.dzlx[0]='3';
				pstrcopy(stDzbpdj.taxorgcode, stDzmx.oritaxorgcode, sizeof(stDzbpdj.taxorgcode));
				pstrcopy(stDzbpdj.entrustdate, stDzmx.orientrustdate, sizeof(stDzbpdj.entrustdate));
				pstrcopy(stDzbpdj.chkdate, sChkDate, sizeof(stDzbpdj.chkdate));
				pstrcopy(stDzbpdj.chkacctord , sChkAcctOrd, sizeof(stDzbpdj.chkacctord));
				pstrcopy(stDzbpdj.trano,stDzmx.oritrano, sizeof(stDzbpdj.trano));
				pstrcopy(stDzbpdj.payeebankno, sPayeeBankNo, sizeof(stDzbpdj.payeebankno));
				pstrcopy(stDzbpdj.paybkcode, sPayBkCode, sizeof(stDzbpdj.paybkcode));
				pstrcopy(stDzbpdj.jyrq, stDzmx.orientrustdate, sizeof(stDzbpdj.jyrq));
				/*pstrcopy(stDzbpdj.jymc, "0000", sizeof(stDzbpdj.jymc));*/
				pstrcopy(stDzbpdj.khmc,stDzmx.handorgname,sizeof(stDzbpdj.khmc));
				/*pstrcopy(stDzbpdj.jyzh, stDzmx.payacct, sizeof(stDzbpdj.jyzh));注释掉本行by liurj 20180719*/
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				stDzbpdj.jyje = stDzmx.traamt; 
				pstrcopy(stDzbpdj.reason_info, "前置<->TIPS;TIPS多", sizeof(stDzbpdj.reason_info));
				pstrcopy(stDzbpdj.dzjg, "93", sizeof(stDzbpdj.dzjg));
				stDzbpdj.clzt[0]='0';
				pstrcopy(stDzbpdj.kzbz, "00000000", sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
				/*Add by wangw 20120816若zhqzlsh为0，则将交易流水号赋给zhqzlsh*/
				if(stDzbpdj.zhqzlsh==0)
					stDzbpdj.zhqzlsh = atol(stDzbpdj.trano);
				/* mod by tuql 20091009
				   pstrcopy(stDzbpdj.dqdh, "", sizeof(stDzbpdj.dqdh));
				   pstrcopy(stDzbpdj.jgdh, "", sizeof(stDzbpdj.jgdh));
				   pstrcopy(stDzbpdj.jygy, "", sizeof(stDzbpdj.jygy));
				   pstrcopy(stDzbpdj.zddh, "", sizeof(stDzbpdj.zddh));
				 */

				/* add by chenxm 20141105 DCI改造工作 */
				memset(sSql1, 0x00, sizeof(sSql1));
				iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);	
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("插入对帐不平登记表失败"),"ERROR");
					iflag = -4;
					break;
				}
				/*add end by chenxm */

				/* noted by chenxm 20141105 DCI改造工作 */
				/*EXEC SQL INSERT INTO tips_dzbpdj VALUES(:stDzbpdj);
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
				  if(SQLERR)
				  {
				  LOG(LM_STD,Fmtmsg("插入对帐不平登记表失败"),"ERROR");
				  iflag = -4;
				  break;
				  }*/
			}/* if( SQLNOTFOUND_TIPS ) 批量扣税费明细表中也没有 */
			else
			{
				/* 更新凭证数据表的对账标志 */
				/* add by chenxm 20141105 DCI改造工作 */
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "UPDATE tips_pzsj SET dzbz='1' "
						"where entrustdate='%s' and taxorgcode ='%s' and trano ='%s'",
						stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oritrano);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
				iSqlRet =DCIExecuteDirect(sSql1);
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("更新凭证数据表失败"),"ERROR");
					LOG(LM_STD,Fmtmsg("entrustdate[%s],oritaxorgcode[%s],trano[%s]",
								stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
					iflag = -6;
					break;
				}
				/*add end by chenxm */

				/*EXEC SQL UPDATE tips_pzsj
				  SET dzbz='1'
				  WHERE entrustdate=:stDzmx.orientrustdate
				  AND taxorgcode=:stDzmx.oritaxorgcode
				  AND trano=:stDzmx.oritrano;
				  if ( SQLERR )
				  {
				  LOG(LM_STD,Fmtmsg("更新凭证数据表失败"),"ERROR");
				  LOG(LM_STD,Fmtmsg("entrustdate[%s],oritaxorgcode[%s],trano[%s]",
				  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
				  iflag = -6;
				  break;
				  }*/
				/* add 20140901 */
				iQznum ++;
				dQzamt = dQzamt + stDzmx.traamt;  /* tips前置对账总金额 */

				/* end add 20140901 */    	        
			}    
		}/* if( SQLNOTFOUND_TIPS ) 当日流水表中没有 */
		else
		{    
			/* 更新凭证数据表的对账标志 */
			/* add by chenxm 20141105 DCI改造工作 */
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_pzsj SET dzbz='1' "
					"where entrustdate='%s' and taxorgcode ='%s' and trano ='%s'",
					stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oritrano);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet =DCIExecuteDirect(sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("更新凭证数据表失败"),"ERROR");
				LOG(LM_STD,Fmtmsg("entrustdate[%s],oritaxorgcode[%s],trano[%s]",
							stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
				iflag = -5;
				break;
			}
			/*add end by chenxm */
			/*EXEC SQL UPDATE tips_pzsj
			  SET dzbz='1'
			  WHERE entrustdate=:stDzmx.orientrustdate
			  AND taxorgcode=:stDzmx.oritaxorgcode
			  AND trano=:stDzmx.oritrano;
			  if ( SQLERR )
			  {
			  LOG(LM_STD,Fmtmsg("更新凭证数据表失败"),"ERROR");
			  LOG(LM_STD,Fmtmsg("entrustdate[%s],oritaxorgcode[%s],trano[%s]",
			  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
			  iflag = -5;
			  break;
			  }
			 */
			/* add 20140901 */
			iQznum ++;
			dQzamt = dQzamt + stDzmx.traamt;  /* tips前置对账总金额 */

			/* end add 20140901 */
		}

	}/*循环勾对结束*/	
	//EXEC SQL CLOSE cur_dzmxxx_tipsdz;    
	DCIFreeCursor(cur);

	if (iflag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24364, Fmtmsg("与TIPS对税收账失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("与TIPS对税收账失败[%d]", iflag), 
				fpub_GetCompname(lXmlhandle));
	}

	/* 循环读取tips_ssplksfmx表记录,把对账日期与对账批次更新到批量交易表中去 */ 
	/* add by chenxm 20141105 DCI改造工作 */	
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT entrustdate,taxorgcode,packno FROM  tips_ssplksfmx \
		where chkdate ='%s' and chkacctord ='%s' and paybkcode ='%s' and payeebankno='%s' \
		and czbd = '7' and substr(kzbz,2,1) = '1' ORDER BY entrustdate, taxorgcode, packno",\
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
	if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur1) == -1)
	{
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur1);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}
	//add end by chenxm 20141105

	/*EXEC SQL DECLARE cur_plksfmx_tipsdz CURSOR for 
	  SELECT entrustdate,taxorgcode,packno 
	  FROM  tips_ssplksfmx
	  WHERE chkdate = :sChkDate 
	  AND chkacctord = :sChkAcctOrd
	  AND paybkcode = :sPayBkCode
	  AND payeebankno = :sPayeeBankNo
	  AND czbd = '7'
	  AND substr(kzbz,2,1) = '1'
	  GROUP by entrustdate, taxorgcode, packno;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));

	  EXEC SQL OPEN cur_plksfmx_tipsdz;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN, "cur_plksfmx_tipsdz", sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	  if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("打开游标失败"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开cur_plksfmx_tipsdz游标失败"), 
	  fpub_GetCompname(lXmlhandle));
	  }	*/

	iflag=0;
	for (i=1;;i++)
	{
		memset(sEntrustDate, 0x00, sizeof(sEntrustDate));
		memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
		memset(sPackNo, 0x00, sizeof(sPackNo));

		iSqlRet = DCIFetch2(cur1, DCI_FETCH_NEXT, 0) ;
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iflag=-1;
			LOG(LM_STD,Fmtmsg("从cur_plksfmx_tipsdz获取数据失败"),fpub_GetCompname(lXmlhandle));
			break;
		}

		if(iSqlRet == 0)
			break;

		sprintf( sEntrustDate, "%s", DCIFieldAsString( cur, 0 ) );
		sprintf( sTaxOrgCode, "%s", DCIFieldAsString( cur, 1) );
		sprintf( sPackNo, "%s", DCIFieldAsString( cur, 2 ) );

		/*EXEC SQL FETCH cur_plksfmx_tipsdz INTO :sEntrustDate, :sTaxOrgCode, :sPackNo;     
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH, "cur_plksfmx_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
		  if ( SQLERR )
		  {  
		  iflag=-1;
		  LOG(LM_STD,Fmtmsg("从cur_plksfmx_tipsdz获取数据失败"),fpub_GetCompname(lXmlhandle));
		  break;
		  }
		  if ( SQLNOTFOUND )
		  break;
		 */

		trim(sEntrustDate);
		trim(sTaxOrgCode);
		trim(sPackNo);

		/* 更新对账日期、对账批次号 */
		/*add by chenxm 20141105 DCI改造工作*/
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET chkdate ='%s',chkacctord='%s' \
			where entrustdate='%s' and orgcode='%s' and packno='%s'",\
			sChkDate, sChkAcctOrd, sEntrustDate, sTaxOrgCode, sPackNo);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			iflag=-2;
			LOG(LM_STD,Fmtmsg("更新tips_pljydj的对账日期、对账批次失败"),fpub_GetCompname(lXmlhandle));
			LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s]",
						sEntrustDate, sTaxOrgCode, sPackNo),fpub_GetCompname(lXmlhandle));
			break;
		}
		/*add end by chenxm */

		/*EXEC SQL UPDATE tips_pljydj 
		  SET chkdate = :sChkDate,
		  chkacctord = :sChkAcctOrd 
		  WHERE  entrustdate=:sEntrustDate  */      /*委托日期*/
		// AND  orgcode=:sTaxOrgCode          /*征收机关代号*/
		// AND	packno=:sPackNo;                 /*包流水号*/
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));          
		  if ( SQLERR )
		  {  
		  iflag=-2;
		  LOG(LM_STD,Fmtmsg("更新tips_pljydj的对账日期、对账批次失败"),fpub_GetCompname(lXmlhandle));
		  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s]",
		  sEntrustDate, sTaxOrgCode, sPackNo),fpub_GetCompname(lXmlhandle));
		  break;
		  }*/
	}
	DCIFreeCursor(cur1);
	//EXEC SQL CLOSE cur_plksfmx_tipsdz;    

	if (iflag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24365, Fmtmsg("更新批量交易登记表的对账日期及对账批次失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新批量交易登记表的对账日期及对账批次失败[%d]", iflag), 
				fpub_GetCompname(lXmlhandle));
	}

	/* 打开日间对账不平文件 */
	memset(sRjbpFile, 0x00, sizeof(sRjbpFile));
	snprintf(sRjbpFile, sizeof(sRjbpFile),"%s/file/tips/chkacct/rjdzbp_%s_%s_%s_%s",
			getenv("HOME"),sChkDate,sPayBkCode,sPayeeBankNo,sChkAcctOrd);
	fp = fopen(sRjbpFile, "wt");
	if(fp == NULL)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24366, Fmtmsg("打开日间对账不平文件失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开日间对账不平文件失败[%s][%s]", 
					strerror(errno), sRjbpFile), fpub_GetCompname(lXmlhandle));
	}
	fprintf(fp,"日间对帐不平记录[%s %s]\n", GetSysDate(), GetSysTime());

	/*
	   判断是否还有没有核对的前置流水
	   如果是日切对账，则记入对账不平登记表，如果是日间对账，记入临时文件
	   状态不明的银行端申报缴款业务不参与当日对账，
	   顺延至次日进行对账，超过规定期限的批量扣税业务将进行作废处理。
	 */
	iCount = 0 ;
	/* add by chenxm 20141105 DCI改造工作*/
	memset(sSql1, 0x00, sizeof(sSql1));
	memset(sErrmsg, 0x00, sizeof(sErrmsg));
	memset(sTemp,0x00, sizeof(sTemp));
	sprintf(sSql1, "select count(*) from tips_drls \
		where jyzt = '0' and qsbz = '0' and substr(dzbz,2,1) = '0' \
		and paybkcode ='%s' and payeebankno ='%s' and ((msgno = '3001' \
		AND workdate = '%s') or (msgno = '1008' and workdate  = '%s'))",\
			sPayBkCode,sPayeeBankNo,sChkDate,sChkDate);
	LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
	iSqlRet = DBSelectToVarChar(sErrmsg, sTemp, sSql1);	    
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fclose(fp);
		fpub_SetMsg(lXmlhandle, 24367, "查询当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle))
	}
	iCount = atol(sTemp);
	/* add end by chenxm */

	/*EXEC SQL SELECT COUNT(*) INTO :iCount 
	  FROM tips_drls 
	  WHERE jyzt = '0'*/                  /*交易状态0 成功*/
	//AND qsbz = '0' 
	//AND substr(dzbz,2,1) = '0'               /* 对账标志第二位：0-未与TIPS对账 */
	//AND paybkcode = :sPayBkCode     /*付款行行号*/
	//AND payeebankno = :sPayeeBankNo /*收款行行号*/
	/*AND ( 
	  ( msgno = '3001' AND workdate = :sChkDate )	
	  OR
	  ( msgno = '1008' AND workdate  = :sChkDate )*/ /* 对当日没有对平的1008,要对出来进行重发 */                    
	//);  
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");	
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetMsg(lXmlhandle, 24367, "查询当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("查询当日流水表失败"), 
	  fpub_GetCompname(lXmlhandle))
	  }*/
	LOG(LM_STD, Fmtmsg("日期[%s]没有核对的前置单笔流水[%d]条",sChkDate,iCount), fpub_GetCompname(lXmlhandle))        
		/* 如当前工作日当日流水表还有未核对的流水 */
		if ( iCount > 0 )
		{
			if(iRet == 2) 
				iRet == 3;  /*状态3 TIPS有多，银行也多*/
			else
				iRet = 1;   /*状态1 银行多*/

			iBkdnum = iBkdnum + iCount;  /*iBkdnum银行多的计数器*/

			/* add by chenxm 20141105 DCI改造工作 */	
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT * FROM tips_drls WHERE jyzt = '0' AND qsbz = '0'\
				AND substr(dzbz,2,1) = '0' AND paybkcode ='%s' AND payeebankno='%s' AND\
				 ( ( msgno = '3001' AND workdate = '%s' ) OR ( msgno = '1008' AND workdate  = '%s' ))",\
					sPayBkCode, sPayeeBankNo,sChkDate,sChkDate);
			if ((cur2 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				return COMPRET_FAIL;
			}
			if (DCIExecute(cur2) == -1)
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
					DCIFreeCursor(cur2);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
			}
			/*add end by chenxm 20141105*/

			/*EXEC SQL DECLARE cur_drls_tipsdz CURSOR for 
			  SELECT *
			  FROM  tips_drls
			  WHERE jyzt = '0'                  交易状态0 成功
			  AND qsbz = '0' 
			  AND substr(dzbz,2,1) = '0'                对账标志第二位：0-未与TIPS对账 
			  AND paybkcode = :sPayBkCode     /付款行行号/
			  AND payeebankno = :sPayeeBankNo /收款行行号*/
			/*  AND ( 
				( msgno = '3001' AND workdate = :sChkDate )	
				OR
				( msgno = '1008' AND workdate  = :sChkDate )*/ /* 对当日没有对平的1008,要对出来进行重发                     
																  );
																  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));*/

			/*EXEC SQL OPEN cur_drls_tipsdz;
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_drls_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
			  if ( SQLERR )
			  {
			  fclose(fp);
			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("打开游标失败"));
			  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开cur_drls_tipsdz游标失败"), 
			  fpub_GetCompname(lXmlhandle));
			  }*/

			/* 循环处理银行多的实时流水记录 */
			iflag=0;
			for (i=1; i<= iCount ;i++)
			{
				memset(&stDrls, 0x00, sizeof(stDrls));
				memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
				/*EXEC SQL FETCH cur_drls_tipsdz INTO :stDrls;   */
				iSqlRet = DBFetch(cur2, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls, sErrmsg);		
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_drls_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));*/	
				/*if ( SQLERR )*/
				if(iSqlRet < 0)
				{  
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					iflag=-1;
					LOG(LM_STD,Fmtmsg("从cur_drls_tipsdz获取数据失败"),fpub_GetCompname(lXmlhandle));
					break;
				}
				/*if ( SQLNOTFOUND )*/
				if(iSqlRet == 0)
					break;

				trim(stDrls.jyrq);
				trim(stDrls.payeebankno);
				trim(stDrls.payacct);

				/* add 20140901 */
				dBkdamt = dBkdamt + stDrls.jyje; /*iBkdnum银行多的金额 */
				/* end 20140901 */

				if(strncmp(stDrls.msgno, "3001", 4) == 0)
				{
					LOG_SSTIPS("3111",Fmtmsg("-->(实时)银行多,TIPS无：交易日期[%s],前置流水[%d],国库收款行[%s],帐号[%s],金额[%15.2f],解决办法：TIPS为准,调整帐务",
								stDrls.zwrq,stDrls.zhqzlsh,stDrls.payeebankno,stDrls.payacct,stDrls.jyje),sPayBkCode,sChkDate);
					/* strcpy(stDzbpdj.jymc, "实时扣款"); mod by tuql 20090910*/
				}
				else
				{
					LOG_SSTIPS("3111",Fmtmsg("-->(银缴)银行多,TIPS无：交易日期[%s],前置流水[%d],国库收款行[%s],帐号[%s],金额[%15.2f],解决办法：TIPS为准,调整帐务",
								stDrls.zwrq,stDrls.zhqzlsh,stDrls.payeebankno,stDrls.payacct,stDrls.jyje),sPayBkCode,sChkDate);
					/* strcpy(stDzbpdj.jymc, "银行缴款"); mod by tuql 20090910*/
				}

				pstrcopy(stDzbpdj.zwrq,stDrls.zwrq, sizeof(stDzbpdj.zwrq));
				pstrcopy(stDzbpdj.workdate,stDrls.workdate, sizeof(stDzbpdj.workdate));
				stDzbpdj.zhqzlsh = stDrls.zhqzlsh;
				pstrcopy(stDzbpdj.zjlsh,stDrls.zjlsh, sizeof(stDzbpdj.zjlsh));
				if(sChkAcctType[0]=='0')
					stDzbpdj.dzlx[0]='2';
				else
					stDzbpdj.dzlx[0]='3';
				pstrcopy(stDzbpdj.taxorgcode, stDrls.taxorgcode, sizeof(stDzbpdj.taxorgcode));
				pstrcopy(stDzbpdj.entrustdate, stDrls.entrustdate, sizeof(stDzbpdj.entrustdate));
				pstrcopy(stDzbpdj.chkdate, sChkDate, sizeof(stDzbpdj.chkdate));  		
				pstrcopy(stDzbpdj.chkacctord , sChkAcctOrd, sizeof(stDzbpdj.chkacctord));
				pstrcopy(stDzbpdj.trano,stDrls.trano, sizeof(stDzbpdj.trano));
				pstrcopy(stDzbpdj.payeebankno, stDrls.payeebankno, sizeof(stDzbpdj.payeebankno));
				pstrcopy(stDzbpdj.paybkcode, stDrls.paybkcode, sizeof(stDzbpdj.paybkcode));
				pstrcopy(stDzbpdj.jyrq, stDrls.jyrq, sizeof(stDzbpdj.jyrq));
				pstrcopy(stDzbpdj.khmc, stDrls.handorgname, sizeof(stDzbpdj.khmc)); 
				/* pstrcopy(stDzbpdj.jymc, "前置<->TIPS;实时前置多", sizeof(stDzbpdj.jymc)); mod by tuql 20090910*/
				pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDrls.msgno));
				pstrcopy(stDzbpdj.jyzh, stDrls.payacct, sizeof(stDzbpdj.jyzh));  		    
				pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));
				pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
				pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.jyqd, stDrls.jyqd, sizeof(stDzbpdj.jyqd));
				pstrcopy(stDzbpdj.jysj, stDrls.jysj, sizeof(stDzbpdj.jysj));  		    
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				pstrcopy(stDzbpdj.dzjg, "92", sizeof(stDzbpdj.dzjg));
				stDzbpdj.jyje = stDrls.jyje;
				pstrcopy(stDzbpdj.reason_info, "前置<->TIPS;实时前置多", sizeof(stDzbpdj.reason_info));
				stDzbpdj.clzt[0]='0';
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				pstrcopy(stDzbpdj.kzbz, stDrls.kzbz, sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.dqdh, stDrls.dqdh, sizeof(stDzbpdj.dqdh));
				pstrcopy(stDzbpdj.jgdh, stDrls.jgdh, sizeof(stDzbpdj.jgdh));
				pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.zddh, stDrls.zddh, sizeof(stDzbpdj.zddh));
				if(sChkAcctType[0] == '1')/* 日切对账 */
				{
					iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);
					/*EXEC SQL INSERT INTO tips_dzbpdj VALUES(:stDzbpdj);
					  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");*/
					/*if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						iflag=-2;
						LOG(LM_STD,Fmtmsg("插入对帐登记表失败"),"ERROR");
						break;
					}
				}else
				{
					trim(stDrls.zjlsh);
					trim(stDrls.trano);
					trim(stDrls.payacct);
					trim(stDrls.taxvouno);
					fprintf(fp,"%s|%d|%s|%s|%s|%s|%.2f|%s|\n",
							stDrls.zwrq, stDrls.zhqzlsh, stDrls.zjlsh, stDrls.entrustdate,
							stDrls.trano, stDrls.payacct, stDrls.jyje, stDrls.taxvouno);
				}		                
			}/* 循环处理银行多的实时流水记录 */
			DCIFreeCursor(cur2);
			/*EXEC SQL CLOSE cur_drls_tipsdz;   */ 

			if (iflag < 0)
			{
				fclose(fp);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24368, Fmtmsg("与TIPS对账时处理前置多实时流水记录失败"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("与TIPS对账时处理前置多流水实时记录失败[%d]", iflag), 
						fpub_GetCompname(lXmlhandle));
			}

			/*如果是日切对账，则标记已核对过, 银行多的实时流水*/
			if(sChkAcctType[0] == '1')
			{
				LOG(LM_STD,"日切对账，则标记已核对过的实时流水记录","INFO");
				/*标记已核对过, 银行多的流水*/
				//add by chenxm 20141105 DCI改造工作
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, " UPDATE tips_drls SET chkdate ='%s',chkacctord ='%s',dzbz=substr(dzbz,1,1)||'2' "
						"WHERE jyzt = '0' AND qsbz = '0' AND substr(dzbz,2,1) = '0' AND paybkcode ='%s' "
						"AND payeebankno ='%s' "
						"AND ( ( msgno = '3001' AND workdate = '%s' ) OR ( msgno = '1008' AND workdate < '%s' ))",
						sChkDate,sChkAcctOrd,sPayBkCode,sPayeeBankNo,sChkDate,sChkDate);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
				iSqlRet = DCIExecuteDirect(sSql1);
				//add end 

				/*EXEC SQL UPDATE tips_drls 
				  SET chkdate = :sChkDate,
				  chkacctord = :sChkAcctOrd,
				  dzbz=substr(dzbz,1,1)||'2'   /          / 对账标志 2-前置多 /
				  WHERE jyzt = '0'                  /交易状态0 成功/
				  AND qsbz = '0' 
				  AND substr(dzbz,2,1) = '0'               / 对账标志第二位：0-未与TIPS对账 /
				  AND paybkcode = :sPayBkCode     /付款行行号/
				  AND payeebankno = :sPayeeBankNo /收款行行号/
				  AND ( 
				  ( msgno = '3001' AND workdate = :sChkDate )	
				  OR
				  ( msgno = '1008' AND workdate < :sChkDate ) *//* 此处为< 主要是银行端缴款会两日对清                     
				);
				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
				if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						fclose(fp);
						fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
						fpub_SetMsg(lXmlhandle, 24369, Fmtmsg("与TIPS对账时更新当日流水表失败"));
						LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("与TIPS对账时更新当日流水表失败"), 
								fpub_GetCompname(lXmlhandle));
					}


				/* add 20140901 */
				dBkdamt = dBkdamt + stDrls.jyje; /*iBkdnum银行多的金额 */
				/* end 20140901 */


			}/*if(sChkAcctType[0] == '1')如果是日切对账，则标记已核对过, 银行多的实时流水*/
		}/* if ( iCount > 0 ) 如当前工作日当日流水表还有未核对的流水 */

	/*
	   判断是否还有没有核对的前置批量流水
	   如果是日切对账，则记入对账不平表，如果是日间对账，记入临时文件
	   状态不明的定时批量扣税业务和银行端申报缴款业务不参与当日对账，
	   顺延至次日进行对账，超过规定期限的批量扣税业务将进行作废处理。
	 */
	iCount = 0 ;
	//add by chenxm 20141105 DCI改造工作
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssplksfmx WHERE czbd= '7' AND substr(kzbz,2,1)='0' "
			"AND workdate ='%s' AND paybkcode ='%s' AND payeebankno = '%s'",
			sChkDate,sPayBkCode,sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
	iSqlRet = DBSelectToVar(sErrmsg,&iCount,sSql1);
	//add end 

	/*EXEC SQL SELECT COUNT(*) INTO :iCount 
	  FROM tips_ssplksfmx 
	  WHERE czbd= '7'  
	  AND substr(kzbz,2,1)='0'    
	  AND workdate = :sChkDate   */    /*对账日期*/
	//  AND paybkcode = :sPayBkCode    /*付款行行号*/
	//  AND payeebankno = :sPayeeBankNo;   /*收款行行号*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");	
	  if ( SQLERR )*/
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fclose(fp);
		fpub_SetMsg(lXmlhandle, 24370, "查询批量扣税费明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("查询批量扣税费明细表失败"), 
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_STD, Fmtmsg("没有核对的前置批量流水[%d]条", iCount), fpub_GetCompname(lXmlhandle))
		/* 如当前工作日批量扣税费明细表还有未核对的流水 */
		if ( iCount > 0 )
		{
			if(iRet == 2 || iRet == 3) 
				iRet == 3;  /*状态3 TIPS有多，银行也多*/
			else
				iRet = 1;   /*状态1 银行多*/

			iBkdnum = iBkdnum + iCount;  /*银行多的计数器*/

			/* add by chenxm 20141105 DCI改造工作 */	
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT * FROM tips_ssplksfmx WHERE czbd= '7' \
				AND substr(kzbz,2,1)='0' AND workdate ='%s' AND paybkcode ='%s' AND payeebankno = '%s'",\
					sChkDate,sPayBkCode, sPayeeBankNo);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			if ((cur3 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				return COMPRET_FAIL;
			}
			if (DCIExecute(cur3) == -1)
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
					DCIFreeCursor(cur1);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
			}
			//add end by chenxm 20141105

			/*EXEC SQL DECLARE cur_ksfmx_tipsdz CURSOR for 
			  SELECT *
			  FROM tips_ssplksfmx 
			  WHERE czbd= '7'  
			  AND substr(kzbz,2,1)='0'    
			  AND workdate = :sChkDate       //对账日期//
			  AND paybkcode = :sPayBkCode    //收款行行号//
			  AND payeebankno = :sPayeeBankNo;   //收款行行号//
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));

			  EXEC SQL OPEN cur_ksfmx_tipsdz;
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ksfmx_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
			  if ( SQLERR )
			  {
			  fclose(fp);
			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("打开游标失败"));
			  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开cur_ksfmx_tipsdz游标失败"), 
			  fpub_GetCompname(lXmlhandle));
			  }*/
			/* 循环处理银行多的批量流水记录 */
			iflag=0;
			for (i=1; i<= iCount ;i++)
			{
				memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
				memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
				//EXEC SQL FETCH cur_ksfmx_tipsdz INTO :stPlksfmx; 
				iSqlRet = DBFetch(cur3, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);			
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_ksfmx_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
				  if ( SQLERR )*/
				if(iSqlRet < 0)
				{  
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					iflag=-1;
					LOG(LM_STD,Fmtmsg("从cur_drls_tipsdz获取数据失败"),fpub_GetCompname(lXmlhandle));
					break;
				}
				//if ( SQLNOTFOUND )
				if(iSqlRet == 0)
					break;

				trim(stPlksfmx.payeebankno);
				trim(stPlksfmx.payacct);
				LOG_SSTIPS("3111",Fmtmsg("-->(批扣)银行多,TIPS无：交易日期[%s],前置流水[%d],国库收款行[%s],帐号[%s],金额[%15.2f],解决办法：TIPS为准,调整帐务",
							stPlksfmx.zwrq,stPlksfmx.plmxxh,stPlksfmx.payeebankno,stPlksfmx.payacct,stPlksfmx.jyje),sPayBkCode,sChkDate);

				pstrcopy(stDzbpdj.zwrq,stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));
				pstrcopy(stDzbpdj.workdate,stPlksfmx.workdate, sizeof(stDzbpdj.workdate));
				stDzbpdj.zhqzlsh = stPlksfmx.plmxxh;  /*批量明细序号*/
				if(sChkAcctType[0]=='0')
					stDzbpdj.dzlx[0]='2';
				else
					stDzbpdj.dzlx[0]='3';
				pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));/* add by tuql 20090507 主机流水号*/	
				pstrcopy(stDzbpdj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stDzbpdj.taxorgcode));
				pstrcopy(stDzbpdj.entrustdate, stPlksfmx.entrustdate, sizeof(stDzbpdj.entrustdate));
				pstrcopy(stDzbpdj.chkdate, sChkDate, sizeof(stDzbpdj.chkdate));
				pstrcopy(stDzbpdj.chkacctord, sChkAcctOrd, sizeof(stDzbpdj.chkacctord));
				pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));
				pstrcopy(stDzbpdj.payeebankno, sPayeeBankNo, sizeof(stDzbpdj.payeebankno));
				pstrcopy(stDzbpdj.paybkcode, sPayBkCode, sizeof(stDzbpdj.paybkcode));
				pstrcopy(stDzbpdj.jyrq, stPlksfmx.zwrq, sizeof(stDzbpdj.jyrq));
				pstrcopy(stDzbpdj.jysj, stPlksfmx.zjsj, sizeof(stDzbpdj.jysj));
				/* pstrcopy(stDzbpdj.jymc, "前置<->TIPS;批量前置多", sizeof(stDzbpdj.jymc)); */
				pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));
				pstrcopy(stDzbpdj.khmc, stPlksfmx.handorgname, sizeof(stDzbpdj.khmc));
				pstrcopy(stDzbpdj.jyzh, stPlksfmx.payacct, sizeof(stDzbpdj.jyzh));
				pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				stDzbpdj.jyje = stPlksfmx.jyje;
				pstrcopy(stDzbpdj.reason_info, "前置<->TIPS;批量前置多", sizeof(stDzbpdj.reason_info));
				pstrcopy(stDzbpdj.dzjg, "92", sizeof(stDzbpdj.dzjg));
				stDzbpdj.clzt[0]='0';
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
				pstrcopy(stDzbpdj.kzbz, stPlksfmx.kzbz, sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.byzd, sPackNo, sizeof(stDzbpdj.byzd));
				pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));
				pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));
				pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));
				/*Add by wangw 20120816若zhqzlsh为0，则将交易流水号赋给zhqzlsh*/
				if(stDzbpdj.zhqzlsh==0)
					stDzbpdj.zhqzlsh = atol(stDzbpdj.trano);
				if(sChkAcctType[0] == '1')/* 日切对账 */
				{
					//EXEC SQL INSERT INTO tips_dzbpdj VALUES(:stDzbpdj);
					iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);
					/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
					  if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						
						iflag=-2;
						LOG(LM_STD,Fmtmsg("插入对帐登记表失败"),"ERROR");
						break;
					}
				}else
				{
					trim(stPlksfmx.zjlsh);
					trim(stPlksfmx.trano);
					trim(stPlksfmx.payacct);
					trim(stPlksfmx.taxvouno);
					fprintf(fp,"%s|%d|%s|%s|%s|%s|%.2f|%s|\n",
							stPlksfmx.zwrq, stPlksfmx.plmxxh, stPlksfmx.zjlsh, stPlksfmx.entrustdate,
							stPlksfmx.trano, stPlksfmx.payacct, stPlksfmx.jyje, stPlksfmx.taxvouno);
				}                           
			}/* for (i=1; i<= iCount ;i++)循环处理银行多的批量流水记录 */            
			/*EXEC SQL CLOSE cur_ksfmx_tipsdz;    */

			if (iflag < 0)
			{
				fclose(fp);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24371, Fmtmsg("与TIPS对账时处理前置多批量流水记录失败"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("与TIPS对账时处理前置多批量流水记录失败[%d]", iflag), 
						fpub_GetCompname(lXmlhandle));
			}

			/*如果是日切对账，则标记已核对过, 银行多的批量流水*/
			if(sChkAcctType[0] == '1')
			{
				LOG(LM_STD,"日切对账，则标记已核对过的批量流水记录","INFO");
				/*标记已核对过, 银行多的批量流水*/
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "UPDATE tips_ssplksfmx SET chkdate = '%s', chkacctord = '%s',\
					kzbz=substr(kzbz,1,1)||'2'||substr(kzbz,3,6) \
					WHERE czbd= '7' AND substr(kzbz,2,1)='0' AND workdate ='%s' \
					AND paybkcode = '%s' AND payeebankno ='%s'",\
						sChkDate, sChkAcctOrd, sChkDate,sPayBkCode,sPayeeBankNo);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
				iSqlRet = DCIExecuteDirect(sSql1);
				/*EXEC SQL UPDATE tips_ssplksfmx 
				  SET chkdate = :sChkDate,
				  chkacctord = :sChkAcctOrd,
				  kzbz=substr(kzbz,1,1)||'2'||substr(kzbz,3,6)             //扩展标志 2-前置多 //
				  WHERE czbd= '7'  
				  AND substr(kzbz,2,1)='0'    
				  AND workdate = :sChkDate       //对账日期//
				  AND paybkcode = :sPayBkCode    //收款行行号//
				  AND payeebankno = :sPayeeBankNo;   //收款行行号*/
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
				  if(SQLERR)*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					fclose(fp);
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
					fpub_SetMsg(lXmlhandle, 24372, Fmtmsg("与TIPS对账时更新批量扣税费明细表失败"));
					LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("与TIPS对账时更新批量扣税费明细表失败"), 
							fpub_GetCompname(lXmlhandle));
				}

				/* add 20140901 */
				dBkdamt = dBkdamt + stPlksfmx.jyje; /*iBkdnum银行多的金额 */
				/* end 20140901 */

			}
		}/* if ( iCount > 0 )如当前工作日批量扣税费明细表还有未核对的流水 */		
	fclose(fp);
	LOG_SSTIPS("3111",Fmtmsg("============================================================================="),sPayBkCode,sChkDate);
	LOG_SSTIPS("3111",Fmtmsg("   核对TIPS明细总笔数[%d]  TIPS多的笔数[%d]  银行多的笔数[%d]\n",iTpnum,iTpdnum,iBkdnum),sPayBkCode,sChkDate);
	
	/* add dci 20141103 */
	iSqlRet=DCICommit();
	/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释    		
	if ( iSqlRet < 0 )
  {
     	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
     	DCIRollback();
      	
     	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
     	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     	return COMPRET_FAIL;     
  }
  */
	/* end dci */
	
	fpub_SetMsg(lXmlhandle, 0, "与TIPS对税收账结束");
	fpub_SetCompStatus(lXmlhandle, iRet);
	/* add by tuql 20100104 1.0.5.0 将对账结果账给/tips/chktipszt结点 */
	memset(sBuf, 0x00, sizeof(sBuf));
	snprintf(sBuf, sizeof(sBuf), "%d", iRet);
	COMP_SOFTSETXML("/tips/chktipszt", sBuf)
		LOG(LM_STD,Fmtmsg("与TIPS对税收账结束"), fpub_GetCompname(lXmlhandle));
	LOG(LM_STD,Fmtmsg("核对TIPS明细总笔数[%d],TIPS多的笔数[%d],银行多的笔数[%d]",
				iTpnum,iTpdnum,iBkdnum), fpub_GetCompname(lXmlhandle));

	/* 增加对账结果统计 add 20140901 */
	/* 初始化对账结果登记表 
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzjgxx  WHERE dzrq = '%s' AND dzxt='0'",sChkDate);
	iSqlRet = DCIExecuteDirect(sSql1);

	/*EXEC SQL delete FROM tips_dzjgxx
	  WHERE dzrq = :sChkDate
	  AND dzxt='0';*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	  if ( SQLERR )
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("删除对账结果登记表记录失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除对账结果登记表记录失败"), 
				fpub_GetCompname(lXmlhandle));
	}
	/* add 20140901 
	iQznum += iBkdnum;
	dQzamt += dBkdamt;  /* tips前置对账总金额 

	pstrcopy(stDzjgxx.dzrq , sChkDate ,sizeof(stDzjgxx.dzrq));
	stDzjgxx.dzxt[0] = '0';
	pstrcopy(stDzjgxx.chkacctord  , sChkAcctOrd ,sizeof(stDzjgxx.chkacctord));
	stDzjgxx.allnum1 = iQznum;     
	stDzjgxx.allamt1 = dQzamt;    
	stDzjgxx.Allnum2 = iTpnum;			
	stDzjgxx.Allamt2 = dTpamt;     
	if(iRet == 0 )
		stDzjgxx.dzjg[0] = '1';
	else if(iRet == 1)
		stDzjgxx.dzjg[0] = '2';
	else if(iRet == 2)
		stDzjgxx.dzjg[0] = '3';
	else if(iRet == 3)
		stDzjgxx.dzjg[0] = '4';    		
	pstrcopy(stDzjgxx.byzd ,"",sizeof(stDzjgxx.byzd));

	iSqlRet = DBInsert("tips_dzjgxx", SD_TIPS_DZJGXX, NUMELE(SD_TIPS_DZJGXX), &stDzjgxx, sErrmsg);
	/*EXEC SQL INSERT INTO tips_dzjgxx values(:stDzjgxx);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if(SQLERR)
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		LOG(LM_STD,Fmtmsg("插入对帐结果失败,对账日期[%s],对账系统[%s]", 
					stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")   
			iflag = -13;

	} */   
	LOG(LM_STD,Fmtmsg("TIPS明细总笔数[%d],TIPS明细总金额[%f],TIPS前置笔数[%d],TIPS前置金额[%f]",
				iTpnum,dTpamt,iQznum,dQzamt), fpub_GetCompname(lXmlhandle));    
	return COMPRET_SUCC;
}


/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_ChkYHJKXX
  组件名称: 银行端缴款信息核对

  组件功能: 
  银行端缴款信息核对
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

  主要操作库表:
  表名              操作
  税收对账批量头	tips_ssdzplt
  税收对账明细信息 tips_ssdzmxxx

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年02月27日
  修改日期: 20141105 DCI改造工作(done)
  修改日期: 20141220DCI改造，已测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_ChkYHJKXX(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	SDB_TIPS_DRLS stDrls;
	char sPayBkCode[12+1];/* 付款行行号 */
	char sPackNo[8+1];/* 包流水号--视为对账批次 */
	char sChkDate[8+1];/* 对账日期 */
	int iCurPackNum;/* 本包笔数 */
	int iCurPackNo;/* 本包序号 */
	//EXEC SQL END   DECLARE SECTION;

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128]; 
	char sBuf[256];
	char sNode[256];/* 节点路径 */
	char sFile[256];
	char sYhjkbfFlow[60];
	char sJyzt[50+1];/* 交易状态 */
	int i;
	int iSucc=0;
	int iFail=0;
	int iSqlRet = -1;
	FILE *fp;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(6);
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(1, sBuf, "付款行行号")
		pstrcopy( sPayBkCode, sBuf, sizeof(sPayBkCode));
	trim(sPayBkCode);            

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPackNo, 0x00, sizeof(sPackNo));
	COMP_GETPARSEPARAS(2, sBuf, "包流水号")
		pstrcopy( sPackNo, sBuf, sizeof(sPackNo));
	trim(sPackNo); 

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(3, sBuf, "对账日期")
		pstrcopy( sChkDate, sBuf, sizeof(sChkDate));
	trim(sChkDate); 

	memset(sBuf, 0x00, sizeof(sBuf));
	iCurPackNum = 0 ;
	COMP_GETPARSEPARAS(4, sBuf, "本包笔数")
		iCurPackNum = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	iCurPackNo = 0 ;
	COMP_GETPARSEPARAS(5, sBuf, "本包序号")
		iCurPackNo = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYhjkbfFlow, 0x00, sizeof(sYhjkbfFlow));
	COMP_GETPARSEPARAS(6, sBuf, "银行缴款补发流程名")
		pstrcopy( sYhjkbfFlow, sBuf, sizeof(sYhjkbfFlow));
	trim(sYhjkbfFlow); 

	LOG(LM_STD,Fmtmsg("银行端缴款信息核对开始处理... 付款行行号[%s],包流水号[%s],对账日期[%s]", 
				sPayBkCode, sPackNo, sChkDate), fpub_GetCompname(lXmlhandle));
	LOG(LM_STD,Fmtmsg("本包笔数[%d],本包序号[%d], 银行缴款补发流程名[%s]", 
				iCurPackNum, iCurPackNo, sYhjkbfFlow), fpub_GetCompname(lXmlhandle));

	/*对账结果文件名*/
	memset(sFile, 0x00, sizeof(sFile));   
	snprintf(sFile, sizeof(sFile),"%s/file/tips/chkacct/yhjkdz_%s_%s",
			getenv("HOME"),sPayBkCode,sChkDate);
	trim(sFile);
	LOG(LM_STD,Fmtmsg("银行端缴款对账结果文件[%s]", sFile), fpub_GetCompname(lXmlhandle));

	/*建立文件*/
	fp=fopen(sFile,"a+");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24376, Fmtmsg("打开银行端缴款对账结果文件失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开银行端缴款对账结果文件失败[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	/*文件头*/
	fprintf(fp,"                                              银行端缴款对帐文件\n");
	fprintf(fp,"     付款行行号:%s                   包流水号:%s               对帐日期:%s            本包序号:%d \n",
			sPayBkCode,sPackNo,sChkDate,iCurPackNo);
	fprintf(fp,"=========================================================================================================\n");
	fprintf(fp,"付款开户行行号   原征收机关代码   原委托日期   原交易流水号   税票号码          交易金额   交易状态      \n");
	fprintf(fp,"=========================================================================================================\n");

	for(i=1;i<=iCurPackNum;i++)
	{
		memset(&stDrls,0x00,sizeof(stDrls)); 
		memset(sJyzt, 0x00, sizeof(sJyzt));

		/*付款开户行行号*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/PayOpBkCode",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.paybkcode,sBuf,sizeof(stDrls.paybkcode));

		/*原发起机构代码*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/OriTaxOrgCode",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.taxorgcode,sBuf,sizeof(stDrls.taxorgcode));

		/*原委托日期*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/OriEntrustDate",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.entrustdate,sBuf,sizeof(stDrls.entrustdate));

		/*原交易水号*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/OriTraNo",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.trano,sBuf,sizeof(stDrls.trano));

		/*原税票号码*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/TaxVouNo",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.taxvouno,sBuf,sizeof(stDrls.taxvouno));

		/*交易金额*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/TraAmt",i);
		COMP_SOFTGETXML(sNode,sBuf);
		stDrls.jyje=atof(sBuf);

		/*查找交易状态不为“正在处理”的交易*/
		/*add by chenxm 20141105 DCI改造工作*/
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT distinct zwrq,xym,jyzt from tips_drls "
			"where taxorgcode='%s' and entrustdate='%s' "
				"and trano ='%s' and taxvouno='%s' and jyje = %0.2f ",
				stDrls.taxorgcode,stDrls.entrustdate,stDrls.trano,stDrls.taxvouno,stDrls.jyje);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		iSqlRet = DBSelectToMultiVar(sErrmsg, sSql1, stDrls.zwrq,stDrls.xym,stDrls.jyzt);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			fclose(fp);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24377, Fmtmsg("查询当日流水表失败"));
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle));
		}
		/*add end by chenxm */
		/*EXEC SQL SELECT distinct zwrq,xym,jyzt 
		INTO :stDrls.zwrq,:stDrls.xym,:stDrls.jyzt 
		FROM tips_drls 
		WHERE taxorgcode=:stDrls.taxorgcode 
		AND entrustdate=:stDrls.entrustdate 
		AND trano=:stDrls.trano 
		AND taxvouno=:stDrls.taxvouno
		AND jyje=:stDrls.jyje ;        
		SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
		if ( SQLERR )
		{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24377, Fmtmsg("查询当日流水表失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle));
		} 
		if ( SQLNOTFOUND_TIPS )*/
		if(iSqlRet == 0)
		{
			iFail++;
			LOG(LM_DEBUG,Fmtmsg("银行端无此交易,征收机关代码[%s],委托日期[%s],交易流水号[%s],税票号码[%s],交易金额[%.2f]",
						stDrls.taxorgcode, stDrls.entrustdate, stDrls.trano, stDrls.taxvouno, stDrls.jyje),fpub_GetCompname(lXmlhandle));
			pstrcopy(stDrls.xym, "24020", sizeof(stDrls.xym));
			pstrcopy(sJyzt, "银行端无此交易", sizeof(sJyzt));
		
		}
		
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/BankNo",stDrls.paybkcode);
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/TaxVouNo",stDrls.taxvouno);
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/OriTaxOrgCode",stDrls.taxorgcode);
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/OriEntrustDate",stDrls.entrustdate);
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/OriTraNo",stDrls.trano);
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/TaxDate",stDrls.zwrq);
		if(stDrls.jyzt[0]=='9')
		{
			iFail++;
			/*更新原交易状态为失败*/
			iSqlRet = DCIBegin();
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				return COMPRET_FAIL;
			}
  		
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_drls  SET jyzt='1',xym='94999',xyxx='银行端缴款处理过期' "
				"where taxorgcode='%s' "
					"and entrustdate='%s' and trano='%s' and taxvouno='%s' and jyje=%0.2f and jyzt='9'",
					stDrls.taxorgcode,stDrls.entrustdate,stDrls.trano,stDrls.taxvouno,stDrls.jyje);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
			iSqlRet = DCIExecuteDirect(sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
  		
				fclose(fp);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
				fpub_SetMsg(lXmlhandle, 24378, Fmtmsg("更新当日流水表失败"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle));
			}
  		
			/*EXEC SQL UPDATE tips_drls 
			  SET jyzt='1',
			  xym='94999',
			  xyxx='银行端缴款处理过期'
			  WHERE taxorgcode=:stDrls.taxorgcode 
			  AND entrustdate=:stDrls.entrustdate 
			  AND trano=:stDrls.trano 
			  AND taxvouno=:stDrls.taxvouno
			  AND jyje=:stDrls.jyje  
			  AND jyzt='9';            
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )
			  {
			  fclose(fp);
			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			  fpub_SetMsg(lXmlhandle, 24378, Fmtmsg("更新当日流水表失败"));
			  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle));
			  }
			  EXEC SQL commit ;*/
			iSqlRet=DCICommit(); 
			/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释   		
			if ( iSqlRet < 0 )
    	{
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    	}
    	*/
			pstrcopy(stDrls.xym, "24020", sizeof(stDrls.xym));
			pstrcopy(sJyzt, "用户申报后未确认扣款", sizeof(sJyzt));
		}else if(stDrls.jyzt[0]=='0')
		{
			iSucc++;
			pstrcopy(sJyzt, "成功的交易", sizeof(sJyzt));
		}else if(stDrls.jyzt[0]=='1')
		{       	    
			iSucc++;
			pstrcopy(sJyzt, "失败的交易", sizeof(sJyzt));
		}else
		{
			iSucc++;
			pstrcopy(sJyzt, "已经冲正的交易", sizeof(sJyzt));
		}
		
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/Result",stDrls.xym);
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/AddWord",sJyzt);
		/* 调补发流程 */
		if ( fpub_CallFlow(lXmlhandle,sYhjkbfFlow) != MID_SYS_SUCC)
		{
			LOG(LM_STD,Fmtmsg("  -->Call子流程失败,请检查[%s]",sYhjkbfFlow),fpub_GetCompname(lXmlhandle));
			memset(sJyzt, 0x00, sizeof(sJyzt));
			strcpy(sJyzt,"交易发送失败");
		}	
		fprintf(fp,"%-17.17s%-17.17s%-13.13s%-15.15s%-18.18s%8.2f   %-14.14s\n",
				stDrls.paybkcode,stDrls.taxorgcode,stDrls.entrustdate,
				stDrls.trano,stDrls.taxvouno,stDrls.jyje,sJyzt);
		}
		fclose(fp);
		LOG(LM_DEBUG,Fmtmsg("一共收到[%d]笔，成功转发[%d]笔，[%d]笔没找到或处于处理状态",
					iCurPackNum,iSucc,iFail), fpub_GetCompname(lXmlhandle));      	 
		fpub_SetMsg(lXmlhandle, 0, "银行端缴款信息核对结束");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
		return COMPRET_SUCC;
}
/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_HXDZ
  组件名称: 与核心对账

  组件功能: 
  与核心对账
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
  发布日期: 2009年02月27日
  修改日期: modify by chenxm 20141112 DCI改造工作
  修改日期: 20141220DCI改造，已测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_HXDZ(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	int iCount;
	int iCount2;
	char sDzrq[8+1];/* 对账日期 */
	char sPrevDate[8+1];/* 对账起始日 */
	SDB_TIPS_HXDZMX stDetail;
	/*BANKDetail stDetail;*/
	SDB_TIPS_DRLS stDrls;
	SDB_TIPS_SSPLKSFMX stPlksfmx;
	SDB_TIPS_DZBPDJ stDzbpdj;         
	double dBkdamt = 0.00; /* TIPS前置多金额 add 20140901 */
	SDB_TIPS_DZJGXX stDzjgxx;  /*  add 20140901 */
	
	char sChkAcctOrd[4+1];/* 对账批次 add 20140901 */
	/*EXEC SQL END   DECLARE SECTION;*/
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	char cCount[16+1];
	char cBkdamt[32+1];

	char sBuf[256];
	int i;
	int iRet=0;
	int iFlag=0;
	int iSqlRet = -1;
	char sMxFileName[256];
	char sLine[1024];
	char sResIcxp[256];
	int iQzdnum = 0;     /*前置多的记录数*/
	int iZjdnum = 0;    /*主机多的记录数*/ 

	/* add 20140901 */
	double dQzdamt =0.00; /*前置多金额 */
	int iZjnum = 0;   /* 核心总笔数 */
	double dZjamt = 0.00; /* 核心总金额 */
	int iQznum = 0; /* TIPS前置总笔数 */
	double dQzamt = 0.00; /* TIPS前置总金额 */    
	/* end add 20140901 */   
	FILE *fp;
	CURSOR cur;
	CURSOR cur1;
	char sIsHxPlDz[1+1];/* add by tuql 20090910 核心批量对账标志 */

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(4);
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
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPrevDate, 0x00, sizeof(sPrevDate));
	COMP_GETPARSEPARAS(4, sBuf, "对账起始日期")
		pstrcopy(sPrevDate, sBuf, sizeof(sPrevDate));
	trim(sPrevDate);    

	LOG(LM_STD,Fmtmsg("与核心对账开始处理..."),fpub_GetCompname(lXmlhandle))  
		LOG(LM_STD,Fmtmsg("对账日期[%s],对账超始日[%s],对账明细文件[%s],明细文件ICXP配置[%s]",
					sDzrq, sPrevDate, sMxFileName, sResIcxp),fpub_GetCompname(lXmlhandle))  

	/* add by tuql 20090910 核心批量对账标志 */
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sIsHxPlDz, 0x00, sizeof(sIsHxPlDz));
	COMP_SOFTGETXML("/tips/ishxpldz", sBuf)
		sIsHxPlDz[0] = sBuf[0];
	if (sIsHxPlDz[0]=='\0')
		sIsHxPlDz[0]='1';
	LOG(LM_STD,Fmtmsg("是否参加与核心批量对账[%s]:0-否,1-是", sIsHxPlDz),fpub_GetCompname(lXmlhandle))     

		//add by chenxm 20141112 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1) \
		WHERE zwrq <= '%s' AND zwrq >= '%s' AND msgno in ('3001', '1008')", sDzrq, sPrevDate);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect(sSql1);
	//add end 

	/*EXEC SQL UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1)
	  WHERE zwrq <= :sDzrq
	  AND zwrq >= :sPrevDate
	  AND msgno in ('3001', '1008');*/
	/* mod by tuql 20091112 AND jyzt = '0'; 
	   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	   if ( SQLERR )*/
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
				fpub_GetCompname(lXmlhandle))        
	}           

	//add by chenxm 20141112 DCI改造工作
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7) \
		WHERE zwrq <= '%s' AND zwrq >= '%s'", sDzrq, sPrevDate);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect(sSql1);
	//add end

	/*EXEC SQL UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7)
	  WHERE zwrq <= :sDzrq
	  AND zwrq >= :sPrevDate;*/
	/* mod by tuql 20091112 AND czbd = '7'; 
	   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	   if ( SQLERR )*/
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量扣税费明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量扣税费明细表失败"),
				fpub_GetCompname(lXmlhandle))        
	}
  LOG(LM_STD,Fmtmsg("打开核心对账文件"),"INFO")
	/*先建打开明细文件,校验*/
	fp = fopen(sMxFileName,"r");
	if ( fp == NULL )
	{
		fpub_SetMsg(lXmlhandle, 24422, "打开核心对账文件失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("打开核心对账文件失败[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle))
	}

	/*文件体处理*/
	for (iFlag=0,i=1; ;i++)
	{   	
		memset(sLine,0x00,sizeof(sLine)); 
		memset(sBuf, 0x00, sizeof(sBuf)); 

		COMP_SOFTSETXML("/tips/hxdz/dzlx", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/zjrq", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/zjlsh", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/zcyhzh", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/jyje", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/qzrq", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/qzlsh", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/jydqdh", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/jyjgdh", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/czbz", sBuf)
    COMP_SOFTSETXML("/tips/hxdz/jydm", sBuf)
		
		
		if (fgets(sLine,sizeof(sLine),fp) == NULL)
				break;                   /*文件结束 跳出*/
		sLine[strlen(sLine)-1]=0;   /* 去除最后一个换行符 */
		trim(sLine);
		/*
		   if ( i==1 || strlen(sLine)<30 )
		   continue;               遇到对帐文件开头,跳过 */
		if (strcmp(sLine,"END") == 0 )
		   break;                  /* 遇到对帐文件结束符*/
		LOG(LM_STD,Fmtmsg("读入第[%d]条明细",i),"INFO")		
		LOG(LM_STD,Fmtmsg("第[%d]条明细：[%s]",i,sLine),"INFO")	
		iRet=SBATCH_FuncICXPUPKG(lXmlhandle,sResIcxp,sLine,strlen(sLine));
		if (iRet < 0)
		{ 
			iFlag = -1; 
			break; 
		}		
		LOG(LM_STD,Fmtmsg("成功解析第[%d]条明细",i),"INFO")		
		
		memset(&stDetail, 0x00, sizeof(stDetail));
    /* 对账类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/dzlx", sBuf)
    stDetail.dzlx[0]=sBuf[0];
    /* 主机日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/zjrq", sBuf)
    pstrcopy(stDetail.zjrq, sBuf, sizeof(stDetail.zjrq));
    /* 主机流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/zjlsh", sBuf)
    pstrcopy(stDetail.zjlsh, sBuf, sizeof(stDetail.zjlsh));
    /* 转出银行帐号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/zcyhzh", sBuf)
    pstrcopy(stDetail.zcyhzh, sBuf, sizeof(stDetail.zcyhzh));
    /* 交易金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jyje", sBuf)
    stDetail.jyje=atof(sBuf);
    /* 前置日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/qzrq", sBuf)
    pstrcopy(stDetail.qzrq, sBuf, sizeof(stDetail.qzrq));
    /* 前置流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/qzlsh", sBuf)
    stDetail.qzlsh=atoi(sBuf);
    /* 交易地区代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jydqdh", sBuf)
    pstrcopy(stDetail.jydqdh, sBuf, sizeof(stDetail.jydqdh));
    /* 交易机构代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jyjgdh", sBuf)
    pstrcopy(stDetail.jyjgdh, sBuf, sizeof(stDetail.jyjgdh));
    /* 冲正标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/czbz", sBuf)
    stDetail.czbz[0]=sBuf[0];
    /* 交易代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jydm", sBuf)
    pstrcopy(stDetail.jydm, sBuf, sizeof(stDetail.jydm));
		
		/* 核心流水入库 add 20141107 自行根据需求确定核心流水是否入库 */  
		iCount=0;
		/* add dci 20141210 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_hxdzmx "
    	"where QZRQ='%s' and QZLSH=%d",sDzrq,stDetail.qzlsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")    
               
        fpub_SetMsg(lXmlhandle, 24201, "查询当日流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    if( iCount > 0)
    {
    	LOG(LM_STD,Fmtmsg("核心流水已存在，跳过本条！对账日期[%s],前置流水号[%d]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
      ;
    }   
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_hxdzmx", SD_TIPS_HXDZMX, NUMELE(SD_TIPS_HXDZMX), &stDetail, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      LOG(LM_STD,Fmtmsg("插入核心对帐结果失败,对账日期[%s],前置流水号[%s]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
    	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("插入核心对帐结果失败"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入核心对帐结果失败"), 
        fpub_GetCompname(lXmlhandle));
    } 
		/* end add dci */
		 
		/* mod dci 20141210    
    EXEC SQL SELECT count(*) INTO :iCount
    	from tips_hxdzmx where QZRQ=:sDzrq and QZLSH=:stDetail.qzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
    	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("查询主机对账登记表记录失败"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询主机对账登记表记录失败"), 
        fpub_GetCompname(lXmlhandle));
    }
    LOG(LM_STD,Fmtmsg("tips-test44,sLine[%s],",
        sLine),"ERROR") 
    if( iCount > 0)
    {
    	LOG(LM_STD,Fmtmsg("核心流水已存在，跳过本条！对账日期[%s],前置流水号[%d]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
      ;
    }    		
    LOG(LM_STD,Fmtmsg("tips-test5,sLine[%s],",
        sLine),"ERROR") 
		EXEC SQL INSERT INTO tips_hxdzmx values(:stDetail);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
     	LOG(LM_STD,Fmtmsg("插入核心对帐结果失败,对账日期[%s],前置流水号[%s]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
    	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("插入核心对帐结果失败"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入核心对帐结果失败"), 
        fpub_GetCompname(lXmlhandle));
     
    }	
    */
		
		/*如果此记录为批量,不参与对账 add by tuql 20091222 
		  if( stDetail.dzlx[0] =='2' && sIsHxPlDz[0]=='0' )
		  { 
		  LOG(LM_STD,Fmtmsg("此交易为批量交易[%s][%d][%s],不参与对账跳过", 
		  stDetail.qzrq, stDetail.qzlsh, stDetail.dzlx),"ERROR")
		  continue;
		  }*/

		/*如果此记录为冲正,则跳到下一个记录中,即被冲正的记录不参与对账*/
    if( stDetail.czbz[0] =='2' )
    { 
        LOG(LM_STD,Fmtmsg("此交易被冲正[%s][%d][%s],跳过", 
                    stDetail.qzrq, stDetail.qzlsh, stDetail.czbz),"ERROR")
        continue;
    }
		/*对于冲正交易,则查找当日流水表,找不到则找对账登记表,再找不到则插入对账登记表*/
		if(memcmp(stDetail.jydm, "36916", 5) == 0)
		{
			/*从当日流水表中取冲正信息*/
			iCount = 0;

			//add by chenxm 20141112 DCI改造工作
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT COUNT(*) FROM  tips_drls \
				WHERE zwrq= '%s' AND zhqzlsh= '%s' AND msgno ='1021' AND jyzt='0'", \
				stDetail.qzrq, stDetail.qzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
			//add end

			/*EXEC SQL SELECT COUNT(*) INTO :iCount 
			  FROM  tips_drls
			  WHERE zwrq=:stDetail.qzrq
			  AND zhqzlsh=:stDetail.qzlsh
			  AND msgno ='1021'
			  AND jyzt='0';
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )*/
			if(iSqlRet < 0)
			{        
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("查找当日流水表冲正记录失败,帐务日期[%s],前置流水号[%d]", 
							stDetail.qzrq, stDetail.qzlsh),"ERROR")   
					iFlag = -3;
				break;	
			}
			/* 如在当日流水表中找不到 */
			if ( iCount == 0 )
			{
				/*从调账表取冲正信息tips_dzbpdj*/
				iCount2 = 0;

				//add by chenxm 20141112 DCI改造工作
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT COUNT(*) FROM  tips_dzbpdj \
					WHERE clrq= '%s' AND cllsh= '%s' AND clzt='5'", stDetail.qzrq, stDetail.qzlsh);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
				iSqlRet = DBSelectToVar(sErrmsg, &iCount2, sSql1);
				//add end

				/*EXEC SQL SELECT COUNT(*) INTO :iCount2
				  FROM  tips_dzbpdj
				  WHERE clrq=:stDetail.qzrq
				  AND cllsh=:stDetail.qzlsh
				  AND clzt='5' */ /*已调账*/;
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
				  if(SQLERR)*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("查找对账不平表冲正记录失败,帐务日期[%s],前置流水号[%d]", 
								stDetail.qzrq, stDetail.qzlsh),"ERROR")   
						iFlag = -5;
					break;
				}
				if ( iCount2 == 0 )
				{
					iZjdnum ++;
					LOG_SSTIPS("3111",Fmtmsg("-->主机冲正多,前置无：前置日期[%s],前置流水[%d],主机日期[%s],主机流水[%s],帐号[%s],金额[%.2f],解决办法：主机为准,查原因",
								stDetail.qzrq,stDetail.qzlsh,stDetail.zjrq,stDetail.zjlsh,stDetail.zcyhzh,stDetail.jyje),"HXDZ",sDzrq);
					memset(&stDzbpdj, 0, sizeof(stDzbpdj));
					pstrcopy(stDzbpdj.zwrq, stDetail.qzrq, sizeof(stDzbpdj.zwrq));
					stDzbpdj.zhqzlsh = stDetail.qzlsh;
					stDzbpdj.dzlx[0]='1';
					pstrcopy(stDzbpdj.zjlsh, stDetail.zjlsh, sizeof(stDzbpdj.zjlsh));
					pstrcopy(stDzbpdj.paybkcode, "", sizeof(stDzbpdj.paybkcode));
					pstrcopy(stDzbpdj.chkdate, sDzrq, sizeof(stDzbpdj.chkdate));
					pstrcopy(stDzbpdj.chkacctord, "", sizeof(stDzbpdj.chkacctord));
					pstrcopy(stDzbpdj.jyrq, stDetail.qzrq, sizeof(stDzbpdj.jyrq));
					pstrcopy(stDzbpdj.jymc, "主机冲正交易", sizeof(stDzbpdj.jymc));
					pstrcopy(stDzbpdj.jyzh, stDetail.zcyhzh, sizeof(stDzbpdj.jyzh));
					stDzbpdj.jyje = stDetail.jyje;
					pstrcopy(stDzbpdj.reason_info, "前置<->主机;主机冲正多", sizeof(stDzbpdj.reason_info));
					pstrcopy(stDzbpdj.dzjg, "39", sizeof(stDzbpdj.dzjg));
					stDzbpdj.clzt[0]='0';
					pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
					pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
					stDzbpdj.cllsh = 0;
					pstrcopy(stDzbpdj.kzbz, "00000000", sizeof(stDzbpdj.kzbz));
					pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
					pstrcopy(stDzbpdj.dqdh, stDetail.jydqdh, sizeof(stDzbpdj.dqdh));
          pstrcopy(stDzbpdj.jgdh, stDetail.jyjgdh, sizeof(stDzbpdj.jgdh));
          pstrcopy(stDzbpdj.jygy, "", sizeof(stDzbpdj.jygy));
          pstrcopy(stDzbpdj.zddh, "", sizeof(stDzbpdj.zddh));
         
					iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj,sErrmsg);                    
					/*EXEC SQL INSERT INTO tips_dzbpdj values(:stDzbpdj);
					  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
					  if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("插入对帐登记表失败,帐务日期[%s],前置流水号[%d]", 
									stDetail.qzrq, stDetail.qzlsh),"ERROR")   
							iFlag = -7;
						break;  	  			  	
					}    	  	    	
				}/* if ( iCount2 == 0 )冲正交易，在对账登记表中找不到 */                
			}/* if ( iCount == 0 )冲正交易，在当日流水表中找不到 */
		}/* if(memcmp(stDetail.jydm, "", 4) == 0)如果是冲正交易*/
		else/* 正常交易 */
		{
			LOG(LM_DEBUG,Fmtmsg("HXDZ：前置日期[%s],前置流水[%d],主机日期[%s],主机流水[%s],帐号[%s],金额[%.2f]",
								stDetail.qzrq,stDetail.qzlsh,stDetail.zjrq,stDetail.zjlsh,stDetail.zcyhzh,stDetail.jyje),"INFO")      
			/* add 20140901 */
			iZjnum ++;
			dZjamt = dZjamt + stDetail.jyje;  /* 核心明细对账总金额 */
			/* end add 20140901 */
			
			/*从当日流水表中取帐务日期及前置流水号相同的记录*/
			//add by chenxm 20141112 DCI改造工作
			memset(sSql1, 0x00, sizeof(sSql1));
			LOG(LM_DEBUG,Fmtmsg("qzrq[%s]qzlsh[%d]jyje[%0.2f]...",stDetail.qzrq, stDetail.qzlsh,stDetail.jyje),"INFO") 
			sprintf(sSql1, "UPDATE tips_drls SET dzbz='1'||substr(dzbz,2,1) WHERE zwrq= '%s' "
					"AND zhqzlsh= %d AND  jyzt='0' AND  msgno in ('3001','1008') AND  jyje= %0.2f", 
					stDetail.qzrq, stDetail.qzlsh,stDetail.jyje);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  		
			iSqlRet = DCIExecuteDirect(sSql1);
			//add end

			/*EXEC SQL UPDATE tips_drls 
			  SET dzbz='1'||substr(dzbz,2,1)
			  WHERE  zwrq=:stDetail.qzrq
			  AND  zhqzlsh=:stDetail.qzlsh
			  AND  jyzt='0'
			  AND  msgno in ('3001','1008')
			  AND  jyje=:stDetail.jyje */
			/* AND  dzbz[1]='0' mod by tuql 20090508 ;
			   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
			   if(SQLERR)*/
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("更新当日流水表失败,帐务日期[%s],前置流水号[%d]", 
							stDetail.qzrq, stDetail.qzlsh),"ERROR")   
					iFlag = -9;
				break;
			}            
			/*如果找不到，则从批量扣税费明细表中取帐务日期及前置流水号相同的记录*/
			//if( SQLNOTFOUND_TIPS ) 
			if(iSqlRet == 0)
			{   
				//add by chenxm 20141112 DCI改造工作
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='1'||substr(kzbz,2,7) WHERE zwrq= '%s' "
						"AND plmxxh= %d AND czbd='7' AND jyje= %0.2f", stDetail.qzrq, stDetail.qzlsh,stDetail.jyje);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
				iSqlRet = DCIExecuteDirect(sSql1);
				//add end

				/*EXEC SQL UPDATE tips_ssplksfmx 
				  SET kzbz='1'||substr(kzbz,2,7)
				  WHERE  zwrq=:stDetail.qzrq
				  AND  plmxxh=:stDetail.qzlsh
				  AND  czbd='7'*/
				/* AND  kzbz[1]='0' mod by tuql 20090508 */
				/*AND  jyje=:stDetail.jyje;
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
				  if(SQLERR)*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("更新批量扣税费明细表失败,帐务日期[%s],前置流水号[%d]", 
								stDetail.qzrq, stDetail.qzlsh),"ERROR")   
						iFlag = -11;
					break;
				}
				/*没有找到的记录记到对帐不符表*/
				//if(SQLNOTFOUND_TIPS)
				if(iSqlRet == 0)
				{
					iZjdnum ++;

					LOG_SSTIPS("3111",Fmtmsg("-->主机多,前置无：前置日期[%s],前置流水[%d],主机日期[%s],主机流水[%s],帐号[%s],金额[%.2f],解决办法：主机为准,查原因",
								stDetail.qzrq,stDetail.qzlsh,stDetail.zjrq,stDetail.zjlsh,stDetail.zcyhzh,stDetail.jyje),"HXDZ",sDzrq);
					memset(&stDzbpdj, 0, sizeof(stDzbpdj));
					pstrcopy(stDzbpdj.zwrq, stDetail.qzrq, sizeof(stDzbpdj.zwrq));
					stDzbpdj.zhqzlsh = stDetail.qzlsh;
					/******begin add by tuql 20091009 增加查询tips_drls及tips_ssplksfmx两表并赋值 ******/
					memset(&stDrls, 0x00, sizeof(stDrls));
					memset(sSql1, 0x00, sizeof(sSql1));
					sprintf(sSql1, "SELECT * FROM tips_drls \
						WHERE zwrq='%s' AND  zhqzlsh=%d AND  msgno in ('3001', '1008')", stDetail.qzrq, stDetail.qzlsh);
					LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
					iSqlRet = prv_SelMulToStruct( &sSql1, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls);
					/*iSqlRet = DBSelectToMultiVar(sErrmsg, sSql1, &stDrls);*/

					/*EXEC SQL SELECT * INTO :stDrls 
					  FROM tips_drls
					  WHERE zwrq=:stDetail.qzrq
					  AND  zhqzlsh=:stDetail.qzlsh
					  AND  msgno in ('3001', '1008');   */        /* 报文编号 3001实扣 1008银缴 */
					/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
					  if ( SQLERR )*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("查询当日流水表失败,帐务日期[%s],前置流水号[%d]", 
									stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle)) 
							iFlag = -32;
						break;
					}
					//if( SQLNOTFOUND_TIPS )/* 在当日流水中找不到 */
					if(iSqlRet == 0)
					{
						memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
						memset(sSql1, 0x00, sizeof(sSql1));
						sprintf(sSql1, "SELECT * FROM tips_ssplksfmx WHERE zwrq='%s' AND plmxxh=%d ", \
							stDetail.qzrq, stDetail.qzlsh);
						LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
						iSqlRet = prv_SelMulToStruct( &sSql1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
						/*iSqlRet = DBSelectToMultiVar(sErrmsg, sSql1, &stDrls);*/

						/*EXEC SQL SELECT * INTO :stPlksfmx
						  FROM tips_ssplksfmx
						  WHERE  zwrq=:stDetail.qzrq
						  AND  plmxxh=:stDetail.qzlsh;  */                       
						/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
						  if ( SQLERR )*/
						if(iSqlRet < 0)
						{
							LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

							LOG(LM_STD,Fmtmsg("查询批量扣税费明细表失败,帐务日期[%s],前置流水号[%d]", 
										stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle))
								iFlag = -33;
							break;
						}
						/*if( SQLNOTFOUND_TIPS )*//* 在批量明细表中找不到,什么都不做 */
						if(iSqlRet == 0)
						{
							;
						}
						else
						{
							/******begin add by tuql 20091112 增加更新tips_drls及tips_ssplksfmx两表 ******/ 
							memset(sSql1, 0x00, sizeof(sSql1));
							sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='3'||substr(kzbz,2,7) \
								WHERE zwrq='%s' AND plmxxh=%d ", stDetail.qzrq, stDetail.qzlsh);
							LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
							iSqlRet = DCIExecuteDirect(sSql1);

							/*EXEC SQL UPDATE tips_ssplksfmx 
							  SET kzbz='3'||substr(kzbz,2,7)
							  WHERE  zwrq=:stDetail.qzrq
							  AND  plmxxh=:stDetail.qzlsh;
							  if ( SQLERR )*/
							if(iSqlRet < 0)
							{
								LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

								LOG(LM_STD,Fmtmsg("更新批量扣税费明细表失败,帐务日期[%s],前置流水号[%d]", 
											stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle))
									iFlag = -35;
								break;
							}                               
							/******end add by tuql 20091112 增加更新tips_drls及tips_ssplksfmx两表 ******/
							pstrcopy(stDzbpdj.zwrq, stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));/* 帐务日期 */
							stDzbpdj.zhqzlsh = stPlksfmx.plmxxh ;
							pstrcopy(stDzbpdj.workdate, stPlksfmx.workdate, sizeof(stDzbpdj.workdate));/* 工作日期 */
							pstrcopy(stDzbpdj.chkdate, stPlksfmx.workdate, sizeof(stDzbpdj.chkdate));/* 对账日期 */
							pstrcopy(stDzbpdj.paybkcode, stPlksfmx.paybkcode, sizeof(stDzbpdj.paybkcode));/* 付款行行号 */
							pstrcopy(stDzbpdj.payeebankno, stPlksfmx.payeebankno, sizeof(stDzbpdj.payeebankno));/* 清算国库行号 */
							pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));/* 地区代号 */
							pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));/* 机构代号 */
							pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));/* 交易柜员 */
							pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));/* 终端代号 */
							pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));/* 主机流水号 */
							pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));/* 贷方帐号 */
							pstrcopy(stDzbpdj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stDzbpdj.taxorgcode));/* 征收机关代码 */
							pstrcopy(stDzbpdj.entrustdate, stPlksfmx.entrustdate, sizeof(stDzbpdj.entrustdate));/* 委托日期 */
							pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));/* 交易流水号 */
							pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));/* 交易代码 */
							pstrcopy(stDzbpdj.khmc, stPlksfmx.handorgname, sizeof(stDzbpdj.khmc));/* 缴款单位名称 */

						}                
					}
					else
					{
						/******begin add by tuql 20091112 增加更新tips_drls及tips_ssplksfmx两表 ******/ 
						memset(sSql1, 0x00, sizeof(sSql1));
						sprintf(sSql1, "UPDATE tips_drls SET dzbz='3'||substr(dzbz,2,1) \
							WHERE zwrq='%s' AND zhqzlsh=%d AND  msgno in ('3001','1008')", \
							stDetail.qzrq, stDetail.qzlsh);
						LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
						iSqlRet = DCIExecuteDirect(sSql1);

						/*EXEC SQL UPDATE tips_drls 
						  SET dzbz='3'||substr(dzbz,2,1)
						  WHERE  zwrq=:stDetail.qzrq
						  AND  zhqzlsh=:stDetail.qzlsh
						  AND  msgno in ('3001','1008');*/
						//if ( SQLERR )
						if(iSqlRet < 0)
						{
							LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
							
							LOG(LM_STD,Fmtmsg("更新当日流水表失败,帐务日期[%s],前置流水号[%d]", 
										stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle)) 
								iFlag = -34;
							break;
						}                               
						/******end add by tuql 20091112 增加更新tips_drls及tips_ssplksfmx两表 ******/       
						pstrcopy(stDzbpdj.zwrq, stDrls.zwrq, sizeof(stDzbpdj.zwrq));/* 帐务日期 */
						stDzbpdj.zhqzlsh = stDrls.zhqzlsh ;
						pstrcopy(stDzbpdj.workdate, stDrls.workdate, sizeof(stDzbpdj.workdate));/* 工作日期 */
						pstrcopy(stDzbpdj.chkdate, stDrls.workdate, sizeof(stDzbpdj.chkdate));/* 对账日期 */
						pstrcopy(stDzbpdj.paybkcode, stDrls.paybkcode, sizeof(stDzbpdj.paybkcode));/* 付款行行号 */
						pstrcopy(stDzbpdj.payeebankno, stDrls.payeebankno, sizeof(stDzbpdj.payeebankno));/* 清算国库行号 */
						pstrcopy(stDzbpdj.dqdh, stDrls.dqdh, sizeof(stDzbpdj.dqdh));/* 地区代号 */
						pstrcopy(stDzbpdj.jgdh, stDrls.jgdh, sizeof(stDzbpdj.jgdh));/* 机构代号 */
						pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));/* 交易柜员 */
						pstrcopy(stDzbpdj.zddh, stDrls.zddh, sizeof(stDzbpdj.zddh));/* 终端代号 */
						pstrcopy(stDzbpdj.zjlsh, stDrls.zjlsh, sizeof(stDzbpdj.zjlsh));/* 主机流水号 */
						pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));/* 贷方帐号 */                    
						pstrcopy(stDzbpdj.taxorgcode, stDrls.taxorgcode, sizeof(stDzbpdj.taxorgcode));/* 征收机关代码 */
						pstrcopy(stDzbpdj.entrustdate, stDrls.entrustdate, sizeof(stDzbpdj.entrustdate));/* 委托日期 */
						pstrcopy(stDzbpdj.trano, stDrls.trano, sizeof(stDzbpdj.trano));/* 交易流水号 */
						pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDzbpdj.jymc));/* 交易代码 */
						pstrcopy(stDzbpdj.khmc, stDrls.handorgname, sizeof(stDzbpdj.khmc));/* 缴款单位名称 */

						/* add 20140901 */
						iQznum ++;
						dQzamt = dQzamt + stDetail.jyje;  /* tips前置对账总金额 */
						/* end add 20140901 */
					}        
					/******end add by tuql 20091009 增加查询tips_drls及tips_ssplksfmx两表并赋值 ******/ 
					stDzbpdj.dzlx[0]='1';
					pstrcopy(stDzbpdj.zjlsh, stDetail.zjlsh, sizeof(stDzbpdj.zjlsh));
					//pstrcopy(stDzbpdj.zjlsh,stDetail.zjlsh,sizeof(stDzbpdj.zjlsh));
					/* mod by tuql 20091009 将以下信息屏蔽
					   LOG(LM_STD,Fmtmsg("qzlsh[%d]zjlsh[%s]",stDetail.qzlsh,stDetail.zjlsh),"ERROR");
					   pstrcopy(stDzbpdj.paybkcode, "", sizeof(stDzbpdj.paybkcode));
					   pstrcopy(stDzbpdj.chkdate, sDzrq, sizeof(stDzbpdj.chkdate));
					 */
					pstrcopy(stDzbpdj.chkacctord, "", sizeof(stDzbpdj.chkacctord));
					pstrcopy(stDzbpdj.jyrq, stDetail.qzrq, sizeof(stDzbpdj.jyrq));
					/* mod by tuql 20091020 将以下信息屏蔽
					   pstrcopy(stDzbpdj.jymc, "扣款交易", sizeof(stDzbpdj.jymc));
					 */
					pstrcopy(stDzbpdj.jyzh, stDetail.zcyhzh, sizeof(stDzbpdj.jyzh));
					stDzbpdj.jyje = stDetail.jyje;
					pstrcopy(stDzbpdj.reason_info, "前置<->主机;主机多", sizeof(stDzbpdj.reason_info));
					pstrcopy(stDzbpdj.dzjg, "39", sizeof(stDzbpdj.dzjg));
					pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));/* add by tuql 20091020 */
					stDzbpdj.clzt[0]='0';
					pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
					pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
					stDzbpdj.cllsh = 0;
					pstrcopy(stDzbpdj.kzbz, "00000000", sizeof(stDzbpdj.kzbz));
					pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
					/* mod by tuql 20091020 将以下信息屏蔽
					   pstrcopy(stDzbpdj.dqdh, stDetail.jydqdh, sizeof(stDzbpdj.dqdh));
					   pstrcopy(stDzbpdj.jgdh, stDetail.jyjgdh, sizeof(stDzbpdj.jgdh));
					   pstrcopy(stDzbpdj.jygy, "", sizeof(stDzbpdj.jygy));
					   pstrcopy(stDzbpdj.zddh, "", sizeof(stDzbpdj.zddh));
					 */
					iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj,sErrmsg);

					/*EXEC SQL INSERT INTO tips_dzbpdj values(:stDzbpdj);
					  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
					  /if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("插入对帐登记表失败,帐务日期[%s],前置流水号[%d]", 
									stDetail.qzrq, stDetail.qzlsh),"ERROR")   
							iFlag = -13;
						break;
					}
				}
				else
				{	
					/* add 20140901 */
					iQznum ++;
					dQzamt = dQzamt + stDetail.jyje;  /* tips前置对账总金额 */
					/* end add 20140901 */
				}/* 对平批量交易计数 */
			}/* 在当日流水中找不到*/
			else
			{		
				/* add 20140901 */
				iQznum ++;
				dQzamt = dQzamt + stDetail.jyje;  /* tips前置对账总金额 */
				/* end add 20140901 */
			}/* 对平实时交易计数 */
		}/* 正常交易 */                       
	}/* for (iFlag=0,i=1; ;i++)文件体处理*/
	fclose(fp);
	if (iFlag < 0)
	{ 
		fpub_SetMsg(lXmlhandle,24423,Fmtmsg("与银行主机对账失败"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("与银行主机对账失败,ret[%d]..",iFlag),"ERROR");
	}
	/*判断是否还有没有核对的前置流水--前置多*/
	iCount = 0;
	dBkdamt = 0.00; /* add dBkdamt 20140901 */

	//add by chenxm 20141112 DCI改造工作
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, " SELECT COUNT(*),SUM(jyje) FROM  tips_drls WHERE zwrq<= '%s' AND zwrq >= '%s'"
			"AND jyzt='0' AND msgno in ('3001','1008') AND substr(dzbz,1,1) = '0'", sDzrq, sPrevDate);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
	iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cCount, &cBkdamt);
	iCount=atoi(cCount);
	dBkdamt=atof(cBkdamt);
	//add end

	/*EXEC SQL SELECT COUNT(*),SUM(jyje) INTO :iCount,:dBkdamt // add dBkdamt 20140901 //
	  FROM  tips_drls
	  WHERE zwrq <= :sDzrq
	  AND zwrq >= :sPrevDate
	  AND jyzt='0' 
	  AND msgno in ('3001','1008')
	  AND substr(dzbz,1,1) = '0';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if(SQLERR)*/
	if(iSqlRet < 0)
	{ 
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR") 
		
		fpub_SetMsg(lXmlhandle,24424,Fmtmsg("查询当日流水表失败"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询当日流水表失败"),"ERROR");
	}
	if( iCount > 0 )
	{
		iQzdnum = iQzdnum + iCount; /* 前置多计数器++ */
		/* add 20140901 */
		dQzdamt += dBkdamt ;
		/* end add 20140901 */

		/* 把前置多的流水记录登记到对账不平表中去 */
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT * FROM  tips_drls \
			WHERE zwrq <= '%s' AND zwrq >= '%s' AND jyzt='0' AND msgno in ('3001','1008') \
			AND substr(dzbz,1,1) = '0'", sDzrq, sPrevDate);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
		{
			LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		if (DCIExecute(cur) == -1)
		{
			LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
				DCIFreeCursor(cur);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, 24425, Fmtmsg("执行游标失败"));
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
		}
		/*EXEC SQL DECLARE cur_drls_hxdz CURSOR for 
		  SELECT *
		  FROM  tips_drls 
		  WHERE zwrq <= :sDzrq
		  AND zwrq >= :sPrevDate
		  AND jyzt='0'
		  AND msgno in ('3001','1008')
		  AND substr(dzbz,1,1) = '0';
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");

		  EXEC SQL OPEN cur_drls_hxdz;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_drls_hxdz",sqlca.sqlcode),"ERROR");
		  if ( SQLERR )
		  {
		  fpub_SetMsg(lXmlhandle,24425, "打开游标失败");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("HXDZ打开cur_drls_hxdz游标失败"),
		  fpub_GetCompname(lXmlhandle))
		  }         */ 
		/*开始循环*/
		for (i=1,iFlag=0;;i++)
		{
			memset(&stDrls, 0x00, sizeof(stDrls));

			iSqlRet = DBFetch(cur, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls, sErrmsg);
			/*EXEC SQL FETCH cur_drls_hxdz INTO :stDrls;     
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_drls_hxdz",sqlca.sqlcode),"ERROR");
			  if ( SQLERR )*/
			if(iSqlRet < 0)
			{  
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				iFlag=-1;
				LOG(LM_STD,Fmtmsg("HXDZ从cur_drls_hxdz游标获取数据失败"),"ERROR");
				break;
			}
			if(iSqlRet == 0)
				/*if ( SQLNOTFOUND )*/
				break;

			/* add 20140901 */
			dBkdamt = dBkdamt + stDrls.jyje; /*iBkdnum银行多的金额 */
			/* end 20140901 */

			LOG_SSTIPS("3111",Fmtmsg("-->(实时)前置多,主机无：交易日期[%s],前置流水[%d],机构号[%s],帐号[%s],金额[%.2f],解决办法：主机为准,查原因",
						stDrls.zwrq,stDrls.zhqzlsh,stDrls.payopbkcode,stDrls.payacct,stDetail.jyje),"HXDZ",sDzrq);    	  	    	  	
			memset(&stDzbpdj, 0, sizeof(stDzbpdj));
			pstrcopy(stDzbpdj.zwrq, stDrls.zwrq, sizeof(stDzbpdj.zwrq));
			stDzbpdj.zhqzlsh = stDrls.zhqzlsh;
			stDzbpdj.dzlx[0]='1';/* 与主机对账 */
			pstrcopy(stDzbpdj.zjlsh, stDrls.zjlsh, sizeof(stDzbpdj.zjlsh));
			pstrcopy(stDzbpdj.workdate, stDrls.workdate, sizeof(stDzbpdj.workdate));
			pstrcopy(stDzbpdj.taxorgcode, stDrls.taxorgcode, sizeof(stDzbpdj.taxorgcode));
			pstrcopy(stDzbpdj.entrustdate, stDrls.entrustdate, sizeof(stDzbpdj.entrustdate));
			/* mod by tuql 20091009 以下信息应赋值为当日流水表的workdate值
			   pstrcopy(stDzbpdj.chkdate, sDzrq, sizeof(stDzbpdj.chkdate));
			 */
			pstrcopy(stDzbpdj.chkdate, stDrls.workdate, sizeof(stDzbpdj.chkdate));
			/* mod by tuql 20091020 以下信息应赋值为当日流水表的chkacctord值
			   pstrcopy(stDzbpdj.chkacctord, "", sizeof(stDzbpdj.chkacctord));
			 */
			pstrcopy(stDzbpdj.chkacctord, stDrls.chkacctord, sizeof(stDzbpdj.chkacctord));
			pstrcopy(stDzbpdj.trano, stDrls.trano, sizeof(stDzbpdj.trano));
			pstrcopy(stDzbpdj.payeebankno, stDrls.payeebankno, sizeof(stDzbpdj.payeebankno));
			/* mod by tuql 20091009 以下信息应赋值为当日流水表的paybkcode值
			   pstrcopy(stDzbpdj.paybkcode, stDrls.payopbkcode, sizeof(stDzbpdj.paybkcode));  		                
			 */
			pstrcopy(stDzbpdj.paybkcode, stDrls.paybkcode, sizeof(stDzbpdj.paybkcode));  		                
			pstrcopy(stDzbpdj.jyrq, stDrls.jyrq, sizeof(stDzbpdj.jyrq));
			pstrcopy(stDzbpdj.jysj, stDrls.jysj, sizeof(stDzbpdj.jysj));
			pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDzbpdj.jymc));
			pstrcopy(stDzbpdj.khmc, stDrls.handorgname, sizeof(stDzbpdj.khmc));
			pstrcopy(stDzbpdj.jyzh, stDrls.payacct, sizeof(stDzbpdj.jyzh));
			pstrcopy(stDzbpdj.zhzl, stDrls.handletype, sizeof(stDzbpdj.zhzl));
			/* mod by tuql 20091009 以下信息应赋值为当日流水表的dfzh值
			   pstrcopy(stDzbpdj.dfzh, stDrls.payeeacct, sizeof(stDzbpdj.dfzh));
			 */
			pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));
			pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));           
			stDzbpdj.jyje = stDrls.jyje;
			pstrcopy(stDzbpdj.reason_info, "前置<->主机;前置多", sizeof(stDzbpdj.reason_info));
			pstrcopy(stDzbpdj.dzjg, "29", sizeof(stDzbpdj.dzjg));
			stDzbpdj.clzt[0]='0';
			pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
			pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
			stDzbpdj.cllsh = 0;
			pstrcopy(stDzbpdj.kzbz, stDrls.dzbz, sizeof(stDzbpdj.kzbz));
			pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
			pstrcopy(stDzbpdj.dqdh, stDrls.dqdh, sizeof(stDzbpdj.dqdh));
			pstrcopy(stDzbpdj.jgdh, stDrls.jgdh, sizeof(stDzbpdj.jgdh));
			pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));
			pstrcopy(stDzbpdj.zddh, stDrls.zddh, sizeof(stDzbpdj.zddh));

			iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj,sErrmsg);
			/*EXEC SQL INSERT INTO tips_dzbpdj values(:stDzbpdj);
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
			  if(SQLERR) */
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("插入对帐登记表失败,帐务日期[%s],前置流水号[%d]", 
							stDrls.zwrq, stDrls.zhqzlsh),"ERROR")   
					iFlag = -3;
				break;  	  			  	
			}
			/*更新该流水明细状态为前置多*/
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_drls SET dzbz='2'||substr(dzbz,2,1) "
				"WHERE entrustdate='%s' AND taxorgcode='%s' "
					"AND trano='%s' AND jyzt='0' AND substr(dzbz,1,1) = '0'", stDrls.entrustdate, stDrls.taxorgcode, stDrls.trano);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet = DCIExecuteDirect(sSql1);
			/*EXEC SQL UPDATE tips_drls 
			  SET dzbz='2'||substr(dzbz,2,1)
			  WHERE entrustdate=:stDrls.entrustdate
			  AND taxorgcode=:stDrls.taxorgcode
			  AND trano=:stDrls.trano
			  AND jyzt='0'
			  AND substr(dzbz,1,1) = '0';
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
			  if(SQLERR) */
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("更新当日流水表失败,帐务日期[%s],前置流水号[%d]", 
							stDrls.zwrq, stDrls.zhqzlsh),"ERROR")   
					iFlag = -5;
				break; 
			}
		}/* for (i=1,iFlag=0;;i++) */    
		/*EXEC SQL CLOSE cur_drls_hxdz;   */
		DCIFreeCursor(cur);

		if (iFlag < 0)
		{
			fpub_SetMsg(lXmlhandle,24426,"处理与核心对账时单笔前置多的情况失败");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("处理与核心对账时单笔前置多的情况失败iflag=[%d]",iFlag),
					fpub_GetCompname(lXmlhandle))
		}

	}/* if( iCount > 0 )与核心对账前置多的情况 */ 

	/* add by tuql 20090910 判断是否核心批量不参加对账 0-不参加*/
	if (sIsHxPlDz[0]=='0')
	{
		LOG(LM_STD,Fmtmsg("----核心批量没参加对账"),fpub_GetCompname(lXmlhandle))
			/* begin add by tuql 20091112 更新对账标志为平 */

			memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='1'||substr(kzbz,2,7) WHERE zwrq <='%s' AND zwrq >='%s' "
				"AND czbd='7' AND substr(kzbz,1,1)='0' ", sDzrq, sPrevDate);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		iSqlRet = DCIExecuteDirect(sSql1);
		/*EXEC SQL UPDATE tips_ssplksfmx
		  SET kzbz='1'||substr(kzbz,2,7)
		  WHERE zwrq <= :sDzrq
		  AND zwrq >= :sPrevDate
		  AND czbd='7'
		  AND substr(kzbz,1,1)='0';           
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
		  if(SQLERR) */ 
		if(iSqlRet < 0)
		{ 
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			fpub_SetMsg(lXmlhandle,24424,Fmtmsg("更新批量扣税费表失败"));
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询批量扣税费表失败"),"ERROR");
		}
		/* end add by tuql 20091112 更新对账标志为平 */
		LOG(LM_DEBUG,Fmtmsg("与核心主机对账结束,主机多[%d]笔, 前置多[%d]笔", 
					iZjdnum, iQzdnum), fpub_GetCompname(lXmlhandle));
		fpub_SetMsg(lXmlhandle, 0, "与核心主机对账结束");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
		return COMPRET_SUCC;        
	}    

	/*判断是否还有没有核对的前置批量交易流水*/
	iCount = 0;
	dBkdamt = 0.00; /*add dBkdamt 20140901 */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT COUNT(*),SUM(jyje) FROM tips_ssplksfmx WHERE zwrq <='%s' AND zwrq >='%s' "
			"AND czbd='7' AND substr(kzbz,1,1)='0' ", sDzrq, sPrevDate);
	
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
	iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cCount, &cBkdamt);
	iCount=atoi(cCount);
	dBkdamt=atof(cBkdamt);
	/*EXEC SQL SELECT COUNT(*),SUM(jyje) INTO :iCount,:dBkdamt //add dBkdamt 20140901 //
	  FROM tips_ssplksfmx
	  WHERE zwrq <= :sDzrq
	  AND zwrq >= :sPrevDate
	  AND czbd='7'
	  AND substr(kzbz,1,1)='0';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if(SQLERR) */
	if(iSqlRet < 0)
	{ 
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle,24424,Fmtmsg("查询批量扣税费表失败"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询批量扣税费表失败"),"ERROR");
	}
	if( iCount > 0 )
	{
		iQzdnum = iQzdnum + iCount; /* 前置多计数器++ */
		/* add 20140901 */        
		dQzdamt += dBkdamt ;
		/* end add 20140901 */

		/* 把前置多的流水记录登记到对账不平表中去 */
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT * FROM  tips_ssplksfmx where zwrq <='%s' and zwrq >='%s' "
				"AND czbd='7' AND substr(kzbz,1,1)='0'",sDzrq, sPrevDate);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
		{
			LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		if (DCIExecute(cur1) == -1)
		{
			LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
				DCIFreeCursor(cur1);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, 24425, Fmtmsg("执行游标失败"));
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
		}

		/*EXEC SQL DECLARE cur_plksfmx_hxdz CURSOR for 
		  SELECT *
		  FROM  tips_ssplksfmx
		  WHERE zwrq <= :sDzrq
		  AND zwrq >= :sPrevDate
		  AND czbd='7'
		  AND substr(kzbz,1,1)='0';
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
		  EXEC SQL OPEN cur_plksfmx_hxdz;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_plksfmx_hxdz",sqlca.sqlcode),"ERROR");
		  if ( SQLERR )
		  {
		  fpub_SetMsg(lXmlhandle,24425, "打开游标失败");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("HXDZ打开cur_plksfmx_hxdz游标失败"),
		  fpub_GetCompname(lXmlhandle))
		  }*/

		/*开始循环*/
		for (i=1,iFlag=0;;i++)
		{
			memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
			/*EXEC SQL FETCH cur_plksfmx_hxdz INTO :stPlksfmx;   
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_plksfmx_hxdz",sqlca.sqlcode),"ERROR");
			  if ( SQLERR )*/
			iSqlRet = DBFetch(cur1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);	
			if(iSqlRet < 0)
			{  
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				iFlag=-1;
				LOG(LM_STD,Fmtmsg("HXDZ从cur_plksfmx_hxdz游标获取数据失败"),"ERROR");
				break;
			}
			/*if ( SQLNOTFOUND )*/
			if(iSqlRet == 0)
				break;
			LOG_SSTIPS("3111",Fmtmsg("-->(批量)前置多,主机无：交易日期[%s],前置流水[%d],国库日期[%s],批次[%s],流水号[%s],机构号[%s],帐号[%s],金额[%.2f],解决办法：主机为准,查原因",
						stPlksfmx.zwrq,stPlksfmx.plmxxh,stPlksfmx.entrustdate,stPlksfmx.packno,
						stPlksfmx.trano,stPlksfmx.payopbkcode,stPlksfmx.payacct,stPlksfmx.jyje),"HXDZ",sDzrq);
			memset(&stDzbpdj, 0, sizeof(stDzbpdj));
			pstrcopy(stDzbpdj.zwrq, stPlksfmx.zwrq, sizeof(stPlksfmx.zwrq));
			stDzbpdj.zhqzlsh = stPlksfmx.plmxxh;
			pstrcopy(stDzbpdj.zjlsh,stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));
			stDzbpdj.dzlx[0]='1';
			pstrcopy(stDzbpdj.workdate, stPlksfmx.workdate, sizeof(stDzbpdj.workdate));
			pstrcopy(stDzbpdj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stDzbpdj.taxorgcode));
			pstrcopy(stDzbpdj.entrustdate, stPlksfmx.entrustdate, sizeof(stDzbpdj.entrustdate));
			/* mod by tuql 20091009 以下信息应赋值为批量明细表的workdate值
			   pstrcopy(stDzbpdj.chkdate, sDzrq, sizeof(stDzbpdj.chkdate));
			 */
			pstrcopy(stDzbpdj.chkdate, stPlksfmx.workdate, sizeof(stDzbpdj.chkdate));
			/* mod by tuql 20091020 以下信息应赋值为当日流水表的chkacctord值
			   pstrcopy(stDzbpdj.chkacctord, "", sizeof(stDzbpdj.chkacctord));
			 */
			pstrcopy(stDzbpdj.chkacctord, stPlksfmx.chkacctord, sizeof(stDzbpdj.chkacctord));
			pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));
			pstrcopy(stDzbpdj.payeebankno, stPlksfmx.payeebankno, sizeof(stDzbpdj.payeebankno));
			/* mod by tuql 20091009 以下信息应赋值为批量明细表的paybkcode值
			   pstrcopy(stDzbpdj.paybkcode, stPlksfmx.payopbkcode, sizeof(stDzbpdj.paybkcode));  	
			 */
			pstrcopy(stDzbpdj.paybkcode, stPlksfmx.paybkcode, sizeof(stDzbpdj.paybkcode));  	
			pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));
			pstrcopy(stDzbpdj.jyrq, stPlksfmx.zjrq, sizeof(stDzbpdj.jyrq));
			pstrcopy(stDzbpdj.jysj, stPlksfmx.zjsj, sizeof(stDzbpdj.jysj));
			stDzbpdj.jdbz[0]='1';
			pstrcopy(stDzbpdj.khmc, stPlksfmx.handorgname, sizeof(stDzbpdj.khmc));
			pstrcopy(stDzbpdj.jyzh, stPlksfmx.payacct, sizeof(stDzbpdj.jyzh));
			pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));
			pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));           
			stDzbpdj.jyje = stPlksfmx.jyje;
			pstrcopy(stDzbpdj.reason_info, "前置<->主机;前置多", sizeof(stDzbpdj.reason_info));
			pstrcopy(stDzbpdj.dzjg, "29", sizeof(stDzbpdj.dzjg));
			/* stDzbpdj.clzt[0]='8'; mod by tuql 20091020 */
			stDzbpdj.clzt[0]='0';
			pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
			pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
			stDzbpdj.cllsh = 0;
			pstrcopy(stDzbpdj.kzbz, stPlksfmx.kzbz, sizeof(stDzbpdj.kzbz));
			pstrcopy(stDzbpdj.clxx, "未处理", sizeof(stDzbpdj.clxx));
			pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));
			pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));
			pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));
			pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));

			iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj,sErrmsg);
			/*EXEC SQL INSERT INTO tips_dzbpdj values(:stDzbpdj);
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
			  if(SQLERR)*/
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("插入对帐登记表失败,帐务日期[%s],批量明细序号[%d]", 
							stPlksfmx.zwrq, stPlksfmx.plmxxh),"ERROR")   
					iFlag = -3;
				break;  	  			  	
			}
			/*更新该流水明细状态为前置多*/
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='2'||substr(kzbz,2,7) \
				WHERE entrustdate = '%s' AND taxorgcode='%s' AND packno='%s' \
				AND trano= '%s' AND czbd='7' AND substr(kzbz,1,1)='0'", \
				stPlksfmx.entrustdate, stPlksfmx.taxorgcode, stPlksfmx.packno, stPlksfmx.trano);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet = DCIExecuteDirect(sSql1);

			/*EXEC SQL UPDATE tips_ssplksfmx 
			  SET kzbz='2'||substr(kzbz,2,7)
			  WHERE entrustdate=:stPlksfmx.entrustdate
			  AND taxorgcode=:stPlksfmx.taxorgcode
			  AND packno=:stPlksfmx.packno
			  AND trano=:stPlksfmx.trano
			  AND czbd='7'
			  AND substr(kzbz,1,1)='0';
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
			  if(SQLERR) */
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("更新批量扣税费明细表失败,帐务日期[%s],批量明细序号[%d]", 
							stPlksfmx.zwrq, stPlksfmx.plmxxh),"ERROR")   
					iFlag = -5;
				break; 
			}
		}/* for (i=1,iFlag=0;;i++) */
		//EXEC SQL CLOSE cur_plksfmx_hxdz; 
		DCIFreeCursor(cur1);
		if (iFlag < 0)
		{
			fpub_SetMsg(lXmlhandle,24427,"处理与核心对账时批量前置多的情况失败");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("处理与核心对账时批量前置多的情况失败iflag=[%d]",iFlag),
					fpub_GetCompname(lXmlhandle))
		}
	}/* if( iCount > 0 )与核心对账前置多的情况 */ 
	LOG(LM_DEBUG,Fmtmsg("与核心主机对账结束,主机多[%d]笔, 前置多[%d]笔", 
				iZjdnum, iQzdnum), fpub_GetCompname(lXmlhandle));

	/* 增加对账结果统计 add 20140901 
	/* 初始化对账结果登记表 
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzjgxx WHERE dzrq = '%s' AND dzxt='1'");
	iSqlRet = DCIExecuteDirect(sSql1);

	/*EXEC SQL delete FROM tips_dzjgxx
	  WHERE dzrq = :sDzrq
	  AND dzxt='1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	/*if ( SQLERR )
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("删除对账结果登记表记录失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除对账结果登记表记录失败"), 
				fpub_GetCompname(lXmlhandle));
	}
	/* add 20140901 
	iQznum += iQzdnum;
	dQzamt += dQzdamt;

	pstrcopy(stDzjgxx.dzrq , sDzrq ,sizeof(stDzjgxx.dzrq));
	stDzjgxx.dzxt[0] = '1';
	pstrcopy(stDzjgxx.chkacctord  , sChkAcctOrd ,sizeof(stDzjgxx.chkacctord));
	stDzjgxx.allnum1 = iQznum;     
	stDzjgxx.allamt1 = dQzamt;    
	stDzjgxx.Allnum2 = iZjnum;			
	stDzjgxx.Allamt2 = dZjamt;     
	if(iQznum == iZjnum )
		stDzjgxx.dzjg[0] = '1';
	else if(iQznum <= iZjnum)
		stDzjgxx.dzjg[0] = '2';
	else if(iQznum >= iZjnum)
		stDzjgxx.dzjg[0] = '3';

	pstrcopy(stDzjgxx.byzd ,"",sizeof(stDzjgxx.byzd));
	iSqlRet = DBInsert("tips_dzjgxx", SD_TIPS_DZJGXX, NUMELE(SD_TIPS_DZJGXX), &stDzjgxx,sErrmsg);
	/*EXEC SQL INSERT INTO tips_dzjgxx values(:stDzjgxx);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	/*  if(SQLERR)
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		LOG(LM_STD,Fmtmsg("插入对帐结果失败,对账日期[%s],对账系统[%s]", 
					stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")   
			iFlag = -13;

	}*/    
	LOG(LM_STD,Fmtmsg("核心明细总笔数[%d],核心明细总金额[%f],TIPS前置笔数[%d],TIPS前置金额[%f]",
				iZjnum,dZjamt,iQznum,dQzamt), fpub_GetCompname(lXmlhandle));    

	fpub_SetMsg(lXmlhandle, 0, "与核心主机对账结束");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);    

	return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_GenREP_DZQD
  组件名称: 生成TIPS对账清单报表
  组件功能: 
  生成TIPS对账清单报表
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
  发布日期: 2009年03月05日
  修改日期: 2009年10月9日
  修改说明：modify by chenxm 20141112 DCI改造工作
  修改日期: 20141220DCI改造，待测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_GenREP_DZQD(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	char sPayBkCode[12+1];/* 付款行行号 */
	char sChkDate[8+1];/*对账日期*/
	char sChkAcctType[1+1];/* 对账类型 */
	char sPayeeBankNo[12+1];/* 收款行行号 */
	char sChkAcctOrd[4+1];/* 对账批次 */
	int iAllNum;/* 总笔数 */
	double dAllAmt;/* 总金额 */
	int iAllNum1;/* 总笔数 */
	double dAllAmt1;/* 总金额 */
	int iAllNum2;/* 总笔数 */
	double dAllAmt2;/* 总金额 */
	int iMzNum;/* 需抹账笔数 add by tuql 20091009 */
	double dMzAmt; /* 需抹账金额 add by tuql 20091009 */
	int iBzNum;/* 需补账笔数 add by tuql 20091009 */
	double dBzAmt;/* 需补账金额 add by tuql 20091009 */
	int iMzNum1;/* 需抹账笔数 add by tuql 20091009 */
	double dMzAmt1; /* 需抹账金额 add by tuql 20091009 */
	int iBzNum1;/* 需补账笔数 add by tuql 20091009 */
	double dBzAmt1;/* 需补账金额 add by tuql 20091009 */
	/*EXEC SQL END   DECLARE SECTION;*/

	SDB_TIPS_SSDZPLT tips_ssdzplt;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	char cAllNum1[16+1];
	char cAllAmt1[32+1];
	char cAllNum2[16+1];
	char cAllAmt2[32+1];
	char cMzNum[16+1];
	char cMzAmt[32+1];
	char cBzNum[16+1];
	char cBzAmt[32+1];
		
	memset(cAllNum1, 0x00, sizeof(cAllNum1)); 
	memset(cAllAmt1, 0x00, sizeof(cAllAmt1)); 
	memset(cAllNum2, 0x00, sizeof(cAllNum2)); 
	memset(cAllAmt2, 0x00, sizeof(cAllAmt2)); 
	memset(cMzNum, 0x00, sizeof(cMzNum)); 
	memset(cMzAmt, 0x00, sizeof(cMzAmt)); 
	memset(cBzNum, 0x00, sizeof(cBzNum)); 
	memset(cBzAmt, 0x00, sizeof(cBzAmt)); 
		
	char sBuf[256];
	char sBuf1[256];
	char sFile[256];/*文件名*/
	int i=0;
	int k=0;
	int iFlag=0;
	int iSqlRet = -1;
	FILE *fp=NULL;
	CURSOR cur;
	CURSOR cur1;
	CURSOR cur2;

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("生成对账清单报表开始"),"INFO");

	/*获取组件参数  --S*/
	COMP_PARACOUNTCHK(3)
	memset(sBuf, 0x00, sizeof(sBuf)); 
	memset(sFile, 0x00, sizeof(sFile));
	COMP_GETPARSEPARAS(1,sBuf,"对账文件名");
	pstrcopy(sFile, sBuf, sizeof(sFile));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(2,sBuf,"付款行行号");
	pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(3,sBuf,"对账日期");
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));     

	LOG(LM_STD,Fmtmsg("付款行行号[%s],对账日期[%s],对账文件名[%s]",
				sPayBkCode, sChkDate, sFile),"INFO");

	iAllNum = 0;
	/* add by chenxm 20141112 DCI改造工作*/
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssdzplt WHERE chkdate = '%s' AND  paybkcode = '%s'", \
		sChkDate, sPayBkCode);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DBSelectToVar(sErrmsg, &iAllNum, sSql1);

	/*EXEC SQL SELECT COUNT(*) INTO :iAllNum
	  FROM tips_ssdzplt 
	  WHERE  chkdate = :sChkDate 
	  AND  paybkcode = :sPayBkCode;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
	  if ( SQLERR )*/

	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("查询对账批量头表失败"));
		LOG(LM_STD,Fmtmsg("查询对账批量头表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	if ( iAllNum == 0 )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("本机构对账日[%s]没有对账记录", sChkDate));
		LOG(LM_STD,Fmtmsg("本机构对账日[%s]没有对账记录", sChkDate), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;        
	}    

	/*打开文件*/
	fp=fopen(sFile,"w");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24488, Fmtmsg("建立对账清单文件失败"));
		LOG(LM_STD,Fmtmsg("建立对账清单文件失败[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL; 
	}   

	fprintf(fp,"                                             横向联网对账清单                           \n\n");
	fprintf(fp,"                        付款行行号：%s                       对账日期：%s \n\n",sPayBkCode,sChkDate);
	fprintf(fp,"   平台与TIPS对账情况：\n");
	/*modify by wangw 右移四个空格   
	  fprintf(fp,"对账标志     收款国库行号      对账批次     批次笔数       批次金额    抹账笔数       抹账金额    补账笔数       补账金额\n"); */
	fprintf(fp,"    对账标志       收款国库行号  对账批次  TIPS笔数       TIPS金额  平台笔数       平台金额  抹账笔数       抹账金额  补账笔数       补账金额\n");

	/*定义游标*/
	/*add by chenxm 20141112 DCI改造工作*/
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT DISTINCT chkaccttype,payeebankno,chkacctord,allnum,allamt \
		FROM tips_ssdzplt WHERE chkdate ='%s' AND  paybkcode = '%s' ORDER BY payeebankno,chkacctord ", \
		sChkDate, sPayBkCode);
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
		LOG(LM_STD,Fmtmsg("声明游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
		LOG(LM_STD,Fmtmsg("打开cur_dzplt_dzqd游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	/*EXEC SQL DECLARE cur_dzplt_dzqd cursor for 
	  SELECT DISTINCT chkaccttype,payeebankno,chkacctord,allnum,allamt
	  FROM tips_ssdzplt 
	  WHERE  chkdate = :sChkDate 
	  AND  paybkcode = :sPayBkCode
	  ORDER BY payeebankno,chkacctord;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
	  LOG(LM_STD,Fmtmsg("声明游标失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }  */
	/*打开游标*/
	/*EXEC SQL OPEN cur_dzplt_dzqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzplt_dzqd",sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
	  LOG(LM_STD,Fmtmsg("打开cur_dzplt_dzqd游标失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  } */

	for (i=1, iFlag=0;; i++)
	{   	  
		iAllNum=0;
		dAllAmt=0.00;
		iAllNum1=0;
		dAllAmt1=0.00;
		iAllNum2=0;
		dAllAmt2=0.00;
		memset(sChkAcctType, 0x00, sizeof(sChkAcctType));
		memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
		memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));

		iSqlRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
		/*EXEC SQL FETCH cur_dzplt_dzqd INTO :sChkAcctType,:sPayeeBankNo,:sChkAcctOrd,:iAllNum,:dAllAmt;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzplt_dzqd",sqlca.sqlcode),"ERR");
		  if (SQLERR)*/
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("从cur_dzplt_dzqd游标获取数据失败"),"ERROR");
			iFlag = -1;
			break;
		}
		/*if (SQLNOTFOUND)*/
		if(iSqlRet == 0)
		{
			break; 
		}

		sprintf( sChkAcctType, "%s", DCIFieldAsString( cur, 0 ) );
		sprintf( sPayeeBankNo, "%s", DCIFieldAsString( cur, 1 ) );
		sprintf( sChkAcctOrd, "%s", DCIFieldAsString( cur, 2 ) );
		iAllNum = atoi(DCIFieldAsString( cur, 3 )) ;
		dAllAmt = atof(DCIFieldAsString( cur, 4 )) ;

		memset(sBuf1, 0x00, sizeof(sBuf1));
		/*****begin mod by tuql 20091009 增加抹补账的笔数及金额*****/
		iMzNum=0;
		dMzAmt=0.00;
		iBzNum=0;
		dBzAmt=0.00;
		if (sChkAcctType[0]=='0' )
		{	
			strcpy(sBuf1,"对平");
		}else
		{ 
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_drls WHERE chkdate= '%s' AND paybkcode='%s' "
					"AND payeebankno='%s' AND jyzt = '0' AND msgno in ('3001', '1008')",sChkDate,sPayBkCode,sPayeeBankNo);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cAllNum1, &cAllAmt1);
			iAllNum1=atoi(cAllNum1);
			dAllAmt1=atof(cAllAmt1);
			/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iAllNum1, :dAllAmt1 
			  FROM tips_drls
			  WHERE chkdate=:sChkDate
			  AND paybkcode=:sPayBkCode
			  AND payeebankno=:sPayeeBankNo
			  AND jyzt = '0'
			  AND msgno in ('3001', '1008');            
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
			  if ( SQLERR )*/
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("查询当日流水表失败[%s][%s][%s]",
							sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
				iFlag = -2;
				break;
			}

			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx WHERE chkdate= '%s' AND paybkcode='%s' "
					"AND payeebankno='%s' AND czbd = '7'", sChkDate, sPayBkCode, sPayeeBankNo);
			
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cAllNum2, &cAllAmt2);
			iAllNum2=atoi(cAllNum2);
			dAllAmt2=atof(cAllAmt2);
			/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iAllNum2, :dAllAmt2 
			  FROM tips_ssplksfmx
			  WHERE chkdate=:sChkDate
			  AND paybkcode=:sPayBkCode
			  AND payeebankno=:sPayeeBankNo
			  AND czbd = '7';         
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
			  if ( SQLERR )*/
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("查询当日流水表失败[%s][%s][%s]",
							sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
				iFlag = -2;
				break;
			}
			/* modify by leejn 20150310 浮点数不能用==比较
			if((iAllNum1+iAllNum2==iAllNum) && (dAllAmt1+dAllAmt2==dAllAmt))
			
			*/
			if((iAllNum1+iAllNum2==iAllNum) && (dAllAmt1+dAllAmt2-dAllAmt <= 0.0000001 )
				&& (dAllAmt1+dAllAmt2-dAllAmt >= -0.0000001))
			{
				strcpy(sBuf1,"对平");
			}
			else
			{
				strcpy(sBuf1,"不平");
			}
			/* 先从tips_dzbpdj表中获取需抹账笔数及金额 add by tuql 20091022*/
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_dzbpdj WHERE chkdate= '%s' AND paybkcode='%s' "
					"AND payeebankno='%s' AND dzlx = '3' AND dzjg in ('92')", sChkDate, sPayBkCode, sPayeeBankNo);
			
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cMzNum, &cMzAmt);
			iMzNum=atoi(cMzNum);
			dMzAmt=atof(cMzAmt);
			/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iMzNum, :dMzAmt 
			  FROM tips_dzbpdj
			  WHERE chkdate=:sChkDate
			  AND paybkcode=:sPayBkCode
			  AND payeebankno=:sPayeeBankNo
			  AND dzlx = '3' 
			  AND dzjg in ('92');           
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
			  if ( SQLERR )*/
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("查询对账不平登记表的需抹账笔数及金额失败[%s][%s][%s]",
							sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
				iFlag = -2;
				break;
			}
			/* 再从tips_dzbpdj表中获取需补账笔数及金额 */
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_dzbpdj WHERE chkdate= '%s' AND paybkcode='%s' "
					"AND payeebankno='%s' AND dzlx = '3' AND dzjg in ('93')", sChkDate, sPayBkCode, sPayeeBankNo);
			
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cBzNum, &cBzAmt);
			iBzNum=atoi(cBzNum);
			dBzAmt=atof(cBzAmt);
			/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iBzNum, :dBzAmt 
			  FROM tips_dzbpdj
			  WHERE chkdate=:sChkDate
			  AND paybkcode=:sPayBkCode
			  AND payeebankno=:sPayeeBankNo
			  AND dzlx = '3' 
			  AND dzjg in ('93');*           
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
			  if ( SQLERR )*/
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("查询对账不平登记表的需补账笔数及金额失败[%s][%s][%s]",
							sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
				iFlag = -3;
				break;
			}
		}

		/*modify by wangw 右移四个空格 */
		fprintf(fp,"  %-14.14s  %-12.12s  %-8.8s  %8d%15.2f  %8d%15.2f  %8d%15.2f  %8d%15.2f\n",
				sBuf1,sPayeeBankNo,sChkAcctOrd,iAllNum,dAllAmt,iAllNum1+iAllNum2,dAllAmt1+dAllAmt2,iMzNum,dMzAmt,iBzNum,dBzAmt);
		/*****end mod by tuql 20091009 增加抹补账的笔数及金额*****/
	}
	/*EXEC SQL CLOSE cur_dzplt_dzqd;*/
	DCIFreeCursor(cur);

	{
		fprintf(fp,"\n\n   平台与核心对账情况：\n");
		/*modify by wangw 右移四个空格   
		  fprintf(fp,"对账标志     收款国库行号      对账批次     批次笔数       批次金额    抹账笔数       抹账金额    补账笔数       补账金额\n"); */
		fprintf(fp,"    对账标志       收款国库行号  对账批次  平台笔数       平台金额  核心笔数       核心金额  抹账笔数       抹账金额  补账笔数       补账金额\n");

		/*定义游标*/
		/*add by chenxm 20141112 DCI改造工作*/
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT DISTINCT chkaccttype,payeebankno,chkacctord,allnum,allamt FROM tips_ssdzplt \
			WHERE chkdate ='%s' AND  paybkcode = '%s' ORDER BY payeebankno,chkacctord ", sChkDate, sPayBkCode);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
		{
			fclose(fp);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
			LOG(LM_STD,Fmtmsg("声明游标失败"), fpub_GetCompname(lXmlhandle));        
			return COMPRET_FAIL;
		}
		if (DCIExecute(cur1) == -1)
		{
			fclose(fp);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
			LOG(LM_STD,Fmtmsg("打开cur_dzplt_dzqd游标失败"), fpub_GetCompname(lXmlhandle));        
			return COMPRET_FAIL;
		}

		/*EXEC SQL DECLARE cur_dzplt_dzqd1 cursor for 
		  SELECT DISTINCT chkaccttype,payeebankno,chkacctord,allnum,allamt
		  FROM tips_ssdzplt 
		  WHERE  chkdate = :sChkDate 
		  AND  paybkcode = :sPayBkCode
		  ORDER BY payeebankno,chkacctord;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
		  if ( SQLERR )
		  {
		  fclose(fp);
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
		  LOG(LM_STD,Fmtmsg("声明游标失败"), fpub_GetCompname(lXmlhandle));        
		  return COMPRET_FAIL;
		  }*/  
		/*打开游标*/
		/*EXEC SQL OPEN cur_dzplt_dzqd1;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzplt_dzqd1",sqlca.sqlcode),"ERROR");
		  if ( SQLERR )
		  {
		  fclose(fp);
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
		  LOG(LM_STD,Fmtmsg("打开cur_dzplt_dzqd1游标失败"), fpub_GetCompname(lXmlhandle));        
		  return COMPRET_FAIL;
		  }*/
		for (i=1, iFlag=0;; i++)
		{   	  
			iAllNum=0;
			dAllAmt=0.00;
			iAllNum1=0;
			dAllAmt1=0.00;
			iAllNum2=0;
			dAllAmt2=0.00;
			memset(sChkAcctType, 0x00, sizeof(sChkAcctType));
			memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
			memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));

			iSqlRet = DCIFetch2(cur1, DCI_FETCH_NEXT, 0);
			/*EXEC SQL FETCH cur_dzplt_dzqd1 INTO :sChkAcctType,:sPayeeBankNo,:sChkAcctOrd,:iAllNum,:dAllAmt;
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzplt_dzqd1",sqlca.sqlcode),"ERR");*/
			if(iSqlRet < 0)
				/*if (SQLERR)*/
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("从cur_dzplt_dzqd1游标获取数据失败"),"ERROR");
				iFlag = -1;
				break;
			}
			/*if (SQLNOTFOUND)*/
			if(iSqlRet == 0)
			{
				break; 
			}

			sprintf( sChkAcctType, "%s", DCIFieldAsString( cur, 0 ) );
			sprintf( sPayeeBankNo, "%s", DCIFieldAsString( cur, 1 ) );
			sprintf( sChkAcctOrd, "%s", DCIFieldAsString( cur, 2 ) );
			iAllNum = atoi( DCIFieldAsString( cur, 3 ) );
			dAllAmt = atof( DCIFieldAsString( cur, 4 ) );

			memset(sBuf1, 0x00, sizeof(sBuf1));
			/*****begin mod by tuql 20091009 增加抹补账的笔数及金额*****/
			iMzNum=0;
			dMzAmt=0.00;
			iBzNum=0;
			dBzAmt=0.00;
			if (sChkAcctType[0]=='0' )
			{	
				strcpy(sBuf1,"对平");
			}else
			{ 
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_drls WHERE chkdate= '%s' AND paybkcode='%s' "
						"AND payeebankno='%s' AND jyzt = '0' AND substr(dzbz,1,1) <> '0' AND msgno in ('3001', '1008')",sChkDate,sPayBkCode,sPayeeBankNo);
				
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
				iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cAllNum1, &cAllAmt1);
				LOG(LM_DEBUG,Fmtmsg("cAllNum1[%s]cAllAmt1[%s]",cAllNum1,cAllAmt1),"INFO") 
				
				iAllNum1=atoi(cAllNum1);
				dAllAmt1=atof(cAllAmt1);
				/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iAllNum1, :dAllAmt1 
				  FROM tips_drls
				  WHERE chkdate=:sChkDate
				  AND paybkcode=:sPayBkCode
				  AND payeebankno=:sPayeeBankNo
				  AND jyzt = '0'
				  AND substr(dzbz,1,1) <> '0'
				  AND msgno in ('3001', '1008');           
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
				  if ( SQLERR )*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("查询当日流水表失败[%s][%s][%s]",
								sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
					iFlag = -2;
					break;
				}

				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx WHERE chkdate= '%s' AND paybkcode='%s' "
						"AND payeebankno='%s' AND substr(kzbz,1,1) <> '0' AND czbd = '7'",sChkDate,sPayBkCode,sPayeeBankNo);
				
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
				iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cAllNum2, &cAllAmt2);
				LOG(LM_DEBUG,Fmtmsg("cAllNum2[%s]cAllAmt2[%s]",cAllNum2,cAllAmt2),"INFO") 
				iAllNum2=atoi(cAllNum2);
				dAllAmt2=atof(cAllAmt2);
				/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iAllNum2, :dAllAmt2 
				  FROM tips_ssplksfmx
				  WHERE chkdate=:sChkDate
				  AND paybkcode=:sPayBkCode
				  AND payeebankno=:sPayeeBankNo
				  AND substr(kzbz,1,1) <> '0'
				  AND czbd = '7';           
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
				  if ( SQLERR )*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("查询批量明细失败[%s][%s][%s]",
								sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
					iFlag = -2;
					break;
				}
				/* 先从tips_dzbpdj表中获取需抹账笔数及金额 add by tuql 20091022*/
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_dzbpdj WHERE chkdate= '%s' AND paybkcode='%s' "
						"AND payeebankno='%s' AND dzlx = '1' AND dzjg in ('39')",sChkDate,sPayBkCode,sPayeeBankNo);
				
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
				iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cMzNum, &cMzAmt);
				iMzNum=atoi(cMzNum);
				dMzAmt=atof(cMzAmt);
				/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iMzNum, :dMzAmt 
				  FROM tips_dzbpdj
				  WHERE chkdate=:sChkDate
				  AND paybkcode=:sPayBkCode
				  AND payeebankno=:sPayeeBankNo
				  AND dzlx = '1' 
				  AND dzjg in ('39');         
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
				  if ( SQLERR )*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("查询对账不平登记表的需抹账笔数及金额失败[%s][%s][%s]",
								sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
					iFlag = -2;
					break;
				}
				/* 再从tips_dzbpdj表中获取需补账笔数及金额 */
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_dzbpdj WHERE chkdate= '%s' AND paybkcode='%s' "
						"AND payeebankno='%s' AND dzlx = '1' AND dzjg in ('29')",sChkDate,sPayBkCode,sPayeeBankNo);
				
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
				iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cBzNum, &cBzAmt);	
				iBzNum=atoi(cBzNum);
				dBzAmt=atof(cBzAmt);
				/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iBzNum, :dBzAmt 
				  FROM tips_dzbpdj
				  WHERE chkdate=:sChkDate
				  AND paybkcode=:sPayBkCode
				  AND payeebankno=:sPayeeBankNo
				  AND dzlx = '1' 
				  AND dzjg in ('29');            
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
				  if ( SQLERR )*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("查询对账不平登记表的需补账笔数及金额失败[%s][%s][%s]",
								sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
					iFlag = -3;
					break;
				}
				if((iMzNum==0) && (iBzNum==0))
				{
					strcpy(sBuf1,"对平");
				}
				else
				{
					strcpy(sBuf1,"不平");
				}
			}
			/*modify by wangw 右移四个空格 */
			fprintf(fp,"  %-14.14s  %-12.12s  %-8.8s  %8d%15.2f  %8d%15.2f  %8d%15.2f  %8d%15.2f\n",
					sBuf1,sPayeeBankNo,sChkAcctOrd,iAllNum1+iAllNum2,dAllAmt1+dAllAmt2,iAllNum1+iAllNum2+iMzNum-iBzNum,dAllAmt1+dAllAmt2+dMzAmt-dBzAmt,iMzNum,dMzAmt,iBzNum,dBzAmt);
			/*****end mod by tuql 20091009 增加抹补账的笔数及金额*****/
		}
		/*EXEC SQL CLOSE cur_dzplt_dzqd1;*/
		DCIFreeCursor(cur1);
	}

	/* add by tuql 20091009 */
	/*增加收款国库行汇总统计--add by wangw 20120830 begin*/
	fprintf(fp,"\n\n\n");
	fprintf(fp,"                                             收款国库行汇总数据                           \n");
	/*modify by wangw 调整格式 
	  fprintf(fp,"     收款国库行号        汇总笔数         汇总金额    抹账笔数          抹账金额    补账笔数          补账金额\n"); */
	fprintf(fp,"     收款国库行号  汇总笔数         汇总金额  抹账笔数          抹账金额  补账笔数          补账金额\n");

	/*定义游标select 字段减少allnum、allamt--wangw 20120906*/
	/*add by chenxm 20141112 DCI改造工作*/
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT DISTINCT payeebankno,sum(curpacknum),sum(curpackamt) FROM tips_ssdzplt \
		WHERE chkdate ='%s' AND  paybkcode = '%s' group BY payeebankno order BY payeebankno", sChkDate, sPayBkCode);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
	
	if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
		LOG(LM_STD,Fmtmsg("声明游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur1) == -1)
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
		LOG(LM_STD,Fmtmsg("打开cur_dzplt_dzqd游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	/*EXEC SQL DECLARE cur_dzplt1_dzqd cursor for 
	  SELECT DISTINCT payeebankno,sum(curpacknum),sum(curpackamt)
	  FROM tips_ssdzplt 
	  WHERE  chkdate = :sChkDate 
	  AND  paybkcode = :sPayBkCode
	  group BY payeebankno
	  order BY payeebankno;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
	  LOG(LM_STD,Fmtmsg("声明游标失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }  */
	/*打开游标*/
	/*EXEC SQL OPEN cur_dzplt1_dzqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzplt1_dzqd",sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
	  LOG(LM_STD,Fmtmsg("打开cur_dzplt1_dzqd游标失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }*/

	for (i=1, iFlag=0;; i++)
	{   	  
		iAllNum=0;
		dAllAmt=0.00;
		memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
		
		iSqlRet = DCIFetch2(cur1, DCI_FETCH_NEXT, 0);
		
		/*EXEC SQL FETCH cur_dzplt1_dzqd INTO :sPayeeBankNo,:iAllNum,:dAllAmt;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzplt1_dzqd",sqlca.sqlcode),"ERR");
		  if (SQLERR)*/
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("从cur_dzplt1_dzqd游标获取数据失败"),"ERROR");
			iFlag = -1;
			break;
		}
		/*if (SQLNOTFOUND)*/
		if(iSqlRet == 0)
		{
			break; 
		}
		
		sprintf( sPayeeBankNo, "%s", DCIFieldAsString( cur, 0 ) );
		iAllNum = atoi(DCIFieldAsString( cur, 1 ) ); 
		dAllAmt = atof(DCIFieldAsString( cur, 2 ) );
		
		
		memset(sBuf, 0x00, sizeof(sBuf));
		/****增加抹补账的笔数及金额*****/
		iMzNum=0;
		dMzAmt=0.00;
		iBzNum=0;
		dBzAmt=0.00;

		/* 先从tips_dzbpdj表中获取需抹账笔数及金额 add by tuql 20091022*/
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_dzbpdj WHERE chkdate= '%s' AND paybkcode='%s' "
				"AND payeebankno='%s' AND dzlx <> '5' AND dzjg in ('39', '92')",sChkDate,sPayBkCode,sPayeeBankNo);
		
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
		iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cMzNum, &cMzAmt);
		iMzNum=atoi(cMzNum);
		dMzAmt=atof(cMzAmt);
		/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iMzNum, :dMzAmt 
		  FROM tips_dzbpdj
		  WHERE chkdate=:sChkDate
		  AND paybkcode=:sPayBkCode
		  AND payeebankno=:sPayeeBankNo
		  AND dzlx <> '5' 
		  AND dzjg in ('39', '92');           
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("查询对账不平登记表的需抹账笔数及金额失败[%s][%s][%s]",
						sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
			iFlag = -2;
			break;
		}
		/* 再从tips_dzbpdj表中获取需补账笔数及金额 */
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT COUNT(*), SUM(jyje) FROM tips_dzbpdj WHERE chkdate= '%s' AND paybkcode='%s' "
				"AND payeebankno='%s' AND dzlx <> '5' AND dzjg in ('29', '92')",sChkDate,sPayBkCode,sPayeeBankNo);
		
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
		iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cMzNum, &cMzAmt);
		iMzNum=atoi(cMzNum);
		dMzAmt=atof(cMzAmt);
		/*EXEC SQL SELECT COUNT(*), SUM(jyje) INTO :iBzNum, :dBzAmt 
		  FROM tips_dzbpdj
		  WHERE chkdate=:sChkDate
		  AND paybkcode=:sPayBkCode
		  AND payeebankno=:sPayeeBankNo
		  AND dzlx <> '5' 
		  AND dzjg in ('29', '93');            
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("查询对账不平登记表的需补账笔数及金额失败[%s][%s][%s]",
						sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
			iFlag = -3;
			break;
		}

		/*modify by wangw 调整格式 */
		fprintf(fp,"     %-12.12s  %8d %16.2f  %8d  %16.2f  %8d  %16.2f\n",
				sPayeeBankNo,iAllNum,dAllAmt,iMzNum,dMzAmt,iBzNum,dBzAmt);
		/*****end 增加抹补账的笔数及金额*****/
	}
	/*EXEC SQL CLOSE cur_dzplt1_dzqd;*/
	DCIFreeCursor(cur);
	/*增加收款国库行汇总统计--add by wangw 20120830 end*/

	fclose(fp);

	if (iFlag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("生成对账清单报表失败"));
		LOG(LM_STD,Fmtmsg("生成对账清单报表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle, 0, Fmtmsg("生成对账清单报表失败"));
	LOG(LM_STD,Fmtmsg("生成对账清单报表成功"),"INFO");
	return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_GenREP_KHHQD
  组件名称: 开户行交易清单报表
  组件功能: 
  开户行交易清单报表
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
  发布日期: 2009年03月05日
  修改日期: modify by chenxm 20141111 DCI改造工作
  修改日期: 20141220DCI改造，待测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_GenREP_KHHQD(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDqdh[10];/*地区代号*/
	char sJgdh[10];/*查询机构代号*/
	char sGyjgdh[10];/*柜员机构代号*/
	char sZwrq[8+1];
	char sZjrq[8+1];
	char sZjlsh[20+1],sJgjb[20+1];
	char sPayAcct[32+1];
	char sMsgNo[4+1],sJkrmc[200+1],sZsjgdm[20+1];
	double dAmt;
	long iCount,iLen;
	char sSql[256];
	//EXEC SQL END   DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char sFile[256];/*文件名*/
	int i=0;
	int k=0;
	int iFlag=0;
	int iSqlRet = -1;
	FILE *fp=NULL;
	CURSOR cur;
	CURSOR cur1;
	SDB_TIPS_SSPLKSFMX tips_ssplksfmx;

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("生成开户行清单报表开始"),"INFO");

	COMP_PARACOUNTCHK(4)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sFile, 0x00, sizeof(sFile));
	COMP_GETPARSEPARAS(1,sBuf,"报表文件名");
	pstrcopy(sFile, sBuf, sizeof(sFile));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDqdh, 0x00, sizeof(sDqdh));
	COMP_GETPARSEPARAS(2,sBuf,"地区代号");
	pstrcopy(sDqdh, sBuf, sizeof(sDqdh));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sJgdh, 0x00, sizeof(sJgdh));
	COMP_GETPARSEPARAS(3,sBuf,"机构代号"); 
	pstrcopy(sJgdh, sBuf, sizeof(sJgdh));
	trim(sJgdh);

	memset(sBuf, 0x00, sizeof(sBuf)); 
	memset(sZwrq, 0x00, sizeof(sZwrq));   
	COMP_GETPARSEPARAS(4,sBuf,"账务日期");
	pstrcopy(sZwrq, sBuf, sizeof(sZwrq));

	LOG(LM_STD,Fmtmsg("账务日期[%s],地区代号[%s],机构代号[%s],报表文件名[%s]",
				sZwrq, sDqdh, sJgdh, sFile),fpub_GetCompname(lXmlhandle));

	/*取柜员所属机构*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/pub/jgdh", sBuf)
		pstrcopy(sGyjgdh, sBuf, sizeof(sGyjgdh));
	trim(sGyjgdh);

	/*取柜员所属机构上级机构--add by wangw 20120911*/
	memset(sJgjb, 0x00, sizeof(sJgjb));

	/* add by chenxm 20141111 */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "select inner_org_id from t_org where org_id = '%s'", sGyjgdh);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DBSelectToVar(sErrmsg, sJgjb, sSql1);
	/*add end */

	/*EXEC SQL select inner_org_id into :sJgjb from t_org where org_id =:sGyjgdh;*/
	trim(sJgjb);
	iLen = strlen(sJgjb);
	LOG(LM_STD,Fmtmsg("sGyjgdh[%s]iLen[%d]sJgjb[%s]",sGyjgdh,iLen,sJgjb),fpub_GetCompname(lXmlhandle));
	iCount = 0;
	memset(sSql1, 0x00, sizeof(sSql1));
	if ( 0 == strlen(sJgdh))
	{
		/* add by chenxm 20141111 */
		sprintf(sSql1, "select COUNT(*) from tips_drls where workdate = '%s' AND  jyzt = '0' "
				"AND  msgno in ('3001', '1008') AND  qsbz = '0' AND  substr(dzbz,2,1) = '1' "
				"AND  rtrim(jgdh) in ( select rtrim(org_id) from t_org where substr(rtrim(inner_org_id),1,%d)= %s)", sZwrq, iLen, sJgjb);
		/* add end */

		/*EXEC SQL SELECT COUNT(*) INTO :iCount
		  FROM tips_drls 
		  WHERE  workdate = :sZwrq
		  AND  jyzt = '0'
		  AND  msgno in ('3001', '1008') 
		  AND  qsbz = '0' 
		  AND  substr(dzbz,2,1) = '1'
		  AND  rtrim(jgdh) in ( select rtrim(org_id) from t_org where substr(rtrim(inner_org_id),1,:iLen)=:sJgjb);*/
		LOG(LM_STD,Fmtmsg("[%d]",iCount),fpub_GetCompname(lXmlhandle));
	}
	else
	{
		/* add by chenxm 20141111 */
		sprintf(sSql1, "select COUNT(*) from tips_drls where workdate = '%s' AND jgdh = '%s' AND  jyzt = '0' "
				"AND  msgno in ('3001', '1008') AND  qsbz = '0' AND  substr(dzbz,2,1) = '1' ", sZwrq, sJgdh);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		/* add end */
		/*EXEC SQL SELECT COUNT(*) INTO :iCount
		  FROM tips_drls 
		  WHERE  workdate = :sZwrq
		  AND  jgdh = :sJgdh 
		  AND  jyzt = '0'
		  AND  msgno in ('3001', '1008') 
		  AND  qsbz = '0' 
		  AND  substr(dzbz,2,1) = '1';*/
	}
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
	  if ( SQLERR )*/
	iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("查询当日流水表失败"));
		LOG(LM_STD,Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	if ( iCount == 0 )
	{ 
		/*modify by wangw 20120809 增加批量明细判断 Begin */
		memset(sSql1, 0x00, sizeof(sSql1));
		if (strlen(sJgdh)==0) 
		{
			sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssplksfmx WHERE  workdate = '%s' AND czbd = '7' "
					"AND  qsbz = '0' AND  substr(kzbz,2,1) = '1' AND  rtrim(jgdh) in ( select rtrim(org_id) "
					"from t_org where substr(rtrim(inner_org_id),1,%d)=%s)",sZwrq, iLen, sJgjb);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			/*EXEC SQL SELECT COUNT(*) INTO :iCount
			  FROM tips_ssplksfmx 
			  WHERE  workdate = :sZwrq
			  AND  czbd = '7'
			  AND  qsbz = '0' 
			  AND  substr(kzbz,2,1) = '1'
			  AND  rtrim(jgdh) in ( select rtrim(org_id)  from t_org where substr(rtrim(inner_org_id),1,:iLen)=:sJgjb);*/
			LOG(LM_STD,Fmtmsg("[%d]",iCount),fpub_GetCompname(lXmlhandle));
		}
		else
		{
			sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssplksfmx WHERE  workdate = '%s' AND  jgdh = '%s' AND  czbd = '7' "
					"AND  qsbz = '0' AND  substr(kzbz,2,1) = '1' ",sZwrq, sJgdh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			/*EXEC SQL SELECT COUNT(*) INTO :iCount
			  FROM tips_ssplksfmx 
			  WHERE  workdate = :sZwrq
			  AND  jgdh = :sJgdh
			  AND  czbd = '7'
			  AND  qsbz = '0' 
			  AND  substr(kzbz,2,1) = '1';*/
		}
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")*/
		iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
		//if ( SQLERR )
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("查询批量明细表失败"));
			LOG(LM_STD,Fmtmsg("查询批量明细表失败"), fpub_GetCompname(lXmlhandle));        
			return COMPRET_FAIL;
		}
		if ( iCount == 0 )
		{
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("本机构无此报表数据"));
			LOG(LM_STD,Fmtmsg("本机构无此报表数据[%d]", iCount), fpub_GetCompname(lXmlhandle));        
			return COMPRET_FAIL;  
		}      
		/*modify by wangw 20120809 增加批量明细判断 End */
	}    

	/*打开文件*/
	fp=fopen(sFile,"w");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24492, Fmtmsg("建立开户行清单报表失败"));
		LOG(LM_STD,Fmtmsg("建立开户行清单报表失败[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL; 
	}  

	fprintf(fp,"                      横向联网扣税情况(开户行)                    \n");
	fprintf(fp,"                                         交易日期：%s\n",sZwrq);
	fprintf(fp,"核心扣账日期        缴款账号           缴款单位名称                            金额   缴款类型    征收机关代码              交易流水号\n");

	/*定义游标*/
	memset(sSql, 0x00, sizeof(sSql));
	if (strlen(sJgdh)==0)
	{
		sprintf(sSql,"SELECT zjrq,payacct,msgno,jyje,handorgname,taxorgcode,zjlsh FROM tips_drls \
			WHERE  workdate ='%s' and jyzt = '0' AND  msgno in ('3001', '1008') AND  qsbz = '0' \
			AND  substr(dzbz,2,1) = '1' AND rtrim(jgdh) in ( select rtrim(org_id)  \
			from t_org where substr(rtrim(inner_org_id),1,%d)='%s')",sZwrq,iLen,sJgjb);
	}
	else
	{
		sprintf(sSql,"SELECT zjrq,payacct,msgno,jyje,handorgname,taxorgcode,zjlsh FROM tips_drls \
		WHERE  workdate ='%s' AND  rtrim(jgdh) ='%s' and jyzt = '0' AND  msgno in ('3001', '1008') \
		AND  qsbz = '0' AND  substr(dzbz,2,1) = '1'",sZwrq,sJgdh);
	}
	LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO") 
	/*EXEC SQL PREPARE sql_qrykhhdq FROM :sSql;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrykhhdq",sqlca.sqlcode),"ERROR"); */   
	/*declare*/
	/*EXEC SQL DECLARE cur_drls_khhqd CURSOR for sql_qrykhhdq;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_drls_khhqd",sqlca.sqlcode),"ERROR");*/

	/*add by chenxm 20141111 DCI改造工作*/
	/*if ( SQLERR )*/
	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
		LOG(LM_STD,Fmtmsg("声明cur_drls_khhqd游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	/*打开游标*/
	/*EXEC SQL OPEN cur_drls_khhqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_drls_khhqd",sqlca.sqlcode),"ERROR");*/
	if (DCIExecute(cur) == -1)
		/*if ( SQLERR )*/
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
		LOG(LM_STD,Fmtmsg("打开cur_drls_khhqd游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	} 
	for (i=1, iFlag=0;; i++)
	{
		dAmt=0.00;
		memset(sZjlsh, 0x00, sizeof(sZjlsh));
		memset(sPayAcct, 0x00, sizeof(sPayAcct));
		memset(sMsgNo, 0x00, sizeof(sMsgNo));
		/*EXEC SQL FETCH cur_drls_khhqd INTO :sZjlsh,:sPayAcct,:sMsgNo,:dAmt,:sJkrmc,:sZsjgdm;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_drls_khhqd",sqlca.sqlcode),"ERR");
		  if (SQLERR)*/
		iSqlRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("从cur_drls_khhqd游标获取数据失败"),"ERROR");
			iFlag = -1;
			break;
		}
		/*if (SQLNOTFOUND)*/
		if(iSqlRet == 0)
		{
			break; 
		}

		sprintf( sZjrq, "%s", DCIFieldAsString( cur, 0 ) );
		sprintf( sPayAcct, "%s", DCIFieldAsString( cur, 1 ) );
		sprintf( sMsgNo, "%s", DCIFieldAsString( cur, 2 ) );
		dAmt = atof( DCIFieldAsString( cur, 3 ) );
		sprintf( sJkrmc, "%s", DCIFieldAsString( cur, 4 ) );
		sprintf( sZsjgdm, "%s", DCIFieldAsString( cur, 5 ) );
		sprintf( sZjlsh, "%s", DCIFieldAsString( cur, 6 ) );

		trim(sMsgNo);
		memset(sBuf, 0x00, sizeof(sBuf));
		if (strncmp(sMsgNo,"3001", 4) == 0)
		{ 
			strcpy(sBuf,"实时扣款"); 
		}else
		{ 
			strcpy(sBuf,"银行端扣款"); 
		}
		fprintf(fp,"%-8.8s       %-18.18s     %-30.30s     %11.2f  %-10.10s  %-20.20s      %-15.15s\n",
				sZjrq, sPayAcct, sJkrmc, dAmt, sBuf, sZsjgdm, sZjlsh );

	}
	/*EXEC SQL CLOSE cur_drls_khhqd;*/
	DCIFreeCursor(cur);

	if (iFlag < 0)
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("生成开户行清单报表失败"));
		LOG(LM_STD,Fmtmsg("生成开户行清单报表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	/*定义游标*/
	memset(sSql, 0x00, sizeof(sSql));
	memset(sBuf, 0x00, sizeof(sBuf));
	strcpy(sBuf,"批量扣款"); 
	if (strlen(sJgdh)==0)
	{
		iLen = strlen(sJgjb);
		sprintf(sSql,"SELECT zjrq,payacct,jyje,handorgname,taxorgcode,zjlsh FROM tips_ssplksfmx \
			WHERE  workdate ='%s'  and czbd = '7' AND  qsbz = '0' AND  substr(kzbz,2,1) = '1' \
			AND rtrim(jgdh) in ( select rtrim(org_id)  from t_org where substr(rtrim(inner_org_id),1,%d)='%s')",\
			sZwrq,iLen,sJgjb);
	}
	else
	{
		sprintf(sSql,"SELECT zjrq,payacct,jyje,handorgname,taxorgcode,zjlsh FROM tips_ssplksfmx \
		WHERE  workdate ='%s' AND  rtrim(jgdh) ='%s' and czbd = '7' AND  qsbz = '0' AND  \
		substr(kzbz,2,1) = '1'",sZwrq,sJgdh);
	}
	LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql1),"INFO") 
	/*EXEC SQL PREPARE sql_qrykhhmxdq FROM :sSql;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrykhhmxdq",sqlca.sqlcode),"ERROR");   */
	if ((cur1 = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
		LOG(LM_STD,Fmtmsg("声明cur_drls_khhqd游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}	
	/*declare*/
	/*EXEC SQL DECLARE cur_plksfmx_khhqd CURSOR for sql_qrykhhmxdq;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERR");*/

	/*打开游标*/
	/*EXEC SQL OPEN cur_plksfmx_khhqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_plksfmx_khhqd",sqlca.sqlcode),"ERROR");*/
	if (DCIExecute(cur1) == -1)
		/*if ( SQLERR )*/
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
		LOG(LM_STD,Fmtmsg("打开cur_plksfmx_khhqd游标失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	} 
	for (i=1, iFlag=0;; i++)
	{   	  
		dAmt=0.00;
		memset(sZjlsh, 0x00, sizeof(sZjlsh));
		memset(sPayAcct, 0x00, sizeof(sPayAcct));
		memset(&tips_ssplksfmx, 0x00, sizeof(SDB_TIPS_SSPLKSFMX));
		/*EXEC SQL FETCH cur_plksfmx_khhqd INTO :sZjlsh,:sPayAcct,:dAmt,:sJkrmc,:sZsjgdm;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_plksfmx_khhqd",sqlca.sqlcode),"ERR");
		  if (SQLERR)*/
		iSqlRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("从cur_plksfmx_khhqd游标获取数据失败"),"ERROR");
			iFlag = -1;
			break;
		}
		/*if (SQLNOTFOUND)*/
		if(iSqlRet == 0)
		{
			break; 
		}
		sprintf( sZjrq, "%s", DCIFieldAsString( cur, 0 ) );
		sprintf( sPayAcct, "%s", DCIFieldAsString( cur, 1 ) );
		dAmt = atof( DCIFieldAsString( cur, 2 ) );
		sprintf( sJkrmc, "%s", DCIFieldAsString( cur, 3 ) );
		sprintf( sZsjgdm, "%s", DCIFieldAsString( cur, 4 ) );
		sprintf( sZjlsh, "%s", DCIFieldAsString( cur, 5 ) );


		fprintf(fp,"%-8.8s       %-18.18s     %-30.30s     %11.2f  %-10.10s  %-20.20s      %-15.15s\n",
				sZjrq, sPayAcct, sJkrmc, dAmt, sBuf, sZsjgdm, sZjlsh );
	}
	fclose(fp);
	/*EXEC SQL CLOSE cur_plksfmx_khhqd;*/
	DCIFreeCursor(cur1);
	if (iFlag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("生成开户行清单报表失败"));
		LOG(LM_STD,Fmtmsg("生成开户行清单报表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle, 0, Fmtmsg("生成开户行清单报表成功"));
	LOG(LM_STD,Fmtmsg("生成开户行清单报表成功"),"INFO");
	return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_GenREP_FKHQD
  组件名称: 生成付款行清单报表
  组件功能: 
  开户行交易清单报表
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
  发布日期: 2009年03月05日
  修改日期: 20141111 modify by chenxm DCI改造工作
  修改日期: 20141220DCI改造，待测
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_GenREP_FKHQD(HXMLTREE lXmlhandle)
{
	int iParas ;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sPayBkCode[12+1];
	char sChkDate[8+1];/*清算行号、对账日期*/
	char sDqdh[10+1];
	char sDzpc[4+1];
	char sJgdh[10+1];
	char sBankno[10+1];
	char str_Jgdh[10+1];
	int iAllNum1;
	int iAllNum2;
	int iAllNum3;
	int iTmpNum;
	char sBegDate[8+1];
	char sEndDate[8+1];
	double dAllAmt1;
	double dAllAmt2;
	double dAllAmt3;
	double dTmpAmt;
	//EXEC SQL END   DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];   
	char cTmpNum[16+1];
  char cTmpAmt[32+1];
  
	char sBuf[256];
	char sFile[256];/*文件名*/
	int i=0;
	int k=0;
	int iFlag=0;
	int iSumNum=0;
	int iSqlRet = -1;
	double dSumAmt=0.00;
	int nSumNum=0;
	double nSumAmt=0.00;
	FILE *fp=NULL;
	CURSOR cur;

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("生成付款行清单报表开始"),"INFO");

	COMP_PARACOUNTCHK(4)

  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sFile, 0x00, sizeof(sFile));
  COMP_GETPARSEPARAS(1,sBuf,"付款行清单报表");
  pstrcopy(sFile, sBuf, sizeof(sFile));
  
  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
  COMP_GETPARSEPARAS(2,sBuf,"付款行行号");
  pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
  
  /* 原产品版参数 mod by  leejn 20141220
  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sChkDate, 0x00, sizeof(sChkDate));
  COMP_GETPARSEPARAS(3,sBuf,"对账日期");
  pstrcopy(sChkDate, sBuf, sizeof(sChkDate));     

  memset(sBegDate, 0x00, sizeof(sBegDate));
  memset(sEndDate, 0x00, sizeof(sEndDate));
  sprintf(sBegDate, "%-6.6s01", sChkDate);
  sprintf(sEndDate, "%-6.6s31", sChkDate);  
  
  LOG(LM_STD,Fmtmsg("付款行行号[%s], 对账日期[%s],报表[%s]", 
        sPayBkCode, sChkDate, sFile),fpub_GetCompname(lXmlhandle));
  */   
     
  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sBegDate, 0x00, sizeof(sBegDate));
  COMP_GETPARSEPARAS(3,sBuf,"查询开始日期");
  pstrcopy(sBegDate, sBuf, sizeof(sBegDate));     

  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sEndDate, 0x00, sizeof(sEndDate));
  COMP_GETPARSEPARAS(4,sBuf,"查询结束日期");
  pstrcopy(sEndDate, sBuf, sizeof(sEndDate));     

  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sBankno, 0x00, sizeof(sBankno));
  COMP_SOFTGETXML("/tips/org", sBuf)
  pstrcopy(sBankno, sBuf, sizeof(sBankno));     

  LOG(LM_STD,Fmtmsg("付款行行号[%s], 对账日期[%s]-[%s],报表[%s]", 
        sPayBkCode, sBegDate,sEndDate, sFile),fpub_GetCompname(lXmlhandle));

	iTmpNum = 0;
	iAllNum1 = 0 ; 
	memset(sSql1, 0x00, sizeof(sSql1));
	if(strlen(sBankno)==0)   
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_drls WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND jyzt = '0' AND msgno in ('3001','1008') AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate, sEndDate, sPayBkCode);

		/* noted by chenxm 20141111 DCI改造工作
		   EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_drls              
		   WHERE workdate >= :sBegDate       //账务日期/
		   AND workdate <= :sEndDate       //账务日期/
		   AND paybkcode = :sPayBkCode //清算行号/
		   AND jyzt = '0'
		   AND msgno in ('3001','1008')
		   AND qsbz='0'
		   AND substr(dzbz,2,1)='1';*/	
	}
	else
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_drls WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND bankno = '%s' AND jyzt = '0' AND msgno in ('3001','1008') AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate, sEndDate, sPayBkCode, sBankno);

		/* noted by chenxm 20141111 DCI改造工作
		   EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_drls              
		   WHERE workdate >= :sBegDate       //账务日期/
		   AND workdate <= :sEndDate       //账务日期/
		   AND paybkcode = :sPayBkCode //清算行号/
		   AND jyzt = '0'
		   AND msgno in ('3001','1008')
		   AND qsbz='0'
		   AND bankno = :sBankno
		   AND substr(dzbz,2,1)='1';*/
	}
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
	  if ( SQLERR )*/
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DBSelectToVar(sErrmsg, &iTmpNum, sSql1 );
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("查询库表失败"));
		LOG(LM_STD,Fmtmsg("查询库表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	iAllNum1 = iAllNum1 + iTmpNum ;

	iTmpNum = 0;    
	memset(sSql1, 0x00, sizeof(sSql1));
	if(strlen(sBankno)==0)   
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssplksfmx WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND czbd = '7' AND qsbz='0' AND substr(kzbz,2,1) = '1'", sBegDate, sEndDate, sPayBkCode);
		
		/*noted by chenxm 20141111 DCI改造工作
		  EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_ssplksfmx              
		  WHERE workdate >= :sBegDate       账务日期
		  AND workdate <= :sEndDate       账务日期
		  AND paybkcode = :sPayBkCode 清算行号
		  AND czbd = '7'
		  AND qsbz='0'
		  AND substr(kzbz,2,1) = '1'; */     

	}
	else
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssplksfmx WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND bankno = '%s' AND czbd = '7' AND qsbz='0' AND substr(kzbz,2,1) = '1'", sBegDate, sEndDate, sPayBkCode,sBankno);

		/* noted by chenxm 20141111 DCI改造工作
		   EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_ssplksfmx              
		   WHERE workdate >= :sBegDate       //账务日期//
		   AND workdate <= :sEndDate       //账务日期//
		   AND paybkcode = :sPayBkCode //清算行号//
		   AND czbd = '7'
		   AND qsbz='0'
		   AND bankno = :sBankno
		   AND substr(kzbz,2,1) = '1';  */    
	}
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DBSelectToVar(sErrmsg, &iTmpNum, sSql1 );
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
	  if ( SQLERR )*/
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("查询库表失败"));
		LOG(LM_STD,Fmtmsg("查询库表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	iAllNum1 = iAllNum1 + iTmpNum ;

	/*iTmpNum = 0;    
	  EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_lsls              
	  WHERE workdate >= :sBegDate       
	  AND workdate <= :sEndDate       
	  AND paybkcode = :sPayBkCode 
	  AND jyzt = '0'
	  AND msgno in ('3001','1008')
	  AND qsbz='0'
	  AND substr(dzbz,2,1)='1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
	  if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("查询库表失败"));
	  LOG(LM_STD,Fmtmsg("查询库表失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }
	  iAllNum1 = iAllNum1 + iTmpNum ;

	  iTmpNum = 0;    
	  EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_ssplksfmx_ls              
	  WHERE workdate >= :sBegDate       
	  AND workdate <= :sEndDate       
	  AND paybkcode = :sPayBkCode 
	  AND czbd = '7'
	  AND qsbz='0'
	  AND substr(kzbz,2,1) = '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
	  if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("查询库表失败"));
	  LOG(LM_STD,Fmtmsg("查询库表失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }*/

	iAllNum1 = iAllNum1 + iTmpNum ;
	if ( iAllNum1 == 0 )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("本机构无此报表数据"));
		LOG(LM_STD,Fmtmsg("本机构无此报表数据[%s]", iAllNum1 ), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;        
	}    

	/*打开文件*/
	fp=fopen(sFile,"w");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24493, Fmtmsg("建立付款行清单报表失败"));
		LOG(LM_STD,Fmtmsg("建立付款行清单报表失败[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL; 
	}    

	fprintf(fp,"                                             横向联网业务统计报表 \n");
	fprintf(fp,"                                                     付款行行号：%s   统计日期：%s -- %s \n",sPayBkCode,sBegDate,sEndDate);
	/*modify by wangw 去掉地区代号*/   
	fprintf(fp,"    机构代号  对账批次    总笔数        总金额   实扣笔数        金额     批扣笔数        金额      银缴笔数      金额\n");


	/*定义游标--modify by wangw 20120913 根据机构和对账批次汇总*/
	memset(sSql1, 0x00, sizeof(sSql1));
	if(strlen(sBankno)==0)   
	{
		sprintf(sSql1, "(SELECT jgdh,chkacctord FROM tips_drls "
				"WHERE workdate >= '%s' "
				"AND workdate <= '%s' "
				"AND paybkcode ='%s' "
				"AND jyzt = '0' "
				"AND msgno in ('3001','1008') "
				"AND qsbz='0' AND substr(dzbz,2,1)='1') "
				"union (SELECT jgdh,chkacctord FROM tips_ssplksfmx "
				"WHERE workdate >= '%s' "
				"AND workdate <= '%s' "
				"AND paybkcode = '%s' "
				"AND czbd = '7' "
				"AND qsbz='0' "
				"AND substr(kzbz,2,1)='1')", sBegDate, sEndDate, sPayBkCode,sBegDate, sEndDate, sPayBkCode);

		/*note by chenxm 20141111 DCI改造工作
		  EXEC SQL DECLARE cur_qshqd CURSOR for 
		  ( SELECT jgdh,chkacctord FROM tips_drls              
		  WHERE workdate >= :sBegDate       //账务日期//
		  AND workdate <= :sEndDate       //账务日期//
		  AND paybkcode = :sPayBkCode //清算行号//
		  AND jyzt = '0'
		  AND msgno in ('3001','1008')
		  AND qsbz='0'
		  AND substr(dzbz,2,1)='1'
		  )
		  union
		  ( SELECT jgdh,chkacctord FROM tips_ssplksfmx              
		  WHERE workdate >= :sBegDate       //账务日期//
		  AND workdate <= :sEndDate       //账务日期//
		  AND paybkcode = :sPayBkCode //清算行号//
		  AND czbd = '7'
		  AND qsbz='0'
		  AND substr(kzbz,2,1)='1'
		  );*/
	}
	else
	{
		sprintf(sSql1, "(SELECT jgdh,chkacctord FROM tips_drls "
				"WHERE workdate >= '%s' "
				"AND workdate <= '%s' "
				"AND paybkcode ='%s' "
				"AND jyzt = '0' "
				"AND msgno in ('3001','1008') "
				"AND bankno = '%s' "
				"AND qsbz='0' "
				"AND substr(dzbz,2,1)='1') "
				"union (SELECT jgdh,chkacctord FROM tips_ssplksfmx "
				"WHERE workdate >= '%s' "
				"AND workdate <= '%s' "
				"AND paybkcode = '%s' "
				"AND czbd = '7' "
				"AND bankno = '%s' "
				"AND qsbz='0' "
				"AND substr(kzbz,2,1)='1')", sBegDate, sEndDate, sPayBkCode,sBankno,sBegDate, sEndDate, sPayBkCode,sBankno);

		/* note by chenxm 20141111 DCI改造工作
		   EXEC SQL DECLARE cur_qshqd CURSOR for   
		   ( SELECT jgdh,chkacctord FROM tips_drls              
		   WHERE workdate >= :sBegDate       //账务日期//
		   AND workdate <= :sEndDate       //账务日期//
		   AND paybkcode = :sPayBkCode //清算行号//
		   AND jyzt = '0'
		   AND msgno in ('3001','1008')
		   AND bankno = :sBankno
		   AND qsbz='0'
		   AND substr(dzbz,2,1)='1'
		   )
		   union
		   ( SELECT jgdh,chkacctord FROM tips_ssplksfmx              
		   WHERE workdate >= :sBegDate       //账务日期//
		   AND workdate <= :sEndDate       //账务日期//
		   AND paybkcode = :sPayBkCode //清算行号//
		   AND czbd = '7'
		   AND bankno = :sBankno
		   AND qsbz='0'
		   AND substr(kzbz,2,1)='1'
		   );*/  
	}
	/*union      
	  ( SELECT jgdh,chkacctord FROM tips_lsls              
	  WHERE workdate >= :sBegDate       
	  AND workdate <= :sEndDate       
	  AND paybkcode = :sPayBkCode 
	  AND jyzt = '0'
	  AND msgno in ('3001','1008')
	  AND qsbz='0'
	  AND substr(dzbz,2,1)='1'
	  )
	  union
	  ( SELECT jgdh,chkacctord FROM tips_ssplksfmx_ls              
	  WHERE workdate >= :sBegDate       
	  AND workdate <= :sEndDate       
	  AND paybkcode = :sPayBkCode 
	  AND czbd = '7'
	  AND qsbz='0'
	  AND substr(kzbz,2,1)='1'
	  )
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERR")
	  noted by chenxm 20141111 DCI改造工作
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("声明游标失败"));
	  LOG(LM_STD,Fmtmsg("声明cur_qshqd游标失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }  */
	/*打开游标*/
	/*EXEC SQL OPEN cur_qshqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_qshqd",sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("打开游标失败"));
	  LOG(LM_STD,Fmtmsg("打开cur_qshqd游标失败"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  } */
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}

	for (i=1, iFlag=0;; i++)
	{
		memset(sDzpc, 0x00, sizeof(sDzpc));
		memset(sJgdh, 0x00, sizeof(sJgdh));
		memset(str_Jgdh, 0x00, sizeof(str_Jgdh));
		/*EXEC SQL FETCH cur_qshqd INTO :sJgdh,:sDzpc;*/
		iSqlRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
		if(iSqlRet <=0)
			break;
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_qshqd",sqlca.sqlcode),"ERR")
		  if (SQLERR)
		  {
		  LOG(LM_STD,Fmtmsg("从cur_qshqd游标获取数据失败"),"ERROR");
		  iFlag = -1;
		  break;
		  }
		  if (SQLNOTFOUND)
		  if(iSqlRet == 0)
		  {
		  break; 
		  }*/
		sprintf( sJgdh, "%s", DCIFieldAsString( cur, 0 ) );
		sprintf( sDzpc, "%s", DCIFieldAsString( cur, 1 ) );
		
		trim(sJgdh);
		trim(sDzpc);
		LOG(LM_DEBUG,Fmtmsg("sJgdh[%s]...",sJgdh),"INFO") 
				
		iSumNum=0;
		dSumAmt=0.00;
		/*统计该机构实扣交易*/
		iAllNum1=0;
		dAllAmt1=0.00;
		iTmpNum=0;
		dTmpAmt=0.00;
		memset(sSql1, 0x00, sizeof(sSql1));
		if(strlen(sBankno)==0)   
		{
			sprintf(sSql1, "SELECT COUNT(*),SUM(jyje) FROM tips_drls WHERE workdate >='%s' "
					"AND workdate <='%s' AND paybkcode = '%s' AND chkacctord ='%s' AND jgdh = '%s' AND jyzt = '0' "
					"AND msgno ='3001' AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate,sEndDate,sPayBkCode,sDzpc,sJgdh);
			
			/*noted by chenxm 20141111 DCI改造工作
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
				INTO :iTmpNum,:dTmpAmt
				FROM tips_drls
				WHERE workdate >= :sBegDate       //账务日期//
				AND workdate <= :sEndDate       //账务日期//
				AND paybkcode = :sPayBkCode //付款行号//
				AND chkacctord = :sDzpc
				AND jgdh = :sJgdh
				AND jyzt = '0'
				AND msgno ='3001'
				AND qsbz='0'
				AND substr(dzbz,2,1)='1';*/
		}
		else
		{
			sprintf(sSql1, "SELECT COUNT(*),SUM(jyje) FROM tips_drls WHERE workdate >='%s' "
					"AND workdate <='%s' AND paybkcode = '%s' AND chkacctord ='%s' AND jgdh = '%s' AND jyzt = '0' "
					"AND bankno = '%s' AND msgno ='3001' AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate,sEndDate,sPayBkCode,sDzpc,sJgdh,sBankno);
			/*noted by chenxm 20141111 DCI改造工作
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
				INTO :iTmpNum,:dTmpAmt
				FROM tips_drls
				WHERE workdate >= :sBegDate       账务日期
				AND workdate <= :sEndDate       账务日期
				AND paybkcode = :sPayBkCode 付款行号
				AND chkacctord = :sDzpc
				AND jgdh = :sJgdh
				AND jyzt = '0'
				AND bankno = :sBankno
				AND msgno ='3001'
				AND qsbz='0'
				AND substr(dzbz,2,1)='1';*/
		}
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR");
		  if ( SQLERR )*/
		
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
		iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cTmpNum, &cTmpAmt);
		iTmpNum=atoi(cTmpNum);
		dTmpAmt=atof(cTmpAmt);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag = -3;
			break;
		}  
		if (iTmpNum==0)
		{
			dTmpAmt = 0.00;
		}
		iAllNum1 = iAllNum1 + iTmpNum;
		dAllAmt1 = dAllAmt1 + dTmpAmt;   

		/*统计该机构银行端缴款交易*/
		iAllNum2=0;
		dAllAmt2=0.00;
		iTmpNum=0;
		dTmpAmt=0.00;
		memset(sSql1, 0x00, sizeof(sSql1));
		if(strlen(sBankno)==0)   
		{
			sprintf(sSql1, "SELECT COUNT(*),SUM(jyje) FROM tips_drls WHERE workdate >='%s' "
					"AND workdate <='%s' AND paybkcode = '%s' AND chkacctord ='%s' AND jgdh = '%s' AND jyzt = '0' "
					"AND msgno ='1008' AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate,sEndDate,sPayBkCode,sDzpc,sJgdh);
			/*noted by chenxm 20141111 DCI改造工作
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
			INTO :iTmpNum,:dTmpAmt
			FROM tips_drls
			WHERE workdate >= :sBegDate       //账务日期//
			AND workdate <= :sEndDate       //账务日期//
			AND paybkcode = :sPayBkCode //付款行号//
			AND chkacctord = :sDzpc
			AND jgdh = :sJgdh
			AND jyzt = '0'
			AND msgno ='1008'
			AND qsbz='0'
			AND substr(dzbz,2,1)='1';*/
		}
		else
		{
			sprintf(sSql1, "SELECT COUNT(*),SUM(jyje) FROM tips_drls WHERE workdate >='%s' "
					"AND workdate <='%s' AND paybkcode = '%s' AND chkacctord ='%s' AND jgdh = '%s' AND jyzt = '0' "
					"AND bankno = '%s' AND msgno ='1008' AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate,sEndDate,sPayBkCode,sDzpc,sJgdh,sBankno);
			/* noted by chenxm 20141111 DCI改造工作
			   EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
			INTO :iTmpNum,:dTmpAmt
			FROM tips_drls
			WHERE workdate >= :sBegDate       //账务日期//
			AND workdate <= :sEndDate       //账务日期//
			AND paybkcode = :sPayBkCode //付款行号//
			AND chkacctord = :sDzpc
			AND jgdh = :sJgdh
			AND jyzt = '0'
			AND bankno = :sBankno
			AND msgno ='1008'
			AND qsbz='0'
			AND substr(dzbz,2,1)='1';*/
		}
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
		  if ( SQLERR )*/
		
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
		iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cTmpNum, &cTmpAmt);
		iTmpNum=atoi(cTmpNum);
		dTmpAmt=atof(cTmpAmt);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag = -5;
			break;
		}  
		if (iTmpNum==0)
		{
			dTmpAmt = 0.00;
		}
		iAllNum2 = iAllNum2 + iTmpNum;
		dAllAmt2 = dAllAmt2 + dTmpAmt;


		/*统计该机构批扣交易*/
		iAllNum3=0;
		dAllAmt3=0.00;
		iTmpNum=0;
		dTmpAmt=0.00;
		memset(sSql1, 0x00, sizeof(sSql1));
		if(strlen(sBankno)==0)   
		{
			sprintf(sSql1, "SELECT COUNT(*),SUM(jyje) FROM tips_ssplksfmx WHERE workdate >='%s' "
					"AND workdate <='%s' AND paybkcode = '%s' AND chkacctord ='%s' AND jgdh = '%s' AND czbd = '7' "
					"AND qsbz='0' AND substr(kzbz,2,1)='1'", sBegDate,sEndDate,sPayBkCode,sDzpc,sJgdh);
			/* noted by chenxm 20141111 DCI改造工作
			   EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
				INTO :iTmpNum,:dTmpAmt
				FROM tips_ssplksfmx
				WHERE workdate >= :sBegDate       //账务日期//
				AND workdate <= :sEndDate       //账务日期//
				AND paybkcode = :sPayBkCode //付款行号//
				AND chkacctord = :sDzpc
				AND jgdh = :sJgdh
				AND czbd = '7'
				AND qsbz='0'
				AND substr(kzbz,2,1) = '1';*/
		}
		else
		{
			sprintf(sSql1, "SELECT COUNT(*),SUM(jyje) FROM tips_ssplksfmx WHERE workdate >='%s' "
					"AND workdate <='%s' AND paybkcode = '%s' AND chkacctord ='%s' AND jgdh = '%s' "
					"AND bankno = '%s' AND czbd = '7' AND qsbz='0' AND substr(kzbz,2,1)='1'", sBegDate,sEndDate,sPayBkCode,sDzpc,sJgdh,sBankno);
			/*noted by chenxm 20141111 DCI改造工作
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
			INTO :iTmpNum,:dTmpAmt
			FROM tips_ssplksfmx
			WHERE workdate >= :sBegDate       //账务日期//
			AND workdate <= :sEndDate       //账务日期//
			AND paybkcode = :sPayBkCode //付款行号//
			AND chkacctord = :sDzpc
			AND jgdh = :sJgdh
			AND bankno = :sBankno
			AND czbd = '7'
			AND qsbz='0'
			AND substr(kzbz,2,1) = '1';*/
		}
		
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
		iSqlRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cTmpNum, &cTmpAmt);
		iTmpNum=atoi(cTmpNum);
		dTmpAmt=atof(cTmpAmt);
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag = -7;
			break;
		}  
		if (iTmpNum==0)
		{
			dTmpAmt = 0.00;
		}
		iAllNum3 = iAllNum3 + iTmpNum;
		dAllAmt3 = dAllAmt3 + dTmpAmt;

		iSumNum=iAllNum1+iAllNum2+iAllNum3;
		dSumAmt=dAllAmt1+dAllAmt2+dAllAmt3;
		nSumNum=nSumNum+iSumNum;
		nSumAmt=nSumAmt+dSumAmt;
		strcpy(str_Jgdh,sJgdh);
		/*删除无效数据，当总笔数=0时不打印--modify by wangw 20120913*/
		if(iSumNum == 0)
			continue;
		fprintf(fp,"    %-8.8s  %8s  %8d    %12.2f %8d    %12.2f %8d    %12.2f%8d    %12.2f \n",
				str_Jgdh,sDzpc,iSumNum,dSumAmt,iAllNum1,dAllAmt1,iAllNum3,dAllAmt3,iAllNum2,dAllAmt2);  /*modify by wangw 去掉地区代号*/    
	}    
	//EXEC SQL CLOSE cur_qshqd;
	DCIFreeCursor(cur);

	fprintf(fp,"\n\n\n\n    汇总：\n");
	fprintf(fp,"    总金额：%12.2f              总笔数：%d\n",nSumAmt,nSumNum);

	fclose(fp);

	if (iFlag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("生成付款行清单报表失败"));
		LOG(LM_STD,Fmtmsg("生成付款行清单报表失败"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle, 0, Fmtmsg("生成付款行清单报表成功"));
	LOG(LM_STD,Fmtmsg("生成付款行清单报表成功"),"INFO");
	return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_QryDZBPMX
  组件名称: 查询对账不平明细

  组件功能: 
  查询对账不平明细
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

  主要操作库表:
  表名              操作
  对账不平登记表	tips_dzbpdj

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年05月15日
  修改日期: 20141105 modify by chenxm DCI改造工作(done)
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_QryDZBPMX(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	SDB_TIPS_DZBPDJ stDzbpdj;
	char sChkDate[8+1];/* 对账日期 */
	char sChkAcctOrd[4+1];/* 对账批次 */
	char sDzlx[1+1];/* 对账类型 */
	char sSql[512];
	/*EXEC SQL END   DECLARE SECTION;*/

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char sDzbpFile[256];
	char sLine[256];
	char sSysDate[8+1];
	char sDzzt[1+1];
	FILE *fp;
	int iret = 0;
	int iFlag = 1;
	int iSqlRet = -1;
	int  i;
	CURSOR cur;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(4);
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"对账日期"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"对账批次"); 
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));    
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzlx, 0x00, sizeof(sDzlx));
	COMP_GETPARSEPARAS(3,sBuf,"对账类型"); 
	sDzlx[0] = sBuf[0];
	memset(sDzbpFile, 0x00, sizeof(sDzbpFile));
	COMP_GETPARSEPARAS(4,sDzbpFile,"对账文件名"); 
	trim(sDzbpFile);

	LOG(LM_STD,Fmtmsg("查询对账不平明细执行开始,对账日期[%s],对账批次[%s],对账类型[%s]",
				sChkDate, sChkAcctOrd, sDzlx),fpub_GetCompname(lXmlhandle))       

		memset(sSysDate, 0x00, sizeof(sSysDate));
	COMP_SOFTGETXML("/sys/sysdate", sSysDate)

		memset(sSql, 0x00, sizeof(sSql));
	if ( sDzlx[0] == '1')/* 与主机对账 */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and dzlx = '%s' order by taxorgcode", 
				sChkDate, sDzlx);
	}else /* 日切对账 */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and chkacctord = '%s' and dzlx = '%s' order by taxorgcode", 
				sChkDate, sChkAcctOrd, sDzlx);        
	}        
	/*prepare*/
	//add by chenxm 20141105 DCI改造工作
	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}

	/*EXEC SQL PREPARE sql_qrydzbpdj FROM :sSql;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrydzbpdj",sqlca.sqlcode),"ERROR"); */   
	/*declare*/
	/*EXEC SQL DECLARE cur_dzbpdj_cxmx CURSOR for sql_qrydzbpdj;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxmx",sqlca.sqlcode),"ERROR");

	  EXEC SQL OPEN cur_dzbpdj_cxmx;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxmx", sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle,24409, "打开游标失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX打开cur_dzbpdj_cxmx游标失败"),
	  fpub_GetCompname(lXmlhandle))
	  }*/

	fp=fopen(sDzbpFile,"w");
	if ( fp == NULL )
	{
		//EXEC SQL CLOSE cur_dzbpdj_cxmx;
		DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("打开对账不平明细文件失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX打开对账不平明细文件失败[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	fprintf(fp,"                             %s\n", "对账不平明细报表");
	fprintf(fp,"    对账日期:%s %s                                 报表日期:%s\n", 
			sChkDate, sChkAcctOrd,sSysDate);
	fprintf(fp,"标志  征收机关代码  委托日期  交易流水号        金额        付款账号  \n", sChkDate, sSysDate);
	/*开始循环*/
	for (i=1,iFlag=0;;i++)
	{
		memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));        
		//EXEC SQL FETCH cur_dzbpdj_cxmx INTO :stDzbpdj;
		//SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzbpdj_cxmx",sqlca.sqlcode),"ERROR");
		iSqlRet = DBFetch(cur, SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ),&stDzbpdj,sErrmsg);
		//if ( SQLERR )
		if(iSqlRet < 0)
		{  
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-1;
			LOG(LM_STD,Fmtmsg("ChkYHJKXX从cur_dzbpdj_cxmx游标获取数据失败"),"ERROR");
			break;
		}
		//if ( SQLNOTFOUND )
		if(iSqlRet == 0)
			break;

		memset(sDzzt, 0x00, sizeof(sDzzt));
		if(   strcmp(stDzbpdj.dzjg, "39" ) == 0 
				||strcmp(stDzbpdj.dzjg, "92" ) == 0
				||strcmp(stDzbpdj.dzjg, "12" ) == 0
		  )
		{
			sDzzt[0] = '+' ;  
		}else if(   strcmp(stDzbpdj.dzjg, "29" ) == 0 
				||strcmp(stDzbpdj.dzjg, "93" ) == 0
				)
		{
			sDzzt[0] = '-' ;
		}
		memset(sLine, 0x00, sizeof(sLine));

		/* mod by tuql 20090912 %20.20s-->%32.32s */
		snprintf(sLine, sizeof(sLine), "%2.2s    %12.12s  %8.8s  %8.8s    %12.2f    %32.32s \n", 
				sDzzt, stDzbpdj.taxorgcode, stDzbpdj.entrustdate, stDzbpdj.trano, stDzbpdj.jyje, stDzbpdj.jyzh);    
		fprintf(fp,"%s",sLine);    
	}

	fclose(fp);
	//EXEC SQL CLOSE cur_dzbpdj_cxmx;
	DCIFreeCursor(cur);

	if (iFlag < 0)
	{
		fpub_SetMsg(lXmlhandle,24410, "生成对账不平明细报表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX生成对账不平明细报表失败"),
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_DEBUG,Fmtmsg("生成对账不平明细报表处理结束"), fpub_GetCompname(lXmlhandle));      	 
	fpub_SetMsg(lXmlhandle, 0, "生成对账不平明细报表处理结束");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;            
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_QryDZBPMX2
  组件名称: 查询对账不平明细(直接出TIPS与核心间的关系)

  组件功能: 
  查询对账不平明细(直接出TIPS与核心间的关系)
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

  主要操作库表:
  表名              操作
  对账不平登记表	tips_dzbpdj

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年10月19日
  修改日期: 20141111 modify by chenxm DCI改造工作
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_QryDZBPMX2(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	SDB_TIPS_DZBPDJ stDzbpdj;
	char sChkDate[8+1];/* 对账日期 */
	char sChkAcctOrd[4+1];/* 对账批次 */
	char sDzlx[1+1];/* 对账类型 */
	char sSql[256];
	char sPayeeBankNo[12+1];/* 收款行行号 */
	char sPayBkCode[12+1];/* 付款行行号 */
	int  iAllCount;/* 总笔数 */
	double dAllAmt;/* 总金额 */
	char sCnClzt[64];/* 处理状态(中文) */
	//EXEC SQL END   DECLARE SECTION;

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	char sBuf[256];
	char sDzbpFile[256];
	char sLine[256];
	char sSysDate[8+1];
	char sCnYwlx[4+1];
	char sCnDzlx[32];
	FILE *fp;
	int iret = 0;
	int iFlag = 1;
	int  i;
	int iSqlRet = -1;
	CURSOR cur;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(4)
		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"对账日期"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"对账批次"); 
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));    
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzlx, 0x00, sizeof(sDzlx));
	COMP_GETPARSEPARAS(3,sBuf,"对账类型"); 
	sDzlx[0] = sBuf[0];
	memset(sDzbpFile, 0x00, sizeof(sDzbpFile));
	COMP_GETPARSEPARAS(4,sDzbpFile,"对账文件名"); 
	trim(sDzbpFile);

	LOG(LM_STD,Fmtmsg("查询对账不平明细执行开始,对账日期[%s],对账批次[%s],对账类型[%s]",
				sChkDate, sChkAcctOrd, sDzlx),fpub_GetCompname(lXmlhandle))       

		memset(sSysDate, 0x00, sizeof(sSysDate));
	COMP_SOFTGETXML("/sys/sysdate", sSysDate)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
	COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
		pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
		pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));

	memset(sSql, 0x00, sizeof(sSql));
	memset(sCnDzlx, 0x00, sizeof(sCnDzlx));
	if ( sDzlx[0] == '4')/* TIPS有核心无,需补账 */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and chkacctord = '%s' and paybkcode = '%s' and payeebankno = '%s' and dzjg in ('29', '93') order by taxorgcode, entrustdate,trano", 
				sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
		strcpy(sCnDzlx, "TIPS有核心无,需补账");
	}else if ( sDzlx[0] == '5')/* TIPS无核心有,需抹账 */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and paybkcode = '%s' and payeebankno = '%s' and dzjg in ('39', '92', '12') order by taxorgcode, entrustdate,trano", 
				sChkDate, sPayBkCode, sPayeeBankNo); 
		strcpy(sCnDzlx, "TIPS无核心有,需抹账");          
	}else
	{
		LOG(LM_STD,Fmtmsg("对账类型[%s]有误,请确认!", sDzlx),fpub_GetCompname(lXmlhandle));
	}            
	trim(sSql);
	trim(sCnDzlx);
	LOG(LM_STD,Fmtmsg("对账不平明细查询SQL:[%s]", sSql),fpub_GetCompname(lXmlhandle));
	/*prepare*/
	//EXEC SQL PREPARE sql_qrydzbpdj2 FROM :sSql;
	//SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrydzbpdj2",sqlca.sqlcode),"ERROR");    
	/*declare*/
	/*EXEC SQL DECLARE cur_dzbpdj_cxmx2 CURSOR for sql_qrydzbpdj2;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxmx2",sqlca.sqlcode),"ERROR");

	  EXEC SQL OPEN cur_dzbpdj_cxmx2;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxmx2", sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle,24409, "打开游标失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX打开cur_dzbpdj_cxmx游标失败"),
	  fpub_GetCompname(lXmlhandle))
	  }*/

	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}	

	fp=fopen(sDzbpFile,"w");
	if ( fp == NULL )
	{
		/*EXEC SQL CLOSE cur_dzbpdj_cxmx2;*/
		DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("打开对账不平明细文件失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX打开对账不平明细文件失败[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	fprintf(fp,"                             %s(%s)\n", "对账不平明细报表", sCnDzlx);
	fprintf(fp,"TIPS日期:%s %s                                 生成报表系统日期:%s\n", sChkDate,sChkAcctOrd,sSysDate);
	fprintf(fp,"征收机关代码  委托日期  交易流水号  业务种类  扣款日期  主机流水号       金额       付款账号               户  名               处理状态  \n");    
	/*开始循环*/
	iAllCount=0;
	dAllAmt=0.00;
	for (i=1,iFlag=0;;i++)
	{
		memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));        
		/*EXEC SQL FETCH cur_dzbpdj_cxmx2 INTO :stDzbpdj;*/
		iSqlRet = DBFetch(cur, SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);
		/*LERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzbpdj_cxmx2",sqlca.sqlcode),"ERROR");
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{  
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-1;
			LOG(LM_STD,Fmtmsg("ChkYHJKXX从cur_dzbpdj_cxmx2游标获取数据失败"),"ERROR");
			break;
		}
		/*f ( SQLNOTFOUND )*/
		if(iSqlRet == 0)
			break;
		memset(sCnYwlx, 0x00, sizeof(sCnYwlx));
		trim(stDzbpdj.jymc);
		if(strncmp(stDzbpdj.jymc, "3001", 4)==0)
			strcpy(sCnYwlx, "实扣");
		else  if(strncmp(stDzbpdj.jymc, "1008", 4)==0)
			strcpy(sCnYwlx, "银缴");
		else  if(strncmp(stDzbpdj.jymc, "3102", 4)==0)      
			strcpy(sCnYwlx, "批扣");

		memset(sCnClzt, 0x00, sizeof(sCnClzt));
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT num_desc FROM  tips_codelist  WHERE code_name='dzbpdj_clzt' AND num=%d", stDzbpdj.clzt);
		/*EXEC SQL SELECT num_desc INTO :sCnClzt
		  FROM  tips_codelist
		  WHERE code_name='dzbpdj_clzt'
		  AND num=:stDzbpdj.clzt;*/
		iSqlRet = DBSelectToVar(sErrmsg, sCnClzt, sSql1);
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERR")\
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{  
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-2;
			LOG(LM_STD,Fmtmsg("查询对帐登记表的中文处理状态失败"),"ERROR");
			break;
		}
		trim(sCnClzt);        
		memset(sLine, 0x00, sizeof(sLine));
		snprintf(sLine, sizeof(sLine), "%12.12s  %8.8s  %8.8s    %4.4s      %8.8s  %8.8s %12.2f    %24.24s%20.20s%10.10s\n", 
				stDzbpdj.taxorgcode, stDzbpdj.entrustdate, stDzbpdj.trano, sCnYwlx, stDzbpdj.zwrq, stDzbpdj.zjlsh, stDzbpdj.jyje, stDzbpdj.jyzh, stDzbpdj.khmc, sCnClzt);    
		trim(sLine);
		fprintf(fp,"%s",sLine);
		iAllCount += 1;
		dAllAmt = dAllAmt + stDzbpdj.jyje;    
	}
	/*EXEC SQL CLOSE cur_dzbpdj_cxmx2;*/
	DCIFreeCursor(cur);

	fprintf(fp,"%s\n","=====================================================================");
	fprintf(fp,"总笔数:%d             总金额:%.2f", iAllCount, dAllAmt);
	fclose(fp);

	if (iFlag < 0)
	{
		fpub_SetMsg(lXmlhandle,24410, "生成对账不平明细报表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX生成对账不平明细报表失败"),
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_DEBUG,Fmtmsg("生成对账不平明细报表处理结束"), fpub_GetCompname(lXmlhandle));      	 
	fpub_SetMsg(lXmlhandle, 0, "生成对账不平明细报表处理结束");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;            
}
/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_QryDZBPMX2x
  组件名称: 查询对账不平明细(直接出TIPS与核心间的关系,含多个清算国库数据)

  组件功能: 
  查询对账不平明细(直接出TIPS与核心间的关系,含多个清算国库数据)
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

  主要操作库表:
  表名              操作
  对账不平登记表	tips_dzbpdj

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年10月22日
  修改日期: 20141111 modify by chenxm DCI改造工作
  参数使用示例: 
 ************************************************************************/
int prv_tips_qryDZBPMX2x(HXMLTREE lXmlhandle, 
		FILE *fp, 
		char sChkDate[], 
		char sChkAcctOrd[], 
		char sPayBkCode[],
		char sPayeeBankNo[],
		char sDzjg[])
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	SDB_TIPS_DZBPDJ stDzbpdj;
	char sSql[256];
	int  iAllCount;/* 总笔数 */
	double dAllAmt;/* 总金额 */
	char sCnClzt[64];/* 处理状态(中文) */
	//EXEC SQL END   DECLARE SECTION;

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	char sBuf[256];
	char sLine[256];
	char sSysDate[8+1];
	char sCnYwlx[4+1];
	int iret = 0;
	int iSqlRet = -1;
	int iFlag = 1;
	int i;
	CURSOR cur;

	memset(sSysDate, 0x00, sizeof(sSysDate));
	COMP_SOFTGETXML("/sys/sysdate", sSysDate)

		fprintf(fp,"TIPS日期:%s %s                                 生成报表系统日期:%s\n", sChkDate,sChkAcctOrd,sSysDate);        
	fprintf(fp,"付款行行号:%s                                  收款行行号:%s\n", sPayBkCode,sPayeeBankNo);
	fprintf(fp,"征收机关代码  委托日期  交易流水号  业务种类  扣款日期  主机流水号       金额       付款账号               户  名               处理状态  \n");                

	memset(sSql, 0x00, sizeof(sSql));
	snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and paybkcode = '%s' and payeebankno = '%s' and dzjg in %s order by taxorgcode, entrustdate,trano", 
			sChkDate, sPayBkCode, sPayeeBankNo, sDzjg);            
	trim(sSql);
	LOG(LM_STD,Fmtmsg("对账不平明细查询SQL:[%s]", sSql),"prv_tips_qryDZBPMX2x");

	/*prepare*/
	//EXEC SQL PREPARE sql_qrydzbpdj2x FROM :sSql;
	//SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrydzbpdj2x",sqlca.sqlcode),"ERROR");    
	/*declare*/
	/*EXEC SQL DECLARE cur_dzbpdj_cxmx2x CURSOR for sql_qrydzbpdj2x;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxmx2x",sqlca.sqlcode),"ERROR");

	  EXEC SQL OPEN cur_dzbpdj_cxmx2x;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxmx2x", sqlca.sqlcode),"prv_tips_qryDZBPMX2x");
	  if ( SQLERR )
	  {
	  LOG(LM_STD,Fmtmsg("打开cur_dzbpdj_cxmx2x游标失败-2"), "prv_tips_qryDZBPMX2x");        
	  return -2;
	  }*/

	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("数据库准备游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}

	/*开始循环*/
	iAllCount=0;
	dAllAmt=0.00;
	for (i=1,iFlag=0;;i++)
	{
		memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));  
		iSqlRet = DBFetch(cur, SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);	
		/*EXEC SQL FETCH cur_dzbpdj_cxmx2x INTO :stDzbpdj;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzbpdj_cxmx2x",sqlca.sqlcode),"prv_tips_qryDZBPMX2x");
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{  
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-3;
			LOG(LM_STD,Fmtmsg("从cur_dzbpdj_cxmx2x游标获取数据失败-3"),"prv_tips_qryDZBPMX2x");
			break;
		}
		/*if ( SQLNOTFOUND )*/
		if(iSqlRet == 0)
			break;
		memset(sCnYwlx, 0x00, sizeof(sCnYwlx));
		trim(stDzbpdj.jymc);
		if(strncmp(stDzbpdj.jymc, "3001", 4)==0)
			strcpy(sCnYwlx, "实扣");
		else  if(strncmp(stDzbpdj.jymc, "1008", 4)==0)
			strcpy(sCnYwlx, "银缴");
		else  if(strncmp(stDzbpdj.jymc, "3102", 4)==0)      
			strcpy(sCnYwlx, "批扣");

		memset(sCnClzt, 0x00, sizeof(sCnClzt));
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT num_desc FROM  tips_codelist WHERE code_name='dzbpdj_clzt' AND num=%d", stDzbpdj.clzt);
		iSqlRet = DBSelectToVar(sErrmsg, sCnClzt, sSql1);
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"prv_tips_qryDZBPMX2x")*/
		if(iSqlRet < 0);
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-4;
			LOG(LM_STD,Fmtmsg("查询对帐登记表的中文处理状态失败"),"prv_tips_qryDZBPMX2x");
			break;
		}

		/*EXEC SQL SELECT num_desc INTO :sCnClzt
		  FROM  tips_codelist
		  WHERE code_name='dzbpdj_clzt'
		  AND num=:stDzbpdj.clzt;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"prv_tips_qryDZBPMX2x")
		  if ( SQLERR )
		  {  
		  iFlag=-4;
		  LOG(LM_STD,Fmtmsg("查询对帐登记表的中文处理状态失败"),"prv_tips_qryDZBPMX2x");
		  break;
		  }*/
		trim(sCnClzt);        
		memset(sLine, 0x00, sizeof(sLine));
		snprintf(sLine, sizeof(sLine), "%12.12s  %8.8s  %8.8s    %4.4s      %8.8s  %8.8s %12.2f    %24.24s%20.20s%10.10s\n", 
				stDzbpdj.taxorgcode, stDzbpdj.entrustdate, stDzbpdj.trano, sCnYwlx, stDzbpdj.zwrq, stDzbpdj.zjlsh, stDzbpdj.jyje, stDzbpdj.jyzh, stDzbpdj.khmc, sCnClzt);    
		trim(sLine);
		fprintf(fp,"%s",sLine);
		iAllCount += 1;
		dAllAmt = dAllAmt + stDzbpdj.jyje;    
	}
	//EXEC SQL CLOSE cur_dzbpdj_cxmx2x;
	DCIFreeCursor(cur);

	fprintf(fp,"%s\n","=====================================================================");
	fprintf(fp,"总笔数:%d             总金额:%.2f", iAllCount, dAllAmt);

	if (iFlag < 0)
	{
		LOG(LM_STD,Fmtmsg("生成对账不平明细报表失败[%d]", iFlag), "prv_tips_qryDZBPMX2x");        
		return iFlag;
	}

	LOG(LM_DEBUG,Fmtmsg("生成对账不平明细报表结束0"), "prv_tips_qryDZBPMX2x");        
	return 0;         
}   

int prv_tips_qryDZBPMX2xA(HXMLTREE lXmlhandle, 
		FILE *fp, 
		char sChkDate[], 
		char sChkAcctOrd[], 
		char sPayBkCode[],
		char sDzjg[])
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	char sSql[256];
	char sPayeeBankNo[12+1];/* 收款行行号 */
	//*EXEC SQL END   DECLARE SECTION; */
	SDB_TIPS_GKZFH2QSH tips_gkzfh2qsh;

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	char sSql2[256];
	int iFlag=0;
	int i;
	int iSqlRet = -1;
	CURSOR cur;

	memset(sSql, 0x00, sizeof(sSql));
	snprintf(sSql, sizeof(sSql), "select payeebankno from tips_gkzfh2qsh where paybkcode = '%s' order by payeebankno ", 
			sPayBkCode);
	trim(sSql);

	/*prepare*/
	//EXEC SQL PREPARE sql_qrygkzfh2xA FROM :sSql;
	//SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrygkzfh2xA",sqlca.sqlcode),"prv_tips_qryDZBPMX2xA");    
	/*declare*/
	/*EXEC SQL DECLARE cur_dzbpdj_cxgkzfh2xA CURSOR for sql_qrygkzfh2xA;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxgkzfh2xA",sqlca.sqlcode),"prv_tips_qryDZBPMX2xA");

	  EXEC SQL OPEN cur_dzbpdj_cxgkzfh2xA;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_cxgkzfh2xA", sqlca.sqlcode),"prv_tips_qryDZBPMX2xA");
	  if ( SQLERR )
	  {
	  LOG(LM_STD,Fmtmsg("打开cur_dzbpdj_cxgkzfh2x4游标失败-42"), "prv_tips_qryDZBPMX2xA");        
	  return -42;
	  }*/

	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}

	for (i=1,iFlag=0;;i++)
	{
		memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));        
		//EXEC SQL FETCH cur_dzbpdj_cxgkzfh2xA INTO :sPayeeBankNo;

		iSqlRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzbpdj_cxgkzfh2xA",sqlca.sqlcode),"prv_tips_qryDZBPMX2xA");
		  if ( SQLERR )*/
		if(iSqlRet < 0)
		{  
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-43;
			LOG(LM_STD,Fmtmsg("从cur_dzbpdj_cxmx2x4游标获取数据失败-43"),"prv_tips_qryDZBPMX2xA");
			break;
		}
		/* if ( SQLNOTFOUND )*/
		if(iSqlRet == 0)
			break;
		sprintf( sPayeeBankNo, "%s", DCIFieldAsString( cur, 0 ) );

		trim(sPayeeBankNo);
		iFlag = prv_tips_qryDZBPMX2x(lXmlhandle, 
				fp, 
				sChkDate, 
				sChkAcctOrd, 
				sPayBkCode, 
				sPayeeBankNo,
				sDzjg);
		if (iFlag < 0)
		{
			LOG(LM_STD,Fmtmsg("生成对账不平明细报表失败[%d]", iFlag),"prv_tips_qryDZBPMX2xA");
			break;
		}                                              
	}

	//EXEC SQL CLOSE cur_dzbpdj_cxgkzfh2xA;
	DCIFreeCursor(cur);

	if (iFlag < 0)
	{
		LOG(LM_STD,Fmtmsg("生成对账不平明细报表失败[%d]", iFlag), "prv_tips_qryDZBPMX2xA");        
		return iFlag;
	}
	LOG(LM_DEBUG,Fmtmsg("生成对账不平明细报表结束0"), "prv_tips_qryDZBPMX2xA");
	return 0;
}

IRESULT SYW_TIPS_QryDZBPMX2x(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sChkDate[8+1];/* 对账日期 */
	char sChkAcctOrd[4+1];/* 对账批次 */
	char sDzlx[1+1];/* 对账类型 */
	char sSql[256];
	char sPayeeBankNo[12+1];/* 收款行行号 */
	char sPayBkCode[12+1];/* 付款行行号 */
	//EXEC SQL END   DECLARE SECTION;

	char sBuf[256];
	char sDzbpFile[256];
	char sLine[256];
	char sCnDzlx[32];
	char sDzjg[128];
	FILE *fp;
	int iret = 0;
	int iFlag = 1;
	int  i;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(4)
		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"对账日期"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"对账批次"); 
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));    
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzlx, 0x00, sizeof(sDzlx));
	COMP_GETPARSEPARAS(3,sBuf,"对账类型"); 
	sDzlx[0] = sBuf[0];
	memset(sDzbpFile, 0x00, sizeof(sDzbpFile));
	COMP_GETPARSEPARAS(4,sDzbpFile,"对账文件名"); 
	trim(sDzbpFile);

	LOG(LM_STD,Fmtmsg("查询对账不平明细执行开始,对账日期[%s],对账批次[%s],对账类型[%s]",
				sChkDate, sChkAcctOrd, sDzlx),fpub_GetCompname(lXmlhandle))

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
	COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
		pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
		pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));

	LOG(LM_STD,Fmtmsg("收款行行号[%s],付款行行号[%s]",
				sPayeeBankNo, sPayBkCode),fpub_GetCompname(lXmlhandle)) 

		fp=fopen(sDzbpFile,"w");
	if ( fp == NULL )
	{       
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("打开对账不平明细文件失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开对账不平明细文件失败[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	memset(sSql, 0x00, sizeof(sSql));
	memset(sCnDzlx, 0x00, sizeof(sCnDzlx));
	memset(sDzjg, 0x00, sizeof(sDzjg));
	iret = 0;

	if ( sDzlx[0] == '4')/* TIPS有核心无,需补账 */
	{   
		strcpy(sCnDzlx, "TIPS有核心无,需补账");
		snprintf(sDzjg, sizeof(sDzjg),"('29', '93') and chkacctord = '%s' ", sChkAcctOrd);
	}else if ( sDzlx[0] == '5')/* TIPS无核心有,需抹账 */
	{
		strcpy(sCnDzlx, "TIPS无核心有,需抹账");
		strcpy(sDzjg, "('39', '92', '12')");
	}else
	{
		LOG(LM_STD,Fmtmsg("对账类型[%s]有误,请确认!", sDzlx),fpub_GetCompname(lXmlhandle));
	}

	fprintf(fp,"                             %s(%s)\n", "对账不平明细报表", sCnDzlx);        
	if (sPayeeBankNo[0]=='\0')/* 需显示该清算行下的全部清算国库对账不平明细 */
	{            
		iret = prv_tips_qryDZBPMX2xA(lXmlhandle, 
				fp, 
				sChkDate, 
				sChkAcctOrd, 
				sPayBkCode,
				sDzjg);
	}else
	{            
		iret = prv_tips_qryDZBPMX2x(lXmlhandle, 
				fp, 
				sChkDate, 
				sChkAcctOrd, 
				sPayBkCode,
				sPayeeBankNo,
				sDzjg);
	}    
	fclose(fp);      
	if (iret < 0)
	{
		fpub_SetMsg(lXmlhandle,24410, "生成对账不平明细报表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("生成对账不平明细报表失败[%d]",iret),
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_DEBUG,Fmtmsg("生成对账不平明细报表处理结束"), fpub_GetCompname(lXmlhandle));      	 
	fpub_SetMsg(lXmlhandle, 0, "生成对账不平明细报表处理结束");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;            
}


/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_RZMZLJCL
  组件名称: 日终抹账逻辑处理
  程序流程步骤：
  日终抹帐逻辑处理：
  92--与TIPS对帐,我方多
  1.3102批量扣款交易
  2.看tips.ini文件中[HXDZ]PLDZ的值
  2.1 ==0 对平  /tips/ismz=1 需上送核心主机抹帐
  2.2 !=0 判断  /tips/hxzjdzbz值
  2.2.1 ==0 未对帐,并查询tips_dzbpdj表,条件帐务日期、前置流水号、
  对帐类型为1。要是有记录存在，则得到此记录的对帐结果的第1位及处理结果。
  要是处理结果为5，则更新对帐不平登记表的处理状态为5,已处理。
  要是不为5,则若为29-则更新原流水状态为失败，批量交易登记表成功减一笔;
  对帐不平登记表中更新为已处理成功。
  2.2.2 ==1 需上送核心主机抹帐
  2.2.3 ==2 更新原流水状态为失败，批量交易登记表成功减一笔；更新对帐不平登记表（共两条记录）
  的状态。
  2.2.4 ==3 理论上不会出现,暂不处理,需人工核查。
  3.3001实时扣款交易
  3.1判断 /tips/hxzjdzbz值
  3.1.1 ==0 未对帐,需查询tips_dzbpdj表,处理情况类似批量扣款

  39--与核心主机对帐，主机多
  1.3102批量扣款交易 查询tips_ssplksfmx表的kzbz[2],判断其值：
  1.1  ==0 未对帐，并查询tips_dzbpdj表,条件帐务日期、前置流水号、
  对帐类型为3,得到处理状态及对帐结果。若查无此记录，则该笔状态不明，不作处理，结束。
  若对帐结果为92-理论上不会出现,该笔需人工核查，更新对帐不平表记录,结束。
  若对帐结果为93-更新原流水状态为成功，批量交易登记表则加上该笔的对应金额，再更新此笔
  的处理结果及状态。
  1.2  ==1  直接上送核心主机抹帐.
  1.3  ==2  理论上不会出现,该笔需人工核查，更新对帐不平表记录,结束。
  1.4  ==3  更新原流水状态为成功，批量交易登记表则加上该笔的对应金额，再更新此笔
  的处理结果及状态。
  2.3001实时扣款交易,处理情况类似以上。


  组件功能: 自动抹账逻辑处理

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

  使用限制:此组件仅用于日终自动调帐需抹账的逻辑判断处理。

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年11月03日
  修改日期: 20141105 modify by chenxm DCI改造工作(done)
  参数使用示例: 
 ************************************************************************/
int prv_tips_updDzbpmx(	HXMLTREE lXmlhandle, SDB_DZBPMX stDzbpmx)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];    /* 帐务日期 */
	int  iYZhqzlsh;      /* 原前置流水号 */
	char sClzt[1+1];     /* 处理状态 */
	char sClxx[50+1];    /* 处理信息 */
	char sYClzt[1+1];    /* 原处理状态 */
	char sDzlx[1+1];     /* 对账类型 */
	char sZwrq[8+1];     /* 帐务日期 */
	int  iClQzlsh;       /* 处理前置流水号 */
	char sSysTime[6+1];  /* 系统时间 */
	//EXEC SQL END DECLARE SECTION;
	char sBuf[256];
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	int iSqlRet = -1;

	memset(sZwrq, 0x00, sizeof(sZwrq));
	iClQzlsh=0;
	memset(sSysTime, 0x00, sizeof(sSysTime));
	COMP_SOFTGETXML("/tips/zwrq", sZwrq)
		memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
		iClQzlsh=atoi(sBuf);
	COMP_SOFTGETXML("/sys/systime", sSysTime)

		memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYZhqzlsh=0;
	memset(sClzt, 0x00, sizeof(sClzt));
	memset(sClxx, 0x00, sizeof(sClxx));
	memset(sYClzt, 0x00, sizeof(sYClzt));
	memset(sDzlx, 0x00, sizeof(sDzlx));

	pstrcopy(sYZwrq, stDzbpmx.yzwrq, sizeof(sYZwrq));
	iYZhqzlsh=stDzbpmx.yqzlsh;
	pstrcopy(sClzt, stDzbpmx.clzt, sizeof(sClzt));
	pstrcopy(sClxx, stDzbpmx.clxx, sizeof(sClxx));
	pstrcopy(sYClzt, stDzbpmx.yclzt, sizeof(sYClzt));
	pstrcopy(sDzlx, stDzbpmx.dzlx, sizeof(sDzlx));

	iSqlRet = DCIBegin();
	if( iSqlRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}

	if(strcmp(sDzlx,"1")==0)
	{
		// add by chenxm DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, " UPDATE tips_dzbpdj set clzt='%s',clrq='%s',clsj='%s',cllsh=%d,clxx='%s',byzd='1',dzjg='1'||substr(dzjg,1,1) "
				"where zwrq='%s' and zhqzlsh =%d and dzlx='%s' and clzt='%s'",
				sClzt,sZwrq,sSysTime,iClQzlsh,sClxx,sYZwrq,iYZhqzlsh,sDzlx,sYClzt);

		/*EXEC SQL UPDATE tips_dzbpdj 
		  SET clzt=:sClzt,
		  clrq=:sZwrq,
		  clsj=:sSysTime,
		  cllsh=:iClQzlsh,
		  clxx=:sClxx,
		  byzd='1',
		  dzjg='1'||substr(dzjg,1,1)
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYZhqzlsh
		  AND dzlx=:sDzlx
		  AND clzt=:sYClzt;*/
	}
	else if(strcmp(sDzlx,"3")==0)
	{
		// add by chenxm DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, " UPDATE tips_dzbpdj set clzt='%s',clrq='%s',clsj='%s',cllsh=%d,clxx='%s',byzd='1',dzjg=substr(dzjg,1,1)||'1' "
				"where zwrq='%s' and zhqzlsh =%d and dzlx='%s' and clzt='%s'",
				sClzt,sZwrq,sSysTime,iClQzlsh,sClxx,sYZwrq,iYZhqzlsh,sDzlx,sYClzt);

		/*EXEC SQL UPDATE tips_dzbpdj 
		  SET clzt=:sClzt,
		  clrq=:sZwrq,
		  clsj=:sSysTime,
		  cllsh=:iClQzlsh,
		  clxx=:sClxx,
		  byzd='1',
		  dzjg=substr(dzjg,1,1)||'1'
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYZhqzlsh
		  AND dzlx=:sDzlx
		  AND clzt=:sYClzt;*/
	}
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if(SQLERR)*/
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新对帐不平登记表失败[%s][%d][%s][%s]", 
					sYZwrq, iYZhqzlsh, sDzlx, sYClzt),fpub_GetCompname(lXmlhandle))
	}    

	iSqlRet=DCICommit();
	/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
	if ( iSqlRet < 0 )
  {
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
  }
  */
    
	return 0;        
}

int prv_tips_Bz9339(HXMLTREE lXmlhandle,
		char yzwrq[8+1],
		int  yqzlsh,
		char ymsgno[4+1],
		double mzje,
		char pljylsh[8+1],
		char plpch[8+1]
		)                  
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];
	int  iYQzlsh;
	char sYMsgNo[4+1];
	double dMzje;
	char sPljylsh[8+1];
	char sPlpch[8+1]; 
	int iClQzlsh;
	char sZwrq[8+1];/* 帐务日期 */
	char sByzd[40+1];            
	//EXEC SQL END DECLARE SECTION; 
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	SDB_DZBPMX stDzbpmx;
	char sBuf[256];
	int iRet;
	int iSqlRet = -1;

	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYQzlsh=0;
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));
	dMzje=0.00;
	memset(sPljylsh, 0x00, sizeof(sPljylsh));
	memset(sPlpch, 0x00, sizeof(sPlpch));

	pstrcopy(sYZwrq, yzwrq, sizeof(sYZwrq));
	iYQzlsh=yqzlsh;
	pstrcopy(sYMsgNo, ymsgno, sizeof(sYMsgNo));
	dMzje=mzje;
	pstrcopy(sPljylsh, pljylsh, sizeof(sPljylsh));
	pstrcopy(sPlpch, plpch, sizeof(sPlpch));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sZwrq, 0x00, sizeof(sZwrq));
	COMP_SOFTGETXML("/tips/zwrq", sBuf)
		pstrcopy(sZwrq, sBuf, sizeof(sZwrq));

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
		iClQzlsh=atoi(sBuf);

	/* 更新与核心对账不平明细记录 */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='4';
	pstrcopy(stDzbpmx.clxx, "调帐成功", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='1';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9221,LM_STD,Fmtmsg("更新对帐不平登记表失败[%d]",iRet),fpub_GetCompname(lXmlhandle))                                
	}
	memset(sByzd, 0x00, sizeof(sByzd));
	snprintf(sByzd, sizeof(sByzd),"%s%08d", sZwrq, iClQzlsh);
	if (strncmp(sYMsgNo,"3102",4) == 0 )
	{
		/* 更新原流水明细记录 */
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_ssplksfmx SET czbd='7',kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6), xyxx='被日终补帐' "
				"where zwrq ='%s' and plmxxh =%d ",sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			LOGRET(-9222,LM_STD,Fmtmsg("更新批量扣税费明细表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm 

		/*EXEC SQL UPDATE tips_ssplksfmx 
		  SET czbd='7',
		  kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),
		  xyxx='被日终补帐'
		  WHERE zwrq=:sYZwrq
		  AND plmxxh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9222,LM_STD,Fmtmsg("更新批量扣税费明细表失败"),fpub_GetCompname(lXmlhandle))
		  }    */            
		/* 更新批量交易登记表 */
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET rzzbs=rzzbs+1,rzzje=rzzje+%0.2f, "
				"where zwrq ='%s' and pljylsh =%s ",dMzje,sYZwrq, sPljylsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9223,LM_STD,Fmtmsg("更新批量交易登记表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm 

		/*EXEC SQL UPDATE tips_pljydj
		  SET rzzbs=rzzbs+1,
		  rzzje=rzzje+:dMzje
		  WHERE zwrq=:sYZwrq
		  AND pljylsh=:sPljylsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9223,LM_STD,Fmtmsg("更新批量交易登记表失败"),fpub_GetCompname(lXmlhandle))
		  }*/                
	}else
	{
		/* 更新原流水明细记录 */
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
			iClQzlsh=atoi(sBuf);

		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET jyzt='0',dzbz=substr(dzbz,1,1)||'1', entrustdate2='%s',zhqzlsh2=%d,xyxx='被日终补帐' "
				"where zwrq ='%s' and zhqzlsh =%d ",sZwrq,iClQzlsh,sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9224,LM_STD,Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_drls 
		  SET jyzt='0',
		  dzbz=substr(dzbz,1,1)||'1',
		  entrustdate2=:sZwrq,
		  zhqzlsh2=:iClQzlsh,
		  xyxx='被日终补帐'
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9224,LM_STD,Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))
		  } */                 
	} 

	/* 更新与TIPS对账不平登记表 */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='4';
	pstrcopy(stDzbpmx.clxx, "补账成功", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='3';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9225,LM_STD,Fmtmsg("更新对帐不平登记表失败[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}                                                                                                               

	//此处有数据库提交问题
	return 0;    
}

int prv_tips_Mz9229(HXMLTREE lXmlhandle,
		char yzwrq[8+1],
		int  yqzlsh,
		char ymsgno[4+1],
		double mzje,
		char pljylsh[8+1],
		char plpch[8+1]
		)                  
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];
	int  iYQzlsh;
	char sYMsgNo[4+1];
	double dMzje;
	char sPljylsh[8+1];
	char sPlpch[8+1]; 
	int iClQzlsh;
	char sZwrq[8+1];/* 帐务日期 */
	char sByzd[40+1];            
	//EXEC SQL END DECLARE SECTION; 
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	SDB_DZBPMX stDzbpmx;
	char sBuf[256];
	int iRet;
	int iSqlRet = -1;

	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYQzlsh=0;
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));
	dMzje=0.00;
	memset(sPljylsh, 0x00, sizeof(sPljylsh));
	memset(sPlpch, 0x00, sizeof(sPlpch));

	pstrcopy(sYZwrq, yzwrq, sizeof(sYZwrq));
	iYQzlsh=yqzlsh;
	pstrcopy(sYMsgNo, ymsgno, sizeof(sYMsgNo));
	dMzje=mzje;
	pstrcopy(sPljylsh, pljylsh, sizeof(sPljylsh));
	pstrcopy(sPlpch, plpch, sizeof(sPlpch));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sZwrq, 0x00, sizeof(sZwrq));
	COMP_SOFTGETXML("/tips/zwrq", sBuf)
		pstrcopy(sZwrq, sBuf, sizeof(sZwrq));

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
		iClQzlsh=atoi(sBuf);

	/* 更新与核心对账不平明细记录 */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "调帐成功", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='1';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9221,LM_STD,Fmtmsg("更新对帐不平登记表失败[%d]",iRet),fpub_GetCompname(lXmlhandle))                                
	}
	memset(sByzd, 0x00, sizeof(sByzd));
	snprintf(sByzd, sizeof(sByzd),"%s%08d", sZwrq, iClQzlsh);
	if (strncmp(sYMsgNo,"3102",4) == 0 )
	{
		/* 更新原流水明细记录 */
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_ssplksfmx SET czbd='4',kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6), xyxx='被日终补帐' "
				"where zwrq ='%s' and plmxxh =%d ",sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9222,LM_STD,Fmtmsg("更新批量扣税费明细表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm 

		/*EXEC SQL UPDATE tips_ssplksfmx 
		  SET czbd='4',
		  kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),
		  xyxx='被日终抹帐'
		  WHERE zwrq=:sYZwrq
		  AND plmxxh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9222,LM_STD,Fmtmsg("更新批量扣税费明细表失败"),fpub_GetCompname(lXmlhandle))
		  }  */              
		/* 更新批量交易登记表 */
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET rzzbs=rzzbs-1,rzzje=rzzje-%0.2f "
				"where zwrq ='%s' and pljylsh =%s ",dMzje,sYZwrq, sPljylsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9223,LM_STD,Fmtmsg("更新批量交易登记表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_pljydj
		  SET rzzbs=rzzbs-1,
		  rzzje=rzzje-:dMzje
		  WHERE zwrq=:sYZwrq
		  AND pljylsh=:sPljylsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9223,LM_STD,Fmtmsg("更新批量交易登记表失败"),fpub_GetCompname(lXmlhandle))
		  }  */              
	}else
	{
		/* 更新原流水明细记录 */
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
			iClQzlsh=atoi(sBuf);

		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET jyzt='3',dzbz=substr(dzbz,1,1)||'1', "
			"entrustdate2='%s',zhqzlsh2=%d,xyxx='被日终补帐' "
				"where zwrq ='%s' and zhqzlsh =%d ",sZwrq,iClQzlsh,sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9224,LM_STD,Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_drls 
		  SET jyzt='3',
		  dzbz=substr(dzbz,1,1)||'1',
		  entrustdate2=:sZwrq,
		  zhqzlsh2=:iClQzlsh,
		  xyxx='被日终抹帐'
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9224,LM_STD,Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))
		  } */                   
	} 

	/* 更新与TIPS对账不平登记表 */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "抹账成功", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='3';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9225,LM_STD,Fmtmsg("更新对帐不平登记表失败[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}                                                                                                               

	return 0;    
}

int prv_tips_Mz3993(HXMLTREE lXmlhandle,
		char yzwrq[8+1],
		int  yqzlsh,
		char ymsgno[4+1],
		double mzje,
		char pljylsh[8+1],
		char plpch[8+1]
		)                  
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];
	int  iYQzlsh;
	char sYMsgNo[4+1];
	double dMzje;
	char sPljylsh[8+1];
	char sPlpch[8+1];    
	int iClQzlsh;
	char sZwrq[8+1];/* 帐务日期 */
	char sByzd[40+1];
	//EXEC SQL END DECLARE SECTION; 

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	SDB_DZBPMX stDzbpmx;
	char sBuf[256];
	int iRet;
	int iSqlRet = -1;

	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYQzlsh=0;
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));
	dMzje=0.00;
	memset(sPljylsh, 0x00, sizeof(sPljylsh));
	memset(sPlpch, 0x00, sizeof(sPlpch));

	pstrcopy(sYZwrq, yzwrq, sizeof(sYZwrq));
	iYQzlsh=yqzlsh;
	pstrcopy(sYMsgNo, ymsgno, sizeof(sYMsgNo));
	dMzje=mzje;
	pstrcopy(sPljylsh, pljylsh, sizeof(sPljylsh));
	pstrcopy(sPlpch, plpch, sizeof(sPlpch));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sZwrq, 0x00, sizeof(sZwrq));
	COMP_SOFTGETXML("/tips/zwrq", sBuf)
		pstrcopy(sZwrq, sBuf, sizeof(sZwrq));

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
		iClQzlsh=atoi(sBuf);

	/* 更新与核心对账不平明细记录 */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "调帐成功", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='3';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-3931,LM_STD,Fmtmsg("更新对帐不平登记表失败[%d]",iRet),fpub_GetCompname(lXmlhandle))                                
	}
	memset(sByzd, 0x00, sizeof(sByzd));
	snprintf(sByzd, sizeof(sByzd),"%s%08d", sZwrq, iClQzlsh);
	if (strncmp(sYMsgNo,"3102",4) == 0 )
	{
		/* 更新原流水明细记录 */
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_ssplksfmx SET czbd='7',xym='90000',"
			"kzbz='1'||substr(kzbz,2,1)||substr(kzbz,3,6), xyxx='被日终抹帐成功' "
				"where zwrq ='%s' and plmxxh =%d ",sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-3932,LM_STD,Fmtmsg("更新批量扣税费明细表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm 

		/*EXEC SQL UPDATE tips_ssplksfmx 
		  SET czbd='7',
		  xym='90000',
		  kzbz='1'||substr(kzbz,2,1)||substr(kzbz,3,6),
		  xyxx='被日终抹帐成功'
		  WHERE zwrq=:sYZwrq
		  AND plmxxh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-3932,LM_STD,Fmtmsg("更新批量扣税费明细表失败"),fpub_GetCompname(lXmlhandle))
		  } */               
		/* 更新批量交易登记表 */
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET rzzbs=rzzbs+1,rzzje=rzzje+%0.2f "
				"where zwrq ='%s' and pljylsh =%s ",dMzje,sYZwrq, sPljylsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-3933,LM_STD,Fmtmsg("更新批量交易登记表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_pljydj
		  SET rzzbs=rzzbs+1,
		  rzzje=rzzje+:dMzje
		  WHERE zwrq=:sYZwrq
		  AND pljylsh=:sPljylsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-3933,LM_STD,Fmtmsg("更新批量交易登记表失败"),fpub_GetCompname(lXmlhandle))
		  } */              
	}else
	{
		/* 更新原流水明细记录 */
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET jyzt='0',dzbz='1'||substr(dzbz,2,1), "
			"entrustdate2='%s',zhqzlsh2=%d,xym='90000',xyxx='被日终抹帐成功' "
				"where zwrq ='%s' and zhqzlsh =%d ",sZwrq,iClQzlsh,sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-3934,LM_STD,Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_drls 
		  SET jyzt='0',
		  dzbz='1'||substr(dzbz,2,1),
		  entrustdate2=:sZwrq,
		  zhqzlsh2=:iClQzlsh,
		  xym='90000',
		  xyxx='被日终抹帐成功'
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-3934,LM_STD,Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))
		  } */                   
	} 

	/* 更新与TIPS对账不平登记表 */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "抹账成功", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='1';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9225,LM_STD,Fmtmsg("更新对帐不平登记表失败[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}                                                                                                               

	return 0;

}

/* 自动补账93 */
int prv_tips_Bz93(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* 对账结果 */
	char sYZwrq[8+1];/* 原帐务日期 */
	int  iYQzlsh;/* 原前置流水号 */
	double dMzje;/* 抹账金额 */
	char sPljylsh[8+1];/* 原批量流水号 */
	char sPlpch[8+1];/* 原批量批次号 */
	int iClQzlsh;/* 处理前置流水号 */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */    
	char sIniFile[256];
	char sIsPldz[1+1];/* 核心批量是否参与对账 */
	int iMz=0;/* 是否需补账 */
	int iRet;
	int iSqlRet = -1;
	SDB_DZBPMX stDzbpmx;
	HXMLTREE lXmlhandle ;/* add by tuql 20091114 */

	/* add by tuql 20091114 */
	lXmlhandle=stMz.lXmlhandle;
	fpub_InitSoComp(lXmlhandle);

	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYQzlsh=0;

	pstrcopy(sYZwrq, stMz.yzwrq, sizeof(sYZwrq));
	iYQzlsh=stMz.yqzlsh;

	/* add by tuql 20091114 */
	memset(yzwrq, 0x00, sizeof(yzwrq));
	yzhqzlsh=0;
	pstrcopy(yzwrq, sYZwrq, sizeof(yzwrq));
	yzhqzlsh=iYQzlsh;

	if (strncmp(stMz.ymsgno,"3102",4) == 0 )
	{
		memset(sIniFile, 0x00, sizeof(sIniFile));
		snprintf(sIniFile, sizeof(sIniFile), "%s/etc/tips.ini", getenv("HOME"));
		memset(sBuf, 0x00, sizeof(sBuf));
		memset(sIsPldz, 0x00, sizeof(sIsPldz));
		if(ExGetCfgItem(sIniFile,"HXDZ","PLDZ",sBuf,sizeof(sBuf))<0)
		{
			sBuf[0]='1';/* 1-参加(缺省) */
		}
		pstrcopy(sIsPldz, sBuf, sizeof(sIsPldz));

		if ( sIsPldz[0] == '0')/* 核心批量不参与对帐,此时需上送核心抹账 */
		{
			LOG(LM_STD,Fmtmsg("本条记录XVV由于TIPS无,前置与核心不对账,缺省对平,需上核心补账处理."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录XVV由于TIPS无,前置与核心不对账,缺省对平,需上核心补账处理."));
			iMz=1;
			return iMz;
		}
	}

	/* 判断原流水与核心主机的对账标志 */
	switch (atoi(stMz.dzbz))
	{
		case 0 : /* 与核心未对账,但还是要到对帐不平登记表中去看一下 */
			/* 到tips_dzbpdj表中查询是否有单边帐存在*/
			memset(sDzjg, 0x00, sizeof(sDzjg));

			//add by chenxm 20141105 DCI改造工作
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT dzjg  FROM tips_dzbpdj \
				WHERE zwrq='%s' and zhqzlsh=%d and dzlx='1' and clzt='0'",sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToVar(sErrmsg, sDzjg, sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOGRET(-921,LM_STD,Fmtmsg("查询对帐不平登记表失败"), fpub_GetCompname(stMz.lXmlhandle))
			}
			//add end by chenxm

			/*EXEC SQL SELECT dzjg INTO :sDzjg   // note by chenxm  20141106 	DCI改造工作
			  FROM tips_dzbpdj
			  WHERE zwrq=:sYZwrq
			  AND zhqzlsh=:iYQzlsh
			  AND dzlx='1'
			  AND clzt='0';
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if(SQLERR)
			  {
			  LOGRET(-921,LM_STD,Fmtmsg("查询对帐不平登记表失败"),
			  fpub_GetCompname(stMz.lXmlhandle))
			  }*/
			//if (SQLNOTFOUND)/* 如找不到,直接上送核心补账 */
			if(iSqlRet == 0)
			{
				LOG(LM_STD,Fmtmsg("本条记录XV?由于TIPS有,前置无但未与核心对账,需上核心补账处理."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("本条记录XV?由于TIPS有,前置无但未与核心对账,需上核心补账处理."));
				  iMz=1;
				/*iRet=prv_tips_Bz9339(stMz.lXmlhandle,
						yzwrq, /* mod by tuql 20091214 sYZwrq, 
						yzhqzlsh, /* mod by tuql 20091214 iYQzlsh, 
						stMz.ymsgno,
						stMz.mzje,/* mod by tuql 20091118  dMzje
						stMz.pljylsh,/* mod by tuql 20091118  sPljylsh
						stMz.plpch /* mod by tuql 20091118  sPlpch
						);
				if (iRet<0)
				{
					return iRet;
				} */
				return iMz;
			}
			break;
		default:
			LOG(LM_STD,Fmtmsg("本条记录XV?已对账."),"INFO");
			break;                
	}/* end switch (stMz.dzbz)) */    
	return iMz;
}

/* 自动抹账92 */
int prv_tips_Mz92(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* 对账结果 */
	char sYZwrq[8+1];/* 原帐务日期 */
	int  iYQzlsh;/* 原前置流水号 */
	double dMzje;/* 抹账金额 */
	char sPljylsh[8+1];/* 原批量流水号 */
	char sPlpch[8+1];/* 原批量批次号 */
	int iClQzlsh;/* 处理前置流水号 */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */    
	char sIniFile[256];
	char sIsPldz[1+1];/* 核心批量是否参与对账 */
	int iMz=0;/* 是否需抹账 */
	int iRet;
	int iSqlRet = -1;
	SDB_DZBPMX stDzbpmx;
	HXMLTREE lXmlhandle ;/* add by tuql 20091114 */

	/* add by tuql 20091114 */
	lXmlhandle=stMz.lXmlhandle;
	fpub_InitSoComp(lXmlhandle);

	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYQzlsh=0;

	pstrcopy(sYZwrq, stMz.yzwrq, sizeof(sYZwrq));
	iYQzlsh=stMz.yqzlsh;

	/* add by tuql 20091114 */
	memset(yzwrq, 0x00, sizeof(yzwrq));
	yzhqzlsh=0;
	pstrcopy(yzwrq, sYZwrq, sizeof(yzwrq));
	yzhqzlsh=iYQzlsh;

	if (strncmp(stMz.ymsgno,"3102",4) == 0 )
	{
		memset(sIniFile, 0x00, sizeof(sIniFile));
		snprintf(sIniFile, sizeof(sIniFile), "%s/etc/tips.ini", getenv("HOME"));
		memset(sBuf, 0x00, sizeof(sBuf));
		memset(sIsPldz, 0x00, sizeof(sIsPldz));
		if(ExGetCfgItem(sIniFile,"HXDZ","PLDZ",sBuf,sizeof(sBuf))<0)
		{
			sBuf[0]='1';/* 1-参加(缺省) */
		}
		pstrcopy(sIsPldz, sBuf, sizeof(sIsPldz));

		if ( sIsPldz[0] == '0')/* 核心批量不参与对帐,此时需上送核心抹账 */
		{
			LOG(LM_STD,Fmtmsg("本条记录XVV由于TIPS无,前置与核心不对账,缺省对平,需上核心抹账处理."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录XVV由于TIPS无,前置与核心不对账,缺省对平,需上核心抹账处理."));
			iMz=1;
			return iMz;
		}
	}

	/* 判断原流水与核心主机的对账标志 */
	switch (atoi(stMz.dzbz))
	{
		case 0 : /* 与核心未对账,但还是要到对帐不平登记表中去看一下 */
			/* 到tips_dzbpdj表中查询是否有单边帐存在*/
			memset(sDzjg, 0x00, sizeof(sDzjg));
			//add by chenxm 20141105 DCI改造工作
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT dzjg  FROM tips_dzbpdj \
				WHERE zwrq='%s' and zhqzlsh=%d and dzlx='1' and clzt='0'",sYZwrq,iYQzlsh);
      LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
			iSqlRet = DBSelectToVar(sErrmsg, sDzjg, sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOGRET(-921,LM_STD,Fmtmsg("查询对帐不平登记表失败"), fpub_GetCompname(stMz.lXmlhandle))
			}
			//add end by chenxm

			/*EXEC SQL SELECT dzjg INTO :sDzjg
			  FROM tips_dzbpdj
			  WHERE zwrq=:sYZwrq
			  AND zhqzlsh=:iYQzlsh
			  AND dzlx='1'
			  AND clzt='0';
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if(SQLERR)
			  {
			  LOGRET(-921,LM_STD,Fmtmsg("查询对帐不平登记表失败"),
			  fpub_GetCompname(stMz.lXmlhandle))
			  }*/
			//if (SQLNOTFOUND)/* 如找不到,直接上送核心抹账 */
			if(iSqlRet == 0)
			{
				LOG(LM_STD,Fmtmsg("本条记录XV?由于TIPS无,前置有但未与核心对账,需上核心抹账处理."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("本条记录XV?由于TIPS无,前置有但未与核心对账,需上核心抹账处理."));
				iMz=1;
				return iMz;
				
			}
			trim(sDzjg);
			/* 若对账结果为29-与核心对账,我方多,只需将原流水状态更改为失败 */
			if (sDzjg[0]=='2')
			{
				LOG(LM_STD,Fmtmsg("本条记录XVX由于TIPS无,前置有,核心无,将原流水状态更改为失败即可."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("本条记录XVX由于TIPS无,前置有,核心无,将原流水状态更改为失败即可."));
				iRet=prv_tips_Mz9229(stMz.lXmlhandle,
						yzwrq, /* mod by tuql 20091214 sYZwrq, */
						yzhqzlsh, /* mod by tuql 20091214 iYQzlsh, */
						stMz.ymsgno,
						stMz.mzje,/* mod by tuql 20091118  dMzje*/
						stMz.pljylsh,/* mod by tuql 20091118  sPljylsh*/
						stMz.plpch /* mod by tuql 20091118  sPlpch*/
						);
				if (iRet<0)
				{
					return iRet;
				} 
			}else/* 若对账结果为39-与核心对账,他方多,挂账处理,人工核查 */
			{
				/* 更新与TIPS对账不平登记表 */
				LOG(LM_STD,Fmtmsg("本条记录由于TIPS无,前置与核心对账核心多,挂账处理,人工核查."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("本条记录由于TIPS无,前置与核心对账核心多,挂账处理,人工核查."));
				memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
				pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
				stDzbpmx.yqzlsh=iYQzlsh;
				stDzbpmx.clzt[0]='9';
				pstrcopy(stDzbpmx.clxx, "挂账处理,人工核查", sizeof(stDzbpmx.clxx));
				stDzbpmx.dzlx[0]='3';
				stDzbpmx.yclzt[0]='0';
				iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
				if (iRet<0)
				{
					LOGRET(-922,LM_STD,Fmtmsg("更新对帐不平登记表失败"),
							fpub_GetCompname(stMz.lXmlhandle))                                
				}
			}
			break;
		case 1 :/* 与核心对平 */
			LOG(LM_STD,Fmtmsg("本条记录由于TIPS无,前置与核心对平,需上核心抹账处理."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录由于TIPS无,前置与核心对平,需上核心抹账处理."));
			iMz=1;
			break;
		case 2 :/* 与核心对账,我方多 */
			LOG(LM_STD,Fmtmsg("本条记录XVX由于TIPS无,前置有,核心无,将原流水状态更改为失败即可."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录XVX由于TIPS无,前置有,核心无,将原流水状态更改为失败即可."));
			iRet=prv_tips_Mz9229(stMz.lXmlhandle,
					yzwrq, /* mod by tuql 20091214 sYZwrq, */
					yzhqzlsh, /* mod by tuql 20091214 iYQzlsh, */
					stMz.ymsgno,
					stMz.mzje,/* mod by tuql 20091118  dMzje*/
					stMz.pljylsh,/* mod by tuql 20091118  sPljylsh*/
					stMz.plpch /* mod by tuql 20091118  sPlpch*/
					);
			if (iRet<0)
			{
				return iRet;
			}                         
			break;
		case 3 :/* 与核心对账,他方多 */
			/* 更新与TIPS对账不平登记表 */
			LOG(LM_STD,Fmtmsg("本条记录由于TIPS无,前置与核心对账核心多,挂账处理,人工核查."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录由于TIPS无,前置与核心对账核心多,挂账处理,人工核查."));
			memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
			pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
			stDzbpmx.yqzlsh=iYQzlsh;
			stDzbpmx.clzt[0]='9';
			pstrcopy(stDzbpmx.clxx, "挂账处理,人工核查", sizeof(stDzbpmx.clxx));
			stDzbpmx.dzlx[0]='3';
			stDzbpmx.yclzt[0]='0';
			iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
			if (iRet<0)
			{
				LOGRET(-923,LM_STD,Fmtmsg("更新对帐不平登记表失败"),
						fpub_GetCompname(stMz.lXmlhandle))                                
			}
			break;
		default:
			break;                
	}/* end switch (stMz.dzbz)) */    
	return iMz;
}

/* 自动补账29 */
int prv_tips_Bz29(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* 对账结果 */
	char sYZwrq[8+1];/* 原帐务日期 */
	int  iYQzlsh;/* 原前置流水号 */
	double dMzje;/* 抹账金额 */
	char sPljylsh[8+1];/* 原批量流水号 */
	char sPlpch[8+1];/* 原批量批次号 */
	int iClQzlsh;/* 处理前置流水号 */
	char sChkDate[8+1];/* 对账日期 */
	char sChkAcctOrd[4+1];/* 对账批次 */
	char sPayBkCode[12+1];/* 付款行行号 */
	char sPayeeBankNo[12+1];/* 收款行行号 */
	//EXEC SQL END DECLARE SECTION;
	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */
	char sIniFile[256];
	char sIsPldz[1+1];/* 核心批量是否参与对账 */
	int iMz=0;/* 是否需抹账 */
	int iRet;
	SDB_DZBPMX stDzbpmx; 
	HXMLTREE lXmlhandle ;/* add by tuql 20091114 */

	/* add by tuql 20091114 */
	lXmlhandle=stMz.lXmlhandle;
	fpub_InitSoComp(lXmlhandle);

	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYQzlsh=0;

	pstrcopy(sYZwrq, stMz.yzwrq, sizeof(sYZwrq));
	iYQzlsh=stMz.yqzlsh;

	/* add by tuql 20091114 */
	memset(yzwrq, 0x00, sizeof(yzwrq));
	yzhqzlsh=0;
	pstrcopy(yzwrq, sYZwrq, sizeof(yzwrq));
	yzhqzlsh=iYQzlsh;        

	/* 判断原流水与核心主机的对账标志 */
	switch (atoi(stMz.dzbz))
	{
		case 1 :/* 与TIPS对平 */
			LOG(LM_STD,Fmtmsg("本条记录由于核心多,TIPS平,需上核心抹账处理."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录由于核心多,TIPS平,需上核心抹账处理."));
			iMz=1;
			break;
		default:
			break;                
	}/* end switch (stmz.dzbz)) */

	return iMz;
}

/* 自动抹账39 */
int prv_tips_Mz39(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* 对账结果 */
	char sYZwrq[8+1];/* 原帐务日期 */
	int  iYQzlsh;/* 原前置流水号 */
	double dMzje;/* 抹账金额 */
	char sPljylsh[8+1];/* 原批量流水号 */
	char sPlpch[8+1];/* 原批量批次号 */
	int iClQzlsh;/* 处理前置流水号 */
	char sChkDate[8+1];/* 对账日期 */
	char sChkAcctOrd[4+1];/* 对账批次 */
	char sPayBkCode[12+1];/* 付款行行号 */
	char sPayeeBankNo[12+1];/* 收款行行号 */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */
	char sIniFile[256];
	char sIsPldz[1+1];/* 核心批量是否参与对账 */
	int iMz=0;/* 是否需抹账 */
	int iRet;
	int iSqlRet = -1;
	SDB_DZBPMX stDzbpmx; 
	HXMLTREE lXmlhandle ;/* add by tuql 20091114 */

	/* add by tuql 20091114 */
	lXmlhandle=stMz.lXmlhandle;
	fpub_InitSoComp(lXmlhandle);

	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	iYQzlsh=0;

	pstrcopy(sYZwrq, stMz.yzwrq, sizeof(sYZwrq));
	iYQzlsh=stMz.yqzlsh;

	/* add by tuql 20091114 */
	memset(yzwrq, 0x00, sizeof(yzwrq));
	yzhqzlsh=0;
	pstrcopy(yzwrq, sYZwrq, sizeof(yzwrq));
	yzhqzlsh=iYQzlsh;        

	/* 判断原流水与核心主机的对账标志 */
	switch (atoi(stMz.dzbz))
	{
		case 0 : /* 与TIPS未对账,但还是要到对帐不平登记表中去看一下 */
			/* 到tips_dzbpdj表中查询是否有单边帐存在*/
			memset(sDzjg, 0x00, sizeof(sDzjg));

			//add by chenxm 20141105 DCI改造工作
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT dzjg  FROM tips_dzbpdj \
				WHERE zwrq='%s' and zhqzlsh=%d and dzlx='3' and clzt='0'",sYZwrq,iYQzlsh); /* 20150602 修正 dzlx='3' */

			iSqlRet = DBSelectToVar(sErrmsg, sDzjg, sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOGRET(-391,LM_STD,Fmtmsg("查询对帐不平登记表失败"), fpub_GetCompname(stMz.lXmlhandle))
			}
			//add end by chenxm

			/*EXEC SQL SELECT dzjg INTO :sDzjg
			  FROM tips_dzbpdj
			  WHERE zwrq=:sYZwrq
			  AND zhqzlsh=:iYQzlsh
			  AND dzlx='3'
			  AND clzt='0';
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if(SQLERR)
			  {
			  LOGRET(-391,LM_STD,Fmtmsg("查询对帐不平登记表失败"),
			  fpub_GetCompname(stMz.lXmlhandle))
			  }*/

			/* 如找不到,只记录暂不处理 mod by tuql 20091214 此处逻辑判断有问题,
			   应再到tips_ssdzplt表中去查询判断*/
			//if (SQLNOTFOUND)
			if(iSqlRet == 0)
			{
				/* 先到tips_ssdzplt表中去查询此工作日是否已对帐 */
				memset(sChkDate, 0x00, sizeof(sChkDate));
				COMP_SOFTGETXML("/tips/ylsxx/workdate", sChkDate)	/* 20150602 WORKDATE改为小写 */
					memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
				COMP_SOFTGETXML("/tips/ylsxx/paybkcode", sPayBkCode) /* 20150602 PAYBKCODE改为小写 */
					memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
				COMP_SOFTGETXML("/tips/ylsxx/payeebankno", sPayeeBankNo) /* 20150602 PAYEEBANKNO改为小写 */
					memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));

				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT chkacctord  FROM tips_ssdzplt "
					"WHERE chkdate='%s' and paybkcode='%s' and payeebankno='%s' "
						"and chkaccttype='1'",sChkDate,sPayBkCode,sPayeeBankNo);
				LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))  
				iSqlRet = DBSelectToVar(sErrmsg, sChkAcctOrd, sSql1);

				/*EXEC SQL SELECT chkacctord INTO :sChkAcctOrd
				  FROM tips_ssdzplt
				  WHERE chkdate=:sChkDate
				  AND paybkcode=:sPayBkCode
				  AND payeebankno=:sPayeeBankNo
				  AND chkaccttype='1';
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
				  if(SQLERR)*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOGRET(-394,LM_STD,Fmtmsg("查询对帐批量头表失败"),
							fpub_GetCompname(stMz.lXmlhandle))
				}
				//if (SQLNOTFOUND)/* 说明还未进行TIPS日终对账 */
				if(iSqlRet == 0)
				{
					LOG(LM_STD,Fmtmsg("本条记录?XV由于核心多,未与TIPS对账,暂不处理."),"INFO");
					LOG_TiaoZ("mz",Fmtmsg("本条记录?XV由于核心多,未与TIPS对账,暂不处理."));
					iMz=0;
					memset(sBuf, 0x00, sizeof(sBuf));
					sBuf[0]='2';/* ?XV情况,暂不处理 */
					COMP_SOFTSETXML("/tips/ismz", sBuf)
						memset(sBuf, 0x00, sizeof(sBuf));
					snprintf(sBuf, sizeof(sBuf), "%s", "本条记录?XV由于核心多,未与TIPS对账,暂不处理.");
					COMP_SOFTSETXML("/tips/mzinfo", sBuf)
						return iMz;                    
				}                           
				/* 已与TIPS对账,核心多,前置与TIPS都失败,需上核心抹账处理 */
				LOG(LM_STD,Fmtmsg("本条记录XXV由于核心多,前置与TIPS都失败,需上核心抹账处理."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("本条记录XXV由于核心多,前置与TIPS都失败,需上核心抹账处理."));
				memset(sBuf, 0x00, sizeof(sBuf));
				sBuf[0]='4';/* XXV情况,只需更新批量明细状态 */
				COMP_SOFTSETXML("/tips/ismz", sBuf)
					iMz=1;
				return iMz;
			}    
			trim(sDzjg);

			/* 若对账结果为93-与TIPS对账,他方多,只需将原流水状态更改为成功 */
			if (sDzjg[1]=='3')
			{
				LOG(LM_STD,Fmtmsg("本条记录VXV由于核心多,TIPS也多,需将原流水状态更改为成功即可."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("本条记录VXV由于核心多,TIPS也多,需将原流水状态更改为成功即可."));
				iRet=prv_tips_Mz3993(stMz.lXmlhandle,
						yzwrq, /* mod by tuql 20091214 sYZwrq, */
						yzhqzlsh, /* mod by tuql 20091214 iYQzlsh, */
						stMz.ymsgno,
						stMz.mzje,
						stMz.pljylsh,
						stMz.plpch
						);
				if (iRet<0)
				{
					return iRet;
				} 
			}else/* 若对账结果为92-与TIPS对账,我方多,挂账处理,人工核查 */
			{
				/* 更新与TIPS对账不平登记表 */
				LOG(LM_STD,Fmtmsg("本条记录由于核心多,TIPS少,挂账处理,人工核查."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("本条记录由于核心多,TIPS少,挂账处理,人工核查."));
				memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
				pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
				stDzbpmx.yqzlsh=iYQzlsh;
				stDzbpmx.clzt[0]='9';
				pstrcopy(stDzbpmx.clxx, "挂账处理,人工核查", sizeof(stDzbpmx.clxx));
				stDzbpmx.dzlx[0]='1';
				stDzbpmx.yclzt[0]='0';
				iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
				if (iRet<0)
				{
					LOGRET(-392,LM_STD,Fmtmsg("更新对帐不平登记表失败"),
							fpub_GetCompname(stMz.lXmlhandle))                                
				}
			}
			break;
		case 1 :/* 与TIPS对平 */
			LOG(LM_STD,Fmtmsg("本条记录由于核心多,TIPS平,需上核心抹账处理."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录由于核心多,TIPS平,需上核心抹账处理."));
			iMz=1;
			break;
		case 3 :/* 与TIPS对账,我方多 */
			LOG(LM_STD,Fmtmsg("本条记录VXV由于核心多,TIPS也多,需将原流水状态更改为成功即可."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录VXV由于核心多,TIPS也多,需将原流水状态更改为成功即可."));
			iRet=prv_tips_Mz3993(stMz.lXmlhandle,
					yzwrq, /* mod by tuql 20091214 sYZwrq, */
					yzhqzlsh, /* mod by tuql 20091214 iYQzlsh, */
					stMz.ymsgno,
					stMz.mzje,
					stMz.pljylsh,
					stMz.plpch
					);
			if (iRet<0)
			{
				return iRet;
			}                         
			break;
		case 2 :/* 与TIPS对账,我方多 */
			/* 更新与TIPS对账不平登记表 */
			LOG(LM_STD,Fmtmsg("本条记录由于核心多,TIPS少,挂账处理,人工核查."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("本条记录由于核心多,TIPS少,挂账处理,人工核查."));
			memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
			pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
			stDzbpmx.yqzlsh=iYQzlsh;
			stDzbpmx.clzt[0]='9';
			pstrcopy(stDzbpmx.clxx, "挂账处理,人工核查", sizeof(stDzbpmx.clxx));
			stDzbpmx.dzlx[0]='1';
			stDzbpmx.yclzt[0]='0';
			iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
			if (iRet<0)
			{
				LOGRET(-393,LM_STD,Fmtmsg("更新对帐不平登记表失败"),
						fpub_GetCompname(stMz.lXmlhandle))                                
			}
			break;
		default:
			break;                
	}/* end switch (stmz.dzbz)) */

	return iMz;
}

IRESULT SYW_TIPS_RZBZLJCL(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];    /* 原帐务日期 */
	int iYQzlsh;         /* 原前置流水号 */
	char sYMsgNo[4+1];   /* 原交易代码 */
	char sDzlx[1+1];     /* 原对帐类型 */
	char sDzjg[2+1];     /* 原对帐结果 */
	char sDzjg2[2+1];    /* 对帐结果2 */
	char sClzt[1+1];     /* 处理状态 */
	char sClxx[50+1];    /* 处理信息 */
	char sYDzbz[8+1];    /* 原对帐标志 */
	int  iCount;         /* 记录数 */
	//EXEC SQL END DECLARE SECTION;
	SDB_MZ  stMz;
	char sBuf[256];
	char sIniFile[256];
	char sIsPldz[1+1];/* 核心批量是否参与对账 */
	int iMz=0;/* 是否需抹账 */
	char sHxDzbz[1+1];/* 核心对帐标志 */
	char sTiDzbz[1+1];/* 与TIPS对帐标志 */
	int iRet=-1;
	double dMzje;
	char sPljylsh[8+1];/* 批量交易流水号 */
	char sPlpch[8+1];/* 批量批次号 */

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(6)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	COMP_GETPARSEPARAS(1,sBuf,"原帐务日期");
	pstrcopy(sYZwrq, sBuf, sizeof(sYZwrq));

	memset(sBuf, 0x00, sizeof(sBuf));
	iYQzlsh=0;
	COMP_GETPARSEPARAS(2,sBuf,"原前置流水号");
	iYQzlsh=atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(3,sBuf,"原对账类型");
	pstrcopy(sDzlx, sBuf, sizeof(sDzlx));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(4,sBuf,"原交易代码");
	pstrcopy(sYMsgNo, sBuf, sizeof(sYMsgNo));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzjg, 0x00, sizeof(sDzjg));    
	COMP_GETPARSEPARAS(5,sBuf,"对帐结果");
	pstrcopy(sDzjg, sBuf, sizeof(sDzjg));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYDzbz, 0x00, sizeof(sYDzbz));    
	COMP_GETPARSEPARAS(6,sBuf,"对帐标志");
	pstrcopy(sYDzbz, sBuf, sizeof(sYDzbz));

	memset(sHxDzbz, 0x00, sizeof(sHxDzbz));
	memset(sTiDzbz, 0x00, sizeof(sTiDzbz));
	sHxDzbz[0]=sYDzbz[0];
	sTiDzbz[0]=sYDzbz[1];

	LOG(LM_STD,Fmtmsg("自动补账逻辑处理...原帐务日期[%s]原前置流水号[%d]原对账类型[%s]",
				sYZwrq, iYQzlsh, sDzlx),fpub_GetCompname(lXmlhandle));     
	LOG(LM_STD,Fmtmsg("原交易代码[%s]原对帐结果[%s]原对帐标志[%s%s]",
				sYMsgNo, sDzjg, sHxDzbz, sTiDzbz),fpub_GetCompname(lXmlhandle)); 
	LOG_TiaoZ("mz",Fmtmsg("原帐务日期[%s]原前置流水号[%d]原对账类型[%s]原交易代码[%s]原对帐结果[%s]原对帐标志[%s%s]",
				sYZwrq, iYQzlsh, sDzlx, sYMsgNo, sDzjg, sHxDzbz, sTiDzbz));
	memset(sBuf, 0x00, sizeof(sBuf));
	dMzje=0.00;
	COMP_SOFTGETXML("/tips/mzje", sBuf)
		dMzje=atof(sBuf);

	memset(sPljylsh, 0x00, sizeof(sPljylsh));
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/pljylsh", sBuf)
		pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));

	memset(sPlpch, 0x00, sizeof(sPlpch));
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/plpch", sBuf)
		pstrcopy(sPlpch, sBuf, sizeof(sPlpch));

	iRet=-1;
	memset(&stMz, 0x00, sizeof(stMz));
	stMz.lXmlhandle=lXmlhandle;
	pstrcopy(stMz.yzwrq, sYZwrq, sizeof(stMz.yzwrq));
	stMz.yqzlsh=iYQzlsh;
	pstrcopy(stMz.ymsgno, sYMsgNo, sizeof(stMz.ymsgno));
	stMz.mzje=dMzje;
	pstrcopy(stMz.pljylsh, sPljylsh, sizeof(stMz.pljylsh));
	pstrcopy(stMz.plpch, sPlpch, sizeof(stMz.plpch));
	/* 若为93--与TIPS对帐,TIPS多 */
	if (sDzjg[1]=='3' )
	{
		LOG(LM_STD,Fmtmsg("--------%s---------",sHxDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sHxDzbz[0];
		iRet=prv_tips_Bz93(stMz);
	}else if (sDzjg[0]=='2' )/* 29--与核心主机对帐，前置多 */
	{
		LOG(LM_STD,Fmtmsg("********%s*********",sTiDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sTiDzbz[0];
		iRet=prv_tips_Bz29(stMz);
	}    
	if(iRet<0)
	{
		fpub_SetMsg(lXmlhandle, 24420, "本记录补账失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("本记录补账失败[%d]",iRet),
				fpub_GetCompname(lXmlhandle))        
	}        
	fpub_SetCompStatus(lXmlhandle,iRet);
	fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "本记录抹账成功");
	return COMPRET_SUCC;
}

IRESULT SYW_TIPS_RZMZLJCL(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];    /* 原帐务日期 */
	int iYQzlsh;         /* 原前置流水号 */
	char sYMsgNo[4+1];   /* 原交易代码 */
	char sDzlx[1+1];     /* 原对帐类型 */
	char sDzjg[2+1];     /* 原对帐结果 */
	char sDzjg2[2+1];    /* 对帐结果2 */
	char sClzt[1+1];     /* 处理状态 */
	char sClxx[50+1];    /* 处理信息 */
	char sYDzbz[8+1];    /* 原对帐标志 */
	int  iCount;         /* 记录数 */
	//EXEC SQL END DECLARE SECTION;
	SDB_MZ  stMz;
	char sBuf[256];
	char sIniFile[256];
	char sIsPldz[1+1];/* 核心批量是否参与对账 */
	int iMz=0;/* 是否需抹账 */
	char sHxDzbz[1+1];/* 核心对帐标志 */
	char sTiDzbz[1+1];/* 与TIPS对帐标志 */
	int iRet=-1;
	double dMzje;
	char sPljylsh[8+1];/* 批量交易流水号 */
	char sPlpch[8+1];/* 批量批次号 */

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(6)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	COMP_GETPARSEPARAS(1,sBuf,"原帐务日期");
	pstrcopy(sYZwrq, sBuf, sizeof(sYZwrq));

	memset(sBuf, 0x00, sizeof(sBuf));
	iYQzlsh=0;
	COMP_GETPARSEPARAS(2,sBuf,"原前置流水号");
	iYQzlsh=atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(3,sBuf,"原对账类型");
	pstrcopy(sDzlx, sBuf, sizeof(sDzlx));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(4,sBuf,"原交易代码");
	pstrcopy(sYMsgNo, sBuf, sizeof(sYMsgNo));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzjg, 0x00, sizeof(sDzjg));    
	COMP_GETPARSEPARAS(5,sBuf,"对帐结果");
	pstrcopy(sDzjg, sBuf, sizeof(sDzjg));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYDzbz, 0x00, sizeof(sYDzbz));    
	COMP_GETPARSEPARAS(6,sBuf,"对帐标志");
	pstrcopy(sYDzbz, sBuf, sizeof(sYDzbz));

	memset(sHxDzbz, 0x00, sizeof(sHxDzbz));
	memset(sTiDzbz, 0x00, sizeof(sTiDzbz));
	sHxDzbz[0]=sYDzbz[0];
	sTiDzbz[0]=sYDzbz[1];

	LOG(LM_STD,Fmtmsg("自动抹账逻辑处理...原帐务日期[%s]原前置流水号[%d]原对账类型[%s]",
				sYZwrq, iYQzlsh, sDzlx),fpub_GetCompname(lXmlhandle));     
	LOG(LM_STD,Fmtmsg("原交易代码[%s]原对帐结果[%s]原对帐标志[%s%s]",
				sYMsgNo, sDzjg, sHxDzbz, sTiDzbz),fpub_GetCompname(lXmlhandle)); 
	LOG_TiaoZ("mz",Fmtmsg("原帐务日期[%s]原前置流水号[%d]原对账类型[%s]原交易代码[%s]原对帐结果[%s]原对帐标志[%s%s]",
				sYZwrq, iYQzlsh, sDzlx, sYMsgNo, sDzjg, sHxDzbz, sTiDzbz));
	memset(sBuf, 0x00, sizeof(sBuf));
	dMzje=0.00;
	COMP_SOFTGETXML("/tips/mzje", sBuf)
		dMzje=atof(sBuf);

	memset(sPljylsh, 0x00, sizeof(sPljylsh));
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/pljylsh", sBuf)
		pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));

	memset(sPlpch, 0x00, sizeof(sPlpch));
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/plpch", sBuf)
		pstrcopy(sPlpch, sBuf, sizeof(sPlpch));

	iRet=-1;
	memset(&stMz, 0x00, sizeof(stMz));
	stMz.lXmlhandle=lXmlhandle;
	pstrcopy(stMz.yzwrq, sYZwrq, sizeof(stMz.yzwrq));
	stMz.yqzlsh=iYQzlsh;
	pstrcopy(stMz.ymsgno, sYMsgNo, sizeof(stMz.ymsgno));
	stMz.mzje=dMzje;
	pstrcopy(stMz.pljylsh, sPljylsh, sizeof(stMz.pljylsh));
	pstrcopy(stMz.plpch, sPlpch, sizeof(stMz.plpch));
	/* 若为92--与TIPS对帐,我方多 */
	if (sDzjg[1]=='2' )
	{
		LOG(LM_STD,Fmtmsg("--------%s---------",sHxDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sHxDzbz[0];
		iRet=prv_tips_Mz92(stMz);
	}else if (sDzjg[0]=='3' )/* 39--与核心主机对帐，主机多 */
	{
		LOG(LM_STD,Fmtmsg("********%s*********",sTiDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sTiDzbz[0];
		iRet=prv_tips_Mz39(stMz);
	}    
	if(iRet<0)
	{
		fpub_SetMsg(lXmlhandle, 24420, "本记录抹账失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("本记录抹账失败[%d]",iRet),
				fpub_GetCompname(lXmlhandle))        
	}        
	fpub_SetCompStatus(lXmlhandle,iRet);
	fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "本记录抹账成功");
	return COMPRET_SUCC;
}
/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_TiaoZ
  组件名称: 与TIPS对帐时如果银行方有记录多的情况银行方采用直接自动进行冲正处理进行调帐 
  与主机对帐时如果前置有记录多则为异常需要人工去处理
  程序流程步骤：
  1 在对帐不平表中找出所有对帐类型为3--日终与TIPS对帐、处理状态0--未处理的记录
  同时符合与主机方对平但与TIPS方对不平的且存在着银行方多的情况,并且需要进行冲正的记录明细 
  2 再到实时扣税表中去查找原交易信息 找到则进行冲正处理
  3 如果未找到 在到批量扣税费明细表中查找该交易是否存在,存在也进行冲正处理
  4 如果还未找到 则跳出循环不用进行补账(TIPS多,银行无记录)
  5 最后更新对帐不平表状态和同时更新原交易的状态为被冲正状态等相关信息

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

  项 目 组: TIPS专用前置产品组
  程 序 员: TUQL
  发布日期: 2009年10月26日
  修改日期: 20141105 modify by chenxm  DCI改造工作
  参数使用示例: 
 ************************************************************************/
int prv_tips_tzmz(HXMLTREE lXmlhandle, 
		char chkdate[8+1],
		char ydzjg[2+1],
		char sTiaoZFlow[128],
		int *iMzSnum,
		double *dMzSje,
		int *iMzFnum,
		double *dMzFje
		)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION; */
	char sChkDate[8+1];/*对帐日期*/
	int iCount=0;
	char sYZwrq[8+1];/* 原帐务日期 */
	int iYQzlsh;/* 原前置流水号 */
	char sYMsgNo[4+1];/* 原交易代码 */
	char sYDzlx[1+1];/* 原对账类型 */
	char sYDzjg[2+1];/* 原对账结果 */
	double dJyje;/* 交易金额 */
	char sJymc[50+1];/* 交易名称 */
	/* EXEC SQL END DECLARE SECTION;*/
	char sBuf[256];
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	int i,iFlag=0;
	int iSqlRet = -1;
	CURSOR cur;

	memset(sChkDate, 0x00, sizeof(sChkDate));
	pstrcopy(sChkDate, chkdate, sizeof(sChkDate));
	memset(sYDzjg, 0x00, sizeof(sYDzjg));
	pstrcopy(sYDzjg, ydzjg, sizeof(sYDzjg));

	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT zwrq,zhqzlsh,jymc,dzlx,jyje FROM tips_dzbpdj "
			"where chkdate='%s' and dzjg='%s' and clzt='0' ORDER  BY zwrq,zhqzlsh", sChkDate,sYDzjg);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	//add by chenxm 20141105 DCI改造工作
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("执行游标失败"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("执行游标失败"), fpub_GetCompname(lXmlhandle));
	}

	/*EXEC SQL DECLARE cur_dzbpdj_tzmz CURSOR for
	  SELECT zwrq,zhqzlsh,jymc,dzlx,jyje
	  FROM tips_dzbpdj
	  WHERE chkdate=:sChkDate  */ 				 /*对帐日期*/
	//      AND dzjg=:sYDzjg                       /*92--TIPS无前置有 39-前置无核心有*/
	//	  AND clzt='0'   						 /*处理状态0-未处理*/
	//	ORDER  BY zwrq,zhqzlsh;  				 /*以帐务日期与前置流水号*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  EXEC SQL OPEN cur_dzbpdj_tzmz;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_tzmz",sqlca.sqlcode),"ERROR");
	  if(SQLERR)
	  {
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开cur_dzbpdj_tzmz游标失败"),
	  fpub_GetCompname(lXmlhandle))
	  }
	 */
	/* 开始逐笔处理 */
	for (i=1, iFlag=0;; i++)
	{   	  
		memset(sYZwrq, 0x00, sizeof(sYZwrq));
		iYQzlsh=0;
		memset(sJymc, 0x00, sizeof(sJymc));
		memset(sYDzlx, 0x00, sizeof(sYDzlx));
		//EXEC SQL FETCH cur_dzbpdj_tzmz INTO :sYZwrq,:iYQzlsh,:sJymc,:sYDzlx,:dJyje;
		//SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzbpdj_tzmz",sqlca.sqlcode),"ERR")
		 
		iSqlRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
		if(iSqlRet <= 0)
			break;
		/*
		sprintf( sYZwrq, "%s", DCIFieldAsString( cur, 0 ) );		
		iYQzlsh = atoi( DCIFieldAsString( cur, 1 ) );
		sprintf( sJymc, "%s", DCIFieldAsString( cur, 2 ) );
		sprintf( sYDzlx, "%s", DCIFieldAsString( cur, 3 ) );
		dJyje = atof(DCIFieldAsString( cur, 4 ) );
		*/
		
		strncpy( sYZwrq, DCIFieldAsString(cur, 0 ), sizeof( sYZwrq ) );		
		iYQzlsh = atoi( DCIFieldAsString( cur, 1 ) );		
		strncpy( sJymc, DCIFieldAsString(cur, 2 ), sizeof( sJymc ) );		
		strncpy( sYDzlx, DCIFieldAsString(cur, 3 ), sizeof( sYDzlx ) );		
		dJyje = atof(DCIFieldAsString( cur, 4 ) );
		
		/*if (SQLERR)
		  {
		  LOG(LM_STD,Fmtmsg("从cur_dzbpdj_tzmz游标获取数据失败"),"ERROR");
		  iFlag = -1;
		  break;
		  }
		  if (SQLNOTFOUND)
		  {
		  break; 
		  }*/
		/*************首先到实时扣税表中或批量扣税费明细表中查找该交易记录是否存在****************/
		trim(sYZwrq);
		trim(sJymc);
		trim(sYDzlx);

		memset(sYMsgNo, 0x00, sizeof(sYMsgNo));
		pstrcopy(sYMsgNo, sJymc, sizeof(sYMsgNo));
		iCount=0;
		if ( strncmp(sYMsgNo, "3001", 4) == 0
				|| strncmp(sYMsgNo, "1008", 4) == 0
		   )
		{
			// added by chenxm 20141104 DCI改造工作
			memset(sTemp, 0x00, sizeof(sTemp));
			sprintf(sSql1, "select count(*) from tips_drls where zwrq = '%s' and zhqzlsh =%d ",
					sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				iFlag = -3; 
				break; 
			}
			// add end by chenxm 

			/*EXEC SQL SELECT COUNT(*) INTO :iCount 
			  FROM tips_drls
			  WHERE  zwrq=:sYZwrq*/      /*原帐务日期*/
			//AND  zhqzlsh=:iYQzlsh; /*原综合前置流水号*/
			/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )
			  { 
			  iFlag = -3; 
			  break; 
			  } */           
		}else if (strncmp(sYMsgNo, "3102", 4) == 0)
		{
			// added by chenxm 20141104 DCI改造工作
			memset(sTemp, 0x00, sizeof(sTemp));
			sprintf(sSql1, "select count(*) from tips_ssplksfmx where zwrq = '%s' and plmxxh =%d ",
					sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				iFlag = -4; 
				break; 
			}
			// add end by chenxm

			/*EXEC SQL SELECT COUNT(*) INTO :iCount 
			  FROM tips_ssplksfmx
			  WHERE  zwrq=:sYZwrq  */    /*原帐务日期*/
			//      AND  plmxxh=:iYQzlsh;  /*原综合前置流水号*/
			/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )
			  { 
			  iFlag = -4; 
			  break; 
			  } */           
		}else
		{
			LOG(LM_STD,Fmtmsg("登记的交易名称有误[%s],跳过暂不处理", sYMsgNo),"ERROR");
			LOG_TiaoZ("mz",Fmtmsg("zwrq[%s]zhqzlsh[%d]---登记的交易名称有误[%s],跳过暂不处理",
						sYZwrq, iYQzlsh,sYMsgNo));
			continue;
		}

		/* 判断原流水记录是否存在 */
		if (iCount!=1)
		{
			LOG(LM_STD,Fmtmsg("原流水不存在count[%d],交易代码[%s],zwrq[%s],zhqzlsh[%d]", 
						iCount, sYMsgNo, sYZwrq, iYQzlsh),"ERROR");

			// added by chenxm 20141104 DCI改造工作
			memset(sTemp, 0x00, sizeof(sTemp));
			sprintf(sSql1, "UPDATE tips_dzbpdj SET clzt='6',clxx='调帐失败,原流水记录不存在' where zwrq = '%s' and zhqzlsh =%d ",
					sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    	
			iSqlRet = DCIExecuteDirect(sSql1);
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				iFlag = -4; 
				break; 
			}
			// add end by chenxm

			/*EXEC SQL UPDATE tips_dzbpdj
			  SET clzt='6',
			  clxx='调帐失败,原流水记录不存在'
			  WHERE zwrq=:sYZwrq
			  AND zhqzlsh=:iYQzlsh;
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )
			  { 
			  iFlag = -5; 
			  break; 
			  } */                       
			LOG_TiaoZ("mz",Fmtmsg("-->抹帐记录：zwrq[%s]zhqzlsh[%d]---调帐失败,原流水记录不存在",
						sYZwrq, iYQzlsh));            
			continue;            
		}
		/* 若为银行端缴款,则向TIPS补发回执；若为实扣或批扣,则向核心主机发起冲正 */
		COMP_SOFTSETXML("/tips/yzwrq", "")
		COMP_SOFTSETXML("/tips/yqzlsh", "")
		COMP_SOFTSETXML("/tips/ymsgno", "")
		COMP_SOFTSETXML("/tips/ydzlx", "")
		COMP_SOFTSETXML("/tips/ydzjg", "")  

		COMP_SOFTSETXML("/tips/yzwrq", sYZwrq)
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sBuf, sizeof(sBuf), "%d", iYQzlsh);
		COMP_SOFTSETXML("/tips/yqzlsh", sBuf)
		COMP_SOFTSETXML("/tips/ymsgno", sYMsgNo)
		COMP_SOFTSETXML("/tips/ydzlx", sYDzlx)
		COMP_SOFTSETXML("/tips/ydzjg", sYDzjg)
		memset(sBuf, 0x00, sizeof(sBuf));/* add by tuql 20091217 */
		sBuf[0]='1';
		COMP_SOFTGETXML("/tips/ismz", sBuf)
			/* 开始调对应的子流程 */            
			if ( fpub_CallFlow(lXmlhandle,sTiaoZFlow) != MID_SYS_SUCC)
			{
				(*iMzFnum)++;
				(*dMzFje) += dJyje;
				iFlag=-6;
				LOG(LM_STD,Fmtmsg("调用[%s]子流程系统错误", sTiaoZFlow),"ERROR");
				break;
			}

		/*判断子流程是否处理成功*/
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
		if ( sBuf[0] == '2' )  /*返回2失败,其它均为成功*/
		{
			(*iMzFnum)++;
			(*dMzFje) += dJyje;
			LOG(LM_STD,Fmtmsg("调用[%s]子流程系统失败", sTiaoZFlow),"ERROR");
			memset(sBuf, 0x00, sizeof(sBuf));
			COMP_SOFTGETXML(XMLNM_RESPMSG,sBuf)
				trim(sBuf);
			LOG_TiaoZ("mz",Fmtmsg("-->抹帐记录：zwrq[%s]zhqzlsh[%d]---调帐失败,%s",
						sYZwrq, iYQzlsh, sBuf));         	
			continue;
		}
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML("/tips/ismz", sBuf)
			if(sBuf[0]=='2')/* 若此节结为2,说明未与TIPS对帐暂不抹账 add by tuql 20091217*/
			{
				continue; 
			}
		LOG_TiaoZ("mz",Fmtmsg("-->抹帐记录：zwrq[%s]zhqzlsh[%d]---调帐成功",
					sYZwrq, iYQzlsh)); 
		(*iMzSnum)++;
		(*dMzSje) += dJyje;
	}           
	//EXEC SQL CLOSE cur_dzbpdj_tzmz; 
	DCIFreeCursor(cur);
	if (iFlag < 0)
	{
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("日终自动调帐失败[%d]",iFlag),
				fpub_GetCompname(lXmlhandle))
	}    
	return 0;        
}

IRESULT SYW_TIPS_TiaoZ(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sChkDate[8+1];                 /*对帐日期*/
	int iCount;                         /* 总记录数 */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char sflow[64];
	char sSysDate[8+1];
	char sSysTime[6+1];
	char sZwrq[8+1];
	int iMzSnum = 0;                     /* 抹帐成功笔数 */
	double dMzSje = 0.00;                /* 抹帐成功金额 */
	int iMzFnum = 0;                     /* 抹帐失败笔数 */
	double dMzFje = 0.00;                /* 抹帐失败金额 */        
	int iRet=0;
	int iSqlRet = -1;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(2)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"对帐日期");
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sflow, 0x00, sizeof(sflow));
	COMP_GETPARSEPARAS(2,sBuf,"对帐不平冲正子流程");
	pstrcopy(sflow, sBuf, sizeof(sflow));

	LOG(LM_STD,Fmtmsg("日终自动调帐开始处理...对帐日期[%s]冲正流程[%s]",
				sChkDate, sflow),fpub_GetCompname(lXmlhandle)); 

	iCount=0;
	//add by chenxm 20141105 DCI改造工作
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT COUNT(*) FROM tips_dzbpdj WHERE chkdate='%s' and dzjg in ('92','39') and clzt='0'",sChkDate);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1 );
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle,24316,"查询对账不平登记表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询对账不平登记表失败"),fpub_GetCompname(lXmlhandle))
	}
	//add end by chenxm 
	//EXEC SQL SELECT COUNT(*) INTO :iCount
	//     FROM tips_dzbpdj
	//   WHERE chkdate=:sChkDate   				 /*对帐日期*/
	//     AND dzjg in ('92','39')                /*92--TIPS无前置有 39-前置无核心有*/
	//	  AND clzt='0';   						 /*处理状态0-未处理*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if (SQLERR)
	  {
	  fpub_SetMsg(lXmlhandle,24316,"查询对账不平登记表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询对账不平登记表失败"),
	  fpub_GetCompname(lXmlhandle))
	  }*/
	if (iCount == 0)
	{
		fpub_SetMsg(lXmlhandle,24317,"没有需要日终调帐(抹账)的记录");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("没有需要日终调帐(抹账)的记录"),
				fpub_GetCompname(lXmlhandle))        
	}    

	memset(sSysDate, 0x00, sizeof(sSysDate));
	COMP_SOFTGETXML("/sys/sysdate",sSysDate);
	memset(sSysTime, 0x00, sizeof(sSysTime));
	COMP_SOFTGETXML("/sys/systime",sSysTime);
	memset(sZwrq, 0x00, sizeof(sZwrq));
	COMP_SOFTGETXML("/tips/zwrq",sZwrq);        

	LOG_TiaoZ("mz",Fmtmsg("\n                                日终自动抹帐开始\n"));
	LOG_TiaoZ("mz",Fmtmsg("系统日期[%s]时间[%s]      前置帐务日期[%s]       TIPS对帐日期[%s]",sSysDate,sSysTime, sZwrq, sChkDate));
	LOG_TiaoZ("mz",Fmtmsg("============================================================================================="));
	LOG_TiaoZ("mz",Fmtmsg("对账状态39，主机多，TIPS对账状态未知，需冲账"));
	iRet=prv_tips_tzmz(lXmlhandle,
			sChkDate,
			"39",
			sflow,
			&iMzSnum,
			&dMzSje,
			&iMzFnum,
			&dMzFje
			);
	if (iRet < 0)
	{
		LOG_TiaoZ("mz",Fmtmsg("============================================================================================="));
		LOG_TiaoZ("mz",Fmtmsg("对账状态39，主机多，TIPS对账状态未知，冲账失败"));
		LOG_TiaoZ("mz",Fmtmsg("本次抹账成功笔数[%d],抹账成功金额[%.2f]  抹账失败笔数[%d],抹账失败金额[%.2f]\n",
					iMzSnum, dMzSje, iMzFnum, dMzFje));
		fpub_SetMsg(lXmlhandle,24313,"日终自动调帐失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("日终自动调帐失败[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}
	LOG_TiaoZ("mz",Fmtmsg("对账状态92，主机对账状态未知，前置多，需冲账"));
	iRet=prv_tips_tzmz(lXmlhandle,
			sChkDate,    
			"92",
			sflow,
			&iMzSnum,
			&dMzSje,
			&iMzFnum,
			&dMzFje
			);
	if (iRet < 0)
	{
		LOG_TiaoZ("mz",Fmtmsg("============================================================================================="));
		LOG_TiaoZ("mz",Fmtmsg("对账状态92，主机对账状态未知，前置多，冲账失败"));
		LOG_TiaoZ("mz",Fmtmsg("本次抹账成功笔数[%d],抹账成功金额[%.2f]  抹账失败笔数[%d],抹账失败金额[%.2f]\n",
					iMzSnum, dMzSje, iMzFnum, dMzFje));
		fpub_SetMsg(lXmlhandle,24314,"日终自动调帐失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("日终自动调帐失败[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}
	LOG_TiaoZ("mz",Fmtmsg("============================================================================================="));
	LOG_TiaoZ("mz",Fmtmsg("本次抹账成功笔数[%d],抹账成功金额[%.2f]  抹账失败笔数[%d],抹账失败金额[%.2f]\n",
				iMzSnum, dMzSje, iMzFnum, dMzFje));
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,Fmtmsg("本次抹账成功笔数[%d],抹账成功金额[%.2f]  抹账失败笔数[%d],抹账失败金额[%.2f]",
				iMzSnum, dMzSje, iMzFnum, dMzFje));
	LOG(LM_STD,Fmtmsg("本次抹账成功笔数[%d],抹账成功金额[%.2f]  抹账失败笔数[%d],抹账失败金额[%.2f]",
				iMzSnum, dMzSje, iMzFnum, dMzFje), fpub_GetCompname(lXmlhandle))
		return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_XIB_HXDZZD
  组件名称: XIB与核心对账(自动)

  组件功能: 
  与核心对账
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
  发布日期: 2012年08月07日
  修改日期: 20141106 modify by chenxm DCI改造工作
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_XIB_HXDZZD(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	int iCount;
	int iCount2;
	char sDzrq[8+1];/* 对账日期 */
	char sPrevDate[8+1];/* 对账起始日 */
	/*BANKDetail stDetail;*/
	SDB_TIPS_HXDZMX stDetail;
	/*SDB_TIPS_XIBHXMX stHxmx;*/
	SDB_TIPS_DRLS stDrls;
	SDB_TIPS_SSPLKSFMX stPlksfmx;
	SDB_TIPS_DZBPDJ stDzbpdj;
	//EXEC SQL END   DECLARE SECTION;

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];
	char sBuf[256];
	int i;
	int iRet=0;
	int iSqlRet = -1;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(1);
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzrq, 0x00, sizeof(sDzrq));
	COMP_GETPARSEPARAS(1, sBuf, "对账日期")
		pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
	trim(sDzrq); 

	LOG(LM_STD,Fmtmsg("与核心对账开始处理..."),fpub_GetCompname(lXmlhandle))  

		/*EXEC SQL BEGIN WORK; 事务开始*/

	iRet = DCIBegin();  //add by chenxm 20141106 DCI改造工作
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}

	/*置当日流水为核心未对账状态*/
	//add by chenxm 20141105 DCI改造工作
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1) WHERE zwrq='%s' and msgno in ('3001','1008')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1)
	  WHERE zwrq = :sDzrq
	  AND msgno in ('3001','1008');*/
	/* mod by tuql 20091112 AND jyzt = '0'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/           
	LOG(LM_STD,Fmtmsg("-----更新当日流水为未对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*置当日批量明细为核心未对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7) WHERE zwrq='%s'",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量扣税费明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量扣税费明细表失败"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7)
	  WHERE zwrq = :sDzrq ;*/
	/* mod by tuql 20091112 AND czbd = '7'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量扣税费明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量扣税费明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量明细为未对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*删除当日核心对账不平记录*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzbpdj WHERE zwrq='%s' and dzlx='1' and byzd in (' ','9')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "删除当日核心对账不平记录");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除当日核心对账不平记录"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_dzbpdj 
	  WHERE zwrq = :sDzrq and dzlx='1' and byzd in (' ','9');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "删除当日核心对账不平记录");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除当日核心对账不平记录"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----删除当日对账不平记录成功------"),fpub_GetCompname(lXmlhandle))  

		/*删除核心流水不参与对账记录*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_xibhxmx WHERE sprq='%s' and ztm not in ('0','1')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "删除核心流水失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除核心流水表失败"),fpub_GetCompname(lXmlhandle)) 
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_xibhxmx 
	  WHERE sprq = :sDzrq and ztm not in ('0','1'); 
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "删除核心流水失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除核心流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----删除核心流水不参与对账记录成功------"),fpub_GetCompname(lXmlhandle))  

		/*将核心明细流水号在当日流水中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq='%s' and dzlsh in (select zjlsh from tips_drls where zwrq = '%s' and jyzt='0')",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"),fpub_GetCompname(lXmlhandle))
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_drls where zwrq = :sDzrq and jyzt='0');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新实时核心明细为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将核心明细流水号在批量明细中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq='%s' and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = '%s' and czbd='7')",sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"),fpub_GetCompname(lXmlhandle))
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = :sDzrq and czbd='7');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量核心明细为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将当日流水流水号在核心明细中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='1'||substr(dzbz,2,1) WHERE zwrq='%s' and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s')",sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='1'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新当日流水为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将当日失败流水流水号在核心明细中存在的更新为核心多状态--add by wangw 20120907*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='3'||substr(dzbz,2,1) WHERE zwrq='%s' and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='3'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----将当日失败流水流水号在核心明细中存在的更新为核心多状态------"),fpub_GetCompname(lXmlhandle))  

		/*将当日流水流水号bu在核心明细中存在的更新为对账不平状态--20120906 增加and msgno in ('3001','1008')条件，处理冲正数据*/

		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='2'||substr(dzbz,2,1) WHERE zwrq='%s' and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1'", sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='2'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新当日流水为对账不平状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将批量明细流水号在核心明细中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7) WHERE zwrq='%s' and czbd='7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s')", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"), fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量明细为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将失败批量明细流水号在核心明细中存在的更新为核心多状态--add vy wangw 20120907*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7) WHERE zwrq='%s' and czbd<>'7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s')", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"),fpub_GetCompname(lXmlhandle))     
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd<>'7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----将失败批量明细流水号在核心明细中存在的更新为核心多状态------"),fpub_GetCompname(lXmlhandle))  

		/*将批量明细流水号不在核心明细中存在的更新为对账不平状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7) WHERE zwrq='%s' and czbd='7' and substr(kzbz,1,1)<>'1'", sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"), fpub_GetCompname(lXmlhandle))     
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and substr(kzbz,1,1)<>'1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量明细为对账不平状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将核心明细未对账的插入对账不平登记表*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate) "
			"select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1','%s','39',' ','核心多','0000','%s' "
			"from tips_xibhxmx where sprq = '%s' and dzbz <> '1'", sDzrq, sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "未对账核心明细插入对账不平登记表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账核心明细插入对账不平登记表失败"), fpub_GetCompname(lXmlhandle))            
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate)  
	  select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1',:sDzrq,'39',' ','核心多','0000',:sDzrq 
	  from tips_xibhxmx 
	  where sprq = :sDzrq and dzbz <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "未对账核心明细插入对账不平登记表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账核心明细插入对账不平登记表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----未对账核心明细插入不平表成功------"),fpub_GetCompname(lXmlhandle))  

		/*将当日流水未对账的插入对账不平登记表--20120906 增加and msgno in ('3001','1008')条件，处理冲正数据*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,'%s',payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000' "
			"from tips_drls where zwrq='%s' and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1) <> '1'", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "未对账当日流水插入对账不平登记表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账当日流水插入对账不平登记表失败"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) 
	  select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,:sDzrq,payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000'
	  from tips_drls 
	  where zwrq=:sDzrq and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1) <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "未对账当日流水插入对账不平登记表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账当日流水插入对账不平登记表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----未对账实时流水插入不平表成功------"),fpub_GetCompname(lXmlhandle))  

		/*将批量明细未对账的插入对账不平登记表*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,'%s',payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000' "
			"from tips_ssplksfmx where zwrq='%s' and and czbd='7' and substr(kzbz,1,1) <> '1'", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "未对账批量明细插入对账不平登记表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未批量明细流水插入对账不平登记表失败"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz)  
	  select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,:sDzrq,payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000'
	  from tips_ssplksfmx 
	  where zwrq=:sDzrq and czbd='7' and substr(kzbz,1,1) <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "未对账批量明细插入对账不平登记表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未批量明细流水插入对账不平登记表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	//EXEC SQL COMMIT;  /*提交*/
	iSqlRet=DCICommit();
	/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
		if ( iSqlRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
   */
	LOG(LM_STD,Fmtmsg("-----未对账批量明细插入不平表成功------"),fpub_GetCompname(lXmlhandle))  

		LOG(LM_DEBUG,Fmtmsg("与核心主机对账结束" ), fpub_GetCompname(lXmlhandle));
	fpub_SetMsg(lXmlhandle, 0, "与核心主机对账结束");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_XIB_HXDZSG
  组件名称: XIB与核心对账(手工)

  组件功能: 
  与核心对账
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
  发布日期: 2012年08月07日
  修改日期: 20141105 DCI 改造工作
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_XIB_HXDZSG(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	int iCount;
	int iCount2;
	char sDzrq[8+1];/* 对账日期 */
	char sPrevDate[8+1];/* 对账起始日 */
	char sQsh[12+1];/* 清算行代码 */
	/*BANKDetail stDetail;*/
	SDB_TIPS_HXDZMX stDetail;
	/*SDB_TIPS_XIBHXMX stHxmx;*/
	SDB_TIPS_DRLS stDrls;
	SDB_TIPS_SSPLKSFMX stPlksfmx;
	SDB_TIPS_DZBPDJ stDzbpdj;
	/*EXEC SQL END   DECLARE SECTION;*/

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	int i;
	int iRet=0;
	int iSqlRet = -1;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(2);
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzrq, 0x00, sizeof(sDzrq));
	COMP_GETPARSEPARAS(1, sBuf, "对账日期")
		pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
	trim(sDzrq); 
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sQsh, 0x00, sizeof(sQsh));
	COMP_GETPARSEPARAS(2, sBuf, "清算行行号")
		pstrcopy(sQsh, sBuf, sizeof(sQsh));
	trim(sQsh); 

	LOG(LM_STD,Fmtmsg("与核心对账开始处理..."),fpub_GetCompname(lXmlhandle))  
		LOG(LM_STD,Fmtmsg("-----对账日期[%s]清算行行号[%s]-----",sDzrq,sQsh),fpub_GetCompname(lXmlhandle))  

		/*EXEC SQL BEGIN WORK; *事务开始*/
		iRet = DCIBegin();  //add by chenxm 20141106 DCI改造工作
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}

	/*置当日流水为核心未对账状态*/
	//add by chenxm 20141105 DCI改造工作
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1) WHERE zwrq='%s' and msgno in ('3001','1008') "
			"and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1)
	  WHERE zwrq = :sDzrq
	  AND msgno in ('3001','1008') and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	 *//* mod by tuql 20091112 AND jyzt = '0'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }     */      
	LOG(LM_STD,Fmtmsg("-----更新当日流水为未对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*置当日批量明细为核心未对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7) WHERE zwrq='%s' "
			"and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量扣税费明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量扣税费明细表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7)
	  WHERE zwrq = :sDzrq  and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	 *//* mod by tuql 20091112 AND czbd = '7'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量扣税费明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量扣税费明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量明细为未对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*删除当日核心对账不平记录*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzbpdj WHERE zwrq='%s' "
			"and dzlx='1' and byzd in(' ','9') and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "删除当日核心对账不平记录");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除当日核心对账不平记录"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_dzbpdj 
	  WHERE zwrq = :sDzrq and dzlx='1' and byzd in(' ','9') and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "删除当日核心对账不平记录");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除当日核心对账不平记录"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----删除当日核心对账不平记录成功------"),fpub_GetCompname(lXmlhandle))  

		/*删除核心流水不参与对账记录--非正常状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_xibhxmx WHERE sprq = '%s' and ztm not in ('0','1')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "删除核心流水失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除核心流水表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_xibhxmx 
	  WHERE sprq = :sDzrq and ztm not in ('0','1') ;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "删除核心流水失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除核心流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----删除核心流水不参与对账记录成功------"),fpub_GetCompname(lXmlhandle))  
		/*删除核心流水不参与对账记录--非本机构*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_xibhxmx WHERE sprq = '%s' and jgdh not in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "删除核心流水失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除核心流水表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_xibhxmx 
	  WHERE sprq = :sDzrq and jgdh not in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "删除核心流水失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("删除核心流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----删除核心流水不参与对账记录成功------"),fpub_GetCompname(lXmlhandle))  

		/*将核心明细流水号在当日流水中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq = '%s' and dzlsh in (select zjlsh from tips_drls where zwrq = '%s' and jyzt='0' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s'))",sDzrq,sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_drls where zwrq = :sDzrq and jyzt='0' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh));
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新实时核心明细为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将核心明细流水号在批量明细中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq = '%s' and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = '%s' and czbd='7' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s'))",sDzrq,sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = :sDzrq and czbd='7' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh));
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新核心明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新核心明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量核心明细为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将当日流水流水号在核心明细中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='1'||substr(dzbz,2,1) WHERE zwrq = '%s' and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='1'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新当日流水为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将当日失败流水流水号在核心明细中存在的更新为核心多状态--add by wangw 20120907*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='3'||substr(dzbz,2,1) WHERE zwrq = '%s' and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='3'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新当日流水为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将当日流水流水号在核心明细中不存在的更新为对账不平状态--20120906 增加and msgno in ('3001','1008')条件，处理冲正数据*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='2'||substr(dzbz,2,1) WHERE zwrq = '%s' and jyzt='0' "
			"and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1' and zjlsh in (select dzlsh from tips_jgdhdj where qshdm = '%s' )",sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='2'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新当日流水表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新当日流水为对账不平状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将批量明细流水号在核心明细中存在的更新为已对账状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7) WHERE zwrq = '%s' and czbd='7' "
			"and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量明细为已对账状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将失败批量明细流水号在核心明细中存在的更新为核心多状态--add by wangw 20120907*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7) WHERE zwrq = '%s' and czbd<>'7' "
			"and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd<>'7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量明细为核心多状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将批量明细流水号在核心明细中存在的更新为对账不平状态*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='2'||substr(kzbz,2,7) WHERE zwrq = '%s' and czbd='7' "
			"and substr(kzbz,1,1)<>'1' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='2'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and substr(kzbz,1,1)<>'1' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "更新批量明细表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新批量明细表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----更新批量明细为对账不平状态成功------"),fpub_GetCompname(lXmlhandle))  

		/*将核心明细未对账的插入对账不平登记表*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate) "
			"select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1','%s','39',' ','核心多','0000','%s' "
			"from tips_xibhxmx where sprq = '%s' and dzbz <> '1'", sDzrq, sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "未对账当日流水插入对账不平登记表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账当日流水插入对账不平登记表失败"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate)  
	  select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1',:sDzrq,'39',' ','核心多','0000',:sDzrq 
	  from tips_xibhxmx 
	  where sprq = :sDzrq and dzbz <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "未对账核心明细插入对账不平登记表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账核心明细插入对账不平登记表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----未对账核心明细插入不平表成功------"),fpub_GetCompname(lXmlhandle))  

		/*将当日流水未对账的插入对账不平登记表--20120906 增加and msgno in ('3001','1008')条件，处理冲正数据*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,:sDzrq,payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000' "
			"from tips_drls where zwrq='%s' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s') and jyzt='0' and substr(dzbz,1,1) <> '1' and msgno in ('3001','1008')", sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "未对账当日流水插入对账不平登记表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账当日流水插入对账不平登记表失败"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz)  
	  select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,:sDzrq,payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000'
	  from tips_drls 
	  where zwrq=:sDzrq and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh) and jyzt='0' and substr(dzbz,1,1) <> '1' and msgno in ('3001','1008');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "未对账当日流水插入对账不平登记表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未对账当日流水插入对账不平登记表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----未对账实时流水插入不平表成功------"),fpub_GetCompname(lXmlhandle))  

		/*将批量明细未对账的插入对账不平登记表*/
		//add by chenxm 20141105 DCI改造工作
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,:sDzrq,payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000' "
			"from tips_ssplksfmx where zwrq='%s' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s') and czbd='7' and substr(kzbz,1,1) <> '1'", sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetMsg(lXmlhandle, 24422, "未对账批量明细插入对账不平登记表失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未批量明细流水插入对账不平登记表失败"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz)  
	  select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,:sDzrq,payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','平台多核心少','0000'
	  from tips_ssplksfmx 
	  where zwrq=:sDzrq and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh) and czbd='7' and substr(kzbz,1,1) <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "未对账批量明细插入对账不平登记表失败");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("未批量明细流水插入对账不平登记表失败"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	//EXEC SQL COMMIT;  /*事务提交*/
	iSqlRet=DCICommit();
	/* INFORMIX 不需要捕获提交错误 DB2 ORA需要放开注释  
		if ( iSqlRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("提交数据库失败"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */
	LOG(LM_STD,Fmtmsg("-----未对账批量明细插入不平表成功------"),fpub_GetCompname(lXmlhandle))  

		LOG(LM_DEBUG,Fmtmsg("与核心主机对账结束" ), fpub_GetCompname(lXmlhandle));
	fpub_SetMsg(lXmlhandle, 0, "与核心主机对账结束");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitDZJG
组件名称: 对账结果信息
 
组件功能: 
    与核心对账
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

主要操作库表:
  表名              操作

项 目 组: TIPS专用前置产品组
程 序 员: leejn
发布日期: 2014年11月07日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitDZJG(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         int iCount;
         char sDzrq[8+1];/* 对账日期 */         
         SDB_TIPS_DZJGXX stDzjgxx;  /*  add 20140901 */        
         /* add 20140901 */
				double dQzdamt =0.00; /*前置多金额 */
				int itmpQznum = 0; /* TIPS前置总笔数 */
    		double dtmpQzamt = 0.00; /* TIPS前置总金额 */
				int iZjnum = 0;   /* 核心总笔数 */
    		double dZjamt = 0.00; /* 核心总金额 */
    		int iQznum = 0; /* TIPS前置总笔数 */
    		double dQzamt = 0.00; /* TIPS前置总金额 */ 
    		int iTpnum = 0;   /* 核心总笔数 */
    		double dTpamt = 0.00; /* 核心总金额 */   
    		
    		char cQzdamt[32+1]; /*前置多金额 */
				char ctmpQznum[16+1]; /* TIPS前置总笔数 */
    		char ctmpQzamt[32+1]; /* TIPS前置总金额 */
				char cZjnum[16+1];  /* 核心总笔数 */
    		char cZjamt[32+1]; /* 核心总金额 */
    		char cQznum[16+1];/* TIPS前置总笔数 */
    		char cQzamt[32+1]; /* TIPS前置总金额 */ 
    		char cTpnum[16+1];  /* 核心总笔数 */
    		char cTpamt[32+1]; /* 核心总金额 */
    /* end add 20140901 */   
    /*EXEC SQL END   DECLARE SECTION;*/
    
    char sBuf[256];
		int i;
	
		int iFlag=0;
	
	 	char sSql1[512];  /*DCI 执行sql语句 add 20141103*/                 
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
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

    COMP_PARACOUNTCHK(1);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDzrq, 0x00, sizeof(sDzrq));
    
    COMP_GETPARSEPARAS(1, sBuf, "对账日期")
    pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
    trim(sDzrq);            
       
    LOG(LM_STD,Fmtmsg("开始生成对账信息..."),fpub_GetCompname(lXmlhandle))  
    LOG(LM_STD,Fmtmsg("对账日期[%s]",sDzrq),fpub_GetCompname(lXmlhandle)) 
    
    /* 增加对账结果统计 add 20140901 */
    /* 初始化对账结果登记表 */        
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "delete FROM tips_dzjgxx WHERE dzrq='%s'",sDzrq);
    iRet = DCIExecuteDirect(sSql1);
	  if ( iRet < 0 )
	  {
	  	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")        
    	
    	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("删除对账结果登记表记录失败"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除对账结果登记表记录失败"), 
      fpub_GetCompname(lXmlhandle));
	  }
	  /* end add 20141103 */

    /* mod dci 20141103
    EXEC SQL delete FROM tips_dzjgxx
         WHERE dzrq = :sDzrq;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("删除对账结果登记表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除对账结果登记表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    */
        
    /* 与核心对账结果 */
    /* 统计核心流水总笔数 总金额 */
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_hxdzmx \
    			where QZRQ='%s'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    	
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZjnum, &cZjamt);
    if ( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("查询主机对账登记表记录失败"));
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询主机对账登记表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    
		iZjnum=atoi(cZjnum);
		dZjamt=atof(cZjamt);
		/* end add dci */

    /* mod dci 20141103
    EXEC SQL SELECT count(*),nvl(sum(jyje),0) INTO :iZjnum,:dZjamt
    	from tips_hxdzmx  where QZRQ=:sDzrq;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("查询主机对账登记表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询主机对账登记表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    */
    
    /* 统计当日流水中与核心对账成功的总笔数 总金额 */
    itmpQznum = 0;
    dtmpQzamt = 0.00;	
    
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_drls \
    			where ZWRQ='%s' and dzbz like '1_'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    	
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1查询当日流水表记录失败"));
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1查询当日流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    itmpQznum=atoi(ctmpQznum);
		dtmpQzamt=atof(ctmpQzamt);
		/* end add dci */
		
    /* mod dci 20141103
    EXEC SQL SELECT count(*),nvl(sum(jyje),0) INTO :itmpQznum,:dtmpQzamt
    	from tips_drls where ZWRQ=:sDzrq and dzbz like '1_';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
    		LOG(LM_STD,Fmtmsg("对账日期[%d][%s]",sqlca.sqlcode,sqlca.sqlerrm),fpub_GetCompname(lXmlhandle)) 
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1查询当日流水表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1查询当日流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
    
    itmpQznum = 0;
    dtmpQzamt = 0.00;		
    
    /* 统计当日流水中与核心对账成功的总笔数 总金额 */
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    			where zwrq='%s' and kzbz like '1_'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    		
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1查询批量流水表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1查询批量流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }			
		itmpQznum=atoi(ctmpQznum);
		dtmpQzamt=atof(ctmpQzamt);

    /* end add dci */
    
    /* mod dci 20141103
    EXEC SQL SELECT count(*),nvl(sum(jyje),0) INTO :itmpQznum,:dtmpQzamt
    	 from tips_ssplksfmx where ZWRQ=:sDzrq and kzbz like '1_';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
		if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1查询批量流水表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1查询批量流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
		
		/* 生成与核心对账结果记录 */
		memset(&stDzjgxx, 0, sizeof(stDzjgxx));
    pstrcopy(stDzjgxx.dzrq , sDzrq ,sizeof(stDzjgxx.dzrq));
    stDzjgxx.dzxt[0] = '0';
    pstrcopy(stDzjgxx.chkacctord  , "" ,sizeof(stDzjgxx.chkacctord));
    stDzjgxx.allnum1 = iQznum;     
		stDzjgxx.allamt1 = dQzamt;    
		stDzjgxx.Allnum2 = iZjnum;			
		stDzjgxx.Allamt2 = dZjamt;     
		if(iQznum == iZjnum )
		{
			if(dQzamt - dZjamt> 0.01 )
				stDzjgxx.dzjg[0] = '2';
			else if(dZjamt - dQzamt > 0.01)
				stDzjgxx.dzjg[0] = '3';
			else
				stDzjgxx.dzjg[0] = '1';
		}
    else if(iQznum >= iZjnum)
    {
    	stDzjgxx.dzjg[0] = '2';
    }
    else if(iQznum <= iZjnum)
    {
    	stDzjgxx.dzjg[0] = '3';
    }
        		
		pstrcopy(stDzjgxx.byzd ,"",sizeof(stDzjgxx.byzd));
		LOG(LM_STD,Fmtmsg("[%s][%s][%s]TIPS前置笔数[%d],TIPS前置金额[%f],核心明细总笔数[%d],核心明细总金额[%f]",
        stDzjgxx.dzrq,stDzjgxx.dzxt,stDzjgxx.dzjg,iQznum,dQzamt,iZjnum,dZjamt), fpub_GetCompname(lXmlhandle));    
    
    /* 登记核心对账结果 */
    /* add dci 20141103 */
    iRet = DBInsert("tips_dzjgxx", SD_TIPS_DZJGXX, NUMELE(SD_TIPS_DZJGXX), &stDzjgxx, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetMsg(lXmlhandle, 24358, "登记核心对帐信息失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD,Fmtmsg("登记核心对帐信息失败,对账日期[%s],对账系统[%s]", 
            stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记核心对帐信息失败"), 
                    fpub_GetCompname(lXmlhandle))
    }
    /* end add dci */
    
    /* mod dci 20141103    
    EXEC SQL INSERT INTO tips_dzjgxx values(:stDzjgxx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
         
         fpub_SetMsg(lXmlhandle, 24358, "登记核心对帐信息失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("登记核心对帐信息失败,对账日期[%s],对账系统[%s]", 
               stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记核心对帐信息失败"), 
                    fpub_GetCompname(lXmlhandle))
         
    }    
    LOG(LM_STD,Fmtmsg("[%s][%s][%s]TIPS前置笔数[%d],TIPS前置金额[%f],核心明细总笔数[%d],核心明细总金额[%f]",
        stDzjgxx.dzrq,stDzjgxx.dzxt,stDzjgxx.dzjg,iQznum,dQzamt,iZjnum,dZjamt), fpub_GetCompname(lXmlhandle));    
    */
        
    /* 与TIPS对账结果 */
    /* 统计TIPS对账流水中总笔数 总金额 */
    iQznum = 0; 
    dQzamt = 0.00; 
    /* 
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(traamt) FROM tips_ssdzmx \
    			where ZWRQ='%s'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    	
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cTpnum, &cTpamt);
    if ( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("查询TIPS对账登记表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询TIPS对账登记表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    
		iTpnum=atoi(cTpnum);
		dTpamt=atof(cTpamt);
		/* end add dci */
		
    /* mod dci 20141103
    EXEC SQL SELECT count(*),nvl(sum(traamt),0) INTO :iTpnum,:dTpamt
    	from tips_ssdzmx where ZWRQ=:sDzrq;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("查询TIPS对账登记表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询TIPS对账登记表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    */
    
    /* 统计当日流水中与核心对账成功的总笔数 总金额 */
    itmpQznum = 0;
    dtmpQzamt = 0.00;	
		
		/* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_drls \
    			where ZWRQ='%s' and dzbz like '_1'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    	
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1查询当日流水表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1查询当日流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }
    itmpQznum=atoi(ctmpQznum);
		dtmpQzamt=atof(ctmpQzamt);
    /* end add dci */
    
		/* mod dci 20141103
    EXEC SQL SELECT count(*),nvl(sum(jyje),0) INTO :itmpQznum,:dtmpQzamt
    	from tips_drls where ZWRQ=:sDzrq and dzbz like '_1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
    		LOG(LM_STD,Fmtmsg("对账日期[%d][%s]",sqlca.sqlcode,sqlca.sqlerrm),fpub_GetCompname(lXmlhandle)) 
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("2查询当日流水表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("2查询当日流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
    
    itmpQznum = 0;
    dtmpQzamt = 0.00;	
    
    /* 统计当日流水中与核心对账成功的总笔数 总金额 */
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    			where zwrq='%s' and kzbz like '_1'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    		
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1查询批量流水表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1查询批量流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }			
		itmpQznum=atoi(ctmpQznum);
		dtmpQzamt=atof(ctmpQzamt);

    /* end add dci */
    
    /* mod dci 20141103
    EXEC SQL SELECT count(*),nvl(sum(jyje),0) INTO :itmpQznum,:dtmpQzamt
    	 from tips_ssplksfmx where ZWRQ=:sDzrq and kzbz like '_1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
		if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("2查询批量流水表记录失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("2查询批量流水表记录失败"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
		
		/* 生成与TIPS对账结果记录 */
		memset(&stDzjgxx, 0, sizeof(stDzjgxx));
		pstrcopy(stDzjgxx.dzrq , sDzrq ,sizeof(stDzjgxx.dzrq));
    stDzjgxx.dzxt[0] = '1';
    pstrcopy(stDzjgxx.chkacctord  , "" ,sizeof(stDzjgxx.chkacctord));
    stDzjgxx.allnum1 = iQznum;     
		stDzjgxx.allamt1 = dQzamt;    
		stDzjgxx.Allnum2 = iTpnum;			
		stDzjgxx.Allamt2 = dTpamt;     
		if(iQznum == iTpnum )
		{
			if(dQzamt - dTpamt > 0.01 )
				stDzjgxx.dzjg[0] = '2';
			else if(dTpamt - dQzamt > 0.01)
				stDzjgxx.dzjg[0] = '3';
			else
				stDzjgxx.dzjg[0] = '1';
    }
    else if(iQznum >= iTpnum)
    {
    	stDzjgxx.dzjg[0] = '2';
    }
    else if(iQznum <= iTpnum)
    {
    	stDzjgxx.dzjg[0] = '3';   		
    }
    
		pstrcopy(stDzjgxx.byzd ,"",sizeof(stDzjgxx.byzd));
		LOG(LM_STD,Fmtmsg("[%s][%s][%s]TIPS前置笔数[%d],TIPS前置金额[%f],TIPS明细总笔数[%d],TIPS明细总金额[%f]",
        stDzjgxx.dzrq,stDzjgxx.dzxt,stDzjgxx.dzjg,iQznum,dQzamt,iTpnum,dTpamt), fpub_GetCompname(lXmlhandle));    
    		
		/* 登记TIPS对账结果 */
		/* add dci 20141103 */    
    iRet = DBInsert("tips_dzjgxx", SD_TIPS_DZJGXX, NUMELE(SD_TIPS_DZJGXX), &stDzjgxx, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetMsg(lXmlhandle, 24358, "登记核心对帐信息失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD,Fmtmsg("登记核心对帐信息失败,对账日期[%s],对账系统[%s]", 
            stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记核心对帐信息失败"), 
                    fpub_GetCompname(lXmlhandle))
    }
    /* end add dci */
		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_dzjgxx values(:stDzjgxx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
         fpub_SetMsg(lXmlhandle, 24358, "登记TIPS对帐信息失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("登记TIPS对帐信息失败,对账日期[%s],对账系统[%s]", 
               stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记TIPS对帐信息失败"), 
                    fpub_GetCompname(lXmlhandle))
         
    } 
    */
       
    LOG(LM_STD,Fmtmsg("TIPS明细总笔数[%d],TIPS明细总金额[%f],TIPS前置笔数[%d],TIPS前置金额[%f]",
        iTpnum,dTpamt,iQznum,dQzamt), fpub_GetCompname(lXmlhandle));    
   	
   	/* mod dci 20141103
   	EXEC SQL commit ;  
   	*/
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
    
    fpub_SetMsg(lXmlhandle, 0, "生成对账结果信息结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);    
    
    return COMPRET_SUCC;
    
}
