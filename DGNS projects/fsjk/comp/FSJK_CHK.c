#include "DCI.h"
#include "stdlib.h"
#include "stdio.h"
#include "gaps_head.h"

#include "../incl/FSJK_DZDJ.h"
#include "../incl/FSJK_DZMX.h"
#include "../incl/FSJK_FCMX.h"
#include "../incl/FSJK_RFMX.h"
#include "../incl/FSJK_ERRMSG.h"
#include "../incl/FSJK_CRC.h"



//���CRCУ��������
unsigned short CRC16(unsigned char* puchMsg, unsigned short usDataLen)
{
	unsigned char uchCRCHi = 0xFF;
	unsigned char uchCRCLo = 0xFF;
	unsigned char uIndex;
	while(usDataLen--)
	{
		uIndex = uchCRCHi ^ *puchMsg++;
		uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
		uchCRCLo = auchCRCLo[uIndex];
	}
	return(uchCRCHi << 8|uchCRCLo);
};

void convertStrToUnChar(char* str,unsigned char* UnChar)
{
	int j = 0;
	int i = strlen(str);
	for( j = 0; j < i ;j ++ )
	{
		UnChar[j] = str[j];
	}
	return;
}

/************************************************************************
��̬�����������
��������: FSJK_ZFPT_CHK_FA
����: ֧��ƽ̨�����ļ����
 
�������: ֧��ƽ̨�����ļ����
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT FSJK_ZFPT_CHK_FA(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];       /*��������*/
  char sChkFile[255+1];      /*�ļ�������·����*/
  char sSignDate[8+1];       /*�Ǽ�����*/
  char sSignTime[6+1];       /*�Ǽ�ʱ��*/
  double dPNAMOUNT=0.00;		 /*�շѽ��*/
  double dPNOVERDUEAMT=0.00; /*���ɽ�*/
  double dAMOUNT=0.00;		   /*�����ܽ��*/
  char sOrgPaySerial[19+1];  /*ԭ֧��ƽ̨��ˮ��*/
  char sOrgPayTime[14+1];		 /*ԭ����ʱ��*/
  
  char sPNAMOUNT[20+1];      /*�ɿ�֪ͨ���ܽ��*100���������ɽ�,���ڼ���У����*/
  char sSRC[100+1];					 /*�������ַ���*/
  unsigned char uSRC[100+1]; /*�������ַ��� unsigned char*/
  unsigned short code;			 /*�������У����*/
  char sCode[5+1];					 /*�������У���� char*/
  int iCodeLen;							 /*У����ĳ���*/
	int tmpi;
	int tmplen;

  FSJK_DZMX SDB_fsjk_dzmx;
  FSJK_RFMX SDB_fsjk_rfmx;
  
  
  FILE *fp;
  
  int transcnt=0;               /*���ױ���*/ 
  int refoundcnt=0;             /*�˷ѱ���*/ 
  int detotcnt=0;               /*��ϸ�ܱ���*/

 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "֧��ƽ̨�����ļ�");
  trim(sBuffer);
  pstrcopy(sChkFile,sBuffer,sizeof(sChkFile));
  
  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "��������");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "�Ǽ�����");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  memset(sSignTime, 0x00, sizeof(sSignTime));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "�Ǽ�ʱ��");
  trim(sBuffer);
  pstrcopy(sSignTime,sBuffer,sizeof(sSignTime));
  
  LOG(LM_STD, Fmtmsg("֧��ƽ̨�����ļ�[%s],��������[%s],�Ǽ�����[%s],�Ǽ�ʱ��[%s]", sChkFile, sChkDate, sSignDate, sSignTime), fpub_GetCompname(lXmlhandle)); 

  if(strlen(sChkFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�����ļ�������Ϊ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�ļ�������Ϊ�գ�"), fpub_GetCompname(lXmlhandle))
      return COMPRET_FAIL ;
  }
  
  fp = fopen(sChkFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "֧��ƽ̨�����ļ���ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sChkFile), fpub_GetCompname(lXmlhandle))
      return COMPRET_FAIL ;
  }

  while( !feof(fp) )
  {
  	 memset(sBuffer, 0x00, sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) <= 0 )
         continue; 
     /*���ױ���*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     transcnt=atoi(sTmp);
     LOG(LM_STD,Fmtmsg("���ױ���[%d]",transcnt ),"ERROR")
     
     /*�˷ѱ���*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     refoundcnt = atof(sTmp);
     LOG(LM_STD,Fmtmsg("�˷ѱ���[%d]",refoundcnt ),"ERROR")
     
     break;
  }
  DCIBegin();
  //������ϸ���
  while( !feof(fp) )
  {
		memset(&SDB_fsjk_dzmx, 0x00, sizeof(SDB_fsjk_dzmx));
		memset(sBuffer, 0x00, sizeof(sBuffer));     
		fgets(sBuffer, sizeof(sBuffer), fp);
		if( strlen(trim(sBuffer)) <= 0 )
		   continue;
		
		detotcnt++;
		
		/*֧�� �� �˷� �����ֶ�*/
		/*1-�ɷ�����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,1,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYCHANNEL,sTmp,sizeof(SDB_fsjk_dzmx.PAYCHANNEL)-1);
		
		/*4-֧��ƽ̨��ˮ��*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,4,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYSERIAL,sTmp,sizeof(SDB_fsjk_dzmx.PAYSERIAL)-1);
		
		/*5-��������*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,5,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYCLEARDATE,sTmp,sizeof(SDB_fsjk_dzmx.PAYCLEARDATE)-1);
		
		/*6-����ʱ��->֧��ƽ̨����ʱ��*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,6,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYDATETIME,sTmp,sizeof(SDB_fsjk_dzmx.PAYDATETIME)-1);
		
		/*7-�����ܽ������ɽ�*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,7,sTmp,'|','\\');
   	dAMOUNT = atof(sTmp);
   	SDB_fsjk_dzmx.AMOUNT=dAMOUNT;		
		
		/*9-��������*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,9,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.DISTRICTNO,sTmp,sizeof(SDB_fsjk_dzmx.DISTRICTNO)-1);
		
		/*10-ִ�յ�λ����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,10,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.UNITNO,sTmp,sizeof(SDB_fsjk_dzmx.UNITNO)-1);
		if(strlen(SDB_fsjk_dzmx.UNITNO) <= 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�����ļ�ִ�յ�λ������벻��Ϊ��"), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�����ļ�ִ�յ�λ������벻��Ϊ��");
			break;
		}
		 
		/*11-�ɿ�֪ͨ�����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,11,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_dzmx.PAYNOTENO)-1); 
		if(strlen(SDB_fsjk_dzmx.PAYNOTENO) <= 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�����ļ��ɿ�֪ͨ����벻��Ϊ��"), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�����ļ��ɿ�֪ͨ����벻��Ϊ��");
			break;
		}
		
		/*12-�ɿ���*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,12,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYERNAME,sTmp,sizeof(SDB_fsjk_dzmx.PAYERNAME)-1);
		
		/*13-�շѽ��*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,13,sTmp,'|','\\');
   	dPNAMOUNT = atof(sTmp);
   	SDB_fsjk_dzmx.PNAMOUNT=dPNAMOUNT;
		
		/*14-���ɽ�*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,14,sTmp,'|','\\');
   	dPNOVERDUEAMT = atof(sTmp);
   	SDB_fsjk_dzmx.PNOVERDUEAMT=dPNOVERDUEAMT;
					
		/*15-Ʊ�����ͱ���*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,15,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.RECEIPTTYPENO,sTmp,sizeof(SDB_fsjk_dzmx.RECEIPTTYPENO)-1);
		
		/*16-Ʊ�ݺ���*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,16,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.RECEIPTNO,sTmp,sizeof(SDB_fsjk_dzmx.RECEIPTNO)-1);
		
		/*17-�շ���Ŀ����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,17,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.ITEMNUMBER,sTmp,sizeof(SDB_fsjk_dzmx.ITEMNUMBER)-1);

		/*31-��ע1*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,31,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.REMARK1,sTmp,sizeof(SDB_fsjk_dzmx.REMARK1)-1);
		
		/*32-��ע2*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,32,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.REMARK2,sTmp,sizeof(SDB_fsjk_dzmx.REMARK2)-1);
		
		/*33-��ע3*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,33,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.REMARK3,sTmp,sizeof(SDB_fsjk_dzmx.REMARK3)-1);
		
		/*ȡ���˷ѱ�־*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,2,sTmp,'|','\\');
		trim(sTmp);
		/*���˷��ֱ�����*/
		if(sTmp[0] == '0'){
					
			/*3-������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERNO,sTmp,sizeof(SDB_fsjk_dzmx.ORDERNO)-1); 
			if(strlen(SDB_fsjk_dzmx.ORDERNO) <= 0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�����ļ������Ų���Ϊ��"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�����ļ������Ų���Ϊ��");
			   break;
			}
		
			/*8-����״̬��֧��ƽ̨���˽����������ֵ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,8,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PAYSTATUS,sTmp,sizeof(SDB_fsjk_dzmx.PAYSTATUS)-1);
			memcpy(SDB_fsjk_dzmx.TRANSSTATUS,sTmp,sizeof(SDB_fsjk_dzmx.TRANSSTATUS)-1);			
			
			/*18-��������ʱ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,18,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFTRANSDATETIME,sTmp,sizeof(SDB_fsjk_dzmx.PFTRANSDATETIME)-1);			
			
			/*19-Ӧ������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,19,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.APPNAME,sTmp,sizeof(SDB_fsjk_dzmx.APPNAME)-1);
			
			/*20-Ӧ�ð汾*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,20,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.APPVERSION,sTmp,sizeof(SDB_fsjk_dzmx.APPVERSION)-1);
			
			/*21-��ת��ַ*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,21,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.REDIRECTURL,sTmp,sizeof(SDB_fsjk_dzmx.REDIRECTURL)-1);
			
			/*22-֪ͨ��ַ*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,22,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.NOTIFYURL,sTmp,sizeof(SDB_fsjk_dzmx.NOTIFYURL)-1);
			
			/*23-����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,23,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.AMOUNTTYPE,sTmp,sizeof(SDB_fsjk_dzmx.AMOUNTTYPE)-1);
			
			/*24-��������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,24,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERDATE,sTmp,sizeof(SDB_fsjk_dzmx.ORDERDATE)-1);
			
			/*25-ҵ�����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,25,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.BUSCODE,sTmp,sizeof(SDB_fsjk_dzmx.BUSCODE)-1);
			
			/*26-�Ӷ�������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,26,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.QUANTITY,sTmp,sizeof(SDB_fsjk_dzmx.QUANTITY)-1);
			
			/*27-ͨ�ò���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,27,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.COMM_PARA,sTmp,sizeof(SDB_fsjk_dzmx.COMM_PARA)-1);
			
			/*�ļ����ޣ������ݿ�����Ҫ*/
			/*SIGNDATE-�Ǽ�����*/
			memcpy(SDB_fsjk_dzmx.SIGNDATE,sSignDate,sizeof(SDB_fsjk_dzmx.SIGNDATE)-1);
			
			/*SIGNTIME-�Ǽ�ʱ��*/
			memcpy(SDB_fsjk_dzmx.SIGNTIME,sSignTime,sizeof(SDB_fsjk_dzmx.SIGNTIME)-1);
			
			/*NUMCHKCD-����У����*/
		  memset(sSRC, 0x00, sizeof(sSRC));
		  memset(uSRC, 0x00, sizeof(uSRC));
		  memset(sCode, 0x00, sizeof(sCode));
			strcat(sSRC,SDB_fsjk_dzmx.UNITNO);
			strcat(sSRC,SDB_fsjk_dzmx.PAYNOTENO);
		  convertStrToUnChar(sSRC,uSRC);	
			code = CRC16(uSRC,strlen(uSRC));
		  memcpy(sCode,itoa(code),sizeof(sCode)-1);
		  iCodeLen = strlen(sCode);
		  tmpi = 0;
		  tmplen = iCodeLen;
		  for( tmpi = 4; tmpi >= 0 ; tmpi-- )
		  {
		  	if( tmplen > 0 )
		  	{
		  		sCode[tmpi] = sCode[tmplen-1];
		  	}else{
		  		sCode[tmpi] = '0';
		  	}
		  	tmplen--;
		  }
		  memcpy(SDB_fsjk_dzmx.NUMCHKCD,sCode,sizeof(SDB_fsjk_dzmx.NUMCHKCD)-1);
		  
			
			/*TOTCHKCD-ȫ��У���루��ʱʹ�ò��������ɽ�Ľɿ�֪ͨ���ܽ�*/
		  memset(sSRC, 0x00, sizeof(sSRC));
		  memset(uSRC, 0x00, sizeof(uSRC));
		  memset(sCode, 0x00, sizeof(sCode));
		  memset(sPNAMOUNT, 0x00, sizeof(sPNAMOUNT));
		  memcpy(sPNAMOUNT,itoa( dPNAMOUNT * 100 ),sizeof(sPNAMOUNT)-1);
			strcat(sSRC,SDB_fsjk_dzmx.UNITNO);
			strcat(sSRC,SDB_fsjk_dzmx.PAYNOTENO);
			strcat(sSRC,sPNAMOUNT);
		  convertStrToUnChar(sSRC,uSRC);	
			code = CRC16(uSRC,strlen(uSRC));
		  memcpy(sCode,itoa(code),sizeof(sCode)-1);
		  iCodeLen = strlen(sCode);
		  tmpi = 0;
		  tmplen = iCodeLen;
		  for( tmpi = 4; tmpi >= 0 ; tmpi-- )
		  {
		  	if( tmplen > 0 )
		  	{
		  		sCode[tmpi] = sCode[tmplen-1];
		  	}else{
		  		sCode[tmpi] = '0';
		  	}
		  	tmplen--;
		  }
		  memcpy(SDB_fsjk_dzmx.TOTCHKCD,sCode,sizeof(SDB_fsjk_dzmx.TOTCHKCD)-1);
		  
		  			
			/*SIGNTIME-�Ǽ�ʱ��*/
			memcpy(SDB_fsjk_dzmx.HOSTDVDSTATUS,"2",sizeof(SDB_fsjk_dzmx.HOSTDVDSTATUS)-1);
			
			/*���*/
			LOG(LM_STD,Fmtmsg("detotcnt=[%d],Insert,UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s],NUMCHKCD=[%s],TOTCHKCD=[%s]", detotcnt, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO,SDB_fsjk_dzmx.NUMCHKCD,SDB_fsjk_dzmx.TOTCHKCD),"ERROR")
			memset(sTmp,0x00,sizeof(sTmp));
			iRet = DBInsert( "FSJK_DZMX", SD_FSJK_DZMX, NUMELE( SD_FSJK_DZMX ), &SDB_fsjk_dzmx,sTmp);
			if( iRet < 0 )
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "�ǼǶ�����ϸ��ʧ�� �ɿ�֪ͨ�����=[%d]������=[%d]������Ϣ=[%s]",SDB_fsjk_dzmx.PAYNOTENO,iRet,DCILastError()), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "�ǼǶ�����ϸ��ʧ��");
				break;   
			}
		
		}else if(sTmp[0] == '1'){/*���˷���*/
			
			/*3-������-�˷�ʱ��Ӧ��ƽ̨���˷���ˮ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFSERIAL,sTmp,sizeof(SDB_fsjk_rfmx.RFSERIAL)-1);
			if(strlen(SDB_fsjk_rfmx.RFSERIAL)<=0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�����ļ������Ų���Ϊ��"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�����ļ������Ų���Ϊ��");
			   break;
			}
			
			/*8-����״̬-֧��ƽ̨����״̬*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,8,sTmp,'|','\\');
			trim(sTmp);
			if(sTmp[0] == '0')
			{
				memcpy(SDB_fsjk_dzmx.PAYSTATUS,"2",sizeof(SDB_fsjk_dzmx.PAYSTATUS)-1);
				memcpy(SDB_fsjk_dzmx.TRANSSTATUS,"2",sizeof(SDB_fsjk_dzmx.TRANSSTATUS)-1);
				memcpy(SDB_fsjk_rfmx.RFSTATUS,"1",sizeof(SDB_fsjk_rfmx.RFSTATUS)-1);
			}else if(sTmp[0] == '1')
			{
				memcpy(SDB_fsjk_dzmx.PAYSTATUS,"3",sizeof(SDB_fsjk_dzmx.PAYSTATUS)-1);
				memcpy(SDB_fsjk_dzmx.TRANSSTATUS,"0",sizeof(SDB_fsjk_dzmx.TRANSSTATUS)-1);
				memcpy(SDB_fsjk_rfmx.RFSTATUS,"0",sizeof(SDB_fsjk_rfmx.RFSTATUS)-1);
			}		

			/*29-ԭ֧��������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,29,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERNO,sTmp,sizeof(SDB_fsjk_dzmx.ORDERNO)-1);
			
			/*30-ԭ֧��ƽ̨��ˮ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,30,sTmp,'|','\\');
			trim(sTmp);
			memcpy(sOrgPaySerial,sTmp,sizeof(sOrgPaySerial)-1);
			
			/*31-ԭ����ʱ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,31,sTmp,'|','\\');
			trim(sTmp);
			memcpy(sOrgPayTime,sTmp,sizeof(sOrgPayTime)-1);			
						
			/*����֧��ƽ̨���˽��*/ 
		  memset(sSql,0x00,sizeof(sSql));
		  sprintf(sSql,"update FSJK_DZMX set PAYSTATUS='%s',TRANSSTATUS='%s' where UNITNO='%s' and PAYNOTENO='%s' and ORDERNO='%s' and PAYDATETIME='%s'", SDB_fsjk_dzmx.PAYSTATUS, SDB_fsjk_dzmx.TRANSSTATUS, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO,sOrgPayTime);
		  LOG( LM_DEBUG, Fmtmsg( "detotcnt=[%d],Update,SQL[%s]", detotcnt,sSql), "INFO" ); 
		  iRet = DCIExecuteDirect( sSql );
		  if( iRet <= 0 )
		  {
		  		iResult = -1;
		      LOG(LM_STD,Fmtmsg("����֧��ƽ̨���˽��,sqlerr[%s]", DCILastError() ),"ERROR")
		      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "֧��ƽ̨�����ļ����ʱ���¶�����ϸ��ʧ��");
		      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		      return COMPRET_FAIL;
		  }
			/*�����˷���ϸ��״̬*/ 
		  memset(sSql,0x00,sizeof(sSql));
		  sprintf(sSql,"update FSJK_RFMX set RFFLAG='2',RFSTATUS='%s' where RFFLAG='3' and UNITNO='%s' and PAYNOTENO='%s' and RFSERIAL='%s'", SDB_fsjk_rfmx.RFSTATUS, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_rfmx.RFSERIAL);
		  LOG( LM_DEBUG, Fmtmsg( "detotcnt=[%d],Update,SQL[%s]", detotcnt,sSql), "INFO" ); 
		  iRet = DCIExecuteDirect( sSql );
		  if( iRet <= 0 )
		  {
		  		iResult = -1;
		      LOG(LM_STD,Fmtmsg("����֧��ƽ̨���˽��,sqlerr[%s]", DCILastError() ),"ERROR")
		      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "֧��ƽ̨�����ļ����ʱ�����˷���ϸ��ʧ��");
		      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		      return COMPRET_FAIL;
		  }
		    	
    }else{

  		iResult = -1;
      LOG(LM_STD,Fmtmsg("��֧�ֵ��˷ѱ�־����0��1��"),"ERROR")
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "֧��ƽ̨�����ļ����ʧ��");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;

    }
    
      
	  if( detotcnt == (transcnt+refoundcnt) ){
	   	LOG(LM_STD,Fmtmsg("������ϸ������"),"ERROR")
	   	break;
	  }
  }
  
  /*���¶��˵ǼǱ��е�֧��ƽ̨������Ϣ*/ 
  memset(sSql,0x00,sizeof(sSql));
  sprintf(sSql,"update FSJK_DZDJ set PAYTRANSNUM='%d',PAYREFOUNDNUM='%d' where CHKDATE='%s' and PAYCHKSTATUS='9'", transcnt, refoundcnt, sChkDate);
  LOG( LM_DEBUG, Fmtmsg( "SQL[%s]", sSql), "INFO" );
  iRet = DCIExecuteDirect( sSql );
  if( iRet <= 0 )
  {
  		iResult = -1;
      LOG(LM_STD,Fmtmsg("֧��ƽ̨�����ļ����ʱ���¶��˵ǼǱ�ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "֧��ƽ̨�����ļ����ʱ���¶��˵ǼǱ�ʧ��");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;
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
      LOG( LM_DEBUG, Fmtmsg( "�ύʱ������Ϣ=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "�����ύ����");
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
��������: FSJK_ZFPT_DVD_FA
����: ֧��ƽ̨�ֳ��ļ����
 
�������: ֧��ƽ̨�ֳ��ļ����
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT FSJK_ZFPT_DVD_FA(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];       /*��������*/
  char sDvdFile[255+1];      /*�ļ�������·����*/
  char sSignDate[8+1];       /*�Ǽ�����*/
  char sSignTime[6+1];       /*�Ǽ�ʱ��*/  
  double dITEMPRICE=0.00;		 /*����*/
  double dITEMQUANTITY=0.00; /*����*/
  double dITEMAMOUNT=0.00;	 /*Ӧ�ս��С�ƣ��������ɽ�*/
  double dITEMOVERDUEAMT=0.00;/*���ɽ�*/

  FSJK_FCMX SDB_fsjk_fcmx;

  FILE *fp;

  int detotcnt=0;               /*��ϸ����*/
  int incnt=0;                  /*�������*/
 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sDvdFile, 0x00, sizeof(sDvdFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "֧��ƽ̨�ֳ��ļ�");
  trim(sBuffer);
  pstrcopy(sDvdFile,sBuffer,sizeof(sDvdFile));
  
  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "��������");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "�Ǽ�����");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  memset(sSignTime, 0x00, sizeof(sSignTime));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "�Ǽ�ʱ��");
  trim(sBuffer);
  pstrcopy(sSignTime,sBuffer,sizeof(sSignTime));
  
  LOG(LM_STD, Fmtmsg("֧��ƽ̨�ֳ��ļ�[%s],��������[%s],�Ǽ�����[%s],�Ǽ�ʱ��[%s]", sDvdFile, sChkDate, sSignDate, sSignTime), fpub_GetCompname(lXmlhandle)); 


  if(strlen(sDvdFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�ֳ��ļ�������Ϊ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�ļ�������Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  LOG(LM_STD, Fmtmsg("֧��ƽ̨�ֳ��ļ�[%s]", sDvdFile), fpub_GetCompname(lXmlhandle));
  
  fp = fopen(sDvdFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "֧��ƽ̨�ֳ��ļ���ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sDvdFile), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

  while( !feof(fp) )
  {
  	 memset(sBuffer, 0x00, sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) <= 0 )
         continue; 
     /*��ϸ����*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     detotcnt=atoi(sTmp);
     LOG(LM_STD,Fmtmsg("��ϸ����[%d]",detotcnt ),"ERROR")
     
     break;
  }
  DCIBegin();
  //������ϸ���
  while( !feof(fp) )
  {
		memset(&SDB_fsjk_fcmx, 0x00, sizeof(SDB_fsjk_fcmx));
		memset(sBuffer, 0x00, sizeof(sBuffer));     
		fgets(sBuffer, sizeof(sBuffer), fp);
		if( strlen(trim(sBuffer)) <= 0 )
		   continue;
		
		incnt++;
		
		/*1-ִ�յ�λ����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,1,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.UNITNO,sTmp,sizeof(SDB_fsjk_fcmx.UNITNO)-1);
		if(strlen(SDB_fsjk_fcmx.UNITNO) == 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�ֳ��ļ�ִ�յ�λ������벻��Ϊ��"), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�ֳ��ļ�ִ�յ�λ������벻��Ϊ��");
			break;
		}
		 
		/*2-�ɿ�֪ͨ�����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,2,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_fcmx.PAYNOTENO)-1);
		if(strlen(SDB_fsjk_fcmx.PAYNOTENO) == 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�ֳ��ļ��ɿ�֪ͨ����벻��Ϊ��"), "INFO" );
			fpub_SetMsg(lXmlhandle, 98733, "֧��ƽ̨�ֳ��ļ��ɿ�֪ͨ����벻��Ϊ��");
			break;
		}
	 
		/*3-������*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,3,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ORDERNO,sTmp,sizeof(SDB_fsjk_fcmx.ORDERNO)-1);
		if(strlen(SDB_fsjk_fcmx.ORDERNO) == 0)
		{
			 iResult = -1;
		   LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�ֳ��ļ������Ų���Ϊ��"), "INFO" );
		   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�ֳ��ļ������Ų���Ϊ��");
		   break;
		}
		
		/*4-�շ���Ŀ����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,4,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ITEMNO,sTmp,sizeof(SDB_fsjk_fcmx.ITEMNO)-1);
		if(strlen(SDB_fsjk_fcmx.ORDERNO) == 0)
		{
			 iResult = -1;
		   LOG( LM_DEBUG, Fmtmsg( "֧��ƽ̨�ֳ��ļ��շ���Ŀ���벻��Ϊ��"), "INFO" );
		   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "֧��ƽ̨�ֳ��ļ��շ���Ŀ���벻��Ϊ��");
		   break;
		}
		
		/*5-�շ���Ŀ���*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,5,sTmp,'|','\\');
		trim(sTmp);
		SDB_fsjk_fcmx.ITEMID=atoi(sTmp); 
		
		/*6-�շ���Ŀ����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,6,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ITEMNAME,sTmp,sizeof(SDB_fsjk_fcmx.ITEMNAME)-1);
		
		/*7-������λ*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,7,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ITEMUNIT,sTmp,sizeof(SDB_fsjk_fcmx.ITEMUNIT)-1);
		
		/*8-����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,8,sTmp,'|','\\');
   	dITEMPRICE = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMPRICE=dITEMPRICE;
		
		/*9-����*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,9,sTmp,'|','\\');
   	dITEMQUANTITY = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMQUANTITY=dITEMQUANTITY;
		
		/*10-Ӧ�ս��С��*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,10,sTmp,'|','\\');
   	dITEMAMOUNT = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMAMOUNT=dITEMAMOUNT;
		
		/*11-���ɽ�*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,11,sTmp,'|','\\');
   	dITEMOVERDUEAMT = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMOVERDUEAMT=dITEMOVERDUEAMT;
		
		/*�ļ����ޣ������ݿ�����Ҫ*/
		/*SIGNDATE-�Ǽ�����*/
		memcpy(SDB_fsjk_fcmx.SIGNDATE,sSignDate,sizeof(SDB_fsjk_fcmx.SIGNDATE)-1);
		
		/*SIGNTIME-�Ǽ�ʱ��*/
		memcpy(SDB_fsjk_fcmx.SIGNTIME,sSignTime,sizeof(SDB_fsjk_fcmx.SIGNTIME)-1);
		
		/*TRANSDATE-��������-��������*/
		memcpy(SDB_fsjk_fcmx.TRANSDATE,sChkDate,sizeof(SDB_fsjk_fcmx.TRANSDATE)-1);
		
		/*���*/
		LOG(LM_STD,Fmtmsg("incnt=[%d],Insert,UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s],ITEMNO=[%s],ITEMID=[%d]", incnt, SDB_fsjk_fcmx.UNITNO, SDB_fsjk_fcmx.PAYNOTENO, SDB_fsjk_fcmx.ORDERNO,SDB_fsjk_fcmx.ITEMNO,SDB_fsjk_fcmx.ITEMID),"ERROR")
		memset(sTmp,0x00,sizeof(sTmp));
		iRet = DBInsert( "FSJK_FCMX", SD_FSJK_FCMX, NUMELE( SD_FSJK_FCMX ), &SDB_fsjk_fcmx,sTmp);
		if( iRet < 0 )
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "�ǼǷֳ���ϸ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "�ǼǷֳ���ϸ��ʧ��");
			break;   
		}
     
    if( detotcnt == incnt ){
     	LOG(LM_STD,Fmtmsg("�ֳ���ϸ������"),"ERROR")
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
      LOG( LM_DEBUG, Fmtmsg( "�ύʱ������Ϣ=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "�����ύ����");
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
��������: FSJK_PFCHK_FA
����: �������˽���ļ����
 
�������: �������˽���ļ����
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT FSJK_PFCHK_FA(HXMLTREE lXmlhandle)
{
  int iRet = 0;
  int iResult = 0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];          /*��������*/
  char sChkFile[255+1];         /*�ļ�������·�����������κţ�*/
  int iFileNum;                 /*�ļ�����*/
  int iDZJGLASTSUM;             /*�������˽��������*/
  char sFileName[300+1];        /*�ļ�������·���������κţ�*/

  FSJK_DZMX SDB_fsjk_dzmx;
  
  FILE *fp;

  int cnt =0;                   /*��ϸ�ܱ��������ļ���*/ 
  int succcnt = 0;              /*�ɹ����������ļ���*/ 
  int errcnt = 0;               /*ʧ�ܱ��������ļ���*/ 
  int tbccnt = 0;               /*��ȷ�ϱ��������ļ���*/
  double succamt = 0.00;        /*�ɹ������ļ���*/
  double erramt = 0.00;         /*ʧ�ܽ����ļ���*/
  double tbcamt = 0.00;         /*��ȷ�Ͻ����ļ���*/
  
  int allcnt = 0;               /*��ϸ�ܱ����������ļ���*/ 
  int allsucccnt = 0;           /*�ɹ������������ļ���*/ 
  int allerrcnt = 0;            /*ʧ�ܱ����������ļ���*/ 
  int alltbccnt = 0;            /*��ȷ�ϱ����������ļ���*/

  double allsuccamt = 0.00;     /*�ɹ��������ļ���*/
  double allerramt = 0.00;      /*ʧ�ܽ������ļ���*/
  double alltbcamt = 0.00;      /*��ȷ�Ͻ������ļ���*/

  int nowcnt = 0;               /*��ǰ�ļ���ǰ����*/
  int allnowcnt = 0;            /*�����ļ���ǰ����*/

  int filecnt = 1;              /*��ǰ�ļ����κ�*/

  fpub_InitSoComp( lXmlhandle );


#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "�������˽���ļ��������������κţ�");
  trim(sBuffer);
  pstrcopy(sChkFile,sBuffer,sizeof(sChkFile));

  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "��������");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));

  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "�ļ�����");
  trim(sBuffer);
  iFileNum=atoi(sBuffer);

  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "�������˽��������");
  trim(sBuffer);
  iDZJGLASTSUM=atoi(sBuffer);

  if(strlen(sChkFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�������˽���ļ�������Ϊ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�ļ�������Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
	LOG(LM_STD, Fmtmsg("filecnt=[%d],iFileNum=[%d]",filecnt,iFileNum), fpub_GetCompname(lXmlhandle))
	
	for(filecnt = 1 ; filecnt <= iFileNum ; filecnt++ )
	{
		
		/*��װ�ļ���*/
		memset(sFileName, 0x00, sizeof(sFileName));
		if( filecnt < 10 ){
			strcat(sFileName,sChkFile);
			strcat(sFileName,"0");
			strcat(sFileName,itoa(filecnt+iDZJGLASTSUM));
			strcat(sFileName,".txt");
		} else if( filecnt >= 10 && filecnt < 99 ) {
			strcat(sFileName,sChkFile);
			strcat(sFileName,itoa(filecnt));
		}
		LOG(LM_STD, Fmtmsg("�������˽���ļ�[%s]", sFileName), fpub_GetCompname(lXmlhandle));
		fp = fopen(sFileName, "r");
		if ( fp == NULL )
		{
			fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "�������˽���ļ���ʧ��");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		  LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sFileName), fpub_GetCompname(lXmlhandle)) 
		  return COMPRET_FAIL ;
		}
		
		nowcnt = 0;
		cnt = 0;
    succcnt = 0; 
    errcnt = 0;  
    tbccnt = 0;	
    succamt = 0.00;	
    erramt = 0.00;
    tbcamt = 0.00;
		
		while( !feof(fp) )
		{
			memset(sBuffer, 0x00, sizeof(sBuffer));     
		  fgets(sBuffer, sizeof(sBuffer), fp);
		  if( strlen(trim(sBuffer)) <= 0 )
		      continue; 
			/*��ϸ�ܱ���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			cnt = atoi(sTmp);
			allcnt += cnt;
			LOG(LM_STD,Fmtmsg("��ϸ�ܱ���[%d]",cnt ),"ERROR")
			
			/*�ɹ�����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			succcnt = atoi(sTmp);
			allsucccnt += succcnt;
			LOG(LM_STD,Fmtmsg("�ɹ�����[%d]",succcnt ),"ERROR")
			
			/*�ɹ����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			succamt = atof(sTmp);
			allsuccamt += succamt;
			LOG(LM_STD,Fmtmsg("�ɹ����[%.2f]",succamt ),"ERROR")
			
			/*ʧ�ܱ���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,4,sTmp,'|','\\');
			trim(sTmp);
			errcnt = atoi(sTmp);
			allerrcnt += errcnt;
			LOG(LM_STD,Fmtmsg("ʧ�ܱ���[%d]",errcnt ),"ERROR")
			
			/*ʧ�ܽ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,5,sTmp,'|','\\');
			trim(sTmp);
			erramt = atof(sTmp);
			allerramt += erramt;
			LOG(LM_STD,Fmtmsg("ʧ�ܽ��[%.2f]",erramt ),"ERROR")
			
			/*��ȷ�ϱ���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,6,sTmp,'|','\\');
			trim(sTmp);
			tbccnt = atoi(sTmp);
			alltbccnt += tbccnt;
			LOG(LM_STD,Fmtmsg("��ȷ�ϱ���[%d]",tbccnt ),"ERROR")  
			
			/*��ȷ�Ͻ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,7,sTmp,'|','\\');
			trim(sTmp);
			tbcamt = atof(sTmp);
			alltbcamt += tbcamt;
			LOG(LM_STD,Fmtmsg("��ȷ�Ͻ��[%.2f]",tbcamt ),"ERROR")
			  
			break;
		}
		fgets(sBuffer, sizeof(sBuffer), fp);//��ȡ�հ���
		DCIBegin();
		//������ϸ���
		while( !feof(fp) )
		{
			memset(&SDB_fsjk_dzmx, 0x00, sizeof(SDB_fsjk_dzmx));
			memset(sBuffer, 0x00, sizeof(sBuffer));     
			fgets(sBuffer, sizeof(sBuffer), fp);
			if( strlen(trim(sBuffer)) <= 0 )
			   continue;
			
			nowcnt++;
			allnowcnt++;
			
			/*1-��������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.DISTRICTNO,sTmp,sizeof(SDB_fsjk_dzmx.DISTRICTNO)-1);
			if(strlen(SDB_fsjk_dzmx.DISTRICTNO) == 0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "�������˽���ļ��������벻��Ϊ��"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�������˽���ļ��������벻��Ϊ��");
			   break;
			}
			
			/*2-ִ�յ�λ����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.UNITNO,sTmp,sizeof(SDB_fsjk_dzmx.UNITNO)-1);			 
			if(strlen(SDB_fsjk_dzmx.UNITNO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "�������˽���ļ�ִ�յ�λ������벻��Ϊ��"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�������˽���ļ�ִ�յ�λ������벻��Ϊ��");
				break;
			}
			 
			/*3-�ɿ�֪ͨ�����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_dzmx.PAYNOTENO)-1); 
			if(strlen(SDB_fsjk_dzmx.PAYNOTENO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "�������˽���ļ��ɿ�֪ͨ����벻��Ϊ��"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�������˽���ļ��ɿ�֪ͨ����벻��Ϊ��");
				break;
			}
		 
			/*4-������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,4,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERNO,sTmp,sizeof(SDB_fsjk_dzmx.ORDERNO)-1);
			if(strlen(SDB_fsjk_dzmx.ORDERNO) == 0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "�������˽���ļ������Ų���Ϊ��"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�������˽���ļ������Ų���Ϊ��");
			   break;
			}
			
			/*5-���˽��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,5,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFCHKSTATUS,sTmp,sizeof(SDB_fsjk_dzmx.PFCHKSTATUS)-1);
			if(strlen(SDB_fsjk_dzmx.PFCHKSTATUS) == 00)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "�������˽���ļ����˽������Ϊ��"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�������˽���ļ����˽������Ϊ��");
			   break;
			}

			/*6-ԭ�����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,6,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFCHKERRCODE,sTmp,sizeof(SDB_fsjk_dzmx.PFCHKERRCODE)-1);
			
			/*7-ԭ��˵��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,7,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFCHKERRMSG,sTmp,sizeof(SDB_fsjk_dzmx.PFCHKERRMSG)-1);
						
			LOG(LM_STD,Fmtmsg("allnowcnt=[%d],nowcnt=[%d],DISTRICTNO=[%s],UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s],PFCHKSTATUS=[%s]", allnowcnt, nowcnt, SDB_fsjk_dzmx.DISTRICTNO, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO,SDB_fsjk_dzmx.PFCHKSTATUS),"ERROR")  
		
			/*���²������˽��*/ 
		  memset(sSql,0x00,sizeof(sSql));
		  sprintf(sSql,"update FSJK_DZMX set PFCHKSTATUS='%s',PFCHKERRCODE='%s',PFCHKERRMSG='%s' where UNITNO='%s' and PAYNOTENO='%s' and ORDERNO='%s'", SDB_fsjk_dzmx.PFCHKSTATUS, SDB_fsjk_dzmx.PFCHKERRCODE, SDB_fsjk_dzmx.PFCHKERRMSG, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO);
		  LOG( LM_DEBUG, Fmtmsg( "���²������˽�� SQL[%s]", sSql), "INFO" ); 
		  iRet = DCIExecuteDirect( sSql );
		  if( iRet <= 0 )
		  {
		  		iResult = -1;
		      LOG(LM_STD,Fmtmsg("���²������˽��,sqlerr[%s]", DCILastError() ),"ERROR")
		      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "���¶�����ϸ����");
		  }
		   
		  if( nowcnt == cnt ){
		   	LOG(LM_STD,Fmtmsg("�������˽���ļ�[%s]������",sFileName),"ERROR")
		   	break;
		  }
		}
		
		/*���¶��˵ǼǱ��еĲ���������Ϣ*/ 
		memset(sSql,0x00,sizeof(sSql));
		sprintf(sSql,"update FSJK_DZDJ set PFSUM='%d',PFSUCCSUM='%d',PFERRSUM='%d',PFTBCSUM='%d' where CHKDATE='%s' and PFCHKSTATUS='4'", allcnt, allsucccnt, allerrcnt, alltbccnt,sChkDate);
		LOG( LM_DEBUG, Fmtmsg( "SQL[%s]", sSql), "INFO" );
		iRet = DCIExecuteDirect( sSql );
		if( iRet <= 0 )
		{
				iResult = -1;
				LOG(LM_STD,Fmtmsg("���������ļ����ʱ���¶��˵ǼǱ�ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
				fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "���������ļ����ʱ���¶��˵ǼǱ�ʧ��");
				fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
				return COMPRET_FAIL;
		}
		
		if( nowcnt != cnt ){
			iResult = -1;
			LOG(LM_STD,Fmtmsg("�������˽���ļ�[%s]ʵ����ϸ����[%d]���ļ�ͷ˵������[%d]��ƥ��",sFileName, nowcnt, cnt),"ERROR")
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
			LOG( LM_DEBUG, Fmtmsg( "�ύʱ������Ϣ=[%s]",DCILastError()), "INFO" );
			DCIRollback();
			fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "�����ύ����");
			return COMPRET_FAIL ;
		}
		
		LOG(LM_STD,Fmtmsg("���в������˽���ļ�������"),"ERROR")
	}
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}



