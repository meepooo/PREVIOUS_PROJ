/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V3.0.00
  ����ϵͳ:AIX5.3
  �ļ�����:SYW_TIPS_CHKACCT.ec
  �ļ�����:TIPS���ʽ��������
  �� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
  �� �� Ա:Tuql
  ��������:
  ��    ��:
  �޸�����:  
 *********************************************************************/
/*
   ����˵��:

   ����˵��
   �����������                 �������                      ��������  ����Ա �޸����� �޸���

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

/* add by tuql 20091108 ���ڸ��¶��˲�ƽ��ϸ*/
typedef struct TDB_DZBPMX
{
	char yzwrq[8+1];/*ԭ��������*/
	int  yqzlsh;/* ԭǰ����ˮ�� */
	char clzt[1+1];/* ����״̬ */
	char clxx[50+1];/* ������Ϣ */
	char yclzt[1+1];/* ԭ����״̬ */
	char dzlx[1+1];/* �������� */
}SDB_DZBPMX; 

/* add by tuql 20091108 ���ڸ��¶��˲�ƽ��ϸ*/
typedef struct TDB_MZ
{
	HXMLTREE lXmlhandle; /* XML����� */
	char yzwrq[8+1];/*ԭ��������*/
	int  yqzlsh;/* ԭǰ����ˮ�� */
	char ymsgno[4+1];/* ԭ���״��� */
	double mzje;/* Ĩ�˽�� */
	char pljylsh[8+1];/* ����������ˮ�� */
	char plpch[8+1];/* �������κ� */
	char dzbz[1+1];/* ���˱�־ */
}SDB_MZ;

