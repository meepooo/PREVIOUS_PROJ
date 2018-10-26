/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:中间业务平台项目(BATCH2.0)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_PQUERY.c
文件描述:代收付分页查询组件集合
项 目 组:
程 序 员:yd@hundsun.com
发布日期:2012年7月22日

程 序 员:yd@hundsun.com
发布日期:2013年3月8日
修改内容:扩展明细查询条件

程 序 员:yd@hundsun.com
发布日期:2013年6月1日
修改内容:修改批次状态查询,处理失败任务没有登记文件信息情况

程 序 员:YangDong
修改日期:20141018
修改说明:DCI改造
*********************************************************************/
#include "gaps_head.h"
#include "batch_head.h"

#define SOCOMPVERSION "V4.1.0.1"
#define SOCOMPBUILDNO BUILDDATETIME

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_PQUERY.so</soname>\
        <sosrcname>BAT_PQUERY.c</sosrcname>\
        <sonote>BATCH批量业务明细分页查询</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2012-7-1 15:08\" programer=\"YangDong\" filesize=\"1591618\">HS-AgentV2.1整理</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2013-3-8 15:08\" programer=\"YangDong\" filesize=\"1591618\">扩展明细查询条件</rec>\
        <rec ver=\"2.1.0.3\" modify=\"2013-6-1 15:08\" programer=\"YangDong\" filesize=\"1591618\">修改批次状态查询,处理失败任务没有登记文件信息情况</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1591618\">DCI改造</rec>\
        </version>\
        </root>";
    printf("\n================动态组件基本信息================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" 取详细信息失败...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" 请查看详细信息...\n");
    return 0;
}

