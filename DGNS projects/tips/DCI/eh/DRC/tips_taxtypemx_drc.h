/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_taxtypemx_drc.eh
�ļ�����:tips_taxtypemx_eh;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_taxtypemx
˵    ��:˰����ϸ
���ڵǼ�˰����ϸ��Ϣ
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_TAXTYPEMX_DRC_EH__
#define __TIPS_TAXTYPEMX_DRC_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TAXTYPEMX
{
  char   jyrq[8+1];
  char   jylsh[8+1];
  char   spxx[40+1];
  char   projectid[2+1];
  char   taxtypename[80+1];
  char   taxstartdate[8+1];
  char   taxenddate[8+1];
  double taxtypeamt;
  char   taxtypecode[10+1];
  char   taxtype[1+1];
  char   budgetsubjectcode[30+1];
  char   limitdate[8+1];
  char   budgetlevelcode[1+1];
  char   budgetlevelname[60+1];
  char   vicesign[35+1];
  char   detailnum[10+1];
}SDB_TIPS_TAXTYPEMX;

#define SD_DATA SDB_TIPS_TAXTYPEMX
#define	SD_MEMBERS\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jylsh,0),\
  DEFSDMEMBER(T_STRING,spxx,0),\
  DEFSDMEMBER(T_STRING,projectid,0),\
  DEFSDMEMBER(T_STRING,taxtypename,0),\
  DEFSDMEMBER(T_STRING,taxstartdate,0),\
  DEFSDMEMBER(T_STRING,taxenddate,0),\
  DEFSDMEMBER(T_DOUBLE,taxtypeamt,2),\
  DEFSDMEMBER(T_STRING,taxtypecode,0),\
  DEFSDMEMBER(T_STRING,taxtype,0),\
  DEFSDMEMBER(T_STRING,budgetsubjectcode,0),\
  DEFSDMEMBER(T_STRING,limitdate,0),\
  DEFSDMEMBER(T_STRING,budgetlevelcode,0),\
  DEFSDMEMBER(T_STRING,budgetlevelname,0),\
  DEFSDMEMBER(T_STRING,vicesign,0),\
  DEFSDMEMBER(T_STRING,detailnum,0)
  DECLAREFIELDS(SD_TIPS_TAXTYPEMX)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXTYPEMX_DRC_EH__*/
