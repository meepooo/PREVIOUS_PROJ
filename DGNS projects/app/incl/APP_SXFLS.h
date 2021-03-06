/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_SXFLS.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_SXFLS (手续费流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_SXFLS_H__
#define __APP_SXFLS_H__
typedef struct TDB_APP_SXFLS
{
  char   ptrq[8+1];              /*平台日期*/
              /*平台日期*/
  char   ptls[16+1];              /*平台流水号*/
              /*平台流水号*/
  char   flbs[32+1];              /*费率标识*/
              /*费率标识*/
  char   yybs[3+1];              /*应用标识*/
              /**/
  char   ywbh[16+1];              /*业务编号*/
              /**/
  char   cpdm[16+1];              /*产品代码*/
              /**/
  char   qdbs[3+1];              /*渠道标识*/
              /**/
  char   jgbs[16+1];              /*机构标识*/
              /**/
  char   khlx[1+1];              /*客户类型*/
              /**/
  char   khbh[32+1];              /*客户编号*/
              /*客户在银行编号*/
  char   yhh[32+1];              /*用户号*/
              /*用户在第三方客户号*/
  char   dwbh[16+1];              /*单位编号*/
              /**/
  char   xtnbz[1+1];              /*系统内标志*/
              /*1 系统内   系统外*/
  char   jylsh[16+1];              /*交易流水号*/
              /*收取手续费的原交易流水号*/
  char   jylx[1+1];              /*交易类型*/
              /*交易类型 0 联� 1批量*/
  char   jyrq[8+1];              /*交易日期*/
              /**/
  char   jygy[16+1];              /*交易柜员*/
              /**/
  char   jyjg[16+1];              /*交易机构*/
              /**/
  double  jyje;              /*交易金额*/
              /*交易金额*/
  int    jybs;              /*交易笔数*/
              /**/
  double  sxfje;              /*手续费金额*/
              /*费用金额*/
  char   sfzt[1+1];              /*收费状态*/
              /*收取状态 0 未收� 1已收取*/
  char   jfzh[32+1];              /*借方帐户*/
              /*借方帐户*/
  char   dfzh[32+1];              /*贷方帐户*/
              /*贷方帐户*/
  char   sfrq[8+1];              /*收费日期*/
              /*收费日期*/
  char   sfjygy[16+1];              /*收费交易柜员*/
              /**/
  char   sfjyjg[16+1];              /*收费交易机构*/
              /**/
  char   sfls[16+1];              /*收费流水号*/
              /**/
  char   lszt[1+1];              /*流水状态*/
              /*流水状态 0 正� 1取消*/
  char   extfld2[40+1];              /*扩展字段2*/
              /**/
  char   extfld1[20+1];              /*扩展字段1*/
              /**/
  char   sm[40+1];              /*说明*/
              /*说明*/
}APP_SXFLS;

#define SD_DATA  APP_SXFLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  flbs, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  jgbs, 0),\
	DEFSDMEMBER(T_STRING,  khlx, 0),\
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  yhh, 0),\
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  xtnbz, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  jyrq, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_LONG,  jybs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxfje, 2),\
	DEFSDMEMBER(T_STRING,  sfzt, 0),\
	DEFSDMEMBER(T_STRING,  jfzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  sfrq, 0),\
	DEFSDMEMBER(T_STRING,  sfjygy, 0),\
	DEFSDMEMBER(T_STRING,  sfjyjg, 0),\
	DEFSDMEMBER(T_STRING,  sfls, 0),\
	DEFSDMEMBER(T_STRING,  lszt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0)


	DECLAREFIELDS(SD_APP_SXFLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_SXFLS_H__*/

