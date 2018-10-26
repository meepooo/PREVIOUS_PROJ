#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>

/**
 * 账户信息表
 */
int ffunc_parse_wbank_file_to_db_tm_account(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_ACCOUNT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_account, 0x00, sizeof(sdb_icps_wb_tm_account));
            pstrcopy(sdb_icps_wb_tm_account.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_account.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_account.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_account.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_account.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_account.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_account.cust_id, '\001', "客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_account.cust_limit_id, '\001', "客户额度ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_account.product_code, '\001', "产品代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_account.default_logical_card_no, '\001', "默认逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_account.currency, '\001', "币种");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_account.credit_limit, '\001', "授信额度");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_account.temp_limit, '\001', "临时额度");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_account.temp_limit_begin_date, '\001', "临时额度开始日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_account.temp_limit_end_date, '\001', "临时额度结束日期");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_account.user_field1, '\001', "备用字段1");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_account.user_field2, '\001', "备用字段2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_account.user_field3, '\001', "备用字段3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_account.curr_balance, '\001', "当前余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_account.user_field4, '\001', "备用字段4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_account.principal_bal, '\001', "本金余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_account.user_field5, '\001', "备用字段5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_account.user_field6, '\001', "备用字段6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_account.begin_bal, '\001', "上一到期日余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_account.pmt_due_day_bal, '\001', "到期还款日余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_account.user_field7, '\001', "备用字段7");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_account.user_field8, '\001', "备用字段8");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_account.user_field9, '\001', "备用字段9");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_account.user_field10, '\001', "备用字段10");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_account.user_field11, '\001', "备用字段11");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_account.user_field12, '\001', "备用字段12");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_account.user_field13, '\001', "备用字段13");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_account.user_field14, '\001', "备用字段14");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_account.user_field15, '\001', "备用字段15");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_account.user_field16, '\001', "备用字段16");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_account.user_field17, '\001', "备用字段17");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_account.user_field18, '\001', "备用字段18");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_account.name, '\001', "姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_account.gender, '\001', "性别");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_account.user_field19, '\001', "备用字段19");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_account.mobile_no, '\001', "移动电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_account.user_field20, '\001', "备用字段20");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_account.billint_cycle, '\001', "还款日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_account.user_field21, '\001', "备用字段21");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_account.user_field22, '\001', "备用字段22");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_account.user_field23, '\001', "备用字段23");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_account.user_field24, '\001', "备用字段24");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_account.user_field25, '\001', "备用字段25");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_account.user_field26, '\001', "备用字段26");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_account.user_field27, '\001', "备用字段27");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_account.user_field28, '\001', "备用字段28");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_account.user_field29, '\001', "备用字段29");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_account.user_field30, '\001', "备用字段30");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_account.user_field31, '\001', "备用字段31");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_account.AGE_CD, '\001', "拖欠月数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_account.user_field32, '\001', "备用字段32");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_account.UNMATCH_DB, '\001', "未入账借记金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_account.user_field33, '\001', "备用字段33");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_account.unmatch_cr, '\001', "未入账贷记金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_account.dd_ind, '\001', "约定还款类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_account.dd_bank_name, '\001', "约定还款银行名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_account.dd_bank_branch, '\001', "约定还款开户行号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_account.dd_bank_acct_no, '\001', "约定还款扣款账号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_account.dd_bank_acct_name, '\001', "约定还款扣款账户姓名");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_account.last_dd_amt, '\001', "上期约定还款金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_account.last_dd_date, '\001', "上期约定还款日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_account.user_field34, '\001', "备用字段34");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_account.last_pmt_amt, '\001', "上期还款金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_account.last_pmt_date, '\001', "上个还款日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_account.last_stmt_date, '\001', "上个到期还款日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_account.last_pmt_due_date, '\001', "上个到期还款日期1");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_account.last_agint_date, '\001', "上课逾期月数提升日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_account.collect_date, '\001', "入催日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_account.collect_out_date, '\001', "出催收队列日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_account.next_stmt_date, '\001', "下个到期还款日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_account.pmt_due_date, '\001', "到期还款日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_account.dd_date, '\001', "约定还款日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_account.grace_date, '\001', "宽限日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_account.user_field35, '\001', "备用字段35");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wb_tm_account.closed_date, '\001', "最终销户日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 78, sdb_icps_wb_tm_account.first_stmt_date, '\001', "首个到期还款日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 79, sdb_icps_wb_tm_account.cancel_date, '\001', "销户日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wb_tm_account.charge_off_date, '\001', "转呆账日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 81, sdb_icps_wb_tm_account.user_field36, '\001', "备用字段36");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wb_tm_account.usesr_field37, '\001', "备用字段37");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 83, sdb_icps_wb_tm_account.usesr_field38, '\001', "备用字段38");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wb_tm_account.usesr_field39, '\001', "备用字段39");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wb_tm_account.usesr_field40, '\001', "备用字段40");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wb_tm_account.usesr_field41, '\001', "备用字段41");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wb_tm_account.usesr_field42, '\001', "备用字段42");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wb_tm_account.usesr_field43, '\001', "备用字段43");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wb_tm_account.usesr_field44, '\001', "备用字段44");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wb_tm_account.usesr_field45, '\001', "备用字段45");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wb_tm_account.usesr_field46, '\001', "备用字段46");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wb_tm_account.usesr_field47, '\001', "备用字段47");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_wb_tm_account.usesr_field48, '\001', "备用字段48");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 94, sdb_icps_wb_tm_account.usesr_field49, '\001', "备用字段49");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 95, sdb_icps_wb_tm_account.ctd_retail_amt, '\001', "当期消费金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 96, sdb_icps_wb_tm_account.ctd_retail_cnt, '\001', "当期消费笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 97, sdb_icps_wb_tm_account.ctd_payment_amt, '\001', "当期还款金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 98, sdb_icps_wb_tm_account.ctd_payment_cnt, '\001', "当期还款笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 99, sdb_icps_wb_tm_account.ctd_db_adj_amt, '\001', "当期借记调整金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 100, sdb_icps_wb_tm_account.ctd_db_adj_cnt, '\001', "当期借记调整笔数");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 101, sdb_icps_wb_tm_account.ctd_cr_adj_cnt, '\001', "当期贷记调整笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 102, sdb_icps_wb_tm_account.ctd_cr_adj_amt, '\001', "当期贷记调整金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 103, sdb_icps_wb_tm_account.ctd_fee_amt, '\001', "当期费用金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 104, sdb_icps_wb_tm_account.ctd_fee_cnt, '\001', "当期费用笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 105, sdb_icps_wb_tm_account.ctd_interest_amt, '\001', "当期利息金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 106, sdb_icps_wb_tm_account.ctd_interest_cnt, '\001', "当期利息笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 107, sdb_icps_wb_tm_account.user_field50, '\001', "备用字段50");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 108, sdb_icps_wb_tm_account.user_field51, '\001', "备用字段51");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 109, sdb_icps_wb_tm_account.user_field52, '\001', "备用字段52");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 110, sdb_icps_wb_tm_account.mtd_retail_amt, '\001', "本月消费金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 111, sdb_icps_wb_tm_account.mtd_retail_cnt, '\001', "本月消费笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 112, sdb_icps_wb_tm_account.user_field53, '\001', "备用字段53");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 113, sdb_icps_wb_tm_account.user_field54, '\001', "备用字段54");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_wb_tm_account.user_field55, '\001', "备用字段55");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 115, sdb_icps_wb_tm_account.user_field56, '\001', "备用字段56");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 116, sdb_icps_wb_tm_account.ytd_retail_amt, '\001', "本年消费金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 117, sdb_icps_wb_tm_account.ytd_retail_cnt, '\001', "本年消费笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 118, sdb_icps_wb_tm_account.user_field57, '\001', "备用字段57");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 119, sdb_icps_wb_tm_account.user_field58, '\001', "备用字段58");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 120, sdb_icps_wb_tm_account.user_field59, '\001', "备用字段59");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 121, sdb_icps_wb_tm_account.user_field60, '\001', "备用字段60");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 122, sdb_icps_wb_tm_account.user_field61, '\001', "备用字段61");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 123, sdb_icps_wb_tm_account.user_field62, '\001', "备用字段62");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 124, sdb_icps_wb_tm_account.user_field63, '\001', "备用字段63");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 125, sdb_icps_wb_tm_account.user_field64, '\001', "备用字段64");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 126, sdb_icps_wb_tm_account.user_field65, '\001', "备用字段65");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 127, sdb_icps_wb_tm_account.user_field66, '\001', "备用字段66");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 128, sdb_icps_wb_tm_account.user_field67, '\001', "备用字段67");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 129, sdb_icps_wb_tm_account.user_field68, '\001', "备用字段68");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 130, sdb_icps_wb_tm_account.user_field69, '\001', "备用字段69");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 131, sdb_icps_wb_tm_account.user_field70, '\001', "备用字段70");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 132, sdb_icps_wb_tm_account.user_field71, '\001', "备用字段71");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 133, sdb_icps_wb_tm_account.user_field72, '\001', "备用字段72");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 134, sdb_icps_wb_tm_account.user_field73, '\001', "备用字段73");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 135, sdb_icps_wb_tm_account.user_field74, '\001', "备用字段74");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 136, sdb_icps_wb_tm_account.user_field75, '\001', "备用字段75");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 137, sdb_icps_wb_tm_account.user_field76, '\001', "备用字段76");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 138, sdb_icps_wb_tm_account.user_field77, '\001', "备用字段77");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 139, sdb_icps_wb_tm_account.user_field78, '\001', "备用字段78");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 140, sdb_icps_wb_tm_account.user_field79, '\001', "备用字段79");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 141, sdb_icps_wb_tm_account.user_field80, '\001', "备用字段80");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 142, sdb_icps_wb_tm_account.user_field81, '\001', "备用字段81");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 143, sdb_icps_wb_tm_account.waive_svcfee_ind, '\001', "是否免除服务费");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 144, sdb_icps_wb_tm_account.user_field82, '\001', "备用字段82");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 145, sdb_icps_wb_tm_account.user_field83, '\001', "备用字段83");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 146, sdb_icps_wb_tm_account.user_field84, '\001', "备用字段84");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 147, sdb_icps_wb_tm_account.user_field85, '\001', "备用字段85");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 148, sdb_icps_wb_tm_account.user_field86, '\001', "备用字段86");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 149, sdb_icps_wb_tm_account.user_field87, '\001', "备用字段87");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 150, sdb_icps_wb_tm_account.user_field88, '\001', "备用字段88");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 151, sdb_icps_wb_tm_account.user_date2, '\001', "上期调额日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 152, sdb_icps_wb_tm_account.user_field89, '\001', "备用字段89");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 153, sdb_icps_wb_tm_account.user_field90, '\001', "备用字段90");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 154, sdb_icps_wb_tm_account.user_field91, '\001', "备用字段91");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 155, sdb_icps_wb_tm_account.user_field92, '\001', "备用字段92");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 156, sdb_icps_wb_tm_account.user_field93, '\001', "备用字段93");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 157, sdb_icps_wb_tm_account.user_field94, '\001', "备用字段94");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 158, sdb_icps_wb_tm_account.user_field95, '\001', "备用字段95");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 159, sdb_icps_wb_tm_account.user_field96, '\001', "备用字段96");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 160, sdb_icps_wb_tm_account.user_field97, '\001', "备用字段97");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 161, sdb_icps_wb_tm_account.user_field98, '\001', "备用字段98");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 162, sdb_icps_wb_tm_account.user_field99, '\001', "备用字段99");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 163, sdb_icps_wb_tm_account.user_field100, '\001', "备用字段100");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 164, sdb_icps_wb_tm_account.user_field101, '\001', "备用字段101");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 165, sdb_icps_wb_tm_account.user_field102, '\001', "备用字段102");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 166, sdb_icps_wb_tm_account.user_field103, '\001', "备用字段103");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 167, sdb_icps_wb_tm_account.user_field104, '\001', "备用字段104");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 168, sdb_icps_wb_tm_account.user_field105, '\001', "备用字段105");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 169, sdb_icps_wb_tm_account.user_field106, '\001', "备用字段106");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 170, sdb_icps_wb_tm_account.user_field107, '\001', "备用字段107");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 171, sdb_icps_wb_tm_account.user_field108, '\001', "备用字段108");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 172, sdb_icps_wb_tm_account.user_field109, '\001', "备用字段109");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 173, sdb_icps_wb_tm_account.user_field110, '\001', "备用字段110");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 174, sdb_icps_wb_tm_account.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 175, sdb_icps_wb_tm_account.mtd_payment_amt, '\001', "当月还款金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 176, sdb_icps_wb_tm_account.mtd_payment_cnt, '\001', "当月还款笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 177, sdb_icps_wb_tm_account.ytd_payment_amt, '\001', "当年还款金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 178, sdb_icps_wb_tm_account.ytd_payment_cnt, '\001', "当年还款笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 179, sdb_icps_wb_tm_account.ltd_payment_amt, '\001', "历史还款金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 180, sdb_icps_wb_tm_account.ltd_payment_cnt, '\001', "历史还款笔数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 181, sdb_icps_wb_tm_account.user_field111, '\001', "备用字段111");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 182, sdb_icps_wb_tm_account.user_field112, '\001', "备用字段112");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 183, sdb_icps_wb_tm_account.user_field113, '\001', "备用字段113");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 184, sdb_icps_wb_tm_account.last_post_date, '\001', "上个批量处理时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 185, sdb_icps_wb_tm_account.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 186, sdb_icps_wb_tm_account.user_field114, '\001', "备用字段114");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 187, sdb_icps_wb_tm_account.last_sync_date, '\001', "上一次入账的批量日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 188, sdb_icps_wb_tm_account.user_field115, '\001', "备用字段115");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 189, sdb_icps_wb_tm_account.user_field116, '\001', "备用字段116");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 190, sdb_icps_wb_tm_account.user_field117, '\001', "备用字段117");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 191, sdb_icps_wb_tm_account.bank_group_id, '\001', "银团编号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 192, sdb_icps_wb_tm_account.bank_proportion, '\001', "银行出资比例");


            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_account.is_check_flag, "1", sizeof(sdb_icps_wb_tm_account.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_ACCOUNT", SD_ICPS_WB_TM_ACCOUNT, NUMELE(SD_ICPS_WB_TM_ACCOUNT),
                    &sdb_icps_wb_tm_account, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_account.org), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 授权流水银团拆分表
 */
