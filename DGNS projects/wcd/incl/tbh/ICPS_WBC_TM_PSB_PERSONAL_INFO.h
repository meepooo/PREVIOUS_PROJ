/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_PSB_PERSONAL_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_PSB_PERSONAL_INFO
˵    ��:�����Ϣ
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_PSB_PERSONAL_INFO_H__
#define __ICPS_WBC_TM_PSB_PERSONAL_INFO_H__
typedef struct TDB_ICPS_WBC_TM_PSB_PERSONAL_INFO
{
	char			busi_date[8+1];
	int				file_order;               
	int				id;                       /*ID                */
	char			app_no[20+1];             /*��������        */
	char			certi_type[1+1];          /*֤������          */
	char			certi_no[18+1];           /*���֤��          */
	char			name[90+1];               /*����              */
	char			sex[1+1];                 /*�Ա�              */
	char			birth_date[8+1];          /*��������          */
	char			marrystate[2+1];          /*����״��          */
	char			mobile[20+1];             /*�ֻ�����          */
	char			homephone[30+1];          /*��ͥ�绰          */
	char			compphone[30+1];          /*��λ�绰          */
	char			qualification[2+1];       /*ѧ��              */
	char			degree[2+1];              /*ѧλ              */
	char			address[700+1];           /*ͨѶ��ַ          */
	char			reside_addr[700+1];       /*������ַ          */
	char			mate_certp[1+1];          /*��ż֤������      */
	char			mate_cerno[18+1];         /*��ż֤������      */
	char			mate_name[30+1];          /*��ż����          */
	char			mate_corp[500+1];         /*��ż������λ      */
	char			mate_phone[30+1];         /*��ż��ϵ�绰      */
	char			addr[700+1];              /*��ס��ַ          */
	char			reside_state[2+1];        /*��ס״��          */
	char			comp_nm[700+1];           /*������λ          */
	char			comp_addr[700+1];         /*��λ��ַ          */
	char			profess[2+1];             /*ְҵ              */
	char			comp_trade[2+1];          /*��ҵ              */
	char			business[2+1];            /*ְ��              */
	char			teach_pose[2+1];          /*ְ��              */
	char			work_date[4+1];           /*����λ������ʼ���*/
	char			infodate[8+1];            /*��Ϣ��������      */
	char			create_time[14+1];        /*����ʱ��          */
	char			psb_query_date[8+1];      /*���б����ѯʱ��  */
	char			reportsn[30+1];           /*���б�����      */
	char			is_check_flag[1+1];       /*                  */
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_PSB_PERSONAL_INFO;

#define SD_DATA  ICPS_WBC_TM_PSB_PERSONAL_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date       ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order      ,0),\
	APP_DEFSDMEMBER(T_LONG,    id              ,0),\
	APP_DEFSDMEMBER(T_STRING,  app_no          ,0),\
	APP_DEFSDMEMBER(T_STRING,  certi_type      ,0),\
	APP_DEFSDMEMBER(T_STRING,  certi_no        ,0),\
	APP_DEFSDMEMBER(T_STRING,  name            ,0),\
	APP_DEFSDMEMBER(T_STRING,  sex             ,0),\
	APP_DEFSDMEMBER(T_STRING,  birth_date      ,0),\
	APP_DEFSDMEMBER(T_STRING,  marrystate      ,0),\
	APP_DEFSDMEMBER(T_STRING,  mobile          ,0),\
	APP_DEFSDMEMBER(T_STRING,  homephone       ,0),\
	APP_DEFSDMEMBER(T_STRING,  compphone       ,0),\
	APP_DEFSDMEMBER(T_STRING,  qualification   ,0),\
	APP_DEFSDMEMBER(T_STRING,  degree          ,0),\
	APP_DEFSDMEMBER(T_STRING,  address         ,0),\
	APP_DEFSDMEMBER(T_STRING,  reside_addr     ,0),\
	APP_DEFSDMEMBER(T_STRING,  mate_certp      ,0),\
	APP_DEFSDMEMBER(T_STRING,  mate_cerno      ,0),\
	APP_DEFSDMEMBER(T_STRING,  mate_name       ,0),\
	APP_DEFSDMEMBER(T_STRING,  mate_corp       ,0),\
	APP_DEFSDMEMBER(T_STRING,  mate_phone      ,0),\
	APP_DEFSDMEMBER(T_STRING,  addr            ,0),\
	APP_DEFSDMEMBER(T_STRING,  reside_state    ,0),\
	APP_DEFSDMEMBER(T_STRING,  comp_nm         ,0),\
	APP_DEFSDMEMBER(T_STRING,  comp_addr       ,0),\
	APP_DEFSDMEMBER(T_STRING,  profess         ,0),\
	APP_DEFSDMEMBER(T_STRING,  comp_trade      ,0),\
	APP_DEFSDMEMBER(T_STRING,  business        ,0),\
	APP_DEFSDMEMBER(T_STRING,  teach_pose      ,0),\
	APP_DEFSDMEMBER(T_STRING,  work_date       ,0),\
	APP_DEFSDMEMBER(T_STRING,  infodate        ,0),\
	APP_DEFSDMEMBER(T_STRING,  create_time     ,0),\
	APP_DEFSDMEMBER(T_STRING,  psb_query_date  ,0),\
	APP_DEFSDMEMBER(T_STRING,  reportsn        ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag   ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1   ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2   ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3   ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_PSB_PERSONAL_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_PSB_PERSONAL_INFO_H__*/
                                                                                                                                      
