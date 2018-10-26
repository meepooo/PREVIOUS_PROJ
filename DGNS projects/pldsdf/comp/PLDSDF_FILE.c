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
/*#include "DRC_esb_md5.h"*/
#include "../eh/agent_batch_info.h"
#include "../eh/batch_dsdf_detail.h"
#include "../eh/pldsdf_custom_detail.h"

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
  程 序 员: zengy
  发布日期: 2017年10月24日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SPLDSDF_FILE_PRE_DEAL(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dTotAmt = 0.00;
    char sSfbz[1+1];
    char sDwbh[16+1];
    /*char sBuf[512];*/
    char sBuf[1024];
    char sFileName[256+1];
    char sFilePath[256+1];
    char sNewFilePath[256+1];
    /*char sLine[1024];*/
    char sLine[3072];
    /*char sNewLine[1024];*/
    char sNewLine[4072];
    char sCmd[512];
    char sErrmsg[512];
    char sMd5[64];
    char sMd5_1[64];
    char sMd5_2[64];
    FILE *fp = NULL;
    FILE *newfp = NULL;
    SDB_AGENT_BATCH_INFO sdb_agent_batch_info;
    
    char sUpdateflag[1+1];
    char sCondition[120+1];

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
    COMP_SOFTGETXML("/sys/sysdate", sBuf);
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
/*add by llh 20180319 begin*/    
    /* 文件类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/wjlx", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.wjlx, sBuf, sizeof(sdb_agent_batch_info.wjlx));
    LOG(LM_DEBUG, Fmtmsg("文件类型[%s]", sdb_agent_batch_info.wjlx), "INFO")
    
    /* 自动入账标志 0-否 1-是*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/zdrzbz", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.zdrzbz, sBuf, sizeof(sdb_agent_batch_info.zdrzbz));
    LOG(LM_DEBUG, Fmtmsg("自动入账标志[%s]", sdb_agent_batch_info.zdrzbz), "INFO")
    
    /* 执行时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/zxsj", sBuf);
    trim(sBuf);
    pstrcopy(sdb_agent_batch_info.zxsj, sBuf, sizeof(sdb_agent_batch_info.zxsj));
    LOG(LM_DEBUG, Fmtmsg("执行时间[%s]", sdb_agent_batch_info.zxsj), "INFO")
/*add by llh 20180319 end*/    

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
    
/*modify by llh 20180319 begin*/
#if 0
    /* 状态 8-待入账申请 */
    pstrcopy(sdb_agent_batch_info.stat, "8", sizeof(sdb_agent_batch_info.stat));
#endif
    if(strcmp(sdb_agent_batch_info.zdrzbz,"1") == 0)
    {
        /* 状态 8-待入账申请 */
        pstrcopy(sdb_agent_batch_info.stat, "8", sizeof(sdb_agent_batch_info.stat));
    }else if(strcmp(sdb_agent_batch_info.zdrzbz,"0") == 0)
    {
        /* 状态赋值为空 */
        pstrcopy(sdb_agent_batch_info.stat, "", sizeof(sdb_agent_batch_info.stat));
    }
	/*文件类型为开户时的处理*/
	if(strcmp(sdb_agent_batch_info.wjlx,"0") == 0)
	{
		pstrcopy(sdb_agent_batch_info.fkfz,sdb_agent_batch_info.brief_code,sizeof(sdb_agent_batch_info.fkfz));
		pstrcopy(sdb_agent_batch_info.lqzjsj,sdb_agent_batch_info.zxsj,sizeof(sdb_agent_batch_info.lqzjsj));
		memset(sdb_agent_batch_info.brief_code,0x00,sizeof(sdb_agent_batch_info.brief_code));
		memset(sdb_agent_batch_info.zxsj,0x00,sizeof(sdb_agent_batch_info.zxsj));

	}
/*modify by llh 20180319 end*/
    
    /* 总笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/total_cnt", sBuf);
    sdb_agent_batch_info.tot_cnt = atol(sBuf);
    LOG(LM_DEBUG, Fmtmsg("总笔数[%ld]", sdb_agent_batch_info.tot_cnt), "INFO")

    /* 总金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/total_amt", sBuf);
    sdb_agent_batch_info.tot_amt = atof(sBuf);
    LOG(LM_DEBUG, Fmtmsg("总金额[%.2lf]", sdb_agent_batch_info.tot_amt), "INFO")

    /* 文件可能是.zip压缩文件，需要进行解压 */
    if(strncmp(sFileName+strlen(sFileName)-4, ".zip", 4) == 0)
    {
        memset(sCmd, 0x00, sizeof(sCmd));
        sprintf(sCmd, "cd %s/file/batch/dsf && unzip -o %s 1>>/home/gapsv4/tmp/gapssh%s.std 2>>/home/gapsv4/tmp/gapssh%s.err",
            getenv("HOME"), sFileName, sdb_agent_batch_info.up_date, sdb_agent_batch_info.up_date);
        if(system(sCmd) != 0)
        {
            fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("解压文件[%s]失败", sFileName));
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD, Fmtmsg("解压文件[%s]失败", sFileName), fpub_GetCompname(lXmlhandle))
            return COMPRET_FAIL;
        }

        /* 来盘文件名 */
        strncpy(sdb_agent_batch_info.ori_file_name, sFileName, strlen(sFileName)-4);
    }
    else
    {
        /* 来盘文件名 */
        strcpy(sdb_agent_batch_info.ori_file_name, sFileName);
    }
    memset(sFilePath, 0x00, sizeof(sFilePath));
    sprintf(sFilePath, "%s/file/batch/dsf/%s", getenv("HOME"), sdb_agent_batch_info.ori_file_name);

    LOG(LM_DEBUG, Fmtmsg("原批量请求文件[%s]", sFilePath), "INFO")
    /*LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO")*/
    /* 校验md5码，请求报文里的是txt格式文件的md5码，需解压后比较 */
    memset(sMd5, 0x00, sizeof(sMd5));
    DRC_getMd5File(sFilePath, sMd5);
	int iCompStat=1;
