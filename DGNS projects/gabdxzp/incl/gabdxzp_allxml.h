/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:恒生公安部电信诈骗前置系统
版    本:V2.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE\INFORMIX\DB2
文件名称:gabdxzp_allxml.h
文件描述:
项 目 组:
程 序 员:
发布日期:2015-09-22
修    订:
修改日期:
*********************************************************************/
/*  
修改记录
修改日期:
修改内容:
修改人:
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

/*系统参数*/
#define XMLNM_SFXT_DXZP_XL  "/sfxt/xl"    /*序列*/
#define XMLNM_SFXT_XNJG   "/sfxt/xnjg"    /*虚拟机构*/
#define XMLNM_SFXT_XNGY   "/sfxt/xngy"    /*虚拟柜员*/
#define XMLNM_DXZP_QSJGID "/gabdxzp/qsjgid"  /*缺省机构ID（目标机构）*/
#define XMLNM_DXZP_YHJGID "/gabdxzp/xxcs/yhjgid"  /*银行机构ID*/
#define XMLNM_DXZP_HXSYNFLG "/gabdxzp/hxsynflg"  /*核心同异步模式*/
#define XMLNM_DXZP_DDMIN "/gabdxzp/xxcs/ddmin"  /*核心同异步模式*/
#define XMLNM_DXZP_AUTOPROCS  "/gabdxzp/xxcs/autoprocs" /*自动任务处理笔数*/
#define XMLNM_SFXT_HXFCBZ  "/sfxt/hxfcbz" /*核心防重标志*/

/*前置机*/
#define XMLNM_GAB_DXZP_QZJ_YWLXBM "/gabdxzp/qzj/ywlxbm"  /*业务类型编码*/
#define XMLNM_GAB_DXZP_QZJ_MODE "/gabdxzp/qzj/mode"  /*消息流转模式*/
#define XMLNM_GAB_DXZP_QZJ_JGID "/gabdxzp/qzj/jgid"  /*机构ID*/

/*业务层*/
#define XMLNM_GAB_DXZP_YWSQBH    "/gabdxzp/ywsqbh"    /*业务申请编号*/
#define XMLNM_GAB_DXZP_YWLXBM    "/gabdxzp/ywlxbm"    /*业务类型编码*/
#define XMLNM_GAB_DXZP_CLLX      "/gabdxzp/cllx"      /*处理类型*/
#define XMLNM_GAB_DXZP_QQDZT     "/gabdxzp/qqdzt"     /*请求单状态*/
#define XMLNM_SFXT_HOST_RESP_ZXJG "/sfzt/host/resp/zxjg"     /*执行结果*/
#define XMLNM_PUB_JYBM           "/pub/JYBM"          /*交易编码/业务类型编码*/
#define XMLNM_GAB_DXZP_SBPCH     "/gabdxzp/sbpch"    /*上报批次号*/
#define XMLNM_GAB_DXZP_SBPCXH    "/gabdxzp/sbpcxh"    /*上报批次序号*/
#define XMLNM_GAB_DXZP_SBZT      "/gabdxzp/sbzt"    /*上报状态*/
#define XMLNM_GAB_DXZP_SBJYDM    "/gabdxzp/sbjydm"    /*上报交易代码*/

#define XMLNM_GAB_DXZP_JBXM      "/gabdxzp/czgym"     /*银行经办姓名*/
#define XMLNM_GAB_DXZP_JBDH      "/gabdxzp/czgydh"     /*银行经办电话*/

/*主机接出层*/
#define XMLNM_SFXT_HOST_REQ_CLLX  "/sfxt/host/req/cllx"     /*处理类型*/

#define XMLNM_SFXT_HOST_RESP_ZJRQ  "/sfxt/host/resp/zjrq"     /*主机日期*/
#define XMLNM_SFXT_HOST_RESP_ZJLSH  "/sfxt/host/resp/zjlsh"     /*主机流水号*/

#define XMLNM_DXZP_YwyDm   "/sfck/host/resp/ywydm"     /*业务应答码*/
#define XMLNM_DXZP_sYwyDxx   "/sfck/host/resp/ywydxx"     /*业务应答信息*/
#define XMLNM_DXZP_DZXH     "/sfck/host/resp/dzxh"        /*冻止序号*/
#endif
