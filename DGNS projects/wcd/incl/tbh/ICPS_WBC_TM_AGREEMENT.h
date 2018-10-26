/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_AGREEMENT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_AGREEMENT
说    明:协议表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_AGREEMENT_H__
#define __ICPS_WBC_TM_AGREEMENT_H__
typedef struct TDB_ICPS_WBC_TM_AGREEMENT
{
	char		busi_date[8+1];                        
	int			file_order;
	char		agreement_no[50+1];                      /*平台订单号            */
	char		merchant_id[20+1];                       /*平台ID                */
	char		product_cd[6+1];                         /*产品CD                */
	char		product_stcode[8+1];                     /*产品结构代码          */
	char		nbs_cust_id[20+1];                       /*NBS客户ID             */
	char		user_id[32+1];                           /*平台的客户ID          */
	char		cnc_card_no[20+1];                       /*贷款卡号              */
	char		debit_card_no[19+1];                     /*他行借记卡号          */
	char		wb_debit_card_no[19+1];                  /*本行借记卡号          */
	char		last_txn_status[4+1];                    /*上一个业务状态        */
	char		txn_status[4+1];                         /*当前业务状态          */
	char		last_native_staus[1+1];                  /*上一处理状态          */
	char		native_staus[1+1];                       /*当前处理状态          */
	char		billing_cycle[2+1];                      /*账单周期              */
	char		first_stmt_date[8+1];                    /*首个账单日            */
	double		agreement_amt;                         /*协议金额              */
	char		pct_id[32+1];                            /*定价控制编号          */
	double		fee_rate;                              /*费用利率              */
	double		interest_rate;                         /*利息利率              */
	double		penalty_rate;                          /*罚息利率              */
	double		liquidated_damages;                    /*违约金                */
	int			curr_term;                                 /*当期期数              */
	char		curr_deduct_stage[1+1];                  /*当前扣款阶段          */
	char		deduct_stage_hst[50+1];                  /*扣款阶段历史记录      */
	double		credit_interest_rate;                  /*信用贷利率            */
	double		credit_penalty_rate;                   /*信用贷罚息利率        */ 
	char		credit_curr_deduct_stage[1+1];           /*信用贷当前扣款阶段    */ 
	char		credit_deduct_stage_hst[5+1];            /*信用贷扣款阶段历史记录*/ 
	char		master_card_flag[20+1];                  /*主还款卡标识          */ 
	char		reserve1[20+1];                          /*保留字段1             */ 
	char		reserve2[50+1];                          /*保留字段2             */
	char		reserve3[50+1];                          /*保留字段3             */
	char		biz_date[8+1];                           /*业务日期              */
	char		created_datetime[14+1];                  /*创建时间日期          */
	char		last_modified_datetime[14+1];            /*更新时间日期          */
	int			loan_init_term;                            /*总期数                */
	char		order_type[2+1];                         /*订单类型              */
	char		fund_status[20+1];                       /*资金占压状态          */
	char		fee_curr_deduct_stage[1+1];              /*费用贷当前扣款阶段    */
	double		profit_ratio;                          /*分润比例              */
	char		product_category[6+1];                   /*产品大类              */
	char		fee_deduct_stage_hst[50+1];              /*费用贷扣款阶段历史记录*/
	char		reserve4[50+1];                          /*保留字段4             */
	char		reserve5[50+1];                          /*保留字段5             */
	char		reserve6[50+1];                          /*保留字段6             */
	char		reserve7[50+1];                          /*保留字段7             */
	char		reserve8[50+1];                          /*保留字段8             */
	char		reserve9[50+1];                          /*保留字段9             */
	char		reserve10[50+1];                         /*保留字段10            */
	char		is_check_flag[1+1];
	char		extend_param1[100+1];
	char		extend_param2[250+1];
	char		extend_param3[40+1];
}ICPS_WBC_TM_AGREEMENT;

#define SD_DATA  ICPS_WBC_TM_AGREEMENT
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date                 ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order                ,0),\
  APP_DEFSDMEMBER(T_STRING,  agreement_no              ,0),\
  APP_DEFSDMEMBER(T_STRING,  merchant_id               ,0),\
  APP_DEFSDMEMBER(T_STRING,  product_cd                ,0),\
  APP_DEFSDMEMBER(T_STRING,  product_stcode            ,0),\
  APP_DEFSDMEMBER(T_STRING,  nbs_cust_id               ,0),\
  APP_DEFSDMEMBER(T_STRING,  user_id                   ,0),\
  APP_DEFSDMEMBER(T_STRING,  cnc_card_no               ,0),\
  APP_DEFSDMEMBER(T_STRING,  debit_card_no             ,0),\
  APP_DEFSDMEMBER(T_STRING,  wb_debit_card_no          ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_txn_status           ,0),\
  APP_DEFSDMEMBER(T_STRING,  txn_status                ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_native_staus         ,0),\
  APP_DEFSDMEMBER(T_STRING,  native_staus              ,0),\
  APP_DEFSDMEMBER(T_STRING,  billing_cycle             ,0),\
  APP_DEFSDMEMBER(T_STRING,  first_stmt_date           ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  agreement_amt             ,2),\
  APP_DEFSDMEMBER(T_STRING,  pct_id                    ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  fee_rate                  ,6),\
  APP_DEFSDMEMBER(T_DOUBLE,  interest_rate             ,6),\
  APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate              ,6),\
  APP_DEFSDMEMBER(T_DOUBLE,  liquidated_damages        ,2),\
  APP_DEFSDMEMBER(T_LONG,    curr_term                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  curr_deduct_stage         ,0),\
  APP_DEFSDMEMBER(T_STRING,  deduct_stage_hst          ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  credit_interest_rate      ,6),\
  APP_DEFSDMEMBER(T_DOUBLE,  credit_penalty_rate       ,6),\
  APP_DEFSDMEMBER(T_STRING,  credit_curr_deduct_stage  ,0),\
  APP_DEFSDMEMBER(T_STRING,  credit_deduct_stage_hst   ,0),\
  APP_DEFSDMEMBER(T_STRING,  master_card_flag          ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve1                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve2                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve3                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  biz_date                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  created_datetime          ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_modified_datetime    ,0),\
  APP_DEFSDMEMBER(T_LONG,    loan_init_term            ,0),\
  APP_DEFSDMEMBER(T_STRING,  order_type                ,0),\
  APP_DEFSDMEMBER(T_STRING,  fund_status               ,0),\
  APP_DEFSDMEMBER(T_STRING,  fee_curr_deduct_stage     ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  profit_ratio              ,8),\
  APP_DEFSDMEMBER(T_STRING,  product_category          ,0),\
  APP_DEFSDMEMBER(T_STRING,  fee_deduct_stage_hst      ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve4                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve5                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve6                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve7                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve8                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve9                  ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve10                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag             ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1             ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2             ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3             ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_AGREEMENT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_AGREEMENT_H__*/
