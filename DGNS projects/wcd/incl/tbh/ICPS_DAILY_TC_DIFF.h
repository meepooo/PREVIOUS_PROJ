/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:DB2
�� �� ��:ICPS_DAILY_TC_DIFF.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[wangzh14925]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_DAILY_TC_DIFF (F_WB30.�ֺܷ˶Բ���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_DAILY_TC_DIFF_H__
#define __ICPS_DAILY_TC_DIFF_H__
typedef struct TDB_ICPS_DAILY_TC_DIFF
{
	char   busi_date[8+1];  /*ҵ������*/
		/*ҵ������*/
	double   total_bal;  /*�����˻����*/
		/*�����˻����*/
	double   reserve_bal;  /*�������˻�*/
		/*�������˻�*/
	double   t_bal;  /*T���в���*/
		/*T���в���*/
	double   reserve_diff; /*����������β��*/
	   /*����������β��*/
	double   financial_diff;  /*��������β��*/
		/*��������β��*/
	double   person_diff;  /*�˹��������*/
		/*�˹��������*/
	double   overplay_diff; /*��ɿ��β��*/
	   /*��ɿ��β��*/       
	double   interest_diff; /*��Ϣ*/  
	    /*��Ϣ*/                                 
	double   daily_diff; /*������*/     
	    /*������*/                         
  char   extend_param1[100+1];  /*��չ1*/
		/*��չ1*/
	char   extend_param2[250+1];  /*��չ2*/
		/*��չ2*/
	char   extend_param3[40+1];  /*��չ3*/
		/*��չ3*/

}ICPS_DAILY_TC_DIFF;

#define SD_DATA ICPS_DAILY_TC_DIFF 
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  total_bal, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  reserve_bal,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  t_bal,2),\
	APP_DEFSDMEMBER(T_DOUBLE,  reserve_diff, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  financial_diff, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  person_diff, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  overplay_diff, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  interest_diff, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  daily_diff, 0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)

	APP_DECLAREFIELDS(SD_ICPS_DAILY_TC_DIFF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_DAILY_TC_DIFF__*/
