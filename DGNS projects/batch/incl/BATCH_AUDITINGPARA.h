/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_AUDITINGPARA.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_AUDITINGPARA (����ҵ����˺���������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_AUDITINGPARA_H__
#define __BATCH_AUDITINGPARA_H__
typedef struct TDB_BATCH_AUDITINGPARA
{
}BATCH_AUDITINGPARA;

#define SD_DATA  BATCH_AUDITINGPARA
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  funcid, 0),\
	DEFSDMEMBER(T_LONG,  parasn, 0),\
	DEFSDMEMBER(T_STRING,  paravalue, 0),\
	DEFSDMEMBER(T_STRING,  snote, 0)


	DECLAREFIELDS(SD_BATCH_AUDITINGPARA)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_AUDITINGPARA_H__*/
