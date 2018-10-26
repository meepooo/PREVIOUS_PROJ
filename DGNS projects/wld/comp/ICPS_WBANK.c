
#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_FILE_CHECK
组件名称:ICPS_FILE_CHECK
组件功能: 登记日终状态表
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_FILE_CHECK(HXMLTREE lXmlhandle)
{
	CURSOR cur;
    char sErrmsg[512];
    char s
    fpub_InitSoComp(lXmlhandle);


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