int ffunc_parse_wbank_file_to_db_tm_auth_bank_cost(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_AUTH_BANK_COST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_auth_bank_cost, 0x00, sizeof(sdb_icps_wb_tm_auth_bank_cost));
            pstrcopy(sdb_icps_wb_tm_auth_bank_cost.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_auth_bank_cost.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_auth_bank_cost.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_auth_bank_cost.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_auth_bank_cost.bank_group_id, '\001', "银团编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_auth_bank_cost.bank_no, '\001', "银行号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_auth_bank_cost.reg_type, '\001', "登记类型");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_auth_bank_cost.reg_amt, '\001', "登记金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_auth_bank_cost.reg_status, '\001', "登记状态");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_auth_bank_cost.reg_sys_id, '\001', "记账流水号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_auth_bank_cost.reg_date, '\001', "记账日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_auth_bank_cost.reg_time, '\001', "记账请求时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_auth_bank_cost.recon_code, '\001', "对账码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_auth_bank_cost.ori_sys_id, '\001', "原记账流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_auth_bank_cost.cust_id, '\001', "客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_auth_bank_cost.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_auth_bank_cost.acct_type, '\001', "账户类型");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_auth_bank_cost.retry, '\001', "尝试次数");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_auth_bank_cost.created_datetime, '\001', "创建时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_auth_bank_cost.last_modified_datetime, '\001', "时间戳");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_auth_bank_cost.user_field268, '\001', "备用字段268");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_auth_bank_cost.is_check_flag, "1", sizeof(sdb_icps_wb_tm_auth_bank_cost.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_AUTH_BANK_COST", SD_ICPS_WB_TM_AUTH_BANK_COST, NUMELE(SD_ICPS_WB_TM_AUTH_BANK_COST),
                    &sdb_icps_wb_tm_auth_bank_cost, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_auth_bank_cost.busi_serial), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 逻辑卡表
 */
int ffunc_parse_wbank_file_to_db_tm_card(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_CARD WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_card, 0x00, sizeof(sdb_icps_wb_tm_card));
            pstrcopy(sdb_icps_wb_tm_card.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_card.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_card.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_card.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_card.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_card.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_card.cust_id, '\001', "客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_card.user_field118, '\001', "备用字段118");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_card.product_cd, '\001', "产品代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_card.app_no, '\001', "申请件编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_card.user_field119, '\001', "备用字段119");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_card.user_field120, '\001', "备用字段120");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_card.bsc_logiccard_no, '\001', "逻辑卡主卡卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_card.user_field121, '\001', "备用字段121");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_card.user_field122, '\001', "备用字段122");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_card.user_field123, '\001', "备用字段123");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_card.user_field124, '\001', "备用字段124");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_card.user_field125, '\001', "备用字段125");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_card.user_field126, '\001', "备用字段126");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_card.activate_ind, '\001', "是否已激活");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_card.cancel_date, '\001', "销卡销户日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_card.latest_card_no, '\001', "最新介质卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_card.user_field127, '\001', "备用字段127");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_card.user_field128, '\001', "备用字段128");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_card.user_field129, '\001', "备用字段129");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_card.user_field130, '\001', "备用字段130");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_card.user_field131, '\001', "备用字段131");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_card.card_expire_date, '\001', "卡片有效日期");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_card.user_field132, '\001', "备用字段132");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_card.user_field133, '\001', "备用字段133");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_card.user_field134, '\001', "备用字段134");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_card.user_field135, '\001', "备用字段135");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_card.user_field136, '\001', "备用字段136");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_card.user_field137, '\001', "备用字段137");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_card.user_field138, '\001', "备用字段138");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_card.user_field139, '\001', "备用字段139");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_card.user_field140, '\001', "备用字段140");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_card.user_field141, '\001', "备用字段141");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_card.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_card.user_field142, '\001', "备用字段142");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_card.user_field143, '\001', "备用字段143");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_card.user_field144, '\001', "备用字段144");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_card.user_field145, '\001', "备用字段145");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_card.is_check_flag, "1", sizeof(sdb_icps_wb_tm_card.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_CARD", SD_ICPS_WB_TM_CARD, NUMELE(SD_ICPS_WB_TM_CARD), &sdb_icps_wb_tm_card, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_card.logical_card_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 总账会计科目表
 */
int ffunc_parse_wbank_file_to_db_tm_gl_bal(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_GL_BAL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_gl_bal, 0x00, sizeof(sdb_icps_wb_tm_gl_bal));
            pstrcopy(sdb_icps_wb_tm_gl_bal.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_gl_bal.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_gl_bal.file_order = rcdCnt;


            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_gl_bal.org  ,'\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_gl_bal.subject  ,'\001', "科目");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_gl_bal.branch_id  ,'\001', "分支行号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_gl_bal.db_bal  ,'\001', "借方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_gl_bal.cr_bal  ,'\001', "贷方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_gl_bal.db_amt  ,'\001', "借方发生额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_gl_bal.db_count  ,'\001', "借方笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_gl_bal.cr_amt  ,'\001', "贷方发生额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_gl_bal.cr_count  ,'\001', "贷方笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_gl_bal.last_db_bal ,'\001', "昨日借方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_gl_bal.last_cr_bal ,'\001', "昨日贷方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_gl_bal.last_mth_db_bal ,'\001', "上月末借方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_gl_bal.last_mth_cr_bal ,'\001', "上月末贷方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_gl_bal.last_qtr_db_bal ,'\001', "上季末借方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_gl_bal.last_qtr_cr_bal ,'\001', "上季末贷方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_gl_bal.last_yr_db_ba ,'\001', "上年末借方余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_gl_bal.last_yr_cr_ba ,'\001', "上年末贷方余额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_gl_bal.jpa_version ,'\001', "乐观锁版本号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_gl_bal.product_cd ,'\001', "产品编号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_gl_bal.bal_id ,'\001', "顺序号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_gl_bal.bank_no ,'\001', "银行代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_gl_bal.bank_group_id ,'\001', "银团代码");


            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_gl_bal.is_check_flag, "1", sizeof(sdb_icps_wb_tm_gl_bal.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_GL_BAL", SD_ICPS_WB_TM_GL_BAL, NUMELE(SD_ICPS_WB_TM_GL_BAL), &sdb_icps_wb_tm_gl_bal, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_gl_bal.subject), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 信用计划表
 */
int ffunc_parse_wbank_file_to_db_tm_plan(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_plan, 0x00, sizeof(sdb_icps_wb_tm_plan));
            pstrcopy(sdb_icps_wb_tm_plan.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_plan.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_plan.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_plan.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_plan.plan_id, '\001', "流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_plan.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_plan.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_plan.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_plan.plan_nbr, '\001', "信用计划号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_plan.plan_type, '\001', "信用计划类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_plan.product_code, '\001', "产品代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_plan.ref_nbr, '\001', "交易参考号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_plan.curr_balance, '\001', "当前余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_plan.begin_bal, '\001', "期初余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_plan.dispute_amt, '\001', "争议金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_plan.tot_due_amt, '\001', "最小还款额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_plan.plan_add_date, '\001', "纪录建立日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_plan.paid_out_date, '\001', "还清日期");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_plan.past_principal, '\001', "上期本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_plan.past_interest, '\001', "上期利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_plan.past_card_fee, '\001', "上期年费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_plan.past_ovrlmt_fee, '\001', "上期超限费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_plan.past_lpc, '\001', "上期滞纳金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_plan.past_nsf_fee, '\001', "上期资金不足费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_plan.past_txn_fee, '\001', "上期交易费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_plan.past_svc_fee, '\001', "上期服务费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_plan.past_ins, '\001', "上期保险金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_plan.past_user_fee1, '\001', "上期自定义费用1");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_plan.past_user_fee2, '\001', "上期自定义费用2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_plan.past_user_fee3, '\001', "上期自定义费用3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_plan.past_user_fee4, '\001', "上期自定义费用4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_plan.past_user_fee5, '\001', "上期自定义费用5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_plan.past_user_fee6, '\001', "上期自定义费用6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_plan.CTD_PRINCIPAL, '\001', "当前本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_plan.ctd_interest, '\001', "当期利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_plan.ctd_card_fee, '\001', "当期年费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_plan.ctd_ovrlmt_fee, '\001', "当期超限费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_plan.ctd_lpc, '\001', "当期滞纳金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_plan.ctd_nsf_fee, '\001', "当期资金不足费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_plan.ctd_svc_fee, '\001', "当期服务费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_plan.ctd_txn_fee, '\001', "当期交易费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_plan.ctd_ins, '\001', "当期保险金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_plan.ctd_user_fee1, '\001', "当期新增自定义费用1";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_plan.ctd_user_fee2, '\001', "当期新增自定义费用2";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_plan.ctd_user_fee3, '\001', "当期新增自定义费用3";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_plan.ctd_user_fee4, '\001', "当期新增自定义费用4";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_plan.ctd_user_fee5, '\001', "当期新增自定义费用5";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_plan.ctd_user_fee6, '\001', "当期新增自定义费用6";)
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_plan.ctd_amt_db, '\001', "当期借记金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_plan.ctd_amt_cr, '\001', "当期贷记金额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_plan.ctd_nbr_db, '\001', "当期借记交易笔数");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_plan.ctd_nbr_cr, '\001', "当期贷记交易笔数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_plan.nodefbnp_int_acru, '\001', "非延迟利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_plan.beg_defbnp_int_acru, '\001', "往期累积延时利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_plan.ctd_defbnp_int_acru, '\001', "当期累积延时利息");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_plan.user_field146, '\001', "备用字段146");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_plan.user_field147, '\001', "备用字段147");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_plan.user_field148, '\001', "备用字段148");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_plan.user_field149, '\001', "备用字段149");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_plan.user_field150, '\001', "备用字段150");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_plan.user_field151, '\001', "备用字段151");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_plan.user_field152, '\001', "备用字段152");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_plan.user_field153, '\001', "备用字段153");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_plan.user_field154, '\001', "备用字段154");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_plan.user_field155, '\001', "备用字段155");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_plan.user_field156, '\001', "备用字段156");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_plan.user_field157, '\001', "备用字段157");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_plan.user_field158, '\001', "备用字段158");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_plan.user_field159, '\001', "备用字段159");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_plan.user_field160, '\001', "备用字段160");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_plan.user_field161, '\001', "备用字段161");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_plan.user_field162, '\001', "备用字段162");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_plan.user_field163, '\001', "备用字段163");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_plan.user_field164, '\001', "备用字段164");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_plan.user_field165, '\001', "备用字段165");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_plan.user_field166, '\001', "备用字段166");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_plan.user_field167, '\001', "备用字段167");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_plan.user_field168, '\001', "备用字段168");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_plan.user_field169, '\001', "备用字段169");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_wb_tm_plan.user_field170, '\001', "备用字段170");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 78, sdb_icps_wb_tm_plan.user_field171, '\001', "备用字段171");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 79, sdb_icps_wb_tm_plan.user_field172, '\001', "备用字段172");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 80, sdb_icps_wb_tm_plan.user_field173, '\001', "备用字段173");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 81, sdb_icps_wb_tm_plan.user_field174, '\001', "备用字段174");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 82, sdb_icps_wb_tm_plan.user_field175, '\001', "备用字段175");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 83, sdb_icps_wb_tm_plan.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 84, sdb_icps_wb_tm_plan.past_penalty, '\001', "往期罚息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 85, sdb_icps_wb_tm_plan.ctd_penalty, '\001', "当期罚息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 86, sdb_icps_wb_tm_plan.past_compound, '\001', "往期复利");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wb_tm_plan.ctd_compound, '\001', "当期复利");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wb_tm_plan.penalty_acru, '\001', "罚息累计");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wb_tm_plan.compound_acru, '\001', "复利累计");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 90, sdb_icps_wb_tm_plan.interest_rate, '\001', "基础利率");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 91, sdb_icps_wb_tm_plan.penalty_rate, '\001', "罚息利率");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 92, sdb_icps_wb_tm_plan.compound_rate, '\001', "复利利率");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 93, sdb_icps_wb_tm_plan.use_plan_rate, '\001', "是否使用plan的利率");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 94, sdb_icps_wb_tm_plan.last_pmt_date, '\001', "上一还款日期");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 95, sdb_icps_wb_tm_plan.term, '\001', "所在贷款期数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_wb_tm_plan.calc_type, '\001', "计费类型");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 97, sdb_icps_wb_tm_plan.calc_cycle, '\001', "计费周期");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_wb_tm_plan.fee_rate, '\001', "费率");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 99, sdb_icps_wb_tm_plan.last_fee_date, '\001', "上一收费日");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 100, sdb_icps_wb_tm_plan.next_fee_date, '\001', "下一收费日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_wb_tm_plan.trans_serial, '\001', "交易流水号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 102, sdb_icps_wb_tm_plan.first_dd_date, '\001', "首次约定还款日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_wb_tm_plan.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_wb_tm_plan.sys_trans_id, '\001', "系统调用流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_wb_tm_plan.user_field176, '\001', "备用字段176");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_wb_tm_plan.sub_terminal_type, '\001', "终端类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_wb_tm_plan.sub_merch_id, '\001', "二级商户编码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_wb_tm_plan.sub_merch_name, '\001', "二级商户名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_wb_tm_plan.wares_desc, '\001', "商品信息");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 110, sdb_icps_wb_tm_plan.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 111, sdb_icps_wb_tm_plan.original_amt, '\001', "原始交易本金");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 112, sdb_icps_wb_tm_plan.interest_calc_base, '\001', "计息基数");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 113, sdb_icps_wb_tm_plan.created_datetime, '\001', "创建时间");



            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_plan.is_check_flag, "1", sizeof(sdb_icps_wb_tm_plan.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_PLAN", SD_ICPS_WB_TM_PLAN, NUMELE(SD_ICPS_WB_TM_PLAN), &sdb_icps_wb_tm_plan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_plan.plan_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 申请主表
 */
int ffunc_parse_wbank_file_to_db_tm_app_main(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_APP_MAIN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_app_main, 0x00, sizeof(sdb_icps_wb_tm_app_main));
            pstrcopy(sdb_icps_wb_tm_app_main.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_app_main.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_app_main.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_app_main.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_app_main.app_no, '\001', "申请件编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_app_main.user_field1, '\001', "备用字段");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_app_main.user_field2, '\001', "备用字段2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_app_main.user_field3, '\001', "备用字段3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_app_main.acc_lmt, '\001', "核准额度");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_app_main.product_cd, '\001', "卡产品代码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_app_main.user_field4, '\001', "备用字段4");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_app_main.user_field5, '\001', "备用字段5");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_app_main.user_field6, '\001', "备用字段6");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_app_main.user_field7, '\001', "备用字段7");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_app_main.user_field8, '\001', "备用字段8");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_app_main.user_field9, '\001', "备用字段9");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_app_main.user_field10, '\001', "备用字段10");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_app_main.user_field11, '\001', "备用字段11");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_app_main.user_field12, '\001', "备用字段12");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_app_main.user_field13, '\001', "备用字段13");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_app_main.user_field14, '\001', "备用字段14");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_app_main.user_field15, '\001', "备用字段15");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_app_main.user_field16, '\001', "备用字段16");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_app_main.user_field17, '\001', "备用字段17");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_app_main.user_field18, '\001', "备用字段18");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_app_main.user_field19, '\001', "备用字段19");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_app_main.user_field20, '\001', "备用字段20");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_app_main.user_field21, '\001', "备用字段21");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_app_main.user_field22, '\001', "备用字段22");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_app_main.user_field23, '\001', "备用字段23");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_app_main.user_field24, '\001', "备用字段24");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_app_main.user_field25, '\001', "备用字段25");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_app_main.user_field26, '\001', "备用字段26");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_app_main.user_field27, '\001', "备用字段27");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_app_main.user_field28, '\001', "备用字段28");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_app_main.user_field29, '\001', "备用字段29");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_app_main.user_field30, '\001', "备用字段30");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_app_main.user_field31, '\001', "备用字段31");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_app_main.user_field32, '\001', "备用字段32");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_app_main.user_field33, '\001', "备用字段33");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_app_main.user_field34, '\001', "备用字段34");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_app_main.user_field35, '\001', "备用字段35");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_app_main.user_field36, '\001', "备用字段36");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_app_main.user_field37, '\001', "备用字段37");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_app_main.user_field38, '\001', "备用字段38");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_app_main.user_field39, '\001', "备用字段39");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_app_main.user_field40, '\001', "备用字段40");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_app_main.user_field41, '\001', "备用字段41");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_app_main.user_field42, '\001', "备用字段42");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_app_main.user_field43, '\001', "备用字段43");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_app_main.user_field44, '\001', "备用字段44");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_app_main.user_field45, '\001', "备用字段45");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_app_main.user_field46, '\001', "备用字段46");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_app_main.user_field47, '\001', "备用字段47");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_app_main.user_field48, '\001', "备用字段48");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_app_main.user_field49, '\001', "备用字段49");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_app_main.user_field50, '\001', "备用字段50");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_app_main.user_field51, '\001', "备用字段51");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_app_main.last_modified_datetime, '\001', "最后修改时间");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_app_main.jpa_Vversion, '\001', "乐观锁");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_app_main.uesr_field52, '\001', "备用字段52");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_app_main.is_check_flag, "1", sizeof(sdb_icps_wb_tm_app_main.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_APP_MAIN", SD_ICPS_WB_TM_APP_MAIN, NUMELE(SD_ICPS_WB_TM_APP_MAIN), &sdb_icps_wb_tm_app_main, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_app_main.app_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 主卡申请人信息表
 */
int ffunc_parse_wbank_file_to_db_tm_app_prim_applicant_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_APP_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_app_info, 0x00, sizeof(sdb_icps_wb_tm_app_info));
            pstrcopy(sdb_icps_wb_tm_app_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_app_info.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_app_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_app_info.id, '\001', "标识");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_app_info.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_app_info.app_no, '\001', "申请件编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_app_info.user_field53, '\001', "备用字段53");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_app_info.user_field54, '\001', "备用字段54");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_app_info.name, '\001', "姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_app_info.emb_logo, '\001', "凸印名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_app_info.gender, '\001', "性别");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_app_info.nationality, '\001', "国籍");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_app_info.residency_country_cd, '\001', "永久居住地国家代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_app_info.id_type, '\001', "证件类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_app_info.id_no, '\001', "证件号码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_app_info.user_field55, '\001', "备用字段55");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_app_info.user_field56, '\001', "备用字段56");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_app_info.birthday, '\001', "生日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_app_info.user_field57, '\001', "备用字段57");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_app_info.user_field58, '\001', "备用字段58");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_app_info.user_field59, '\001', "备用字段59");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_app_info.user_field60, '\001', "备用字段60");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_app_info.user_field61, '\001', "备用字段61");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_app_info.user_field62, '\001', "备用字段62");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_app_info.user_field63, '\001', "备用字段63");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_app_info.user_field64, '\001', "备用字段64");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_app_info.user_field65, '\001', "备用字段65");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_app_info.user_field66, '\001', "备用字段66");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_app_info.user_field67, '\001', "备用字段67");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_app_info.user_field68, '\001', "备用字段68");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_app_info.user_field69, '\001', "备用字段69");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_app_info.cellphone, '\001', "移动电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_app_info.user_field70, '\001', "备用字段70");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_app_info.user_field71, '\001', "备用字段71");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_app_info.user_field72, '\001', "备用字段72");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_app_info.user_field73, '\001', "备用字段73");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_app_info.user_field74, '\001', "备用字段74");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_app_info.user_field75, '\001', "备用字段75");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_app_info.user_field76, '\001', "备用字段76");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_app_info.user_field77, '\001', "备用字段77");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_app_info.user_field78, '\001', "备用字段78");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_app_info.user_field79, '\001', "备用字段79");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_app_info.user_field80, '\001', "备用字段80");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_app_info.user_field81, '\001', "备用字段81");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_app_info.user_field82, '\001', "备用字段82");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_app_info.user_field83, '\001', "备用字段83");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_app_info.user_field84, '\001', "备用字段84");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_app_info.user_field85, '\001', "备用字段85");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_app_info.user_field86, '\001', "备用字段86");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_app_info.user_field87, '\001', "备用字段87");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_app_info.user_field88, '\001', "备用字段88");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_app_info.user_field89, '\001', "备用字段89");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_app_info.user_field90, '\001', "备用字段90");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_app_info.user_field91, '\001', "备用字段91");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_app_info.user_field92, '\001', "备用字段92");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_app_info.user_field93, '\001', "备用字段93");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_app_info.user_field94, '\001', "备用字段94");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_app_info.user_field95, '\001', "备用字段95");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_app_info.user_field96, '\001', "备用字段96");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_app_info.user_field97, '\001', "备用字段97");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_app_info.user_field98, '\001', "备用字段98");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_app_info.user_field99, '\001', "备用字段99");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_app_info.pr_of_country, '\001', "是否永久居住");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_app_info.user_field100, '\001', "备用字段100");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_app_info.user_field101, '\001', "备用字段101");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_app_info.user_field102, '\001', "备用字段102");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_app_info.user_field103, '\001', "备用字段103");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_app_info.user_field104, '\001', "备用字段104");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_app_info.user_field105, '\001', "备用字段105");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_app_info.user_field106, '\001', "备用字段106");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_app_info.user_field107, '\001', "备用字段107");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_app_info.user_field108, '\001', "备用字段108");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_app_info.user_field109, '\001', "备用字段109");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_app_info.user_field110, '\001', "备用字段110");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_app_info.user_field111, '\001', "备用字段111");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_app_info.user_field112, '\001', "备用字段112");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_app_info.jpa_version, '\001', "乐观锁");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_app_info.cust_no, '\001', "客户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_app_info.acct_no, '\001', "账户号");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_app_info.is_check_flag, "1", sizeof(sdb_icps_wb_tm_app_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_APP_INFO", SD_ICPS_WB_TM_APP_INFO, NUMELE(SD_ICPS_WB_TM_APP_INFO),
                    &sdb_icps_wb_tm_app_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_app_info.app_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 客户信息表
 */
