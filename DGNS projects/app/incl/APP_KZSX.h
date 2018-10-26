/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_KZSX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_KZSX (扩展属性表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_KZSX_H__
#define __APP_KZSX_H__
typedef struct TDB_APP_KZSX
{
  char   pkey[40+1];              /*键值*/
              /*键值 存放需要扩充参数的表的表名  记录的唯一关键值，存在多个字段通过"|"分隔
                如 cpxx_001*/
  char   csmc[20+1];              /*参数名称*/
              /*表示扩充后的字段用英文字母表示，类似于表字段名称*/
  char   cssm[80+1];              /*参数说明*/
              /*参数说明*/
  char   csz[80+1];              /*参数值*/
              /*参数的值*/
  char   extfld[40+1];              /*扩展参数*/
              /*扩展参数*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}APP_KZSX;

#define SD_DATA  APP_KZSX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_STRING,  csmc, 0),\
	DEFSDMEMBER(T_STRING,  cssm, 0),\
	DEFSDMEMBER(T_STRING,  csz, 0),\
	DEFSDMEMBER(T_STRING,  extfld, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_KZSX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_KZSX_H__*/
