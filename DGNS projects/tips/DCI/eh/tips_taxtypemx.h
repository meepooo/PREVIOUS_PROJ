/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_taxtypemx.eh
�ļ�����:tips_taxtypemx;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_taxtypemx
˵    ��:˰����ϸ
���ڵǼǿͻ�����Э����Ϣ
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_TAXTYPEMX_EH__
#define __TIPS_TAXTYPEMX_EH__
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
  char   taxtypeamt[18+1];
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
  DEFSDMEMBER(T_STRING,taxtypeamt,0)
	DECLAREFIELDS(SD_TIPS_TAXTYPEMX)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXTYPEMX_EH__*/
