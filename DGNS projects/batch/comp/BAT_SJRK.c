/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_SJRK.c
文件描述: 批量业务处理文件映射-数据入库处理转换组件集
项 目 组:中间业务平台项目组
程 序 员:YangDong
修改日期:2011-8-1

程 序 员:YangDong
修改日期:2014-10-18
*********************************************************************/
#include "gaps_head.h"
#include <sys/time.h>
#include <sys/timeb.h>
#include "app_head.h"
#include "batch_head.h"

#define SOCOMPVERSION "V4.1.0.1"

static struct timeb starttime,endtime;

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_SJRK.so</soname>\
        <sosrcname>BAT_SJRK.c</sosrcname>\
        <sonote>BATCH数据入库组件集合</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"YangDong\" filesize=\"1128297\">HS-AgentV2.1整理</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1128297\">DCI改造</rec>\
        <rec ver=\"4.1.0.2\" modify=\"2016-08-10 13:08\" programer=\"Tuql\" filesize=\"1128297\">增加对域包含特殊字符的检查</rec>\
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

IRESULT sql_LoadFromFile_b(char* sFilename, char *sTname, char cDiv, char cEscape, long *lResult);

/*
 * 获取文件列配置信息
*/
int getFileColumn(BATCH_FILECOLUMN *pFileColumn,BATCH_FILEMAP *pFileMap,BATCH_FILESORT *pFileSort)
{
    int colflag=0;

    for( pfileColumnIter = i_list_begin(t_fileColumnList);
              pfileColumnIter!= i_list_end(t_fileColumnList);
                   pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        if( pFileSort->fileclasssn == gSFileColumn->fileclasssn )
        {
            trim(gSFileColumn->columnid);
            /* 找到该列属性(来源文件位置=列序号) */
            if( gSFileColumn->columnsn == atoi( pFileMap->lywz ) )
            {
                colflag=1;
                memcpy(pFileColumn,(BATCH_FILECOLUMN *)(pfileColumnIter->data),sizeof(BATCH_FILECOLUMN));
                break;
            }
        }
    }
    return colflag;
}

/* 汇总处理 */
int totalProc(HXMLTREE lXmlhandle,char *lineBuf, BATCH_FILESORT *pFileSort)
{
    int count=-1;
    char sTmpStr[128];
    char xmlCont[128];
    char sDiv[BATCH_MAXLEN_DIV+1];
    char xmlNode[258];
    double     dTmp=0.00;
    char sFmt[32];

    int  iLen = 0;
    int    i = 0, j = 0, position = 0;
    int  iLineField = 0;
    int  iSplitLine = 0;
    char tmpBuf[128];

    /* 处理结尾的换行回车 */
    iLen = strlen( lineBuf );
    if( lineBuf[iLen-1] == 10 || lineBuf[iLen-1] == 13    )
        lineBuf[iLen-1] = '\0';
    if( lineBuf[iLen-2] == 10 || lineBuf[iLen-2] == 13    )
        lineBuf[iLen-2] = '\0';

    if (pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT)
    {
       memset(sDiv, 0x00, sizeof(sDiv));
       iSplitLine = func_GetDiv( pFileSort->columnsprtr, ICXP_DIV, sDiv );
       iSplitLine=fprv_getDelimitCount(lineBuf, sDiv);
    }else if (pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL)
    {
       memset(sDiv, 0x00, sizeof(sDiv));
       iSplitLine = func_GetDiv( pFileSort->columnsprtr, ICXP_DIV, sDiv );
       iSplitLine=fprv_getDelimitCount(lineBuf, sDiv); 
       iSplitLine ++;
    }
    /* 取汇总分类的列配置信息进行处理 */
    for( pfileColumnIter = i_list_begin(t_fileColumnList); 
                 pfileColumnIter!= i_list_end(t_fileColumnList); 
                     pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        memset(sTmpStr, 0, sizeof(sTmpStr));          
        if( pFileSort->fileclasssn == gSFileColumn->fileclasssn ) /* 只处理汇总分类 */
        {
            iLineField ++;
            switch( pFileSort->columnflag[0] )
            {
                case BATCH_FILESORT_COLUNM_FIX:    /* 定长 */
                    memcpy(sTmpStr, lineBuf+gSFileColumn->offset-1,gSFileColumn->columnlen);
                    break;
                case BATCH_FILESORT_COLUNM_SPLIT_TAIL: /* 去尾分隔符 */

                case BATCH_FILESORT_COLUNM_SPLIT: /* 分隔符 */
                    trim(pFileSort->columnsprtr);
                    if( pFileSort->columnsprtr[0] == 0 )
                    {
                        fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
                            Fmtmsg("BATCH: 非法分隔符[%s]", pFileSort->columnsprtr) );
                        LOG(LM_STD,Fmtmsg("BATCH: 非法分隔符[%s]", pFileSort->columnsprtr ),"ERROR")
                        return -1;
                    }
                    
                    fprv_getSubStr(lineBuf, gSFileColumn->columnsn, pFileSort->columnsprtr, sTmpStr);
                    break;
                default:  
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
                            Fmtmsg("BATCH: 列分割标识非法[%s]", pFileSort->columnflag) );
                    LOG(LM_STD,Fmtmsg("BATCH: 列分割标识非法[%s]", pFileSort->columnflag),"ERROR")
                    count=-1;
                    return count;
            }

            if( gSFileColumn->izoom != 0 )  /* 如果有偏移,计算偏移后数值 */
            {
                dTmp=atof(sTmpStr)*pow(10,-gSFileColumn->izoom);
                if( gSFileColumn->iprecision < 1 )
                    gSFileColumn->iprecision = 2;  /* 默认小数精度2 */
                sprintf(sFmt,"%%.%df",gSFileColumn->iprecision);
                snprintf(sTmpStr, sizeof( sTmpStr ), sFmt,dTmp);
            }
             /* 处理填充字符 */
            if ( gSFileColumn->ifiller > 0 && gSFileColumn->columnlen > 0 )  
            {
                memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
                strcpy( tmpBuf, sTmpStr );
                position = gSFileColumn->columnlen; 
                if ( gSFileColumn->regular[0] == 'R' )   /* 右对齐 */
                {
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* 查找有效字符开始位置 */
                         if( tmpBuf[i] != gSFileColumn->ifiller )
                         {
                             position = i; 
                             break;
                         }
                    } 
                    memset( sTmpStr, 0x00, sizeof( sTmpStr ) );
                    memcpy( sTmpStr, tmpBuf+position, gSFileColumn->columnlen - position );
                    sTmpStr[ gSFileColumn->columnlen -  position] = '\0';
                }
                else if ( gSFileColumn->regular[0] == 'L' )   /* 左对齐 */
                {
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* 查找填充字符开始位置 */
                         if( tmpBuf[i] == gSFileColumn->ifiller )
                         {
                             position = i; 
                             break;
                         }
                    } 
                    memset( sTmpStr, 0x00, sizeof( sTmpStr ) );
                    memcpy( sTmpStr, tmpBuf, position );
                    sTmpStr[position] = '\0';
                }
                else /* 不设置对齐方式 */
                {
                    j = 0;
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* 查找非填充字符 */
                         if( tmpBuf[i] != gSFileColumn->ifiller )
                         {
                             sTmpStr[j++]= tmpBuf[i] ; 
                         }
                    } 
                    sTmpStr[j] = '\0';
                }
            }

            /* 处理列属性 */
            if( ( 0 != gSFileColumn->lsx[0] ) && strlen(gSFileColumn->lsx) ) 
            {
                if( strcmp(gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_SETXML) == 0) /* 列属性，设置xml*/
                {
                    trim( gSFileColumn->fldref );
                    memset(xmlNode,0,sizeof(xmlNode));
                    if( gSFileColumn->fldref[0] == '/')
                    {
                        snprintf( xmlNode, sizeof( xmlNode ), "%s",gSFileColumn->fldref );
                    }
                    else
                    {
                        snprintf( xmlNode, sizeof( xmlNode ),  "/batch/%s",gSFileColumn->fldref );
                    }
                    COMP_SOFTSETXML(xmlNode, sTmpStr );
                }
                else if( strcmp(gSFileColumn->lsx, BATCH_FILECOLUMN_LSX_ZBS) == 0) /* 列属性，总笔数 */
                {
                    COMP_SOFTSETXML(XMLNM_BATCH_HZ_ZBS,sTmpStr);        
                    LOG(LM_STD,Fmtmsg("BATCH: 来盘文件总笔数[%s]",sTmpStr),"INFO")
                }
                else if( strcmp(gSFileColumn->lsx, BATCH_FILECOLUMN_LSX_ZJE) == 0) /* 列属性，总金额 */
                {
                    if ( strlen(sTmpStr) >= 15)
                    {
                        fpub_SetMsg(lXmlhandle,MID_BATCH_SJRK_SUMAMT,Fmtmsg(MSG_BATCH_SJRK_SUMAMT) );
                        LOG(LM_STD,Fmtmsg("BATCH: 文件解析失败(汇总金额超限)[%s]",sTmpStr),"ERROR")
                        count=-2;
                        return count; 
                    }
                    COMP_SOFTSETXML(XMLNM_BATCH_HZ_ZJE,sTmpStr);        
                    LOG(LM_STD,Fmtmsg("BATCH: 来盘文件总金额[%s]",sTmpStr),"INFO")
                }
                else if( strcmp(gSFileColumn->lsx, BATCH_FILECOLUMN_LSX_SHPCH ) == 0) /* 列属性 商户批次号 */
                {
                    COMP_SOFTSETXML(XMLNM_BATCH_REQ_SHPCH,sTmpStr);        
                    LOG(LM_STD,Fmtmsg("BATCH: 来盘文件商户批次号[%s]",sTmpStr),"INFO")
                }
                else
                {
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
                            Fmtmsg("BATCH: 列属性非法[%s]", gSFileColumn->lsx) );
                    LOG(LM_STD,Fmtmsg("BATCH: 列属性非法[%s]",gSFileColumn->lsx),"ERROR")
                    count=-2;
                    return count;         
                }
            }           
            /* 处理非空 */
            if ( gSFileColumn->isid[0] == '1' && sTmpStr[0] == '\0')
            {
                LOG(LM_STD,Fmtmsg("BATCH: 汇总第[%d-%s]列域非空为空[%s]",
                    gSFileColumn->columnsn, gSFileColumn->columnid,sTmpStr),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
                    Fmtmsg(MSG_BATCH_TOTALLINE_NOTNULL, gSFileColumn->columnsn, gSFileColumn->columnid) );
                count=-99;
                return count; 
            }
            count=0;
        }
    }
    if (iSplitLine>0 && iLineField != iSplitLine)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
            Fmtmsg(MSG_BATCH_TOTALLINE_COLS, iLineField, iSplitLine) );
        LOG(LM_STD,Fmtmsg("BATCH: 汇总行域数不符,配置%d列,实际%d列,[%s]",
            iLineField, iSplitLine, lineBuf),"ERROR")
        count=-2;
        return count;
    }
    
    return count;
}

