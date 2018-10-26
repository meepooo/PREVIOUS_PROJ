/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_noticebusiness.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_noticebusiness (住建部公积金通知存款类业务)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_NOTICEBUSINESS_H__
#define __YW_GJJ_NOTICEBUSINESS_H__
typedef struct TDB_YW_GJJ_NOTICEBUSINESS
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号*/
	char   txunitno[15+1];  /*交易机构号*/
		/*交易机构号*/
	char   jylx[1+1];  /*交易类型*/
		/*交易类型 0-通知存款支取 1-通知存款支取设定 2-通知存款支取通知取消*/
	char   currno[3+1];  /*币种*/
		/*币种*/
	char   curriden[1+1];  /*钞汇鉴别*/
		/*钞汇鉴别*/
	char   fixedacctno[32+1];  /*通知存款账号*/
		/*通知存款账号*/
	char   fixedacctname[60+1];  /*通知账户户名*/
		/*通知账户户名*/
	char   fixedacctopenbank[60+1];  /*通知账户开户机构名*/
		/*通知账户开户机构名*/
	char   noticesetserialno[20+1];  /*通知设定序号*/
		/*通知设定序号*/
	char   bookno[50+1];  /*册号*/
		/*册号 帐号为一本通时,必输*/
	char   booklistno[50+1];  /*笔号*/
		/*笔号 帐号为一本通时,必输*/
	char   noticeflag[1+1];  /*通知标志*/
		/*通知标志0：正常 1：通知已过期*/
	char   noticedrawsetdate[8+1];  /*通知设定日期*/
		/*通知设定日期*/
	char   noticedrawdate[8+1];  /*通知支取日期*/
		/*通知支取日期*/
	double   drawamt;  /*支取金额*/
		/*支取金额*/
	double   balance;  /*存单余额*/
		/*存单余额*/
	double   noticedepositamt;  /*通知存款金额*/
		/*通知存款金额*/
	char   activedacctno[32+1];  /*活期账号*/
		/*活期账号*/
	char   activedacctname[60+1];  /*活期户名*/
		/*活期户名*/
	char   activedacctopenbank[60+1];  /*活期账户开户机构名*/
		/*活期账户开户机构名*/
	char   depositperiod[1+1];  /*存期*/
		/*存期 6-1天 7-7天   */
	char   acctno[32+1];  /*存款账号*/
		/*存款账号*/
	char   drawtype[1+1];  /*支取方式*/
		/*支取方式 0：按支取通知支取 1：直接支取*/
	char   acctname[60+1];  /*存款账户户名*/
		/*存款账户户名*/
	double   noticedrawamt;  /*通知支取金额*/
		/*通知支取金额*/
	char   depositbegindate[8+1];  /*存入日期*/
		/*存入日期*/
	char   zwrq[8+1];  /*前置日期*/
		/*前置日期*/
	char   systime[6+1];  /*前置时间*/
		/*前置时间*/
	char   remark[32+1];  /*备用*/
		/*备用*/
	char   remark1[64+1];  /*备用1*/
		/*备用1*/
	char   remark2[128+1];  /*备用2*/
		/*备用2*/
	char   remark3[254+1];  /*备用3*/
		/*备用3*/
	char   remark4[254+1];  /*备用4*/
		/*备用4*/

}YW_GJJ_NOTICEBUSINESS;

#define SD_DATA  YW_GJJ_NOTICEBUSINESS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctno, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctname, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  noticesetserialno, 0),\
	DEFSDMEMBER(T_STRING,  bookno, 0),\
	DEFSDMEMBER(T_STRING,  booklistno, 0),\
	DEFSDMEMBER(T_STRING,  noticeflag, 0),\
	DEFSDMEMBER(T_STRING,  noticedrawsetdate, 0),\
	DEFSDMEMBER(T_STRING,  noticedrawdate, 0),\
	DEFSDMEMBER(T_DOUBLE,  drawamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  balance, 2),\
	DEFSDMEMBER(T_DOUBLE,  noticedepositamt, 2),\
	DEFSDMEMBER(T_STRING,  activedacctno, 0),\
	DEFSDMEMBER(T_STRING,  activedacctname, 0),\
	DEFSDMEMBER(T_STRING,  activedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  depositperiod, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  drawtype, 0),\
	DEFSDMEMBER(T_STRING,  acctname, 0),\
	DEFSDMEMBER(T_DOUBLE,  noticedrawamt, 2),\
	DEFSDMEMBER(T_STRING,  depositbegindate, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_NOTICEBUSINESS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_NOTICEBUSINESS_H__*/
