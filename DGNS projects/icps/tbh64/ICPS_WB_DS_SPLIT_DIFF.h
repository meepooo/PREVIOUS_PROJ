/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_DS_SPLIT_DIFF.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_DS_SPLIT_DIFF (F_WB26.����β�������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_DS_SPLIT_DIFF_H__
#define __ICPS_WB_DS_SPLIT_DIFF_H__
typedef struct TDB_ICPS_WB_DS_SPLIT_DIFF
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   partition_date[8+1];  /*��������*/
		/*��������*/
	char   error_type[40+1];  /*�쳣����*/
		/*�쳣����*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	char   bank_no[10+1];  /*���б��*/
		/*���б��*/
	char   busi_serial[40+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   trans_type[10+1];  /*��������*/
		/*��������*/
	char   name[80+1];  /*����*/
		/*����*/
	char   logical_card_no[19+1];  /*�߼�����*/
		/*�߼�����*/
	double   bf_amt;  /*������������*/
		/*������������*/
	double   account_amt;  /*CNC���˽��*/
		/*CNC���˽��*/
	double   error_amt;  /*Ӧ�������*/
		/*Ӧ�������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_DS_SPLIT_DIFF;

#define SD_DATA  ICPS_WB_DS_SPLIT_DIFF
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  error_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bf_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  account_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  error_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_SPLIT_DIFF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_SPLIT_DIFF_H__*/
