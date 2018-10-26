/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE
文 件 名:ICPS_JB_RESULTINFO.h
文件描述:ICPS_JB_RESULTINFO;结构定义数据库开发嵌C头文件
项 目 组:银行支付结算产品部
程 序 员:
发布时间:2017-08-10 15:06:29 [By qinsb@hundsun.com]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_RESULTINFO ()
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __ICPS_JB_RESULTINFO_H__
#define __ICPS_JB_RESULTINFO_H__

typedef struct
{
    char    ptrq[8+1];          /*平台日期*/
    char    ptlsh[10+1];          /*平台流水号*/
    char    version[8+1];          /*版本号*/
    char    appid[32+1];          /*系统标识*/
    char    function[16+1];          /*交易编码*/
    char    reqtimezone[32+1];          /*发送方所在时区*/
    char    reqtime[16+1];          /*报文发起时间*/
    char    reqmsgid[64+1];          /*请求报文唯一标示*/
    char    signtype[16+1];          /*签名算法类型*/
    char    inputcharset[16+1];          /*报文字符编码*/
    char    reserve[32+1];          /*预留域*/
    char    applyno[64+1];          /*申请单号*/
    char    certtype[2+1];          /*证件类型*/
    char    certno[32+1];          /*证件号码*/
    char    name[32+1];          /*姓名*/
    char    platformaccess[1+1];          /*本次审批结果，是否通过*/
    char    platformrefusereaso[1024+1];          /*审批不通过的原因*/
    char    platformadmit[18+1];          /*如果通过，则输出审批额度*/
    char    platformrate[8+1];          /*如果通过，则输出审批基础利率*/
    char    riskrating[32+1];          /*风险评级*/
    char    solvencyratings[32+1];          /*偿债能力评级*/
    char    changeresultreason[1024+1];          /*额度、定价变更原因*/
    char    resultcode[6+1];          /*响应码*/
    char    resultmsg[255+1];          /*响应描述*/
    char    isadmit[1+1];          /*是否推荐准入*/
    char    admitmsg[255+1];          /*准入原因*/
}ST_ICPS_JB_RESULTINFO;
#define SD_DATA  ST_ICPS_JB_RESULTINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,ptrq, 0),\
    DEFSDMEMBER(T_STRING,ptlsh, 0),\
    DEFSDMEMBER(T_STRING,version, 0),\
    DEFSDMEMBER(T_STRING,appid, 0),\
    DEFSDMEMBER(T_STRING,function, 0),\
    DEFSDMEMBER(T_STRING,reqtimezone, 0),\
    DEFSDMEMBER(T_STRING,reqtime, 0),\
    DEFSDMEMBER(T_STRING,reqmsgid, 0),\
    DEFSDMEMBER(T_STRING,signtype, 0),\
    DEFSDMEMBER(T_STRING,inputcharset, 0),\
    DEFSDMEMBER(T_STRING,reserve, 0),\
    DEFSDMEMBER(T_STRING,applyno, 0),\
    DEFSDMEMBER(T_STRING,certtype, 0),\
    DEFSDMEMBER(T_STRING,certno, 0),\
    DEFSDMEMBER(T_STRING,name, 0),\
    DEFSDMEMBER(T_STRING,platformaccess, 0),\
    DEFSDMEMBER(T_STRING,platformrefusereaso, 0),\
    DEFSDMEMBER(T_STRING,platformadmit, 0),\
    DEFSDMEMBER(T_STRING,platformrate, 0),\
    DEFSDMEMBER(T_STRING,riskrating, 0),\
    DEFSDMEMBER(T_STRING,solvencyratings, 0),\
    DEFSDMEMBER(T_STRING,changeresultreason, 0),\
    DEFSDMEMBER(T_STRING,resultcode, 0),\
    DEFSDMEMBER(T_STRING,resultmsg, 0),\
    DEFSDMEMBER(T_STRING,isadmit, 0),\
    DEFSDMEMBER(T_STRING,admitmsg, 0)
DECLAREFIELDS(SD_ICPS_JB_RESULTINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
