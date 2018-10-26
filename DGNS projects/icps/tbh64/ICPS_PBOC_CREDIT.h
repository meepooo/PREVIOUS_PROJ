/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_PBOC_CREDIT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_PBOC_CREDIT (3.����������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_PBOC_CREDIT_H__
#define __ICPS_PBOC_CREDIT_H__
typedef struct TDB_ICPS_PBOC_CREDIT
{
	char   apply_no[64+1];  /*���뵥��*/
		/*���뵥��*/
	char   plt_date[8+1];  /*ƽ̨����*/
		/*ƽ̨����*/
	char   plt_serial[16+1];  /*ƽ̨��ˮ��*/
		/*ƽ̨��ˮ��*/
	char   id_type[2+1];  /*֤������*/
		/*֤������*/
	char   id_num[32+1];  /*֤������*/
		/*֤������*/
	char   query_no[64+1];  /*��ѯ���*/
		/*��ѯ���*/
	char   query_flag[1+1];  /*��ѯ���*/
		/*��ѯ��� 1���в�ѯ�Ҳ鵽���棻0���в�ѯ�����޴���*/
	int   manage_last_12_qry_cnt;  /*����������12���²�ѯ����*/
		/*��ѯ-����������12���²�ѯ����*/
	int   manage_last_3_qry_cnt;  /*����������3���²�ѯ����*/
		/*��ѯ-����������3���²�ѯ����*/
	int   manage_last_6_qry_cnt;  /*����������6���²�ѯ����*/
		/*��ѯ-����������6���²�ѯ����*/
	int   approve_last_12_qry_cnt;  /*�����������12���²�ѯ����*/
		/*��ѯ-�������������12���²�ѯ����*/
	int   approve_last_3_qry_cnt;  /*�����������3���²�ѯ����*/
		/*��ѯ-�������������3���²�ѯ����*/
	int   approve_last_6_qry_cnt;  /*�����������6���²�ѯ����*/
		/*��ѯ-�������������6���²�ѯ����*/
	int   approve_last_30d_qry_org_cnt;  /*�����������1���²�ѯ������*/
		/*��ѯ-�������������1���²�ѯ������*/
	int   approve_last_12_qry_org_cnt;  /*�����������12���²�ѯ������*/
		/*��ѯ-�������������12���²�ѯ������*/
	int   approve_last_3_qry_org_cnt;  /*�����������3���²�ѯ������*/
		/*��ѯ-�������������3���²�ѯ������*/
	int   approve_last_6_qry_org_cnt;  /*�����������6���²�ѯ������*/
		/*��ѯ-�������������6���²�ѯ������*/
	int   card_last_12_qry_cnt;  /*���ÿ��������12���²�ѯ����*/
		/*��ѯ-���ÿ����������12���²�ѯ����*/
	int   card_last_3_qry_cnt;  /*���ÿ��������3���²�ѯ����*/
		/*��ѯ-���ÿ����������3���²�ѯ����*/
	int   card_last_6_qry_cnt;  /*���ÿ��������6���²�ѯ����*/
		/*��ѯ-���ÿ����������6���²�ѯ����*/
	int   card_last_30d_qry_org_cnt;  /*���ÿ��������1���²�ѯ����*/
		/*��ѯ-���ÿ����������1���²�ѯ����*/
	int   card_last_3_qry_org_cnt;  /*���ÿ��������3���²�ѯ������*/
		/*��ѯ-���ÿ����������3���²�ѯ������*/
	int   card_last_6_qry_org_cnt;  /*���ÿ��������6���²�ѯ������*/
		/*��ѯ-���ÿ����������6���²�ѯ������*/
	int   all_loan_num;  /*�ܴ������*/
		/*�ܴ����������������״̬��*/
	int   car_loan_num;  /*��������*/
		/*��������*/
	int   biz_loan_num;  /*��Ӫ�������*/
		/*��Ӫ�������*/
	int   house_loan_num;  /*��������*/
		/*��������*/
	int   os_all_loan_num;  /*δ����������ʻ������ܱ���*/
		/*δ����������ʻ������ܱ���*/
	int   os_car_loan_num;  /*δ���峵������*/
		/*δ���峵������*/
	int   os_house_loan_num;  /*δ���巿������*/
		/*δ���巿������*/
	int   os_biz_loan_num;  /*δ���徭Ӫ�������*/
		/*δ���徭Ӫ�������*/
	int   ln_nca_con13_cnt_sum;  /*δ����������Ѵ������*/
		/*δ�������Ѵ����ͳ�Ƹ������Ѵ������*/
	int   ln_nca_crd_cnt_sum;  /*δ�������ô������*/
		/*δ�������ô������*/
	double   loan_max_amount;  /*������߶��*/
		/*������߶��*/
	double   loan_oper_max_amount;  /*��Ӫ�Դ�����߶��*/
		/*��Ӫ�Դ�����߶��*/
	double   balance_sum;  /*δ������������ܺ�*/
		/*δ������������ܺ�*/
	double   loan_sum_amount;  /*δ����������ܺ�*/
		/*δ����������ܺ�*/
	double   ln_nca_amt_avg;  /*δ�������ƽ����ͬ���*/
		/*δ�������ƽ����ͬ���*/
	double   loan_house_amt_sum;  /*δ���巿����ͬ���*/
		/*δ���巿����ͬ���*/
	double   loan_house_bal_sum;  /*δ���巿�����*/
		/*δ���巿�����*/
	double   business_loan_sum_amount;  /*δ���徭Ӫ�����ͬ���*/
		/*δ���徭Ӫ�����ͬ���*/
	double   business_loan_sum_balance;  /*δ���徭Ӫ�������*/
		/*δ���徭Ӫ�������*/
	double   ln_nca_con13_bal_sum;  /*δ����������Ѵ������*/
		/*δ�������Ѵ����ͳ�Ƹ������Ѵ�����*/
	int   ln_nca_rmm_avg;  /*δ�������ƽ��ʣ�໹������*/
		/*δ�������ƽ��ʣ�໹������*/
	int   ln_nca_pmm_avg;  /*δ�������ƽ����������*/
		/*δ�������ƽ����������*/
	double   ln_nca_pmo_avg;  /*����δ�������ƽ��Ӧ����*/
		/*����δ�������ƽ��Ӧ����*/
	double   ln_nca_pmt_sum;  /*δ����������ʵ����*/
		/*δ����������ʵ����*/
	double   repay_car_mon;  /*�¶ȳ�������Ӧ����*/
		/*�¶ȳ�������Ӧ����*/
	double   repay_house_mon;  /*�¶ȷ�������Ӧ����*/
		/*�¶ȷ�������Ӧ����*/
	int   ln_nca_m1_max_3m;  /*δ��������3����������ڴ���*/
		/*δ��������3����������ڴ���*/
	double   loan_ovd_max_bal_cpt;  /*�����������ڽ��*/
		/*�����������ڽ��*/
	double   loan_cur_ovd_amount;  /*���ǰ�����ܽ��*/
		/*���ǰ�����ܽ��*/
	int   ln_cd_max_24m;  /*�����24���������������*/
		/*�����24���������������*/
	int   ln_cd_max;  /*��ǰ���������������*/
		/*��ǰ���������������*/
	int   loan_delq_12mth_max;  /*δ��������12���������������*/
		/*δ��������12���������������*/
	int   loan_delq_3mth_max;  /*δ��������3���������������*/
		/*δ��������3���������������*/
	int   loan_delq_6mth_max;  /*δ��������6���������������*/
		/*δ��������6���������������*/
	char   class_5_credit_mortgage[1+1];  /*���������������������弶����*/
		/*���������������������弶���� 1-���� 2-��ע 3-�μ� 4-���� 5-��ʧ 6-δ֪*/
	char   class_5_not_mortgage[1+1];  /*�ǰ��������������������弶����*/
		/*�ǰ��������������������弶���� 1-���� 2-��ע 3-�μ� 4-���� 5-��ʧ 6-δ֪*/
	int   dull_loan_num;  /*�������ô������*/
		/*�������ô������*/
	double   dull_loan_sum;  /*���˵Ĵ�����*/
		/*���˵Ĵ�����*/
	int   all_assure_loan_num;  /*�ܵ�������*/
		/*�ܵ�������*/
	double   all_assure_loan_sum;  /*�ܵ������*/
		/*�ܵ������*/
	int   cont_under_attention_assure;  /*���ⵣ���弶�����ע�����ϱ���*/
		/*���ⵣ���弶�����ע�����ϱ���*/
	double   cont_under_secondary_assure;  /*״̬Ϊ�μ������ϵĵ���������*/
		/*������״̬Ϊ���μ��������ϵĵ���������*/
	double   assure_under_attention_amt;  /*״̬Ϊ��ע�����ϵĵ���������*/
		/*������״̬Ϊ����ע�������ϵĵ���������*/
	double   as_cv2_bal_sum;  /*���ⵣ���弶�����ע���������*/
		/*���ⵣ���弶�����ע���������*/
	double   card_amt_sum;  /*���ⵣ���弶�����ע������������δ�������ÿ�������Ŷ��*/
		/*���ⵣ���弶�����ע������������δ�������ÿ�������Ŷ��*/
	double   cc_act_lmt_max;  /*������δ�������ÿ�������Ŷ��*/
		/*������δ�������ÿ�������Ŷ��*/
	double   ac_nml_lmt_avg;  /*����״̬��ƽ�����*/
		/*����״̬��ƽ�����*/
	double   ac_nml_lmt_sum;  /*����״̬���ܶ��*/
		/*����״̬���ܶ��*/
	int   card_issue_org_cnt;  /*����״̬����������*/
		/*����״̬����������*/
	int   card_rmb_cnt;  /*��ǰ������δ��������Ҵ��ǿ���*/
		/*��ǰ������δ��������Ҵ��ǿ���*/
	int   cc_cnt_sum;  /*����δ�������ǿ���*/
		/*����δ�������ǿ���*/
	int   cc_nca_cnt_sum;  /*δ�������ǿ���*/
		/*δ�������ǿ���*/
	int   normal_num;  /*����״̬���ǿ���*/
		/*����״̬���ǿ���*/
	int   all_card_cnt;  /*�ܿ���*/
		/*�ܿ��������ǿ�+׼���ǿ�����������״̬��*/
	double   cc_act_cu_o90_pct;  /*������δ�������ǿ���ǰʹ���ʴ��ڵ���90%ռ����δ�������ǿ�����*/
		/*������δ�������ǿ���ǰʹ���ʴ��ڵ���90%ռ����δ�������ǿ�����*/
	double   cc_nca_cu_min;  /*δ�������ǿ���ǰ��Сʹ����*/
		/*δ�������ǿ���ǰ��Сʹ����*/
	double   cc_nca_mu_max;  /*δ�������ǿ����6����ƽ��ʹ����*/
		/*δ�������ǿ����6����ƽ��ʹ����*/
	double   card_nca_hb_max;  /*δ�������ǿ����ʹ�ö��*/
		/*δ�������ǿ����ʹ�ö��*/
	double   ac_nca_cu_avg;  /*δ��������ǰƽ��ʹ����*/
		/*δ��������ǰƽ��ʹ����*/
	double   ac_nca_hb_max;  /*δ���������ʹ�ö��*/
		/*δ���������ʹ�ö��*/
	double   cc_nml_mu_avg;  /*����״̬���ǿ�6����ƽ��ʹ����*/
		/*����״̬���ǿ�6����ƽ��ʹ����*/
	double   all_card_cur_ovd_used;  /*����״̬����ǰƽ��ʹ����*/
		/*����״̬����ǰƽ��ʹ����*/
	double   card_nca_pmo_sum;  /*����δ�������ǿ���Ӧ�����ܶ�*/
		/*����δ�������ǿ���Ӧ�����ܶ�*/
	int   card_delq_6mth_max_cnt;  /*δ�������ǿ���6����������ڴ���*/
		/*δ�������ǿ���6����������ڴ���*/
	int   card_delq_12mth_max_cnt;  /*δ�������ǿ���12����������ڴ���*/
		/*δ�������ǿ���12����������ڴ���*/
	int   card_delq_3mth_max_cnt;  /*δ�������ǿ���3����������ڴ���*/
		/*δ�������ǿ���3����������ڴ���*/
	double   card_max_ovd_bal;  /*���ǿ�����������ڽ��*/
		/*���ǿ�����������ڽ��*/
	double   all_card_cur_ovd_amt_sum;  /*δ��������ǰ�����ڽ��*/
		/*δ��������ǰ�����ڽ��*/
	int   cont_dull_card_cnt;  /*���˵Ĵ��ǿ���*/
		/*���˵Ĵ��ǿ���*/
	int   dull_scard_cnt;  /*���˵�׼���ǿ���*/
		/*���˵�׼���ǿ���*/
	int   ac_abn_cnt_sum;  /*���ǿ�Ϊ���ʶ���ֹ������*/
		/*���ǿ�Ϊ���ʡ����ᡢֹ������*/
	int   cc_act_m1_cnt_3m;  /*����δ�������ǿ���3����1�ڼ��������ڿ���*/
		/*����δ�������ǿ�����3����1�ڼ��������ڿ���*/
	double   cc_act_m1_cnt_pct_3m;  /*����δ�������ǿ���3����1�ڼ��������ڿ���ռ��*/
		/*����δ�������ǿ�����3����1�ڼ��������ڿ���ռ��*/
	double   cc_act_m1_cnt_pct_6m;  /*����δ�������ǿ���6����1�ڼ��������ڿ���ռ��*/
		/*����δ�������ǿ�����6����1�ڼ��������ڿ���ռ��*/
	int   ac_nca_cd_max;  /*δ��������ǰ�����������*/
		/*δ��������ǰ�����������*/
	int   cc_cd_max_24m;  /*���ǿ���24���������������*/
		/*���ǿ���24���������������*/
	int   card_delq_12mth_max;  /*���ǿ�δ�����˻��й�ȥ12���������������*/
		/*���ǿ�δ�����˻��У���ȥ12���������������*/
	int   card_delq_3mth_max;  /*���ǿ�δ�����˻��й�ȥ3���������������*/
		/*���ǿ�δ�����˻��У���ȥ3���������������*/
	int   card_delq_6mth_max;  /*���ǿ�δ�����˻��й�ȥ6���������������*/
		/*���ǿ�δ�����˻��У���ȥ6���������������*/
	int   qc_act_cd_max_24m;  /*׼������24���������������*/
		/*׼��������24���������������*/
	int   scard_delq_12mth_max;  /*׼����δ�����˻��й�ȥ12���������������*/
		/*׼������δ�����˻��У���ȥ12���������������*/
	int   scard_delq_3mth_max;  /*׼����δ�����˻��й�ȥ3���������������*/
		/*׼������δ�����˻��У���ȥ3���������������*/
	int   scard_delq_6mth_max;  /*׼����δ�����˻��й�ȥ6���������������*/
		/*׼������δ�����˻��У���ȥ6���������������*/
	int   credit_opm_max;  /*������ʷ*/
		/*������ʷ(���翪������ѯ�����������������ѯ����ȡ���)*/
	int   ac_opm_max;  /*��󿪿�����*/
		/*��󿪿�����*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_PBOC_CREDIT;

#define SD_DATA  ICPS_PBOC_CREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  query_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  query_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  manage_last_12_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  manage_last_3_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  manage_last_6_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_12_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_3_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_6_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_30d_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_12_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_3_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  approve_last_6_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_12_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_3_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_6_qry_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_30d_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_3_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_last_6_qry_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  all_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  car_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  biz_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  house_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_all_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_car_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_house_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  os_biz_loan_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_con13_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_crd_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_max_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_oper_max_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  balance_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_sum_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_amt_avg, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_house_amt_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_house_bal_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  business_loan_sum_amount, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  business_loan_sum_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_con13_bal_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_rmm_avg, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_pmm_avg, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_pmo_avg, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ln_nca_pmt_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_car_mon, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_house_mon, 2),\
	APP_DEFSDMEMBER(T_LONG,  ln_nca_m1_max_3m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_ovd_max_bal_cpt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_cur_ovd_amount, 2),\
	APP_DEFSDMEMBER(T_LONG,  ln_cd_max_24m, 0),\
	APP_DEFSDMEMBER(T_LONG,  ln_cd_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_delq_12mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_delq_3mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  loan_delq_6mth_max, 0),\
	APP_DEFSDMEMBER(T_STRING,  class_5_credit_mortgage, 0),\
	APP_DEFSDMEMBER(T_STRING,  class_5_not_mortgage, 0),\
	APP_DEFSDMEMBER(T_LONG,  dull_loan_num, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  dull_loan_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  all_assure_loan_num, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  all_assure_loan_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  cont_under_attention_assure, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cont_under_secondary_assure, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  assure_under_attention_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  as_cv2_bal_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_amt_sum, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_lmt_max, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nml_lmt_avg, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nml_lmt_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  card_issue_org_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_rmb_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_nca_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  normal_num, 0),\
	APP_DEFSDMEMBER(T_LONG,  all_card_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_cu_o90_pct, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_nca_cu_min, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_nca_mu_max, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_nca_hb_max, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nca_cu_avg, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  ac_nca_hb_max, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_nml_mu_avg, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  all_card_cur_ovd_used, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_nca_pmo_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_6mth_max_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_12mth_max_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_3mth_max_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  card_max_ovd_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  all_card_cur_ovd_amt_sum, 2),\
	APP_DEFSDMEMBER(T_LONG,  cont_dull_card_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  dull_scard_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  ac_abn_cnt_sum, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_act_m1_cnt_3m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_m1_cnt_pct_3m, 5),\
	APP_DEFSDMEMBER(T_DOUBLE,  cc_act_m1_cnt_pct_6m, 5),\
	APP_DEFSDMEMBER(T_LONG,  ac_nca_cd_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  cc_cd_max_24m, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_12mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_3mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  card_delq_6mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  qc_act_cd_max_24m, 0),\
	APP_DEFSDMEMBER(T_LONG,  scard_delq_12mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  scard_delq_3mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  scard_delq_6mth_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  credit_opm_max, 0),\
	APP_DEFSDMEMBER(T_LONG,  ac_opm_max, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_PBOC_CREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_PBOC_CREDIT_H__*/
