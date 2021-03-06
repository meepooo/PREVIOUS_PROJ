/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_CPXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_CPXX (产品基础信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_CPXX_H__
#define __APP_CPXX_H__
typedef struct TDB_APP_CPXX
{
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   cpmc[40+1];              /*产品名称*/
              /*产品名称*/
  char   yybs[8+1];              /*应用标识*/
              /*应用标识*/
  char   zbjg[16+1];              /*主办机构*/
              /*主办机构*/
  char   zbgy[16+1];              /*主办柜员*/
              /*主办柜员*/
  char   khjl[20+1];              /*客户经理*/
              /*客户经理*/
  char   ywrqlx[1+1];              /*业务日期类型*/
              /*业务日期类型 1公共 2私� 默� 1*/
  char   qdkzbz[1+1];              /*渠道控制标志*/
              /*渠道控制标志 0控制 1不控� 默认1*/
  char   jgkzcs[1+1];              /*机构控制参数*/
              /*机构控制参数 见数据字典 KEY=K_JGKZC 默认 不控制*/
  char   sxfbz[1+1];              /*手续费收取标志*/
              /*手续费收取标志 0收取 1免� 默认1*/
  char   sfqybz[1+1];              /*三方签约标志*/
              /*0不需要签约，1 第三方签约，2主机签约，3 同时签�  默认 */
  char   qyms[1+1];              /*签约模式*/
              /*1  产品代码＋银行帐号  产品代码＋用户�  产品代码＋银行帐号＋用户�  默认2*/
  char   xyxljz[16+1];              /*协议序列键值*/
              /*协议序列键值 默认 K_KHCPQY*/
  char   kkfs[1+1];              /*扣款方式*/
              /*1全额扣款，2 部分扣款 默认1*/
  char   jzsx[1+1];              /*记账顺序*/
              /*0先主机后第三方，1先第三方后主机 默认0*/
  char   dzms[1+1];              /*对帐模式*/
              /*对帐模式 1银行为主 2第三方为主*/
  char   zjyyh[8+1];              /*主机应用号*/
              /**/
  char   zjzyyh[8+1];              /*主机子应用号*/
              /**/
  int    lsblts;              /*流水保留天数*/
              /*流水保留天数*/
  int    pdblts;              /*凭单保留天数*/
              /*凭单保留天数*/
  char   jyfs[1+1];              /*交易方式*/
              /*交易方式 见数据字典 KEY=K_JYFS*/
  char   rzms[1+1];              /*日志模式*/
              /*0调试  1 生� 默� 1*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[40+1];              /*扩展参数1*/
              /*扩展参数1*/
  char   extfld2[40+1];              /*扩展参数2*/
              /*扩展参数2*/
  char   cpzt[1+1];              /*产品状态*/
              /*产品状态 见数据字典 KEY=K_CPZT*/
}APP_CPXX;

#define SD_DATA  APP_CPXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  cpmc, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  zbjg, 0),\
	DEFSDMEMBER(T_STRING,  zbgy, 0),\
	DEFSDMEMBER(T_STRING,  khjl, 0),\
	DEFSDMEMBER(T_STRING,  ywrqlx, 0),\
	DEFSDMEMBER(T_STRING,  qdkzbz, 0),\
	DEFSDMEMBER(T_STRING,  jgkzcs, 0),\
	DEFSDMEMBER(T_STRING,  sxfbz, 0),\
	DEFSDMEMBER(T_STRING,  sfqybz, 0),\
	DEFSDMEMBER(T_STRING,  qyms, 0),\
	DEFSDMEMBER(T_STRING,  xyxljz, 0),\
	DEFSDMEMBER(T_STRING,  kkfs, 0),\
	DEFSDMEMBER(T_STRING,  jzsx, 0),\
	DEFSDMEMBER(T_STRING,  dzms, 0),\
	DEFSDMEMBER(T_STRING,  zjyyh, 0),\
	DEFSDMEMBER(T_STRING,  zjzyyh, 0),\
	DEFSDMEMBER(T_LONG,  lsblts, 0),\
	DEFSDMEMBER(T_LONG,  pdblts, 0),\
	DEFSDMEMBER(T_STRING,  jyfs, 0),\
	DEFSDMEMBER(T_STRING,  rzms, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  cpzt, 0)


	DECLAREFIELDS(SD_APP_CPXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPXX_H__*/
