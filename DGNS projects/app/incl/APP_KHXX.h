/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_KHXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_KHXX (�ͻ���Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_KHXX_H__
#define __APP_KHXX_H__
typedef struct TDB_APP_KHXX
{
  char   khbh[16+1];              /*�ͻ����*/
              /*�ͻ���� ������ K_KHBH ����*/
  char   khxm[80+1];              /*�ͻ�����*/
              /*�ͻ�����*/
  char   ywxm[40+1];              /*Ӣ������*/
              /*Ӣ������*/
  char   bm[20+1];              /*����*/
              /*����*/
  char   khlx[1+1];              /*�ͻ�����*/
              /*�ͻ����� �������ֵ�KEY=K_KHLX*/
  char   zjkhbh[32+1];              /*�����ͻ����*/
              /*�����ͻ����*/
  char   zjlx[3+1];              /*֤������*/
              /*֤������ �������ֵ�KEY=K_ZJLX*/
  char   zjhm[32+1];              /*֤������*/
              /*֤������*/
  char   csny[8+1];              /*��������*/
              /*��������*/
  char   sex[1+1];              /*�Ա�*/
              /*�Ա� �������ֵ�KEY=K_SEX*/
  char   gj[3+1];              /*����*/
              /*����*/
  char   hk[60+1];              /*����*/
              /*����*/
  char   hyzk[1+1];              /*����״��*/
              /*����״�� 0δ�� 1�ѻ� 2��� 9δ֪*/
  char   jycd[1+1];              /*�����̶�*/
              /*�����̶� �������ֵ�KEY=K_JYCD*/
  char   zy[3+1];              /*ְҵ*/
              /*ְҵ  ���ݹ��ұ�׼*/
  char   zw[20+1];              /*ְ��*/
              /*ְ��*/
  double  srqk;              /*���������*/
              /*���������*/
  char   gsdz[60+1];              /*��˾��ַ*/
              /*��˾��ַ*/
  char   gsyb[6+1];              /*��˾�ʱ�*/
              /*��˾�ʱ�*/
  char   gsdh[16+1];              /*��˾�绰*/
              /*��˾�绰*/
  char   zzdz[60+1];              /*סլ��ַ*/
              /*סլ��ַ*/
  char   zzyb[6+1];              /*סլ�ʱ�*/
              /*סլ�ʱ�*/
  char   zzdh[16+1];              /*סլ�绰*/
              /*סլ�绰*/
  char   sjhm[16+1];              /*�ֻ�����*/
              /*�ֻ�����*/
  char   memail[32+1];              /*��������*/
              /*��������*/
  char   yjdzlx[1+1];              /*�ʼĵ�ַ����*/
              /*�ʼĵ�ַ���� 1��˾��ַ2סլ��ַ*/
  char   bz[1+1];              /*��־*/
              /*��־ 0���� 1��Ч Xɾ��*/
}APP_KHXX;

#define SD_DATA  APP_KHXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  khxm, 0),\
	DEFSDMEMBER(T_STRING,  ywxm, 0),\
	DEFSDMEMBER(T_STRING,  bm, 0),\
	DEFSDMEMBER(T_STRING,  khlx, 0),\
	DEFSDMEMBER(T_STRING,  zjkhbh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  csny, 0),\
	DEFSDMEMBER(T_STRING,  sex, 0),\
	DEFSDMEMBER(T_STRING,  gj, 0),\
	DEFSDMEMBER(T_STRING,  hk, 0),\
	DEFSDMEMBER(T_STRING,  hyzk, 0),\
	DEFSDMEMBER(T_STRING,  jycd, 0),\
	DEFSDMEMBER(T_STRING,  zy, 0),\
	DEFSDMEMBER(T_STRING,  zw, 0),\
	DEFSDMEMBER(T_DOUBLE,  srqk, 2),\
	DEFSDMEMBER(T_STRING,  gsdz, 0),\
	DEFSDMEMBER(T_STRING,  gsyb, 0),\
	DEFSDMEMBER(T_STRING,  gsdh, 0),\
	DEFSDMEMBER(T_STRING,  zzdz, 0),\
	DEFSDMEMBER(T_STRING,  zzyb, 0),\
	DEFSDMEMBER(T_STRING,  zzdh, 0),\
	DEFSDMEMBER(T_STRING,  sjhm, 0),\
	DEFSDMEMBER(T_STRING,  memail, 0),\
	DEFSDMEMBER(T_STRING,  yjdzlx, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0)


	DECLAREFIELDS(SD_APP_KHXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_KHXX_H__*/

