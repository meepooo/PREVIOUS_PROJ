#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>

/**
 * �˻���Ϣ��
 */
int ffunc_parse_wbank_file_to_db_tm_account(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_ACCOUNT sdb_icps_wb_tm_account;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_ACCOUNT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_account, 0x00, sizeof(sdb_icps_wb_tm_account));
            pstrcopy(sdb_icps_wb_tm_account.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_account.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_account.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_account.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_account.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_account.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_account.cust_id, '\001', "�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_account.cust_limit_id, '\001', "�ͻ����ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_account.product_code, '\001', "��Ʒ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_account.default_logical_card_no, '\001', "Ĭ���߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_account.currency, '\001', "����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_account.credit_limit, '\001', "���Ŷ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_account.temp_limit, '\001', "��ʱ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_account.temp_limit_begin_date, '\001', "��ʱ��ȿ�ʼ����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_account.temp_limit_end_date, '\001', "��ʱ��Ƚ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_account.user_field1, '\001', "�����ֶ�1");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_account.user_field2, '\001', "�����ֶ�2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_account.user_field3, '\001', "�����ֶ�3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_account.curr_balance, '\001', "��ǰ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_account.user_field4, '\001', "�����ֶ�4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_account.principal_bal, '\001', "�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_account.user_field5, '\001', "�����ֶ�5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_account.user_field6, '\001', "�����ֶ�6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_account.begin_bal, '\001', "��һ���������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_account.pmt_due_day_bal, '\001', "���ڻ��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_account.user_field7, '\001', "�����ֶ�7");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_account.user_field8, '\001', "�����ֶ�8");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_account.user_field9, '\001', "�����ֶ�9");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_account.user_field10, '\001', "�����ֶ�10");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_account.user_field11, '\001', "�����ֶ�11");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_account.user_field12, '\001', "�����ֶ�12");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_account.user_field13, '\001', "�����ֶ�13");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_account.user_field14, '\001', "�����ֶ�14");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_account.user_field15, '\001', "�����ֶ�15");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_account.user_field16, '\001', "�����ֶ�16");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_account.user_field17, '\001', "�����ֶ�17");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_account.user_field18, '\001', "�����ֶ�18");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_account.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_account.gender, '\001', "�Ա�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_account.user_field19, '\001', "�����ֶ�19");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_account.mobile_no, '\001', "�ƶ��绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_account.user_field20, '\001', "�����ֶ�20");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_account.billint_cycle, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_account.user_field21, '\001', "�����ֶ�21");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_account.user_field22, '\001', "�����ֶ�22");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_account.user_field23, '\001', "�����ֶ�23");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_account.user_field24, '\001', "�����ֶ�24");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_account.user_field25, '\001', "�����ֶ�25");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_account.user_field26, '\001', "�����ֶ�26");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_account.user_field27, '\001', "�����ֶ�27");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_account.user_field28, '\001', "�����ֶ�28");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_account.user_field29, '\001', "�����ֶ�29");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_account.user_field30, '\001', "�����ֶ�30");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_account.user_field31, '\001', "�����ֶ�31");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_account.AGE_CD, '\001', "��Ƿ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_account.user_field32, '\001', "�����ֶ�32");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_account.UNMATCH_DB, '\001', "δ���˽�ǽ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_account.user_field33, '\001', "�����ֶ�33");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_account.unmatch_cr, '\001', "δ���˴��ǽ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_account.dd_ind, '\001', "Լ����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_account.dd_bank_name, '\001', "Լ��������������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_account.dd_bank_branch, '\001', "Լ��������к�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_account.dd_bank_acct_no, '\001', "Լ������ۿ��˺�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_account.dd_bank_acct_name, '\001', "Լ������ۿ��˻�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_account.last_dd_amt, '\001', "����Լ��������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_account.last_dd_date, '\001', "����Լ����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_account.user_field34, '\001', "�����ֶ�34");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_account.last_pmt_amt, '\001', "���ڻ�����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_account.last_pmt_date, '\001', "�ϸ���������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_account.last_stmt_date, '\001', "�ϸ����ڻ�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_account.last_pmt_due_date, '\001', "�ϸ����ڻ�������1");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_account.last_agint_date, '\001', "�Ͽ�����������������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_account.collect_date, '\001', "�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_account.collect_out_date, '\001', "�����ն�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_account.next_stmt_date, '\001', "�¸����ڻ�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_account.pmt_due_date, '\001', "���ڻ�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_account.dd_date, '\001', "Լ����������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_account.grace_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_account.user_field35, '\001', "�����ֶ�35");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wb_tm_account.closed_date, '\001', "������������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 78, sdb_icps_wb_tm_account.first_stmt_date, '\001', "�׸����ڻ�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 79, sdb_icps_wb_tm_account.cancel_date, '\001', "��������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wb_tm_account.charge_off_date, '\001', "ת��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 81, sdb_icps_wb_tm_account.user_field36, '\001', "�����ֶ�36");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wb_tm_account.usesr_field37, '\001', "�����ֶ�37");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 83, sdb_icps_wb_tm_account.usesr_field38, '\001', "�����ֶ�38");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wb_tm_account.usesr_field39, '\001', "�����ֶ�39");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wb_tm_account.usesr_field40, '\001', "�����ֶ�40");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wb_tm_account.usesr_field41, '\001', "�����ֶ�41");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wb_tm_account.usesr_field42, '\001', "�����ֶ�42");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wb_tm_account.usesr_field43, '\001', "�����ֶ�43");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wb_tm_account.usesr_field44, '\001', "�����ֶ�44");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wb_tm_account.usesr_field45, '\001', "�����ֶ�45");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wb_tm_account.usesr_field46, '\001', "�����ֶ�46");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wb_tm_account.usesr_field47, '\001', "�����ֶ�47");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_wb_tm_account.usesr_field48, '\001', "�����ֶ�48");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 94, sdb_icps_wb_tm_account.usesr_field49, '\001', "�����ֶ�49");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 95, sdb_icps_wb_tm_account.ctd_retail_amt, '\001', "�������ѽ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 96, sdb_icps_wb_tm_account.ctd_retail_cnt, '\001', "�������ѱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 97, sdb_icps_wb_tm_account.ctd_payment_amt, '\001', "���ڻ�����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 98, sdb_icps_wb_tm_account.ctd_payment_cnt, '\001', "���ڻ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 99, sdb_icps_wb_tm_account.ctd_db_adj_amt, '\001', "���ڽ�ǵ������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 100, sdb_icps_wb_tm_account.ctd_db_adj_cnt, '\001', "���ڽ�ǵ�������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 101, sdb_icps_wb_tm_account.ctd_cr_adj_cnt, '\001', "���ڴ��ǵ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 102, sdb_icps_wb_tm_account.ctd_cr_adj_amt, '\001', "���ڴ��ǵ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 103, sdb_icps_wb_tm_account.ctd_fee_amt, '\001', "���ڷ��ý��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 104, sdb_icps_wb_tm_account.ctd_fee_cnt, '\001', "���ڷ��ñ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 105, sdb_icps_wb_tm_account.ctd_interest_amt, '\001', "������Ϣ���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 106, sdb_icps_wb_tm_account.ctd_interest_cnt, '\001', "������Ϣ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 107, sdb_icps_wb_tm_account.user_field50, '\001', "�����ֶ�50");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 108, sdb_icps_wb_tm_account.user_field51, '\001', "�����ֶ�51");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 109, sdb_icps_wb_tm_account.user_field52, '\001', "�����ֶ�52");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 110, sdb_icps_wb_tm_account.mtd_retail_amt, '\001', "�������ѽ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 111, sdb_icps_wb_tm_account.mtd_retail_cnt, '\001', "�������ѱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 112, sdb_icps_wb_tm_account.user_field53, '\001', "�����ֶ�53");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 113, sdb_icps_wb_tm_account.user_field54, '\001', "�����ֶ�54");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_wb_tm_account.user_field55, '\001', "�����ֶ�55");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 115, sdb_icps_wb_tm_account.user_field56, '\001', "�����ֶ�56");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 116, sdb_icps_wb_tm_account.ytd_retail_amt, '\001', "�������ѽ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 117, sdb_icps_wb_tm_account.ytd_retail_cnt, '\001', "�������ѱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 118, sdb_icps_wb_tm_account.user_field57, '\001', "�����ֶ�57");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 119, sdb_icps_wb_tm_account.user_field58, '\001', "�����ֶ�58");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 120, sdb_icps_wb_tm_account.user_field59, '\001', "�����ֶ�59");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 121, sdb_icps_wb_tm_account.user_field60, '\001', "�����ֶ�60");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 122, sdb_icps_wb_tm_account.user_field61, '\001', "�����ֶ�61");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 123, sdb_icps_wb_tm_account.user_field62, '\001', "�����ֶ�62");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 124, sdb_icps_wb_tm_account.user_field63, '\001', "�����ֶ�63");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 125, sdb_icps_wb_tm_account.user_field64, '\001', "�����ֶ�64");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 126, sdb_icps_wb_tm_account.user_field65, '\001', "�����ֶ�65");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 127, sdb_icps_wb_tm_account.user_field66, '\001', "�����ֶ�66");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 128, sdb_icps_wb_tm_account.user_field67, '\001', "�����ֶ�67");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 129, sdb_icps_wb_tm_account.user_field68, '\001', "�����ֶ�68");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 130, sdb_icps_wb_tm_account.user_field69, '\001', "�����ֶ�69");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 131, sdb_icps_wb_tm_account.user_field70, '\001', "�����ֶ�70");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 132, sdb_icps_wb_tm_account.user_field71, '\001', "�����ֶ�71");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 133, sdb_icps_wb_tm_account.user_field72, '\001', "�����ֶ�72");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 134, sdb_icps_wb_tm_account.user_field73, '\001', "�����ֶ�73");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 135, sdb_icps_wb_tm_account.user_field74, '\001', "�����ֶ�74");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 136, sdb_icps_wb_tm_account.user_field75, '\001', "�����ֶ�75");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 137, sdb_icps_wb_tm_account.user_field76, '\001', "�����ֶ�76");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 138, sdb_icps_wb_tm_account.user_field77, '\001', "�����ֶ�77");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 139, sdb_icps_wb_tm_account.user_field78, '\001', "�����ֶ�78");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 140, sdb_icps_wb_tm_account.user_field79, '\001', "�����ֶ�79");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 141, sdb_icps_wb_tm_account.user_field80, '\001', "�����ֶ�80");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 142, sdb_icps_wb_tm_account.user_field81, '\001', "�����ֶ�81");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 143, sdb_icps_wb_tm_account.waive_svcfee_ind, '\001', "�Ƿ���������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 144, sdb_icps_wb_tm_account.user_field82, '\001', "�����ֶ�82");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 145, sdb_icps_wb_tm_account.user_field83, '\001', "�����ֶ�83");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 146, sdb_icps_wb_tm_account.user_field84, '\001', "�����ֶ�84");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 147, sdb_icps_wb_tm_account.user_field85, '\001', "�����ֶ�85");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 148, sdb_icps_wb_tm_account.user_field86, '\001', "�����ֶ�86");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 149, sdb_icps_wb_tm_account.user_field87, '\001', "�����ֶ�87");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 150, sdb_icps_wb_tm_account.user_field88, '\001', "�����ֶ�88");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 151, sdb_icps_wb_tm_account.user_date2, '\001', "���ڵ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 152, sdb_icps_wb_tm_account.user_field89, '\001', "�����ֶ�89");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 153, sdb_icps_wb_tm_account.user_field90, '\001', "�����ֶ�90");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 154, sdb_icps_wb_tm_account.user_field91, '\001', "�����ֶ�91");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 155, sdb_icps_wb_tm_account.user_field92, '\001', "�����ֶ�92");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 156, sdb_icps_wb_tm_account.user_field93, '\001', "�����ֶ�93");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 157, sdb_icps_wb_tm_account.user_field94, '\001', "�����ֶ�94");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 158, sdb_icps_wb_tm_account.user_field95, '\001', "�����ֶ�95");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 159, sdb_icps_wb_tm_account.user_field96, '\001', "�����ֶ�96");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 160, sdb_icps_wb_tm_account.user_field97, '\001', "�����ֶ�97");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 161, sdb_icps_wb_tm_account.user_field98, '\001', "�����ֶ�98");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 162, sdb_icps_wb_tm_account.user_field99, '\001', "�����ֶ�99");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 163, sdb_icps_wb_tm_account.user_field100, '\001', "�����ֶ�100");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 164, sdb_icps_wb_tm_account.user_field101, '\001', "�����ֶ�101");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 165, sdb_icps_wb_tm_account.user_field102, '\001', "�����ֶ�102");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 166, sdb_icps_wb_tm_account.user_field103, '\001', "�����ֶ�103");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 167, sdb_icps_wb_tm_account.user_field104, '\001', "�����ֶ�104");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 168, sdb_icps_wb_tm_account.user_field105, '\001', "�����ֶ�105");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 169, sdb_icps_wb_tm_account.user_field106, '\001', "�����ֶ�106");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 170, sdb_icps_wb_tm_account.user_field107, '\001', "�����ֶ�107");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 171, sdb_icps_wb_tm_account.user_field108, '\001', "�����ֶ�108");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 172, sdb_icps_wb_tm_account.user_field109, '\001', "�����ֶ�109");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 173, sdb_icps_wb_tm_account.user_field110, '\001', "�����ֶ�110");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 174, sdb_icps_wb_tm_account.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 175, sdb_icps_wb_tm_account.mtd_payment_amt, '\001', "���»�����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 176, sdb_icps_wb_tm_account.mtd_payment_cnt, '\001', "���»������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 177, sdb_icps_wb_tm_account.ytd_payment_amt, '\001', "���껹����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 178, sdb_icps_wb_tm_account.ytd_payment_cnt, '\001', "���껹�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 179, sdb_icps_wb_tm_account.ltd_payment_amt, '\001', "��ʷ������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 180, sdb_icps_wb_tm_account.ltd_payment_cnt, '\001', "��ʷ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 181, sdb_icps_wb_tm_account.user_field111, '\001', "�����ֶ�111");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 182, sdb_icps_wb_tm_account.user_field112, '\001', "�����ֶ�112");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 183, sdb_icps_wb_tm_account.user_field113, '\001', "�����ֶ�113");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 184, sdb_icps_wb_tm_account.last_post_date, '\001', "�ϸ���������ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 185, sdb_icps_wb_tm_account.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 186, sdb_icps_wb_tm_account.user_field114, '\001', "�����ֶ�114");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 187, sdb_icps_wb_tm_account.last_sync_date, '\001', "��һ�����˵���������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 188, sdb_icps_wb_tm_account.user_field115, '\001', "�����ֶ�115");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 189, sdb_icps_wb_tm_account.user_field116, '\001', "�����ֶ�116");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 190, sdb_icps_wb_tm_account.user_field117, '\001', "�����ֶ�117");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 191, sdb_icps_wb_tm_account.bank_group_id, '\001', "���ű��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 192, sdb_icps_wb_tm_account.bank_proportion, '\001', "���г��ʱ���");


            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_account.is_check_flag, "1", sizeof(sdb_icps_wb_tm_account.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_ACCOUNT", SD_ICPS_WB_TM_ACCOUNT, NUMELE(SD_ICPS_WB_TM_ACCOUNT),
                    &sdb_icps_wb_tm_account, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_account.org), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ��Ȩ��ˮ���Ų�ֱ�
 */
