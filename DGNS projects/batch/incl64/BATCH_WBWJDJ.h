/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_WBWJDJ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_WBWJDJ (����ҵ���ⲿ�ļ��ǼǱ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_WBWJDJ_H__
#define __BATCH_WBWJDJ_H__
typedef struct TDB_BATCH_WBWJDJ
{
  char   djrq[8+1];/*�Ǽ�����*/
  /**/
  long    djlsh;/*�Ǽ���ˮ��*/
  /**/
  char   djsj[6+1];/*�Ǽ�ʱ��*/
  /**/
  char   ywbh[16+1];/*ҵ����*/
              /**/
  char   djjg[16+1];              /*�Ǽǻ���*/
              /**/
  char   djgy[16+1];              /*�Ǽǹ�Ա*/
              /**/
  char   shjg[16+1];              /*��˻���*/
              /**/
  char   shgy[16+1];              /*��˹�Ա*/
              /**/
  char   shpch[32+1];              /*�̻����κ�*/
              /**/
  char   pkrq[8+1];              /*��������*/
              /**/
  char   ptpch[8+1];              /*ƽ̨���κ�*/
              /**/
  char   lpwjlj[254+1];              /*�����ļ�·��*/
              /**/
  char   lpwjm[60+1];              /*�����ļ���*/
              /**/
  char   zbs[8+1];              /*�ܱ���*/
              /**/
  double  zje;              /*�ܽ��*/
              /**/
  long    threadno;              /*�߳���*/
              /*���߼�ѡ��Ĭ��Ϊ1��*/
  char   taskmode[1+1];              /*����ʼ��ʽ*/
              /*1��������2���ֶ���Ĭ��Ϊ1��*/
  char   pczt[1+1];              /*����״̬*/
              /*1�������ϴ���2��������3�����ڴ���4���ѷ��أ�5������ʧ�ܣ�X������*/
  char   shzt[1+1];              /*���״̬*/
              /*0�����ͨ����1��δ��ˣ�2�����ʧ��*/
  char   note[128+1];              /*ע��*/
 
  long    breakdata;                  /* */

  char   extfld1[40+1];              /*��չ�ֶ�һ*/
              /**/
  char   extfld2[40+1];              /*��չ�ֶζ�*/
              /**/
  char   extfld3[40+1];              /*��չ�ֶ���*/
              /**/

}BATCH_WBWJDJ;

#define SD_DATA  BATCH_WBWJDJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  djrq, 0),\
	DEFSDMEMBER(T_LONG,  djlsh, 0),\
	DEFSDMEMBER(T_STRING,  djsj, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  djjg, 0),\
	DEFSDMEMBER(T_STRING,  djgy, 0),\
	DEFSDMEMBER(T_STRING,  shjg, 0),\
	DEFSDMEMBER(T_STRING,  shgy, 0),\
	DEFSDMEMBER(T_STRING,  shpch, 0),\
	DEFSDMEMBER(T_STRING,  pkrq, 0),\
	DEFSDMEMBER(T_STRING,  ptpch, 0),\
	DEFSDMEMBER(T_STRING,  lpwjlj, 0),\
	DEFSDMEMBER(T_STRING,  lpwjm, 0),\
	DEFSDMEMBER(T_STRING,  zbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  zje, 2),\
	DEFSDMEMBER(T_LONG,  threadno, 0),\
	DEFSDMEMBER(T_STRING,  taskmode, 0),\
	DEFSDMEMBER(T_STRING,  pczt, 0),\
	DEFSDMEMBER(T_STRING,  shzt, 0),\
	DEFSDMEMBER(T_STRING,  note, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0)


	DECLAREFIELDS(SD_BATCH_WBWJDJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_WBWJDJ_H__*/
