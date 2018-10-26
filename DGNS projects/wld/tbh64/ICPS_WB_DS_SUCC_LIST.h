/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_DS_SUCC_LIST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_DS_SUCC_LIST (F_WB29.�Ѻ�������嵥��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_DS_SUCC_LIST_H__
#define __ICPS_WB_DS_SUCC_LIST_H__
typedef struct TDB_ICPS_WB_DS_SUCC_LIST
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   writeoff_date[10+1];  /*��������*/
		/*��������*/
	char   name[200+1];  /*����*/
		/*����*/
	char   cust_id[20+1];  /*�ͻ���*/
		/*�ͻ���*/
	char   bank_no[20+1];  /*���к�*/
		/*���к�*/
	char   bank_group_id[5+1];  /*���ź�*/
		/*���ź�*/
	char   product_cd[6+1];  /*��Ʒ��*/
		/*��Ʒ��*/
	char   logical_card_no[19+1];  /*����*/
		/*����*/
	char   ref_nbr[23+1];  /*�ο���*/
		/*�ο���*/
	char   writeoff_proc_status[20+1];  /*����״̬*/
		/*����״̬*/
	double   loan_init_prin;  /*����*/
		/*����*/
	double   loan_intr_penalty;  /*��Ϣ��Ϣ*/
		/*��Ϣ��Ϣ*/
	double   bank_proportion;  /*���ű���*/
		/*���ű���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_DS_SUCC_LIST;

#define SD_DATA  ICPS_WB_DS_SUCC_LIST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  writeoff_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  writeoff_proc_status, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_intr_penalty, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_SUCC_LIST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_SUCC_LIST_H__*/
