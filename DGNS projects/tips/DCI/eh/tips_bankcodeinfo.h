/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_bankcodeinfo.eh
文件描述:tips_bankcodeinfo;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_bankcodeinfo (清算银行代码)
说    明:清算银行代码
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_BANKCODEINFO_EH__
#define __TIPS_BANKCODEINFO_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BANKCODEINFO
{
  char   reckbankno[12+1];              /*清算银行行号*/
              /*清算银行行号*/
  char   genbankname[60+1];              /*银行名称*/
              /*银行名称*/
  char   reckontype[1+1];              /*清算渠道*/
              /*清算渠道*/
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
}SDB_TIPS_BANKCODEINFO;

#define SD_DATA SDB_TIPS_BANKCODEINFO
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,reckbankno,0),\
  DEFSDMEMBER(T_STRING,genbankname,0),\
  DEFSDMEMBER(T_STRING,reckontype,0),\
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
	DECLAREFIELDS(SD_TIPS_BANKCODEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BANKCODEINFO_EH__*/
