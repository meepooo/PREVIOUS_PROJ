/***********************************************************************
  ��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
  ��Ŀ����:TIPSר��ǰ�ò�Ʒ
  ��    ��:V3.0
  ����ϵͳ:AIX SCO LINUX SunOS HP-UX
  �� �� ��:INFORMIX
  �� �� ��:tips_drls.eh
  �ļ�����:tips_drls;�ṹ�������ݿ⿪��ǶCͷ�ļ�
  �� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
  �� �� Ա:
  ����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
  ��    ��:
  �޸�ʱ��:
 ************************************************************************
 ��    ��:tips_drls (������ˮ��)
 ˵    ��:
 ************************************************************************
 �޸ļ�¼:
 �޸�����:20091112
 �޸�����:�ڸ������˺�(payacct)ǰ����Э�����(protocolno)
 �޸�����:
 �� �� ��:tuql
 ************************************************************************/
#ifndef __TIPS_DRLS_H__
#define __TIPS_DRLS_H__

typedef struct TDB_TIPS_DRLS
{
	char   zwrq[8+1];              /*��������*/
	/**/
	int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
	/**/
	char   jyqd[10+1];              /*��������*/
	/**/
	char   workdate[8+1];              /*��������*/
	/**/
	char   entrustdate[8+1];              /*ί������*/
	/**/
	char   taxorgcode[12+1];              /*���ջ��ش���*/
	/**/
	char   trano[8+1];              /*������ˮ��*/
	/*������ˮ��
	  TIPS������ˮ��
	  ��������ʱΪ�����������*/
	char   msgno[4+1];              /*���ı��*/
	/**/
	char   entrustdate2[8+1];              /*ί������2*/
	/*�ۿ��ʱ��¼��������ί������
	  ��������ʱ��¼ԭ���׵�ί������*/
	char   trano2[8+1];              /*������ˮ��2*/
	/*������ˮ��2
	  �ۿ��ʱΪ�������׵ĳ����������
	  ��������ʱΪԭ������ˮ��*/
	int    zhqzlsh2;              /*�ۺ�ǰ����ˮ��2*/
	/*�ۺ�ǰ����ˮ��2
	  �������׵���ˮ��*/
	char   chkdate[8+1];              /*��������*/
	/**/
	char   chkacctord[4+1];              /*�������κ�*/
	/**/
	char   handletype[1+1];              /*�������*/
	/**/
	char   trecode[10+1];              /*�������*/
	/**/
	char   payeebankno[12+1];              /*�տ����к�*/
	/**/
	char   payeeorgcode[12+1];              /*�տλ����*/
	/**/
	char   payeeacct[32+1];              /*�տ����˺�*/
	/**/
	char   payeename[60+1];              /*�տ�������*/
	/**/
	char   paybkcode[12+1];              /*�������к�*/
	/**/
	char   payopbkcode[12+1];              /*��������к�*/
	/**/
	char   protocolno[60+1];              /*Э�����*/
	/**/
	char   payacct[32+1];              /*�������˺�*/
	/**/
	char   handorgname[200+1];              /*�ɿλ����*/
	/**/
	char   dfzh[32+1];              /*�����ʺ�*/
	/**/
	double  jyje;              /*���׽��*/
	/**/
	char   taxvouno[18+1];              /*˰Ʊ����*/
	/**/
	char   dqdh[10+1];              /*��������*/
	/**/
	char   jgdh[10+1];              /*��������*/
	/**/
	char   jygy[16+1];              /*���׹�Ա*/
	/**/
	char   zddh[16+1];              /*�ն˴���*/
	/**/
	char   jyrq[8+1];              /*��������*/
	/**/
	char   jysj[8+1];              /*����ʱ��*/
	/**/
	char   zjrq[8+1];              /*��������*/
	/**/
	char   zjsj[8+1];              /*����ʱ��*/
	/**/
	char   zjlsh[32+1];              /*������ˮ��*/
	/**/
	char   zjxym[8+1];              /*������Ӧ��*/
	/**/
	char   zjxyxx[60+1];              /*������Ӧ��Ϣ*/
	/**/
	double  sxf;              /*������*/
	/**/
	double  zhye;              /*�˻����*/
	/**/
	char   xym[5+1];              /*��Ӧ��*/
	/**/
	char   xyxx[60+1];              /*��Ӧ��Ϣ*/
	/**/
	char   jyzt[1+1];              /*����״̬*/
	/*0-�ɹ�
	  1-ʧ��
	  2-������
	  9-���ڴ�����*/
	char   dzbz[2+1];              /*���˱�־*/
	/*��1λ�����������˱�־0-δ���� 1-�Ѷ���  2-�ҷ���,3-������
	  ��2λ����TIPS���˱�־0-δ���� 1-�Ѷ���  2-�ҷ���,3-������ */
	char   qsbz[1+1];              /*�����־*/
	/*0-δ���� 1-������*/
	char   kzbz[8+1];              /*��չ��־*/
	/**/
	char   taxpaycode[20+1];              /*��˰�˱���*/
	/**/
	char   taxpayname[200+1];              /*��˰������*/
	/**/
	char   spxx[40+1];              /*˰Ʊ��Ϣ*/
	/**/
	char   byzd[60+1];              /*�����ֶ�*/
	/**/
}SDB_TIPS_DRLS;

