#include "DCI.h"
#include "stdlib.h"
#include "stdio.h"
#include "gaps_head.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/pabybh_xmlmacro.h"
#include "../incl/PABYBH_HOSCHKINFO.h"
#include "../incl/PABYBH_NOTBAL.h"


/************************************************************************
动态组件函数定义
函数名称: PAB_ICC_HostChkInfoLd
名称: 主机对账文件入库
 
组件功能: 主机对账文件入库
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_HOSTCHKINFOLD(HXMLTREE lXmlhandle)
{
	  int  iParas=0;
	  int  iRet=0;
	  char sBuffer[1024];
	  char sTmp[255];
	  char sFileName[100+1];    /*主机对账文件*/
	  int  iResult=0;
	  int  iCount=0;
	  int  ict=0;
	  char sSql[1024] = {0};
	  char sExtdate[20] = {0};
	  char sExtchannel[20] = {0};
	  char sExttranscode[20] = {0};
	  char sOpenDate[8+1] = {0};
	  char scoBankNo[10+1];  //合作行号
	  char currStep[1+1];    /*当前步点*/
	  char sFilePath[256+1]; //文件绝对路径
	  char sSrvCode[8+1];   //服务代码
	  char sSerNo[10+1]; //存放业务流水号
	  char sErrmsg[255+1];
	  char ywbh[20];
  
  
	  PABYBH_HOSCHKINFO SDB_HostChkInfo;
	  FILE *fp;
	 
	  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
