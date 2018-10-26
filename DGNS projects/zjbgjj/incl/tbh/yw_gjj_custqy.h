/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_custqy.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_custqy (住建部公积金中心账户签约表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_CUSTQY_H__
#define __YW_GJJ_CUSTQY_H__
typedef struct TDB_YW_GJJ_CUSTQY
{
	char   receivenode[6+1];  /*公积金中心节点号*/
		/**/
	char   acctno[32+1];  /*账号*/
		/**/
	char   custno[32+1];  /*客户编号*/
		/**/
	char   acctname[60+1];  /*账户名称*/
		/**/
	char   opbrhno[20+1];  /*开户机构号*/
		/**/
	char   opbrhname[80+1];  /*开户机构名*/
		/**/
	char   acctnature[1+1];  /*账户性质*/
		/*1-活期2-定期3-一户通*/
	char   accttype[1+1];  /*账户类型*/
		/*1-归集户2-结算户3-增值收益户4-贷款本金专户5-贷款利息专户6-贷款罚息专户7-贷款违约金专户*/
	char   acctkind[1+1];  /*账户类别*/
		/*2-对公1-对私*/
	char   acctstatus[1+1];  /*账户状态*/
		/*0-注销 1-正常*/
	char   trantype[1+1];  /*签约转账方式*/
		/*1-同行2-实时（他行）3-非实时（他行）*/
	char   bankacctno[32+1];  /*银行扣款资金内部过渡户*/
		/**/
	char   bkrefloancapno[32+1];  /*银行委托贷款本金账号*/
		/**/
	char   dkbjacctno[32+1];  /*银行贷款本金内部过渡户*/
		/**/
	char   dklxacctno[32+1];  /*银行贷款利息内部过渡户*/
		/**/
	char   qystatus[1+1];  /*签约状态*/
		/*0-签约，1-解约*/
	char   qydate[8+1];  /*签约日期*/
		/**/
	char   sendflag[1+1];  /*推送标志*/
		/*0-未推送，1-已推送*/
	char   remark[32+1];  /*备注*/
		/**/
	char   remark1[64+1];  /*备注1*/
		/**/
	char   remark2[128+1];  /*备注2*/
		/**/
	char   remark3[254+1];  /*备注3*/
		/**/
	char   remark4[254+1];  /*备注4*/
		/**/

}YW_GJJ_CUSTQY;

#define SD_DATA  YW_GJJ_CUSTQY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  receivenode, 0),\
	DEFSDMEMBER(T_STRING,  acctno, 0),\
	DEFSDMEMBER(T_STRING,  custno, 0),\
	DEFSDMEMBER(T_STRING,  acctname, 0),\
	DEFSDMEMBER(T_STRING,  opbrhno, 0),\
	DEFSDMEMBER(T_STRING,  opbrhname, 0),\
	DEFSDMEMBER(T_STRING,  acctnature, 0),\
	DEFSDMEMBER(T_STRING,  accttype, 0),\
	DEFSDMEMBER(T_STRING,  acctkind, 0),\
	DEFSDMEMBER(T_STRING,  acctstatus, 0),\
	DEFSDMEMBER(T_STRING,  trantype, 0),\
	DEFSDMEMBER(T_STRING,  bankacctno, 0),\
	DEFSDMEMBER(T_STRING,  bkrefloancapno, 0),\
	DEFSDMEMBER(T_STRING,  dkbjacctno, 0),\
	DEFSDMEMBER(T_STRING,  dklxacctno, 0),\
	DEFSDMEMBER(T_STRING,  qystatus, 0),\
	DEFSDMEMBER(T_STRING,  qydate, 0),\
	DEFSDMEMBER(T_STRING,  sendflag, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_CUSTQY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_CUSTQY_H__*/
