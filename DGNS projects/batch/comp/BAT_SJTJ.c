/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_SJTJ.ec
文件描述:提交核心文件生成
程 序 员:YangDong
发布日期:20110801

程 序 员:YangDong
修改日期:20141018
修改说明:DCI改造

*********************************************************************/
#include "gaps_head.h"
#include "app_head.h"
#include "batch_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_SJTJ.so</soname>\
        <sosrcname>BAT_SJTJ.c</sosrcname>\
        <sonote>BATCH数据提交组件集合</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"YangDong\" filesize=\"1238198\">HS-AgentV2.1整理</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1238198\">DCI改造</rec>\
        </version>\
        </root>";
    printf("\n================动态组件基本信息================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" -->取详细信息失败...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" -->请查看详细信息...\n");
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_SJTJ
组件名称:BATCH_SJTJ
组件功能: 批量业务生成数据提交文件
组件参数:
 序号 参数类型  参数名称      资源类别     缺省值  可空  参数说明    
  1   1-输入    主机文件名    416XML解析字符串  *      N      
  2   1-输入    文件标识      416XML解析字符串  *      N    
  3   1-输入    映射标识      416XML解析字符串  *      N    
  4   1-输入    业务表名      416XML解析字符串  *      N    
使用限制:单明细文件格式
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_SJTJ(HXMLTREE lXmlhandle)
{
    char sMapID[40+1];
    char sYwbh[16+1];
    char sColID[32+1];
    char sFileID[32+1];
    char sSqlStr[4096];
    char sSjtjExpWhere[256];
    /* int iWjxh = 0;     文件序号 */
    /* int iZjszwz = 0;   主机上账位置 */

    int  iParas,iResult;
    char sBuf[1024];
    char linebuf[BATCH_MAX_FILELINE_BYTE];
    char outbuf[BATCH_MAX_FILELINE_BYTE];
    char sNode[128];
    char sTableName[40+1];
    char sFileBasicName[128];
    char sFileParsedName[128];
    char sFileBakName[128];
    char sFilePath[128];
    char sFileFullName[128];
    char sTmpFileFullName[128];
    char sTmpFileName[128];
    char sFileType[2+1];
    char sTotalBuf[BATCH_MAX_FILELINE_BYTE]; 
    char sPkrq[8+1];
    char sPtpch[8+1],sGetFlag[1+1];
    int  iTSortCount=0;
    int  i,iAbort=0,length=0;
    long lRCount=0;
    FILE *hostfp;
    FILE *srcfp;
    FILE *tmpfp;
    char sCondStr[1024];
    char sColStr[2048];  /* 提交后台映射字段 */
    int  lPgNum = 0;    /* 每主机文件最大记录数 */
    /* long lLsxh = 0;     流水序号 */
    int  iFileCount = 1;    /* 文件数 */
    int  iFileNum = 0;      /* 文件内记录数 */
    int  iTotalNum= 0;      /* 本批次记录数 */
    double dFileAmt= 0;     /* 文件内总金额 */
    double dTotalAmt = 0;   /* 本批次总金额 */

    CURSOR cur;
    char sErrmsg[512];
    int iRet = -1;

    int  iLsxh = 0;
    int  iPos = 0;

    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    BATCH_FILEMAP  sdb_batch_filemap;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(5)

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"主机文件名")
    pstrcopy(sFileBasicName,sBuf,sizeof(sFileBasicName)); 
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"文件标识")

    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJBS_NULL,MSG_BATCH_WJBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileID,sBuf,sizeof(sFileID));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"映射标识")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YSBS_NULL,MSG_BATCH_YSBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sMapID,sBuf,sizeof(sMapID));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"业务表名")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBM_NULL,MSG_BATCH_YWBM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(5,sBuf,"主机文件记录数限制")
    lPgNum = atol( sBuf );

    /* 批扣日期 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* 平台批次号 */
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
    /* 业务编号 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sYwbh,sBuf,sizeof(sYwbh));

    /* 文件类型 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILEFMT,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJLX_NULL,MSG_BATCH_WJLX_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sFileType,sBuf,sizeof(sFileType));
    
    /*数据提交导出WHERE条件*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSjtjExpWhere, 0x00, sizeof(sSjtjExpWhere));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_EXPWHERE, sBuf)
    if (sBuf[0] == '\0')
    {/*WHERE条件为空,未设置相关属性*/
        snprintf(sSjtjExpWhere, sizeof(sSjtjExpWhere), "AND shzt !='1' AND clzt='9' ");
    }else
    {
        snprintf(sSjtjExpWhere, sizeof(sSjtjExpWhere), "%s", StrReplace(sBuf, "#", "'"));
    }
    
    LOG(LM_DEBUG,Fmtmsg("BATCH: 文件类型[%s]，主机文件记录数限制[%d],expwhere[%s]", 
        sFileType, lPgNum, sSjtjExpWhere ),"DEBUG");

    /* 主机文件拆分时，需要控制重复提交情况 */
    /* 如果是重复提交,则只提交上送核心失败的文件 */
    /* 文件已经生成,不再写文件,为文件个数和文件起始序号赋值 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_SJTJ_SUBMIITED_WJXH, sBuf );
    if( atoi( sBuf ) >= 1 )
    {
        /* 文件已经提交过,不用再提交,从提交失败的文件序号开始提交 */
        LOG(LM_STD,Fmtmsg("重新提交核心,从文件序号[%s]以后开始", sBuf ),"INFO")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        /* 不生成文件，直接调起主机批扣交易 */
        return 0;
    }
    else
    {
        COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_SUBMIITED_WJXH, "0"  );
    }

    /* 文件名处理 */
    /* 主机文件保存位置 
    snprintf( sFilePath, sizeof( sFilePath ),\
        "%s/batch/zjwj", getenv("GAPSFILEDIR") );
    */
    memset(sFilePath, 0x00, sizeof(sFilePath));
    iRet = fprv_getBatchFilePath(lXmlhandle,sFilePath, sizeof(sFilePath));
    iRet = xml_DelElement( lXmlhandle, "/batch/sjtj/wjxx" );
    /* 文件序号，从1开始 */
    COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_WJXH , itoa( iFileCount ) );

    if( strlen( sFileBasicName ) < 1 ) 
    {
        if( lPgNum > 0 )  /* 文件需要拆分 */
            snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                        "%s_%s_%s_%d.req", sYwbh, sPkrq, sPtpch, iFileCount );
        else /* 文件不需要拆分 */
            snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                "%s_%s_%s.req", sYwbh, sPkrq, sPtpch );
    }

    /* 解析生成主机文件名( 配置信息可以带xml节点名 ) */
    if( strlen( sFileBasicName ) > 2 )
    {
        /* 保存文件名配置 */
        pstrcopy( sFileBakName, sFileBasicName, sizeof(sFileBasicName)); 
        LOG(LM_DEBUG,Fmtmsg("BATCH: 主机文件名称解析,[%s]=>",sFileBasicName),"DEBUG")
        /* 先解析XML变量 */
        if(xml_ParseXMLString(lXmlhandle,sFileBasicName,sizeof(sFileBasicName))==FAIL)
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,\
                        Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* 解析后文件名 */
        strcpy( sFileParsedName, sFileBasicName );
        /* 恢复文件名配置 */
        pstrcopy( sFileBasicName, sFileBakName, sizeof(sFileBasicName)); 
    }
    /* 文件全名 */
    snprintf( sFileFullName, sizeof( sFileFullName ),\
        "%s/%s",sFilePath, sFileParsedName );

    memset( sSqlStr,0x00, sizeof( sSqlStr ) );
    snprintf( sSqlStr, sizeof( sSqlStr ), "SELECT * FROM  batch_filemap\
        WHERE mapid='%s' AND zjszwz > 0 ORDER BY zjszwz",sMapID );

    if ((cur = DCIDeclareCursor(sSqlStr, DCI_STMT_LOCATOR)) == -1)
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
    /* 文件配置中列位置 */
    memset(sColStr,0,sizeof(sColStr));
    memset( &sdb_batch_filemap, 0x00, sizeof( BATCH_FILEMAP ) );
    iPos = 0;
    while( ( iRet = DBFetch(cur, SD_BATCH_FILEMAP, NUMELE(SD_BATCH_FILEMAP), &sdb_batch_filemap, sErrmsg ) ) > 0 )
    {
        iPos ++;
        memset( sColID, 0x00, sizeof( sColID ) );
        /*iZjszwz = sdb_batch_filemap.zjszwz;*/
        strcpy( sColID, sdb_batch_filemap.columnid );
        /* 在select字段中添加空值，保证导出文件字段数与文件配置匹配 */
        /* deleted 
        if( iPos < iZjszwz )
        {
            while( iZjszwz > iPos && iPos < BATCH_MAX_FILE_COL_NUM )
            {
                strcat( sColStr, " ''" );
                strcat( sColStr, "," );
                iPos++;
            }
        }
        */
        trim( sColID );
        strcat( sColStr, sColID );
        strcat( sColStr, "," );
        memset( &sdb_batch_filemap, 0x00, sizeof( BATCH_FILEMAP ) );
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 去最后一个 , */
    sColStr[strlen( sColStr ) - 1 ] = '\0';
    
    /* 明细提交标志 */
    memset( sGetFlag, 0x00, sizeof( sGetFlag ) );
    /* mod by yangdong 20130305 bug
    COMP_SOFTSETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );
    */
    COMP_SOFTGETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );

    LOG(LM_DEBUG,Fmtmsg("BATCH: 提交标志[%s]", sGetFlag ),"DEBUG");

    /* 组装查询条件语句 */
    /*  clzt:9 未处理， cgbz:0 成功，1 部分成功  审核状态 1 审核失败  */
    if(0 == memcmp(sGetFlag, BATCH_MXTJBZ_NONPROC_FAIL ,1 ))  /* 提交未处理或处理失败明细 */
    {
        snprintf(sCondStr, sizeof( sCondStr ), "ywbh='%s' AND shzt !='1' \
            AND (clzt='9' OR ( cgbz<>'0' AND cgbz <> '1' ) ) ", sYwbh);
    }
    else /* 提交本批次未处理明细 */
    {
        snprintf(sCondStr, sizeof( sCondStr ),"pkrq='%s' AND ptpch='%s' %s ", sPkrq, sPtpch, sSjtjExpWhere ); 
    }

    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );

    /* modified by yangdong 20130201 在gaps4.1中，可能会引起oracle的-600错
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT lsxh as pnxh,%s FROM %s WHERE %s ORDER BY lsxh"\
                      ,sColStr, sTableName, sCondStr );
    */
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT trim(lsxh) as pnxh,%s FROM %s WHERE %s ORDER BY lsxh", \
        sColStr, sTableName, sCondStr );

    /* 导出到临时文件 */
    memset(sTmpFileName,0,sizeof(sTmpFileName));
    snprintf(sTmpFileName, sizeof( sTmpFileName), \
        "%s/tmp/batch_sjtj_tmp%s.%s", getenv("HOME"), sPkrq, sPtpch );
    if( sql_UnloadToFile(sTmpFileName,sSqlStr,'^','\\',&lRCount)!= MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("BATCH:导出文件处理失败,[%s]",sSqlStr),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_GENFILE,MSG_BATCH_SJTJ_GENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if( lRCount == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:无需要提交核心处理明细"),"WARNING");
        fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"BATCH:无需要提交核心处理明细");
        /* 设置本批次提交核心文件数 */
        COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_WJS,"0" );
        /* 设置本批次总笔数 */
        COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZBS,"0");
        /* 设置本批次总金额 */
        COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZJE,"0.00");
    
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }

    /* 打开导出文件处理 */
    if((srcfp = fopen(sTmpFileName, "r")) == NULL)
    {
        LOG(LM_STD,Fmtmsg("BATCH: 打开文件处理失败,[%s]",sTmpFileName),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 主机文件处理开始 */
    if((hostfp = fopen(sFileFullName, "w")) == NULL)
    {
        fclose( srcfp );
        LOG(LM_STD,Fmtmsg("BATCH: 打开文件处理失败,[%s]",sFileFullName),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 文件列信息链表初始化 */
    iResult =fprv_initFileColumn(sFileID,&t_fileColumnList );
    if( iResult <= 0 )
    {
        fclose( srcfp );
        fclose( hostfp );
        LOG(LM_STD,Fmtmsg("BATCH: 文件列信息链表初始化失败,[%s]",sFileID),"ERROR");
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
            Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 明细分类信息链表初始化 */
    iResult =fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_DETAIL,&t_fileDetailSortList);
    if( iResult != 1 )  /* 只支持单个明细分类 */
    {
        LOG(LM_STD,Fmtmsg("BATCH: 文件明细分类[%s]映射链表初始化失败,分类数[%d]",\
            sFileID, iResult ),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        fclose( srcfp );
        fclose( hostfp );
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 取明细分类信息 */
    memset(&thisSort, 0, sizeof(BATCH_FILESORT));
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* 单明细或不需要文件汇总分类映射链表初始化 */
    if( strcmp( sFileType,"01" ) != 0 )
    {
        iTSortCount=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_TOTAL,&t_fileTotalSortList);
        if( iTSortCount <= 0  )
        {
            fclose( srcfp );
            fclose( hostfp );
            batch_totalsortlistFree();
            batch_detailsortlistFree();
            LOG(LM_STD,Fmtmsg("BATCH: 文件汇总分类映射链表初始化,[%s]",sFileID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /* 处理可能的汇总信息 */
    /* 文件不拆分，直接处理 */
    if( lPgNum <= 0 )
    {
        if( strcmp( sFileType,"02" ) == 0 ||   /* 单汇总单明细 */
            strcmp( sFileType,"04" ) == 0 )    /* 单汇总单明细加汇总 */
        {
            iResult = SumWithCondSql( sCondStr, sTableName,"jyje", &iTotalNum, &dTotalAmt );
            if( iResult < 0 )
            {
                fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                batch_totalsortlistFree();
                batch_detailsortlistFree();
                batch_columnlistFree();
                fclose( hostfp );
                fclose( srcfp );
                return COMPRET_FAIL;
            }
            /* 遍历汇总分类，一个汇总分类处理一行记录,需要配置保证汇总分类的顺序匹配文件 */
            iResult = totalProc_write( lXmlhandle,iTotalNum,dTotalAmt, hostfp, BATCH_TOTAL_HEAD, sFileType,t_fileTotalSortList,t_fileColumnList);
            if( iResult < 0)
            {
                fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                batch_totalsortlistFree();
                batch_detailsortlistFree();
                batch_columnlistFree();
                fclose( hostfp );
                fclose( srcfp );
                return COMPRET_FAIL;
            }
        }
    }
    LOG(LM_DEBUG,Fmtmsg("BATCH: 明细处理开始"),"DEBUG");
    /* 处理明细信息 */
    dFileAmt = 0.00;
    iFileNum = 0;
    iTotalNum = 0;
    dTotalAmt = 0.00;
    memset(linebuf, 0, sizeof(linebuf));
    iAbort = 0;
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        /* 过滤空行  */
        if( 0 == linebuf[0] || 13 == linebuf[0] )
        {
            continue;
        }
                
        /* 文件内记录数 */
        iFileNum++;

        /* 根据配置，生成明细信息 */
        memset(outbuf, 0, sizeof(outbuf));
        iResult = detailProc_write(lXmlhandle,&iLsxh, linebuf,&dFileAmt,outbuf,&thisSort,t_fileColumnList);
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 明细信息处理失败,[%s]", linebuf),"ERROR");
            iAbort=4;
            break;
        }

        /* 明细处理记录总数 */
        iTotalNum ++;
        /* 添加一个换行 */
        length = strlen( outbuf );
        outbuf[ length ] = '\n';
        /* 写入提交核心文件 
        LOG(LM_DEBUG,Fmtmsg("BATCH: 核心文件写入[%d][%d][%s]",\
                iFileNum,length,outbuf),"ERROR");
        */
        iResult = fwrite( outbuf, length + 1, 1, hostfp);
        if( iResult < 0)
        {
            LOG(LM_STD,Fmtmsg("BATCH: 文件写入失败,[%d],[%d],[%s]",\
                iResult,errno,strerror(errno)),"ERROR");
            iAbort=7;
            break;
        }
        /* 判断是否需要拆分文件 */
        if( ( lPgNum > 0 ) && ( ( iLsxh% lPgNum ) == 0 ) )
        {
            /* 汇总在后，处理汇总信息 */
            if( strcmp( sFileType,"03" ) == 0 || /* 03 单明细＋汇总 */
                strcmp( sFileType,"04" ) == 0 )  /* 04 汇总＋单明细＋汇总 */

            {
                /* 直接在末尾添加汇总信息 */
                iResult = totalProc_write(lXmlhandle,iFileNum,dFileAmt,hostfp, BATCH_TOTAL_TAIL,sFileType ,t_fileTotalSortList,t_fileColumnList);
                if( iResult < 0)
                {
                    fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    iAbort=6;
                    break;
                }
            }
            fclose( hostfp );
            if( strcmp( sFileType,"02" ) == 0 || /* 02 汇总＋单明细 */
                strcmp( sFileType,"04" ) == 0 )  /* 汇总＋单明细＋汇总 */
            {
                /* 汇总在前，处理汇总信息, 需要重写文件，将汇总记录放在文件头 */
                /* 重写打开一个临时文件 */
                snprintf( sTmpFileFullName, sizeof( sFileFullName ), "%s.tmp",sFileFullName );
                hostfp = fopen( sTmpFileFullName, "w+");
                if( hostfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 打开文件处理失败,[%s]",sTmpFileFullName),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                    iAbort=6;
                    break;
                }
                iResult = totalProc_write(lXmlhandle,iFileNum,dFileAmt,hostfp, BATCH_TOTAL_HEAD,sFileType ,t_fileTotalSortList,t_fileColumnList);
                if( iResult < 0)
                {
                    fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    iAbort=6;
                    break;
                }
                /* 将明细文件添加到新文件后面 */
                tmpfp = fopen( sFileFullName,"r+" );
                if( tmpfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 打开文件处理失败,[%s]",sFileFullName),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                    iAbort=6;
                    break;
                }
                memset( sBuf, 0x00, sizeof( sBuf ) );
                /* 将明细文件内容写入到新文件的汇总记录之后 */
                while( fgets( sBuf, BATCH_MAX_FILELINE_BYTE, tmpfp ) != NULL )
                {
                    fprintf( hostfp, "%s", sBuf );
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                }
                fclose( tmpfp );
                fclose( hostfp );

                /* 删除明细文件，将新文件命名为同名文件 */
                unlink( sFileFullName );
                iResult = rename( sTmpFileFullName, sFileFullName );
                if( iResult != 0 )
                {
                    iAbort=7;
                    break;
                }
                
            }

            /* 数据入库时已插入对应记录的文件序号 */
            /* 文件名 */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjmc", iFileCount );
            COMP_SOFTSETXML(  sNode , sFileParsedName);
            /* 文件全名 */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", iFileCount );
            COMP_SOFTSETXML(  sNode ,sFileFullName );
            /* 文件内笔数 */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iFileCount );
            COMP_SOFTSETXML(  sNode , itoa( iFileNum ) );
             /* 文件内交易金额 */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iFileCount );
            sprintf( sBuf, "%.2f", dFileAmt );
            COMP_SOFTSETXML(  sNode , sBuf );

            /* 重起一个文件 */
            /* 文件个数 */
            iFileCount ++;

            COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_WJXH , itoa( iFileCount ) );
        
            if( strlen( sFileBasicName ) < 1 ) 
            {
                /* 文件名默认：业务编号＋批扣日期＋批次号+文件序号.req */
                snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                    "%s_%s_%s_%d.req", sYwbh, sPkrq, sPtpch, iFileCount );
            }
        
            /* 解析生成主机文件名( 配置信息可以带xml节点名 ) */
            if( strlen( sFileBasicName ) > 2 )
            {
                /* 保存文件名配置 */
                pstrcopy( sFileBakName, sFileBasicName, sizeof(sFileBasicName)); 
                LOG(LM_DEBUG,Fmtmsg("BATCH: 主机文件名称解析,[%s]=>",sFileBasicName),"DEBUG")
                /* 先解析XML变量 */
                if(xml_ParseXMLString(lXmlhandle,sFileBasicName,sizeof(sFileBasicName))==FAIL)
                {
                    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,\
                        Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                /* 解析后文件名 */
                strcpy( sFileParsedName, sFileBasicName );
                /* 恢复文件名配置 */
                pstrcopy( sFileBasicName, sFileBakName, sizeof(sFileBasicName)); 
            }
            /* 文件全名 */
            snprintf( sFileFullName, sizeof( sFileFullName ),\
                "%s/%s",sFilePath, sFileParsedName );

            if( ( hostfp = fopen( sFileFullName, "w" ) ) == NULL )
            {
                LOG(LM_STD,Fmtmsg("打开文件失败,file=[%s],error=[%s]",\
                    sFileFullName,strerror(errno)),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* 明细处理总金额 */
            dTotalAmt += dFileAmt;
            /* 新文件记录数和总金额归0 */
            iFileNum = 0;
            dFileAmt = 0.00;

        }

        memset(linebuf, 0, sizeof(linebuf));
    }

    fclose( srcfp );

    if( iFileNum > 0  && iAbort == 0  )  /* 若最后一个文件无记录(空文件),则不会提交核心 */
    {
        if( lPgNum > 0 )
        {
            /* 主机文件拆分，最后需要处理头上的汇总记录 */
            if( strcmp( sFileType,"02" ) == 0 || /* 02 汇总＋单明细 */
                strcmp( sFileType,"04" ) == 0 )  /* 汇总＋单明细＋汇总 */
            {
                fclose( hostfp );
                /* 汇总在前，处理汇总信息, 需要重写文件，将汇总记录放在文件头 */
                /* 重写打开一个临时文件 */
                snprintf( sTmpFileFullName, sizeof( sFileFullName ), "%s.tmp",sFileFullName );
                hostfp = fopen( sTmpFileFullName, "w+");
                if( hostfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 打开文件处理失败,[%s]",sTmpFileFullName),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                    iAbort=6;
                }
                iResult = totalProc_write(lXmlhandle,iFileNum,dFileAmt,hostfp,BATCH_TOTAL_HEAD,sFileType,t_fileTotalSortList,t_fileColumnList);
                if( iResult < 0)
                {
                    fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    iAbort=10;
                }
                /* 将明细文件添加到新文件后面 */
                tmpfp = fopen( sFileFullName,"r" );
                if( tmpfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 打开文件处理失败,[%s]",sFileFullName),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                    iAbort=6;
                }
                while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, tmpfp ) != NULL )
                {
                   fprintf( hostfp, "%s", linebuf );
                }
                fclose( tmpfp );
                /* 删除明细文件，将新文件命名为同名文件 */
                unlink( sFileFullName );
                iResult = rename( sTmpFileFullName, sFileFullName );
                if( iResult != 0 )
                {
                    fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                    iAbort=11;
                }
            }
        }

        /* 处理汇总信息 */
        if( strcmp( sFileType,"03" ) == 0 ||  /*  明细 ＋ 汇总 格式 */
            strcmp( sFileType,"04" ) == 0 )   /*  汇总＋明细＋汇总格式 */
        {
            /* 配置保证文件分类序号 */

            iResult = totalProc_write(lXmlhandle,iFileNum,dFileAmt,hostfp, BATCH_TOTAL_TAIL,sFileType,t_fileTotalSortList,t_fileColumnList);
            if( iResult < 0)
            {
                fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,\
                          Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                iAbort=12;
            }
        }

        /* 文件名 */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjmc", iFileCount );
        COMP_SOFTSETXML(  sNode, sFileParsedName );
        /* 文件全名 */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", iFileCount );
        COMP_SOFTSETXML(  sNode, sFileFullName );
        /* 文件内笔数 */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iFileCount );
        COMP_SOFTSETXML(  sNode , itoa( iFileNum) );
        /* 文件内交易金额 */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iFileCount );
        sprintf( sBuf, "%.2f", dFileAmt );
        COMP_SOFTSETXML(  sNode , sBuf );
        /* 明细处理总金额 */
        dTotalAmt += dFileAmt;
    }
    else /* 空文件，删除 */
    {
        iFileCount --;
        LOG(LM_STD,Fmtmsg("BATCH: 生成提交文件处理错误: [%d]",iAbort),"ERROR");
        unlink( sFileFullName );
    }

    /* linux下重复fclose会coredump */
#ifdef _OS_LINUX__
    if( hostfp->_fileno >= 0 )
#endif
    fclose( hostfp );

    unlink(sTmpFileName);

    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_totalsortlistFree();

    /* 更新文件内记录的处理状态 
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
LOG(LM_DEBUG,Fmtmsg("更新明细流水表:begin"),"ERROR");
    snprintf(sSqlStr,sizeof(sSqlStr),"UPDATE %s SET clzt='1' \
                  WHERE pkrq='%s' AND ptpch='%s' ",\
                  sTableName, sPkrq, sPtpch);
    if( sql_DynExec(sSqlStr,&iResult)!=0 && iResult <=0 )
    {
        LOG(LM_STD,Fmtmsg("更新明细流水表失败:[%s], [%d]",\
                                sSqlStr, sqlca.sqlcode),"ERROR");
        iAbort = -9;
    }
LOG(LM_DEBUG,Fmtmsg("更新明细流水表:end"),"ERROR");
    */

    /* 处理异常 */
    if( iAbort )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 生成提交文件处理错误: [%d]",iAbort),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_GENFILE,MSG_BATCH_SJTJ_GENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;
    }

    /* 设置本批次提交核心文件数 */
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_WJS,itoa(iFileCount));
    /* 设置本批次总笔数 */
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZBS,itoa(iTotalNum));
    /* 设置本批次总金额 */
    memset(sBuf,0,sizeof(sBuf));
    sprintf(sBuf,"%.2f",dTotalAmt);
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZJE,sBuf );

    COMP_HARDCOPYXML(XMLNM_BATCH_RUNCTRL_CPDM,XMLNM_BATCH_SJTJ_CPDM);
    COMP_HARDCOPYXML(XMLNM_BATCH_REQ_YWBH,XMLNM_BATCH_SJTJ_YWBH);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:BATCH_SJTJ_WAIT
