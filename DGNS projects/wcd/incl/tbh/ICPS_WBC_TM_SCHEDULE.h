/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WBC_TM_SCHEDULE.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd2239]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_SCHEDULE
说    明:贷款分配表
************************************************************************
修改记录:195
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_SCHEDULE_H__
#define __ICPS_WBC_TM_SCHEDULE_H__
typedef struct TDB_ICPS_WBC_TM_SCHEDULE
{
		char		busi_date[8+1];                       /*                      */
		int			file_order;                           /*                      */
		char		schedule_id[20+1];                    /* 分配表ID  fuwd22392           */
		char		loan_id[20+1];                        /* 分期计划ID  fuwd22392         */
		char		org[12+1];                            /* 机构号               */
		char		acct_no[20+1];                              /* 账户编号 fuwd22392            */
		char		acct_type[1+1];                     /* 账户类型             */
		char		logical_card_no[19+1];                /* 逻辑卡号             */
		char		card_no[19+1];                        /* 卡号                 */
		double		loan_init_prin;                       /* 分期总本金           */
		int			loan_init_term;                       /* 分期总期数           */
		int			curr_term;                            /* 当前期数             */
		double		loan_term_prin;                       /* 应还本金             */
		double		loan_term_fee1;                       /* 应还费用             */
		double		loan_term_interest;                   /* 应还利息             */
		char		loan_pmt_due_date[8+1];             /* 到款到期还款日期     */
		char		loan_grace_date[8+1];               /* 宽限日               */
		char		last_modified_datetime[14+1];         /* 修改时间             */
		char		start_date[8+1];                     /* 起息日               */
		char		schedule_action[1+1];               /* 还款计划操作动作     */
		double		prin_paid;                            /* 已偿还本金           */
		double		int_paid;                             /* 已偿还利息           */
		double		penalty_paid;                         /* 已偿还罚息           */
		double		compound_paid;                        /* 已偿还复利           */
		double		fee_paid;                             /* 已偿还费用           */
		double		late_charge_paid;                     /* 已偿还滞纳金         */
		double		adv_pmt_fee_paid;                     /* 已偿还提前还款手续费 */
		char		paid_out_date[8+1];                   /* 还清日期             */
		char		is_check_flag[1+1];                   /*                      */
		char		extend_param1[100+1];               /*                      */
		char		extend_param2[250+1];               /*                      */
		char		extend_param3[40+1];                 /*                      */
}ICPS_WBC_TM_SCHEDULE;
#define SD_DATA  ICPS_WBC_TM_SCHEDULE
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,	busi_date                   ,0),\
  APP_DEFSDMEMBER(T_LONG,	file_order                  ,0),\
  APP_DEFSDMEMBER(T_STRING,	schedule_id                 ,0),\
  APP_DEFSDMEMBER(T_STRING,	loan_id                     ,0),\
  APP_DEFSDMEMBER(T_STRING,	org                         ,0),\
  APP_DEFSDMEMBER(T_STRING,	acct_no                     ,0),\
  APP_DEFSDMEMBER(T_STRING,	acct_type                   ,0),\
  APP_DEFSDMEMBER(T_STRING,	logical_card_no             ,0),\
  APP_DEFSDMEMBER(T_STRING,	card_no                     ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,	loan_init_prin              ,2),\
  APP_DEFSDMEMBER(T_LONG,	loan_init_term              ,0),\
  APP_DEFSDMEMBER(T_LONG,	curr_term                   ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,	loan_term_prin              ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	loan_term_fee1              ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	loan_term_interest          ,2),\
  APP_DEFSDMEMBER(T_STRING,	loan_pmt_due_date           ,0),\
  APP_DEFSDMEMBER(T_STRING,	loan_grace_date             ,0),\
  APP_DEFSDMEMBER(T_STRING,	last_modified_datetime      ,0),\
  APP_DEFSDMEMBER(T_STRING,	start_date                  ,0),\
  APP_DEFSDMEMBER(T_STRING,	schedule_action             ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,	prin_paid                   ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	int_paid                    ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	penalty_paid                ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	compound_paid               ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	fee_paid                    ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	late_charge_paid            ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,	adv_pmt_fee_paid            ,2),\
  APP_DEFSDMEMBER(T_STRING,	paid_out_date               ,0),\
  APP_DEFSDMEMBER(T_STRING,	is_check_flag               ,0),\
  APP_DEFSDMEMBER(T_STRING,	extend_param1               ,0),\
  APP_DEFSDMEMBER(T_STRING,	extend_param2               ,0),\
  APP_DEFSDMEMBER(T_STRING,	extend_param3               ,0)
        
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_SCHEDULE)
#undef SD_DATA
#undef SD_MEMBERS

#endif /*end of __ICPS_WBC_TM_SCHEDULE_H__*/                                  
