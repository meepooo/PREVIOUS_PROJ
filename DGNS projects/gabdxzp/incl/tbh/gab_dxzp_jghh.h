/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_jghh.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_jghh (����թƭ�����кű�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_JGHH_H__
#define __GAB_DXZP_JGHH_H__
typedef struct TDB_GAB_DXZP_JGHH
{
	char   jgh[16+1];  /*������*/
		/*�����ţ�һ��ָ�йܻ�����*/
	char   hh[14+1];  /*�к�*/
		/*�к�*/
	char   jgmc[100+1];  /*��������*/
		/*��������*/
	char   by1[30+1];  /*����1*/
		/**/
	char   by2[254+1];  /*����2*/
		/**/
	char   by3[254+1];  /*����3*/
		/**/

}GAB_DXZP_JGHH;

#define SD_DATA  GAB_DXZP_JGHH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  jgh, 0),\
	DEFSDMEMBER(T_STRING,  hh, 0),\
	DEFSDMEMBER(T_STRING,  jgmc, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_JGHH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_JGHH_H__*/
