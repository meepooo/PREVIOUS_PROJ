/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V3.0.00
����ϵͳ:AIX5.3
�ļ�����:SYW_TIPS_FUNDRT.sqc
�ļ�����:TIPS�ʽ�㻮����
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
/* mod dci 20141103 
EXEC SQL INCLUDE  "gaps_head.eh";
EXEC SQL INCLUDE  "../eh/tips_sszjhhls.eh";/* ˰���ʽ�㻮��ˮ�� 
EXEC SQL INCLUDE  "../eh/tips_sszjhhlspz.eh";/* ˰���ʽ�㻮��ˮ��ƾ֤ 
*/

#include "../eh/tips_sszjhhls.h"/* ˰���ʽ�㻮��ˮ�� */
#include "../eh/tips_sszjhhlspz.h"/* ˰���ʽ�㻮��ˮ��ƾ֤ */

/*EXEC SQL BEGIN DECLARE SECTION;*/
typedef struct TDB_ZJHHDZ
{
	char zjrq[8+1];/*��������*/
	char zjlsh[32+1];/*������ˮ��*/
	char chkdate[8+1];/*��������*/
	char chkacctord[4+1];/*��������*/
	char paybkcode[12+1];/*�������к�*/ 
	char payacct[32+1];/*�������˺�*/
	char payeebankno[12+1];/*�տ����к�*/  
	char payeeacct[32+1];/*��������־*/
	double jyje;/*���׽��*/
	char qzrq[8+1];/*ǰ������*/
	int qzlsh;/*ǰ����ˮ��*/
}SDB_ZJHHDZ;
/*EXEC SQL END DECLARE SECTION;*/

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )
/*****************************************
��¼�ʽ�㻮������־�ĺ���

*****************************************/
int LOG_ZJHHDZ(char *sTransCode,char *buf)
{
  char sfile[200];
  FILE *fp;
  
  memset(sfile, 0x00, sizeof(sfile));
  sprintf(sfile,"%s/file/tips/chkacct/ZJHHDZ_%s_%s.log",getenv("HOME"),sTransCode,GetSysDate());
  if ((fp=fopen(sfile,"a+")) ==  NULL )	
    return -1;
  fprintf(fp," %s\n",buf);
  fclose(fp); 
  return 0;	
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitHHLS
�������: ��ʼʵʱ�㻮��ˮ
�������: 
    ��ʼʵʱ�㻮��ˮ
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
tips_sszjhhls  ˰���ʽ�㻮��ˮ��

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��12��23��
�޸�����: 2014��12��20��DCI����
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitHHLS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103 
    EXEC SQL BEGIN DECLARE SECTION;
         SDB_TIPS_SSZJHHLS stZjhhls;
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
  	
  	SDB_TIPS_SSZJHHLS stZjhhls;
  	char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
    fpub_InitSoComp(lXmlhandle);

    memset(&stZjhhls, 0x00, sizeof(stZjhhls));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( stZjhhls.zwrq, sBuf, sizeof(stZjhhls.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "�ۺ�ǰ����ˮ��")
    stZjhhls.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("��ʼʵʱ�㻮��ˮ�� ��������[%s],�ۺ�ǰ����ˮ��[%d]", 
        stZjhhls.zwrq, stZjhhls.zhqzlsh), fpub_GetCompname(lXmlhandle));    

		/* add dci 20141103 */
		iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		/* end dci */
		
    /* 3.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkDate", sBuf)
    pstrcopy( stZjhhls.chkdate, sBuf, sizeof(stZjhhls.chkdate));
    if ( stZjhhls.chkdate[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("�������ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������ڲ���Ϊ��, chkdate=[%s]", stZjhhls.chkdate),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 4.�������κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy( stZjhhls.chkacctord, sBuf, sizeof(stZjhhls.chkacctord));
    if ( stZjhhls.chkacctord[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("�������κŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������κŲ���Ϊ��, chkacctord=[%s]", stZjhhls.chkacctord),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 5.�������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy( stZjhhls.paybkcode, sBuf, sizeof(stZjhhls.paybkcode));
    if ( stZjhhls.paybkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("�������кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������кŲ���Ϊ��, paybkcode=[%s]", stZjhhls.paybkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 6.�տ����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy( stZjhhls.payeebankno, sBuf, sizeof(stZjhhls.payeebankno));
    if ( stZjhhls.payeebankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("�տ����кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ����кŲ���Ϊ��, payeebankno=[%s]", stZjhhls.payeebankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 7.��������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy( stZjhhls.payopbkcode, sBuf, sizeof(stZjhhls.payopbkcode));
    if ( stZjhhls.payopbkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("��������кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("��������кŲ���Ϊ��, payopbkcode=[%s]", stZjhhls.payopbkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 8.�������˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy( stZjhhls.payacct, sBuf, sizeof(stZjhhls.payacct));
    if ( stZjhhls.payacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("�������˺Ų���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������˺Ų���Ϊ��, payacct=[%s]", stZjhhls.payacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 9.���������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkName", sBuf)
    pstrcopy( stZjhhls.paybkname, sBuf, sizeof(stZjhhls.paybkname));
    if ( stZjhhls.paybkname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24279, Fmtmsg("���������Ʋ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���������Ʋ���Ϊ��, paybkname=[%s]", stZjhhls.paybkname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 10.�տ�����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOpBankNo", sBuf)
    pstrcopy( stZjhhls.payeeopbankno, sBuf, sizeof(stZjhhls.payeeopbankno));
    if ( stZjhhls.payeeopbankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24280, Fmtmsg("�տ�����кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ�����кŲ���Ϊ��, payeeopbandno=[%s]", stZjhhls.payeeopbankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 11.�տ����˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy( stZjhhls.payeeacct, sBuf, sizeof(stZjhhls.payeeacct));
    if ( stZjhhls.payeeacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24281, Fmtmsg("�տ����˺Ų���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ����˺Ų���Ϊ��, payeeacct=[%s]", stZjhhls.payeeacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 12.�տ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankName", sBuf)
    pstrcopy( stZjhhls.payeebankname, sBuf, sizeof(stZjhhls.payeebankname));
    if ( stZjhhls.payeebankname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24282, Fmtmsg("�տ������Ʋ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ������Ʋ���Ϊ��, payeebankname=[%s]", stZjhhls.payeebankname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 13.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctType", sBuf)
    pstrcopy( stZjhhls.chkaccttype, sBuf, sizeof(stZjhhls.chkaccttype));
    if ( stZjhhls.chkaccttype[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24283, Fmtmsg("�������Ͳ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������Ͳ���Ϊ��, payeeacct=[%s]", stZjhhls.chkaccttype),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 14.���α��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllNum", sBuf)
    stZjhhls.allnum = atoi(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24284, Fmtmsg("���α�������Ϊ��"));
        LOG(LM_STD,Fmtmsg("���α�������Ϊ��, allnum=[%d]", stZjhhls.allnum),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 15.���ν�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllAmt", sBuf)
    stZjhhls.allamt=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24285, Fmtmsg("���ν���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���ν���Ϊ��, allamt=[%.2f]", stZjhhls.allamt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }   
    
    /* 16.���ױ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jybs", sBuf)
    stZjhhls.jybs = atoi(sBuf);
    if ( sBuf[0] == '\0' )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24286, Fmtmsg("���ױ�������Ϊ��"));
        LOG(LM_STD,Fmtmsg("���ױ�������Ϊ��, jybs=[%d]", stZjhhls.jybs),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 17.���׽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyje", sBuf)
    stZjhhls.jyje=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24287, Fmtmsg("���׽���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���׽���Ϊ��, jyje=[%.2f]", stZjhhls.jyje),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 18.���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/addword", sBuf)
    pstrcopy(stZjhhls.addword, sBuf, sizeof(stZjhhls.addword));
    if ( stZjhhls.addword[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24288, Fmtmsg("���Բ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���Բ���Ϊ��, addword=[%s]", stZjhhls.addword),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 19.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyrq", sBuf)
    pstrcopy(stZjhhls.jyrq, sBuf, sizeof(stZjhhls.jyrq));
    if ( stZjhhls.jyrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24289, Fmtmsg("�������ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������ڲ���Ϊ��, jyrq=[%s]", stZjhhls.jyrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 20.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jysj", sBuf)
    pstrcopy(stZjhhls.jysj, sBuf, sizeof(stZjhhls.jysj));
    if ( stZjhhls.jysj[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24290, Fmtmsg("����ʱ�䲻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("����ʱ�䲻��Ϊ��, jysj=[%s]", stZjhhls.jysj),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 21.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(stZjhhls.qsrq, sBuf, sizeof(stZjhhls.qsrq));
    if ( stZjhhls.qsrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24291, Fmtmsg("�������ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������ڲ���Ϊ��, qsrq=[%s]", stZjhhls.qsrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 22.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qslsh", sBuf)
    stZjhhls.qslsh=atoi(sBuf);
    if ( stZjhhls.qslsh == 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24292, Fmtmsg("������ˮ�Ų���Ϊ��"));
        LOG(LM_STD,Fmtmsg("������ˮ�Ų���Ϊ��, qslsh=[%d]", stZjhhls.qslsh),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 23.ҵ������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ywzl", sBuf)
    pstrcopy(stZjhhls.ywzl, sBuf, sizeof(stZjhhls.ywzl));
    if ( stZjhhls.ywzl[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24293, Fmtmsg("ҵ�����಻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("ҵ�����಻��Ϊ��, ywzl=[%s]", stZjhhls.ywzl),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 24.�㻮���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hhcs", sBuf)
    stZjhhls.hhcs=atoi(sBuf);

    /* 25.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stZjhhls.zjrq, sBuf, sizeof(stZjhhls.zjrq));

    /* 26.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stZjhhls.zjsj, sBuf, sizeof(stZjhhls.zjsj));

    /* 27.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stZjhhls.zjlsh, sBuf, sizeof(stZjhhls.zjlsh));

    /* 28.����״̬ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stZjhhls.jyzt, sBuf, sizeof(stZjhhls.jyzt));
    if ( stZjhhls.jyzt[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24298, Fmtmsg("����״̬����Ϊ��"));
        LOG(LM_STD,Fmtmsg("����״̬����Ϊ��, jyzt=[%s]", stZjhhls.jyzt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 29.��Ӧ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xym", sBuf)
    pstrcopy(stZjhhls.xym, sBuf, sizeof(stZjhhls.xym));
    if ( stZjhhls.xym[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24299, Fmtmsg("��Ӧ�벻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("��Ӧ�벻��Ϊ��, xym=[%s]", stZjhhls.xym),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 30.��Ӧ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xyxx", sBuf)
    pstrcopy(stZjhhls.xyxx, sBuf, sizeof(stZjhhls.xyxx));
    if ( stZjhhls.xyxx[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24300, Fmtmsg("��Ӧ��Ϣ����Ϊ��"));
        LOG(LM_STD,Fmtmsg("��Ӧ��Ϣ����Ϊ��, xyxx=[%s]", stZjhhls.xyxx),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 31.�����־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stZjhhls.qsbz, sBuf, sizeof(stZjhhls.qsbz));
    if ( stZjhhls.qsbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24301, Fmtmsg("�����־����Ϊ��"));
        LOG(LM_STD,Fmtmsg("�����־����Ϊ��, qsbz=[%s]", stZjhhls.qsbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 32.���˱�־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stZjhhls.dzbz, sBuf, sizeof(stZjhhls.dzbz));
    if ( stZjhhls.dzbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("���˱�־����Ϊ��"));
        LOG(LM_STD,Fmtmsg("���˱�־����Ϊ��, dzbz=[%s]", stZjhhls.dzbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 32.�ֹ��޸���Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sgxgxx", sBuf)
    pstrcopy(stZjhhls.sgxgxx, sBuf, sizeof(stZjhhls.sgxgxx));

    /* 33.�����ֶ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/byzd", sBuf)
    pstrcopy(stZjhhls.byzd, sBuf, sizeof(stZjhhls.byzd));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_sszjhhls", SD_TIPS_SSZJHHLS, NUMELE(SD_TIPS_SSZJHHLS), &stZjhhls, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24308, "��ʼ��˰���ʽ�㻮��ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("��ʼ��˰���ʽ�㻮��ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL; 
    }
		
		iRet =DCICommit();
		/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */
    /* end add dci 20141103 */
                       
    /* mod dci 20141103 
    EXEC SQL INSERT INTO tips_sszjhhls  VALUES (:stZjhhls);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24308, "��ʼ��˰���ʽ�㻮��ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("��ʼ��˰���ʽ�㻮��ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	    
		*/
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}    

