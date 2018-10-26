/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_dtjc_resp.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_dtjc_resp (电信诈骗动态解除响应)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_DTJC_RESP_H__
#define __GAB_DXZP_DTJC_RESP_H__
typedef struct TDB_GAB_DXZP_DTJC_RESP
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单流水号，用于标识查控请求单*/
	long   rwxh;  /*任务序号*/
		/*任务序号*/
	char   jcdtcxsm[300+1];  /*解除动态查询说明*/
		/*解除动态查询说明*/
	char   fksm[150+1];  /*反馈说明*/
		/*反馈说明*/
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

}GAB_DXZP_DTJC_RESP;

#define SD_DATA  GAB_DXZP_DTJC_RESP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  jcdtcxsm, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_DTJC_RESP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_DTJC_RESP_H__*/
