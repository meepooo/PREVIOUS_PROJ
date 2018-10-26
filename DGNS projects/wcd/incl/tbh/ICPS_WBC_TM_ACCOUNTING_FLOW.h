 /***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_ACCOUNTING_FLOW.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_ACCOUNTING_FLOW
说    明:会计分录日报表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_ACCOUNTING_FLOW_H__
#define __ICPS_WBC_TM_ACCOUNTING_FLOW_H__
typedef struct TDB_ICPS_WBC_TM_ACCOUNTING_FLOW
{
 
    char            busi_date[8+1];        /*              */
    int             file_order;            /*              */
    char            org[12+1];             /*内部机构号    */
    char            cps_txn_seq[36+1];     /*核心交易流水  */
    char            card_no[19+1];         /*卡号          */
    char            curr_cd[3+1];          /*币种          */
    char            txn_code[4+1];         /*交易码        */
    char            txn_desc[80+1];        /*交易描述      */
    char            db_cr_ind[1+1];        /*借贷标记      */
    double          post_amt;              /*入账金额      */
    char            post_gl_ind[1+1];      /*入账方式      */
    char            owning_branch[9+1];    /*支行          */
    char            subject[40+1];         /*科目          */
    char            red_flag[1+1];         /*红蓝字标识    */
    char            queue[20+1];                 /*排序 fuwd22392 M        */
    char            product_cd[6+1];       /*产品号        */
    char            ref_nbr[23+1];         /*借据号        */
    char            age_group[1+1];        /*账龄组        */
    char            plan_nbr[6+1];         /*信用计划号    */
    char            bnp_group[2+1];        /*余额成分组    */
    char            bank_group_id[5+1];    /*银团代码      */
    char            bank_no[10+1];         /*银行代码      */
    int             term;                  /*期数          */
    char            batchdate[14+1];        /*批量          */
    char            is_check_flag[1+1];    /*              */
    char            extend_param1[100+1];  /*              */
    char            extend_param2[250+1];  /*              */
	char			extend_param3[40+1];
}ICPS_WBC_TM_ACCOUNTING_FLOW;
#define SD_DATA  ICPS_WBC_TM_ACCOUNTING_FLOW
#define SD_MEMBERS \ 
      APP_DEFSDMEMBER(T_STRING,  busi_date      ,0),\
      APP_DEFSDMEMBER(T_LONG,    file_order     ,0),\
      APP_DEFSDMEMBER(T_STRING,  org            ,0),\
      APP_DEFSDMEMBER(T_STRING,  cps_txn_seq    ,0),\
      APP_DEFSDMEMBER(T_STRING,  card_no        ,0),\
      APP_DEFSDMEMBER(T_STRING,  curr_cd        ,0),\
      APP_DEFSDMEMBER(T_STRING,  txn_code       ,0),\
      APP_DEFSDMEMBER(T_STRING,  txn_desc       ,0),\
      APP_DEFSDMEMBER(T_STRING,  db_cr_ind      ,0),\
      APP_DEFSDMEMBER(T_DOUBLE,  post_amt       ,2),\
      APP_DEFSDMEMBER(T_STRING,  post_gl_ind    ,0),\
      APP_DEFSDMEMBER(T_STRING,  owning_branch  ,0),\
      APP_DEFSDMEMBER(T_STRING,  subject        ,0),\
      APP_DEFSDMEMBER(T_STRING,  red_flag       ,0),\
      APP_DEFSDMEMBER(T_STRING,    queue          ,0),\
      APP_DEFSDMEMBER(T_STRING,  product_cd     ,0),\
      APP_DEFSDMEMBER(T_STRING,  ref_nbr        ,0),\
      APP_DEFSDMEMBER(T_STRING,  age_group      ,0),\
      APP_DEFSDMEMBER(T_STRING,  plan_nbr       ,0),\
      APP_DEFSDMEMBER(T_STRING,  bnp_group      ,0),\
      APP_DEFSDMEMBER(T_STRING,  bank_group_id  ,0),\
      APP_DEFSDMEMBER(T_STRING,  bank_no        ,0),\
      APP_DEFSDMEMBER(T_LONG,    term           ,0),\
      APP_DEFSDMEMBER(T_STRING,  batchdate      ,0),\
      APP_DEFSDMEMBER(T_STRING,  is_check_flag  ,0),\
      APP_DEFSDMEMBER(T_STRING,  extend_param1  ,0),\
      APP_DEFSDMEMBER(T_STRING,  extend_param2  ,0),\
	  APP_DEFSDMEMBER(T_STRING,  extend_param3  ,0)
      APP_DECLAREFIELDS(SD_ICPS_WBC_TM_ACCOUNTING_FLOW)   
    #undef SD_DATA                               
    #undef SD_MEMBERS                            
                                             
    #endif  /*end of __ICPS_WBC_TM_ACCOUNTING_FLOW_H__*/