/**********************************************************************
组件函数: SBATCH_PQUERY
组件名称: 支持外围单表分页查询功能,必须遵循接口设计
组件参数：
输入参数：
输出参数：
处理说明: 支持外围分页查询功能
          参数配置：
                    外围上翻时必须送上次应答的上翻ID.
                    外围下翻时必须送上次应答的下翻ID.          
*************************************************************************/
IRESULT SBATCH_PQUERY(HXMLTREE lXmlhandle)
{
    char sQrySql[1024];
    /*int  iCurrent = 0;*/
    char sTable[32+1];
    char sQuyTable[32+1];
    char sTableCol[16+1];
    char sTableColName[40+1];
    char sMapID[64+1];
    char sSql1[1024];
    char sDbType[128];
    
    int  i,iParas,iRet;
    char sYwbh[16+1];
    char sShpch[32+1];
    char sPtpch[16+1];
    char sPkrq[8+1];
    char sYhzh[32+1];
    char sYhh1[32+1]; /* 用户号 */
    char sCxbz[1+1];  /* 查询标志 0-当前表（默认） 1－历史表 */
    char sCgbz[1+1];  /* 成功标志 */
    char sXym[16+1];  /* 响应码 */
    char sCxzd1[16+1];/* 扩展查询字段1 */
    char sCxzd2[16+1];/* 扩展查询字段2 */
    char sCxzd3[16+1];/* 扩展查询字段3 */
    char sCxtj1[32+1];/* 扩展查询条件1 */
    char sCxtj2[32+1];/* 扩展查询条件2 */
    char sCxtj3[32+1];/* 扩展查询条件3 */
    char errmsg[512];
    char sBuf[512+1];
    char sLinebuf[BATCH_MAX_FILELINE_BYTE+1];
    char sLsh[8+1];
    char sFhgs[1+1];
    char sFldList[512+1];
    char sFldName[2048+1];
    char sCondSql[512+1];
    char querycol[512+1];
    char countsql[512+1];
    char sQuerySql[2048];
    char querydirect[1+1];
    char querynum[3+1];
    char queryoffset[8+1];
    long lResult;
    char sFilePath[128+1],sFileName[128+1];
    char sFileFullName[256+1];
    char sFileFullName2[256+2];
    char sFileName2[128+2];
    int iSqllen=0;
    int iCount=0/*, iSeqnum=0*/;
    int iPageNum = 0;
    int maxRowID,minRowID;
    FILE * fp;
    FILE * fp2;
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle);
                      
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG"); 
       
    /*组件参数检查*/
    COMP_PARACOUNTCHKMIN(3)
    
    memset(sBuf, 0, sizeof(sBuf));
    memset(querydirect, 0, sizeof(querydirect));
    COMP_GETPARSEPARAS(1,sBuf,"查询方向: 0首次:1上翻:2下翻") 
    trim(sBuf);
    strncpy(querydirect, sBuf, sizeof(querydirect)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    memset(querynum, 0, sizeof(querynum));
    COMP_GETPARSEPARAS(2,sBuf,"最大记录数")
    trim(sBuf);
    strncpy(querynum, sBuf, sizeof(querynum)-1);
    
    memset(queryoffset, 0, sizeof(queryoffset));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"上次查询ID")
    trim(sBuf);
    strncpy(queryoffset, sBuf, sizeof(queryoffset)-1);
    
    memset(sFhgs, 0, sizeof(sFhgs));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"返回格式 " ); /*:1 不带字段信息（默认） 2 首行字段名 3 首行字段名,次行字段说明 */
    trim(sBuf);
    strncpy(sFhgs, sBuf, sizeof(sFhgs)-1);

    iPageNum = atoi( querynum );
    if( iPageNum <= 0 )
        iPageNum = 20;  /* 默认每次查询返回20条 */

    memset(sTable, 0, sizeof(sTable));
    COMP_HARDGETXML( "/batch/wwmapinfo/ywbm",sTable );
    memset(sYwbh, 0, sizeof(sYwbh));
    COMP_SOFTGETXML( "/batch/req/ywbh",sYwbh );

    /* 平台批次号 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sPtpch, 0, sizeof(sPtpch));
    COMP_SOFTGETXML( "/batch/req/ptpch",sBuf);
    strncpy(sPtpch, sBuf, sizeof(sPtpch)-1);

    /* 商户批次号 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sShpch, 0, sizeof(sShpch));
    COMP_SOFTGETXML( "/batch/req/shpch",sBuf);
    strncpy(sShpch, sBuf, sizeof(sShpch)-1);

    /* 批扣日期 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sPkrq, 0, sizeof(sPkrq));
    COMP_SOFTGETXML( "/batch/req/pkrq",sBuf );
    strncpy(sPkrq, sBuf, sizeof(sPkrq)-1);

    /* 银行账号 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sYhzh, 0, sizeof(sYhzh));
    COMP_SOFTGETXML( "/batch/req/yhzh",sBuf);
    strncpy(sYhzh, sBuf, sizeof(sYhzh)-1);

    /* 用户编号 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sYhh1, 0, sizeof(sYhh1));
    COMP_SOFTGETXML( "/batch/req/yhh1",sBuf);
    strncpy(sYhh1, sBuf, sizeof(sYhh1)-1);

    /* 查询标志 0-当前表(默认) 1-历史表 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sCxbz, 0, sizeof(sCxbz));
    COMP_SOFTGETXML( "/batch/req/cxbz",sBuf);
    strncpy(sCxbz, sBuf, sizeof(sCxbz)-1);

    /* 成功标志 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sCgbz, 0, sizeof(sCgbz));
    COMP_SOFTGETXML( "/batch/req/cgbz",sBuf);
    strncpy(sCgbz, sBuf, sizeof(sCgbz)-1);
    
    /* 响应码 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sXym, 0, sizeof(sXym));
    COMP_SOFTGETXML( "/batch/req/xym",sBuf);
    strncpy(sXym, sBuf, sizeof(sXym)-1);

    /* 扩展的查询字段名和查询条件名 */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sCxtj1, 0, sizeof(sCxtj1));
    COMP_SOFTGETXML( "/batch/req/cxtj1",sBuf);
    strncpy(sCxtj1, sBuf, sizeof(sCxtj1)-1);

    memset(sBuf, 0, sizeof(sBuf));
    memset(sCxtj2, 0, sizeof(sCxtj2));
    COMP_SOFTGETXML( "/batch/req/cxtj2",sBuf);
    strncpy(sCxtj2, sBuf, sizeof(sCxtj2)-1);

    memset(sBuf, 0, sizeof(sBuf));
    memset(sCxtj3, 0, sizeof(sCxtj3));
    COMP_SOFTGETXML( "/batch/req/cxtj3",sBuf);
    strncpy(sCxtj3, sBuf, sizeof(sCxtj3)-1);

    /* 查询标志 1-历史表 0-当前表（默认） */
    if( sCxbz[0] == '1' )
    {
        /* 表名规则 BATCH_打头，历史表名为BATCH_HIS打头 */
        memset(sQuyTable, 0, sizeof(sQuyTable));
        snprintf( sQuyTable, sizeof( sQuyTable ), "BATCH_HIS_%s", sTable + 6 );
    }
    else
        strcpy( sQuyTable, sTable );

    sprintf( sCondSql ," WHERE 1= 1 " );
    if( strlen( trim( sYwbh ) ) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND ywbh='%s' " , sYwbh );
        strcat( sCondSql, sBuf );
    }

    if( strlen( trim( sPkrq )) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND pkrq ='%s' " , sPkrq );
        strcat( sCondSql, sBuf );
    }
   
    if( strlen( trim( sPtpch)) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND ptpch ='%s' " , sPtpch );
        strcat( sCondSql, sBuf );
    }

    if( strlen( trim( sYhzh )) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND yhzh ='%s' " , sYhzh );
        strcat( sCondSql, sBuf );
    }

    if( strlen( trim( sShpch) ) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND  ptpch IN ( SELECT ptpch FROM batch_wbwjdj WHERE shpch ='%s' ) " , sShpch );
        strcat( sCondSql, sBuf );
    }

    if( strlen( trim( sYhh1 )) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND yhh1 ='%s' " , sYhh1 );
        strcat( sCondSql, sBuf );
    }

    if( strlen( trim( sCgbz )) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND cgbz='%s' " , sCgbz);
        strcat( sCondSql, sBuf );
    }

    if( strlen( trim( sXym )) > 0 )
    {
        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND xym='%s' " , sXym );
        strcat( sCondSql, sBuf );
    }

    /* 扩展查询条件 */
    if( strlen( trim( sCxtj1 )) > 0 )
    {
        memset(sBuf, 0, sizeof(sBuf));
        memset(sCxzd1, 0, sizeof(sCxzd1));
        COMP_SOFTGETXML( "/batch/req/cxzd1",sBuf);
        strncpy(sCxzd1, sBuf, sizeof(sCxzd1)-1);

        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND %s='%s' " , sCxzd1, sCxtj1 );
        strcat( sCondSql, sBuf );
    }

    /* 扩展查询条件 */
    if( strlen( trim( sCxtj2 )) > 0 )
    {
        memset(sBuf, 0, sizeof(sBuf));
        memset(sCxzd2, 0, sizeof(sCxzd2));
        COMP_SOFTGETXML( "/batch/req/cxzd2",sBuf);
        strncpy(sCxzd2, sBuf, sizeof(sCxzd2)-1);

        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND %s='%s' " , sCxzd2, sCxtj2 );
        strcat( sCondSql, sBuf );
    }

    /* 扩展查询条件 */
    if( strlen( trim( sCxtj3 )) > 0 )
    {
        memset(sBuf, 0, sizeof(sBuf));
        memset(sCxzd3, 0, sizeof(sCxzd3));
        COMP_SOFTGETXML( "/batch/req/cxzd3",sBuf);
        strncpy(sCxzd3, sBuf, sizeof(sCxzd3)-1);

        memset( sBuf, 0x00, sizeof( sBuf ) );
        sprintf( sBuf, " AND %s='%s' " , sCxzd3, sCxtj3 );
        strcat( sCondSql, sBuf );
    }

    iSqllen = strlen( sCondSql );
    if( iSqllen > 512 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_QUERY_COLERR,MSG_BATCH_QUERY_COLERR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iCount=0;
    if( querydirect[0] =='2' )       /* 下翻  */
    {
        maxRowID = iPageNum + atoi(queryoffset);
        minRowID = atoi(queryoffset)+1;
    }
    else if( querydirect[0] =='1' )  /* 上翻  */
    {
        maxRowID = atoi(queryoffset)-1;
        minRowID = maxRowID-iPageNum+1;
        if( minRowID < 0 )
            minRowID = 0;
    }
    else                            /* 默认首次查询 */
    {
        /* 计算记录总数 */
        memset(countsql, 0, sizeof(countsql));
        sprintf(countsql, "SELECT COUNT(*) FROM %s %s ", sQuyTable, sCondSql );
        iRet = prv_CntSql( countsql, &iCount, errmsg);
        if( iRet == -1 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 获取统计信息失败,sql[%s],\
                SQLERR=[%s] [%d]", sSql1, DCILastError(), iRet ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        LOG(LM_DEBUG,Fmtmsg("记录总数: [%ld]",iCount),"DEBUG");
        /* 无查询记录 */
        if ( iCount <=0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 获取统计信息失败,sql[%s]",  countsql ),"ERROR");
            fpub_SetMsg(lXmlhandle, MID_SQL_NOTFOUND, MSG_SQL_NOTFOUND );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        /* 总记录数 */
        COMP_HARDSETXML("/batch/resp/zbs",itoa(iCount));
        maxRowID = iPageNum;
        minRowID = 1;
    }
 
    /*返回文件名*/
    memset( sLsh, 0x00, sizeof( sLsh ) );
    COMP_HARDGETXML( XMLNM_ZHQZLSH,sLsh );
    memset(sFileName, 0, sizeof(sFileName));
    memset(sFileFullName, 0, sizeof(sFileFullName));
    sprintf( sFileName,"batch_mxcx_%s%s.txt" , sYwbh,sLsh );
    COMP_HARDSETXML( "/batch/resp/wjmc", sFileName);
    sprintf( sFilePath,"%s/tmp" ,  getenv( "HOME" ) );
    COMP_HARDSETXML( "/batch/resp/wjlj", sFilePath);
    sprintf( sFileFullName, "%s/%s", sFilePath, sFileName );
    
    /*单表分页查询模式*/
    memset(sQrySql, 0, sizeof(sQrySql));

    /* 获取该业务明细表字段信息 */
    memset( querycol, 0, sizeof( querycol ));
    memset(sTableCol, 0, sizeof(sTableCol));
    memset(sTableColName, 0, sizeof(sTableColName));
    memset( sFldList, 0, sizeof( sFldList ));
    memset( sFldName, 0, sizeof( sFldName));

    COMP_HARDGETXML( "/batch/wwmapinfo/mapid",sMapID);

    snprintf( sSql1, sizeof( sSql1 ), "SELECT a.columnid , b.fldname  FROM batch_filemap a, app_tablereg b\
        WHERE a.mapid='%s' AND a.columnid=b.fldid AND b.tablename='%s' AND a.flxh=0 ORDER BY a.columnsn", sMapID, sTable );
    if ((cur = DCIDeclareCursor( sSql1, 0)) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("数据库操作失败[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("数据库操作失败[%s]",DCILastError()),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iCount = 0;
    while( ( iRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0) ) > 0 )
    {
        sprintf( sTableCol, "%s", DCIFieldAsString( cur, 0 ) );
        sprintf( sTableColName, "%s", DCIFieldAsString( cur, 0 ) );

        trim(sTableCol);
        trim(sTableColName);

        strcat( querycol, sTableCol );
        strcat( querycol,"," );
        iCount ++;
        /* 字段信息 */
        if( sFhgs[0] != '1' &&  sFhgs[0] != '\0' &&  sFhgs[0] != ' ' )  /* 返回字段信息 */
        {
            if( sFhgs[0] == '2' || sFhgs[0] == '4' ) /* 返回字段名 */
            {
                strcat( sFldList, sTableCol );  
                strcat( sFldList, "|");  
            }
            if( sFhgs[0] == '3' || sFhgs[0] == '4' ) /* 返回字段名 */
            {
                strcat( sFldName, sTableColName );  
                strcat( sFldName, "|");  
            }
        }
        memset( sTableCol,0,sizeof( sTableCol ));
        memset( sTableColName,0,sizeof( sTableColName ));
    }
    DCIFreeCursor(cur);
    if( iRet == -1 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 获取外部文件信息失败,sql[%s],\
            SQLERR=[%s] [%d]", sSql1, DCILastError(), iRet ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if( iCount < 1 )
    {
        LOG(LM_STD,Fmtmsg("无需要查询返回字段配置"),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_QUERY_COLERR,MSG_BATCH_QUERY_COLERR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 去除最后一个' */
    iSqllen = strlen( querycol );
    if( iSqllen > 512 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_QUERY_COLERR,MSG_BATCH_QUERY_COLERR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    querycol[iSqllen - 1] = '\0';

    memset( sDbType, 0x00, sizeof( sDbType ) );
    sprintf(sDbType, "%s", getenv("DB"));
    trim( sDbType );

    if( memcmp( sDbType,"ORACLE",6 ) == 0 )
        sprintf( sQuerySql,"SELECT %s FROM ( SELECT ROWNUM RN, A.*  FROM ( SELECT %s FROM %s %s ) A WHERE ROWNUM <= %d ) WHERE RN >= %d",\
            querycol, querycol, sQuyTable , sCondSql, maxRowID, minRowID );
    else if( memcmp( sDbType,"DB2",3 ) == 0 )
        sprintf( sQuerySql,"SELECT %s FROM( SELECT ROW_NUMBER() OVER (ORDER BY pkrq, ptpch, lsxh ) AS RN, A.* \
            FROM ( SELECT %s FROM %s %s ) AS A ) AS TEMP where TEMP.RN <=%d AND TEMP.RN >= %d",\
            querycol, querycol, sTable,sCondSql, maxRowID, minRowID );
    else if( memcmp( sDbType,"INFORMIX",8 ) == 0 )
        sprintf( sQuerySql,"SELECT SKIP %d FIRST %d %s FROM %s %s",\
            minRowID, iPageNum, querycol, sTable , sCondSql );

    if ( sql_UnloadToFile(sFileFullName,sQuerySql,'|','\\',&lResult) != MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("querySql=[%s]",sQuerySql),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if( sFhgs[0] != '1' &&  sFhgs[0] !=  '\0' &&  sFhgs[0] != ' ' )  /* 返回字段信息 */
    {
        memset( sFileName2, 0x00, sizeof( sFileName2 ) );
        sprintf( sFileName2, "%s2", sFileName );
        COMP_HARDSETXML( "/batch/resp/wjmc", sFileName2);
        sprintf( sFileFullName2, "%s2", sFileFullName );
        if( ( fp = ( fopen( sFileFullName, "r" ) ) ) == NULL )
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_OPENFILE,"打开文件失败" );
            LOG(LM_STD,Fmtmsg("打开文件[%s]失败,err[%s]",sFileFullName, strerror(errno) ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if( ( fp2 = ( fopen( sFileFullName2, "w+" ) ) ) == NULL )
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_OPENFILE,"打开文件失败" );
            LOG(LM_STD,Fmtmsg("打开文件[%s]失败,err[%s]",sFileFullName2, strerror(errno) ),"ERROR");
            fclose( fp );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if( sFhgs[0] == '2' || sFhgs[0] == '4' ) /* 返回字段名 */
        {
            fprintf( fp2, "%s", sFldList );
            fprintf( fp2, "\n" );
        }
        if( sFhgs[0] == '3' || sFhgs[0] == '4' ) /* 返回字段说明 */
        {
            fprintf( fp2,"%s", sFldName);
            fprintf( fp2, "\n" );
        }
        memset( sLinebuf, 0x00, sizeof( sLinebuf ) );
        while( fgets( sLinebuf, BATCH_MAX_FILELINE_BYTE, fp ) != NULL    )
        {
            fprintf( fp2, sLinebuf );
            memset( sLinebuf, 0x00, sizeof( sLinebuf ) );
        }
        iRet = fclose( fp );
        iRet = fclose( fp2 );
    }

    /* 本页数 */
    COMP_HARDSETXML( "/batch/resp/ynbs", itoa( lResult ) );
    /* 首记录ID */
    COMP_HARDSETXML("/batch/resp/firstid", itoa( minRowID ) );
    /* 尾记录ID */
    COMP_HARDSETXML("/batch/resp/lastid", itoa( maxRowID ) );
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}

/**********************************************************************
组件函数: BATCH_STATUS_QUERY
组件名称: 根据输入条件，查询批次状态
组件参数：
输入参数：
输出参数：
处理说明: 
*************************************************************************/
IRESULT SBATCH_STATUS_QUERY(HXMLTREE lXmlhandle)
{
    char sQuerySql[1024];
    BATCH_PLRW sdb_batch_plrw;
    BATCH_WBWJDJ sdb_batch_wbwjdj;
    
    int  i,iParas,iCount;
    char sYwbh[16+1];
    char sShpch[32+1];
    char sPtpch[16+1];
    char sPkrq[8+1];
    char sPkrq_b[8+1];
    char sPkrq_e[8+1];
    char sCondSql[768];
    char countsql[1024];
    char sXmlNode[64];
    char errmsg[128];
    char sTmp[64];
    int  iRet = -1;
    char sErrmsg[512];
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle);
                      
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")  
       
    /*查询条件获取*/

    /* 业务编号 */
    COMP_SOFTGETXML( "/batch/req/ywbh",sYwbh );
    /* 平台批次号 */
    COMP_SOFTGETXML( "/batch/req/ptpch",sPtpch );
    /* 商户批次号 */
    COMP_SOFTGETXML( "/batch/req/shpch",sShpch );
    /* 批扣日期 */
    COMP_SOFTGETXML( "/batch/req/pkrq",sPkrq );
    /* 批扣开始日期 */
    COMP_SOFTGETXML( "/batch/req/pkrq_begin",sPkrq_b );
    /* 批扣结束日期 */
    COMP_SOFTGETXML( "/batch/req/pkrq_end",sPkrq_e );
    
    sprintf( sCondSql ," WHERE 1= 1 " );
    if( strlen( trim( sYwbh ) ) > 0 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " AND ywbh='%s' " , sYwbh );
        strcat( sCondSql, sTmp );
    }

    if( strlen( trim( sPkrq )) > 0 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " AND pkrq ='%s' " , sPkrq );
        strcat( sCondSql, sTmp );
    }
   
    if( strlen( trim( sPtpch)) > 0 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " AND ptpch ='%s' " , sPtpch );
        strcat( sCondSql, sTmp );
    }

    if( strlen( trim( sShpch) ) > 0 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " AND shpch ='%s' ", sShpch );
        strcat( sCondSql, sTmp );
    }

    /* 查询正常批次信息 */
    sprintf( sQuerySql,"SELECT * FROM batch_plrw %s", sCondSql );
    if ((cur = DCIDeclareCursor(sQuerySql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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
    memset( &sdb_batch_plrw,0,sizeof( sdb_batch_plrw ));
    i = 0;
    while( ( iRet = DBFetch(cur, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg ) ) > 0 )
    {
        i ++; 

        if ( i > 500 ) /* 限制最大返回记录数，此情形应该不常见 */
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_NOTFOUND, "查询返回记录数超过限制，请检查查询条件" );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        /* 批扣日期 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pkrq", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.pkrq);

        /* 批次号 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ptpch", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.ptpch);

        /* 商户批次号  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shpch", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.shpch);

        /* 业务编号 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ywbh", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.ywbh);

        /* 单位编号  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dwbh", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.dwbh);

        /* 实际总金额 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzje", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%.2f", sdb_batch_plrw.sjzje );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* 实际总笔数 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzbs", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_plrw.sjzbs );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* 成功总金额 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzje", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%.2f", sdb_batch_plrw.cgzje );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* 成功总笔数 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzbs", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_plrw.cgzbs );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* 失败总金额 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzje", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%.2f", sdb_batch_plrw.sbzje );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* 失败总笔数 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzbs", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_plrw.sbzbs );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* 来盘文件名  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/lpwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.lpwjm);

        /* 成功回盘文件名(默认) */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shcgwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.shcgwjm);

        /* 失败回盘文件名 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shsbwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.shsbwjm);

        /* 当前步点 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dqbd", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.dqbd);

        /* 步点状态  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/bdzt", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.bdzt);

        /* 任务状态 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/rwzt", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.rwzt);

        /* 响应码 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xydm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.xydm );

        /* 响应信息 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xyxx", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.xyxx );

        /* 对已发起批量任务，不返回外部文件表登记信息 */
        /* 登记日期 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djrq", i );
        COMP_SOFTSETXML(sXmlNode, " ");

        /* 登记流水号 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djlsh", i );
        COMP_SOFTSETXML(sXmlNode, " ");

        /* 批次状态 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pczt", i );
        COMP_SOFTSETXML(sXmlNode, " ");

        /* 审核状态 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shzt", i );
        COMP_SOFTSETXML(sXmlNode, " ");

        memset( &sdb_batch_plrw,0,sizeof( sdb_batch_plrw ));
    }
    DCIFreeCursor(cur);
    if ( iRet == -1 )
    {
        LOG(LM_DEBUG,Fmtmsg("sql: [%s]", sQuerySql ),"DEBUG");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 查询未发起的任务信息 */
    memset( sQuerySql, 0x00, sizeof( sQuerySql ) );
    sprintf( sQuerySql,"SELECT djrq,djlsh,shpch,ywbh,lpwjm,shzt, pczt\
        FROM batch_wbwjdj  a %s  AND ( ptpch IS NULL OR ptpch='' OR ptpch=' ')", sCondSql );
    if ((cur = DCIDeclareCursor(sQuerySql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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

    memset( &sdb_batch_wbwjdj,0,sizeof( sdb_batch_wbwjdj ));
    while( ( iRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0) ) > 0 )
    {
        i ++; 

        sprintf( sdb_batch_wbwjdj.djrq, "%s", DCIFieldAsString( cur, 0 ) );
        sdb_batch_wbwjdj.djlsh = atoi( DCIFieldAsString( cur, 1 ) );
        sprintf( sdb_batch_wbwjdj.shpch, "%s", DCIFieldAsString( cur, 2 ) );
        sprintf( sdb_batch_wbwjdj.ywbh, "%s", DCIFieldAsString( cur, 3 ) );
        sprintf( sdb_batch_wbwjdj.lpwjm, "%s", DCIFieldAsString( cur, 4 ) );
        sprintf( sdb_batch_wbwjdj.shzt, "%s", DCIFieldAsString( cur, 5 ) );
        sprintf( sdb_batch_wbwjdj.pczt, "%s", DCIFieldAsString( cur, 6 ) );

        /* added by yangdong 20130601 未提交任务，批次信息赋值为空，与前面的查询节点保持一致 */
        /* 批扣日期 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pkrq", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 批次号 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ptpch", i );
        COMP_SOFTSETXML(sXmlNode, "" );
        
        /* 商户批次号  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shpch", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.shpch);

        /* 业务编号 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ywbh", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.ywbh);

        /* 单位编号  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dwbh", i );
        COMP_SOFTSETXML(sXmlNode, "");

        /* 实际总金额 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzje", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 实际总笔数 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzbs", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 成功总金额 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzje", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 成功总笔数 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzbs", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 失败总金额 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzje", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 失败总笔数 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzbs", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 来盘文件名  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/lpwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.lpwjm);

        /* 成功回盘文件名(默认) */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shcgwjm", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 失败回盘文件名 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shsbwjm", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 当前步点 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dqbd", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 步点状态  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/bdzt", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 任务状态 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/rwzt", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 响应码 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xydm", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 响应信息 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xyxx", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* 登记日期 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djrq", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.djrq);

        /* 登记流水号 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djlsh", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_wbwjdj.djlsh );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* 批次状态 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pczt", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.pczt);

        /* 审核状态 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shzt", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.shzt);

        memset( &sdb_batch_wbwjdj,0,sizeof( sdb_batch_wbwjdj ));
    }
    DCIFreeCursor(cur);
    if ( iRet == -1 )
    {
        LOG(LM_DEBUG,Fmtmsg("sql: [%s]", sQuerySql ),"DEBUG");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("记录总数: [%ld] 查询条件[%s]",i, sCondSql ),"DEBUG");
    /* modified by yangdong 20130601 */
    COMP_HARDSETXML("/batch/resp/zbs",itoa(i));

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}
