/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_crcapintmx.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_crcapintmx (ס������������Ϣ�ֽ���ϸ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_CRCAPINTMX_H__
#define __YW_GJJ_CRCAPINTMX_H__
typedef struct TDB_YW_GJJ_CRCAPINTMX
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
	char   mxacctno[32+1];  /*ҵ����ϸ�˺�*/
		/*ҵ����ϸ�˺�*/
	char   mxserialno[32+1];  /*ҵ����ϸ��ˮ��*/
		/*ҵ����ϸ��ˮ��*/
	char   idnumber[18+1];  /*���֤��*/
		/*���֤��*/
	char   contractno[32+1];  /*��ͬ���*/
		/*��ͬ���*/
	char   name[60+1];  /*����*/
		/*����*/
	double   amt;  /*������*/
		/*������*/
	double   capamt;  /*���������*/
		/*���������*/
	double   intamt;  /*������Ϣ������*/
		/*������Ϣ������*/
	double   penamt;  /*���Ϣ������*/
		/*���Ϣ������*/
	double   fineamt;  /*����ΥԼ������*/
		/*����ΥԼ������*/
	double   bkamt;  /*�ǿۿ�����*/
		/*�ǿۿ�����*/
	double   refcapamt;  /*�ǿۿ���������*/
		/*�ǿۿ���������*/
	double   refintamt;  /*�ǿۿ������Ϣ������*/
		/*�ǿۿ������Ϣ������*/
	double   refineamt;  /*�ǿۿ����ΥԼ������*/
		/*�ǿۿ����ΥԼ������*/
	double   repenamt;  /*�ǿۿ���Ϣ������*/
		/*�ǿۿ���Ϣ������*/
	char   summary[60+1];  /*ժҪ*/
		/*ժҪ*/
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

}YW_GJJ_CRCAPINTMX;

#define SD_DATA  YW_GJJ_CRCAPINTMX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  seqno, 0),\
	DEFSDMEMBER(T_STRING,  batchno, 0),\
	DEFSDMEMBER(T_STRING,  fileno, 0),\
	DEFSDMEMBER(T_STRING,  mxacctno, 0),\
	DEFSDMEMBER(T_STRING,  mxserialno, 0),\
	DEFSDMEMBER(T_STRING,  idnumber, 0),\
	DEFSDMEMBER(T_STRING,  contractno, 0),\
	DEFSDMEMBER(T_STRING,  name, 0),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_DOUBLE,  capamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  intamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  penamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  fineamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  bkamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refcapamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refintamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refineamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  repenamt, 2),\
	DEFSDMEMBER(T_STRING,  summary, 0),\
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


	DECLAREFIELDS(SD_YW_GJJ_CRCAPINTMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CRCAPINTMX_H__*/
