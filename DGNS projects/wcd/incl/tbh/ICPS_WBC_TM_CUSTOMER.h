/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WBC_TM_CUSTOMER.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_CUSTOMER
说    明:
************************************************************************
修改记录:195
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/

#ifndef __ICPS_WBC_TM_CUSTOMER_H__
#define __ICPS_WBC_TM_CUSTOMER_H__
typedef struct TDB_ICPS_WBC_TM_CUSTOMER
{
   char       busi_date[8+1];                                   
   int        file_order;                                             
   char       org[12+1];                              /*机构号                             */
   char       cust_id[20+1];                          /*客户编号fuwd22392 modify   */
   char       id_no[30+1];                            /*证件号码                           */
   char       id_type[1+1];                           /*证件类型                           */
   char       title[1+1];                             /*称谓                               */
   char       name[80+1];                             /*姓名                               */
   char       gender[1+1];                            /*性别                               */
   char       birthday[8+1];                          /*生日                               */
   char       occupation[1+1];                        /*职业                               */
   char       bankmember_no[20+1];                    /*本行员工号                         */
   char       nationality[3+1];                       /*国籍                               */
   char       pr_of_country[1+1];                     /*是否永久居住                       */
   char       residency_country_cd[3+1];              /*永久居住地国家代码                 */
   char       marital_status[1+1];                    /*婚姻状况                           */
   char       qualification[1+1];                     /*教育状况                           */
   char       social_status[1+1];                     /*风险情况                           */
   char       id_issuer_address[200+1];               /*发证机关所在地址                   */
   char       home_phone[20+1];                       /*家庭电话                           */
   char       house_ownership[1+1];                   /*房屋持有类型                       */
   char       house_type[1+1];                        /*住宅类型                           */
   char       home_stand_from[8+1];                   /*现住址居住起始年月                 */
   char       liquid_asset[1+1];                      /*个人资产类型                       */
   char       mobile_no[20+1];                        /*移动电话                           */
   char       email[80+1];                            /*电子邮箱                           */
   char       emp_status[1+1];                        /*就业状态                           */
   int        nbr_of_dependents;                       /*抚养人数                           */
   char       language_ind[4+1];                      /*语言代码                           */
   char       setup_date[8+1];                        /*创建日期                           */
   double     social_ins_amt;                         /*社保缴存金额                       */
   char       drive_license_id[20+1];                 /*驾驶证号码                         */
   char       drive_lic_reg_date[8+1];                /*驾驶证登记日期                     */
   char       obligate_question[80+1];                /*预留问题                           */
   char       obligate_answer[80+1];                  /*预留答案                           */
   char       emp_stability[1+1];                     /*工作稳定性                         */
   char       corp_name[200+1];                       /*公司名称                           */
   char       user_code1[4+1];                        /*用户自定义代码1                    */
   char       user_code2[4+1];                        /*用户自定义代码2                    */
   char       user_code3[4+1];                        /*用户自定义代码3                    */
   char       user_code4[4+1];                        /*用户自定义代码4                    */
   char       user_code5[4+1];                        /*用户自定义代码5                    */
   char       user_code6[4+1];                        /*用户自定义代码6                    */
   char       user_date1[8+1];                        /*用户自定义日期1                    */
   char       user_date2[8+1];                        /*用户自定义日期2                    */
   char       user_date3[8+1];                        /*用户自定义日期3                    */
   char       user_date4[8+1];                        /*用户自定义日期4                    */
   char       user_date5[8+1];                        /*用户自定义日期5                    */
   char       user_date6[8+1];                        /*用户自定义日期6                    */
   int        user_number1;                           /*用户自定义笔数1                    */
   int        user_number2;                           /*用户自定义笔数2                    */
   int        user_number3;                           /*用户自定义笔数3                    */
   int        user_number4;                           /*用户自定义笔数4                    */
   int        user_number5;                           /*用户自定义笔数5                    */
   int        user_number6;                           /*用户自定义笔数6                    */
   char       user_field1[40+1];                      /*用户自定义域1                      */
   char       user_field2[40+1];                      /*用户自定义域2                      */
   char       user_field3[40+1];                      /*用户自定义域3                      */
   char       user_field4[40+1];                      /*用户自定义域4                      */
   char       user_field5[40+1];                      /*用户自定义域5                      */
   char       user_field6[40+1];                      /*用户自定义域6                      */
   double     user_amt1;                              /*用户自定义金额1                    */
   double     user_amt2;                              /*用户自定义金额2                    */
   double     user_amt3;                              /*用户自定义金额3                    */
   double     user_amt4;                              /*用户自定义金额4                    */
   double     user_amt5;                              /*用户自定义金额5                    */
   double     user_amt6;                              /*昨日贷记卡承诺余额                 */
   char       bank_customer_id[20+1];                 /*行内统一用户号                     */
   char       emb_name[26+1];                         /*凸印姓名                           */
   int        jpa_version;                            /*乐观锁版本号                       */
   char       cust_limit_id[20+1];                    /*客户额度ID fuwd22392 modify         */
   char       last_modified_datetime[14+1];           /*修改时间                           */
   char       cust_level[10+1];                       /*客户等级                           */
   char       pledeg_type[2+1];                       /*押品类型                           */
   char       surname[20+1];                          /*姓氏                               */
   char       created_datetime[14+1];                 /*创建时间                           */
   char       customer_type[3+1];                     /*客群分类                           */
   char       block_code[53+1];                       /*锁定码                             */
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
