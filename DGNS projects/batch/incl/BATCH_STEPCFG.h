/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_STEPCFG.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_STEPCFG (ҵ�񲽵��������ñ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_STEPCFG_H__
#define __BATCH_STEPCFG_H__
typedef struct TDB_BATCH_STEPCFG
{
  char   flowid[32+1];              /*���̱�ʶ*/
              /**/
  int    flowsn;              /*����ִ�����*/
              /*����ִ�����*/
  char   stepid[32+1];              /*�����ʶ*/
              /**/
  char   attribnote[40+1];              /*��������*/
              /**/
  char   attribid[16+1];              /*���Ա�ʶ*/
              /**/
  char   attribtype[1+1];              /*��������*/
              /*0 �������� 1��������*/
  char   attribvalue[60+1];              /*����ֵ*/
              /**/
}BATCH_STEPCFG;

#define SD_DATA  BATCH_STEPCFG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  flowid, 0),\
	DEFSDMEMBER(T_LONG,    flowsn, 0),\
	DEFSDMEMBER(T_STRING,  stepid, 0),\
	DEFSDMEMBER(T_STRING,  attribnote, 0),\
	DEFSDMEMBER(T_STRING,  attribid, 0),\
	DEFSDMEMBER(T_STRING,  attribtype, 0),\
	DEFSDMEMBER(T_STRING,  attribvalue, 0)


	DECLAREFIELDS(SD_BATCH_STEPCFG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_STEPCFG_H__*/
