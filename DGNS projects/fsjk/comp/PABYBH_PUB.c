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
�汾:V1.1.1.0
��̬�����������
�����������:PAB_NextWorkDate
�������:PAB_NextWorkDate
�������:ƽ�����й��������л�
�������:
 ��� ��������  ��������            ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   �������          
  2   1-����   ƽ������ҵ������                         
�� Ŀ �飺
�� �� Ա:
��������:
�޸�����:
����ʹ��ʾ��:
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
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

  memset(sBankno, 0x00, sizeof(sBankno));
  memset(sBusiDate, 0x00, sizeof(sBusiDate));
  COMP_GETPARSEPARAS(1, sBankno, "�����к�")
  COMP_GETPARSEPARAS(2, sBusiDate, "ƽ������ҵ������")
  trim(sBankno);
  trim(sBusiDate);

  /*��������ʱΪ�գ�ֱ��������������*/
  if( strlen(sBusiDate) == 0 )
  {
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
      return COMPRET_SUCC;   
  } 

  memset(sWorkDate,0x00,sizeof(sWorkDate));
  COMP_SOFTGETXML(XMLNM_PABYBH_ORGCFG_WORKDATE, sWorkDate);  
	

  memset(sTmp,0x00,sizeof(sTmp));
  LOG( LM_DEBUG, Fmtmsg( "ƽ��������ҵ������=[%s];���й�������=[%s]",sBusiDate,sWorkDate), "INFO" );
  if( strlen(sWorkDate) == 0 || strlen(sBusiDate) == 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "ҵ�����ڲ���Ϊ�� ���й�������=[%s] ƽ��������ҵ������[%s]",sWorkDate,sBusiDate), "INFO" );
      fpub_SetMsg(lXmlhandle, 98799, "ҵ�����ڲ���Ϊ��");
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL;   
  } 
  
  if( strncmp(sWorkDate,sBusiDate,8) != 0 )
  {
      LOG( LM_STD, Fmtmsg( "����Eͨ�������ڲ�һ��,����������Ϊ[%s]�����ڸ���Ϊ[%s]",sBankno,sBusiDate), "ERR" );
      memset(sSql,0x00,sizeof(sSql));
      DCIBegin();
      sprintf(sSql,"update PABYBH_ORGCFG set WORKDATE ='%s' where COBANKNO ='%s' ",sBusiDate,sBankno);
      DCIExecuteDirect(sSql); 
      if( DCICommit() != 0 )
		  {
		      DCIRollback();
		      LOG( LM_STD, Fmtmsg( "�ύ����ʧ��[%s]",DCILastError()), "ERR" );
		      fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "�ύ����ʧ��" );
		      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		      return COMPRET_FAIL;
		  }   
  }
  
    
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}

