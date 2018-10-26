#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include "../incl/cJSON.h"

/************************************************************************
��̬�����������
�����������:ICPS_APPLY_INSERT
�������:ICPS_APPLY_INSERT
�������: �Ǽ���Ȩ������ˮ��
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_APPLY_INSERT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_APPLY sdb_icps_apply;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_apply, 0, sizeof(sdb_icps_apply));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_BUSI_NO, sdb_icps_apply.busi_no, "ҵ����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_NO, sdb_icps_apply.apply_no, "���뵥��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_TYPE, sdb_icps_apply.id_type, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_NUM, sdb_icps_apply.id_num, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_VALID_END_DATE, sdb_icps_apply.id_valid_end_date, "֤����Ч��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_NAME, sdb_icps_apply.name, "����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_MOBILE_NO, sdb_icps_apply.mobile_no, "�ֻ���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_AUTH_FLAG, sdb_icps_apply.auth_flag, "֥����Ȩ�ɹ���ʶ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_HAS_ADMIT_FLAG, sdb_icps_apply.has_admit_flag, "֮ǰ�Ƿ��ж��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_DATE, sdb_icps_apply.apply_plt_date, "��������ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_SERIAL, sdb_icps_apply.apply_plt_serial, "��������ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_STATUS, sdb_icps_apply.apply_status, "��������״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CREDIT_NO, sdb_icps_apply.credit_no, "���ű��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_ADMIT_FLAG, sdb_icps_apply.info_admit_flag, "�����Ƿ��Ƽ�׼��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_AMT, sdb_icps_apply.credit_amt, "�Ƽ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_RATE, sdb_icps_apply.credit_rate, "�Ƽ�����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_CODE, sdb_icps_apply.refuse_code, "�ܾ���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_REASON, sdb_icps_apply.refuse_reason, "�ܾ�ԭ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_DATE, sdb_icps_apply.info_plt_date, "���г���ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_SERIAL, sdb_icps_apply.info_plt_serial, "���г���ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_STATUS, sdb_icps_apply.info_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_ACCESS, sdb_icps_apply.third_access, "�Ƿ�ͨ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_REFUSE_REASON, sdb_icps_apply.third_refuse_reason, "������ͨ��ԭ��");
    ICPS_GETXMLNODE_MONEY(XMLNM_ICPS_APPLY_THIRD_AMT, sdb_icps_apply.third_amt, "�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_THIRD_RATE, sdb_icps_apply.third_rate, "������������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_RISK_RATING, sdb_icps_apply.risk_rating, "��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_SOLVENCY_RATING, sdb_icps_apply.solvency_rating, "��ծ��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CHANGE_RESULT_REASON, sdb_icps_apply.change_result_reason, "��ȶ��۱��ԭ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_FLAG, sdb_icps_apply.ack_admit_flag, "���������Ƿ�׼��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_MSG, sdb_icps_apply.ack_admit_msg, "׼��ԭ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_DATE, sdb_icps_apply.ack_plt_date, "����ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_SERIAL, sdb_icps_apply.ack_plt_serial, "����ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_STATUS, sdb_icps_apply.ack_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM1, sdb_icps_apply.extend_param1, "��չ1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM2, sdb_icps_apply.extend_param2, "��չ2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM3, sdb_icps_apply.extend_param3, "��չ3");

    iRet = APP_DBInsert("ICPS_APPLY", SD_ICPS_APPLY, NUMELE(SD_ICPS_APPLY), &sdb_icps_apply, sErrmsg);
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
 �����������:ICPS_APPLY_UPDATE
 �������:ICPS_APPLY_UPDATE
 �������: ������ˮ��
 �������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
 ʹ������:
 �� �� Ա:
 ��������:2009��12��11��
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT ICPS_APPLY_UPDATE(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    char sSql_Where[256];
    ICPS_APPLY sdb_icps_apply;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_apply, 0, sizeof(sdb_icps_apply));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_BUSI_NO, sdb_icps_apply.busi_no, "ҵ����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_NO, sdb_icps_apply.apply_no, "���뵥��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_TYPE, sdb_icps_apply.id_type, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_NUM, sdb_icps_apply.id_num, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_VALID_END_DATE, sdb_icps_apply.id_valid_end_date, "֤����Ч��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_NAME, sdb_icps_apply.name, "����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_MOBILE_NO, sdb_icps_apply.mobile_no, "�ֻ���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_AUTH_FLAG, sdb_icps_apply.auth_flag, "֥����Ȩ�ɹ���ʶ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_HAS_ADMIT_FLAG, sdb_icps_apply.has_admit_flag, "֮ǰ�Ƿ��ж��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_DATE, sdb_icps_apply.apply_plt_date, "��������ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_SERIAL, sdb_icps_apply.apply_plt_serial, "��������ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_STATUS, sdb_icps_apply.apply_status, "��������״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CREDIT_NO, sdb_icps_apply.credit_no, "���ű��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_ADMIT_FLAG, sdb_icps_apply.info_admit_flag, "�����Ƿ��Ƽ�׼��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_AMT, sdb_icps_apply.credit_amt, "�Ƽ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_RATE, sdb_icps_apply.credit_rate, "�Ƽ�����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_CODE, sdb_icps_apply.refuse_code, "�ܾ���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_REASON, sdb_icps_apply.refuse_reason, "�ܾ�ԭ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_DATE, sdb_icps_apply.info_plt_date, "���г���ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_SERIAL, sdb_icps_apply.info_plt_serial, "���г���ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_STATUS, sdb_icps_apply.info_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_ACCESS, sdb_icps_apply.third_access, "�Ƿ�ͨ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_REFUSE_REASON, sdb_icps_apply.third_refuse_reason, "������ͨ��ԭ��");
    ICPS_GETXMLNODE_MONEY(XMLNM_ICPS_APPLY_THIRD_AMT, sdb_icps_apply.third_amt, "�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_THIRD_RATE, sdb_icps_apply.third_rate, "������������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_RISK_RATING, sdb_icps_apply.risk_rating, "��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_SOLVENCY_RATING, sdb_icps_apply.solvency_rating, "��ծ��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CHANGE_RESULT_REASON, sdb_icps_apply.change_result_reason, "��ȶ��۱��ԭ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_FLAG, sdb_icps_apply.ack_admit_flag, "���������Ƿ�׼��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_MSG, sdb_icps_apply.ack_admit_msg, "׼��ԭ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_DATE, sdb_icps_apply.ack_plt_date, "����ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_SERIAL, sdb_icps_apply.ack_plt_serial, "����ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_STATUS, sdb_icps_apply.ack_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM1, sdb_icps_apply.extend_param1, "��չ1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM2, sdb_icps_apply.extend_param2, "��չ2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM3, sdb_icps_apply.extend_param3, "��չ3");

    snprintf(sSql_Where, sizeof(sSql_Where), " BUSI_NO='%s' AND APPLY_NO='%s'", sdb_icps_apply.busi_no, sdb_icps_apply.apply_no);

    iRet = APP_DBUpdate("ICPS_APPLY", SD_ICPS_APPLY, NUMELE(SD_ICPS_APPLY), &sdb_icps_apply, sSql_Where, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ���²���ʧ��, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    /* �ύ���� */
    if (DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ��ύ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    if (iRet == 0)
    {
        LOG(LM_STD, Fmtmsg("���²����޷��������ļ�¼[%s]", sSql_Where), "INFO")
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_NORECORD);
        return ICPS_COMPSTATUS_SQL_NORECORD;
    }

    fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_SUCC);
    return ICPS_COMPSTATUS_SQL_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:ICPS_APPLY_ZM_INFO_INS
 �������:ICPS_APPLY_ZM_INFO_INS
 �������: �Ǽ�֥��������Ϣ
 �������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
 ʹ������:
 �� �� Ա:
 ��������:2009��12��11��
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT ICPS_APPLY_ZM_INFO_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_ZM_CREDIT sdb_icps_zm_credit;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_zm_credit, 0, sizeof(sdb_icps_zm_credit));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_zm_credit.apply_no, "���뵥��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_zm_credit.plt_date, "ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_zm_credit.plt_serial, "ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_ID_TYPE, sdb_icps_zm_credit.id_type, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_ID_NUM, sdb_icps_zm_credit.id_num, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_COMPANY_NAME, sdb_icps_zm_credit.company_name, "���ڹ�˾");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_OCCUPATION, sdb_icps_zm_credit.occupation, "ְҵ����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_HAVE_CAR_FLAG, sdb_icps_zm_credit.have_car_flag, "�Ƿ��г�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_HAVE_HOUSE_FLAG, sdb_icps_zm_credit.have_house_flag, "�Ƿ��з�");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_AUTH_FIN_LAST_1M_CNT, sdb_icps_zm_credit.auth_fin_last_1m_cnt, "���һ����������ѯ���ڻ�����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_AUTH_FIN_LAST_3M_CNT, sdb_icps_zm_credit.auth_fin_last_3m_cnt, "���������������ѯ���ڻ�����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_AUTH_FIN_LAST_6M_CNT, sdb_icps_zm_credit.auth_fin_last_6m_cnt, "���������������ѯ���ڻ�����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_OVD_ORDER_CNT_6M, sdb_icps_zm_credit.ovd_order_cnt_6m, "��������������ܱ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_ZMINFO_OVD_ORDER_AMT_6M, sdb_icps_zm_credit.ovd_order_amt_6m, "��������������ܽ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_MOBILE_FIXED_DAYS, sdb_icps_zm_credit.mobile_fixed_days, "�ֻ����ȶ�����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_ADR_STABILITY_DAYS, sdb_icps_zm_credit.adr_stability_days, "��ַ�ȶ�����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_ZMINFO_LAST_6M_AVG_ASSET_TOTAL, sdb_icps_zm_credit.last_6m_avg_asset_total, "��������������ʲ��վ�ֵ");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_ZMINFO_TOT_PAY_AMT_6M, sdb_icps_zm_credit.tot_pay_amt_6m, "���������֧���ܽ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_XFDC_INDEX, sdb_icps_zm_credit.xfdc_index, "���ѵ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_POSITIVE_BIZ_CNT_1Y, sdb_icps_zm_credit.positive_biz_cnt_1y, "���һ����Լ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_EXTEND_PARAM1, sdb_icps_zm_credit.extend_param1, "��չ1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_EXTEND_PARAM2, sdb_icps_zm_credit.extend_param2, "��չ2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_EXTEND_PARAM3, sdb_icps_zm_credit.extend_param3, "��չ3");

    iRet = APP_DBInsert("ICPS_ZM_CREDIT", SD_ICPS_ZM_CREDIT, NUMELE(SD_ICPS_ZM_CREDIT), &sdb_icps_zm_credit, sErrmsg);
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


