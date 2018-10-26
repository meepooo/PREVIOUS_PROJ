#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>

/*
 * 客户信息文件
 */
int ffunc_parse_jintiao_file_to_db_cus(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_CUS sdb_icps_jt_cus;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_CUS WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*空行*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jt_cus, 0x00, sizeof(sdb_icps_jt_cus));
        //pstrcopy(sdb_icps_jt_cus.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_cus.busi_date)); /*业务日期*/
        sdb_icps_jt_cus.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.busi_date, "@!@", "业务日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.customer_code, "@!@", "客户编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.customer_name, "@!@", "客户姓名");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.gender, "@!@", "客户性别");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.brith_date, "@!@", "出生日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.resident_flag, "@!@", "居民标志");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.customer_status, "@!@", "客户状态");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.border_in_out_flag, "@!@", "境内境外标志");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.id_type, "@!@", "证件类型");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.id_num, "@!@", "证件号码");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.mobile_no, "@!@", "手机号码");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.addr, "@!@", "通讯地址");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.bank_name, "@!@", "绑定银行卡行名");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cus.bank_acct, "@!@", "绑定银行卡卡号");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jt_cus.is_check_flag, "1", sizeof(sdb_icps_jt_cus.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_CUS", SD_ICPS_JT_CUS, NUMELE(SD_ICPS_JT_CUS), &sdb_icps_jt_cus, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jt_cus.customer_code), "ERROR");
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
 * 授信额度信息文件
 */
int ffunc_parse_jintiao_file_to_db_cuscredit(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_CUSCREDIT sdb_icps_jt_cuscredit;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_CUSCREDIT WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*空行*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jt_cuscredit, 0x00, sizeof(sdb_icps_jt_cuscredit));
        //pstrcopy(sdb_icps_jt_cuscredit.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_cuscredit.busi_date)); /*业务日期*/
        sdb_icps_jt_cuscredit.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.busi_date, "@!@", "业务日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.customer_code, "@!@", "客户编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.product_code, "@!@", "产品编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.quota_code, "@!@", "额度编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.currency, "@!@", "币种");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.cycle_quota_flag, "@!@", "循环额度标志");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.start_date, "@!@", "授信生效起始日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.end_date, "@!@", "授信到期日");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.quota, "@!@", "授信额度");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.limit, "@!@", "授信期限");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.nouse_quota, "@!@", "未动拨授信额度");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.tmp_quota_flag, "@!@", "是否临时额度");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_cuscredit.auth_status, "@!@", "授信状态");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jt_cuscredit.is_check_flag, "1", sizeof(sdb_icps_jt_cuscredit.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_CUSCREDIT", SD_ICPS_JT_CUSCREDIT, NUMELE(SD_ICPS_JT_CUSCREDIT), &sdb_icps_jt_cuscredit,
                sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jt_cuscredit.customer_code), "ERROR");
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
 * 调额信息文件
 */
int ffunc_parse_jintiao_file_to_db_quotaadjust(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_QUOTAADJUST sdb_icps_jt_quotaadjust;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_QUOTAADJUST WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*空行*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jt_quotaadjust, 0x00, sizeof(sdb_icps_jt_quotaadjust));
        pstrcopy(sdb_icps_jt_quotaadjust.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_quotaadjust.busi_date)); /*业务日期*/
        sdb_icps_jt_quotaadjust.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.customer_code, "@!@", "客户编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.product_code, "@!@", "产品编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.quota_code, "@!@", "额度编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_type, "@!@", "调额类型");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_mode, "@!@", "调额方式");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_quota, "@!@", "调额额度");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.before_adjust_quota, "@!@", "调额前授信额度");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.after_adjust_quota, "@!@", "调额后授信额度");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_cal_date, "@!@", "调额额度生成日");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_effective_date, "@!@", "调额额度生效日");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.adjust_serial, "@!@", "调额流水号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_quotaadjust.error_type, "@!@", "差错类型");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jt_quotaadjust.is_check_flag, "1", sizeof(sdb_icps_jt_quotaadjust.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_QUOTAADJUST", SD_ICPS_JT_QUOTAADJUST, NUMELE(SD_ICPS_JT_QUOTAADJUST),
                &sdb_icps_jt_quotaadjust, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jt_quotaadjust.customer_code), "ERROR");
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
 * 贷款借据信息表文件
 */
