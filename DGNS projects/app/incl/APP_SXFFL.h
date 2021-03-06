/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_SXFFL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_SXFFL (手续费费率表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_SXFFL_H__
#define __APP_SXFFL_H__
typedef struct TDB_APP_SXFFL
{
  char   flbs[32+1];              /*费率标识*/
              /*手工输入*/
  char   xh[2+1];              /*序号*/
              /*浮动费率时多个费率分段的序号*/
  char   fdbz[1+1];              /*浮动标志*/
              /*0 不浮动，  浮� */
  char   nwkbz[1+1];              /*内外扣标志*/
              /*0外扣  1 内�  默� 0*/
  char   sxxkz[1+1];              /*上下限控制*/
              /*0 控制   不控� */
  double  sxje;              /*上限金额*/
              /**/
  double  xxje;              /*下限金额*/
              /**/
  char   jslx[1+1];              /*计算参数类型*/
              /*计算参数类型 1 金�  2百分�   如果为 ，表示手续费计算针对交易笔数的，如果是百分比，表示手续费计算针对交易金额。*/
  double  jscs;              /*计算参数*/
              /*计算参数 计算类型为1 输入金� 输入 表示1元；类型为2，输入百分� 如输入 ，表示1％*/
  char   kjbz[1+1];              /*优惠标志*/
              /*0无优惠 1 打�  金额扣� 默认0*/
  double  kjcs;              /*扣减参数*/
              /*优惠 %结尾标识折扣率 否则为扣减金额*/
  char   fdlx[1+1];              /*浮动类型*/
              /*浮动类型 1 交易笔数浮�  交易金额浮动*/
  char   ljbz[1+1];              /*累� 标志*/
              /*0 不累进   累� 默认0*/
  char   bhbz[1+1];              /*包含上限标志*/
              /*计算参数包含上限标志  1 包含上� 0包含下限*/
  char   qss[16+1];              /*起始参数*/
              /**/
  char   jss[16+1];              /*结束参数*/
              /**/
  char   sm[40+1];              /*说明*/
              /*说明*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}APP_SXFFL;

#define SD_DATA  APP_SXFFL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  flbs, 0),\
	DEFSDMEMBER(T_STRING,  xh, 0),\
	DEFSDMEMBER(T_STRING,  fdbz, 0),\
	DEFSDMEMBER(T_STRING,  nwkbz, 0),\
	DEFSDMEMBER(T_STRING,  sxxkz, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxje, 2),\
	DEFSDMEMBER(T_DOUBLE,  xxje, 2),\
	DEFSDMEMBER(T_STRING,  jslx, 0),\
	DEFSDMEMBER(T_DOUBLE,  jscs, 6),\
	DEFSDMEMBER(T_STRING,  kjbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  kjcs, 6),\
	DEFSDMEMBER(T_STRING,  fdlx, 0),\
	DEFSDMEMBER(T_STRING,  ljbz, 0),\
	DEFSDMEMBER(T_STRING,  bhbz, 0),\
	DEFSDMEMBER(T_STRING,  qss, 0),\
	DEFSDMEMBER(T_STRING,  jss, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)

	DECLAREFIELDS(SD_APP_SXFFL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_SXFFL_H__*/