int ffunc_parse_wbank_file_to_db_tm_auth_bank_cost(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_AUTH_BANK_COST sdb_icps_wb_tm_auth_bank_cost;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_AUTH_BANK_COST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_auth_bank_cost, 0x00, sizeof(sdb_icps_wb_tm_auth_bank_cost));
            pstrcopy(sdb_icps_wb_tm_auth_bank_cost.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_auth_bank_cost.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_auth_bank_cost.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_auth_bank_cost.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_auth_bank_cost.bank_group_id, '\001', "���ű��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_auth_bank_cost.bank_no, '\001', "���к�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_auth_bank_cost.reg_type, '\001', "�Ǽ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_auth_bank_cost.reg_amt, '\001', "�Ǽǽ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_auth_bank_cost.reg_status, '\001', "�Ǽ�״̬");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_auth_bank_cost.reg_sys_id, '\001', "������ˮ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_auth_bank_cost.reg_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_auth_bank_cost.reg_time, '\001', "��������ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_auth_bank_cost.recon_code, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_auth_bank_cost.ori_sys_id, '\001', "ԭ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_auth_bank_cost.cust_id, '\001', "�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_auth_bank_cost.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_auth_bank_cost.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_auth_bank_cost.retry, '\001', "���Դ���");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_auth_bank_cost.created_datetime, '\001', "����ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_auth_bank_cost.last_modified_datetime, '\001', "ʱ���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_auth_bank_cost.user_field268, '\001', "�����ֶ�268");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_auth_bank_cost.is_check_flag, "1", sizeof(sdb_icps_wb_tm_auth_bank_cost.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_AUTH_BANK_COST", SD_ICPS_WB_TM_AUTH_BANK_COST, NUMELE(SD_ICPS_WB_TM_AUTH_BANK_COST),
                    &sdb_icps_wb_tm_auth_bank_cost, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_auth_bank_cost.busi_serial), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �߼�����
 */
int ffunc_parse_wbank_file_to_db_tm_card(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_CARD sdb_icps_wb_tm_card;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_CARD WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_card, 0x00, sizeof(sdb_icps_wb_tm_card));
            pstrcopy(sdb_icps_wb_tm_card.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_card.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_card.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_card.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_card.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_card.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_card.cust_id, '\001', "�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_card.user_field118, '\001', "�����ֶ�118");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_card.product_cd, '\001', "��Ʒ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_card.app_no, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_card.user_field119, '\001', "�����ֶ�119");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_card.user_field120, '\001', "�����ֶ�120");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_card.bsc_logiccard_no, '\001', "�߼�����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_card.user_field121, '\001', "�����ֶ�121");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_card.user_field122, '\001', "�����ֶ�122");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_card.user_field123, '\001', "�����ֶ�123");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_card.user_field124, '\001', "�����ֶ�124");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_card.user_field125, '\001', "�����ֶ�125");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_card.user_field126, '\001', "�����ֶ�126");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_card.activate_ind, '\001', "�Ƿ��Ѽ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_card.cancel_date, '\001', "������������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_card.latest_card_no, '\001', "���½��ʿ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_card.user_field127, '\001', "�����ֶ�127");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_card.user_field128, '\001', "�����ֶ�128");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_card.user_field129, '\001', "�����ֶ�129");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_card.user_field130, '\001', "�����ֶ�130");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_card.user_field131, '\001', "�����ֶ�131");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_card.card_expire_date, '\001', "��Ƭ��Ч����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_card.user_field132, '\001', "�����ֶ�132");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_card.user_field133, '\001', "�����ֶ�133");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_card.user_field134, '\001', "�����ֶ�134");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_card.user_field135, '\001', "�����ֶ�135");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_card.user_field136, '\001', "�����ֶ�136");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_card.user_field137, '\001', "�����ֶ�137");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_card.user_field138, '\001', "�����ֶ�138");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_card.user_field139, '\001', "�����ֶ�139");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_card.user_field140, '\001', "�����ֶ�140");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_card.user_field141, '\001', "�����ֶ�141");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_card.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_card.user_field142, '\001', "�����ֶ�142");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_card.user_field143, '\001', "�����ֶ�143");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_card.user_field144, '\001', "�����ֶ�144");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_card.user_field145, '\001', "�����ֶ�145");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_card.is_check_flag, "1", sizeof(sdb_icps_wb_tm_card.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_CARD", SD_ICPS_WB_TM_CARD, NUMELE(SD_ICPS_WB_TM_CARD), &sdb_icps_wb_tm_card, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_card.logical_card_no), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ���˻�ƿ�Ŀ��
 */
