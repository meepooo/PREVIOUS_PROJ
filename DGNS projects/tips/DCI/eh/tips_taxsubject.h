/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_taxsubject.eh
�ļ�����:tips_taxsubject;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_taxsubject (˰Ŀ����)
˵    ��:˰Ŀ����
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_TAXSUBJECT_EH__
#define __TIPS_TAXSUBJECT_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TAXSUBJECT
{
  char   taxsubjectcode[20+1];              /*˰Ŀ����*/
              /*˰Ŀ����*/
  char   taxorgtype[1+1];              /*���ջ�������*/
              /*���ջ�������*/
  char   taxsubjectname[60+1];              /*˰Ŀ����*/
              /*˰Ŀ����*/
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
}SDB_TIPS_TAXSUBJECT;

#define SD_DATA SDB_TIPS_TAXSUBJECT
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,taxsubjectcode,0),\
  DEFSDMEMBER(T_STRING,taxorgtype,0),\
  DEFSDMEMBER(T_STRING,taxsubjectname,0),\
  DEFSDMEMBER(T_STRING,description,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_TAXSUBJECT)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TAXSUBJECT_EH__*/
