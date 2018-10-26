/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JT_FUND_DETAIL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JT_FUND_DETAIL (F_JT8.��ҵ�ʽ���ˮ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JT_FUND_DETAIL_H__
#define __ICPS_JT_FUND_DETAIL_H__
typedef struct TDB_ICPS_JT_FUND_DETAIL
{
	char   trans_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	char   file_type[8+1];  /*�ļ�����*/
		/*�ļ�����*/
	int   file_order;  /*�ļ����*/
		/**/
	char   trans_time[6+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   sys_date[8+1];  /*ϵͳ����*/
		/*ϵͳ����*/
	char   acct_direction[1+1];  /*��֧����*/
		/*��֧����*/
	double   trans_amt;  /*���׽��*/
		/*���׽��*/
	char   summary_code[10+1];  /*ժҪ����*/
		/*ժҪ����*/
	char   summary[250+1];  /*����ժҪ*/
		/*����ժҪ*/
	double   acct_bal;  /*�˻����*/
		/*�˻����*/
	char   currency[3+1];  /*���Һ�*/
		/*���Һ�*/
	char   peer_acct[36+1];  /*�Է��˻�*/
		/*�Է��˻�*/
	char   peer_acct_name[60+1];  /*�Է��˻�����*/
		/*�Է��˻�����*/
	char   remarks[250+1];  /*��ע*/
		/*��ע*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JT_FUND_DETAIL;

#define SD_DATA  ICPS_JT_FUND_DETAIL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  trans_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_type, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_direction, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  summary_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  summary, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  acct_bal, 2),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  peer_acct, 0),\
	APP_DEFSDMEMBER(T_STRING,  peer_acct_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  remarks, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_FUND_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_FUND_DETAIL_H__*/
