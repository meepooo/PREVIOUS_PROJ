/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
文 件 名:DRC_BASE64.c
文件描述:
项 目 组:
程 序 员:fuyw
创建时间:2016/8/18
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
#include "DRC_des.h"
#include "base64.h"

/************************************************************************
动态组件函数定义 对文件每一行先做3DES加密再做BASE64加密
组件函数名称:DRC_BASE64
组件名称:DRC_BASE64
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
	1         输入      para1               XML解析字符串       NULL                          不可空    3Des的key
	2         输入      para2               XML解析字符串       NULL                          不可空    源文件路径
	3         输入      para3               XML解析字符串       NULL                          不可空    目标文件路径

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
修改日期:/2016/8/17
参数使用示例:
************************************************************************/
IRESULT DRC_BASE64(HXMLTREE lXmlhandle)
{
	int	nRet = -1;
	int	nLenDes = -1;
	int	nLenBase64 = -1;
	char	sSrcData[1024] ;
	char	sDesData[1024] ;
	char	sFlag[10] ;
	char	*pTemp = NULL;

	fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	
	/*判断参数个数*/
	nRet=fpub_GetPARAcount(lXmlhandle);
	if (nRet != 3)
	{
		LOG(LM_STD, Fmtmsg("  -->处理失败:输入参数个数错误"), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}	
	
	/*获取输入参数:Des的key*/
	memset(sFlag,0x00,sizeof(sFlag));
	COMP_GETPARSEPARAS(1, sFlag, "赋值解析式");
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("flag[%s]", sFlag), __func__)
#endif	
	/*获取输入参数:源文件路径*/
	memset(sSrcData,0x00,sizeof(sSrcData));
	COMP_GETPARSEPARAS(2, sSrcData, "赋值解析式");
	LOG(LM_DEBUG, Fmtmsg("SrcData[%s]", sSrcData), __func__)

	/*获取输入参数:目标文件路径*/
	memset(sDesData,0x00,sizeof(sDesData));
	COMP_GETPARSEPARAS(3, sDesData, "赋值解析式");
	LOG(LM_DEBUG, Fmtmsg("DestData[%s]", sDesData), __func__)

	nLenDes = strlen(sSrcData) ;

	if ( sFlag[0] == '0' )
	{	
		/*BASE64加密*/
		pTemp=base64_encode(sSrcData,nLenDes,&nLenBase64);
		if( NULL == pTemp)
		{
			LOG(LM_DEBUG, Fmtmsg("BASE64加密错误"), __func__)
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
	}	
	if ( sFlag[0] == '1' )
	{	
		/*BASE64加密*/
		pTemp=base64_decode(sSrcData,nLenDes,&nLenBase64);
		if( NULL == pTemp)
		{
			LOG(LM_DEBUG, Fmtmsg("BASE64解码错误"), __func__)
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
	}	

	LOG(LM_DEBUG, Fmtmsg("pTemp[%s][%ld]", pTemp, strlen(pTemp)), __func__)

//	if(xml_SetBinElement(lXmlhandle,sDesData,pTemp,strlen(pTemp)) < 0)
//	if (xml_SetElement(lXmlhandle, sDesData, pTemp) == -1)
	if(xml_SetElement(lXmlhandle, sDesData, pTemp)<0)
	{
		/*LOG(LM_DEBUG,Fmtmsg("赋值报文失败"),"ERROR");*/
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(-1,LM_STD,Fmtmsg("赋值报文失败"),"ERR");
	}

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
	     "<soname>FILE_LineToDesToBase64.so</soname>"
	     "<sosrcname>FILE_LineToDesToBase64.c</sosrcname>"
	     "<sonote></sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-31 18:33:21\" programer=\"[fuyw]\" filesize=\"FILE\">初始发布版</rec>"
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
