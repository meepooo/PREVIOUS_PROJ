/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_FLOWCFG.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_FLOWCFG (�����������ñ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_FLOWCFG_H__
#define __BATCH_FLOWCFG_H__
typedef struct TDB_BATCH_FLOWCFG
{
 char   flowid[32+1];/*���̱�ʶ*/
 /**/
 char   flowname[40+1];/*������*/
 /**/
 long    flowsn;/*ִ�����*/
 /**/
  char   stepid[32+1];              /*�����ʶ*/
              /**/
 long    stepsn;/*�������*/
 /**/
  char   stepname[32+1];              /*��������*/
              /**/
  char   extfld1[40+1];              /*��չ�ֶ�1*/
              /**/
  char   extfld2[40+1];              /*��չ�ֶ�2*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}BATCH_FLOWCFG;

#define SD_DATA  BATCH_FLOWCFG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  flowid, 0),\
	DEFSDMEMBER(T_STRING,  flowname, 0),\
	DEFSDMEMBER(T_LONG,  flowsn, 0),\
	DEFSDMEMBER(T_STRING,  stepid, 0),\
	DEFSDMEMBER(T_LONG,  stepsn, 0),\
	DEFSDMEMBER(T_STRING,  stepname, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_FLOWCFG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FLOWCFG_H__*/
