/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_sbxx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_sbxx (����թƭ�ϱ���Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_H__
#define __GAB_DXZP_SBXX_H__
typedef struct TDB_GAB_DXZP_SBXX
{
	char   csbwlsh[53+1];  /*���䱨����ˮ��*/
		/**/
	char   jybm[6+1];  /*���ױ���*/
		/**/
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/**/
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���󵥱�ʶ ������ˮ�ţ����ڱ�ʶ�������*/
	char   sqjgdm[12+1];  /*�����������*/
		/*����������� �������ػ�������*/
	char   mbjgdm[12+1];  /*Ŀ���������*/
		/*Ŀ��������� ��Э�����󵥷��͸�Ŀ������Ĵ���*/
	char   ywlx[4+1];  /*ҵ������*/
		/*ҵ������*/
	char   sjms[500+1];  /*�¼�����*/
		/**/
	char   sbjgdm[16+1];  /*�ϱ���������*/
		/**/
	char   sbjgmc[200+1];  /*�ϱ���������*/
		/**/
	char   jbrxm[100+1];  /*����������*/
		/**/
	char   jbrdh[30+1];  /*�����˵绰*/
		/**/
	char   ywrq[8+1];  /*ҵ������*/
		/*ҵ������*/
	char   ywlsh[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   jbjg[16+1];  /*�������*/
		/*�������*/
	char   jbgy[16+1];  /*�����Ա*/
		/*�����Ա*/
	char   clrq[8+1];  /*��������*/
		/**/
	char   clsj[6+1];  /*����ʱ��*/
		/**/
	long   sbjls;  /*�ϱ���¼��*/
		/**/
	char   sbjg[2+1];  /*�ϱ����*/
		/**/
	char   respcode[8+1];  /*��Ӧ��*/
		/**/
	char   respmsg[200+1];  /*��Ӧ��Ϣ*/
		/**/
	char   zwrq[8+1];  /*gaps����*/
		/*gaps����*/
	char   systime[6+1];  /*gapsʱ��*/
		/*gapsʱ��*/
	char   zhqzlsh[16+1];  /*gaps��ˮ��*/
		/*gaps��ˮ��*/
	char   sbpcwjm[254+1];  /*�ϱ������ļ���*/
		/**/
	char   by1[30+1];  /*����1*/
		/**/
	char   by2[254+1];  /*����2*/
		/**/
	char   by3[254+1];  /*����3*/
		/**/

}GAB_DXZP_SBXX;

#define SD_DATA  GAB_DXZP_SBXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  sqjgdm, 0),\
	DEFSDMEMBER(T_STRING,  mbjgdm, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  sjms, 0),\
	DEFSDMEMBER(T_STRING,  sbjgdm, 0),\
	DEFSDMEMBER(T_STRING,  sbjgmc, 0),\
	DEFSDMEMBER(T_STRING,  jbrxm, 0),\
	DEFSDMEMBER(T_STRING,  jbrdh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_LONG,  sbjls, 0),\
	DEFSDMEMBER(T_STRING,  sbjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  zhqzlsh, 0),\
	DEFSDMEMBER(T_STRING,  sbpcwjm, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_H__*/
