/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_jjzf.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_jjzf (����թƭֹ����ֹ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_JJZF_H__
#define __GAB_DXZP_JJZF_H__
typedef struct TDB_GAB_DXZP_JJZF
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���������󵥱�ʶ�����ڱ�ʶ�������*/
	long   rwxh;  /*�������*/
		/*�������*/
	char   yywsqbh[36+1];  /*ԭҵ��������*/
		/*ԭҵ�������� ԭ����ֹ����������ˮ��ʶ����ʩΪ�������ֹ��ʱʹ�ã�*/
	char   sfblc[2+1];  /*�Ƿ�����*/
		/*�Ƿ����� 00-�����ύ����ֹ������һ����˻���01-�����ύ����ֹ����һ����˻���02-���оٱ�����ֹ������һ����˻���03-���оٱ�����ֹ����һ����˻���04-������һ���ֹ�����̣�05-����һ���ֹ������*/
	char   yjbsqbh[36+1];  /*ԭ�ٱ�������*/
		/*ԭ�ٱ�������*/
	char   kh[30+1];  /*����*/
		/*���� ����ֹ���Ŀ���*/
	char   zczhyh[12+1];  /*ת���˻��������л�������*/
		/**/
	char   zczhyhmc[150+1];  /*ת���˻���������*/
		/**/
	char   zczhm[100+1];  /*ת���˻���*/
		/**/
	char   zczh[30+1];  /*ת���˺�*/
		/**/
	char   bz[3+1];  /*����*/
		/**/
	char   zcje[18+1];  /*ת�����*/
		/**/
	char   zcrq[8+1];  /*ת������*/
		/**/
	char   zcsj[6+1];  /*ת��ʱ��*/
		/**/
	char   khyh[12+1];  /*ֹ���˻��������л�������*/
		/**/
	char   khyhmc[150+1];  /*ֹ���˻�������������*/
		/**/
	char   zhlb[2+1];  /*ֹ���˺����*/
		/**/
	char   zhmc[120+1];  /*ֹ���˻���*/
		/**/
	char   zh[50+1];  /*ֹ���˿���*/
		/**/
	char   dqr[8+1];  /*ֹ��������*/
		/**/
	int   jgfksj;  /*��������޶�ʱ��*/
		/**/
	char   zfqssj[14+1];  /*ֹ����ʼʱ��*/
		/*ֹ����ʼʱ��*/
	char   zfjssj[14+1];  /*ֹ������ʱ��*/
		/*ֹ������ʱ��*/
	char   zxjg[1+1];  /*ִ�н��*/
		/*ִ�н�� 0-ִ�гɹ� 1-ִ��ʧ��*/
	char   respcode[8+1];  /*������*/
		/**/
	char   respmsg[100+1];  /*����ԭ��*/
		/**/
	char   zxqssj[14+1];  /*ִ����ʼʱ��*/
		/*ִ����ʼʱ��*/
	char   zxjssj[14+1];  /*ִ�н���ʱ��*/
		/*ִ�н���ʱ��*/
	char   fksm[300+1];  /*����˵��*/
		/**/
	char   fkjgmc[150+1];  /*������������*/
		/**/
	char   zhye[20+1];  /*�˻����*/
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

}GAB_DXZP_JJZF;

#define SD_DATA  GAB_DXZP_JJZF
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  sfblc, 0),\
	DEFSDMEMBER(T_STRING,  yjbsqbh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zczhyh, 0),\
	DEFSDMEMBER(T_STRING,  zczhyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zczhm, 0),\
	DEFSDMEMBER(T_STRING,  zczh, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  zcje, 0),\
	DEFSDMEMBER(T_STRING,  zcrq, 0),\
	DEFSDMEMBER(T_STRING,  zcsj, 0),\
	DEFSDMEMBER(T_STRING,  khyh, 0),\
	DEFSDMEMBER(T_STRING,  khyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zhlb, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  dqr, 0),\
	DEFSDMEMBER(T_LONG,  jgfksj, 0),\
	DEFSDMEMBER(T_STRING,  zfqssj, 0),\
	DEFSDMEMBER(T_STRING,  zfjssj, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zxqssj, 0),\
	DEFSDMEMBER(T_STRING,  zxjssj, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  zhye, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_JJZF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_JJZF_H__*/
