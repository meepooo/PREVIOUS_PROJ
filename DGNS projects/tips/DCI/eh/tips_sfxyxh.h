/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_sfxyxh.eh
�ļ�����:tips_sfxyxh;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_sfxyxh (����Э����ű�)
˵    ��:������ţ���������Э�����
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_SFXYXH_EH__
#define __TIPS_SFXYXH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SFXYXH
{
  char   xh1[10+1];              /*���1*/
              /*���1*/
  char   xh2[12+1];              /*���2*/
              /*���2*/
  char   xh3[10+1];              /*���3*/
              /*���3*/
}SDB_TIPS_SFXYXH;

#define SD_DATA SDB_TIPS_SFXYXH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,xh1,0),\
  DEFSDMEMBER(T_STRING,xh2,0),\
  DEFSDMEMBER(T_STRING,xh3,0)
	DECLAREFIELDS(SD_TIPS_SFXYXH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SFXYXH_EH__*/
