/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_ZJXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_ZJXX (批量文件类型表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_ZJXX_H__
#define __BATCH_ZJXX_H__
typedef struct TDB_BATCH_ZJXX
{
  char   hostid[30+1];      
  long   flag;              
  char   status[1+1];     
  char   bak1[40+1];    
  char   bak2[40+1];   
}BATCH_ZJXX;

#define SD_DATA  BATCH_ZJXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  hostid, 0),\
	DEFSDMEMBER(T_LONG,  flag, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_STRING,  bak1, 0),\
	DEFSDMEMBER(T_STRING,  bak2, 0)

	DECLAREFIELDS(SD_BATCH_ZJXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_ZJXX_H__*/
