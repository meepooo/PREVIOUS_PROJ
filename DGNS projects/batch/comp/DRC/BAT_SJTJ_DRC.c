/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V3.0.00
  操作系统:AIX5.3
  文件名称:SYW_BATCH_B2S_DRC.c
  文件描述:批量业务处理文件映射-数据提回处理转换组件集
  项 目 组:中间业务项目组
  程 序 员:sunpj
  发布日期:2017-06-12
  修    订:
  修改日期:  
 *********************************************************************/
/*
   总体说明:
   函数说明
   组件函数名称                 组件名称                      发布日期  程序员 修改日期 修改人

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"
#include "../../incl/DRC/BATCH_SPLITFILECONTROL.h"

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_BATCH_B2S_PN
  组件名称: 批转单计算进程个数

  组件功能: 
  批转单报文生成
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: sunpj
  发布日期: 2017年06月09日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
 IRESULT SYW_BATCH_B2S_PN(HXMLTREE lXmlhandle)
{
    int  iProNum = 0;
    int  iMaxProNum = 0;
    long lTotalNum = 0;
    long lFileLimitLine = 0;
    
    char cTmp[1024 + 1];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    /**文件总笔数**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/total_num", cTmp);
    lTotalNum = atol(cTmp);
    LOG(LM_DEBUG, Fmtmsg("文件总笔数[%ld]", lTotalNum), "INFO")
    
    /**文件限制行数**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/zjmapinfo/jlsxz", cTmp);
    lFileLimitLine = atol(cTmp);
    LOG(LM_DEBUG, Fmtmsg("文件限制行数[%ld]", lFileLimitLine), "INFO")
    
    /**批转单最大进程数**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/b2s/ps_num", cTmp);
    iMaxProNum = atoi(cTmp);
    LOG(LM_DEBUG, Fmtmsg("批转单最大进程数[%d]", iMaxProNum), "INFO")
    
    /**求批转单进程数**/
    if (0 == lTotalNum % lFileLimitLine)
    {
        iProNum = lTotalNum / lFileLimitLine;
    }
    else
    {
        iProNum = lTotalNum / lFileLimitLine + 1;
    }
    if (iProNum > iMaxProNum)
    {
        iProNum = iMaxProNum;
        lFileLimitLine = lTotalNum / iMaxProNum;
        if (0 != lTotalNum % iMaxProNum)
        {
            lFileLimitLine = lFileLimitLine + 1;
            if (0 == lTotalNum % lFileLimitLine)
            {
                iProNum = lTotalNum / lFileLimitLine;
            }
            else
            {
                iProNum = lTotalNum / lFileLimitLine + 1;
            }
        }
    }
    LOG(LM_DEBUG, Fmtmsg("文件限制行数[%ld]批转单进程数[%d]", lFileLimitLine, iProNum), "INFO")
    
    /**批转单进程数、进程处理笔数**/
    memset(cTmp, 0x00, sizeof(cTmp));
    sprintf(cTmp, "%d", iProNum);
    COMP_SOFTSETXML("/batch/ps_num", cTmp);
    memset(cTmp, 0x00, sizeof(cTmp));
    sprintf(cTmp, "%ld", lFileLimitLine);
    COMP_SOFTSETXML("/batch/ps_per_bum", cTmp);
    
    fpub_SetCompStatus(lXmlhandle, 0);
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_BATCH_B2S_UPDDETAIL
  组件名称: 批转单更新业务明细表

  组件功能: 
  批转单报文生成
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: sunpj
  发布日期: 2017年06月09日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
 IRESULT SYW_BATCH_B2S_UPDDETAIL(HXMLTREE lXmlhandle)
{
    int    iParas;
    int    iRet = 0;
    int    iRepeats = 0;
    int    iHostRespNum = 0;
    int    iColCount = 0;
    int    iIsHaveRespCode = 0;
    int    iIsUpdOnce = 0; 
    char   cTmp[1024 + 1];
    char   cBuf[1024 + 1];
    char   cTableName[128 + 1];
    char   cSqlStr1[1024 + 1];
    char   cSqlStr2[10 * 1024 + 1];
    char   cSqlWhere[2 * 1024 + 1];
    char   cTableColName[128 + 1];
    char   cUpdFlag[32 + 1];
    char   cBatchDate[8 + 1];
    char   cPatBatchNo[16 + 1];
    char   cColCount[16 + 1];
    char   cFldType[32 + 1];
    char   cErrmsg[256+1];
    char   cIsRespCodeConv[16 + 1];
    char   cRespCodeMapId[128 + 1];
    char   cRespCodeSrc[32 + 1];
    char   cRespCodeDes[16 + 1];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    memset(cErrmsg, 0x00, sizeof(cErrmsg));
    
    /**批扣日期**/
    memset(cBatchDate, 0x00, sizeof(cBatchDate));
    COMP_SOFTGETXML("/batch/pkrq", cBatchDate);
    
    /**平台批次号**/
    memset(cPatBatchNo, 0x00, sizeof(cPatBatchNo));
    COMP_SOFTGETXML("/batch/ptpch", cPatBatchNo);
    
    /**业务表名**/
    memset(cTableName, 0x00, sizeof(cTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", cTableName);
    LOG(LM_DEBUG, Fmtmsg("业务表名[%s]", cTableName), "INFO")
    
    /**主机结果位置个数**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/sjtj/zjjgwz", cTmp);
    iHostRespNum = atoi(cTmp);
    LOG(LM_DEBUG, Fmtmsg("账户结果位置数[%d]", iHostRespNum), "INFO")
    
    /**响应码转换标志**/
    memset(cIsRespCodeConv, 0x00, sizeof(cIsRespCodeConv));
    COMP_SOFTGETXML("/batch/zjmapinfo/zhbz", cIsRespCodeConv);
    LOG(LM_DEBUG, Fmtmsg("响应码转换标志[%s]", cIsRespCodeConv), "INFO")
    
    /**响应码转换ID**/
    memset(cRespCodeMapId, 0x00, sizeof(cRespCodeMapId));
    COMP_SOFTGETXML("/batch/zjmapinfo/zhbs", cRespCodeMapId);
    LOG(LM_DEBUG, Fmtmsg("响应码转换ID[%s]", cRespCodeMapId), "INFO")
    
    /**组更新语句**/
    memset(cSqlStr2, 0x00, sizeof(cSqlStr2));
    memset(cSqlWhere, 0x00, sizeof(cSqlWhere));
    sprintf(cSqlStr2, "update %s set ", cTableName);
    sprintf(cSqlWhere, " where pkrq='%s' and ptpch='%s'", cBatchDate, cPatBatchNo);
    while (iRepeats < iHostRespNum)
    {
        memset(cSqlStr1, 0x00, sizeof(cSqlStr1));
        
        /**列名**/
        memset(cTmp, 0x00, sizeof(cTmp));
        memset(cTableColName, 0x00, sizeof(cTableColName));
        sprintf(cTmp, "/batch/sjtj/filemapinfo2|%d/columnid", iRepeats);
        COMP_SOFTGETXML(cTmp, cTableColName);
        trim(cTableColName);
        
        /**更新标志**/
        memset(cTmp, 0x00, sizeof(cTmp));
        memset(cUpdFlag, 0x00, sizeof(cUpdFlag));
        sprintf(cTmp, "/batch/sjtj/filemapinfo2|%d/thgxbz", iRepeats);
        COMP_SOFTGETXML(cTmp, cUpdFlag);
        trim(cUpdFlag);
        
        /**主机结果位置**/
        memset(cTmp, 0x00, sizeof(cTmp));
        memset(cColCount, 0x00, sizeof(cColCount));
        sprintf(cTmp, "/batch/sjtj/filemapinfo2|%d/zjjgwz", iRepeats);
        COMP_SOFTGETXML(cTmp, cColCount);
        iColCount = atoi(cColCount);
        
        /**查询列类型**/
        memset(cSqlStr1, 0x00, sizeof(cSqlStr1));
        memset(cFldType, 0x00, sizeof(cFldType));
        sprintf(cSqlStr1, "select fldtype from app_tablereg where tablename='%s' and fldid='%s'"
                        ,cTableName , cTableColName);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSqlStr1), "INFO")
        iRet = DBSelectToVarChar(cErrmsg, cFldType, cSqlStr1);
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("查询表信息配置表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询表信息配置表失败");
            return COMPRET_FAIL;
        }
        trim(cFldType);
        
        /**获取返回值**/
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/batch/custom/resp/%s", cTableColName);
        COMP_SOFTGETXML(cTmp, cBuf);
        memset(cTmp, 0x00, sizeof(cTmp));
        
        if (0 == strcmp(cUpdFlag, "1"))/**更新内容**/
        {
            if (0 == strcmp(cTableColName, "xym"))
            {
                iIsHaveRespCode = 1;
            }
            
            /**更新字段**/
            if (0 == strcmp(cFldType, "C") || 0 == strcmp(cFldType, "V"))
            {
                if (0 == iIsUpdOnce)
                {
                    sprintf(cTmp, "%s='%s'", cTableColName, cBuf);
                }
                else
                {
                    sprintf(cTmp, ",%s='%s'", cTableColName, cBuf);
                }
            }
            else if (0 == strcmp(cFldType, "I"))
            {
                if (0 == iIsUpdOnce)
                {
                    sprintf(cTmp, "%s=%ld", cTableColName, atol(cBuf));
                }
                else
                {
                    sprintf(cTmp, ",%s=%ld", cTableColName, atol(cBuf));
                }
            }
            else if (0 == strcmp(cFldType, "D"))
            {
                if (0 == iIsUpdOnce)
                {
                    sprintf(cTmp, "%s=%.2f", cTableColName, atof(cBuf));
                }
                else
                {
                    sprintf(cTmp, ",%s=%.2f", cTableColName, atof(cBuf));
                }
            }
            else
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("不支持的数据类型[%s]", cFldType), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "不支持的数据类型");
                return COMPRET_FAIL;
            }
            strcat(cSqlStr2, cTmp);
            if (0 == strcmp(cTableColName, "xym"))
            {
                strcpy(cRespCodeSrc, cBuf);
            }
            iIsUpdOnce++;
        }
        else if (0 == strcmp(cUpdFlag, "2"))/**更新条件**/
        {
           if (0 == strcmp(cFldType, "C") || 0 == strcmp(cFldType, "V"))
            {
                sprintf(cTmp, " and %s='%s'", cTableColName, cBuf);
            }
            else if (0 == strcmp(cFldType, "I"))
            {
                sprintf(cTmp, " and %s=%ld", cTableColName, atol(cBuf));
            }
            else if (0 == strcmp(cFldType, "D"))
            {
                sprintf(cTmp, " and %s=%.2f", cTableColName, atof(cBuf));
            }
            else
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("不支持的数据类型[%s]", cFldType), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "不支持的数据类型");
                return COMPRET_FAIL;
            }
            strcat(cSqlWhere, cTmp);
        }
        else
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("不支持的更新标志[%s]", cUpdFlag), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "不支持的更新标志");
            return COMPRET_FAIL;
        }
        
        iRepeats++;
    }
    
    /**更新成功标志  未配置更新响应码则不更新成功标志**/
    if (1 == iIsHaveRespCode)
    {
        if (0 == strcmp(cIsRespCodeConv, "0"))
        {
            memset(cSqlStr1, 0x00, sizeof(cSqlStr1));
            memset(cRespCodeDes, 0x00, sizeof(cRespCodeDes));
            sprintf(cSqlStr1, "select resp_d from batch_mapresp where mapid='%s' and resp_s='%s'"
                ,cRespCodeMapId , cRespCodeSrc);
            LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSqlStr1), "INFO")
            iRet = DBSelectToVarChar(cErrmsg, cRespCodeDes, cSqlStr1);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("查询响应码映射表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "查询响应码映射表失败");
                return COMPRET_FAIL;
            }
            //LOG(LM_DEBUG, Fmtmsg("响应码[%s]", cRespCodeDes), "INFO")
            trim(cRespCodeDes);
        }
        else
        {
            /**不转换则默认失败**/
            memset(cRespCodeDes, 0x00, sizeof(cRespCodeDes));
            strcpy(cRespCodeDes, "2");
        }
        
        sprintf(cTmp, ",cgbz='%s'", cRespCodeDes);
        strcat(cSqlStr2, cTmp);
    }
    
    /**组更新语句**/
    strcat(cSqlStr2, cSqlWhere);
    LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSqlStr2), "INFO")
    
    iRet = DCIExecuteDirect(cSqlStr2);
    if (0 > iRet)
    {
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, -1);
        LOG(LM_STD, Fmtmsg("更新批量业务明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "更新批量业务明细表失败");
        return COMPRET_FAIL;
    }
    
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle, 0);
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_BATCH_SPLIT_FILE
  组件名称: 按系统编号拆分文件

  组件功能: 
  按系统编号拆分文件
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: sunpj
  发布日期: 2017年06月09日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
 IRESULT SYW_BATCH_SPLIT_FILE(HXMLTREE lXmlhandle)
{
    int  iRet = 0;
    int  iHostNum = 0;
    int  iRepeatNum = 0;
    long lPatBatchNo = 0;
    long lTotalNum = 0;
    long lFileNum = 0;
    
    double dTotalAmt = 0.00;
    
    char cBuf[1024+1];
    char cSql[1024+1];
    char cErrmsg[1024+1];
    char cHostNo[64+1];
    char cHostBatchNo[64+1];
    char cLineBuf[1024+1];
    char cTotalAmt[32+1];
    char cTotalNum[32+1];
    char cBatchDate[32+1];
    char cPatBatchNo[32+1];
    char cProductNo[32+1];
    char cFileHostNo[2+1];
    char cTbaleName[128+1];
    char cPayeeAcctNo[32+1];
    char cOFileName[256+1];
    char cOfileNameAll[512+1];
    
    FILE *fp_read = NULL;
    FILE *fp_write[100+1];
    
    CURSOR cur;
    
    BATCH_SPLITFILECONTROL stSplitFileControl;
    
    LOG(LM_DEBUG, Fmtmsg("系统限制个数[%d]", (sizeof(fp_write)/sizeof(FILE *)) - 1), "INFO")
    while (iRepeatNum < (sizeof(fp_write)/sizeof(FILE *)))
    {
        fp_write[iRepeatNum] = NULL;
        iRepeatNum++;
    }
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    /**批扣日期**/
    memset(cBatchDate, 0x00, sizeof(cBatchDate));
    COMP_SOFTGETXML("/batch/pkrq", cBatchDate);
    
    /**平台批次号**/
    memset(cPatBatchNo, 0x00, sizeof(cPatBatchNo));
    COMP_SOFTGETXML("/batch/ptpch", cPatBatchNo);
    lPatBatchNo = atol(cPatBatchNo);
    
    /**文件序号**/
    memset(cBuf, 0x00, sizeof(cBuf));
    COMP_SOFTGETXML("/batch/sjtj/wjxh", cBuf);
    lFileNum = atol(cBuf);
    LOG(LM_DEBUG, Fmtmsg("文件序号[%ld]", lFileNum), "INFO")
    
    /**业务表名**/
    memset(cTbaleName, 0x00, sizeof(cTbaleName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", cTbaleName);
    
    /**产品代码**/
    memset(cProductNo, 0x00, sizeof(cProductNo));
    COMP_SOFTGETXML("/batch/req/cpdm", cProductNo);
    
    /**原文件全名**/
    memset(cBuf, 0x00, sizeof(cBuf)); 
    memset(cOfileNameAll, 0x00, sizeof(cOfileNameAll));
    sprintf(cBuf, "/batch/sjtj/wjxx|%ld/wjqm", lFileNum);
    COMP_SOFTGETXML(cBuf, cOfileNameAll);
    LOG(LM_DEBUG, Fmtmsg("原文件全名[%s]", cOfileNameAll), "INFO")
    
    /**原文件名**/
    memset(cOFileName, 0x00, sizeof(cOFileName));
    COMP_SOFTGETXML("/batch/file/des/name", cOFileName);
    LOG(LM_DEBUG, Fmtmsg("原文件名[%s]", cOFileName), "INFO")
    
    /** add by llh 20180115
     * 手续费归属标志
     * **/
    char sSxfgsbz[1+1];
    memset(sSxfgsbz, 0x00, sizeof(sSxfgsbz));
    COMP_SOFTGETXML("/batch/req/sxfgsbz", sSxfgsbz);
    LOG(LM_DEBUG, Fmtmsg("手续费归属标志[%s]", sSxfgsbz), "INFO")
    /** add by llh 20180115 **/

    /**统计当前批次涉及的系统个数**/
    memset(cSql, 0x00, sizeof(cSql));
    memset(cErrmsg, 0x00, sizeof(cErrmsg));
    sprintf(cSql, "select count(distinct byzd1) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt !='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
    LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
    iRet = DBSelectToVar(cErrmsg, &iHostNum, cSql);
    if (0 > iRet)
    {
        fpub_SetCompStatus(lXmlhandle, -1);
        LOG(LM_STD, Fmtmsg("查询批量明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
        return COMPRET_FAIL;
    }
    if ((sizeof(fp_write)/sizeof(FILE *)) - 1 < iHostNum)
    {
        fpub_SetCompStatus(lXmlhandle, -1);
        LOG(LM_STD, Fmtmsg("主机系统数超限"), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "主机系统数超限，无法处理");
        return COMPRET_FAIL;
    }
    
    /**拆分文件处理**/
    iRepeatNum = 0;
    memset(cHostBatchNo, 0x00, sizeof(cHostBatchNo));
    COMP_SOFTGETXML("/batch/batch_no", cHostBatchNo);
    LOG(LM_DEBUG, Fmtmsg("cHostBatchNo[%s]", cHostBatchNo), "INFO")
    LOG(LM_DEBUG, Fmtmsg("iHostNum[%d]", iHostNum), "INFO")
    if (1 < iHostNum)
    {
        /**获取当前批次的系统编号**/
        memset(cSql, 0x00, sizeof(cSql));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        sprintf(cSql, "select distinct byzd1 from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt !='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        if (-1 == (cur = DCIDeclareCursor(cSql, DCI_STMT_LOCATOR)))
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD,Fmtmsg("查询批量明细表失败,sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
            return COMPRET_FAIL;
        }
        if (-1 == DCIExecute(cur))
        {
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD,Fmtmsg("打开游标失败,sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
            return COMPRET_FAIL;
        }
        
        while (iRepeatNum < iHostNum)
        {
            iRepeatNum++;
            memset(cHostNo, 0x00, sizeof(cHostNo));
            memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
            iRet = DCIFetch(cur);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("查询批量明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
                return COMPRET_FAIL;
            }
            else if (0 == iRet)
            {
                break;
            }
            strncpy(cHostNo, DCIFieldAsString(cur, 0), sizeof(cHostNo));
            trim(cHostNo);
            LOG(LM_DEBUG, Fmtmsg("hostno[%s]", cHostNo), "INFO")
        
            memset(cSql, 0x00, sizeof(cSql));
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            sprintf(cSql, "select * from batch_splitfilecontrol where host_batch_no='%s' and host_no='%s'",
                      cHostBatchNo, cHostNo);
            LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
            iRet = prv_SelMulToStruct(&cSql, SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL), &stSplitFileControl);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("查询批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "查询批量平台文件分割控制表失败");
                return COMPRET_FAIL;
            }
            else if (0 == iRet)
            {
                /**登记拆分控制表**/
                memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
                strncpy(stSplitFileControl.host_batch_no, cHostBatchNo, sizeof(stSplitFileControl.host_batch_no));
                strncpy(stSplitFileControl.host_no, cHostNo, sizeof(stSplitFileControl.host_no));
                strncpy(stSplitFileControl.o_file_req, cOfileNameAll, sizeof(stSplitFileControl.o_file_req));
                sprintf(stSplitFileControl.file_req, "%s/file/batch/%s/%s/%s_%s", getenv("HOME"), cProductNo
                        , cBatchDate, cHostNo, cOFileName);
                strcpy(stSplitFileControl.state, "9");
                memset(cErrmsg, 0x00, sizeof(cErrmsg));
                iRet = DBInsert("batch_splitfilecontrol", SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL)
                                , &stSplitFileControl, cErrmsg);
                if (0 > iRet)
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("登记批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "登记批量平台文件分割控制表失败");
                    return COMPRET_FAIL;
                }
                //LOG(LM_DEBUG, Fmtmsg("insert batch_splitfilecontrol success"), "INFO")
                
                /**默认拆文件成功 失败报错**/
                memset(cBuf, 0x00, sizeof(cBuf));
                sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/state", iRepeatNum);
                COMP_SOFTSETXML(cBuf, "0");
            }
            else
            {
                LOG(LM_DEBUG, Fmtmsg("state[%s]", stSplitFileControl.state), "INFO")
                memset(cBuf, 0x00, sizeof(cBuf));
                sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/state", iRepeatNum);
                COMP_SOFTSETXML(cBuf, stSplitFileControl.state);
                if (0 == strncmp(stSplitFileControl.state, "9", 1))
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("文件拆分处理中"), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "文件拆分处理中");
                    return COMPRET_FAIL;
                }
                else if (0 == strncmp(stSplitFileControl.state, "1", 1))
                {
                    memset(cSql, 0x00, sizeof(cSql));
                    memset(cErrmsg, 0x00, sizeof(cErrmsg));
                    sprintf(cSql, "update batch_splitfilecontrol set state='9' where host_batch_no='%s' and host_no"
                            , cHostBatchNo, cHostNo);
                    LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
                    iRet = DCIExecuteDirect(cSql);
                    if (0 > iRet)
                    {
                        fpub_SetCompStatus(lXmlhandle, -1);
                        LOG(LM_STD, Fmtmsg("更新批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                        fpub_SetMsg(lXmlhandle, 100001, "更新批量平台文件分割控制表失败");
                        return COMPRET_FAIL;
                    }
                }
                else if (0 != strncmp(stSplitFileControl.state, "0", 1))
                {
                    continue;
                }
            }
            memset(cSql, 0x00, sizeof(cSql));
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            memset(cTotalNum, 0x00, sizeof(cTotalNum));
            memset(cTotalAmt, 0x00, sizeof(cTotalAmt));
            /**** 如果手续费归属标志为2-个人时,需要将手续费计算到交易金额里  ****/
            if(strcmp(sSxfgsbz,"2") == 0)
            {
                sprintf(cSql, "select count(*),sum(jyje)+sum(sxfje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and trim(byzd1)='%s' and shzt!='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum, cHostNo);
            }else
            {
                sprintf(cSql, "select count(*),sum(jyje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and trim(byzd1)='%s' and shzt!='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum, cHostNo);
            }
            LOG(LM_DEBUG,Fmtmsg("cSql [%s]",cSql),"DEBUG")
            iRet = DBSelectToMultiVarChar(cErrmsg, cSql, &cTotalNum, &cTotalAmt);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("查询批量明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
                return COMPRET_FAIL;
            }
            
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/hostno", iRepeatNum);
            COMP_SOFTSETXML(cBuf, stSplitFileControl.host_no);
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/zbs", iRepeatNum);
            COMP_SOFTSETXML(cBuf, cTotalNum);
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/zje", iRepeatNum);
            COMP_SOFTSETXML(cBuf, cTotalAmt);
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/file_req", iRepeatNum);
            COMP_SOFTSETXML(cBuf, stSplitFileControl.file_req);
        }
        
        COMP_SOFTSETXML("/batch/sjtj/splitfile/hostnum", itoa(iHostNum));
        
        iRet =DCICommit();
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("登记批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "登记批量平台文件分割控制表失败");
            return COMPRET_FAIL;
        }
        
        if (0 == strncmp(stSplitFileControl.state, "9", 1) || 0 == strncmp(stSplitFileControl.state, "1", 1))
        {
            /**读源文件**/
            fp_read = fopen(cOfileNameAll, "r");
            if (NULL == fp_read)
            {
                memset(cSql, 0x00, sizeof(cSql));
                memset(cErrmsg, 0x00, sizeof(cErrmsg));
                sprintf(cSql, "update batch_splitfilecontrol set state='1' where host_batch_no='%s'", cHostBatchNo);
                LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
                iRet = DCIExecuteDirect(cSql);
                if (0 > iRet)
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("更新批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "更新批量平台文件分割控制表失败");
                    return COMPRET_FAIL;
                }
                
                iRet =DCICommit();
                if (0 > iRet)
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("更新批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "更新批量平台文件分割控制表失败");
                    return COMPRET_FAIL;
                }
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("打开文件失败[%s]", cOfileNameAll), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "打开文件失败");
                return COMPRET_FAIL;
            }
            
            /**拆文件**/
            memset(cLineBuf, 0x00, sizeof(cLineBuf));
            while (NULL != fgets(cLineBuf, sizeof(cLineBuf), fp_read))
            {
                memset(cBuf, 0x00, sizeof(cBuf));
                strncpy(cBuf, cLineBuf + 634, 40);
                trim(cBuf);
                strncpy(cFileHostNo, cBuf, sizeof(cFileHostNo));
                LOG(LM_DEBUG, Fmtmsg("cFileHostNo[%s]", cBuf), "INFO")
                iRepeatNum = 0;
                while (iRepeatNum < iHostNum)
                {
                    iRepeatNum++;
                    memset(cBuf, 0x00, sizeof(cBuf));
                    memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
                    sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/hostno", iRepeatNum);
                    COMP_SOFTGETXML(cBuf, stSplitFileControl.host_no);
                    if (0 == strcmp(cFileHostNo, stSplitFileControl.host_no))
                    {
                        memset(cBuf, 0x00, sizeof(cBuf));
                        sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/file_req", iRepeatNum);
                        COMP_SOFTGETXML(cBuf, stSplitFileControl.file_req);
                        if (NULL == fp_write[iRepeatNum-1])
                        {
                            fp_write[iRepeatNum-1] = fopen(stSplitFileControl.file_req, "w+");
                            LOG(LM_DEBUG, Fmtmsg("打开文件"), "INFO")
                            if (NULL == fp_write[iRepeatNum-1])
                            {
                                fclose(fp_read);
                                fp_read = NULL;
                                memset(cSql, 0x00, sizeof(cSql));
                                memset(cErrmsg, 0x00, sizeof(cErrmsg));
                                sprintf(cSql, "update batch_splitfilecontrol set state='1' where host_batch_no='%s'", cHostBatchNo);
                                LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
                                iRet = DCIExecuteDirect(cSql);
                                if (0 > iRet)
                                {
                                    fpub_SetCompStatus(lXmlhandle, -1);
                                    LOG(LM_STD, Fmtmsg("更新批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                                    fpub_SetMsg(lXmlhandle, 100001, "更新批量平台文件分割控制表失败");
                                    return COMPRET_FAIL;
                                }
                                
                                iRet =DCICommit();
                                if (0 > iRet)
                                {
                                    fpub_SetCompStatus(lXmlhandle, -1);
                                    LOG(LM_STD, Fmtmsg("更新批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                                    fpub_SetMsg(lXmlhandle, 100001, "更新批量平台文件分割控制表失败");
                                    return COMPRET_FAIL;
                                }
                                fpub_SetCompStatus(lXmlhandle, -1);
                                LOG(LM_STD, Fmtmsg("打开文件失败[%s]", stSplitFileControl.file_req), "ERROR")
                                fpub_SetMsg(lXmlhandle, 100001, "打开文件失败");
                                return COMPRET_FAIL;
                            }
                            memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
                            strncpy(cPayeeAcctNo, cLineBuf + 301, 32);
                            /* add 20171113 zengy 判断若收款账号为空则取付款账号作为选取核心依据 beg */
                            trim(cPayeeAcctNo);
                            if(strlen(cPayeeAcctNo) == 0)
                            {
                                memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
                                strncpy(cPayeeAcctNo, cLineBuf + 133, 32);
                                trim(cPayeeAcctNo);
                            }
                            /* add 20171113 zengy 判断若收款账号为空则取付款账号作为选取核心依据 end */
                            memset(cBuf, 0x00, sizeof(cBuf));
                            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/payeeacctno", iRepeatNum);
                            COMP_SOFTSETXML(cBuf, cPayeeAcctNo);
                        }
                        break;
                    }
                }
                fprintf(fp_write[iRepeatNum-1], "%s", cLineBuf);
                memset(cLineBuf, 0x00, sizeof(cLineBuf));
            }
            fclose(fp_read);
            fp_read = NULL;
            iRepeatNum = 0;
            while (iRepeatNum < iHostNum)
            {
                LOG(LM_DEBUG, Fmtmsg("关闭文件"), "INFO")
                fclose(fp_write[iRepeatNum]);
                fp_write[iRepeatNum] = NULL;
                iRepeatNum++;
            }
            
            memset(cSql, 0x00, sizeof(cSql));
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            sprintf(cSql, "update batch_splitfilecontrol set state='0' where host_batch_no='%s'", cHostBatchNo);
            LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
            iRet = DCIExecuteDirect(cSql);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("更新批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "更新批量平台文件分割控制表失败");
                return COMPRET_FAIL;
            }
            
            iRet =DCICommit();
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("更新批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "更新批量平台文件分割控制表失败");
                return COMPRET_FAIL;
            }
        }
    }
    else
    {
        /**获取当前批次的系统编号**/
        memset(cSql, 0x00, sizeof(cSql));
        memset(cHostNo, 0x00, sizeof(cHostNo));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
        sprintf(cSql, "select distinct byzd1 from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        iRet = DBSelectToVarChar(cErrmsg, cHostNo, cSql);
        if (0 >= iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("查询批量明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("hostno[%s]", cHostNo), "INFO")
        trim(cHostNo);
        LOG(LM_DEBUG, Fmtmsg("hostno[%s]", cHostNo), "INFO")
        
        memset(cSql, 0x00, sizeof(cSql));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        sprintf(cSql, "select * from batch_splitfilecontrol where host_batch_no='%s' and host_no='%s'",
                  cHostBatchNo, cHostNo);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        iRet = prv_SelMulToStruct(&cSql, SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL), &stSplitFileControl);
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("查询批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询批量平台文件分割控制表失败");
            return COMPRET_FAIL;
        }
        else if (0 == iRet)
        {
            /**登记拆分控制表**/
            memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
            strncpy(stSplitFileControl.host_batch_no, cHostBatchNo, sizeof(stSplitFileControl.host_batch_no));
            strncpy(stSplitFileControl.host_no, cHostNo, sizeof(stSplitFileControl.host_no));
            strncpy(stSplitFileControl.o_file_req, cOfileNameAll, sizeof(stSplitFileControl.o_file_req));
            strncpy(stSplitFileControl.file_req, cOfileNameAll, sizeof(stSplitFileControl.file_req));
            strcpy(stSplitFileControl.state, "0");
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            iRet = DBInsert("batch_splitfilecontrol", SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL)
                            , &stSplitFileControl, cErrmsg);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("登记批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "登记批量平台文件分割控制表失败");
                return COMPRET_FAIL;
            }
            
            iRet =DCICommit();
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("登记批量平台文件分割控制表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "登记批量平台文件分割控制表失败");
                return COMPRET_FAIL;
            }
            
            COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/state", "0");
        }
        else
        {
            LOG(LM_DEBUG, Fmtmsg("state[%s]", stSplitFileControl.state), "INFO")
            COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/state", stSplitFileControl.state);
            if (0 == strncmp(stSplitFileControl.state, "9", 1) || 0 == strncmp(stSplitFileControl.state, "1", 1))
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("系统错误"), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "系统错误");
                return COMPRET_FAIL;
            }
        }
        
        /**统计金额、笔数**/
        memset(cSql, 0x00, sizeof(cSql));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        memset(cTotalNum, 0x00, sizeof(cTotalNum));
        memset(cTotalAmt, 0x00, sizeof(cTotalAmt));
        /**** 如果手续费归属标志为2-个人时,需要将手续费计算到交易金额里  ****/
        if(strcmp(sSxfgsbz,"2") == 0)
        {
            sprintf(cSql, "select count(*),sum(jyje)+sum(sxfje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt!='1' and clzt='9'", cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        }else
        {
            sprintf(cSql, "select count(*),sum(jyje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt!='1' and clzt='9'", cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        }
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        iRet = DBSelectToMultiVarChar(cErrmsg, cSql, &cTotalNum, &cTotalAmt);
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("查询批量明细表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "查询批量明细表失败");
            return COMPRET_FAIL;
        }
        
        /**取账号**/
        memset(cLineBuf, 0x00, sizeof(cLineBuf));
        memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
        fp_read = fopen(cOfileNameAll, "r");
        if (NULL == fopen)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("打开文件失败[%s]", cOfileNameAll), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "打开文件失败");
            return COMPRET_FAIL;
        }
        fgets(cLineBuf, sizeof(cLineBuf), fp_read);
        strncpy(cPayeeAcctNo, cLineBuf + 301, 32);
        /* add 20171113 zengy 判断若收款账号为空则取付款账号作为选取核心依据 beg */
        trim(cPayeeAcctNo);
        if(strlen(cPayeeAcctNo) == 0)
        {
            memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
            strncpy(cPayeeAcctNo, cLineBuf + 133, 32);
            trim(cPayeeAcctNo);
        }
        /* add 20171113 zengy 判断若收款账号为空则取付款账号作为选取核心依据 end */
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/payeeacctno", cPayeeAcctNo);
        
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/hostno", cHostNo);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/zbs", cTotalNum);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/zje", cTotalAmt);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/file_req", stSplitFileControl.file_req);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/hostnum", "1");
        fclose(fp_read);
        fp_read = NULL;
    }
    
    fpub_SetCompStatus(lXmlhandle, 0);
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}

/********************************************************
* 名称: prv_SelMulToStruct
* 功能: DCI查询多个字段至结构体
* 参数说明: 1:
*     2:
*     3:
*			4:
* 返回: -1:失败
*   >=0:打报后数据长度(成功)
********************************************************/
int prv_SelMulToStruct( const char* sSql, FLD_DESC desc_arr[], int desc_num, void* pdes)
{
    CURSOR cur;
    char szErrMsg[512];
    
    if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
    {
        LOG(LM_STD, Fmtmsg("传入参数空"), "WARNING");
        return -1;
    }
    cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
    if (cur == INVALID_CURSOR)
    {
        LOG(LM_STD, Fmtmsg("游标定义失败[%s]-[%s]",  DCILastError(), sSql), "ERROR");
        return -1;
    }
    if(DCIExecute(cur) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败[%s]", DCILastError() ), "ERROR");
        DCIFreeCursor(cur);
        return -1;
    }
    int rs = 0;
    if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
    {
        LOG(LM_STD, Fmtmsg("游标获取记录错误[%s]",  szErrMsg ), "ERROR");
        return -1;
    }
 		
 		DCIFreeCursor(cur);
    return rs;
}
