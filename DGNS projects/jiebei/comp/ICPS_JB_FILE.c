#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "../incl/ICPS_JB_HEAD.h"

IRESULT ICPS_SFTP_GETFILE(HXMLTREE lXmlhandle)
{
    char sBuf[10000];
    char sDate[8 + 1];
    char sPath[40 + 1];
	char sPath_o[40 + 1];
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
	ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, sPath_o,"GXP存储目录");
    LOG(LM_DEBUG, Fmtmsg("业务编号[%s]本地存储目录[%s]GXP存储目录[%s]", sBusi_No, sPath,sPath_o), "DEBUG");

    if (0 == strcmp(sBusi_No, "jiebei") || 0 == strcmp(sBusi_No, "jintiao"))
    {
        iRet = ffunc_getfile_to_local(lXmlhandle, sDate,sBusi_No, sPath,sPath_o);
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
