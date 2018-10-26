/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_CPQDGX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_CPQDGX (产品渠道关系表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_CPQDGX_H__
#define __APP_CPQDGX_H__
typedef struct TDB_APP_CPQDGX
{
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   qdbs[3+1];              /*渠道标识*/
              /*渠道标识*/
  char   sjkzbz[1+1];              /*时间控制标志*/
              /*时间控制标志  0控制 1不控制*/
  char   qssj[6+1];              /*起始时间*/
              /*起始时间*/
  char   jssj[6+1];              /*结束时间*/
              /*结束时间*/
  char   xekzbz[1+1];              /*限额控制标志*/
              /*限额控制标志 0控制 1不控制*/
  double  zxxe;              /*最小限额*/
              /*最小限额*/
  double  zdxe;              /*最大限额*/
              /*最大限额*/
  char   czbz[1+1];              /*冲正标志*/
              /*是否允许冲正  0允许 1不允许*/
  char   zdczbz[1+1];              /*自动冲正标志*/
              /*系统异常是否自动冲正  0是 1否*/
  char   fpbcbz[1+1];              /*发票保存标志*/
              /*发票保存标志 0保存 1不保存*/
  char   fpcsfs[1+1];              /*发票传输方式*/
              /*发票传输方式 0报文 1文件*/
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
  char   zt[1+1];              /*状态*/
              /*状态 0允许 1不允许*/
}APP_CPQDGX;

#define SD_DATA  APP_CPQDGX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  xekzbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  zxxe, 2),\
	DEFSDMEMBER(T_DOUBLE,  zdxe, 2),\
	DEFSDMEMBER(T_STRING,  czbz, 0),\
	DEFSDMEMBER(T_STRING,  zdczbz, 0),\
	DEFSDMEMBER(T_STRING,  fpbcbz, 0),\
	DEFSDMEMBER(T_STRING,  fpcsfs, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_CPQDGX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPQDGX_H__*/
