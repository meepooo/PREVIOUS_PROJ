/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_DZJGXX.eh
�ļ�����:tips_DZJGXX;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2014-9-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_DZJGXX (���˽���Ǽ�)
˵    ��:���˽���Ǽ�
���ڵǼǶ��ʽ����Ϣ
����������
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_DZJGXX_EH__
#define __TIPS_DZJGXX_EH__

typedef struct TDB_TIPS_DZJGXX
{
	char dzrq[8+1];
	char dzxt[1+1];
	char chkacctord[4+1];
	int  allnum1;
	double allamt1;
	int    Allnum2;
	double Allamt2;
	char dzjg[1+1];
	char byzd[60+1];
}SDB_TIPS_DZJGXX;

#define SD_DATA SDB_TIPS_DZJGXX
#define	SD_MEMBERS\
	DEFSDMEMBER(T_STRING,dzrq,0),\
	DEFSDMEMBER(T_STRING,dzxt,0),\
	DEFSDMEMBER(T_STRING,chkacctord,0),\
	DEFSDMEMBER(T_LONG,allnum1,0),\
	DEFSDMEMBER(T_DOUBLE,allamt1,2),\
	DEFSDMEMBER(T_LONG,Allnum2,0),\
	DEFSDMEMBER(T_DOUBLE,Allamt2,2),\
	DEFSDMEMBER(T_STRING,dzjg,0),\
	DEFSDMEMBER(T_STRING,byzd,0)

	DECLAREFIELDS(SD_TIPS_DZJGXX)

#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_DZJGXX_EH__*/
