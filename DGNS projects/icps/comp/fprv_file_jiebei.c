#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>

int ffunc_parse_jiebei_file_to_db_accounting(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_TOTAL sdb_icps_jb_total;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_TOTAL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    memset(&sdb_icps_jb_total, 0x00, sizeof(sdb_icps_jb_total));
    pstrcopy(sdb_icps_jb_total.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_total.busi_date)); /*ҵ������*/

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);

    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_int_amt, "ʵ��������Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_to_accrued_ovd_prin_amt, "���ڱ��𣨷�Ӧ�ƣ�ת���ڱ���Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_to_accrued_prin_amt, "�������𣨷�Ӧ�ƣ�ת��������Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_non_accrued_ovd_prin_amt, "ʵ�����ڱ��𣨷�Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_int_amt, "ʵ��������Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_to_non_prin_amt, "��������Ӧ�ƣ�ת�������𣨷�Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_to_non_ovd_prin_amt, "���ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_prin_amt, "ʵ����������Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_non_accrued_prin_amt, "ʵ���������𣨷�Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_ovd_int_amt, "������Ϣ�����ڣ�ת������Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_int_amt, "������Ϣ�����ڣ�ת������Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_in_ovd_int_amt, "ʵ��������Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_ovd_int_amt, "ʵ��������Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.encash_amt, "�������Ž��");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_ovd_int_pnlt_amt, "��������90�����ڣ������������ÿ��������Ϣ��Ϣ");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_accrued_ovd_int_pnlt_amt, "��������90�����ϴ������ÿ��������Ϣ��Ϣ");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.prin_to_ovd_prin_amt, "��������ת���ڱ���");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.int_to_ovd_int_amt, "������Ϣת������Ϣ");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_accrued_int_amt, "��������90�����ϴ������ÿ����Ϣ");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_in_ovd_int_pnlt_int_amt, "ʵ��������Ϣ��Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_ovd_int_pnlt_int_amt, "ʵ��������Ϣ��Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_int_amt, "��������/����90�����ڣ������������ÿ����Ϣ");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_ovd_int_amt, "������Ϣ�����⣩ת������Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_int_amt, "������Ϣ�����⣩ת������Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_ovd_prin_pnlt_amt, "��������90�����ڣ������������ÿ�����ڱ���Ϣ");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_accrued_ovd_prin_pnlt_amt, "��������90�����ϴ������ÿ�����ڱ���Ϣ");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_ovd_prin_pnlt_int_amt, "ʵ�����ڱ���Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_in_ovd_prin_pnlt_int_amt, "ʵ�����ڱ���Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_ovd_prin_pnlt_amt, "���ڱ���Ϣ�����⣩ת�Ȿ��Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_ovd_int_pnlt_amt, "������Ϣ��Ϣ�����⣩ת������Ϣ��Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_ovd_int_pnlt_amt, "������Ϣ��Ϣ�����ڣ�ת������Ϣ��Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_ovd_prin_pnlt_amt, "���ڱ���Ϣ�����ڣ�ת���ڱ���Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_accrued_ovd_prin_amt, "ʵ�����ڱ���Ӧ�ƣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.withhold_amt, "�������̱�������۽��");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.refund_amt, "�����˻����̱�������");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_int_amt, "����������Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_int_amt, "����������Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_ovd_int_amt, "����������Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_ovd_int_amt, "����������Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_ovd_prin_pnlt_int_amt, "�������ڱ���Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_ovd_prin_pnlt_int_amt, "�������ڱ���Ϣ�����⣩");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_ovd_int_pnlt_int_amt, "����������Ϣ��Ϣ�����ڣ�");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_ovd_int_pnlt_int_amt, "����������Ϣ��Ϣ�����⣩");

    /*�������ݿ�*/
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = APP_DBInsert("ICPS_JB_TOTAL", SD_ICPS_JB_TOTAL, NUMELE(SD_ICPS_JB_TOTAL), &sdb_icps_jb_total, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    if (DCICommit() != MID_SYS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIRollback();
        return -1;
    }

    return 0;
}

