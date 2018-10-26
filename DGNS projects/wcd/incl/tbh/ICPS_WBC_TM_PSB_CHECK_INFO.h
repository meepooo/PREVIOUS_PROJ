/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_PSB_CHECK_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_PSB_CHECK_INFO
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_PSB_CHECK_INFO_H__
#define __ICPS_WBC_TM_PSB_CHECK_INFO_H__
typedef struct TDB_ICPS_WBC_TM_PSB_CHECK_INFO
{
	char			busi_date[8+1];                  
	int				file_order;
	char			seq_no[32+1];                   /*��ѯ��ˮ��      */
	char			org[12+1];                      /*������          */
	char			app_no[20+1];                   /*��������      */
	char			id_type[2+1];                   /*֤������        */
	char			id_no[18+1];                    /*֤������        */
	char			name[30+1];                     /*����            */
	char			gender[2+1];                    /*�Ա�            */
	char			result_person_id[1+1];          /*֤������˲���*/
	char			result_person_name[1+1];        /*�����˲���    */
	char			photo_id[100+1];                /*��Ƭ�ļ�id      */
	char			nation[40+1];                   /*����            */
	char			photo_md5[100+1];               /*��Ƭmd5ֵ       */
	char			old_name[80+1];                 /*������          */
	char			birth[8+1];                     /*��������        */
	char			native_place[100+1];            /*����ʡ���أ�����*/
	char			address[100+1];                 /*סַ            */
	char			work_place[100+1];              /*������        */
	char			marital_status[40+1];           /*����״��        */
	char			degree_of_education[100+1];     /*�Ļ��̶�        */
	char			issued_authority[50+1];         /*ǩ������        */
	char			birth_place[25+1];              /*������          */
	char			occupation[30+1];               /*ְҵ            */
	char			bl0[20+1];                      /*����״̬        */
	char			bl1[20+1];                      /*Υ��״̬        */
	char			created_datetime[14+1];         /*����ʱ��        */
	char			last_modified_datetime[14+1];   /*����޸�ʱ��    */
	int				jpa_version;                    /*�ֹ���          */
	char			product_cd[6+1];                /*��Ʒ���        */
	char			msg_serv_error[40+1];           /*�����쳣����    */
	char			msg_id_error[40+1];             /*��ѯ�������    */
	char			flag[1+1];                      /*�����ȡ����    */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];

}ICPS_WBC_TM_PSB_CHECK_INFO;

#define SD_DATA  ICPS_WBC_TM_PSB_CHECK_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  seq_no                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  org                     ,0),\
	APP_DEFSDMEMBER(T_STRING,  app_no                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  gender                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  result_person_id        ,0),\
	APP_DEFSDMEMBER(T_STRING,  result_person_name      ,0),\
	APP_DEFSDMEMBER(T_STRING,  photo_id                ,0),\
	APP_DEFSDMEMBER(T_STRING,  nation                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  photo_md5               ,0),\
	APP_DEFSDMEMBER(T_STRING,  old_name                ,0),\
	APP_DEFSDMEMBER(T_STRING,  birth                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  native_place            ,0),\
	APP_DEFSDMEMBER(T_STRING,  address                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  work_place              ,0),\
	APP_DEFSDMEMBER(T_STRING,  marital_status          ,0),\
	APP_DEFSDMEMBER(T_STRING,  degree_of_education     ,0),\
	APP_DEFSDMEMBER(T_STRING,  issued_authority        ,0),\
	APP_DEFSDMEMBER(T_STRING,  birth_place             ,0),\
	APP_DEFSDMEMBER(T_STRING,  occupation              ,0),\
	APP_DEFSDMEMBER(T_STRING,  bl0                     ,0),\
	APP_DEFSDMEMBER(T_STRING,  bl1                     ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_LONG,    jpa_version             ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
	APP_DEFSDMEMBER(T_STRING,  msg_serv_error          ,0),\
	APP_DEFSDMEMBER(T_STRING,  msg_id_error            ,0),\
	APP_DEFSDMEMBER(T_STRING,  flag                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_PSB_CHECK_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_PSB_CHECK_INFO_H__*/
                                                                                                                              
