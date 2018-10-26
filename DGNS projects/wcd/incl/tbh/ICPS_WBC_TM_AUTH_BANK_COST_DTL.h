/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WBC_TM_AUTH_BANK_COST_DTL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_AUTH_BANK_COST_DTL
˵    ��:��Ȩ��ˮ���Ų����ϸ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_AUTH_BANK_COST_DTL_H__
#define __ICPS_WBC_TM_AUTH_BANK_COST_DTL_H__
typedef struct TDB_ICPS_WBC_TM_AUTH_BANK_COST_DTL
{
	char	busi_date[8+1];
	int		file_order;
	char	consumer_trans_id[32+1];
	char	bank_group_id[5+1];
	char	bank_no[10+1];
	char	loan_receipt_nbr[20+1];
	char	reg_type[10+1];
	double	reg_amt;
	char	biz_date[8+1];
	char	cust_id[20+1];/*fuwd22392 modify*/
	char	acct_no[20+1];/*fuwd22392 modify*/
	char	acct_type[1+1];
	char	created_datetime[14+1];
	char	last_modified_datetime[14+1];
	char	card_no[19+1];
	char	is_check_flag[1+1];
	char	extend_param1[100+1];
	char	extend_param2[250+1];
	char	extend_param3[40+1];
}ICPS_WBC_TM_AUTH_BANK_COST_DTL;
 
#define SD_DATA  ICPS_WBC_TM_AUTH_BANK_COST_DTL
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date               ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order              ,0),\
  APP_DEFSDMEMBER(T_STRING,  consumer_trans_id       ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_group_id           ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  loan_receipt_nbr        ,0),\
  APP_DEFSDMEMBER(T_STRING,  reg_type                ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  reg_amt                 ,2),\
  APP_DEFSDMEMBER(T_STRING,  biz_date                ,0),\
  APP_DEFSDMEMBER(T_STRING,  cust_id                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  acct_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  acct_type               ,0),\
  APP_DEFSDMEMBER(T_STRING,  created_datetime        ,0),\
  APP_DEFSDMEMBER(T_STRING,  last_modified_datetime  ,0),\
  APP_DEFSDMEMBER(T_STRING,  card_no                 ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2           ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3           ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_AUTH_BANK_COST_DTL)       
  #undef SD_DATA                                     
  #undef SD_MEMBERS                                  
                                                     
  #endif  /*end of __ICPS_WBC_TM_AUTH_BANK_COST_DTL_H__*/      
