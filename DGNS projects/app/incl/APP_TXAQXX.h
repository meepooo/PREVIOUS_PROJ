/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_TXAQXX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_TXAQXX (ͨѶ��ȫ��Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_TXAQXX_H__
#define __APP_TXAQXX_H__
typedef struct TDB_APP_TXAQXX
{
  char   ljbs[8+1];              /*������ʶ*/
              /*������ʶ L_*/
  char   ljmc[40+1];              /*��������*/
              /*��������*/
  char   ljlx[1+1];              /*��������*/
              /*�������� 1�������� 2��������ϵͳ 3������λ 9����*/
  char   dwbh[16+1];              /*��λ���*/
              /*��λ��� ���������*/
  char   qdkz[1+1];              /*ǩ������*/
              /*�Ƿ����ǩ��״̬��Ĭ��1��
                0 ���� 1������*/
  char   txms[1+1];              /*ͨѶģʽ*/
              /*ͨѶģʽ�������ֵ� KEY=K_TXMS*/
  char   txdz[100+1];              /*ͨѶ��ַ*/
              /*ͨѶ��ַ*/
  char   txdk[6+1];              /*ͨѶ�˿�*/
              /*ͨѶ�˿�*/
  int    fscs;              /*���ͳ�ʱ*/
              /*���ͳ�ʱ*/
  int    jscs;              /*���ճ�ʱ*/
              /*���ճ�ʱ*/
  char   ljjgh[16+1];              /*����������*/
              /*����������*/
  char   ljgyh[16+1];              /*������Ա��*/
              /*������Ա��*/
  char   ljzdh[16+1];              /*�����ն˺�*/
              /*�����ն˺�*/
  char   key1[128+1];              /*��Կ1*/
              /*��Կ1*/
  char   key2[128+1];              /*��Կ2*/
              /*��Կ2*/
  char   key3[128+1];              /*��Կ3*/
              /*��Կ3*/
  char   ftpdz[16+1];              /*FTP��ַ*/
              /*ftp��ַ��Ĭ��ͬͨѶ��ַ*/
  char   ftpyh[16+1];              /*FTP�û�*/
              /*ftp�û�����*/
  char   ftpmm[32+1];              /*FTP����*/
              /*ftp�û�����*/
  char   ftpgzfs[1+1];              /*FTP������ʽ*/
              /*(1 ����ģʽ 2 ����ģʽii)*/
  char   ftpcsfs[1+1];              /*FTP���䷽ʽ*/
              /*ftp���䷽ʽ(1 bin 2 ascii)*/
  char   ftpzdms[1+1];              /*FTP��������ģʽ*/
              /*0-����PORT 1-����PASV*/
  char   ftpdflj[40+1];              /*�Է��ļ�·��*/
              /*�Է��ļ����·��*/
  char   ftpbdlj[40+1];              /*�����ļ�·��*/
              /*�����ļ����·��*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
  char   extfld1[40+1];              /*��չ�ֶ�1*/
              /*��չ�ֶ�1*/
  char   extfld2[254+1];              /*��չ�ֶ�2*/
              /*��չ�ֶ�2*/
  char   txzt[1+1];              /*ͨѶ״̬*/
              /*ͨѶ״̬ 0���� 9��Ч*/
  char   qdzt[1+1];              /*ǩ��״̬*/
              /*ǩ��״̬  1ǩ�� 2ǩ�� */
}APP_TXAQXX;

#define SD_DATA  APP_TXAQXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ljbs, 0),\
	DEFSDMEMBER(T_STRING,  ljmc, 0),\
	DEFSDMEMBER(T_STRING,  ljlx, 0),\
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  qdkz, 0),\
	DEFSDMEMBER(T_STRING,  txms, 0),\
	DEFSDMEMBER(T_STRING,  txdz, 0),\
	DEFSDMEMBER(T_STRING,  txdk, 0),\
	DEFSDMEMBER(T_LONG,  fscs, 0),\
	DEFSDMEMBER(T_LONG,  jscs, 0),\
	DEFSDMEMBER(T_STRING,  ljjgh, 0),\
	DEFSDMEMBER(T_STRING,  ljgyh, 0),\
	DEFSDMEMBER(T_STRING,  ljzdh, 0),\
	DEFSDMEMBER(T_STRING,  key1, 0),\
	DEFSDMEMBER(T_STRING,  key2, 0),\
	DEFSDMEMBER(T_STRING,  key3, 0),\
	DEFSDMEMBER(T_STRING,  ftpdz, 0),\
	DEFSDMEMBER(T_STRING,  ftpyh, 0),\
	DEFSDMEMBER(T_STRING,  ftpmm, 0),\
	DEFSDMEMBER(T_STRING,  ftpgzfs, 0),\
	DEFSDMEMBER(T_STRING,  ftpcsfs, 0),\
	DEFSDMEMBER(T_STRING,  ftpzdms, 0),\
	DEFSDMEMBER(T_STRING,  ftpdflj, 0),\
	DEFSDMEMBER(T_STRING,  ftpbdlj, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  txzt, 0),\
	DEFSDMEMBER(T_STRING,  qdzt, 0)


	DECLAREFIELDS(SD_APP_TXAQXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_TXAQXX_H__*/

