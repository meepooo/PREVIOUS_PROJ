/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_CPJGGX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_CPJGGX (产品机构关系表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_CPJGGX_H__
#define __APP_CPJGGX_H__
typedef struct TDB_APP_CPJGGX
{
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   jgbh[16+1];              /*机构编号*/
              /*机构编号*/
  char   sjkzbz[1+1];              /*时间控制标志*/
              /*时间控制标志  0控制 1不控制*/
  char   qssj[6+1];              /*起始时间*/
              /*起始时间*/
  char   jssj[6+1];              /*结束时间*/
              /*结束时间*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[40+1];              /*扩展参数1*/
              /*扩展参数1*/
  char   extfld2[40+1];              /*扩展参数2*/
              /*扩展参数1*/
  char   zt[1+1];              /*状态*/
              /*状态 0允许 1不允许*/
}APP_CPJGGX;

#define SD_DATA  APP_CPJGGX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  jgbh, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_CPJGGX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPJGGX_H__*/
