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
��̬�����������
��������: PAB_DLCG_SECLOAD
����: ȯ����Ϣ¼��
 
�������: ȯ����Ϣ¼��
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
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
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  memset(sFileName,0x00,sizeof(sFileName));
  COMP_GETPARSEPARAS(1, sFileName, "ȯ����Ϣ�ļ���")
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

  DCIBegin();
  while( !feof(fp) )
  {
     memset(sBuffer,0x00,sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) < 20 )
         continue;

     /*ȯ�̴���*/
     memset(sTmp,0x00,sizeof(sTmp));
     memset(sSecCode,0x00,sizeof(sSecCode));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     memcpy(sSecCode,sTmp,sizeof(sSecCode)-1);
     

     /*ȯ������*/
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
     LOG( LM_DEBUG, Fmtmsg( "sql���=[%s]",sTmp), "INFO" );
     
     iRet = DCIExecuteDirect(sTmp);
     if ( iRet < 1 )
     {
          iResult = -1;
          LOG( LM_DEBUG, Fmtmsg( "�Ǽ�ȯ����Ϣ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "�Ǽ�ȯ����Ϣ��ʧ��" );
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
��������: PAB_DLCG_CHKINFOLD
����: ���ն����ļ����
 
�������: ���ն����ļ����
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT PABYBH_DEP_CHKINFOLD(HXMLTREE lXmlhandle)
{
  int iParas=0;
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];        /*��������*/
  char sFileName[100+1];     /*�ļ����ƣ�����·����*/
  char sFilePath[128+1];     /*�ļ�·��*/
  char sChkFile[255+1];      /*�ļ�������·����*/
  char sBankNo[20+1];        /*������*/
  char sSvrCode[4+1];        /*�������*/
  double dAmt=0.00;          /*���׽��*/
  char currStep[1+1];        /*��ǰ����*/
  PABYBH_DEPCHKINFO SDB_depChkInfo;
  
  
  FILE *fp;
  
  int incnt=0;               /*ת�����*/
  double inAmt=0.00;         /*ת����*/
  int outcnt=0;              /*ת������*/
  double outAmt=0.00;        /*ת�����*/
  char nettype[1+1];              /*�����*/
  double netAmt=0.00;        /*������*/
  int totcnt=0;               /*�ܱ���*/
  double totAmt=0.00;         /*�ܽ��*/
  int detotcnt=0;               /*��ϸ�ܱ���*/
  double detotAmt=0.00;         /*��ϸ�ܽ��*/
 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  /*�����к�*/
  memset(sBankNo, 0x00, sizeof(sBankNo));
  memset(sBuffer, 0x00, sizeof(sBuffer));  
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_COBANKNO, sBuffer);  
  trim(sBuffer);
  memcpy(sBankNo, sBuffer, sizeof(sBankNo)-1);
  /*�������*/
  memset(sSvrCode, 0x00, sizeof(sSvrCode));
  memset(sBuffer, 0x00, sizeof(sBuffer));  
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sBuffer);  
  trim(sBuffer);
  memcpy(sSvrCode, sBuffer, sizeof(sSvrCode)-1);
  /*�ļ�·��*/
  memset(sFilePath, 0x00, sizeof(sFilePath));
  memset(sBuffer, 0x00, sizeof(sBuffer));  
  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_PABCHEFP, sBuffer);  
  trim(sBuffer);
  memcpy(sFilePath, sBuffer, sizeof(sFilePath)-1);
  
  memset(sFileName, 0x00, sizeof(sFileName));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "���ն����ļ�");
  trim(sBuffer);
  pstrcopy(sFileName,sBuffer,sizeof(sFileName));
  
  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "��������");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));
  
  LOG(LM_STD, Fmtmsg("��������[%s]", sChkDate), fpub_GetCompname(lXmlhandle)); 
  LOG(LM_STD, Fmtmsg("�����к�[%s]", sBankNo), fpub_GetCompname(lXmlhandle));
  LOG(LM_STD, Fmtmsg("�������[%s]", sSvrCode), fpub_GetCompname(lXmlhandle));

  if(strlen(sFileName) == 0)
  {
      fpub_SetMsg(lXmlhandle, 98690, "ƽ�������ļ�������Ϊ��");
/*      fpub_SetMsg(lXmlhandle, 98689, "���ļ�ʧ��");*/
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�ļ�������Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  sprintf(sChkFile, "%s/%s", sFilePath, sFileName);
  LOG(LM_STD, Fmtmsg("���ն����ļ�[%s]", sChkFile), fpub_GetCompname(lXmlhandle));
  
  fp = fopen(sChkFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, 98689, "ƽ�������ļ���ʧ��");
/*      fpub_SetMsg(lXmlhandle, 98689, "���ļ�ʧ��");*/
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sFileName), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

  memset(sTmp, 0x00, sizeof(sTmp));
  sprintf(sTmp,"delete from PABYBH_DEPCHKINFO where checkDate ='%s' and coBankNo='%s'", sChkDate, sBankNo);
  LOG(LM_STD, Fmtmsg("֧���ظ����� [%s]", sTmp), fpub_GetCompname(lXmlhandle)) 
  DCIBegin();
  /*֧���ظ�����,�ظ�����ʱ��Ҫ����ˮ������ݶ���ȫ������Ϊδ����*/
  iRet=DCIExecuteDirect(sTmp);
	if( iRet < 0 )
  {
      LOG(LM_STD,Fmtmsg("���¶���״̬��ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
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
     /*�ܱ���*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     totcnt=atoi(sTmp);
     LOG(LM_STD,Fmtmsg("�ļ��ܱ���[%d]",totcnt ),"ERROR")
     
     /*�ܽ��*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     totAmt = atof(sTmp)/100;
     LOG(LM_STD,Fmtmsg("�ļ��ܽ��[%.2lf]",totAmt ),"ERROR")
     
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

     /*�ʽ�����*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.TRANSFERTYPE,sTmp,sizeof(SDB_depChkInfo.TRANSFERTYPE)-1);
		 
     /*�����ʺ�*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.ACCTNO,sTmp,sizeof(SDB_depChkInfo.ACCTNO)-1);

     /*ȯ�̴���*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,3,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.STOCKCODE,sTmp,sizeof(SDB_depChkInfo.STOCKCODE)-1);

     /*֤ȯ�ʽ�̨�˺�*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,4,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.CAPITALACCTNO,sTmp,sizeof(SDB_depChkInfo.CAPITALACCTNO)-1);

     /*������*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,5,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.TRANSDATE,sTmp,sizeof(SDB_depChkInfo.TRANSDATE)-1);

     /*����ʱ��*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,6,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.TRANSTIME,sTmp,sizeof(SDB_depChkInfo.TRANSTIME)-1);

     /*���*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,7,sTmp,'|','\\');
     dAmt = atof(sTmp)/100;
     SDB_depChkInfo.AMT=dAmt;

     /*��������ˮ��*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,8,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.WORKSERIALNO,sTmp,sizeof(SDB_depChkInfo.WORKSERIALNO)-1);

     /*����ƽ̨��ˮ��*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,9,sTmp,'|','\\');
     trim(sTmp);
     memcpy(SDB_depChkInfo.IEPSERIALNO,sTmp,sizeof(SDB_depChkInfo.IEPSERIALNO)-1);
     LOG(LM_STD,Fmtmsg("detotcnt=[%d],IEPSERIALNO=[%s], strlen(SDB_depChkInfo.IEPSERIALNO)=[%d] ", detotcnt, SDB_depChkInfo.IEPSERIALNO , strlen(SDB_depChkInfo.IEPSERIALNO)),"ERROR")  
 
     if(strlen(SDB_depChkInfo.IEPSERIALNO)<=6)
     {
     		 iResult = -1;
         LOG( LM_DEBUG, Fmtmsg( "ƽ����ϸ�ļ�����ƽ̨��ˮ�Ų���Ϊ��"), "INFO" );
         fpub_SetMsg(lXmlhandle, 98733, "ƽ����ϸ�ļ�����ƽ̨��ˮ�Ų���Ϊ��");
         break;
     }


     
     /*���*/
     memset(sTmp,0x00,sizeof(sTmp));
     iRet = DBInsert( "PABYBH_DEPCHKINFO", SD_PABYBH_DEPCHKINFO, NUMELE( SD_PABYBH_DEPCHKINFO ), &SDB_depChkInfo,sTmp);
     if( iRet < 0 )
     {
         iResult = -1;
         LOG( LM_DEBUG, Fmtmsg( "�ǼǶ�����ϸ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
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
  
  /*�Ƚ���ϸ��¼�ͽ�����ļ��еļ�¼�ͽ���Ƿ�һ��*/
  if(totcnt == detotcnt && (totAmt - detotAmt) < 0.00001 && (totAmt - detotAmt) > -0.00001)
  {
  		LOG(LM_STD,Fmtmsg("�ļ�ͳ�Ƶļ�¼����detotcnt=[%d],detotAmt=[%.2lf]���ļ��и�����totcnt=[%d],totAmt=[%.2lf]���", detotcnt,detotAmt,totcnt,totAmt ),"ERROR")  
  }
  else
  {
  	  LOG(LM_STD,Fmtmsg("�ļ�ͳ�Ƶļ�¼����detotcnt=[%d],detotAmt=[%.2lf]���ļ��и�����totcnt=[%d],totAmt=[%.2lf]��һ��", detotcnt,detotAmt,totcnt,totAmt ),"ERROR")
      DCIRollback();
      fpub_SetMsg(lXmlhandle, 98730, "ƽ���ļ������Ļ�����Ϣ����ϸͳ�ƵĲ�һ��");
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

    /*���¶���״̬����Ϣ*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set totalcount=%d, totalamt=%.2lf, inTotCnt=%d, inTotAmt=%.2lf, outTotCnt=%d, outTotAmt=%.2lf, netAmt=%.2lf, netType='%s', iepChkFile='%s', execStep='1', execStat='0' where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", totcnt, totAmt, incnt, inAmt, outcnt, outAmt, netAmt, nettype, sFileName, sChkDate, sBankNo, sSvrCode);
    LOG( LM_DEBUG, Fmtmsg( "���¶���״̬����Ϣ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("���¶���״̬��ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
      
  
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( " ������Ϣ=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      return COMPRET_FAIL ;
  }
  
  /*��ǰ���㸳ֵ-1*/
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "1"); 
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTAT, "0"); 
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}


/************************************************************************/
/************************************************************************
��̬�����������
��������: PAB_DLHJ_IEPHXDZ
����: ����Eͬ����
 
�������: 
         1.��Eͨ���;
         2.���ж��;
         3.���������ɹ�����Eͨδ�ɹ���������δ�����ġ�
         ��3������оٳ������������й�Ա�ο������˲�ƽ���������ɸ���������
         �ƶ����д���ʽ��
         
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT PABYBH_IEPCHK( HXMLTREE lXmlhandle )
{
    int iParas=0;
    int iRet=0;
    char sTmp[200];
    char sSql[2048];
    char sBuffer[255];
    char sChkDate[8+1];  /*��������*/
    char sIepDate[8+1];  /*��Eͨ����*/
    char sSvrCode[10];   /*�������*/
    char sBankNo[20];    /*�����б��*/
    char sBksvr[20];    // �ⲿ������
    char sChkTrans[20]; /*������˽��״���  ��ʽ��'944302','xxxxxx'*/
    char zwrq[8+1];   /*��������*/
    char zhqzlsh[20+1];  /*�ۺ�ǰ����ˮ��*/
    char systime[6+1];   /*ʱ��*/
    char  currStep[1+1]; /*��ǰ����*/
        
    memset(sChkDate, 0x00, sizeof(sChkDate));
    memset(sIepDate, 0x00, sizeof(sIepDate));
    memset(sSvrCode, 0x00, sizeof(sSvrCode)); 
    
    
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    COMP_PARACOUNTCHKMIN(4)
    
    memset(sChkDate, 0x00, sizeof(sChkDate));
    memset(sSvrCode, 0x00, sizeof(sSvrCode));
    memset(sBankNo,  0x00, sizeof(sBankNo));

    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "��������");
    trim(sTmp);
    memcpy(sChkDate, sTmp, 8);
    LOG(LM_DEBUG, Fmtmsg("��������=[%s]", sChkDate), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "�������");
    trim(sTmp);
    memcpy(sSvrCode, sTmp, sizeof(sSvrCode)-1);
    LOG(LM_DEBUG, Fmtmsg("�������=[%s]", sSvrCode), "");    
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(3, sTmp, "�����б��");
    trim(sTmp);
    memcpy(sBankNo, sTmp, sizeof(sBankNo)-1);
    LOG(LM_DEBUG, Fmtmsg("�����б��=[%s]", sBankNo), ""); 
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "������˽��״���");
    trim(sTmp);
    memcpy(sChkTrans, sTmp, sizeof(sChkTrans)-1);
    LOG(LM_DEBUG, Fmtmsg("������˽��״���=[%s]", sChkTrans), "");
    
    
    /* �ⲿ������
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "�ⲿ������");
    trim(sTmp);
    memcpy(sBksvr, sTmp, sizeof(sBksvr)-1);
    LOG(LM_DEBUG, Fmtmsg("�ⲿ������=[%s]", sBksvr), ""); 
 */
    /*��ǰ����*/
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
    LOG(LM_DEBUG, Fmtmsg("����=[%s]��״̬=[%s]", currStep, sBuffer), "");
    /*��ǰ����<1�򲽵�1ִ��ʧ�ܣ�����������ִ��*/
    if(currStep[0] < '1' || (currStep[0] == '1' && sBuffer[0] != '0'))
    {
        LOG(LM_STD,Fmtmsg("������ɲ���1-�����ļ����,��ǰ����:%c", currStep[0]),"ERROR")
        fpub_SetMsg(lXmlhandle, 98691, "������ɲ���1-�����ļ����");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    
    /*����ƽ������Ϊ������*/
    DCIBegin();
    /*�ָ�ԭ��ˮ������Ϣ*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.chkflag='0' where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s)", sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "0���ָ�ԭ��ˮ������Ϣ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("�ָ�ԭ��ˮ������Ϣ0δ����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    
    /*���±�����ˮ״̬-�ɹ�����ƽ��Ϊ׼*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.stat='0', ser.chkflag='X' where ser.workDate = '%s' and ser.coBankNo='%s' and ser.svrCode='%s'  and transCode in (%s) and exists (select dep.iepSerialNo from PABYBH_DEPCHKINFO dep where dep.checkDate='%s' and dep.coBankNo='%s' and (dep.workSerialNo=ser.workSerialNo or dep.iepSerialNo=ser.iepSerialNo))", sChkDate, sBankNo, sSvrCode, sChkTrans, sChkDate, sBankNo);
    LOG( LM_DEBUG, Fmtmsg( "1������ˮ����״̬���ɹ���¼��״̬����Ϊƽ���ĳɹ�״̬ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���±�����ˮ״̬0ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*���±�����ˮ״̬-ʧ�ܣ���ƽ��Ϊ׼*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.stat='1', ser.chkflag='X' where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s) and ser.stat='0' and ser.chkflag='0'", sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "2������ˮ���в���ƽ��������ϸ�еĳɹ�״̬��¼��״̬����Ϊʧ��״̬ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���±�����ˮ״̬1ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*���±�����ˮ�����˺ţ���ƽ��Ϊ׼*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.acctNo=(select dep.acctNo from PABYBH_DEPCHKINFO dep where dep.checkDate='%s' and dep.coBankNo='%s' and (ser.workSerialNo=dep.workSerialNo or ser.iepSerialNo=dep.iepSerialNo)) where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and transCode in (%s) and stat='0'", sChkDate, sBankNo, sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "3������ˮ���������˺Ų�һ�µļ�¼���� SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���±�����ˮ�����˺�ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*���±�����ˮ���׽���ƽ��Ϊ׼*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.transAmt=(select dep.amt from PABYBH_DEPCHKINFO dep where dep.checkDate='%s' and dep.coBankNo='%s' and (ser.workSerialNo=dep.workSerialNo or ser.iepSerialNo=dep.iepSerialNo)) where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and transCode in (%s) and stat='0'", sChkDate, sBankNo, sChkDate, sBankNo, sSvrCode, sChkTrans);
    LOG( LM_DEBUG, Fmtmsg( "4������ˮ���н��׽�һ�µļ�¼���� SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���±�����ˮ���׽��ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*���Ǳ�����ˮ����ƽ��Ϊ׼*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"insert into PABYBH_SERIAL select '%s', 'B'||dep.iepSerialNo, '', '', '%s', '%s', case when dep.workSerialNo is null or trim(dep.workSerialNo)='' then 'B'||dep.iepSerialNo else dep.workSerialNo end, dep.transDate, 'Y'||dep.iepSerialNo, '', '',   '%s', '', '', '', '', '', '', '944302', dep.transferType, '', '�ʽ�ת', dep.transferType, '%s', '', '', dep.acctNo, '', '', dep.stockCode, dep.capitalAcctNo, dep.amt, 0.00, 0.00, 0.00, '', '', '', '', '%s', dep.transDate, dep.iepSerialNo, '', '', '00', '��¼�ɹ�', '', '', '', '', '', '00000', '��¼�ɹ�', '0', '', '0', 'X', '', '', '', '', '', '', '', 'X', '', '', '', '', '' from PABYBH_DEPCHKINFO dep left join  PABYBH_SERIAL ser on (dep.workSerialNo=ser.workSerialNo or dep.iepSerialNo=ser.iepSerialNo) and ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s) where dep.checkDate='%s' and dep.coBankNo='%s'  and ser.workSerialNo is null and ser.iepSerialNo is null", zwrq, systime, sChkDate, sBankNo, sSvrCode, sChkDate, sChkDate, sBankNo, sSvrCode, sChkTrans, sChkDate, sBankNo);
    LOG( LM_DEBUG, Fmtmsg( "5������ƽ����ϸ��¼��ˮ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("��¼��ˮʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*���¶��˱�־*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_SERIAL  ser set ser.chkflag='X' where ser.workDate='%s' and ser.coBankNo='%s' and ser.svrCode='%s' and ser.transCode in (%s) and ser.chkflag='0'", sChkDate, sBankNo, sSvrCode, sChkTrans );
    LOG( LM_DEBUG, Fmtmsg( "6�����¶��˱�־ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���µ�����ˮ���˱�־ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*���¶���״̬����Ϣ*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set execStep='2', execStat='0' where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", sChkDate, sBankNo, sSvrCode);
    LOG( LM_DEBUG, Fmtmsg( "7�����¶���״̬����Ϣ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("���¶���״̬��ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    if( DCICommit() != 0 )
    {
        LOG( LM_DEBUG, Fmtmsg( " ������Ϣ=[%s]",DCILastError()), "INFO" );
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"�����ύʧ��");
        return COMPRET_FAIL ;
    }    
    /*��ǰ���㸳ֵ-2*/
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "2"); 
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTAT, "0"); 
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
��������: PABYBH_CHKTOTACCT
����: ����Eͬ������
 
�������: 
         1.��Eͨ���;
         2.���ж��;
         3.���������ɹ�����Eͨδ�ɹ���������δ�����ġ�
         ��3������оٳ������������й�Ա�ο������˲�ƽ���������ɸ���������
         �ƶ����д���ʽ��
         
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT PABYBH_CHKTOTACCT( HXMLTREE lXmlhandle )
{
    int iParas=0;
    int iRet=0;
    char sTmp[200];
    char sBuf[1024];
    char sFileName[128];
    char sFilePath[128+1];     /*�ļ�·��*/
    char sChkFile[255+1];      /*�ļ�������·����*/
    int totcnt=0;
    double totamt=0.00;
    int pkgtotcnt=0;
    double pkgtotamt=0.00;
    int loctotcnt=0;
    double loctotamt=0.00;
    
    FILE *fp;
    
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALCOUNT, sTmp);  
    trim(sTmp);
    pkgtotcnt=atoi(sTmp);
    LOG(LM_DEBUG, Fmtmsg("�����е��ܱ���=[%d]", pkgtotcnt), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALAMT, sTmp);  
    trim(sTmp);
    pkgtotamt=atof(sTmp);
    LOG(LM_DEBUG, Fmtmsg("�������ܽ��=[%lf]", pkgtotamt), "");  
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT, sTmp);  
    trim(sTmp);
    loctotcnt=atoi(sTmp);
    LOG(LM_DEBUG, Fmtmsg("�����ܱ���=[%d]", loctotcnt), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT, sTmp);  
    trim(sTmp);
    loctotamt=atof(sTmp);
    LOG(LM_DEBUG, Fmtmsg("�����ܽ��=[%lf]", loctotamt), "");
        
    memset(sFileName, 0x00, sizeof(sFileName));
  memset(sTmp, 0x00, sizeof(sTmp));
  COMP_GETPARSEPARAS(1, sTmp, "���ն����ļ�");
  trim(sTmp);
  pstrcopy(sFileName,sTmp,sizeof(sFileName));  
  
  if(strlen(sFileName) == 0)
  {
      fpub_SetMsg(lXmlhandle, 98690, "ƽ�������ļ�������Ϊ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�ļ�������Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

	memset(sFilePath, 0x00, sizeof(sFilePath));
  memset(sTmp, 0x00, sizeof(sTmp));
  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_PABCHEFP, sTmp);
  trim(sTmp);
  pstrcopy(sFilePath,sTmp,sizeof(sFilePath));
  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  sprintf(sChkFile, "%s/%s", sFilePath, sFileName);
  LOG(LM_STD, Fmtmsg("���ն����ļ�[%s]", sChkFile), fpub_GetCompname(lXmlhandle));
  
  fp = fopen(sChkFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, 98689, "ƽ�������ļ���ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sFileName), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  if(feof(fp))
  {
    LOG(LM_STD,Fmtmsg("�����ļ�Ϊ���ļ�����"),"ERROR")
        fpub_SetMsg(lXmlhandle, 98713, "ƽ�������ļ�Ϊ���ļ�");
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
     /*�ܱ���*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuf,1,sTmp,'|','\\');
     trim(sTmp);
     totcnt=atoi(sTmp);
     LOG(LM_DEBUG, Fmtmsg("�ļ��ܱ���=[%d]", totcnt), "");
    
     
     /*�ܽ��*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuf,2,sTmp,'|','\\');
     trim(sTmp);
     totamt = atof(sTmp)/100;
     LOG(LM_DEBUG, Fmtmsg("�ļ��ܽ��=[%.2lf]", totamt), "");
    
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
    LOG(LM_STD,Fmtmsg("ƽ�������ļ��뱨�ĵĽ�������һ�£���"),"ERROR")
        fpub_SetMsg(lXmlhandle, 98644, "ƽ�������ļ��뱨�ĵĽ�������һ�£���");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
  }    
    
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
��������: PABYBH_CHKRSLINFO
����: ���˽����Ϣ�Ǽǻ����
 
�������: 
         1.��Eͨ���;
         2.���ж��;
         3.���������ɹ�����Eͨδ�ɹ���������δ�����ġ�
         ��3������оٳ������������й�Ա�ο������˲�ƽ���������ɸ���������
         �ƶ����д���ʽ��
         
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
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
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    memset(&SDB_checkCtl, 0x00, sizeof(SDB_checkCtl));
      
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "���˲���");
    trim(sTmp);
    pstrcopy(SDB_checkCtl.EXECSTEP,sTmp,sizeof(SDB_checkCtl.EXECSTEP));  
    LOG(LM_DEBUG,Fmtmsg("���˲���[%s]",sTmp),"INFO");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "��ϸ���˽��");
    trim(sTmp);
    pstrcopy(SDB_checkCtl.CHKDETAILRESULT,sTmp,sizeof(SDB_checkCtl.CHKDETAILRESULT));  
    LOG(LM_DEBUG,Fmtmsg("��ϸ���˽��[%s]",sTmp),"INFO");
/*    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(3, sTmp, "��������");
    trim(sTmp);
    pstrcopy(SDB_checkCtl.CHKDETAILRESULT,sTmp,sizeof(SDB_checkCtl.CHKDETAILRESULT));  
    LOG(LM_DEBUG,Fmtmsg("��������[%s]",sTmp),"INFO");
*/    
    /*��������*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_CHECKDATE, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.CHECKDATE,sTmp,sizeof(SDB_checkCtl.CHECKDATE));  
    LOG(LM_DEBUG,Fmtmsg("��������[%s]",sTmp),"INFO");
    
    /*�����к�*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_COBANKNO, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.COBANKNO,sTmp,sizeof(SDB_checkCtl.COBANKNO));  
    LOG(LM_DEBUG,Fmtmsg("�����к�[%s]",sTmp),"INFO");
    
    /*�������*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_SVRCODE, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.SVRCODE,sTmp,sizeof(SDB_checkCtl.SVRCODE));  
    LOG(LM_DEBUG,Fmtmsg("�������[%s]",sTmp),"INFO");
    
    /*��������*/
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_HARDGETXML(XMLNM_PABYBH_CHECKCTL_MSGTYPE, sTmp);  
    trim(sTmp);
    pstrcopy(SDB_checkCtl.MSGTYPE,sTmp,sizeof(SDB_checkCtl.MSGTYPE));  
    LOG(LM_DEBUG,Fmtmsg("��������[%s]",sTmp),"INFO");
      
    DCIBegin();
      memset(sTmp,0x00,sizeof(sTmp));
      memset(sSql,0x00,sizeof(sSql));
      memset(sErrmsg,0x00,sizeof(sErrmsg));
      sprintf(sSql,"select chkdetailresult from PABYBH_CHECKCTL where checkdate='%s' and cobankno='%s' and svrcode='%s' and msgtype='%s'",SDB_checkCtl.CHECKDATE, SDB_checkCtl.COBANKNO, SDB_checkCtl.SVRCODE, SDB_checkCtl.MSGTYPE);
      LOG( LM_DEBUG, Fmtmsg( "��ѯ���˽���� SQL[%s]", sSql), "INFO" ); 
      iRet = DBSelectToMultiVarChar(sErrmsg,sSql,sTmp);
      trim(sTmp);
      LOG( LM_DEBUG, Fmtmsg( "��ѯ���˽���� IRET[%d]", iRet), "INFO" ); 
      if( iRet < 0 )
      {
          LOG( LM_DEBUG, Fmtmsg( "��ѯ���˽����Ϣʧ�ܣ�SQL[%s]", sSql), "INFO" );
          DCIRollback();
          fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
          fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
          return COMPSTATUS_FAIL;     
      }
      if( iRet == 0 )
      {
	        if(SDB_checkCtl.EXECSTEP[0] == '0' || strlen(SDB_checkCtl.EXECSTEP) == 0)
	        {          
		          /*�ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�ܱ���[%d]",SDB_checkCtl.TOTALCOUNT),"INFO");
		          
		          /*�ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�ܽ��[%.2lf]",SDB_checkCtl.TOTALAMT),"INFO");
		          
		          /*�����ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܱ���[%d]",SDB_checkCtl.BACKTOTALCOUNT),"INFO");
		          
		          /*�����ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܽ��[%.2lf]",SDB_checkCtl.BACKTOTALAMT),"INFO");
		          
		          /*ƽ̨�ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�ܱ���[%d]",SDB_checkCtl.LOCALTOTALCOUNT),"INFO");
		          
		          /*ƽ̨�ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�ܽ��[%.2lf]",SDB_checkCtl.LOCALTOTALAMT),"INFO");
		          
		          /*ƽ̨�����ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�����ܱ���[%.d]",SDB_checkCtl.LOCALBACKTOTALCOUNT),"INFO");
		          
		          /*ƽ̨�����ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�����ܽ��[%.2lf]",SDB_checkCtl.LOCALBACKTOTALAMT),"INFO");
		          
		          /*�����ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܱ���[%d]",SDB_checkCtl.HOSTTOTALCOUNT),"INFO");
		          
		          /*�����ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܽ��[%.2lf]",SDB_checkCtl.HOSTTOTALAMT),"INFO");
		          
		          /*���������ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("���������ܱ���[%d]",SDB_checkCtl.HOSTBACKTOTALCOUNT),"INFO");
		          
		          /*���������ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("���������ܽ��[%.2lf]",SDB_checkCtl.HOSTBACKTOTALAMT),"INFO");
		          
		          /*������*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.NETAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("������[%.2lf]",SDB_checkCtl.NETAMT),"INFO");
		          
		          /*�����  '0���� 1֧��'*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETTYPE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.NETTYPE,sTmp,sizeof(SDB_checkCtl.NETTYPE));
		          LOG(LM_DEBUG,Fmtmsg("�����  '0���� 1֧��'[%s]",sTmp),"INFO");
		          
		          /*ƽ�������ļ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_IEPCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.IEPCHKFILE,sTmp,sizeof(SDB_checkCtl.IEPCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("ƽ�������ļ���[%s]",sTmp),"INFO");
		          
		          /*���������ļ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.HOSTCHKFILE,sTmp,sizeof(SDB_checkCtl.HOSTCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("���������ļ���[%s]",sTmp),"INFO");
		          
		          /*���Ķ����˽��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_CHKPABTOTALRESULT, sTmp);
		          trim(sTmp);
		          if(strlen(sTmp) == 0)
		              SDB_checkCtl.CHKPABTOTALRESULT[0]='0';
		          else pstrcopy(SDB_checkCtl.CHKPABTOTALRESULT,sTmp,sizeof(SDB_checkCtl.CHKPABTOTALRESULT));
		          LOG(LM_DEBUG,Fmtmsg("���Ķ����˽��[%s]",SDB_checkCtl.CHKPABTOTALRESULT),"INFO");
		          
		          
		          /*ִ�в���*/
		          LOG(LM_DEBUG,Fmtmsg("ִ�в���[%s]",SDB_checkCtl.EXECSTEP),"INFO");
		          
		          /*ִ��״̬'0-�ɹ� 1-ʧ��'*/
		          if(strlen(SDB_checkCtl.EXECSTEP) != 0)
		          {
		          		if(SDB_checkCtl.CHKPABTOTALRESULT[0] == '3')
		              		SDB_checkCtl.EXECSTAT[0]='1';
		              else SDB_checkCtl.EXECSTAT[0]='0';
		          }
		          LOG(LM_DEBUG,Fmtmsg("ִ��״̬'0-�ɹ� 1-ʧ��'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
		          
		          /*��ϸ���˽��*/
		          if(strlen(SDB_checkCtl.CHKDETAILRESULT) == 0)
		            SDB_checkCtl.CHKDETAILRESULT[0]='0';
		          LOG(LM_DEBUG,Fmtmsg("��ϸ���˽��[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
		          
		          
		          /*���Ķ����˽��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_CHKHOSTTOTALRESULT, sTmp);
		          trim(sTmp);
		          if(strlen(sTmp) == 0)
		              SDB_checkCtl.CHKHOSTTOTALRESULT[0]='0';
		          else pstrcopy(SDB_checkCtl.CHKHOSTTOTALRESULT,sTmp,sizeof(SDB_checkCtl.CHKHOSTTOTALRESULT));
		          LOG(LM_DEBUG,Fmtmsg("���Ķ����˽��[%s]",SDB_checkCtl.CHKHOSTTOTALRESULT),"INFO");
		          
		          /*�����ֶ�1*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD1, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD1,sTmp,sizeof(SDB_checkCtl.EXTFLD1));
		          LOG(LM_DEBUG,Fmtmsg("�����ֶ�1[%s]",sTmp),"INFO");
		          
		          /*�����ֶ�2*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD2, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD2,sTmp,sizeof(SDB_checkCtl.EXTFLD2));
		          LOG(LM_DEBUG,Fmtmsg("�����ֶ�2[%s]",sTmp),"INFO");
		          
		          /*�����ֶ�3*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD3, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD3,sTmp,sizeof(SDB_checkCtl.EXTFLD3));
		          LOG(LM_DEBUG,Fmtmsg("�����ֶ�3[%s]",sTmp),"INFO");
		          
		          memset(sTmp,0x00,sizeof(sTmp));
		          iRet = DBInsert( "PABYBH_CHECKCTL", SD_PABYBH_CHECKCTL, NUMELE( SD_PABYBH_CHECKCTL ), &SDB_checkCtl,sTmp);
		          if( iRet < 0 )
		          {
		              DCIRollback();
		              LOG( LM_DEBUG, Fmtmsg( "�ǼǶ��˽����ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
		              fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		              return COMPSTATUS_FAIL;   
		          }
	      	}
	        else 
	        {
		          DCIRollback();
		          LOG( LM_DEBUG, Fmtmsg("������Ϣ������"), "INFO" );
		          fpub_SetMsg(lXmlhandle, 98715, "������Ϣ������");
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
				          LOG( LM_DEBUG, Fmtmsg( "�ʽ�����ڴ����л��Ѷ�ƽ����ϸ���˽��[%s]", sTmp), "INFO" );
				          DCIRollback();
				          fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
				          fpub_SetMsg(lXmlhandle, 98741, "�ʽ�����ڴ����л��Ѷ�ƽ");
				          return COMPSTATUS_FAIL;     
		          }
	        	  memset(sTmp,0x00,sizeof(sTmp));
				      sprintf(sTmp,"delete from PABYBH_CHECKCTL where checkdate ='%s' and cobankno='%s' and svrcode='%s' and msgtype='%s' ",SDB_checkCtl.CHECKDATE, SDB_checkCtl.COBANKNO, SDB_checkCtl.SVRCODE, SDB_checkCtl.MSGTYPE);
				      LOG( LM_DEBUG, Fmtmsg( "ɾ�����˼�¼�� SQL[%s]", sTmp), "INFO" );
				      iRet=DCIExecuteDirect(sTmp);
			      	if(iRet<0)
			        {
				          DCIRollback();
				          LOG( LM_DEBUG, Fmtmsg("ɾ�����˽������"), "INFO" );
				          fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				          fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
				          return COMPSTATUS_FAIL;
			        }          
		          /*�ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�ܱ���[%d]",SDB_checkCtl.TOTALCOUNT),"INFO");
		          
		          /*�ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_TOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.TOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�ܽ��[%.2lf]",SDB_checkCtl.TOTALAMT),"INFO");
		          
		          /*�����ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܱ���[%d]",SDB_checkCtl.BACKTOTALCOUNT),"INFO");
		          
		          /*�����ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_BACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.BACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܽ��[%.2lf]",SDB_checkCtl.BACKTOTALAMT),"INFO");
		          
		          /*ƽ̨�ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�ܱ���[%d]",SDB_checkCtl.LOCALTOTALCOUNT),"INFO");
		          
		          /*ƽ̨�ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�ܽ��[%.2lf]",SDB_checkCtl.LOCALTOTALAMT),"INFO");
		          
		          /*ƽ̨�����ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�����ܱ���[%d]",SDB_checkCtl.LOCALBACKTOTALCOUNT),"INFO");
		          
		          /*ƽ̨�����ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_LOCALBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.LOCALBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("ƽ̨�����ܽ��[%.2lf]",SDB_checkCtl.LOCALBACKTOTALAMT),"INFO");
		          
		          /*�����ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܱ���[%d]",SDB_checkCtl.HOSTTOTALCOUNT),"INFO");
		          
		          /*�����ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("�����ܽ��[%.2lf]",SDB_checkCtl.HOSTTOTALAMT),"INFO");
		          
		          /*���������ܱ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALCOUNT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALCOUNT=atoi(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("���������ܱ���[%d]",SDB_checkCtl.HOSTBACKTOTALCOUNT),"INFO");
		          
		          /*���������ܽ��*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTBACKTOTALAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.HOSTBACKTOTALAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("���������ܽ��[%.2lf]",SDB_checkCtl.HOSTBACKTOTALAMT),"INFO");
		          
		          /*������*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETAMT, sTmp);
		          trim(sTmp);
		          SDB_checkCtl.NETAMT=atof(sTmp);
		          LOG(LM_DEBUG,Fmtmsg("������[%.2lf]",SDB_checkCtl.NETAMT),"INFO");
		          
		          /*�����  '0���� 1֧��'*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_NETTYPE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.NETTYPE,sTmp,sizeof(SDB_checkCtl.NETTYPE));
		          LOG(LM_DEBUG,Fmtmsg("�����  '0���� 1֧��'[%s]",sTmp),"INFO");
		          
		          /*ƽ�������ļ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_IEPCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.IEPCHKFILE,sTmp,sizeof(SDB_checkCtl.IEPCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("ƽ�������ļ���[%s]",sTmp),"INFO");
		          
		          /*���������ļ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.HOSTCHKFILE,sTmp,sizeof(SDB_checkCtl.HOSTCHKFILE));
		          LOG(LM_DEBUG,Fmtmsg("���������ļ���[%s]",sTmp),"INFO");
		          
		          /*���Ķ����˽��*/
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
		          LOG(LM_DEBUG,Fmtmsg("���Ķ����˽��[%s]",SDB_checkCtl.CHKPABTOTALRESULT),"INFO");
		          
		          
		          /*ִ�в���*/
		          LOG(LM_DEBUG,Fmtmsg("ִ�в���[%s]",SDB_checkCtl.EXECSTEP),"INFO");
		          
		          /*ִ��״̬'0-�ɹ� 1-ʧ��'*/
		          if(SDB_checkCtl.CHKPABTOTALRESULT[0] == '3')
		              SDB_checkCtl.EXECSTAT[0]='1';
		          else SDB_checkCtl.EXECSTAT[0]='0';
		          LOG(LM_DEBUG,Fmtmsg("ִ��״̬'0-�ɹ� 1-ʧ��'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
		          
		          /*��ϸ���˽��*/
		          LOG(LM_DEBUG,Fmtmsg("��ϸ���˽��[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
		          
		          
		          /*���Ķ����˽��*/
		          SDB_checkCtl.CHKHOSTTOTALRESULT[0]='0';
		          LOG(LM_DEBUG,Fmtmsg("���Ķ����˽��[%s]",SDB_checkCtl.CHKHOSTTOTALRESULT),"INFO");
		          
		          /*�����ֶ�1*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD1, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD1,sTmp,sizeof(SDB_checkCtl.EXTFLD1));
		          LOG(LM_DEBUG,Fmtmsg("�����ֶ�1[%s]",sTmp),"INFO");
		          
		          /*�����ֶ�2*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD2, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD2,sTmp,sizeof(SDB_checkCtl.EXTFLD2));
		          LOG(LM_DEBUG,Fmtmsg("�����ֶ�2[%s]",sTmp),"INFO");
		          
		          /*�����ֶ�3*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_EXTFLD3, sTmp);
		          trim(sTmp);
		          pstrcopy(SDB_checkCtl.EXTFLD3,sTmp,sizeof(SDB_checkCtl.EXTFLD3));
		          LOG(LM_DEBUG,Fmtmsg("�����ֶ�3[%s]",sTmp),"INFO");
		          
		          memset(sTmp,0x00,sizeof(sTmp));
		          iRet = DBInsert( "PABYBH_CHECKCTL", SD_PABYBH_CHECKCTL, NUMELE( SD_PABYBH_CHECKCTL ), &SDB_checkCtl,sTmp);
		          if( iRet < 0 )
		          {
		              DCIRollback();
		              LOG( LM_DEBUG, Fmtmsg( "�ǼǶ��˽����ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
		              fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		              return COMPSTATUS_FAIL;   
		          }
	        }
	        else
	        {
		          memset(sBuf,0x00,sizeof(sBuf));
	          	iLen=0;
	          
		          /*ִ�в���*/
		          if(strlen(SDB_checkCtl.EXECSTEP)==0)
		          {
			          	if(strlen(SDB_checkCtl.CHKDETAILRESULT)==0)
			          	{
			            		DCIRollback();
				              LOG( LM_DEBUG, Fmtmsg("ִ�в���Ͷ��˽������ȫΪ��"), "INFO" );
				              fpub_SetMsg(lXmlhandle, 98716, "ִ�в���Ͷ��˽������ȫΪ��");
				              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
				              return COMPSTATUS_FAIL;
			            }
			            else
			            {
			            		/*��ϸ���˽��*/
			                sprintf(sBuf+iLen,"chkdetailresult='%s'",SDB_checkCtl.CHKDETAILRESULT);
			                iLen=strlen(sBuf);
			                LOG(LM_DEBUG,Fmtmsg("��ϸ���˽��[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
			            }
		            
		          }
		          else 
		          {
		          	  SDB_checkCtl.EXECSTAT[0]='0';
		               
		           
				          /*��ϸ���˽��*/
				          if(SDB_checkCtl.CHKDETAILRESULT[0]!=0)
				          {
					            if(SDB_checkCtl.CHKDETAILRESULT[0] == '3')
					            {
			                  SDB_checkCtl.EXECSTAT[0]='1';
			                  LOG(LM_DEBUG,Fmtmsg("ִ��״̬'0-�ɹ� 1-ʧ��'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
					            }
					            sprintf(sBuf+iLen,"chkdetailresult='%s', ",SDB_checkCtl.CHKDETAILRESULT);
					            iLen=strlen(sBuf);
					            LOG(LM_DEBUG,Fmtmsg("��ϸ���˽��[%s]",SDB_checkCtl.CHKDETAILRESULT),"INFO");
				          }
				          LOG(LM_DEBUG,Fmtmsg("ִ��״̬'0-�ɹ� 1-ʧ��'[%s]",SDB_checkCtl.EXECSTAT),"INFO");
				          sprintf(sBuf+iLen,"execstep='%s', execstat='%s'",SDB_checkCtl.EXECSTEP, SDB_checkCtl.EXECSTAT);
		              iLen=strlen(sBuf);
		              LOG(LM_DEBUG,Fmtmsg("ִ�в���[%s]",SDB_checkCtl.EXECSTEP),"INFO");
				          
		          }
		          
		          /*ƽ�������ļ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_IEPCHKFILE, sTmp);
		          trim(sTmp);
		          if(sTmp[0]!=0)
		          {
			            sprintf(sBuf+iLen,", iepchkfile='%s'",sTmp);
			            iLen=strlen(sBuf);
			            LOG(LM_DEBUG,Fmtmsg("ƽ�������ļ���[%s]",sTmp),"INFO");
		          }
		          /*���������ļ���*/
		          memset(sTmp, 0x00, sizeof(sTmp));
		          COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_HOSTCHKFILE, sTmp);
		          trim(sTmp);
		          if(sTmp[0]!=0)
		          {
			            sprintf(sBuf+iLen,", hostchkfile='%s'",sTmp);
			            iLen=strlen(sBuf);
		          }
		          LOG(LM_DEBUG,Fmtmsg("���������ļ���[%s]",sTmp),"INFO");
		          
		          
		          
		          memset(sSql,0x00,sizeof(sSql));
		          sprintf(sSql,"update PABYBH_CHECKCTL set %s where checkdate ='%s' and cobankno='%s' and svrcode='%s' and msgtype='%s' ", sBuf, SDB_checkCtl.CHECKDATE, SDB_checkCtl.COBANKNO, SDB_checkCtl.SVRCODE, SDB_checkCtl.MSGTYPE);
		          LOG( LM_DEBUG, Fmtmsg( "���¶��˽���� SQL[%s]", sSql), "INFO" ); 
		      	  iRet=DCIExecuteDirect(sSql);
		          if(iRet<=0)
		          {
		              DCIRollback();
		              LOG( LM_DEBUG, Fmtmsg("���¶��˽������"), "INFO" );
		              fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		              fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
		              return COMPSTATUS_FAIL;
		          }
	        }
        
      }
      
      if( DCICommit() != 0 )
      {
          LOG( LM_DEBUG, Fmtmsg( " ������Ϣ=[%s]",DCILastError()), "INFO" );
          DCIRollback();
          fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"�����ύʧ��");
          return COMPRET_FAIL ;
      }
      
      if(SDB_checkCtl.EXECSTEP[0]!=0)
      {
      		/*��ǰ���㸳ֵ*/
    			COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_EXECSTEP, SDB_checkCtl.EXECSTEP); 
    	}
    	
    	if(SDB_checkCtl.EXECSTEP[0]!=0)
      {
      		/*��ϸ���˽����ֵ*/
    			COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, SDB_checkCtl.CHKDETAILRESULT); 
    	}
    	
  
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}

