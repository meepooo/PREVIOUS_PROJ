/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_YWRQ.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_YWRQ (业务日期表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_YWRQ_H__
#define __APP_YWRQ_H__
typedef struct TDB_APP_YWRQ
{
  char   pkey[20+1];              /*键值*/
              /*键值  产品代码*/
  char   syywrq[8+1];              /*上一业务日期*/
              /*上一业务日期*/
  char   ywrq[8+1];              /*业务日期*/
              /*产品业务日期*/
  char   xyywrq[8+1];              /*下一业务日期*/
              /*下一业务日期*/
  char   cch[2+1];              /*场次号*/
              /*场次号*/
  int    lsh;              /*流水号*/
              /*流水号*/
  char   extfld[40+1];              /*扩展参数*/
              /*扩展参数*/
  char   sm[40+1];              /*说明*/
              /*说明*/
}APP_YWRQ;

#define SD_DATA  APP_YWRQ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_STRING,  syywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  xyywrq, 0),\
	DEFSDMEMBER(T_STRING,  cch, 0),\
	DEFSDMEMBER(T_LONG,  lsh, 0),\
	DEFSDMEMBER(T_STRING,  extfld, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0)


	DECLAREFIELDS(SD_APP_YWRQ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_YWRQ_H__*/