/*
 * ��;֧����ϸ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_lending_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_LENDING_DETAIL sdb_icps_jb_lending_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LENDING_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_lending_detail, 0x00, sizeof(sdb_icps_jb_lending_detail));
        pstrcopy(sdb_icps_jb_lending_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_lending_detail.busi_date)); /*ҵ������*/
        sdb_icps_jb_lending_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_lending_detail.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_lending_detail.fund_seq_no, ',', "�ſ��ʽ���ˮ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_lending_detail.third_product_code, ',', "��Ʒ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_lending_detail.name, ',', "�ͻ���ʵ����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_lending_detail.id_type, ',', "֤������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_lending_detail.id_num, ',', "֤������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_lending_detail.loan_status, ',', "����״̬");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_lending_detail.loan_use, ',', "������;");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_lending_detail.use_area, ',', "�����ʽ�ʹ��λ��");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_lending_detail.apply_date, ',', "����֧��ʱ��");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_lending_detail.encash_date, ',', "�ſ�����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_lending_detail.currency, ',', "����");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_lending_detail.encash_amt, ',', "�ſ���");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_lending_detail.start_date, ',', "������Ϣ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_lending_detail.end_date, ',', "�������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_lending_detail.total_terms, ',', "�����ڴ���");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_lending_detail.repay_mode, ',', "���ʽ");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_jb_lending_detail.grace_day, ',', "����������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_jb_lending_detail.rate_type, ',', "��������");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_jb_lending_detail.day_rate, ',', "����������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_jb_lending_detail.prin_repay_frequency, ',', "���𻹿�Ƶ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_jb_lending_detail.int_repay_frequency, ',', "��Ϣ����Ƶ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_jb_lending_detail.guarantee_type, ',', "��������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_jb_lending_detail.credit_no, ',', "���ű��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_jb_lending_detail.encash_acct_type, ',', "�ſ��ʺ�����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_jb_lending_detail.encash_acct, ',', "�ſ��ʺ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_jb_lending_detail.repay_acct_type, ',', "�����ʺ�����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_jb_lending_detail.repay_acct, ',', "�����ʺ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_jb_lending_detail.loan_apply_no, ',', "�������뵥��");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_lending_detail.is_check_flag, "1", sizeof(sdb_icps_jb_lending_detail.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LENDING_DETAIL", SD_ICPS_JB_LENDING_DETAIL, NUMELE(SD_ICPS_JB_LENDING_DETAIL),
                &sdb_icps_jb_lending_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_jb_lending_detail.contract_no,
                            sdb_icps_jb_lending_detail.fund_seq_no), "ERROR");
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
 * �ſ��ݣ���ϸ�ļ����
 */