int ffunc_parse_wbank_file_to_db_tm_customer(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_CUSTOMER WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_app_info, 0x00, sizeof(sdb_icps_wb_tm_app_info));
            pstrcopy(sdb_icps_wb_tm_app_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_app_info.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_app_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_app_info.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_app_info.cust_id, '\001', "客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_app_info.id_num, '\001', "证件号码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_app_info.id_type, '\001', "证件类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_app_info.title, '\001', "称谓");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_app_info.name, '\001', "姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_app_info.gender, '\001', "性别");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_app_info.brith_date, '\001', "生日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_app_info.user_field177, '\001', "备用字段177");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_app_info.user_field178, '\001', "备用字段178");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_app_info.nationality, '\001', "国籍");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_app_info.pr_of_country, '\001', "是否永久居住");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_app_info.residency_country_cd, '\001', "永久居住地国家代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_app_info.user_field179, '\001', "备用字段179");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_app_info.user_field180, '\001', "备用字段180");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_app_info.user_field181, '\001', "备用字段181");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_app_info.user_field182, '\001', "备用字段182");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_app_info.user_field183, '\001', "备用字段183");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_app_info.user_field184, '\001', "备用字段184");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_app_info.user_field185, '\001', "备用字段185");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_app_info.user_field186, '\001', "备用字段186");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_app_info.user_field187, '\001', "备用字段187");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_app_info.mobile_no, '\001', "移动电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_app_info.user_field188, '\001', "备用字段188");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_app_info.user_field189, '\001', "备用字段189");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_app_info.user_field190, '\001', "备用字段190");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_app_info.language_ind, '\001', "语言代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_app_info.user_field191, '\001', "备用字段191");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_app_info.user_field192, '\001', "备用字段192");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_app_info.user_field193, '\001', "备用字段193");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_app_info.user_field194, '\001', "备用字段194");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_app_info.user_field195, '\001', "备用字段195");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_app_info.user_field196, '\001', "备用字段196");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_app_info.user_field197, '\001', "备用字段197");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_app_info.user_field198, '\001', "备用字段198");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_app_info.user_field199, '\001', "备用字段199");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_app_info.user_field200, '\001', "备用字段200");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_app_info.user_field201, '\001', "备用字段201");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_app_info.user_field202, '\001', "备用字段202");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_app_info.user_field203, '\001', "备用字段203");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_app_info.user_field204, '\001', "备用字段204");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_app_info.user_field205, '\001', "备用字段205");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_app_info.user_field206, '\001', "备用字段206");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_app_info.user_field207, '\001', "备用字段207");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_app_info.user_field208, '\001', "备用字段208");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_app_info.user_field209, '\001', "备用字段209");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_app_info.user_field210, '\001', "备用字段210");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_app_info.user_field211, '\001', "备用字段211");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_app_info.user_field212, '\001', "备用字段212");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_app_info.user_field213, '\001', "备用字段213");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_app_info.user_field214, '\001', "备用字段214");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_app_info.user_field215, '\001', "备用字段215");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_app_info.user_field216, '\001', "备用字段216");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_app_info.user_field217, '\001', "备用字段217");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_app_info.user_field218, '\001', "备用字段218");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_app_info.user_field219, '\001', "备用字段219");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_app_info.user_field220, '\001', "备用字段220");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_app_info.user_field221, '\001', "备用字段221");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_app_info.user_field222, '\001', "备用字段222");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_app_info.user_field223, '\001', "备用字段223");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_app_info.user_field224, '\001', "备用字段224");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_app_info.user_field225, '\001', "备用字段225");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_app_info.user_field226, '\001', "备用字段226");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_app_info.user_field227, '\001', "备用字段227");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_app_info.user_field228, '\001', "备用字段228");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_app_info.user_field229, '\001', "备用字段229");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_app_info.emb_name, '\001', "拼音名");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_app_info.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_app_info.cust_limit_id, '\001', "客户额度ID");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_app_info.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_app_info.user_field230, '\001', "备用字段230");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_app_info.user_field231, '\001', "备用字段231");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_app_info.surname, '\001', "姓氏");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_app_info.user_field232, '\001', "备用字段232");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_app_info.user_field233, '\001', "备用字段233");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_app_info.user_field234, '\001', "备用字段234");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_app_info.is_check_flag, "1", sizeof(sdb_icps_wb_tm_app_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_CUSTOMER", SD_ICPS_WB_TM_CUSTOMER, NUMELE(SD_ICPS_WB_TM_CUSTOMER),
                    &sdb_icps_wb_tm_app_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_app_info.cust_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 当日入账交易表
 */
int ffunc_parse_wbank_file_to_db_tt_txn_post(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TT_TXN_POST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tt_txn_post, 0x00, sizeof(sdb_icps_wb_tt_txn_post));
            pstrcopy(sdb_icps_wb_tt_txn_post.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tt_txn_post.busi_date)); /*业务日期*/
            sdb_icps_wb_tt_txn_post.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tt_txn_post.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tt_txn_post.trans_serial, '\001', "交易流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tt_txn_post.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tt_txn_post.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tt_txn_post.card_no, '\001', "卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tt_txn_post.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tt_txn_post.bsc_logiccard_no, '\001', "逻辑卡主卡卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tt_txn_post.product_code, '\001', "产品代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tt_txn_post.trans_date, '\001', "交易日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tt_txn_post.trans_time, '\001', "交易时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tt_txn_post.post_txn_type, '\001', "入账交易类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tt_txn_post.txn_code, '\001', "交易码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tt_txn_post.loan_flag, '\001', "借贷标志");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tt_txn_post.trans_amt, '\001', "交易金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tt_txn_post.post_amt, '\001', "入账币种金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tt_txn_post.transfer_in_date, '\001', "入账日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tt_txn_post.user_field235, '\001', "备用字段235");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tt_txn_post.user_field236, '\001', "备用字段236");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tt_txn_post.txn_curr_cd, '\001', "交易币种代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tt_txn_post.post_curr_cd, '\001', "入账币种代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tt_txn_post.orig_trans_date, '\001', "原始交易日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tt_txn_post.plan_nbr, '\001', "信用计划号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tt_txn_post.ref_nbr, '\001', "交易参考号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tt_txn_post.txn_desc, '\001', "交易描述");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tt_txn_post.txn_short_desc, '\001', "账单交易描述");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tt_txn_post.user_field237, '\001', "备用字段237");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tt_txn_post.posting_flag, '\001', "入账结果标示码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tt_txn_post.pre_posting_flag, '\001', "往日入账结果标示码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tt_txn_post.user_field238, '\001', "备用字段238");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tt_txn_post.orig_pmt_amt, '\001', "还款交易原始金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tt_txn_post.user_field239, '\001', "备用字段239");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tt_txn_post.user_field240, '\001', "备用字段240");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tt_txn_post.user_field241, '\001', "备用字段241");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tt_txn_post.user_field242, '\001', "备用字段242");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tt_txn_post.mcc, '\001', "商户类别代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tt_txn_post.input_txn_code, '\001', "原交易交易码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tt_txn_post.input_txn_amt, '\001', "原交易交易金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tt_txn_post.input_sett_amt, '\001', "原交易清算金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tt_txn_post.user_field246, '\001', "备用字段246");
            /*TODO:此处示例文件比文档多 三个字段*/
            //ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tt_txn_post.not_sure1, '\001', "临时使用1");
            //ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tt_txn_post.not_sure2, '\001', "临时使用2");
            //ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tt_txn_post.not_sure3, '\001', "临时使用3");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tt_txn_post.stmt_date, '\001', "下一到期还款日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tt_txn_post.user_field247, '\001', "备用字段247");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tt_txn_post.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tt_txn_post.term, '\001', "所在贷款期数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tt_txn_post.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tt_txn_post.sys_trans_id, '\001', "系统调用流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tt_txn_post.user_field248, '\001', "备用字段248");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tt_txn_post.sub_terminal_type, '\001', "终端类型");
            /*TODO:此处示例文件比文档多 三个字段*/
            //ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tt_txn_post.not_sure4, '\001', "临时使用4");
            //ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tt_txn_post.not_sure5, '\001', "临时使用5");
            //ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tt_txn_post.not_sure6, '\001', "临时使用6");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tt_txn_post.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tt_txn_post.paid_stmt_date, '\001', "还款对应出单日（没用）");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tt_txn_post.repay_amt, '\001', "应还款额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tt_txn_post.bank_proportion, '\001', "银行出资比例");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tt_txn_post.is_check_flag, "1", sizeof(sdb_icps_wb_tt_txn_post.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TT_TXN_POST", SD_ICPS_WB_TT_TXN_POST, NUMELE(SD_ICPS_WB_TT_TXN_POST),
                    &sdb_icps_wb_tt_txn_post, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tt_txn_post.trans_serial), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 挂账交易历史表
 */