/* 明细处理(配置保证注册表与映射表的序列一致性) */
int detailProc(HXMLTREE lXmlhandle, int cycNum, int iWjxh, char *inBuf, double *dTotal ,char *outbuf,BATCH_FILESORT *pFileSort)
{
    char sSql[512];
    char sFldValue[128];
    char fldCont[BATCH_MAX_FILE_COL_LEN];
    char sTmpStr[128];
    char sDiv[BATCH_MAXLEN_DIV+1];
    int  iLineField = 0;
    int  iSplitLine = 0;
    int  ret;
    char xmlNode[128];
    char itemBuf[BATCH_MAX_FILE_COL_LEN];
    double dTmp=0.00;
    char sFmt[128];
    char sCheckFlag[1+1];
    int    iTmp;
    int    iLen;
    int    iIsId = 0, iIsId2=0;
    int    iIsDetailCnts = 0;
    char   sIsIdFildName[32];
    int    i = 0, j = 0, position = 0;
    char tmpBuf[BATCH_MAX_FILE_COL_LEN];
    int   iFldCont=0, iSpeChar=0;

    memset(sCheckFlag, 0x00, sizeof(sCheckFlag));
    COMP_SOFTGETXML("/batch/checkelemflag", sCheckFlag)
    /* 默认 件最多32列,每个字段最长128个字符 */
    char sss[ BATCH_MAX_FILE_COL_NUM ][ BATCH_MAX_FILE_COL_LEN ];
    char *p=&sss[0][0];

    BATCH_FILECOLUMN thisColumn;

    /* 处理结尾的换行回车 */
    iLen = strlen( inBuf );
    if( inBuf[iLen-1] == 10 || inBuf[iLen-1] == 13    )
        inBuf[iLen-1] = '\0';
    if( inBuf[iLen-2] == 10 || inBuf[iLen-2] == 13    )
        inBuf[iLen-2] = '\0';

    /*先对明细域数做检查,要求跟配置完全保持一致*/
    if (pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT)
    {
       memset(sDiv, 0x00, sizeof(sDiv));
       iSplitLine = func_GetDiv( pFileSort->columnsprtr, ICXP_DIV, sDiv );
       iSplitLine=fprv_getDelimitCount(inBuf, sDiv);
    }else if (pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL)
    {
       memset(sDiv, 0x00, sizeof(sDiv));
       iSplitLine = func_GetDiv( pFileSort->columnsprtr, ICXP_DIV, sDiv );
       iSplitLine=fprv_getDelimitCount(inBuf, sDiv); 
       iSplitLine ++;
    }

    /* 取汇总分类的列配置信息进行处理 */
    for( pfileColumnIter = i_list_begin(t_fileColumnList); 
                 pfileColumnIter!= i_list_end(t_fileColumnList); 
                     pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        memset(sTmpStr, 0, sizeof(sTmpStr));          
        if( pFileSort->fileclasssn == gSFileColumn->fileclasssn ) /* 只处理明细分类 */
        {
            iLineField ++;
        }
    }
    if (iSplitLine>0 && iLineField != iSplitLine && sCheckFlag[0]=='1')
    {
        LOG(LM_STD,Fmtmsg("BATCH: 明细行域数不符,配置%d列,实际%d列,[%s]",
            iLineField, iSplitLine, inBuf),"ERROR")
        iIsDetailCnts = iSplitLine;
    }
    
    /* 分隔符模式，先把文件列内容全部解析到临时数组变量中 */   
    if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT ||
        pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL ) /* 去尾分隔符 */
    {
        memset( &sss, 0x00, BATCH_MAX_FILE_COL_NUM * BATCH_MAX_FILE_COL_LEN);
        trim( pFileSort->columnsprtr );
        if( pFileSort->columnsprtr[0] == 0 )
        {
           LOG(LM_STD,Fmtmsg("BATCH: 非法分隔符[%s]", pFileSort->columnsprtr ),"ERROR")
           return -1; 
        }
        fprv_GetAllSubstr( p, inBuf, pFileSort->columnsprtr, &iTmp );
    }

    /* 文件映射遍历 */
    for( pfileMapIter = i_list_begin(t_fileMapList); 
             pfileMapIter != i_list_end(t_fileMapList); 
             pfileMapIter = i_list_iter_next(pfileMapIter) )
    { 
        /* 取 文件映射链表 列映射信息 */
        gSFileMap = (BATCH_FILEMAP *)(pfileMapIter->data);
        memset(fldCont, 0, sizeof(fldCont));
/*
LOG(LM_DEBUG,Fmtmsg("columnid[%s] ", gSFileMap->columnid),"INFO");
LOG(LM_DEBUG,Fmtmsg("lylx[%s] ", gSFileMap->lylx ),"INFO");
*/
        switch( gSFileMap->lylx[0] )
        {
            case BATCH_FILEMAP_LYLX_FILE:    /* 来盘文件 */
                /* 获取列信息 */
                memset(&thisColumn, 0, sizeof(thisColumn));
                ret=getFileColumn(&thisColumn,gSFileMap,pFileSort);
                if( ret <= 0)
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 无对应的列信息[%s]",gSFileMap->lywz),"ERROR")
                    return -6;
                }
                trim(thisColumn.lsx);
                trim(thisColumn.fldref);
                if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_FIX )          /* 定长 */
                {
                    memset(itemBuf,0,sizeof(itemBuf));
                    memcpy(itemBuf,inBuf+thisColumn.offset-1,thisColumn.columnlen);
                    if( thisColumn.izoom != 0 )
                    {
                        dTmp=atof(itemBuf)*pow(10,-thisColumn.izoom);
                                               
                        if( thisColumn.iprecision < 1 )
                            thisColumn.iprecision = 2;  /* 默认小数精度2 */
                        sprintf(sFmt,"%%.%df",thisColumn.iprecision);
                        snprintf(itemBuf,sizeof( itemBuf ),sFmt,dTmp);
                    }
                }
                else if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT ||    /* 分割符 */
                         pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL ) /* 去尾分隔符 */
                {
                    memset(itemBuf,0,sizeof(itemBuf));
                    snprintf( itemBuf, sizeof( itemBuf ), "%s", sss[atoi(gSFileMap->lywz) - 1 ]);
                    if( thisColumn.izoom != 0 ) /* 有偏移，需要计算 */
                    {                            
                        dTmp=atof(itemBuf)*pow(10,-thisColumn.izoom);
                        memset(sFmt,0,sizeof(sFmt));
                        if( thisColumn.iprecision < 1 )
                            thisColumn.iprecision = 2;  /* 默认小数精度2 */
                        sprintf(sFmt,"%%.%df",thisColumn.iprecision);
                        memset(itemBuf, 0,sizeof(itemBuf));
                        snprintf(itemBuf, sizeof( itemBuf ), sFmt,dTmp);
                    }
                    /* 分隔符模式，设置了字段长度，也要判断长度。超长字符将被截取 */
                    if( thisColumn.columnlen > 0 )
                    {
                        itemBuf[thisColumn.columnlen] = '\0';
                    }
                }
                else
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 列分割标识非法[%s]",pFileSort->columnflag),"ERROR")
                    return -1;
                }

                /* 处理填充字符 */
                if ( thisColumn.ifiller > 0 && thisColumn.columnlen > 0 )  
                {
                    memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
                    strcpy( tmpBuf, itemBuf );
                    position = thisColumn.columnlen; 
                    if ( thisColumn.regular[0] == 'R' )   /* 右对齐 */
                    {
                        for( i = 0; i<= thisColumn.columnlen; i++ )
                        {
                             /* 查找有效字符开始位置 */
                             if( tmpBuf[i] != thisColumn.ifiller )
                             {
                                 position = i; 
                                 break;
                             }
                        } 
                        memset( itemBuf, 0x00, sizeof( itemBuf ) );
                        memcpy( itemBuf, tmpBuf+position, thisColumn.columnlen - position );
                        itemBuf[ thisColumn.columnlen -  position] = '\0';
                    }
                    else if ( thisColumn.regular[0] == 'L' )   /* 左对齐 */
                    {
                        for( i = 0; i<= thisColumn.columnlen; i++ )
                        {
                             /* 查找填充字符开始位置 */
                             if( tmpBuf[i] == thisColumn.ifiller )
                             {
                                 position = i; 
                                 break;
                             }
                        } 
                        memset( itemBuf, 0x00, sizeof( itemBuf ) );
                        memcpy( itemBuf, tmpBuf, position );
                        itemBuf[position] = '\0';
                    }
                    else /* 不设置对齐方式 */
                    {
                        j = 0;
                        for( i = 0; i<= thisColumn.columnlen; i++ )
                        {
                             /* 查找非填充字符 */
                             if( tmpBuf[i] != thisColumn.ifiller )
                             {
                                 itemBuf[j++]= tmpBuf[i] ; 
                             }
                        } 
                        itemBuf[j] = '\0';
                    }
                }

                snprintf(fldCont, sizeof( fldCont ),"%s^",itemBuf);
                if( strcmp(thisColumn.lsx,BATCH_FILECOLUMN_LSX_SETXML) == 0) /* 列属性：set XML */
                {
                    memset(xmlNode,0,sizeof(xmlNode));
                    if( thisColumn.fldref[0] == '/')
                    {
                        snprintf( xmlNode, sizeof( xmlNode ), "%s",thisColumn.fldref );
                    }
                    else
                    {
                        snprintf( xmlNode, sizeof( xmlNode ),  "/batch/%s",thisColumn.fldref );
                    }
                    trim(xmlNode);
                    if( xml_SetElement(lXmlhandle,xmlNode," ") == FAIL )
                    {            
                        LOG(LM_DEBUG,Fmtmsg(MSG_SYS_XMLSET,xmlNode,GETXMLERR),"DEBUG")
                    }                    
                    if( xml_SetElement(lXmlhandle,xmlNode,alltrim(itemBuf)) == FAIL )
                    {            
                        LOG(LM_DEBUG,Fmtmsg(MSG_SYS_XMLSET,xmlNode,GETXMLERR),"DEBUG")
                    }            
                }        
                else if( strcmp(thisColumn.lsx,BATCH_FILECOLUMN_LSX_ADD) == 0)  /* 列属性：交易金额累加  */
                {
                    dTmp=atof(itemBuf); 
                    *dTotal+=dTmp;         
                }
                else if( strcmp(thisColumn.lsx,BATCH_FILECOLUMN_LSX_SUB) == 0) /* 列属性：交易金额累减 */
                {
                    dTmp=atof(itemBuf); 
                    *dTotal-=dTmp;         
                }
                trim(itemBuf);                
                /*增加对域非空为空判断*/
                if (thisColumn.isid[0] == '1' && itemBuf[0] == '\0')
                {/*列域非空为空,需设置响应码、响应信息及成功标志*/
                    iIsId = atoi(gSFileMap->lywz);
                    memset(sIsIdFildName, 0x00, sizeof(sIsIdFildName));
                    pstrcopy(sIsIdFildName, thisColumn.columnid, sizeof(sIsIdFildName));
                }

                /*add by tuql 20160810 增加对域包含特殊字符的检查 begin*/
                if (iSpeChar == 0)
                {
                    iFldCont = strlen(fldCont);
                    for (i=0;i<iFldCont;i++)
                    {
                        if ( fldCont[i]==10 || fldCont[i]==13 )
                        {
                            /**/
                            memset(sIsIdFildName, 0x00, sizeof(sIsIdFildName));
                            pstrcopy(sIsIdFildName, thisColumn.columnid, sizeof(sIsIdFildName));
                            iIsId2 = atoi(gSFileMap->lywz);
                            iSpeChar=i+1;
                            memset(sTmpStr, 0x00, sizeof(sTmpStr));
                            iLen=sizeof(sTmpStr);
                            xml_asctohex( sTmpStr, iLen, fldCont, iFldCont );
                            LOG(LM_STD,Fmtmsg("888887799-->域中包含特殊字符[%d-%s][%d-%s]",iIsId2, sIsIdFildName,iSpeChar,sTmpStr),"ERROR");
                    
                            break;
                        }
                    }
                }

                break;

            case BATCH_FILEMAP_LYLX_XML:    /* XML获取 */
                trim(gSFileMap->lywz);
                memset(itemBuf, 0, sizeof(itemBuf));
                COMP_SOFTGETXML(gSFileMap->lywz,itemBuf);
                trim(itemBuf);
                snprintf(fldCont, sizeof( fldCont), "%s^",itemBuf);
                break;
                
            case BATCH_FILEMAP_LYLX_SEQ:    /* 流水序号  */
                snprintf(fldCont, sizeof( fldCont ),  "%d^",cycNum);
                break;
            
            case BATCH_FILEMAP_LYLX_CONST:    /* 常量 */
                trim(gSFileMap->lywz);
                snprintf(fldCont, sizeof( fldCont ),  "%s^",gSFileMap->lywz);
                break;
                
            case BATCH_FILEMAP_LYLX_WJSEQ:   /* 文件序号 */
                snprintf(fldCont, sizeof( fldCont ),  "%d^",iWjxh );
                break;

            case BATCH_FILEMAP_LYLX_ZHQZLSH:    /* 综合前置流水号 */
                /* 生成新流水号  */
                ret =fpub_ExGenLSerialno(lXmlhandle, XMLNM_ZHQZLSH , 1 );
                if( ret != MID_SYS_SUCC )
                {
                    LOG(LM_STD,Fmtmsg("生成新的综合前置流水号失败！ret[%d]",ret),"ERROR");
                    return -2;
                }
                COMP_SOFTGETXML( XMLNM_ZHQZLSH, itemBuf )
                snprintf(fldCont, sizeof( fldCont), "%s^",itemBuf);
                break;

            default:
                snprintf(fldCont, sizeof( fldCont ),  "%s^","");
                break;
        }

        /* 整行输出(外部要保证不能溢出) */
        if ( strcmp(gSFileMap->columnid, "clzt") == 0 )
        {/*处理标志*/
            if ( iIsId > 0 || iIsDetailCnts > 0 || iSpeChar > 0)
            {   
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^","1");
            }
        }
        if ( strcmp(gSFileMap->columnid, "cgbz") == 0 )
        {/*成功标志*/
            if ( iIsId > 0 || iIsDetailCnts > 0 || iSpeChar > 0)
            {
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^",BATCH_CGBZ_S_FAIL);
            }
            
        }
        if ( strcmp(gSFileMap->columnid, "xym") == 0 )
        {/*响应码*/
            if ( iIsId > 0 || iIsDetailCnts > 0 || iSpeChar > 0)
            {
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^",itoa(MID_BATCH_PROCLINE_NOTNULL));
            }
        }
        if ( strcmp(gSFileMap->columnid, "xyxx") == 0 )
        {/*响应信息*/
            if ( iIsDetailCnts > 0 )
            {
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^",
                    Fmtmsg(MSG_BATCH_DETAILLINE_COLS, iLineField, iSplitLine));
            }else if ( iIsId > 0 )
            {
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^",
                    Fmtmsg(MSG_BATCH_DETAILLINE_NOTNULL, iIsId, sIsIdFildName));
            }else if ( iSpeChar > 0)
            {
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^",
                    Fmtmsg(MSG_BATCH_DETAILLINE_SPECHAR, iIsId2, sIsIdFildName, iSpeChar));
            }
        }

        strcat(outbuf,fldCont);
    }
    return strlen( outbuf );
}

