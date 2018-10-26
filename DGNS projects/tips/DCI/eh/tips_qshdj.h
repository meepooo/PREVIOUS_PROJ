/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_qshdj.eh
文件描述:tips_qshdj;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_qshdj (商业银行清算行登记表)
说    明:付款行登记表
机构对应的帐号,针对不同的机构,
登记贷方帐号及挂帐账号所使用的业务代号/序号
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_QSHDJ_EH__
#define __TIPS_QSHDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_QSHDJ
{
  char   dqdh[10+1];              /*地区代号*/
              /*地区代号*/
  char   jgdh[10+1];              /*机构代号*/
              /*机构编号*/
  char   yybs[30+1];              /*应用标识*/
              /*应用标识
                可能在不同的使用中,机构对应多个帐号使用
                缺省为TIPS*/
  char   dfzh[32+1];              /*贷方账号*/
              /*贷方账号业务代号
                用于主机扣款交易及挂帐交易计算帐号
                */
  char   gzzh[32+1];              /*挂帐账号*/
              /*挂帐账号业务代号
                用于挂帐交易(差错调整),计算账号*/
  char   paybkcode[12+1];              /*付款行行号*/
              /*机构对应TIPS系统中的支付系统行号(清算行)
                */
  char   paybkname[12+1];              /*付款行名称*/
              /*机构对应TIPS系统中的支付系统行名称
                */
  char   note[50+1];              /*说明信息*/
              /*说明信息*/
  char   modidate[8+1];              /*操作日期*/
              /*操作日期*/
  char   modiinfo[50+1];              /*操作说明信息*/
              /*操作说明信息
                系统自动生成最后一次操作的信息*/
  char   kzbz[8+1];              /*扩展标志*/
              /*扩展标志
                用于自定义扩展*/
  char   byzd[80+1];              /*备用字段*/
              /*备用字段*/
}SDB_TIPS_QSHDJ;

#define SD_DATA SDB_TIPS_QSHDJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,yybs,0),\
  DEFSDMEMBER(T_STRING,dfzh,0),\
  DEFSDMEMBER(T_STRING,gzzh,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,paybkname,0),\
  DEFSDMEMBER(T_STRING,note,0),\
  DEFSDMEMBER(T_STRING,modidate,0),\
  DEFSDMEMBER(T_STRING,modiinfo,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_QSHDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_QSHDJ_EH__*/
