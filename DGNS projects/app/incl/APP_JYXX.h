/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_JYXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_JYXX (交易信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_JYXX_H__
#define __APP_JYXX_H__
typedef struct TDB_APP_JYXX
{
  char   jydm[8+1];              /*交易代码*/
              /*交易代码*/
  char   jymc[40+1];              /*交易名称*/
              /*交易名称*/
  char   yybs[8+1];              /*应用标识*/
              /*应用标识 应用标识 见app_yyxx表*/
  char   jylx[1+1];              /*交易类型*/
              /*交易类型 0正交易 1反交� 9其他*/
  char   lsjlbz[1+1];              /*流水记录标志*/
              /*流水记录标志 0记录 1不记录*/
  char   rzbz[1+1];              /*入帐标志*/
              /*入帐标志 0入帐 1非入帐*/
  char   bbbz[1+1];              /*报表标志*/
              /*报表标志 0报表 1非报表*/
  char   cpxg[1+1];              /*产品相关*/
              /*产品相关 0相关 1不相关(交易与产品无关时，交易的机构，渠道，交易时间，限额等都不做控制)*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[40+1];              /*扩展参数1*/
              /*扩展参数1*/
  char   extfld2[40+1];              /*扩展参数2*/
              /*扩展参数2*/
  char   qtbz[1+1];              /*启停标志*/
              /*启停标志 0开启 1关闭*/
}APP_JYXX;

#define SD_DATA  APP_JYXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  jymc, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  lsjlbz, 0),\
	DEFSDMEMBER(T_STRING,  rzbz, 0),\
	DEFSDMEMBER(T_STRING,  bbbz, 0),\
	DEFSDMEMBER(T_STRING,  cpxg, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qtbz, 0)


	DECLAREFIELDS(SD_APP_JYXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_JYXX_H__*/

