/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:COUPON_ZJYW_RZZT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:COUPON_ZJYW_RZZT(卡券平台对账汇总表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __COUPON_ZJYW_RZZT_H__
#define __COUPON_ZJYW_RZZT_H__
typedef struct TDB_COUPON_ZJYW_RZZT
{
  char   ptrq[8+1];              /*平台日期*/
  char   dzrq[8+1];              /*对账日期*/
  char   status[2+1];
  int    wiamp_zbs;   
  int    zjyw_zbs;
  char   extfld1[20+1];
  char   extfld2[20+1];
}COUPON_ZJYW_RZZT;

#define SD_DATA COUPON_ZJYW_RZZT 
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_LONG,    wiamp_zbs, 0),\
	DEFSDMEMBER(T_LONG,    zjyw_zbs, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)

	DECLAREFIELDS(SD_COUPON_ZJYW_RZZT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __COUPON_ZJYW_RZZT_H__*/

