/********************************************************************i
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WBC_TM_APP_MAIN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名: ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO
说    明:主卡申请人信息表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO_H__
#define __ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO_H__
typedef struct TDB_ICPS_WBC_TM_APP_PRIM_APPLICANT_INFO
{
 char         busi_date[8+1];                        /*业务日期                       */
 int          file_order;                            /*文件序号                       */
 char         id[20+1];                                    /*标识*/
 char         org[12+1];                             /*机构号              */
 char         app_no[20+1];                          /*申请件编号          */
 char         if_selected_card[1+1];                 /*是否自选卡号        */
 char         card_no[19+1];                         /*卡号                */
 char         name[80+1];                            /*姓名                */
 char         emb_logo[30+1];                        /*凸印名称            */
 char         gender[2+1];                           /*性别                */
 char         nationality[3+1];                      /*国籍                */
 char         residency_country_cd[3+1];             /*永久居住地国家代码  */
 char         id_type[1+1];                          /*证件类型            */
 char         id_no[18+1];                           /*证件号码            */
 char         id_last_date[8+1];                     /*证件到期日          */
 char         id_issuer_address[200+1];              /*发证机关所在地址    */
 char         birthday[8+1];                         /*生日                */
 char         liquid_asset[1+1];                     /*个人资产类型        */
 double       year_income;                          /*年收入              */
 char         qualification[1+1];                   /*教育状况            */
 char         marital_status[1+1];                  /*婚姻状况            */
 char         home_addr_ctry_cd[3+1];               /*家庭国家代码        */
 char         home_state[40+1];                     /*家庭所在省          */
 char         home_city[40+1];                      /*家庭所在市          */
 char         home_zone[40+1];                      /*家庭所在区县        */
 char         house_ownership[1+1];                 /*房屋持有类型        */
 char         home_add[200+1];                      /*家庭地址            */
 char         home_postcode[10+1];                  /*家庭住宅邮编        */
 char         home_phone[20+1];                     /*家庭电话            */
 char         home_stand_from[8+1];                 /*现住址居住起始年月  */
 char         cellphone[20+1];                      /*移动电话            */
 char         email[80+1];                          /*电子邮箱            */
 char         qq_acct[40+1];                        /*QQ账号              */
 char         open_id[40+1];                        /*公众号              */
 char         house_type[1+1];                      /*住宅类型            */
 char         family_member[2+1];                   /*家庭人口            */
 double       family_avge_venue;                    /*家庭人均年收入      */
 char         bankmem_flag[1+1];                     /*是否行内员工        */
 char         bankmember_no[20+1];                    /*本行员工号          */
 char         corp_name[200+1];                                  /*公司名称            */
 char         emp_addr_ctry_cd[3+1];                           /*公司国家代码        */
 char         emp_province[40+1];                               /*公司所在省          */
 char         emp_city[40+1];                                   /*公司所在市          */
 char         emp_zone[40+1];                                   /*公司所在区/县       */
 char         emp_add[200+1];                                    /*公司地址            */
 char         emp_postcode[10+1];                               /*公司邮编            */
 char         emp_phone[20+1];                                  /*公司电话            */
 char         emp_depapment[80+1];                              /*任职部门            */
 char         emp_post[1+1];                                   /*职务                */
 char         emp_structure[1+1];                              /*公司性质            */
 char         emp_type[1+1];                                   /*公司行业类别        */
 double       emp_workyears;                              /*本公司工作年限      */
 char         corp_fax[20+1];                                   /*公司传真            */
 char         occupation[1+1];                                 /*职业                */
 char         title_of_technical[1+1];                         /*职称                */
 char         emp_stand_from[8+1];                             /*现单位工作起始年月  */
 char         pos_pin_verify_ind[1+1];                         /*是否消费凭密        */
 char         photo_use_flag[1+1];                             /*是否彩照卡          */
 char         group_num[10+1];                                  /*申请团办编号        */
 char         emp_stability[1+1];                              /*工作稳定性          */
 char         emp_status[1+1];                                 /*是否在职            */
 char         pr_of_country[1+1];                              /*是否永久居住        */
 char         other_ask[80+1];                                  /*预留问题            */
 char         other_answer[80+1];                               /*预留答案            */
 char         pri_name[80+1];                                   /*推荐人姓名          */
 char         pri_card_num[19+1];                               /*推荐人卡号          */
 char         appno_external[20+1];                             /*申请编号_外部送入   */
 char         bank_customer_id[32+1];                           /*行内客户号          */
 char         ref_contact_id[40+1];                             /*推荐人联系号码      */
 char         ref_contact_type[1+1];                           /*推荐人联系号码类型  */
 char         pledeg_type[2+1];                                /*押品类型            */
 char         update_user[40+1];                                /*修改人              */
 char         create_user[40+1];                                /*创建人              */
 char         created_datetime[14+1];                           /*创建时间            */
 char         last_modified_datetime[14+1];                     /*最后修改时间        */
 int          jpa_version;                                /*乐观锁              */
 char         cust_no[19+1];                                    /*客户号 fuwd22392 Modify*/
 char         acct_no[19+1];                                    /*账户号 fuwd22392 Modify */
 char         product_cd[6+1];                                 /*产品编号            */
 char         open_acc_datetime[14+1];                          /*开户时间            */
 char         is_check_flag[1+1];                                /*对账标志*/
 char         extend_param1[100+1];                               /*扩展字段*/
 char         extend_param2[250+1];                              /*扩展字段*/ 
 char         extend_param3[40+1];                               /*扩展字段*/
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
