/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_zsjg2gkzfh.eh
�ļ�����:tips_zsjg2gkzfh;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_zsjg2gkzfh (���ջ��غ͹���֧���ж��ձ�)
˵    ��:���ջ��غ͹���֧���ж��ձ�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_ZSJG2GKZFH_EH__
#define __TIPS_ZSJG2GKZFH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_ZSJG2GKZFH
{
  char   dqdh[10+1];              /*��������*/
              /**/
  char   jgdh[10+1];              /*��������*/
              /**/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /**/
  char   taxorgtype[1+1];              /*���ջ�������*/
              /*1-��˰ 2-��˰
                3-���� 4-����
                5-���� 6-�籣*/
  unknow  taxorgname;              /*���ջ�������*/
              /**/
  char   payeebankno[12+1];              /*����֧���к�*/
              /**/
  unknow  trename;              /*��������*/
              /**/
  char   xgrq[8+1];              /*�޸�����*/
              /**/
  char   xgsj[8+1];              /*�޸�ʱ��*/
              /*�޸�ʱ��*/
  char   xggy[10+1];              /*�޸Ĺ�Ա*/
              /*�޸Ĺ�Ա*/
}SDB_TIPS_ZSJG2GKZFH;

#define SD_DATA SDB_TIPS_ZSJG2GKZFH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,taxorgtype,0),\
  unknow  taxorgname\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  unknow  trename\
  DEFSDMEMBER(T_STRING,xgrq,0),\
  DEFSDMEMBER(T_STRING,xgsj,0),\
  DEFSDMEMBER(T_STRING,xggy,0)
	DECLAREFIELDS(SD_TIPS_ZSJG2GKZFH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_ZSJG2GKZFH_EH__*/
