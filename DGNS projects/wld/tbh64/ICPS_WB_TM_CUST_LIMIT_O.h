/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_CUST_LIMIT_O.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_CUST_LIMIT_O (F_WB14.�Զ�������Ϣ��-��Ȩ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_CUST_LIMIT_O_H__
#define __ICPS_WB_TM_CUST_LIMIT_O_H__
typedef struct TDB_ICPS_WB_TM_CUST_LIMIT_O
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   cust_limit_id[20+1];  /*�ͻ����ID*/
		/*�ͻ����ID*/
	char   limit_category[20+1];  /*�������*/
		/*�������*/
	char   limit_type[1+1];  /*�������*/
		/*�������*/
	double   credit_limit;  /*���ö��*/
		/*���ö��*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	char   last_modified_datetime[14+1];  /*�޸�ʱ��*/
		/*�޸�ʱ��*/
	char   created_datetime[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_CUST_LIMIT_O;

#define SD_DATA  ICPS_WB_TM_CUST_LIMIT_O
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_limit_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  limit_category, 0),\
	APP_DEFSDMEMBER(T_STRING,  limit_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  credit_limit, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_CUST_LIMIT_O)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_CUST_LIMIT_O_H__*/