组件名称: BATCH_SJTJ_WAIT
组件功能: 批量业务数据提交文件后等待时间
组件参数:
 序号 参数类型  参数名称      资源类别     缺省值  可空  参数说明    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT BATCH_SJTJ_WAIT(HXMLTREE lXmlhandle)
{
    int  iParas,iResult;
    char sBuf[128];
   /* int  iFileNum = 0;       文件内记录数 */
    int  iFirmTime = 0;     /* 固定断点时间 */
    int  iFloatTime= 0;     /* 浮动断点时间 */
    int  iTotal = 0;
    int  iFileRec = 0;      /* 文件记录数 */
    int  iMAXHOSTWAIT = 0;  /* 最长等待时间 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"文件内记录数")
    iFileRec = atoi( sBuf );
    
    /* 固定断点时间  */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_GDDDSJ,sBuf);
    iFirmTime = atoi( sBuf );
    /* 浮动断点时间 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_FDDDSJ,sBuf);
    iFloatTime = atoi( sBuf );
    /* 最长等待时间  */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_BATCH_MAXHOSTWAIT,sBuf);
    iMAXHOSTWAIT = atoi( sBuf );

    /* 提交核心中断时间 = 固定断点时间 + 文件记录数/1000 * 浮动断点时间 */
    iTotal = iFirmTime + iFileRec / 1000 * iFloatTime ;
   
    /* 控制最长等待时间 */
    if( iMAXHOSTWAIT > 1 && iTotal > iMAXHOSTWAIT )
        iTotal = iMAXHOSTWAIT;
        
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_WAIT,itoa( iTotal ) );

    LOG(LM_DEBUG,Fmtmsg("firm[%d] float[%d] ret[%d] 提交等待时间[%d]",\
        iFirmTime, iFloatTime, iFileRec, iTotal ),"DEBUG")
                  
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:BATCH_SJTJ_TIME_CTRL
组件名称: BATCH_SJTJ_TIME_CTRL
组件功能: 批量业务数据提交夜批量开始时间的判断
组件参数:
 序号 参数类型  参数名称      资源类别     缺省值  可空  参数说明    
使用限制:
程 序 员: yerong
发布日期:
修改日期:
参数使用示例:
************************************************************************/

IRESULT SBATCH_SJTJ_TIME_CTRL(HXMLTREE lXmlhandle)
{
    int ret=0;
    char sBuf[100];
        
    memset( sBuf, 0, sizeof( sBuf ));
    COMP_SOFTGETXML( "/batch/req/sjtjflag",sBuf);
    if( sBuf[0]=='1' )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0; 
    }
        
    ret=prv_clsj( lXmlhandle, "sjtj" );
    /* 可以重新执行的,由守护进程进行处理 */
    if ( ret == -1 )
    { 
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_WAIT);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL );
        return COMPSTATUS_FAIL;
    }
    if( ret==-2 )
    {   /* 失败,不可以重新执行 */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;              
}
