/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_BANK.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_BANK
˵    ��:���б�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_BANK_H__
#define __ICPS_WBC_TM_BANK_H__
typedef struct TDB_ICPS_WBC_TM_BANK
{
    char            busi_date[8+1];
    int             file_order;
    char            bank_no[10+1];            /*���к�               */
    char            bank_name[40+1];          /*��������             */
    char            paying_acct[100+1];       /*�������˻���         */
    char            is_check_flag[1+1];
    char            extend_param1[100+1];
    char            extend_param2[250+1];
    char            extend_param3[40+1];
}ICPS_WBC_TM_BANK;

#define SD_DATA  ICPS_WBC_TM_BANK
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date      ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order     ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_no        ,0),\
  APP_DEFSDMEMBER(T_STRING,  bank_name      ,0),\
  APP_DEFSDMEMBER(T_STRING,  paying_acct    ,0),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3  ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_TM_BANK)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_TM_BANK_H__*/
              
