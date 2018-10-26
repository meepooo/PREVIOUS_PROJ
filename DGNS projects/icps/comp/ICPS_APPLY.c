#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include "../incl/cJSON.h"

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_APPLY_INSERT
组件名称:ICPS_APPLY_INSERT
组件功能: 登记授权申请流水表
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_APPLY_INSERT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_APPLY sdb_icps_apply;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_apply, 0, sizeof(sdb_icps_apply));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_BUSI_NO, sdb_icps_apply.busi_no, "业务编号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_NO, sdb_icps_apply.apply_no, "申请单号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_TYPE, sdb_icps_apply.id_type, "证件类型");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_NUM, sdb_icps_apply.id_num, "证件号码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_VALID_END_DATE, sdb_icps_apply.id_valid_end_date, "证件有效期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_NAME, sdb_icps_apply.name, "姓名");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_MOBILE_NO, sdb_icps_apply.mobile_no, "手机号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_AUTH_FLAG, sdb_icps_apply.auth_flag, "芝麻授权成功标识");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_HAS_ADMIT_FLAG, sdb_icps_apply.has_admit_flag, "之前是否有额度");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_DATE, sdb_icps_apply.apply_plt_date, "授信申请平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_SERIAL, sdb_icps_apply.apply_plt_serial, "授信申请平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_STATUS, sdb_icps_apply.apply_status, "授信申请状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CREDIT_NO, sdb_icps_apply.credit_no, "授信编号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_ADMIT_FLAG, sdb_icps_apply.info_admit_flag, "银行是否推荐准入");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_AMT, sdb_icps_apply.credit_amt, "推荐额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_RATE, sdb_icps_apply.credit_rate, "推荐利率");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_CODE, sdb_icps_apply.refuse_code, "拒绝码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_REASON, sdb_icps_apply.refuse_reason, "拒绝原因");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_DATE, sdb_icps_apply.info_plt_date, "银行初审平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_SERIAL, sdb_icps_apply.info_plt_serial, "银行初审平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_STATUS, sdb_icps_apply.info_status, "初审状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_ACCESS, sdb_icps_apply.third_access, "是否通过审批");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_REFUSE_REASON, sdb_icps_apply.third_refuse_reason, "审批不通过原因");
    ICPS_GETXMLNODE_MONEY(XMLNM_ICPS_APPLY_THIRD_AMT, sdb_icps_apply.third_amt, "审批额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_THIRD_RATE, sdb_icps_apply.third_rate, "审批基础利率");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_RISK_RATING, sdb_icps_apply.risk_rating, "风险评级");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_SOLVENCY_RATING, sdb_icps_apply.solvency_rating, "偿债能力评级");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CHANGE_RESULT_REASON, sdb_icps_apply.change_result_reason, "额度定价变更原因");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_FLAG, sdb_icps_apply.ack_admit_flag, "终审银行是否准入");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_MSG, sdb_icps_apply.ack_admit_msg, "准入原因");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_DATE, sdb_icps_apply.ack_plt_date, "终审平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_SERIAL, sdb_icps_apply.ack_plt_serial, "终审平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_STATUS, sdb_icps_apply.ack_status, "终审状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM1, sdb_icps_apply.extend_param1, "扩展1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM2, sdb_icps_apply.extend_param2, "扩展2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM3, sdb_icps_apply.extend_param3, "扩展3");

    iRet = APP_DBInsert("ICPS_APPLY", SD_ICPS_APPLY, NUMELE(SD_ICPS_APPLY), &sdb_icps_apply, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 提交事务 */
    if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:ICPS_APPLY_UPDATE
 组件名称:ICPS_APPLY_UPDATE
 组件功能: 更新流水表
 组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
 使用限制:
 程 序 员:
 发布日期:2009年12月11日
 修改日期:
 参数使用示例:
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

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_BUSI_NO, sdb_icps_apply.busi_no, "业务编号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_NO, sdb_icps_apply.apply_no, "申请单号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_TYPE, sdb_icps_apply.id_type, "证件类型");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_NUM, sdb_icps_apply.id_num, "证件号码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ID_VALID_END_DATE, sdb_icps_apply.id_valid_end_date, "证件有效期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_NAME, sdb_icps_apply.name, "姓名");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_MOBILE_NO, sdb_icps_apply.mobile_no, "手机号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_AUTH_FLAG, sdb_icps_apply.auth_flag, "芝麻授权成功标识");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_HAS_ADMIT_FLAG, sdb_icps_apply.has_admit_flag, "之前是否有额度");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_DATE, sdb_icps_apply.apply_plt_date, "授信申请平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_PLT_SERIAL, sdb_icps_apply.apply_plt_serial, "授信申请平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_APPLY_STATUS, sdb_icps_apply.apply_status, "授信申请状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CREDIT_NO, sdb_icps_apply.credit_no, "授信编号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_ADMIT_FLAG, sdb_icps_apply.info_admit_flag, "银行是否推荐准入");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_AMT, sdb_icps_apply.credit_amt, "推荐额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_CREDIT_RATE, sdb_icps_apply.credit_rate, "推荐利率");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_CODE, sdb_icps_apply.refuse_code, "拒绝码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_REFUSE_REASON, sdb_icps_apply.refuse_reason, "拒绝原因");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_DATE, sdb_icps_apply.info_plt_date, "银行初审平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_PLT_SERIAL, sdb_icps_apply.info_plt_serial, "银行初审平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_INFO_STATUS, sdb_icps_apply.info_status, "初审状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_ACCESS, sdb_icps_apply.third_access, "是否通过审批");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_THIRD_REFUSE_REASON, sdb_icps_apply.third_refuse_reason, "审批不通过原因");
    ICPS_GETXMLNODE_MONEY(XMLNM_ICPS_APPLY_THIRD_AMT, sdb_icps_apply.third_amt, "审批额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_APPLY_THIRD_RATE, sdb_icps_apply.third_rate, "审批基础利率");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_RISK_RATING, sdb_icps_apply.risk_rating, "风险评级");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_SOLVENCY_RATING, sdb_icps_apply.solvency_rating, "偿债能力评级");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_CHANGE_RESULT_REASON, sdb_icps_apply.change_result_reason, "额度定价变更原因");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_FLAG, sdb_icps_apply.ack_admit_flag, "终审银行是否准入");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_ADMIT_MSG, sdb_icps_apply.ack_admit_msg, "准入原因");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_DATE, sdb_icps_apply.ack_plt_date, "终审平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_PLT_SERIAL, sdb_icps_apply.ack_plt_serial, "终审平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_ACK_STATUS, sdb_icps_apply.ack_status, "终审状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM1, sdb_icps_apply.extend_param1, "扩展1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM2, sdb_icps_apply.extend_param2, "扩展2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_APPLY_EXTEND_PARAM3, sdb_icps_apply.extend_param3, "扩展3");

    snprintf(sSql_Where, sizeof(sSql_Where), " BUSI_NO='%s' AND APPLY_NO='%s'", sdb_icps_apply.busi_no, sdb_icps_apply.apply_no);

    iRet = APP_DBUpdate("ICPS_APPLY", SD_ICPS_APPLY, NUMELE(SD_ICPS_APPLY), &sdb_icps_apply, sSql_Where, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库更新操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    /* 提交事务 */
    if (DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库提交操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    if (iRet == 0)
    {
        LOG(LM_STD, Fmtmsg("更新操作无符合条件的记录[%s]", sSql_Where), "INFO")
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_NORECORD);
        return ICPS_COMPSTATUS_SQL_NORECORD;
    }

    fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_SUCC);
    return ICPS_COMPSTATUS_SQL_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:ICPS_APPLY_ZM_INFO_INS
 组件名称:ICPS_APPLY_ZM_INFO_INS
 组件功能: 登记芝麻信用信息
 组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
 使用限制:
 程 序 员:
 发布日期:2009年12月11日
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT ICPS_APPLY_ZM_INFO_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_ZM_CREDIT sdb_icps_zm_credit;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_zm_credit, 0, sizeof(sdb_icps_zm_credit));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_zm_credit.apply_no, "申请单号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_zm_credit.plt_date, "平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_zm_credit.plt_serial, "平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_ID_TYPE, sdb_icps_zm_credit.id_type, "证件类型");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_ID_NUM, sdb_icps_zm_credit.id_num, "证件号码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_COMPANY_NAME, sdb_icps_zm_credit.company_name, "所在公司");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_OCCUPATION, sdb_icps_zm_credit.occupation, "职业类型");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_HAVE_CAR_FLAG, sdb_icps_zm_credit.have_car_flag, "是否有车");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_HAVE_HOUSE_FLAG, sdb_icps_zm_credit.have_house_flag, "是否有房");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_AUTH_FIN_LAST_1M_CNT, sdb_icps_zm_credit.auth_fin_last_1m_cnt, "最近一个月主动查询金融机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_AUTH_FIN_LAST_3M_CNT, sdb_icps_zm_credit.auth_fin_last_3m_cnt, "最近三个月主动查询金融机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_AUTH_FIN_LAST_6M_CNT, sdb_icps_zm_credit.auth_fin_last_6m_cnt, "最近六个月主动查询金融机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_OVD_ORDER_CNT_6M, sdb_icps_zm_credit.ovd_order_cnt_6m, "最近六个月逾期总笔数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_ZMINFO_OVD_ORDER_AMT_6M, sdb_icps_zm_credit.ovd_order_amt_6m, "最近六个月逾期总金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_MOBILE_FIXED_DAYS, sdb_icps_zm_credit.mobile_fixed_days, "手机号稳定天数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_ADR_STABILITY_DAYS, sdb_icps_zm_credit.adr_stability_days, "地址稳定天数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_ZMINFO_LAST_6M_AVG_ASSET_TOTAL, sdb_icps_zm_credit.last_6m_avg_asset_total, "最近六个月流动资产日均值");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_ZMINFO_TOT_PAY_AMT_6M, sdb_icps_zm_credit.tot_pay_amt_6m, "最近六个月支付总金额");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_XFDC_INDEX, sdb_icps_zm_credit.xfdc_index, "消费档次");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_ZMINFO_POSITIVE_BIZ_CNT_1Y, sdb_icps_zm_credit.positive_biz_cnt_1y, "最近一年履约场景数");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_EXTEND_PARAM1, sdb_icps_zm_credit.extend_param1, "扩展1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_EXTEND_PARAM2, sdb_icps_zm_credit.extend_param2, "扩展2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_ZMINFO_EXTEND_PARAM3, sdb_icps_zm_credit.extend_param3, "扩展3");

    iRet = APP_DBInsert("ICPS_ZM_CREDIT", SD_ICPS_ZM_CREDIT, NUMELE(SD_ICPS_ZM_CREDIT), &sdb_icps_zm_credit, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 提交事务 */
    if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}


