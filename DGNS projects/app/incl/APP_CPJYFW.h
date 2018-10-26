/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_CPJYFW.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_CPJYFW (产品交易服务关系)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_CPJYFW_H__
#define __APP_CPJYFW_H__
typedef struct TDB_APP_CPJYFW
{
  char   cpdm[16+1];              /*产品代码*/
  char   jydm[8+1];              /*交易代码*/
  char   sjkzbz[1+1];              /*时间控制标志*/
  char   qssj[6+1];              /*起始时间*/
  char   jssj[6+1];              /*结束时间*/
  char   xekzbz[1+1];              /*限额控制标志*/
  double  zxxe;              /*最小限额*/
  double  zdxe;              /*最大限额*/
  char   qykzbz[1+1];              /*签约控制标志*/
  char   qxkz[8+1];              /*权限控制标志*/
  char   gyedkzfs[1+1];              /*柜员额度控制方式*/
  char   jgedkzfs[1+1];              /*机构额度控制方式*/
  char   whjg[16+1];              /*维护机构*/
  char   whgy[16+1];              /*维护柜员*/
  char   whsj[14+1];              /*维护时间*/
  char   extfld1[40+1];              /*扩展参数1*/
  char   extfld2[40+1];              /*扩展参数2*/
  char   qtbz[1+1];              /*启停标志*/
}APP_CPJYFW;

#define SD_DATA  APP_CPJYFW
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  xekzbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  zxxe, 2),\
	DEFSDMEMBER(T_DOUBLE,  zdxe, 2),\
	DEFSDMEMBER(T_STRING,  qykzbz, 0),\
	DEFSDMEMBER(T_STRING,  qxkz, 0),\
	DEFSDMEMBER(T_STRING,  gyedkzfs, 0),\
	DEFSDMEMBER(T_STRING,  jgedkzfs, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qtbz, 0)


	DECLAREFIELDS(SD_APP_CPJYFW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPJYFW_H__*/
