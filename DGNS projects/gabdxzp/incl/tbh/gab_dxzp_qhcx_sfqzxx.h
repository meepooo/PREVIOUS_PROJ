/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_qhcx_sfqzxx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_qhcx_sfqzxx (����թƭȫ����ѯ_˾��ǿ����Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_QHCX_SFQZXX_H__
#define __GAB_DXZP_QHCX_SFQZXX_H__
typedef struct TDB_GAB_DXZP_QHCX_SFQZXX
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*������������ˮ�ţ����ڱ�ʶ�������*/
	int   rwxh;  /*�������*/
		/*�������*/
	char   csxh[8+1];  /*��ʩ���*/
		/*��ʩ���*/
	char   zh[50+1];  /*�˺�*/
		/*�˺�*/
	char   kh[30+1];  /*���ۺ�*/
		/*���ۺ�*/
	char   djksr[14+1];  /*���Ὺʼ��*/
		/*���Ὺʼ��*/
	char   djjzr[14+1];  /*�����ֹ��*/
		/*�����ֹ��*/
	char   djjgmc[50+1];  /*�����������*/
		/*�����������*/
	char   bz[3+1];  /*����*/
		/*����*/
	char   djje[20+1];  /*������*/
		/*������*/
	char   beiz[1000+1];  /*��ע*/
		/*��ע*/
	char   djcslx[4+1];  /*�����ʩ����*/
		/*�����ʩ����*/
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

}GAB_DXZP_QHCX_SFQZXX;

#define SD_DATA  GAB_DXZP_QHCX_SFQZXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  csxh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  djksr, 0),\
	DEFSDMEMBER(T_STRING,  djjzr, 0),\
	DEFSDMEMBER(T_STRING,  djjgmc, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  djje, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  djcslx, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_QHCX_SFQZXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_QHCX_SFQZXX_H__*/
