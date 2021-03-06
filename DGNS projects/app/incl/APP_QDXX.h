/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_QDXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_QDXX (渠道信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_QDXX_H__
#define __APP_QDXX_H__
typedef struct TDB_APP_QDXX
{
  char   qdbs[3+1];              /*渠道标识*/
              /*渠道标识 见数据字典 KEY=K_QDB */
  char   qdmc[40+1];              /*渠道名称*/
              /*渠道名称*/
  char   qdsm[80+1];              /*渠道中文说明*/
              /*渠道中文说明*/
  char   sjkzbz[1+1];              /*时间控制标志*/
              /*时间控制标志 0 控� 1不控制*/
  char   qssj[8+1];              /*起始时间*/
              /*起始时间 */
  char   jssj[8+1];              /*结束时间*/
              /*结束时间*/
  char   czbz[1+1];              /*冲正标志*/
              /*是否允许冲正  0允许 1不允许*/
  char   zdczbz[1+1];              /*自动冲正标志*/
              /*系统异常是否自动冲正  0是 1否*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[40+1];              /*扩展字段1*/
              /*扩展字段1*/
  char   extfld2[40+1];              /*扩展字段2*/
              /*扩展字段2*/
  char   qdzt[1+1];              /*渠道状态*/
              /*渠道状态 0开启 1关闭*/
}APP_QDXX;

#define SD_DATA  APP_QDXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  qdmc, 0),\
	DEFSDMEMBER(T_STRING,  qdsm, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  czbz, 0),\
	DEFSDMEMBER(T_STRING,  zdczbz, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qdzt, 0)


	DECLAREFIELDS(SD_APP_QDXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_QDXX_H__*/
