/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_CPJYGYKZ.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_CPJYGYKZ (产品交易柜员级别控制)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_CPJYGYKZ_H__
#define __APP_CPJYGYKZ_H__
typedef struct TDB_APP_CPJYGYKZ
{
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   jydm[8+1];              /*交易代码*/
              /*交易代码*/
  char   kzbz[1+1];              /*控制标志*/
              /*0 不控制 1控制*/
  char   gyjb[2+1];              /*柜员级别*/
              /*数据字典 K_APP_GYJB*/
  char   cxcl[1+1];              /*超限处理*/
              /*0 交易拒绝 1 检查授权柜员级别 2 检查授权柜员岗位 3 检查授权柜员级别和岗位*/
  char   sqgygw[8+1];              /*授权柜员岗位*/
              /*数据字典K_APP_GYGW*/
  char   sqgyjb[2+1];              /*授权柜员级别*/
              /*数据字典K_APP_GYJB*/
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
}APP_CPJYGYKZ;

#define SD_DATA  APP_CPJYGYKZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  kzbz, 0),\
	DEFSDMEMBER(T_STRING,  gyjb, 0),\
	DEFSDMEMBER(T_STRING,  cxcl, 0),\
	DEFSDMEMBER(T_STRING,  sqgygw, 0),\
	DEFSDMEMBER(T_STRING,  sqgyjb, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_CPJYGYKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPJYGYKZ_H__*/
