/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_accserial.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_accserial (ס�����������˻��䶯֪ͨ��ϸ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_ACCSERIAL_H__
#define __YW_GJJ_ACCSERIAL_H__
typedef struct TDB_YW_GJJ_ACCSERIAL
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/**/
	char   sendnode[6+1];  /*���ͷ��ڵ��*/
		/**/
	char   acctno[32+1];  /*�˺�*/
		/*�˺�*/
	char   seqno[20+1];  /*���*/
		/*���*/
	char   hostseq[32+1];  /*����������ˮ��*/
		/*����������ˮ��*/
	char   jydm[6+1];  /*���״���*/
		/*���״���*/
	char   rivalacctno[32+1];  /*���׶����˺�*/
		/*���׶����˺�*/
	char   rivalacctname[60+1];  /*���׶��ֻ���*/
		/*���׶��ֻ���*/
	double   amt;  /*���*/
		/*���*/
	char   trandate[8+1];  /*��������*/
		/*��������*/
	char   trantime[6+1];  /*����ʱ��*/
		/*����ʱ��*/
	double   availbal;  /*�������*/
		/*�������*/
	char   openbrhno[20+1];  /*����������*/
		/*����������*/
	char   beiz[254+1];  /*˵��*/
		/*˵��*/
	char   currno[3+1];  /*����*/
		/*����156*/
	char   curriden[1+1];  /*�����־*/
		/*�����־1���� 2����*/
	double   bal;  /*���*/
		/*�˻����*/
	double   overamt;  /*��͸֧���*/
		/*��͸֧���*/
	char   dcmttp[4+1];  /*ƾ֤����*/
		/*ƾ֤����*/
	char   dcmtno[16+1];  /*ƾ֤����*/
		/*ƾ֤����*/
	char   bankno[32+1];  /*���׶����к�*/
		/*���׶����к�*/
	char   desctx[60+1];  /*ժҪ*/
		/*ժҪ*/
	char   transtatus[1+1];  /*������ʶ*/
		/*Y������ N��δ����*/
	char   penno[30+1];  /*�ʺ�*/
		/*����/֪ͨ/һ��ͨ�˻�ʹ�ã����ڱ�ʶ�˺��²�ͬ���*/
	char   copno[30+1];  /*���*/
		/*����/֪ͨ/һ��ͨʹ�ã���ʶ�˺��²�ͬ���*/
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

}YW_GJJ_ACCSERIAL;

#define SD_DATA  YW_GJJ_ACCSERIAL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  sendnode, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  seqno, 0),\
	DEFSDMEMBER(T_STRING,  hostseq, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  rivalacctno, 0),\
	DEFSDMEMBER(T_STRING,  rivalacctname, 0),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_STRING,  trandate, 0),\
	DEFSDMEMBER(T_STRING,  trantime, 0),\
	DEFSDMEMBER(T_DOUBLE,  availbal, 2),\
	DEFSDMEMBER(T_STRING,  openbrhno, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_DOUBLE,  bal, 2),\
	DEFSDMEMBER(T_DOUBLE,  overamt, 2),\
	DEFSDMEMBER(T_STRING,  dcmttp, 0),\
	DEFSDMEMBER(T_STRING,  dcmtno, 0),\
	DEFSDMEMBER(T_STRING,  bankno, 0),\
	DEFSDMEMBER(T_STRING,  desctx, 0),\
	DEFSDMEMBER(T_STRING,  transtatus, 0),\
	DEFSDMEMBER(T_STRING,  penno, 0),\
	DEFSDMEMBER(T_STRING,  copno, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_ACCSERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_ACCSERIAL_H__*/
