/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_PLRW.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_PLRW (����ҵ�������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_PLRW_H__
#define __BATCH_PLRW_H__
typedef struct TDB_BATCH_PLRW
{
  char   pkrq[8+1];              /*��������*/
              /*��������(ƽ̨����)*/
  char   ptpch[8+1];              /*ƽ̨���κ�*/
              /*ƽ̨���κ�*/
  char   taskpri[3+1];              /*�������ȼ�*/
              /*�������ȼ�*/
  char   shpch[32+1];              /*�̻����κ�*/
              /*�̻����κ�*/
  char   zjpch[32+1];              /*�������κ�*/
              /*�������κ�*/
  char   ywbh[16+1];              /*ҵ����*/
              /*ҵ����*/
  char   dwbh[16+1];              /*��λ���*/
              /*��λ���*/
  char   tjrq[8+1];              /*�ύ����*/
              /*��Χ�ύ���������*/
  char   tjsj[6+1];              /*�ύʱ��*/
              /*�ύʱ��*/
  char   clrq[8+1];              /*��������*/
              /*�����������*/
  char   clsj[6+1];              /*����ʱ��*/
              /*����ʱ��*/
  double  zje;              /*�ܽ��*/
              /*�����ܽ�����*/
  int    zbs;              /*�ܱ���*/
              /*�����ܱ���������*/
  double  sjzje;              /*ʵ���ܽ��*/
              /*ʵ���ܽ��ļ��ڣ�*/
  int    sjzbs;              /*ʵ���ܱ���*/
              /*ʵ���ܱ������ļ��ڣ�*/
  double  cgzje;              /*�ɹ��ܽ��*/
              /*�ɹ��ܽ��*/
  int    cgzbs;              /*�ɹ��ܱ���*/
              /*�ɹ��ܱ���*/
  double  sbzje;              /*ʧ���ܽ��*/
              /*ʧ���ܽ��*/
  int    sbzbs;              /*ʧ���ܱ���*/
              /*ʧ���ܱ���*/
  double  sxfje;              /*�����ѽ��*/
              /*�����ѽ��*/
  int    xkhbs;              /*�¿�������*/
              /*�¿�������*/
  double  xkhje;              /*�¿������*/
              /*�¿������*/
  char   lpwjm[60+1];              /*�̻������ļ���*/
              /*�̻������ļ���*/
  char   sczjwjm[60+1];              /*�ϴ������ļ���*/
              /*�ϴ������ļ���*/
  char   zjhfwjm[60+1];              /*�����ظ��ļ���*/
              /*�����ظ��ļ���*/
  char   shcgwjm[60+1];              /*�ظ��̻��ɹ��ļ���*/
              /*�ظ��̻��ɹ��ļ����������ļ�����*/
  char   shsbwjm[60+1];              /*�ظ��̻�ʧ���ļ���*/
              /*�ظ��̻�ʧ���ļ���*/
  char   dqbd[2+1];              /*��ǰ����*/
              /*�������� 0 ��ȡ���� 1 ������� 2 ����У�� 3 �ύ���� 4�������  5����*/
  char   fzbd[2+1];              /*��������*/
              /*��������
����������Ϊ7������Ƕ��ʱ����Ч����������ʹ��00
00-������  09-������ 10-������  19-������ 11-�ѷ���*/
  char   bdzt[1+1];              /*����״̬*/
              /* 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C����*/
  char   rwzt[1+1];              /*����״̬*/
              /* 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ�����  X ���� C����*/
  char   xydm[8+1];              /*��Ӧ����*/
              /*��Ӧ����*/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /*��Ӧ��Ϣ*/
  char   bqtpkrq[8+1];              /*��Ƕ����������*/
              /*��Ƕ����������*/
  char   bqtptpch[8+1];              /*��Ƕ��ƽ̨���κ�*/
              /*��Ƕ��ƽ̨���κ�*/
  char   qtbz[1+1];              /*Ƕ�ױ�־*/
              /*Ƕ�ױ�־*/
  char   qtpkrq[8+1];              /*Ƕ����������*/
              /*Ƕ����������*/
  char   qtptpch[8+1];              /*Ƕ��ƽ̨���κ�*/
              /*Ƕ��ƽ̨���κ�*/
}BATCH_PLRW;

#define SD_DATA  BATCH_PLRW
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkrq, 0),\
	DEFSDMEMBER(T_STRING,  ptpch, 0),\
	DEFSDMEMBER(T_STRING,  taskpri, 0),\
	DEFSDMEMBER(T_STRING,  shpch, 0),\
	DEFSDMEMBER(T_STRING,  zjpch, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  tjrq, 0),\
	DEFSDMEMBER(T_STRING,  tjsj, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_DOUBLE,  zje, 2),\
	DEFSDMEMBER(T_LONG,  zbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sjzje, 2),\
	DEFSDMEMBER(T_LONG,  sjzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  cgzje, 2),\
	DEFSDMEMBER(T_LONG,  cgzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sbzje, 2),\
	DEFSDMEMBER(T_LONG,  sbzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxfje, 2),\
	DEFSDMEMBER(T_LONG,  xkhbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  xkhje, 2),\
	DEFSDMEMBER(T_STRING,  lpwjm, 0),\
	DEFSDMEMBER(T_STRING,  sczjwjm, 0),\
	DEFSDMEMBER(T_STRING,  zjhfwjm, 0),\
	DEFSDMEMBER(T_STRING,  shcgwjm, 0),\
	DEFSDMEMBER(T_STRING,  shsbwjm, 0),\
	DEFSDMEMBER(T_STRING,  dqbd, 0),\
	DEFSDMEMBER(T_STRING,  fzbd, 0),\
	DEFSDMEMBER(T_STRING,  bdzt, 0),\
	DEFSDMEMBER(T_STRING,  rwzt, 0),\
	DEFSDMEMBER(T_STRING,  xydm, 0),\
	DEFSDMEMBER(T_STRING,  xyxx, 0),\
	DEFSDMEMBER(T_STRING,  bqtpkrq, 0),\
	DEFSDMEMBER(T_STRING,  bqtptpch, 0),\
	DEFSDMEMBER(T_STRING,  qtbz, 0),\
	DEFSDMEMBER(T_STRING,  qtpkrq, 0),\
	DEFSDMEMBER(T_STRING,  qtptpch, 0)
		
	DECLAREFIELDS(SD_BATCH_PLRW)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_PLRW_H__*/
