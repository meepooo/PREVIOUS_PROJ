/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_djxj.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_djxj (����թƭ���������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_DJXJ_H__
#define __GAB_DXZP_DJXJ_H__
typedef struct TDB_GAB_DXZP_DJXJ
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���������󵥱�ʶ�����ڱ�ʶ�������*/
	int   rwxh;  /*�������*/
		/*�������*/
	char   yywsqbh[36+1];  /*ԭҵ��������*/
		/*ԭҵ�������� ԭ����ֹ����������ˮ��ʶ����ʩΪ�������ֹ��ʱʹ�ã�*/
	char   khyh[12+1];  /*�����˻��������л�������*/
		/*�����˻��������л�������*/
	char   khyhmc[150+1];  /*�����˻�������������*/
		/*�����˻�������������*/
	char   zhlb[2+1];  /*�����˺����*/
		/*�����˺����*/
	char   zhmc[120+1];  /*�����˻���*/
		/*�����˻���*/
	char   zh[50+1];  /*�����˿���*/
		/*�����˿���*/
	char   zjlx[2+1];  /*�����˻�֤������*/
		/**/
	char   zjhm[30+1];  /*�����˺�֤������*/
		/**/
	char   djfs[2+1];  /*���᷽ʽ*/
		/**/
	char   bz[3+1];  /*����*/
		/**/
	char   je[18+1];  /*���*/
		/**/
	char   dqr[8+1];  /*���ᵽ����*/
		/*���ᵽ����*/
	char   djqssj[14+1];  /*������ʼʱ��*/
		/*������ʼʱ��*/
	char   djjssj[14+1];  /*�������ʱ��*/
		/*�������ʱ��*/
	int   jgfksj;  /*��������޶�ʱ��*/
		/*��������޶�ʱ��*/
	char   zxjg[1+1];  /*ִ�н��*/
		/*ִ�н�� 0-���ɹ���1-�ɹ�*/
	char   respcode[8+1];  /*������*/
		/**/
	char   respmsg[100+1];  /*����ԭ��*/
		/**/
	char   kh[30+1];  /*����*/
		/*���� ����ֹ���Ŀ���*/
	char   zxqssj[14+1];  /*ִ����ʼʱ��*/
		/*ִ����ʼʱ��  ִ�д�ʩ��ʱ��*/
	char   zxjssj[14+1];  /*ִ�н���ʱ��*/
		/*ִ����ʼʱ��  ִ�д�ʩ��ʱ��*/
	char   fksm[300+1];  /*����˵��*/
		/**/
	char   fkjgmc[150+1];  /*������������*/
		/**/
	char   djje[20+1];  /*ִ�ж�����*/
		/**/
	char   zhye[20+1];  /*�˻����*/
		/**/
	char   zxdjje[20+1];  /*���ȶ�����*/
		/**/
	char   zxdjrq[12+1];  /*���ȶ��ᵽ����*/
		/**/
	char   zhkyye[20+1];  /*�˻��������*/
		/**/
	char   zxdjjg[60+1];  /*���ȶ������*/
		/**/
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

}GAB_DXZP_DJXJ;

#define SD_DATA  GAB_DXZP_DJXJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  khyh, 0),\
	DEFSDMEMBER(T_STRING,  khyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zhlb, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  djfs, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  je, 0),\
	DEFSDMEMBER(T_STRING,  dqr, 0),\
	DEFSDMEMBER(T_STRING,  djqssj, 0),\
	DEFSDMEMBER(T_STRING,  djjssj, 0),\
	DEFSDMEMBER(T_LONG,  jgfksj, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zxqssj, 0),\
	DEFSDMEMBER(T_STRING,  zxjssj, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  djje, 0),\
	DEFSDMEMBER(T_STRING,  zhye, 0),\
	DEFSDMEMBER(T_STRING,  zxdjje, 0),\
	DEFSDMEMBER(T_STRING,  zxdjrq, 0),\
	DEFSDMEMBER(T_STRING,  zhkyye, 0),\
	DEFSDMEMBER(T_STRING,  zxdjjg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_DJXJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_DJXJ_H__*/
