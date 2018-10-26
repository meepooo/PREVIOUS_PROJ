/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_lxrxx.eh
文件描述:tips_lxrxx;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_lxrxx (联系人信息表)
说    明:联系人信息表

************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_LXRXX_EH__
#define __TIPS_LXRXX_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_LXRXX
{
  char   dwdm[20+1];              /*单位代码*/
              /*单位代码
                */
  char   dwmc[80+1];              /*单位名称*/
              /*单位名称 */
  char   glgk[100+1];              /*管理国库*/
              /*管理国库*/
  char   lxr[20+1];              /*联系人*/
              /*联系人*/
  char   lxdh[40+1];              /*联系电话*/
              /*联系电话*/
  char   bz[200+1];              /*备注*/
              /*备注*/
}SDB_TIPS_LXRXX;

#define SD_DATA SDB_TIPS_LXRXX
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dwdm,0),\
  DEFSDMEMBER(T_STRING,dwmc,0),\
  DEFSDMEMBER(T_STRING,glgk,0),\
  DEFSDMEMBER(T_STRING,lxr,0),\
  DEFSDMEMBER(T_STRING,lxdh,0),\
  DEFSDMEMBER(T_STRING,bz,0)
	DECLAREFIELDS(SD_TIPS_LXRXX)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_LXRXX_EH__*/
