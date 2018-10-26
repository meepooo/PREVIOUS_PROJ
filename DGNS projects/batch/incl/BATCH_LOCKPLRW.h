/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_LOCKPLRW.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_LOCKPLRW (锁定批量任务)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_LOCKPLRW_H__
#define __BATCH_LOCKPLRW_H__
typedef struct TDB_BATCH_LOCKPLRW
{
    char   pkrq[8+1];           /*批扣日期*/
    char   ptpch[8+1];          /*平台批次号*/
    char   curstep[2+1];        /*当前步点*/
    char   curassstep[2+1];     /*当前辅助步点*/
    char   curstatus[1+1];      /*步点状态*/
    char   taskstatus[1+1];     /*任务状态*/
    char   wherestep[2+1];      /*条件步点*/
    char   whereassstep[2+1];   /*条件辅助步点*/
    char   wherestatus[2+1];    /*条件状态*/
    char   wheretask[2+1];      /*条件任务*/
}BATCH_LOCKPLRW;

#endif  /*end of __BATCH_LOCKPLRW_H__*/
