/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_qhcx_qlxx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_qhcx_qlxx (电信诈骗全户查询_权利人信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_QHCX_QLXX_H__
#define __GAB_DXZP_QHCX_QLXX_H__
typedef struct TDB_GAB_DXZP_QHCX_QLXX
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单流水号，用于标识查控请求单*/
	int   rwxh;  /*任务序号*/
		/*任务序号*/
	char   xh[8+1];  /*序号*/
		/*序号*/
	char   zh[50+1];  /*账号*/
		/*账号*/
	char   kh[30+1];  /*卡折号*/
		/*卡折号*/
	char   zjlx[15+1];  /*证件类型代码*/
		/*证件类型代码*/
	char   zjhm[30+1];  /*证件号码*/
		/*证件号码*/
	char   qllx[2+1];  /*权利类型*/
		/*权利类型*/
	char   qlrxm[60+1];  /*权利人姓名*/
		/*权利人姓名*/
	char   qlje[20+1];  /*权利金额*/
		/*权利金额*/
	char   qlrtxdz[60+1];  /*权利人通讯地址*/
		/*权利人通讯地址*/
	char   qlrlxfs[50+1];  /*权利人联系方式*/
		/*权利人联系方式*/
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

}GAB_DXZP_QHCX_QLXX;

#define SD_DATA  GAB_DXZP_QHCX_QLXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  xh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  qllx, 0),\
	DEFSDMEMBER(T_STRING,  qlrxm, 0),\
	DEFSDMEMBER(T_STRING,  qlje, 0),\
	DEFSDMEMBER(T_STRING,  qlrtxdz, 0),\
	DEFSDMEMBER(T_STRING,  qlrlxfs, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_QHCX_QLXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_QHCX_QLXX_H__*/
