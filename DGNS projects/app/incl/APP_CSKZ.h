/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_CSKZ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_CSKZ (�������Ʊ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_CSKZ_H__
#define __APP_CSKZ_H__
typedef struct TDB_APP_CSKZ
{
  char   csjz[20+1];              /*������ֵ*/
              /*������ֵ*/
  char   cslx[1+1];              /*��������*/
              /*�������� �������ֵ� KEY=K_CSLX*/
  char   cstj[8+1];              /*��������*/
              /*�������� �������Ϊ����������������ʶ���ΪӦ������Ӧ�ñ�ʶ*/
  char   jdm[80+1];              /*�ڵ���*/
              /*�ڵ���*/
  char   jdz[40+1];              /*�ڵ�ֵ*/
              /*�ڵ�ֵ*/
  char   remark[40+1];              /*˵��*/
              /*˵��*/
  char   jzlx[1+1];              /*��������*/
              /*�������� 0�Զ� 1���Զ�*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}APP_CSKZ;

#define SD_DATA  APP_CSKZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  csjz, 0),\
	DEFSDMEMBER(T_STRING,  cslx, 0),\
	DEFSDMEMBER(T_STRING,  cstj, 0),\
	DEFSDMEMBER(T_STRING,  jdm, 0),\
	DEFSDMEMBER(T_STRING,  jdz, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  jzlx, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_CSKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CSKZ_H__*/
