/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_dual.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_dual (住建部公积金业务流水号)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_DUAL_H__
#define __YW_GJJ_DUAL_H__
typedef struct TDB_YW_GJJ_DUAL
{
	long   nextval;  /*业务流水号*/
		/*业务流水号*/
}YW_GJJ_DUAL;

#define SD_DATA  YW_GJJ_DUAL
#define SD_MEMBERS \
	DEFSDMEMBER(T_LONG,  nextval, 0)

	DECLAREFIELDS(SD_YW_GJJ_DUAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_DUAL_H__*/
