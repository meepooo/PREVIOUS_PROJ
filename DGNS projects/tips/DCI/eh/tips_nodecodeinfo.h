/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_nodecodeinfo.eh
�ļ�����:tips_nodecodeinfo;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_nodecodeinfo (�ڵ����)
˵    ��:�ڵ����

************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_NODECODEINFO_EH__
#define __TIPS_NODECODEINFO_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_NODECODEINFO
{
  char   nodecode[12+1];              /*�ڵ����*/
              /*�ڵ����*/
  char   nodename[60+1];              /*�ڵ�����*/
              /*�ڵ�����*/
  char   ofnodetype[1+1];              /*�ڵ���������*/
              /*�ڵ���������*/
  char   nodedn[150+1];              /*�ڵ���֤��ʶ*/
              /*�ڵ���֤��ʶ*/
  char   opersign[1+1];              /*������־*/
              /*������־
                ���ڱ�ʶ���ݸ��µ����ͣ������¼�����*/
  char   effectdate[10+1];              /*��Ч����*/
              /*��Ч����
                ������¼����Ч���ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊ����ʱ��Ϊ�������ڣ���������Ϊɾ��ʱ��ΪʧЧ����*/
  char   updatearea[10+1];              /*���·�Χ*/
              /*���·�Χ
                �������*/
  char   nodestatus[1+1];              /*�ڵ�״̬*/
              /*�ڵ�״̬(�������ֶ�)
                1��¼
                2����
                3ǩ��
                4ͣ��
                */
}SDB_TIPS_NODECODEINFO;

#define SD_DATA SDB_TIPS_NODECODEINFO
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,nodecode,0),\
  DEFSDMEMBER(T_STRING,nodename,0),\
  DEFSDMEMBER(T_STRING,ofnodetype,0),\
  DEFSDMEMBER(T_STRING,nodedn,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0),\
  DEFSDMEMBER(T_STRING,nodestatus,0)
	DECLAREFIELDS(SD_TIPS_NODECODEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_NODECODEINFO_EH__*/
