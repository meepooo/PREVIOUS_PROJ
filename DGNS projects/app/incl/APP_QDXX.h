/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_QDXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_QDXX (������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_QDXX_H__
#define __APP_QDXX_H__
typedef struct TDB_APP_QDXX
{
  char   qdbs[3+1];              /*������ʶ*/
              /*������ʶ �������ֵ� KEY=K_QDB */
  char   qdmc[40+1];              /*��������*/
              /*��������*/
  char   qdsm[80+1];              /*��������˵��*/
              /*��������˵��*/
  char   sjkzbz[1+1];              /*ʱ����Ʊ�־*/
              /*ʱ����Ʊ�־ 0 ��� 1������*/
  char   qssj[8+1];              /*��ʼʱ��*/
              /*��ʼʱ�� */
  char   jssj[8+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   czbz[1+1];              /*������־*/
              /*�Ƿ��������  0���� 1������*/
  char   zdczbz[1+1];              /*�Զ�������־*/
              /*ϵͳ�쳣�Ƿ��Զ�����  0�� 1��*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[40+1];              /*��չ�ֶ�1*/
              /*��չ�ֶ�1*/
  char   extfld2[40+1];              /*��չ�ֶ�2*/
              /*��չ�ֶ�2*/
  char   qdzt[1+1];              /*����״̬*/
              /*����״̬ 0���� 1�ر�*/
}APP_QDXX;

#define SD_DATA  APP_QDXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  qdmc, 0),\
	DEFSDMEMBER(T_STRING,  qdsm, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  czbz, 0),\
	DEFSDMEMBER(T_STRING,  zdczbz, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qdzt, 0)


	DECLAREFIELDS(SD_APP_QDXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_QDXX_H__*/
