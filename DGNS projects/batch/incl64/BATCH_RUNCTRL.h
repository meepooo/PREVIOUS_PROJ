/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_RUNCTRL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_RUNCTRL (����ҵ�����п��Ʊ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_RUNCTRL_H__
#define __BATCH_RUNCTRL_H__
typedef struct TDB_BATCH_RUNCTRL
{
  char   cpdm[16+1];              /*ҵ����*/
              /**/
  char   flowid[32+1];              /*���̱�ʶ*/
              /**/
  char   maxtask[5+1];              /*���������*/
              /**/
  char   maxthread[5+1];              /*����߳���*/
              /**/
  char   zjysbs[32+1];              /*����ӳ���ʶ*/
              /**/
  char   wwysbs[32+1];              /*��Χӳ���ʶ*/
              /**/
  char   shbz[1+1];              /*��˱�־*/
              /*0����Ҫ����ⲿ�ļ���1������Ҫ����ⲿ�ļ�*/
  char   taskmode[1+1];              /*����ʼ��ʽ*/
              /*1��������2���ֶ���Ĭ��Ϊ1��*/
  char   taskpri[1+1];              /* �������ȼ�*/
              /*�������ȼ� 0-��ͨ 1-�Ӽ� 2-�ؼ�*/
  char   pzbd[2+1];              /* ���ò���*/
              /*���ò���*/
  char   extfld1[60+1];              /*��չ�ֶ�һ*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}BATCH_RUNCTRL;

#define SD_DATA  BATCH_RUNCTRL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  flowid, 0),\
	DEFSDMEMBER(T_STRING,  maxtask, 0),\
	DEFSDMEMBER(T_STRING,  maxthread, 0),\
	DEFSDMEMBER(T_STRING,  zjysbs, 0),\
	DEFSDMEMBER(T_STRING,  wwysbs, 0),\
	DEFSDMEMBER(T_STRING,  shbz, 0),\
	DEFSDMEMBER(T_STRING,  taskmode, 0),\
	DEFSDMEMBER(T_STRING,  taskpri, 0),\
	DEFSDMEMBER(T_STRING,  pzbd, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)

	DECLAREFIELDS(SD_BATCH_RUNCTRL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_RUNCTRL_H__*/
