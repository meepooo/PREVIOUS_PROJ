/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:AGENT_DRLS.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:AGENT_DRLS (代收付应用当日流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __AGENT_DRLS_H__
#define __AGENT_DRLS_H__
typedef struct TDB_AGENT_DRLS
{
  char   ptrq[8+1];              /*平台日期*/
  char   ptsj[6+1];              /*平台时间*/
  int    ptls;              /*平台流水号*/
  int    jyxh;              /*交易序列号*/
  int    yptlsh;              /*原平台流水号*/
  char   jyjg[16+1];              /*交易机构*/
  char   jygy[16+1];              /*交易柜员*/
  char   sqjg[16+1];              /*授权机构*/
  char   sqgy[16+1];              /*授权柜员*/
  char   qdbs[3+1];              /*渠道标识*/
  char   zdsbbh[8+1];              /*终端设备编号*/
  char   cpdm[16+1];              /*产品代码*/
  char   ywbh[16+1];              /*业务编号*/
  char   ywrq[8+1];              /*业务日期*/
  int    ywlsh;              /*业务流水号*/
  char   jydm[8+1];              /*交易代码*/
  char   khmc[80+1];              /*客户名称*/
  char   khbh[32+1];              /*客户编号*/
  char   dqdm[8+1];              /*地区代码*/
  char   yhlx[16+1];              /*用户类型*/
  char   yhh1[32+1];              /*用户号*/
  char   yhbsh[32+1];              /*用户标识号*/
  char   yhmc[80+1];              /*用户名称*/
  char   jybz[3+1];              /*交易币种*/
  char   xzbz[1+1];              /*现转标志*/
  char   jdbz[1+1];              /*借贷标志*/
  char   zhlx[2+1];              /*帐户类型*/
  char   yhzh[32+1];              /*银行帐号*/
  double  jyje;              /*交易金额*/
  double  jyje2;              /*交易金额2*/
  double  sxf;              /*手续费*/
  double  znj;              /*滞纳金*/
  char   pzzl[3+1];              /*凭证种类*/
  char   pzhm[32+1];              /*凭证号码*/
  char   jfbsh[32+1];              /*缴费标识号*/
  int    cxlsh;              /*查询流水号*/
  char   jyzy[40+1];              /*交易摘要*/
  char   fqflsh[32+1];              /*发起方流水号*/
  char   fqfrq[8+1];              /*发起方日期*/
  char   fqfsj[6+1];              /*发起方时间*/
  char   fqfjydm[8+1];              /*发起方交易代码*/
  char   dsflsh[22+1];              /*第三方流水号*/
  char   dsfrq[14+1];              /*第三方日期*/
  char   dsfjylx[8+1];              /*第三方交易类类型*/
  char   dsfjydm[8+1];              /*第三方交易代码*/
  char   dsfxym[8+1];              /*第三方响应码*/
  char   dsfxyxx[60+1];              /*第三方响应信息*/
  char   dsfjyzt[1+1];              /*第三方交易状态*/
  char   zjlsh[32+1];              /*主机流水号*/
  char   zjrq[14+1];              /*主机日期*/
  char   zjjydm[8+1];              /*主机交易代码*/
  char   zjxym[8+1];              /*主机响应码*/
  char   zjxyxx[60+1];              /*主机响应信息*/
  char   zjjyzt[1+1];              /*主机交易状态*/
  char   jyxym[8+1];              /*交易响应码*/
  char   jyxyxx[60+1];              /*交易响应信息*/
  char   jyzt[1+1];              /*交易状态*/
  char   dsfdzbz[1+1];              /*第三方对帐标志*/
  char   zjdzbz[1+1];              /*主机对帐标志*/
  char   extfld1[40+1];              /*扩展1*/
  char   extfld2[40+1];              /*扩展2*/
  char   extfld3[40+1];              /*扩展3*/
  char   extfld4[40+1];              /*扩展4*/
  char   extfld5[40+1];              /*扩展5*/
  char   extfld6[40+1];              /*扩展6*/
}AGENT_DRLS;

#define SD_DATA  AGENT_DRLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  ptsj, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_LONG,  jyxh, 0),\
	DEFSDMEMBER(T_LONG,  yptlsh, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  sqjg, 0),\
	DEFSDMEMBER(T_STRING,  sqgy, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  zdsbbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_LONG,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  khmc, 0),\
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  dqdm, 0),\
	DEFSDMEMBER(T_STRING,  yhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhh1, 0),\
	DEFSDMEMBER(T_STRING,  yhbsh, 0),\
	DEFSDMEMBER(T_STRING,  yhmc, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhzh, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  jyje2, 2),\
	DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
	DEFSDMEMBER(T_DOUBLE,  znj, 2),\
	DEFSDMEMBER(T_STRING,  pzzl, 0),\
	DEFSDMEMBER(T_STRING,  pzhm, 0),\
	DEFSDMEMBER(T_STRING,  jfbsh, 0),\
	DEFSDMEMBER(T_LONG,  cxlsh, 0),\
	DEFSDMEMBER(T_STRING,  jyzy, 0),\
	DEFSDMEMBER(T_STRING,  fqflsh, 0),\
	DEFSDMEMBER(T_STRING,  fqfrq, 0),\
	DEFSDMEMBER(T_STRING,  fqfsj, 0),\
	DEFSDMEMBER(T_STRING,  fqfjydm, 0),\
	DEFSDMEMBER(T_STRING,  dsflsh, 0),\
	DEFSDMEMBER(T_STRING,  dsfrq, 0),\
	DEFSDMEMBER(T_STRING,  dsfjylx, 0),\
	DEFSDMEMBER(T_STRING,  dsfjydm, 0),\
	DEFSDMEMBER(T_STRING,  dsfxym, 0),\
	DEFSDMEMBER(T_STRING,  dsfxyxx, 0),\
	DEFSDMEMBER(T_STRING,  dsfjyzt, 0),\
	DEFSDMEMBER(T_STRING,  zjlsh, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjjydm, 0),\
	DEFSDMEMBER(T_STRING,  zjxym, 0),\
	DEFSDMEMBER(T_STRING,  zjxyxx, 0),\
	DEFSDMEMBER(T_STRING,  zjjyzt, 0),\
	DEFSDMEMBER(T_STRING,  jyxym, 0),\
	DEFSDMEMBER(T_STRING,  jyxyxx, 0),\
	DEFSDMEMBER(T_STRING,  jyzt, 0),\
	DEFSDMEMBER(T_STRING,  dsfdzbz, 0),\
	DEFSDMEMBER(T_STRING,  zjdzbz, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  extfld4, 0),\
	DEFSDMEMBER(T_STRING,  extfld5, 0),\
	DEFSDMEMBER(T_STRING,  extfld6, 0)


	DECLAREFIELDS(SD_AGENT_DRLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_DRLS_H__*/

