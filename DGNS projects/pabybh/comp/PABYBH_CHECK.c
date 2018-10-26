#include "DCI.h"
#include "stdlib.h"
#include "stdio.h"
#include "gaps_head.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/PABYBH_SIGN.h"
#include "../incl/PABYBH_DEPCHKINFO.h"
#include "../incl/pabybh_xmlmacro.h"
#include "../incl/PABYBH_CHECKCTL.h"
 

/************************************************************************
动态组件函数定义
函数名称: PAB_DLCG_SECLOAD
名称: 券商信息录入
 
组件功能: 券商信息录入
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_TRADERLOAD(HXMLTREE lXmlhandle)
{
  int iParas;
  int iRet=0;
  int iResult=0;
  char sBuffer[200+1];
  char sTmp[200+1];
  char sFileName[100+1];
  char sSecCode[8+1];
  char sSecName[120+1];
  FILE *fp;
  struct stat filestat;
   
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  memset(sFileName,0x00,sizeof(sFileName));
  COMP_GETPARSEPARAS(1, sFileName, "券商信息文件名")
  trim(sFileName);
  
  fp = fopen(sFileName, "r");
  if ( fp==NULL )
  {
      fpub_SetMsg(lXmlhandle, 98689, "打开券商信息文件文件失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("打开文件%s失败",sFileName), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;      
  }  
  
  fstat(fileno(fp), &filestat);
  if (S_ISDIR(filestat.st_mode))
  {
      fclose(fp);
      fpub_SetMsg(lXmlhandle,98689,"目录文件") ;
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("目录文件"), fpub_GetCompname(lXmlhandle)); 
      return COMPRET_FAIL;      
  } 

  DCIBegin();
  while( !feof(fp) )
  {
     memset(sBuffer,0x00,sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) < 20 )
         continue;

     /*券商代码*/
     memset(sTmp,0x00,sizeof(sTmp));
     memset(sSecCode,0x00,sizeof(sSecCode));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     memcpy(sSecCode,sTmp,sizeof(sSecCode)-1);
     

     /*券商名称*/
     memset(sTmp,0x00,sizeof(sTmp));
     memset(sSecName,0x00,sizeof(sSecName));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     memcpy(sSecName,sTmp,sizeof(sSecName));
     
     memset(sTmp,0x00,sizeof(sTmp));
     sprintf(sTmp,"delete from PABYBH_TRADER where SECCODE ='%s' ",sSecCode);
     DCIExecuteDirect(sTmp);
     
     memset(sTmp,0x00,sizeof(sTmp));
     strcpy(sTmp,"insert into PABYBH_TRADER values(");
     sprintf(sTmp+strlen(sTmp),"'%s','%s','','','')",sSecCode,sSecName);
     LOG( LM_DEBUG, Fmtmsg( "sql语句=[%s]",sTmp), "INFO" );
     
     iRet = DCIExecuteDirect(sTmp);
     if ( iRet < 1 )
     {
          iResult = -1;
          LOG( LM_DEBUG, Fmtmsg( "登记券商信息表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "登记券商信息表失败" );
          break;   
     }
  }

  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }
  
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( " 错误信息=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"事务提交失败");
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
函数名称: PAB_DLCG_CHKINFOLD
名称: 日终对账文件入库
 
组件功能: 日终对账文件入库
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_DEP_CHKINFOLD(HXMLTREE lXmlhandle)
{
  int iParas=0;
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];        /*对账日期*/
  char sFileName[100+1];     /*文件名称（不带路径）*/
  char sFilePath[128+1];     /*文件路径*/
  char sChkFile[255+1];      /*文件名（带路径）*/
  char sBankNo[20+1];        /*合作号*/
  char sSvrCode[4+1];        /*服务代码*/
  double dAmt=0.00;          /*交易金额*/
  char currStep[1+1];        /*当前步点*/
  PABYBH_DEPCHKINFO SDB_depChkInfo;
  
  
  FILE *fp;
  
  int incnt=0;               /*转入笔数*/
  double inAmt=0.00;         /*转入金额*/
  int outcnt=0;              /*转出笔数*/
  double outAmt=0.00;        /*转出金额*/
  char nettype[1+1];              /*轧差方向*/
  double netAmt=0.00;        /*轧差金额*/
  int totcnt=0;               /*总笔数*/
  double totAmt=0.00;         /*总金额*/
  int detotcnt=0;               /*明细总笔数*/
  double detotAmt=0.00;         /*明细总金额*/
 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  /*合作行号*/
  memset(sBankNo, 0x00, sizeof(sBankNo));
  memset(sBuffer, 0x00, sizeof(sBuffer));  
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_COBANKNO, sBuffer);  
  trim(sBuffer);
  memcpy(sBankNo, sBuffer, sizeof(sBankNo)-1);
  /*服务代码*/
  memset(sSvrCode, 0x00, sizeof(sSvrCode));
  memset(sBuffer, 0x00, sizeof(sBuffer));  
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sBuffer);  
  trim(sBuffer);
  memcpy(sSvrCode, sBuffer, sizeof(sSvrCode)-1);
  /*文件路径*/
  memset(sFilePath, 0x00, sizeof(sFilePath));
  memset(sBuffer, 0x00, sizeof(sBuffer));  
  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_PABCHEFP, sBuffer);  
  trim(sBuffer);
  memcpy(sFilePath, sBuffer, sizeof(sFilePath)-1);
  
  memset(sFileName, 0x00, sizeof(sFileName));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "日终对账文件");
  trim(sBuffer);
  pstrcopy(sFileName,sBuffer,sizeof(sFileName));
  
  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "对账日期");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));
  
  LOG(LM_STD, Fmtmsg("对账日期[%s]", sChkDate), fpub_GetCompname(lXmlhandle)); 
  LOG(LM_STD, Fmtmsg("合作行号[%s]", sBankNo), fpub_GetCompname(lXmlhandle));
  LOG(LM_STD, Fmtmsg("服务代码[%s]", sSvrCode), fpub_GetCompname(lXmlhandle));

  if(strlen(sFileName) == 0)
  {
      fpub_SetMsg(lXmlhandle, 98690, "平安对账文件名不能为空");
/*      fpub_SetMsg(lXmlhandle, 98689, "打开文件失败");*/
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("文件名不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  sprintf(sChkFile, "%s/%s", sFilePath, sFileName);
  LOG(LM_STD, Fmtmsg("日终对账文件[%s]", sChkFile), fpub_GetCompname(lXmlhandle));
  
  fp = fopen(sChkFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, 98689, "平安对账文件打开失败");
/*      fpub_SetMsg(lXmlhandle, 98689, "打开文件失败");*/
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("打开文件%s失败",sFileName), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

  memset(sTmp, 0x00, sizeof(sTmp));
  sprintf(sTmp,"delete from PABYBH_DEPCHKINFO where checkDate ='%s' and coBankNo='%s'", sChkDate, sBankNo);
  LOG(LM_STD, Fmtmsg("支持重复对账 [%s]", sTmp), fpub_GetCompname(lXmlhandle)) 
  DCIBegin();
  /*支持重复对账,重复对账时需要将流水表的数据对账全部更新为未对账*/
  iRet=DCIExecuteDirect(sTmp);
	if( iRet < 0 )
  {
      LOG(LM_STD,Fmtmsg("更新对账状态表失败,sqlerr[%s]", DCILastError() ),"ERROR")
      DCIRollback();
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;
  }
  while( !feof(fp) )
  {
  	 memset(sBuffer, 0x00, sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) <= 0 )
         continue; 
     /*总笔数*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     totcnt=atoi(sTmp);
     LOG(LM_STD,Fmtmsg("文件总笔数[%d]",totcnt ),"ERROR")
     
     /*总金额*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     totAmt = atof(sTmp)/100;
     LOG(LM_STD,Fmtmsg("文件总金额[%.2lf]",totAmt ),"ERROR")
     
     break;
  }
  while( !feof(fp) )
  {
     memset(&SDB_depChkInfo, 0x00, sizeof(SDB_depChkInfo));  
     memcpy(SDB_depChkInfo.COBANKNO, sBankNo, sizeof(SDB_depChkInfo.COBANKNO)-1);
     memcpy(SDB_depChkInfo.CHECKDATE,sChkDate,sizeof(SDB_depChkInfo.CHECKDATE)-1);   

     memset(sBuffer, 0x00, sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) <= 0 )
         continue;    

     /*资金类型*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.TRANSFERTYPE,sTmp,sizeof(SDB_depChkInfo.TRANSFERTYPE)-1);
		 
     /*银行帐号*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.ACCTNO,sTmp,sizeof(SDB_depChkInfo.ACCTNO)-1);

     /*券商代码*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,3,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.STOCKCODE,sTmp,sizeof(SDB_depChkInfo.STOCKCODE)-1);

     /*证券资金台账号*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,4,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.CAPITALACCTNO,sTmp,sizeof(SDB_depChkInfo.CAPITALACCTNO)-1);

     /*交易日*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,5,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.TRANSDATE,sTmp,sizeof(SDB_depChkInfo.TRANSDATE)-1);

     /*交易时间*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,6,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.TRANSTIME,sTmp,sizeof(SDB_depChkInfo.TRANSTIME)-1);

     /*金额*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,7,sTmp,'|','\\');
     dAmt = atof(sTmp)/100;
     SDB_depChkInfo.AMT=dAmt;

     /*合作行流水号*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,8,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.WORKSERIALNO,sTmp,sizeof(SDB_depChkInfo.WORKSERIALNO)-1);

     /*银银平台流水号*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,9,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.IEPSERIALNO,sTmp,sizeof(SDB_depChkInfo.IEPSERIALNO)-1);
     LOG(LM_STD,Fmtmsg("detotcnt=[%d],IEPSERIALNO=[%s], strlen(SDB_depChkInfo.IEPSERIALNO)=[%d] ", detotcnt, SDB_depChkInfo.IEPSERIALNO , strlen(SDB_depChkInfo.IEPSERIALNO)),"ERROR")  
 
     if(strlen(SDB_depChkInfo.IEPSERIALNO)<=6)
     {
     		 iResult = -1;
         LOG( LM_DEBUG, Fmtmsg( "平安明细文件银银平台流水号不能为空"), "INFO" );
         fpub_SetMsg(lXmlhandle, 98733, "平安明细文件银银平台流水号不能为空");
         break;
     }


     
     /*入表*/
     memset(sTmp,0x00,sizeof(sTmp));
     iRet = DBInsert( "PABYBH_DEPCHKINFO", SD_PABYBH_DEPCHKINFO, NUMELE( SD_PABYBH_DEPCHKINFO ), &SDB_depChkInfo,sTmp);
     if( iRet < 0 )
     {
         iResult = -1;
         LOG( LM_DEBUG, Fmtmsg( "登记对账明细表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
         fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
         break;   
     }
     
     detotcnt++;
     detotAmt+=SDB_depChkInfo.AMT;
     if(SDB_depChkInfo.TRANSFERTYPE[0] == '0')
		 {
		 	   incnt++;
		 	   inAmt+=SDB_depChkInfo.AMT;
		 }
		 else
		 {
		 	   outcnt++;
		 	   outAmt+=SDB_depChkInfo.AMT;
		 }
  }

  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }
  
  /*比较明细记录和金额与文件中的记录和金额是否一致*/
  if(totcnt == detotcnt && (totAmt - detotAmt) < 0.00001 && (totAmt - detotAmt) > -0.00001)
  {
  		LOG(LM_STD,Fmtmsg("文件统计的记录与金额detotcnt=[%d],detotAmt=[%.2lf]与文件中给出的totcnt=[%d],totAmt=[%.2lf]相等", detotcnt,detotAmt,totcnt,totAmt ),"ERROR")  
  }
  else
  {
  	  LOG(LM_STD,Fmtmsg("文件统计的记录与金额detotcnt=[%d],detotAmt=[%.2lf]与文件中给出的totcnt=[%d],totAmt=[%.2lf]不一致", detotcnt,detotAmt,totcnt,totAmt ),"ERROR")
      DCIRollback();
      fpub_SetMsg(lXmlhandle, 98730, "平安文件给出的汇总信息与明细统计的不一致");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;
  }
  
  COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_INTOTCNT, itoa(incnt));
  memset(sTmp,0x00,sizeof(sTmp));
  sprintf(sTmp,"%.2lf",inAmt);
  COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_INTOTAMT, sTmp);
  
  COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_OUTTOTCNT, itoa(outcnt));
  memset(sTmp,0x00,sizeof(sTmp));
  sprintf(sTmp,"%.2lf",outAmt);
  COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_OUTTOTAMT, sTmp);
  
  if((inAmt-outAmt)> -0.00001)
  {
  	memset(nettype,0x00,sizeof(nettype));
  	nettype[0]='0';
    COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_NETTYPE, "0");
    memset(sTmp,0x00,sizeof(sTmp));
    netAmt=inAmt-outAmt;
  sprintf(sTmp,"%.2lf",netAmt);
    COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_NETAMT, sTmp);
  }
  else
  {
  	memset(nettype,0x00,sizeof(nettype));
  	nettype[0]='1';
    COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_NETTYPE, "1");
    memset(sTmp,0x00,sizeof(sTmp));
    netAmt=outAmt-inAmt;
  sprintf(sTmp,"%.2lf",netAmt);
    COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_NETAMT, sTmp);
  }

    /*更新对账状态表信息*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set totalcount=%d, totalamt=%.2lf, inTotCnt=%d, inTotAmt=%.2lf, outTotCnt=%d, outTotAmt=%.2lf, netAmt=%.2lf, netType='%s', iepChkFile='%s', execStep='1', execStat='0' where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", totcnt, totAmt, incnt, inAmt, outcnt, outAmt, netAmt, nettype, sFileName, sChkDate, sBankNo, sSvrCode);
    LOG( LM_DEBUG, Fmtmsg( "更新对账状态表信息 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("更新对账状态表失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
      
  
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( " 错误信息=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      return COMPRET_FAIL ;
  }
  
  /*当前步点赋值-1*/
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "1"); 
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTAT, "0"); 
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}