int ffunc_parse_wbank_file_to_db_tm_txn_reject(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_TXN_REJECT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_txn_reject, 0x00, sizeof(sdb_icps_wb_tm_txn_reject));
            pstrcopy(sdb_icps_wb_tm_txn_reject.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_tm_txn_reject.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_txn_reject.file_order = rcdCnt;


            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_txn_reject.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_txn_reject.trans_serial, '\001', "交易流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_txn_reject.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_txn_reject.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_txn_reject.card_no, '\001', "卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_txn_reject.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_txn_reject.bsc_logiccard_no, '\001', "逻辑卡主卡卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_txn_reject.product_code, '\001', "产品代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_txn_reject.trans_date, '\001', "交易日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_txn_reject.trans_time, '\001', "交易时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_txn_reject.post_txn_type, '\001', "入账交易类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_txn_reject.txn_code, '\001', "交易码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_txn_reject.loan_flag, '\001', "借贷标志");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_txn_reject.trans_amt, '\001', "交易金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_txn_reject.post_amt, '\001', "入账币种金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_txn_reject.transfer_in_date, '\001', "入账日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_txn_reject.user_field252, '\001', "备用字段252");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_txn_reject.user_field253, '\001', "备用字段253");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_txn_reject.txn_curr_cd, '\001', "交易币种代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_txn_reject.post_curr_cd, '\001', "入账币种代码");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_txn_reject.orig_trans_date, '\001', "原始交易日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_txn_reject.plan_nbr, '\001', "信用计划号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_txn_reject.ref_nbr, '\001', "交易参考号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_txn_reject.txn_desc, '\001', "交易描述");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_txn_reject.txn_short_desc, '\001', "账单交易描述");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_txn_reject.user_field254, '\001', "备用字段254");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_txn_reject.posting_flag, '\001', "入账结果标示码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_txn_reject.pre_posting_flag, '\001', "往日入账结果标示码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_txn_reject.user_field255, '\001', "备用字段255");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_txn_reject.orig_pmt_amt, '\001', "还款交易原始金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_txn_reject.user_field256, '\001', "备用字段256");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_txn_reject.user_field257, '\001', "备用字段257");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_txn_reject.user_field258, '\001', "备用字段258");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_txn_reject.user_field259, '\001', "备用字段259");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_txn_reject.mcc, '\001', "商户类别代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_txn_reject.input_txn_code, '\001', "原交易交易码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_txn_reject.input_txn_amt, '\001', "原交易交易金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_txn_reject.input_sett_amt, '\001', "原交易清算金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_txn_reject.user_field260, '\001', "备用字段260");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_txn_reject.user_field261, '\001', "备用字段261");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_txn_reject.user_field262, '\001', "备用字段262");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_txn_reject.user_field263, '\001', "备用字段263");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_txn_reject.stmt_date, '\001', "下一到期还款日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_txn_reject.voucher_no, '\001', "销售单凭证号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_txn_reject.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_txn_reject.term, '\001', "所在贷款期数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_txn_reject.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_txn_reject.sys_trans_id, '\001', "系统调用流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_txn_reject.user_field265, '\001', "备用字段265");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_txn_reject.user_field264, '\001', "备用字段264");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_txn_reject.sub_terminal_type, '\001', "终端类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_txn_reject.user_field266, '\001', "备用字段266");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_txn_reject.user_field267, '\001', "备用字段267");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_txn_reject.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_txn_reject.paid_stmt_date, '\001', "还款所属出单日（无用）");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_txn_reject.repay_amt, '\001', "应还款额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_txn_reject.bank_proportion, '\001', "银行出资比例");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_txn_reject.is_check_flag, "1", sizeof(sdb_icps_wb_tm_txn_reject.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_TXN_REJECT", SD_ICPS_WB_TM_TXN_REJECT, NUMELE(SD_ICPS_WB_TM_TXN_REJECT),
                    &sdb_icps_wb_tm_txn_reject, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_txn_reject.trans_serial), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 分期信息表
 */
int ffunc_parse_wbank_file_to_db_tm_loan(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_LOAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_loan, 0x00, sizeof(sdb_icps_wb_tm_loan));
            pstrcopy(sdb_icps_wb_tm_loan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_loan.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_loan.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_loan.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_loan.loan_id, '\001', "借据ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_loan.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_loan.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_loan.ref_nbr, '\001', "交易参考号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_loan.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_loan.card_no, '\001', "卡号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_loan.register_date, '\001', "贷款注册日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_loan.request_time, '\001', "请求日期时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_loan.loan_type, '\001', "贷款类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_loan.loan_status, '\001', "贷款状态");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_loan.last_loan_status, '\001', "贷款上次状态");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_loan.loan_init_term, '\001', "贷款总期数");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_loan.curr_term, '\001', "当前期数");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_loan.remain_term, '\001', "剩余期数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_loan.loan_init_prin, '\001', "贷款总本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_loan.loan_fixed_pmt_prin, '\001', "贷款每期应还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_loan.loan_first_term_prin, '\001', "贷款首期应还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_loan.loan_final_term_prin, '\001', "贷款末期应还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_loan.loan_init_fee1, '\001', "贷款总手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_loan.loan_fixed_fee1, '\001', "贷款每期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_loan.loan_first_term_fee1, '\001', "贷款首期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_loan.loan_final_term_fee1, '\001', "贷款末期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 24, sdb_icps_wb_tm_loan.unearned_prin, '\001', "贷款账单的本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 25, sdb_icps_wb_tm_loan.unearned_fee1, '\001', "贷款账单手续费");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 26, sdb_icps_wb_tm_loan.paid_out_date, '\001', "还清日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 27, sdb_icps_wb_tm_loan.terminate_date, '\001', "提前终止日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_wb_tm_loan.terminate_reason_cd, '\001', "贷款终止原因代码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 29, sdb_icps_wb_tm_loan.prin_paid, '\001', "已偿还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 30, sdb_icps_wb_tm_loan.int_paid, '\001', "已偿还利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 31, sdb_icps_wb_tm_loan.fee_paid, '\001', "已偿还费用");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 32, sdb_icps_wb_tm_loan.loan_curr_bal, '\001', "贷款当前总余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_wb_tm_loan.loan_bal_xfrout, '\001', "贷款未到期余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 34, sdb_icps_wb_tm_loan.loan_bal_xfrin, '\001', "贷款已到期余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 35, sdb_icps_wb_tm_loan.loan_bal_principal, '\001', "欠款总本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 36, sdb_icps_wb_tm_loan.loan_bal_interest, '\001', "欠款总利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_wb_tm_loan.loan_bal_penalty, '\001', "欠款总罚息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 38, sdb_icps_wb_tm_loan.loan_prin_xfrout, '\001', "贷款未到期本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 39, sdb_icps_wb_tm_loan.loan_prin_xfrin, '\001', "贷款已到期本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 40, sdb_icps_wb_tm_loan.loan_fee1_xfrout, '\001', "贷款未到期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 41, sdb_icps_wb_tm_loan.loan_fee1_xfrin, '\001', "贷款已到期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 42, sdb_icps_wb_tm_loan.orig_txn_amt, '\001', "原始交易币种金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 43, sdb_icps_wb_tm_loan.orig_trans_date, '\001', "原始交易日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_wb_tm_loan.orig_auth_code, '\001', "原始交易授权码");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 45, sdb_icps_wb_tm_loan.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_wb_tm_loan.loan_code, '\001', "贷款产品号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_wb_tm_loan.register_id, '\001', "贷款申请顺序号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_wb_tm_loan.resch_init_prin, '\001', "展期本金金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 49, sdb_icps_wb_tm_loan.resch_date, '\001', "展期生效日期");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_wb_tm_loan.bef_resch_fixed_pmt_prin, '\001', "展期前每期应还本金");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 51, sdb_icps_wb_tm_loan.bef_resch_init_term, '\001', "展期前总期数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 52, sdb_icps_wb_tm_loan.bef_resch_first_term_prin, '\001', "展期前贷款首期应还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 53, sdb_icps_wb_tm_loan.bef_resch_final_term_prin, '\001', "展期前贷款末期应还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_wb_tm_loan.bef_resch_init_fee1, '\001', "展期前贷款总手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_wb_tm_loan.bef_resch_fixed_fee1, '\001', "BEF_贷款每期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_wb_tm_loan.bef_resch_first_term_fee1, '\001', "展期前贷款首期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_wb_tm_loan.bef_resch_final_term_fee1, '\001', "展期前贷款末期手续费");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_wb_tm_loan.resch_first_term_fee1, '\001', "展期后首期手续费");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_wb_tm_loan.loan_fee_method, '\001', "贷款手续费收取方式");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 60, sdb_icps_wb_tm_loan.interest_rate, '\001', "基础利率");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 61, sdb_icps_wb_tm_loan.penalty_rate, '\001', "罚息利率");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 62, sdb_icps_wb_tm_loan.compound_rate, '\001', "复利利率");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 63, sdb_icps_wb_tm_loan.float_rate, '\001', "浮动比例");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_wb_tm_loan.loan_receipt_nbr, '\001', "借据号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 65, sdb_icps_wb_tm_loan.loan_expire_date, '\001', "贷款到期日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_wb_tm_loan.loan_cd, '\001', "贷款逾期最大期数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 67, sdb_icps_wb_tm_loan.payment_hist, '\001', "24个月还款状态");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 68, sdb_icps_wb_tm_loan.ctd_payment_amt, '\001', "当期还款额");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 69, sdb_icps_wb_tm_loan.past_resch_cnt, '\001', "已展期次数");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 70, sdb_icps_wb_tm_loan.past_shorted_cnt, '\001', "已缩期次数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 71, sdb_icps_wb_tm_loan.adv_pmt_amt, '\001', "提前还款金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 72, sdb_icps_wb_tm_loan.last_action_date, '\001', "上次行动日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_wb_tm_loan.last_action_type, '\001', "上次行动类型");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 74, sdb_icps_wb_tm_loan.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 75, sdb_icps_wb_tm_loan.activate_date, '\001', "激活日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 76, sdb_icps_wb_tm_loan.interest_calc_base, '\001', "计息基数");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 77, sdb_icps_wb_tm_loan.first_bill_date, '\001', "首个到期还款日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_wb_tm_loan.age_cd, '\001', "账龄");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_wb_tm_loan.recalc_ind, '\001', "利率重算标志");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 80, sdb_icps_wb_tm_loan.recalc_date, '\001', "利率重算日");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 81, sdb_icps_wb_tm_loan.grace_date, '\001', "宽限日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 82, sdb_icps_wb_tm_loan.cancel_date, '\001', "撤销日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_wb_tm_loan.cancel_reason, '\001', "贷款撤销原因");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_wb_tm_loan.bank_group_id, '\001', "银团编号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 85, sdb_icps_wb_tm_loan.due_days, '\001', "当前逾期天数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_wb_tm_loan.contract_ver, '\001', "合同版本号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 87, sdb_icps_wb_tm_loan.loan_init_interest, '\001', "贷款总利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 88, sdb_icps_wb_tm_loan.bef_init_interest, '\001', "原贷款总利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 89, sdb_icps_wb_tm_loan.bank_proportion, '\001', "银行出资比例");


            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_loan.is_check_flag, "1", sizeof(sdb_icps_wb_tm_loan.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_LOAN", SD_ICPS_WB_TM_LOAN, NUMELE(SD_ICPS_WB_TM_LOAN),
                    &sdb_icps_wb_tm_loan, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_loan.ref_nbr), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 贷款分配表
 */
