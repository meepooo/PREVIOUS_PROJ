/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_qhcx_zzhxx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_qhcx_zzhxx (����թƭȫ����ѯ_���˺���Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_QHCX_ZZHXX_H__
#define __GAB_DXZP_QHCX_ZZHXX_H__
typedef struct TDB_GAB_DXZP_QHCX_ZZHXX
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*������������ˮ�ţ����ڱ�ʶ�������*/
	int   rwxh;  /*�������*/
		/*�������*/
	char   zzhxh[8+1];  /*���˻����*/
		/*���˻����*/
	char   zh[40+1];  /*�ˣ�������*/
		/*�ˣ�������*/
	char   zzhlb[30+1];  /*���˻����*/
		/*���˻����*/
	char   zhzt[10+1];  /*�˻�״̬*/
		/*�˻�״̬*/
	char   bz[3+1];  /*����*/
		/*����*/
	char   chbz[8+1];  /*�����־*/
		/*�����־*/
	char   zhye[20+1];  /*�˻����*/
		/*�˻����*/
	char   kyye[20+1];  /*�������*/
		/*�������*/
	char   zhjysj[14+1];  /*�����ʱ��*/
		/*�����ʱ��*/
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

}GAB_DXZP_QHCX_ZZHXX;

#define SD_DATA  GAB_DXZP_QHCX_ZZHXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  zzhxh, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zzhlb, 0),\
	DEFSDMEMBER(T_STRING,  zhzt, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  chbz, 0),\
	DEFSDMEMBER(T_STRING,  zhye, 0),\
	DEFSDMEMBER(T_STRING,  kyye, 0),\
	DEFSDMEMBER(T_STRING,  zhjysj, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_QHCX_ZZHXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_QHCX_ZZHXX_H__*/
