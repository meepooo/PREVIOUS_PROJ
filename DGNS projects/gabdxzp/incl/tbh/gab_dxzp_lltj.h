/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_lltj.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_lltj (����թƭ����ͳ�Ʊ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_LLTJ_H__
#define __GAB_DXZP_LLTJ_H__
typedef struct TDB_GAB_DXZP_LLTJ
{
	char   csbwlsh[53+1];  /*���䱨����ˮ��*/
		/**/
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���󵥱�ʶ ������ˮ�ţ����ڱ�ʶ�������*/
	char   tgjgbm[12+1];  /*�йܻ�������*/
		/*�йܻ�������*/
	char   ywlx[4+1];  /*ҵ������*/
		/*ҵ������*/
	char   ptywlx[4+1];  /*ƽ̨ҵ������*/
		/*ҵ������*/
	char   qssj[14+1];  /*��ʼʱ��*/
		/**/
	char   jzsj[14+1];  /*��ֹʱ��*/
		/**/
	char   tjsm[300+1];  /*ͳ��˵��*/
		/*����˵��*/
	int   llzz;  /*������ֵ*/
		/**/
	int   wfkllzz;  /*δ����������ֵ*/
		/**/
	int   qttjz;  /*����ͳ��ֵ*/
		/**/
	char   qttjsjsm[150+1];  /*����ͳ������˵��*/
		/**/
	char   bz[150+1];  /*��ע*/
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

}GAB_DXZP_LLTJ;

#define SD_DATA  GAB_DXZP_LLTJ
#define SD_MEMBERS \ 
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  tgjgbm, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  ptywlx, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jzsj, 0),\
	DEFSDMEMBER(T_STRING,  tjsm, 0),\
	DEFSDMEMBER(T_LONG,  llzz, 0),\
	DEFSDMEMBER(T_LONG,  wfkllzz, 0),\
	DEFSDMEMBER(T_LONG,  qttjz, 0),\
	DEFSDMEMBER(T_STRING,  qttjsjsm, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_LLTJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_LLTJ_H__*/
