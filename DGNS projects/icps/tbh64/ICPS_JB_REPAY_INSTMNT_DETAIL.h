/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_REPAY_INSTMNT_DETAIL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_REPAY_INSTMNT_DETAIL (F_JB6.������ڣ���ϸ�ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_REPAY_INSTMNT_DETAIL_H__
#define __ICPS_JB_REPAY_INSTMNT_DETAIL_H__
typedef struct TDB_ICPS_JB_REPAY_INSTMNT_DETAIL
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   contract_no[32+1];  /*����ƽ̨�����ͬ��*/
		/*����ƽ̨�����ͬ��*/
	char   repay_seq_no[64+1];  /*������ˮ��*/
		/*������ˮ��*/
	int   term_no;  /*�ڴκ�*/
		/*�ڴκ�*/
	char   repay_amt_type[8+1];  /*����������*/
		/*���������� 01-���ڻ��� 02-��ǰ���� 03-���ڻ���*/
	char   repay_date[8+1];  /*��������*/
		/*�������� YYYYMMDD*/
	double   curr_prin_bal;  /*���λ���ǰ��Ӧ��δ�ձ���*/
		/*���λ���ǰ��Ӧ��δ�ձ���*/
	double   curr_int_bal;  /*���λ���ǰ��Ӧ��δ����Ϣ*/
		/*���λ���ǰ��Ӧ��δ����Ϣ*/
	double   curr_ovd_prin_pnlt_bal;  /*���λ���ǰ��Ӧ��δ�����ڱ���Ϣ*/
		/*���λ���ǰ��Ӧ��δ�����ڱ���Ϣ*/
	double   curr_ovd_int_pnlt_bal;  /*���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ*/
		/*���λ���ǰ��Ӧ��δ��������Ϣ��Ϣ*/
	double   repay_amt;  /*����ʵ���ܽ��*/
		/*����ʵ���ܽ��*/
	double   paid_prin_amt;  /*����ʵ��������*/
		/*����ʵ��������*/
	double   paid_int_amt;  /*����ʵ����Ϣ���*/
		/*����ʵ����Ϣ���*/
	double   paid_ovd_prin_pnlt_amt;  /*����ʵ�����ڱ���Ϣ���*/
		/*����ʵ�����ڱ���Ϣ���*/
	double   paid_ovd_int_pnlt_amt;  /*����ʵ��������Ϣ��Ϣ���*/
		/*����ʵ��������Ϣ��Ϣ���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_REPAY_INSTMNT_DETAIL;

#define SD_DATA  ICPS_JB_REPAY_INSTMNT_DETAIL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  contract_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_seq_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  term_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_amt_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  repay_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_prin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_int_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_prin_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_ovd_int_pnlt_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  repay_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_REPAY_INSTMNT_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_REPAY_INSTMNT_DETAIL_H__*/
