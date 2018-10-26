/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_pljydj.eh
文件描述:tips_pljydj;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:21 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_pljydj (批量交易登记表)
说    明:登记批量扣税(费)、支付等交易信息记录。
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_PLJYDJ_EH__
#define __TIPS_PLJYDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_PLJYDJ
{
  char   zwrq[8+1];              /*帐务日期*/
              /**/
  char   pljydm[5+1];              /*批量交易代码*/
              /*批量交易代码：
                GSPKS--国税批扣税
                DSPKS--地税批扣税
                SBPKF--社保批扣费
                CZPZF--财政批支付*/
  char   pljylsh[8+1];              /*批量交易流水号*/
              /*综合前置流水号*/
  int    pczbs;              /*批次总笔数*/
              /*一个批量可能对应多个批次，如主机规定第批只送300笔,而一个批量有1000笔*/
  char   entrustdate[8+1];              /*委托日期*/
              /**/
  char   orgcode[12+1];              /*发起机关代码*/
              /*征收机关代码、社保机构编号或财政机关代码*/
  char   packno[8+1];              /*包流水号*/
              /**/
  char   workdate[8+1];              /*工作日期*/
              /**/
  int    allnum;              /*总笔数*/
              /**/
  double  allamt;              /*总金额*/
              /**/
  char    handletype[1+1];              /*经收类别*/
              /*经收类别,征收机关填写*/
  char   payeebankno[12+1];              /*收款行行号*/
              /**/
  char   payeeorgcode[12+1];              /*收款单位代码*/
              /**/
  char    payeeacct[32+1];              /*收款人账号*/
              /**/
  char   payeename[60+1];              /*收款人名称*/
              /**/
  char   paybkcode[12+1];              /*付款行行号*/
              /**/
  char   chkdate[8+1];              /*对账日期*/
              /**/
  char   chkacctord[4+1];              /*对账批次*/
              /**/
  int    rzzbs;              /*入帐总笔数*/
              /**/
  double  rzzje;              /*入帐总金额*/
              /**/
  int    zfzbs;              /*止付总笔数*/
              /*当为财政支付令时，填退款总笔数*/
  double  zfzje;              /*止付总金额*/
              /*当为财政支付令时，填退款总金额*/
  char   xym[5+1];              /*响应码*/
              /**/
  char   xyxx[60+1];              /*响应信息*/
              /**/
  char   czbd[1+1];              /*操作步点*/
              /*操作步点
                当批量交易代码为SWPKS或SBPKF时
                1-数据落地(3102TIPS转发批量扣税请求、银行->TIPS9121通用确认应答处理)
                2-数据准备
                3-数据提交
                4-数据提回
                5-结果处理
                6-结果返回(TIPS 2102批量扣税回执、银行 9121通用确认应答)
                7-处理结果通知(收到9122明细错误通知)*/
  char   wcbz[1+1];              /*完成标志*/
              /*完成标志
                0-未处理
                1-处理失败
                2-处理成功
                3-被止付
                4-被作废
                5-被部分退款
                6-被全额退款
                9-处理中*/
  char   clqsrq[8+1];              /*处理起始日期*/
              /**/
  char   clqssj[8+1];              /*处理超始时间*/
              /**/
  char   cljsrq[8+1];              /*处理结束日期*/
              /**/
  char   cljssj[8+1];              /*处理结束时间*/
              /**/
  char   kzbz[8+1];              /*扩展标志*/
              /*扩展标志
                当批量交易代码为SWPKS或SBPKF时：
                第1位：与主机对帐，0-未对帐,1-平,2-我方多,3-它方多
                第2位，与TIPS对帐，0-未对帐,1-平,2-我方多,3-它方多
                第3位：0-未清算，1-已清算
                */
  char   byzd[60+1];              /*备用字段*/
              /**/
}SDB_TIPS_PLJYDJ;

#define SD_DATA SDB_TIPS_PLJYDJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,pljydm,0),\
  DEFSDMEMBER(T_STRING,pljylsh,0),\
  DEFSDMEMBER(T_LONG,pczbs,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,orgcode,0),\
  DEFSDMEMBER(T_STRING,packno,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_LONG,allnum,0),\
  DEFSDMEMBER(T_DOUBLE,allamt,2),\
  DEFSDMEMBER(T_STRING, handletype,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,payeeorgcode,0),\
  DEFSDMEMBER(T_STRING, payeeacct,0),\
  DEFSDMEMBER(T_STRING,payeename,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_LONG,rzzbs,0),\
  DEFSDMEMBER(T_DOUBLE,rzzje,2),\
  DEFSDMEMBER(T_LONG,zfzbs,0),\
  DEFSDMEMBER(T_DOUBLE,zfzje,2),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,czbd,0),\
  DEFSDMEMBER(T_STRING,wcbz,0),\
  DEFSDMEMBER(T_STRING,clqsrq,0),\
  DEFSDMEMBER(T_STRING,clqssj,0),\
  DEFSDMEMBER(T_STRING,cljsrq,0),\
  DEFSDMEMBER(T_STRING,cljssj,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_PLJYDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_PLJYDJ_EH__*/
