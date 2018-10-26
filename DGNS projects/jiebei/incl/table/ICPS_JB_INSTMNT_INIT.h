/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_INSTMNT_INIT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_INSTMNT_INIT (F_JB10.�ճ������ڣ���Ϣ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_INSTMNT_INIT_H__
#define __ICPS_JB_INSTMNT_INIT_H__
typedef struct TDB_ICPS_JB_INSTMNT_INIT
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   contract_no[32+1];  /*����ƽ̨�����ͬ��*/
		/*����ƽ̨�����ͬ��*/
	char   settle_date[8+1];  /*�������*/
		/*������� YYYYMMDD*/
	int   term_no;  /*�ڴκ�*/
		/*�ڴκ�*/
	char   start_date[8+1];  /*���ڿ�ʼ����*/
		/*���ڿ�ʼ���� YYYYMMDD*/
	char   end_date[8+1];  /*���ڽ�������*/
		/*���ڽ������ڣ����ڻ����գ� YYYYMMDD*/
	char   status[10+1];  /*����״̬*/
		/*����״̬������NORMAL,����OVD,����CLEAR */
	char   clear_date[8+1];  /*��������*/
		/*�������� YYYYMMDD*/
	char   prin_ovd_date[8+1];  /*����ת��������*/
		/*����ת�������� YYYYMMDD*/
	char   int_ovd_date[8+1];  /*��Ϣת��������*/
		/*��Ϣת�������� YYYYMMDD*/
	int   prin_ovd_days;  /*������������*/
		/*������������*/
	int   int_ovd_days;  /*��Ϣ��������*/
		/*��Ϣ��������*/
	double   prin_bal;  /*�������*/
		/*�������*/
	double   int_bal;  /*��Ϣ���*/
		/*��Ϣ���*/
	double   ovd_prin_pnlt_bal;  /*���ڱ���Ϣ���*/
		/*���ڱ���Ϣ���*/
	double   ovd_int_pnlt_bal;  /*������Ϣ��Ϣ���*/
		/*������Ϣ��Ϣ���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_INSTMNT_INIT;

#define SD_DATA  ICPS_JB_INSTMNT_INIT
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  settle_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  term_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  start_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  end_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  status, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  prin_ovd_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  int_ovd_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  prin_ovd_days, 0),\
	APP_DEFSDMEMBER(T_LONG,  int_ovd_days, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_prin_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_int_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_INSTMNT_INIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_INSTMNT_INIT_H__*/
