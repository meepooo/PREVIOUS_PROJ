/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_ACCOUNT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_ACCOUNT (F_WB1.�˻���Ϣ��-����������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_ACCOUNT_H__
#define __ICPS_WB_TM_ACCOUNT_H__
typedef struct TDB_ICPS_WB_TM_ACCOUNT
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   acct_no[20+1];  /*�˻����*/
		/*�˻����*/
	char   acct_type[1+1];  /*�˻�����*/
		/*�˻�����*/
	char   cust_id[20+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   cust_limit_id[20+1];  /*�ͻ����ID*/
		/*�ͻ����ID*/
	char   product_code[6+1];  /*��Ʒ����*/
		/*��Ʒ����*/
	char   default_logical_card_no[19+1];  /*Ĭ���߼�����*/
		/*Ĭ���߼�����*/
	char   currency[3+1];  /*����*/
		/*����*/
	double   credit_limit;  /*���Ŷ��*/
		/*���Ŷ��*/
	double   temp_limit;  /*��ʱ���*/
		/*��ʱ���*/
	char   temp_limit_begin_date[8+1];  /*��ʱ��ȿ�ʼ����*/
		/*��ʱ��ȿ�ʼ����*/
	char   temp_limit_end_date[8+1];  /*��ʱ��Ƚ�������*/
		/*��ʱ��Ƚ�������*/
	double   user_field1;  /*�����ֶ�1*/
		/*�����ֶ�1*/
	double   user_field2;  /*�����ֶ�2*/
		/*�����ֶ�2*/
	double   user_field3;  /*�����ֶ�3*/
		/*�����ֶ�3*/
	double   curr_balance;  /*��ǰ���*/
		/*��ǰ���*/
	double   user_field4;  /*�����ֶ�4*/
		/*�����ֶ�4*/
	double   principal_bal;  /*�������*/
		/*�������*/
	double   user_field5;  /*�����ֶ�5*/
		/*�����ֶ�5*/
	double   user_field6;  /*�����ֶ�6*/
		/*�����ֶ�6*/
	double   begin_bal;  /*��һ���������*/
		/*��һ���������*/
	double   pmt_due_day_bal;  /*���ڻ��������*/
		/*���ڻ��������*/
	double   user_field7;  /*�����ֶ�7*/
		/*�����ֶ�7*/
	char   user_field8[1+1];  /*�����ֶ�8*/
		/*�����ֶ�8*/
	double   user_field9;  /*�����ֶ�9*/
		/*�����ֶ�9*/
	double   user_field10;  /*�����ֶ�10*/
		/*�����ֶ�10*/
	double   user_field11;  /*�����ֶ�11*/
		/*�����ֶ�11*/
	double   user_field12;  /*�����ֶ�12*/
		/*�����ֶ�12*/
	double   user_field13;  /*�����ֶ�13*/
		/*�����ֶ�13*/
	char   user_field14[8+1];  /*�����ֶ�14*/
		/*�����ֶ�14*/
	char   user_field15[8+1];  /*�����ֶ�15*/
		/*�����ֶ�15*/
	char   user_field16[8+1];  /*�����ֶ�16*/
		/*�����ֶ�16*/
	char   user_field17[8+1];  /*�����ֶ�17*/
		/*�����ֶ�17*/
	int   user_field18;  /*�����ֶ�18*/
		/*�����ֶ�18*/
	char   name[80+1];  /*����*/
		/*����*/
	char   gender[1+1];  /*�Ա�*/
		/*�Ա�*/
	char   user_field19[9+1];  /*�����ֶ�19*/
		/*�����ֶ�19*/
	char   mobile_no[20+1];  /*�ƶ��绰*/
		/*�ƶ��绰*/
	char   user_field20[200+1];  /*�����ֶ�20*/
		/*�����ֶ�20*/
	char   billint_cycle[2+1];  /*������*/
		/*������*/
	char   user_field21[1+1];  /*�����ֶ�21*/
		/*�����ֶ�21*/
	char   user_field22[1+1];  /*�����ֶ�22*/
		/*�����ֶ�22*/
	char   user_field23[1+1];  /*�����ֶ�23*/
		/*�����ֶ�23*/
	char   user_field24[3+1];  /*�����ֶ�24*/
		/*�����ֶ�24*/
	char   user_field25[40+1];  /*�����ֶ�25*/
		/*�����ֶ�25*/
	char   user_field26[40+1];  /*�����ֶ�26*/
		/*�����ֶ�26*/
	char   user_field27[40+1];  /*�����ֶ�27*/
		/*�����ֶ�27*/
	char   user_field28[200+1];  /*�����ֶ�28*/
		/*�����ֶ�28*/
	char   user_field29[10+1];  /*�����ֶ�29*/
		/*�����ֶ�29*/
	char   user_field30[80+1];  /*�����ֶ�30*/
		/*�����ֶ�30*/
	char   user_field31[27+1];  /*�����ֶ�31*/
		/*�����ֶ�31*/
	char   AGE_CD[1+1];  /*��Ƿ����*/
		/*��Ƿ����*/
	char   user_field32[1+1];  /*�����ֶ�32*/
		/*�����ֶ�32*/
	double   UNMATCH_DB;  /*δ���˽�ǽ��*/
		/*δ���˽�ǽ��*/
	double   user_field33;  /*�����ֶ�33*/
		/*�����ֶ�33*/
	double   unmatch_cr;  /*δ���˴��ǽ��*/
		/*δ���˴��ǽ��*/
	char   dd_ind[1+1];  /*Լ����������*/
		/*Լ����������*/
	char   dd_bank_name[80+1];  /*Լ��������������*/
		/*Լ��������������*/
	char   dd_bank_branch[14+1];  /*Լ��������к�*/
		/*Լ��������к�*/
	char   dd_bank_acct_no[40+1];  /*Լ������ۿ��˺�*/
		/*Լ������ۿ��˺�*/
	char   dd_bank_acct_name[80+1];  /*Լ������ۿ��˻�����*/
		/*Լ������ۿ��˻�����*/
	double   last_dd_amt;  /*����Լ��������*/
		/*����Լ��������*/
	char   last_dd_date[14+1];  /*����Լ����������*/
		/*����Լ����������*/
	char   user_field34[1+1];  /*�����ֶ�34*/
		/*�����ֶ�34*/
	double   last_pmt_amt;  /*���ڻ�����*/
		/*���ڻ�����*/
	char   last_pmt_date[14+1];  /*�ϸ���������*/
		/*�ϸ���������*/
	char   last_stmt_date[14+1];  /*�ϸ����ڻ�������*/
		/*�ϸ����ڻ�������*/
	char   last_pmt_due_date[14+1];  /*�ϸ����ڻ�������1*/
		/*�ϸ����ڻ�������1*/
	char   last_agint_date[14+1];  /*�Ͽ�����������������*/
		/*�Ͽ�����������������*/
	char   collect_date[14+1];  /*�������*/
		/*�������*/
	char   collect_out_date[14+1];  /*�����ն�������*/
		/*�����ն�������*/
	char   next_stmt_date[14+1];  /*�¸����ڻ�������*/
		/*�¸����ڻ�������*/
	char   pmt_due_date[14+1];  /*���ڻ�������*/
		/*���ڻ�������*/
	char   dd_date[14+1];  /*Լ����������*/
		/*Լ����������*/
	char   grace_date[14+1];  /*��������*/
		/*��������*/
	char   user_field35[14+1];  /*�����ֶ�35*/
		/*�����ֶ�35*/
	char   closed_date[14+1];  /*������������*/
		/*������������*/
	char   first_stmt_date[14+1];  /*�׸����ڻ�������*/
		/*�׸����ڻ�������*/
	char   cancel_date[14+1];  /*��������*/
		/*��������*/
	char   charge_off_date[14+1];  /*ת��������*/
		/*ת��������*/
	char   user_field36[14+1];  /*�����ֶ�36*/
		/*�����ֶ�36*/
	double   usesr_field37;  /*�����ֶ�37*/
		/*�����ֶ�37*/
	double   usesr_field38;  /*�����ֶ�38*/
		/*�����ֶ�38*/
	double   usesr_field39;  /*�����ֶ�39*/
		/*�����ֶ�39*/
	double   usesr_field40;  /*�����ֶ�40*/
		/*�����ֶ�40*/
	double   usesr_field41;  /*�����ֶ�41*/
		/*�����ֶ�41*/
	double   usesr_field42;  /*�����ֶ�42*/
		/*�����ֶ�42*/
	double   usesr_field43;  /*�����ֶ�43*/
		/*�����ֶ�43*/
	double   usesr_field44;  /*�����ֶ�44*/
		/*�����ֶ�44*/
	double   usesr_field45;  /*�����ֶ�45*/
		/*�����ֶ�45*/
	double   usesr_field46;  /*�����ֶ�46*/
		/*�����ֶ�46*/
	double   usesr_field47;  /*�����ֶ�47*/
		/*�����ֶ�47*/
	double   usesr_field48;  /*�����ֶ�48*/
		/*�����ֶ�48*/
	int   usesr_field49;  /*�����ֶ�49*/
		/*�����ֶ�49*/
	double   ctd_retail_amt;  /*�������ѽ��*/
		/*�������ѽ��*/
	int   ctd_retail_cnt;  /*�������ѱ���*/
		/*�������ѱ���*/
	double   ctd_payment_amt;  /*���ڻ�����*/
		/*���ڻ�����*/
	int   ctd_payment_cnt;  /*���ڻ������*/
		/*���ڻ������*/
	double   ctd_db_adj_amt;  /*���ڽ�ǵ������*/
		/*���ڽ�ǵ������*/
	int   ctd_db_adj_cnt;  /*���ڽ�ǵ�������*/
		/*���ڽ�ǵ�������*/
	int   ctd_cr_adj_cnt;  /*���ڴ��ǵ�������*/
		/*���ڴ��ǵ�������*/
	double   ctd_cr_adj_amt;  /*���ڴ��ǵ������*/
		/*���ڴ��ǵ������*/
	double   ctd_fee_amt;  /*���ڷ��ý��*/
		/*���ڴ��ǵ������*/
	int   ctd_fee_cnt;  /*���ڷ��ñ���*/
		/*���ڷ��ñ���*/
	double   ctd_interest_amt;  /*������Ϣ���*/
		/*������Ϣ���*/
	int   ctd_interest_cnt;  /*������Ϣ����*/
		/*������Ϣ����*/
	double   user_field50;  /*�����ֶ�50*/
		/*�����ֶ�50*/
	int   user_field51;  /*�����ֶ�51*/
		/*�����ֶ�51*/
	double   user_field52;  /*�����ֶ�52*/
		/*�����ֶ�52*/
	double   mtd_retail_amt;  /*�������ѽ��*/
		/*�������ѽ��*/
	int   mtd_retail_cnt;  /*�������ѱ���*/
		/*�������ѱ���*/
	double   user_field53;  /*�����ֶ�53*/
		/*�����ֶ�53*/
	int   user_field54;  /*�����ֶ�54*/
		/*�����ֶ�54*/
	double   user_field55;  /*�����ֶ�55*/
		/*�����ֶ�55*/
	int   user_field56;  /*�����ֶ�56*/
		/*�����ֶ�56*/
	double   ytd_retail_amt;  /*�������ѽ��*/
		/*�������ѽ��*/
	int   ytd_retail_cnt;  /*�������ѱ���*/
		/*�������ѱ���*/
	double   user_field57;  /*�����ֶ�57*/
		/*�����ֶ�57*/
	int   user_field58;  /*�����ֶ�58*/
		/*�����ֶ�58*/
	double   user_field59;  /*�����ֶ�59*/
		/*�����ֶ�59*/
	int   user_field60;  /*�����ֶ�60*/
		/*�����ֶ�60*/
	double   user_field61;  /*�����ֶ�61*/
		/*�����ֶ�61*/
	int   user_field62;  /*�����ֶ�62*/
		/*�����ֶ�62*/
	double   user_field63;  /*�����ֶ�63*/
		/*�����ֶ�63*/
	int   user_field64;  /*�����ֶ�64*/
		/*�����ֶ�64*/
	double   user_field65;  /*�����ֶ�65*/
		/*�����ֶ�64*/
	int   user_field66;  /*�����ֶ�66*/
		/*�����ֶ�66*/
	double   user_field67;  /*�����ֶ�67*/
		/*�����ֶ�67*/
	int   user_field68;  /*�����ֶ�68*/
		/*�����ֶ�68*/
	double   user_field69;  /*�����ֶ�69*/
		/*�����ֶ�69*/
	int   user_field70;  /*�����ֶ�70*/
		/*�����ֶ�70*/
	double   user_field71;  /*�����ֶ�71*/
		/*�����ֶ�71*/
	double   user_field72;  /*�����ֶ�72*/
		/*�����ֶ�72*/
	double   user_field73;  /*�����ֶ�73*/
		/*�����ֶ�73*/
	double   user_field74;  /*�����ֶ�74*/
		/*�����ֶ�74*/
	char   user_field75[8+1];  /*�����ֶ�75*/
		/*�����ֶ�75*/
	char   user_field76[2+1];  /*�����ֶ�76*/
		/*�����ֶ�76*/
	char   user_field77[24+1];  /*�����ֶ�77*/
		/*�����ֶ�77*/
	char   user_field78[24+1];  /*�����ֶ�78*/
		/*�����ֶ�78*/
	char   user_field79[1+1];  /*�����ֶ�79*/
		/*�����ֶ�79*/
	char   user_field80[1+1];  /*�����ֶ�80*/
		/*�����ֶ�80*/
	char   user_field81[1+1];  /*�����ֶ�81*/
		/*�����ֶ�81*/
	char   waive_svcfee_ind[1+1];  /*�Ƿ���������*/
		/*�Ƿ���������*/
	char   user_field82[4+1];  /*�����ֶ�82*/
		/*�����ֶ�82*/
	char   user_field83[4+1];  /*�����ֶ�83*/
		/*�����ֶ�83*/
	char   user_field84[4+1];  /*�����ֶ�84*/
		/*�����ֶ�84*/
	char   user_field85[4+1];  /*�����ֶ�85*/
		/*�����ֶ�85*/
	char   user_field86[4+1];  /*�����ֶ�86*/
		/*�����ֶ�86*/
	char   user_field87[4+1];  /*�����ֶ�87*/
		/*�����ֶ�87*/
	char   user_field88[14+1];  /*�����ֶ�88*/
		/*�����ֶ�88*/
	char   user_date2[14+1];  /*���ڵ�������*/
		/*���ڵ�������*/
	char   user_field89[14+1];  /*�����ֶ�89*/
		/*�����ֶ�89*/
	char   user_field90[14+1];  /*�����ֶ�90*/
		/*�����ֶ�90*/
	char   user_field91[14+1];  /*�����ֶ�91*/
		/*�����ֶ�91*/
	char   user_field92[14+1];  /*�����ֶ�92*/
		/*�����ֶ�92*/
	int   user_field93;  /*�����ֶ�93*/
		/*�����ֶ�93*/
	int   user_field94;  /*�����ֶ�94*/
		/*�����ֶ�94*/
	int   user_field95;  /*�����ֶ�95*/
		/*�����ֶ�95*/
	int   user_field96;  /*�����ֶ�96*/
		/*�����ֶ�96*/
	int   user_field97;  /*�����ֶ�97*/
		/*�����ֶ�97*/
	int   user_field98;  /*�����ֶ�98*/
		/*�����ֶ�98*/
	char   user_field99[40+1];  /*�����ֶ�99*/
		/*�����ֶ�99*/
	char   user_field100[40+1];  /*�����ֶ�100*/
		/*�����ֶ�100*/
	char   user_field101[40+1];  /*�����ֶ�101*/
		/*�����ֶ�101*/
	char   user_field102[40+1];  /*�����ֶ�102*/
		/*�����ֶ�102*/
	char   user_field103[40+1];  /*�����ֶ�103*/
		/*�����ֶ�103*/
	char   user_field104[40+1];  /*�����ֶ�104*/
		/*�����ֶ�104*/
	double   user_field105;  /*�����ֶ�105*/
		/*�����ֶ�105*/
	double   user_field106;  /*�����ֶ�106*/
		/*�����ֶ�106*/
	double   user_field107;  /*�����ֶ�107*/
		/*�����ֶ�107*/
	double   user_field108;  /*�����ֶ�108*/
		/*�����ֶ�108*/
	double   user_field109;  /*�����ֶ�109*/
		/*�����ֶ�109*/
	double   user_field110;  /*�����ֶ�110*/
		/*�����ֶ�110*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	double   mtd_payment_amt;  /*���»�����*/
		/*���»�����*/
	int   mtd_payment_cnt;  /*���»������*/
		/*���»������*/
	double   ytd_payment_amt;  /*���껹����*/
		/*���껹����*/
	int   ytd_payment_cnt;  /*���껹�����*/
		/*���껹�����*/
	double   ltd_payment_amt;  /*��ʷ������*/
		/*��ʷ������*/
	int   ltd_payment_cnt;  /*��ʷ�������*/
		/*��ʷ�������*/
	char   user_field111[1+1];  /*�����ֶ�111*/
		/*�����ֶ�111*/
	double   user_field112;  /*�����ֶ�112*/
		/*�����ֶ�112*/
	int   user_field113;  /*�����ֶ�113*/
		/*�����ֶ�113*/
	char   last_post_date[8+1];  /*�ϸ���������ʱ��*/
		/*�ϸ���������ʱ��*/
	char   last_modified_datetime[14+1];  /*�޸�ʱ��*/
		/*�޸�ʱ��*/
	char   user_field114[8+1];  /*�����ֶ�114*/
		/*�����ֶ�114*/
	char   last_sync_date[8+1];  /*��һ�����˵���������*/
		/*��һ�����˵���������*/
	char   user_field115[14+1];  /*�����ֶ�115*/
		/*�����ֶ�115*/
	double   user_field116;  /*�����ֶ�116*/
		/*�����ֶ�116*/
	char   user_field117[16+1];  /*�����ֶ�117*/
		/*�����ֶ�117*/
	char   bank_group_id[5+1];  /*���ű��*/
		/*���ű��*/
	double   bank_proportion;  /*���г��ʱ���*/
		/*���г��ʱ���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_ACCOUNT;

#define SD_DATA  ICPS_WB_TM_ACCOUNT
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_limit_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  default_logical_card_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  currency, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  credit_limit, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  temp_limit, 4),\
	APP_DEFSDMEMBER(T_STRING,  temp_limit_begin_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  temp_limit_end_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field1, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field2, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field3, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  curr_balance, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field4, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  principal_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field5, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field6, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  begin_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  pmt_due_day_bal, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field7, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field8, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field9, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field10, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field11, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field12, 4),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field13, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field14, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field15, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field16, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field17, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field18, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field19, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field20, 0),\
	APP_DEFSDMEMBER(T_STRING,  billint_cycle, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field21, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field22, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field23, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field24, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field25, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field26, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field27, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field28, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field29, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field30, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field31, 0),\
	APP_DEFSDMEMBER(T_STRING,  AGE_CD, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field32, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  UNMATCH_DB, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field33, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  unmatch_cr, 2),\
	APP_DEFSDMEMBER(T_STRING,  dd_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_branch, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_bank_acct_name, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_dd_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  last_dd_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field34, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  last_pmt_amt, 2),\
	APP_DEFSDMEMBER(T_STRING,  last_pmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_pmt_due_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_agint_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  collect_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  collect_out_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  next_stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  pmt_due_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  dd_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  grace_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field35, 0),\
	APP_DEFSDMEMBER(T_STRING,  closed_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  first_stmt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  cancel_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  charge_off_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field36, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field37, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field38, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field39, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field40, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field41, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field42, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field43, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field44, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field45, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field46, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field47, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  usesr_field48, 2),\
	APP_DEFSDMEMBER(T_LONG,  usesr_field49, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_retail_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_retail_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_db_adj_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_db_adj_cnt, 0),\
	APP_DEFSDMEMBER(T_LONG,  ctd_cr_adj_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_cr_adj_amt, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_fee_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_fee_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ctd_interest_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ctd_interest_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field50, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field51, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field52, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  mtd_retail_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  mtd_retail_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field53, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field54, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field55, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field56, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ytd_retail_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ytd_retail_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field57, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field58, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field59, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field60, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field61, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field62, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field63, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field64, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field65, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field66, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field67, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field68, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field69, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field70, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field71, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field72, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field73, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field74, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field75, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field76, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field77, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field78, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field79, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field80, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field81, 0),\
	APP_DEFSDMEMBER(T_STRING,  waive_svcfee_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field82, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field83, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field84, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field85, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field86, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field87, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field88, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_date2, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field89, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field90, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field91, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field92, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field93, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field94, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field95, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field96, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field97, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field98, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field99, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field100, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field101, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field102, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field103, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field104, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field105, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field106, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field107, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field108, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field109, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field110, 2),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  mtd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  mtd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ytd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ytd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  ltd_payment_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,  ltd_payment_cnt, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field111, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field112, 2),\
	APP_DEFSDMEMBER(T_LONG,  user_field113, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_post_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field114, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_sync_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field115, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field116, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field117, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion, 2),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_ACCOUNT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_ACCOUNT_H__*/
