/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_IM_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_IM_INFO (F_WB16.�ͻ���ʱͨѶ��Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_IM_INFO_H__
#define __ICPS_WB_TM_IM_INFO_H__
typedef struct TDB_ICPS_WB_TM_IM_INFO
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   seq_no[20+1];  /*���*/
		/*���*/
	char   org[12+1];  /*������*/
		/*������*/
	char   product_code[6+1];  /*��Ʒ����*/
		/*��Ʒ����*/
	char   cust_id[20+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   app_type[3+1];  /*Ӧ������*/
		/*Ӧ������*/
	char   app_acct_no[40+1];  /*Ӧ���˺�*/
		/*Ӧ���˺�*/
	char   user_field282[255+1];  /*�����ֶ�282*/
		/*�����ֶ�282*/
	char   created_datetime[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   update_time[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	char   last_update_biz_date[14+1];  /*�ϴ���������ҵ������*/
		/*�ϴ���������ҵ������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_IM_INFO;

#define SD_DATA  ICPS_WB_TM_IM_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  seq_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field282, 0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  update_time, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_update_biz_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_IM_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_IM_INFO_H__*/