/* ����TIPS��˰����ʱ��TIPS��ǰ���еļ�¼ */
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
  ��¼������־�ĺ���2

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
  ��̬�����������
  �����������: SYW_TIPS_RegDZPKG
  �������: �Ǽ�˰��Ʊ���˰�
  �������: 
  �Ǽ�˰��Ʊ���˰�
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

  ��Ҫ�������:
  ����              ����
  ˰�ն�������ͷ	tips_ssdzplt
  ˰�ն�����ϸ��Ϣ tips_ssdzmxxx

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��02��25��
  �޸�����: 20141105 DCI���칤��
  �޸�����: 20141220DCI���죬�Ѳ�
  ����ʹ��ʾ��: 
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

	LOG(LM_STD,Fmtmsg("�Ǽ�˰��Ʊ���˰���ʼ����... "), fpub_GetCompname(lXmlhandle))

		/*************************��ȡ��������ͷ����***************************/    
		memset(&stDzplt, 0x00, sizeof(stDzplt)); 
	/*��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/zwrq",sBuf)
		pstrcopy(stDzplt.zwrq,sBuf,sizeof(stDzplt.zwrq));
	/*�ۺ�ǰ����ˮ��*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/pub/zhqzlsh",sBuf)
		stDzplt.zhqzlsh=atoi(sBuf);
	/*��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/WorkDate",sBuf)
		pstrcopy(stDzplt.workdate,sBuf,sizeof(stDzplt.workdate));
	/*�������к�*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/PayBkCode",sBuf)
		pstrcopy(stDzplt.paybkcode,sBuf,sizeof(stDzplt.paybkcode));
	/*�տ����к�*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/PayeeBankNo",sBuf)
		pstrcopy(stDzplt.payeebankno,sBuf,sizeof(stDzplt.payeebankno));
	/*��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChkDate",sBuf)
		pstrcopy(stDzplt.chkdate,sBuf,sizeof(stDzplt.chkdate));
	/*��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChkAcctOrd",sBuf)
		pstrcopy(stDzplt.chkacctord,sBuf,sizeof(stDzplt.chkacctord));
	/*��һ��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/PriorChkAcctOrd",sBuf)
		pstrcopy(stDzplt.priorchkacctord,sBuf,sizeof(stDzplt.priorchkacctord));
	/*��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChkAcctType",sBuf)
		pstrcopy(stDzplt.chkaccttype,sBuf,sizeof(stDzplt.chkaccttype));
	/*�ܱ���*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/AllNum",sBuf)
		stDzplt.allnum=atoi(sBuf);
	/*�ܽ��*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/AllAmt",sBuf)
		stDzplt.allamt=atof(sBuf);
	/*�Ӱ�����*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tips/ChildPackNum",sBuf)
		stDzplt.childpacknum=atoi(sBuf);
	/*�������*/
	memset(sBuf, 0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/tips/CurPackNo",sBuf)
		stDzplt.curpackno=atoi(sBuf);
	/*��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("CurPackNum",sBuf)
		stDzplt.curpacknum=atoi(sBuf);
	/*�������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("CurPackAmt",sBuf)
		stDzplt.curpackamt=atof(sBuf);    

	LOG(LM_DEBUG,Fmtmsg("��������[%s],��������[%s],�������[%d]",
				stDzplt.chkdate, stDzplt.chkacctord, stDzplt.curpackno),"DEBUG");

	/************************������ݿ�����Ƿ���ڸö��ʰ���¼********************/
	iCount = 0 ;

	//add by chenxm 20141104 DCI���칤��
	memset(sSql1, 0x00, sizeof(sSql1));
	memset(sTemp, 0x00, sizeof(sTemp));
	
	sprintf(sSql1, "SELECT count(*) FROM tips_ssdzplt WHERE chkdate='%s' and chkacctord ='%s'\
		and curpackno ='%d' and paybkcode ='%s' and payeebankno='%s'",stDzplt.chkdate,\
		stDzplt.chkacctord, stDzplt.curpackno, stDzplt.paybkcode, stDzplt.payeebankno);
	
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
	iSqlRet = DBSelectToVarChar(sErrmsg, sTemp, sSql1);
	if( iSqlRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24356, Fmtmsg("��ѯ˰�ն�������ͷ��ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ˰�ն�������ͷ��ʧ��"),fpub_GetCompname(lXmlhandle)); 
	}
	iCount = atol(sTemp);
	// add end 

	// noted by chenxm  20141104 DCI���칤��
	//EXEC SQL SELECT COUNT(*) INTO :iCount 
	//    FROM tips_ssdzplt 
	//    WHERE chkdate=:stDzplt.chkdate           /*��������*/
	//      AND chkacctord=:stDzplt.chkacctord     /*��������*/
	//      AND curpackno=:stDzplt.curpackno       /*�������*/
	//      AND paybkcode=:stDzplt.paybkcode       /*�������к�*/
	//      AND payeebankno=:stDzplt.payeebankno ; /*�տ����к�*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  /if ( SQLERR )
	  {
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24356, Fmtmsg("��ѯ˰�ն�������ͷ��ʧ��"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ˰�ն�������ͷ��ʧ��"), 
	  fpub_GetCompname(lXmlhandle));        
	  }
	//noded end 

	 */
	if ( iCount != 0 )   /*�м�¼�Ѿ����ڲ����ٲ����ݿ��*/
	{
		iflag = 1;  /*1--�м�¼�����������¼�����������*/
		LOG(LM_STD,Fmtmsg("˰��Ʊ��ϸ�������ݰ��Ѵ���,����"), 
				fpub_GetCompname(lXmlhandle));
		/* mod by tuql 20100129 �����ȵ��ضԱ���,��commit delete�����
		   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		   fpub_SetMsg(lXmlhandle, 24357, Fmtmsg("˰��Ʊ��ϸ�������ݰ��Ѵ���,����"));
		   LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ˰�ն�������ͷ��ʧ��"), 
		   fpub_GetCompname(lXmlhandle));
		 */
	}else
		iflag = 0 ;

	if ( iflag == 0 )  /*0--��ʾ���ݿ����δ�иð���¼�������*/
	{

		/*EXEC SQL BEGIN WORK;  ����ʼ*/
		/*��ֵ���ڵ�*/
		memset(sroot1, 0x00, sizeof(sroot1));
		strcpy(sroot1,"/tips/MSG/BankCompare3111");

		// add by chenxm 20141104 DCI���칤�� 
		iSqlRet = DCIBegin();
		if( iSqlRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
	  
	  //add by lrj 20180912 �ط���������ԭ���������ݵ������ʧ��
	  memset(sSql1, 0x00, sizeof(sSql1));
	
	  sprintf(sSql1, "DELETE FROM tips_ssdzmx WHERE chkdate='%s' and chkacctord ='%s'\
		and curpackno ='%d' and paybkcode ='%s' and payeebankno='%s'",stDzplt.chkdate,\
		stDzplt.chkacctord, stDzplt.curpackno, stDzplt.paybkcode, stDzplt.payeebankno);
	  LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
	  iSqlRet = DCIExecuteDirect(sSql1);
	  if( iSqlRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
    /*end add by lrj 20180912 �ط���������ԭ���������ݵ������ʧ��*/
	  
		/*�ǼǶ�����ϸ������*/
		for (i=1;i<=stDzplt.curpacknum;i++)
		{
			memset(&stDzmx, 0x00, sizeof(stDzmx));
			/*************************��ȡ������ϸ����***************************/
			/*��������*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/zwrq",sBuf)
				pstrcopy(stDzmx.zwrq,sBuf,sizeof(stDzmx.zwrq));
			/*�ۺ�ǰ����ˮ��*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/zhqzlsh",sBuf)
				stDzmx.zhqzlsh=atoi(sBuf);
			/*��������*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/WorkDate",sBuf)
				pstrcopy(stDzmx.workdate,sBuf,sizeof(stDzmx.workdate));
			/*��������*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/ChkDate",sBuf)
				pstrcopy(stDzmx.chkdate,sBuf,sizeof(stDzmx.chkdate));
			/*��������*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/ChkAcctOrd",sBuf)
				pstrcopy(stDzmx.chkacctord,sBuf,sizeof(stDzmx.chkacctord));
			/*�������*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/CurPackNo",sBuf) //modified by lrj 20180912
				stDzmx.curpackno=atoi(sBuf);            
			/*��������к�*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/PayOpBkCode",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.payopbkcode,sBuf,sizeof(stDzmx.payopbkcode));    
			/*�������к�*/
			memset(sBuf, 0x00,sizeof(sBuf));
			COMP_SOFTGETXML("/tips/PayBkCode",sBuf)
				pstrcopy(stDzmx.paybkcode,sBuf,sizeof(stDzmx.paybkcode));
			/*�տ����к�*/
			COMP_SOFTGETXML("/tips/PayeeBankNo",sBuf)
				pstrcopy(stDzmx.payeebankno,sBuf,sizeof(stDzmx.payeebankno));
			/*�����˻�*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/PayAcct",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.payacct,sBuf,sizeof(stDzmx.payacct));
			/*��λ����*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/HandOrgName",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.handorgname,sBuf,sizeof(stDzmx.handorgname));          
			/*ԭ���ջ��ش���*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriTaxOrgCode",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.oritaxorgcode,sBuf,sizeof(stDzmx.oritaxorgcode));            
			if (stDzmx.oritaxorgcode[0] == '\0')
			{
				/* EXEC SQL ROLLBACK WORK;*/
				fpub_SetMsg(lXmlhandle, 24358, Fmtmsg("��[%d]������,��[%d]���������ݲ�����", stDzplt.curpacknum, i));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				LOG(LM_STD, Fmtmsg("ԭ���ջ���[%s],ԭί������[%s],ԭ����ˮ��[%s],ԭ������ˮ��[%s]", 
							stDzmx.oritaxorgcode, stDzmx.orientrustdate, stDzmx.oripackno, stDzmx.oritrano), 
						fpub_GetCompname(lXmlhandle))
					LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��[%d]������,��[%d]���������ݲ�����", stDzplt.curpacknum, i), 
							fpub_GetCompname(lXmlhandle))                
			}
			/*ԭί������*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriEntrustDate",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.orientrustdate,sBuf,sizeof(stDzmx.orientrustdate));
			/*ԭ����ˮ��*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriPackNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.oripackno,sBuf,sizeof(stDzmx.oripackno));
			/*ԭ������ˮ��*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/OriTraNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.oritrano,sBuf,sizeof(stDzmx.oritrano));
			/*���׽��*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/TraAmt",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				stDzmx.traamt=atof(sBuf);
			/*˰Ʊ����*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/TaxVouNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.taxvouno,sBuf,sizeof(stDzmx.taxvouno));
			/*��˰������*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/TaxPayName",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.taxpayname,sBuf,sizeof(stDzmx.taxpayname));
			/*Э�����*/
			memset(sBuf, 0x00,sizeof(sBuf));
			memset(sXml, 0x00, sizeof(sXml));
			snprintf(sXml,sizeof(sXml),"%s|%d/ProtocolNo",sroot1,i);
			COMP_SOFTGETXML(sXml,sBuf)
				pstrcopy(stDzmx.protocolno,sBuf,sizeof(stDzmx.protocolno));          

			/*�ǼǶ�����ϸ��Ϣ��*/
			// add by chenxm 20141104 DCI���칤�� 
			//snprintf(sTable, "%s", "tips_ssdzmx");
			
			iSqlRet = DBInsert("tips_ssdzmx", SD_TIPS_SSDZMX, NUMELE(SD_TIPS_SSDZMX), &stDzmx, sErrmsg);
			if( iSqlRet < 0 )
			{
				/*DCIRollback(); */
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				fpub_SetMsg(lXmlhandle, 24358, "�ǼǶ�����ϸ��Ϣʧ��");
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				LOG(LM_STD, Fmtmsg("ԭ���ջ���[%s],ԭί������[%s],ԭ����ˮ��[%s],ԭ������ˮ��[%s]", 
							stDzmx.oritaxorgcode, stDzmx.orientrustdate, stDzmx.oripackno, stDzmx.oritrano), 
						fpub_GetCompname(lXmlhandle))
				
				LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ǼǶ�����ϸ��Ϣʧ��"), fpub_GetCompname(lXmlhandle))	        
			}

			/*
			   EXEC SQL INSERT INTO tips_ssdzmx  VALUES(:stDzmx);
			   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
			   if ( SQLERR )
			   {*/
			/*  EXEC SQL ROLLBACK WORK;*/
			/*fpub_SetMsg(lXmlhandle, 24358, "�ǼǶ�����ϸ��Ϣʧ��");
			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			  LOG(LM_STD, Fmtmsg("ԭ���ջ���[%s],ԭί������[%s],ԭ����ˮ��[%s],ԭ������ˮ��[%s]", 
			  stDzmx.oritaxorgcode, stDzmx.orientrustdate, stDzmx.oripackno, stDzmx.oritrano), 
			  fpub_GetCompname(lXmlhandle))
			  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ǼǶ�����ϸ��Ϣʧ��"), 
			  fpub_GetCompname(lXmlhandle))
			  }*/
		}

		/*�ǼǶ�������ͷ��*/

		iSqlRet = DBInsert("tips_ssdzplt", SD_TIPS_SSDZPLT, NUMELE(SD_TIPS_SSDZPLT), &stDzplt, sErrmsg);
		if( iSqlRet < 0 )
		{
			/*DCIRollback(); */
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			fpub_SetMsg(lXmlhandle, 24359, "�ǼǶ�������ͷ��Ϣʧ��");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			
			LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ǼǶ�������ͷ��Ϣʧ��"),fpub_GetCompname(lXmlhandle))
		}

		/*
		   EXEC SQL INSERT INTO tips_ssdzplt VALUES(:stDzplt);
		   SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
		   if ( SQLERR )
		   {*/
		/*  EXEC SQL ROLLBACK WORK; */  /*
										   fpub_SetMsg(lXmlhandle, 24359, "�ǼǶ�������ͷ��Ϣʧ��");
										   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
										   LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ǼǶ�������ͷ��Ϣʧ��"), 
										   fpub_GetCompname(lXmlhandle))
										   }

		/*�����ύ����
		EXEC SQL COMMIT WORK;
		/*SQLERRLOG(LM_STD,Fmtmsg("���ݿ��ύʧ��sqlcode=[%d]",sqlca.sqlcode),"ERROR");
		if ( SQLERR )  
		{
		EXEC SQL ROLLBACK WORK;
		fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("���ݿ����ʧ��"));
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return COMPRET_FAIL;    	
		} */       
		iSqlRet=DCICommit();
		/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
		if ( iSqlRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */
	}
	fpub_SetMsg(lXmlhandle, 0, "�Ǽ�˰��Ʊ���˰��ɹ�");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	LOG(LM_STD,Fmtmsg("�Ǽ�˰��Ʊ���˰��ɹ�"), fpub_GetCompname(lXmlhandle));
	return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_ChkSSDZBZT
  �������: �ж�˰�ն��ʰ�״̬
  �������: 
  �ж�˰�ն��ʰ�״̬
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

  ��Ҫ�������:
  ����              ����
  ˰�ն�������ͷ	tips_ssdzplt
  ˰�ն�����ϸ��Ϣ tips_ssdzmxxx

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��02��25��
  �޸�����: 20141105 DCI���칤��
  �޸�����: 20141220DCI���죬�Ѳ�
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_ChkSSDZBZT(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;  //noted by chenxm 20141104
	int iCountPkg;/*������*/
	int iCountMxbs;/*����ϸ���յ����ܱ���*/
	double dTraamt;/*��ϸ�����ܽ��*/
	char cCountMxbs[16+1];
	char cTraamt[32+1];
	char sChkDate[8+1];/* �������� */
	char sChkAcctOrd[4+1];/* �������κ� */
	char sPayBkCode[12+1];/* �������к� */
	char sPayeeBankNo[12+1];/* �տ����к� */
	//EXEC SQL END   DECLARE SECTION;  //noted by chenxm 20141104

	char sSql1[1024];
	char sErrmsg[256];
	char sBuf[256];
	char sTemp[128];
	
	int iRet = -1;  // added by chenxm 20141104 DCI���칤��
	int i;
	int iret=0;
	int iTmp;
	int iFlag=0;
	int iZbs;/* �ܱ��� */
	int iChildPackNum;/*�Ӱ���*/
	double dZje;/*�ܽ��*/
	char sZje[32];/* add by tuql 20090910 */
	char sTraamt[32];/* add by tuql 20090910 */

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("�ж�˰�ն��ʰ�״̬��ʼ����... "), fpub_GetCompname(lXmlhandle))

		COMP_PARACOUNTCHK(7)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"��������");
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"�������κ�");
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(3,sBuf,"�Ӱ���");
	iChildPackNum = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(4,sBuf,"���ζ����ܱ���");
	iZbs = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(5,sBuf,"���ζ����ܽ��");
	dZje = atof(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(6,sBuf,"�������к�");
	pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayeeBankNo, 0x00,sizeof(sPayeeBankNo));
	COMP_GETPARSEPARAS(7,sBuf,"�տ����к�");
	pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo));

	LOG(LM_STD,Fmtmsg("��������[%s],�������κ�[%s],�Ӱ���[%d]",sChkDate, sChkAcctOrd, iChildPackNum),
			fpub_GetCompname(lXmlhandle))
		LOG(LM_STD,Fmtmsg("�������к�[%s],�տ����к�[%s]", sPayBkCode, sPayeeBankNo),
				fpub_GetCompname(lXmlhandle))

		/*��ö������ڡ��������κ��������Ѿ��յ���������*/
		iCountPkg = 0 ;
	//added by chenxm 20141104 DCI���칤�� 
	memset(sSql1, 0x00, sizeof(sSql1));
	memset(sTemp, 0x00, sizeof(sTemp));
	sprintf(sSql1, "select count(*) from tips_ssdzplt where chkdate = '%s' and chkacctord ='%s'\
			and paybkcode ='%s' and payeebankno='%s'", sChkDate,sChkAcctOrd,sPayBkCode,sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iRet = DBSelectToVarChar(sErrmsg, sTemp, sSql1);
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
		
		fpub_SetMsg(lXmlhandle, 24356, "��ѯ˰�ն�������ͷ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ѯ�������ձ������Ѿ��յ���������ʧ��"), fpub_GetCompname(lXmlhandle))
	}		
	iCountPkg = atol(sTemp);
	/*
	   EXEC SQL SELECT COUNT(*) INTO :iCountPkg
	   FROM tips_ssdzplt 
	   WHERE chkdate = :sChkDate  *//*��������*/
	// AND chkacctord  = :sChkAcctOrd /*��������*/
	// AND paybkcode = :sPayBkCode   /*�������к�*/
	// AND payeebankno = :sPayeeBankNo ;  /*�տ����к�*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24356, "��ѯ˰�ն�������ͷ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ѯ�������ձ������Ѿ��յ���������ʧ��"), 
	  fpub_GetCompname(lXmlhandle))
	  }	
	 */
	/*�ж��յ��İ������Ƿ�����Ӱ�������������ȣ��򷵻����״̬1 ��ʾ�����ΰ���δ��ȫ*/
	if (iChildPackNum != iCountPkg)
	{
		LOG(LM_STD,Fmtmsg("  -->�����ζ��˰�δȫ���ף������ж��˴���"),"ERROR");
		fpub_SetCompStatus(lXmlhandle,1);
		return 0 ;
	}
	/*��ö������ڡ��������κ��������Ѿ��յ�����ϸ���ݵ������ͽ��׽���ܼ�*/
	/* added by chenxm 20141104 DCI���칤��*/
	memset(sTemp, 0x00, sizeof(sTemp));
	sprintf(sSql1, "select count(*),SUM(traamt) from tips_ssdzmx where chkdate = '%s' and chkacctord ='%s' "
			"and paybkcode ='%s' and payeebankno='%s'", sChkDate,sChkAcctOrd,sPayBkCode,sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
	iRet = DBSelectToMultiVarChar(sErrmsg, sSql1, &cCountMxbs, &cTraamt);	
	iCountMxbs=atoi(cCountMxbs);
	dTraamt=atof(cTraamt);
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
		
		fpub_SetMsg(lXmlhandle, 24360, "��ѯ˰�ն�����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ѯ�������ձ����������Ѿ��յ���ϸ�����������׽��ϼ�ʧ��"), fpub_GetCompname(lXmlhandle))
	}

	/* noded by chenxm 20141104 DCI���칤��
	   EXEC SQL SELECT COUNT(*),NVL(SUM(traamt),0.00) 
INTO :iCountMxbs,:dTraamt
FROM tips_ssdzmx
WHERE chkdate = :sChkDate  /*��������*/
	// AND chkacctord  = :sChkAcctOrd /*��������*/
	// AND paybkcode = :sPayBkCode   /*�������к�*/
	// AND payeebankno = :sPayeeBankNo ;  /*�տ����к�*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24360, "��ѯ˰�ն�����ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ѯ�������ձ����������Ѿ��յ���ϸ�����������׽��ϼ�ʧ��"), 
	  fpub_GetCompname(lXmlhandle))
	  }	  

	 */
	/*�ж��յ�����ϸ�����Ƿ���ڰ���ϸ������������ȣ��򷵻�ʧ�ܣ��ð�����ʧ�ܣ�*/
	if (iZbs != iCountMxbs)
	{
		fpub_SetMsg(lXmlhandle, 24361, "�����ΰ���ϸ�����Ͱ�ͷ�������ϸ��������");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		/* add by tuql 20090910 ������ϸ�ۼ�������ӡ����־��*/
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�����ΰ���ϸ�����Ͱ�ͷ�������ϸ��������zbs[%d],count[%d]", iZbs ,iCountMxbs), 
				fpub_GetCompname(lXmlhandle))
	}  
	/*�ж��յ�����ϸ���׺ϼ��Ƿ���ڰ���ϸ���׺ϼƣ�������ȣ��򷵻�ʧ�ܣ��ð�����ʧ�ܣ�*/
	memset(sZje, 0x00, sizeof(sZje));
	memset(sTraamt, 0x00, sizeof(sTraamt));
	snprintf(sZje, sizeof(sZje), "%15.2f", dZje);
	snprintf(sTraamt, sizeof(sTraamt), "%15.2f", dTraamt);
	trim(sZje);
	trim(sTraamt);
	/* if (dZje != dTraamt) */    
	if (strcmp(sZje, sTraamt)!=0)
	{
		fpub_SetMsg(lXmlhandle, 24362, "�����ΰ���ϸ���ϼƺͰ�ͷ������ܽ���");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		/* add by tuql 20090910 ������ϸ�ۼƽ���ӡ����־��*/
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�����ΰ���ϸ���ϼƺͰ�ͷ������ܽ���zje[%s]sumje[%s]", sZje, sTraamt), 
				fpub_GetCompname(lXmlhandle))
	}
	fpub_SetMsg(lXmlhandle, 0, "�ж�˰�ն��ʰ�״̬����");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	LOG(LM_STD,Fmtmsg("�ж�˰�ն��ʰ�״̬����"), fpub_GetCompname(lXmlhandle));
	return COMPRET_SUCC;

}

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_ChkSSTIPS
  �������: ��TIPS��˰��ʵʱ��������
  �������: 
  ��TIPS��˰��ʵʱ��������
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��
  1                  ���ж�
  2                  TIPS��
  3                  TIPS�ࡢ���жࡡ

  ��Ҫ�������:
  ����              ����
  ˰�ն�������ͷ	tips_ssdzplt
  ˰�ն�����ϸ��Ϣ tips_ssdzmxxx

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��02��25��
  �޸�����: 2010��01��04�� 1.0.5.0
  �޸�ԭ��1.0.5.0 �����Զ������,�轫���˽��״̬����/tips/chktipszt���
  �޸�����: 20141220DCI���죬�Ѳ�
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_ChkSSTIPS(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	int iCount;
	char sChkDate[8+1];/* �������� */
	char sChkAcctType[1+1];/* �������� */
	char sChkAcctOrd[4+1];/* �������� */
	char sPayBkCode[12+1];/* �������к� */
	char sPayeeBankNo[12+1];/* �տ����к� */
	char sEntrustDate[8+1];/* ί������ */
	char sTaxOrgCode[12+1];/* ���ջ��ش��� */
	char sPackNo[8+1];/* ����ˮ�� */
	SDB_TIPS_SSDZMX stDzmx;/* ������ϸ��Ϣ */
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
	int iTpnum=0;/* Tips�ܱ��� */
	int iTpdnum=0;/* TIPS��������� */
	int iBkdnum=0; /* ���ж�ļ����� */

	/* add 20140901 */
	double dTpamt = 0.00; /* TIPS�ܽ�� */
	int iQznum = 0; /* TIPSǰ���ܱ��� */
	double dQzamt = 0.00; /* TIPSǰ���ܽ�� */

	double dTpdamt = 0.00; /* TIPSǰ�ö��ܽ�� */
	double dBkdamt = 0.00; /* ���ж��ܽ�� */    
	/* end add 20140901 */

	FILE *fp;
	CURSOR cur; /* add by chenxm DCI���칤�� 20141105 */
	CURSOR cur1;
	CURSOR cur2;
	CURSOR cur3;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(5)
		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"��������"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	trim(sChkDate);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"��������");
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd)); 
	trim(sChkAcctOrd);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(3,sBuf,"�������к�"); 
	pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
	trim(sPayBkCode);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
	COMP_GETPARSEPARAS(4,sBuf,"�տ����к�");
	pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo)); 
	trim(sPayeeBankNo);    

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctType, 0x00, sizeof(sChkAcctType));
	COMP_GETPARSEPARAS(5,sBuf,"��������");
	pstrcopy(sChkAcctType, sBuf, sizeof(sChkAcctType)); 
	trim(sChkAcctType); 

	LOG(LM_STD,Fmtmsg("��TIPS��˰���˿�ʼ����,��������[%s],��������[%s],��������[%s]",
				sChkDate,sChkAcctOrd, sChkAcctType),fpub_GetCompname(lXmlhandle));     
	LOG(LM_STD,Fmtmsg("�������к�[%s],�տ����к�[%s]",
				sPayBkCode, sPayeeBankNo),fpub_GetCompname(lXmlhandle));

	/* �Ա���г�ʼ��,ʹ������ظ����� */
	/* add by chenxm 20141105 DCI���칤�� */
	iSqlRet = DCIBegin();
	if( iSqlRet < 0 )
	{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("���µ�����ˮ��ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle));
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
	   fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("���µ�����ˮ��ʧ��"));
	   LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"), 
	   fpub_GetCompname(lXmlhandle));
	   }
	 */

	/* add by chenxm 20141105 DCI���칤�� */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz=substr(kzbz,1,1)||'0'||substr(kzbz,3,6), qsbz='0' "
			"where chkdate ='%s' and chkacctord = '%s' and paybkcode='%s' and payeebankno = '%s'",
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect( sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("����������˰����ϸ��ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle));
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
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("����������˰����ϸ��ʧ��"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"), 
	  fpub_GetCompname(lXmlhandle));
	  } */       

	/* add by chenxm 20141105 DCI���칤�� */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_pljydj SET kzbz=substr(kzbz,1,1)||'00'||substr(kzbz,4,5) "
			"where chkdate ='%s' and chkacctord = '%s' and paybkcode='%s' and payeebankno = '%s' and czbd = '7'",
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect( sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("�����������׵ǼǱ��ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����������׵ǼǱ��ʧ��"), fpub_GetCompname(lXmlhandle));
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
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("�����������׵ǼǱ��ʧ��"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����������׵ǼǱ��ʧ��"), 
	  fpub_GetCompname(lXmlhandle));
	  }*/

	/* add by chenxm 20141105 DCI���칤�� */
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzbpdj where chkdate ='%s' and chkacctord = '%s' "
			"and paybkcode='%s' and payeebankno = '%s' AND dzlx in ('2', '3') AND clzt= '0'",
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DCIExecuteDirect( sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ɾ�����˲�ƽ�ǼǱ��¼ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ�����˲�ƽ�ǼǱ��¼ʧ��"), fpub_GetCompname(lXmlhandle));
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
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ɾ�����˲�ƽ�ǼǱ��¼ʧ��"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ�����˲�ƽ�ǼǱ��¼ʧ��"), 
	  fpub_GetCompname(lXmlhandle));
	  }*/

	/* ѭ����ȡtips_ssdzmxxx���¼,��tips_drls��tips_ssplksfmx���� */
	/* add by chenxm 20141105 DCI���칤�� */	
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT * FROM  tips_ssdzmx where chkdate ='%s' and chkacctord ='%s'\
		and paybkcode ='%s' and payeebankno='%s' ORDER BY curpackno,oritrano",\
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRiSqlRetet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
	}
	//add end by chenxm 20141105

	/*EXEC SQL DECLARE cur_dzmxxx_tipsdz CURSOR for 
	  SELECT * FROM  tips_ssdzmx 
	  WHERE chkdate = :sChkDate 
	  AND chkacctord = :sChkAcctOrd
	  AND paybkcode = :sPayBkCode
	  AND payeebankno = :sPayeeBankNo
	  ORDER BY curpackno,oritrano;/* �����,ԭ������ˮ�� *//*
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));

	EXEC SQL OPEN cur_dzmxxx_tipsdz;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzmxxx_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
	if ( SQLERR )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��cur_dzmxxx_tipsdz�α�ʧ��"), 
				fpub_GetCompname(lXmlhandle));
	}        */

	/*��ʼѭ������*/
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			iflag=-1;
			LOG(LM_STD,Fmtmsg("��cur_dzmxxx_tipsdz��ȡ����ʧ��"),fpub_GetCompname(lXmlhandle));
			break;
		}
		/*if ( SQLNOTFOUND )*/
		if(iSqlRet == 0)
			break;

		iTpnum ++;
		/* add 20140901 */
		dTpamt = dTpamt + stDzmx.traamt;  /* tips��ϸ�����ܽ�� */

		/* end add 20140901 */

		trim(stDzmx.orientrustdate);
		trim(stDzmx.oritaxorgcode);
		trim(stDzmx.payeebankno);
		trim(stDzmx.paybkcode);
		trim(stDzmx.oritrano);
		trim(stDzmx.payacct);
		/*���µ�����ˮ����ί�����ڼ�������ˮ����ͬ�ļ�¼*/
		/* add by chenxm 20141105 DCI���칤�� */
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET dzbz=substr(dzbz,1,1)||'1', chkdate = '%s', chkacctord = '%s' "
				"where entrustdate='%s' and taxorgcode = '%s' and trano ='%s' and payeebankno='%s' and paybkcode ='%s' "
				"and jyje = %0.2f and msgno in ('3001', '1008') AND jyzt='0' and qsbz='0'", sChkDate, sChkAcctOrd, 
				stDzmx.orientrustdate, stDzmx.oritaxorgcode,stDzmx.oritrano,stDzmx.payeebankno,stDzmx.paybkcode,stDzmx.traamt);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		iSqlRet = DCIExecuteDirect( sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
			LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
						stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
			LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
						stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
			iflag = -2;
			break;
		}
		/* add end by chenxm */

		/* EXEC SQL UPDATE tips_drls 
		/*  SET dzbz=substr(dzbz,1,1)||'1',           ���ö��˱�־�ڶ�λΪ�Ѻ�TIPS��ƽ
		chkdate = :sChkDate,         ��������
		chkacctord = :sChkAcctOrd    ��������
		WHERE  entrustdate=:stDzmx.orientrustdate   ί������ 
		AND  taxorgcode=:stDzmx.oritaxorgcode        ���ջ��ش��� 
		AND  trano=:stDzmx.oritrano                ������ˮ�� 
		AND  msgno in ('3001', '1008')            ���ı�� 3001ʵ�� 1008���� 
		AND  payeebankno=:stDzmx.payeebankno      �տ����к� 
		AND  paybkcode=:stDzmx.paybkcode          �������к� 
		AND  jyzt='0'                             ����״̬ 0 �ɹ� 
		AND	dzbz[2]='0'                          ���˱�־ 
		AND  qsbz='0'                             �����־ 
		AND  jyje=:stDzmx.traamt;                 ���׽��  
		SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
		if ( SQLERR )
		{
		LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
		LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
		stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
		LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
		stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
		iflag = -2;
		break;
		}*/
		/* Ҫ��û�ҵ�,��������˰����ϸ���в��Ҹ��� */
		/*if ( SQLNOTFOUND_TIPS )*/

		if(iSqlRet == 0 )
		{
			/* add by chenxm 20141105 DCI���칤�� */
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),\
			 chkdate = '%s', chkacctord = '%s' where entrustdate='%s' and taxorgcode = '%s' \
			 and packno ='%s' and trano ='%s' and payeebankno='%s' and paybkcode ='%s' \
			 and jyje = %0.2f and czbd='7' and qsbz='0'", \
			 sChkDate, sChkAcctOrd, stDzmx.orientrustdate, stDzmx.oritaxorgcode,stDzmx.oripackno,\
			 stDzmx.oritrano,stDzmx.payeebankno,stDzmx.paybkcode,stDzmx.traamt);  /*stDzmx.payacct������ȶ� by liurj 20180720*/
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet = DCIExecuteDirect( sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				LOG(LM_STD,Fmtmsg("����������˰�ѱ�ʧ��"),"ERROR");
				LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
							stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
				LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
							stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
				iflag = -3;
				break;
			}
			/* add end by chenxm */

			/* EXEC SQL UPDATE tips_ssplksfmx 
			//SET kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),                  ���ö��˱�־�ڶ�λΪ�Ѻ�TIPS��ƽ
			//     chkdate = :sChkDate,         ��������
			//     chkacctord = :sChkAcctOrd    ��������
			// WHERE  entrustdate=:stDzmx.orientrustdate   ί������ 
			//   AND  taxorgcode=:stDzmx.oritaxorgcode      ���ջ��ش��� 
			//   AND  packno=:stDzmx.oripackno                ����ˮ�� add by tuql 20090506
			//   AND  trano=:stDzmx.oritrano                ������ˮ�� 
			//   AND  payeebankno=:stDzmx.payeebankno      �տ����к� 
			//  AND  paybkcode=:stDzmx.paybkcode          �������к� 
			//   AND  payacct=:stDzmx.payacct              �����˺� 
			//   AND  czbd='7'                            �������� 7 �ɹ� 
			AND	kzbz[2]='0'                          ���˱�־ 0��TIPSδ����
			AND  qsbz='0'                            �����־ 
			AND  jyje=:stDzmx.traamt;                 ���׽�� 
			SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
			if ( SQLERR )
			{
			LOG(LM_STD,Fmtmsg("����������˰�ѱ�ʧ��"),"ERROR");
			LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
			stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
			LOG(LM_STD,Fmtmsg("paybkcode[%s],payeebankno[%s],payacct[%s],jyje[%.2f]",
			stDzmx.paybkcode, stDzmx.payeebankno, stDzmx.payacct, stDzmx.traamt),fpub_GetCompname(lXmlhandle));
			iflag = -3;
			break;
			}*/

			/*������˰����ϸ��Ҳû���ҵ��ļ�¼�ǵ����ʲ�����*/
			/*if( SQLNOTFOUND_TIPS )*/
			if(iSqlRet == 0)
			{
				iRet = 2;   /*�������״̬2 ���ʲ���*/
				iTpdnum ++; /*TIPS���������*/
				memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
				/*pstrcopy(stDzbpdj.zwrq, GetSysDate(), sizeof(stDzbpdj.zwrq)); ����Ϊ��������*/
				pstrcopy(stDzbpdj.zwrq, sChkDate, sizeof(stDzbpdj.zwrq));
				stDzbpdj.zhqzlsh = 0;
				/******begin add by tuql 20091009 ���Ӳ�ѯtips_drls��tips_ssplksfmx������ֵ ******/
				memset(&stDrls, 0x00, sizeof(stDrls));

				/* add by chenxm 20141105 DCI���칤�� */
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "SELECT * FROM tips_drls where entrustdate='%s' and taxorgcode ='%s' "
						"and trano='%s' and msgno in ('3001', '1008')",stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oritrano);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
				iSqlRet = prv_SelMulToStruct( &sSql1, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls);
				/*iSqlRet =DBSelectToMultiVar(sErrmsg, sSql1, &stDrls);*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")
					
					LOG(LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"),"ERROR");
					LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
								stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
					iflag = -32;
					break;
				}
				/* add end by chenxm */

				//EXEC SQL SELECT * INTO :stDrls 
				//   FROM tips_drls
				//    WHERE entrustdate=:stDzmx.orientrustdate  /* ί������ */
				//      AND  taxorgcode=:stDzmx.oritaxorgcode       /* ���ջ��ش��� */
				//       AND  trano=:stDzmx.oritrano               /* ������ˮ�� */
				//       AND  msgno in ('3001', '1008');           /* ���ı�� 3001ʵ�� 1008���� */
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
				  if ( SQLERR )
				  {
				  LOG(LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"),"ERROR");
				  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
				  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
				  iflag = -32;
				  break;
				  }*/

				//if( SQLNOTFOUND_TIPS )/* �ڵ�����ˮ���Ҳ��� */
				if(iSqlRet == 0)
				{
					memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));

					/* add by chenxm 20141105 DCI���칤�� */
					memset(sSql1, 0x00, sizeof(sSql1));
					sprintf(sSql1, "SELECT * FROM tips_ssplksfmx where entrustdate='%s' and taxorgcode ='%s' "
							"and packno='%s' and trano ='%s'",stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oripackno,stDzmx.oritrano);
					LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
					/*iSqlRet =DBSelectToMultiVar(sErrmsg, sSql1, &stPlksfmx);*/
					iSqlRet = prv_SelMulToStruct( &sSql1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("��ѯ������˰�ѱ�ʧ��"),"ERROR");
						LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
									stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
						iflag = -33;
						break;
					}
					/*add end by chenxm */

					//EXEC SQL SELECT * INTO :stPlksfmx
					//     FROM tips_ssplksfmx
					//     WHERE  entrustdate=:stDzmx.orientrustdate  /* ί������ */
					//       AND  taxorgcode=:stDzmx.oritaxorgcode       /* ���ջ��ش��� */
					//       AND  packno=:stDzmx.oripackno               /* ����ˮ�� */
					//       AND  trano=:stDzmx.oritrano;               /* ������ˮ�� */                         
					/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
					  if ( SQLERR )
					  {
					  LOG(LM_STD,Fmtmsg("��ѯ������˰�ѱ�ʧ��"),"ERROR");
					  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s],trano[%s]",
					  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oripackno, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
					  iflag = -33;
					  break;
					  }*/
					if( iSqlRet ==0 )/* ��������ϸ�����Ҳ���,ʲô������ */
					{
						;
					}else
					{
						/******begin add by tuql 20091112 ���Ӹ���tips_ssplksfmx���� ******/
						/* add by chenxm 20141105 DCI���칤�� */
						memset(sSql1, 0x00, sizeof(sSql1));
						sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz=substr(kzbz,1,1)||'3'||substr(kzbz,3,6),chkdate='%s',chkacctord='%s' \
								where entrustdate='%s' and taxorgcode ='%s' and packno='%s' and trano ='%s'",\
								sChkDate,sChkAcctOrd,stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oripackno,stDzmx.oritrano);
						LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
						iSqlRet =DCIExecuteDirect(sSql1);
						if(iSqlRet < 0)
						{
							LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

							LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
							LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
										stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
							iflag = -35;
							break;
						}
						/*add end by chenxm */

						//EXEC SQL UPDATE tips_ssplksfmx 
						//     SET kzbz=substr(kzbz,1,1)||'3'||substr(kzbz,3,5),                 /*���ö��˱�־�ڶ�λΪ�Ѻ�TIPS��ƽ*/
						//         chkdate = :sChkDate,         /*��������*/
						//         chkacctord = :sChkAcctOrd    /*��������*/
						//     WHERE  entrustdate=:stDzmx.orientrustdate  /* ί������ */
						//       AND  taxorgcode=:stDzmx.oritaxorgcode       /* ���ջ��ش��� */
						//       AND  packno=:stDzmx.oripackno               /* ����ˮ�� add by tuql 20090506*/
						//       AND  trano=:stDzmx.oritrano;               /* ������ˮ�� */
						/*if ( SQLERR )
						  {
						  LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
						  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
						  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
						  iflag = -35;
						  break;
						  }*/
						/******end add by tuql 20091112 ���Ӹ���tips_drls��tips_ssplksfmx���� ******/        
						pstrcopy(stDzbpdj.zwrq, stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));/* �������� */
						stDzbpdj.zhqzlsh = stPlksfmx.plmxxh ;
						pstrcopy(stDzbpdj.workdate, stPlksfmx.workdate, sizeof(stDzbpdj.workdate));/* �������� */
						pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));/* �������� */
						pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));/* �������� */
						pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));/* ���׹�Ա */
						pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));/* �ն˴��� */
						pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));/* ������ˮ�� */
						pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));/* �����ʺ� */
						pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));/* �������� */
						pstrcopy(stDzbpdj.jyzh, stPlksfmx.payacct, sizeof(stDzbpdj.jyzh));/* �����˺�  add by liurj 20180719 */
					}                
				}else
				{
					/******begin add by tuql 20091112 ���Ӹ���tips_drls��tips_ssplksfmx���� ******/
					/* add by chenxm 20141105 DCI���칤�� */
					memset(sSql1, 0x00, sizeof(sSql1));
					sprintf(sSql1, "UPDATE tips_drls SET dzbz=substr(dzbz,1,1)||'3',chkdate='%s',chkacctord='%s' "
							"where entrustdate='%s' and taxorgcode ='%s' and trano ='%s' and msgno in ('3001', '1008')",
							sChkDate,sChkAcctOrd,stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oripackno,stDzmx.oritrano);
					LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
					iSqlRet =DCIExecuteDirect(sSql1);
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
						LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
									stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
						iflag = -34;
						break;
					}
					/*add end by chenxm */

					//EXEC SQL UPDATE tips_drls 
					//     SET dzbz=substr(dzbz,1,1)||'3',           /*���ö��˱�־�ڶ�λΪTIPS����*/
					//         chkdate = :sChkDate,         /*��������*/
					//         chkacctord = :sChkAcctOrd    /*��������*/
					//     WHERE  entrustdate=:stDzmx.orientrustdate  /* ί������ */
					//       AND  taxorgcode=:stDzmx.oritaxorgcode       /* ���ջ��ش��� */
					//       AND  trano=:stDzmx.oritrano               /* ������ˮ�� */
					//      AND  msgno in ('3001', '1008');           /* ���ı�� 3001ʵ�� 1008���� */
					/*if ( SQLERR )
					  {
					  LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
					  LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],trano[%s]",
					  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
					  iflag = -34;
					  break;
					  }
					 */
					/******end add by tuql 20091112 ���Ӹ���tips_drls��tips_ssplksfmx���� ******/
					pstrcopy(stDzbpdj.zwrq, stDrls.zwrq, sizeof(stDzbpdj.zwrq));/* �������� */
					stDzbpdj.zhqzlsh = stDrls.zhqzlsh ;
					pstrcopy(stDzbpdj.workdate, stDrls.workdate, sizeof(stDzbpdj.workdate));/* �������� */
					pstrcopy(stDzbpdj.dqdh, stDrls.dqdh, sizeof(stDzbpdj.dqdh));/* �������� */
					pstrcopy(stDzbpdj.jgdh, stDrls.jgdh, sizeof(stDzbpdj.jgdh));/* �������� */
					pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));/* ���׹�Ա */
					pstrcopy(stDzbpdj.zddh, stDrls.zddh, sizeof(stDzbpdj.zddh));/* �ն˴��� */
					pstrcopy(stDzbpdj.zjlsh, stDrls.zjlsh, sizeof(stDzbpdj.zjlsh));/* ������ˮ�� */
					pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));/* �����ʺ� */                    
					pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDzbpdj.jymc));/* ��������,���״��� */
					pstrcopy(stDzbpdj.jyzh, stDrls.payacct, sizeof(stDzbpdj.jyzh));/* �����˺�  add by liurj 20180719 */
				}        
				/******end add by tuql 20091009 ���Ӳ�ѯtips_drls��tips_ssplksfmx������ֵ ******/
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
				/*pstrcopy(stDzbpdj.jyzh, stDzmx.payacct, sizeof(stDzbpdj.jyzh));ע�͵�����by liurj 20180719*/
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				stDzbpdj.jyje = stDzmx.traamt; 
				pstrcopy(stDzbpdj.reason_info, "ǰ��<->TIPS;TIPS��", sizeof(stDzbpdj.reason_info));
				pstrcopy(stDzbpdj.dzjg, "93", sizeof(stDzbpdj.dzjg));
				stDzbpdj.clzt[0]='0';
				pstrcopy(stDzbpdj.kzbz, "00000000", sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
				/*Add by wangw 20120816��zhqzlshΪ0���򽫽�����ˮ�Ÿ���zhqzlsh*/
				if(stDzbpdj.zhqzlsh==0)
					stDzbpdj.zhqzlsh = atol(stDzbpdj.trano);
				/* mod by tuql 20091009
				   pstrcopy(stDzbpdj.dqdh, "", sizeof(stDzbpdj.dqdh));
				   pstrcopy(stDzbpdj.jgdh, "", sizeof(stDzbpdj.jgdh));
				   pstrcopy(stDzbpdj.jygy, "", sizeof(stDzbpdj.jygy));
				   pstrcopy(stDzbpdj.zddh, "", sizeof(stDzbpdj.zddh));
				 */

				/* add by chenxm 20141105 DCI���칤�� */
				memset(sSql1, 0x00, sizeof(sSql1));
				iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);	
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("������ʲ�ƽ�ǼǱ�ʧ��"),"ERROR");
					iflag = -4;
					break;
				}
				/*add end by chenxm */

				/* noted by chenxm 20141105 DCI���칤�� */
				/*EXEC SQL INSERT INTO tips_dzbpdj VALUES(:stDzbpdj);
				  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
				  if(SQLERR)
				  {
				  LOG(LM_STD,Fmtmsg("������ʲ�ƽ�ǼǱ�ʧ��"),"ERROR");
				  iflag = -4;
				  break;
				  }*/
			}/* if( SQLNOTFOUND_TIPS ) ������˰����ϸ����Ҳû�� */
			else
			{
				/* ����ƾ֤���ݱ�Ķ��˱�־ */
				/* add by chenxm 20141105 DCI���칤�� */
				memset(sSql1, 0x00, sizeof(sSql1));
				sprintf(sSql1, "UPDATE tips_pzsj SET dzbz='1' "
						"where entrustdate='%s' and taxorgcode ='%s' and trano ='%s'",
						stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oritrano);
				LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
				iSqlRet =DCIExecuteDirect(sSql1);
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("����ƾ֤���ݱ�ʧ��"),"ERROR");
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
				  LOG(LM_STD,Fmtmsg("����ƾ֤���ݱ�ʧ��"),"ERROR");
				  LOG(LM_STD,Fmtmsg("entrustdate[%s],oritaxorgcode[%s],trano[%s]",
				  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
				  iflag = -6;
				  break;
				  }*/
				/* add 20140901 */
				iQznum ++;
				dQzamt = dQzamt + stDzmx.traamt;  /* tipsǰ�ö����ܽ�� */

				/* end add 20140901 */    	        
			}    
		}/* if( SQLNOTFOUND_TIPS ) ������ˮ����û�� */
		else
		{    
			/* ����ƾ֤���ݱ�Ķ��˱�־ */
			/* add by chenxm 20141105 DCI���칤�� */
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_pzsj SET dzbz='1' "
					"where entrustdate='%s' and taxorgcode ='%s' and trano ='%s'",
					stDzmx.orientrustdate,stDzmx.oritaxorgcode,stDzmx.oritrano);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet =DCIExecuteDirect(sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("����ƾ֤���ݱ�ʧ��"),"ERROR");
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
			  LOG(LM_STD,Fmtmsg("����ƾ֤���ݱ�ʧ��"),"ERROR");
			  LOG(LM_STD,Fmtmsg("entrustdate[%s],oritaxorgcode[%s],trano[%s]",
			  stDzmx.orientrustdate, stDzmx.oritaxorgcode, stDzmx.oritrano),fpub_GetCompname(lXmlhandle));
			  iflag = -5;
			  break;
			  }
			 */
			/* add 20140901 */
			iQznum ++;
			dQzamt = dQzamt + stDzmx.traamt;  /* tipsǰ�ö����ܽ�� */

			/* end add 20140901 */
		}

	}/*ѭ�����Խ���*/	
	//EXEC SQL CLOSE cur_dzmxxx_tipsdz;    
	DCIFreeCursor(cur);

	if (iflag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24364, Fmtmsg("��TIPS��˰����ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��TIPS��˰����ʧ��[%d]", iflag), 
				fpub_GetCompname(lXmlhandle));
	}

	/* ѭ����ȡtips_ssplksfmx���¼,�Ѷ���������������θ��µ��������ױ���ȥ */ 
	/* add by chenxm 20141105 DCI���칤�� */	
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT entrustdate,taxorgcode,packno FROM  tips_ssplksfmx \
		where chkdate ='%s' and chkacctord ='%s' and paybkcode ='%s' and payeebankno='%s' \
		and czbd = '7' and substr(kzbz,2,1) = '1' ORDER BY entrustdate, taxorgcode, packno",\
			sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
	if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur1) == -1)
	{
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur1);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
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
	  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("���α�ʧ��"));
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��cur_plksfmx_tipsdz�α�ʧ��"), 
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iflag=-1;
			LOG(LM_STD,Fmtmsg("��cur_plksfmx_tipsdz��ȡ����ʧ��"),fpub_GetCompname(lXmlhandle));
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
		  LOG(LM_STD,Fmtmsg("��cur_plksfmx_tipsdz��ȡ����ʧ��"),fpub_GetCompname(lXmlhandle));
		  break;
		  }
		  if ( SQLNOTFOUND )
		  break;
		 */

		trim(sEntrustDate);
		trim(sTaxOrgCode);
		trim(sPackNo);

		/* ���¶������ڡ��������κ� */
		/*add by chenxm 20141105 DCI���칤��*/
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET chkdate ='%s',chkacctord='%s' \
			where entrustdate='%s' and orgcode='%s' and packno='%s'",\
			sChkDate, sChkAcctOrd, sEntrustDate, sTaxOrgCode, sPackNo);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			iflag=-2;
			LOG(LM_STD,Fmtmsg("����tips_pljydj�Ķ������ڡ���������ʧ��"),fpub_GetCompname(lXmlhandle));
			LOG(LM_STD,Fmtmsg("entrustdate[%s],taxorgcode[%s],packno[%s]",
						sEntrustDate, sTaxOrgCode, sPackNo),fpub_GetCompname(lXmlhandle));
			break;
		}
		/*add end by chenxm */

		/*EXEC SQL UPDATE tips_pljydj 
		  SET chkdate = :sChkDate,
		  chkacctord = :sChkAcctOrd 
		  WHERE  entrustdate=:sEntrustDate  */      /*ί������*/
		// AND  orgcode=:sTaxOrgCode          /*���ջ��ش���*/
		// AND	packno=:sPackNo;                 /*����ˮ��*/
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));          
		  if ( SQLERR )
		  {  
		  iflag=-2;
		  LOG(LM_STD,Fmtmsg("����tips_pljydj�Ķ������ڡ���������ʧ��"),fpub_GetCompname(lXmlhandle));
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
		fpub_SetMsg(lXmlhandle, 24365, Fmtmsg("�����������׵ǼǱ�Ķ������ڼ���������ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����������׵ǼǱ�Ķ������ڼ���������ʧ��[%d]", iflag), 
				fpub_GetCompname(lXmlhandle));
	}

	/* ���ռ���˲�ƽ�ļ� */
	memset(sRjbpFile, 0x00, sizeof(sRjbpFile));
	snprintf(sRjbpFile, sizeof(sRjbpFile),"%s/file/tips/chkacct/rjdzbp_%s_%s_%s_%s",
			getenv("HOME"),sChkDate,sPayBkCode,sPayeeBankNo,sChkAcctOrd);
	fp = fopen(sRjbpFile, "wt");
	if(fp == NULL)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24366, Fmtmsg("���ռ���˲�ƽ�ļ�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ռ���˲�ƽ�ļ�ʧ��[%s][%s]", 
					strerror(errno), sRjbpFile), fpub_GetCompname(lXmlhandle));
	}
	fprintf(fp,"�ռ���ʲ�ƽ��¼[%s %s]\n", GetSysDate(), GetSysTime());

	/*
	   �ж��Ƿ���û�к˶Ե�ǰ����ˮ
	   ��������ж��ˣ��������˲�ƽ�ǼǱ�������ռ���ˣ�������ʱ�ļ�
	   ״̬���������ж��걨�ɿ�ҵ�񲻲��뵱�ն��ˣ�
	   ˳�������ս��ж��ˣ������涨���޵�������˰ҵ�񽫽������ϴ���
	 */
	iCount = 0 ;
	/* add by chenxm 20141105 DCI���칤��*/
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iSqlRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fclose(fp);
		fpub_SetMsg(lXmlhandle, 24367, "��ѯ������ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))
	}
	iCount = atol(sTemp);
	/* add end by chenxm */

	/*EXEC SQL SELECT COUNT(*) INTO :iCount 
	  FROM tips_drls 
	  WHERE jyzt = '0'*/                  /*����״̬0 �ɹ�*/
	//AND qsbz = '0' 
	//AND substr(dzbz,2,1) = '0'               /* ���˱�־�ڶ�λ��0-δ��TIPS���� */
	//AND paybkcode = :sPayBkCode     /*�������к�*/
	//AND payeebankno = :sPayeeBankNo /*�տ����к�*/
	/*AND ( 
	  ( msgno = '3001' AND workdate = :sChkDate )	
	  OR
	  ( msgno = '1008' AND workdate  = :sChkDate )*/ /* �Ե���û�ж�ƽ��1008,Ҫ�Գ��������ط� */                    
	//);  
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");	
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetMsg(lXmlhandle, 24367, "��ѯ������ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ѯ������ˮ��ʧ��"), 
	  fpub_GetCompname(lXmlhandle))
	  }*/
	LOG(LM_STD, Fmtmsg("����[%s]û�к˶Ե�ǰ�õ�����ˮ[%d]��",sChkDate,iCount), fpub_GetCompname(lXmlhandle))        
		/* �統ǰ�����յ�����ˮ����δ�˶Ե���ˮ */
		if ( iCount > 0 )
		{
			if(iRet == 2) 
				iRet == 3;  /*״̬3 TIPS�ж࣬����Ҳ��*/
			else
				iRet = 1;   /*״̬1 ���ж�*/

			iBkdnum = iBkdnum + iCount;  /*iBkdnum���ж�ļ�����*/

			/* add by chenxm 20141105 DCI���칤�� */	
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT * FROM tips_drls WHERE jyzt = '0' AND qsbz = '0'\
				AND substr(dzbz,2,1) = '0' AND paybkcode ='%s' AND payeebankno='%s' AND\
				 ( ( msgno = '3001' AND workdate = '%s' ) OR ( msgno = '1008' AND workdate  = '%s' ))",\
					sPayBkCode, sPayeeBankNo,sChkDate,sChkDate);
			if ((cur2 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				return COMPRET_FAIL;
			}
			if (DCIExecute(cur2) == -1)
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
					DCIFreeCursor(cur2);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
			}
			/*add end by chenxm 20141105*/

			/*EXEC SQL DECLARE cur_drls_tipsdz CURSOR for 
			  SELECT *
			  FROM  tips_drls
			  WHERE jyzt = '0'                  ����״̬0 �ɹ�
			  AND qsbz = '0' 
			  AND substr(dzbz,2,1) = '0'                ���˱�־�ڶ�λ��0-δ��TIPS���� 
			  AND paybkcode = :sPayBkCode     /�������к�/
			  AND payeebankno = :sPayeeBankNo /�տ����к�*/
			/*  AND ( 
				( msgno = '3001' AND workdate = :sChkDate )	
				OR
				( msgno = '1008' AND workdate  = :sChkDate )*/ /* �Ե���û�ж�ƽ��1008,Ҫ�Գ��������ط�                     
																  );
																  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));*/

			/*EXEC SQL OPEN cur_drls_tipsdz;
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_drls_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
			  if ( SQLERR )
			  {
			  fclose(fp);
			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("���α�ʧ��"));
			  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��cur_drls_tipsdz�α�ʧ��"), 
			  fpub_GetCompname(lXmlhandle));
			  }*/

			/* ѭ���������ж��ʵʱ��ˮ��¼ */
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					iflag=-1;
					LOG(LM_STD,Fmtmsg("��cur_drls_tipsdz��ȡ����ʧ��"),fpub_GetCompname(lXmlhandle));
					break;
				}
				/*if ( SQLNOTFOUND )*/
				if(iSqlRet == 0)
					break;

				trim(stDrls.jyrq);
				trim(stDrls.payeebankno);
				trim(stDrls.payacct);

				/* add 20140901 */
				dBkdamt = dBkdamt + stDrls.jyje; /*iBkdnum���ж�Ľ�� */
				/* end 20140901 */

				if(strncmp(stDrls.msgno, "3001", 4) == 0)
				{
					LOG_SSTIPS("3111",Fmtmsg("-->(ʵʱ)���ж�,TIPS�ޣ���������[%s],ǰ����ˮ[%d],�����տ���[%s],�ʺ�[%s],���[%15.2f],����취��TIPSΪ׼,��������",
								stDrls.zwrq,stDrls.zhqzlsh,stDrls.payeebankno,stDrls.payacct,stDrls.jyje),sPayBkCode,sChkDate);
					/* strcpy(stDzbpdj.jymc, "ʵʱ�ۿ�"); mod by tuql 20090910*/
				}
				else
				{
					LOG_SSTIPS("3111",Fmtmsg("-->(����)���ж�,TIPS�ޣ���������[%s],ǰ����ˮ[%d],�����տ���[%s],�ʺ�[%s],���[%15.2f],����취��TIPSΪ׼,��������",
								stDrls.zwrq,stDrls.zhqzlsh,stDrls.payeebankno,stDrls.payacct,stDrls.jyje),sPayBkCode,sChkDate);
					/* strcpy(stDzbpdj.jymc, "���нɿ�"); mod by tuql 20090910*/
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
				/* pstrcopy(stDzbpdj.jymc, "ǰ��<->TIPS;ʵʱǰ�ö�", sizeof(stDzbpdj.jymc)); mod by tuql 20090910*/
				pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDrls.msgno));
				pstrcopy(stDzbpdj.jyzh, stDrls.payacct, sizeof(stDzbpdj.jyzh));  		    
				pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));
				pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
				pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.jyqd, stDrls.jyqd, sizeof(stDzbpdj.jyqd));
				pstrcopy(stDzbpdj.jysj, stDrls.jysj, sizeof(stDzbpdj.jysj));  		    
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				pstrcopy(stDzbpdj.dzjg, "92", sizeof(stDzbpdj.dzjg));
				stDzbpdj.jyje = stDrls.jyje;
				pstrcopy(stDzbpdj.reason_info, "ǰ��<->TIPS;ʵʱǰ�ö�", sizeof(stDzbpdj.reason_info));
				stDzbpdj.clzt[0]='0';
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				pstrcopy(stDzbpdj.kzbz, stDrls.kzbz, sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.dqdh, stDrls.dqdh, sizeof(stDzbpdj.dqdh));
				pstrcopy(stDzbpdj.jgdh, stDrls.jgdh, sizeof(stDzbpdj.jgdh));
				pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.zddh, stDrls.zddh, sizeof(stDzbpdj.zddh));
				if(sChkAcctType[0] == '1')/* ���ж��� */
				{
					iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);
					/*EXEC SQL INSERT INTO tips_dzbpdj VALUES(:stDzbpdj);
					  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");*/
					/*if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						iflag=-2;
						LOG(LM_STD,Fmtmsg("������ʵǼǱ�ʧ��"),"ERROR");
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
			}/* ѭ���������ж��ʵʱ��ˮ��¼ */
			DCIFreeCursor(cur2);
			/*EXEC SQL CLOSE cur_drls_tipsdz;   */ 

			if (iflag < 0)
			{
				fclose(fp);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24368, Fmtmsg("��TIPS����ʱ����ǰ�ö�ʵʱ��ˮ��¼ʧ��"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��TIPS����ʱ����ǰ�ö���ˮʵʱ��¼ʧ��[%d]", iflag), 
						fpub_GetCompname(lXmlhandle));
			}

			/*��������ж��ˣ������Ѻ˶Թ�, ���ж��ʵʱ��ˮ*/
			if(sChkAcctType[0] == '1')
			{
				LOG(LM_STD,"���ж��ˣ������Ѻ˶Թ���ʵʱ��ˮ��¼","INFO");
				/*����Ѻ˶Թ�, ���ж����ˮ*/
				//add by chenxm 20141105 DCI���칤��
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
				  dzbz=substr(dzbz,1,1)||'2'   /          / ���˱�־ 2-ǰ�ö� /
				  WHERE jyzt = '0'                  /����״̬0 �ɹ�/
				  AND qsbz = '0' 
				  AND substr(dzbz,2,1) = '0'               / ���˱�־�ڶ�λ��0-δ��TIPS���� /
				  AND paybkcode = :sPayBkCode     /�������к�/
				  AND payeebankno = :sPayeeBankNo /�տ����к�/
				  AND ( 
				  ( msgno = '3001' AND workdate = :sChkDate )	
				  OR
				  ( msgno = '1008' AND workdate < :sChkDate ) *//* �˴�Ϊ< ��Ҫ�����ж˽ɿ�����ն���                     
				);
				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
				if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						fclose(fp);
						fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
						fpub_SetMsg(lXmlhandle, 24369, Fmtmsg("��TIPS����ʱ���µ�����ˮ��ʧ��"));
						LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��TIPS����ʱ���µ�����ˮ��ʧ��"), 
								fpub_GetCompname(lXmlhandle));
					}


				/* add 20140901 */
				dBkdamt = dBkdamt + stDrls.jyje; /*iBkdnum���ж�Ľ�� */
				/* end 20140901 */


			}/*if(sChkAcctType[0] == '1')��������ж��ˣ������Ѻ˶Թ�, ���ж��ʵʱ��ˮ*/
		}/* if ( iCount > 0 ) �統ǰ�����յ�����ˮ����δ�˶Ե���ˮ */

	/*
	   �ж��Ƿ���û�к˶Ե�ǰ��������ˮ
	   ��������ж��ˣ��������˲�ƽ��������ռ���ˣ�������ʱ�ļ�
	   ״̬�����Ķ�ʱ������˰ҵ������ж��걨�ɿ�ҵ�񲻲��뵱�ն��ˣ�
	   ˳�������ս��ж��ˣ������涨���޵�������˰ҵ�񽫽������ϴ���
	 */
	iCount = 0 ;
	//add by chenxm 20141105 DCI���칤��
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
	  AND workdate = :sChkDate   */    /*��������*/
	//  AND paybkcode = :sPayBkCode    /*�������к�*/
	//  AND payeebankno = :sPayeeBankNo;   /*�տ����к�*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");	
	  if ( SQLERR )*/
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fclose(fp);
		fpub_SetMsg(lXmlhandle, 24370, "��ѯ������˰����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), 
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_STD, Fmtmsg("û�к˶Ե�ǰ��������ˮ[%d]��", iCount), fpub_GetCompname(lXmlhandle))
		/* �統ǰ������������˰����ϸ����δ�˶Ե���ˮ */
		if ( iCount > 0 )
		{
			if(iRet == 2 || iRet == 3) 
				iRet == 3;  /*״̬3 TIPS�ж࣬����Ҳ��*/
			else
				iRet = 1;   /*״̬1 ���ж�*/

			iBkdnum = iBkdnum + iCount;  /*���ж�ļ�����*/

			/* add by chenxm 20141105 DCI���칤�� */	
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT * FROM tips_ssplksfmx WHERE czbd= '7' \
				AND substr(kzbz,2,1)='0' AND workdate ='%s' AND paybkcode ='%s' AND payeebankno = '%s'",\
					sChkDate,sPayBkCode, sPayeeBankNo);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			if ((cur3 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				return COMPRET_FAIL;
			}
			if (DCIExecute(cur3) == -1)
			{
				fclose(fp);
				LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
					DCIFreeCursor(cur1);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
			}
			//add end by chenxm 20141105

			/*EXEC SQL DECLARE cur_ksfmx_tipsdz CURSOR for 
			  SELECT *
			  FROM tips_ssplksfmx 
			  WHERE czbd= '7'  
			  AND substr(kzbz,2,1)='0'    
			  AND workdate = :sChkDate       //��������//
			  AND paybkcode = :sPayBkCode    //�տ����к�//
			  AND payeebankno = :sPayeeBankNo;   //�տ����к�//
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));

			  EXEC SQL OPEN cur_ksfmx_tipsdz;
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ksfmx_tipsdz",sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
			  if ( SQLERR )
			  {
			  fclose(fp);
			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			  fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("���α�ʧ��"));
			  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��cur_ksfmx_tipsdz�α�ʧ��"), 
			  fpub_GetCompname(lXmlhandle));
			  }*/
			/* ѭ���������ж��������ˮ��¼ */
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					iflag=-1;
					LOG(LM_STD,Fmtmsg("��cur_drls_tipsdz��ȡ����ʧ��"),fpub_GetCompname(lXmlhandle));
					break;
				}
				//if ( SQLNOTFOUND )
				if(iSqlRet == 0)
					break;

				trim(stPlksfmx.payeebankno);
				trim(stPlksfmx.payacct);
				LOG_SSTIPS("3111",Fmtmsg("-->(����)���ж�,TIPS�ޣ���������[%s],ǰ����ˮ[%d],�����տ���[%s],�ʺ�[%s],���[%15.2f],����취��TIPSΪ׼,��������",
							stPlksfmx.zwrq,stPlksfmx.plmxxh,stPlksfmx.payeebankno,stPlksfmx.payacct,stPlksfmx.jyje),sPayBkCode,sChkDate);

				pstrcopy(stDzbpdj.zwrq,stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));
				pstrcopy(stDzbpdj.workdate,stPlksfmx.workdate, sizeof(stDzbpdj.workdate));
				stDzbpdj.zhqzlsh = stPlksfmx.plmxxh;  /*������ϸ���*/
				if(sChkAcctType[0]=='0')
					stDzbpdj.dzlx[0]='2';
				else
					stDzbpdj.dzlx[0]='3';
				pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));/* add by tuql 20090507 ������ˮ��*/	
				pstrcopy(stDzbpdj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stDzbpdj.taxorgcode));
				pstrcopy(stDzbpdj.entrustdate, stPlksfmx.entrustdate, sizeof(stDzbpdj.entrustdate));
				pstrcopy(stDzbpdj.chkdate, sChkDate, sizeof(stDzbpdj.chkdate));
				pstrcopy(stDzbpdj.chkacctord, sChkAcctOrd, sizeof(stDzbpdj.chkacctord));
				pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));
				pstrcopy(stDzbpdj.payeebankno, sPayeeBankNo, sizeof(stDzbpdj.payeebankno));
				pstrcopy(stDzbpdj.paybkcode, sPayBkCode, sizeof(stDzbpdj.paybkcode));
				pstrcopy(stDzbpdj.jyrq, stPlksfmx.zwrq, sizeof(stDzbpdj.jyrq));
				pstrcopy(stDzbpdj.jysj, stPlksfmx.zjsj, sizeof(stDzbpdj.jysj));
				/* pstrcopy(stDzbpdj.jymc, "ǰ��<->TIPS;����ǰ�ö�", sizeof(stDzbpdj.jymc)); */
				pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));
				pstrcopy(stDzbpdj.khmc, stPlksfmx.handorgname, sizeof(stDzbpdj.khmc));
				pstrcopy(stDzbpdj.jyzh, stPlksfmx.payacct, sizeof(stDzbpdj.jyzh));
				pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				stDzbpdj.jyje = stPlksfmx.jyje;
				pstrcopy(stDzbpdj.reason_info, "ǰ��<->TIPS;����ǰ�ö�", sizeof(stDzbpdj.reason_info));
				pstrcopy(stDzbpdj.dzjg, "92", sizeof(stDzbpdj.dzjg));
				stDzbpdj.clzt[0]='0';
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
				pstrcopy(stDzbpdj.kzbz, stPlksfmx.kzbz, sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.byzd, sPackNo, sizeof(stDzbpdj.byzd));
				pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));
				pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));
				pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));
				/*Add by wangw 20120816��zhqzlshΪ0���򽫽�����ˮ�Ÿ���zhqzlsh*/
				if(stDzbpdj.zhqzlsh==0)
					stDzbpdj.zhqzlsh = atol(stDzbpdj.trano);
				if(sChkAcctType[0] == '1')/* ���ж��� */
				{
					//EXEC SQL INSERT INTO tips_dzbpdj VALUES(:stDzbpdj);
					iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, sErrmsg);
					/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
					  if(SQLERR)*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						
						iflag=-2;
						LOG(LM_STD,Fmtmsg("������ʵǼǱ�ʧ��"),"ERROR");
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
			}/* for (i=1; i<= iCount ;i++)ѭ���������ж��������ˮ��¼ */            
			/*EXEC SQL CLOSE cur_ksfmx_tipsdz;    */

			if (iflag < 0)
			{
				fclose(fp);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, 24371, Fmtmsg("��TIPS����ʱ����ǰ�ö�������ˮ��¼ʧ��"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��TIPS����ʱ����ǰ�ö�������ˮ��¼ʧ��[%d]", iflag), 
						fpub_GetCompname(lXmlhandle));
			}

			/*��������ж��ˣ������Ѻ˶Թ�, ���ж��������ˮ*/
			if(sChkAcctType[0] == '1')
			{
				LOG(LM_STD,"���ж��ˣ������Ѻ˶Թ���������ˮ��¼","INFO");
				/*����Ѻ˶Թ�, ���ж��������ˮ*/
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
				  kzbz=substr(kzbz,1,1)||'2'||substr(kzbz,3,6)             //��չ��־ 2-ǰ�ö� //
				  WHERE czbd= '7'  
				  AND substr(kzbz,2,1)='0'    
				  AND workdate = :sChkDate       //��������//
				  AND paybkcode = :sPayBkCode    //�տ����к�//
				  AND payeebankno = :sPayeeBankNo;   //�տ����к�*/
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
				  if(SQLERR)*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					fclose(fp);
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
					fpub_SetMsg(lXmlhandle, 24372, Fmtmsg("��TIPS����ʱ����������˰����ϸ��ʧ��"));
					LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��TIPS����ʱ����������˰����ϸ��ʧ��"), 
							fpub_GetCompname(lXmlhandle));
				}

				/* add 20140901 */
				dBkdamt = dBkdamt + stPlksfmx.jyje; /*iBkdnum���ж�Ľ�� */
				/* end 20140901 */

			}
		}/* if ( iCount > 0 )�統ǰ������������˰����ϸ����δ�˶Ե���ˮ */		
	fclose(fp);
	LOG_SSTIPS("3111",Fmtmsg("============================================================================="),sPayBkCode,sChkDate);
	LOG_SSTIPS("3111",Fmtmsg("   �˶�TIPS��ϸ�ܱ���[%d]  TIPS��ı���[%d]  ���ж�ı���[%d]\n",iTpnum,iTpdnum,iBkdnum),sPayBkCode,sChkDate);
	
	/* add dci 20141103 */
	iSqlRet=DCICommit();
	/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��    		
	if ( iSqlRet < 0 )
  {
     	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
     	DCIRollback();
      	
     	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
     	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     	return COMPRET_FAIL;     
  }
  */
	/* end dci */
	
	fpub_SetMsg(lXmlhandle, 0, "��TIPS��˰���˽���");
	fpub_SetCompStatus(lXmlhandle, iRet);
	/* add by tuql 20100104 1.0.5.0 �����˽���˸�/tips/chktipszt��� */
	memset(sBuf, 0x00, sizeof(sBuf));
	snprintf(sBuf, sizeof(sBuf), "%d", iRet);
	COMP_SOFTSETXML("/tips/chktipszt", sBuf)
		LOG(LM_STD,Fmtmsg("��TIPS��˰���˽���"), fpub_GetCompname(lXmlhandle));
	LOG(LM_STD,Fmtmsg("�˶�TIPS��ϸ�ܱ���[%d],TIPS��ı���[%d],���ж�ı���[%d]",
				iTpnum,iTpdnum,iBkdnum), fpub_GetCompname(lXmlhandle));

	/* ���Ӷ��˽��ͳ�� add 20140901 */
	/* ��ʼ�����˽���ǼǱ� 
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"), 
				fpub_GetCompname(lXmlhandle));
	}
	/* add 20140901 
	iQznum += iBkdnum;
	dQzamt += dBkdamt;  /* tipsǰ�ö����ܽ�� 

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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		LOG(LM_STD,Fmtmsg("������ʽ��ʧ��,��������[%s],����ϵͳ[%s]", 
					stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")   
			iflag = -13;

	} */   
	LOG(LM_STD,Fmtmsg("TIPS��ϸ�ܱ���[%d],TIPS��ϸ�ܽ��[%f],TIPSǰ�ñ���[%d],TIPSǰ�ý��[%f]",
				iTpnum,dTpamt,iQznum,dQzamt), fpub_GetCompname(lXmlhandle));    
	return COMPRET_SUCC;
}


