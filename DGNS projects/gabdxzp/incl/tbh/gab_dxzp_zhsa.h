/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_zhsa.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_zhsa (����թƭ�˻��永��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_ZHSA_H__
#define __GAB_DXZP_ZHSA_H__
typedef struct TDB_GAB_DXZP_ZHSA
{
	char   jybm[6+1];  /*���ױ���*/
		/**/
	char   csbwlsh[53+1];  /*���䱨����ˮ��*/
		/**/
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���󵥱�ʶ ������ˮ�ţ����ڱ�ʶ�������*/
	char   ywlx[4+1];  /*ҵ������*/
		/*ҵ������*/
	char   zh[30+1];  /*�˿���*/
		/**/
	char   zhm[120+1];  /*�˻���*/
		/**/
	char   zt[1+1];  /*״̬*/
		/*״̬(0-�����永/����������1-���永������2-�ڿ�������)*/
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

}GAB_DXZP_ZHSA;

#define SD_DATA  GAB_DXZP_ZHSA
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_ZHSA)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_ZHSA_H__*/
