/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_FILEMAP.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_FILEMAP (������ṹ���ļ�ӳ���ϵ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_FILEMAP_H__
#define __BATCH_FILEMAP_H__
typedef struct TDB_BATCH_FILEMAP
{
  char   mapid[32+1];              /*ӳ���ʶ*/
              /**/
  long    flxh;              /*�������*/
              /**/
  long    columnsn;              /*�����*/
              /**/
  char   columnid[16+1];              /*�б�ʶ*/
              /*��Ӧҵ���ṹע����Ϣ���������*/
  char   lylx[1+1];              /*��Դ����*/
              /*1�������ļ���ȡ��2��xml��ȡ��3�����̻�ȡ��4�����л�ȡ��5����ֵ��6������*/
  char   lywz[60+1];              /*��Դλ��*/
              /*������Դ������*/
  long    zjszwz;              /*��������λ��*/
              /*���������ļ������*/
  long    zjjgwz;              /*�������λ��*/
              /*��������ļ������*/
  char   thgxbz[1+1];              /*�����ļ���ظ��±�־*/
              /*0��1��*/
  long    hpwjwz;              /*�����ļ�λ��*/
              /*�����ļ������*/

}BATCH_FILEMAP;

#define SD_DATA  BATCH_FILEMAP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mapid, 0),\
	DEFSDMEMBER(T_LONG,  flxh, 0),\
	DEFSDMEMBER(T_LONG,  columnsn, 0),\
	DEFSDMEMBER(T_STRING,  columnid, 0),\
	DEFSDMEMBER(T_STRING,  lylx, 0),\
	DEFSDMEMBER(T_STRING,  lywz, 0),\
	DEFSDMEMBER(T_LONG,  zjszwz, 0),\
	DEFSDMEMBER(T_LONG,  zjjgwz, 0),\
	DEFSDMEMBER(T_STRING,  thgxbz, 0),\
	DEFSDMEMBER(T_LONG,  hpwjwz, 0)


	DECLAREFIELDS(SD_BATCH_FILEMAP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILEMAP_H__*/
