/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_sazh.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_sazh (����թƭ�永�˻���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_SAZH_H__
#define __GAB_DXZP_SAZH_H__
typedef struct TDB_GAB_DXZP_SAZH
{
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/**/
	long   sbpcxh;  /*�ϱ��������*/
		/**/
	char   jybm[6+1];  /*���ױ���*/
		/**/
	char   csbwlsh[53+1];  /*���䱨����ˮ��*/
		/**/
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���󵥱�ʶ ������ˮ�ţ����ڱ�ʶ�������*/
	char   ywlx[4+1];  /*ҵ������*/
		/*ҵ������*/
	char   sjtzm[4+1];  /*�¼�������*/
		/**/
	char   yywsqbh[36+1];  /*ԭ�ϱ����*/
		/*ԭ�ϱ����*/
	char   kh[30+1];  /*��/�ۺ�*/
		/**/
	char   zhm[120+1];  /*�˻���*/
		/**/
	char   zjlx[2+1];  /*֤������*/
		/**/
	char   zjhm[30+1];  /*֤����*/
		/**/
	char   lxdh[30+1];  /*��ϵ�绰*/
		/**/
	char   txdz[150+1];  /*ͨѶ��ַ*/
		/**/
	char   yzbm[10+1];  /*��������*/
		/**/
	char   zhlx[30+1];  /*�˻�����*/
		/**/
	char   zhzt[10+1];  /*�˻�״̬*/
		/**/
	char   khrq[8+1];  /*��������*/
		/**/
	char   xhrq[8+1];  /*��������*/
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

}GAB_DXZP_SAZH;

#define SD_DATA  GAB_DXZP_SAZH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  lxdh, 0),\
	DEFSDMEMBER(T_STRING,  txdz, 0),\
	DEFSDMEMBER(T_STRING,  yzbm, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  zhzt, 0),\
	DEFSDMEMBER(T_STRING,  khrq, 0),\
	DEFSDMEMBER(T_STRING,  xhrq, 0),\
	DEFSDMEMBER(T_STRING,  kkdd, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SAZH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SAZH_H__*/
