/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE
文 件 名:ICPS_JB_bankinfo.h
文件描述:ICPS_JB_BANKINFO;结构定义数据库开发嵌C头文件
项 目 组:银行支付结算产品部
程 序 员:
发布时间:2017-08-10 15:06:30 [By qinsb@hundsun.com]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_BANKINFO ()
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __ICPS_JB_BANKINFO_H__
#define __ICPS_JB_BANKINFO_H__

typedef struct
{
    char    ptrq[8+1];                        /*平台日期*/
    char    ptlsh[10+1];                      /*平台流水号*/
    char    reqmsgid[64+1];                   /*请求报文唯一标示*/
    char    applyno[64+1];                    /*请求报文唯一标识*/
    char    isexistcust[1+1];                  /*是否存量客户*/
    char    isexistdebtcust[1+1];                /*是否存量借记卡客户*/
    char    balance[18+1];                     /*卡内余额*/
    char    avgbalancelast3days[18+1];                /*近3个月日均余额*/
    char    avgbalancelast6days[18+1];                /*近6个月日均余额*/
    char    incomelast3m[18+1];                /*近3个月银行流水收入金额数*/
    char    paylast3m[18+1];                  /*近3个月银行流水支出金额数*/
    char    incomelast6m[18+1];                /*近6个月银行流水收入金额数*/
    char    paylast6m[18+1];                  /*近6个月银行流水支出金额数*/
    char    isexistccust[1+1];                /*是否存量信用卡客户*/
    char    currccamt[18+1];                  /*本行信用卡授信额度*/
    char    currdisburseccamt[18+1];                /*本行信用卡当前使用额度*/
    char    isexistfincust[1+1];                /*是否存量理财客户*/
    char    finbalance[18+1];                  /*理财余额*/
    char    avgfinballast6m[18+1];                /*近6个月日均理余额*/
    char    isexistinsurancecus[1+1];                /*是否存量保险客户*/
    char    isexistloancust[1+1];                /*是否存量贷款客户*/
    char    operationloanbal[18+1];                /*经营类贷款总余额*/
    char    personalcreditbal[18+1];                /*个人信用类贷总余额*/
    char    autoloanbal[18+1];                /*车贷余额*/
    char    autoasset[18+1];                  /*车产价值评估额*/
    char    houseloanbal[18+1];                /*房贷余额*/
    char    houseasset[18+1];                /*房产价值评估额*/
    char    isstockcust[1+1];                  /*是否证券客户*/
    char    isthirddepository[1+1];          /*是否第三方存管客户*/
    char    ispayrollcust[1+1];              /*是否工资代发客户*/
    char    issocialsecuritycus[1+1];              /*是否社保代缴客户*/
    char    islifepaymentcust[1+1];              /*是否水电煤代缴客户*/
    char    incorporation[120+1];              /*工作单位*/
    char    incorigin[1+1];                    /*工作单位数据来源*/
    char    position[120+1];                   /*职位*/
    char    positionorigin[1+1];              /*职位信息来源*/
    char    industry[120+1];                  /*行业*/
    char    industryorigin[1+1];              /*行业信息来源*/
    char    workyears[3+1];                  /*工作年限*/
    char    workyearsorigin[1+1];              /*工作年限信息来源*/
    char    income[18+1];                    /*月收入区间*/
    char    incomeorigin[1+1];              /*月收入信息来源*/
    char    marriagestatus[1+1];              /*婚姻状态*/
    char    marriageorigin[1+1];              /*婚姻状态信息来源*/
    char    isoperation[1+1];                /*是否经营者（工商企业或个体工商企业????*/
    char    operationorigin[1+1];              /*是否经营者信息来源*/
    char    isinnerblackcust[1+1];              /*是否击中内部黑名单客户*/
    char    ispolicecertified[1+1];              /*是否公安网身份验证成功*/
    char    iscourtexeccust[1+1];              /*是否击中被执行人等涉诉信息*/
    char    isqryhousefund[1+1];              /*是否有查询公积金信息*/
    char    fundqrydate[8+1];                /*公积金查询时间*/
    char    fundmonthamt[18+1];              /*公积金查询月缴纳额*/
    char    fundaccountdate[8+1];              /*公积金开户日期*/
    char    fundmonthslast6m[3+1];          /*近6个月累计缴纳月数*/
    char    fundamtlast6m[18+1];             /*近6个月累计缴纳金额*/
    char    fundtotalmonths[3+1];             /*总缴纳月数*/
    char    fundtotalamt[18+1];             /*总缴纳金额*/
    char    fundmaxamt[18+1];               /*公积金属地缴纳上限*/
    char    isqrysocialsec[1+1];             /*是否有查询社保信息*/
    char    socialqrydate[8+1];             /*社保信息查询时间*/
    char    pensionqrymonthamt[18+1];             /*养老保险查询月缴纳额*/
    char    pensionaccountdate[8+1];             /*养老保险开户日期*/
    char    pensionmonthslast6m[3+1];             /*近6个月养老保险累计缴纳月数*/
    char    pensionamtlast6m[18+1];             /*近6个月养老保险累计缴纳金额*/
    char    pensiontotalmonths[3+1];             /*养老保险总缴纳月数*/
    char    pensiontotalamt[18+1];             /*养老保险总缴纳金额*/
    char    mdcmonthamt[18+1];               /*医疗保险查询月缴纳额*/
    char    mdcaccountdate[8+1];             /*医疗保险开户日期*/
    char    mdcmonthslast6m[3+1];             /*近6个月医疗保险累计缴纳月数*/
    char    mdcamtlast6m[18+1];             /*近6个月医疗保险累计缴纳金额*/
    char    mdctotalmonths[3+1];             /*医疗保险总缴纳月数*/
    char    mdctotalamt[18+1];             /*医疗保险总缴纳金额*/
    char    isqrydegree[1+1];              /*是否有查询学历信息*/
    char    schoolname[120+1];             /*院校名称*/
    char    degreelevel[30+1];             /*学历层次*/
    char    degreetype[120+1];             /*学历类别*/
    char    entranceyear[8+1];             /*入学年份*/
    char    isqrycommunication[1+1];             /*是否有查询运营商信息*/
    char    communication[1+1];             /*运营商*/
    char    onlinedays[8+1];                  /*在网时长*/
    char    totaltelfare[18+1];             /*总话费账单金额*/
    char    totalcalhours[8+1];             /*半年内通话时长*/
    char    isoutblackcust[1+1];             /*是否击中外部查询黑名单*/
    char    bankencryptedfeatur[4000+1];          /*半年内通话时长*/
    char    bank_encrypted_meta[1024+1];          /*是否击中外部查询黑名单*/
}ST_ICPS_JB_BANKINFO;
#define SD_DATA  ST_ICPS_JB_BANKINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,isexistcust, 0),\
    DEFSDMEMBER(T_STRING,isexistdebtcust, 0),\
    DEFSDMEMBER(T_STRING,balance, 0),\
    DEFSDMEMBER(T_STRING,avgbalancelast3days, 0),\
    DEFSDMEMBER(T_STRING,avgbalancelast6days, 0),\
    DEFSDMEMBER(T_STRING,incomelast3m, 0),\
    DEFSDMEMBER(T_STRING,paylast3m, 0),\
    DEFSDMEMBER(T_STRING,incomelast6m, 0),\
    DEFSDMEMBER(T_STRING,paylast6m, 0),\
    DEFSDMEMBER(T_STRING,isexistccust, 0),\
    DEFSDMEMBER(T_STRING,currccamt, 0),\
    DEFSDMEMBER(T_STRING,currdisburseccamt, 0),\
    DEFSDMEMBER(T_STRING,isexistfincust, 0),\
    DEFSDMEMBER(T_STRING,finbalance, 0),\
    DEFSDMEMBER(T_STRING,avgfinballast6m, 0),\
    DEFSDMEMBER(T_STRING,isexistinsurancecus, 0),\
    DEFSDMEMBER(T_STRING,isexistloancust, 0),\
    DEFSDMEMBER(T_STRING,operationloanbal, 0),\
    DEFSDMEMBER(T_STRING,personalcreditbal, 0),\
    DEFSDMEMBER(T_STRING,autoloanbal, 0),\
    DEFSDMEMBER(T_STRING,autoasset, 0),\
    DEFSDMEMBER(T_STRING,houseloanbal, 0),\
    DEFSDMEMBER(T_STRING,houseasset, 0),\
    DEFSDMEMBER(T_STRING,isstockcust, 0),\
    DEFSDMEMBER(T_STRING,isthirddepository, 0),\
    DEFSDMEMBER(T_STRING,ispayrollcust, 0),\
    DEFSDMEMBER(T_STRING,issocialsecuritycus, 0),\
    DEFSDMEMBER(T_STRING,islifepaymentcust, 0),\
    DEFSDMEMBER(T_STRING,incorporation, 0),\
    DEFSDMEMBER(T_STRING,incorigin, 0),\
    DEFSDMEMBER(T_STRING,position, 0),\
    DEFSDMEMBER(T_STRING,positionorigin, 0),\
    DEFSDMEMBER(T_STRING,industry, 0),\
    DEFSDMEMBER(T_STRING,industryorigin, 0),\
    DEFSDMEMBER(T_STRING,workyears, 0),\
    DEFSDMEMBER(T_STRING,workyearsorigin, 0),\
    DEFSDMEMBER(T_STRING,income, 0),\
    DEFSDMEMBER(T_STRING,incomeorigin, 0),\
    DEFSDMEMBER(T_STRING,marriagestatus, 0),\
    DEFSDMEMBER(T_STRING,marriageorigin, 0),\
    DEFSDMEMBER(T_STRING,isoperation, 0),\
    DEFSDMEMBER(T_STRING,operationorigin, 0),\
    DEFSDMEMBER(T_STRING,isinnerblackcust, 0),\
    DEFSDMEMBER(T_STRING,ispolicecertified, 0),\
    DEFSDMEMBER(T_STRING,iscourtexeccust, 0),\
    DEFSDMEMBER(T_STRING,isqryhousefund, 0),\
    DEFSDMEMBER(T_STRING,fundqrydate, 0),\
    DEFSDMEMBER(T_STRING,fundmonthamt, 0),\
    DEFSDMEMBER(T_STRING,fundaccountdate, 0),\
    DEFSDMEMBER(T_STRING,fundmonthslast6m, 0),\
    DEFSDMEMBER(T_STRING,fundamtlast6m, 0),\
    DEFSDMEMBER(T_STRING,fundtotalmonths, 0),\
    DEFSDMEMBER(T_STRING,fundtotalamt, 0),\
    DEFSDMEMBER(T_STRING,fundmaxamt, 0),\
    DEFSDMEMBER(T_STRING,isqrysocialsec, 0),\
    DEFSDMEMBER(T_STRING,socialqrydate, 0),\
    DEFSDMEMBER(T_STRING,pensionqrymonthamt, 0),\
    DEFSDMEMBER(T_STRING,pensionaccountdate, 0),\
    DEFSDMEMBER(T_STRING,pensionmonthslast6m, 0),\
    DEFSDMEMBER(T_STRING,pensionamtlast6m, 0),\
    DEFSDMEMBER(T_STRING,pensiontotalmonths, 0),\
    DEFSDMEMBER(T_STRING,pensiontotalamt, 0),\
    DEFSDMEMBER(T_STRING,mdcmonthamt, 0),\
    DEFSDMEMBER(T_STRING,mdcaccountdate, 0),\
    DEFSDMEMBER(T_STRING,mdcmonthslast6m, 0),\
    DEFSDMEMBER(T_STRING,mdcamtlast6m, 0),\
    DEFSDMEMBER(T_STRING,mdctotalmonths, 0),\
    DEFSDMEMBER(T_STRING,mdctotalamt, 0),\
    DEFSDMEMBER(T_STRING,isqrydegree, 0),\
    DEFSDMEMBER(T_STRING,schoolname, 0),\
    DEFSDMEMBER(T_STRING,degreelevel, 0),\
    DEFSDMEMBER(T_STRING,degreetype, 0),\
    DEFSDMEMBER(T_STRING,entranceyear, 0),\
    DEFSDMEMBER(T_STRING,isqrycommunication, 0),\
    DEFSDMEMBER(T_STRING,communication, 0),\
    DEFSDMEMBER(T_STRING,onlinedays, 0),\
    DEFSDMEMBER(T_STRING,totaltelfare, 0),\
    DEFSDMEMBER(T_STRING,totalcalhours, 0),\
    DEFSDMEMBER(T_STRING,isoutblackcust, 0),\
    DEFSDMEMBER(T_STRING,bankencryptedfeatur, 0),\
    DEFSDMEMBER(T_STRING,bank_encrypted_meta, 0)
DECLAREFIELDS(SD_ICPS_JB_BANKINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
