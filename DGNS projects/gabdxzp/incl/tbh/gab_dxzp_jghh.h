/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_jghh.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_jghh (电信诈骗机构行号表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_JGHH_H__
#define __GAB_DXZP_JGHH_H__
typedef struct TDB_GAB_DXZP_JGHH
{
	char   jgh[16+1];  /*机构号*/
		/*机构号，一般指托管机构号*/
	char   hh[14+1];  /*行号*/
		/*行号*/
	char   jgmc[100+1];  /*机构名称*/
		/*机构名称*/
	char   by1[30+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_JGHH;

#define SD_DATA  GAB_DXZP_JGHH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  jgh, 0),\
	DEFSDMEMBER(T_STRING,  hh, 0),\
	DEFSDMEMBER(T_STRING,  jgmc, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_JGHH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_JGHH_H__*/
