/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:yw_gjj_custqy.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[����ǿ]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:yw_gjj_custqy (ס���������������˻�ǩԼ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __YW_GJJ_CUSTQY_H__
#define __YW_GJJ_CUSTQY_H__
typedef struct TDB_YW_GJJ_CUSTQY
{
	char   receivenode[6+1];  /*���������Ľڵ��*/
		/**/
	char   acctno[32+1];  /*�˺�*/
		/**/
	char   custno[32+1];  /*�ͻ����*/
		/**/
	char   acctname[60+1];  /*�˻�����*/
		/**/
	char   opbrhno[20+1];  /*����������*/
		/**/
	char   opbrhname[80+1];  /*����������*/
		/**/
	char   acctnature[1+1];  /*�˻�����*/
		/*1-����2-����3-һ��ͨ*/
	char   accttype[1+1];  /*�˻�����*/
		/*1-�鼯��2-���㻧3-��ֵ���滧4-�����ר��5-������Ϣר��6-���Ϣר��7-����ΥԼ��ר��*/
	char   acctkind[1+1];  /*�˻����*/
		/*2-�Թ�1-��˽*/
	char   acctstatus[1+1];  /*�˻�״̬*/
		/*0-ע�� 1-����*/
	char   trantype[1+1];  /*ǩԼת�˷�ʽ*/
		/*1-ͬ��2-ʵʱ�����У�3-��ʵʱ�����У�*/
	char   bankacctno[32+1];  /*���пۿ��ʽ��ڲ����ɻ�*/
		/**/
	char   bkrefloancapno[32+1];  /*����ί�д�����˺�*/
		/**/
	char   dkbjacctno[32+1];  /*���д�����ڲ����ɻ�*/
		/**/
	char   dklxacctno[32+1];  /*���д�����Ϣ�ڲ����ɻ�*/
		/**/
	char   qystatus[1+1];  /*ǩԼ״̬*/
		/*0-ǩԼ��1-��Լ*/
	char   qydate[8+1];  /*ǩԼ����*/
		/**/
	char   sendflag[1+1];  /*���ͱ�־*/
		/*0-δ���ͣ�1-������*/
	char   remark[32+1];  /*��ע*/
		/**/
	char   remark1[64+1];  /*��ע1*/
		/**/
	char   remark2[128+1];  /*��ע2*/
		/**/
	char   remark3[254+1];  /*��ע3*/
		/**/
	char   remark4[254+1];  /*��ע4*/
		/**/

}YW_GJJ_CUSTQY;

#define SD_DATA  YW_GJJ_CUSTQY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  receivenode, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  custno, 0),\
	DEFSDMEMBER(T_STRING,  acctname, 0),\
	DEFSDMEMBER(T_STRING,  opbrhno, 0),\
	DEFSDMEMBER(T_STRING,  opbrhname, 0),\
	DEFSDMEMBER(T_STRING,  acctnature, 0),\
	DEFSDMEMBER(T_STRING,  accttype, 0),\
	DEFSDMEMBER(T_STRING,  acctkind, 0),\
	DEFSDMEMBER(T_STRING,  acctstatus, 0),\
	DEFSDMEMBER(T_STRING,  trantype, 0),\
	DEFSDMEMBER(T_STRING,  bankacctno, 0),\
	DEFSDMEMBER(T_STRING,  bkrefloancapno, 0),\
	DEFSDMEMBER(T_STRING,  dkbjacctno, 0),\
	DEFSDMEMBER(T_STRING,  dklxacctno, 0),\
	DEFSDMEMBER(T_STRING,  qystatus, 0),\
	DEFSDMEMBER(T_STRING,  qydate, 0),\
	DEFSDMEMBER(T_STRING,  sendflag, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_CUSTQY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CUSTQY_H__*/
