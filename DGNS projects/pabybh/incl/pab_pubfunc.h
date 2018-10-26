/**********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:
文 件 名:ICC_PABFE.h
文件描述:系统信息宏定义头文件
项 目 组:中间业务产品发展部研发组
程 序 员:中间业务产品发展部研发组
发布时间:2013年3月12日
修 订:中间业务产品发展部研发组
修改时间:2013年3月12日
**********************************************************************/
#ifndef __PAB_PUBFUNC_H__
#define __PAB_PUBFUNC_H__

typedef struct ACCTINFO
{
  char acctno[50];
  char acctname[100];
  char mobile[15];
  char certtype[2+1];
  char certno[32+1];
  char cardtype[2+1];	
}AcctInfo;

#endif
