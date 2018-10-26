/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_trepayfileinfo_drc.h
文件描述:tips_trepayfileinfo_eh;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2017-5-31 15:56:00 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_trepayfileinfo_drc.h
说    明:TIPS国库集中支付文件信息
用于登记TIPS集中支付文件信息
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_TREPAYFILEINFO_DRC_EH__
#define __TIPS_TREPAYFILEINFO_DRC_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_TREPAYFILEINFO
{
  char   trandate[8+1];
  long   transeq;
  char   packno[8+1];
  char   brc[16+1];
  char   tel[16+1];
  char   systime[6+1];
  char   step[2+1];
  char   state[1+1];
  char   filetype[1+1];
  char   filename[256+1];
  long   totalnum;
  double totalamt;
  char   trecode[10+1];
  char   finorgcode[12+1];
  char   payoutvoutype[1+1];
  char   paytype[1+1];
  char   vouno[20+1];
  char   voudate[8+1];
  char   payacct[32+1];
  char   payname[200+1];
  char   payaddr[200+1];
  char   payeeacct[32+1];
  char   payeename[200+1];
  char   payeeaddr[200+1];
  char   payeeopbk[12+1];
  char   addword[200+1];
  char   budgettype[1+1];
  char   trimsign[1+1];
  char   ofyear[4+1];
  char   resultmsg[200+1];
  char   remark1[10+1];
  char   remark2[20+1];
  char   remark3[50+1];
  char   remark4[100+1];
  char   remark5[200+1];
}SDB_TIPS_TREPAYFILEINFO;

#define SD_DATA SDB_TIPS_TREPAYFILEINFO
#define	SD_MEMBERS\
  DEFSDMEMBER(T_STRING,trandate,0),\
  DEFSDMEMBER(T_LONG,transeq,2),\
  DEFSDMEMBER(T_STRING,packno,0),\
  DEFSDMEMBER(T_STRING,brc,0),\
  DEFSDMEMBER(T_STRING,tel,0),\
  DEFSDMEMBER(T_STRING,state,0),\
  DEFSDMEMBER(T_STRING,step,0),\
  DEFSDMEMBER(T_STRING,state,0),\
  DEFSDMEMBER(T_STRING,filetype,0),\
  DEFSDMEMBER(T_STRING,filename,0),\
  DEFSDMEMBER(T_LONG,totalnum,2),\
  DEFSDMEMBER(T_DOUBLE,totalamt,2),\
  DEFSDMEMBER(T_STRING,trecode,0),\
  DEFSDMEMBER(T_STRING,finorgcode,0),\
  DEFSDMEMBER(T_STRING,payoutvoutype,0),\
  DEFSDMEMBER(T_STRING,paytype,0),\
  DEFSDMEMBER(T_STRING,vouno,0),\
  DEFSDMEMBER(T_STRING,voudate,0),\
  DEFSDMEMBER(T_STRING,payacct,0),\
  DEFSDMEMBER(T_STRING,payname,0),\
  DEFSDMEMBER(T_STRING,payaddr,0),\
  DEFSDMEMBER(T_STRING,payeeacct,0),\
  DEFSDMEMBER(T_STRING,payeename,0),\
  DEFSDMEMBER(T_STRING,payeeaddr,0),\
  DEFSDMEMBER(T_STRING,payeeopbk,0),\
  DEFSDMEMBER(T_STRING,addword,0),\
  DEFSDMEMBER(T_STRING,budgettype,0),\
  DEFSDMEMBER(T_STRING,trimsign,0),\
  DEFSDMEMBER(T_STRING,ofyear,0),\
  DEFSDMEMBER(T_STRING,resultmsg,0),\
  DEFSDMEMBER(T_STRING,remark1,0),\
  DEFSDMEMBER(T_STRING,remark2,0),\
  DEFSDMEMBER(T_STRING,remark3,0),\
  DEFSDMEMBER(T_STRING,remark4,0),\
  DEFSDMEMBER(T_STRING,remark5,0)
  DECLAREFIELDS(SD_TIPS_TREPAYFILEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_TREPAYFILEINFO_DRC_EH__*/
