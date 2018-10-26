#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gaps_head.h"
#include "DCI.h"
#include "../incl/pabybh_xmlmacro.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/PABYBH_SVRINFO.h"
#include "../incl/PABYBH_ACCTO2N.h"


/************************************************************************
版本:V1.1.1.0
动态组件函数定义
组件函数名称:PAB_NextWorkDate
组件名称:PAB_NextWorkDate
组件功能:平安银行工作日期切换
组件参数:
 序号 参数类型  参数名称            资源类别     缺省值  可空  参数说明
  1   1-输入   服务代码          
  2   1-输入   平安银行业务日期                         
项 目 组：
程 序 员:
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT PABYBH_NextWorkDate( HXMLTREE lXmlhandle )
{
  char sBankno[30+1];
  char sWorkDate[8+1];
  char sBusiDate[30+1];
  char sTmp[128+1];
  char sSql[1024+1];
  int  iRet=0;
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

  memset(sBankno, 0x00, sizeof(sBankno));
  memset(sBusiDate, 0x00, sizeof(sBusiDate));
  COMP_GETPARSEPARAS(1, sBankno, "合作行号")
  COMP_GETPARSEPARAS(2, sBusiDate, "平安银行业务日期")
  trim(sBankno);
  trim(sBusiDate);

  /*柜面请求时为空，直接跳过后续处理*/
  if( strlen(sBusiDate) == 0 )
  {
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
      return COMPRET_SUCC;   
  } 

  memset(sWorkDate,0x00,sizeof(sWorkDate));
  COMP_SOFTGETXML(XMLNM_PABYBH_ORGCFG_WORKDATE, sWorkDate);  
	

  memset(sTmp,0x00,sizeof(sTmp));
  LOG( LM_DEBUG, Fmtmsg( "平安请求报文业务日期=[%s];本行工作日期=[%s]",sBusiDate,sWorkDate), "INFO" );
  if( strlen(sWorkDate) == 0 || strlen(sBusiDate) == 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "业务日期不能为空 本行工作日期=[%s] 平安请求报文业务日期[%s]",sWorkDate,sBusiDate), "INFO" );
      fpub_SetMsg(lXmlhandle, 98799, "业务日期不能为空");
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL;   
  } 
  
  if( strncmp(sWorkDate,sBusiDate,8) != 0 )
  {
      LOG( LM_STD, Fmtmsg( "与行E通工作日期不一致,将服务类型为[%s]的日期更新为[%s]",sBankno,sBusiDate), "ERR" );
      memset(sSql,0x00,sizeof(sSql));
      DCIBegin();
      sprintf(sSql,"update PABYBH_ORGCFG set WORKDATE ='%s' where COBANKNO ='%s' ",sBusiDate,sBankno);
      DCIExecuteDirect(sSql); 
      if( DCICommit() != 0 )
		  {
		      DCIRollback();
		      LOG( LM_STD, Fmtmsg( "提交事务失败[%s]",DCILastError()), "ERR" );
		      fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "提交事务失败" );
		      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		      return COMPRET_FAIL;
		  }   
  }
  
    
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}

