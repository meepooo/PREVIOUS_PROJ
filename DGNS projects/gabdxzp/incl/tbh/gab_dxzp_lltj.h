/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_lltj.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_lltj (电信诈骗流量统计表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_LLTJ_H__
#define __GAB_DXZP_LLTJ_H__
typedef struct TDB_GAB_DXZP_LLTJ
{
	char   csbwlsh[53+1];  /*传输报文流水号*/
		/**/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*请求单标识 请求单流水号，用于标识查控请求单*/
	char   tgjgbm[12+1];  /*托管机构编码*/
		/*托管机构编码*/
	char   ywlx[4+1];  /*业务类型*/
		/*业务类型*/
	char   ptywlx[4+1];  /*平台业务类型*/
		/*业务类型*/
	char   qssj[14+1];  /*起始时间*/
		/**/
	char   jzsj[14+1];  /*截止时间*/
		/**/
	char   tjsm[300+1];  /*统计说明*/
		/*案件说明*/
	int   llzz;  /*流量总值*/
		/**/
	int   wfkllzz;  /*未反馈流量总值*/
		/**/
	int   qttjz;  /*其他统计值*/
		/**/
	char   qttjsjsm[150+1];  /*其他统计数据说明*/
		/**/
	char   bz[150+1];  /*备注*/
		/**/
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

}GAB_DXZP_LLTJ;

#define SD_DATA  GAB_DXZP_LLTJ
#define SD_MEMBERS \ 
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  tgjgbm, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  ptywlx, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jzsj, 0),\
	DEFSDMEMBER(T_STRING,  tjsm, 0),\
	DEFSDMEMBER(T_LONG,  llzz, 0),\
	DEFSDMEMBER(T_LONG,  wfkllzz, 0),\
	DEFSDMEMBER(T_LONG,  qttjz, 0),\
	DEFSDMEMBER(T_STRING,  qttjsjsm, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_LLTJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_LLTJ_H__*/
