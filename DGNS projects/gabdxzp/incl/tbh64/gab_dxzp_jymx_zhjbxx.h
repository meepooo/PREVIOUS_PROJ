/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_jymx_zhjbxx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_jymx_zhjbxx (����թƭ������_�˻�������Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_JYMX_ZHJBXX_H__
#define __GAB_DXZP_JYMX_ZHJBXX_H__
typedef struct TDB_GAB_DXZP_JYMX_ZHJBXX
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*������������ˮ�ţ����ڱ�ʶ�������*/
	long   rwxh;  /*�������*/
		/*�������*/
	char   zhm[120+1];  /*�˻���*/
		/*�˻���*/
	char   kzh[30+1];  /*��/�ۺ�*/
		/*��/�ۺ�*/
	char   khwd[150+1];  /*��������*/
		/*��������*/
	char   khwddm[20+1];  /*�����������*/
		/*�����������*/
	char   khrq[14+1];  /*��������*/
		/*��������*/
	char   xhrq[14+1];  /*��������*/
		/*��������*/
	char   xhwd[150+1];  /*��������*/
		/*��������*/
	char   beiz[150+1];  /*��ע*/
		/*��ע */
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

}GAB_DXZP_JYMX_ZHJBXX;

#define SD_DATA  GAB_DXZP_JYMX_ZHJBXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  kzh, 0),\
	DEFSDMEMBER(T_STRING,  khwd, 0),\
	DEFSDMEMBER(T_STRING,  khwddm, 0),\
	DEFSDMEMBER(T_STRING,  khrq, 0),\
	DEFSDMEMBER(T_STRING,  xhrq, 0),\
	DEFSDMEMBER(T_STRING,  xhwd, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_JYMX_ZHJBXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_JYMX_ZHJBXX_H__*/
