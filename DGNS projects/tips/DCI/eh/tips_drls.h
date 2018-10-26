/***********************************************************************
  版权所有:恒生电子TIPS专用前置产品组
  项目名称:TIPS专用前置产品
  版    本:V3.0
  操作系统:AIX SCO LINUX SunOS HP-UX
  数 据 库:INFORMIX
  文 件 名:tips_drls.eh
  文件描述:tips_drls;结构定义数据库开发嵌C头文件
  项 目 组:TIPS专用前置产品组
  程 序 员:
  发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
  修    订:
  修改时间:
 ************************************************************************
 表    名:tips_drls (当日流水表)
 说    明:
 ************************************************************************
 修改记录:
 修改日期:20091112
 修改内容:在付款人账号(payacct)前增加协议书号(protocolno)
 修改内容:
 修 改 人:tuql
 ************************************************************************/
#ifndef __TIPS_DRLS_H__
#define __TIPS_DRLS_H__

typedef struct TDB_TIPS_DRLS
{
	char   zwrq[8+1];              /*帐务日期*/
	/**/
	int    zhqzlsh;              /*综合前置流水号*/
	/**/
	char   jyqd[10+1];              /*交易渠道*/
	/**/
	char   workdate[8+1];              /*工作日期*/
	/**/
	char   entrustdate[8+1];              /*委托日期*/
	/**/
	char   taxorgcode[12+1];              /*征收机关代码*/
	/**/
	char   trano[8+1];              /*交易流水号*/
	/*交易流水号
	  TIPS方的流水号
	  冲正交易时为冲正申请序号*/
	char   msgno[4+1];              /*报文编号*/
	/**/
	char   entrustdate2[8+1];              /*委托日期2*/
	/*扣款交易时记录冲正交易委托日期
	  冲正交易时记录原交易的委托日期*/
	char   trano2[8+1];              /*交易流水号2*/
	/*交易流水号2
	  扣款交易时为冲正交易的冲正申请序号
	  冲正交易时为原交易流水号*/
	int    zhqzlsh2;              /*综合前置流水号2*/
	/*综合前置流水号2
	  冲正交易的流水号*/
	char   chkdate[8+1];              /*对账日期*/
	/**/
	char   chkacctord[4+1];              /*对账批次号*/
	/**/
	char   handletype[1+1];              /*经收类别*/
	/**/
	char   trecode[10+1];              /*国库代码*/
	/**/
	char   payeebankno[12+1];              /*收款行行号*/
	/**/
	char   payeeorgcode[12+1];              /*收款单位代码*/
	/**/
	char   payeeacct[32+1];              /*收款人账号*/
	/**/
	char   payeename[60+1];              /*收款人名称*/
	/**/
	char   paybkcode[12+1];              /*付款行行号*/
	/**/
	char   payopbkcode[12+1];              /*付款开户行行号*/
	/**/
	char   protocolno[60+1];              /*协议书号*/
	/**/
	char   payacct[32+1];              /*付款人账号*/
	/**/
	char   handorgname[200+1];              /*缴款单位名称*/
	/**/
	char   dfzh[32+1];              /*贷方帐号*/
	/**/
	double  jyje;              /*交易金额*/
	/**/
	char   taxvouno[18+1];              /*税票号码*/
	/**/
	char   dqdh[10+1];              /*地区代号*/
	/**/
	char   jgdh[10+1];              /*机构代号*/
	/**/
	char   jygy[16+1];              /*交易柜员*/
	/**/
	char   zddh[16+1];              /*终端代号*/
	/**/
	char   jyrq[8+1];              /*交易日期*/
	/**/
	char   jysj[8+1];              /*交易时间*/
	/**/
	char   zjrq[8+1];              /*主机日期*/
	/**/
	char   zjsj[8+1];              /*主机时间*/
	/**/
	char   zjlsh[32+1];              /*主机流水号*/
	/**/
	char   zjxym[8+1];              /*主机响应码*/
	/**/
	char   zjxyxx[60+1];              /*主机响应信息*/
	/**/
	double  sxf;              /*手续费*/
	/**/
	double  zhye;              /*账户余额*/
	/**/
	char   xym[5+1];              /*响应码*/
	/**/
	char   xyxx[60+1];              /*响应信息*/
	/**/
	char   jyzt[1+1];              /*交易状态*/
	/*0-成功
	  1-失败
	  2-被冲正
	  9-正在处理中*/
	char   dzbz[2+1];              /*对账标志*/
	/*第1位：与主机对账标志0-未对账 1-已对账  2-我方多,3-它方多
	  第2位：与TIPS对账标志0-未对账 1-已对账  2-我方多,3-它方多 */
	char   qsbz[1+1];              /*清算标志*/
	/*0-未清算 1-已清算*/
	char   kzbz[8+1];              /*扩展标志*/
	/**/
	char   taxpaycode[20+1];              /*纳税人编码*/
	/**/
	char   taxpayname[200+1];              /*纳税人名称*/
	/**/
	char   spxx[40+1];              /*税票信息*/
	/**/
	char   byzd[60+1];              /*备用字段*/
	/**/
}SDB_TIPS_DRLS;

