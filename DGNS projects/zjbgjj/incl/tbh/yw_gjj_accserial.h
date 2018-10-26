/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_accserial.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_accserial (住建部公积金账户变动通知明细表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_ACCSERIAL_H__
#define __YW_GJJ_ACCSERIAL_H__
typedef struct TDB_YW_GJJ_ACCSERIAL
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/**/
	char   sendnode[6+1];  /*发送方节点号*/
		/**/
	char   acctno[32+1];  /*账号*/
		/*账号*/
	char   seqno[20+1];  /*序号*/
		/*序号*/
	char   hostseq[32+1];  /*银行主机流水号*/
		/*银行主机流水号*/
	char   jydm[6+1];  /*交易代码*/
		/*交易代码*/
	char   rivalacctno[32+1];  /*交易对手账号*/
		/*交易对手账号*/
	char   rivalacctname[60+1];  /*交易对手户名*/
		/*交易对手户名*/
	double   amt;  /*金额*/
		/*金额*/
	char   trandate[8+1];  /*交易日期*/
		/*交易日期*/
	char   trantime[6+1];  /*交易时间*/
		/*交易时间*/
	double   availbal;  /*可用余额*/
		/*可用余额*/
	char   openbrhno[20+1];  /*开户机构号*/
		/*开户机构号*/
	char   beiz[254+1];  /*说明*/
		/*说明*/
	char   currno[3+1];  /*币种*/
		/*币种156*/
	char   curriden[1+1];  /*炒汇标志*/
		/*炒汇标志1：钞 2：汇*/
	double   bal;  /*余额*/
		/*账户余额*/
	double   overamt;  /*可透支余额*/
		/*可透支余额*/
	char   dcmttp[4+1];  /*凭证种类*/
		/*凭证种类*/
	char   dcmtno[16+1];  /*凭证号码*/
		/*凭证号码*/
	char   bankno[32+1];  /*交易对手行号*/
		/*交易对手行号*/
	char   desctx[60+1];  /*摘要*/
		/*摘要*/
	char   transtatus[1+1];  /*冲正标识*/
		/*Y：冲正 N：未冲正*/
	char   penno[30+1];  /*笔号*/
		/*定期/通知/一本通账户使用，用于标识账号下不同存款*/
	char   copno[30+1];  /*册号*/
		/*定期/通知/一本通使用，标识账号下不同存款*/
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

}YW_GJJ_ACCSERIAL;

#define SD_DATA  YW_GJJ_ACCSERIAL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  sendnode, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  seqno, 0),\
	DEFSDMEMBER(T_STRING,  hostseq, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  rivalacctno, 0),\
	DEFSDMEMBER(T_STRING,  rivalacctname, 0),\
	DEFSDMEMBER(T_DOUBLE,  amt, 2),\
	DEFSDMEMBER(T_STRING,  trandate, 0),\
	DEFSDMEMBER(T_STRING,  trantime, 0),\
	DEFSDMEMBER(T_DOUBLE,  availbal, 2),\
	DEFSDMEMBER(T_STRING,  openbrhno, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  currno, 0),\
	DEFSDMEMBER(T_STRING,  curriden, 0),\
	DEFSDMEMBER(T_DOUBLE,  bal, 2),\
	DEFSDMEMBER(T_DOUBLE,  overamt, 2),\
	DEFSDMEMBER(T_STRING,  dcmttp, 0),\
	DEFSDMEMBER(T_STRING,  dcmtno, 0),\
	DEFSDMEMBER(T_STRING,  bankno, 0),\
	DEFSDMEMBER(T_STRING,  desctx, 0),\
	DEFSDMEMBER(T_STRING,  transtatus, 0),\
	DEFSDMEMBER(T_STRING,  penno, 0),\
	DEFSDMEMBER(T_STRING,  copno, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_ACCSERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_ACCSERIAL_H__*/
