/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:gab_dxzp_lxdx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:gab_dxzp_lxdx (����թƭ��ѯ�´��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __GAB_DXZP_LXDX_H__
#define __GAB_DXZP_LXDX_H__
typedef struct TDB_GAB_DXZP_LXDX
{
	char   lxrq[8+1];  /*��ѯ����*/
		/**/
	char   lxpch[32+1];  /*��ѯ���κ�*/
		/**/
	char   lxsj[6+1];  /*��ѯʱ��*/
		/**/
	char   respcode[6+1];  /*������*/
		/**/
	char   respmsg[200+1];  /*������Ϣ*/
		/**/
	int   lxbs;  /*��ѯ����*/
		/**/
	char   lxwj[254+1];  /*��ѯ�ļ�*/
		/**/
	char   by1[32+1];  /*����1*/
		/**/
	char   by2[254+1];  /*����2*/
		/**/
	char   by3[254+1];  /*����3*/
		/**/

}GAB_DXZP_LXDX;

#define SD_DATA  GAB_DXZP_LXDX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  lxrq, 0),\
	DEFSDMEMBER(T_STRING,  lxpch, 0),\
	DEFSDMEMBER(T_STRING,  lxsj, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_LONG,  lxbs, 0),\
	DEFSDMEMBER(T_STRING,  lxwj, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_LXDX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_LXDX_H__*/
