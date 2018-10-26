/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_wtgxdj.eh
文件描述:tips_wtgxdj;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_wtgxdj (委托关系登记)
说    明:TIPS委托关系登记
用于登记客户三方协议信息
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_WTGXDJLSLS_EH__
#define __TIPS_WTGXDJLSLS_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_WTGXDJLSLS
{
  char   protocolno[60+1];              /*协议书号*/
              /*协议书号
                征收机关、商业银行、纳税人三方签订的委托协议书号*/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /*征收机关代码*/
  char   paybkcode[12+1];              /*付款行行号*/
              /*付款行行号
                指纳税人开户行对应的清算银行的支付系统行号*/
  char   payacct[32+1];              /*付款账户*/
              /*付款账户
                “三方委托缴款协议书”中纳税人的缴款户账号*/
  char   bankprotocolno[30+1];              /*银行协议书号*/
              /*银行协议书号
                [TIPS协议登记表]中的协议书号,主表的主键
                */
  char   taxpaycode[20+1];              /*纳税人编码*/
              /*纳税人编码*/
  char   payopbkcode[12+1];              /*付款开户行行号*/
              /*付款开户行行号*/
  char   taxpayname[200+1];              /*纳税人名称*/
              /*纳税人名称*/
  char   handorgname[200+1];              /*缴款单位名称*/
              /*缴款单位名称*/
  char   khh[12+1];              /*客户号*/
              /*客户号：银行客户号
                主机返回*/
  char   wtgxzt[1+1];              /*委托关系状态*/
              /*委托关系状态：（0 正常_NORMAL|1 撤销_REVOKE|2 锁定_LOCK），缺省为0即正常。*/
  char   gxdjrq[8+1];              /*关系登记日期*/
              /*关系登记日期*/
  char   djlsh[18+1];              /*登记流水号*/
              /*登记流水号：登记委托关系综合应用前置流水号*/
  char   djdqdh[10+1];              /*登记地区代号*/
              /*登记地区代号*/
  char   djjgdh[10+1];              /*登记机构代号*/
              /*登记机构代号*/
  char   djjygy[16+1];              /*登记交易柜员*/
              /*登记交易柜员*/
  char   djzddh[16+1];              /*登记终端代号*/
              /**/
  char   xgrq[8+1];              /*修改日期*/
              /*关系撤销日期*/
  char   xglsh[18+1];              /*修改流水号*/
              /*撤销流水号：撤销委托关系综合应用前置流水号*/
  char   xgdqdh[10+1];              /*修改地区代号*/
              /*修改地区代号*/
  char   xgjgdh[10+1];              /*修改机构代号*/
              /**/
  char   xgjygy[16+1];              /*修改交易柜员*/
              /*修改交易柜员*/
  char   xgzddh[16+1];              /*修改终端代号*/
              /**/
  char   kzbz[8+1];              /*扩展标志*/
              /*扩展标志：该委托关系是否有扩展信息
                第1位：
                  帐户种类:0-对公,1-卡,2-活一本
                第2位：
                  钞汇标志:0-钞,1-汇
                  */
  char   yzbz[1+1];              /*验证标志*/
              /*校验标记0-未校验 1-验证通过 2-撤销验证*/
  char   yzxgrq[8+1];            /*验证修改日期*/
  
  char   byzd[80+1];              /*备用字段*/
              /*备用字段，用于存储额外信息*/
  char   opbankno[10+1];              /* 开户机构 */
}SDB_TIPS_WTGXDJLSLS;

#define SD_DATA  SDB_TIPS_WTGXDJLSLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,protocolno    ,0),\
	DEFSDMEMBER(T_STRING,taxorgcode    ,0),\
	DEFSDMEMBER(T_STRING,paybkcode     ,0),\
	DEFSDMEMBER(T_STRING,payacct       ,0),\
	DEFSDMEMBER(T_STRING,bankprotocolno,0),\
	DEFSDMEMBER(T_STRING,taxpaycode    ,0),\
	DEFSDMEMBER(T_STRING,payopbkcode   ,0),\
	DEFSDMEMBER(T_STRING,taxpayname    ,0),\
	DEFSDMEMBER(T_STRING,handorgname   ,0),\
	DEFSDMEMBER(T_STRING,khh           ,0),\
	DEFSDMEMBER(T_STRING,wtgxzt        ,0),\
	DEFSDMEMBER(T_STRING,gxdjrq        ,0),\
	DEFSDMEMBER(T_STRING,djlsh         ,0),\
	DEFSDMEMBER(T_STRING,djdqdh        ,0),\
	DEFSDMEMBER(T_STRING,djjgdh        ,0),\
	DEFSDMEMBER(T_STRING,djjygy        ,0),\
	DEFSDMEMBER(T_STRING,djzddh        ,0),\
	DEFSDMEMBER(T_STRING,xgrq          ,0),\
	DEFSDMEMBER(T_STRING,xglsh         ,0),\
	DEFSDMEMBER(T_STRING,xgdqdh        ,0),\
	DEFSDMEMBER(T_STRING,xgjgdh        ,0),\
	DEFSDMEMBER(T_STRING,xgjygy        ,0),\
	DEFSDMEMBER(T_STRING,xgzddh        ,0),\
	DEFSDMEMBER(T_STRING,kzbz          ,0),\
	DEFSDMEMBER(T_STRING,yzbz          ,0),\
	DEFSDMEMBER(T_STRING,yzxgrq          ,0),\
	DEFSDMEMBER(T_STRING,byzd          ,0),\
	DEFSDMEMBER(T_STRING,opbankno     ,0)

	DECLAREFIELDS(SD_TIPS_WTGXDJLSLS)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_WTGXDJ_EH__*/
