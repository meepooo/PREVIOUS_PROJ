/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_ssplksfmx.eh
�ļ�����:tips_ssplksfmx;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_ssplksfmx (˰��������˰����ϸ��)
˵    ��:TIPS������˰����ϸ��
���ڵǼ������������ϸ��¼

************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_SSPLKSFMX_EH__
#define __TIPS_SSPLKSFMX_EH__

typedef struct TDB_TIPS_SSPLKSFMX
{
  char   zwrq[8+1];              /*��������*/
              /*��������*/
  char   pljydm[5+1];              /*�������״���*/
              /**/
  char   pljylsh[8+1];              /*����������ˮ��*/
              /**/
  char   plpch[10+1];              /*�������κ�*/
              /**/
  int    plmxxh;              /*������ϸ���*/
              /*�ۺ�ǰ����ˮ��*/
  int    clcs;              /*�������*/
              /*�������
                T+N����ʱ���Բ��ɹ��ļ�¼��ÿ������һ��*/
  char   workdate[8+1];              /*��������*/
              /*tips��������*/
  char   entrustdate[8+1];              /*ί������*/
              /*ί������
                ָTIPS��������*/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /**/
  char   packno[8+1];              /*����ˮ��*/
              /*����ˮ��
                ��ͬ��TIPS�����������κ�
                ���ڷ���Ψһ��ʶһ��������ˮ�ţ��ɷ����Զ���*/
  int   returnterm;              /*��ִ����*/
              /*Ҫ���ڻ�ִ���޹涨�������ڷ��ػ�ִ*/
  char   chkdate[8+1];              /*��������*/
              /**/
  char   chkacctord[4+1];              /*��������*/
              /**/
  char   trano[8+1];              /*������ˮ��*/
              /*������ˮ��*/
  char   protocolno[60+1];              /*Э�����*/
              /*ǩԼ��
                  ��ͻ���ί�й�ϵ��--����Э���*/
  char   dfzh[32+1];              /*�����ʺ�*/
              /*�����ʺ�*/
  char   paybkcode[12+1];              /*�������к�*/
              /*�������к�*/
  char   payopbkcode[12+1];              /*��������к�*/
              /*��������к�
                ָ��˰�˿������к�*/
  char   payacct[32+1];              /*�����ʺ�*/
              /*�����ʺ�
                ������ί�нɿ�Э���顱����˰�˵Ľɿ�˺�*/
  char   payeebankno[12+1];              /*�տ����к�*/
              /**/
  char   handorgname[200+1];              /*�ɿλ����*/
              /*�ɿλ����*/
  char   taxvouno[18+1];              /*˰Ʊ����*/
              /*˰Ʊ����*/
  double  jyje;              /*���׽��*/
              /*���׽�� TraAmt*/
  double  sxf;              /*������*/
              /**/
  double  zhye;              /*�˻����*/
              /**/
  double  je2;              /*���2*/
              /*���2
                ����*/
  char   zjrq[8+1];              /*��������*/
              /*��������
                �ۿ�ʱǰ�õ���Ȼ����*/
  char   zjsj[8+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   zjlsh[32+1];              /*������ˮ��*/
              /*������ˮ��
                �������ص���ˮ��,��Ա��ˮ��*/
  char   dqdh[10+1];              /*��������*/
              /*��������*/
  char   jgdh[10+1];              /*��������*/
              /*��������*/
  char   jygy[16+1];              /*���׹�Ա*/
              /*���׹�Ա*/
  char   zddh[16+1];              /*�ն˴���*/
              /*�ն˴���*/
  char   czbd[1+1];              /*��������*/
              /*�������㣺�ñʽ��׵�����״̬
                0-δ����
                1-��ֹ��
                2-������
                3-������
                4-��Ĩ��
                5-���������쳣
                6-�����������ȴ��������
                7-�ۿ�ɹ�
                8-�Ѵ���(������ϵ������,�ۿ�ʧ�ܵ�)
                */
  char   qsbz[1+1];              /*�����־*/
              /*�����ʶ
                0-δ����
                1-������ 
                 */
  char   xym[5+1];              /*��Ӧ��*/
              /*��Ӧ��*/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /*��Ӧ��Ϣ*/
  char   kzbz[8+1];              /*��չ��־*/
              /*��չ��־
                ��1λ�����������ʣ�0-δ����,1-ƽ,2-�ҷ���,3-������
                ��2λ����TIPS���ʣ�0-δ����,1-ƽ,2-�ҷ���,3-������
                ��3λ��������������ʣ�0-δ����,1-ƽ,2-�ҷ���,3-������
                ��4λ����ϸ�Ƿ��Ѿ�У�飺0-δУ��,1-��У��,2-�ѻ�ִ                
                */
  char   taxpaycode[20+1];              /*��˰�˱���*/
              /**/
  char   taxpayname[200+1];              /*��˰������*/
              /**/
  char   spxx[40+1];              /*˰Ʊ��Ϣ*/
              /*˰Ʊ��Ϣ�ļ���
                ����·��Ϊ$HOME/file/tips/spxx/
                */
  char   byzd[60+1];              /*�����ֶ�*/
              /*�����ֶ�
                ���ڴ洢������Ϣ*/

}SDB_TIPS_SSPLKSFMX;

#define SD_DATA SDB_TIPS_SSPLKSFMX
#define SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,pljydm,0),\
  DEFSDMEMBER(T_STRING,pljylsh,0),\
  DEFSDMEMBER(T_STRING,plpch,0),\
  DEFSDMEMBER(T_LONG,plmxxh,0),\
  DEFSDMEMBER(T_LONG,clcs,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,packno,0),\
  DEFSDMEMBER(T_LONG,returnterm,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,trano,0),\
  DEFSDMEMBER(T_STRING,protocolno,0),\
  DEFSDMEMBER(T_STRING,dfzh,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,handorgname,0),\
  DEFSDMEMBER(T_STRING,taxvouno,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_DOUBLE,sxf,2),\
  DEFSDMEMBER(T_DOUBLE,zhye,2),\
  DEFSDMEMBER(T_DOUBLE,je2,2),\
  DEFSDMEMBER(T_STRING,zjrq,0),\
  DEFSDMEMBER(T_STRING,zjsj,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,czbd,0),\
  DEFSDMEMBER(T_STRING,qsbz,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING,taxpaycode,0),\
  DEFSDMEMBER(T_STRING,taxpayname,0),\
  DEFSDMEMBER(T_STRING,spxx,0),\
  DEFSDMEMBER(T_STRING,byzd,0)

	DECLAREFIELDS(SD_TIPS_SSPLKSFMX)
#undef SD_DATA                                                                                                      
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSPLKSFMX_EH__*/
