/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
文 件 名:DATA_STRREPLACE.c
文件描述:
项 目 组:
程 序 员:[傅阳伟]
创建时间:2015-7-28 17:18:33[Gen]
修    订:
修改时间:
****************************************************************************/
/****************************************************************************
修改记录
修改日期:
修 改 人:
修改内容:
****************************************************************************/
#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

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
	     "<soname>DATA_STRREPLACE.so</soname>"
	     "<sosrcname>DATA_STRREPLACE.c</sosrcname>"
	     "<sonote>字符串替换</sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-28 17:18:33\" programer=\"[傅阳伟]\" filesize=\"FILE\">初始发布版</rec>"
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


int nAnalysisString(char *sSrc,char *sDesc1,char *sDesc2)
{
	int nRet = -1;	
	
	char *pTemp  = NULL;
	
	pTemp = strchr(sSrc, '|');

	if( NULL == pTemp )
	{
		return -1;	
	}
		
	strncpy(sDesc1,sSrc,pTemp-sSrc);
	strcpy(sDesc2,pTemp+1);
	
	return nRet;
}
















/************************************************************************
动态组件函数定义
组件函数名称:DATA_STRREPLACE
组件名称:DATA_STRREPLACE
组件功能:字符串替换
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2015-7-28 17:18:33(gen)
参数使用示例:
************************************************************************/
IRESULT DATA_STRREPLACE(HXMLTREE lXmlhandle)
{
  
  char sBufSrc[102400];
  char sSrc[128];
  char sDesc[128];
	char sBufDesc[102400];
  int  iParas;
  int	i = -1;

  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	iParas=fpub_GetPARAcount(lXmlhandle); 
	LOG(LM_STD,Fmtmsg("count(iParas)=[%d]",iParas),__func__);
	
	for(i = 1;i<= iParas;i++)
	{		
		memset(sBufSrc,0x00,sizeof(sBufSrc));
		memset(sSrc,0x00,sizeof(sSrc));
		memset(sDesc,0x00,sizeof(sDesc));
		
		COMP_GETPARSEPARAS(i,sBufSrc,"0-成功，1-失败");
		nAnalysisString(sBufSrc,sSrc,sDesc);
		LOG(LM_STD,Fmtmsg("SRC[%s],DESC[%s]",sSrc,sDesc),__func__);
		
		
		COMP_GETSOFTXML("/commbuf",sBufSrc);
		LOG(LM_STD,Fmtmsg("sBufSrc[%s]",sBufSrc),__func__);

	}
	


  /*XXX处理失败
  if ( 2 > 1 )
  {
    LOG(LM_STD, Fmtmsg("  -->处理失败:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }	
	*/
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}



