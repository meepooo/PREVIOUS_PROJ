/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_MERCHANT_CUST.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_MERCHANT_CUST
说    明:平台客户信息表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_MERCHANT_CUST_H__
#define __ICPS_WBC_TM_MERCHANT_CUST_H__
typedef struct TDB_ICPS_WBC_TM_MERCHANT_CUST
{
	char			busi_date[8+1];                  
	int				file_order;                     
	char			user_id[32+1];                   /*平台的客户ID         */
	char			merchant_id[20+1];               /*平台ID               */
	char			nbs_cust_id[20+1];               /*NBS客户ID            */
	char			user_name[60+1];                 /*平台注册的客户名称   */
	char			user_mobile[20+1];               /*平台登记的用户手机号 */
	char			apply_datetime[14+1];            /*平台ID申请时间       */
	char			reg_mobile[20+1];                /*注册手机号           */
	char			qq_openid[32+1];                 /*QQ_OPENID            */
	char			wx_openid[32+1];                 /*WX_OPENID            */
	char			login_id[32+1];                  /*微众WEB登录ID        */
	char			company_name[60+1];              /*单位名称             */
	char			company_phone[20+1];             /*单位电话             */
	char			address[60+1];                   /*居住地址             */
	char			contact_name[40+1];              /*联系人名称           */
	char			contact_phone[20+1];             /*联系人手机号         */
	char			contact_relation[10+1];          /*联系人关系           */
	char			reserve1[20+1];                  /*保留字段1            */
	char			reserve2[50+1];                  /*保留字段2            */
	char			reserve3[50+1];                  /*保留字段3            */
	char			biz_date[8+1];                   /*业务日期             */
	char			created_datetime[14+1];          /*创建时间日期         */
	char			last_modified_datetime[14+1];    /*更新时间日期         */
	char			contact_addr[80+1];              /*联系人地址           */
	char			contact_id_no[30+1];             /*联系人身份证号       */
	char			co_licenses[80+1];               /*营业执照号           */
	char			driver_license[30+1];            /*驾驶证号码           */
	char			company_addr[80+1];              /*公司地址             */
	char			home_phone[20+1];                /*家庭固话号码         */
	char			occupation[60+1];                /*职业                 */
	double			ss_ave_amt_mtly;               /*每月社保平均缴交金额 */
	double			salary_ave_mtly;               /*每月平均工资进账流水 */
	char			is_home_visited[1+1];            /*有无家访             */
	char			house_info[80+1];                /*房产信息             */
	char			mer_apply_result[1+1];           /*审批结果             */
	char			mer_apply_view[80+1];            /*审批意见             */
	char			mer_refuse_reason[10+1];         /*拒绝原因分类         */
	char			cust_value[2014+1];              /*客户信息（大字段）   */
	char			is_guarantor[1+1];               /*有无担保人           */
	char			is_check_flag[1+1];              /*                     */
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_TM_MERCHANT_CUST;

#define SD_DATA  ICPS_WBC_TM_MERCHANT_CUST
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
  APP_DEFSDMEMBER(T_STRING,  user_id                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  merchant_id             ,0),\
  APP_DEFSDMEMBER(T_STRING,  nbs_cust_id             ,0),\
  APP_DEFSDMEMBER(T_STRING,  user_name               ,0),\
  APP_DEFSDMEMBER(T_STRING,  user_mobile             ,0),\
  APP_DEFSDMEMBER(T_STRING,  apply_datetime          ,0),\
  APP_DEFSDMEMBER(T_STRING,  reg_mobile              ,0),\
  APP_DEFSDMEMBER(T_STRING,  qq_openid               ,0),\
  APP_DEFSDMEMBER(T_STRING,  wx_openid               ,0),\
  APP_DEFSDMEMBER(T_STRING,  login_id                ,0),\
  APP_DEFSDMEMBER(T_STRING,  company_name            ,0),\
  APP_DEFSDMEMBER(T_STRING,  company_phone           ,0),\
  APP_DEFSDMEMBER(T_STRING,  address                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_name            ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_phone           ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_relation        ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve1                ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve2                ,0),\
  APP_DEFSDMEMBER(T_STRING,  reserve3                ,0),\
  APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
  APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_addr            ,0),\
  APP_DEFSDMEMBER(T_STRING,  contact_id_no           ,0),\
  APP_DEFSDMEMBER(T_STRING,  co_licenses             ,0),\
  APP_DEFSDMEMBER(T_STRING,  driver_license          ,0),\
  APP_DEFSDMEMBER(T_STRING,  company_addr            ,0),\
  APP_DEFSDMEMBER(T_STRING,  home_phone              ,0),\
  APP_DEFSDMEMBER(T_STRING,  occupation              ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  ss_ave_amt_mtly         ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,  salary_ave_mtly         ,2),\
  APP_DEFSDMEMBER(T_STRING,  is_home_visited         ,0),\
  APP_DEFSDMEMBER(T_STRING,  house_info              ,0),\
  APP_DEFSDMEMBER(T_STRING,  mer_apply_result        ,0),\
  APP_DEFSDMEMBER(T_STRING,  mer_apply_view          ,0),\
  APP_DEFSDMEMBER(T_STRING,  mer_refuse_reason       ,0),\
  APP_DEFSDMEMBER(T_STRING,  cust_value              ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_guarantor            ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_MERCHANT_CUST)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_MERCHANT_CUST_H__*/
                                                                                                                                                      
