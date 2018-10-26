/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_crcapint.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_crcapint (住建部公积金贷款本息分解主表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_CRCAPINT_H__
#define __YW_GJJ_CRCAPINT_H__
typedef struct TDB_YW_GJJ_CRCAPINT
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号*/
	char   txunitno[15+1];  /*交易机构号*/
		/*交易机构号*/
	char   batchno[20+1];  /*批次号*/
		/*批次号*/
	char   fileno[8+1];  /*文件序号*/
		/*文件序号*/
	char   oribatchno[20+1];  /*原贷款扣款批次号*/
		/*原贷款扣款批次号*/
	long   batchtotalnum;  /*总笔数*/
		/*本批次交易总笔数*/
	double   batchtotalamt;  /*总金额*/
		/*本批次交易总金额*/
	char   beiz[254+1];  /*说明*/
		/*说明*/
	double   bkamt;  /*扣款交易还贷金额*/
		/*到银行扣款还贷金额*/
	double   refamt;  /*非扣款交易还贷金额*/
		/*不需要银行扣款或公积金还贷金额*/
	double   refcapamt;  /*非扣款交易贷款本金发生额*/
		/*非扣款本金还款额*/
	double   refintamt;  /*非扣款交易贷款利息发生额*/
		/*非扣款利息还款额*/
	double   repenamt;  /*非扣款交易贷款罚息发生额*/
		/*非扣款罚息还款额*/
	double   refineamt;  /*非扣款交易贷款违约金发生额*/
		/*非扣款违约金还款额*/
	char   bankacctno[32+1];  /*银行扣款资金内部过渡户*/
		/*贷款扣款中使用的收款银行收款内部过渡户*/
	char   bkrefloancapno[32+1];  /*银行委托贷款本金账号*/
		/*银行委托贷款本金账号*/
	char   bkloancapinacctno[32+1];  /*银行贷款本金内部过渡户*/
		/*银行使用的贷款本金过渡户*/
	char   bkloanintinacctno[32+1];  /*银行贷款利息内部过渡户*/
		/*银行使用的贷款利息过渡户*/
	char   loancapcracctno[32+1];  /*贷款本金收方账号*/
		/*公积金中心放置贷款本金账号*/
	char   loancapcracctname[60+1];  /*贷款本金收方户名*/
		/*贷款本金账号户名*/
	char   loancapcracctclass[1+1];  /*贷款本金收方账户类别*/
		/*1：对私 2：对公*/
	char   loancapcracctbkname[60+1];  /*贷款本金收方账户行名*/
		/*贷款本金收方账户行名*/
	double   loancapamt;  /*银行扣款贷款本金发生额*/
		/*银行扣款贷款本金发生额*/
	char   loanintcracctno[32+1];  /*贷款利息收方账号*/
		/*公积金中心放置贷款利息账号*/
	char   loanintcracctname[60+1];  /*贷款利息收方户名*/
		/*贷款利息收方户名*/
	char   loanintcracctclass[1+1];  /*贷款利息收方账户类别*/
		/*1：对私 2：对公*/
	char   loanintcracctbkname[60+1];  /*贷款利息收方账户行名*/
		/*贷款利息收方账户行名*/
	double   loanintamt;  /*银行扣款贷款利息发生额*/
		/*银行扣款贷款利息发生额*/
	char   loanpencracctno[32+1];  /*贷款罚息收方账号*/
		/*公积金中心放置贷款罚息账号*/
	char   loanpencracctname[60+1];  /*贷款罚息收方户名*/
		/*贷款罚息收方户名*/
	char   loanpencracctclass[1+1];  /*贷款罚息收方账户类别*/
		/*1：对私 2：对公*/
	char   loanpencratbkname[60+1];  /*贷款罚息收方账户行名*/
		/*贷款罚息收方账户行名*/
	double   loanpenamt;  /*银行扣款贷款罚息发生额*/
		/*银行扣款贷款罚息发生额*/
	char   loanfinecracctno[32+1];  /*贷款违约金收方账号*/
		/*公积金中心放置贷款违约金账号*/
	char   loanfinecracctname[60+1];  /*贷款违约金收方户名*/
		/*贷款违约金收方账户行名*/
	char   loanfinecracctclass[1+1];  /*贷款违约金收方账户类别*/
		/*1：对私2：对公*/
	char   loanfinecratbkname[60+1];  /*贷款违约金收方账户行名*/
		/*贷款违约金收方账户行名*/
	double   loanfineamt;  /*银行扣款贷款违约金发生额*/
		/*银行扣款贷款违约金发生额户时填写*/
	long   batchsuccnum;  /*成功笔数*/
		/*成功笔数*/
	double   batchsuccamt;  /*成功金额*/
		/*成功金额*/
	long   batchfailnum;  /*失败笔数*/
		/*失败笔数*/
	double   batchfailamt;  /*失败金额*/
		/*失败金额*/
	char   zipfilename[128+1];  /*密文文件名*/
		/*密文文件名*/
	char   unzipfilename[128+1];  /*明文文件名*/
		/*明文文件名*/
	char   trantype[1+1];  /*交易类别*/
		/*交易类别 a：行内代扣 b：行内代发 c：跨行代扣 d: 跨行代发 e: 混合代扣 f: 混合代发 g: 其他*/
	char   dealtype[1+1];  /*处理类型*/
		/*处理类型1:文件 2:逐笔 3:都支持*/
	char   dealstep[1+1];  /*处理步点*/
		/*处理步点0-初态，1-收妥，2-处理中，3-处理完成*/
	char   dealstatus[5+1];  /*处理状态*/
		/*0-初态，1-成功，2-失败*/
	char   dealinf[160+1];  /*处理结果描述*/
		/*处理结果描述*/
	char   batchpch[64+1];  /*核心处理批次号*/
		/*核心处理批次号*/
	char   querystatus[1+1];  /*结果查询状态*/
		/*结果查询状态0-未查询，1-已查询，2-查询失败*/
	char   zwrq[8+1];  /*前置日期*/
		/*前置日期*/
	char   systime[6+1];  /*前置时间*/
		/*前置时间*/
	char   remark[32+1];  /*备注*/
		/*备注*/
	char   remark1[64+1];  /*备注1*/
		/*备注1*/
	char   remark2[128+1];  /*备注2*/
		/*备注2*/
	char   remark3[254+1];  /*备注3*/
		/*备注3*/
	char   remark4[254+1];  /*备注4*/
		/*备注4*/

}YW_GJJ_CRCAPINT;

