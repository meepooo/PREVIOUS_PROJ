/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_jjzf.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_jjzf (电信诈骗止付解止表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_JJZF_H__
#define __GAB_DXZP_JJZF_H__
typedef struct TDB_GAB_DXZP_JJZF
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单标识，用于标识查控请求单*/
	long   rwxh;  /*任务序号*/
		/*任务序号*/
	char   yywsqbh[36+1];  /*原业务申请编号*/
		/*原业务申请编号 原紧急止付的任务流水号识；措施为解除紧急止付时使用；*/
	char   sfblc[2+1];  /*是否补流程*/
		/*是否补流程 00-初次提交正常止付人民币活期账户；01-初次提交正常止付外币活期账户；02-银行举报案件止付人民币活期账户；03-银行举报案件止付外币活期账户；04-后补人民币活期止付流程；05-后补外币活期止付流程*/
	char   yjbsqbh[36+1];  /*原举报申请编号*/
		/*原举报申请编号*/
	char   kh[30+1];  /*卡号*/
		/*卡号 请求止付的卡号*/
	char   zczhyh[12+1];  /*转出账户所属银行机构编码*/
		/**/
	char   zczhyhmc[150+1];  /*转出账户银行名称*/
		/**/
	char   zczhm[100+1];  /*转出账户名*/
		/**/
	char   zczh[30+1];  /*转出账号*/
		/**/
	char   bz[3+1];  /*币种*/
		/**/
	char   zcje[18+1];  /*转出金额*/
		/**/
	char   zcrq[8+1];  /*转出日期*/
		/**/
	char   zcsj[6+1];  /*转出时间*/
		/**/
	char   khyh[12+1];  /*止付账户所属银行机构编码*/
		/**/
	char   khyhmc[150+1];  /*止付账户所属银行名称*/
		/**/
	char   zhlb[2+1];  /*止付账号类别*/
		/**/
	char   zhmc[120+1];  /*止付账户名*/
		/**/
	char   zh[50+1];  /*止付账卡号*/
		/**/
	char   dqr[8+1];  /*止付到期日*/
		/**/
	int   jgfksj;  /*结果反馈限定时间*/
		/**/
	char   zfqssj[14+1];  /*止付起始时间*/
		/*止付起始时间*/
	char   zfjssj[14+1];  /*止付结束时间*/
		/*止付结束时间*/
	char   zxjg[1+1];  /*执行结果*/
		/*执行结果 0-执行成功 1-执行失败*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[100+1];  /*错误原因*/
		/**/
	char   zxqssj[14+1];  /*执行起始时间*/
		/*执行起始时间*/
	char   zxjssj[14+1];  /*执行结束时间*/
		/*执行结束时间*/
	char   fksm[300+1];  /*反馈说明*/
		/**/
	char   fkjgmc[150+1];  /*反馈机构名称*/
		/**/
	char   zhye[20+1];  /*账户余额*/
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

}GAB_DXZP_JJZF;

#define SD_DATA  GAB_DXZP_JJZF
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  sfblc, 0),\
	DEFSDMEMBER(T_STRING,  yjbsqbh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zczhyh, 0),\
	DEFSDMEMBER(T_STRING,  zczhyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zczhm, 0),\
	DEFSDMEMBER(T_STRING,  zczh, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  zcje, 0),\
	DEFSDMEMBER(T_STRING,  zcrq, 0),\
	DEFSDMEMBER(T_STRING,  zcsj, 0),\
	DEFSDMEMBER(T_STRING,  khyh, 0),\
	DEFSDMEMBER(T_STRING,  khyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zhlb, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  dqr, 0),\
	DEFSDMEMBER(T_LONG,  jgfksj, 0),\
	DEFSDMEMBER(T_STRING,  zfqssj, 0),\
	DEFSDMEMBER(T_STRING,  zfjssj, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zxqssj, 0),\
	DEFSDMEMBER(T_STRING,  zxjssj, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  zhye, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_JJZF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_JJZF_H__*/
