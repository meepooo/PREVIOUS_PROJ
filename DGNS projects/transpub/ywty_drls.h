/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�� �� ��:INFORMIX
�� �� ��:ywty_drls.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:GAPS�з���
�� �� Ա:[Tianhc]
��������:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�����:
************************************************************************
��    ��:ywty_drls (YWTY_DRLS������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/

#ifndef __YWTY_DRLS_H__
#define __YWTY_DRLS_H__
typedef struct TDB_YWTY_DRLS
{
  char   zwrq[8+1];  /*��������*/
  /*��������,��Ӧ������������������*/
  int   zhqzlsh;  /*�ۺ�ǰ����ˮ��*/
  /*�ۺ�ǰ����ˮ�� ƽ̨�Զ����ɵ����*/
  char   zxlsh[16+1];  /*������ˮ��*/
  /*�������ص���ˮ��*/
  char   dsfzwrq[8+1];  /*��������������*/
  /*�������������� ���ڵ��������������ڵ�ҵ��,��Ǽ�*/
  char   dsflsh[18+1];  /*��������ˮ��*/
  /*��������ˮ��*/
  char   jygzh[12+1];  /*���׸��ٺ�*/
  /*���׸��ٺ� ����һ�������ж���ӽ��׹���,��������ۺ�ǰ����ˮ*/
  int   zhqzlsh2;  /*�ۺ�ǰ����ˮ��2*/
  /*�ۺ�ǰ����ˮ��2 һ�����ڳ�������������������¼���й�������ˮ��*/
  char   sqm[6+1];  /*��Ȩ��*/
  /*��Ȩ��*/
  char   sqczy[8+1];  /*��Ȩ����Ա*/
  /*��Ȩ����Ա,��������Ȩ�Ľ���*/
  char   sjjgbh[16+1];  /*�ϼ��������*/
  /*�ϼ��������,����ͳ��*/
  char   jgbh[16+1];  /*�������*/
  /*�������*/
  char   nbjgbs[24+1];  /*�ڲ�������ʶ*/
  /*�ڲ�������ʶ,ƽ̨�ڲ��������*/
  char   wtjgbh[16+1];  /*ί�л������*/
  /*ί�л������*/
  char   wtnbjgbs[24+1];  /*ί�л����ڲ���ʶ*/
  /*ί�л����ڲ���ʶ*/
  char   czyh[8+1];  /*����Ա��*/
  /*����Ա��*/
  char   jdbh[16+1];  /*�ڵ���*/
  /*�ڵ���,���ATM������*/
  char   jyqd[12+1];  /*��������*/
  /*��������,���׵ķ�����(��ϵͳ��)*/
  char   jyrq[8+1];  /*��������*/
  /*��������*/
  char   jysj[6+1];  /*����ʱ��*/
  /*����ʱ��*/
  char   jydm[50+1];  /*���״���*/
  /*���״���,�ⲿ���״���*/
  char   jymc[50+1];  /*��������*/
  /*��������*/
  char   ywdm[10+1];  /*ҵ�����*/
  /*ҵ�����*/
  char   xmdh[10+1];  /*��Ŀ����*/
  /*��Ŀ����*/
  char   khmc[80+1];  /*�ͻ�����*/
  /*�ͻ�����*/
  char   jyzh[32+1];  /*�����ʺ�*/
  /*�����ʺ�*/
  char   zhzl[2+1];  /*�ʻ�����*/
  /*�ʻ�����*/
  char   jyzh2[32+1];  /*�Է��ʺ�*/
  /*�Է��ʺ�:����ת���ཻ��*/
  char   zhzl2[2+1];  /*�Է��ʻ�����*/
  /*�Է��ʻ�����*/
  char   zhjg2[32+1];  /*�Է�������*/
  /*�Է�������*/
  char   khh[20+1];  /*�ͻ���*/
  /*�ͻ���:��������*/
  char   yhh[32+1];  /*�û���*/
  /*�û���:�������ı�ʶ��*/
  char   bzh[2+1];  /*���ֺ�*/
  /*���ֺ�*/
  double   jyje;  /*���׽��*/
  /*���׽��*/
  double   sxf;  /*������*/
  /*������*/
  double   gbf;  /*������*/
  /*������*/
  double   znj;  /*�ʹ���*/
  /*�ʹ���*/
  char   jyzt[1+1];  /*����״̬*/
  /*����״̬: 0-�ɹ� 1-ʧ�� 2-������ 3-ȡ�� 9-���ڴ�����*/
  char   xym[8+1];  /*��Ӧ��*/
  /*��Ӧ��*/
  char   xyxx[60+1];  /*��Ӧ��Ϣ*/
  /*��Ӧ��Ϣ*/
  char   jyfs[1+1];  /*���׷�ʽ*/
  /*���׷�ʽ �����ۡ��ֽ�֧Ʊ...*/
  char   jdbz[1+1];  /*�����ʶ*/
  /*�����ʶ 0-�� 1-��*/
  char   gdbz[1+1];  /*�鵵��־*/
  /*�鵵��־ 0-����鵵 1-�鵵(��ʷ��ˮ)*/
  char   jyzl[1+1];  /*��������*/
  /*�������� 1-������ 2-ί�й�ϵ�� 3-��ѯ�� 4-������ 5-������*/
  char   jzbz[1+1];  /*���ʱ�ʶ*/
  /*���ʱ�ʶ 0-������ 1-����(�����)*/
  char   qsbz[1+1];  /*�����ʶ*/
  /*�����ʶ 0-δ���� 1-������*/
  char   kzbz[8+1];  /*��չ��ʶ*/
  /*��չ��ʶ �����Զ�����չ*/
  char   wbzwbs[20+1];  /*�ⲿ�����ʶ*/
  /*�ⲿ�����ʶ ���ڼ�¼�������������Ϣ*/
  int   trans_time;  /*���׺�ʱ*/
  /*���׺�ʱ ��λ��ms*/
  char   byzd[128+1];  /*�����ֶ�*/
  /*�����ֶ�*/

}YWTY_DRLS;

#define SD_DATA  YWTY_DRLS
#define SD_MEMBERS  DEFSDMEMBER(T_STRING,  zwrq, 0),\
 DEFSDMEMBER(T_LONG,  zhqzlsh, 0),\
 DEFSDMEMBER(T_STRING,  zxlsh, 0),\
 DEFSDMEMBER(T_STRING,  dsfzwrq, 0),\
 DEFSDMEMBER(T_STRING,  dsflsh, 0),\
 DEFSDMEMBER(T_STRING,  jygzh, 0),\
 DEFSDMEMBER(T_LONG,  zhqzlsh2, 0),\
 DEFSDMEMBER(T_STRING,  sqm, 0),\
 DEFSDMEMBER(T_STRING,  sqczy, 0),\
 DEFSDMEMBER(T_STRING,  sjjgbh, 0),\
 DEFSDMEMBER(T_STRING,  jgbh, 0),\
 DEFSDMEMBER(T_STRING,  nbjgbs, 0),\
 DEFSDMEMBER(T_STRING,  wtjgbh, 0),\
 DEFSDMEMBER(T_STRING,  wtnbjgbs, 0),\
 DEFSDMEMBER(T_STRING,  czyh, 0),\
 DEFSDMEMBER(T_STRING,  jdbh, 0),\
 DEFSDMEMBER(T_STRING,  jyqd, 0),\
 DEFSDMEMBER(T_STRING,  jyrq, 0),\
 DEFSDMEMBER(T_STRING,  jysj, 0),\
 DEFSDMEMBER(T_STRING,  jydm, 0),\
 DEFSDMEMBER(T_STRING,  jymc, 0),\
 DEFSDMEMBER(T_STRING,  ywdm, 0),\
 DEFSDMEMBER(T_STRING,  xmdh, 0),\
 DEFSDMEMBER(T_STRING,  khmc, 0),\
 DEFSDMEMBER(T_STRING,  jyzh, 0),\
 DEFSDMEMBER(T_STRING,  zhzl, 0),\
 DEFSDMEMBER(T_STRING,  jyzh2, 0),\
 DEFSDMEMBER(T_STRING,  zhzl2, 0),\
 DEFSDMEMBER(T_STRING,  zhjg2, 0),\
 DEFSDMEMBER(T_STRING,  khh, 0),\
 DEFSDMEMBER(T_STRING,  yhh, 0),\
 DEFSDMEMBER(T_STRING,  bzh, 0),\
 DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
 DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
 DEFSDMEMBER(T_DOUBLE,  gbf, 2),\
 DEFSDMEMBER(T_DOUBLE,  znj, 2),\
 DEFSDMEMBER(T_STRING,  jyzt, 0),\
 DEFSDMEMBER(T_STRING,  xym, 0),\
 DEFSDMEMBER(T_STRING,  xyxx, 0),\
 DEFSDMEMBER(T_STRING,  jyfs, 0),\
 DEFSDMEMBER(T_STRING,  jdbz, 0),\
 DEFSDMEMBER(T_STRING,  gdbz, 0),\
 DEFSDMEMBER(T_STRING,  jyzl, 0),\
 DEFSDMEMBER(T_STRING,  jzbz, 0),\
 DEFSDMEMBER(T_STRING,  qsbz, 0),\
 DEFSDMEMBER(T_STRING,  kzbz, 0),\
 DEFSDMEMBER(T_STRING,  wbzwbs, 0),\
 DEFSDMEMBER(T_LONG,  trans_time, 0),\
 DEFSDMEMBER(T_STRING,  byzd, 0)


DECLAREFIELDS(SD_YWTY_DRLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YWTY_DRLS_H__*/
