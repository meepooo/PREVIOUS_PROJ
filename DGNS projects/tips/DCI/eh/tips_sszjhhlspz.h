/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_sszjhhlspz.eh
�ļ�����:tips_sszjhhlspz;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2010-1-4 10:55:14 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_sszjhhlspz (˰���ʽ�㻮��ˮ��)
˵    ��:˰���ʽ�㻮��ˮ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_SSZJHHLSPZ_EH__
#define __TIPS_SSZJHHLSPZ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SSZJHHLSPZ
{
  char   zwrq[8+1];              /*��������*/
              /**/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /**/
  char   chkdate[8+1];              /*��������*/
              /**/
  char   chkacctord[4+1];              /*��������*/
              /**/
  char   paybkcode[12+1];              /*�������к�*/
              /*�������к�*/
  char   payeebankno[12+1];              /*�տ����к�*/
              /*�������*/
  char   payopbkcode[12+1];              /*��������к�*/
              /**/
  char   payacct[32+1];              /*�������˺�*/
              /*�����˺�(��Ӧtips_qshdj���е�dfzh)*/
  char   paybkname[60+1];              /*����������*/
              /**/
  char   payeeopbankno[12+1];              /*�տ�����к�*/
              /**/
  char   payeeacct[32+1];              /*�տ����˺�*/
              /**/
  char   payeebankname[60+1];              /*�տ�������*/
              /**/
  char   chkaccttype[1+1];              /*��������*/
              /*0-�ռ�
                1-����*/
  int   allnum;              /*���α���*/
              /**/
  double  allamt;              /*���ν��*/
              /**/
  int   jybs;              /*���ױ���*/
              /**/
  double  jyje;              /*���׽��*/
              /**/
  char   addword[60+1];              /*����*/
              /**/
  char   jyrq[8+1];              /*��������*/
              /**/
  char   jysj[8+1];              /*����ʱ��*/
              /**/
  char   qsrq[8+1];              /*��������*/
              /*ǰ����������*/
  int    qslsh;              /*������ˮ��*/
              /*ǰ��������ˮ��*/
  char   ywzl[5+1];              /*ҵ������*/
              /*����*/
  int    hhcs;              /*�㻮����*/
              /*��ʼΪ��1��*/
  char   zjrq[8+1];              /*��������*/
              /*����������֧��ϵͳ����*/
  char   zjsj[8+1];              /*����ʱ��*/
              /*����������֧��ϵͳʱ��*/
  char   zjlsh[32+1];              /*������ˮ��*/
              /*����������֧��ϵͳ��ˮ��*/
  char   jyzt[1+1];              /*����״̬*/
              /*0-��TIPS����ʧ��
                1-δ����
                2-�ѷ���
                3-����ʧ��
                4-���ͳ�ʱ
                5-����ɹ�
                6-����ʧ��
                9-���ڴ�����*/
  char   xym[8+1];              /*��Ӧ��*/
              /**/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /**/
  char   qsbz[1+1];              /*�����־*/
              /*0-δ����
                1-�ѷ���
                2-����ɹ�
                3-����ʧ��
                4-�ֹ�����*/
  char   dzbz[1+1];              /*���˱�־*/
              /*0-δ����
                1-��ƽ
                2-�ҷ���
                3-������*/
  char   sgxgxx[60+1];              /*�ֹ��޸���Ϣ*/
              /*����ֹ�����ʱ���޸�����8&�޸�ʱ��6&�޸ĵ�����&�޸Ļ�����&�޸Ĺ�Ա&*/
  char   byzd[40+1];              /*�����ֶ�*/
  char	 qspch[32+1];				/*�������κ�*/
  int	dycs;					/*��ӡ����*/
              /**/
  char   qjylx[1+1];
  char	 qslx[1+1];
}SDB_TIPS_SSZJHHLSPZ;

#define SD_DATA SDB_TIPS_SSZJHHLSPZ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,paybkname,0),\
  DEFSDMEMBER(T_STRING,payeeopbankno,0),\
  DEFSDMEMBER(T_STRING,payeeacct,0),\
  DEFSDMEMBER(T_STRING,payeebankname,0),\
  DEFSDMEMBER(T_STRING,chkaccttype,0),\
  DEFSDMEMBER(T_LONG,   allnum,0),\
  DEFSDMEMBER(T_DOUBLE,allamt,2),\
  DEFSDMEMBER(T_LONG,   jybs,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,addword,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,qsrq,0),\
  DEFSDMEMBER(T_LONG,qslsh,0),\
  DEFSDMEMBER(T_STRING,ywzl,0),\
  DEFSDMEMBER(T_LONG,hhcs,0),\
  DEFSDMEMBER(T_STRING,zjrq,0),\
  DEFSDMEMBER(T_STRING,zjsj,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,jyzt,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,qsbz,0),\
  DEFSDMEMBER(T_STRING,dzbz,0),\
  DEFSDMEMBER(T_STRING,sgxgxx,0),\
  DEFSDMEMBER(T_STRING,byzd,0),\
  DEFSDMEMBER(T_STRING,qspch,0),\
  DEFSDMEMBER(T_LONG,dycs,0),\
  DEFSDMEMBER(T_STRING,qjylx,0),\
  DEFSDMEMBER(T_STRING,qslx,0)
	DECLAREFIELDS(SD_TIPS_SSZJHHLSPZ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSZJHHLSPZ_EH__*/
