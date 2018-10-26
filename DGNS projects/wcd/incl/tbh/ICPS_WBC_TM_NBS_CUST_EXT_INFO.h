/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_NBS_CUST_EXT_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_NBS_CUST_EXT_INFO
˵    ��:nbs�ͻ���չ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_NBS_CUST_EXT_INFO_H__
#define __ICPS_WBC_TM_NBS_CUST_EXT_INFO_H__
typedef struct TDB_ICPS_WBC_TM_NBS_CUST_EXT_INFO
{
	char			busi_date[8+1];
	int				file_order;
	char			nbs_cust_id[20+1];            /*NBS�ͻ�ID   */
	char			product_cd[6+1];              /*��Ʒ��      */
	char			merchant_id[20+1];            /*ƽ̨ID      */
	char			name[80+1];                   /*����        */
	char			id_type[2+1];                 /*֤������    */
	char			id_no[30+1];                  /*֤������    */
	char			id_no_expiry[30+1];           /*���֤��Ч��*/
	char			residential_address[100+1];   /*��ַ        */
	char			gender[1+1];                  /*�Ա�        */
	char			nationality[20+1];            /*����        */
	char			marriage[20+1];               /*����״��    */
	char			education[20+1];              /*ѧ��        */
	char			cust_ext_inf1[30+1];          /*����        */
	char			cust_ext_inf2[30+1];          /*�����ֶ�    */
	char			cust_ext_inf3[30+1];          /*�����ֶ�    */
	char			cust_ext_inf4[30+1];          /*�����ֶ�    */
	char			cust_ext_inf5[30+1];          /*�����ֶ�    */
	char			cust_ext_inf6[30+1];          /*�����ֶ�    */
	char			cust_ext_inf7[30+1];          /*�����ֶ�    */
	char			cust_ext_inf8[30+1];          /*�����ֶ�    */
	char			cust_ext_inf9[30+1];          /*�����ֶ�    */
	char			cust_ext_inf10[30+1];         /*�����ֶ�    */
	char			cust_ext_inf11[30+1];         /*�����ֶ�    */
	char			cust_ext_inf12[30+1];         /*�����ֶ�    */
	char			cust_ext_inf13[30+1];         /*�����ֶ�    */
	char			cust_ext_inf14[30+1];         /*�����ֶ�    */
	char			cust_ext_inf15[30+1];         /*�����ֶ�    */
	char			cust_ext_inf16[30+1];         /*�����ֶ�    */
	char			cust_ext_inf17[50+1];         /*�����ֶ�    */
	char			cust_ext_inf18[50+1];         /*�����ֶ�    */
	char			cust_ext_inf19[100+1];        /*�����ֶ�    */
	char			cust_ext_inf20[100+1];        /*�����ֶ�    */
	char			created_datetime[14+1];       /*����ʱ������*/
	char			last_modified_datetime[14+1]; /*����ʱ������*/
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_NBS_CUST_EXT_INFO;

#define SD_DATA  ICPS_WBC_TM_NBS_CUST_EXT_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
	APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_no_expiry            ,0),\
	APP_DEFSDMEMBER(T_STRING,  residential_address     ,0),\
	APP_DEFSDMEMBER(T_STRING,  gender                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  nationality             ,0),\
	APP_DEFSDMEMBER(T_STRING,  marriage                ,0),\
	APP_DEFSDMEMBER(T_STRING,  education               ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf3           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf4           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf5           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf6           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf7           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf8           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf9           ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf10          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf11          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf12          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf13          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf14          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf15          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf16          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf17          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf18          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf19          ,0),\
	APP_DEFSDMEMBER(T_STRING,  cust_ext_inf20          ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)

  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_NBS_CUST_EXT_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_NBS_CUST_EXT_INFO_H__*/
                                                                                                                                          
