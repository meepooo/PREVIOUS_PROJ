/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_PZXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_PZXX (凭证内容信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_PZXX_H__
#define __APP_PZXX_H__
typedef struct TDB_APP_PZXX
{
  char   ptrq[8+1];              /*平台日期*/
              /*平台日期 产生凭证的交易平台日期yyyymmdd*/
  int    ptls;              /*平台流水号*/
              /*平台流水号*/
  int    pzxh;              /*凭证序号*/
              /*凭证序号*/
  int    ywls;              /*业务流水号*/
              /*业务流水*/
  char   ywrq[8+1];              /*业务日期*/
              /*业务日期*/
  char   yybs[8+1];              /*应用标识*/
              /*应用标识*/
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   yhbh[32+1];              /*用户编号*/
              /*用户编号*/
  char   yhbsh[32+1];              /*客户标识号*/
              /*客户标识号*/
  char   khmc[80+1];              /*客户名称*/
              /*客户名称*/
  char   yhzh[32+1];              /*银行帐号*/
              /*银行帐号*/
  double  jyje;              /*交易金额*/
              /*交易金额*/
  double  jyje2;              /*交易金额2*/
              /*交易金额2*/
  double  jyje3;              /*交易金额3*/
              /*交易金额3*/
  double  sxf;              /*手续费*/
              /*手续费*/
  char   jfzq[16+1];              /*缴费周期*/
              /*缴费周期*/
  char   qsrq[10+1];              /*起始日期*/
              /*起始日期*/
  char   jsrq[10+1];              /*结束日期*/
              /*结束日期*/
  char   sjdm[10+1];              /*税局代码*/
              /*税局代码*/
  char   qdbs[3+1];              /*交易渠道*/
              /*交易渠道*/
  char   pzzl[3+1];              /*凭证种类*/
              /*凭证种类*/
  char   pzhm[32+1];              /*凭证号码*/
              /*凭证号码*/
  char   pzsm[40+1];              /*凭证说明*/
              /*凭证说明*/
  char   dyrq[8+1];              /*打印日期*/
              /*打印日期*/
  char   dysj[6+1];              /*打印时间*/
              /*打印时间*/
  int    dyls;              /*打印流水号*/
              /*打印流水号*/
  char   dyjg[16+1];              /*打印机构*/
              /*打印机构*/
  char   dygy[16+1];              /*打印柜员*/
              /*打印柜员*/
  int    dycs;              /*打印次数*/
              /*打印次数*/
  char   jlbz[1+1];              /*记录标志*/
              /*记录标志 0正常 1撤消*/
  char   extfld1[40+1];              /*扩展字段1*/
              /*扩展字段1*/
  char   extfld2[40+1];              /*扩展字段2*/
              /*扩展字段2*/
  long   pznr;              /*凭证内容*/
              /*凭证内容*/
}APP_PZXX;

#define SD_DATA  APP_PZXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_LONG,  pzxh, 0),\
	DEFSDMEMBER(T_LONG,  ywls, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  yhbh, 0),\
	DEFSDMEMBER(T_STRING,  yhbsh, 0),\
	DEFSDMEMBER(T_STRING,  khmc, 0),\
	DEFSDMEMBER(T_STRING,  yhzh, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  jyje2, 2),\
	DEFSDMEMBER(T_DOUBLE,  jyje3, 2),\
	DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
	DEFSDMEMBER(T_STRING,  jfzq, 0),\
	DEFSDMEMBER(T_STRING,  qsrq, 0),\
	DEFSDMEMBER(T_STRING,  jsrq, 0),\
	DEFSDMEMBER(T_STRING,  sjdm, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  pzzl, 0),\
	DEFSDMEMBER(T_STRING,  pzhm, 0),\
	DEFSDMEMBER(T_STRING,  pzsm, 0),\
	DEFSDMEMBER(T_STRING,  dyrq, 0),\
	DEFSDMEMBER(T_STRING,  dysj, 0),\
	DEFSDMEMBER(T_LONG,  dyls, 0),\
	DEFSDMEMBER(T_STRING,  dyjg, 0),\
	DEFSDMEMBER(T_STRING,  dygy, 0),\
	DEFSDMEMBER(T_LONG,  dycs, 0),\
	DEFSDMEMBER(T_STRING,  jlbz, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  pznr, 0)


	DECLAREFIELDS(SD_APP_PZXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_PZXX_H__*/
