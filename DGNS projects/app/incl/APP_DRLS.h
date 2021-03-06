/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_DRLS.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_DRLS (平台公共流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_DRLS_H__
#define __APP_DRLS_H__
typedef struct TDB_APP_DRLS
{
  char   ptrq[8+1];              /*平台日期*/
              /*平台日期 yyyymmdd*/
  int    ptls;              /*平台流水号*/
              /*平台流水号*/
  char   ptsj[6+1];              /*平台时间*/
              /*平台时间 hhmmss*/
  char   rzbz[1+1];              /*入帐标志*/
              /*入帐标志 0入帐 1非入帐*/
  char   jylx[1+1];              /*交易类型*/
              /*交易类型 0正交易 1反交� 9其他*/
  int    yptls;              /*原平台流水号*/
              /*原平台流水号*/
  char   jyjg[16+1];              /*交易机构*/
              /*交易机构*/
  char   jygy[16+1];              /*交易柜员*/
              /*交易柜员*/
  char   qdbs[3+1];              /*渠道标识*/
              /*渠道标识 */
  char   zdsbbh[8+1];              /*终端设备编号*/
              /*终端设备编号*/
  char   yybs[8+1];              /*应用标识*/
              /*应用标识 */
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   ywbh[16+1];              /*业务编号*/
              /*业务编号*/
  char   jydm[8+1];              /*交易代码*/
              /*交易代码*/
  char   yhbh[32+1];              /*用户编号*/
              /*用户编号 如手机号*/
  char   xzbz[1+1];              /*现转标志*/
              /*现转标志  0现金 1转帐*/
  char   jdbz[1+1];              /*借贷标志*/
              /*借贷标志  见数据字典key=k_jdbz*/
  char   zhlx[2+1];              /*帐户类型*/
              /*帐户类型  见数据字典key=k_zhlx*/
  char   yhzh[32+1];              /*银行帐号*/
              /*银行帐号*/
  char   dfzh[32+1];              /*对方帐号*/
              /*对方帐号*/
  double  jyje;              /*交易金额*/
              /*交易金额*/
  double  sxf;              /*手续费*/
              /*手续费*/
  int    pcbh;              /*批次编号*/
              /*批次编号*/
  char   jyxym[8+1];              /*交易响应码*/
              /*交易响应码*/
  char   jyxyxx[60+1];              /*交易响应信息*/
              /*交易响应信息*/
  char   jyzt[1+1];              /*交易状态*/
              /*交易状态见数据字典KEY=K_JYZT*/
  char   extfld1[40+1];              /*扩展1*/
              /*扩展1*/
  char   extfld2[40+1];              /*扩展2*/
              /*扩展2*/
}APP_DRLS;

#define SD_DATA  APP_DRLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  ptsj, 0),\
	DEFSDMEMBER(T_STRING,  rzbz, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_LONG,  yptls, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  zdsbbh, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  yhbh, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
	DEFSDMEMBER(T_LONG,  pcbh, 0),\
	DEFSDMEMBER(T_STRING,  jyxym, 0),\
	DEFSDMEMBER(T_STRING,  jyxyxx, 0),\
	DEFSDMEMBER(T_STRING,  jyzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_DRLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DRLS_H__*/
