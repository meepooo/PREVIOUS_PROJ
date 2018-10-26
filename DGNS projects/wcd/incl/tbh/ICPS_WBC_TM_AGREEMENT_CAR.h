/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_AGREEMENT_CAR.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_AGREEMENT_CAR
˵    ��:Э�鸽�ӱ�(��)
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_AGREEMENT_CAR_H__
#define __ICPS_WBC_TM_AGREEMENT_CAR_H__
typedef struct TDB_ICPS_WBC_TM_AGREEMENT_CAR
{
	char		busi_date[8+1];                
	int			file_order;         
	char		agreement_no[50+1];                    /*ƽ̨������          */
	char		merchant_id[20+1];                     /*ƽ̨ID��            */
	char		product_cd[50+1];                      /*��Ʒ��              */
	char		mer_order_no[50+1];                    /*ƽ̨Э���          */
	char		is_new_car[1+1];                       /*�Ƿ��³�            */
	char		car_id[21+1];                          /*����ID              */
	double		car_price;                             /*�������ۼ�          */
	double		car_inquiry_price;                     /*�ⲿ����Դ��ѯ��    */
	double		assess_amount;                         /*������ֵ            */
	char		assess_time[8+1];                      /*��������ʱ��        */
	char		assess_class[5+1];                     /*������⼶��        */
	char		registrate_time[14+1];                 /*��������            */
	char		vehicle_id[32+1];                      /*�������ܺ�          */
	char		engine_no[32+1];                       /*��������            */
	char		mileage[20+1];                               /*��ʻ��� fuwd22392 Modify    */
	char		xfr_times[20+1];                             /*��������fuwd22392 Modify            */
	char		coty[20+1];                                  /*����    fuwd22392 Modify            */
	char		motorcycle_type[30+1];                 /*��������            */
	char		ins_expire_date[14+1];                 /*���յ�����          */
	char		dealer_id[32+1];                       /*����ID              */
	char		dealer_name[32+1];                     /*����                */
	char		is_stage_guarantee_dealer[1+1];        /*�Ƿ�׶��Ե�������  */
	char		car_name[20+1];                        /*��������            */
	char		is_second_hand_car[1+1];               /*�Ƿ���ֳ�          */
	double		car_actual_price;                      /*����ʵ�ʳɽ���      */
	double		down_payment;                          /*�׸��ܽ��          */
	char		car_context[3000+1];                   /*������Ϣ            */
	char		driver_license[30+1];                  /*��ʻ֤����          */
	char		home_phone[20+1];                      /*��ͥ�̻�����        */
	char		occupation[60+1];                      /*ְҵ                */
	double		ss_ave_amt_mtly;                       /*ÿ���籣ƽ���ɽ����*/
	double		salary_ave_mtly;                       /*ÿ��ƽ�����ʽ�����ˮ*/
	char		is_home_visited[1+1];                  /*���޼ҷ�            */
	char		house_info[80+1];                      /*������Ϣ            */
	char		mer_apply_result[1+1];                 /*�������            */
	char		mer_apply_view[80+1];                  /*�������            */
	char		mer_refuse_reason[10+1];               /*�ܾ�ԭ�����        */
	char		biz_date[8+1];                         /*ҵ������            */
	char		created_datetime[14+1];                /*����ʱ��            */
	char		last_modified_datetime[14+1];          /*����ʱ��            */
	char		is_check_flag[1+1];
	char		extend_param1[100+1];
	char		extend_param2[250+1];
	char		extend_param3[40+1];
}ICPS_WBC_TM_AGREEMENT_CAR;

#define SD_DATA  ICPS_WBC_TM_AGREEMENT_CAR
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date                  ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  agreement_no               ,0),\
	APP_DEFSDMEMBER(T_STRING,  merchant_id                ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  mer_order_no               ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_new_car                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  car_id                     ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  car_price                  ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  car_inquiry_price          ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  assess_amount              ,2),\
	APP_DEFSDMEMBER(T_STRING,  assess_time                ,0),\
	APP_DEFSDMEMBER(T_STRING,  assess_class               ,0),\
	APP_DEFSDMEMBER(T_STRING,  registrate_time            ,0),\
	APP_DEFSDMEMBER(T_STRING,  vehicle_id                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  engine_no                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  mileage                    ,0),\
	APP_DEFSDMEMBER(T_STRING,  xfr_times                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  coty                       ,0),\
	APP_DEFSDMEMBER(T_STRING,  motorcycle_type            ,0),\
	APP_DEFSDMEMBER(T_STRING,  ins_expire_date            ,0),\
	APP_DEFSDMEMBER(T_STRING,  dealer_id                  ,0),\
	APP_DEFSDMEMBER(T_STRING,  dealer_name                ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_stage_guarantee_dealer  ,0),\
	APP_DEFSDMEMBER(T_STRING,  car_name                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_second_hand_car         ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  car_actual_price           ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  down_payment               ,2),\
	APP_DEFSDMEMBER(T_STRING,  car_context                ,0),\
	APP_DEFSDMEMBER(T_STRING,  driver_license             ,0),\
	APP_DEFSDMEMBER(T_STRING,  home_phone                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  occupation                 ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ss_ave_amt_mtly            ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  salary_ave_mtly            ,2),\
	APP_DEFSDMEMBER(T_STRING,  is_home_visited            ,0),\
	APP_DEFSDMEMBER(T_STRING,  house_info                 ,0),\
	APP_DEFSDMEMBER(T_STRING,  mer_apply_result           ,0),\
	APP_DEFSDMEMBER(T_STRING,  mer_apply_view             ,0),\
	APP_DEFSDMEMBER(T_STRING,  mer_refuse_reason          ,0),\
	APP_DEFSDMEMBER(T_STRING,  biz_date                   ,0),\
	APP_DEFSDMEMBER(T_STRING,  created_datetime           ,0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime     ,0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag              ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1              ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2              ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3              ,0)
  	APP_DECLAREFIELDS(SD_ICPS_WBC_TM_AGREEMENT_CAR)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_AGREEMENT_CAR_H__*/
