/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
文 件 名:DATA_GetMd5.c
文件描述:
项 目 组:
程 序 员:傅阳伟
创建时间:2016/8/24
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
#include "DRC_esb_md5.h"
/************************************************************************
动态组件函数定义 获取字符串或者文件的MD5值
组件函数名称:DATA_GetMd5
组件名称:DATA_GetMd5
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
	1         输入      para1               XML解析字符串       NULL                          可空      加密源类型 1文件 其他字符串
	2         输入      para2               XML解析字符串       NULL                          不可空    加密源 
	3         输入      para3               XML解析字符串       NULL                          不可空    存放MD5的XML路径


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
修改日期:2016/8/24
参数使用示例:
************************************************************************/
IRESULT DATA_GetMd5(HXMLTREE lXmlhandle)
{
	int	nParas = -1;
	int	nFlag = -1;

	char sTemp[1024] = {0x00};
	char sMd5[1024] = {0x00};
	char sPath[1024] = {0x00};


	fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	nParas=fpub_GetPARAcount(lXmlhandle);
	
	/*判断参数个数*/
	if (nParas != 3)
	{
		LOG(LM_STD, Fmtmsg("  -->处理失败:输入参数个数错误"), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}	
	
	chdir(getenv("HOME"));

	/*获取输入参数:加密类型*/
	memset(sTemp,0x00,sizeof(sTemp));
	COMP_GETPARSEPARAS(1, sTemp, "赋值解析式");
	nFlag = atoi(sTemp);
	LOG(LM_DEBUG, Fmtmsg("nFlag[%d]", nFlag), __func__)

	/*获取输入参数:加密源*/
	memset(sTemp,0x00,sizeof(sTemp));
	COMP_GETPARSEPARAS(2, sTemp, "赋值解析式");
	LOG(LM_DEBUG, Fmtmsg("加密源[%s]", sTemp), __func__)
	
	/*获取输入参数:输出的XML路径*/
	memset(sPath,0x00,sizeof(sPath));
	COMP_GETPARSEPARAS(3, sPath, "赋值解析式");

	

	memset(sMd5,0x00,sizeof(sMd5));
	if(1 == nFlag)
	{
		DRC_getMd5File(sTemp,sMd5);
		
	}
	else
	{
		DRC_getMd5Str(sTemp,strlen(sTemp),sMd5);
	}

	xml_SetElement(lXmlhandle,sPath, alltrim(sMd5)); 


fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	return 0;
}



/*
   注：本函数为组件库公共函数,用于在发布状态下显示内部版本信息
       在生产环境下，每次更新均应修改版本号、填入相应信息
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
	     "<soname>FILE_LineTo3DesToBase64.so</soname>"
	     "<sosrcname>FILE_LineTo3DesToBase64.c</sosrcname>"
	     "<sonote></sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-31 18:33:21\" programer=\"[傅阳伟]\" filesize=\"FILE\">初始发布版</rec>"
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
