/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_COLL_REC.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_COLL_REC (F_WB23.���ռ�¼��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_COLL_REC_H__
#define __ICPS_WB_TM_COLL_REC_H__
typedef struct TDB_ICPS_WB_TM_COLL_REC
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	int   coll_rec_id;  /*�߼���ˮ��*/
		/*�߼���ˮ��*/
	char   case_no[32+1];  /*�������*/
		/*�������*/
	char   cust_id[20+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   coll_rec_type[10+1];  /*�߼�����*/
		/*�߼�����*/
	char   action_code[32+1];  /*���ն���*/
		/*���ն���*/
	char   user_field1[1+1];  /*�����ֶ�*/
		/*�����ֶ�*/
	char   user_field2[4+1];  /*�����ֶ�2*/
		/*�����ֶ�2*/
	char   coll_time[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   coll_conseq[10+1];  /*���ս��*/
		/*���ս��*/
	double   prom_amt;  /*��ŵ���*/
		/*��ŵ���*/
	char   prom_date[14+1];  /*��ŵ����*/
		/*��ŵ����*/
	char   user_field3[400+1];  /*�����ֶ�3*/
		/*�����ֶ�3*/
	double   user_field4;  /*�����ֶ�4*/
		/*�����ֶ�4*/
	char   user_field5[10+1];  /*�����ֶ�5*/
		/*�����ֶ�5*/
	char   user_field6[10+1];  /*�����ֶ�6*/
		/*�����ֶ�6*/
	char   user_field7[10+1];  /*�����ֶ�7*/
		/*�����ֶ�7*/
	char   user_field8[10+1];  /*�����ֶ�8*/
		/*�����ֶ�8*/
	char   user_field9[10+1];  /*�����ֶ�9*/
		/*�����ֶ�9*/
	char   user_field10[10+1];  /*�����ֶ�10*/
		/*�����ֶ�10*/
	char   user_field11[20+1];  /*�����ֶ�11*/
		/*�����ֶ�11*/
	char   user_field12[50+1];  /*�����ֶ�12*/
		/*�����ֶ�12*/
	char   user_field13[50+1];  /*�����ֶ�13*/
		/*�����ֶ�13*/
	char   user_field14[10+1];  /*�����ֶ�14*/
		/*�����ֶ�14*/
	char   user_field15[10+1];  /*�����ֶ�15*/
		/*�����ֶ�15*/
	char   user_field16[50+1];  /*�����ֶ�16*/
		/*�����ֶ�16*/
	char   user_field17[50+1];  /*�����ֶ�17*/
		/*�����ֶ�17*/
	char   user_field18[14+1];  /*�����ֶ�18*/
		/*�����ֶ�18*/
	char   user_field19[14+1];  /*�����ֶ�19*/
		/*�����ֶ�19*/
	int   user_field20;  /*�����ֶ�20*/
		/*�����ֶ�20*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_COLL_REC;

#define SD_DATA  ICPS_WB_TM_COLL_REC
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_LONG,  coll_rec_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  case_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  coll_rec_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  action_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field1, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field2, 0),\
	APP_DEFSDMEMBER(T_STRING,  coll_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  coll_conseq, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prom_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  prom_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field3, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field4, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field5, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field6, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field7, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field8, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field9, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field10, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field11, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field12, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field13, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field14, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field15, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field16, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field17, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field18, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field19, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field20, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_COLL_REC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_COLL_REC_H__*/
