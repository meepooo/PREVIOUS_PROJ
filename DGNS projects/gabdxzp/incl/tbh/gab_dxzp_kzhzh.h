/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_kzhzh.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_kzhzh (���˺��ۺ���Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_KZHZH_H__
#define __GAB_DXZP_KZHZH_H__
typedef struct TDB_GAB_DXZP_KZHZH
{
	char   zh[30+1];  /*�˺�*/
		/**/
	char   kh[30+1];  /*����*/
		/**/
	char   zhmc[100+1];  /*�˻���*/
		/**/
	int   dccs;  /*�������*/
		/**/
	char   dczt[1+1];  /*����״̬*/
		/*0-����  1-���*/
	char   dcywsqbh[40+1];  /*��������ҵ���*/
		/**/
	char   dcqssj[14+1];  /*������ʼʱ��*/
		/**/
	char   dcjssj[14+1];  /*�������ʱ��*/
		/**/
	int   djcs;  /*�������*/
		/**/
	char   djzt[1+1];  /*����״̬*/
		/*0-����  1-��� 2-���� 9-��ʼ*/
	double   djljje;  /*�����ۼƽ��*/
		/**/
	char   djywsqbh[40+1];  /*��������ҵ���*/
		/**/
	char   djqssj[14+1];  /*������ʼʱ��*/
		/**/
	char   djjssj[14+1];  /*�������ʱ��*/
		/**/
	int   zfcs;  /*ֹ������*/
		/*0-ֹ��  1-��� 2-��ֹ  9-��ʼ*/
	char   zfzt[1+1];  /*ֹ��״̬*/
		/**/
	double   zfljje;  /*ֹ���ۼƽ��*/
		/**/
	char   zfywsqbh[40+1];  /*ֹ������ҵ���*/
		/**/
	char   zfqssj[14+1];  /*ֹ����ʼʱ��*/
		/**/
	char   zfjssj[14+1];  /*ֹ������ʱ��*/
		/**/
	int   khcs;  /*�ۻ�����*/
		/**/
	double   khljje;  /*�ۻ��ۼƽ��*/
		/**/
	char   khywsqbh[40+1];  /*�ۻ�����ҵ���*/
		/**/
	char   by1[32+1];  /*����1*/
		/**/
	char   by2[255+1];  /*����2*/
		/**/
	char   by3[255+1];  /*����3*/
		/**/

}GAB_DXZP_KZHZH;

#define SD_DATA  GAB_DXZP_KZHZH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_LONG,  dccs, 0),\
	DEFSDMEMBER(T_STRING,  dczt, 0),\
	DEFSDMEMBER(T_STRING,  dcywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  dcqssj, 0),\
	DEFSDMEMBER(T_STRING,  dcjssj, 0),\
	DEFSDMEMBER(T_LONG,  djcs, 0),\
	DEFSDMEMBER(T_STRING,  djzt, 0),\
	DEFSDMEMBER(T_DOUBLE,  djljje, 2),\
	DEFSDMEMBER(T_STRING,  djywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  djqssj, 0),\
	DEFSDMEMBER(T_STRING,  djjssj, 0),\
	DEFSDMEMBER(T_LONG,  zfcs, 0),\
	DEFSDMEMBER(T_STRING,  zfzt, 0),\
	DEFSDMEMBER(T_DOUBLE,  zfljje, 2),\
	DEFSDMEMBER(T_STRING,  zfywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  zfqssj, 0),\
	DEFSDMEMBER(T_STRING,  zfjssj, 0),\
	DEFSDMEMBER(T_LONG,  khcs, 0),\
	DEFSDMEMBER(T_DOUBLE,  khljje, 2),\
	DEFSDMEMBER(T_STRING,  khywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_KZHZH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_KZHZH_H__*/