/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdZJHH
�������: �����ʽ�ʵʱ�㻮��
�������: 
  �����ʽ�ʵʱ�㻮��״̬
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
˰���ʽ�㻮��ˮ��	tips_sszjhhls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��12��23��
�޸�����: 2014��12��20��DCI���죬������
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdZJHH(HXMLTREE lXmlhandle)
{	
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sZwrq[8+1];
         int iZhqzlsh;
         char sJyzt[1+1];/* ����״̬ */
         char sQsrq[8+1];/* �������� */
         int iQslsh;/* ������ˮ�� */
         char sZjrq[8+1];/* �������� */
         char sZjsj[8+1];/* ����ʱ�� */
         char sZjlsh[32+1];/* ������ˮ�� */
         char sXym[5+1];/* ��Ӧ�� */
         char sXyxx[60+1];/* ��Ӧ��Ϣ */
    /*EXEC SQL END DECLARE SECTION;*/
    
    char sBuf[256];
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
  	
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(10);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "�ۺ�ǰ����ˮ��")
    iZhqzlsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJyzt, 0x00, sizeof(sJyzt));
    COMP_GETPARSEPARAS(3, sBuf, "����״̬")
    pstrcopy( sJyzt, sBuf, sizeof(sJyzt));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_GETPARSEPARAS(4, sBuf, "��������")
    pstrcopy( sQsrq, sBuf, sizeof(sQsrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iQslsh=0;
    COMP_GETPARSEPARAS(5, sBuf, "������ˮ��")
    iQslsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjrq, 0x00, sizeof(sZjrq));
    COMP_GETPARSEPARAS(6, sBuf, "��������")
    pstrcopy( sZjrq, sBuf, sizeof(sZjrq));       

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjsj, 0x00, sizeof(sZjsj));
    COMP_GETPARSEPARAS(7, sBuf, "����ʱ��")
    pstrcopy( sZjsj, sBuf, sizeof(sZjsj));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjlsh, 0x00, sizeof(sZjlsh));
    COMP_GETPARSEPARAS(8, sBuf, "������ˮ��")
    pstrcopy( sZjlsh, sBuf, sizeof(sZjlsh));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXym, 0x00, sizeof(sXym));
    COMP_GETPARSEPARAS(9, sBuf, "��Ӧ��")
    pstrcopy( sXym, sBuf, sizeof(sXym));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXyxx, 0x00, sizeof(sXyxx));
    COMP_GETPARSEPARAS(10, sBuf, "��Ӧ��Ϣ")
    pstrcopy( sXyxx, sBuf, sizeof(sXyxx));
    
    LOG(LM_STD,Fmtmsg("�����ʽ�ʵʱ�㻮��ʼ����...��������[%s]ǰ����ˮ��=[%d]����״̬=[%s]",sZwrq, iZhqzlsh, sJyzt),"INFO")
    LOG(LM_STD,Fmtmsg("��������[%s]������ˮ��=[%d]��������=[%s]����ʱ��=[%s]������ˮ��[%s]", sQsrq, iQslsh, sZjrq, sZjsj, sZjlsh),"INFO")
    LOG(LM_STD,Fmtmsg("��Ӧ��=[%s]��Ӧ��Ϣ[%s]", sXym, sXyxx),"INFO")
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhls \
    		set jyzt  ='%s',\
    				hhcs  =hhcs + 1,\
    				qsrq  ='%s',\
    				qslsh =%d,\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s',\
    				xym   ='%s',\
    				xyxx  ='%s' \
    			where zwrq='%s' and zhqzlsh=%d" \
             ,sJyzt  \
             ,sQsrq  \
             ,iQslsh \
             ,sZjrq  \
             ,sZjsj  \
             ,sZjlsh \
             ,sXym   \
             ,sXyxx  \
             ,sZwrq  \
             ,iZhqzlsh);   
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = DCIExecuteDirect(sSql1);	 
         
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "ʵʱ�ʽ�ʵʱ�㻮��ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("ʵʱ�ʽ�ʵʱ�㻮��ʧ��"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24286, "����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���¼δ�ҵ�");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���¼δ�ҵ�"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;		
    }	

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_sszjhhls
    	   SET jyzt = :sJyzt,
    	       hhcs = hhcs + 1,
    	       qsrq = :sQsrq,
    	       qslsh = :iQslsh,
    	       zjrq = :sZjrq,
    	       zjsj = :sZjsj,
    	       zjlsh = :sZjlsh,
    	       xym = :sXym,
    	       xyxx = :sXyxx
         WHERE zwrq = :sZwrq 
           AND zhqzlsh = :iZhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "ʵʱ�ʽ�ʵʱ�㻮��ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("ʵʱ�ʽ�ʵʱ�㻮��ʧ��"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND )	
    {
         fpub_SetMsg(lXmlhandle, 24286, "����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���¼δ�ҵ�");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���¼δ�ҵ�"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    */   
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
��̬�����������
�����������: SYW_TIPS_ZJHH
�������: �ʽ�㻮(���)
�������: 
  �ʽ�㻮
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
˰���ʽ�㻮��ˮ��	tips_sszjhhls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��12��25��
�޸�����: 2014��12��20��DCI����
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_ZJHH(HXMLTREE lXmlhandle)
{	
    int iParas;
    //EXEC SQL BEGIN DECLARE SECTION;
         char sZwrq[8+1];
         int iZhqzlsh;
         char sJyzt[1+1];
         int iCount;
    //EXEC SQL END DECLARE SECTION;
    char sBuf[256];
    char sSubFlow[256];
    int iflag ;
    int iAll;
    int iSucc;
    int iFail;
      	
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1);
    
    memset(sSubFlow, 0x00, sizeof(sSubFlow));
    COMP_GETPARSEPARAS(1, sSubFlow, "�ʽ�㻮����")
    trim(sSubFlow);
    
    LOG(LM_STD,Fmtmsg("�ʽ�㻮��ʼ����...ʵʱ�㻮����=[%s]",sSubFlow),"INFO")
   
    iCount = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_sszjhhls \
    	where jyzt in ('1', '2') AND jyje > 0.00");   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")        	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "��ѯ˰���ʽ�㻮��ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ˰���ʽ�㻮��ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;    
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_sszjhhls
         WHERE jyzt in ('1', '2')
           AND jyje > 0.00;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "��ѯ˰���ʽ�㻮��ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ˰���ʽ�㻮��ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
    if ( iCount < 1 )
    {
         fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "��ǰû��Ҫ������ʽ�㻮��¼");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
         LOG(LM_STD, Fmtmsg("��ǰû��Ҫ������ʽ�㻮��¼"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_SUCC ;        
    }
    
    LOG(LM_STD, Fmtmsg("��ǰ��Ҫ������ʽ�㻮��¼��[%d]��", iCount), fpub_GetCompname(lXmlhandle))	
	   
    /* ����ҵ����ϸ�� */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select zwrq, zhqzlsh, jyzt from tips_sszjhhls \
    	where jyzt in ('1', '2') AND jyje > 0.00");  
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,36001, "���α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ��cur_ksfmx_plhz�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
   	
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL DECLARE cur_zjhhls CURSOR for 
         SELECT zwrq, zhqzlsh, jyzt
         FROM tips_sszjhhls
         WHERE jyzt in ('1', '2')
           AND jyje > 0.00;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_zjhhls;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_zjhhls",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24311, "���α�cur_zjhhlsʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��cur_zjhhls�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*��ʼѭ��*/
    iSucc = 0;
    iFail = 0;
    /* add dci 20141103 */
    for (iAll=0,iflag=0;;iAll++)
    {
        memset(sZwrq, 0x00, sizeof(sZwrq));
        iZhqzlsh=0;
        memset(sJyzt, 0x00, sizeof(sJyzt));
        iRet = DCIFetch(cur);
             
        if ( iRet < 0 )
        {  
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("��cur_zjhhls�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( iRet ==0 )
          break;
          
        sprintf( sZwrq, "%s", DCIFieldAsString( cur, 0 ) );
				iZhqzlsh = atoi(DCIFieldAsString( cur, 1 )) ;
				sprintf( sJyzt, "%s", DCIFieldAsString( cur, 2 ) );

        trim(sZwrq);
        trim(sJyzt);
              
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf),"%d", iZhqzlsh);
        COMP_SOFTSETXML("/tips/zhqzlsh", sBuf)
        COMP_SOFTSETXML("/tips/jyzt", sJyzt)
              
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("���ʽ�㻮������ϵͳ����"),"ERROR");
        	break;
        }
        
        /*�ж��������Ƿ���ɹ� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*����2ʧ��,������Ϊ�ɹ� */
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("���ʽ�㻮������ʧ��"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    DCIFreeCursor(cur);
    /* end add dci 20141103 */

    /* mod dci 20141103 
    for (iAll=0,iflag=0;;iAll++)
    {
        memset(sZwrq, 0x00, sizeof(sZwrq));
        iZhqzlsh=0;
        memset(sJyzt, 0x00, sizeof(sJyzt));
        EXEC SQL FETCH cur_zjhhls INTO :sZwrq, :iZhqzlsh, :sJyzt;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_zjhhls", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("��cur_zjhhls�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;

        trim(sZwrq);
        trim(sJyzt);
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf),"%d", iZhqzlsh);
        COMP_SOFTSETXML("/tips/zhqzlsh", sBuf)
        COMP_SOFTSETXML("/tips/jyzt", sJyzt)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("���ʽ�㻮������ϵͳ����"),"ERROR");
        	break;
        }
        
        /*�ж��������Ƿ���ɹ�
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*����2ʧ��,������Ϊ�ɹ�
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("���ʽ�㻮������ʧ��"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    EXEC SQL CLOSE cur_zjhhls; 
    */
       
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"���������ʽ�㻮ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���������ʽ�㻮ʧ��iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    fpub_SetMsg(lXmlhandle,0,"���������ʽ�㻮����");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���������ʽ�㻮����,��[%d]��,�ɹ�[%d]��,ʧ��[%d]��",
        iAll, iSucc, iFail), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
} 