/************************************************************************/
/************************************************************************
动态组件函数定义
函数名称: PAB_DLHJ_IEPHXDZ
名称: 与行E同对账
 
组件功能: 
         1.行E通多的;
         2.本行多的;
         3.本行主机成功，行E通未成功，核心尚未冲正的。
         将3种情况列举出来，供合作行柜员参考，对账不平后续处理由各个合作行
         制定自行处理方式。
         
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_IEPCHK( HXMLTREE lXmlhandle )
{
    int iParas=0;
    int iRet=0;
    char sTmp[200];
    char sSql[2048];
    char sBuffer[255];
    char sChkDate[8+1];  /*对帐日期*/
    char sIepDate[8+1];  /*行E通日期*/
    char sSvrCode[10];   /*服务代码*/
    char sBankNo[20];    /*合作行编号*/
    char sBksvr[20];    // 外部交易码
    char sChkTrans[20]; /*参与对账交易代码  格式：'944302','xxxxxx'*/
    char zwrq[8+1];   /*账务日期*/
    char zhqzlsh[20+1];  /*综合前置流水号*/
    char systime[6+1];   /*时间*/
    char  currStep[1+1]; /*当前步点*/
        
    memset(sChkDate, 0x00, sizeof(sChkDate));
    memset(sIepDate, 0x00, sizeof(sIepDate));
    memset(sSvrCode, 0x00, sizeof(sSvrCode)); 
    
    
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    COMP_PARACOUNTCHKMIN(4)
    
    memset(sChkDate, 0x00, sizeof(sChkDate));
    memset(sSvrCode, 0x00, sizeof(sSvrCode));
    memset(sBankNo,  0x00, sizeof(sBankNo));

    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "对帐日期");
    trim(sTmp);
    memcpy(sChkDate, sTmp, 8);
    LOG(LM_DEBUG, Fmtmsg("对帐日期=[%s]", sChkDate), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "服务代码");
    trim(sTmp);
    memcpy(sSvrCode, sTmp, sizeof(sSvrCode)-1);
    LOG(LM_DEBUG, Fmtmsg("服务代码=[%s]", sSvrCode), "");    
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(3, sTmp, "合作行编号");
    trim(sTmp);
    memcpy(sBankNo, sTmp, sizeof(sBankNo)-1);
    LOG(LM_DEBUG, Fmtmsg("合作行编号=[%s]", sBankNo), ""); 
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "参与对账交易代码");
    trim(sTmp);
    memcpy(sChkTrans, sTmp, sizeof(sChkTrans)-1);
    LOG(LM_DEBUG, Fmtmsg("参与对账交易代码=[%s]", sChkTrans), "");
    
    
    /* 外部交易码
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "外部交易码");
    trim(sTmp);
    memcpy(sBksvr, sTmp, sizeof(sBksvr)-1);
    LOG(LM_DEBUG, Fmtmsg("外部交易码=[%s]", sBksvr), ""); 
 */
    /*当前步点*/
    memset(currStep, 0x00, sizeof(currStep));
    memset(sBuffer, 0x00, sizeof(sBuffer));  
    COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTEP, sBuffer);  
    trim(sBuffer);
    memcpy(currStep, sBuffer, sizeof(currStep)-1);
    
    memset(zwrq, 0x00, sizeof(zwrq));
    memset(sBuffer, 0x00, sizeof(sBuffer));  
    COMP_SOFTGETXML("/pub/zwrq", sBuffer);  
    trim(sBuffer);
    memcpy(zwrq, sBuffer, sizeof(zwrq)-1);
    
    memset(zhqzlsh, 0x00, sizeof(zhqzlsh));
    memset(sBuffer, 0x00, sizeof(sBuffer));  
    COMP_SOFTGETXML("/pub/zhqzlsh", sBuffer);  
    trim(sBuffer);
    memcpy(zhqzlsh, sBuffer, sizeof(zhqzlsh)-1);
    
    memset(systime, 0x00, sizeof(systime));
    memset(sBuffer, 0x00, sizeof(sBuffer));  
    COMP_SOFTGETXML("/sys/systime", sBuffer);  
    trim(sBuffer);
    memcpy(systime, sBuffer, sizeof(systime)-1);
   
    memset(sBuffer, 0x00, sizeof(sBuffer));  
    COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTAT, sBuffer);  
    trim(sBuffer);
    LOG(LM_DEBUG, Fmtmsg("步点=[%s]，状态=[%s]", currStep, sBuffer), "");
    /*当前步点<1或步点1执行失败，则不允许本操作执行*/
    if(currStep[0] < '1' || (currStep[0] == '1' && sBuffer[0] != '0'))
    {
        LOG(LM_STD,Fmtmsg("请先完成步点1-对账文件入库,当前步点:%c", currStep[0]),"ERROR")
        fpub_SetMsg(lXmlhandle, 98691, "请先完成步点1-对账文件入库");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    
    /*先以平安银行为主对账*/
    DCIBegin();
    /*恢复原流水对账信息*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.chkflag='0' where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s)", sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "0、恢复原流水对账信息 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("恢复原流水对账信息0未对账失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    
    /*更新本地流水状态-成功，以平安为准*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.stat='0', ser.chkflag='X' where ser.workDate = '%s' and ser.coBankNo='%s' and ser.svrCode='%s'  and transCode in (%s) and exists (select dep.iepSerialNo from PABYBH_DEPCHKINFO dep where dep.checkDate='%s' and dep.coBankNo='%s' and (dep.workSerialNo=ser.workSerialNo or dep.iepSerialNo=ser.iepSerialNo))", sChkDate, sBankNo, sSvrCode, sChkTrans, sChkDate, sBankNo);
    LOG( LM_DEBUG, Fmtmsg( "1、将流水表中状态不成功记录的状态更新为平安的成功状态 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新本地流水状态0失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*更新本地流水状态-失败，以平安为准*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.stat='1', ser.chkflag='X' where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s) and ser.stat='0' and ser.chkflag='0'", sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "2、将流水表中不在平安对账明细中的成功状态记录的状态更新为失败状态 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新本地流水状态1失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*更新本地流水银行账号，以平安为准*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.acctNo=(select dep.acctNo from PABYBH_DEPCHKINFO dep where dep.checkDate='%s' and dep.coBankNo='%s' and (ser.workSerialNo=dep.workSerialNo or ser.iepSerialNo=dep.iepSerialNo)) where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and transCode in (%s) and stat='0'", sChkDate, sBankNo, sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "3、将流水表中银行账号不一致的记录更新 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新本地流水银行账号失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*更新本地流水交易金额，以平安为准*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.transAmt=(select dep.amt from PABYBH_DEPCHKINFO dep where dep.checkDate='%s' and dep.coBankNo='%s' and (ser.workSerialNo=dep.workSerialNo or ser.iepSerialNo=dep.iepSerialNo)) where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and transCode in (%s) and stat='0'", sChkDate, sBankNo, sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "4、将流水表中交易金额不一致的记录更新 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新本地流水交易金额失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*补记本地流水，以平安为准*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"insert into PABYBH_SERIAL select '%s', 'B'||dep.iepSerialNo, '', '', '%s', '%s', case when dep.workSerialNo is null or trim(dep.workSerialNo)='' then 'B'||dep.iepSerialNo else dep.workSerialNo end, dep.transDate, 'Y'||dep.iepSerialNo, '', '',   '%s', '', '', '', '', '', '', '944302', dep.transferType, '', '资金划转', dep.transferType, '%s', '', '', dep.acctNo, '', '', dep.stockCode, dep.capitalAcctNo, dep.amt, 0.00, 0.00, 0.00, '', '', '', '', '%s', dep.transDate, dep.iepSerialNo, '', '', '00', '补录成功', '', '', '', '', '', '00000', '补录成功', '0', '', '0', 'X', '', '', '', '', '', '', '', 'X', '', '', '', '', '' from PABYBH_DEPCHKINFO dep left join  PABYBH_SERIAL ser on (dep.workSerialNo=ser.workSerialNo or dep.iepSerialNo=ser.iepSerialNo) and ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s) where dep.checkDate='%s' and dep.coBankNo='%s'  and ser.workSerialNo is null and ser.iepSerialNo is null", zwrq, systime, sChkDate, sBankNo, sSvrCode, sChkDate, sChkDate, sBankNo, sSvrCode, sChkTrans, sChkDate, sBankNo);
    LOG( LM_DEBUG, Fmtmsg( "5、根据平安明细补录流水 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("补录流水失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*更新对账标志*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.chkflag='X' where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s) and ser.chkflag='0'", sChkDate, sBankNo, sSvrCode, sChkTrans );
    LOG( LM_DEBUG, Fmtmsg( "6、更新对账标志 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新当日流水对账标志失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*更新对账状态表信息*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set execStep='2', execStat='0' where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", sChkDate, sBankNo, sSvrCode);
    LOG( LM_DEBUG, Fmtmsg( "7、更新对账状态表信息 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("更新对账状态表失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    if( DCICommit() != 0 )
    {
        LOG( LM_DEBUG, Fmtmsg( " 错误信息=[%s]",DCILastError()), "INFO" );
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"事务提交失败");
        return COMPRET_FAIL ;
    }    
    /*当前步点赋值-2*/
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "2"); 
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTAT, "0"); 
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}


