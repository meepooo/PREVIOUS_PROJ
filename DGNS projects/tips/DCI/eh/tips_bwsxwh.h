/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_bwsxwh.eh
文件描述:tips_bwsxwh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-19 14:48:58 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_bwsxwh (报文属性维护表)
说    明:TIPS报文属性维护报文编号、报文类型、批单类型、收支类型、核对标志等信息。
本表数据一般用SQL进行初始化
修改此表要授权
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_BWSXWH_EH__
#define __TIPS_BWSXWH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BWSXWH
{
  char   msgno[4+1];              /*报文编号*/
              /**/
  char   bwmc[40+1];              /*报文名称*/
              /**/
  char   bwlx[4+1];              /*报文类型*/
              /*报文类型：send-发送报文 recv-接收报文*/
  char   bwms[1+1];              /*报文模式*/
              /*tips接口的报文模式
                共有6种模式*/
  char   ywhz[4+1];              /*业务回执*/
              /*业务回执：响应报文编号(正常)*/
  char   ycydtz1[4+1];              /*异常应答通知1*/
              /*出错时返回的报文编号1*/
  char   ycydtz2[4+1];              /*异常应答通知2*/
              /**/
  char   ssdl[1+1];              /*所属队列*/
              /*报文批单性质 O-实时(单笔)报文；B-批量报文*/
  char   sfcj[1+1];              /*是否持久*/
              /*是否是持久队列 0-否 1-是*/
  char   sfgq[1+1];              /*是否过期*/
              /*0-不过期(否) 1-过期*/
  char   bwppjz[3+1];              /*报文匹配机制*/
              /*报文匹配机制
                第一位 MQ消息ID 0-否 1-是
                第二位 报文参考号 0-否 1-是
                第三位 业务要素 0-否 1-是*/
  char   byzd[40+1];              /*备用字段*/
              /**/
}SDB_TIPS_BWSXWH;

#define SD_DATA SDB_TIPS_BWSXWH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,msgno,0),\
  DEFSDMEMBER(T_STRING,bwmc,0),\
  DEFSDMEMBER(T_STRING,bwlx,0),\
  DEFSDMEMBER(T_STRING,bwms,0),\
  DEFSDMEMBER(T_STRING,ywhz,0),\
  DEFSDMEMBER(T_STRING,ycydtz1,0),\
  DEFSDMEMBER(T_STRING,ycydtz2,0),\
  DEFSDMEMBER(T_STRING,ssdl,0),\
  DEFSDMEMBER(T_STRING,sfcj,0),\
  DEFSDMEMBER(T_STRING,sfgq,0),\
  DEFSDMEMBER(T_STRING,bwppjz,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_BWSXWH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BWSXWH_EH__*/
