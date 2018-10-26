/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_DS_DCA_COMMISSION.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_DS_DCA_COMMISSION (F_WB27.ί����ս�ݼ����÷�̯��ϸ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_DS_DCA_COMMISSION_H__
#define __ICPS_WB_DS_DCA_COMMISSION_H__
typedef struct TDB_ICPS_WB_DS_DCA_COMMISSION
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	double   out_amt;  /*ί����*/
		/*ί����*/
	double   out_prin;  /*ί�Ȿ��*/
		/*ί�Ȿ��*/
	double   out_interest;  /*ί����Ϣ*/
		/*ί����Ϣ*/
	double   out_penatly;  /*ί�ⷣϢ*/
		/*ί�ⷣϢ*/
	int   out_due_days;  /*ί����������*/
		/*ί����������*/
	char   out_age_cd[6+1];  /*ί������ʱ��*/
		/*ί������ʱ��*/
	double   repay_amt;  /*������*/
		/*������*/
	double   commision_ratio;  /*ί�����*/
		/*ί�����*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	double   bank_proportion;  /*���ű���*/
		/*���ű���*/
	double   out_expense;  /*ί�����*/
		/*ί�����*/
	char   name[80+1];  /*����*/
		/*����*/
	char   logical_card_no[19+1];  /*����*/
		/*����*/
	char   cust_id[20+1];  /*�ͻ���*/
		/*�ͻ���*/
	char   acct_no[20+1];  /*�˻���*/
		/*�˻���*/
	char   loan_receipt_nbr[20+1];  /*��ݺ�*/
		/*��ݺ�*/
	char   bn[20+1];  /*���к�*/
		/*���к�*/
	char   partition_date[10+1];  /*��������*/
		/*��������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_DS_DCA_COMMISSION;

#define SD_DATA  ICPS_WB_DS_DCA_COMMISSION
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_prin, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_interest, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_penatly, 2),\
	APP_DEFSDMEMBER(T_LONG,  out_due_days, 0),\
	APP_DEFSDMEMBER(T_STRING,  out_age_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  commision_ratio, 2),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_expense, 2),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bn, 0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_DCA_COMMISSION)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_DCA_COMMISSION_H__*/
