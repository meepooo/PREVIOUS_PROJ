/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP
˵    ��:CBS�������ܱ���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP_H__
#define __ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP_H__
typedef struct TDB_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP
{
	char		busi_date[8+1];
	int			file_order;
	char		partition_date[10+1];          /*��������            */
	char		bank_group_id[32+1];           /*���ű��            */
	double		clearing_calc_day_amt;         /*ʵ����Ϣ            */
	double		clearing_day_no_vat_amt;       /*����ƽ̨�ѣ�����˰��*/
	double		clearing_day_vat_amt;          /*����ƽ̨�ѣ�˰��    */
	int			txn_num;                       /*������              */
	double		clearing_day_amt;              /*ƽ̨��              */
	char		is_check_flag[1+1];
	char		extend_param1[100+1];
	char		extend_param2[250+1];
	char		extend_param3[40+1];
}ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP;

#define SD_DATA  ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date                ,0),\
	APP_DEFSDMEMBER(T_LONG,    file_order               ,0),\
	APP_DEFSDMEMBER(T_STRING,  partition_date           ,0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id            ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  clearing_calc_day_amt    ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  clearing_day_no_vat_amt  ,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  clearing_day_vat_amt     ,2),\
	APP_DEFSDMEMBER(T_LONG,    txn_num                  ,0),\
	APP_DEFSDMEMBER(T_DOUBLE,  clearing_day_amt         ,2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag            ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1            ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2            ,0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3            ,0)
  	APP_DECLAREFIELDS(SD_ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_REPORT_CBS_PTJR_CAR_DATA_PAID_SUM_DAY_COOP_H__*/
                              
