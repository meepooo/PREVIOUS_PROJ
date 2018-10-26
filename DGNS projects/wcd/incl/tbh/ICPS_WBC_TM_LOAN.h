/***********************************************************************    
��Ȩ����:�������ӹɷ����޹�˾                                                             
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ                                                     
��    ��:V1.00                                                                
����ϵͳ:                                                                       
�� �� ��:INFORMIX                                                              
�� �� ��:ICPS_WBC_TM_LOAN.h                                                
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�                                                         
�� Ŀ ��:                                                                      
�� �� Ա:[fuwd22392]                                                         
����ʱ��:2018-06-12 10:00:00 [Gen]                                              
��    ��:                                                                     
�޸�ʱ��:                                                                       
************************************************************************    
��    ��:ICPS_WBC_TM_LOAN                                                 
˵    ��:������Ϣ��                                                                     
************************************************************************    
�޸ļ�¼:195                                                                    
�޸�����:                                                                       
�޸�����:                                                                       
�� �� ��:                                                                      
�޸�����:                                                                       
************************************************************************/ 
#ifndef __ICPS_WBC_TM_LOAN_H__
#define __ICPS_WBC_TM_LOAN_H__
typedef struct TDB_ICPS_WBC_TM_LOAN
{  
	char		busi_date[8+1];                                 /*                                */
	int	  		file_order;                                     /*                                */
	char		org[12+1];                                      /* ������                         */
	char 		loan_id[20+1];                                 /* ���ڼƻ�ID  fuwd22392 M          */
	char 		acct_no[20+1];                                  /* �˻����   fuwd22392 M          */
	char		acct_type[1+1];	                                /* �˻�����                       */
	char		ref_nbr[23+1];	                                /* ���ײο���                     */
	char		logical_card_no[19+1];	                        /* �߼�����                       */
	char		card_no[19+1];	                                /* ����                           */
	char		register_date[8+1];	                            /* ����ע������                   */
	char		request_time[14+1];	                            /* ��������ʱ��                   */
	char		loan_type[5+1];	                                /* ��������                       */
	char		loan_status[1+1];	                              /* ����״̬                       */
	char		last_loan_status[1+1];	                        /* �����ϴ�״̬                   */
	int			loan_init_term;                                 /* ����������                     */
	int			curr_term;                                      /* ��ǰ����                       */
	int			remain_term;                                    /* ʣ������                       */
	double		loan_init_prin;                                 /* �����ܱ���                     */
	double		loan_fixed_pmt_prin;                            /* ����ÿ��Ӧ������               */
	double		loan_first_term_prin;                           /* ��������Ӧ������               */
	double		loan_final_term_prin;                           /* ����ĩ��Ӧ������               */
	double		loan_init_fee1;                                 /* ������������                   */
	double		loan_fixed_fee1;                                /* ����ÿ��������                 */
	double		loan_first_term_fee1;                           /* ��������������                 */
	double		loan_final_term_fee1;                           /* ����ĩ��������                 */
	double		unearned_prin;                                  /* δ���˵��ı���                 */
	double		unearned_fee1;                                  /* δ���˵�������                 */
	char		paid_out_date[8+1];                             /* ��������                       */
	char		terminate_date[8+1];                            /* ��ǰ��ֹ����                   */
	char		terminate_reason_cd[1+1];                       /* ������ֹԭ�����               */
	double		prin_paid;                                      /* �ѳ�������                     */
	double		int_paid;                                       /* �ѳ�����Ϣ                     */
	double		fee_paid;                                       /* �ѳ�������                     */
	double		loan_curr_bal;                                  /* ���ڵ�ǰ�����                 */
	double		loan_bal_xfrout;                                /* ����δ�������                 */
	double		loan_bal_xfrin;                                 /* �����ѳ��˵����               */
	double		loan_bal_principal;                             /* Ƿ���ܱ���                     */
	double		loan_bal_interest;                              /* Ƿ������Ϣ                     */
	double		loan_bal_penalty;                               /* Ƿ���ܷ�Ϣ                     */
	double		loan_prin_xfrout;                               /* ����δ���ڱ���                 */
	double		loan_prin_xfrin;                                /* �����ѳ��˵�����               */
	double		loan_fee1_xfrout;                               /* ����δ����������               */
	double		loan_fee1_xfrin;                                /* �����ѳ��˵�������             */
	double		orig_txn_amt;                                   /* ԭʼ���ױ��ֽ��               */
	char		orig_trans_date[8+1];                           /* ԭʼ��������                   */
	char		orig_auth_code [6+1];                           /* ԭʼ������Ȩ��                 */
	int			jpa_version;                                    /* �ֹ����汾��                   */
	char		loan_code[4+1];                                 /* ���ڼƻ�����                   */
	char		register_id[20+1];                                    /* ��������˳��� fuwd22392 M     */
	double		resch_init_prin;                                /* չ�ڱ�����                   */
	char		resch_date[8+1];	                              /* չ����Ч����                   */
	double		bef_resch_fixed_pmt_prin;                       /* չ��ǰÿ��Ӧ������             */
	int			bef_resch_init_term;                            /* չ��ǰ������                   */
	double		bef_resch_first_term_prin;                      /* չ��ǰ��������Ӧ������         */
	double		bef_resch_final_term_prin;                      /* չ��ǰ����ĩ��Ӧ������         */
	double		bef_resch_init_fee1;                            /* չ��ǰ������������             */
	double		bef_resch_fixed_fee1;                           /* ����ÿ��������                 */
	double		bef_resch_first_term_fee1;                      /* չ��ǰ��������������           */
	double		bef_resch_final_term_fee1;                      /* չ��ǰ����ĩ��������           */
	double		resch_first_term_fee1;                          /* չ�ں�����������               */
	char		loan_fee_method[1+1];	                          /* ������������ȡ��ʽ             */
	double		interest_rate;                                  /* ��������                       */
	double		penalty_rate;                                   /* ��Ϣ����                       */
	double		compound_rate;                                  /* ��������                       */
	double		float_rate;                                     /* ��������                       */
	char		loan_receipt_nbr[20+1];	                        /* ��ݺ�                         */
	char		loan_expire_date[8+1];	                        /* ���������                   */
	char		loan_cd[2+1];	                                  /* ���������������               */
	char		payment_hist[24+1];	                            /* 24���»���״̬                 */
	double		ctd_payment_amt;                                /* ���ڻ����                     */
	int			past_resch_cnt;                                 /* ��չ�ڴ���                     */
	int			past_shorted_cnt;                               /* �����ڴ���                     */
	double		adv_pmt_amt;                                    /* ��ǰ������                   */
	char		last_action_date[8+1];	                        /* �ϴ��ж�����                   */
	char		last_action_type[1+1];	                        /* �ϴ��ж�����                   */
	char		last_modified_datetime[14+1];	                  /* �޸�ʱ��                       */
	char		activate_date[8+1];	                            /* ��������                       */
	char		interest_calc_base[1+1];	                      /* ��Ϣ����                       */
	char		first_bill_date[8+1];	                          /* �׸��˵���                     */
	char		age_cd[1+1];	                                  /* ����                           */
	char		recalc_ind[1+1];	                              /* ���������־                   */
	char		recalc_date[8+1];	                              /* ����������                     */
	char		grace_date[8+1];	                              /* ��������                       */
	char		cancel_date[8+1];	                              /* ��������                       */
	char		cancel_reason[100+1];                           /* �����ԭ��                   */
	char		bank_group_id[5+1];	                            /* ���ű��                       */
	int			due_days;                                       /* ��ǰ��������                   */
	char		contract_ver[200+1];                            /* ��ͬ�汾��                     */
	double		loan_init_interest;                             /* ��������Ϣ                     */
	double		bef_init_interest;                              /* ԭ��������Ϣ                   */
	double		penalty_paid;                                   /* �ѻ���Ϣ                       */
	double		compound_paid;                                  /* �ѻ�����                       */
	double		late_charge_paid;                               /* �ѻ����ɽ�                     */
	double		loan_bal_late_charge;                           /* Ƿ�������ɽ�                   */
	char		next_xfr_date[8+1];	                            /* ��һ��ת��                     */
	char		next_late_charge_date[8+1];	                    /* ��һ���ɽ���ȡ��               */
	double		fee_rate;                                       /* ����                           */
	double		late_charge_fee_rate;                           /* ���ɽ����                     */
	double		adv_pmt_fee_rate;                               /* ��ǰ���������ѷ���             */
	double		loan_bal_adv_pmt_fee;                           /* ��ǰ������������Ƿ��           */
	double		adv_pmt_fee_paid;                               /* �ѻ���ǰ����������             */
	char		last_xfr_date[8+1];	                            /* ��һ��ת����                   */
	double		loan_bal_fee;                                   /* Ƿ���ܷ���                     */
	char		payee_card_no[40+1];	                          /* �տ��                       */
	char		payee_bank_name[60+1];	                        /* �տ�������                     */
	char		billing_cycle[2+1];	                            /* �˵���                         */
	char		last_stmt_date[8+1];	                          /* �ϸ��˵�����                   */
	char		next_stmt_date[8+1];	                          /* �¸��˵�����                   */
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
                                                              
                                                              
