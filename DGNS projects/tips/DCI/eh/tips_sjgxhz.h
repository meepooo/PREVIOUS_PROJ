/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_sjgxhz.eh
文件描述:tips_sjgxhz;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_sjgxhz (数据更新汇总表)
说    明:9100数据更新汇总表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_SJGXHZ_EH__
#define __TIPS_SJGXHZ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_SJGXHZ
{
  char   zwrq[8+1];              /*帐务日期*/
              /*帐务日期,对应帐务主机的帐务日期*/
  int    zhqzlsh;              /*综合前置流水号*/
              /*综合前置流水号
                平台自动生成的序号*/
  char   workdate[8+1];              /*工作日期*/
              /*TIPS的工作日期*/
  char   updatebatch[8+1];              /*更新批次*/
              /*TIPS编制，每一期更新的所有公共参数为同一个更新批次,编码规则为：年份＋序号，即YYYYXXXX*/
  int    num_101;              /*征收机关代码更新记录数*/
              /*征收机关代码更新记录数*/
  int    num_101_succ;              /*征收机关代码更新成功记录数*/
              /*征收机关代码更新成功记录数*/
  int    num_102;              /*清算银行代码更新记录数*/
              /*清算银行代码更新记录数*/
  int    num_102_succ;              /*清算银行代码更新成功记录数*/
              /*清算银行代码更新成功记录数*/
  int    num_103;              /*节点代码更新记录数*/
              /*节点代码更新记录数*/
  int    num_103_succ;              /*节点代码更新成功记录数*/
              /*节点代码更新成功记录数*/
  int    num_104;              /*国库代码更新记录数*/
              /*国库代码更新记录数*/
  int    num_104_succ;              /*国库代码更新成功记录数*/
              /*国库代码更新成功记录数*/
  int    num_105;              /*预算科目代码更新记录数*/
              /*预算科目代码更新记录数*/
  int    num_105_succ;              /*预算科目代码更新成功记录数*/
              /*预算科目代码更新成功记录数*/
  int    num_106;              /*退库原因代码更新记录数*/
              /*退库原因代码更新记录数*/
  int    num_106_succ;              /*退库原因代码更新成功记录数*/
              /*退库原因代码更新成功记录数*/
  int    num_107;              /*更正原因代码更新记录数*/
              /*更正原因代码更新记录数*/
  int    num_107_succ;              /*更正原因代码更新成功记录数*/
              /*更正原因代码更新成功记录数*/
  int    num_108;              /*税种代码更新记录数*/
              /*税种代码更新记录数*/
  int    num_108_succ;              /*税种代码更新成功记录数*/
              /*税种代码更新成功记录数*/
  int    num_109;              /*税目代码更新记录数*/
              /*税目代码更新记录数*/
  int    num_109_succ;              /*税目代码更新成功记录数*/
              /*税目代码更新成功记录数*/
  int    num_110;              /*num110更新记录数*/
              /*num110更新记录数
                备用*/
  int    num_110_succ;              /*num110更新成功记录数*/
              /*num110更新成功记录数
                备用*/
  int    num_111;              /*num111更新记录数*/
              /*num111更新记录数
                备用*/
  int    num_111_succ;              /*num111更新成功记录数*/
              /*num111更新成功记录数
                备用*/
  int    num_112;              /*num112更新记录数*/
              /*num112更新记录数
                备用*/
  int    num_112_succ;              /*num112更新成功记录数*/
              /*num112更新成功记录数
                备用*/
  char   xym[8+1];              /*响应码*/
              /*响应码*/
  char   xyxx[60+1];              /*响应信息*/
              /*响应信息*/
  int    tran_time;              /*交易耗时*/
              /*交易耗时
                单位：ms*/
  char   reserve1[50+1];              /*reserve1*/
              /*reserve1
                冲正交易时记录冲正原因*/
  char   byzd[128+1];              /*备用字段*/
              /*备用字段*/
}SDB_TIPS_SJGXHZ;

#define SD_DATA SDB_TIPS_SJGXHZ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,updatebatch,0),\
  DEFSDMEMBER(T_LONG,num_101,0),\
  DEFSDMEMBER(T_LONG,num_101_succ,0),\
  DEFSDMEMBER(T_LONG,num_102,0),\
  DEFSDMEMBER(T_LONG,num_102_succ,0),\
  DEFSDMEMBER(T_LONG,num_103,0),\
  DEFSDMEMBER(T_LONG,num_103_succ,0),\
  DEFSDMEMBER(T_LONG,num_104,0),\
  DEFSDMEMBER(T_LONG,num_104_succ,0),\
  DEFSDMEMBER(T_LONG,num_105,0),\
  DEFSDMEMBER(T_LONG,num_105_succ,0),\
  DEFSDMEMBER(T_LONG,num_106,0),\
  DEFSDMEMBER(T_LONG,num_106_succ,0),\
  DEFSDMEMBER(T_LONG,num_107,0),\
  DEFSDMEMBER(T_LONG,num_107_succ,0),\
  DEFSDMEMBER(T_LONG,num_108,0),\
  DEFSDMEMBER(T_LONG,num_108_succ,0),\
  DEFSDMEMBER(T_LONG,num_109,0),\
  DEFSDMEMBER(T_LONG,num_109_succ,0),\
  DEFSDMEMBER(T_LONG,num_110,0),\
  DEFSDMEMBER(T_LONG,num_110_succ,0),\
  DEFSDMEMBER(T_LONG,num_111,0),\
  DEFSDMEMBER(T_LONG,num_111_succ,0),\
  DEFSDMEMBER(T_LONG,num_112,0),\
  DEFSDMEMBER(T_LONG,num_112_succ,0),\
  DEFSDMEMBER(T_STRING,xym,0),\
  DEFSDMEMBER(T_STRING,xyxx,0),\
  DEFSDMEMBER(T_LONG,tran_time,0),\
  DEFSDMEMBER(T_STRING,reserve1,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_SJGXHZ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_SJGXHZ_EH__*/
