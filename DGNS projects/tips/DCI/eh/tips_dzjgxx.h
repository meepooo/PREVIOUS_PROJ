/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_DZJGXX.eh
文件描述:tips_DZJGXX;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2014-9-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_DZJGXX (对账结果登记)
说    明:对账结果登记
用于登记对帐结果信息
本表无主键
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_DZJGXX_EH__
#define __TIPS_DZJGXX_EH__

typedef struct TDB_TIPS_DZJGXX
{
	char dzrq[8+1];
	char dzxt[1+1];
	char chkacctord[4+1];
	int  allnum1;
	double allamt1;
	int    Allnum2;
	double Allamt2;
	char dzjg[1+1];
	char byzd[60+1];
}SDB_TIPS_DZJGXX;

#define SD_DATA SDB_TIPS_DZJGXX
#define	SD_MEMBERS\
	DEFSDMEMBER(T_STRING,dzrq,0),\
	DEFSDMEMBER(T_STRING,dzxt,0),\
	DEFSDMEMBER(T_STRING,chkacctord,0),\
	DEFSDMEMBER(T_LONG,allnum1,0),\
	DEFSDMEMBER(T_DOUBLE,allamt1,2),\
	DEFSDMEMBER(T_LONG,Allnum2,0),\
	DEFSDMEMBER(T_DOUBLE,Allamt2,2),\
	DEFSDMEMBER(T_STRING,dzjg,0),\
	DEFSDMEMBER(T_STRING,byzd,0)

	DECLAREFIELDS(SD_TIPS_DZJGXX)

#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_DZJGXX_EH__*/
