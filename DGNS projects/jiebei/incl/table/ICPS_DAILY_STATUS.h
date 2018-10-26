/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_DAILY_STATUS.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_DAILY_STATUS (7.����״̬��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_DAILY_STATUS_H__
#define __ICPS_DAILY_STATUS_H__
typedef struct TDB_ICPS_DAILY_STATUS
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	char   busi_no[16+1];  /*ҵ����*/
		/*ҵ���� jiebei-���� jintiao-���� wbank-΢����*/
	char   file_step[2+1];  /*�ļ�����*/
		/*�ļ����� 00-��ȡ�� 01-��ȡ�ɹ� 02-���ֻ�ȡ�ɹ� 03-��ȡʧ�� 04-����� 05-���ɹ� 06-�������ɹ� 07-���ʧ�� 99-��ʼ*/
	char   third_total_check_status[1+1];  /*������������״̬*/
		/*������������״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   third_detail_check_status[1+1];  /*��������ϸ����״̬*/
		/*��������ϸ����״̬  0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   host_total_check_status[1+1];  /*���Ķ�����״̬*/
		/*���Ķ�����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   host_detail_check_status[1+1];  /*������ϸ����״̬*/
		/*������ϸ����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   third_pre_total_check_status[1+1];  /*������Ԥ������״̬*/
		/*������Ԥ������״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   third_pre_detail_check_status[1+1];  /*������Ԥ��ϸ����״̬*/
		/*������Ԥ��ϸ����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   host_pre_total_check_status[1+1];  /*����Ԥ������״̬*/
		/*����Ԥ������״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   host_pre_detail_check_status[1+1];  /*����Ԥ��ϸ����״̬*/
		/*����Ԥ��ϸ����״̬ 0 δ���� 1 ����ƽ 2 ���˲�ƽ 3���˳��� 4����ƽ��β�� 9 ������*/
	char   clear_status[1+1];  /*����״̬*/
		/*����״̬ 0 δ����1 ������ 2 �������  6 ����״̬δ֪ 9 ������*/
	char   plt_date[8+1];  /*ƽ̨����*/
		/*ƽ̨����YYYYMMDD*/
	char   plt_serial[16+1];  /*ƽ̨��ˮ��*/
		/*ƽ̨��ˮ��*/
	char   send_host_serial[64+1];  /*����������ˮ��*/
		/*����������ˮ��*/
	char   send_host_date[8+1];  /*������������*/
		/*������������*/
	char   host_serial[64+1];  /*������ˮ��*/
		/*������ˮ��*/
	char   host_date[8+1];  /*��������*/
		/*��������*/
	char   respcode[8+1];  /*������Ӧ��*/
		/*������Ӧ��*/
	char   respmsg[250+1];  /*������Ӧ��Ϣ*/
		/*������Ӧ��Ϣ*/
	char   trans_status[1+1];  /*����״̬*/
		/*����״̬*/
	char   branch[16+1];  /*���׻���*/
		/*���׻���*/
	char   teller[16+1];  /*���׹�Ա*/
		/*���׹�Ա*/
	char   extend_param1[10+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_DAILY_STATUS;

#define SD_DATA  ICPS_DAILY_STATUS
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_step, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_pre_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_pre_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_pre_total_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_pre_detail_check_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  teller, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_DAILY_STATUS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_DAILY_STATUS_H__*/
