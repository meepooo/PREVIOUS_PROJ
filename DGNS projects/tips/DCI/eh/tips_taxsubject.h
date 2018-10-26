/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_taxsubject.eh
文件描述:tips_taxsubject;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_taxsubject (税目代码)
说    明:税目代码
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_TAXSUBJECT_EH__
#define __TIPS_TAXSUBJECT_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TAXSUBJECT
{
  char   taxsubjectcode[20+1];              /*税目代码*/
              /*税目代码*/
  char   taxorgtype[1+1];              /*征收机关类型*/
              /*征收机关类型*/
  char   taxsubjectname[60+1];              /*税目名称*/
              /*税目名称*/
  char   description[80+1];              /*描述*/
              /*描述*/
  char   opersign[1+1];              /*操作标志*/
              /*操作标志
                用于标识数据更新的类型，详见附录代码表*/
  char   effectdate[10+1];              /*生效日期*/
              /*生效日期
                此条记录的生效日期，更新类型为增加时，为增加日期；更新类型为更正时，为更新日期；更新类型为删除时，为失效日期*/
  char   updatearea[10+1];              /*更新范围*/
              /*更新范围
                国库代码*/
}SDB_TIPS_TAXSUBJECT;

#define SD_DATA SDB_TIPS_TAXSUBJECT
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,taxsubjectcode,0),\
  DEFSDMEMBER(T_STRING,taxorgtype,0),\
  DEFSDMEMBER(T_STRING,taxsubjectname,0),\
  DEFSDMEMBER(T_STRING,description,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_TAXSUBJECT)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXSUBJECT_EH__*/
