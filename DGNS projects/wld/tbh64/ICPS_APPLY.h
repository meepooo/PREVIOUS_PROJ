/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_APPLY.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_APPLY (2.授信申请流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_APPLY_H__
#define __ICPS_APPLY_H__
typedef struct TDB_ICPS_APPLY
{
	char   busi_no[16+1];  /*业务编号*/
		/*业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷*/
	char   apply_no[64+1];  /*申请单号*/
		/*申请单号*/
	char   id_type[2+1];  /*证件类型*/
		/*证件类型*/
	char   id_num[32+1];  /*证件号码*/
		/*证件号码*/
	char   id_valid_end_date[8+1];  /*证件有效期*/
		/*证件有效期*/
	char   name[64+1];  /*姓名*/
		/*姓名*/
	char   mobile_no[32+1];  /*手机号*/
		/*手机号*/
	char   auth_flag[1+1];  /*芝麻授权成功标识*/
		/*芝麻授权成功标识 Y-授权成功 N-授权失败*/
	char   has_admit_flag[1+1];  /*之前是否有额度*/
		/*之前是否有额度 Y-之前有额度，N-之前没有额度*/
	char   apply_plt_date[8+1];  /*授信申请平台日期*/
		/*授信申请平台日期*/
	char   apply_plt_serial[16+1];  /*授信申请平台流水号*/
		/*授信申请平台流水号*/
	char   apply_status[1+1];  /*授信申请状态*/
		/*授信申请状态 0-成功 1-失败 6-未知 9-初始*/
	char   credit_no[32+1];  /*授信编号*/
		/*授信编号*/
	char   info_admit_flag[1+1];  /*银行是否推荐准入*/
		/*银行是否推荐准入 Y-准入 N-不准入*/
	double   credit_amt;  /*推荐额度*/
		/*推荐额度*/
	double   credit_rate;  /*推荐利率*/
		/*推荐利率*/
	char   refuse_code[64+1];  /*拒绝码*/
		/*拒绝码*/
	char   refuse_reason[1024+1];  /*拒绝原因*/
		/*拒绝原因*/
	char   info_plt_date[8+1];  /*银行初审平台日期*/
		/*银行初审平台日期*/
	char   info_plt_serial[16+1];  /*银行初审平台流水号*/
		/*银行初审平台流水号*/
	char   info_status[1+1];  /*初审状态*/
		/*初审状态 0-成功 1-失败 6-未知 9-初始*/
	char   third_access[1+1];  /*是否通过审批*/
		/*是否通过审批 Y-通过 N-不通过*/
	char   third_refuse_reason[1024+1];  /*审批不通过原因*/
		/*审批不通过原因*/
	double   third_amt;  /*审批额度*/
		/*审批额度*/
	double   third_rate;  /*审批基础利率*/
		/*审批基础利率*/
	char   risk_rating[1+1];  /*风险评级*/
		/*风险评级*/
	char   solvency_rating[1+1];  /*偿债能力评级*/
		/*偿债能力评级*/
	char   change_result_reason[1024+1];  /*额度定价变更原因*/
		/*额度定价变更原因*/
	char   ack_admit_flag[1+1];  /*终审银行是否准入*/
		/*终审银行是否准入 Y-准入 N-不准入*/
	char   ack_admit_msg[255+1];  /*准入原因*/
		/*准入原因*/
	char   ack_plt_date[8+1];  /*终审平台日期*/
		/*终审平台日期*/
	char   ack_plt_serial[16+1];  /*终审平台流水号*/
		/*终审平台流水号*/
	char   ack_status[1+1];  /*终审状态*/
		/*终审状态 0-成功 1-失败 6-未知 9-初始*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_APPLY;

#define SD_DATA  ICPS_APPLY
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_valid_end_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  auth_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  has_admit_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  credit_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_admit_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  credit_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  credit_rate, 6),\
	APP_DEFSDMEMBER(T_STRING,  refuse_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  refuse_reason, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_access, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_refuse_reason, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  third_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  third_rate, 6),\
	APP_DEFSDMEMBER(T_STRING,  risk_rating, 0),\
	APP_DEFSDMEMBER(T_STRING,  solvency_rating, 0),\
	APP_DEFSDMEMBER(T_STRING,  change_result_reason, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_admit_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_admit_msg, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_APPLY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_APPLY_H__*/
