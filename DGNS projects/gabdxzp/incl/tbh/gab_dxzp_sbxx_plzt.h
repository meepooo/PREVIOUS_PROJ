/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_sbxx_plzt.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_sbxx_plzt (电信诈骗上报信息_批量状态表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_PLZT_H__
#define __GAB_DXZP_SBXX_PLZT_H__
typedef struct TDB_GAB_DXZP_SBXX_PLZT
{
	char   sbpch[36+1];  /*上报批次号*/
		/**/
	int   sbpcxh;  /*上报批次序号*/
		/**/
	char   sbjydm[6+1];  /*上报交易代码*/
		/**/
	char   sbzt[1+1];  /*上报状态*/
		/*上报状态 0-初始 1-成功 2-失败 3-超时 9-上报中*/
	char   respcode[8+1];  /*响应码*/
		/*响应码*/
	char   respmsg[200+1];  /*响应信息*/
		/*响应信息*/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   by1[30+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_SBXX_PLZT;

#define SD_DATA  GAB_DXZP_SBXX_PLZT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  sbjydm, 0),\
	DEFSDMEMBER(T_STRING,  sbzt, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX_PLZT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_PLZT_H__*/
