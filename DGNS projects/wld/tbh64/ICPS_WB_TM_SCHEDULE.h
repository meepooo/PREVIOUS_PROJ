/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_SCHEDULE.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_SCHEDULE (F_WB12.��������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_SCHEDULE_H__
#define __ICPS_WB_TM_SCHEDULE_H__
typedef struct TDB_ICPS_WB_TM_SCHEDULE
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   schedule_id[20+1];  /*�����ID*/
		/*�����ID*/
	char   loan_id[20+1];  /*����ƻ�ID*/
		/*����ƻ�ID*/
	char   org[12+1];  /*������*/
		/*������*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	char   logical_card_no[19+1];  /*�߼�����*/
		/*�߼�����*/
	char   card_no[19+1];  /*����*/
		/*����*/
	double   loan_init_prin;  /*�����ܱ���*/
		/*�����ܱ���*/
	int   loan_init_term;  /*����������*/
		/*����������*/
	int   curr_term;  /*��ǰ����*/
		/*��ǰ����*/
	double   loan_term_prin;  /*Ӧ������*/
		/*Ӧ������*/
	double   loan_term_fee1;  /*Ӧ������*/
		/*Ӧ������*/
	double   loan_term_interest;  /*Ӧ����Ϣ*/
		/*Ӧ����Ϣ*/
	char   loan_pmt_due_date[14+1];  /*����ڻ�������*/
		/*����ڻ�������*/
	char   loan_grace_date[14+1];  /*������*/
		/*������*/
	char   last_modified_datetime[14+1];  /*�޸�ʱ��*/
		/*�޸�ʱ��*/
	char   start_date[14+1];  /*��Ϣ��*/
		/*��Ϣ��*/
	char   schedule_action[1+1];  /*����ƻ���������*/
		/*����ƻ���������*/
	double   prin_paid;  /*�ѳ�������*/
		/*�ѳ�������*/
	double   int_paid;  /*�ѳ�����Ϣ*/
		/*�ѳ�����Ϣ*/
	double   penalty_paid;  /*�ѳ�����Ϣ*/
		/*�ѳ�����Ϣ*/
	double   compound_paid;  /*�ѳ�������*/
		/*�ѳ�������*/
	double   fee_paid;  /*�ѳ�������*/
		/*�ѳ�������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_SCHEDULE;

#define SD_DATA  ICPS_WB_TM_SCHEDULE
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  schedule_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_prin, 2),\
	APP_DEFSDMEMBER(T_LONG,  loan_init_term, 0),\
	APP_DEFSDMEMBER(T_LONG,  curr_term, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_term_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_term_fee1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_term_interest, 2),\
	APP_DEFSDMEMBER(T_STRING,  loan_pmt_due_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_grace_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  start_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  schedule_action, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  compound_paid, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_paid, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_SCHEDULE)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_SCHEDULE_H__*/