#define SD_DATA SDB_TIPS_DRLS
#define SD_MEMBERS\
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_LONG,zhqzlsh,2),\
	DEFSDMEMBER(T_STRING,jyqd,0),\
	DEFSDMEMBER(T_STRING,workdate,0),\
	DEFSDMEMBER(T_STRING,entrustdate,0),\
	DEFSDMEMBER(T_STRING,taxorgcode,0),\
	DEFSDMEMBER(T_STRING,trano,0),\
	DEFSDMEMBER(T_STRING,msgno,0),\
	DEFSDMEMBER(T_STRING,entrustdate2,0),\
	DEFSDMEMBER(T_STRING,trano2,0),\
	DEFSDMEMBER(T_LONG,zhqzlsh2,2),\
	DEFSDMEMBER(T_STRING,chkdate,0),\
	DEFSDMEMBER(T_STRING,chkacctord,0),\
	DEFSDMEMBER(T_STRING,handletype,0),\
	DEFSDMEMBER(T_STRING,trecode,0),\
	DEFSDMEMBER(T_STRING,payeebankno,0),\
	DEFSDMEMBER(T_STRING,payeeorgcode,0),\
	DEFSDMEMBER(T_STRING,payeeacct,0),\
	DEFSDMEMBER(T_STRING,payeename,0),\
	DEFSDMEMBER(T_STRING,paybkcode,0),\
	DEFSDMEMBER(T_STRING,payopbkcode,0),\
	DEFSDMEMBER(T_STRING,protocolno,0),\
	DEFSDMEMBER(T_STRING,payacct,0),\
	DEFSDMEMBER(T_STRING,handorgname,0),\
	DEFSDMEMBER(T_STRING,dfzh,0),\
	DEFSDMEMBER(T_DOUBLE,jyje,2),\
	DEFSDMEMBER(T_STRING,taxvouno,0),\
	DEFSDMEMBER(T_STRING,dqdh,0),\
	DEFSDMEMBER(T_STRING,jgdh,0),\
	DEFSDMEMBER(T_STRING,jygy,0),\
	DEFSDMEMBER(T_STRING,zddh,0),\
	DEFSDMEMBER(T_STRING,jyrq,0),\
	DEFSDMEMBER(T_STRING,jysj,0),\
	DEFSDMEMBER(T_STRING,zjrq,0),\
	DEFSDMEMBER(T_STRING,zjsj,0),\
	DEFSDMEMBER(T_STRING,zjlsh,0),\
	DEFSDMEMBER(T_STRING,zjxym,0),\
	DEFSDMEMBER(T_STRING,zjxyxx,0),\
	DEFSDMEMBER(T_DOUBLE,sxf,2),\
	DEFSDMEMBER(T_DOUBLE,zhye,2),\
	DEFSDMEMBER(T_STRING,xym,0),\
	DEFSDMEMBER(T_STRING,xyxx,0),\
	DEFSDMEMBER(T_STRING,jyzt,0),\
	DEFSDMEMBER(T_STRING,dzbz,0),\
	DEFSDMEMBER(T_STRING,qsbz,0),\
	DEFSDMEMBER(T_STRING,kzbz,0),\
	DEFSDMEMBER(T_STRING,taxpaycode,0),\
	DEFSDMEMBER(T_STRING,taxpayname,0),\
	DEFSDMEMBER(T_STRING,spxx,0),\
	DEFSDMEMBER(T_STRING,byzd,0)

	DECLAREFIELDS(SD_TIPS_DRLS)                                                                                   
#undef SD_DATA                                                                  
#undef SD_MEMBERS 

#endif  /*end of __TIPS_DRLS_H__*/
