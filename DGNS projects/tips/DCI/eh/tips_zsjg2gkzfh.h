/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_zsjg2gkzfh.eh
文件描述:tips_zsjg2gkzfh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_zsjg2gkzfh (征收机关和国库支付行对照表)
说    明:征收机关和国库支付行对照表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_ZSJG2GKZFH_EH__
#define __TIPS_ZSJG2GKZFH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_ZSJG2GKZFH
{
  char   dqdh[10+1];              /*地区代号*/
              /**/
  char   jgdh[10+1];              /*机构代号*/
              /**/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /**/
  char   taxorgtype[1+1];              /*征收机关类型*/
              /*1-国税 2-地税
                3-海关 4-财政
                5-工商 6-社保*/
  unknow  taxorgname;              /*征收机关名称*/
              /**/
  char   payeebankno[12+1];              /*国库支付行号*/
              /**/
  unknow  trename;              /*国库名称*/
              /**/
  char   xgrq[8+1];              /*修改日期*/
              /**/
  char   xgsj[8+1];              /*修改时间*/
              /*修改时间*/
  char   xggy[10+1];              /*修改柜员*/
              /*修改柜员*/
}SDB_TIPS_ZSJG2GKZFH;

#define SD_DATA SDB_TIPS_ZSJG2GKZFH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,taxorgtype,0),\
  unknow  taxorgname\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  unknow  trename\
  DEFSDMEMBER(T_STRING,xgrq,0),\
  DEFSDMEMBER(T_STRING,xgsj,0),\
  DEFSDMEMBER(T_STRING,xggy,0)
	DECLAREFIELDS(SD_TIPS_ZSJG2GKZFH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_ZSJG2GKZFH_EH__*/
