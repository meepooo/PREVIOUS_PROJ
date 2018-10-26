/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_SPLITFILECONTROL.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[孙朋君]
发布时间:2017-7-20 09:04:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_SPLITFILECONTROL (批量平台文件分割控制表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_SPLITFILECONTROL_H__
#define __BATCH_SPLITFILECONTROL_H__
typedef struct TDB_BATCH_SPLITFILECONTROL
{
    char    host_batch_no[26+1];
    char    host_no[2+1];
    char    o_file_req[512+1];
    char    file_req[512+1];
    char    file_resp[512+1];
    char    n_file_resp[512+1];
    char    state[1+1];
    char    remark1[10+1];
    char    remark2[20+1];
    char    remark3[50+1];
    char    remark4[100+1];
    char    remark5[200+1];
}BATCH_SPLITFILECONTROL;

#define SD_DATA  BATCH_SPLITFILECONTROL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  host_batch_no, 0),\
	DEFSDMEMBER(T_STRING,  host_no, 0),\
	DEFSDMEMBER(T_STRING,  o_file_req, 0),\
	DEFSDMEMBER(T_STRING,  file_req, 0),\
	DEFSDMEMBER(T_STRING,  file_resp, 0),\
	DEFSDMEMBER(T_STRING,  n_file_resp, 0),\
	DEFSDMEMBER(T_STRING,  state, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0),\
	DEFSDMEMBER(T_STRING,  remark5, 0)

	DECLAREFIELDS(SD_BATCH_SPLITFILECONTROL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_SPLITFILECONTROL_H__*/
