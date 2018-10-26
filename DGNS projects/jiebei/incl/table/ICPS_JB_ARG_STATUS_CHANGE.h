/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_ARG_STATUS_CHANGE.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_ARG_STATUS_CHANGE (F_JB12.�����̬ת����ˮ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_ARG_STATUS_CHANGE_H__
#define __ICPS_JB_ARG_STATUS_CHANGE_H__
typedef struct TDB_ICPS_JB_ARG_STATUS_CHANGE
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   contract_no[32+1];  /*����ƽ̨�����ͬ��*/
		/*����ƽ̨�����ͬ��*/
	char   settle_date[8+1];  /*�������*/
		/*�������*/
	char   status_seq_no[64+1];  /*״̬�仯��ˮ��*/
		/*״̬�仯��ˮ��*/
	char   event_code[16+1];  /*�¼���*/
		/*�¼��룬ת����11020007��ת��Ӧ��11020014��תӦ��11020015*/
	char   before_status[10+1];  /*���ת��ǰ״̬*/
		/*���ת��ǰ״̬������Ӧ�ƣ� ��ȡֵΪNORMAL��Ӧ�Ʊ��ȡֵ��0��1��*/
	char   after_status[10+1];  /*���ת�ƺ�״̬*/
		/*���ת�ƺ�״̬������Ӧ�ƣ���ȡֵΪOVD��Ӧ�Ʊ��ȡֵΪ0��1��*/
	double   prin_amt;  /*��������*/
		/*��������*/
	double   int_amt;  /*��Ϣ������*/
		/*��Ϣ������*/
	double   ovd_prin_pnlt_amt;  /*���ڱ���Ϣ������*/
		/*���ڱ���Ϣ������*/
	double   ovd_int_pnlt_amt;  /*������Ϣ��Ϣ������*/
		/*������Ϣ��Ϣ������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_ARG_STATUS_CHANGE;

#define SD_DATA  ICPS_JB_ARG_STATUS_CHANGE
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  settle_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  status_seq_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  event_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  before_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  after_status, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_ARG_STATUS_CHANGE)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_ARG_STATUS_CHANGE_H__*/
