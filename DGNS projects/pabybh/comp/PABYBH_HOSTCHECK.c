#include "DCI.h"
#include "stdlib.h"
#include "stdio.h"
#include "gaps_head.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/pabybh_xmlmacro.h"
#include "../incl/PABYBH_HOSCHKINFO.h"
#include "../incl/PABYBH_NOTBAL.h"


/************************************************************************
��̬�����������
��������: PAB_ICC_HostChkInfoLd
����: ���������ļ����
 
�������: ���������ļ����
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT PABYBH_HOSTCHKINFOLD(HXMLTREE lXmlhandle)
{
	  int  iParas=0;
	  int  iRet=0;
	  char sBuffer[1024];
	  char sTmp[255];
	  char sFileName[100+1];    /*���������ļ�*/
	  int  iResult=0;
	  int  iCount=0;
	  int  ict=0;
	  char sSql[1024] = {0};
	  char sExtdate[20] = {0};
	  char sExtchannel[20] = {0};
	  char sExttranscode[20] = {0};
	  char sOpenDate[8+1] = {0};
	  char scoBankNo[10+1];  //�����к�
	  char currStep[1+1];    /*��ǰ����*/
	  char sFilePath[256+1]; //�ļ�����·��
	  char sSrvCode[8+1];   //�������
	  char sSerNo[10+1]; //���ҵ����ˮ��
	  char sErrmsg[255+1];
	  char ywbh[20];
  
  
	  PABYBH_HOSCHKINFO SDB_HostChkInfo;
	  FILE *fp;
	 
	  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
