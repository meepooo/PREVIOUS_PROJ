/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_dtcx_resp.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_dtcx_resp (电信诈骗动态查询响应)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_DTCX_RESP_H__
#define __GAB_DXZP_DTCX_RESP_H__
typedef struct TDB_GAB_DXZP_DTCX_RESP
{
	char   sbpch[36+1];  /*上报批次号*/
		/*上报批次号*/
	long   sbpcxh;  /*上报批次序号*/
		/*上报批次序号*/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单流水号，用于标识查控请求单*/
	long   rwxh;  /*任务序号*/
		/*任务序号*/
	char   zhm[120+1];  /*账户名*/
		/*账户名*/
	char   zh[50+1];  /*账号*/
		/*账号*/
	char   jylx[50+1];  /*交易类型*/
		/*交易类型*/
	char   jdbz[1+1];  /*借贷标志*/
		/*借贷标志*/
	char   bz[3+1];  /*币种*/
		/*币种*/
	char   jyje[18+1];  /*交易金额*/
		/*交易金额*/
	char   jyye[18+1];  /*交易余额*/
		/*交易余额*/
	char   jysj[14+1];  /*交易时间*/
		/*交易时间*/
	char   jylsh[50+1];  /*交易流水号*/
		/*交易流水号*/
	char   jydfmc[60+1];  /*交易对方名称*/
		/*交易对方名称*/
	char   jydfzh[30+1];  /*交易对方账号*/
		/*交易对方账号*/
	char   jydfzjhm[30+1];  /*交易对方证件号码*/
		/*交易对方证件号码*/
	char   jydfzhkhh[60+1];  /*交易对方账号开户行*/
		/*交易对方账号开户行*/
	char   jyzy[150+1];  /*交易摘要*/
		/*交易摘要*/
	char   jywdmc[150+1];  /*交易网点名称*/
		/*交易网点名称*/
	char   jywddm[20+1];  /*交易网点代码*/
		/*交易网点代码*/
	char   rzh[30+1];  /*日志号*/
		/*日志号*/
	char   cph[30+1];  /*传票号*/
		/*传票号*/
	char   pzzl[10+1];  /*凭证种类*/
		/*凭证种类*/
	char   pzh[30+1];  /*凭证号*/
		/*凭证号*/
	char   xjbz[2+1];  /*现金标志*/
		/*现金标志*/
	char   zdh[30+1];  /*终端号*/
		/*终端号*/
	char   jysfcg[2+1];  /*交易是否成功*/
		/*交易是否成功*/
	char   jyfsd[150+1];  /*交易发生地*/
		/*交易发生地*/
	char   shmc[150+1];  /*商户名称*/
		/*商户名称*/
	char   shh[30+1];  /*商户号*/
		/*商户号*/
	char   ip[30+1];  /*ip地址*/
		/*ip地址*/
	char   mac[50+1];  /*mac地址*/
		/*mac地址*/
	char   jygyh[20+1];  /*交易柜员号*/
		/*交易柜员号*/
	char   beiz[150+1];  /*备注*/
		/*备注*/
	char   fksm[300+1];  /*反馈说明*/
		/*反馈说明*/
	char   fkjgmc[150+1];  /*反馈机构名称*/
		/*反馈机构名称*/
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

}GAB_DXZP_DTCX_RESP;

#define SD_DATA  GAB_DXZP_DTCX_RESP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  jyje, 0),\
	DEFSDMEMBER(T_STRING,  jyye, 0),\
	DEFSDMEMBER(T_STRING,  jysj, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jydfmc, 0),\
	DEFSDMEMBER(T_STRING,  jydfzh, 0),\
	DEFSDMEMBER(T_STRING,  jydfzjhm, 0),\
	DEFSDMEMBER(T_STRING,  jydfzhkhh, 0),\
	DEFSDMEMBER(T_STRING,  jyzy, 0),\
	DEFSDMEMBER(T_STRING,  jywdmc, 0),\
	DEFSDMEMBER(T_STRING,  jywddm, 0),\
	DEFSDMEMBER(T_STRING,  rzh, 0),\
	DEFSDMEMBER(T_STRING,  cph, 0),\
	DEFSDMEMBER(T_STRING,  pzzl, 0),\
	DEFSDMEMBER(T_STRING,  pzh, 0),\
	DEFSDMEMBER(T_STRING,  xjbz, 0),\
	DEFSDMEMBER(T_STRING,  zdh, 0),\
	DEFSDMEMBER(T_STRING,  jysfcg, 0),\
	DEFSDMEMBER(T_STRING,  jyfsd, 0),\
	DEFSDMEMBER(T_STRING,  shmc, 0),\
	DEFSDMEMBER(T_STRING,  shh, 0),\
	DEFSDMEMBER(T_STRING,  ip, 0),\
	DEFSDMEMBER(T_STRING,  mac, 0),\
	DEFSDMEMBER(T_STRING,  jygyh, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_DTCX_RESP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_DTCX_RESP_H__*/
