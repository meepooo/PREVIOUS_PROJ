/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_dbsfk.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_dbsfk (住建部公积金单笔收付款表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_DBSFK_H__
#define __YW_GJJ_DBSFK_H__
typedef struct TDB_YW_GJJ_DBSFK
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号*/
	char   txunitno[15+1];  /*交易机构号*/
		/*交易机构号*/
	char   sfkbz[1+1];  /*收付款标志*/
		/*收付款标志*/
	char   currno[3+1];  /*币种*/
		/*币种*/
	char   curriden[1+1];  /*钞汇鉴别*/
		/*钞汇鉴别*/
	char   settletype[1+1];  /*结算模式*/
		/*结算模式*/
	char   bustype[6+1];  /*业务类型*/
		/*业务类型*/
	char   deacctno[32+1];  /*付方账号*/
		/*付方账号*/
	char   deacctname[60+1];  /*付方户名*/
		/*付方户名*/
	char   deacctclass[1+1];  /*付方账户类别*/
		/*付方账户类别*/
	char   debankname[60+1];  /*付方行名*/
		/*付方行名*/
	char   dechgno[12+1];  /*付方联行号*/
		/*付方联行号*/
	char   debankclass[1+1];  /*付方账户行别*/
		/*付方账户行别*/
	char   conagrno[32+1];  /*多方协议号*/
		/*多方协议号*/
	double   capamt;  /*本金发生额*/
		/*本金发生额*/
	char   deintacctno[32+1];  /*付息户账号*/
		/*付息户账号*/
	char   deintacctname[60+1];  /*付息户户名*/
		/*付息户户名*/
	char   deintacctclass[1+1];  /*付息户类别*/
		/*付息户类别*/
	char   deintcracct[32+1];  /*利息收方账号*/
		/*利息收方账号*/
	double   intamt;  /*利息发生额*/
		/*利息发生额*/
	char   cracctno[32+1];  /*收方账号*/
		/*收方账号*/
	char   cracctname[60+1];  /*收方户名*/
		/*收方户名*/
	char   cracctclass[1+1];  /*收方账户类别*/
		/*收方账户类别*/
	char   crbankclass[1+1];  /*收方账户行别*/
		/*收方账户行别*/
	char   crbankname[60+1];  /*收方行名*/
		/*收方行名*/
	char   crchgno[12+1];  /*收方联行号*/
		/*收方联行号*/
	double   amt;  /*金额*/
		/*金额*/
	char   refacctno[32+1];  /*业务明细账号*/
		/*业务明细账号*/
	char   refseqno1[32+1];  /*业务明细流水号1*/
		/*业务明细流水号1*/
	char   refseqno2[32+1];  /*业务明细流水号2*/
		/*业务明细流水号2*/
	char   zwrq[8+1];  /*前置日期*/
		/*前置日期*/
	char   systime[6+1];  /*前置时间*/
		/*前置时间*/
	char   remark[32+1];  /*备注*/
		/*备注*/
	char   remark1[64+1];  /*备用1*/
		/*备用1*/
	char   remark2[128+1];  /*备注2*/
		/*备注2*/
	char   remark3[254+1];  /*备用3*/
		/*备用3*/
	char   remark4[254+1];  /*备用4*/
		/*备用4*/

}YW_GJJ_DBSFK;

#define SD_DATA  YW_GJJ_DBSFK
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  sfkbz, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  settletype, 0),\
	DEFSDMEMBER(T_STRING,  bustype, 0),\
	DEFSDMEMBER(T_STRING,  deacctno, 0),\
	DEFSDMEMBER(T_STRING,  deacctname, 0),\
	DEFSDMEMBER(T_STRING,  deacctclass, 0),\
	DEFSDMEMBER(T_STRING,  debankname, 0),\
	DEFSDMEMBER(T_STRING,  dechgno, 0),\
	DEFSDMEMBER(T_STRING,  debankclass, 0),\
	DEFSDMEMBER(T_STRING,  conagrno, 0),\
	DEFSDMEMBER(T_DOUBLE,  capamt, 2),\
	DEFSDMEMBER(T_STRING,  deintacctno, 0),\
	DEFSDMEMBER(T_STRING,  deintacctname, 0),\
	DEFSDMEMBER(T_STRING,  deintacctclass, 0),\
	DEFSDMEMBER(T_STRING,  deintcracct, 0),\
	DEFSDMEMBER(T_DOUBLE,  intamt, 2),\
	DEFSDMEMBER(T_STRING,  cracctno, 0),\
	DEFSDMEMBER(T_STRING,  cracctname, 0),\
	DEFSDMEMBER(T_STRING,  cracctclass, 0),\
	DEFSDMEMBER(T_STRING,  crbankclass, 0),\
	DEFSDMEMBER(T_STRING,  crbankname, 0),\
	DEFSDMEMBER(T_STRING,  crchgno, 0),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_STRING,  refacctno, 0),\
	DEFSDMEMBER(T_STRING,  refseqno1, 0),\
	DEFSDMEMBER(T_STRING,  refseqno2, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_DBSFK)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_DBSFK_H__*/
