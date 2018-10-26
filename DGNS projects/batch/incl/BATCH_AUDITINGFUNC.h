/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_AUDITINGFUNC.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_AUDITINGFUNC (批量业务审核流程配置)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_AUDITINGFUNC_H__
#define __BATCH_AUDITINGFUNC_H__
typedef struct TDB_BATCH_AUDITINGFUNC
{
  char   auditingid[32+1];              /*审核标识*/
              /**/
  int    auditingsn;              /*序号*/
              /**/
  char   funcid[32+1];              /*函数标识*/
              /**/
  char   shsbbz[1+1];              /*审核失败标志*/
              /*审核失败标志0返回审核失败1跳过审核失败明细*/

  char   snote[32+1];              /*说明*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
             
}BATCH_AUDITINGFUNC;

#define SD_DATA  BATCH_AUDITINGFUNC
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  auditingid, 0),\
	DEFSDMEMBER(T_LONG,  auditingsn, 0),\
	DEFSDMEMBER(T_STRING,  funcid, 0),\
	DEFSDMEMBER(T_STRING,  shsbbz, 0),\
	DEFSDMEMBER(T_STRING,  snote, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_AUDITINGFUNC)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_AUDITINGFUNC_H__*/
