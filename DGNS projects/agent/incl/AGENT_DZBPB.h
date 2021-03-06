/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:AGENT_DZBPB.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:AGENT_DZBPB (对帐不平表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __AGENT_DZBPB_H__
#define __AGENT_DZBPB_H__
typedef struct TDB_AGENT_DZBPB
{
  char   dzrq[8+1];              /*对账日期*/
              /**/
  char   ptrq[8+1];              /*平台日期*/
              /**/
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
  char   xzbz[1+1];              /*现转标志*/
              /*现转标志 0现金 1转帐*/
  char   jdbz[1+1];              /*借贷标识*/
              /*借贷标志(d 借 C贷)*/
  double  jyje;              /*交易金额*/
              /*交易金额*/
  double  ptjyje;              /*平台交易金额*/
              /*平台交易金额*/
  char   jfzh[32+1];              /*借方帐号*/
              /*借方帐号*/
  char   jffzh[10+1];              /*借方分帐号*/
              /*借方分帐号*/
  char   dfzh[32+1];              /*贷方帐号*/
              /*贷方帐号*/
  char   dffzh[10+1];              /*贷方分帐号*/
              /*贷方分帐号*/
  char   ywlsh[16+1];              /*业务流水号*/
              /*业务流水号*/
  char   ywrq[8+1];              /*业务日期*/
              /*业务日期*/
  char   lslx[1+1];              /*流水类型*/
              /*流水类型  1 主机对�  第三方对账*/
  char   dzbz[1+1];              /*对帐标志*/
              /*对帐标志  0 未对�  �  平台�  平台少*/
  char   tzlsh[22+1];              /*调账流水号*/
              /*调账流水号*/
  char   clzt[1+1];              /*处理状态*/
              /*处理状态 0未处理 1已处� 8处理过程出� 9处理中*/
  char   extfld1[20+1];              /*扩展字段1*/
              /*扩展字段1*/
  char   extfld2[20+1];              /*扩展字段2*/
              /*扩展字段2*/
  char   extfld3[20+1];              /*扩展字段3*/
              /*扩展字段3*/
}AGENT_DZBPB;

#define SD_DATA  AGENT_DZBPB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjls, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  ptjyje, 2),\
	DEFSDMEMBER(T_STRING,  jfzh, 0),\
	DEFSDMEMBER(T_STRING,  jffzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  dffzh, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  lslx, 0),\
	DEFSDMEMBER(T_STRING,  dzbz, 0),\
	DEFSDMEMBER(T_STRING,  tzlsh, 0),\
	DEFSDMEMBER(T_STRING,  clzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0)


	DECLAREFIELDS(SD_AGENT_DZBPB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_DZBPB_H__*/

