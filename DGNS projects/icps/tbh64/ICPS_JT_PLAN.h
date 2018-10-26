/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JT_PLAN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JT_PLAN (F_JT6.�����ƻ���Ϣ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JT_PLAN_H__
#define __ICPS_JT_PLAN_H__
typedef struct TDB_ICPS_JT_PLAN
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������YYYYMMDD*/
	int   file_order;  /*�ļ����*/
		/**/
	char   contract_no[64+1];  /*��ͬ��*/
		/*�ͻ�ǩ���ĺ�ͬ����*/
	char   product_code[4+1];  /*��Ʒ���*/
		/*��Ʒ���*/
	char   quota_code[60+1];  /*��ȱ��*/
		/*��ȱ��*/
	char   loan_code[60+1];  /*������*/
		/*������*/
	char   term_no[20+1];  /*���ڵ���*/
		/*���ڵ���*/
	int   repay_order;  /*��������*/
		/*��������*/
	char   prin_end_date[10+1];  /*��������*/
		/*��������YYYYMMDD*/
	double   prin_amt;  /*����*/
		/*���� ����Ӧ�ó����ı�������*/
	char   int_end_date[10+1];  /*��Ϣ������*/
		/*��Ϣ������YYYYMMDD*/
	double   int_amt;  /*��Ϣ*/
		/*��Ϣ ���ڣ���ֹ��Ϣ�����գ�Ӧ����Ϣ������������Ϣ�ͷ�Ϣ*/
	int   repay_terms;  /*����������*/
		/*����������*/
	double   pnlt_amt;  /*��Ϣ*/
		/*��Ϣ*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JT_PLAN;

#define SD_DATA  ICPS_JT_PLAN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  quota_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  term_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  repay_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  prin_end_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  int_end_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  repay_terms, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_PLAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_PLAN_H__*/
