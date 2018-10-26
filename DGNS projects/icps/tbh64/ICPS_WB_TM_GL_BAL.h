/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_GL_BAL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_GL_BAL (F_WB4.���˻�ƿ�Ŀ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_GL_BAL_H__
#define __ICPS_WB_TM_GL_BAL_H__
typedef struct TDB_ICPS_WB_TM_GL_BAL
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   subject[40+1];  /*��Ŀ*/
		/*��Ŀ*/
	char   branch_id[9+1];  /*��֧�к�*/
		/*��֧�к�*/
	double   db_bal;  /*�跽���*/
		/*�跽���*/
	double   cr_bal;  /*�������*/
		/*�������*/
	double   db_amt;  /*�跽������*/
		/*�跽������*/
	int   db_count;  /*�跽����*/
		/*�跽����*/
	double   cr_amt;  /*����������*/
		/*����������*/
	int   cr_count;  /*��������*/
		/*��������*/
	double   last_db_bal;  /*���ս跽���*/
		/*���ս跽���*/
	double   last_cr_bal;  /*���մ������*/
		/*���մ������*/
	double   last_mth_db_bal;  /*����ĩ�跽���*/
		/*����ĩ�跽���*/
	double   last_mth_cr_bal;  /*����ĩ�������*/
		/*����ĩ�������*/
	double   last_qtr_db_bal;  /*�ϼ�ĩ�跽���*/
		/*�ϼ�ĩ�跽���*/
	double   last_qtr_cr_bal;  /*�ϼ�ĩ�������*/
		/*�ϼ�ĩ�������*/
	double   last_yr_db_ba;  /*����ĩ�跽���*/
		/*����ĩ�跽���*/
	double   last_yr_cr_ba;  /*����ĩ�������*/
		/*����ĩ�������*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	char   product_cd[6+1];  /*��Ʒ���*/
		/*��Ʒ���*/
	int   bal_id;  /*˳���*/
		/*˳���*/
	char   bank_no[10+1];  /*���д���*/
		/*���д���*/
	char   bank_group_id[5+1];  /*���Ŵ���*/
		/*���Ŵ���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_GL_BAL;

#define SD_DATA  ICPS_WB_TM_GL_BAL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  subject, 0),\
	APP_DEFSDMEMBER(T_STRING,  branch_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  db_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  cr_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  db_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  db_count, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cr_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  cr_count, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_db_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_cr_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_mth_db_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_mth_cr_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_qtr_db_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_qtr_cr_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_yr_db_ba, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_yr_cr_ba, 2),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_LONG,  bal_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_GL_BAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_GL_BAL_H__*/
