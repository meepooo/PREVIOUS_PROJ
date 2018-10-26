/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_PLRW.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_PLRW (批量业务任务表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_PLRW_H__
#define __BATCH_PLRW_H__
typedef struct TDB_BATCH_PLRW
{
  char   pkrq[8+1];              /*批扣日期*/
              /*批扣日期(平台日期)*/
  char   ptpch[8+1];              /*平台批次号*/
              /*平台批次号*/
  char   taskpri[3+1];              /*任务优先级*/
              /*任务优先级*/
  char   shpch[32+1];              /*商户批次号*/
              /*商户批次号*/
  char   zjpch[32+1];              /*主机批次号*/
              /*主机批次号*/
  char   ywbh[16+1];              /*业务编号*/
              /*业务编号*/
  char   dwbh[16+1];              /*单位编号*/
              /*单位编号*/
  char   tjrq[8+1];              /*提交日期*/
              /*外围提交任务的日期*/
  char   tjsj[6+1];              /*提交时间*/
              /*提交时间*/
  char   clrq[8+1];              /*处理日期*/
              /*处理结束日期*/
  char   clsj[6+1];              /*处理时间*/
              /*处理时间*/
  double  zje;              /*总金额*/
              /*请求总金额（任务）*/
  int    zbs;              /*总笔数*/
              /*请求总笔数（任务）*/
  double  sjzje;              /*实际总金额*/
              /*实际总金额（文件内）*/
  int    sjzbs;              /*实际总笔数*/
              /*实际总笔数（文件内）*/
  double  cgzje;              /*成功总金额*/
              /*成功总金额*/
  int    cgzbs;              /*成功总笔数*/
              /*成功总笔数*/
  double  sbzje;              /*失败总金额*/
              /*失败总金额*/
  int    sbzbs;              /*失败总笔数*/
              /*失败总笔数*/
  double  sxfje;              /*手续费金额*/
              /*手续费金额*/
  int    xkhbs;              /*新开户笔数*/
              /*新开户笔数*/
  double  xkhje;              /*新开户金额*/
              /*新开户金额*/
  char   lpwjm[60+1];              /*商户来盘文件名*/
              /*商户来盘文件名*/
  char   sczjwjm[60+1];              /*上传主机文件名*/
              /*上传主机文件名*/
  char   zjhfwjm[60+1];              /*主机回复文件名*/
              /*主机回复文件名*/
  char   shcgwjm[60+1];              /*回复商户成功文件名*/
              /*回复商户成功文件名（回盘文件名）*/
  char   shsbwjm[60+1];              /*回复商户失败文件名*/
              /*回复商户失败文件名*/
  char   dqbd[2+1];              /*当前步点*/
              /*操作步点 0 获取数据 1 数据入库 2 数据校验 3 提交主机 4主机提回  5回盘*/
  char   fzbd[2+1];              /*辅助步点*/
              /*辅助步点
当操作步点为7－任务嵌套时才有效，其他步点使用00
00-待受理  09-受理中 10-待返回  19-返回中 11-已返回*/
  char   bdzt[1+1];              /*步点状态*/
              /* 0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正*/
  char   rwzt[1+1];              /*任务状态*/
              /* 0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正*/
  char   xydm[8+1];              /*响应代码*/
              /*响应代码*/
  char   xyxx[60+1];              /*响应信息*/
              /*响应信息*/
  char   bqtpkrq[8+1];              /*被嵌套批扣日期*/
              /*被嵌套批扣日期*/
  char   bqtptpch[8+1];              /*被嵌套平台批次号*/
              /*被嵌套平台批次号*/
  char   qtbz[1+1];              /*嵌套标志*/
              /*嵌套标志*/
  char   qtpkrq[8+1];              /*嵌套批扣日期*/
              /*嵌套批扣日期*/
  char   qtptpch[8+1];              /*嵌套平台批次号*/
              /*嵌套平台批次号*/
}BATCH_PLRW;

#define SD_DATA  BATCH_PLRW
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkrq, 0),\
	DEFSDMEMBER(T_STRING,  ptpch, 0),\
	DEFSDMEMBER(T_STRING,  taskpri, 0),\
	DEFSDMEMBER(T_STRING,  shpch, 0),\
	DEFSDMEMBER(T_STRING,  zjpch, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  tjrq, 0),\
	DEFSDMEMBER(T_STRING,  tjsj, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_DOUBLE,  zje, 2),\
	DEFSDMEMBER(T_LONG,  zbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sjzje, 2),\
	DEFSDMEMBER(T_LONG,  sjzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  cgzje, 2),\
	DEFSDMEMBER(T_LONG,  cgzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sbzje, 2),\
	DEFSDMEMBER(T_LONG,  sbzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxfje, 2),\
	DEFSDMEMBER(T_LONG,  xkhbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  xkhje, 2),\
	DEFSDMEMBER(T_STRING,  lpwjm, 0),\
	DEFSDMEMBER(T_STRING,  sczjwjm, 0),\
	DEFSDMEMBER(T_STRING,  zjhfwjm, 0),\
	DEFSDMEMBER(T_STRING,  shcgwjm, 0),\
	DEFSDMEMBER(T_STRING,  shsbwjm, 0),\
	DEFSDMEMBER(T_STRING,  dqbd, 0),\
	DEFSDMEMBER(T_STRING,  fzbd, 0),\
	DEFSDMEMBER(T_STRING,  bdzt, 0),\
	DEFSDMEMBER(T_STRING,  rwzt, 0),\
	DEFSDMEMBER(T_STRING,  xydm, 0),\
	DEFSDMEMBER(T_STRING,  xyxx, 0),\
	DEFSDMEMBER(T_STRING,  bqtpkrq, 0),\
	DEFSDMEMBER(T_STRING,  bqtptpch, 0),\
	DEFSDMEMBER(T_STRING,  qtbz, 0),\
	DEFSDMEMBER(T_STRING,  qtpkrq, 0),\
	DEFSDMEMBER(T_STRING,  qtptpch, 0)
		
	DECLAREFIELDS(SD_BATCH_PLRW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_PLRW_H__*/
