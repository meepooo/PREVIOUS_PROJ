/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_sbxx_zhxx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_sbxx_zhxx (����թƭ�ϱ���Ϣ_�˻���Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_ZHXX_H__
#define __GAB_DXZP_SBXX_ZHXX_H__
typedef struct TDB_GAB_DXZP_SBXX_ZHXX
{
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/*�ϱ����κ�*/
	int   sbpcxh;  /*�ϱ��������*/
		/*�ϱ��������*/
	char   zhxh[8+1];  /*�˻����*/
		/*�������*/
	char   jybm[6+1];  /*���ױ���*/
		/*���ױ���*/
	char   csbwlsh[53+1];  /*���䱨����ˮ��*/
		/*���䱨����ˮ��*/
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*ҵ��������*/
	char   zh[30+1];  /*�˺�*/
		/**/
	char   kksj[14+1];  /*����ʱ��*/
		/**/
	char   kkdd[20+1];  /*�����ص�*/
		/**/
	char   zwrq[8+1];  /*gaps����*/
		/*gaps����*/
	char   systime[6+1];  /*gapsʱ��*/
		/*gapsʱ��*/
	char   by1[30+1];  /*����1*/
		/**/
	char   by2[254+1];  /*����2*/
		/**/
	char   by3[254+1];  /*����3*/
		/**/

}GAB_DXZP_SBXX_ZHXX;

#define SD_DATA  GAB_DXZP_SBXX_ZHXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  zhxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  kksj, 0),\
	DEFSDMEMBER(T_STRING,  kkdd, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX_ZHXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_ZHXX_H__*/
