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
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }

    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_TOTAL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    memset(&sdb_icps_jb_total, 0x00, sizeof(sdb_icps_jb_total));
    pstrcopy(sdb_icps_jb_total.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_total.busi_date)); /*业务日期*/

    /*读取文件*/
    /*去掉第一行*/
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);

    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_int_amt, "实还正常利息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_to_accrued_ovd_prin_amt, "逾期本金（非应计）转逾期本金（应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_to_accrued_prin_amt, "正常本金（非应计）转正常本金（应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_non_accrued_ovd_prin_amt, "实还逾期本金（非应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_int_amt, "实还正常利息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_to_non_prin_amt, "正常本金（应计）转正常本金（非应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_to_non_ovd_prin_amt, "逾期本金（应计）转逾期本金（非应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_prin_amt, "实还正常本金（应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_non_accrued_prin_amt, "实还正常本金（非应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_ovd_int_amt, "逾期利息（表内）转逾期利息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_int_amt, "正常利息（表内）转正常利息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_in_ovd_int_amt, "实还逾期利息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_ovd_int_amt, "实还逾期利息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.encash_amt, "当天贷款发放金额");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_ovd_int_pnlt_amt, "短期逾期90天以内（含）贷款计提每日逾期利息罚息");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_accrued_ovd_int_pnlt_amt, "短期逾期90天以上贷款计提每日逾期利息罚息");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.prin_to_ovd_prin_amt, "正常本金转逾期本金");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.int_to_ovd_int_amt, "正常利息转逾期利息");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_accrued_int_amt, "短期逾期90天以上贷款计提每日利息");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_in_ovd_int_pnlt_int_amt, "实还逾期利息罚息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_ovd_int_pnlt_int_amt, "实还逾期利息罚息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_int_amt, "短期正常/逾期90天以内（含）贷款计提每日利息");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_ovd_int_amt, "逾期利息（表外）转逾期利息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_int_amt, "正常利息（表外）转正常利息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.accrued_ovd_prin_pnlt_amt, "短期逾期90天以内（含）贷款计提每日逾期本金罚息");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.non_accrued_ovd_prin_pnlt_amt, "短期逾期90天以上贷款计提每日逾期本金罚息");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_out_ovd_prin_pnlt_int_amt, "实还逾期本金罚息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_in_ovd_prin_pnlt_int_amt, "实还逾期本金罚息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_ovd_prin_pnlt_amt, "逾期本金罚息（表外）转逾本金罚息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.out_to_in_ovd_int_pnlt_amt, "逾期利息罚息（表外）转逾期利息罚息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_ovd_int_pnlt_amt, "逾期利息罚息（表内）转逾期利息罚息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.in_to_out_ovd_prin_pnlt_amt, "逾期本金罚息（表内）转逾期本金罚息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.paid_accrued_ovd_prin_amt, "实还逾期本金（应计）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.withhold_amt, "当天网商备付金代扣金额");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.refund_amt, "当天退回网商备付金金额");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_int_amt, "减免正常利息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_int_amt, "减免正常利息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_ovd_int_amt, "减免逾期利息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_ovd_int_amt, "减免逾期利息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_ovd_prin_pnlt_int_amt, "减免逾期本金罚息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_ovd_prin_pnlt_int_amt, "减免逾期本金罚息（表外）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_in_ovd_int_pnlt_int_amt, "减免逾期利息罚息（表内）");
    ICPS_GET_MONEY_FROM_TOTALFILE_JB(fp, sdb_icps_jb_total.xpt_out_ovd_int_pnlt_int_amt, "减免逾期利息罚息（表外）");

    /*插入数据库*/
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = APP_DBInsert("ICPS_JB_TOTAL", SD_ICPS_JB_TOTAL, NUMELE(SD_ICPS_JB_TOTAL), &sdb_icps_jb_total, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
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
 * 在途支用明细文件
 */
int ffunc_parse_jiebei_file_to_db_lending_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_LENDING_DETAIL sdb_icps_jb_lending_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LENDING_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_lending_detail, 0x00, sizeof(sdb_icps_jb_lending_detail));
        pstrcopy(sdb_icps_jb_lending_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_lending_detail.busi_date)); /*业务日期*/
        sdb_icps_jb_lending_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_lending_detail.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_lending_detail.fund_seq_no, ',', "放款资金流水号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_lending_detail.third_product_code, ',', "产品码");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_lending_detail.name, ',', "客户真实姓名");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_lending_detail.id_type, ',', "证件类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_lending_detail.id_num, ',', "证件号码");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_lending_detail.loan_status, ',', "贷款状态");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_lending_detail.loan_use, ',', "贷款用途");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_lending_detail.use_area, ',', "贷款资金使用位置");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_lending_detail.apply_date, ',', "申请支用时间");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_lending_detail.encash_date, ',', "放款日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_lending_detail.currency, ',', "币种");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_lending_detail.encash_amt, ',', "放款金额");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_lending_detail.start_date, ',', "贷款起息日");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_lending_detail.end_date, ',', "贷款到期日");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_lending_detail.total_terms, ',', "贷款期次数");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_lending_detail.repay_mode, ',', "还款方式");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_jb_lending_detail.grace_day, ',', "宽限期天数");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_jb_lending_detail.rate_type, ',', "利率类型");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_jb_lending_detail.day_rate, ',', "贷款日利率");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_jb_lending_detail.prin_repay_frequency, ',', "本金还款频率");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_jb_lending_detail.int_repay_frequency, ',', "利息还款频率");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_jb_lending_detail.guarantee_type, ',', "担保类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_jb_lending_detail.credit_no, ',', "授信编号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_jb_lending_detail.encash_acct_type, ',', "放款帐号类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_jb_lending_detail.encash_acct, ',', "放款帐号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_jb_lending_detail.repay_acct_type, ',', "还款帐号类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_jb_lending_detail.repay_acct, ',', "还款帐号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_jb_lending_detail.loan_apply_no, ',', "贷款申请单号");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_lending_detail.is_check_flag, "1", sizeof(sdb_icps_jb_lending_detail.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LENDING_DETAIL", SD_ICPS_JB_LENDING_DETAIL, NUMELE(SD_ICPS_JB_LENDING_DETAIL),
                &sdb_icps_jb_lending_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_jb_lending_detail.contract_no,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 放款（借据）明细文件入库
 */
