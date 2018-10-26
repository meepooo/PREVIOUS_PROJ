#include "gaps_head.h"


/************************************************************************
��̬�����������
�����������: SYW_TIPS_GENZHQZLSH_EH
�������: �����ۺ�ǰ����ˮ�ţ���Ӧ����ģʽ����Ⱥģʽ
�������: 
  ���ɷ�������ˮ��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: zhangl
��������: 2017��05��2��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_GENZHQZLSH_EH(HXMLTREE lXmlhandle)
{
    int iParas;
	char sBuf[255];
	int iMode;
	char xmlNode[255];
	int iret = 0;
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("������ˮ�ſ�ʼ"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(2)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"ģʽ");
    trim(sBuf);
    iMode = atoi(sBuf);
	
    memset(sBuf, 0x00, sizeof(sBuf));
	memset(xmlNode, 0x00, sizeof(xmlNode));
    COMP_GETPARSEPARAS(2,sBuf,"ǰ����ˮ��·��");
    trim(sBuf);
    strncpy(xmlNode, sBuf, sizeof(xmlNode)-1);

	memset(sBuf, 0x00 ,sizeof(sBuf));
	if (0 == iMode) {
		iret = prv_GenSerinoSingle(lXmlhandle, sBuf, sizeof(sBuf));
	}
	else if (1 == iMode) {
		iret = prv_GenSerinoHA(lXmlhandle, sBuf, sizeof(sBuf));
	}
	else {
		fpub_SetMsg(lXmlhandle, -1, "������ˮ��ʧ��");
    	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	if (iret < 0) {
		fpub_SetMsg(lXmlhandle, -1, "������ˮ��ʧ��");
    	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	snprintf(sBuf, sizeof(sBuf), "%d", iret);
	COMP_HARDSETXML(xmlNode, sBuf);
    fpub_SetMsg(lXmlhandle, 0, "���ɷ�������ˮ��");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("������ˮ�Ž���"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}   

