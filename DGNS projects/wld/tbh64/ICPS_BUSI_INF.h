/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_BUSI_INF.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_BUSI_INF (6.ҵ����Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_BUSI_INF_H__
#define __ICPS_BUSI_INF_H__
typedef struct TDB_ICPS_BUSI_INF
{
	char   busi_no[16+1];  /*ҵ����*/
		/*ҵ���� jiebei-���� jintiao-���� wbank-΢����*/
	char   busi_nm[64+1];  /*ҵ������*/
		/*ҵ������*/
	char   local_id[16+1];  /*����������*/
		/*����������*/
	char   time_zone[32+1];  /*������ʱ��*/
		/*������ʱ��*/
	char   sign_type[16+1];  /*ǩ���㷨����*/
		/*ǩ���㷨���� RSA*/
	char   message_charset[16+1];  /*�����ַ�����*/
		/*�����ַ�����*/
	char   version[8+1];  /*�汾��*/
		/*�汾��*/
	char   clear_acct_id[64+1];  /*�ڲ������˺�*/
		/*�ڲ������˺�*/
	char   clear_acct_nm[128+1];  /*�ڲ������˺�����*/
		/*�ڲ������˺�����*/
	char   position_acct_id[64+1];  /*�ڲ�ͷ���˺�*/
		/*�ڲ�ͷ���˺�*/
	char   position_acct_nm[128+1];  /*�ڲ�ͷ���˺�����*/
		/*�ڲ�ͷ���˺�����*/
	char   fee_out_acct_id[64+1];  /*������֧���˺�*/
		/*������֧���˺�*/
	char   fee_out_acct_nm[128+1];  /*������֧���˺�����*/
		/*������֧���˺�����*/
	char   fee_in_acct_id[64+1];  /*�����������˺�*/
		/*�����������˺�*/
	char   fee_in_acct_nm[128+1];  /*�����������˺�����*/
		/*�����������˺�����*/
	char   provisions_acct_id[64+1];  /*�������������˺�*/
		/*�������������˺�*/
	char   provisions_acct_nm[128+1];  /*�������������˺�����*/
		/*�������������˺�����*/
	char   open_flag[1+1];  /*��ͨ��ʶ*/
		/*��ͨ��ʶ 0-δ��ͨ 1-��ͨ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_BUSI_INF;

#define SD_DATA  ICPS_BUSI_INF
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  local_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  time_zone, 0),\
	APP_DEFSDMEMBER(T_STRING,  sign_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  message_charset, 0),\
	APP_DEFSDMEMBER(T_STRING,  version, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  position_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  position_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_out_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_out_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_in_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_in_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  provisions_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  provisions_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  open_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_BUSI_INF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_BUSI_INF_H__*/