int ffunc_parse_jiebei_file_to_db_loan_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];
    ICPS_JB_LOAN_DETAIL sdb_icps_jb_loan_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LOAN_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_loan_detail, 0x00, sizeof(sdb_icps_jb_loan_detail));
        pstrcopy(sdb_icps_jb_loan_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_loan_detail.busi_date)); /*ҵ������*/
        sdb_icps_jb_loan_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_loan_detail.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_loan_detail.fund_seq_no, ',', "�ſ��ʽ���ˮ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_loan_detail.third_product_code, ',', "��Ʒ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_loan_detail.name, ',', "�ͻ���ʵ����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_loan_detail.id_type, ',', "֤������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_loan_detail.id_num, ',', "֤������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_loan_detail.loan_status, ',', "����״̬");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_loan_detail.loan_use, ',', "������;");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_loan_detail.use_area, ',', "�����ʽ�ʹ��λ��");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_loan_detail.apply_date, ',', "����֧��ʱ��");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_loan_detail.encash_date, ',', "�ſ�����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_loan_detail.currency, ',', "����");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_loan_detail.encash_amt, ',', "�ſ���");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_loan_detail.start_date, ',', "������Ϣ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_loan_detail.end_date, ',', "�������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_loan_detail.total_terms, ',', "�����ڴ���");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_loan_detail.repay_mode, ',', "���ʽ");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_jb_loan_detail.grace_day, ',', "����������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_jb_loan_detail.rate_type, ',', "��������");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_jb_loan_detail.day_rate, ',', "����������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_jb_loan_detail.prin_repay_frequency, ',', "���𻹿�Ƶ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_jb_loan_detail.int_repay_frequency, ',', "��Ϣ����Ƶ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_jb_loan_detail.guarantee_type, ',', "��������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_jb_loan_detail.credit_no, ',', "���ű��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_jb_loan_detail.encash_acct_type, ',', "�ſ��ʺ�����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_jb_loan_detail.encash_acct, ',', "�ſ��ʺ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_jb_loan_detail.repay_acct_type, ',', "�����ʺ�����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_jb_loan_detail.repay_acct, ',', "�����ʺ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_jb_loan_detail.loan_apply_no, ',', "�������뵥��");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_loan_detail.is_check_flag, "1", sizeof(sdb_icps_jb_loan_detail.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LOAN_DETAIL", SD_ICPS_JB_LOAN_DETAIL, NUMELE(SD_ICPS_JB_LOAN_DETAIL), &sdb_icps_jb_loan_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_jb_loan_detail.contract_no, sdb_icps_jb_loan_detail.fund_seq_no),
                    "ERROR");
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
 * �ſ���ڣ���ϸ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_repay_plan(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_REPAY_PLAN sdb_icps_jb_repay_plan;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_REPAY_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_repay_plan, 0x00, sizeof(sdb_icps_jb_repay_plan));
        pstrcopy(sdb_icps_jb_repay_plan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_repay_plan.busi_date)); /*ҵ������*/
        sdb_icps_jb_repay_plan.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_repay_plan.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_repay_plan.term_no, ',', "�ڴκ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_repay_plan.start_date, ',', "���ڿ�ʼ����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_repay_plan.end_date, ',', "���ڽ�������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_repay_plan.prin_amt, ',', "������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_repay_plan.int_amt, ',', "��ʼ��Ϣ������");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_repay_plan.is_check_flag, "1", sizeof(sdb_icps_jb_repay_plan.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_REPAY_PLAN", SD_ICPS_JB_REPAY_PLAN, NUMELE(SD_ICPS_JB_REPAY_PLAN), &sdb_icps_jb_repay_plan, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_jb_repay_plan.contract_no, sdb_icps_jb_repay_plan.term_no),
                    "ERROR");
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
 * �����ݣ���ϸ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_repay_loan_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_REPAY_LOAN_DETAIL sdb_icps_jb_repay_loan_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_REPAY_LOAN_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_repay_loan_detail, 0x00, sizeof(sdb_icps_jb_repay_loan_detail));
        pstrcopy(sdb_icps_jb_repay_loan_detail.busi_date, st_para_chkfileins.busi_date,
                sizeof(sdb_icps_jb_repay_loan_detail.busi_date)); /*ҵ������*/
        sdb_icps_jb_repay_loan_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_repay_loan_detail.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_repay_loan_detail.repay_seq_no, ',', "������ˮ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_repay_loan_detail.fee_no, ',', "�շѵ���");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_repay_loan_detail.withdraw_no, ',', "�������ֵ���");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_repay_loan_detail.repay_type, ',', "��������");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_repay_loan_detail.repay_date, ',', "��������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_repay_loan_detail.curr_prin_bal, ',', "���λ���ǰ��Ӧ��δ�������������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_repay_loan_detail.curr_ovd_prin_bal, ',', "���λ���ǰ��Ӧ��δ�����ڱ������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_repay_loan_detail.curr_int_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_repay_loan_detail.curr_ovd_int_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_repay_loan_detail.curr_ovd_prin_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ�����ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_repay_loan_detail.curr_ovd_int_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_repay_loan_detail.repay_amt, ',', "�ܽ��");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_repay_loan_detail.paid_prin_amt, ',', "����ʵ������������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_repay_loan_detail.paid_ovd_prin_amt, ',', "����ʵ�����ڱ�����");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_repay_loan_detail.paid_int_amt, ',', "����ʵ��������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_repay_loan_detail.paid_ovd_int_amt, ',', "����ʵ��������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 18, sdb_icps_jb_repay_loan_detail.paid_ovd_prin_pnlt_amt, ',', "����ʵ�����ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 19, sdb_icps_jb_repay_loan_detail.paid_ovd_int_pnlt_amt, ',', "����ʵ��������Ϣ��Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 20, sdb_icps_jb_repay_loan_detail.fee_amt, ',', "���λ����Ӧ��ƽ̨����ѽ��");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_repay_loan_detail.is_check_flag, "1", sizeof(sdb_icps_jb_repay_loan_detail.is_check_flag));


        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_REPAY_LOAN_DETAIL", SD_ICPS_JB_REPAY_LOAN_DETAIL, NUMELE(SD_ICPS_JB_REPAY_LOAN_DETAIL),
                &sdb_icps_jb_repay_loan_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_jb_repay_loan_detail.contract_no,
                            sdb_icps_jb_repay_loan_detail.repay_seq_no), "ERROR");
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
 * ������ڣ���ϸ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_repay_instmnt_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_REPAY_INSTMNT_DETAIL sdb_icps_jb_repay_instmnt_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_REPAY_INSTMNT_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_repay_instmnt_detail, 0x00, sizeof(sdb_icps_jb_repay_instmnt_detail));
        pstrcopy(sdb_icps_jb_repay_instmnt_detail.busi_date, st_para_chkfileins.busi_date,
                sizeof(sdb_icps_jb_repay_instmnt_detail.busi_date)); /*ҵ������*/
        sdb_icps_jb_repay_instmnt_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_repay_instmnt_detail.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_repay_instmnt_detail.repay_seq_no, ',', "������ˮ��");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_repay_instmnt_detail.term_no, ',', "�ڴκ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_repay_instmnt_detail.repay_amt_type, ',', "����������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_repay_instmnt_detail.repay_date, ',', "��������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_repay_instmnt_detail.curr_prin_bal, ',', "���λ���ǰ��Ӧ��δ�ձ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_repay_instmnt_detail.curr_int_bal, ',', "���λ���ǰ��Ӧ��δ����Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_repay_instmnt_detail.curr_ovd_prin_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ�����ڱ���Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_repay_instmnt_detail.curr_ovd_int_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_repay_instmnt_detail.repay_amt, ',', "����ʵ���ܽ��");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_repay_instmnt_detail.paid_prin_amt, ',', "����ʵ��������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_repay_instmnt_detail.paid_int_amt, ',', "����ʵ����Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_repay_instmnt_detail.paid_ovd_prin_pnlt_amt, ',', "����ʵ�����ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_repay_instmnt_detail.paid_ovd_int_pnlt_amt, ',', "����ʵ��������Ϣ��Ϣ���");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_repay_instmnt_detail.is_check_flag, "1", sizeof(sdb_icps_jb_repay_instmnt_detail.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_REPAY_INSTMNT_DETAIL", SD_ICPS_JB_REPAY_INSTMNT_DETAIL, NUMELE(SD_ICPS_JB_REPAY_INSTMNT_DETAIL),
                &sdb_icps_jb_repay_instmnt_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_jb_repay_instmnt_detail.contract_no,
                            sdb_icps_jb_repay_instmnt_detail.repay_seq_no), "ERROR");
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
 * ���⣨��ݣ���ϸ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_xpt_loan_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_XPT_LOAN_DETAIL sdb_icps_jb_xpt_loan_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_XPT_LOAN_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_xpt_loan_detail, 0x00, sizeof(sdb_icps_jb_xpt_loan_detail));
        pstrcopy(sdb_icps_jb_xpt_loan_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_xpt_loan_detail.busi_date)); /*ҵ������*/
        sdb_icps_jb_xpt_loan_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_xpt_loan_detail.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_xpt_loan_detail.xpt_seq_no, ',', "������ˮ��");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_xpt_loan_detail.xpt_date, ',', "����ʱ��");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_xpt_loan_detail.curr_int_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_xpt_loan_detail.curr_ovd_int_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_xpt_loan_detail.curr_ovd_prin_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ�����ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_xpt_loan_detail.curr_ovd_int_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_xpt_loan_detail.xpt_amt, ',', "�����ܽ��");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_xpt_loan_detail.xpt_int_amt, ',', "���μ���������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_xpt_loan_detail.xpt_ovd_int_amt, ',', "���μ���������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_xpt_loan_detail.xpt_ovd_prin_pnlt_amt, ',', "���μ������ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_xpt_loan_detail.xpt_ovd_int_pnlt_amt, ',', "���μ���������Ϣ��Ϣ���");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_xpt_loan_detail.is_check_flag, "1", sizeof(sdb_icps_jb_xpt_loan_detail.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_XPT_LOAN_DETAIL", SD_ICPS_JB_XPT_LOAN_DETAIL, NUMELE(SD_ICPS_JB_XPT_LOAN_DETAIL),
                &sdb_icps_jb_xpt_loan_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_jb_xpt_loan_detail.contract_no,
                            sdb_icps_jb_xpt_loan_detail.xpt_seq_no), "ERROR");
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
 * ���⣨���ڣ���ϸ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_xpt_instmnt_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_XPT_INSTMNT_DETAIL sdb_icps_jb_xpt_instmnt_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_XPT_INSTMNT_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_xpt_instmnt_detail, 0x00, sizeof(sdb_icps_jb_xpt_instmnt_detail));
        pstrcopy(sdb_icps_jb_xpt_instmnt_detail.busi_date, st_para_chkfileins.busi_date,
                sizeof(sdb_icps_jb_xpt_instmnt_detail.busi_date)); /*ҵ������*/
        sdb_icps_jb_xpt_instmnt_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_xpt_instmnt_detail.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_xpt_instmnt_detail.xpt_seq_no, ',', "������ˮ��");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_xpt_instmnt_detail.term_no, ',', "�ڴκ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_xpt_instmnt_detail.settle_date, ',', "����������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_xpt_instmnt_detail.curr_int_bal, ',', "���λ���ǰ��Ӧ��δ����Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_xpt_instmnt_detail.curr_ovd_prin_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ�����ڱ���Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_xpt_instmnt_detail.curr_ovd_int_pnlt_bal, ',', "���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_xpt_instmnt_detail.xpt_amt, ',', "���μ����ܽ��");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_xpt_instmnt_detail.xpt_int_amt, ',', "���μ�����Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_xpt_instmnt_detail.xpt_ovd_prin_pnlt_amt, ',', "���μ������ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_xpt_instmnt_detail.xpt_ovd_int_pnlt_amt, ',', "���μ���������Ϣ��Ϣ���");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_xpt_instmnt_detail.is_check_flag, "1", sizeof(sdb_icps_jb_xpt_instmnt_detail.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_XPT_INSTMNT_DETAIL", SD_ICPS_JB_XPT_INSTMNT_DETAIL, NUMELE(SD_ICPS_JB_XPT_INSTMNT_DETAIL),
                &sdb_icps_jb_xpt_instmnt_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_jb_xpt_instmnt_detail.contract_no,
                            sdb_icps_jb_xpt_instmnt_detail.xpt_seq_no), "ERROR");
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
 * �ճ�����ݣ���Ϣ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_loan_init(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_LOAN_INIT sdb_icps_jb_loan_init;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LOAN_INIT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_loan_init, 0x00, sizeof(sdb_icps_jb_loan_init));
        pstrcopy(sdb_icps_jb_loan_init.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_loan_init.busi_date)); /*ҵ������*/
        sdb_icps_jb_loan_init.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_loan_init.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_loan_init.settle_date, ',', "�������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_loan_init.status, ',', "���״̬");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_loan_init.clear_date, ',', "��������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_loan_init.asset_class, ',', "�弶�����ʶ");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_loan_init.accrued_status, ',', "Ӧ�Ʒ�Ӧ�Ʊ�ʶ");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_loan_init.next_repay_date, ',', "��һ��������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_loan_init.unclear_terms, ',', "δ��������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_loan_init.ovd_terms, ',', "�����ڴ���");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_loan_init.prin_ovd_days, ',', "������������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_loan_init.int_ovd_days, ',', "��Ϣ��������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_loan_init.prin_bal, ',', "�����������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_loan_init.ovd_prin_bal, ',', "���ڱ������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_loan_init.int_bal, ',', "������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_loan_init.ovd_int_bal, ',', "������Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_loan_init.ovd_prin_pnlt_bal, ',', "���ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_loan_init.ovd_int_pnlt_bal, ',', "������Ϣ��Ϣ���");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_loan_init.is_check_flag, "1", sizeof(sdb_icps_jb_loan_init.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LOAN_INIT", SD_ICPS_JB_LOAN_INIT, NUMELE(SD_ICPS_JB_LOAN_INIT), &sdb_icps_jb_loan_init, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jb_loan_init.contract_no), "ERROR");
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
 * �ճ������ڣ���Ϣ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_instmnt_init(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_INSTMNT_INIT sdb_icps_jb_instmnt_init;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_INSTMNT_INIT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_instmnt_init, 0x00, sizeof(sdb_icps_jb_instmnt_init));
        pstrcopy(sdb_icps_jb_instmnt_init.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_instmnt_init.busi_date)); /*ҵ������*/
        sdb_icps_jb_instmnt_init.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_instmnt_init.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_instmnt_init.settle_date, ',', "�������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_instmnt_init.term_no, ',', "�ڴκ�");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_instmnt_init.start_date, ',', "���ڿ�ʼ����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_instmnt_init.end_date, ',', "���ڽ�������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_instmnt_init.status, ',', "����״̬");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_instmnt_init.clear_date, ',', "��������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_instmnt_init.prin_ovd_date, ',', "����ת��������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_instmnt_init.int_ovd_date, ',', "��Ϣת��������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_instmnt_init.prin_ovd_days, ',', "������������");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_instmnt_init.int_ovd_days, ',', "��Ϣ��������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_instmnt_init.prin_bal, ',', "�������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_instmnt_init.int_bal, ',', "��Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_instmnt_init.ovd_prin_pnlt_bal, ',', "���ڱ���Ϣ���");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_instmnt_init.ovd_int_pnlt_bal, ',', "������Ϣ��Ϣ���");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_instmnt_init.is_check_flag, "1", sizeof(sdb_icps_jb_instmnt_init.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_INSTMNT_INIT", SD_ICPS_JB_INSTMNT_INIT, NUMELE(SD_ICPS_JB_INSTMNT_INIT), &sdb_icps_jb_instmnt_init,
                sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jb_instmnt_init.contract_no), "ERROR");
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
 * ��Ϣ������ϸ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_loan_calc(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_LOAN_CALC sdb_icps_jb_loan_calc;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LOAN_CALC WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_loan_calc, 0x00, sizeof(sdb_icps_jb_loan_calc));
        pstrcopy(sdb_icps_jb_loan_calc.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_loan_calc.busi_date)); /*ҵ������*/
        sdb_icps_jb_loan_calc.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_loan_calc.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_loan_calc.calc_date, ',', "��Ϣ����");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_loan_calc.accrued_status, ',', "Ӧ�Ʒ�Ӧ�Ʊ�ʶ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_loan_calc.prin_bal, ',', "�����������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_loan_calc.ovd_prin_bal, ',', "���ڱ������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_loan_calc.ovd_int_bal, ',', "������Ϣ���");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_loan_calc.real_rate, ',', "����ʵ��������");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_loan_calc.pnlt_rate, ',', "���Ϣ������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_loan_calc.int_amt, ',', "������Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_loan_calc.ovd_prin_pnlt_amt, ',', "���ڱ���Ϣ");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_loan_calc.ovd_int_pnlt_amt, ',', "������Ϣ��Ϣ");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_loan_calc.is_check_flag, "1", sizeof(sdb_icps_jb_loan_calc.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LOAN_CALC", SD_ICPS_JB_LOAN_CALC, NUMELE(SD_ICPS_JB_LOAN_CALC), &sdb_icps_jb_loan_calc,
                sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jb_loan_calc.contract_no), "ERROR");
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
 * �����̬ת����ˮ�ļ�
 */
