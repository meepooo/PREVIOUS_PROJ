/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_cskz.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_cskz (住建部公积金初始化参数)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_CSKZ_H__
#define __YW_GJJ_CSKZ_H__
typedef struct TDB_YW_GJJ_CSKZ
{
	char   csjz[20+1];  /*参数键值*/
		/*参数键值*/
	char   cslx[1+1];  /*参数类型*/
		/*参数类型*/
	char   cstj[8+1];  /*参数条件*/
		/*参数条件 如果类型为渠道则输入渠道标识如果为应用输入应用标识*/
	char   jdm[80+1];  /*节点名*/
		/*节点名*/
	char   jdz[40+1];  /*节点值*/
		/*节点值*/
	char   remark[40+1];  /*说明*/
		/*说明*/
	char   jzlx[1+1];  /*加载类型*/
		/*加载类型 0自动 1非自动*/
	char   whjg[16+1];  /*机构*/
		/**/
	char   whgy[16+1];  /*柜员*/
		/**/
	char   whsj[14+1];  /*时间*/
		/**/

}YW_GJJ_CSKZ;

#define SD_DATA  YW_GJJ_CSKZ
#define SD_MEMBERS \ 
	DEFSDMEMBER(T_STRING,  csjz, 0),\
	DEFSDMEMBER(T_STRING,  cslx, 0),\
	DEFSDMEMBER(T_STRING,  cstj, 0),\
	DEFSDMEMBER(T_STRING,  jdm, 0),\
	DEFSDMEMBER(T_STRING,  jdz, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  jzlx, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_YW_GJJ_CSKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CSKZ_H__*/