int ffunc_parse_jiebei_file_to_db_loan_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];
    ICPS_JB_LOAN_DETAIL sdb_icps_jb_loan_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LOAN_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_loan_detail, 0x00, sizeof(sdb_icps_jb_loan_detail));
        pstrcopy(sdb_icps_jb_loan_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_loan_detail.busi_date)); /*业务日期*/
        sdb_icps_jb_loan_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_loan_detail.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_loan_detail.fund_seq_no, ',', "放款资金流水号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_loan_detail.third_product_code, ',', "产品码");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_loan_detail.name, ',', "客户真实姓名");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_loan_detail.id_type, ',', "证件类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_loan_detail.id_num, ',', "证件号码");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_loan_detail.loan_status, ',', "贷款状态");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_loan_detail.loan_use, ',', "贷款用途");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_loan_detail.use_area, ',', "贷款资金使用位置");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_loan_detail.apply_date, ',', "申请支用时间");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_loan_detail.encash_date, ',', "放款日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_loan_detail.currency, ',', "币种");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_loan_detail.encash_amt, ',', "放款金额");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_loan_detail.start_date, ',', "贷款起息日");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_loan_detail.end_date, ',', "贷款到期日");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_loan_detail.total_terms, ',', "贷款期次数");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_loan_detail.repay_mode, ',', "还款方式");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 18, sdb_icps_jb_loan_detail.grace_day, ',', "宽限期天数");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 19, sdb_icps_jb_loan_detail.rate_type, ',', "利率类型");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 20, sdb_icps_jb_loan_detail.day_rate, ',', "贷款日利率");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 21, sdb_icps_jb_loan_detail.prin_repay_frequency, ',', "本金还款频率");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 22, sdb_icps_jb_loan_detail.int_repay_frequency, ',', "利息还款频率");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 23, sdb_icps_jb_loan_detail.guarantee_type, ',', "担保类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 24, sdb_icps_jb_loan_detail.credit_no, ',', "授信编号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 25, sdb_icps_jb_loan_detail.encash_acct_type, ',', "放款帐号类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 26, sdb_icps_jb_loan_detail.encash_acct, ',', "放款帐号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 27, sdb_icps_jb_loan_detail.repay_acct_type, ',', "还款帐号类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 28, sdb_icps_jb_loan_detail.repay_acct, ',', "还款帐号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 29, sdb_icps_jb_loan_detail.loan_apply_no, ',', "贷款申请单号");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_loan_detail.is_check_flag, "1", sizeof(sdb_icps_jb_loan_detail.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LOAN_DETAIL", SD_ICPS_JB_LOAN_DETAIL, NUMELE(SD_ICPS_JB_LOAN_DETAIL), &sdb_icps_jb_loan_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_jb_loan_detail.contract_no, sdb_icps_jb_loan_detail.fund_seq_no),
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 放款（分期）明细文件
 */
