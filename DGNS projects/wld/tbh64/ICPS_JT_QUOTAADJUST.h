/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JT_QUOTAADJUST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JT_QUOTAADJUST (F_JT4.������Ϣ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JT_QUOTAADJUST_H__
#define __ICPS_JT_QUOTAADJUST_H__
typedef struct TDB_ICPS_JT_QUOTAADJUST
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������YYYYMMDD*/
	int   file_order;  /*�ļ����*/
		/**/
	char   customer_code[60+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   product_code[4+1];  /*��Ʒ���*/
		/*��Ʒ���*/
	char   quota_code[60+1];  /*��ȱ��*/
		/*��ȱ��*/
	char   adjust_type[2+1];  /*��������*/
		/*����*/
	char   adjust_mode[2+1];  /*���ʽ*/
		/*ѭ����ȱ�־*/
	double   adjust_quota;  /*������*/
		/*������Ч��ʼ����*/
	double   before_adjust_quota;  /*����ǰ���Ŷ��*/
		/*���ŵ�����*/
	double   after_adjust_quota;  /*��������Ŷ��*/
		/*���Ŷ��*/
	char   adjust_cal_date[8+1];  /*������������*/
		/*��������*/
	char   adjust_effective_date[8+1];  /*��������Ч��*/
		/*δ�������Ŷ��*/
	char   adjust_serial[60+1];  /*������ˮ��*/
		/*�Ƿ���ʱ���*/
	char   error_type[1+1];  /*�������*/
		/*����״̬*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JT_QUOTAADJUST;

#define SD_DATA  ICPS_JT_QUOTAADJUST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  customer_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  quota_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  adjust_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  adjust_mode, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  adjust_quota, 8),\
	APP_DEFSDMEMBER(T_DOUBLE,  before_adjust_quota, 8),\
	APP_DEFSDMEMBER(T_DOUBLE,  after_adjust_quota, 8),\
	APP_DEFSDMEMBER(T_STRING,  adjust_cal_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  adjust_effective_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  adjust_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  error_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_QUOTAADJUST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_QUOTAADJUST_H__*/
