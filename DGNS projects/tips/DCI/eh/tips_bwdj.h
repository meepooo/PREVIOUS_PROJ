/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_bwdj.eh
�ļ�����:tips_bwdj;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_bwdj (���ĵǼǱ�)
˵    ��:���ڵǼ���TIPSͨѶ�����󡢻�ִ���ġ�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_BWDJ_EH__
#define __TIPS_BWDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BWDJ
{
  char   sendorgcode[12+1];              /*�����������*/
              /*���ջ��ش��롢�������к�*/
  char   entrustdate[8+1];              /*ί������*/
              /*��ΪTIPS�˷�����Ϊί�����ڣ���Ϊ��ҵ���ж˷�����Ϊ��������*/
  char   packno[8+1];              /*����ˮ��*/
              /**/
  char   msgno[4+1];              /*���ı��*/
              /*����ţ�
                3102--������˰������
                2102--������˰�ѻ�ִ
                1123--ֹ������*/
  char   bwlx[1+1];              /*��������*/
              /*�������ͣ�
                1-TIPS���Ͱ�
                2-TIPS���հ�
                3-TIPSֹ����*/
  char   paybkcode[12+1];              /*�������к�*/
              /**/
  char   bwwjm[60+1];              /*�����ļ���*/
              /**/
  char   zwrq[8+1];              /*��������*/
              /*�����ĵ�����*/
  char   clsj[8+1];              /*����ʱ��*/
              /**/
  char   zhqzlsh[8+1];              /*�ۺ�ǰ����ˮ��*/
              /*�����������ģ�ֻ������ɹ�����ʱ������������ˮ�š�����ֹ����ˮ�ŵ�*/
  char   dqzt[1+1];              /*��ǰ״̬*/
              /*1-���ͳɹ�
                2-���ͳɹ�,�յ�ȷ��Ӧ��
                3-���ͳɹ����յ�������
                4-���ճɹ�
                5-���ճɹ�,����ȷ��Ӧ��
                6-���ճɹ�,���ش�����
                7-���ط�
                8-����Ϊ�ɹ�
                9-����ʧ��
                */
  char   workdate[8+1];              /*��������*/
              /**/
  int    allnum;              /*�ܱ���*/
              /**/
  double  allamt;              /*�ܽ��*/
              /**/
  int    succnum;              /*�ɹ�����*/
              /**/
  double  succamt;              /*�ɹ����*/
              /**/
  int    zfbs;              /*ֹ������*/
              /*�˿��������������*/
  double  zfje;              /*ֹ�����*/
              /*�˿���������*/
  char   respmsginfo[60+1];              /*��Ӧ����Ϣ*/
              /*��������8|����ڵ����12|���ı��Ϻ�20|���ı��4|*/
  char   bwhdrq[8+1];              /*���ĺ˶�����*/
              /**/
  char   bwhdzt[1+1];              /*���ĺ˶�״̬*/
              /*0-����˶� 1-δ�˶� 2-�˶�ƽ 3-�ҷ��� 4-������ 5-�쳣 */
  char   bwhdjg[1+1];              /*���ĺ˶Խ��*/
              /*�˶Խ��
                1-�ҷ�����,�ҷ���,�貹��
                2-TIPS����,TIPS��,�������ط�
                3-�ҷ�����,TIPS��,�쳣
                4-TIPS����,�ҷ���,�쳣
                5-ƽ,����,��һ��,�쳣
                6-ƽ,״̬��һ��(�ҷ�δ����),��Ϊ����
                7-ƽ,��һ��+δ����,�쳣*/
  char   bfrq[8+1];              /*��������*/
              /**/
  int    clcs;              /*�������*/
              /**/
}SDB_TIPS_BWDJ;

#define SD_DATA SDB_TIPS_BWDJ
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,sendorgcode,0),\
	DEFSDMEMBER(T_STRING,entrustdate,0),\
	DEFSDMEMBER(T_STRING,packno,0),\
	DEFSDMEMBER(T_STRING,msgno,0),\
	DEFSDMEMBER(T_STRING,bwlx,0),\
	DEFSDMEMBER(T_STRING,paybkcode,0),\
	DEFSDMEMBER(T_STRING,bwwjm,0),\
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_STRING,clsj,0),\
	DEFSDMEMBER(T_STRING,zhqzlsh,0),\
	DEFSDMEMBER(T_STRING,dqzt,0),\
	DEFSDMEMBER(T_STRING,workdate,0),\
	DEFSDMEMBER(T_LONG,allnum,0),\
	DEFSDMEMBER(T_DOUBLE,allamt,2),\
	DEFSDMEMBER(T_LONG,succnum,0),\
	DEFSDMEMBER(T_DOUBLE,succamt,2),\
	DEFSDMEMBER(T_LONG,zfbs,0),\
	DEFSDMEMBER(T_DOUBLE,zfje,2),\
	DEFSDMEMBER(T_STRING,respmsginfo,0),\
	DEFSDMEMBER(T_STRING,bwhdrq,0),\
	DEFSDMEMBER(T_STRING,bwhdzt,0),\
	DEFSDMEMBER(T_STRING,bwhdjg,0),\
	DEFSDMEMBER(T_STRING,bfrq,0),\
	DEFSDMEMBER(T_LONG,clcs,0)
	
	DECLAREFIELDS(SD_TIPS_BWDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BWDJ_EH__*/