int ffunc_parse_jiebei_file_to_db_repay_plan(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_REPAY_PLAN sdb_icps_jb_repay_plan;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_REPAY_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_repay_plan, 0x00, sizeof(sdb_icps_jb_repay_plan));
        pstrcopy(sdb_icps_jb_repay_plan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_repay_plan.busi_date)); /*业务日期*/
        sdb_icps_jb_repay_plan.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_repay_plan.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_repay_plan.term_no, ',', "期次号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_repay_plan.start_date, ',', "分期开始日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_repay_plan.end_date, ',', "分期结束日期");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_repay_plan.prin_amt, ',', "本金金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_repay_plan.int_amt, ',', "初始利息匡算金额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_repay_plan.is_check_flag, "1", sizeof(sdb_icps_jb_repay_plan.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_REPAY_PLAN", SD_ICPS_JB_REPAY_PLAN, NUMELE(SD_ICPS_JB_REPAY_PLAN), &sdb_icps_jb_repay_plan, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_jb_repay_plan.contract_no, sdb_icps_jb_repay_plan.term_no),
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 还款（借据）明细文件
 */
int ffunc_parse_jiebei_file_to_db_repay_loan_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_REPAY_LOAN_DETAIL sdb_icps_jb_repay_loan_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_REPAY_LOAN_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_repay_loan_detail, 0x00, sizeof(sdb_icps_jb_repay_loan_detail));
        pstrcopy(sdb_icps_jb_repay_loan_detail.busi_date, st_para_chkfileins.busi_date,
                sizeof(sdb_icps_jb_repay_loan_detail.busi_date)); /*业务日期*/
        sdb_icps_jb_repay_loan_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_repay_loan_detail.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_repay_loan_detail.repay_seq_no, ',', "还款流水号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_repay_loan_detail.fee_no, ',', "收费单号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_repay_loan_detail.withdraw_no, ',', "还款提现单号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_repay_loan_detail.repay_type, ',', "还款类型");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_repay_loan_detail.repay_date, ',', "还款日期");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_repay_loan_detail.curr_prin_bal, ',', "本次还款前的应收未收正常本金余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_repay_loan_detail.curr_ovd_prin_bal, ',', "本次还款前的应收未收逾期本金余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_repay_loan_detail.curr_int_bal, ',', "本次还款前的应收未收正常利息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_repay_loan_detail.curr_ovd_int_bal, ',', "本次还款前的应收未收逾期利息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_repay_loan_detail.curr_ovd_prin_pnlt_bal, ',', "本次还款前的应收未收逾期本金罚息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_repay_loan_detail.curr_ovd_int_pnlt_bal, ',', "本次还款前的应收未收逾期利息罚息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_repay_loan_detail.repay_amt, ',', "总金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_repay_loan_detail.paid_prin_amt, ',', "本次实还正常本金金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_repay_loan_detail.paid_ovd_prin_amt, ',', "本次实还逾期本金金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_repay_loan_detail.paid_int_amt, ',', "本次实还正常利息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_repay_loan_detail.paid_ovd_int_amt, ',', "本次实还逾期利息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 18, sdb_icps_jb_repay_loan_detail.paid_ovd_prin_pnlt_amt, ',', "本次实还逾期本金罚息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 19, sdb_icps_jb_repay_loan_detail.paid_ovd_int_pnlt_amt, ',', "本次实还逾期利息罚息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 20, sdb_icps_jb_repay_loan_detail.fee_amt, ',', "本次还款对应的平台服务费金额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_repay_loan_detail.is_check_flag, "1", sizeof(sdb_icps_jb_repay_loan_detail.is_check_flag));


        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_REPAY_LOAN_DETAIL", SD_ICPS_JB_REPAY_LOAN_DETAIL, NUMELE(SD_ICPS_JB_REPAY_LOAN_DETAIL),
                &sdb_icps_jb_repay_loan_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_jb_repay_loan_detail.contract_no,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 还款（分期）明细文件
 */