/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_ChkYHJKXX
  �������: ���ж˽ɿ���Ϣ�˶�

  �������: 
  ���ж˽ɿ���Ϣ�˶�
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����
  ˰�ն�������ͷ	tips_ssdzplt
  ˰�ն�����ϸ��Ϣ tips_ssdzmxxx

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��02��27��
  �޸�����: 20141105 DCI���칤��(done)
  �޸�����: 20141220DCI���죬�Ѳ�
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_ChkYHJKXX(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	SDB_TIPS_DRLS stDrls;
	char sPayBkCode[12+1];/* �������к� */
	char sPackNo[8+1];/* ����ˮ��--��Ϊ�������� */
	char sChkDate[8+1];/* �������� */
	int iCurPackNum;/* �������� */
	int iCurPackNo;/* ������� */
	//EXEC SQL END   DECLARE SECTION;

	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128]; 
	char sBuf[256];
	char sNode[256];/* �ڵ�·�� */
	char sFile[256];
	char sYhjkbfFlow[60];
	char sJyzt[50+1];/* ����״̬ */
	int i;
	int iSucc=0;
	int iFail=0;
	int iSqlRet = -1;
	FILE *fp;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(6);
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(1, sBuf, "�������к�")
		pstrcopy( sPayBkCode, sBuf, sizeof(sPayBkCode));
	trim(sPayBkCode);            

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPackNo, 0x00, sizeof(sPackNo));
	COMP_GETPARSEPARAS(2, sBuf, "����ˮ��")
		pstrcopy( sPackNo, sBuf, sizeof(sPackNo));
	trim(sPackNo); 

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(3, sBuf, "��������")
		pstrcopy( sChkDate, sBuf, sizeof(sChkDate));
	trim(sChkDate); 

	memset(sBuf, 0x00, sizeof(sBuf));
	iCurPackNum = 0 ;
	COMP_GETPARSEPARAS(4, sBuf, "��������")
		iCurPackNum = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	iCurPackNo = 0 ;
	COMP_GETPARSEPARAS(5, sBuf, "�������")
		iCurPackNo = atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYhjkbfFlow, 0x00, sizeof(sYhjkbfFlow));
	COMP_GETPARSEPARAS(6, sBuf, "���нɿ��������")
		pstrcopy( sYhjkbfFlow, sBuf, sizeof(sYhjkbfFlow));
	trim(sYhjkbfFlow); 

	LOG(LM_STD,Fmtmsg("���ж˽ɿ���Ϣ�˶Կ�ʼ����... �������к�[%s],����ˮ��[%s],��������[%s]", 
				sPayBkCode, sPackNo, sChkDate), fpub_GetCompname(lXmlhandle));
	LOG(LM_STD,Fmtmsg("��������[%d],�������[%d], ���нɿ��������[%s]", 
				iCurPackNum, iCurPackNo, sYhjkbfFlow), fpub_GetCompname(lXmlhandle));

	/*���˽���ļ���*/
	memset(sFile, 0x00, sizeof(sFile));   
	snprintf(sFile, sizeof(sFile),"%s/file/tips/chkacct/yhjkdz_%s_%s",
			getenv("HOME"),sPayBkCode,sChkDate);
	trim(sFile);
	LOG(LM_STD,Fmtmsg("���ж˽ɿ���˽���ļ�[%s]", sFile), fpub_GetCompname(lXmlhandle));

	/*�����ļ�*/
	fp=fopen(sFile,"a+");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24376, Fmtmsg("�����ж˽ɿ���˽���ļ�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����ж˽ɿ���˽���ļ�ʧ��[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	/*�ļ�ͷ*/
	fprintf(fp,"                                              ���ж˽ɿ�����ļ�\n");
	fprintf(fp,"     �������к�:%s                   ����ˮ��:%s               ��������:%s            �������:%d \n",
			sPayBkCode,sPackNo,sChkDate,iCurPackNo);
	fprintf(fp,"=========================================================================================================\n");
	fprintf(fp,"��������к�   ԭ���ջ��ش���   ԭί������   ԭ������ˮ��   ˰Ʊ����          ���׽��   ����״̬      \n");
	fprintf(fp,"=========================================================================================================\n");

	for(i=1;i<=iCurPackNum;i++)
	{
		memset(&stDrls,0x00,sizeof(stDrls)); 
		memset(sJyzt, 0x00, sizeof(sJyzt));

		/*��������к�*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/PayOpBkCode",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.paybkcode,sBuf,sizeof(stDrls.paybkcode));

		/*ԭ�����������*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/OriTaxOrgCode",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.taxorgcode,sBuf,sizeof(stDrls.taxorgcode));

		/*ԭί������*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/OriEntrustDate",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.entrustdate,sBuf,sizeof(stDrls.entrustdate));

		/*ԭ����ˮ��*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/OriTraNo",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.trano,sBuf,sizeof(stDrls.trano));

		/*ԭ˰Ʊ����*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/TaxVouNo",i);
		COMP_SOFTGETXML(sNode,sBuf);
		pstrcopy(stDrls.taxvouno,sBuf,sizeof(stDrls.taxvouno));

		/*���׽��*/
		memset(sNode, 0x00, sizeof(sNode));
		memset(sBuf, 0x00, sizeof(sBuf));
		snprintf(sNode,sizeof(sNode),"/tips/MSG/BankCompare3113|%d/TraAmt",i);
		COMP_SOFTGETXML(sNode,sBuf);
		stDrls.jyje=atof(sBuf);

		/*���ҽ���״̬��Ϊ�����ڴ����Ľ���*/
		/*add by chenxm 20141105 DCI���칤��*/
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT distinct zwrq,xym,jyzt from tips_drls "
			"where taxorgcode='%s' and entrustdate='%s' "
				"and trano ='%s' and taxvouno='%s' and jyje = %0.2f ",
				stDrls.taxorgcode,stDrls.entrustdate,stDrls.trano,stDrls.taxvouno,stDrls.jyje);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		iSqlRet = DBSelectToMultiVar(sErrmsg, sSql1, stDrls.zwrq,stDrls.xym,stDrls.jyzt);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			fclose(fp);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24377, Fmtmsg("��ѯ������ˮ��ʧ��"));
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle));
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
		fpub_SetMsg(lXmlhandle, 24377, Fmtmsg("��ѯ������ˮ��ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle));
		} 
		if ( SQLNOTFOUND_TIPS )*/
		if(iSqlRet == 0)
		{
			iFail++;
			LOG(LM_DEBUG,Fmtmsg("���ж��޴˽���,���ջ��ش���[%s],ί������[%s],������ˮ��[%s],˰Ʊ����[%s],���׽��[%.2f]",
						stDrls.taxorgcode, stDrls.entrustdate, stDrls.trano, stDrls.taxvouno, stDrls.jyje),fpub_GetCompname(lXmlhandle));
			pstrcopy(stDrls.xym, "24020", sizeof(stDrls.xym));
			pstrcopy(sJyzt, "���ж��޴˽���", sizeof(sJyzt));
		
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
			/*����ԭ����״̬Ϊʧ��*/
			iSqlRet = DCIBegin();
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
					fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
				return COMPRET_FAIL;
			}
  		
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "UPDATE tips_drls  SET jyzt='1',xym='94999',xyxx='���ж˽ɿ�����' "
				"where taxorgcode='%s' "
					"and entrustdate='%s' and trano='%s' and taxvouno='%s' and jyje=%0.2f and jyzt='9'",
					stDrls.taxorgcode,stDrls.entrustdate,stDrls.trano,stDrls.taxvouno,stDrls.jyje);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
			iSqlRet = DCIExecuteDirect(sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
  		
				fclose(fp);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
				fpub_SetMsg(lXmlhandle, 24378, Fmtmsg("���µ�����ˮ��ʧ��"));
				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle));
			}
  		
			/*EXEC SQL UPDATE tips_drls 
			  SET jyzt='1',
			  xym='94999',
			  xyxx='���ж˽ɿ�����'
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
			  fpub_SetMsg(lXmlhandle, 24378, Fmtmsg("���µ�����ˮ��ʧ��"));
			  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle));
			  }
			  EXEC SQL commit ;*/
			iSqlRet=DCICommit(); 
			/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��   		
			if ( iSqlRet < 0 )
    	{
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    	}
    	*/
			pstrcopy(stDrls.xym, "24020", sizeof(stDrls.xym));
			pstrcopy(sJyzt, "�û��걨��δȷ�Ͽۿ�", sizeof(sJyzt));
		}else if(stDrls.jyzt[0]=='0')
		{
			iSucc++;
			pstrcopy(sJyzt, "�ɹ��Ľ���", sizeof(sJyzt));
		}else if(stDrls.jyzt[0]=='1')
		{       	    
			iSucc++;
			pstrcopy(sJyzt, "ʧ�ܵĽ���", sizeof(sJyzt));
		}else
		{
			iSucc++;
			pstrcopy(sJyzt, "�Ѿ������Ľ���", sizeof(sJyzt));
		}
		
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/Result",stDrls.xym);
		COMP_SOFTSETXML("/CFX/MSG/SingleReturn2108/AddWord",sJyzt);
		/* ���������� */
		if ( fpub_CallFlow(lXmlhandle,sYhjkbfFlow) != MID_SYS_SUCC)
		{
			LOG(LM_STD,Fmtmsg("  -->Call������ʧ��,����[%s]",sYhjkbfFlow),fpub_GetCompname(lXmlhandle));
			memset(sJyzt, 0x00, sizeof(sJyzt));
			strcpy(sJyzt,"���׷���ʧ��");
		}	
		fprintf(fp,"%-17.17s%-17.17s%-13.13s%-15.15s%-18.18s%8.2f   %-14.14s\n",
				stDrls.paybkcode,stDrls.taxorgcode,stDrls.entrustdate,
				stDrls.trano,stDrls.taxvouno,stDrls.jyje,sJyzt);
		}
		fclose(fp);
		LOG(LM_DEBUG,Fmtmsg("һ���յ�[%d]�ʣ��ɹ�ת��[%d]�ʣ�[%d]��û�ҵ����ڴ���״̬",
					iCurPackNum,iSucc,iFail), fpub_GetCompname(lXmlhandle));      	 
		fpub_SetMsg(lXmlhandle, 0, "���ж˽ɿ���Ϣ�˶Խ���");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
		return COMPRET_SUCC;
}
/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_HXDZ
  �������: ����Ķ���

  �������: 
  ����Ķ���
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��02��27��
  �޸�����: modify by chenxm 20141112 DCI���칤��
  �޸�����: 20141220DCI���죬�Ѳ�
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_HXDZ(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	int iCount;
	int iCount2;
	char sDzrq[8+1];/* �������� */
	char sPrevDate[8+1];/* ������ʼ�� */
	SDB_TIPS_HXDZMX stDetail;
	/*BANKDetail stDetail;*/
	SDB_TIPS_DRLS stDrls;
	SDB_TIPS_SSPLKSFMX stPlksfmx;
	SDB_TIPS_DZBPDJ stDzbpdj;         
	double dBkdamt = 0.00; /* TIPSǰ�ö��� add 20140901 */
	SDB_TIPS_DZJGXX stDzjgxx;  /*  add 20140901 */
	
	char sChkAcctOrd[4+1];/* �������� add 20140901 */
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
	int iQzdnum = 0;     /*ǰ�ö�ļ�¼��*/
	int iZjdnum = 0;    /*������ļ�¼��*/ 

	/* add 20140901 */
	double dQzdamt =0.00; /*ǰ�ö��� */
	int iZjnum = 0;   /* �����ܱ��� */
	double dZjamt = 0.00; /* �����ܽ�� */
	int iQznum = 0; /* TIPSǰ���ܱ��� */
	double dQzamt = 0.00; /* TIPSǰ���ܽ�� */    
	/* end add 20140901 */   
	FILE *fp;
	CURSOR cur;
	CURSOR cur1;
	char sIsHxPlDz[1+1];/* add by tuql 20090910 �����������˱�־ */

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(4);
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sMxFileName, 0x00, sizeof(sMxFileName));
	COMP_GETPARSEPARAS(1, sBuf, "������ϸ�ļ�")
		pstrcopy(sMxFileName, sBuf, sizeof(sMxFileName));
	trim(sMxFileName);            
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sResIcxp, 0x00, sizeof(sResIcxp));
	COMP_GETPARSEPARAS(2, sBuf, "��ϸ�ļ�ICXP����")
		pstrcopy(sResIcxp, sBuf, sizeof(sResIcxp));
	trim(sResIcxp); 
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzrq, 0x00, sizeof(sDzrq));
	COMP_GETPARSEPARAS(3, sBuf, "��������")
		pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
	trim(sDzrq); 
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPrevDate, 0x00, sizeof(sPrevDate));
	COMP_GETPARSEPARAS(4, sBuf, "������ʼ����")
		pstrcopy(sPrevDate, sBuf, sizeof(sPrevDate));
	trim(sPrevDate);    

	LOG(LM_STD,Fmtmsg("����Ķ��˿�ʼ����..."),fpub_GetCompname(lXmlhandle))  
		LOG(LM_STD,Fmtmsg("��������[%s],���˳�ʼ��[%s],������ϸ�ļ�[%s],��ϸ�ļ�ICXP����[%s]",
					sDzrq, sPrevDate, sMxFileName, sResIcxp),fpub_GetCompname(lXmlhandle))  

	/* add by tuql 20090910 �����������˱�־ */
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sIsHxPlDz, 0x00, sizeof(sIsHxPlDz));
	COMP_SOFTGETXML("/tips/ishxpldz", sBuf)
		sIsHxPlDz[0] = sBuf[0];
	if (sIsHxPlDz[0]=='\0')
		sIsHxPlDz[0]='1';
	LOG(LM_STD,Fmtmsg("�Ƿ�μ��������������[%s]:0-��,1-��", sIsHxPlDz),fpub_GetCompname(lXmlhandle))     

		//add by chenxm 20141112 DCI���칤��
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
				fpub_GetCompname(lXmlhandle))        
	}           

	//add by chenxm 20141112 DCI���칤��
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������˰����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������˰����ϸ��ʧ��"),
				fpub_GetCompname(lXmlhandle))        
	}
  LOG(LM_STD,Fmtmsg("�򿪺��Ķ����ļ�"),"INFO")
	/*�Ƚ�����ϸ�ļ�,У��*/
	fp = fopen(sMxFileName,"r");
	if ( fp == NULL )
	{
		fpub_SetMsg(lXmlhandle, 24422, "�򿪺��Ķ����ļ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�򿪺��Ķ����ļ�ʧ��[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle))
	}

	/*�ļ��崦��*/
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
				break;                   /*�ļ����� ����*/
		sLine[strlen(sLine)-1]=0;   /* ȥ�����һ�����з� */
		trim(sLine);
		/*
		   if ( i==1 || strlen(sLine)<30 )
		   continue;               ���������ļ���ͷ,���� */
		if (strcmp(sLine,"END") == 0 )
		   break;                  /* ���������ļ�������*/
		LOG(LM_STD,Fmtmsg("�����[%d]����ϸ",i),"INFO")		
		LOG(LM_STD,Fmtmsg("��[%d]����ϸ��[%s]",i,sLine),"INFO")	
		iRet=SBATCH_FuncICXPUPKG(lXmlhandle,sResIcxp,sLine,strlen(sLine));
		if (iRet < 0)
		{ 
			iFlag = -1; 
			break; 
		}		
		LOG(LM_STD,Fmtmsg("�ɹ�������[%d]����ϸ",i),"INFO")		
		
		memset(&stDetail, 0x00, sizeof(stDetail));
    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/dzlx", sBuf)
    stDetail.dzlx[0]=sBuf[0];
    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/zjrq", sBuf)
    pstrcopy(stDetail.zjrq, sBuf, sizeof(stDetail.zjrq));
    /* ������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/zjlsh", sBuf)
    pstrcopy(stDetail.zjlsh, sBuf, sizeof(stDetail.zjlsh));
    /* ת�������ʺ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/zcyhzh", sBuf)
    pstrcopy(stDetail.zcyhzh, sBuf, sizeof(stDetail.zcyhzh));
    /* ���׽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jyje", sBuf)
    stDetail.jyje=atof(sBuf);
    /* ǰ������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/qzrq", sBuf)
    pstrcopy(stDetail.qzrq, sBuf, sizeof(stDetail.qzrq));
    /* ǰ����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/qzlsh", sBuf)
    stDetail.qzlsh=atoi(sBuf);
    /* ���׵������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jydqdh", sBuf)
    pstrcopy(stDetail.jydqdh, sBuf, sizeof(stDetail.jydqdh));
    /* ���׻������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jyjgdh", sBuf)
    pstrcopy(stDetail.jyjgdh, sBuf, sizeof(stDetail.jyjgdh));
    /* ������־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/czbz", sBuf)
    stDetail.czbz[0]=sBuf[0];
    /* ���״��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hxdz/jydm", sBuf)
    pstrcopy(stDetail.jydm, sBuf, sizeof(stDetail.jydm));
		
		/* ������ˮ��� add 20141107 ���и�������ȷ��������ˮ�Ƿ���� */  
		iCount=0;
		/* add dci 20141210 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_hxdzmx "
    	"where QZRQ='%s' and QZLSH=%d",sDzrq,stDetail.qzlsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")    
               
        fpub_SetMsg(lXmlhandle, 24201, "��ѯ������ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    if( iCount > 0)
    {
    	LOG(LM_STD,Fmtmsg("������ˮ�Ѵ��ڣ�������������������[%s],ǰ����ˮ��[%d]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
      ;
    }   
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_hxdzmx", SD_TIPS_HXDZMX, NUMELE(SD_TIPS_HXDZMX), &stDetail, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      LOG(LM_STD,Fmtmsg("������Ķ��ʽ��ʧ��,��������[%s],ǰ����ˮ��[%s]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
    	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("������Ķ��ʽ��ʧ��"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������Ķ��ʽ��ʧ��"), 
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
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("��ѯ�������˵ǼǱ��¼ʧ��"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�������˵ǼǱ��¼ʧ��"), 
        fpub_GetCompname(lXmlhandle));
    }
    LOG(LM_STD,Fmtmsg("tips-test44,sLine[%s],",
        sLine),"ERROR") 
    if( iCount > 0)
    {
    	LOG(LM_STD,Fmtmsg("������ˮ�Ѵ��ڣ�������������������[%s],ǰ����ˮ��[%d]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
      ;
    }    		
    LOG(LM_STD,Fmtmsg("tips-test5,sLine[%s],",
        sLine),"ERROR") 
		EXEC SQL INSERT INTO tips_hxdzmx values(:stDetail);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
     	LOG(LM_STD,Fmtmsg("������Ķ��ʽ��ʧ��,��������[%s],ǰ����ˮ��[%s]", 
           stDetail.qzrq, stDetail.qzlsh),"ERROR")   
    	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("������Ķ��ʽ��ʧ��"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������Ķ��ʽ��ʧ��"), 
        fpub_GetCompname(lXmlhandle));
     
    }	
    */
		
		/*����˼�¼Ϊ����,��������� add by tuql 20091222 
		  if( stDetail.dzlx[0] =='2' && sIsHxPlDz[0]=='0' )
		  { 
		  LOG(LM_STD,Fmtmsg("�˽���Ϊ��������[%s][%d][%s],�������������", 
		  stDetail.qzrq, stDetail.qzlsh, stDetail.dzlx),"ERROR")
		  continue;
		  }*/

		/*����˼�¼Ϊ����,��������һ����¼��,���������ļ�¼���������*/
    if( stDetail.czbz[0] =='2' )
    { 
        LOG(LM_STD,Fmtmsg("�˽��ױ�����[%s][%d][%s],����", 
                    stDetail.qzrq, stDetail.qzlsh, stDetail.czbz),"ERROR")
        continue;
    }
		/*���ڳ�������,����ҵ�����ˮ��,�Ҳ������Ҷ��˵ǼǱ�,���Ҳ����������˵ǼǱ�*/
		if(memcmp(stDetail.jydm, "36916", 5) == 0)
		{
			/*�ӵ�����ˮ����ȡ������Ϣ*/
			iCount = 0;

			//add by chenxm 20141112 DCI���칤��
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("���ҵ�����ˮ�������¼ʧ��,��������[%s],ǰ����ˮ��[%d]", 
							stDetail.qzrq, stDetail.qzlsh),"ERROR")   
					iFlag = -3;
				break;	
			}
			/* ���ڵ�����ˮ�����Ҳ��� */
			if ( iCount == 0 )
			{
				/*�ӵ��˱�ȡ������Ϣtips_dzbpdj*/
				iCount2 = 0;

				//add by chenxm 20141112 DCI���칤��
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
				  AND clzt='5' */ /*�ѵ���*/;
				/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
				  if(SQLERR)*/
				if(iSqlRet < 0)
				{
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("���Ҷ��˲�ƽ�������¼ʧ��,��������[%s],ǰ����ˮ��[%d]", 
								stDetail.qzrq, stDetail.qzlsh),"ERROR")   
						iFlag = -5;
					break;
				}
				if ( iCount2 == 0 )
				{
					iZjdnum ++;
					LOG_SSTIPS("3111",Fmtmsg("-->����������,ǰ���ޣ�ǰ������[%s],ǰ����ˮ[%d],��������[%s],������ˮ[%s],�ʺ�[%s],���[%.2f],����취������Ϊ׼,��ԭ��",
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
					pstrcopy(stDzbpdj.jymc, "������������", sizeof(stDzbpdj.jymc));
					pstrcopy(stDzbpdj.jyzh, stDetail.zcyhzh, sizeof(stDzbpdj.jyzh));
					stDzbpdj.jyje = stDetail.jyje;
					pstrcopy(stDzbpdj.reason_info, "ǰ��<->����;����������", sizeof(stDzbpdj.reason_info));
					pstrcopy(stDzbpdj.dzjg, "39", sizeof(stDzbpdj.dzjg));
					stDzbpdj.clzt[0]='0';
					pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
					pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
					stDzbpdj.cllsh = 0;
					pstrcopy(stDzbpdj.kzbz, "00000000", sizeof(stDzbpdj.kzbz));
					pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
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
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("������ʵǼǱ�ʧ��,��������[%s],ǰ����ˮ��[%d]", 
									stDetail.qzrq, stDetail.qzlsh),"ERROR")   
							iFlag = -7;
						break;  	  			  	
					}    	  	    	
				}/* if ( iCount2 == 0 )�������ף��ڶ��˵ǼǱ����Ҳ��� */                
			}/* if ( iCount == 0 )�������ף��ڵ�����ˮ�����Ҳ��� */
		}/* if(memcmp(stDetail.jydm, "", 4) == 0)����ǳ�������*/
		else/* �������� */
		{
			LOG(LM_DEBUG,Fmtmsg("HXDZ��ǰ������[%s],ǰ����ˮ[%d],��������[%s],������ˮ[%s],�ʺ�[%s],���[%.2f]",
								stDetail.qzrq,stDetail.qzlsh,stDetail.zjrq,stDetail.zjlsh,stDetail.zcyhzh,stDetail.jyje),"INFO")      
			/* add 20140901 */
			iZjnum ++;
			dZjamt = dZjamt + stDetail.jyje;  /* ������ϸ�����ܽ�� */
			/* end add 20140901 */
			
			/*�ӵ�����ˮ����ȡ�������ڼ�ǰ����ˮ����ͬ�ļ�¼*/
			//add by chenxm 20141112 DCI���칤��
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
							stDetail.qzrq, stDetail.qzlsh),"ERROR")   
					iFlag = -9;
				break;
			}            
			/*����Ҳ��������������˰����ϸ����ȡ�������ڼ�ǰ����ˮ����ͬ�ļ�¼*/
			//if( SQLNOTFOUND_TIPS ) 
			if(iSqlRet == 0)
			{   
				//add by chenxm 20141112 DCI���칤��
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("����������˰����ϸ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
								stDetail.qzrq, stDetail.qzlsh),"ERROR")   
						iFlag = -11;
					break;
				}
				/*û���ҵ��ļ�¼�ǵ����ʲ�����*/
				//if(SQLNOTFOUND_TIPS)
				if(iSqlRet == 0)
				{
					iZjdnum ++;

					LOG_SSTIPS("3111",Fmtmsg("-->������,ǰ���ޣ�ǰ������[%s],ǰ����ˮ[%d],��������[%s],������ˮ[%s],�ʺ�[%s],���[%.2f],����취������Ϊ׼,��ԭ��",
								stDetail.qzrq,stDetail.qzlsh,stDetail.zjrq,stDetail.zjlsh,stDetail.zcyhzh,stDetail.jyje),"HXDZ",sDzrq);
					memset(&stDzbpdj, 0, sizeof(stDzbpdj));
					pstrcopy(stDzbpdj.zwrq, stDetail.qzrq, sizeof(stDzbpdj.zwrq));
					stDzbpdj.zhqzlsh = stDetail.qzlsh;
					/******begin add by tuql 20091009 ���Ӳ�ѯtips_drls��tips_ssplksfmx������ֵ ******/
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
					  AND  msgno in ('3001', '1008');   */        /* ���ı�� 3001ʵ�� 1008���� */
					/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),fpub_GetCompname(lXmlhandle));
					  if ( SQLERR )*/
					if(iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
									stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle)) 
							iFlag = -32;
						break;
					}
					//if( SQLNOTFOUND_TIPS )/* �ڵ�����ˮ���Ҳ��� */
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
							LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

							LOG(LM_STD,Fmtmsg("��ѯ������˰����ϸ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
										stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle))
								iFlag = -33;
							break;
						}
						/*if( SQLNOTFOUND_TIPS )*//* ��������ϸ�����Ҳ���,ʲô������ */
						if(iSqlRet == 0)
						{
							;
						}
						else
						{
							/******begin add by tuql 20091112 ���Ӹ���tips_drls��tips_ssplksfmx���� ******/ 
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
								LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

								LOG(LM_STD,Fmtmsg("����������˰����ϸ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
											stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle))
									iFlag = -35;
								break;
							}                               
							/******end add by tuql 20091112 ���Ӹ���tips_drls��tips_ssplksfmx���� ******/
							pstrcopy(stDzbpdj.zwrq, stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));/* �������� */
							stDzbpdj.zhqzlsh = stPlksfmx.plmxxh ;
							pstrcopy(stDzbpdj.workdate, stPlksfmx.workdate, sizeof(stDzbpdj.workdate));/* �������� */
							pstrcopy(stDzbpdj.chkdate, stPlksfmx.workdate, sizeof(stDzbpdj.chkdate));/* �������� */
							pstrcopy(stDzbpdj.paybkcode, stPlksfmx.paybkcode, sizeof(stDzbpdj.paybkcode));/* �������к� */
							pstrcopy(stDzbpdj.payeebankno, stPlksfmx.payeebankno, sizeof(stDzbpdj.payeebankno));/* ��������к� */
							pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));/* �������� */
							pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));/* �������� */
							pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));/* ���׹�Ա */
							pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));/* �ն˴��� */
							pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));/* ������ˮ�� */
							pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));/* �����ʺ� */
							pstrcopy(stDzbpdj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stDzbpdj.taxorgcode));/* ���ջ��ش��� */
							pstrcopy(stDzbpdj.entrustdate, stPlksfmx.entrustdate, sizeof(stDzbpdj.entrustdate));/* ί������ */
							pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));/* ������ˮ�� */
							pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));/* ���״��� */
							pstrcopy(stDzbpdj.khmc, stPlksfmx.handorgname, sizeof(stDzbpdj.khmc));/* �ɿλ���� */

						}                
					}
					else
					{
						/******begin add by tuql 20091112 ���Ӹ���tips_drls��tips_ssplksfmx���� ******/ 
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
							LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
							
							LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
										stDetail.qzrq, stDetail.qzlsh),fpub_GetCompname(lXmlhandle)) 
								iFlag = -34;
							break;
						}                               
						/******end add by tuql 20091112 ���Ӹ���tips_drls��tips_ssplksfmx���� ******/       
						pstrcopy(stDzbpdj.zwrq, stDrls.zwrq, sizeof(stDzbpdj.zwrq));/* �������� */
						stDzbpdj.zhqzlsh = stDrls.zhqzlsh ;
						pstrcopy(stDzbpdj.workdate, stDrls.workdate, sizeof(stDzbpdj.workdate));/* �������� */
						pstrcopy(stDzbpdj.chkdate, stDrls.workdate, sizeof(stDzbpdj.chkdate));/* �������� */
						pstrcopy(stDzbpdj.paybkcode, stDrls.paybkcode, sizeof(stDzbpdj.paybkcode));/* �������к� */
						pstrcopy(stDzbpdj.payeebankno, stDrls.payeebankno, sizeof(stDzbpdj.payeebankno));/* ��������к� */
						pstrcopy(stDzbpdj.dqdh, stDrls.dqdh, sizeof(stDzbpdj.dqdh));/* �������� */
						pstrcopy(stDzbpdj.jgdh, stDrls.jgdh, sizeof(stDzbpdj.jgdh));/* �������� */
						pstrcopy(stDzbpdj.jygy, stDrls.jygy, sizeof(stDzbpdj.jygy));/* ���׹�Ա */
						pstrcopy(stDzbpdj.zddh, stDrls.zddh, sizeof(stDzbpdj.zddh));/* �ն˴��� */
						pstrcopy(stDzbpdj.zjlsh, stDrls.zjlsh, sizeof(stDzbpdj.zjlsh));/* ������ˮ�� */
						pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));/* �����ʺ� */                    
						pstrcopy(stDzbpdj.taxorgcode, stDrls.taxorgcode, sizeof(stDzbpdj.taxorgcode));/* ���ջ��ش��� */
						pstrcopy(stDzbpdj.entrustdate, stDrls.entrustdate, sizeof(stDzbpdj.entrustdate));/* ί������ */
						pstrcopy(stDzbpdj.trano, stDrls.trano, sizeof(stDzbpdj.trano));/* ������ˮ�� */
						pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDzbpdj.jymc));/* ���״��� */
						pstrcopy(stDzbpdj.khmc, stDrls.handorgname, sizeof(stDzbpdj.khmc));/* �ɿλ���� */

						/* add 20140901 */
						iQznum ++;
						dQzamt = dQzamt + stDetail.jyje;  /* tipsǰ�ö����ܽ�� */
						/* end add 20140901 */
					}        
					/******end add by tuql 20091009 ���Ӳ�ѯtips_drls��tips_ssplksfmx������ֵ ******/ 
					stDzbpdj.dzlx[0]='1';
					pstrcopy(stDzbpdj.zjlsh, stDetail.zjlsh, sizeof(stDzbpdj.zjlsh));
					//pstrcopy(stDzbpdj.zjlsh,stDetail.zjlsh,sizeof(stDzbpdj.zjlsh));
					/* mod by tuql 20091009 ��������Ϣ����
					   LOG(LM_STD,Fmtmsg("qzlsh[%d]zjlsh[%s]",stDetail.qzlsh,stDetail.zjlsh),"ERROR");
					   pstrcopy(stDzbpdj.paybkcode, "", sizeof(stDzbpdj.paybkcode));
					   pstrcopy(stDzbpdj.chkdate, sDzrq, sizeof(stDzbpdj.chkdate));
					 */
					pstrcopy(stDzbpdj.chkacctord, "", sizeof(stDzbpdj.chkacctord));
					pstrcopy(stDzbpdj.jyrq, stDetail.qzrq, sizeof(stDzbpdj.jyrq));
					/* mod by tuql 20091020 ��������Ϣ����
					   pstrcopy(stDzbpdj.jymc, "�ۿ��", sizeof(stDzbpdj.jymc));
					 */
					pstrcopy(stDzbpdj.jyzh, stDetail.zcyhzh, sizeof(stDzbpdj.jyzh));
					stDzbpdj.jyje = stDetail.jyje;
					pstrcopy(stDzbpdj.reason_info, "ǰ��<->����;������", sizeof(stDzbpdj.reason_info));
					pstrcopy(stDzbpdj.dzjg, "39", sizeof(stDzbpdj.dzjg));
					pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));/* add by tuql 20091020 */
					stDzbpdj.clzt[0]='0';
					pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
					pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
					stDzbpdj.cllsh = 0;
					pstrcopy(stDzbpdj.kzbz, "00000000", sizeof(stDzbpdj.kzbz));
					pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
					/* mod by tuql 20091020 ��������Ϣ����
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
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

						LOG(LM_STD,Fmtmsg("������ʵǼǱ�ʧ��,��������[%s],ǰ����ˮ��[%d]", 
									stDetail.qzrq, stDetail.qzlsh),"ERROR")   
							iFlag = -13;
						break;
					}
				}
				else
				{	
					/* add 20140901 */
					iQznum ++;
					dQzamt = dQzamt + stDetail.jyje;  /* tipsǰ�ö����ܽ�� */
					/* end add 20140901 */
				}/* ��ƽ�������׼��� */
			}/* �ڵ�����ˮ���Ҳ���*/
			else
			{		
				/* add 20140901 */
				iQznum ++;
				dQzamt = dQzamt + stDetail.jyje;  /* tipsǰ�ö����ܽ�� */
				/* end add 20140901 */
			}/* ��ƽʵʱ���׼��� */
		}/* �������� */                       
	}/* for (iFlag=0,i=1; ;i++)�ļ��崦��*/
	fclose(fp);
	if (iFlag < 0)
	{ 
		fpub_SetMsg(lXmlhandle,24423,Fmtmsg("��������������ʧ��"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������������ʧ��,ret[%d]..",iFlag),"ERROR");
	}
	/*�ж��Ƿ���û�к˶Ե�ǰ����ˮ--ǰ�ö�*/
	iCount = 0;
	dBkdamt = 0.00; /* add dBkdamt 20140901 */

	//add by chenxm 20141112 DCI���칤��
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR") 
		
		fpub_SetMsg(lXmlhandle,24424,Fmtmsg("��ѯ������ˮ��ʧ��"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"),"ERROR");
	}
	if( iCount > 0 )
	{
		iQzdnum = iQzdnum + iCount; /* ǰ�ö������++ */
		/* add 20140901 */
		dQzdamt += dBkdamt ;
		/* end add 20140901 */

		/* ��ǰ�ö����ˮ��¼�Ǽǵ����˲�ƽ����ȥ */
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT * FROM  tips_drls \
			WHERE zwrq <= '%s' AND zwrq >= '%s' AND jyzt='0' AND msgno in ('3001','1008') \
			AND substr(dzbz,1,1) = '0'", sDzrq, sPrevDate);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
		{
			LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		if (DCIExecute(cur) == -1)
		{
			LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
				DCIFreeCursor(cur);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, 24425, Fmtmsg("ִ���α�ʧ��"));
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
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
		  fpub_SetMsg(lXmlhandle,24425, "���α�ʧ��");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("HXDZ��cur_drls_hxdz�α�ʧ��"),
		  fpub_GetCompname(lXmlhandle))
		  }         */ 
		/*��ʼѭ��*/
		for (i=1,iFlag=0;;i++)
		{
			memset(&stDrls, 0x00, sizeof(stDrls));

			iSqlRet = DBFetch(cur, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls, sErrmsg);
			/*EXEC SQL FETCH cur_drls_hxdz INTO :stDrls;     
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_drls_hxdz",sqlca.sqlcode),"ERROR");
			  if ( SQLERR )*/
			if(iSqlRet < 0)
			{  
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				iFlag=-1;
				LOG(LM_STD,Fmtmsg("HXDZ��cur_drls_hxdz�α��ȡ����ʧ��"),"ERROR");
				break;
			}
			if(iSqlRet == 0)
				/*if ( SQLNOTFOUND )*/
				break;

			/* add 20140901 */
			dBkdamt = dBkdamt + stDrls.jyje; /*iBkdnum���ж�Ľ�� */
			/* end 20140901 */

			LOG_SSTIPS("3111",Fmtmsg("-->(ʵʱ)ǰ�ö�,�����ޣ���������[%s],ǰ����ˮ[%d],������[%s],�ʺ�[%s],���[%.2f],����취������Ϊ׼,��ԭ��",
						stDrls.zwrq,stDrls.zhqzlsh,stDrls.payopbkcode,stDrls.payacct,stDetail.jyje),"HXDZ",sDzrq);    	  	    	  	
			memset(&stDzbpdj, 0, sizeof(stDzbpdj));
			pstrcopy(stDzbpdj.zwrq, stDrls.zwrq, sizeof(stDzbpdj.zwrq));
			stDzbpdj.zhqzlsh = stDrls.zhqzlsh;
			stDzbpdj.dzlx[0]='1';/* ���������� */
			pstrcopy(stDzbpdj.zjlsh, stDrls.zjlsh, sizeof(stDzbpdj.zjlsh));
			pstrcopy(stDzbpdj.workdate, stDrls.workdate, sizeof(stDzbpdj.workdate));
			pstrcopy(stDzbpdj.taxorgcode, stDrls.taxorgcode, sizeof(stDzbpdj.taxorgcode));
			pstrcopy(stDzbpdj.entrustdate, stDrls.entrustdate, sizeof(stDzbpdj.entrustdate));
			/* mod by tuql 20091009 ������ϢӦ��ֵΪ������ˮ���workdateֵ
			   pstrcopy(stDzbpdj.chkdate, sDzrq, sizeof(stDzbpdj.chkdate));
			 */
			pstrcopy(stDzbpdj.chkdate, stDrls.workdate, sizeof(stDzbpdj.chkdate));
			/* mod by tuql 20091020 ������ϢӦ��ֵΪ������ˮ���chkacctordֵ
			   pstrcopy(stDzbpdj.chkacctord, "", sizeof(stDzbpdj.chkacctord));
			 */
			pstrcopy(stDzbpdj.chkacctord, stDrls.chkacctord, sizeof(stDzbpdj.chkacctord));
			pstrcopy(stDzbpdj.trano, stDrls.trano, sizeof(stDzbpdj.trano));
			pstrcopy(stDzbpdj.payeebankno, stDrls.payeebankno, sizeof(stDzbpdj.payeebankno));
			/* mod by tuql 20091009 ������ϢӦ��ֵΪ������ˮ���paybkcodeֵ
			   pstrcopy(stDzbpdj.paybkcode, stDrls.payopbkcode, sizeof(stDzbpdj.paybkcode));  		                
			 */
			pstrcopy(stDzbpdj.paybkcode, stDrls.paybkcode, sizeof(stDzbpdj.paybkcode));  		                
			pstrcopy(stDzbpdj.jyrq, stDrls.jyrq, sizeof(stDzbpdj.jyrq));
			pstrcopy(stDzbpdj.jysj, stDrls.jysj, sizeof(stDzbpdj.jysj));
			pstrcopy(stDzbpdj.jymc, stDrls.msgno, sizeof(stDzbpdj.jymc));
			pstrcopy(stDzbpdj.khmc, stDrls.handorgname, sizeof(stDzbpdj.khmc));
			pstrcopy(stDzbpdj.jyzh, stDrls.payacct, sizeof(stDzbpdj.jyzh));
			pstrcopy(stDzbpdj.zhzl, stDrls.handletype, sizeof(stDzbpdj.zhzl));
			/* mod by tuql 20091009 ������ϢӦ��ֵΪ������ˮ���dfzhֵ
			   pstrcopy(stDzbpdj.dfzh, stDrls.payeeacct, sizeof(stDzbpdj.dfzh));
			 */
			pstrcopy(stDzbpdj.dfzh, stDrls.dfzh, sizeof(stDzbpdj.dfzh));
			pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));           
			stDzbpdj.jyje = stDrls.jyje;
			pstrcopy(stDzbpdj.reason_info, "ǰ��<->����;ǰ�ö�", sizeof(stDzbpdj.reason_info));
			pstrcopy(stDzbpdj.dzjg, "29", sizeof(stDzbpdj.dzjg));
			stDzbpdj.clzt[0]='0';
			pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
			pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
			stDzbpdj.cllsh = 0;
			pstrcopy(stDzbpdj.kzbz, stDrls.dzbz, sizeof(stDzbpdj.kzbz));
			pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("������ʵǼǱ�ʧ��,��������[%s],ǰ����ˮ��[%d]", 
							stDrls.zwrq, stDrls.zhqzlsh),"ERROR")   
					iFlag = -3;
				break;  	  			  	
			}
			/*���¸���ˮ��ϸ״̬Ϊǰ�ö�*/
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
							stDrls.zwrq, stDrls.zhqzlsh),"ERROR")   
					iFlag = -5;
				break; 
			}
		}/* for (i=1,iFlag=0;;i++) */    
		/*EXEC SQL CLOSE cur_drls_hxdz;   */
		DCIFreeCursor(cur);

		if (iFlag < 0)
		{
			fpub_SetMsg(lXmlhandle,24426,"��������Ķ���ʱ����ǰ�ö�����ʧ��");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������Ķ���ʱ����ǰ�ö�����ʧ��iflag=[%d]",iFlag),
					fpub_GetCompname(lXmlhandle))
		}

	}/* if( iCount > 0 )����Ķ���ǰ�ö����� */ 

	/* add by tuql 20090910 �ж��Ƿ�����������μӶ��� 0-���μ�*/
	if (sIsHxPlDz[0]=='0')
	{
		LOG(LM_STD,Fmtmsg("----��������û�μӶ���"),fpub_GetCompname(lXmlhandle))
			/* begin add by tuql 20091112 ���¶��˱�־Ϊƽ */

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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			fpub_SetMsg(lXmlhandle,24424,Fmtmsg("����������˰�ѱ�ʧ��"));
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������˰�ѱ�ʧ��"),"ERROR");
		}
		/* end add by tuql 20091112 ���¶��˱�־Ϊƽ */
		LOG(LM_DEBUG,Fmtmsg("������������˽���,������[%d]��, ǰ�ö�[%d]��", 
					iZjdnum, iQzdnum), fpub_GetCompname(lXmlhandle));
		fpub_SetMsg(lXmlhandle, 0, "������������˽���");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
		return COMPRET_SUCC;        
	}    

	/*�ж��Ƿ���û�к˶Ե�ǰ������������ˮ*/
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle,24424,Fmtmsg("��ѯ������˰�ѱ�ʧ��"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������˰�ѱ�ʧ��"),"ERROR");
	}
	if( iCount > 0 )
	{
		iQzdnum = iQzdnum + iCount; /* ǰ�ö������++ */
		/* add 20140901 */        
		dQzdamt += dBkdamt ;
		/* end add 20140901 */

		/* ��ǰ�ö����ˮ��¼�Ǽǵ����˲�ƽ����ȥ */
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT * FROM  tips_ssplksfmx where zwrq <='%s' and zwrq >='%s' "
				"AND czbd='7' AND substr(kzbz,1,1)='0'",sDzrq, sPrevDate);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
		{
			LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		if (DCIExecute(cur1) == -1)
		{
			LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
				DCIFreeCursor(cur1);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, 24425, Fmtmsg("ִ���α�ʧ��"));
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
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
		  fpub_SetMsg(lXmlhandle,24425, "���α�ʧ��");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("HXDZ��cur_plksfmx_hxdz�α�ʧ��"),
		  fpub_GetCompname(lXmlhandle))
		  }*/

		/*��ʼѭ��*/
		for (i=1,iFlag=0;;i++)
		{
			memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
			/*EXEC SQL FETCH cur_plksfmx_hxdz INTO :stPlksfmx;   
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_plksfmx_hxdz",sqlca.sqlcode),"ERROR");
			  if ( SQLERR )*/
			iSqlRet = DBFetch(cur1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);	
			if(iSqlRet < 0)
			{  
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				iFlag=-1;
				LOG(LM_STD,Fmtmsg("HXDZ��cur_plksfmx_hxdz�α��ȡ����ʧ��"),"ERROR");
				break;
			}
			/*if ( SQLNOTFOUND )*/
			if(iSqlRet == 0)
				break;
			LOG_SSTIPS("3111",Fmtmsg("-->(����)ǰ�ö�,�����ޣ���������[%s],ǰ����ˮ[%d],��������[%s],����[%s],��ˮ��[%s],������[%s],�ʺ�[%s],���[%.2f],����취������Ϊ׼,��ԭ��",
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
			/* mod by tuql 20091009 ������ϢӦ��ֵΪ������ϸ���workdateֵ
			   pstrcopy(stDzbpdj.chkdate, sDzrq, sizeof(stDzbpdj.chkdate));
			 */
			pstrcopy(stDzbpdj.chkdate, stPlksfmx.workdate, sizeof(stDzbpdj.chkdate));
			/* mod by tuql 20091020 ������ϢӦ��ֵΪ������ˮ���chkacctordֵ
			   pstrcopy(stDzbpdj.chkacctord, "", sizeof(stDzbpdj.chkacctord));
			 */
			pstrcopy(stDzbpdj.chkacctord, stPlksfmx.chkacctord, sizeof(stDzbpdj.chkacctord));
			pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));
			pstrcopy(stDzbpdj.payeebankno, stPlksfmx.payeebankno, sizeof(stDzbpdj.payeebankno));
			/* mod by tuql 20091009 ������ϢӦ��ֵΪ������ϸ���paybkcodeֵ
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
			pstrcopy(stDzbpdj.reason_info, "ǰ��<->����;ǰ�ö�", sizeof(stDzbpdj.reason_info));
			pstrcopy(stDzbpdj.dzjg, "29", sizeof(stDzbpdj.dzjg));
			/* stDzbpdj.clzt[0]='8'; mod by tuql 20091020 */
			stDzbpdj.clzt[0]='0';
			pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
			pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
			stDzbpdj.cllsh = 0;
			pstrcopy(stDzbpdj.kzbz, stPlksfmx.kzbz, sizeof(stDzbpdj.kzbz));
			pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("������ʵǼǱ�ʧ��,��������[%s],������ϸ���[%d]", 
							stPlksfmx.zwrq, stPlksfmx.plmxxh),"ERROR")   
					iFlag = -3;
				break;  	  			  	
			}
			/*���¸���ˮ��ϸ״̬Ϊǰ�ö�*/
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("����������˰����ϸ��ʧ��,��������[%s],������ϸ���[%d]", 
							stPlksfmx.zwrq, stPlksfmx.plmxxh),"ERROR")   
					iFlag = -5;
				break; 
			}
		}/* for (i=1,iFlag=0;;i++) */
		//EXEC SQL CLOSE cur_plksfmx_hxdz; 
		DCIFreeCursor(cur1);
		if (iFlag < 0)
		{
			fpub_SetMsg(lXmlhandle,24427,"��������Ķ���ʱ����ǰ�ö�����ʧ��");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
			LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������Ķ���ʱ����ǰ�ö�����ʧ��iflag=[%d]",iFlag),
					fpub_GetCompname(lXmlhandle))
		}
	}/* if( iCount > 0 )����Ķ���ǰ�ö����� */ 
	LOG(LM_DEBUG,Fmtmsg("������������˽���,������[%d]��, ǰ�ö�[%d]��", 
				iZjdnum, iQzdnum), fpub_GetCompname(lXmlhandle));

	/* ���Ӷ��˽��ͳ�� add 20140901 
	/* ��ʼ�����˽���ǼǱ� 
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"), 
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		LOG(LM_STD,Fmtmsg("������ʽ��ʧ��,��������[%s],����ϵͳ[%s]", 
					stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")   
			iFlag = -13;

	}*/    
	LOG(LM_STD,Fmtmsg("������ϸ�ܱ���[%d],������ϸ�ܽ��[%f],TIPSǰ�ñ���[%d],TIPSǰ�ý��[%f]",
				iZjnum,dZjamt,iQznum,dQzamt), fpub_GetCompname(lXmlhandle));    

	fpub_SetMsg(lXmlhandle, 0, "������������˽���");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);    

	return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_GenREP_DZQD
  �������: ����TIPS�����嵥����
  �������: 
  ����TIPS�����嵥����
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��03��05��
  �޸�����: 2009��10��9��
  �޸�˵����modify by chenxm 20141112 DCI���칤��
  �޸�����: 20141220DCI���죬����
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_GenREP_DZQD(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	char sPayBkCode[12+1];/* �������к� */
	char sChkDate[8+1];/*��������*/
	char sChkAcctType[1+1];/* �������� */
	char sPayeeBankNo[12+1];/* �տ����к� */
	char sChkAcctOrd[4+1];/* �������� */
	int iAllNum;/* �ܱ��� */
	double dAllAmt;/* �ܽ�� */
	int iAllNum1;/* �ܱ��� */
	double dAllAmt1;/* �ܽ�� */
	int iAllNum2;/* �ܱ��� */
	double dAllAmt2;/* �ܽ�� */
	int iMzNum;/* ��Ĩ�˱��� add by tuql 20091009 */
	double dMzAmt; /* ��Ĩ�˽�� add by tuql 20091009 */
	int iBzNum;/* �貹�˱��� add by tuql 20091009 */
	double dBzAmt;/* �貹�˽�� add by tuql 20091009 */
	int iMzNum1;/* ��Ĩ�˱��� add by tuql 20091009 */
	double dMzAmt1; /* ��Ĩ�˽�� add by tuql 20091009 */
	int iBzNum1;/* �貹�˱��� add by tuql 20091009 */
	double dBzAmt1;/* �貹�˽�� add by tuql 20091009 */
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
	char sFile[256];/*�ļ���*/
	int i=0;
	int k=0;
	int iFlag=0;
	int iSqlRet = -1;
	FILE *fp=NULL;
	CURSOR cur;
	CURSOR cur1;
	CURSOR cur2;

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("���ɶ����嵥����ʼ"),"INFO");

	/*��ȡ�������  --S*/
	COMP_PARACOUNTCHK(3)
	memset(sBuf, 0x00, sizeof(sBuf)); 
	memset(sFile, 0x00, sizeof(sFile));
	COMP_GETPARSEPARAS(1,sBuf,"�����ļ���");
	pstrcopy(sFile, sBuf, sizeof(sFile));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_GETPARSEPARAS(2,sBuf,"�������к�");
	pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(3,sBuf,"��������");
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));     

	LOG(LM_STD,Fmtmsg("�������к�[%s],��������[%s],�����ļ���[%s]",
				sPayBkCode, sChkDate, sFile),"INFO");

	iAllNum = 0;
	/* add by chenxm 20141112 DCI���칤��*/
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("��ѯ��������ͷ��ʧ��"));
		LOG(LM_STD,Fmtmsg("��ѯ��������ͷ��ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	if ( iAllNum == 0 )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("������������[%s]û�ж��˼�¼", sChkDate));
		LOG(LM_STD,Fmtmsg("������������[%s]û�ж��˼�¼", sChkDate), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;        
	}    

	/*���ļ�*/
	fp=fopen(sFile,"w");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24488, Fmtmsg("���������嵥�ļ�ʧ��"));
		LOG(LM_STD,Fmtmsg("���������嵥�ļ�ʧ��[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL; 
	}   

	fprintf(fp,"                                             �������������嵥                           \n\n");
	fprintf(fp,"                        �������кţ�%s                       �������ڣ�%s \n\n",sPayBkCode,sChkDate);
	fprintf(fp,"   ƽ̨��TIPS���������\n");
	/*modify by wangw �����ĸ��ո�   
	  fprintf(fp,"���˱�־     �տ�����к�      ��������     ���α���       ���ν��    Ĩ�˱���       Ĩ�˽��    ���˱���       ���˽��\n"); */
	fprintf(fp,"    ���˱�־       �տ�����к�  ��������  TIPS����       TIPS���  ƽ̨����       ƽ̨���  Ĩ�˱���       Ĩ�˽��  ���˱���       ���˽��\n");

	/*�����α�*/
	/*add by chenxm 20141112 DCI���칤��*/
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT DISTINCT chkaccttype,payeebankno,chkacctord,allnum,allamt \
		FROM tips_ssdzplt WHERE chkdate ='%s' AND  paybkcode = '%s' ORDER BY payeebankno,chkacctord ", \
		sChkDate, sPayBkCode);
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
		LOG(LM_STD,Fmtmsg("�����α�ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
		LOG(LM_STD,Fmtmsg("��cur_dzplt_dzqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
	  LOG(LM_STD,Fmtmsg("�����α�ʧ��"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }  */
	/*���α�*/
	/*EXEC SQL OPEN cur_dzplt_dzqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzplt_dzqd",sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
	  LOG(LM_STD,Fmtmsg("��cur_dzplt_dzqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("��cur_dzplt_dzqd�α��ȡ����ʧ��"),"ERROR");
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
		/*****begin mod by tuql 20091009 ����Ĩ���˵ı��������*****/
		iMzNum=0;
		dMzAmt=0.00;
		iBzNum=0;
		dBzAmt=0.00;
		if (sChkAcctType[0]=='0' )
		{	
			strcpy(sBuf1,"��ƽ");
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��[%s][%s][%s]",
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��[%s][%s][%s]",
							sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
				iFlag = -2;
				break;
			}
			/* modify by leejn 20150310 ������������==�Ƚ�
			if((iAllNum1+iAllNum2==iAllNum) && (dAllAmt1+dAllAmt2==dAllAmt))
			
			*/
			if((iAllNum1+iAllNum2==iAllNum) && (dAllAmt1+dAllAmt2-dAllAmt <= 0.0000001 )
				&& (dAllAmt1+dAllAmt2-dAllAmt >= -0.0000001))
			{
				strcpy(sBuf1,"��ƽ");
			}
			else
			{
				strcpy(sBuf1,"��ƽ");
			}
			/* �ȴ�tips_dzbpdj���л�ȡ��Ĩ�˱�������� add by tuql 20091022*/
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ����Ĩ�˱��������ʧ��[%s][%s][%s]",
							sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
				iFlag = -2;
				break;
			}
			/* �ٴ�tips_dzbpdj���л�ȡ�貹�˱�������� */
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ���貹�˱��������ʧ��[%s][%s][%s]",
							sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
				iFlag = -3;
				break;
			}
		}

		/*modify by wangw �����ĸ��ո� */
		fprintf(fp,"  %-14.14s  %-12.12s  %-8.8s  %8d%15.2f  %8d%15.2f  %8d%15.2f  %8d%15.2f\n",
				sBuf1,sPayeeBankNo,sChkAcctOrd,iAllNum,dAllAmt,iAllNum1+iAllNum2,dAllAmt1+dAllAmt2,iMzNum,dMzAmt,iBzNum,dBzAmt);
		/*****end mod by tuql 20091009 ����Ĩ���˵ı��������*****/
	}
	/*EXEC SQL CLOSE cur_dzplt_dzqd;*/
	DCIFreeCursor(cur);

	{
		fprintf(fp,"\n\n   ƽ̨����Ķ��������\n");
		/*modify by wangw �����ĸ��ո�   
		  fprintf(fp,"���˱�־     �տ�����к�      ��������     ���α���       ���ν��    Ĩ�˱���       Ĩ�˽��    ���˱���       ���˽��\n"); */
		fprintf(fp,"    ���˱�־       �տ�����к�  ��������  ƽ̨����       ƽ̨���  ���ı���       ���Ľ��  Ĩ�˱���       Ĩ�˽��  ���˱���       ���˽��\n");

		/*�����α�*/
		/*add by chenxm 20141112 DCI���칤��*/
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT DISTINCT chkaccttype,payeebankno,chkacctord,allnum,allamt FROM tips_ssdzplt \
			WHERE chkdate ='%s' AND  paybkcode = '%s' ORDER BY payeebankno,chkacctord ", sChkDate, sPayBkCode);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
		if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
		{
			fclose(fp);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
			LOG(LM_STD,Fmtmsg("�����α�ʧ��"), fpub_GetCompname(lXmlhandle));        
			return COMPRET_FAIL;
		}
		if (DCIExecute(cur1) == -1)
		{
			fclose(fp);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
			LOG(LM_STD,Fmtmsg("��cur_dzplt_dzqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
		  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
		  LOG(LM_STD,Fmtmsg("�����α�ʧ��"), fpub_GetCompname(lXmlhandle));        
		  return COMPRET_FAIL;
		  }*/  
		/*���α�*/
		/*EXEC SQL OPEN cur_dzplt_dzqd1;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzplt_dzqd1",sqlca.sqlcode),"ERROR");
		  if ( SQLERR )
		  {
		  fclose(fp);
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
		  LOG(LM_STD,Fmtmsg("��cur_dzplt_dzqd1�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOG(LM_STD,Fmtmsg("��cur_dzplt_dzqd1�α��ȡ����ʧ��"),"ERROR");
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
			/*****begin mod by tuql 20091009 ����Ĩ���˵ı��������*****/
			iMzNum=0;
			dMzAmt=0.00;
			iBzNum=0;
			dBzAmt=0.00;
			if (sChkAcctType[0]=='0' )
			{	
				strcpy(sBuf1,"��ƽ");
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��[%s][%s][%s]",
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("��ѯ������ϸʧ��[%s][%s][%s]",
								sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
					iFlag = -2;
					break;
				}
				/* �ȴ�tips_dzbpdj���л�ȡ��Ĩ�˱�������� add by tuql 20091022*/
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ����Ĩ�˱��������ʧ��[%s][%s][%s]",
								sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
					iFlag = -2;
					break;
				}
				/* �ٴ�tips_dzbpdj���л�ȡ�貹�˱�������� */
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ���貹�˱��������ʧ��[%s][%s][%s]",
								sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
					iFlag = -3;
					break;
				}
				if((iMzNum==0) && (iBzNum==0))
				{
					strcpy(sBuf1,"��ƽ");
				}
				else
				{
					strcpy(sBuf1,"��ƽ");
				}
			}
			/*modify by wangw �����ĸ��ո� */
			fprintf(fp,"  %-14.14s  %-12.12s  %-8.8s  %8d%15.2f  %8d%15.2f  %8d%15.2f  %8d%15.2f\n",
					sBuf1,sPayeeBankNo,sChkAcctOrd,iAllNum1+iAllNum2,dAllAmt1+dAllAmt2,iAllNum1+iAllNum2+iMzNum-iBzNum,dAllAmt1+dAllAmt2+dMzAmt-dBzAmt,iMzNum,dMzAmt,iBzNum,dBzAmt);
			/*****end mod by tuql 20091009 ����Ĩ���˵ı��������*****/
		}
		/*EXEC SQL CLOSE cur_dzplt_dzqd1;*/
		DCIFreeCursor(cur1);
	}

	/* add by tuql 20091009 */
	/*�����տ�����л���ͳ��--add by wangw 20120830 begin*/
	fprintf(fp,"\n\n\n");
	fprintf(fp,"                                             �տ�����л�������                           \n");
	/*modify by wangw ������ʽ 
	  fprintf(fp,"     �տ�����к�        ���ܱ���         ���ܽ��    Ĩ�˱���          Ĩ�˽��    ���˱���          ���˽��\n"); */
	fprintf(fp,"     �տ�����к�  ���ܱ���         ���ܽ��  Ĩ�˱���          Ĩ�˽��  ���˱���          ���˽��\n");

	/*�����α�select �ֶμ���allnum��allamt--wangw 20120906*/
	/*add by chenxm 20141112 DCI���칤��*/
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT DISTINCT payeebankno,sum(curpacknum),sum(curpackamt) FROM tips_ssdzplt \
		WHERE chkdate ='%s' AND  paybkcode = '%s' group BY payeebankno order BY payeebankno", sChkDate, sPayBkCode);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
	
	if ((cur1 = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
		LOG(LM_STD,Fmtmsg("�����α�ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur1) == -1)
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
		LOG(LM_STD,Fmtmsg("��cur_dzplt_dzqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
	  LOG(LM_STD,Fmtmsg("�����α�ʧ��"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }  */
	/*���α�*/
	/*EXEC SQL OPEN cur_dzplt1_dzqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzplt1_dzqd",sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
	  LOG(LM_STD,Fmtmsg("��cur_dzplt1_dzqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("��cur_dzplt1_dzqd�α��ȡ����ʧ��"),"ERROR");
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
		/****����Ĩ���˵ı��������*****/
		iMzNum=0;
		dMzAmt=0.00;
		iBzNum=0;
		dBzAmt=0.00;

		/* �ȴ�tips_dzbpdj���л�ȡ��Ĩ�˱�������� add by tuql 20091022*/
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ����Ĩ�˱��������ʧ��[%s][%s][%s]",
						sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
			iFlag = -2;
			break;
		}
		/* �ٴ�tips_dzbpdj���л�ȡ�貹�˱�������� */
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ���貹�˱��������ʧ��[%s][%s][%s]",
						sChkDate, sPayBkCode, sPayeeBankNo),"ERROR");
			iFlag = -3;
			break;
		}

		/*modify by wangw ������ʽ */
		fprintf(fp,"     %-12.12s  %8d %16.2f  %8d  %16.2f  %8d  %16.2f\n",
				sPayeeBankNo,iAllNum,dAllAmt,iMzNum,dMzAmt,iBzNum,dBzAmt);
		/*****end ����Ĩ���˵ı��������*****/
	}
	/*EXEC SQL CLOSE cur_dzplt1_dzqd;*/
	DCIFreeCursor(cur);
	/*�����տ�����л���ͳ��--add by wangw 20120830 end*/

	fclose(fp);

	if (iFlag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("���ɶ����嵥����ʧ��"));
		LOG(LM_STD,Fmtmsg("���ɶ����嵥����ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle, 0, Fmtmsg("���ɶ����嵥����ʧ��"));
	LOG(LM_STD,Fmtmsg("���ɶ����嵥����ɹ�"),"INFO");
	return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_GenREP_KHHQD
  �������: �����н����嵥����
  �������: 
  �����н����嵥����
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��03��05��
  �޸�����: modify by chenxm 20141111 DCI���칤��
  �޸�����: 20141220DCI���죬����
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_GenREP_KHHQD(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDqdh[10];/*��������*/
	char sJgdh[10];/*��ѯ��������*/
	char sGyjgdh[10];/*��Ա��������*/
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
	char sFile[256];/*�ļ���*/
	int i=0;
	int k=0;
	int iFlag=0;
	int iSqlRet = -1;
	FILE *fp=NULL;
	CURSOR cur;
	CURSOR cur1;
	SDB_TIPS_SSPLKSFMX tips_ssplksfmx;

	fpub_InitSoComp(lXmlhandle);

	LOG(LM_STD,Fmtmsg("���ɿ������嵥����ʼ"),"INFO");

	COMP_PARACOUNTCHK(4)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sFile, 0x00, sizeof(sFile));
	COMP_GETPARSEPARAS(1,sBuf,"�����ļ���");
	pstrcopy(sFile, sBuf, sizeof(sFile));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDqdh, 0x00, sizeof(sDqdh));
	COMP_GETPARSEPARAS(2,sBuf,"��������");
	pstrcopy(sDqdh, sBuf, sizeof(sDqdh));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sJgdh, 0x00, sizeof(sJgdh));
	COMP_GETPARSEPARAS(3,sBuf,"��������"); 
	pstrcopy(sJgdh, sBuf, sizeof(sJgdh));
	trim(sJgdh);

	memset(sBuf, 0x00, sizeof(sBuf)); 
	memset(sZwrq, 0x00, sizeof(sZwrq));   
	COMP_GETPARSEPARAS(4,sBuf,"��������");
	pstrcopy(sZwrq, sBuf, sizeof(sZwrq));

	LOG(LM_STD,Fmtmsg("��������[%s],��������[%s],��������[%s],�����ļ���[%s]",
				sZwrq, sDqdh, sJgdh, sFile),fpub_GetCompname(lXmlhandle));

	/*ȡ��Ա��������*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/pub/jgdh", sBuf)
		pstrcopy(sGyjgdh, sBuf, sizeof(sGyjgdh));
	trim(sGyjgdh);

	/*ȡ��Ա���������ϼ�����--add by wangw 20120911*/
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("��ѯ������ˮ��ʧ��"));
		LOG(LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	if ( iCount == 0 )
	{ 
		/*modify by wangw 20120809 ����������ϸ�ж� Begin */
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("��ѯ������ϸ��ʧ��"));
			LOG(LM_STD,Fmtmsg("��ѯ������ϸ��ʧ��"), fpub_GetCompname(lXmlhandle));        
			return COMPRET_FAIL;
		}
		if ( iCount == 0 )
		{
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
			fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�������޴˱�������"));
			LOG(LM_STD,Fmtmsg("�������޴˱�������[%d]", iCount), fpub_GetCompname(lXmlhandle));        
			return COMPRET_FAIL;  
		}      
		/*modify by wangw 20120809 ����������ϸ�ж� End */
	}    

	/*���ļ�*/
	fp=fopen(sFile,"w");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24492, Fmtmsg("�����������嵥����ʧ��"));
		LOG(LM_STD,Fmtmsg("�����������嵥����ʧ��[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL; 
	}  

	fprintf(fp,"                      ����������˰���(������)                    \n");
	fprintf(fp,"                                         �������ڣ�%s\n",sZwrq);
	fprintf(fp,"���Ŀ�������        �ɿ��˺�           �ɿλ����                            ���   �ɿ�����    ���ջ��ش���              ������ˮ��\n");

	/*�����α�*/
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

	/*add by chenxm 20141111 DCI���칤��*/
	/*if ( SQLERR )*/
	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
		LOG(LM_STD,Fmtmsg("����cur_drls_khhqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	/*���α�*/
	/*EXEC SQL OPEN cur_drls_khhqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_drls_khhqd",sqlca.sqlcode),"ERROR");*/
	if (DCIExecute(cur) == -1)
		/*if ( SQLERR )*/
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
		LOG(LM_STD,Fmtmsg("��cur_drls_khhqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("��cur_drls_khhqd�α��ȡ����ʧ��"),"ERROR");
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
			strcpy(sBuf,"ʵʱ�ۿ�"); 
		}else
		{ 
			strcpy(sBuf,"���ж˿ۿ�"); 
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
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("���ɿ������嵥����ʧ��"));
		LOG(LM_STD,Fmtmsg("���ɿ������嵥����ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	/*�����α�*/
	memset(sSql, 0x00, sizeof(sSql));
	memset(sBuf, 0x00, sizeof(sBuf));
	strcpy(sBuf,"�����ۿ�"); 
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
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
		LOG(LM_STD,Fmtmsg("����cur_drls_khhqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}	
	/*declare*/
	/*EXEC SQL DECLARE cur_plksfmx_khhqd CURSOR for sql_qrykhhmxdq;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERR");*/

	/*���α�*/
	/*EXEC SQL OPEN cur_plksfmx_khhqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_plksfmx_khhqd",sqlca.sqlcode),"ERROR");*/
	if (DCIExecute(cur1) == -1)
		/*if ( SQLERR )*/
	{
		fclose(fp);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
		LOG(LM_STD,Fmtmsg("��cur_plksfmx_khhqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOG(LM_STD,Fmtmsg("��cur_plksfmx_khhqd�α��ȡ����ʧ��"),"ERROR");
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
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("���ɿ������嵥����ʧ��"));
		LOG(LM_STD,Fmtmsg("���ɿ������嵥����ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle, 0, Fmtmsg("���ɿ������嵥����ɹ�"));
	LOG(LM_STD,Fmtmsg("���ɿ������嵥����ɹ�"),"INFO");
	return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_GenREP_FKHQD
  �������: ���ɸ������嵥����
  �������: 
  �����н����嵥����
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��03��05��
  �޸�����: 20141111 modify by chenxm DCI���칤��
  �޸�����: 20141220DCI���죬����
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_GenREP_FKHQD(HXMLTREE lXmlhandle)
{
	int iParas ;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sPayBkCode[12+1];
	char sChkDate[8+1];/*�����кš���������*/
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
	char sFile[256];/*�ļ���*/
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

	LOG(LM_STD,Fmtmsg("���ɸ������嵥����ʼ"),"INFO");

	COMP_PARACOUNTCHK(4)

  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sFile, 0x00, sizeof(sFile));
  COMP_GETPARSEPARAS(1,sBuf,"�������嵥����");
  pstrcopy(sFile, sBuf, sizeof(sFile));
  
  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
  COMP_GETPARSEPARAS(2,sBuf,"�������к�");
  pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
  
  /* ԭ��Ʒ����� mod by  leejn 20141220
  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sChkDate, 0x00, sizeof(sChkDate));
  COMP_GETPARSEPARAS(3,sBuf,"��������");
  pstrcopy(sChkDate, sBuf, sizeof(sChkDate));     

  memset(sBegDate, 0x00, sizeof(sBegDate));
  memset(sEndDate, 0x00, sizeof(sEndDate));
  sprintf(sBegDate, "%-6.6s01", sChkDate);
  sprintf(sEndDate, "%-6.6s31", sChkDate);  
  
  LOG(LM_STD,Fmtmsg("�������к�[%s], ��������[%s],����[%s]", 
        sPayBkCode, sChkDate, sFile),fpub_GetCompname(lXmlhandle));
  */   
     
  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sBegDate, 0x00, sizeof(sBegDate));
  COMP_GETPARSEPARAS(3,sBuf,"��ѯ��ʼ����");
  pstrcopy(sBegDate, sBuf, sizeof(sBegDate));     

  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sEndDate, 0x00, sizeof(sEndDate));
  COMP_GETPARSEPARAS(4,sBuf,"��ѯ��������");
  pstrcopy(sEndDate, sBuf, sizeof(sEndDate));     

  memset(sBuf, 0x00, sizeof(sBuf));
  memset(sBankno, 0x00, sizeof(sBankno));
  COMP_SOFTGETXML("/tips/org", sBuf)
  pstrcopy(sBankno, sBuf, sizeof(sBankno));     

  LOG(LM_STD,Fmtmsg("�������к�[%s], ��������[%s]-[%s],����[%s]", 
        sPayBkCode, sBegDate,sEndDate, sFile),fpub_GetCompname(lXmlhandle));

	iTmpNum = 0;
	iAllNum1 = 0 ; 
	memset(sSql1, 0x00, sizeof(sSql1));
	if(strlen(sBankno)==0)   
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_drls WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND jyzt = '0' AND msgno in ('3001','1008') AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate, sEndDate, sPayBkCode);

		/* noted by chenxm 20141111 DCI���칤��
		   EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_drls              
		   WHERE workdate >= :sBegDate       //��������/
		   AND workdate <= :sEndDate       //��������/
		   AND paybkcode = :sPayBkCode //�����к�/
		   AND jyzt = '0'
		   AND msgno in ('3001','1008')
		   AND qsbz='0'
		   AND substr(dzbz,2,1)='1';*/	
	}
	else
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_drls WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND bankno = '%s' AND jyzt = '0' AND msgno in ('3001','1008') AND qsbz='0' AND substr(dzbz,2,1)='1'", sBegDate, sEndDate, sPayBkCode, sBankno);

		/* noted by chenxm 20141111 DCI���칤��
		   EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_drls              
		   WHERE workdate >= :sBegDate       //��������/
		   AND workdate <= :sEndDate       //��������/
		   AND paybkcode = :sPayBkCode //�����к�/
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("��ѯ���ʧ��"));
		LOG(LM_STD,Fmtmsg("��ѯ���ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}
	iAllNum1 = iAllNum1 + iTmpNum ;

	iTmpNum = 0;    
	memset(sSql1, 0x00, sizeof(sSql1));
	if(strlen(sBankno)==0)   
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssplksfmx WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND czbd = '7' AND qsbz='0' AND substr(kzbz,2,1) = '1'", sBegDate, sEndDate, sPayBkCode);
		
		/*noted by chenxm 20141111 DCI���칤��
		  EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_ssplksfmx              
		  WHERE workdate >= :sBegDate       ��������
		  AND workdate <= :sEndDate       ��������
		  AND paybkcode = :sPayBkCode �����к�
		  AND czbd = '7'
		  AND qsbz='0'
		  AND substr(kzbz,2,1) = '1'; */     

	}
	else
	{
		sprintf(sSql1, "SELECT COUNT(*) FROM tips_ssplksfmx WHERE workdate >= '%s' AND workdate <= '%s' AND paybkcode = '%s' "
				"AND bankno = '%s' AND czbd = '7' AND qsbz='0' AND substr(kzbz,2,1) = '1'", sBegDate, sEndDate, sPayBkCode,sBankno);

		/* noted by chenxm 20141111 DCI���칤��
		   EXEC SQL SELECT COUNT(*) INTO :iTmpNum FROM tips_ssplksfmx              
		   WHERE workdate >= :sBegDate       //��������//
		   AND workdate <= :sEndDate       //��������//
		   AND paybkcode = :sPayBkCode //�����к�//
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("��ѯ���ʧ��"));
		LOG(LM_STD,Fmtmsg("��ѯ���ʧ��"), fpub_GetCompname(lXmlhandle));        
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
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("��ѯ���ʧ��"));
	  LOG(LM_STD,Fmtmsg("��ѯ���ʧ��"), fpub_GetCompname(lXmlhandle));        
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
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("��ѯ���ʧ��"));
	  LOG(LM_STD,Fmtmsg("��ѯ���ʧ��"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }*/

	iAllNum1 = iAllNum1 + iTmpNum ;
	if ( iAllNum1 == 0 )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�������޴˱�������"));
		LOG(LM_STD,Fmtmsg("�������޴˱�������[%s]", iAllNum1 ), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;        
	}    

	/*���ļ�*/
	fp=fopen(sFile,"w");
	if ( fp == NULL )
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24493, Fmtmsg("�����������嵥����ʧ��"));
		LOG(LM_STD,Fmtmsg("�����������嵥����ʧ��[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL; 
	}    

	fprintf(fp,"                                             ��������ҵ��ͳ�Ʊ��� \n");
	fprintf(fp,"                                                     �������кţ�%s   ͳ�����ڣ�%s -- %s \n",sPayBkCode,sBegDate,sEndDate);
	/*modify by wangw ȥ����������*/   
	fprintf(fp,"    ��������  ��������    �ܱ���        �ܽ��   ʵ�۱���        ���     ���۱���        ���      ���ɱ���      ���\n");


	/*�����α�--modify by wangw 20120913 ���ݻ����Ͷ������λ���*/
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

		/*note by chenxm 20141111 DCI���칤��
		  EXEC SQL DECLARE cur_qshqd CURSOR for 
		  ( SELECT jgdh,chkacctord FROM tips_drls              
		  WHERE workdate >= :sBegDate       //��������//
		  AND workdate <= :sEndDate       //��������//
		  AND paybkcode = :sPayBkCode //�����к�//
		  AND jyzt = '0'
		  AND msgno in ('3001','1008')
		  AND qsbz='0'
		  AND substr(dzbz,2,1)='1'
		  )
		  union
		  ( SELECT jgdh,chkacctord FROM tips_ssplksfmx              
		  WHERE workdate >= :sBegDate       //��������//
		  AND workdate <= :sEndDate       //��������//
		  AND paybkcode = :sPayBkCode //�����к�//
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

		/* note by chenxm 20141111 DCI���칤��
		   EXEC SQL DECLARE cur_qshqd CURSOR for   
		   ( SELECT jgdh,chkacctord FROM tips_drls              
		   WHERE workdate >= :sBegDate       //��������//
		   AND workdate <= :sEndDate       //��������//
		   AND paybkcode = :sPayBkCode //�����к�//
		   AND jyzt = '0'
		   AND msgno in ('3001','1008')
		   AND bankno = :sBankno
		   AND qsbz='0'
		   AND substr(dzbz,2,1)='1'
		   )
		   union
		   ( SELECT jgdh,chkacctord FROM tips_ssplksfmx              
		   WHERE workdate >= :sBegDate       //��������//
		   AND workdate <= :sEndDate       //��������//
		   AND paybkcode = :sPayBkCode //�����к�//
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
	  noted by chenxm 20141111 DCI���칤��
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24489, Fmtmsg("�����α�ʧ��"));
	  LOG(LM_STD,Fmtmsg("����cur_qshqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  }  */
	/*���α�*/
	/*EXEC SQL OPEN cur_qshqd;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_qshqd",sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fclose(fp);
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
	  fpub_SetMsg(lXmlhandle, 24490, Fmtmsg("���α�ʧ��"));
	  LOG(LM_STD,Fmtmsg("��cur_qshqd�α�ʧ��"), fpub_GetCompname(lXmlhandle));        
	  return COMPRET_FAIL;
	  } */
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		fclose(fp);
		LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
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
		  LOG(LM_STD,Fmtmsg("��cur_qshqd�α��ȡ����ʧ��"),"ERROR");
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
		/*ͳ�Ƹû���ʵ�۽���*/
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
			
			/*noted by chenxm 20141111 DCI���칤��
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
				INTO :iTmpNum,:dTmpAmt
				FROM tips_drls
				WHERE workdate >= :sBegDate       //��������//
				AND workdate <= :sEndDate       //��������//
				AND paybkcode = :sPayBkCode //�����к�//
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
			/*noted by chenxm 20141111 DCI���칤��
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
				INTO :iTmpNum,:dTmpAmt
				FROM tips_drls
				WHERE workdate >= :sBegDate       ��������
				AND workdate <= :sEndDate       ��������
				AND paybkcode = :sPayBkCode �����к�
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag = -3;
			break;
		}  
		if (iTmpNum==0)
		{
			dTmpAmt = 0.00;
		}
		iAllNum1 = iAllNum1 + iTmpNum;
		dAllAmt1 = dAllAmt1 + dTmpAmt;   

		/*ͳ�Ƹû������ж˽ɿ��*/
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
			/*noted by chenxm 20141111 DCI���칤��
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
			INTO :iTmpNum,:dTmpAmt
			FROM tips_drls
			WHERE workdate >= :sBegDate       //��������//
			AND workdate <= :sEndDate       //��������//
			AND paybkcode = :sPayBkCode //�����к�//
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
			/* noted by chenxm 20141111 DCI���칤��
			   EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
			INTO :iTmpNum,:dTmpAmt
			FROM tips_drls
			WHERE workdate >= :sBegDate       //��������//
			AND workdate <= :sEndDate       //��������//
			AND paybkcode = :sPayBkCode //�����к�//
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag = -5;
			break;
		}  
		if (iTmpNum==0)
		{
			dTmpAmt = 0.00;
		}
		iAllNum2 = iAllNum2 + iTmpNum;
		dAllAmt2 = dAllAmt2 + dTmpAmt;


		/*ͳ�Ƹû������۽���*/
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
			/* noted by chenxm 20141111 DCI���칤��
			   EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
				INTO :iTmpNum,:dTmpAmt
				FROM tips_ssplksfmx
				WHERE workdate >= :sBegDate       //��������//
				AND workdate <= :sEndDate       //��������//
				AND paybkcode = :sPayBkCode //�����к�//
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
			/*noted by chenxm 20141111 DCI���칤��
			  EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00)
			INTO :iTmpNum,:dTmpAmt
			FROM tips_ssplksfmx
			WHERE workdate >= :sBegDate       //��������//
			AND workdate <= :sEndDate       //��������//
			AND paybkcode = :sPayBkCode //�����к�//
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

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
		/*ɾ����Ч���ݣ����ܱ���=0ʱ����ӡ--modify by wangw 20120913*/
		if(iSumNum == 0)
			continue;
		fprintf(fp,"    %-8.8s  %8s  %8d    %12.2f %8d    %12.2f %8d    %12.2f%8d    %12.2f \n",
				str_Jgdh,sDzpc,iSumNum,dSumAmt,iAllNum1,dAllAmt1,iAllNum3,dAllAmt3,iAllNum2,dAllAmt2);  /*modify by wangw ȥ����������*/    
	}    
	//EXEC SQL CLOSE cur_qshqd;
	DCIFreeCursor(cur);

	fprintf(fp,"\n\n\n\n    ���ܣ�\n");
	fprintf(fp,"    �ܽ�%12.2f              �ܱ�����%d\n",nSumAmt,nSumNum);

	fclose(fp);

	if (iFlag < 0)
	{
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
		fpub_SetMsg(lXmlhandle, 24491, Fmtmsg("���ɸ������嵥����ʧ��"));
		LOG(LM_STD,Fmtmsg("���ɸ������嵥����ʧ��"), fpub_GetCompname(lXmlhandle));        
		return COMPRET_FAIL;
	}

	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle, 0, Fmtmsg("���ɸ������嵥����ɹ�"));
	LOG(LM_STD,Fmtmsg("���ɸ������嵥����ɹ�"),"INFO");
	return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_QryDZBPMX
  �������: ��ѯ���˲�ƽ��ϸ

  �������: 
  ��ѯ���˲�ƽ��ϸ
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����
  ���˲�ƽ�ǼǱ�	tips_dzbpdj

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��05��15��
  �޸�����: 20141105 modify by chenxm DCI���칤��(done)
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_QryDZBPMX(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	SDB_TIPS_DZBPDJ stDzbpdj;
	char sChkDate[8+1];/* �������� */
	char sChkAcctOrd[4+1];/* �������� */
	char sDzlx[1+1];/* �������� */
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
	COMP_GETPARSEPARAS(1,sBuf,"��������"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"��������"); 
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));    
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzlx, 0x00, sizeof(sDzlx));
	COMP_GETPARSEPARAS(3,sBuf,"��������"); 
	sDzlx[0] = sBuf[0];
	memset(sDzbpFile, 0x00, sizeof(sDzbpFile));
	COMP_GETPARSEPARAS(4,sDzbpFile,"�����ļ���"); 
	trim(sDzbpFile);

	LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ��ϸִ�п�ʼ,��������[%s],��������[%s],��������[%s]",
				sChkDate, sChkAcctOrd, sDzlx),fpub_GetCompname(lXmlhandle))       

		memset(sSysDate, 0x00, sizeof(sSysDate));
	COMP_SOFTGETXML("/sys/sysdate", sSysDate)

		memset(sSql, 0x00, sizeof(sSql));
	if ( sDzlx[0] == '1')/* ���������� */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and dzlx = '%s' order by taxorgcode", 
				sChkDate, sDzlx);
	}else /* ���ж��� */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and chkacctord = '%s' and dzlx = '%s' order by taxorgcode", 
				sChkDate, sChkAcctOrd, sDzlx);        
	}        
	/*prepare*/
	//add by chenxm 20141105 DCI���칤��
	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
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
	  fpub_SetMsg(lXmlhandle,24409, "���α�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX��cur_dzbpdj_cxmx�α�ʧ��"),
	  fpub_GetCompname(lXmlhandle))
	  }*/

	fp=fopen(sDzbpFile,"w");
	if ( fp == NULL )
	{
		//EXEC SQL CLOSE cur_dzbpdj_cxmx;
		DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("�򿪶��˲�ƽ��ϸ�ļ�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX�򿪶��˲�ƽ��ϸ�ļ�ʧ��[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	fprintf(fp,"                             %s\n", "���˲�ƽ��ϸ����");
	fprintf(fp,"    ��������:%s %s                                 ��������:%s\n", 
			sChkDate, sChkAcctOrd,sSysDate);
	fprintf(fp,"��־  ���ջ��ش���  ί������  ������ˮ��        ���        �����˺�  \n", sChkDate, sSysDate);
	/*��ʼѭ��*/
	for (i=1,iFlag=0;;i++)
	{
		memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));        
		//EXEC SQL FETCH cur_dzbpdj_cxmx INTO :stDzbpdj;
		//SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_dzbpdj_cxmx",sqlca.sqlcode),"ERROR");
		iSqlRet = DBFetch(cur, SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ),&stDzbpdj,sErrmsg);
		//if ( SQLERR )
		if(iSqlRet < 0)
		{  
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-1;
			LOG(LM_STD,Fmtmsg("ChkYHJKXX��cur_dzbpdj_cxmx�α��ȡ����ʧ��"),"ERROR");
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
		fpub_SetMsg(lXmlhandle,24410, "���ɶ��˲�ƽ��ϸ����ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX���ɶ��˲�ƽ��ϸ����ʧ��"),
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_DEBUG,Fmtmsg("���ɶ��˲�ƽ��ϸ���������"), fpub_GetCompname(lXmlhandle));      	 
	fpub_SetMsg(lXmlhandle, 0, "���ɶ��˲�ƽ��ϸ���������");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;            
}

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_QryDZBPMX2
  �������: ��ѯ���˲�ƽ��ϸ(ֱ�ӳ�TIPS����ļ�Ĺ�ϵ)

  �������: 
  ��ѯ���˲�ƽ��ϸ(ֱ�ӳ�TIPS����ļ�Ĺ�ϵ)
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����
  ���˲�ƽ�ǼǱ�	tips_dzbpdj

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��10��19��
  �޸�����: 20141111 modify by chenxm DCI���칤��
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_QryDZBPMX2(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	SDB_TIPS_DZBPDJ stDzbpdj;
	char sChkDate[8+1];/* �������� */
	char sChkAcctOrd[4+1];/* �������� */
	char sDzlx[1+1];/* �������� */
	char sSql[256];
	char sPayeeBankNo[12+1];/* �տ����к� */
	char sPayBkCode[12+1];/* �������к� */
	int  iAllCount;/* �ܱ��� */
	double dAllAmt;/* �ܽ�� */
	char sCnClzt[64];/* ����״̬(����) */
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
	COMP_GETPARSEPARAS(1,sBuf,"��������"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"��������"); 
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));    
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzlx, 0x00, sizeof(sDzlx));
	COMP_GETPARSEPARAS(3,sBuf,"��������"); 
	sDzlx[0] = sBuf[0];
	memset(sDzbpFile, 0x00, sizeof(sDzbpFile));
	COMP_GETPARSEPARAS(4,sDzbpFile,"�����ļ���"); 
	trim(sDzbpFile);

	LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ��ϸִ�п�ʼ,��������[%s],��������[%s],��������[%s]",
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
	if ( sDzlx[0] == '4')/* TIPS�к�����,�貹�� */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and chkacctord = '%s' and paybkcode = '%s' and payeebankno = '%s' and dzjg in ('29', '93') order by taxorgcode, entrustdate,trano", 
				sChkDate, sChkAcctOrd, sPayBkCode, sPayeeBankNo);
		strcpy(sCnDzlx, "TIPS�к�����,�貹��");
	}else if ( sDzlx[0] == '5')/* TIPS�޺�����,��Ĩ�� */
	{
		snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and paybkcode = '%s' and payeebankno = '%s' and dzjg in ('39', '92', '12') order by taxorgcode, entrustdate,trano", 
				sChkDate, sPayBkCode, sPayeeBankNo); 
		strcpy(sCnDzlx, "TIPS�޺�����,��Ĩ��");          
	}else
	{
		LOG(LM_STD,Fmtmsg("��������[%s]����,��ȷ��!", sDzlx),fpub_GetCompname(lXmlhandle));
	}            
	trim(sSql);
	trim(sCnDzlx);
	LOG(LM_STD,Fmtmsg("���˲�ƽ��ϸ��ѯSQL:[%s]", sSql),fpub_GetCompname(lXmlhandle));
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
	  fpub_SetMsg(lXmlhandle,24409, "���α�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX��cur_dzbpdj_cxmx�α�ʧ��"),
	  fpub_GetCompname(lXmlhandle))
	  }*/

	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
	}	

	fp=fopen(sDzbpFile,"w");
	if ( fp == NULL )
	{
		/*EXEC SQL CLOSE cur_dzbpdj_cxmx2;*/
		DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("�򿪶��˲�ƽ��ϸ�ļ�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX�򿪶��˲�ƽ��ϸ�ļ�ʧ��[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	fprintf(fp,"                             %s(%s)\n", "���˲�ƽ��ϸ����", sCnDzlx);
	fprintf(fp,"TIPS����:%s %s                                 ���ɱ���ϵͳ����:%s\n", sChkDate,sChkAcctOrd,sSysDate);
	fprintf(fp,"���ջ��ش���  ί������  ������ˮ��  ҵ������  �ۿ�����  ������ˮ��       ���       �����˺�               ��  ��               ����״̬  \n");    
	/*��ʼѭ��*/
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-1;
			LOG(LM_STD,Fmtmsg("ChkYHJKXX��cur_dzbpdj_cxmx2�α��ȡ����ʧ��"),"ERROR");
			break;
		}
		/*f ( SQLNOTFOUND )*/
		if(iSqlRet == 0)
			break;
		memset(sCnYwlx, 0x00, sizeof(sCnYwlx));
		trim(stDzbpdj.jymc);
		if(strncmp(stDzbpdj.jymc, "3001", 4)==0)
			strcpy(sCnYwlx, "ʵ��");
		else  if(strncmp(stDzbpdj.jymc, "1008", 4)==0)
			strcpy(sCnYwlx, "����");
		else  if(strncmp(stDzbpdj.jymc, "3102", 4)==0)      
			strcpy(sCnYwlx, "����");

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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-2;
			LOG(LM_STD,Fmtmsg("��ѯ���ʵǼǱ�����Ĵ���״̬ʧ��"),"ERROR");
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
	fprintf(fp,"�ܱ���:%d             �ܽ��:%.2f", iAllCount, dAllAmt);
	fclose(fp);

	if (iFlag < 0)
	{
		fpub_SetMsg(lXmlhandle,24410, "���ɶ��˲�ƽ��ϸ����ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ChkYHJKXX���ɶ��˲�ƽ��ϸ����ʧ��"),
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_DEBUG,Fmtmsg("���ɶ��˲�ƽ��ϸ���������"), fpub_GetCompname(lXmlhandle));      	 
	fpub_SetMsg(lXmlhandle, 0, "���ɶ��˲�ƽ��ϸ���������");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;            
}
/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_QryDZBPMX2x
  �������: ��ѯ���˲�ƽ��ϸ(ֱ�ӳ�TIPS����ļ�Ĺ�ϵ,����������������)

  �������: 
  ��ѯ���˲�ƽ��ϸ(ֱ�ӳ�TIPS����ļ�Ĺ�ϵ,����������������)
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����
  ���˲�ƽ�ǼǱ�	tips_dzbpdj

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��10��22��
  �޸�����: 20141111 modify by chenxm DCI���칤��
  ����ʹ��ʾ��: 
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
	int  iAllCount;/* �ܱ��� */
	double dAllAmt;/* �ܽ�� */
	char sCnClzt[64];/* ����״̬(����) */
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

		fprintf(fp,"TIPS����:%s %s                                 ���ɱ���ϵͳ����:%s\n", sChkDate,sChkAcctOrd,sSysDate);        
	fprintf(fp,"�������к�:%s                                  �տ����к�:%s\n", sPayBkCode,sPayeeBankNo);
	fprintf(fp,"���ջ��ش���  ί������  ������ˮ��  ҵ������  �ۿ�����  ������ˮ��       ���       �����˺�               ��  ��               ����״̬  \n");                

	memset(sSql, 0x00, sizeof(sSql));
	snprintf(sSql, sizeof(sSql), " select * from tips_dzbpdj where chkdate = '%s' and paybkcode = '%s' and payeebankno = '%s' and dzjg in %s order by taxorgcode, entrustdate,trano", 
			sChkDate, sPayBkCode, sPayeeBankNo, sDzjg);            
	trim(sSql);
	LOG(LM_STD,Fmtmsg("���˲�ƽ��ϸ��ѯSQL:[%s]", sSql),"prv_tips_qryDZBPMX2x");

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
	  LOG(LM_STD,Fmtmsg("��cur_dzbpdj_cxmx2x�α�ʧ��-2"), "prv_tips_qryDZBPMX2x");        
	  return -2;
	  }*/

	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("���ݿ�׼���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
	}

	/*��ʼѭ��*/
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-3;
			LOG(LM_STD,Fmtmsg("��cur_dzbpdj_cxmx2x�α��ȡ����ʧ��-3"),"prv_tips_qryDZBPMX2x");
			break;
		}
		/*if ( SQLNOTFOUND )*/
		if(iSqlRet == 0)
			break;
		memset(sCnYwlx, 0x00, sizeof(sCnYwlx));
		trim(stDzbpdj.jymc);
		if(strncmp(stDzbpdj.jymc, "3001", 4)==0)
			strcpy(sCnYwlx, "ʵ��");
		else  if(strncmp(stDzbpdj.jymc, "1008", 4)==0)
			strcpy(sCnYwlx, "����");
		else  if(strncmp(stDzbpdj.jymc, "3102", 4)==0)      
			strcpy(sCnYwlx, "����");

		memset(sCnClzt, 0x00, sizeof(sCnClzt));
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "SELECT num_desc FROM  tips_codelist WHERE code_name='dzbpdj_clzt' AND num=%d", stDzbpdj.clzt);
		iSqlRet = DBSelectToVar(sErrmsg, sCnClzt, sSql1);
		/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"prv_tips_qryDZBPMX2x")*/
		if(iSqlRet < 0);
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-4;
			LOG(LM_STD,Fmtmsg("��ѯ���ʵǼǱ�����Ĵ���״̬ʧ��"),"prv_tips_qryDZBPMX2x");
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
		  LOG(LM_STD,Fmtmsg("��ѯ���ʵǼǱ�����Ĵ���״̬ʧ��"),"prv_tips_qryDZBPMX2x");
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
	fprintf(fp,"�ܱ���:%d             �ܽ��:%.2f", iAllCount, dAllAmt);

	if (iFlag < 0)
	{
		LOG(LM_STD,Fmtmsg("���ɶ��˲�ƽ��ϸ����ʧ��[%d]", iFlag), "prv_tips_qryDZBPMX2x");        
		return iFlag;
	}

	LOG(LM_DEBUG,Fmtmsg("���ɶ��˲�ƽ��ϸ�������0"), "prv_tips_qryDZBPMX2x");        
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
	char sPayeeBankNo[12+1];/* �տ����к� */
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
	  LOG(LM_STD,Fmtmsg("��cur_dzbpdj_cxgkzfh2x4�α�ʧ��-42"), "prv_tips_qryDZBPMX2xA");        
	  return -42;
	  }*/

	if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
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
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			iFlag=-43;
			LOG(LM_STD,Fmtmsg("��cur_dzbpdj_cxmx2x4�α��ȡ����ʧ��-43"),"prv_tips_qryDZBPMX2xA");
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
			LOG(LM_STD,Fmtmsg("���ɶ��˲�ƽ��ϸ����ʧ��[%d]", iFlag),"prv_tips_qryDZBPMX2xA");
			break;
		}                                              
	}

	//EXEC SQL CLOSE cur_dzbpdj_cxgkzfh2xA;
	DCIFreeCursor(cur);

	if (iFlag < 0)
	{
		LOG(LM_STD,Fmtmsg("���ɶ��˲�ƽ��ϸ����ʧ��[%d]", iFlag), "prv_tips_qryDZBPMX2xA");        
		return iFlag;
	}
	LOG(LM_DEBUG,Fmtmsg("���ɶ��˲�ƽ��ϸ�������0"), "prv_tips_qryDZBPMX2xA");
	return 0;
}

