#include <math.h>
#include <dirent.h>

#define SOCOMPBUILDNO BUILDDATETIME#define SOCOMPVERSION "V1.0.0"
#include "DCI.h"
#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include "../tbh64/ICPS_DS_ACCOUNTING_FLOW_DIFF.h"

#define PRECISION 0.00001

IRESULT ICPS_SFTP_GETFILE(HXMLTREE lXmlhandle)
{
    char sBuf[10000];
    char sDate[8 + 1];
    char sPath[40 + 1];
    char sBusi_No[20];
    int iRet = -1;
    int iParas = 0;

    /*初始化组件*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(3)

    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sDate, "文件所在文件夹日期");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sBusi_No, "业务编号");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, sPath, "本地存储目录");
    LOG(LM_DEBUG, Fmtmsg("业务编号[%s]本地存储目录[%s]", sBusi_No, sPath), "DEBUG");

    if (0 == strcmp(sBusi_No, "jiebei") || 0 == strcmp(sBusi_No, "jintiao"))
    {
        iRet = ffunc_getfile_to_local(lXmlhandle, sDate,sBusi_No, sPath);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("暂不支持的业务"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "暂不支持的业务");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*TODO:把文件名称赋值到xml节点*/
    iRet = ffunc_getfilename_to_xml(lXmlhandle, sBusi_No, sPath);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_FILE_PRE_CHECK
组件名称:ICPS_FILE_PRE_CHECK
组件功能: 文件预处理
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_FILE_PRE_CHECK(HXMLTREE lXmlhandle)
{
    char sBuf[10000];
    int iRet = -1;
    int iParas = 0;

    PARA_FILEPRECHK st_para_fileprechk;
    /*初始化组件*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(4)

    memset(&st_para_fileprechk, 0x00, sizeof(st_para_fileprechk));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_fileprechk.date, "文件所在文件夹日期");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_fileprechk.busi_no, "业务编号");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, st_para_fileprechk.bank_id, "本行代码");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, st_para_fileprechk.path, "本地存储目录");
    LOG(LM_DEBUG,
            Fmtmsg("文件所在文件夹日期[%s]业务编号[%s]本行代码[%s]本地存储目录[%s]", st_para_fileprechk.date, st_para_fileprechk.busi_no,
                    st_para_fileprechk.bank_id, st_para_fileprechk.path), "DEBUG");

    if (0 == strcmp(st_para_fileprechk.busi_no, "wbank"))
    {
        iRet = ffunc_file_pre_check(lXmlhandle, st_para_fileprechk);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("暂不支持的业务"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "暂不支持的业务");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_FILE_INFO_INIT
组件名称:ICPS_FILE_INFO_INIT
组件功能: 初始化文件管理信息
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_FILE_INFO_INIT(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];

    PARA_FILEINFOINIT st_para_fileinfoinit;

    /*初始化组件*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    memset(&st_para_fileinfoinit, 0, sizeof(st_para_fileinfoinit));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_fileinfoinit.busi_date, "业务日期");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_fileinfoinit.busi_no, "业务编号");
    LOG(LM_STD, Fmtmsg("业务日期=[%s],业务编号=[%s]", st_para_fileinfoinit.busi_date, st_para_fileinfoinit.busi_no), "INFO");

    if (0 == strcmp(st_para_fileinfoinit.busi_no, "jiebei"))
    {
        iRet = ffunc_init_jiebei_file_info(lXmlhandle, st_para_fileinfoinit);
    }
    else if (0 == strcmp(st_para_fileinfoinit.busi_no, "jintiao"))
    {
        iRet = ffunc_init_jintiao_file_info(lXmlhandle, st_para_fileinfoinit);
    }
    else if (0 == strcmp(st_para_fileinfoinit.busi_no, "wbank"))
    {
        LOG(LM_STD, Fmtmsg("函数:ICPS_FILE_INFO_INIT"), "ERROR")
        iRet = ffunc_init_wbank_file_info(lXmlhandle, st_para_fileinfoinit);
    }
    else
    {
        LOG(LM_STD, Fmtmsg("暂不支持的业务"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "暂不支持的业务");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_CHK_FILE_INS
组件名称:ICPS_CHK_FILE_INS
组件功能: 对账明细文件入库
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_CHK_FILE_INS(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    int fileins_status = -1;

    FILE *fp = NULL;

    PARA_CHKFILEINS st_para_chkfileins;

    memset(&st_para_chkfileins, 0, sizeof(st_para_chkfileins));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_chkfileins.busi_date, "业务日期");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_chkfileins.busi_no, "业务编号");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, st_para_chkfileins.file_type, "文件类型");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, st_para_chkfileins.file_path, "文件路径");

    LOG(LM_STD,
            Fmtmsg("业务日期=[%s],业务编号=[%s],文件类型=[%s]\n文件路径=[%s]", st_para_chkfileins.busi_date, st_para_chkfileins.busi_no,
                    st_para_chkfileins.file_type, st_para_chkfileins.file_path), "INFO");

    /*借呗，金条打开对账文件，并入库*/
    if (0 == strcmp(st_para_chkfileins.busi_no, "jiebei") || 0 == strcmp(st_para_chkfileins.busi_no, "jintiao"))
    {
        if ((fp = fopen(st_para_chkfileins.file_path, "r")) == NULL)
        {
            LOG(LM_STD, Fmtmsg("打开对账文件失败[%s]", st_para_chkfileins.file_path), "ERROR");
            fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "文件打开失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if (0 == strcmp(st_para_chkfileins.busi_no, "jiebei"))
        {
            iRet = ffunc_parse_jiebei_file_to_db(lXmlhandle, fp, st_para_chkfileins);
        }
        else if (0 == strcmp(st_para_chkfileins.busi_no, "jintiao"))
        {
            iRet = ffunc_parse_jintiao_file_to_db(lXmlhandle, fp, st_para_chkfileins);
        }
    }
    else if (0 == strcmp(st_para_chkfileins.busi_no, "wbank"))
    {
        LOG(LM_STD, Fmtmsg("开始处理文件[%s]", st_para_chkfileins.busi_no), "INFO")
        iRet = ffunc_parse_wbank_file_to_db(lXmlhandle, st_para_chkfileins);
    }
    else
    {
        if (fp)
        {
            fclose(fp);
            fp = NULL;
        }
        LOG(LM_STD, Fmtmsg("暂不支持的业务"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "暂不支持的业务");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if (0 > iRet)
    {
        if (fp)
        {
            fclose(fp);
            fp = NULL;
        }
        LOG(LM_STD, Fmtmsg("对账文件入库失败iRet[%d]", iRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "文件入库失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (fp)
    {
        fclose(fp);
        fp = NULL;
    }

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
动态组件函数定义
组件函数名称:ICPS_JIEBEI_CHKSUM
组件名称:ICPS_JIEBEI_CHKSUM
组件功能: 蚂蚁借呗对总账
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_JIEBEI_CHKSUM(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
    char sBuf[255];
    char sBusi_Date[8 + 1];

    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(1)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sBusi_Date, "业务日期");

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_JINTIAO_CHKSUM
组件名称:ICPS_JINTIAO_CHKSUM
组件功能: 京东金条对总账
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_JINTIAO_CHKSUM(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
    char sBuf[255];
    char sBusi_Date[8 + 1];

    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(1)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sBusi_Date, "业务日期");

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_WBANK_CHKSUM
组件名称:ICPS_WBANK_CHKSUM
组件功能:T-1日尾差清算
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_WBANK_CHKSUM(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
    char sBuf[256];
    char sErrmsg[256];
    char sBusi_Date[8 + 1];
    char sClear_Date[8 + 1];
	char sDiff_Node[128]; /**尾差存放节点**/
    char sSqlStr[1024];

    double provisions_bal = 0.00;
    double position_bal = 0.00;
    double trans_total_amt = 0.00;
    double sum_diff_amt = 0.00; /*尾差汇总*/
    double interest_amt = 0.00; /*当日结息金额*/
    double daily_diff_amt; /*日终差额*/
	double ds_split_diff_T; /**T+1日和T日A01类应调整金额**/
	double ds_split_diff_T2; /**A02类应调整金额**/
	double ds_split_diff_B1; /**B01类应调整金额**/
	double ds_split_diff_G1; /**G01类应调整金额**/
    //double diff_range; /*日终差异范围*/
	
	ICPS_DAILY_TC_DIFF icps_daily_tc_diff;
	memset(&icps_daily_tc_diff, 0x00, sizeof(icps_daily_tc_diff));
	
    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(2)
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sClear_Date, "清算日期");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sBusi_Date, "业务日期");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, sDiff_Node, "尾差存放节点");
    LOG(LM_DEBUG, Fmtmsg("业务日期[%s]", sBusi_Date), "");
    LOG(LM_DEBUG, Fmtmsg("清算日期[%s]", sClear_Date), "");
    LOG(LM_DEBUG, Fmtmsg("尾差存放节点[%s]", sDiff_Node), "");

	pstrcopy(icps_daily_tc_diff.busi_date, sBusi_Date, sizeof(icps_daily_tc_diff.busi_date));
	pstrcopy(icps_daily_tc_diff.clear_date, sClear_Date, sizeof(icps_daily_tc_diff.clear_date));

    ICPS_GETXMLNODE_DOUBLE("/icps/req/provisions_bal", provisions_bal, "备付金当日余额");
    ICPS_GETXMLNODE_DOUBLE("/icps/req/position_bal", position_bal, "影子账户余额");
    /**ICPS_GETXMLNODE_DOUBLE("/icps/req/trans_total_amt", trans_total_amt, "账务发生额");取消账务发生额---modify by wl 20180515**/
    LOG(LM_DEBUG, Fmtmsg("备付金当日余额[%.2f],影子账户余额[%.2f],账务发生额[%.2f]", provisions_bal, position_bal, trans_total_amt), "");
  //  ICPS_GETXMLNODE_DOUBLE("/icps/cskz/diff_range", diff_range, "日终差异范围");
	icps_daily_tc_diff.total_bal=position_bal;
	icps_daily_tc_diff.reserve_bal=provisions_bal;
	
    memset(sSqlStr, 0, sizeof(sSqlStr));
    snprintf(sSqlStr, sizeof(sSqlStr),
           /** "SELECT NVL(SUM(ERROR_AMT),0) AS SUM_DIFF_AMT FROM (SELECT CASE WHEN ERROR_TYPE='D01' AND TRANS_TYPE='D' THEN 0-ERROR_AMT ELSE ERROR_AMT END AS ERROR_AMT FROM ICPS_WB_DS_SPLIT_DIFF WHERE BUSI_DATE='%s')",**/
			 "select NVL(SUM(ERROR_AMT),0) AS SUM_DIFF_AMT from (select case when a.trans_type in ('C','DR') then a.ERROR_AMT when a.trans_type='D' then -a.ERROR_AMT end as ERROR_AMT from ICPS_WB_DS_SPLIT_DIFF a where a.busi_date='%s' and  a.trans_type in('C','DR','D') and a.error_type='D01')", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("统计尾差调整总金额[%s]", sSqlStr), "DEBUG");

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    trim(sBuf);
    sum_diff_amt = atof(sBuf);
	icps_daily_tc_diff.t_bal=sum_diff_amt;
    LOG(LM_DEBUG, Fmtmsg("尾差调整总金额[%s][%f]", sBuf, sum_diff_amt), "DEBUG");

	/**计算T日和T+1日A01类应调整金额**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where  busi_date in (to_char((to_date('%s','yyyymmdd')+1 days),'yyyymmdd'),'%s') and ERROR_TYPE='A01'",
			sBusi_Date, sBusi_Date);
	
    LOG(LM_DEBUG, Fmtmsg("A01类应调整金额[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_T=atof(sBuf);
	icps_daily_tc_diff.reserve_diff=ds_split_diff_T;
    LOG(LM_DEBUG, Fmtmsg("统计A01金额[%f]",ds_split_diff_T ), "DEBUG");

	/**T日的DS_SPLIT_DIFF表中的A02类应调整金额汇总**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where ERROR_TYPE='A02' and busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("A02类应调整金额[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_T2=atof(sBuf);
	icps_daily_tc_diff.financial_diff=ds_split_diff_T2;
    LOG(LM_DEBUG, Fmtmsg("统计A02金额[%f]",ds_split_diff_T2 ), "DEBUG");

	/**T日的DS_SPLIT_DIFF表中的B01类应调整金额汇总**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where ERROR_TYPE='B01' and busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("B01类应调整金额[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_B1=atof(sBuf);
	icps_daily_tc_diff.person_diff=ds_split_diff_B1;
    LOG(LM_DEBUG, Fmtmsg("统计B01金额[%f]",ds_split_diff_B1 ), "DEBUG");

	/**T日的DS_SPLIT_DIFF表中的G01类应调整金额汇总**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select NVL(sum(ERROR_AMT), 0) from ICPS_WB_DS_SPLIT_DIFF where ERROR_TYPE='G01' and busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("G01类应调整金额[%s]", sSqlStr), "DEBUG");
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	trim(sBuf);
	ds_split_diff_G1=atof(sBuf);
	icps_daily_tc_diff.overplay_diff=ds_split_diff_G1;
    LOG(LM_DEBUG, Fmtmsg("统计G01金额[%f]",ds_split_diff_G1 ), "DEBUG");

	/**统计当天结息金额**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    snprintf(sSqlStr, sizeof(sSqlStr),
            "SELECT NVL(AMOUNT,0) FROM ICPS_WB_RSS_OTHER_DETAIL WHERE SUBSTR(BUSI_DATE,5,4) IN('0321','0621','0921','1221') AND DATA_TYPE='1' AND MEMO=''"); LOG(LM_DEBUG, Fmtmsg("统计结息金额[%s]", sSqlStr), "DEBUG");

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    trim(sBuf);
    interest_amt = atof(sBuf);
	icps_daily_tc_diff.interest_diff=interest_amt;
    LOG(LM_DEBUG, Fmtmsg("结息金额[%f]", interest_amt), "DEBUG");

    daily_diff_amt = position_bal  - provisions_bal - sum_diff_amt - ds_split_diff_T - ds_split_diff_T2 - ds_split_diff_B1 - ds_split_diff_G1 + interest_amt;
	daily_diff_amt=fabs(daily_diff_amt);
	icps_daily_tc_diff.daily_diff=daily_diff_amt;
    LOG(LM_DEBUG, Fmtmsg("日终差额[%f]", daily_diff_amt), "DEBUG");
   
   	memset(sErrmsg, 0x00, sizeof(sErrmsg));
   	iRet = APP_DBInsert("ICPS_DAILY_TC_DIFF", SD_ICPS_DAILY_TC_DIFF, NUMELE(SD_ICPS_DAILY_TC_DIFF), &icps_daily_tc_diff, sErrmsg);     
	if (iRet < 0)
    {
	    LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
	    return iRet;
	 }   
   	if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("数据库提交失败,sqlerr[%s]", DCILastError()), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
       	return -1;
   	}
	
    memset(sBuf, 0, sizeof(sBuf));
	sprintf (sBuf, "%.2f", daily_diff_amt);
	trim(sBuf);
	COMP_HARDSETXML(sDiff_Node,sBuf);
	/**
	if (fabs(daily_diff_amt - diff_range) > PRECISION)
	{
        LOG(LM_STD, Fmtmsg("尾差过大"), "ERROR")
		COMP_HARDSETXML("/pub/diff_range", "1");
	}
    else
	{
        LOG(LM_STD, Fmtmsg("尾差在可控范围内"), "ERROR")
		COMP_HARDSETXML("/pub/diff_range", "0");
	}***/
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:ICPS_WBANK_TOTAL_CHECK
组件名称:ICPS_WBANK_DETAIL_CHECK
组件功能: 微粒贷明细检查对账
组件参数:
 序号 参数类型  参数名称                资源类别         缺省值           可空  参数说明
  1   1-输入   明细文件名               XML解析字符串                      N    明细文件名
使用限制:
程 序 员:
发布日期:2009年12月11日
修改日期:
参数使用示例:
************************************************************************/
IRESULT ICPS_WBANK_TOTAL_CHECK(HXMLTREE lXmlhandle)
{
    int iParas = -1;
    int iRet = -1;
	int iDr_status= 0;
	int iCr_status= 0;
	int iDcount = 0; /**借方明细汇总笔数**/
	int iCcount = 0; /**贷方笔数**/
    char sBuf[1024];
    char sErrmsg[256];
    char sBusi_Date[8 + 1]; /**业务日期**/
    char sBusi_No[16 + 1]; /**业务种类**/
    char sSqlStr[1024];
    char sSqlStr2[1024];
	char sSubject[40];/**科目号**/
	char sZje1[40];
	char sZje2[40];
	char sTmp[128];
	double dDr_amt;/**贷方发生额汇总**/
	double dCr_amt;/**借方发生额汇总**/
	double dDr_pmt;/**当日贷方发生额**/
	double dCr_pmt;/**当日借方发生额**/

	ICPS_DS_ACCOUNTING_FLOW_DIFF  ds_accounting_flow_diff;
    ICPS_WB_TM_GL_BAL tm_gl_bal;
	
	int iNum=0; /**汇总条数**/
	int iSucc_flag= 0; /**0成功，1失败**/
	CURSOR cur;
    
    /*初始化组件*/
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    /*检查入参个数*/
    COMP_PARACOUNTCHKMIN(2)

    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, sBusi_Date, "业务日期");
	trim(sBusi_Date);
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, sBusi_No, "业务种类");
	trim(sBusi_No);
    LOG(LM_DEBUG, Fmtmsg("业务日期[%s]", sBusi_Date), "");
    LOG(LM_DEBUG, Fmtmsg("业务种类[%s]", sBusi_No), "");
	
	/**科目核对**/
    memset(sSqlStr, 0, sizeof(sSqlStr));
    memset(sBuf, 0, sizeof(sBuf));
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    LOG(LM_DEBUG, Fmtmsg("1-[%s]", sBusi_Date), "");
    snprintf(sSqlStr, sizeof(sSqlStr),
			"select subject,db_amt,db_count,cr_amt,cr_count,bank_group_id,product_cd from ICPS_WB_TM_GL_BAL	where busi_date='%s'", sBusi_Date);
    LOG(LM_DEBUG, Fmtmsg("sSqlStr[%s]", sSqlStr), "");
	if(cur = DCIDeclareCursor(sSqlStr, DCI_STMT_LOCATOR) == -1)
	{
		 LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
		 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		 fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		 return COMPRET_FAIL;
    }
	 if (DCIExecute(cur) == -1)
    {
         LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
	     DCIFreeCursor(cur);
	     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
	     return COMPRET_FAIL;
	}
    LOG(LM_DEBUG, Fmtmsg("2[%s]", sBusi_Date), "");
	while(1 == DCIFetch2(cur,DCI_FETCH_NEXT,0))
    {
   		 LOG(LM_DEBUG, Fmtmsg("3[%s]", sBusi_Date), "");
		 iDr_status= 0;
		 iCr_status= 0;
		 iDcount = 0; 
	 	 iCcount = 0;
	     memset(&tm_gl_bal, 0x00, sizeof(tm_gl_bal));
		 memset(&ds_accounting_flow_diff, 0x00, sizeof(&ds_accounting_flow_diff));
		 /**科目**/
         strncpy(tm_gl_bal.subject,DCIFieldAsString(cur,0),sizeof(tm_gl_bal.subject));
   		 LOG(LM_DEBUG, Fmtmsg("subject[%s]", tm_gl_bal.subject), "");
		 /**借方发生额**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp, DCIFieldAsString(cur,1), sizeof(sTmp));
		 trim(sTmp);
   		 LOG(LM_DEBUG, Fmtmsg("sTmp[%s]", sTmp), "");
         tm_gl_bal.db_amt=atof(sTmp);
   		 LOG(LM_DEBUG, Fmtmsg("db_amt[%.2f]", tm_gl_bal.db_amt), "");
         /**借方笔数**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp,DCIFieldAsString(cur,2), sizeof(sTmp));
		 trim(sTmp);
         tm_gl_bal.db_count=atoi(trim(sTmp));
   		 LOG(LM_DEBUG, Fmtmsg("db_count[%d]", tm_gl_bal.db_count), "");
		 /**贷方发生额**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp,DCIFieldAsString(cur,3), sizeof(sTmp));
		 trim(sTmp);
         tm_gl_bal.cr_amt=atof(sTmp);
   		 LOG(LM_DEBUG, Fmtmsg("cr_amt[%.2f]", tm_gl_bal.cr_amt), "");
		 /**贷方笔数**/
		 memset(sTmp, 0x00, sizeof(sTmp));
         strncpy(sTmp,DCIFieldAsString(cur,4), sizeof(sTmp));
		 trim(sTmp);
         tm_gl_bal.cr_count=atoi(trim(sTmp));
   		 LOG(LM_DEBUG, Fmtmsg("cr_count[%d]", tm_gl_bal.cr_count), "");
		 /**银团编号**/
         strncpy(tm_gl_bal.bank_group_id,DCIFieldAsString(cur,5),sizeof(tm_gl_bal.bank_group_id));
   		 LOG(LM_DEBUG, Fmtmsg("bank_group_id[%s]", tm_gl_bal.bank_group_id), "");
		 /**产品代码**/
         strncpy(tm_gl_bal.product_cd,DCIFieldAsString(cur,6),sizeof(tm_gl_bal.product_cd));
   		 LOG(LM_DEBUG, Fmtmsg("tm_gl_bal.product_cd[%s]", tm_gl_bal.product_cd), "");
		 /**统计会计日报表当日发生额汇总**/
		 /**今日贷方余额=昨日贷方余额-今日贷方发生额 \
		  	今日借方余额=昨日借方余额+今日借方发生额 \
			今日贷方发生额=今日贷方发生额蓝字-今日贷方发生额红字\
			今日借方发生额=今日借方发生额蓝字-今日借方发生额红字***/

		/**核对借方发生额**/
		iDr_status = ffunc_mxzz_check(lXmlhandle, tm_gl_bal, sBusi_Date, "D", &dDr_amt, &iDcount);
		if (0 == iDr_status)
		{
			DCIFreeCursor(cur);
    		LOG(LM_DEBUG, Fmtmsg("核对借方发生额失败!"), "");
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		}
		/**核对贷方发生额**/
		iCr_status = ffunc_mxzz_check(lXmlhandle, tm_gl_bal, sBusi_Date, "C",  &dCr_amt, &iCcount);
		if (0 == iCr_status)
		{	
			DCIFreeCursor(cur);
    		LOG(LM_DEBUG, Fmtmsg("核对贷方发生额失败!"), "");
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		}
		sprintf (ds_accounting_flow_diff.dr_check_flag,"%d", iDr_status);
		sprintf (ds_accounting_flow_diff.cr_check_flag,"%d", iCr_status);
		ds_accounting_flow_diff.db_tcnt = tm_gl_bal.db_count;
		ds_accounting_flow_diff.cr_tcnt = tm_gl_bal.cr_count;
		ds_accounting_flow_diff.db_count = iDcount;
		ds_accounting_flow_diff.cr_count = iCcount;

		pstrcopy(ds_accounting_flow_diff.busi_date, sBusi_Date, sizeof(ds_accounting_flow_diff.busi_date));
		pstrcopy(ds_accounting_flow_diff.subject,tm_gl_bal.subject, sizeof(ds_accounting_flow_diff.subject));
		pstrcopy(ds_accounting_flow_diff.busi_no, sBusi_No, sizeof(ds_accounting_flow_diff.busi_no));
		pstrcopy(ds_accounting_flow_diff.product_cd, tm_gl_bal.product_cd, sizeof(ds_accounting_flow_diff.product_cd));
		pstrcopy(ds_accounting_flow_diff.bank_group_id, tm_gl_bal.bank_group_id, sizeof(ds_accounting_flow_diff.bank_group_id));
		ds_accounting_flow_diff.db_amt=dDr_amt;
		ds_accounting_flow_diff.cr_amt=dCr_amt;
		ds_accounting_flow_diff.db_pmt=tm_gl_bal.db_amt;
		ds_accounting_flow_diff.cr_pmt=tm_gl_bal.cr_amt;

    	memset(sErrmsg, 0x00, sizeof(sErrmsg));
     	iRet = APP_DBInsert("ICPS_DS_ACCOUNTING_FLOW_DIFF", SD_ICPS_DS_ACCOUNTING_FLOW_DIFF, NUMELE(SD_ICPS_DS_ACCOUNTING_FLOW_DIFF), &ds_accounting_flow_diff, sErrmsg);     
		if (iRet < 0)
	    {
		    LOG(LM_STD, Fmtmsg("数据库操作失败,sqlerr[%s]", DCILastError()), "ERROR")
		    DCIRollback();
			DCIFreeCursor(cur);
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
		    return iRet;
		 }   
    
    	if (DCICommit() != MID_SYS_SUCC)
        {
            LOG(LM_STD, Fmtmsg("数据库提交失败,sqlerr[%s]", DCILastError()), "ERROR")
	        DCIRollback();
			DCIFreeCursor(cur);
	     	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	     	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        	return -1;
    	}
	    if (iDr_status != 1 || iCr_status != 1)
		{
			iSucc_flag++;
		}
	}
	DCIFreeCursor(cur);
	if (iSucc_flag == 0)
	{
		COMP_HARDSETXML("/icps/req/chkstatus", "0"); 
	}
	else
	{
		COMP_HARDSETXML("/icps/req/chkstatus", "1"); 
		
	}
  	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   	return COMPRET_SUCC;

}	

/************************************************************************
动态组件函数定义
函数名称: ICPS_WB_CAV_INS
名称: 微粒贷核销文件入库
 
组件功能: 微粒贷核销文件入库
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT ICPS_WB_CAV_INS(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sCAVFile[255+1];      /*文件名（带路径）*/
  char sSignDate[8+1];       /*登记日期*/
  double dLoanInitPrin=0.00;		 /*借据本金*/

  ICPS_WB_CAV_INFO icps_wb_cav_info;

  FILE *fp;

  int incnt=0;                  /*已入笔数*/
 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sCAVFile, 0x00, sizeof(sCAVFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "文件名（带路径）");
  trim(sBuffer);
  pstrcopy(sCAVFile,sBuffer,sizeof(sCAVFile));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "登记日期");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  LOG(LM_STD, Fmtmsg("微粒贷核销文件[%s],登记日期[%s]", sCAVFile, sSignDate), fpub_GetCompname(lXmlhandle)); 


  if(strlen(sCAVFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "微粒贷核销文件名不能为空");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("文件名不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  fp = fopen(sCAVFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "微粒贷核销文件打开失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("打开文件%s失败",sCAVFile), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

  DCIBegin();
  //明细入库
  while( !feof(fp) )
  {
		memset(&icps_wb_cav_info, 0x00, sizeof(icps_wb_cav_info));
		memset(sBuffer, 0x00, sizeof(sBuffer));     
		fgets(sBuffer, sizeof(sBuffer), fp);
		if( strlen(trim(sBuffer)) <= 0 )
		   continue;
		
		incnt++;
		
		/*1-CNC客户ID*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,1,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.CUST_ID,sTmp,sizeof(icps_wb_cav_info.CUST_ID)-1);
		
		/*2-逻辑卡号*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,2,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.LOGICAL_CARD_NO,sTmp,sizeof(icps_wb_cav_info.LOGICAL_CARD_NO)-1);
		if(strlen(icps_wb_cav_info.LOGICAL_CARD_NO) == 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "逻辑卡号不能为空"), "INFO" );
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "逻辑卡号不能为空");
			break;
		}
	 
		/*3-产品号*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,3,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.PRODUCT_CD,sTmp,sizeof(icps_wb_cav_info.PRODUCT_CD)-1);
		
		/*4-借据号(交易参考号)*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,4,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.REF_NBR,sTmp,sizeof(icps_wb_cav_info.REF_NBR)-1);
		if(strlen(icps_wb_cav_info.REF_NBR) == 0)
		{
			 iResult = -1;
		   LOG( LM_DEBUG, Fmtmsg( "借据号(交易参考号)不能为空"), "INFO" );
		   fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "借据号(交易参考号)不能为空");
		   break;
		}
		
		/*5-借据本金*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,5,sTmp,',','\\');
   	dLoanInitPrin = atof(sTmp);
   	icps_wb_cav_info.LOAN_INIT_PRIN=dLoanInitPrin;
   	
		/*6-银团号*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,6,sTmp,',','\\');
		trim(sTmp);
		memcpy(icps_wb_cav_info.BANK_GROUP_ID,sTmp,sizeof(icps_wb_cav_info.BANK_GROUP_ID)-1);
		
		/*文件中无，但数据库中需要*/
		/*BUSI_DATE-业务日期*/
		memcpy(icps_wb_cav_info.BUSI_DATE,sSignDate,sizeof(icps_wb_cav_info.BUSI_DATE)-1);
		
		/*入表*/
		LOG(LM_STD,Fmtmsg("incnt=[%d],Insert,LOGICAL_CARD_NO=[%s],REF_NBR=[%s]", incnt, icps_wb_cav_info.LOGICAL_CARD_NO, icps_wb_cav_info.REF_NBR),"ERROR")
		memset(sTmp,0x00,sizeof(sTmp));
//		iRet = DBInsert( "ICPS_WB_CAV_INFO", SD_ICPS_WB_CAV_INFO, NUMELE( SD_ICPS_WB_CAV_INFO ), &icps_wb_cav_info,sTmp);
		iRet = APP_DBInsert("ICPS_WB_CAV_INFO", SD_ICPS_WB_CAV_INFO, NUMELE(SD_ICPS_WB_CAV_INFO), &icps_wb_cav_info,sTmp);
		if( iRet < 0 )
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "入库微粒贷核销信息表 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "入库微粒贷核销信息表");
			break;   
		}
  }

  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }    
  
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "提交时错误信息=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "事务提交报错");
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
函数名称: ICPS_WB_CAV_PRE
名称: 微粒贷核销文件预检查
 
组件功能: 微粒贷核销文件预检查
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT ICPS_WB_CAV_PRE(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sFilePath[255+1];      /*指定路径*/
  char sNameString[255+1];      /*指定路径*/
  char sFileExistXML[255+1];      /*指定路径*/
  DIR *dirp;
  struct dirent *dp;
  char sFilesName[1024]={0};
  int iFileExistNum=0;
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sFilePath, 0x00, sizeof(sFilePath));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "指定路径");
  trim(sBuffer);
  pstrcopy(sFilePath,sBuffer,sizeof(sFilePath));
  
  memset(sNameString, 0x00, sizeof(sNameString));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "文件名所包含字符串");
  trim(sBuffer);
  pstrcopy(sNameString,sBuffer,sizeof(sNameString));
  
  memset(sFileExistXML, 0x00, sizeof(sFileExistXML));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "存在文件个数存放节点");
  trim(sBuffer);
  pstrcopy(sFileExistXML,sBuffer,sizeof(sFileExistXML));
  
  LOG(LM_STD, Fmtmsg("指定路径[%s],存在文件个数存放节点[%s]", sFilePath, sFileExistXML), fpub_GetCompname(lXmlhandle)); 

  if(strlen(sFilePath) == 0)
  {
    fpub_SetMsg(lXmlhandle, MID_SYS_OPENFILE, "指定路径不能为空");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    LOG(LM_STD, Fmtmsg("指定路径不能为空！"), fpub_GetCompname(lXmlhandle))
    return COMPRET_FAIL ;
  }
  
  if(strlen(sNameString) == 0)
  {
    pstrcopy(sNameString,".zip",sizeof(sNameString));
  }
  LOG(LM_STD, Fmtmsg("文件名所包含字符串[%s]", sNameString), fpub_GetCompname(lXmlhandle)); 
  dirp = opendir(sFilePath);
  while((dp=readdir(dirp)) != NULL)
  {
    strcat(sFilesName,dp->d_name);
    strcat(sFilesName,"|");
    if(strstr(dp->d_name,sNameString) != NULL )
    {
      LOG(LM_STD, Fmtmsg("存在核销文件[%s]", dp->d_name), fpub_GetCompname(lXmlhandle));
      iFileExistNum += 1;
    }
  }
  LOG(LM_STD, Fmtmsg("文件名[%s]", sFilesName), fpub_GetCompname(lXmlhandle));
  closedir(dirp);
  COMP_HARDSETXML(sFileExistXML, itoa(iFileExistNum));
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}

