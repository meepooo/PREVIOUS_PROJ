/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_FILECOLUMN.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_FILECOLUMN (批量文件列信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_FILECOLUMN_H__
#define __BATCH_FILECOLUMN_H__
typedef struct TDB_BATCH_FILECOLUMN
{
  char   fileid[32+1];              /*文件标识*/
              /**/
  long    fileclasssn;              /*文件分类序号*/
              /**/
  long    columnsn;              /*列序号*/
              /**/
  char   columnid[16+1];              /*列标识*/
              /**/
  char   isid[1+1];              /*是否可空*/
              /*0是1否*/
  char   columnname[40+1];              /*列名称*/
              /**/
  char   lsx[1+1];              /*列属性*/
              /*标识特定列属性，如金额（A+，A-）*/
  long    offset;              /*起始位置*/
              /**/
  long    columnlen;              /*内容长度*/
              /**/
  long    iprecision;              /*小数精度*/
              /**/
  long    izoom;              /*小数偏移*/
              /**/
  char   regular[1+1];              /*对齐方式*/
              /*对齐方式：（l 左对齐,R 右对齐）缺省为L*/
  long    ifiller;              /*填充字符*/
              /*填充符的ASCII编码*/
  char   fldref[32+1];              /*数据路径*/
              /**/
  char   snote[32+1];              /*说明*/
              /**/
  char   extfld1[60+1];              /*扩展字段一*/
              /**/
}BATCH_FILECOLUMN;

#define SD_DATA  BATCH_FILECOLUMN
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  fileid, 0),\
	DEFSDMEMBER(T_LONG,  fileclasssn, 0),\
	DEFSDMEMBER(T_LONG,  columnsn, 0),\
	DEFSDMEMBER(T_STRING,  columnid, 0),\
	DEFSDMEMBER(T_STRING,  isid, 0),\
	DEFSDMEMBER(T_STRING,  columnname, 0),\
	DEFSDMEMBER(T_STRING,  lsx, 0),\
	DEFSDMEMBER(T_LONG,  offset, 0),\
	DEFSDMEMBER(T_LONG,  columnlen, 0),\
	DEFSDMEMBER(T_LONG,  iprecision, 0),\
	DEFSDMEMBER(T_LONG,  izoom, 0),\
	DEFSDMEMBER(T_STRING,  regular, 0),\
	DEFSDMEMBER(T_LONG,  ifiller, 0),\
	DEFSDMEMBER(T_STRING,  fldref, 0),\
	DEFSDMEMBER(T_STRING,  snote, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0)


	DECLAREFIELDS(SD_BATCH_FILECOLUMN)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILECOLUMN_H__*/