/************************************************************************
�汾:V1.1.1.0
��̬�����������
�����������:PAB_HeadPkgChk
�������:PAB_HeadPkgChk
�������:ƽ�����й�������ͷУ��
�������:
 ��� ��������  ��������            ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   �������          
  2   1-����   ƽ������ҵ������                         
�� Ŀ �飺
�� �� Ա:
��������:
�޸�����:
����ʹ��ʾ��:
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
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

  memset(sType, 0x00, sizeof(sType));
  COMP_GETPARSEPARAS(1, sType, "��eͨ,ƽ����������ǰ�ñ�־")
  trim(sType);

  /*����Ӧ���־:1-��Eͨ����2-ƽ����������ǰ������*/
  if( strlen(sType) == 0 )
  {
      LOG(LM_STD, Fmtmsg("����Ӧ���־����Ϊ��"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "����Ӧ���־����Ϊ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;          
  }

  memset(sSign,0x00,sizeof(sSign));
  if( sType[0] == '1' )
  {
      /*���������Eͨ�����У����*/
      strcpy(sSign,"iep");

      /*У��ҵ������*/
      memset(sNode,0x00,sizeof(sNode));
      memset(sBuffer,0x00,sizeof(sBuffer));
      sprintf(sNode,"/%s/req/BusinessDate",sSign);
      COMP_SOFTGETXML(sNode, sBuffer)
      if( strlen(trim(sBuffer)) == 0 )
      {
          LOG(LM_STD, Fmtmsg("��Eͨҵ�����ڲ���Ϊ��!"), "DEBUG") 
          fpub_SetMsg(lXmlhandle, 98799, "��Eͨҵ�����ڲ���Ϊ��!");
          fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          return COMPRET_FAIL ;         
      }
      
      /*У��ҵ����ˮ��*/
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
              LOG(LM_STD, Fmtmsg("��Eͨҵ����ˮ����Ϊ��!"), "DEBUG") 
              fpub_SetMsg(lXmlhandle, 98799, "��Eͨҵ����ˮ����Ϊ��!");
              fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
              return COMPRET_FAIL ;         
          } 
      }        
  }
  else
  {
      /*�������ƽ����������ǰ�÷����У����*/
      strcpy(sSign,"pabfe");
  }
      
  /*У�齻�״���*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ExTransCode",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("���״��벻��Ϊ��!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "���״��벻��Ϊ��!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*���׷�������*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ChannelDate",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("���������ڲ���Ϊ��!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "���������ڲ���Ϊ��!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*У�齻��ʱ��*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ChannelTime",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("���׷���ʱ�䲻��Ϊ��!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "���׷���ʱ�䲻��Ϊ��!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*�����б��*/
  memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/ReceivingInstitution",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("�����б�Ų���Ϊ��!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, 98799, "�����б�Ų���Ϊ��!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }

  /*�����л�����*/
  /*memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/AcceptorOrgNo",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("�����л����Ų���Ϊ��!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "�����л����Ų���Ϊ��!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }
  */
  /*��������*/
  /*memset(sNode,0x00,sizeof(sNode));
  memset(sBuffer,0x00,sizeof(sBuffer));
  sprintf(sNode,"/%s/req/TransChannel",sSign);
  COMP_SOFTGETXML(sNode, sBuffer)
  if( strlen(trim(sBuffer)) == 0 )
  {
      LOG(LM_STD, Fmtmsg("������������Ϊ��!"), "DEBUG") 
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "������������Ϊ��!");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL ;         
  }
 */
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}


/************************************************************************
 �汾:V1.1.1.0
 ��̬�����������
 �����������:PABYBH_GETPRONO
 �������:PABYBH_GETPRONO
 �������:����Э�����
 �������:
 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
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
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

  memset(sBuf,0x00,sizeof(sBuf));
  memset(sNodeName,0x00,sizeof(sNodeName));
  COMP_GETPARSEPARAS( 1, sBuf, "��Žڵ�" );
  trim(sBuf);
  if(sBuf[0] == 0)
  {
  		LOG( LM_DEBUG, "��Žڵ㲻��Ϊ�գ�", "INFO" );
      fpub_SetMsg(lXmlhandle, 99999, "��Žڵ㲻��Ϊ�գ�");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;
  }
  pstrcopy(sNodeName, sBuf, sizeof(sNodeName));
  
  memset(sBuf,0x00,sizeof(sBuf));
  COMP_GETPARSEPARAS( 2, sBuf, "Э����ų���" );
  trim(sBuf);
  sNolen=atoi(sBuf);
  /*Ĭ��Ϊ8λ*/
  if(sNolen == 0 || sNolen>8)
 	sNolen=8;
 	
 	memset(sBuf,0x00,sizeof(sBuf));
  COMP_GETPARSEPARAS( 3, sBuf, "�Ƿ��ύ�ڲ�����" );  /*1-�ύ 0-���ύ��Ĭ�ϲ��ύ*/
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
      LOG( LM_DEBUG, Fmtmsg( "��ȡҵ����ˮ��ʧ��=[%d]",iRet), "INFO" );
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
      LOG( LM_STD, Fmtmsg( "ִ��sql���ʧ��[%s];Ӱ���¼����=[%d]",DCILastError(),iRet), "ERR" );
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL;      
  }

	if(flag[0] == '1')
	{  
		  if( DCICommit() != 0 )
		  {
		      DCIRollback();
		      LOG( LM_STD, Fmtmsg( "�ύ����ʧ��[%s]",DCILastError()), "ERR" );
		      fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "�ύ����ʧ��" );
		      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		      return COMPRET_FAIL; 
		  }
  } 
  else LOG( LM_DEBUG, "δ�ύ������ע�������������", "INFO" );
  

