/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
文 件 名:SCOMP_DEMO.c
文件描述:简单样例组件及测试专用组件集
项 目 组:GAPS研发组
程 序 员:Tianhc
发布日期:2011-07-15 8:43:28
修    订:
修改日期:
****************************************************************************/

#include "gaps_head.h"
#include "xml.h"
static char Level_STRAC_DEMO_c[] = "{$Id: STRAC_DEMO.c 2548 2014-07-09 09:26:16Z tianhc $}";

/************************************************************************
动态组件函数定义
组件函数名称: STRAC_HELLOWORLD
组件名称: TRAC_HELLOWORLD
组件功能:
     最简单的Hello World组件,用于练习&教学
组件参数:
  序号 参数名称   资源类别     缺省值   是否可空  参数说明
  1   第1个参数    416-解析字符串            Y    0-设置组件为失败,其余设置组件运行成功

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: GAPSV4.1
程 序 员:
发布日期: 2011-07-15 8:44:15
修改日期:
参数使用示例:
************************************************************************/
IRESULT STRAC_HELLOWORLD(HXMLTREE lXmlhandle)
{
  char spara1[30];
  char sbuf[255];
  int  iParas;
  fpub_InitSoComp(lXmlhandle);
  COMP_GETPARSEPARAS(1, spara1, "第1个参数")
  LOG(LM_DEBUG, Fmtmsg("  -->第1个参数[%s]", spara1), "INFO")
  LOG(LM_STD, Fmtmsg("Hello World!"), __func__)
  if ( strcmp(spara1, "0") == 0 )
  {
    LOG(LM_STD, Fmtmsg("  -->交易拒绝:xxxx"), "ERROR");
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}


static char* prv_malloc_2(int isize)
{
	  char *ptmp;
	  LOG(LM_STD, Fmtmsg("  嵌套函数中的内存分配2..."), __func__)
	  ptmp = (char *)malloc(isize);
	  return ptmp;
}	


static char* prv_malloc(int isize)
{
	  LOG(LM_STD, Fmtmsg("  嵌套函数中的内存分配1..."), __func__)
	  return prv_malloc_2(isize);
}	

/************************************************************************
动态组件函数定义
组件函数名称: STRAC_MEMLEAK
组件名称: TRAC_MEMLEAK
组件功能:
     内存泄漏场景模拟组件,用于验证测试案例运行是否正常
组件参数:
  序号 参数名称   资源类别     缺省值   是否可空  参数说明


组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: GAPSV4.1
程 序 员:
发布日期: 2011-07-15 8:44:15
修改日期:
参数使用示例:
************************************************************************/
IRESULT STRAC_MEMLEAK(HXMLTREE lXmlhandle)
{
  char sflag_malloc[30], sflag_openfile[30], sflag_cursor[30];
  char sbuf[255], *p, *pfunc, *poverstack;
  char sbuf6[6];
  int  iParas, iret;
  FILE *fp;
  CURSOR cur;
  
  fpub_InitSoComp(lXmlhandle);
  COMP_GETPARSEPARAS(1, sflag_malloc, "内存分配开关")
  COMP_GETPARSEPARAS(2, sflag_openfile, "打开文件开关")
  COMP_GETPARSEPARAS(3, sflag_cursor, "打开游标开关")


  LOG(LM_DEBUG, Fmtmsg("  -->内存分配开关[%s],打开文件开关[%s],打开游标开关[%s]", sflag_malloc, sflag_openfile, sflag_cursor), "INFO")
  LOG(LM_STD, Fmtmsg(" [WARN]本组件只用于测试!验证流程调试功能中的内存泄漏、文件句柄、DCI SQL跟踪是否正常!!"), __func__)

  
  if ((p = (char *)malloc(1234)) == NULL)
  {
    LOG(LM_STD, Fmtmsg("  -->组件异常:内存分配失败!, err[%s]", strerror(errno)), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		

  if (sbuf[0] == '1')                   /*使用未初始化的变量!*/
  {	
  	LOG(LM_STD, Fmtmsg("未初始化的变量"), __func__);
  }	

  p[1235] = '1';                        /*堆空间:测试指针越界--可以静态检查*/
  xml_GetElement(lXmlhandle, "/sys/sysdate", sbuf, sizeof(sbuf));
  poverstack = (char *)malloc(6) ;
  strcpy(poverstack, sbuf);             /*堆空间:测试指针越界(写)-无法静态检查*/
  free(poverstack);
  
  strcpy(sbuf6, sbuf);                  /*栈空间:测试指针越界(写)-无法静态检查*/
  
  sbuf6[0] = p[1235];                   /*堆空间:测试指针越界(读)-可以静态检查*/
  p[0]     = sbuf6[7];                  /*栈空间:测试指针越界(读)-可以静态检查*/

  
  pfunc=prv_malloc(4321);
  if (sflag_malloc[0] != '1')
  {	
  	free(p);
  	free(pfunc);
  }
  else
  {
    LOG(LM_STD, Fmtmsg("  -->注意:本组件分配1234字节内存,未释放,模拟内存泄漏场景, 在ACIDE中运行测试案例-->打开内存泄漏检测项时,应该能发现本组件异常!"), __func__);
    LOG(LM_STD, Fmtmsg("  -->注意:本组件分配4321字节内存(嵌套函数),未释放,模拟内存泄漏场景, 在ACIDE中运行测试案例-->打开内存泄漏检测项时,应该能发现本组件异常!"), __func__);
  }		  

  snprintf(sbuf, sizeof(sbuf), "%s/etc/gaps.ini", getenv("HOME"));
  if ((fp = fopen(sbuf, "r")) == NULL)
  {
    LOG(LM_STD, Fmtmsg("  -->组件异常:打开文件失败, file[%s], err[%s]!", sbuf, strerror(errno)), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  if (sflag_openfile[0] != '1')
  	fclose(fp);
  else
  {
    LOG(LM_STD, Fmtmsg("  -->注意:本组件打开一个文件,未关闭,模拟句柄未关的场景, 在ACIDE中运行测试案例,应该能发现本组件异常!"), __func__);
  }		  
  
  snprintf(sbuf, sizeof(sbuf), "select count(*) from ywty_drls");
  if ((cur = DCIDeclareCursor(sbuf, DCI_STMT_LOCATOR)) == -1)  
  {
    LOG(LM_STD, Fmtmsg("  -->组件异常:执行SQL失败, sql[%s],DCIDeclareCursor err[%s]!", sbuf, DCILastError()), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  if (DCIExecute(cur) == -1)
  {
    LOG(LM_STD, Fmtmsg("  -->组件异常:执行SQL失败, sql[%s],DCIExecute err[%s]!", sbuf, DCILastError()), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  iret = DCIFetch(cur);
  if (iret < 0)
  {
    LOG(LM_STD, Fmtmsg("  -->组件异常:执行SQL失败, sql[%s],DCIFetch err[%s]!", sbuf, DCILastError()), __func__);
    DCIFreeCursor(cur);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  LOG(LM_STD, Fmtmsg(" Fetch, sql[%s], fld[0]=%s", sbuf, DCIFieldAsString(cur, 0)), __func__);

  if (sflag_cursor[0] != '1')
  	DCIFreeCursor(cur);
  else
  {
    LOG(LM_STD, Fmtmsg("  -->注意:本组件打开一个游标,未关闭,模拟游标未关的场景, 在ACIDE中运行测试案例,应该能发现本组件异常!"), __func__);
  }		  
  /*SHA跟踪不合适：
    1、其块状分配空间, 一般也不释放; 2、可能系统会用到; 
    3、6级跟踪不到，7级才行,7级会跟踪过多的系统调用过程;
  */
  if (item_set("test_key", strlen("test_key"), __func__, strlen(__func__)) == '\0')
  {
    LOG(LM_STD, Fmtmsg("  -->组件异常:SHA操作失败, item_set err[%s]!", item_get_err_msg(item_getErrorId())), __func__);
  }		

  LOG(LM_STD, Fmtmsg(" 内存泄漏测试组件完成, 请查看HTTP日志看详细信息，对于非ACIDE发起的模拟测试,有些泄漏内容也许不会显示!"), __func__);  
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}

/*
  流程引擎回调函数DEMO：
  HXMLTREE   hxml        当前上下文xml句柄
  char       *compname   当前组件名
  int        icompstat   组件执行状态
  int        computime   组件执行耗时,单位ms
*/
int func_exlog(HXMLTREE hxml, char *compname, int icompstat, int computime)
{
	char sline[255];
	if (icompstat >= 0)
	  return 0;
	snprintf(sline, sizeof(sline), "\nsystime=%s, zhqzlsh=%s, trace=%s ...\n", 
	   xml_GetElementP(hxml, "/sys/systime"),
	   xml_GetElementP(hxml, "/pub/zhqzlsh"),
	   xml_GetElementP(hxml, "/pub/traceid"));
	LOG(LM_STD, sline, __func__);
	return 0;  
}	

/************************************************************************
动态组件函数定义
组件函数名称: SGAPS_COMPEXFUNC_REG
组件名称: GAPS_COMPEXFUNC_REG
组件功能:
     GAPS平台层扩展组件：注册组件执行外挂函数
     建议在初始化流程中调用!
组件参数:

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: GAPSV4.1
程 序 员:
发布日期: 2014/7/7 11:10:40
修改日期:
参数使用示例:
************************************************************************/   
IRESULT SGAPS_COMPEXFUNC_REG(HXMLTREE lXmlhandle)
{
  fpub_InitSoComp(lXmlhandle);
	
	LOG(LM_STD, Fmtmsg(" 注册GAPS流程引擎外挂函数: %s", "func_exlog"), __func__);
	fpub_gapssfs_compexfunc_reg( (void *)func_exlog);
	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0; 
}	



