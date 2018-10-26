/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_sbxx_glzhxx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_sbxx_glzhxx (电信诈骗上报信息_关联账户信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_GLZHXX_H__
#define __GAB_DXZP_SBXX_GLZHXX_H__
typedef struct TDB_GAB_DXZP_SBXX_GLZHXX
{
	char   sbpch[36+1];  /*上报批次号*/
		/*上报批次号*/
	long   sbpcxh;  /*上报批次序号*/
		/*上报批次序号*/
	char   zhxh[8+1];  /*关联账户序号*/
		/*交易序号*/
	char   jybm[6+1];  /*交易编码*/
		/*交易编码*/
	char   csbwlsh[53+1];  /*传输报文流水号*/
		/*传输报文流水号*/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*业务申请编号*/
	char   zh[30+1];  /*账号*/
		/*账号*/
	char   zhlx[30+1];  /*账户类型*/
		/*账户类型*/
	char   zhzt[10+1];  /*账户状态*/
		/*账户状态*/
	char   bz[3+1];  /*币种*/
		/*币种*/
	char   chbz[10+1];  /*钞汇标志*/
		/*钞汇标志*/
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

}GAB_DXZP_SBXX_GLZHXX;

#define SD_DATA  GAB_DXZP_SBXX_GLZHXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  zhxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  zhzt, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  chbz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX_GLZHXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_GLZHXX_H__*/
