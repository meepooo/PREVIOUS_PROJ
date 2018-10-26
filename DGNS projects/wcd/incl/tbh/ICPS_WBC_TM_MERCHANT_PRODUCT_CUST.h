/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_MERCHANT_PRODUCT_CUST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
˵    ��:�ͻ���Ʒ��Ϣ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_MERCHANT_PRODUCT_CUST_H__
#define __ICPS_WBC_TM_MERCHANT_PRODUCT_CUST_H__
typedef struct TDB_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
{
	char			busi_date[8+1];
	int				file_order;
	char			user_id[32+1];                  /*ƽ̨�Ŀͻ�ID   */
	char			merchant_id[20+1];              /*ƽ̨ID         */
	char			product_cd[6+1];                /*��ƷCD         */
	char			cnc_card_no[20+1];              /*�����       */
	char			debit_card_no[19+1];            /*���н�ǿ���   */
	char			wb_debit_card_no[19+1];         /*���н�ǿ���   */
	char			nbs_cust_id[20+1];              /*NBS�ͻ�ID      */
	char			aps_app_time[8+1];              /*APS��������ʱ��*/
	char			aps_app_no[20+1];               /*APS���������  */
	char			aps_app_no_status[20+1];        /*APS�����״̬  */
	int				aps_app_count;                  /*�����������   */
	char			aps_approval_date[8+1];         /*APS����ͨ������*/
	char			aps_result_level[2+1];          /*APS��������ȼ�*/
	char			aps_rej_code[15+1];             /*APS�����ܾ���  */
	char			aps_rej_date[10+1];             /*APS�����ܾ�ʱ��*/
	char			cnc_setup_date[8+1];            /*���������   */
	double			aps_credit_limit;               /*����ʱ���Ŷ�� */
	char			gid[64+1];                      /*����ԴGID      */
	char			oper_ip[24+1];                  /*����ԴIP       */
	char			os_type[20+1];                  /*����ϵͳ       */
	char			lbs[60+1];                      /*LBS            */
	char			ios_idfa[50+1];                 /*IOS��ʾ��      */
	char			android_imei[50+1];             /*ANDROID������ַ*/
	char			submitted_entry[3+1];           /*�ύ���       */
	char			submitted_city[32+1];           /*�������       */
	char			reserve1[20+1];                 /*�����ֶ�1      */
	char			reserve2[50+1];                 /*�����ֶ�2      */
	char			reserve3[50+1];                 /*�����ֶ�3      */
	char			biz_date[8+1];                  /*ҵ������       */
	char			created_datetime[14+1];         /*����ʱ������   */
	char			last_modified_datetime[14+1];   /*����ʱ������   */
	char			app_biz_seq_no[32+1];           /*����ҵ����ˮ�� */
	char			aps_rej_reason[120+1];          /*����ܾ�ԭ��   */
	char			app_expiry_date[8+1];           /*����ʧЧ����   */
	char			agent_id[20+1];                 /*���������id   */
	char			agent_name[30+1];               /*����������     */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_MERCHANT_PRODUCT_CUST;

#define SD_DATA  ICPS_WBC_TM_MERCHANT_PRODUCT_CUST
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
   APP_DEFSDMEMBER(T_STRING,  user_id                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
   APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
   APP_DEFSDMEMBER(T_STRING,  cnc_card_no             ,0),\
   APP_DEFSDMEMBER(T_STRING,  debit_card_no           ,0),\
   APP_DEFSDMEMBER(T_STRING,  wb_debit_card_no        ,0),\
   APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_app_time            ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_app_no              ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_app_no_status       ,0),\
   APP_DEFSDMEMBER(T_LONG,    aps_app_count           ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_approval_date       ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_result_level        ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_rej_code            ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_rej_date            ,0),\
   APP_DEFSDMEMBER(T_STRING,  cnc_setup_date          ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,  aps_credit_limit        ,2),\
   APP_DEFSDMEMBER(T_STRING,  gid                     ,0),\
   APP_DEFSDMEMBER(T_STRING,  oper_ip                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  os_type                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  lbs                     ,0),\
   APP_DEFSDMEMBER(T_STRING,  ios_idfa                ,0),\
   APP_DEFSDMEMBER(T_STRING,  android_imei            ,0),\
   APP_DEFSDMEMBER(T_STRING,  submitted_entry         ,0),\
   APP_DEFSDMEMBER(T_STRING,  submitted_city          ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve1                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve2                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve3                ,0),\
   APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
   APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
   APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
   APP_DEFSDMEMBER(T_STRING,  app_biz_seq_no          ,0),\
   APP_DEFSDMEMBER(T_STRING,  aps_rej_reason          ,0),\
   APP_DEFSDMEMBER(T_STRING,  app_expiry_date         ,0),\
   APP_DEFSDMEMBER(T_STRING,  agent_id                ,0),\
   APP_DEFSDMEMBER(T_STRING,  agent_name              ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)

  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_MERCHANT_PRODUCT_CUST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_APP_MAIN_H__*/
                                                                                                                                                  