/************************************************************************
��̬�����������
��������: FSJK_PFREFOUND_FA
����: �����˷������ļ����
 
�������: �����˷������ļ����
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���
************************************************************************/
IRESULT FSJK_PFREFOUND_FA(HXMLTREE lXmlhandle)
{
  int iRet = 0;
  int iResult = 0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sSignDate[30+1];          /*�˿�����*/
  char sSignTime[30+1];          /*�˿�ʱ��*/
  char sRefoundFile[255+1];      /*�ļ�������·�����������κţ�*/
  int iFileNum;				 			 		 /*�ļ�����*/
  char sFileName[300+1];		     /*�ļ�������·���������κţ�*/

  FSJK_RFMX SDB_fsjk_rfmx;
  
  FILE *fp;

  int cnt = 0;               		/*��ϸ�ܱ��������ļ���*/
  double amt = 0.00;						/*��ϸ�ܽ����ļ���*/ 
  int allcnt;               	  /*��ϸ�ܱ����������ļ���*/ 
  double allamt = 0.00;					/*��ϸ�ܽ������ļ���*/ 
  int nowcnt = 0;								/*��ǰ�ļ���ǰ����*/
  int allnowcnt = 0;						/*�����ļ���ǰ����*/
  int filecnt = 1;						  /*��ǰ�ļ����κ�*/
  double dAMTOVER = 0.00;				/*�˷��ܽ����ʣ������ɽ�*/

  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  
  memset(sRefoundFile, 0x00, sizeof(sRefoundFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "�����˷������ļ��������������κţ�");
  trim(sBuffer);
  pstrcopy(sRefoundFile,sBuffer,sizeof(sRefoundFile));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "�Ǽ�����");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  memset(sSignTime, 0x00, sizeof(sSignTime));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "�Ǽ�ʱ��");
  trim(sBuffer);
  pstrcopy(sSignTime,sBuffer,sizeof(sSignTime));
  
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "�ļ�����");
  trim(sBuffer);
  iFileNum=atoi(sBuffer);
  
  LOG(LM_STD, Fmtmsg("�Ǽ�����[%s],�Ǽ�ʱ��[%s]", sSignDate, sSignTime), fpub_GetCompname(lXmlhandle)); 

  if(strlen(sRefoundFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�����˷������ļ�������Ϊ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�ļ�������Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  if(strlen(sSignDate) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�Ǽ�����");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�Ǽ����ڲ���Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  if(strlen(sSignTime) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�Ǽ�ʱ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("�Ǽ�ʱ�䲻��Ϊ�գ�"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

	for(filecnt = 1 ; filecnt <= iFileNum ; filecnt++ )
	{
		
		/*��װ�ļ���*/
		memset(sFileName, 0x00, sizeof(sFileName));
		if( filecnt < 10 ){
			strcat(sFileName,sRefoundFile);
			strcat(sFileName,"0");
			strcat(sFileName,itoa(filecnt));
			strcat(sFileName,".txt");
		} else if( filecnt >= 10 && filecnt < 99 ) {
			strcat(sFileName,sRefoundFile);
			strcat(sFileName,itoa(filecnt));
		}
		LOG(LM_STD, Fmtmsg("�����˷������ļ�[%s]", sFileName), fpub_GetCompname(lXmlhandle));
		fp = fopen(sFileName, "r");
		if ( fp == NULL )
		{
			fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "�����˷������ļ���ʧ��");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		  LOG(LM_STD, Fmtmsg("���ļ�%sʧ��",sFileName), fpub_GetCompname(lXmlhandle)) 
		  return COMPRET_FAIL ;
		}
		
		nowcnt = 0;
		cnt = 0;
		amt = 0.00;
		
		while( !feof(fp) )
		{
			memset(sBuffer, 0x00, sizeof(sBuffer));     
		  fgets(sBuffer, sizeof(sBuffer), fp);
		  if( strlen(trim(sBuffer)) <= 0 )
		      continue; 
			/*��ϸ�ܱ���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			cnt = atoi(sTmp);
			allcnt += cnt;
			LOG(LM_STD,Fmtmsg("��ϸ�ܱ���[%d]",cnt ),"ERROR")
			
			/*��ϸ�ܽ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			amt = atof(sTmp);
			allamt += amt;
			LOG(LM_STD,Fmtmsg("��ϸ�ܽ��[%.2f]",amt ),"ERROR")
			  
			break;
		}
		fgets(sBuffer, sizeof(sBuffer), fp);//��ȡ�հ���
		DCIBegin();
		//������ϸ���
		while( !feof(fp) )
		{
			memset(&SDB_fsjk_rfmx, 0x00, sizeof(SDB_fsjk_rfmx));
			memset(sBuffer, 0x00, sizeof(sBuffer));     
			fgets(sBuffer, sizeof(sBuffer), fp);
			if( strlen(trim(sBuffer)) <= 0 )
			   continue;
			
			nowcnt++;
			allnowcnt++;
			
			/*�ļ�����*/
			memcpy(SDB_fsjk_rfmx.FILENAME,sFileName,sizeof(SDB_fsjk_rfmx.FILENAME)-1);
			/*�Ǽ�����*/
			memcpy(SDB_fsjk_rfmx.SIGNDATE,sSignDate,sizeof(SDB_fsjk_rfmx.SIGNDATE)-1);
			/*�Ǽ�ʱ��*/
			memcpy(SDB_fsjk_rfmx.SIGNTIME,sSignTime,sizeof(SDB_fsjk_rfmx.SIGNTIME)-1);
			/*�˷ѱ�־-�������˷�*/
			memcpy(SDB_fsjk_rfmx.RFFLAG,"9",sizeof(SDB_fsjk_rfmx.RFFLAG)-1);
			
			/*1-ִ�յ�λ����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.UNITNO,sTmp,sizeof(SDB_fsjk_rfmx.UNITNO)-1);			 
			if(strlen(SDB_fsjk_rfmx.UNITNO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "�����˷������ļ�ִ�յ�λ���벻��Ϊ��"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�����˷������ļ�ִ�յ�λ���벻��Ϊ��");
				break;
			}
			
			/*2-�ɿ�֪ͨ�����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_rfmx.PAYNOTENO)-1); 
			if(strlen(SDB_fsjk_rfmx.PAYNOTENO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "�����˷������ļ��ɿ�֪ͨ����벻��Ϊ��"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "�����˷������ļ��ɿ�֪ͨ����벻��Ϊ��");
				break;
			}
		 
			/*3-������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.ORDERNO,sTmp,sizeof(SDB_fsjk_rfmx.ORDERNO)-1);
			
			/*4-�ɿ���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,4,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.PAYERNAME,sTmp,sizeof(SDB_fsjk_rfmx.PAYERNAME)-1);

			/*5-���˷��ܽ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,5,sTmp,'|','\\');
   		dAMTOVER = atof(sTmp);
   		SDB_fsjk_rfmx.RFAMTOVER=dAMTOVER;
			
			/*6-�ɷ�ʱ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,6,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.TRANSTIME,sTmp,sizeof(SDB_fsjk_rfmx.TRANSTIME)-1);
			
			/*7-Ʊ�����ͱ���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,7,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RECEIPTTYPENO,sTmp,sizeof(SDB_fsjk_rfmx.RECEIPTTYPENO)-1);
			
			/*8-Ʊ�ݺ���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,8,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RECEIPTNO,sTmp,sizeof(SDB_fsjk_rfmx.RECEIPTNO)-1);
			
			/*9-�˷�ԭ��*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,9,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFREASON,sTmp,sizeof(SDB_fsjk_rfmx.RFREASON)-1);
			
			/*10-�˿���*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,10,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFNAME,sTmp,sizeof(SDB_fsjk_rfmx.RFNAME)-1);
			
			/*11-�˿�����ϵ�绰*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,11,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFTEL,sTmp,sizeof(SDB_fsjk_rfmx.RFTEL)-1);
			
			/*12-�˿��˺�*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,12,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFCOUNT,sTmp,sizeof(SDB_fsjk_rfmx.RFCOUNT)-1);
			
			/*13-����������*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,13,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.COUNTBANK,sTmp,sizeof(SDB_fsjk_rfmx.COUNTBANK)-1);
			
			/*14-�ɷ�����*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,14,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.PAYCHANNEL,sTmp,sizeof(SDB_fsjk_rfmx.PAYCHANNEL)-1);
			
			/*15-��ע*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,15,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.REMARK,sTmp,sizeof(SDB_fsjk_rfmx.REMARK)-1);
						
			LOG(LM_STD,Fmtmsg("allnowcnt=[%d],nowcnt=[%d],UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s]", allnowcnt, nowcnt, SDB_fsjk_rfmx.UNITNO, SDB_fsjk_rfmx.PAYNOTENO, SDB_fsjk_rfmx.ORDERNO),"ERROR")  
		
		  /*���*/
			memset(sTmp,0x00,sizeof(sTmp));
			iRet = DBInsert( "FSJK_RFMX", SD_FSJK_RFMX, NUMELE( SD_FSJK_RFMX ), &SDB_fsjk_rfmx,sTmp);
			if( iRet < 0 )
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "�Ǽ��˷���ϸ��ʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "�Ǽ��˷���ϸ��ʧ��");
				break;   
			}
		   
		  if( nowcnt == cnt ){
		   	LOG(LM_STD,Fmtmsg("�����˷������ļ�[%s]������",sFileName),"ERROR")
		   	break;
		  }
		}
		
		if( nowcnt != cnt ){
			iResult = -1;
			LOG(LM_STD,Fmtmsg("�����˷������ļ�[%s]ʵ����ϸ����[%d]���ļ�ͷ˵������[%d]��ƥ��",sFileName, nowcnt, cnt),"ERROR")
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
			LOG( LM_DEBUG, Fmtmsg( "�ύʱ������Ϣ=[%s]",DCILastError()), "INFO" );
			DCIRollback();
			fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "�����ύ����");
			return COMPRET_FAIL ;
		}
		
		LOG(LM_STD,Fmtmsg("���в����˷������ļ�������"),"ERROR")
	}
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}