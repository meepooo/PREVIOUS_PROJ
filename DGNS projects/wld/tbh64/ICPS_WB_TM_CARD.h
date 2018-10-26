/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_CARD.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_CARD (F_WB3.�߼�����)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_CARD_H__
#define __ICPS_WB_TM_CARD_H__
typedef struct TDB_ICPS_WB_TM_CARD
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   logical_card_no[19+1];  /*�߼�����*/
		/*�߼�����*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   cust_id[20+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   user_field118[15+1];  /*�����ֶ�118*/
		/*�����ֶ�118*/
	char   product_cd[6+1];  /*��Ʒ����*/
		/*��Ʒ����*/
	char   app_no[20+1];  /*��������*/
		/*��������*/
	char   user_field119[40+1];  /*�����ֶ�119*/
		/*�����ֶ�119*/
	char   user_field120[1+1];  /*�����ֶ�120*/
		/*�����ֶ�120*/
	char   bsc_logiccard_no[19+1];  /*�߼�����������*/
		/*�߼�����������*/
	char   user_field121[9+1];  /*�����ֶ�121*/
		/*�����ֶ�121*/
	char   user_field122[15+1];  /*�����ֶ�122*/
		/*�����ֶ�122*/
	char   user_field123[80+1];  /*�����ֶ�123*/
		/*�����ֶ�123*/
	char   user_field124[19+1];  /*�����ֶ�124*/
		/*�����ֶ�124*/
	char   user_field125[14+1];  /*�����ֶ�125*/
		/*�����ֶ�125*/
	char   user_field126[27+1];  /*�����ֶ�126*/
		/*�����ֶ�126*/
	char   activate_ind[1+1];  /*�Ƿ��Ѽ���*/
		/*�Ƿ��Ѽ���*/
	char   cancel_date[14+1];  /*������������*/
		/*������������*/
	char   latest_card_no[19+1];  /*���½��ʿ���*/
		/*���½��ʿ���*/
	char   user_field127[1+1];  /*�����ֶ�127*/
		/*�����ֶ�127*/
	char   user_field128[20+1];  /*�����ֶ�128*/
		/*�����ֶ�128*/
	char   user_field129[80+1];  /*�����ֶ�129*/
		/*�����ֶ�129*/
	char   user_field130[1+1];  /*�����ֶ�130*/
		/*�����ֶ�130*/
	char   user_field131[1+1];  /*�����ֶ�131*/
		/*�����ֶ�131*/
	char   card_expire_date[14+1];  /*��Ƭ��Ч����*/
		/*��Ƭ��Ч����*/
	double   user_field132;  /*�����ֶ�132*/
		/*�����ֶ�132*/
	char   user_field133[1+1];  /*�����ֶ�133*/
		/*�����ֶ�133*/
	char   user_field134[3+1];  /*�����ֶ�134*/
		/*�����ֶ�134*/
	char   user_field135[14+1];  /*�����ֶ�135*/
		/*�����ֶ�135*/
	char   user_field136[14+1];  /*�����ֶ�136*/
		/*�����ֶ�136*/
	char   user_field137[1+1];  /*�����ֶ�137*/
		/*�����ֶ�137*/
	char   user_field138[14+1];  /*�����ֶ�138*/
		/*�����ֶ�138*/
	char   user_field139[1+1];  /*�����ֶ�139*/
		/*�����ֶ�139*/
	char   user_field140[1+1];  /*�����ֶ�140*/
		/*�����ֶ�140*/
	char   user_field141[1+1];  /*�����ֶ�141*/
		/*�����ֶ�141*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	char   user_field142[14+1];  /*�����ֶ�142*/
		/*�����ֶ�142*/
	char   user_field143[14+1];  /*�����ֶ�143*/
		/*�����ֶ�143*/
	char   user_field144[14+1];  /*�����ֶ�144*/
		/*�����ֶ�144*/
	char   user_field145[14+1];  /*�����ֶ�145*/
		/*�����ֶ�145*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_CARD;

#define SD_DATA  ICPS_WB_TM_CARD
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field118, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field119, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field120, 0),\
	APP_DEFSDMEMBER(T_STRING,  bsc_logiccard_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field121, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field122, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field123, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field124, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field125, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field126, 0),\
	APP_DEFSDMEMBER(T_STRING,  activate_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  latest_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field127, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field128, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field129, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field130, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field131, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_expire_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field132, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field133, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field134, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field135, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field136, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field137, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field138, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field139, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field140, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field141, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field142, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field143, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field144, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field145, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_CARD)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_CARD_H__*/
