/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF
˵    ��:β�������
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF_H__
#define __ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF_H__
typedef struct TDB_ICPS_WBC_BANK_GROUP_DFQ_SPLIT_DIFF
{
	char			busi_date[8+1];
	int				file_order;
	char			partition_date[8+1];           /*��������      */
	char			product_cd[6+1];               /*��Ʒ���      */
	char			error_type[40+1];              /*�쳣����      */
	char			bank_group_id[10+1];           /*���ű��      */
	char			bank_no[20+1];                 /*���б��      */
	char			consumer_trans_id[40+1];       /*ҵ����ˮ��    */
	char			reg_type[10+1];                /*��������      */
	char			name[80+1];                    /*����          */
	char			logical_card_no[19+1];         /*�߼�����      */
	double			bf_amt;                        /*������������*/
	double			account_amt;                   /*CNC���˽��   */
	double			error_amt;                     /*Ӧ�������    */
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
