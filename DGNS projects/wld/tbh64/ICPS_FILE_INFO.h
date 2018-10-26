/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_FILE_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_FILE_INFO (8.文件信息管理表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_FILE_INFO_H__
#define __ICPS_FILE_INFO_H__
typedef struct TDB_ICPS_FILE_INFO
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	char   busi_no[16+1];  /*业务编号*/
		/*业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷*/
	char   file_type[60+1];  /*文件类型*/
		/*文件类型*/
	char   md5_code[64+1];  /*MD5值*/
		/*MD5值 16进制字符串*/
	char   file_status[1+1];  /*文件状态*/
		/*文件状态*/
	char   plt_date[8+1];  /*平台日期*/
		/*平台日期YYYYMMDD*/
	char   plt_serial[16+1];  /*平台流水号*/
		/*平台流水号*/
	char   extend_param1[10+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_FILE_INFO;

#define SD_DATA  ICPS_FILE_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  md5_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_FILE_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_FILE_INFO_H__*/