/*add by tuql 20160711 增加手工录入批次明细的处理*/
int batch_sjct_sglr(HXMLTREE lXmlhandle, char *psTableName )
{
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sBuf[256];
    char sLrzbs[8+1];
    char sLrzje[20+1];
    char sErrmsg[1024];
    char sSql[256];
    int  iLrzbs=0,iHZbs=0;
    double  dLrzje=0,dHZje=0.00;
    int iRet=-1;
    
    memset(sPkrq, 0x00, sizeof(sPkrq));
    memset(sPtpch, 0x00, sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sPkrq)
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sPtpch)
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select count(pkrq),sum(jyje) from %s where pkrq='%s' and ptpch='%s'",
        psTableName, sPkrq, sPtpch);
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(sLrzbs, 0x00, sizeof(sLrzbs));
    memset(sLrzje, 0x00, sizeof(sLrzje));
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),"INFO")
    iRet=DBSelectToMultiVarChar(sErrmsg, sSql, sLrzbs, sLrzje);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return -1;
    }
    /* 设置实际总笔数 */
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZBS, sLrzbs);
    iHZbs=atoi(sLrzbs);
    /* 设置实际总金额 */
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZJE, sLrzje);
    if (sLrzje[0] == '\0') sLrzje[0]='0';
    dHZje=atof(sLrzje);
    LOG(LM_STD,Fmtmsg("BATCH: 手工入库 实际总笔数[%s]实际总金额[%s]", sLrzbs,sLrzje),"INFO")
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select zbs,zje from batch_plrw where pkrq='%s' and ptpch='%s'",
        psTableName, sPkrq, sPtpch);
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    memset(sLrzbs, 0x00, sizeof(sLrzbs));
    memset(sLrzje, 0x00, sizeof(sLrzje));
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),"INFO")
    iRet=DBSelectToMultiVarChar(sErrmsg, sSql, sLrzbs, sLrzje);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return -1;
    }
    if(sLrzbs[0]='\0') sLrzbs[0] = '0';
    if(sLrzje[0]='\0') sLrzje[0] = '0';
    iLrzbs=atoi(sLrzbs);
    dLrzje=atof(sLrzje)*1.00;
    COMP_SOFTSETXML(XMLNM_BATCH_REQ_ZBS, sLrzbs)
    COMP_SOFTSETXML(XMLNM_BATCH_REQ_ZJE, sLrzje)

    if( iLrzbs > 0 )
    {
        /* 总笔数不符 */
        if( abs(iHZbs - iLrzbs) > 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 录入总笔数[%d]与明细[%d]不符",iLrzbs,iHZbs),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZBS_MXZBS,Fmtmsg(MSG_BATCH_LRZBS_MXZBS,iLrzbs,iHZbs));        
            return -3;
        }
        /* 总金额不符 */
        if( fabs(dHZje - dLrzje) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 录入总金额[%f]与明细总金额[%f]不符",dLrzje,dHZje),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZJE_MXZJE,Fmtmsg(MSG_BATCH_LRZJE_MXZJE,dLrzje,dHZje));
            return -4;
        }
    }

    return 0;
}
/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_SJRK
组件名称:BATCH_SJRK
组件功能: 
组件参数:
 序号 参数类型    参数名称                 资源类别         缺省值    可空    参数说明        
    1     1-输入     文件名            416XML解析字符串    *            N        
    2     1-输入     文件标识        416XML解析字符串    *            N        
    3     1-输入     映射标识        416XML解析字符串    *            N        
    4     1-输入     业务表名        416XML解析字符串    *            N        
 
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_SJRK(HXMLTREE lXmlhandle)
{
    int  iParas,iResult;
    char sBuf[256];
    char linebuf[BATCH_MAX_FILELINE_BYTE];
    char outbuf[BATCH_MAX_FILELINE_BYTE];
    char sFileId[40+1];
    char sFileType[2+1];
    char sTableName[40+1];
    char sFileName[128];
    char sTmpFileName[128];
    char sTmpFilePath[128];
    char sMapId[40+1];
    int  iTSortCount=0;
    int  totalcount=0;
    int  detailcount=0;
    /*int  iValid=0;*/
    int  i,iAbort=0,length=0,iPtpch=0;
    int iRet = 0;
    int  iBatchReqZbs=0;
    char sPkrq[8+1];
    char sSqlStr[256];
    char sCodeFmt[2+1];
    char sFileTypeReal[1+1];
    long lRCount=0;
    FILE *tmpfp;
    FILE * srcfp;
    FILE * fp1;
    int iTotalRows=0;
    double dTotal=0.00;
    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
 
    int iClassPre = 0;    /* 上一分类序号 */
    int  iRearClass = 1;
    int ii =0, index = 0;
    int iWjxh = 1;
    int lPgNum = 0;    /* 每主机文件最大记录数 */
    int iFileLen = 0;  /*文件内容长度*/
    char sSjhqfs[1+1];/*数据获取方式*/
    
    fpub_InitSoComp(lXmlhandle);

    memset(sSjhqfs, 0x00, sizeof(sSjhqfs));
    COMP_SOFTGETXML(XMLNM_BATCH_HQSJ_HQSJFS,sSjhqfs)
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始,hqsjfs01=[%s]",fpub_GetCompname(lXmlhandle), sSjhqfs),"DEBUG");
    
    COMP_PARACOUNTCHKMIN(6)
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"文件名")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJM_NULL,MSG_BATCH_WJM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileName,sBuf,sizeof(sFileName));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"文件标识")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJBS_NULL,MSG_BATCH_WJBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileId,sBuf,sizeof(sFileId));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"映射标识")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YSBS_NULL,MSG_BATCH_YSBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sMapId,sBuf,sizeof(sMapId));
    
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
    COMP_GETPARSEPARAS(5,sBuf,"文件类型")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJLX_NULL,MSG_BATCH_WJLX_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileType,sBuf,sizeof(sFileType));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(6,sBuf,"主机文件记录数限制")
    lPgNum = atol( sBuf );
    
    /*add by tuql 2060711 若为批次明细为手工录入，则直接判断记录数和录入金额*/
    if (strcmp(sSjhqfs,BATCH_ATTRIBUTE_HQSJFS_SGLR)== 0)
    {/*手工录入*/
        iRet=batch_sjct_sglr(lXmlhandle, sTableName);
        if (iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("手工输入明细总笔数总金额有误[%d]", iRet), fpub_GetCompname(lXmlhandle));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return iRet;
        }
        LOG(LM_STD,Fmtmsg("手工录入明细,执行结束"),fpub_GetCompname(lXmlhandle));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }

    /*文件格式*/
    memset(sFileTypeReal, 0x00, sizeof(sFileTypeReal));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILETYPE, sFileTypeReal)
    /*文件编码格式*/
    memset(sCodeFmt, 0x00, sizeof(sCodeFmt));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_CODEFMT, sCodeFmt)

    LOG(LM_STD,Fmtmsg("BATCH: 文件名[%s] ", sFileName),"INFO")

    LOG(LM_STD,Fmtmsg("BATCH: 文件类型[%s] 文件格式[%s] 编码格式[%s]", 
        sFileTypeReal, sFileType, sCodeFmt ),"INFO")
    if( sFileName[0] == '~' )  /* ~代表HOME目录 */
    {
         sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName+2 ); 
         strcpy( sFileName, sBuf );
         LOG(LM_DEBUG,Fmtmsg("BATCH: 文件名[%s] ", sFileName ),"DEBUG")
    }
    else if( sFileName[0] != '/') /* 相对路径时 */
    {
         sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName ); 
         strcpy( sFileName, sBuf );
         LOG(LM_DEBUG,Fmtmsg("BATCH: 文件名[%s] ", sFileName ),"DEBUG")
    }
