/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_xdxx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_xdxx (����թƭ�´���Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_XDXX_H__
#define __GAB_DXZP_XDXX_H__
typedef struct TDB_GAB_DXZP_XDXX
{
	char   ywsqbh[36+1];  /*ҵ��������*/
		/*���󵥱�ʶ ������ˮ�ţ����ڱ�ʶ�������*/
	char   jybm[6+1];  /*���ױ���*/
		/**/
	char   xxlzms[2+1];  /*��Ϣ��תģʽ*/
		/**/
	char   csbwlsh[53+1];  /*���䱨����ˮ��*/
		/**/
	char   gaywsqbh[36+1];  /*����ҵ��������*/
		/**/
	char   fsjgbm[12+1];  /*���ͻ������*/
		/*���ͻ������*/
	char   sqjgdm[12+1];  /*�����������*/
		/*����������� �������ػ�������*/
	char   mbjgdm[12+1];  /*Ŀ���������*/
		/*Ŀ��������� ��Э�����󵥷��͸�Ŀ������Ĵ���*/
	char   cxztlb[2+1];  /*����������*/
		/*���������� 01����������� 02����Թ�����λ������*/
	char   ywlx[4+1];  /*ҵ������*/
		/*ҵ������*/
	char   jjcd[2+1];  /*�����̶�*/
		/*�����̶� 01����������02����Ӽ�*/
	char   ajbh[30+1];  /*�������*/
		/*������� ������������*/
	char   ajlx[50+1];  /*��������*/
		/*�������� ������������*/
	char   ajsy[300+1];  /*��������*/
		/*��������*/
	char   ajsm[300+1];  /*����˵��*/
		/*����˵��*/
	char   sqrq[8+1];  /*��������*/
		/*���������Ŀ�����ʱ��ϵͳ����ʱ��*/
	char   sqsj[6+1];  /*����ʱ��*/
		/*���������Ŀ�����ʱ��ϵͳ����ʱ��*/
	char   sqjgbm[12+1];  /*�����������*/
		/**/
	char   sqjgmc[150+1];  /*�����������*/
		/*�����˵�λ���� ��ѯ������������λ����*/
	char   jbrxm[40+1];  /*����������*/
		/*����������*/
	char   jbrzjlx[2+1];  /*������֤������*/
		/*������֤������ �˴�Ĭ��Ϊ110031 ����֤*/
	char   jbrzjhm[30+1];  /*������֤������*/
		/*������֤������ �����˾���*/
	char   jbrdh[30+1];  /*�����˵绰*/
		/*�������ֻ��� ��ѯ�����˵��ֻ�����*/
	char   xcrxm[40+1];  /*Э��������*/
		/*Э��������*/
	char   xcrzjlx[2+1];  /*Э����֤������*/
		/*Э����֤������ �˴�Ĭ��Ϊ110031 ����֤*/
	char   xcrzjhm[30+1];  /*Э����֤������*/
		/*Э����֤������*/
	char   ywrq[8+1];  /*ҵ������*/
		/*ҵ������*/
	char   ywlsh[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   jbjg[16+1];  /*���о������*/
		/*�������*/
	char   jbgy[16+1];  /*���о����Ա*/
		/*�����Ա*/
	char   jbxm[100+1];  /*���о�������*/
		/**/
	char   jbdh[30+1];  /*���о���绰*/
		/**/
	long   rwsl;  /*��������*/
		/*��������*/
	long   jgfkxdsj;  /*��������޶�ʱ��*/
		/*��������޶�ʱ��*/
	char   fkxdrq[8+1];  /*�����޶�����*/
		/*�����޶�����*/
	char   fkxdsj[6+1];  /*�����޶�ʱ��*/
		/*�����޶�ʱ��*/
	char   fkddrq[8+1];  /*������������*/
		/*������������*/
	char   fkddsj[6+1];  /*��������ʱ��*/
		/*��������ʱ��*/
	char   szclbz[1+1];  /*���Դ����־*/
		/*���Դ����־ 0-ϵͳ 1-�ֹ�*/
	char   clrq[8+1];  /*��������*/
		/**/
	char   clsj[6+1];  /*����ʱ��*/
		/**/
	char   zwrq[8+1];  /*gaps����*/
		/*gaps����*/
	char   systime[6+1];  /*gapsʱ��*/
		/*gapsʱ��*/
	char   zhqzlsh[16+1];  /*gaps��ˮ��*/
		/*gaps��ˮ��*/
	char   qqdzt[2+1];  /*����״̬*/
		/*����״̬ ��һλ��0-��ʼ 1-��� 2-����(�ύ) 3-��� 4-����  �ڶ�λ��0-��ʼ 1-���ɹ���2-�ɹ�; 3-��ʱ; 9-������*/
	char   ywydm[4+1];  /*ҵ��Ӧ����*/
		/*ҵ��Ӧ���� �������ҵ��Ӧ���붨��*/
	char   ywydxx[100+1];  /*ҵ��Ӧ����Ϣ*/
		/*ҵ��Ӧ����Ϣ �������ҵ��Ӧ���붨��*/
	char   zxjg[1+1];  /*ִ�н��*/
		/*ִ�н�� 0-���ɹ���1-�ɹ�*/
	char   respcode[8+1];  /*������*/
		/**/
	char   respmsg[100+1];  /*����ԭ��*/
		/**/
	char   zjrq[8+1];  /*��������*/
		/**/
	char   zjlsh[32+1];  /*������ˮ��*/
		/**/
	char   dzxh[36+1];  /*��ֹ���*/
		/*��ֹ���*/
	char   sbpch[36+1];  /*�ϱ����κ�*/
		/*�ϱ����κ�*/
	char   lxrq[8+1];  /*��ѯ����*/
		/*��ѯ����*/
	char   lxpch[32+1];  /*��ѯ���κ�*/
		/*��ѯ���κ�*/
	long   pcxh;  /*�������*/
		/*�������*/
	long   tjhxcs;  /*�ύ���Ĵ���*/
		/*�ύ���Ĵ���*/
	long   fkqzcs;  /*����ǰ�ô���*/
		/*����ǰ�ô���*/
	char   by11[30+1];  /*����11*/
		/**/
	char   by12[254+1];  /*����12*/
		/**/
	char   by13[254+1];  /*����13*/
		/**/

}GAB_DXZP_XDXX;

#define SD_DATA  GAB_DXZP_XDXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  xxlzms, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  gaywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  fsjgbm, 0),\
	DEFSDMEMBER(T_STRING,  sqjgdm, 0),\
	DEFSDMEMBER(T_STRING,  mbjgdm, 0),\
	DEFSDMEMBER(T_STRING,  cxztlb, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  jjcd, 0),\
	DEFSDMEMBER(T_STRING,  ajbh, 0),\
	DEFSDMEMBER(T_STRING,  ajlx, 0),\
	DEFSDMEMBER(T_STRING,  ajsy, 0),\
	DEFSDMEMBER(T_STRING,  ajsm, 0),\
	DEFSDMEMBER(T_STRING,  sqrq, 0),\
	DEFSDMEMBER(T_STRING,  sqsj, 0),\
	DEFSDMEMBER(T_STRING,  sqjgbm, 0),\
	DEFSDMEMBER(T_STRING,  sqjgmc, 0),\
	DEFSDMEMBER(T_STRING,  jbrxm, 0),\
	DEFSDMEMBER(T_STRING,  jbrzjlx, 0),\
	DEFSDMEMBER(T_STRING,  jbrzjhm, 0),\
	DEFSDMEMBER(T_STRING,  jbrdh, 0),\
	DEFSDMEMBER(T_STRING,  xcrxm, 0),\
	DEFSDMEMBER(T_STRING,  xcrzjlx, 0),\
	DEFSDMEMBER(T_STRING,  xcrzjhm, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  jbxm, 0),\
	DEFSDMEMBER(T_STRING,  jbdh, 0),\
	DEFSDMEMBER(T_LONG,  rwsl, 0),\
	DEFSDMEMBER(T_LONG,  jgfkxdsj, 0),\
	DEFSDMEMBER(T_STRING,  fkxdrq, 0),\
	DEFSDMEMBER(T_STRING,  fkxdsj, 0),\
	DEFSDMEMBER(T_STRING,  fkddrq, 0),\
	DEFSDMEMBER(T_STRING,  fkddsj, 0),\
	DEFSDMEMBER(T_STRING,  szclbz, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  zhqzlsh, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  ywydm, 0),\
	DEFSDMEMBER(T_STRING,  ywydxx, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjlsh, 0),\
	DEFSDMEMBER(T_STRING,  dzxh, 0),\
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_STRING,  lxrq, 0),\
	DEFSDMEMBER(T_STRING,  lxpch, 0),\
	DEFSDMEMBER(T_LONG,  pcxh, 0),\
	DEFSDMEMBER(T_LONG,  tjhxcs, 0),\
	DEFSDMEMBER(T_LONG,  fkqzcs, 0),\
	DEFSDMEMBER(T_STRING,  by11, 0),\
	DEFSDMEMBER(T_STRING,  by12, 0),\
	DEFSDMEMBER(T_STRING,  by13, 0)


	DECLAREFIELDS(SD_GAB_DXZP_XDXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_XDXX_H__*/