int ffunc_parse_wbank_file_to_db_tm_schedule(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_SCHEDULE WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_tm_schedule, 0x00, sizeof(sdb_icps_wb_tm_schedule));
            pstrcopy(sdb_icps_wb_tm_schedule.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_tm_schedule.busi_date)); /*业务日期*/
            sdb_icps_wb_tm_schedule.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_tm_schedule.schedule_id, '\001', "分配表ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_tm_schedule.loan_id, '\001', "贷款计划ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_tm_schedule.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_tm_schedule.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_tm_schedule.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_tm_schedule.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_tm_schedule.card_no, '\001', "卡号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_tm_schedule.loan_init_prin, '\001', "贷款总本金");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_tm_schedule.loan_init_term, '\001', "贷款总期数");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_tm_schedule.curr_term, '\001', "当前期数");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_tm_schedule.loan_term_prin, '\001', "应还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_tm_schedule.loan_term_fee1, '\001', "应还费用");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_tm_schedule.loan_term_interest, '\001', "应还利息");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_tm_schedule.loan_pmt_due_date, '\001', "到款到期还款日期");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_tm_schedule.loan_grace_date, '\001', "宽限日");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_tm_schedule.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_tm_schedule.start_date, '\001', "起息日");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_tm_schedule.schedule_action, '\001', "还款计划操作动作");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_tm_schedule.prin_paid, '\001', "已偿还本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_tm_schedule.int_paid, '\001', "已偿还利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_tm_schedule.penalty_paid, '\001', "已偿还罚息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_tm_schedule.compound_paid, '\001', "已偿还复利");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 23, sdb_icps_wb_tm_schedule.fee_paid, '\001', "已偿还费用");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_tm_schedule.is_check_flag, "1", sizeof(sdb_icps_wb_tm_schedule.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_SCHEDULE", SD_ICPS_WB_TM_SCHEDULE, NUMELE(SD_ICPS_WB_TM_SCHEDULE),
                    &sdb_icps_wb_tm_schedule, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_tm_schedule.schedule_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 会计分录日报表
 */
int ffunc_parse_wbank_file_to_db_ds_accounting_flow(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_ACCOUNTING_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_ds_accounting_flow, 0x00, sizeof(sdb_icps_wb_ds_accounting_flow));
            pstrcopy(sdb_icps_wb_ds_accounting_flow.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_wb_ds_accounting_flow.busi_date)); /*业务日期*/
            sdb_icps_wb_ds_accounting_flow.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_ds_accounting_flow.org, '\001', "内部机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_ds_accounting_flow.host_trans_serial, '\001', "核心交易流水");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_ds_accounting_flow.card_no, '\001', "卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_ds_accounting_flow.currency, '\001', "币种");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_ds_accounting_flow.txn_code, '\001', "交易码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_ds_accounting_flow.txn_desc, '\001', "交易描述");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_ds_accounting_flow.db_cr_ind, '\001', "借贷标记");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_ds_accounting_flow.post_amt, '\001', "入账金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_ds_accounting_flow.post_gl_ind, '\001', "入账方式");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_wb_ds_accounting_flow.owning_branch, '\001', "支行");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_wb_ds_accounting_flow.subject, '\001', "科目");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_wb_ds_accounting_flow.red_flag, '\001', "红蓝字标识");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 13, sdb_icps_wb_ds_accounting_flow.queue, '\001', "排序");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_wb_ds_accounting_flow.product_cd, '\001', "产品号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_wb_ds_accounting_flow.ref_nbr, '\001', "借据号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_wb_ds_accounting_flow.age_group, '\001', "账龄组");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_wb_ds_accounting_flow.plan_nbr, '\001', "信用计划号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_wb_ds_accounting_flow.bnp_group, '\001', "余额成分组");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_wb_ds_accounting_flow.bank_group_id, '\001', "银团代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_wb_ds_accounting_flow.bank_no, '\001', "银行代码");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 21, sdb_icps_wb_ds_accounting_flow.term, '\001', "期数");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 22, sdb_icps_wb_ds_accounting_flow.batchDate, '\001', "批量");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_ds_accounting_flow.is_check_flag, "1", sizeof(sdb_icps_wb_ds_accounting_flow.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_ACCOUNTING_FLOW", SD_ICPS_WB_DS_ACCOUNTING_FLOW, NUMELE(SD_ICPS_WB_DS_ACCOUNTING_FLOW),
                    &sdb_icps_wb_ds_accounting_flow, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_ds_accounting_flow.host_trans_serial), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 自定义额度信息表-授权
 */
int ffunc_parse_wbank_file_to_db_tm_cust_limit_o(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_CUST_LIMIT_O WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_cust_limit_o, 0x00, sizeof(sdb_icps_tm_cust_limit_o));
            pstrcopy(sdb_icps_tm_cust_limit_o.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_cust_limit_o.busi_date)); /*业务日期*/
            sdb_icps_tm_cust_limit_o.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_cust_limit_o.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_cust_limit_o.cust_limit_id, '\001', "客户额度ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_cust_limit_o.limit_category, '\001', "额度种类");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_cust_limit_o.limit_type, '\001', "额度类型");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_cust_limit_o.credit_limit, '\001', "信用额度");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_cust_limit_o.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_cust_limit_o.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_cust_limit_o.created_datetime, '\001', "创建时间");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_cust_limit_o.is_check_flag, "1", sizeof(sdb_icps_tm_cust_limit_o.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_CUST_LIMIT_O", SD_ICPS_WB_TM_CUST_LIMIT_O, NUMELE(SD_ICPS_WB_TM_CUST_LIMIT_O),
                    &sdb_icps_tm_cust_limit_o, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_tm_cust_limit_o.cust_limit_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 授权交易历史
 */
