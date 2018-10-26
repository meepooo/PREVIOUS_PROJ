/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_BANK_GROUP_MEMBER.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_BANK_GROUP_MEMBER
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_BANK_GROUP_MEMBER_H__
#define __ICPS_WBC_TM_BANK_GROUP_MEMBER_H__
typedef struct TDB_ICPS_WBC_TM_BANK_GROUP_MEMBER
{
  char		busi_date[8+1];
  int 	 	file_order;
  char 	 	member_id[20+1];                    /*˳���      */
  char		bank_group_id[5+1];           /*���ű��    */
  char		bank_no[10+1];                /*���к�      */
  double	bank_proportion;              /*���г��ʱ���*/
  char		product_category[6+1];        /*��Ʒ����    */
  int 	 	priority;                     /*�������ȼ�  */
  char		is_check_flag[1+1];
  char		extend_param1[100+1];
  char		extend_param2[250+1];
  char		extend_param3[40+1];
}ICPS_WBC_TM_BANK_GROUP_MEMBER;

#define SD_DATA  ICPS_WBC_TM_BANK_GROUP_MEMBER
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date         ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order        ,0),\
  APP_DEFSDMEMBER(T_STRING,    member_id         ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_group_id     ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_no           ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  bank_proportion   ,2),\
  APP_DEFSDMEMBER(T_STRING,  product_category  ,0),\
  APP_DEFSDMEMBER(T_LONG,    priority          ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag     ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1     ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2     ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3     ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_BANK_GROUP_MEMBER)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_BANK_GROUP_MEMBER_H__*/
