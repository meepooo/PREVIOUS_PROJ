/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_lxdx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_lxdx (电信诈骗轮询下达表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_LXDX_H__
#define __GAB_DXZP_LXDX_H__
typedef struct TDB_GAB_DXZP_LXDX
{
	char   lxrq[8+1];  /*轮询日期*/
		/**/
	char   lxpch[32+1];  /*轮询批次号*/
		/**/
	char   lxsj[6+1];  /*轮询时间*/
		/**/
	char   respcode[6+1];  /*返回码*/
		/**/
	char   respmsg[200+1];  /*返回信息*/
		/**/
	int   lxbs;  /*轮询笔数*/
		/**/
	char   lxwj[254+1];  /*轮询文件*/
		/**/
	char   by1[32+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_LXDX;

#define SD_DATA  GAB_DXZP_LXDX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  lxrq, 0),\
	DEFSDMEMBER(T_STRING,  lxpch, 0),\
	DEFSDMEMBER(T_STRING,  lxsj, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_LONG,  lxbs, 0),\
	DEFSDMEMBER(T_STRING,  lxwj, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_LXDX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_LXDX_H__*/
