/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_dzbpdj.eh
文件描述:tips_dzbpdj;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_dzbpdj (对帐不平登记表)
说    明:对帐不平登记表
用于登记对帐不平时的信息及相关的挂帐处理结果信息
本表无主键
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_DZBPDJ_EH__
#define __TIPS_DZBPDJ_EH__

typedef struct TDB_TIPS_DZBPDJ
{
  char   zwrq[8+1];              /*帐务日期*/
              /*帐务日期,对应帐务主机的帐务日期*/
  int    zhqzlsh;              /*综合前置流水号*/
              /*综合前置流水号
                原交易流水号
                */
  char   workdate[8+1];              /*工作日期*/
              /*tips工作日期*/
  char   dqdh[10+1];              /*地区代号*/
              /**/
  char   jgdh[10+1];              /*机构代号*/
              /**/
  char   jygy[16+1];              /*交易柜员*/
              /**/
  char   zddh[16+1];              /*终端代号*/
              /**/
  char   dzlx[1+1];              /*对帐类型*/
              /*对帐类型
                1-与主机对帐
                2-与TIPS日间对帐
                3-与TIPS日终对帐
                4-与TIPS对银行端缴款 
                6-对帐不平挂帐处理*/
  char   zjlsh[32+1];              /*主机流水号*/
              /*主机返回的流水号*/
  char   taxorgcode[12+1];              /*征收机关代码*/
              /**/
  char   entrustdate[8+1];              /*委托日期*/
              /*第三方日期*/
  char   trano[8+1];              /*交易流水号*/
              /*第三方流水号*/
  char   chkdate[8+1];              /*对账日期*/
              /**/
  char   chkacctord[4+1];              /*对帐批次*/
              /*对帐批次号*/
  char   payeebankno[12+1];              /*收款行行号*/
              /*机构编号,交易机构
                对方多时为对方的机构号*/
  char   paybkcode[12+1];              /*付款行行号*/
              /*开户机构编号*/
  char   czyh[16+1];              /*操作员号*/
              /*操作员号*/
  char   jyqd[10+1];              /*交易渠道*/
              /*交易渠道,交易的发起者(子系统名)*/
  char   jyrq[8+1];              /*交易日期*/
              /*交易日期*/
  char   jysj[8+1];              /*交易时间*/
              /*交易时间*/
  char   jymc[50+1];              /*交易名称*/
              /*交易名称*/
  char   khmc[200+1];              /*客户名称*/
              /*客户名称*/
  char   jyzh[32+1];              /*交易账号*/
              /*交易帐号*/
  char   zhzl[2+1];              /*帐户种类*/
              /*帐户种类*/
  char   dfzh[32+1];              /*贷方帐号*/
              /*对方帐号
                指贷方帐号*/
  char   bzh[2+1];              /*币种号*/
              /*币种号*/
  double  jyje;              /*交易金额*/
              /*交易金额*/
  char   reason_info[80+1];              /*不平原因*/
              /*不平原因*/
  char   dzjg[2+1];              /*对帐结果*/
              /*对帐结果
                第1位，
                与主机对帐结果:1-平,2-本方多,3-主机多
                第2位，
                与第三方对帐结果:1-平,2-本方多,3-它方多
                */
  char   clzt[1+1];              /*处理状态*/
              /*处理状态
                0-未处理
                1-已成功挂帐
                2-挂帐失败
                5-已调帐
                6-调帐失败
                7-已处理(针对包核对)
                8-无须处理
                9-挂起,暂不处理*/
  char   jdbz[1+1];              /*借贷标志*/
              /*借贷标识
                0-借
                1-贷*/
  char   clrq[8+1];              /*处理日期*/
              /*处理日期*/
  char   clsj[8+1];              /*处理时间*/
              /*处理时间*/
  int    cllsh;              /*处理流水号*/
              /*处理流水号
                挂帐处理时的综合前置流水号*/
  char   clzjlsh[32+1];              /*处理主机流水号*/
              /*挂帐处理的主机流水*/
  char   clxx[50+1];              /*处理信息*/
              /*处理信息*/
  char   kzbz[8+1];              /*扩展标识*/
              /*扩展标识
                用于自定义扩展*/
  char   byzd[60+1];              /*备用字段*/
              /*备用字段*/
}SDB_TIPS_DZBPDJ;

#define SD_DATA SDB_TIPS_DZBPDJ
#define SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
	DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,dzlx,0),\
  DEFSDMEMBER(T_STRING,zjlsh,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,trano,0),\
  DEFSDMEMBER(T_STRING,chkdate,0),\
  DEFSDMEMBER(T_STRING,chkacctord,0),\
  DEFSDMEMBER(T_STRING,payeebankno,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,czyh,0),\
  DEFSDMEMBER(T_STRING,jyqd,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,jymc,0),\
  DEFSDMEMBER(T_STRING,khmc,0),\
  DEFSDMEMBER(T_STRING,jyzh,0),\
  DEFSDMEMBER(T_STRING,zhzl,0),\
  DEFSDMEMBER(T_STRING,dfzh,0),\
  DEFSDMEMBER(T_STRING,bzh,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_STRING,reason_info,0),\
  DEFSDMEMBER(T_STRING,dzjg,0),\
  DEFSDMEMBER(T_STRING,clzt,0),\
  DEFSDMEMBER(T_STRING,jdbz,0),\
  DEFSDMEMBER(T_STRING,clrq,0),\
  DEFSDMEMBER(T_STRING,clsj,0),\
  DEFSDMEMBER(T_LONG,cllsh,0),\
  DEFSDMEMBER(T_STRING,clzjlsh,0),\
  DEFSDMEMBER(T_STRING,clxx,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
	DEFSDMEMBER(T_STRING,byzd,0)

    DECLAREFIELDS(SD_TIPS_DZBPDJ)       
#undef SD_DATA                                                                                                      
#undef SD_MEMBERS

#endif  /*end of __TIPS_DZBPDJ_EH__*/
