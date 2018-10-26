/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_yhsbcx.eh
文件描述:tips_yhsbcx;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_yhsbcx (银行申报查询表)
说    明:税收银行申报查询表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_YHSBCX_EH__
#define __TIPS_YHSBCX_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_YHSBCX
{
  char   zwrq[8+1];              /*帐务日期*/
              /*对应柜面申报查询、申报交易的委托日期*/
  int    zhqzlsh;              /*综合前置流水号*/
              /*对应柜面申报查询、申报交易的查询序号*/
  char   jyqd[10+1];              /*交易渠道*/
              /*用于区分发起交易的渠道
                tips   tips发起
                hx9996 hx9996转发 */
  char   dqdh[10+1];              /*地区代号*/
              /**/
  char   jgdh[10+1];              /*机构代号*/
              /**/
  char   jygy[16+1];              /*交易柜员*/
              /**/
  char   zddh[16+1];              /*终端代号*/
              /**/
  char   workdate[8+1];              /*工作日期*/
              /*tips工作日期*/
  char   jyrq[8+1];              /*交易日期*/
              /*交易日期*/
  char   jysj[8+1];              /*交易时间*/
              /*交易时间*/
  char   bankno[12+1];              /*商业银行行号*/
              /*商业银行行号
                发起查询的清算行的支付系统行号*/
  char   entrustdate[8+1];              /*委托日期*/
              /*实时扣款请求发起日期*/
  char   queryno[8+1];              /*查询序号*/
              /*查询序号
                同综合前置流水号
                */
  char   payopbkcode[12+1];              /*付款开户行行号*/
              /*付款开户行行号
                指纳税人开户行行号，征收机关必须填写*/
  char   bankname[60+1];              /*开户行名称*/
              /*开户行名称*/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /*征收机关代码*/
  char   corpcode[20+1];              /*企业代码*/
              /*收款单位代码
                商业银行经收时是指收款人开户行行号；
                国库经收时是指收款国库代码*/
  char   taxpaycode[20+1];              /*纳税人编码*/
              /*纳税人编码*/
  char   outerlevyno[20+1];              /*外部申报电子序号*/
              /*外部申报电子序号*/
  char   addword[12+1];              /*附言*/
              /*附言*/
  double  jyje;              /*交易金额*/
              /*交易金额
                本次实时扣款的总金额*/
  int    detailnum;              /*交易明细数*/
              /**/
  char   result[5+1];              /*处理结果*/
              /*处理结果
                返回给TIPS的处理结果*/
  char   spxxwjm[40+1];              /*税票信息文件名*/
              /*税种明细
                payment1001以XML方式记录，用于补打税票*/
}SDB_TIPS_YHSBCX;

#define SD_DATA SDB_TIPS_YHSBCX
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,jyqd,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,bankno,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,queryno,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,bankname,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,corpcode,0),\
  DEFSDMEMBER(T_STRING,taxpaycode,0),\
  DEFSDMEMBER(T_STRING,outerlevyno,0),\
  DEFSDMEMBER(T_STRING,addword,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_LONG,detailnum,0),\
  DEFSDMEMBER(T_STRING,result,0),\
  DEFSDMEMBER(T_STRING,spxxwjm,0)
	DECLAREFIELDS(SD_TIPS_YHSBCX)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_YHSBCX_EH__*/
