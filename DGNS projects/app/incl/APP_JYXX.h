/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_JYXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_JYXX (������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_JYXX_H__
#define __APP_JYXX_H__
typedef struct TDB_APP_JYXX
{
  char   jydm[8+1];              /*���״���*/
              /*���״���*/
  char   jymc[40+1];              /*��������*/
              /*��������*/
  char   yybs[8+1];              /*Ӧ�ñ�ʶ*/
              /*Ӧ�ñ�ʶ Ӧ�ñ�ʶ ��app_yyxx��*/
  char   jylx[1+1];              /*��������*/
              /*�������� 0������ 1����� 9����*/
  char   lsjlbz[1+1];              /*��ˮ��¼��־*/
              /*��ˮ��¼��־ 0��¼ 1����¼*/
  char   rzbz[1+1];              /*���ʱ�־*/
              /*���ʱ�־ 0���� 1������*/
  char   bbbz[1+1];              /*�����־*/
              /*�����־ 0���� 1�Ǳ���*/
  char   cpxg[1+1];              /*��Ʒ���*/
              /*��Ʒ��� 0��� 1�����(�������Ʒ�޹�ʱ�����׵Ļ���������������ʱ�䣬�޶�ȶ���������)*/
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
  char   qtbz[1+1];              /*��ͣ��־*/
              /*��ͣ��־ 0���� 1�ر�*/
}APP_JYXX;

#define SD_DATA  APP_JYXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  jymc, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  lsjlbz, 0),\
	DEFSDMEMBER(T_STRING,  rzbz, 0),\
	DEFSDMEMBER(T_STRING,  bbbz, 0),\
	DEFSDMEMBER(T_STRING,  cpxg, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qtbz, 0)


	DECLAREFIELDS(SD_APP_JYXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_JYXX_H__*/

