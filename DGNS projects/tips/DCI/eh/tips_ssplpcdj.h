/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_ssplpcdj.eh
�ļ�����:tips_ssplpcdj;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:21 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_ssplpcdj (˰���������εǼǱ�)
˵    ��:����������ʱ�Ǽ���Ϣ.
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_SSPLPCDJ_EH__
#define __TIPS_SSPLPCDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SSPLPCDJ
{
  char   zwrq[8+1];              /*��������*/
              /**/
  char   pljydm[5+1];              /*�������״���*/
              /**/
  char   pljylsh[8+1];              /*����������ˮ��*/
              /**/
  char   plpch[10+1];              /*�������κ�*/
              /**/
  int    pclsh;              /*������ˮ��*/
              /**/
  int    ykbs;              /*Ӧ�۱���*/
              /**/
  double  ykje;              /*Ӧ�۽��*/
              /**/
  int    skbs;              /*ʵ�۱���*/
              /**/
  double  skje;              /*ʵ�۽��*/
              /**/
  int    zjsbbs;              /*����ʧ�ܱ���*/
              /**/
  char   qqzjwjm[60+1];              /*���������ļ���*/
              /**/
  char   zjjgwjm[60+1];              /*��������ļ���*/
              /**/
  char   xym[8+1];              /*��Ӧ��*/
              /**/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /**/
  char   czbd[1+1];              /*��������*/
              /*��ǰ�������㣺�������׵�ǰ��������������
                1 ��ʼ��
                2 �����������ȴ����
                3 ����ļ����
                4 ���������ļ��������*/
  char   clqsrq[8+1];              /*������ʼ����*/
              /**/
  char   clqssj[8+1];              /*������ʼʱ��*/
              /**/
  char   cljsrq[8+1];              /*�����������*/
              /**/
  char   cljssj[8+1];              /*�������ʱ��*/
              /**/
  char   byzd[60+1];              /*�����ֶ�*/
              /**/
}SDB_TIPS_SSPLPCDJ;

#define SD_DATA SDB_TIPS_SSPLPCDJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,pljydm,0),\
  DEFSDMEMBER(T_STRING,pljylsh,0),\
  DEFSDMEMBER(T_STRING,plpch,0),\
  DEFSDMEMBER(T_LONG,pclsh,0),\
  DEFSDMEMBER(T_LONG,ykbs,0),\
  DEFSDMEMBER(T_DOUBLE,ykje,2),\
  DEFSDMEMBER(T_LONG,skbs,0),\
  DEFSDMEMBER(T_DOUBLE,skje,2),\
  DEFSDMEMBER(T_LONG,zjsbbs,0),\
  DEFSDMEMBER(T_STRING,qqzjwjm,0),\
  DEFSDMEMBER(T_STRING,zjjgwjm,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,czbd,0),\
  DEFSDMEMBER(T_STRING,clqsrq,0),\
  DEFSDMEMBER(T_STRING,clqssj,0),\
  DEFSDMEMBER(T_STRING,cljsrq,0),\
  DEFSDMEMBER(T_STRING,cljssj,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_SSPLPCDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSPLPCDJ_EH__*/
