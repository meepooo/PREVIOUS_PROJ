/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_AUTH_HST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_AUTH_HST (F_WB15.��Ȩ������ʷ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_AUTH_HST_H__
#define __ICPS_WB_TM_AUTH_HST_H__
typedef struct TDB_ICPS_WB_TM_AUTH_HST
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   log_kv[20+1];  /*LOG�ļ�ֵ*/
		/*LOG�ļ�ֵ*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	char   logical_card_no[19+1];  /*�߼�����*/
		/*�߼�����*/
	long   acq_ref_no;  /*����������ױ���*/
		/*����������ױ���*/
	double   trans_amt;  /*���׽��*/
		/*���׽��*/
	char   txn_curr_cd[3+1];  /*���ױ��ִ���*/
		/*���ױ��ִ���*/
	char   user_field269[6+1];  /*�����ֶ�269*/
		/*�����ֶ�269*/
	char   acq_name_addr[40+1];  /*����������Ƶ�ַ*/
		/*����������Ƶ�ַ*/
	double   chb_txn_amt;  /*�ֿ����˻����ֽ��*/
		/*�ֿ����˻����ֽ��*/
	char   chb_curr_cd[3+1];  /*�ֿ����˻�����*/
		/*�ֿ����˻�����*/
	char   user_field270[15+1];  /*�����ֶ�270*/
		/*�����ֶ�270*/
	char   mcc[4+1];  /*�̻�������*/
		/*�̻�������*/
	char   acq_branch_id[9+1];  /*������д���*/
		/*������д���*/
	char   fwd_inst_id[11+1];  /*ת��������*/
		/*ת��������*/
	char   transmission_timestamp[10+1];  /*��������*/
		/*��������*/
	char   settle_date[4+1];  /*��������*/
		/*��������*/
	char   txn_direction[20+1];  /*���׷���*/
		/*���׷���*/
	char   txn_terminal[40+1];  /*�����ն�*/
		/*�����ն�*/
	char   trans_status[1+1];  /*����״̬*/
		/*����״̬*/
	char   trans_type[20+1];  /*��������*/
		/*��������*/
	char   log_ol_time[14+1];  /*LOG����ʱ��*/
		/*LOG����ʱ��*/
	char   log_biz_date[14+1];  /*����ҵ������*/
		/*����ҵ������*/
	char   mti[4+1];  /*�������ͱ�ʶ*/
		/*�������ͱ�ʶ*/
	char   orig_txn_type[20+1];  /*ԭ��������*/
		/*ԭ��������*/
	char   orig_fwd_inst_id[11+1];  /*ԭʼת��������*/
		/*ԭʼת��������*/
	char   orig_acq_inst_id[11+1];  /*ԭʼ���������*/
		/*ԭʼ���������*/
	char   orig_mti[4+1];  /*ԭ����MTI*/
		/*ԭ����MTI*/
	char   orig_trans_date[14+1];  /*ԭʼ��������*/
		/*ԭʼ��������*/
	int   orig_trace_no;  /*ԭʼϵͳ���ٺ�*/
		/*ԭʼϵͳ���ٺ�*/
	char   orig_txn_proc[6+1];  /*ԭ���״�����*/
		/*ԭ���״�����*/
	double   orig_txn_amt;  /*ԭʼ���ױ��ֽ��*/
		/*ԭʼ���ױ��ֽ��*/
	char   orig_log_kv[20+1];  /*ԭ����LOG��ֵ*/
		/*ԭ����LOG��ֵ*/
	char   orig_txn_val_1[38+1];  /*ԭ���׼�ֵ1*/
		/*ԭ���׼�ֵ1*/
	char   orig_txn_val_2[40+1];  /*ԭ���׼�ֵ2*/
		/*ԭ���׼�ֵ2*/
	double   orig_chb_txn_amt;  /*ԭʼ���˱��ֽ��*/
		/*ԭʼ���˱��ֽ��*/
	char   orig_biz_date[14+1];  /*ԭ���׵�����ҵ��������*/
		/*ԭ���׵�����ҵ��������*/
	char   last_reversal_date[14+1];  /*���һ�γ峷ʱ��*/
		/*���һ�γ峷ʱ��*/
	int   void_count;  /*��������*/
		/*��������*/
	char   manual_auth_flag[1+1];  /*�˹���Ȩ��־*/
		/*�˹���Ȩ��־*/
	char   opera_id[40+1];  /*����ԱID*/
		/*����ԱID*/
	char   brand[2+1];  /*Ʒ��*/
		/*Ʒ��*/
	char   product_code[6+1];  /*��Ʒ����*/
		/*��Ʒ����*/
	char   mcc_type[2+1];  /*�̻����ͷ���*/
		/*�̻����ͷ���*/
	char   user_field271[4+1];  /*�����ֶ�271*/
		/*�����ֶ�271*/
	char   user_field272[1+1];  /*�����ֶ�272*/
		/*�����ֶ�272*/
	double   comp_amt;  /*������Ȩ���*/
		/*������Ȩ���*/
	char   final_upd_direction[1+1];  /*���ո��·���*/
		/*���ո��·���*/
	double   final_upd_amt;  /*���ո��½��*/
		/*���ո��½��*/
	char   ic_ind[1+1];  /*�Ƿ�IC��*/
		/*�Ƿ�IC��*/
	char   the_3dsecure_type[1+1];  /*�Ƿ�3D���Ӱ�ȫ����*/
		/*�Ƿ�3D���Ӱ�ȫ����*/
	char   vip_status[1+1];  /*VIP״̬*/
		/*VIP״̬*/
	double   curr_balance;  /*��ǰ���*/
		/*��ǰ���*/
	double   cash_amt;  /*ȡ�ֽ��*/
		/*ȡ�ֽ��*/
	double   otb;  /*���ö��*/
		/*���ö��*/
	double   cash_otb;  /*ȡ�ֿ��ö��*/
		/*ȡ�ֿ��ö��*/
	double   cust_otb;  /*�ͻ����ö��*/
		/*�ͻ����ö��*/
	char   user_field273[20+1];  /*�����ֶ�273*/
		/*�����ֶ�273*/
	char   user_field274[20+1];  /*�����ֶ�274*/
		/*�����ֶ�274*/
	char   expire_date[4+1];  /*��Ч����*/
		/*��Ч����*/
	char   track_one_result[20+1];  /*һ�ŵ������Խ��*/
		/*һ�ŵ������Խ��*/
	char   track_two_result[20+1];  /*���ŵ������Խ��*/
		/*���ŵ������Խ��*/
	char   track_three_result[20+1];  /*���ŵ������Խ��*/
		/*���ŵ������Խ��*/
	char   pwd_type[1+1];  /*��������*/
		/*��������*/
	char   check_pwd_result[20+1];  /*��֤������*/
		/*��֤������*/
	int   pay_pwd_err_num;  /*֧������������*/
		/*֧������������*/
	char   check_cvv_result[20+1];  /*CVV��֤���*/
		/*CVV��֤���*/
	char   check_cvv2_result[20+1];  /*CVV2��֤���*/
		/*CVV2��֤���*/
	char   check_icvn_result[20+1];  /*ICVN��֤���*/
		/*ICVN��֤���*/
	char   check_arqc_result[20+1];  /*ARQC��֤���*/
		/*ARQC��֤���*/
	char   check_atc_result[20+1];  /*ATC��֤���*/
		/*ATC��֤���*/
	char   check_cvr_result[20+1];  /*CVR��֤���*/
		/*CVR��֤���*/
	char   check_tvr_result[20+1];  /*TVR��֤���*/
		/*TVR��֤���*/
	char   user_field275[40+1];  /*�����ֶ�275*/
		/*�����ֶ�275*/
	double   unmatch_cr;  /*δƥ����ǽ��*/
		/*δƥ����ǽ��*/
	double   unmatch_db;  /*δƥ���ǽ��*/
		/*δƥ���ǽ��*/
	char   b002[20+1];  /*���ʿ���-B002*/
		/*���ʿ���-B002*/
	char   b003[6+1];  /*���״�����-B003*/
		/*���״�����-B003*/
	char   b007[10+1];  /*���״���ʱ��-B007*/
		/*���״���ʱ��-B007*/
	char   b011[6+1];  /*ϵͳ���ٺ�-B011*/
		/*ϵͳ���ٺ�-B011*/
	char   b022[3+1];  /*�����PIN��ȡ��-B022*/
		/*�����PIN��ȡ��-B022*/
	char   b025[4+1];  /*�����������-B025*/
		/*�����������-B025*/
	char   b032[15+1];  /*���������ʶ��-B032*/
		/*���������ʶ��-B032*/
	char   b033[40+1];  /*����������Ƶ�ַ-B033*/
		/*����������Ƶ�ַ-B033*/
	char   b039[2+1];  /*������-B039*/
		/*������-B039*/
	char   b042[15+1];  /*�ܿ���(�̻�)��ʶ��-B042*/
		/*�ܿ���(�̻�)��ʶ��-B042*/
	char   user_field277[103+1];  /*�����ֶ�276*/
		/*�����ֶ�276*/
	char   user_field278[400+1];  /*�����ֶ�277*/
		/*�����ֶ�277*/
	char   b090[42+1];  /*ԭʼ����Ԫ*/
		/*ԭʼ����Ԫ*/
	char   opera_term_id[20+1];  /*�����û��ն˱��*/
		/*�����û��ն˱��*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	double   b004;  /*���׻��ҽ��-B004*/
		/*���׻��ҽ��-B004*/
	double   b006;  /*�˻����ҽ��-B006*/
		/*�˻����ҽ��-B006*/
	char   b049[3+1];  /*���׻��Ҵ���-B049*/
		/*���׻��Ҵ���-B049*/
	char   b051[3+1];  /*�˻����Ҵ���-B051*/
		/*�˻����Ҵ���-B051*/
	char   b037[23+1];  /*�����ο���-B037*/
		/*�����ο���-B037*/
	double   b028;  /*������-B028*/
		/*������-B028*/
	char   b048[999+1];  /*��������-B048*/
		/*��������-B048*/
	char   b054[60+1];  /*�����������-B054*/
		/*�����������-B054*/
	char   user_field279[27+1];  /*�����ֶ�278*/
		/*�����ֶ�278*/
	char   user_field280[27+1];  /*�����ֶ�279*/
		/*�����ֶ�279*/
	char   user_field281[27+1];  /*�����ֶ�280*/
		/*�����ֶ�280*/
	char   busi_serial[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   sys_trans_id[32+1];  /*ϵͳ������ˮ��*/
		/*ϵͳ������ˮ��*/
	char   user_field282[15+1];  /*�����ֶ�281*/
		/*�����ֶ�281*/
	char   sub_terminal_type[15+1];  /*�ն�����*/
		/*�ն�����*/
	char   sub_merch_id[40+1];  /*�����̻�����*/
		/*�����̻�����*/
	char   sub_merch_name[60+1];  /*�����̻�����*/
		/*�����̻�����*/
	char   wares_desc[60+1];  /*��Ʒ��Ϣ*/
		/*��Ʒ��Ϣ*/
	char   last_modified_datetime[14+1];  /*�޸�ʱ��*/
		/*�޸�ʱ��*/
	int   part_month;  /*�����õ��·�*/
		/*�����õ��·�*/
	char   paid_stmt_date[14+1];  /*�����˵���*/
		/*�����˵���*/
	double   repay_amt;  /*Ӧ�����*/
		/*Ӧ�����*/
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

}ICPS_WB_TM_AUTH_HST;

#define SD_DATA  ICPS_WB_TM_AUTH_HST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  log_kv, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  acq_ref_no, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  txn_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field269, 0),\
	APP_DEFSDMEMBER(T_STRING,  acq_name_addr, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  chb_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  chb_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field270, 0),\
	APP_DEFSDMEMBER(T_STRING,  mcc, 0),\
	APP_DEFSDMEMBER(T_STRING,  acq_branch_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  fwd_inst_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  transmission_timestamp, 0),\
	APP_DEFSDMEMBER(T_STRING,  settle_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_direction, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_terminal, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  log_ol_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  log_biz_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  mti, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_fwd_inst_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_acq_inst_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_mti, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_trans_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  orig_trace_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_proc, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  orig_log_kv, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_val_1, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_txn_val_2, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_chb_txn_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  orig_biz_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_reversal_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  void_count, 0),\
	APP_DEFSDMEMBER(T_STRING,  manual_auth_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  opera_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  brand, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  mcc_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field271, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field272, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  comp_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  final_upd_direction, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  final_upd_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  ic_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  the_3dsecure_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  vip_status, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cash_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  otb, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cash_otb, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cust_otb, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field273, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field274, 0),\
	APP_DEFSDMEMBER(T_STRING,  expire_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  track_one_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  track_two_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  track_three_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  pwd_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_pwd_result, 0),\
	APP_DEFSDMEMBER(T_LONG,  pay_pwd_err_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_cvv_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_cvv2_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_icvn_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_arqc_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_atc_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_cvr_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  check_tvr_result, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field275, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  unmatch_cr, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unmatch_db, 2),\
	APP_DEFSDMEMBER(T_STRING,  b002, 0),\
	APP_DEFSDMEMBER(T_STRING,  b003, 0),\
	APP_DEFSDMEMBER(T_STRING,  b007, 0),\
	APP_DEFSDMEMBER(T_STRING,  b011, 0),\
	APP_DEFSDMEMBER(T_STRING,  b022, 0),\
	APP_DEFSDMEMBER(T_STRING,  b025, 0),\
	APP_DEFSDMEMBER(T_STRING,  b032, 0),\
	APP_DEFSDMEMBER(T_STRING,  b033, 0),\
	APP_DEFSDMEMBER(T_STRING,  b039, 0),\
	APP_DEFSDMEMBER(T_STRING,  b042, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field277, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field278, 0),\
	APP_DEFSDMEMBER(T_STRING,  b090, 0),\
	APP_DEFSDMEMBER(T_STRING,  opera_term_id, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  b004, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  b006, 4),\
	APP_DEFSDMEMBER(T_STRING,  b049, 0),\
	APP_DEFSDMEMBER(T_STRING,  b051, 0),\
	APP_DEFSDMEMBER(T_STRING,  b037, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  b028, 4),\
	APP_DEFSDMEMBER(T_STRING,  b048, 0),\
	APP_DEFSDMEMBER(T_STRING,  b054, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field279, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field280, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field281, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field282, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_terminal_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  wares_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_LONG,  part_month, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_stmt_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_AUTH_HST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_AUTH_HST_H__*/