/*	if(fpub_ExecComp(lXmlhandle,"DRC_GETMD5",&iCompStat,3,"1",sFilePath,"/agent/tmp/md5") != 0)
	{
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("MD5码校验失败"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("MD5码校验失败[%s]", sMd5), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
	}
    COMP_SOFTGETXML("/agent/tmp/md5", sMd5);*/
    trim(sMd5);
    LOG(LM_DEBUG, Fmtmsg("sFilePath[%s]sMd5[%s]", sFilePath,sMd5), "INFO")
    memset(sMd5_1, 0x00, sizeof(sMd5_1));
    memset(sMd5_2, 0x00, sizeof(sMd5_2));
    strcpy(sMd5_1, strtoupper(sdb_agent_batch_info.md5_code));
    strcpy(sMd5_2, strtoupper(sMd5));
    trim(sMd5_1);
    trim(sMd5_2);
    LOG(LM_DEBUG, Fmtmsg("sMd5_1[%s]sMd5_2[%s]", sMd5_1,sMd5_2), "INFO")
    if(strcmp(sMd5_1, sMd5_2) != 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("MD5码校验失败"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("MD5码校验失败[%s]", sMd5), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    /* 新文件 */
    memset(sNewFilePath, 0x00, sizeof(sNewFilePath));
    sprintf(sNewFilePath, "%s/file/pldsdf/%s.new", getenv("HOME"),sdb_agent_batch_info.ori_file_name);
    /*sprintf(sNewFilePath, "%s/file/pldsdf/%s/%s.new", getenv("HOME"), sdb_agent_batch_info.up_date,sdb_agent_batch_info.ori_file_name);*/

    /* 打开原导入文件，若为旧格式，需转换为新文件格式 */
    fp = fopen(sFilePath, "r");
    if(fp == NULL)
    {
        fpub_SetMsg(lXmlhandle, 24103, "打开文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("打开文件失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    newfp = fopen(sNewFilePath, "w");
    if(newfp == NULL)
    {
        fclose(fp);
        fpub_SetMsg(lXmlhandle, 24103, "打开文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("打开文件失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sLine, 0x00, sizeof(sLine));
    while(fgets(sLine, sizeof(sLine)-1, fp) != NULL)
    {
        /* 判断是否空行，是则直接跳过 */
        memset(sNewLine, 0x00, sizeof(sNewLine));
        sprintf(sNewLine, "%s", sLine);
        trim(sNewLine);
        if(strlen(sNewLine) == 0)
        {
            continue;
        }

        /* 去除最后一个换行符 */
        sLine[strlen(sLine)-1]=0;
        if(sLine[strlen(sLine)-1] == 0x0d) /* 去除末尾的(^M) */
        {
            sLine[strlen(sLine)-1]=0;
        }

        lTotCnt++;
        LOG(LM_DEBUG, Fmtmsg("sLine[%s]", sLine), "INFO")

        /* 收付标志 1-收 2-付 */
        if(strcmp(sSfbz, "1") == 0) /* 代收 */
        {
            /* 首行, 判断单位编号是否一致, 代收格式例:单位编号=210344;version=1.2 */
            if(lTotCnt == 1)
            {
                memset(sDwbh, 0x00, sizeof(sDwbh));
                memset(sBuf, 0x00, sizeof(sBuf));
                GetListbyDiv(sLine, 1, sBuf, ';', '\\');
                strncpy(sDwbh, sBuf+9, 16);
                trim(sDwbh);

                if(strcmp(sDwbh, sdb_agent_batch_info.dwbh) != 0)
                {
                    fclose(fp);
                    fclose(newfp);
                    fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("单位编号与文件中[%s]不一致", sDwbh));
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD, Fmtmsg("单位编号与文件中[%s]不一致", sDwbh), fpub_GetCompname(lXmlhandle))
                    return COMPRET_FAIL;
                }

                /* 将首行写入新文件 */
                fprintf(newfp, "单位编号：%s;\n", sDwbh);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            /* 明细新格式如下:
               序号|合同号|款项日期|客户账号|户名|总金额|业务金额|费用1|费用2|备注|
               附言|费用3|费用4|费用5|
            */

            /* 6.金额 */
            memset(sBuf, 0x00, sizeof(sBuf));
            GetListbyDiv(sLine, 6, sBuf, '|', '\\');
            dTotAmt += atof(sBuf);

            /* 10.备注, 旧文件格式可能以10结束, 新文件格式以14结束, 旧格式按新格式补足14列 */
            memset(sBuf, 0x00, sizeof(sBuf));
            if(GetListbyDiv(sLine, 10, sBuf, '|', '\\') == -1)
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            memset(sNewLine, 0x00, sizeof(sNewLine));
            if(GetListbyDiv(sLine, 11, sBuf, '|', '\\') == -1) /* 11.附言 */
            {
                sprintf(sNewLine, "%s%-62s|%-13s|%-13|%-13s|",
                    sLine, " ", " ", " ", " ");

                /* 将明细行写入新文件 */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            if(GetListbyDiv(sLine, 14, sBuf, '|', '\\') == -1) /* 14.费用5 */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            if(GetListbyDiv(sLine, 15, sBuf, '|', '\\') > 0) /* 超出第15列 */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            /* 将明细行写入新文件 */
            fprintf(newfp, "%s\n", sLine);
            memset(sLine, 0x00, sizeof(sLine));
        }
        else /* 代付 */
        {
            /* 首行, 判断单位编号是否一致, 代付格式例:单位编号：210344;version=1.2 */
            if(lTotCnt == 1)
            {
                memset(sDwbh, 0x00, sizeof(sDwbh));
                memset(sBuf, 0x00, sizeof(sBuf));
                GetListbyDiv(sLine, 1, sBuf, ';', '\\');
                strncpy(sDwbh, sBuf+10, 16);
                trim(sDwbh);

                if(strcmp(sDwbh, sdb_agent_batch_info.dwbh) != 0)
                {
                    fclose(fp);
                    fclose(newfp);
                    fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("单位编号与文件中[%s]不一致", sDwbh));
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD, Fmtmsg("单位编号与文件中[%s]不一致", sDwbh), fpub_GetCompname(lXmlhandle))
                    return COMPRET_FAIL;
                }

                /* 将首行写入新文件 */
                fprintf(newfp, "单位编号：%s;\n", sDwbh);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            /* 明细新格式如下:
               批号|序号|交易柜员|处理标志|类型|账号|金额|户名|证件类型|证件号码|证件有效期|性别|出生日期|地址|发证机关|邮政编码|电话号码|状态|
               对方行号|对方行行名|附言|备注|职业|工作单位|税收居民身份|转账类型|
            */

            /* 7.金额 */
            memset(sBuf, 0x00, sizeof(sBuf));
            GetListbyDiv(sLine, 7, sBuf, '|', '\\');
            dTotAmt += atof(sBuf);

            /* 18.状态, 旧文件格式可能以18或22结束, 新文件格式以25结束, 旧格式按新格式补足25列 */
            memset(sBuf, 0x00, sizeof(sBuf));
            if(GetListbyDiv(sLine, 18, sBuf, '|', '\\') == -1)
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            memset(sNewLine, 0x00, sizeof(sNewLine));
            if(GetListbyDiv(sLine, 19, sBuf, '|', '\\') == -1) /* 19.对方行号 */
            {
                /*sprintf(sNewLine, "%s%-14s|%-100s|%-62s|%-62s|%-10s|%-42s|%-1s|",
                    sLine, " ", " ", " ", " ", " ", " ", " ");*/
                sprintf(sNewLine, "%s%-14s|%-100s|%-62s|%-62s|%-10s|%-42s|%-1s|%s|%s|",
                    sLine, " ", " ", " ", " ", " ", " ", " "," "," ");

                /* 将明细行写入新文件 */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            if(GetListbyDiv(sLine, 22, sBuf, '|', '\\') == -1) /* 22.备注 */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            if(GetListbyDiv(sLine, 23, sBuf, '|', '\\') == -1) /* 23.职业 */
            {
                /*sprintf(sNewLine, "%s%-10s|%-42s|%-1s|",
                    sLine, " ", " ", " ");*/
                sprintf(sNewLine, "%s%-10s|%-42s|%-1s|%s|%s|",
                    sLine, " ", " ", " "," "," ");

                /* 将明细行写入新文件 */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            if(GetListbyDiv(sLine, 25, sBuf, '|', '\\') == -1) /* 25.税收居民身份 */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }
            
            if(GetListbyDiv(sLine, 26, sBuf, '|', '\\') == -1) /* 26.扩展1 */
            {
                sprintf(sNewLine, "%s%s|%s|",
                    sLine, " ", " ");

                /* 将明细行写入新文件 */
                fprintf(newfp, "%s\n", sNewLine);

                memset(sLine, 0x00, sizeof(sLine));
                continue;
            }

            /*if(GetListbyDiv(sLine, 26, sBuf, '|', '\\') >= 0)  超出第26列 */
            if(GetListbyDiv(sLine, 28, sBuf, '|', '\\') >= 0) /* 超出第28列 */
            {
                fclose(fp);
                fclose(newfp);
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt));
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOG(LM_STD, Fmtmsg("第[%ld]行文件明细格式不符", lTotCnt), fpub_GetCompname(lXmlhandle))
                return COMPRET_FAIL;
            }

            /* 将明细行写入新文件 */
            fprintf(newfp, "%s\n", sLine);
            memset(sLine, 0x00, sizeof(sLine));
        }
    }
    fclose(fp);
    fclose(newfp);

    lTotCnt = lTotCnt-1;
    if(lTotCnt <= 0)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("文件明细笔数为零"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("文件明细笔数为零"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    /* 校验总笔数和总金额 */
    if(sdb_agent_batch_info.tot_cnt != lTotCnt)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("与文件明细总笔数[%ld]不符", lTotCnt));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("与文件明细总笔数[%ld]不符", lTotCnt), fpub_GetCompname(lXmlhandle))
		LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");
        return COMPRET_FAIL;
    }
	LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");

    if((sdb_agent_batch_info.tot_amt - dTotAmt) > 0.00001 ||
       (sdb_agent_batch_info.tot_amt - dTotAmt) < -0.00001)
    {
        fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("与文件明细总金额[%.2lf]不符", dTotAmt));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("与文件明细总金额[%.2lf]不符", dTotAmt), fpub_GetCompname(lXmlhandle))
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
#if 0
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
#endif
/*add by llh 20180319 begin*/
    /* 数据库更新标志 0-插入 1-更新*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sUpdateflag, 0x00, sizeof(sUpdateflag));
    COMP_SOFTGETXML("/agent/req/updateflag", sBuf);
    trim(sBuf);
    pstrcopy(sUpdateflag, sBuf, sizeof(sUpdateflag));
    LOG(LM_DEBUG, Fmtmsg("数据库更新标志[%s]", sUpdateflag), "INFO");
	sprintf(sdb_agent_batch_info.extfld1,"%s%s",sdb_agent_batch_info.up_date,sdb_agent_batch_info.up_time);
    
    if(strcmp(sUpdateflag,"0") == 0)
    {
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
    }else if(strcmp(sUpdateflag,"1") == 0)
    {
        memset(sCondition, 0x00, sizeof(sCondition));
        sprintf(sCondition,"batch_no='%s'",sdb_agent_batch_info.batch_no);
        /* 更新批量代收付导入信息登记簿 */
        iRet = DBUpdate("agent_batch_info", SD_AGENT_BATCH_INFO, NUMELE(SD_AGENT_BATCH_INFO), &sdb_agent_batch_info, sCondition, sErrmsg);
        if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIRollback();
            return COMPRET_FAIL;
        }
    }
