/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_CPXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_CPXX (��Ʒ������Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_CPXX_H__
#define __APP_CPXX_H__
typedef struct TDB_APP_CPXX
{
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   cpmc[40+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   yybs[8+1];              /*Ӧ�ñ�ʶ*/
              /*Ӧ�ñ�ʶ*/
  char   zbjg[16+1];              /*�������*/
              /*�������*/
  char   zbgy[16+1];              /*�����Ա*/
              /*�����Ա*/
  char   khjl[20+1];              /*�ͻ�����*/
              /*�ͻ�����*/
  char   ywrqlx[1+1];              /*ҵ����������*/
              /*ҵ���������� 1���� 2˽� Ĭ� 1*/
  char   qdkzbz[1+1];              /*�������Ʊ�־*/
              /*�������Ʊ�־ 0���� 1����� Ĭ��1*/
  char   jgkzcs[1+1];              /*�������Ʋ���*/
              /*�������Ʋ��� �������ֵ� KEY=K_JGKZC Ĭ�� ������*/
  char   sxfbz[1+1];              /*��������ȡ��־*/
              /*��������ȡ��־ 0��ȡ 1��� Ĭ��1*/
  char   sfqybz[1+1];              /*����ǩԼ��־*/
              /*0����ҪǩԼ��1 ������ǩԼ��2����ǩԼ��3 ͬʱǩ�  Ĭ�� */
  char   qyms[1+1];              /*ǩԼģʽ*/
              /*1  ��Ʒ���룫�����ʺ�  ��Ʒ���룫�û��  ��Ʒ���룫�����ʺţ��û��  Ĭ��2*/
  char   xyxljz[16+1];              /*Э�����м�ֵ*/
              /*Э�����м�ֵ Ĭ�� K_KHCPQY*/
  char   kkfs[1+1];              /*�ۿʽ*/
              /*1ȫ��ۿ2 ���ֿۿ� Ĭ��1*/
  char   jzsx[1+1];              /*����˳��*/
              /*0���������������1�ȵ����������� Ĭ��0*/
  char   dzms[1+1];              /*����ģʽ*/
              /*����ģʽ 1����Ϊ�� 2������Ϊ��*/
  char   zjyyh[8+1];              /*����Ӧ�ú�*/
              /**/
  char   zjzyyh[8+1];              /*������Ӧ�ú�*/
              /**/
  int    lsblts;              /*��ˮ��������*/
              /*��ˮ��������*/
  int    pdblts;              /*ƾ����������*/
              /*ƾ����������*/
  char   jyfs[1+1];              /*���׷�ʽ*/
              /*���׷�ʽ �������ֵ� KEY=K_JYFS*/
  char   rzms[1+1];              /*��־ģʽ*/
              /*0����  1 ��� Ĭ� 1*/
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
  char   cpzt[1+1];              /*��Ʒ״̬*/
              /*��Ʒ״̬ �������ֵ� KEY=K_CPZT*/
}APP_CPXX;

#define SD_DATA  APP_CPXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  cpmc, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  zbjg, 0),\
	DEFSDMEMBER(T_STRING,  zbgy, 0),\
	DEFSDMEMBER(T_STRING,  khjl, 0),\
	DEFSDMEMBER(T_STRING,  ywrqlx, 0),\
	DEFSDMEMBER(T_STRING,  qdkzbz, 0),\
	DEFSDMEMBER(T_STRING,  jgkzcs, 0),\
	DEFSDMEMBER(T_STRING,  sxfbz, 0),\
	DEFSDMEMBER(T_STRING,  sfqybz, 0),\
	DEFSDMEMBER(T_STRING,  qyms, 0),\
	DEFSDMEMBER(T_STRING,  xyxljz, 0),\
	DEFSDMEMBER(T_STRING,  kkfs, 0),\
	DEFSDMEMBER(T_STRING,  jzsx, 0),\
	DEFSDMEMBER(T_STRING,  dzms, 0),\
	DEFSDMEMBER(T_STRING,  zjyyh, 0),\
	DEFSDMEMBER(T_STRING,  zjzyyh, 0),\
	DEFSDMEMBER(T_LONG,  lsblts, 0),\
	DEFSDMEMBER(T_LONG,  pdblts, 0),\
	DEFSDMEMBER(T_STRING,  jyfs, 0),\
	DEFSDMEMBER(T_STRING,  rzms, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  cpzt, 0)


	DECLAREFIELDS(SD_APP_CPXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPXX_H__*/
