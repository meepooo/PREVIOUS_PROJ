/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_LENDING_DETAIL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_LENDING_DETAIL (F_JB2.��;֧����ϸ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_LENDING_DETAIL_H__
#define __ICPS_JB_LENDING_DETAIL_H__
typedef struct TDB_ICPS_JB_LENDING_DETAIL
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   contract_no[64+1];  /*����ƽ̨�����ͬ��*/
		/*����ƽ̨�����ͬ��*/
	char   fund_seq_no[64+1];  /*�ſ��ʽ���ˮ��*/
		/*�ſ��ʽ���ˮ��*/
	char   third_product_code[64+1];  /*��Ʒ��*/
		/*��Ʒ��*/
	char   name[128+1];  /*�ͻ���ʵ����*/
		/*�ͻ���ʵ����*/
	char   id_type[2+1];  /*֤������*/
		/*֤������*/
	char   id_num[32+1];  /*�ͻ�֤������*/
		/*�ͻ�֤������*/
	char   loan_status[2+1];  /*����״̬*/
		/*����״̬ 1-�ɹ� 2-ʧ�� 3-��;*/
	char   loan_use[2+1];  /*������;*/
		/*������; 1-���� 2-��Ӫ*/
	char   use_area[2+1];  /*�����ʽ�ʹ��λ��*/
		/*�����ʽ�ʹ��λ�� 0-���� 1-����*/
	char   apply_date[20+1];  /*����֧��ʱ��*/
		/*����֧��ʱ�� YYYYMMDDHHMMSS*/
	char   encash_date[20+1];  /*�ſ�����*/
		/*�ſ����� YYYYMMDDHHMMSS*/
	char   currency[3+1];  /*����*/
		/*���� CNY*/
	double   encash_amt;  /*�ſ���*/
		/*�ſ���*/
	char   start_date[8+1];  /*������Ϣ��*/
		/*������Ϣ�� YYYYMMDD*/
	char   end_date[8+1];  /*�������*/
		/*������� YYYYMMDD*/
	int   total_terms;  /*�����ڴ���*/
		/*�����ڴ���*/
	char   repay_mode[8+1];  /*���ʽ*/
		/*���ʽ 1-�ȶϢ 2-�ȶ�� 6-���ڸ�Ϣ����һ�λ���*/
	int   grace_day;  /*����������*/
		/*����������*/
	char   rate_type[2+1];  /*��������*/
		/*�������� F-�̶����� L0-��������-���� L1-��������-���� L2-��������-���� L3-��������-���� L4-��������-������ L5-��������-���� L9-��������-����*/
	double   day_rate;  /*����������*/
		/*����������*/
	char   prin_repay_frequency[2+1];  /*���𻹿�Ƶ��*/
		/*���𻹿�Ƶ�ʣ��ñʴ����������λ���ʱ��ļ����01:��02:��03:��04:��05:����06:��07:һ����08:�����ڣ���������������ʱ�仹�99:����*/
	char   int_repay_frequency[2+1];  /*��Ϣ����Ƶ��*/
		/*���𻹿�Ƶ�ʣ��ñʴ����������λ���ʱ��ļ����01:��02:��03:��04:��05:����06:��07:һ����08:�����ڣ���������������ʱ�仹�99:����*/
	char   guarantee_type[3+1];  /*��������*/
		/*�������ͣ�A ��Ѻ����B ��Ѻ����B01   ���ز���Ѻ����B99   ������Ѻ����C ��֤����C01   ��������C99   ������֤����D ����/�ⵣ������E ��ϵ���Z ����*/
	char   credit_no[64+1];  /*���ű��*/
		/*���ű��*/
	char   encash_acct_type[2+1];  /*�ſ��ʺ�����*/
		/*�ſ��ʺ����ͣ�01:���н�ǿ�02:֧����*/
	char   encash_acct[32+1];  /*�ſ��ʺ�*/
		/*�ſ��ʺ�*/
	char   repay_acct_type[2+1];  /*�����ʺ�����*/
		/*�����ʺ����ͣ�01:���н�ǿ�02:֧����*/
	char   repay_acct[32+1];  /*�����ʺ�*/
		/*�����ʺ�*/
	char   loan_apply_no[32+1];  /*�������뵥��*/
		/*�������뵥��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_LENDING_DETAIL;

#define SD_DATA  ICPS_JB_LENDING_DETAIL
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  fund_seq_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_use, 0),\
	APP_DEFSDMEMBER(T_STRING,  use_area, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  start_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  total_terms, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_mode, 0),\
	APP_DEFSDMEMBER(T_LONG,  grace_day, 0),\
	APP_DEFSDMEMBER(T_STRING,  rate_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  day_rate, 6),\
	APP_DEFSDMEMBER(T_STRING,  prin_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_STRING,  int_repay_frequency, 0),\
	APP_DEFSDMEMBER(T_STRING,  guarantee_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  credit_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  encash_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_LENDING_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_LENDING_DETAIL_H__*/
