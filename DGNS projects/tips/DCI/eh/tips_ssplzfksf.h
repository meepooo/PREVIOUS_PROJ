/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_ssplzfksf.eh
文件描述:tips_ssplzfksf;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_ssplzfksf (税收批量止付扣税费)
说    明:TIPS批量止付扣税费
用于登记止付请求数据
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_SSPLZFKSF_EH__
#define __TIPS_SSPLZFKSF_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SSPLZFKSF
{
  char   zwrq[8+1];              /*帐务日期*/
              /*帐务日期*/
  char   plzflsh[8+1];              /*批量止付流水号*/
              /*接收日期
                指系统日期*/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /*征收机关*/
  char   entrustdate[8+1];              /*委托日期*/
              /*委托日期*/
  char   stopno[8+1];              /*止付申请序号*/
              /*止付申请序号*/
  char   workdate[10+1];              /*工作日期*/
              /*工作日期
                TIPS请求->应答用*/
  char   yzwrq[8+1];              /*原帐务日期*/
              /**/
  char   ypljylsh[8+1];              /*原批量交易流水号*/
              /**/
  int    yplmxxh;              /*原批量明细序号*/
              /**/
  char   orientrustdate[8+1];              /*原委托日期*/
              /*原委托日期*/
  char   oripackno[8+1];              /*原包流水号*/
              /*原包流水号
                */
  char   oritrano[8+1];              /*原交易流水号*/
              /*原对方流水*/
  char   stoptype[1+1];              /*止付类型*/
              /*止付类型
                0-单笔
                1-整包*/
  int    allnum;              /*总笔数*/
              /*总笔数*/
  double  allamt;              /*总金额*/
              /*总金额*/
  int    num_succ;              /*成功笔数*/
              /*成功笔数*/
  double  amt_succ;              /*成功金额*/
              /*成功金额*/
  char   clrq[8+1];              /*处理日期*/
              /*处理日期
                止付成功为止付帐务日期*/
  char   clsj[8+1];              /*处理时间*/
              /*处理时间*/
  char   dqzt[1+1];              /*当前状态*/
              /*当前状态
                0-未处理
                1-处理成功
                2-处理失败

                */
  char   xym[6+1];              /*响应码*/
              /*响应码*/
  char   xyxx[60+1];              /*响应信息*/
              /*响应信息*/
  char   kzbz[8+1];              /*扩展标志*/
              /*扩展标志
                第1位：与主机对帐，0-未对帐,1-平,2-我方多,3-它方多
                第2位，与TIPS对帐，0-未对帐,1-平,2-我方多,3-它方多
                第3位：

                */
  char    stopreason[60+1];              /*止付原因*/
              /*止付原因*/
  char    byzd[60+1];              /*备用字段*/
              /*备用字段
                用于存储辅助信息*/
}SDB_TIPS_SSPLZFKSF;

#define SD_DATA SDB_TIPS_SSPLZFKSF
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,plzflsh,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,stopno,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,yzwrq,0),\
  DEFSDMEMBER(T_STRING,ypljylsh,0),\
  DEFSDMEMBER(T_LONG,yplmxxh,0),\
  DEFSDMEMBER(T_STRING,orientrustdate,0),\
  DEFSDMEMBER(T_STRING,oripackno,0),\
  DEFSDMEMBER(T_STRING,oritrano,0),\
  DEFSDMEMBER(T_STRING,stoptype,0),\
  DEFSDMEMBER(T_LONG,allnum,0),\
  DEFSDMEMBER(T_DOUBLE,allamt,2),\
  DEFSDMEMBER(T_LONG,num_succ,0),\
  DEFSDMEMBER(T_DOUBLE,amt_succ,2),\
  DEFSDMEMBER(T_STRING,clrq,0),\
  DEFSDMEMBER(T_STRING,clsj,0),\
  DEFSDMEMBER(T_STRING,dqzt,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING, stopreason,0),\
  DEFSDMEMBER(T_STRING, byzd,0)
	DECLAREFIELDS(SD_TIPS_SSPLZFKSF)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSPLZFKSF_EH__*/
