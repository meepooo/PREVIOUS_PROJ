/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_AGREEMENT_CAR.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_AGREEMENT_CAR
说    明:协议附加表(车)
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_AGREEMENT_CAR_H__
#define __ICPS_WBC_TM_AGREEMENT_CAR_H__
typedef struct TDB_ICPS_WBC_TM_AGREEMENT_CAR
{
	char		busi_date[8+1];                
	int			file_order;         
	char		agreement_no[50+1];                    /*平台订单号          */
	char		merchant_id[20+1];                     /*平台ID号            */
	char		product_cd[50+1];                      /*产品号              */
	char		mer_order_no[50+1];                    /*平台协议号          */
	char		is_new_car[1+1];                       /*是否新车            */
	char		car_id[21+1];                          /*车辆ID              */
	double		car_price;                             /*车辆销售价          */
	double		car_inquiry_price;                     /*外部数据源查询价    */
	double		assess_amount;                         /*车辆估值            */
	char		assess_time[8+1];                      /*车辆评估时间        */
	char		assess_class[5+1];                     /*车辆检测级别        */
	char		registrate_time[14+1];                 /*上牌日期            */
	char		vehicle_id[32+1];                      /*机动车架号          */
	char		engine_no[32+1];                       /*发动机号            */
	char		mileage[20+1];                               /*行驶里程 fuwd22392 Modify    */
	char		xfr_times[20+1];                             /*过户次数fuwd22392 Modify            */
	char		coty[20+1];                                  /*车龄    fuwd22392 Modify            */
	char		motorcycle_type[30+1];                 /*车型描述            */
	char		ins_expire_date[14+1];                 /*保险到期日          */
	char		dealer_id[32+1];                       /*车商ID              */
	char		dealer_name[32+1];                     /*车商                */
	char		is_stage_guarantee_dealer[1+1];        /*是否阶段性担保车商  */
	char		car_name[20+1];                        /*车辆名称            */
	char		is_second_hand_car[1+1];               /*是否二手车          */
	double		car_actual_price;                      /*车辆实际成交价      */
	double		down_payment;                          /*首付总金额          */
	char		car_context[3000+1];                   /*补充信息            */
	char		driver_license[30+1];                  /*驾驶证号码          */
	char		home_phone[20+1];                      /*家庭固话号码        */
	char		occupation[60+1];                      /*职业                */
	double		ss_ave_amt_mtly;                       /*每月社保平均缴交金额*/
	double		salary_ave_mtly;                       /*每月平均工资进账流水*/
	char		is_home_visited[1+1];                  /*有无家访            */
	char		house_info[80+1];                      /*房产信息            */
	char		mer_apply_result[1+1];                 /*审批结果            */
	char		mer_apply_view[80+1];                  /*审批意见            */
	char		mer_refuse_reason[10+1];               /*拒绝原因分类        */
	char		biz_date[8+1];                         /*业务日期            */
	char		created_datetime[14+1];                /*创建时间            */
	char		last_modified_datetime[14+1];          /*更新时间            */
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
