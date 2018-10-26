/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_APPLY.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_APPLY (2.����������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_APPLY_H__
#define __ICPS_APPLY_H__
typedef struct TDB_ICPS_APPLY
{
	char   busi_no[16+1];  /*ҵ����*/
		/*ҵ���� jiebei-���� jintiao-���� wbank-΢����*/
	char   apply_no[64+1];  /*���뵥��*/
		/*���뵥��*/
	char   id_type[2+1];  /*֤������*/
		/*֤������*/
	char   id_num[32+1];  /*֤������*/
		/*֤������*/
	char   id_valid_end_date[8+1];  /*֤����Ч��*/
		/*֤����Ч��*/
	char   name[64+1];  /*����*/
		/*����*/
	char   mobile_no[32+1];  /*�ֻ���*/
		/*�ֻ���*/
	char   auth_flag[1+1];  /*֥����Ȩ�ɹ���ʶ*/
		/*֥����Ȩ�ɹ���ʶ Y-��Ȩ�ɹ� N-��Ȩʧ��*/
	char   has_admit_flag[1+1];  /*֮ǰ�Ƿ��ж��*/
		/*֮ǰ�Ƿ��ж�� Y-֮ǰ�ж�ȣ�N-֮ǰû�ж��*/
	char   apply_plt_date[8+1];  /*��������ƽ̨����*/
		/*��������ƽ̨����*/
	char   apply_plt_serial[16+1];  /*��������ƽ̨��ˮ��*/
		/*��������ƽ̨��ˮ��*/
	char   apply_status[1+1];  /*��������״̬*/
		/*��������״̬ 0-�ɹ� 1-ʧ�� 6-δ֪ 9-��ʼ*/
	char   credit_no[32+1];  /*���ű��*/
		/*���ű��*/
	char   info_admit_flag[1+1];  /*�����Ƿ��Ƽ�׼��*/
		/*�����Ƿ��Ƽ�׼�� Y-׼�� N-��׼��*/
	double   credit_amt;  /*�Ƽ����*/
		/*�Ƽ����*/
	double   credit_rate;  /*�Ƽ�����*/
		/*�Ƽ�����*/
	char   refuse_code[64+1];  /*�ܾ���*/
		/*�ܾ���*/
	char   refuse_reason[1024+1];  /*�ܾ�ԭ��*/
		/*�ܾ�ԭ��*/
	char   info_plt_date[8+1];  /*���г���ƽ̨����*/
		/*���г���ƽ̨����*/
	char   info_plt_serial[16+1];  /*���г���ƽ̨��ˮ��*/
		/*���г���ƽ̨��ˮ��*/
	char   info_status[1+1];  /*����״̬*/
		/*����״̬ 0-�ɹ� 1-ʧ�� 6-δ֪ 9-��ʼ*/
	char   third_access[1+1];  /*�Ƿ�ͨ������*/
		/*�Ƿ�ͨ������ Y-ͨ�� N-��ͨ��*/
	char   third_refuse_reason[1024+1];  /*������ͨ��ԭ��*/
		/*������ͨ��ԭ��*/
	double   third_amt;  /*�������*/
		/*�������*/
	double   third_rate;  /*������������*/
		/*������������*/
	char   risk_rating[1+1];  /*��������*/
		/*��������*/
	char   solvency_rating[1+1];  /*��ծ��������*/
		/*��ծ��������*/
	char   change_result_reason[1024+1];  /*��ȶ��۱��ԭ��*/
		/*��ȶ��۱��ԭ��*/
	char   ack_admit_flag[1+1];  /*���������Ƿ�׼��*/
		/*���������Ƿ�׼�� Y-׼�� N-��׼��*/
	char   ack_admit_msg[255+1];  /*׼��ԭ��*/
		/*׼��ԭ��*/
	char   ack_plt_date[8+1];  /*����ƽ̨����*/
		/*����ƽ̨����*/
	char   ack_plt_serial[16+1];  /*����ƽ̨��ˮ��*/
		/*����ƽ̨��ˮ��*/
	char   ack_status[1+1];  /*����״̬*/
		/*����״̬ 0-�ɹ� 1-ʧ�� 6-δ֪ 9-��ʼ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_APPLY;

#define SD_DATA  ICPS_APPLY
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_valid_end_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  auth_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  has_admit_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  apply_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  credit_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_admit_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  credit_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  credit_rate, 6),\
	APP_DEFSDMEMBER(T_STRING,  refuse_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  refuse_reason, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  info_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_access, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_refuse_reason, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  third_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  third_rate, 6),\
	APP_DEFSDMEMBER(T_STRING,  risk_rating, 0),\
	APP_DEFSDMEMBER(T_STRING,  solvency_rating, 0),\
	APP_DEFSDMEMBER(T_STRING,  change_result_reason, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_admit_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_admit_msg, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  ack_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_APPLY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_APPLY_H__*/