/*******�ǵý������˺Ŵ����*******/
	  memset(sTmp,0x00,sizeof(sTmp));
	  memset(sFileName,0x00,sizeof(sFileName));
	  COMP_GETPARSEPARAS(1, sFileName, "���������ļ���")
	  trim(sFileName);
	  LOG( LM_DEBUG, Fmtmsg( "���������ļ�=[%s]",sFileName), "INFO" );
	  
	  memset(sTmp,0x00,sizeof(sTmp));
	  memset(sOpenDate,0x00,sizeof(sOpenDate));
	  COMP_GETPARSEPARAS(2, sTmp, "��������")
	  trim(sTmp);
	  memcpy(sOpenDate,sTmp,sizeof(sOpenDate)-1);
	  LOG( LM_DEBUG, Fmtmsg( "��������=[%s]",sTmp), "INFO" );
    //�����к�
    memset(scoBankNo,0x00,sizeof(scoBankNo));
	  COMP_SOFTGETXML(XMLNM_PABYBH_ORGCFG_COBANKNO, scoBankNo);  
	  trim(scoBankNo);
	  LOG( LM_DEBUG, Fmtmsg( "�����к�=[%s]",scoBankNo), "INFO" );
	  //�ļ�·��
    memset(sFilePath,0x00,sizeof(sFilePath));
	  COMP_SOFTGETXML(XMLNM_PABYBH_PARACTL_HOSTCHEFP, sFilePath);  
	  trim(sFilePath);
	  LOG( LM_DEBUG, Fmtmsg( "�ļ�·��=[%s]",sFilePath), "INFO" );
	  strcat(sFilePath,"/");
	  strcat(sFilePath,sFileName);
	  //�������
	  memset(sSrvCode,0x00,sizeof(sSrvCode));
	  COMP_SOFTGETXML(XMLNM_PABYBH_CHECKCTL_SVRCODE, sSrvCode);  
	  trim(sSrvCode);
	  LOG( LM_DEBUG, Fmtmsg( "�������=[%s]",sSrvCode), "INFO" );
    /*��ǰ����*/
	  memset(currStep, 0x00, sizeof(currStep));
	  memset(sBuffer, 0x00, sizeof(sBuffer));  
	  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTEP, sBuffer);  
	  trim(sBuffer);
	  memcpy(currStep, sBuffer, sizeof(currStep)-1);
  
    memset(sBuffer, 0x00, sizeof(sBuffer));  
    COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTAT, sBuffer);  
    trim(sBuffer);
    /*��ǰ����<2�򲽵�2ִ��ʧ�ܣ�����������ִ��*/
    if(currStep[0] < '2' || (currStep[0] == '2' && sBuffer[0] != '0'))
    {
    	  LOG(LM_STD,Fmtmsg("������ɲ���2-ƽ����ϸ����,��ǰ����:%c", currStep[0]),"ERROR")
        fpub_SetMsg(lXmlhandle, 98691, "������ɲ���2-ƽ����ϸ����");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
  
	  DCIBegin();
	  
	  sprintf(sSql, "delete from PABYBH_HOSCHKINFO where checkDate='%s' and  cobankno='%s'and svrType='%s'",sOpenDate,scoBankNo,sSrvCode );
	  LOG(LM_DEBUG,Fmtmsg("sql���=[%s]",sSql),"DEBUG")
	  iRet = DCIExecuteDirect(sSql);
	  if( iRet < 0 )
	  {
	      DCIRollback(); 
	      LOG( LM_DEBUG, Fmtmsg( "ɾ������������ʱ��ʧ��! ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
	      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"ɾ������������ʱ��ʧ��");
	      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	      return COMPRET_FAIL ;
	  } 
	
	  fp = fopen(sFilePath, "r");
	  if ( fp==NULL )
	  {
	      DCIRollback(); 
	      fpub_SetMsg(lXmlhandle, 98689, "���ļ�ʧ��");
	      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sFileName), fpub_GetCompname(lXmlhandle)) 
	      return COMPRET_FAIL ;      
	  }
	  memset(sBuffer,0x00,sizeof(sBuffer));  
	  while ( fgets(sBuffer, sizeof(sBuffer)-1, fp) != NULL )
	  {
	     
				iCount++;
        LOG( LM_DEBUG, Fmtmsg( "----��ǰ��[%d]��---- ", iCount), "INFO" );          
	      memset(&SDB_HostChkInfo,0x00,sizeof(SDB_HostChkInfo));
	      //������
	      memcpy(SDB_HostChkInfo.COBANKNO ,scoBankNo,  sizeof(SDB_HostChkInfo.COBANKNO)-1);
				//��������
        memcpy(SDB_HostChkInfo.CHECKDATE ,sOpenDate,  sizeof(SDB_HostChkInfo.CHECKDATE)-1);
 				//ƽ̨��ˮ��     
				memset(sTmp,0x00,sizeof(sTmp));
				memset(sSerNo,0x00,sizeof(sSerNo));
        GetListbyDiv(sBuffer,1,sTmp,'|','\\');
        trim(sTmp);
        LOG( LM_DEBUG, Fmtmsg( "ƽ̨��ˮ��=[%s]",sTmp), "INFO" );   
				//������ˮ��Դϵͳ��ʶ��(6λ) +Դϵͳ��������(8λ) +���κ�(2λ) + ҵ����ˮ���(10λ)���м�ҵ��ϵͳ�ı�ʶ��Ϊ��100021��
				//ƽ̨ҵ����ˮ��ȡ ϵͳ ��������+ 10λҵ����ˮ��
				if(!strlen(sTmp))
				{
				     iResult = -1;
				     LOG(LM_STD,Fmtmsg("ƽ̨��ˮ�Ų���Ϊ��" ),"ERROR")
				     fpub_SetMsg(lXmlhandle, 98736,"ƽ̨��ˮ�Ų���Ϊ��");
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
	      //��Ʒ����
	     	memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,4,sTmp,'|','\\');
        trim(sTmp);
        memcpy(ywbh,sTmp,sizeof(ywbh)-1);
        LOG( LM_DEBUG, Fmtmsg( "��Ʒ����=[%s]",sTmp), "INFO" );
        //ҵ������
        memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,5,sTmp,'|','\\');
        trim(sTmp);
        memcpy(ywbh+strlen(ywbh),sTmp,  sizeof(20-strlen(ywbh))-1);
        LOG( LM_DEBUG, Fmtmsg( "ҵ����=[%s]",ywbh), "INFO" );
        if(strcmp(ywbh, "003001510000") != 0)
        {
        		 LOG(LM_DEBUG, Fmtmsg("�Ǵ��ҵ������ϸ"), "INFO" );
        		 continue;
				}
	      
	      //��������
	     	memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,7,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTDATE,sTmp,  sizeof(SDB_HostChkInfo.HOSTDATE)-1);
        LOG( LM_DEBUG, Fmtmsg( "��������=[%s]",sTmp), "INFO" );   
        //������ˮ��
     	  memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,6,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTSERIALNO,sTmp,  sizeof(SDB_HostChkInfo.HOSTSERIALNO)-1);
        LOG( LM_DEBUG, Fmtmsg( "������ˮ��=[%s]",sTmp), "INFO" );   
        //������������
        memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,9,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTBACKDATE,sTmp,  sizeof(SDB_HostChkInfo.HOSTBACKDATE)-1);
        LOG( LM_DEBUG, Fmtmsg( "������������=[%s]",sTmp), "INFO" );   
    
        //����������ˮ��
        memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,8,sTmp,'|','\\');
        trim(sTmp);
        memcpy(SDB_HostChkInfo.HOSTBACKSERNO,sTmp,  sizeof(SDB_HostChkInfo.HOSTBACKSERNO)-1);
        LOG( LM_DEBUG, Fmtmsg( "����������ˮ��=[%s]",sTmp), "INFO" );  
        //���Ľ��״���
        strcpy(SDB_HostChkInfo.HOSTTRANSCODE,"2932");
        //�����˺�
     	  memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,10,sTmp,'|','\\');
        trim(sTmp);
        //memcpy(SDB_HostChkInfo.ACCTNO,sTmp,  sizeof(SDB_HostChkInfo.ACCTNO)-1);
        LOG( LM_DEBUG, Fmtmsg( "�����˺�=[%s]",sTmp), "INFO" );  
				
        //���������˺�ӳ��
         memset(sSql,0x00,sizeof(sSql));
         memset(sErrmsg,0x00,sizeof(sErrmsg));
         sprintf(sSql,"select  oldacct from PABYBH_ACCTO2N where  newacct='%s' and coBankNo='%s'",sTmp, scoBankNo);
         LOG( LM_DEBUG, Fmtmsg( "��ѯ���������˺�ӳ�� SQL[%s]", sSql), "INFO" );
  	     iRet = DBSelectToMultiVarChar( sErrmsg, sSql, SDB_HostChkInfo.ACCTNO ) ;
		     if( iRet < 0 )
		     {
		     			iResult = -1;
		          LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
		          fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		          break;
		     }
	       trim(SDB_HostChkInfo.ACCTNO);
	       //���˺Ŷ�Ӧ�����˺Ų����ڣ����ú��Ĵ������˺�
	       if(iRet == 0)
	       {
	       			memcpy(SDB_HostChkInfo.ACCTNO,sTmp,  sizeof(SDB_HostChkInfo.ACCTNO)-1);
	       }
	       //��Ӧ�����˺Ŵ��ھ������˺Ų������������Ĵ������˺ż�¼�������ֶ�
	       else
	       {
			  			memcpy(SDB_HostChkInfo.EXTFLD1,sTmp,  sizeof(SDB_HostChkInfo.ACCTNO)-1);
	       }
 		    //���׽��
     	  memset(sTmp,0x00,sizeof(sTmp));
        GetListbyDiv(sBuffer,11,sTmp,'|','\\');
        trim(sTmp);
        SDB_HostChkInfo.TRANSAMT=atof(sTmp);
        LOG( LM_DEBUG, Fmtmsg( "���׽��=[%s]",sTmp), "INFO" );  

        //״̬
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
        LOG( LM_DEBUG, Fmtmsg( "״̬=[%s]",sTmp), "INFO" );  

      	//ҵ������ -�������
        memcpy(SDB_HostChkInfo.SVRTYPE,sSrvCode,  sizeof(SDB_HostChkInfo.SVRTYPE)-1);
	      /*���*/
	      memset(sBuffer,0x00,sizeof(sBuffer));
	      iRet = DBInsert( "PABYBH_HOSCHKINFO", SD_PABYBH_HOSCHKINFO, NUMELE(SD_PABYBH_HOSCHKINFO),&SDB_HostChkInfo,sBuffer);
	      if( iRet <= 0 )
	      {
	          iResult = -1;
	          LOG( LM_DEBUG, Fmtmsg( "�Ǽ�����������ϸ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
	          fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, "�Ǽ�����������ϸ��ʧ��" );
	      	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	          break;   
	      }
	      ict++;
      
  	} /* while */

	  fclose(fp);
	  fp = NULL;
	  LOG( LM_DEBUG, Fmtmsg( "-----�Ǽ�����������ϸ��ɹ����ļ��ܱ���[%d]���Ǽ��ܱ���[%d]------ ", iCount, ict ), "INFO" );
	   
	  if( iResult < 0 )
	  {
	      DCIRollback;
	      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
	      return COMPRET_FAIL ;
	  }

		/*���¶���״̬����Ϣ*/
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set execStep='4', execStat='0'  where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", sOpenDate, scoBankNo,sSrvCode);
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
	      fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,"�����ύʧ��");
	      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	      return COMPRET_FAIL ;
	  }

		/*��ǰ���㸳ֵ*/
		COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "4");
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

