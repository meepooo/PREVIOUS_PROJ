/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_CPJGGX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_CPJGGX (��Ʒ������ϵ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_CPJGGX_H__
#define __APP_CPJGGX_H__
typedef struct TDB_APP_CPJGGX
{
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   jgbh[16+1];              /*�������*/
              /*�������*/
  char   sjkzbz[1+1];              /*ʱ����Ʊ�־*/
              /*ʱ����Ʊ�־  0���� 1������*/
  char   qssj[6+1];              /*��ʼʱ��*/
              /*��ʼʱ��*/
  char   jssj[6+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[40+1];              /*��չ����1*/
              /*��չ����1*/
  char   extfld2[40+1];              /*��չ����2*/
              /*��չ����1*/
  char   zt[1+1];              /*״̬*/
              /*״̬ 0���� 1������*/
}APP_CPJGGX;

#define SD_DATA  APP_CPJGGX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  jgbh, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_CPJGGX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPJGGX_H__*/