int ffunc_parse_jiebei_file_to_db_repay_instmnt_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_REPAY_INSTMNT_DETAIL sdb_icps_jb_repay_instmnt_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_REPAY_INSTMNT_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_repay_instmnt_detail, 0x00, sizeof(sdb_icps_jb_repay_instmnt_detail));
        pstrcopy(sdb_icps_jb_repay_instmnt_detail.busi_date, st_para_chkfileins.busi_date,
                sizeof(sdb_icps_jb_repay_instmnt_detail.busi_date)); /*业务日期*/
        sdb_icps_jb_repay_instmnt_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_repay_instmnt_detail.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_repay_instmnt_detail.repay_seq_no, ',', "还款流水号");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_repay_instmnt_detail.term_no, ',', "期次号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_repay_instmnt_detail.repay_amt_type, ',', "还款金额类型");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_repay_instmnt_detail.repay_date, ',', "还款日期");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_repay_instmnt_detail.curr_prin_bal, ',', "本次还款前的应收未收本金");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_repay_instmnt_detail.curr_int_bal, ',', "本次还款前的应收未收利息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_repay_instmnt_detail.curr_ovd_prin_pnlt_bal, ',', "本次还款前的应收未收逾期本金罚息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_repay_instmnt_detail.curr_ovd_int_pnlt_bal, ',', "本次还款前的应收未收逾期利息罚息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_repay_instmnt_detail.repay_amt, ',', "本次实还总金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_repay_instmnt_detail.paid_prin_amt, ',', "本次实还本金金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_repay_instmnt_detail.paid_int_amt, ',', "本次实还利息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_repay_instmnt_detail.paid_ovd_prin_pnlt_amt, ',', "本次实还逾期本金罚息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_repay_instmnt_detail.paid_ovd_int_pnlt_amt, ',', "本次实还逾期利息罚息金额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_repay_instmnt_detail.is_check_flag, "1", sizeof(sdb_icps_jb_repay_instmnt_detail.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_REPAY_INSTMNT_DETAIL", SD_ICPS_JB_REPAY_INSTMNT_DETAIL, NUMELE(SD_ICPS_JB_REPAY_INSTMNT_DETAIL),
                &sdb_icps_jb_repay_instmnt_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_jb_repay_instmnt_detail.contract_no,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 减免（借据）明细文件
 */
