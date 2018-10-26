/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:COUPON_WIAMP_DZLSB.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:COUPON_WIAMP_DZLSB(卡券平台对账流水号)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __COUPON_WIAMP_DZLSB_H__
#define __COUPON_WIAMP_DZLSB_H__
typedef struct TDB_COUPON_WIAMP_DZLSB
{
  char   dzrq[8+1];              /*对账日期*/
  char   changeorderno[128+1];
  char   weiorderno[128+1];
  char   busses_id[20+1];
  char   couponno[128+1];
  char   user_id[20+1];
  int    couponnum;   
  char   gettime[20+1];
  double couponprize;
  char   orderstatus[2+1];
}COUPON_WIAMP_DZLSB;

#define SD_DATA COUPON_WIAMP_DZLSB 
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  changeorderno, 0),\
	DEFSDMEMBER(T_STRING,  weiorderno, 0),\
	DEFSDMEMBER(T_STRING,  busses_id, 0),\
	DEFSDMEMBER(T_STRING,  couponno, 0),\
	DEFSDMEMBER(T_STRING,  user_id, 0),\
	DEFSDMEMBER(T_LONG,    couponnum, 0),\
	DEFSDMEMBER(T_STRING,  gettime, 0),\
	DEFSDMEMBER(T_DOUBLE,  couponprize, 2),\
	DEFSDMEMBER(T_STRING,  orderstatus, 0)

	DECLAREFIELDS(SD_COUPON_WIAMP_DZLSB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __COUPON_WIAMP_DZLSB_H__*/

