/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE
文 件 名:ICPS_JB_zminfo.h
文件描述:ICPS_JB_ZMINFO;结构定义数据库开发嵌C头文件
项 目 组:银行支付结算产品部
程 序 员:
发布时间:2017-08-11 11:07:53 [By qinsb@hundsun.com]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_ZMINFO (申请人芝麻信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __ICPS_JB_ZMINFO_H__
#define __ICPS_JB_ZMINFO_H__

typedef struct
{
    char    ptrq[8+1];                     /*平台日期*/
    char    ptlsh[10+1];                 /*平台流水号*/
    char    reqmsgid[64+1];                /*请求报文唯一标示*/
    char    applyno[64+1];                   /*请求报文唯一标识*/
    char    creditscore_success[1+1];          /*芝麻信用评分-成功标志*/
    char    creditscore_biz_no[64+1];          /*芝麻信用评分-bizno*/
    char    creditscore_zmscore[8+1];          /*芝麻信用评分-芝麻分*/
    char    watchlistii_success[1+1];          /*芝麻行业关注名单-成功标志*/
    char    watchlistii_biz_no[64+1];          /*芝麻行业关注名单-bizno*/
    char    watchlistii_matched[1+1];          /*芝麻行业关注名单-是否关注*/
    char    ivs_success[1+1];             /*芝麻欺诈关注清单-成功标志*/
    char    ivs_hit[8+1];                 /*芝麻欺诈关注清单-是否击中*/
    char    ivs_biz_no[64+1];             /*芝麻欺诈关注清单-bizno*/
    char    company_name[120+1];          /*所在公司*/
    char    occupation[30+1];              /*职业类型*/
    char    have_car_flag[4+1];          /*是否有车*/
    char    have_fang_flag[4+1];          /*是否有房*/
    char    auth_fin_last_1mcnt[3+1];          /*最近一个月主动查询金融机构数*/
    char    auth_fin_last_3mcnt[3+1];          /*最近三个月主动查询金融机构数*/
    char    auth_fin_last_6mcnt[3+1];          /*最近六个月主动查询金融机构数*/
    char    ovd_order_cnt_6m[3+1];          /*最近六个月逾期总笔数*/
    char    ovd_order_amt_6m[18+1];          /*最近六个月逾期总金额*/
    char    mobile_fixed_days[5+1];          /*手机号稳定天数*/
    char    adr_stability_days[5+1];          /*地址稳定天数*/
    char    last6mavgassettotal[18+1];          /*最近六个月流动资产日均值*/
    char    tot_pay_amt_6m[18+1];               /*最近六个月支付总金额*/
    char    xfdc_index[18+1];                   /*消费档次*/
    char    positive_biz_cnt_1y[5+1];           /*最近一年履约场景数*/
    int     pbocinfo;                           /*人行征信信息 */
}ST_ICPS_JB_ZMINFO;
#define SD_DATA  ST_ICPS_JB_ZMINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,creditscore_success, 0),\
    DEFSDMEMBER(T_STRING,creditscore_biz_no, 0),\
    DEFSDMEMBER(T_STRING,creditscore_zmscore, 0),\
    DEFSDMEMBER(T_STRING,watchlistii_success, 0),\
    DEFSDMEMBER(T_STRING,watchlistii_biz_no, 0),\
    DEFSDMEMBER(T_STRING,watchlistii_matched, 0),\
    DEFSDMEMBER(T_STRING,ivs_success, 0),\
    DEFSDMEMBER(T_STRING,ivs_hit, 0),\
    DEFSDMEMBER(T_STRING,ivs_biz_no, 0),\
    DEFSDMEMBER(T_STRING,company_name, 0),\
    DEFSDMEMBER(T_STRING,occupation, 0),\
    DEFSDMEMBER(T_STRING,have_car_flag, 0),\
    DEFSDMEMBER(T_STRING,have_fang_flag, 0),\
    DEFSDMEMBER(T_STRING,auth_fin_last_1mcnt, 0),\
    DEFSDMEMBER(T_STRING,auth_fin_last_3mcnt, 0),\
    DEFSDMEMBER(T_STRING,auth_fin_last_6mcnt, 0),\
    DEFSDMEMBER(T_STRING,ovd_order_cnt_6m, 0),\
    DEFSDMEMBER(T_STRING,ovd_order_amt_6m, 0),\
    DEFSDMEMBER(T_STRING,mobile_fixed_days, 0),\
    DEFSDMEMBER(T_STRING,adr_stability_days, 0),\
    DEFSDMEMBER(T_STRING,last6mavgassettotal, 0),\
    DEFSDMEMBER(T_STRING,tot_pay_amt_6m, 0),\
    DEFSDMEMBER(T_STRING,xfdc_index, 0),\
    DEFSDMEMBER(T_STRING,positive_biz_cnt_1y, 0),\
    DEFSDMEMBER(T_LONG,pbocinfo, 0)
DECLAREFIELDS(SD_ICPS_JB_ZMINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
