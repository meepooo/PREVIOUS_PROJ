/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_DS_APPROVAL_FLOW.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_DS_APPROVAL_FLOW (F_WB30.���������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_DS_APPROVAL_FLOW_H__
#define __ICPS_WB_DS_APPROVAL_FLOW_H__
typedef struct TDB_ICPS_WB_DS_APPROVAL_FLOW
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   partition_date[10+1];  /*��������*/
		/*��������*/
	char   busi_no[40+1];  /*��ˮ��*/
		/*��ˮ��*/
	char   bank_no[20+1];  /*���к�*/
		/*���к�*/
	char   final_ret[20+1];  /*�����������*/
		/*�����������*/
	char   ours_approval_ret[40+1];  /*�������������*/
		/*�������������*/
	char   code_block[200+1];  /*�ܾ���*/
		/*�ܾ���*/
	char   is_first[2+1];  /*�Ƿ��׽�*/
		/*�Ƿ��׽�*/
	char   outer_ret[40+1];  /*�����л����������*/
		/*�����л����������*/
	char   psz_ret[40+1];  /*Psz���������*/
		/*Psz���������*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_DS_APPROVAL_FLOW;

#define SD_DATA  ICPS_WB_DS_APPROVAL_FLOW
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  final_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  ours_approval_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  code_block, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_first, 0),\
	APP_DEFSDMEMBER(T_STRING,  outer_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  psz_ret, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_APPROVAL_FLOW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_APPROVAL_FLOW_H__*/
