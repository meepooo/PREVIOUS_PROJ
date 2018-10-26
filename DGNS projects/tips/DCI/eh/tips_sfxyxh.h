/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_sfxyxh.eh
文件描述:tips_sfxyxh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_sfxyxh (三方协议序号表)
说    明:控制序号，用于生成协议序号
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_SFXYXH_EH__
#define __TIPS_SFXYXH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SFXYXH
{
  char   xh1[10+1];              /*序号1*/
              /*序号1*/
  char   xh2[12+1];              /*序号2*/
              /*序号2*/
  char   xh3[10+1];              /*序号3*/
              /*序号3*/
}SDB_TIPS_SFXYXH;

#define SD_DATA SDB_TIPS_SFXYXH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,xh1,0),\
  DEFSDMEMBER(T_STRING,xh2,0),\
  DEFSDMEMBER(T_STRING,xh3,0)
	DECLAREFIELDS(SD_TIPS_SFXYXH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SFXYXH_EH__*/