int ffunc_parse_wbank_file_to_db_tm_gl_bal(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_GL_BAL sdb_icps_wb_tm_gl_bal;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_GL_BAL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_gl_bal, 0x00, sizeof(sdb_icps_wb_tm_gl_bal));
            pstrcopy(sdb_icps_wb_tm_gl_bal.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_gl_bal.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_gl_bal.file_order = rcdCnt;


            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_gl_bal.org  ,'\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_gl_bal.subject  ,'\001', "��Ŀ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_gl_bal.branch_id  ,'\001', "��֧�к�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_gl_bal.db_bal  ,'\001', "�跽���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_gl_bal.cr_bal  ,'\001', "�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_gl_bal.db_amt  ,'\001', "�跽������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_gl_bal.db_count  ,'\001', "�跽����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_gl_bal.cr_amt  ,'\001', "����������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_gl_bal.cr_count  ,'\001', "��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_gl_bal.last_db_bal ,'\001', "���ս跽���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_gl_bal.last_cr_bal ,'\001', "���մ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_gl_bal.last_mth_db_bal ,'\001', "����ĩ�跽���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_gl_bal.last_mth_cr_bal ,'\001', "����ĩ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_gl_bal.last_qtr_db_bal ,'\001', "�ϼ�ĩ�跽���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_gl_bal.last_qtr_cr_bal ,'\001', "�ϼ�ĩ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_gl_bal.last_yr_db_ba ,'\001', "����ĩ�跽���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_gl_bal.last_yr_cr_ba ,'\001', "����ĩ�������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_gl_bal.jpa_version ,'\001', "�ֹ����汾��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_gl_bal.product_cd ,'\001', "��Ʒ���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_gl_bal.bal_id ,'\001', "˳���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_gl_bal.bank_no ,'\001', "���д���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_gl_bal.bank_group_id ,'\001', "���Ŵ���");


            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_gl_bal.is_check_flag, "1", sizeof(sdb_icps_wb_tm_gl_bal.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_GL_BAL", SD_ICPS_WB_TM_GL_BAL, NUMELE(SD_ICPS_WB_TM_GL_BAL), &sdb_icps_wb_tm_gl_bal, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_gl_bal.subject), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ���üƻ���
 */
int ffunc_parse_wbank_file_to_db_tm_plan(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_PLAN sdb_icps_wb_tm_plan;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_plan, 0x00, sizeof(sdb_icps_wb_tm_plan));
            pstrcopy(sdb_icps_wb_tm_plan.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_plan.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_plan.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_plan.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_plan.plan_id, '\001', "��ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_plan.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_plan.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_plan.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_plan.plan_nbr, '\001', "���üƻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_plan.plan_type, '\001', "���üƻ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_plan.product_code, '\001', "��Ʒ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_plan.ref_nbr, '\001', "���ײο���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_plan.curr_balance, '\001', "��ǰ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_plan.begin_bal, '\001', "�ڳ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_plan.dispute_amt, '\001', "������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_plan.tot_due_amt, '\001', "��С�����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_plan.plan_add_date, '\001', "��¼��������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_plan.paid_out_date, '\001', "��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_plan.past_principal, '\001', "���ڱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_plan.past_interest, '\001', "������Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_plan.past_card_fee, '\001', "�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_plan.past_ovrlmt_fee, '\001', "���ڳ��޷�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_plan.past_lpc, '\001', "�������ɽ�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_plan.past_nsf_fee, '\001', "�����ʽ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_plan.past_txn_fee, '\001', "���ڽ��׷�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_plan.past_svc_fee, '\001', "���ڷ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_plan.past_ins, '\001', "���ڱ��ս��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_plan.past_user_fee1, '\001', "�����Զ������1");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_plan.past_user_fee2, '\001', "�����Զ������2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_plan.past_user_fee3, '\001', "�����Զ������3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_plan.past_user_fee4, '\001', "�����Զ������4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_plan.past_user_fee5, '\001', "�����Զ������5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_plan.past_user_fee6, '\001', "�����Զ������6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_plan.CTD_PRINCIPAL, '\001', "��ǰ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_plan.ctd_interest, '\001', "������Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_plan.ctd_card_fee, '\001', "�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_plan.ctd_ovrlmt_fee, '\001', "���ڳ��޷�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_plan.ctd_lpc, '\001', "�������ɽ�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_plan.ctd_nsf_fee, '\001', "�����ʽ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_plan.ctd_svc_fee, '\001', "���ڷ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_plan.ctd_txn_fee, '\001', "���ڽ��׷�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_plan.ctd_ins, '\001', "���ڱ��ս��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_plan.ctd_user_fee1, '\001', "���������Զ������1";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_plan.ctd_user_fee2, '\001', "���������Զ������2";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_plan.ctd_user_fee3, '\001', "���������Զ������3";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_plan.ctd_user_fee4, '\001', "���������Զ������4";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_plan.ctd_user_fee5, '\001', "���������Զ������5";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_plan.ctd_user_fee6, '\001', "���������Զ������6";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_plan.ctd_amt_db, '\001', "���ڽ�ǽ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_plan.ctd_amt_cr, '\001', "���ڴ��ǽ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_plan.ctd_nbr_db, '\001', "���ڽ�ǽ��ױ���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_plan.ctd_nbr_cr, '\001', "���ڴ��ǽ��ױ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_plan.nodefbnp_int_acru, '\001', "���ӳ���Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_plan.beg_defbnp_int_acru, '\001', "�����ۻ���ʱ��Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_plan.ctd_defbnp_int_acru, '\001', "�����ۻ���ʱ��Ϣ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_plan.user_field146, '\001', "�����ֶ�146");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_plan.user_field147, '\001', "�����ֶ�147");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_plan.user_field148, '\001', "�����ֶ�148");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_plan.user_field149, '\001', "�����ֶ�149");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_plan.user_field150, '\001', "�����ֶ�150");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_plan.user_field151, '\001', "�����ֶ�151");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_plan.user_field152, '\001', "�����ֶ�152");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_plan.user_field153, '\001', "�����ֶ�153");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_plan.user_field154, '\001', "�����ֶ�154");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_plan.user_field155, '\001', "�����ֶ�155");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_plan.user_field156, '\001', "�����ֶ�156");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_plan.user_field157, '\001', "�����ֶ�157");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_plan.user_field158, '\001', "�����ֶ�158");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_plan.user_field159, '\001', "�����ֶ�159");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_plan.user_field160, '\001', "�����ֶ�160");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_plan.user_field161, '\001', "�����ֶ�161");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_plan.user_field162, '\001', "�����ֶ�162");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_plan.user_field163, '\001', "�����ֶ�163");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_plan.user_field164, '\001', "�����ֶ�164");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_plan.user_field165, '\001', "�����ֶ�165");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_plan.user_field166, '\001', "�����ֶ�166");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_plan.user_field167, '\001', "�����ֶ�167");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_plan.user_field168, '\001', "�����ֶ�168");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_plan.user_field169, '\001', "�����ֶ�169");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_wb_tm_plan.user_field170, '\001', "�����ֶ�170");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 78, sdb_icps_wb_tm_plan.user_field171, '\001', "�����ֶ�171");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 79, sdb_icps_wb_tm_plan.user_field172, '\001', "�����ֶ�172");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 80, sdb_icps_wb_tm_plan.user_field173, '\001', "�����ֶ�173");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 81, sdb_icps_wb_tm_plan.user_field174, '\001', "�����ֶ�174");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wb_tm_plan.user_field175, '\001', "�����ֶ�175");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 83, sdb_icps_wb_tm_plan.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wb_tm_plan.past_penalty, '\001', "���ڷ�Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wb_tm_plan.ctd_penalty, '\001', "���ڷ�Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wb_tm_plan.past_compound, '\001', "���ڸ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wb_tm_plan.ctd_compound, '\001', "���ڸ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wb_tm_plan.penalty_acru, '\001', "��Ϣ�ۼ�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wb_tm_plan.compound_acru, '\001', "�����ۼ�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wb_tm_plan.interest_rate, '\001', "��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wb_tm_plan.penalty_rate, '\001', "��Ϣ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wb_tm_plan.compound_rate, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 93, sdb_icps_wb_tm_plan.use_plan_rate, '\001', "�Ƿ�ʹ��plan������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 94, sdb_icps_wb_tm_plan.last_pmt_date, '\001', "��һ��������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 95, sdb_icps_wb_tm_plan.term, '\001', "���ڴ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_wb_tm_plan.calc_type, '\001', "�Ʒ�����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 97, sdb_icps_wb_tm_plan.calc_cycle, '\001', "�Ʒ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wb_tm_plan.fee_rate, '\001', "����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 99, sdb_icps_wb_tm_plan.last_fee_date, '\001', "��һ�շ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 100, sdb_icps_wb_tm_plan.next_fee_date, '\001', "��һ�շ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_wb_tm_plan.trans_serial, '\001', "������ˮ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 102, sdb_icps_wb_tm_plan.first_dd_date, '\001', "�״�Լ����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wb_tm_plan.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wb_tm_plan.sys_trans_id, '\001', "ϵͳ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_wb_tm_plan.user_field176, '\001', "�����ֶ�176");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_wb_tm_plan.sub_terminal_type, '\001', "�ն�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_wb_tm_plan.sub_merch_id, '\001', "�����̻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_wb_tm_plan.sub_merch_name, '\001', "�����̻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_wb_tm_plan.wares_desc, '\001', "��Ʒ��Ϣ");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 110, sdb_icps_wb_tm_plan.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 111, sdb_icps_wb_tm_plan.original_amt, '\001', "ԭʼ���ױ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 112, sdb_icps_wb_tm_plan.interest_calc_base, '\001', "��Ϣ����");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 113, sdb_icps_wb_tm_plan.created_datetime, '\001', "����ʱ��");



            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_plan.is_check_flag, "1", sizeof(sdb_icps_wb_tm_plan.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_PLAN", SD_ICPS_WB_TM_PLAN, NUMELE(SD_ICPS_WB_TM_PLAN), &sdb_icps_wb_tm_plan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_plan.plan_id), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ��������
 */
int ffunc_parse_wbank_file_to_db_tm_app_main(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_APP_MAIN sdb_icps_wb_tm_app_main;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_APP_MAIN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_app_main, 0x00, sizeof(sdb_icps_wb_tm_app_main));
            pstrcopy(sdb_icps_wb_tm_app_main.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_app_main.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_app_main.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_app_main.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_app_main.app_no, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_app_main.user_field1, '\001', "�����ֶ�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_app_main.user_field2, '\001', "�����ֶ�2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_app_main.user_field3, '\001', "�����ֶ�3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_app_main.acc_lmt, '\001', "��׼���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_app_main.product_cd, '\001', "����Ʒ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_app_main.user_field4, '\001', "�����ֶ�4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_app_main.user_field5, '\001', "�����ֶ�5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_app_main.user_field6, '\001', "�����ֶ�6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_app_main.user_field7, '\001', "�����ֶ�7");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_app_main.user_field8, '\001', "�����ֶ�8");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_app_main.user_field9, '\001', "�����ֶ�9");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_app_main.user_field10, '\001', "�����ֶ�10");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_app_main.user_field11, '\001', "�����ֶ�11");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_app_main.user_field12, '\001', "�����ֶ�12");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_app_main.user_field13, '\001', "�����ֶ�13");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_app_main.user_field14, '\001', "�����ֶ�14");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_app_main.user_field15, '\001', "�����ֶ�15");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_app_main.user_field16, '\001', "�����ֶ�16");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_app_main.user_field17, '\001', "�����ֶ�17");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_app_main.user_field18, '\001', "�����ֶ�18");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_app_main.user_field19, '\001', "�����ֶ�19");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_app_main.user_field20, '\001', "�����ֶ�20");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_app_main.user_field21, '\001', "�����ֶ�21");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_app_main.user_field22, '\001', "�����ֶ�22");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_app_main.user_field23, '\001', "�����ֶ�23");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_app_main.user_field24, '\001', "�����ֶ�24");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_app_main.user_field25, '\001', "�����ֶ�25");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_app_main.user_field26, '\001', "�����ֶ�26");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_app_main.user_field27, '\001', "�����ֶ�27");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_app_main.user_field28, '\001', "�����ֶ�28");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_app_main.user_field29, '\001', "�����ֶ�29");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_app_main.user_field30, '\001', "�����ֶ�30");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_app_main.user_field31, '\001', "�����ֶ�31");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_app_main.user_field32, '\001', "�����ֶ�32");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_app_main.user_field33, '\001', "�����ֶ�33");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_app_main.user_field34, '\001', "�����ֶ�34");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_app_main.user_field35, '\001', "�����ֶ�35");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_app_main.user_field36, '\001', "�����ֶ�36");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_app_main.user_field37, '\001', "�����ֶ�37");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_app_main.user_field38, '\001', "�����ֶ�38");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_app_main.user_field39, '\001', "�����ֶ�39");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_app_main.user_field40, '\001', "�����ֶ�40");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_app_main.user_field41, '\001', "�����ֶ�41");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_app_main.user_field42, '\001', "�����ֶ�42");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_app_main.user_field43, '\001', "�����ֶ�43");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_app_main.user_field44, '\001', "�����ֶ�44");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_app_main.user_field45, '\001', "�����ֶ�45");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_app_main.user_field46, '\001', "�����ֶ�46");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_app_main.user_field47, '\001', "�����ֶ�47");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_app_main.user_field48, '\001', "�����ֶ�48");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_app_main.user_field49, '\001', "�����ֶ�49");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_app_main.user_field50, '\001', "�����ֶ�50");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_app_main.user_field51, '\001', "�����ֶ�51");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_app_main.last_modified_datetime, '\001', "����޸�ʱ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_app_main.jpa_Vversion, '\001', "�ֹ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_app_main.uesr_field52, '\001', "�����ֶ�52");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_app_main.is_check_flag, "1", sizeof(sdb_icps_wb_tm_app_main.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_APP_MAIN", SD_ICPS_WB_TM_APP_MAIN, NUMELE(SD_ICPS_WB_TM_APP_MAIN), &sdb_icps_wb_tm_app_main, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_app_main.app_no), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ������������Ϣ��
 */
int ffunc_parse_wbank_file_to_db_tm_app_prim_applicant_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_APP_INFO sdb_icps_wb_tm_app_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_APP_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_app_info, 0x00, sizeof(sdb_icps_wb_tm_app_info));
            pstrcopy(sdb_icps_wb_tm_app_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_app_info.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_app_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_app_info.id, '\001', "��ʶ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_app_info.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_app_info.app_no, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_app_info.user_field53, '\001', "�����ֶ�53");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_app_info.user_field54, '\001', "�����ֶ�54");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_app_info.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_app_info.emb_logo, '\001', "͹ӡ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_app_info.gender, '\001', "�Ա�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_app_info.nationality, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_app_info.residency_country_cd, '\001', "���þ�ס�ع��Ҵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_app_info.id_type, '\001', "֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_app_info.id_no, '\001', "֤������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_app_info.user_field55, '\001', "�����ֶ�55");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_app_info.user_field56, '\001', "�����ֶ�56");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_app_info.birthday, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_app_info.user_field57, '\001', "�����ֶ�57");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_app_info.user_field58, '\001', "�����ֶ�58");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_app_info.user_field59, '\001', "�����ֶ�59");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_app_info.user_field60, '\001', "�����ֶ�60");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_app_info.user_field61, '\001', "�����ֶ�61");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_app_info.user_field62, '\001', "�����ֶ�62");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_app_info.user_field63, '\001', "�����ֶ�63");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_app_info.user_field64, '\001', "�����ֶ�64");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_app_info.user_field65, '\001', "�����ֶ�65");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_app_info.user_field66, '\001', "�����ֶ�66");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_app_info.user_field67, '\001', "�����ֶ�67");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_app_info.user_field68, '\001', "�����ֶ�68");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_app_info.user_field69, '\001', "�����ֶ�69");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_app_info.cellphone, '\001', "�ƶ��绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_app_info.user_field70, '\001', "�����ֶ�70");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_app_info.user_field71, '\001', "�����ֶ�71");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_app_info.user_field72, '\001', "�����ֶ�72");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_app_info.user_field73, '\001', "�����ֶ�73");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_app_info.user_field74, '\001', "�����ֶ�74");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_app_info.user_field75, '\001', "�����ֶ�75");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_app_info.user_field76, '\001', "�����ֶ�76");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_app_info.user_field77, '\001', "�����ֶ�77");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_app_info.user_field78, '\001', "�����ֶ�78");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_app_info.user_field79, '\001', "�����ֶ�79");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_app_info.user_field80, '\001', "�����ֶ�80");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_app_info.user_field81, '\001', "�����ֶ�81");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_app_info.user_field82, '\001', "�����ֶ�82");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_app_info.user_field83, '\001', "�����ֶ�83");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_app_info.user_field84, '\001', "�����ֶ�84");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_app_info.user_field85, '\001', "�����ֶ�85");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_app_info.user_field86, '\001', "�����ֶ�86");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_app_info.user_field87, '\001', "�����ֶ�87");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_app_info.user_field88, '\001', "�����ֶ�88");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_app_info.user_field89, '\001', "�����ֶ�89");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_app_info.user_field90, '\001', "�����ֶ�90");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_app_info.user_field91, '\001', "�����ֶ�91");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_app_info.user_field92, '\001', "�����ֶ�92");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_app_info.user_field93, '\001', "�����ֶ�93");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_app_info.user_field94, '\001', "�����ֶ�94");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_app_info.user_field95, '\001', "�����ֶ�95");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_app_info.user_field96, '\001', "�����ֶ�96");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_app_info.user_field97, '\001', "�����ֶ�97");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_app_info.user_field98, '\001', "�����ֶ�98");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_app_info.user_field99, '\001', "�����ֶ�99");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_app_info.pr_of_country, '\001', "�Ƿ����þ�ס");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_app_info.user_field100, '\001', "�����ֶ�100");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_app_info.user_field101, '\001', "�����ֶ�101");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_app_info.user_field102, '\001', "�����ֶ�102");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_app_info.user_field103, '\001', "�����ֶ�103");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_app_info.user_field104, '\001', "�����ֶ�104");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_app_info.user_field105, '\001', "�����ֶ�105");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_app_info.user_field106, '\001', "�����ֶ�106");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_app_info.user_field107, '\001', "�����ֶ�107");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_app_info.user_field108, '\001', "�����ֶ�108");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_app_info.user_field109, '\001', "�����ֶ�109");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_app_info.user_field110, '\001', "�����ֶ�110");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_app_info.user_field111, '\001', "�����ֶ�111");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_app_info.user_field112, '\001', "�����ֶ�112");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_app_info.jpa_version, '\001', "�ֹ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_app_info.cust_no, '\001', "�ͻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_app_info.acct_no, '\001', "�˻���");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_app_info.is_check_flag, "1", sizeof(sdb_icps_wb_tm_app_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_APP_INFO", SD_ICPS_WB_TM_APP_INFO, NUMELE(SD_ICPS_WB_TM_APP_INFO),
                    &sdb_icps_wb_tm_app_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_app_info.app_no), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �ͻ���Ϣ��
 */
