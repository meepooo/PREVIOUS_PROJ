/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_AUDITINGFUNC.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_AUDITINGFUNC (����ҵ�������������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_AUDITINGFUNC_H__
#define __BATCH_AUDITINGFUNC_H__
typedef struct TDB_BATCH_AUDITINGFUNC
{
  char   auditingid[32+1];              /*��˱�ʶ*/
              /**/
  int    auditingsn;              /*���*/
              /**/
  char   funcid[32+1];              /*������ʶ*/
              /**/
  char   shsbbz[1+1];              /*���ʧ�ܱ�־*/
              /*���ʧ�ܱ�־0�������ʧ��1�������ʧ����ϸ*/

  char   snote[32+1];              /*˵��*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
             
}BATCH_AUDITINGFUNC;

#define SD_DATA  BATCH_AUDITINGFUNC
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  auditingid, 0),\
	DEFSDMEMBER(T_LONG,  auditingsn, 0),\
	DEFSDMEMBER(T_STRING,  funcid, 0),\
	DEFSDMEMBER(T_STRING,  shsbbz, 0),\
	DEFSDMEMBER(T_STRING,  snote, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_AUDITINGFUNC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_AUDITINGFUNC_H__*/
