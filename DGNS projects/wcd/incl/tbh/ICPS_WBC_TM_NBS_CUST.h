/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_NBS_CUST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_NBS_CUST
˵    ��:nbs�ͻ���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_NBS_CUST_H__
#define __ICPS_WBC_TM_NBS_CUST_H__
typedef struct TDB_ICPS_WBC_TM_NBS_CUST
{
	char			busi_date[8+1];                
	int				file_order;
	char			nbs_cust_id[20+1];                  /*NBS�ͻ�ID   */
	char			name[80+1];                         /*����        */
	char			id_type[2+1];                       /*֤������    */
	char			id_no[30+1];                        /*֤������    */
	char			ecif_no[40+1];                      /*ecif�ͻ���  */
	char			reserve1[20+1];                     /*�����ֶ�1   */
	char			reserve2[20+1];                     /*���֤��Ч��*/
	char			reserve3[50+1];                     /*�����ֶ�3   */
	char			biz_date[8+1];                      /*ҵ������    */
	char			created_datetime[14+1];             /*����ʱ������*/
	char			last_modified_datetime[14+1];       /*����ʱ������*/
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];

}ICPS_WBC_TM_NBS_CUST;

#define SD_DATA  ICPS_WBC_TM_NBS_CUST
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
   APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
   APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
   APP_DEFSDMEMBER(T_STRING,  ecif_no                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve1                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve2                ,0),\
   APP_DEFSDMEMBER(T_STRING,  reserve3                ,0),\
   APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
   APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
   APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_NBS_CUST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_NBS_CUSTN_H__*/
