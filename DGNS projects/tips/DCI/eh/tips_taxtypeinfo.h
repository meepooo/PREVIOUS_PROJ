/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_taxtypeinfo.eh
�ļ�����:tips_taxtypeinfo;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_taxtypeinfo (˰�ִ���)
˵    ��:˰�ִ���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_TAXTYPEINFO_EH__
#define __TIPS_TAXTYPEINFO_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TAXTYPEINFO
{
  char   taxtypecode[10+1];              /*˰�ִ���*/
              /*˰�ִ���*/
  char   taxorgtype[1+1];              /*���ջ�������*/
              /*���ջ�������*/
  char   taxtypename[60+1];              /*˰������*/
              /*˰������*/
  char   description[80+1];              /*����*/
              /*����*/
  char   opersign[1+1];              /*������־*/
              /*������־
                ���ڱ�ʶ���ݸ��µ����ͣ������¼�����*/
  char   effectdate[10+1];              /*��Ч����*/
              /*��Ч����
                ������¼����Ч���ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊɾ��ʱ��ΪʧЧ����*/
  char   updatearea[10+1];              /*���·�Χ*/
              /*���·�Χ
                �������*/
}SDB_TIPS_TAXTYPEINFO;

#define SD_DATA SDB_TIPS_TAXTYPEINFO
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,taxtypecode,0),\
  DEFSDMEMBER(T_STRING,taxorgtype,0),\
  DEFSDMEMBER(T_STRING,taxtypename,0),\
  DEFSDMEMBER(T_STRING,description,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_TAXTYPEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXTYPEINFO_EH__*/
