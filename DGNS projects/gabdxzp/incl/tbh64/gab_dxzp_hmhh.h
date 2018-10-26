/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_hmhh.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_hmhh (电信诈骗行名行号表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_HMHH_H__
#define __GAB_DXZP_HMHH_H__
typedef struct TDB_GAB_DXZP_HMHH
{
	char   hh[14+1];  /*行号*/
		/*行号*/
	int   xh;  /*序号*/
		/*序号*/
	char   hm[100+1];  /*行名*/
		/*行名*/
	char   hb[1+1];  /*行别*/
		/*行别  1-全国性银行 2-城市商业银行 3-省级农信联社  4-农村商业银行 5-民营银行 9-外资银行 t-托管银行 T-本法人行*/
	char   hbsm[20+1];  /*行别说明*/
		/*行别说明*/
	char   jbjg[16+1];  /*经办机构*/
		/*经办机构*/
	char   jbgy[16+1];  /*经办柜员*/
		/*经办柜员*/
	char   lxdh[20+1];  /*经办人电话*/
		/*经办人电话*/
	char   by1[30+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_HMHH;

#define SD_DATA  GAB_DXZP_HMHH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  hh, 0),\
	DEFSDMEMBER(T_LONG,  xh, 0),\
	DEFSDMEMBER(T_STRING,  hm, 0),\
	DEFSDMEMBER(T_STRING,  hb, 0),\
	DEFSDMEMBER(T_STRING,  hbsm, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  lxdh, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_HMHH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_HMHH_H__*/
