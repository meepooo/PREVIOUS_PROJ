/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_qhcx_qlxx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_qhcx_qlxx (����թƭȫ����ѯ_Ȩ������Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_QHCX_QLXX_H__
#define __GAB_DXZP_QHCX_QLXX_H__
typedef struct TDB_GAB_DXZP_QHCX_QLXX
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*������������ˮ�ţ����ڱ�ʶ�������*/
	int   rwxh;  /*�������*/
		/*�������*/
	char   xh[8+1];  /*���*/
		/*���*/
	char   zh[50+1];  /*�˺�*/
		/*�˺�*/
	char   kh[30+1];  /*���ۺ�*/
		/*���ۺ�*/
	char   zjlx[15+1];  /*֤�����ʹ���*/
		/*֤�����ʹ���*/
	char   zjhm[30+1];  /*֤������*/
		/*֤������*/
	char   qllx[2+1];  /*Ȩ������*/
		/*Ȩ������*/
	char   qlrxm[60+1];  /*Ȩ��������*/
		/*Ȩ��������*/
	char   qlje[20+1];  /*Ȩ�����*/
		/*Ȩ�����*/
	char   qlrtxdz[60+1];  /*Ȩ����ͨѶ��ַ*/
		/*Ȩ����ͨѶ��ַ*/
	char   qlrlxfs[50+1];  /*Ȩ������ϵ��ʽ*/
		/*Ȩ������ϵ��ʽ*/
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

}GAB_DXZP_QHCX_QLXX;

#define SD_DATA  GAB_DXZP_QHCX_QLXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  xh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  qllx, 0),\
	DEFSDMEMBER(T_STRING,  qlrxm, 0),\
	DEFSDMEMBER(T_STRING,  qlje, 0),\
	DEFSDMEMBER(T_STRING,  qlrtxdz, 0),\
	DEFSDMEMBER(T_STRING,  qlrlxfs, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_QHCX_QLXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_QHCX_QLXX_H__*/
