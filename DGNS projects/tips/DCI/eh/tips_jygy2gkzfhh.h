/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_jygy2gkzfhh.eh
�ļ�����:tips_jygy2gkzfhh;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:21 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_jygy2gkzfhh (���׹�Ա�͹���֧���кŶ��ձ�)
˵    ��:���׹�Ա�͹���֧���кŶ��ձ�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_JYGY2GKZFHH_EH__
#define __TIPS_JYGY2GKZFHH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_JYGY2GKZFHH
{
  char   dqdh[10+1];              /*��������*/
              /*��������*/
  char   jgdh[10+1];              /*��������*/
              /*��������*/
  char   czyh[16+1];              /*���׹�Ա*/
              /*����Ա��*/
  char   zddh[16+1];              /*�ն˴���*/
              /**/
  int    czyjb;              /*��Ա����*/
              /*��Ա����
                �������ֵ�-"system_gyjb"ά��
                */
  char   czymc[20+1];              /*��Ա����*/
              /*����Ա����*/
  char   payeebankno[12+1];              /*����֧���к�*/
              /**/
}SDB_TIPS_JYGY2GKZFHH;

#define SD_DATA SDB_TIPS_JYGY2GKZFHH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,czyh,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_LONG,czyjb,0),\
  DEFSDMEMBER(T_STRING,czymc,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0)
	DECLAREFIELDS(SD_TIPS_JYGY2GKZFHH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_JYGY2GKZFHH_EH__*/