#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;  
}

/************************************************************************
��̬�����������
��������: PABYBH_ACCT2NACCT
����: ���������˺�ӳ��
 
�������: ���������˺�ӳ��
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
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
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  memset(sFileName,0x00,sizeof(sFileName));
  COMP_GETPARSEPARAS(1, sFileName, "�˺�ӳ���ļ���")
  trim(sFileName);
  
  fp = fopen(sFileName, "r");
  if ( fp==NULL )
  {
      fpub_SetMsg(lXmlhandle, 98689, "��ȯ����Ϣ�ļ��ļ�ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sFileName), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;      
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

     /*���˺�*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,7,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_accto2n.NEWACCT,sTmp,sizeof(SDB_accto2n.NEWACCT)-1);
     
		/*���˺Ż���*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,3,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_accto2n.NEWORG,sTmp,sizeof(SDB_accto2n.NEWORG)-1);

     /*���˺�*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,6,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_accto2n.OLDACCT,sTmp,sizeof(SDB_accto2n.OLDACCT));     

     /*���˺Ż���*/
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
          LOG( LM_DEBUG, Fmtmsg( "��ѯ�����˺�ӳ���ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "��ѯ�����˺�ӳ���ʧ��" );
          break;   
     }
     if(iRet == 0)
     {   
		     /*���*/
		     memset(sTmp,0x00,sizeof(sTmp));
		     iRet = DBInsert( "PABYBH_ACCTO2N", SD_PABYBH_ACCTO2N, NUMELE( SD_PABYBH_ACCTO2N ), &SDB_accto2n,sTmp);
		     if( iRet < 0 )
		     {
		         iResult = -1;
		         LOG( LM_DEBUG, Fmtmsg( "�Ǽ������˺�ӳ���ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
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
		     LOG( LM_DEBUG, Fmtmsg( "sql���=[%s]",sSql), "INFO" );     
		     iRet = DCIExecuteDirect(sSql);
		     if ( iRet < 1 )
		     {
		          iResult = -1;
		          LOG( LM_DEBUG, Fmtmsg( "���������˺�ӳ���ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
		          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "���������˺�ӳ���ʧ��" );
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
      LOG( LM_DEBUG, Fmtmsg( " ������Ϣ=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"�����ύʧ��");
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
��������: PABYBH_CHECKSRVCODE
����: ƽ̨����У��
 
�������: ƽ̨����У��
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
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
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");
#endif

	  /*ȡ�������*/
  memset(sSvrCode,0x00,sizeof(sSvrCode));
  memset(sTmp,0x00,sizeof(sTmp));
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sTmp);
  trim(sTmp);
  memcpy(sSvrCode, sTmp, sizeof(sSvrCode)-1);
 LOG( LM_DEBUG, Fmtmsg( "�������Ϊ=[%s]",sSvrCode), "INFO" );
  if( strlen(sSvrCode) == 0 )
  {
      LOG( LM_DEBUG, "������벻��Ϊ��!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle,98702 , "������벻��Ϊ��");
     return COMPRET_FAIL ;
//      SetErrorMsg(lXmlhandle,BFE_ERR_SVRCODENULL,"������벻��Ϊ��!");
  //    return -1;
  }
  
   /*ȡ�����к�*/
  memset(sCobankno,0x00,sizeof(sCobankno));
  memset(sTmp,0x00,sizeof(sTmp));
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_COBANKNO, sTmp);
  trim(sTmp);
  memcpy(sCobankno, sTmp, sizeof(sCobankno)-1);
 LOG( LM_DEBUG, Fmtmsg( "�����к�Ϊ=[%s]",sCobankno), "INFO" );
   
  
  memset(&SDB_SvrInfo,0x00,sizeof(SDB_SvrInfo));
  memset(sSql,0x00,sizeof(sSql));
  memset(sBuffer,0x00,sizeof(sBuffer));  
  sprintf(sSql,"select SVRNAME, WORKTIME, SVRSTATUS from PABYBH_SVRINFO where COBANKNO='%s' and SVRCODE = '%s'", sCobankno, sSvrCode);
  LOG( LM_DEBUG, Fmtmsg( "sSql=[%s]",sSql), "INFO" );
  memset(sErr,0x00,sizeof(sErr));
  iRet=DBSelectToMultiVarChar(sErr, sSql, SDB_SvrInfo.SVRNAME, SDB_SvrInfo.WORKTIME, SDB_SvrInfo.SVRSTATUS);
  if( iRet < 0 )
  {
  	LOG( LM_DEBUG, Fmtmsg( "��ѯ������Ϣ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR,"ִ���쳣");
     return COMPRET_FAIL ;
    
  }

  if( iRet == 0 )
  {
      LOG( LM_DEBUG, "������Ϣ����δ����!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, 98686, "������Ϣ����δ����");
     return COMPRET_FAIL ;
    
  }  

  /*��������*/
  trim(SDB_SvrInfo.SVRNAME);
  COMP_SOFTSETXML("/pabybh/req/svrname", SDB_SvrInfo.SVRNAME)  


  /*ҵ��չʱ���*/
  if( strlen(trim(SDB_SvrInfo.WORKTIME)) != 0 )
  {
      /*��ȡ����ʱ�䣺һ��Ҫ׼ȷ*/
      memset(sSysTime,0x00,sizeof(sSysTime));
      COMP_SOFTGETXML("/sys/systime", sSysTime)
      lSysTime = atol(trim(sSysTime));
     
      /*ҵ��ʼʱ��*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(SDB_SvrInfo.WORKTIME,1,sTmp,'|','\\');
      trim(sTmp);  
      LOG( LM_DEBUG, Fmtmsg("start time [%s]",sTmp), "Error" );
      COMP_SOFTSETXML("/pabybh/req/beginTime", sTmp)  
      
      /*�Ƿ�ҵ��ʼʱ��*/
      if( lSysTime < atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "ҵ��δ����չʱ��,��ʼʱ��=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle,98726 , "ҵ��δ����չʱ��");
          return COMPRET_FAIL ;             
      }
           
      /*ҵ�����ʱ��*/
      memset(sTmp,0x00,sizeof(sTmp));

      GetListbyDiv(SDB_SvrInfo.WORKTIME,2,sTmp,'|','\\');
      LOG( LM_DEBUG, Fmtmsg("end time [%s]",sTmp), "Error" );
      trim(sTmp);  
      COMP_SOFTSETXML("/pabybh/req/endTime", sTmp) 

      /*�Ƿ�ҵ�����ʱ��*/
      if( lSysTime > atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "ҵ���ѹ�����ʱ��,����ʱ��=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle, 98727,"ҵ���ѹ�����ʱ��");
          return COMPRET_FAIL ;              
      }     
  }
    
  /*����״̬��0-��Ч;��������Ч*/
  trim(SDB_SvrInfo.SVRSTATUS);
  if( SDB_SvrInfo.SVRSTATUS[0] != '0' )
  {
      LOG( LM_DEBUG, Fmtmsg( "������δ��Ч!״̬=[%s]",SDB_SvrInfo.SVRSTATUS), "INFO" );
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle,98728 , "������δ��Ч");
      return COMPRET_FAIL ;  
  }
  
  COMP_SOFTSETXML("/pabybh/req/svrstatus", SDB_SvrInfo.SVRSTATUS)

#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}
