/*PAB_HeadPkgChk  PAB_ICC_InsSerial PAB_ICC_UpdSerial���ο�cibybh�Ǽ���ˮ��*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gaps_head.h"
#include "DCI.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/PABYBH_SERIAL.h"
#include "../incl/pabybh_xmlmacro.h"


static int iCountOpen = 0;

#define _u8 unsigned char
#define _u16 unsigned short
#define _u32 unsigned int



/********************************************************
*   ����:     func_ChkZhCharGBK
*   ����:     ���GBK�����ַ���ĩβ�Ƿ��в����������ģ�����ȥ��
*   ����˵��: sTmpStr   �ַ���
*   ����:     -1:ʧ��
              >=0:�ɹ�

GB2312
��Χ�� 0xA1A1 - 0xFEFE
���ַ�Χ�� 0xB0A1 - 0xF7FE
GBK
���ַ�Χ�� 0x8140 - 0xFEFE

********************************************************/
int
func_ChkZhCharGBK (HXMLTREE lXmlhandle, char* sStr)
{
    int iTmp = 0, iLenStr = 0;
    unsigned char uc;
    char* sTmpStr = sStr;

    iLenStr = strlen(sTmpStr);
    if (0 == iLenStr)
    {
	LOG(LM_STD, Fmtmsg("�ַ���Ϊ�գ��˳�У�飡", iTmp), "INFO")
	return 0;
    }

    while (iTmp < iLenStr - 2)
    {
	/*����������ַ�������������ֽڣ��������һ���ֽ�*/
	uc = (unsigned char) sTmpStr[iTmp];
	if (uc >= 0x81 && uc <= 0xFE)
	{
	    iTmp += 2;
	}
	else
	    iTmp++;
    }
    LOG(LM_STD, Fmtmsg("sTmpStr[%X-%X]", (unsigned char )sTmpStr[iTmp], (unsigned char )sTmpStr[iTmp + 1]), "INFO")
    /*����������ֽ������*/
    if (iTmp == iLenStr - 2) /*���ָ�����ڶ����ַ�*/
    {
	uc = (unsigned char) sTmpStr[iTmp];
	if (uc >= 0x81 && uc <= 0xFE)/*��������ֽ���һ�����֣�����Ҫ�ټ����*/
	    return 0;
	else
	    iTmp++;
    }

    /*�������е�ìͷӦ�ö�ָ�������һ���ֽ�*/
    if (iTmp == iLenStr - 1) /*���ָ�����һ���ַ�*/
    {
	uc = (unsigned char) sTmpStr[iTmp];
	if (uc >= 0x81 && uc <= 0xFE)/*���һ���ֽ��ǰ�����֣��ɵ���*/
	    sTmpStr[iTmp] = '\0';
	else
	    return 0;
    }
    else/*���ǲ����ܵ�*/
    {
	LOG(LM_STD, Fmtmsg("ɨ���ַ��������ⲻӦ�ð���iTmp[%d]", iTmp), "INFO")
	return -1;
    }

    return 0;
}



