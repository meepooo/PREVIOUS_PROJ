/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_AGREEMENT_NO_MAP.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_AGREEMENT_NO_MAP
˵    ��:������ӳ���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_AGREEMENT_NO_MAP_H__
#define __ICPS_WBC_TM_AGREEMENT_NO_MAP_H__
typedef struct TDB_ICPS_WBC_TM_AGREEMENT_NO_MAP
{
	char			busi_date[8+1];                      
	int				file_order; 
	char			agreement_no[50+1];                     /*NBS������   */
	char			merchant_id[20+1];                      /*ƽ̨ID��    */
	char			mer_order_no[50+1];                     /*ƽ̨������  */
	char			txn_status[4+1];                        /*ƽ̨Э��״̬*/
	char			biz_data[8+1];                       /*ҵ������    */
	char			created_datetime[14+1];                 /*����ʱ��    */
	char			last_modified_datetime[14+1];           /*�޸�ʱ��    */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_AGREEMENT_NO_MAP;

#define SD_DATA  ICPS_WBC_TM_AGREEMENT_NO_MAP
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  agreement_no            ,0),\
	APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  mer_order_no            ,0),\
	APP_DEFSDMEMBER(T_STRING,  txn_status              ,0),\
	APP_DEFSDMEMBER(T_STRING,  biz_data                ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  	APP_DECLAREFIELDS(SD_ICPS_WBC_TM_AGREEMENT_NO_MAP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_AGREEMENT_NO_MAP_H__*/
                              
