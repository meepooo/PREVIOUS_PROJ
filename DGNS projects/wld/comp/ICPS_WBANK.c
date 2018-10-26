
#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"

/************************************************************************
��̬�����������
�����������:ICPS_FILE_CHECK
�������:ICPS_FILE_CHECK
�������: �Ǽ�����״̬��
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_FILE_CHECK(HXMLTREE lXmlhandle)
{
	CURSOR cur;
    char sErrmsg[512];
    char s
    fpub_InitSoComp(lXmlhandle);


    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* �ύ���� */
    if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}


