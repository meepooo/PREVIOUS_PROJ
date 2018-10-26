/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_sszjhhlspz.eh
文件描述:tips_sszjhhlspz;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2010-1-4 10:55:14 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_sszjhhlspz (税收资金汇划流水表)
说    明:税收资金汇划流水表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_SSZJHHLSPZ_EH__
#define __TIPS_SSZJHHLSPZ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SSZJHHLSPZ
{
  char   zwrq[8+1];              /*帐务日期*/
              /**/
  int    zhqzlsh;              /*综合前置流水号*/
              /**/
  char   chkdate[8+1];              /*对账日期*/
              /**/
  char   chkacctord[4+1];              /*对账批次*/
              /**/
  char   paybkcode[12+1];              /*付款行行号*/
              /*清算行行号*/
  char   payeebankno[12+1];              /*收款行行号*/
              /*清算国库*/
  char   payopbkcode[12+1];              /*付款开户行行号*/
              /**/
  char   payacct[32+1];              /*付款人账号*/
              /*清算账号(对应tips_qshdj表中的dfzh)*/
  char   paybkname[60+1];              /*付款人名称*/
              /**/
  char   payeeopbankno[12+1];              /*收款开户行行号*/
              /**/
  char   payeeacct[32+1];              /*收款人账号*/
              /**/
  char   payeebankname[60+1];              /*收款人名称*/
              /**/
  char   chkaccttype[1+1];              /*对账类型*/
              /*0-日间
                1-日切*/
  int   allnum;              /*批次笔数*/
              /**/
  double  allamt;              /*批次金额*/
              /**/
  int   jybs;              /*交易笔数*/
              /**/
  double  jyje;              /*交易金额*/
              /**/
  char   addword[60+1];              /*附言*/
              /**/
  char   jyrq[8+1];              /*交易日期*/
              /**/
  char   jysj[8+1];              /*交易时间*/
              /**/
  char   qsrq[8+1];              /*清算日期*/
              /*前置帐务日期*/
  int    qslsh;              /*清算流水号*/
              /*前置帐务流水号*/
  char   ywzl[5+1];              /*业务种类*/
              /*待定*/
  int    hhcs;              /*汇划次数*/
              /*初始为第1次*/
  char   zjrq[8+1];              /*主机日期*/
              /*核心主机或支付系统日期*/
  char   zjsj[8+1];              /*主机时间*/
              /*核心主机或支付系统时间*/
  char   zjlsh[32+1];              /*主机流水号*/
              /*核心主机或支付系统流水号*/
  char   jyzt[1+1];              /*交易状态*/
              /*0-与TIPS对账失败
                1-未发送
                2-已发送
                3-发送失败
                4-发送超时
                5-划款成功
                6-划款失败
                9-正在处理中*/
  char   xym[8+1];              /*响应码*/
              /**/
  char   xyxx[60+1];              /*响应信息*/
              /**/
  char   qsbz[1+1];              /*清算标志*/
              /*0-未清算
                1-已发送
                2-清算成功
                3-清算失败
                4-手工处理*/
  char   dzbz[1+1];              /*对账标志*/
              /*0-未对账
                1-对平
                2-我方多
                3-他方多*/
  char   sgxgxx[60+1];              /*手工修改信息*/
              /*存放手工处理时的修改日期8&修改时间6&修改地区号&修改机构号&修改柜员&*/
  char   byzd[40+1];              /*备用字段*/
  char	 qspch[32+1];				/*清算批次号*/
  int	dycs;					/*打印次数*/
              /**/
  char   qjylx[1+1];
  char	 qslx[1+1];
}SDB_TIPS_SSZJHHLSPZ;

#define SD_DATA SDB_TIPS_SSZJHHLSPZ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,paybkname,0),\
  DEFSDMEMBER(T_STRING,payeeopbankno,0),\
  DEFSDMEMBER(T_STRING,payeeacct,0),\
  DEFSDMEMBER(T_STRING,payeebankname,0),\
  DEFSDMEMBER(T_STRING,chkaccttype,0),\
  DEFSDMEMBER(T_LONG,   allnum,0),\
  DEFSDMEMBER(T_DOUBLE,allamt,2),\
  DEFSDMEMBER(T_LONG,   jybs,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,addword,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,qsrq,0),\
  DEFSDMEMBER(T_LONG,qslsh,0),\
  DEFSDMEMBER(T_STRING,ywzl,0),\
  DEFSDMEMBER(T_LONG,hhcs,0),\
  DEFSDMEMBER(T_STRING,zjrq,0),\
  DEFSDMEMBER(T_STRING,zjsj,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,jyzt,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,qsbz,0),\
  DEFSDMEMBER(T_STRING,dzbz,0),\
  DEFSDMEMBER(T_STRING,sgxgxx,0),\
  DEFSDMEMBER(T_STRING,byzd,0),\
  DEFSDMEMBER(T_STRING,qspch,0),\
  DEFSDMEMBER(T_LONG,dycs,0),\
  DEFSDMEMBER(T_STRING,qjylx,0),\
  DEFSDMEMBER(T_STRING,qslx,0)
	DECLAREFIELDS(SD_TIPS_SSZJHHLSPZ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSZJHHLSPZ_EH__*/
