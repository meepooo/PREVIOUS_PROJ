/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_cskz.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_cskz (ס�����������ʼ������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_CSKZ_H__
#define __YW_GJJ_CSKZ_H__
typedef struct TDB_YW_GJJ_CSKZ
{
	char   csjz[20+1];  /*������ֵ*/
		/*������ֵ*/
	char   cslx[1+1];  /*��������*/
		/*��������*/
	char   cstj[8+1];  /*��������*/
		/*�������� �������Ϊ����������������ʶ���ΪӦ������Ӧ�ñ�ʶ*/
	char   jdm[80+1];  /*�ڵ���*/
		/*�ڵ���*/
	char   jdz[40+1];  /*�ڵ�ֵ*/
		/*�ڵ�ֵ*/
	char   remark[40+1];  /*˵��*/
		/*˵��*/
	char   jzlx[1+1];  /*��������*/
		/*�������� 0�Զ� 1���Զ�*/
	char   whjg[16+1];  /*����*/
		/**/
	char   whgy[16+1];  /*��Ա*/
		/**/
	char   whsj[14+1];  /*ʱ��*/
		/**/

}YW_GJJ_CSKZ;

#define SD_DATA  YW_GJJ_CSKZ
#define SD_MEMBERS \ 
	DEFSDMEMBER(T_STRING,  csjz, 0),\
	DEFSDMEMBER(T_STRING,  cslx, 0),\
	DEFSDMEMBER(T_STRING,  cstj, 0),\
	DEFSDMEMBER(T_STRING,  jdm, 0),\
	DEFSDMEMBER(T_STRING,  jdz, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  jzlx, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_YW_GJJ_CSKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CSKZ_H__*/