/*******记得将新老账号处理掉*******/
	  memset(sTmp,0x00,sizeof(sTmp));
	  memset(sFileName,0x00,sizeof(sFileName));
	  COMP_GETPARSEPARAS(1, sFileName, "主机对账文件名")
	  trim(sFileName);
	  LOG( LM_DEBUG, Fmtmsg( "主机对账文件=[%s]",sFileName), "INFO" );
	  
	  memset(sTmp,0x00,sizeof(sTmp));
	  memset(sOpenDate,0x00,sizeof(sOpenDate));
	  COMP_GETPARSEPARAS(2, sTmp, "对账日期")
	  trim(sTmp);
	  memcpy(sOpenDate,sTmp,sizeof(sOpenDate)-1);
	  LOG( LM_DEBUG, Fmtmsg( "对账日期=[%s]",sTmp), "INFO" );
    //合作行号
    memset(scoBankNo,0x00,sizeof(scoBankNo));
	  COMP_SOFTGETXML(XMLNM_PABYBH_ORGCFG_COBANKNO, scoBankNo);  
	  trim(scoBankNo);
	  LOG( LM_DEBUG, Fmtmsg( "合作行号=[%s]",scoBankNo), "INFO" );
	  //文件路径
    memset(sFilePath,0x00,sizeof(sFilePath));
	  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_HOSTCHEFP, sFilePath);  
	  trim(sFilePath);
	  LOG( LM_DEBUG, Fmtmsg( "文件路径=[%s]",sFilePath), "INFO" );
	  strcat(sFilePath,"/");
	  strcat(sFilePath,sFileName);
	  //服务代码
	  memset(sSrvCode,0x00,sizeof(sSrvCode));
	  COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_SVRCODE, sSrvCode);  
	  trim(sSrvCode);
	  LOG( LM_DEBUG, Fmtmsg( "服务代码=[%s]",sSrvCode), "INFO" );
    /*当前步点*/
	  memset(currStep, 0x00, sizeof(currStep));
	  memset(sBuffer, 0x00, sizeof(sBuffer));  
	  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTEP, sBuffer);  
	  trim(sBuffer);
	  memcpy(currStep, sBuffer, sizeof(currStep)-1);
  
    memset(sBuffer, 0x00, sizeof(sBuffer));  
    COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTAT, sBuffer);  
    trim(sBuffer);
    /*当前步点<2或步点2执行失败，则不允许本操作执行*/
    if(currStep[0] < '2' || (currStep[0] == '2' && sBuffer[0] != '0'))
    {
    	  LOG(LM_STD,Fmtmsg("请先完成步点2-平安明细对账,当前步点:%c", currStep[0]),"ERROR")
        fpub_SetMsg(lXmlhandle, 98691, "请先完成步点2-平安明细对账");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
  
	  DCIBegin();
	  
	  sprintf(sSql, "delete from PABYBH_HOSCHKINFO where checkDate='%s' and  cobankno='%s'and svrType='%s'",sOpenDate,scoBankNo,sSrvCode );
	  LOG(LM_DEBUG,Fmtmsg("sql语句=[%s]",sSql),"DEBUG")
	  iRet = DCIExecuteDirect(sSql);
	  if( iRet < 0 )
	  {
	      DCIRollback(); 
	      LOG( LM_DEBUG, Fmtmsg( "删除主机对账临时表失败! 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
	      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"删除主机对账临时表失败");
	      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	      return COMPRET_FAIL ;
	  } 
	
	  fp = fopen(sFilePath, "r");
	  if ( fp==NULL )
	  {
	      DCIRollback(); 
	      fpub_SetMsg(lXmlhandle, 98689, "打开文件失败");
	      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	      LOG(LM_STD, Fmtmsg("打开文件%s失败",sFileName), fpub_GetCompname(lXmlhandle)) 
	      return COMPRET_FAIL ;      
	  }
	  memset(sBuffer,0x00,sizeof(sBuffer));  
	  while ( fgets(sBuffer, sizeof(sBuffer)-1, fp) != NULL )
	  {
	     
				iCount++;
        LOG( LM_DEBUG, Fmtmsg( "----当前第[%d]笔---- ", iCount), "INFO" );          
	      memset(&SDB_HostChkInfo,0x00,sizeof(SDB_HostChkInfo));
	      //合作行
	      memcpy(SDB_HostChkInfo.COBANKNO ,scoBankNo,  sizeof(SDB_HostChkInfo.COBANKNO)-1);
				//对账日期
        memcpy(SDB_HostChkInfo.CHECKDATE ,sOpenDate,  sizeof(SDB_HostChkInfo.CHECKDATE)-1);
 				//平台流水号     
				memset(sTmp,0x00,sizeof(sTmp));
				memset(sSerNo,0x00,sizeof(sSerNo));
        GetListbyDiv(sBuffer,1,sTmp,'|','\\');
        trim(sTmp);
        LOG( LM_DEBUG, Fmtmsg( "平台流水号=[%s]",sTmp), "INFO" );   
				//核心流水号源系统标识号(6位) +源系统交易日期(8位) +批次号(2位) + 业务流水序号(10位)。中间业务系统的标识号为“100021”
				//平台业务流水号取 系统 交易日期+ 10位业务流水号
				if(!strlen(sTmp))
				{
				     iResult = -1;
				     LOG(LM_STD,Fmtmsg("平台流水号不能为空" ),"ERROR")
				     fpub_SetMsg(lXmlhandle, 98736,"平台流水号不能为空");
				     break;
				}
				if(sTmp[6] == 'B')
				{
						memcpy(SDB_HostChkInfo.WORKSERIALNO,sTmp+6,8);
						sprintf(SDB_HostChkInfo.WORKSERIALNO+8,"%ld",atol(sTmp+16));
				}
				else
				{
		        memcpy(SDB_HostChkInfo.WORKSERIALNO,sTmp+6,8);
		        memcpy(sSerNo,sTmp+16,10);
		      	sprintf(SDB_HostChkInfo.WORKSERIALNO+8,"%s",sSerNo);
		    }
        LOG( LM_DEBUG, Fmtmsg( "workserialno=[%s]",SDB_HostChkInfo.WORKSERIALNO), "INFO" );   
	      
	      memset(ywbh,0x00,sizeof(ywbh));
	      //产品代码
	     	memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,4,sTmp,'|','\\');
        trim(sTmp);
        memcpy(ywbh,sTmp,sizeof(ywbh)-1);
        LOG( LM_DEBUG, Fmtmsg( "产品代码=[%s]",sTmp), "INFO" );
        //业务子类
        memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,5,sTmp,'|','\\');
        trim(sTmp);
        memcpy(ywbh+strlen(ywbh),sTmp,  sizeof(20-strlen(ywbh))-1);
        LOG( LM_DEBUG, Fmtmsg( "业务编号=[%s]",ywbh), "INFO" );
        if(strcmp(ywbh, "003001510000") != 0)
        {
        		 LOG(LM_DEBUG, Fmtmsg("非存管业务交易明细"), "INFO" );
        		 continue;
				}
	      
	      //主机日期
	     	memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,7,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTDATE,sTmp,  sizeof(SDB_HostChkInfo.HOSTDATE)-1);
        LOG( LM_DEBUG, Fmtmsg( "主机日期=[%s]",sTmp), "INFO" );   
        //主机流水号
     	  memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,6,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTSERIALNO,sTmp,  sizeof(SDB_HostChkInfo.HOSTSERIALNO)-1);
        LOG( LM_DEBUG, Fmtmsg( "主机流水号=[%s]",sTmp), "INFO" );   
        //主机冲正日期
        memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,9,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTBACKDATE,sTmp,  sizeof(SDB_HostChkInfo.HOSTBACKDATE)-1);
        LOG( LM_DEBUG, Fmtmsg( "主机冲正日期=[%s]",sTmp), "INFO" );   
    
        //主机冲正流水号
        memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,8,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTBACKSERNO,sTmp,  sizeof(SDB_HostChkInfo.HOSTBACKSERNO)-1);
        LOG( LM_DEBUG, Fmtmsg( "主机冲正流水号=[%s]",sTmp), "INFO" );  
        //核心交易代码
        strcpy(SDB_HostChkInfo.HOSTTRANSCODE,"2932");
        //银行账号
     	  memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,10,sTmp,'|','\\');
        trim(sTmp);
        //memcpy(SDB_HostChkInfo.ACCTNO,sTmp,  sizeof(SDB_HostChkInfo.ACCTNO)-1);
        LOG( LM_DEBUG, Fmtmsg( "银行账号=[%s]",sTmp), "INFO" );  
				
        //核心新老账号映射
         memset(sSql,0x00,sizeof(sSql));
         memset(sErrmsg,0x00,sizeof(sErrmsg));
         sprintf(sSql,"select  oldacct from PABYBH_ACCTO2N where  newacct='%s' and coBankNo='%s'",sTmp, scoBankNo);
         LOG( LM_DEBUG, Fmtmsg( "查询核心新老账号映射 SQL[%s]", sSql), "INFO" );
  	     iRet = DBSelectToMultiVarChar( sErrmsg, sSql, SDB_HostChkInfo.ACCTNO ) ;
		     if( iRet < 0 )
		     {
		     			iResult = -1;
		          LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
		          fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		          break;
		     }
	       trim(SDB_HostChkInfo.ACCTNO);
	       //新账号对应的老账号不存在，就用核心传来的账号
	       if(iRet == 0)
	       {
	       			memcpy(SDB_HostChkInfo.ACCTNO,sTmp,  sizeof(SDB_HostChkInfo.ACCTNO)-1);
	       }
	       //对应的老账号存在就用老账号插入主机表，核心传来的账号记录到备用字段
	       else
	       {
			  			memcpy(SDB_HostChkInfo.EXTFLD1,sTmp,  sizeof(SDB_HostChkInfo.ACCTNO)-1);
	       }
 		    //交易金额
     	  memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,11,sTmp,'|','\\');
        trim(sTmp);
        SDB_HostChkInfo.TRANSAMT=atof(sTmp);
        LOG( LM_DEBUG, Fmtmsg( "交易金额=[%s]",sTmp), "INFO" );  

        //状态
     	  memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,12,sTmp,'|','\\');
        trim(sTmp);
        if(sTmp[0]=='2')
        {	
						SDB_HostChkInfo.STAT[0]='7';
						SDB_HostChkInfo.JOINCHKFLAG[0]='0';
				}	
				else if(sTmp[0]=='0')	
				{	
      		  SDB_HostChkInfo.STAT[0]='0';
      		  SDB_HostChkInfo.JOINCHKFLAG[0]='1';
      	}
        LOG( LM_DEBUG, Fmtmsg( "状态=[%s]",sTmp), "INFO" );  

      	//业务种类 -服务代码
        memcpy(SDB_HostChkInfo.SVRTYPE,sSrvCode,  sizeof(SDB_HostChkInfo.SVRTYPE)-1);
	      /*入表*/
	      memset(sBuffer,0x00,sizeof(sBuffer));
	      iRet = DBInsert( "PABYBH_HOSCHKINFO", SD_PABYBH_HOSCHKINFO, NUMELE(SD_PABYBH_HOSCHKINFO),&SDB_HostChkInfo,sBuffer);
	      if( iRet <= 0 )
	      {
	          iResult = -1;
	          LOG( LM_DEBUG, Fmtmsg( "登记主机对账明细表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
	          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "登记主机对账明细表失败" );
	      	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	          break;   
	      }
	      ict++;
      
  	} /* while */

	  fclose(fp);
	  fp = NULL;
	  LOG( LM_DEBUG, Fmtmsg( "-----登记主机对账明细表成功，文件总笔数[%d]，登记总笔数[%d]------ ", iCount, ict ), "INFO" );
	   
	  if( iResult < 0 )
	  {
	      DCIRollback;
	      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
	      return COMPRET_FAIL ;
	  }

		/*更新对账状态表信息*/
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set execStep='4', execStat='0'  where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", sOpenDate, scoBankNo,sSrvCode);
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
	      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"事务提交失败");
	      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	      return COMPRET_FAIL ;
	  }

		/*当前步点赋值*/
		COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "4");
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