IRESULT PABYBH_HOSTCHK( HXMLTREE lXmlhandle )
{
    int iParas=0;
    int iRet=0;
    char sTmp[255];
    char sSql[2048];
    char sErrmsg[1024];
    char sChkDate[8+1];  /*��������*/
    char sSrvCode[10];   /*�������*/
    char sBankNo[20];    /*�����б��*/
    char sBksvr[20];    // �ⲿ������
    char sChkTrans[20]; /*������˽��״���  ��ʽ��'944302','xxxxxx'*/
    char currStep[1+1];   /*��ǰ����*/
    char chkres[1+1];     /*��ϸ���˽��*/
        
    
    fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

    COMP_PARACOUNTCHKMIN(4)
    
    memset(sChkDate, 0x00, sizeof(sChkDate));
    memset(sSrvCode, 0x00, sizeof(sSrvCode));
    memset(sBankNo,  0x00, sizeof(sBankNo));

    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "��������");
    trim(sTmp);
    memcpy(sChkDate, sTmp, 8);
    LOG(LM_DEBUG, Fmtmsg("��������=[%s]", sChkDate), "");
    
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "�������");
    trim(sTmp);
    memcpy(sSrvCode, sTmp, sizeof(sSrvCode)-1);
    LOG(LM_DEBUG, Fmtmsg("�������=[%s]", sSrvCode), "");    
    
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

   /*��ǰ����*/
	  memset(currStep, 0x00, sizeof(currStep));
	  memset(sTmp, 0x00, sizeof(sTmp));  
	  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTEP, sTmp);  
	  trim(sTmp);
	  memcpy(currStep, sTmp, sizeof(currStep)-1);
  
    memset(sTmp, 0x00, sizeof(sTmp));  
    COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURRSTAT, sTmp);  
    trim(sTmp);
    /*��ǰ����<4�򲽵�4ִ��ʧ�ܣ�����������ִ��*/
    if(currStep[0] < '4' || (currStep[0] == '4' && sTmp[0] != '0'))
    {
    	  LOG(LM_STD,Fmtmsg("������ɲ���4-�����ļ����,��ǰ����:%c", currStep[0]),"ERROR")
        fpub_SetMsg(lXmlhandle, 98691, "������ɲ���4-�����ļ����");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }     
    
    /* �ⲿ������
    memset(sTmp, 0x00, sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "�ⲿ������");
    trim(sTmp);
    memcpy(sBksvr, sTmp, sizeof(sBksvr)-1);
    LOG(LM_DEBUG, Fmtmsg("�ⲿ������=[%s]", sBksvr), ""); 
 */
    DCIBegin();
    /*������Ķ���*/
    
    
    /*1�����ݲ�ƽ��ϸ��*/
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"insert into PABYBH_NOTBAL_HIS select * from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s'", sChkDate, sBankNo, sSrvCode);
    LOG( LM_DEBUG, Fmtmsg( "1�����ݶ��˲�ƽ��=[%s]", sSql), "INFO" ); 
    iRet=DCIExecuteDirect(sSql);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݶ��˲�ƽ��ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*2��ɾ�����˲�ƽ��ϸ��*/
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"delete from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s'", sChkDate, sBankNo, sSrvCode);
    LOG( LM_DEBUG, Fmtmsg( "2��ɾ�����˲�ƽ��=[%s]", sSql), "INFO" ); 
    iRet=DCIExecuteDirect(sSql);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("ɾ�����˲�ƽ��ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 3����������
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sTmp, 0x00, sizeof( sTmp ) );
    
    sprintf(sSql, "insert into PABYBH_NOTBAL select '%s', '%s', '%s', ser.capitalType, ser.stockCode, ser.capitalAcctNo, ser.workSerialNo, ser.oristat, ser.oriAcctNo, ser.oriTransAmt, ser.transCode, ser.iepSerialNo, ser.stat, ser.acctNo, ser.transAmt, ser.iepTransCode, host.hostDate, host.hostSerialNo, host.stat, host.acctNo, host.transAmt, host.hostTransCode, case when (ser.acctNo=host.acctNo or ser.acctno2=host.acctNo) and ser.transAmt=host.transAmt and ser.stat=host.stat then '1' when host.workSerialNo is null then '2' when ser.workSerialNo is null then '3' when ser.acctNo!=host.acctNo and (ser.acctno2 is null or ser.acctno2 != host.acctno) then '4' when ser.acctNo is null then '4' when host.acctNo is null then '4' when ser.transAmt!=host.transAmt then '5' when ser.stat!=host.stat then '6' end as checkStat, '9', '', '', '', '', '', '', '', '', '', '' from ( select * from PABYBH_SERIAL where workDate='%s' and coBankNo='%s' and svrCode='%s' and transCode in (%s) and stat in ('0','6')) ser full join (select * from PABYBH_HOSCHKINFO where checkDate='%s' and coBankNo='%s' and svrType='%s' and joinChkFlag='1') host on ser.workDate=host.checkDate and ser.workSerialNo=host.workSerialNo and ser.coBankNo=host.coBankNo ", sChkDate, sBankNo, sSrvCode, sChkDate, sBankNo, sSrvCode, sChkTrans, sChkDate, sBankNo, sSrvCode);

    LOG(LM_DEBUG, Fmtmsg("3��������ϸ����[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("������ϸ���˲���ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 4��
       ���µ�����ˮ��¼����������״̬��1-ƽ��4-�˺Ų�����5-����
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL ser set ser.chkFlag=(select no.checkStat from PABYBH_NOTBAL no where no.checkDate='%s' and ser.workSerialNo=no.workSerialNo and no.coBankNo='%s' and no.svrCode='%s' and no.checkStat in('1','4','5','6') ) where ser.workDate='%s' and ser.workSerialNo in (select no.workSerialNo from PABYBH_NOTBAL no where no.checkDate='%s' and no.coBankNo='%s' and no.svrCode='%s' and checkStat in('1','4','5','6'))  ", sChkDate, sBankNo, sSrvCode, sChkDate, sChkDate, sBankNo, sSrvCode );
    LOG(LM_DEBUG, Fmtmsg("4�����µ�����ˮ����״̬1-ƽ,4-�˺Ų���,5-����[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���µ�����ˮ����״̬1-ƽ,4-�˺Ų���,5-�����ļ�¼����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 5��
       ���µ�����ˮ��¼����������״̬��2-ƽ̨��
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL set chkFlag='2' where workDate='%s' and coBankNo='%s' and workSerialNo in (select workSerialNo from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' and  checkStat='2')  ", sChkDate, sBankNo, sChkDate, sBankNo, sSrvCode );    
    LOG(LM_DEBUG, Fmtmsg("5�����µ�����ˮ��¼�Ķ���״̬��2-ƽ̨��[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���µ�����ˮ��¼�Ķ���״̬��2-ƽ̨�����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 6��
       ���µ�����ˮ��¼����������״̬��3-ƽ̨��
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL set chkFlag='3' where workDate='%s' and coBankNo='%s' and hostSerialNo in (select hostSerialNo from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' and  checkStat='3')  ", sChkDate, sBankNo, sChkDate, sBankNo, sSrvCode);
    LOG(LM_DEBUG, Fmtmsg("6�����µ�����ˮ��¼�Ķ���״̬��3-ƽ̨��[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���µ�����ˮ��¼�Ķ���״̬��3-ƽ̨�ٲ���ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 7��
       ���µ�����ˮ��¼����������״̬��1-ƽ-ʧ��
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " update PABYBH_SERIAL set chkFlag='1' where workDate='%s' and coBankNo='%s' and  svrCode='%s' and  chkflag='X'  ", sChkDate, sBankNo, sSrvCode);
    LOG(LM_DEBUG, Fmtmsg("7�����µ�����ˮʧ�ܼ�¼�Ķ���״̬��1-ƽ[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���µ�����ˮʧ�ܼ�¼�Ķ���״̬��1-ƽ����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 8��
       ɾ������ƽ�ļ�¼
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " delete from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' and  checkStat='1' ", sChkDate, sBankNo, sSrvCode);    
    LOG(LM_DEBUG, Fmtmsg("8��ɾ������ƽ�ļ�¼[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("ɾ������ƽ�ļ�¼����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 9��
       ���²�ƽ��¼��ƽ̨����Ϣ
    */
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, " merge into PABYBH_NOTBAL no using (select * from PABYBH_HOSCHKINFO where checkDate='%s' and coBankNo='%s' and svrType='%s' and joinChkFlag='1') host on no.hostSerialNo=host.hostSerialNo and no.checkstat='3' when matched then update set no.workSerialNo=host.workSerialNo, (no.transfertype, no.stockcode, no.capitalacctno, no.bankstat, no.bankacctno, no.bankamt, no.banktranscode) = (select capitaltype, stockcode, capitalacctno, oristat, oriacctno, oritransamt, transcode from PABYBH_SERIAL where workdate='%s' and workserialno=host.workSerialNo ) ", sChkDate, sBankNo, sSrvCode, sChkDate);    
    LOG(LM_DEBUG, Fmtmsg("9�����²�ƽ��¼��ƽ̨����Ϣ[%s]", sSql),"INFO");
    iRet = DCIExecuteDirect( sSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���²�ƽ��¼��ƽ̨����Ϣ����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 10��ͳ���Ƿ��в�ƽ��ϸ����������״̬����ģ���������ϸ״̬ */
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sTmp, 0x00, sizeof( sTmp ) );
    memset( chkres, 0x00, sizeof( chkres ) );
    memset( sErrmsg, 0x00, sizeof( sErrmsg ) );
    sprintf(sSql, "select count( checkStat) from PABYBH_NOTBAL where checkDate='%s' and coBankNo='%s' and svrCode='%s' ", sChkDate, sBankNo, sSrvCode );    
    LOG(LM_DEBUG, Fmtmsg("10��ͳ��������ƽ��ϸ����[%s]", sSql),"INFO");
    iRet = DBSelectToMultiVarChar( sErrmsg, sSql, sTmp ) ;
    if( iRet < 0 )
    {
    		DCIRollback();
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if ( atoi(sTmp)>0 ) /*������ϸ����״̬��2-��ƽ*/
    {
    		chkres[0]='2';
        COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, "2");
    }
    else /*������ϸ����״̬��1-ƽ*/
    {
    		chkres[0]='1';
        COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, "1");
    }
    
    /*11�����¶���״̬����Ϣ*/ 
    memset(sSql,0x00,sizeof(sSql));
    sprintf(sSql,"update PABYBH_CHECKCTL set execStep='5', execStat='0', chkdetailresult='%s' where checkDate='%s' and coBankNo='%s' and svrCode='%s' and msgType='0'", chkres, sChkDate, sBankNo, sSrvCode);
    LOG( LM_DEBUG, Fmtmsg( "11�����¶���״̬����Ϣ SQL[%s]", sSql), "INFO" ); 
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("���¶���״̬��ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
		
		/* �ύ���� */
    if ( DCICommit() != MID_SYS_SUCC )
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "�ύ����ʧ��");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*��ǰ���㸳ֵ*/
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTEP, "5");
    COMP_SOFTSETXML(XMLNM_PABYBH_REQ_CURRSTAT, "0"); 
    /*��ϸ���˽����ֵ*/
    COMP_SOFTSETXML(XMLNM_PABYBH_CHECKCTL_CHKDETAILRESULT, chkres); 
    
#ifdef DEBUG
    LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
    fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
    
    return COMPRET_SUCC;
}

