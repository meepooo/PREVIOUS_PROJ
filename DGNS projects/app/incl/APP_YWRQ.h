/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_YWRQ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_YWRQ (ҵ�����ڱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_YWRQ_H__
#define __APP_YWRQ_H__
typedef struct TDB_APP_YWRQ
{
  char   pkey[20+1];              /*��ֵ*/
              /*��ֵ  ��Ʒ����*/
  char   syywrq[8+1];              /*��һҵ������*/
              /*��һҵ������*/
  char   ywrq[8+1];              /*ҵ������*/
              /*��Ʒҵ������*/
  char   xyywrq[8+1];              /*��һҵ������*/
              /*��һҵ������*/
  char   cch[2+1];              /*���κ�*/
              /*���κ�*/
  int    lsh;              /*��ˮ��*/
              /*��ˮ��*/
  char   extfld[40+1];              /*��չ����*/
              /*��չ����*/
  char   sm[40+1];              /*˵��*/
              /*˵��*/
}APP_YWRQ;

#define SD_DATA  APP_YWRQ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_STRING,  syywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  xyywrq, 0),\
	DEFSDMEMBER(T_STRING,  cch, 0),\
	DEFSDMEMBER(T_LONG,  lsh, 0),\
	DEFSDMEMBER(T_STRING,  extfld, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0)


	DECLAREFIELDS(SD_APP_YWRQ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_YWRQ_H__*/