/************************************************************************
版本:V1.1.1.0
动态组件函数定义
组件函数名称:PAB_HeadPkgChk
组件名称:PAB_HeadPkgChk
组件功能:平安银行公共报文头校验
组件参数:
 序号 参数类型  参数名称            资源类别     缺省值  可空  参数说明
  1   1-输入   服务代码          
  2   1-输入   平安银行业务日期                         
项 目 组：
程 序 员:
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT PABYBH_HeadPkgChk( HXMLTREE lXmlhandle )
{
  char sType[30+1];
  char sNode[50+1];
  char sSign[20+1];
  char sBuffer[256+1];
  char sTransCode[12+1];
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

  memset(sType, 0x00, sizeof(sType));
  COMP_GETPARSEPARAS(1, sType, "行e通,平安银行银银前置标志")
  trim(sType);

  /*请求应答标志:1-行E通请求；2-平安银行银银前置请求*/
  if( strlen(sType) == 0 )
  {
      LOG(LM_STD, Fmtmsg("请求应答标志不能为空"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "请求应答标志不能为空");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;          
  }

  memset(sSign,0x00,sizeof(sSign));
  if( sType[0] == '1' )
  {
      /*自行添加行E通请求的校验域*/
      strcpy(sSign,"iep");

      /*校验业务日期*/
      memset(sNode,0x00,sizeof(sNode));
      memset(sBuffer,0x00,sizeof(sBuffer));
      sprintf(sNode,"/%s/req/BusinessDate",sSign);
      COMP_SOFTGETXML(sNode, sBuffer)
      if( strlen(trim(sBuffer)) == 0 )
      {
          LOG(LM_STD, Fmtmsg("行E通业务日期不能为空!"), "DEBUG") 
          fpub_SetMsg(lXmlhandle, 98799, "行E通业务日期不能为空!");
          fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          return COMPRET_FAIL ;         
      }
      
      /*校验业务流水号*/
      memset(sNode,0x00,sizeof(sNode));
      memset(sBuffer,0x00,sizeof(sBuffer));
      sprintf(sNode,"/%s/req/BusinessSerialNo",sSign);
      COMP_SOFTGETXML(sNode, sBuffer)
      
      memset(sNode,0x00,sizeof(sNode));
      memset(sTransCode,0x00,sizeof(sTransCode));
      sprintf(sNode,"/%s/req/ExTransCode",sSign);
      COMP_SOFTGETXML(sNode, sTransCode)
      
      if( strncmp(sTransCode,"900007",6) == 0 )
      {
          if( strlen(trim(sBuffer)) == 0 )
          {
              LOG(LM_STD, Fmtmsg("行E通业务流水不能为空!"), "DEBUG") 
              fpub_SetMsg(lXmlhandle, 98799, "行E通业务流水不能为空!");
              fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
              return COMPRET_FAIL ;         
          } 
      }        
  }
  else
  {
      /*自行添加平安银行银银前置发起的校验域*/
      strcpy(sSign,"pabfe");
  }
      
  /*校验交易代码*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ExTransCode",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("交易代码不能为空!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "交易代码不能为空!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*交易发生日期*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ChannelDate",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("请求交易日期不能为空!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "请求交易日期不能为空!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*校验交易时间*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ChannelTime",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("交易发生时间不能为空!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "交易发生时间不能为空!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*联网行编号*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ReceivingInstitution",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("联网行编号不能为空!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "联网行编号不能为空!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*合作行机构号*/
  /*memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/AcceptorOrgNo",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("合作行机构号不能为空!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "合作行机构号不能为空!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }
  */
  /*交易渠道*/
  /*memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/TransChannel",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("交易渠道不能为空!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "交易渠道不能为空!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }
 */
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}


