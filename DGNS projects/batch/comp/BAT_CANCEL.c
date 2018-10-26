/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V2.1.0.1
操作系统:AIX5.3+ORACLE+HSXP
文件名称:BAT_CANCEL.ec
文件描述:批量撤销提交核心处理
程 序 员:YangDong
发布日期:20140715
*********************************************************************/
#include "gaps_head.h"
#include "app_head.h"
#include "batch_head.h"

/*EXEC SQL include "gaps_head.eh";*/

#define SOCOMPVERSION "V2.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_SJTJ.so</soname>\
        <sosrcname>BAT_SJTJ.ec FOR ORACLE</sosrcname>\
        <sonote>BATCH数据撤销处理组件集合</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2014-7-15 15:08\" programer=\"YangDong\" filesize=\"1238198\">HS-AgentV2.1整理</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2014-11-13 13:08\" programer=\"Chenxm\" filesize=\"1238198\">DCI改造</rec>\
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
组件函数名称:SBATCH_PLCZ_SJTJ
组件名称:BATCH_PLCZ_SJTJ
组件功能: 批量业务生成数据提交文件
组件参数:
 序号 参数类型  参数名称      资源类别     缺省值  可空  参数说明    
  1   1-输入    主机文件名    416XML解析字符串  *      N      
  2   1-输入    文件标识      416XML解析字符串  *      N    
  3   1-输入    映射标识      416XML解析字符串  *      N    
  4   1-输入    业务表名      416XML解析字符串  *      N    
  5   1-输入    文件序号      416XML解析字符串  *      N    