/************************************************************************
动态组件函数定义
函数名称: PABYBH_CHKTOTACCT
名称: 与行E同对总账
 
组件功能: 
         1.行E通多的;
         2.本行多的;
         3.本行主机成功，行E通未成功，核心尚未冲正的。
         将3种情况列举出来，供合作行柜员参考，对账不平后续处理由各个合作行
         制定自行处理方式。
         
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_CHKTOTACCT( HXMLTREE lXmlhandle )
{
    int iParas=0;
    int iRet=0;
    char sTmp[200];
    char sBuf[1024];
    char sFileName[128];
    char sFilePath[128+1];     /*文件路径*/
    char sChkFile[255+1];      /*文件名（带路径）*/
    int totcnt=0;
    double totamt=0.00;
    int pkgtotcnt=0;
    double pkgtotamt=0.00;
    int loctotcnt=0;
    double loctotamt=0.00;
    
    FILE *fp;
    
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALCOUNT, sTmp);  
    trim(sTmp);
    pkgtotcnt=atoi(sTmp);
    LOG(LM_DEBUG, Fmtmsg("报文中的总笔数=[%d]", pkgtotcnt), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALAMT, sTmp);  
    trim(sTmp);
    pkgtotamt=atof(sTmp);
    LOG(LM_DEBUG, Fmtmsg("报文中总金额=[%lf]", pkgtotamt), "");  
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT, sTmp);  
    trim(sTmp);
    loctotcnt=atoi(sTmp);
    LOG(LM_DEBUG, Fmtmsg("本地总笔数=[%d]", loctotcnt), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT, sTmp);  
    trim(sTmp);
    loctotamt=atof(sTmp);
    LOG(LM_DEBUG, Fmtmsg("本地总金额=[%lf]", loctotamt), "");
        
    memset(sFileName, 0x00, sizeof(sFileName));
  memset(sTmp, 0x00, sizeof(sTmp));
  COMP_GETPARSEPARAS(1, sTmp, "日终对账文件");
  trim(sTmp);
  pstrcopy(sFileName,sTmp,sizeof(sFileName));  
  
  if(strlen(sFileName) == 0)
  {
      fpub_SetMsg(lXmlhandle, 98690, "平安对账文件名不能为空");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("文件名不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

	memset(sFilePath, 0x00, sizeof(sFilePath));
  memset(sTmp, 0x00, sizeof(sTmp));
  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_PABCHEFP, sTmp);
  trim(sTmp);
  pstrcopy(sFilePath,sTmp,sizeof(sFilePath));
  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  sprintf(sChkFile, "%s/%s", sFilePath, sFileName);
  LOG(LM_STD, Fmtmsg("日终对账文件[%s]", sChkFile), fpub_GetCompname(lXmlhandle));
  
  fp = fopen(sChkFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, 98689, "平安对账文件打开失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("打开文件%s失败",sFileName), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  if(feof(fp))
  {
    LOG(LM_STD,Fmtmsg("对账文件为空文件！！"),"ERROR")
        fpub_SetMsg(lXmlhandle, 98713, "平安对账文件为空文件");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
  }
  while( !feof(fp) )
  {
     memset(sBuf, 0x00, sizeof(sBuf));     
     fgets(sBuf, sizeof(sBuf), fp);
     trim(sBuf);
     if(strlen(sBuf) == 0)
         continue;
     /*总笔数*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuf,1,sTmp,'|','\\');
     trim(sTmp);
     totcnt=atoi(sTmp);
     LOG(LM_DEBUG, Fmtmsg("文件总笔数=[%d]", totcnt), "");
    
     
     /*总金额*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuf,2,sTmp,'|','\\');
     trim(sTmp);
     totamt = atof(sTmp)/100;
     LOG(LM_DEBUG, Fmtmsg("文件总金额=[%.2lf]", totamt), "");
    
     break;
  }
  
  if((totamt - pkgtotamt) <0.00001 && (totamt - pkgtotamt) >-0.00001  && totcnt == pkgtotcnt)
  {
    if((totamt - loctotamt) <0.00001 && (totamt - loctotamt) >-0.00001  && totcnt == loctotcnt)
    {
        COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKPABTOTALRESULT, "1");
    }
    else  
    {
    	COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKPABTOTALRESULT, "2");
    }
  }
  else
  {
    LOG(LM_STD,Fmtmsg("平安对账文件与报文的金额、笔数不一致！！"),"ERROR")
        fpub_SetMsg(lXmlhandle, 98644, "平安对账文件与报文的金额、笔数不一致！！");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
  }    
    
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
函数名称: PABYBH_CHKRSLINFO
名称: 对账结果信息登记或更新
 
组件功能: 
         1.行E通多的;
         2.本行多的;
         3.本行主机成功，行E通未成功，核心尚未冲正的。
         将3种情况列举出来，供合作行柜员参考，对账不平后续处理由各个合作行
         制定自行处理方式。
         
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_CHKRSLINFO( HXMLTREE lXmlhandle )
{
    int iParas=0;
    int iRet=0;
    int iLen=0;
    char sTmp[200];
    char sSql[1024];
    char sBuf[1024];
    char sFileName[128];
    char sErrmsg[255];
    PABYBH_CHECKCTL SDB_checkCtl;
    

    
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    memset(&SDB_checkCtl, 0x00, sizeof(SDB_checkCtl));
      
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "对账步点");
    trim(sTmp);
    pstrcopy(SDB_checkCtl.EXECSTEP,sTmp,sizeof(SDB_checkCtl.EXECSTEP));  
    LOG(LM_DEBUG,Fmtmsg("对账步点[%s]",sTmp),"INFO");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "明细对账结果");
    trim(sTmp);
    pstrcopy(SDB_checkCtl.CHKDETAILRESULT,sTmp,sizeof(SDB_checkCtl.CHKDETAILRESULT));  
    LOG(LM_DEBUG,Fmtmsg("明细对账结果[%s]",sTmp),"INFO");
/*    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(3, sTmp, "操作类型");
    trim(sTmp);
    pstrcopy(SDB_checkCtl.CHKDETAILRESULT,sTmp,sizeof(SDB_checkCtl.CHKDETAILRESULT));  
    LOG(LM_DEBUG,Fmtmsg("操作类型[%s]",sTmp),"INFO");
*/    
    /*对账日期*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_CHECKDATE, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.CHECKDATE,sTmp,sizeof(SDB_checkCtl.CHECKDATE));  
    LOG(LM_DEBUG,Fmtmsg("对账日期[%s]",sTmp),"INFO");
    
    /*合作行号*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_COBANKNO, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.COBANKNO,sTmp,sizeof(SDB_checkCtl.COBANKNO));  
    LOG(LM_DEBUG,Fmtmsg("合作行号[%s]",sTmp),"INFO");
    
    /*服务代码*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_SVRCODE, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.SVRCODE,sTmp,sizeof(SDB_checkCtl.SVRCODE));  
    LOG(LM_DEBUG,Fmtmsg("服务代码[%s]",sTmp),"INFO");
    
    /*对账类型*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_MSGTYPE, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.MSGTYPE,sTmp,sizeof(SDB_checkCtl.MSGTYPE));  
    LOG(LM_DEBUG,Fmtmsg("对账类型[%s]",sTmp),"INFO");
      
    DCIBegin();
      memset(sTmp,0x00,sizeof(sTmp));
      memset(sSql,0x00,sizeof(sSql));
      memset(sErrmsg,0x00,sizeof(sErrmsg));
      sprintf(sSql,"select chkdetailresult from PABYBH_CHECKCTL where checkdate='%s' and cobankno='%s' and svrcode='%s' and msgtype='%s'",SDB_checkCtl.CHECKDATE, SDB_checkCtl.COBANKNO, SDB_checkCtl.SVRCODE, SDB_checkCtl.MSGTYPE);
      LOG( LM_DEBUG, Fmtmsg( "查询对账结果表 SQL[%s]", sSql), "INFO" ); 
      iRet = DBSelectToMultiVarChar(sErrmsg,sSql,sTmp);
      trim(sTmp);
      LOG( LM_DEBUG, Fmtmsg( "查询对账结果表 IRET[%d]", iRet), "INFO" ); 
      if( iRet < 0 )
      {
          LOG( LM_DEBUG, Fmtmsg( "查询对账结果信息失败，SQL[%s]", sSql), "INFO" );
          DCIRollback();
          fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
          fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
          return COMPSTATUS_FAIL;     
      }
      if( iRet == 0 )
      {
	        if(SDB_checkCtl.EXECSTEP[0] == '0' || strlen(SDB_checkCtl.EXECSTEP) == 0)
	        {          
		          /*总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("总笔数[%d]",SDB_checkCtl.TOTALCOUNT),"INFO");
		          
		          /*总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("总金额[%.2lf]",SDB_checkCtl.TOTALAMT),"INFO");
		          
		          /*冲正总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("冲正总笔数[%d]",SDB_checkCtl.BACKTOTALCOUNT),"INFO");
		          
		          /*冲正总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("冲正总金额[%.2lf]",SDB_checkCtl.BACKTOTALAMT),"INFO");
		          
		          /*平台总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台总笔数[%d]",SDB_checkCtl.LOCALTOTALCOUNT),"INFO");
		          
		          /*平台总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台总金额[%.2lf]",SDB_checkCtl.LOCALTOTALAMT),"INFO");
		          
		          /*平台冲正总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台冲正总笔数[%.d]",SDB_checkCtl.LOCALBACKTOTALCOUNT),"INFO");
		          
		          /*平台冲正总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台冲正总金额[%.2lf]",SDB_checkCtl.LOCALBACKTOTALAMT),"INFO");
		          
		          /*主机总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机总笔数[%d]",SDB_checkCtl.HOSTTOTALCOUNT),"INFO");
		          
		          /*主机总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机总金额[%.2lf]",SDB_checkCtl.HOSTTOTALAMT),"INFO");
		          
		          /*主机冲正总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机冲正总笔数[%d]",SDB_checkCtl.HOSTBACKTOTALCOUNT),"INFO");
		          
		          /*主机冲正总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机冲正总金额[%.2lf]",SDB_checkCtl.HOSTBACKTOTALAMT),"INFO");
		          
		          /*轧差金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.NETAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("轧差金额[%.2lf]",SDB_checkCtl.NETAMT),"INFO");
		          
		          /*轧差方向  '0收入 1支出'*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETTYPE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.NETTYPE,sTmp,sizeof(SDB_checkCtl.NETTYPE));
		          LOG(LM_DEBUG,Fmtmsg("轧差方向  '0收入 1支出'[%s]",sTmp),"INFO");
		          
		          /*平安对账文件名*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_IEPCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.IEPCHKFILE,sTmp,sizeof(SDB_checkCtl.IEPCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("平安对账文件名[%s]",sTmp),"INFO");
		          
		          /*主机对账文件名*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.HOSTCHKFILE,sTmp,sizeof(SDB_checkCtl.HOSTCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("主机对账文件名[%s]",sTmp),"INFO");
		          
		          /*中心对总账结果*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_CHKPABTOTALRESULT, sTmp);
		          trim(sTmp);
		          if(strlen(sTmp) == 0)
		              SDB_checkCtl.CHKPABTOTALRESULT[0]='0';
		          else pstrcopy(SDB_checkCtl.CHKPABTOTALRESULT,sTmp,sizeof(SDB_checkCtl.CHKPABTOTALRESULT));
		          LOG(LM_DEBUG,Fmtmsg("中心对总账结果[%s]",SDB_checkCtl.CHKPABTOTALRESULT),"INFO");
		          
		          
		          /*执行步点*/
		          LOG(LM_DEBUG,Fmtmsg("执行步点[%s]",SDB_checkCtl.EXECSTEP),"INFO");
		          
		          /*执行状态'0-成功 1-失败'*/
		          if(strlen(SDB_checkCtl.EXECSTEP) != 0)
		          {
		          		if(SDB_checkCtl.CHKPABTOTALRESULT[0] == '3')
		              		SDB_checkCtl.EXECSTAT[0]='1';
		              else SDB_checkCtl.EXECSTAT[0]='0';
		          }
		          LOG(LM_DEBUG,Fmtmsg("执行状态'0-成功 1-失败'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
		          
		          /*明细对账结果*/
		          if(strlen(SDB_checkCtl.CHKDETAILRESULT) == 0)
		            SDB_checkCtl.CHKDETAILRESULT[0]='0';
		          LOG(LM_DEBUG,Fmtmsg("明细对账结果[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
		          
		          
		          /*核心对总账结果*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_CHKHOSTTOTALRESULT, sTmp);
		          trim(sTmp);
		          if(strlen(sTmp) == 0)
		              SDB_checkCtl.CHKHOSTTOTALRESULT[0]='0';
		          else pstrcopy(SDB_checkCtl.CHKHOSTTOTALRESULT,sTmp,sizeof(SDB_checkCtl.CHKHOSTTOTALRESULT));
		          LOG(LM_DEBUG,Fmtmsg("核心对总账结果[%s]",SDB_checkCtl.CHKHOSTTOTALRESULT),"INFO");
		          
		          /*备用字段1*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD1, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD1,sTmp,sizeof(SDB_checkCtl.EXTFLD1));
		          LOG(LM_DEBUG,Fmtmsg("备用字段1[%s]",sTmp),"INFO");
		          
		          /*备用字段2*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD2, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD2,sTmp,sizeof(SDB_checkCtl.EXTFLD2));
		          LOG(LM_DEBUG,Fmtmsg("备用字段2[%s]",sTmp),"INFO");
		          
		          /*备用字段3*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD3, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD3,sTmp,sizeof(SDB_checkCtl.EXTFLD3));
		          LOG(LM_DEBUG,Fmtmsg("备用字段3[%s]",sTmp),"INFO");
		          
		          memset(sTmp,0x00,sizeof(sTmp));
		          iRet = DBInsert( "PABYBH_CHECKCTL", SD_PABYBH_CHECKCTL, NUMELE( SD_PABYBH_CHECKCTL ), &SDB_checkCtl,sTmp);
		          if( iRet < 0 )
		          {
		              DCIRollback();
		              LOG( LM_DEBUG, Fmtmsg( "登记对账结果表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
		              fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		              return COMPSTATUS_FAIL;   
		          }
	      	}
	        else 
	        {
		          DCIRollback();
		          LOG( LM_DEBUG, Fmtmsg("对账信息不存在"), "INFO" );
		          fpub_SetMsg(lXmlhandle, 98715, "对账信息不存在");
		          fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		          return COMPSTATUS_FAIL;
	        }          
      }
      else
      {
	        if(SDB_checkCtl.EXECSTEP[0] == '0')
	        {  
		        	if((strcmp(SDB_checkCtl.SVRCODE, "0101") == 0 || strcmp(SDB_checkCtl.MSGTYPE, "0") == 0) && (sTmp[0] == '1' || sTmp[0] == '9'))
		        	{
				          LOG( LM_DEBUG, Fmtmsg( "资金对账在处理中或已对平，明细对账结果[%s]", sTmp), "INFO" );
				          DCIRollback();
				          fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
				          fpub_SetMsg(lXmlhandle, 98741, "资金对账在处理中或已对平");
				          return COMPSTATUS_FAIL;     
		          }
	        	  memset(sTmp,0x00,sizeof(sTmp));
				      sprintf(sTmp,"delete from PABYBH_CHECKCTL where checkdate ='%s' and cobankno='%s' and svrcode='%s' and msgtype='%s' ",SDB_checkCtl.CHECKDATE, SDB_checkCtl.COBANKNO, SDB_checkCtl.SVRCODE, SDB_checkCtl.MSGTYPE);
				      LOG( LM_DEBUG, Fmtmsg( "删除对账记录表 SQL[%s]", sTmp), "INFO" );
				      iRet=DCIExecuteDirect(sTmp);
			      	if(iRet<0)
			        {
				          DCIRollback();
				          LOG( LM_DEBUG, Fmtmsg("删除对账结果表报错"), "INFO" );
				          fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				          fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
				          return COMPSTATUS_FAIL;
			        }          
		          /*总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("总笔数[%d]",SDB_checkCtl.TOTALCOUNT),"INFO");
		          
		          /*总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("总金额[%.2lf]",SDB_checkCtl.TOTALAMT),"INFO");
		          
		          /*冲正总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("冲正总笔数[%d]",SDB_checkCtl.BACKTOTALCOUNT),"INFO");
		          
		          /*冲正总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("冲正总金额[%.2lf]",SDB_checkCtl.BACKTOTALAMT),"INFO");
		          
		          /*平台总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台总笔数[%d]",SDB_checkCtl.LOCALTOTALCOUNT),"INFO");
		          
		          /*平台总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台总金额[%.2lf]",SDB_checkCtl.LOCALTOTALAMT),"INFO");
		          
		          /*平台冲正总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台冲正总笔数[%d]",SDB_checkCtl.LOCALBACKTOTALCOUNT),"INFO");
		          
		          /*平台冲正总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("平台冲正总金额[%.2lf]",SDB_checkCtl.LOCALBACKTOTALAMT),"INFO");
		          
		          /*主机总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机总笔数[%d]",SDB_checkCtl.HOSTTOTALCOUNT),"INFO");
		          
		          /*主机总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机总金额[%.2lf]",SDB_checkCtl.HOSTTOTALAMT),"INFO");
		          
		          /*主机冲正总笔数*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机冲正总笔数[%d]",SDB_checkCtl.HOSTBACKTOTALCOUNT),"INFO");
		          
		          /*主机冲正总金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("主机冲正总金额[%.2lf]",SDB_checkCtl.HOSTBACKTOTALAMT),"INFO");
		          
		          /*轧差金额*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.NETAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("轧差金额[%.2lf]",SDB_checkCtl.NETAMT),"INFO");
		          
		          /*轧差方向  '0收入 1支出'*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETTYPE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.NETTYPE,sTmp,sizeof(SDB_checkCtl.NETTYPE));
		          LOG(LM_DEBUG,Fmtmsg("轧差方向  '0收入 1支出'[%s]",sTmp),"INFO");
		          
		          /*平安对账文件名*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_IEPCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.IEPCHKFILE,sTmp,sizeof(SDB_checkCtl.IEPCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("平安对账文件名[%s]",sTmp),"INFO");
		          
		          /*主机对账文件名*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.HOSTCHKFILE,sTmp,sizeof(SDB_checkCtl.HOSTCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("主机对账文件名[%s]",sTmp),"INFO");
		          
		          /*中心对总账结果*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_CHKPABTOTALRESULT, sTmp);
		          trim(sTmp);
		          if(strlen(sTmp) == 0)
		          {
		          		SDB_checkCtl.CHKPABTOTALRESULT[0]='0';
		          }
		          else
		          {
		          		pstrcopy(SDB_checkCtl.CHKPABTOTALRESULT,sTmp,sizeof(SDB_checkCtl.CHKPABTOTALRESULT));
		          }
		          LOG(LM_DEBUG,Fmtmsg("中心对总账结果[%s]",SDB_checkCtl.CHKPABTOTALRESULT),"INFO");
		          
		          
		          /*执行步点*/
		          LOG(LM_DEBUG,Fmtmsg("执行步点[%s]",SDB_checkCtl.EXECSTEP),"INFO");
		          
		          /*执行状态'0-成功 1-失败'*/
		          if(SDB_checkCtl.CHKPABTOTALRESULT[0] == '3')
		              SDB_checkCtl.EXECSTAT[0]='1';
		          else SDB_checkCtl.EXECSTAT[0]='0';
		          LOG(LM_DEBUG,Fmtmsg("执行状态'0-成功 1-失败'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
		          
		          /*明细对账结果*/
		          LOG(LM_DEBUG,Fmtmsg("明细对账结果[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
		          
		          
		          /*核心对总账结果*/
		          SDB_checkCtl.CHKHOSTTOTALRESULT[0]='0';
		          LOG(LM_DEBUG,Fmtmsg("核心对总账结果[%s]",SDB_checkCtl.CHKHOSTTOTALRESULT),"INFO");
		          
		          /*备用字段1*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD1, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD1,sTmp,sizeof(SDB_checkCtl.EXTFLD1));
		          LOG(LM_DEBUG,Fmtmsg("备用字段1[%s]",sTmp),"INFO");
		          
		          /*备用字段2*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD2, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD2,sTmp,sizeof(SDB_checkCtl.EXTFLD2));
		          LOG(LM_DEBUG,Fmtmsg("备用字段2[%s]",sTmp),"INFO");
		          
		          /*备用字段3*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD3, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD3,sTmp,sizeof(SDB_checkCtl.EXTFLD3));
		          LOG(LM_DEBUG,Fmtmsg("备用字段3[%s]",sTmp),"INFO");
		          
		          memset(sTmp,0x00,sizeof(sTmp));
		          iRet = DBInsert( "PABYBH_CHECKCTL", SD_PABYBH_CHECKCTL, NUMELE( SD_PABYBH_CHECKCTL ), &SDB_checkCtl,sTmp);
		          if( iRet < 0 )
		          {
		              DCIRollback();
		              LOG( LM_DEBUG, Fmtmsg( "登记对账结果表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
		              fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		              return COMPSTATUS_FAIL;   
		          }
	        }
	        else
	        {
		          memset(sBuf,0x00,sizeof(sBuf));
	          	iLen=0;
	          
		          /*执行步点*/
		          if(strlen(SDB_checkCtl.EXECSTEP)==0)
		          {
			          	if(strlen(SDB_checkCtl.CHKDETAILRESULT)==0)
			          	{
			            		DCIRollback();
				              LOG( LM_DEBUG, Fmtmsg("执行步点和对账结果不能全为空"), "INFO" );
				              fpub_SetMsg(lXmlhandle, 98716, "执行步点和对账结果不能全为空");
				              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
				              return COMPSTATUS_FAIL;
			            }
			            else
			            {
			            		/*明细对账结果*/
			                sprintf(sBuf+iLen,"chkdetailresult='%s'",SDB_checkCtl.CHKDETAILRESULT);
			                iLen=strlen(sBuf);
			                LOG(LM_DEBUG,Fmtmsg("明细对账结果[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
			            }
		            
		          }
		          else 
		          {
		          	  SDB_checkCtl.EXECSTAT[0]='0';
		               
		           
				          /*明细对账结果*/
				          if(SDB_checkCtl.CHKDETAILRESULT[0]!=0)
				          {
					            if(SDB_checkCtl.CHKDETAILRESULT[0] == '3')
					            {
			                  SDB_checkCtl.EXECSTAT[0]='1';
			                  LOG(LM_DEBUG,Fmtmsg("执行状态'0-成功 1-失败'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
					            }
					            sprintf(sBuf+iLen,"chkdetailresult='%s', ",SDB_checkCtl.CHKDETAILRESULT);
					            iLen=strlen(sBuf);
					            LOG(LM_DEBUG,Fmtmsg("明细对账结果[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
				          }
				          LOG(LM_DEBUG,Fmtmsg("执行状态'0-成功 1-失败'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
				          sprintf(sBuf+iLen,"execstep='%s', execstat='%s'",SDB_checkCtl.EXECSTEP, SDB_checkCtl.EXECSTAT);
		              iLen=strlen(sBuf);
		              LOG(LM_DEBUG,Fmtmsg("执行步点[%s]",SDB_checkCtl.EXECSTEP),"INFO");
				          
		          }
		          
		          /*平安对账文件名*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_IEPCHKFILE, sTmp);
		          trim(sTmp);
		          if(sTmp[0]!=0)
		          {
			            sprintf(sBuf+iLen,", iepchkfile='%s'",sTmp);
			            iLen=strlen(sBuf);
			            LOG(LM_DEBUG,Fmtmsg("平安对账文件名[%s]",sTmp),"INFO");
		          }
		          /*主机对账文件名*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE, sTmp);
		          trim(sTmp);
		          if(sTmp[0]!=0)
		          {
			            sprintf(sBuf+iLen,", hostchkfile='%s'",sTmp);
			            iLen=strlen(sBuf);
		          }
		          LOG(LM_DEBUG,Fmtmsg("主机对账文件名[%s]",sTmp),"INFO");
		          
		          
		          
		          memset(sSql,0x00,sizeof(sSql));
		          sprintf(sSql,"update PABYBH_CHECKCTL set %s where checkdate ='%s' and cobankno='%s' and svrcode='%s' and msgtype='%s' ", sBuf, SDB_checkCtl.CHECKDATE, SDB_checkCtl.COBANKNO, SDB_checkCtl.SVRCODE, SDB_checkCtl.MSGTYPE);
		          LOG( LM_DEBUG, Fmtmsg( "更新对账结果表 SQL[%s]", sSql), "INFO" ); 
		      	  iRet=DCIExecuteDirect(sSql);
		          if(iRet<=0)
		          {
		              DCIRollback();
		              LOG( LM_DEBUG, Fmtmsg("更新对账结果表报错"), "INFO" );
		              fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		              return COMPSTATUS_FAIL;
		          }
	        }
        
      }
      
      if( DCICommit() != 0 )
      {
          LOG( LM_DEBUG, Fmtmsg( " 错误信息=[%s]",DCILastError()), "INFO" );
          DCIRollback();
          fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"事务提交失败");
          return COMPRET_FAIL ;
      }
      
      if(SDB_checkCtl.EXECSTEP[0]!=0)
      {
      		/*当前步点赋值*/
    			COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_EXECSTEP, SDB_checkCtl.EXECSTEP); 
    	}
    	
    	if(SDB_checkCtl.EXECSTEP[0]!=0)
      {
      		/*明细对账结果赋值*/
    			COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, SDB_checkCtl.CHKDETAILRESULT); 
    	}
    	
  
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}