int ffunc_parse_wbank_file_to_db_tm_customer(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_CUSTOMER sdb_icps_wb_tm_app_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_CUSTOMER WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_app_info, 0x00, sizeof(sdb_icps_wb_tm_app_info));
            pstrcopy(sdb_icps_wb_tm_app_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_app_info.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_app_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_app_info.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_app_info.cust_id, '\001', "�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_app_info.id_num, '\001', "֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_app_info.id_type, '\001', "֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_app_info.title, '\001', "��ν");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_app_info.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_app_info.gender, '\001', "�Ա�");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_app_info.brith_date, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_app_info.user_field177, '\001', "�����ֶ�177");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_app_info.user_field178, '\001', "�����ֶ�178");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_app_info.nationality, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_app_info.pr_of_country, '\001', "�Ƿ����þ�ס");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_app_info.residency_country_cd, '\001', "���þ�ס�ع��Ҵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_app_info.user_field179, '\001', "�����ֶ�179");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_app_info.user_field180, '\001', "�����ֶ�180");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_app_info.user_field181, '\001', "�����ֶ�181");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_app_info.user_field182, '\001', "�����ֶ�182");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_app_info.user_field183, '\001', "�����ֶ�183");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_app_info.user_field184, '\001', "�����ֶ�184");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_app_info.user_field185, '\001', "�����ֶ�185");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_app_info.user_field186, '\001', "�����ֶ�186");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_app_info.user_field187, '\001', "�����ֶ�187");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_app_info.mobile_no, '\001', "�ƶ��绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_app_info.user_field188, '\001', "�����ֶ�188");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_app_info.user_field189, '\001', "�����ֶ�189");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_app_info.user_field190, '\001', "�����ֶ�190");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_app_info.language_ind, '\001', "���Դ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_app_info.user_field191, '\001', "�����ֶ�191");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_app_info.user_field192, '\001', "�����ֶ�192");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_app_info.user_field193, '\001', "�����ֶ�193");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_app_info.user_field194, '\001', "�����ֶ�194");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_app_info.user_field195, '\001', "�����ֶ�195");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_app_info.user_field196, '\001', "�����ֶ�196");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_app_info.user_field197, '\001', "�����ֶ�197");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_app_info.user_field198, '\001', "�����ֶ�198");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_app_info.user_field199, '\001', "�����ֶ�199");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_app_info.user_field200, '\001', "�����ֶ�200");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_app_info.user_field201, '\001', "�����ֶ�201");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_app_info.user_field202, '\001', "�����ֶ�202");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_app_info.user_field203, '\001', "�����ֶ�203");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_app_info.user_field204, '\001', "�����ֶ�204");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_app_info.user_field205, '\001', "�����ֶ�205");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_app_info.user_field206, '\001', "�����ֶ�206");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_app_info.user_field207, '\001', "�����ֶ�207");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_app_info.user_field208, '\001', "�����ֶ�208");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_app_info.user_field209, '\001', "�����ֶ�209");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_app_info.user_field210, '\001', "�����ֶ�210");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_app_info.user_field211, '\001', "�����ֶ�211");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_app_info.user_field212, '\001', "�����ֶ�212");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_app_info.user_field213, '\001', "�����ֶ�213");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_app_info.user_field214, '\001', "�����ֶ�214");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_app_info.user_field215, '\001', "�����ֶ�215");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_app_info.user_field216, '\001', "�����ֶ�216");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_app_info.user_field217, '\001', "�����ֶ�217");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_app_info.user_field218, '\001', "�����ֶ�218");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_app_info.user_field219, '\001', "�����ֶ�219");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_app_info.user_field220, '\001', "�����ֶ�220");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_app_info.user_field221, '\001', "�����ֶ�221");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_app_info.user_field222, '\001', "�����ֶ�222");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_app_info.user_field223, '\001', "�����ֶ�223");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_app_info.user_field224, '\001', "�����ֶ�224");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_app_info.user_field225, '\001', "�����ֶ�225");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_app_info.user_field226, '\001', "�����ֶ�226");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_app_info.user_field227, '\001', "�����ֶ�227");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_app_info.user_field228, '\001', "�����ֶ�228");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_app_info.user_field229, '\001', "�����ֶ�229");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_app_info.emb_name, '\001', "ƴ����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_app_info.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_app_info.cust_limit_id, '\001', "�ͻ����ID");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_app_info.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_app_info.user_field230, '\001', "�����ֶ�230");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_app_info.user_field231, '\001', "�����ֶ�231");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_app_info.surname, '\001', "����");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_app_info.user_field232, '\001', "�����ֶ�232");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_app_info.user_field233, '\001', "�����ֶ�233");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_app_info.user_field234, '\001', "�����ֶ�234");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_app_info.is_check_flag, "1", sizeof(sdb_icps_wb_tm_app_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_CUSTOMER", SD_ICPS_WB_TM_CUSTOMER, NUMELE(SD_ICPS_WB_TM_CUSTOMER),
                    &sdb_icps_wb_tm_app_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_app_info.cust_id), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �������˽��ױ�
 */
int ffunc_parse_wbank_file_to_db_tt_txn_post(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TT_TXN_POST sdb_icps_wb_tt_txn_post;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TT_TXN_POST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tt_txn_post, 0x00, sizeof(sdb_icps_wb_tt_txn_post));
            pstrcopy(sdb_icps_wb_tt_txn_post.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tt_txn_post.busi_date)); /*ҵ������*/
            sdb_icps_wb_tt_txn_post.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tt_txn_post.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tt_txn_post.trans_serial, '\001', "������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tt_txn_post.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tt_txn_post.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tt_txn_post.card_no, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tt_txn_post.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tt_txn_post.bsc_logiccard_no, '\001', "�߼�����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tt_txn_post.product_code, '\001', "��Ʒ����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tt_txn_post.trans_date, '\001', "��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tt_txn_post.trans_time, '\001', "����ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tt_txn_post.post_txn_type, '\001', "���˽�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tt_txn_post.txn_code, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tt_txn_post.loan_flag, '\001', "�����־");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tt_txn_post.trans_amt, '\001', "���׽��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tt_txn_post.post_amt, '\001', "���˱��ֽ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tt_txn_post.transfer_in_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tt_txn_post.user_field235, '\001', "�����ֶ�235");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tt_txn_post.user_field236, '\001', "�����ֶ�236");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tt_txn_post.txn_curr_cd, '\001', "���ױ��ִ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tt_txn_post.post_curr_cd, '\001', "���˱��ִ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tt_txn_post.orig_trans_date, '\001', "ԭʼ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tt_txn_post.plan_nbr, '\001', "���üƻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tt_txn_post.ref_nbr, '\001', "���ײο���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tt_txn_post.txn_desc, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tt_txn_post.txn_short_desc, '\001', "�˵���������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tt_txn_post.user_field237, '\001', "�����ֶ�237");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tt_txn_post.posting_flag, '\001', "���˽����ʾ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tt_txn_post.pre_posting_flag, '\001', "�������˽����ʾ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tt_txn_post.user_field238, '\001', "�����ֶ�238");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tt_txn_post.orig_pmt_amt, '\001', "�����ԭʼ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tt_txn_post.user_field239, '\001', "�����ֶ�239");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tt_txn_post.user_field240, '\001', "�����ֶ�240");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tt_txn_post.user_field241, '\001', "�����ֶ�241");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tt_txn_post.user_field242, '\001', "�����ֶ�242");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tt_txn_post.mcc, '\001', "�̻�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tt_txn_post.input_txn_code, '\001', "ԭ���׽�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tt_txn_post.input_txn_amt, '\001', "ԭ���׽��׽��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tt_txn_post.input_sett_amt, '\001', "ԭ����������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tt_txn_post.user_field246, '\001', "�����ֶ�246");
            /*TODO:�˴�ʾ���ļ����ĵ��� �����ֶ�*/
            //ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tt_txn_post.not_sure1, '\001', "��ʱʹ��1");
            //ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tt_txn_post.not_sure2, '\001', "��ʱʹ��2");
            //ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tt_txn_post.not_sure3, '\001', "��ʱʹ��3");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tt_txn_post.stmt_date, '\001', "��һ���ڻ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tt_txn_post.user_field247, '\001', "�����ֶ�247");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tt_txn_post.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tt_txn_post.term, '\001', "���ڴ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tt_txn_post.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tt_txn_post.sys_trans_id, '\001', "ϵͳ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tt_txn_post.user_field248, '\001', "�����ֶ�248");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tt_txn_post.sub_terminal_type, '\001', "�ն�����");
            /*TODO:�˴�ʾ���ļ����ĵ��� �����ֶ�*/
            //ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tt_txn_post.not_sure4, '\001', "��ʱʹ��4");
            //ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tt_txn_post.not_sure5, '\001', "��ʱʹ��5");
            //ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tt_txn_post.not_sure6, '\001', "��ʱʹ��6");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tt_txn_post.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tt_txn_post.paid_stmt_date, '\001', "�����Ӧ�����գ�û�ã�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tt_txn_post.repay_amt, '\001', "Ӧ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tt_txn_post.bank_proportion, '\001', "���г��ʱ���");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tt_txn_post.is_check_flag, "1", sizeof(sdb_icps_wb_tt_txn_post.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TT_TXN_POST", SD_ICPS_WB_TT_TXN_POST, NUMELE(SD_ICPS_WB_TT_TXN_POST),
                    &sdb_icps_wb_tt_txn_post, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tt_txn_post.trans_serial), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ���˽�����ʷ��
 */
int ffunc_parse_wbank_file_to_db_tm_txn_reject(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_TXN_REJECT sdb_icps_wb_tm_txn_reject;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_TXN_REJECT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_txn_reject, 0x00, sizeof(sdb_icps_wb_tm_txn_reject));
            pstrcopy(sdb_icps_wb_tm_txn_reject.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_txn_reject.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_txn_reject.file_order = rcdCnt;


            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_txn_reject.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_txn_reject.trans_serial, '\001', "������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_txn_reject.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_txn_reject.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_txn_reject.card_no, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_txn_reject.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_txn_reject.bsc_logiccard_no, '\001', "�߼�����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_txn_reject.product_code, '\001', "��Ʒ����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_txn_reject.trans_date, '\001', "��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_txn_reject.trans_time, '\001', "����ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_txn_reject.post_txn_type, '\001', "���˽�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_txn_reject.txn_code, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_txn_reject.loan_flag, '\001', "�����־");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_txn_reject.trans_amt, '\001', "���׽��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_txn_reject.post_amt, '\001', "���˱��ֽ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_txn_reject.transfer_in_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_txn_reject.user_field252, '\001', "�����ֶ�252");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_txn_reject.user_field253, '\001', "�����ֶ�253");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_txn_reject.txn_curr_cd, '\001', "���ױ��ִ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_txn_reject.post_curr_cd, '\001', "���˱��ִ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_txn_reject.orig_trans_date, '\001', "ԭʼ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_txn_reject.plan_nbr, '\001', "���üƻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_txn_reject.ref_nbr, '\001', "���ײο���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_txn_reject.txn_desc, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_txn_reject.txn_short_desc, '\001', "�˵���������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_txn_reject.user_field254, '\001', "�����ֶ�254");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_txn_reject.posting_flag, '\001', "���˽����ʾ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_txn_reject.pre_posting_flag, '\001', "�������˽����ʾ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_txn_reject.user_field255, '\001', "�����ֶ�255");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_txn_reject.orig_pmt_amt, '\001', "�����ԭʼ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_txn_reject.user_field256, '\001', "�����ֶ�256");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_txn_reject.user_field257, '\001', "�����ֶ�257");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_txn_reject.user_field258, '\001', "�����ֶ�258");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_txn_reject.user_field259, '\001', "�����ֶ�259");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_txn_reject.mcc, '\001', "�̻�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_txn_reject.input_txn_code, '\001', "ԭ���׽�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_txn_reject.input_txn_amt, '\001', "ԭ���׽��׽��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_txn_reject.input_sett_amt, '\001', "ԭ����������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_txn_reject.user_field260, '\001', "�����ֶ�260");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_txn_reject.user_field261, '\001', "�����ֶ�261");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_txn_reject.user_field262, '\001', "�����ֶ�262");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_txn_reject.user_field263, '\001', "�����ֶ�263");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_txn_reject.stmt_date, '\001', "��һ���ڻ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_txn_reject.voucher_no, '\001', "���۵�ƾ֤��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_txn_reject.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_txn_reject.term, '\001', "���ڴ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_txn_reject.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_txn_reject.sys_trans_id, '\001', "ϵͳ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_txn_reject.user_field265, '\001', "�����ֶ�265");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_txn_reject.user_field264, '\001', "�����ֶ�264");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_txn_reject.sub_terminal_type, '\001', "�ն�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_txn_reject.user_field266, '\001', "�����ֶ�266");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_txn_reject.user_field267, '\001', "�����ֶ�267");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_txn_reject.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_txn_reject.paid_stmt_date, '\001', "�������������գ����ã�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_txn_reject.repay_amt, '\001', "Ӧ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_txn_reject.bank_proportion, '\001', "���г��ʱ���");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_txn_reject.is_check_flag, "1", sizeof(sdb_icps_wb_tm_txn_reject.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_TXN_REJECT", SD_ICPS_WB_TM_TXN_REJECT, NUMELE(SD_ICPS_WB_TM_TXN_REJECT),
                    &sdb_icps_wb_tm_txn_reject, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_txn_reject.trans_serial), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ������Ϣ��
 */
