/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
文 件 名:DATA_DEC_DATE.c
文件描述:
项 目 组:
程 序 员:[]
创建时间:2015-7-31 18:33:21[Gen]
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

#define MAX_SIZE 256
#include "gaps_head.h"
/*
   注：本函数为组件库公共函数,用于在发布状态下显示内部版本信息
       在生产环境下，每次更新均应修改版本号、填入相应信息
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
	     "<soname>DATA_DEC_DATE.so</soname>"
	     "<sosrcname>DATA_DEC_DATE.c</sosrcname>"
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





char* TrimSpeChar(char c,char *sData)
{
	int i = 0;
	int j = 0;
	
	if ( NULL == sData)
	{
		return NULL;	
	}
	
	while( '\0' != *(sData+i))
	{
		if (c != *(sData+i)&& ' ' != *(sData+i))
		{
			*(sData+j) = *(sData+i);
			i++;
			j++;	
		}
		else
		{
			i++;
		}		
	
	}

	*(sData+j)='\0';

	return sData;
}

/************************************************************************
动态组件函数定义
组件函数名称:DATA_DEC_DATE
组件名称:DATA_DEC_DATE
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
	1         输入      para1               ICXP报文                                          0         元素名=字符赋值公式
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
修改日期:/2015-7-31 18:33:21(gen)
参数使用示例:
************************************************************************/
IRESULT SDATA_TRIMSPECHAR(HXMLTREE lXmlhandle)
{
  char para1[30];

  char	sPath[MAX_SIZE];
  char	sData[MAX_SIZE];
  char	cTrimChar;
  int	iParas;
  int	i;

  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	iParas=fpub_GetPARAcount(lXmlhandle);
	
	/*XXX处理失败*/
  if ( iParas <	2 )
  {
    LOG(LM_STD, Fmtmsg("  -->处理失败:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }	


	COMP_GETPARSEPARAS(1,sData,"0-成功,1-失败");
	cTrimChar = atoi(sData);

	if('\0' == cTrimChar)
	{
		LOG(LM_STD, Fmtmsg("  -->参数1错误:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
	}
			
	for(i=2;i<=iParas;i++)
	{
		memset(sPath,0x00,sizeof(sPath));
		memset(sData,0x00,sizeof(sData));
		
		COMP_GETPARSEPARAS(i, sPath, "赋值解析式");
		
		LOG(LM_STD, Fmtmsg("sPath[%s]赋值", sPath), "");		
		xml_GetElement(lXmlhandle, sPath, sData,sizeof(sData));
		LOG(LM_STD, Fmtmsg("sData[%s]赋值", sData), "");	
		alltrim(sData);
		TrimSpeChar(cTrimChar,sData);
		LOG(LM_STD, Fmtmsg("去[%c]sData[%s]赋值", cTrimChar,sData), "");	
		xml_SetElement(lXmlhandle, sPath, alltrim(sData)); 
	}	


#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}


