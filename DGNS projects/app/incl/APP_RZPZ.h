/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_RZPZ.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_RZPZ (日终配置表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_RZPZ_H__
#define __APP_RZPZ_H__
typedef struct TDB_APP_RZPZ
{
  char   ssyy[8+1];              /*所属应用*/
              /*应用标识*/
  char   czlx[1+1];              /*操作类型*/
              /*1 归档 2 清理 3 备份 */
  char   dxlx[1+1];              /*对象类型*/
              /*1 数据库 2 文件*/
  char   czdx1[128+1];              /*源操作对象*/
              /*归档时存放源表；源文件路径*/
  char   czdx2[128+1];              /*目的操作对象*/
              /*归档时存放目标表；目标文件路径*/
  char   cztj[254+1];              /*操作条件*/
              /*数据库表的 sql条件*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[20+1];              /*扩展字段1*/
              /*扩展1*/
  char   extfld2[20+1];              /*扩展字段2*/
              /*扩展2*/
}APP_RZPZ;

#define SD_DATA  APP_RZPZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ssyy, 0),\
	DEFSDMEMBER(T_STRING,  czlx, 0),\
	DEFSDMEMBER(T_STRING,  dxlx, 0),\
	DEFSDMEMBER(T_STRING,  czdx1, 0),\
	DEFSDMEMBER(T_STRING,  czdx2, 0),\
	DEFSDMEMBER(T_STRING,  cztj, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_RZPZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_RZPZ_H__*/