IRESULT PABYBH_HOSTCHK( HXMLTREE lXmlhandle )
{
    int iParas=0;
    int iRet=0;
    char sTmp[255];
    char sSql[2048];
    char sErrmsg[1024];
    char sChkDate[8+1];  /*对帐日期*/
    char sSrvCode[10];   /*服务代码*/
    char sBankNo[20];    /*合作行编号*/
    char sBksvr[20];    // 外部交易码
    char sChkTrans[20]; /*参与对账交易代码  格式：'944302','xxxxxx'*/
    char currStep[1+1];   /*当前步点*/
    char chkres[1+1];     /*明细对账结果*/
        
    
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    COMP_PARACOUNTCHKMIN(4)
    
    memset(sChkDate, 0x00, sizeof(sChkDate));
    memset(sSrvCode, 0x00, sizeof(sSrvCode));
    memset(sBankNo,  0x00, sizeof(sBankNo));

    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "对帐日期");
    trim(sTmp);
    memcpy(sChkDate, sTmp, 8);
    LOG(LM_DEBUG, Fmtmsg("对帐日期=[%s]", sChkDate), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "服务代码");
    trim(sTmp);
    memcpy(sSrvCode, sTmp, sizeof(sSrvCode)-1);
    LOG(LM_DEBUG, Fmtmsg("服务代码=[%s]", sSrvCode), "");    
    
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

   /*当前步点*/
	  memset(currStep, 0x00, sizeof(currStep));
	  memset(sTmp, 0x00, sizeof(sTmp));  
	  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTEP, sTmp);  
	  trim(sTmp);
	  memcpy(currStep, sTmp, sizeof(currStep)-1);
  
    memset(sTmp, 0x00, sizeof(sTmp));  
    COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTAT, sTmp);  
    trim(sTmp);
    /*当前步点<4或步点4执行失败，则不允许本操作执行*/
    if(currStep[0] < '4' || (currStep[0] == '4' && sTmp[0] != '0'))
    {
    	  LOG(LM_STD,Fmtmsg("请先完成步点4-对账文件入库,当前步点:%c", currStep[0]),"ERROR")
        fpub_SetMsg(lXmlhandle, 98691, "请先完成步点4-对账文件入库");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }     
    
    /* 外部交易码
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "外部交易码");
    trim(sTmp);
    memcpy(sBksvr, sTmp, sizeof(sBksvr)-1);
    LOG(LM_DEBUG, Fmtmsg("外部交易码=[%s]", sBksvr), ""); 
 */
    DCIBegin();
    /*检查中心对账*/
    
    
    /*1、备份不平明细表*/
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"insert into PABYBH_NOTBAL_HIS select * from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s'", sChkDate, sBankNo, sSrvCode);
    LOG( LM_DEBUG, Fmtmsg( "1、备份对账不平表=[%s]", sSql), "INFO" ); 
    iRet=DCIExecuteDirect(sSql);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("备份对账不平表失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*2、删除对账不平明细表*/
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"delete from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s'", sChkDate, sBankNo, sSrvCode);
    LOG( LM_DEBUG, Fmtmsg( "2、删除对账不平表=[%s]", sSql), "INFO" ); 
    iRet=DCIExecuteDirect(sSql);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("删除对账不平表失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 3、主机对账
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sTmp, 0x00, sizeof( sTmp ) );
    
    sprintf(sSql, "insert into PABYBH_NOTBAL select '%s', '%s', '%s', ser.capitalType, ser.stockCode, ser.capitalAcctNo, ser.workSerialNo, ser.oristat, ser.oriAcctNo, ser.oriTransAmt, ser.transCode, ser.iepSerialNo, ser.stat, ser.acctNo, ser.transAmt, ser.iepTransCode, host.hostDate, host.hostSerialNo, host.stat, host.acctNo, host.transAmt, host.hostTransCode, case when (ser.acctNo=host.acctNo or ser.acctno2=host.acctNo) and ser.transAmt=host.transAmt and ser.stat=host.stat then '1' when host.workSerialNo is null then '2' when ser.workSerialNo is null then '3' when ser.acctNo!=host.acctNo and (ser.acctno2 is null or ser.acctno2 != host.acctno) then '4' when ser.acctNo is null then '4' when host.acctNo is null then '4' when ser.transAmt!=host.transAmt then '5' when ser.stat!=host.stat then '6' end as checkStat, '9', '', '', '', '', '', '', '', '', '', '' from ( select * from PABYBH_SERIAL where workDate='%s' and coBankNo='%s' and svrCode='%s' and transCode in (%s) and stat in ('0','6')) ser full join (select * from PABYBH_HOSCHKINFO where checkDate='%s' and coBankNo='%s' and svrType='%s' and joinChkFlag='1') host on ser.workDate=host.checkDate and ser.workSerialNo=host.workSerialNo and ser.coBankNo=host.coBankNo ", sChkDate, sBankNo, sSrvCode, sChkDate, sBankNo, sSrvCode, sChkTrans, sChkDate, sBankNo, sSrvCode);

    LOG(LM_DEBUG, Fmtmsg("3、主机明细对账[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("核心明细对账操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 4、
       更新当日流水记录的主机对账状态：1-平，4-账号不符，5-金额不符
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL ser set ser.chkFlag=(select no.checkStat from PABYBH_NOTBAL no where no.checkDate='%s' and ser.workSerialNo=no.workSerialNo and no.coBankNo='%s' and no.svrCode='%s' and no.checkStat in('1','4','5','6') ) where ser.workDate='%s' and ser.workSerialNo in (select no.workSerialNo from PABYBH_NOTBAL no where no.checkDate='%s' and no.coBankNo='%s' and no.svrCode='%s' and checkStat in('1','4','5','6'))  ", sChkDate, sBankNo, sSrvCode, sChkDate, sChkDate, sBankNo, sSrvCode );
    LOG(LM_DEBUG, Fmtmsg("4、更新当日流水对账状态1-平,4-账号不符,5-金额不符[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新当日流水对账状态1-平,4-账号不符,5-金额不符的记录操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 5、
       更新当日流水记录的主机对账状态：2-平台多
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL set chkFlag='2' where workDate='%s' and coBankNo='%s' and workSerialNo in (select workSerialNo from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' and  checkStat='2')  ", sChkDate, sBankNo, sChkDate, sBankNo, sSrvCode );    
    LOG(LM_DEBUG, Fmtmsg("5、更新当日流水记录的对账状态：2-平台多[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新当日流水记录的对账状态：2-平台多操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 6、
       更新当日流水记录的主机对账状态：3-平台少
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL set chkFlag='3' where workDate='%s' and coBankNo='%s' and hostSerialNo in (select hostSerialNo from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' and  checkStat='3')  ", sChkDate, sBankNo, sChkDate, sBankNo, sSrvCode);
    LOG(LM_DEBUG, Fmtmsg("6、更新当日流水记录的对账状态：3-平台少[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新当日流水记录的对账状态：3-平台少操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 7、
       更新当日流水记录的主机对账状态：1-平-失败
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL set chkFlag='1' where workDate='%s' and coBankNo='%s' and  svrCode='%s' and  chkflag='X'  ", sChkDate, sBankNo, sSrvCode);
    LOG(LM_DEBUG, Fmtmsg("7、更新当日流水失败记录的对账状态：1-平[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新当日流水失败记录的对账状态：1-平操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 8、
       删除对账平的记录
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " delete from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' and  checkStat='1' ", sChkDate, sBankNo, sSrvCode);    
    LOG(LM_DEBUG, Fmtmsg("8、删除对账平的记录[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("删除对账平的记录操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 9、
       更新不平记录中平台的信息
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " merge into PABYBH_NOTBAL no using (select * from PABYBH_HOSCHKINFO where checkDate='%s' and coBankNo='%s' and svrType='%s' and joinChkFlag='1') host on no.hostSerialNo=host.hostSerialNo and no.checkstat='3' when matched then update set no.workSerialNo=host.workSerialNo, (no.transfertype, no.stockcode, no.capitalacctno, no.bankstat, no.bankacctno, no.bankamt, no.banktranscode) = (select capitaltype, stockcode, capitalacctno, oristat, oriacctno, oritransamt, transcode from PABYBH_SERIAL where workdate='%s' and workserialno=host.workSerialNo ) ", sChkDate, sBankNo, sSrvCode, sChkDate);    
    LOG(LM_DEBUG, Fmtmsg("9、更新不平记录中平台的信息[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("更新不平记录中平台的信息操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 10、统计是否有不平明细，设置日终状态表里的，主机对明细状态 */
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sTmp, 0x00, sizeof( sTmp ) );
    memset( chkres, 0x00, sizeof( chkres ) );
    memset( sErrmsg, 0x00, sizeof( sErrmsg ) );
    sprintf(sSql, "select count( checkStat) from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' ", sChkDate, sBankNo, sSrvCode );    
    LOG(LM_DEBUG, Fmtmsg("10、统计主机不平明细数量[%s]", sSql),"INFO");
    iRet = DBSelectToMultiVarChar( sErrmsg, sSql, sTmp ) ;
    if( iRet < 0 )
    {
    		DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if ( atoi(sTmp)>0 ) /*主机明细对账状态：2-不平*/
    {
    		chkres[0]='2';
        COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, "2");
    }
    else /*主机明细对账状态：1-平*/
    {
    		chkres[0]='1';
        COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, "1");
    }
    
    /*11、更新对账状态表信息*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set execStep='5', execStat='0', chkdetailresult='%s' where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", chkres, sChkDate, sBankNo, sSrvCode);
    LOG( LM_DEBUG, Fmtmsg( "11、更新对账状态表信息 SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("更新对账状态表失败,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
		
		/* 提交事务 */
    if ( DCICommit() != MID_SYS_SUCC )
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "提交事务失败");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*当前步点赋值*/
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "5");
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTAT, "0"); 
    /*明细对账结果赋值*/
    COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, chkres); 
    
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}

