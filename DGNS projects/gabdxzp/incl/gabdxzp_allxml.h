/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:��������������թƭǰ��ϵͳ
��    ��:V2.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE\INFORMIX\DB2
�ļ�����:gabdxzp_allxml.h
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

#ifndef __GAB_DXZP_ALLXML_H__
#define __GAB_DXZP_ALLXML_H__
         
#include "xml/gab_dxzp_djxj_xml.h" 
#include "xml/gab_dxzp_dtcx_xml.h" 
#include "xml/gab_dxzp_jjzf_xml.h" 
#include "xml/gab_dxzp_jymx_xml.h" 
#include "xml/gab_dxzp_qhcx_xml.h" 
#include "xml/gab_dxzp_sajb_xml.h" 
#include "xml/gab_dxzp_sazh_xml.h" 
#include "xml/gab_dxzp_sbxx_xml.h" 
#include "xml/gab_dxzp_sfsa_xml.h" 
#include "xml/gab_dxzp_xdxx_xml.h" 
#include "xml/gab_dxzp_yckk_xml.h" 
#include "xml/gab_dxzp_ycsj_xml.h" 
#include "xml/gab_dxzp_zhsa_xml.h" 
#include "xml/gab_dxzp_ztcx_xml.h" 
#include "xml/gab_dxzp_dtcx_resp_xml.h" 
#include "xml/gab_dxzp_dtjc_resp_xml.h" 
#include "xml/gab_dxzp_jymx_zhjbxx_xml.h" 
#include "xml/gab_dxzp_qhcx_qlxx_xml.h" 
#include "xml/gab_dxzp_qhcx_sfqzxx_xml.h" 
#include "xml/gab_dxzp_qhcx_zzhxx_xml.h" 
#include "xml/gab_dxzp_zhjbxx_zhxx_xml.h" 
#include "xml/gab_dxzp_zhxx_zhjyxx_xml.h" 
#include "xml/gab_dxzp_ztcx_resp_xml.h"
#include "xml/gab_dxzp_qhcx_zhxx_xml.h" 
#include "xml/gab_dxzp_qhcx_zhjbxx_xml.h"

/*ϵͳ����*/
#define XMLNM_SFXT_DXZP_XL  "/sfxt/xl"    /*����*/
#define XMLNM_SFXT_XNJG   "/sfxt/xnjg"    /*�������*/
#define XMLNM_SFXT_XNGY   "/sfxt/xngy"    /*�����Ա*/
#define XMLNM_DXZP_QSJGID "/gabdxzp/qsjgid"  /*ȱʡ����ID��Ŀ�������*/
#define XMLNM_DXZP_YHJGID "/gabdxzp/xxcs/yhjgid"  /*���л���ID*/
#define XMLNM_DXZP_HXSYNFLG "/gabdxzp/hxsynflg"  /*����ͬ�첽ģʽ*/
#define XMLNM_DXZP_DDMIN "/gabdxzp/xxcs/ddmin"  /*����ͬ�첽ģʽ*/
#define XMLNM_DXZP_AUTOPROCS  "/gabdxzp/xxcs/autoprocs" /*�Զ����������*/
#define XMLNM_SFXT_HXFCBZ  "/sfxt/hxfcbz" /*���ķ��ر�־*/

/*ǰ�û�*/
#define XMLNM_GAB_DXZP_QZJ_YWLXBM "/gabdxzp/qzj/ywlxbm"  /*ҵ�����ͱ���*/
#define XMLNM_GAB_DXZP_QZJ_MODE "/gabdxzp/qzj/mode"  /*��Ϣ��תģʽ*/
#define XMLNM_GAB_DXZP_QZJ_JGID "/gabdxzp/qzj/jgid"  /*����ID*/

/*ҵ���*/
#define XMLNM_GAB_DXZP_YWSQBH    "/gabdxzp/ywsqbh"    /*ҵ��������*/
#define XMLNM_GAB_DXZP_YWLXBM    "/gabdxzp/ywlxbm"    /*ҵ�����ͱ���*/
#define XMLNM_GAB_DXZP_CLLX      "/gabdxzp/cllx"      /*��������*/
#define XMLNM_GAB_DXZP_QQDZT     "/gabdxzp/qqdzt"     /*����״̬*/
#define XMLNM_SFXT_HOST_RESP_ZXJG "/sfzt/host/resp/zxjg"     /*ִ�н��*/
#define XMLNM_PUB_JYBM           "/pub/JYBM"          /*���ױ���/ҵ�����ͱ���*/
#define XMLNM_GAB_DXZP_SBPCH     "/gabdxzp/sbpch"    /*�ϱ����κ�*/
#define XMLNM_GAB_DXZP_SBPCXH    "/gabdxzp/sbpcxh"    /*�ϱ��������*/
#define XMLNM_GAB_DXZP_SBZT      "/gabdxzp/sbzt"    /*�ϱ�״̬*/
#define XMLNM_GAB_DXZP_SBJYDM    "/gabdxzp/sbjydm"    /*�ϱ����״���*/

#define XMLNM_GAB_DXZP_JBXM      "/gabdxzp/czgym"     /*���о�������*/
#define XMLNM_GAB_DXZP_JBDH      "/gabdxzp/czgydh"     /*���о���绰*/

/*�����ӳ���*/
#define XMLNM_SFXT_HOST_REQ_CLLX  "/sfxt/host/req/cllx"     /*��������*/

#define XMLNM_SFXT_HOST_RESP_ZJRQ  "/sfxt/host/resp/zjrq"     /*��������*/
#define XMLNM_SFXT_HOST_RESP_ZJLSH  "/sfxt/host/resp/zjlsh"     /*������ˮ��*/

#define XMLNM_DXZP_YwyDm   "/sfck/host/resp/ywydm"     /*ҵ��Ӧ����*/
#define XMLNM_DXZP_sYwyDxx   "/sfck/host/resp/ywydxx"     /*ҵ��Ӧ����Ϣ*/
#define XMLNM_DXZP_DZXH     "/sfck/host/resp/dzxh"        /*��ֹ���*/
#endif
