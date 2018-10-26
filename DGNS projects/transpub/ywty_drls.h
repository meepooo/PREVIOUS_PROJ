/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
数 据 库:INFORMIX
文 件 名:ywty_drls.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:GAPS研发组
程 序 员:[Tianhc]
发布日期:2009-4-29 19:40:39 [Gen]
修    订:
修改日期:
************************************************************************
表    名:ywty_drls (YWTY_DRLS当日流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/

#ifndef __YWTY_DRLS_H__
#define __YWTY_DRLS_H__
typedef struct TDB_YWTY_DRLS
{
  char   zwrq[8+1];  /*帐务日期*/
  /*帐务日期,对应帐务主机的帐务日期*/
  int   zhqzlsh;  /*综合前置流水号*/
  /*综合前置流水号 平台自动生成的序号*/
  char   zxlsh[16+1];  /*主机流水号*/
  /*主机返回的流水号*/
  char   dsfzwrq[8+1];  /*第三方帐务日期*/
  /*第三方帐务日期 对于第三方有帐务日期的业务,需登记*/
  char   dsflsh[18+1];  /*第三方流水号*/
  /*第三方流水号*/
  char   jygzh[12+1];  /*交易跟踪号*/
  /*交易跟踪号 可能一个交易有多个子交易构成,包含多个综合前置流水*/
  int   zhqzlsh2;  /*综合前置流水号2*/
  /*综合前置流水号2 一般用于冲正、撤销等与其它记录进行关联的流水号*/
  char   sqm[6+1];  /*授权码*/
  /*授权码*/
  char   sqczy[8+1];  /*授权操作员*/
  /*授权操作员,用于需授权的交易*/
  char   sjjgbh[16+1];  /*上级机构编号*/
  /*上级机构编号,用于统计*/
  char   jgbh[16+1];  /*机构编号*/
  /*机构编号*/
  char   nbjgbs[24+1];  /*内部机构标识*/
  /*内部机构标识,平台内部机构编号*/
  char   wtjgbh[16+1];  /*委托机构编号*/
  /*委托机构编号*/
  char   wtnbjgbs[24+1];  /*委托机构内部标识*/
  /*委托机构内部标识*/
  char   czyh[8+1];  /*操作员号*/
  /*操作员号*/
  char   jdbh[16+1];  /*节点编号*/
  /*节点编号,针对ATM等渠道*/
  char   jyqd[12+1];  /*交易渠道*/
  /*交易渠道,交易的发起者(子系统名)*/
  char   jyrq[8+1];  /*交易日期*/
  /*交易日期*/
  char   jysj[6+1];  /*交易时间*/
  /*交易时间*/
  char   jydm[50+1];  /*交易代码*/
  /*交易代码,外部交易代码*/
  char   jymc[50+1];  /*交易名称*/
  /*交易名称*/
  char   ywdm[10+1];  /*业务代码*/
  /*业务代码*/
  char   xmdh[10+1];  /*项目代号*/
  /*项目代号*/
  char   khmc[80+1];  /*客户名称*/
  /*客户名称*/
  char   jyzh[32+1];  /*交易帐号*/
  /*交易帐号*/
  char   zhzl[2+1];  /*帐户种类*/
  /*帐户种类*/
  char   jyzh2[32+1];  /*对方帐号*/
  /*对方帐号:用于转帐类交易*/
  char   zhzl2[2+1];  /*对方帐户种类*/
  /*对方帐户种类*/
  char   zhjg2[32+1];  /*对方机构号*/
  /*对方机构号*/
  char   khh[20+1];  /*客户号*/
  /*客户号:主机返回*/
  char   yhh[32+1];  /*用户号*/
  /*用户号:第三方的标识号*/
  char   bzh[2+1];  /*币种号*/
  /*币种号*/
  double   jyje;  /*交易金额*/
  /*交易金额*/
  double   sxf;  /*手续费*/
  /*手续费*/
  double   gbf;  /*工本费*/
  /*工本费*/
  double   znj;  /*滞呆金*/
  /*滞呆金*/
  char   jyzt[1+1];  /*交易状态*/
  /*交易状态: 0-成功 1-失败 2-被冲正 3-取消 9-正在处理中*/
  char   xym[8+1];  /*响应码*/
  /*响应码*/
  char   xyxx[60+1];  /*响应信息*/
  /*响应信息*/
  char   jyfs[1+1];  /*交易方式*/
  /*交易方式 卡、折、现金、支票...*/
  char   jdbz[1+1];  /*借贷标识*/
  /*借贷标识 0-借 1-贷*/
  char   gdbz[1+1];  /*归档标志*/
  /*归档标志 0-不需归档 1-归档(历史流水)*/
  char   jyzl[1+1];  /*交易种类*/
  /*交易种类 1-帐务类 2-委托关系类 3-查询类 4-批量类 5-辅助类*/
  char   jzbz[1+1];  /*记帐标识*/
  /*记帐标识 0-不记帐 1-记帐(需对帐)*/
  char   qsbz[1+1];  /*清算标识*/
  /*清算标识 0-未清算 1-已清算*/
  char   kzbz[8+1];  /*扩展标识*/
  /*扩展标识 用于自定义扩展*/
  char   wbzwbs[20+1];  /*外部帐务标识*/
  /*外部帐务标识 用于记录第三方的相关信息*/
  int   trans_time;  /*交易耗时*/
  /*交易耗时 单位：ms*/
  char   byzd[128+1];  /*备用字段*/
  /*备用字段*/

}YWTY_DRLS;

#define SD_DATA  YWTY_DRLS
#define SD_MEMBERS  DEFSDMEMBER(T_STRING,  zwrq, 0),\
 DEFSDMEMBER(T_LONG,  zhqzlsh, 0),\
 DEFSDMEMBER(T_STRING,  zxlsh, 0),\
 DEFSDMEMBER(T_STRING,  dsfzwrq, 0),\
 DEFSDMEMBER(T_STRING,  dsflsh, 0),\
 DEFSDMEMBER(T_STRING,  jygzh, 0),\
 DEFSDMEMBER(T_LONG,  zhqzlsh2, 0),\
 DEFSDMEMBER(T_STRING,  sqm, 0),\
 DEFSDMEMBER(T_STRING,  sqczy, 0),\
 DEFSDMEMBER(T_STRING,  sjjgbh, 0),\
 DEFSDMEMBER(T_STRING,  jgbh, 0),\
 DEFSDMEMBER(T_STRING,  nbjgbs, 0),\
 DEFSDMEMBER(T_STRING,  wtjgbh, 0),\
 DEFSDMEMBER(T_STRING,  wtnbjgbs, 0),\
 DEFSDMEMBER(T_STRING,  czyh, 0),\
 DEFSDMEMBER(T_STRING,  jdbh, 0),\
 DEFSDMEMBER(T_STRING,  jyqd, 0),\
 DEFSDMEMBER(T_STRING,  jyrq, 0),\
 DEFSDMEMBER(T_STRING,  jysj, 0),\
 DEFSDMEMBER(T_STRING,  jydm, 0),\
 DEFSDMEMBER(T_STRING,  jymc, 0),\
 DEFSDMEMBER(T_STRING,  ywdm, 0),\
 DEFSDMEMBER(T_STRING,  xmdh, 0),\
 DEFSDMEMBER(T_STRING,  khmc, 0),\
 DEFSDMEMBER(T_STRING,  jyzh, 0),\
 DEFSDMEMBER(T_STRING,  zhzl, 0),\
 DEFSDMEMBER(T_STRING,  jyzh2, 0),\
 DEFSDMEMBER(T_STRING,  zhzl2, 0),\
 DEFSDMEMBER(T_STRING,  zhjg2, 0),\
 DEFSDMEMBER(T_STRING,  khh, 0),\
 DEFSDMEMBER(T_STRING,  yhh, 0),\
 DEFSDMEMBER(T_STRING,  bzh, 0),\
 DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
 DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
 DEFSDMEMBER(T_DOUBLE,  gbf, 2),\
 DEFSDMEMBER(T_DOUBLE,  znj, 2),\
 DEFSDMEMBER(T_STRING,  jyzt, 0),\
 DEFSDMEMBER(T_STRING,  xym, 0),\
 DEFSDMEMBER(T_STRING,  xyxx, 0),\
 DEFSDMEMBER(T_STRING,  jyfs, 0),\
 DEFSDMEMBER(T_STRING,  jdbz, 0),\
 DEFSDMEMBER(T_STRING,  gdbz, 0),\
 DEFSDMEMBER(T_STRING,  jyzl, 0),\
 DEFSDMEMBER(T_STRING,  jzbz, 0),\
 DEFSDMEMBER(T_STRING,  qsbz, 0),\
 DEFSDMEMBER(T_STRING,  kzbz, 0),\
 DEFSDMEMBER(T_STRING,  wbzwbs, 0),\
 DEFSDMEMBER(T_LONG,  trans_time, 0),\
 DEFSDMEMBER(T_STRING,  byzd, 0)


DECLAREFIELDS(SD_YWTY_DRLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YWTY_DRLS_H__*/
