/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_MAPRESP.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_MAPRESP (批量响应码映射)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_MAPRESP_H__
#define __BATCH_MAPRESP_H__
typedef struct TDB_BATCH_MAPRESP
{
	char   mapid[32+1];  /*映射标识*/
		/**/
	char   note[40+1];  /*映射说明*/
		/**/
	char   resp_s[10+1];  /*源响应码*/
		/**/
	char   resp_d[10+1];  /*映射响应码*/
		/**/
	char   msg_d[40+1];  /*响应信息*/
		/**/
	char   bz[1+1];  /*默认转换标识*/
		/*默认转换标识 0 �  � 默�  一个响应码资源，最多一� 默认转换*/
	char   whjg[16+1];  /*维护机构*/
		/**/
	char   whgy[16+1];  /*维护柜员*/
		/**/
	char   whsj[14+1];  /*维护时间*/
		/**/

}BATCH_MAPRESP;

#define SD_DATA  BATCH_MAPRESP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mapid, 0),\
	DEFSDMEMBER(T_STRING,  note, 0),\
	DEFSDMEMBER(T_STRING,  resp_s, 0),\
	DEFSDMEMBER(T_STRING,  resp_d, 0),\
	DEFSDMEMBER(T_STRING,  msg_d, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_MAPRESP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_MAPRESP_H__*/