/************************************************************************
 版本:V1.1.1.0
 动态组件函数定义
 组件函数名称:PABYBH_GETPRONO
 组件名称:PABYBH_GETPRONO
 组件功能:生成协议序号
 组件参数:
 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT PABYBH_GETPRONO( HXMLTREE lXmlhandle )
{
  int iRet=0;
  char sBuf[255];
  char sBuffer[1024];
  char sErr[255];
  char curval[10+1];
  char pinc[10+1];
  char minval[10+1];
  char maxval[10+1];
  char sNodeName[100+1];
  int sNolen=0;
  long iSeque=0;
  long iPinc=0;
  long iMinval=0;
  long iMaxval=0;
  char sSql[1024];
  char flag[1+1];
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

  memset(sBuf,0x00,sizeof(sBuf));
  memset(sNodeName,0x00,sizeof(sNodeName));
  COMP_GETPARSEPARAS( 1, sBuf, "存放节点" );
  trim(sBuf);
  if(sBuf[0] == 0)
  {
  		LOG( LM_DEBUG, "存放节点不能为空！", "INFO" );
      fpub_SetMsg(lXmlhandle, 99999, "存放节点不能为空！");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;
  }
  pstrcopy(sNodeName, sBuf, sizeof(sNodeName));
  
  memset(sBuf,0x00,sizeof(sBuf));
  COMP_GETPARSEPARAS( 2, sBuf, "协议序号长度" );
  trim(sBuf);
  sNolen=atoi(sBuf);
  /*默认为8位*/
  if(sNolen == 0 || sNolen>8)
 	sNolen=8;
 	
 	memset(sBuf,0x00,sizeof(sBuf));
  COMP_GETPARSEPARAS( 3, sBuf, "是否提交内部事务" );  /*1-提交 0-不提交，默认不提交*/
  trim(sBuf);
  pstrcopy(flag, sBuf, sizeof(flag));
  

	DCIBegin();
  memset(sSql,0x00,sizeof(sSql));
  sprintf(sSql,"select CURR_VALUE, PINC, MIN_VALUE, MAX_VALUE from APP_XLKZ where PKEY='K_PABYBH_XYBH' for update");
  
  LOG( LM_DEBUG, Fmtmsg( "SQL=[%s]",sSql), "INFO" );
  
  memset(curval,0x00,sizeof(curval));
  memset(pinc,0x00,sizeof(pinc));
  memset(minval,0x00,sizeof(minval));
  memset(maxval,0x00,sizeof(maxval));
  memset(sErr,0x00,sizeof(sErr));
  iRet=DBSelectToMultiVarChar(sErr, sSql, curval, pinc, minval, maxval);
  if( iRet <= 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "获取业务流水号失败=[%d]",iRet), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;
  }   
  trim(curval);
  trim(pinc);
  trim(minval);
  trim(maxval);
  iSeque = atol(curval);
  iPinc = atol(pinc);
  iMinval = atol(minval);
  iMaxval = atol(maxval);
  
  if( iSeque == iMaxval )
  	  iSeque = iMinval;
  else
  	  iSeque = iSeque + iPinc ;
  
  memset(curval,0x00,sizeof(curval));
  sprintf(curval,"%ld",iSeque);
  
  memset(sBuf,0x00,sizeof(sBuf));
  sprintf(sBuf,"%08ld",iSeque);
  sNolen=strlen(sBuf)-sNolen;
  COMP_SOFTSETXML(sNodeName,sBuf+sNolen);

  memset(sSql,0x00,sizeof(sSql));
  sprintf(sSql,"update APP_XLKZ set CURR_VALUE = '%s' where PKEY='K_PABYBH_XYBH'",curval);

  LOG( LM_DEBUG, Fmtmsg( "SQL=[%s]",sSql), "INFO" );
  iRet = DCIExecuteDirect(sSql);
  if( iRet <= 0 )
  {
  		DCIRollback();
      LOG( LM_STD, Fmtmsg( "执行sql语句失败[%s];影响记录条数=[%d]",DCILastError(),iRet), "ERR" );
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL;      
  }

	if(flag[0] == '1')
	{  
		  if( DCICommit() != 0 )
		  {
		      DCIRollback();
		      LOG( LM_STD, Fmtmsg( "提交事务失败[%s]",DCILastError()), "ERR" );
		      fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "提交事务失败" );
		      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		      return COMPRET_FAIL; 
		  }
  } 
  else LOG( LM_DEBUG, "未提交事务，请注意后续结束事务", "INFO" );
  

#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;  
}

