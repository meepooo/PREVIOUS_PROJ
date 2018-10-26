/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_RRS_CLEAR_DETAIL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_RRS_CLEAR_DETAIL (F_WB21.备付金资金清算明细)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_RRS_CLEAR_DETAIL_H__
#define __ICPS_WB_RRS_CLEAR_DETAIL_H__
typedef struct TDB_ICPS_WB_RRS_CLEAR_DETAIL
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   data_dt[10+1];  /*数据日期*/
		/*数据日期:YYYY-MM-DD */
	char   acct_no[40+1];  /*备付金帐号*/
		/*备付金帐号*/
	char   currency[3+1];  /*币种*/
		/*币种:CNY-人民币 */
	char   bank_group_code[5+1];  /*银团编号*/
		/*银团编号:除1、3类型外，其他数据类型的均为为ZZZZZ */
	char   data_type[6+1];  /*数据类型*/
		/*数据类型： 1：放款 2：放款撤销 3：还款 4：还款撤销 5：其他划入款项 6：其他划出款项" */
	double   amount;  /*发生额*/
		/*发生额*/
	char   ds[10+1];  /*日期分区*/
		/*日期分区*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_RRS_CLEAR_DETAIL;

#define SD_DATA  ICPS_WB_RRS_CLEAR_DETAIL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  data_dt, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  data_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  amount, 4),\
	APP_DEFSDMEMBER(T_STRING,  ds, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_RRS_CLEAR_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_RRS_CLEAR_DETAIL_H__*/