#if 0  
    sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName ); 
    strcpy( sFileName, sBuf );
    LOG(LM_DEBUG,Fmtmsg("BATCH: 文件名[%s] ", sFileName ),"DEBUG")
#endif 
    
    if ( sFileTypeReal[0] == '0')
    {/*0-文本格式,才需要转换*/
        if ( sCodeFmt[0] == '1')
        {/*1-UTF-8格式*/
            iRet=fpub_convFileFmt(sFileName, &iFileLen, 2);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 文件编码格式[%s]转换失败[%d] ", "UTF-8", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "UTF-8"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }else if ( sCodeFmt[0] == '2')
        {/*2-BASE64格式*/
            iRet=fpub_convFileFmt(sFileName, &iFileLen, 4);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 文件编码格式[%s]转换失败[%d] ", "BASE64", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "BASE64"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }
    }
    
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
    
    /* 清理原批次信息(单步重复操作的情况) */ 
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf);
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;        
    }
    iPtpch=atol(sBuf);
    memset(sSqlStr, 0, sizeof(sSqlStr));
    snprintf(sSqlStr,sizeof(sSqlStr),"DELETE FROM %s \
        WHERE pkrq='%s' AND ptpch='%d'",\
        sTableName,sPkrq,iPtpch);
    iRet = DCIExecuteDirect( sSqlStr ); 
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_DEL_YWMX,\
            Fmtmsg(MSG_BATCH_DEL_YWMX,-1));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;        
    }
    
    /* 生成临时文件，用于导入数据库明细表 */
    memset(sTmpFilePath, 0x00, sizeof(sTmpFilePath));
    iRet = fprv_getBatchFilePath(lXmlhandle,sTmpFilePath, sizeof(sTmpFilePath));
    LOG(LM_STD,Fmtmsg("fprv_getBatchFilePath[%d][%s]",iRet, sTmpFilePath ),"ERROR")
    memset(sTmpFileName, 0, sizeof(sTmpFileName));
    snprintf(sTmpFileName, sizeof( sTmpFileName ),\
        "%s/batch_sjrk_tmp%s.%ld", sTmpFilePath, sPkrq,getpid());
    
    /* 单明细或者多汇总多明细格式，不需要文件汇总分类映射链表初始化 --原注释*/
    /* 单明细格式，不需要文件汇总分类映射链表初始化 */
    if( strcmp( sFileType,"01" ) != 0 )
    {
        iTSortCount=fprv_initFileSort(sFileId,BATCH_FILESORT_TYPE_S_TOTAL,&t_fileTotalSortList);
        if( iTSortCount <= 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 文件汇总分类映射链表初始化失败,[%s][%d]",\
                               sFileId,iTSortCount),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                         Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileId));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /* 文件明细分类映射链表初始化 */
    iResult =fprv_initFileSort(sFileId,BATCH_FILESORT_TYPE_S_DETAIL, &t_fileDetailSortList);
    if( iResult != 1 )  /* 明细分类有且仅有一个 */
    {
        LOG(LM_STD,Fmtmsg("BATCH: 文件明细分类映射链表初始化失败,[%s][%d]",\
                           sFileId,iResult ),"ERROR")
        batch_totalsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                          Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileId));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 取明细分类信息 从链表中取第一条配置信息 */
    memset(&thisSort, 0, sizeof(BATCH_FILESORT));
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* 文件列信息链表初始化 */
    iResult=fprv_initFileColumn(sFileId,&t_fileColumnList);
    if( iResult <= 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:文件列信息链表初始化[%s]",sFileId),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
            Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileId));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 文件映射信息链表初始化 */
    iResult=fprv_initFileMap(sMapId,BATCH_STEPNM_SJRK,&t_fileMapList);
    if( iResult <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 文件映射信息链表初始化,[%s],[%s]",\
            BATCH_STEPNM_SJRK,sMapId),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILEMAP_LISTFAIL,\
            Fmtmsg(MSG_BATCH_FILEMAP_LISTFAIL,sFileId));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 获取文件总行数 rows */
    /* 01 单明细 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
    /* 20110825 所有文件都获取行数 
    if( strcmp( sFileType,"03" ) == 0 || strcmp( sFileType,"04" ) == 0  ) 
    {
    */
        /* 打开来盘文件 */
        if((fp1 = fopen(sFileName, "r")) == NULL)
        {
            batch_totalsortlistFree();
            batch_detailsortlistFree();
            batch_columnlistFree();
            batch_maplistFree();
            LOG(LM_STD,Fmtmsg("BATCH: 打开来盘文件[%s]失败",sFileName),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        iTotalRows=0;
        while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, fp1 ) != NULL )
        {
            iTotalRows++ ;

            /*去掉回车换行,可以处理多个回车换行的 modified by chenxm 20141212*/
            if( 10 == linebuf[0] || 13 == linebuf[0] )
            iTotalRows-- ;
        }
        /* 去除最后一行的回车换行,若有多个换行则无法解析 (noted by chenxm 20141212)*/
        /*if( 10 == linebuf[0] || 13 == linebuf[0] )
        {
            iTotalRows-- ;
        }*/
        LOG(LM_STD,Fmtmsg("BATCH: 文件总行数[%d]", iTotalRows ),"INFO")

        fclose(fp1);
/* 20110825 所有文件都获取行数 
    }
*/

    /* 打开来盘文件处理 */
    if( ( srcfp = fopen( sFileName, "r" ) ) == NULL )
    {
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        LOG(LM_STD,Fmtmsg("BATCH: 打开来盘文件[%s]失败",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 处理开头的汇总信息 */
    /* 01 单明细 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
    if( strcmp( sFileType,"02" ) == 0 || strcmp( sFileType,"04" ) == 0 )
    {
        /* 遍历汇总分类，一个汇总分类处理一行记录,
           需要配置保证汇总分类的顺序匹配文件 */
        iClassPre= 0;  /* 上一分类序号 */
        for( pfileTotalSortIter = i_list_begin(t_fileTotalSortList);
              pfileTotalSortIter!= i_list_end(t_fileTotalSortList);
                  pfileTotalSortIter = i_list_iter_next(pfileTotalSortIter) )
        {
            /* 取汇总分类信息 */
            memset(&thisSortT, 0, sizeof(BATCH_FILESORT));
            memcpy( &thisSortT,(BATCH_FILESORT *)(pfileTotalSortIter->data),sizeof(BATCH_FILESORT));
            if( strcmp( sFileType,"04" ) == 0 && ( thisSortT.fileclasssn - iClassPre ) > 1 )
            {
                 iRearClass = thisSortT.fileclasssn ; /* 尾部汇总分类的分类序号 */
                 break;  /* 当前分类序号跳跃，说明中间有明细分类，退出 */
            }
            iClassPre++;
            if( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
            {
                totalcount++;
                iResult =totalProc(lXmlhandle, linebuf, &thisSortT);
                if( iResult != 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 汇总信息处理失败,[%s],[%d],[%s]",
                        linebuf,thisSortT.fileclasssn,thisSortT.classname),"ERROR")
                    batch_totalsortlistFree();
                    batch_detailsortlistFree();
                    batch_columnlistFree();
                    batch_maplistFree();
                    fclose(srcfp);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
        }
    }

    /* 01 单明细 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
    if( strcmp( sFileType,"03" ) == 0 ) 
        iTotalRows -= iTSortCount ; /* 减去汇总行数，为实际明细记录数最大序号 */
    else if( strcmp( sFileType,"04" ) == 0 ) 
        iTotalRows = iTotalRows -iTSortCount ; 
        /* 减去结尾汇总记录数，为实际明细记录数最大序号 */
    else if ( strcmp( sFileType,"02" ) == 0 )
        iTotalRows -= 1 ;
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS, sBuf);
    iBatchReqZbs = atoi(sBuf);
    LOG(LM_STD,Fmtmsg("BATCH: 文件明细结尾行, iBatchReqZbs[%d],iTotalRows[%d],iTSortCount[%d],iClassPre[%d]", 
        iBatchReqZbs,iTotalRows,iTSortCount, iClassPre ),"INFO")
    if ( iBatchReqZbs > 0 && iBatchReqZbs != iTotalRows)
    {
        LOG(LM_STD,Fmtmsg("BATCH: 来盘文件不完整,明细记录缺少[%d]行", iBatchReqZbs - iTotalRows),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_BATCH_LRZBS_MXZBS,MSG_BATCH_LRZBS_MXZBS);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if((tmpfp = fopen(sTmpFileName, "w")) == NULL)
    {
        LOG(LM_STD,Fmtmsg("BATCH: 打开文件[%s]失败",sTmpFileName),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 开始处理明细信息 */
    index = 0;
    memset(linebuf, 0, sizeof(linebuf));
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        index ++;
        /* 无有效信息 继续*/
        if( strlen( linebuf ) < 3 )
        {
            continue;
        }

        detailcount++;
        /*  rows为文件总行数 */
        if( index > iTotalRows && (strcmp( sFileType,"03" ) == 0 || strcmp( sFileType,"04" ) == 0)) 
        {
            detailcount --;
            break; /* 只有 TYPE＝03 04 的才会走到这里 */
        }
        memset(outbuf, 0, sizeof(outbuf));

        /* 解析来盘文件记录，根据映射，处理成可以导入数据库表的字符串 */
        length = detailProc(lXmlhandle,detailcount,iWjxh,linebuf,&dTotal,outbuf,&thisSort);
        if( length < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH:明细信息处理失败[%s]",linebuf),"ERROR")
            iAbort = 6;
            break;
        }
        outbuf[length] = '\n';
        iResult = fwrite( outbuf, length + 1, 1, tmpfp );
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 文件写入失败,[%d],[%s]",\
                            errno,strerror(errno)),"ERROR")
            iAbort=7;
            break;
        }
        memset(linebuf, 0, sizeof(linebuf));
        /* 设置文件序号 */
        if( ( lPgNum > 0 ) && ( ( detailcount % lPgNum ) == 0 ) )
           iWjxh ++;
        
    }
    /* 处理尾部汇总信息 */  
    /* 01 单明细 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
    if( ( strcmp( sFileType, "03" ) == 0 ||  strcmp( sFileType, "04" ) == 0 ) && ! iAbort )
    {
        ii = 0;
        /* 配置保证分类信息顺序 */
        for( pfileTotalSortIter = i_list_begin(t_fileTotalSortList);
              pfileTotalSortIter!= i_list_end(t_fileTotalSortList);
                  pfileTotalSortIter = i_list_iter_next(pfileTotalSortIter) )
        {
            /* 取汇总分类信息 */
            memset(&thisSortT, 0, sizeof(BATCH_FILESORT));
            memcpy( &thisSortT,(BATCH_FILESORT *)(pfileTotalSortIter->data),sizeof(BATCH_FILESORT));
            if( ( strcmp( sFileType, "04" ) == 0 ) && ( thisSortT.fileclasssn < iRearClass ) )
            {
                 continue;  /* 头部汇总分类信息过滤 */
            }
            if( ii == 0 )
                ;  /* 第一行信息已经存放在linebuf中 */ 
            else if(  fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
            {
                totalcount++;
            }
            else
            {
                LOG(LM_STD,Fmtmsg("BATCH: 取汇总记录信息失败"),"ERROR")
                iAbort = -1;
                break;
            }
          
            iResult =totalProc(lXmlhandle, linebuf, &thisSortT);
            if( iResult != 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 汇总信息处理失败,[%s],[%d],[%s]",
                linebuf,thisSortT.fileclasssn,thisSortT.classname),"ERROR")
                iAbort = iResult;
                break;
            }

            ii++;
        }
    }

    fclose(tmpfp);
    fclose(srcfp);
    /* 释放链表资源 */
    batch_totalsortlistFree();
    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_maplistFree();
    
    /* 处理异常 */
    switch ( iAbort )
    {
        case 0:
            break;
        case -1:
        case -2:
        case -99:
            unlink(sTmpFileName);
            fpub_SetCompStatus(lXmlhandle,COMPRET_FAIL);
            return COMPRET_FAIL;
        case -5:
            unlink(sTmpFileName);
            fpub_SetCompStatus(lXmlhandle,COMPRET_FAIL);
            return COMPRET_FAIL;
        case -6:
            unlink(sTmpFileName);
            fpub_SetMsg(lXmlhandle,MID_BATCH_LXX_NOFUND,MSG_BATCH_LXX_NOFUND);            
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPRET_FAIL;
        default:
            unlink(sTmpFileName);
            fpub_SetMsg(lXmlhandle,MID_BATCH_SJRK,MSG_BATCH_SJRK);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPRET_FAIL;
    }
    LOG(LM_DEBUG,Fmtmsg("BATCH: 明细文件处理结束,处理记录总数: [%d]",detailcount),"DEBUG");
    if( detailcount == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 来盘文件[%s]明细记录为空",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_LPWJ_NULL,MSG_BATCH_LPWJ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;
    }
    /*将临时文件数据导入本地明细表*/
    /* modified by yangdong 20111020 玕（ASCII码5C开头，就是‘\’） 转义字符问题
    if(sql_LoadFromFile(sTmpFileName,sTableName,'^','\\',&lRCount) != 0 )
    */
    int iii = 1;
    /* modified  by yangdong 使用分布提交的load函数 
    if(sql_LoadFromFile(sTmpFileName,sTableName,'^',iii,&lRCount) != 0 )
    */
    /* modified by guoliang 20130412 根据不同的响应码设置不同的响应信息 */
    iRet = sql_LoadFromFile_b(sTmpFileName,sTableName,'^',iii,&lRCount);
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 将文件[%s]数据导入本地明细表[%s]失败[%d],返回码[%d]",\
                          sTmpFileName, sTableName, lRCount, iRet),"INFO")
            switch ( iRet )
            {
                case -41:
                        fpub_SetMsg(lXmlhandle,MID_BATCH_SJRK_SQLNOTNULL,\
                        Fmtmsg(MSG_BATCH_SJRK_SQLNOTNULL,lRCount));
                        break;
                case -42:
                        fpub_SetMsg(lXmlhandle,MID_BATCH_SJRK_OVERLEN,\
                        Fmtmsg(MSG_BATCH_SJRK_OVERLEN,lRCount));
                        break;
                default:
                        fpub_SetMsg(lXmlhandle,MID_BATCH_LOAD_YWMX,\
                        Fmtmsg(MSG_BATCH_LOAD_YWMX,-1));
                        break;
            }
        sql_RollbackTrans();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;
    }
    /* end */
    /*  add by yr 20120814 增加commit */
    if( DCICommit() == -1 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*   end add */

    /* 删除临时文件 */
    unlink(sTmpFileName);

    /* 设置实际总笔数 */
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZBS,itoa(detailcount));
    /* 设置实际总金额 */
    memset(sBuf,0,sizeof(sBuf));
    sprintf(sBuf,"%.2f",dTotal);
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZJE,sBuf);
    LOG(LM_STD,Fmtmsg("BATCH: 入库 实际总笔数[%s]实际总金额[%s]",itoa(detailcount),sBuf),"INFO")

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
函数声明:
IRESULT sql_LoadFromFile(char* sFilename,char *sTname,
                         char cDiv,char cEscape,long *lResult)
