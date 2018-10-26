/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_dbsfk.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_dbsfk (ס���������𵥱��ո����)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_DBSFK_H__
#define __YW_GJJ_DBSFK_H__
typedef struct TDB_YW_GJJ_DBSFK
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��*/
	char   txunitno[15+1];  /*���׻�����*/
		/*���׻�����*/
	char   sfkbz[1+1];  /*�ո����־*/
		/*�ո����־*/
	char   currno[3+1];  /*����*/
		/*����*/
	char   curriden[1+1];  /*�������*/
		/*�������*/
	char   settletype[1+1];  /*����ģʽ*/
		/*����ģʽ*/
	char   bustype[6+1];  /*ҵ������*/
		/*ҵ������*/
	char   deacctno[32+1];  /*�����˺�*/
		/*�����˺�*/
	char   deacctname[60+1];  /*��������*/
		/*��������*/
	char   deacctclass[1+1];  /*�����˻����*/
		/*�����˻����*/
	char   debankname[60+1];  /*��������*/
		/*��������*/
	char   dechgno[12+1];  /*�������к�*/
		/*�������к�*/
	char   debankclass[1+1];  /*�����˻��б�*/
		/*�����˻��б�*/
	char   conagrno[32+1];  /*�෽Э���*/
		/*�෽Э���*/
	double   capamt;  /*��������*/
		/*��������*/
	char   deintacctno[32+1];  /*��Ϣ���˺�*/
		/*��Ϣ���˺�*/
	char   deintacctname[60+1];  /*��Ϣ������*/
		/*��Ϣ������*/
	char   deintacctclass[1+1];  /*��Ϣ�����*/
		/*��Ϣ�����*/
	char   deintcracct[32+1];  /*��Ϣ�շ��˺�*/
		/*��Ϣ�շ��˺�*/
	double   intamt;  /*��Ϣ������*/
		/*��Ϣ������*/
	char   cracctno[32+1];  /*�շ��˺�*/
		/*�շ��˺�*/
	char   cracctname[60+1];  /*�շ�����*/
		/*�շ�����*/
	char   cracctclass[1+1];  /*�շ��˻����*/
		/*�շ��˻����*/
	char   crbankclass[1+1];  /*�շ��˻��б�*/
		/*�շ��˻��б�*/
	char   crbankname[60+1];  /*�շ�����*/
		/*�շ�����*/
	char   crchgno[12+1];  /*�շ����к�*/
		/*�շ����к�*/
	double   amt;  /*���*/
		/*���*/
	char   refacctno[32+1];  /*ҵ����ϸ�˺�*/
		/*ҵ����ϸ�˺�*/
	char   refseqno1[32+1];  /*ҵ����ϸ��ˮ��1*/
		/*ҵ����ϸ��ˮ��1*/
	char   refseqno2[32+1];  /*ҵ����ϸ��ˮ��2*/
		/*ҵ����ϸ��ˮ��2*/
	char   zwrq[8+1];  /*ǰ������*/
		/*ǰ������*/
	char   systime[6+1];  /*ǰ��ʱ��*/
		/*ǰ��ʱ��*/
	char   remark[32+1];  /*��ע*/
		/*��ע*/
	char   remark1[64+1];  /*����1*/
		/*����1*/
	char   remark2[128+1];  /*��ע2*/
		/*��ע2*/
	char   remark3[254+1];  /*����3*/
		/*����3*/
	char   remark4[254+1];  /*����4*/
		/*����4*/

}YW_GJJ_DBSFK;

#define SD_DATA  YW_GJJ_DBSFK
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  sfkbz, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  settletype, 0),\
	DEFSDMEMBER(T_STRING,  bustype, 0),\
	DEFSDMEMBER(T_STRING,  deacctno, 0),\
	DEFSDMEMBER(T_STRING,  deacctname, 0),\
	DEFSDMEMBER(T_STRING,  deacctclass, 0),\
	DEFSDMEMBER(T_STRING,  debankname, 0),\
	DEFSDMEMBER(T_STRING,  dechgno, 0),\
	DEFSDMEMBER(T_STRING,  debankclass, 0),\
	DEFSDMEMBER(T_STRING,  conagrno, 0),\
	DEFSDMEMBER(T_DOUBLE,  capamt, 2),\
	DEFSDMEMBER(T_STRING,  deintacctno, 0),\
	DEFSDMEMBER(T_STRING,  deintacctname, 0),\
	DEFSDMEMBER(T_STRING,  deintacctclass, 0),\
	DEFSDMEMBER(T_STRING,  deintcracct, 0),\
	DEFSDMEMBER(T_DOUBLE,  intamt, 2),\
	DEFSDMEMBER(T_STRING,  cracctno, 0),\
	DEFSDMEMBER(T_STRING,  cracctname, 0),\
	DEFSDMEMBER(T_STRING,  cracctclass, 0),\
	DEFSDMEMBER(T_STRING,  crbankclass, 0),\
	DEFSDMEMBER(T_STRING,  crbankname, 0),\
	DEFSDMEMBER(T_STRING,  crchgno, 0),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_STRING,  refacctno, 0),\
	DEFSDMEMBER(T_STRING,  refseqno1, 0),\
	DEFSDMEMBER(T_STRING,  refseqno2, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_DBSFK)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_DBSFK_H__*/
