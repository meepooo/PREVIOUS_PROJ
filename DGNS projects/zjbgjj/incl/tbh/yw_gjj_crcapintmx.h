/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_crcapintmx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_crcapintmx (住建部公积金贷款本息分解明细表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_CRCAPINTMX_H__
#define __YW_GJJ_CRCAPINTMX_H__
typedef struct TDB_YW_GJJ_CRCAPINTMX
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号*/
	char   txunitno[15+1];  /*交易机构号*/
		/*交易机构号*/
	char   seqno[20+1];  /*序号*/
		/*序号*/
	char   batchno[20+1];  /*批次号*/
		/*批次号*/
	char   fileno[5+1];  /*文件序号*/
		/*文件序号*/
	char   mxacctno[32+1];  /*业务明细账号*/
		/*业务明细账号*/
	char   mxserialno[32+1];  /*业务明细流水号*/
		/*业务明细流水号*/
	char   idnumber[18+1];  /*身份证号*/
		/*身份证号*/
	char   contractno[32+1];  /*合同编号*/
		/*合同编号*/
	char   name[60+1];  /*姓名*/
		/*姓名*/
	double   amt;  /*还款金额*/
		/*还款金额*/
	double   capamt;  /*贷款本金发生额*/
		/*贷款本金发生额*/
	double   intamt;  /*贷款利息发生额*/
		/*贷款利息发生额*/
	double   penamt;  /*贷款罚息发生额*/
		/*贷款罚息发生额*/
	double   fineamt;  /*贷款违约金发生额*/
		/*贷款违约金发生额*/
	double   bkamt;  /*非扣款还贷金额*/
		/*非扣款还贷金额*/
	double   refcapamt;  /*非扣款贷款本金发生额*/
		/*非扣款贷款本金发生额*/
	double   refintamt;  /*非扣款贷款利息发生额*/
		/*非扣款贷款利息发生额*/
	double   refineamt;  /*非扣款贷款违约金发生额*/
		/*非扣款贷款违约金发生额*/
	double   repenamt;  /*非扣款贷款罚息发生额*/
		/*非扣款贷款罚息发生额*/
	char   summary[60+1];  /*摘要*/
		/*摘要*/
	char   dealstatus[1+1];  /*处理结果*/
		/*处理结果0-初态，1-成功，2失败，3超时*/
	char   hostseq[32+1];  /*主机流水*/
		/*主机流水*/
	char   hostdate[8+1];  /*主机日期*/
		/*主机日期*/
	char   caphostseqno[32+1];  /*本金银行流水号*/
		/*本金银行流水号*/
	char   inthostseqno[32+1];  /*利息银行流水号*/
		/*利息银行流水号*/
	char   dealcode[5+1];  /*处理结果码*/
		/*处理结果码00000-成功，99999超时，其他失败*/
	char   dealmsg[160+1];  /*处理结果信息*/
		/*处理结果信息*/
	char   hzno[32+1];  /*回执编号*/
		/*回执编号*/
	char   bankex[254+1];  /*银行扩展*/
		/*银行扩展*/
	char   zwrq[8+1];  /*前置日期*/
		/*前置日期*/
	char   systime[6+1];  /*前置时间*/
		/*前置时间*/
	char   remark[32+1];  /*备用*/
		/*备用*/
	char   remark1[128+1];  /*备用1*/
		/*备用1*/
	char   remark2[64+1];  /*备用2*/
		/*备用2*/
	char   remark3[254+1];  /*备用3*/
		/*备用3*/
	char   remark4[254+1];  /*备用4*/
		/*备用4*/

}YW_GJJ_CRCAPINTMX;

#define SD_DATA  YW_GJJ_CRCAPINTMX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  seqno, 0),\
	DEFSDMEMBER(T_STRING,  batchno, 0),\
	DEFSDMEMBER(T_STRING,  fileno, 0),\
	DEFSDMEMBER(T_STRING,  mxacctno, 0),\
	DEFSDMEMBER(T_STRING,  mxserialno, 0),\
	DEFSDMEMBER(T_STRING,  idnumber, 0),\
	DEFSDMEMBER(T_STRING,  contractno, 0),\
	DEFSDMEMBER(T_STRING,  name, 0),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_DOUBLE,  capamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  intamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  penamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  fineamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  bkamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refcapamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refintamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  refineamt, 2),\
	DEFSDMEMBER(T_DOUBLE,  repenamt, 2),\
	DEFSDMEMBER(T_STRING,  summary, 0),\
	DEFSDMEMBER(T_STRING,  dealstatus, 0),\
	DEFSDMEMBER(T_STRING,  hostseq, 0),\
	DEFSDMEMBER(T_STRING,  hostdate, 0),\
	DEFSDMEMBER(T_STRING,  caphostseqno, 0),\
	DEFSDMEMBER(T_STRING,  inthostseqno, 0),\
	DEFSDMEMBER(T_STRING,  dealcode, 0),\
	DEFSDMEMBER(T_STRING,  dealmsg, 0),\
	DEFSDMEMBER(T_STRING,  hzno, 0),\
	DEFSDMEMBER(T_STRING,  bankex, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_CRCAPINTMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CRCAPINTMX_H__*/