int ffunc_parse_jiebei_file_to_db_xpt_loan_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_XPT_LOAN_DETAIL sdb_icps_jb_xpt_loan_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_XPT_LOAN_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_xpt_loan_detail, 0x00, sizeof(sdb_icps_jb_xpt_loan_detail));
        pstrcopy(sdb_icps_jb_xpt_loan_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_xpt_loan_detail.busi_date)); /*业务日期*/
        sdb_icps_jb_xpt_loan_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_xpt_loan_detail.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_xpt_loan_detail.xpt_seq_no, ',', "减免流水号");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_xpt_loan_detail.xpt_date, ',', "减免时间");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_xpt_loan_detail.curr_int_bal, ',', "本次还款前的应收未收正常利息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_xpt_loan_detail.curr_ovd_int_bal, ',', "本次还款前的应收未收逾期利息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_xpt_loan_detail.curr_ovd_prin_pnlt_bal, ',', "本次还款前的应收未收逾期本金罚息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_xpt_loan_detail.curr_ovd_int_pnlt_bal, ',', "本次还款前的应收未收逾期利息罚息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_xpt_loan_detail.xpt_amt, ',', "减免总金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_xpt_loan_detail.xpt_int_amt, ',', "本次减免正常利息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_xpt_loan_detail.xpt_ovd_int_amt, ',', "本次减免逾期利息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_xpt_loan_detail.xpt_ovd_prin_pnlt_amt, ',', "本次减免逾期本金罚息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_xpt_loan_detail.xpt_ovd_int_pnlt_amt, ',', "本次减免逾期利息罚息金额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_xpt_loan_detail.is_check_flag, "1", sizeof(sdb_icps_jb_xpt_loan_detail.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_XPT_LOAN_DETAIL", SD_ICPS_JB_XPT_LOAN_DETAIL, NUMELE(SD_ICPS_JB_XPT_LOAN_DETAIL),
                &sdb_icps_jb_xpt_loan_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_jb_xpt_loan_detail.contract_no,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 减免（分期）明细文件
 */
