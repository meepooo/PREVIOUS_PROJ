/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_DICT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_DICT (数据字典表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_DICT_H__
#define __APP_DICT_H__
typedef struct TDB_APP_DICT
{
	char   pkey;  /*KEY值*/
		/**/
	char   keyjs;  /*KEY值解释*/
		/*KEY值解释*/
	char   pval;  /*值*/
		/**/
	char   prompt;  /*说明*/
		/**/
	char   ssyy;  /*所属应用*/
		/*应用标识*/
	char   whjg;  /*维护机构*/
		/**/
	char   whgy;  /*维护柜员*/
		/**/
	char   whsj;  /*维护时间*/
		/**/

}APP_DICT;

#define SD_DATA  APP_DICT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_STRING,  keyjs, 0),\
	DEFSDMEMBER(T_STRING,  pval, 0),\
	DEFSDMEMBER(T_STRING,  prompt, 0),\
	DEFSDMEMBER(T_STRING,  ssyy, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_DICT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DICT_H__*/