IRESULT SYW_TIPS_QryDZBPMX2x(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sChkDate[8+1];/* �������� */
	char sChkAcctOrd[4+1];/* �������� */
	char sDzlx[1+1];/* �������� */
	char sSql[256];
	char sPayeeBankNo[12+1];/* �տ����к� */
	char sPayBkCode[12+1];/* �������к� */
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
	COMP_GETPARSEPARAS(1,sBuf,"��������"); 
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
	COMP_GETPARSEPARAS(2,sBuf,"��������"); 
	pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));    
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzlx, 0x00, sizeof(sDzlx));
	COMP_GETPARSEPARAS(3,sBuf,"��������"); 
	sDzlx[0] = sBuf[0];
	memset(sDzbpFile, 0x00, sizeof(sDzbpFile));
	COMP_GETPARSEPARAS(4,sDzbpFile,"�����ļ���"); 
	trim(sDzbpFile);

	LOG(LM_STD,Fmtmsg("��ѯ���˲�ƽ��ϸִ�п�ʼ,��������[%s],��������[%s],��������[%s]",
				sChkDate, sChkAcctOrd, sDzlx),fpub_GetCompname(lXmlhandle))

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
	COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
		pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
	COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
		pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));

	LOG(LM_STD,Fmtmsg("�տ����к�[%s],�������к�[%s]",
				sPayeeBankNo, sPayBkCode),fpub_GetCompname(lXmlhandle)) 

		fp=fopen(sDzbpFile,"w");
	if ( fp == NULL )
	{       
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24408, Fmtmsg("�򿪶��˲�ƽ��ϸ�ļ�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�򿪶��˲�ƽ��ϸ�ļ�ʧ��[%s]", 
					strerror(errno)), fpub_GetCompname(lXmlhandle));
	}

	memset(sSql, 0x00, sizeof(sSql));
	memset(sCnDzlx, 0x00, sizeof(sCnDzlx));
	memset(sDzjg, 0x00, sizeof(sDzjg));
	iret = 0;

	if ( sDzlx[0] == '4')/* TIPS�к�����,�貹�� */
	{   
		strcpy(sCnDzlx, "TIPS�к�����,�貹��");
		snprintf(sDzjg, sizeof(sDzjg),"('29', '93') and chkacctord = '%s' ", sChkAcctOrd);
	}else if ( sDzlx[0] == '5')/* TIPS�޺�����,��Ĩ�� */
	{
		strcpy(sCnDzlx, "TIPS�޺�����,��Ĩ��");
		strcpy(sDzjg, "('39', '92', '12')");
	}else
	{
		LOG(LM_STD,Fmtmsg("��������[%s]����,��ȷ��!", sDzlx),fpub_GetCompname(lXmlhandle));
	}

	fprintf(fp,"                             %s(%s)\n", "���˲�ƽ��ϸ����", sCnDzlx);        
	if (sPayeeBankNo[0]=='\0')/* ����ʾ���������µ�ȫ�����������˲�ƽ��ϸ */
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
		fpub_SetMsg(lXmlhandle,24410, "���ɶ��˲�ƽ��ϸ����ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ɶ��˲�ƽ��ϸ����ʧ��[%d]",iret),
				fpub_GetCompname(lXmlhandle))
	}
	LOG(LM_DEBUG,Fmtmsg("���ɶ��˲�ƽ��ϸ���������"), fpub_GetCompname(lXmlhandle));      	 
	fpub_SetMsg(lXmlhandle, 0, "���ɶ��˲�ƽ��ϸ���������");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;            
}


