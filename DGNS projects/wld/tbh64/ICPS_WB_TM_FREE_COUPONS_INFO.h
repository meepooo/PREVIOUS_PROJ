/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_FREE_COUPONS_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_FREE_COUPONS_INFO (F_WB25.��Ϣ����Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_FREE_COUPONS_INFO_H__
#define __ICPS_WB_TM_FREE_COUPONS_INFO_H__
typedef struct TDB_ICPS_WB_TM_FREE_COUPONS_INFO
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   list_no[21+1];  /*�ʸ���*/
		/*�ʸ���*/
	char   act_no[11+1];  /*����*/
		/*����*/
	char   equity_no[8+1];  /*Ȩ����*/
		/*Ȩ����*/
	char   equity_type[10+1];  /*Ȩ������*/
		/*Ȩ������*/
	long   equity_value;  /*Ȩ��ֵ*/
		/*Ȩ��ֵ*/
	char   loan_receipt_nbr[20+1];  /*��ݺ�*/
		/*��ݺ�*/
	char   card_no[19+1];  /*���ʿ���*/
		/*���ʿ���*/
	char   ref_nbr[23+1];  /*���ײο�*/
		/*���ײο�*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	char   bank_no[10+1];  /*���б��*/
		/*���б��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_FREE_COUPONS_INFO;

#define SD_DATA  ICPS_WB_TM_FREE_COUPONS_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  list_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  act_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  equity_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  equity_type, 0),\
	APP_DEFSDMEMBER(T_LONG,  equity_value, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_FREE_COUPONS_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_FREE_COUPONS_INFO_H__*/
