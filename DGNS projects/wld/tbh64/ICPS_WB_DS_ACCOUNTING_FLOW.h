/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_DS_ACCOUNTING_FLOW.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_DS_ACCOUNTING_FLOW (F_WB13.��Ʒ�¼�ձ���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_DS_ACCOUNTING_FLOW_H__
#define __ICPS_WB_DS_ACCOUNTING_FLOW_H__
typedef struct TDB_ICPS_WB_DS_ACCOUNTING_FLOW
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*�ڲ�������*/
		/*�ڲ�������*/
	char   host_trans_serial[36+1];  /*���Ľ�����ˮ*/
		/*���Ľ�����ˮ*/
	char   card_no[19+1];  /*����*/
		/*����*/
	char   currency[3+1];  /*����*/
		/*����*/
	char   txn_code[4+1];  /*������*/
		/*������*/
	char   txn_desc[80+1];  /*��������*/
		/*��������*/
	char   db_cr_ind[1+1];  /*������*/
		/*������*/
	double   post_amt;  /*���˽��*/
		/*���˽��*/
	char   post_gl_ind[1+1];  /*���˷�ʽ*/
		/*���˷�ʽ*/
	char   owning_branch[9+1];  /*֧��*/
		/*֧��*/
	char   subject[40+1];  /*��Ŀ*/
		/*��Ŀ*/
	char   red_flag[1+1];  /*�����ֱ�ʶ*/
		/*�����ֱ�ʶ*/
	long   queue;  /*����*/
		/*����*/
	char   product_cd[10+1];  /*��Ʒ��*/
		/*��Ʒ��*/
	char   ref_nbr[25+1];  /*��ݺ�*/
		/*��ݺ�*/
	char   age_group[5+1];  /*������*/
		/*������*/
	char   plan_nbr[10+1];  /*���üƻ���*/
		/*���üƻ���*/
	char   bnp_group[5+1];  /*���ɷ���*/
		/*���ɷ���*/
	char   bank_group_id[10+1];  /*���Ŵ���*/
		/*���Ŵ���*/
	char   bank_no[15+1];  /*���д���*/
		/*���д���*/
	int   term;  /*����*/
		/*����*/
	char   batchDate[14+1];  /*����*/
		/*����*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_DS_ACCOUNTING_FLOW;

#define SD_DATA  ICPS_WB_DS_ACCOUNTING_FLOW
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  host_trans_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  txn_desc, 0),\
	APP_DEFSDMEMBER(T_STRING,  db_cr_ind, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  post_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  post_gl_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  owning_branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  subject, 0),\
	APP_DEFSDMEMBER(T_STRING,  red_flag, 0),\
	APP_DEFSDMEMBER(T_LONG,  queue, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  ref_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  age_group, 0),\
	APP_DEFSDMEMBER(T_STRING,  plan_nbr, 0),\
	APP_DEFSDMEMBER(T_STRING,  bnp_group, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_no, 0),\
	APP_DEFSDMEMBER(T_LONG,  term, 0),\
	APP_DEFSDMEMBER(T_STRING,  batchDate, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_DS_ACCOUNTING_FLOW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_DS_ACCOUNTING_FLOW_H__*/
