/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V2.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE\INFORMIX\DB2
�ļ�����:icps_jb_allxml.h
�ļ�����:
�� Ŀ ��:
�� �� Ա:
��������:2015-09-22
��    ��:
�޸�����:
*********************************************************************/
/*
�޸ļ�¼
�޸�����:
�޸�����:
�޸���:
*/

#ifndef __ICPS_JB_ALLXML_H__
#define __ICPS_JB_ALLXML_H__

#include "./xml/icps_jb_applyinfo.h"
#include "./xml/icps_jb_resultinfo.h"
#include "./xml/icps_jb_bankinfo.h"
#include "./xml/icps_jb_extinfo.h"
#include "./xml/icps_jb_zminfo.h"
#include "./xml/icps_jb_idcode2addr.h"
#define XMLNM_ICPS_JB_PBOC_INFO   "/jiebei_req/request/body/pbocInfo"       /* ����������Ϣ�ڵ� */
#define XMLNM_ICPS_JB_ZM_INFO   "/jiebei_req/request/body/zmInfo"       /* ֥����Ϣ�ڵ� */
#define XMLNM_ICPS_JB_EXT_INFO   "/jiebei_req/request/body/extInfo"       /*��չ��Ϣ */
#define XMLNM_ICPS_JB_PTRQ   "/pub/zwrq"       /*��������*/
#define XMLNM_ICPS_JB_PTLSH   "/pub/zhqzlsh"       /*�ۺ�ǰ����ˮ�� */
#define XMLNM_ICPS_JB_SYSTIME   "/sys/systime"       /*ϵͳʱ�� */
#define XMLNM_ICPS_JB_REQMSGID   "/pub/reqmsgid"       /*������Ψһ��ʾ */
#define XMLNM_ICPS_JB_APPLYNO   "/pub/applyno"       /*���뵥�� */
#define XMLNM_ICPS_JB_RESPCODE   "/pub/respcode"       /*��Ӧ��*/
#define XMLNM_ICPS_JB_RESPMSG   "/pub/respmsg"       /*��Ӧ��Ϣ */
#define XMLNM_ICPS_JB_WJHBS   "/myjb/sysinfo/wjhbs"       /*�ļ��ϲ��� */
#endif


