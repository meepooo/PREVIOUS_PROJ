/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_qhcx_zzhxx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_qhcx_zzhxx (电信诈骗全户查询_子账号信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_QHCX_ZZHXX_H__
#define __GAB_DXZP_QHCX_ZZHXX_H__
typedef struct TDB_GAB_DXZP_QHCX_ZZHXX
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单流水号，用于标识查控请求单*/
	int   rwxh;  /*任务序号*/
		/*任务序号*/
	char   zzhxh[8+1];  /*子账户序号*/
		/*子账户序号*/
	char   zh[40+1];  /*账（卡）号*/
		/*账（卡）号*/
	char   zzhlb[30+1];  /*子账户类别*/
		/*子账户类别*/
	char   zhzt[10+1];  /*账户状态*/
		/*账户状态*/
	char   bz[3+1];  /*币种*/
		/*币种*/
	char   chbz[8+1];  /*钞汇标志*/
		/*钞汇标志*/
	char   zhye[20+1];  /*账户余额*/
		/*账户余额*/
	char   kyye[20+1];  /*可用余额*/
		/*可用余额*/
	char   zhjysj[14+1];  /*最后交易时间*/
		/*最后交易时间*/
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

}GAB_DXZP_QHCX_ZZHXX;

#define SD_DATA  GAB_DXZP_QHCX_ZZHXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  zzhxh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zzhlb, 0),\
	DEFSDMEMBER(T_STRING,  zhzt, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  chbz, 0),\
	DEFSDMEMBER(T_STRING,  zhye, 0),\
	DEFSDMEMBER(T_STRING,  kyye, 0),\
	DEFSDMEMBER(T_STRING,  zhjysj, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_QHCX_ZZHXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_QHCX_ZZHXX_H__*/
