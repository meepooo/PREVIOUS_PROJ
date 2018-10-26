/***********************************************************************    
版权所有:恒生电子股份有限公司                                                             
项目名称:综合技术平台(Turandot)项目                                                     
版    本:V1.00                                                                
操作系统:                                                                       
数 据 库:INFORMIX                                                              
文 件 名:ICPS_WBC_TM_LOAN.h                                                
文件描述:结构定义数据库开发嵌C头文件                                                         
项 目 组:                                                                      
程 序 员:[fuwd22392]                                                         
发布时间:2018-06-12 10:00:00 [Gen]                                              
修    订:                                                                     
修改时间:                                                                       
************************************************************************    
表    名:ICPS_WBC_TM_LOAN                                                 
说    明:分期信息表                                                                     
************************************************************************    
修改记录:195                                                                    
修改日期:                                                                       
修改内容:                                                                       
修 改 人:                                                                      
修改内容:                                                                       
************************************************************************/ 
#ifndef __ICPS_WBC_TM_LOAN_H__
#define __ICPS_WBC_TM_LOAN_H__
typedef struct TDB_ICPS_WBC_TM_LOAN
{  
	char		busi_date[8+1];                                 /*                                */
	int	  		file_order;                                     /*                                */
	char		org[12+1];                                      /* 机构号                         */
	char 		loan_id[20+1];                                 /* 分期计划ID  fuwd22392 M          */
	char 		acct_no[20+1];                                  /* 账户编号   fuwd22392 M          */
	char		acct_type[1+1];	                                /* 账户类型                       */
	char		ref_nbr[23+1];	                                /* 交易参考号                     */
	char		logical_card_no[19+1];	                        /* 逻辑卡号                       */
	char		card_no[19+1];	                                /* 卡号                           */
	char		register_date[8+1];	                            /* 分期注册日期                   */
	char		request_time[14+1];	                            /* 请求日期时间                   */
	char		loan_type[5+1];	                                /* 分期类型                       */
	char		loan_status[1+1];	                              /* 分期状态                       */
	char		last_loan_status[1+1];	                        /* 分期上次状态                   */
	int			loan_init_term;                                 /* 分期总期数                     */
	int			curr_term;                                      /* 当前期数                       */
	int			remain_term;                                    /* 剩余期数                       */
	double		loan_init_prin;                                 /* 分期总本金                     */
	double		loan_fixed_pmt_prin;                            /* 分期每期应还本金               */
	double		loan_first_term_prin;                           /* 分期首期应还本金               */
	double		loan_final_term_prin;                           /* 分期末期应还本金               */
	double		loan_init_fee1;                                 /* 分期总手续费                   */
	double		loan_fixed_fee1;                                /* 分期每期手续费                 */
	double		loan_first_term_fee1;                           /* 分期首期手续费                 */
	double		loan_final_term_fee1;                           /* 分期末期手续费                 */
	double		unearned_prin;                                  /* 未出账单的本金                 */
	double		unearned_fee1;                                  /* 未出账单手续费                 */
	char		paid_out_date[8+1];                             /* 还清日期                       */
	char		terminate_date[8+1];                            /* 提前终止日期                   */
	char		terminate_reason_cd[1+1];                       /* 分期终止原因代码               */
	double		prin_paid;                                      /* 已偿还本金                     */
	double		int_paid;                                       /* 已偿还利息                     */
	double		fee_paid;                                       /* 已偿还费用                     */
	double		loan_curr_bal;                                  /* 分期当前总余额                 */
	double		loan_bal_xfrout;                                /* 分期未到期余额                 */
	double		loan_bal_xfrin;                                 /* 分期已出账单余额               */
	double		loan_bal_principal;                             /* 欠款总本金                     */
	double		loan_bal_interest;                              /* 欠款总利息                     */
	double		loan_bal_penalty;                               /* 欠款总罚息                     */
	double		loan_prin_xfrout;                               /* 分期未到期本金                 */
	double		loan_prin_xfrin;                                /* 分期已出账单本金               */
	double		loan_fee1_xfrout;                               /* 分期未到期手续费               */
	double		loan_fee1_xfrin;                                /* 分期已出账单手续费             */
	double		orig_txn_amt;                                   /* 原始交易币种金额               */
	char		orig_trans_date[8+1];                           /* 原始交易日期                   */
	char		orig_auth_code [6+1];                           /* 原始交易授权码                 */
	int			jpa_version;                                    /* 乐观锁版本号                   */
	char		loan_code[4+1];                                 /* 分期计划代码                   */
	char		register_id[20+1];                                    /* 分期申请顺序号 fuwd22392 M     */
	double		resch_init_prin;                                /* 展期本金金额                   */
	char		resch_date[8+1];	                              /* 展期生效日期                   */
	double		bef_resch_fixed_pmt_prin;                       /* 展期前每期应还本金             */
	int			bef_resch_init_term;                            /* 展期前总期数                   */
	double		bef_resch_first_term_prin;                      /* 展期前分期首期应还本金         */
	double		bef_resch_final_term_prin;                      /* 展期前分期末期应还本金         */
	double		bef_resch_init_fee1;                            /* 展期前分期总手续费             */
	double		bef_resch_fixed_fee1;                           /* 分期每期手续费                 */
	double		bef_resch_first_term_fee1;                      /* 展期前分期首期手续费           */
	double		bef_resch_final_term_fee1;                      /* 展期前分期末期手续费           */
	double		resch_first_term_fee1;                          /* 展期后首期手续费               */
	char		loan_fee_method[1+1];	                          /* 分期手续费收取方式             */
	double		interest_rate;                                  /* 基础利率                       */
	double		penalty_rate;                                   /* 罚息利率                       */
	double		compound_rate;                                  /* 复利利率                       */
	double		float_rate;                                     /* 浮动比例                       */
	char		loan_receipt_nbr[20+1];	                        /* 借据号                         */
	char		loan_expire_date[8+1];	                        /* 贷款到期日期                   */
	char		loan_cd[2+1];	                                  /* 贷款逾期最大期数               */
	char		payment_hist[24+1];	                            /* 24个月还款状态                 */
	double		ctd_payment_amt;                                /* 当期还款额                     */
	int			past_resch_cnt;                                 /* 已展期次数                     */
	int			past_shorted_cnt;                               /* 已缩期次数                     */
	double		adv_pmt_amt;                                    /* 提前还款金额                   */
	char		last_action_date[8+1];	                        /* 上次行动日期                   */
	char		last_action_type[1+1];	                        /* 上次行动类型                   */
	char		last_modified_datetime[14+1];	                  /* 修改时间                       */
	char		activate_date[8+1];	                            /* 激活日期                       */
	char		interest_calc_base[1+1];	                      /* 计息基数                       */
	char		first_bill_date[8+1];	                          /* 首个账单日                     */
	char		age_cd[1+1];	                                  /* 账龄                           */
	char		recalc_ind[1+1];	                              /* 利率重算标志                   */
	char		recalc_date[8+1];	                              /* 利率重算日                     */
	char		grace_date[8+1];	                              /* 宽限日期                       */
	char		cancel_date[8+1];	                              /* 撤销日期                       */
	char		cancel_reason[100+1];                           /* 贷款撤销原因                   */
	char		bank_group_id[5+1];	                            /* 银团编号                       */
	int			due_days;                                       /* 当前逾期天数                   */
	char		contract_ver[200+1];                            /* 合同版本号                     */
	double		loan_init_interest;                             /* 贷款总利息                     */
	double		bef_init_interest;                              /* 原贷款总利息                   */
	double		penalty_paid;                                   /* 已还罚息                       */
	double		compound_paid;                                  /* 已还复利                       */
	double		late_charge_paid;                               /* 已还滞纳金                     */
	double		loan_bal_late_charge;                           /* 欠款总滞纳金                   */
	char		next_xfr_date[8+1];	                            /* 下一结转日                     */
	char		next_late_charge_date[8+1];	                    /* 下一滞纳金收取日               */
	double		fee_rate;                                       /* 费率                           */
	double		late_charge_fee_rate;                           /* 滞纳金费率                     */
	double		adv_pmt_fee_rate;                               /* 提前还款手续费费率             */
	double		loan_bal_adv_pmt_fee;                           /* 提前还款手续费总欠款           */
	double		adv_pmt_fee_paid;                               /* 已还提前还款手续费             */
	char		last_xfr_date[8+1];	                            /* 上一结转日期                   */
	double		loan_bal_fee;                                   /* 欠款总费用                     */
	char		payee_card_no[40+1];	                          /* 收款卡号                       */
	char		payee_bank_name[60+1];	                        /* 收款行名称                     */
	char		billing_cycle[2+1];	                            /* 账单日                         */
	char		last_stmt_date[8+1];	                          /* 上个账单日期                   */
	char		next_stmt_date[8+1];	                          /* 下个账单日期                   */
	char		is_check_flag[1+1];	                            /*                                */
	char		extend_param1[100+1];                           /*                                */
	char		extend_param2[250+1];                           /*                                */
	char		extend_param3[40+1];                            /*                                 */
}ICPS_WBC_TM_LOAN;

