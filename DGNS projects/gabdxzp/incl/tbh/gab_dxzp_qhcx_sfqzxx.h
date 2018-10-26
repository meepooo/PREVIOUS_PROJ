/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_qhcx_sfqzxx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_qhcx_sfqzxx (电信诈骗全户查询_司法强制信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_QHCX_SFQZXX_H__
#define __GAB_DXZP_QHCX_SFQZXX_H__
typedef struct TDB_GAB_DXZP_QHCX_SFQZXX
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单流水号，用于标识查控请求单*/
	int   rwxh;  /*任务序号*/
		/*任务序号*/
	char   csxh[8+1];  /*措施序号*/
		/*措施序号*/
	char   zh[50+1];  /*账号*/
		/*账号*/
	char   kh[30+1];  /*卡折号*/
		/*卡折号*/
	char   djksr[14+1];  /*冻结开始日*/
		/*冻结开始日*/
	char   djjzr[14+1];  /*冻结截止日*/
		/*冻结截止日*/
	char   djjgmc[50+1];  /*冻结机关名称*/
		/*冻结机关名称*/
	char   bz[3+1];  /*币种*/
		/*币种*/
	char   djje[20+1];  /*冻结金额*/
		/*冻结金额*/
	char   beiz[1000+1];  /*备注*/
		/*备注*/
	char   djcslx[4+1];  /*冻结措施类型*/
		/*冻结措施类型*/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   by1[30+1];  /*备用1*/
		/*备用1*/
	char   by2[254+1];  /*备用2*/
		/*备用2*/
	char   by3[254+1];  /*备用3*/
		/*备用3*/

}GAB_DXZP_QHCX_SFQZXX;

#define SD_DATA  GAB_DXZP_QHCX_SFQZXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  csxh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  djksr, 0),\
	DEFSDMEMBER(T_STRING,  djjzr, 0),\
	DEFSDMEMBER(T_STRING,  djjgmc, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  djje, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  djcslx, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_QHCX_SFQZXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_QHCX_SFQZXX_H__*/
