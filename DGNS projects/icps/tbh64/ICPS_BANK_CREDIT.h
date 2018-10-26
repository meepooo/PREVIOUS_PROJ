/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_BANK_CREDIT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_BANK_CREDIT (5.����������Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_BANK_CREDIT_H__
#define __ICPS_BANK_CREDIT_H__
typedef struct TDB_ICPS_BANK_CREDIT
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
	char   is_exist_customer[1+1];  /*�Ƿ�����ͻ�*/
		/*�Ƿ�����ͻ� 1-�� 0-��*/
	char   is_exist_debt_customer[1+1];  /*�Ƿ������ǿ��ͻ�*/
		/*�Ƿ������ǿ��ͻ� 1-�� 0-��*/
	double   balance;  /*�������*/
		/*�������*/
	double   avg_balance_last_3days;  /*��3�����վ����*/
		/*��3�����վ����*/
	double   avg_balance_last_6days;  /*��6�����վ����*/
		/*��6�����վ����*/
	double   income_last_3m;  /*��3����������ˮ��������*/
		/*��3����������ˮ��������*/
	double   pay_last_3m;  /*��3����������ˮ֧�������*/
		/*��3����������ˮ֧�������*/
	double   income_last_6m;  /*��6����������ˮ��������*/
		/*��6����������ˮ��������*/
	double   pay_last_6m;  /*��6����������ˮ֧�������*/
		/*��6����������ˮ֧�������*/
	char   is_exist_credit_customer[1+1];  /*�Ƿ�������ÿ��ͻ�*/
		/*�Ƿ�������ÿ��ͻ� 1-�� 0-��*/
	double   curr_credit_card_amt;  /*�������ÿ����Ŷ��*/
		/*�������ÿ����Ŷ��*/
	double   curr_use_credit_card_amt;  /*�������ÿ���ǰʹ�ö��*/
		/*�������ÿ���ǰʹ�ö��*/
	char   is_exist_fin_customer[1+1];  /*�Ƿ������ƿͻ�*/
		/*�Ƿ������ƿͻ� 1-�� 0-��*/
	double   fin_balance;  /*������*/
		/*������*/
	double   avg_fin_bal_last_6m;  /*��6�����վ������*/
		/*��6�����վ������*/
	char   is_exist_insurance_customer[1+1];  /*�Ƿ�������տͻ�*/
		/*�Ƿ�������տͻ� 1-�� 0-��*/
	char   is_exist_loan_customer[1+1];  /*�Ƿ��������ͻ�*/
		/*�Ƿ��������ͻ� 1-�� 0-��*/
	double   operation_loan_bal;  /*��Ӫ����������*/
		/*��Ӫ����������*/
	double   personal_credit_bal;  /*����������������*/
		/*����������������*/
	double   car_loan_bal;  /*�������*/
		/*�������*/
	double   car_asset;  /*������ֵ������*/
		/*������ֵ������*/
	double   house_loan_bal;  /*�������*/
		/*�������*/
	double   house_asset;  /*������ֵ������*/
		/*������ֵ������*/
	char   is_stock_customer[1+1];  /*�Ƿ�֤ȯ�ͻ�*/
		/*�Ƿ�֤ȯ�ͻ� 1-�� 0-��*/
	char   is_third_depository[1+1];  /*�Ƿ��������ܿͻ�*/
		/*�Ƿ��������ܿͻ� 1-�� 0-��*/
	char   is_payroll_customer[1+1];  /*�Ƿ��ʴ����ͻ�*/
		/*�Ƿ��ʴ����ͻ� 1-�� 0-��*/
	char   is_social_security_customer[1+1];  /*�Ƿ��籣���ɿͻ�*/
		/*�Ƿ��籣���ɿͻ� 1-�� 0-��*/
	char   is_life_payment_customer[1+1];  /*�Ƿ�ˮ��ú���ɿͻ�*/
		/*�Ƿ�ˮ��ú���ɿͻ� 1-�� 0-��*/
	char   company_name[255+1];  /*������λ*/
		/*������λ*/
	char   company_origin[1+1];  /*������λ������Դ*/
		/*������λ������Դ 1-��ʵ 2-�ͻ���д 3-����*/
	char   position[64+1];  /*ְλ*/
		/*ְλ*/
	char   position_origin[1+1];  /*ְλ��Ϣ��Դ*/
		/*ְλ��Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����*/
	char   industry[64+1];  /*��ҵ*/
		/*��ҵ*/
	char   industry_origin[1+1];  /*��ҵ��Ϣ��Դ*/
		/*��ҵ��Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����*/
	int   work_years;  /*��������*/
		/*��������*/
	char   work_years_origin[1+1];  /*����������Ϣ��Դ*/
		/*����������Ϣ ��Դ 1-��ʵ 2-�ͻ���д 3-����*/
	int   income;  /*����������*/
		/*����������*/
	char   income_origin[1+1];  /*��������Ϣ��Դ*/
		/*��������Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����*/
	char   marriage_status[1+1];  /*����״̬*/
		/*����״̬ 1-δ�� 2-�ѻ� 3-��� 4-ɥż NULL-����*/
	char   marriage_origin[1+1];  /*����״̬��Ϣ��Դ*/
		/*����״̬��Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����*/
	char   is_operation[1+1];  /*�Ƿ�Ӫ��*/
		/*�Ƿ�Ӫ�� ��������ҵ����幤����ҵ����1-�� 0-��*/
	char   operation_origin[1+1];  /*�Ƿ�Ӫ����Ϣ��Դ*/
		/*�Ƿ�Ӫ����Ϣ��Դ 1-��ʵ 2-�ͻ���д 3-����*/
	char   is_inner_black_customer[1+1];  /*�Ƿ�����ڲ��������ͻ�*/
		/*�Ƿ�����ڲ��������ͻ� 1-�� 0-��*/
	char   is_police_certified[1+1];  /*�Ƿ񹫰��������֤�ɹ�*/
		/*�Ƿ񹫰��������֤�ɹ� 1- �� 0-��*/
	char   is_court_exec_customer[1+1];  /*�Ƿ���б�ִ���˵�������Ϣ*/
		/*�Ƿ���б�ִ���˵�������Ϣ 1-�� 0-��*/
	char   is_query_house_fund[1+1];  /*�Ƿ��в�ѯ��������Ϣ*/
		/*�Ƿ��в�ѯ��������Ϣ 1-�� 0-�� */
	char   fund_query_date[6+1];  /*�������ѯʱ��*/
		/*�������ѯʱ�� YYYYMM*/
	double   fund_month_amt;  /*�������ѯ�½��ɶ�*/
		/*�������ѯ�½��ɶ�*/
	char   fund_acct_date[6+1];  /*�����𿪻�����*/
		/*�����𿪻����� YYYYMM*/
	int   fund_months_last_6m;  /*��6�����ۼƽ�������*/
		/*��6�����ۼƽ�������*/
	double   fund_amt_last_6m;  /*��6�����ۼƽ��ɽ��*/
		/*��6�����ۼƽ��ɽ��*/
	int   fund_total_months;  /*�ܽ�������*/
		/*�ܽ�������*/
	double   fund_total_amt;  /*�ܽ��ɽ��*/
		/*�ܽ��ɽ��*/
	double   fund_max_amt;  /*���������ؽ�������*/
		/*���������ؽ�������*/
	char   is_query_social_security[1+1];  /*�Ƿ��в�ѯ�籣��Ϣ*/
		/*�Ƿ��в�ѯ�籣��Ϣ 1-�� 0-�� */
	char   social_query_date[6+1];  /*�籣��Ϣ��ѯʱ��*/
		/*�籣��Ϣ��ѯʱ�� YYYYMM*/
	double   pension_query_month_amt;  /*���ϱ��ղ�ѯ�½��ɶ�*/
		/*���ϱ��ղ�ѯ�½��ɶ�*/
	char   pension_acct_date[6+1];  /*���ϱ��տ�������*/
		/*���ϱ��տ������� YYYYMM*/
	int   pension_months_last_6m;  /*��6�������ϱ����ۼƽ�������*/
		/*��6�������ϱ����ۼƽ�������*/
	double   pension_amt_last_6m;  /*��6�������ϱ����ۼƽ��ɽ��*/
		/*��6�������ϱ����ۼƽ��ɽ��*/
	int   pension_total_months;  /*���ϱ����ܽ�������*/
		/*���ϱ����ܽ�������*/
	double   pension_total_amt;  /*���ϱ����ܽ��ɽ��*/
		/*���ϱ����ܽ��ɽ��*/
	double   medicare_month_amt;  /*ҽ�Ʊ��ղ�ѯ�½��ɶ�*/
		/*ҽ�Ʊ��ղ�ѯ�½��ɶ�*/
	char   medicare_acct_date[6+1];  /*ҽ�Ʊ��տ�������*/
		/*ҽ�Ʊ��տ������� YYYYMM*/
	int   medicare_months_last_6m;  /*��6����ҽ�Ʊ����ۼƽ�������*/
		/*��6����ҽ�Ʊ����ۼƽ�������*/
	double   medicare_amt_last_6m;  /*��6����ҽ�Ʊ����ۼƽ��ɽ��*/
		/*��6����ҽ�Ʊ����ۼƽ��ɽ��*/
	int   medicare_total_months;  /*ҽ�Ʊ����ܽ�������*/
		/*ҽ�Ʊ����ܽ�������*/
	double   medicare_total_amt;  /*ҽ�Ʊ����ܽ��ɽ��*/
		/*ҽ�Ʊ����ܽ��ɽ��*/
	char   is_query_degree[1+1];  /*�Ƿ��в�ѯѧ����Ϣ*/
		/*�Ƿ��в�ѯѧ����Ϣ 1-�� 0-�� */
	char   school_name[64+1];  /*ԺУ����*/
		/*ԺУ����*/
	char   degree_level[64+1];  /*ѧ�����*/
		/*ѧ����� ���м����£�ר�ƣ�ѧʿ��˶ʿ����ʿ������*/
	char   degree_type[64+1];  /*ѧ�����*/
		/*ѧ�����*/
	char   entrance_year[4+1];  /*��ѧ���*/
		/*��ѧ��� YYYY*/
	char   is_query_communication[1+1];  /*�Ƿ��в�ѯ��Ӫ����Ϣ*/
		/*�Ƿ��в�ѯ��Ӫ����Ϣ 1-�� 0-�� */
	char   communication[1+1];  /*��Ӫ��*/
		/*��Ӫ�� 1-�ƶ� 2-��ͨ 3-���� 4-����*/
	int   online_days;  /*����ʱ��*/
		/*����ʱ��*/
	double   total_tel_fare;  /*�ܻ����˵����*/
		/*�ܻ����˵����*/
	int   total_call_hours;  /*������ͨ��ʱ��*/
		/*������ͨ��ʱ�� ��Сʱ����ȡ��*/
	char   is_out_black_customer[1+1];  /*�Ƿ�����ⲿ��ѯ������*/
		/*�Ƿ�����ⲿ��ѯ������ 1-�� 0-�� */
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_BANK_CREDIT;

#define SD_DATA  ICPS_BANK_CREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_debt_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  avg_balance_last_3days, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  avg_balance_last_6days, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  income_last_3m, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pay_last_3m, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  income_last_6m, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pay_last_6m, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_credit_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_credit_card_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_use_credit_card_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_fin_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fin_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  avg_fin_bal_last_6m, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_insurance_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_exist_loan_customer, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  operation_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  personal_credit_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  car_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  car_asset, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  house_loan_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  house_asset, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_stock_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_third_depository, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_payroll_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_social_security_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_life_payment_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  company_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  company_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  position, 0),\
	APP_DEFSDMEMBER(T_STRING,  position_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  industry, 0),\
	APP_DEFSDMEMBER(T_STRING,  industry_origin, 0),\
	APP_DEFSDMEMBER(T_LONG,  work_years, 0),\
	APP_DEFSDMEMBER(T_STRING,  work_years_origin, 0),\
	APP_DEFSDMEMBER(T_LONG,  income, 0),\
	APP_DEFSDMEMBER(T_STRING,  income_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  marriage_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  marriage_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_operation, 0),\
	APP_DEFSDMEMBER(T_STRING,  operation_origin, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_inner_black_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_police_certified, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_court_exec_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_query_house_fund, 0),\
	APP_DEFSDMEMBER(T_STRING,  fund_query_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_month_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  fund_acct_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  fund_months_last_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_amt_last_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  fund_total_months, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_total_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fund_max_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_query_social_security, 0),\
	APP_DEFSDMEMBER(T_STRING,  social_query_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pension_query_month_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  pension_acct_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  pension_months_last_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pension_amt_last_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  pension_total_months, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pension_total_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  medicare_month_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  medicare_acct_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  medicare_months_last_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  medicare_amt_last_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  medicare_total_months, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  medicare_total_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_query_degree, 0),\
	APP_DEFSDMEMBER(T_STRING,  school_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  degree_level, 0),\
	APP_DEFSDMEMBER(T_STRING,  degree_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  entrance_year, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_query_communication, 0),\
	APP_DEFSDMEMBER(T_STRING,  communication, 0),\
	APP_DEFSDMEMBER(T_LONG,  online_days, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  total_tel_fare, 2),\
	APP_DEFSDMEMBER(T_LONG,  total_call_hours, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_out_black_customer, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_BANK_CREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_BANK_CREDIT_H__*/
