/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_fixedbusiness.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_fixedbusiness (ס������������ҵ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_FIXEDBUSINESS_H__
#define __YW_GJJ_FIXEDBUSINESS_H__
typedef struct TDB_YW_GJJ_FIXEDBUSINESS
{
	char   sendseqno[32+1];  /*���ͷ���ˮ��*/
		/*���ͷ���ˮ��*/
	char   txunitno[15+1];  /*���׻�����*/
		/*���׻�����*/
	char   jylx[1+1];  /*��������*/
		/*�������� 0-����ת���� 1-����֧ȡ 2-����ת�淽ʽ�趨*/
	char   currno[3+1];  /*����*/
		/*����*/
	char   curriden[1+1];  /*�������*/
		/*�������*/
	char   activedacctno[32+1];  /*�����˺�*/
		/*�����˺�*/
	char   activedacctname[60+1];  /*���ڻ���*/
		/*���ڻ���*/
	char   activedacctopenbank[60+1];  /*�����˻�����������*/
		/*�����˻�����������*/
	char   fixedacctno[32+1];  /*�����˺�*/
		/*�����˺�*/
	char   fixedacctname[60+1];  /*���ڻ���*/
		/*���ڻ���*/
	char   fixedacctopenbank[60+1];  /*�����˻�����������*/
		/*�����˻�����������*/
	char   depositperiod[1+1];  /*����*/
		/*���� 0�������� 1������ 2��һ�� 3������ 4������ 5������  */
	double   interestrate;  /*����*/
		/*���й�������*/
	double   amt;  /*���׽��*/
		/*���׽��*/
	char   extenddeposittype[1+1];  /*ת�淽ʽ*/
		/*ת�淽ʽ 0������+��Ϣ�Զ�ת��  1�����Զ�ת��  2�������Զ�ת��  */
	char   partexdeacctno[32+1];  /*��Ϣת��ת���˺�*/
		/*��������*/
	char   beiz[254+1];  /*˵��*/
		/*��Ϣ���˺�*/
	char   bookno[50+1];  /*���*/
		/*��� �ʺ�Ϊһ��ͨʱ,����*/
	char   booklistno[50+1];  /*�ʺ�*/
		/*�ʺ� �ʺ�Ϊһ��ͨʱ,����*/
	char   depositbegindate[8+1];  /*��������*/
		/*��������*/
	char   depositenddate[8+1];  /*��������*/
		/*��������*/
	double   depostiamt;  /*ʵ�ʽ��*/
		/*ʵ�ʽ��*/
	double   drawamt;  /*֧ȡ���*/
		/*֧ȡ���*/
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

}YW_GJJ_FIXEDBUSINESS;

#define SD_DATA  YW_GJJ_FIXEDBUSINESS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  activedacctno, 0),\
	DEFSDMEMBER(T_STRING,  activedacctname, 0),\
	DEFSDMEMBER(T_STRING,  activedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctno, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctname, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  depositperiod, 0),\
	DEFSDMEMBER(T_DOUBLE,  interestrate, 5),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_STRING,  extenddeposittype, 0),\
	DEFSDMEMBER(T_STRING,  partexdeacctno, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  bookno, 0),\
	DEFSDMEMBER(T_STRING,  booklistno, 0),\
	DEFSDMEMBER(T_STRING,  depositbegindate, 0),\
	DEFSDMEMBER(T_STRING,  depositenddate, 0),\
	DEFSDMEMBER(T_DOUBLE,  depostiamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  drawamt, 2),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_FIXEDBUSINESS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_FIXEDBUSINESS_H__*/
