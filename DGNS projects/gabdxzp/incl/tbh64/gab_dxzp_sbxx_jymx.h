/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_sbxx_jymx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_sbxx_jymx (����թƭ�ϱ���Ϣ_������ϸ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_JYMX_H__
#define __GAB_DXZP_SBXX_JYMX_H__
typedef struct TDB_GAB_DXZP_SBXX_JYMX
{
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/*�ϱ����κ�*/
	long   sbpcxh;  /*�ϱ��������*/
		/*�ϱ��������*/
	char   zhxh[8+1];  /*�˻����*/
		/*�˻����*/
	long   jyxh;  /*�������*/
		/*�������*/
	char   jybm[6+1];  /*���ױ���*/
		/*���ױ���*/
	char   csbwlsh[53+1];  /*���䱨����ˮ��*/
		/*���䱨����ˮ��*/
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*ҵ��������*/
	char   sjtzm[4+1];  /*�¼�������*/
		/*�¼�������*/
	char   zh[50+1];  /*�˿���*/
		/*�˿���*/
	char   zhm[120+1];  /*�˻���*/
		/*�˻���*/
	char   zjlx[6+1];  /*֤������*/
		/*֤������*/
	char   zjhm[30+1];  /*֤����*/
		/*֤����*/
	char   jylsh[64+1];  /*������ˮ��*/
		/*������ˮ��*/
	char   jysj[14+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   jylx[20+1];  /*��������*/
		/*��������*/
	char   bz[3+1];  /*����*/
		/*����*/
	char   jyje[20+1];  /*���׽��*/
		/*���׽��*/
	char   zczhyhjg[12+1];  /*ת���˻����л���*/
		/*ת���˻����л���*/
	char   zczhyhmc[136+1];  /*ת���˻���������*/
		/*ת���˻���������*/
	char   zczhm[60+1];  /*ת���˻���*/
		/*ת���˻���������*/
	char   zczh[30+1];  /*ת���˺�*/
		/*ת���˺�*/
	char   ddzhyhjg[12+1];  /*�Զ��˻����л���*/
		/*�Զ��˻����л���*/
	char   ddzhyhmc[136+1];  /*�Զ��˻���������*/
		/*�Զ��˻���������*/
	char   ddzhm[60+1];  /*�Զ��˻���*/
		/*�Զ��˻���*/
	char   ddzh[30+1];  /*�Զ��˺�*/
		/*�Զ��˺�*/
	char   ip[30+1];  /*ip��ַ*/
		/*ip��ַ*/
	char   mac[20+1];  /*mac��ַ*/
		/*mac��ַ*/
	char   sbid[20+1];  /*�豸id*/
		/*�豸id*/
	char   jydd[150+1];  /*���׵ص�*/
		/*���׵ص�*/
	char   beiz[150+1];  /*��ע*/
		/**/
	char   zfbz[1+1];  /*ֹ����־*/
		/*ֹ����־ 0-��ֹ����1-δֹ����*/
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

}GAB_DXZP_SBXX_JYMX;

#define SD_DATA  GAB_DXZP_SBXX_JYMX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  zhxh, 0),\
	DEFSDMEMBER(T_LONG,  jyxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jysj, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  jyje, 0),\
	DEFSDMEMBER(T_STRING,  zczhyhjg, 0),\
	DEFSDMEMBER(T_STRING,  zczhyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zczhm, 0),\
	DEFSDMEMBER(T_STRING,  zczh, 0),\
	DEFSDMEMBER(T_STRING,  ddzhyhjg, 0),\
	DEFSDMEMBER(T_STRING,  ddzhyhmc, 0),\
	DEFSDMEMBER(T_STRING,  ddzhm, 0),\
	DEFSDMEMBER(T_STRING,  ddzh, 0),\
	DEFSDMEMBER(T_STRING,  ip, 0),\
	DEFSDMEMBER(T_STRING,  mac, 0),\
	DEFSDMEMBER(T_STRING,  sbid, 0),\
	DEFSDMEMBER(T_STRING,  jydd, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  zfbz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX_JYMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_JYMX_H__*/
