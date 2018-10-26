/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:
�� �� ��:ICPS_WB_CAV_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_CAV_INFO (΢����������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_CAV_INFO_H__
#define __ICPS_WB_CAV_INFO_H__
typedef struct TDB_ICPS_WB_CAV_INFO
{
	char   BUSI_DATE[8+1];  /*ҵ������*/
	char   NAME[90+1];  /*�ͻ�����*/
	char   CERTI_NO[18+1];  /*���֤��*/
	char   CARD_NO[19+1];  /*���п���*/
	char   CUST_ID[32+1];  /*CNC�ͻ�ID*/
	char   LOGICAL_CARD_NO[19+1];  /*�߼�����*/
	char   PRODUCT_CD[6+1];  /*��Ʒ��*/
	char   REF_NBR[23+1];  /*��ݺţ����ײο��ţ�*/
	double LOAN_INIT_PRIN;  /*��ݱ���*/
	char   BANK_GROUP_ID[5+1];  /*���ű��*/
	char   EXTEND_PARAM1[100+1];  /*��չ1*/
	char   EXTEND_PARAM2[250+1];  /*��չ2*/
	char   EXTEND_PARAM3[40+1];  /*��չ3*/

}ICPS_WB_CAV_INFO;

#define SD_DATA  ICPS_WB_CAV_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  BUSI_DATE, 0),\
	APP_DEFSDMEMBER(T_STRING,  NAME, 0),\
	APP_DEFSDMEMBER(T_STRING,  CERTI_NO, 0),\
	APP_DEFSDMEMBER(T_STRING,  CARD_NO, 0),\
	APP_DEFSDMEMBER(T_STRING,  CUST_ID, 0),\
	APP_DEFSDMEMBER(T_STRING,  LOGICAL_CARD_NO, 0),\
	APP_DEFSDMEMBER(T_STRING,  PRODUCT_CD, 0),\
	APP_DEFSDMEMBER(T_STRING,  REF_NBR, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  LOAN_INIT_PRIN, 2),\
	APP_DEFSDMEMBER(T_STRING,  BANK_GROUP_ID, 0),\
	APP_DEFSDMEMBER(T_STRING,  EXTEND_PARAM1, 0),\
	APP_DEFSDMEMBER(T_STRING,  EXTEND_PARAM2, 0),\
	APP_DEFSDMEMBER(T_STRING,  EXTEND_PARAM3, 0)

	APP_DECLAREFIELDS(SD_ICPS_WB_CAV_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_CAV_INFO_H__*/
