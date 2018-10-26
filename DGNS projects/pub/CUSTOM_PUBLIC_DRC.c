/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V1.0.00
  操作系统:LIUNX64
  文件名称:CUSTOM_PUBLIC_DRC.c
  文件描述:GAPS个性化公共组件
  项 目 组:
  程 序 员:liurj
  发布日期:
  修    订:
  修改日期:  
 *********************************************************************/

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.00"
#define MAX_RES_BUF_SIZE 5*1024

#include "gaps_head.h"
#include <string.h>

/*
   注：本函数为组件库公共函数,用于在发布状态下显示内部版本信息
       在生产环境下，每次更新均应修改版本号、填入相应信息
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
             "<soname>CUSTOM_PUBLIC_DRC.so</soname>"
             "<sosrcname>CUSTOM_PUBLIC_DRC.c</sosrcname>"
             "<sonote>个性化公共组件</sonote>"
             "<version>"
               "<rec ver=\"1.0.00\" modify=\"2018-01-22 17:18:33\" programer=\"[刘如杰]\" filesize=\"FILE\">初始发布版</rec>"
             "</version>"
     "</root>";
  printf("\n================动态组件基本信息================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if (strlen(sversion) >= isize)
  {
        printf(" -->取详细信息失败...\n");
        return -2;
  }
        strcpy(sinfo,sversion);
        printf(" -->请查看详细信息...\n");
  return 0;
}


/************************************************************************
  动态组件函数定义
  组件函数名称: SYS_CUSTOM_SHELLOUTPUT
  组件名称: 执行shell命令并取输出结果

  组件功能: 
  执行shell命令并取输出结果
  组件参数: 
  序号 参数名称        资源类别       缺省值   是否可空  参数说明
  1    SHELL命令       XML解析字符串           不可为空  需要执行的SHELL命令
  2    结果保存节点    XML解析字符串           不可为空  执行SHELL命令后输出屏幕的结果保存至某节点

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作
  无

  项 目 组: 
  程 序 员: liurj
  发布日期: 2018年01月22日
  修改日期: 
  修改日期: 
  参数使用示例: pwd /sys/shelloutput 
 ************************************************************************/
IRESULT SYS_CUSTOM_SHELLOUTPUT(HXMLTREE lXmlhandle)
{
    int iParas;
    char sCmd[256] = {0};     //SHELL命令
    char sOutput[256] = {0};  //SHELL输出的结果保存到该节点
    char sLine[1024] = {0};   //shell输出的结果的每一行
    char* pRes = NULL;        //shell输出的总体结果
    FILE* fp = NULL;
    int iOffset = 0;
    int iLen = 0;
 
    fpub_InitSoComp(lXmlhandle); 
    
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  

    COMP_PARACOUNTCHKMIN(2);
    COMP_GETPARSEPARAS(1, sCmd, "SHELL命令");
    COMP_GETPARSEPARAS(2, sOutput, "保存输出结果的节点");
    
    pRes = (char *)malloc(sizeof(char) * MAX_RES_BUF_SIZE);
    if(pRes == NULL)
    {
      LOG(LM_STD, "malloc分配内存失败", __func__);     
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("申请内存失败，未执行SHELL命令"));
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);    
      return COMPRET_FAIL;
    }
    
    memset(pRes, 0, MAX_RES_BUF_SIZE);  	
    fp = popen(sCmd, "r");
    if(fp == NULL)
    {
      LOG(LM_STD, "读取SHELL命令结果失败", "ERROR");
      fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL;
    }
      	  	
    while(fgets(sLine, sizeof(sLine), fp) != NULL)
    {
      iLen = strlen(sLine);
      if(iOffset + iLen < MAX_RES_BUF_SIZE)
      {
        pstrcopy(pRes+iOffset, sLine, MAX_RES_BUF_SIZE-iOffset);
        memset(sLine, 0, sizeof(sLine));
        iOffset += iLen;
      }
      else
      {
        pRes[iOffset] = '\0';
        if(fp != NULL)
        {
          pclose(fp);
          fp = NULL;
        }
        COMP_SOFTSETXML(sOutput,pRes);
        LOG(LM_STD, "申请的内存不足以保存SHELL输出的结果，只保存了部份结果", "ERROR");
        fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        free(pRes);
        pRes = NULL;
        return COMPRET_FAIL;			}
    }

    if(fp != NULL)
    {
      pclose(fp);
      fp = NULL;
    }

    if(pRes[iOffset-1] =='\n')
    {
      pRes[iOffset-1] = '\0';
    }

    COMP_SOFTSETXML(sOutput,pRes);
    free(pRes);
    pRes = NULL;
    LOG(LM_STD, "获取shell执行结果成功", "INFO");
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
