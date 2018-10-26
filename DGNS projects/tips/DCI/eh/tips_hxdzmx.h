/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_hxdzmx.eh
文件描述:tips_hxdzmx;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_hxdzmx 
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_HXDZMX_H__
#define __TIPS_HXDZMX_H__

typedef struct TDB_TIPS_HXDZMX
{
	char dzlx[1+1];/*对账类型*/
	char zjrq[8+1];/*核心日期*/
	char zjlsh[32+1];/*核心流水号mod by tuql 20090908*/
	char zcyhzh[32+1];/*转出银行帐号*/ 
	double jyje;/*交易金额*/
	char qzrq[8+1];/*前置日期*/
	int  qzlsh;/*前置流水号*/
	char jydqdh[10+1];/*交易地区代号*/
	char jyjgdh[10+1];/*交易机构代号*/  
	char czbz[1+1];/*被冲正标志*/
	char jydm[10+1];/*交易代码*/
}SDB_TIPS_HXDZMX;

#define SD_DATA SDB_TIPS_HXDZMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,dzlx,0),\
	DEFSDMEMBER(T_STRING,zjrq,0),\
	DEFSDMEMBER(T_STRING,zjlsh,0),\
	DEFSDMEMBER(T_STRING,zcyhzh,0),\
	DEFSDMEMBER(T_DOUBLE,jyje,0),\
  DEFSDMEMBER(T_STRING,qzrq,0),\
	DEFSDMEMBER(T_LONG,qzlsh,0),\
  DEFSDMEMBER(T_STRING,jydqdh,0),\
	DEFSDMEMBER(T_STRING,jyjgdh,0),\
	DEFSDMEMBER(T_STRING,czbz,0),\
	DEFSDMEMBER(T_STRING,jydm,0)

 DECLAREFIELDS(SD_TIPS_HXDZMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_HXDZMX_H__*/
