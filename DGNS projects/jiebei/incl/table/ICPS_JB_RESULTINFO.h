/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE
�� �� ��:ICPS_JB_RESULTINFO.h
�ļ�����:ICPS_JB_RESULTINFO;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:����֧�������Ʒ��
�� �� Ա:
����ʱ��:2017-08-10 15:06:29 [By qinsb@hundsun.com]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_RESULTINFO ()
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __ICPS_JB_RESULTINFO_H__
#define __ICPS_JB_RESULTINFO_H__

typedef struct
{
    char    ptrq[8+1];          /*ƽ̨����*/
    char    ptlsh[10+1];          /*ƽ̨��ˮ��*/
    char    version[8+1];          /*�汾��*/
    char    appid[32+1];          /*ϵͳ��ʶ*/
    char    function[16+1];          /*���ױ���*/
    char    reqtimezone[32+1];          /*���ͷ�����ʱ��*/
    char    reqtime[16+1];          /*���ķ���ʱ��*/
    char    reqmsgid[64+1];          /*������Ψһ��ʾ*/
    char    signtype[16+1];          /*ǩ���㷨����*/
    char    inputcharset[16+1];          /*�����ַ�����*/
    char    reserve[32+1];          /*Ԥ����*/
    char    applyno[64+1];          /*���뵥��*/
    char    certtype[2+1];          /*֤������*/
    char    certno[32+1];          /*֤������*/
    char    name[32+1];          /*����*/
    char    platformaccess[1+1];          /*��������������Ƿ�ͨ��*/
    char    platformrefusereaso[1024+1];          /*������ͨ����ԭ��*/
    char    platformadmit[18+1];          /*���ͨ����������������*/
    char    platformrate[8+1];          /*���ͨ���������������������*/
    char    riskrating[32+1];          /*��������*/
    char    solvencyratings[32+1];          /*��ծ��������*/
    char    changeresultreason[1024+1];          /*��ȡ����۱��ԭ��*/
    char    resultcode[6+1];          /*��Ӧ��*/
    char    resultmsg[255+1];          /*��Ӧ����*/
    char    isadmit[1+1];          /*�Ƿ��Ƽ�׼��*/
    char    admitmsg[255+1];          /*׼��ԭ��*/
}ST_ICPS_JB_RESULTINFO;
#define SD_DATA  ST_ICPS_JB_RESULTINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,version, 0),\
    DEFSDMEMBER(T_STRING,appid, 0),\
    DEFSDMEMBER(T_STRING,function, 0),\
    DEFSDMEMBER(T_STRING,reqtimezone, 0),\
    DEFSDMEMBER(T_STRING,reqtime, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,signtype, 0),\
    DEFSDMEMBER(T_STRING,inputcharset, 0),\
    DEFSDMEMBER(T_STRING,reserve, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,certtype, 0),\
    DEFSDMEMBER(T_STRING,certno, 0),\
    DEFSDMEMBER(T_STRING,name, 0),\
    DEFSDMEMBER(T_STRING,platformaccess, 0),\
    DEFSDMEMBER(T_STRING,platformrefusereaso, 0),\
    DEFSDMEMBER(T_STRING,platformadmit, 0),\
    DEFSDMEMBER(T_STRING,platformrate, 0),\
    DEFSDMEMBER(T_STRING,riskrating, 0),\
    DEFSDMEMBER(T_STRING,solvencyratings, 0),\
    DEFSDMEMBER(T_STRING,changeresultreason, 0),\
    DEFSDMEMBER(T_STRING,resultcode, 0),\
    DEFSDMEMBER(T_STRING,resultmsg, 0),\
    DEFSDMEMBER(T_STRING,isadmit, 0),\
    DEFSDMEMBER(T_STRING,admitmsg, 0)
DECLAREFIELDS(SD_ICPS_JB_RESULTINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
