/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE
�� �� ��:ICPS_JB_EXTINFO.h
�ļ�����:ICPS_JB_EXTINFO;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:����֧�������Ʒ��
�� �� Ա:
����ʱ��:2017-08-10 15:06:30 [By qinsb@hundsun.com]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_EXTINFO ()
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __ICPS_JB_EXTINFO_H__
#define __ICPS_JB_EXTINFO_H__

typedef struct
{
    char    ptrq[8+1];          /*ƽ̨����*/
    char    ptlsh[10+1];          /*ƽ̨��ˮ��*/
    char    reqmsgid[64+1];          /**/
    char    applyno[64+1];          /**/
    char    isplatadm[1+1];          /*ƽ̨���Ƿ�׼��*/
    char    platunadmreason[1024+1];          /*ƽ̨����׼��ԭ��*/
    char    platcreditamt[18+1];          /*ƽ̨�����Ŷ��*/
    char    isjbprecreditcust[1+1];          /*�Ƿ����Ԥ���ſͻ�*/
    char    loanrate[8+1];          /*��������*/
    char    period[64+1];          /*��Ʒ����*/
    char    repaytype[64+1];          /*���ʽ*/
    char    risklevel[32+1];          /*��������*/
    char    repayabilitylvl[32+1];          /*��ծ��������*/
    char    changereason[1024+1];          /*�������ۡ�����ԭ��*/
}ST_ICPS_JB_EXTINFO;
#define SD_DATA  ST_ICPS_JB_EXTINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,isplatadm, 0),\
    DEFSDMEMBER(T_STRING,platunadmreason, 0),\
    DEFSDMEMBER(T_STRING,platcreditamt, 0),\
    DEFSDMEMBER(T_STRING,isjbprecreditcust, 0),\
    DEFSDMEMBER(T_STRING,loanrate, 0),\
    DEFSDMEMBER(T_STRING,period, 0),\
    DEFSDMEMBER(T_STRING,repaytype, 0),\
    DEFSDMEMBER(T_STRING,risklevel, 0),\
    DEFSDMEMBER(T_STRING,repayabilitylvl, 0),\
    DEFSDMEMBER(T_STRING,changereason, 0)
DECLAREFIELDS(SD_ICPS_JB_EXTINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