函数功能:
从指定Load格式文件中提取记录插入到指定数据库表
输入参数:
         char *sFilename       数据文件名(全路径)
         char *sTname          表名
         char cDiv             分隔符      缺省为'|'
         char cEscape          转义字符    缺省为'\'
         long *lResult         插入记录条数(输出)
返    回:
         成功
           MID_SYS_SUCC
         失败
           MID_SYS_INVALID
           MID_SYS_OPENFILE
 
           MID_SQL_PREPARE
           MID_SQL_DESCRIBE
 
           MID_SQL_ALLOCDESCPT
           MID_SQL_SETDESCPT
限    制:
项 目 组:中间业务产品研发组
程 序 员:Stony.Z,Tianhc,Shining
发布日期:2000年01月01日
修改日期:2002年04月01日
修改日期:2009年01月09日
例:
   旧的代码只能用于INFORMIX,对于ORACLE不适用;
   针对ORACLE的代码采用select_lda=sqlald()这种ORACLE的特殊结构,过程不清淅,有内存泄露!
   故参考fpub_InsertTableFromXML代码重写
************************************************************************/
IRESULT sql_LoadFromFile_b(char* sFilename, char *sTname,
                         char cDiv, char cEscape, long *lResult)
{
    int iLineLen, k, i, iflag;
    FILE *fpLoadfile;
    char sLbuffer[128000], sLbuffer0[128000];
    int    iCnt;
    double dvalue;
    float    fvalue;
    char    year[5];
    char    month[3];
    char    day[3];
    int     year_num;
    int     month_num;
    int     day_num;
    int        iTmp;
    char sSqlstr[4096];
    char sValstr[4096];
    char sTmp[2048];
    char **sdata;
    char sFldname[51];
    CURSOR cur, cur_ins;
    int numCols;
    int iType[256] = {0};
    int iSize[256] = {0};
    int iScale[256] = {0};
    char sSqlErrMsg[512];
    char sDbType[128];
    /*int number=0;*/
 

    LOG(LM_DEBUG, Fmtmsg("动态载入数据开始,从文件[%s]->表[%s]", sFilename, sTname),"DEBUG")

#ifdef TIMEDEBUG
    ftime(&starttime);
#endif

    memset( sDbType, 0x00, sizeof( sDbType ) );
    sprintf(sDbType, "%s", getenv("DB"));
    trim( sDbType );

    *lResult = 0;
    if ( !*sFilename || !*sTname )
    {
        LOG(LM_STD,Fmtmsg("文件名[%s] 表名[%s]", sFilename, sTname ),"ERROR")
        return    MID_SYS_INVALID;
    }
    /* 打开文件 */
    if ( cDiv == 0 )
        cDiv = '|';
    if ( cEscape == 0 )
        cEscape = '\\';
 
    if ( (fpLoadfile = fopen(sFilename, "r")) == NULL )
    {
        LOG(LM_STD,Fmtmsg("文件[%s] 打开失败", sFilename ),"ERROR")
        return MID_SYS_OPENFILE;
    }
 
    /* 获取表结构 */
    sprintf(sSqlstr, "select * from %s where 1=2", sTname);
    cur = DCIDeclareCursor(sSqlstr, 0);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        fclose(fpLoadfile);
        return MID_SQL_DECLARE;
    }
    DCIExecute(cur);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fclose(fpLoadfile);
        return MID_SQL_EXECUTE;
    }
    numCols = DCINumCols(cur);                        /* 取字段数 */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fclose(fpLoadfile);
        return MID_SQL_EXECUTE;
    }
 
    /*生成动态SQL语句*/
    memset(sSqlstr, 0 , sizeof(sSqlstr));
    memset(sValstr, 0 , sizeof(sValstr));
    sprintf(sSqlstr, "insert into %s (", sTname);
    sprintf(sValstr, " ) values ( ");
 
    for (iCnt = 0, iflag = 0; iCnt < numCols;iCnt++)
    {
        memset(sFldname, 0, sizeof(sFldname));
        DCIColName(cur, iCnt, sFldname, sizeof(sFldname));     /* 取字段名 */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            fclose(fpLoadfile);
            return MID_SQL_EXECUTE;
        }
        trim(sFldname);
        if ( strcmp(sFldname, "id") != 0 && strcmp(sFldname, "ID") != 0 )
        {
            strcat(sSqlstr, sFldname);
            strcat(sSqlstr, ",");
            sprintf(sValstr + strlen(sValstr), ":v%d,", iCnt);
        }
    }
    sSqlstr[strlen(sSqlstr)-1] = ' ';
    sValstr[strlen(sValstr)-1] = ' ';
    strcat(sValstr, ")");
    strcat(sSqlstr, sValstr);
 
    cur_ins = DCIDeclareCursor(sSqlstr, 0);    /* 打开insert的游标 */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fclose(fpLoadfile);
        return MID_SQL_DECLARE;
    }
 
    sdata = calloc (numCols, sizeof(void *));
    if ( sdata == NULL )
    {
        DCIFreeCursor(cur);
        DCIFreeCursor(cur_ins);
        fclose(fpLoadfile);
        return -1;
    }
    /*将数据文件数据插入该表中*/
    iflag = 0;
    /*bind*/
    for (iCnt = 0;iCnt < numCols;iCnt++)
    {
            iType[iCnt] = DCIColType(cur, iCnt);     /* 取字段类型 */
            if ( DCIERR )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
                iflag = -22;
                break;
            }
            iSize[iCnt] = DCIColSize(cur, iCnt);     /* 取字段大小 */
            if ( DCIERR )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
                iflag = -23;
                break;
            }
            iScale[iCnt] = DCIColScale(cur, iCnt);    /* 取字段精度 */
            if ( DCIERR )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
                iflag = 24;
                break;
            }
