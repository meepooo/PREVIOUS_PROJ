/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_LOAN_YX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_LOAN_YX
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_LOAN_YX_H__
#define __ICPS_WBC_TM_LOAN_YX_H__
typedef struct TDB_ICPS_WBC_TM_LOAN_YX
{
	char		busi_date[8+1];              
	int			file_order; 
	char		loan_receipt_nbr[20+1];        /*借据号                                      */
	char		merchant_id[20+1];             /*平台ID                                      */
	char		product_cd[6+1];               /*产品CD                                      */
	char		agreement_no[50+1];            /*平台协议号                                  */
	char		cnc_card_no[20+1];             /*贷款卡号                                    */
	int			loan_init_term;                /*总期数                                      */
	int			curr_term;                     /*当期期数                                    */
	int			remain_term;                   /*剩余期数                                    */
	double		interest_rate;                 /*利息利率                                    */
	char		loan_status[1+1];              /*状态                                        */
	double		loan_prin;                     /*总本金                                      */
	double		loan_paid;                     /*已还本金                                    */
	double		loan_init_interest;            /*总利息                                      */
	double		int_paid;                      /*已还利息                                    */
	char		loan_expire_date[8+1];         /*到期日期                                    */
	char		grace_date[8+1];               /*宽限日                                      */
	int			due_days;                      /*逾期天数                                    */
	char		loan_paidout_flg[1+1];         /*结清标识                                    */
	char		loan_paidout_date[8+1];        /*结清日期                                    */
	char		terminate_reason_cd[1+1];      /*终止原因代码                                */
	char		batch_date[8+1];               /*批量同步日期                                */
	char		batch_no[16+1];                /*批次号                                      */
	double		loan_bal_late_charge;          /*欠款总滞纳金                                */
	double		loan_bal_adv_pmt_fee;          /*欠款总提前还款手续费                        */
	double		loan_bal_fee;                  /*欠款总费用                                  */
	double		late_charge_paid;              /*已还滞纳金                                  */
	double		adv_pmt_fee_paid;              /*已还提前还款手续费                          */
	double		fee_paid;                      /*已还费用                                    */
	double		next_prin;                     /*下期本金                                    */
	double		next_fee;                      /*下期手续费                                  */
	char		register_date[8+1];            /*借据注册日期                                */
	double		prin_bal;                      /*欠款总本金                                  */
	double		int_bal;                       /*欠款总利息                                  */
	double		penalty_bal;                   /*欠款总罚息                                  */
	double		penalty_paid;                  /*已还罚息                                    */
	double		penalty_rate;                  /*罚息利率                                    */
	char		biz_date[8+1];                 /*业务日期                                    */
	char		created_datetime[14+1];        /*创建时间日期                                */
	char		last_modified_datetime[14+1];  /*更新时间日期                                */
	char		loan_type[20+1];               /*借据类型                                    */
	double		unearned_prin;                 /*未到期本金                                  */
	char		inst_return_flag[1+1];         /*是否已退息                                  */
	char		paid_out_return_status[1+1];   /*结清退保退息状态                            */
	char		ref_nbr[20+1];                 /*交易检索号                                  */
	char		loan_merge_type[20+1];         /*借据合并类型                                */
	double		bef_init_interest;             /*原贷款总利息                                */
	int			orig_init_term;                /*原始贷款期数                                */
	int			gl_term;                       /*总账期数，会计账期数。需要乘以还款间隔以加工*/
	char		is_check_flag[1+1];
	char		extend_param1[100+1];
	char		extend_param2[250+1];
	char		extend_param3[40+1];
}ICPS_WBC_TM_LOAN_YX;

#define SD_DATA  ICPS_WBC_TM_LOAN_YX
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr        ,0),\
	APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
	APP_DEFSDMEMBER(T_STRING,  agreement_no            ,0),\
	APP_DEFSDMEMBER(T_STRING,  cnc_card_no             ,0),\
	APP_DEFSDMEMBER(T_LONG,    loan_init_term          ,0),\
	APP_DEFSDMEMBER(T_LONG,    curr_term               ,0),\
	APP_DEFSDMEMBER(T_LONG,    remain_term             ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_rate           ,6),\
	APP_DEFSDMEMBER(T_STRING,  loan_status             ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_prin               ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_paid               ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_interest      ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_paid                ,2),\
	APP_DEFSDMEMBER(T_STRING,  loan_expire_date        ,0),\
	APP_DEFSDMEMBER(T_STRING,  grace_date              ,0),\
	APP_DEFSDMEMBER(T_LONG,    due_days                ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_paidout_flg        ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_paidout_date       ,0),\
	APP_DEFSDMEMBER(T_STRING,  terminate_reason_cd     ,0),\
	APP_DEFSDMEMBER(T_STRING,  batch_date              ,0),\
	APP_DEFSDMEMBER(T_STRING,  batch_no                ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_late_charge    ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_adv_pmt_fee    ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_fee            ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  late_charge_paid        ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  adv_pmt_fee_paid        ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_paid                ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  next_prin               ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  next_fee                ,2),\
	APP_DEFSDMEMBER(T_STRING,  register_date           ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_bal                ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_bal                 ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_bal             ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_paid            ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate            ,6),\
	APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_type               ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  unearned_prin           ,2),\
	APP_DEFSDMEMBER(T_STRING,  inst_return_flag        ,0),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_return_status  ,0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_merge_type         ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_init_interest       ,2),\
	APP_DEFSDMEMBER(T_LONG,    orig_init_term          ,0),\
	APP_DEFSDMEMBER(T_LONG,    gl_term                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_LOAN_YX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_LOAN_YX_H__*/
