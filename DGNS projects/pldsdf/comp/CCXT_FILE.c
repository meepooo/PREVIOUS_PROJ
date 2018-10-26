/********************************************************************
 版权所有:恒生电子股份有限公司
 项目名称:综合应用平台（GAPS）项目
 版    本:V3.0.00
 操作系统:AIX5.3
 文件名称:PLDSDF_FILE.c
 文件描述:批量业务处理文件映射-数据提回处理转换组件集
 项 目 组:中间业务项目组
 程 序 员:zengy
 发布日期:2017-10-24
 修    订:
 修改日期:  
 *********************************************************************/
/**********************************************************************
 总体说明:
 函数说明
 组件函数名称                 组件名称                      发布日期  程序员 修改日期 修改人
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"
#include "../eh/agent_batch_info.h"
#include "../../app/incl/APP_KHCPQY.h"

/************************************************************************
  动态组件函数定义
  组件函数名称: SPLDSDF_FILE_PRE_DEAL
  组件名称: 批量代收代付文件前处理

  组件功能: 
            文件前处理: 总笔数、总金额校验; 文件格式校验等
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: zhandd
  发布日期: 2017年10月24日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SCCXTDS_FILE_PRE_DEAL(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas = 0;
    int iComStat = 0; /*组件返回码*/
    long lTotCnt = 0; /*从文件读取的笔数*/
    double dTotAmt = 0.00;
    char line_count[20];
    char sSfbz[1+1];
    char sJybs[10];
    char sJyje[17];
    char sDsrq[8];
    char sDwbh[16+1];
    char sBuf[512];
    char sFileName[256+1];
    char sFilePath[256+1];
    char sNewFilePath[256+1];
    char sLine[1024];
    char sNewLine[1024];
    char sCmd[512];
    char sErrmsg[512];
    char sMd5[64];
    char sMd5_1[64];
    char sMd5_2[64];
    char sLast_line[256+1];
    char sWj_line[10]; /*来盘文件行数*/
    FILE *fp = NULL;

    SDB_AGENT_BATCH_INFO sdb_agent_batch_info;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* 组件参数检查 */
    COMP_PARACOUNTCHKMIN(2)

    /* 文件名 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    COMP_GETPARSEPARAS(1, sBuf, "来盘文件名")
    trim(sBuf);
    pstrcopy(sFileName, sBuf, sizeof(sFileName));
    LOG(LM_DEBUG, Fmtmsg("来盘文件名[%s]", sFileName), "INFO")

    /* 收付标志 1-收2-付 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    COMP_GETPARSEPARAS(2, sBuf, "收付标志")
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("收付标志[%s]", sSfbz), "INFO")

    memset(&sdb_agent_batch_info, 0x00, sizeof(sdb_agent_batch_info));

    /* 批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/batch/req/shpch", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.batch_no, sBuf, sizeof(sdb_agent_batch_info.batch_no));
    LOG(LM_DEBUG, Fmtmsg("批次号[%s]", sdb_agent_batch_info.batch_no), "INFO")

    /* 产品代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/cpdm", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.cpdm, sBuf, sizeof(sdb_agent_batch_info.cpdm));
    LOG(LM_DEBUG, Fmtmsg("产品代码[%s]", sdb_agent_batch_info.cpdm), "INFO")

    /* 单位编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.dwbh, sBuf, sizeof(sdb_agent_batch_info.dwbh));
    LOG(LM_DEBUG, Fmtmsg("单位编号[%s]", sdb_agent_batch_info.dwbh), "INFO")

    /* 原上传文件名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/ori_file_name", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.file_name, sBuf, sizeof(sdb_agent_batch_info.file_name));
    LOG(LM_DEBUG, Fmtmsg("原上传文件名[%s]", sdb_agent_batch_info.file_name), "INFO")

    /* 上传日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zwrq", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_date, sBuf, sizeof(sdb_agent_batch_info.up_date));
    LOG(LM_DEBUG, Fmtmsg("上传日期[%s]", sdb_agent_batch_info.up_date), "INFO")

    /* 上传流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zhqzlsh", sBuf);
    sdb_agent_batch_info.up_seq_no = atol(sBuf);
    LOG(LM_DEBUG, Fmtmsg("上传流水号[%ld]", sdb_agent_batch_info.up_seq_no), "INFO")

    /* 上传时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_time, sBuf, sizeof(sdb_agent_batch_info.up_time));
    LOG(LM_DEBUG, Fmtmsg("上传时间[%s]", sdb_agent_batch_info.up_time), "INFO")

    /* 上传机构 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/brc", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_unit, sBuf, sizeof(sdb_agent_batch_info.up_unit));
    LOG(LM_DEBUG, Fmtmsg("上传机构[%s]", sdb_agent_batch_info.up_unit), "INFO")

    /* 上传柜员 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/tel", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_teller, sBuf, sizeof(sdb_agent_batch_info.up_teller));
    LOG(LM_DEBUG, Fmtmsg("上传柜员[%s]", sdb_agent_batch_info.up_teller), "INFO")

    /* 上传渠道标识 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/qdbs", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.up_channel, sBuf, sizeof(sdb_agent_batch_info.up_channel));
    LOG(LM_DEBUG, Fmtmsg("上传渠道标识[%s]", sdb_agent_batch_info.up_channel), "INFO")

    /* 上传方式 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/scfs", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.upload_type, sBuf, sizeof(sdb_agent_batch_info.upload_type));
    LOG(LM_DEBUG, Fmtmsg("上传方式[%s]", sdb_agent_batch_info.upload_type), "INFO")

    /* 收付标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/sfbz", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.dc_flag, sBuf, sizeof(sdb_agent_batch_info.dc_flag));
    LOG(LM_DEBUG, Fmtmsg("收付标志[%s]", sdb_agent_batch_info.dc_flag), "INFO")

    /* 入账运行日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/exec_date", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.exec_date, sBuf, sizeof(sdb_agent_batch_info.exec_date));
    LOG(LM_DEBUG, Fmtmsg("入账运行日期[%s]", sdb_agent_batch_info.exec_date), "INFO")
    if(strlen(sdb_agent_batch_info.exec_date) > 0 &&
        strcmp(sdb_agent_batch_info.exec_date, sdb_agent_batch_info.up_date) < 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, "入账运行日期不能小于当前日期");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("入账运行日期不能小于当前日期"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    /* 摘要代码（上核心使用) */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/batch/req/zydm", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.brief_code, sBuf, sizeof(sdb_agent_batch_info.brief_code));
    LOG(LM_DEBUG, Fmtmsg("摘要代码[%s]", sdb_agent_batch_info.brief_code), "INFO")

    /* md5码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/MD5", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.md5_code, sBuf, sizeof(sdb_agent_batch_info.md5_code));
    LOG(LM_DEBUG, Fmtmsg("md5码[%s]", sdb_agent_batch_info.md5_code), "INFO")

    /* 状态 8-待入账申请 */
    pstrcopy(sdb_agent_batch_info.stat, "8", sizeof(sdb_agent_batch_info.stat));
    
    /* 文件类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/wjlx", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.wjlx, sBuf, sizeof(sdb_agent_batch_info.wjlx));
    LOG(LM_DEBUG, Fmtmsg("文件类型[%s]", sdb_agent_batch_info.wjlx), "INFO")

    /* 来盘文件名 */
    strcpy(sdb_agent_batch_info.ori_file_name, sFileName);
        
    memset(sFilePath, 0x00, sizeof(sFilePath));
    sprintf(sFilePath, "%s/file/batch/ccxt/%s", getenv("HOME"), sdb_agent_batch_info.ori_file_name);
    LOG(LM_DEBUG, Fmtmsg("原批量请求文件[%s]", sFilePath), "INFO")
 
    /*计算文件行数sWj_line*/
    iRet=fpub_ExecComp(lXmlhandle,"FILE_GetFileSize",&iComStat,3,sFilePath,"2","/agent/req/wj_line");
    if(iRet!=MID_SYS_SUCC || iComStat!=COMPSTATUS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, 24103, "计算文件行数失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("计算文件行数失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }
    memset(sWj_line, 0x00, sizeof(sWj_line));
    COMP_SOFTGETXML("/agent/req/wj_line", sWj_line);
    trim(sWj_line);
    LOG(LM_DEBUG, Fmtmsg("文件行数[%s]", sWj_line), "INFO")

    /*获取文件最后一行,汇总信息*/
    iRet=fpub_ExecComp(lXmlhandle,"FILE_LoadToX",&iComStat,5,"file_ccxt_hzxx",sFilePath,sWj_line,"0","/agent/file_hz");
    if(iRet!=MID_SYS_SUCC || iComStat!=COMPSTATUS_SUCC)
    {
        fpub_SetMsg(lXmlhandle, 24103, "计算文件行数失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("计算文件行数失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/file_hz|1/zbs", sBuf);
    trim(sBuf);
    lTotCnt=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/file_hz|1/zje", sBuf);
    trim(sBuf);
    dTotAmt=atof(sBuf); 
    sdb_agent_batch_info.tot_amt=dTotAmt;
    sdb_agent_batch_info.tot_cnt=lTotCnt;
    
    sprintf(sNewFilePath, "%s/file/pldsdf/%s.new",getenv("HOME"), sdb_agent_batch_info.ori_file_name);
    sprintf(sCmd,"cp %s %s",sFilePath,sNewFilePath);
    system(sCmd);
    
    if(lTotCnt != (atol(sWj_line)-1))
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("文件笔数不符"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("文件笔数不符 sWj_line=[%s] lTotCnt=[%d]",sWj_line,lTotCnt), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }
    if(lTotCnt <= 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("文件明细笔数为零"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("文件明细笔数为零"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 插入批量代收付导入信息登记簿 */
    iRet = DBInsert("agent_batch_info", SD_AGENT_BATCH_INFO, NUMELE(SD_AGENT_BATCH_INFO), &sdb_agent_batch_info, sErrmsg);
    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        return COMPRET_FAIL;
    }

    if(DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("插入代收付导入信息登记簿agent_batch_info成功"), "INFO")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG ,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}
