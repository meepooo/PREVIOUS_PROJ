/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_TXN_REJECT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_TXN_REJECT (F_WB10.���˽�����ʷ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_TXN_REJECT_H__
#define __ICPS_WB_TM_TXN_REJECT_H__
typedef struct TDB_ICPS_WB_TM_TXN_REJECT
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   trans_serial[20+1];  /*������ˮ��*/
		/*������ˮ��*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	char   card_no[19+1];  /*����*/
		/*����*/
	char   logical_card_no[19+1];  /*�߼�����*/
		/*�߼�����*/
	char   bsc_logiccard_no[19+1];  /*�߼�����������*/
		/*�߼�����������*/
	char   product_code[6+1];  /*��Ʒ����*/
		/*��Ʒ����*/
	char   trans_date[14+1];  /*��������*/
		/*��������*/
	char   trans_time[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   post_txn_type[1+1];  /*���˽�������*/
		/*���˽�������*/
	char   txn_code[4+1];  /*������*/
		/*������*/
	char   loan_flag[1+1];  /*�����־*/
		/*�����־*/
	double   trans_amt;  /*���׽��*/
		/*���׽��*/
	double   post_amt;  /*���˱��ֽ��*/
		/*���˱��ֽ�� */
	char   transfer_in_date[14+1];  /*��������*/
		/*��������*/
	char   user_field252[6+1];  /*�����ֶ�252*/
		/*�����ֶ�252*/
	char   user_field253[27+1];  /*�����ֶ�253*/
		/*�����ֶ�253*/
	char   txn_curr_cd[3+1];  /*���ױ��ִ���*/
		/*���ױ��ִ���*/
	char   post_curr_cd[3+1];  /*���˱��ִ���*/
		/*���˱��ִ���*/
	char   orig_trans_date[14+1];  /*ԭʼ��������*/
		/*ԭʼ��������*/
	char   plan_nbr[6+1];  /*���üƻ���*/
		/*���üƻ���*/
	char   ref_nbr[23+1];  /*���ײο���*/
		/*���ײο���*/
	char   txn_desc[80+1];  /*��������*/
		/*��������*/
	char   txn_short_desc[80+1];  /*�˵���������*/
		/*�˵���������*/
	double   user_field254;  /*�����ֶ�254*/
		/*�����ֶ�254*/
	char   posting_flag[3+1];  /*���˽����ʾ��*/
		/*���˽����ʾ��*/
	char   pre_posting_flag[3+1];  /*�������˽����ʾ��*/
		/*�������˽����ʾ��*/
	double   user_field255;  /*�����ֶ�255*/
		/*�����ֶ�255*/
	double   orig_pmt_amt;  /*�����ԭʼ���*/
		/*�����ԭʼ���*/
	char   user_field256[9+1];  /*�����ֶ�256*/
		/*�����ֶ�256*/
	char   user_field257[8+1];  /*�����ֶ�257*/
		/*�����ֶ�257*/
	char   user_field258[15+1];  /*�����ֶ�258*/
		/*�����ֶ�258*/
	char   user_field259[40+1];  /*�����ֶ�259*/
		/*�����ֶ�259*/
	char   mcc[4+1];  /*�̻�������*/
		/*�̻�������*/
	char   input_txn_code[4+1];  /*ԭ���׽�����*/
		/*ԭ���׽�����*/
	double   input_txn_amt;  /*ԭ���׽��׽��*/
		/*ԭ���׽��׽��*/
	double   input_sett_amt;  /*ԭ����������*/
		/*ԭ����������*/
	double   user_field260;  /*�����ֶ�260*/
		/*�����ֶ�260*/
	double   user_field261;  /*�����ֶ�261*/
		/*�����ֶ�261*/
	double   user_field262;  /*�����ֶ�262*/
		/*�����ֶ�262*/
	double   user_field263;  /*�����ֶ�263*/
		/*�����ֶ�263*/
	char   stmt_date[14+1];  /*��һ���ڻ�����*/
		/*��һ���ڻ�����*/
	char   voucher_no[7+1];  /*���۵�ƾ֤��*/
		/*���۵�ƾ֤��*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	int   term;  /*���ڴ�������*/
		/*���ڴ�������*/
	char   busi_serial[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   sys_trans_id[32+1];  /*ϵͳ������ˮ��*/
		/*ϵͳ������ˮ��*/
	char   user_field265[40+1];  /*�����ֶ�265*/
		/*�����ֶ�265*/
	char   user_field264[15+1];  /*�����ֶ�264*/
		/*�����ֶ�264*/
	char   sub_terminal_type[15+1];  /*�ն�����*/
		/*�ն�����*/
	char   user_field266[60+1];  /*�����ֶ�266*/
		/*�����ֶ�266*/
	char   user_field267[60+1];  /*�����ֶ�267*/
		/*�����ֶ�267*/
	char   last_modified_datetime[14+1];  /*�޸�ʱ��*/
		/*�޸�ʱ��*/
	char   paid_stmt_date[14+1];  /*�������������գ����ã�*/
		/*�������������գ����ã�*/
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

}ICPS_WB_TM_TXN_REJECT;

#define SD_DATA  ICPS_WB_TM_TXN_REJECT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  bsc_logiccard_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  post_txn_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  post_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  transfer_in_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field252, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field253, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  post_curr_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  orig_trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_short_desc, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field254, 4),\
	APP_DEFSDMEMBER(T_STRING,  posting_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  pre_posting_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field255, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  orig_pmt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field256, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field257, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field258, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field259, 0),\
	APP_DEFSDMEMBER(T_STRING,  mcc, 0),\
	APP_DEFSDMEMBER(T_STRING,  input_txn_code, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  input_txn_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  input_sett_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field260, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field261, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field262, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field263, 2),\
	APP_DEFSDMEMBER(T_STRING,  stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  voucher_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_LONG,  term, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field265, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field264, 0),\
	APP_DEFSDMEMBER(T_STRING,  sub_terminal_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field266, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field267, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_stmt_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_TXN_REJECT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_TXN_REJECT_H__*/