/************************************************************************
��̬�����������
�����������: SYW_TIPS_ZJHHDZ
�������: �ʽ�㻮����(һ��)
 
�������: 
    �ʽ�㻮����(һ��)
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

��Ҫ�������:
  ����              ����
˰���ʽ�㻮��ˮ��	tips_sszjhhls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��12��25��
�޸�����: 2014��12��20��DCI���죬������
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_ZJHHDZ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION;*/
         SDB_ZJHHDZ stZjhhdz;
         SDB_TIPS_SSZJHHLS stZjhhls;
         char sDzrq[8+1];
         int iCount;
    /*EXEC SQL END DECLARE SECTION;*/
    
    char sBuf[256];
	int i;
	int iRet=0;
	int iFlag=0;
	char sMxFileName[256];
	char sLine[1024];
	char sResIcxp[256];
	int iQzdnum = 0;     /*ǰ�ö�ļ�¼��*/
	int iZjdnum = 0;    /*������ļ�¼��*/    
    FILE *fp;

		char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		CURSOR cur;
		
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(3);
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
    
    LOG(LM_STD,Fmtmsg("�ʽ�㻮���˿�ʼ����..."),fpub_GetCompname(lXmlhandle))  
    LOG(LM_STD,Fmtmsg("��������[%s],������ϸ�ļ�[%s],��ϸ�ļ�ICXP����[%s]",
        sDzrq, sMxFileName, sResIcxp),fpub_GetCompname(lXmlhandle))  
		
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "UPDATE tips_sszjhhls SET dzbz='0',qsbz='0' \
    		WHERE chkdate ='%s'",sDzrq);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                 	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24422, "����˰���ʽ�㻮��ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����˰���ʽ�㻮��ˮ��ʧ��"),
            fpub_GetCompname(lXmlhandle))       
    }
    
		/* end add dci 20141103 */
		
		/* mod dci 20141103 
    EXEC SQL UPDATE tips_sszjhhls SET dzbz='0',qsbz='0'
         WHERE chkdate = :sDzrq;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24422, "����˰���ʽ�㻮��ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����˰���ʽ�㻮��ˮ��ʧ��"),
            fpub_GetCompname(lXmlhandle))        
    }           
		*/
		
    /*�ȴ���ϸ�ļ�,У��*/
    fp = fopen(sMxFileName,"r");
    if ( fp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24422, "���ʽ�㻮�����ļ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���ʽ�㻮�����ļ�ʧ��[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
    /*�ļ��崦��*/
    for (iFlag=0,i=1; ;i++)
    {   	
        memset(sLine,0x00,sizeof(sLine));
        memset(sBuf, 0x00, sizeof(sBuf));  
        COMP_SOFTSETXML("/tips/zjhhdz/zjrq", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/zjlsh", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/ChkDate", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/ChkAcctOrd", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayBkCode", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayAcct", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayeeBankNo", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/PayeeAcct", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/jyje", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/qzrq", sBuf)
        COMP_SOFTSETXML("/tips/zjhhdz/qzlsh", sBuf)
        if (fgets(sLine,sizeof(sLine),fp) == NULL)
            break;                   /*�ļ����� ����*/
        trim(sLine);
        if ( i==1 || strlen(sLine) < 30 )
            continue;               /*���������ļ���ͷ�����,����*/
        sLine[strlen(sLine)-1]=0;   /*ȥ�����һ�����з�*/
        if (strcmp(sLine,"END") == 0 )
            break;                   /*���������ļ�������*/
        iRet=SBATCH_FuncICXPUPKG(lXmlhandle,sResIcxp,sLine,strlen(sLine));
        if (iRet < 0)
        { 
            iFlag = -1; 
            break; 
        }	
        memset(&stZjhhdz, 0x00, sizeof(stZjhhdz));
        /* �������� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/zjrq", sBuf)
        pstrcopy(stZjhhdz.zjrq, sBuf, sizeof(stZjhhdz.zjrq));
        /* ������ˮ�� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/zjlsh", sBuf)
        pstrcopy(stZjhhdz.zjlsh, sBuf, sizeof(stZjhhdz.zjlsh));
        /* �������� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/ChkDate", sBuf)
        pstrcopy(stZjhhdz.chkdate, sBuf, sizeof(stZjhhdz.chkdate));
        /* �������κ� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/ChkAcctOrd", sBuf)
        pstrcopy(stZjhhdz.chkacctord, sBuf, sizeof(stZjhhdz.chkacctord));
        /*  �������к� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayBkCode", sBuf)
        pstrcopy(stZjhhdz.paybkcode, sBuf, sizeof(stZjhhdz.paybkcode));
        /* �������˺� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayAcct", sBuf)
        pstrcopy(stZjhhdz.payacct, sBuf, sizeof(stZjhhdz.payacct));
        /* �տ����к� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayeeBankNo", sBuf)
        pstrcopy(stZjhhdz.payeebankno, sBuf, sizeof(stZjhhdz.payeebankno));
        /* �տ����˺� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/PayeeAcct", sBuf)
        pstrcopy(stZjhhdz.payeeacct, sBuf, sizeof(stZjhhdz.payeeacct));
        /* ���׽�� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/jyje", sBuf)
        stZjhhdz.jyje=atof(sBuf);
        /* ǰ������ */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/qzrq", sBuf)
        pstrcopy(stZjhhdz.qzrq, sBuf, sizeof(stZjhhdz.qzrq));
        /* ǰ����ˮ�� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/zjhhdz/qzlsh", sBuf)
        stZjhhdz.qzlsh=atoi(sBuf);
        /*���ʽ�㻮��ˮ����ȡ�������ڼ�ǰ����ˮ����ͬ�ļ�¼*/
        
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "UPDATE tips_sszjhhls SET dzbz='1',qsbz='1' \
    			WHERE zwrq='%s' AND  zhqzlsh=%d AND  jyzt='5' AND  jyje=%.2f",\
    			stZjhhdz.qzrq,stZjhhdz.qzlsh,stZjhhdz.jyje);
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")             	
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        	LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
                stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
            iFlag = -9;
            break;    
    		}
    		/*����Ҳ���������е�����,���ĳɹ�,ǰ��ʧ�� */
     		if( iRet == 0 ) 
        {   
  		  	iZjdnum ++;
    	  	LOG_ZJHHDZ("zjhhdz",Fmtmsg("-->�����ɹ�,ǰ��ʧ�ܣ�ǰ������[%s],ǰ����ˮ[%d],��������[%s],������ˮ[%s]���[%.2f],����취����ԭ��,�����ʽ�㻮������",
    	  	    	  	stZjhhdz.qzrq,stZjhhdz.qzlsh,stZjhhdz.zjrq,stZjhhdz.zjlsh,stZjhhdz.jyje));        
            /*���ʽ�㻮��ˮ����ȡ�������ڼ�ǰ����ˮ����ͬ�ļ�¼ */
          memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "UPDATE tips_sszjhhls SET dzbz='3',qsbz='0' \
    				WHERE zwrq='%s' AND  zhqzlsh=%d",\
    				stZjhhdz.qzrq,stZjhhdz.qzlsh);               	
    			iRet = DCIExecuteDirect(sSql1);	   
    			if ( iRet < 0 )
    			{
                LOG(LM_STD,Fmtmsg("�����ʽ�㻮��ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
                    stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
                iFlag = -9;
                break;
     	    }    	  

        }/* �����ɹ�,ǰ��ʧ�� */            
    
        /* end add dci 20141103 */
        
        /* mod dci 20141103 
     	EXEC SQL UPDATE tips_sszjhhls 
			 SET dzbz='1',
			     qsbz='1'
			 WHERE  zwrq=:stZjhhdz.qzrq
			   AND  zhqzlsh=:stZjhhdz.qzlsh
			   AND  jyzt='5'
               AND  jyje=:stZjhhdz.jyje ;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
  	 	if(SQLERR)
  	 	{
            LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
                stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
            iFlag = -9;
            break;
     	}
     	/*����Ҳ���������е�����,���ĳɹ�,ǰ��ʧ��
     	if( SQLNOTFOUND_TIPS ) 
        {   
  		  	iZjdnum ++;
    	  	LOG_ZJHHDZ("zjhhdz",Fmtmsg("-->�����ɹ�,ǰ��ʧ�ܣ�ǰ������[%s],ǰ����ˮ[%d],��������[%s],������ˮ[%s]���[%.2f],����취����ԭ��,�����ʽ�㻮������",
    	  	    	  	stZjhhdz.qzrq,stZjhhdz.qzlsh,stZjhhdz.zjrq,stZjhhdz.zjlsh,stZjhhdz.jyje));        
            /*���ʽ�㻮��ˮ����ȡ�������ڼ�ǰ����ˮ����ͬ�ļ�¼
     	    EXEC SQL UPDATE tips_sszjhhls 
		    	 SET dzbz='3',
		    	     qsbz='0'
		    	 WHERE  zwrq=:stZjhhdz.qzrq
		    	   AND  zhqzlsh=:stZjhhdz.qzlsh;
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
  	 	    if(SQLERR)
  	 	    {
                LOG(LM_STD,Fmtmsg("�����ʽ�㻮��ˮ��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
                    stZjhhdz.qzrq, stZjhhdz.qzlsh),"ERROR")   
                iFlag = -9;
                break;
     	    }    	  	
        }/* �����ɹ�,ǰ��ʧ�� */                
    }/* for (iFlag=0,i=1; ;i++)�ļ��崦�� */    
    
    fclose(fp);
    if (iFlag < 0)
    { 
        fpub_SetMsg(lXmlhandle,24423,Fmtmsg("�ʽ�㻮����ʧ��"));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�ʽ�㻮����ʧ��,ret[%d]..",iFlag),"ERROR");
    }
    /*�ж��Ƿ���δ�˶Ե�ǰ����ˮ--ǰ�ö�*/
    iCount = 0;
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_sszjhhls \
    	where chkdate = '%s' AND jyzt='5' AND dzbz = '0' AND qsbz = '0'",sDzrq);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle,24424,Fmtmsg("��ѯ�ʽ�㻮��ʧ��"));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�ʽ�㻮��ʧ��"),"ERROR");  
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount 
         FROM  tips_sszjhhls
     	 WHERE chkdate = :sDzrq
     	   AND jyzt='5'
           AND dzbz = '0'
           AND qsbz = '0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    { 
        fpub_SetMsg(lXmlhandle,24424,Fmtmsg("��ѯ�ʽ�㻮��ʧ��"));
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�ʽ�㻮��ʧ��"),"ERROR");
    }
    */
    
    if( iCount > 0 )
    {
        iQzdnum = iQzdnum + iCount; /* ǰ�ö������++ */
        /* ��ǰ�ö����ˮ��¼���ʱ�־��Ϊ2,��д�����ʲ�ƽ�ļ��� */
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_sszjhhls \
    			where chkdate = '%s' AND jyzt='5' AND dzbz = '0' AND qsbz = '0'",sDzrq); 
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            fpub_SetMsg(lXmlhandle,36001, "���α�ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ��cur_ksfmx_plhz�α�ʧ��"),
                fpub_GetCompname(lXmlhandle))
        }

        /* end dci 20141103 */
        
        /* mod dci 20141103 
        EXEC SQL DECLARE cur_zjhhdz CURSOR for 
            SELECT *
            FROM  tips_sszjhhls 
            WHERE chkdate = :sDzrq
              AND jyzt='5'
              AND dzbz = '0'
              AND qsbz = '0';
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
        
        EXEC SQL OPEN cur_zjhhdz;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_zjhhdz",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle,24425, "���α�ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("HXDZ��cur_drls_hxdz_cur�α�ʧ��"),
                fpub_GetCompname(lXmlhandle))
        }
        */
                  
        /*��ʼѭ��*/
        for (i=1,iFlag=0;;i++)
        {
            memset(&stZjhhls, 0x00, sizeof(stZjhhls));
            /* add dci 20141103 */
            iRet = DBFetch(cur, SD_TIPS_SSZJHHLS,NUMELE(SD_TIPS_SSZJHHLS),&stZjhhls, sErrmsg );
						if ( iRet < 0 )
            {  
            	iFlag=-1;
            	LOG(LM_STD,Fmtmsg("��cur_zjhhdz�α��ȡ����ʧ��"),"ERROR");
            	break;
            }
            if ( iRet == 0 )
              break;
            /* end add dci 20141103 */
            
            /* mod dci 20141103 
            EXEC SQL FETCH cur_zjhhdz INTO :stZjhhls;     
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_zjhhdz",sqlca.sqlcode),"ERROR");
            if ( SQLERR )
            {  
            	iFlag=-1;
            	LOG(LM_STD,Fmtmsg("��cur_zjhhdz�α��ȡ����ʧ��"),"ERROR");
            	break;
            }
            if ( SQLNOTFOUND )
              break;
            */  
            
            trim(stZjhhls.zjlsh);  
    	  		LOG_ZJHHDZ("zjhhdz",Fmtmsg("-->ǰ�óɹ�,����ʧ�ܣ���������[%s],ǰ����ˮ[%d],��������[%s],������ˮ��[%s]���[%.2f],����취����ԭ��,�����ʽ�㻮������",
    	  	  	stZjhhls.zwrq,stZjhhls.zhqzlsh,stZjhhls.zjrq,stZjhhls.zjlsh,stZjhhls.jyje));
            /*���¸���ˮ��ϸ״̬Ϊǰ�ö�*/
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhls \
    							set dzbz='2' \
    							where zwrq='%s' and zhqzlsh=%d" \
    							,stZjhhls.zwrq  \
    							,stZjhhls.zhqzlsh  );
               	
        		iRet = DCIExecuteDirect(sSql1);	 
        		if ( iRet < 0 )
        		{
            	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
            	
            	LOG(LM_STD,Fmtmsg("�����ʽ�㻮��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
                    stZjhhls.zwrq, stZjhhls.zhqzlsh),"ERROR")   
                iFlag = -5;
                break; 
        		}

            /* end add dci 20141103 */
            
            /* mod dci 20141103 
            EXEC SQL UPDATE tips_sszjhhls 
                 SET dzbz='2'
                 WHERE zwrq=:stZjhhls.zwrq
                   AND zhqzlsh=:stZjhhls.zhqzlsh;
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
            if(SQLERR)
            {
                LOG(LM_STD,Fmtmsg("�����ʽ�㻮��ʧ��,��������[%s],ǰ����ˮ��[%d]", 
                    stZjhhls.zwrq, stZjhhls.zhqzlsh),"ERROR")   
                iFlag = -5;
                break; 
            }
            */
        }/* for (i=1,iFlag=0;;i++) */ 
        /* add dci 20141103 */
        DCIFreeCursor(cur);
        /* end add dci 20141103 */
        
        /* mod dci 20141103   
        EXEC SQL CLOSE cur_zjhhdz; */
        
        if (iFlag < 0)
        {
            fpub_SetMsg(lXmlhandle,24426,"�����ʽ�㻮����ʱǰ�óɹ�����ʧ�ܵ����ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����ʽ�㻮����ʱǰ�óɹ�����ʧ�ܵ����ʧ��iflag=[%d]",iFlag),
                fpub_GetCompname(lXmlhandle))
        }

    }/* if( iCount > 0 )����Ķ���ǰ�ö����� */    
    LOG(LM_DEBUG,Fmtmsg("�ʽ�㻮���˽���,������[%d]��, ǰ�ö�[%d]��", 
        iZjdnum, iQzdnum), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle, 0, "�ʽ�㻮���˽���");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitHHLSPZ
�������: ��ʼʵʱ�㻮��ˮ
�������: 
    ��ʼʵʱ�㻮��ˮ
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
tips_sszjhhls  ˰���ʽ�㻮��ˮ��

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��12��23��
�޸�����: 2014��12��20��DCI���죬������
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitHHLSPZ(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         SDB_TIPS_SSZJHHLSPZ stZjhhlspz;
    /*EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
  	
    fpub_InitSoComp(lXmlhandle);

    memset(&stZjhhlspz, 0x00, sizeof(stZjhhlspz));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( stZjhhlspz.zwrq, sBuf, sizeof(stZjhhlspz.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "�������κ�")
    pstrcopy( stZjhhlspz.qspch, sBuf, sizeof(stZjhhlspz.qspch));
           
    LOG(LM_STD,Fmtmsg("��ʼʵʱ�㻮��ˮƾ֤�� ��������[%s],�������κ�[%s]", 
        stZjhhlspz.zwrq, stZjhhlspz.qspch), fpub_GetCompname(lXmlhandle));    
		
		/* 2.ǰ����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    stZjhhlspz.zhqzlsh = atoi(sBuf);
    
    /* 3.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkDate", sBuf)
    pstrcopy( stZjhhlspz.chkdate, sBuf, sizeof(stZjhhlspz.chkdate));
    if ( stZjhhlspz.chkdate[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("�������ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������ڲ���Ϊ��, chkdate=[%s]", stZjhhlspz.chkdate),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 4.�������κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy( stZjhhlspz.chkacctord, sBuf, sizeof(stZjhhlspz.chkacctord));
    if ( stZjhhlspz.chkacctord[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("�������κŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������κŲ���Ϊ��, chkacctord=[%s]", stZjhhlspz.chkacctord),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 5.�������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy( stZjhhlspz.paybkcode, sBuf, sizeof(stZjhhlspz.paybkcode));
    if ( stZjhhlspz.paybkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("�������кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������кŲ���Ϊ��, paybkcode=[%s]", stZjhhlspz.paybkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 6.�տ����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy( stZjhhlspz.payeebankno, sBuf, sizeof(stZjhhlspz.payeebankno));
    if ( stZjhhlspz.payeebankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("�տ����кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ����кŲ���Ϊ��, payeebankno=[%s]", stZjhhlspz.payeebankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 7.��������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy( stZjhhlspz.payopbkcode, sBuf, sizeof(stZjhhlspz.payopbkcode));
    if ( stZjhhlspz.payopbkcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("��������кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("��������кŲ���Ϊ��, payopbkcode=[%s]", stZjhhlspz.payopbkcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 8.�������˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy( stZjhhlspz.payacct, sBuf, sizeof(stZjhhlspz.payacct));
    if ( stZjhhlspz.payacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("�������˺Ų���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������˺Ų���Ϊ��, payacct=[%s]", stZjhhlspz.payacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 9.���������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkName", sBuf)
    pstrcopy( stZjhhlspz.paybkname, sBuf, sizeof(stZjhhlspz.paybkname));
    if ( stZjhhlspz.paybkname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24279, Fmtmsg("���������Ʋ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���������Ʋ���Ϊ��, paybkname=[%s]", stZjhhlspz.paybkname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 10.�տ�����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOpBankNo", sBuf)
    pstrcopy( stZjhhlspz.payeeopbankno, sBuf, sizeof(stZjhhlspz.payeeopbankno));
    if ( stZjhhlspz.payeeopbankno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24280, Fmtmsg("�տ�����кŲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ�����кŲ���Ϊ��, payeeopbandno=[%s]", stZjhhlspz.payeeopbankno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 11.�տ����˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy( stZjhhlspz.payeeacct, sBuf, sizeof(stZjhhlspz.payeeacct));
    if ( stZjhhlspz.payeeacct[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24281, Fmtmsg("�տ����˺Ų���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ����˺Ų���Ϊ��, payeeacct=[%s]", stZjhhlspz.payeeacct),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 12.�տ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankName", sBuf)
    pstrcopy( stZjhhlspz.payeebankname, sBuf, sizeof(stZjhhlspz.payeebankname));
    if ( stZjhhlspz.payeebankname[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24282, Fmtmsg("�տ������Ʋ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�տ������Ʋ���Ϊ��, payeebankname=[%s]", stZjhhlspz.payeebankname),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 13.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctType", sBuf)
    pstrcopy( stZjhhlspz.chkaccttype, sBuf, sizeof(stZjhhlspz.chkaccttype));
    if ( stZjhhlspz.chkaccttype[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24283, Fmtmsg("�������Ͳ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������Ͳ���Ϊ��, payeeacct=[%s]", stZjhhlspz.chkaccttype),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 14.���α��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllNum", sBuf)
    stZjhhlspz.allnum = atoi(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24284, Fmtmsg("���α�������Ϊ��"));
        LOG(LM_STD,Fmtmsg("���α�������Ϊ��, allnum=[%d]", stZjhhlspz.allnum),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 15.���ν�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllAmt", sBuf)
    stZjhhlspz.allamt=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24285, Fmtmsg("���ν���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���ν���Ϊ��, allamt=[%.2f]", stZjhhlspz.allamt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }   
    
    /* 16.���ױ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jybs", sBuf)
    stZjhhlspz.jybs = atoi(sBuf);
    if ( sBuf[0] == '\0' )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24286, Fmtmsg("���ױ�������Ϊ��"));
        LOG(LM_STD,Fmtmsg("���ױ�������Ϊ��, jybs=[%d]", stZjhhlspz.jybs),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 17.���׽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyje", sBuf)
    stZjhhlspz.jyje=atof(sBuf);
    if ( sBuf[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24287, Fmtmsg("���׽���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���׽���Ϊ��, jyje=[%.2f]", stZjhhlspz.jyje),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 18.���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/addword", sBuf)
    pstrcopy(stZjhhlspz.addword, sBuf, sizeof(stZjhhlspz.addword));
    if ( stZjhhlspz.addword[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24288, Fmtmsg("���Բ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("���Բ���Ϊ��, addword=[%s]", stZjhhlspz.addword),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 19.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyrq", sBuf)
    pstrcopy(stZjhhlspz.jyrq, sBuf, sizeof(stZjhhlspz.jyrq));
    if ( stZjhhlspz.jyrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24289, Fmtmsg("�������ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������ڲ���Ϊ��, jyrq=[%s]", stZjhhlspz.jyrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 20.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jysj", sBuf)
    pstrcopy(stZjhhlspz.jysj, sBuf, sizeof(stZjhhlspz.jysj));
    if ( stZjhhlspz.jysj[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24290, Fmtmsg("����ʱ�䲻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("����ʱ�䲻��Ϊ��, jysj=[%s]", stZjhhlspz.jysj),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 21.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(stZjhhlspz.qsrq, sBuf, sizeof(stZjhhlspz.qsrq));
    if ( stZjhhlspz.qsrq[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24291, Fmtmsg("�������ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("�������ڲ���Ϊ��, qsrq=[%s]", stZjhhlspz.qsrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 22.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qslsh", sBuf)
    stZjhhlspz.qslsh=atoi(sBuf);
    if ( stZjhhlspz.qslsh == 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24292, Fmtmsg("������ˮ�Ų���Ϊ��"));
        LOG(LM_STD,Fmtmsg("������ˮ�Ų���Ϊ��, qslsh=[%d]", stZjhhlspz.qslsh),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 23.ҵ������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ywzl", sBuf)
    pstrcopy(stZjhhlspz.ywzl, sBuf, sizeof(stZjhhlspz.ywzl));
    if ( stZjhhlspz.ywzl[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24293, Fmtmsg("ҵ�����಻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("ҵ�����಻��Ϊ��, ywzl=[%s]", stZjhhlspz.ywzl),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 24.�㻮���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/hhcs", sBuf)
    stZjhhlspz.hhcs=atoi(sBuf);

    /* 25.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stZjhhlspz.zjrq, sBuf, sizeof(stZjhhlspz.zjrq));

    /* 26.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stZjhhlspz.zjsj, sBuf, sizeof(stZjhhlspz.zjsj));

    /* 27.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stZjhhlspz.zjlsh, sBuf, sizeof(stZjhhlspz.zjlsh));

    /* 28.����״̬ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stZjhhlspz.jyzt, sBuf, sizeof(stZjhhlspz.jyzt));
    if ( stZjhhlspz.jyzt[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24298, Fmtmsg("����״̬����Ϊ��"));
        LOG(LM_STD,Fmtmsg("����״̬����Ϊ��, jyzt=[%s]", stZjhhlspz.jyzt),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 29.��Ӧ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xym", sBuf)
    pstrcopy(stZjhhlspz.xym, sBuf, sizeof(stZjhhlspz.xym));
    if ( stZjhhlspz.xym[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24299, Fmtmsg("��Ӧ�벻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("��Ӧ�벻��Ϊ��, xym=[%s]", stZjhhlspz.xym),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 30.��Ӧ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/xyxx", sBuf)
    pstrcopy(stZjhhlspz.xyxx, sBuf, sizeof(stZjhhlspz.xyxx));
    if ( stZjhhlspz.xyxx[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24300, Fmtmsg("��Ӧ��Ϣ����Ϊ��"));
        LOG(LM_STD,Fmtmsg("��Ӧ��Ϣ����Ϊ��, xyxx=[%s]", stZjhhlspz.xyxx),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }        

    /* 31.�����־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stZjhhlspz.qsbz, sBuf, sizeof(stZjhhlspz.qsbz));
    if ( stZjhhlspz.qsbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24301, Fmtmsg("�����־����Ϊ��"));
        LOG(LM_STD,Fmtmsg("�����־����Ϊ��, qsbz=[%s]", stZjhhlspz.qsbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 32.���˱�־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stZjhhlspz.dzbz, sBuf, sizeof(stZjhhlspz.dzbz));
    if ( stZjhhlspz.dzbz[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("���˱�־����Ϊ��"));
        LOG(LM_STD,Fmtmsg("���˱�־����Ϊ��, dzbz=[%s]", stZjhhlspz.dzbz),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }    

    /* 32.�ֹ��޸���Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sgxgxx", sBuf)
    pstrcopy(stZjhhlspz.sgxgxx, sBuf, sizeof(stZjhhlspz.sgxgxx));

    /* 33.�����ֶ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/byzd", sBuf)
    pstrcopy(stZjhhlspz.byzd, sBuf, sizeof(stZjhhlspz.byzd));
    
    /* 34.�������κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qspch", sBuf)
    pstrcopy(stZjhhlspz.qspch, sBuf, sizeof(stZjhhlspz.qspch));
    
    /* 35.��ӡ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dycs", sBuf)
    stZjhhlspz.dycs=0;
    
    /* 36.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qjylx", sBuf)
    pstrcopy(stZjhhlspz.qjylx, sBuf, sizeof(stZjhhlspz.qjylx));
        
    /* 37.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qslx", sBuf)
    pstrcopy(stZjhhlspz.qslx, sBuf, sizeof(stZjhhlspz.qslx));    
		
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_sszjhhlspz", SD_TIPS_SSZJHHLSPZ, NUMELE(SD_TIPS_SSZJHHLSPZ), &stZjhhlspz, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
			fpub_SetMsg(lXmlhandle, 24308, "��ʼ��˰���ʽ�㻮��ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("��ʼ��˰���ʽ�㻮��ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))
        
        return COMPRET_FAIL;  
    }

		/* end add dci 20141103 */ 
		/* mod dci 20141103 
    EXEC SQL INSERT INTO tips_sszjhhlspz  VALUES (:stZjhhlspz);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24308, "��ʼ��˰���ʽ�㻮��ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("��ʼ��˰���ʽ�㻮��ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))
        
        return COMPRET_FAIL;         
    }	    
    */

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}   


