/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_SXFLS.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_SXFLS (��������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_SXFLS_H__
#define __APP_SXFLS_H__
typedef struct TDB_APP_SXFLS
{
  char   ptrq[8+1];              /*ƽ̨����*/
              /*ƽ̨����*/
  char   ptls[16+1];              /*ƽ̨��ˮ��*/
              /*ƽ̨��ˮ��*/
  char   flbs[32+1];              /*���ʱ�ʶ*/
              /*���ʱ�ʶ*/
  char   yybs[3+1];              /*Ӧ�ñ�ʶ*/
              /**/
  char   ywbh[16+1];              /*ҵ����*/
              /**/
  char   cpdm[16+1];              /*��Ʒ����*/
              /**/
  char   qdbs[3+1];              /*������ʶ*/
              /**/
  char   jgbs[16+1];              /*������ʶ*/
              /**/
  char   khlx[1+1];              /*�ͻ�����*/
              /**/
  char   khbh[32+1];              /*�ͻ����*/
              /*�ͻ������б��*/
  char   yhh[32+1];              /*�û���*/
              /*�û��ڵ������ͻ���*/
  char   dwbh[16+1];              /*��λ���*/
              /**/
  char   xtnbz[1+1];              /*ϵͳ�ڱ�־*/
              /*1 ϵͳ��   ϵͳ��*/
  char   jylsh[16+1];              /*������ˮ��*/
              /*��ȡ�����ѵ�ԭ������ˮ��*/
  char   jylx[1+1];              /*��������*/
              /*�������� 0 ��� 1����*/
  char   jyrq[8+1];              /*��������*/
              /**/
  char   jygy[16+1];              /*���׹�Ա*/
              /**/
  char   jyjg[16+1];              /*���׻���*/
              /**/
  double  jyje;              /*���׽��*/
              /*���׽��*/
  int    jybs;              /*���ױ���*/
              /**/
  double  sxfje;              /*�����ѽ��*/
              /*���ý��*/
  char   sfzt[1+1];              /*�շ�״̬*/
              /*��ȡ״̬ 0 δ��� 1����ȡ*/
  char   jfzh[32+1];              /*�跽�ʻ�*/
              /*�跽�ʻ�*/
  char   dfzh[32+1];              /*�����ʻ�*/
              /*�����ʻ�*/
  char   sfrq[8+1];              /*�շ�����*/
              /*�շ�����*/
  char   sfjygy[16+1];              /*�շѽ��׹�Ա*/
              /**/
  char   sfjyjg[16+1];              /*�շѽ��׻���*/
              /**/
  char   sfls[16+1];              /*�շ���ˮ��*/
              /**/
  char   lszt[1+1];              /*��ˮ״̬*/
              /*��ˮ״̬ 0 ��� 1ȡ��*/
  char   extfld2[40+1];              /*��չ�ֶ�2*/
              /**/
  char   extfld1[20+1];              /*��չ�ֶ�1*/
              /**/
  char   sm[40+1];              /*˵��*/
              /*˵��*/
}APP_SXFLS;

#define SD_DATA  APP_SXFLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  flbs, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  jgbs, 0),\
	DEFSDMEMBER(T_STRING,  khlx, 0),\
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  yhh, 0),\
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  xtnbz, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  jyrq, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_LONG,  jybs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxfje, 2),\
	DEFSDMEMBER(T_STRING,  sfzt, 0),\
	DEFSDMEMBER(T_STRING,  jfzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  sfrq, 0),\
	DEFSDMEMBER(T_STRING,  sfjygy, 0),\
	DEFSDMEMBER(T_STRING,  sfjyjg, 0),\
	DEFSDMEMBER(T_STRING,  sfls, 0),\
	DEFSDMEMBER(T_STRING,  lszt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0)


	DECLAREFIELDS(SD_APP_SXFLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_SXFLS_H__*/

