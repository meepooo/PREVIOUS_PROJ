/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_crcapint.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_crcapint (ס������������Ϣ�ֽ�����)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_CRCAPINT_H__
#define __YW_GJJ_CRCAPINT_H__
typedef struct TDB_YW_GJJ_CRCAPINT
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��*/
	char   txunitno[15+1];  /*���׻�����*/
		/*���׻�����*/
	char   batchno[20+1];  /*���κ�*/
		/*���κ�*/
	char   fileno[8+1];  /*�ļ����*/
		/*�ļ����*/
	char   oribatchno[20+1];  /*ԭ����ۿ����κ�*/
		/*ԭ����ۿ����κ�*/
	long   batchtotalnum;  /*�ܱ���*/
		/*�����ν����ܱ���*/
	double   batchtotalamt;  /*�ܽ��*/
		/*�����ν����ܽ��*/
	char   beiz[254+1];  /*˵��*/
		/*˵��*/
	double   bkamt;  /*�ۿ�׻������*/
		/*�����пۿ�����*/
	double   refamt;  /*�ǿۿ�׻������*/
		/*����Ҫ���пۿ�򹫻��𻹴����*/
	double   refcapamt;  /*�ǿۿ�״��������*/
		/*�ǿۿ�𻹿��*/
	double   refintamt;  /*�ǿۿ�״�����Ϣ������*/
		/*�ǿۿ���Ϣ�����*/
	double   repenamt;  /*�ǿۿ�״��Ϣ������*/
		/*�ǿۿϢ�����*/
	double   refineamt;  /*�ǿۿ�״���ΥԼ������*/
		/*�ǿۿ�ΥԼ�𻹿��*/
	char   bankacctno[32+1];  /*���пۿ��ʽ��ڲ����ɻ�*/
		/*����ۿ���ʹ�õ��տ������տ��ڲ����ɻ�*/
	char   bkrefloancapno[32+1];  /*����ί�д�����˺�*/
		/*����ί�д�����˺�*/
	char   bkloancapinacctno[32+1];  /*���д�����ڲ����ɻ�*/
		/*����ʹ�õĴ������ɻ�*/
	char   bkloanintinacctno[32+1];  /*���д�����Ϣ�ڲ����ɻ�*/
		/*����ʹ�õĴ�����Ϣ���ɻ�*/
	char   loancapcracctno[32+1];  /*������շ��˺�*/
		/*���������ķ��ô�����˺�*/
	char   loancapcracctname[60+1];  /*������շ�����*/
		/*������˺Ż���*/
	char   loancapcracctclass[1+1];  /*������շ��˻����*/
		/*1����˽ 2���Թ�*/
	char   loancapcracctbkname[60+1];  /*������շ��˻�����*/
		/*������շ��˻�����*/
	double   loancapamt;  /*���пۿ���������*/
		/*���пۿ���������*/
	char   loanintcracctno[32+1];  /*������Ϣ�շ��˺�*/
		/*���������ķ��ô�����Ϣ�˺�*/
	char   loanintcracctname[60+1];  /*������Ϣ�շ�����*/
		/*������Ϣ�շ�����*/
	char   loanintcracctclass[1+1];  /*������Ϣ�շ��˻����*/
		/*1����˽ 2���Թ�*/
	char   loanintcracctbkname[60+1];  /*������Ϣ�շ��˻�����*/
		/*������Ϣ�շ��˻�����*/
	double   loanintamt;  /*���пۿ������Ϣ������*/
		/*���пۿ������Ϣ������*/
	char   loanpencracctno[32+1];  /*���Ϣ�շ��˺�*/
		/*���������ķ��ô��Ϣ�˺�*/
	char   loanpencracctname[60+1];  /*���Ϣ�շ�����*/
		/*���Ϣ�շ�����*/
	char   loanpencracctclass[1+1];  /*���Ϣ�շ��˻����*/
		/*1����˽ 2���Թ�*/
	char   loanpencratbkname[60+1];  /*���Ϣ�շ��˻�����*/
		/*���Ϣ�շ��˻�����*/
	double   loanpenamt;  /*���пۿ���Ϣ������*/
		/*���пۿ���Ϣ������*/
	char   loanfinecracctno[32+1];  /*����ΥԼ���շ��˺�*/
		/*���������ķ��ô���ΥԼ���˺�*/
	char   loanfinecracctname[60+1];  /*����ΥԼ���շ�����*/
		/*����ΥԼ���շ��˻�����*/
	char   loanfinecracctclass[1+1];  /*����ΥԼ���շ��˻����*/
		/*1����˽2���Թ�*/
	char   loanfinecratbkname[60+1];  /*����ΥԼ���շ��˻�����*/
		/*����ΥԼ���շ��˻�����*/
	double   loanfineamt;  /*���пۿ����ΥԼ������*/
		/*���пۿ����ΥԼ�����ʱ��д*/
	long   batchsuccnum;  /*�ɹ�����*/
		/*�ɹ�����*/
	double   batchsuccamt;  /*�ɹ����*/
		/*�ɹ����*/
	long   batchfailnum;  /*ʧ�ܱ���*/
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

}YW_GJJ_CRCAPINT;

#define SD_DATA  YW_GJJ_CRCAPINT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  batchno, 0),\
	DEFSDMEMBER(T_STRING,  fileno, 0),\
	DEFSDMEMBER(T_STRING,  oribatchno, 0),\
	DEFSDMEMBER(T_LONG,  batchtotalnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchtotalamt, 2),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_DOUBLE,  bkamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refcapamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refintamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  repenamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refineamt, 2),\
	DEFSDMEMBER(T_STRING,  bankacctno, 0),\
	DEFSDMEMBER(T_STRING,  bkrefloancapno, 0),\
	DEFSDMEMBER(T_STRING,  bkloancapinacctno, 0),\
	DEFSDMEMBER(T_STRING,  bkloanintinacctno, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctno, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctname, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loancapamt, 2),\
	DEFSDMEMBER(T_STRING,  loanintcracctno, 0),\
	DEFSDMEMBER(T_STRING,  loanintcracctname, 0),\
	DEFSDMEMBER(T_STRING,  loanintcracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loanintcracctbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loanintamt, 2),\
	DEFSDMEMBER(T_STRING,  loanpencracctno, 0),\
	DEFSDMEMBER(T_STRING,  loanpencracctname, 0),\
	DEFSDMEMBER(T_STRING,  loanpencracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loanpencratbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loanpenamt, 2),\
	DEFSDMEMBER(T_STRING,  loanfinecracctno, 0),\
	DEFSDMEMBER(T_STRING,  loanfinecracctname, 0),\
	DEFSDMEMBER(T_STRING,  loanfinecracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loanfinecratbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loanfineamt, 2),\
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


	DECLAREFIELDS(SD_YW_GJJ_CRCAPINT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CRCAPINT_H__*/
