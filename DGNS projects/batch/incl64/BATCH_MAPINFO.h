/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_MAPINFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_MAPINFO (批量映射信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_MAPINFO_H__
#define __BATCH_MAPINFO_H__
typedef struct TDB_BATCH_MAPINFO
{
  char   mapid[32+1];              /*映射标识*/
              /**/
  char   maptype[1+1];              /*映射类型*/
              /*0 外围文件映射
                1 主机文件映射*/
  char   mapidnote[40+1];              /*映射标识说明*/
              /**/
  char   ywbm[32+1];              /*关联表名*/
              /**/
  char   lpwjbs[32+1];              /*来盘文件标识*/
              /**/
  char   hpwjbs[32+1];              /*回盘文件标识*/
              /**/
  char   tjwjbs[32+1];              /*主机提交文件标识*/
              /**/
  char   thwjbs[32+1];              /*主机提回文件标识*/
              /**/
  long    jlsxz;              /*主机记录数限制*/
              /*主机批扣文件最大记录数 默认 0  不控制*/
  char   zhbz[1+1];              /*响应码转换标志*/
              /*0 转换 1 不转换*/
  char   zhbs[32+1];              /*响应码转换标识*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}BATCH_MAPINFO;

#define SD_DATA  BATCH_MAPINFO
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mapid, 0),\
	DEFSDMEMBER(T_STRING,  maptype, 0),\
	DEFSDMEMBER(T_STRING,  mapidnote, 0),\
	DEFSDMEMBER(T_STRING,  ywbm, 0),\
	DEFSDMEMBER(T_STRING,  lpwjbs, 0),\
	DEFSDMEMBER(T_STRING,  hpwjbs, 0),\
	DEFSDMEMBER(T_STRING,  tjwjbs, 0),\
	DEFSDMEMBER(T_STRING,  thwjbs, 0),\
	DEFSDMEMBER(T_LONG,  jlsxz, 0),\
	DEFSDMEMBER(T_STRING,  zhbz, 0),\
	DEFSDMEMBER(T_STRING,  zhbs, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_MAPINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_MAPINFO_H__*/
