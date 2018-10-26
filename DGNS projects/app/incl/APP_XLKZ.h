/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_XLKZ.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_XLKZ (序列控制表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_XLKZ_H__
#define __APP_XLKZ_H__
typedef struct TDB_APP_XLKZ
{
  char   pkey[20+1];              /*KEY值*/
              /**/
  int    curr_value;              /*当前值*/
              /**/
  int    pinc;              /*步进值*/
              /**/
  int    min_value;              /*最小值*/
              /**/
  int    max_value;              /*最大值*/
              /**/
  char   remark[40+1];              /*说明*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}APP_XLKZ;

#define SD_DATA  APP_XLKZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  pkey, 0),\
	DEFSDMEMBER(T_LONG,  curr_value, 0),\
	DEFSDMEMBER(T_LONG,  pinc, 0),\
	DEFSDMEMBER(T_LONG,  min_value, 0),\
	DEFSDMEMBER(T_LONG,  max_value, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_XLKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_XLKZ_H__*/