int ffunc_parse_jintiao_file_to_db_loan(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_LOAN sdb_icps_jt_loan;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_LOAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*空行*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jt_loan, 0x00, sizeof(sdb_icps_jt_loan));
        //pstrcopy(sdb_icps_jt_loan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_loan.busi_date)); /*业务日期*/
        sdb_icps_jt_loan.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.busi_date, "@!@", "业务日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.contract_no, "@!@", "合同号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.customer_code, "@!@", "客户编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.product_code, "@!@", "产品编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.quota_code, "@!@", "额度编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_code, "@!@", "贷款编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.currency, "@!@", "币种");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_status, "@!@", "贷款状态");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.encash_date, "@!@", "放款日期");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.encash_amt, "@!@", "放款金额");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.end_date, "@!@", "到期日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.use_area, "@!@", "贷款资金使用位置");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.prin_repay_frequency, "@!@", "本金还款频率");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_repay_frequency, "@!@", "利息还款频率");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.self_pay_amt, "@!@", "自主支付金额");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.entrusted_pay_amt, "@!@", "受托支付金额");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_flag, "@!@", "逾期标志");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_days, "@!@", "逾期天数");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_non_days, "@!@", "逾期宽限天数");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.prin_ovd_days, "@!@", "本金逾期日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_ovd_days, "@!@", "利息逾期日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.next_int_date, "@!@", "下一付息日");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.rate_type, "@!@", "利率类型");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_bal, "@!@", "贷款余额");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_loan_bal, "@!@", "逾期贷款余额");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.ovd_int, "@!@", "逾期利息");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.out_int_bal, "@!@", "表外欠息");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_flag, "@!@", "计息标志");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.accrued_int, "@!@", "应计利息");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.int_amt, "@!@", "当日利息");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.pnlt_amt, "@!@", "当日罚息");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.encash_acct, "@!@", "贷款入帐账号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.repay_acct, "@!@", "还款账号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.guarantee_type, "@!@", "贷款担保方式");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.repay_mode, "@!@", "还款方式");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_rate, "@!@", "借款利率");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.penalty_rate, "@!@", "违约金利率");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.loan_rate_type, "@!@", "借款利率类型");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_loan.penalty_rate_type, "@!@", "违约金利率类型");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jt_loan.is_check_flag, "1", sizeof(sdb_icps_jt_loan.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_LOAN", SD_ICPS_JT_LOAN, NUMELE(SD_ICPS_JT_LOAN), &sdb_icps_jt_loan, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jt_loan.customer_code), "ERROR");
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
 * 贷款还款计划信息文件
 */
int ffunc_parse_jintiao_file_to_db_plan(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_PLAN sdb_icps_jt_plan;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_PLAN WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*空行*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jt_plan, 0x00, sizeof(sdb_icps_jt_plan));
        //pstrcopy(sdb_icps_jt_plan.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_plan.busi_date)); /*业务日期*/
        sdb_icps_jt_plan.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.busi_date, "@!@", "业务日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.contract_no, "@!@", "合同号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.product_code, "@!@", "产品编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.quota_code, "@!@", "额度编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.loan_code, "@!@", "贷款编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.term_no, "@!@", "分期单号");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.repay_order, "@!@", "还款期数");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.prin_end_date, "@!@", "本金到期日");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.prin_amt, "@!@", "本金");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.int_end_date, "@!@", "利息到期日");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.int_amt, "@!@", "利息");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.repay_terms, "@!@", "还款总期数");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_plan.pnlt_amt, "@!@", "罚息");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jt_plan.is_check_flag, "1", sizeof(sdb_icps_jt_plan.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_PLAN", SD_ICPS_JT_PLAN, NUMELE(SD_ICPS_JT_PLAN), &sdb_icps_jt_plan, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jt_plan.contract_no), "ERROR");
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
 * 贷款还款明细信息文件
 */
