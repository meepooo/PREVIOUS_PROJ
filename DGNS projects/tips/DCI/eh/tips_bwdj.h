/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_bwdj.eh
文件描述:tips_bwdj;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_bwdj (报文登记表)
说    明:用于登记与TIPS通讯的请求、回执报文。
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_BWDJ_EH__
#define __TIPS_BWDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BWDJ
{
  char   sendorgcode[12+1];              /*发起机构代码*/
              /*征收机关代码、付款行行号*/
  char   entrustdate[8+1];              /*委托日期*/
              /*如为TIPS端发起则为委托日期；若为商业银行端发起，则为帐务日期*/
  char   packno[8+1];              /*包流水号*/
              /**/
  char   msgno[4+1];              /*报文编号*/
              /*包编号：
                3102--批量扣税费请求
                2102--批量扣税费回执
                1123--止付请求*/
  char   bwlx[1+1];              /*报文类型*/
              /*报文类型：
                1-TIPS发送包
                2-TIPS接收包
                3-TIPS止付包*/
  char   paybkcode[12+1];              /*付款行行号*/
              /**/
  char   bwwjm[60+1];              /*报文文件名*/
              /**/
  char   zwrq[8+1];              /*帐务日期*/
              /*处理报文的日期*/
  char   clsj[8+1];              /*处理时间*/
              /**/
  char   zhqzlsh[8+1];              /*综合前置流水号*/
              /*对于批量报文，只记账务成功处理时的批量交易流水号、批量止付流水号等*/
  char   dqzt[1+1];              /*当前状态*/
              /*1-发送成功
                2-发送成功,收到确认应答
                3-发送成功，收到处理结果
                4-接收成功
                5-接收成功,返回确认应答
                6-接收成功,返回处理结果
                7-被重发
                8-被置为成功
                9-发送失败
                */
  char   workdate[8+1];              /*工作日期*/
              /**/
  int    allnum;              /*总笔数*/
              /**/
  double  allamt;              /*总金额*/
              /**/
  int    succnum;              /*成功笔数*/
              /**/
  double  succamt;              /*成功金额*/
              /**/
  int    zfbs;              /*止付笔数*/
              /*退款笔数、撤销笔数*/
  double  zfje;              /*止付金额*/
              /*退款金额、撤销金额*/
  char   respmsginfo[60+1];              /*响应包信息*/
              /*工作日期8|发起节点代码12|报文标认号20|报文编号4|*/
  char   bwhdrq[8+1];              /*报文核对日期*/
              /**/
  char   bwhdzt[1+1];              /*报文核对状态*/
              /*0-不需核对 1-未核对 2-核对平 3-我方多 4-它方多 5-异常 */
  char   bwhdjg[1+1];              /*报文核对结果*/
              /*核对结果
                1-我方发起,我方多,需补发
                2-TIPS发起,TIPS多,需申请重发
                3-我方发起,TIPS多,异常
                4-TIPS发起,我方多,异常
                5-平,笔数,金额不一致,异常
                6-平,状态不一致(我方未收妥),置为收妥
                7-平,不一致+未收妥,异常*/
  char   bfrq[8+1];              /*补发日期*/
              /**/
  int    clcs;              /*处理次数*/
              /**/
}SDB_TIPS_BWDJ;

#define SD_DATA SDB_TIPS_BWDJ
#define	SD_MEMBERS \
	DEFSDMEMBER(T_STRING,sendorgcode,0),\
	DEFSDMEMBER(T_STRING,entrustdate,0),\
	DEFSDMEMBER(T_STRING,packno,0),\
	DEFSDMEMBER(T_STRING,msgno,0),\
	DEFSDMEMBER(T_STRING,bwlx,0),\
	DEFSDMEMBER(T_STRING,paybkcode,0),\
	DEFSDMEMBER(T_STRING,bwwjm,0),\
	DEFSDMEMBER(T_STRING,zwrq,0),\
	DEFSDMEMBER(T_STRING,clsj,0),\
	DEFSDMEMBER(T_STRING,zhqzlsh,0),\
	DEFSDMEMBER(T_STRING,dqzt,0),\
	DEFSDMEMBER(T_STRING,workdate,0),\
	DEFSDMEMBER(T_LONG,allnum,0),\
	DEFSDMEMBER(T_DOUBLE,allamt,2),\
	DEFSDMEMBER(T_LONG,succnum,0),\
	DEFSDMEMBER(T_DOUBLE,succamt,2),\
	DEFSDMEMBER(T_LONG,zfbs,0),\
	DEFSDMEMBER(T_DOUBLE,zfje,2),\
	DEFSDMEMBER(T_STRING,respmsginfo,0),\
	DEFSDMEMBER(T_STRING,bwhdrq,0),\
	DEFSDMEMBER(T_STRING,bwhdzt,0),\
	DEFSDMEMBER(T_STRING,bwhdjg,0),\
	DEFSDMEMBER(T_STRING,bfrq,0),\
	DEFSDMEMBER(T_LONG,clcs,0)
	
	DECLAREFIELDS(SD_TIPS_BWDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BWDJ_EH__*/
