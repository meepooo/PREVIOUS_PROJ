/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_ssplzfksf.eh
�ļ�����:tips_ssplzfksf;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_ssplzfksf (˰������ֹ����˰��)
˵    ��:TIPS����ֹ����˰��
���ڵǼ�ֹ����������
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_SSPLZFKSF_EH__
#define __TIPS_SSPLZFKSF_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SSPLZFKSF
{
  char   zwrq[8+1];              /*��������*/
              /*��������*/
  char   plzflsh[8+1];              /*����ֹ����ˮ��*/
              /*��������
                ָϵͳ����*/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /*���ջ���*/
  char   entrustdate[8+1];              /*ί������*/
              /*ί������*/
  char   stopno[8+1];              /*ֹ���������*/
              /*ֹ���������*/
  char   workdate[10+1];              /*��������*/
              /*��������
                TIPS����->Ӧ����*/
  char   yzwrq[8+1];              /*ԭ��������*/
              /**/
  char   ypljylsh[8+1];              /*ԭ����������ˮ��*/
              /**/
  int    yplmxxh;              /*ԭ������ϸ���*/
              /**/
  char   orientrustdate[8+1];              /*ԭί������*/
              /*ԭί������*/
  char   oripackno[8+1];              /*ԭ����ˮ��*/
              /*ԭ����ˮ��
                */
  char   oritrano[8+1];              /*ԭ������ˮ��*/
              /*ԭ�Է���ˮ*/
  char   stoptype[1+1];              /*ֹ������*/
              /*ֹ������
                0-����
                1-����*/
  int    allnum;              /*�ܱ���*/
              /*�ܱ���*/
  double  allamt;              /*�ܽ��*/
              /*�ܽ��*/
  int    num_succ;              /*�ɹ�����*/
              /*�ɹ�����*/
  double  amt_succ;              /*�ɹ����*/
              /*�ɹ����*/
  char   clrq[8+1];              /*��������*/
              /*��������
                ֹ���ɹ�Ϊֹ����������*/
  char   clsj[8+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   dqzt[1+1];              /*��ǰ״̬*/
              /*��ǰ״̬
                0-δ����
                1-����ɹ�
                2-����ʧ��

                */
  char   xym[6+1];              /*��Ӧ��*/
              /*��Ӧ��*/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /*��Ӧ��Ϣ*/
  char   kzbz[8+1];              /*��չ��־*/
              /*��չ��־
                ��1λ�����������ʣ�0-δ����,1-ƽ,2-�ҷ���,3-������
                ��2λ����TIPS���ʣ�0-δ����,1-ƽ,2-�ҷ���,3-������
                ��3λ��

                */
  char    stopreason[60+1];              /*ֹ��ԭ��*/
              /*ֹ��ԭ��*/
  char    byzd[60+1];              /*�����ֶ�*/
              /*�����ֶ�
                ���ڴ洢������Ϣ*/
}SDB_TIPS_SSPLZFKSF;

#define SD_DATA SDB_TIPS_SSPLZFKSF
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,plzflsh,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,stopno,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,yzwrq,0),\
  DEFSDMEMBER(T_STRING,ypljylsh,0),\
  DEFSDMEMBER(T_LONG,yplmxxh,0),\
  DEFSDMEMBER(T_STRING,orientrustdate,0),\
  DEFSDMEMBER(T_STRING,oripackno,0),\
  DEFSDMEMBER(T_STRING,oritrano,0),\
  DEFSDMEMBER(T_STRING,stoptype,0),\
  DEFSDMEMBER(T_LONG,allnum,0),\
  DEFSDMEMBER(T_DOUBLE,allamt,2),\
  DEFSDMEMBER(T_LONG,num_succ,0),\
  DEFSDMEMBER(T_DOUBLE,amt_succ,2),\
  DEFSDMEMBER(T_STRING,clrq,0),\
  DEFSDMEMBER(T_STRING,clsj,0),\
  DEFSDMEMBER(T_STRING,dqzt,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING, stopreason,0),\
  DEFSDMEMBER(T_STRING, byzd,0)
	DECLAREFIELDS(SD_TIPS_SSPLZFKSF)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSPLZFKSF_EH__*/
