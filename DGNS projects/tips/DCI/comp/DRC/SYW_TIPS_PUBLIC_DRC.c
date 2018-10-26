/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V3.0.00
  操作系统:AIX5.3
  文件名称:SYW_TIPS_PUBLIC_DRC.c
  文件描述:TIPS个性化公共组件
  项 目 组:TIPS专用前置产品组
  程 序 员:sunpj
  发布日期:
  修    订:
  修改日期:  
 *********************************************************************/
/*
   总体说明:
   函数说明
   组件函数名称                 组件名称                      发布日期  程序员 修改日期 修改人

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_TRIMMSG
  组件名称: TIPS报文去除空格

  组件功能: 
  TIPS报文去除空格
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: TIPS专用前置产品组
  程 序 员: sunpj
  发布日期: 2017年05月23日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SYW_TIPS_TRIMMSG(HXMLTREE lXmlhandle)
{
    int iParas;
    char   cRootNodeName[64 + 1]       = {0};
    char   cTmp[512 + 1]               = {0};
    
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TRIMMSG...处理开始"), "INFO") 
    
    COMP_PARACOUNTCHK(1);
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cRootNodeName, 0x00, sizeof(cRootNodeName));
    COMP_GETPARSEPARAS(1, cTmp, "报文节点名");
    pstrcopy(cRootNodeName, cTmp, sizeof(cRootNodeName));
    LOG(LM_DEBUG, Fmtmsg("报文节点名[%s]", cRootNodeName), "INFO")
    
    prv_trimLeafNodeValue(lXmlhandle, cRootNodeName);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TRIMMSG...处理结束"), "INFO")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}

void prv_trimLeafNodeValue(HXMLTREE lXmlhandle, const char* cRootNodeName)
{
    int    iElementCount               = 0;
    int    iRepeats                    = 0;
    char   cSubNodeName[64 + 1]        = {0};
    char   cValue[10*1024 + 1]         = {0};
    char   cNodePath[1024 + 1]         = {0};
    
    iElementCount = xml_ChildElementCount(lXmlhandle, cRootNodeName);
    //LOG(LM_DEBUG, Fmtmsg("节点数[%d]", iElementCount), "INFO")
    
    if (0 != iElementCount)
    {
        iRepeats = 0;
        while (iRepeats < iElementCount)
        {
            if (0 == xml_GetChildElementName(lXmlhandle, cRootNodeName, iRepeats + 1, cSubNodeName, sizeof(cSubNodeName)))
            {
                sprintf(cNodePath, "%s/%s", cRootNodeName, cSubNodeName);
                if (1 == xml_IsLeafNode(lXmlhandle, cNodePath))
                {
                    //LOG(LM_DEBUG, Fmtmsg("节点[%s]是叶子节点", cNodePath), "INFO")
                    memset(cValue, 0x00, sizeof(cValue));
                    COMP_SOFTGETXML(cNodePath, cValue);
                    trim(cValue);
                    COMP_SOFTSETXML(cNodePath, cValue);
					iRepeats++;
                }
                else if (1 == xml_ElementExist(lXmlhandle, cNodePath))
                {
                    //LOG(LM_DEBUG, Fmtmsg("节点[%s]非叶子节点", cNodePath), "INFO")
                    prv_trimLeafNodeValue(lXmlhandle, cNodePath);
					iRepeats++;
                }
                else
                {
                    LOG(LM_DEBUG, Fmtmsg("程序异常结束"), "INFO")
                    break;
                }
            }
        }
    }
}