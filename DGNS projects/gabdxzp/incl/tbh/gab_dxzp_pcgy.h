/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_pcgy.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_pcgy (����թƭ�ϱ���Ϣ_���θ�Ҫ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_PCGY_H__
#define __GAB_DXZP_PCGY_H__
typedef struct TDB_GAB_DXZP_PCGY
{
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/*�ϱ����κ�*/
	char   scrq[8+1];  /*��������*/
		/*��������*/
	char   sjgs[10+1];  /*�¼�����*/
		/*�¼����� yckk-�쳣���� sazh-�永�˻� ycsj-�쳣�¼�*/
	char   sjtzm[6+1];  /*�¼�������*/
		/*�¼�������*/
	char   sbjg[16+1];  /*�ϱ�����*/
		/*�ϱ�����*/
	char   sbgy[16+1];  /*�ϱ���Ա*/
		/*�ϱ���Ա*/
	char   sbrq[8+1];  /*�ϱ�����*/
		/*�ϱ�����*/
	char   sbsj[6+1];  /*�ϱ�ʱ��*/
		/*�ϱ�ʱ��*/
	int   ysbjls;  /*Ԥ�ϱ���¼��*/
		/*Ԥ�ϱ���¼��*/
	int   wsbjls;  /*���ϱ���¼��*/
		/*���ϱ���¼��*/
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

}GAB_DXZP_PCGY;

#define SD_DATA  GAB_DXZP_PCGY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_STRING,  scrq, 0),\
	DEFSDMEMBER(T_STRING,  sjgs, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  sbjg, 0),\
	DEFSDMEMBER(T_STRING,  sbgy, 0),\
	DEFSDMEMBER(T_STRING,  sbrq, 0),\
	DEFSDMEMBER(T_STRING,  sbsj, 0),\
	DEFSDMEMBER(T_LONG,  ysbjls, 0),\
	DEFSDMEMBER(T_LONG,  wsbjls, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_PCGY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_PCGY_H__*/
