/********************************************************************i
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WBC_TM_APP_MAIN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��: ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO
˵    ��:������������Ϣ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO_H__
#define __ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO_H__
typedef struct TDB_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO
{
 char         busi_date[8+1];                        /*ҵ������                       */
 int          file_order;                            /*�ļ����                       */
 char         id[20+1];                                    /*��ʶ*/
 char         org[12+1];                             /*������              */
 char         app_no[20+1];                          /*��������          */
 char         if_selected_card[1+1];                 /*�Ƿ���ѡ����        */
 char         card_no[19+1];                         /*����                */
 char         name[80+1];                            /*����                */
 char         emb_logo[30+1];                        /*͹ӡ����            */
 char         gender[2+1];                           /*�Ա�                */
 char         nationality[3+1];                      /*����                */
 char         residency_country_cd[3+1];             /*���þ�ס�ع��Ҵ���  */
 char         id_type[1+1];                          /*֤������            */
 char         id_no[18+1];                           /*֤������            */
 char         id_last_date[8+1];                     /*֤��������          */
 char         id_issuer_address[200+1];              /*��֤�������ڵ�ַ    */
 char         birthday[8+1];                         /*����                */
 char         liquid_asset[1+1];                     /*�����ʲ�����        */
 double       year_income;                          /*������              */
 char         qualification[1+1];                   /*����״��            */
 char         marital_status[1+1];                  /*����״��            */
 char         home_addr_ctry_cd[3+1];               /*��ͥ���Ҵ���        */
 char         home_state[40+1];                     /*��ͥ����ʡ          */
 char         home_city[40+1];                      /*��ͥ������          */
 char         home_zone[40+1];                      /*��ͥ��������        */
 char         house_ownership[1+1];                 /*���ݳ�������        */
 char         home_add[200+1];                      /*��ͥ��ַ            */
 char         home_postcode[10+1];                  /*��ͥסլ�ʱ�        */
 char         home_phone[20+1];                     /*��ͥ�绰            */
 char         home_stand_from[8+1];                 /*��סַ��ס��ʼ����  */
 char         cellphone[20+1];                      /*�ƶ��绰            */
 char         email[80+1];                          /*��������            */
 char         qq_acct[40+1];                        /*QQ�˺�              */
 char         open_id[40+1];                        /*���ں�              */
 char         house_type[1+1];                      /*סլ����            */
 char         family_member[2+1];                   /*��ͥ�˿�            */
 double       family_avge_venue;                    /*��ͥ�˾�������      */
 char         bankmem_flag[1+1];                     /*�Ƿ�����Ա��        */
 char         bankmember_no[20+1];                    /*����Ա����          */
 char         corp_name[200+1];                                  /*��˾����            */
 char         emp_addr_ctry_cd[3+1];                           /*��˾���Ҵ���        */
 char         emp_province[40+1];                               /*��˾����ʡ          */
 char         emp_city[40+1];                                   /*��˾������          */
 char         emp_zone[40+1];                                   /*��˾������/��       */
 char         emp_add[200+1];                                    /*��˾��ַ            */
 char         emp_postcode[10+1];                               /*��˾�ʱ�            */
 char         emp_phone[20+1];                                  /*��˾�绰            */
 char         emp_depapment[80+1];                              /*��ְ����            */
 char         emp_post[1+1];                                   /*ְ��                */
 char         emp_structure[1+1];                              /*��˾����            */
 char         emp_type[1+1];                                   /*��˾��ҵ���        */
 double       emp_workyears;                              /*����˾��������      */
 char         corp_fax[20+1];                                   /*��˾����            */
 char         occupation[1+1];                                 /*ְҵ                */
 char         title_of_technical[1+1];                         /*ְ��                */
 char         emp_stand_from[8+1];                             /*�ֵ�λ������ʼ����  */
 char         pos_pin_verify_ind[1+1];                         /*�Ƿ�����ƾ��        */
 char         photo_use_flag[1+1];                             /*�Ƿ���տ�          */
 char         group_num[10+1];                                  /*�����Ű���        */
 char         emp_stability[1+1];                              /*�����ȶ���          */
 char         emp_status[1+1];                                 /*�Ƿ���ְ            */
 char         pr_of_country[1+1];                              /*�Ƿ����þ�ס        */
 char         other_ask[80+1];                                  /*Ԥ������            */
 char         other_answer[80+1];                               /*Ԥ����            */
 char         pri_name[80+1];                                   /*�Ƽ�������          */
 char         pri_card_num[19+1];                               /*�Ƽ��˿���          */
 char         appno_external[20+1];                             /*������_�ⲿ����   */
 char         bank_customer_id[32+1];                           /*���ڿͻ���          */
 char         ref_contact_id[40+1];                             /*�Ƽ�����ϵ����      */
 char         ref_contact_type[1+1];                           /*�Ƽ�����ϵ��������  */
 char         pledeg_type[2+1];                                /*ѺƷ����            */
 char         update_user[40+1];                                /*�޸���              */
 char         create_user[40+1];                                /*������              */
 char         created_datetime[14+1];                           /*����ʱ��            */
 char         last_modified_datetime[14+1];                     /*����޸�ʱ��        */
 int          jpa_version;                                /*�ֹ���              */
 char         cust_no[19+1];                                    /*�ͻ��� fuwd22392 Modify*/
 char         acct_no[19+1];                                    /*�˻��� fuwd22392 Modify */
 char         product_cd[6+1];                                 /*��Ʒ���            */
 char         open_acc_datetime[14+1];                          /*����ʱ��            */
 char         is_check_flag[1+1];                                /*���˱�־*/
 char         extend_param1[100+1];                               /*��չ�ֶ�*/
 char         extend_param2[250+1];                              /*��չ�ֶ�*/ 
 char         extend_param3[40+1];                               /*��չ�ֶ�*/
}ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO;

 #define SD_DATA  ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO                                                                            
 #define SD_MEMBERS \                  
  APP_DEFSDMEMBER(T_STRING,    busi_date                       ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order                      ,0),\
  APP_DEFSDMEMBER(T_STRING,    id                              ,0),\
  APP_DEFSDMEMBER(T_STRING,    org                             ,0),\
  APP_DEFSDMEMBER(T_STRING,    app_no                          ,0),\
  APP_DEFSDMEMBER(T_STRING,    if_selected_card                ,0),\
  APP_DEFSDMEMBER(T_STRING,    card_no                         ,0),\
  APP_DEFSDMEMBER(T_STRING,    name                            ,0),\
  APP_DEFSDMEMBER(T_STRING,    emb_logo                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    gender                          ,0),\
  APP_DEFSDMEMBER(T_STRING,    nationality                     ,0),\
  APP_DEFSDMEMBER(T_STRING,    residency_country_cd            ,0),\
  APP_DEFSDMEMBER(T_STRING,    id_type                         ,0),\
  APP_DEFSDMEMBER(T_STRING,    id_no                           ,0),\
  APP_DEFSDMEMBER(T_STRING,    id_last_date                    ,0),\
  APP_DEFSDMEMBER(T_STRING,    id_issuer_address               ,0),\
  APP_DEFSDMEMBER(T_STRING,    birthday                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    liquid_asset                    ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,    year_income                     ,2),\
  APP_DEFSDMEMBER(T_STRING,    qualification                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    marital_status                  ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_addr_ctry_cd               ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_state                      ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_city                       ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_zone                       ,0),\
  APP_DEFSDMEMBER(T_STRING,    house_ownership                 ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_add                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_postcode                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_phone                      ,0),\
  APP_DEFSDMEMBER(T_STRING,    home_stand_from                 ,0),\
  APP_DEFSDMEMBER(T_STRING,    cellphone                       ,0),\
  APP_DEFSDMEMBER(T_STRING,    email                           ,0),\
  APP_DEFSDMEMBER(T_STRING,    qq_acct                         ,0),\
  APP_DEFSDMEMBER(T_STRING,    open_id                         ,0),\
  APP_DEFSDMEMBER(T_STRING,    house_type                      ,0),\
  APP_DEFSDMEMBER(T_STRING,    family_member                   ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,    family_avge_venue               ,2),\
  APP_DEFSDMEMBER(T_STRING,    bankmem_flag                    ,0),\
  APP_DEFSDMEMBER(T_STRING,    bankmember_no                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    corp_name                       ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_addr_ctry_cd                ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_province                    ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_city                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_zone                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_add                         ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_postcode                    ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_phone                       ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_depapment                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_post                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_structure                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_type                        ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,    emp_workyears                   ,2),\
  APP_DEFSDMEMBER(T_STRING,    corp_fax                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    occupation                      ,0),\
  APP_DEFSDMEMBER(T_STRING,    title_of_technical              ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_stand_from                  ,0),\
  APP_DEFSDMEMBER(T_STRING,    pos_pin_verify_ind              ,0),\
  APP_DEFSDMEMBER(T_STRING,    photo_use_flag                  ,0),\
  APP_DEFSDMEMBER(T_STRING,    group_num                       ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_stability                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    emp_status                      ,0),\
  APP_DEFSDMEMBER(T_STRING,    pr_of_country                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    other_ask                       ,0),\
  APP_DEFSDMEMBER(T_STRING,    other_answer                    ,0),\
  APP_DEFSDMEMBER(T_STRING,    pri_name                        ,0),\
  APP_DEFSDMEMBER(T_STRING,    pri_card_num                    ,0),\
  APP_DEFSDMEMBER(T_STRING,    appno_external                  ,0),\
  APP_DEFSDMEMBER(T_STRING,    bank_customer_id                ,0),\
  APP_DEFSDMEMBER(T_STRING,    ref_contact_id                  ,0),\
  APP_DEFSDMEMBER(T_STRING,    ref_contact_type                ,0),\
  APP_DEFSDMEMBER(T_STRING,    pledeg_type                     ,0),\
  APP_DEFSDMEMBER(T_STRING,    update_user                     ,0),\
  APP_DEFSDMEMBER(T_STRING,    create_user                     ,0),\
  APP_DEFSDMEMBER(T_STRING,    created_datetime                ,0),\
  APP_DEFSDMEMBER(T_STRING,    last_modified_datetime          ,0),\
  APP_DEFSDMEMBER(T_LONG,    jpa_version                     ,0),\
  APP_DEFSDMEMBER(T_STRING,    cust_no                         ,0),\
  APP_DEFSDMEMBER(T_STRING,    acct_no                         ,0),\
  APP_DEFSDMEMBER(T_STRING,    product_cd                      ,0),\
  APP_DEFSDMEMBER(T_STRING,    open_acc_datetime               ,0),\
  APP_DEFSDMEMBER(T_STRING,    is_check_flag                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    extend_param1                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    extend_param2                   ,0),\
  APP_DEFSDMEMBER(T_STRING,    extend_param3                   ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO_H__*/                                                    
