/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_TABLEREG.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_TABLEREG (����ҵ���ṹע����Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_TABLEREG_H__
#define __BATCH_TABLEREG_H__
typedef struct TDB_BATCH_TABLEREG
{
  char   tablename[32+1];              /*����*/
              /**/
  int    fldsn;              /*�ֶ����*/
              /**/
  char   fldid[16+1];              /*�ֶα�ʶ*/
              /**/
  char   fldname[40+1];              /*�ֶ�����*/
              /**/
  char   fldtype[1+1];              /*�ֶ�����*/
              /*I����D����C�ַ���*/
  char   fldlen[10+1];              /*�ֶγ���*/
              /**/
  char   decimaldigits[10+1];              /*С��λ��*/
              /**/
  char   iskey[1+1];              /*�Ƿ�Ϊ����*/
              /*0��1���ǣ�Ĭ��1)*/
  char   isnull[1+1];              /*�Ƿ�����Ϊ��*/
              /*0����1������ ��Ĭ��0)*/
  char   fldshd[1+1];              /*���α�־*/
              /*0������ 1-�������� 2-ȫ����*/
}BATCH_TABLEREG;

#define SD_DATA  BATCH_TABLEREG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  tablename, 0),\
	DEFSDMEMBER(T_LONG,  fldsn, 0),\
	DEFSDMEMBER(T_STRING,  fldid, 0),\
	DEFSDMEMBER(T_STRING,  fldname, 0),\
	DEFSDMEMBER(T_STRING,  fldtype, 0),\
	DEFSDMEMBER(T_STRING,  fldlen, 0),\
	DEFSDMEMBER(T_STRING,  decimaldigits, 0),\
	DEFSDMEMBER(T_STRING,  iskey, 0),\
	DEFSDMEMBER(T_STRING,  isnull, 0),\
    DEFSDMEMBER(T_STRING,  fldshd, 0)

	DECLAREFIELDS(SD_BATCH_TABLEREG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_TABLEREG_H__*/
