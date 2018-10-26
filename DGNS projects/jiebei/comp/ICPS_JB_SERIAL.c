#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "../incl/ICPS_JB_HEAD.h"

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_SERIAL_INSERT
组件名称:ICPS_SERIAL_INSERT
组件功能: 登记流水表
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_SERIAL_INSERT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[512];
    ICPS_SERIAL sdb_icps_serial;

    fpub_InitSoComp(lXmlhandle);

    /*获取流水记录标志 0 记录 1 不记录*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sBuf);
    trim(sBuf);
    if ((0 == sBuf[0]) || ('1' == sBuf[0]))
    {
        LOG(LM_STD, Fmtmsg("本交易不记流水[%s]", sBuf), "INFO")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    memset(&sdb_icps_serial, 0, sizeof(sdb_icps_serial));

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_serial.plt_date, "平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_TIME, sdb_icps_serial.plt_time, "平台时间");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_serial.plt_serial, "平台流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_BUSI_DATE, sdb_icps_serial.busi_date, "业务日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_BUSI_NO, sdb_icps_serial.busi_no, "业务编号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_CHANNEL, sdb_icps_serial.channel, "渠道代码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_LOCAL_ID, sdb_icps_serial.local_id, "本行机构标识");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_TRANS_CODE, sdb_icps_serial.trans_code, "平台交易代码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_RECV_FLAG, sdb_icps_serial.send_recv_flag, "往来账标志");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_APPLY_NO, sdb_icps_serial.apply_no, "申请单号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_VERSION, sdb_icps_serial.version, "版本号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_TIME_ZONE, sdb_icps_serial.send_time_zone, "发送方所在时区");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_DTTM, sdb_icps_serial.send_dttm, "报文发起时间");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_MSG_ID, sdb_icps_serial.msg_id, "请求报文标示号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_ID, sdb_icps_serial.third_id, "第三方机构标识");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_TRANS_CODE, sdb_icps_serial.third_trans_code, "第三方交易代码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_RESPCODE, sdb_icps_serial.third_respcode, "第三方响应码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_RESPMSG, sdb_icps_serial.third_respmsg, "第三方响应信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_THIRD_TRANS_STATUS, sdb_icps_serial.third_trans_status, "第三方交易状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_RETRY, sdb_icps_serial.retry, "是否需要重试标记");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_HOST_SERIAL, sdb_icps_serial.send_host_serial, "上送主机流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_SEND_HOST_DATE, sdb_icps_serial.send_host_date, "上送主机日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_SERIAL, sdb_icps_serial.host_serial, "主机流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_DATE, sdb_icps_serial.host_date, "主机日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_TRANS_CODE, sdb_icps_serial.host_trans_code, "主机交易代码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_RESPCODE, sdb_icps_serial.host_respcode, "主机响应码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_RESPMSG, sdb_icps_serial.host_respmsg, "主机响应信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_HOST_STATUS, sdb_icps_serial.host_status, "主机交易状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_IN_CHANNEL_DATE, sdb_icps_serial.in_channel_date, "行内渠道日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_IN_CHANNEL_SERIAL, sdb_icps_serial.in_channel_serial, "行内渠道流水号");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_RESPCODE, sdb_icps_serial.respcode, "交易响应码");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_RESPMSG, sdb_icps_serial.respmsg, "交易响应信息");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_TRANS_STATUS, sdb_icps_serial.trans_status, "交易状态");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_BRANCH, sdb_icps_serial.branch, "交易机构");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_TELLER, sdb_icps_serial.teller, "交易柜员");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_GRANT_BRANCH, sdb_icps_serial.grant_branch, "授权机构");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_GRANT_TELLER, sdb_icps_serial.grant_teller, "授权柜员");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM1, sdb_icps_serial.extend_param1, "扩展1");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM2, sdb_icps_serial.extend_param2, "扩展2");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM3, sdb_icps_serial.extend_param3, "扩展3");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM4, sdb_icps_serial.extend_param4, "扩展4");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_EXTEND_PARAM5, sdb_icps_serial.extend_param5, "扩展5");

    iRet = APP_DBInsert("ICPS_SERIAL", SD_ICPS_SERIAL, NUMELE(SD_ICPS_SERIAL), &sdb_icps_serial, sErrmsg);
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
 组件函数名称:ICPS_SERIAL_UPDATE
 组件名称:ICPS_SERIAL_UPDATE
 组件功能: 更新流水表
 组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
 使用限制:
 程 序 员:
 发布日期:2009年12月11日
 修改日期:
 参数使用示例:
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

    /*获取流水记录标志 0 记录 1 不记录*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sBuf);
    trim(sBuf);
    if ((0 == sBuf[0]) || ('1' == sBuf[0]))
    {
        LOG(LM_STD, Fmtmsg("本交易不记流水[%s]", sBuf), "INFO")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    memset(&sdb_icps_serial, 0, sizeof(sdb_icps_serial));
    memset(sSql_Values, 0, sizeof(sSql_Values));

    snprintf(sSql_Values, sizeof(sSql_Values), "UPDATE ICPS_SERIAL SET ");

    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_DATE, sdb_icps_serial.plt_date, "平台日期");
    ICPS_GETXMLNODE_STRING(XMLNM_ICPS_REQ_PLT_SERIAL, sdb_icps_serial.plt_serial, "平台流水号");

    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_BUSI_DATE, sSql_Values, sSql_Buf, "BUSI_DATE", "业务日期");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_BUSI_NO, sSql_Values, sSql_Buf, "BUSI_NO", "业务编号");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_CHANNEL, sSql_Values, sSql_Buf, "CHANNEL", "渠道代码");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_LOCAL_ID, sSql_Values, sSql_Buf, "LOCAL_ID", "本行机构标识");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_TRANS_CODE, sSql_Values, sSql_Buf, "TRANS_CODE", "平台交易代码");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_RECV_FLAG, sSql_Values, sSql_Buf, "SEND_RECV_FLAG", "往来账标志");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_APPLY_NO, sSql_Values, sSql_Buf, "APPLY_NO", "申请单号");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_VERSION, sSql_Values, sSql_Buf, "VERSION", "版本号");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_TIME_ZONE, sSql_Values, sSql_Buf, "SEND_TIME_ZONE", "发送方所在时区");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_DTTM, sSql_Values, sSql_Buf, "SEND_DTTM", "报文发起时间");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_MSG_ID, sSql_Values, sSql_Buf, "MSG_ID", "请求报文标示号");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_ID, sSql_Values, sSql_Buf, "THIRD_ID", "第三方机构标识");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_TRANS_CODE, sSql_Values, sSql_Buf, "THIRD_TRANS_CODE", "第三方交易代码");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_RESPCODE, sSql_Values, sSql_Buf, "THIRD_RESPCODE", "第三方响应码");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_RESPMSG, sSql_Values, sSql_Buf, "THIRD_RESPMSG", "第三方响应信息");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_THIRD_TRANS_STATUS, sSql_Values, sSql_Buf, "THIRD_TRANS_STATUS", "第三方交易状态");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_RETRY, sSql_Values, sSql_Buf, "RETRY", "是否需要重试标记");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_HOST_SERIAL, sSql_Values, sSql_Buf, "SEND_HOST_SERIAL", "上送主机流水号");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_SEND_HOST_DATE, sSql_Values, sSql_Buf, "SEND_HOST_DATE", "上送主机日期");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_SERIAL, sSql_Values, sSql_Buf, "HOST_SERIAL", "主机流水号");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_DATE, sSql_Values, sSql_Buf, "HOST_DATE", "主机日期");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_TRANS_CODE, sSql_Values, sSql_Buf, "HOST_TRANS_CODE", "主机交易代码");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_RESPCODE, sSql_Values, sSql_Buf, "HOST_RESPCODE", "主机响应码");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_RESPMSG, sSql_Values, sSql_Buf, "HOST_RESPMSG", "主机响应信息");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_HOST_STATUS, sSql_Values, sSql_Buf, "HOST_STATUS", "主机交易状态");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_RESPCODE, sSql_Values, sSql_Buf, "RESPCODE", "交易响应码");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_RESPMSG, sSql_Values, sSql_Buf, "RESPMSG", "交易响应信息");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_TRANS_STATUS, sSql_Values, sSql_Buf, "TRANS_STATUS", "交易状态");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_BRANCH, sSql_Values, sSql_Buf, "BRANCH", "交易机构");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_TELLER, sSql_Values, sSql_Buf, "TELLER", "交易柜员");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_GRANT_BRANCH, sSql_Values, sSql_Buf, "GRANT_BRANCH", "授权机构");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_GRANT_TELLER, sSql_Values, sSql_Buf, "GRANT_TELLER", "授权柜员");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM1, sSql_Values, sSql_Buf, "EXTEND_PARAM1", "扩展1");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM2, sSql_Values, sSql_Buf, "EXTEND_PARAM2", "扩展2");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM3, sSql_Values, sSql_Buf, "EXTEND_PARAM3", "扩展3");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM4, sSql_Values, sSql_Buf, "EXTEND_PARAM4", "扩展4");
    ICPS_SQLSETVALUE_STRING(XMLNM_ICPS_RESP_EXTEND_PARAM5, sSql_Values, sSql_Buf, "EXTEND_PARAM5", "扩展5");

    sSql_Values[strlen(sSql_Values) - 1] = '\0'; /*去掉最后一个","*/

    snprintf(sSql_Where, sizeof(sSql_Where), " WHERE PLT_DATE='%s' AND PLT_SERIAL='%s' ", sdb_icps_serial.plt_date,
            sdb_icps_serial.plt_serial);
    strcat(sSql_Values, sSql_Where);
    LOG(LM_STD, Fmtmsg("sSql_Values[%s]", sSql_Values), "INFO");
    DCIBegin();
    iRet = DCIExecuteDirect(sSql_Values);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库更新操作失败, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    /* 提交事务 */
    if (DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库提交操作失败, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    if (iRet == 0)
    {
        LOG(LM_STD, Fmtmsg("更新操作无符合条件的记录"), "INFO")
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_NORECORD);
        return ICPS_COMPSTATUS_SQL_NORECORD;
    }

    fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_SUCC);
    return ICPS_COMPSTATUS_SQL_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_EXECUPD
