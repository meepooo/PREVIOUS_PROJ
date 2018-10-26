/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:
文 件 名:ICPS_WBC_TM_PLAN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_PLAN
说    明:信用计划表
************************************************************************
修改记录:195
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_PLAN_H__
#define __ICPS_WBC_TM_PLAN_H__
typedef struct TDB_ICPS_WBC_TM_PLAN
{
  char         busi_date[8+1];                               
  int          file_order;
  char         org[12+1];                                      /*机构号                              */
  char         plan_id[20+1];                                  /*信用计划ID fuwd22392 modify         */
  char         acct_no[20+1];                                  /*账户编号   fuwd22392 modify           */
  char         acct_type[1+1];                                 /*账户类型                            */
  char         logical_card_no[19+1];                          /*逻辑卡号                            */
  char         plan_nbr[6+1];                                  /*信用计划号                          */
  char         plan_type[1+1];                                 /*信用计划类型                        */
  char         product_cd[6+1];                                /*产品代码                            */
  char         ref_nbr[23+1];                                  /*交易参考号                          */
  double       curr_bal;                                       /*当前余额                            */
  double       begin_bal;                                      /*期初余额                            */
  double       dispute_amt;                                    /*争议金额                            */
  double       tot_due_amt;                                    /*最小还款额                          */
  char         plan_add_date[8+1];                             /*信用计划建立日期                    */
  char         paid_out_date[8+1];                             /*还清日期                            */
  double       past_principal;                                 /*已出账单本金                        */
  double       past_interest;                                  /*已出账单利息                        */
  double       past_card_fee;                                  /*已出账单年费                        */
  double       past_ovrlmt_fee;                                /*已出账单超限费                      */
  double       past_lpc;                                       /*已出账单滞纳金                      */
  double       past_nsf_fee;                                   /*已出账单资金不足费                  */
  double       past_txn_fee;                                   /*已出账单交易费                      */
  double       past_svc_fee;                                   /*已出账单服务费                      */
  double       past_ins;                                       /*已出账单保险金额                    */
  double       past_user_fee1;                                 /*已出账单自定义费用1                 */
  double       past_user_fee2;                                 /*已出账单自定义费用2                 */
  double       past_user_fee3;                                 /*已出账单自定义费用3                 */
  double       past_user_fee4;                                 /*已出账单自定义费用4                 */
  double       past_user_fee5;                                 /*已出账单自定义费用5                 */
  double       past_user_fee6;                                 /*已出账单自定义费用6                 */
  double       ctd_principal;                                  /*当期本金                            */
  double       ctd_interest;                                   /*当期利息                            */
  double       ctd_card_fee;                                   /*当期年费                            */
  double       ctd_ovrlmt_fee;                                 /*当期超限费                          */
  double       ctd_lpc;                                        /*当期滞纳金                          */
  double       ctd_nsf_fee;                                    /*当期资金不足费                      */
  double       ctd_svc_fee;                                    /*当期服务费                          */
  double       ctd_txn_fee;                                    /*当期交易费                          */
  double       ctd_ins;                                        /*当期保险金额                        */
  double       ctd_user_fee1;                                  /*当期新增自定义费用1                 */
  double       ctd_user_fee2;                                  /*当期新增自定义费用2                 */
  double       ctd_user_fee3;                                  /*当期新增自定义费用3                 */
  double       ctd_user_fee4;                                  /*当期新增自定义费用4                 */
  double       ctd_user_fee5;                                  /*当期新增自定义费用5                 */
  double       ctd_user_fee6;                                  /*当期新增自定义费用6                 */
  double       ctd_amt_db;                                     /*当期借记金额                        */
  double       ctd_amt_cr;                                     /*当期贷记金额                        */
  int          ctd_nbr_db;                                     /*当期借记交易笔数                    */
  int          ctd_nbr_cr;                                     /*当期贷记交易笔数                    */
  double       nodefbnp_int_acru;                              /*非延迟利息                          */
  double       beg_defbnp_int_acru;                            /*往期累积延时利息                    */
  double       ctd_defbnp_int_acru;                            /*当期累积延时利息                    */
  char         user_code1[4+1];                                /*用户自定义代码1                     */
  char         user_code2[4+1];                                /*用户自定义代码2                     */
  char         user_code3[4+1];                                /*用户自定义代码3                     */
  char         user_code4[4+1];                                /*用户自定义代码4                     */
  char         user_code5[4+1];                                /*用户自定义代码5                     */
  char         user_code6[4+1];                                /*用户自定义代码6                     */
  int          user_number1;                                   /*用户自定义笔数1                     */
  int          user_number2;                                   /*用户自定义笔数2                     */
  int          user_number3;                                   /*用户自定义笔数3                     */
  int          user_number4;                                   /*用户自定义笔数4                     */
  int          user_number5;                                   /*用户自定义笔数5                     */
  int          user_number6;                                   /*用户自定义笔数6                     */
  char         user_field1[40+1];                              /*用户自定义域1                       */
  char         user_field2[40+1];                              /*用户自定义域2                       */
  char         user_field3[40+1];                              /*用户自定义域3                       */
  char         user_field4[40+1];                              /*用户自定义域4                       */
  char         user_field5[40+1];                              /*用户自定义域5                       */
  char         user_field6[40+1];                              /*用户自定义域6                       */
  char         user_date1[8+1];                                /*用户自定义日期1                     */
  char         user_date2[8+1];                                /*用户自定义日期2                     */
  char         user_date3[8+1];                                /*用户自定义日期3                     */
  char         user_date4[8+1];                                /*用户自定义日期4                     */
  char         user_date5[8+1];                                /*用户自定义日期5                     */
  char         user_date6[8+1];                                /*用户自定义日期6                     */
  double       user_amt1;                                      /*用户自定义金额1                     */
  double       user_amt2;                                      /*用户自定义金额2                     */
  double       user_amt3;                                      /*用户自定义金额3                     */
  double       user_amt4;                                      /*用户自定义金额4                     */
  double       user_amt5;                                      /*用户自定义金额5                     */
  double       user_amt6;                                      /*昨日贷记卡承诺余额                  */
  int          jpa_version;                                    /*乐观锁版本号                        */
  double       past_penalty;                                   /*往期罚息                            */
  double       ctd_penalty;                                    /*当期罚息                            */
  double       past_compound;                                  /*往期复利                            */
  double       ctd_compound;                                   /*当期复利                            */
  double       penalty_acru;                                   /*罚息累计                            */
  double       compound_acru;                                  /*复利累计                            */
  double       interest_rate;                                  /*基础利率                            */
  double       penalty_rate;                                   /*罚息利率                            */
  double       compound_rate;                                  /*复利利率                            */
  char         use_plan_rate[1+1];                             /*是否使用plan的利率                  */
  char         last_pmt_date[8+1];                             /*上一还款日期                        */
  int          term;                                           /*所在分期期数                        */
  char         calc_type[1+1];                                 /*计费类型                            */
  int          calc_cycle;                                     /*计费周期                            */
  double       fee_rate;                                       /*费率                                */
  char         last_fee_date[8+1];                             /*上一收费日                          */
  char         next_fee_date[8+1];                             /*下一收费日                          */
  char         txn_seq[20+1];                                        /*交易流水号                          */
  char         first_dd_date[8+1];                             /*首次约定还款日期                    */
  char         consumer_trans_id[32+1];                        /*业务流水号                          */
  char         sys_trans_id[32+1];                             /*系统调用流水号                      */
  char         qchannel_id[15+1];                              /*渠道编号                            */
  char         sub_terminal_type[15+1];                        /*终端类型                            */
  char         sub_merch_id[40+1];                             /*二级商户编码                        */
  char         sub_merch_name[60+1];                           /*二级商户名称                        */
  char         wares_desc[60+1];                               /*商品信息                            */
  char         last_modified_datetime[14+1];                   /*修改时间                            */
  double       original_amt;                                   /*原始交易本金                        */
  char         interest_calc_base[1+1];                        /*计息基数                            */
  char         created_datetime[14+1];                         /*创建时间                            */
  char         is_check_flag[1+1];
  char         extend_param1[100+1];
  char         extend_param2[250+1];
  char         extend_param3[40+1];
}ICPS_WBC_TM_PLAN;

