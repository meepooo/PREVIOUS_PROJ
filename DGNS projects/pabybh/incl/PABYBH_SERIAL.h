#ifndef __PABYBH_SERIAL_H__
#define __PABYBH_SERIAL_H__ 

typedef struct TDB_PABYBH_SERIAL
{
	char TRANSDATE[8+1]            ;       /*ƽ̨����*/
	char TRANSSERIALNO[40+1]       ;       /*ƽ̨��ˮ��*/
	char ORITRANSDATE[8+1]         ;       /*ԭƽ̨����*/
	char ORITRANSSERIALNO[40+1]    ;       /*ԭƽ̨��ˮ��*/
	char TRANSTIME[8+1]            ;       /*����ʱ��*/
	char WORKDATE[8+1]             ;       /*ҵ������*/
	char WORKSERIALNO[40+1]        ;       /*ҵ����ˮ��*/
	char REQDATE[8+1]              ;       /*��������*/
	char REQSERIALNO[40+1]         ;       /*������ˮ��*/
	char CLUSTERNODENAME[30+1]     ;       /*��Ⱥ�ڵ��������*/
	char CLUSTERNODEIP[20+1]       ;       /*��Ⱥ�ڵ����IP*/
	char COBANKNO[12+1]            ;       /*�����к�*/
	char TRANSORG[10+1]            ;       /*���׻���*/
	char TRANSOPER[10+1]           ;       /*���׹�Ա*/
	char AUTHORG[10+1]             ;       /*��Ȩ����*/
	char AUTHOPER[10+1]            ;       /*��Ȩ��Ա*/
	char CNLTYPE[5+1]              ;       /*��������*/
	char TERMEQUINO[20+1]          ;       /*�ն��豸���*/
	char TRANSCODE[12+1]           ;       /*���״���*/
	char TRANSCODE1[1+1]           ;       /*���ӽ��״��� 0 ���� 1 ��� 2���������� 3 ���򹤱���*/
	char CUACOUNTYPE[1+1]          ;       /*�����˱�־ 0-���� 1-����*/
	char TRANSNAME[100+1]          ;       /*��������*/
	char CAPITALTYPE[1+1]          ;       /*�ʽ�����,0 ---ת��1--- ת��*/
	char SVRCODE[10+1]             ;       /*�������   (��ܡ��ƽ��)*/
	char CUSTNAME[80+1]            ;       /*�ͻ�����*/
	char CUSTTYPE[2+1]             ;       /*�ͻ�����*/
	char ACCTNO[32+1]              ;       /*�����˺�*/
	char ACCTNO2[32+1]             ;       /*�ʺ�2   �������˻�*/
	char ORIACCTNO[32+1]           ;       /*�����˺�  ͬ��*/
	char STOCKCODE[8+1]            ;       /*ȯ�̴���*/
	char CAPITALACCTNO[32+1]       ;       /*�ʽ��ʺ�*/
	double TRANSAMT                ;       /*���׽��*/
	double ORITRANSAMT             ;       /*���׽��*/
	double AMT2                    ;       /*���2*/
	double AMT3                    ;       /*���3*/
	char CURR[3+1]                 ;       /*����*/
	char CASHFLAG[1+1]             ;       /*�����ʶ*/
	char IEPSVRCODE[8+1]           ;       /*��Eͨ�������*/
	char IEPTRANSCODE[16+1]        ;       /*��Eͨ���״���*/
	char IEPBSIDATE[8+1]           ;       /*��Eͨҵ������*/
	char IEPTRADATE[8+1]           ;       /*��Eͨ��������*/
	char IEPSERIALNO[32+1]         ;       /*��Eͨ��ˮ��   ����*/
	char ORIIEPBSIDATE[8+1]        ;       /*ԭ��Eͨҵ������*/
	char ORIIEPSERIALNO[32+1]      ;       /*ԭ��Eͨ��ˮ��*/
	char IEPRESPCODE[12+1]         ;       /*��Eͨ��Ӧ����*/
	char IEPRESPMSG[120+1]         ;       /*��Eͨ��Ӧ��Ϣ*/
	char HOSTBSIDATE[8+1]          ;       /*������������*/
	char HOSTSERIALNO[32+1]        ;       /*������ˮ��*/
	char HOSTTRANSCODE[16+1]       ;       /*�������״���*/
	char HOSTRESPCODE[12+1]        ;       /*������Ӧ����*/
	char HOSTRESPMSG[120+1]        ;       /*������Ӧ��Ϣ*/
	char RESPCODE[10+1]            ;       /*��Ӧ��*/
	char RESPMSG[120+1]            ;       /*��Ӧ��Ϣ*/
	char IEPSTAT[1+1]              ;       /*���Ľ���״̬'0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ'*/
	char HOSTSTAT[1+1]             ;       /*���Ľ���״̬'0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ'*/
	char STAT[1+1]                 ;       /*����״̬'0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ'*/
	char ORISTAT[1+1]              ;       /*ƽ̨ͬ������״̬ǰԭ״̬ '0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ Xԭ��ˮ������'*/
	char CERTTYPE[2+1]             ;       /*֤������*/
	char CERTNO[32+1]              ;       /*֤������*/
  char PHONE[20+1]               ;       /*��ϵ��ʽ      */
  char AGENTNAME[80+1]           ;       /*�����˿ͻ�����*/
  char AGENTCERTY[2+1]           ;       /*������֤������*/
  char AGENTCERNO[32+1]          ;       /*������֤������*/
  char AGENTPHONE[20+1]          ;       /*��������ϵ��ʽ*/
	char CHKFLAG[1+1]              ;       /*���˱�־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�9-������*/
	char MEMO[128+1]               ;       /*��ע*/
	char EXTFLD1[64+1]             ;       /*�����ֶ�1*/
	char EXTFLD2[64+1]             ;       /*�����ֶ�2*/
	char EXTFLD3[128+1]            ;       /*�����ֶ�3*/
	char EXTFLD4[128+1]                    /*�����ֶ�4*/
}PABYBH_SERIAL;	

