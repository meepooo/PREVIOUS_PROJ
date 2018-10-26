/***********************************************************************
版权所有:兴业银行科技部福州研发中心
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_nbcsb.eh
文件描述:tips_nbcsb;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_nbcsb (内部参数表)
说    明:TIPS内部参数表
用于针对该业务的内部参数控制
本表有且只有一条记录
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_NBCSB_EH__
#define __TIPS_NBCSB_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_NBCSB
{
  char   workdate[8+1];              /*工作日期*/
              /**/
  char   zwrq[8+1];              /*帐务日期*/
              /*保存tips日切时中间业务平台的账务日期
                考虑到tips跨节日日切的可能
                */
  char   dqzt[1+1];              /*当前状态*/
              /*当前状态
                0-正常
                1-停止
                2-强制退出
                3-故障
                8-日切开始
                */
  char   qdqt[1+1];              /*签到签退*/
              /*签到签退
                0-签到
                1-签退*/
  char   passwd[32+1];              /*签到密码*/
              /*签到密码*/
  char   src[12+1];              /*发起节点代码*/
              /*商业银行节点代码:由TIPS给各个接入机构统一编码*/
  char   des[12+1];              /*接收节点代码*/
              /*tips节点代码
                100000000000*/
  char   bankorgcode[12+1];              /*银行支付行号*/
              /**/
  char   ver[10+1];              /*版本号*/
              /**/
  char   zdgydq[10+1];              /*自动柜员地区*/
              /**/
  char   zdgyjg[10+1];              /*自动柜员机构*/
              /**/
  char   zdgy[16+1];              /*自动柜员*/
              /*固定柜员号
                上主机交易时用到
                4位开户行号+4位固定序号*/
  char   zdfhgy[16+1];
  char   zdsqgy[16+1];
  int    plclzdbs;              /*批量处理最大笔数*/
              /*批量处理最大笔数
                单次批量处理最大笔数由ywty_ywlx表控制，本字段控制批量处理上送主机的总笔数
                */
  char   kzbz[8+1];              /*扩展标志*/
              /*扩展标志
                用于自定义扩展*/
  unknow  reserve1;              /*保留字段1*/
              /**/
  unknow  reserve2;              /*保留字段2*/
              /*保留字段2*/
  unknow  reserve3;              /*保留字段3*/
              /*保存与主机对账时中间业务平台的账务日期*/
  unknow  byzd;              /*备用字段*/
              /**/
}SDB_TIPS_NBCSB;

#define SD_DATA SDB_TIPS_NBCSB
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_STRING,dqzt,0),\
  DEFSDMEMBER(T_STRING,qdqt,0),\
  DEFSDMEMBER(T_STRING,passwd,0),\
  DEFSDMEMBER(T_STRING,src,0),\
  DEFSDMEMBER(T_STRING,des,0),\
  DEFSDMEMBER(T_STRING,bankorgcode,0),\
  DEFSDMEMBER(T_STRING,ver,0),\
  DEFSDMEMBER(T_STRING,zdgydq,0),\
  DEFSDMEMBER(T_STRING,zdgyjg,0),\
  DEFSDMEMBER(T_STRING,zdgy,0),\
  DEFSDMEMBER(T_STRING,zdfhgy,0),\
  DEFSDMEMBER(T_STRING,zdsqgy,0),\
  DEFSDMEMBER(T_LONG,plclzdbs,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  unknow  reserve1\
  unknow  reserve2\
  unknow  reserve3\
  unknow  byzd
	DECLAREFIELDS(SD_TIPS_NBCSB)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_NBCSB_EH__*/
