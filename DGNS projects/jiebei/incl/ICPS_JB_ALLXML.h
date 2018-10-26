/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V2.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE\INFORMIX\DB2
文件名称:icps_jb_allxml.h
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

#ifndef __ICPS_JB_ALLXML_H__
#define __ICPS_JB_ALLXML_H__

#include "./xml/icps_jb_applyinfo.h"
#include "./xml/icps_jb_resultinfo.h"
#include "./xml/icps_jb_bankinfo.h"
#include "./xml/icps_jb_extinfo.h"
#include "./xml/icps_jb_zminfo.h"
#include "./xml/icps_jb_idcode2addr.h"
#define XMLNM_ICPS_JB_PBOC_INFO   "/jiebei_req/request/body/pbocInfo"       /* 人行征信信息节点 */
#define XMLNM_ICPS_JB_ZM_INFO   "/jiebei_req/request/body/zmInfo"       /* 芝麻信息节点 */
#define XMLNM_ICPS_JB_EXT_INFO   "/jiebei_req/request/body/extInfo"       /*扩展信息 */
#define XMLNM_ICPS_JB_PTRQ   "/pub/zwrq"       /*账务日期*/
#define XMLNM_ICPS_JB_PTLSH   "/pub/zhqzlsh"       /*综合前置流水号 */
#define XMLNM_ICPS_JB_SYSTIME   "/sys/systime"       /*系统时间 */
#define XMLNM_ICPS_JB_REQMSGID   "/pub/reqmsgid"       /*请求报文唯一标示 */
#define XMLNM_ICPS_JB_APPLYNO   "/pub/applyno"       /*申请单号 */
#define XMLNM_ICPS_JB_RESPCODE   "/pub/respcode"       /*响应码*/
#define XMLNM_ICPS_JB_RESPMSG   "/pub/respmsg"       /*响应信息 */
#define XMLNM_ICPS_JB_WJHBS   "/myjb/sysinfo/wjhbs"       /*文件合并数 */
#endif


