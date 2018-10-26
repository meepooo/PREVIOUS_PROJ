/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_ssdzplt.eh
文件描述:tips_ssdzplt;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_ssdzplt (税收对账批量头表)
说    明:TIPS日间和日终对账登记表--对账批量头表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_SSDZPLT_EH__
#define __TIPS_SSDZPLT_EH__

typedef struct TDB_TIPS_SSDZPLT
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
              /*付款行行号
                付款开户行行号对应的清算行号
                对帐时以此为单位*/
  char   payeebankno[12+1];              /*收款行行号*/
              /*清算国库支付行号*/
  char   priorchkacctord[4+1];              /*上一对账批次*/
              /*该字段的值取本次对账的上一批对账的批次的值，仅当当日首批对账，该值等于本次对账批次的值。*/
  char   chkaccttype[1+1];              /*对账类型*/
              /*0 日间
                1 日切*/
  int    allnum;              /*总笔数*/
              /*参加本次对账的缴款书总笔数*/
  double  allamt;              /*总金额*/
              /*参加本次对账的缴款书总金额*/
  int    childpacknum;              /*子包总数*/
              /**/
  int    curpackno;              /*本包序号*/
              /*拆包处理时为当前包的序号，未拆包时本包序号为1*/
  int    curpacknum;              /*本包笔数*/
              /**/
  double  curpackamt;              /*本包金额*/
              /**/
}SDB_TIPS_SSDZPLT;

#define SD_DATA SDB_TIPS_SSDZPLT
#define SD_MEMBERS\
    DEFSDMEMBER(T_STRING,zwrq,0),\
    DEFSDMEMBER(T_LONG,zhqzlsh,0),\
    DEFSDMEMBER(T_STRING,workdate,0),\
    DEFSDMEMBER(T_STRING,chkdate,0),\
    DEFSDMEMBER(T_STRING,chkacctord,0),\
    DEFSDMEMBER(T_STRING,paybkcode,0),\
    DEFSDMEMBER(T_STRING,payeebankno,0),\
    DEFSDMEMBER(T_STRING,priorchkacctord,0),\
    DEFSDMEMBER(T_STRING,chkaccttype,0),\
    DEFSDMEMBER(T_LONG,allnum,0),\
    DEFSDMEMBER(T_DOUBLE,allamt,2),\
    DEFSDMEMBER(T_LONG,childpacknum,0),\
    DEFSDMEMBER(T_LONG,curpackno,0),\
    DEFSDMEMBER(T_LONG,curpacknum,0),\
    DEFSDMEMBER(T_DOUBLE,curpackamt,2),\

    DECLAREFIELDS(SD_TIPS_SSDZPLT)

#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __TIPS_SSDZPLT_EH__*/
