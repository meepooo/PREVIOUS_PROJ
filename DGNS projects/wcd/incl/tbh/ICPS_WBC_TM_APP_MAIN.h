/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WBC_TM_APP_MAIN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[liaohw21982]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_APP_MAIN
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_APP_MAIN_H__
#define __ICPS_WBC_TM_APP_MAIN_H__
typedef struct TDB_ICPS_WBC_TM_APP_MAIN
{
  char     busi_date[8+1];                        /*业务日期                       */
  int      file_order;                            /*文件序号                       */
  char     org[12+1];                             /*机构号                         */
  char     app_no[20+1];                          /*申请件编号                     */
  char     app_type[1+1];                         /*申请类型                       */
  double   app_lmt;                               /*申请额度                       */
  double   sug_lmt;                               /*系统建议额度                   */
  double   acc_lmt;                               /*核准额度                       */
  char     product_cd[6+1];                       /*卡产品代码                     */
  double   business_limit;                        /*商务卡额度                     */
  double   micro_loan_limit;                      /*小额贷款额度                   */
  double   vehicle_loan;                          /*专项额度车贷                   */
  double   house_loan;                            /*专项额度房贷                   */
  double   renovation_loan;                       /*专项额度装修贷                 */
  double   travel_loan;                           /*专项额度旅游贷                 */
  double   wedding_loan;                          /*专项额度婚庆贷                 */
  double   durable_loan;                          /*专项额度耐消贷                 */
  char     priority[1+1];                         /*客户等级                       */
  char     client_type[3+1];                      /*客户类型                       */
  char     approve_quick_flag[1+1];               /*快速审批标志                   */
  char     busns_num[20+1];                       /*公司编号                       */
  char     rtf_state[3+1];                        /*审批状态                       */
  int      point_result;                          /*评分值                         */
  double   cust_rate_discount;                    /*客户利率浮动比例               */
  char     pro_num[20+1];                         /*流程实例号                     */
  char     pro_name[400+1];                       /*流程节点名称                   */
  char     refuse_code[1000+1];                   /*拒绝原因码                     */
  int      answer_err_cnt;                        /*问题回答错误次数               */
  char     is_clt[1+1];                           /*是否集体件                     */
  char     spreader_num[20+1];                    /*推广人编号                     */
  char     spreader_org[20+1];                    /*推广机构                       */
  char     spreader_bank[9+1];                    /*推广人所属分行                 */
  char     spreader_way[20+1];                    /*推广方式                       */
  char     spreader_type[1+1];                    /*推广渠道                       */
  char     spreader_name[80+1];                   /*推广人姓名                     */
  char     spreader_num_pre[20+1];                /*推广单位预审人编号             */
  char     spreader_phone[20+1];                  /*推广人手机号码                 */
  char     sales_ind[1+1];                        /*是否接受推广邮件               */
  char     owning_branch[9+1];                    /*发卡网点                       */
  char     app_promotion_cd[15+1];                /*促销码                         */
  char     app_source[20+1];                      /*申请来源                       */
  char     bank_customer_id[32+1];                /*行内客户号                     */
  char     dd_flag[1+1];                          /*约定扣款是否开通标识           */
  char     deduct_deal_no[40+1];                  /*自扣协议号                     */
  char     if_refuse[1+1];                        /*是否拒绝                       */
  char     if_end[1+1];                           /*是否处理完成件                 */
  char     apply_from_type[1+1];                  /*申请来源类别                   */
  char     appno_external[20+1];                  /*申请编号_外部送入              */
  char     appno_attach_external[20+1];           /*附卡申请编号_外部送入          */
  char     remark[400+1];                         /*备注                           */
  char     create_user[40+1];                     /*创建人                         */
  char     update_user[40+1];                     /*修改人                         */
  char     biz_no[32+1];                          /*业务流水号                     */
  char     trace_no[32+1];                        /*调起方流水号                   */
  char     called_no[32+1];                       /*被调方流水号                   */
  char     result_code[10+1];                     /*审批结果码                     */
  char     created_datetime[14+1];                /*创建时间                       */
  char     last_modified_datetime[14+1];          /*最后修改时间                   */
  int      jpa_version;                           /*乐观锁                         */
  char     is_shared_credit_limit[1+1];           /*是否共享额度                   */
  char     approval_datetime[14+1];               /*审批通过时间                   */
  char     is_check_flag[1+1];                    /*参与对账标识                   */
  char     extend_param1[100+1];                  /*扩展1                          */
  char     extend_param2[250+1];                  /*扩展2                          */
  char     extend_param3[40+1];                   /*扩展3                          */

}ICPS_WBC_TM_APP_MAIN;

