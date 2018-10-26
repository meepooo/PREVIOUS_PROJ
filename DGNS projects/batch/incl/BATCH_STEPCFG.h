/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_STEPCFG.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_STEPCFG (业务步点属性配置表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_STEPCFG_H__
#define __BATCH_STEPCFG_H__
typedef struct TDB_BATCH_STEPCFG
{
  char   flowid[32+1];              /*流程标识*/
              /**/
  int    flowsn;              /*流程执行序号*/
              /*流程执行序号*/
  char   stepid[32+1];              /*步点标识*/
              /**/
  char   attribnote[40+1];              /*属性名称*/
              /**/
  char   attribid[16+1];              /*属性标识*/
              /**/
  char   attribtype[1+1];              /*属性类型*/
              /*0 运行属性 1开发属性*/
  char   attribvalue[60+1];              /*属性值*/
              /**/
}BATCH_STEPCFG;

#define SD_DATA  BATCH_STEPCFG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  flowid, 0),\
	DEFSDMEMBER(T_LONG,    flowsn, 0),\
	DEFSDMEMBER(T_STRING,  stepid, 0),\
	DEFSDMEMBER(T_STRING,  attribnote, 0),\
	DEFSDMEMBER(T_STRING,  attribid, 0),\
	DEFSDMEMBER(T_STRING,  attribtype, 0),\
	DEFSDMEMBER(T_STRING,  attribvalue, 0)


	DECLAREFIELDS(SD_BATCH_STEPCFG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_STEPCFG_H__*/
