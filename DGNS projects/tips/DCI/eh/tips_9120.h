/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:中间业务平台
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_9120.eh
文件描述:tips_9120;结构定义数据库开发嵌C头文件
项 目 组:中间业务产品发展部研发组
程 序 员:
发布时间:2009-10-23 16:25:39 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_9120 (9120通用应答)
说    明:存储9120通用应答交易内容
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_9120_EH__
#define __TIPS_9120_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_9120
{
  char   zwrq[8+1];              /*帐务日期*/
              /**/
  int    zhqzlsh;              /*综合前置流水号*/
              /**/
  char   workdate[8+1];              /*工作日期*/
              /**/
  char   systime[6+1];              /*应答时间*/
              /**/
  char   orimsgid[20+1];              /*原报文标识号*/
              /**/
  char   orimsgno[4+1];              /*原报文编号*/
              /**/
  char   result[5+1];              /*处理结果*/
              /**/
  char   addword[60+1];              /*附言*/
              /**/
  char   information[1024+1];              /*详细信息*/
              /**/
}SDB_TIPS_9120;

#define SD_DATA SDB_TIPS_9120
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,systime,0),\
  DEFSDMEMBER(T_STRING,orimsgid,0),\
  DEFSDMEMBER(T_STRING,orimsgno,0),\
  DEFSDMEMBER(T_STRING,result,0),\
  DEFSDMEMBER(T_STRING,addword,0),\
  DEFSDMEMBER(T_STRING,information,0)
	DECLAREFIELDS(SD_TIPS_9120)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_9120_EH__*/
