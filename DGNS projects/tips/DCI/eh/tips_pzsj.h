/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_pzsj.eh
�ļ�����:tips_pzsj;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_pzsj (ƾ֤���ݱ�)
˵    ��:ƾ֤���ݱ����ر������ƾ֤��Ϣ������Ϣ����ӡ��Ϣ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_PZSJ_EH__
#define __TIPS_PZSJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_PZSJ
{
  char   zwrq[8+1];              /*��������*/
              /**/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /**/
  char   jyrq[8+1];              /*��������*/
              /**/
  char   dqdh[10+1];              /*��������*/
              /**/
  char   jgdh[10+1];              /*��������*/
              /**/
  char   jygy[16+1];              /*���׹�Ա*/
              /**/
  char   zddh[16+1];              /*�ն˴���*/
              /**/
  char   msgno[4+1];              /*���ı��*/
              /**/
  char   entrustdate[8+1];              /*ί������*/
              /**/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /**/
  char   packno[8+1];              /*����ˮ��*/
              /**/
  char   trano[8+1];              /*������ˮ��*/
              /**/
  char   payeebankno[12+1];              /*�տ��д���*/
              /**/
  char   payeename[60+1];              /*�տ�������*/
              /**/
  char   paybkcode[12+1];              /*�����д���*/
              /**/
  char   payopbkcode[12+1];              /*������д���*/
              /**/
  char   payacct[32+1];              /*�����˺�*/
              /**/
  char   handorgname[200+1];              /*�ɿλ����*/
              /**/
  double  jyje;              /*���׽��*/
              /**/
  char   corpcode[20+1];              /*��ҵ����*/
              /**/
  char   taxvouno[18+1];              /*˰Ʊ����*/
              /**/
  char   taxpaycode[20+1];              /*��˰�˱���*/
              /**/
  char   pzlx[1+1];              /*ƾ֤����*/
              /*ƾ֤���� 1-��˰ 2-��˰ 6-�籣*/
  int    dycs;              /*��ӡ����*/
              /**/
  char   dzbz[1+1];              /*���˱�־*/
              /*��TIPS���˱�־ 0-δ���� 1-��ƽ*/
  char   pzsjwjm[40+1];              /*ƾ֤�����ļ���*/
              /*����$HOME/file/tips/spxx/��
                */
  char   jyqd[10+1];
  char   zjrq[8+1];
  char   zjsj[8+1];
  char   zjlsh[32+1];
  char   jyzt[1+1];
  char   hxdzbz[1+1];
  char   qsbz[1+1];
  char   taxpayname[200+1];
  char   qspch[32+1];
  char   chkdate[8+1];
  char   chkacctord[4+1];
  char   opbankno[10+1];
  char   opbankname[60+1];
  char	 khh[12+1];
  char	 chjyje[100+1];
}SDB_TIPS_PZSJ;

#define SD_DATA SDB_TIPS_PZSJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,msgno,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,packno,0),\
  DEFSDMEMBER(T_STRING,trano,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,payeename,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,handorgname,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,corpcode,0),\
  DEFSDMEMBER(T_STRING,taxvouno,0),\
  DEFSDMEMBER(T_STRING,taxpaycode,0),\
  DEFSDMEMBER(T_STRING,pzlx,0),\
  DEFSDMEMBER(T_LONG,dycs,0),\
  DEFSDMEMBER(T_STRING,dzbz,0),\
  DEFSDMEMBER(T_STRING,pzsjwjm,0),\
  DEFSDMEMBER(T_STRING,jyqd,0),\
  DEFSDMEMBER(T_STRING,zjrq,0),\
  DEFSDMEMBER(T_STRING,zjsj,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,jyzt,0),\
  DEFSDMEMBER(T_STRING,hxdzbz,0),\
  DEFSDMEMBER(T_STRING,qsbz,0),\
  DEFSDMEMBER(T_STRING,taxpayname,0),\
  DEFSDMEMBER(T_STRING,qspch,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,opbankno,0),\
  DEFSDMEMBER(T_STRING,opbankname,0),\
  DEFSDMEMBER(T_STRING,khh,0),\
  DEFSDMEMBER(T_STRING,chjyje,0)
	DECLAREFIELDS(SD_TIPS_PZSJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_PZSJ_EH__*/
