/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_sjgxhz.eh
�ļ�����:tips_sjgxhz;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_sjgxhz (���ݸ��»��ܱ�)
˵    ��:9100���ݸ��»��ܱ�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_SJGXHZ_EH__
#define __TIPS_SJGXHZ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SJGXHZ
{
  char   zwrq[8+1];              /*��������*/
              /*��������,��Ӧ������������������*/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /*�ۺ�ǰ����ˮ��
                ƽ̨�Զ����ɵ����*/
  char   workdate[8+1];              /*��������*/
              /*TIPS�Ĺ�������*/
  char   updatebatch[8+1];              /*��������*/
              /*TIPS���ƣ�ÿһ�ڸ��µ����й�������Ϊͬһ����������,�������Ϊ����ݣ���ţ���YYYYXXXX*/
  int    num_101;              /*���ջ��ش�����¼�¼��*/
              /*���ջ��ش�����¼�¼��*/
  int    num_101_succ;              /*���ջ��ش�����³ɹ���¼��*/
              /*���ջ��ش�����³ɹ���¼��*/
  int    num_102;              /*�������д�����¼�¼��*/
              /*�������д�����¼�¼��*/
  int    num_102_succ;              /*�������д�����³ɹ���¼��*/
              /*�������д�����³ɹ���¼��*/
  int    num_103;              /*�ڵ������¼�¼��*/
              /*�ڵ������¼�¼��*/
  int    num_103_succ;              /*�ڵ������³ɹ���¼��*/
              /*�ڵ������³ɹ���¼��*/
  int    num_104;              /*���������¼�¼��*/
              /*���������¼�¼��*/
  int    num_104_succ;              /*���������³ɹ���¼��*/
              /*���������³ɹ���¼��*/
  int    num_105;              /*Ԥ���Ŀ������¼�¼��*/
              /*Ԥ���Ŀ������¼�¼��*/
  int    num_105_succ;              /*Ԥ���Ŀ������³ɹ���¼��*/
              /*Ԥ���Ŀ������³ɹ���¼��*/
  int    num_106;              /*�˿�ԭ�������¼�¼��*/
              /*�˿�ԭ�������¼�¼��*/
  int    num_106_succ;              /*�˿�ԭ�������³ɹ���¼��*/
              /*�˿�ԭ�������³ɹ���¼��*/
  int    num_107;              /*����ԭ�������¼�¼��*/
              /*����ԭ�������¼�¼��*/
  int    num_107_succ;              /*����ԭ�������³ɹ���¼��*/
              /*����ԭ�������³ɹ���¼��*/
  int    num_108;              /*˰�ִ�����¼�¼��*/
              /*˰�ִ�����¼�¼��*/
  int    num_108_succ;              /*˰�ִ�����³ɹ���¼��*/
              /*˰�ִ�����³ɹ���¼��*/
  int    num_109;              /*˰Ŀ������¼�¼��*/
              /*˰Ŀ������¼�¼��*/
  int    num_109_succ;              /*˰Ŀ������³ɹ���¼��*/
              /*˰Ŀ������³ɹ���¼��*/
  int    num_110;              /*num110���¼�¼��*/
              /*num110���¼�¼��
                ����*/
  int    num_110_succ;              /*num110���³ɹ���¼��*/
              /*num110���³ɹ���¼��
                ����*/
  int    num_111;              /*num111���¼�¼��*/
              /*num111���¼�¼��
                ����*/
  int    num_111_succ;              /*num111���³ɹ���¼��*/
              /*num111���³ɹ���¼��
                ����*/
  int    num_112;              /*num112���¼�¼��*/
              /*num112���¼�¼��
                ����*/
  int    num_112_succ;              /*num112���³ɹ���¼��*/
              /*num112���³ɹ���¼��
                ����*/
  char   xym[8+1];              /*��Ӧ��*/
              /*��Ӧ��*/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /*��Ӧ��Ϣ*/
  int    tran_time;              /*���׺�ʱ*/
              /*���׺�ʱ
                ��λ��ms*/
  char   reserve1[50+1];              /*reserve1*/
              /*reserve1
                ��������ʱ��¼����ԭ��*/
  char   byzd[128+1];              /*�����ֶ�*/
              /*�����ֶ�*/
}SDB_TIPS_SJGXHZ;

#define SD_DATA SDB_TIPS_SJGXHZ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,updatebatch,0),\
  DEFSDMEMBER(T_LONG,num_101,0),\
  DEFSDMEMBER(T_LONG,num_101_succ,0),\
  DEFSDMEMBER(T_LONG,num_102,0),\
  DEFSDMEMBER(T_LONG,num_102_succ,0),\
  DEFSDMEMBER(T_LONG,num_103,0),\
  DEFSDMEMBER(T_LONG,num_103_succ,0),\
  DEFSDMEMBER(T_LONG,num_104,0),\
  DEFSDMEMBER(T_LONG,num_104_succ,0),\
  DEFSDMEMBER(T_LONG,num_105,0),\
  DEFSDMEMBER(T_LONG,num_105_succ,0),\
  DEFSDMEMBER(T_LONG,num_106,0),\
  DEFSDMEMBER(T_LONG,num_106_succ,0),\
  DEFSDMEMBER(T_LONG,num_107,0),\
  DEFSDMEMBER(T_LONG,num_107_succ,0),\
  DEFSDMEMBER(T_LONG,num_108,0),\
  DEFSDMEMBER(T_LONG,num_108_succ,0),\
  DEFSDMEMBER(T_LONG,num_109,0),\
  DEFSDMEMBER(T_LONG,num_109_succ,0),\
  DEFSDMEMBER(T_LONG,num_110,0),\
  DEFSDMEMBER(T_LONG,num_110_succ,0),\
  DEFSDMEMBER(T_LONG,num_111,0),\
  DEFSDMEMBER(T_LONG,num_111_succ,0),\
  DEFSDMEMBER(T_LONG,num_112,0),\
  DEFSDMEMBER(T_LONG,num_112_succ,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_LONG,tran_time,0),\
  DEFSDMEMBER(T_STRING,reserve1,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_SJGXHZ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SJGXHZ_EH__*/