#define SD_DATA  PABYBH_SERIAL
#define SD_MEMBERS \
  DEFSDMEMBER(T_STRING,  TRANSDATE, 0),\
  DEFSDMEMBER(T_STRING,  TRANSSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  ORITRANSDATE, 0),\
  DEFSDMEMBER(T_STRING,  ORITRANSSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  TRANSTIME, 0),\
  DEFSDMEMBER(T_STRING,  WORKDATE, 0),\
  DEFSDMEMBER(T_STRING,  WORKSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  REQDATE, 0),\
  DEFSDMEMBER(T_STRING,  REQSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  CLUSTERNODENAME, 0),\
  DEFSDMEMBER(T_STRING,  CLUSTERNODEIP, 0),\
  DEFSDMEMBER(T_STRING,  COBANKNO, 0),\
  DEFSDMEMBER(T_STRING,  TRANSORG, 0),\
  DEFSDMEMBER(T_STRING,  TRANSOPER, 0),\
  DEFSDMEMBER(T_STRING,  AUTHORG, 0),\
  DEFSDMEMBER(T_STRING,  AUTHOPER, 0),\
  DEFSDMEMBER(T_STRING,  CNLTYPE, 0),\
  DEFSDMEMBER(T_STRING,  TERMEQUINO, 0),\
  DEFSDMEMBER(T_STRING,  TRANSCODE, 0),\
  DEFSDMEMBER(T_STRING,  TRANSCODE1, 0),\
  DEFSDMEMBER(T_STRING,  CUACOUNTYPE, 0),\
  DEFSDMEMBER(T_STRING,  TRANSNAME, 0),\
  DEFSDMEMBER(T_STRING,  CAPITALTYPE, 0),\
  DEFSDMEMBER(T_STRING,  SVRCODE, 0),\
  DEFSDMEMBER(T_STRING,  CUSTNAME, 0),\
  DEFSDMEMBER(T_STRING,  CUSTTYPE, 0),\
  DEFSDMEMBER(T_STRING,  ACCTNO, 0),\
  DEFSDMEMBER(T_STRING,  ORIACCTNO, 0),\
  DEFSDMEMBER(T_STRING,  ACCTNO2, 0),\
  DEFSDMEMBER(T_STRING,  STOCKCODE, 0),\
  DEFSDMEMBER(T_STRING,  CAPITALACCTNO, 0),\
  DEFSDMEMBER(T_DOUBLE,  TRANSAMT, 0),\
  DEFSDMEMBER(T_DOUBLE,  ORITRANSAMT, 0),\
  DEFSDMEMBER(T_DOUBLE,  AMT2, 0),\
  DEFSDMEMBER(T_DOUBLE,  AMT3, 0),\
  DEFSDMEMBER(T_STRING,  CURR, 0),\
  DEFSDMEMBER(T_STRING,  CASHFLAG, 0),\
  DEFSDMEMBER(T_STRING,  IEPSVRCODE, 0),\
  DEFSDMEMBER(T_STRING,  IEPTRANSCODE, 0),\
  DEFSDMEMBER(T_STRING,  IEPBSIDATE, 0),\
  DEFSDMEMBER(T_STRING,  IEPTRADATE, 0),\
  DEFSDMEMBER(T_STRING,  IEPSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  ORIIEPBSIDATE, 0),\
  DEFSDMEMBER(T_STRING,  ORIIEPSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  IEPRESPCODE, 0),\
  DEFSDMEMBER(T_STRING,  IEPRESPMSG, 0),\
  DEFSDMEMBER(T_STRING,  HOSTBSIDATE, 0),\
  DEFSDMEMBER(T_STRING,  HOSTSERIALNO, 0),\
  DEFSDMEMBER(T_STRING,  HOSTTRANSCODE, 0),\
  DEFSDMEMBER(T_STRING,  HOSTRESPCODE, 0),\
  DEFSDMEMBER(T_STRING,  HOSTRESPMSG, 0),\
  DEFSDMEMBER(T_STRING,  RESPCODE, 0),\
  DEFSDMEMBER(T_STRING,  RESPMSG, 0),\
  DEFSDMEMBER(T_STRING,  IEPSTAT, 0),\
  DEFSDMEMBER(T_STRING,  HOSTSTAT, 0),\
  DEFSDMEMBER(T_STRING,  STAT, 0),\
  DEFSDMEMBER(T_STRING,  ORISTAT, 0),\
  DEFSDMEMBER(T_STRING,  CERTTYPE, 0),\
  DEFSDMEMBER(T_STRING,  CERTNO, 0),\
  DEFSDMEMBER(T_STRING,  PHONE, 0),\
  DEFSDMEMBER(T_STRING,  AGENTNAME, 0),\
  DEFSDMEMBER(T_STRING,  AGENTCERTY, 0),\
  DEFSDMEMBER(T_STRING,  AGENTCERNO, 0),\
  DEFSDMEMBER(T_STRING,  AGENTPHONE, 0),\
  DEFSDMEMBER(T_STRING,  CHKFLAG, 0),\
  DEFSDMEMBER(T_STRING,  MEMO, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD1, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD2, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD3, 0),\
  DEFSDMEMBER(T_STRING,  EXTFLD4, 0)

  DECLAREFIELDS(SD_PABYBH_SERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_SERIAL_H__*/
