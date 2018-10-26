/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_DWCPXY.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_DWCPXY (产品单位协议表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_DWCPXY_H__
#define __APP_DWCPXY_H__
typedef struct TDB_APP_DWCPXY
{
  char   dwbh[16+1];              /*单位编号*/
              /*单位编号*/
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   ywbh[16+1];              /*业务编号*/
              /*业务编号 代收付业务填代理业务编号，银保通填险种*/
  char   ywmc[40+1];              /*业务名称*/
              /**/
  char   xybh[20+1];              /*协议编号*/
              /*合同编号*/
  char   yhdm[16+1];              /*银行代码*/
              /*银行代码*/
  char   ljbs[8+1];              /*联机标识*/
              /**/
  char   zhlx[2+1];              /*账户类型*/
              /*账户类型 见数据字典 KEY=K_ZHLX*/
  char   sfbz[1+1];              /*收付标识*/
              /*1 收  ? 其?*/
  char   dszh[32+1];              /*代收账户*/
              /*代收账户*/
  char   dszhmc[80+1];              /*代收账户户名*/
              /*代收账户户名*/
  char   dfzh[32+1];              /*代付账户*/
              /*代付账户*/
  char   dfzhmc[80+1];              /*代付账户户名*/
              /*代付账户户名*/
  char   khjl[20+1];              /*客户经理*/
              /*客户经理*/
  char   lxr[20+1];              /*业务联系人*/
              /**/
  char   email[32+1];              /*业务联系EMAIL*/
              /**/
  char   lxdh[16+1];              /*业务联系电话*/
              /**/
  char   hyksrq[8+1];              /*合约开始日期*/
              /*合约开始日期*/
  char   hyjsrq[8+1];              /*合约结束日期*/
              /*合约结束日期*/
  char   bljg[16+1];              /*办理机构*/
              /*办理机构*/
  char   blgy[16+1];              /*办理柜员*/
              /*办理柜员*/
  char   blrq[16+1];              /*办理日期*/
              /*办理日期*/
  double  zhzded;              /*账户最低额度*/
              /*账户最低额度*/
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
  char   qyzt[1+1];              /*签约状态*/
              /*签约状态 0正常 1撤消*/
  char   fwrx[32+1];        /*服务热线*/
              /*服务热线*/
  char   jfbhxsmc[100+1];        /*缴费编号显示名称*/
              /*缴费编号显示名称*/
  char   khh[32+1];        /*客户号*/
              /*客户号*/
  char   nbhzhmc[100+1];        /*内部户账号名称*/
              /*内部户账号名称*/
  char   nbhzh[32+1];        /*内部户账号*/
              /*内部户账号*/
  char   sxfnbhzhmc[100+1];        /*手续费内部户账号名称*/
              /*手续费内部户账号名称*/
  char   sxfnbhzh[32+1];        /*手续费内部户账号*/
              /*手续费内部户账号*/
  char   scfs[2+1];        /*上传方式*/
              /*01-缴费平台 02-自有系统 03-线下代理*/
  char   shzt[1+1];        /*审核状态*/
              /*9-未审核 1-审核通过 2-审核拒绝*/
  char   shsj[14+1];        /*审核时间*/
              /*审核时间*/
  char   shgy[16+1];        /*审核柜员*/
              /*审核柜员*/
  char   shjg[32+1];        /*审核机构*/
              /*审核机构*/
}APP_DWCPXY;

#define SD_DATA  APP_DWCPXY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  ywmc, 0),\
	DEFSDMEMBER(T_STRING,  xybh, 0),\
	DEFSDMEMBER(T_STRING,  yhdm, 0),\
	DEFSDMEMBER(T_STRING,  ljbs, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  sfbz, 0),\
	DEFSDMEMBER(T_STRING,  dszh, 0),\
	DEFSDMEMBER(T_STRING,  dszhmc, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzhmc, 0),\
	DEFSDMEMBER(T_STRING,  khjl, 0),\
	DEFSDMEMBER(T_STRING,  lxr, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  lxdh, 0),\
	DEFSDMEMBER(T_STRING,  hyksrq, 0),\
	DEFSDMEMBER(T_STRING,  hyjsrq, 0),\
	DEFSDMEMBER(T_STRING,  bljg, 0),\
	DEFSDMEMBER(T_STRING,  blgy, 0),\
	DEFSDMEMBER(T_STRING,  blrq, 0),\
	DEFSDMEMBER(T_DOUBLE,  zhzded, 2),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qyzt, 0),\
	DEFSDMEMBER(T_STRING,  fwrx, 0),\
	DEFSDMEMBER(T_STRING,  jfbhxsmc, 0),\
	DEFSDMEMBER(T_STRING,  khh, 0),\
	DEFSDMEMBER(T_STRING,  nbhzhmc, 0),\
	DEFSDMEMBER(T_STRING,  nbhzh, 0),\
	DEFSDMEMBER(T_STRING,  sxfnbhzhmc, 0),\
	DEFSDMEMBER(T_STRING,  sxfnbhzh, 0),\
	DEFSDMEMBER(T_STRING,  scfs, 0),\
	DEFSDMEMBER(T_STRING,  shzt, 0),\
	DEFSDMEMBER(T_STRING,  shsj, 0),\
	DEFSDMEMBER(T_STRING,  shgy, 0),\
	DEFSDMEMBER(T_STRING,  shjg, 0)


	DECLAREFIELDS(SD_APP_DWCPXY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DWCPXY_H__*/
