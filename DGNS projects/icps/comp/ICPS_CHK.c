#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_DAILYSTATUS_INSERT
组件名称:ICPS_DAILYSTATUS_INSERT
组件功能: 登记日终状态表
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_DAILYSTATUS_INSERT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_DAILY_STATUS sdb_icps_daily_status;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_icps_daily_status, 0, sizeof(sdb_icps_daily_status));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_BUSI_DATE, sdb_icps_daily_status.busi_date, "业务日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_BUSI_NO, sdb_icps_daily_status.busi_no, "业务编号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_FILE_STEP, sdb_icps_daily_status.file_step, "文件步点");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_TOTAL_CHECK_STATUS, sdb_icps_daily_status.third_total_check_status, "第三方对总账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_DETAIL_CHECK_STATUS, sdb_icps_daily_status.third_detail_check_status, "第三方明细对账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_TOTAL_CHECK_STATUS, sdb_icps_daily_status.host_total_check_status, "核心对总账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_DETAIL_CHECK_STATUS, sdb_icps_daily_status.host_detail_check_status, "核心明细对账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_PRE_TOTAL_CHECK_STATUS, sdb_icps_daily_status.third_pre_total_check_status, "第三方预对总账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_THIRD_PRE_DETAIL_CHECK_STATUS, sdb_icps_daily_status.third_pre_detail_check_status, "第三方预明细对账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_PRE_TOTAL_CHECK_STATUS, sdb_icps_daily_status.host_pre_total_check_status, "核心预对总账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_PRE_DETAIL_CHECK_STATUS, sdb_icps_daily_status.host_pre_detail_check_status, "核心预明细对账状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_CLEAR_STATUS, sdb_icps_daily_status.clear_status, "清算状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_PLT_DATE, sdb_icps_daily_status.plt_date, "平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_PLT_SERIAL, sdb_icps_daily_status.plt_serial, "平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_SEND_HOST_DATE, sdb_icps_daily_status.send_host_date, "上送主机日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_SERIAL, sdb_icps_daily_status.host_serial, "主机流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_HOST_DATE, sdb_icps_daily_status.host_date, "主机日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_RESPCODE, sdb_icps_daily_status.respcode, "交易响应码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_RESPMSG, sdb_icps_daily_status.respmsg, "交易响应信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_TRANS_STATUS, sdb_icps_daily_status.trans_status, "交易状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_BRANCH, sdb_icps_daily_status.branch, "交易机构");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_TELLER, sdb_icps_daily_status.teller, "交易柜员");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM1, sdb_icps_daily_status.extend_param1, "扩展1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM2, sdb_icps_daily_status.extend_param2, "扩展2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_DAILY_STATUS_EXTEND_PARAM3, sdb_icps_daily_status.extend_param3, "扩展3");

    iRet = APP_DBInsert("ICPS_DAILY_STATUS", SD_ICPS_DAILY_STATUS, NUMELE(SD_ICPS_DAILY_STATUS), &sdb_icps_daily_status, sErrmsg);
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


