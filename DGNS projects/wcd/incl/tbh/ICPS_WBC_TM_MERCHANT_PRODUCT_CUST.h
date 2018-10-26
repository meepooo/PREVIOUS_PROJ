/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
说    明:客户产品信息表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_MERCHANT_PRODUCT_CUST_H__
#define __ICPS_WBC_TM_MERCHANT_PRODUCT_CUST_H__
typedef struct TDB_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
{
	char			busi_date[8+1];
	int				file_order;
	char			user_id[32+1];                  /*平台的客户ID   */
	char			merchant_id[20+1];              /*平台ID         */
	char			product_cd[6+1];                /*产品CD         */
	char			cnc_card_no[20+1];              /*贷款卡号       */
	char			debit_card_no[19+1];            /*他行借记卡号   */
	char			wb_debit_card_no[19+1];         /*本行借记卡号   */
	char			nbs_cust_id[20+1];              /*NBS客户ID      */
	char			aps_app_time[8+1];              /*APS开户申请时间*/
	char			aps_app_no[20+1];               /*APS开户申请号  */
	char			aps_app_no_status[20+1];        /*APS申请号状态  */
	int				aps_app_count;                  /*单日申请次数   */
	char			aps_approval_date[8+1];         /*APS审批通过日期*/
	char			aps_result_level[2+1];          /*APS审批结果等级*/
	char			aps_rej_code[15+1];             /*APS审批拒绝码  */
	char			aps_rej_date[10+1];             /*APS审批拒绝时间*/
	char			cnc_setup_date[8+1];            /*开贷款户日期   */
	double			aps_credit_limit;               /*开户时授信额度 */
	char			gid[64+1];                      /*操作源GID      */
	char			oper_ip[24+1];                  /*操作源IP       */
	char			os_type[20+1];                  /*操作系统       */
	char			lbs[60+1];                      /*LBS            */
	char			ios_idfa[50+1];                 /*IOS标示符      */
	char			android_imei[50+1];             /*ANDROID蓝牙地址*/
	char			submitted_entry[3+1];           /*提交入口       */
	char			submitted_city[32+1];           /*申请城市       */
	char			reserve1[20+1];                 /*保留字段1      */
	char			reserve2[50+1];                 /*保留字段2      */
	char			reserve3[50+1];                 /*保留字段3      */
	char			biz_date[8+1];                  /*业务日期       */
	char			created_datetime[14+1];         /*创建时间日期   */
	char			last_modified_datetime[14+1];   /*更新时间日期   */
	char			app_biz_seq_no[32+1];           /*申请业务流水号 */
	char			aps_rej_reason[120+1];          /*申请拒绝原因   */
	char			app_expiry_date[8+1];           /*申请失效日期   */
	char			agent_id[20+1];                 /*代理人身份id   */
	char			agent_name[30+1];               /*代理人姓名     */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_MERCHANT_PRODUCT_CUST;

#define SD_DATA  ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
   APP_DEFSDMEMBER(T_STRING,  user_id                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
   APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
   APP_DEFSDMEMBER(T_STRING,  cnc_card_no             ,0),\
   APP_DEFSDMEMBER(T_STRING,  debit_card_no           ,0),\
   APP_DEFSDMEMBER(T_STRING,  wb_debit_card_no        ,0),\
   APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_app_time            ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_app_no              ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_app_no_status       ,0),\
   APP_DEFSDMEMBER(T_LONG,    aps_app_count           ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_approval_date       ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_result_level        ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_rej_code            ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_rej_date            ,0),\
   APP_DEFSDMEMBER(T_STRING,  cnc_setup_date          ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,  aps_credit_limit        ,2),\
   APP_DEFSDMEMBER(T_STRING,  gid                     ,0),\
   APP_DEFSDMEMBER(T_STRING,  oper_ip                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  os_type                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  lbs                     ,0),\
   APP_DEFSDMEMBER(T_STRING,  ios_idfa                ,0),\
   APP_DEFSDMEMBER(T_STRING,  android_imei            ,0),\
   APP_DEFSDMEMBER(T_STRING,  submitted_entry         ,0),\
   APP_DEFSDMEMBER(T_STRING,  submitted_city          ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve1                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve2                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve3                ,0),\
   APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
   APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
   APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
   APP_DEFSDMEMBER(T_STRING,  app_biz_seq_no          ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_rej_reason          ,0),\
   APP_DEFSDMEMBER(T_STRING,  app_expiry_date         ,0),\
   APP_DEFSDMEMBER(T_STRING,  agent_id                ,0),\
   APP_DEFSDMEMBER(T_STRING,  agent_name              ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)

  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_APP_MAIN_H__*/
                                                                                                                                                  
