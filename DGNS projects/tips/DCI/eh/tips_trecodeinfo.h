/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_trecodeinfo.eh
�ļ�����:tips_trecodeinfo;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_trecodeinfo (�������)
˵    ��:�������

************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_TRECODEINFO_EH__
#define __TIPS_TRECODEINFO_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TRECODEINFO
{
  char   trecode[10+1];              /*�������*/
              /*�������*/
  char   trename[60+1];              /*��������*/
              /*��������*/
  char   trelevel[1+1];              /*���⼶��*/
              /*���⼶��*/
  char   paybankno[12+1];              /*֧���к�*/
              /*֧���к�*/
  char   reckontrecode[10+1];              /*����������*/
              /*����������*/
  char   uptrecode[10+1];              /*����������*/
              /*����������*/
  char   ofprovtrea[10+1];              /*����ʡ�ֿ����*/
              /*����ʡ�ֿ����*/
  char   ofcitytrea[10+1];              /*��������֧�����*/
              /*��������֧�����*/
  char   ofcountytrea[10+1];              /*������֧�����*/
              /*������֧�����*/
  char   ofnodecode[12+1];              /*�����ڵ����*/
              /*�����ڵ����*/
  char   address[80+1];              /*��ַ*/
              /*��ַ*/
  char   postalcode[6+1];              /*��������*/
              /*��������*/
  char   peoplename[10+1];              /*��ϵ������*/
              /*��ϵ������*/
  char   peoplephone[15+1];              /*��ϵ������*/
              /*��ϵ������*/
  char   peoplemobile[11+1];              /*��ϵ���ֻ�*/
              /*��ϵ���ֻ�*/
  char   email[60+1];              /*��������*/
              /*��������*/
  char   opersign[1+1];              /*������־*/
              /*������־
                ���ڱ�ʶ���ݸ��µ����ͣ������¼�����*/
  char   effectdate[10+1];              /*��Ч����*/
              /*��Ч����
                ������¼����Ч���ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊɾ��ʱ��ΪʧЧ����*/
  char   updatearea[10+1];              /*���·�Χ*/
              /*���·�Χ
                �������*/
}SDB_TIPS_TRECODEINFO;

#define SD_DATA SDB_TIPS_TRECODEINFO
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,trecode,0),\
  DEFSDMEMBER(T_STRING,trename,0),\
  DEFSDMEMBER(T_STRING,trelevel,0),\
  DEFSDMEMBER(T_STRING,paybankno,0),\
  DEFSDMEMBER(T_STRING,reckontrecode,0),\
  DEFSDMEMBER(T_STRING,uptrecode,0),\
  DEFSDMEMBER(T_STRING,ofprovtrea,0),\
  DEFSDMEMBER(T_STRING,ofcitytrea,0),\
  DEFSDMEMBER(T_STRING,ofcountytrea,0),\
  DEFSDMEMBER(T_STRING,ofnodecode,0),\
  DEFSDMEMBER(T_STRING,address,0),\
  DEFSDMEMBER(T_STRING,postalcode,0),\
  DEFSDMEMBER(T_STRING,peoplename,0),\
  DEFSDMEMBER(T_STRING,peoplephone,0),\
  DEFSDMEMBER(T_STRING,peoplemobile,0),\
  DEFSDMEMBER(T_STRING,email,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_TRECODEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TRECODEINFO_EH__*/