使用限制:单明细文件格式
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_PLCZ_SJTJ(HXMLTREE lXmlhandle)
{
    /*EXEC SQL BEGIN DECLARE SECTION; */
        char sMapID[40+1];
        char sYwbh[16+1];
        char sColID[32+1];
        char sFileID[32+1];
        char sSqlStr[1024];
        int iWjxh = 0;     /* 文件序号 */
        /*int iZjszwz = 0;    主机上账位置 */
    /*EXEC SQL END   DECLARE SECTION; */
    int  iParas,iResult;
    char sBuf[256];
    char sSql[512];
    char sErrmsg[218];
    char lineBuf[BATCH_MAX_FILELINE_BYTE];
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
    char sColStr[256];  /* 提交后台映射字段 */
    /*long lLsxh = 0;      流水序号 */
    /*int  iFileCount = 1;     文件数 */
    int  iFileNum = 0;      /* 文件内记录数 */
    int  iTotalNum= 0;      /* 本批次记录数 */
    double dFileAmt= 0;     /* 文件内总金额 */
    double dTotalAmt = 0;   /* 本批次总金额 */

    int  iLsxh = 0;
    int  iPos = 0;
    int iRet = -1;

    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    BATCH_FILEMAP batch_filemap;
    CURSOR cur;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(7)

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

    /* 批扣日期 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(5,sBuf,"原批扣日期")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* 平台批次号 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(6,sBuf,"原平台批次号")
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    /* 文件序号 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(7,sBuf,"文件序号")
    iWjxh = atoi( sBuf );
    if( iWjxh == 0 )  /* 文件序号默认1 */
    {
        iWjxh = 1;
    }
    COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_SUBMIITED_WJXH, itoa( iWjxh ) );
    
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

    /* 文件名处理 */
    /* 主机文件保存位置 */
    snprintf( sFilePath, sizeof( sFilePath ),\
        "%s/batch/zjwj", getenv("GAPSFILEDIR") );

    snprintf( sFileParsedName,sizeof( sFileParsedName ),\
        "%s_%s_%s_%d.req", sYwbh, sPkrq, sPtpch, iWjxh );

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

    /*add by chenxm 20141113DCI改造工作*/
    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "SELECT batch_filemap.columnid, batch_filemap.zjszwz FROM  batch_filemap "
        "WHERE mapid = '%s' AND zjszwz > 0 ORDER BY zjszwz", sMapID);
    if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
    {
        LOG(LM_STD,Fmtmsg("数据库打开游标操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("执行游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    }
    /*add end 
    EXEC SQL DECLARE cur_col_str CURSOR FOR
        SELECT batch_filemap.columnid, batch_filemap.zjszwz FROM  batch_filemap  
        WHERE mapid = :sMapID AND zjszwz > 0 ORDER BY zjszwz;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    EXEC SQL OPEN cur_col_str;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_col_str",sqlca.sqlcode),"ERROR")
    if( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    memset( sColID, 0x00, sizeof( sColID ) );
    iZjszwz = 0;
    EXEC SQL FETCH cur_col_str into :sColID , :iZjszwz  ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_col_str",sqlca.sqlcode),"ERROR")
    if( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        EXEC SQL CLOSE cur_col_str;
        return COMPRET_FAIL;
    }*/

    /* 文件配置中列位置 */
    memset(sColStr,0,sizeof(sColStr));
    iPos = 0;
    /*while ( SQLSUCC )*/
    while(iRet > 0)
    {
        iPos ++;
        trim( sColID );
        strcat( sColStr, sColID );
        strcat( sColStr, "," );

        memset( sColID, 0x00, sizeof( sColID ) );
        /*EXEC SQL FETCH cur_col_str into :sColID , :iZjszwz ;*/
        iRet = DBFetch(cur, SD_BATCH_FILEMAP, NUMELE(SD_BATCH_FILEMAP), &batch_filemap, sErrmsg);
        if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("查询数据库失败[%d][%s]",iRet,sSql),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPSTATUS_FAIL;
            }
    }
    /*EXEC SQL CLOSE cur_col_str; */
    DCIFreeCursor(cur);
    /* 去最后一个 , */
    sColStr[strlen( sColStr ) - 1 ] = '\0';
    
    /* 明细提交标志 */
    memset( sGetFlag, 0x00, sizeof( sGetFlag ) );
    COMP_SOFTGETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );

    /* 组装查询条件语句 */
    /*  cgbz:0 成功，1 部分成功 */
    snprintf(sCondStr, sizeof( sCondStr ),"pkrq='%s' AND ptpch='%s' AND wjxh='%d' AND cgbz='0' OR cgbz='1' ", sPkrq, sPtpch, iWjxh ); 

    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT trim(lsxh) as pnxh,%s FROM %s WHERE %s ORDER BY lsxh"\
        ,sColStr, sTableName, sCondStr );

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
        LOG(LM_STD,Fmtmsg("BATCH:本序号[%d]无需要提交核心处理明细",iWjxh),"INFO");
        /* 文件内笔数 */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iWjxh );
        COMP_SOFTSETXML(  sNode , "0" );
        /* 文件内交易金额 */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iWjxh );
        COMP_SOFTSETXML(  sNode , "0.00");
        
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

    LOG(LM_DEBUG,Fmtmsg("BATCH: 明细处理开始"),"DEBUG");
    /* 处理明细信息 */
    dFileAmt = 0.00;
    iFileNum = 0;
    iTotalNum = 0;
    dTotalAmt = 0.00;
    memset(lineBuf, 0, sizeof(lineBuf));
    iAbort = 0;
    while( fgets( lineBuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        /* 过滤空行  */
        if( 0 == lineBuf[0] || 13 == lineBuf[0] )
        {
            continue;
        }
                
        /* 文件内记录数 */
        iFileNum++;

        /* 根据配置，生成明细信息 */
        memset(outbuf, 0, sizeof(outbuf));
        iResult = detailProc_write(lXmlhandle,&iLsxh, lineBuf,&dFileAmt,outbuf,&thisSort,t_fileColumnList);
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 明细信息处理失败,[%s]", lineBuf),"ERROR");
            iAbort=4;
            break;
        }

        /* 明细处理记录总数 */
        iTotalNum ++;
        /* 明细处理总金额 */
        dTotalAmt += dFileAmt;

        /* 添加一个换行 */
        length = strlen( outbuf );
        outbuf[ length ] = '\n';
        /* 写入提交核心文件 */
        iResult = fwrite( outbuf, length + 1, 1, hostfp);
        if( iResult < 0)
        {
            LOG(LM_STD,Fmtmsg("BATCH: 文件写入失败,[%d],[%d],[%s]",\
                       iResult,errno,strerror(errno)),"ERROR");
            iAbort=7;
            break;
        }
    }

    fclose( srcfp );
    
    /* 文件名 */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjmc", iWjxh );
    COMP_SOFTSETXML(  sNode, sFileParsedName );
    /* 文件全名 */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", iWjxh );
    COMP_SOFTSETXML(  sNode, sFileFullName );
    /* 文件内笔数 */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iWjxh );
    COMP_SOFTSETXML(  sNode , itoa( iFileNum) );
    /* 文件内交易金额 */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iWjxh );
    sprintf( sBuf, "%.2f", dFileAmt );
    COMP_SOFTSETXML(  sNode , sBuf );

    /* linux下重复fclose会coredump */
#ifdef _OS_LINUX__
    if( hostfp->_fileno >= 0 )
