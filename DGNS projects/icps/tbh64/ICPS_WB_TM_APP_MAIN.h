/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_APP_MAIN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_APP_MAIN (F_WB6.��������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_APP_MAIN_H__
#define __ICPS_WB_TM_APP_MAIN_H__
typedef struct TDB_ICPS_WB_TM_APP_MAIN
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   app_no[20+1];  /*��������*/
		/*��������*/
	char   user_field1[1+1];  /*�����ֶ�*/
		/*�����ֶ�*/
	double   user_field2;  /*�����ֶ�2*/
		/*�����ֶ�2*/
	double   user_field3;  /*�����ֶ�3*/
		/*�����ֶ�3*/
	double   acc_lmt;  /*��׼���*/
		/*��׼���*/
	char   product_cd[6+1];  /*����Ʒ����*/
		/*����Ʒ����*/
	double   user_field4;  /*�����ֶ�4*/
		/*�����ֶ�4*/
	double   user_field5;  /*�����ֶ�5*/
		/*�����ֶ�5*/
	double   user_field6;  /*�����ֶ�6*/
		/*�����ֶ�6*/
	double   user_field7;  /*�����ֶ�7*/
		/*�����ֶ�7*/
	double   user_field8;  /*�����ֶ�8*/
		/*�����ֶ�8*/
	double   user_field9;  /*�����ֶ�9*/
		/*�����ֶ�9*/
	double   user_field10;  /*�����ֶ�10*/
		/*�����ֶ�10*/
	double   user_field11;  /*�����ֶ�11*/
		/*�����ֶ�11*/
	char   user_field12[1+1];  /*�����ֶ�12*/
		/*�����ֶ�12*/
	char   user_field13[3+1];  /*�����ֶ�13*/
		/*�����ֶ�13*/
	char   user_field14[1+1];  /*�����ֶ�14*/
		/*�����ֶ�14*/
	char   user_field15[20+1];  /*�����ֶ�15*/
		/*�����ֶ�15*/
	char   user_field16[3+1];  /*�����ֶ�16*/
		/*�����ֶ�16*/
	int   user_field17;  /*�����ֶ�17*/
		/*�����ֶ�17*/
	double   user_field18;  /*�����ֶ�18*/
		/*�����ֶ�18*/
	char   user_field19[20+1];  /*�����ֶ�19*/
		/*�����ֶ�19*/
	char   user_field20[400+1];  /*�����ֶ�20*/
		/*�����ֶ�20*/
	char   user_field21[1000+1];  /*�����ֶ�21*/
		/*�����ֶ�21*/
	int   user_field22;  /*�����ֶ�22*/
		/*�����ֶ�22*/
	char   user_field23[1+1];  /*�����ֶ�23*/
		/*�����ֶ�23*/
	char   user_field24[20+1];  /*�����ֶ�24*/
		/*�����ֶ�24*/
	char   user_field25[20+1];  /*�����ֶ�25*/
		/*�����ֶ�25*/
	char   user_field26[9+1];  /*�����ֶ�26*/
		/*�����ֶ�26*/
	char   user_field27[20+1];  /*�����ֶ�27*/
		/*�����ֶ�27*/
	char   user_field28[1+1];  /*�����ֶ�28*/
		/*�����ֶ�28*/
	char   user_field29[80+1];  /*�����ֶ�29*/
		/*�����ֶ�29*/
	char   user_field30[20+1];  /*�����ֶ�30*/
		/*�����ֶ�30*/
	char   user_field31[20+1];  /*�����ֶ�31*/
		/*�����ֶ�31*/
	char   user_field32[1+1];  /*�����ֶ�32*/
		/*�����ֶ�32*/
	char   user_field33[9+1];  /*�����ֶ�33*/
		/*�����ֶ�33*/
	char   user_field34[15+1];  /*�����ֶ�34*/
		/*�����ֶ�34*/
	char   user_field35[20+1];  /*�����ֶ�35*/
		/*�����ֶ�35*/
	char   user_field36[32+1];  /*�����ֶ�36*/
		/*�����ֶ�36*/
	char   user_field37[1+1];  /*�����ֶ�37*/
		/*�����ֶ�37*/
	char   user_field38[40+1];  /*�����ֶ�38*/
		/*�����ֶ�38*/
	char   user_field39[1+1];  /*�����ֶ�39*/
		/*�����ֶ�39*/
	char   user_field40[1+1];  /*�����ֶ�40*/
		/*�����ֶ�40*/
	char   user_field41[1+1];  /*�����ֶ�41*/
		/*�����ֶ�41*/
	char   user_field42[20+1];  /*�����ֶ�42*/
		/*�����ֶ�42*/
	char   user_field43[20+1];  /*�����ֶ�43*/
		/*�����ֶ�43*/
	char   user_field44[400+1];  /*�����ֶ�44*/
		/*�����ֶ�44*/
	char   user_field45[40+1];  /*�����ֶ�45*/
		/*�����ֶ�45*/
	char   user_field46[40+1];  /*�����ֶ�46*/
		/*�����ֶ�46*/
	char   user_field47[32+1];  /*�����ֶ�47*/
		/*�����ֶ�47*/
	char   user_field48[32+1];  /*�����ֶ�48*/
		/*�����ֶ�48*/
	char   user_field49[32+1];  /*�����ֶ�49*/
		/*�����ֶ�49*/
	char   user_field50[10+1];  /*�����ֶ�50*/
		/*�����ֶ�50*/
	char   user_field51[14+1];  /*�����ֶ�51*/
		/*�����ֶ�51*/
	char   last_modified_datetime[14+1];  /*����޸�ʱ��*/
		/*����޸�ʱ��*/
	int   jpa_Vversion;  /*�ֹ���*/
		/*�ֹ���*/
	char   uesr_field52[1+1];  /*�����ֶ�52*/
		/*�����ֶ�52*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_APP_MAIN;

#define SD_DATA  ICPS_WB_TM_APP_MAIN
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field1, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field2, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field3, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  acc_lmt, 4),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field4, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field5, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field6, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field7, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field8, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field9, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field10, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field11, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field12, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field13, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field14, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field15, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field16, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field17, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field18, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field19, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field20, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field21, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field22, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field23, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field24, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field25, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field26, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field27, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field28, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field29, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field30, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field31, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field32, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field33, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field34, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field35, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field36, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field37, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field38, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field39, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field40, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field41, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field42, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field43, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field44, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field45, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field46, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field47, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field48, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field49, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field50, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field51, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_Vversion, 0),\
	APP_DEFSDMEMBER(T_STRING,  uesr_field52, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_APP_MAIN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_APP_MAIN_H__*/
