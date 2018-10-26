/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_AGREEMENT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_AGREEMENT
˵    ��:Э���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_AGREEMENT_H__
#define __ICPS_WBC_TM_AGREEMENT_H__
typedef struct TDB_ICPS_WBC_TM_AGREEMENT
{
	char		busi_date[8+1];                        
	int			file_order;
	char		agreement_no[50+1];                      /*ƽ̨������            */
	char		merchant_id[20+1];                       /*ƽ̨ID                */
	char		product_cd[6+1];                         /*��ƷCD                */
	char		product_stcode[8+1];                     /*��Ʒ�ṹ����          */
	char		nbs_cust_id[20+1];                       /*NBS�ͻ�ID             */
	char		user_id[32+1];                           /*ƽ̨�Ŀͻ�ID          */
	char		cnc_card_no[20+1];                       /*�����              */
	char		debit_card_no[19+1];                     /*���н�ǿ���          */
	char		wb_debit_card_no[19+1];                  /*���н�ǿ���          */
	char		last_txn_status[4+1];                    /*��һ��ҵ��״̬        */
	char		txn_status[4+1];                         /*��ǰҵ��״̬          */
	char		last_native_staus[1+1];                  /*��һ����״̬          */
	char		native_staus[1+1];                       /*��ǰ����״̬          */
	char		billing_cycle[2+1];                      /*�˵�����              */
	char		first_stmt_date[8+1];                    /*�׸��˵���            */
	double		agreement_amt;                         /*Э����              */
	char		pct_id[32+1];                            /*���ۿ��Ʊ��          */
	double		fee_rate;                              /*��������              */
	double		interest_rate;                         /*��Ϣ����              */
	double		penalty_rate;                          /*��Ϣ����              */
	double		liquidated_damages;                    /*ΥԼ��                */
	int			curr_term;                                 /*��������              */
	char		curr_deduct_stage[1+1];                  /*��ǰ�ۿ�׶�          */
	char		deduct_stage_hst[50+1];                  /*�ۿ�׶���ʷ��¼      */
	double		credit_interest_rate;                  /*���ô�����            */
	double		credit_penalty_rate;                   /*���ô���Ϣ����        */ 
	char		credit_curr_deduct_stage[1+1];           /*���ô���ǰ�ۿ�׶�    */ 
	char		credit_deduct_stage_hst[5+1];            /*���ô��ۿ�׶���ʷ��¼*/ 
	char		master_card_flag[20+1];                  /*�������ʶ          */ 
	char		reserve1[20+1];                          /*�����ֶ�1             */ 
	char		reserve2[50+1];                          /*�����ֶ�2             */
	char		reserve3[50+1];                          /*�����ֶ�3             */
	char		biz_date[8+1];                           /*ҵ������              */
	char		created_datetime[14+1];                  /*����ʱ������          */
	char		last_modified_datetime[14+1];            /*����ʱ������          */
	int			loan_init_term;                            /*������                */
	char		order_type[2+1];                         /*��������              */
	char		fund_status[20+1];                       /*�ʽ�ռѹ״̬          */
	char		fee_curr_deduct_stage[1+1];              /*���ô���ǰ�ۿ�׶�    */
	double		profit_ratio;                          /*�������              */
	char		product_category[6+1];                   /*��Ʒ����              */
	char		fee_deduct_stage_hst[50+1];              /*���ô��ۿ�׶���ʷ��¼*/
	char		reserve4[50+1];                          /*�����ֶ�4             */
	char		reserve5[50+1];                          /*�����ֶ�5             */
	char		reserve6[50+1];                          /*�����ֶ�6             */
	char		reserve7[50+1];                          /*�����ֶ�7             */
	char		reserve8[50+1];                          /*�����ֶ�8             */
	char		reserve9[50+1];                          /*�����ֶ�9             */
	char		reserve10[50+1];                         /*�����ֶ�10            */
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
