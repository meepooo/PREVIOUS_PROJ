/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_TABLEINFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_TABLEINFO (����ҵ����ϸ����Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_TABLEINFO_H__
#define __BATCH_TABLEINFO_H__
typedef struct TDB_BATCH_TABLEINFO
{

}BATCH_TABLEINFO;

#define SD_DATA  BATCH_TABLEINFO
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  tablecode, 0),\
	DEFSDMEMBER(T_STRING,  tablename, 0),\
	DEFSDMEMBER(T_STRING,  tabletype, 0),\
	DEFSDMEMBER(T_STRING,  table_mb, 0),\
	DEFSDMEMBER(T_STRING,  tabletbspace, 0),\
	DEFSDMEMBER(T_STRING,  indextbspace, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_TABLEINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_TABLEINFO_H__*/