#endif
    fclose( hostfp );

    unlink(sTmpFileName);

    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_totalsortlistFree();

    /* 处理异常 */
    if( iAbort )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 生成提交文件处理错误: [%d]",iAbort),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_GENFILE,MSG_BATCH_SJTJ_GENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_PLCZ_SJTH
组件名称:BATCH_PLCZ_SJTH
组件功能: 批量业务数据提回处理
组件参数:
 序号 参数类型  参数名称      资源类别     缺省值  可空  参数说明    
  1   1-输入    主机文件名    416XML解析字符串  *      N      
  2   1-输入    文件标识      416XML解析字符串  *      N    
  3   1-输入    映射标识      416XML解析字符串  *      N    
  4   1-输入    业务表名      416XML解析字符串  *      N    
  5   1-输入    文件序号      416XML解析字符串  *      N    
使用限制:单明细文件格式
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_PLCZ_SJTH(HXMLTREE lXmlhandle)
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
        char sXym[10+1];
        char sSplit[10+1];
        char sSql[1024];
        /*int iWjxh = 0;      文件序号 */
        /*int iZjszwz = 0;    主机上账位置 */
    /*EXEC SQL END   DECLARE SECTION; */
    int  iParas,iResult;
    char sBuf[256];
    char lineBuf[BATCH_MAX_FILELINE_BYTE];
    char sTableName[40+1];
    char sFileName[128];
    char sPkrq[8+1];
    char sPtpch[8+1];
    FILE *hostfp;
    long lLsxh = 0;     /* 流水序号 */
    int iRet = -1;

    /*int  iLsxh = 0;*/
    /*int  iPos = 0;*/

    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(4)

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"主机文件名")
    pstrcopy(sFileName,sBuf,sizeof(sFileName)); 

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"业务表名")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBM_NULL,MSG_BATCH_YWBM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"批扣日期")
    /* 批扣日期 */
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* 平台批次号 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"平台批次号")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    if(( hostfp = fopen(sFileName, "r+")) == NULL)
    {
        LOG(LM_STD,Fmtmsg("BATCH: 打开主机返回文件[%s]失败",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*add by chenxm 20141113 DCI改造工作*/
    iRet = DCIBegin();
    if(iRet != 0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }/* add end */

    LOG(LM_DEBUG,Fmtmsg("BATCH: 明细处理开始"),"DEBUG");
    /* 处理明细信息 */
    memset(lineBuf, 0, sizeof(lineBuf));
    memset( sSplit, 0x00, sizeof( sSplit ) );
    strcpy( sSplit, "124" );
    while( fgets( lineBuf, BATCH_MAX_FILELINE_BYTE, hostfp ) != NULL )
    {
        /* 过滤空行  */
        if( 0 == lineBuf[0] || 13 == lineBuf[0] )
        {
            continue;
        }
                
        /* 文件内记录数 */

        /* 序号|中文名|英文名|交易金额|性别|证件类型|证件号码|卡号|凭证类型|地址|联系电话|产品类型|币种|卡凭证号|余额类型|附言|错误编号|错误描述|冻结编号 */
        memset( sBuf , 0x00, sizeof( sBuf ) );
        /* 序号 */
        fprv_getSubStr(lineBuf, 1, sSplit, sBuf);
        lLsxh = atol( sBuf );

        /* 错误编号 */
        memset( sBuf , 0x00, sizeof( sBuf ) );
        fprv_getSubStr(lineBuf, 17, sSplit, sBuf);
        pstrcopy(sXym,sBuf,sizeof(sXym)); 
        trim( sXym );

        /* 判断是否成功 */
        if( strcmp( sXym,"00000" ) == 0 )
        {
            /* 撤销成功，将原批次对应明细信息置为已冲正 */
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf( sSql,"UPDATE %s SET cgbz='7' WHERE pkrq='%s' and ptpch='%s' and lsxh=%ld ", sTableName, sPkrq, sPtpch, lLsxh );
            iRet = DCIExecuteDirect(sSql);
            /*if ( sql_DynExec(sSql,&iResult)!=0 || iResult <=0 )*/
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息处理失败,[%d],[%s]: [%d][%s]",\
                    lLsxh,lineBuf,iRet,sSql),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
                fclose( hostfp );
                /*sql_RollbackTrans();*/
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPSTATUS_FAIL;
            }
        }
    }
    DCICommit();

    /*if( sql_CommitTrans() !=MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败!,sqlcode[%d]",sqlca.sqlcode),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_FAIL,Fmtmsg(MSG_SQL_FAIL,sqlca.sqlcode));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }*/

    fclose( hostfp );

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
