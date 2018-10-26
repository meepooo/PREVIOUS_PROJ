/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_trepayfiledetail_drc.h
文件描述:tips_trepayfiledetail_eh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2017-5-31 15:56:00 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_trepayfiledetail_drc.h
说    明:TIPS集中支付文件明细
用于登记TIPS集中支付明细信息
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_TREPAYFILEDETAIL_DRC_EH__
#define __TIPS_TREPAYFILEDETAIL_DRC_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TREPAYFILEDETAIL
{
  char   trandate[8+1];
  long   transeq;
  long   seqno;
  char   bdgorgcode[15+1];
  char   funcsbtcode[30+1];
  char   ecnomicsubjectcode[30+1];
  double   amt;
  char   acctprop[2+1];
  char   remark1[10+1];
  char   remark2[20+1];
  char   remark3[50+1];
  char   remark4[100+1];
  char   remark5[200+1];
}SDB_TIPS_TREPAYFILEDETAIL;

#define SD_DATA SDB_TIPS_TREPAYFILEDETAIL
#define	SD_MEMBERS\
  DEFSDMEMBER(T_STRING,trandate,0),\
  DEFSDMEMBER(T_LONG,transeq,2),\
  DEFSDMEMBER(T_LONG,seqno,2),\
  DEFSDMEMBER(T_STRING,bdgorgcode,0),\
  DEFSDMEMBER(T_STRING,funcsbtcode,0),\
  DEFSDMEMBER(T_STRING,ecnomicsubjectcode,0),\
  DEFSDMEMBER(T_DOUBLE,amt,2),\
  DEFSDMEMBER(T_STRING,acctprop,0),\
  DEFSDMEMBER(T_STRING,remark1,0),\
  DEFSDMEMBER(T_STRING,remark2,0),\
  DEFSDMEMBER(T_STRING,remark3,0),\
  DEFSDMEMBER(T_STRING,remark4,0),\
  DEFSDMEMBER(T_STRING,remark5,0)
  DECLAREFIELDS(SD_TIPS_TREPAYFILEDETAIL)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TREPAYFILEDETAIL_DRC_EH__*/
