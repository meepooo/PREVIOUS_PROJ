/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_MERCHANT_CUST.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_MERCHANT_CUST
˵    ��:ƽ̨�ͻ���Ϣ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_MERCHANT_CUST_H__
#define __ICPS_WBC_TM_MERCHANT_CUST_H__
typedef struct TDB_ICPS_WBC_TM_MERCHANT_CUST
{
	char			busi_date[8+1];                  
	int				file_order;                     
	char			user_id[32+1];                   /*ƽ̨�Ŀͻ�ID         */
	char			merchant_id[20+1];               /*ƽ̨ID               */
	char			nbs_cust_id[20+1];               /*NBS�ͻ�ID            */
	char			user_name[60+1];                 /*ƽ̨ע��Ŀͻ�����   */
	char			user_mobile[20+1];               /*ƽ̨�Ǽǵ��û��ֻ��� */
	char			apply_datetime[14+1];            /*ƽ̨ID����ʱ��       */
	char			reg_mobile[20+1];                /*ע���ֻ���           */
	char			qq_openid[32+1];                 /*QQ_OPENID            */
	char			wx_openid[32+1];                 /*WX_OPENID            */
	char			login_id[32+1];                  /*΢��WEB��¼ID        */
	char			company_name[60+1];              /*��λ����             */
	char			company_phone[20+1];             /*��λ�绰             */
	char			address[60+1];                   /*��ס��ַ             */
	char			contact_name[40+1];              /*��ϵ������           */
	char			contact_phone[20+1];             /*��ϵ���ֻ���         */
	char			contact_relation[10+1];          /*��ϵ�˹�ϵ           */
	char			reserve1[20+1];                  /*�����ֶ�1            */
	char			reserve2[50+1];                  /*�����ֶ�2            */
	char			reserve3[50+1];                  /*�����ֶ�3            */
	char			biz_date[8+1];                   /*ҵ������             */
	char			created_datetime[14+1];          /*����ʱ������         */
	char			last_modified_datetime[14+1];    /*����ʱ������         */
	char			contact_addr[80+1];              /*��ϵ�˵�ַ           */
	char			contact_id_no[30+1];             /*��ϵ�����֤��       */
	char			co_licenses[80+1];               /*Ӫҵִ�պ�           */
	char			driver_license[30+1];            /*��ʻ֤����           */
	char			company_addr[80+1];              /*��˾��ַ             */
	char			home_phone[20+1];                /*��ͥ�̻�����         */
	char			occupation[60+1];                /*ְҵ                 */
	double			ss_ave_amt_mtly;               /*ÿ���籣ƽ���ɽ���� */
	double			salary_ave_mtly;               /*ÿ��ƽ�����ʽ�����ˮ */
	char			is_home_visited[1+1];            /*���޼ҷ�             */
	char			house_info[80+1];                /*������Ϣ             */
	char			mer_apply_result[1+1];           /*�������             */
	char			mer_apply_view[80+1];            /*�������             */
	char			mer_refuse_reason[10+1];         /*�ܾ�ԭ�����         */
	char			cust_value[2014+1];              /*�ͻ���Ϣ�����ֶΣ�   */
	char			is_guarantor[1+1];               /*���޵�����           */
	char			is_check_flag[1+1];              /*                     */
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_MERCHANT_CUST;

#define SD_DATA  ICPS_WBC_TM_MERCHANT_CUST
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
  APP_DEFSDMEMBER(T_STRING,  user_id                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
  APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
  APP_DEFSDMEMBER(T_STRING,  user_name               ,0),\
  APP_DEFSDMEMBER(T_STRING,  user_mobile             ,0),\
  APP_DEFSDMEMBER(T_STRING,  apply_datetime          ,0),\
  APP_DEFSDMEMBER(T_STRING,  reg_mobile              ,0),\
  APP_DEFSDMEMBER(T_STRING,  qq_openid               ,0),\
  APP_DEFSDMEMBER(T_STRING,  wx_openid               ,0),\
  APP_DEFSDMEMBER(T_STRING,  login_id                ,0),\
  APP_DEFSDMEMBER(T_STRING,  company_name            ,0),\
  APP_DEFSDMEMBER(T_STRING,  company_phone           ,0),\
  APP_DEFSDMEMBER(T_STRING,  address                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_name            ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_phone           ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_relation        ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve1                ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve2                ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve3                ,0),\
  APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
  APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_addr            ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_id_no           ,0),\
  APP_DEFSDMEMBER(T_STRING,  co_licenses             ,0),\
  APP_DEFSDMEMBER(T_STRING,  driver_license          ,0),\
  APP_DEFSDMEMBER(T_STRING,  company_addr            ,0),\
  APP_DEFSDMEMBER(T_STRING,  home_phone              ,0),\
  APP_DEFSDMEMBER(T_STRING,  occupation              ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  ss_ave_amt_mtly         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,  salary_ave_mtly         ,2),\
  APP_DEFSDMEMBER(T_STRING,  is_home_visited         ,0),\
  APP_DEFSDMEMBER(T_STRING,  house_info              ,0),\
  APP_DEFSDMEMBER(T_STRING,  mer_apply_result        ,0),\
  APP_DEFSDMEMBER(T_STRING,  mer_apply_view          ,0),\
  APP_DEFSDMEMBER(T_STRING,  mer_refuse_reason       ,0),\
  APP_DEFSDMEMBER(T_STRING,  cust_value              ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_guarantor            ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_MERCHANT_CUST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_MERCHANT_CUST_H__*/
                                                                                                                                                      
