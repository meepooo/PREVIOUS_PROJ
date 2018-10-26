/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:sfck_timeout.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:sfck_timeout (司法查控超时查证表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __SFCK_TIMEOUT_H__
#define __SFCK_TIMEOUT_H__
typedef struct TDB_SFCK_TIMEOUT
{
	char xtbh[16+1]; /*系统编号*/
	    /*系统编号*/
	char ywbm[20+1];/*业务表名*/
	    /*业务表名*/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*请求单标识 请求单流水号，用于标识查控请求单*/
	char   ywrq[8+1];  /*业务日期*/
		/*业务日期*/
	char   ywlsh[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   qqdzt[2+1];  /*请求单状态*/
		/*请求单状态*/

}SFCK_TIMEOUT;

#define SD_DATA  SFCK_TIMEOUT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  xtbh, 0),\
	DEFSDMEMBER(T_STRING,  ywbm, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0)

	DECLAREFIELDS(SD_SFCK_TIMEOUT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __SFCK_TIMEOUT_H__*/
