/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:住建部公积金前置系统
版    本:V2.0
操作系统:LINUX
数 据 库:ORACLE
文件名称:zjbgjj_allxml.h
文件描述:
项 目 组:
程 序 员:
发布日期:2016-10-19
修    订:
修改日期:
*********************************************************************/
/*
修改记录
修改日期:
修改内容:
修改人:
*/

#ifndef __ZJB_GJJ_ALLXML_H__
#define __ZJB_GJJ_ALLXML_H__



#define XMLNM_ZJBGJJ_XNJG   "/zjbgjj/xnjg"    /*虚拟机构*/
#define XMLNM_ZJBGJJ_XNGY   "/zjbgjj/xngy"    /*虚拟柜员*/
#define XMLNM_ZJBGJJ_XL     "/zjbgjj/xl"    /*序列*/
#define XMLNM_ZJBGJJ_HOST_RESP_ZJRQ       "/zjb/host/resp/zjrq"       /*主机日期*/
#define XMLNM_ZJBGJJ_HOST_RESP_ZJLSH      "/zjb/host/resp/zjlsh"      /*主机流水号*/
#define XMLNM_ZJBGJJ_HOST_RESP_ZJSJ       "/zjb/host/resp/zjsj"       /*主机时间*/
#define XMLNM_ZJBGJJ_HOST_RESP_ZJXYM      "/zjb/host/resp/zjxym"      /*主机响应码*/
#define XMLNM_ZJBGJJ_HOST_RESP_ZJXYXX     "/zjb/host/resp/zjxyxx"     /*主机响应信息*/
#define XMLNM_ZJBGJJ_HOST_RESP_BJYHLSH    "/zjb/host/resp/bjyhlsh"    /*本金银行流水号*/
#define XMLNM_ZJBGJJ_HOST_RESP_LXYHLSH    "/zjb/host/resp/lxyhlsh"    /*利息银行流水号*/
#define XMLNM_ZJBGJJ_HOST_RESP_DKFXYHLSH  "/zjb/host/resp/dkfxyhlsh"  /*贷款罚息银行主机流水号*/
#define XMLNM_ZJBGJJ_HOST_RESP_DKWYYHLSH  "/zjb/host/resp/dkwyyhlsh"  /*贷款违约金银行流水号*/
#define XMLNM_ZJBGJJ_HOST_RESP_BATCH      "/zjb/host/resp/batchno"      /*交易批次号*/

#define XMLNM_ZJBGJJ_QQDZT         "/zjbgjj/qqdzt"          /*核心处理结果*/
#define XMLNM_ZJBGJJ_HXSYNFLG      "/zjbgjj/hxsynflg"       /*同步标志0-同步 1-异步*/
#define XMLNM_ZJBGJJ_SENDSEQNO     "/zjbgjj/sendseqno"      /*发送方流水号*/
#define XMLNM_ZJBGJJ_TXUNITNO      "/zjbgjj/txunitno"       /*交易机构号*/

#define XMLNM_ZJBGJJ_WZ_QQDZT      "/zjbgjj/wzqqdzt"        /*往帐请求单状态*/
#define XMLNM_ZJBGJJ_WZ_SENDNODE   "/zjbgjj/sendnode"       /*往帐发送方节点号*/
#define XMLNM_ZJBGJJ_WZ_RECEIVENODE "/zjbgjj/receivenode"   /*往帐请求单状态*/
#define XMLNM_ZJBGJJ_YHDM          "/zjbgjj/yhdm"           /*银行代码*/
#define XMLNM_ZJBGJJ_AUTOPROC      "/zjbgjj/autoprocs"      /*定时任务自动处理笔数*/


#endif


