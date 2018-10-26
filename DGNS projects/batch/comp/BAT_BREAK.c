/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_UPD_BREAKDATE.c
文件描述:更新breakdate组件集
程 序 员:TUQL
发布日期:2016-06-04
程 序 员:
修改日期:
修改说明:
 *********************************************************************/
#include <dlfcn.h>
#include "gaps_head.h"
/*#include "DCI.h"*/
#include "batch_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_CTRL.so</soname>\
        <sosrcname>BAT_CTRL.c</sosrcname>\
        <sonote>更新breakdate组件集</sonote>\
        <version>\
        <rec ver=\"4.1.0.1\" modify=\"2016-6-4 15:08\" programer=\"TUQL\" filesize=\"1266963\">HS-AgentV2.1整理</rec>\
        </version>\
        </root>";
    printf("\n================动态组件基本信息================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" 取详细信息失败...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" 请查看详细信息...\n");
    return 0;
}
/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_UPD_BREAKDATA
组件名称:SBATCH_UPD_BREAKDATA
组件功能: 批量业务更新BREAKDATA
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
1    1-输入   步点响应码  416XML解析字符串           N
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_UPD_BREAKDATA(HXMLTREE lXmlhandle)
{
    
    DCIBegin();
    /* 不管是否断点，保存当前节点信息 */
    if( fprv_export_break( lXmlhandle ) != 0 )
    {
        DCIRollback();
        return COMPSTATUS_FAIL;
    }
    DCICommit();
    fpub_SetCompStatus(lXmlhandle, COMPRET_SUCC );

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return COMPRET_SUCC;  
}
    