int ffunc_parse_wbank_file_to_db_tm_loan(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_LOAN sdb_icps_wb_tm_loan;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_LOAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_loan, 0x00, sizeof(sdb_icps_wb_tm_loan));
            pstrcopy(sdb_icps_wb_tm_loan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_loan.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_loan.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_loan.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_loan.loan_id, '\001', "���ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_loan.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_loan.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_loan.ref_nbr, '\001', "���ײο���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_loan.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_loan.card_no, '\001', "����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_loan.register_date, '\001', "����ע������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_loan.request_time, '\001', "��������ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_loan.loan_type, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_loan.loan_status, '\001', "����״̬");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_loan.last_loan_status, '\001', "�����ϴ�״̬");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_loan.loan_init_term, '\001', "����������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_loan.curr_term, '\001', "��ǰ����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_loan.remain_term, '\001', "ʣ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_loan.loan_init_prin, '\001', "�����ܱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_loan.loan_fixed_pmt_prin, '\001', "����ÿ��Ӧ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_loan.loan_first_term_prin, '\001', "��������Ӧ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_loan.loan_final_term_prin, '\001', "����ĩ��Ӧ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_loan.loan_init_fee1, '\001', "������������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_loan.loan_fixed_fee1, '\001', "����ÿ��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_loan.loan_first_term_fee1, '\001', "��������������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_loan.loan_final_term_fee1, '\001', "����ĩ��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_loan.unearned_prin, '\001', "�����˵��ı���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_loan.unearned_fee1, '\001', "�����˵�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_loan.paid_out_date, '\001', "��������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_loan.terminate_date, '\001', "��ǰ��ֹ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_loan.terminate_reason_cd, '\001', "������ֹԭ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_loan.prin_paid, '\001', "�ѳ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_loan.int_paid, '\001', "�ѳ�����Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_loan.fee_paid, '\001', "�ѳ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_loan.loan_curr_bal, '\001', "���ǰ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_loan.loan_bal_xfrout, '\001', "����δ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_loan.loan_bal_xfrin, '\001', "�����ѵ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_loan.loan_bal_principal, '\001', "Ƿ���ܱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_loan.loan_bal_interest, '\001', "Ƿ������Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_loan.loan_bal_penalty, '\001', "Ƿ���ܷ�Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_loan.loan_prin_xfrout, '\001', "����δ���ڱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_loan.loan_prin_xfrin, '\001', "�����ѵ��ڱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_loan.loan_fee1_xfrout, '\001', "����δ����������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_loan.loan_fee1_xfrin, '\001', "�����ѵ���������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_loan.orig_txn_amt, '\001', "ԭʼ���ױ��ֽ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_loan.orig_trans_date, '\001', "ԭʼ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_loan.orig_auth_code, '\001', "ԭʼ������Ȩ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_loan.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_loan.loan_code, '\001', "�����Ʒ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_loan.register_id, '\001', "��������˳���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_loan.resch_init_prin, '\001', "չ�ڱ�����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_loan.resch_date, '\001', "չ����Ч����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_loan.bef_resch_fixed_pmt_prin, '\001', "չ��ǰÿ��Ӧ������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_loan.bef_resch_init_term, '\001', "չ��ǰ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_loan.bef_resch_first_term_prin, '\001', "չ��ǰ��������Ӧ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_loan.bef_resch_final_term_prin, '\001', "չ��ǰ����ĩ��Ӧ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_loan.bef_resch_init_fee1, '\001', "չ��ǰ������������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_loan.bef_resch_fixed_fee1, '\001', "BEF_����ÿ��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_loan.bef_resch_first_term_fee1, '\001', "չ��ǰ��������������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_loan.bef_resch_final_term_fee1, '\001', "չ��ǰ����ĩ��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_loan.resch_first_term_fee1, '\001', "չ�ں�����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_loan.loan_fee_method, '\001', "������������ȡ��ʽ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_loan.interest_rate, '\001', "��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_loan.penalty_rate, '\001', "��Ϣ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_loan.compound_rate, '\001', "��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_loan.float_rate, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_loan.loan_receipt_nbr, '\001', "��ݺ�");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_loan.loan_expire_date, '\001', "���������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_loan.loan_cd, '\001', "���������������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_loan.payment_hist, '\001', "24���»���״̬");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_loan.ctd_payment_amt, '\001', "���ڻ����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_loan.past_resch_cnt, '\001', "��չ�ڴ���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_loan.past_shorted_cnt, '\001', "�����ڴ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_loan.adv_pmt_amt, '\001', "��ǰ������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_loan.last_action_date, '\001', "�ϴ��ж�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_loan.last_action_type, '\001', "�ϴ��ж�����");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_loan.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_loan.activate_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_loan.interest_calc_base, '\001', "��Ϣ����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wb_tm_loan.first_bill_date, '\001', "�׸����ڻ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_wb_tm_loan.age_cd, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_wb_tm_loan.recalc_ind, '\001', "���������־");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wb_tm_loan.recalc_date, '\001', "����������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 81, sdb_icps_wb_tm_loan.grace_date, '\001', "��������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 82, sdb_icps_wb_tm_loan.cancel_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_wb_tm_loan.cancel_reason, '\001', "�����ԭ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_wb_tm_loan.bank_group_id, '\001', "���ű��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 85, sdb_icps_wb_tm_loan.due_days, '\001', "��ǰ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_wb_tm_loan.contract_ver, '\001', "��ͬ�汾��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wb_tm_loan.loan_init_interest, '\001', "��������Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wb_tm_loan.bef_init_interest, '\001', "ԭ��������Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wb_tm_loan.bank_proportion, '\001', "���г��ʱ���");


            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_loan.is_check_flag, "1", sizeof(sdb_icps_wb_tm_loan.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_LOAN", SD_ICPS_WB_TM_LOAN, NUMELE(SD_ICPS_WB_TM_LOAN),
                    &sdb_icps_wb_tm_loan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_loan.ref_nbr), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ��������
 */
int ffunc_parse_wbank_file_to_db_tm_schedule(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_SCHEDULE sdb_icps_wb_tm_schedule;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_SCHEDULE WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_schedule, 0x00, sizeof(sdb_icps_wb_tm_schedule));
            pstrcopy(sdb_icps_wb_tm_schedule.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_schedule.busi_date)); /*ҵ������*/
            sdb_icps_wb_tm_schedule.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_schedule.schedule_id, '\001', "�����ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_schedule.loan_id, '\001', "����ƻ�ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_schedule.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_schedule.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_schedule.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_schedule.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_schedule.card_no, '\001', "����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_schedule.loan_init_prin, '\001', "�����ܱ���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_schedule.loan_init_term, '\001', "����������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_schedule.curr_term, '\001', "��ǰ����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_schedule.loan_term_prin, '\001', "Ӧ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_schedule.loan_term_fee1, '\001', "Ӧ������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_schedule.loan_term_interest, '\001', "Ӧ����Ϣ");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_schedule.loan_pmt_due_date, '\001', "����ڻ�������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_schedule.loan_grace_date, '\001', "������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_schedule.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_schedule.start_date, '\001', "��Ϣ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_schedule.schedule_action, '\001', "����ƻ���������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_schedule.prin_paid, '\001', "�ѳ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_schedule.int_paid, '\001', "�ѳ�����Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_schedule.penalty_paid, '\001', "�ѳ�����Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_schedule.compound_paid, '\001', "�ѳ�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_schedule.fee_paid, '\001', "�ѳ�������");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_tm_schedule.is_check_flag, "1", sizeof(sdb_icps_wb_tm_schedule.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_SCHEDULE", SD_ICPS_WB_TM_SCHEDULE, NUMELE(SD_ICPS_WB_TM_SCHEDULE),
                    &sdb_icps_wb_tm_schedule, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_tm_schedule.schedule_id), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ��Ʒ�¼�ձ���
 */
int ffunc_parse_wbank_file_to_db_ds_accounting_flow(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_DS_ACCOUNTING_FLOW sdb_icps_wb_ds_accounting_flow;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_ACCOUNTING_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_ds_accounting_flow, 0x00, sizeof(sdb_icps_wb_ds_accounting_flow));
            pstrcopy(sdb_icps_wb_ds_accounting_flow.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_ds_accounting_flow.busi_date)); /*ҵ������*/
            sdb_icps_wb_ds_accounting_flow.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_ds_accounting_flow.org, '\001', "�ڲ�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_ds_accounting_flow.host_trans_serial, '\001', "���Ľ�����ˮ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_ds_accounting_flow.card_no, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_ds_accounting_flow.currency, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_ds_accounting_flow.txn_code, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_ds_accounting_flow.txn_desc, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_ds_accounting_flow.db_cr_ind, '\001', "������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_ds_accounting_flow.post_amt, '\001', "���˽��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_ds_accounting_flow.post_gl_ind, '\001', "���˷�ʽ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_ds_accounting_flow.owning_branch, '\001', "֧��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_ds_accounting_flow.subject, '\001', "��Ŀ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_ds_accounting_flow.red_flag, '\001', "�����ֱ�ʶ");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_ds_accounting_flow.queue, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_ds_accounting_flow.product_cd, '\001', "��Ʒ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_ds_accounting_flow.ref_nbr, '\001', "��ݺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_ds_accounting_flow.age_group, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_ds_accounting_flow.plan_nbr, '\001', "���üƻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_ds_accounting_flow.bnp_group, '\001', "���ɷ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_ds_accounting_flow.bank_group_id, '\001', "���Ŵ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_ds_accounting_flow.bank_no, '\001', "���д���");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_ds_accounting_flow.term, '\001', "����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_ds_accounting_flow.batchDate, '\001', "����");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_ds_accounting_flow.is_check_flag, "1", sizeof(sdb_icps_wb_ds_accounting_flow.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_ACCOUNTING_FLOW", SD_ICPS_WB_DS_ACCOUNTING_FLOW, NUMELE(SD_ICPS_WB_DS_ACCOUNTING_FLOW),
                    &sdb_icps_wb_ds_accounting_flow, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_ds_accounting_flow.host_trans_serial), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �Զ�������Ϣ��-��Ȩ
 */
int ffunc_parse_wbank_file_to_db_tm_cust_limit_o(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_CUST_LIMIT_O sdb_icps_tm_cust_limit_o;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_CUST_LIMIT_O WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_cust_limit_o, 0x00, sizeof(sdb_icps_tm_cust_limit_o));
            pstrcopy(sdb_icps_tm_cust_limit_o.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_cust_limit_o.busi_date)); /*ҵ������*/
            sdb_icps_tm_cust_limit_o.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_cust_limit_o.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_cust_limit_o.cust_limit_id, '\001', "�ͻ����ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_cust_limit_o.limit_category, '\001', "�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_cust_limit_o.limit_type, '\001', "�������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_cust_limit_o.credit_limit, '\001', "���ö��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_cust_limit_o.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_cust_limit_o.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_cust_limit_o.created_datetime, '\001', "����ʱ��");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_cust_limit_o.is_check_flag, "1", sizeof(sdb_icps_tm_cust_limit_o.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_CUST_LIMIT_O", SD_ICPS_WB_TM_CUST_LIMIT_O, NUMELE(SD_ICPS_WB_TM_CUST_LIMIT_O),
                    &sdb_icps_tm_cust_limit_o, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_tm_cust_limit_o.cust_limit_id), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ��Ȩ������ʷ
 */
