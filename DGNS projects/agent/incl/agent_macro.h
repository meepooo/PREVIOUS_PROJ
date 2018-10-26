/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:̫ԭ�����м�ҵ��ƽ̨��Ŀ
��    ��:V3.0
����ϵͳ:AIX5.2+DB2V8.2+ANSI.C
�ļ�����:agent_macro.h
�ļ�����:����ҵ��ƽ̨�궨���ļ�
�� Ŀ ��:����ҵ��ƽ̨��Ŀ��
�� �� Ա:
��������:2007.06.26
��    ��:
�޸�����:
*********************************************************************/
#if !defined(__AGENT_MACRO__H)
#define __AGENT_MACRO__H

/* ��־�궨�����ڸ���ESQLC���� */
#define	__STRLOC(A)			__STRLOC_R(A)
#define	__STRLOC_R(A)		#A
#define	_TRACE		"[�ļ�" __FILE__ "][��" __STRLOC(__LINE__) "]"

   
     
/*�Ƿ�������*/
#define RYEAR(a) ((a) % 4 == 0 && (a) % 100 != 0 || (a) % 400 == 0)
/*һ�������*/
#define YEARDAYS(a) RYEAR(a)?366:365
/*���µ�����*/
#define MON2DAYS(a) RYEAR(a)?29:28
/*һ���µ�����*/
#define RMONTHDAYS(a, b) ((a) == 2?(MON2DAYS(b)):((a) < 8 && (a) % 2 == 0 || (a) >= 8 && (a) % 2 != 0)?30:31)

/* ��ϵͳ���ڵ㳤�� ���ܳ���2M !!! */

#define AGT_DATA_MAX_LENGTH      2097152            /*MAX_BUFFER 2M*/
#define AGT_BUFF_MAX_LENGTH      2097152            /*MAX_BUFFER 2M*/
#define DEFAULT_AGENT_YYBS      "002"              /*Ĭ�ϴ���ҵ��ƽ̨���*/

/* ����ҵ��ƽ̨��־�궨�忪ʼ */
#define	AGT_COMPEXEC_LOGRET(agtmid,agtmsg,agtresult)	{                  \
		fpub_SetMsg(lXmlhandle,agtmid,agtmsg);          \
		fpub_SetCompStatus(lXmlhandle, agtresult);                                 \
		LOGRET(COMPRET_FAIL, LM_STD, agtmsg,fpub_GetCompname(lXmlhandle));         \
	}
#define	AGT_LOG(logmsg)	{   \
		LOG(LM_STD,Fmtmsg("����ҵ��ƽ̨�����[%s]������־\n	[%s]",fpub_GetCompname(lXmlhandle),logmsg),"INFO");  \
	}

/* ����ҵ��ƽ̨��־�궨����� */

#define MAX_FILE_SIZE 131072

/* added by yangdong 20090414 ���״���궨�� */
#define AGT_TRANCODE_SIGN_IN      "920201"   /*�ͻ�ǩԼ*/
#define AGT_TRANCODE_SIGN_OUT     "920202"  /*�ͻ���Լ*/
#define AGT_TRANCODE_SIGN_MOD     "920203"   /*�ͻ�ǩԼ�޸�*/
#define AGT_TRANCODE_COLLECT_D    "920301"   /*���д���(ֱ��)*/
#define AGT_TRANCODE_COLLECT_Q    "920302"   /*���д���(�Ȳ���)*/
#define AGT_TRANCODE_PAY_D        "920303"   /*���д���(ֱ��)*/
#define AGT_TRANCODE_PAY_Q        "920304"   /*���д���(�Ȳ���)*/

#endif


