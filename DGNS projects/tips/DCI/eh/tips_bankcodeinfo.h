/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_bankcodeinfo.eh
�ļ�����:tips_bankcodeinfo;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_bankcodeinfo (�������д���)
˵    ��:�������д���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_BANKCODEINFO_EH__
#define __TIPS_BANKCODEINFO_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BANKCODEINFO
{
  char   reckbankno[12+1];              /*���������к�*/
              /*���������к�*/
  char   genbankname[60+1];              /*��������*/
              /*��������*/
  char   reckontype[1+1];              /*��������*/
              /*��������*/
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
}SDB_TIPS_BANKCODEINFO;

#define SD_DATA SDB_TIPS_BANKCODEINFO
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,reckbankno,0),\
  DEFSDMEMBER(T_STRING,genbankname,0),\
  DEFSDMEMBER(T_STRING,reckontype,0),\
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
	DECLAREFIELDS(SD_TIPS_BANKCODEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BANKCODEINFO_EH__*/
