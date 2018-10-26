/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_trecodeinfo.eh
文件描述:tips_trecodeinfo;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_trecodeinfo (国库代码)
说    明:国库代码

************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_TRECODEINFO_EH__
#define __TIPS_TRECODEINFO_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TRECODEINFO
{
  char   trecode[10+1];              /*国库代码*/
              /*国库代码*/
  char   trename[60+1];              /*国库名称*/
              /*国库名称*/
  char   trelevel[1+1];              /*国库级次*/
              /*国库级次*/
  char   paybankno[12+1];              /*支付行号*/
              /*支付行号*/
  char   reckontrecode[10+1];              /*清算国库代码*/
              /*清算国库代码*/
  char   uptrecode[10+1];              /*管理国库代码*/
              /*管理国库代码*/
  char   ofprovtrea[10+1];              /*所属省分库代码*/
              /*所属省分库代码*/
  char   ofcitytrea[10+1];              /*所属中心支库代码*/
              /*所属中心支库代码*/
  char   ofcountytrea[10+1];              /*所属县支库代码*/
              /*所属县支库代码*/
  char   ofnodecode[12+1];              /*所属节点代码*/
              /*所属节点代码*/
  char   address[80+1];              /*地址*/
              /*地址*/
  char   postalcode[6+1];              /*邮政编码*/
              /*邮政编码*/
  char   peoplename[10+1];              /*联系人姓名*/
              /*联系人姓名*/
  char   peoplephone[15+1];              /*联系人座机*/
              /*联系人座机*/
  char   peoplemobile[11+1];              /*联系人手机*/
              /*联系人手机*/
  char   email[60+1];              /*电子邮箱*/
              /*电子邮箱*/
  char   opersign[1+1];              /*操作标志*/
              /*操作标志
                用于标识数据更新的类型，详见附录代码表*/
  char   effectdate[10+1];              /*生效日期*/
              /*生效日期
                此条记录的生效日期，更新类型为增加时，为增加日期；更新类型为更正时，为更新日期；更新类型为删除时，为失效日期*/
  char   updatearea[10+1];              /*更新范围*/
              /*更新范围
                国库代码*/
}SDB_TIPS_TRECODEINFO;

#define SD_DATA SDB_TIPS_TRECODEINFO
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,trecode,0),\
  DEFSDMEMBER(T_STRING,trename,0),\
  DEFSDMEMBER(T_STRING,trelevel,0),\
  DEFSDMEMBER(T_STRING,paybankno,0),\
  DEFSDMEMBER(T_STRING,reckontrecode,0),\
  DEFSDMEMBER(T_STRING,uptrecode,0),\
  DEFSDMEMBER(T_STRING,ofprovtrea,0),\
  DEFSDMEMBER(T_STRING,ofcitytrea,0),\
  DEFSDMEMBER(T_STRING,ofcountytrea,0),\
  DEFSDMEMBER(T_STRING,ofnodecode,0),\
  DEFSDMEMBER(T_STRING,address,0),\
  DEFSDMEMBER(T_STRING,postalcode,0),\
  DEFSDMEMBER(T_STRING,peoplename,0),\
  DEFSDMEMBER(T_STRING,peoplephone,0),\
  DEFSDMEMBER(T_STRING,peoplemobile,0),\
  DEFSDMEMBER(T_STRING,email,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_TRECODEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TRECODEINFO_EH__*/
