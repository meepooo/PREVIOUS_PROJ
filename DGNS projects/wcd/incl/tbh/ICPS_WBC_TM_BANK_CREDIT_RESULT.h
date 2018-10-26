/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_TM_BANK_CREDIT_RESULT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_TM_BANK_CREDIT_RESULT
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_TM_BANK_CREDIT_RESULT_H__
#define __ICPS_WBC_TM_BANK_CREDIT_RESULT_H__
typedef struct TDB_ICPS_WBC_TM_BANK_CREDIT_RESULT
{  
  char		busi_date[8+1];
  int		file_order;
  char		seq_no[32+1];                     /*决策流水            */
  char		bank_no[20+1];                    /*银行编号            */
  char		bank_name[80+1];                  /*银行名              */
  char		id_no[30+1];                      /*证件号              */
  char		id_type[2+1];                     /*证件类型            */
  char		name[80+1];                       /*姓名                */
  char		nbs_order_no[32+1];               /*订单号              */
  char		credit_info[1024+1];              /*征信信息            */
  char		rule_action_type[2+1];            /*征信规则命中状态    */
  char		rule_code[50+1];                  /*征信规则规则拒绝码  */
  char		ruile_desc[500+1];                /*规则规则决策拒绝描述*/
  char		is_bl_rej[2+1];                   /*黑名单命中状态      */
  char		bl_rej_code[50+1];                /*黑名单拒绝编码      */
  char		bl_rej_desc[500+1];               /*黑名单拒绝描述      */
  char		credit_datetime[14+1];            /*风险判定时间        */
  char		result_code[9+1];                 /*决策结果            */
  char		result_desc[100+1];               /*决策结果描述        */
  char		created_datetime[14+1];           /*创建时间            */
  char		last_modified_datetime[14+1];     /*更新时间            */
  char		is_check_flag[1+1];
  char		extend_param1[100+1];
  char		extend_param2[250+1];
  char		extend_param3[40+1];

}ICPS_WBC_TM_BANK_CREDIT_RESULT;

#define SD_DATA  ICPS_WBC_TM_BANK_CREDIT_RESULT
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
   APP_DEFSDMEMBER(T_STRING,  seq_no                  ,0),\
   APP_DEFSDMEMBER(T_STRING,  bank_no                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  bank_name               ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_no                   ,0),\
   APP_DEFSDMEMBER(T_STRING,  id_type                 ,0),\
   APP_DEFSDMEMBER(T_STRING,  name                    ,0),\
   APP_DEFSDMEMBER(T_STRING,  nbs_order_no            ,0),\
   APP_DEFSDMEMBER(T_STRING,  credit_info             ,0),\
   APP_DEFSDMEMBER(T_STRING,  rule_action_type        ,0),\
   APP_DEFSDMEMBER(T_STRING,  rule_code               ,0),\
   APP_DEFSDMEMBER(T_STRING,  ruile_desc              ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_bl_rej               ,0),\
   APP_DEFSDMEMBER(T_STRING,  bl_rej_code             ,0),\
   APP_DEFSDMEMBER(T_STRING,  bl_rej_desc             ,0),\
   APP_DEFSDMEMBER(T_STRING,  credit_datetime         ,0),\
   APP_DEFSDMEMBER(T_STRING,  result_code             ,0),\
   APP_DEFSDMEMBER(T_STRING,  result_desc             ,0),\
   APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
   APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_BANK_CREDIT_RESULT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_BANK_CREDIT_RESULT_H__*/
                                                                              
