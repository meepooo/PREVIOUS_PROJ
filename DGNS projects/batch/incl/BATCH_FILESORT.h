/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_FILESORT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_FILESORT (�����ļ�������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_FILESORT_H__
#define __BATCH_FILESORT_H__
typedef struct TDB_BATCH_FILESORT
{
  char   fileid[32+1];              /*�ļ���ʶ*/
              /**/
  int    fileclasssn;              /*�ļ��������*/
              /**/
  char   classname[40+1];              /*��������*/
              /**/
  char   classtype[1+1];              /*��������*/
              /*1�����ܣ�2����ϸ*/
  int    higherupsn;              /*�ϼ��������*/
              /**/
  char   positionflag[1+1];              /*λ�ñ�־*/
              /*����*/
  char   classposition[32+1];              /*λ��*/
              /*����*/
  int    columnno;              /*����*/
              /**/
  char   rowsprtr[32+1];              /*�зָ���*/
              /*����*/
  char   sprtrattrib[1+1];              /*�зָ�������*/
              /*����*/
  char   columnflag[1+1];              /*�зָ���־*/
              /*1����2�ָ�*/
  char   columnsprtr[32+1];              /*�зָ���*/
              /**/
  char   extfld1[60+1];              /*��չ�ֶ�һ*/
              /**/

}BATCH_FILESORT;

#define SD_DATA  BATCH_FILESORT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  fileid, 0),\
	DEFSDMEMBER(T_LONG,  fileclasssn, 0),\
	DEFSDMEMBER(T_STRING,  classname, 0),\
	DEFSDMEMBER(T_STRING,  classtype, 0),\
	DEFSDMEMBER(T_LONG,  higherupsn, 0),\
	DEFSDMEMBER(T_STRING,  positionflag, 0),\
	DEFSDMEMBER(T_STRING,  classposition, 0),\
	DEFSDMEMBER(T_LONG,  columnno, 0),\
	DEFSDMEMBER(T_STRING,  rowsprtr, 0),\
	DEFSDMEMBER(T_STRING,  sprtrattrib, 0),\
	DEFSDMEMBER(T_STRING,  columnflag, 0),\
	DEFSDMEMBER(T_STRING,  columnsprtr, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0)


	DECLAREFIELDS(SD_BATCH_FILESORT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILESORT_H__*/
