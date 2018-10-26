/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_AUTH_BANK_COST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_AUTH_BANK_COST
说    明:授权流水银团拆分表
************************************************************************
修改记录:195
修改日期:
修改内容:
修 改 人:
修改内容:
***************************************/
#ifndef __ICPS_WBC_TM_AUTH_BANK_COST_H__
#define __ICPS_WBC_TM_AUTH_BANK_COST_H__
typedef struct TDB_ICPS_WBC_TM_AUTH_BANK_COST
{
	char         busi_date[8+1];                   
	int          file_order;
	char         consumer_trans_id[32+1];                 /*业务流水号   */
	char         bank_group_id[5+1];                      /*银团编号     */
	char         bank_no[10+1];                           /*银行号       */
	char         reg_type[50+1];                          /*登记类型     */
	double       reg_amt;                                 /*登记金额     */
	char         reg_status[10+1];                        /*登记状态     */
	char         biz_date[8+1];                           /*业务日期     */
	char         reg_sys_id[32+1];                        /*记账流水号   */
	char         reg_date[14+1];                           /*记账日期     */
	char         reg_time[14+1];                          /*记账请求时间 */
	char         recon_code[20+1];                        /*对账码       */
	char         ori_sys_id[32+1];                        /*原记账流水号 */
	char         cust_id[20+1];                           /*客户编号     */
	char         acct_no[20+1];                           /*账户编号     */
	char         acct_type[1+1];                          /*账户类型     */
	int          retry;                                   /*尝试次数     */
	char         created_datetime[14+1];                  /*创建时间     */
	char         last_modified_datetime[14+1];            /*时间戳       */
	int          jpa_version;                             /*乐观锁版本号 */
	char         card_no[19+1];                           /*卡号         */
	char         is_check_flag[1+1];
	char         extend_param1[100+1];
	char         extend_param2[250+1];
	char         extend_param3[40+1];
}ICPS_WBC_TM_AUTH_BANK_COST;
		
#define SD_DATA  ICPS_WBC_TM_AUTH_BANK_COST
#define SD_MEMBERS \ 		
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  consumer_trans_id       ,0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id           ,0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  reg_type                ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  reg_amt                 ,2),\
	APP_DEFSDMEMBER(T_STRING,  reg_status              ,0),\
	APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
	APP_DEFSDMEMBER(T_STRING,  reg_sys_id              ,0),\
	APP_DEFSDMEMBER(T_STRING,  reg_date                ,0),\
	APP_DEFSDMEMBER(T_STRING,  reg_time                ,0),\
	APP_DEFSDMEMBER(T_STRING,  recon_code              ,0),\
	APP_DEFSDMEMBER(T_STRING,  ori_sys_id              ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type               ,0),\
	APP_DEFSDMEMBER(T_LONG,   retry                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_LONG,   jpa_version             ,0),\
	APP_DEFSDMEMBER(T_STRING,  card_no                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
	APP_DECLAREFIELDS(SD_ICPS_WBC_TM_AUTH_BANK_COST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_AUTH_BANK_COST_H__*/
