/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_XLKZ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_XLKZ (���п��Ʊ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_XLKZ_H__
#define __APP_XLKZ_H__
typedef struct TDB_APP_XLKZ
{
  char   pkey[20+1];              /*KEYֵ*/
              /**/
  int    curr_value;              /*��ǰֵ*/
              /**/
  int    pinc;              /*����ֵ*/
              /**/
  int    min_value;              /*��Сֵ*/
              /**/
  int    max_value;              /*���ֵ*/
              /**/
  char   remark[40+1];              /*˵��*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}APP_XLKZ;

#define SD_DATA  APP_XLKZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_LONG,  curr_value, 0),\
	DEFSDMEMBER(T_LONG,  pinc, 0),\
	DEFSDMEMBER(T_LONG,  min_value, 0),\
	DEFSDMEMBER(T_LONG,  max_value, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_XLKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_XLKZ_H__*/
