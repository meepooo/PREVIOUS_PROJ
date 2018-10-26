/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE
�� �� ��:ICPS_JB_bankinfo.h
�ļ�����:ICPS_JB_BANKINFO;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:����֧�������Ʒ��
�� �� Ա:
����ʱ��:2017-08-10 15:06:30 [By qinsb@hundsun.com]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_BANKINFO ()
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __ICPS_JB_BANKINFO_H__
#define __ICPS_JB_BANKINFO_H__

typedef struct
{
    char    ptrq[8+1];                        /*ƽ̨����*/
    char    ptlsh[10+1];                      /*ƽ̨��ˮ��*/
    char    reqmsgid[64+1];                   /*������Ψһ��ʾ*/
    char    applyno[64+1];                    /*������Ψһ��ʶ*/
    char    isexistcust[1+1];                  /*�Ƿ�����ͻ�*/
    char    isexistdebtcust[1+1];                /*�Ƿ������ǿ��ͻ�*/
    char    balance[18+1];                     /*�������*/
    char    avgbalancelast3days[18+1];                /*��3�����վ����*/
    char    avgbalancelast6days[18+1];                /*��6�����վ����*/
    char    incomelast3m[18+1];                /*��3����������ˮ��������*/
    char    paylast3m[18+1];                  /*��3����������ˮ֧�������*/
    char    incomelast6m[18+1];                /*��6����������ˮ��������*/
    char    paylast6m[18+1];                  /*��6����������ˮ֧�������*/
    char    isexistccust[1+1];                /*�Ƿ�������ÿ��ͻ�*/
    char    currccamt[18+1];                  /*�������ÿ����Ŷ��*/
    char    currdisburseccamt[18+1];                /*�������ÿ���ǰʹ�ö��*/
    char    isexistfincust[1+1];                /*�Ƿ������ƿͻ�*/
    char    finbalance[18+1];                  /*������*/
    char    avgfinballast6m[18+1];                /*��6�����վ������*/
    char    isexistinsurancecus[1+1];                /*�Ƿ�������տͻ�*/
    char    isexistloancust[1+1];                /*�Ƿ��������ͻ�*/
    char    operationloanbal[18+1];                /*��Ӫ����������*/
    char    personalcreditbal[18+1];                /*����������������*/
    char    autoloanbal[18+1];                /*�������*/
    char    autoasset[18+1];                  /*������ֵ������*/
    char    houseloanbal[18+1];                /*�������*/
    char    houseasset[18+1];                /*������ֵ������*/
    char    isstockcust[1+1];                  /*�Ƿ�֤ȯ�ͻ�*/
    char    isthirddepository[1+1];          /*�Ƿ��������ܿͻ�*/
    char    ispayrollcust[1+1];              /*�Ƿ��ʴ����ͻ�*/
    char    issocialsecuritycus[1+1];              /*�Ƿ��籣���ɿͻ�*/
    char    islifepaymentcust[1+1];              /*�Ƿ�ˮ��ú���ɿͻ�*/
    char    incorporation[120+1];              /*������λ*/
    char    incorigin[1+1];                    /*������λ������Դ*/
    char    position[120+1];                   /*ְλ*/
    char    positionorigin[1+1];              /*ְλ��Ϣ��Դ*/
    char    industry[120+1];                  /*��ҵ*/
    char    industryorigin[1+1];              /*��ҵ��Ϣ��Դ*/
    char    workyears[3+1];                  /*��������*/
    char    workyearsorigin[1+1];              /*����������Ϣ��Դ*/
    char    income[18+1];                    /*����������*/
    char    incomeorigin[1+1];              /*��������Ϣ��Դ*/
    char    marriagestatus[1+1];              /*����״̬*/
    char    marriageorigin[1+1];              /*����״̬��Ϣ��Դ*/
    char    isoperation[1+1];                /*�Ƿ�Ӫ�ߣ�������ҵ����幤����ҵ????*/
    char    operationorigin[1+1];              /*�Ƿ�Ӫ����Ϣ��Դ*/
    char    isinnerblackcust[1+1];              /*�Ƿ�����ڲ��������ͻ�*/
    char    ispolicecertified[1+1];              /*�Ƿ񹫰��������֤�ɹ�*/
    char    iscourtexeccust[1+1];              /*�Ƿ���б�ִ���˵�������Ϣ*/
    char    isqryhousefund[1+1];              /*�Ƿ��в�ѯ��������Ϣ*/
    char    fundqrydate[8+1];                /*�������ѯʱ��*/
    char    fundmonthamt[18+1];              /*�������ѯ�½��ɶ�*/
    char    fundaccountdate[8+1];              /*�����𿪻�����*/
    char    fundmonthslast6m[3+1];          /*��6�����ۼƽ�������*/
    char    fundamtlast6m[18+1];             /*��6�����ۼƽ��ɽ��*/
    char    fundtotalmonths[3+1];             /*�ܽ�������*/
    char    fundtotalamt[18+1];             /*�ܽ��ɽ��*/
    char    fundmaxamt[18+1];               /*���������ؽ�������*/
    char    isqrysocialsec[1+1];             /*�Ƿ��в�ѯ�籣��Ϣ*/
    char    socialqrydate[8+1];             /*�籣��Ϣ��ѯʱ��*/
    char    pensionqrymonthamt[18+1];             /*���ϱ��ղ�ѯ�½��ɶ�*/
    char    pensionaccountdate[8+1];             /*���ϱ��տ�������*/
    char    pensionmonthslast6m[3+1];             /*��6�������ϱ����ۼƽ�������*/
    char    pensionamtlast6m[18+1];             /*��6�������ϱ����ۼƽ��ɽ��*/
    char    pensiontotalmonths[3+1];             /*���ϱ����ܽ�������*/
    char    pensiontotalamt[18+1];             /*���ϱ����ܽ��ɽ��*/
    char    mdcmonthamt[18+1];               /*ҽ�Ʊ��ղ�ѯ�½��ɶ�*/
    char    mdcaccountdate[8+1];             /*ҽ�Ʊ��տ�������*/
    char    mdcmonthslast6m[3+1];             /*��6����ҽ�Ʊ����ۼƽ�������*/
    char    mdcamtlast6m[18+1];             /*��6����ҽ�Ʊ����ۼƽ��ɽ��*/
    char    mdctotalmonths[3+1];             /*ҽ�Ʊ����ܽ�������*/
    char    mdctotalamt[18+1];             /*ҽ�Ʊ����ܽ��ɽ��*/
    char    isqrydegree[1+1];              /*�Ƿ��в�ѯѧ����Ϣ*/
    char    schoolname[120+1];             /*ԺУ����*/
    char    degreelevel[30+1];             /*ѧ�����*/
    char    degreetype[120+1];             /*ѧ�����*/
    char    entranceyear[8+1];             /*��ѧ���*/
    char    isqrycommunication[1+1];             /*�Ƿ��в�ѯ��Ӫ����Ϣ*/
    char    communication[1+1];             /*��Ӫ��*/
    char    onlinedays[8+1];                  /*����ʱ��*/
    char    totaltelfare[18+1];             /*�ܻ����˵����*/
    char    totalcalhours[8+1];             /*������ͨ��ʱ��*/
    char    isoutblackcust[1+1];             /*�Ƿ�����ⲿ��ѯ������*/
    char    bankencryptedfeatur[4000+1];          /*������ͨ��ʱ��*/
    char    bank_encrypted_meta[1024+1];          /*�Ƿ�����ⲿ��ѯ������*/
}ST_ICPS_JB_BANKINFO;
#define SD_DATA  ST_ICPS_JB_BANKINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,isexistcust, 0),\
    DEFSDMEMBER(T_STRING,isexistdebtcust, 0),\
    DEFSDMEMBER(T_STRING,balance, 0),\
    DEFSDMEMBER(T_STRING,avgbalancelast3days, 0),\
    DEFSDMEMBER(T_STRING,avgbalancelast6days, 0),\
    DEFSDMEMBER(T_STRING,incomelast3m, 0),\
    DEFSDMEMBER(T_STRING,paylast3m, 0),\
    DEFSDMEMBER(T_STRING,incomelast6m, 0),\
    DEFSDMEMBER(T_STRING,paylast6m, 0),\
    DEFSDMEMBER(T_STRING,isexistccust, 0),\
    DEFSDMEMBER(T_STRING,currccamt, 0),\
    DEFSDMEMBER(T_STRING,currdisburseccamt, 0),\
    DEFSDMEMBER(T_STRING,isexistfincust, 0),\
    DEFSDMEMBER(T_STRING,finbalance, 0),\
    DEFSDMEMBER(T_STRING,avgfinballast6m, 0),\
    DEFSDMEMBER(T_STRING,isexistinsurancecus, 0),\
    DEFSDMEMBER(T_STRING,isexistloancust, 0),\
    DEFSDMEMBER(T_STRING,operationloanbal, 0),\
    DEFSDMEMBER(T_STRING,personalcreditbal, 0),\
    DEFSDMEMBER(T_STRING,autoloanbal, 0),\
    DEFSDMEMBER(T_STRING,autoasset, 0),\
    DEFSDMEMBER(T_STRING,houseloanbal, 0),\
    DEFSDMEMBER(T_STRING,houseasset, 0),\
    DEFSDMEMBER(T_STRING,isstockcust, 0),\
    DEFSDMEMBER(T_STRING,isthirddepository, 0),\
    DEFSDMEMBER(T_STRING,ispayrollcust, 0),\
    DEFSDMEMBER(T_STRING,issocialsecuritycus, 0),\
    DEFSDMEMBER(T_STRING,islifepaymentcust, 0),\
    DEFSDMEMBER(T_STRING,incorporation, 0),\
    DEFSDMEMBER(T_STRING,incorigin, 0),\
    DEFSDMEMBER(T_STRING,position, 0),\
    DEFSDMEMBER(T_STRING,positionorigin, 0),\
    DEFSDMEMBER(T_STRING,industry, 0),\
    DEFSDMEMBER(T_STRING,industryorigin, 0),\
    DEFSDMEMBER(T_STRING,workyears, 0),\
    DEFSDMEMBER(T_STRING,workyearsorigin, 0),\
    DEFSDMEMBER(T_STRING,income, 0),\
    DEFSDMEMBER(T_STRING,incomeorigin, 0),\
    DEFSDMEMBER(T_STRING,marriagestatus, 0),\
    DEFSDMEMBER(T_STRING,marriageorigin, 0),\
    DEFSDMEMBER(T_STRING,isoperation, 0),\
    DEFSDMEMBER(T_STRING,operationorigin, 0),\
    DEFSDMEMBER(T_STRING,isinnerblackcust, 0),\
    DEFSDMEMBER(T_STRING,ispolicecertified, 0),\
    DEFSDMEMBER(T_STRING,iscourtexeccust, 0),\
    DEFSDMEMBER(T_STRING,isqryhousefund, 0),\
    DEFSDMEMBER(T_STRING,fundqrydate, 0),\
    DEFSDMEMBER(T_STRING,fundmonthamt, 0),\
    DEFSDMEMBER(T_STRING,fundaccountdate, 0),\
    DEFSDMEMBER(T_STRING,fundmonthslast6m, 0),\
    DEFSDMEMBER(T_STRING,fundamtlast6m, 0),\
    DEFSDMEMBER(T_STRING,fundtotalmonths, 0),\
    DEFSDMEMBER(T_STRING,fundtotalamt, 0),\
    DEFSDMEMBER(T_STRING,fundmaxamt, 0),\
    DEFSDMEMBER(T_STRING,isqrysocialsec, 0),\
    DEFSDMEMBER(T_STRING,socialqrydate, 0),\
    DEFSDMEMBER(T_STRING,pensionqrymonthamt, 0),\
    DEFSDMEMBER(T_STRING,pensionaccountdate, 0),\
    DEFSDMEMBER(T_STRING,pensionmonthslast6m, 0),\
    DEFSDMEMBER(T_STRING,pensionamtlast6m, 0),\
    DEFSDMEMBER(T_STRING,pensiontotalmonths, 0),\
    DEFSDMEMBER(T_STRING,pensiontotalamt, 0),\
    DEFSDMEMBER(T_STRING,mdcmonthamt, 0),\
    DEFSDMEMBER(T_STRING,mdcaccountdate, 0),\
    DEFSDMEMBER(T_STRING,mdcmonthslast6m, 0),\
    DEFSDMEMBER(T_STRING,mdcamtlast6m, 0),\
    DEFSDMEMBER(T_STRING,mdctotalmonths, 0),\
    DEFSDMEMBER(T_STRING,mdctotalamt, 0),\
    DEFSDMEMBER(T_STRING,isqrydegree, 0),\
    DEFSDMEMBER(T_STRING,schoolname, 0),\
    DEFSDMEMBER(T_STRING,degreelevel, 0),\
    DEFSDMEMBER(T_STRING,degreetype, 0),\
    DEFSDMEMBER(T_STRING,entranceyear, 0),\
    DEFSDMEMBER(T_STRING,isqrycommunication, 0),\
    DEFSDMEMBER(T_STRING,communication, 0),\
    DEFSDMEMBER(T_STRING,onlinedays, 0),\
    DEFSDMEMBER(T_STRING,totaltelfare, 0),\
    DEFSDMEMBER(T_STRING,totalcalhours, 0),\
    DEFSDMEMBER(T_STRING,isoutblackcust, 0),\
    DEFSDMEMBER(T_STRING,bankencryptedfeatur, 0),\
    DEFSDMEMBER(T_STRING,bank_encrypted_meta, 0)
DECLAREFIELDS(SD_ICPS_JB_BANKINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
