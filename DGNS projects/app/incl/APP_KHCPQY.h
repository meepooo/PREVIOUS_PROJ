/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_KHCPQY.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_KHCPQY (�ͻ���ƷǩԼ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_KHCPQY_H__
#define __APP_KHCPQY_H__
typedef struct TDB_APP_KHCPQY
{
  char   xybh[20+1];              /*Э����*/
              /*Э���� ���������ɣ���Ʒ��Ϣ�������ã�*/
  char   khbh[16+1];              /*�ͻ����*/
              /*�ͻ����*/
  char   cpdm[16+1];              /*��Ʒ����*/
              /*��Ʒ����*/
  char   ywbh[16+1];              /*ҵ����*/
              /*ҵ���� */
  char   zhlx[2+1];              /*�˻�����*/
              /*�˻����� */
  char   khjg[16+1];              /*��������*/
              /*ǩԼ�˻���������*/
  char   qyzh[32+1];              /*ǩԼ�˻�*/
              /*ǩԼ�˻�*/
  char   zhhm[60+1];              /*�˻�����*/
              /*�˻�����*/
  char   dlzjlx[3+1];              /*����֤������*/
              /*������֤������ �������ֵ� KEY=K_ZJLX*/
  char   dlzjhm[32+1];              /*����֤������*/
              /*������֤������*/
  char   zjlx[3+1];              /*֤������*/
              /*֤������ �������ֵ� KEY=K_ZJLX*/
  char   zjhm[32+1];              /*֤������*/
              /*֤������*/
  char   qylx[1+1];              /*ǩԼ����*/
              /*ǩԼ���� 0���� 1���� 9����*/
  char   khjl[20+1];              /*�ͻ�����*/
              /*�ͻ�����*/
  char   hyksrq[8+1];              /*��Լ��ʼ����*/
              /*��Լ��ʼ����*/
  char   hyjsrq[8+1];              /*��Լ��������*/
              /*��Լ��������*/
  char   ktqd[60+1];              /*��ͨ����*/
              /*��ͨ����  ������ʶͨ�� | ��ָ��� ALL��ʾȫ��ͨ*/
  char   bljg[16+1];              /*�������*/
              /*�������*/
  char   blgy[16+1];              /*�����Ա*/
              /*�����Ա*/
  char   blrq[8+1];              /*��������*/
              /*��������*/
  char   yhh1[32+1];              /*�û���1*/
              /*�û���1*/
  char   yhh2[32+1];              /*�û���2*/
              /*�û���2*/
  char   yhh3[32+1];              /*�û���3*/
              /*�û���3*/
  char   yhmc[80+1];              /*�û�����*/
              /*�û�����(�������û�����)*/
  char   yhlx[16+1];              /*�û�����*/
              /*�û�����(�������û�����)*/
  char   yhyb[6+1];              /*�û��ʱ�*/
              /*�û��ʱ�(�������û��ʱ�)*/
  char   yhdh[12+1];              /*�û��绰*/
              /*�û��绰(�������û��绰)*/
  char   yhdz[60+1];              /*�û���ַ*/
              /*�û���ַ(�������û���ַ)*/
  char   jybz[3+1];              /*���ױ���*/
              /*���ױ���*/
  double  kkzdxe;              /*�ۿ�����޶�*/
              /*�ۿ�����޶�*/
  char   kkzq[1+1];              /*�ۿ�����*/
              /*�ۿ�����  --0-û���ڣ�1-�գ�2-�ܣ�3-�£�4-��*/
  char   ydkkrq[8+1];              /*Լ���ۿ�����*/
              /*Լ���ۿ�����*/
  char   kkzt[1+1];              /*�ۿ�״̬*/
              /*���һ�οۿ�״̬ 0  �ɹ�  1 ���ֳɹ�  2-ʧ�� */
  char   kkrq[8+1];              /*�ۿ�����*/
              /*���һ�οۿ�����*/
  char   dxtzbz[1+1];              /*����֪ͨ��־*/
              /*����֪ͨ��־ 0֪ͨ 1��֪ͨ*/
  double  zhzded;              /*�˻���Ͷ��*/
              /*�˻���Ͷ��*/
  char   extfld1[40+1];              /*��չ����1*/
              /*��չ����1*/
  char   extfld2[40+1];              /*��չ����2*/
              /*��չ����2*/
  char   extfld3[40+1];              /*��չ����3*/
              /*��չ����3*/
  char   extfld4[40+1];              /*��չ����4*/
              /*��չ����4*/
  char   extfld5[40+1];              /*��չ����5*/
              /*��չ����5*/
  char   extfld6[254+1];              /*��չ����6*/
              /*��չ����6*/
  char   qyzt[1+1];              /*ǩԼ״̬*/
              /*ǩԼ״̬ 0���� 1����*/
}APP_KHCPQY;

#define SD_DATA  APP_KHCPQY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  xybh, 0),\
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  khjg, 0),\
	DEFSDMEMBER(T_STRING,  qyzh, 0),\
	DEFSDMEMBER(T_STRING,  zhhm, 0),\
	DEFSDMEMBER(T_STRING,  dlzjlx, 0),\
	DEFSDMEMBER(T_STRING,  dlzjhm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  qylx, 0),\
	DEFSDMEMBER(T_STRING,  khjl, 0),\
	DEFSDMEMBER(T_STRING,  hyksrq, 0),\
	DEFSDMEMBER(T_STRING,  hyjsrq, 0),\
	DEFSDMEMBER(T_STRING,  ktqd, 0),\
	DEFSDMEMBER(T_STRING,  bljg, 0),\
	DEFSDMEMBER(T_STRING,  blgy, 0),\
	DEFSDMEMBER(T_STRING,  blrq, 0),\
	DEFSDMEMBER(T_STRING,  yhh1, 0),\
	DEFSDMEMBER(T_STRING,  yhh2, 0),\
	DEFSDMEMBER(T_STRING,  yhh3, 0),\
	DEFSDMEMBER(T_STRING,  yhmc, 0),\
	DEFSDMEMBER(T_STRING,  yhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhyb, 0),\
	DEFSDMEMBER(T_STRING,  yhdh, 0),\
	DEFSDMEMBER(T_STRING,  yhdz, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_DOUBLE,  kkzdxe, 2),\
	DEFSDMEMBER(T_STRING,  kkzq, 0),\
	DEFSDMEMBER(T_STRING,  ydkkrq, 0),\
	DEFSDMEMBER(T_STRING,  kkzt, 0),\
	DEFSDMEMBER(T_STRING,  kkrq, 0),\
	DEFSDMEMBER(T_STRING,  dxtzbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  zhzded, 2),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  extfld4, 0),\
	DEFSDMEMBER(T_STRING,  extfld5, 0),\
	DEFSDMEMBER(T_STRING,  extfld6, 0),\
	DEFSDMEMBER(T_STRING,  qyzt, 0)


	DECLAREFIELDS(SD_APP_KHCPQY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_KHCPQY_H__*/

