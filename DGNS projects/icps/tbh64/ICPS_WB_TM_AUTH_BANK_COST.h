/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_AUTH_BANK_COST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_AUTH_BANK_COST (F_WB2.�����ļ�����ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_AUTH_BANK_COST_H__
#define __ICPS_WB_TM_AUTH_BANK_COST_H__
typedef struct TDB_ICPS_WB_TM_AUTH_BANK_COST
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   busi_serial[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	char   bank_no[10+1];  /*���к�*/
		/*���к�*/
	char   reg_type[50+1];  /*�Ǽ�����*/
		/*�Ǽ�����*/
	double   reg_amt;  /*�Ǽǽ��*/
		/*�Ǽǽ��*/
	char   reg_status[10+1];  /*�Ǽ�״̬*/
		/*�Ǽ�״̬*/
	char   reg_sys_id[32+1];  /*������ˮ��*/
		/*������ˮ��*/
	char   reg_date[14+1];  /*��������*/
		/*��������*/
	char   reg_time[14+1];  /*��������ʱ��*/
		/*��������ʱ��*/
	char   recon_code[20+1];  /*������*/
		/*������*/
	char   ori_sys_id[32+1];  /*ԭ������ˮ��*/
		/*ԭ������ˮ��*/
	char   cust_id[20+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	int   retry;  /*���Դ���*/
		/*���Դ���*/
	char   created_datetime[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   last_modified_datetime[14+1];  /*ʱ���*/
		/*ʱ���*/
	int   user_field268;  /*�����ֶ�268*/
		/*�����ֶ�268*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_AUTH_BANK_COST;

#define SD_DATA  ICPS_WB_TM_AUTH_BANK_COST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  reg_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  reg_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  reg_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  reg_sys_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  reg_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  reg_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  recon_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  ori_sys_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_LONG,  retry, 0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field268, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_AUTH_BANK_COST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_AUTH_BANK_COST_H__*/