/*add by llh 20180319 end*/

    if(DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("插入代收付导入信息登记簿agent_batch_info成功"), "INFO")
	LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	LOG(LM_DEBUG, Fmtmsg("aaaaaa"), "INFO");
    LOG(LM_DEBUG ,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SPLDSDF_FILE_GEN
  组件名称: 批量代收代付回盘文件生成处理

  组件功能: 
            生成结果回盘文件
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: zengy
  发布日期: 2017年10月24日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SPLDSDF_FILE_GEN(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    char sBatchNo[32+1];
    char sSfbz[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sStat[1+1];
    char sDownFlag[1+1];
    char sBuf[512];
    char sFileName[256+1];
    char sFilePath[512+1];
    char sLine[1024];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    FILE *fp = NULL;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcur;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* 组件参数检查 */
    COMP_PARACOUNTCHKMIN(2)

    /* 商户批次号 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sBatchNo, 0x00, sizeof(sBatchNo));
    COMP_GETPARSEPARAS(1, sBuf, "商户批次号")
    trim(sBuf);
    pstrcopy(sBatchNo, sBuf, sizeof(sBatchNo));
    LOG(LM_DEBUG, Fmtmsg("商户批次号[%s]", sBatchNo), "INFO")

    /* 收付标志 1-收2-付 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    COMP_GETPARSEPARAS(2, sBuf, "收付标志")
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("收付标志[%s]", sSfbz), "INFO")

    /* 业务表名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("业务表名[%s]", sTableName), "INFO")

    /* 批扣日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/resp/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("批扣日期[%s]", sPkrq), "INFO")

    /* 平台批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/resp/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("平台批次号[%s]", sPtpch), "INFO")

    /* 单位编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/resp/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("单位编号[%s]", sDwbh), "INFO")

    /* 文件下载标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDownFlag, 0x00, sizeof(sDownFlag));
    COMP_SOFTGETXML("/agent/req/down_flag", sBuf);
    trim(sBuf);
    pstrcopy(sDownFlag, sBuf, sizeof(sDownFlag));
    LOG(LM_DEBUG, Fmtmsg("文件下载标志[%s]", sDownFlag), "INFO")

    /* 回盘结果文件名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    memset(sFilePath, 0x00, sizeof(sFilePath));
    COMP_SOFTGETXML("/batch/stepcfg/info/hqsj/attribvalue", sBuf);
    trim(sBuf);
    sprintf(sFileName, "%s_%s_%s_RT"/*"%s_%s_%s_RT.txt"*/, sDwbh, sPkrq, sPtpch);
    sprintf(sFilePath, "%s/%s/%s", getenv("HOME"), sBuf, sFileName);
    LOG(LM_DEBUG, Fmtmsg("生成回盘结果文件名[%s]", sFilePath), "INFO")

    fp = fopen(sFilePath, "w");
    if(fp == NULL)
    {
        fpub_SetMsg(lXmlhandle, 24103, "打开文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("打开文件失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where wbpch='%s' order by wbxh asc", sTableName, sBatchNo);

    if((plcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcur) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("数据库操作失败, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 写首行 */
    fprintf(fp, "单位编号：%s\n", sDwbh);

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcur, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        lTotCnt++;

        /* 数据的记录状态，0：初始1：成功2：失败 */
        memset(sStat, 0x00, sizeof(sStat));
        trim(sdb_batch_dsdf_detail.cgbz);
        trim(sdb_batch_dsdf_detail.zjxym);
        trim(sdb_batch_dsdf_detail.zjxyxx);
        trim(sdb_batch_dsdf_detail.xym);
        trim(sdb_batch_dsdf_detail.xyxx);
        trim(sdb_batch_dsdf_detail.jlbs);
        /* 成功标志 0-成功 1-部分成功 2-失败 9-初始 */
        /*sStat-记录状态：0-初始 1-成功 2-失败*/
        if(sdb_batch_dsdf_detail.cgbz[0] == '0' || sdb_batch_dsdf_detail.cgbz[0] == '1')
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0015");
            /*if(sdb_batch_dsdf_detail.jlbs[0] == '0')*/
            if(sdb_batch_dsdf_detail.jlbs[0] == '1'||
				sdb_batch_dsdf_detail.jlbs[0] == '2'||
				sdb_batch_dsdf_detail.jlbs[0] == '3')
            {
                strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0056");  /* 开户成功 */
            }
            strcpy(sdb_batch_dsdf_detail.zjxyxx, "入账成功");
            strcpy(sStat, "1");
        }
        else if(sdb_batch_dsdf_detail.cgbz[0] == '2') 
           /* strlen(sdb_batch_dsdf_detail.zjxym) == 0
            strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)*/
        {
            if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxym, sdb_batch_dsdf_detail.xym);
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.xyxx);

            strcpy(sStat, "2");
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0) /* 批次全部失败时，登记错误信息在kzzd7里 */
            {
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.kzzd7);
            }
        }
        else
        {
            strcpy(sStat, "2");
        }

        /* 如果核心返回响应码为空，则使用ACR2938作为默认 */
        trim(sdb_batch_dsdf_detail.zjxym);
        if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "ACR2938");
        }

        /* 收付标志 1-收 2-付 */
        memset(sLine, 0x00, sizeof(sLine));
        if(strcmp(sSfbz, "1") == 0) /* 代收 */
        {
            /*旧文件格式
            序号
            合同号
            款项日期
            户名
            银行账号
            应收总金额
            实收总金额
            应收业务费用
            实收业务费用
            应收关联费用1
            实收关联费用1
            应收关联费用2
            实收关联费用2
            入账日期
            银行返回码
            银行返回码中文说明
            */
            sprintf(sLine,"%-7ld|%-20s|%-8s|%-42s|%-18s|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%-8s|%-4s|%-60s|",
                  sdb_batch_dsdf_detail.wbxh,
                  sdb_batch_dsdf_detail.yhh1,
                  sdb_batch_dsdf_detail.kxrq,
                  sdb_batch_dsdf_detail.fkrxm,
                  sdb_batch_dsdf_detail.fkrzh,
                  sdb_batch_dsdf_detail.jyje,
                  sdb_batch_dsdf_detail.sjje,
                  sdb_batch_dsdf_detail.ywje,
                  sdb_batch_dsdf_detail.sjywje,
                  sdb_batch_dsdf_detail.fyje1,
                  sdb_batch_dsdf_detail.sjfyje1,
                  sdb_batch_dsdf_detail.fyje2,
                  sdb_batch_dsdf_detail.sjfyje2,
                  sdb_batch_dsdf_detail.zwrq,
                  sdb_batch_dsdf_detail.xym,
                  sdb_batch_dsdf_detail.xyxx);
        }
        else /* 代付 */
        {
            trim(sdb_batch_dsdf_detail.wbpch);
            trim(sdb_batch_dsdf_detail.skrzh);
            trim(sdb_batch_dsdf_detail.zjhm);
            trim(sdb_batch_dsdf_detail.kzzd6);
            trim(sdb_batch_dsdf_detail.zwrq);
            trim(sdb_batch_dsdf_detail.zjxym);
            trim(sdb_batch_dsdf_detail.zjxyxx);
            /* 旧格式 
               代付回盘文件格式
                  批次号	16A
                  序号	7A
                  客户账号	19A
                  证件号码	20A
                  户名	42A
                  客户应贷金额	13P2
                  客户实贷金额	13P2
                  入账日期	8P0
                  记录状态	1A
                  信息标识	7A
                  标识中文说明	40A
            */
            sprintf(sLine, "%-16s|%07d|%-19s|%-20s|%-42s|%013.2lf|%013.2lf|%-8s|%-1s|%-7s|%-40s|",
            //sprintf(sLine, "%s|%d|%s|%s|%s|%lf|%f|%s|%s|%s|%s|",
                    sdb_batch_dsdf_detail.wbpch,
                    sdb_batch_dsdf_detail.wbxh,
                    sdb_batch_dsdf_detail.skrzh,
                    sdb_batch_dsdf_detail.zjhm,
                    sdb_batch_dsdf_detail.kzzd6,
                    sdb_batch_dsdf_detail.jyje,
                    sdb_batch_dsdf_detail.sjje,
                    sdb_batch_dsdf_detail.zwrq,
                    sStat,
                    sdb_batch_dsdf_detail.zjxym,
                    sdb_batch_dsdf_detail.zjxyxx);
        }

        /* 写入明细行 */
        fprintf(fp, "%s\n", sLine);
        memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    }

    if(iRet < 0)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcur);

    fclose(fp);

    LOG(LM_DEBUG, Fmtmsg("共写入[%ld]笔记录到回盘结果文件", lTotCnt), "DEBUG")
    if(lTotCnt<=0)
    {
        fpub_SetMsg(lXmlhandle, 24103, "查询批次信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("查询批次信息失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML("/batch/resp/ret_file_name", sFileName);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: SPLDSDF_SJTJ_DF
  组件名称: 批量代收代付数据提交个性化处理_代付

  组件功能: 
            数据提交个性化处理_代付
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: zengy
  发布日期: 2017年10月24日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SPLDSDF_SJTJ_DF(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dChargeAmt = 0.00;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sSxfbz[1+1];
    char sJlbs[32+1];
    char sBuf[512];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    char sUpdSql[1024];
    char jslx[1+1];
    char sxxkz[1+1];
    char sJscs[18];
    char sXxje[18];
    char sSxje[18];
    double jscs = 0.00;
    double xxje = 0.00;
    double sxje = 0.00;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcurdel;
    
    char sBatchno[32+1];
    char sWjlx[1+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* 组件参数检查 */

    /* 业务表名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("业务表名[%s]", sTableName), "INFO")

    /* 批扣日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("批扣日期[%s]", sPkrq), "INFO")

    /* 平台批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("平台批次号[%s]", sPtpch), "INFO")
    
    /* 批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sBatchno, 0x00, sizeof(sBatchno));
    COMP_SOFTGETXML("/agent/req/batch_no", sBuf);
    trim(sBuf);
    pstrcopy(sBatchno, sBuf, sizeof(sBatchno));
    LOG(LM_DEBUG, Fmtmsg("批次号[%s]", sBatchno), "INFO")

    /* 单位编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("单位编号[%s]", sDwbh), "INFO")

    /* 手续费标志 0-收取 1-不收取 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSxfbz, 0x00, sizeof(sSxfbz));
    COMP_SOFTGETXML("/agent/req/sxfbz", sBuf);
    trim(sBuf);
    pstrcopy(sSxfbz, sBuf, sizeof(sSxfbz));
    LOG(LM_DEBUG, Fmtmsg("手续费标志[%s]", sSxfbz), "INFO")

    if(sSxfbz[0] == '0')
    {
        /* 查询费率信息 */
        memset(sSql, 0x00, sizeof(sSql));
        memset(jslx, 0x00, sizeof(jslx));
        memset(sxxkz, 0x00, sizeof(sxxkz));
        memset(sJscs, 0x00, sizeof(sJscs));
        memset(sXxje, 0x00, sizeof(sXxje));
        memset(sSxje, 0x00, sizeof(sSxje));
        jscs = 0.00;
        xxje = 0.00;
        sxje = 0.00;
        snprintf(sSql, sizeof(sSql), "SELECT jslx, jscs, sxxkz, xxje, sxje FROM APP_SXFFL WHERE flbs='%s' FETCH FIRST 1 ROWS ONLY", sDwbh);
        iRet = DBSelectToMultiVarChar(sErrmsg, sSql, jslx, sJscs, sxxkz, sXxje, sSxje);
        if(iRet == 0)
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        else if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("手续费参数[%s][%s][%s][%s][%s]", jslx, sJscs, sxxkz, sXxje, sSxje), "INFO")
        jscs = atof(sJscs);
        xxje = atof(sXxje);
        sxje = atof(sSxje);
    }
    
    /******
    add by llh 20180509 begin
    ******/
    memset(sSql, 0x00, sizeof(sSql));
    memset(sWjlx, 0x00, sizeof(sWjlx));
    snprintf(sSql, sizeof(sSql), "select wjlx from agent_batch_info WHERE batch_no='%s'", sBatchno);
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql, sWjlx);
    if(iRet == 0)
    {
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    else if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG, Fmtmsg("sWjlx[%s]", sWjlx), "INFO")
    /******
    add by llh 20180509 end
    ******/

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where pkrq='%s' and ptpch='%s' and shzt !='1' and clzt='9'", sTableName, sPkrq, sPtpch);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    if((plcurdel = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcurdel) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcurdel, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        dChargeAmt = 0.00;
        if(sSxfbz[0] == '0' && strcmp(sWjlx,"0")!= 0)
        {
            if(jslx[0] == '1') /* 计算参数类型为金额 */
            {
                dChargeAmt = jscs;
            }
            else if(jslx[0] == '2') /* 计算参数类型为百分比 */
            {
                dChargeAmt = sdb_batch_dsdf_detail.jyje * jscs/100 ;
                LOG(LM_DEBUG, Fmtmsg("dChargeAmt[%f]", dChargeAmt), "INFO")
            }
            else
            {
                LOG(LM_STD, Fmtmsg("计算参数类型错[%s]", jslx), "ERROR")
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(sxxkz[0] == '0') /* 上下限控制 */
            {
                /*dChargeAmt = max(sxje, min(dChargeAmt, xxje));*/
                /*如果手续费小于等于下限则取下限值*/
                if(dChargeAmt <= xxje)
                    dChargeAmt=xxje;
                /*如果手续费大于下限值*/
                else
                {
                    /*如果手续费大于等于上限值则取上限值*/
                    if(dChargeAmt >= sxje)
                        dChargeAmt=sxje;
                    /*否则取手续费本身*/
                    else
                        ;
                }
            }
            /*
            LOG(LM_STD, Fmtmsg("交易金额[%.2lf]手续费金额[%.2lf]", sdb_batch_dsdf_detail.jyje, dChargeAmt), "DEBUG")
            */
        }
        else if(strcmp(sWjlx,"0") == 0)
        	  dChargeAmt=0.00;

        /* 是否新开户标志 0-是 9-非*/
        trim(sdb_batch_dsdf_detail.skrzh);
        if(strlen(sdb_batch_dsdf_detail.skrzh) == 0)
        {
            strcpy(sJlbs, "0");
        }
        else
        {
            strcpy(sJlbs, "9");
        }

        memset(sUpdSql, 0x00, sizeof(sUpdSql));
        sprintf(sUpdSql, "UPDATE %s SET sxfje=%.2f, jlbs='%s', skrxm=kzzd6 where pkrq='%s' and ptpch='%s' and lsxh=%d and wjxh=%d",
            sTableName, dChargeAmt, sJlbs,
            sPkrq, sPtpch, sdb_batch_dsdf_detail.lsxh, sdb_batch_dsdf_detail.wjxh);
        LOG(LM_DEBUG, Fmtmsg("sUpdSql[%s]", sUpdSql), "INFO")
        iRet = DCIExecuteDirect(sUpdSql);
        if(iRet < 1)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
            DCIFreeCursor(plcurdel);
            DCIRollback();
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        lTotCnt++;
        if(lTotCnt%80 == 0)
        {
            if(DCICommit()!= 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(DCIBegin()!= 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }

    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcurdel);

    LOG(LM_DEBUG, Fmtmsg("共处理[%ld]笔记录", lTotCnt), "DEBUG")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: PLDSDF_SJTJ_DS
  组件名称: 批量代收代付数据提交个性化处理_代收

  组件功能: 
            数据提交个性化处理_代收
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: lilinghai
  发布日期: 2018年01月10日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT PLDSDF_SJTJ_DS(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dChargeAmt = 0.00;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sSxfbz[1+1];
    char sJlbs[32+1];
    char sBuf[512];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    char sUpdSql[1024];
    char jslx[1+1];
    char sxxkz[1+1];
    char sJscs[18];
    char sXxje[18];
    char sSxje[18];
    double jscs = 0.00;
    double xxje = 0.00;
    double sxje = 0.00;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcurdel;

    char sSxfgsbz[1+1];
    char sKzzd7[20+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* 组件参数检查 */

    /* 业务表名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("业务表名[%s]", sTableName), "INFO")

    /* 批扣日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("批扣日期[%s]", sPkrq), "INFO")

    /* 平台批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("平台批次号[%s]", sPtpch), "INFO")

    /* 单位编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("单位编号[%s]", sDwbh), "INFO")

    /* 手续费标志 0-收取 1-不收取 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSxfbz, 0x00, sizeof(sSxfbz));
    COMP_SOFTGETXML("/agent/req/sxfbz", sBuf);
    trim(sBuf);
    pstrcopy(sSxfbz, sBuf, sizeof(sSxfbz));
    LOG(LM_DEBUG, Fmtmsg("手续费标志[%s]", sSxfbz), "INFO")
    
    /* 手续费归属标志 0-单位，1-其他，2-个人 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSxfgsbz, 0x00, sizeof(sSxfgsbz));
    COMP_SOFTGETXML("/agent/req/sxfgsbz", sBuf);
    trim(sBuf);
    pstrcopy(sSxfgsbz, sBuf, sizeof(sSxfgsbz));
    LOG(LM_DEBUG, Fmtmsg("手续费归属标志[%s]", sSxfgsbz), "INFO")

    if(sSxfbz[0] == '0')
    {
        /* 查询费率信息 */
        memset(sSql, 0x00, sizeof(sSql));
        memset(jslx, 0x00, sizeof(jslx));
        memset(sxxkz, 0x00, sizeof(sxxkz));
        memset(sJscs, 0x00, sizeof(sJscs));
        memset(sXxje, 0x00, sizeof(sXxje));
        memset(sSxje, 0x00, sizeof(sSxje));
        jscs = 0.00;
        xxje = 0.00;
        sxje = 0.00;
        snprintf(sSql, sizeof(sSql), "SELECT jslx, jscs, sxxkz, xxje, sxje FROM APP_SXFFL WHERE flbs='%s' FETCH FIRST 1 ROWS ONLY", sDwbh);
        iRet = DBSelectToMultiVarChar(sErrmsg, sSql, jslx, sJscs, sxxkz, sXxje, sSxje);
        if(iRet == 0)
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        else if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("手续费参数[%s][%s][%s][%s][%s]", jslx, sJscs, sxxkz, sXxje, sSxje), "INFO")
        jscs = atof(sJscs);
        xxje = atof(sXxje);
        sxje = atof(sSxje);
    }

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where pkrq='%s' and ptpch='%s' and shzt !='1' and clzt='9'", sTableName, sPkrq, sPtpch);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    if((plcurdel = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcurdel) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcurdel, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        dChargeAmt = 0.00;
        if(sSxfbz[0] == '0')
        {
            if(jslx[0] == '1') /* 计算参数类型为金额 */
            {
                dChargeAmt = jscs;
            }
            else if(jslx[0] == '2') /* 计算参数类型为百分比 */
            {
                dChargeAmt = sdb_batch_dsdf_detail.jyje * jscs/100 ;
            }
            else
            {
                LOG(LM_STD, Fmtmsg("计算参数类型错[%s]", jslx), "ERROR")
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(sxxkz[0] == '0') /* 上下限控制 */
            {
                /*dChargeAmt = max(sxje, min(dChargeAmt, xxje));*/
                /*如果手续费小于等于下限则取下限值*/
                if(dChargeAmt <= xxje)
                    dChargeAmt=xxje;
                /*如果手续费大于下限值*/
                else
                {
                    /*如果手续费大于等于上限值则取上限值*/
                    if(dChargeAmt >= sxje)
                        dChargeAmt=sxje;
                    /*否则取手续费本身*/
                    else
                        ;
                }
            }
            /*
            LOG(LM_STD, Fmtmsg("交易金额[%.2lf]手续费金额[%.2lf]", sdb_batch_dsdf_detail.jyje, dChargeAmt), "DEBUG")
            */
        }
        
        /*
         * 收取个人手续费时,将金额累加到交易金额并保存
         * 1-代付 2-代收
         * */
        if(strcmp(sSxfgsbz,"2") == 0)
        {
            /*保存交易金额+手续费的总值*/
            sdb_batch_dsdf_detail.kzzd10=dChargeAmt+sdb_batch_dsdf_detail.jyje;
        }
        else
        {
            sdb_batch_dsdf_detail.kzzd10=sdb_batch_dsdf_detail.jyje;
        }

        memset(sUpdSql, 0x00, sizeof(sUpdSql));
        sprintf(sUpdSql, "UPDATE %s SET sxfje=%.2f,kzzd10=%.2f where pkrq='%s' and ptpch='%s' and lsxh=%d and wjxh=%d",
            sTableName, dChargeAmt, sdb_batch_dsdf_detail.kzzd10,
            sPkrq, sPtpch, sdb_batch_dsdf_detail.lsxh, sdb_batch_dsdf_detail.wjxh);
        iRet = DCIExecuteDirect(sUpdSql);
        if(iRet < 1)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
            DCIFreeCursor(plcurdel);
            DCIRollback();
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        lTotCnt++;
        if(lTotCnt%80 == 0)
        {
            if(DCICommit()!= 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(DCIBegin()!= 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }

    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcurdel);

    LOG(LM_DEBUG, Fmtmsg("共处理[%ld]笔记录", lTotCnt), "DEBUG")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: PLDSDF_DS_PTCHECK
  组件名称: 批量代付数据协议校验

  组件功能: 
            批量代付数据协议校验
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: lilinghai
  发布日期: 2018年01月19日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT PLDSDF_DS_PTCHECK(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    double dChargeAmt = 0.00;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sQyzt[1+1];
    char sFkrzh[32+1];
    char sSubstrFkrzh[32+1];
    char sBuf[512];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    char sUpdSql[1024];
    char sSfbz[1+1];
    char sJyqy[1+1];
    char sCpdm[16+1];
    char sQyms[1+1];
    
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcurdel;

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    memset(sPkrq, 0x00, sizeof(sPkrq));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    memset(sQyzt, 0x00, sizeof(sQyzt));
    memset(sFkrzh, 0x00, sizeof(sFkrzh));
    memset(sSubstrFkrzh, 0x00, sizeof(sSubstrFkrzh));
    memset(sTableName, 0x00, sizeof(sTableName));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(sSql, 0x00, sizeof(sSql));
    memset(sUpdSql, 0x00, sizeof(sUpdSql));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    memset(sJyqy, 0x00, sizeof(sJyqy));
    memset(sCpdm, 0x00, sizeof(sCpdm));
    memset(sQyms, 0x00, sizeof(sQyms));
    
    /* 收付标志 1-收2-付 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/sfbz", sBuf);
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("收付标志[%s]", sSfbz), "INFO")
    if(strcmp(sSfbz,"2") == 0)
    {    
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return 0;
    }

    /* 校验签约标志 0-不校验 1-校验 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/jyqy", sBuf);
    trim(sBuf);
    pstrcopy(sJyqy, sBuf, sizeof(sJyqy));
    LOG(LM_DEBUG, Fmtmsg("校验协议标志[%s]", sJyqy), "INFO")
    if(strcmp(sJyqy,"0") == 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        return 0;
    }

    /* 业务表名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("业务表名[%s]", sTableName), "INFO")

    /* 批扣日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("批扣日期[%s]", sPkrq), "INFO")

    /* 平台批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("平台批次号[%s]", sPtpch), "INFO")
    
    /* 产品代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/cpdm", sBuf);
    trim(sBuf);
    pstrcopy(sCpdm, sBuf, sizeof(sCpdm));
    LOG(LM_DEBUG, Fmtmsg("产品代码[%s]", sCpdm), "INFO")
    
    /*签约模式*/
    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select qyms from app_cpxx where cpdm='%s'", sCpdm);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    iRet = DBSelectToVarChar(sErrmsg, sQyms, sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*查询该批次所有记录,并校验协议是否有效、正确*/
    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where pkrq='%s' and ptpch='%s'", sTableName, sPkrq, sPtpch);
    LOG(LM_DEBUG, Fmtmsg("sql[%s]", sSql), "INFO")
    if((plcurdel = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcurdel) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if(iRet != 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcurdel,SD_BATCH_DSDF_DETAIL,NUMELE(SD_BATCH_DSDF_DETAIL),&sdb_batch_dsdf_detail,sErrmsg))> 0)
    {
        trim(sdb_batch_dsdf_detail.fkrzh);
        LOG(LM_DEBUG,Fmtmsg("fkrzh[%s]",sdb_batch_dsdf_detail.fkrzh),"DEBUG");
        
        memset(sUpdSql, 0x00, sizeof(sUpdSql));
        trim(sdb_batch_dsdf_detail.yhh1);
        trim(sdb_batch_dsdf_detail.fkrzh);
#if 0
        sprintf(sUpdSql, "select qyzh, qyzt from app_khcpqy where trim(yhh1)='%s' and trim(ywbh)='%s'",
				sdb_batch_dsdf_detail.yhh1,sdb_batch_dsdf_detail.ywbh);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", sUpdSql), "INFO")
        iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
		if(0 == iRet)
		{
            sprintf(sUpdSql, "select qyzh, qyzt from app_khcpqy where trim(xybh)='%s' and trim(ywbh)='%s'",
					sdb_batch_dsdf_detail.yhh1,sdb_batch_dsdf_detail.ywbh);
            LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", sUpdSql), "INFO")
            iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
		    if(0 == iRet)
			{
                sprintf(sUpdSql, "select qyzh, qyzt from app_khcpqy where trim(qyzh)='%s' and trim(ywbh)='%s'",
			    		sdb_batch_dsdf_detail.fkrzh,sdb_batch_dsdf_detail.ywbh);
                LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", sUpdSql), "INFO")
                iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
			}
		}
#endif
		/* 产品代码+银行帐号唯一 */
        if ( strcmp(sQyms,"1") == 0 )
        {
            /* 银行帐号不能为空 */
            if ( 0 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                 fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("银行帐号不能为空"));
                 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                 return -1;    
            }
            if ( 19 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE ( qyzh = '%s' or qyzh = substr('%s',7) ) AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.fkrzh , sCpdm);
			}
			else
			{
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE qyzh = '%s' AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh , sCpdm);
			}
        }
        else /* 产品代码+银行帐号+用户编号唯一 签约类型3 */
        if ( strcmp(sQyms,"3") == 0 )
        {
            /* 银行帐号不能为空 */
            if ( 0 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                DCIRollback();
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("银行帐号不能为空"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
        
            /* 用户编号不能为空 */
            if ( 0 == strlen(sdb_batch_dsdf_detail.yhh1) )
            {
                DCIRollback();
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("用户编号不能为空"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            if ( 19 == strlen(sdb_batch_dsdf_detail.fkrzh) )
            {
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE ( qyzh = '%s' or qyzh = substr('%s',7) ) AND yhh1 = '%s' AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.yhh1 ,sCpdm);
			}
			else
			{
                sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE qyzh = '%s' AND yhh1 = '%s' AND cpdm ='%s'",\
                            sdb_batch_dsdf_detail.fkrzh ,sdb_batch_dsdf_detail.yhh1 ,sCpdm);
			}
        }
        else /* 业务编号+用户编号唯一 */
        if ( strcmp(sQyms,"4") == 0 )
        {
            /* 用户编号不能为空 */
            if ( 0 == strlen(sdb_batch_dsdf_detail.yhh1) )
            {
                DCIRollback();
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("用户编号不能为空"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy WHERE yhh1 = '%s' AND ywbh='%s'", \
                         sdb_batch_dsdf_detail.yhh1 ,sdb_batch_dsdf_detail.ywbh );
        }
        else
        /* 产品代码+用户编号唯一  默认值*/
        {
            /* 用户编号不能为空 */
            if ( 0 == strlen(sdb_batch_dsdf_detail.yhh1) )
            {
                fpub_SetMsg(lXmlhandle, 24103, Fmtmsg("用户编号不能为空"));
                 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                 return -1;    
            }
            sprintf( sUpdSql,"SELECT qyzh,qyzt FROM app_khcpqy \
                        WHERE yhh1 = '%s' AND cpdm='%s'",sdb_batch_dsdf_detail.yhh1 ,sCpdm);
        }
        LOG(LM_DEBUG, Fmtmsg("sUpdSql[%s]", sUpdSql), "INFO")
        iRet = DBSelectToMultiVarChar(sErrmsg, sUpdSql, sFkrzh, sQyzt);
        if (iRet <= 0)
        {
            /*查询协议失败时更新批量代收代付表明细失败*/
            LOG(LM_STD, Fmtmsg("查询客户协议表失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            memset(sUpdSql, 0x00, sizeof(sUpdSql));
            sprintf(sUpdSql, "update %s set shzt='1',clzt='1',cgbz='2',xym='2',xyxx='校验协议时查询协议失败' where pkrq='%s' and ptpch='%s' and lsxh='%d' and wjxh='%d'",sTableName,sPkrq,sPtpch,sdb_batch_dsdf_detail.lsxh,sdb_batch_dsdf_detail.wjxh);
            LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", sUpdSql), "INFO")
            iRet = DCIExecuteDirect(sUpdSql);
            if(iRet < 1)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            continue;
        }
        /*校验协议付款人信息&&协议状态*/
        trim(sFkrzh);
        /*截取文件明细付款人账号后13位*/
        memcpy(sSubstrFkrzh,sdb_batch_dsdf_detail.fkrzh+6,sizeof(sSubstrFkrzh));
        if(strcmp(sdb_batch_dsdf_detail.fkrzh,sFkrzh) != 0 || strcmp(sQyzt,"0") != 0)
        {
            if(strcmp(sSubstrFkrzh,sFkrzh) != 0)   
            {
                LOG(LM_STD, Fmtmsg("协议校验失败"), "ERROR")
                LOG(LM_STD, Fmtmsg("协议付款人[%s],文件明细记录付款人[%s]", sFkrzh, sdb_batch_dsdf_detail.fkrzh), "ERROR")
                LOG(LM_STD, Fmtmsg("协议状态[%s] 0-有效 1-撤销", sQyzt), "ERROR")
                memset(sUpdSql, 0x00, sizeof(sUpdSql));
                sprintf(sUpdSql, "update %s set shzt='1',clzt='1',cgbz='2',xym='2',xyxx='协议校验失败' where pkrq='%s' and ptpch='%s' and lsxh='%d' and wjxh='%d'",sTableName,sPkrq,sPtpch,sdb_batch_dsdf_detail.lsxh,sdb_batch_dsdf_detail.wjxh);
                LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", sUpdSql), "INFO")
                iRet = DCIExecuteDirect(sUpdSql);
                if(iRet < 1)
                {
                    LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s][%d][%s]", DCILastError(), iRet, sUpdSql), "ERROR")
                    DCIFreeCursor(plcurdel);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                continue;
            }
        }

        lTotCnt++;
        if(lTotCnt%80 == 0)
        {
            if(DCICommit()!= 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            if(DCIBegin()!= 0)
            {
                LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
                DCIFreeCursor(plcurdel);
                DCIRollback();
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }

    if(iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIFreeCursor(plcurdel);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcurdel);

    LOG(LM_DEBUG, Fmtmsg("共处理[%ld]笔记录", lTotCnt), "DEBUG")

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
  动态组件函数定义
  组件函数名称: PLDSDF_PTC_PLWJDR
  组件名称: 批量文件协议更新导入文件并组织核心文件

  组件功能: 
            批量文件协议更新导入文件并组织核心文件
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: 
  发布日期: 
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT PLDSDF_PTC_PLWJDR(HXMLTREE lXmlhandle)
{
    FILE *fp=NULL;
    FILE *fp2=NULL;
    char sBuf[1024+1];
    char sLine[1024+1];
    char sBatchno[32+1];
    char sFilename[120+1];
    char sNewFilename[120+1];
    char sNewPathFilename[120+1];
    char sDwbh[16+1];
    char sSysdate[8+1];
    char sSystime[6+1];
    char sXyxljz[8+1];
    char sQygy[16+1];
    char sQdbs[4+1];
    char sJyjg[16+1];
    char sCmd[521+1];
    char sCurrvalue[10+1];
    char cErrmsg[521+1];
    char sSignType[1+1];
    char sCpdm[16+1];
    SDB_PLDSDF_CUSTOM_DETAIL sdb_pldsdf_custom_detail;
    
    int iNum=0;
    int iRet=0;

    memset(sBuf,0x00,sizeof(sBuf));
    memset(sLine,0x00,sizeof(sLine));
    memset(sBatchno,0x00,sizeof(sBatchno));
    memset(sFilename,0x00,sizeof(sFilename));
    memset(sNewFilename,0x00,sizeof(sNewFilename));
    memset(sNewPathFilename,0x00,sizeof(sNewPathFilename));
    memset(sDwbh,0x00,sizeof(sDwbh));
    memset(sSysdate,0x00,sizeof(sSysdate));
    memset(sSystime,0x00,sizeof(sSystime));
    memset(sXyxljz,0x00,sizeof(sXyxljz));
    memset(sQygy,0x00,sizeof(sQygy));
    memset(sQdbs,0x00,sizeof(sQdbs));
    memset(sJyjg,0x00,sizeof(sJyjg));
    memset(sCmd,0x00,sizeof(sCmd));
    memset(sCurrvalue,0x00,sizeof(sCurrvalue));
    memset(cErrmsg,0x00,sizeof(cErrmsg));
    memset(sSignType,0x00,sizeof(sSignType));
    memset(sCpdm,0x00,sizeof(sCpdm));
    
    char gnm[1+1];
    char qystlx[1+1];
    char jyqd[10+1];
    char sXybh[20+1];
    char sSql1[1024+1];
    char sFilestr[1024+1];
       
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    /* 批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/batch/req/batch_no", sBuf);
    trim(sBuf);
    pstrcopy(sBatchno, sBuf, sizeof(sBatchno));
    LOG(LM_DEBUG, Fmtmsg("批次号[%s]", sBatchno), "INFO")
    
    /* 柜面上送文件名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/localpathfile_name", sBuf);
    trim(sBuf);
    pstrcopy(sFilename, sBuf, sizeof(sFilename));
    LOG(LM_DEBUG, Fmtmsg("柜面上送文件名[%s]", sFilename), "INFO")
    
    /* 单位编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("单位编号[%s]", sDwbh), "INFO")
    
    /* 系统日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf);
    trim(sBuf);
    pstrcopy(sSysdate, sBuf, sizeof(sSysdate));
    
    /* 系统时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf);
    trim(sBuf);
    pstrcopy(sSystime, sBuf, sizeof(sSystime));
    
    /* 协议序列键值 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/app/cpxx/xyxljz", sBuf);
    trim(sBuf);
    pstrcopy(sXyxljz, sBuf, sizeof(sXyxljz));
    
    /* 签约柜员 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/tel", sBuf);
    trim(sBuf);
    pstrcopy(sQygy, sBuf, sizeof(sQygy));
    
    /* 渠道标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/qdbs", sBuf);
    trim(sBuf);
    pstrcopy(sQdbs, sBuf, sizeof(sQdbs));
    
    /* 交易机构 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/agent/req/brc", sBuf);
    trim(sBuf);
    pstrcopy(sJyjg, sBuf, sizeof(sJyjg));
    
    /* 签约模式 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/app/cpxx/qyms", sBuf);
    trim(sBuf);
    pstrcopy(sSignType, sBuf, sizeof(sSignType));
    
    /* 产品代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/app/cpxx/cpdm", sBuf);
    trim(sBuf);
    pstrcopy(sCpdm, sBuf, sizeof(sCpdm));
    
    sprintf(sNewFilename,"%s_%s_%s.req",sDwbh,sSysdate,sSystime);
    sprintf(sNewPathFilename,"%s/file/batch/0041000/%s/%s_%s_%s.req",getenv("HOME"),sSysdate,sDwbh,sSysdate,sSystime);
    LOG(LM_DEBUG, Fmtmsg("上送核心文件名[%s]", sNewPathFilename), "INFO")
    
    /*打开柜面文件*/
    fp=fopen(sFilename,"r");
    if(fp == NULL)
    {
        LOG(LM_STD, Fmtmsg("打开柜面文件失败"), "")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*打开上送核心文件*/
    fp2 = fopen(sNewPathFilename, "w");
    if(fp2 == NULL)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("打开上送核心文件失败"), "")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
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
    
    memset(sLine,0x00,sizeof(sLine));
    while(fgets(sLine, sizeof(sLine)-1, fp) != NULL)
    {
        iNum++;
        trim(sLine);
        if(strlen(sLine)==0)
            continue;
        
        LOG(LM_DEBUG, Fmtmsg("第[%d]条文件明细记录",iNum),"DEBUG");
        LOG(LM_DEBUG, Fmtmsg("sLine[%s]",sLine),"DEBUG");
        memset(gnm,0x00,sizeof(gnm));
        memset(qystlx,0x00,sizeof(qystlx));
        memset(jyqd,0x00,sizeof(jyqd));
        memset(sXybh,0x00,sizeof(sXybh));
        memset(sFilestr,0x00,sizeof(sFilestr));
        memset(cErrmsg,0x00,sizeof(cErrmsg));
        memset(&sdb_pldsdf_custom_detail,0x00,sizeof(sdb_pldsdf_custom_detail));
        
        pstrcopy(sdb_pldsdf_custom_detail.pch,sBatchno,sizeof(sdb_pldsdf_custom_detail.pch));
        pstrcopy(sdb_pldsdf_custom_detail.wjmc,sFilename,sizeof(sdb_pldsdf_custom_detail.wjmc));
        pstrcopy(sdb_pldsdf_custom_detail.qygy,sQygy,sizeof(sdb_pldsdf_custom_detail.qygy));
        pstrcopy(sdb_pldsdf_custom_detail.qyjg,sJyjg,sizeof(sdb_pldsdf_custom_detail.qyjg));
        
        /*第1个值--序号*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 1, sBuf, '|', '\\');
        trim(sBuf);
        sdb_pldsdf_custom_detail.wjxh=atoi(sBuf);
        
        /*第4个值--银行账号名称*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 4, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.yhzhmc,sBuf,sizeof(sdb_pldsdf_custom_detail.yhzhmc));

        /*第5个值--证件号码*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 5, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.zjhm,sBuf,sizeof(sdb_pldsdf_custom_detail.zjhm));

        /*第8个值--联系地址*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 8, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.lxdz,sBuf,sizeof(sdb_pldsdf_custom_detail.lxdz));

        /*第9个值--备注*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 9, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.bz,sBuf,sizeof(sdb_pldsdf_custom_detail.bz));

        /*第10个值--备用1*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 10, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.bz1,sBuf,sizeof(sdb_pldsdf_custom_detail.bz1));

        /*第11个值--备用2*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 11, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.bz2,sBuf,sizeof(sdb_pldsdf_custom_detail.bz2));
        
        /*第6个值--协议记录状态*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 6, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.xyjlzt,sBuf,sizeof(sdb_pldsdf_custom_detail.xyjlzt));
        if(strcmp(sBuf,"0")==0)
            strcpy(gnm,"A");
        else if(strcmp(sBuf,"1")==1)
            strcpy(gnm,"C");
        else
            continue;
        
        /*生成协议序列号*/
        memset(sCmd,0x00,sizeof(sCmd));
        sprintf(sCmd,"select curr_value from  app_xlkz where pkey='%s'",sXyxljz);
        iRet=DBSelectToVarChar(cErrmsg,sCurrvalue,sCmd);
        if (0 > iRet)
        {
            LOG(LM_STD, Fmtmsg("获取协议序列号失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sprintf(sdb_pldsdf_custom_detail.xybh,"%s%s",sSysdate,sCurrvalue);
        
        memset(sCmd,0x00,sizeof(sCmd));
        sprintf(sCmd,"update app_xlkz set curr_value=curr_value+1");
        iRet=DCIExecuteDirect(sCmd);
        if (0 >= iRet)
        {
            LOG(LM_STD, Fmtmsg("获取协议序列号失败, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        /*第2个值--合同号*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 2, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.hth,sBuf,sizeof(sdb_pldsdf_custom_detail.hth));
        
        strcpy(sdb_pldsdf_custom_detail.xydm,"10000030");
        strcpy(qystlx,"1");
        
        /*第3个值--银行账号*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 3, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.yhzh,sBuf,sizeof(sdb_pldsdf_custom_detail.yhzh));
        
        /*第7个值--联系电话*/
        memset(sBuf,0x00,sizeof(sBuf));
        GetListbyDiv(sLine, 7, sBuf, '|', '\\');
        trim(sBuf);
        pstrcopy(sdb_pldsdf_custom_detail.lxdh,sBuf,sizeof(sdb_pldsdf_custom_detail.lxdh));
        
        strcpy(sdb_pldsdf_custom_detail.qysxrq,sSysdate);
        strcpy(sdb_pldsdf_custom_detail.qydqrq,"29991230");
        strcpy(sdb_pldsdf_custom_detail.qyrq,sSysdate);
        strcpy(jyqd,"80");
        
        /* 插入批量客户签约明细表 */
        LOG(LM_DEBUG,Fmtmsg("pch[%s]",sdb_pldsdf_custom_detail.pch),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("wjxh[%d]",sdb_pldsdf_custom_detail.wjxh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("wjmc[%s]",sdb_pldsdf_custom_detail.wjmc),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("hth[%s]",sdb_pldsdf_custom_detail.hth),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("tyxybh[%s]",sdb_pldsdf_custom_detail.tyxybh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("xybh[%s]",sdb_pldsdf_custom_detail.xybh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("xydm[%s]",sdb_pldsdf_custom_detail.xydm),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("khh[%s]",sdb_pldsdf_custom_detail.khh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("yhzh[%s]",sdb_pldsdf_custom_detail.yhzh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("yhzhmc[%s]",sdb_pldsdf_custom_detail.yhzhmc),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("zjhm[%s]",sdb_pldsdf_custom_detail.zjhm),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("xyjlzt[%s]",sdb_pldsdf_custom_detail.xyjlzt),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("lxdh[%s]",sdb_pldsdf_custom_detail.lxdh),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("lxdz[%s]",sdb_pldsdf_custom_detail.lxdz),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qysxrq[%s]",sdb_pldsdf_custom_detail.qysxrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qydqrq[%s]",sdb_pldsdf_custom_detail.qydqrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qyrq[%s]",sdb_pldsdf_custom_detail.qyrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("jyrq[%s]",sdb_pldsdf_custom_detail.jyrq),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qygy[%s]",sdb_pldsdf_custom_detail.qygy),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("jygy[%s]",sdb_pldsdf_custom_detail.jygy),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("qyjg[%s]",sdb_pldsdf_custom_detail.qyjg),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("fhxxm[%s]",sdb_pldsdf_custom_detail.fhxxm),"DEBUG");
        LOG(LM_DEBUG,Fmtmsg("cwzwms[%s]",sdb_pldsdf_custom_detail.cwzwms),"DEBUG");
        
        /**************检查是否已签约*****************/
        /* 产品代码+银行帐号唯一 */
		memset(sSql1,0x00,sizeof(sSql1));
        if ( sSignType[0] == '1' )
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE \
                qyzh='%s' AND cpdm='%s' and qyzt='0' ",sdb_pldsdf_custom_detail.yhzh, sCpdm );
        }
        else
        /* 产品代码+银行帐号+用户编号唯一 签约类型3 为默认值 */
        if ( sSignType[0] == '3' )
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE \
                qyzh='%s' AND yhh1='%s'  AND cpdm='%s' and qyzt='0' ",sdb_pldsdf_custom_detail.yhzh, sdb_pldsdf_custom_detail.hth, sCpdm );
        }
        
        else
        /* 业务编号+用户编号唯一 */
        if ( sSignType[0] == '4' )
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE\
                yhh1='%s'  AND ywbh='%s' and qyzt='0' ",sdb_pldsdf_custom_detail.hth, sDwbh);
        }
        
        else
        /* 产品代码+用户编号唯一 */
        {
            snprintf( sSql1, sizeof( sSql1 ), "SELECT xybh FROM app_khcpqy WHERE\
                yhh1='%s'  AND cpdm='%s' and qyzt='0' ", sdb_pldsdf_custom_detail.hth, sCpdm );
        }
        LOG(LM_DEBUG, Fmtmsg("sSql1[%s]",sSql1), "INFO")
        iRet = DBSelectToMultiVar( cErrmsg, sSql1, sXybh ) ;
        LOG(LM_DEBUG, Fmtmsg("iRet[%d]  sXybh[%s]",iRet,sXybh), "INFO")
        if ( iRet == 0 )  /* 记录不存在 */
        {
            /*写入核心文件*/
            sprintf(sFilestr,"%-26s%-26s%-1s%-60s%-10s%-32s%-8s%-1s%-32s%-1s%-32s%-18s%-8s%-8s%-8s%-8s%-5s\
                        %-5s%-20s%-32s%-6s%-5s%-20s%-122s%-122s%-30s%-7s%-60s\n",
               " "," ",gnm,sdb_pldsdf_custom_detail.xybh," ",sdb_pldsdf_custom_detail.yhzh,sdb_pldsdf_custom_detail.xydm,qystlx,
               sdb_pldsdf_custom_detail.yhzh," "," ",sdb_pldsdf_custom_detail.lxdh,sdb_pldsdf_custom_detail.qysxrq,sdb_pldsdf_custom_detail.qydqrq,
               sdb_pldsdf_custom_detail.qyrq,"00000000",sdb_pldsdf_custom_detail.qygy," "," ",sQdbs,sQdbs,sdb_pldsdf_custom_detail.qyjg,
               " "," "," "," "," "," ");
            fwrite(sFilestr,strlen(sFilestr),1,fp2);
        }
        else  /*  查询失败或者查询到签约记录 */
        {
            if(iRet < 0)
            {
                strcpy(sdb_pldsdf_custom_detail.djzt,"2");/*签约失败*/
                strcpy(sdb_pldsdf_custom_detail.fhxxm,"999999");
                strcpy(sdb_pldsdf_custom_detail.cwzwms,"查询数据库失败");                
            }
            else if(iRet > 0)
            {
                strcpy(sdb_pldsdf_custom_detail.djzt,"3");/*重复签约*/
                strcpy(sdb_pldsdf_custom_detail.fhxxm,"999999");
                strcpy(sdb_pldsdf_custom_detail.cwzwms,"重复签约");   
            }
        }
        
        /**************检查是否已签约*****************/

        iRet = DBInsert("pldsdf_custom_detail", SD_PLDSDF_CUSTOM_DETAIL, NUMELE(SD_PLDSDF_CUSTOM_DETAIL), &sdb_pldsdf_custom_detail, cErrmsg);
        if(iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIRollback();
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("插入批量客户签约明细表pldsdf_custom_detail成功"), "INFO")
        
        memset(sLine,0x00,sizeof(sLine));
        memset(&sdb_pldsdf_custom_detail,0x00,sizeof(sdb_pldsdf_custom_detail));
    }
    
    if(DCICommit()!= 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    fclose(fp);
    fclose(fp2);
    
    COMP_SOFTSETXML("/agent/req/hxfilename",sNewFilename);
    COMP_SOFTSETXML("/agent/req/hxpathfilename",sNewPathFilename);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}
/************************************************************************
  动态组件函数定义
  组件函数名称: SPLDS_FILEGEN
  组件名称: 批量代收单笔缴费查询文件生成

  组件功能: 
            生成结果回盘文件
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: 中间业务项目组
  程 序 员: llh
  发布日期: 2018年09月21日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
IRESULT SPLDS_FILEGEN(HXMLTREE lXmlhandle)
{
    int iRet = 0;
    int iParas;
    long lTotCnt = 0;
    char sBatchNo[32+1];
    char sSfbz[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sDwbh[16+1];
    char sStat[1+1];
    char sDownFlag[1+1];
    char sBuf[512];
    char sFileName[256+1];
    char sFilePath[512+1];
    char sLine[1024];
    char sTableName[64];
    char sErrmsg[512];
    char sSql[1024];
    FILE *fp = NULL;
    SDB_BATCH_DSDF_DETAIL sdb_batch_dsdf_detail;
    CURSOR plcur;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG")

    /* 组件参数检查 */
    COMP_PARACOUNTCHKMIN(2)

    /* 商户批次号 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sBatchNo, 0x00, sizeof(sBatchNo));
    COMP_GETPARSEPARAS(1, sBuf, "商户批次号")
    trim(sBuf);
    pstrcopy(sBatchNo, sBuf, sizeof(sBatchNo));
    LOG(LM_DEBUG, Fmtmsg("商户批次号[%s]", sBatchNo), "INFO")

    /* 收付标志 1-收2-付 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sSfbz, 0x00, sizeof(sSfbz));
    COMP_GETPARSEPARAS(2, sBuf, "收付标志")
    trim(sBuf);
    pstrcopy(sSfbz, sBuf, sizeof(sSfbz));
    LOG(LM_DEBUG, Fmtmsg("收付标志[%s]", sSfbz), "INFO")

    /* 业务表名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTableName, 0x00, sizeof(sTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", sBuf);
    trim(sBuf);
    pstrcopy(sTableName, sBuf, sizeof(sTableName));
    LOG(LM_DEBUG, Fmtmsg("业务表名[%s]", sTableName), "INFO")

    /* 批扣日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML("/batch/resp/pkrq", sBuf);
    trim(sBuf);
    pstrcopy(sPkrq, sBuf, sizeof(sPkrq));
    LOG(LM_DEBUG, Fmtmsg("批扣日期[%s]", sPkrq), "INFO")

    /* 平台批次号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML("/batch/resp/ptpch", sBuf);
    trim(sBuf);
    pstrcopy(sPtpch, sBuf, sizeof(sPtpch));
    LOG(LM_DEBUG, Fmtmsg("平台批次号[%s]", sPtpch), "INFO")

    /* 单位编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDwbh, 0x00, sizeof(sDwbh));
    COMP_SOFTGETXML("/agent/resp/dwbh", sBuf);
    trim(sBuf);
    pstrcopy(sDwbh, sBuf, sizeof(sDwbh));
    LOG(LM_DEBUG, Fmtmsg("单位编号[%s]", sDwbh), "INFO")

    /* 文件下载标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDownFlag, 0x00, sizeof(sDownFlag));
    COMP_SOFTGETXML("/agent/req/down_flag", sBuf);
    trim(sBuf);
    pstrcopy(sDownFlag, sBuf, sizeof(sDownFlag));
    LOG(LM_DEBUG, Fmtmsg("文件下载标志[%s]", sDownFlag), "INFO")

    /* 回盘结果文件名 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    memset(sFilePath, 0x00, sizeof(sFilePath));
    COMP_SOFTGETXML("/batch/stepcfg/info/hqsj/attribvalue", sBuf);
    trim(sBuf);
    sprintf(sFileName, "%s_%s_%s_RT"/*"%s_%s_%s_RT.txt"*/, sDwbh, sPkrq, sPtpch);
    sprintf(sFilePath, "%s/%s/%s", getenv("HOME"), sBuf, sFileName);
    LOG(LM_DEBUG, Fmtmsg("生成回盘结果文件名[%s]", sFilePath), "INFO")

    fp = fopen(sFilePath, "w");
    if(fp == NULL)
    {
        fpub_SetMsg(lXmlhandle, 24103, "打开文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("打开文件失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "select * from %s where wbpch='%s' order by wbxh asc", sTableName, sBatchNo);

    if((plcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if(DCIExecute(plcur) == -1)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("数据库操作失败, sql[%s] err[%s]", sSql, DCILastError()), "ERROR")
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 写首行 */
    fprintf(fp, "单位编号：%s\n", sDwbh);

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    while((iRet = DBFetch(plcur, SD_BATCH_DSDF_DETAIL, NUMELE(SD_BATCH_DSDF_DETAIL), &sdb_batch_dsdf_detail, sErrmsg ) ) > 0 )
    {
        lTotCnt++;

        /* 数据的记录状态，0：初始1：成功2：失败 */
        memset(sStat, 0x00, sizeof(sStat));
        trim(sdb_batch_dsdf_detail.cgbz);
        trim(sdb_batch_dsdf_detail.zjxym);
        trim(sdb_batch_dsdf_detail.zjxyxx);
        trim(sdb_batch_dsdf_detail.xym);
        trim(sdb_batch_dsdf_detail.xyxx);
        trim(sdb_batch_dsdf_detail.jlbs);
        /* 成功标志 0-成功 1-部分成功 2-失败 9-初始 */
        /*sStat-记录状态：0-初始 1-成功 2-失败*/
        if(sdb_batch_dsdf_detail.cgbz[0] == '0' || sdb_batch_dsdf_detail.cgbz[0] == '1')
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0015");
            /*if(sdb_batch_dsdf_detail.jlbs[0] == '0')*/
            if(sdb_batch_dsdf_detail.jlbs[0] == '1'||
				sdb_batch_dsdf_detail.jlbs[0] == '2'||
				sdb_batch_dsdf_detail.jlbs[0] == '3')
            {
                strcpy(sdb_batch_dsdf_detail.zjxym, "AGR0056");  /* 开户成功 */
            }
            strcpy(sdb_batch_dsdf_detail.zjxyxx, "入账成功");
            strcpy(sStat, "1");
        }
        else if(sdb_batch_dsdf_detail.cgbz[0] == '2') 
           /* strlen(sdb_batch_dsdf_detail.zjxym) == 0
            strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)*/
        {
            if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxym, sdb_batch_dsdf_detail.xym);
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0)
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.xyxx);

            strcpy(sStat, "2");
            if(strlen(sdb_batch_dsdf_detail.zjxyxx) == 0) /* 批次全部失败时，登记错误信息在kzzd7里 */
            {
                strcpy(sdb_batch_dsdf_detail.zjxyxx, sdb_batch_dsdf_detail.kzzd7);
            }
        }
        else
        {
            strcpy(sStat, "2");
        }

        /* 如果核心返回响应码为空，则使用ACR2938作为默认 */
        trim(sdb_batch_dsdf_detail.zjxym);
        if(strlen(sdb_batch_dsdf_detail.zjxym) == 0)
        {
            strcpy(sdb_batch_dsdf_detail.zjxym, "ACR2938");
        }

        /* 收付标志 1-收 2-付 */
        memset(sLine, 0x00, sizeof(sLine));
        if(strcmp(sSfbz, "1") == 0) /* 代收 */
        {
            /*旧文件格式
            序号
            合同号
            款项日期
            户名
            银行账号
            应收总金额
            实收总金额
            应收业务费用
            实收业务费用
            应收关联费用1
            实收关联费用1
            应收关联费用2
            实收关联费用2
            入账日期
            银行返回码
            银行返回码中文说明
            */
            sprintf(sLine,"%-7ld|%-20s|%-8s|%-42s|%-18s|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%013.2f|%-8s|%-4s|%-60s|",
                  sdb_batch_dsdf_detail.wbxh,
                  sdb_batch_dsdf_detail.yhh1,
                  sdb_batch_dsdf_detail.kxrq,
                  sdb_batch_dsdf_detail.fkrxm,
                  sdb_batch_dsdf_detail.fkrzh,
                  sdb_batch_dsdf_detail.jyje,
                  sdb_batch_dsdf_detail.sjje,
                  sdb_batch_dsdf_detail.ywje,
                  sdb_batch_dsdf_detail.sjywje,
                  sdb_batch_dsdf_detail.fyje1,
                  sdb_batch_dsdf_detail.sjfyje1,
                  sdb_batch_dsdf_detail.fyje2,
                  sdb_batch_dsdf_detail.sjfyje2,
                  sdb_batch_dsdf_detail.zwrq,
                  sdb_batch_dsdf_detail.xym,
                  sdb_batch_dsdf_detail.xyxx);
        }
        else /* 代付 */
        {
            trim(sdb_batch_dsdf_detail.wbpch);
            trim(sdb_batch_dsdf_detail.skrzh);
            trim(sdb_batch_dsdf_detail.zjhm);
            trim(sdb_batch_dsdf_detail.kzzd6);
            trim(sdb_batch_dsdf_detail.zwrq);
            trim(sdb_batch_dsdf_detail.zjxym);
            trim(sdb_batch_dsdf_detail.zjxyxx);
            /* 旧格式 
               代付回盘文件格式
                  批次号	16A
                  序号	7A
                  客户账号	19A
                  证件号码	20A
                  户名	42A
                  客户应贷金额	13P2
                  客户实贷金额	13P2
                  入账日期	8P0
                  记录状态	1A
                  信息标识	7A
                  标识中文说明	40A
            */
            sprintf(sLine, "%-16s|%07d|%-19s|%-20s|%-42s|%013.2lf|%013.2lf|%-8s|%-1s|%-7s|%-40s|",
            //sprintf(sLine, "%s|%d|%s|%s|%s|%lf|%f|%s|%s|%s|%s|",
                    sdb_batch_dsdf_detail.wbpch,
                    sdb_batch_dsdf_detail.wbxh,
                    sdb_batch_dsdf_detail.skrzh,
                    sdb_batch_dsdf_detail.zjhm,
                    sdb_batch_dsdf_detail.kzzd6,
                    sdb_batch_dsdf_detail.jyje,
                    sdb_batch_dsdf_detail.sjje,
                    sdb_batch_dsdf_detail.zwrq,
                    sStat,
                    sdb_batch_dsdf_detail.zjxym,
                    sdb_batch_dsdf_detail.zjxyxx);
        }

        /* 写入明细行 */
        fprintf(fp, "%s\n", sLine);
        memset(&sdb_batch_dsdf_detail, 0x00, sizeof(sdb_batch_dsdf_detail));
    }

    if(iRet < 0)
    {
        fclose(fp);
        LOG(LM_STD, Fmtmsg("数据库操作失败, sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        DCIFreeCursor(plcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(plcur);

    fclose(fp);

    LOG(LM_DEBUG, Fmtmsg("共写入[%ld]笔记录到回盘结果文件", lTotCnt), "DEBUG")
    if(lTotCnt<=0)
    {
        fpub_SetMsg(lXmlhandle, 24103, "查询批次信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("查询批次信息失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML("/batch/resp/ret_file_name", sFileName);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    return COMPRET_SUCC;
}