int ffunc_parse_wbank_file_to_db_tm_auth_hst(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_AUTH_HST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_auth_hst, 0x00, sizeof(sdb_icps_tm_auth_hst));
            pstrcopy(sdb_icps_tm_auth_hst.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_auth_hst.busi_date)); /*业务日期*/
            sdb_icps_tm_auth_hst.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_auth_hst.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_auth_hst.log_kv, '\001', "LOG的键值");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_auth_hst.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_auth_hst.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_auth_hst.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_auth_hst.acq_ref_no, '\001', "受理机构交易编码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_auth_hst.trans_amt, '\001', "交易金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_auth_hst.txn_curr_cd, '\001', "交易币种代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_auth_hst.user_field269, '\001', "备用字段269");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_auth_hst.acq_name_addr, '\001', "受理机构名称地址");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_auth_hst.chb_txn_amt, '\001', "持卡人账户币种金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_auth_hst.chb_curr_cd, '\001', "持卡人账户币种");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_auth_hst.user_field270, '\001', "备用字段270");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_auth_hst.mcc, '\001', "商户类别代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_auth_hst.acq_branch_id, '\001', "受理分行代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_auth_hst.fwd_inst_id, '\001', "转发机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_auth_hst.transmission_timestamp, '\001', "传送日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_tm_auth_hst.settle_date, '\001', "清算日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_tm_auth_hst.txn_direction, '\001', "交易方向");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_tm_auth_hst.txn_terminal, '\001', "交易终端");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_tm_auth_hst.trans_status, '\001', "交易状态");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_tm_auth_hst.trans_type, '\001', "交易类型");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 23, sdb_icps_tm_auth_hst.log_ol_time, '\001', "LOG联机时间");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 24, sdb_icps_tm_auth_hst.log_biz_date, '\001', "联机业务日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_tm_auth_hst.mti, '\001', "交易类型标识");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_tm_auth_hst.orig_txn_type, '\001', "原交易类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_tm_auth_hst.orig_fwd_inst_id, '\001', "原始转发机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_tm_auth_hst.orig_acq_inst_id, '\001', "原始受理机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_tm_auth_hst.orig_mti, '\001', "原交易MTI");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_tm_auth_hst.orig_trans_date, '\001', "原始交易日期");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 31, sdb_icps_tm_auth_hst.orig_trace_no, '\001', "原始系统跟踪号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 32, sdb_icps_tm_auth_hst.orig_txn_proc, '\001', "原交易处理码");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 33, sdb_icps_tm_auth_hst.orig_txn_amt, '\001', "原始交易币种金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 34, sdb_icps_tm_auth_hst.orig_log_kv, '\001', "原交易LOG键值");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 35, sdb_icps_tm_auth_hst.orig_txn_val_1, '\001', "原交易键值1");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 36, sdb_icps_tm_auth_hst.orig_txn_val_2, '\001', "原交易键值2");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 37, sdb_icps_tm_auth_hst.orig_chb_txn_amt, '\001', "原始入账币种金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 38, sdb_icps_tm_auth_hst.orig_biz_date, '\001', "原交易的联机业务处理日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 39, sdb_icps_tm_auth_hst.last_reversal_date, '\001', "最后一次冲撤时间");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 40, sdb_icps_tm_auth_hst.void_count, '\001', "撤销次数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 41, sdb_icps_tm_auth_hst.manual_auth_flag, '\001', "人工授权标志");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 42, sdb_icps_tm_auth_hst.opera_id, '\001', "操作员ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 43, sdb_icps_tm_auth_hst.brand, '\001', "品牌");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 44, sdb_icps_tm_auth_hst.product_code, '\001', "产品代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 45, sdb_icps_tm_auth_hst.mcc_type, '\001', "商户类型分组");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 46, sdb_icps_tm_auth_hst.user_field271, '\001', "备用字段271");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 47, sdb_icps_tm_auth_hst.user_field272, '\001', "备用字段272");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 48, sdb_icps_tm_auth_hst.comp_amt, '\001', "最终授权金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 49, sdb_icps_tm_auth_hst.final_upd_direction, '\001', "最终更新方向");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 50, sdb_icps_tm_auth_hst.final_upd_amt, '\001', "最终更新金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 51, sdb_icps_tm_auth_hst.ic_ind, '\001', "是否IC卡");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 52, sdb_icps_tm_auth_hst.the_3dsecure_type, '\001', "是否3D电子安全交易");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 53, sdb_icps_tm_auth_hst.vip_status, '\001', "VIP状态");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 54, sdb_icps_tm_auth_hst.curr_balance, '\001', "当前余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 55, sdb_icps_tm_auth_hst.cash_amt, '\001', "取现金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 56, sdb_icps_tm_auth_hst.otb, '\001', "可用额度");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 57, sdb_icps_tm_auth_hst.cash_otb, '\001', "取现可用额度");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 58, sdb_icps_tm_auth_hst.cust_otb, '\001', "客户可用额度");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 59, sdb_icps_tm_auth_hst.user_field273, '\001', "备用字段273");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 60, sdb_icps_tm_auth_hst.user_field274, '\001', "备用字段274");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 61, sdb_icps_tm_auth_hst.expire_date, '\001', "有效日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 62, sdb_icps_tm_auth_hst.track_one_result, '\001', "一磁道完整性结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 63, sdb_icps_tm_auth_hst.track_two_result, '\001', "二磁道完整性结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 64, sdb_icps_tm_auth_hst.track_three_result, '\001', "三磁道完整性结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 65, sdb_icps_tm_auth_hst.pwd_type, '\001', "密码种类");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 66, sdb_icps_tm_auth_hst.check_pwd_result, '\001', "验证密码结果");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 67, sdb_icps_tm_auth_hst.pay_pwd_err_num, '\001', "支付密码错误次数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 68, sdb_icps_tm_auth_hst.check_cvv_result, '\001', "CVV验证结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 69, sdb_icps_tm_auth_hst.check_cvv2_result, '\001', "CVV2验证结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 70, sdb_icps_tm_auth_hst.check_icvn_result, '\001', "ICVN验证结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 71, sdb_icps_tm_auth_hst.check_arqc_result, '\001', "ARQC验证结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 72, sdb_icps_tm_auth_hst.check_atc_result, '\001', "ATC验证结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 73, sdb_icps_tm_auth_hst.check_cvr_result, '\001', "CVR验证结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 74, sdb_icps_tm_auth_hst.check_tvr_result, '\001', "TVR验证结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 75, sdb_icps_tm_auth_hst.user_field275, '\001', "备用字段275");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 76, sdb_icps_tm_auth_hst.unmatch_cr, '\001', "未匹配贷记金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 77, sdb_icps_tm_auth_hst.unmatch_db, '\001', "未匹配借记金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 78, sdb_icps_tm_auth_hst.b002, '\001', "介质卡号-B002");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 79, sdb_icps_tm_auth_hst.b003, '\001', "交易处理码-B003");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 80, sdb_icps_tm_auth_hst.b007, '\001', "交易传输时间-B007");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 81, sdb_icps_tm_auth_hst.b011, '\001', "系统跟踪号-B011");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 82, sdb_icps_tm_auth_hst.b022, '\001', "服务点PIN获取码-B022");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 83, sdb_icps_tm_auth_hst.b025, '\001', "服务点条件码-B025");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 84, sdb_icps_tm_auth_hst.b032, '\001', "受理机构标识码-B032");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 85, sdb_icps_tm_auth_hst.b033, '\001', "受理机构名称地址-B033");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 86, sdb_icps_tm_auth_hst.b039, '\001', "返回码-B039");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 87, sdb_icps_tm_auth_hst.b042, '\001', "受卡方(商户)标识码-B042");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 88, sdb_icps_tm_auth_hst.user_field277, '\001', "备用字段276");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 89, sdb_icps_tm_auth_hst.user_field278, '\001', "备用字段277");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 90, sdb_icps_tm_auth_hst.b090, '\001', "原始数据元");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 91, sdb_icps_tm_auth_hst.opera_term_id, '\001', "操作用户终端编号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 92, sdb_icps_tm_auth_hst.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 93, sdb_icps_tm_auth_hst.b004, '\001', "交易货币金额-B004");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 94, sdb_icps_tm_auth_hst.b006, '\001', "账户货币金额-B006");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 95, sdb_icps_tm_auth_hst.b049, '\001', "交易货币代码-B049");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 96, sdb_icps_tm_auth_hst.b051, '\001', "账户货币代码-B051");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 97, sdb_icps_tm_auth_hst.b037, '\001', "检索参考号-B037");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 98, sdb_icps_tm_auth_hst.b028, '\001', "手续费-B028");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 99, sdb_icps_tm_auth_hst.b048, '\001', "附加数据-B048");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 100, sdb_icps_tm_auth_hst.b054, '\001', "返回余额数组-B054");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 101, sdb_icps_tm_auth_hst.user_field279, '\001', "备用字段278");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 102, sdb_icps_tm_auth_hst.user_field280, '\001', "备用字段279");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 103, sdb_icps_tm_auth_hst.user_field281, '\001', "备用字段280");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 104, sdb_icps_tm_auth_hst.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 105, sdb_icps_tm_auth_hst.sys_trans_id, '\001', "系统调用流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 106, sdb_icps_tm_auth_hst.user_field282, '\001', "备用字段281");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 107, sdb_icps_tm_auth_hst.sub_terminal_type, '\001', "终端类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 108, sdb_icps_tm_auth_hst.sub_merch_id, '\001', "二级商户编码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 109, sdb_icps_tm_auth_hst.sub_merch_name, '\001', "二级商户名称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 110, sdb_icps_tm_auth_hst.wares_desc, '\001', "商品信息");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 111, sdb_icps_tm_auth_hst.last_modified_datetime, '\001', "修改时间");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 112, sdb_icps_tm_auth_hst.part_month, '\001', "分区用的月份");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 113, sdb_icps_tm_auth_hst.paid_stmt_date, '\001', "还款账单日");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 114, sdb_icps_tm_auth_hst.repay_amt, '\001', "应还款额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 115, sdb_icps_tm_auth_hst.bank_proportion, '\001', "银行出资比例");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_auth_hst.is_check_flag, "1", sizeof(sdb_icps_tm_auth_hst.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_AUTH_HST", SD_ICPS_WB_TM_AUTH_HST, NUMELE(SD_ICPS_WB_TM_AUTH_HST),
                    &sdb_icps_tm_auth_hst, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_tm_auth_hst.log_kv), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 客户即时通讯信息表
 */
int ffunc_parse_wbank_file_to_db_tm_im_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_IM_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_im_info, 0x00, sizeof(sdb_icps_tm_im_info));
            pstrcopy(sdb_icps_tm_im_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_im_info.busi_date)); /*业务日期*/
            sdb_icps_tm_im_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_im_info.seq_no, '\001', "序号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_im_info.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_im_info.product_code, '\001', "产品代码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_im_info.cust_id, '\001', "客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_im_info.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_im_info.app_type, '\001', "应用类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_im_info.app_acct_no, '\001', "应用账号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_im_info.user_field282, '\001', "备用字段282");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_im_info.created_datetime, '\001', "创建时间");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_im_info.update_time, '\001', "更新时间");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_im_info.jpa_version, '\001', "乐观锁版本号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_im_info.last_update_biz_date, '\001', "上次联机更新业务日期");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_im_info.is_check_flag, "1", sizeof(sdb_icps_tm_im_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_IM_INFO", SD_ICPS_WB_TM_IM_INFO, NUMELE(SD_ICPS_WB_TM_IM_INFO), &sdb_icps_tm_im_info,
                    sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_tm_im_info.seq_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 还款借据清单表
 */
int ffunc_parse_wbank_file_to_db_tm_loan_receipt_list(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_LOAN_RECEIPT_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_loan_receipt_list, 0x00, sizeof(sdb_icps_tm_loan_receipt_list));
            pstrcopy(sdb_icps_tm_loan_receipt_list.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_tm_loan_receipt_list.busi_date)); /*业务日期*/
            sdb_icps_tm_loan_receipt_list.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_loan_receipt_list.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_loan_receipt_list.sys_trans_id, '\001', "系统调用流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_loan_receipt_list.loan_receipt_nbr, '\001', "借据号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_loan_receipt_list.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_loan_receipt_list.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_loan_receipt_list.card_no, '\001', "卡号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_loan_receipt_list.transfer_in_date, '\001', "入账日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_loan_receipt_list.last_modified_datetime, '\001', "时间戳");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_loan_receipt_list.pay_amt, '\001', "还款金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_loan_receipt_list.bank_group_id, '\001', "银团编号");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_loan_receipt_list.is_check_flag, "1", sizeof(sdb_icps_tm_loan_receipt_list.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_LOAN_RECEIPT_LIST", SD_ICPS_WB_TM_LOAN_RECEIPT_LIST, NUMELE(SD_ICPS_WB_TM_LOAN_RECEIPT_LIST), &sdb_icps_tm_loan_receipt_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("第[%d]条记录插入失败['%s','%s','%s']", rcdCnt, sdb_icps_tm_loan_receipt_list.busi_serial,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 还款借据清单表历史
 */
int ffunc_parse_wbank_file_to_db_tm_loan_receipt_list_hst(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_RE_HST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_re_hst, 0x00, sizeof(sdb_icps_tm_re_hst));
            pstrcopy(sdb_icps_tm_re_hst.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_re_hst.busi_date)); /*业务日期*/
            sdb_icps_tm_re_hst.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_re_hst.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_re_hst.sys_trans_id, '\001', "系统调用流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_re_hst.loan_receipt_nbr, '\001', "借据号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_re_hst.acct_no, '\001', "账户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_re_hst.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_re_hst.card_no, '\001', "卡号");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_re_hst.transfer_in_date, '\001', "入账日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_re_hst.last_modified_datetime, '\001', "时间戳");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_re_hst.move_date, '\001', "转移日期(大数据提取用)");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_re_hst.part_month, '\001', "分区用的月份");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_re_hst.pay_amt, '\001', "还款金额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_re_hst.bank_group_id, '\001', "银团编号");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_re_hst.is_check_flag, "1", sizeof(sdb_icps_tm_re_hst.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_RE_HST", SD_ICPS_WB_TM_RE_HST, NUMELE(SD_ICPS_WB_TM_RE_HST), &sdb_icps_tm_re_hst,
                    sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("第[%d]条记录插入失败['%s','%s','%s']", rcdCnt, sdb_icps_tm_re_hst.busi_serial,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 身份信息
 */
int ffunc_parse_wbank_file_to_db_tm_psb_personal_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_PSB_PERSONAL_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_psb_personal_info, 0x00, sizeof(sdb_icps_tm_psb_personal_info));
            pstrcopy(sdb_icps_tm_psb_personal_info.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_psb_personal_info.busi_date)); /*业务日期*/
            sdb_icps_tm_psb_personal_info.file_order = rcdCnt;

            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_psb_personal_info.id, '\001', "ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_psb_personal_info.app_no, '\001', "申请件编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_psb_personal_info.id_type, '\001', "证件类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_psb_personal_info.certi_no, '\001', "身份证号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_psb_personal_info.name, '\001', "姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_psb_personal_info.gender, '\001', "性别");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_psb_personal_info.birth_date, '\001', "出生日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_psb_personal_info.marital_status, '\001', "婚姻状况");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_psb_personal_info.mobile_no, '\001', "手机号码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_psb_personal_info.home_phone, '\001', "家庭电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_psb_personal_info.unit_phone, '\001', "单位电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_psb_personal_info.qualification, '\001', "学历");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_psb_personal_info.degree, '\001', "学位");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_psb_personal_info.address, '\001', "通讯地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_psb_personal_info.reside_addr, '\001', "户籍地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_psb_personal_info.mate_certp, '\001', "配偶证件类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_psb_personal_info.mate_cerno, '\001', "配偶证件号码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_tm_psb_personal_info.mate_name, '\001', "配偶姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_tm_psb_personal_info.mate_corp, '\001', "配偶工作单位");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_tm_psb_personal_info.mate_phone, '\001', "配偶联系电话");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_tm_psb_personal_info.addr, '\001', "居住地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_tm_psb_personal_info.reside_state, '\001', "居住状况");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_tm_psb_personal_info.comp_nm, '\001', "工作单位");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_tm_psb_personal_info.unit_addr, '\001', "单位地址");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_tm_psb_personal_info.profession, '\001', "职业");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_tm_psb_personal_info.comp_trade, '\001', "行业");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_tm_psb_personal_info.position, '\001', "职务");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_tm_psb_personal_info.teach_pose, '\001', "职称");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_tm_psb_personal_info.work_date, '\001', "本单位工作起始年份");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 30, sdb_icps_tm_psb_personal_info.infodate, '\001', "信息更新日期");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 31, sdb_icps_tm_psb_personal_info.create_time, '\001', "创建时间");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_psb_personal_info.is_check_flag, "1", sizeof(sdb_icps_tm_psb_personal_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_PSB_PERSONAL_INFO", SD_ICPS_WB_TM_PSB_PERSONAL_INFO, NUMELE(SD_ICPS_WB_TM_PSB_PERSONAL_INFO), &sdb_icps_tm_psb_personal_info,
                    sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_tm_psb_personal_info.id,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 备付金资金清算汇总
 */
int ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_tot(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_RRS_BDM_UDF_CLEAR_TOT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_rrs_bdm_udf_clear_tot, 0x00, sizeof(sdb_icps_rrs_bdm_udf_clear_tot));
            pstrcopy(sdb_icps_rrs_bdm_udf_clear_tot.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_rrs_bdm_udf_clear_tot.busi_date)); /*业务日期*/
            sdb_icps_rrs_bdm_udf_clear_tot.file_order = rcdCnt;

            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 1, sdb_icps_rrs_bdm_udf_clear_tot.data_dt, '\001', "数据日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_rrs_bdm_udf_clear_tot.acct_no, '\001', "备付金帐号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_rrs_bdm_udf_clear_tot.currency, '\001', "币种");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_rrs_bdm_udf_clear_tot.acct_name, '\001', "户名");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 5, sdb_icps_rrs_bdm_udf_clear_tot.last_balance, '\001', "上日账户余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_rrs_bdm_udf_clear_tot.balance, '\001', "本日账户余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_rrs_bdm_udf_clear_tot.payment_amt, '\001', "当日放款总金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_rrs_bdm_udf_clear_tot.repayment_amt, '\001', "当日还款总金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_rrs_bdm_udf_clear_tot.other_credit_amt, '\001', "当日其他划入款项");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_rrs_bdm_udf_clear_tot.other_debit_amt, '\001', "当日其他划出款项");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 11, sdb_icps_rrs_bdm_udf_clear_tot.ds, '\001', "日期分区");

            /*参与对账标志*/
            pstrcopy(sdb_icps_rrs_bdm_udf_clear_tot.is_check_flag, "1", sizeof(sdb_icps_rrs_bdm_udf_clear_tot.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_RRS_BDM_UDF_CLEAR_TOT", SD_ICPS_WB_RRS_BDM_UDF_CLEAR_TOT,
                    NUMELE(SD_ICPS_WB_RRS_BDM_UDF_CLEAR_TOT), &sdb_icps_rrs_bdm_udf_clear_tot, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("第[%d]条记录插入失败['%s','%s','%s']", rcdCnt, sdb_icps_rrs_bdm_udf_clear_tot.data_dt,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 备付金资金清算明细（分类汇总）
 */
int ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_detail(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_RRS_CLEAR_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_rrs_clear_detail, 0x00, sizeof(sdb_icps_rrs_clear_detail));
            pstrcopy(sdb_icps_rrs_clear_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_rrs_clear_detail.busi_date)); /*业务日期*/
            sdb_icps_rrs_clear_detail.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_rrs_clear_detail.data_dt, '\001', "数据日期");

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_rrs_clear_detail.data_dt           , '\001', "数据日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_rrs_clear_detail.acct_no           , '\001', "备付金帐号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_rrs_clear_detail.currency          , '\001', "币种");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_rrs_clear_detail.bank_group_code   , '\001', "银团编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_rrs_clear_detail.data_type         , '\001', "数据类型");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 6, sdb_icps_rrs_clear_detail.amount            , '\001', "发生额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_rrs_clear_detail.ds                , '\001', "日期分区");

            /*参与对账标志*/
            pstrcopy(sdb_icps_rrs_clear_detail.is_check_flag, "1", sizeof(sdb_icps_rrs_clear_detail.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_RRS_CLEAR_DETAIL", SD_ICPS_WB_RRS_CLEAR_DETAIL, NUMELE(SD_ICPS_WB_RRS_CLEAR_DETAIL),
                    &sdb_icps_rrs_clear_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("第[%d]条记录插入失败['%s','%s','%s']", rcdCnt, sdb_icps_rrs_clear_detail.data_dt,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 备付金其他款项资金明细（分类汇总）
 */
int ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_other_detail(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_RSS_OTHER_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_rss_other_detail, 0x00, sizeof(sdb_icps_rss_other_detail));
            pstrcopy(sdb_icps_rss_other_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_rss_other_detail.busi_date)); /*业务日期*/
            sdb_icps_rss_other_detail.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_rss_other_detail.data_dt, '\001', "数据日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_rss_other_detail.acct_no, '\001', "备付金账号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_rss_other_detail.currency, '\001', "币种");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_rss_other_detail.bank_group_code, '\001', "银团编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_rss_other_detail.data_type, '\001', "数据类型");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_rss_other_detail.ser_no, '\001', "明细序号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_rss_other_detail.amount, '\001', "发生额");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_rss_other_detail.memo, '\001', "备注");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_rss_other_detail.ds, '\001', "日期分区");

            /*参与对账标志*/
            pstrcopy(sdb_icps_rss_other_detail.is_check_flag, "1", sizeof(sdb_icps_rss_other_detail.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_RSS_OTHER_DETAIL", SD_ICPS_WB_RSS_OTHER_DETAIL, NUMELE(SD_ICPS_WB_RSS_OTHER_DETAIL),
                    &sdb_icps_rss_other_detail, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("第[%d]条记录插入失败['%s','%s','%s']", rcdCnt, sdb_icps_rss_other_detail.data_dt,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 催收记录表
 */
int ffunc_parse_wbank_file_to_db_tm_coll_rec(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_COLL_REC WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_coll_rec, 0x00, sizeof(sdb_icps_tm_coll_rec));
            pstrcopy(sdb_icps_tm_coll_rec.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_coll_rec.busi_date)); /*业务日期*/
            sdb_icps_tm_coll_rec.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_coll_rec.org, '\001', "机构号");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_coll_rec.coll_rec_id, '\001', "催记流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_coll_rec.case_no, '\001', "案件编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_coll_rec.cust_id, '\001', "客户编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_coll_rec.coll_rec_type, '\001', "催记类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_coll_rec.action_code, '\001', "催收动作");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_coll_rec.user_field1, '\001', "备用字段");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_coll_rec.user_field2, '\001', "备用字段2");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_coll_rec.coll_time, '\001', "催收时间");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_coll_rec.coll_conseq, '\001', "催收结果");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_coll_rec.prom_amt, '\001', "承诺金额");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_coll_rec.prom_date, '\001', "承诺日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_coll_rec.user_field3, '\001', "备用字段3");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_coll_rec.user_field4, '\001', "备用字段4");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_coll_rec.user_field5, '\001', "备用字段5");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_coll_rec.user_field6, '\001', "备用字段6");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_coll_rec.user_field7, '\001', "备用字段7");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_tm_coll_rec.user_field8, '\001', "备用字段8");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_tm_coll_rec.user_field9, '\001', "备用字段9");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 20, sdb_icps_tm_coll_rec.user_field10, '\001', "备用字段10");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_tm_coll_rec.user_field11, '\001', "备用字段11");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_tm_coll_rec.user_field12, '\001', "备用字段12");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_tm_coll_rec.user_field13, '\001', "备用字段13");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_tm_coll_rec.user_field14, '\001', "备用字段14");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_tm_coll_rec.user_field15, '\001', "备用字段15");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_tm_coll_rec.user_field16, '\001', "备用字段16");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_tm_coll_rec.user_field17, '\001', "备用字段17");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 28, sdb_icps_tm_coll_rec.user_field18, '\001', "备用字段18");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 29, sdb_icps_tm_coll_rec.user_field19, '\001', "备用字段19");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 30, sdb_icps_tm_coll_rec.user_field20, '\001', "备用字段20");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_coll_rec.is_check_flag, "1", sizeof(sdb_icps_tm_coll_rec.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_COLL_REC", SD_ICPS_WB_TM_COLL_REC, NUMELE(SD_ICPS_WB_TM_COLL_REC),
                    &sdb_icps_tm_coll_rec, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD,
                        Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_tm_coll_rec.coll_rec_id, sdb_icps_tm_coll_rec.case_no),
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 借据纳税加工表
 */
int ffunc_parse_wbank_file_to_db_tm_loan_vms(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_LOAN_VMS WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_loan_vms, 0x00, sizeof(sdb_icps_tm_loan_vms));
            pstrcopy(sdb_icps_tm_loan_vms.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_tm_loan_vms.busi_date)); /*业务日期*/
            sdb_icps_tm_loan_vms.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_loan_vms.id, '\001', "纳税借据ID");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_loan_vms.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_loan_vms.card_no, '\001', "介质卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_loan_vms.ref_nbr, '\001', "交易参考号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_loan_vms.bank_group_id, '\001', "银团编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_loan_vms.bank_no, '\001', "银行编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_loan_vms.product_cd, '\001', "产品号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_loan_vms.biz_tax_interes, '\001', "营业税下的应计和应收息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_loan_vms.vat_int_bal, '\001', "90天内的应纳税息余额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_loan_vms.norevoke_vat_int_bal, '\001', "不冲抵算法下应纳税息（含90天内+90天外还款补记部分）");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_loan_vms.vat_tax, '\001', "记账增值税");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 12, sdb_icps_tm_loan_vms.loan_int_term, '\001', "贷款总期数");
            ICPS_WB_GET_DATE_TIME_BY_DIV(sFileLineGBK, 13, sdb_icps_tm_loan_vms.last_modified_time, '\001', "上次修改时间");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 14, sdb_icps_tm_loan_vms.paid_out_date, '\001', "结清日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_tm_loan_vms.age_no, '\001', "账龄");
            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 16, sdb_icps_tm_loan_vms.batch_date, '\001', "批量日期");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 17, sdb_icps_tm_loan_vms.lpa_version, '\001', "乐观锁版本号");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_loan_vms.is_check_flag, "1", sizeof(sdb_icps_tm_loan_vms.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_LOAN_VMS", SD_ICPS_WB_TM_LOAN_VMS, NUMELE(SD_ICPS_WB_TM_LOAN_VMS),
                    &sdb_icps_tm_loan_vms, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_tm_loan_vms.id, sdb_icps_tm_loan_vms.ref_nbr),
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 免息券信息表
 */
