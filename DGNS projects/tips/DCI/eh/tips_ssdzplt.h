/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_ssdzplt.eh
�ļ�����:tips_ssdzplt;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_ssdzplt (˰�ն�������ͷ��)
˵    ��:TIPS�ռ�����ն��˵ǼǱ�--��������ͷ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_SSDZPLT_EH__
#define __TIPS_SSDZPLT_EH__

typedef struct TDB_TIPS_SSDZPLT
{
  char   zwrq[8+1];              /*��������*/
              /*ǰ�û���������*/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /*ǰ�û��ۺ�ǰ����ˮ��*/
  char   workdate[8+1];              /*��������*/
              /*tips��������*/
  char   chkdate[8+1];              /*��������*/
              /*ԭ����ˮ��
                */
  char   chkacctord[4+1];              /*��������*/
              /*��������*/
  char   paybkcode[12+1];              /*�������к�*/
              /*�������к�
                ��������кŶ�Ӧ�������к�
                ����ʱ�Դ�Ϊ��λ*/
  char   payeebankno[12+1];              /*�տ����к�*/
              /*�������֧���к�*/
  char   priorchkacctord[4+1];              /*��һ��������*/
              /*���ֶε�ֵȡ���ζ��˵���һ�����˵����ε�ֵ�����������������ˣ���ֵ���ڱ��ζ������ε�ֵ��*/
  char   chkaccttype[1+1];              /*��������*/
              /*0 �ռ�
                1 ����*/
  int    allnum;              /*�ܱ���*/
              /*�μӱ��ζ��˵Ľɿ����ܱ���*/
  double  allamt;              /*�ܽ��*/
              /*�μӱ��ζ��˵Ľɿ����ܽ��*/
  int    childpacknum;              /*�Ӱ�����*/
              /**/
  int    curpackno;              /*�������*/
              /*�������ʱΪ��ǰ������ţ�δ���ʱ�������Ϊ1*/
  int    curpacknum;              /*��������*/
              /**/
  double  curpackamt;              /*�������*/
              /**/
}SDB_TIPS_SSDZPLT;

#define SD_DATA SDB_TIPS_SSDZPLT
#define SD_MEMBERS\
    DEFSDMEMBER(T_STRING,zwrq,0),\
    DEFSDMEMBER(T_LONG,zhqzlsh,0),\
    DEFSDMEMBER(T_STRING,workdate,0),\
    DEFSDMEMBER(T_STRING,chkdate,0),\
    DEFSDMEMBER(T_STRING,chkacctord,0),\
    DEFSDMEMBER(T_STRING,paybkcode,0),\
    DEFSDMEMBER(T_STRING,payeebankno,0),\
    DEFSDMEMBER(T_STRING,priorchkacctord,0),\
    DEFSDMEMBER(T_STRING,chkaccttype,0),\
    DEFSDMEMBER(T_LONG,allnum,0),\
    DEFSDMEMBER(T_DOUBLE,allamt,2),\
    DEFSDMEMBER(T_LONG,childpacknum,0),\
    DEFSDMEMBER(T_LONG,curpackno,0),\
    DEFSDMEMBER(T_LONG,curpacknum,0),\
    DEFSDMEMBER(T_DOUBLE,curpackamt,2),\

    DECLAREFIELDS(SD_TIPS_SSDZPLT)

#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_SSDZPLT_EH__*/