/*LOG(LM_STD, Fmtmsg("iType=%d isize=%d",iType[iCnt] , iSize[iCnt]), __func__);*/
            
            /*设置动态SQL描述语句*/
            switch ( iType[iCnt] )
            {
            case DCIT_INTEGER:    /* INTEGER */
                sdata[iCnt] = calloc(1, sizeof(int));
                if ( sdata[iCnt] == NULL )
                {
                    iflag = -25;
                    break;
                }
                iSize[iCnt] = sizeof(int);
                break;
            case DCIT_NUMERIC:    /* numeric */
                iType[iCnt]=DCIT_DOUBLE;
            case DCIT_DOUBLE:    /* double */            
                sdata[iCnt] = calloc(1, sizeof(double));
                if ( sdata[iCnt] == NULL )
                {
                    iflag = -26;
                    break;
                }
                iSize[iCnt] = sizeof(double);                
                break;
            case DCIT_DATE:
                sdata[iCnt] = calloc(1, sizeof(DCIDate));
                if ( sdata[iCnt] == NULL )
                {
                    iflag = -27;
                    break;
                }
                break;
            case DCIT_CHAR:
            case DCIT_VARCHAR:
            iSize[iCnt]++; /*char类型分配内存字段长度应该加1*/ 
            sdata[iCnt] = calloc(iSize[iCnt], sizeof(char));
            if ( sdata[iCnt] == NULL )
            {
               iflag = -28;
               break;
            }
            break;
            default:
                sdata[iCnt] = calloc(iSize[iCnt], sizeof(char));
                if ( sdata[iCnt] == NULL )
                {
                    iflag = -29;
                    break;
                }
                break;
            }
            if (iflag < 0)
                break;            
            DCIBindPara(cur_ins, iCnt, sdata[iCnt], iSize[iCnt], iType[iCnt]);
            if ( DCIERR )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
                iflag = -31;
                break;
            }
    }
    if(iflag == 0)
    {
        /*end*/
        ftime(&starttime);
        while ( fgets(sLbuffer0, sizeof(sLbuffer0), fpLoadfile) != NULL)
        {
            (*lResult)++;
            iLineLen = strlen(sLbuffer0);
            memset(sLbuffer, 0, sizeof(sLbuffer));
            for ( k = 0, i = 0;k < iLineLen;k++)
            {
                if ( sLbuffer0[k] == cEscape )
                {
                    if ( sLbuffer0[k+1] == '\n' )
                    {
                        if ( fgets(sLbuffer0, sizeof(sLbuffer0), fpLoadfile) != NULL )
                        {
                            iLineLen = strlen(sLbuffer0);
                            k = 0;
                        }
                    }
                }
                sLbuffer[i++] = sLbuffer0[k];
            }
            
            /*加入对空行的跳过处理    by shining 2013-01-28 13:21:14*/
            if ((strlen(trim(sLbuffer0))==0)||(sLbuffer0[0] == '\n'))
                continue;
            /*end */
            
            /*根据分隔符和转义字符从行缓冲区取字段的值*/
            for (iCnt = 0;iCnt < numCols;iCnt++)
            {
             
                memset(sTmp, 0x00, sizeof(sTmp));
                if ( fpvt_GetListbyDiv(sLbuffer, iCnt + 1, sTmp, cDiv, cEscape) < 0 )
                {/*找不到指定列*/
                    iflag = -21;
                    break;
                }
              /*LOG(LM_STD, Fmtmsg("-----%d----[%s]",iCnt, sTmp), __func__);*/
                /*设置动态SQL描述语句*/
                switch ( iType[iCnt] )
                {
                case DCIT_INTEGER:    /* INTEGER */
                    iTmp = atoi(sTmp);
                    /*         sprintf(sdata[iCnt],"%d",iTmp); */
                    *(int *)sdata[iCnt] = iTmp;
                    break;
                case DCIT_NUMERIC:    /* numeric */
                case DCIT_DOUBLE:    /* double */            
                    dvalue = atof(sTmp);
                    /*         sprintf(sdata[iCnt],"%d",iTmp); */
         
                    *(double *)sdata[iCnt] = dvalue;
                    break;
                case DCIT_DATE:
                    memcpy(year, sTmp, 4);
                    year[4] = '\0';
                    memcpy(month, sTmp + 4, 2);
                    month[2] = '\0';
                    strncpy(day, sTmp + 6, 2);
                    day[2] = '\0';
                    year_num = atoi(year);
                    month_num = atoi(month);
                    day_num = atoi(day);
                    SetDCIDate((DCIDate*)sdata[iCnt], year_num,    month_num , day_num);
                    break;
               case DCIT_CHAR:
               case DCIT_VARCHAR:
                      if (strlen(sTmp) > iSize[iCnt]-1)
                      {
                          memcpy(sdata[iCnt], sTmp, iSize[iCnt]-1);
                          /* modified by yangdong 20151125 会coredump
                          LOG(LM_STD,Fmtmsg("BATCH: 数据第%d域[%s]超长,%s位后字段被自动截取",iCnt, sTmp, iSize[iCnt]-1 ),"ERROR")
                          */
                          LOG(LM_STD,Fmtmsg("BATCH: 数据第[%d]域[%s]超过定义长度[%d]",iCnt, sTmp, iSize[iCnt]-1 ),"ERROR")
                          iflag = -42;
                      }
                      else
                         strcpy(sdata[iCnt], sTmp);
                         trim(sdata[iCnt]);
                      break;
                default:
                    if (strlen(sTmp) > iSize[iCnt])
                        memcpy(sdata[iCnt], sTmp, iSize[iCnt]);
                    else
                        strcpy(sdata[iCnt], sTmp);
                    trim(sdata[iCnt]);
                    break;
                }
            }

            if (iflag < 0)
                break;
     
            DCIExecute(cur_ins);
            DCIERRLOG(LM_STD, Fmtmsg("Execute SQL失败[%s]", DCILastError() ), __func__);
            if ( DCIERR )
            {
                /* modified by guoliang 20130412 判断出错信息 */
                memset(sSqlErrMsg, 0x00, sizeof(sSqlErrMsg));
               strncpy(sSqlErrMsg, DCILastError(), sizeof(sSqlErrMsg)-1);
               if( (strstr(sSqlErrMsg, "ORA-01400")) != NULL)
                    iflag = -41;
               else
                    iflag = -32;
               break;
               /* end */
            }

            /* added by yangdong 20130131 分布提交 */
            if( ( (*lResult)  % 5000 ) == 0 )
            {
                ftime(&endtime);
                LOG(LM_DEBUG,Fmtmsg("BATCH: 入库[%d],cast[%ld]ms", *lResult,\
                (endtime.time-starttime.time)*1000+endtime.millitm-starttime.millitm ),"DEBUG");

                if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
                {
                    if ( sql_CommitTrans() !=MID_SYS_SUCC )
                    {
                        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                        sql_RollbackTrans();
                        iflag= -33;
                        break;
                    }
                }
                ftime(&starttime);
            }
        }
        /*处理结束,free sdata()*/
        for (i = 0; i < numCols; i++)
        {
            if (sdata[i])
            {
                free(sdata[i]);
                sdata[i] = NULL;
            }
        }
    }
    free(sdata);
    sdata = NULL;
    DCIFreeCursor(cur);
    DCIFreeCursor(cur_ins);
    fclose(fpLoadfile);
 
#ifdef TIMEDEBUG
    ftime(&endtime);
    LOG(LM_DEBUG, Fmtmsg("动态载入表 usendtime[%ld]",\
         (endtime.time - starttime.time)*1000 + endtime.millitm - starttime.millitm), "DEBUG")
#endif
    if (iflag < 0)
    {
        LOG(LM_STD, Fmtmsg("动态载入表[%s]失败, iflag=[%d], rows=[%d]", sTname, iflag, *lResult), "ERROR")
        return iflag;
    }
 
    LOG(LM_STD, Fmtmsg("动态载入表[%s]成功结束,共[%d]笔", sTname, *lResult), "DEBUG")
 
    return MID_SYS_SUCC;
}
