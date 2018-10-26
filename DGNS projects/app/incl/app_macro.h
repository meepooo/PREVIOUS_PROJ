/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:太原交行中间业务平台项目
版    本:V3.0
操作系统:AIX5.2+ORACLE+ANSI.C
文件名称:agent_macro.h
文件描述:代理业务平台宏定义文件
项 目 组:代理业务平台项目组
程 序 员:
发布日期:2007.06.26
修    订:
修改日期:
*********************************************************************/
#if !defined(__APP_MACRO__H)
#define __APP_MACRO__H

/*是否是闰年*/
#define RYEAR(a) ((a) % 4 == 0 && (a) % 100 != 0 || (a) % 400 == 0)
/*一年的天数*/
#define YEARDAYS(a) RYEAR(a)?366:365
/*二月的天数*/
#define MON2DAYS(a) RYEAR(a)?29:28
/*一个月的天数*/
#define RMONTHDAYS(a, b) ((a) == 2?(MON2DAYS(b)):((a) < 8 && (a) % 2 == 0 || (a) >= 8 && (a) % 2 != 0)?30:31)

#define APP_CPDM_MAXSERIAL   99999999             /* 产品业务流水号最大值 */
#define APP_DEFAULT_CUR      "CNY"                  /* 默认币种 */
#define SOCOMPBUILDNO BUILDDATETIME
	
#endif

