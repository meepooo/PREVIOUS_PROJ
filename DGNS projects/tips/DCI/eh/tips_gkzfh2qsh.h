/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_gkzfh2qsh.eh
�ļ�����:tips_gkzfh2qsh;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_gkzfh2qsh (����֧���к���ҵ���������ж��ձ�)
˵    ��:����֧���к���ҵ���������ж��ձ�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_GKZFH2QSH_EH__
#define __TIPS_GKZFH2QSH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_GKZFH2QSH
{
  char   payeebankno[12+1];              /*����֧���к�*/
              /*�������*/
  /*unknow  trename;              ��������*/
  char   trename[128+1];
              /**/
  char   paybkcode[12+1];              /*�������к�*/
              /*�������к�
                ��ҵ����������
                */
	/* unknow  paybkname;              ����������*/
  char  paybkname[60+1];
  char  payeeacct[32+1];
  char  payeename[60+1];
              /**/
  char   xgrq[8+1];              /*�޸�����*/
              /*�޸�����*/
  char   xgsj[8+1];              /*�޸�ʱ��*/
              /*�޸�ʱ��*/
  char   xggy[10+1];              /*�޸Ĺ�Ա*/
              /*�޸Ĺ�Ա*/
}SDB_TIPS_GKZFH2QSH;

#define SD_DATA SDB_TIPS_GKZFH2QSH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,trename,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,paybkname,0),\
  DEFSDMEMBER(T_STRING,payeeacct,0),\
  DEFSDMEMBER(T_STRING,payeename,0),\
  DEFSDMEMBER(T_STRING,xgrq,0),\
  DEFSDMEMBER(T_STRING,xgsj,0),\
  DEFSDMEMBER(T_STRING,xggy,0)

	DECLAREFIELDS(SD_TIPS_GKZFH2QSH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_GKZFH2QSH_EH__*/
