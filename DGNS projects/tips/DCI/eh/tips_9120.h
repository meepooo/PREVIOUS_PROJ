/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:�м�ҵ��ƽ̨
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_9120.eh
�ļ�����:tips_9120;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:�м�ҵ���Ʒ��չ���з���
�� �� Ա:
����ʱ��:2009-10-23 16:25:39 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_9120 (9120ͨ��Ӧ��)
˵    ��:�洢9120ͨ��Ӧ��������
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_9120_EH__
#define __TIPS_9120_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_9120
{
  char   zwrq[8+1];              /*��������*/
              /**/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /**/
  char   workdate[8+1];              /*��������*/
              /**/
  char   systime[6+1];              /*Ӧ��ʱ��*/
              /**/
  char   orimsgid[20+1];              /*ԭ���ı�ʶ��*/
              /**/
  char   orimsgno[4+1];              /*ԭ���ı��*/
              /**/
  char   result[5+1];              /*������*/
              /**/
  char   addword[60+1];              /*����*/
              /**/
  char   information[1024+1];              /*��ϸ��Ϣ*/
              /**/
}SDB_TIPS_9120;

#define SD_DATA SDB_TIPS_9120
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,systime,0),\
  DEFSDMEMBER(T_STRING,orimsgid,0),\
  DEFSDMEMBER(T_STRING,orimsgno,0),\
  DEFSDMEMBER(T_STRING,result,0),\
  DEFSDMEMBER(T_STRING,addword,0),\
  DEFSDMEMBER(T_STRING,information,0)
	DECLAREFIELDS(SD_TIPS_9120)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_9120_EH__*/
