/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_pljydj.eh
�ļ�����:tips_pljydj;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:21 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_pljydj (�������׵ǼǱ�)
˵    ��:�Ǽ�������˰(��)��֧���Ƚ�����Ϣ��¼��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_PLJYDJ_EH__
#define __TIPS_PLJYDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_PLJYDJ
{
  char   zwrq[8+1];              /*��������*/
              /**/
  char   pljydm[5+1];              /*�������״���*/
              /*�������״��룺
                GSPKS--��˰����˰
                DSPKS--��˰����˰
                SBPKF--�籣���۷�
                CZPZF--������֧��*/
  char   pljylsh[8+1];              /*����������ˮ��*/
              /*�ۺ�ǰ����ˮ��*/
  int    pczbs;              /*�����ܱ���*/
              /*һ���������ܶ�Ӧ������Σ��������涨����ֻ��300��,��һ��������1000��*/
  char   entrustdate[8+1];              /*ί������*/
              /**/
  char   orgcode[12+1];              /*������ش���*/
              /*���ջ��ش��롢�籣������Ż�������ش���*/
  char   packno[8+1];              /*����ˮ��*/
              /**/
  char   workdate[8+1];              /*��������*/
              /**/
  int    allnum;              /*�ܱ���*/
              /**/
  double  allamt;              /*�ܽ��*/
              /**/
  char    handletype[1+1];              /*�������*/
              /*�������,���ջ�����д*/
  char   payeebankno[12+1];              /*�տ����к�*/
              /**/
  char   payeeorgcode[12+1];              /*�տλ����*/
              /**/
  char    payeeacct[32+1];              /*�տ����˺�*/
              /**/
  char   payeename[60+1];              /*�տ�������*/
              /**/
  char   paybkcode[12+1];              /*�������к�*/
              /**/
  char   chkdate[8+1];              /*��������*/
              /**/
  char   chkacctord[4+1];              /*��������*/
              /**/
  int    rzzbs;              /*�����ܱ���*/
              /**/
  double  rzzje;              /*�����ܽ��*/
              /**/
  int    zfzbs;              /*ֹ���ܱ���*/
              /*��Ϊ����֧����ʱ�����˿��ܱ���*/
  double  zfzje;              /*ֹ���ܽ��*/
              /*��Ϊ����֧����ʱ�����˿��ܽ��*/
  char   xym[5+1];              /*��Ӧ��*/
              /**/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /**/
  char   czbd[1+1];              /*��������*/
              /*��������
                ���������״���ΪSWPKS��SBPKFʱ
                1-�������(3102TIPSת��������˰��������->TIPS9121ͨ��ȷ��Ӧ����)
                2-����׼��
                3-�����ύ
                4-�������
                5-�������
                6-�������(TIPS 2102������˰��ִ������ 9121ͨ��ȷ��Ӧ��)
                7-������֪ͨ(�յ�9122��ϸ����֪ͨ)*/
  char   wcbz[1+1];              /*��ɱ�־*/
              /*��ɱ�־
                0-δ����
                1-����ʧ��
                2-����ɹ�
                3-��ֹ��
                4-������
                5-�������˿�
                6-��ȫ���˿�
                9-������*/
  char   clqsrq[8+1];              /*������ʼ����*/
              /**/
  char   clqssj[8+1];              /*����ʼʱ��*/
              /**/
  char   cljsrq[8+1];              /*�����������*/
              /**/
  char   cljssj[8+1];              /*�������ʱ��*/
              /**/
  char   kzbz[8+1];              /*��չ��־*/
              /*��չ��־
                ���������״���ΪSWPKS��SBPKFʱ��
                ��1λ�����������ʣ�0-δ����,1-ƽ,2-�ҷ���,3-������
                ��2λ����TIPS���ʣ�0-δ����,1-ƽ,2-�ҷ���,3-������
                ��3λ��0-δ���㣬1-������
                */
  char   byzd[60+1];              /*�����ֶ�*/
              /**/
}SDB_TIPS_PLJYDJ;

#define SD_DATA SDB_TIPS_PLJYDJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,pljydm,0),\
  DEFSDMEMBER(T_STRING,pljylsh,0),\
  DEFSDMEMBER(T_LONG,pczbs,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,orgcode,0),\
  DEFSDMEMBER(T_STRING,packno,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_LONG,allnum,0),\
  DEFSDMEMBER(T_DOUBLE,allamt,2),\
  DEFSDMEMBER(T_STRING, handletype,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,payeeorgcode,0),\
  DEFSDMEMBER(T_STRING, payeeacct,0),\
  DEFSDMEMBER(T_STRING,payeename,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_LONG,rzzbs,0),\
  DEFSDMEMBER(T_DOUBLE,rzzje,2),\
  DEFSDMEMBER(T_LONG,zfzbs,0),\
  DEFSDMEMBER(T_DOUBLE,zfzje,2),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,czbd,0),\
  DEFSDMEMBER(T_STRING,wcbz,0),\
  DEFSDMEMBER(T_STRING,clqsrq,0),\
  DEFSDMEMBER(T_STRING,clqssj,0),\
  DEFSDMEMBER(T_STRING,cljsrq,0),\
  DEFSDMEMBER(T_STRING,cljssj,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_PLJYDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_PLJYDJ_EH__*/
