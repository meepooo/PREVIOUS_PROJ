/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_struct_report.eh
�ļ�����:tips_struct_report;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-12-16 13:47:16 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_struct_report (����ṹ��)
˵    ��:�˱��Ǳ����ǽṹ�壬Ϊ����ͨ��PD����ͷ�ļ������ӵ�"��",���ڳ�������,SYW_TIPS_REPORT.ec
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_STRUCT_REPORT_EH__
#define __TIPS_STRUCT_REPORT_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_STRUCT_REPORT
{
  char   zwrq[8+1];              /*��������*/
              /**/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /**/
  char   payacct[32+1];              /*�����˺�*/
              /**/
  char   handorgname[200+1];              /*�ɿλ����*/
              /**/
  double  jyje;              /*���׽��*/
              /**/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /**/
  char   taxvouno[18+1];              /*˰Ʊ����*/
              /**/
  char   jyzt[1+1];              /*����״̬*/
              /**/
  char   chkdate[8+1];              /*��������*/
              /**/
  char   chkacctord[4+1];              /*�������κ�*/
              /**/
  char   jygy[16+1];              /*���׹�Ա*/
              /**/
  char   xyxx[60+1];              /*��Ӧ��Ϣ*/
              /**/
  char   protocolno[60+1];              /*Э�����*/
              /**/
}SDB_TIPS_STRUCT_REPORT;

#define SD_DATA SDB_TIPS_STRUCT_REPORT
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,handorgname,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,taxvouno,0),\
  DEFSDMEMBER(T_STRING,jyzt,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,protocolno,0)
	DECLAREFIELDS(SD_TIPS_STRUCT_REPORT)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_STRUCT_REPORT_EH__*/