/************************************************************************
 动态组件函数定义
 组件函数名称:ICPS_APPLY_PBOC_INFO_INS
 组件名称:ICPS_APPLY_PBOC_INFO_INS
 组件功能: 登记人行征信信息
 组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
 使用限制:
 程 序 员:
 发布日期:2009年12月11日
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT ICPS_APPLY_PBOC_INFO_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_PBOC_CREDIT sdb_icps_pboc_credit;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_pboc_credit, 0, sizeof(sdb_icps_pboc_credit));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_pboc_credit.apply_no, "申请单号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_pboc_credit.plt_date, "平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_pboc_credit.plt_serial, "平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_ID_TYPE, sdb_icps_pboc_credit.id_type, "证件类型");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_ID_NUM, sdb_icps_pboc_credit.id_num, "证件号码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_QUERY_NO, sdb_icps_pboc_credit.query_no, "查询编号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_QUERY_FLAG, sdb_icps_pboc_credit.query_flag, "查询标记");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_MANAGE_LAST_12_QRY_CNT, sdb_icps_pboc_credit.manage_last_12_qry_cnt, "贷后管理最近12个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_MANAGE_LAST_3_QRY_CNT, sdb_icps_pboc_credit.manage_last_3_qry_cnt, "贷后管理最近3个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_MANAGE_LAST_6_QRY_CNT, sdb_icps_pboc_credit.manage_last_6_qry_cnt, "贷后管理最近6个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_12_QRY_CNT, sdb_icps_pboc_credit.approve_last_12_qry_cnt, "贷款审批最近12个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_3_QRY_CNT, sdb_icps_pboc_credit.approve_last_3_qry_cnt, "贷款审批最近3个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_6_QRY_CNT, sdb_icps_pboc_credit.approve_last_6_qry_cnt, "贷款审批最近6个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_30D_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_30d_qry_org_cnt, "贷款审批最近1个月查询机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_12_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_12_qry_org_cnt, "贷款审批最近12个月查询机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_3_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_3_qry_org_cnt, "贷款审批最近3个月查询机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_APPROVE_LAST_6_QRY_ORG_CNT, sdb_icps_pboc_credit.approve_last_6_qry_org_cnt, "贷款审批最近6个月查询机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_12_QRY_CNT, sdb_icps_pboc_credit.card_last_12_qry_cnt, "信用卡审批最近12个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_3_QRY_CNT, sdb_icps_pboc_credit.card_last_3_qry_cnt, "信用卡审批最近3个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_6_QRY_CNT, sdb_icps_pboc_credit.card_last_6_qry_cnt, "信用卡审批最近6个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_30D_QRY_ORG_CNT, sdb_icps_pboc_credit.card_last_30d_qry_org_cnt, "信用卡审批最近1个月查询次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_3_QRY_ORG_CNT, sdb_icps_pboc_credit.card_last_3_qry_org_cnt, "信用卡审批最近3个月查询机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_LAST_6_QRY_ORG_CNT, sdb_icps_pboc_credit.card_last_6_qry_org_cnt, "信用卡审批最近6个月查询机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_ALL_LOAN_NUM, sdb_icps_pboc_credit.all_loan_num, "总贷款笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CAR_LOAN_NUM, sdb_icps_pboc_credit.car_loan_num, "车贷笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_BIZ_LOAN_NUM, sdb_icps_pboc_credit.biz_loan_num, "经营贷款笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_HOUSE_LOAN_NUM, sdb_icps_pboc_credit.house_loan_num, "房贷笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_ALL_LOAN_NUM, sdb_icps_pboc_credit.os_all_loan_num, "未结清人民币帐户贷款总笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_CAR_LOAN_NUM, sdb_icps_pboc_credit.os_car_loan_num, "未结清车贷笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_HOUSE_LOAN_NUM, sdb_icps_pboc_credit.os_house_loan_num, "未结清房贷笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_OS_BIZ_LOAN_NUM, sdb_icps_pboc_credit.os_biz_loan_num, "未结清经营贷款笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_CON13_CNT_SUM, sdb_icps_pboc_credit.ln_nca_con13_cnt_sum, "未结清个人消费贷款笔数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_CRD_CNT_SUM, sdb_icps_pboc_credit.ln_nca_crd_cnt_sum, "未结清信用贷款笔数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_MAX_AMOUNT, sdb_icps_pboc_credit.loan_max_amount, "贷款最高额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_OPER_MAX_AMOUNT, sdb_icps_pboc_credit.loan_oper_max_amount, "经营性贷款最高额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_BALANCE_SUM, sdb_icps_pboc_credit.balance_sum, "未结清贷款本金余额总和");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_SUM_AMOUNT, sdb_icps_pboc_credit.loan_sum_amount, "未结清贷款额度总和");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_AMT_AVG, sdb_icps_pboc_credit.ln_nca_amt_avg, "未结清贷款平均合同金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_HOUSE_AMT_SUM, sdb_icps_pboc_credit.loan_house_amt_sum, "未结清房贷合同金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_HOUSE_BAL_SUM, sdb_icps_pboc_credit.loan_house_bal_sum, "未结清房贷余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_BUSINESS_LOAN_SUM_AMOUNT, sdb_icps_pboc_credit.business_loan_sum_amount, "未结清经营贷款合同金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_BUSINESS_LOAN_SUM_BALANCE, sdb_icps_pboc_credit.business_loan_sum_balance, "未结清经营贷款余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_CON13_BAL_SUM, sdb_icps_pboc_credit.ln_nca_con13_bal_sum, "未结清个人消费贷款余额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_RMM_AVG, sdb_icps_pboc_credit.ln_nca_rmm_avg, "未结清贷款平均剩余还款月数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_PMM_AVG, sdb_icps_pboc_credit.ln_nca_pmm_avg, "未结清贷款平均还款月数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_PMO_AVG, sdb_icps_pboc_credit.ln_nca_pmo_avg, "当月未结清贷款平均应还款");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LN_NCA_PMT_SUM, sdb_icps_pboc_credit.ln_nca_pmt_sum, "未结清贷款当月总实还款");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_REPAY_CAR_MON, sdb_icps_pboc_credit.repay_car_mon, "月度车贷按揭应还款");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_REPAY_HOUSE_MON, sdb_icps_pboc_credit.repay_house_mon, "月度房贷按揭应还款");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_NCA_M1_MAX_3M, sdb_icps_pboc_credit.ln_nca_m1_max_3m, "未结清贷款近3个月最大逾期次数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_OVD_MAX_BAL_CPT, sdb_icps_pboc_credit.loan_ovd_max_bal_cpt, "贷款单月最大逾期金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_LOAN_CUR_OVD_AMOUNT, sdb_icps_pboc_credit.loan_cur_ovd_amount, "贷款当前逾期总金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_CD_MAX_24M, sdb_icps_pboc_credit.ln_cd_max_24m, "贷款近24个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LN_CD_MAX, sdb_icps_pboc_credit.ln_cd_max, "当前贷款最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LOAN_DELQ_12MTH_MAX, sdb_icps_pboc_credit.loan_delq_12mth_max, "未结清贷款近12个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LOAN_DELQ_3MTH_MAX, sdb_icps_pboc_credit.loan_delq_3mth_max, "未结清贷款近3个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_LOAN_DELQ_6MTH_MAX, sdb_icps_pboc_credit.loan_delq_6mth_max, "未结清贷款近6个月最大逾期期数");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_CLASS_5_CREDIT_MORTGAGE, sdb_icps_pboc_credit.class_5_credit_mortgage, "按揭类贷款（房贷、车贷）五级分类");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_CLASS_5_NOT_MORTGAGE, sdb_icps_pboc_credit.class_5_not_mortgage, "非按揭类贷款（房贷、车贷）五级分类");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_DULL_LOAN_NUM, sdb_icps_pboc_credit.dull_loan_num, "呆帐信用贷款笔数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_DULL_LOAN_SUM, sdb_icps_pboc_credit.dull_loan_sum, "呆账的贷款数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_ALL_ASSURE_LOAN_NUM, sdb_icps_pboc_credit.all_assure_loan_num, "总担保笔数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ALL_ASSURE_LOAN_SUM, sdb_icps_pboc_credit.all_assure_loan_sum, "总担保金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CONT_UNDER_ATTENTION_ASSURE, sdb_icps_pboc_credit.cont_under_attention_assure, "对外担保五级分类关注及以上笔数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CONT_UNDER_SECONDARY_ASSURE, sdb_icps_pboc_credit.cont_under_secondary_assure, "状态为次级及以上的担保贷款数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ASSURE_UNDER_ATTENTION_AMT, sdb_icps_pboc_credit.assure_under_attention_amt, "状态为关注及以上的担保贷款金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AS_CV2_BAL_SUM, sdb_icps_pboc_credit.as_cv2_bal_sum, "对外担保五级分类关注及以上余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_AMT_SUM, sdb_icps_pboc_credit.card_amt_sum, "对外担保五级分类关注及以上余额激活且未销户信用卡最大授信额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_LMT_MAX, sdb_icps_pboc_credit.cc_act_lmt_max, "激活且未销户信用卡最大授信额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NML_LMT_AVG, sdb_icps_pboc_credit.ac_nml_lmt_avg, "正常状态卡平均额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NML_LMT_SUM, sdb_icps_pboc_credit.ac_nml_lmt_sum, "正常状态卡总额度");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_ISSUE_ORG_CNT, sdb_icps_pboc_credit.card_issue_org_cnt, "正常状态发卡机构数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_RMB_CNT, sdb_icps_pboc_credit.card_rmb_cnt, "当前激活且未销户人民币贷记卡数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_CNT_SUM, sdb_icps_pboc_credit.cc_cnt_sum, "激活未销户贷记卡数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_NCA_CNT_SUM, sdb_icps_pboc_credit.cc_nca_cnt_sum, "未销户贷记卡数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_NORMAL_NUM, sdb_icps_pboc_credit.normal_num, "正常状态贷记卡数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_ALL_CARD_CNT, sdb_icps_pboc_credit.all_card_cnt, "总卡数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_CU_O90_PCT, sdb_icps_pboc_credit.cc_act_cu_o90_pct, "激活且未销户贷记卡当前使用率大于等于90%占激活未销户贷记卡比例");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_NCA_CU_MIN, sdb_icps_pboc_credit.cc_nca_cu_min, "未销户贷记卡当前最小使用率");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_NCA_MU_MAX, sdb_icps_pboc_credit.cc_nca_mu_max, "未销户贷记卡最大6个月平均使用率");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_NCA_HB_MAX, sdb_icps_pboc_credit.card_nca_hb_max, "未销户贷记卡最大使用额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NCA_CU_AVG, sdb_icps_pboc_credit.ac_nca_cu_avg, "未销户卡当前平均使用率");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_AC_NCA_HB_MAX, sdb_icps_pboc_credit.ac_nca_hb_max, "未销户卡最大使用额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_NML_MU_AVG, sdb_icps_pboc_credit.cc_nml_mu_avg, "正常状态贷记卡6个月平均使用率");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ALL_CARD_CUR_OVD_USED, sdb_icps_pboc_credit.all_card_cur_ovd_used, "正常状态卡当前平均使用率");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_NCA_PMO_SUM, sdb_icps_pboc_credit.card_nca_pmo_sum, "所有未销户贷记卡的应还款总额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_6MTH_MAX_CNT, sdb_icps_pboc_credit.card_delq_6mth_max_cnt, "未销户贷记卡近6个月最大逾期次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_12MTH_MAX_CNT, sdb_icps_pboc_credit.card_delq_12mth_max_cnt, "未销户贷记卡近12个月最大逾期次数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_3MTH_MAX_CNT, sdb_icps_pboc_credit.card_delq_3mth_max_cnt, "未销户贷记卡近3个月最大逾期次数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CARD_MAX_OVD_BAL, sdb_icps_pboc_credit.card_max_ovd_bal, "贷记卡单月最高逾期金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_ALL_CARD_CUR_OVD_AMT_SUM, sdb_icps_pboc_credit.all_card_cur_ovd_amt_sum, "未销户卡当前总逾期金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CONT_DULL_CARD_CNT, sdb_icps_pboc_credit.cont_dull_card_cnt, "呆账的贷记卡数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_DULL_SCARD_CNT, sdb_icps_pboc_credit.dull_scard_cnt, "呆账的准贷记卡数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_AC_ABN_CNT_SUM, sdb_icps_pboc_credit.ac_abn_cnt_sum, "贷记卡为呆帐冻结止付卡数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_ACT_M1_CNT_3M, sdb_icps_pboc_credit.cc_act_m1_cnt_3m, "激活未销户贷记卡近3个月1期及以上逾期卡数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_M1_CNT_PCT_3M, sdb_icps_pboc_credit.cc_act_m1_cnt_pct_3m, "激活未销户贷记卡近3个月1期及以上逾期卡数占比");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_PBOCINFO_CC_ACT_M1_CNT_PCT_6M, sdb_icps_pboc_credit.cc_act_m1_cnt_pct_6m, "激活未销户贷记卡近6个月1期及以上逾期卡数占比");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_AC_NCA_CD_MAX, sdb_icps_pboc_credit.ac_nca_cd_max, "未销户卡当前最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CC_CD_MAX_24M, sdb_icps_pboc_credit.cc_cd_max_24m, "贷记卡近24个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_12MTH_MAX, sdb_icps_pboc_credit.card_delq_12mth_max, "贷记卡未销户账户中过去12个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_3MTH_MAX, sdb_icps_pboc_credit.card_delq_3mth_max, "贷记卡未销户账户中过去3个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CARD_DELQ_6MTH_MAX, sdb_icps_pboc_credit.card_delq_6mth_max, "贷记卡未销户账户中过去6个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_QC_ACT_CD_MAX_24M, sdb_icps_pboc_credit.qc_act_cd_max_24m, "准贷卡近24个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_SCARD_DELQ_12MTH_MAX, sdb_icps_pboc_credit.scard_delq_12mth_max, "准贷卡未销户账户中过去12个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_SCARD_DELQ_3MTH_MAX, sdb_icps_pboc_credit.scard_delq_3mth_max, "准贷卡未销户账户中过去3个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_SCARD_DELQ_6MTH_MAX, sdb_icps_pboc_credit.scard_delq_6mth_max, "准贷卡未销户账户中过去6个月最大逾期期数");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_CREDIT_OPM_MAX, sdb_icps_pboc_credit.credit_opm_max, "信用历史");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_PBOCINFO_AC_OPM_MAX, sdb_icps_pboc_credit.ac_opm_max, "最大开卡月数");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_EXTEND_PARAM1, sdb_icps_pboc_credit.extend_param1, "扩展1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_EXTEND_PARAM2, sdb_icps_pboc_credit.extend_param2, "扩展2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_PBOCINFO_EXTEND_PARAM3, sdb_icps_pboc_credit.extend_param3, "扩展3");

    iRet = APP_DBInsert("ICPS_PBOC_CREDIT", SD_ICPS_PBOC_CREDIT, NUMELE(SD_ICPS_PBOC_CREDIT), &sdb_icps_pboc_credit, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 提交事务 */
    if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:ICPS_APPLY_BANK_INFO_INS
 组件名称:ICPS_APPLY_BANK_INFO_INS
 组件功能: 登记银行信用信息
 组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
 使用限制:
 程 序 员:
 发布日期:2009年12月11日
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT ICPS_APPLY_BANK_INFO_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_BANK_CREDIT sdb_icps_bank_credit;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_bank_credit, 0, sizeof(sdb_icps_bank_credit));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_bank_credit.apply_no, "申请单号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_bank_credit.plt_date, "平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_bank_credit.plt_serial, "平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_ID_TYPE, sdb_icps_bank_credit.id_type, "证件类型");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_ID_NUM, sdb_icps_bank_credit.id_num, "证件号码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_CUSTOMER, sdb_icps_bank_credit.is_exist_customer, "是否存量客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_DEBT_CUSTOMER, sdb_icps_bank_credit.is_exist_debt_customer, "是否存量借记卡客户");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_BALANCE, sdb_icps_bank_credit.balance, "卡内余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_AVG_BALANCE_LAST_3DAYS, sdb_icps_bank_credit.avg_balance_last_3days, "近3个月日均余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_AVG_BALANCE_LAST_6DAYS, sdb_icps_bank_credit.avg_balance_last_6days, "近6个月日均余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_INCOME_LAST_3M, sdb_icps_bank_credit.income_last_3m, "近3个月银行流水收入金额数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PAY_LAST_3M, sdb_icps_bank_credit.pay_last_3m, "近3个月银行流水支出金额数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_INCOME_LAST_6M, sdb_icps_bank_credit.income_last_6m, "近6个月银行流水收入金额数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PAY_LAST_6M, sdb_icps_bank_credit.pay_last_6m, "近6个月银行流水支出金额数");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_CREDIT_CUSTOMER, sdb_icps_bank_credit.is_exist_credit_customer, "是否存量信用卡客户");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CURR_CREDIT_CARD_AMT, sdb_icps_bank_credit.curr_credit_card_amt, "本行信用卡授信额度");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CURR_USE_CREDIT_CARD_AMT, sdb_icps_bank_credit.curr_use_credit_card_amt, "本行信用卡当前使用额度");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_FIN_CUSTOMER, sdb_icps_bank_credit.is_exist_fin_customer, "是否存量理财客户");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FIN_BALANCE, sdb_icps_bank_credit.fin_balance, "理财余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_AVG_FIN_BAL_LAST_6M, sdb_icps_bank_credit.avg_fin_bal_last_6m, "近6个月日均理余额");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_INSURANCE_CUSTOMER, sdb_icps_bank_credit.is_exist_insurance_customer, "是否存量保险客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_EXIST_LOAN_CUSTOMER, sdb_icps_bank_credit.is_exist_loan_customer, "是否存量贷款客户");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_OPERATION_LOAN_BAL, sdb_icps_bank_credit.operation_loan_bal, "经营类贷款总余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PERSONAL_CREDIT_BAL, sdb_icps_bank_credit.personal_credit_bal, "个人信用类贷总余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CAR_LOAN_BAL, sdb_icps_bank_credit.car_loan_bal, "车贷余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_CAR_ASSET, sdb_icps_bank_credit.car_asset, "车产价值评估额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_HOUSE_LOAN_BAL, sdb_icps_bank_credit.house_loan_bal, "房贷余额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_HOUSE_ASSET, sdb_icps_bank_credit.house_asset, "房产价值评估额");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_STOCK_CUSTOMER, sdb_icps_bank_credit.is_stock_customer, "是否证券客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_THIRD_DEPOSITORY, sdb_icps_bank_credit.is_third_depository, "是否第三方存管客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_PAYROLL_CUSTOMER, sdb_icps_bank_credit.is_payroll_customer, "是否工资代发客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_SOCIAL_SECURITY_CUSTOMER, sdb_icps_bank_credit.is_social_security_customer, "是否社保代缴客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_LIFE_PAYMENT_CUSTOMER, sdb_icps_bank_credit.is_life_payment_customer, "是否水电煤代缴客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_COMPANY_NAME, sdb_icps_bank_credit.company_name, "工作单位");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_COMPANY_ORIGIN, sdb_icps_bank_credit.company_origin, "工作单位数据来源");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_POSITION, sdb_icps_bank_credit.position, "职位");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_POSITION_ORIGIN, sdb_icps_bank_credit.position_origin, "职位信息来源");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_INDUSTRY, sdb_icps_bank_credit.industry, "行业");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_INDUSTRY_ORIGIN, sdb_icps_bank_credit.industry_origin, "行业信息来源");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_WORK_YEARS, sdb_icps_bank_credit.work_years, "工作年限");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_WORK_YEARS_ORIGIN, sdb_icps_bank_credit.work_years_origin, "工作年限信息来源");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_INCOME, sdb_icps_bank_credit.income, "月收入区间");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_INCOME_ORIGIN, sdb_icps_bank_credit.income_origin, "月收入信息来源");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_MARRIAGE_STATUS, sdb_icps_bank_credit.marriage_status, "婚姻状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_MARRIAGE_ORIGIN, sdb_icps_bank_credit.marriage_origin, "婚姻状态信息来源");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_OPERATION, sdb_icps_bank_credit.is_operation, "是否经营者");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_OPERATION_ORIGIN, sdb_icps_bank_credit.operation_origin, "是否经营者信息来源");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_INNER_BLACK_CUSTOMER, sdb_icps_bank_credit.is_inner_black_customer, "是否击中内部黑名单客户");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_POLICE_CERTIFIED, sdb_icps_bank_credit.is_police_certified, "是否公安网身份验证成功");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_COURT_EXEC_CUSTOMER, sdb_icps_bank_credit.is_court_exec_customer, "是否击中被执行人等涉诉信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_HOUSE_FUND, sdb_icps_bank_credit.is_query_house_fund, "是否有查询公积金信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_FUND_QUERY_DATE, sdb_icps_bank_credit.fund_query_date, "公积金查询时间");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_MONTH_AMT, sdb_icps_bank_credit.fund_month_amt, "公积金查询月缴纳额");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_FUND_ACCT_DATE, sdb_icps_bank_credit.fund_acct_date, "公积金开户日期");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_FUND_MONTHS_LAST_6M, sdb_icps_bank_credit.fund_months_last_6m, "近6个月累计缴纳月数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_AMT_LAST_6M, sdb_icps_bank_credit.fund_amt_last_6m, "近6个月累计缴纳金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_FUND_TOTAL_MONTHS, sdb_icps_bank_credit.fund_total_months, "总缴纳月数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_TOTAL_AMT, sdb_icps_bank_credit.fund_total_amt, "总缴纳金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_FUND_MAX_AMT, sdb_icps_bank_credit.fund_max_amt, "公积金属地缴纳上限");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_SOCIAL_SECURITY, sdb_icps_bank_credit.is_query_social_security, "是否有查询社保信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_SOCIAL_QUERY_DATE, sdb_icps_bank_credit.social_query_date, "社保信息查询时间");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PENSION_QUERY_MONTH_AMT, sdb_icps_bank_credit.pension_query_month_amt, "养老保险查询月缴纳额");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_PENSION_ACCT_DATE, sdb_icps_bank_credit.pension_acct_date, "养老保险开户日期");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_PENSION_MONTHS_LAST_6M, sdb_icps_bank_credit.pension_months_last_6m, "近6个月养老保险累计缴纳月数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PENSION_AMT_LAST_6M, sdb_icps_bank_credit.pension_amt_last_6m, "近6个月养老保险累计缴纳金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_PENSION_TOTAL_MONTHS, sdb_icps_bank_credit.pension_total_months, "养老保险总缴纳月数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_PENSION_TOTAL_AMT, sdb_icps_bank_credit.pension_total_amt, "养老保险总缴纳金额");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_MEDICARE_MONTH_AMT, sdb_icps_bank_credit.medicare_month_amt, "医疗保险查询月缴纳额");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_MEDICARE_ACCT_DATE, sdb_icps_bank_credit.medicare_acct_date, "医疗保险开户日期");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_MEDICARE_MONTHS_LAST_6M, sdb_icps_bank_credit.medicare_months_last_6m, "近6个月医疗保险累计缴纳月数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_MEDICARE_AMT_LAST_6M, sdb_icps_bank_credit.medicare_amt_last_6m, "近6个月医疗保险累计缴纳金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_MEDICARE_TOTAL_MONTHS, sdb_icps_bank_credit.medicare_total_months, "医疗保险总缴纳月数");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_MEDICARE_TOTAL_AMT, sdb_icps_bank_credit.medicare_total_amt, "医疗保险总缴纳金额");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_DEGREE, sdb_icps_bank_credit.is_query_degree, "是否有查询学历信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_SCHOOL_NAME, sdb_icps_bank_credit.school_name, "院校名称");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_DEGREE_LEVEL, sdb_icps_bank_credit.degree_level, "学历层次");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_DEGREE_TYPE, sdb_icps_bank_credit.degree_type, "学历类别");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_ENTRANCE_YEAR, sdb_icps_bank_credit.entrance_year, "入学年份");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_QUERY_COMMUNICATION, sdb_icps_bank_credit.is_query_communication, "是否有查询运营商信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_COMMUNICATION, sdb_icps_bank_credit.communication, "运营商");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_ONLINE_DAYS, sdb_icps_bank_credit.online_days, "在网时长");
    ICPS_GETXMLNODE_DOUBLE(XMLNM_ICPS_BANKINFO_TOTAL_TEL_FARE, sdb_icps_bank_credit.total_tel_fare, "总话费账单金额");
    ICPS_GETXMLNODE_INTEGER(XMLNM_ICPS_BANKINFO_TOTAL_CALL_HOURS, sdb_icps_bank_credit.total_call_hours, "半年内通话时长");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_IS_OUT_BLACK_CUSTOMER, sdb_icps_bank_credit.is_out_black_customer, "是否击中外部查询黑名单");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_EXTEND_PARAM1, sdb_icps_bank_credit.extend_param1, "扩展1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_EXTEND_PARAM2, sdb_icps_bank_credit.extend_param2, "扩展2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_BANKINFO_EXTEND_PARAM3, sdb_icps_bank_credit.extend_param3, "扩展3");

    iRet = APP_DBInsert("ICPS_BANK_CREDIT", SD_ICPS_BANK_CREDIT, NUMELE(SD_ICPS_BANK_CREDIT), &sdb_icps_bank_credit, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 提交事务 */
    if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:ICPS_ZMINFO_JSON2XML
 组件名称:ICPS_ZMINFO_JSON2XML
 组件功能: 登记银行信用信息
 组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
 使用限制:
 程 序 员:
 发布日期:2009年12月11日
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT ICPS_ZMINFO_JSON2XML(HXMLTREE lXmlhandle)
{
    char sBuf[10000];
    char cZmInfo[5000 + 1];
    char sPath[40 + 1];
    int iRet = -1;
    int iParas = 0;

    /*初始化组件*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(2)

    ICPS_GETPARSEPARAS_STRING(1, sBuf, cZmInfo, "芝麻信息");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sPath, "路径");
    LOG(LM_DEBUG, Fmtmsg("芝麻信息=[%s],路径=[%s]", cZmInfo, sPath), "DEBUG");

    if (strlen(cZmInfo) > 0)
    {
        iRet = cJSON_to_ZmInfo(lXmlhandle, cZmInfo, sPath);
        if (iRet < 0)
            return iRet;
    }

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");
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

    /*初始化组件*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(2)

    /* XMl获取--Begin */
    /*获取入参1*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "银行信息")
    strncpy(cBankInfo, sBuf, sizeof(cBankInfo) - 1);
    trim(cBankInfo);
    LOG(LM_DEBUG, Fmtmsg("银行信息[%s]", cBankInfo), "DEBUG");

    /*获取入参2*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "JSON路径")
    strncpy(path, sBuf, sizeof(path) - 1);
    trim(path);
    LOG(LM_DEBUG, Fmtmsg("JSO路径[%s]", path), "DEBUG");

    if (strlen(cBankInfo) > 0)
    {
        iRet = cBankInfo_to_Xml(lXmlhandle, cBankInfo, path);
        if (iRet < 0)
            return iRet;
    }

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}
