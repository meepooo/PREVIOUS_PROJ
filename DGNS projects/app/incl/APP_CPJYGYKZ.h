/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_CPJYGYKZ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_CPJYGYKZ (��Ʒ���׹�Ա�������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_CPJYGYKZ_H__
#define __APP_CPJYGYKZ_H__
typedef struct TDB_APP_CPJYGYKZ
{
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   jydm[8+1];              /*���״���*/
              /*���״���*/
  char   kzbz[1+1];              /*���Ʊ�־*/
              /*0 ������ 1����*/
  char   gyjb[2+1];              /*��Ա����*/
              /*�����ֵ� K_APP_GYJB*/
  char   cxcl[1+1];              /*���޴���*/
              /*0 ���׾ܾ� 1 �����Ȩ��Ա���� 2 �����Ȩ��Ա��λ 3 �����Ȩ��Ա����͸�λ*/
  char   sqgygw[8+1];              /*��Ȩ��Ա��λ*/
              /*�����ֵ�K_APP_GYGW*/
  char   sqgyjb[2+1];              /*��Ȩ��Ա����*/
              /*�����ֵ�K_APP_GYJB*/
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
}APP_CPJYGYKZ;

#define SD_DATA  APP_CPJYGYKZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  kzbz, 0),\
	DEFSDMEMBER(T_STRING,  gyjb, 0),\
	DEFSDMEMBER(T_STRING,  cxcl, 0),\
	DEFSDMEMBER(T_STRING,  sqgygw, 0),\
	DEFSDMEMBER(T_STRING,  sqgyjb, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_CPJYGYKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPJYGYKZ_H__*/
