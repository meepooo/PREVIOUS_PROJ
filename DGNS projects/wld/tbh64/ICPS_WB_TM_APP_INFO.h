/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_APP_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_APP_INFO (F_WB7.������������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_APP_INFO_H__
#define __ICPS_WB_TM_APP_INFO_H__
typedef struct TDB_ICPS_WB_TM_APP_INFO
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   id[20+1];  /*��ʶ*/
		/*��ʶ*/
	char   org[12+1];  /*������*/
		/*������*/
	char   app_no[20+1];  /*��������*/
		/*��������*/
	char   user_field53[1+1];  /*�����ֶ�53*/
		/*�����ֶ�53*/
	char   user_field54[19+1];  /*�����ֶ�54*/
		/*�����ֶ�54*/
	char   name[80+1];  /*����*/
		/*����*/
	char   emb_logo[30+1];  /*͹ӡ����*/
		/*͹ӡ����*/
	char   gender[2+1];  /*�Ա�*/
		/*�Ա�*/
	char   nationality[3+1];  /*����*/
		/*����*/
	char   residency_country_cd[3+1];  /*���þ�ס�ع��Ҵ���*/
		/*���þ�ס�ع��Ҵ���*/
	char   id_type[1+1];  /*֤������*/
		/*֤������*/
	char   id_no[30+1];  /*֤������*/
		/*֤������*/
	char   user_field55[14+1];  /*�����ֶ�55*/
		/*�����ֶ�55*/
	char   user_field56[200+1];  /*�����ֶ�56*/
		/*�����ֶ�56*/
	char   birthday[14+1];  /*����*/
		/*����*/
	char   user_field57[1+1];  /*�����ֶ�57*/
		/*�����ֶ�57*/
	double   user_field58;  /*�����ֶ�58*/
		/*�����ֶ�58*/
	char   user_field59[1+1];  /*�����ֶ�59*/
		/*�����ֶ�59*/
	char   user_field60[1+1];  /*�����ֶ�60*/
		/*�����ֶ�60*/
	char   user_field61[3+1];  /*�����ֶ�61*/
		/*�����ֶ�61*/
	char   user_field62[40+1];  /*�����ֶ�62*/
		/*�����ֶ�62*/
	char   user_field63[40+1];  /*�����ֶ�63*/
		/*�����ֶ�63*/
	char   user_field64[40+1];  /*�����ֶ�64*/
		/*�����ֶ�64*/
	char   user_field65[1+1];  /*�����ֶ�65*/
		/*�����ֶ�65*/
	char   user_field66[200+1];  /*�����ֶ�66*/
		/*�����ֶ�66*/
	char   user_field67[10+1];  /*�����ֶ�67*/
		/*�����ֶ�67*/
	char   user_field68[20+1];  /*�����ֶ�68*/
		/*�����ֶ�68*/
	char   user_field69[14+1];  /*�����ֶ�69*/
		/*�����ֶ�69*/
	char   cellphone[20+1];  /*�ƶ��绰*/
		/*�ƶ��绰*/
	char   user_field70[80+1];  /*�����ֶ�70*/
		/*�����ֶ�70*/
	char   user_field71[40+1];  /*�����ֶ�71*/
		/*�����ֶ�71*/
	char   user_field72[40+1];  /*�����ֶ�72*/
		/*�����ֶ�72*/
	char   user_field73[1+1];  /*�����ֶ�73*/
		/*�����ֶ�73*/
	char   user_field74[2+1];  /*�����ֶ�74*/
		/*�����ֶ�74*/
	double   user_field75;  /*�����ֶ�75*/
		/*�����ֶ�75*/
	char   user_field76[1+1];  /*�����ֶ�76*/
		/*�����ֶ�76*/
	char   user_field77[20+1];  /*�����ֶ�77*/
		/*�����ֶ�77*/
	char   user_field78[200+1];  /*�����ֶ�78*/
		/*�����ֶ�78*/
	char   user_field79[3+1];  /*�����ֶ�79*/
		/*�����ֶ�79*/
	char   user_field80[40+1];  /*�����ֶ�80*/
		/*�����ֶ�80*/
	char   user_field81[40+1];  /*�����ֶ�81*/
		/*�����ֶ�81*/
	char   user_field82[40+1];  /*�����ֶ�82*/
		/*�����ֶ�82*/
	char   user_field83[200+1];  /*�����ֶ�83*/
		/*�����ֶ�83*/
	char   user_field84[10+1];  /*�����ֶ�84*/
		/*�����ֶ�84*/
	char   user_field85[20+1];  /*�����ֶ�85*/
		/*�����ֶ�85*/
	char   user_field86[80+1];  /*�����ֶ�86*/
		/*�����ֶ�86*/
	char   user_field87[1+1];  /*�����ֶ�87*/
		/*�����ֶ�87*/
	char   user_field88[1+1];  /*�����ֶ�88*/
		/*�����ֶ�88*/
	char   user_field89[1+1];  /*�����ֶ�89*/
		/*�����ֶ�89*/
	double   user_field90;  /*�����ֶ�90*/
		/*�����ֶ�90*/
	char   user_field91[20+1];  /*�����ֶ�91*/
		/*�����ֶ�91*/
	char   user_field92[1+1];  /*�����ֶ�92*/
		/*�����ֶ�92*/
	char   user_field93[1+1];  /*�����ֶ�93*/
		/*�����ֶ�93*/
	char   user_field94[14+1];  /*�����ֶ�94*/
		/*�����ֶ�94*/
	char   user_field95[1+1];  /*�����ֶ�95*/
		/*�����ֶ�95*/
	char   user_field96[1+1];  /*�����ֶ�96*/
		/*�����ֶ�96*/
	char   user_field97[10+1];  /*�����ֶ�97*/
		/*�����ֶ�97*/
	char   user_field98[1+1];  /*�����ֶ�98*/
		/*�����ֶ�98*/
	char   user_field99[1+1];  /*�����ֶ�99*/
		/*�����ֶ�99*/
	char   pr_of_country[1+1];  /*�Ƿ����þ�ס*/
		/*�Ƿ����þ�ס*/
	char   user_field100[80+1];  /*�����ֶ�100*/
		/*�����ֶ�100*/
	char   user_field101[80+1];  /*�����ֶ�101*/
		/*�����ֶ�101*/
	char   user_field102[80+1];  /*�����ֶ�102*/
		/*�����ֶ�102*/
	char   user_field103[19+1];  /*�����ֶ�103*/
		/*�����ֶ�103*/
	char   user_field104[20+1];  /*�����ֶ�104*/
		/*�����ֶ�104*/
	char   user_field105[32+1];  /*�����ֶ�105*/
		/*�����ֶ�105*/
	char   user_field106[40+1];  /*�����ֶ�106*/
		/*�����ֶ�106*/
	char   user_field107[1+1];  /*�����ֶ�107*/
		/*�����ֶ�107*/
	char   user_field108[2+1];  /*�����ֶ�108*/
		/*�����ֶ�108*/
	char   user_field109[40+1];  /*�����ֶ�109*/
		/*�����ֶ�109*/
	char   user_field110[40+1];  /*�����ֶ�110*/
		/*�����ֶ�110*/
	char   user_field111[14+1];  /*�����ֶ�111*/
		/*�����ֶ�111*/
	char   user_field112[14+1];  /*�����ֶ�112*/
		/*�����ֶ�112*/
	int   jpa_version;  /*�ֹ���*/
		/*�ֹ���*/
	char   cust_no[20+1];  /*�ͻ���*/
		/*�ͻ���*/
	char   acct_no[20+1];  /*�˻���*/
		/*�˻���*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_APP_INFO;

#define SD_DATA  ICPS_WB_TM_APP_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  id, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field53, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field54, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  emb_logo, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  nationality, 0),\
	APP_DEFSDMEMBER(T_STRING,  residency_country_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field55, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field56, 0),\
	APP_DEFSDMEMBER(T_STRING,  birthday, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field57, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field58, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field59, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field60, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field61, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field62, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field63, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field64, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field65, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field66, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field67, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field68, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field69, 0),\
	APP_DEFSDMEMBER(T_STRING,  cellphone, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field70, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field71, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field72, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field73, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field74, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field75, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field76, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field77, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field78, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field79, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field80, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field81, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field82, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field83, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field84, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field85, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field86, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field87, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field88, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field89, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field90, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field91, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field92, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field93, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field94, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field95, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field96, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field97, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field98, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field99, 0),\
	APP_DEFSDMEMBER(T_STRING,  pr_of_country, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field100, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field101, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field102, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field103, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field104, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field105, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field106, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field107, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field108, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field109, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field110, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field111, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field112, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_APP_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_APP_INFO_H__*/
