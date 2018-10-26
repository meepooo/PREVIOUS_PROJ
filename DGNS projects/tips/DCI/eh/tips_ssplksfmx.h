/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_ssplksfmx.eh
文件描述:tips_ssplksfmx;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_ssplksfmx (税收批量扣税费明细表)
说    明:TIPS批量扣税费明细表
用于登记批量处理的明细记录

************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_SSPLKSFMX_EH__
#define __TIPS_SSPLKSFMX_EH__

typedef struct TDB_TIPS_SSPLKSFMX
{
  char   zwrq[8+1];              /*帐务日期*/
              /*帐务日期*/
  char   pljydm[5+1];              /*批量交易代码*/
              /**/
  char   pljylsh[8+1];              /*批量交易流水号*/
              /**/
  char   plpch[10+1];              /*批量批次号*/
              /**/
  int    plmxxh;              /*批量明细序号*/
              /*综合前置流水号*/
  int    clcs;              /*处理次数*/
              /*处理次数
                T+N交易时，对不成功的记录，每天重试一次*/
  char   workdate[8+1];              /*工作日期*/
              /*tips工作日期*/
  char   entrustdate[8+1];              /*委托日期*/
              /*委托日期
                指TIPS方的日期*/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /**/
  char   packno[8+1];              /*包流水号*/
              /*包流水号
                等同于TIPS方的批量批次号
                用于发起方唯一标识一个包的流水号，由发起方自定义*/
  int   returnterm;              /*回执期限*/
              /*要求在回执期限规定的天数内返回回执*/
  char   chkdate[8+1];              /*对账日期*/
              /**/
  char   chkacctord[4+1];              /*对账批次*/
              /**/
  char   trano[8+1];              /*交易流水号*/
              /*交易流水号*/
  char   protocolno[60+1];              /*协议书号*/
              /*签约号
                  与客户的委托关系号--三方协议号*/
  char   dfzh[32+1];              /*贷方帐号*/
              /*贷方帐号*/
  char   paybkcode[12+1];              /*付款行行号*/
              /*付款行行号*/
  char   payopbkcode[12+1];              /*付款开户行行号*/
              /*付款开户行行号
                指纳税人开户行行号*/
  char   payacct[32+1];              /*付款帐号*/
              /*付款帐号
                “三方委托缴款协议书”中纳税人的缴款户账号*/
  char   payeebankno[12+1];              /*收款行行号*/
              /**/
  char   handorgname[200+1];              /*缴款单位名称*/
              /*缴款单位名称*/
  char   taxvouno[18+1];              /*税票号码*/
              /*税票号码*/
  double  jyje;              /*交易金额*/
              /*交易金额 TraAmt*/
  double  sxf;              /*手续费*/
              /**/
  double  zhye;              /*账户余额*/
              /**/
  double  je2;              /*金额2*/
              /*金额2
                备用*/
  char   zjrq[8+1];              /*主机日期*/
              /*处理日期
                扣款时前置的自然日期*/
  char   zjsj[8+1];              /*主机时间*/
              /*处理时间*/
  char   zjlsh[32+1];              /*主机流水号*/
              /*主机流水号
                主机返回的流水号,柜员流水号*/
  char   dqdh[10+1];              /*地区代号*/
              /*地区代号*/
  char   jgdh[10+1];              /*机构代号*/
              /*机构代号*/
  char   jygy[16+1];              /*交易柜员*/
              /*交易柜员*/
  char   zddh[16+1];              /*终端代号*/
              /*终端代号*/
  char   czbd[1+1];              /*操作步点*/
              /*操作步点：该笔交易的入账状态
                0-未处理
                1-被止付
                2-被作废
                3-被冲正
                4-被抹帐
                5-主机批扣异常
                6-上送主机，等待结果返回
                7-扣款成功
                8-已处理(包括关系不存在,扣款失败等)
                */
  char   qsbz[1+1];              /*清算标志*/
              /*清算标识
                0-未清算
                1-已清算 
                 */
  char   xym[5+1];              /*响应码*/
              /*响应码*/
  char   xyxx[60+1];              /*响应信息*/
              /*响应信息*/
  char   kzbz[8+1];              /*扩展标志*/
              /*扩展标志
                第1位：与主机对帐，0-未对帐,1-平,2-我方多,3-它方多
                第2位，与TIPS对帐，0-未对帐,1-平,2-我方多,3-它方多
                第3位：与村镇主机对帐，0-未对帐,1-平,2-我方多,3-它方多
                第4位：明细是否已经校验：0-未校验,1-已校验,2-已回执                
                */
  char   taxpaycode[20+1];              /*纳税人编码*/
              /**/
  char   taxpayname[200+1];              /*纳税人名称*/
              /**/
  char   spxx[40+1];              /*税票信息*/
              /*税票信息文件名
                保存路径为$HOME/file/tips/spxx/
                */
  char   byzd[60+1];              /*备用字段*/
              /*备用字段
                用于存储辅助信息*/

}SDB_TIPS_SSPLKSFMX;

#define SD_DATA SDB_TIPS_SSPLKSFMX
#define SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,pljydm,0),\
  DEFSDMEMBER(T_STRING,pljylsh,0),\
  DEFSDMEMBER(T_STRING,plpch,0),\
  DEFSDMEMBER(T_LONG,plmxxh,0),\
  DEFSDMEMBER(T_LONG,clcs,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,packno,0),\
  DEFSDMEMBER(T_LONG,returnterm,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,trano,0),\
  DEFSDMEMBER(T_STRING,protocolno,0),\
  DEFSDMEMBER(T_STRING,dfzh,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,handorgname,0),\
  DEFSDMEMBER(T_STRING,taxvouno,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_DOUBLE,sxf,2),\
  DEFSDMEMBER(T_DOUBLE,zhye,2),\
  DEFSDMEMBER(T_DOUBLE,je2,2),\
  DEFSDMEMBER(T_STRING,zjrq,0),\
  DEFSDMEMBER(T_STRING,zjsj,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,czbd,0),\
  DEFSDMEMBER(T_STRING,qsbz,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING,taxpaycode,0),\
  DEFSDMEMBER(T_STRING,taxpayname,0),\
  DEFSDMEMBER(T_STRING,spxx,0),\
  DEFSDMEMBER(T_STRING,byzd,0)

	DECLAREFIELDS(SD_TIPS_SSPLKSFMX)
#undef SD_DATA                                                                                                      
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSPLKSFMX_EH__*/
