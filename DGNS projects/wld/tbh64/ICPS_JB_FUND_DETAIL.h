/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_JB_FUND_DETAIL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_FUND_DETAIL (F_JB13.���������ʽ�����ļ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_JB_FUND_DETAIL_H__
#define __ICPS_JB_FUND_DETAIL_H__
typedef struct TDB_ICPS_JB_FUND_DETAIL
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   third_busi_serial[64+1];  /*�������н�����ˮ��*/
		/*�������н�����ˮ��*/
	char   third_busi_type[32+1];  /*ҵ�����*/
		/*ҵ�����������P_DLGATE������P_WITHDRAW������շ��˻��Ƕ����ģ���P_FEE�������շѣ�*/
	double   trans_amt;  /*���׽��*/
		/*���׽�� ����Ϊ����������Ϊ����*/
	double   trans_refund_amt;  /*�����˿���*/
		/*�����˿��� ����˽�����0������Ǵ����˿�*/
	char   trans_dttm[14+1];  /*����ʱ��*/
		/*����ʱ�� YYYYMMDDHHMMSS*/
	char   third_trans_name[256+1];  /*��������*/
		/*�������� ���գ�����*/
	char   peer_org_name[32+1];  /*�Է���������*/
		/*�Է���������*/
	char   trans_sub_detail[128+1];  /*ҵ�񵥺�*/
		/*ҵ�񵥺�*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_JB_FUND_DETAIL;

#define SD_DATA  ICPS_JB_FUND_DETAIL
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_busi_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_busi_type, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  trans_refund_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  trans_dttm, 0),\
	APP_DEFSDMEMBER(T_STRING,  third_trans_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  peer_org_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  trans_sub_detail, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_JB_FUND_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_JB_FUND_DETAIL_H__*/
