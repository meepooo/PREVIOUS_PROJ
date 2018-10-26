/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_pzsj.eh
文件描述:tips_pzsj;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_pzsj (凭证数据表)
说    明:凭证数据表：本地保存各类凭证信息生成信息，打印信息等
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_PZSJ_EH__
#define __TIPS_PZSJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_PZSJ
{
  char   zwrq[8+1];              /*帐务日期*/
              /**/
  int    zhqzlsh;              /*综合前置流水号*/
              /**/
  char   jyrq[8+1];              /*交易日期*/
              /**/
  char   dqdh[10+1];              /*地区代号*/
              /**/
  char   jgdh[10+1];              /*机构代号*/
              /**/
  char   jygy[16+1];              /*交易柜员*/
              /**/
  char   zddh[16+1];              /*终端代号*/
              /**/
  char   msgno[4+1];              /*报文编号*/
              /**/
  char   entrustdate[8+1];              /*委托日期*/
              /**/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /**/
  char   packno[8+1];              /*包流水号*/
              /**/
  char   trano[8+1];              /*交易流水号*/
              /**/
  char   payeebankno[12+1];              /*收款行代码*/
              /**/
  char   payeename[60+1];              /*收款人名称*/
              /**/
  char   paybkcode[12+1];              /*付款行代码*/
              /**/
  char   payopbkcode[12+1];              /*付款开户行代码*/
              /**/
  char   payacct[32+1];              /*付款账号*/
              /**/
  char   handorgname[200+1];              /*缴款单位名称*/
              /**/
  double  jyje;              /*交易金额*/
              /**/
  char   corpcode[20+1];              /*企业代码*/
              /**/
  char   taxvouno[18+1];              /*税票号码*/
              /**/
  char   taxpaycode[20+1];              /*纳税人编码*/
              /**/
  char   pzlx[1+1];              /*凭证类型*/
              /*凭证类型 1-国税 2-地税 6-社保*/
  int    dycs;              /*打印次数*/
              /**/
  char   dzbz[1+1];              /*对账标志*/
              /*与TIPS对账标志 0-未对账 1-对平*/
  char   pzsjwjm[40+1];              /*凭证数据文件名*/
              /*放在$HOME/file/tips/spxx/下
                */
  char   jyqd[10+1];
  char   zjrq[8+1];
  char   zjsj[8+1];
  char   zjlsh[32+1];
  char   jyzt[1+1];
  char   hxdzbz[1+1];
  char   qsbz[1+1];
  char   taxpayname[200+1];
  char   qspch[32+1];
  char   chkdate[8+1];
  char   chkacctord[4+1];
  char   opbankno[10+1];
  char   opbankname[60+1];
  char	 khh[12+1];
  char	 chjyje[100+1];
}SDB_TIPS_PZSJ;

#define SD_DATA SDB_TIPS_PZSJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,msgno,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,packno,0),\
  DEFSDMEMBER(T_STRING,trano,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,payeename,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,handorgname,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,corpcode,0),\
  DEFSDMEMBER(T_STRING,taxvouno,0),\
  DEFSDMEMBER(T_STRING,taxpaycode,0),\
  DEFSDMEMBER(T_STRING,pzlx,0),\
  DEFSDMEMBER(T_LONG,dycs,0),\
  DEFSDMEMBER(T_STRING,dzbz,0),\
  DEFSDMEMBER(T_STRING,pzsjwjm,0),\
  DEFSDMEMBER(T_STRING,jyqd,0),\
  DEFSDMEMBER(T_STRING,zjrq,0),\
  DEFSDMEMBER(T_STRING,zjsj,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,jyzt,0),\
  DEFSDMEMBER(T_STRING,hxdzbz,0),\
  DEFSDMEMBER(T_STRING,qsbz,0),\
  DEFSDMEMBER(T_STRING,taxpayname,0),\
  DEFSDMEMBER(T_STRING,qspch,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,opbankno,0),\
  DEFSDMEMBER(T_STRING,opbankname,0),\
  DEFSDMEMBER(T_STRING,khh,0),\
  DEFSDMEMBER(T_STRING,chjyje,0)
	DECLAREFIELDS(SD_TIPS_PZSJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_PZSJ_EH__*/
