/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_drbatch.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_drbatch (ס���������������ո�������)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_DRBATCH_H__
#define __YW_GJJ_DRBATCH_H__
typedef struct TDB_YW_GJJ_DRBATCH
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��*/
	char   txunitno[15+1];  /*���׻�����*/
		/*���׻�����*/
	char   sfkbz[1+1];  /*�ո����־*/
		/*�ո����־0-�տ�,1-����,2-�ۿ�*/
	char   batchno[20+1];  /*���κ�*/
		/*���κ�*/
	char   fileno[8+1];  /*�ļ����*/
		/*�ļ����*/
	char   currno[3+1];  /*����*/
		/*����*/
	char   curriden[1+1];  /*�������*/
		/*�������*/
	char   filetype[1+1];  /*�ļ�����*/
		/*�ļ�����*/
	char   bustype[6+1];  /*ҵ������*/
		/*ҵ������*/
	char   batchprjno[32+1];  /*������Ŀ���*/
		/*������Ŀ���*/
	char   acctno[32+1];  /*�˺�*/
		/*�˺�*/
	char   acctname[60+1];  /*����*/
		/*����*/
	char   acctclass[1+1];  /*�˻����*/
		/*�˻����*/
	double   batchcapamt;  /*�������*/
		/*�������*/
	char   deintacctno[32+1];  /*������Ϣ���˺�*/
		/*������Ϣ���˺�*/
	char   deintacctname[60+1];  /*������Ϣ������*/
		/*������Ϣ������*/
	char   deintacctclass[1+1];  /*������Ϣ�����*/
		/*������Ϣ�����*/
	char   deintcracct[32+1];  /*��Ϣ�շ��˺�*/
		/*��Ϣ�շ��˺�*/
	double   batchintamt;  /*������Ϣ���*/
		/*������Ϣ���*/
	char   bankacctno[32+1];  /*�����ڲ����ɻ�*/
		/*�����ڲ����ɻ�*/
	int   batchtotalnum;  /*�ܱ���*/
		/*�ܱ���*/
	double   batchtotalamt;  /*�ܽ��*/
		/*�ܽ��*/
	int   batchsuccnum;  /*�ɹ�����*/
		/*�ɹ�����*/
	double   batchsuccamt;  /*�ɹ����*/
		/*�ɹ����*/
	int   batchfailnum;  /*ʧ�ܱ���*/
		/*ʧ�ܱ���*/
	double   batchfailamt;  /*ʧ�ܽ��*/
		/*ʧ�ܽ��*/
	char   zipfilename[128+1];  /*�����ļ���*/
		/*�����ļ���*/
	char   unzipfilename[128+1];  /*�����ļ���*/
		/*�����ļ���*/
	char   trantype[1+1];  /*�������*/
		/*������� a�����ڴ��� b�����ڴ��� c�����д��� d: ���д��� e: ��ϴ��� f: ��ϴ��� g: ����*/
	char   dealtype[1+1];  /*��������*/
		/*��������1:�ļ� 2:��� 3:��֧��*/
	char   dealstep[1+1];  /*������*/
		/*������0-��̬��1-���ף�2-�����У�3-�������*/
	char   dealstatus[5+1];  /*����״̬*/
		/*0-��̬��1-�ɹ���2-ʧ��*/
	char   dealinf[160+1];  /*����������*/
		/*����������*/
	char   batchpch[64+1];  /*���Ĵ������κ�*/
		/*���Ĵ������κ�*/
	char   querystatus[1+1];  /*�����ѯ״̬*/
		/*�����ѯ״̬0-δ��ѯ��1-�Ѳ�ѯ��2-��ѯʧ��*/
	char   zwrq[8+1];  /*ǰ������*/
		/*ǰ������*/
	char   systime[6+1];  /*ǰ��ʱ��*/
		/*ǰ��ʱ��*/
	char   remark[32+1];  /*��ע*/
		/*��ע*/
	char   remark1[64+1];  /*��ע1*/
		/*��ע1*/
	char   remark2[128+1];  /*��ע2*/
		/*��ע2*/
	char   remark3[254+1];  /*��ע3*/
		/*��ע3*/
	char   remark4[254+1];  /*��ע4*/
		/*��ע4*/

}YW_GJJ_DRBATCH;

#define SD_DATA  YW_GJJ_DRBATCH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  sfkbz, 0),\
	DEFSDMEMBER(T_STRING,  batchno, 0),\
	DEFSDMEMBER(T_STRING,  fileno, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  filetype, 0),\
	DEFSDMEMBER(T_STRING,  bustype, 0),\
	DEFSDMEMBER(T_STRING,  batchprjno, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  acctname, 0),\
	DEFSDMEMBER(T_STRING,  acctclass, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchcapamt, 2),\
	DEFSDMEMBER(T_STRING,  deintacctno, 0),\
	DEFSDMEMBER(T_STRING,  deintacctname, 0),\
	DEFSDMEMBER(T_STRING,  deintacctclass, 0),\
	DEFSDMEMBER(T_STRING,  deintcracct, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchintamt, 2),\
	DEFSDMEMBER(T_STRING,  bankacctno, 0),\
	DEFSDMEMBER(T_LONG,  batchtotalnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchtotalamt, 2),\
	DEFSDMEMBER(T_LONG,  batchsuccnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchsuccamt, 2),\
	DEFSDMEMBER(T_LONG,  batchfailnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchfailamt, 2),\
	DEFSDMEMBER(T_STRING,  zipfilename, 0),\
	DEFSDMEMBER(T_STRING,  unzipfilename, 0),\
	DEFSDMEMBER(T_STRING,  trantype, 0),\
	DEFSDMEMBER(T_STRING,  dealtype, 0),\
	DEFSDMEMBER(T_STRING,  dealstep, 0),\
	DEFSDMEMBER(T_STRING,  dealstatus, 0),\
	DEFSDMEMBER(T_STRING,  dealinf, 0),\
	DEFSDMEMBER(T_STRING,  batchpch, 0),\
	DEFSDMEMBER(T_STRING,  querystatus, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_DRBATCH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_DRBATCH_H__*/
