/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JT_LOAN_TOTAL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JT_LOAN_TOTAL (F_JT1.���ܼ��˱�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JT_LOAN_TOTAL_H__
#define __ICPS_JT_LOAN_TOTAL_H__
typedef struct TDB_ICPS_JT_LOAN_TOTAL
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	double   encash_amt;  /*���ڴ���ſ��ʽ�*/
		/*���ڴ���ſ��ʽ�*/
	double   prin_to_ovd_prin_amt;  /*���ڴ�����������ת���ڱ���Ӧ�ƣ�*/
		/*���ڴ�����������ת���ڱ���Ӧ�ƣ�*/
	double   non_prin_to_ovd_prin_amt;  /*���ڴ�����������ת���ڱ��𣨷�Ӧ�ƣ�*/
		/*���ڴ�����������ת���ڱ��𣨷�Ӧ�ƣ�*/
	double   accrued_to_non_ovd_prin_amt;  /*���ڴ������ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�*/
		/*���ڴ������ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�*/
	double   in_int_to_ovd_int_amt;  /*���ڴ���������Ϣת������Ϣ�����ڣ�*/
		/*���ڴ���������Ϣת������Ϣ�����ڣ�*/
	double   out_int_to_ovd_int_amt;  /*���ڴ���������Ϣת������Ϣ�����⣩*/
		/*���ڴ���������Ϣת������Ϣ�����⣩*/
	double   in_to_out_ovd_int_amt;  /*���ڴ���������Ϣ�����ڣ�ת������Ϣ�����⣩*/
		/*���ڴ���������Ϣ�����ڣ�ת������Ϣ�����⣩*/
	double   in_to_out_pnlt_int_amt;  /*���ڴ��Ϣ�����ڣ�ת��Ϣ�����⣩*/
		/*���ڴ��Ϣ�����ڣ�ת��Ϣ�����⣩*/
	double   in_refund_ovd_int_amt;  /*�����˻����������������Ϣ�����ڣ�*/
		/*�����˻����������������Ϣ�����ڣ�*/
	double   paid_prin_amt;  /*ʵ���������������*/
		/*ʵ���������������*/
	double   paid_accrued_ovd_prin_amt;  /*ʵ���������ڴ����Ӧ�ƣ�*/
		/*ʵ���������ڴ����Ӧ�ƣ�*/
	double   paid_non_accrued_ovd_prin_amt;  /*ʵ���������ڴ���𣨷�Ӧ�ƣ�*/
		/*ʵ���������ڴ���𣨷�Ӧ�ƣ�*/
	double   paid_int_amt;  /*ʵ����������������Ϣ*/
		/*ʵ����������������Ϣ*/
	double   paid_in_ovd_int_amt;  /*ʵ���������ڴ�����Ϣ�����ڣ�*/
		/*ʵ���������ڴ�����Ϣ�����ڣ�*/
	double   paid_out_ovd_int_amt;  /*ʵ���������ڴ�����Ϣ�����⣩*/
		/*ʵ���������ڴ�����Ϣ�����⣩*/
	double   paid_in_pnlt_int_amt;  /*ʵ�����ڴ��Ϣ�����ڣ�*/
		/*ʵ�����ڴ��Ϣ�����ڣ�*/
	double   paid_out_pnlt_int_amt;  /*ʵ�����ڴ��Ϣ�����⣩*/
		/*ʵ�����ڴ��Ϣ�����⣩*/
	double   ahead_prin_amt;  /*��ǰ�黹���ڴ�����������*/
		/*��ǰ�黹���ڴ�����������*/
	double   ahead_int_amt;  /*��ǰ�黹���ڴ���������Ϣ*/
		/*��ǰ�黹���ڴ���������Ϣ*/
	double   refund_prin_amt;  /*�˻����ڴ����*/
		/*�˻����ڴ����*/
	double   refund_ovd_prin_amt;  /*�˻����ڴ������ڱ���Ӧ�ƣ�*/
		/*�˻����ڴ������ڱ���Ӧ�ƣ�*/
	double   refund_in_pnlt_int;  /*�˻����ڴ��Ϣ�����ڣ�*/
		/*�˻����ڴ��Ϣ�����ڣ�*/
	double   encash_amt2;  /*�г��ڴ���ſ��ʽ�*/
		/*�г��ڴ���ſ��ʽ�*/
	double   prin_to_ovd_prin_amt2;  /*�г��ڴ�����������ת���ڱ���Ӧ�ƣ�*/
		/*�г��ڴ�����������ת���ڱ���Ӧ�ƣ�*/
	double   non_prin_to_ovd_prin_amt2;  /*�г��ڴ�����������ת���ڱ��𣨷�Ӧ�ƣ�*/
		/*�г��ڴ�����������ת���ڱ��𣨷�Ӧ�ƣ�*/
	double   accrued_to_non_ovd_prin_amt2;  /*�г��ڴ������ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�*/
		/*�г��ڴ������ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�*/
	double   in_int_to_ovd_int_amt2;  /*�г��ڴ���������Ϣת������Ϣ�����ڣ�*/
		/*�г��ڴ���������Ϣת������Ϣ�����ڣ�*/
	double   out_int_to_ovd_int_amt2;  /*�г��ڴ���������Ϣת������Ϣ�����⣩*/
		/*�г��ڴ���������Ϣת������Ϣ�����⣩*/
	double   in_to_out_ovd_int_amt2;  /*�г��ڴ���������Ϣ�����ڣ�ת������Ϣ�����⣩*/
		/*�г��ڴ���������Ϣ�����ڣ�ת������Ϣ�����⣩*/
	double   in_to_out_pnlt_int_amt2;  /*�г��ڴ��Ϣ�����ڣ�ת��Ϣ�����⣩*/
		/*�г��ڴ��Ϣ�����ڣ�ת��Ϣ�����⣩*/
	double   in_refund_ovd_int_amt2;  /*�г����˻����������������Ϣ�����ڣ�*/
		/*�г����˻����������������Ϣ�����ڣ�*/
	double   paid_prin_amt2;  /*ʵ���г������������*/
		/*ʵ���г������������*/
	double   paid_accrued_ovd_prin_amt2;  /*ʵ���г������ڴ����Ӧ�ƣ�*/
		/*ʵ���г������ڴ����Ӧ�ƣ�*/
	double   paid_non_accrued_ovd_prin_amt2;  /*ʵ���г������ڴ���𣨷�Ӧ�ƣ�*/
		/*ʵ���г������ڴ���𣨷�Ӧ�ƣ�*/
	double   paid_int_amt2;  /*ʵ���г�������������Ϣ*/
		/*ʵ���г�������������Ϣ*/
	double   paid_in_ovd_int_amt2;  /*ʵ���г������ڴ�����Ϣ�����ڣ�*/
		/*ʵ���г������ڴ�����Ϣ�����ڣ�*/
	double   paid_out_ovd_int_amt2;  /*ʵ���г������ڴ�����Ϣ�����⣩*/
		/*ʵ���г������ڴ�����Ϣ�����⣩*/
	double   paid_in_pnlt_int_amt2;  /*ʵ���г��ڴ��Ϣ�����ڣ�*/
		/*ʵ���г��ڴ��Ϣ�����ڣ�*/
	double   paid_out_pnlt_int_amt2;  /*ʵ���г��ڴ��Ϣ�����⣩*/
		/*ʵ���г��ڴ��Ϣ�����⣩*/
	double   ahead_prin_amt2;  /*��ǰ�黹�г��ڴ�����������*/
		/*��ǰ�黹�г��ڴ�����������*/
	double   ahead_int_amt2;  /*��ǰ�黹�г��ڴ���������Ϣ*/
		/*��ǰ�黹�г��ڴ���������Ϣ*/
	double   refund_prin_amt2;  /*�˻��г��ڴ����*/
		/*�˻��г��ڴ����*/
	double   refund_ovd_prin_amt2;  /*�˻��г��ڴ������ڱ���Ӧ�ƣ�*/
		/*�˻��г��ڴ������ڱ���Ӧ�ƣ�*/
	double   refund_in_pnlt_int_amt2;  /*�˻��г��ڴ��Ϣ�����ڣ�*/
		/*�˻��г��ڴ��Ϣ�����ڣ�*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JT_LOAN_TOTAL;

#define SD_DATA  ICPS_JT_LOAN_TOTAL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_to_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_prin_to_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_int_to_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_int_to_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_refund_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_in_pnlt_int, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_to_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_prin_to_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_int_to_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_int_to_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_refund_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_accrued_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ahead_int_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_ovd_prin_amt2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_in_pnlt_int_amt2, 2),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JT_LOAN_TOTAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JT_LOAN_TOTAL_H__*/
