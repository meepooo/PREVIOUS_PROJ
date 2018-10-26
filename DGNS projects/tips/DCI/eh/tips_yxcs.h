/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_yxcs.eh
文件描述:tips_yxcs;结构定义数据库开发嵌C头文件
项 目 组:金融产品三部TIPS研发组
程 序 员:tuql
发布时间:2009-10-23 13:09:30 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_yxcs (TIPS运行参数)
说    明:TIPS运行参数
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_YXCS_EH__
#define __TIPS_YXCS_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_YXCS
{
  char   zwrq[8+1];              /*帐务日期*/
              /**/
  int    zhqzlsh;              /*综合前置流水号*/
              /**/
  char   workdate[8+1];              /*工作日期*/
              /**/
  char   paramtypeno[4+1];              /*参数类型编号*/
              /*参数类型，目前定义的有102（TIPS运行时序），103（交易数据查询期限），104（业务受理窗口）*/
  char   paramdescrip[80+1];              /*参数类型描述*/
              /**/
  char   detailno[16+1];              /*明细序号*/
              /**/
  char   detaildescri[80+1];              /*明细序号描述*/
              /**/
  char   detailvalue[60+1];              /*参数取值*/
              /**/
}SDB_TIPS_YXCS;

#define SD_DATA SDB_TIPS_YXCS
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,paramtypeno,0),\
  DEFSDMEMBER(T_STRING,paramdescrip,0),\
  DEFSDMEMBER(T_STRING,detailno,0),\
  DEFSDMEMBER(T_STRING,detaildescri,0),\
  DEFSDMEMBER(T_STRING,detailvalue,0)
	DECLAREFIELDS(SD_TIPS_YXCS)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_YXCS_EH__*/
