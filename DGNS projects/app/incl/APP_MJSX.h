/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_MJSX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_MJSX (枚举属性控制表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_MJSX_H__
#define __APP_MJSX_H__
typedef struct TDB_APP_MJSX
{
  char   mjid[16+1];              /*枚举ID*/
              /*枚举ID*/
  char   mjsm[40+1];              /*枚举说明*/
              /*枚举说明*/
  char   sxlx[1+1];              /*属性类型*/
              /*属性类型 1条件 2结果*/
  char   sxxh[2+1];              /*属性序号*/
              /*属性根据属性类型，从1开始，不能大于10，与关系表的位置相对应*/
  char   sxmc[16+1];              /*属性名称*/
              /*属性名称*/
  char   sxnr[40+1];              /*属性内容位置*/
              /*如果类型为条件，表示数据的来源，如果类型为结果，数据的目的*/
  char   sxsm[40+1];              /*属性说明*/
              /*属性的中文说明*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}APP_MJSX;

#define SD_DATA  APP_MJSX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mjid, 0),\
	DEFSDMEMBER(T_STRING,  mjsm, 0),\
	DEFSDMEMBER(T_STRING,  sxlx, 0),\
	DEFSDMEMBER(T_STRING,  sxxh, 0),\
	DEFSDMEMBER(T_STRING,  sxmc, 0),\
	DEFSDMEMBER(T_STRING,  sxnr, 0),\
	DEFSDMEMBER(T_STRING,  sxsm, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_MJSX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_MJSX_H__*/

