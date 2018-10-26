/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_PLRWBD.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_PLRWBD (批量业务任务步点明细表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_PLRWBD_H__
#define __BATCH_PLRWBD_H__
typedef struct TDB_BATCH_PLRWBD
{
  char   pkrq[8+1];              /*批扣日期*/
              /*批扣日期(平台日期)*/
  char   ptpch[8+1];              /*平台批次号*/
              /*平台批次号*/
  int    flowsn;              /*流程执行序号*/
              /*流程执行序号*/
  char   czbd[2+1];              /*操作步点*/
              /*操作步点 0 获取数据 1 数据入库 2 数据审核 3 数据提交 4数据提回  5企业回盘  */
  char   fzbd[2+1];              /*辅助步点*/
              /*辅助步点
当操作步点为7－任务嵌套时才有效，其他步点使用00
00-待受理  09-受理中 10-待返回  19-返回中 11-已返回*/
  char   bdzt[1+1];              /*步点状态*/
              /* 0中止 1结束 2断点 3返回 4等待 9在处理中 */
  char   cljg[16+1];              /*处理机构*/
              /*处理机构*/
  char   clgy[16+1];              /*处理柜员*/
              /*处理柜员*/
  char   clksrq[8+1];              /*处理开始日期*/
              /**/
  char   clkssj[6+1];              /*处理开始时间*/
              /**/
  char   cljsrq[8+1];              /*处理结束日期*/
              /**/
  char   cljssj[6+1];              /*处理结束时间*/
              /**/
  int    clcs;              /*处理次数*/
              /**/
  char   xydm[8+1];              /*响应代码*/
              /*响应代码*/
  char   xyxx[60+1];              /*响应信息*/
              /*响应信息*/
}BATCH_PLRWBD;

#define SD_DATA  BATCH_PLRWBD
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkrq, 0),\
	DEFSDMEMBER(T_STRING,  ptpch, 0),\
	DEFSDMEMBER(T_LONG,  flowsn, 0),\
	DEFSDMEMBER(T_STRING,  czbd, 0),\
	DEFSDMEMBER(T_STRING,  fzbd, 0),\
	DEFSDMEMBER(T_STRING,  bdzt, 0),\
	DEFSDMEMBER(T_STRING,  cljg, 0),\
	DEFSDMEMBER(T_STRING,  clgy, 0),\
	DEFSDMEMBER(T_STRING,  clksrq, 0),\
	DEFSDMEMBER(T_STRING,  clkssj, 0),\
	DEFSDMEMBER(T_STRING,  cljsrq, 0),\
	DEFSDMEMBER(T_STRING,  cljssj, 0),\
	DEFSDMEMBER(T_LONG,  clcs, 0),\
	DEFSDMEMBER(T_STRING,  xydm, 0),\
	DEFSDMEMBER(T_STRING,  xyxx, 0)


	DECLAREFIELDS(SD_BATCH_PLRWBD)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_PLRWBD_H__*/
