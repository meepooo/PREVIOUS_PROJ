/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_taxsubjectlist_drc.eh
文件描述:tips_taxsubjectlist;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_taxsubjectlist
说    明:税目明细
用于登记税目明细信息
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_TAXSUBJECTLIST_DRC_EH__
#define __TIPS_TAXSUBJECTLIST_DRC_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct SDB_TIPS_TAXSUBJECTLIST
{
  char   jyrq[8+1];
  char   jylsh[8+1];
  char   projectid[2+1];
  char   detailno[10+1];
  char   taxsubjectcode[20+1];
  char   taxsubjectname[60+1];
  char   taxnumber[10+1];
  double taxamt;
  double facttaxamt;
  double taxrate;
  double exptaxamt;
  double discounttaxamt;
  char   remark1[10+1];
  char   remark2[20+1];
  char   remark3[50+1];
  char   remark4[100+1];
  char   remark5[200+1];
}SDB_TIPS_TAXSUBJECTLIST;

#define SD_DATA SDB_TIPS_TAXSUBJECTLIST
#define	SD_MEMBERS\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jylsh,0),\
  DEFSDMEMBER(T_STRING,projectid,0),\
  DEFSDMEMBER(T_STRING,detailno,0),\
  DEFSDMEMBER(T_STRING,taxsubjectcode,0),\
  DEFSDMEMBER(T_STRING,taxsubjectname,0),\
  DEFSDMEMBER(T_STRING,taxnumber,0),\
  DEFSDMEMBER(T_DOUBLE,taxamt,2),\
  DEFSDMEMBER(T_DOUBLE,facttaxamt,2),\
  DEFSDMEMBER(T_DOUBLE,taxrate,2),\
  DEFSDMEMBER(T_DOUBLE,exptaxamt,2),\
  DEFSDMEMBER(T_DOUBLE,discounttaxamt,2),\
  DEFSDMEMBER(T_STRING,remark1,0),\
  DEFSDMEMBER(T_STRING,remark2,0),\
  DEFSDMEMBER(T_STRING,remark3,0),\
  DEFSDMEMBER(T_STRING,remark4,0),\
  DEFSDMEMBER(T_STRING,remark5,0)
  DECLAREFIELDS(SD_TIPS_TAXSUBJECTLIST)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXSUBJECTLIST_DRC_EH__*/
