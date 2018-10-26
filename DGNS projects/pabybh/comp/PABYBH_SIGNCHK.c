#include "gaps_head.h"
#include "xml.h"
#include "DCI.h"
#include "stdlib.h"
#include "stdio.h"
#include "../incl/pabybh_xmlmacro.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/PABYBH_SIGN.h"
/************************************************************************
动态组件函数定义
函数名称: PAB_CKPAB_IN_FILE
名称: 预指定关系对账
 
组件功能:当日建立的预指定关系对账；
         1.平安银行行E通多则补录。
         2.行内多（未对账的记录）则将关系表状态置2（作废）  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
typedef struct TDB_ACCTO
{
  char acctno[32+1];
  char oldacctno[32+1];
  char sign[1+1]
}RECODE_ACCTNO;

IRESULT PABYBH_SIGNCHK(HXMLTREE lXmlhandle)
{
  int iParas;
  int iRet=0;
  int iResult = 0;
  char sBuffer[1024];
  char sSql[1024];
  char sTmp[200+1];
  char sFileName[100+1];
  char sFileType[1+1];     //文件类型  1-帐户 2-销户
  char sFilePath[265+1];  //文件路径
  char sDate[8+1];   //更新日期
  char sTime[6+1];    // 更新时间
  char sNum[8+1];
  char sChkDate[8+1];   //对账日期
  char sInfor[6+1];
  long iCount;
  int iComStat=0;
  int iiRet=0;
    
  char acctno[32+1];
  char oldacctno[32+1];
  char sign[1+1];
  char hostsign[1+1];
  char errMsg[255];
  
  FILE *fp;
  struct stat filestat;

  PABYBH_SIGN pabybh_sign;
  RECODE_ACCTNO recode_acctno;
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  memset(sFileName,0x00,sizeof(sFileName));
  memset(sFileType,0x00,sizeof(sFileType));
  memset(sFilePath,0x00,sizeof(sFilePath));
  memset(sDate,0x00,sizeof(sDate));
  memset(sTime,0x00,sizeof(sTime));
   memset(sNum,0x00,sizeof(sNum));
   memset(sChkDate,0x00,sizeof(sChkDate));
   
  memset(sTmp,0x00,sizeof(sTmp));
  COMP_GETPARSEPARAS(1, sTmp, "文件类型")
	trim(sTmp);  
	memcpy(sFileType,sTmp,sizeof(sFileType)-1);
  
  memset(sTmp,0x00,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "预指定对账明细文件")
  trim(sTmp); 
  memcpy(sFileName,sTmp,sizeof(sFileName)-1);
  LOG(LM_STD, Fmtmsg("预指定对账明细文件[%s]", sFileName), "INFO") 
  LOG(LM_STD, Fmtmsg("文件类型[%s]", sFileType), "INFO") 
  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_PABCHEFP, sFilePath);
   COMP_SOFTGETXML("/sys/sysdate", sDate);
   COMP_SOFTGETXML("/sys/systime", sTime);
   COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_CHECKDATE, sChkDate);
  strcat(sFilePath,"/");
  strcat(sFilePath,sFileName);
   LOG( LM_DEBUG, Fmtmsg( "文件绝对路径为[%s]",sFilePath), "INFO" );
  fp = fopen(sFilePath, "r");
  if ( fp==NULL )
  {
     fpub_SetMsg(lXmlhandle,98689,"打开文件失败") ;    
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("打开文件%s失败",sFileName), fpub_GetCompname(lXmlhandle));
      return COMPRET_FAIL;     
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
  /*初始化对账标志*/
  memset(sSql,0x00,sizeof(sSql));
     sprintf(sSql,"update PABYBH_SIGN set CHKFLAG='0' where UPDATEDATE ='%s' and BUSITYPE ='08' and stat='%c'",sChkDate, sFileType[0]);
     LOG( LM_DEBUG, Fmtmsg( "初始化对账标志sql=[%s]",sSql), "INFO" );
     iRet = DCIExecuteDirect(sSql);
	  if( iRet < 0 )
	  { 
	      LOG( LM_DEBUG, Fmtmsg( "初始化对账标志失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
	      fclose(fp);
	      DCIRollback();
	      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"初始化对账标志失败") ;    
	      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
	      return COMPRET_FAIL ;              
	  }

   memset(sBuffer,0x00,sizeof(sBuffer));     
   fgets(sBuffer, sizeof(sBuffer), fp);
   GetListbyDiv(sBuffer,1,sNum,'|','\\');  
   iCount=0;
  while( !feof(fp) )
  {
     memset(sBuffer,0x00,sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) < 20 )
         continue;
  		
  		iCount++;
      memset(&pabybh_sign,0x00,sizeof(pabybh_sign));
      
           
     /*客户类型*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,1,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CUSTTYPE,sTmp,sizeof(pabybh_sign.CUSTTYPE)-1);
      
      /*银行帐号*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,2,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.ACCTNO,sTmp,sizeof(pabybh_sign.ACCTNO)-1);
      /*券商代码*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,3,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.STOCKCODE,sTmp,sizeof(pabybh_sign.STOCKCODE)-1);   
      
      /*证券资金台账号*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,4,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CAPITALACCTNO,sTmp,sizeof(pabybh_sign.CAPITALACCTNO)-1);    
     
      /*开户日期*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,5,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.SIGNDATE,sTmp,sizeof(pabybh_sign.SIGNDATE)-1);         
                  
      /*开户机构=交易机构*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,6,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.TRANSORG,sTmp,sizeof(pabybh_sign.TRANSORG)-1);   
            
      /*证件类型*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,7,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CERTTYPE,sTmp,sizeof(pabybh_sign.CERTTYPE)-1);     
      
      /*证件号码*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,8,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CERTNO,sTmp,sizeof(pabybh_sign.CERTNO)-1);     
      
      /*客户姓名*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,9,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CUSTNAME,sTmp,sizeof(pabybh_sign.CUSTNAME)-1);
      
      if(sFileType[0]=='2')
			{
			    /*销户日期*/
			    memset(sTmp,0x00,sizeof(sTmp));
			    GetListbyDiv(sBuffer,10,sTmp,'|','\\');
			    trim(sTmp);
			    memcpy(pabybh_sign.UPDATEDATE,sTmp,sizeof(pabybh_sign.UPDATEDATE)-1);
			    /*扩展字段*/
			     memset(sTmp,0x00,sizeof(sTmp));
			     GetListbyDiv(sBuffer,11,sTmp,'|','\\');
			     trim(sTmp);
			     memcpy(pabybh_sign.MEMO,sTmp,sizeof(pabybh_sign.MEMO)-1);
			}
       
     /*匹配本行数据*/
     /*证券编号+证券资金台账号+业务类型为主键*/
     memset(sSql,0x00,sizeof(sSql));
     strcpy(sSql,"select ACCTNO,OLDACCTNO,stat,hoststat from PABYBH_SIGN where");
     sprintf(sSql+strlen(sSql)," STOCKCODE ='%s' and",pabybh_sign.STOCKCODE);
     sprintf(sSql+strlen(sSql)," CAPITALACCTNO ='%s' and",pabybh_sign.CAPITALACCTNO); 
     sprintf(sSql+strlen(sSql)," BUSITYPE ='08'");
     LOG( LM_DEBUG, Fmtmsg( "查询预指定关系表sql=[%s]",sSql), "INFO" );
     

      
     /*判断记录是否存在*/
     memset(acctno,0x00,sizeof(acctno));
     memset(oldacctno,0x00,sizeof(oldacctno));
     memset(sign,0x00,sizeof(sign));
     memset(hostsign,0x00,sizeof(hostsign));
     iRet=DBSelectToMultiVarChar(errMsg, sSql,acctno,oldacctno,sign,hostsign);
     LOG( LM_DEBUG, Fmtmsg( "acctno=[%s] oldacctno=[%s] stat=[%s] hoststat[%s]",acctno,oldacctno,sign,hostsign), "INFO" );
     if( iRet < 0 )
     {
         iResult = -1;
         LOG( LM_DEBUG, Fmtmsg( "查询预指定关系表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"登记预指定关系表失败") ;    
         break; 
     }
  
     else if( iRet == 0 )  /*行E通多补录*/
     {
     			if(sFileType[0]=='2')
     				continue;
     			
          
          
          /*获取协议号*/
			    iiRet=fpub_ExecComp(lXmlhandle,"PABYBH_GETPRONO",&iComStat,3,"/pabybh/tmp/protocolno","6","0");
			    if(iiRet!=MID_SYS_SUCC || iComStat!=COMPSTATUS_SUCC)
			    {
			        iResult = -1;
			        LOG( LM_DEBUG, Fmtmsg( "获取协议号错误！"), "INFO" );
			        fpub_SetMsg(lXmlhandle,99999,"获取协议号错误！") ;    
			        break; 
			    }
    			memset(sTmp,0x00,sizeof(sTmp));
		 /*   memset(sInfor,0x00,sizeof(sInfor));*/
		    	COMP_SOFTGETXML("/pabybh/tmp/protocolno", sTmp);
		    	trim(sTmp);
		    	COMP_SOFTGETXML("/pub/zwrq", pabybh_sign.PROTOCOLNO);
		    	trim(pabybh_sign.PROTOCOLNO);
	         memcpy(pabybh_sign.PROTOCOLNO+8,sTmp,sizeof(pabybh_sign.PROTOCOLNO+8)-1);
	         
	        //服务代码
	        strcpy(pabybh_sign.SVRCODE,"0802");
			     pabybh_sign.STAT[0]='1';
			     pabybh_sign.HOSTSTAT[0]='9'; 
           pabybh_sign.CHKFLAG[0]='1';
           strcpy(pabybh_sign.MEMO,"对账不平补录"); 

          //指定时间
          strcpy(pabybh_sign.SIGNTIME,sTime);
          //指定修改日期、时间
          strcpy(pabybh_sign.UPDATEDATE,sChkDate);
          strcpy(pabybh_sign.UPDATETIME,sTime);
          //合作行号
         COMP_SOFTGETXML(XMLNM_PABYBH_ORGCFG_COBANKNO, pabybh_sign.COBANKNO);
          //业务类型
          strcpy(pabybh_sign.BUSITYPE,"08");
    
          memset(sTmp,0x00,sizeof(sTmp)); 
          iRet = DBInsert( "PABYBH_SIGN", SD_PABYBH_SIGN, NUMELE( SD_PABYBH_SIGN ), &pabybh_sign,sTmp);
          if( iRet <= 0)
          {
              iResult = -2;
              LOG( LM_DEBUG, Fmtmsg( "登记预指定关系表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
              fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"登记预指定关系表失败") ;
              break;   
          }             
     }     
     else  /*对账平,更新对账标志，指定状态*/
     {
         if(strcmp(acctno,pabybh_sign.ACCTNO))
         {
			        memset(oldacctno,0x00,sizeof(oldacctno)); 
			        strcpy(oldacctno,acctno);
		           memset(sSql,0x00,sizeof(sSql));
		           if(strcmp(hostsign, "1") == 0)
		           {
				           if(sFileType[0]=='1')
				               sprintf(sSql,"update PABYBH_SIGN set SIGNDATE='%s', ACCTNO='%s',OLDACCTNO='%s',CERTTYPE='%s',CERTNO='%s', CUSTTYPE='%s', CUSTNAME='%s', STAT='1',HOSTSTAT='9',CHKFLAG='1',updatedate='%s',updatetime='%s' where", pabybh_sign.SIGNDATE, pabybh_sign.ACCTNO,oldacctno,pabybh_sign.CERTTYPE, pabybh_sign.CERTNO,pabybh_sign.CUSTTYPE,pabybh_sign.CUSTNAME,sChkDate,sTime);
				           else  if(sFileType[0]=='2')
				           	   sprintf(sSql,"update PABYBH_SIGN set ACCTNO='%s',OLDACCTNO='%s',CERTTYPE='%s',CERTNO='%s', CUSTTYPE='%s', CUSTNAME='%s', STAT='2',HOSTSTAT='9',CHKFLAG='1',updatedate='%s',updatetime='%s' where",  pabybh_sign.ACCTNO,oldacctno,pabybh_sign.CERTTYPE,pabybh_sign.CERTNO,pabybh_sign.CUSTTYPE,pabybh_sign.CUSTNAME,sChkDate,sTime);
				           
		           } 
		           else
		           {
				           if(sFileType[0]=='1')
				               sprintf(sSql,"update PABYBH_SIGN set SIGNDATE='%s', ACCTNO='%s',OLDACCTNO='%s',CERTTYPE='%s',CERTNO='%s', CUSTTYPE='%s', CUSTNAME='%s',STAT='1',CHKFLAG='1',updatedate='%s',updatetime='%s' where", pabybh_sign.SIGNDATE, pabybh_sign.ACCTNO,oldacctno,pabybh_sign.CERTTYPE, pabybh_sign.CERTNO,pabybh_sign.CUSTTYPE,pabybh_sign.CUSTNAME,sChkDate,sTime);
				           else  if(sFileType[0]=='2')
				           	   sprintf(sSql,"update PABYBH_SIGN set ACCTNO='%s',OLDACCTNO='%s',CERTTYPE='%s',CERTNO='%s', CUSTTYPE='%s', CUSTNAME='%s',STAT='2',CHKFLAG='1',updatedate='%s',updatetime='%s' where",  pabybh_sign.ACCTNO,oldacctno,pabybh_sign.CERTTYPE, pabybh_sign.CERTNO,pabybh_sign.CUSTTYPE,pabybh_sign.CUSTNAME,sChkDate,sTime);
				           
		           }
		  
		           sprintf(sSql+strlen(sSql)," STOCKCODE ='%s' and",pabybh_sign.STOCKCODE);
		           sprintf(sSql+strlen(sSql)," CAPITALACCTNO ='%s' and",pabybh_sign.CAPITALACCTNO);      
		            sprintf(sSql+strlen(sSql)," BUSITYPE ='08'");  
		            LOG( LM_DEBUG, Fmtmsg( "更新预指定关系表sql=[%s]",sSql), "INFO" );
		           iRet = DCIExecuteDirect(sSql);
		           if( iRet < 1 )
		           {
		               iResult = -3;
		               LOG( LM_DEBUG, Fmtmsg( "更新预指定关系表对账状态失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
		               fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"更新预指定关系表对账状态失败") ;    
		               break;                     
		           }              
         }
         else
		     {
		        if(sFileType[0]=='1')
		         {  
		             /*if(sign[0]=='1')
		                     sprintf(sSql,"update PABYBH_SIGN set CHKFLAG='1',updatedate='%s',updatetime='%s' where", pabybh_sign.SIGNDATE,sTime);
		     */
		                     sprintf(sSql,"update PABYBH_SIGN set SIGNDATE='%s',STAT='1',CHKFLAG='1',updatedate='%s',updatetime='%s' where", pabybh_sign.SIGNDATE, sChkDate,sTime);
		    
		         }
		         else if(sFileType[0]=='2')  
		         {
		             /*if(sign[0]=='2')
		                     sprintf(sSql,"update PABYBH_SIGN set CHKFLAG='1',updatedate='%s',updatetime='%s' where", pabybh_sign.UPDATEDATE,sTime);
		     */
		                     sprintf(sSql,"update PABYBH_SIGN set STAT='2',CHKFLAG='1',updatedate='%s',updatetime='%s' where", sChkDate,sTime);
		     
		         }
              sprintf(sSql+strlen(sSql)," STOCKCODE ='%s' and",pabybh_sign.STOCKCODE);
              sprintf(sSql+strlen(sSql)," CAPITALACCTNO ='%s' and",pabybh_sign.CAPITALACCTNO);      
               sprintf(sSql+strlen(sSql)," BUSITYPE ='08'");  
              LOG( LM_DEBUG, Fmtmsg( "更新预指定关系表sql=[%s]",sSql), "INFO" );
              iRet = DCIExecuteDirect(sSql);
              if( iRet < 1 )
              {
                  iResult = -3;
                  LOG( LM_DEBUG, Fmtmsg( "更新预指定关系表对账状态失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
               	 fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"更新预指定关系表对账状态失败") ;
               	 break;    
		          }
		     }    
     }
      
  }  
  
  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "核对明细错！"), "INFO" );
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }
  if(iCount!=atol(sNum))
  {
      DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "文件明细数与总明细数不符"), "INFO" );
      fpub_SetMsg(lXmlhandle,98729,"文件明细数与总明细数不符") ;    
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         

  }


	  
	  if(sFileType[0]=='1')
	  {
			  /*更新本行未对账的指定关系状态为"作废"*/
			  memset(sSql,0x00,sizeof(sSql));
			  sprintf(sSql,"update PABYBH_SIGN set STAT='3', HOSTSTAT='9', CHKFLAG='1', updatedate='%s',updatetime='%s'", sChkDate,sTime);
			  sprintf(sSql+strlen(sSql)," where SIGNDATE ='%s' and CHKFLAG='0' and BUSITYPE ='08' and stat='1'",sChkDate);
			  LOG( LM_DEBUG, Fmtmsg( "更新本行未对账的指定关系状态为-作废sql=[%s]",sSql), "INFO" );
			  iRet = DCIExecuteDirect(sSql);
			  if( iRet < 0 )
			  { 
			      LOG( LM_DEBUG, Fmtmsg( "更新本行未对账的指定关系状态为-作废失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
			      DCIRollback();
			      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"更新本行未对账的指定关系状态为-作废失败") ;    
			      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
			      return COMPRET_FAIL ;              
			  }
    }
    else 
    {
			  /*更新对账标志为1*/
			  memset(sSql,0x00,sizeof(sSql));
			  strcpy(sSql,"update PABYBH_SIGN set CHKFLAG='1'");
			  sprintf(sSql+strlen(sSql)," where UPDATEDATE ='%s' and CHKFLAG='0' and BUSITYPE ='08' and stat='%c'", sChkDate, sFileType[0]);
			  LOG( LM_DEBUG, Fmtmsg( "更新对账标志为1sql=[%s]",sSql), "INFO" );
			  iRet = DCIExecuteDirect(sSql);
			  if( iRet < 0 )
			  { 
			      LOG( LM_DEBUG, Fmtmsg( "更新对账标志为1失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
			      DCIRollback();
			      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"更新对账标志为1失败") ;    
			      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
			      return COMPRET_FAIL ;              
			  }  
     }
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( " 错误信息=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"事务提交失败") ;  
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );  
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}
