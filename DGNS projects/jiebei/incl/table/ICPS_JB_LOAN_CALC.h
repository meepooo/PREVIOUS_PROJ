/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_LOAN_CALC.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_LOAN_CALC (F_JB11.��Ϣ������ϸ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_LOAN_CALC_H__
#define __ICPS_JB_LOAN_CALC_H__
typedef struct TDB_ICPS_JB_LOAN_CALC
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   contract_no[64+1];  /*����ƽ̨�����ͬ��*/
		/*����ƽ̨�����ͬ��*/
	char   calc_date[8+1];  /*��Ϣ����*/
		/*��Ϣ���� YYYYMMDD*/
	char   accrued_status[2+1];  /*Ӧ�Ʒ�Ӧ�Ʊ�ʶ*/
		/*Ӧ�Ʒ�Ӧ�Ʊ�ʶ Ӧ��0����Ӧ��1*/
	double   prin_bal;  /*�����������*/
		/*�����������*/
	double   ovd_prin_bal;  /*���ڱ������*/
		/*���ڱ������*/
	double   ovd_int_bal;  /*������Ϣ���*/
		/*������Ϣ���*/
	double   real_rate;  /*����ʵ��������*/
		/*����ʵ��������*/
	double   pnlt_rate;  /*���Ϣ������*/
		/*���Ϣ������*/
	double   int_amt;  /*������Ϣ*/
		/*������Ϣ*/
	double   ovd_prin_pnlt_amt;  /*���ڱ���Ϣ*/
		/*���ڱ���Ϣ*/
	double   ovd_int_pnlt_amt;  /*������Ϣ��Ϣ*/
		/*������Ϣ��Ϣ*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_LOAN_CALC;

#define SD_DATA  ICPS_JB_LOAN_CALC
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  calc_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  accrued_status, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  real_rate, 6),\
	APP_DEFSDMEMBER(T_DOUBLE,  pnlt_rate, 6),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_LOAN_CALC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_LOAN_CALC_H__*/
