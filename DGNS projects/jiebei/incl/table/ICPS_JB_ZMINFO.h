/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE
�� �� ��:ICPS_JB_zminfo.h
�ļ�����:ICPS_JB_ZMINFO;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:����֧�������Ʒ��
�� �� Ա:
����ʱ��:2017-08-11 11:07:53 [By qinsb@hundsun.com]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_ZMINFO (������֥����Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __ICPS_JB_ZMINFO_H__
#define __ICPS_JB_ZMINFO_H__

typedef struct
{
    char    ptrq[8+1];                     /*ƽ̨����*/
    char    ptlsh[10+1];                 /*ƽ̨��ˮ��*/
    char    reqmsgid[64+1];                /*������Ψһ��ʾ*/
    char    applyno[64+1];                   /*������Ψһ��ʶ*/
    char    creditscore_success[1+1];          /*֥����������-�ɹ���־*/
    char    creditscore_biz_no[64+1];          /*֥����������-bizno*/
    char    creditscore_zmscore[8+1];          /*֥����������-֥���*/
    char    watchlistii_success[1+1];          /*֥����ҵ��ע����-�ɹ���־*/
    char    watchlistii_biz_no[64+1];          /*֥����ҵ��ע����-bizno*/
    char    watchlistii_matched[1+1];          /*֥����ҵ��ע����-�Ƿ��ע*/
    char    ivs_success[1+1];             /*֥����թ��ע�嵥-�ɹ���־*/
    char    ivs_hit[8+1];                 /*֥����թ��ע�嵥-�Ƿ����*/
    char    ivs_biz_no[64+1];             /*֥����թ��ע�嵥-bizno*/
    char    company_name[120+1];          /*���ڹ�˾*/
    char    occupation[30+1];              /*ְҵ����*/
    char    have_car_flag[4+1];          /*�Ƿ��г�*/
    char    have_fang_flag[4+1];          /*�Ƿ��з�*/
    char    auth_fin_last_1mcnt[3+1];          /*���һ����������ѯ���ڻ�����*/
    char    auth_fin_last_3mcnt[3+1];          /*���������������ѯ���ڻ�����*/
    char    auth_fin_last_6mcnt[3+1];          /*���������������ѯ���ڻ�����*/
    char    ovd_order_cnt_6m[3+1];          /*��������������ܱ���*/
    char    ovd_order_amt_6m[18+1];          /*��������������ܽ��*/
    char    mobile_fixed_days[5+1];          /*�ֻ����ȶ�����*/
    char    adr_stability_days[5+1];          /*��ַ�ȶ�����*/
    char    last6mavgassettotal[18+1];          /*��������������ʲ��վ�ֵ*/
    char    tot_pay_amt_6m[18+1];               /*���������֧���ܽ��*/
    char    xfdc_index[18+1];                   /*���ѵ���*/
    char    positive_biz_cnt_1y[5+1];           /*���һ����Լ������*/
    int     pbocinfo;                           /*����������Ϣ */
}ST_ICPS_JB_ZMINFO;
#define SD_DATA  ST_ICPS_JB_ZMINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,creditscore_success, 0),\
    DEFSDMEMBER(T_STRING,creditscore_biz_no, 0),\
    DEFSDMEMBER(T_STRING,creditscore_zmscore, 0),\
    DEFSDMEMBER(T_STRING,watchlistii_success, 0),\
    DEFSDMEMBER(T_STRING,watchlistii_biz_no, 0),\
    DEFSDMEMBER(T_STRING,watchlistii_matched, 0),\
    DEFSDMEMBER(T_STRING,ivs_success, 0),\
    DEFSDMEMBER(T_STRING,ivs_hit, 0),\
    DEFSDMEMBER(T_STRING,ivs_biz_no, 0),\
    DEFSDMEMBER(T_STRING,company_name, 0),\
    DEFSDMEMBER(T_STRING,occupation, 0),\
    DEFSDMEMBER(T_STRING,have_car_flag, 0),\
    DEFSDMEMBER(T_STRING,have_fang_flag, 0),\
    DEFSDMEMBER(T_STRING,auth_fin_last_1mcnt, 0),\
    DEFSDMEMBER(T_STRING,auth_fin_last_3mcnt, 0),\
    DEFSDMEMBER(T_STRING,auth_fin_last_6mcnt, 0),\
    DEFSDMEMBER(T_STRING,ovd_order_cnt_6m, 0),\
    DEFSDMEMBER(T_STRING,ovd_order_amt_6m, 0),\
    DEFSDMEMBER(T_STRING,mobile_fixed_days, 0),\
    DEFSDMEMBER(T_STRING,adr_stability_days, 0),\
    DEFSDMEMBER(T_STRING,last6mavgassettotal, 0),\
    DEFSDMEMBER(T_STRING,tot_pay_amt_6m, 0),\
    DEFSDMEMBER(T_STRING,xfdc_index, 0),\
    DEFSDMEMBER(T_STRING,positive_biz_cnt_1y, 0),\
    DEFSDMEMBER(T_LONG,pbocinfo, 0)
DECLAREFIELDS(SD_ICPS_JB_ZMINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
