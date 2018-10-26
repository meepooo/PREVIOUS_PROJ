/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_LOAN_VMS.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_LOAN_VMS (F_WB24.�����˰�ӹ���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_LOAN_VMS_H__
#define __ICPS_WB_TM_LOAN_VMS_H__
typedef struct TDB_ICPS_WB_TM_LOAN_VMS
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   id[20+1];  /*��˰���ID*/
		/*��˰���ID*/
	char   org[12+1];  /*������*/
		/*������*/
	char   card_no[19+1];  /*���ʿ���*/
		/*���ʿ���*/
	char   ref_nbr[23+1];  /*���ײο���*/
		/*���ײο���*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	char   bank_no[10+1];  /*���б��*/
		/*���б��*/
	char   product_cd[6+1];  /*��Ʒ��*/
		/*��Ʒ��*/
	double   biz_tax_interes;  /*Ӫҵ˰�µ�Ӧ�ƺ�Ӧ��Ϣ*/
		/*Ӫҵ˰�µ�Ӧ�ƺ�Ӧ��Ϣ*/
	double   vat_int_bal;  /*90���ڵ�Ӧ��˰Ϣ���*/
		/*90���ڵ�Ӧ��˰Ϣ���*/
	double   norevoke_vat_int_bal;  /*������㷨��Ӧ��˰Ϣ����90����+90���⻹��ǲ��֣�*/
		/*������㷨��Ӧ��˰Ϣ����90����+90���⻹��ǲ��֣�*/
	double   vat_tax;  /*������ֵ˰*/
		/*������ֵ˰*/
	int   loan_int_term;  /*����������*/
		/*����������*/
	char   last_modified_time[14+1];  /*�ϴ��޸�ʱ��*/
		/*�ϴ��޸�ʱ��*/
	char   paid_out_date[14+1];  /*��������*/
		/*��������*/
	char   age_no[1+1];  /*����*/
		/*����*/
	char   batch_date[14+1];  /*��������*/
		/*��������*/
	int   lpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_LOAN_VMS;

#define SD_DATA  ICPS_WB_TM_LOAN_VMS
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  id, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  biz_tax_interes, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  vat_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  norevoke_vat_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  vat_tax, 2),\
	APP_DEFSDMEMBER(T_LONG,  loan_int_term, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  age_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  batch_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  lpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_LOAN_VMS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_LOAN_VMS_H__*/
