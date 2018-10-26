/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_LOAN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_LOAN (F_WB11.������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_LOAN_H__
#define __ICPS_WB_TM_LOAN_H__
typedef struct TDB_ICPS_WB_TM_LOAN
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   loan_id[20+1];  /*���ID*/
		/*���ID*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	char   ref_nbr[23+1];  /*���ײο���*/
		/*���ײο���*/
	char   logical_card_no[19+1];  /*�߼�����*/
		/*�߼�����*/
	char   card_no[19+1];  /*����*/
		/*����*/
	char   register_date[14+1];  /*����ע������*/
		/*����ע������*/
	char   request_time[14+1];  /*��������ʱ��*/
		/*��������ʱ��*/
	char   loan_type[5+1];  /*��������*/
		/*��������*/
	char   loan_status[1+1];  /*����״̬*/
		/*����״̬*/
	char   last_loan_status[1+1];  /*�����ϴ�״̬*/
		/*�����ϴ�״̬*/
	int   loan_init_term;  /*����������*/
		/*����������*/
	int   curr_term;  /*��ǰ����*/
		/*��ǰ����*/
	int   remain_term;  /*ʣ������*/
		/*ʣ������*/
	double   loan_init_prin;  /*�����ܱ���*/
		/*�����ܱ���*/
	double   loan_fixed_pmt_prin;  /*����ÿ��Ӧ������*/
		/*����ÿ��Ӧ������*/
	double   loan_first_term_prin;  /*��������Ӧ������*/
		/*��������Ӧ������*/
	double   loan_final_term_prin;  /*����ĩ��Ӧ������*/
		/*����ĩ��Ӧ������*/
	double   loan_init_fee1;  /*������������*/
		/*������������*/
	double   loan_fixed_fee1;  /*����ÿ��������*/
		/*����ÿ��������*/
	double   loan_first_term_fee1;  /*��������������*/
		/*��������������*/
	double   loan_final_term_fee1;  /*����ĩ��������*/
		/*����ĩ��������*/
	double   unearned_prin;  /*�����˵��ı���*/
		/*�����˵��ı���*/
	double   unearned_fee1;  /*�����˵�������*/
		/*�����˵�������*/
	char   paid_out_date[14+1];  /*��������*/
		/*��������*/
	char   terminate_date[14+1];  /*��ǰ��ֹ����*/
		/*��ǰ��ֹ����*/
	char   terminate_reason_cd[1+1];  /*������ֹԭ�����*/
		/*������ֹԭ�����*/
	double   prin_paid;  /*�ѳ�������*/
		/*�ѳ�������*/
	double   int_paid;  /*�ѳ�����Ϣ*/
		/*�ѳ�����Ϣ*/
	double   fee_paid;  /*�ѳ�������*/
		/*�ѳ�������*/
	double   loan_curr_bal;  /*���ǰ�����*/
		/*���ǰ�����*/
	double   loan_bal_xfrout;  /*����δ�������*/
		/*����δ�������*/
	double   loan_bal_xfrin;  /*�����ѵ������*/
		/*�����ѵ������*/
	double   loan_bal_principal;  /*Ƿ���ܱ���*/
		/*Ƿ���ܱ���*/
	double   loan_bal_interest;  /*Ƿ������Ϣ*/
		/*Ƿ������Ϣ*/
	double   loan_bal_penalty;  /*Ƿ���ܷ�Ϣ*/
		/*Ƿ���ܷ�Ϣ*/
	double   loan_prin_xfrout;  /*����δ���ڱ���*/
		/*����δ���ڱ���*/
	double   loan_prin_xfrin;  /*�����ѵ��ڱ���*/
		/*�����ѵ��ڱ���*/
	double   loan_fee1_xfrout;  /*����δ����������*/
		/*����δ����������*/
	double   loan_fee1_xfrin;  /*�����ѵ���������*/
		/*�����ѵ���������*/
	double   orig_txn_amt;  /*ԭʼ���ױ��ֽ��*/
		/*ԭʼ���ױ��ֽ��*/
	char   orig_trans_date[14+1];  /*ԭʼ��������*/
		/*ԭʼ��������*/
	char   orig_auth_code[6+1];  /*ԭʼ������Ȩ��*/
		/*ԭʼ������Ȩ��*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	char   loan_code[4+1];  /*�����Ʒ��*/
		/*�����Ʒ��*/
	char   register_id[20+1];  /*��������˳���*/
		/*��������˳���*/
	double   resch_init_prin;  /*չ�ڱ�����*/
		/*չ�ڱ�����*/
	char   resch_date[14+1];  /*չ����Ч����*/
		/*չ����Ч����*/
	double   bef_resch_fixed_pmt_prin;  /*չ��ǰÿ��Ӧ������*/
		/*չ��ǰÿ��Ӧ������*/
	int   bef_resch_init_term;  /*չ��ǰ������*/
		/*չ��ǰ������*/
	double   bef_resch_first_term_prin;  /*չ��ǰ��������Ӧ������*/
		/*չ��ǰ��������Ӧ������*/
	double   bef_resch_final_term_prin;  /*չ��ǰ����ĩ��Ӧ������*/
		/*չ��ǰ����ĩ��Ӧ������*/
	double   bef_resch_init_fee1;  /*չ��ǰ������������*/
		/*չ��ǰ������������*/
	double   bef_resch_fixed_fee1;  /*BEF_����ÿ��������*/
		/*BEF_����ÿ��������*/
	double   bef_resch_first_term_fee1;  /*չ��ǰ��������������*/
		/*չ��ǰ��������������*/
	double   bef_resch_final_term_fee1;  /*չ��ǰ����ĩ��������*/
		/*չ��ǰ����ĩ��������*/
	double   resch_first_term_fee1;  /*չ�ں�����������*/
		/*չ�ں�����������*/
	char   loan_fee_method[1+1];  /*������������ȡ��ʽ*/
		/*������������ȡ��ʽ*/
	double   interest_rate;  /*��������*/
		/*��������*/
	double   penalty_rate;  /*��Ϣ����*/
		/*��Ϣ����*/
	double   compound_rate;  /*��������*/
		/*��������*/
	double   float_rate;  /*��������*/
		/*��������*/
	char   loan_receipt_nbr[20+1];  /*��ݺ�*/
		/*��ݺ�*/
	char   loan_expire_date[14+1];  /*���������*/
		/*���������*/
	char   loan_cd[2+1];  /*���������������*/
		/*���������������*/
	char   payment_hist[24+1];  /*24���»���״̬*/
		/*24���»���״̬*/
	double   ctd_payment_amt;  /*���ڻ����*/
		/*���ڻ����*/
	int   past_resch_cnt;  /*��չ�ڴ���*/
		/*��չ�ڴ���*/
	int   past_shorted_cnt;  /*�����ڴ���*/
		/*�����ڴ���*/
	double   adv_pmt_amt;  /*��ǰ������*/
		/*��ǰ������*/
	char   last_action_date[14+1];  /*�ϴ��ж�����*/
		/*�ϴ��ж�����*/
	char   last_action_type[1+1];  /*�ϴ��ж�����*/
		/*�ϴ��ж�����*/
	char   last_modified_datetime[14+1];  /*�޸�ʱ��*/
		/*�޸�ʱ��*/
	char   activate_date[14+1];  /*��������*/
		/*��������*/
	char   interest_calc_base[14+1];  /*��Ϣ����*/
		/*��Ϣ����*/
	char   first_bill_date[14+1];  /*�׸����ڻ�����*/
		/*�׸����ڻ�����*/
	char   age_cd[1+1];  /*����*/
		/*����*/
	char   recalc_ind[1+1];  /*���������־*/
		/*���������־*/
	char   recalc_date[14+1];  /*����������*/
		/*����������*/
	char   grace_date[14+1];  /*��������*/
		/*��������*/
	char   cancel_date[14+1];  /*��������*/
		/*��������*/
	char   cancel_reason[100+1];  /*�����ԭ��*/
		/*�����ԭ��*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	int   due_days;  /*��ǰ��������*/
		/*��ǰ��������*/
	char   contract_ver[200+1];  /*��ͬ�汾��*/
		/*��ͬ�汾��*/
	double   loan_init_interest;  /*��������Ϣ*/
		/*��������Ϣ*/
	double   bef_init_interest;  /*ԭ��������Ϣ*/
		/*ԭ��������Ϣ*/
	double   bank_proportion;  /*���г��ʱ���*/
		/*���г��ʱ���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_LOAN;

#define SD_DATA  ICPS_WB_TM_LOAN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  register_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  request_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_loan_status, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_init_term, 0),\
	APP_DEFSDMEMBER(T_LONG,  curr_term, 0),\
	APP_DEFSDMEMBER(T_LONG,  remain_term, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fixed_pmt_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_first_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_final_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fixed_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_first_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_final_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unearned_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unearned_fee1, 2),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  terminate_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  terminate_reason_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_curr_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_xfrout, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_xfrin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_principal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_penalty, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_prin_xfrout, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_prin_xfrin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fee1_xfrout, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_fee1_xfrin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  orig_trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_auth_code, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  register_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  resch_init_prin, 2),\
	APP_DEFSDMEMBER(T_STRING,  resch_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_fixed_pmt_prin, 2),\
	APP_DEFSDMEMBER(T_LONG,  bef_resch_init_term, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_first_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_final_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_init_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_fixed_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_first_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_resch_final_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  resch_first_term_fee1, 2),\
	APP_DEFSDMEMBER(T_STRING,  loan_fee_method, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  compound_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  float_rate, 2),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_expire_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  payment_hist, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  past_resch_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  past_shorted_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  adv_pmt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  last_action_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_action_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  activate_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  interest_calc_base, 0),\
	APP_DEFSDMEMBER(T_STRING,  first_bill_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  age_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  recalc_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  recalc_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  grace_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_reason, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_LONG,  due_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_ver, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_init_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_LOAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_LOAN_H__*/
