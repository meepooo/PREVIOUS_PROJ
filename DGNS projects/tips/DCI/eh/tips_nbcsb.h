/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_nbcsb.eh
�ļ�����:tips_nbcsb;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_nbcsb (�ڲ�������)
˵    ��:TIPS�ڲ�������
������Ը�ҵ����ڲ���������
��������ֻ��һ����¼
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_NBCSB_EH__
#define __TIPS_NBCSB_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_NBCSB
{
  char   workdate[8+1];              /*��������*/
              /**/
  char   zwrq[8+1];              /*��������*/
              /*����tips����ʱ�м�ҵ��ƽ̨����������
                ���ǵ�tips��������еĿ���
                */
  char   dqzt[1+1];              /*��ǰ״̬*/
              /*��ǰ״̬
                0-����
                1-ֹͣ
                2-ǿ���˳�
                3-����
                8-���п�ʼ
                */
  char   qdqt[1+1];              /*ǩ��ǩ��*/
              /*ǩ��ǩ��
                0-ǩ��
                1-ǩ��*/
  char   passwd[32+1];              /*ǩ������*/
              /*ǩ������*/
  char   src[12+1];              /*����ڵ����*/
              /*��ҵ���нڵ����:��TIPS�������������ͳһ����*/
  char   des[12+1];              /*���սڵ����*/
              /*tips�ڵ����
                100000000000*/
  char   bankorgcode[12+1];              /*����֧���к�*/
              /**/
  char   ver[10+1];              /*�汾��*/
              /**/
  char   zdgydq[10+1];              /*�Զ���Ա����*/
              /**/
  char   zdgyjg[10+1];              /*�Զ���Ա����*/
              /**/
  char   zdgy[16+1];              /*�Զ���Ա*/
              /*�̶���Ա��
                ����������ʱ�õ�
                4λ�����к�+4λ�̶����*/
  char   zdfhgy[16+1];
  char   zdsqgy[16+1];
  int    plclzdbs;              /*��������������*/
              /*��������������
                ��������������������ywty_ywlx����ƣ����ֶο����������������������ܱ���
                */
  char   kzbz[8+1];              /*��չ��־*/
              /*��չ��־
                �����Զ�����չ*/
  unknow  reserve1;              /*�����ֶ�1*/
              /**/
  unknow  reserve2;              /*�����ֶ�2*/
              /*�����ֶ�2*/
  unknow  reserve3;              /*�����ֶ�3*/
              /*��������������ʱ�м�ҵ��ƽ̨����������*/
  unknow  byzd;              /*�����ֶ�*/
              /**/
}SDB_TIPS_NBCSB;

#define SD_DATA SDB_TIPS_NBCSB
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,dqzt,0),\
  DEFSDMEMBER(T_STRING,qdqt,0),\
  DEFSDMEMBER(T_STRING,passwd,0),\
  DEFSDMEMBER(T_STRING,src,0),\
  DEFSDMEMBER(T_STRING,des,0),\
  DEFSDMEMBER(T_STRING,bankorgcode,0),\
  DEFSDMEMBER(T_STRING,ver,0),\
  DEFSDMEMBER(T_STRING,zdgydq,0),\
  DEFSDMEMBER(T_STRING,zdgyjg,0),\
  DEFSDMEMBER(T_STRING,zdgy,0),\
  DEFSDMEMBER(T_STRING,zdfhgy,0),\
  DEFSDMEMBER(T_STRING,zdsqgy,0),\
  DEFSDMEMBER(T_LONG,plclzdbs,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  unknow  reserve1\
  unknow  reserve2\
  unknow  reserve3\
  unknow  byzd
	DECLAREFIELDS(SD_TIPS_NBCSB)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_NBCSB_EH__*/
