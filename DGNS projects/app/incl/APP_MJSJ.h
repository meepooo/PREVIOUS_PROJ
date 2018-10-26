/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_MJSJ.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_MJSJ (枚举数据表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_MJSJ_H__
#define __APP_MJSJ_H__
typedef struct TDB_APP_MJSJ
{
  char   mjid[16+1];              /*枚举ID*/
              /*枚举ID*/
  char   mjsm[40+1];              /*枚举说明*/
              /*枚举说明*/
  int    sjxh;              /*数据序号*/
              /*数据序号*/
  char   qsbz[1+1];              /*缺省标识*/
              /*缺省标识  0是 1非*/
  char   req1[40+1];              /*条件1*/
              /**/
  char   req2[40+1];              /*条件2*/
              /**/
  char   req3[40+1];              /*条件3*/
              /**/
  char   req4[40+1];              /*条件4*/
              /**/
  char   req5[40+1];              /*条件5*/
              /**/
  char   req6[40+1];              /*条件6*/
              /**/
  char   req7[40+1];              /*条件7*/
              /**/
  char   req8[40+1];              /*条件8*/
              /**/
  char   req9[40+1];              /*条件9*/
              /**/
  char   req10[40+1];              /*条件10*/
              /**/
  char   resp1[40+1];              /*结果1*/
              /**/
  char   resp2[40+1];              /*结果2*/
              /**/
  char   resp3[40+1];              /*结果3*/
              /**/
  char   resp4[40+1];              /*结果4*/
              /**/
  char   resp5[40+1];              /*结果5*/
              /**/
  char   resp6[40+1];              /*结果6*/
              /**/
  char   resp7[40+1];              /*结果7*/
              /**/
  char   resp8[40+1];              /*结果8*/
              /**/
  char   resp9[40+1];              /*结果9*/
              /**/
  char   resp10[40+1];              /*结果10*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}APP_MJSJ;

#define SD_DATA  APP_MJSJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mjid, 0),\
	DEFSDMEMBER(T_STRING,  mjsm, 0),\
	DEFSDMEMBER(T_LONG,  sjxh, 0),\
	DEFSDMEMBER(T_STRING,  qsbz, 0),\
	DEFSDMEMBER(T_STRING,  req1, 0),\
	DEFSDMEMBER(T_STRING,  req2, 0),\
	DEFSDMEMBER(T_STRING,  req3, 0),\
	DEFSDMEMBER(T_STRING,  req4, 0),\
	DEFSDMEMBER(T_STRING,  req5, 0),\
	DEFSDMEMBER(T_STRING,  req6, 0),\
	DEFSDMEMBER(T_STRING,  req7, 0),\
	DEFSDMEMBER(T_STRING,  req8, 0),\
	DEFSDMEMBER(T_STRING,  req9, 0),\
	DEFSDMEMBER(T_STRING,  req10, 0),\
	DEFSDMEMBER(T_STRING,  resp1, 0),\
	DEFSDMEMBER(T_STRING,  resp2, 0),\
	DEFSDMEMBER(T_STRING,  resp3, 0),\
	DEFSDMEMBER(T_STRING,  resp4, 0),\
	DEFSDMEMBER(T_STRING,  resp5, 0),\
	DEFSDMEMBER(T_STRING,  resp6, 0),\
	DEFSDMEMBER(T_STRING,  resp7, 0),\
	DEFSDMEMBER(T_STRING,  resp8, 0),\
	DEFSDMEMBER(T_STRING,  resp9, 0),\
	DEFSDMEMBER(T_STRING,  resp10, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_MJSJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_MJSJ_H__*/

