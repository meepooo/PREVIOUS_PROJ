/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_drbatch.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_drbatch (住建部公积金批量收付款主表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_DRBATCH_H__
#define __YW_GJJ_DRBATCH_H__
typedef struct TDB_YW_GJJ_DRBATCH
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号*/
	char   txunitno[15+1];  /*交易机构号*/
		/*交易机构号*/
	char   sfkbz[1+1];  /*收付款标志*/
		/*收付款标志0-收款,1-付款,2-扣款*/
	char   batchno[20+1];  /*批次号*/
		/*批次号*/
	char   fileno[8+1];  /*文件序号*/
		/*文件序号*/
	char   currno[3+1];  /*币种*/
		/*币种*/
	char   curriden[1+1];  /*钞汇鉴别*/
		/*钞汇鉴别*/
	char   filetype[1+1];  /*文件类型*/
		/*文件类型*/
	char   bustype[6+1];  /*业务类型*/
		/*业务类型*/
	char   batchprjno[32+1];  /*批量项目编号*/
		/*批量项目编号*/
	char   acctno[32+1];  /*账号*/
		/*账号*/
	char   acctname[60+1];  /*户名*/
		/*户名*/
	char   acctclass[1+1];  /*账户类别*/
		/*账户类别*/
	double   batchcapamt;  /*付款本金金额*/
		/*付款本金金额*/
	char   deintacctno[32+1];  /*付方利息户账号*/
		/*付方利息户账号*/
	char   deintacctname[60+1];  /*付方利息户户名*/
		/*付方利息户户名*/
	char   deintacctclass[1+1];  /*付方利息户类别*/
		/*付方利息户类别*/
	char   deintcracct[32+1];  /*利息收方账号*/
		/*利息收方账号*/
	double   batchintamt;  /*付款利息金额*/
		/*付款利息金额*/
	char   bankacctno[32+1];  /*银行内部过渡户*/
		/*银行内部过渡户*/
	int   batchtotalnum;  /*总笔数*/
		/*总笔数*/
	double   batchtotalamt;  /*总金额*/
		/*总金额*/
	int   batchsuccnum;  /*成功笔数*/
		/*成功笔数*/
	double   batchsuccamt;  /*成功金额*/
		/*成功金额*/
	int   batchfailnum;  /*失败笔数*/
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

}YW_GJJ_DRBATCH;

#define SD_DATA  YW_GJJ_DRBATCH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  sfkbz, 0),\
	DEFSDMEMBER(T_STRING,  batchno, 0),\
	DEFSDMEMBER(T_STRING,  fileno, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_STRING,  filetype, 0),\
	DEFSDMEMBER(T_STRING,  bustype, 0),\
	DEFSDMEMBER(T_STRING,  batchprjno, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  acctname, 0),\
	DEFSDMEMBER(T_STRING,  acctclass, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchcapamt, 2),\
	DEFSDMEMBER(T_STRING,  deintacctno, 0),\
	DEFSDMEMBER(T_STRING,  deintacctname, 0),\
	DEFSDMEMBER(T_STRING,  deintacctclass, 0),\
	DEFSDMEMBER(T_STRING,  deintcracct, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchintamt, 2),\
	DEFSDMEMBER(T_STRING,  bankacctno, 0),\
	DEFSDMEMBER(T_LONG,  batchtotalnum, 0),\
	DEFSDMEMBER(T_DOUBLE,  batchtotalamt, 2),\
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


	DECLAREFIELDS(SD_YW_GJJ_DRBATCH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_DRBATCH_H__*/
