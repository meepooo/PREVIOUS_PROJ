/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_trans.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_trans (住建部公积金主流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_TRANS_H__
#define __YW_GJJ_TRANS_H__
typedef struct TDB_YW_GJJ_TRANS
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号*/
	char   txunitno[15+1];  /*交易机构号*/
		/*交易机构号*/
	char   sendnode[6+1];  /*中心代码*/
		/*中心代码*/
	char   senddate[8+1];  /*发送方日期*/
		/*发送方日期*/
	char   sendtime[6+1];  /*发送方时间*/
		/**/
	char   transcode[7+1];  /*交易码*/
		/*交易码*/
	char   receivenode[6+1];  /*接收方节点号*/
		/**/
	char   bdcdate[8+1];  /*采集系统日期*/
		/*采集系统日期*/
	char   bdctime[6+1];  /*数据应用系统时间*/
		/*数据应用系统时间*/
	char   bdcseqno[32+1];  /*数据应用系统流水号*/
		/*采集系统流水号*/
	char   custno[32+1];  /*银行客户编号*/
		/*银行客户编号*/
	char   operno[21+1];  /*发送操作员*/
		/*发送操作员*/
	int   beginrec;  /*开始记录数*/
		/*开始记录数*/
	int   maxrec;  /*一次查询最大记录数*/
		/*一次查询最大记录数*/
	char   clrq[8+1];  /*处理日期*/
		/*处理日期*/
	char   clsj[6+1];  /*处理时间*/
		/*处理时间*/
	char   jbjg[16+1];  /*银行经办机构*/
		/*经办机构*/
	char   jbgy[16+1];  /*银行经办柜员*/
		/*经办柜员*/
	char   ywlsh[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   hoststatus[1+1];  /*银行主机处理状态*/
		/*银行主机处理状态0-成功 1-失败 3-超时 9-初始*/
	char   hostseqno[32+1];  /*银行主机流水号*/
		/*银行主机流水号*/
	char   hostmsg[160+1];  /*银行主机响应信息*/
		/*银行主机响应信息*/
	char   hostrespcode[20+1];  /*银行主机响应码*/
		/*银行主机响应码*/
	char   zjrq[8+1];  /*主机日期*/
		/*主机日期*/
	char   zjsj[6+1];  /*主机时间*/
		/*主机时间*/
	int   tjhxcs;  /*提交核心次数*/
		/*提交核心次数*/
	char   caphostseqno[32+1];  /*本金银行主机流水号*/
		/*本金银行主机流水号*/
	char   inthostseqno[32+1];  /*利息银行主机流水号*/
		/*利息银行主机流水号*/
	char   penhostseqno[32+1];  /*贷款罚息银行主机流水号*/
		/*贷款罚息银行主机流水号*/
	char   finehostseqno[32+1];  /*贷款违约金银行流水号*/
		/*贷款违约金银行流水号*/
	char   summary[60+1];  /*摘要*/
		/*摘要*/
	char   batch[20+1];  /*交易批量编号*/
		/*交易批量编号*/
	char   transdate[8+1];  /*交易日期*/
		/*交易日期*/
	char   transtime[8+1];  /*交易时间*/
		/*交易时间*/
	char   qzlsh[10+1];  /*前置流水号*/
		/*前置流水号*/
	char   qqdzt[2+1];  /*请求单状态*/
		/*11-落地失败,20-已落地待处理,21-提交失败,23-提交超时,30-已提交待提回,31-提回失败,33-提回超时,40-已处理待反馈,41-反馈失败,43-反馈超时,99-已反馈*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[100+1];  /*错误原因*/
		/**/
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

}YW_GJJ_TRANS;

#define SD_DATA  YW_GJJ_TRANS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  txunitno, 0),\
	DEFSDMEMBER(T_STRING,  sendnode, 0),\
	DEFSDMEMBER(T_STRING,  senddate, 0),\
	DEFSDMEMBER(T_STRING,  sendtime, 0),\
	DEFSDMEMBER(T_STRING,  transcode, 0),\
	DEFSDMEMBER(T_STRING,  receivenode, 0),\
	DEFSDMEMBER(T_STRING,  bdcdate, 0),\
	DEFSDMEMBER(T_STRING,  bdctime, 0),\
	DEFSDMEMBER(T_STRING,  bdcseqno, 0),\
	DEFSDMEMBER(T_STRING,  custno, 0),\
	DEFSDMEMBER(T_STRING,  operno, 0),\
	DEFSDMEMBER(T_LONG,  beginrec, 0),\
	DEFSDMEMBER(T_LONG,  maxrec, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  hoststatus, 0),\
	DEFSDMEMBER(T_STRING,  hostseqno, 0),\
	DEFSDMEMBER(T_STRING,  hostmsg, 0),\
	DEFSDMEMBER(T_STRING,  hostrespcode, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjsj, 0),\
	DEFSDMEMBER(T_LONG,  tjhxcs, 0),\
	DEFSDMEMBER(T_STRING,  caphostseqno, 0),\
	DEFSDMEMBER(T_STRING,  inthostseqno, 0),\
	DEFSDMEMBER(T_STRING,  penhostseqno, 0),\
	DEFSDMEMBER(T_STRING,  finehostseqno, 0),\
	DEFSDMEMBER(T_STRING,  summary, 0),\
	DEFSDMEMBER(T_STRING,  batch, 0),\
	DEFSDMEMBER(T_STRING,  transdate, 0),\
	DEFSDMEMBER(T_STRING,  transtime, 0),\
	DEFSDMEMBER(T_STRING,  qzlsh, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_TRANS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_TRANS_H__*/
