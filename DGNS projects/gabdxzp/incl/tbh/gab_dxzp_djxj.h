/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_djxj.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_djxj (电信诈骗冻结续解表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_DJXJ_H__
#define __GAB_DXZP_DJXJ_H__
typedef struct TDB_GAB_DXZP_DJXJ
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单标识，用于标识查控请求单*/
	int   rwxh;  /*任务序号*/
		/*任务序号*/
	char   yywsqbh[36+1];  /*原业务申请编号*/
		/*原业务申请编号 原紧急止付的任务流水号识；措施为解除紧急止付时使用；*/
	char   khyh[12+1];  /*冻结账户所属银行机构编码*/
		/*冻结账户所属银行机构编码*/
	char   khyhmc[150+1];  /*冻结账户所属银行名称*/
		/*冻结账户所属银行名称*/
	char   zhlb[2+1];  /*冻结账号类别*/
		/*冻结账号类别*/
	char   zhmc[120+1];  /*冻结账户名*/
		/*冻结账户名*/
	char   zh[50+1];  /*冻结账卡号*/
		/*冻结账卡号*/
	char   zjlx[2+1];  /*冻结账户证件类型*/
		/**/
	char   zjhm[30+1];  /*冻结账号证件号码*/
		/**/
	char   djfs[2+1];  /*冻结方式*/
		/**/
	char   bz[3+1];  /*币种*/
		/**/
	char   je[18+1];  /*金额*/
		/**/
	char   dqr[8+1];  /*冻结到期日*/
		/*冻结到期日*/
	char   djqssj[14+1];  /*冻结起始时间*/
		/*冻结起始时间*/
	char   djjssj[14+1];  /*冻结结束时间*/
		/*冻结结束时间*/
	int   jgfksj;  /*结果反馈限定时间*/
		/*结果反馈限定时间*/
	char   zxjg[1+1];  /*执行结果*/
		/*执行结果 0-不成功；1-成功*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[100+1];  /*错误原因*/
		/**/
	char   kh[30+1];  /*卡号*/
		/*卡号 请求止付的卡号*/
	char   zxqssj[14+1];  /*执行起始时间*/
		/*执行起始时间  执行措施的时间*/
	char   zxjssj[14+1];  /*执行结束时间*/
		/*执行起始时间  执行措施的时间*/
	char   fksm[300+1];  /*反馈说明*/
		/**/
	char   fkjgmc[150+1];  /*反馈机构名称*/
		/**/
	char   djje[20+1];  /*执行冻结金额*/
		/**/
	char   zhye[20+1];  /*账户余额*/
		/**/
	char   zxdjje[20+1];  /*在先冻结金额*/
		/**/
	char   zxdjrq[12+1];  /*在先冻结到期日*/
		/**/
	char   zhkyye[20+1];  /*账户可用余额*/
		/**/
	char   zxdjjg[60+1];  /*在先冻结机关*/
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

}GAB_DXZP_DJXJ;

#define SD_DATA  GAB_DXZP_DJXJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  khyh, 0),\
	DEFSDMEMBER(T_STRING,  khyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zhlb, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  djfs, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  je, 0),\
	DEFSDMEMBER(T_STRING,  dqr, 0),\
	DEFSDMEMBER(T_STRING,  djqssj, 0),\
	DEFSDMEMBER(T_STRING,  djjssj, 0),\
	DEFSDMEMBER(T_LONG,  jgfksj, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zxqssj, 0),\
	DEFSDMEMBER(T_STRING,  zxjssj, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  djje, 0),\
	DEFSDMEMBER(T_STRING,  zhye, 0),\
	DEFSDMEMBER(T_STRING,  zxdjje, 0),\
	DEFSDMEMBER(T_STRING,  zxdjrq, 0),\
	DEFSDMEMBER(T_STRING,  zhkyye, 0),\
	DEFSDMEMBER(T_STRING,  zxdjjg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_DJXJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_DJXJ_H__*/
