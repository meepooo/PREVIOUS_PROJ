/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_GYXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_GYXX (��Ա��Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_GYXX_H__
#define __APP_GYXX_H__
typedef struct TDB_APP_GYXX
{
  char   gyh[16+1];              /*��Ա��*/
              /*��Ա��*/
  char   jgbh[16+1];              /*�������*/
              /*�������*/
  char   mm[32+1];              /*��Ա����*/
              /*��Ա����*/
  char   gyjb[2+1];              /*��Ա����*/
              /*��Ա����*/
  char   gygw[32+1];              /*��Ա��λ*/
              /*��Ա��λ*/
  char   gymc[16+1];              /*��Ա����*/
              /*��Ա����*/
  char   email[32+1];              /*email*/
              /*email����*/
  char   fax[16+1];              /*����*/
              /*����*/
  char   tel[16+1];              /*�绰*/
              /*�绰*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[40+1];              /*��չ����1*/
              /*��չ����1*/
  char   extfld2[40+1];              /*��չ����2*/
              /*��չ����2*/
  char   zt[1+1];              /*״̬*/
              /*״̬*/
}APP_GYXX;

#define SD_DATA  APP_GYXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  gyh, 0),\
	DEFSDMEMBER(T_STRING,  jgbh, 0),\
	DEFSDMEMBER(T_STRING,  mm, 0),\
	DEFSDMEMBER(T_STRING,  gyjb, 0),\
	DEFSDMEMBER(T_STRING,  gygw, 0),\
	DEFSDMEMBER(T_STRING,  gymc, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  fax, 0),\
	DEFSDMEMBER(T_STRING,  tel, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_GYXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_GYXX_H__*/