int ffunc_parse_jiebei_file_to_db_xpt_instmnt_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_XPT_INSTMNT_DETAIL sdb_icps_jb_xpt_instmnt_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_XPT_INSTMNT_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_xpt_instmnt_detail, 0x00, sizeof(sdb_icps_jb_xpt_instmnt_detail));
        pstrcopy(sdb_icps_jb_xpt_instmnt_detail.busi_date, st_para_chkfileins.busi_date,
                sizeof(sdb_icps_jb_xpt_instmnt_detail.busi_date)); /*业务日期*/
        sdb_icps_jb_xpt_instmnt_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_xpt_instmnt_detail.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_xpt_instmnt_detail.xpt_seq_no, ',', "减免流水号");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_xpt_instmnt_detail.term_no, ',', "期次号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_xpt_instmnt_detail.settle_date, ',', "减免会计日期");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_xpt_instmnt_detail.curr_int_bal, ',', "本次还款前的应收未收利息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_xpt_instmnt_detail.curr_ovd_prin_pnlt_bal, ',', "本次还款前的应收未收逾期本金罚息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_xpt_instmnt_detail.curr_ovd_int_pnlt_bal, ',', "本次还款前的应收未收逾期利息罚息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_xpt_instmnt_detail.xpt_amt, ',', "本次减免总金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_xpt_instmnt_detail.xpt_int_amt, ',', "本次减免利息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_xpt_instmnt_detail.xpt_ovd_prin_pnlt_amt, ',', "本次减免逾期本金罚息金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_xpt_instmnt_detail.xpt_ovd_int_pnlt_amt, ',', "本次减免逾期利息罚息金额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_xpt_instmnt_detail.is_check_flag, "1", sizeof(sdb_icps_jb_xpt_instmnt_detail.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_XPT_INSTMNT_DETAIL", SD_ICPS_JB_XPT_INSTMNT_DETAIL, NUMELE(SD_ICPS_JB_XPT_INSTMNT_DETAIL),
                &sdb_icps_jb_xpt_instmnt_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD,
                    Fmtmsg("第[%d]条记录插入失败['%s','%s']", rcdCnt, sdb_icps_jb_xpt_instmnt_detail.contract_no,
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 日初（借据）信息文件
 */
int ffunc_parse_jiebei_file_to_db_loan_init(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_LOAN_INIT sdb_icps_jb_loan_init;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LOAN_INIT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_loan_init, 0x00, sizeof(sdb_icps_jb_loan_init));
        pstrcopy(sdb_icps_jb_loan_init.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_loan_init.busi_date)); /*业务日期*/
        sdb_icps_jb_loan_init.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_loan_init.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_loan_init.settle_date, ',', "会计日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_loan_init.status, ',', "借据状态");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_loan_init.clear_date, ',', "结清日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_loan_init.asset_class, ',', "五级分类标识");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_loan_init.accrued_status, ',', "应计非应计标识");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_loan_init.next_repay_date, ',', "下一还款日期");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_loan_init.unclear_terms, ',', "未结清期数");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_loan_init.ovd_terms, ',', "逾期期次数");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_loan_init.prin_ovd_days, ',', "本金逾期天数");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_loan_init.int_ovd_days, ',', "利息逾期天数");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_loan_init.prin_bal, ',', "正常本金余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_loan_init.ovd_prin_bal, ',', "逾期本金余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_loan_init.int_bal, ',', "正常利息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_loan_init.ovd_int_bal, ',', "逾期利息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 16, sdb_icps_jb_loan_init.ovd_prin_pnlt_bal, ',', "逾期本金罚息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 17, sdb_icps_jb_loan_init.ovd_int_pnlt_bal, ',', "逾期利息罚息余额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_loan_init.is_check_flag, "1", sizeof(sdb_icps_jb_loan_init.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LOAN_INIT", SD_ICPS_JB_LOAN_INIT, NUMELE(SD_ICPS_JB_LOAN_INIT), &sdb_icps_jb_loan_init, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jb_loan_init.contract_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 日初（分期）信息文件
 */
int ffunc_parse_jiebei_file_to_db_instmnt_init(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_INSTMNT_INIT sdb_icps_jb_instmnt_init;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_INSTMNT_INIT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_instmnt_init, 0x00, sizeof(sdb_icps_jb_instmnt_init));
        pstrcopy(sdb_icps_jb_instmnt_init.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_instmnt_init.busi_date)); /*业务日期*/
        sdb_icps_jb_instmnt_init.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_instmnt_init.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_instmnt_init.settle_date, ',', "会计日期");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_instmnt_init.term_no, ',', "期次号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_instmnt_init.start_date, ',', "分期开始日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_instmnt_init.end_date, ',', "分期结束日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_instmnt_init.status, ',', "分期状态");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_instmnt_init.clear_date, ',', "结清日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_instmnt_init.prin_ovd_date, ',', "本金转逾期日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_instmnt_init.int_ovd_date, ',', "利息转逾期日期");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_instmnt_init.prin_ovd_days, ',', "本金逾期天数");
        ICPS_GET_INTEGER_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_instmnt_init.int_ovd_days, ',', "利息逾期天数");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 12, sdb_icps_jb_instmnt_init.prin_bal, ',', "本金余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 13, sdb_icps_jb_instmnt_init.int_bal, ',', "利息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 14, sdb_icps_jb_instmnt_init.ovd_prin_pnlt_bal, ',', "逾期本金罚息余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 15, sdb_icps_jb_instmnt_init.ovd_int_pnlt_bal, ',', "逾期利息罚息余额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_instmnt_init.is_check_flag, "1", sizeof(sdb_icps_jb_instmnt_init.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_INSTMNT_INIT", SD_ICPS_JB_INSTMNT_INIT, NUMELE(SD_ICPS_JB_INSTMNT_INIT), &sdb_icps_jb_instmnt_init,
                sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jb_instmnt_init.contract_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 利息计提明细文件
 */
int ffunc_parse_jiebei_file_to_db_loan_calc(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_LOAN_CALC sdb_icps_jb_loan_calc;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_LOAN_CALC WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_loan_calc, 0x00, sizeof(sdb_icps_jb_loan_calc));
        pstrcopy(sdb_icps_jb_loan_calc.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_loan_calc.busi_date)); /*业务日期*/
        sdb_icps_jb_loan_calc.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_loan_calc.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_loan_calc.calc_date, ',', "计息日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_loan_calc.accrued_status, ',', "应计非应计标识");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_loan_calc.prin_bal, ',', "正常本金余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_loan_calc.ovd_prin_bal, ',', "逾期本金余额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_loan_calc.ovd_int_bal, ',', "逾期利息余额");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_loan_calc.real_rate, ',', "贷款实际日利率");
        ICPS_GET_DOUBLE_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_loan_calc.pnlt_rate, ',', "贷款罚息日利率");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_loan_calc.int_amt, ',', "正常利息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_loan_calc.ovd_prin_pnlt_amt, ',', "逾期本金罚息");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 11, sdb_icps_jb_loan_calc.ovd_int_pnlt_amt, ',', "逾期利息罚息");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_loan_calc.is_check_flag, "1", sizeof(sdb_icps_jb_loan_calc.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_LOAN_CALC", SD_ICPS_JB_LOAN_CALC, NUMELE(SD_ICPS_JB_LOAN_CALC), &sdb_icps_jb_loan_calc,
                sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jb_loan_calc.contract_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 借据形态转移流水文件
 */
