/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_STEPATTRIB.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_STEPATTRIB (�����������Ա�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_STEPATTRIB_H__
#define __BATCH_STEPATTRIB_H__
typedef struct TDB_BATCH_STEPATTRIB
{

}BATCH_STEPATTRIB;

#define SD_DATA  BATCH_STEPATTRIB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  stepid, 0),\
	DEFSDMEMBER(T_STRING,  stepname, 0),\
	DEFSDMEMBER(T_STRING,  attribid, 0),\
	DEFSDMEMBER(T_STRING,  attribnote, 0),\
	DEFSDMEMBER(T_STRING,  attribvalue, 0)


	DECLAREFIELDS(SD_BATCH_STEPATTRIB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_STEPATTRIB_H__*/
