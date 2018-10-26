/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_DAILY_STATUS.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_DAILY_STATUS (7.日终状态表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_DAILY_STATUS_H__
#define __ICPS_DAILY_STATUS_H__
typedef struct TDB_ICPS_DAILY_STATUS
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	char   busi_no[16+1];  /*业务编号*/
		/*业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷*/
	char   file_step[2+1];  /*文件步点*/
		/*文件步点 00-获取中 01-获取成功 02-部分获取成功 03-获取失败 04-入库中 05-入库成功 06-部分入库成功 07-入库失败 99-初始*/
	char   third_total_check_status[1+1];  /*第三方对总账状态*/
		/*第三方对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   third_detail_check_status[1+1];  /*第三方明细对账状态*/
		/*第三方明细对账状态  0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   host_total_check_status[1+1];  /*核心对总账状态*/
		/*核心对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   host_detail_check_status[1+1];  /*核心明细对账状态*/
		/*核心明细对账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   third_pre_total_check_status[1+1];  /*第三方预对总账状态*/
		/*第三方预对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   third_pre_detail_check_status[1+1];  /*第三方预明细对账状态*/
		/*第三方预明细对账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   host_pre_total_check_status[1+1];  /*核心预对总账状态*/
		/*核心预对总账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   host_pre_detail_check_status[1+1];  /*核心预明细对账状态*/
		/*核心预明细对账状态 0 未对账 1 对账平 2 对账不平 3对账出错 4对账平有尾差 9 对账中*/
	char   clear_status[1+1];  /*清算状态*/
		/*清算状态 0 未清算1 已清算 2 清算出错  6 清算状态未知 9 清算中*/
	char   plt_date[8+1];  /*平台日期*/
		/*平台日期YYYYMMDD*/
	char   plt_serial[16+1];  /*平台流水号*/
		/*平台流水号*/
	char   send_host_serial[64+1];  /*上送主机流水号*/
		/*上送主机流水号*/
	char   send_host_date[8+1];  /*上送主机日期*/
		/*上送主机日期*/
	char   host_serial[64+1];  /*主机流水号*/
		/*主机流水号*/
	char   host_date[8+1];  /*主机日期*/
		/*主机日期*/
	char   respcode[8+1];  /*交易响应码*/
		/*交易响应码*/
	char   respmsg[250+1];  /*交易响应信息*/
		/*交易响应信息*/
	char   trans_status[1+1];  /*交易状态*/
		/*交易状态*/
	char   branch[16+1];  /*交易机构*/
		/*交易机构*/
	char   teller[16+1];  /*交易柜员*/
		/*交易柜员*/
	char   extend_param1[10+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_DAILY_STATUS;

#define SD_DATA  ICPS_DAILY_STATUS
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_step, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_pre_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_pre_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_pre_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_pre_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  teller, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_DAILY_STATUS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_DAILY_STATUS_H__*/
