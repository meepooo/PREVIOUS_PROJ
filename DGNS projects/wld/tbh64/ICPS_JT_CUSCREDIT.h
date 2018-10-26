/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JT_CUSCREDIT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JT_CUSCREDIT (F_JT3.���Ŷ����Ϣ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JT_CUSCREDIT_H__
#define __ICPS_JT_CUSCREDIT_H__
typedef struct TDB_ICPS_JT_CUSCREDIT
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������YYYYMMDD*/
	int   file_order;  /*�ļ����*/
		/**/
	char   customer_code[60+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   product_code[4+1];  /*��Ʒ���*/
		/*��Ʒ���*/
	char   quota_code[60+1];  /*��ȱ��*/
		/*��ȱ��*/
	char   currency[3+1];  /*����*/
		/*����*/
	char   cycle_quota_flag[1+1];  /*ѭ����ȱ�־*/
		/*ѭ����ȱ�־*/
	char   start_date[8+1];  /*������Ч��ʼ����*/
		/*������Ч��ʼ����*/
	char   end_date[8+1];  /*���ŵ�����*/
		/*���ŵ�����*/
	double   quota;  /*���Ŷ��*/
		/*���Ŷ��*/
	int   limit;  /*��������*/
		/*��������*/
	double   nouse_quota;  /*δ�������Ŷ��*/
		/*δ�������Ŷ��*/
	char   tmp_quota_flag[4+1];  /*�Ƿ���ʱ���*/
		/*�Ƿ���ʱ���*/
	char   auth_status[3+1];  /*����״̬*/
		/*����״̬*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JT_CUSCREDIT;

#define SD_DATA  ICPS_JT_CUSCREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  quota_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  cycle_quota_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  start_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  quota, 2),\
	APP_DEFSDMEMBER(T_LONG,  limit, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  nouse_quota, 2),\
	APP_DEFSDMEMBER(T_STRING,  tmp_quota_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  auth_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_CUSCREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_CUSCREDIT_H__*/