/************************************************************************
�汾:V1.1.1.0
��̬�����������
�����������:PAB_ICC_InsSerial
�������:PAB_ICC_InsSerial
�������:ƽ����������ǰ�ò�����ˮ
�������:
        ��Ҫʹ�ֶ���ֵ�����ж���
        1.��¼��֮ǰ����Ӧ�Ľڵ㸳ֵ��
        2.���¼�¼֮ǰ����Ӧ�޸ĵĽڵ㸳ֵ��
        
        ������ò�Ҫ�޸ģ������ƽ����Eͨͨ�����ã�����ҵ���޸Ŀ�����������ҵ��ʧ�ء�                   
�� Ŀ �飺
�� �� Ա:
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT PABYBH_InsSerial( HXMLTREE lXmlhandle )
{
  char sTmp[256+1];
  char sErrMsg[256];
  int  iRet=0;
  PABYBH_SERIAL SDB_Serial;
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

	/*��ȡ��ˮ��¼��־ 0 ��¼ 1 ����¼*/
    memset(sTmp,0,sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sTmp);
    if ( ( 0 == sTmp[0] ) || ( sTmp[0] == '1' ))
    {
        LOG(LM_STD, Fmtmsg("�����ײ�����ˮ[%s]", sTmp),"")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }


  memset(&SDB_Serial,0x00,sizeof(SDB_Serial));
  
	/*��������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSDATE, sTmp)
	memcpy(SDB_Serial.TRANSDATE, sTmp, sizeof(SDB_Serial.TRANSDATE)-1);
	
	/*ƽ̨��ˮ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSSERIALNO, sTmp)
	memcpy(SDB_Serial.TRANSSERIALNO, sTmp, sizeof(SDB_Serial.TRANSSERIALNO)-1);
	
	/*ԭƽ̨����*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSDATE, sTmp)
	memcpy(SDB_Serial.ORITRANSDATE, sTmp, sizeof(SDB_Serial.ORITRANSDATE)-1);
	
	/*ԭƽ̨��ˮ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSSERIALNO, sTmp)
	memcpy(SDB_Serial.ORITRANSSERIALNO, sTmp, sizeof(SDB_Serial.ORITRANSSERIALNO)-1);
	
	/*����ʱ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSTIME, sTmp)
	memcpy(SDB_Serial.TRANSTIME, sTmp, sizeof(SDB_Serial.TRANSTIME)-1);
	
	/*ҵ������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_WORKDATE, sTmp)
	memcpy(SDB_Serial.WORKDATE, sTmp, sizeof(SDB_Serial.WORKDATE)-1);
	
	/*ҵ����ˮ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_WORKSERIALNO, sTmp)
	memcpy(SDB_Serial.WORKSERIALNO, sTmp, sizeof(SDB_Serial.WORKSERIALNO)-1);
	
	/*��������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_REQDATE, sTmp)
	memcpy(SDB_Serial.REQDATE, sTmp, sizeof(SDB_Serial.REQDATE)-1);
	
	/*������ˮ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_REQSERIALNO, sTmp)
	memcpy(SDB_Serial.REQSERIALNO, sTmp, sizeof(SDB_Serial.REQSERIALNO)-1);
	
	/*��Ⱥ�ڵ��������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CLUSTERNODENAME, sTmp)
	memcpy(SDB_Serial.CLUSTERNODENAME, sTmp, sizeof(SDB_Serial.CLUSTERNODENAME)-1);
	
	/*��Ⱥ�ڵ����IP*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CLUSTERNODEIP, sTmp)
	memcpy(SDB_Serial.CLUSTERNODEIP, sTmp, sizeof(SDB_Serial.CLUSTERNODEIP)-1);
	
	/*�����к�*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_COBANKNO, sTmp)
	memcpy(SDB_Serial.COBANKNO, sTmp, sizeof(SDB_Serial.COBANKNO)-1);
	
	/*���׻���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSORG, sTmp)
	memcpy(SDB_Serial.TRANSORG, sTmp, sizeof(SDB_Serial.TRANSORG)-1);
	
	/*���׹�Ա*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSOPER, sTmp)
	memcpy(SDB_Serial.TRANSOPER, sTmp, sizeof(SDB_Serial.TRANSOPER)-1);
	
	/*��Ȩ����*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AUTHORG, sTmp)
	memcpy(SDB_Serial.AUTHORG, sTmp, sizeof(SDB_Serial.AUTHORG)-1);
	
	/*��Ȩ��Ա*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AUTHOPER, sTmp)
	memcpy(SDB_Serial.AUTHOPER, sTmp, sizeof(SDB_Serial.AUTHOPER)-1);
	
	/*��������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CNLTYPE, sTmp)
	memcpy(SDB_Serial.CNLTYPE, sTmp, sizeof(SDB_Serial.CNLTYPE)-1);
	
	/*�ն��豸���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TERMEQUINO, sTmp)
	memcpy(SDB_Serial.TERMEQUINO, sTmp, sizeof(SDB_Serial.TERMEQUINO)-1);
	
	/*���״���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSCODE, sTmp)
	memcpy(SDB_Serial.TRANSCODE, sTmp, sizeof(SDB_Serial.TRANSCODE)-1);
	
	/*���ӽ��״���0����1���2����������3���򹤱���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSCODE1, sTmp)
	memcpy(SDB_Serial.TRANSCODE1, sTmp, sizeof(SDB_Serial.TRANSCODE1)-1);
	
	/*��������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUACOUNTYPE, sTmp)
	memcpy(SDB_Serial.CUACOUNTYPE, sTmp, sizeof(SDB_Serial.CUACOUNTYPE)-1);
	
	/*�����˱�־*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSNAME, sTmp)
	memcpy(SDB_Serial.TRANSNAME, sTmp, sizeof(SDB_Serial.TRANSNAME)-1);
	
	/*�ʽ�����, 0---ת��1---ת��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CAPITALTYPE, sTmp)
	memcpy(SDB_Serial.CAPITALTYPE, sTmp, sizeof(SDB_Serial.CAPITALTYPE)-1);
	
	/*�������(��ܡ��ƽ��)*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sTmp)
	memcpy(SDB_Serial.SVRCODE, sTmp, sizeof(SDB_Serial.SVRCODE)-1);
	
	/*�ͻ�����*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTNAME, sTmp)
	memcpy(SDB_Serial.CUSTNAME, sTmp, sizeof(SDB_Serial.CUSTNAME)-1);
	
	/*�ͻ�����00-����01-����*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTTYPE, sTmp)
	memcpy(SDB_Serial.CUSTTYPE, sTmp, sizeof(SDB_Serial.CUSTTYPE)-1);
	
	/*�����˺�*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO, sTmp)
	memcpy(SDB_Serial.ACCTNO, sTmp, sizeof(SDB_Serial.ACCTNO)-1);
	
	/*�����ʺ�*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIACCTNO, sTmp)
	memcpy(SDB_Serial.ORIACCTNO, sTmp, sizeof(SDB_Serial.ORIACCTNO)-1);
	
	/*�ʺ�2�������˻�*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO2, sTmp)
	memcpy(SDB_Serial.ACCTNO2, sTmp, sizeof(SDB_Serial.ACCTNO2)-1);
	
	/*ȯ�̴���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STOCKCODE, sTmp)
	memcpy(SDB_Serial.STOCKCODE, sTmp, sizeof(SDB_Serial.STOCKCODE)-1);
	
	/*�ʽ��ʺ�*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CAPITALACCTNO, sTmp)
	memcpy(SDB_Serial.CAPITALACCTNO, sTmp, sizeof(SDB_Serial.CAPITALACCTNO)-1);
	
	/*���׽��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSAMT, sTmp)
	SDB_Serial.TRANSAMT=atof(sTmp);
	
	/*���׽��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSAMT, sTmp)
	SDB_Serial.ORITRANSAMT=atof(sTmp);
	
	/*���2*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT2, sTmp)
	SDB_Serial.AMT2=atof(sTmp);
	
	/*���3*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT3, sTmp)
	SDB_Serial.AMT3=atof(sTmp);
	
	/*����*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURR, sTmp)
	memcpy(SDB_Serial.CURR, sTmp, sizeof(SDB_Serial.CURR)-1);
	
	/*�����ʶ*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CASHFLAG, sTmp)
	memcpy(SDB_Serial.CASHFLAG, sTmp, sizeof(SDB_Serial.CASHFLAG)-1);
	
	/*��Eͨ�������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSVRCODE, sTmp)
	memcpy(SDB_Serial.IEPSVRCODE, sTmp, sizeof(SDB_Serial.IEPSVRCODE)-1);
	
	/*��Eͨ���״���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRANSCODE, sTmp)
	memcpy(SDB_Serial.IEPTRANSCODE, sTmp, sizeof(SDB_Serial.IEPTRANSCODE)-1);
	
	/*��Eͨҵ������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPBSIDATE, sTmp)
	memcpy(SDB_Serial.IEPBSIDATE, sTmp, sizeof(SDB_Serial.IEPBSIDATE)-1);
	
	/*��Eͨ��������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRADATE, sTmp)
	memcpy(SDB_Serial.IEPTRADATE, sTmp, sizeof(SDB_Serial.IEPTRADATE)-1);
	
	/*��Eͨ��ˮ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSERIALNO, sTmp)
	memcpy(SDB_Serial.IEPSERIALNO, sTmp, sizeof(SDB_Serial.IEPSERIALNO)-1);
	
	/*ԭ��Eͨҵ������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPBSIDATE, sTmp)
	memcpy(SDB_Serial.ORIIEPBSIDATE, sTmp, sizeof(SDB_Serial.ORIIEPBSIDATE)-1);
	
	/*ԭ��Eͨ��ˮ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPSERIALNO, sTmp)
	memcpy(SDB_Serial.ORIIEPSERIALNO, sTmp, sizeof(SDB_Serial.ORIIEPSERIALNO)-1);
	
	/*��Eͨ��Ӧ����*/
	sprintf(SDB_Serial.IEPRESPCODE,"");
	
	/*��Eͨ��Ӧ��Ϣ*/
	sprintf(SDB_Serial.IEPRESPMSG, "");
	
	/*������������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTBSIDATE, sTmp)
	memcpy(SDB_Serial.HOSTBSIDATE, sTmp, sizeof(SDB_Serial.HOSTBSIDATE)-1);
	
	/*������ˮ��*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSERIALNO, sTmp)
	memcpy(SDB_Serial.HOSTSERIALNO, sTmp, sizeof(SDB_Serial.HOSTSERIALNO)-1);
	
	/*�������״���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTTRANSCODE, sTmp)
	memcpy(SDB_Serial.HOSTTRANSCODE, sTmp, sizeof(SDB_Serial.HOSTTRANSCODE)-1);
	
	/*������Ӧ����*/
	sprintf(SDB_Serial.HOSTRESPCODE, "");
	
	/*������Ӧ��Ϣ*/
	sprintf(SDB_Serial.HOSTRESPMSG, "");
	
	/*��Ӧ��*/
	sprintf(SDB_Serial.RESPCODE, "");
	
	/*��Ӧ��Ϣ*/
	sprintf(SDB_Serial.RESPMSG, "");
	
	/*���Ľ���״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSTAT, sTmp)
	memcpy(SDB_Serial.IEPSTAT, sTmp, sizeof(SDB_Serial.IEPSTAT)-1);
	
	/*���Ľ���״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSTAT, sTmp)
	memcpy(SDB_Serial.HOSTSTAT, sTmp, sizeof(SDB_Serial.HOSTSTAT)-1);
	
	/*����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STAT, sTmp)
	memcpy(SDB_Serial.STAT, sTmp, sizeof(SDB_Serial.STAT)-1);
	
	/*ƽ̨ͬ������ǰԭ����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORISTAT, sTmp)
	memcpy(SDB_Serial.ORISTAT, sTmp, sizeof(SDB_Serial.ORISTAT)-1);
	
	/*֤������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTTYPE, sTmp)
	memcpy(SDB_Serial.CERTTYPE, sTmp, sizeof(SDB_Serial.CERTTYPE)-1);
	
	/*֤������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTNO, sTmp)
	memcpy(SDB_Serial.CERTNO, sTmp, sizeof(SDB_Serial.CERTNO)-1);
	
	/*��ϵ��ʽ*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_PHONE, sTmp)
	memcpy(SDB_Serial.PHONE, sTmp, sizeof(SDB_Serial.PHONE)-1);
	
	/*�����˿ͻ�����*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTNAME, sTmp)
	memcpy(SDB_Serial.AGENTNAME, sTmp, sizeof(SDB_Serial.AGENTNAME)-1);
	
	/*������֤������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERTY, sTmp)
	memcpy(SDB_Serial.AGENTCERTY, sTmp, sizeof(SDB_Serial.AGENTCERTY)-1);
	
	/*������֤������*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERNO, sTmp)
	memcpy(SDB_Serial.AGENTCERNO, sTmp, sizeof(SDB_Serial.AGENTCERNO)-1);
	
	/*��������ϵ��ʽ*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTPHONE, sTmp)
	memcpy(SDB_Serial.AGENTPHONE, sTmp, sizeof(SDB_Serial.AGENTPHONE)-1);
	
	/*���˱�־, 0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�4-˫���޼���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CHKFLAG, sTmp)
	memcpy(SDB_Serial.CHKFLAG, sTmp, sizeof(SDB_Serial.CHKFLAG)-1);
	
	/*��ע*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_MEMO, sTmp)
	memcpy(SDB_Serial.MEMO, sTmp, sizeof(SDB_Serial.MEMO)-1);
	
	/*�����ֶ�1*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD1, sTmp)
	memcpy(SDB_Serial.EXTFLD1, sTmp, sizeof(SDB_Serial.EXTFLD1)-1);
	
	/*�����ֶ�2*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD2, sTmp)
	memcpy(SDB_Serial.EXTFLD2, sTmp, sizeof(SDB_Serial.EXTFLD2)-1);
	
	/*�����ֶ�3*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD3, sTmp)
	memcpy(SDB_Serial.EXTFLD3, sTmp, sizeof(SDB_Serial.EXTFLD3)-1);
	
	/*�����ֶ�4*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD4, sTmp)
	memcpy(SDB_Serial.EXTFLD4, sTmp, sizeof(SDB_Serial.EXTFLD4)-1);
  
  DCIBegin();
    
  memset(sErrMsg,0x00,sizeof(sErrMsg));
  iRet = DBInsert( "PABYBH_SERIAL", SD_PABYBH_SERIAL, NUMELE( SD_PABYBH_SERIAL ), &SDB_Serial,sErrMsg);
  if( iRet <= 0 )
  {
     LOG( LM_DEBUG, Fmtmsg( "������ˮ�Ǽ�ʧ��! ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
     return COMPRET_FAIL ;
  }
  if( DCICommit() != 0 )
  {
  	 DCIRollback();
     LOG( LM_DEBUG, Fmtmsg( "������ˮ�ύʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     return COMPRET_FAIL ;
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
�����������:PAB_ICC_UpdSerial
�������:PAB_ICC_UpdSerial
�������:ƽ����������ǰ�ø�����ˮ
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
IRESULT PABYBH_UpdSerial( HXMLTREE lXmlhandle )
{
  char sTmp[256+1];
  char sErrMsg[256];
  char sSql[1024*3];
  char sZwrq[30+1];
  char sZhqzlsh[30+1];
  char sRunSql[2048];
  int  iRet=0;
  int iLen=0;
  PABYBH_SERIAL SDB_Serial;
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�п�ʼ", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

	/*��ȡ��ˮ��¼��־ 0 ��¼ 1 ����¼*/
    memset(sTmp,0,sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sTmp);
    if ( ( 0 == sTmp[0] ) || ( sTmp[0] == '1' ))
    {
        LOG(LM_STD, Fmtmsg("�����ײ�����ˮ[%s]", sTmp),"")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    
  memset(sZwrq, 0x00, sizeof(sZwrq));
  memset(sZhqzlsh, 0x00, sizeof(sZhqzlsh));
  COMP_GETPARSEPARAS(1, sZwrq, "��������")
  COMP_GETPARSEPARAS(2, sZhqzlsh, "�ۺ�ǰ����ˮ��")
  trim(sZwrq);
  trim(sZhqzlsh);
 
  memset(&SDB_Serial,0x00,sizeof(SDB_Serial));
  DCIBegin();
  
  /* ��ʼ������ --B*/
    memset(sSql, 0, sizeof(sSql));
    iLen = 0; 
	
	/*����״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STAT, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.STAT, sTmp, sizeof(SDB_Serial.STAT));
	if(strlen(SDB_Serial.STAT)>0)
	{
		sprintf(sSql+iLen, "STAT='%s', ORISTAT='%s'", SDB_Serial.STAT, SDB_Serial.STAT);
		iLen=strlen(sSql);
	}
	
	/*ԭƽ̨����*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORITRANSDATE, sTmp, sizeof(SDB_Serial.ORITRANSDATE));
	if(strlen(SDB_Serial.ORITRANSDATE)>0)
	{
		sprintf(sSql+iLen, ", ORITRANSDATE='%s'", SDB_Serial.ORITRANSDATE);
		iLen=strlen(sSql);
	}
	
	/*ԭƽ̨��ˮ��*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORITRANSSERIALNO, sTmp, sizeof(SDB_Serial.ORITRANSSERIALNO));
	if(strlen(SDB_Serial.ORITRANSSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", ORITRANSSERIALNO='%s'", SDB_Serial.ORITRANSSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*���׻���*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSORG, sTmp)
	trim(sTmp);
	pstrcopy(SDB_Serial.TRANSORG, sTmp, sizeof(SDB_Serial.TRANSORG));
	if(strlen(SDB_Serial.TRANSORG)>0)
	{
		sprintf(sSql+iLen, ", TRANSORG='%s'", SDB_Serial.TRANSORG);
		iLen=strlen(sSql);
	}
	
	/*���׹�Ա*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSOPER, sTmp)
	trim(sTmp);
	pstrcopy(SDB_Serial.TRANSOPER, sTmp, sizeof(SDB_Serial.TRANSOPER));
	if(strlen(SDB_Serial.TRANSOPER)>0)
	{
		sprintf(sSql+iLen, ", TRANSOPER='%s'", SDB_Serial.TRANSOPER);
		iLen=strlen(sSql);
	}
	
	/*�������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.SVRCODE, sTmp, sizeof(SDB_Serial.SVRCODE));
	if(strlen(SDB_Serial.SVRCODE)>0)
	{
		sprintf(sSql+iLen, ", SVRCODE='%s'", SDB_Serial.SVRCODE);
		iLen=strlen(sSql);
	}
	
	/*�ͻ�����*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTNAME, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CUSTNAME, sTmp, sizeof(SDB_Serial.CUSTNAME));
	if(strlen(SDB_Serial.CUSTNAME)>0)
	{
		sprintf(sSql+iLen, ", CUSTNAME='%s'", SDB_Serial.CUSTNAME);
		iLen=strlen(sSql);
	}
	
	/*�ͻ�����00-����01-����*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTTYPE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CUSTTYPE, sTmp, sizeof(SDB_Serial.CUSTTYPE));
	if(strlen(SDB_Serial.CUSTTYPE)>0)
	{
		sprintf(sSql+iLen, ", CUSTTYPE='%s'", SDB_Serial.CUSTTYPE);
		iLen=strlen(sSql);
	}
	
	/*�����˺�*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ACCTNO, sTmp, sizeof(SDB_Serial.ACCTNO));
	if(strlen(SDB_Serial.ACCTNO)>0)
	{
		sprintf(sSql+iLen, ", ACCTNO='%s', ORIACCTNO='%s'", SDB_Serial.ACCTNO, SDB_Serial.ACCTNO);
		iLen=strlen(sSql);
	}
	
	/*�ʺ�2�������˻�*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO2, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ACCTNO2, sTmp, sizeof(SDB_Serial.ACCTNO2));
	if(strlen(SDB_Serial.ACCTNO2)>0)
	{
		sprintf(sSql+iLen, ", ACCTNO2='%s'", SDB_Serial.ACCTNO2);
		iLen=strlen(sSql);
	}
	
	/*ȯ�̴���*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STOCKCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.STOCKCODE, sTmp, sizeof(SDB_Serial.STOCKCODE));
	if(strlen(SDB_Serial.STOCKCODE)>0)
	{
		sprintf(sSql+iLen, ", STOCKCODE='%s'", SDB_Serial.STOCKCODE);
		iLen=strlen(sSql);
	}
	
	/*�ʽ��ʺ�*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CAPITALACCTNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CAPITALACCTNO, sTmp, sizeof(SDB_Serial.CAPITALACCTNO));
	if(strlen(SDB_Serial.CAPITALACCTNO)>0)
	{
		sprintf(sSql+iLen, ", CAPITALACCTNO='%s'", SDB_Serial.CAPITALACCTNO);
		iLen=strlen(sSql);
	}
	
	/*���׽��*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSAMT, sTmp);
	trim(sTmp);
	if(strlen(sTmp)>0)
	{
		SDB_Serial.TRANSAMT=atof(sTmp);
		sprintf(sSql+iLen, ", TRANSAMT='%.2lf', ORITRANSAMT='%.2lf'", SDB_Serial.TRANSAMT, SDB_Serial.TRANSAMT);
		iLen=strlen(sSql);
	}
	
	/*���2*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT2, sTmp);
	trim(sTmp);
	if(sTmp>0)
	{
		SDB_Serial.AMT2=atof(sTmp);
		sprintf(sSql+iLen, ", AMT2='%f'", SDB_Serial.AMT2);
		iLen=strlen(sSql);
	}
	
	/*���3*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT3, sTmp);
	trim(sTmp);
	if(sTmp>0)
	{
		SDB_Serial.AMT3=atof(sTmp);
		sprintf(sSql+iLen, ", AMT3='%f'", SDB_Serial.AMT3);
		iLen=strlen(sSql);
	}
	
	/*����*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURR, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CURR, sTmp, sizeof(SDB_Serial.CURR));
	if(strlen(SDB_Serial.CURR)>0)
	{
		sprintf(sSql+iLen, ", CURR='%s'", SDB_Serial.CURR);
		iLen=strlen(sSql);
	}
	
	/*�����ʶ*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CASHFLAG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CASHFLAG, sTmp, sizeof(SDB_Serial.CASHFLAG));
	if(strlen(SDB_Serial.CASHFLAG)>0)
	{
		sprintf(sSql+iLen, ", CASHFLAG='%s'", SDB_Serial.CASHFLAG);
		iLen=strlen(sSql);
	}
	
	/*��Eͨ�������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSVRCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPSVRCODE, sTmp, sizeof(SDB_Serial.IEPSVRCODE));
	if(strlen(SDB_Serial.IEPSVRCODE)>0)
	{
		sprintf(sSql+iLen, ", IEPSVRCODE='%s'", SDB_Serial.IEPSVRCODE);
		iLen=strlen(sSql);
	}
	
	/*��Eͨ���״���*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRANSCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPTRANSCODE, sTmp, sizeof(SDB_Serial.IEPTRANSCODE));
	if(strlen(SDB_Serial.IEPTRANSCODE)>0)
	{
		sprintf(sSql+iLen, ", IEPTRANSCODE='%s'", SDB_Serial.IEPTRANSCODE);
		iLen=strlen(sSql);
	}
	
	/*��Eͨҵ������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPBSIDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPBSIDATE, sTmp, sizeof(SDB_Serial.IEPBSIDATE));
	if(strlen(SDB_Serial.IEPBSIDATE)>0)
	{
		sprintf(sSql+iLen, ", IEPBSIDATE='%s'", SDB_Serial.IEPBSIDATE);
		iLen=strlen(sSql);
	}
	
	/*��Eͨ��������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRADATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPTRADATE, sTmp, sizeof(SDB_Serial.IEPTRADATE));
	if(strlen(SDB_Serial.IEPTRADATE)>0)
	{
		sprintf(sSql+iLen, ", IEPTRADATE='%s'", SDB_Serial.IEPTRADATE);
		iLen=strlen(sSql);
	}
	
	/*��Eͨ��ˮ��*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPSERIALNO, sTmp, sizeof(SDB_Serial.IEPSERIALNO));
	if(strlen(SDB_Serial.IEPSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", IEPSERIALNO='%s'", SDB_Serial.IEPSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*ԭ��Eͨҵ������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPBSIDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORIIEPBSIDATE, sTmp, sizeof(SDB_Serial.ORIIEPBSIDATE));
	if(strlen(SDB_Serial.ORIIEPBSIDATE)>0)
	{
		sprintf(sSql+iLen, ", ORIIEPBSIDATE='%s'", SDB_Serial.ORIIEPBSIDATE);
		iLen=strlen(sSql);
	}
	
	/*ԭ��Eͨ��ˮ��*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORIIEPSERIALNO, sTmp, sizeof(SDB_Serial.ORIIEPSERIALNO));
	if(strlen(SDB_Serial.ORIIEPSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", ORIIEPSERIALNO='%s'", SDB_Serial.ORIIEPSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*��Eͨ��Ӧ����*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPRESPCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPRESPCODE, sTmp, sizeof(SDB_Serial.IEPRESPCODE));
	if(strlen(SDB_Serial.IEPRESPCODE)>0)
	{
		sprintf(sSql+iLen, ", IEPRESPCODE='%s'", SDB_Serial.IEPRESPCODE);
		iLen=strlen(sSql);
	}
	
	/*��Eͨ��Ӧ��Ϣ*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPRESPMSG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPRESPMSG, sTmp, sizeof(SDB_Serial.IEPRESPMSG));
	if(strlen(SDB_Serial.IEPRESPMSG)>0)
	{
		sprintf(sSql+iLen, ", IEPRESPMSG='%s'", SDB_Serial.IEPRESPMSG);
		iLen=strlen(sSql);
	}
	
	/*������������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTBSIDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTBSIDATE, sTmp, sizeof(SDB_Serial.HOSTBSIDATE));
	if(strlen(SDB_Serial.HOSTBSIDATE)>0)
	{
		sprintf(sSql+iLen, ", HOSTBSIDATE='%s'", SDB_Serial.HOSTBSIDATE);
		iLen=strlen(sSql);
	}
	
	/*������ˮ��*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTSERIALNO, sTmp, sizeof(SDB_Serial.HOSTSERIALNO));
	if(strlen(SDB_Serial.HOSTSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", HOSTSERIALNO='%s'", SDB_Serial.HOSTSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*�������״���*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTTRANSCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTTRANSCODE, sTmp, sizeof(SDB_Serial.HOSTTRANSCODE));
	if(strlen(SDB_Serial.HOSTTRANSCODE)>0)
	{
		sprintf(sSql+iLen, ", HOSTTRANSCODE='%s'", SDB_Serial.HOSTTRANSCODE);
		iLen=strlen(sSql);
	}
	
	/*������Ӧ����*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTRESPCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTRESPCODE, sTmp, sizeof(SDB_Serial.HOSTRESPCODE));
	if(strlen(SDB_Serial.HOSTRESPCODE)>0)
	{
		sprintf(sSql+iLen, ", HOSTRESPCODE='%s'", SDB_Serial.HOSTRESPCODE);
		iLen=strlen(sSql);
	}
	
	/*������Ӧ��Ϣ*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTRESPMSG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTRESPMSG, sTmp, sizeof(SDB_Serial.HOSTRESPMSG));
	if(strlen(SDB_Serial.HOSTRESPMSG)>0)
	{
		sprintf(sSql+iLen, ", HOSTRESPMSG='%s'", SDB_Serial.HOSTRESPMSG);
		iLen=strlen(sSql);
	}
	
	/*��Ӧ��*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_RESPCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.RESPCODE, sTmp, sizeof(SDB_Serial.RESPCODE));
	if(strlen(SDB_Serial.RESPCODE)>0)
	{
		sprintf(sSql+iLen, ", RESPCODE='%s'", SDB_Serial.RESPCODE);
		iLen=strlen(sSql);
	}
	
	/*��Ӧ��Ϣ*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_RESPMSG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.RESPMSG, sTmp, sizeof(SDB_Serial.RESPMSG));
	if (strlen(SDB_Serial.RESPMSG) == (sizeof(SDB_Serial.RESPMSG) - 1))
    {
			LOG(LM_STD, Fmtmsg("У���ַ���"), "INFO")
			func_ChkZhCharGBK(lXmlhandle, SDB_Serial.RESPMSG);
    }
	if(strlen(SDB_Serial.RESPMSG)>0)
	{
		sprintf(sSql+iLen, ", RESPMSG='%s'", SDB_Serial.RESPMSG);
		iLen=strlen(sSql);
	}
	
	/*���Ľ���״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSTAT, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPSTAT, sTmp, sizeof(SDB_Serial.IEPSTAT));
	if(strlen(SDB_Serial.IEPSTAT)>0)
	{
		sprintf(sSql+iLen, ", IEPSTAT='%s'", SDB_Serial.IEPSTAT);
		iLen=strlen(sSql);
	}
	
	/*���Ľ���״̬'0�ɹ�1ʧ��6״̬δ֪7������8������9��ʼ'*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSTAT, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTSTAT, sTmp, sizeof(SDB_Serial.HOSTSTAT));
	if(strlen(SDB_Serial.HOSTSTAT)>0)
	{
		sprintf(sSql+iLen, ", HOSTSTAT='%s'", SDB_Serial.HOSTSTAT);
		iLen=strlen(sSql);
	}
	
	
	
	/*֤������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTTYPE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CERTTYPE, sTmp, sizeof(SDB_Serial.CERTTYPE));
	if(strlen(SDB_Serial.CERTTYPE)>0)
	{
		sprintf(sSql+iLen, ", CERTTYPE='%s'", SDB_Serial.CERTTYPE);
		iLen=strlen(sSql);
	}
	
	/*֤������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CERTNO, sTmp, sizeof(SDB_Serial.CERTNO));
	if(strlen(SDB_Serial.CERTNO)>0)
	{
		sprintf(sSql+iLen, ", CERTNO='%s'", SDB_Serial.CERTNO);
		iLen=strlen(sSql);
	}
	
	/*��ϵ��ʽ*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_PHONE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.PHONE, sTmp, sizeof(SDB_Serial.PHONE));
	if(strlen(SDB_Serial.PHONE)>0)
	{
		sprintf(sSql+iLen, ", PHONE='%s'", SDB_Serial.PHONE);
		iLen=strlen(sSql);
	}
	
	/*����������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTNAME, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTNAME, sTmp, sizeof(SDB_Serial.AGENTNAME));
	if(strlen(SDB_Serial.AGENTNAME)>0)
	{
		sprintf(sSql+iLen, ", AGENTNAME='%s'", SDB_Serial.AGENTNAME);
		iLen=strlen(sSql);
	}
	
	/*������֤������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERTY, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTCERTY, sTmp, sizeof(SDB_Serial.AGENTCERTY));
	if(strlen(SDB_Serial.AGENTCERTY)>0)
	{
		sprintf(sSql+iLen, ", AGENTCERTY='%s'", SDB_Serial.AGENTCERTY);
		iLen=strlen(sSql);
	}
	
	/*������֤������*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTCERNO, sTmp, sizeof(SDB_Serial.AGENTCERNO));
	if(strlen(SDB_Serial.AGENTCERNO)>0)
	{
		sprintf(sSql+iLen, ", AGENTCERNO='%s'", SDB_Serial.AGENTCERNO);
		iLen=strlen(sSql);
	}
	
	/*��������ϵ��ʽ*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTPHONE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTPHONE, sTmp, sizeof(SDB_Serial.AGENTPHONE));
	if(strlen(SDB_Serial.AGENTPHONE)>0)
	{
		sprintf(sSql+iLen, ", AGENTPHONE='%s'", SDB_Serial.AGENTPHONE);
		iLen=strlen(sSql);
	}
	
	/*��ע*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_MEMO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.MEMO, sTmp, sizeof(SDB_Serial.MEMO));
	if(strlen(SDB_Serial.MEMO)>0)
	{
		sprintf(sSql+iLen, ", MEMO='%s'", SDB_Serial.MEMO);
		iLen=strlen(sSql);
	}
	
	/*�����ֶ�1*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD1, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD1, sTmp, sizeof(SDB_Serial.EXTFLD1));
	if(strlen(SDB_Serial.EXTFLD1)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD1='%s'", SDB_Serial.EXTFLD1);
		iLen=strlen(sSql);
	}
	
	/*�����ֶ�2*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD2, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD2, sTmp, sizeof(SDB_Serial.EXTFLD2));
	if(strlen(SDB_Serial.EXTFLD2)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD2='%s'", SDB_Serial.EXTFLD2);
		iLen=strlen(sSql);
	}
	
	/*�����ֶ�3*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD3, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD3, sTmp, sizeof(SDB_Serial.EXTFLD3));
	if(strlen(SDB_Serial.EXTFLD3)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD3='%s'", SDB_Serial.EXTFLD3);
		iLen=strlen(sSql);
	}
	
	/*�����ֶ�4*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD4, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD4, sTmp, sizeof(SDB_Serial.EXTFLD4));
	if(strlen(SDB_Serial.EXTFLD4)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD4='%s'", SDB_Serial.EXTFLD4);
		iLen=strlen(sSql);
	}
   
  memset(sErrMsg,0x00,sizeof(sErrMsg));
  memset(sRunSql,0x00,sizeof(sRunSql));
  sprintf(sRunSql,"update PABYBH_SERIAL set %s where transDate ='%s' and transSerialNo ='%s'", sSql, sZwrq, sZhqzlsh);
  LOG(LM_DEBUG,Fmtmsg("sql���=[%s]",sRunSql),"DEBUG")
  iRet = DCIExecuteDirect(sRunSql);
  if( iRet <= 0 )
  {
  	DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "������Eͨǰ����ˮʧ��! ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL ;
  }
 
  if( DCICommit() != 0 )
  {
  	DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "������Eͨǰ����ˮʧ�� ������=[%d]������Ϣ=[%s]",iRet,DCILastError()), "INFO" );
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL ;
  }
  
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "���[%s]ִ�н���", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}