int ffunc_parse_jiebei_file_to_db_arg_status_change(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_ARG_STATUS_CHANGE sdb_icps_jb_arg_status_change;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_ARG_STATUS_CHANGE WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_arg_status_change, 0x00, sizeof(sdb_icps_jb_arg_status_change));
        pstrcopy(sdb_icps_jb_arg_status_change.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_arg_status_change.busi_date)); /*业务日期*/
        sdb_icps_jb_arg_status_change.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_arg_status_change.contract_no, ',', "借呗平台贷款合同号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_arg_status_change.settle_date, ',', "会计日期");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_arg_status_change.status_seq_no, ',', "状态变化流水号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_arg_status_change.event_code, ',', "事件码");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_arg_status_change.before_status, ',', "借据转移前状态");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_arg_status_change.after_status, ',', "借据转移后状态");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_arg_status_change.prin_amt, ',', "本金发生额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_arg_status_change.int_amt, ',', "利息发生额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 9, sdb_icps_jb_arg_status_change.ovd_prin_pnlt_amt, ',', "逾期本金罚息发生额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 10, sdb_icps_jb_arg_status_change.ovd_int_pnlt_amt, ',', "逾期利息罚息发生额");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_arg_status_change.is_check_flag, "1", sizeof(sdb_icps_jb_arg_status_change.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_ARG_STATUS_CHANGE", SD_ICPS_JB_ARG_STATUS_CHANGE, NUMELE(SD_ICPS_JB_ARG_STATUS_CHANGE),
                &sdb_icps_jb_arg_status_change, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jb_arg_status_change.contract_no), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

/*
 * 网商银行资金对账文件
 */
