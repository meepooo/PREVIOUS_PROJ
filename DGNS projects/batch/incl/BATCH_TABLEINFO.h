/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_TABLEINFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_TABLEINFO (批量业务明细表信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_TABLEINFO_H__
#define __BATCH_TABLEINFO_H__
typedef struct TDB_BATCH_TABLEINFO
{

}BATCH_TABLEINFO;

#define SD_DATA  BATCH_TABLEINFO
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  tablecode, 0),\
	DEFSDMEMBER(T_STRING,  tablename, 0),\
	DEFSDMEMBER(T_STRING,  tabletype, 0),\
	DEFSDMEMBER(T_STRING,  table_mb, 0),\
	DEFSDMEMBER(T_STRING,  tabletbspace, 0),\
	DEFSDMEMBER(T_STRING,  indextbspace, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_TABLEINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_TABLEINFO_H__*/
