/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_MAPINFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_MAPINFO (����ӳ����Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_MAPINFO_H__
#define __BATCH_MAPINFO_H__
typedef struct TDB_BATCH_MAPINFO
{
  char   mapid[32+1];              /*ӳ���ʶ*/
              /**/
  char   maptype[1+1];              /*ӳ������*/
              /*0 ��Χ�ļ�ӳ��
                1 �����ļ�ӳ��*/
  char   mapidnote[40+1];              /*ӳ���ʶ˵��*/
              /**/
  char   ywbm[32+1];              /*��������*/
              /**/
  char   lpwjbs[32+1];              /*�����ļ���ʶ*/
              /**/
  char   hpwjbs[32+1];              /*�����ļ���ʶ*/
              /**/
  char   tjwjbs[32+1];              /*�����ύ�ļ���ʶ*/
              /**/
  char   thwjbs[32+1];              /*��������ļ���ʶ*/
              /**/
  long    jlsxz;              /*������¼������*/
              /*���������ļ�����¼�� Ĭ�� 0  ������*/
  char   zhbz[1+1];              /*��Ӧ��ת����־*/
              /*0 ת�� 1 ��ת��*/
  char   zhbs[32+1];              /*��Ӧ��ת����ʶ*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}BATCH_MAPINFO;

#define SD_DATA  BATCH_MAPINFO
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mapid, 0),\
	DEFSDMEMBER(T_STRING,  maptype, 0),\
	DEFSDMEMBER(T_STRING,  mapidnote, 0),\
	DEFSDMEMBER(T_STRING,  ywbm, 0),\
	DEFSDMEMBER(T_STRING,  lpwjbs, 0),\
	DEFSDMEMBER(T_STRING,  hpwjbs, 0),\
	DEFSDMEMBER(T_STRING,  tjwjbs, 0),\
	DEFSDMEMBER(T_STRING,  thwjbs, 0),\
	DEFSDMEMBER(T_LONG,  jlsxz, 0),\
	DEFSDMEMBER(T_STRING,  zhbz, 0),\
	DEFSDMEMBER(T_STRING,  zhbs, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_MAPINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_MAPINFO_H__*/
