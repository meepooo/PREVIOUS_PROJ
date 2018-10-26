/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_KHCPQY.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_KHCPQY (客户产品签约表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_KHCPQY_H__
#define __APP_KHCPQY_H__
typedef struct TDB_APP_KHCPQY
{
  char   xybh[20+1];              /*协议编号*/
              /*协议编号 由序列生成（产品信息表中配置）*/
  char   khbh[16+1];              /*客户编号*/
              /*客户编号*/
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   ywbh[16+1];              /*业务编号*/
              /*业务编号 */
  char   zhlx[2+1];              /*账户类型*/
              /*账户类型 */
  char   khjg[16+1];              /*开户机构*/
              /*签约账户开户机构*/
  char   qyzh[32+1];              /*签约账户*/
              /*签约账户*/
  char   zhhm[60+1];              /*账户户名*/
              /*账户户名*/
  char   dlzjlx[3+1];              /*代理证件类型*/
              /*代理人证件类型 见数据字典 KEY=K_ZJLX*/
  char   dlzjhm[32+1];              /*代理证件号码*/
              /*代理人证件号码*/
  char   zjlx[3+1];              /*证件类型*/
              /*证件类型 见数据字典 KEY=K_ZJLX*/
  char   zjhm[32+1];              /*证件号码*/
              /*证件号码*/
  char   qylx[1+1];              /*签约类型*/
              /*签约类型 0联机 1批量 9其他*/
  char   khjl[20+1];              /*客户经理*/
              /*客户经理*/
  char   hyksrq[8+1];              /*合约开始日期*/
              /*合约开始日期*/
  char   hyjsrq[8+1];              /*合约结束日期*/
              /*合约结束日期*/
  char   ktqd[60+1];              /*开通渠道*/
              /*开通渠道  渠道标识通过 | 后分隔， ALL表示全开通*/
  char   bljg[16+1];              /*办理机构*/
              /*办理机构*/
  char   blgy[16+1];              /*办理柜员*/
              /*办理柜员*/
  char   blrq[8+1];              /*办理日期*/
              /*办理日期*/
  char   yhh1[32+1];              /*用户号1*/
              /*用户号1*/
  char   yhh2[32+1];              /*用户号2*/
              /*用户号2*/
  char   yhh3[32+1];              /*用户号3*/
              /*用户号3*/
  char   yhmc[80+1];              /*用户名称*/
              /*用户名称(第三方用户名称)*/
  char   yhlx[16+1];              /*用户类型*/
              /*用户类型(第三方用户类型)*/
  char   yhyb[6+1];              /*用户邮编*/
              /*用户邮编(第三方用户邮编)*/
  char   yhdh[12+1];              /*用户电话*/
              /*用户电话(第三方用户电话)*/
  char   yhdz[60+1];              /*用户地址*/
              /*用户地址(第三方用户地址)*/
  char   jybz[3+1];              /*交易币种*/
              /*交易币种*/
  double  kkzdxe;              /*扣款最大限额*/
              /*扣款最大限额*/
  char   kkzq[1+1];              /*扣款周期*/
              /*扣款周期  --0-没周期，1-日，2-周，3-月，4-年*/
  char   ydkkrq[8+1];              /*约定扣款日期*/
              /*约定扣款日期*/
  char   kkzt[1+1];              /*扣款状态*/
              /*最近一次扣款状态 0  成功  1 部分成功  2-失败 */
  char   kkrq[8+1];              /*扣款日期*/
              /*最近一次扣款日期*/
  char   dxtzbz[1+1];              /*短信通知标志*/
              /*短信通知标志 0通知 1不通知*/
  double  zhzded;              /*账户最低额度*/
              /*账户最低额度*/
  char   extfld1[40+1];              /*扩展参数1*/
              /*扩展参数1*/
  char   extfld2[40+1];              /*扩展参数2*/
              /*扩展参数2*/
  char   extfld3[40+1];              /*扩展参数3*/
              /*扩展参数3*/
  char   extfld4[40+1];              /*扩展参数4*/
              /*扩展参数4*/
  char   extfld5[40+1];              /*扩展参数5*/
              /*扩展参数5*/
  char   extfld6[254+1];              /*扩展参数6*/
              /*扩展参数6*/
  char   qyzt[1+1];              /*签约状态*/
              /*签约状态 0正常 1撤消*/
}APP_KHCPQY;

#define SD_DATA  APP_KHCPQY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  xybh, 0),\
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  khjg, 0),\
	DEFSDMEMBER(T_STRING,  qyzh, 0),\
	DEFSDMEMBER(T_STRING,  zhhm, 0),\
	DEFSDMEMBER(T_STRING,  dlzjlx, 0),\
	DEFSDMEMBER(T_STRING,  dlzjhm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  qylx, 0),\
	DEFSDMEMBER(T_STRING,  khjl, 0),\
	DEFSDMEMBER(T_STRING,  hyksrq, 0),\
	DEFSDMEMBER(T_STRING,  hyjsrq, 0),\
	DEFSDMEMBER(T_STRING,  ktqd, 0),\
	DEFSDMEMBER(T_STRING,  bljg, 0),\
	DEFSDMEMBER(T_STRING,  blgy, 0),\
	DEFSDMEMBER(T_STRING,  blrq, 0),\
	DEFSDMEMBER(T_STRING,  yhh1, 0),\
	DEFSDMEMBER(T_STRING,  yhh2, 0),\
	DEFSDMEMBER(T_STRING,  yhh3, 0),\
	DEFSDMEMBER(T_STRING,  yhmc, 0),\
	DEFSDMEMBER(T_STRING,  yhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhyb, 0),\
	DEFSDMEMBER(T_STRING,  yhdh, 0),\
	DEFSDMEMBER(T_STRING,  yhdz, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_DOUBLE,  kkzdxe, 2),\
	DEFSDMEMBER(T_STRING,  kkzq, 0),\
	DEFSDMEMBER(T_STRING,  ydkkrq, 0),\
	DEFSDMEMBER(T_STRING,  kkzt, 0),\
	DEFSDMEMBER(T_STRING,  kkrq, 0),\
	DEFSDMEMBER(T_STRING,  dxtzbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  zhzded, 2),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  extfld4, 0),\
	DEFSDMEMBER(T_STRING,  extfld5, 0),\
	DEFSDMEMBER(T_STRING,  extfld6, 0),\
	DEFSDMEMBER(T_STRING,  qyzt, 0)


	DECLAREFIELDS(SD_APP_KHCPQY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_KHCPQY_H__*/

