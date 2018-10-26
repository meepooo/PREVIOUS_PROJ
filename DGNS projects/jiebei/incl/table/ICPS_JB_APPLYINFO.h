/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE
�� �� ��:ICPS_JB_applyinfo.h
�ļ�����:ICPS_JB_APPLYINFO;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:����֧�������Ʒ��
�� �� Ա:
����ʱ��:2017-08-10 15:06:30 [By qinsb@hundsun.com]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_APPLYINFO ()
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __ICPS_JB_APPLYINFO_H__
#define __ICPS_JB_APPLYINFO_H__

typedef struct
{
    char    ptrq[8+1];          /**/
    char    ptlsh[10+1];          /**/
    char    version[8+1];          /*�汾��*/
    char    appid[32+1];          /*ϵͳ��ʶ*/
    char    function[50+1];          /*���ױ���*/
    char    reqtimezone[32+1];          /*���ͷ�����ʱ��*/
    char    reqtime[16+1];          /*���ķ���ʱ��*/
    char    reqmsgid[64+1];          /*������Ψһ��ʾ*/
    char    signtype[16+1];          /*ǩ���㷨����*/
    char    inputcharset[16+1];          /*�����ַ�����*/
    char    reserve[32+1];          /*Ԥ����*/
    char    applyno[64+1];          /*���뵥��*/
    char    certtype[2+1];          /*֤������*/
    char    certno[32+1];          /*֤������*/
    char    certvalidenddate[8+1];          /*֤����Ч��*/
    char    name[32+1];          /*����*/
	char    customerno[64+1];     /*�ͻ���� */
    char    mobileno[32+1];          /*�ֻ���*/
    char    occupation[1+1];				/*ְҵ*/
    char	address[256+1];          /*��ϸ��ַ*/ 
    char	city[20+1];           /*����*/        
    char	prov[20+1];           /*ʡ��*/        
    char	area[20+1];           /*����*/        
    char    zmauthflag[1+1];          /*֥����Ȩ�ɹ���ʾ*/
    char    hasjbadmit[1+1];          /*�Ƿ�֮ǰ���н��¶��*/
    char    applystat[1+1];          /*����״̬*/
    char    reqcode[6+1];          /*������Ӧ��*/
    char    reqmsg[255+1];          /*������Ӧ��Ϣ*/
    char    reqdate[8+1];          /*��������*/
    char    reqtime1[10+1];          /*����ʱ��*/
	char    reqtraceno[64+1];        /*������ˮ��*/
    char    isadmit[1+1];          /*�Ƿ��Ƽ�׼��*/
    char    creditno[32+1];          /*���ű��*/
    char    creditamt[18+1];          /*�Ƽ�׼��ʱ���Ƽ��Ķ��*/
    char    creditrate[8+1];          /*�Ƽ�׼��ʱ���Ƽ�������*/
    char    refusecode[64+1];          /*�Ƽ��ܾ�ʱ���ܾ���*/
    char    refusemsg[1024+1];          /*�Ƽ��ܾ�ʱ���ܾ�ԭ��*/
    char    respcode[6+1];          /*������Ӧ��*/
    char    respmsg[255+1];          /*������Ӧ��Ϣ*/
    char    retry[1+1];          /*�Ƿ����� */
    char    resultstat[1+1];          /*�����״̬*/
    char    respdate[8+1];          /*��������*/
    char    resptime[10+1];          /*����ʱ��*/
}ST_ICPS_JB_APPLYINFO;
#define SD_DATA  ST_ICPS_JB_APPLYINFO
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
    DEFSDMEMBER(T_STRING,certvalidenddate, 0),\
    DEFSDMEMBER(T_STRING,name, 0),\
    DEFSDMEMBER(T_STRING,customerno, 0),\
    DEFSDMEMBER(T_STRING,mobileno, 0),\
    DEFSDMEMBER(T_STRING,occupation, 0),\
    DEFSDMEMBER(T_STRING,address, 0),\
    DEFSDMEMBER(T_STRING,city, 0),\
    DEFSDMEMBER(T_STRING,prov, 0),\
    DEFSDMEMBER(T_STRING,area, 0),\
    DEFSDMEMBER(T_STRING,zmauthflag, 0),\
    DEFSDMEMBER(T_STRING,hasjbadmit, 0),\
    DEFSDMEMBER(T_STRING,applystat, 0),\
    DEFSDMEMBER(T_STRING,reqcode, 0),\
    DEFSDMEMBER(T_STRING,reqmsg, 0),\
    DEFSDMEMBER(T_STRING,reqdate, 0),\
    DEFSDMEMBER(T_STRING,reqtime1, 0),\
	DEFSDMEMBER(T_STRING,reqtraceno, 0),\
    DEFSDMEMBER(T_STRING,isadmit, 0),\
    DEFSDMEMBER(T_STRING,creditno, 0),\
    DEFSDMEMBER(T_STRING,creditamt, 0),\
    DEFSDMEMBER(T_STRING,creditrate, 0),\
    DEFSDMEMBER(T_STRING,refusecode, 0),\
    DEFSDMEMBER(T_STRING,refusemsg, 0),\
    DEFSDMEMBER(T_STRING,respcode, 0),\
    DEFSDMEMBER(T_STRING,respmsg, 0),\
    DEFSDMEMBER(T_STRING,retry, 0),\
    DEFSDMEMBER(T_STRING,resultstat, 0),\
    DEFSDMEMBER(T_STRING,respdate, 0),\
    DEFSDMEMBER(T_STRING,resptime, 0)
DECLAREFIELDS(SD_ICPS_JB_APPLYINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
