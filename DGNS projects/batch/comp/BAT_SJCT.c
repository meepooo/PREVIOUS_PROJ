/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_SJCT.c
文件描述: 批量业务处理文件映射-数据重提处理转换组件集
项 目 组:中间业务平台项目组
程 序 员:yangdong
发布日期:20110801
*********************************************************************/
#include "gaps_head.h"
#include "app_head.h"
#include "batch_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_SJCT.so</soname>\
        <sosrcname>BAT_SJCT.c</sosrcname>\
        <sonote>BATCH数据重提组件集合</sonote>\
        <version>\
        <rec ver=\"4.1.0.1\" modify=\"2016-07-11 10:08\" programer=\"tuql\" filesize=\"1291580\">数据重提改造</rec>\
        </version>\
        </root>";
    printf("\n================动态组件基本信息================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if (strlen(sversion) >= isize)
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
组件函数名称:SBATCH_SJCT
组件名称:BATCH_SJCT
组件功能:数据重提
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_SJCT(HXMLTREE lXmlhandle)
{
    char sMapID[40+1];
    char sColID[32+1];
    int  iHpwjwz;
    int  iParas,iResult;
    char sBuf[128];
    char linebuf[BATCH_MAX_FILELINE_BYTE];
    char outbuf[BATCH_MAX_FILELINE_BYTE];
    char sTableName[50+1];
    char sFilePath[64];
    char sFilePath2[64];
    char sFileBasicName[64];
    char sFileFullName[128];
    char sTmpFileName[128];
    char sFileID[40+1];
    char sFileType[2+1];
    char sYwbh[16+1];
    char sPkrq[8+1];
    char sPtpch[8+1],sGenFlag[1+1];
    char sCodeFmt[2+1];
    char sFileTypeReal[1+1];
    int  iTSortCount=0;
    int  i,iAbort=0,length=0,index=0;
    int iFileLen = 0;  /*文件内容长度*/
    char sCondStr[256];   /* 重提条件字符串 */
    char sColStr[1024];    /* 重提文件所需列名 */
    char sSqlStr[1300];
    long lRCount=0;
    int  iTotalNum=0;
    int  iLsxh = 0;
    double dTotalAmt=0.00;
    FILE *destfp;
    FILE *srcfp;
    char sSql1[1024];
    char sErrmsg[512];
    CURSOR cur;
    int iRet =-1;
    BATCH_FILEMAP sdb_batch_filemap;
    
    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(6)
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sTableName,0,sizeof(sTableName));
    COMP_GETPARSEPARAS(1,sBuf,"业务表名")
    pstrcopy(sTableName,sBuf,sizeof(sTableName));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileBasicName,0,sizeof(sFileBasicName));
    COMP_GETPARSEPARAS(2,sBuf,"重提文件名")
    pstrcopy(sFileBasicName ,sBuf,sizeof(sFileBasicName)); 
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sMapID,0,sizeof(sMapID));
    COMP_GETPARSEPARAS(3,sBuf,"映射标识")
    pstrcopy(sMapID,sBuf,sizeof(sMapID));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileID,0,sizeof(sFileID));
    COMP_GETPARSEPARAS(4,sBuf,"重提文件标识")
    pstrcopy(sFileID,sBuf,sizeof(sFileID));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileType,0,sizeof(sFileType));
    COMP_GETPARSEPARAS(5,sBuf,"重提文件类型")
    pstrcopy(sFileType,sBuf,sizeof(sFileType));

    memset(sBuf,0,sizeof(sBuf));
    memset(sGenFlag,0,sizeof(sGenFlag));
    COMP_GETPARSEPARAS(6,sBuf,"重提标志")
    pstrcopy(sGenFlag,sBuf,sizeof(sGenFlag));
    
    /* 批扣日期 */
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YPKRQ,sPkrq);
    trim(sPkrq);

    /* 批量业务编号 */
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbh,0,sizeof(sYwbh));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    pstrcopy(sYwbh,sBuf,sizeof(sYwbh)); 
    
    /* 平台批次号 */
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YPTPCH,sPtpch);
    trim(sPtpch);

    /* 重提文件路径1  */
    memset(sFilePath,0,sizeof(sFilePath));
    COMP_SOFTGETXML( XMLNM_BATCH_REQ_LOCALPATH,sFilePath );
    trim(sFilePath);

    /* 重提文件路径2  */
    memset(sFilePath2,0,sizeof(sFilePath2));
    COMP_SOFTGETXML( XMLNM_BATCH_SJHP_FILEDIR,sFilePath2 );
    trim(sFilePath2);

    LOG(LM_DEBUG,Fmtmsg("BATCH: 重提标志[%s] 文件标识[%s] 文件名[%s] 原批扣日期[%s] 原批次号[%s]",\
        sGenFlag, sMapID, sFileBasicName, sPkrq, sPtpch  ),"DEBUG");

    /* 文件名默认：业务编号＋批扣日期＋批次号 */
    if( strlen( sFileBasicName ) < 1 )
    {
        if( sGenFlag[0] == '3' )  /* 失败文件，默认加_f */
            snprintf( sFileBasicName, sizeof( sFileBasicName ),\
                "CT_%s_%s_%s_f", sYwbh, sPkrq, sPtpch );
        else 
            snprintf( sFileBasicName, sizeof( sFileBasicName ),\
               "CT_%s_%s_%s", sYwbh, sPkrq, sPtpch );
    }

    if( strlen( sGenFlag ) < 1 )
        strcpy( sGenFlag,"1" );  /* 默认重提标志 1 本批全部明细  */

    /* 组装重提文件需要处理字符串 */
    /* 根据映射配置，取需要处理的字段 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM  batch_filemap\
        WHERE mapid ='%s' AND lylx='1' order by to_number(lywz) ",sMapID  );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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
    memset(sColStr,0,sizeof(sColStr));
    memset( &sdb_batch_filemap, 0x00, sizeof( BATCH_FILEMAP ) );
    iTotalNum = 0;
    while( ( iRet = DBFetch(cur, SD_BATCH_FILEMAP, NUMELE(SD_BATCH_FILEMAP), &sdb_batch_filemap, sErrmsg ) ) > 0 )
    {
        iTotalNum++;
        trim( sColID );
        strcat( sColStr, sdb_batch_filemap.columnid );
        strcat( sColStr, "," );
        memset( &sdb_batch_filemap, 0x00, sizeof( BATCH_FILEMAP ) );
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    /* 去最后一个 , */
    sColStr[strlen( sColStr ) - 1 ] = '\0';
    /* 检查是否配置外部文件映射 */
    if( iTotalNum < 1 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJHP_PZNULL,MSG_BATCH_SJHP_PZNULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: colstr[%s] genflag[%s]", sColStr,sGenFlag ),"DEBUG");

    /* 重提条件组装 */
    /* 重提标志     0 所有批次明细
                    1 本批次全部明细
                    2 本批次成功明细
                    3 本批次失败明细
                    4 分别生成本批成功失败明细 */
    /* 成功标志 0 成功 1 部分成功 2 失败 */
    memset(sSqlStr, 0, sizeof(sSqlStr));
    if( strcmp( sGenFlag, BATCH_ATTRIBUTE_MXHPBZ_SUCC ) == 0 ) /*成功明细*/
    {
        snprintf(sCondStr, sizeof( sCondStr ), " pkrq='%s' AND ptpch='%s' \
            AND ( cgbz='0' OR cgbz='1' ) ", sPkrq,sPtpch);        
    }
    else if( strcmp( sGenFlag, BATCH_ATTRIBUTE_MXHPBZ_FAIL ) == 0 ) /*失败明细*/
    {
        snprintf(sCondStr,sizeof( sCondStr ), " pkrq='%s' AND ptpch='%s'\
            AND ( cgbz !='0' AND  cgbz != '1' ) ", sPkrq, sPtpch);        
    }
    else if( strcmp( sGenFlag, BATCH_ATTRIBUTE_MXHPBZ_ALLDATA ) == 0 ) /*全部批次明细*/
    {
        snprintf(sCondStr,sizeof( sCondStr ), " 1=1 ");        
    }
    else  /* 默认生成本批次所有明细 */
    {
        snprintf(sCondStr, sizeof( sCondStr ),\
            " pkrq='%s' AND ptpch='%s'", sPkrq, sPtpch); 
    }
        
    /* 文件汇总分类映射链表初始化 */
    if( strcmp( sFileType,"01" ) != 0 )  /* 非单明细 */
    {
        iTSortCount=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_TOTAL,&t_fileTotalSortList );
        if ( iTSortCount <= 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH:汇总分类初始化失败,[%s]",sFileID),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /* 文件明细分类链表初始化 */
    iResult=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_DETAIL, &t_fileDetailSortList);
    if ( iResult != 1 ) /* 只有一个明细分类 */
    {
        LOG(LM_STD,Fmtmsg("BATCH: 明细分类初始化失败,[%s] iResult[%d]",sFileID, iResult ),"ERROR");
        batch_totalsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
            Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 取明细分类信息 从链表中取第一条配置信息即退出，即默认只有一个明细分类 */
    memset(&thisSort, 0x00, sizeof(BATCH_FILESORT) );
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* 文件列信息链表初始化 */
    iResult=fprv_initFileColumn(sFileID,&t_fileColumnList );
    if ( iResult <= 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 文件列信息初始化失败,[%s]",sFileID),"ERROR");
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
                               Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 文件映射信息链表初始化 */
    iResult=fprv_initFileMap(sMapID,BATCH_STEPNM_SJHP,&t_fileMapList);
    if( iResult <=0 )
    {
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILEMAP_LISTFAIL,\
                        Fmtmsg(MSG_BATCH_FILEMAP_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 重提文件名解析( 配置信息可以带xml节点名 ) */
    if( strlen( sFileBasicName ) > 2 )
    {
        LOG(LM_DEBUG,Fmtmsg("BATCH: 重提文件名称解析,[%s]=>",sFileBasicName ),"DEBUG")
        /* 先解析XML变量 */
        if(xml_ParseXMLString(lXmlhandle,sFileBasicName,sizeof(sFileBasicName))==FAIL)
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,\
                Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    LOG(LM_DEBUG,Fmtmsg("BATCH: 开始处理重提文件[%s][%s]", sFilePath, sFileBasicName ),"DEBUG");
    /* 文件路径处理 */
    memset(sFileFullName, 0x00, sizeof(sFileFullName));
    if ( strlen(sFilePath) > 0 )
    {
        snprintf( sFileFullName, sizeof( sFileFullName ), "%s/%s",sFilePath, sFileBasicName );
    }else
    {
        if( sFilePath2[0] != '/' ) /* 相对路径，取默认文件路径 */
        {
            snprintf( sFileFullName, sizeof( sFileFullName ),\
                     "%s/%s/%s", getenv("HOME"), sFilePath2, sFileBasicName  );
        }
        else
        {
            snprintf( sFileFullName, sizeof( sFileFullName ), "%s/%s",sFilePath2, sFileBasicName );
        }
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: 开始处理重提文件[%s]type[%s]", sFileFullName,sFileType ),"DEBUG");

    /* 统计核心实际交易金额 */
    iTotalNum = 0;
    iResult=SumWithCondSql( sCondStr, sTableName, "jyje", &iTotalNum, &dTotalAmt );
    if( iResult < 0 )
    {
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC,iResult));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 重提文件处理开始 */
    if((destfp = fopen(sFileFullName, "w")) == NULL)
    {
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        LOG(LM_STD,Fmtmsg("BATCH: 打开文件[%s]失败",sFileFullName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    /* 处理开头的汇总信息 */
    if( strcmp( sFileType,"02" ) == 0 ||   /* 单汇总单明细 */
        strcmp( sFileType,"04" ) == 0 )    /* 多汇总单明细 */
    {
        /* 遍历汇总分类，一个汇总分类处理一行记录,需要配置保证汇总分类的顺序匹配文件 */
        iResult=totalProc_write( lXmlhandle,iTotalNum,dTotalAmt,destfp,BATCH_TOTAL_HEAD,sFileType ,t_fileTotalSortList,t_fileColumnList);
        if( iResult < 0)
        {
            batch_totalsortlistFree();
            batch_detailsortlistFree();
            batch_columnlistFree();
            batch_maplistFree();
            fclose( destfp );
            fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC,iResult));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /* 导出需要重提数据文件 */
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT lsxh AS bat_pnxh, %s FROM %s WHERE %s \
        ORDER BY bat_pnxh",sColStr, sTableName, sCondStr );
    LOG(LM_DEBUG,Fmtmsg("BATCH: 重提条件[%s]", sSqlStr ),"DEBUG");
    memset(sTmpFileName,0,sizeof(sTmpFileName));
    snprintf(sTmpFileName, sizeof( sTmpFileName ),\
             "%s/tmp/batch_sjct_tmp%s.%s", getenv("HOME"), sPkrq, sPtpch );
    if( sql_UnloadToFile(sTmpFileName,sSqlStr,'^','\\',&lRCount)!=MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("BATCH:导出文件处理失败,[%s]",sSqlStr),"ERROR");
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fclose( destfp );
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJHP_UNLOAD,MSG_BATCH_SJHP_UNLOAD );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 打开导出文件处理 */
    if((srcfp = fopen(sTmpFileName, "r")) == NULL)
    {
        LOG(LM_STD,Fmtmsg("BATCH: 打开文件处理失败,[%s]",sTmpFileName),"ERROR");
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fclose( destfp );
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJHP_UNLOAD,MSG_BATCH_SJHP_UNLOAD );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 处理明细信息 */
    index=0;
    dTotalAmt=0.00;
    memset(linebuf, 0, sizeof(linebuf));
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL    )
    {
        /* 无信息继续 */
        if( 13 == linebuf[0] || 10 == linebuf[0] || 0 == linebuf[0] )
        {
            continue;
        }

        index ++;
        memset(outbuf, 0, sizeof(outbuf));
        iResult=detailProc_write(lXmlhandle, &iLsxh, linebuf,&dTotalAmt,outbuf,&thisSort,t_fileColumnList);
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 明细信息处理失败,[%s] [%d] [%s]",\
                linebuf,index,thisSort.classname),"ERROR");
            iAbort=4;
            break;
        }
        length=strlen(outbuf);
        outbuf[length] = '\n';
        iResult=fwrite( outbuf, length+1, 1, destfp);
        if( iResult < 0)
        {
            LOG(LM_STD,Fmtmsg("BATCH: 文件写入失败,[%d],[%d],[%s]",\
                iResult,index,strerror(errno)),"ERROR");
            iAbort=7;
            break;
        }

        memset(linebuf, 0x00, sizeof(linebuf));
    }

    /* 处理最后的汇总信息 */
    if( strcmp( sFileType,"03" ) == 0 ||   /* 单汇总单明细 */
        strcmp( sFileType,"04" ) == 0 )    /* 多汇总单明细 */
    {
        iResult=totalProc_write( lXmlhandle,iTotalNum,dTotalAmt,destfp,BATCH_TOTAL_TAIL,sFileType,t_fileTotalSortList,t_fileColumnList);
        if( iResult < 0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC,iResult));
            iAbort=8;
        }
    }

    fclose(destfp);
    fclose(srcfp);
    unlink(sTmpFileName);

    /* 释放链表资源  */
    batch_totalsortlistFree();
    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_maplistFree();

    /* 处理异常 */
    if( iAbort )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 生成重提文件处理错误: [%d]",iAbort),"ERROR");
        unlink(sFileFullName);
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,MSG_SYS_COMPEXEC);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPSTATUS_FAIL;
    }

    /* 设置文件信息 */
    /* 文件内笔数 */
    COMP_SOFTSETXML( XMLNM_BATCH_REQ_ZBS, itoa( iTotalNum ) );
    /* 文件内交易金额 */
    sprintf( sBuf, "%.2f", dTotalAmt );
    COMP_SOFTSETXML(  XMLNM_BATCH_REQ_ZJE, sBuf );

    LOG(LM_DEBUG,Fmtmsg("BATCH:数据重提,文件名称[%s],总笔数[%d],总金额[%.2f]",\
        sFileBasicName,iTotalNum,dTotalAmt),"DEBUG")

    /*文件格式*/
    memset(sFileTypeReal, 0x00, sizeof(sFileTypeReal));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILETYPE, sFileTypeReal)
    /*文件编码格式*/
    memset(sCodeFmt, 0x00, sizeof(sCodeFmt));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_CODEFMT, sCodeFmt)
    LOG(LM_STD,Fmtmsg("BATCH: 数据重提转换编码格式,文件类型[%s] 文件格式[%s] 编码格式[%s]", 
        sFileTypeReal, sFileType, sCodeFmt ),"INFO")
    if ( sFileTypeReal[0] == '0')
    {/*0-文本格式,才需要转换*/
        if ( sCodeFmt[0] == '1')
        {/*1-UTF-8格式*/
            iRet=fpub_convFileFmt(sFileFullName, &iFileLen, 1);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 文件编码格式[%s]转换失败[%d] ", "UTF-8", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "UTF-8"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }else if ( sCodeFmt[0] == '2')
        {/*2-BASE64格式*/
            iRet=fpub_convFileFmt(sFileFullName, &iFileLen, 3);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 文件编码格式[%s]转换失败[%d] ", "BASE64", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "BASE64"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }
    }

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