int ffunc_parse_wbank_file_to_db_tm_free_coupons_info(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_TM_FREE_COUPONS_INFO WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_tm_free_coupons_info, 0x00, sizeof(sdb_icps_tm_free_coupons_info));
            pstrcopy(sdb_icps_tm_free_coupons_info.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_tm_free_coupons_info.busi_date)); /*业务日期*/
            sdb_icps_tm_free_coupons_info.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_tm_free_coupons_info.org, '\001', "机构号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_tm_free_coupons_info.list_no, '\001', "资格编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_tm_free_coupons_info.act_no, '\001', "活动编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_tm_free_coupons_info.equity_no, '\001', "权益编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_tm_free_coupons_info.equity_type, '\001', "权益类型");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 6, sdb_icps_tm_free_coupons_info.equity_value, '\001', "权益值");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_tm_free_coupons_info.loan_receipt_nbr, '\001', "借据号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_tm_free_coupons_info.card_no, '\001', "介质卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_tm_free_coupons_info.ref_nbr, '\001', "交易参考");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_tm_free_coupons_info.bank_group_id, '\001', "银团编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_tm_free_coupons_info.bank_no, '\001', "银行编号");

            /*参与对账标志*/
            pstrcopy(sdb_icps_tm_free_coupons_info.is_check_flag, "1", sizeof(sdb_icps_tm_free_coupons_info.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_TM_FREE_COUPONS_INFO", SD_ICPS_WB_TM_FREE_COUPONS_INFO,
                    NUMELE(SD_ICPS_WB_TM_FREE_COUPONS_INFO), &sdb_icps_tm_free_coupons_info, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_tm_free_coupons_info.list_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 免息券信息表
 */
int ffunc_parse_wbank_file_to_db_ds_split_diff(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_SPLIT_DIFF WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_split_diff, 0x00, sizeof(sdb_icps_ds_split_diff));
            pstrcopy(sdb_icps_ds_split_diff.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_ds_split_diff.busi_date)); /*业务日期*/
            sdb_icps_ds_split_diff.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_split_diff.partition_date, '\001', "批量日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_split_diff.error_type, '\001', "异常类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_split_diff.bank_group_id, '\001', "银团编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_split_diff.bank_no, '\001', "银行编号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_split_diff.busi_serial, '\001', "业务流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_split_diff.trans_type, '\001', "交易类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_split_diff.name, '\001', "姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_split_diff.logical_card_no, '\001', "逻辑卡号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_split_diff.bf_amt, '\001', "备付金清算金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_split_diff.account_amt, '\001', "CNC记账金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_split_diff.error_amt, '\001', "应调整差额");

            /*参与对账标志*/
            pstrcopy(sdb_icps_ds_split_diff.is_check_flag, "1", sizeof(sdb_icps_ds_split_diff.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_SPLIT_DIFF", SD_ICPS_WB_DS_SPLIT_DIFF, NUMELE(SD_ICPS_WB_DS_SPLIT_DIFF),
                    &sdb_icps_ds_split_diff, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_ds_split_diff.busi_serial), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 委外催收借据级费用分摊明细表
 */
int ffunc_parse_wbank_file_to_db_ds_dca_commission(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_DCA_COMMISSION WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_dca_commission, 0x00, sizeof(sdb_icps_ds_dca_commission));
            pstrcopy(sdb_icps_ds_dca_commission.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_ds_dca_commission.busi_date)); /*业务日期*/
            sdb_icps_ds_dca_commission.file_order = rcdCnt;

            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_dca_commission.out_amt, '\001', "委外金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_dca_commission.out_prin, '\001', "委外本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_dca_commission.out_interest, '\001', "委外利息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_dca_commission.out_penatly, '\001', "委外罚息");
            ICPS_WB_GET_INTEGER_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_dca_commission.out_due_days, '\001', "委外逾期天数");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_dca_commission.out_age_cd, '\001', "委外逾期时段");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_dca_commission.repay_amt, '\001', "还款金额");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_dca_commission.commision_ratio, '\001', "委外费率");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_dca_commission.bank_group_id, '\001', "银团编号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_dca_commission.bank_proportion, '\001', "银团比例");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_dca_commission.out_expense, '\001', "委外费用");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_ds_dca_commission.name, '\001', "名字");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_ds_dca_commission.logical_card_no, '\001', "卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_ds_dca_commission.cust_id, '\001', "客户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_ds_dca_commission.acct_no, '\001', "账户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_ds_dca_commission.loan_receipt_nbr, '\001', "借据号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_ds_dca_commission.bn, '\001', "银行号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 18, sdb_icps_ds_dca_commission.partition_date, '\001', "分区日期");

            /*参与对账标志*/
            pstrcopy(sdb_icps_ds_dca_commission.is_check_flag, "1", sizeof(sdb_icps_ds_dca_commission.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_DCA_COMMISSION", SD_ICPS_WB_DS_DCA_COMMISSION, NUMELE(SD_ICPS_WB_DS_DCA_COMMISSION),
                    &sdb_icps_ds_dca_commission, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败", rcdCnt), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 待核销借据与已核销借据差异表
 */
int ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_diff(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_DIFF_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_diff_list, 0x00, sizeof(sdb_icps_ds_diff_list));
            pstrcopy(sdb_icps_ds_diff_list.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_ds_diff_list.busi_date)); /*业务日期*/
            sdb_icps_ds_diff_list.file_order = rcdCnt;

            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_diff_list.id_num, '\001', "证件号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_diff_list.id_type, '\001', "证件类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_diff_list.cust_id, '\001', "客户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_diff_list.product_code, '\001', "产品号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_diff_list.acct_no, '\001', "账号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_diff_list.acct_type, '\001', "账户类型");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_diff_list.logical_card_no, '\001', "卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_diff_list.ref_nbr, '\001', "参考号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_diff_list.loan_init_prin, '\001', "本金");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_diff_list.bank_group_id, '\001', "银团号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_diff_list.writeoff_proc_status, '\001', "核销状态");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_ds_diff_list.writeoff_proc_desc, '\001', "未核销原因");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 13, sdb_icps_ds_diff_list.product_attr, '\001', "产品属性");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_ds_diff_list.name, '\001', "姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_ds_diff_list.writeoff_date, '\001', "核销日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 16, sdb_icps_ds_diff_list.bank_no, '\001', "银行号");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 17, sdb_icps_ds_diff_list.bank_proportion, '\001', "银团比例");

            /*参与对账标志*/
            pstrcopy(sdb_icps_ds_diff_list.is_check_flag, "1", sizeof(sdb_icps_ds_diff_list.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_DIFF_LIST", SD_ICPS_WB_DS_DIFF_LIST, NUMELE(SD_ICPS_WB_DS_DIFF_LIST),
                    &sdb_icps_ds_diff_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_ds_diff_list.cust_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 已核销借据清单表
 */
int ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_success(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_SUCC_LIST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_ds_succ_list, 0x00, sizeof(sdb_icps_ds_succ_list));
            pstrcopy(sdb_icps_ds_succ_list.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_ds_succ_list.busi_date)); /*业务日期*/
            sdb_icps_ds_succ_list.file_order = rcdCnt;

            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 1, sdb_icps_ds_succ_list.writeoff_date, '\001', "核销日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_ds_succ_list.name, '\001', "姓名");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_ds_succ_list.cust_id, '\001', "客户号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_ds_succ_list.bank_no, '\001', "银行号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_ds_succ_list.bank_group_id, '\001', "银团号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_ds_succ_list.product_cd, '\001', "产品号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_ds_succ_list.logical_card_no, '\001', "卡号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_ds_succ_list.ref_nbr, '\001', "参考号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_ds_succ_list.writeoff_proc_status, '\001', "核销状态");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 10, sdb_icps_ds_succ_list.loan_init_prin, '\001', "本金");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 11, sdb_icps_ds_succ_list.loan_intr_penalty, '\001', "利息罚息");
            ICPS_WB_GET_DOUBLE_BY_DIV(sFileLineGBK, 12, sdb_icps_ds_succ_list.bank_proportion, '\001', "银团比例");

            /*参与对账标志*/
            pstrcopy(sdb_icps_ds_succ_list.is_check_flag, "1", sizeof(sdb_icps_ds_succ_list.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_SUCC_LIST", SD_ICPS_WB_DS_SUCC_LIST, NUMELE(SD_ICPS_WB_DS_SUCC_LIST),
                    &sdb_icps_ds_succ_list, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_ds_succ_list.cust_id), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/**
 * 审批结果流水表
 */
int ffunc_parse_wbank_file_to_db_report_ds_approval_flow(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
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
        LOG(LM_STD, Fmtmsg("打开文件失败[%s]", list_file_name), "ERROR");
        return -404;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_WB_DS_APPROVAL_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    while (!feof(fp_list))
    {
        memset(sFileLineList, 0x00, sizeof(sFileLineList));
        fgets(sFileLineList, sizeof(sFileLineList), fp_list);
        chomp_CRLF(sFileLineList);

        trim(sFileLineList);
        /*空行*/
        if (sFileLineList[0] == '\0')
            continue;

        memset(check_file_name, 0x00, sizeof(check_file_name));
        snprintf(check_file_name, sizeof(check_file_name), "%s/%s", st_para_chkfileins.file_path, sFileLineList);
        LOG(LM_STD, Fmtmsg("check_file_name[%s]", check_file_name), "INFO");
        if ((fp_check = fopen(check_file_name, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", check_file_name), "ERROR");
            fclose(fp_list);
            return -1;
        }

        while (!feof(fp_check))
        {
            memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
            memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
            fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp_check);
            chomp_CRLF(sFileLineUTF8);
            /*空行*/
            if (sFileLineUTF8[0] == '\0')
                continue;
            iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
            rcdCnt++;
            transcCnt++;

            memset(&sdb_icps_wb_ds_approval_flow, 0x00, sizeof(sdb_icps_wb_ds_approval_flow));
            pstrcopy(sdb_icps_wb_ds_approval_flow.busi_date, st_para_chkfileins.busi_date,
                    sizeof(sdb_icps_wb_ds_approval_flow.busi_date)); /*业务日期*/
            sdb_icps_wb_ds_approval_flow.file_order = rcdCnt;

            ICPS_WB_GET_DATE_BY_DIV(sFileLineGBK, 1, sdb_icps_wb_ds_approval_flow.partition_date, '\001', "分区日期");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_wb_ds_approval_flow.busi_no, '\001', "流水号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_wb_ds_approval_flow.bank_no, '\001', "银行号");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_wb_ds_approval_flow.final_ret, '\001', "最终审批结果  ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_wb_ds_approval_flow.ours_approval_ret, '\001', "合作行审批结果 ");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_wb_ds_approval_flow.code_block, '\001', "拒绝码");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_wb_ds_approval_flow.is_first, '\001', "是否首借");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_wb_ds_approval_flow.outer_ret, '\001', "合作行机房审批结果");
            ICPS_WB_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_wb_ds_approval_flow.psz_ret, '\001', "Psz区审批结果");

            /*参与对账标志*/
            pstrcopy(sdb_icps_wb_ds_approval_flow.is_check_flag, "1", sizeof(sdb_icps_wb_ds_approval_flow.is_check_flag));
            /*插入数据库*/
            memset(sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = APP_DBInsert("ICPS_WB_DS_APPROVAL_FLOW", SD_ICPS_WB_DS_APPROVAL_FLOW, NUMELE(SD_ICPS_WB_DS_APPROVAL_FLOW),
                    &sdb_icps_wb_ds_approval_flow, sErrmsg);
            if (iRet < 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
                LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_wb_ds_approval_flow.busi_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

int ffunc_parse_wbank_file_to_db(HXMLTREE lXmlhandle, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int fileins_status = -1;

    if (0 == strcmp(st_para_chkfileins.file_type, "tm_account"))
    {
        /*账户信息表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_account(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_bank_cost"))
    {
        /*存款核心记账流水表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_auth_bank_cost(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_card"))
    {
        /*逻辑卡表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_card(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_gl_bal"))
    {
        /*总账会计科目表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_gl_bal(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_plan"))
    {
        /*信用计划表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_plan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_app_main"))
    {
        /*申请主表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_app_main(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_app_prim_applicant_info"))
    {
        /*主卡申请人信息表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_app_prim_applicant_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_customer"))
    {
        /*客户信息表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_customer(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tt_txn_post"))
    {
        /*当日入账交易表*/
        iRet = ffunc_parse_wbank_file_to_db_tt_txn_post(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_txn_reject"))
    {
        /*挂账交易历史表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_txn_reject(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan"))
    {
        /*分期信息表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_schedule"))
    {
        /*贷款分配表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_schedule(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_accounting_flow"))
    {
        /*会计分录日报表*/
        iRet = ffunc_parse_wbank_file_to_db_ds_accounting_flow(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_cust_limit_o"))
    {
        /*自定义额度信息表-授权*/
        iRet = ffunc_parse_wbank_file_to_db_tm_cust_limit_o(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_auth_hst"))
    {
        /*授权交易历史*/
        iRet = ffunc_parse_wbank_file_to_db_tm_auth_hst(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_im_info"))
    {
        /*客户即时通讯信息表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_im_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_receipt_list"))
    {
        /*还款借据清单表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan_receipt_list(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_receipt_list_hst"))
    {
        /*还款借据清单表历史*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan_receipt_list_hst(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_psb_personal_info"))
    {
        /*身份信息*/
        iRet = ffunc_parse_wbank_file_to_db_tm_psb_personal_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_tot"))
    {
        /*备付金资金清算汇总*/
        iRet = ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_tot(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_detail"))
    {
        /*备付金资金清算明细（分类汇总）*/
        iRet = ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "rrs_bdm_udf_clear_other_detail"))
    {
        /*备付金其他款项资金明细（分类汇总）*/
        iRet = ffunc_parse_wbank_file_to_db_rrs_bdm_udf_clear_other_detail(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_coll_rec"))
    {
        /*催收记录表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_coll_rec(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_loan_vms"))
    {
        /*借据纳税加工表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_loan_vms(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "tm_free_coupons_info"))
    {
        /*免息券信息表*/
        iRet = ffunc_parse_wbank_file_to_db_tm_free_coupons_info(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_split_diff"))
    {
        /*银团尾差调整表*/
        iRet = ffunc_parse_wbank_file_to_db_ds_split_diff(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_dca_commission"))
    {
        /*委外催收借据级费用分摊明细表*/
        iRet = ffunc_parse_wbank_file_to_db_ds_dca_commission(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_loan_writeoff_list_diff"))
    {
        /*待核销借据与已核销借据差异表*/
        iRet = ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_diff(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "ds_loan_writeoff_list_success"))
    {
        /*已核销借据清单表*/
        iRet = ffunc_parse_wbank_file_to_db_ds_loan_writeoff_list_success(lXmlhandle, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "report_ds_approval_flow"))
    {
        /*审批结果流水表*/
        iRet = ffunc_parse_wbank_file_to_db_report_ds_approval_flow(lXmlhandle, st_para_chkfileins);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("文件类型错误！"), "ERROR");
        return -2;
    }

    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("目前文件入库状态[%d]", fileins_status), "INFO")

    if (9 == fileins_status) /*初始*/
    {
        if (0 == iRet) /*成功*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*成功*/
        else if (-404 == iRet) /*无文件*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "9") /*初始*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "2") /*失败*/
    }
    else if (0 == fileins_status) /*成功*/
    {
        if (0 == iRet) /*成功*/
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "0") /*成功*/
        else
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*部分成功*/
    }
    else if (2 == fileins_status) /*失败*/
    {
        if (0 == iRet || -404 == iRet)
            COMP_SOFTSETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, "1") /*部分成功*/
    }
    COMP_SOFTGETXML(XMLNM_ICPS_REQ_FILEINS_STATUS, sBuf);
    fileins_status = atoi(trim(sBuf));
    LOG(LM_STD, Fmtmsg("本文件入库后状态[%d]", fileins_status), "INFO")
    iRet = ffunc_upd_file_info(st_para_chkfileins.busi_date, st_para_chkfileins.busi_no, st_para_chkfileins.file_type, iRet);

    return iRet;
}

int ffunc_init_wbank_file_info(HXMLTREE lXmlhandle, PARA_FILEINFOINIT st_para_fileinfoinit)
{
    int iRet;

    /*账户信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_account");
    /*存款核心记账流水表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_bank_cost");
    /*逻辑卡表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_card");
    /*总账会计科目表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_gl_bal");
    /*信用计划表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_plan");
    /*申请主表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_main");
    /*主卡申请人信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_app_prim_applicant_info");
    /*客户信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_customer");
    /*当日入账交易表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tt_txn_post");
    /*挂账交易历史表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_txn_reject");
    /*分期信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan");
    /*贷款分配表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_schedule");
    /*会计分录日报表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_accounting_flow");
    /*自定义额度信息表-授权*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_cust_limit_o");
    /*授权交易历史*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_auth_hst");
    /*客户即时通讯信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_im_info");
    /*还款借据清单表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_receipt_list");
    /*还款借据清单表历史*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_receipt_list_hst");
    /*身份信息*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_psb_personal_info");
    /*备付金资金清算汇总*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_tot");
    /*备付金资金清算明细（分类汇总）*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_detail");
    /*备付金其他款项资金明细（分类汇总*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "rrs_bdm_udf_clear_other_detail");
    /*催收记录表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_coll_rec");
    /*借据纳税加工表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_loan_vms");
    /*免息券信息表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "tm_free_coupons_info");
    /*银团尾差调整表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_split_diff");
    /*委外催收借据级费用分摊明细表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_dca_commission");
    /*待核销借据与已核销借据差异表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_loan_writeoff_list_diff");
    /*已核销借据清单表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "ds_loan_writeoff_list_success");
    /*审批结果流水表*/
    iRet = ffunc_ins_file_info(st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no, "report_ds_approval_flow");
    return 0;
}
