/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_hmhh.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_hmhh (����թƭ�����кű�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_HMHH_H__
#define __GAB_DXZP_HMHH_H__
typedef struct TDB_GAB_DXZP_HMHH
{
	char   hh[14+1];  /*�к�*/
		/*�к�*/
	int   xh;  /*���*/
		/*���*/
	char   hm[100+1];  /*����*/
		/*����*/
	char   hb[1+1];  /*�б�*/
		/*�б�  1-ȫ�������� 2-������ҵ���� 3-ʡ��ũ������  4-ũ����ҵ���� 5-��Ӫ���� 9-�������� t-�й����� T-��������*/
	char   hbsm[20+1];  /*�б�˵��*/
		/*�б�˵��*/
	char   jbjg[16+1];  /*�������*/
		/*�������*/
	char   jbgy[16+1];  /*�����Ա*/
		/*�����Ա*/
	char   lxdh[20+1];  /*�����˵绰*/
		/*�����˵绰*/
	char   by1[30+1];  /*����1*/
		/**/
	char   by2[254+1];  /*����2*/
		/**/
	char   by3[254+1];  /*����3*/
		/**/

}GAB_DXZP_HMHH;

#define SD_DATA  GAB_DXZP_HMHH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  hh, 0),\
	DEFSDMEMBER(T_LONG,  xh, 0),\
	DEFSDMEMBER(T_STRING,  hm, 0),\
	DEFSDMEMBER(T_STRING,  hb, 0),\
	DEFSDMEMBER(T_STRING,  hbsm, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  lxdh, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_HMHH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_HMHH_H__*/
