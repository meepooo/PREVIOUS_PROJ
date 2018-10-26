/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_gkzfh2qsh.eh
文件描述:tips_gkzfh2qsh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_gkzfh2qsh (国库支付行和商业银行清算行对照表)
说    明:国库支付行和兴业银行清算行对照表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_GKZFH2QSH_EH__
#define __TIPS_GKZFH2QSH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_GKZFH2QSH
{
  char   payeebankno[12+1];              /*国库支付行号*/
              /*国库代码*/
  /*unknow  trename;              国库名称*/
  char   trename[128+1];
              /**/
  char   paybkcode[12+1];              /*付款行行号*/
              /*付款行行号
                商业银行清算行
                */
	/* unknow  paybkname;              付款行名称*/
  char  paybkname[60+1];
  char  payeeacct[32+1];
  char  payeename[60+1];
              /**/
  char   xgrq[8+1];              /*修改日期*/
              /*修改日期*/
  char   xgsj[8+1];              /*修改时间*/
              /*修改时间*/
  char   xggy[10+1];              /*修改柜员*/
              /*修改柜员*/
}SDB_TIPS_GKZFH2QSH;

#define SD_DATA SDB_TIPS_GKZFH2QSH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,trename,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,paybkname,0),\
  DEFSDMEMBER(T_STRING,payeeacct,0),\
  DEFSDMEMBER(T_STRING,payeename,0),\
  DEFSDMEMBER(T_STRING,xgrq,0),\
  DEFSDMEMBER(T_STRING,xgsj,0),\
  DEFSDMEMBER(T_STRING,xggy,0)

	DECLAREFIELDS(SD_TIPS_GKZFH2QSH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_GKZFH2QSH_EH__*/