int ffunc_parse_wbank_file_to_db_tm_auth_hst(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_AUTH_HST sdb_icps_tm_auth_hst;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_AUTH_HST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_auth_hst, 0x00, sizeof(sdb_icps_tm_auth_hst));
            pstrcopy(sdb_icps_tm_auth_hst.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_auth_hst.busi_date)); /*ҵ������*/
            sdb_icps_tm_auth_hst.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_auth_hst.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_auth_hst.log_kv, '\001', "LOG�ļ�ֵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_auth_hst.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_auth_hst.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_auth_hst.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_auth_hst.acq_ref_no, '\001', "����������ױ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_auth_hst.trans_amt, '\001', "���׽��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_auth_hst.txn_curr_cd, '\001', "���ױ��ִ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_auth_hst.user_field269, '\001', "�����ֶ�269");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_auth_hst.acq_name_addr, '\001', "����������Ƶ�ַ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_auth_hst.chb_txn_amt, '\001', "�ֿ����˻����ֽ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_auth_hst.chb_curr_cd, '\001', "�ֿ����˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_auth_hst.user_field270, '\001', "�����ֶ�270");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_auth_hst.mcc, '\001', "�̻�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_auth_hst.acq_branch_id, '\001', "������д���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_auth_hst.fwd_inst_id, '\001', "ת��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_auth_hst.transmission_timestamp, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_tm_auth_hst.settle_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_tm_auth_hst.txn_direction, '\001', "���׷���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_tm_auth_hst.txn_terminal, '\001', "�����ն�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_tm_auth_hst.trans_status, '\001', "����״̬");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_tm_auth_hst.trans_type, '\001', "��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 23, sdb_icps_tm_auth_hst.log_ol_time, '\001', "LOG����ʱ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 24, sdb_icps_tm_auth_hst.log_biz_date, '\001', "����ҵ������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_tm_auth_hst.mti, '\001', "�������ͱ�ʶ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_tm_auth_hst.orig_txn_type, '\001', "ԭ��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_tm_auth_hst.orig_fwd_inst_id, '\001', "ԭʼת��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_tm_auth_hst.orig_acq_inst_id, '\001', "ԭʼ���������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_tm_auth_hst.orig_mti, '\001', "ԭ����MTI");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_tm_auth_hst.orig_trans_date, '\001', "ԭʼ��������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 31, sdb_icps_tm_auth_hst.orig_trace_no, '\001', "ԭʼϵͳ���ٺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_tm_auth_hst.orig_txn_proc, '\001', "ԭ���״�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_tm_auth_hst.orig_txn_amt, '\001', "ԭʼ���ױ��ֽ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_tm_auth_hst.orig_log_kv, '\001', "ԭ����LOG��ֵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_tm_auth_hst.orig_txn_val_1, '\001', "ԭ���׼�ֵ1");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_tm_auth_hst.orig_txn_val_2, '\001', "ԭ���׼�ֵ2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_tm_auth_hst.orig_chb_txn_amt, '\001', "ԭʼ���˱��ֽ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 38, sdb_icps_tm_auth_hst.orig_biz_date, '\001', "ԭ���׵�����ҵ��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_tm_auth_hst.last_reversal_date, '\001', "���һ�γ峷ʱ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 40, sdb_icps_tm_auth_hst.void_count, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_tm_auth_hst.manual_auth_flag, '\001', "�˹���Ȩ��־");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_tm_auth_hst.opera_id, '\001', "����ԱID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_tm_auth_hst.brand, '\001', "Ʒ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_tm_auth_hst.product_code, '\001', "��Ʒ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_tm_auth_hst.mcc_type, '\001', "�̻����ͷ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_tm_auth_hst.user_field271, '\001', "�����ֶ�271");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_tm_auth_hst.user_field272, '\001', "�����ֶ�272");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_tm_auth_hst.comp_amt, '\001', "������Ȩ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_tm_auth_hst.final_upd_direction, '\001', "���ո��·���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_tm_auth_hst.final_upd_amt, '\001', "���ո��½��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_tm_auth_hst.ic_ind, '\001', "�Ƿ�IC��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_tm_auth_hst.the_3dsecure_type, '\001', "�Ƿ�3D���Ӱ�ȫ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_tm_auth_hst.vip_status, '\001', "VIP״̬");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_tm_auth_hst.curr_balance, '\001', "��ǰ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_tm_auth_hst.cash_amt, '\001', "ȡ�ֽ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_tm_auth_hst.otb, '\001', "���ö��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_tm_auth_hst.cash_otb, '\001', "ȡ�ֿ��ö��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_tm_auth_hst.cust_otb, '\001', "�ͻ����ö��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_tm_auth_hst.user_field273, '\001', "�����ֶ�273");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_tm_auth_hst.user_field274, '\001', "�����ֶ�274");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_tm_auth_hst.expire_date, '\001', "��Ч����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_tm_auth_hst.track_one_result, '\001', "һ�ŵ������Խ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_tm_auth_hst.track_two_result, '\001', "���ŵ������Խ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_tm_auth_hst.track_three_result, '\001', "���ŵ������Խ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_tm_auth_hst.pwd_type, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_tm_auth_hst.check_pwd_result, '\001', "��֤������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 67, sdb_icps_tm_auth_hst.pay_pwd_err_num, '\001', "֧������������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_tm_auth_hst.check_cvv_result, '\001', "CVV��֤���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_tm_auth_hst.check_cvv2_result, '\001', "CVV2��֤���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_tm_auth_hst.check_icvn_result, '\001', "ICVN��֤���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_tm_auth_hst.check_arqc_result, '\001', "ARQC��֤���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_tm_auth_hst.check_atc_result, '\001', "ATC��֤���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_tm_auth_hst.check_cvr_result, '\001', "CVR��֤���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 74, sdb_icps_tm_auth_hst.check_tvr_result, '\001', "TVR��֤���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_tm_auth_hst.user_field275, '\001', "�����ֶ�275");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 76, sdb_icps_tm_auth_hst.unmatch_cr, '\001', "δƥ����ǽ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_tm_auth_hst.unmatch_db, '\001', "δƥ���ǽ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_tm_auth_hst.b002, '\001', "���ʿ���-B002");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_tm_auth_hst.b003, '\001', "���״�����-B003");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 80, sdb_icps_tm_auth_hst.b007, '\001', "���״���ʱ��-B007");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 81, sdb_icps_tm_auth_hst.b011, '\001', "ϵͳ���ٺ�-B011");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 82, sdb_icps_tm_auth_hst.b022, '\001', "�����PIN��ȡ��-B022");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_tm_auth_hst.b025, '\001', "�����������-B025");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_tm_auth_hst.b032, '\001', "���������ʶ��-B032");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 85, sdb_icps_tm_auth_hst.b033, '\001', "����������Ƶ�ַ-B033");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_tm_auth_hst.b039, '\001', "������-B039");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 87, sdb_icps_tm_auth_hst.b042, '\001', "�ܿ���(�̻�)��ʶ��-B042");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 88, sdb_icps_tm_auth_hst.user_field277, '\001', "�����ֶ�276");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 89, sdb_icps_tm_auth_hst.user_field278, '\001', "�����ֶ�277");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 90, sdb_icps_tm_auth_hst.b090, '\001', "ԭʼ����Ԫ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 91, sdb_icps_tm_auth_hst.opera_term_id, '\001', "�����û��ն˱��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 92, sdb_icps_tm_auth_hst.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_tm_auth_hst.b004, '\001', "���׻��ҽ��-B004");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 94, sdb_icps_tm_auth_hst.b006, '\001', "�˻����ҽ��-B006");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 95, sdb_icps_tm_auth_hst.b049, '\001', "���׻��Ҵ���-B049");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_tm_auth_hst.b051, '\001', "�˻����Ҵ���-B051");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 97, sdb_icps_tm_auth_hst.b037, '\001', "�����ο���-B037");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_tm_auth_hst.b028, '\001', "������-B028");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 99, sdb_icps_tm_auth_hst.b048, '\001', "��������-B048");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 100, sdb_icps_tm_auth_hst.b054, '\001', "�����������-B054");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_tm_auth_hst.user_field279, '\001', "�����ֶ�278");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 102, sdb_icps_tm_auth_hst.user_field280, '\001', "�����ֶ�279");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_tm_auth_hst.user_field281, '\001', "�����ֶ�280");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_tm_auth_hst.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_tm_auth_hst.sys_trans_id, '\001', "ϵͳ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_tm_auth_hst.user_field282, '\001', "�����ֶ�281");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_tm_auth_hst.sub_terminal_type, '\001', "�ն�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_tm_auth_hst.sub_merch_id, '\001', "�����̻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_tm_auth_hst.sub_merch_name, '\001', "�����̻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 110, sdb_icps_tm_auth_hst.wares_desc, '\001', "��Ʒ��Ϣ");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 111, sdb_icps_tm_auth_hst.last_modified_datetime, '\001', "�޸�ʱ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 112, sdb_icps_tm_auth_hst.part_month, '\001', "�����õ��·�");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 113, sdb_icps_tm_auth_hst.paid_stmt_date, '\001', "�����˵���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_tm_auth_hst.repay_amt, '\001', "Ӧ�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 115, sdb_icps_tm_auth_hst.bank_proportion, '\001', "���г��ʱ���");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_auth_hst.is_check_flag, "1", sizeof(sdb_icps_tm_auth_hst.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_AUTH_HST", SD_ICPS_WB_TM_AUTH_HST, NUMELE(SD_ICPS_WB_TM_AUTH_HST),
                    &sdb_icps_tm_auth_hst, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_tm_auth_hst.log_kv), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �ͻ���ʱͨѶ��Ϣ��
 */
int ffunc_parse_wbank_file_to_db_tm_im_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_IM_INFO sdb_icps_tm_im_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_IM_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_im_info, 0x00, sizeof(sdb_icps_tm_im_info));
            pstrcopy(sdb_icps_tm_im_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_im_info.busi_date)); /*ҵ������*/
            sdb_icps_tm_im_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_im_info.seq_no, '\001', "���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_im_info.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_im_info.product_code, '\001', "��Ʒ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_im_info.cust_id, '\001', "�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_im_info.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_im_info.app_type, '\001', "Ӧ������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_im_info.app_acct_no, '\001', "Ӧ���˺�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_im_info.user_field282, '\001', "�����ֶ�282");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_im_info.created_datetime, '\001', "����ʱ��");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_im_info.update_time, '\001', "����ʱ��");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_im_info.jpa_version, '\001', "�ֹ����汾��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_im_info.last_update_biz_date, '\001', "�ϴ���������ҵ������");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_im_info.is_check_flag, "1", sizeof(sdb_icps_tm_im_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_IM_INFO", SD_ICPS_WB_TM_IM_INFO, NUMELE(SD_ICPS_WB_TM_IM_INFO), &sdb_icps_tm_im_info,
                    sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_tm_im_info.seq_no), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �������嵥��
 */
int ffunc_parse_wbank_file_to_db_tm_loan_receipt_list(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_LOAN_RECEIPT_LIST sdb_icps_tm_loan_receipt_list;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_LOAN_RECEIPT_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_loan_receipt_list, 0x00, sizeof(sdb_icps_tm_loan_receipt_list));
            pstrcopy(sdb_icps_tm_loan_receipt_list.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_tm_loan_receipt_list.busi_date)); /*ҵ������*/
            sdb_icps_tm_loan_receipt_list.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_loan_receipt_list.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_loan_receipt_list.sys_trans_id, '\001', "ϵͳ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_loan_receipt_list.loan_receipt_nbr, '\001', "��ݺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_loan_receipt_list.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_loan_receipt_list.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_loan_receipt_list.card_no, '\001', "����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_loan_receipt_list.transfer_in_date, '\001', "��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_loan_receipt_list.last_modified_datetime, '\001', "ʱ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_loan_receipt_list.pay_amt, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_loan_receipt_list.bank_group_id, '\001', "���ű��");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_loan_receipt_list.is_check_flag, "1", sizeof(sdb_icps_tm_loan_receipt_list.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_LOAN_RECEIPT_LIST", SD_ICPS_WB_TM_LOAN_RECEIPT_LIST, NUMELE(SD_ICPS_WB_TM_LOAN_RECEIPT_LIST), &sdb_icps_tm_loan_receipt_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("��[%d]����¼����ʧ��['%s','%s','%s']", rcdCnt, sdb_icps_tm_loan_receipt_list.busi_serial,
                                sdb_icps_tm_loan_receipt_list.sys_trans_id, sdb_icps_tm_loan_receipt_list.loan_receipt_nbr),
                        "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �������嵥����ʷ
 */
int ffunc_parse_wbank_file_to_db_tm_loan_receipt_list_hst(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_RE_HST sdb_icps_tm_re_hst;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_RE_HST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_re_hst, 0x00, sizeof(sdb_icps_tm_re_hst));
            pstrcopy(sdb_icps_tm_re_hst.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_re_hst.busi_date)); /*ҵ������*/
            sdb_icps_tm_re_hst.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_re_hst.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_re_hst.sys_trans_id, '\001', "ϵͳ������ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_re_hst.loan_receipt_nbr, '\001', "��ݺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_re_hst.acct_no, '\001', "�˻����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_re_hst.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_re_hst.card_no, '\001', "����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_re_hst.transfer_in_date, '\001', "��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_re_hst.last_modified_datetime, '\001', "ʱ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_re_hst.move_date, '\001', "ת������(��������ȡ��)");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_re_hst.part_month, '\001', "�����õ��·�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_re_hst.pay_amt, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_re_hst.bank_group_id, '\001', "���ű��");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_re_hst.is_check_flag, "1", sizeof(sdb_icps_tm_re_hst.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_RE_HST", SD_ICPS_WB_TM_RE_HST, NUMELE(SD_ICPS_WB_TM_RE_HST), &sdb_icps_tm_re_hst,
                    sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("��[%d]����¼����ʧ��['%s','%s','%s']", rcdCnt, sdb_icps_tm_re_hst.busi_serial,
                                sdb_icps_tm_re_hst.sys_trans_id, sdb_icps_tm_re_hst.loan_receipt_nbr), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �����Ϣ
 */
int ffunc_parse_wbank_file_to_db_tm_psb_personal_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_PSB_PERSONAL_INFO sdb_icps_tm_psb_personal_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_PSB_PERSONAL_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_psb_personal_info, 0x00, sizeof(sdb_icps_tm_psb_personal_info));
            pstrcopy(sdb_icps_tm_psb_personal_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_psb_personal_info.busi_date)); /*ҵ������*/
            sdb_icps_tm_psb_personal_info.file_order = rcdCnt;

            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_psb_personal_info.id, '\001', "ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_psb_personal_info.app_no, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_psb_personal_info.id_type, '\001', "֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_psb_personal_info.certi_no, '\001', "���֤��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_psb_personal_info.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_psb_personal_info.gender, '\001', "�Ա�");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_psb_personal_info.birth_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_psb_personal_info.marital_status, '\001', "����״��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_psb_personal_info.mobile_no, '\001', "�ֻ�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_psb_personal_info.home_phone, '\001', "��ͥ�绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_psb_personal_info.unit_phone, '\001', "��λ�绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_psb_personal_info.qualification, '\001', "ѧ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_psb_personal_info.degree, '\001', "ѧλ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_psb_personal_info.address, '\001', "ͨѶ��ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_psb_personal_info.reside_addr, '\001', "������ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_psb_personal_info.mate_certp, '\001', "��ż֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_psb_personal_info.mate_cerno, '\001', "��ż֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_tm_psb_personal_info.mate_name, '\001', "��ż����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_tm_psb_personal_info.mate_corp, '\001', "��ż������λ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_tm_psb_personal_info.mate_phone, '\001', "��ż��ϵ�绰");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_tm_psb_personal_info.addr, '\001', "��ס��ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_tm_psb_personal_info.reside_state, '\001', "��ס״��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_tm_psb_personal_info.comp_nm, '\001', "������λ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_tm_psb_personal_info.unit_addr, '\001', "��λ��ַ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_tm_psb_personal_info.profession, '\001', "ְҵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_tm_psb_personal_info.comp_trade, '\001', "��ҵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_tm_psb_personal_info.position, '\001', "ְ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_tm_psb_personal_info.teach_pose, '\001', "ְ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_tm_psb_personal_info.work_date, '\001', "����λ������ʼ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_tm_psb_personal_info.infodate, '\001', "��Ϣ��������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 31, sdb_icps_tm_psb_personal_info.create_time, '\001', "����ʱ��");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_psb_personal_info.is_check_flag, "1", sizeof(sdb_icps_tm_psb_personal_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_PSB_PERSONAL_INFO", SD_ICPS_WB_TM_PSB_PERSONAL_INFO, NUMELE(SD_ICPS_WB_TM_PSB_PERSONAL_INFO), &sdb_icps_tm_psb_personal_info,
                    sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_tm_psb_personal_info.id,
                                sdb_icps_tm_psb_personal_info.app_no), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �������ʽ��������
 */
int ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_tot(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_RRS_BDM_UDF_CLEAR_TOT sdb_icps_rrs_bdm_udf_clear_tot;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_RRS_BDM_UDF_CLEAR_TOT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_rrs_bdm_udf_clear_tot, 0x00, sizeof(sdb_icps_rrs_bdm_udf_clear_tot));
            pstrcopy(sdb_icps_rrs_bdm_udf_clear_tot.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_rrs_bdm_udf_clear_tot.busi_date)); /*ҵ������*/
            sdb_icps_rrs_bdm_udf_clear_tot.file_order = rcdCnt;

            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 1, sdb_icps_rrs_bdm_udf_clear_tot.data_dt, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_rrs_bdm_udf_clear_tot.acct_no, '\001', "�������ʺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_rrs_bdm_udf_clear_tot.currency, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_rrs_bdm_udf_clear_tot.acct_name, '\001', "����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_rrs_bdm_udf_clear_tot.last_balance, '\001', "�����˻����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_rrs_bdm_udf_clear_tot.balance, '\001', "�����˻����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_rrs_bdm_udf_clear_tot.payment_amt, '\001', "���շſ��ܽ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_rrs_bdm_udf_clear_tot.repayment_amt, '\001', "���ջ����ܽ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_rrs_bdm_udf_clear_tot.other_credit_amt, '\001', "���������������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_rrs_bdm_udf_clear_tot.other_debit_amt, '\001', "����������������");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 11, sdb_icps_rrs_bdm_udf_clear_tot.ds, '\001', "���ڷ���");

            /*������˱�־*/
            pstrcopy(sdb_icps_rrs_bdm_udf_clear_tot.is_check_flag, "1", sizeof(sdb_icps_rrs_bdm_udf_clear_tot.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_RRS_BDM_UDF_CLEAR_TOT", SD_ICPS_WB_RRS_BDM_UDF_CLEAR_TOT,
                    NUMELE(SD_ICPS_WB_RRS_BDM_UDF_CLEAR_TOT), &sdb_icps_rrs_bdm_udf_clear_tot, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("��[%d]����¼����ʧ��['%s','%s','%s']", rcdCnt, sdb_icps_rrs_bdm_udf_clear_tot.data_dt,
                                sdb_icps_rrs_bdm_udf_clear_tot.acct_no, sdb_icps_rrs_bdm_udf_clear_tot.currency), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �������ʽ�������ϸ��������ܣ�
 */
int ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_detail(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_RRS_CLEAR_DETAIL sdb_icps_rrs_clear_detail;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_RRS_CLEAR_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_rrs_clear_detail, 0x00, sizeof(sdb_icps_rrs_clear_detail));
            pstrcopy(sdb_icps_rrs_clear_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_rrs_clear_detail.busi_date)); /*ҵ������*/
            sdb_icps_rrs_clear_detail.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_rrs_clear_detail.data_dt, '\001', "��������");

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_rrs_clear_detail.data_dt           , '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_rrs_clear_detail.acct_no           , '\001', "�������ʺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_rrs_clear_detail.currency          , '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_rrs_clear_detail.bank_group_code   , '\001', "���ű��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_rrs_clear_detail.data_type         , '\001', "��������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_rrs_clear_detail.amount            , '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_rrs_clear_detail.ds                , '\001', "���ڷ���");

            /*������˱�־*/
            pstrcopy(sdb_icps_rrs_clear_detail.is_check_flag, "1", sizeof(sdb_icps_rrs_clear_detail.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_RRS_CLEAR_DETAIL", SD_ICPS_WB_RRS_CLEAR_DETAIL, NUMELE(SD_ICPS_WB_RRS_CLEAR_DETAIL),
                    &sdb_icps_rrs_clear_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("��[%d]����¼����ʧ��['%s','%s','%s']", rcdCnt, sdb_icps_rrs_clear_detail.data_dt,
                                sdb_icps_rrs_clear_detail.acct_no, sdb_icps_rrs_clear_detail.currency), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ���������������ʽ���ϸ��������ܣ�
 */
int ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_other_detail(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_RSS_OTHER_DETAIL sdb_icps_rss_other_detail;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_RSS_OTHER_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_rss_other_detail, 0x00, sizeof(sdb_icps_rss_other_detail));
            pstrcopy(sdb_icps_rss_other_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_rss_other_detail.busi_date)); /*ҵ������*/
            sdb_icps_rss_other_detail.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_rss_other_detail.data_dt, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_rss_other_detail.acct_no, '\001', "�������˺�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_rss_other_detail.currency, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_rss_other_detail.bank_group_code, '\001', "���ű��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_rss_other_detail.data_type, '\001', "��������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_rss_other_detail.ser_no, '\001', "��ϸ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_rss_other_detail.amount, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_rss_other_detail.memo, '\001', "��ע");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_rss_other_detail.ds, '\001', "���ڷ���");

            /*������˱�־*/
            pstrcopy(sdb_icps_rss_other_detail.is_check_flag, "1", sizeof(sdb_icps_rss_other_detail.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_RSS_OTHER_DETAIL", SD_ICPS_WB_RSS_OTHER_DETAIL, NUMELE(SD_ICPS_WB_RSS_OTHER_DETAIL),
                    &sdb_icps_rss_other_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("��[%d]����¼����ʧ��['%s','%s','%s']", rcdCnt, sdb_icps_rss_other_detail.data_dt,
                                sdb_icps_rss_other_detail.acct_no, sdb_icps_rss_other_detail.currency), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ���ռ�¼��
 */
int ffunc_parse_wbank_file_to_db_tm_coll_rec(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_COLL_REC sdb_icps_tm_coll_rec;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_COLL_REC WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_coll_rec, 0x00, sizeof(sdb_icps_tm_coll_rec));
            pstrcopy(sdb_icps_tm_coll_rec.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_coll_rec.busi_date)); /*ҵ������*/
            sdb_icps_tm_coll_rec.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_coll_rec.org, '\001', "������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_coll_rec.coll_rec_id, '\001', "�߼���ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_coll_rec.case_no, '\001', "�������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_coll_rec.cust_id, '\001', "�ͻ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_coll_rec.coll_rec_type, '\001', "�߼�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_coll_rec.action_code, '\001', "���ն���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_coll_rec.user_field1, '\001', "�����ֶ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_coll_rec.user_field2, '\001', "�����ֶ�2");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_coll_rec.coll_time, '\001', "����ʱ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_coll_rec.coll_conseq, '\001', "���ս��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_coll_rec.prom_amt, '\001', "��ŵ���");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_coll_rec.prom_date, '\001', "��ŵ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_coll_rec.user_field3, '\001', "�����ֶ�3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_coll_rec.user_field4, '\001', "�����ֶ�4");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_coll_rec.user_field5, '\001', "�����ֶ�5");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_coll_rec.user_field6, '\001', "�����ֶ�6");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_coll_rec.user_field7, '\001', "�����ֶ�7");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_tm_coll_rec.user_field8, '\001', "�����ֶ�8");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_tm_coll_rec.user_field9, '\001', "�����ֶ�9");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_tm_coll_rec.user_field10, '\001', "�����ֶ�10");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_tm_coll_rec.user_field11, '\001', "�����ֶ�11");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_tm_coll_rec.user_field12, '\001', "�����ֶ�12");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_tm_coll_rec.user_field13, '\001', "�����ֶ�13");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_tm_coll_rec.user_field14, '\001', "�����ֶ�14");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_tm_coll_rec.user_field15, '\001', "�����ֶ�15");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_tm_coll_rec.user_field16, '\001', "�����ֶ�16");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_tm_coll_rec.user_field17, '\001', "�����ֶ�17");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 28, sdb_icps_tm_coll_rec.user_field18, '\001', "�����ֶ�18");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 29, sdb_icps_tm_coll_rec.user_field19, '\001', "�����ֶ�19");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 30, sdb_icps_tm_coll_rec.user_field20, '\001', "�����ֶ�20");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_coll_rec.is_check_flag, "1", sizeof(sdb_icps_tm_coll_rec.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_COLL_REC", SD_ICPS_WB_TM_COLL_REC, NUMELE(SD_ICPS_WB_TM_COLL_REC),
                    &sdb_icps_tm_coll_rec, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_tm_coll_rec.coll_rec_id, sdb_icps_tm_coll_rec.case_no),
                        "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �����˰�ӹ���
 */
