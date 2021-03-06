/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_budgetsubject.eh
文件描述:tips_budgetsubject;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_budgetsubject (预算科目代码)
说    明:预算科目代码
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_BUDGETSUBJECT_EH__
#define __TIPS_BUDGETSUBJECT_EH__

#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BUDGETSUBJECT
{
  char   budgetsubjectcode[30+1];              /*预算科目代码*/
              /*预算科目代码*/
  char   budgetsubjectname[60+1];              /*预算科目名称*/
              /*预算科目名称*/
  char   subjecttype[1+1];              /*科目类型*/
              /*科目类型*/
  char   iesign[1+1];              /*收支标志*/
              /*收支标志*/
  char   budgetattrib[1+1];              /*科目属性*/
              /*科目属性*/
  char   opersign[1+1];              /*操作标志*/
              /*操作标志
                用于标识数据更新的类型，详见附录代码表*/
  char   effectdate[10+1];              /*生效日期*/
              /*生效日期
                此条记录的生效日期，更新类型为增加时，为增加日期；更新类型为更正时，为更新日期；更新类型为删除时，为失效日期*/
  char   updatearea[10+1];              /*更新范围*/
              /*更新范围
                国库代码*/
}SDB_TIPS_BUDGETSUBJECT;

#define SD_DATA SDB_TIPS_BUDGETSUBJECT
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,budgetsubjectcode,0),\
  DEFSDMEMBER(T_STRING,budgetsubjectname,0),\
  DEFSDMEMBER(T_STRING,subjecttype,0),\
  DEFSDMEMBER(T_STRING,iesign,0),\
  DEFSDMEMBER(T_STRING,budgetattrib,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_BUDGETSUBJECT)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BUDGETSUBJECT_EH__*/
