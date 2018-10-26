/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_REPAY_LOAN_DETAIL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_REPAY_LOAN_DETAIL (F_JB5.�����ݣ���ϸ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_REPAY_LOAN_DETAIL_H__
#define __ICPS_JB_REPAY_LOAN_DETAIL_H__
typedef struct TDB_ICPS_JB_REPAY_LOAN_DETAIL
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   contract_no[64+1];  /*����ƽ̨�����ͬ��*/
		/*����ƽ̨�����ͬ��*/
	char   repay_seq_no[64+1];  /*������ˮ��*/
		/*������ˮ��*/
	char   fee_no[64+1];  /*�շѵ���*/
		/*�շѵ���*/
	char   withdraw_no[64+1];  /*�������ֵ���*/
		/*�������ֵ���*/
	char   repay_type[8+1];  /*��������*/
		/*�������� 01-�������� 02-�����ۿ� 03-����֪ͨ���� 04-���»���*/
	char   repay_date[20+1];  /*��������*/
		/*�������� YYYYMMDDHHMMSS*/
	double   curr_prin_bal;  /*���λ���ǰ��Ӧ��δ�������������*/
		/*���λ���ǰ��Ӧ��δ�������������*/
	double   curr_ovd_prin_bal;  /*���λ���ǰ��Ӧ��δ�����ڱ������*/
		/*���λ���ǰ��Ӧ��δ�����ڱ������*/
	double   curr_int_bal;  /*���λ���ǰ��Ӧ��δ��������Ϣ���*/
		/*���λ���ǰ��Ӧ��δ��������Ϣ���*/
	double   curr_ovd_int_bal;  /*���λ���ǰ��Ӧ��δ��������Ϣ���*/
		/*���λ���ǰ��Ӧ��δ��������Ϣ���*/
	double   curr_ovd_prin_pnlt_bal;  /*���λ���ǰ��Ӧ��δ�����ڱ���Ϣ���*/
		/*���λ���ǰ��Ӧ��δ�����ڱ���Ϣ���*/
	double   curr_ovd_int_pnlt_bal;  /*���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ���*/
		/*���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ���*/
	double   repay_amt;  /*�ܽ��*/
		/*�ܽ��*/
	double   paid_prin_amt;  /*����ʵ������������*/
		/*����ʵ������������*/
	double   paid_ovd_prin_amt;  /*����ʵ�����ڱ�����*/
		/*����ʵ�����ڱ�����*/
	double   paid_int_amt;  /*����ʵ��������Ϣ���*/
		/*����ʵ��������Ϣ���*/
	double   paid_ovd_int_amt;  /*����ʵ��������Ϣ���*/
		/*����ʵ��������Ϣ���*/
	double   paid_ovd_prin_pnlt_amt;  /*����ʵ�����ڱ���Ϣ���*/
		/*����ʵ�����ڱ���Ϣ���*/
	double   paid_ovd_int_pnlt_amt;  /*����ʵ��������Ϣ��Ϣ���*/
		/*����ʵ��������Ϣ��Ϣ���*/
	double   fee_amt;  /*���λ����Ӧ��ƽ̨����ѽ��*/
		/*���λ����Ӧ��ƽ̨����ѽ��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_REPAY_LOAN_DETAIL;

#define SD_DATA  ICPS_JB_REPAY_LOAN_DETAIL
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_seq_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  withdraw_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_prin_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_int_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_REPAY_LOAN_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_REPAY_LOAN_DETAIL_H__*/