#define SD_DATA  ICPS_WBC_TM_APP_MAIN
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,       busi_date             ,0),\
  APP_DEFSDMEMBER(T_LONG,         file_order            ,0),\
  APP_DEFSDMEMBER(T_STRING,       org                   ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_no                ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_type              ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,       app_lmt               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       sug_lmt               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       acc_lmt               ,2),\
  APP_DEFSDMEMBER(T_STRING,       product_cd            ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,       business_limit        ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       micro_loan_limit      ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       vehicle_loan          ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       house_loan            ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       renovation_loan       ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       travel_loan           ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       wedding_loan          ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,       durable_loan          ,2),\
  APP_DEFSDMEMBER(T_STRING,       priority              ,0),\
  APP_DEFSDMEMBER(T_STRING,       client_type           ,0),\
  APP_DEFSDMEMBER(T_STRING,       approve_quick_flag    ,0),\
  APP_DEFSDMEMBER(T_STRING,       busns_num             ,0),\
  APP_DEFSDMEMBER(T_STRING,       rtf_state             ,0),\
  APP_DEFSDMEMBER(T_LONG,         point_result          ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,       cust_rate_discount    ,4),\
  APP_DEFSDMEMBER(T_STRING,       pro_num               ,0),\
  APP_DEFSDMEMBER(T_STRING,       pro_name              ,0),\
  APP_DEFSDMEMBER(T_STRING,       refuse_code           ,0),\
  APP_DEFSDMEMBER(T_LONG,         answer_err_cnt        ,0),\
  APP_DEFSDMEMBER(T_STRING,       is_clt                ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_num          ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_org          ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_bank         ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_way          ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_type         ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_name         ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_num_pre      ,0),\
  APP_DEFSDMEMBER(T_STRING,       spreader_phone        ,0),\
  APP_DEFSDMEMBER(T_STRING,       sales_ind             ,0),\
  APP_DEFSDMEMBER(T_STRING,       owning_branch         ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_promotion_cd      ,0),\
  APP_DEFSDMEMBER(T_STRING,       app_source            ,0),\
  APP_DEFSDMEMBER(T_STRING,       bank_customer_id      ,0),\
  APP_DEFSDMEMBER(T_STRING,       dd_flag               ,0),\
  APP_DEFSDMEMBER(T_STRING,       deduct_deal_no        ,0),\
  APP_DEFSDMEMBER(T_STRING,       if_refuse             ,0),\
  APP_DEFSDMEMBER(T_STRING,       if_end                ,0),\
  APP_DEFSDMEMBER(T_STRING,       apply_from_type       ,0),\
  APP_DEFSDMEMBER(T_STRING,       appno_external        ,0),\
  APP_DEFSDMEMBER(T_STRING,       appno_attach_external ,0),\
  APP_DEFSDMEMBER(T_STRING,       remark                ,0),\
  APP_DEFSDMEMBER(T_STRING,       create_user           ,0),\
  APP_DEFSDMEMBER(T_STRING,       update_user           ,0),\
  APP_DEFSDMEMBER(T_STRING,       biz_no                ,0),\
  APP_DEFSDMEMBER(T_STRING,       trace_no              ,0),\
  APP_DEFSDMEMBER(T_STRING,       called_no             ,0),\
  APP_DEFSDMEMBER(T_STRING,       result_code           ,0),\
  APP_DEFSDMEMBER(T_STRING,       created_datetime      ,0),\
  APP_DEFSDMEMBER(T_STRING,       last_modified_datetime,0),\
  APP_DEFSDMEMBER(T_LONG,         jpa_version           ,0),\
  APP_DEFSDMEMBER(T_STRING,       is_shared_credit_limit,0),\
  APP_DEFSDMEMBER(T_STRING,       approval_datetime     ,0),\
  APP_DEFSDMEMBER(T_STRING,       is_check_flag         ,0),\
  APP_DEFSDMEMBER(T_STRING,       extend_param1         ,0),\
  APP_DEFSDMEMBER(T_STRING,       extend_param2         ,0),\
  APP_DEFSDMEMBER(T_STRING,       extend_param3         ,0)

  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_APP_MAIN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_APP_MAIN_H__*/
