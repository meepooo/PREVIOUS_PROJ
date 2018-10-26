/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_autoproc.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_autoproc (电信诈骗自动处理表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_AUTOPROC_H__
#define __GAB_DXZP_AUTOPROC_H__
typedef struct TDB_GAB_DXZP_AUTOPROC
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*请求单标识 请求单流水号，用于标识查控请求单*/
	char   jjcd[2+1];  /*紧急程度*/
		/*紧急程度 01代表正常；02代表加急*/
	char   qqdzt[2+1];  /*请求单状态*/
		/*请求单状态 第一位：0-初始 1-落地 2-处理(提交) 3-提回 4-反馈  第二位：0-初始 1-不成功；2-成功; 3-超时; 9-处理中*/
	char   zh[30+1];  /*帐号*/
		/*账号*/

}GAB_DXZP_AUTOPROC;

#define SD_DATA  GAB_DXZP_AUTOPROC
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jjcd, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0)

	DECLAREFIELDS(SD_GAB_DXZP_AUTOPROC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_AUTOPROC_H__*/
