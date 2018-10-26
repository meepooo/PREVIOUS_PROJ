/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_fixedbusiness.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_fixedbusiness (住建部公积金定期业务)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_FIXEDBUSINESS_H__
#define __YW_GJJ_FIXEDBUSINESS_H__
typedef struct TDB_YW_GJJ_FIXEDBUSINESS
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号*/
	char   txunitno[15+1];  /*交易机构号*/
		/*交易机构号*/
	char   jylx[1+1];  /*交易类型*/
		/*交易类型 0-活期转定期 1-定期支取 2-定期转存方式设定*/
	char   currno[3+1];  /*币种*/
		/*币种*/
	char   curriden[1+1];  /*钞汇鉴别*/
		/*钞汇鉴别*/
	char   activedacctno[32+1];  /*活期账号*/
		/*活期账号*/
	char   activedacctname[60+1];  /*活期户名*/
		/*活期户名*/
	char   activedacctopenbank[60+1];  /*活期账户开户机构名*/
		/*活期账户开户机构名*/
	char   fixedacctno[32+1];  /*定期账号*/
		/*定期账号*/
	char   fixedacctname[60+1];  /*定期户名*/
		/*定期户名*/
	char   fixedacctopenbank[60+1];  /*定期账户开户机构名*/
		/*定期账户开户机构名*/
	char   depositperiod[1+1];  /*存期*/
		/*存期 0：三个月 1：半年 2：一年 3：两年 4：三年 5：五年  */
	double   interestrate;  /*利率*/
		/*银行挂牌利率*/
	double   amt;  /*交易金额*/
		/*交易金额*/
	char   extenddeposittype[1+1];  /*转存方式*/
		/*转存方式 0：本金+利息自动转存  1：不自动转存  2：本金自动转存  */
	char   partexdeacctno[32+1];  /*利息转存转入账号*/
		/*本金发生额*/
	char   beiz[254+1];  /*说明*/
		/*付息户账号*/
	char   bookno[50+1];  /*册号*/
		/*册号 帐号为一本通时,必输*/
	char   booklistno[50+1];  /*笔号*/
		/*笔号 帐号为一本通时,必输*/
	char   depositbegindate[8+1];  /*存入日期*/
		/*存入日期*/
	char   depositenddate[8+1];  /*到期日期*/
		/*到期日期*/
	double   depostiamt;  /*实际金额*/
		/*实际金额*/
	double   drawamt;  /*支取金额*/
		/*支取金额*/
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

}YW_GJJ_FIXEDBUSINESS;

#define SD_DATA  YW_GJJ_FIXEDBUSINESS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  activedacctno, 0),\
	DEFSDMEMBER(T_STRING,  activedacctname, 0),\
	DEFSDMEMBER(T_STRING,  activedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctno, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctname, 0),\
	DEFSDMEMBER(T_STRING,  fixedacctopenbank, 0),\
	DEFSDMEMBER(T_STRING,  depositperiod, 0),\
	DEFSDMEMBER(T_DOUBLE,  interestrate, 5),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_STRING,  extenddeposittype, 0),\
	DEFSDMEMBER(T_STRING,  partexdeacctno, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  bookno, 0),\
	DEFSDMEMBER(T_STRING,  booklistno, 0),\
	DEFSDMEMBER(T_STRING,  depositbegindate, 0),\
	DEFSDMEMBER(T_STRING,  depositenddate, 0),\
	DEFSDMEMBER(T_DOUBLE,  depostiamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  drawamt, 2),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_FIXEDBUSINESS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_FIXEDBUSINESS_H__*/
