/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_ZM_CREDIT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_ZM_CREDIT (4.֥��������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_ZM_CREDIT_H__
#define __ICPS_ZM_CREDIT_H__
typedef struct TDB_ICPS_ZM_CREDIT
{
	char   apply_no[64+1];  /*���뵥��*/
		/*���뵥��*/
	char   plt_date[8+1];  /*ƽ̨����*/
		/*ƽ̨����*/
	char   plt_serial[16+1];  /*ƽ̨��ˮ��*/
		/*ƽ̨��ˮ��*/
	char   id_type[2+1];  /*֤������*/
		/*֤������*/
	char   id_num[32+1];  /*֤������*/
		/*֤������*/
	char   company_name[255+1];  /*���ڹ�˾*/
		/*���ڹ�˾*/
	char   occupation[64+1];  /*ְҵ����*/
		/*ְҵ����*/
	char   have_car_flag[1+1];  /*�Ƿ��г�*/
		/*�Ƿ��г�*/
	char   have_house_flag[1+1];  /*�Ƿ��з�*/
		/*�Ƿ��з�*/
	int   auth_fin_last_1m_cnt;  /*���һ����������ѯ���ڻ�����*/
		/*���һ����������ѯ���ڻ�����*/
	int   auth_fin_last_3m_cnt;  /*���������������ѯ���ڻ�����*/
		/*���������������ѯ���ڻ�����*/
	int   auth_fin_last_6m_cnt;  /*���������������ѯ���ڻ�����*/
		/*���������������ѯ���ڻ�����*/
	int   ovd_order_cnt_6m;  /*��������������ܱ���*/
		/*��������������ܱ���*/
	double   ovd_order_amt_6m;  /*��������������ܽ��*/
		/*��������������ܽ��*/
	int   mobile_fixed_days;  /*�ֻ����ȶ�����*/
		/*�ֻ����ȶ�����*/
	int   adr_stability_days;  /*��ַ�ȶ�����*/
		/*��ַ�ȶ�����*/
	double   last_6m_avg_asset_total;  /*��������������ʲ��վ�ֵ*/
		/*��������������ʲ��վ�ֵ*/
	double   tot_pay_amt_6m;  /*���������֧���ܽ��*/
		/*���������֧���ܽ��*/
	char   xfdc_index[64+1];  /*���ѵ���*/
		/*���ѵ���*/
	int   positive_biz_cnt_1y;  /*���һ����Լ������*/
		/*���һ����Լ������*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_ZM_CREDIT;

#define SD_DATA  ICPS_ZM_CREDIT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  apply_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  company_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  occupation, 0),\
	APP_DEFSDMEMBER(T_STRING,  have_car_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  have_house_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  auth_fin_last_1m_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  auth_fin_last_3m_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  auth_fin_last_6m_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  ovd_order_cnt_6m, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ovd_order_amt_6m, 2),\
	APP_DEFSDMEMBER(T_LONG,  mobile_fixed_days, 0),\
	APP_DEFSDMEMBER(T_LONG,  adr_stability_days, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_6m_avg_asset_total, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  tot_pay_amt_6m, 2),\
	APP_DEFSDMEMBER(T_STRING,  xfdc_index, 0),\
	APP_DEFSDMEMBER(T_LONG,  positive_biz_cnt_1y, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_ZM_CREDIT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_ZM_CREDIT_H__*/
