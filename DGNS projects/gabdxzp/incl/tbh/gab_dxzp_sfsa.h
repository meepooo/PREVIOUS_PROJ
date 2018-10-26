/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_sfsa.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_sfsa (电信诈骗身份涉案表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SFSA_H__
#define __GAB_DXZP_SFSA_H__
typedef struct TDB_GAB_DXZP_SFSA
{
	char   jybm[6+1];  /*交易编码*/
		/**/
	char   csbwlsh[53+1];  /*传输报文流水号*/
		/**/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*请求单标识 请求单流水号，用于标识查控请求单*/
	char   ywlx[4+1];  /*业务类型*/
		/*业务类型*/
	char   zjlx[6+1];  /*证件类型*/
		/**/
	char   zjhm[30+1];  /*证件号*/
		/**/
	char   zhhm[120+1];  /*证件所有人姓名*/
		/**/
	char   zt[1+1];  /*状态*/
		/*状态(0-不在涉案/可疑名单；1-在涉案名单；2-在可疑名单)*/
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

}GAB_DXZP_SFSA;

#define SD_DATA  GAB_DXZP_SFSA
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  zhhm, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SFSA)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SFSA_H__*/