/************************************************************************
 ��̬�����������
 �����������:ICPS_APPLY_PBOC_INFO_INS
 �������:ICPS_APPLY_PBOC_INFO_INS
 �������: �Ǽ�����������Ϣ
 �������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
 ʹ������:
 �� �� Ա:
 ��������:2009��12��11��
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT ICPS_APPLY_PBOC_INFO_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_PBOC_CREDIT sdb_icps_pboc_credit;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_pboc_credit, 0, sizeof(sdb_icps_pboc_credit));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_pboc_credit.apply_no, "���뵥��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_pboc_credit.plt_date, "ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_pboc_credit.plt_serial, "ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_ID_TYPE, sdb_icps_pboc_credit.id_type, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_ID_NUM, sdb_icps_pboc_credit.id_num, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_QUERY_NO, sdb_icps_pboc_credit.query_no, "��ѯ���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_QUERY_FLAG, sdb_icps_pboc_credit.query_flag, "��ѯ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_MANAGE_LAST_12_QRY_CNT, sdb_icps_pboc_credit.manage_last_12_qry_cnt, "����������12���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_MANAGE_LAST_3_QRY_CNT, sdb_icps_pboc_credit.manage_last_3_qry_cnt, "����������3���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_MANAGE_LAST_6_QRY_CNT, sdb_icps_pboc_credit.manage_last_6_qry_cnt, "����������6���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_12_QRY_CNT, sdb_icps_pboc_credit.approve_last_12_qry_cnt, "�����������12���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_3_QRY_CNT, sdb_icps_pboc_credit.approve_last_3_qry_cnt, "�����������3���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_6_QRY_CNT, sdb_icps_pboc_credit.approve_last_6_qry_cnt, "�����������6���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_30D_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_30d_qry_org_cnt, "�����������1���²�ѯ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_12_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_12_qry_org_cnt, "�����������12���²�ѯ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_3_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_3_qry_org_cnt, "�����������3���²�ѯ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_6_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_6_qry_org_cnt, "�����������6���²�ѯ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_12_QRY_CNT, sdb_icps_pboc_credit.card_last_12_qry_cnt, "���ÿ��������12���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_3_QRY_CNT, sdb_icps_pboc_credit.card_last_3_qry_cnt, "���ÿ��������3���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_6_QRY_CNT, sdb_icps_pboc_credit.card_last_6_qry_cnt, "���ÿ��������6���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_30D_QRY_ORG_CNT, sdb_icps_pboc_credit.card_last_30d_qry_org_cnt, "���ÿ��������1���²�ѯ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_3_QRY_ORG_CNT, sdb_icps_pboc_credit.card_last_3_qry_org_cnt, "���ÿ��������3���²�ѯ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_6_QRY_ORG_CNT, sdb_icps_pboc_credit.card_last_6_qry_org_cnt, "���ÿ��������6���²�ѯ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_ALL_LOAN_NUM, sdb_icps_pboc_credit.all_loan_num, "�ܴ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CAR_LOAN_NUM, sdb_icps_pboc_credit.car_loan_num, "��������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_BIZ_LOAN_NUM, sdb_icps_pboc_credit.biz_loan_num, "��Ӫ�������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_HOUSE_LOAN_NUM, sdb_icps_pboc_credit.house_loan_num, "��������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_ALL_LOAN_NUM, sdb_icps_pboc_credit.os_all_loan_num, "δ����������ʻ������ܱ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_CAR_LOAN_NUM, sdb_icps_pboc_credit.os_car_loan_num, "δ���峵������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_HOUSE_LOAN_NUM, sdb_icps_pboc_credit.os_house_loan_num, "δ���巿������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_BIZ_LOAN_NUM, sdb_icps_pboc_credit.os_biz_loan_num, "δ���徭Ӫ�������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_CON13_CNT_SUM, sdb_icps_pboc_credit.ln_nca_con13_cnt_sum, "δ����������Ѵ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_CRD_CNT_SUM, sdb_icps_pboc_credit.ln_nca_crd_cnt_sum, "δ�������ô������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_MAX_AMOUNT, sdb_icps_pboc_credit.loan_max_amount, "������߶��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_OPER_MAX_AMOUNT, sdb_icps_pboc_credit.loan_oper_max_amount, "��Ӫ�Դ�����߶��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_BALANCE_SUM, sdb_icps_pboc_credit.balance_sum, "δ������������ܺ�");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_SUM_AMOUNT, sdb_icps_pboc_credit.loan_sum_amount, "δ����������ܺ�");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_AMT_AVG, sdb_icps_pboc_credit.ln_nca_amt_avg, "δ�������ƽ����ͬ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_HOUSE_AMT_SUM, sdb_icps_pboc_credit.loan_house_amt_sum, "δ���巿����ͬ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_HOUSE_BAL_SUM, sdb_icps_pboc_credit.loan_house_bal_sum, "δ���巿�����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_BUSINESS_LOAN_SUM_AMOUNT, sdb_icps_pboc_credit.business_loan_sum_amount, "δ���徭Ӫ�����ͬ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_BUSINESS_LOAN_SUM_BALANCE, sdb_icps_pboc_credit.business_loan_sum_balance, "δ���徭Ӫ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_CON13_BAL_SUM, sdb_icps_pboc_credit.ln_nca_con13_bal_sum, "δ����������Ѵ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_RMM_AVG, sdb_icps_pboc_credit.ln_nca_rmm_avg, "δ�������ƽ��ʣ�໹������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_PMM_AVG, sdb_icps_pboc_credit.ln_nca_pmm_avg, "δ�������ƽ����������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_PMO_AVG, sdb_icps_pboc_credit.ln_nca_pmo_avg, "����δ�������ƽ��Ӧ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_PMT_SUM, sdb_icps_pboc_credit.ln_nca_pmt_sum, "δ����������ʵ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_REPAY_CAR_MON, sdb_icps_pboc_credit.repay_car_mon, "�¶ȳ�������Ӧ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_REPAY_HOUSE_MON, sdb_icps_pboc_credit.repay_house_mon, "�¶ȷ�������Ӧ����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_M1_MAX_3M, sdb_icps_pboc_credit.ln_nca_m1_max_3m, "δ��������3����������ڴ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_OVD_MAX_BAL_CPT, sdb_icps_pboc_credit.loan_ovd_max_bal_cpt, "�����������ڽ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_CUR_OVD_AMOUNT, sdb_icps_pboc_credit.loan_cur_ovd_amount, "���ǰ�����ܽ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_CD_MAX_24M, sdb_icps_pboc_credit.ln_cd_max_24m, "�����24���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_CD_MAX, sdb_icps_pboc_credit.ln_cd_max, "��ǰ���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LOAN_DELQ_12MTH_MAX, sdb_icps_pboc_credit.loan_delq_12mth_max, "δ��������12���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LOAN_DELQ_3MTH_MAX, sdb_icps_pboc_credit.loan_delq_3mth_max, "δ��������3���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LOAN_DELQ_6MTH_MAX, sdb_icps_pboc_credit.loan_delq_6mth_max, "δ��������6���������������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_CLASS_5_CREDIT_MORTGAGE, sdb_icps_pboc_credit.class_5_credit_mortgage, "���������������������弶����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_CLASS_5_NOT_MORTGAGE, sdb_icps_pboc_credit.class_5_not_mortgage, "�ǰ��������������������弶����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_DULL_LOAN_NUM, sdb_icps_pboc_credit.dull_loan_num, "�������ô������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_DULL_LOAN_SUM, sdb_icps_pboc_credit.dull_loan_sum, "���˵Ĵ�����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_ALL_ASSURE_LOAN_NUM, sdb_icps_pboc_credit.all_assure_loan_num, "�ܵ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ALL_ASSURE_LOAN_SUM, sdb_icps_pboc_credit.all_assure_loan_sum, "�ܵ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CONT_UNDER_ATTENTION_ASSURE, sdb_icps_pboc_credit.cont_under_attention_assure, "���ⵣ���弶�����ע�����ϱ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CONT_UNDER_SECONDARY_ASSURE, sdb_icps_pboc_credit.cont_under_secondary_assure, "״̬Ϊ�μ������ϵĵ���������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ASSURE_UNDER_ATTENTION_AMT, sdb_icps_pboc_credit.assure_under_attention_amt, "״̬Ϊ��ע�����ϵĵ���������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AS_CV2_BAL_SUM, sdb_icps_pboc_credit.as_cv2_bal_sum, "���ⵣ���弶�����ע���������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_AMT_SUM, sdb_icps_pboc_credit.card_amt_sum, "���ⵣ���弶�����ע������������δ�������ÿ�������Ŷ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_LMT_MAX, sdb_icps_pboc_credit.cc_act_lmt_max, "������δ�������ÿ�������Ŷ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NML_LMT_AVG, sdb_icps_pboc_credit.ac_nml_lmt_avg, "����״̬��ƽ�����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NML_LMT_SUM, sdb_icps_pboc_credit.ac_nml_lmt_sum, "����״̬���ܶ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_ISSUE_ORG_CNT, sdb_icps_pboc_credit.card_issue_org_cnt, "����״̬����������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_RMB_CNT, sdb_icps_pboc_credit.card_rmb_cnt, "��ǰ������δ��������Ҵ��ǿ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_CNT_SUM, sdb_icps_pboc_credit.cc_cnt_sum, "����δ�������ǿ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_NCA_CNT_SUM, sdb_icps_pboc_credit.cc_nca_cnt_sum, "δ�������ǿ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_NORMAL_NUM, sdb_icps_pboc_credit.normal_num, "����״̬���ǿ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_ALL_CARD_CNT, sdb_icps_pboc_credit.all_card_cnt, "�ܿ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_CU_O90_PCT, sdb_icps_pboc_credit.cc_act_cu_o90_pct, "������δ�������ǿ���ǰʹ���ʴ��ڵ���90%ռ����δ�������ǿ�����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_NCA_CU_MIN, sdb_icps_pboc_credit.cc_nca_cu_min, "δ�������ǿ���ǰ��Сʹ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_NCA_MU_MAX, sdb_icps_pboc_credit.cc_nca_mu_max, "δ�������ǿ����6����ƽ��ʹ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_NCA_HB_MAX, sdb_icps_pboc_credit.card_nca_hb_max, "δ�������ǿ����ʹ�ö��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NCA_CU_AVG, sdb_icps_pboc_credit.ac_nca_cu_avg, "δ��������ǰƽ��ʹ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NCA_HB_MAX, sdb_icps_pboc_credit.ac_nca_hb_max, "δ���������ʹ�ö��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_NML_MU_AVG, sdb_icps_pboc_credit.cc_nml_mu_avg, "����״̬���ǿ�6����ƽ��ʹ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ALL_CARD_CUR_OVD_USED, sdb_icps_pboc_credit.all_card_cur_ovd_used, "����״̬����ǰƽ��ʹ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_NCA_PMO_SUM, sdb_icps_pboc_credit.card_nca_pmo_sum, "����δ�������ǿ���Ӧ�����ܶ�");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_6MTH_MAX_CNT, sdb_icps_pboc_credit.card_delq_6mth_max_cnt, "δ�������ǿ���6����������ڴ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_12MTH_MAX_CNT, sdb_icps_pboc_credit.card_delq_12mth_max_cnt, "δ�������ǿ���12����������ڴ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_3MTH_MAX_CNT, sdb_icps_pboc_credit.card_delq_3mth_max_cnt, "δ�������ǿ���3����������ڴ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_MAX_OVD_BAL, sdb_icps_pboc_credit.card_max_ovd_bal, "���ǿ�����������ڽ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ALL_CARD_CUR_OVD_AMT_SUM, sdb_icps_pboc_credit.all_card_cur_ovd_amt_sum, "δ��������ǰ�����ڽ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CONT_DULL_CARD_CNT, sdb_icps_pboc_credit.cont_dull_card_cnt, "���˵Ĵ��ǿ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_DULL_SCARD_CNT, sdb_icps_pboc_credit.dull_scard_cnt, "���˵�׼���ǿ���");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_AC_ABN_CNT_SUM, sdb_icps_pboc_credit.ac_abn_cnt_sum, "���ǿ�Ϊ���ʶ���ֹ������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_ACT_M1_CNT_3M, sdb_icps_pboc_credit.cc_act_m1_cnt_3m, "����δ�������ǿ���3����1�ڼ��������ڿ���");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_M1_CNT_PCT_3M, sdb_icps_pboc_credit.cc_act_m1_cnt_pct_3m, "����δ�������ǿ���3����1�ڼ��������ڿ���ռ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_M1_CNT_PCT_6M, sdb_icps_pboc_credit.cc_act_m1_cnt_pct_6m, "����δ�������ǿ���6����1�ڼ��������ڿ���ռ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_AC_NCA_CD_MAX, sdb_icps_pboc_credit.ac_nca_cd_max, "δ��������ǰ�����������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_CD_MAX_24M, sdb_icps_pboc_credit.cc_cd_max_24m, "���ǿ���24���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_12MTH_MAX, sdb_icps_pboc_credit.card_delq_12mth_max, "���ǿ�δ�����˻��й�ȥ12���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_3MTH_MAX, sdb_icps_pboc_credit.card_delq_3mth_max, "���ǿ�δ�����˻��й�ȥ3���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_6MTH_MAX, sdb_icps_pboc_credit.card_delq_6mth_max, "���ǿ�δ�����˻��й�ȥ6���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_QC_ACT_CD_MAX_24M, sdb_icps_pboc_credit.qc_act_cd_max_24m, "׼������24���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_SCARD_DELQ_12MTH_MAX, sdb_icps_pboc_credit.scard_delq_12mth_max, "׼����δ�����˻��й�ȥ12���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_SCARD_DELQ_3MTH_MAX, sdb_icps_pboc_credit.scard_delq_3mth_max, "׼����δ�����˻��й�ȥ3���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_SCARD_DELQ_6MTH_MAX, sdb_icps_pboc_credit.scard_delq_6mth_max, "׼����δ�����˻��й�ȥ6���������������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CREDIT_OPM_MAX, sdb_icps_pboc_credit.credit_opm_max, "������ʷ");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_AC_OPM_MAX, sdb_icps_pboc_credit.ac_opm_max, "��󿪿�����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_EXTEND_PARAM1, sdb_icps_pboc_credit.extend_param1, "��չ1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_EXTEND_PARAM2, sdb_icps_pboc_credit.extend_param2, "��չ2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_EXTEND_PARAM3, sdb_icps_pboc_credit.extend_param3, "��չ3");

    iRet = APP_DBInsert("ICPS_PBOC_CREDIT", SD_ICPS_PBOC_CREDIT, NUMELE(SD_ICPS_PBOC_CREDIT), &sdb_icps_pboc_credit, sErrmsg);
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

/************************************************************************
 ��̬�����������
 �����������:ICPS_APPLY_BANK_INFO_INS
 �������:ICPS_APPLY_BANK_INFO_INS
 �������: �Ǽ�����������Ϣ
 �������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
 ʹ������:
 �� �� Ա:
 ��������:2009��12��11��
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT ICPS_APPLY_BANK_INFO_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_BANK_CREDIT sdb_icps_bank_credit;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_bank_credit, 0, sizeof(sdb_icps_bank_credit));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_bank_credit.apply_no, "���뵥��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_bank_credit.plt_date, "ƽ̨����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_bank_credit.plt_serial, "ƽ̨��ˮ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_ID_TYPE, sdb_icps_bank_credit.id_type, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_ID_NUM, sdb_icps_bank_credit.id_num, "֤������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_CUSTOMER, sdb_icps_bank_credit.is_exist_customer, "�Ƿ�����ͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_DEBT_CUSTOMER, sdb_icps_bank_credit.is_exist_debt_customer, "�Ƿ������ǿ��ͻ�");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_BALANCE, sdb_icps_bank_credit.balance, "�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_AVG_BALANCE_LAST_3DAYS, sdb_icps_bank_credit.avg_balance_last_3days, "��3�����վ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_AVG_BALANCE_LAST_6DAYS, sdb_icps_bank_credit.avg_balance_last_6days, "��6�����վ����");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_INCOME_LAST_3M, sdb_icps_bank_credit.income_last_3m, "��3����������ˮ��������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PAY_LAST_3M, sdb_icps_bank_credit.pay_last_3m, "��3����������ˮ֧�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_INCOME_LAST_6M, sdb_icps_bank_credit.income_last_6m, "��6����������ˮ��������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PAY_LAST_6M, sdb_icps_bank_credit.pay_last_6m, "��6����������ˮ֧�������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_CREDIT_CUSTOMER, sdb_icps_bank_credit.is_exist_credit_customer, "�Ƿ�������ÿ��ͻ�");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CURR_CREDIT_CARD_AMT, sdb_icps_bank_credit.curr_credit_card_amt, "�������ÿ����Ŷ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CURR_USE_CREDIT_CARD_AMT, sdb_icps_bank_credit.curr_use_credit_card_amt, "�������ÿ���ǰʹ�ö��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_FIN_CUSTOMER, sdb_icps_bank_credit.is_exist_fin_customer, "�Ƿ������ƿͻ�");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FIN_BALANCE, sdb_icps_bank_credit.fin_balance, "������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_AVG_FIN_BAL_LAST_6M, sdb_icps_bank_credit.avg_fin_bal_last_6m, "��6�����վ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_INSURANCE_CUSTOMER, sdb_icps_bank_credit.is_exist_insurance_customer, "�Ƿ�������տͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_LOAN_CUSTOMER, sdb_icps_bank_credit.is_exist_loan_customer, "�Ƿ��������ͻ�");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_OPERATION_LOAN_BAL, sdb_icps_bank_credit.operation_loan_bal, "��Ӫ����������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PERSONAL_CREDIT_BAL, sdb_icps_bank_credit.personal_credit_bal, "����������������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CAR_LOAN_BAL, sdb_icps_bank_credit.car_loan_bal, "�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CAR_ASSET, sdb_icps_bank_credit.car_asset, "������ֵ������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_HOUSE_LOAN_BAL, sdb_icps_bank_credit.house_loan_bal, "�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_HOUSE_ASSET, sdb_icps_bank_credit.house_asset, "������ֵ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_STOCK_CUSTOMER, sdb_icps_bank_credit.is_stock_customer, "�Ƿ�֤ȯ�ͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_THIRD_DEPOSITORY, sdb_icps_bank_credit.is_third_depository, "�Ƿ��������ܿͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_PAYROLL_CUSTOMER, sdb_icps_bank_credit.is_payroll_customer, "�Ƿ��ʴ����ͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_SOCIAL_SECURITY_CUSTOMER, sdb_icps_bank_credit.is_social_security_customer, "�Ƿ��籣���ɿͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_LIFE_PAYMENT_CUSTOMER, sdb_icps_bank_credit.is_life_payment_customer, "�Ƿ�ˮ��ú���ɿͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_COMPANY_NAME, sdb_icps_bank_credit.company_name, "������λ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_COMPANY_ORIGIN, sdb_icps_bank_credit.company_origin, "������λ������Դ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_POSITION, sdb_icps_bank_credit.position, "ְλ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_POSITION_ORIGIN, sdb_icps_bank_credit.position_origin, "ְλ��Ϣ��Դ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_INDUSTRY, sdb_icps_bank_credit.industry, "��ҵ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_INDUSTRY_ORIGIN, sdb_icps_bank_credit.industry_origin, "��ҵ��Ϣ��Դ");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_WORK_YEARS, sdb_icps_bank_credit.work_years, "��������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_WORK_YEARS_ORIGIN, sdb_icps_bank_credit.work_years_origin, "����������Ϣ��Դ");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_INCOME, sdb_icps_bank_credit.income, "����������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_INCOME_ORIGIN, sdb_icps_bank_credit.income_origin, "��������Ϣ��Դ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_MARRIAGE_STATUS, sdb_icps_bank_credit.marriage_status, "����״̬");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_MARRIAGE_ORIGIN, sdb_icps_bank_credit.marriage_origin, "����״̬��Ϣ��Դ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_OPERATION, sdb_icps_bank_credit.is_operation, "�Ƿ�Ӫ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_OPERATION_ORIGIN, sdb_icps_bank_credit.operation_origin, "�Ƿ�Ӫ����Ϣ��Դ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_INNER_BLACK_CUSTOMER, sdb_icps_bank_credit.is_inner_black_customer, "�Ƿ�����ڲ��������ͻ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_POLICE_CERTIFIED, sdb_icps_bank_credit.is_police_certified, "�Ƿ񹫰��������֤�ɹ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_COURT_EXEC_CUSTOMER, sdb_icps_bank_credit.is_court_exec_customer, "�Ƿ���б�ִ���˵�������Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_HOUSE_FUND, sdb_icps_bank_credit.is_query_house_fund, "�Ƿ��в�ѯ��������Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_FUND_QUERY_DATE, sdb_icps_bank_credit.fund_query_date, "�������ѯʱ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_MONTH_AMT, sdb_icps_bank_credit.fund_month_amt, "�������ѯ�½��ɶ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_FUND_ACCT_DATE, sdb_icps_bank_credit.fund_acct_date, "�����𿪻�����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_FUND_MONTHS_LAST_6M, sdb_icps_bank_credit.fund_months_last_6m, "��6�����ۼƽ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_AMT_LAST_6M, sdb_icps_bank_credit.fund_amt_last_6m, "��6�����ۼƽ��ɽ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_FUND_TOTAL_MONTHS, sdb_icps_bank_credit.fund_total_months, "�ܽ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_TOTAL_AMT, sdb_icps_bank_credit.fund_total_amt, "�ܽ��ɽ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_MAX_AMT, sdb_icps_bank_credit.fund_max_amt, "���������ؽ�������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_SOCIAL_SECURITY, sdb_icps_bank_credit.is_query_social_security, "�Ƿ��в�ѯ�籣��Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_SOCIAL_QUERY_DATE, sdb_icps_bank_credit.social_query_date, "�籣��Ϣ��ѯʱ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PENSION_QUERY_MONTH_AMT, sdb_icps_bank_credit.pension_query_month_amt, "���ϱ��ղ�ѯ�½��ɶ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_PENSION_ACCT_DATE, sdb_icps_bank_credit.pension_acct_date, "���ϱ��տ�������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_PENSION_MONTHS_LAST_6M, sdb_icps_bank_credit.pension_months_last_6m, "��6�������ϱ����ۼƽ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PENSION_AMT_LAST_6M, sdb_icps_bank_credit.pension_amt_last_6m, "��6�������ϱ����ۼƽ��ɽ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_PENSION_TOTAL_MONTHS, sdb_icps_bank_credit.pension_total_months, "���ϱ����ܽ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PENSION_TOTAL_AMT, sdb_icps_bank_credit.pension_total_amt, "���ϱ����ܽ��ɽ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_MEDICARE_MONTH_AMT, sdb_icps_bank_credit.medicare_month_amt, "ҽ�Ʊ��ղ�ѯ�½��ɶ�");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_MEDICARE_ACCT_DATE, sdb_icps_bank_credit.medicare_acct_date, "ҽ�Ʊ��տ�������");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_MEDICARE_MONTHS_LAST_6M, sdb_icps_bank_credit.medicare_months_last_6m, "��6����ҽ�Ʊ����ۼƽ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_MEDICARE_AMT_LAST_6M, sdb_icps_bank_credit.medicare_amt_last_6m, "��6����ҽ�Ʊ����ۼƽ��ɽ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_MEDICARE_TOTAL_MONTHS, sdb_icps_bank_credit.medicare_total_months, "ҽ�Ʊ����ܽ�������");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_MEDICARE_TOTAL_AMT, sdb_icps_bank_credit.medicare_total_amt, "ҽ�Ʊ����ܽ��ɽ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_DEGREE, sdb_icps_bank_credit.is_query_degree, "�Ƿ��в�ѯѧ����Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_SCHOOL_NAME, sdb_icps_bank_credit.school_name, "ԺУ����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_DEGREE_LEVEL, sdb_icps_bank_credit.degree_level, "ѧ�����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_DEGREE_TYPE, sdb_icps_bank_credit.degree_type, "ѧ�����");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_ENTRANCE_YEAR, sdb_icps_bank_credit.entrance_year, "��ѧ���");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_COMMUNICATION, sdb_icps_bank_credit.is_query_communication, "�Ƿ��в�ѯ��Ӫ����Ϣ");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_COMMUNICATION, sdb_icps_bank_credit.communication, "��Ӫ��");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_ONLINE_DAYS, sdb_icps_bank_credit.online_days, "����ʱ��");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_TOTAL_TEL_FARE, sdb_icps_bank_credit.total_tel_fare, "�ܻ����˵����");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_TOTAL_CALL_HOURS, sdb_icps_bank_credit.total_call_hours, "������ͨ��ʱ��");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_OUT_BLACK_CUSTOMER, sdb_icps_bank_credit.is_out_black_customer, "�Ƿ�����ⲿ��ѯ������");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_EXTEND_PARAM1, sdb_icps_bank_credit.extend_param1, "��չ1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_EXTEND_PARAM2, sdb_icps_bank_credit.extend_param2, "��չ2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_EXTEND_PARAM3, sdb_icps_bank_credit.extend_param3, "��չ3");

    iRet = APP_DBInsert("ICPS_BANK_CREDIT", SD_ICPS_BANK_CREDIT, NUMELE(SD_ICPS_BANK_CREDIT), &sdb_icps_bank_credit, sErrmsg);
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

/************************************************************************
 ��̬�����������
 �����������:ICPS_ZMINFO_JSON2XML
 �������:ICPS_ZMINFO_JSON2XML
 �������: �Ǽ�����������Ϣ
 �������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
 ʹ������:
 �� �� Ա:
 ��������:2009��12��11��
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT ICPS_ZMINFO_JSON2XML(HXMLTREE lXmlhandle)
{
    char sBuf[10000];
    char cZmInfo[5000 + 1];
    char sPath[40 + 1];
    int iRet = -1;
    int iParas = 0;

    /*��ʼ�����*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(2)

    ICPS_GETPARSEPARAS_STRING(1, sBuf, cZmInfo, "֥����Ϣ");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sPath, "·��");
    LOG(LM_DEBUG, Fmtmsg("֥����Ϣ=[%s],·��=[%s]", cZmInfo, sPath), "DEBUG");

    if (strlen(cZmInfo) > 0)
    {
        iRet = cJSON_to_ZmInfo(lXmlhandle, cZmInfo, sPath);
        if (iRet < 0)
            return iRet;
    }

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}


IRESULT SBankinfo_to_xml(HXMLTREE lXmlhandle)
{
    char sBuf[10000] =
    { 0 };
    char cBankInfo[40 + 1] =
    { 0 };
    char path[40 + 1] =
    { 0 };
    int iRet = -1;
    int iParas = 0;

    /*��ʼ�����*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*�����θ���*/
    COMP_PARACOUNTCHKMIN(2)

    /* XMl��ȡ--Begin */
    /*��ȡ���1*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "������Ϣ")
    strncpy(cBankInfo, sBuf, sizeof(cBankInfo) - 1);
    trim(cBankInfo);
    LOG(LM_DEBUG, Fmtmsg("������Ϣ[%s]", cBankInfo), "DEBUG");

    /*��ȡ���2*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "JSON·��")
    strncpy(path, sBuf, sizeof(path) - 1);
    trim(path);
    LOG(LM_DEBUG, Fmtmsg("JSO·��[%s]", path), "DEBUG");

    if (strlen(cBankInfo) > 0)
    {
        iRet = cBankInfo_to_Xml(lXmlhandle, cBankInfo, path);
        if (iRet < 0)
            return iRet;
    }

    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}
