/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_DWXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_DWXX (��λ��Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_DWXX_H__
#define __APP_DWXX_H__
typedef struct TDB_APP_DWXX
{
  char   dwbh[16+1];              /*��λ���*/
              /**/
  char   dwmc[80+1];              /*��λ����*/
              /*��λ����*/
  char   dwzjlx[2+1];              /*��λ֤������*/
              /*��λ֤������ �������ֵ� KEY=K_DWZJLX*/
  char   dwzjhm[32+1];              /*��λ֤������*/
              /*��λ֤������*/
  char   dwlxr[16+1];              /*��λ��ϵ������*/
              /*��λ��ϵ������*/
  char   dwlxrdh[16+1];              /*��λ��ϵ�˵绰*/
              /*��λ��ϵ�˵绰*/
  char   dwdz[60+1];              /*��λ��ϵ��ַ*/
              /*��λ��ϵ��ַ*/
  char   dwemail[32+1];              /*��λ��ϵemail*/
              /*��λ��ϵemail*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[40+1];              /*��չ����1*/
              /*��չ����1*/
  char   extfld2[40+1];              /*��չ����2*/
              /*��չ����2*/
  char   zt[1+1];              /*״̬*/
              /*״̬ 0 ��� Xɾ��*/
}APP_DWXX;

#define SD_DATA  APP_DWXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  dwmc, 0),\
	DEFSDMEMBER(T_STRING,  dwzjlx, 0),\
	DEFSDMEMBER(T_STRING,  dwzjhm, 0),\
	DEFSDMEMBER(T_STRING,  dwlxr, 0),\
	DEFSDMEMBER(T_STRING,  dwlxrdh, 0),\
	DEFSDMEMBER(T_STRING,  dwdz, 0),\
	DEFSDMEMBER(T_STRING,  dwemail, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_DWXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DWXX_H__*/
