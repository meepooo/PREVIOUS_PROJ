/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_FILEMAP.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_FILEMAP (批量表结构与文件映射关系表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_FILEMAP_H__
#define __BATCH_FILEMAP_H__
typedef struct TDB_BATCH_FILEMAP
{
  char   mapid[32+1];              /*映射标识*/
              /**/
  long    flxh;              /*分类序号*/
              /**/
  long    columnsn;              /*列序号*/
              /**/
  char   columnid[16+1];              /*列标识*/
              /*对应业务表结构注册信息表里的列名*/
  char   lylx[1+1];              /*来源类型*/
              /*1：来盘文件获取，2：xml获取，3：流程获取，4：序列获取，5：填值，6：赋空*/
  char   lywz[60+1];              /*来源位置*/
              /*根据来源类型填*/
  long    zjszwz;              /*主机上账位置*/
              /*主机上账文件列序号*/
  long    zjjgwz;              /*主机结果位置*/
              /*主机结果文件列序号*/
  char   thgxbz[1+1];              /*主机文件提回更新标志*/
              /*0是1否*/
  long    hpwjwz;              /*回盘文件位置*/
              /*回盘文件列序号*/

}BATCH_FILEMAP;

#define SD_DATA  BATCH_FILEMAP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mapid, 0),\
	DEFSDMEMBER(T_LONG,  flxh, 0),\
	DEFSDMEMBER(T_LONG,  columnsn, 0),\
	DEFSDMEMBER(T_STRING,  columnid, 0),\
	DEFSDMEMBER(T_STRING,  lylx, 0),\
	DEFSDMEMBER(T_STRING,  lywz, 0),\
	DEFSDMEMBER(T_LONG,  zjszwz, 0),\
	DEFSDMEMBER(T_LONG,  zjjgwz, 0),\
	DEFSDMEMBER(T_STRING,  thgxbz, 0),\
	DEFSDMEMBER(T_LONG,  hpwjwz, 0)


	DECLAREFIELDS(SD_BATCH_FILEMAP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_FILEMAP_H__*/
