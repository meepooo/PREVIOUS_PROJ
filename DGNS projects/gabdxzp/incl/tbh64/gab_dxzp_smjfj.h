/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_smjfj.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_smjfj (����թƭɨ���������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_SMJFJ_H__
#define __GAB_DXZP_SMJFJ_H__
typedef struct TDB_GAB_DXZP_SMJFJ
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*ҵ��������*/
	long   xh;  /*���*/
		/*���*/
	char   wjm[254+1];  /*�ļ���*/
		/**/
	char   wjdx[12+1];  /*�ļ���С*/
		/**/
	char   yxjz[36+1];  /*Ӱ��ֵ*/
		/*Ӱ��ֵ*/
	char   zwrq[8+1];  /*gaps����*/
		/*gaps����*/
	char   systime[6+1];  /*gapsʱ��*/
		/*gapsʱ��*/
	char   by1[30+1];  /*����1*/
		/*����1*/
	char   by2[254+1];  /*����2*/
		/*����2*/
	char   by3[254+1];  /*����3*/
		/*����3*/

}GAB_DXZP_SMJFJ;

#define SD_DATA  GAB_DXZP_SMJFJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  xh, 0),\
	DEFSDMEMBER(T_STRING,  wjm, 0),\
	DEFSDMEMBER(T_STRING,  wjdx, 0),\
	DEFSDMEMBER(T_STRING,  yxjz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SMJFJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SMJFJ_H__*/
