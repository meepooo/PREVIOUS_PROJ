/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_ZJXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_ZJXX (�����ļ����ͱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_ZJXX_H__
#define __BATCH_ZJXX_H__
typedef struct TDB_BATCH_ZJXX
{
  char   hostid[30+1];      
  long   flag;              
  char   status[1+1];     
  char   bak1[40+1];    
  char   bak2[40+1];   
}BATCH_ZJXX;

#define SD_DATA  BATCH_ZJXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  hostid, 0),\
	DEFSDMEMBER(T_LONG,  flag, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_STRING,  bak1, 0),\
	DEFSDMEMBER(T_STRING,  bak2, 0)

	DECLAREFIELDS(SD_BATCH_ZJXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_ZJXX_H__*/
