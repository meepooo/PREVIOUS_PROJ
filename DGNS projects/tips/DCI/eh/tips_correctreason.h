/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_correctreason.eh
�ļ�����:tips_correctreason;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_correctreason (����ԭ�����)
˵    ��:����ԭ�����
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_CORRECTREASON_EH__
#define __TIPS_CORRECTREASON_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_CORRECTREASON
{
  char   reasoncode[12+1];              /*����ԭ�����*/
              /*����ԭ�����*/
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
}SDB_TIPS_CORRECTREASON;

#define SD_DATA SDB_TIPS_CORRECTREASON
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,reasoncode,0),\
  DEFSDMEMBER(T_STRING,description,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0)
	DECLAREFIELDS(SD_TIPS_CORRECTREASON)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_CORRECTREASON_EH__*/
