/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_RZPZ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_RZPZ (�������ñ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_RZPZ_H__
#define __APP_RZPZ_H__
typedef struct TDB_APP_RZPZ
{
  char   ssyy[8+1];              /*����Ӧ��*/
              /*Ӧ�ñ�ʶ*/
  char   czlx[1+1];              /*��������*/
              /*1 �鵵 2 ���� 3 ���� */
  char   dxlx[1+1];              /*��������*/
              /*1 ���ݿ� 2 �ļ�*/
  char   czdx1[128+1];              /*Դ��������*/
              /*�鵵ʱ���Դ��Դ�ļ�·��*/
  char   czdx2[128+1];              /*Ŀ�Ĳ�������*/
              /*�鵵ʱ���Ŀ���Ŀ���ļ�·��*/
  char   cztj[254+1];              /*��������*/
              /*���ݿ��� sql����*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[20+1];              /*��չ�ֶ�1*/
              /*��չ1*/
  char   extfld2[20+1];              /*��չ�ֶ�2*/
              /*��չ2*/
}APP_RZPZ;

#define SD_DATA  APP_RZPZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ssyy, 0),\
	DEFSDMEMBER(T_STRING,  czlx, 0),\
	DEFSDMEMBER(T_STRING,  dxlx, 0),\
	DEFSDMEMBER(T_STRING,  czdx1, 0),\
	DEFSDMEMBER(T_STRING,  czdx2, 0),\
	DEFSDMEMBER(T_STRING,  cztj, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_RZPZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_RZPZ_H__*/

