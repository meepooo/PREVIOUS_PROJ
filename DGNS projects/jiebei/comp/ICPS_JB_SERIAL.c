#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "../incl/ICPS_JB_HEAD.h"

/************************************************************************
��̬�����������
�����������:ICPS_SERIAL_INSERT
�������:ICPS_SERIAL_INSERT
�������: �Ǽ���ˮ��
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_SERIAL_INSERT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_SERIAL sdb_icps_serial;

    fpub_InitSoComp(lXmlhandle);

    /*��ȡ��ˮ��¼��־ 0 ��¼ 1 ����¼*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sBuf);
    trim(sBuf);
    if ((0 == sBuf[0]) || ('1' == sBuf[0]))
    {
        LOG(LM_STD, Fmtmsg("�����ײ�����ˮ[%s]", sBuf), "INFO")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    memset(&sdb_icps_serial, 0, sizeof(sdb_icps_serial));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_serial.plt_date, "ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_TIME, sdb_icps_serial.plt_time, "ƽ̨ʱ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_serial.plt_serial, "ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_BUSI_DATE, sdb_icps_serial.busi_date, "ҵ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_BUSI_NO, sdb_icps_serial.busi_no, "ҵ����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_CHANNEL, sdb_icps_serial.channel, "��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_LOCAL_ID, sdb_icps_serial.local_id, "���л�����ʶ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_TRANS_CODE, sdb_icps_serial.trans_code, "ƽ̨���״���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_RECV_FLAG, sdb_icps_serial.send_recv_flag, "�����˱�־");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_serial.apply_no, "���뵥��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_VERSION, sdb_icps_serial.version, "�汾��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_TIME_ZONE, sdb_icps_serial.send_time_zone, "���ͷ�����ʱ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_DTTM, sdb_icps_serial.send_dttm, "���ķ���ʱ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_MSG_ID, sdb_icps_serial.msg_id, "�����ı�ʾ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_ID, sdb_icps_serial.third_id, "������������ʶ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_TRANS_CODE, sdb_icps_serial.third_trans_code, "���������״���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_RESPCODE, sdb_icps_serial.third_respcode, "��������Ӧ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_RESPMSG, sdb_icps_serial.third_respmsg, "��������Ӧ��Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_TRANS_STATUS, sdb_icps_serial.third_trans_status, "����������״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_RETRY, sdb_icps_serial.retry, "�Ƿ���Ҫ���Ա��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_HOST_SERIAL, sdb_icps_serial.send_host_serial, "����������ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_HOST_DATE, sdb_icps_serial.send_host_date, "������������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_SERIAL, sdb_icps_serial.host_serial, "������ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_DATE, sdb_icps_serial.host_date, "��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_TRANS_CODE, sdb_icps_serial.host_trans_code, "�������״���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_RESPCODE, sdb_icps_serial.host_respcode, "������Ӧ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_RESPMSG, sdb_icps_serial.host_respmsg, "������Ӧ��Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_STATUS, sdb_icps_serial.host_status, "��������״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_IN_CHANNEL_DATE, sdb_icps_serial.in_channel_date, "������������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_IN_CHANNEL_SERIAL, sdb_icps_serial.in_channel_serial, "����������ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_RESPCODE, sdb_icps_serial.respcode, "������Ӧ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_RESPMSG, sdb_icps_serial.respmsg, "������Ӧ��Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_TRANS_STATUS, sdb_icps_serial.trans_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_BRANCH, sdb_icps_serial.branch, "���׻���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_TELLER, sdb_icps_serial.teller, "���׹�Ա");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_GRANT_BRANCH, sdb_icps_serial.grant_branch, "��Ȩ����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_GRANT_TELLER, sdb_icps_serial.grant_teller, "��Ȩ��Ա");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM1, sdb_icps_serial.extend_param1, "��չ1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM2, sdb_icps_serial.extend_param2, "��չ2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM3, sdb_icps_serial.extend_param3, "��չ3");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM4, sdb_icps_serial.extend_param4, "��չ4");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM5, sdb_icps_serial.extend_param5, "��չ5");

    iRet = APP_DBInsert("ICPS_SERIAL", SD_ICPS_SERIAL, NUMELE(SD_ICPS_SERIAL), &sdb_icps_serial, sErrmsg);
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
    return COMPRET_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:ICPS_SERIAL_UPDATE
 �������:ICPS_SERIAL_UPDATE
 �������: ������ˮ��
 �������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
 ʹ������:
 �� �� Ա:
 ��������:2009��12��11��
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT ICPS_SERIAL_UPDATE(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    char sSql_Buf[64];
    char sSql_Values[4096];
    char sSql_Where[256];
    ICPS_SERIAL sdb_icps_serial;

    fpub_InitSoComp(lXmlhandle);

    /*��ȡ��ˮ��¼��־ 0 ��¼ 1 ����¼*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sBuf);
    trim(sBuf);
    if ((0 == sBuf[0]) || ('1' == sBuf[0]))
    {
        LOG(LM_STD, Fmtmsg("�����ײ�����ˮ[%s]", sBuf), "INFO")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    memset(&sdb_icps_serial, 0, sizeof(sdb_icps_serial));
    memset(sSql_Values, 0, sizeof(sSql_Values));

    snprintf(sSql_Values, sizeof(sSql_Values), "UPDATE ICPS_SERIAL SET ");

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_serial.plt_date, "ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_serial.plt_serial, "ƽ̨��ˮ��");

    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_BUSI_DATE, sSql_Values, sSql_Buf, "BUSI_DATE", "ҵ������");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_BUSI_NO, sSql_Values, sSql_Buf, "BUSI_NO", "ҵ����");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_CHANNEL, sSql_Values, sSql_Buf, "CHANNEL", "��������");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_LOCAL_ID, sSql_Values, sSql_Buf, "LOCAL_ID", "���л�����ʶ");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_TRANS_CODE, sSql_Values, sSql_Buf, "TRANS_CODE", "ƽ̨���״���");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_RECV_FLAG, sSql_Values, sSql_Buf, "SEND_RECV_FLAG", "�����˱�־");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_APPLY_NO, sSql_Values, sSql_Buf, "APPLY_NO", "���뵥��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_VERSION, sSql_Values, sSql_Buf, "VERSION", "�汾��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_TIME_ZONE, sSql_Values, sSql_Buf, "SEND_TIME_ZONE", "���ͷ�����ʱ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_DTTM, sSql_Values, sSql_Buf, "SEND_DTTM", "���ķ���ʱ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_MSG_ID, sSql_Values, sSql_Buf, "MSG_ID", "�����ı�ʾ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_ID, sSql_Values, sSql_Buf, "THIRD_ID", "������������ʶ");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_TRANS_CODE, sSql_Values, sSql_Buf, "THIRD_TRANS_CODE", "���������״���");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_RESPCODE, sSql_Values, sSql_Buf, "THIRD_RESPCODE", "��������Ӧ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_RESPMSG, sSql_Values, sSql_Buf, "THIRD_RESPMSG", "��������Ӧ��Ϣ");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_TRANS_STATUS, sSql_Values, sSql_Buf, "THIRD_TRANS_STATUS", "����������״̬");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_RETRY, sSql_Values, sSql_Buf, "RETRY", "�Ƿ���Ҫ���Ա��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_HOST_SERIAL, sSql_Values, sSql_Buf, "SEND_HOST_SERIAL", "����������ˮ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_HOST_DATE, sSql_Values, sSql_Buf, "SEND_HOST_DATE", "������������");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_SERIAL, sSql_Values, sSql_Buf, "HOST_SERIAL", "������ˮ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_DATE, sSql_Values, sSql_Buf, "HOST_DATE", "��������");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_TRANS_CODE, sSql_Values, sSql_Buf, "HOST_TRANS_CODE", "�������״���");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_RESPCODE, sSql_Values, sSql_Buf, "HOST_RESPCODE", "������Ӧ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_RESPMSG, sSql_Values, sSql_Buf, "HOST_RESPMSG", "������Ӧ��Ϣ");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_STATUS, sSql_Values, sSql_Buf, "HOST_STATUS", "��������״̬");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_RESPCODE, sSql_Values, sSql_Buf, "RESPCODE", "������Ӧ��");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_RESPMSG, sSql_Values, sSql_Buf, "RESPMSG", "������Ӧ��Ϣ");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_TRANS_STATUS, sSql_Values, sSql_Buf, "TRANS_STATUS", "����״̬");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_BRANCH, sSql_Values, sSql_Buf, "BRANCH", "���׻���");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_TELLER, sSql_Values, sSql_Buf, "TELLER", "���׹�Ա");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_GRANT_BRANCH, sSql_Values, sSql_Buf, "GRANT_BRANCH", "��Ȩ����");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_GRANT_TELLER, sSql_Values, sSql_Buf, "GRANT_TELLER", "��Ȩ��Ա");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM1, sSql_Values, sSql_Buf, "EXTEND_PARAM1", "��չ1");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM2, sSql_Values, sSql_Buf, "EXTEND_PARAM2", "��չ2");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM3, sSql_Values, sSql_Buf, "EXTEND_PARAM3", "��չ3");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM4, sSql_Values, sSql_Buf, "EXTEND_PARAM4", "��չ4");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM5, sSql_Values, sSql_Buf, "EXTEND_PARAM5", "��չ5");

    sSql_Values[strlen(sSql_Values) - 1] = '\0'; /*ȥ�����һ��","*/

    snprintf(sSql_Where, sizeof(sSql_Where), " WHERE PLT_DATE='%s' AND PLT_SERIAL='%s' ", sdb_icps_serial.plt_date,
            sdb_icps_serial.plt_serial);
    strcat(sSql_Values, sSql_Where);
    LOG(LM_STD, Fmtmsg("sSql_Values[%s]", sSql_Values), "INFO");
    DCIBegin();
    iRet = DCIExecuteDirect(sSql_Values);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ���²���ʧ��, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    /* �ύ���� */
    if (DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ��ύ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    if (iRet == 0)
    {
        LOG(LM_STD, Fmtmsg("���²����޷��������ļ�¼"), "INFO")
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_NORECORD);
        return ICPS_COMPSTATUS_SQL_NORECORD;
    }

    fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_SUCC);
    return ICPS_COMPSTATUS_SQL_SUCC;
}

