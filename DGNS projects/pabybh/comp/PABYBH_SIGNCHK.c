#include "gaps_head.h"
#include "xml.h"
#include "DCI.h"
#include "stdlib.h"
#include "stdio.h"
#include "../incl/pabybh_xmlmacro.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/PABYBH_SIGN.h"
/************************************************************************
��̬�����������
��������: PAB_CKPAB_IN_FILE
����: Ԥָ����ϵ����
 
�������:���ս�����Ԥָ����ϵ���ˣ�
         1.ƽ��������Eͨ����¼��
         2.���ڶࣨδ���˵ļ�¼���򽫹�ϵ��״̬��2�����ϣ�  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
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
  char sFileType[1+1];     //�ļ�����  1-�ʻ� 2-����
  char sFilePath[265+1];  //�ļ�·��
  char sDate[8+1];   //��������
  char sTime[6+1];    // ����ʱ��
  char sNum[8+1];
  char sChkDate[8+1];   //��������
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
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  memset(sFileName,0x00,sizeof(sFileName));
  memset(sFileType,0x00,sizeof(sFileType));
  memset(sFilePath,0x00,sizeof(sFilePath));
  memset(sDate,0x00,sizeof(sDate));
  memset(sTime,0x00,sizeof(sTime));
   memset(sNum,0x00,sizeof(sNum));
   memset(sChkDate,0x00,sizeof(sChkDate));
   
  memset(sTmp,0x00,sizeof(sTmp));
  COMP_GETPARSEPARAS(1, sTmp, "�ļ�����")
	trim(sTmp);  
	memcpy(sFileType,sTmp,sizeof(sFileType)-1);
  
  memset(sTmp,0x00,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "Ԥָ��������ϸ�ļ�")
  trim(sTmp); 
  memcpy(sFileName,sTmp,sizeof(sFileName)-1);
  LOG(LM_STD, Fmtmsg("Ԥָ��������ϸ�ļ�[%s]", sFileName), "INFO") 
  LOG(LM_STD, Fmtmsg("�ļ�����[%s]", sFileType), "INFO") 
  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_PABCHEFP, sFilePath);
   COMP_SOFTGETXML("/sys/sysdate", sDate);
   COMP_SOFTGETXML("/sys/systime", sTime);
   COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_CHECKDATE, sChkDate);
  strcat(sFilePath,"/");
  strcat(sFilePath,sFileName);
   LOG( LM_DEBUG, Fmtmsg( "�ļ�����·��Ϊ[%s]",sFilePath), "INFO" );
  fp = fopen(sFilePath, "r");
  if ( fp==NULL )
  {
     fpub_SetMsg(lXmlhandle,98689,"���ļ�ʧ��") ;    
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sFileName), fpub_GetCompname(lXmlhandle));
      return COMPRET_FAIL;     
  }
  
  fstat(fileno(fp), &filestat);
  if (S_ISDIR(filestat.st_mode))
  {
      fclose(fp);
      fpub_SetMsg(lXmlhandle,98689,"Ŀ¼�ļ�") ;    
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("Ŀ¼�ļ�"), fpub_GetCompname(lXmlhandle)); 
      return COMPRET_FAIL;      
  }
  
  DCIBegin();  
  /*��ʼ�����˱�־*/
  memset(sSql,0x00,sizeof(sSql));
     sprintf(sSql,"update PABYBH_SIGN set CHKFLAG='0' where UPDATEDATE ='%s' and BUSITYPE ='08' and stat='%c'",sChkDate, sFileType[0]);
     LOG( LM_DEBUG, Fmtmsg( "��ʼ�����˱�־sql=[%s]",sSql), "INFO" );
     iRet = DCIExecuteDirect(sSql);
	  if( iRet < 0 )
	  { 
	      LOG( LM_DEBUG, Fmtmsg( "��ʼ�����˱�־ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
	      fclose(fp);
	      DCIRollback();
	      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"��ʼ�����˱�־ʧ��") ;    
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
      
           
     /*�ͻ�����*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,1,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CUSTTYPE,sTmp,sizeof(pabybh_sign.CUSTTYPE)-1);
      
      /*�����ʺ�*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,2,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.ACCTNO,sTmp,sizeof(pabybh_sign.ACCTNO)-1);
      /*ȯ�̴���*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,3,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.STOCKCODE,sTmp,sizeof(pabybh_sign.STOCKCODE)-1);   
      
      /*֤ȯ�ʽ�̨�˺�*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,4,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CAPITALACCTNO,sTmp,sizeof(pabybh_sign.CAPITALACCTNO)-1);    
     
      /*��������*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,5,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.SIGNDATE,sTmp,sizeof(pabybh_sign.SIGNDATE)-1);         
                  
      /*��������=���׻���*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,6,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.TRANSORG,sTmp,sizeof(pabybh_sign.TRANSORG)-1);   
            
      /*֤������*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,7,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CERTTYPE,sTmp,sizeof(pabybh_sign.CERTTYPE)-1);     
      
      /*֤������*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,8,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CERTNO,sTmp,sizeof(pabybh_sign.CERTNO)-1);     
      
      /*�ͻ�����*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(sBuffer,9,sTmp,'|','\\');
      trim(sTmp);
      memcpy(pabybh_sign.CUSTNAME,sTmp,sizeof(pabybh_sign.CUSTNAME)-1);
      
      if(sFileType[0]=='2')
			{
			    /*��������*/
			    memset(sTmp,0x00,sizeof(sTmp));
			    GetListbyDiv(sBuffer,10,sTmp,'|','\\');
			    trim(sTmp);
			    memcpy(pabybh_sign.UPDATEDATE,sTmp,sizeof(pabybh_sign.UPDATEDATE)-1);
			    /*��չ�ֶ�*/
			     memset(sTmp,0x00,sizeof(sTmp));
			     GetListbyDiv(sBuffer,11,sTmp,'|','\\');
			     trim(sTmp);
			     memcpy(pabybh_sign.MEMO,sTmp,sizeof(pabybh_sign.MEMO)-1);
			}
       
     /*ƥ�䱾������*/
     /*֤ȯ���+֤ȯ�ʽ�̨�˺�+ҵ������Ϊ����*/
     memset(sSql,0x00,sizeof(sSql));
     strcpy(sSql,"select ACCTNO,OLDACCTNO,stat,hoststat from PABYBH_SIGN where");
     sprintf(sSql+strlen(sSql)," STOCKCODE ='%s' and",pabybh_sign.STOCKCODE);
     sprintf(sSql+strlen(sSql)," CAPITALACCTNO ='%s' and",pabybh_sign.CAPITALACCTNO); 
     sprintf(sSql+strlen(sSql)," BUSITYPE ='08'");
     LOG( LM_DEBUG, Fmtmsg( "��ѯԤָ����ϵ��sql=[%s]",sSql), "INFO" );
     

      
     /*�жϼ�¼�Ƿ����*/
     memset(acctno,0x00,sizeof(acctno));
     memset(oldacctno,0x00,sizeof(oldacctno));
     memset(sign,0x00,sizeof(sign));
     memset(hostsign,0x00,sizeof(hostsign));
     iRet=DBSelectToMultiVarChar(errMsg, sSql,acctno,oldacctno,sign,hostsign);
     LOG( LM_DEBUG, Fmtmsg( "acctno=[%s] oldacctno=[%s] stat=[%s] hoststat[%s]",acctno,oldacctno,sign,hostsign), "INFO" );
     if( iRet < 0 )
     {
         iResult = -1;
         LOG( LM_DEBUG, Fmtmsg( "��ѯԤָ����ϵ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"�Ǽ�Ԥָ����ϵ��ʧ��") ;    
         break; 
     }
  
     else if( iRet == 0 )  /*��Eͨ�ಹ¼*/
     {
     			if(sFileType[0]=='2')
     				continue;
     			
          
          
          /*��ȡЭ���*/
			    iiRet=fpub_ExecComp(lXmlhandle,"PABYBH_GETPRONO",&iComStat,3,"/pabybh/tmp/protocolno","6","0");
			    if(iiRet!=MID_SYS_SUCC || iComStat!=COMPSTATUS_SUCC)
			    {
			        iResult = -1;
			        LOG( LM_DEBUG, Fmtmsg( "��ȡЭ��Ŵ���"), "INFO" );
			        fpub_SetMsg(lXmlhandle,99999,"��ȡЭ��Ŵ���") ;    
			        break; 
			    }
    			memset(sTmp,0x00,sizeof(sTmp));
		 /*   memset(sInfor,0x00,sizeof(sInfor));*/
		    	COMP_SOFTGETXML("/pabybh/tmp/protocolno", sTmp);
		    	trim(sTmp);
		    	COMP_SOFTGETXML("/pub/zwrq", pabybh_sign.PROTOCOLNO);
		    	trim(pabybh_sign.PROTOCOLNO);
	         memcpy(pabybh_sign.PROTOCOLNO+8,sTmp,sizeof(pabybh_sign.PROTOCOLNO+8)-1);
	         
	        //�������
	        strcpy(pabybh_sign.SVRCODE,"0802");
			     pabybh_sign.STAT[0]='1';
			     pabybh_sign.HOSTSTAT[0]='9'; 
           pabybh_sign.CHKFLAG[0]='1';
           strcpy(pabybh_sign.MEMO,"���˲�ƽ��¼"); 

          //ָ��ʱ��
          strcpy(pabybh_sign.SIGNTIME,sTime);
          //ָ���޸����ڡ�ʱ��
          strcpy(pabybh_sign.UPDATEDATE,sChkDate);
          strcpy(pabybh_sign.UPDATETIME,sTime);
          //�����к�
         COMP_SOFTGETXML(XMLNM_PABYBH_ORGCFG_COBANKNO, pabybh_sign.COBANKNO);
          //ҵ������
          strcpy(pabybh_sign.BUSITYPE,"08");
    
          memset(sTmp,0x00,sizeof(sTmp)); 
          iRet = DBInsert( "PABYBH_SIGN", SD_PABYBH_SIGN, NUMELE( SD_PABYBH_SIGN ), &pabybh_sign,sTmp);
          if( iRet <= 0)
          {
              iResult = -2;
              LOG( LM_DEBUG, Fmtmsg( "�Ǽ�Ԥָ����ϵ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
              fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"�Ǽ�Ԥָ����ϵ��ʧ��") ;
              break;   
          }             
     }     
     else  /*����ƽ,���¶��˱�־��ָ��״̬*/
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
		            LOG( LM_DEBUG, Fmtmsg( "����Ԥָ����ϵ��sql=[%s]",sSql), "INFO" );
		           iRet = DCIExecuteDirect(sSql);
		           if( iRet < 1 )
		           {
		               iResult = -3;
		               LOG( LM_DEBUG, Fmtmsg( "����Ԥָ����ϵ�����״̬ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
		               fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"����Ԥָ����ϵ�����״̬ʧ��") ;    
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
              LOG( LM_DEBUG, Fmtmsg( "����Ԥָ����ϵ��sql=[%s]",sSql), "INFO" );
              iRet = DCIExecuteDirect(sSql);
              if( iRet < 1 )
              {
                  iResult = -3;
                  LOG( LM_DEBUG, Fmtmsg( "����Ԥָ����ϵ�����״̬ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
               	 fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"����Ԥָ����ϵ�����״̬ʧ��") ;
               	 break;    
		          }
		     }    
     }
      
  }  
  
  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "�˶���ϸ��"), "INFO" );
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }
  if(iCount!=atol(sNum))
  {
      DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "�ļ���ϸ��������ϸ������"), "INFO" );
      fpub_SetMsg(lXmlhandle,98729,"�ļ���ϸ��������ϸ������") ;    
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         

  }


	  
	  if(sFileType[0]=='1')
	  {
			  /*���±���δ���˵�ָ����ϵ״̬Ϊ"����"*/
			  memset(sSql,0x00,sizeof(sSql));
			  sprintf(sSql,"update PABYBH_SIGN set STAT='3', HOSTSTAT='9', CHKFLAG='1', updatedate='%s',updatetime='%s'", sChkDate,sTime);
			  sprintf(sSql+strlen(sSql)," where SIGNDATE ='%s' and CHKFLAG='0' and BUSITYPE ='08' and stat='1'",sChkDate);
			  LOG( LM_DEBUG, Fmtmsg( "���±���δ���˵�ָ����ϵ״̬Ϊ-����sql=[%s]",sSql), "INFO" );
			  iRet = DCIExecuteDirect(sSql);
			  if( iRet < 0 )
			  { 
			      LOG( LM_DEBUG, Fmtmsg( "���±���δ���˵�ָ����ϵ״̬Ϊ-����ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
			      DCIRollback();
			      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"���±���δ���˵�ָ����ϵ״̬Ϊ-����ʧ��") ;    
			      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
			      return COMPRET_FAIL ;              
			  }
    }
    else 
    {
			  /*���¶��˱�־Ϊ1*/
			  memset(sSql,0x00,sizeof(sSql));
			  strcpy(sSql,"update PABYBH_SIGN set CHKFLAG='1'");
			  sprintf(sSql+strlen(sSql)," where UPDATEDATE ='%s' and CHKFLAG='0' and BUSITYPE ='08' and stat='%c'", sChkDate, sFileType[0]);
			  LOG( LM_DEBUG, Fmtmsg( "���¶��˱�־Ϊ1sql=[%s]",sSql), "INFO" );
			  iRet = DCIExecuteDirect(sSql);
			  if( iRet < 0 )
			  { 
			      LOG( LM_DEBUG, Fmtmsg( "���¶��˱�־Ϊ1ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
			      DCIRollback();
			      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"���¶��˱�־Ϊ1ʧ��") ;    
			      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
			      return COMPRET_FAIL ;              
			  }  
     }
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( " ������Ϣ=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"�����ύʧ��") ;  
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );  
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}
