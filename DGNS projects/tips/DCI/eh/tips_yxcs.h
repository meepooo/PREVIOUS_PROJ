/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ��
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_yxcs.eh
�ļ�����:tips_yxcs;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:���ڲ�Ʒ����TIPS�з���
�� �� Ա:tuql
����ʱ��:2009-10-23 13:09:30 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_yxcs (TIPS���в���)
˵    ��:TIPS���в���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_YXCS_EH__
#define __TIPS_YXCS_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_YXCS
{
  char   zwrq[8+1];              /*��������*/
              /**/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /**/
  char   workdate[8+1];              /*��������*/
              /**/
  char   paramtypeno[4+1];              /*�������ͱ��*/
              /*�������ͣ�Ŀǰ�������102��TIPS����ʱ�򣩣�103���������ݲ�ѯ���ޣ���104��ҵ�������ڣ�*/
  char   paramdescrip[80+1];              /*������������*/
              /**/
  char   detailno[16+1];              /*��ϸ���*/
              /**/
  char   detaildescri[80+1];              /*��ϸ�������*/
              /**/
  char   detailvalue[60+1];              /*����ȡֵ*/
              /**/
}SDB_TIPS_YXCS;

#define SD_DATA SDB_TIPS_YXCS
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,paramtypeno,0),\
  DEFSDMEMBER(T_STRING,paramdescrip,0),\
  DEFSDMEMBER(T_STRING,detailno,0),\
  DEFSDMEMBER(T_STRING,detaildescri,0),\
  DEFSDMEMBER(T_STRING,detailvalue,0)
	DECLAREFIELDS(SD_TIPS_YXCS)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_YXCS_EH__*/
