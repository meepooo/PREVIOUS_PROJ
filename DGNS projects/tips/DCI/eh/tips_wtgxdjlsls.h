/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_wtgxdj.eh
�ļ�����:tips_wtgxdj;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_wtgxdj (ί�й�ϵ�Ǽ�)
˵    ��:TIPSί�й�ϵ�Ǽ�
���ڵǼǿͻ�����Э����Ϣ
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_WTGXDJLSLS_EH__
#define __TIPS_WTGXDJLSLS_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_WTGXDJLSLS
{
  char   protocolno[60+1];              /*Э�����*/
              /*Э�����
                ���ջ��ء���ҵ���С���˰������ǩ����ί��Э�����*/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /*���ջ��ش���*/
  char   paybkcode[12+1];              /*�������к�*/
              /*�������к�
                ָ��˰�˿����ж�Ӧ���������е�֧��ϵͳ�к�*/
  char   payacct[32+1];              /*�����˻�*/
              /*�����˻�
                ������ί�нɿ�Э���顱����˰�˵Ľɿ�˺�*/
  char   bankprotocolno[30+1];              /*����Э�����*/
              /*����Э�����
                [TIPSЭ��ǼǱ�]�е�Э�����,���������
                */
  char   taxpaycode[20+1];              /*��˰�˱���*/
              /*��˰�˱���*/
  char   payopbkcode[12+1];              /*��������к�*/
              /*��������к�*/
  char   taxpayname[200+1];              /*��˰������*/
              /*��˰������*/
  char   handorgname[200+1];              /*�ɿλ����*/
              /*�ɿλ����*/
  char   khh[12+1];              /*�ͻ���*/
              /*�ͻ��ţ����пͻ���
                ��������*/
  char   wtgxzt[1+1];              /*ί�й�ϵ״̬*/
              /*ί�й�ϵ״̬����0 ����_NORMAL|1 ����_REVOKE|2 ����_LOCK����ȱʡΪ0��������*/
  char   gxdjrq[8+1];              /*��ϵ�Ǽ�����*/
              /*��ϵ�Ǽ�����*/
  char   djlsh[18+1];              /*�Ǽ���ˮ��*/
              /*�Ǽ���ˮ�ţ��Ǽ�ί�й�ϵ�ۺ�Ӧ��ǰ����ˮ��*/
  char   djdqdh[10+1];              /*�Ǽǵ�������*/
              /*�Ǽǵ�������*/
  char   djjgdh[10+1];              /*�Ǽǻ�������*/
              /*�Ǽǻ�������*/
  char   djjygy[16+1];              /*�Ǽǽ��׹�Ա*/
              /*�Ǽǽ��׹�Ա*/
  char   djzddh[16+1];              /*�Ǽ��ն˴���*/
              /**/
  char   xgrq[8+1];              /*�޸�����*/
              /*��ϵ��������*/
  char   xglsh[18+1];              /*�޸���ˮ��*/
              /*������ˮ�ţ�����ί�й�ϵ�ۺ�Ӧ��ǰ����ˮ��*/
  char   xgdqdh[10+1];              /*�޸ĵ�������*/
              /*�޸ĵ�������*/
  char   xgjgdh[10+1];              /*�޸Ļ�������*/
              /**/
  char   xgjygy[16+1];              /*�޸Ľ��׹�Ա*/
              /*�޸Ľ��׹�Ա*/
  char   xgzddh[16+1];              /*�޸��ն˴���*/
              /**/
  char   kzbz[8+1];              /*��չ��־*/
              /*��չ��־����ί�й�ϵ�Ƿ�����չ��Ϣ
                ��1λ��
                  �ʻ�����:0-�Թ�,1-��,2-��һ��
                ��2λ��
                  �����־:0-��,1-��
                  */
  char   yzbz[1+1];              /*��֤��־*/
              /*У����0-δУ�� 1-��֤ͨ�� 2-������֤*/
  char   yzxgrq[8+1];            /*��֤�޸�����*/
  
  char   byzd[80+1];              /*�����ֶ�*/
              /*�����ֶΣ����ڴ洢������Ϣ*/
  char   opbankno[10+1];              /* �������� */
}SDB_TIPS_WTGXDJLSLS;

#define SD_DATA  SDB_TIPS_WTGXDJLSLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,protocolno    ,0),\
	DEFSDMEMBER(T_STRING,taxorgcode    ,0),\
	DEFSDMEMBER(T_STRING,paybkcode     ,0),\
	DEFSDMEMBER(T_STRING,payacct       ,0),\
	DEFSDMEMBER(T_STRING,bankprotocolno,0),\
	DEFSDMEMBER(T_STRING,taxpaycode    ,0),\
	DEFSDMEMBER(T_STRING,payopbkcode   ,0),\
	DEFSDMEMBER(T_STRING,taxpayname    ,0),\
	DEFSDMEMBER(T_STRING,handorgname   ,0),\
	DEFSDMEMBER(T_STRING,khh           ,0),\
	DEFSDMEMBER(T_STRING,wtgxzt        ,0),\
	DEFSDMEMBER(T_STRING,gxdjrq        ,0),\
	DEFSDMEMBER(T_STRING,djlsh         ,0),\
	DEFSDMEMBER(T_STRING,djdqdh        ,0),\
	DEFSDMEMBER(T_STRING,djjgdh        ,0),\
	DEFSDMEMBER(T_STRING,djjygy        ,0),\
	DEFSDMEMBER(T_STRING,djzddh        ,0),\
	DEFSDMEMBER(T_STRING,xgrq          ,0),\
	DEFSDMEMBER(T_STRING,xglsh         ,0),\
	DEFSDMEMBER(T_STRING,xgdqdh        ,0),\
	DEFSDMEMBER(T_STRING,xgjgdh        ,0),\
	DEFSDMEMBER(T_STRING,xgjygy        ,0),\
	DEFSDMEMBER(T_STRING,xgzddh        ,0),\
	DEFSDMEMBER(T_STRING,kzbz          ,0),\
	DEFSDMEMBER(T_STRING,yzbz          ,0),\
	DEFSDMEMBER(T_STRING,yzxgrq          ,0),\
	DEFSDMEMBER(T_STRING,byzd          ,0),\
	DEFSDMEMBER(T_STRING,opbankno     ,0)

	DECLAREFIELDS(SD_TIPS_WTGXDJLSLS)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_WTGXDJ_EH__*/
