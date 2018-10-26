/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_RWJKB.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_RWJKB (应用任务监控表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_RWJKB_H__
#define __APP_RWJKB_H__
typedef struct TDB_APP_RWJKB
{
  char   yybs[8+1];              /*应用标识*/
              /*应用标识*/
  char   yymc[40+1];              /*应用名称*/
              /*应用名称*/
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   cpmc[40+1];              /*产品名称*/
              /*产品名称*/
  char   rwmc[50+1];              /*任务名称*/
              /*任务名称*/
  char   jydm[8+1];              /*交易代码*/
              /*交易代码*/
  char   jymc[40+1];              /*交易名称*/
              /*交易名称*/
  int    ptls;              /*平台流水*/
              /*平台流水*/
  char   ptrq[8+1];              /*平台日期*/
              /*平台日期*/
  char   jyjg[16+1];              /*交易机构*/
              /*提醒机构*/
  char   jygy[16+1];              /*交易柜员*/
              /*提醒柜员*/
  char   qdbs[3+1];              /*渠道标识*/
              /*渠道标识*/
  char   kssj[19+1];              /*开始时间*/
              /*开始时间戳*/
  char   jssj[19+1];              /*结束时间*/
              /*结束时间戳*/
  int    yxsj;              /*运行时间*/
              /*运行毫秒数*/
  int    zxcs;              /*运行次数*/
              /*运行次数*/
  char   zxzt[1+1];              /*执行状态*/
              /*执行状态0:执行成功1:执行失败9:执行中*/
  char   xym[5+1];              /*响应代码*/
              /*响应代码*/
  char   xyxx[60+1];              /*响应信息*/
              /*响应信息*/
  char   extfld1[20+1];              /*扩展字段1*/
              /*扩展1*/
  char   extfld2[20+1];              /*扩展字段2*/
              /*扩展2*/
}APP_RWJKB;

#define SD_DATA  APP_RWJKB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  yymc, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  cpmc, 0),\
	DEFSDMEMBER(T_STRING,  rwmc, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  jymc, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  kssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_LONG,  yxsj, 0),\
	DEFSDMEMBER(T_LONG,  zxcs, 0),\
	DEFSDMEMBER(T_STRING,  zxzt, 0),\
	DEFSDMEMBER(T_STRING,  xym, 0),\
	DEFSDMEMBER(T_STRING,  xyxx, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_RWJKB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_RWJKB_H__*/

