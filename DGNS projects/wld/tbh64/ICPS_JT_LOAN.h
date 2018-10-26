/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JT_LOAN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JT_LOAN (F_JT5.��������Ϣ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JT_LOAN_H__
#define __ICPS_JT_LOAN_H__
typedef struct TDB_ICPS_JT_LOAN
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������YYYYMMDD*/
	int   file_order;  /*�ļ����*/
		/**/
	char   contract_no[64+1];  /*��ͬ��*/
		/*�ͻ�ǩ���ĺ�ͬ����*/
	char   customer_code[60+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   product_code[4+1];  /*��Ʒ���*/
		/*��Ʒ���*/
	char   quota_code[60+1];  /*��ȱ��*/
		/*��ȱ��*/
	char   loan_code[60+1];  /*������*/
		/*������*/
	char   currency[3+1];  /*����*/
		/*���� Ĭ��CNY*/
	char   loan_status[1+1];  /*����״̬*/
		/*����״̬ 1���� 2���� 3���� 9����*/
	char   encash_date[8+1];  /*�ſ�����*/
		/*�ſ�����*/
	double   encash_amt;  /*�ſ���*/
		/*�ſ���*/
	char   end_date[8+1];  /*��������*/
		/*��������*/
	char   use_area[6+1];  /*�����ʽ�ʹ��λ��*/
		/*�����ʽ�ʹ��λ�� I:���ڣ��й���½��O:���⣨���۰�̨��*/
	char   prin_repay_frequency[6+1];  /*���𻹿�Ƶ��*/
		/*���𻹿�Ƶ�� �������λ���ʱ��ļ�� 01:�� 02:�� 03:�� 04:�� 05:���� 06:�� 07:һ����08:�����ڣ���������������ʱ�仹�99:����*/
	char   int_repay_frequency[6+1];  /*��Ϣ����Ƶ��*/
		/*��Ϣ����Ƶ�� �������λ���ʱ��ļ�� 01:�� 02:�� 03:�� 04:�� 05:���� 06:�� 07:һ����08:�����ڣ���������������ʱ�仹�99:����*/
	double   self_pay_amt;  /*����֧�����*/
		/*����֧�����*/
	double   entrusted_pay_amt;  /*����֧�����*/
		/*����֧�����*/
	char   ovd_flag[1+1];  /*���ڱ�־*/
		/*���ڱ�־ 1:���� 0:����*/
	int   ovd_days;  /*��������*/
		/*��������*/
	int   ovd_non_days;  /*���ڿ�������*/
		/*���ڿ�������*/
	char   prin_ovd_days[8+1];  /*������������*/
		/*������������*/
	char   int_ovd_days[8+1];  /*��Ϣ��������*/
		/*��Ϣ��������*/
	char   next_int_date[8+1];  /*��һ��Ϣ��*/
		/*��һ��Ϣ��*/
	char   rate_type[6+1];  /*��������*/
		/*�������� F:�̶����� L0:��������-���� L1:��������-���� L2:��������-���� L3:��������-���� L4:��������-������ L5:��������-���� L9:��������-����*/
	double   loan_bal;  /*�������*/
		/*�������*/
	double   ovd_loan_bal;  /*���ڴ������*/
		/*���ڴ������*/
	double   ovd_int;  /*������Ϣ*/
		/*������Ϣ*/
	double   out_int_bal;  /*����ǷϢ*/
		/*����ǷϢ*/
	char   int_flag[1+1];  /*��Ϣ��־*/
		/*��Ϣ��־ Y:������Ϣ N:ֹͣ��Ϣ*/
	double   accrued_int;  /*Ӧ����Ϣ*/
		/*Ӧ����Ϣ*/
	double   int_amt;  /*������Ϣ*/
		/*������Ϣ*/
	double   pnlt_amt;  /*���շ�Ϣ*/
		/*���շ�Ϣ*/
	char   encash_acct[64+1];  /*���������˺�*/
		/*���������˺�*/
	char   repay_acct[64+1];  /*�����˺�*/
		/*�����˺�*/
	char   guarantee_type[3+1];  /*�������ʽ*/
		/*�������ʽ A��Ѻ����B��Ѻ����B01���ز���Ѻ����B99������Ѻ����C��֤����C01��������C99������֤����D����/�ⵣ������E��ϵ���Z ����*/
	char   repay_mode[1+1];  /*���ʽ*/
		/*���ʽ 1-�ȶ��;2-���ڻ���*/
	double   loan_rate;  /*�������*/
		/*�������*/
	double   penalty_rate;  /*ΥԼ������*/
		/*ΥԼ������*/
	char   loan_rate_type[1+1];  /*�����������*/
		/*�����������*/
	char   penalty_rate_type[1+1];  /*ΥԼ����������*/
		/*ΥԼ����������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JT_LOAN;

#define SD_DATA  ICPS_JT_LOAN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  quota_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 8),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  use_area, 0),\
	APP_DEFSDMEMBER(T_STRING,  prin_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_STRING,  int_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  self_pay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  entrusted_pay_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  ovd_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  ovd_days, 0),\
	APP_DEFSDMEMBER(T_LONG,  ovd_non_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  prin_ovd_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  int_ovd_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  next_int_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  rate_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_int_bal, 2),\
	APP_DEFSDMEMBER(T_STRING,  int_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_int, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  encash_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  guarantee_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_mode, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_rate, 8),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate, 8),\
	APP_DEFSDMEMBER(T_STRING,  loan_rate_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  penalty_rate_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_LOAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_LOAN_H__*/
