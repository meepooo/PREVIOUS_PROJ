/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_sajb.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_sajb (����թƭ�永�ٱ���)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_SAJB_H__
#define __GAB_DXZP_SAJB_H__
typedef struct TDB_GAB_DXZP_SAJB
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
		/*ҵ��������*/
	char   jsjgid[12+1];  /*���ջ���id*/
		/*���ջ���id*/
	char   tgjgbm[12+1];  /*�йܻ�������*/
		/*�йܻ�������*/
	char   ywlx[4+1];  /*ҵ������*/
		/*ҵ������*/
	char   shrxm[60+1];  /*�ܺ�������*/
		/**/
	char   shrlxdh[30+1];  /*�ܺ�����ϵ�绰*/
		/**/
	char   zjlx[2+1];  /*֤������*/
		/**/
	char   zjhm[30+1];  /*֤����*/
		/**/
	char   sjms[300+1];  /*�¼�����*/
		/**/
	char   ajjblx[2+1];  /*�����ٱ�����*/
		/*�����ٱ�����  01-����,02-ֹ��������*/
	char   zjrq[8+1];  /*��������*/
		/**/
	char   zjlsh[32+1];  /*������ˮ��*/
		/**/
	char   dzxh[36+1];  /*��ֹ���*/
		/*��ֹ���*/
	char   yxbz[1+1];  /*Ӱ���־*/
		/*Ӱ���־ 0-��Ӱ�� 1-��Ӱ��*/
	char   qqdzt[2+1];  /*����״̬*/
		/*����״̬ ��һλ��0-��ʼ 1-��� 2-����(�ύ) 3-��� 4-����  �ڶ�λ��0-��ʼ 1-���ɹ���2-�ɹ�; 3-��ʱ; 9-������*/
	char   zxjg[1+1];  /*ִ�н��*/
		/*ִ�н�� 0-���ɹ���1-�ɹ�*/
	char   respcode[8+1];  /*������*/
		/**/
	char   respmsg[100+1];  /*����ԭ��*/
		/**/
	char   fkdjjzsj[14+1];  /*���������ֹʱ��*/
		/**/
	char   cxjg[4+1];  /*��ѯ���*/
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

}GAB_DXZP_SAJB;

#define SD_DATA  GAB_DXZP_SAJB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jsjgid, 0),\
	DEFSDMEMBER(T_STRING,  tgjgbm, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  shrxm, 0),\
	DEFSDMEMBER(T_STRING,  shrlxdh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  sjms, 0),\
	DEFSDMEMBER(T_STRING,  ajjblx, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjlsh, 0),\
	DEFSDMEMBER(T_STRING,  dzxh, 0),\
	DEFSDMEMBER(T_STRING,  yxbz, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  fkdjjzsj, 0),\
	DEFSDMEMBER(T_STRING,  cxjg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SAJB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SAJB_H__*/
