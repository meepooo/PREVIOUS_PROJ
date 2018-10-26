/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:AGENT_RZZT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:AGENT_RZZT (日终状态表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __AGENT_RZZT_H__
#define __AGENT_RZZT_H__
typedef struct TDB_AGENT_RZZT
{
  char   ywbh[16+1];         /*业务编号*/
              /**/
  char   ptrq[8+1];          /*平台日期*/
              /**/
  char   ywrq[8+1];          /*业务日期*/
              /**/
  char   zjmxdzzt[1+1];      /*主机明细对账状态*/
              /**/
  char   zjzzdzzt[1+1];       /*主机总对账状态*/
              /**/
  char   dsfmxdzzt[1+1];     /*第三方明细对帐状态*/
              /**/
  char   dsfzzdzzt[1+1];      /*第三方总对帐状态*/
              /**/
  double  zjzje;             /*主机对帐总金额*/
              /**/
  int    zjzbs;              /*主机对帐总笔数*/
  
  double  dsfzje;            /*第三方对帐总金额*/
              /**/
  int    dsfzbs;             /*第三方对帐总笔数*/
              /**/
  char   gdzt[1+1];          /*归档状态*/
              /**/
  char   qlzt[1+1];          /*清理状态*/
              /**/
  char   extfld1[20+1];
  char   extfld2[20+1];
}AGENT_RZZT;

#define SD_DATA  AGENT_RZZT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  zjmxdzzt, 0),\
	DEFSDMEMBER(T_STRING,  zjzzdzzt, 0),\
	DEFSDMEMBER(T_STRING,  dsfmxdzzt, 0),\
	DEFSDMEMBER(T_STRING,  dsfzzdzzt, 0),\
	DEFSDMEMBER(T_DOUBLE,  zjzje, 2),\
	DEFSDMEMBER(T_LONG,  zjzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  dsfzje, 2),\
	DEFSDMEMBER(T_LONG,  dsfzbs, 0),\
	DEFSDMEMBER(T_STRING,  gdzt, 0),\
	DEFSDMEMBER(T_STRING,  qlzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_AGENT_RZZT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_RZZT_H__*/

