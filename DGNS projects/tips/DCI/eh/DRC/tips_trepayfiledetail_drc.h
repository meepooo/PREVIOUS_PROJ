/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_trepayfiledetail_drc.h
�ļ�����:tips_trepayfiledetail_eh;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2017-5-31 15:56:00 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_trepayfiledetail_drc.h
˵    ��:TIPS����֧���ļ���ϸ
���ڵǼ�TIPS����֧����ϸ��Ϣ
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_TREPAYFILEDETAIL_DRC_EH__
#define __TIPS_TREPAYFILEDETAIL_DRC_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TREPAYFILEDETAIL
{
  char   trandate[8+1];
  long   transeq;
  long   seqno;
  char   bdgorgcode[15+1];
  char   funcsbtcode[30+1];
  char   ecnomicsubjectcode[30+1];
  double   amt;
  char   acctprop[2+1];
  char   remark1[10+1];
  char   remark2[20+1];
  char   remark3[50+1];
  char   remark4[100+1];
  char   remark5[200+1];
}SDB_TIPS_TREPAYFILEDETAIL;

#define SD_DATA SDB_TIPS_TREPAYFILEDETAIL
#define	SD_MEMBERS\
  DEFSDMEMBER(T_STRING,trandate,0),\
  DEFSDMEMBER(T_LONG,transeq,2),\
  DEFSDMEMBER(T_LONG,seqno,2),\
  DEFSDMEMBER(T_STRING,bdgorgcode,0),\
  DEFSDMEMBER(T_STRING,funcsbtcode,0),\
  DEFSDMEMBER(T_STRING,ecnomicsubjectcode,0),\
  DEFSDMEMBER(T_DOUBLE,amt,2),\
  DEFSDMEMBER(T_STRING,acctprop,0),\
  DEFSDMEMBER(T_STRING,remark1,0),\
  DEFSDMEMBER(T_STRING,remark2,0),\
  DEFSDMEMBER(T_STRING,remark3,0),\
  DEFSDMEMBER(T_STRING,remark4,0),\
  DEFSDMEMBER(T_STRING,remark5,0)
  DECLAREFIELDS(SD_TIPS_TREPAYFILEDETAIL)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TREPAYFILEDETAIL_DRC_EH__*/
