/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_CUSTOMER.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_CUSTOMER (F_WB8.�ͻ���Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_CUSTOMER_H__
#define __ICPS_WB_TM_CUSTOMER_H__
typedef struct TDB_ICPS_WB_TM_CUSTOMER
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	char   org[12+1];  /*������*/
		/*������*/
	char   cust_id[20+1];  /*�ͻ����*/
		/*�ͻ����*/
	char   id_num[30+1];  /*֤������*/
		/*֤������*/
	char   id_type[1+1];  /*֤������*/
		/*֤������*/
	char   title[1+1];  /*��ν*/
		/*��ν*/
	char   name[80+1];  /*����*/
		/*����*/
	char   gender[1+1];  /*�Ա�*/
		/*�Ա�*/
	char   brith_date[8+1];  /*����*/
		/*����*/
	char   user_field177[1+1];  /*�����ֶ�177*/
		/*�����ֶ�177*/
	char   user_field178[20+1];  /*�����ֶ�178*/
		/*�����ֶ�178*/
	char   nationality[3+1];  /*����*/
		/*����*/
	char   pr_of_country[1+1];  /*�Ƿ����þ�ס*/
		/*�Ƿ����þ�ס*/
	char   residency_country_cd[3+1];  /*���þ�ס�ع��Ҵ���*/
		/*���þ�ס�ع��Ҵ���*/
	char   user_field179[1+1];  /*�����ֶ�179*/
		/*�����ֶ�179*/
	char   user_field180[1+1];  /*�����ֶ�180*/
		/*�����ֶ�180*/
	char   user_field181[1+1];  /*�����ֶ�181*/
		/*�����ֶ�181*/
	char   user_field182[200+1];  /*�����ֶ�182*/
		/*�����ֶ�182*/
	char   user_field183[20+1];  /*�����ֶ�183*/
		/*�����ֶ�183*/
	char   user_field184[1+1];  /*�����ֶ�184*/
		/*�����ֶ�184*/
	char   user_field185[1+1];  /*�����ֶ�185*/
		/*�����ֶ�185*/
	char   user_field186[14+1];  /*�����ֶ�186*/
		/*�����ֶ�186*/
	char   user_field187[1+1];  /*�����ֶ�187*/
		/*�����ֶ�187*/
	char   mobile_no[20+1];  /*�ƶ��绰*/
		/*�ƶ��绰*/
	char   user_field188[80+1];  /*�����ֶ�188*/
		/*�����ֶ�188*/
	char   user_field189[1+1];  /*�����ֶ�189*/
		/*�����ֶ�189*/
	int   user_field190;  /*�����ֶ�190*/
		/*�����ֶ�190*/
	char   language_ind[4+1];  /*���Դ���*/
		/*���Դ���*/
	char   user_field191[14+1];  /*�����ֶ�191*/
		/*�����ֶ�191*/
	double   user_field192;  /*�����ֶ�192*/
		/*�����ֶ�192*/
	char   user_field193[20+1];  /*�����ֶ�193*/
		/*�����ֶ�193*/
	char   user_field194[14+1];  /*�����ֶ�194*/
		/*�����ֶ�194*/
	char   user_field195[80+1];  /*�����ֶ�195*/
		/*�����ֶ�195*/
	char   user_field196[80+1];  /*�����ֶ�196*/
		/*�����ֶ�196*/
	char   user_field197[1+1];  /*�����ֶ�197*/
		/*�����ֶ�197*/
	char   user_field198[200+1];  /*�����ֶ�198*/
		/*�����ֶ�198*/
	char   user_field199[4+1];  /*�����ֶ�199*/
		/*�����ֶ�199*/
	char   user_field200[4+1];  /*�����ֶ�200*/
		/*�����ֶ�200*/
	char   user_field201[4+1];  /*�����ֶ�201*/
		/*�����ֶ�201*/
	char   user_field202[4+1];  /*�����ֶ�202*/
		/*�����ֶ�202*/
	char   user_field203[4+1];  /*�����ֶ�203*/
		/*�����ֶ�203*/
	char   user_field204[4+1];  /*�����ֶ�204*/
		/*�����ֶ�204*/
	char   user_field205[14+1];  /*�����ֶ�205*/
		/*�����ֶ�205*/
	char   user_field206[14+1];  /*�����ֶ�206*/
		/*�����ֶ�206*/
	char   user_field207[14+1];  /*�����ֶ�207*/
		/*�����ֶ�207*/
	char   user_field208[14+1];  /*�����ֶ�208*/
		/*�����ֶ�208*/
	char   user_field209[14+1];  /*�����ֶ�209*/
		/*�����ֶ�209*/
	char   user_field210[14+1];  /*�����ֶ�210*/
		/*�����ֶ�210*/
	int   user_field211;  /*�����ֶ�211*/
		/*�����ֶ�211*/
	int   user_field212;  /*�����ֶ�212*/
		/*�����ֶ�212*/
	int   user_field213;  /*�����ֶ�213*/
		/*�����ֶ�213*/
	int   user_field214;  /*�����ֶ�214*/
		/*�����ֶ�214*/
	int   user_field215;  /*�����ֶ�215*/
		/*�����ֶ�215*/
	int   user_field216;  /*�����ֶ�216*/
		/*�����ֶ�216*/
	char   user_field217[40+1];  /*�����ֶ�217*/
		/*�����ֶ�217*/
	char   user_field218[40+1];  /*�����ֶ�218*/
		/*�����ֶ�218*/
	char   user_field219[40+1];  /*�����ֶ�219*/
		/*�����ֶ�219*/
	char   user_field220[40+1];  /*�����ֶ�220*/
		/*�����ֶ�220*/
	char   user_field221[40+1];  /*�����ֶ�221*/
		/*�����ֶ�221*/
	char   user_field222[40+1];  /*�����ֶ�222*/
		/*�����ֶ�222*/
	double   user_field223;  /*�����ֶ�223*/
		/*�����ֶ�223*/
	double   user_field224;  /*�����ֶ�224*/
		/*�����ֶ�224*/
	double   user_field225;  /*�����ֶ�225*/
		/*�����ֶ�225*/
	double   user_field226;  /*�����ֶ�226*/
		/*�����ֶ�226*/
	double   user_field227;  /*�����ֶ�227*/
		/*�����ֶ�227*/
	double   user_field228;  /*�����ֶ�228*/
		/*�����ֶ�228*/
	char   user_field229[20+1];  /*�����ֶ�229*/
		/*�����ֶ�229*/
	char   emb_name[26+1];  /*ƴ����*/
		/*ƴ����*/
	int   jpa_version;  /*�ֹ����汾��*/
		/*�ֹ����汾��*/
	char   cust_limit_id[20+1];  /*�ͻ����ID*/
		/*�ͻ����ID*/
	char   last_modified_datetime[14+1];  /*�޸�ʱ��*/
		/*�޸�ʱ��*/
	char   user_field230[10+1];  /*�����ֶ�230*/
		/*�����ֶ�230*/
	char   user_field231[2+1];  /*�����ֶ�231*/
		/*�����ֶ�231*/
	char   surname[20+1];  /*����*/
		/*����*/
	char   user_field232[14+1];  /*�����ֶ�232*/
		/*�����ֶ�232*/
	char   user_field233[3+1];  /*�����ֶ�233*/
		/*�����ֶ�233*/
	char   user_field234[53+1];  /*�����ֶ�234*/
		/*�����ֶ�234*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_CUSTOMER;

#define SD_DATA  ICPS_WB_TM_CUSTOMER
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  title, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  brith_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field177, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field178, 0),\
	APP_DEFSDMEMBER(T_STRING,  nationality, 0),\
	APP_DEFSDMEMBER(T_STRING,  pr_of_country, 0),\
	APP_DEFSDMEMBER(T_STRING,  residency_country_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field179, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field180, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field181, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field182, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field183, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field184, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field185, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field186, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field187, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field188, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field189, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field190, 0),\
	APP_DEFSDMEMBER(T_STRING,  language_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field191, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field192, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field193, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field194, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field195, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field196, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field197, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field198, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field199, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field200, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field201, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field202, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field203, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field204, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field205, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field206, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field207, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field208, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field209, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field210, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field211, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field212, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field213, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field214, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field215, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field216, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field217, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field218, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field219, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field220, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field221, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field222, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field223, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field224, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field225, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field226, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field227, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field228, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field229, 0),\
	APP_DEFSDMEMBER(T_STRING,  emb_name, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_limit_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field230, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field231, 0),\
	APP_DEFSDMEMBER(T_STRING,  surname, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field232, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field233, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field234, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_CUSTOMER)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_CUSTOMER_H__*/
