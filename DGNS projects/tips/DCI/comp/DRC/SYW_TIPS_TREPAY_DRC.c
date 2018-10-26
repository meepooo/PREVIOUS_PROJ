/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V3.0.00
  操作系统:AIX5.3
  文件名称:SYW_TIPS_PUBLIC_DRC.c
  文件描述:TIPS个性化公共组件
  项 目 组:TIPS专用前置产品组
  程 序 员:sunpj
  发布日期:
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

#include "../../eh/DRC/tips_trepayfileinfo_drc.h"
#include "../../eh/DRC/tips_trepayfiledetail_drc.h"

/************************************************************************
  动态组件函数定义
  组件函数名称: SYW_TIPS_TREPAY_INDB
  组件名称: 国库集中支付文件信息落地

  组件功能: 
  国库集中支付文件信息落地
  组件参数: 
  序号 参数名称     资源类别       缺省值   是否可空  参数说明

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作

  项 目 组: TIPS专用前置产品组
  程 序 员: sunpj
  发布日期: 2017年05月31日
  修改日期: 
  修改日期: 
  参数使用示例: 
 ************************************************************************/
 IRESULT SYW_TIPS_TREPAY_INDB(HXMLTREE lXmlhandle)
{
    int    iParas;
    int    iRet = 0;
    long   lFileLine = 0;
    double dTotalAmt = 0.00;
    char   cFileType[1 + 1]            = {0};
    char   cFileName[128 + 1]          = {0};
    char   cFilePath[512 + 1]          = {0};
    char   cFileNameAll[1024 + 1]      = {0};
    char   cTmp[512 + 1]               = {0};
    char   cBuf[2048 + 1]              = {0};
    char   cErrMsg[512 + 1]            = {0};
    FILE   *fp = NULL;
    
    SDB_TIPS_TREPAYFILEINFO      stTrePayFileInfo;
    SDB_TIPS_TREPAYFILEDETAIL    stTrePayFileDetail;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TREPAY_INDB...处理开始"), "INFO")
    
    memset(&stTrePayFileInfo, 0x00, sizeof(stTrePayFileInfo));
    
    COMP_PARACOUNTCHK(3);
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cFileType, 0x00, sizeof(cFileType));
    COMP_GETPARSEPARAS(1, cTmp, "文件类型");
    pstrcopy(cFileType, cTmp, sizeof(cFileType));
    LOG(LM_DEBUG, Fmtmsg("文件类型[%s]", cFileType), "INFO")
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cFileName, 0x00, sizeof(cFileName));
    COMP_GETPARSEPARAS(2, cTmp, "文件名");
    pstrcopy(cFileName, cTmp, sizeof(cFileName));
    LOG(LM_DEBUG, Fmtmsg("文件名[%s]", cFileName), "INFO")
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cFilePath, 0x00, sizeof(cFilePath));
    COMP_GETPARSEPARAS(3, cTmp, "文件路径");
    pstrcopy(cFilePath, cTmp, sizeof(cFilePath));
    LOG(LM_DEBUG, Fmtmsg("文件路径[%s]", cFilePath), "INFO")
    
    /**获取日期**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/zwrq", cTmp)
    pstrcopy(stTrePayFileInfo.trandate, cTmp, sizeof(stTrePayFileInfo.trandate));
    
    /**获取流水**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/pub/zhqzlsh", cTmp)
    stTrePayFileInfo.transeq = atol(cTmp);
    
    /**获取包流水号**/
    pstrcopy(stTrePayFileInfo.packno, cTmp, sizeof(stTrePayFileInfo.packno));
    
    /**获取交易机构**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/pub/jgdh", cTmp)
    pstrcopy(stTrePayFileInfo.brc, cTmp, sizeof(stTrePayFileInfo.brc));
    
    /**获取交易柜员**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/pub/jygy", cTmp)
    pstrcopy(stTrePayFileInfo.tel, cTmp, sizeof(stTrePayFileInfo.tel));
    
    /**获取系统时间**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/sys/systime", cTmp)
    pstrcopy(stTrePayFileInfo.tel, cTmp, sizeof(stTrePayFileInfo.tel));
    
    /**获取步点信息**/
    pstrcopy(stTrePayFileInfo.step, "0", sizeof(stTrePayFileInfo.step));
    
    /**获取状态信息**/
    pstrcopy(stTrePayFileInfo.state, "0", sizeof(stTrePayFileInfo.state));
    
    /**获取文件类型**/
    pstrcopy(stTrePayFileInfo.filetype, cFileType, sizeof(stTrePayFileInfo.filetype));
    
    /**获取文件名**/
    pstrcopy(stTrePayFileInfo.filename, cFileName, sizeof(stTrePayFileInfo.filename));
    
    /**获取国库代码**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/TreCode", cTmp)
    pstrcopy(stTrePayFileInfo.trecode, cTmp, sizeof(stTrePayFileInfo.trecode));
    
    /**获取财政机关代码**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/FinOrgCode", cTmp)
    pstrcopy(stTrePayFileInfo.finorgcode, cTmp, sizeof(stTrePayFileInfo.finorgcode));
    
    /**获取支出凭证类型**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayoutVouType", cTmp)
    pstrcopy(stTrePayFileInfo.payoutvoutype, cTmp, sizeof(stTrePayFileInfo.payoutvoutype));
    
    /**获取支付方式**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayMode", cTmp)
    pstrcopy(stTrePayFileInfo.paytype, cTmp, sizeof(stTrePayFileInfo.paytype));
    
    /**获取收款人账号**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeAcct", cTmp)
    pstrcopy(stTrePayFileInfo.payeeacct, cTmp, sizeof(stTrePayFileInfo.payeeacct));
    
    /**获取收款人名称**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeName", cTmp)
    pstrcopy(stTrePayFileInfo.payeename, cTmp, sizeof(stTrePayFileInfo.payeename));
    
    /**获取收款人地址**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeAddr", cTmp)
    pstrcopy(stTrePayFileInfo.payeeaddr, cTmp, sizeof(stTrePayFileInfo.payeeaddr));
    
    /**获取收款人开户行行号**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeOpBkNo", cTmp)
    pstrcopy(stTrePayFileInfo.payeeopbk, cTmp, sizeof(stTrePayFileInfo.payeeopbk));
    
    /**读取文件信息&登记文件信息到表----BEGIN**/
    sprintf(cFileNameAll, "%s/%s", cFilePath, cFileName);
    if (NULL == (fp = fopen(cFileNameAll, "r")))
    {
        LOG(LM_STD, Fmtmsg("读取文件失败[%s]", cFileNameAll), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 100001, "读取文件失败");
        return COMPRET_FAIL;
    }
    
    while (NULL != fgets(cBuf, sizeof(cBuf), fp))
    {
        lFileLine++;
        //LOG(LM_DEBUG, Fmtmsg("%d---[%s]", lFileLine, cBuf), "INFO")
        if (1 == lFileLine)
        {
            /**获取凭证编码**/
            GetListbyDiv(cBuf, 2, stTrePayFileInfo.vouno, ',','\\');
            
            /**获取凭证日期**/
            GetListbyDiv(cBuf, 3, stTrePayFileInfo.voudate, ',','\\');
            
            /**获取付款人账号**/
            GetListbyDiv(cBuf, 4, stTrePayFileInfo.payacct, ',','\\');
            
            /**获取付款人名称**/
            GetListbyDiv(cBuf, 5, stTrePayFileInfo.payname, ',','\\');
            
            /**获取付款人地址**/
            GetListbyDiv(cBuf, 6, stTrePayFileInfo.payaddr, ',','\\');
            
            /**获取附言**/
            GetListbyDiv(cBuf, 11, stTrePayFileInfo.addword, ',','\\');
            
            /**获取预算种类**/
            GetListbyDiv(cBuf, 12, stTrePayFileInfo.budgettype, ',','\\');
            
            /**获取整理期标志**/
            GetListbyDiv(cBuf, 13, stTrePayFileInfo.trimsign, ',','\\');
            
            /**获取所属年度**/
            GetListbyDiv(cBuf, 14, stTrePayFileInfo.ofyear, ',','\\');
            
            /**获取总金额**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 15, cTmp, ',','\\');
            stTrePayFileInfo.totalamt = atof(cTmp);
            
            /**获取总笔数**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 16, cTmp, ',','\\');
            stTrePayFileInfo.totalnum = atol(cTmp);
            
            //LOG(LM_DEBUG, Fmtmsg("%s---%d---%.2f", stTrePayFileInfo.ofyear, stTrePayFileInfo.totalnum, stTrePayFileInfo.totalamt), "INFO")
            
            /**登记文件信息表**/
            memset(cErrMsg, 0x00, sizeof(cErrMsg));
            iRet = DBInsert("tips_trepayfileinfo", SD_TIPS_TREPAYFILEINFO, NUMELE(SD_TIPS_TREPAYFILEINFO), &stTrePayFileInfo, cErrMsg);
            if(0 > iRet)
            {
                fclose(fp);
                fp = NULL;
                DCIRollback();
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("新增集中支付文件信息失败"),
                fpub_GetCompname(lXmlhandle))
            }
        }
        else
        {
            memset(&stTrePayFileDetail, 0x00, sizeof(stTrePayFileDetail));
            
            /**获取日期**/
            pstrcopy(stTrePayFileDetail.trandate, stTrePayFileInfo.trandate, sizeof(stTrePayFileDetail.trandate));
    
            /**获取流水**/
            stTrePayFileDetail.transeq = stTrePayFileInfo.transeq;
            
            /**获取序号**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 1, cTmp, ',','\\');
            stTrePayFileDetail.seqno = atol(cTmp);
            
            /**获取预算单位代码**/
            GetListbyDiv(cBuf, 2, stTrePayFileDetail.bdgorgcode,  ',','\\');
            
            /**获取功能科目代码**/
            GetListbyDiv(cBuf, 3, stTrePayFileDetail.funcsbtcode,  ',','\\');
            
            /**获取经济科目代码**/
            GetListbyDiv(cBuf, 4, stTrePayFileDetail.ecnomicsubjectcode,  ',','\\');
            
            /**获取金额**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 5, cTmp, ',','\\');
            stTrePayFileDetail.amt = atof(cTmp);
            dTotalAmt +=stTrePayFileDetail.amt;
            
            /**获取帐户性质**/
            GetListbyDiv(cBuf, 6, stTrePayFileDetail.acctprop,  ',','\\');
            
            /**登记明细表**/
            memset(cErrMsg, 0x00, sizeof(cErrMsg));
            iRet = DBInsert("tips_trepayfiledetail", SD_TIPS_TREPAYFILEDETAIL, NUMELE(SD_TIPS_TREPAYFILEDETAIL), &stTrePayFileDetail, cErrMsg);
            if(0 > iRet)
            {
                fclose(fp);
                fp = NULL;
                DCIRollback();
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("新增集中支付明细信息失败"),
                fpub_GetCompname(lXmlhandle))
            }
        }
    }
    fclose(fp);
    fp = NULL;
    /**读取文件信息&登记文件信息到表----END**/
    
    /**文件总笔数校验**/
    if (lFileLine - 1 != stTrePayFileInfo.totalnum)
    {
        DCIRollback();
        LOG(LM_STD, Fmtmsg("文件总笔数不一致"), "ERROR")  
        fpub_SetMsg(lXmlhandle, 100001, Fmtmsg("文件总笔数不一致"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;  
    }
    
    /**文件总金额校验**/
    if (dTotalAmt - stTrePayFileInfo.totalamt < -0.01 || dTotalAmt - stTrePayFileInfo.totalamt > 0.01)
    {
        DCIRollback();
        LOG(LM_STD, Fmtmsg("文件总金额不一致"), "ERROR")  
        fpub_SetMsg(lXmlhandle, 100001, Fmtmsg("文件总金额不一致"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;  
    }
    
    /**数据提交**/
    if (0 > DCICommit())
    {
        DCIRollback();
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")  
        fpub_SetMsg(lXmlhandle, 100001, Fmtmsg("提交数据库失败"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;     
    }
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TREPAY_INDB...处理结束"), "INFO")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}