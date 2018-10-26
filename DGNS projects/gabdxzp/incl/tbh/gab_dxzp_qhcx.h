/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_qhcx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_qhcx (电信诈骗全户查询表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_QHCX_H__
#define __GAB_DXZP_QHCX_H__
typedef struct TDB_GAB_DXZP_QHCX
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单标识，用于标识查控请求单*/
	int   rwxh;  /*任务序号*/
		/*任务序号*/
	char   zhlb[2+1];  /*查询账号类别*/
		/**/
	char   cxzjlx[15+1];  /*查询证照类型代码*/
		/**/
	char   cxzjhm[30+1];  /*查询证照号码*/
		/**/
	char   zhmc[150+1];  /*查询主体名称*/
		/**/
	char   cxnr[8+1];  /*查询内容*/
		/*查询内容 01-账户基本信息；02-账户信息(含强制措施、共有权/优先权信息)*/
	int   jgfksj;  /*结果反馈限定时间*/
		/**/
	char   bankname[150+1];  /*查询银行名称*/
		/*查询银行名称*/
	char   bankid[12+1];  /*查询银行机构编码*/
		/*查询银行机构编码*/
	char   zxjg[1+1];  /*执行结果*/
		/*执行结果 0-不成功；1-成功*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[100+1];  /*错误原因*/
		/**/
	char   fksm[500+1];  /*反馈说明*/
		/**/
	char   fkjgmc[200+1];  /*反馈机构名称*/
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

}GAB_DXZP_QHCX;

#define SD_DATA  GAB_DXZP_QHCX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  zhlb, 0),\
	DEFSDMEMBER(T_STRING,  cxzjlx, 0),\
	DEFSDMEMBER(T_STRING,  cxzjhm, 0),\
	DEFSDMEMBER(T_STRING,  zhmc, 0),\
	DEFSDMEMBER(T_STRING,  cxnr, 0),\
	DEFSDMEMBER(T_LONG,  jgfksj, 0),\
	DEFSDMEMBER(T_STRING,  bankname, 0),\
	DEFSDMEMBER(T_STRING,  bankid, 0),\
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


	DECLAREFIELDS(SD_GAB_DXZP_QHCX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_QHCX_H__*/
