/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_budgetsubject.eh
�ļ�����:tips_budgetsubject;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_budgetsubject (Ԥ���Ŀ����)
˵    ��:Ԥ���Ŀ����
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_BUDGETSUBJECT_EH__
#define __TIPS_BUDGETSUBJECT_EH__

#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BUDGETSUBJECT
{
  char   budgetsubjectcode[30+1];              /*Ԥ���Ŀ����*/
              /*Ԥ���Ŀ����*/
  char   budgetsubjectname[60+1];              /*Ԥ���Ŀ����*/
              /*Ԥ���Ŀ����*/
  char   subjecttype[1+1];              /*��Ŀ����*/
              /*��Ŀ����*/
  char   iesign[1+1];              /*��֧��־*/
              /*��֧��־*/
  char   budgetattrib[1+1];              /*��Ŀ����*/
              /*��Ŀ����*/
  char   opersign[1+1];              /*������־*/
              /*������־
                ���ڱ�ʶ���ݸ��µ����ͣ������¼�����*/
  char   effectdate[10+1];              /*��Ч����*/
              /*��Ч����
                ������¼����Ч���ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊɾ��ʱ��ΪʧЧ����*/
  char   updatearea[10+1];              /*���·�Χ*/
              /*���·�Χ
                �������*/
}SDB_TIPS_BUDGETSUBJECT;

#define SD_DATA SDB_TIPS_BUDGETSUBJECT
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,budgetsubjectcode,0),\
  DEFSDMEMBER(T_STRING,budgetsubjectname,0),\
  DEFSDMEMBER(T_STRING,subjecttype,0),\
  DEFSDMEMBER(T_STRING,iesign,0),\
  DEFSDMEMBER(T_STRING,budgetattrib,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_BUDGETSUBJECT)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BUDGETSUBJECT_EH__*/
