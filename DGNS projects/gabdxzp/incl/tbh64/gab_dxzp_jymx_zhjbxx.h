/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_jymx_zhjbxx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_jymx_zhjbxx (电信诈骗卡介质_账户基本信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_JYMX_ZHJBXX_H__
#define __GAB_DXZP_JYMX_ZHJBXX_H__
typedef struct TDB_GAB_DXZP_JYMX_ZHJBXX
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单流水号，用于标识查控请求单*/
	long   rwxh;  /*任务序号*/
		/*任务序号*/
	char   zhm[120+1];  /*账户名*/
		/*账户名*/
	char   kzh[30+1];  /*卡/折号*/
		/*卡/折号*/
	char   khwd[150+1];  /*开户网点*/
		/*开户网点*/
	char   khwddm[20+1];  /*开户网点代码*/
		/*开户网点代码*/
	char   khrq[14+1];  /*开户日期*/
		/*开户日期*/
	char   xhrq[14+1];  /*销户日期*/
		/*销户日期*/
	char   xhwd[150+1];  /*销户网点*/
		/*销户网点*/
	char   beiz[150+1];  /*备注*/
		/*备注 */
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

}GAB_DXZP_JYMX_ZHJBXX;

#define SD_DATA  GAB_DXZP_JYMX_ZHJBXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  kzh, 0),\
	DEFSDMEMBER(T_STRING,  khwd, 0),\
	DEFSDMEMBER(T_STRING,  khwddm, 0),\
	DEFSDMEMBER(T_STRING,  khrq, 0),\
	DEFSDMEMBER(T_STRING,  xhrq, 0),\
	DEFSDMEMBER(T_STRING,  xhwd, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_JYMX_ZHJBXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_JYMX_ZHJBXX_H__*/