#define SD_DATA SDB_TIPS_DRLS
#define SD_MEMBERS\
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_LONG,zhqzlsh,2),\
	DEFSDMEMBER(T_STRING,jyqd,0),\
	DEFSDMEMBER(T_STRING,workdate,0),\
	DEFSDMEMBER(T_STRING,entrustdate,0),\
	DEFSDMEMBER(T_STRING,taxorgcode,0),\
	DEFSDMEMBER(T_STRING,trano,0),\
	DEFSDMEMBER(T_STRING,msgno,0),\
	DEFSDMEMBER(T_STRING,entrustdate2,0),\
	DEFSDMEMBER(T_STRING,trano2,0),\
	DEFSDMEMBER(T_LONG,zhqzlsh2,2),\
	DEFSDMEMBER(T_STRING,chkdate,0),\
	DEFSDMEMBER(T_STRING,chkacctord,0),\
	DEFSDMEMBER(T_STRING,handletype,0),\
	DEFSDMEMBER(T_STRING,trecode,0),\
	DEFSDMEMBER(T_STRING,payeebankno,0),\
	DEFSDMEMBER(T_STRING,payeeorgcode,0),\
	DEFSDMEMBER(T_STRING,payeeacct,0),\
	DEFSDMEMBER(T_STRING,payeename,0),\
	DEFSDMEMBER(T_STRING,paybkcode,0),\
	DEFSDMEMBER(T_STRING,payopbkcode,0),\
	DEFSDMEMBER(T_STRING,protocolno,0),\
	DEFSDMEMBER(T_STRING,payacct,0),\
	DEFSDMEMBER(T_STRING,handorgname,0),\
	DEFSDMEMBER(T_STRING,dfzh,0),\
	DEFSDMEMBER(T_DOUBLE,jyje,2),\
	DEFSDMEMBER(T_STRING,taxvouno,0),\
	DEFSDMEMBER(T_STRING,dqdh,0),\
	DEFSDMEMBER(T_STRING,jgdh,0),\
	DEFSDMEMBER(T_STRING,jygy,0),\
	DEFSDMEMBER(T_STRING,zddh,0),\
	DEFSDMEMBER(T_STRING,jyrq,0),\
	DEFSDMEMBER(T_STRING,jysj,0),\
	DEFSDMEMBER(T_STRING,zjrq,0),\
	DEFSDMEMBER(T_STRING,zjsj,0),\
	DEFSDMEMBER(T_STRING,zjlsh,0),\
	DEFSDMEMBER(T_STRING,zjxym,0),\
	DEFSDMEMBER(T_STRING,zjxyxx,0),\
	DEFSDMEMBER(T_DOUBLE,sxf,2),\
	DEFSDMEMBER(T_DOUBLE,zhye,2),\
	DEFSDMEMBER(T_STRING,xym,0),\
	DEFSDMEMBER(T_STRING,xyxx,0),\
	DEFSDMEMBER(T_STRING,jyzt,0),\
	DEFSDMEMBER(T_STRING,dzbz,0),\
	DEFSDMEMBER(T_STRING,qsbz,0),\
	DEFSDMEMBER(T_STRING,kzbz,0),\
	DEFSDMEMBER(T_STRING,taxpaycode,0),\
	DEFSDMEMBER(T_STRING,taxpayname,0),\
	DEFSDMEMBER(T_STRING,spxx,0),\
	DEFSDMEMBER(T_STRING,byzd,0)

	DECLAREFIELDS(SD_TIPS_DRLS)                                                                                   
#undef SD_DATA                                                                  
#undef SD_MEMBERS 

#endif  /*end of __TIPS_DRLS_H__*/
