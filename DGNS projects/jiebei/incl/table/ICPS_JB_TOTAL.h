/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_TOTAL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_TOTAL (F_JB1.���ܼ����ļ���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_TOTAL_H__
#define __ICPS_JB_TOTAL_H__
typedef struct TDB_ICPS_JB_TOTAL
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	double   encash_amt;  /*�������Ž��*/
		/*�������Ž��*/
	double   withhold_amt;  /*�������̱�������۽��*/
		/*�������̱�������۽��*/
	double   refund_amt;  /*�����˻����̱�������*/
		/*�����˻����̱�������*/
	double   accrued_int_amt;  /*��������/����90�����ڣ������������ÿ����Ϣ*/
		/*��������/����90�����ڣ������������ÿ����Ϣ*/
	double   non_accrued_int_amt;  /*��������90�����ϴ������ÿ����Ϣ*/
		/*��������90�����ϴ������ÿ����Ϣ*/
	double   accrued_ovd_prin_pnlt_amt;  /*��������90�����ڣ������������ÿ�����ڱ���Ϣ*/
		/*��������90�����ڣ������������ÿ�����ڱ���Ϣ*/
	double   non_accrued_ovd_prin_pnlt_amt;  /*��������90�����ϴ������ÿ�����ڱ���Ϣ*/
		/*��������90�����ϴ������ÿ�����ڱ���Ϣ*/
	double   accrued_ovd_int_pnlt_amt;  /*��������90�����ڣ������������ÿ��������Ϣ��Ϣ*/
		/*��������90�����ڣ������������ÿ��������Ϣ��Ϣ*/
	double   non_accrued_ovd_int_pnlt_amt;  /*��������90�����ϴ������ÿ��������Ϣ��Ϣ*/
		/*��������90�����ϴ������ÿ��������Ϣ��Ϣ*/
	double   prin_to_ovd_prin_amt;  /*��������ת���ڱ���*/
		/*��������ת���ڱ���*/
	double   int_to_ovd_int_amt;  /*������Ϣת������Ϣ*/
		/*������Ϣת������Ϣ*/
	double   accrued_to_non_prin_amt;  /*��������Ӧ�ƣ�ת�������𣨷�Ӧ�ƣ�*/
		/*��������Ӧ�ƣ�ת�������𣨷�Ӧ�ƣ�*/
	double   accrued_to_non_ovd_prin_amt;  /*���ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�*/
		/*���ڱ���Ӧ�ƣ�ת���ڱ��𣨷�Ӧ�ƣ�*/
	double   in_to_out_int_amt;  /*������Ϣ�����ڣ�ת������Ϣ�����⣩*/
		/*������Ϣ�����ڣ�ת������Ϣ�����⣩*/
	double   in_to_out_ovd_int_amt;  /*������Ϣ�����ڣ�ת������Ϣ�����⣩*/
		/*������Ϣ�����ڣ�ת������Ϣ�����⣩*/
	double   in_to_out_ovd_prin_pnlt_amt;  /*���ڱ���Ϣ�����ڣ�ת���ڱ���Ϣ�����⣩*/
		/*���ڱ���Ϣ�����ڣ�ת���ڱ���Ϣ�����⣩*/
	double   in_to_out_ovd_int_pnlt_amt;  /*������Ϣ��Ϣ�����ڣ�ת������Ϣ��Ϣ�����⣩*/
		/*������Ϣ��Ϣ�����ڣ�ת������Ϣ��Ϣ�����⣩*/
	double   non_to_accrued_prin_amt;  /*�������𣨷�Ӧ�ƣ�ת��������Ӧ�ƣ�*/
		/*�������𣨷�Ӧ�ƣ�ת��������Ӧ�ƣ�*/
	double   non_to_accrued_ovd_prin_amt;  /*���ڱ��𣨷�Ӧ�ƣ�ת���ڱ���Ӧ�ƣ�*/
		/*���ڱ��𣨷�Ӧ�ƣ�ת���ڱ���Ӧ�ƣ�*/
	double   out_to_in_int_amt;  /*������Ϣ�����⣩ת������Ϣ�����ڣ�*/
		/*������Ϣ�����⣩ת������Ϣ�����ڣ�*/
	double   out_to_in_ovd_int_amt;  /*������Ϣ�����⣩ת������Ϣ�����ڣ�*/
		/*������Ϣ�����⣩ת������Ϣ�����ڣ�*/
	double   out_to_in_ovd_prin_pnlt_amt;  /*���ڱ���Ϣ�����⣩ת�Ȿ��Ϣ�����ڣ�*/
		/*���ڱ���Ϣ�����⣩ת�Ȿ��Ϣ�����ڣ�*/
	double   out_to_in_ovd_int_pnlt_amt;  /*������Ϣ��Ϣ�����⣩ת������Ϣ��Ϣ�����ڣ�*/
		/*������Ϣ��Ϣ�����⣩ת������Ϣ��Ϣ�����ڣ�*/
	double   paid_prin_amt;  /*ʵ����������Ӧ�ƣ�*/
		/*ʵ����������Ӧ�ƣ�*/
	double   paid_non_accrued_prin_amt;  /*ʵ���������𣨷�Ӧ�ƣ�*/
		/*ʵ���������𣨷�Ӧ�ƣ�*/
	double   paid_accrued_ovd_prin_amt;  /*ʵ�����ڱ���Ӧ�ƣ�*/
		/*ʵ�����ڱ���Ӧ�ƣ�*/
	double   paid_non_accrued_ovd_prin_amt;  /*ʵ�����ڱ��𣨷�Ӧ�ƣ�*/
		/*ʵ�����ڱ��𣨷�Ӧ�ƣ�*/
	double   paid_int_amt;  /*ʵ��������Ϣ�����ڣ�*/
		/*ʵ��������Ϣ�����ڣ�*/
	double   paid_out_int_amt;  /*ʵ��������Ϣ�����⣩*/
		/*ʵ��������Ϣ�����⣩*/
	double   paid_in_ovd_int_amt;  /*ʵ��������Ϣ�����ڣ�*/
		/*ʵ��������Ϣ�����ڣ�*/
	double   paid_out_ovd_int_amt;  /*ʵ��������Ϣ�����⣩*/
		/*ʵ��������Ϣ�����⣩*/
	double   paid_in_ovd_prin_pnlt_int_amt;  /*ʵ�����ڱ���Ϣ�����ڣ�*/
		/*ʵ�����ڱ���Ϣ�����ڣ�*/
	double   paid_out_ovd_prin_pnlt_int_amt;  /*ʵ�����ڱ���Ϣ�����⣩*/
		/*ʵ�����ڱ���Ϣ�����⣩*/
	double   paid_in_ovd_int_pnlt_int_amt;  /*ʵ��������Ϣ��Ϣ�����ڣ�*/
		/*ʵ��������Ϣ��Ϣ�����ڣ�*/
	double   paid_out_ovd_int_pnlt_int_amt;  /*ʵ��������Ϣ��Ϣ�����⣩*/
		/*ʵ��������Ϣ��Ϣ�����⣩*/
	double   xpt_in_int_amt;  /*����������Ϣ�����ڣ�*/
		/*����������Ϣ�����ڣ�*/
	double   xpt_out_int_amt;  /*����������Ϣ�����⣩*/
		/*����������Ϣ�����⣩*/
	double   xpt_in_ovd_int_amt;  /*����������Ϣ�����ڣ�*/
		/*����������Ϣ�����ڣ�*/
	double   xpt_out_ovd_int_amt;  /*����������Ϣ�����⣩*/
		/*����������Ϣ�����⣩*/
	double   xpt_in_ovd_prin_pnlt_int_amt;  /*�������ڱ���Ϣ�����ڣ�*/
		/*�������ڱ���Ϣ�����ڣ�*/
	double   xpt_out_ovd_prin_pnlt_int_amt;  /*�������ڱ���Ϣ�����⣩*/
		/*�������ڱ���Ϣ�����⣩*/
	double   xpt_in_ovd_int_pnlt_int_amt;  /*����������Ϣ��Ϣ�����ڣ�*/
		/*����������Ϣ��Ϣ�����ڣ�*/
	double   xpt_out_ovd_int_pnlt_int_amt;  /*����������Ϣ��Ϣ�����⣩*/
		/*����������Ϣ��Ϣ�����⣩*/
	double fee_amt;    /*ƽ̨����ѻ��ܽ��*/
		/*ƽ̨����ѻ��ܽ��*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_TOTAL;

#define SD_DATA  ICPS_JB_TOTAL
#define SD_MEMBERS \
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  encash_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  withhold_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  refund_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_accrued_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_accrued_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_accrued_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_to_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_to_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  accrued_to_non_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  in_to_out_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_to_accrued_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  non_to_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_ovd_prin_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  out_to_in_ovd_int_pnlt_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_non_accrued_ovd_prin_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_in_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  paid_out_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_ovd_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_ovd_prin_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_in_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  xpt_out_ovd_int_pnlt_int_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_amt,2),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_TOTAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_TOTAL_H__*/
