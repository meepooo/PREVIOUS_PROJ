/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_DS_DIFF_LIST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_DS_DIFF_LIST (F_WB28.待核销借据与已核销借据差异表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_DS_DIFF_LIST_H__
#define __ICPS_WB_DS_DIFF_LIST_H__
typedef struct TDB_ICPS_WB_DS_DIFF_LIST
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   id_num[30+1];  /*证件号*/
		/*证件号*/
	char   id_type[1+1];  /*证件类型*/
		/*证件类型*/
	char   cust_id[20+1];  /*客户号*/
		/*客户号*/
	char   product_code[6+1];  /*产品号*/
		/*产品号*/
	char   acct_no[20+1];  /*账号*/
		/*账号*/
	char   acct_type[1+1];  /*账户类型*/
		/*账户类型*/
	char   logical_card_no[19+1];  /*卡号*/
		/*卡号*/
	char   ref_nbr[23+1];  /*参考号*/
		/*参考号*/
	double   loan_init_prin;  /*本金*/
		/*本金*/
	char   bank_group_id[5+1];  /*银团号*/
		/*银团号*/
	char   writeoff_proc_status[20+1];  /*核销状态*/
		/*核销状态*/
	char   writeoff_proc_desc[100+1];  /*未核销原因*/
		/*未核销原因*/
	char   product_attr[5+1];  /*产品属性*/
		/*产品属性*/
	char   name[200+1];  /*姓名*/
		/*姓名*/
	char   writeoff_date[10+1];  /*核销日期*/
		/*核销日期*/
	char   bank_no[20+1];  /*银行号*/
		/*银行号*/
	double   bank_proportion;  /*银团比例*/
		/*银团比例*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_DS_DIFF_LIST;

#define SD_DATA  ICPS_WB_DS_DIFF_LIST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_prin, 2),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  writeoff_proc_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  writeoff_proc_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_attr, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  writeoff_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_DIFF_LIST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_DIFF_LIST_H__*/
