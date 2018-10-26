/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_FLOWCFG.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_FLOWCFG (批量流程配置表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_FLOWCFG_H__
#define __BATCH_FLOWCFG_H__
typedef struct TDB_BATCH_FLOWCFG
{
 char   flowid[32+1];/*流程标识*/
 /**/
 char   flowname[40+1];/*流程名*/
 /**/
 long    flowsn;/*执行序号*/
 /**/
  char   stepid[32+1];              /*步点标识*/
              /**/
 long    stepsn;/*步点序号*/
 /**/
  char   stepname[32+1];              /*步点名称*/
              /**/
  char   extfld1[40+1];              /*扩展字段1*/
              /**/
  char   extfld2[40+1];              /*扩展字段2*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}BATCH_FLOWCFG;

#define SD_DATA  BATCH_FLOWCFG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  flowid, 0),\
	DEFSDMEMBER(T_STRING,  flowname, 0),\
	DEFSDMEMBER(T_LONG,  flowsn, 0),\
	DEFSDMEMBER(T_STRING,  stepid, 0),\
	DEFSDMEMBER(T_LONG,  stepsn, 0),\
	DEFSDMEMBER(T_STRING,  stepname, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_FLOWCFG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FLOWCFG_H__*/
