/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF
说    明:尾差调整表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF_H__
#define __ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF_H__
typedef struct TDB_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF
{
	char			busi_date[8+1];
	int				file_order;
	char			partition_date[8+1];           /*批量日期      */
	char			product_cd[6+1];               /*产品编号      */
	char			error_type[40+1];              /*异常类型      */
	char			bank_group_id[10+1];           /*银团编号      */
	char			bank_no[20+1];                 /*银行编号      */
	char			consumer_trans_id[40+1];       /*业务流水号    */
	char			reg_type[10+1];                /*交易类型      */
	char			name[80+1];                    /*姓名          */
	char			logical_card_no[19+1];         /*逻辑卡号      */
	double			bf_amt;                        /*备付金清算金额*/
	double			account_amt;                   /*CNC记账金额   */
	double			error_amt;                     /*应调整差额    */
	char			is_check_flag[1+1];
	char			extend_param1[100+1];
	char			extend_param2[250+1];
	char			extend_param3[40+1];
}ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF;

#define SD_DATA  ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date          ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order         ,0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date     ,0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd         ,0),\
	APP_DEFSDMEMBER(T_STRING,  error_type         ,0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id      ,0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no            ,0),\
	APP_DEFSDMEMBER(T_STRING,  consumer_trans_id  ,0),\
	APP_DEFSDMEMBER(T_STRING,  reg_type           ,0),\
	APP_DEFSDMEMBER(T_STRING,  name               ,0),\
	APP_DEFSDMEMBER(T_STRING,  logical_card_no    ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bf_amt             ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  account_amt        ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  error_amt          ,2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag      ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1      ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2      ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3      ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF_H__*/
