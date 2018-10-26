/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_zygsbw.eh
文件描述:tips_zygsbw;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_zygsbw (自由格式报文)
说    明:自由格式报文
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_ZYGSBW_EH__
#define __TIPS_ZYGSBW_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_ZYGSBW
{
  char   zwrq[8+1];              /*帐务日期*/
              /*帐务日期,对应帐务主机的帐务日期*/
  int    zhqzlsh;              /*综合前置流水号*/
              /*综合前置流水号
                平台自动生成的序号*/
  char   workdate[8+1];              /*工作日期*/
              /*交易耗时
                单位：ms*/
  char   msgtype[1+1];              /*消息类型*/
              /*消息类型
                1-接收 2-发送
                */
  char   srcnodecode[12+1];              /*源节点代码*/
              /*源节点代码
                发起自由格式报文交易的原始节点代码*/
  char   desnodecode[12+1];              /*目的节点代码*/
              /*目的节点代码
                接收自由格式报文交易的最终目的节点代码*/
  char   sendorgcode[12+1];              /*发起机构代码*/
              /*发起机构代码
                信息发起者机构代码。若该自由格式报文最终发起方为机构，则该项必填*/
  char   rcvorgcode[12+1];              /*接收机构代码*/
              /*接收机构代码
                信息接收者机构代码。若该自由格式报文最终接受方为机构，则该项必填*/
  char   ydbz[1+1];              /*阅读标志*/
              /*阅读标志
                接收报文的阅读状态：
                0 未阅读
                1 已阅读
                */
  char   content[2048+1];              /*内容*/
              /*内容
                自由格式内容*/
  char   jyrq[8+1];              /*交易日期*/
              /*交易日期*/
  char   jysj[8+1];              /*交易时间*/
              /*交易时间*/
  char   dqdh[10+1];              /*地区代号*/
              /*地区代号
                发送时，为发送报文的操作员地区代号
                接收时，为第一个阅读报文的操作员地区代号
                */
  char   jgdh[10+1];              /*机构代号*/
              /*机构代号
                发送时，为发送报文的操作员机构代号
                接收时，为第一个阅读报文的操作员机构代号
                */
  char   jygy[16+1];              /*交易柜员*/
              /*操作员号
                发送时，为发送报文的操作员代号
                接收时，为第一个阅读报文的操作员代号*/
  char   zddh[16+1];              /*终端代号*/
              /**/
  char   byzd[128+1];              /*备用字段*/
              /*备用字段*/
}SDB_TIPS_ZYGSBW;

#define SD_DATA SDB_TIPS_ZYGSBW
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,msgtype,0),\
  DEFSDMEMBER(T_STRING,srcnodecode,0),\
  DEFSDMEMBER(T_STRING,desnodecode,0),\
  DEFSDMEMBER(T_STRING,sendorgcode,0),\
  DEFSDMEMBER(T_STRING,rcvorgcode,0),\
  DEFSDMEMBER(T_STRING,ydbz,0),\
  DEFSDMEMBER(T_STRING,content,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_ZYGSBW)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_ZYGSBW_EH__*/