#define SD_DATA  ICPS_WBC_TM_PLAN
#define SD_MEMBERS \ 
     APP_DEFSDMEMBER(T_STRING,             busi_date                       ,0),\
     APP_DEFSDMEMBER(T_LONG,               file_order                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             org                             ,0),\
     APP_DEFSDMEMBER(T_STRING,             plan_id                         ,0),\
     APP_DEFSDMEMBER(T_STRING,             acct_no                         ,0),\
     APP_DEFSDMEMBER(T_STRING,             acct_type                       ,0),\
     APP_DEFSDMEMBER(T_STRING,             logical_card_no                 ,0),\
     APP_DEFSDMEMBER(T_STRING,             plan_nbr                        ,0),\
     APP_DEFSDMEMBER(T_STRING,             plan_type                       ,0),\
     APP_DEFSDMEMBER(T_STRING,             product_cd                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             ref_nbr                         ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             curr_bal                        ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             begin_bal                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             dispute_amt                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             tot_due_amt                     ,2),\
     APP_DEFSDMEMBER(T_STRING,             plan_add_date                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             paid_out_date                   ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_principal                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_interest                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_card_fee                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_ovrlmt_fee                 ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_lpc                        ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_nsf_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_txn_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_svc_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_ins                        ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee1                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee2                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee3                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee4                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee5                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_user_fee6                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_principal                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_interest                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_card_fee                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_ovrlmt_fee                  ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_lpc                         ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_nsf_fee                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_svc_fee                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_txn_fee                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_ins                         ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee1                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee2                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee3                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee4                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee5                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_user_fee6                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_amt_db                      ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_amt_cr                      ,2),\
     APP_DEFSDMEMBER(T_LONG,               ctd_nbr_db                      ,0),\
     APP_DEFSDMEMBER(T_LONG,               ctd_nbr_cr                      ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             nodefbnp_int_acru               ,4),\
     APP_DEFSDMEMBER(T_DOUBLE,             beg_defbnp_int_acru             ,4),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_defbnp_int_acru             ,4),\
     APP_DEFSDMEMBER(T_STRING,             user_code1                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code2                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code3                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code4                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code5                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_code6                      ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number1                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number2                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number3                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number4                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number5                    ,0),\
     APP_DEFSDMEMBER(T_LONG,               user_number6                    ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field1                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field2                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field3                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field4                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field5                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_field6                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date1                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date2                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date3                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date4                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date5                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             user_date6                      ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt1                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt2                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt3                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt4                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt5                       ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             user_amt6                       ,0),\
     APP_DEFSDMEMBER(T_LONG,               jpa_version                     ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_penalty                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_penalty                     ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             past_compound                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             ctd_compound                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             penalty_acru                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             compound_acru                   ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             interest_rate                   ,4),\
     APP_DEFSDMEMBER(T_DOUBLE,             penalty_rate                    ,2),\
     APP_DEFSDMEMBER(T_DOUBLE,             compound_rate                   ,2),\
     APP_DEFSDMEMBER(T_STRING,             use_plan_rate                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             last_pmt_date                   ,0),\
     APP_DEFSDMEMBER(T_LONG,               term                            ,0),\
     APP_DEFSDMEMBER(T_STRING,             calc_type                       ,0),\
     APP_DEFSDMEMBER(T_LONG,               calc_cycle                      ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             fee_rate                        ,2),\
     APP_DEFSDMEMBER(T_STRING,             last_fee_date                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             next_fee_date                   ,0),\
     APP_DEFSDMEMBER(T_LONG,               txn_seq                         ,0),\
     APP_DEFSDMEMBER(T_STRING,             first_dd_date                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             consumer_trans_id               ,0),\
     APP_DEFSDMEMBER(T_STRING,             sys_trans_id                    ,0),\
     APP_DEFSDMEMBER(T_STRING,             qchannel_id                     ,0),\
     APP_DEFSDMEMBER(T_STRING,             sub_terminal_type               ,0),\
     APP_DEFSDMEMBER(T_STRING,             sub_merch_id                    ,0),\
     APP_DEFSDMEMBER(T_STRING,             sub_merch_name                  ,0),\
     APP_DEFSDMEMBER(T_STRING,             wares_desc                      ,0),\
     APP_DEFSDMEMBER(T_STRING,             last_modified_datetime          ,0),\
     APP_DEFSDMEMBER(T_DOUBLE,             original_amt                    ,4),\
     APP_DEFSDMEMBER(T_STRING,             interest_calc_base              ,0),\
     APP_DEFSDMEMBER(T_STRING,             created_datetime                ,0),\
     APP_DEFSDMEMBER(T_STRING,             is_check_flag                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             extend_param1                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             extend_param2                   ,0),\
     APP_DEFSDMEMBER(T_STRING,             extend_param3                   ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_PLAN)
#undef SD_DATA
#undef SD_MEMBERS

#endif
