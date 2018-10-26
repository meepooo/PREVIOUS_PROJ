/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_struct_report.eh
文件描述:tips_struct_report;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-12-16 13:47:16 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_struct_report (报表结构体)
说    明:此表并非表，而是结构体，为了能通过PD生成头文件而增加的"表",用于出报表中,SYW_TIPS_REPORT.ec
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_STRUCT_REPORT_EH__
#define __TIPS_STRUCT_REPORT_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_STRUCT_REPORT
{
  char   zwrq[8+1];              /*帐务日期*/
              /**/
  int    zhqzlsh;              /*综合前置流水号*/
              /**/
  char   payacct[32+1];              /*付款账号*/
              /**/
  char   handorgname[200+1];              /*缴款单位名称*/
              /**/
  double  jyje;              /*交易金额*/
              /**/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /**/
  char   taxvouno[18+1];              /*税票号码*/
              /**/
  char   jyzt[1+1];              /*交易状态*/
              /**/
  char   chkdate[8+1];              /*对账日期*/
              /**/
  char   chkacctord[4+1];              /*对账批次号*/
              /**/
  char   jygy[16+1];              /*交易柜员*/
              /**/
  char   xyxx[60+1];              /*响应信息*/
              /**/
  char   protocolno[60+1];              /*协议书号*/
              /**/
}SDB_TIPS_STRUCT_REPORT;

#define SD_DATA SDB_TIPS_STRUCT_REPORT
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,handorgname,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,taxvouno,0),\
  DEFSDMEMBER(T_STRING,jyzt,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,protocolno,0)
	DECLAREFIELDS(SD_TIPS_STRUCT_REPORT)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_STRUCT_REPORT_EH__*/
