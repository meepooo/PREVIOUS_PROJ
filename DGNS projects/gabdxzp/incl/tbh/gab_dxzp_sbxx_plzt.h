/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_sbxx_plzt.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_sbxx_plzt (����թƭ�ϱ���Ϣ_����״̬��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_PLZT_H__
#define __GAB_DXZP_SBXX_PLZT_H__
typedef struct TDB_GAB_DXZP_SBXX_PLZT
{
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/**/
	int   sbpcxh;  /*�ϱ��������*/
		/**/
	char   sbjydm[6+1];  /*�ϱ����״���*/
		/**/
	char   sbzt[1+1];  /*�ϱ�״̬*/
		/*�ϱ�״̬ 0-��ʼ 1-�ɹ� 2-ʧ�� 3-��ʱ 9-�ϱ���*/
	char   respcode[8+1];  /*��Ӧ��*/
		/*��Ӧ��*/
	char   respmsg[200+1];  /*��Ӧ��Ϣ*/
		/*��Ӧ��Ϣ*/
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

}GAB_DXZP_SBXX_PLZT;

#define SD_DATA  GAB_DXZP_SBXX_PLZT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  sbjydm, 0),\
	DEFSDMEMBER(T_STRING,  sbzt, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX_PLZT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_PLZT_H__*/
