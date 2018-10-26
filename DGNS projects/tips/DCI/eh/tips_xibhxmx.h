/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_xibhxmx.eh
文件描述:tips_xibhxmx;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_xibhxmx (三方协议序号表)
说    明:控制序号，用于生成协议序号
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_XIBHXMX_H__
#define __TIPS_XIBHXMX_H__

typedef struct TDB_TIPS_XIBHXMX
{
	char  zwrq[70+1];
	char  khmc[70+1];
	char  khbh[20+1];
	char  khzh[32+1];
	double  jyje ;
	char  sprq[8+1];
	char  hxrq[8+1];
	char  hxcxrq[8+1];
	char  zy[20+1];
	char  status[20+1];
	char  bz[60+1];
	char  ztm[60+1];
	char  dzlsh[15+1];
	char  jgdh[12+1];
	char  dzbz[1+1];
}SDB_TIPS_XIBHXMX;

#define SD_DATA SDB_TIPS_XIBHXMX
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_STRING,khmc,0),\
	DEFSDMEMBER(T_STRING,khbh,0),\
	DEFSDMEMBER(T_STRING,khzh,0),\
	DEFSDMEMBER(T_DOUBLE,jyje,2),\
	DEFSDMEMBER(T_STRING,sprq,0),\
	DEFSDMEMBER(T_STRING,hxrq,0),\
	DEFSDMEMBER(T_STRING,hxcxrq,0),\
	DEFSDMEMBER(T_STRING,zy,0),\
	DEFSDMEMBER(T_STRING,status,0),\
	DEFSDMEMBER(T_STRING,bz,0),\
	DEFSDMEMBER(T_STRING,ztm,0),\
	DEFSDMEMBER(T_STRING,dzlsh,0),\
	DEFSDMEMBER(T_STRING,jgdh,0),\
	DEFSDMEMBER(T_STRING,dzbz,0)

 DECLAREFIELDS(SD_TIPS_XIBHXMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_XIBHXMX_H__*/
