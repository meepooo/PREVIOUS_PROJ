/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_PZXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_PZXX (ƾ֤������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_PZXX_H__
#define __APP_PZXX_H__
typedef struct TDB_APP_PZXX
{
  char   ptrq[8+1];              /*ƽ̨����*/
              /*ƽ̨���� ����ƾ֤�Ľ���ƽ̨����yyyymmdd*/
  int    ptls;              /*ƽ̨��ˮ��*/
              /*ƽ̨��ˮ��*/
  int    pzxh;              /*ƾ֤���*/
              /*ƾ֤���*/
  int    ywls;              /*ҵ����ˮ��*/
              /*ҵ����ˮ*/
  char   ywrq[8+1];              /*ҵ������*/
              /*ҵ������*/
  char   yybs[8+1];              /*Ӧ�ñ�ʶ*/
              /*Ӧ�ñ�ʶ*/
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   yhbh[32+1];              /*�û����*/
              /*�û����*/
  char   yhbsh[32+1];              /*�ͻ���ʶ��*/
              /*�ͻ���ʶ��*/
  char   khmc[80+1];              /*�ͻ�����*/
              /*�ͻ�����*/
  char   yhzh[32+1];              /*�����ʺ�*/
              /*�����ʺ�*/
  double  jyje;              /*���׽��*/
              /*���׽��*/
  double  jyje2;              /*���׽��2*/
              /*���׽��2*/
  double  jyje3;              /*���׽��3*/
              /*���׽��3*/
  double  sxf;              /*������*/
              /*������*/
  char   jfzq[16+1];              /*�ɷ�����*/
              /*�ɷ�����*/
  char   qsrq[10+1];              /*��ʼ����*/
              /*��ʼ����*/
  char   jsrq[10+1];              /*��������*/
              /*��������*/
  char   sjdm[10+1];              /*˰�ִ���*/
              /*˰�ִ���*/
  char   qdbs[3+1];              /*��������*/
              /*��������*/
  char   pzzl[3+1];              /*ƾ֤����*/
              /*ƾ֤����*/
  char   pzhm[32+1];              /*ƾ֤����*/
              /*ƾ֤����*/
  char   pzsm[40+1];              /*ƾ֤˵��*/
              /*ƾ֤˵��*/
  char   dyrq[8+1];              /*��ӡ����*/
              /*��ӡ����*/
  char   dysj[6+1];              /*��ӡʱ��*/
              /*��ӡʱ��*/
  int    dyls;              /*��ӡ��ˮ��*/
              /*��ӡ��ˮ��*/
  char   dyjg[16+1];              /*��ӡ����*/
              /*��ӡ����*/
  char   dygy[16+1];              /*��ӡ��Ա*/
              /*��ӡ��Ա*/
  int    dycs;              /*��ӡ����*/
              /*��ӡ����*/
  char   jlbz[1+1];              /*��¼��־*/
              /*��¼��־ 0���� 1����*/
  char   extfld1[40+1];              /*��չ�ֶ�1*/
              /*��չ�ֶ�1*/
  char   extfld2[40+1];              /*��չ�ֶ�2*/
              /*��չ�ֶ�2*/
  long   pznr;              /*ƾ֤����*/
              /*ƾ֤����*/
}APP_PZXX;

#define SD_DATA  APP_PZXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_LONG,  pzxh, 0),\
	DEFSDMEMBER(T_LONG,  ywls, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  yhbh, 0),\
	DEFSDMEMBER(T_STRING,  yhbsh, 0),\
	DEFSDMEMBER(T_STRING,  khmc, 0),\
	DEFSDMEMBER(T_STRING,  yhzh, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  jyje2, 2),\
	DEFSDMEMBER(T_DOUBLE,  jyje3, 2),\
	DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
	DEFSDMEMBER(T_STRING,  jfzq, 0),\
	DEFSDMEMBER(T_STRING,  qsrq, 0),\
	DEFSDMEMBER(T_STRING,  jsrq, 0),\
	DEFSDMEMBER(T_STRING,  sjdm, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  pzzl, 0),\
	DEFSDMEMBER(T_STRING,  pzhm, 0),\
	DEFSDMEMBER(T_STRING,  pzsm, 0),\
	DEFSDMEMBER(T_STRING,  dyrq, 0),\
	DEFSDMEMBER(T_STRING,  dysj, 0),\
	DEFSDMEMBER(T_LONG,  dyls, 0),\
	DEFSDMEMBER(T_STRING,  dyjg, 0),\
	DEFSDMEMBER(T_STRING,  dygy, 0),\
	DEFSDMEMBER(T_LONG,  dycs, 0),\
	DEFSDMEMBER(T_STRING,  jlbz, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  pznr, 0)


	DECLAREFIELDS(SD_APP_PZXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_PZXX_H__*/
