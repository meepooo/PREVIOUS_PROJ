#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>

/*
 * �ͻ���Ϣ�ļ�
 */
int ffunc_parse_jintiao_file_to_db_cus(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_CUS sdb_icps_jt_cus;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_CUS WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*����*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jt_cus, 0x00, sizeof(sdb_icps_jt_cus));
        //pstrcopy(sdb_icps_jt_cus.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_cus.busi_date)); /*ҵ������*/
        sdb_icps_jt_cus.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.busi_date, "@!@", "ҵ������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.customer_code, "@!@", "�ͻ����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.customer_name, "@!@", "�ͻ�����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.gender, "@!@", "�ͻ��Ա�");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.brith_date, "@!@", "��������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.resident_flag, "@!@", "�����־");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.customer_status, "@!@", "�ͻ�״̬");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.border_in_out_flag, "@!@", "���ھ����־");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.id_type, "@!@", "֤������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.id_num, "@!@", "֤������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.mobile_no, "@!@", "�ֻ�����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.addr, "@!@", "ͨѶ��ַ");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.bank_name, "@!@", "�����п�����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.bank_acct, "@!@", "�����п�����");

        /*������˱�־*/
        pstrcopy(sdb_icps_jt_cus.is_check_flag, "1", sizeof(sdb_icps_jt_cus.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_CUS", SD_ICPS_JT_CUS, NUMELE(SD_ICPS_JT_CUS), &sdb_icps_jt_cus, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jt_cus.customer_code), "ERROR");
            DCIRollback();
            return iRet;
        }

        if (transcCnt >= 1000)
        {
            if (DCICommit() != MID_SYS_SUCC)
            {
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIRollback();
                return -1;
            }
            DCIBegin();
            transcCnt = 0;
        }
    }
    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * ���Ŷ����Ϣ�ļ�
 */
int ffunc_parse_jintiao_file_to_db_cuscredit(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_CUSCREDIT sdb_icps_jt_cuscredit;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_CUSCREDIT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*����*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jt_cuscredit, 0x00, sizeof(sdb_icps_jt_cuscredit));
        //pstrcopy(sdb_icps_jt_cuscredit.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_cuscredit.busi_date)); /*ҵ������*/
        sdb_icps_jt_cuscredit.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.busi_date, "@!@", "ҵ������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.customer_code, "@!@", "�ͻ����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.product_code, "@!@", "��Ʒ���");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.quota_code, "@!@", "��ȱ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.currency, "@!@", "����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.cycle_quota_flag, "@!@", "ѭ����ȱ�־");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.start_date, "@!@", "������Ч��ʼ����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.end_date, "@!@", "���ŵ�����");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.quota, "@!@", "���Ŷ��");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.limit, "@!@", "��������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.nouse_quota, "@!@", "δ�������Ŷ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.tmp_quota_flag, "@!@", "�Ƿ���ʱ���");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.auth_status, "@!@", "����״̬");

        /*������˱�־*/
        pstrcopy(sdb_icps_jt_cuscredit.is_check_flag, "1", sizeof(sdb_icps_jt_cuscredit.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_CUSCREDIT", SD_ICPS_JT_CUSCREDIT, NUMELE(SD_ICPS_JT_CUSCREDIT), &sdb_icps_jt_cuscredit,
                sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jt_cuscredit.customer_code), "ERROR");
            DCIRollback();
            return iRet;
        }

        if (transcCnt >= 1000)
        {
            if (DCICommit() != MID_SYS_SUCC)
            {
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIRollback();
                return -1;
            }
            DCIBegin();
            transcCnt = 0;
        }
    }
    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * ������Ϣ�ļ�
 */
int ffunc_parse_jintiao_file_to_db_quotaadjust(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_QUOTAADJUST sdb_icps_jt_quotaadjust;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_QUOTAADJUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*����*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jt_quotaadjust, 0x00, sizeof(sdb_icps_jt_quotaadjust));
        pstrcopy(sdb_icps_jt_quotaadjust.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_quotaadjust.busi_date)); /*ҵ������*/
        sdb_icps_jt_quotaadjust.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.customer_code, "@!@", "�ͻ����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.product_code, "@!@", "��Ʒ���");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.quota_code, "@!@", "��ȱ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_type, "@!@", "��������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_mode, "@!@", "���ʽ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_quota, "@!@", "������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.before_adjust_quota, "@!@", "����ǰ���Ŷ��");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.after_adjust_quota, "@!@", "��������Ŷ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_cal_date, "@!@", "������������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_effective_date, "@!@", "��������Ч��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_serial, "@!@", "������ˮ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.error_type, "@!@", "�������");

        /*������˱�־*/
        pstrcopy(sdb_icps_jt_quotaadjust.is_check_flag, "1", sizeof(sdb_icps_jt_quotaadjust.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_QUOTAADJUST", SD_ICPS_JT_QUOTAADJUST, NUMELE(SD_ICPS_JT_QUOTAADJUST),
                &sdb_icps_jt_quotaadjust, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jt_quotaadjust.customer_code), "ERROR");
            DCIRollback();
            return iRet;
        }

        if (transcCnt >= 1000)
        {
            if (DCICommit() != MID_SYS_SUCC)
            {
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIRollback();
                return -1;
            }
            DCIBegin();
            transcCnt = 0;
        }
    }
    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * ��������Ϣ���ļ�
 */
