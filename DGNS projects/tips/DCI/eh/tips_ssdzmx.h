/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_ssdzmx.eh
�ļ�����:tips_ssdzmx;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_ssdzmx (˰�ն�����ϸ)
˵    ��:TIPS�ռ�����ն��˵ǼǱ�--������ϸ��Ϣ��
************************************************************************
�޸ļ�¼:
�޸�����:2014-11-05
�޸�����:
�޸�����:DCI�����޸�ͷ�ļ�
�� �� ��:chenxm
************************************************************************/
#ifndef __TIPS_SSDZMX_EH__
#define __TIPS_SSDZMX_EH__

typedef struct TDB_TIPS_SSDZMX
{
  char   zwrq[8+1];              /*��������*/
              /*ǰ�û���������*/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /*ǰ�û��ۺ�ǰ����ˮ��*/
  char   workdate[8+1];              /*��������*/
              /*tips��������*/
  char   chkdate[8+1];              /*��������*/
              /*ԭ����ˮ��
                */
  char   chkacctord[4+1];              /*��������*/
              /*��������*/
  char   paybkcode[12+1];              /*�������к�*/
              /**/
  char   payeebankno[12+1];              /*�տ����к�*/
              /**/
  int    curpackno;              /*�������*/
              /*�������ʱΪ��ǰ������ţ�δ���ʱ�������Ϊ1*/
  char   payopbkcode[12+1];              /*��������к�*/
              /*��˰�˿�����*/
  char   payacct[32+1];              /*�����˻�*/
              /*������ί�нɿ�Э���顱����˰�˵Ľɿ�˺�,���ж˽ɿ�ҵ���п���Ϊ��*/
  char   handorgname[200+1];              /*�ɿλ����*/
              /*�ɿλ����*/
  char   oritaxorgcode[12+1];              /*ԭ���ջ��ش���*/
              /*���������ջ��ش��룬 ����������ݸ���֪ͨ�����е����ջ��ش��룬TIPS��д��*/
  char   orientrustdate[8+1];              /*ԭί������*/
              /*�����ջ��ش��롢������ˮ��һ��Ψһ��ʶһ�ʽ��ף�TIPS��д*/
  char   oripackno[8+1];              /*ԭ����ˮ��*/
              /*����������������ˮ�ţ�ֻ�ڰ���ϸ�˶�ʱʹ�á�*/
  char   oritrano[8+1];              /*ԭ������ˮ��*/
              /*�ο�������ˮ��*/
  double  traamt;              /*���׽��*/
              /*���ʿۿ���ܽ��*/
  char   taxvouno[18+1];              /*˰Ʊ����*/
              /**/
  char   taxpayname[200+1];              /*��˰������*/
              /**/
  char   protocolno[60+1];              /*Э�����*/
              /**/
}SDB_TIPS_SSDZMX;

#define SD_DATA SDB_TIPS_SSDZMX
#define	SD_MEMBERS\
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_LONG,zhqzlsh,0),\
	DEFSDMEMBER(T_STRING,workdate,0),\
	DEFSDMEMBER(T_STRING,chkdate,0),\
	DEFSDMEMBER(T_STRING,chkacctord,0),\
	DEFSDMEMBER(T_STRING,paybkcode,0),\
	DEFSDMEMBER(T_STRING,payeebankno,0),\
	DEFSDMEMBER(T_LONG,curpackno,0),\
	DEFSDMEMBER(T_STRING,payopbkcode,0),\
	DEFSDMEMBER(T_STRING,payacct,0),\
	DEFSDMEMBER(T_STRING,handorgname,0),\
	DEFSDMEMBER(T_STRING,oritaxorgcode,0),\
	DEFSDMEMBER(T_STRING,orientrustdate,0),\
	DEFSDMEMBER(T_STRING,oripackno,0),\
	DEFSDMEMBER(T_STRING,oritrano,0),\
	DEFSDMEMBER(T_DOUBLE,traamt,2),\
	DEFSDMEMBER(T_STRING,taxvouno,0),\
	DEFSDMEMBER(T_STRING,taxpayname,0),\
	DEFSDMEMBER(T_STRING,protocolno,0)


	DECLAREFIELDS(SD_TIPS_SSDZMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_SSDZMX_EH__*/
