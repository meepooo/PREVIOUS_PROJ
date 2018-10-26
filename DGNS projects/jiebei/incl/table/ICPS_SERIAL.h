/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_SERIAL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_SERIAL (1.������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_SERIAL_H__
#define __ICPS_SERIAL_H__
typedef struct TDB_ICPS_SERIAL
{
	char   plt_date[8+1];  /*ƽ̨����*/
		/*ƽ̨����YYYYMMDD*/
	char   plt_time[6+1];  /*ƽ̨ʱ��*/
		/*ƽ̨ʱ��HHMMSS*/
	char   plt_serial[16+1];  /*ƽ̨��ˮ��*/
		/*ƽ̨��ˮ��*/
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	char   busi_no[16+1];  /*ҵ����*/
		/*ҵ���� jiebei-���� jintiao-���� wbank-΢����*/
	char   channel[16+1];  /*��������*/
		/*�������� 311-���� 312-�������� 313-΢����*/
	char   local_id[32+1];  /*���л�����ʶ*/
		/*���л�����ʶ*/
	char   trans_code[8+1];  /*ƽ̨���״���*/
		/*ƽ̨���״���*/
	char   send_recv_flag[1+1];  /*�����˱�־*/
		/*�����˱�־ 0-���� 1-����*/
	char   apply_no[64+1];  /*���뵥��*/
		/*���뵥��*/
	char   version[8+1];  /*�汾��*/
		/*�汾�� �ӿڰ汾*/
	char   send_time_zone[32+1];  /*���ͷ�����ʱ��*/
		/*���ͷ�����ʱ�� UTC+8*/
	char   send_dttm[16+1];  /*���ķ���ʱ��*/
		/*���ķ���ʱ�� YYYYMMDDHHMMSS*/
	char   msg_id[64+1];  /*�����ı�ʾ��*/
		/*�����ı�ʾ��*/
	char   third_id[32+1];  /*������������ʶ*/
		/*������������ʶ*/
	char   third_trans_code[64+1];  /*���������״���*/
		/*���������״���*/
	char   third_respcode[16+1];  /*��������Ӧ��*/
		/*��������Ӧ��*/
	char   third_respmsg[255+1];  /*��������Ӧ��Ϣ*/
		/*��������Ӧ��Ϣ*/
	char   third_trans_status[1+1];  /*����������״̬*/
		/*����������״̬*/
	char   retry[1+1];  /*�Ƿ���Ҫ���Ա��*/
		/*�Ƿ���Ҫ���Ա�� Y-��Ҫ N-����Ҫ*/
	char   send_host_serial[64+1];  /*����������ˮ��*/
		/*����������ˮ��*/
	char   send_host_date[8+1];  /*������������*/
		/*������������*/
	char   host_serial[64+1];  /*������ˮ��*/
		/*������ˮ��*/
	char   host_date[8+1];  /*��������*/
		/*��������*/
	char   host_trans_code[16+1];  /*�������״���*/
		/*�������״���*/
	char   host_respcode[16+1];  /*������Ӧ��*/
		/*������Ӧ��*/
	char   host_respmsg[250+1];  /*������Ӧ��Ϣ*/
		/*������Ӧ��Ϣ*/
	char   host_status[2+1];  /*��������״̬*/
		/*��������״̬*/
	char   in_channel_date[64+1];  /*������������*/
		/*������������*/
	char   in_channel_serial[8+1];  /*����������ˮ��*/
		/*����������ˮ��*/
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
	char   grant_branch[16+1];  /*��Ȩ����*/
		/*��Ȩ����*/
	char   grant_teller[16+1];  /*��Ȩ��Ա*/
		/*��Ȩ��Ա*/
	char   extend_param1[10+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/
	char   extend_param4[60+1];  /*��չ4*/
		/*��չ4*/
	char   extend_param5[250+1];  /*��չ5*/
		/*��չ5*/

}ICPS_SERIAL;

#define SD_DATA  ICPS_SERIAL
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  channel, 0),\
	APP_DEFSDMEMBER(T_STRING,  local_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_recv_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  version, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_time_zone, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_dttm, 0),\
	APP_DEFSDMEMBER(T_STRING,  msg_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_trans_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  retry, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  send_host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_trans_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  in_channel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  in_channel_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  respcode, 0),\
	APP_DEFSDMEMBER(T_STRING,  respmsg, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  teller, 0),\
	APP_DEFSDMEMBER(T_STRING,  grant_branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  grant_teller, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param4, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param5, 0)


	APP_DECLAREFIELDS(SD_ICPS_SERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_SERIAL_H__*/
