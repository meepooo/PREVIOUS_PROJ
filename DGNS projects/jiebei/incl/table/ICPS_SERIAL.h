/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_SERIAL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_SERIAL (1.当日流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_SERIAL_H__
#define __ICPS_SERIAL_H__
typedef struct TDB_ICPS_SERIAL
{
	char   plt_date[8+1];  /*平台日期*/
		/*平台日期YYYYMMDD*/
	char   plt_time[6+1];  /*平台时间*/
		/*平台时间HHMMSS*/
	char   plt_serial[16+1];  /*平台流水号*/
		/*平台流水号*/
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	char   busi_no[16+1];  /*业务编号*/
		/*业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷*/
	char   channel[16+1];  /*渠道代码*/
		/*渠道代码 311-借呗 312-京东金条 313-微粒贷*/
	char   local_id[32+1];  /*本行机构标识*/
		/*本行机构标识*/
	char   trans_code[8+1];  /*平台交易代码*/
		/*平台交易代码*/
	char   send_recv_flag[1+1];  /*往来账标志*/
		/*往来账标志 0-来账 1-往账*/
	char   apply_no[64+1];  /*申请单号*/
		/*申请单号*/
	char   version[8+1];  /*版本号*/
		/*版本号 接口版本*/
	char   send_time_zone[32+1];  /*发送方所在时区*/
		/*发送方所在时区 UTC+8*/
	char   send_dttm[16+1];  /*报文发起时间*/
		/*报文发起时间 YYYYMMDDHHMMSS*/
	char   msg_id[64+1];  /*请求报文标示号*/
		/*请求报文标示号*/
	char   third_id[32+1];  /*第三方机构标识*/
		/*第三方机构标识*/
	char   third_trans_code[64+1];  /*第三方交易代码*/
		/*第三方交易代码*/
	char   third_respcode[16+1];  /*第三方响应码*/
		/*第三方响应码*/
	char   third_respmsg[255+1];  /*第三方响应信息*/
		/*第三方响应信息*/
	char   third_trans_status[1+1];  /*第三方交易状态*/
		/*第三方交易状态*/
	char   retry[1+1];  /*是否需要重试标记*/
		/*是否需要重试标记 Y-需要 N-不需要*/
	char   send_host_serial[64+1];  /*上送主机流水号*/
		/*上送主机流水号*/
	char   send_host_date[8+1];  /*上送主机日期*/
		/*上送主机日期*/
	char   host_serial[64+1];  /*主机流水号*/
		/*主机流水号*/
	char   host_date[8+1];  /*主机日期*/
		/*主机日期*/
	char   host_trans_code[16+1];  /*主机交易代码*/
		/*主机交易代码*/
	char   host_respcode[16+1];  /*主机响应码*/
		/*主机响应码*/
	char   host_respmsg[250+1];  /*主机响应信息*/
		/*主机响应信息*/
	char   host_status[2+1];  /*主机交易状态*/
		/*主机交易状态*/
	char   in_channel_date[64+1];  /*行内渠道日期*/
		/*行内渠道日期*/
	char   in_channel_serial[8+1];  /*行内渠道流水号*/
		/*行内渠道流水号*/
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
	char   grant_branch[16+1];  /*授权机构*/
		/*授权机构*/
	char   grant_teller[16+1];  /*授权柜员*/
		/*授权柜员*/
	char   extend_param1[10+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/
	char   extend_param4[60+1];  /*扩展4*/
		/*扩展4*/
	char   extend_param5[250+1];  /*扩展5*/
		/*扩展5*/

}ICPS_SERIAL;

#define SD_DATA  ICPS_SERIAL
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  channel, 0),\
	APP_DEFSDMEMBER(T_STRING,  local_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_recv_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  version, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_time_zone, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_dttm, 0),\
	APP_DEFSDMEMBER(T_STRING,  msg_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_trans_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  retry, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_trans_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  in_channel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  in_channel_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  teller, 0),\
	APP_DEFSDMEMBER(T_STRING,  grant_branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  grant_teller, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param4, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param5, 0)


	APP_DECLAREFIELDS(SD_ICPS_SERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_SERIAL_H__*/
