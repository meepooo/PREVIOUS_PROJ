/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_ycsj.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_ycsj (����թƭ�쳣�¼���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_YCSJ_H__
#define __GAB_DXZP_YCSJ_H__
typedef struct TDB_GAB_DXZP_YCSJ
{
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/**/
	int   sbpcxh;  /*�ϱ��������*/
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
	char   jylsh[64+1];  /*������ˮ��*/
		/**/
	char   jysj[14+1];  /*����ʱ��*/
		/**/
	char   jylx[20+1];  /*��������*/
		/**/
	char   bz[3+1];  /*����*/
		/**/
	char   je[20+1];  /*���׽��*/
		/**/
	char   zcyhjg[12+1];  /*ת���˻��������л�������*/
		/**/
	char   zcyhmc[136+1];  /*ת���˻�������������*/
		/**/
	char   zczhhm[60+1];  /*ת���˻���*/
		/**/
	char   zczh[30+1];  /*ת���˿���*/
		/**/
	char   ddyhjg[12+1];  /*���׶Զ��˻��������л�������*/
		/**/
	char   ddyhmc[136+1];  /*���׶Զ��˻�������������*/
		/**/
	char   ddzhm[60+1];  /*���׶Զ��˻���*/
		/**/
	char   ddzh[30+1];  /*���׶Զ��˿���*/
		/**/
	char   ipdz[30+1];  /*ip��ַ*/
		/**/
	char   mac[20+1];  /*mac��ַ*/
		/**/
	char   sbid[20+1];  /*�豸id*/
		/**/
	char   jydd[150+1];  /*���׵ص�*/
		/**/
	char   beiz[150+1];  /*��ע*/
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

}GAB_DXZP_YCSJ;

#define SD_DATA  GAB_DXZP_YCSJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jysj, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  je, 0),\
	DEFSDMEMBER(T_STRING,  zcyhjg, 0),\
	DEFSDMEMBER(T_STRING,  zcyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zczhhm, 0),\
	DEFSDMEMBER(T_STRING,  zczh, 0),\
	DEFSDMEMBER(T_STRING,  ddyhjg, 0),\
	DEFSDMEMBER(T_STRING,  ddyhmc, 0),\
	DEFSDMEMBER(T_STRING,  ddzhm, 0),\
	DEFSDMEMBER(T_STRING,  ddzh, 0),\
	DEFSDMEMBER(T_STRING,  ipdz, 0),\
	DEFSDMEMBER(T_STRING,  mac, 0),\
	DEFSDMEMBER(T_STRING,  sbid, 0),\
	DEFSDMEMBER(T_STRING,  jydd, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_YCSJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_YCSJ_H__*/
