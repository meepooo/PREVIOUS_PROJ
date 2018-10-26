/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_WB_TM_PSB_PERSONAL_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WB_TM_PSB_PERSONAL_INFO (F_WB19.�����Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WB_TM_PSB_PERSONAL_INFO_H__
#define __ICPS_WB_TM_PSB_PERSONAL_INFO_H__
typedef struct TDB_ICPS_WB_TM_PSB_PERSONAL_INFO
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	int   file_order;  /*�ļ����*/
		/*�ļ����*/
	int   id;  /*ID*/
		/*ID*/
	char   app_no[20+1];  /*��������*/
		/*��������*/
	char   id_type[1+1];  /*֤������*/
		/*֤������*/
	char   certi_no[18+1];  /*���֤��*/
		/*���֤��*/
	char   name[90+1];  /*����*/
		/*����*/
	char   gender[1+1];  /*�Ա�*/
		/*�Ա�*/
	char   birth_date[14+1];  /*��������*/
		/*��������*/
	char   marital_status[2+1];  /*����״��*/
		/*����״��*/
	char   mobile_no[20+1];  /*�ֻ�����*/
		/*�ֻ�����*/
	char   home_phone[30+1];  /*��ͥ�绰*/
		/*��ͥ�绰*/
	char   unit_phone[30+1];  /*��λ�绰*/
		/*��λ�绰*/
	char   qualification[2+1];  /*ѧ��*/
		/*ѧ��*/
	char   degree[2+1];  /*ѧλ*/
		/*ѧλ*/
	char   address[700+1];  /*ͨѶ��ַ*/
		/*ͨѶ��ַ*/
	char   reside_addr[700+1];  /*������ַ*/
		/*������ַ*/
	char   mate_certp[1+1];  /*��ż֤������*/
		/*��ż֤������*/
	char   mate_cerno[18+1];  /*��ż֤������*/
		/*��ż֤������*/
	char   mate_name[30+1];  /*��ż����*/
		/*��ż����*/
	char   mate_corp[500+1];  /*��ż������λ*/
		/*��ż������λ*/
	char   mate_phone[30+1];  /*��ż��ϵ�绰*/
		/*��ż��ϵ�绰*/
	char   addr[700+1];  /*��ס��ַ*/
		/*��ס��ַ*/
	char   reside_state[2+1];  /*��ס״��*/
		/*��ס״��*/
	char   comp_nm[700+1];  /*������λ*/
		/*������λ*/
	char   unit_addr[700+1];  /*��λ��ַ*/
		/*��λ��ַ*/
	char   profession[2+1];  /*ְҵ*/
		/*ְҵ*/
	char   comp_trade[2+1];  /*��ҵ*/
		/*��ҵ*/
	char   position[2+1];  /*ְ��*/
		/*ְ��*/
	char   teach_pose[2+1];  /*ְ��*/
		/*ְ��*/
	char   work_date[4+1];  /*����λ������ʼ���*/
		/*����λ������ʼ���*/
	char   infodate[14+1];  /*��Ϣ��������*/
		/*��Ϣ��������*/
	char   create_time[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   is_check_flag[1+1];  /*������˱�ʶ*/
		/*������˱�ʶ*/
	char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_WB_TM_PSB_PERSONAL_INFO;

#define SD_DATA  ICPS_WB_TM_PSB_PERSONAL_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_LONG,  id, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  certi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  birth_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  marital_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  home_phone, 0),\
	APP_DEFSDMEMBER(T_STRING,  unit_phone, 0),\
	APP_DEFSDMEMBER(T_STRING,  qualification, 0),\
	APP_DEFSDMEMBER(T_STRING,  degree, 0),\
	APP_DEFSDMEMBER(T_STRING,  address, 0),\
	APP_DEFSDMEMBER(T_STRING,  reside_addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_certp, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_cerno, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_corp, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_phone, 0),\
	APP_DEFSDMEMBER(T_STRING,  addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  reside_state, 0),\
	APP_DEFSDMEMBER(T_STRING,  comp_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  unit_addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  profession, 0),\
	APP_DEFSDMEMBER(T_STRING,  comp_trade, 0),\
	APP_DEFSDMEMBER(T_STRING,  position, 0),\
	APP_DEFSDMEMBER(T_STRING,  teach_pose, 0),\
	APP_DEFSDMEMBER(T_STRING,  work_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  infodate, 0),\
	APP_DEFSDMEMBER(T_STRING,  create_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_PSB_PERSONAL_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_PSB_PERSONAL_INFO_H__*/
