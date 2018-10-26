/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_LOAN_YX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_LOAN_YX
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_LOAN_YX_H__
#define __ICPS_WBC_TM_LOAN_YX_H__
typedef struct TDB_ICPS_WBC_TM_LOAN_YX
{
	char		busi_date[8+1];              
	int			file_order; 
	char		loan_receipt_nbr[20+1];        /*��ݺ�                                      */
	char		merchant_id[20+1];             /*ƽ̨ID                                      */
	char		product_cd[6+1];               /*��ƷCD                                      */
	char		agreement_no[50+1];            /*ƽ̨Э���                                  */
	char		cnc_card_no[20+1];             /*�����                                    */
	int			loan_init_term;                /*������                                      */
	int			curr_term;                     /*��������                                    */
	int			remain_term;                   /*ʣ������                                    */
	double		interest_rate;                 /*��Ϣ����                                    */
	char		loan_status[1+1];              /*״̬                                        */
	double		loan_prin;                     /*�ܱ���                                      */
	double		loan_paid;                     /*�ѻ�����                                    */
	double		loan_init_interest;            /*����Ϣ                                      */
	double		int_paid;                      /*�ѻ���Ϣ                                    */
	char		loan_expire_date[8+1];         /*��������                                    */
	char		grace_date[8+1];               /*������                                      */
	int			due_days;                      /*��������                                    */
	char		loan_paidout_flg[1+1];         /*�����ʶ                                    */
	char		loan_paidout_date[8+1];        /*��������                                    */
	char		terminate_reason_cd[1+1];      /*��ֹԭ�����                                */
	char		batch_date[8+1];               /*����ͬ������                                */
	char		batch_no[16+1];                /*���κ�                                      */
	double		loan_bal_late_charge;          /*Ƿ�������ɽ�                                */
	double		loan_bal_adv_pmt_fee;          /*Ƿ������ǰ����������                        */
	double		loan_bal_fee;                  /*Ƿ���ܷ���                                  */
	double		late_charge_paid;              /*�ѻ����ɽ�                                  */
	double		adv_pmt_fee_paid;              /*�ѻ���ǰ����������                          */
	double		fee_paid;                      /*�ѻ�����                                    */
	double		next_prin;                     /*���ڱ���                                    */
	double		next_fee;                      /*����������                                  */
	char		register_date[8+1];            /*���ע������                                */
	double		prin_bal;                      /*Ƿ���ܱ���                                  */
	double		int_bal;                       /*Ƿ������Ϣ                                  */
	double		penalty_bal;                   /*Ƿ���ܷ�Ϣ                                  */
	double		penalty_paid;                  /*�ѻ���Ϣ                                    */
	double		penalty_rate;                  /*��Ϣ����                                    */
	char		biz_date[8+1];                 /*ҵ������                                    */
	char		created_datetime[14+1];        /*����ʱ������                                */
	char		last_modified_datetime[14+1];  /*����ʱ������                                */
	char		loan_type[20+1];               /*�������                                    */
	double		unearned_prin;                 /*δ���ڱ���                                  */
	char		inst_return_flag[1+1];         /*�Ƿ�����Ϣ                                  */
	char		paid_out_return_status[1+1];   /*�����˱���Ϣ״̬                            */
	char		ref_nbr[20+1];                 /*���׼�����                                  */
	char		loan_merge_type[20+1];         /*��ݺϲ�����                                */
	double		bef_init_interest;             /*ԭ��������Ϣ                                */
	int			orig_init_term;                /*ԭʼ��������                                */
	int			gl_term;                       /*�����������������������Ҫ���Ի������Լӹ�*/
	char		is_check_flag[1+1];
	char		extend_param1[100+1];
	char		extend_param2[250+1];
	char		extend_param3[40+1];
}ICPS_WBC_TM_LOAN_YX;

#define SD_DATA  ICPS_WBC_TM_LOAN_YX
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr        ,0),\
	APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd              ,0),\
	APP_DEFSDMEMBER(T_STRING,  agreement_no            ,0),\
	APP_DEFSDMEMBER(T_STRING,  cnc_card_no             ,0),\
	APP_DEFSDMEMBER(T_LONG,    loan_init_term          ,0),\
	APP_DEFSDMEMBER(T_LONG,    curr_term               ,0),\
	APP_DEFSDMEMBER(T_LONG,    remain_term             ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_rate           ,6),\
	APP_DEFSDMEMBER(T_STRING,  loan_status             ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_prin               ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_paid               ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_init_interest      ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_paid                ,2),\
	APP_DEFSDMEMBER(T_STRING,  loan_expire_date        ,0),\
	APP_DEFSDMEMBER(T_STRING,  grace_date              ,0),\
	APP_DEFSDMEMBER(T_LONG,    due_days                ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_paidout_flg        ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_paidout_date       ,0),\
	APP_DEFSDMEMBER(T_STRING,  terminate_reason_cd     ,0),\
	APP_DEFSDMEMBER(T_STRING,  batch_date              ,0),\
	APP_DEFSDMEMBER(T_STRING,  batch_no                ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_late_charge    ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_adv_pmt_fee    ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  loan_bal_fee            ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  late_charge_paid        ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  adv_pmt_fee_paid        ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  fee_paid                ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  next_prin               ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  next_fee                ,2),\
	APP_DEFSDMEMBER(T_STRING,  register_date           ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  prin_bal                ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  int_bal                 ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_bal             ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_paid            ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  penalty_rate            ,6),\
	APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_type               ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  unearned_prin           ,2),\
	APP_DEFSDMEMBER(T_STRING,  inst_return_flag        ,0),\
	APP_DEFSDMEMBER(T_STRING,  paid_out_return_status  ,0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  loan_merge_type         ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bef_init_interest       ,2),\
	APP_DEFSDMEMBER(T_LONG,    orig_init_term          ,0),\
	APP_DEFSDMEMBER(T_LONG,    gl_term                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_LOAN_YX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_LOAN_YX_H__*/
