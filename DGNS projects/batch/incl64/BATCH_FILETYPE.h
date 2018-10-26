/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_FILETYPE.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_FILETYPE (批量文件类型表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_FILETYPE_H__
#define __BATCH_FILETYPE_H__
typedef struct TDB_BATCH_FILETYPE
{
  char   fileid[32+1];              /*文件标识*/
              /**/
  char   fileidnote[40+1];              /*文件标识说明*/
              /**/
  char   filetype[1+1];              /*文件类型*/
              /*0- txt 1-DBF 2-xls 3-xlsx 4-dbf  默认 0*/
  char   filefmt[2+1];              /*文件格式*/
              /*01  单明细
                02  汇总＋单明细
                03  单明细＋汇总
                04  汇总＋单明细＋汇总
                */
  char   codefmt[1+1];              /*编码格式*/
              /*编码格式 0-ascii 1-utf-8 2-base64*/
  char   extfld1[32+1];              /*扩展字段一*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}BATCH_FILETYPE;

#define SD_DATA  BATCH_FILETYPE
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  fileid, 0),\
	DEFSDMEMBER(T_STRING,  fileidnote, 0),\
	DEFSDMEMBER(T_STRING,  filetype, 0),\
	DEFSDMEMBER(T_STRING,  filefmt, 0),\
	DEFSDMEMBER(T_STRING,  codefmt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_FILETYPE)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILETYPE_H__*/