int ffunc_parse_jintiao_file_to_db_loan(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_LOAN sdb_icps_jt_loan;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_LOAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*����*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jt_loan, 0x00, sizeof(sdb_icps_jt_loan));
        //pstrcopy(sdb_icps_jt_loan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_loan.busi_date)); /*ҵ������*/
        sdb_icps_jt_loan.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.busi_date, "@!@", "ҵ������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.contract_no, "@!@", "��ͬ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.customer_code, "@!@", "�ͻ����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.product_code, "@!@", "��Ʒ���");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.quota_code, "@!@", "��ȱ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_code, "@!@", "������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.currency, "@!@", "����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_status, "@!@", "����״̬");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.encash_date, "@!@", "�ſ�����");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.encash_amt, "@!@", "�ſ���");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.end_date, "@!@", "��������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.use_area, "@!@", "�����ʽ�ʹ��λ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.prin_repay_frequency, "@!@", "���𻹿�Ƶ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_repay_frequency, "@!@", "��Ϣ����Ƶ��");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.self_pay_amt, "@!@", "����֧�����");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.entrusted_pay_amt, "@!@", "����֧�����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_flag, "@!@", "���ڱ�־");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_days, "@!@", "��������");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_non_days, "@!@", "���ڿ�������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.prin_ovd_days, "@!@", "������������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_ovd_days, "@!@", "��Ϣ��������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.next_int_date, "@!@", "��һ��Ϣ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.rate_type, "@!@", "��������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_bal, "@!@", "�������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_loan_bal, "@!@", "���ڴ������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_int, "@!@", "������Ϣ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.out_int_bal, "@!@", "����ǷϢ");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_flag, "@!@", "��Ϣ��־");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.accrued_int, "@!@", "Ӧ����Ϣ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_amt, "@!@", "������Ϣ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.pnlt_amt, "@!@", "���շ�Ϣ");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.encash_acct, "@!@", "���������˺�");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.repay_acct, "@!@", "�����˺�");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.guarantee_type, "@!@", "�������ʽ");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.repay_mode, "@!@", "���ʽ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_rate, "@!@", "�������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.penalty_rate, "@!@", "ΥԼ������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_rate_type, "@!@", "�����������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.penalty_rate_type, "@!@", "ΥԼ����������");

        /*������˱�־*/
        pstrcopy(sdb_icps_jt_loan.is_check_flag, "1", sizeof(sdb_icps_jt_loan.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_LOAN", SD_ICPS_JT_LOAN, NUMELE(SD_ICPS_JT_LOAN), &sdb_icps_jt_loan, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jt_loan.customer_code), "ERROR");
            DCIRollback();
            return iRet;
        }

        if (transcCnt >= 1000)
        {
            if (DCICommit() != MID_SYS_SUCC)
            {
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIRollback();
                return -1;
            }
            DCIBegin();
            transcCnt = 0;
        }
    }
    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * �����ƻ���Ϣ�ļ�
 */
int ffunc_parse_jintiao_file_to_db_plan(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_PLAN sdb_icps_jt_plan;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*����*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jt_plan, 0x00, sizeof(sdb_icps_jt_plan));
        //pstrcopy(sdb_icps_jt_plan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_plan.busi_date)); /*ҵ������*/
        sdb_icps_jt_plan.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.busi_date, "@!@", "ҵ������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.contract_no, "@!@", "��ͬ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.product_code, "@!@", "��Ʒ���");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.quota_code, "@!@", "��ȱ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.loan_code, "@!@", "������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.term_no, "@!@", "���ڵ���");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.repay_order, "@!@", "��������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.prin_end_date, "@!@", "��������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.prin_amt, "@!@", "����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.int_end_date, "@!@", "��Ϣ������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.int_amt, "@!@", "��Ϣ");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.repay_terms, "@!@", "����������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.pnlt_amt, "@!@", "��Ϣ");

        /*������˱�־*/
        pstrcopy(sdb_icps_jt_plan.is_check_flag, "1", sizeof(sdb_icps_jt_plan.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_PLAN", SD_ICPS_JT_PLAN, NUMELE(SD_ICPS_JT_PLAN), &sdb_icps_jt_plan, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jt_plan.contract_no), "ERROR");
            DCIRollback();
            return iRet;
        }

        if (transcCnt >= 1000)
        {
            if (DCICommit() != MID_SYS_SUCC)
            {
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIRollback();
                return -1;
            }
            DCIBegin();
            transcCnt = 0;
        }
    }
    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * �������ϸ��Ϣ�ļ�
 */
