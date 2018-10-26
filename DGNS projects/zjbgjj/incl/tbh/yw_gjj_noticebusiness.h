/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_noticebusiness.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_noticebusiness (ס����������֪ͨ�����ҵ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_NOTICEBUSINESS_H__
#define __YW_GJJ_NOTICEBUSINESS_H__
typedef struct TDB_YW_GJJ_NOTICEBUSINESS
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��*/
	char   txunitno[15+1];  /*���׻�����*/
		/*���׻�����*/
	char   jylx[1+1];  /*��������*/
		/*�������� 0-֪ͨ���֧ȡ 1-֪ͨ���֧ȡ�趨 2-֪ͨ���֧ȡ֪ͨȡ��*/
	char   currno[3+1];  /*����*/
		/*����*/
	char   curriden[1+1];  /*�������*/
		/*�������*/
	char   fixedacctno[32+1];  /*֪ͨ����˺�*/
		/*֪ͨ����˺�*/
	char   fixedacctname[60+1];  /*֪ͨ�˻�����*/
		/*֪ͨ�˻�����*/
	char   fixedacctopenbank[60+1];  /*֪ͨ�˻�����������*/
		/*֪ͨ�˻�����������*/
	char   noticesetserialno[20+1];  /*֪ͨ�趨���*/
		/*֪ͨ�趨���*/
	char   bookno[50+1];  /*���*/
		/*��� �ʺ�Ϊһ��ͨʱ,����*/
	char   booklistno[50+1];  /*�ʺ�*/
		/*�ʺ� �ʺ�Ϊһ��ͨʱ,����*/
	char   noticeflag[1+1];  /*֪ͨ��־*/
		/*֪ͨ��־0������ 1��֪ͨ�ѹ���*/
	char   noticedrawsetdate[8+1];  /*֪ͨ�趨����*/
		/*֪ͨ�趨����*/
	char   noticedrawdate[8+1];  /*֪֧ͨȡ����*/
		/*֪֧ͨȡ����*/
	double   drawamt;  /*֧ȡ���*/
		/*֧ȡ���*/
	double   balance;  /*�浥���*/
		/*�浥���*/
	double   noticedepositamt;  /*֪ͨ�����*/
		/*֪ͨ�����*/
	char   activedacctno[32+1];  /*�����˺�*/
		/*�����˺�*/
	char   activedacctname[60+1];  /*���ڻ���*/
		/*���ڻ���*/
	char   activedacctopenbank[60+1];  /*�����˻�����������*/
		/*�����˻�����������*/
	char   depositperiod[1+1];  /*����*/
		/*���� 6-1�� 7-7��   */
	char   acctno[32+1];  /*����˺�*/
		/*����˺�*/
	char   drawtype[1+1];  /*֧ȡ��ʽ*/
		/*֧ȡ��ʽ 0����֧ȡ֪֧ͨȡ 1��ֱ��֧ȡ*/
	char   acctname[60+1];  /*����˻�����*/
		/*����˻�����*/
	double   noticedrawamt;  /*֪֧ͨȡ���*/
		/*֪֧ͨȡ���*/
	char   depositbegindate[8+1];  /*��������*/
		/*��������*/
	char   zwrq[8+1];  /*ǰ������*/
		/*ǰ������*/
	char   systime[6+1];  /*ǰ��ʱ��*/
		/*ǰ��ʱ��*/
	char   remark[32+1];  /*����*/
		/*����*/
	char   remark1[64+1];  /*����1*/
		/*����1*/
	char   remark2[128+1];  /*����2*/
		/*����2*/
	char   remark3[254+1];  /*����3*/
		/*����3*/
	char   remark4[254+1];  /*����4*/
		/*����4*/

}YW_GJJ_NOTICEBUSINESS;

#define SD_DATA  YW_GJJ_NOTICEBUSINESS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctno, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctname, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  noticesetserialno, 0),\
	DEFSDMEMBER(T_STRING,  bookno, 0),\
	DEFSDMEMBER(T_STRING,  booklistno, 0),\
	DEFSDMEMBER(T_STRING,  noticeflag, 0),\
	DEFSDMEMBER(T_STRING,  noticedrawsetdate, 0),\
	DEFSDMEMBER(T_STRING,  noticedrawdate, 0),\
	DEFSDMEMBER(T_DOUBLE,  drawamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  balance, 2),\
	DEFSDMEMBER(T_DOUBLE,  noticedepositamt, 2),\
	DEFSDMEMBER(T_STRING,  activedacctno, 0),\
	DEFSDMEMBER(T_STRING,  activedacctname, 0),\
	DEFSDMEMBER(T_STRING,  activedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  depositperiod, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  drawtype, 0),\
	DEFSDMEMBER(T_STRING,  acctname, 0),\
	DEFSDMEMBER(T_DOUBLE,  noticedrawamt, 2),\
	DEFSDMEMBER(T_STRING,  depositbegindate, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_NOTICEBUSINESS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_NOTICEBUSINESS_H__*/
