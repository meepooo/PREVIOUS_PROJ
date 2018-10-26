/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE
文 件 名:ICPS_JB_EXTINFO.h
文件描述:ICPS_JB_EXTINFO;结构定义数据库开发嵌C头文件
项 目 组:银行支付结算产品部
程 序 员:
发布时间:2017-08-10 15:06:30 [By qinsb@hundsun.com]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_EXTINFO ()
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __ICPS_JB_EXTINFO_H__
#define __ICPS_JB_EXTINFO_H__

typedef struct
{
    char    ptrq[8+1];          /*平台日期*/
    char    ptlsh[10+1];          /*平台流水号*/
    char    reqmsgid[64+1];          /**/
    char    applyno[64+1];          /**/
    char    isplatadm[1+1];          /*平台贷是否准入*/
    char    platunadmreason[1024+1];          /*平台贷不准入原因*/
    char    platcreditamt[18+1];          /*平台贷授信额度*/
    char    isjbprecreditcust[1+1];          /*是否借呗预授信客户*/
    char    loanrate[8+1];          /*基础利率*/
    char    period[64+1];          /*产品期限*/
    char    repaytype[64+1];          /*还款方式*/
    char    risklevel[32+1];          /*风险评级*/
    char    repayabilitylvl[32+1];          /*偿债能力评级*/
    char    changereason[1024+1];          /*提额、降额、提价、降价原因*/
}ST_ICPS_JB_EXTINFO;
#define SD_DATA  ST_ICPS_JB_EXTINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,isplatadm, 0),\
    DEFSDMEMBER(T_STRING,platunadmreason, 0),\
    DEFSDMEMBER(T_STRING,platcreditamt, 0),\
    DEFSDMEMBER(T_STRING,isjbprecreditcust, 0),\
    DEFSDMEMBER(T_STRING,loanrate, 0),\
    DEFSDMEMBER(T_STRING,period, 0),\
    DEFSDMEMBER(T_STRING,repaytype, 0),\
    DEFSDMEMBER(T_STRING,risklevel, 0),\
    DEFSDMEMBER(T_STRING,repayabilitylvl, 0),\
    DEFSDMEMBER(T_STRING,changereason, 0)
DECLAREFIELDS(SD_ICPS_JB_EXTINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