/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdZJHHPZ
�������: �����ʽ�ʵʱ�㻮��
�������: 
  �����ʽ�ʵʱ�㻮��״̬
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
˰���ʽ�㻮��ˮ��	tips_sszjhhls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��12��23��
�޸�����: 2014��12��20��DCI���죬������
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdZJHHPZ(HXMLTREE lXmlhandle)
{	
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sZwrq[8+1];
         int iZhqzlsh;
         char sJyzt[1+1];/* ����״̬ */
         char sQsrq[8+1];/* �������� */
         int iQslsh;/* ������ˮ�� */
         char sZjrq[8+1];/* �������� */
         char sZjsj[8+1];/* ����ʱ�� */
         char sZjlsh[32+1];/* ������ˮ�� */
         char sXym[5+1];/* ��Ӧ�� */
         char sXyxx[60+1];/* ��Ӧ��Ϣ */
         char	sQspch[32+1];
         char sQsbz[1+1];
    /*EXEC SQL END DECLARE SECTION;*/
    
    char sBuf[256];
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
  	
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(12);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "�ۺ�ǰ����ˮ��")
    iZhqzlsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJyzt, 0x00, sizeof(sJyzt));
    COMP_GETPARSEPARAS(3, sBuf, "����״̬")
    pstrcopy( sJyzt, sBuf, sizeof(sJyzt));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_GETPARSEPARAS(4, sBuf, "��������")
    pstrcopy( sQsrq, sBuf, sizeof(sQsrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iQslsh=0;
    COMP_GETPARSEPARAS(5, sBuf, "������ˮ��")
    iQslsh=atoi(sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjrq, 0x00, sizeof(sZjrq));
    COMP_GETPARSEPARAS(6, sBuf, "��������")
    pstrcopy( sZjrq, sBuf, sizeof(sZjrq));       

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjsj, 0x00, sizeof(sZjsj));
    COMP_GETPARSEPARAS(7, sBuf, "����ʱ��")
    pstrcopy( sZjsj, sBuf, sizeof(sZjsj));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZjlsh, 0x00, sizeof(sZjlsh));
    COMP_GETPARSEPARAS(8, sBuf, "������ˮ��")
    pstrcopy( sZjlsh, sBuf, sizeof(sZjlsh));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXym, 0x00, sizeof(sXym));
    COMP_GETPARSEPARAS(9, sBuf, "��Ӧ��")
    pstrcopy( sXym, sBuf, sizeof(sXym));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sXyxx, 0x00, sizeof(sXyxx));
    COMP_GETPARSEPARAS(10, sBuf, "��Ӧ��Ϣ")
    pstrcopy( sXyxx, sBuf, sizeof(sXyxx));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQspch, 0x00, sizeof(sQspch));
    COMP_GETPARSEPARAS(11, sBuf, "�������κ�")
    pstrcopy( sQspch, sBuf, sizeof(sQspch));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsbz, 0x00, sizeof(sQsbz));
    COMP_GETPARSEPARAS(12, sBuf, "�����ʶ")
    pstrcopy( sQsbz, sBuf, sizeof(sQsbz));
    
    LOG(LM_STD,Fmtmsg("�����ʽ�ʵʱ�㻮��ʼ����...��������[%s]ǰ����ˮ��=[%d]����״̬=[%s]",sZwrq, iZhqzlsh, sJyzt),"INFO")
    LOG(LM_STD,Fmtmsg("��������[%s]������ˮ��=[%d]��������=[%s]����ʱ��=[%s]������ˮ��[%s]", sQsrq, iQslsh, sZjrq, sZjsj, sZjlsh),"INFO")
    LOG(LM_STD,Fmtmsg("��Ӧ��=[%s]��Ӧ��Ϣ[%s]", sXym, sXyxx),"INFO")
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhls \
    		set jyzt  ='%s',\
    				hhcs  =hhcs + 1,\
    				qsrq  ='%s',\
    				qslsh =%d,\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s',\
    				xym   ='%s',\
    				xyxx  ='%s',\
    				qsbz  ='%s'\
    			where zwrq='%s' and zhqzlsh=%d", \
      sJyzt ,sQsrq  ,iQslsh ,sZjrq  ,sZjsj  ,sZjlsh ,sXym   ,sXyxx  ,sQsbz  ,sZwrq  ,iZhqzlsh);   
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "ʵʱ�ʽ�ʵʱ�㻮ƾ֤��ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("ʵʱ�ʽ�ʵʱ�㻮ƾ֤��ʧ��"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24286, "����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮ƾ֤���¼δ�ҵ�");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���ƾ֤¼δ�ҵ�"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;		
    }	
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sszjhhlspz \
    		set jyzt  ='%s',\
    				hhcs  =hhcs + 1,\
    				qsrq  ='%s',\
    				qslsh =%d,\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s',\
    				xym   ='%s',\
    				xyxx  ='%s',\
    				qsbz  ='%s'\
    			where byzd ='%s' " \
             ,sJyzt  \
             ,sQsrq  \
             ,iQslsh \
             ,sZjrq  \
             ,sZjsj  \
             ,sZjlsh \
             ,sXym   \
             ,sXyxx  \
             ,sQsbz  \
             ,sQspch);   

    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "ʵʱ�ʽ�ʵʱ�㻮ƾ֤��ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("ʵʱ�ʽ�ʵʱ�㻮ƾ֤��ʧ��"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24286, "����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮ƾ֤���¼δ�ҵ�");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���ƾ֤¼δ�ҵ�"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;		
    }	
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_sszjhhlspz
    	   SET jyzt = :sJyzt,
    	       hhcs = hhcs + 1,
    	       qsrq = :sQsrq,
    	       qslsh = :iQslsh,
    	       zjrq = :sZjrq,
    	       zjsj = :sZjsj,
    	       zjlsh = :sZjlsh,
    	       xym = :sXym,
    	       xyxx = :sXyxx,
    	       qsbz = :sQsbz
         WHERE zwrq = :sZwrq 
           AND qspch = :sQspch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "ʵʱ�ʽ�ʵʱ�㻮ƾ֤��ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("ʵʱ�ʽ�ʵʱ�㻮ƾ֤��ʧ��"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND )	
    {
         fpub_SetMsg(lXmlhandle, 24286, "����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮ƾ֤���¼δ�ҵ�");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���ƾ֤¼δ�ҵ�"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	  
    
    EXEC SQL UPDATE tips_sszjhhls
    	SET jyzt = :sJyzt,
    	       hhcs = hhcs + 1,
    	       qsrq = :sQsrq,
    	       qslsh = :iQslsh,
    	       zjrq = :sZjrq,
    	       zjsj = :sZjsj,
    	       zjlsh = :sZjlsh,
    	       xym = :sXym,
    	       xyxx = :sXyxx,
    	       qsbz = :sQsbz
         WHERE byzd = :sQspch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")       	
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "ʵʱ�ʽ�ʵʱ�㻮��ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("ʵʱ�ʽ�ʵʱ�㻮��ʧ��"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND )	
    {
         fpub_SetMsg(lXmlhandle, 24286, "����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���¼δ�ҵ�");
         EXEC SQL rollback;
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,Fmtmsg("����ʧ��-->ʵʱ�ʽ�ʵʱ�㻮���¼δ�ҵ�"),fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    */ 
           	
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 
