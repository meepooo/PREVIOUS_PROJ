/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_KZSX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_KZSX (��չ���Ա�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_KZSX_H__
#define __APP_KZSX_H__
typedef struct TDB_APP_KZSX
{
  char   pkey[40+1];              /*��ֵ*/
              /*��ֵ �����Ҫ��������ı�ı���  ��¼��Ψһ�ؼ�ֵ�����ڶ���ֶ�ͨ��"|"�ָ�
                �� cpxx_001*/
  char   csmc[20+1];              /*��������*/
              /*��ʾ�������ֶ���Ӣ����ĸ��ʾ�������ڱ��ֶ�����*/
  char   cssm[80+1];              /*����˵��*/
              /*����˵��*/
  char   csz[80+1];              /*����ֵ*/
              /*������ֵ*/
  char   extfld[40+1];              /*��չ����*/
              /*��չ����*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}APP_KZSX;

#define SD_DATA  APP_KZSX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_STRING,  csmc, 0),\
	DEFSDMEMBER(T_STRING,  cssm, 0),\
	DEFSDMEMBER(T_STRING,  csz, 0),\
	DEFSDMEMBER(T_STRING,  extfld, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_KZSX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_KZSX_H__*/
