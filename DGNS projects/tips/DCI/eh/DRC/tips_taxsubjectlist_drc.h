/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_taxsubjectlist_drc.eh
�ļ�����:tips_taxsubjectlist;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_taxsubjectlist
˵    ��:˰Ŀ��ϸ
���ڵǼ�˰Ŀ��ϸ��Ϣ
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_TAXSUBJECTLIST_DRC_EH__
#define __TIPS_TAXSUBJECTLIST_DRC_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct SDB_TIPS_TAXSUBJECTLIST
{
  char   jyrq[8+1];
  char   jylsh[8+1];
  char   projectid[2+1];
  char   detailno[10+1];
  char   taxsubjectcode[20+1];
  char   taxsubjectname[60+1];
  char   taxnumber[10+1];
  double taxamt;
  double facttaxamt;
  double taxrate;
  double exptaxamt;
  double discounttaxamt;
  char   remark1[10+1];
  char   remark2[20+1];
  char   remark3[50+1];
  char   remark4[100+1];
  char   remark5[200+1];
}SDB_TIPS_TAXSUBJECTLIST;

#define SD_DATA SDB_TIPS_TAXSUBJECTLIST
#define	SD_MEMBERS\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jylsh,0),\
  DEFSDMEMBER(T_STRING,projectid,0),\
  DEFSDMEMBER(T_STRING,detailno,0),\
  DEFSDMEMBER(T_STRING,taxsubjectcode,0),\
  DEFSDMEMBER(T_STRING,taxsubjectname,0),\
  DEFSDMEMBER(T_STRING,taxnumber,0),\
  DEFSDMEMBER(T_DOUBLE,taxamt,2),\
  DEFSDMEMBER(T_DOUBLE,facttaxamt,2),\
  DEFSDMEMBER(T_DOUBLE,taxrate,2),\
  DEFSDMEMBER(T_DOUBLE,exptaxamt,2),\
  DEFSDMEMBER(T_DOUBLE,discounttaxamt,2),\
  DEFSDMEMBER(T_STRING,remark1,0),\
  DEFSDMEMBER(T_STRING,remark2,0),\
  DEFSDMEMBER(T_STRING,remark3,0),\
  DEFSDMEMBER(T_STRING,remark4,0),\
  DEFSDMEMBER(T_STRING,remark5,0)
  DECLAREFIELDS(SD_TIPS_TAXSUBJECTLIST)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXSUBJECTLIST_DRC_EH__*/
