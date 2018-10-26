/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE
文 件 名:icps_jb_idcode2addr.h
文件描述:ICPS_JB_IDCODE2ADDR;结构定义数据库开发嵌C头文件
项 目 组:银行支付结算产品部
程 序 员:
发布时间:2017-08-10 15:06:30 [By qinsb@hundsun.com]
修    订:
修改时间:
************************************************************************
表    名:ICPS_JB_IDCODE2ADDR ()
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __ICPS_JB_IDCODE2ADDR_H__
#define __ICPS_JB_IDCODE2ADDR_H__

typedef struct
{
    char	id6code[6+1];         /*身份证前6位编码*/
    char	shrtnm[60+1];         /*地区名*/
    char	fullnm[100+1];        /*地区全名*/
    char	upcode[6+1];          /*上级编码*/
    char	lvl[1+1];             /*层级*/
}ST_ICPS_JB_IDCODE2ADDR;
#define SD_DATA  ST_ICPS_JB_IDCODE2ADDR
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,id6code, 0),\
    DEFSDMEMBER(T_STRING,shrtnm, 0),\
    DEFSDMEMBER(T_STRING,fullnm, 0),\
    DEFSDMEMBER(T_STRING,upcode, 0),\
    DEFSDMEMBER(T_STRING,lvl, 0)
DECLAREFIELDS(SD_ICPS_JB_IDCODE2ADDR)
#undef SD_DATA
#undef SD_MEMBERS

#endif