/************************************************************************
动态组件函数定义
函数名称: PABYBH_ACCT2NACCT
名称: 核心新老账号映射
 
组件功能: 核心新老账号映射
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_ACCT2NACCT(HXMLTREE lXmlhandle)
{
  int iParas;
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[200+1];
  char sSql[1024+1];
  char sFileName[100+1];
  char sNewacct[32+1];
  char sOldacct[32+1];
  char sOacct[32+1];
  char cobankno[20];
  char sErr[255];
  FILE *fp;
  struct stat filestat;
  
  PABYBH_ACCTO2N SDB_accto2n;
   
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  memset(sFileName,0x00,sizeof(sFileName));
  COMP_GETPARSEPARAS(1, sFileName, "账号映射文件名")
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
  
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_COBANKNO,cobankno);

  DCIBegin();
  while( !feof(fp) )
  {
     memset(sBuffer,0x00,sizeof(sBuffer));  
     memset(&SDB_accto2n,0x00,sizeof(SDB_accto2n));   
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) < 20 )
         continue;
     
     memcpy(SDB_accto2n.COBANKNO,cobankno,sizeof(SDB_accto2n.COBANKNO)-1);

     /*新账号*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,7,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_accto2n.NEWACCT,sTmp,sizeof(SDB_accto2n.NEWACCT)-1);
     
		/*新账号机构*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,3,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_accto2n.NEWORG,sTmp,sizeof(SDB_accto2n.NEWORG)-1);

     /*老账号*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,6,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_accto2n.OLDACCT,sTmp,sizeof(SDB_accto2n.OLDACCT));     

     /*老账号机构*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_accto2n.OLDORG,sTmp,sizeof(SDB_accto2n.OLDORG));
     
     memset(sSql,0x00,sizeof(sSql));
     memset(sOldacct,0x00,sizeof(sOldacct));
     memset(sNewacct,0x00,sizeof(sNewacct));
     sprintf(sSql,"select newacct, oldacct from PABYBH_ACCTO2N where newacct ='%s' or newacct='%s' ", SDB_accto2n.OLDACCT, SDB_accto2n.NEWACCT);
     memset(sErr,0x00,sizeof(sErr));
     iRet=DBSelectToMultiVarChar(sErr, sSql, sNewacct, sOldacct);
     if ( iRet < 0 )
     {
          iResult = -1;
          LOG( LM_DEBUG, Fmtmsg( "查询新老账号映射表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "查询新老账号映射表失败" );
          break;   
     }
     if(iRet == 0)
     {   
		     /*入表*/
		     memset(sTmp,0x00,sizeof(sTmp));
		     iRet = DBInsert( "PABYBH_ACCTO2N", SD_PABYBH_ACCTO2N, NUMELE( SD_PABYBH_ACCTO2N ), &SDB_accto2n,sTmp);
		     if( iRet < 0 )
		     {
		         iResult = -1;
		         LOG( LM_DEBUG, Fmtmsg( "登记新老账号映射表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
		         fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		         break;   
		     }
     }
     else 
     {
     		if(strcmp(sNewacct, SDB_accto2n.NEWACCT) == 0)
     		{
     				continue;
     		}
		     memset(sSql,0x00,sizeof(sSql));
		     sprintf(sSql,"update PABYBH_ACCTO2N set newacct='%s', neworg='%s' where cobankno='%s' and oldacct='%s'", SDB_accto2n.NEWACCT, SDB_accto2n.NEWORG, SDB_accto2n.COBANKNO, sOldacct);
		     LOG( LM_DEBUG, Fmtmsg( "sql语句=[%s]",sSql), "INFO" );     
		     iRet = DCIExecuteDirect(sSql);
		     if ( iRet < 1 )
		     {
		          iResult = -1;
		          LOG( LM_DEBUG, Fmtmsg( "更新新老账号映射表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
		          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "更新新老账号映射表失败" );
		          break;   
		     }
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
函数名称: PABYBH_CHECKSRVCODE
名称: 平台服务校验
 
组件功能: 平台服务校验
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT PABYBH_CHECKSRVCODE( HXMLTREE lXmlhandle )
{
  char sSql[1024+1];
  char sBuffer[1042],sTmp[128+1];
  char sSvrCode[6+1];
  char sCobankno[12+1];
  int  iRet=0;
  char sSysTime[6+1];
  long lSysTime=0;
  char sErr[255];
  PABYBH_SVRINFO SDB_SvrInfo;

	fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");
#endif

	  /*取服务代码*/
  memset(sSvrCode,0x00,sizeof(sSvrCode));
  memset(sTmp,0x00,sizeof(sTmp));
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sTmp);
  trim(sTmp);
  memcpy(sSvrCode, sTmp, sizeof(sSvrCode)-1);
 LOG( LM_DEBUG, Fmtmsg( "服务代码为=[%s]",sSvrCode), "INFO" );
  if( strlen(sSvrCode) == 0 )
  {
      LOG( LM_DEBUG, "服务代码不能为空!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle,98702 , "服务代码不能为空");
     return COMPRET_FAIL ;
//      SetErrorMsg(lXmlhandle,BFE_ERR_SVRCODENULL,"服务代码不能为空!");
  //    return -1;
  }
  
   /*取合作行号*/
  memset(sCobankno,0x00,sizeof(sCobankno));
  memset(sTmp,0x00,sizeof(sTmp));
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_COBANKNO, sTmp);
  trim(sTmp);
  memcpy(sCobankno, sTmp, sizeof(sCobankno)-1);
 LOG( LM_DEBUG, Fmtmsg( "合作行号为=[%s]",sCobankno), "INFO" );
   
  
  memset(&SDB_SvrInfo,0x00,sizeof(SDB_SvrInfo));
  memset(sSql,0x00,sizeof(sSql));
  memset(sBuffer,0x00,sizeof(sBuffer));  
  sprintf(sSql,"select SVRNAME, WORKTIME, SVRSTATUS from PABYBH_SVRINFO where COBANKNO='%s' and SVRCODE = '%s'", sCobankno, sSvrCode);
  LOG( LM_DEBUG, Fmtmsg( "sSql=[%s]",sSql), "INFO" );
  memset(sErr,0x00,sizeof(sErr));
  iRet=DBSelectToMultiVarChar(sErr, sSql, SDB_SvrInfo.SVRNAME, SDB_SvrInfo.WORKTIME, SDB_SvrInfo.SVRSTATUS);
  if( iRet < 0 )
  {
  	LOG( LM_DEBUG, Fmtmsg( "查询服务信息表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR,"执行异常");
     return COMPRET_FAIL ;
    
  }

  if( iRet == 0 )
  {
      LOG( LM_DEBUG, "服务信息表尚未配置!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, 98686, "服务信息表尚未配置");
     return COMPRET_FAIL ;
    
  }  

  /*服务名称*/
  trim(SDB_SvrInfo.SVRNAME);
  COMP_SOFTSETXML("/pabybh/req/svrname", SDB_SvrInfo.SVRNAME)  


  /*业务开展时间段*/
  if( strlen(trim(SDB_SvrInfo.WORKTIME)) != 0 )
  {
      /*获取机器时间：一定要准确*/
      memset(sSysTime,0x00,sizeof(sSysTime));
      COMP_SOFTGETXML("/sys/systime", sSysTime)
      lSysTime = atol(trim(sSysTime));
     
      /*业务开始时间*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(SDB_SvrInfo.WORKTIME,1,sTmp,'|','\\');
      trim(sTmp);  
      LOG( LM_DEBUG, Fmtmsg("start time [%s]",sTmp), "Error" );
      COMP_SOFTSETXML("/pabybh/req/beginTime", sTmp)  
      
      /*是否到业务开始时间*/
      if( lSysTime < atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "业务未到开展时间,开始时间=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle,98726 , "业务未到开展时间");
          return COMPRET_FAIL ;             
      }
           
      /*业务结束时间*/
      memset(sTmp,0x00,sizeof(sTmp));

      GetListbyDiv(SDB_SvrInfo.WORKTIME,2,sTmp,'|','\\');
      LOG( LM_DEBUG, Fmtmsg("end time [%s]",sTmp), "Error" );
      trim(sTmp);  
      COMP_SOFTSETXML("/pabybh/req/endTime", sTmp) 

      /*是否到业务结束时间*/
      if( lSysTime > atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "业务已过结束时间,结束时间=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle, 98727,"业务已过结束时间");
          return COMPRET_FAIL ;              
      }     
  }
    
  /*服务状态：0-生效;其他不生效*/
  trim(SDB_SvrInfo.SVRSTATUS);
  if( SDB_SvrInfo.SVRSTATUS[0] != '0' )
  {
      LOG( LM_DEBUG, Fmtmsg( "服务尚未生效!状态=[%s]",SDB_SvrInfo.SVRSTATUS), "INFO" );
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle,98728 , "服务尚未生效");
      return COMPRET_FAIL ;  
  }
  
  COMP_SOFTSETXML("/pabybh/req/svrstatus", SDB_SvrInfo.SVRSTATUS)

#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}