组件名称:ICPS_EXECUPD
组件功能:执行更新语句
组件参数:sql语句

备注：

项 目 组:
程 序 员:
发布日期:2015年6月2日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_EXECUPD(HXMLTREE lXmlhandle)
{
    int iRet, iParas;
    char sBuf[256];
    char sUpdSql[4096];

    COMP_PARACOUNTCHKMIN(1);

    memset(sUpdSql, 0, sizeof(sUpdSql));
    COMP_GETPARSEPARAS(1, sUpdSql, "执行语句")
    trim(sUpdSql);
    if (0 == sUpdSql[0]) /*执行语句不能为空*/
    {
        fpub_SetMsg(lXmlhandle, 99999, "PARA NULL ERR!");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("更新语句:[%s]", sUpdSql), "INFO");

    DCIBegin();
    iRet = DCIExecuteDirect(sUpdSql);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库更新操作失败, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    /* 提交事务 */
    if (DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库提交操作失败, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return ICPS_COMPSTATUS_SQL_FAIL;
    }

    if (iRet == 0)
    {
        LOG(LM_STD, Fmtmsg("更新操作无符合条件的记录"), "INFO")
        fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_NORECORD);
        return ICPS_COMPSTATUS_SQL_NORECORD;
    }

    fpub_SetCompStatus(lXmlhandle, ICPS_COMPSTATUS_SQL_SUCC);
    return ICPS_COMPSTATUS_SQL_SUCC;
}

