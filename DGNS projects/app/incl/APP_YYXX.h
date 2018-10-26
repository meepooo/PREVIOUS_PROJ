/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_YYXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_YYXX (应用信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_YYXX_H__
#define __APP_YYXX_H__
typedef struct TDB_APP_YYXX
{
  char   yybs[8+1];              /*应用标识*/
              /*应用标识 */
  char   yymc[40+1];              /*应用名称*/
              /*应用名称*/
  char   yysm[80+1];              /*应用说明*/
              /*应用说明*/
  char   yykfksrq[8+1];              /*应用开发开始日期*/
              /*应用开发开始日期*/
  char   yykfjsrq[8+1];              /*应用开发结束日期*/
              /*应用开发结束日期*/
  char   yyfbrq[8+1];              /*应用发布日期*/
              /*应用发布日期*/
  char   yybbh[20+1];              /*应用版本号*/
              /*应用版本号*/
  char   yhh[40+1];              /*用户号*/
              /*用户号*/
  char   sqh[40+1];              /*授权号*/
              /*授权号*/
  char   yykfjl[40+1];              /*应用开发经理*/
              /*应用开发经理*/
  char   yyzbjl[40+1];              /*应用质保经理*/
              /*应用质保经理*/
  char   yyzt[1+1];              /*应用状态*/
              /*0正常 1关闭*/
  char   extfld[40+1];              /*扩展字段*/
              /*扩展字段*/
}APP_YYXX;

#define SD_DATA  APP_YYXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  yymc, 0),\
	DEFSDMEMBER(T_STRING,  yysm, 0),\
	DEFSDMEMBER(T_STRING,  yykfksrq, 0),\
	DEFSDMEMBER(T_STRING,  yykfjsrq, 0),\
	DEFSDMEMBER(T_STRING,  yyfbrq, 0),\
	DEFSDMEMBER(T_STRING,  yybbh, 0),\
	DEFSDMEMBER(T_STRING,  yhh, 0),\
	DEFSDMEMBER(T_STRING,  sqh, 0),\
	DEFSDMEMBER(T_STRING,  yykfjl, 0),\
	DEFSDMEMBER(T_STRING,  yyzbjl, 0),\
	DEFSDMEMBER(T_STRING,  yyzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld, 0)


	DECLAREFIELDS(SD_APP_YYXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_YYXX_H__*/
