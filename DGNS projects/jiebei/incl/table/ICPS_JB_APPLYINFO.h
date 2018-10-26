/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE
文 件 名:ICPS_JB_applyinfo.h
文件描述:ICPS_JB_APPLYINFO;结构定义数据库开发嵌C头文件
项 目 组:银行支付结算产品部
程 序 员:
发布时间:2017-08-10 15:06:30 [By qinsb@hundsun.com]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_APPLYINFO ()
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __ICPS_JB_APPLYINFO_H__
#define __ICPS_JB_APPLYINFO_H__

typedef struct
{
    char    ptrq[8+1];          /**/
    char    ptlsh[10+1];          /**/
    char    version[8+1];          /*版本号*/
    char    appid[32+1];          /*系统标识*/
    char    function[50+1];          /*交易编码*/
    char    reqtimezone[32+1];          /*发送方所在时区*/
    char    reqtime[16+1];          /*报文发起时间*/
    char    reqmsgid[64+1];          /*请求报文唯一标示*/
    char    signtype[16+1];          /*签名算法类型*/
    char    inputcharset[16+1];          /*报文字符编码*/
    char    reserve[32+1];          /*预留域*/
    char    applyno[64+1];          /*申请单号*/
    char    certtype[2+1];          /*证件类型*/
    char    certno[32+1];          /*证件号码*/
    char    certvalidenddate[8+1];          /*证件有效期*/
    char    name[32+1];          /*姓名*/
	char    customerno[64+1];     /*客户编号 */
    char    mobileno[32+1];          /*手机号*/
    char    occupation[1+1];				/*职业*/
    char	address[256+1];          /*详细地址*/ 
    char	city[20+1];           /*城市*/        
    char	prov[20+1];           /*省份*/        
    char	area[20+1];           /*地区*/        
    char    zmauthflag[1+1];          /*芝麻授权成功表示*/
    char    hasjbadmit[1+1];          /*是否之前就有借呗额度*/
    char    applystat[1+1];          /*请求单状态*/
    char    reqcode[6+1];          /*请求响应码*/
    char    reqmsg[255+1];          /*请求响应信息*/
    char    reqdate[8+1];          /*初审日期*/
    char    reqtime1[10+1];          /*初审时间*/
	char    reqtraceno[64+1];        /*请求流水号*/
    char    isadmit[1+1];          /*是否推荐准入*/
    char    creditno[32+1];          /*授信编号*/
    char    creditamt[18+1];          /*推荐准入时，推荐的额度*/
    char    creditrate[8+1];          /*推荐准入时，推荐的利率*/
    char    refusecode[64+1];          /*推荐拒绝时，拒绝码*/
    char    refusemsg[1024+1];          /*推荐拒绝时，拒绝原因*/
    char    respcode[6+1];          /*返回响应码*/
    char    respmsg[255+1];          /*返回响应信息*/
    char    retry[1+1];          /*是否重试 */
    char    resultstat[1+1];          /*结果单状态*/
    char    respdate[8+1];          /*返回日期*/
    char    resptime[10+1];          /*返回时间*/
}ST_ICPS_JB_APPLYINFO;
#define SD_DATA  ST_ICPS_JB_APPLYINFO
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
    DEFSDMEMBER(T_STRING,certvalidenddate, 0),\
    DEFSDMEMBER(T_STRING,name, 0),\
    DEFSDMEMBER(T_STRING,customerno, 0),\
    DEFSDMEMBER(T_STRING,mobileno, 0),\
    DEFSDMEMBER(T_STRING,occupation, 0),\
    DEFSDMEMBER(T_STRING,address, 0),\
    DEFSDMEMBER(T_STRING,city, 0),\
    DEFSDMEMBER(T_STRING,prov, 0),\
    DEFSDMEMBER(T_STRING,area, 0),\
    DEFSDMEMBER(T_STRING,zmauthflag, 0),\
    DEFSDMEMBER(T_STRING,hasjbadmit, 0),\
    DEFSDMEMBER(T_STRING,applystat, 0),\
    DEFSDMEMBER(T_STRING,reqcode, 0),\
    DEFSDMEMBER(T_STRING,reqmsg, 0),\
    DEFSDMEMBER(T_STRING,reqdate, 0),\
    DEFSDMEMBER(T_STRING,reqtime1, 0),\
	DEFSDMEMBER(T_STRING,reqtraceno, 0),\
    DEFSDMEMBER(T_STRING,isadmit, 0),\
    DEFSDMEMBER(T_STRING,creditno, 0),\
    DEFSDMEMBER(T_STRING,creditamt, 0),\
    DEFSDMEMBER(T_STRING,creditrate, 0),\
    DEFSDMEMBER(T_STRING,refusecode, 0),\
    DEFSDMEMBER(T_STRING,refusemsg, 0),\
    DEFSDMEMBER(T_STRING,respcode, 0),\
    DEFSDMEMBER(T_STRING,respmsg, 0),\
    DEFSDMEMBER(T_STRING,retry, 0),\
    DEFSDMEMBER(T_STRING,resultstat, 0),\
    DEFSDMEMBER(T_STRING,respdate, 0),\
    DEFSDMEMBER(T_STRING,resptime, 0)
DECLAREFIELDS(SD_ICPS_JB_APPLYINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif
