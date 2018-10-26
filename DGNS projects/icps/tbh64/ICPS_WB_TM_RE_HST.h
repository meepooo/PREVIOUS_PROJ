/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_RE_HST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_RE_HST (F_WB18.�������嵥����ʷ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_RE_HST_H__
#define __ICPS_WB_TM_RE_HST_H__
typedef struct TDB_ICPS_WB_TM_RE_HST
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   busi_serial[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   sys_trans_id[32+1];  /*ϵͳ������ˮ��*/
		/*ϵͳ������ˮ��*/
	char   loan_receipt_nbr[20+1];  /*��ݺ�*/
		/*��ݺ�*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	char   card_no[19+1];  /*����*/
		/*����*/
	char   transfer_in_date[14+1];  /*��������*/
		/*��������*/
	char   last_modified_datetime[14+1];  /*ʱ���*/
		/*ʱ���*/
	char   move_date[14+1];  /*ת������(��������ȡ��)*/
		/*ת������(��������ȡ��)*/
	int   part_month;  /*�����õ��·�*/
		/*�����õ��·�*/
	double   pay_amt;  /*������*/
		/*������*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_RE_HST;

#define SD_DATA  ICPS_WB_TM_RE_HST
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  sys_trans_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  transfer_in_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  move_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  part_month, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  pay_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_RE_HST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_RE_HST_H__*/
