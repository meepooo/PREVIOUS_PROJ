/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_CPSXFKZ.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_CPSXFKZ (��Ʒ�����ѿ��Ʊ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_CPSXFKZ_H__
#define __APP_CPSXFKZ_H__
typedef struct TDB_APP_CPSXFKZ
{
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   xh[2+1];              /*���*/
              /*��Ʒ�ж����������ʱ���������Զ�����������У���1��ʼ�����ϵ�������λ�ö�Ӧ*/
  char   kzsx[32+1];              /*�������Խڵ���*/
              /*�磺/app/sxf/khlx*/
  char   kzsxm[40+1];              /*��������˵��*/
              /*�������Ե�����˵��*/
  char   sxlylx[1+1];              /*������Դ����*/
              /*��������ֵ����Դ��1 ���ݿ�  �����ֵ䣬����ά�������ѹ�ϵʱѡ��������Ե�������Դ*/
  char   kzsxly[40+1];              /*����������Դ*/
              /*�����Դ����Ϊ �����ֵ䣬����ֵ��ֵ;�����Դ�����ݿ⣬��ſ������ֶ����м䶺�Ÿ���,�� T_ORG,org_i  ��ʾ�����������Ի�����Ļ�����*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[40+1];              /*��չ�ֶ�1*/
              /*˵�� */
  char   extfld2[40+1];              /*��չ�ֶ�2*/
              /*˵�� */
}APP_CPSXFKZ;

#define SD_DATA  APP_CPSXFKZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  xh, 0),\
	DEFSDMEMBER(T_STRING,  kzsx, 0),\
	DEFSDMEMBER(T_STRING,  kzsxm, 0),\
	DEFSDMEMBER(T_STRING,  sxlylx, 0),\
	DEFSDMEMBER(T_STRING,  kzsxly, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_CPSXFKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPSXFKZ_H__*/

