/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:太原交行中间业务平台项目
版    本:V3.0
操作系统:AIX5.2+DB2V8.2+ANSI.C
文件名称:agent_macro.h
文件描述:代理业务平台宏定义文件
项 目 组:代理业务平台项目组
程 序 员:
发布日期:2007.06.26
修    订:
修改日期:
*********************************************************************/
#if !defined(__AGENT_MACRO__H)
#define __AGENT_MACRO__H

/* 日志宏定义用于跟踪ESQLC行列 */
#define	__STRLOC(A)			__STRLOC_R(A)
#define	__STRLOC_R(A)		#A
#define	_TRACE		"[文件" __FILE__ "][行" __STRLOC(__LINE__) "]"

   
     
/*是否是闰年*/
#define RYEAR(a) ((a) % 4 == 0 && (a) % 100 != 0 || (a) % 400 == 0)
/*一年的天数*/
#define YEARDAYS(a) RYEAR(a)?366:365
/*二月的天数*/
#define MON2DAYS(a) RYEAR(a)?29:28
/*一个月的天数*/
#define RMONTHDAYS(a, b) ((a) == 2?(MON2DAYS(b)):((a) < 8 && (a) % 2 == 0 || (a) >= 8 && (a) % 2 != 0)?30:31)

/* 本系统单节点长度 不能超过2M !!! */

#define AGT_DATA_MAX_LENGTH      2097152            /*MAX_BUFFER 2M*/
#define AGT_BUFF_MAX_LENGTH      2097152            /*MAX_BUFFER 2M*/
#define DEFAULT_AGENT_YYBS      "002"              /*默认代理业务平台编号*/

/* 代理业务平台日志宏定义开始 */
#define	AGT_COMPEXEC_LOGRET(agtmid,agtmsg,agtresult)	{                  \
		fpub_SetMsg(lXmlhandle,agtmid,agtmsg);          \
		fpub_SetCompStatus(lXmlhandle, agtresult);                                 \
		LOGRET(COMPRET_FAIL, LM_STD, agtmsg,fpub_GetCompname(lXmlhandle));         \
	}
#define	AGT_LOG(logmsg)	{   \
		LOG(LM_STD,Fmtmsg("代理业务平台：组件[%s]运行日志\n	[%s]",fpub_GetCompname(lXmlhandle),logmsg),"INFO");  \
	}

/* 代理业务平台日志宏定义结束 */

#define MAX_FILE_SIZE 131072

/* added by yangdong 20090414 交易代码宏定义 */
#define AGT_TRANCODE_SIGN_IN      "920201"   /*客户签约*/
#define AGT_TRANCODE_SIGN_OUT     "920202"  /*客户解约*/
#define AGT_TRANCODE_SIGN_MOD     "920203"   /*客户签约修改*/
#define AGT_TRANCODE_COLLECT_D    "920301"   /*银行代收(直接)*/
#define AGT_TRANCODE_COLLECT_Q    "920302"   /*银行代收(先查后缴)*/
#define AGT_TRANCODE_PAY_D        "920303"   /*银行代付(直接)*/
#define AGT_TRANCODE_PAY_Q        "920304"   /*银行代付(先查后缴)*/

#endif


