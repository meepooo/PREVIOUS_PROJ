/**********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V2.1.0.1
����ϵͳ:AIX LINUX
�� �� ��:
�� �� ��:agent_mid.h
�ļ�����:ϵͳ��Ϣ�궨��ͷ�ļ�
�� Ŀ ��:�м�ҵ���Ʒ�з���
�� �� Ա:�м�ҵ���Ʒ�з���
����ʱ��:2011��11��1��
**********************************************************************/
/*
�޸ļ�¼
�޸�����:
�޸�����:
�޸���:
*/
#ifndef __AGENT_MSG_H__
#define __AGENT_MSG_H__

#define MSG_AGENT_NOYWBH              "AGENT:���ո��޴�ҵ����"
#define MSG_AGENT_NOYWLX              "AGENT:���ո��޴�ҵ������"
#define MSG_AGENT_YWLX_ZT             "AGENT:��ҵ������״̬��Ч"
#define MSG_AGENT_YWLX                "AGENT:��ҵ������״̬�Ƿ�"
#define MSG_AGENT_YWBH_ZT             "AGENT:��ҵ����״̬��Ч"
#define MSG_AGENT_YWBH                "AGENT:��ҵ����״̬�Ƿ�"
#define MSG_AGENT_DRLS_TJ             "AGENT:ͳ�ƴ��ո�Ӧ����ˮʧ��"
#define MSG_AGENT_ZJMXDZ_CURERR       "AGENT:��ȡ������ˮ�α궨�����" 
#define MSG_AGENT_ZJMXDZ_OPENERR      "AGENT:��������ˮ�α����"
#define MSG_AGENT_ZJMXDZ_DRLSERR      "AGENT:��ȡƽ̨��ˮ�α궨�����"
#define MSG_AGENT_DZBPB_INSERT        "AGENT:��¼���˲�ƽ��ʧ��"
#define MSG_AGENT_ZJMXDZ_DRLSOPEN     "AGENT:��ȡƽ̨��ˮ�α�򿪴���"
#define MSG_AGENT_DRLS_INSERT         "AGENT:��¼������ˮ��ʧ��"
#define MSG_AGENT_DRLS_UPDATE         "AGENT:���µ�����ˮ��ʧ��"
#define MSG_AGENT_DRLS_UNCHECK        "AGENT:��δ���������˼�¼"
#define MSG_AGENT_DRLS_UNPROC         "AGENT:��δ����ͬ������ƽ��ˮ"
#define MSG_AGENT_DZBPB_QUYFAIL       "AGENT:��ѯ���˲�ƽ��ˮʧ��"
#define MSG_AGENT_DZBPB_NOTEXIST      "AGENT:�޴˲�ƽ��ˮ��Ϣ"
#define MSG_AGENT_YWRQLX_COMMON       "AGENT:ҵ����������Ϊ����,���赥������" 
#define MSG_AGENT_DRLS_QUYFAIL        "AGENT:��ѯ������ˮʧ��"
#define MSG_AGENT_DRLS_NOTFOUND        "AGENT:�޴���ˮ�Ŷ�Ӧ����ˮ"
#define MSG_AGENT_REPORT_CURERR       "AGENT:���ܱ�������ˮ�α����"
#define MSG_AGENT_REPORT_OPENERR      "AGENT:���ܱ������ˮ�α����"
#define MSG_AGENT_REPORT_YWBHERR      "AGENT:��ѯҵ���ű�ʧ��"
#define MSG_AGENT_QUERY_MODEERR       "AGENT:ϵͳ��֧�ָò�ѯģʽ"
#define MSG_AGENT_QUERY_PQRYERR       "AGENT:��ҳ��ѯʧ��"
#define MSG_AGENT_REPEAT_SIGN         "AGENT:��ǩ��������δǩ��"
#define MSG_AGENT_REPEAT_UNSIGN       "AGENT:��ǩ�˻�����δǩ��"
#define MSG_AGENT_YWBH_NONEED_SIGN    "AGENT:��Ʒ������ǩ��ǩ��"
#define MSG_AGENT_BILLNOTFOUND        "AGENT:��Ʊ��Ϣ������"
#define MSG_AGENT_PZXX_INSERT         "AGENT:���뷢Ʊ��Ϣʧ��,[%d]"
#define MSG_AGENT_PZXX_UPDATE         "AGENT:���·�Ʊ��Ϣʧ��,[%d]"
#define MSG_AGENT_PZXX_DELETE         "AGENT:ɾ����Ʊ��Ϣʧ��,[%d]"
#define MSG_AGENT_DRLS_CANCEL         "AGENT:����������ˮ��ʧ��,[%d]"
#define MSG_AGENT_DRLS_REPEAL         "AGENT:����������ˮ��ʧ��,[%d]"
#define MSG_AGENT_SERIAL_ZT           "AGENT:��ˮ״̬������"
#define MSG_AGENT_CANCEL_TELLER       "AGENT:�����Ǳ����׹�Ա"
#define MSG_AGENT_SERIAL_NOTFOUND     "AGENT:��ˮ������"
#define MSG_AGENT_BILL_NOTVAL         "AGENT:��Ʊ��Ϣ�����ڻ��Ѵ�ӡ"
#define MSG_AGENT_CPRQ_SAME           "AGENT:ҵ������ͬ���к�������ͬ "AGENT:
#define MSG_AGENT_DRLS_NULL           "AGENT:������ˮ��Ϊ��"
#define MSG_AGENT_BILL_QUYCOND        "AGENT:��Ʊ��ѯ���ʺ�,�ͻ���,��ˮ�Ų���ͬʱΪ��"
#define MSG_AGENT_RZZT_INSERT         "AGENT:��������״̬��ˮ�����"
#define MSG_AGENT_RZZT_UPDATE         "AGENT:��������״̬��ˮ�����"
#define MSG_AGENT_ZJDZSB              "AGENT:��������ʧ��,���ڶ�����"
#define MSG_AGENT_DSFDZSB             "AGENT:����������ʧ��,���ڶ�����"
#define MSG_AGENT_QSRQ_NULL           "AGENT:��ʼ����Ϊ��"

#endif                                                                               