#define SD_DATA  ICPS_WBC_TM_LOAN
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,		busi_date                    ,0),\
  APP_DEFSDMEMBER(T_LONG,  	 	file_order                   ,0),\
  APP_DEFSDMEMBER(T_STRING,		org                          ,0),\
  APP_DEFSDMEMBER(T_STRING,     loan_id                      ,0),\
  APP_DEFSDMEMBER(T_STRING,  	acct_no                      ,0),\
  APP_DEFSDMEMBER(T_STRING,		acct_type                    ,0),\
  APP_DEFSDMEMBER(T_STRING,		ref_nbr                      ,0),\
  APP_DEFSDMEMBER(T_STRING,		logical_card_no              ,0),\
  APP_DEFSDMEMBER(T_STRING,		card_no                      ,0),\
  APP_DEFSDMEMBER(T_STRING,		register_date                ,0),\
  APP_DEFSDMEMBER(T_STRING,		request_time                 ,0),\
  APP_DEFSDMEMBER(T_STRING,		loan_type                    ,0),\
  APP_DEFSDMEMBER(T_STRING,		loan_status                  ,0),\
  APP_DEFSDMEMBER(T_STRING,		last_loan_status             ,0),\
  APP_DEFSDMEMBER(T_LONG,  		loan_init_term               ,0),\
  APP_DEFSDMEMBER(T_LONG,  		curr_term                    ,0),\
  APP_DEFSDMEMBER(T_LONG,  		remain_term                  ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_init_prin               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_fixed_pmt_prin          ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_first_term_prin         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_final_term_prin         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_init_fee1               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_fixed_fee1              ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_first_term_fee1         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_final_term_fee1         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		unearned_prin                ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		unearned_fee1                ,0),\
  APP_DEFSDMEMBER(T_STRING,		paid_out_date                ,0),\
  APP_DEFSDMEMBER(T_STRING,		terminate_date               ,0),\
  APP_DEFSDMEMBER(T_STRING,		terminate_reason_cd          ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,		prin_paid                    ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		int_paid                     ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		fee_paid                     ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_curr_bal                ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_xfrout              ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_xfrin               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_principal           ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_interest            ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_penalty             ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_prin_xfrout             ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_prin_xfrin              ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_fee1_xfrout             ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		loan_fee1_xfrin              ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		orig_txn_amt                 ,2),\
  APP_DEFSDMEMBER(T_STRING,		orig_trans_date              ,0),\
  APP_DEFSDMEMBER(T_STRING,		orig_auth_code               ,0),\
  APP_DEFSDMEMBER(T_LONG,  		jpa_version                  ,0),\
  APP_DEFSDMEMBER(T_STRING,		loan_code                    ,0),\
  APP_DEFSDMEMBER(T_LONG,  		register_id                  ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,		resch_init_prin              ,2),\
  APP_DEFSDMEMBER(T_STRING,		resch_date                   ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,		bef_resch_fixed_pmt_prin     ,2),\
  APP_DEFSDMEMBER(T_LONG,  		bef_resch_init_term          ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,		bef_resch_first_term_prin    ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		bef_resch_final_term_prin    ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		bef_resch_init_fee1          ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		bef_resch_fixed_fee1         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		bef_resch_first_term_fee1    ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		bef_resch_final_term_fee1    ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,		resch_first_term_fee1        ,2),\
  APP_DEFSDMEMBER(T_STRING,		loan_fee_method              ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,		interest_rate                ,4),\
  APP_DEFSDMEMBER(T_DOUBLE,		penalty_rate                 ,4),\
  APP_DEFSDMEMBER(T_DOUBLE,		compound_rate                ,4),\
  APP_DEFSDMEMBER(T_DOUBLE,		float_rate                   ,2),\
  APP_DEFSDMEMBER(T_STRING,		loan_receipt_nbr             ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		loan_expire_date             ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		loan_cd                      ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		payment_hist                 ,0),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		ctd_payment_amt              ,2),\ 
  APP_DEFSDMEMBER(T_LONG,  		past_resch_cnt               ,0),\ 
  APP_DEFSDMEMBER(T_LONG,  		past_shorted_cnt             ,0),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		adv_pmt_amt                  ,2),\ 
  APP_DEFSDMEMBER(T_STRING,		last_action_date             ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		last_action_type             ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		last_modified_datetime       ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		activate_date                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		interest_calc_base           ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		first_bill_date              ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		age_cd                       ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		recalc_ind                   ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		recalc_date                  ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		grace_date                   ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		cancel_date                  ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		cancel_reason                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		bank_group_id                ,0),\ 
  APP_DEFSDMEMBER(T_LONG,  		due_days                     ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		contract_ver                 ,0),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		loan_init_interest           ,2),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		bef_init_interest            ,2),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		penalty_paid                 ,2),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		compound_paid                ,2),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		late_charge_paid             ,2),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_late_charge         ,2),\ 
  APP_DEFSDMEMBER(T_STRING,		next_xfr_date                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		next_late_charge_date        ,0),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		fee_rate                     ,7),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		late_charge_fee_rate         ,7),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		adv_pmt_fee_rate             ,7),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_adv_pmt_fee         ,2),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		adv_pmt_fee_paid             ,2),\ 
  APP_DEFSDMEMBER(T_STRING,		last_xfr_date                ,0),\ 
  APP_DEFSDMEMBER(T_DOUBLE,		loan_bal_fee                 ,2),\ 
  APP_DEFSDMEMBER(T_STRING,		payee_card_no                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		payee_bank_name              ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		billing_cycle                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		last_stmt_date               ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		next_stmt_date               ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		is_check_flag                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		extend_param1                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		extend_param2                ,0),\ 
  APP_DEFSDMEMBER(T_STRING,		extend_param3                ,0) 
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_LOAN)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __ICPS_WBC_TM_LOAN_H__*/
                                                              
                                                              
