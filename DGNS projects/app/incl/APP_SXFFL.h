/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_SXFFL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_SXFFL (�����ѷ��ʱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_SXFFL_H__
#define __APP_SXFFL_H__
typedef struct TDB_APP_SXFFL
{
  char   flbs[32+1];              /*���ʱ�ʶ*/
              /*�ֹ�����*/
  char   xh[2+1];              /*���*/
              /*��������ʱ������ʷֶε����*/
  char   fdbz[1+1];              /*������־*/
              /*0 ��������  ��� */
  char   nwkbz[1+1];              /*����۱�־*/
              /*0���  1 �ڿ  Ĭ� 0*/
  char   sxxkz[1+1];              /*�����޿���*/
              /*0 ����   ����� */
  double  sxje;              /*���޽��*/
              /**/
  double  xxje;              /*���޽��*/
              /**/
  char   jslx[1+1];              /*�����������*/
              /*����������� 1 ��  2�ٷֱ   ���Ϊ ����ʾ�����Ѽ�����Խ��ױ����ģ�����ǰٷֱȣ���ʾ�����Ѽ�����Խ��׽�*/
  double  jscs;              /*�������*/
              /*������� ��������Ϊ1 ����� ���� ��ʾ1Ԫ������Ϊ2������ٷֱ ������ ����ʾ1��*/
  char   kjbz[1+1];              /*�Żݱ�־*/
              /*0���Ż� 1 ���  ���ۼ Ĭ��0*/
  double  kjcs;              /*�ۼ�����*/
              /*�Ż� %��β��ʶ�ۿ��� ����Ϊ�ۼ����*/
  char   fdlx[1+1];              /*��������*/
              /*�������� 1 ���ױ������  ���׽���*/
  char   ljbz[1+1];              /*�۽ ��־*/
              /*0 ���۽�   �۽ Ĭ��0*/
  char   bhbz[1+1];              /*�������ޱ�־*/
              /*��������������ޱ�־  1 ������� 0��������*/
  char   qss[16+1];              /*��ʼ����*/
              /**/
  char   jss[16+1];              /*��������*/
              /**/
  char   sm[40+1];              /*˵��*/
              /*˵��*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}APP_SXFFL;

#define SD_DATA  APP_SXFFL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  flbs, 0),\
	DEFSDMEMBER(T_STRING,  xh, 0),\
	DEFSDMEMBER(T_STRING,  fdbz, 0),\
	DEFSDMEMBER(T_STRING,  nwkbz, 0),\
	DEFSDMEMBER(T_STRING,  sxxkz, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxje, 2),\
	DEFSDMEMBER(T_DOUBLE,  xxje, 2),\
	DEFSDMEMBER(T_STRING,  jslx, 0),\
	DEFSDMEMBER(T_DOUBLE,  jscs, 6),\
	DEFSDMEMBER(T_STRING,  kjbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  kjcs, 6),\
	DEFSDMEMBER(T_STRING,  fdlx, 0),\
	DEFSDMEMBER(T_STRING,  ljbz, 0),\
	DEFSDMEMBER(T_STRING,  bhbz, 0),\
	DEFSDMEMBER(T_STRING,  qss, 0),\
	DEFSDMEMBER(T_STRING,  jss, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)

	DECLAREFIELDS(SD_APP_SXFFL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_SXFFL_H__*/