/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_RZMZLJCL
  �������: ����Ĩ���߼�����
  �������̲��裺
  ����Ĩ���߼�����
  92--��TIPS����,�ҷ���
  1.3102�����ۿ��
  2.��tips.ini�ļ���[HXDZ]PLDZ��ֵ
  2.1 ==0 ��ƽ  /tips/ismz=1 �����ͺ�������Ĩ��
  2.2 !=0 �ж�  /tips/hxzjdzbzֵ
  2.2.1 ==0 δ����,����ѯtips_dzbpdj��,�����������ڡ�ǰ����ˮ�š�
  ��������Ϊ1��Ҫ���м�¼���ڣ���õ��˼�¼�Ķ��ʽ���ĵ�1λ����������
  Ҫ�Ǵ�����Ϊ5������¶��ʲ�ƽ�ǼǱ�Ĵ���״̬Ϊ5,�Ѵ���
  Ҫ�ǲ�Ϊ5,����Ϊ29-�����ԭ��ˮ״̬Ϊʧ�ܣ��������׵ǼǱ�ɹ���һ��;
  ���ʲ�ƽ�ǼǱ��и���Ϊ�Ѵ���ɹ���
  2.2.2 ==1 �����ͺ�������Ĩ��
  2.2.3 ==2 ����ԭ��ˮ״̬Ϊʧ�ܣ��������׵ǼǱ�ɹ���һ�ʣ����¶��ʲ�ƽ�ǼǱ���������¼��
  ��״̬��
  2.2.4 ==3 �����ϲ������,�ݲ�����,���˹��˲顣
  3.3001ʵʱ�ۿ��
  3.1�ж� /tips/hxzjdzbzֵ
  3.1.1 ==0 δ����,���ѯtips_dzbpdj��,����������������ۿ�

  39--������������ʣ�������
  1.3102�����ۿ�� ��ѯtips_ssplksfmx���kzbz[2],�ж���ֵ��
  1.1  ==0 δ���ʣ�����ѯtips_dzbpdj��,�����������ڡ�ǰ����ˮ�š�
  ��������Ϊ3,�õ�����״̬�����ʽ���������޴˼�¼����ñ�״̬��������������������
  �����ʽ��Ϊ92-�����ϲ������,�ñ����˹��˲飬���¶��ʲ�ƽ���¼,������
  �����ʽ��Ϊ93-����ԭ��ˮ״̬Ϊ�ɹ����������׵ǼǱ�����ϸñʵĶ�Ӧ���ٸ��´˱�
  �Ĵ�������״̬��
  1.2  ==1  ֱ�����ͺ�������Ĩ��.
  1.3  ==2  �����ϲ������,�ñ����˹��˲飬���¶��ʲ�ƽ���¼,������
  1.4  ==3  ����ԭ��ˮ״̬Ϊ�ɹ����������׵ǼǱ�����ϸñʵĶ�Ӧ���ٸ��´˱�
  �Ĵ�������״̬��
  2.3001ʵʱ�ۿ��,��������������ϡ�


  �������: �Զ�Ĩ���߼�����

  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ�

  ��־��Ϣ: 
  ��־����           ��־��

  ��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

  ��Ҫ����Ԫ��:
  Ԫ��·��          ����

  ��Ҫ�������:
  ����              ����

  ʹ������:����������������Զ�������Ĩ�˵��߼��жϴ���

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��11��03��
  �޸�����: 20141105 modify by chenxm DCI���칤��(done)
  ����ʹ��ʾ��: 
 ************************************************************************/