#define SD_DATA  YW_GJJ_CRCAPINT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  batchno, 0),\
	DEFSDMEMBER(T_STRING,  fileno, 0),\
	DEFSDMEMBER(T_STRING,  oribatchno, 0),\
	DEFSDMEMBER(T_LONG,  batchtotalnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchtotalamt, 2),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_DOUBLE,  bkamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refcapamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refintamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  repenamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refineamt, 2),\
	DEFSDMEMBER(T_STRING,  bankacctno, 0),\
	DEFSDMEMBER(T_STRING,  bkrefloancapno, 0),\
	DEFSDMEMBER(T_STRING,  bkloancapinacctno, 0),\
	DEFSDMEMBER(T_STRING,  bkloanintinacctno, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctno, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctname, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loancapcracctbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loancapamt, 2),\
	DEFSDMEMBER(T_STRING,  loanintcracctno, 0),\
	DEFSDMEMBER(T_STRING,  loanintcracctname, 0),\
	DEFSDMEMBER(T_STRING,  loanintcracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loanintcracctbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loanintamt, 2),\
	DEFSDMEMBER(T_STRING,  loanpencracctno, 0),\
	DEFSDMEMBER(T_STRING,  loanpencracctname, 0),\
	DEFSDMEMBER(T_STRING,  loanpencracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loanpencratbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loanpenamt, 2),\
	DEFSDMEMBER(T_STRING,  loanfinecracctno, 0),\
	DEFSDMEMBER(T_STRING,  loanfinecracctname, 0),\
	DEFSDMEMBER(T_STRING,  loanfinecracctclass, 0),\
	DEFSDMEMBER(T_STRING,  loanfinecratbkname, 0),\
	DEFSDMEMBER(T_DOUBLE,  loanfineamt, 2),\
	DEFSDMEMBER(T_LONG,  batchsuccnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchsuccamt, 2),\
	DEFSDMEMBER(T_LONG,  batchfailnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchfailamt, 2),\
	DEFSDMEMBER(T_STRING,  zipfilename, 0),\
	DEFSDMEMBER(T_STRING,  unzipfilename, 0),\
	DEFSDMEMBER(T_STRING,  trantype, 0),\
	DEFSDMEMBER(T_STRING,  dealtype, 0),\
	DEFSDMEMBER(T_STRING,  dealstep, 0),\
	DEFSDMEMBER(T_STRING,  dealstatus, 0),\
	DEFSDMEMBER(T_STRING,  dealinf, 0),\
	DEFSDMEMBER(T_STRING,  batchpch, 0),\
	DEFSDMEMBER(T_STRING,  querystatus, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_CRCAPINT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CRCAPINT_H__*/
