/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_REPAY_PLAN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_REPAY_PLAN (F_JB4.�ſ���ڣ���ϸ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_REPAY_PLAN_H__
#define __ICPS_JB_REPAY_PLAN_H__
typedef struct TDB_ICPS_JB_REPAY_PLAN
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   contract_no[64+1];  /*����ƽ̨�����Լ��*/
		/*����ƽ̨�����Լ��*/
	int   term_no;  /*�ڴκ�*/
		/*�ڴκ�*/
	char   start_date[8+1];  /*���ڿ�ʼ����*/
		/*���ڿ�ʼ���� YYYYMMDD*/
	char   end_date[8+1];  /*���ڽ�������*/
		/*���ڽ������� YYYYMMDD*/
	double   prin_amt;  /*������*/
		/*������*/
	double   int_amt;  /*��ʼ��Ϣ������*/
		/*��ʼ��Ϣ������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_REPAY_PLAN;

#define SD_DATA  ICPS_JB_REPAY_PLAN
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  term_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  start_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_REPAY_PLAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_REPAY_PLAN_H__*/
