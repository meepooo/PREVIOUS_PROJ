/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JT_CUS.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JT_CUS (F_JT2.�ͻ���Ϣ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JT_CUS_H__
#define __ICPS_JT_CUS_H__
typedef struct TDB_ICPS_JT_CUS
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������YYYYMMDD*/
	int   file_order;  /*�ļ����*/
		/**/
	char   customer_code[60+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   customer_name[250+1];  /*�ͻ�����*/
		/*�ͻ�����*/
	char   gender[1+1];  /*�ͻ��Ա�*/
		/*�ͻ��Ա�*/
	char   brith_date[8+1];  /*��������*/
		/*��������YYYYMMDD*/
	char   resident_flag[1+1];  /*�����־*/
		/*�����־*/
	char   customer_status[1+1];  /*�ͻ�״̬*/
		/*�ͻ�״̬*/
	char   border_in_out_flag[1+1];  /*���ھ����־*/
		/*���ھ����־*/
	char   id_type[5+1];  /*֤������*/
		/*֤������*/
	char   id_num[60+1];  /*֤������*/
		/*֤������*/
	char   mobile_no[60+1];  /*�ֻ�����*/
		/*�ֻ�����*/
	char   addr[250+1];  /*ͨѶ��ַ*/
		/*ͨѶ��ַ*/
	char   bank_name[100+1];  /*�����п�����*/
		/*�����п�����*/
	char   bank_acct[60+1];  /*�����п�����*/
		/*�����п�����*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JT_CUS;

#define SD_DATA  ICPS_JT_CUS
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  brith_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  resident_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  border_in_out_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_CUS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_CUS_H__*/
