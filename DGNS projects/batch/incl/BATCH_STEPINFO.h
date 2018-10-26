/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_STEPINFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_STEPINFO (批量步点信息)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_STEPINFO_H__
#define __BATCH_STEPINFO_H__
typedef struct TDB_BATCH_STEPINFO
{
    char   pkrq[8+1];           /*批扣日期*/
    char   ptpch[8+1];          /*平台批次号*/
    char   cpdm[16+1];          /*产品代码*/
    char   ywbh[16+1];          /*业务编号*/
    char   flowid[32+1];        /*流程标识*/
    char   ywb[32+1];           /*业务表*/
    char   zjysbs[32+1];        /*主机映射标识*/
    char   wwysbs[32+1];        /*外围映射标识*/
    char   curstep[2+1];        /*当前步点*/
    char   curassstep[2+1];     /*当前辅助步点*/
    char   curstatus[1+1];      /*步点状态*/
    char   taskstatus[1+1];     /*任务状态*/
    char   nextstep[2+1];       /*下一步点*/
    char   stepid[32+1];        /*步点标识*/
    char   stepnm[32+1];        /*步点名称*/
    int    flowsn;              /*执行序号*/
    char   extfld1[40+1];       /*扩展字段1*/
    char   extfld2[40+1];       /*扩展字段2*/
}BATCH_STEPINFO;

#endif  /*end of __BATCH_STEPINFO_H__*/
