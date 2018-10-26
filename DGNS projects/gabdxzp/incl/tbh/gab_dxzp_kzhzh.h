/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_kzhzh.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[章亮]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_kzhzh (卡账号综合信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_KZHZH_H__
#define __GAB_DXZP_KZHZH_H__
typedef struct TDB_GAB_DXZP_KZHZH
{
	char   zh[30+1];  /*账号*/
		/**/
	char   kh[30+1];  /*卡号*/
		/**/
	char   zhmc[100+1];  /*账户名*/
		/**/
	int   dccs;  /*动查次数*/
		/**/
	char   dczt[1+1];  /*动查状态*/
		/*0-动查  1-解除*/
	char   dcywsqbh[40+1];  /*动查最新业务号*/
		/**/
	char   dcqssj[14+1];  /*动查起始时间*/
		/**/
	char   dcjssj[14+1];  /*动查结束时间*/
		/**/
	int   djcs;  /*冻结次数*/
		/**/
	char   djzt[1+1];  /*冻结状态*/
		/*0-冻结  1-解除 2-续冻 9-初始*/
	double   djljje;  /*冻结累计金额*/
		/**/
	char   djywsqbh[40+1];  /*冻结最新业务号*/
		/**/
	char   djqssj[14+1];  /*冻结起始时间*/
		/**/
	char   djjssj[14+1];  /*冻结结束时间*/
		/**/
	int   zfcs;  /*止付次数*/
		/*0-止付  1-解除 2-续止  9-初始*/
	char   zfzt[1+1];  /*止付状态*/
		/**/
	double   zfljje;  /*止付累计金额*/
		/**/
	char   zfywsqbh[40+1];  /*止付最新业务号*/
		/**/
	char   zfqssj[14+1];  /*止付起始时间*/
		/**/
	char   zfjssj[14+1];  /*止付结束时间*/
		/**/
	int   khcs;  /*扣划次数*/
		/**/
	double   khljje;  /*扣划累计金额*/
		/**/
	char   khywsqbh[40+1];  /*扣划最新业务号*/
		/**/
	char   by1[32+1];  /*备用1*/
		/**/
	char   by2[255+1];  /*备用2*/
		/**/
	char   by3[255+1];  /*备用3*/
		/**/

}GAB_DXZP_KZHZH;

#define SD_DATA  GAB_DXZP_KZHZH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_LONG,  dccs, 0),\
	DEFSDMEMBER(T_STRING,  dczt, 0),\
	DEFSDMEMBER(T_STRING,  dcywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  dcqssj, 0),\
	DEFSDMEMBER(T_STRING,  dcjssj, 0),\
	DEFSDMEMBER(T_LONG,  djcs, 0),\
	DEFSDMEMBER(T_STRING,  djzt, 0),\
	DEFSDMEMBER(T_DOUBLE,  djljje, 2),\
	DEFSDMEMBER(T_STRING,  djywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  djqssj, 0),\
	DEFSDMEMBER(T_STRING,  djjssj, 0),\
	DEFSDMEMBER(T_LONG,  zfcs, 0),\
	DEFSDMEMBER(T_STRING,  zfzt, 0),\
	DEFSDMEMBER(T_DOUBLE,  zfljje, 2),\
	DEFSDMEMBER(T_STRING,  zfywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  zfqssj, 0),\
	DEFSDMEMBER(T_STRING,  zfjssj, 0),\
	DEFSDMEMBER(T_LONG,  khcs, 0),\
	DEFSDMEMBER(T_DOUBLE,  khljje, 2),\
	DEFSDMEMBER(T_STRING,  khywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_KZHZH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_KZHZH_H__*/

