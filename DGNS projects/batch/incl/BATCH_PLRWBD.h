/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_PLRWBD.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_PLRWBD (����ҵ�����񲽵���ϸ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_PLRWBD_H__
#define __BATCH_PLRWBD_H__
typedef struct TDB_BATCH_PLRWBD
{
  char   pkrq[8+1];              /*��������*/
              /*��������(ƽ̨����)*/
  char   ptpch[8+1];              /*ƽ̨���κ�*/
              /*ƽ̨���κ�*/
  int    flowsn;              /*����ִ�����*/
              /*����ִ�����*/
  char   czbd[2+1];              /*��������*/
              /*�������� 0 ��ȡ���� 1 ������� 2 ������� 3 �����ύ 4�������  5��ҵ����  */
  char   fzbd[2+1];              /*��������*/
              /*��������
����������Ϊ7������Ƕ��ʱ����Ч����������ʹ��00
00-������  09-������ 10-������  19-������ 11-�ѷ���*/
  char   bdzt[1+1];              /*����״̬*/
              /* 0��ֹ 1���� 2�ϵ� 3���� 4�ȴ� 9�ڴ����� */
  char   cljg[16+1];              /*�������*/
              /*�������*/
  char   clgy[16+1];              /*�����Ա*/
              /*�����Ա*/
  char   clksrq[8+1];              /*����ʼ����*/
              /**/
  char   clkssj[6+1];              /*����ʼʱ��*/
              /**/
  char   cljsrq[8+1];              /*�����������*/
              /**/
  char   cljssj[6+1];              /*�������ʱ��*/
              /**/
  int    clcs;              /*�������*/
              /**/
  char   xydm[8+1];              /*��Ӧ����*/
              /*��Ӧ����*/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /*��Ӧ��Ϣ*/
}BATCH_PLRWBD;

#define SD_DATA  BATCH_PLRWBD
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkrq, 0),\
	DEFSDMEMBER(T_STRING,  ptpch, 0),\
	DEFSDMEMBER(T_LONG,  flowsn, 0),\
	DEFSDMEMBER(T_STRING,  czbd, 0),\
	DEFSDMEMBER(T_STRING,  fzbd, 0),\
	DEFSDMEMBER(T_STRING,  bdzt, 0),\
	DEFSDMEMBER(T_STRING,  cljg, 0),\
	DEFSDMEMBER(T_STRING,  clgy, 0),\
	DEFSDMEMBER(T_STRING,  clksrq, 0),\
	DEFSDMEMBER(T_STRING,  clkssj, 0),\
	DEFSDMEMBER(T_STRING,  cljsrq, 0),\
	DEFSDMEMBER(T_STRING,  cljssj, 0),\
	DEFSDMEMBER(T_LONG,  clcs, 0),\
	DEFSDMEMBER(T_STRING,  xydm, 0),\
	DEFSDMEMBER(T_STRING,  xyxx, 0)


	DECLAREFIELDS(SD_BATCH_PLRWBD)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_PLRWBD_H__*/