int ffunc_parse_jiebei_file_to_db_fund_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLineUTF8[1024], sFileLineGBK[1024];
    char *pUTF8 = sFileLineUTF8, *pGBK = sFileLineGBK;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JB_FUND_DETAIL sdb_icps_jb_fund_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JB_FUND_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    /*去掉第一行*/
    memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
    fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
    while (!feof(fp))
    {
        memset(sFileLineUTF8, 0, sizeof(sFileLineUTF8));
        memset(sFileLineGBK, 0, sizeof(sFileLineGBK));
        fgets(sFileLineUTF8, sizeof(sFileLineUTF8), fp);
        chomp_CRLF(sFileLineUTF8);

        /*空行*/
        if (sFileLineUTF8[0] == '\0')
            continue;
        iRet = code_convert("UTF-8", "GBK", pUTF8, sizeof(sFileLineUTF8), pGBK, sizeof(sFileLineGBK));
        rcdCnt++;
        transcCnt++;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jb_fund_detail, 0x00, sizeof(sdb_icps_jb_fund_detail));
        pstrcopy(sdb_icps_jb_fund_detail.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jb_fund_detail.busi_date)); /*业务日期*/
        sdb_icps_jb_fund_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 1, sdb_icps_jb_fund_detail.third_busi_serial, ',', "网商银行交易流水号");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 2, sdb_icps_jb_fund_detail.third_busi_type, ',', "业务操作");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 3, sdb_icps_jb_fund_detail.trans_amt, ',', "交易金额");
        ICPS_GET_MONEY_BY_DIV(sFileLineGBK, 4, sdb_icps_jb_fund_detail.trans_refund_amt, ',', "交易退款金额");
        ICPS_GET_DATE_TIME_BY_DIV(sFileLineGBK, 5, sdb_icps_jb_fund_detail.trans_dttm, ',', "交易时间");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 6, sdb_icps_jb_fund_detail.third_trans_name, ',', "交易名称");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 7, sdb_icps_jb_fund_detail.peer_org_name, ',', "对方机构名称");
        ICPS_GET_STRING_BY_DIV(sFileLineGBK, 8, sdb_icps_jb_fund_detail.trans_sub_detail, ',', "业务单号");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jb_fund_detail.is_check_flag, "1", sizeof(sdb_icps_jb_fund_detail.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JB_FUND_DETAIL", SD_ICPS_JB_FUND_DETAIL, NUMELE(SD_ICPS_JB_FUND_DETAIL), &sdb_icps_jb_fund_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jb_fund_detail.third_busi_serial), "ERROR");
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

    LOG(LM_STD, Fmtmsg("插入记录数[%d]", rcdCnt), "INFO")

    return 0;
}

int ffunc_parse_jiebei_file_to_db(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    if (0 == strcmp(st_para_chkfileins.file_type, "accounting"))
    {
        /*汇总记账文件*/
        iRet = ffunc_parse_jiebei_file_to_db_accounting(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "lending_detail"))
    {
        /*在途支用明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_lending_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan_detail"))
    {
        /*放款（借据）明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_loan_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "repay_plan"))
    {
        /*放款（分期）明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_repay_plan(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "repay_loan_detail"))
    {
        /*还款（借据）明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_repay_loan_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "repay_instmnt_detail"))
    {
        /*还款（分期）明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_repay_instmnt_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "exempt_loan_detail"))
    {
        /*减免（借据）明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_xpt_loan_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "exempt_instmnt_detail"))
    {
        /*减免（分期）明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_xpt_instmnt_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan_init"))
    {
        /*日初（借据）信息文件*/
        iRet = ffunc_parse_jiebei_file_to_db_loan_init(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "instmnt_init"))
    {
        /*日初（分期）信息文件*/
        iRet = ffunc_parse_jiebei_file_to_db_instmnt_init(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan_calc"))
    {
        /*利息计提明细文件*/
        iRet = ffunc_parse_jiebei_file_to_db_loan_calc(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "arg_status_change"))
    {
        /*借据形态转移流水文件*/
        iRet = ffunc_parse_jiebei_file_to_db_arg_status_change(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "fund_detail"))
    {
        /*网商银行资金对账文件*/
        iRet = ffunc_parse_jiebei_file_to_db_fund_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("文件类型错误！"), "ERROR");
        return -2;
    }

    return iRet;
}
