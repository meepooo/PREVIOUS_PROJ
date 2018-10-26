/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:ICPS_FILE_INFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_FILE_INFO (8.�ļ���Ϣ�����)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_FILE_INFO_H__
#define __ICPS_FILE_INFO_H__
typedef struct TDB_ICPS_FILE_INFO
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	char   busi_no[16+1];  /*ҵ����*/
		/*ҵ���� jiebei-���� jintiao-���� wbank-΢����*/
	char   file_type[60+1];  /*�ļ�����*/
		/*�ļ�����*/
	char   md5_code[64+1];  /*MD5ֵ*/
		/*MD5ֵ 16�����ַ���*/
	char   file_status[1+1];  /*�ļ�״̬*/
		/*�ļ�״̬*/
	char   plt_date[8+1];  /*ƽ̨����*/
		/*ƽ̨����YYYYMMDD*/
	char   plt_serial[16+1];  /*ƽ̨��ˮ��*/
		/*ƽ̨��ˮ��*/
	char   extend_param1[10+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_FILE_INFO;

#define SD_DATA  ICPS_FILE_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  md5_code, 0),\
	APP_DEFSDMEMBER(T_STRING,  file_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  plt_serial, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_FILE_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_FILE_INFO_H__*/