int ffunc_parse_wbank_file_to_db_tm_loan_vms(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_LOAN_VMS sdb_icps_tm_loan_vms;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_LOAN_VMS WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_loan_vms, 0x00, sizeof(sdb_icps_tm_loan_vms));
            pstrcopy(sdb_icps_tm_loan_vms.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_loan_vms.busi_date)); /*ҵ������*/
            sdb_icps_tm_loan_vms.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_loan_vms.id, '\001', "��˰���ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_loan_vms.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_loan_vms.card_no, '\001', "���ʿ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_loan_vms.ref_nbr, '\001', "���ײο���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_loan_vms.bank_group_id, '\001', "���ű��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_loan_vms.bank_no, '\001', "���б��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_loan_vms.product_cd, '\001', "��Ʒ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_loan_vms.biz_tax_interes, '\001', "Ӫҵ˰�µ�Ӧ�ƺ�Ӧ��Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_loan_vms.vat_int_bal, '\001', "90���ڵ�Ӧ��˰Ϣ���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_loan_vms.norevoke_vat_int_bal, '\001', "������㷨��Ӧ��˰Ϣ����90����+90���⻹��ǲ��֣�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_loan_vms.vat_tax, '\001', "������ֵ˰");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_loan_vms.loan_int_term, '\001', "����������");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_loan_vms.last_modified_time, '\001', "�ϴ��޸�ʱ��");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_loan_vms.paid_out_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_loan_vms.age_no, '\001', "����");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_loan_vms.batch_date, '\001', "��������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_loan_vms.lpa_version, '\001', "�ֹ����汾��");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_loan_vms.is_check_flag, "1", sizeof(sdb_icps_tm_loan_vms.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_LOAN_VMS", SD_ICPS_WB_TM_LOAN_VMS, NUMELE(SD_ICPS_WB_TM_LOAN_VMS),
                    &sdb_icps_tm_loan_vms, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s','%s']", rcdCnt, sdb_icps_tm_loan_vms.id, sdb_icps_tm_loan_vms.ref_nbr),
                        "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ��Ϣȯ��Ϣ��
 */
int ffunc_parse_wbank_file_to_db_tm_free_coupons_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_TM_FREE_COUPONS_INFO sdb_icps_tm_free_coupons_info;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_FREE_COUPONS_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_free_coupons_info, 0x00, sizeof(sdb_icps_tm_free_coupons_info));
            pstrcopy(sdb_icps_tm_free_coupons_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_tm_free_coupons_info.busi_date)); /*ҵ������*/
            sdb_icps_tm_free_coupons_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_free_coupons_info.org, '\001', "������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_free_coupons_info.list_no, '\001', "�ʸ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_free_coupons_info.act_no, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_free_coupons_info.equity_no, '\001', "Ȩ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_free_coupons_info.equity_type, '\001', "Ȩ������");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_free_coupons_info.equity_value, '\001', "Ȩ��ֵ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_free_coupons_info.loan_receipt_nbr, '\001', "��ݺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_free_coupons_info.card_no, '\001', "���ʿ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_free_coupons_info.ref_nbr, '\001', "���ײο�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_free_coupons_info.bank_group_id, '\001', "���ű��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_free_coupons_info.bank_no, '\001', "���б��");

            /*������˱�־*/
            pstrcopy(sdb_icps_tm_free_coupons_info.is_check_flag, "1", sizeof(sdb_icps_tm_free_coupons_info.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_FREE_COUPONS_INFO", SD_ICPS_WB_TM_FREE_COUPONS_INFO,
                    NUMELE(SD_ICPS_WB_TM_FREE_COUPONS_INFO), &sdb_icps_tm_free_coupons_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_tm_free_coupons_info.list_no), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ��Ϣȯ��Ϣ��
 */
int ffunc_parse_wbank_file_to_db_ds_split_diff(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_DS_SPLIT_DIFF sdb_icps_ds_split_diff;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_SPLIT_DIFF WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_split_diff, 0x00, sizeof(sdb_icps_ds_split_diff));
            pstrcopy(sdb_icps_ds_split_diff.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_ds_split_diff.busi_date)); /*ҵ������*/
            sdb_icps_ds_split_diff.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_split_diff.partition_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_split_diff.error_type, '\001', "�쳣����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_split_diff.bank_group_id, '\001', "���ű��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_split_diff.bank_no, '\001', "���б��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_split_diff.busi_serial, '\001', "ҵ����ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_split_diff.trans_type, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_split_diff.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_split_diff.logical_card_no, '\001', "�߼�����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_split_diff.bf_amt, '\001', "������������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_split_diff.account_amt, '\001', "CNC���˽��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_split_diff.error_amt, '\001', "Ӧ�������");

            /*������˱�־*/
            pstrcopy(sdb_icps_ds_split_diff.is_check_flag, "1", sizeof(sdb_icps_ds_split_diff.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_SPLIT_DIFF", SD_ICPS_WB_DS_SPLIT_DIFF, NUMELE(SD_ICPS_WB_DS_SPLIT_DIFF),
                    &sdb_icps_ds_split_diff, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_ds_split_diff.busi_serial), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ί����ս�ݼ����÷�̯��ϸ��
 */
int ffunc_parse_wbank_file_to_db_ds_dca_commission(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_DS_DCA_COMMISSION sdb_icps_ds_dca_commission;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_DCA_COMMISSION WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_dca_commission, 0x00, sizeof(sdb_icps_ds_dca_commission));
            pstrcopy(sdb_icps_ds_dca_commission.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_ds_dca_commission.busi_date)); /*ҵ������*/
            sdb_icps_ds_dca_commission.file_order = rcdCnt;

            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_dca_commission.out_amt, '\001', "ί����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_dca_commission.out_prin, '\001', "ί�Ȿ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_dca_commission.out_interest, '\001', "ί����Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_dca_commission.out_penatly, '\001', "ί�ⷣϢ");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_dca_commission.out_due_days, '\001', "ί����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_dca_commission.out_age_cd, '\001', "ί������ʱ��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_dca_commission.repay_amt, '\001', "������");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_dca_commission.commision_ratio, '\001', "ί�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_dca_commission.bank_group_id, '\001', "���ű��");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_dca_commission.bank_proportion, '\001', "���ű���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_dca_commission.out_expense, '\001', "ί�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_ds_dca_commission.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_ds_dca_commission.logical_card_no, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_ds_dca_commission.cust_id, '\001', "�ͻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_ds_dca_commission.acct_no, '\001', "�˻���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_ds_dca_commission.loan_receipt_nbr, '\001', "��ݺ�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_ds_dca_commission.bn, '\001', "���к�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_ds_dca_commission.partition_date, '\001', "��������");

            /*������˱�־*/
            pstrcopy(sdb_icps_ds_dca_commission.is_check_flag, "1", sizeof(sdb_icps_ds_dca_commission.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_DCA_COMMISSION", SD_ICPS_WB_DS_DCA_COMMISSION, NUMELE(SD_ICPS_WB_DS_DCA_COMMISSION),
                    &sdb_icps_ds_dca_commission, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��", rcdCnt), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ������������Ѻ�����ݲ����
 */
int ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_diff(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_DS_DIFF_LIST sdb_icps_ds_diff_list;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_DIFF_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_diff_list, 0x00, sizeof(sdb_icps_ds_diff_list));
            pstrcopy(sdb_icps_ds_diff_list.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_ds_diff_list.busi_date)); /*ҵ������*/
            sdb_icps_ds_diff_list.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_diff_list.id_num, '\001', "֤����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_diff_list.id_type, '\001', "֤������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_diff_list.cust_id, '\001', "�ͻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_diff_list.product_code, '\001', "��Ʒ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_diff_list.acct_no, '\001', "�˺�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_diff_list.acct_type, '\001', "�˻�����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_diff_list.logical_card_no, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_diff_list.ref_nbr, '\001', "�ο���");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_diff_list.loan_init_prin, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_diff_list.bank_group_id, '\001', "���ź�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_diff_list.writeoff_proc_status, '\001', "����״̬");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_ds_diff_list.writeoff_proc_desc, '\001', "δ����ԭ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_ds_diff_list.product_attr, '\001', "��Ʒ����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_ds_diff_list.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_ds_diff_list.writeoff_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_ds_diff_list.bank_no, '\001', "���к�");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_ds_diff_list.bank_proportion, '\001', "���ű���");

            /*������˱�־*/
            pstrcopy(sdb_icps_ds_diff_list.is_check_flag, "1", sizeof(sdb_icps_ds_diff_list.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_DIFF_LIST", SD_ICPS_WB_DS_DIFF_LIST, NUMELE(SD_ICPS_WB_DS_DIFF_LIST),
                    &sdb_icps_ds_diff_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_ds_diff_list.cust_id), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * �Ѻ�������嵥��
 */
int ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_success(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_DS_SUCC_LIST sdb_icps_ds_succ_list;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_SUCC_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_succ_list, 0x00, sizeof(sdb_icps_ds_succ_list));
            pstrcopy(sdb_icps_ds_succ_list.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_ds_succ_list.busi_date)); /*ҵ������*/
            sdb_icps_ds_succ_list.file_order = rcdCnt;

            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_succ_list.writeoff_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_succ_list.name, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_succ_list.cust_id, '\001', "�ͻ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_succ_list.bank_no, '\001', "���к�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_succ_list.bank_group_id, '\001', "���ź�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_succ_list.product_cd, '\001', "��Ʒ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_succ_list.logical_card_no, '\001', "����");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_succ_list.ref_nbr, '\001', "�ο���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_succ_list.writeoff_proc_status, '\001', "����״̬");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_succ_list.loan_init_prin, '\001', "����");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_succ_list.loan_intr_penalty, '\001', "��Ϣ��Ϣ");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_ds_succ_list.bank_proportion, '\001', "���ű���");

            /*������˱�־*/
            pstrcopy(sdb_icps_ds_succ_list.is_check_flag, "1", sizeof(sdb_icps_ds_succ_list.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_SUCC_LIST", SD_ICPS_WB_DS_SUCC_LIST, NUMELE(SD_ICPS_WB_DS_SUCC_LIST),
                    &sdb_icps_ds_succ_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_ds_succ_list.cust_id), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * ���������ˮ��
 */
int ffunc_parse_wbank_file_to_db_report_ds_approval_flow(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*��ϸ��¼����*/
    int transcCnt = 0; /*�������*/
    char sFileLineUTF8[1024], sFileLineGBK[1024], sFileLineList[50];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    FILE *fp_list = NULL;
    char list_file_name[255];

    FILE *fp_check = NULL;
    char check_file_name[255];

    ICPS_WB_DS_APPROVAL_FLOW sdb_icps_wb_ds_approval_flow;

    memset(list_file_name, 0x00, sizeof(list_file_name));
    snprintf(list_file_name, sizeof(list_file_name), "%s/.filelist", st_para_chkfileins.file_path);
    if ((fp_list = fopen(list_file_name, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_APPROVAL_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("ɾ��ԭʼ���˼�¼[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*����*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*����*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_ds_approval_flow, 0x00, sizeof(sdb_icps_wb_ds_approval_flow));
            pstrcopy(sdb_icps_wb_ds_approval_flow.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_ds_approval_flow.busi_date)); /*ҵ������*/
            sdb_icps_wb_ds_approval_flow.file_order = rcdCnt;

            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_ds_approval_flow.partition_date, '\001', "��������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_ds_approval_flow.busi_no, '\001', "��ˮ��");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_ds_approval_flow.bank_no, '\001', "���к�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_ds_approval_flow.final_ret, '\001', "�����������  ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_ds_approval_flow.ours_approval_ret, '\001', "������������� ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_ds_approval_flow.code_block, '\001', "�ܾ���");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_ds_approval_flow.is_first, '\001', "�Ƿ��׽�");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_ds_approval_flow.outer_ret, '\001', "�����л����������");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_ds_approval_flow.psz_ret, '\001', "Psz���������");

            /*������˱�־*/
            pstrcopy(sdb_icps_wb_ds_approval_flow.is_check_flag, "1", sizeof(sdb_icps_wb_ds_approval_flow.is_check_flag));
            /*�������ݿ�*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_APPROVAL_FLOW", SD_ICPS_WB_DS_APPROVAL_FLOW, NUMELE(SD_ICPS_WB_DS_APPROVAL_FLOW),
                    &sdb_icps_wb_ds_approval_flow, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("��[%d]����¼����ʧ��['%s']", rcdCnt, sdb_icps_wb_ds_approval_flow.busi_no), "ERROR");
                DCIRollback();
                return iRet;
            }

            if (transcCnt >= 1000)
            {
                if (DCICommit() != MID_SYS_SUCC)
                {
                    DCIRollback();
                    return -1;
                }
                DCIBegin();
                transcCnt = 0;
            }
        }

        if (DCICommit() != MID_SYS_SUCC)
        {
            DCIRollback();
            return -1;
        }

    }

    LOG(LM_STD, Fmtmsg("�����¼��[%d]", rcdCnt), "INFO")

    return 0;
}

int ffunc_parse_wbank_file_to_db(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int fileins_status = -1;

    if (0 == strcmp(st_para_chkfileins.file_type, "tm_account"))
    {
        /*�˻���Ϣ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_account(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_bank_cost"))
    {
        /*�����ļ�����ˮ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_auth_bank_cost(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_card"))
    {
        /*�߼�����*/
        iRet = ffunc_parse_wbank_file_to_db_tm_card(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_gl_bal"))
    {
        /*���˻�ƿ�Ŀ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_gl_bal(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_plan"))
    {
        /*���üƻ���*/
        iRet = ffunc_parse_wbank_file_to_db_tm_plan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_app_main"))
    {
        /*��������*/
        iRet = ffunc_parse_wbank_file_to_db_tm_app_main(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_app_prim_applicant_info"))
    {
        /*������������Ϣ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_app_prim_applicant_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_customer"))
    {
        /*�ͻ���Ϣ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_customer(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tt_txn_post"))
    {
        /*�������˽��ױ�*/
        iRet = ffunc_parse_wbank_file_to_db_tt_txn_post(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_txn_reject"))
    {
        /*���˽�����ʷ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_txn_reject(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan"))
    {
        /*������Ϣ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_schedule"))
    {
        /*��������*/
        iRet = ffunc_parse_wbank_file_to_db_tm_schedule(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_accounting_flow"))
    {
        /*��Ʒ�¼�ձ���*/
        iRet = ffunc_parse_wbank_file_to_db_ds_accounting_flow(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_cust_limit_o"))
    {
        /*�Զ�������Ϣ��-��Ȩ*/
        iRet = ffunc_parse_wbank_file_to_db_tm_cust_limit_o(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_hst"))
    {
        /*��Ȩ������ʷ*/
        iRet = ffunc_parse_wbank_file_to_db_tm_auth_hst(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_im_info"))
    {
        /*�ͻ���ʱͨѶ��Ϣ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_im_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_receipt_list"))
    {
        /*�������嵥��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan_receipt_list(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_receipt_list_hst"))
    {
        /*�������嵥����ʷ*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan_receipt_list_hst(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_psb_personal_info"))
    {
        /*�����Ϣ*/
        iRet = ffunc_parse_wbank_file_to_db_tm_psb_personal_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_tot"))
    {
        /*�������ʽ��������*/
        iRet = ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_tot(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_detail"))
    {
        /*�������ʽ�������ϸ��������ܣ�*/
        iRet = ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_other_detail"))
    {
        /*���������������ʽ���ϸ��������ܣ�*/
        iRet = ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_other_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_coll_rec"))
    {
        /*���ռ�¼��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_coll_rec(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_vms"))
    {
        /*�����˰�ӹ���*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan_vms(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_free_coupons_info"))
    {
        /*��Ϣȯ��Ϣ��*/
        iRet = ffunc_parse_wbank_file_to_db_tm_free_coupons_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_split_diff"))
    {
        /*����β�������*/
        iRet = ffunc_parse_wbank_file_to_db_ds_split_diff(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_dca_commission"))
    {
        /*ί����ս�ݼ����÷�̯��ϸ��*/
        iRet = ffunc_parse_wbank_file_to_db_ds_dca_commission(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_loan_writeoff_list_diff"))
    {
        /*������������Ѻ�����ݲ����*/
        iRet = ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_diff(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_loan_writeoff_list_success"))
    {
        /*�Ѻ�������嵥��*/
        iRet = ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_success(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "report_ds_approval_flow"))
    {
        /*���������ˮ��*/
        iRet = ffunc_parse_wbank_file_to_db_report_ds_approval_flow(lXmlhandle, st_para_chkfileins);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ļ����ʹ���"), "ERROR");
        return -2;
    }

    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("Ŀǰ�ļ����״̬[%d]", fileins_status), "INFO")

    if (9 == fileins_status) /*��ʼ*/
    {
        if (0 == iRet) /*�ɹ�*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*�ɹ�*/
        else if (-404 == iRet) /*���ļ�*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "9") /*��ʼ*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "2") /*ʧ��*/
    }
    else if (0 == fileins_status) /*�ɹ�*/
    {
        if (0 == iRet) /*�ɹ�*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*�ɹ�*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*���ֳɹ�*/
    }
    else if (2 == fileins_status) /*ʧ��*/
    {
        if (0 == iRet || -404 == iRet)
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*���ֳɹ�*/
    }
    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("���ļ�����״̬[%d]", fileins_status), "INFO")
    iRet = ffunc_upd_file_info(st_para_chkfileins.busi_date, st_para_chkfileins.busi_no, st_para_chkfileins.file_type, iRet);

    return iRet;
}

int ffunc_init_wbank_file_info(HXMLTREE lXmlhandle, PARA_FILEINFOINIT st_para_fileinfoinit)
{
    int iRet;

    /*�˻���Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_account");
    /*�����ļ�����ˮ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_bank_cost");
    /*�߼�����*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_card");
    /*���˻�ƿ�Ŀ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_gl_bal");
    /*���üƻ���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_plan");
    /*��������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_main");
    /*������������Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_prim_applicant_info");
    /*�ͻ���Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_customer");
    /*�������˽��ױ�*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tt_txn_post");
    /*���˽�����ʷ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_txn_reject");
    /*������Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan");
    /*��������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_schedule");
    /*��Ʒ�¼�ձ���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_accounting_flow");
    /*�Զ�������Ϣ��-��Ȩ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_cust_limit_o");
    /*��Ȩ������ʷ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_hst");
    /*�ͻ���ʱͨѶ��Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_im_info");
    /*�������嵥��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_receipt_list");
    /*�������嵥����ʷ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_receipt_list_hst");
    /*�����Ϣ*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_psb_personal_info");
    /*�������ʽ��������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_tot");
    /*�������ʽ�������ϸ��������ܣ�*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_detail");
    /*���������������ʽ���ϸ���������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_other_detail");
    /*���ռ�¼��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_coll_rec");
    /*�����˰�ӹ���*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_vms");
    /*��Ϣȯ��Ϣ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_free_coupons_info");
    /*����β�������*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_split_diff");
    /*ί����ս�ݼ����÷�̯��ϸ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_dca_commission");
    /*������������Ѻ�����ݲ����*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_loan_writeoff_list_diff");
    /*�Ѻ�������嵥��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_loan_writeoff_list_success");
    /*���������ˮ��*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "report_ds_approval_flow");
    return 0;
}
