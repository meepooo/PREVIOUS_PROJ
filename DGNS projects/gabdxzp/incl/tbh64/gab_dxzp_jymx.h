/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_jymx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_jymx (电信诈骗交易明细表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_JYMX_H__
#define __GAB_DXZP_JYMX_H__
typedef struct TDB_GAB_DXZP_JYMX
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单标识，用于标识查控请求单*/
	long   rwxh;  /*任务序号*/
		/*任务序号*/
	char   khyh[12+1];  /*查询账户所属银行机构编码*/
		/**/
	char   khyhmc[150+1];  /*查询账户所属银行名称*/
		/**/
	char   zhlb[2+1];  /*查询账号类别*/
		/**/
	char   zhmc[120+1];  /*查询账户名*/
		/**/
	char   zh[30+1];  /*查询账卡号*/
		/**/
	char   cxnr[8+1];  /*查询内容*/
		/**/
	char   cxqsrq[8+1];  /*查询起始日期*/
		/**/
	char   cxqssj[6+1];  /*查询起始时间*/
		/**/
	char   cxjzrq[8+1];  /*查询截止日期*/
		/**/
	char   cxjzsj[6+1];  /*查询截止时间*/
		/**/
	long   jgfksj;  /*结果反馈限定时间*/
		/**/
	char   zxjg[1+1];  /*执行结果*/
		/*执行结果 0-不成功；1-成功*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[100+1];  /*错误原因*/
		/**/
	char   fksm[300+1];  /*反馈说明*/
		/**/
	char   fkjgmc[150+1];  /*反馈机构名称*/
		/**/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   by1[30+1];  /*备用1*/
		/*备用1*/
	char   by2[254+1];  /*备用2*/
		/*备用2*/
	char   by3[254+1];  /*备用3*/
		/*备用3*/

}GAB_DXZP_JYMX;

#define SD_DATA  GAB_DXZP_JYMX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  khyh, 0),\
	DEFSDMEMBER(T_STRING,  khyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zhlb, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  cxnr, 0),\
	DEFSDMEMBER(T_STRING,  cxqsrq, 0),\
	DEFSDMEMBER(T_STRING,  cxqssj, 0),\
	DEFSDMEMBER(T_STRING,  cxjzrq, 0),\
	DEFSDMEMBER(T_STRING,  cxjzsj, 0),\
	DEFSDMEMBER(T_LONG,  jgfksj, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_JYMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_JYMX_H__*/
