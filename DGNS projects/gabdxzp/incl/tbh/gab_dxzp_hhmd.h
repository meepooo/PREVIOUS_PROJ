/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_hhmd.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_hhmd (����թƭ�ڻ�������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_HHMD_H__
#define __GAB_DXZP_HHMD_H__
typedef struct TDB_GAB_DXZP_HHMD
{
	char   mdlx[1+1];  /*��������*/
		/*�������� 0-�˺����� 1-֤������*/
	char   mdjz[64+1];  /*������ֵ*/
		/*������ֵ Hashֵ  ChinaFinancialCertificationAuthority_ԭʼֵ,��ʹ��SM3�㷨���й�ϣ�õ���ֵ,��Ϊ֤�պ���� 01_000000000000000000��Ŀǰֻ֧�����֤*/
	char   mdly[1+1];  /*������Դ*/
		/*������Դ 1-����*/
	char   ajlx[4+1];  /*��������*/
		/*�������� 1-����թƭ*/
	char   xm[100+1];  /*����*/
		/*��������Ӧ������*/
	char   mdjb[1+1];  /*��������*/
		/*�������� 0-������ 1-������ 2-������ */
	char   gxrq[8+1];  /*��������*/
		/*��������*/
	char   gxsj[6+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   by1[30+1];  /*����1*/
		/**/
	char   by2[254+1];  /*����2*/
		/**/
	char   by3[254+1];  /*����3*/
		/**/

}GAB_DXZP_HHMD;

#define SD_DATA  GAB_DXZP_HHMD
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mdlx, 0),\
	DEFSDMEMBER(T_STRING,  mdjz, 0),\
	DEFSDMEMBER(T_STRING,  mdly, 0),\
	DEFSDMEMBER(T_STRING,  ajlx, 0),\
	DEFSDMEMBER(T_STRING,  xm, 0),\
	DEFSDMEMBER(T_STRING,  mdjb, 0),\
	DEFSDMEMBER(T_STRING,  gxrq, 0),\
	DEFSDMEMBER(T_STRING,  gxsj, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_HHMD)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_HHMD_H__*/
