/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_ssdzmx.eh
文件描述:tips_ssdzmx;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_ssdzmx (税收对账明细)
说    明:TIPS日间和日终对账登记表--对账明细信息表
************************************************************************
修改记录:
修改日期:2014-11-05
修改内容:
修改内容:DCI改造修改头文件
修 改 人:chenxm
************************************************************************/
#ifndef __TIPS_SSDZMX_EH__
#define __TIPS_SSDZMX_EH__

typedef struct TDB_TIPS_SSDZMX
{
  char   zwrq[8+1];              /*账务日期*/
              /*前置机账务日期*/
  int    zhqzlsh;              /*综合前置流水号*/
              /*前置机综合前置流水号*/
  char   workdate[8+1];              /*工作日期*/
              /*tips工作日期*/
  char   chkdate[8+1];              /*对账日期*/
              /*原包流水号
                */
  char   chkacctord[4+1];              /*对账批次*/
              /*对账批次*/
  char   paybkcode[12+1];              /*付款行行号*/
              /**/
  char   payeebankno[12+1];              /*收款行行号*/
              /**/
  int    curpackno;              /*本包序号*/
              /*拆包处理时为当前包的序号，未拆包时本包序号为1*/
  char   payopbkcode[12+1];              /*付款开户行行号*/
              /*纳税人开户行*/
  char   payacct[32+1];              /*付款账户*/
              /*“三方委托缴款协议书”中纳税人的缴款户账号,银行端缴款业务中可能为空*/
  char   handorgname[200+1];              /*缴款单位名称*/
              /*缴款单位名称*/
  char   oritaxorgcode[12+1];              /*原征收机关代码*/
              /*即基层征收机关代码， 详见公共数据更新通知报文中的征收机关代码，TIPS填写。*/
  char   orientrustdate[8+1];              /*原委托日期*/
              /*和征收机关代码、交易流水号一起唯一标识一笔交易，TIPS填写*/
  char   oripackno[8+1];              /*原包流水号*/
              /*本交易所属包的流水号，只在包明细核对时使用。*/
  char   oritrano[8+1];              /*原交易流水号*/
              /*参考交易流水号*/
  double  traamt;              /*交易金额*/
              /*本笔扣款的总金额*/
  char   taxvouno[18+1];              /*税票号码*/
              /**/
  char   taxpayname[200+1];              /*纳税人名称*/
              /**/
  char   protocolno[60+1];              /*协议书号*/
              /**/
}SDB_TIPS_SSDZMX;

#define SD_DATA SDB_TIPS_SSDZMX
#define	SD_MEMBERS\
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_LONG,zhqzlsh,0),\
	DEFSDMEMBER(T_STRING,workdate,0),\
	DEFSDMEMBER(T_STRING,chkdate,0),\
	DEFSDMEMBER(T_STRING,chkacctord,0),\
	DEFSDMEMBER(T_STRING,paybkcode,0),\
	DEFSDMEMBER(T_STRING,payeebankno,0),\
	DEFSDMEMBER(T_LONG,curpackno,0),\
	DEFSDMEMBER(T_STRING,payopbkcode,0),\
	DEFSDMEMBER(T_STRING,payacct,0),\
	DEFSDMEMBER(T_STRING,handorgname,0),\
	DEFSDMEMBER(T_STRING,oritaxorgcode,0),\
	DEFSDMEMBER(T_STRING,orientrustdate,0),\
	DEFSDMEMBER(T_STRING,oripackno,0),\
	DEFSDMEMBER(T_STRING,oritrano,0),\
	DEFSDMEMBER(T_DOUBLE,traamt,2),\
	DEFSDMEMBER(T_STRING,taxvouno,0),\
	DEFSDMEMBER(T_STRING,taxpayname,0),\
	DEFSDMEMBER(T_STRING,protocolno,0)


	DECLAREFIELDS(SD_TIPS_SSDZMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_SSDZMX_EH__*/
