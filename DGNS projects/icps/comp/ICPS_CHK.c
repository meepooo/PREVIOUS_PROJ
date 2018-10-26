#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"

/************************************************************************
��̬�����������
�����������:ICPS_DAILYSTATUS_INSERT
�������:ICPS_DAILYSTATUS_INSERT
�������: �Ǽ�����״̬��
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_DAILYSTATUS_INSERT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_DAILY_STATUS sdb_icps_daily_status;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_daily_status, 0, sizeof(sdb_icps_daily_status));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_BUSI_DATE, sdb_icps_daily_status.busi_date, "ҵ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_BUSI_NO, sdb_icps_daily_status.busi_no, "ҵ����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_FILE_STEP, sdb_icps_daily_status.file_step, "�ļ�����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_TOTAL_CHECK_STATUS, sdb_icps_daily_status.third_total_check_status, "������������״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_DETAIL_CHECK_STATUS, sdb_icps_daily_status.third_detail_check_status, "��������ϸ����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_TOTAL_CHECK_STATUS, sdb_icps_daily_status.host_total_check_status, "���Ķ�����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_DETAIL_CHECK_STATUS, sdb_icps_daily_status.host_detail_check_status, "������ϸ����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_PRE_TOTAL_CHECK_STATUS, sdb_icps_daily_status.third_pre_total_check_status, "������Ԥ������״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_PRE_DETAIL_CHECK_STATUS, sdb_icps_daily_status.third_pre_detail_check_status, "������Ԥ��ϸ����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_PRE_TOTAL_CHECK_STATUS, sdb_icps_daily_status.host_pre_total_check_status, "����Ԥ������״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_PRE_DETAIL_CHECK_STATUS, sdb_icps_daily_status.host_pre_detail_check_status, "����Ԥ��ϸ����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_CLEAR_STATUS, sdb_icps_daily_status.clear_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_PLT_DATE, sdb_icps_daily_status.plt_date, "ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_PLT_SERIAL, sdb_icps_daily_status.plt_serial, "ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_SEND_HOST_DATE, sdb_icps_daily_status.send_host_date, "������������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_SERIAL, sdb_icps_daily_status.host_serial, "������ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_DATE, sdb_icps_daily_status.host_date, "��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_RESPCODE, sdb_icps_daily_status.respcode, "������Ӧ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_RESPMSG, sdb_icps_daily_status.respmsg, "������Ӧ��Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_TRANS_STATUS, sdb_icps_daily_status.trans_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_BRANCH, sdb_icps_daily_status.branch, "���׻���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_TELLER, sdb_icps_daily_status.teller, "���׹�Ա");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM1, sdb_icps_daily_status.extend_param1, "��չ1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM2, sdb_icps_daily_status.extend_param2, "��չ2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM3, sdb_icps_daily_status.extend_param3, "��չ3");

    iRet = APP_DBInsert("ICPS_DAILY_STATUS", SD_ICPS_DAILY_STATUS, NUMELE(SD_ICPS_DAILY_STATUS), &sdb_icps_daily_status, sErrmsg);
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


