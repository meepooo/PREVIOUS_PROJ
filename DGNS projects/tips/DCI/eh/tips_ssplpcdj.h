/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_ssplpcdj.eh
文件描述:tips_ssplpcdj;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:21 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_ssplpcdj (税收批量批次登记表)
说    明:与主机交互时登记信息.
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_SSPLPCDJ_EH__
#define __TIPS_SSPLPCDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SSPLPCDJ
{
  char   zwrq[8+1];              /*帐务日期*/
              /**/
  char   pljydm[5+1];              /*批量交易代码*/
              /**/
  char   pljylsh[8+1];              /*批量交易流水号*/
              /**/
  char   plpch[10+1];              /*批量批次号*/
              /**/
  int    pclsh;              /*批次流水号*/
              /**/
  int    ykbs;              /*应扣笔数*/
              /**/
  double  ykje;              /*应扣金额*/
              /**/
  int    skbs;              /*实扣笔数*/
              /**/
  double  skje;              /*实扣金额*/
              /**/
  int    zjsbbs;              /*主机失败笔数*/
              /**/
  char   qqzjwjm[60+1];              /*请求主机文件名*/
              /**/
  char   zjjgwjm[60+1];              /*主机结果文件名*/
              /**/
  char   xym[8+1];              /*响应码*/
              /**/
  char   xyxx[60+1];              /*响应信息*/
              /**/
  char   czbd[1+1];              /*操作步点*/
              /*当前操作步点：批量交易当前所处的批量操作
                1 初始化
                2 上送主机，等待结果
                3 结果文件提回
                4 主机返回文件处理结束*/
  char   clqsrq[8+1];              /*处理起始日期*/
              /**/
  char   clqssj[8+1];              /*处理起始时间*/
              /**/
  char   cljsrq[8+1];              /*处理结束日期*/
              /**/
  char   cljssj[8+1];              /*处理结束时间*/
              /**/
  char   byzd[60+1];              /*备用字段*/
              /**/
}SDB_TIPS_SSPLPCDJ;

#define SD_DATA SDB_TIPS_SSPLPCDJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,pljydm,0),\
  DEFSDMEMBER(T_STRING,pljylsh,0),\
  DEFSDMEMBER(T_STRING,plpch,0),\
  DEFSDMEMBER(T_LONG,pclsh,0),\
  DEFSDMEMBER(T_LONG,ykbs,0),\
  DEFSDMEMBER(T_DOUBLE,ykje,2),\
  DEFSDMEMBER(T_LONG,skbs,0),\
  DEFSDMEMBER(T_DOUBLE,skje,2),\
  DEFSDMEMBER(T_LONG,zjsbbs,0),\
  DEFSDMEMBER(T_STRING,qqzjwjm,0),\
  DEFSDMEMBER(T_STRING,zjjgwjm,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_STRING,czbd,0),\
  DEFSDMEMBER(T_STRING,clqsrq,0),\
  DEFSDMEMBER(T_STRING,clqssj,0),\
  DEFSDMEMBER(T_STRING,cljsrq,0),\
  DEFSDMEMBER(T_STRING,cljssj,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_SSPLPCDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SSPLPCDJ_EH__*/