/************************************************************************
��̬�����������
�����������:ICPS_EXECUPD
�������:ICPS_EXECUPD
�������:ִ�и������
�������:sql���

��ע��

�� Ŀ ��:
�� �� Ա:
��������:2015��6��2��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_EXECUPD(HXMLTREE lXmlhandle)
{
    int iRet, iParas;
    char sBuf[256];
    char sUpdSql[4096];

    COMP_PARACOUNTCHKMIN(1);

    memset(sUpdSql, 0, sizeof(sUpdSql));
    COMP_GETPARSEPARAS(1, sUpdSql, "ִ�����")
    trim(sUpdSql);
    if (0 == sUpdSql[0]) /*ִ����䲻��Ϊ��*/
    {
        fpub_SetMsg(lXmlhandle, 99999, "PARA NULL ERR!");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("�������:[%s]", sUpdSql), "INFO");

    DCIBegin();
    iRet = DCIExecuteDirect(sUpdSql);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ���²���ʧ��, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    /* �ύ���� */
    if (DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ��ύ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    if (iRet == 0)
    {
        LOG(LM_STD, Fmtmsg("���²����޷��������ļ�¼"), "INFO")
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_NORECORD);
        return ICPS_COMPSTATUS_SQL_NORECORD;
    }

    fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_SUCC);
    return ICPS_COMPSTATUS_SQL_SUCC;
}

