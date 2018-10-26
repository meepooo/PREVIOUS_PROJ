/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:COUPON_DZBPB.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:COUPON_DZBPB(对帐不平表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __COUPON_DZBPB_H__
#define __COUPON_DZBPB_H__
typedef struct TDB_COUPON_DZBPB
{
  char   ptrq[8+1];              /*平台日期*/
  char   dzrq[8+1];              /*对账日期*/
  char   changeorderno[128+1];
  char   weiorderno[128+1];
  char   couponno[128+1];
  char   status[2+1];
  int    wiamp_ordernum;   
  int    zjyw_ordernum;
  char   extfld1[20+1];
  char   extfld2[20+1];
}COUPON_DZBPB;

#define SD_DATA COUPON_DZBPB 
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  changeorderno, 0),\
	DEFSDMEMBER(T_STRING,  weiorderno, 0),\
	DEFSDMEMBER(T_STRING,  couponno, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_LONG,    wiamp_ordernum, 0),\
	DEFSDMEMBER(T_LONG,    zjyw_ordernum, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)

	DECLAREFIELDS(SD_COUPON_DZBPB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __COUPON_DZBPB_H__*/

