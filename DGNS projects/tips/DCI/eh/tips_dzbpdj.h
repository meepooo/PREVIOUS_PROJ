/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_dzbpdj.eh
�ļ�����:tips_dzbpdj;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_dzbpdj (���ʲ�ƽ�ǼǱ�)
˵    ��:���ʲ�ƽ�ǼǱ�
���ڵǼǶ��ʲ�ƽʱ����Ϣ����صĹ��ʴ�������Ϣ
����������
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_DZBPDJ_EH__
#define __TIPS_DZBPDJ_EH__

typedef struct TDB_TIPS_DZBPDJ
{
  char   zwrq[8+1];              /*��������*/
              /*��������,��Ӧ������������������*/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /*�ۺ�ǰ����ˮ��
                ԭ������ˮ��
                */
  char   workdate[8+1];              /*��������*/
              /*tips��������*/
  char   dqdh[10+1];              /*��������*/
              /**/
  char   jgdh[10+1];              /*��������*/
              /**/
  char   jygy[16+1];              /*���׹�Ա*/
              /**/
  char   zddh[16+1];              /*�ն˴���*/
              /**/
  char   dzlx[1+1];              /*��������*/
              /*��������
                1-����������
                2-��TIPS�ռ����
                3-��TIPS���ն���
                4-��TIPS�����ж˽ɿ� 
                6-���ʲ�ƽ���ʴ���*/
  char   zjlsh[32+1];              /*������ˮ��*/
              /*�������ص���ˮ��*/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /**/
  char   entrustdate[8+1];              /*ί������*/
              /*����������*/
  char   trano[8+1];              /*������ˮ��*/
              /*��������ˮ��*/
  char   chkdate[8+1];              /*��������*/
              /**/
  char   chkacctord[4+1];              /*��������*/
              /*�������κ�*/
  char   payeebankno[12+1];              /*�տ����к�*/
              /*�������,���׻���
                �Է���ʱΪ�Է��Ļ�����*/
  char   paybkcode[12+1];              /*�������к�*/
              /*�����������*/
  char   czyh[16+1];              /*����Ա��*/
              /*����Ա��*/
  char   jyqd[10+1];              /*��������*/
              /*��������,���׵ķ�����(��ϵͳ��)*/
  char   jyrq[8+1];              /*��������*/
              /*��������*/
  char   jysj[8+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   jymc[50+1];              /*��������*/
              /*��������*/
  char   khmc[200+1];              /*�ͻ�����*/
              /*�ͻ�����*/
  char   jyzh[32+1];              /*�����˺�*/
              /*�����ʺ�*/
  char   zhzl[2+1];              /*�ʻ�����*/
              /*�ʻ�����*/
  char   dfzh[32+1];              /*�����ʺ�*/
              /*�Է��ʺ�
                ָ�����ʺ�*/
  char   bzh[2+1];              /*���ֺ�*/
              /*���ֺ�*/
  double  jyje;              /*���׽��*/
              /*���׽��*/
  char   reason_info[80+1];              /*��ƽԭ��*/
              /*��ƽԭ��*/
  char   dzjg[2+1];              /*���ʽ��*/
              /*���ʽ��
                ��1λ��
                ���������ʽ��:1-ƽ,2-������,3-������
                ��2λ��
                ����������ʽ��:1-ƽ,2-������,3-������
                */
  char   clzt[1+1];              /*����״̬*/
              /*����״̬
                0-δ����
                1-�ѳɹ�����
                2-����ʧ��
                5-�ѵ���
                6-����ʧ��
                7-�Ѵ���(��԰��˶�)
                8-���봦��
                9-����,�ݲ�����*/
  char   jdbz[1+1];              /*�����־*/
              /*�����ʶ
                0-��
                1-��*/
  char   clrq[8+1];              /*��������*/
              /*��������*/
  char   clsj[8+1];              /*����ʱ��*/
              /*����ʱ��*/
  int    cllsh;              /*������ˮ��*/
              /*������ˮ��
                ���ʴ���ʱ���ۺ�ǰ����ˮ��*/
  char   clzjlsh[32+1];              /*����������ˮ��*/
              /*���ʴ����������ˮ*/
  char   clxx[50+1];              /*������Ϣ*/
              /*������Ϣ*/
  char   kzbz[8+1];              /*��չ��ʶ*/
              /*��չ��ʶ
                �����Զ�����չ*/
  char   byzd[60+1];              /*�����ֶ�*/
              /*�����ֶ�*/
}SDB_TIPS_DZBPDJ;

#define SD_DATA SDB_TIPS_DZBPDJ
#define SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
	DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,dzlx,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,trano,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,czyh,0),\
  DEFSDMEMBER(T_STRING,jyqd,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,jymc,0),\
  DEFSDMEMBER(T_STRING,khmc,0),\
  DEFSDMEMBER(T_STRING,jyzh,0),\
  DEFSDMEMBER(T_STRING,zhzl,0),\
  DEFSDMEMBER(T_STRING,dfzh,0),\
  DEFSDMEMBER(T_STRING,bzh,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,reason_info,0),\
  DEFSDMEMBER(T_STRING,dzjg,0),\
  DEFSDMEMBER(T_STRING,clzt,0),\
  DEFSDMEMBER(T_STRING,jdbz,0),\
  DEFSDMEMBER(T_STRING,clrq,0),\
  DEFSDMEMBER(T_STRING,clsj,0),\
  DEFSDMEMBER(T_LONG,cllsh,0),\
  DEFSDMEMBER(T_STRING,clzjlsh,0),\
  DEFSDMEMBER(T_STRING,clxx,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
	DEFSDMEMBER(T_STRING,byzd,0)

    DECLAREFIELDS(SD_TIPS_DZBPDJ)       
#undef SD_DATA                                                                                                      
#undef SD_MEMBERS

#endif  /*end of __TIPS_DZBPDJ_EH__*/
