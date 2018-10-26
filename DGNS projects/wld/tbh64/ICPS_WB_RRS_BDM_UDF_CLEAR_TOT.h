/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_RRS_BDM_UDF_CLEAR_TOT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_RRS_BDM_UDF_CLEAR_TOT (F_WB20.�������ʽ�������ܱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_RRS_BDM_UDF_CLEAR_TOT_H__
#define __ICPS_WB_RRS_BDM_UDF_CLEAR_TOT_H__
typedef struct TDB_ICPS_WB_RRS_BDM_UDF_CLEAR_TOT
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   data_dt[10+1];  /*��������*/
		/*��������*/
	char   acct_no[40+1];  /*�������ʺ�*/
		/*�������ʺ�*/
	char   currency[23+1];  /*����*/
		/*����*/
	char   acct_name[100+1];  /*����*/
		/*����*/
	double   last_balance;  /*�����˻����*/
		/*�����˻����*/
	double   balance;  /*�����˻����*/
		/*�����˻����*/
	double   payment_amt;  /*���շſ��ܽ��*/
		/*���շſ��ܽ��*/
	double   repayment_amt;  /*���ջ����ܽ��*/
		/*���ջ����ܽ��*/
	double   other_credit_amt;  /*���������������*/
		/*���������������*/
	double   other_debit_amt;  /*����������������*/
		/*����������������*/
	char   ds[10+1];  /*���ڷ���*/
		/*���ڷ���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_RRS_BDM_UDF_CLEAR_TOT;

#define SD_DATA  ICPS_WB_RRS_BDM_UDF_CLEAR_TOT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  data_dt, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_name, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_balance, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  balance, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  payment_amt, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  repayment_amt, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  other_credit_amt, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  other_debit_amt, 4),\
	APP_DEFSDMEMBER(T_STRING,  ds, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_RRS_BDM_UDF_CLEAR_TOT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_RRS_BDM_UDF_CLEAR_TOT_H__*/