int ffunc_parse_jiebei_file_to_db_arg_status_change(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_ARG_STATUS_CHANGE sdb_icps_jb_arg_status_change;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_ARG_STATUS_CHANGE WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_arg_status_change, 0x00, sizeof(sdb_icps_jb_arg_status_change));
        pstrcopy(sdb_icps_jb_arg_status_change.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_arg_status_change.busi_date)); /*ҵ������*/
        sdb_icps_jb_arg_status_change.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_arg_status_change.contract_no, ',', "����ƽ̨�����ͬ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_arg_status_change.settle_date, ',', "�������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_arg_status_change.status_seq_no, ',', "״̬�仯��ˮ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_arg_status_change.event_code, ',', "�¼���");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_arg_status_change.before_status, ',', "���ת��ǰ״̬");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_arg_status_change.after_status, ',', "���ת�ƺ�״̬");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_arg_status_change.prin_amt, ',', "��������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_arg_status_change.int_amt, ',', "��Ϣ������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_arg_status_change.ovd_prin_pnlt_amt, ',', "���ڱ���Ϣ������");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_arg_status_change.ovd_int_pnlt_amt, ',', "������Ϣ��Ϣ������");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_arg_status_change.is_check_flag, "1", sizeof(sdb_icps_jb_arg_status_change.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_ARG_STATUS_CHANGE", SD_ICPS_JB_ARG_STATUS_CHANGE, NUMELE(SD_ICPS_JB_ARG_STATUS_CHANGE),
                &sdb_icps_jb_arg_status_change, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jb_arg_status_change.contract_no), "ERROR");
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
 * ���������ʽ�����ļ�
 */