int prv_tips_updDzbpmx(	HXMLTREE lXmlhandle, SDB_DZBPMX stDzbpmx)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];    /* �������� */
	int  iYZhqzlsh;      /* ԭǰ����ˮ�� */
	char sClzt[1+1];     /* ����״̬ */
	char sClxx[50+1];    /* ������Ϣ */
	char sYClzt[1+1];    /* ԭ����״̬ */
	char sDzlx[1+1];     /* �������� */
	char sZwrq[8+1];     /* �������� */
	int  iClQzlsh;       /* ����ǰ����ˮ�� */
	char sSysTime[6+1];  /* ϵͳʱ�� */
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}

	if(strcmp(sDzlx,"1")==0)
	{
		// add by chenxm DCI���칤��
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
		// add by chenxm DCI���칤��
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
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��[%s][%d][%s][%s]", 
					sYZwrq, iYZhqzlsh, sDzlx, sYClzt),fpub_GetCompname(lXmlhandle))
	}    

	iSqlRet=DCICommit();
	/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
	if ( iSqlRet < 0 )
  {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
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
	char sZwrq[8+1];/* �������� */
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

	/* ��������Ķ��˲�ƽ��ϸ��¼ */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='4';
	pstrcopy(stDzbpmx.clxx, "���ʳɹ�", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='1';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9221,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��[%d]",iRet),fpub_GetCompname(lXmlhandle))                                
	}
	memset(sByzd, 0x00, sizeof(sByzd));
	snprintf(sByzd, sizeof(sByzd),"%s%08d", sZwrq, iClQzlsh);
	if (strncmp(sYMsgNo,"3102",4) == 0 )
	{
		/* ����ԭ��ˮ��ϸ��¼ */
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_ssplksfmx SET czbd='7',kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6), xyxx='�����ղ���' "
				"where zwrq ='%s' and plmxxh =%d ",sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
			
			LOGRET(-9222,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm 

		/*EXEC SQL UPDATE tips_ssplksfmx 
		  SET czbd='7',
		  kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),
		  xyxx='�����ղ���'
		  WHERE zwrq=:sYZwrq
		  AND plmxxh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9222,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
		  }    */            
		/* �����������׵ǼǱ� */
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET rzzbs=rzzbs+1,rzzje=rzzje+%0.2f, "
				"where zwrq ='%s' and pljylsh =%s ",dMzje,sYZwrq, sPljylsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9223,LM_STD,Fmtmsg("�����������׵ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
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
		  LOGRET(-9223,LM_STD,Fmtmsg("�����������׵ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
		  }*/                
	}else
	{
		/* ����ԭ��ˮ��ϸ��¼ */
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
			iClQzlsh=atoi(sBuf);

		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET jyzt='0',dzbz=substr(dzbz,1,1)||'1', entrustdate2='%s',zhqzlsh2=%d,xyxx='�����ղ���' "
				"where zwrq ='%s' and zhqzlsh =%d ",sZwrq,iClQzlsh,sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9224,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_drls 
		  SET jyzt='0',
		  dzbz=substr(dzbz,1,1)||'1',
		  entrustdate2=:sZwrq,
		  zhqzlsh2=:iClQzlsh,
		  xyxx='�����ղ���'
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9224,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))
		  } */                 
	} 

	/* ������TIPS���˲�ƽ�ǼǱ� */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='4';
	pstrcopy(stDzbpmx.clxx, "���˳ɹ�", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='3';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9225,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}                                                                                                               

	//�˴������ݿ��ύ����
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
	char sZwrq[8+1];/* �������� */
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

	/* ��������Ķ��˲�ƽ��ϸ��¼ */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "���ʳɹ�", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='1';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9221,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��[%d]",iRet),fpub_GetCompname(lXmlhandle))                                
	}
	memset(sByzd, 0x00, sizeof(sByzd));
	snprintf(sByzd, sizeof(sByzd),"%s%08d", sZwrq, iClQzlsh);
	if (strncmp(sYMsgNo,"3102",4) == 0 )
	{
		/* ����ԭ��ˮ��ϸ��¼ */
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_ssplksfmx SET czbd='4',kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6), xyxx='�����ղ���' "
				"where zwrq ='%s' and plmxxh =%d ",sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9222,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm 

		/*EXEC SQL UPDATE tips_ssplksfmx 
		  SET czbd='4',
		  kzbz=substr(kzbz,1,1)||'1'||substr(kzbz,3,6),
		  xyxx='������Ĩ��'
		  WHERE zwrq=:sYZwrq
		  AND plmxxh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9222,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
		  }  */              
		/* �����������׵ǼǱ� */
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET rzzbs=rzzbs-1,rzzje=rzzje-%0.2f "
				"where zwrq ='%s' and pljylsh =%s ",dMzje,sYZwrq, sPljylsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9223,LM_STD,Fmtmsg("�����������׵ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
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
		  LOGRET(-9223,LM_STD,Fmtmsg("�����������׵ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
		  }  */              
	}else
	{
		/* ����ԭ��ˮ��ϸ��¼ */
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML("/tips/newqzlsh", sBuf)
			iClQzlsh=atoi(sBuf);

		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET jyzt='3',dzbz=substr(dzbz,1,1)||'1', "
			"entrustdate2='%s',zhqzlsh2=%d,xyxx='�����ղ���' "
				"where zwrq ='%s' and zhqzlsh =%d ",sZwrq,iClQzlsh,sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-9224,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_drls 
		  SET jyzt='3',
		  dzbz=substr(dzbz,1,1)||'1',
		  entrustdate2=:sZwrq,
		  zhqzlsh2=:iClQzlsh,
		  xyxx='������Ĩ��'
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-9224,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))
		  } */                   
	} 

	/* ������TIPS���˲�ƽ�ǼǱ� */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "Ĩ�˳ɹ�", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='3';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9225,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��[%d]",iRet),
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
	char sZwrq[8+1];/* �������� */
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

	/* ��������Ķ��˲�ƽ��ϸ��¼ */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "���ʳɹ�", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='3';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-3931,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��[%d]",iRet),fpub_GetCompname(lXmlhandle))                                
	}
	memset(sByzd, 0x00, sizeof(sByzd));
	snprintf(sByzd, sizeof(sByzd),"%s%08d", sZwrq, iClQzlsh);
	if (strncmp(sYMsgNo,"3102",4) == 0 )
	{
		/* ����ԭ��ˮ��ϸ��¼ */
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_ssplksfmx SET czbd='7',xym='90000',"
			"kzbz='1'||substr(kzbz,2,1)||substr(kzbz,3,6), xyxx='������Ĩ�ʳɹ�' "
				"where zwrq ='%s' and plmxxh =%d ",sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-3932,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm 

		/*EXEC SQL UPDATE tips_ssplksfmx 
		  SET czbd='7',
		  xym='90000',
		  kzbz='1'||substr(kzbz,2,1)||substr(kzbz,3,6),
		  xyxx='������Ĩ�ʳɹ�'
		  WHERE zwrq=:sYZwrq
		  AND plmxxh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-3932,LM_STD,Fmtmsg("����������˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
		  } */               
		/* �����������׵ǼǱ� */
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_pljydj SET rzzbs=rzzbs+1,rzzje=rzzje+%0.2f "
				"where zwrq ='%s' and pljylsh =%s ",dMzje,sYZwrq, sPljylsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-3933,LM_STD,Fmtmsg("�����������׵ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
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
		  LOGRET(-3933,LM_STD,Fmtmsg("�����������׵ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
		  } */              
	}else
	{
		/* ����ԭ��ˮ��ϸ��¼ */
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
		sprintf(sSql1, "UPDATE tips_drls SET jyzt='0',dzbz='1'||substr(dzbz,2,1), "
			"entrustdate2='%s',zhqzlsh2=%d,xym='90000',xyxx='������Ĩ�ʳɹ�' "
				"where zwrq ='%s' and zhqzlsh =%d ",sZwrq,iClQzlsh,sYZwrq, iYQzlsh);
		iSqlRet = DCIExecuteDirect(sSql1);
		if(iSqlRet < 0)
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

			LOGRET(-3934,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))
		}
		//add end by chenxm

		/*EXEC SQL UPDATE tips_drls 
		  SET jyzt='0',
		  dzbz='1'||substr(dzbz,2,1),
		  entrustdate2=:sZwrq,
		  zhqzlsh2=:iClQzlsh,
		  xym='90000',
		  xyxx='������Ĩ�ʳɹ�'
		  WHERE zwrq=:sYZwrq
		  AND zhqzlsh=:iYQzlsh;
		  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
		  if(SQLERR)
		  {
		  LOGRET(-3934,LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))
		  } */                   
	} 

	/* ������TIPS���˲�ƽ�ǼǱ� */
	memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
	pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
	stDzbpmx.yqzlsh=iYQzlsh;
	stDzbpmx.clzt[0]='5';
	pstrcopy(stDzbpmx.clxx, "Ĩ�˳ɹ�", sizeof(stDzbpmx.clxx));
	stDzbpmx.dzlx[0]='1';
	stDzbpmx.yclzt[0]='0';
	iRet=prv_tips_updDzbpmx(lXmlhandle,stDzbpmx);
	if (iRet<0)
	{
		LOGRET(-9225,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}                                                                                                               

	return 0;

}

/* �Զ�����93 */
int prv_tips_Bz93(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* ���˽�� */
	char sYZwrq[8+1];/* ԭ�������� */
	int  iYQzlsh;/* ԭǰ����ˮ�� */
	double dMzje;/* Ĩ�˽�� */
	char sPljylsh[8+1];/* ԭ������ˮ�� */
	char sPlpch[8+1];/* ԭ�������κ� */
	int iClQzlsh;/* ����ǰ����ˮ�� */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */    
	char sIniFile[256];
	char sIsPldz[1+1];/* ���������Ƿ������� */
	int iMz=0;/* �Ƿ��貹�� */
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
			sBuf[0]='1';/* 1-�μ�(ȱʡ) */
		}
		pstrcopy(sIsPldz, sBuf, sizeof(sIsPldz));

		if ( sIsPldz[0] == '0')/* �����������������,��ʱ�����ͺ���Ĩ�� */
		{
			LOG(LM_STD,Fmtmsg("������¼XVV����TIPS��,ǰ������Ĳ�����,ȱʡ��ƽ,���Ϻ��Ĳ��˴���."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼XVV����TIPS��,ǰ������Ĳ�����,ȱʡ��ƽ,���Ϻ��Ĳ��˴���."));
			iMz=1;
			return iMz;
		}
	}

	/* �ж�ԭ��ˮ����������Ķ��˱�־ */
	switch (atoi(stMz.dzbz))
	{
		case 0 : /* �����δ����,������Ҫ�����ʲ�ƽ�ǼǱ���ȥ��һ�� */
			/* ��tips_dzbpdj���в�ѯ�Ƿ��е����ʴ���*/
			memset(sDzjg, 0x00, sizeof(sDzjg));

			//add by chenxm 20141105 DCI���칤��
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT dzjg  FROM tips_dzbpdj \
				WHERE zwrq='%s' and zhqzlsh=%d and dzlx='1' and clzt='0'",sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToVar(sErrmsg, sDzjg, sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOGRET(-921,LM_STD,Fmtmsg("��ѯ���ʲ�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(stMz.lXmlhandle))
			}
			//add end by chenxm

			/*EXEC SQL SELECT dzjg INTO :sDzjg   // note by chenxm  20141106 	DCI���칤��
			  FROM tips_dzbpdj
			  WHERE zwrq=:sYZwrq
			  AND zhqzlsh=:iYQzlsh
			  AND dzlx='1'
			  AND clzt='0';
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if(SQLERR)
			  {
			  LOGRET(-921,LM_STD,Fmtmsg("��ѯ���ʲ�ƽ�ǼǱ�ʧ��"),
			  fpub_GetCompname(stMz.lXmlhandle))
			  }*/
			//if (SQLNOTFOUND)/* ���Ҳ���,ֱ�����ͺ��Ĳ��� */
			if(iSqlRet == 0)
			{
				LOG(LM_STD,Fmtmsg("������¼XV?����TIPS��,ǰ���޵�δ����Ķ���,���Ϻ��Ĳ��˴���."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("������¼XV?����TIPS��,ǰ���޵�δ����Ķ���,���Ϻ��Ĳ��˴���."));
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
			LOG(LM_STD,Fmtmsg("������¼XV?�Ѷ���."),"INFO");
			break;                
	}/* end switch (stMz.dzbz)) */    
	return iMz;
}

