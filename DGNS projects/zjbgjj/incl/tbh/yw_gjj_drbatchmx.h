/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_drbatchmx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_drbatchmx (ס���������������ո�����ϸ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_DRBATCHMX_H__
#define __YW_GJJ_DRBATCHMX_H__
typedef struct TDB_YW_GJJ_DRBATCHMX
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��*/
	char   txunitno[15+1];  /*���׻�����*/
		/*���׻�����*/
	char   seqno[20+1];  /*���*/
		/*���*/
	char   batchno[20+1];  /*���κ�*/
		/*���κ�*/
	char   fileno[5+1];  /*�ļ����*/
		/*�ļ����*/
	double   amt;  /*���*/
		/*���*/
	char   acctno[32+1];  /*�˺�*/
		/*�˺�*/
	char   acctname[60+1];  /*����*/
		/*����*/
	char   chgno[12+1];  /*�˻����к�*/
		/*�˻����к�*/
	char   openchgno[12+1];  /*���������к�*/
		/*���������к�*/
	double   drbal;  /*�������*/
		/*�������*/
	double   crbal;  /*�շ����*/
		/*�շ����*/
	char   address[80+1];  /*��ַ*/
		/*��ַ*/
	char   conagrno[32+1];  /*�෽Э���*/
		/*�෽Э���*/
	char   amttype[1+1];  /*����־*/
		/*����־*/
	char   summary[60+1];  /*ժҪ*/
		/*ժҪ*/
	char   mxacctno[32+1];  /*ҵ����ϸ�˺�*/
		/*ҵ����ϸ�˺�*/
	char   mxserialno1[32+1];  /*ҵ����ϸ��ˮ��1*/
		/*ҵ����ϸ��ˮ��1*/
	char   mxserialno2[32+1];  /*ҵ����ϸ��ˮ��2*/
		/*ҵ����ϸ��ˮ��2*/
	double   capamt;  /*��������*/
		/*��������*/
	double   intamt;  /*��Ϣ������*/
		/*��Ϣ������*/
	char   dealstatus[1+1];  /*������*/
		/*������0-��̬��1-�ɹ���2ʧ�ܣ�3��ʱ*/
	char   hostseq[32+1];  /*������ˮ*/
		/*������ˮ*/
	char   hostdate[8+1];  /*��������*/
		/*��������*/
	char   caphostseqno[32+1];  /*����������ˮ��*/
		/*����������ˮ��*/
	char   inthostseqno[32+1];  /*��Ϣ������ˮ��*/
		/*��Ϣ������ˮ��*/
	char   dealcode[5+1];  /*��������*/
		/*��������00000-�ɹ���99999��ʱ������ʧ��*/
	char   dealmsg[160+1];  /*��������Ϣ*/
		/*��������Ϣ*/
	char   hzno[32+1];  /*��ִ���*/
		/*��ִ���*/
	char   bankex[254+1];  /*������չ*/
		/*������չ*/
	char   zwrq[8+1];  /*ǰ������*/
		/*ǰ������*/
	char   systime[6+1];  /*ǰ��ʱ��*/
		/*ǰ��ʱ��*/
	char   remark[32+1];  /*����*/
		/*����*/
	char   remark1[128+1];  /*����1*/
		/*����1*/
	char   remark2[64+1];  /*����2*/
		/*����2*/
	char   remark3[254+1];  /*����3*/
		/*����3*/
	char   remark4[254+1];  /*����4*/
		/*����4*/

}YW_GJJ_DRBATCHMX;

#define SD_DATA  YW_GJJ_DRBATCHMX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  seqno, 0),\
	DEFSDMEMBER(T_STRING,  batchno, 0),\
	DEFSDMEMBER(T_STRING,  fileno, 0),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  acctname, 0),\
	DEFSDMEMBER(T_STRING,  chgno, 0),\
	DEFSDMEMBER(T_STRING,  openchgno, 0),\
	DEFSDMEMBER(T_DOUBLE,  drbal, 2),\
	DEFSDMEMBER(T_DOUBLE,  crbal, 2),\
	DEFSDMEMBER(T_STRING,  address, 0),\
	DEFSDMEMBER(T_STRING,  conagrno, 0),\
	DEFSDMEMBER(T_STRING,  amttype, 0),\
	DEFSDMEMBER(T_STRING,  summary, 0),\
	DEFSDMEMBER(T_STRING,  mxacctno, 0),\
	DEFSDMEMBER(T_STRING,  mxserialno1, 0),\
	DEFSDMEMBER(T_STRING,  mxserialno2, 0),\
	DEFSDMEMBER(T_DOUBLE,  capamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  intamt, 2),\
	DEFSDMEMBER(T_STRING,  dealstatus, 0),\
	DEFSDMEMBER(T_STRING,  hostseq, 0),\
	DEFSDMEMBER(T_STRING,  hostdate, 0),\
	DEFSDMEMBER(T_STRING,  caphostseqno, 0),\
	DEFSDMEMBER(T_STRING,  inthostseqno, 0),\
	DEFSDMEMBER(T_STRING,  dealcode, 0),\
	DEFSDMEMBER(T_STRING,  dealmsg, 0),\
	DEFSDMEMBER(T_STRING,  hzno, 0),\
	DEFSDMEMBER(T_STRING,  bankex, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_DRBATCHMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_DRBATCHMX_H__*/