int ffunc_parse_jiebei_file_to_db_fund_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_FUND_DETAIL sdb_icps_jb_fund_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_FUND_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*��ȡ�ļ�*/
    /*ȥ����һ��*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*����*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*�����ļ����ݵ���ṹ��*/
        memset(&sdb_icps_jb_fund_detail, 0x00, sizeof(sdb_icps_jb_fund_detail));
        pstrcopy(sdb_icps_jb_fund_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_fund_detail.busi_date)); /*ҵ������*/
        sdb_icps_jb_fund_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_fund_detail.third_busi_serial, ',', "�������н�����ˮ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_fund_detail.third_busi_type, ',', "ҵ�����");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_fund_detail.trans_amt, ',', "���׽��");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_fund_detail.trans_refund_amt, ',', "�����˿���");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_fund_detail.trans_dttm, ',', "����ʱ��");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_fund_detail.third_trans_name, ',', "��������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_fund_detail.peer_org_name, ',', "�Է���������");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_fund_detail.trans_sub_detail, ',', "ҵ�񵥺�");

        /*������˱�־*/
        pstrcopy(sdb_icps_jb_fund_detail.is_check_flag, "1", sizeof(sdb_icps_jb_fund_detail.is_check_flag));

        /*�������ݿ�*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_FUND_DETAIL", SD_ICPS_JB_FUND_DETAIL, NUMELE(SD_ICPS_JB_FUND_DETAIL), &sdb_icps_jb_fund_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_jb_fund_detail.third_busi_serial), "ERROR");
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

int ffunc_parse_jiebei_file_to_db(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("�ļ����Ϊ�գ�����"), "ERROR");
        return -1;
    }
    if (0 == strcmp(st_para_chkfileins.file_type, "accounting"))
    {
        /*���ܼ����ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_accounting(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "lending_detail"))
    {
        /*��;֧����ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_lending_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan_detail"))
    {
        /*�ſ��ݣ���ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_loan_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "repay_plan"))
    {
        /*�ſ���ڣ���ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_repay_plan(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "repay_loan_detail"))
    {
        /*�����ݣ���ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_repay_loan_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "repay_instmnt_detail"))
    {
        /*������ڣ���ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_repay_instmnt_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "exempt_loan_detail"))
    {
        /*���⣨��ݣ���ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_xpt_loan_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "exempt_instmnt_detail"))
    {
        /*���⣨���ڣ���ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_xpt_instmnt_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan_init"))
    {
        /*�ճ�����ݣ���Ϣ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_loan_init(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "instmnt_init"))
    {
        /*�ճ������ڣ���Ϣ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_instmnt_init(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan_calc"))
    {
        /*��Ϣ������ϸ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_loan_calc(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "arg_status_change"))
    {
        /*�����̬ת����ˮ�ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_arg_status_change(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "fund_detail"))
    {
        /*���������ʽ�����ļ�*/
        iRet = ffunc_parse_jiebei_file_to_db_fund_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ļ����ʹ���"), "ERROR");
        return -2;
    }

    return iRet;
}
