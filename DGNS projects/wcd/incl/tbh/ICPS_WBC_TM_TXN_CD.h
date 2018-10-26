/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:db2
�� �� ��:ICPS_WBC_TM_TXN_CD.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[fuwd22392]
����ʱ��:2018-06-12 10:00:00 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_WBC_TM_TXN_CD
˵    ��:�����������ã�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __ICPS_WBC_TM_TXN_CD_H__
#define __ICPS_WBC_TM_TXN_CD_H__
typedef struct TDB_ICPS_WBC_TM_TXN_CD
{
    char            busi_date[8+1];              /*          */
    int             file_order;                  /*          */
    char            flow_no[20+1];               /*FLOW_NO fuwd22392 modify  */
    char            org[12+1];                   /*������    */
    char            txn_code[4+1];               /*������    */
    char            txn_desc[80+1];              /*��������  */
    char            txn_class[1+1];              /*TXN_CLASS */
    char            bnp[30+1];                   /*���ɷ�  */
    char            is_check_flag[1+1];          /*          */
    char            extend_param1[100+1];        /*          */
    char            extend_param2[250+1];        /*          */
    char            extend_param3[40+1];         /*          */
}ICPS_WBC_TM_TXN_CD;

#define SD_DATA  ICPS_WBC_TM_TXN_CD
#define SD_MEMBERS \ 
   APP_DEFSDMEMBER(T_STRING,  busi_date      ,0),\
   APP_DEFSDMEMBER(T_LONG,    file_order     ,0),\
   APP_DEFSDMEMBER(T_STRING,    flow_no        ,0),\
   APP_DEFSDMEMBER(T_STRING,  org            ,0),\
   APP_DEFSDMEMBER(T_STRING,  txn_code       ,0),\
   APP_DEFSDMEMBER(T_STRING,  txn_desc       ,0),\
   APP_DEFSDMEMBER(T_STRING,  txn_class      ,0),\
   APP_DEFSDMEMBER(T_STRING,  bnp            ,0),\
   APP_DEFSDMEMBER(T_STRING,  is_check_flag  ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param1  ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param2  ,0),\
   APP_DEFSDMEMBER(T_STRING,  extend_param3  ,0)
   APP_DECLAREFIELDS(SD_ICPS_WBC_TM_TXN_CD)     
 #undef SD_DATA                                   
 #undef SD_MEMBERS                                
                                                  
 #endif  /*end of __ICPS_WBC_TM_TXN_CD_H__*/    