int ffunc_parse_jintiao_file_to_db_flow(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_FLOW sdb_icps_jt_flow;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*����*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jt_flow, 0x00, sizeof(sdb_icps_jt_flow));
        //pstrcopy(sdb_icps_jt_flow.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_flow.busi_date)); /*ҵ������*/
        sdb_icps_jt_flow.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.busi_date, "@!@", "ҵ������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.contract_no, "@!@", "��ͬ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.product_code, "@!@", "��Ʒ���");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.quota_code, "@!@", "��ȱ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.loan_code, "@!@", "������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.term_no, "@!@", "���ڵ���");
        ICPS_GET_DATE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_date, "@!@", "��������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_serial, "@!@", "��ˮ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_mode, "@!@", "���ʽ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.curr_prin_amt, "@!@", "����Ӧ������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.prin_amt, "@!@", "������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.curr_int_amt, "@!@", "����Ӧ����Ϣ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.int_amt, "@!@", "��Ϣ���");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.curr_other_amt, "@!@", "����Ӧ���������");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.pnlt_amt, "@!@", "��Ϣ���");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_order, "@!@", "��������");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.unclear_terms, "@!@", "ʣ�໹������");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_amt_type, "@!@", "��������");

        /*������˱�־*/
        pstrcopy(sdb_icps_jt_flow.is_check_flag, "1", sizeof(sdb_icps_jt_flow.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_FLOW", SD_ICPS_JT_FLOW, NUMELE(SD_ICPS_JT_FLOW), &sdb_icps_jt_flow, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jt_flow.contract_no), "ERROR");
            DCIRollback();
            return iRet;
        }

        if (transcCnt >= 1000)
        {
            if (DCICommit() != MID_SYS_SUCC)
            {
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIRollback();
                return -1;
            }
            DCIBegin();
            transcCnt = 0;
        }
    }
    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * ��ҵ�ʽ���ˮ�ļ�
 */
int ffunc_parse_jintiao_file_to_db_fund_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_FUND_DETAIL sdb_icps_jt_fund_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_FUND_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*����*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jt_fund_detail, 0x00, sizeof(sdb_icps_jt_fund_detail));
        sdb_icps_jt_fund_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.trans_time, "@!@", "����ʱ��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.sys_date, "@!@", "ϵͳ����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.acct_direction, "@!@", "��֧����");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.trans_amt, "@!@", "���׽��");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.summary_code, "@!@", "ժҪ����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.summary, "@!@", "����ժҪ");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.acct_bal, "@!@", "�˻����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.currency, "@!@", "���Һ�");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.peer_acct, "@!@", "�Է��˻�");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.peer_acct_name, "@!@", "�Է��˻�����");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.remarks, "@!@", "��ע");

        /*������˱�־*/
        pstrcopy(sdb_icps_jt_fund_detail.is_check_flag, "1", sizeof(sdb_icps_jt_fund_detail.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_FUND_DETAIL", SD_ICPS_JT_FUND_DETAIL, NUMELE(SD_ICPS_JT_FUND_DETAIL),
                &sdb_icps_jt_fund_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jt_fund_detail.peer_acct), "ERROR");
            DCIRollback();
            return iRet;
        }

        if (transcCnt >= 1000)
        {
            if (DCICommit() != MID_SYS_SUCC)
            {
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIRollback();
                return -1;
            }
            DCIBegin();
            transcCnt = 0;
        }
    }
    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

int ffunc_parse_jintiao_file_to_db(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }

    if (0 == strcmp(st_para_chkfileins.file_type, "loan_total"))
    {
        /*�����ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_loan_total(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "cus"))
    {
        /*�ͻ���Ϣ�ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_cus(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "cuscredit"))
    {
        /*���Ŷ����Ϣ�ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_cuscredit(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "quotaadjust"))
    {
        /*������Ϣ�ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_quotaadjust(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan"))
    {
        /*��������Ϣ�ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_loan(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "plan"))
    {
        /*�����ƻ���Ϣ�ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_plan(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "flow"))
    {
        /*�������ϸ��Ϣ�ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_flow(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "fund_detail"))
    {
        /*��ҵ�ʽ���ˮ�ļ�*/
        iRet = ffunc_parse_jintiao_file_to_db_fund_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ļ����ʹ���"), "ERROR");
        return -2;
    }

    return iRet;
}
