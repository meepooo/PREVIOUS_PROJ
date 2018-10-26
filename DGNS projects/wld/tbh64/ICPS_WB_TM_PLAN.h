/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_PLAN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_PLAN (F_WB5.���üƻ���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_PLAN_H__
#define __ICPS_WB_TM_PLAN_H__
typedef struct TDB_ICPS_WB_TM_PLAN
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   plan_id[20+1];  /*��ˮ��*/
		/*��ˮ��*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	char   logical_card_no[19+1];  /*�߼�����*/
		/*�߼�����*/
	char   plan_nbr[6+1];  /*���üƻ���*/
		/*���üƻ���*/
	char   plan_type[1+1];  /*���üƻ�����*/
		/*���üƻ�����*/
	char   product_code[6+1];  /*��Ʒ����*/
		/*��Ʒ����*/
	char   ref_nbr[23+1];  /*���ײο���*/
		/*���ײο���*/
	double   curr_balance;  /*��ǰ���*/
		/*��ǰ���*/
	double   begin_bal;  /*�ڳ����*/
		/*�ڳ����*/
	double   dispute_amt;  /*������*/
		/*������*/
	double   tot_due_amt;  /*��С�����*/
		/*��С�����*/
	char   plan_add_date[14+1];  /*��¼��������*/
		/*��¼��������*/
	char   paid_out_date[14+1];  /*��������*/
		/*��������*/
	double   past_principal;  /*���ڱ���*/
		/*���ڱ���*/
	double   past_interest;  /*������Ϣ*/
		/*������Ϣ*/
	double   past_card_fee;  /*�������*/
		/*�������*/
	double   past_ovrlmt_fee;  /*���ڳ��޷�*/
		/*���ڳ��޷�*/
	double   past_lpc;  /*�������ɽ�*/
		/*�������ɽ�*/
	double   past_nsf_fee;  /*�����ʽ����*/
		/*�����ʽ����*/
	double   past_txn_fee;  /*���ڽ��׷�*/
		/*���ڽ��׷�*/
	double   past_svc_fee;  /*���ڷ����*/
		/*���ڷ����*/
	double   past_ins;  /*���ڱ��ս��*/
		/*���ڱ��ս��*/
	double   past_user_fee1;  /*�����Զ������1*/
		/*�����Զ������1*/
	double   past_user_fee2;  /*�����Զ������2*/
		/*�����Զ������2*/
	double   past_user_fee3;  /*�����Զ������3*/
		/*�����Զ������3*/
	double   past_user_fee4;  /*�����Զ������4*/
		/*�����Զ������4*/
	double   past_user_fee5;  /*�����Զ������5*/
		/*�����Զ������5*/
	double   past_user_fee6;  /*�����Զ������6*/
		/*�����Զ������6*/
	double   CTD_PRINCIPAL;  /*��ǰ����*/
		/*��ǰ����*/
	double   ctd_interest;  /*������Ϣ*/
		/*������Ϣ*/
	double   ctd_card_fee;  /*�������*/
		/*�������*/
	double   ctd_ovrlmt_fee;  /*���ڳ��޷�*/
		/*���ڳ��޷�*/
	double   ctd_lpc;  /*�������ɽ�*/
		/*�������ɽ�*/
	double   ctd_nsf_fee;  /*�����ʽ����*/
		/*�����ʽ����*/
	double   ctd_svc_fee;  /*���ڷ����*/
		/*���ڷ����*/
	double   ctd_txn_fee;  /*���ڽ��׷�*/
		/*���ڽ��׷�*/
	double   ctd_ins;  /*���ڱ��ս��*/
		/*���ڱ��ս��*/
	double   ctd_user_fee1;  /*���������Զ������1*/
		/*���������Զ������1*/
	double   ctd_user_fee2;  /*���������Զ������2*/
		/*���������Զ������2*/
	double   ctd_user_fee3;  /*���������Զ������3*/
		/*���������Զ������3*/
	double   ctd_user_fee4;  /*���������Զ������4*/
		/*���������Զ������4*/
	double   ctd_user_fee5;  /*���������Զ������5*/
		/*���������Զ������5*/
	double   ctd_user_fee6;  /*���������Զ������6*/
		/*���������Զ������6*/
	double   ctd_amt_db;  /*���ڽ�ǽ��*/
		/*���ڽ�ǽ��*/
	double   ctd_amt_cr;  /*���ڴ��ǽ��*/
		/*���ڴ��ǽ��*/
	int   ctd_nbr_db;  /*���ڽ�ǽ��ױ���*/
		/*���ڽ�ǽ��ױ���*/
	int   ctd_nbr_cr;  /*���ڴ��ǽ��ױ���*/
		/*���ڴ��ǽ��ױ���*/
	double   nodefbnp_int_acru;  /*���ӳ���Ϣ*/
		/*���ӳ���Ϣ*/
	double   beg_defbnp_int_acru;  /*�����ۻ���ʱ��Ϣ*/
		/*�����ۻ���ʱ��Ϣ*/
	double   ctd_defbnp_int_acru;  /*�����ۻ���ʱ��Ϣ*/
		/*�����ۻ���ʱ��Ϣ*/
	char   user_field146[4+1];  /*�����ֶ�146*/
		/*�����ֶ�146*/
	char   user_field147[4+1];  /*�����ֶ�147*/
		/*�����ֶ�147*/
	char   user_field148[4+1];  /*�����ֶ�148*/
		/*�����ֶ�148*/
	char   user_field149[4+1];  /*�����ֶ�149*/
		/*�����ֶ�149*/
	char   user_field150[4+1];  /*�����ֶ�150*/
		/*�����ֶ�150*/
	char   user_field151[4+1];  /*�����ֶ�151*/
		/*�����ֶ�151*/
	int   user_field152;  /*�����ֶ�152*/
		/*�����ֶ�152*/
	int   user_field153;  /*�����ֶ�153*/
		/*�����ֶ�153*/
	int   user_field154;  /*�����ֶ�154*/
		/*�����ֶ�154*/
	int   user_field155;  /*�����ֶ�155*/
		/*�����ֶ�155*/
	int   user_field156;  /*�����ֶ�156*/
		/*�����ֶ�156*/
	int   user_field157;  /*�����ֶ�157*/
		/*�����ֶ�157*/
	char   user_field158[40+1];  /*�����ֶ�158*/
		/*�����ֶ�158*/
	char   user_field159[40+1];  /*�����ֶ�159*/
		/*�����ֶ�159*/
	char   user_field160[40+1];  /*�����ֶ�160*/
		/*�����ֶ�160*/
	char   user_field161[40+1];  /*�����ֶ�161*/
		/*�����ֶ�161*/
	char   user_field162[40+1];  /*�����ֶ�162*/
		/*�����ֶ�162*/
	char   user_field163[40+1];  /*�����ֶ�163*/
		/*�����ֶ�163*/
	char   user_field164[14+1];  /*�����ֶ�164*/
		/*�����ֶ�164*/
	char   user_field165[14+1];  /*�����ֶ�165*/
		/*�����ֶ�165*/
	char   user_field166[14+1];  /*�����ֶ�166*/
		/*�����ֶ�166*/
	char   user_field167[14+1];  /*�����ֶ�167*/
		/*�����ֶ�167*/
	char   user_field168[14+1];  /*�����ֶ�168*/
		/*�����ֶ�168*/
	char   user_field169[14+1];  /*�����ֶ�169*/
		/*�����ֶ�169*/
	double   user_field170;  /*�����ֶ�170*/
		/*�����ֶ�170*/
	double   user_field171;  /*�����ֶ�171*/
		/*�����ֶ�171*/
	double   user_field172;  /*�����ֶ�172*/
		/*�����ֶ�172*/
	double   user_field173;  /*�����ֶ�173*/
		/*�����ֶ�173*/
	double   user_field174;  /*�����ֶ�174*/
		/*�����ֶ�174*/
	double   user_field175;  /*�����ֶ�175*/
		/*�����ֶ�175*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	double   past_penalty;  /*���ڷ�Ϣ*/
		/*���ڷ�Ϣ*/
	double   ctd_penalty;  /*���ڷ�Ϣ*/
		/*���ڷ�Ϣ*/
	double   past_compound;  /*���ڸ���*/
		/*���ڸ���*/
	double   ctd_compound;  /*���ڸ���*/
		/*���ڸ���*/
	double   penalty_acru;  /*��Ϣ�ۼ�*/
		/*��Ϣ�ۼ�*/
	double   compound_acru;  /*�����ۼ�*/
		/*�����ۼ�*/
	double   interest_rate;  /*��������*/
		/*��������*/
	double   penalty_rate;  /*��Ϣ����*/
		/*��Ϣ����*/
	double   compound_rate;  /*��������*/
		/*��������*/
	char   use_plan_rate[1+1];  /*�Ƿ�ʹ��plan������*/
		/*�Ƿ�ʹ��plan������*/
	char   last_pmt_date[14+1];  /*��һ��������*/
		/*��һ��������*/
	int   term;  /*���ڴ�������*/
		/*���ڴ�������*/
	char   calc_type[1+1];  /*�Ʒ�����*/
		/*�Ʒ�����*/
	int   calc_cycle;  /*�Ʒ�����*/
		/*�Ʒ�����*/
	double   fee_rate;  /*����*/
		/*����*/
	char   last_fee_date[14+1];  /*��һ�շ���*/
		/*��һ�շ���*/
	char   next_fee_date[14+1];  /*��һ�շ���*/
		/*��һ�շ���*/
	char   trans_serial[20+1];  /*������ˮ��*/
		/*������ˮ��*/
	char   first_dd_date[14+1];  /*�״�Լ����������*/
		/*������ˮ��*/
	char   busi_serial[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   sys_trans_id[32+1];  /*ϵͳ������ˮ��*/
		/*ϵͳ������ˮ��*/
	char   user_field176[15+1];  /*�����ֶ�176*/
		/*�����ֶ�176*/
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
	double   original_amt;  /*ԭʼ���ױ���*/
		/*ԭʼ���ױ���*/
	char   interest_calc_base[1+1];  /*��Ϣ����*/
		/*��Ϣ����*/
	char   created_datetime[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_PLAN;

#define SD_DATA  ICPS_WB_TM_PLAN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  begin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  dispute_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  tot_due_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  plan_add_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_principal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_card_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_ovrlmt_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_lpc, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_nsf_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_txn_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_svc_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_ins, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee3, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee4, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee5, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_user_fee6, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  CTD_PRINCIPAL, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_card_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_ovrlmt_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_lpc, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_nsf_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_svc_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_txn_fee, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_ins, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee3, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee4, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee5, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_user_fee6, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_amt_db, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_amt_cr, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_nbr_db, 0),\
	APP_DEFSDMEMBER(T_LONG,  ctd_nbr_cr, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  nodefbnp_int_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  beg_defbnp_int_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_defbnp_int_acru, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field146, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field147, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field148, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field149, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field150, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field151, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field152, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field153, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field154, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field155, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field156, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field157, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field158, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field159, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field160, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field161, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field162, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field163, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field164, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field165, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field166, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field167, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field168, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field169, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field170, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field171, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field172, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field173, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field174, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field175, 2),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_penalty, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_penalty, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  past_compound, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_compound, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  compound_acru, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  compound_rate, 4),\
	APP_DEFSDMEMBER(T_STRING,  use_plan_rate, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_pmt_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  term, 0),\
	APP_DEFSDMEMBER(T_STRING,  calc_type, 0),\
	APP_DEFSDMEMBER(T_LONG,  calc_cycle, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_rate, 4),\
	APP_DEFSDMEMBER(T_STRING,  last_fee_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  next_fee_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  first_dd_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field176, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_terminal_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_merch_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  wares_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  original_amt, 4),\
	APP_DEFSDMEMBER(T_STRING,  interest_calc_base, 0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_PLAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_PLAN_H__*/