/* �Զ�Ĩ��92 */
int prv_tips_Mz92(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* ���˽�� */
	char sYZwrq[8+1];/* ԭ�������� */
	int  iYQzlsh;/* ԭǰ����ˮ�� */
	double dMzje;/* Ĩ�˽�� */
	char sPljylsh[8+1];/* ԭ������ˮ�� */
	char sPlpch[8+1];/* ԭ�������κ� */
	int iClQzlsh;/* ����ǰ����ˮ�� */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */    
	char sIniFile[256];
	char sIsPldz[1+1];/* ���������Ƿ������� */
	int iMz=0;/* �Ƿ���Ĩ�� */
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
			sBuf[0]='1';/* 1-�μ�(ȱʡ) */
		}
		pstrcopy(sIsPldz, sBuf, sizeof(sIsPldz));

		if ( sIsPldz[0] == '0')/* �����������������,��ʱ�����ͺ���Ĩ�� */
		{
			LOG(LM_STD,Fmtmsg("������¼XVV����TIPS��,ǰ������Ĳ�����,ȱʡ��ƽ,���Ϻ���Ĩ�˴���."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼XVV����TIPS��,ǰ������Ĳ�����,ȱʡ��ƽ,���Ϻ���Ĩ�˴���."));
			iMz=1;
			return iMz;
		}
	}

	/* �ж�ԭ��ˮ����������Ķ��˱�־ */
	switch (atoi(stMz.dzbz))
	{
		case 0 : /* �����δ����,������Ҫ�����ʲ�ƽ�ǼǱ���ȥ��һ�� */
			/* ��tips_dzbpdj���в�ѯ�Ƿ��е����ʴ���*/
			memset(sDzjg, 0x00, sizeof(sDzjg));
			//add by chenxm 20141105 DCI���칤��
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT dzjg  FROM tips_dzbpdj \
				WHERE zwrq='%s' and zhqzlsh=%d and dzlx='1' and clzt='0'",sYZwrq,iYQzlsh);
      LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")     
			iSqlRet = DBSelectToVar(sErrmsg, sDzjg, sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOGRET(-921,LM_STD,Fmtmsg("��ѯ���ʲ�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(stMz.lXmlhandle))
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
			  LOGRET(-921,LM_STD,Fmtmsg("��ѯ���ʲ�ƽ�ǼǱ�ʧ��"),
			  fpub_GetCompname(stMz.lXmlhandle))
			  }*/
			//if (SQLNOTFOUND)/* ���Ҳ���,ֱ�����ͺ���Ĩ�� */
			if(iSqlRet == 0)
			{
				LOG(LM_STD,Fmtmsg("������¼XV?����TIPS��,ǰ���е�δ����Ķ���,���Ϻ���Ĩ�˴���."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("������¼XV?����TIPS��,ǰ���е�δ����Ķ���,���Ϻ���Ĩ�˴���."));
				iMz=1;
				return iMz;
				
			}
			trim(sDzjg);
			/* �����˽��Ϊ29-����Ķ���,�ҷ���,ֻ�轫ԭ��ˮ״̬����Ϊʧ�� */
			if (sDzjg[0]=='2')
			{
				LOG(LM_STD,Fmtmsg("������¼XVX����TIPS��,ǰ����,������,��ԭ��ˮ״̬����Ϊʧ�ܼ���."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("������¼XVX����TIPS��,ǰ����,������,��ԭ��ˮ״̬����Ϊʧ�ܼ���."));
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
			}else/* �����˽��Ϊ39-����Ķ���,������,���˴���,�˹��˲� */
			{
				/* ������TIPS���˲�ƽ�ǼǱ� */
				LOG(LM_STD,Fmtmsg("������¼����TIPS��,ǰ������Ķ��˺��Ķ�,���˴���,�˹��˲�."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("������¼����TIPS��,ǰ������Ķ��˺��Ķ�,���˴���,�˹��˲�."));
				memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
				pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
				stDzbpmx.yqzlsh=iYQzlsh;
				stDzbpmx.clzt[0]='9';
				pstrcopy(stDzbpmx.clxx, "���˴���,�˹��˲�", sizeof(stDzbpmx.clxx));
				stDzbpmx.dzlx[0]='3';
				stDzbpmx.yclzt[0]='0';
				iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
				if (iRet<0)
				{
					LOGRET(-922,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��"),
							fpub_GetCompname(stMz.lXmlhandle))                                
				}
			}
			break;
		case 1 :/* ����Ķ�ƽ */
			LOG(LM_STD,Fmtmsg("������¼����TIPS��,ǰ������Ķ�ƽ,���Ϻ���Ĩ�˴���."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼����TIPS��,ǰ������Ķ�ƽ,���Ϻ���Ĩ�˴���."));
			iMz=1;
			break;
		case 2 :/* ����Ķ���,�ҷ��� */
			LOG(LM_STD,Fmtmsg("������¼XVX����TIPS��,ǰ����,������,��ԭ��ˮ״̬����Ϊʧ�ܼ���."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼XVX����TIPS��,ǰ����,������,��ԭ��ˮ״̬����Ϊʧ�ܼ���."));
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
		case 3 :/* ����Ķ���,������ */
			/* ������TIPS���˲�ƽ�ǼǱ� */
			LOG(LM_STD,Fmtmsg("������¼����TIPS��,ǰ������Ķ��˺��Ķ�,���˴���,�˹��˲�."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼����TIPS��,ǰ������Ķ��˺��Ķ�,���˴���,�˹��˲�."));
			memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
			pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
			stDzbpmx.yqzlsh=iYQzlsh;
			stDzbpmx.clzt[0]='9';
			pstrcopy(stDzbpmx.clxx, "���˴���,�˹��˲�", sizeof(stDzbpmx.clxx));
			stDzbpmx.dzlx[0]='3';
			stDzbpmx.yclzt[0]='0';
			iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
			if (iRet<0)
			{
				LOGRET(-923,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��"),
						fpub_GetCompname(stMz.lXmlhandle))                                
			}
			break;
		default:
			break;                
	}/* end switch (stMz.dzbz)) */    
	return iMz;
}

/* �Զ�����29 */
int prv_tips_Bz29(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* ���˽�� */
	char sYZwrq[8+1];/* ԭ�������� */
	int  iYQzlsh;/* ԭǰ����ˮ�� */
	double dMzje;/* Ĩ�˽�� */
	char sPljylsh[8+1];/* ԭ������ˮ�� */
	char sPlpch[8+1];/* ԭ�������κ� */
	int iClQzlsh;/* ����ǰ����ˮ�� */
	char sChkDate[8+1];/* �������� */
	char sChkAcctOrd[4+1];/* �������� */
	char sPayBkCode[12+1];/* �������к� */
	char sPayeeBankNo[12+1];/* �տ����к� */
	//EXEC SQL END DECLARE SECTION;
	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */
	char sIniFile[256];
	char sIsPldz[1+1];/* ���������Ƿ������� */
	int iMz=0;/* �Ƿ���Ĩ�� */
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

	/* �ж�ԭ��ˮ����������Ķ��˱�־ */
	switch (atoi(stMz.dzbz))
	{
		case 1 :/* ��TIPS��ƽ */
			LOG(LM_STD,Fmtmsg("������¼���ں��Ķ�,TIPSƽ,���Ϻ���Ĩ�˴���."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼���ں��Ķ�,TIPSƽ,���Ϻ���Ĩ�˴���."));
			iMz=1;
			break;
		default:
			break;                
	}/* end switch (stmz.dzbz)) */

	return iMz;
}

/* �Զ�Ĩ��39 */
int prv_tips_Mz39(SDB_MZ stMz)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sDzjg[2+1];/* ���˽�� */
	char sYZwrq[8+1];/* ԭ�������� */
	int  iYQzlsh;/* ԭǰ����ˮ�� */
	double dMzje;/* Ĩ�˽�� */
	char sPljylsh[8+1];/* ԭ������ˮ�� */
	char sPlpch[8+1];/* ԭ�������κ� */
	int iClQzlsh;/* ����ǰ����ˮ�� */
	char sChkDate[8+1];/* �������� */
	char sChkAcctOrd[4+1];/* �������� */
	char sPayBkCode[12+1];/* �������к� */
	char sPayeeBankNo[12+1];/* �տ����к� */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char yzwrq[8+1];/* add by tuql 20091114 */
	int  yzhqzlsh;/* add by tuql 20091114 */
	char sIniFile[256];
	char sIsPldz[1+1];/* ���������Ƿ������� */
	int iMz=0;/* �Ƿ���Ĩ�� */
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

	/* �ж�ԭ��ˮ����������Ķ��˱�־ */
	switch (atoi(stMz.dzbz))
	{
		case 0 : /* ��TIPSδ����,������Ҫ�����ʲ�ƽ�ǼǱ���ȥ��һ�� */
			/* ��tips_dzbpdj���в�ѯ�Ƿ��е����ʴ���*/
			memset(sDzjg, 0x00, sizeof(sDzjg));

			//add by chenxm 20141105 DCI���칤��
			memset(sSql1, 0x00, sizeof(sSql1));
			sprintf(sSql1, "SELECT dzjg  FROM tips_dzbpdj \
				WHERE zwrq='%s' and zhqzlsh=%d and dzlx='3' and clzt='0'",sYZwrq,iYQzlsh); /* 20150602 ���� dzlx='3' */

			iSqlRet = DBSelectToVar(sErrmsg, sDzjg, sSql1);
			if(iSqlRet < 0)
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

				LOGRET(-391,LM_STD,Fmtmsg("��ѯ���ʲ�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(stMz.lXmlhandle))
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
			  LOGRET(-391,LM_STD,Fmtmsg("��ѯ���ʲ�ƽ�ǼǱ�ʧ��"),
			  fpub_GetCompname(stMz.lXmlhandle))
			  }*/

			/* ���Ҳ���,ֻ��¼�ݲ����� mod by tuql 20091214 �˴��߼��ж�������,
			   Ӧ�ٵ�tips_ssdzplt����ȥ��ѯ�ж�*/
			//if (SQLNOTFOUND)
			if(iSqlRet == 0)
			{
				/* �ȵ�tips_ssdzplt����ȥ��ѯ�˹������Ƿ��Ѷ��� */
				memset(sChkDate, 0x00, sizeof(sChkDate));
				COMP_SOFTGETXML("/tips/ylsxx/workdate", sChkDate)	/* 20150602 WORKDATE��ΪСд */
					memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
				COMP_SOFTGETXML("/tips/ylsxx/paybkcode", sPayBkCode) /* 20150602 PAYBKCODE��ΪСд */
					memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
				COMP_SOFTGETXML("/tips/ylsxx/payeebankno", sPayeeBankNo) /* 20150602 PAYEEBANKNO��ΪСд */
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

					LOGRET(-394,LM_STD,Fmtmsg("��ѯ��������ͷ��ʧ��"),
							fpub_GetCompname(stMz.lXmlhandle))
				}
				//if (SQLNOTFOUND)/* ˵����δ����TIPS���ն��� */
				if(iSqlRet == 0)
				{
					LOG(LM_STD,Fmtmsg("������¼?XV���ں��Ķ�,δ��TIPS����,�ݲ�����."),"INFO");
					LOG_TiaoZ("mz",Fmtmsg("������¼?XV���ں��Ķ�,δ��TIPS����,�ݲ�����."));
					iMz=0;
					memset(sBuf, 0x00, sizeof(sBuf));
					sBuf[0]='2';/* ?XV���,�ݲ����� */
					COMP_SOFTSETXML("/tips/ismz", sBuf)
						memset(sBuf, 0x00, sizeof(sBuf));
					snprintf(sBuf, sizeof(sBuf), "%s", "������¼?XV���ں��Ķ�,δ��TIPS����,�ݲ�����.");
					COMP_SOFTSETXML("/tips/mzinfo", sBuf)
						return iMz;                    
				}                           
				/* ����TIPS����,���Ķ�,ǰ����TIPS��ʧ��,���Ϻ���Ĩ�˴��� */
				LOG(LM_STD,Fmtmsg("������¼XXV���ں��Ķ�,ǰ����TIPS��ʧ��,���Ϻ���Ĩ�˴���."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("������¼XXV���ں��Ķ�,ǰ����TIPS��ʧ��,���Ϻ���Ĩ�˴���."));
				memset(sBuf, 0x00, sizeof(sBuf));
				sBuf[0]='4';/* XXV���,ֻ�����������ϸ״̬ */
				COMP_SOFTSETXML("/tips/ismz", sBuf)
					iMz=1;
				return iMz;
			}    
			trim(sDzjg);

			/* �����˽��Ϊ93-��TIPS����,������,ֻ�轫ԭ��ˮ״̬����Ϊ�ɹ� */
			if (sDzjg[1]=='3')
			{
				LOG(LM_STD,Fmtmsg("������¼VXV���ں��Ķ�,TIPSҲ��,�轫ԭ��ˮ״̬����Ϊ�ɹ�����."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("������¼VXV���ں��Ķ�,TIPSҲ��,�轫ԭ��ˮ״̬����Ϊ�ɹ�����."));
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
			}else/* �����˽��Ϊ92-��TIPS����,�ҷ���,���˴���,�˹��˲� */
			{
				/* ������TIPS���˲�ƽ�ǼǱ� */
				LOG(LM_STD,Fmtmsg("������¼���ں��Ķ�,TIPS��,���˴���,�˹��˲�."),"INFO");
				LOG_TiaoZ("mz",Fmtmsg("������¼���ں��Ķ�,TIPS��,���˴���,�˹��˲�."));
				memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
				pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
				stDzbpmx.yqzlsh=iYQzlsh;
				stDzbpmx.clzt[0]='9';
				pstrcopy(stDzbpmx.clxx, "���˴���,�˹��˲�", sizeof(stDzbpmx.clxx));
				stDzbpmx.dzlx[0]='1';
				stDzbpmx.yclzt[0]='0';
				iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
				if (iRet<0)
				{
					LOGRET(-392,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��"),
							fpub_GetCompname(stMz.lXmlhandle))                                
				}
			}
			break;
		case 1 :/* ��TIPS��ƽ */
			LOG(LM_STD,Fmtmsg("������¼���ں��Ķ�,TIPSƽ,���Ϻ���Ĩ�˴���."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼���ں��Ķ�,TIPSƽ,���Ϻ���Ĩ�˴���."));
			iMz=1;
			break;
		case 3 :/* ��TIPS����,�ҷ��� */
			LOG(LM_STD,Fmtmsg("������¼VXV���ں��Ķ�,TIPSҲ��,�轫ԭ��ˮ״̬����Ϊ�ɹ�����."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼VXV���ں��Ķ�,TIPSҲ��,�轫ԭ��ˮ״̬����Ϊ�ɹ�����."));
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
		case 2 :/* ��TIPS����,�ҷ��� */
			/* ������TIPS���˲�ƽ�ǼǱ� */
			LOG(LM_STD,Fmtmsg("������¼���ں��Ķ�,TIPS��,���˴���,�˹��˲�."),"INFO");
			LOG_TiaoZ("mz",Fmtmsg("������¼���ں��Ķ�,TIPS��,���˴���,�˹��˲�."));
			memset(&stDzbpmx, 0x00, sizeof(stDzbpmx));
			pstrcopy(stDzbpmx.yzwrq, sYZwrq, sizeof(stDzbpmx.yzwrq));
			stDzbpmx.yqzlsh=iYQzlsh;
			stDzbpmx.clzt[0]='9';
			pstrcopy(stDzbpmx.clxx, "���˴���,�˹��˲�", sizeof(stDzbpmx.clxx));
			stDzbpmx.dzlx[0]='1';
			stDzbpmx.yclzt[0]='0';
			iRet=prv_tips_updDzbpmx(stMz.lXmlhandle,stDzbpmx);
			if (iRet<0)
			{
				LOGRET(-393,LM_STD,Fmtmsg("���¶��ʲ�ƽ�ǼǱ�ʧ��"),
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
	char sYZwrq[8+1];    /* ԭ�������� */
	int iYQzlsh;         /* ԭǰ����ˮ�� */
	char sYMsgNo[4+1];   /* ԭ���״��� */
	char sDzlx[1+1];     /* ԭ�������� */
	char sDzjg[2+1];     /* ԭ���ʽ�� */
	char sDzjg2[2+1];    /* ���ʽ��2 */
	char sClzt[1+1];     /* ����״̬ */
	char sClxx[50+1];    /* ������Ϣ */
	char sYDzbz[8+1];    /* ԭ���ʱ�־ */
	int  iCount;         /* ��¼�� */
	//EXEC SQL END DECLARE SECTION;
	SDB_MZ  stMz;
	char sBuf[256];
	char sIniFile[256];
	char sIsPldz[1+1];/* ���������Ƿ������� */
	int iMz=0;/* �Ƿ���Ĩ�� */
	char sHxDzbz[1+1];/* ���Ķ��ʱ�־ */
	char sTiDzbz[1+1];/* ��TIPS���ʱ�־ */
	int iRet=-1;
	double dMzje;
	char sPljylsh[8+1];/* ����������ˮ�� */
	char sPlpch[8+1];/* �������κ� */

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(6)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	COMP_GETPARSEPARAS(1,sBuf,"ԭ��������");
	pstrcopy(sYZwrq, sBuf, sizeof(sYZwrq));

	memset(sBuf, 0x00, sizeof(sBuf));
	iYQzlsh=0;
	COMP_GETPARSEPARAS(2,sBuf,"ԭǰ����ˮ��");
	iYQzlsh=atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(3,sBuf,"ԭ��������");
	pstrcopy(sDzlx, sBuf, sizeof(sDzlx));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(4,sBuf,"ԭ���״���");
	pstrcopy(sYMsgNo, sBuf, sizeof(sYMsgNo));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzjg, 0x00, sizeof(sDzjg));    
	COMP_GETPARSEPARAS(5,sBuf,"���ʽ��");
	pstrcopy(sDzjg, sBuf, sizeof(sDzjg));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYDzbz, 0x00, sizeof(sYDzbz));    
	COMP_GETPARSEPARAS(6,sBuf,"���ʱ�־");
	pstrcopy(sYDzbz, sBuf, sizeof(sYDzbz));

	memset(sHxDzbz, 0x00, sizeof(sHxDzbz));
	memset(sTiDzbz, 0x00, sizeof(sTiDzbz));
	sHxDzbz[0]=sYDzbz[0];
	sTiDzbz[0]=sYDzbz[1];

	LOG(LM_STD,Fmtmsg("�Զ������߼�����...ԭ��������[%s]ԭǰ����ˮ��[%d]ԭ��������[%s]",
				sYZwrq, iYQzlsh, sDzlx),fpub_GetCompname(lXmlhandle));     
	LOG(LM_STD,Fmtmsg("ԭ���״���[%s]ԭ���ʽ��[%s]ԭ���ʱ�־[%s%s]",
				sYMsgNo, sDzjg, sHxDzbz, sTiDzbz),fpub_GetCompname(lXmlhandle)); 
	LOG_TiaoZ("mz",Fmtmsg("ԭ��������[%s]ԭǰ����ˮ��[%d]ԭ��������[%s]ԭ���״���[%s]ԭ���ʽ��[%s]ԭ���ʱ�־[%s%s]",
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
	/* ��Ϊ93--��TIPS����,TIPS�� */
	if (sDzjg[1]=='3' )
	{
		LOG(LM_STD,Fmtmsg("--------%s---------",sHxDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sHxDzbz[0];
		iRet=prv_tips_Bz93(stMz);
	}else if (sDzjg[0]=='2' )/* 29--������������ʣ�ǰ�ö� */
	{
		LOG(LM_STD,Fmtmsg("********%s*********",sTiDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sTiDzbz[0];
		iRet=prv_tips_Bz29(stMz);
	}    
	if(iRet<0)
	{
		fpub_SetMsg(lXmlhandle, 24420, "����¼����ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����¼����ʧ��[%d]",iRet),
				fpub_GetCompname(lXmlhandle))        
	}        
	fpub_SetCompStatus(lXmlhandle,iRet);
	fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "����¼Ĩ�˳ɹ�");
	return COMPRET_SUCC;
}

IRESULT SYW_TIPS_RZMZLJCL(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sYZwrq[8+1];    /* ԭ�������� */
	int iYQzlsh;         /* ԭǰ����ˮ�� */
	char sYMsgNo[4+1];   /* ԭ���״��� */
	char sDzlx[1+1];     /* ԭ�������� */
	char sDzjg[2+1];     /* ԭ���ʽ�� */
	char sDzjg2[2+1];    /* ���ʽ��2 */
	char sClzt[1+1];     /* ����״̬ */
	char sClxx[50+1];    /* ������Ϣ */
	char sYDzbz[8+1];    /* ԭ���ʱ�־ */
	int  iCount;         /* ��¼�� */
	//EXEC SQL END DECLARE SECTION;
	SDB_MZ  stMz;
	char sBuf[256];
	char sIniFile[256];
	char sIsPldz[1+1];/* ���������Ƿ������� */
	int iMz=0;/* �Ƿ���Ĩ�� */
	char sHxDzbz[1+1];/* ���Ķ��ʱ�־ */
	char sTiDzbz[1+1];/* ��TIPS���ʱ�־ */
	int iRet=-1;
	double dMzje;
	char sPljylsh[8+1];/* ����������ˮ�� */
	char sPlpch[8+1];/* �������κ� */

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(6)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYZwrq, 0x00, sizeof(sYZwrq));
	COMP_GETPARSEPARAS(1,sBuf,"ԭ��������");
	pstrcopy(sYZwrq, sBuf, sizeof(sYZwrq));

	memset(sBuf, 0x00, sizeof(sBuf));
	iYQzlsh=0;
	COMP_GETPARSEPARAS(2,sBuf,"ԭǰ����ˮ��");
	iYQzlsh=atoi(sBuf);

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(3,sBuf,"ԭ��������");
	pstrcopy(sDzlx, sBuf, sizeof(sDzlx));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYMsgNo, 0x00, sizeof(sYMsgNo));    
	COMP_GETPARSEPARAS(4,sBuf,"ԭ���״���");
	pstrcopy(sYMsgNo, sBuf, sizeof(sYMsgNo));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sDzjg, 0x00, sizeof(sDzjg));    
	COMP_GETPARSEPARAS(5,sBuf,"���ʽ��");
	pstrcopy(sDzjg, sBuf, sizeof(sDzjg));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYDzbz, 0x00, sizeof(sYDzbz));    
	COMP_GETPARSEPARAS(6,sBuf,"���ʱ�־");
	pstrcopy(sYDzbz, sBuf, sizeof(sYDzbz));

	memset(sHxDzbz, 0x00, sizeof(sHxDzbz));
	memset(sTiDzbz, 0x00, sizeof(sTiDzbz));
	sHxDzbz[0]=sYDzbz[0];
	sTiDzbz[0]=sYDzbz[1];

	LOG(LM_STD,Fmtmsg("�Զ�Ĩ���߼�����...ԭ��������[%s]ԭǰ����ˮ��[%d]ԭ��������[%s]",
				sYZwrq, iYQzlsh, sDzlx),fpub_GetCompname(lXmlhandle));     
	LOG(LM_STD,Fmtmsg("ԭ���״���[%s]ԭ���ʽ��[%s]ԭ���ʱ�־[%s%s]",
				sYMsgNo, sDzjg, sHxDzbz, sTiDzbz),fpub_GetCompname(lXmlhandle)); 
	LOG_TiaoZ("mz",Fmtmsg("ԭ��������[%s]ԭǰ����ˮ��[%d]ԭ��������[%s]ԭ���״���[%s]ԭ���ʽ��[%s]ԭ���ʱ�־[%s%s]",
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
	/* ��Ϊ92--��TIPS����,�ҷ��� */
	if (sDzjg[1]=='2' )
	{
		LOG(LM_STD,Fmtmsg("--------%s---------",sHxDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sHxDzbz[0];
		iRet=prv_tips_Mz92(stMz);
	}else if (sDzjg[0]=='3' )/* 39--������������ʣ������� */
	{
		LOG(LM_STD,Fmtmsg("********%s*********",sTiDzbz),fpub_GetCompname(lXmlhandle));
		stMz.dzbz[0]=sTiDzbz[0];
		iRet=prv_tips_Mz39(stMz);
	}    
	if(iRet<0)
	{
		fpub_SetMsg(lXmlhandle, 24420, "����¼Ĩ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����¼Ĩ��ʧ��[%d]",iRet),
				fpub_GetCompname(lXmlhandle))        
	}        
	fpub_SetCompStatus(lXmlhandle,iRet);
	fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "����¼Ĩ�˳ɹ�");
	return COMPRET_SUCC;
}
/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_TiaoZ
  �������: ��TIPS����ʱ������з��м�¼���������з�����ֱ���Զ����г���������е��� 
  ����������ʱ���ǰ���м�¼����Ϊ�쳣��Ҫ�˹�ȥ����
  �������̲��裺
  1 �ڶ��ʲ�ƽ�����ҳ����ж�������Ϊ3--������TIPS���ʡ�����״̬0--δ����ļ�¼
  ͬʱ��������������ƽ����TIPS���Բ�ƽ���Ҵ��������з�������,������Ҫ���г����ļ�¼��ϸ 
  2 �ٵ�ʵʱ��˰����ȥ����ԭ������Ϣ �ҵ�����г�������
  3 ���δ�ҵ� �ڵ�������˰����ϸ���в��Ҹý����Ƿ����,����Ҳ���г�������
  4 �����δ�ҵ� ������ѭ�����ý��в���(TIPS��,�����޼�¼)
  5 �����¶��ʲ�ƽ��״̬��ͬʱ����ԭ���׵�״̬Ϊ������״̬�������Ϣ

  �������: 

  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ�

  ��־��Ϣ: 
  ��־����           ��־��

  ��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

  ��Ҫ����Ԫ��:
  Ԫ��·��          ����

  ��Ҫ�������:
  ����              ����

  ʹ������:

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: TUQL
  ��������: 2009��10��26��
  �޸�����: 20141105 modify by chenxm  DCI���칤��
  ����ʹ��ʾ��: 
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
	char sChkDate[8+1];/*��������*/
	int iCount=0;
	char sYZwrq[8+1];/* ԭ�������� */
	int iYQzlsh;/* ԭǰ����ˮ�� */
	char sYMsgNo[4+1];/* ԭ���״��� */
	char sYDzlx[1+1];/* ԭ�������� */
	char sYDzjg[2+1];/* ԭ���˽�� */
	double dJyje;/* ���׽�� */
	char sJymc[50+1];/* �������� */
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
	//add by chenxm 20141105 DCI���칤��
	if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)	
	{
		LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}
	if (DCIExecute(cur) == -1)
	{
		LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ִ���α�ʧ��"));
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ִ���α�ʧ��"), fpub_GetCompname(lXmlhandle));
	}

	/*EXEC SQL DECLARE cur_dzbpdj_tzmz CURSOR for
	  SELECT zwrq,zhqzlsh,jymc,dzlx,jyje
	  FROM tips_dzbpdj
	  WHERE chkdate=:sChkDate  */ 				 /*��������*/
	//      AND dzjg=:sYDzjg                       /*92--TIPS��ǰ���� 39-ǰ���޺�����*/
	//	  AND clzt='0'   						 /*����״̬0-δ����*/
	//	ORDER  BY zwrq,zhqzlsh;  				 /*������������ǰ����ˮ��*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  EXEC SQL OPEN cur_dzbpdj_tzmz;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_dzbpdj_tzmz",sqlca.sqlcode),"ERROR");
	  if(SQLERR)
	  {
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��cur_dzbpdj_tzmz�α�ʧ��"),
	  fpub_GetCompname(lXmlhandle))
	  }
	 */
	/* ��ʼ��ʴ��� */
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
		  LOG(LM_STD,Fmtmsg("��cur_dzbpdj_tzmz�α��ȡ����ʧ��"),"ERROR");
		  iFlag = -1;
		  break;
		  }
		  if (SQLNOTFOUND)
		  {
		  break; 
		  }*/
		/*************���ȵ�ʵʱ��˰���л�������˰����ϸ���в��Ҹý��׼�¼�Ƿ����****************/
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
			// added by chenxm 20141104 DCI���칤��
			memset(sTemp, 0x00, sizeof(sTemp));
			sprintf(sSql1, "select count(*) from tips_drls where zwrq = '%s' and zhqzlsh =%d ",
					sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
			iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				
				iFlag = -3; 
				break; 
			}
			// add end by chenxm 

			/*EXEC SQL SELECT COUNT(*) INTO :iCount 
			  FROM tips_drls
			  WHERE  zwrq=:sYZwrq*/      /*ԭ��������*/
			//AND  zhqzlsh=:iYQzlsh; /*ԭ�ۺ�ǰ����ˮ��*/
			/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )
			  { 
			  iFlag = -3; 
			  break; 
			  } */           
		}else if (strncmp(sYMsgNo, "3102", 4) == 0)
		{
			// added by chenxm 20141104 DCI���칤��
			memset(sTemp, 0x00, sizeof(sTemp));
			sprintf(sSql1, "select count(*) from tips_ssplksfmx where zwrq = '%s' and plmxxh =%d ",
					sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
			iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				iFlag = -4; 
				break; 
			}
			// add end by chenxm

			/*EXEC SQL SELECT COUNT(*) INTO :iCount 
			  FROM tips_ssplksfmx
			  WHERE  zwrq=:sYZwrq  */    /*ԭ��������*/
			//      AND  plmxxh=:iYQzlsh;  /*ԭ�ۺ�ǰ����ˮ��*/
			/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )
			  { 
			  iFlag = -4; 
			  break; 
			  } */           
		}else
		{
			LOG(LM_STD,Fmtmsg("�ǼǵĽ�����������[%s],�����ݲ�����", sYMsgNo),"ERROR");
			LOG_TiaoZ("mz",Fmtmsg("zwrq[%s]zhqzlsh[%d]---�ǼǵĽ�����������[%s],�����ݲ�����",
						sYZwrq, iYQzlsh,sYMsgNo));
			continue;
		}

		/* �ж�ԭ��ˮ��¼�Ƿ���� */
		if (iCount!=1)
		{
			LOG(LM_STD,Fmtmsg("ԭ��ˮ������count[%d],���״���[%s],zwrq[%s],zhqzlsh[%d]", 
						iCount, sYMsgNo, sYZwrq, iYQzlsh),"ERROR");

			// added by chenxm 20141104 DCI���칤��
			memset(sTemp, 0x00, sizeof(sTemp));
			sprintf(sSql1, "UPDATE tips_dzbpdj SET clzt='6',clxx='����ʧ��,ԭ��ˮ��¼������' where zwrq = '%s' and zhqzlsh =%d ",
					sYZwrq,iYQzlsh);
			LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    	
			iSqlRet = DCIExecuteDirect(sSql1);
			if( iSqlRet < 0 )
			{
				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
				iFlag = -4; 
				break; 
			}
			// add end by chenxm

			/*EXEC SQL UPDATE tips_dzbpdj
			  SET clzt='6',
			  clxx='����ʧ��,ԭ��ˮ��¼������'
			  WHERE zwrq=:sYZwrq
			  AND zhqzlsh=:iYQzlsh;
			  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
			  if ( SQLERR )
			  { 
			  iFlag = -5; 
			  break; 
			  } */                       
			LOG_TiaoZ("mz",Fmtmsg("-->Ĩ�ʼ�¼��zwrq[%s]zhqzlsh[%d]---����ʧ��,ԭ��ˮ��¼������",
						sYZwrq, iYQzlsh));            
			continue;            
		}
		/* ��Ϊ���ж˽ɿ�,����TIPS������ִ����Ϊʵ�ۻ�����,������������������ */
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
			/* ��ʼ����Ӧ�������� */            
			if ( fpub_CallFlow(lXmlhandle,sTiaoZFlow) != MID_SYS_SUCC)
			{
				(*iMzFnum)++;
				(*dMzFje) += dJyje;
				iFlag=-6;
				LOG(LM_STD,Fmtmsg("����[%s]������ϵͳ����", sTiaoZFlow),"ERROR");
				break;
			}

		/*�ж��������Ƿ���ɹ�*/
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
		if ( sBuf[0] == '2' )  /*����2ʧ��,������Ϊ�ɹ�*/
		{
			(*iMzFnum)++;
			(*dMzFje) += dJyje;
			LOG(LM_STD,Fmtmsg("����[%s]������ϵͳʧ��", sTiaoZFlow),"ERROR");
			memset(sBuf, 0x00, sizeof(sBuf));
			COMP_SOFTGETXML(XMLNM_RESPMSG,sBuf)
				trim(sBuf);
			LOG_TiaoZ("mz",Fmtmsg("-->Ĩ�ʼ�¼��zwrq[%s]zhqzlsh[%d]---����ʧ��,%s",
						sYZwrq, iYQzlsh, sBuf));         	
			continue;
		}
		memset(sBuf, 0x00, sizeof(sBuf));
		COMP_SOFTGETXML("/tips/ismz", sBuf)
			if(sBuf[0]=='2')/* ���˽ڽ�Ϊ2,˵��δ��TIPS�����ݲ�Ĩ�� add by tuql 20091217*/
			{
				continue; 
			}
		LOG_TiaoZ("mz",Fmtmsg("-->Ĩ�ʼ�¼��zwrq[%s]zhqzlsh[%d]---���ʳɹ�",
					sYZwrq, iYQzlsh)); 
		(*iMzSnum)++;
		(*dMzSje) += dJyje;
	}           
	//EXEC SQL CLOSE cur_dzbpdj_tzmz; 
	DCIFreeCursor(cur);
	if (iFlag < 0)
	{
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����Զ�����ʧ��[%d]",iFlag),
				fpub_GetCompname(lXmlhandle))
	}    
	return 0;        
}

IRESULT SYW_TIPS_TiaoZ(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	char sChkDate[8+1];                 /*��������*/
	int iCount;                         /* �ܼ�¼�� */
	//EXEC SQL END DECLARE SECTION;
	char sSql1[1024];
	char sErrmsg[256];
	char sTemp[128];

	char sBuf[256];
	char sflow[64];
	char sSysDate[8+1];
	char sSysTime[6+1];
	char sZwrq[8+1];
	int iMzSnum = 0;                     /* Ĩ�ʳɹ����� */
	double dMzSje = 0.00;                /* Ĩ�ʳɹ���� */
	int iMzFnum = 0;                     /* Ĩ��ʧ�ܱ��� */
	double dMzFje = 0.00;                /* Ĩ��ʧ�ܽ�� */        
	int iRet=0;
	int iSqlRet = -1;

	fpub_InitSoComp(lXmlhandle);

	COMP_PARACOUNTCHK(2)

		memset(sBuf, 0x00, sizeof(sBuf));
	memset(sChkDate, 0x00, sizeof(sChkDate));
	COMP_GETPARSEPARAS(1,sBuf,"��������");
	pstrcopy(sChkDate, sBuf, sizeof(sChkDate));

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sflow, 0x00, sizeof(sflow));
	COMP_GETPARSEPARAS(2,sBuf,"���ʲ�ƽ����������");
	pstrcopy(sflow, sBuf, sizeof(sflow));

	LOG(LM_STD,Fmtmsg("�����Զ����ʿ�ʼ����...��������[%s]��������[%s]",
				sChkDate, sflow),fpub_GetCompname(lXmlhandle)); 

	iCount=0;
	//add by chenxm 20141105 DCI���칤��
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "SELECT COUNT(*) FROM tips_dzbpdj WHERE chkdate='%s' and dzjg in ('92','39') and clzt='0'",sChkDate);
	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO") 
	iSqlRet = DBSelectToVar(sErrmsg, &iCount, sSql1 );
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle,24316,"��ѯ���˲�ƽ�ǼǱ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ�ʧ��"),fpub_GetCompname(lXmlhandle))
	}
	//add end by chenxm 
	//EXEC SQL SELECT COUNT(*) INTO :iCount
	//     FROM tips_dzbpdj
	//   WHERE chkdate=:sChkDate   				 /*��������*/
	//     AND dzjg in ('92','39')                /*92--TIPS��ǰ���� 39-ǰ���޺�����*/
	//	  AND clzt='0';   						 /*����״̬0-δ����*/
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
	  if (SQLERR)
	  {
	  fpub_SetMsg(lXmlhandle,24316,"��ѯ���˲�ƽ�ǼǱ�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
	  LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ���˲�ƽ�ǼǱ�ʧ��"),
	  fpub_GetCompname(lXmlhandle))
	  }*/
	if (iCount == 0)
	{
		fpub_SetMsg(lXmlhandle,24317,"û����Ҫ���յ���(Ĩ��)�ļ�¼");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("û����Ҫ���յ���(Ĩ��)�ļ�¼"),
				fpub_GetCompname(lXmlhandle))        
	}    

	memset(sSysDate, 0x00, sizeof(sSysDate));
	COMP_SOFTGETXML("/sys/sysdate",sSysDate);
	memset(sSysTime, 0x00, sizeof(sSysTime));
	COMP_SOFTGETXML("/sys/systime",sSysTime);
	memset(sZwrq, 0x00, sizeof(sZwrq));
	COMP_SOFTGETXML("/tips/zwrq",sZwrq);        

	LOG_TiaoZ("mz",Fmtmsg("\n                                �����Զ�Ĩ�ʿ�ʼ\n"));
	LOG_TiaoZ("mz",Fmtmsg("ϵͳ����[%s]ʱ��[%s]      ǰ����������[%s]       TIPS��������[%s]",sSysDate,sSysTime, sZwrq, sChkDate));
	LOG_TiaoZ("mz",Fmtmsg("============================================================================================="));
	LOG_TiaoZ("mz",Fmtmsg("����״̬39�������࣬TIPS����״̬δ֪�������"));
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
		LOG_TiaoZ("mz",Fmtmsg("����״̬39�������࣬TIPS����״̬δ֪������ʧ��"));
		LOG_TiaoZ("mz",Fmtmsg("����Ĩ�˳ɹ�����[%d],Ĩ�˳ɹ����[%.2f]  Ĩ��ʧ�ܱ���[%d],Ĩ��ʧ�ܽ��[%.2f]\n",
					iMzSnum, dMzSje, iMzFnum, dMzFje));
		fpub_SetMsg(lXmlhandle,24313,"�����Զ�����ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����Զ�����ʧ��[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}
	LOG_TiaoZ("mz",Fmtmsg("����״̬92����������״̬δ֪��ǰ�ö࣬�����"));
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
		LOG_TiaoZ("mz",Fmtmsg("����״̬92����������״̬δ֪��ǰ�ö࣬����ʧ��"));
		LOG_TiaoZ("mz",Fmtmsg("����Ĩ�˳ɹ�����[%d],Ĩ�˳ɹ����[%.2f]  Ĩ��ʧ�ܱ���[%d],Ĩ��ʧ�ܽ��[%.2f]\n",
					iMzSnum, dMzSje, iMzFnum, dMzFje));
		fpub_SetMsg(lXmlhandle,24314,"�����Զ�����ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
		LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����Զ�����ʧ��[%d]",iRet),
				fpub_GetCompname(lXmlhandle))
	}
	LOG_TiaoZ("mz",Fmtmsg("============================================================================================="));
	LOG_TiaoZ("mz",Fmtmsg("����Ĩ�˳ɹ�����[%d],Ĩ�˳ɹ����[%.2f]  Ĩ��ʧ�ܱ���[%d],Ĩ��ʧ�ܽ��[%.2f]\n",
				iMzSnum, dMzSje, iMzFnum, dMzFje));
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,Fmtmsg("����Ĩ�˳ɹ�����[%d],Ĩ�˳ɹ����[%.2f]  Ĩ��ʧ�ܱ���[%d],Ĩ��ʧ�ܽ��[%.2f]",
				iMzSnum, dMzSje, iMzFnum, dMzFje));
	LOG(LM_STD,Fmtmsg("����Ĩ�˳ɹ�����[%d],Ĩ�˳ɹ����[%.2f]  Ĩ��ʧ�ܱ���[%d],Ĩ��ʧ�ܽ��[%.2f]",
				iMzSnum, dMzSje, iMzFnum, dMzFje), fpub_GetCompname(lXmlhandle))
		return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_XIB_HXDZZD
  �������: XIB����Ķ���(�Զ�)

  �������: 
  ����Ķ���
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: wangw
  ��������: 2012��08��07��
  �޸�����: 20141106 modify by chenxm DCI���칤��
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_XIB_HXDZZD(HXMLTREE lXmlhandle)
{
	int iParas;
	//EXEC SQL BEGIN DECLARE SECTION;
	int iCount;
	int iCount2;
	char sDzrq[8+1];/* �������� */
	char sPrevDate[8+1];/* ������ʼ�� */
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
	COMP_GETPARSEPARAS(1, sBuf, "��������")
		pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
	trim(sDzrq); 

	LOG(LM_STD,Fmtmsg("����Ķ��˿�ʼ����..."),fpub_GetCompname(lXmlhandle))  

		/*EXEC SQL BEGIN WORK; ����ʼ*/

	iRet = DCIBegin();  //add by chenxm 20141106 DCI���칤��
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}

	/*�õ�����ˮΪ����δ����״̬*/
	//add by chenxm 20141105 DCI���칤��
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1) WHERE zwrq='%s' and msgno in ('3001','1008')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1)
	  WHERE zwrq = :sDzrq
	  AND msgno in ('3001','1008');*/
	/* mod by tuql 20091112 AND jyzt = '0'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/           
	LOG(LM_STD,Fmtmsg("-----���µ�����ˮΪδ����״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*�õ���������ϸΪ����δ����״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7) WHERE zwrq='%s'",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������˰����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7)
	  WHERE zwrq = :sDzrq ;*/
	/* mod by tuql 20091112 AND czbd = '7'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������˰����ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������˰����ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����������ϸΪδ����״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*ɾ�����պ��Ķ��˲�ƽ��¼*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzbpdj WHERE zwrq='%s' and dzlx='1' and byzd in (' ','9')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "ɾ�����պ��Ķ��˲�ƽ��¼");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ�����պ��Ķ��˲�ƽ��¼"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_dzbpdj 
	  WHERE zwrq = :sDzrq and dzlx='1' and byzd in (' ','9');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "ɾ�����պ��Ķ��˲�ƽ��¼");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ�����պ��Ķ��˲�ƽ��¼"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----ɾ�����ն��˲�ƽ��¼�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*ɾ��������ˮ��������˼�¼*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_xibhxmx WHERE sprq='%s' and ztm not in ('0','1')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "ɾ��������ˮʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ��������ˮ��ʧ��"),fpub_GetCompname(lXmlhandle)) 
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_xibhxmx 
	  WHERE sprq = :sDzrq and ztm not in ('0','1'); 
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "ɾ��������ˮʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ��������ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----ɾ��������ˮ��������˼�¼�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ���ڵ�����ˮ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq='%s' and dzlsh in (select zjlsh from tips_drls where zwrq = '%s' and jyzt='0')",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_drls where zwrq = :sDzrq and jyzt='0');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����ʵʱ������ϸΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ����������ϸ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq='%s' and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = '%s' and czbd='7')",sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = :sDzrq and czbd='7');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----��������������ϸΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ˮ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='1'||substr(dzbz,2,1) WHERE zwrq='%s' and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s')",sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='1'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----���µ�����ˮΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*������ʧ����ˮ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ���Ķ�״̬--add by wangw 20120907*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='3'||substr(dzbz,2,1) WHERE zwrq='%s' and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='3'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----������ʧ����ˮ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ���Ķ�״̬------"),fpub_GetCompname(lXmlhandle))  

		/*��������ˮ��ˮ��bu�ں�����ϸ�д��ڵĸ���Ϊ���˲�ƽ״̬--20120906 ����and msgno in ('3001','1008')�����������������*/

		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='2'||substr(dzbz,2,1) WHERE zwrq='%s' and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1'", sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))  
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='2'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----���µ�����ˮΪ���˲�ƽ״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7) WHERE zwrq='%s' and czbd='7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s')", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����������ϸΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��ʧ��������ϸ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ���Ķ�״̬--add vy wangw 20120907*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7) WHERE zwrq='%s' and czbd<>'7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s')", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))     
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd<>'7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----��ʧ��������ϸ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ���Ķ�״̬------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ�Ų��ں�����ϸ�д��ڵĸ���Ϊ���˲�ƽ״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7) WHERE zwrq='%s' and czbd='7' and substr(kzbz,1,1)<>'1'", sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))     
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and substr(kzbz,1,1)<>'1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����������ϸΪ���˲�ƽ״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸδ���˵Ĳ�����˲�ƽ�ǼǱ�*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate) "
			"select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1','%s','39',' ','���Ķ�','0000','%s' "
			"from tips_xibhxmx where sprq = '%s' and dzbz <> '1'", sDzrq, sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "δ���˺�����ϸ������˲�ƽ�ǼǱ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˺�����ϸ������˲�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))            
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate)  
	  select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1',:sDzrq,'39',' ','���Ķ�','0000',:sDzrq 
	  from tips_xibhxmx 
	  where sprq = :sDzrq and dzbz <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "δ���˺�����ϸ������˲�ƽ�ǼǱ�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˺�����ϸ������˲�ƽ�ǼǱ�ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----δ���˺�����ϸ���벻ƽ��ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ˮδ���˵Ĳ�����˲�ƽ�ǼǱ�--20120906 ����and msgno in ('3001','1008')�����������������*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,'%s',payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000' "
			"from tips_drls where zwrq='%s' and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1) <> '1'", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) 
	  select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,:sDzrq,payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000'
	  from tips_drls 
	  where zwrq=:sDzrq and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1) <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----δ����ʵʱ��ˮ���벻ƽ��ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸδ���˵Ĳ�����˲�ƽ�ǼǱ�*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,'%s',payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000' "
			"from tips_ssplksfmx where zwrq='%s' and and czbd='7' and substr(kzbz,1,1) <> '1'", sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "δ����������ϸ������˲�ƽ�ǼǱ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ������ϸ��ˮ������˲�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz)  
	  select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,:sDzrq,payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000'
	  from tips_ssplksfmx 
	  where zwrq=:sDzrq and czbd='7' and substr(kzbz,1,1) <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "δ����������ϸ������˲�ƽ�ǼǱ�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ������ϸ��ˮ������˲�ƽ�ǼǱ�ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	//EXEC SQL COMMIT;  /*�ύ*/
	iSqlRet=DCICommit();
	/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
		if ( iSqlRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
   */
	LOG(LM_STD,Fmtmsg("-----δ����������ϸ���벻ƽ��ɹ�------"),fpub_GetCompname(lXmlhandle))  

		LOG(LM_DEBUG,Fmtmsg("������������˽���" ), fpub_GetCompname(lXmlhandle));
	fpub_SetMsg(lXmlhandle, 0, "������������˽���");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_XIB_HXDZSG
  �������: XIB����Ķ���(�ֹ�)

  �������: 
  ����Ķ���
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: wangw
  ��������: 2012��08��07��
  �޸�����: 20141105 DCI ���칤��
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_XIB_HXDZSG(HXMLTREE lXmlhandle)
{
	int iParas;
	/*EXEC SQL BEGIN DECLARE SECTION;*/
	int iCount;
	int iCount2;
	char sDzrq[8+1];/* �������� */
	char sPrevDate[8+1];/* ������ʼ�� */
	char sQsh[12+1];/* �����д��� */
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
	COMP_GETPARSEPARAS(1, sBuf, "��������")
		pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
	trim(sDzrq); 
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sQsh, 0x00, sizeof(sQsh));
	COMP_GETPARSEPARAS(2, sBuf, "�������к�")
		pstrcopy(sQsh, sBuf, sizeof(sQsh));
	trim(sQsh); 

	LOG(LM_STD,Fmtmsg("����Ķ��˿�ʼ����..."),fpub_GetCompname(lXmlhandle))  
		LOG(LM_STD,Fmtmsg("-----��������[%s]�������к�[%s]-----",sDzrq,sQsh),fpub_GetCompname(lXmlhandle))  

		/*EXEC SQL BEGIN WORK; *����ʼ*/
		iRet = DCIBegin();  //add by chenxm 20141106 DCI���칤��
	if( iRet < 0 )
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		return COMPRET_FAIL;
	}

	/*�õ�����ˮΪ����δ����״̬*/
	//add by chenxm 20141105 DCI���칤��
	memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1) WHERE zwrq='%s' and msgno in ('3001','1008') "
			"and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle))   
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_drls SET dzbz='0'||substr(dzbz,2,1)
	  WHERE zwrq = :sDzrq
	  AND msgno in ('3001','1008') and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	 *//* mod by tuql 20091112 AND jyzt = '0'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }     */      
	LOG(LM_STD,Fmtmsg("-----���µ�����ˮΪδ����״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*�õ���������ϸΪ����δ����״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7) WHERE zwrq='%s' "
			"and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������˰����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL UPDATE tips_ssplksfmx SET kzbz='0'||substr(kzbz,2,7)
	  WHERE zwrq = :sDzrq  and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	 *//* mod by tuql 20091112 AND czbd = '7'; */
	/*SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������˰����ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������˰����ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����������ϸΪδ����״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*ɾ�����պ��Ķ��˲�ƽ��¼*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_dzbpdj WHERE zwrq='%s' "
			"and dzlx='1' and byzd in(' ','9') and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "ɾ�����պ��Ķ��˲�ƽ��¼");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ�����պ��Ķ��˲�ƽ��¼"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_dzbpdj 
	  WHERE zwrq = :sDzrq and dzlx='1' and byzd in(' ','9') and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "ɾ�����պ��Ķ��˲�ƽ��¼");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ�����պ��Ķ��˲�ƽ��¼"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----ɾ�����պ��Ķ��˲�ƽ��¼�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*ɾ��������ˮ��������˼�¼--������״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_xibhxmx WHERE sprq = '%s' and ztm not in ('0','1')",sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "ɾ��������ˮʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ��������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_xibhxmx 
	  WHERE sprq = :sDzrq and ztm not in ('0','1') ;
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "ɾ��������ˮʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ��������ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----ɾ��������ˮ��������˼�¼�ɹ�------"),fpub_GetCompname(lXmlhandle))  
		/*ɾ��������ˮ��������˼�¼--�Ǳ�����*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "delete FROM tips_xibhxmx WHERE sprq = '%s' and jgdh not in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "ɾ��������ˮʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ��������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL delete FROM tips_xibhxmx 
	  WHERE sprq = :sDzrq and jgdh not in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "ɾ��������ˮʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ɾ��������ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----ɾ��������ˮ��������˼�¼�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ���ڵ�����ˮ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq = '%s' and dzlsh in (select zjlsh from tips_drls where zwrq = '%s' and jyzt='0' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s'))",sDzrq,sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_drls where zwrq = :sDzrq and jyzt='0' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh));
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����ʵʱ������ϸΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ����������ϸ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_xibhxmx set dzbz='1' WHERE sprq = '%s' and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = '%s' and czbd='7' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s'))",sDzrq,sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_xibhxmx set dzbz='1'
	  WHERE sprq = :sDzrq and dzlsh in (select zjlsh from tips_ssplksfmx where zwrq = :sDzrq and czbd='7' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh));
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���º�����ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���º�����ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----��������������ϸΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ˮ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='1'||substr(dzbz,2,1) WHERE zwrq = '%s' and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='1'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----���µ�����ˮΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*������ʧ����ˮ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ���Ķ�״̬--add by wangw 20120907*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='3'||substr(dzbz,2,1) WHERE zwrq = '%s' and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='3'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt<>'0' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----���µ�����ˮΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ˮ��ˮ���ں�����ϸ�в����ڵĸ���Ϊ���˲�ƽ״̬--20120906 ����and msgno in ('3001','1008')�����������������*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_drls set dzbz='2'||substr(dzbz,2,1) WHERE zwrq = '%s' and jyzt='0' "
			"and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1' and zjlsh in (select dzlsh from tips_jgdhdj where qshdm = '%s' )",sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_drls set dzbz='2'||substr(dzbz,2,1)
	  WHERE zwrq=:sDzrq and jyzt='0' and msgno in ('3001','1008') and substr(dzbz,1,1)<>'1' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "���µ�����ˮ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----���µ�����ˮΪ���˲�ƽ״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ�Ѷ���״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7) WHERE zwrq = '%s' and czbd='7' "
			"and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='1'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����������ϸΪ�Ѷ���״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��ʧ��������ϸ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ���Ķ�״̬--add by wangw 20120907*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7) WHERE zwrq = '%s' and czbd<>'7' "
			"and zjlsh in (select dzlsh from tips_xibhxmx where sprq = '%s' )",sDzrq,sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='3'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd<>'7' and zjlsh in (select dzlsh from tips_xibhxmx where sprq = :sDzrq );
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����������ϸΪ���Ķ�״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸ��ˮ���ں�����ϸ�д��ڵĸ���Ϊ���˲�ƽ״̬*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "update tips_ssplksfmx set kzbz='2'||substr(kzbz,2,7) WHERE zwrq = '%s' and czbd='7' "
			"and substr(kzbz,1,1)<>'1' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s')",sDzrq,sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		DCIRollback();
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))          
	}
	//add end by chenxm

	/*EXEC SQL update tips_ssplksfmx set kzbz='2'||substr(kzbz,2,7)
	  WHERE zwrq=:sDzrq and czbd='7' and substr(kzbz,1,1)<>'1' and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh);
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "����������ϸ��ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����������ϸ��ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----����������ϸΪ���˲�ƽ״̬�ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸδ���˵Ĳ�����˲�ƽ�ǼǱ�*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate) "
			"select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1','%s','39',' ','���Ķ�','0000','%s' "
			"from tips_xibhxmx where sprq = '%s' and dzbz <> '1'", sDzrq, sDzrq, sDzrq);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,khmc,jyzh,jyje,jgdh,zjlsh,clzt,dzlx,jyrq,dzjg,byzd,reason_info,kzbz,chkdate)  
	  select zwrq,substr(dzlsh,11,5),khmc,khzh,jyje,jgdh,dzlsh,'0','1',:sDzrq,'39',' ','���Ķ�','0000',:sDzrq 
	  from tips_xibhxmx 
	  where sprq = :sDzrq and dzbz <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "δ���˺�����ϸ������˲�ƽ�ǼǱ�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˺�����ϸ������˲�ƽ�ǼǱ�ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----δ���˺�����ϸ���벻ƽ��ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ˮδ���˵Ĳ�����˲�ƽ�ǼǱ�--20120906 ����and msgno in ('3001','1008')�����������������*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,:sDzrq,payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000' "
			"from tips_drls where zwrq='%s' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s') and jyzt='0' and substr(dzbz,1,1) <> '1' and msgno in ('3001','1008')", sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")

		fpub_SetMsg(lXmlhandle, 24422, "δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz)  
	  select zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,'1',substr(zjlsh,1,15),taxorgcode,entrustdate,trano,:sDzrq,payeebankno,paybkcode,jyrq,jysj,'3001',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000'
	  from tips_drls 
	  where zwrq=:sDzrq and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh) and jyzt='0' and substr(dzbz,1,1) <> '1' and msgno in ('3001','1008');
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ���˵�����ˮ������˲�ƽ�ǼǱ�ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	LOG(LM_STD,Fmtmsg("-----δ����ʵʱ��ˮ���벻ƽ��ɹ�------"),fpub_GetCompname(lXmlhandle))  

		/*��������ϸδ���˵Ĳ�����˲�ƽ�ǼǱ�*/
		//add by chenxm 20141105 DCI���칤��
		memset(sSql1, 0x00, sizeof(sSql1));
	sprintf(sSql1, "insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz) "
			"select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,:sDzrq,payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000' "
			"from tips_ssplksfmx where zwrq='%s' and jgdh in (select jgdh from tips_jgdhdj where qshdm='%s') and czbd='7' and substr(kzbz,1,1) <> '1'", sDzrq, sQsh);		
	iSqlRet = DCIExecuteDirect(sSql1);
	if(iSqlRet < 0)
	{
		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
		
		fpub_SetMsg(lXmlhandle, 24422, "δ����������ϸ������˲�ƽ�ǼǱ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ������ϸ��ˮ������˲�ƽ�ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))      
	}
	//add end by chenxm

	/*EXEC SQL insert into tips_dzbpdj(zwrq,zhqzlsh,workdate,dqdh,jgdh,jygy,zddh,dzlx,zjlsh,taxorgcode,entrustdate,trano,chkdate,payeebankno,paybkcode,jyrq,jysj,jymc,khmc,jyzh,jyje,dzjg,clzt,byzd,reason_info,kzbz)  
	  select zwrq,plmxxh,workdate,dqdh,jgdh,jygy,zddh,'1',zjlsh,taxorgcode,entrustdate,packno,:sDzrq,payeebankno,paybkcode,zjrq,zjsj,'3102',handorgname,payacct,jyje,'29','0',' ','ƽ̨�������','0000'
	  from tips_ssplksfmx 
	  where zwrq=:sDzrq and jgdh in (select jgdh from tips_jgdhdj where qshdm=:sQsh) and czbd='7' and substr(kzbz,1,1) <> '1';
	  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
	  if ( SQLERR )
	  {
	  fpub_SetMsg(lXmlhandle, 24422, "δ����������ϸ������˲�ƽ�ǼǱ�ʧ��");
	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	  LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("δ������ϸ��ˮ������˲�ƽ�ǼǱ�ʧ��"),
	  fpub_GetCompname(lXmlhandle))        
	  }*/
	//EXEC SQL COMMIT;  /*�����ύ*/
	iSqlRet=DCICommit();
	/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
		if ( iSqlRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */
	LOG(LM_STD,Fmtmsg("-----δ����������ϸ���벻ƽ��ɹ�------"),fpub_GetCompname(lXmlhandle))  

		LOG(LM_DEBUG,Fmtmsg("������������˽���" ), fpub_GetCompname(lXmlhandle));
	fpub_SetMsg(lXmlhandle, 0, "������������˽���");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitDZJG
�������: ���˽����Ϣ
 
�������: 
    ����Ķ���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

��Ҫ�������:
  ����              ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: leejn
��������: 2014��11��07��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitDZJG(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         int iCount;
         char sDzrq[8+1];/* �������� */         
         SDB_TIPS_DZJGXX stDzjgxx;  /*  add 20140901 */        
         /* add 20140901 */
				double dQzdamt =0.00; /*ǰ�ö��� */
				int itmpQznum = 0; /* TIPSǰ���ܱ��� */
    		double dtmpQzamt = 0.00; /* TIPSǰ���ܽ�� */
				int iZjnum = 0;   /* �����ܱ��� */
    		double dZjamt = 0.00; /* �����ܽ�� */
    		int iQznum = 0; /* TIPSǰ���ܱ��� */
    		double dQzamt = 0.00; /* TIPSǰ���ܽ�� */ 
    		int iTpnum = 0;   /* �����ܱ��� */
    		double dTpamt = 0.00; /* �����ܽ�� */   
    		
    		char cQzdamt[32+1]; /*ǰ�ö��� */
				char ctmpQznum[16+1]; /* TIPSǰ���ܱ��� */
    		char ctmpQzamt[32+1]; /* TIPSǰ���ܽ�� */
				char cZjnum[16+1];  /* �����ܱ��� */
    		char cZjamt[32+1]; /* �����ܽ�� */
    		char cQznum[16+1];/* TIPSǰ���ܱ��� */
    		char cQzamt[32+1]; /* TIPSǰ���ܽ�� */ 
    		char cTpnum[16+1];  /* �����ܱ��� */
    		char cTpamt[32+1]; /* �����ܽ�� */
    /* end add 20140901 */   
    /*EXEC SQL END   DECLARE SECTION;*/
    
    char sBuf[256];
		int i;
	
		int iFlag=0;
	
	 	char sSql1[512];  /*DCI ִ��sql��� add 20141103*/                 
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
  	int iRet=0;  
  	
  	iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}   
  	
  	fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDzrq, 0x00, sizeof(sDzrq));
    
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy(sDzrq, sBuf, sizeof(sDzrq));
    trim(sDzrq);            
       
    LOG(LM_STD,Fmtmsg("��ʼ���ɶ�����Ϣ..."),fpub_GetCompname(lXmlhandle))  
    LOG(LM_STD,Fmtmsg("��������[%s]",sDzrq),fpub_GetCompname(lXmlhandle)) 
    
    /* ���Ӷ��˽��ͳ�� add 20140901 */
    /* ��ʼ�����˽���ǼǱ� */        
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "delete FROM tips_dzjgxx WHERE dzrq='%s'",sDzrq);
    iRet = DCIExecuteDirect(sSql1);
	  if ( iRet < 0 )
	  {
	  	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")        
    	
    	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    	fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"));
    	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"), 
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
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ�����˽���ǼǱ��¼ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }
    */
        
    /* ����Ķ��˽�� */
    /* ͳ�ƺ�����ˮ�ܱ��� �ܽ�� */
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_hxdzmx \
    			where QZRQ='%s'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    	
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZjnum, &cZjamt);
    if ( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("��ѯ�������˵ǼǱ��¼ʧ��"));
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�������˵ǼǱ��¼ʧ��"), 
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
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("��ѯ�������˵ǼǱ��¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�������˵ǼǱ��¼ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }
    */
    
    /* ͳ�Ƶ�����ˮ������Ķ��˳ɹ����ܱ��� �ܽ�� */
    itmpQznum = 0;
    dtmpQzamt = 0.00;	
    
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_drls \
    			where ZWRQ='%s' and dzbz like '1_'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    	
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1��ѯ������ˮ���¼ʧ��"));
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1��ѯ������ˮ���¼ʧ��"), 
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
    		LOG(LM_STD,Fmtmsg("��������[%d][%s]",sqlca.sqlcode,sqlca.sqlerrm),fpub_GetCompname(lXmlhandle)) 
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1��ѯ������ˮ���¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1��ѯ������ˮ���¼ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
    
    itmpQznum = 0;
    dtmpQzamt = 0.00;		
    
    /* ͳ�Ƶ�����ˮ������Ķ��˳ɹ����ܱ��� �ܽ�� */
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    			where zwrq='%s' and kzbz like '1_'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    		
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1��ѯ������ˮ���¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1��ѯ������ˮ���¼ʧ��"), 
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
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1��ѯ������ˮ���¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1��ѯ������ˮ���¼ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
		
		/* ��������Ķ��˽����¼ */
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
		LOG(LM_STD,Fmtmsg("[%s][%s][%s]TIPSǰ�ñ���[%d],TIPSǰ�ý��[%f],������ϸ�ܱ���[%d],������ϸ�ܽ��[%f]",
        stDzjgxx.dzrq,stDzjgxx.dzxt,stDzjgxx.dzjg,iQznum,dQzamt,iZjnum,dZjamt), fpub_GetCompname(lXmlhandle));    
    
    /* �ǼǺ��Ķ��˽�� */
    /* add dci 20141103 */
    iRet = DBInsert("tips_dzjgxx", SD_TIPS_DZJGXX, NUMELE(SD_TIPS_DZJGXX), &stDzjgxx, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetMsg(lXmlhandle, 24358, "�ǼǺ��Ķ�����Ϣʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD,Fmtmsg("�ǼǺ��Ķ�����Ϣʧ��,��������[%s],����ϵͳ[%s]", 
            stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ǼǺ��Ķ�����Ϣʧ��"), 
                    fpub_GetCompname(lXmlhandle))
    }
    /* end add dci */
    
    /* mod dci 20141103    
    EXEC SQL INSERT INTO tips_dzjgxx values(:stDzjgxx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
         
         fpub_SetMsg(lXmlhandle, 24358, "�ǼǺ��Ķ�����Ϣʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("�ǼǺ��Ķ�����Ϣʧ��,��������[%s],����ϵͳ[%s]", 
               stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ǼǺ��Ķ�����Ϣʧ��"), 
                    fpub_GetCompname(lXmlhandle))
         
    }    
    LOG(LM_STD,Fmtmsg("[%s][%s][%s]TIPSǰ�ñ���[%d],TIPSǰ�ý��[%f],������ϸ�ܱ���[%d],������ϸ�ܽ��[%f]",
        stDzjgxx.dzrq,stDzjgxx.dzxt,stDzjgxx.dzjg,iQznum,dQzamt,iZjnum,dZjamt), fpub_GetCompname(lXmlhandle));    
    */
        
    /* ��TIPS���˽�� */
    /* ͳ��TIPS������ˮ���ܱ��� �ܽ�� */
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
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("��ѯTIPS���˵ǼǱ��¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯTIPS���˵ǼǱ��¼ʧ��"), 
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
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("��ѯTIPS���˵ǼǱ��¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯTIPS���˵ǼǱ��¼ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }
    */
    
    /* ͳ�Ƶ�����ˮ������Ķ��˳ɹ����ܱ��� �ܽ�� */
    itmpQznum = 0;
    dtmpQzamt = 0.00;	
		
		/* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_drls \
    			where ZWRQ='%s' and dzbz like '_1'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    	
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1��ѯ������ˮ���¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1��ѯ������ˮ���¼ʧ��"), 
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
    		LOG(LM_STD,Fmtmsg("��������[%d][%s]",sqlca.sqlcode,sqlca.sqlerrm),fpub_GetCompname(lXmlhandle)) 
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("2��ѯ������ˮ���¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("2��ѯ������ˮ���¼ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
    
    itmpQznum = 0;
    dtmpQzamt = 0.00;	
    
    /* ͳ�Ƶ�����ˮ������Ķ��˳ɹ����ܱ��� �ܽ�� */
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    			where zwrq='%s' and kzbz like '_1'",sDzrq); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    		
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&ctmpQznum, &ctmpQzamt);
    if ( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("1��ѯ������ˮ���¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1��ѯ������ˮ���¼ʧ��"), 
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
        fpub_SetMsg(lXmlhandle, 24363, Fmtmsg("2��ѯ������ˮ���¼ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("2��ѯ������ˮ���¼ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }	
    */
    
    iQznum += itmpQznum;
    dQzamt += dtmpQzamt;
		
		/* ������TIPS���˽����¼ */
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
		LOG(LM_STD,Fmtmsg("[%s][%s][%s]TIPSǰ�ñ���[%d],TIPSǰ�ý��[%f],TIPS��ϸ�ܱ���[%d],TIPS��ϸ�ܽ��[%f]",
        stDzjgxx.dzrq,stDzjgxx.dzxt,stDzjgxx.dzjg,iQznum,dQzamt,iTpnum,dTpamt), fpub_GetCompname(lXmlhandle));    
    		
		/* �Ǽ�TIPS���˽�� */
		/* add dci 20141103 */    
    iRet = DBInsert("tips_dzjgxx", SD_TIPS_DZJGXX, NUMELE(SD_TIPS_DZJGXX), &stDzjgxx, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
    	
      fpub_SetMsg(lXmlhandle, 24358, "�ǼǺ��Ķ�����Ϣʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD,Fmtmsg("�ǼǺ��Ķ�����Ϣʧ��,��������[%s],����ϵͳ[%s]", 
            stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ǼǺ��Ķ�����Ϣʧ��"), 
                    fpub_GetCompname(lXmlhandle))
    }
    /* end add dci */
		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_dzjgxx values(:stDzjgxx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
         fpub_SetMsg(lXmlhandle, 24358, "�Ǽ�TIPS������Ϣʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("�Ǽ�TIPS������Ϣʧ��,��������[%s],����ϵͳ[%s]", 
               stDzjgxx.dzrq, stDzjgxx.dzxt),"ERROR")  
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�Ǽ�TIPS������Ϣʧ��"), 
                    fpub_GetCompname(lXmlhandle))
         
    } 
    */
       
    LOG(LM_STD,Fmtmsg("TIPS��ϸ�ܱ���[%d],TIPS��ϸ�ܽ��[%f],TIPSǰ�ñ���[%d],TIPSǰ�ý��[%f]",
        iTpnum,dTpamt,iQznum,dQzamt), fpub_GetCompname(lXmlhandle));    
   	
   	/* mod dci 20141103
   	EXEC SQL commit ;  
   	*/
   	iRet =DCICommit();
   	/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
       	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ����ʧ�ܣ�"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    } 
    */
    
    fpub_SetMsg(lXmlhandle, 0, "���ɶ��˽����Ϣ����");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);    
    
    return COMPRET_SUCC;
    
}
