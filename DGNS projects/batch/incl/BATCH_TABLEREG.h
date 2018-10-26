/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_TABLEREG.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_TABLEREG (批量业务表结构注册信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_TABLEREG_H__
#define __BATCH_TABLEREG_H__
typedef struct TDB_BATCH_TABLEREG
{
  char   tablename[32+1];              /*表名*/
              /**/
  int    fldsn;              /*字段序号*/
              /**/
  char   fldid[16+1];              /*字段标识*/
              /**/
  char   fldname[40+1];              /*字段名称*/
              /**/
  char   fldtype[1+1];              /*字段类型*/
              /*I整形D浮点C字符串*/
  char   fldlen[10+1];              /*字段长度*/
              /**/
  char   decimaldigits[10+1];              /*小数位数*/
              /**/
  char   iskey[1+1];              /*是否为主键*/
              /*0是1不是（默认1)*/
  char   isnull[1+1];              /*是否允许为空*/
              /*0允许1不允许 （默认0)*/
  char   fldshd[1+1];              /*屏蔽标志*/
              /*0不屏蔽 1-部分屏蔽 2-全屏蔽*/
}BATCH_TABLEREG;

#define SD_DATA  BATCH_TABLEREG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  tablename, 0),\
	DEFSDMEMBER(T_LONG,  fldsn, 0),\
	DEFSDMEMBER(T_STRING,  fldid, 0),\
	DEFSDMEMBER(T_STRING,  fldname, 0),\
	DEFSDMEMBER(T_STRING,  fldtype, 0),\
	DEFSDMEMBER(T_STRING,  fldlen, 0),\
	DEFSDMEMBER(T_STRING,  decimaldigits, 0),\
	DEFSDMEMBER(T_STRING,  iskey, 0),\
	DEFSDMEMBER(T_STRING,  isnull, 0),\
    DEFSDMEMBER(T_STRING,  fldshd, 0)

	DECLAREFIELDS(SD_BATCH_TABLEREG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_TABLEREG_H__*/
