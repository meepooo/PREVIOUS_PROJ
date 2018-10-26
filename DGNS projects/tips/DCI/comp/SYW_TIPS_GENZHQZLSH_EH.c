#include "gaps_head.h"


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_GENZHQZLSH_EH
组件名称: 生成综合前置流水号，适应单机模式，集群模式
组件功能: 
  生成发核心流水号
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: zhangl
发布日期: 2017年05月2日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_GENZHQZLSH_EH(HXMLTREE lXmlhandle)
{
    int iParas;
	char sBuf[255];
	int iMode;
	char xmlNode[255];
	int iret = 0;
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("生成流水号开始"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(2)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"模式");
    trim(sBuf);
    iMode = atoi(sBuf);
	
    memset(sBuf, 0x00, sizeof(sBuf));
	memset(xmlNode, 0x00, sizeof(xmlNode));
    COMP_GETPARSEPARAS(2,sBuf,"前置流水号路径");
    trim(sBuf);
    strncpy(xmlNode, sBuf, sizeof(xmlNode)-1);

	memset(sBuf, 0x00 ,sizeof(sBuf));
	if (0 == iMode) {
		iret = prv_GenSerinoSingle(lXmlhandle, sBuf, sizeof(sBuf));
	}
	else if (1 == iMode) {
		iret = prv_GenSerinoHA(lXmlhandle, sBuf, sizeof(sBuf));
	}
	else {
		fpub_SetMsg(lXmlhandle, -1, "生成流水号失败");
    	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	if (iret < 0) {
		fpub_SetMsg(lXmlhandle, -1, "生成流水号失败");
    	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	snprintf(sBuf, sizeof(sBuf), "%d", iret);
	COMP_HARDSETXML(xmlNode, sBuf);
    fpub_SetMsg(lXmlhandle, 0, "生成发核心流水号");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("生成流水号结束"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}   

