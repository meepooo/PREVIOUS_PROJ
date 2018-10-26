/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_taxtypemx_drc.eh
文件描述:tips_taxtypemx_eh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_taxtypemx
说    明:税种明细
用于登记税种明细信息
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_TAXTYPEMX_DRC_EH__
#define __TIPS_TAXTYPEMX_DRC_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TAXTYPEMX
{
  char   jyrq[8+1];
  char   jylsh[8+1];
  char   spxx[40+1];
  char   projectid[2+1];
  char   taxtypename[80+1];
  char   taxstartdate[8+1];
  char   taxenddate[8+1];
  double taxtypeamt;
  char   taxtypecode[10+1];
  char   taxtype[1+1];
  char   budgetsubjectcode[30+1];
  char   limitdate[8+1];
  char   budgetlevelcode[1+1];
  char   budgetlevelname[60+1];
  char   vicesign[35+1];
  char   detailnum[10+1];
}SDB_TIPS_TAXTYPEMX;

#define SD_DATA SDB_TIPS_TAXTYPEMX
#define	SD_MEMBERS\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jylsh,0),\
  DEFSDMEMBER(T_STRING,spxx,0),\
  DEFSDMEMBER(T_STRING,projectid,0),\
  DEFSDMEMBER(T_STRING,taxtypename,0),\
  DEFSDMEMBER(T_STRING,taxstartdate,0),\
  DEFSDMEMBER(T_STRING,taxenddate,0),\
  DEFSDMEMBER(T_DOUBLE,taxtypeamt,2),\
  DEFSDMEMBER(T_STRING,taxtypecode,0),\
  DEFSDMEMBER(T_STRING,taxtype,0),\
  DEFSDMEMBER(T_STRING,budgetsubjectcode,0),\
  DEFSDMEMBER(T_STRING,limitdate,0),\
  DEFSDMEMBER(T_STRING,budgetlevelcode,0),\
  DEFSDMEMBER(T_STRING,budgetlevelname,0),\
  DEFSDMEMBER(T_STRING,vicesign,0),\
  DEFSDMEMBER(T_STRING,detailnum,0)
  DECLAREFIELDS(SD_TIPS_TAXTYPEMX)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXTYPEMX_DRC_EH__*/
