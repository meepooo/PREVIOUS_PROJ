/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_sendserial.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_sendserial (ס����������������ˮ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_SENDSERIAL_H__
#define __YW_GJJ_SENDSERIAL_H__
typedef struct TDB_YW_GJJ_SENDSERIAL
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��-������ˮ��*/
	char   sendnode[6+1];  /*���ͷ��ڵ��*/
		/*���ͷ��ڵ��-�μ����д����*/
	char   senddate[8+1];  /*���ͷ�����*/
		/*���ͷ�����*/
	char   sendtime[6+1];  /*���ͷ�ʱ��*/
		/*���ͷ�ʱ��*/
	char   transcode[7+1];  /*������*/
		/*������*/
	char   receivenode[6+1];  /*���շ��ڵ��*/
		/*���շ��ڵ��-�μ����������Ĵ����*/
	char   receivedate[8+1];  /*���շ�����*/
		/*���շ�����*/
	char   receivetime[6+1];  /*���շ�ʱ��*/
		/*���շ�ʱ��*/
	char   receiveseqno[32+1];  /*���շ���ˮ��*/
		/*���շ���ˮ��-����Ӧ��ϵͳ������ˮ��*/
	char   jbjg[16+1];  /*���о������*/
		/*�������*/
	char   jbgy[16+1];  /*���о����Ա*/
		/*�����Ա*/
	char   txstatus[1+1];  /*����״̬*/
		/*0���ɹ� 1��ʧ�� 9����ʼ */
	char   qzlsh[10+1];  /*ǰ����ˮ��*/
		/*ǰ����ˮ��*/
	char   qqdzt[2+1];  /*����״̬*/
		/*20-��ʼ,41-����ʧ��,43-������ʱ,99-�ѷ���*/
	char   respcode[8+1];  /*������*/
		/**/
	char   respmsg[254+1];  /*����ԭ��*/
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

}YW_GJJ_SENDSERIAL;

#define SD_DATA  YW_GJJ_SENDSERIAL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  sendnode, 0),\
	DEFSDMEMBER(T_STRING,  senddate, 0),\
	DEFSDMEMBER(T_STRING,  sendtime, 0),\
	DEFSDMEMBER(T_STRING,  transcode, 0),\
	DEFSDMEMBER(T_STRING,  receivenode, 0),\
	DEFSDMEMBER(T_STRING,  receivedate, 0),\
	DEFSDMEMBER(T_STRING,  receivetime, 0),\
	DEFSDMEMBER(T_STRING,  receiveseqno, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  txstatus, 0),\
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


	DECLAREFIELDS(SD_YW_GJJ_SENDSERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_SENDSERIAL_H__*/
