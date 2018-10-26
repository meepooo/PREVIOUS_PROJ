/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_jygy2gkzfhh.eh
文件描述:tips_jygy2gkzfhh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:21 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_jygy2gkzfhh (交易柜员和国库支付行号对照表)
说    明:交易柜员和国库支付行号对照表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_JYGY2GKZFHH_EH__
#define __TIPS_JYGY2GKZFHH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_JYGY2GKZFHH
{
  char   dqdh[10+1];              /*地区代号*/
              /*地区代号*/
  char   jgdh[10+1];              /*机构代号*/
              /*机构代号*/
  char   czyh[16+1];              /*交易柜员*/
              /*操作员号*/
  char   zddh[16+1];              /*终端代号*/
              /**/
  int    czyjb;              /*柜员级别*/
              /*柜员级别
                由数据字典-"system_gyjb"维护
                */
  char   czymc[20+1];              /*柜员名称*/
              /*操作员名称*/
  char   payeebankno[12+1];              /*国库支付行号*/
              /**/
}SDB_TIPS_JYGY2GKZFHH;

#define SD_DATA SDB_TIPS_JYGY2GKZFHH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,czyh,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_LONG,czyjb,0),\
  DEFSDMEMBER(T_STRING,czymc,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0)
	DECLAREFIELDS(SD_TIPS_JYGY2GKZFHH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_JYGY2GKZFHH_EH__*/
