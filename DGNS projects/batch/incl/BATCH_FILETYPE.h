/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_FILETYPE.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_FILETYPE (�����ļ����ͱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_FILETYPE_H__
#define __BATCH_FILETYPE_H__
typedef struct TDB_BATCH_FILETYPE
{
  char   fileid[32+1];              /*�ļ���ʶ*/
              /**/
  char   fileidnote[40+1];              /*�ļ���ʶ˵��*/
              /**/
  char   filetype[1+1];              /*�ļ�����*/
              /*0- txt 1-DBF 2-xls 3-xlsx 4-dbf  Ĭ�� 0*/
  char   filefmt[2+1];              /*�ļ���ʽ*/
              /*01  ����ϸ
                02  ���ܣ�����ϸ
                03  ����ϸ������
                04  ���ܣ�����ϸ������
                */
  char   codefmt[1+1];              /*�����ʽ*/
              /*�����ʽ 0-ascii 1-utf-8 2-base64*/
  char   extfld1[32+1];              /*��չ�ֶ�һ*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}BATCH_FILETYPE;

#define SD_DATA  BATCH_FILETYPE
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  fileid, 0),\
	DEFSDMEMBER(T_STRING,  fileidnote, 0),\
	DEFSDMEMBER(T_STRING,  filetype, 0),\
	DEFSDMEMBER(T_STRING,  filefmt, 0),\
	DEFSDMEMBER(T_STRING,  codefmt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_FILETYPE)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILETYPE_H__*/
