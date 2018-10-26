/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_trans.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_trans (ס��������������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_TRANS_H__
#define __YW_GJJ_TRANS_H__
typedef struct TDB_YW_GJJ_TRANS
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��*/
	char   txunitno[15+1];  /*���׻�����*/
		/*���׻�����*/
	char   sendnode[6+1];  /*���Ĵ���*/
		/*���Ĵ���*/
	char   senddate[8+1];  /*���ͷ�����*/
		/*���ͷ�����*/
	char   sendtime[6+1];  /*���ͷ�ʱ��*/
		/**/
	char   transcode[7+1];  /*������*/
		/*������*/
	char   receivenode[6+1];  /*���շ��ڵ��*/
		/**/
	char   bdcdate[8+1];  /*�ɼ�ϵͳ����*/
		/*�ɼ�ϵͳ����*/
	char   bdctime[6+1];  /*����Ӧ��ϵͳʱ��*/
		/*����Ӧ��ϵͳʱ��*/
	char   bdcseqno[32+1];  /*����Ӧ��ϵͳ��ˮ��*/
		/*�ɼ�ϵͳ��ˮ��*/
	char   custno[32+1];  /*���пͻ����*/
		/*���пͻ����*/
	char   operno[21+1];  /*���Ͳ���Ա*/
		/*���Ͳ���Ա*/
	int   beginrec;  /*��ʼ��¼��*/
		/*��ʼ��¼��*/
	int   maxrec;  /*һ�β�ѯ����¼��*/
		/*һ�β�ѯ����¼��*/
	char   clrq[8+1];  /*��������*/
		/*��������*/
	char   clsj[6+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   jbjg[16+1];  /*���о������*/
		/*�������*/
	char   jbgy[16+1];  /*���о����Ա*/
		/*�����Ա*/
	char   ywlsh[32+1];  /*ҵ����ˮ��*/
		/*ҵ����ˮ��*/
	char   hoststatus[1+1];  /*������������״̬*/
		/*������������״̬0-�ɹ� 1-ʧ�� 3-��ʱ 9-��ʼ*/
	char   hostseqno[32+1];  /*����������ˮ��*/
		/*����������ˮ��*/
	char   hostmsg[160+1];  /*����������Ӧ��Ϣ*/
		/*����������Ӧ��Ϣ*/
	char   hostrespcode[20+1];  /*����������Ӧ��*/
		/*����������Ӧ��*/
	char   zjrq[8+1];  /*��������*/
		/*��������*/
	char   zjsj[6+1];  /*����ʱ��*/
		/*����ʱ��*/
	int   tjhxcs;  /*�ύ���Ĵ���*/
		/*�ύ���Ĵ���*/
	char   caphostseqno[32+1];  /*��������������ˮ��*/
		/*��������������ˮ��*/
	char   inthostseqno[32+1];  /*��Ϣ����������ˮ��*/
		/*��Ϣ����������ˮ��*/
	char   penhostseqno[32+1];  /*���Ϣ����������ˮ��*/
		/*���Ϣ����������ˮ��*/
	char   finehostseqno[32+1];  /*����ΥԼ��������ˮ��*/
		/*����ΥԼ��������ˮ��*/
	char   summary[60+1];  /*ժҪ*/
		/*ժҪ*/
	char   batch[20+1];  /*�����������*/
		/*�����������*/
	char   transdate[8+1];  /*��������*/
		/*��������*/
	char   transtime[8+1];  /*����ʱ��*/
		/*����ʱ��*/
	char   qzlsh[10+1];  /*ǰ����ˮ��*/
		/*ǰ����ˮ��*/
	char   qqdzt[2+1];  /*����״̬*/
		/*11-���ʧ��,20-����ش�����,21-�ύʧ��,23-�ύ��ʱ,30-���ύ�����,31-���ʧ��,33-��س�ʱ,40-�Ѵ��������,41-����ʧ��,43-������ʱ,99-�ѷ���*/
	char   respcode[8+1];  /*������*/
		/**/
	char   respmsg[100+1];  /*����ԭ��*/
		/**/
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

}YW_GJJ_TRANS;

#define SD_DATA  YW_GJJ_TRANS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  sendnode, 0),\
	DEFSDMEMBER(T_STRING,  senddate, 0),\
	DEFSDMEMBER(T_STRING,  sendtime, 0),\
	DEFSDMEMBER(T_STRING,  transcode, 0),\
	DEFSDMEMBER(T_STRING,  receivenode, 0),\
	DEFSDMEMBER(T_STRING,  bdcdate, 0),\
	DEFSDMEMBER(T_STRING,  bdctime, 0),\
	DEFSDMEMBER(T_STRING,  bdcseqno, 0),\
	DEFSDMEMBER(T_STRING,  custno, 0),\
	DEFSDMEMBER(T_STRING,  operno, 0),\
	DEFSDMEMBER(T_LONG,  beginrec, 0),\
	DEFSDMEMBER(T_LONG,  maxrec, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  hoststatus, 0),\
	DEFSDMEMBER(T_STRING,  hostseqno, 0),\
	DEFSDMEMBER(T_STRING,  hostmsg, 0),\
	DEFSDMEMBER(T_STRING,  hostrespcode, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjsj, 0),\
	DEFSDMEMBER(T_LONG,  tjhxcs, 0),\
	DEFSDMEMBER(T_STRING,  caphostseqno, 0),\
	DEFSDMEMBER(T_STRING,  inthostseqno, 0),\
	DEFSDMEMBER(T_STRING,  penhostseqno, 0),\
	DEFSDMEMBER(T_STRING,  finehostseqno, 0),\
	DEFSDMEMBER(T_STRING,  summary, 0),\
	DEFSDMEMBER(T_STRING,  batch, 0),\
	DEFSDMEMBER(T_STRING,  transdate, 0),\
	DEFSDMEMBER(T_STRING,  transtime, 0),\
	DEFSDMEMBER(T_STRING,  qzlsh, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_TRANS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_TRANS_H__*/