int ffunc_parse_jintiao_file_to_db_flow(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_FLOW sdb_icps_jt_flow;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_FLOW WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*空行*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jt_flow, 0x00, sizeof(sdb_icps_jt_flow));
        //pstrcopy(sdb_icps_jt_flow.busi_date, st_para_chkfileins.busi_date, sizeof(sdb_icps_jt_flow.busi_date)); /*业务日期*/
        sdb_icps_jt_flow.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.busi_date, "@!@", "业务日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.contract_no, "@!@", "合同号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.product_code, "@!@", "产品编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.quota_code, "@!@", "额度编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.loan_code, "@!@", "贷款编号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.term_no, "@!@", "分期单号");
        ICPS_GET_DATE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_date, "@!@", "还款日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_serial, "@!@", "流水号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_mode, "@!@", "还款方式");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.curr_prin_amt, "@!@", "本期应还本金");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.prin_amt, "@!@", "本金金额");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.curr_int_amt, "@!@", "本期应还利息");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.int_amt, "@!@", "利息金额");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.curr_other_amt, "@!@", "本期应还其他金额");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.pnlt_amt, "@!@", "罚息金额");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_order, "@!@", "还款期数");
        ICPS_GET_INTEGER_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.unclear_terms, "@!@", "剩余还款期数");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_flow.repay_amt_type, "@!@", "还款类型");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jt_flow.is_check_flag, "1", sizeof(sdb_icps_jt_flow.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_FLOW", SD_ICPS_JT_FLOW, NUMELE(SD_ICPS_JT_FLOW), &sdb_icps_jt_flow, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jt_flow.contract_no), "ERROR");
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
 * 兴业资金流水文件
 */
int ffunc_parse_jintiao_file_to_db_fund_detail(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{

    int iRet = -1;
    char sBuf[255];
    int rcdCnt = 0; /*明细记录笔数*/
    int transcCnt = 0; /*事务笔数*/
    char sFileLine[1024], *pLinePointer;
    char sSqlStr[1024];
    char sErrmsg[256];

    ICPS_JT_FUND_DETAIL sdb_icps_jt_fund_detail;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }
    DCIBegin();
    memset(sSqlStr, 0x00, sizeof(sSqlStr));
    sprintf(sSqlStr, " DELETE FROM ICPS_JT_FUND_DETAIL WHERE BUSI_DATE='%s'", st_para_chkfileins.busi_date);
    LOG(LM_STD, Fmtmsg("删除原始对账记录[%s]", sSqlStr), "DEBUG");
    iRet = DCIExecuteDirect(sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    /*读取文件*/
    while (!feof(fp))
    {
        memset(sFileLine, 0, sizeof(sFileLine));
        fgets(sFileLine, sizeof(sFileLine), fp);
        chomp_CRLF(sFileLine);

        /*空行*/
        if (sFileLine[0] == '\0')
            continue;

        rcdCnt++;
        transcCnt++;

        pLinePointer = sFileLine;

        /*解析文件内容到表结构体*/
        memset(&sdb_icps_jt_fund_detail, 0x00, sizeof(sdb_icps_jt_fund_detail));
        sdb_icps_jt_fund_detail.file_order = rcdCnt;

        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.trans_time, "@!@", "交易时间");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.sys_date, "@!@", "系统日期");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.acct_direction, "@!@", "收支方向");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.trans_amt, "@!@", "交易金额");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.summary_code, "@!@", "摘要代码");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.summary, "@!@", "中文摘要");
        ICPS_GET_DOUBLE_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.acct_bal, "@!@", "账户余额");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.currency, "@!@", "货币号");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.peer_acct, "@!@", "对方账户");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.peer_acct_name, "@!@", "对方账户户名");
        ICPS_GET_STRING_BY_MULTDIV(&pLinePointer, sdb_icps_jt_fund_detail.remarks, "@!@", "备注");

        /*参与对账标志*/
        pstrcopy(sdb_icps_jt_fund_detail.is_check_flag, "1", sizeof(sdb_icps_jt_fund_detail.is_check_flag));

        /*插入数据库*/
        memset(sErrmsg, 0x00, sizeof(sErrmsg));
        iRet = APP_DBInsert("ICPS_JT_FUND_DETAIL", SD_ICPS_JT_FUND_DETAIL, NUMELE(SD_ICPS_JT_FUND_DETAIL),
                &sdb_icps_jt_fund_detail, sErrmsg);
        if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
            LOG(LM_STD, Fmtmsg("第[%d]条记录插入失败['%s']", rcdCnt, sdb_icps_jt_fund_detail.peer_acct), "ERROR");
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

int ffunc_parse_jintiao_file_to_db(HXMLTREE lXmlhandle, FILE* fp, PARA_CHKFILEINS st_para_chkfileins)
{
    int iRet = -1;

    if (fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("文件句柄为空，错误！"), "ERROR");
        return -1;
    }

    if (0 == strcmp(st_para_chkfileins.file_type, "loan_total"))
    {
        /*总账文件*/
        iRet = ffunc_parse_jintiao_file_to_db_loan_total(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "cus"))
    {
        /*客户信息文件*/
        iRet = ffunc_parse_jintiao_file_to_db_cus(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "cuscredit"))
    {
        /*授信额度信息文件*/
        iRet = ffunc_parse_jintiao_file_to_db_cuscredit(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "quotaadjust"))
    {
        /*调额信息文件*/
        iRet = ffunc_parse_jintiao_file_to_db_quotaadjust(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "loan"))
    {
        /*贷款借据信息文件*/
        iRet = ffunc_parse_jintiao_file_to_db_loan(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "plan"))
    {
        /*贷款还款计划信息文件*/
        iRet = ffunc_parse_jintiao_file_to_db_plan(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "flow"))
    {
        /*贷款还款明细信息文件*/
        iRet = ffunc_parse_jintiao_file_to_db_flow(lXmlhandle, fp, st_para_chkfileins);
    }
    else if (0 == strcmp(st_para_chkfileins.file_type, "fund_detail"))
    {
        /*兴业资金流水文件*/
        iRet = ffunc_parse_jintiao_file_to_db_fund_detail(lXmlhandle, fp, st_para_chkfileins);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("文件类型错误！"), "ERROR");
        return -2;
    }

    return iRet;
}
