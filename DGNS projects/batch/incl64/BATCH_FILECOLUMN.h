/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_FILECOLUMN.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_FILECOLUMN (�����ļ�����Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_FILECOLUMN_H__
#define __BATCH_FILECOLUMN_H__
typedef struct TDB_BATCH_FILECOLUMN
{
  char   fileid[32+1];              /*�ļ���ʶ*/
              /**/
  long    fileclasssn;              /*�ļ��������*/
              /**/
  long    columnsn;              /*�����*/
              /**/
  char   columnid[16+1];              /*�б�ʶ*/
              /**/
  char   isid[1+1];              /*�Ƿ�ɿ�*/
              /*0��1��*/
  char   columnname[40+1];              /*������*/
              /**/
  char   lsx[1+1];              /*������*/
              /*��ʶ�ض������ԣ����A+��A-��*/
  long    offset;              /*��ʼλ��*/
              /**/
  long    columnlen;              /*���ݳ���*/
              /**/
  long    iprecision;              /*С������*/
              /**/
  long    izoom;              /*С��ƫ��*/
              /**/
  char   regular[1+1];              /*���뷽ʽ*/
              /*���뷽ʽ����l �����,R �Ҷ��룩ȱʡΪL*/
  long    ifiller;              /*����ַ�*/
              /*������ASCII����*/
  char   fldref[32+1];              /*����·��*/
              /**/
  char   snote[32+1];              /*˵��*/
              /**/
  char   extfld1[60+1];              /*��չ�ֶ�һ*/
              /**/
}BATCH_FILECOLUMN;

#define SD_DATA  BATCH_FILECOLUMN
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  fileid, 0),\
	DEFSDMEMBER(T_LONG,  fileclasssn, 0),\
	DEFSDMEMBER(T_LONG,  columnsn, 0),\
	DEFSDMEMBER(T_STRING,  columnid, 0),\
	DEFSDMEMBER(T_STRING,  isid, 0),\
	DEFSDMEMBER(T_STRING,  columnname, 0),\
	DEFSDMEMBER(T_STRING,  lsx, 0),\
	DEFSDMEMBER(T_LONG,  offset, 0),\
	DEFSDMEMBER(T_LONG,  columnlen, 0),\
	DEFSDMEMBER(T_LONG,  iprecision, 0),\
	DEFSDMEMBER(T_LONG,  izoom, 0),\
	DEFSDMEMBER(T_STRING,  regular, 0),\
	DEFSDMEMBER(T_LONG,  ifiller, 0),\
	DEFSDMEMBER(T_STRING,  fldref, 0),\
	DEFSDMEMBER(T_STRING,  snote, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0)


	DECLAREFIELDS(SD_BATCH_FILECOLUMN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILECOLUMN_H__*/
