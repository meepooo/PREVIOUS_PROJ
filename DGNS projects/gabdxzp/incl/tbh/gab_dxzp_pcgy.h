/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_pcgy.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_pcgy (电信诈骗上报信息_批次概要表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_PCGY_H__
#define __GAB_DXZP_PCGY_H__
typedef struct TDB_GAB_DXZP_PCGY
{
	char   sbpch[36+1];  /*上报批次号*/
		/*上报批次号*/
	char   scrq[8+1];  /*生成日期*/
		/*生成日期*/
	char   sjgs[10+1];  /*事件归属*/
		/*事件归属 yckk-异常开卡 sazh-涉案账户 ycsj-异常事件*/
	char   sjtzm[6+1];  /*事件特征码*/
		/*事件特征码*/
	char   sbjg[16+1];  /*上报机构*/
		/*上报机构*/
	char   sbgy[16+1];  /*上报柜员*/
		/*上报柜员*/
	char   sbrq[8+1];  /*上报日期*/
		/*上报日期*/
	char   sbsj[6+1];  /*上报时间*/
		/*上报时间*/
	int   ysbjls;  /*预上报记录数*/
		/*预上报记录数*/
	int   wsbjls;  /*已上报记录数*/
		/*已上报记录数*/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   by1[30+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_PCGY;

#define SD_DATA  GAB_DXZP_PCGY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_STRING,  scrq, 0),\
	DEFSDMEMBER(T_STRING,  sjgs, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  sbjg, 0),\
	DEFSDMEMBER(T_STRING,  sbgy, 0),\
	DEFSDMEMBER(T_STRING,  sbrq, 0),\
	DEFSDMEMBER(T_STRING,  sbsj, 0),\
	DEFSDMEMBER(T_LONG,  ysbjls, 0),\
	DEFSDMEMBER(T_LONG,  wsbjls, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_PCGY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_PCGY_H__*/
