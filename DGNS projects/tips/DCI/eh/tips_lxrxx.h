/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_lxrxx.eh
�ļ�����:tips_lxrxx;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_lxrxx (��ϵ����Ϣ��)
˵    ��:��ϵ����Ϣ��

************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_LXRXX_EH__
#define __TIPS_LXRXX_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_LXRXX
{
  char   dwdm[20+1];              /*��λ����*/
              /*��λ����
                */
  char   dwmc[80+1];              /*��λ����*/
              /*��λ���� */
  char   glgk[100+1];              /*�������*/
              /*�������*/
  char   lxr[20+1];              /*��ϵ��*/
              /*��ϵ��*/
  char   lxdh[40+1];              /*��ϵ�绰*/
              /*��ϵ�绰*/
  char   bz[200+1];              /*��ע*/
              /*��ע*/
}SDB_TIPS_LXRXX;

#define SD_DATA SDB_TIPS_LXRXX
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dwdm,0),\
  DEFSDMEMBER(T_STRING,dwmc,0),\
  DEFSDMEMBER(T_STRING,glgk,0),\
  DEFSDMEMBER(T_STRING,lxr,0),\
  DEFSDMEMBER(T_STRING,lxdh,0),\
  DEFSDMEMBER(T_STRING,bz,0)
	DECLAREFIELDS(SD_TIPS_LXRXX)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_LXRXX_EH__*/
