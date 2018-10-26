/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_FILESORT.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_FILESORT (批量文件分类信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_FILESORT_H__
#define __BATCH_FILESORT_H__
typedef struct TDB_BATCH_FILESORT
{
  char   fileid[32+1];              /*文件标识*/
              /**/
  int    fileclasssn;              /*文件分类序号*/
              /**/
  char   classname[40+1];              /*分类名称*/
              /**/
  char   classtype[1+1];              /*分类类型*/
              /*1：汇总，2：明细*/
  int    higherupsn;              /*上级分类序号*/
              /**/
  char   positionflag[1+1];              /*位置标志*/
              /*备用*/
  char   classposition[32+1];              /*位置*/
              /*备用*/
  int    columnno;              /*列数*/
              /**/
  char   rowsprtr[32+1];              /*行分隔符*/
              /*备用*/
  char   sprtrattrib[1+1];              /*行分隔符属性*/
              /*备用*/
  char   columnflag[1+1];              /*列分隔标志*/
              /*1定长2分隔*/
  char   columnsprtr[32+1];              /*列分隔符*/
              /**/
  char   extfld1[60+1];              /*扩展字段一*/
              /**/

}BATCH_FILESORT;

#define SD_DATA  BATCH_FILESORT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  fileid, 0),\
	DEFSDMEMBER(T_LONG,  fileclasssn, 0),\
	DEFSDMEMBER(T_STRING,  classname, 0),\
	DEFSDMEMBER(T_STRING,  classtype, 0),\
	DEFSDMEMBER(T_LONG,  higherupsn, 0),\
	DEFSDMEMBER(T_STRING,  positionflag, 0),\
	DEFSDMEMBER(T_STRING,  classposition, 0),\
	DEFSDMEMBER(T_LONG,  columnno, 0),\
	DEFSDMEMBER(T_STRING,  rowsprtr, 0),\
	DEFSDMEMBER(T_STRING,  sprtrattrib, 0),\
	DEFSDMEMBER(T_STRING,  columnflag, 0),\
	DEFSDMEMBER(T_STRING,  columnsprtr, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0)


	DECLAREFIELDS(SD_BATCH_FILESORT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILESORT_H__*/
