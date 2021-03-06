/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:AGENT_DZLSB.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:AGENT_DZLSB (对帐流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __AGENT_DZLSB_H__
#define __AGENT_DZLSB_H__
typedef struct TDB_AGENT_DZLSB
{
  char   ptrq[8+1];              /*平台日期*/
              /*平台日期*/
  int    ptls;              /*平台流水号*/
              /*平台流水号*/
  char   zjrq[8+1];              /*主机日期*/
              /*主机日期*/
  char   zjls[32+1];              /*主机流水号*/
              /*主机流水号*/
  char   jyjg[16+1];              /*交易机构*/
              /*交易机构*/
  char   jygy[16+1];              /*交易柜员*/
              /*交易柜员*/
  char   jybz[3+1];              /*交易币种*/
              /*交易币种 见数据字典 KE  K_JYBZ*/
  char   ywbh[16+1];              /*业务编号*/
              /*业务编号*/
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   xzbz[1+1];              /*现转标志*/
              /*现转标志 0现金 1转帐*/
  char   jdbz[1+1];              /*借贷标识*/
              /*借贷标志(d 借 C贷)*/
  double  jyje;              /*交易金额*/
              /*交易金额*/
  char   jfzh[32+1];              /*借方帐号*/
              /*借方帐号*/
  char   jffzh[10+1];              /*借方分帐号*/
              /*借方分帐号*/
  char   dfzh[32+1];              /*贷方帐号*/
              /*贷方帐号*/
  char   dffzh[10+1];              /*贷方分帐号*/
              /*贷方分帐号*/
  char   extfld1[20+1];              /*扩展字段1*/
              /*扩展字段1*/
  char   extfld2[20+1];              /*扩展字段2*/
              /*扩展字段2*/
  char   extfld3[20+1];              /*扩展字段3*/
              /*扩展字段3*/
  char   jyzt[1+1];              /*交易状态*/
              /*交易状态 k_jyzt*/
  char   zjdzbz[1+1];              /*主机对帐标志*/
              /*对帐标志  0 未对�  �  平台�  平台少*/
}AGENT_DZLSB;

#define SD_DATA  AGENT_DZLSB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjls, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_STRING,  jfzh, 0),\
	DEFSDMEMBER(T_STRING,  jffzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  dffzh, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  jyzt, 0),\
	DEFSDMEMBER(T_STRING,  zjdzbz, 0)


	DECLAREFIELDS(SD_AGENT_DZLSB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_DZLSB_H__*/
