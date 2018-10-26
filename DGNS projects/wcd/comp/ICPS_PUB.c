#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_GEN_MSG_ID
组件名称:ICPS_GEN_MSG_ID
组件功能: 生成第三方报文标示号
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_GEN_MSG_ID(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sMsg_Id[64 + 1]; /*报文标示号*/

    PARA_GENMSGID st_para_genmsgid;

    memset(&st_para_genmsgid, 0, sizeof(st_para_genmsgid));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_genmsgid.busi_no, "业务编号");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_genmsgid.plt_date, "平台日期");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, st_para_genmsgid.plt_serial, "平台流水号");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, st_para_genmsgid.msg_id_path, "报文标示号存放路径");

    LOG(LM_STD,
            Fmtmsg("业务编号=[%s],平台日期=[%s],平台流水号=[%s]\n报文标示号存放路径=[%s]", st_para_genmsgid.busi_no, st_para_genmsgid.plt_date,
                    st_para_genmsgid.plt_serial, st_para_genmsgid.msg_id_path), "INFO");

    /*判断业务编号，暂只支持借呗*/
    if (0 == strcmp(st_para_genmsgid.busi_no, "jiebei"))
    {
        snprintf(sMsg_Id, sizeof(sMsg_Id), "%08.8s%08d", st_para_genmsgid.plt_date, atol(st_para_genmsgid.plt_serial));
        LOG(LM_STD, Fmtmsg("报文标示号=[%s]", sMsg_Id), "INFO");
    }
    else
    {
        LOG(LM_STD, Fmtmsg("暂不支持的业务"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "暂不支持的业务");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML(st_para_genmsgid.msg_id_path, sMsg_Id);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
