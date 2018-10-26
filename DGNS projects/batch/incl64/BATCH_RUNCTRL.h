/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_RUNCTRL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_RUNCTRL (批量业务运行控制表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_RUNCTRL_H__
#define __BATCH_RUNCTRL_H__
typedef struct TDB_BATCH_RUNCTRL
{
  char   cpdm[16+1];              /*业务编号*/
              /**/
  char   flowid[32+1];              /*流程标识*/
              /**/
  char   maxtask[5+1];              /*最大任务数*/
              /**/
  char   maxthread[5+1];              /*最大线程数*/
              /**/
  char   zjysbs[32+1];              /*主机映射标识*/
              /**/
  char   wwysbs[32+1];              /*外围映射标识*/
              /**/
  char   shbz[1+1];              /*审核标志*/
              /*0：需要审核外部文件，1：不需要审核外部文件*/
  char   taskmode[1+1];              /*任务开始方式*/
              /*1：立即，2：手动（默认为1）*/
  char   taskpri[1+1];              /* 任务优先级*/
              /*任务优先级 0-普通 1-加急 2-特急*/
  char   pzbd[2+1];              /* 配置步点*/
              /*配置步点*/
  char   extfld1[60+1];              /*扩展字段一*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}BATCH_RUNCTRL;

#define SD_DATA  BATCH_RUNCTRL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  flowid, 0),\
	DEFSDMEMBER(T_STRING,  maxtask, 0),\
	DEFSDMEMBER(T_STRING,  maxthread, 0),\
	DEFSDMEMBER(T_STRING,  zjysbs, 0),\
	DEFSDMEMBER(T_STRING,  wwysbs, 0),\
	DEFSDMEMBER(T_STRING,  shbz, 0),\
	DEFSDMEMBER(T_STRING,  taskmode, 0),\
	DEFSDMEMBER(T_STRING,  taskpri, 0),\
	DEFSDMEMBER(T_STRING,  pzbd, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)

	DECLAREFIELDS(SD_BATCH_RUNCTRL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_RUNCTRL_H__*/
