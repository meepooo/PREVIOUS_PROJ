/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WBC_TM_CUSTOMER.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_CUSTOMER
˵    ��:
************************************************************************
�޸ļ�¼:195
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/

#ifndef __ICPS_WBC_TM_CUSTOMER_H__
#define __ICPS_WBC_TM_CUSTOMER_H__
typedef struct TDB_ICPS_WBC_TM_CUSTOMER
{
   char       busi_date[8+1];                                   
   int        file_order;                                             
   char       org[12+1];                              /*������                             */
   char       cust_id[20+1];                          /*�ͻ����fuwd22392 modify   */
   char       id_no[30+1];                            /*֤������                           */
   char       id_type[1+1];                           /*֤������                           */
   char       title[1+1];                             /*��ν                               */
   char       name[80+1];                             /*����                               */
   char       gender[1+1];                            /*�Ա�                               */
   char       birthday[8+1];                          /*����                               */
   char       occupation[1+1];                        /*ְҵ                               */
   char       bankmember_no[20+1];                    /*����Ա����                         */
   char       nationality[3+1];                       /*����                               */
   char       pr_of_country[1+1];                     /*�Ƿ����þ�ס                       */
   char       residency_country_cd[3+1];              /*���þ�ס�ع��Ҵ���                 */
   char       marital_status[1+1];                    /*����״��                           */
   char       qualification[1+1];                     /*����״��                           */
   char       social_status[1+1];                     /*�������                           */
   char       id_issuer_address[200+1];               /*��֤�������ڵ�ַ                   */
   char       home_phone[20+1];                       /*��ͥ�绰                           */
   char       house_ownership[1+1];                   /*���ݳ�������                       */
   char       house_type[1+1];                        /*סլ����                           */
   char       home_stand_from[8+1];                   /*��סַ��ס��ʼ����                 */
   char       liquid_asset[1+1];                      /*�����ʲ�����                       */
   char       mobile_no[20+1];                        /*�ƶ��绰                           */
   char       email[80+1];                            /*��������                           */
   char       emp_status[1+1];                        /*��ҵ״̬                           */
   int        nbr_of_dependents;                       /*��������                           */
   char       language_ind[4+1];                      /*���Դ���                           */
   char       setup_date[8+1];                        /*��������                           */
   double     social_ins_amt;                         /*�籣�ɴ���                       */
   char       drive_license_id[20+1];                 /*��ʻ֤����                         */
   char       drive_lic_reg_date[8+1];                /*��ʻ֤�Ǽ�����                     */
   char       obligate_question[80+1];                /*Ԥ������                           */
   char       obligate_answer[80+1];                  /*Ԥ����                           */
   char       emp_stability[1+1];                     /*�����ȶ���                         */
   char       corp_name[200+1];                       /*��˾����                           */
   char       user_code1[4+1];                        /*�û��Զ������1                    */
   char       user_code2[4+1];                        /*�û��Զ������2                    */
   char       user_code3[4+1];                        /*�û��Զ������3                    */
   char       user_code4[4+1];                        /*�û��Զ������4                    */
   char       user_code5[4+1];                        /*�û��Զ������5                    */
   char       user_code6[4+1];                        /*�û��Զ������6                    */
   char       user_date1[8+1];                        /*�û��Զ�������1                    */
   char       user_date2[8+1];                        /*�û��Զ�������2                    */
   char       user_date3[8+1];                        /*�û��Զ�������3                    */
   char       user_date4[8+1];                        /*�û��Զ�������4                    */
   char       user_date5[8+1];                        /*�û��Զ�������5                    */
   char       user_date6[8+1];                        /*�û��Զ�������6                    */
   int        user_number1;                           /*�û��Զ������1                    */
   int        user_number2;                           /*�û��Զ������2                    */
   int        user_number3;                           /*�û��Զ������3                    */
   int        user_number4;                           /*�û��Զ������4                    */
   int        user_number5;                           /*�û��Զ������5                    */
   int        user_number6;                           /*�û��Զ������6                    */
   char       user_field1[40+1];                      /*�û��Զ�����1                      */
   char       user_field2[40+1];                      /*�û��Զ�����2                      */
   char       user_field3[40+1];                      /*�û��Զ�����3                      */
   char       user_field4[40+1];                      /*�û��Զ�����4                      */
   char       user_field5[40+1];                      /*�û��Զ�����5                      */
   char       user_field6[40+1];                      /*�û��Զ�����6                      */
   double     user_amt1;                              /*�û��Զ�����1                    */
   double     user_amt2;                              /*�û��Զ�����2                    */
   double     user_amt3;                              /*�û��Զ�����3                    */
   double     user_amt4;                              /*�û��Զ�����4                    */
   double     user_amt5;                              /*�û��Զ�����5                    */
   double     user_amt6;                              /*���մ��ǿ���ŵ���                 */
   char       bank_customer_id[20+1];                 /*����ͳһ�û���                     */
   char       emb_name[26+1];                         /*͹ӡ����                           */
   int        jpa_version;                            /*�ֹ����汾��                       */
   char       cust_limit_id[20+1];                    /*�ͻ����ID fuwd22392 modify         */
   char       last_modified_datetime[14+1];           /*�޸�ʱ��                           */
   char       cust_level[10+1];                       /*�ͻ��ȼ�                           */
   char       pledeg_type[2+1];                       /*ѺƷ����                           */
   char       surname[20+1];                          /*����                               */
   char       created_datetime[14+1];                 /*����ʱ��                           */
   char       customer_type[3+1];                     /*��Ⱥ����                           */
   char       block_code[53+1];                       /*������                             */
   char       is_check_flag[1+1];           
   char       extend_param1[100+1];         
   char       extend_param2[250+1];         
   char       extend_param3[40+1];
 }ICPS_WBC_TM_CUSTOMER;
 
 #define SD_DATA  ICPS_WBC_TM_CUSTOMER                                     
 #define SD_MEMBERS \                                            
   APP_DEFSDMEMBER(T_STRING,   busi_date                ,0),\
   APP_DEFSDMEMBER(T_LONG,   file_order               ,0),\
   APP_DEFSDMEMBER(T_STRING,   org                      ,0),\
   APP_DEFSDMEMBER(T_STRING,   cust_id                  ,0),\
   APP_DEFSDMEMBER(T_STRING,   id_no                    ,0),\
   APP_DEFSDMEMBER(T_STRING,   id_type                  ,0),\
   APP_DEFSDMEMBER(T_STRING,   title                    ,0),\
   APP_DEFSDMEMBER(T_STRING,   name                     ,0),\
   APP_DEFSDMEMBER(T_STRING,   gender                   ,0),\
   APP_DEFSDMEMBER(T_STRING,   birthday                 ,0),\
   APP_DEFSDMEMBER(T_STRING,   occupation               ,0),\
   APP_DEFSDMEMBER(T_STRING,   bankmember_no            ,0),\
   APP_DEFSDMEMBER(T_STRING,   nationality              ,0),\
   APP_DEFSDMEMBER(T_STRING,   pr_of_country            ,0),\
   APP_DEFSDMEMBER(T_STRING,   residency_country_cd     ,0),\
   APP_DEFSDMEMBER(T_STRING,   marital_status           ,0),\
   APP_DEFSDMEMBER(T_STRING,   qualification            ,0),\
   APP_DEFSDMEMBER(T_STRING,   social_status            ,0),\
   APP_DEFSDMEMBER(T_STRING,   id_issuer_address        ,0),\
   APP_DEFSDMEMBER(T_STRING,   home_phone               ,0),\
   APP_DEFSDMEMBER(T_STRING,   house_ownership          ,0),\
   APP_DEFSDMEMBER(T_STRING,   house_type               ,0),\
   APP_DEFSDMEMBER(T_STRING,   home_stand_from          ,0),\
   APP_DEFSDMEMBER(T_STRING,   liquid_asset             ,0),\
   APP_DEFSDMEMBER(T_STRING,   mobile_no                ,0),\
   APP_DEFSDMEMBER(T_STRING,   email                    ,0),\
   APP_DEFSDMEMBER(T_STRING,   emp_status               ,0),\
   APP_DEFSDMEMBER(T_LONG,   nbr_of_dependents        ,0),\
   APP_DEFSDMEMBER(T_STRING,   language_ind             ,0),\
   APP_DEFSDMEMBER(T_STRING,   setup_date               ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,   social_ins_amt           ,2),\
   APP_DEFSDMEMBER(T_STRING,   drive_license_id         ,0),\
   APP_DEFSDMEMBER(T_STRING,   drive_lic_reg_date       ,0),\
   APP_DEFSDMEMBER(T_STRING,   obligate_question        ,0),\
   APP_DEFSDMEMBER(T_STRING,   obligate_answer          ,0),\
   APP_DEFSDMEMBER(T_STRING,   emp_stability            ,0),\
   APP_DEFSDMEMBER(T_STRING,   corp_name                ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_code1               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_code2               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_code3               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_code4               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_code5               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_code6               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_date1               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_date2               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_date3               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_date4               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_date5               ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_date6               ,0),\
   APP_DEFSDMEMBER(T_LONG,   user_number1             ,0),\
   APP_DEFSDMEMBER(T_LONG,   user_number2             ,0),\
   APP_DEFSDMEMBER(T_LONG,   user_number3             ,0),\
   APP_DEFSDMEMBER(T_LONG,   user_number4             ,0),\
   APP_DEFSDMEMBER(T_LONG,   user_number5             ,0),\
   APP_DEFSDMEMBER(T_LONG,   user_number6             ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_field1              ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_field2              ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_field3              ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_field4              ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_field5              ,0),\
   APP_DEFSDMEMBER(T_STRING,   user_field6              ,0),\
   APP_DEFSDMEMBER(T_DOUBLE,   user_amt1                ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,   user_amt2                ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,   user_amt3                ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,   user_amt4                ,2),\
   APP_DEFSDMEMBER(T_DOUBLE,   user_amt5                ,2),\                   
   APP_DEFSDMEMBER(T_DOUBLE,   user_amt6                ,2),\
   APP_DEFSDMEMBER(T_STRING,   bank_customer_id         ,0),\
   APP_DEFSDMEMBER(T_STRING,   emb_name                 ,0),\
   APP_DEFSDMEMBER(T_LONG,   jpa_version              ,0),\
   APP_DEFSDMEMBER(T_STRING,   cust_limit_id            ,0),\
   APP_DEFSDMEMBER(T_STRING,   last_modified_datetime   ,0),\
   APP_DEFSDMEMBER(T_STRING,   cust_level               ,0),\
   APP_DEFSDMEMBER(T_STRING,   pledeg_type              ,0),\
   APP_DEFSDMEMBER(T_STRING,   surname                  ,0),\
   APP_DEFSDMEMBER(T_STRING,   created_datetime         ,0),\
   APP_DEFSDMEMBER(T_STRING,   customer_type            ,0),\
   APP_DEFSDMEMBER(T_STRING,   block_code               ,0),\
   APP_DEFSDMEMBER(T_STRING,   is_check_flag            ,0),\
   APP_DEFSDMEMBER(T_STRING,   extend_param1            ,0),\
   APP_DEFSDMEMBER(T_STRING,   extend_param2            ,0),\
   APP_DEFSDMEMBER(T_STRING,   extend_param3            ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_CUSTOMER)
#undef SD_DATA
#undef SD_MEMBERS

#endif /*end of ICPS_WBC_TM_CUSSTOMER.h*/                                 
