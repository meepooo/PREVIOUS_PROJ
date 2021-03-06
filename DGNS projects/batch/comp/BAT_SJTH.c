/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_SJTH.c
文件描述: 批量业务处理文件映射-数据提回处理转换组件集
项 目 组:中间业务平台项目组
程 序 员:YangDong
发布日期:20110801

程 序 员:YangDong
修改日期:20130225
修改说明:使用prepare，提高更新效率

程 序 员:YangDong
修改日期:20130301
修改说明:将响应码转换，集成到数据提回中统一处理

程 序 员:YangDong
修改日期:20130524
修改说明:响应码转换，支持只转响应码，不转换响应信息

程 序 员:YangDong
修改日期:20141018
修改说明:DCI改造
*********************************************************************/
#include "gaps_head.h"
#include <sys/time.h>
#include <sys/timeb.h>
#include "app_head.h"
#include "batch_head.h"

static struct timeb starttime,endtime;

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_SJTH.so</soname>\
        <sosrcname>BAT_SJTH.c</sosrcname>\
        <sonote>BATCH数据提回组件集合</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"YangDong\" filesize=\"1236294\">HS-AgentV2.1整理</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2013-2-25 15:08\" programer=\"YangDong\" filesize=\"1236294\">使用Prepare提高数据库操作效率</rec>\
        <rec ver=\"2.1.0.3\" modify=\"2013-3-1 15:08\" programer=\"YangDong\" filesize=\"1236294\">把响应码转换集成到数据提回中处理</rec>\
        <rec ver=\"2.1.0.4\" modify=\"2013-5-24 15:08\" programer=\"YangDong\" filesize=\"1236294\">支持只转换响应码，不转换信息信息</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1236294\">DCI改造</rec>\
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

/* 响应码转换,返回转换后响应码在响应码数组中的位置 */
/* 参数说明
sResp:响应码数组
iResoCount:响应码组数
sResp_S：传入原响应码
iPos：输出目的响应信息位置
 */
int prv_resp_conv( char sResp[][10+1] , int iRespCount, char* sResp_S, int* iPos )
{
    int i = 0;
    for( i = 0; i < iRespCount; i++ )
    {
        if( strcmp( sResp[i], sResp_S ) == 0 )
        {
            *iPos = i;
            return *iPos;
        }
    }
    *iPos = -1;
    return -1;
}

void prv_free_data( char ** sdata, int iCount )
{
    int i;
    for (i = 0; i < iCount; i++ )
    {
        if (sdata[i])
        {
            free(sdata[i]);
            sdata[i] = NULL;
        }
    }

    free(sdata);

    return ;
}


/* 汇总处理 */
int prv_sjth_totalProc(HXMLTREE lXmlhandle, char *lineBuf, 
                 BATCH_FILESORT *pFileSort, double* dTotalAmt, int* iTotalCount ,i_list_t *t_fileTotalSortList,i_list_t *t_fileColumnList)
{
    int count=-1;
    char itemBuf[BATCH_MAX_FILE_COL_LEN];
    char xmlNode[128];
    char sDiv[BATCH_MAXLEN_DIV+1];
    char sFmt[32];
    double     dTmp=0.00;
    int  iLen = 0;
    int  i = 0, j = 0, position = 0;
    char tmpBuf[BATCH_MAX_FILE_COL_LEN];

    LOG(LM_DEBUG,Fmtmsg("BATCH: 汇总信息处理[%s]: ",lineBuf ),"DEBUG")
    
    /*trim回车换行符*/
    iLen = strlen( lineBuf );
    if( lineBuf[iLen-1] == 10 || lineBuf[iLen-1] == 13 )
    {
        lineBuf[iLen-1] = 0;
    }

    if( lineBuf[iLen-2] == 10 ||  lineBuf[iLen-2] == 13 )
    {
        lineBuf[iLen-2] = 0;
    }

    for( pfileColumnIter = i_list_begin(t_fileColumnList); 
         pfileColumnIter!= i_list_end(t_fileColumnList); 
             pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        
        memset(itemBuf, 0, sizeof(itemBuf));
        /* parse this total's record */
        if ( pFileSort->fileclasssn == gSFileColumn->fileclasssn )
        {
            switch( pFileSort->columnflag[0] )
            {
                 case BATCH_FILESORT_COLUNM_FIX:  /* 定长 */
                     memcpy(itemBuf, lineBuf+gSFileColumn->offset-1,gSFileColumn->columnlen);
                     break; 
                 case BATCH_FILESORT_COLUNM_SPLIT_TAIL:/* 去尾分隔符 */

                 case BATCH_FILESORT_COLUNM_SPLIT:/* 分隔符 */
                     fprv_getSubStr(lineBuf, gSFileColumn->columnsn, pFileSort->columnsprtr, itemBuf);
                     break; 
                 default:
                     break; /* 默认不处理 */
             }

             /* 20121105 added by yangdong  增加汇总信息的数据格式处理 */
            if( gSFileColumn->izoom != 0 )  /* 如果有偏移,计算偏移后数值 */
            {
                dTmp=atof(itemBuf)*pow(10,-gSFileColumn->izoom);
                if( gSFileColumn->iprecision < 1 )
                    gSFileColumn->iprecision = 2;  /* 默认小数精度2 */
                sprintf(sFmt,"%%.%df",gSFileColumn->iprecision);
                snprintf(itemBuf, sizeof( itemBuf ), sFmt,dTmp);
            }
             /* 处理填充字符 */
            if ( gSFileColumn->ifiller > 0 && gSFileColumn->columnlen > 0 )  
            {
                memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
                strcpy( tmpBuf, itemBuf );
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
                    memset( itemBuf, 0x00, sizeof( itemBuf ) );
                    memcpy( itemBuf, tmpBuf+position, gSFileColumn->columnlen - position );
                    itemBuf[ gSFileColumn->columnlen -  position] = '\0';
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
                    memset( itemBuf, 0x00, sizeof( itemBuf ) );
                    memcpy( itemBuf, tmpBuf, position );
                    itemBuf[position] = '\0';
                }
                else /* 不设置对齐方式 */
                {
                    j = 0;
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* 查找非填充字符 */
                         if( tmpBuf[i] != gSFileColumn->ifiller )
                         {
                             itemBuf[j++]= tmpBuf[i] ; 
                         }
                    } 
                    itemBuf[j] = '\0';
                }
            }
            /*  end of add */

             trim(gSFileColumn->lsx);
             if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_SETXML) == 0) /* 列属性，设置xml*/
             {
                 trim( gSFileColumn->fldref );
                 memset(xmlNode,0,sizeof(xmlNode));
                 if ( gSFileColumn->fldref[0] == '/')
                 {
                     snprintf( xmlNode, sizeof( xmlNode ),  "%s",gSFileColumn->fldref );
                 }
                 else
                 {
                     snprintf( xmlNode, sizeof( xmlNode ), "/batch/%s",gSFileColumn->fldref );
                 }
                 COMP_SOFTSETXML(xmlNode, itemBuf);
             }
             else if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_ZJE) == 0) /* 列属性，总金额*/
             {
                 *dTotalAmt = atof( itemBuf );
             }
             else if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_ZBS ) == 0) /* 列属性，总笔数*/
             {
                 *iTotalCount = atoi( itemBuf );
             }
             count=0;
        }
    }
    return count;
}

/* 明细处理 */
int prv_sjth_detailProc(HXMLTREE lXmlhandle,char *inBuf,int iPos, char *sSubItem,BATCH_FILESORT *pFileSort, double* dDetailAmt ,i_list_t *t_fileColumnList)
{
    char sDiv[BATCH_MAXLEN_DIV+1];
    char itemBuf[BATCH_MAX_FILE_COL_LEN];
    char sFmt[64];
    /*int  failed=0;*/
    /*int  iVal=0;*/
    double dVal = 0.00;
    int  ret;
    int  iLen;
    int  iFound = 0;
    int  i = 0 ,j = 0, position = 0;
    char tmpBuf[BATCH_MAX_FILE_COL_LEN];
    
    /*trim回车换行符*/
    iLen = strlen( inBuf );
    if( inBuf[iLen-1] == 10 || inBuf[iLen-1] == 13 )
    {
        inBuf[iLen-1] = 0;
    }

    if( inBuf[iLen-2] == 10 ||  inBuf[iLen-2] == 13 )
    {
        inBuf[iLen-2] = 0;
    }
    /* 根据映射关系的主机结果位置与文件列信息，找到列配置信息，并获取对应列值 */
    iFound = 0;
    for( pfileColumnIter = i_list_begin(t_fileColumnList);
             pfileColumnIter!= i_list_end(t_fileColumnList);
                 pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = NULL; 
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        if( pFileSort->fileclasssn == gSFileColumn->fileclasssn &&  /* 明细 */
            gSFileColumn->columnsn == iPos ) /* 列序号 */
        {
            iFound = 1;
            break;
        }
    }
    if(  iFound != 1 ) /* 文件列配置信息未获取到 */
    {
        /*failed = -1;*/
        LOG(LM_STD,Fmtmsg("BATCH: filesort_sn[%d] column_sn[%d] pos[%d]",\
            pFileSort->fileclasssn, gSFileColumn->fileclasssn,iPos ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_NOTFOUND,MSG_BATCH_FILECOLUMN_NOTFOUND);
        return -1;
    }

    memset(itemBuf, 0, sizeof(itemBuf));
    if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_FIX ) /* 定长 */
    {
        memcpy(itemBuf,inBuf+gSFileColumn->offset-1,gSFileColumn->columnlen);
        trim(itemBuf);
    }
    else if ( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT || /* 分割符*/
              pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL ) /* 去尾分割符*/
    {
         fprv_getSubStr(inBuf, iPos, pFileSort->columnsprtr, itemBuf);
    }
    else /* 其他不支持 */
    {
        /*failed=-2;*/
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_FF, MSG_BATCH_WJGS_FF );
        return -1;
    }    
    /* 处理最后的换行回车符 */
    iLen = strlen( itemBuf ) ;
    if( itemBuf[iLen-1] == 10 ||  itemBuf[iLen-1] == 13 )
    {
        itemBuf[iLen-1] = 0;
        iLen -- ;
    }
    if( itemBuf[iLen-2] == 10 ||  itemBuf[iLen-2] == 13 )
    {
        itemBuf[iLen-2] = 0;
        iLen -- ;
    }

    /* 处理填充字符 */
    if ( gSFileColumn->ifiller > 0 )  
    {
        position = iLen ;
        memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
        strcpy( tmpBuf, itemBuf );
        if ( gSFileColumn->regular[0] == 'R' )   /* 右对齐 */
        {
            for( i = 0; i<= iLen; i++ )
            {
                 /* 查找有效字符开始位置 */
                 if( tmpBuf[i] != gSFileColumn->ifiller )
                 {
                     position = i; 
                     break;
                 }
            } 
            memset( itemBuf, 0x00, sizeof( itemBuf ) );
            memcpy( itemBuf, tmpBuf+position, iLen - position );
        }
        else if ( gSFileColumn->regular[0] == 'L' )   /* 左对齐 */
        {
            for( i = 0; i<= iLen; i++ )
            {
                 /* 查找填充字符开始位置 */
                 if( tmpBuf[i] == gSFileColumn->ifiller )
                 {
                     position = i; 
                     break;
                 }
            } 
            memset( itemBuf, 0x00, sizeof( itemBuf ) );
            memcpy( itemBuf, tmpBuf, position );
        }
        else /* 不设置对齐方式 */
        {
            j = 0;
            for( i = 0; i<= iLen; i++ )
            {
                 /* 查找非填充字符 */
                 if( tmpBuf[i] != gSFileColumn->ifiller )
                 {
                     itemBuf[j++]= tmpBuf[i] ;
                 }
            }
            itemBuf[j] = '\0';
        }
    }

    /* 处理数据偏移 */
    if ( gSFileColumn->izoom != 0 )  
    {
        dVal = atof(itemBuf)*pow(10,-gSFileColumn->izoom);
        sprintf( sFmt,"%%.%df", gSFileColumn->iprecision );
        snprintf( itemBuf, sizeof( itemBuf ), sFmt, dVal );
    }

    if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_ADD) == 0)/* 交易金额累加 */
    {
         *dDetailAmt += atof( itemBuf );
    }
    strcpy( sSubItem, itemBuf );
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_SJTH
组件名称:BATCH_SJTH
组件功能: 批量业务生成数据提回文件模板
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
    1   1-输入    主机文件名    416XML解析字符串  *      N      
    2   1-输入    业务表名      416XML解析字符串  *      N    
    3   1-输入    映射标识      416XML解析字符串  *      N    
    4   1-输入    文件标识      416XML解析字符串  *      N      
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_SJTH(HXMLTREE lXmlhandle)
{
    char sSqlStr[2048];
    char sSqlUpd[2048];
    int  iAllcount=0;
    int  iCount = 0;
    int  iCount2 = 0;
    BATCH_FILEMAP sdb_batch_filemap;
    char **sdata;
    char sResp_S[10+1]; 
    char sResp_D[20+1]; 
    char sMsg_D[20+1]; 
    char sResp_Bz[1+1]; 
    char sFileFullName[128];
    int  iParas,iResult;
    char sBuf[256];
    char linebuf[BATCH_MAX_FILELINE_BYTE];
    char sTableName[40+1];
    char sFileName[256]; /* 主机返回文件全名(带路径) */
    char sFileID[40+1];
    char sMapID[40+1];   /* 映射标识 */
    int  iTSortCount=0;
    char sRespID[40+1];  /* 响应码转换标识 */
    int  i,iAbort=0;
    char sPtpch[8+1];
    char sPkrq[8+1];
    char sNode[32+1];
    FILE *srcfp;
    FILE *fp1;
    char sFileType[2+1];
    int  iTotalCount = 0;    /* 汇总信息总笔数 */     
    int  iTotalRows = 0;
    int  iDetailEndRow= 0;   /* 明细最后一行行号 */
    double dTotalAmt = 0.00;  /* 汇总信息总金额 */
    double dDetailAmt = 0.00; /* 明细总金额 */
    int  iClassPre = 0;       /* 上一分类序号 */
    int  iRearClass = 1;
    int  ii = 0, index = 0;
    int  iDetailCount = 0;
    int  updFlag = 0;
    int  valFlag = 0;
    int  iUniqueKey=1;/*更新条件是唯一索引 1-是*/
    int  pos[BATCH_MAX_TABLEREG_NUM];            /* 主机映射中，库表字段在主机返回文件中的位置*/

    int  iHostResp=0;
    int  iDsfResp=0;
    CURSOR cur;
    char sErrmsg[512];
    char sDbType[128];
    BATCH_MAPRESP sdb_batch_mapresp;
    int iRet = -1;
    int iType[256] = {0};
    int iSize[256] = {0};
    int iScale[256] = {0};
    int iflag =0;
    double  dDouble;
    int     iInt;

    /* added by yangdong 20130524 */
    int iHostXyxxFlag = 0;   /* 主机响应信息转换标志*/
    int iDsfXyxxFlag = 0;   /* 第三方响应信息转换标志*/

    char ssResp_S[BATCH_MAX_RESP][10+1];  /*主机响应码－源 */
    char ssResp_D[BATCH_MAX_RESP][20+1];  /*主机响应码－目的 */ 
    char ssMsg_D[BATCH_MAX_RESP][40+1];   /*主机响应信息 */
    char ssDFTResp_D[20+1]; 
    char ssDFTMsg_D[40+1]; 
    char sHostFileFlg[1+1];/*与主机交互标志*/
    char ssDsfResp_S[BATCH_MAX_RESP][10+1];  /*主机响应码－源 */
    char ssDsfResp_D[BATCH_MAX_RESP][20+1];  /*第三方响应码－目的 */
    char ssDsfMsg_D[BATCH_MAX_RESP][40+1];   /*第三方响应信息 */
    char ssDFTDsfResp_D[20+1];               /*默认响应码*/
    char ssDFTDsfMsg_D[40+1];                /*默认响应信息*/
    int  iPosXym = 0;                        /*响应码在更新语句中出现位置*/
    int  iPos = 0;                           /*响应码在响应信息数组中位置*/
    int  iHostValPos = 0;
    int  iDsfValPos  = 0;
    int  iFileValPos = 0;                     /*更新信息在回盘文件位置*/
    
    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    COMP_PARACOUNTCHKMIN(5)
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"文件名")
    pstrcopy(sFileName,sBuf,sizeof(sFileName));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"文件标识")
    pstrcopy(sFileID,sBuf,sizeof(sFileID));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"映射标识")
    pstrcopy(sMapID,sBuf,sizeof(sMapID));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"注册表名")
    pstrcopy(sTableName,sBuf,sizeof(sTableName));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(5,sBuf,"文件类型")
    pstrcopy(sFileType,sBuf,sizeof(sFileType));
    
    /* 批扣日期 */
    memset(sPkrq, 0, sizeof( sPkrq ) );
    COMP_SOFTGETXML( XMLNM_BATCH_PKRQ, sPkrq );
    trim(sPkrq);
    
    /* 平台批次号 */
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sPtpch);
    trim(sPtpch);

    /*根据参数删除上送主机请求文件*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sHostFileFlg, 0x00, sizeof(sHostFileFlg));
    COMP_SOFTGETXML(XMLNM_BATCH_HOSTFILE, sBuf);
    sHostFileFlg[0] = sBuf[0];
    if ( sHostFileFlg[0] == '1' )
    {/*需要删除与主机交互的文件*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/batch/sjth/wjxh", sBuf)
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", atoi(sBuf) );
        memset(sFileFullName, 0x00, sizeof(sFileFullName));
        COMP_SOFTGETXML(  sNode, sFileFullName );
        LOG(LM_STD,Fmtmsg("BATCH: 数据提回步点,%s-删除与主机交互的上送文件[%d][%s]",\
            sHostFileFlg,atoi(sBuf), sFileFullName ),"INFO");
        unlink( sFileFullName );
    }

    LOG(LM_STD,Fmtmsg("BATCH: file[%s],type[%s]table[%s]map[%s]",\
        sFileName, sFileType, sTableName, sMapID ),"INFO");

    memset( sDbType, 0x00, sizeof( sDbType ) );
    sprintf(sDbType, "%s", getenv("DB"));
    trim( sDbType );

    /* added by yangdong 20130312 默认响应信息初始化 */
    memset( ssDFTResp_D, 0x00, sizeof( ssDFTResp_D ) );
    memset( ssDFTMsg_D, 0x00, sizeof( ssDFTMsg_D ) );
    memset( ssDFTDsfResp_D, 0x00, sizeof( ssDFTDsfResp_D ) );
    memset( ssDFTDsfMsg_D, 0x00, sizeof( ssDFTDsfMsg_D ) );

    /* 获取主机响应码映射信息 */
    /* 转换标志 */
    COMP_SOFTGETXML(XMLNM_BATCH_ZJMAPINFO_ZHBZ,sBuf);
    trim( sBuf );
    if( sBuf[0] == '0' ) /* 0-需要转换 */
    {
        /* 获取转换标识 */
        memset( sRespID, 0x00, sizeof( sRespID ) );
        COMP_SOFTGETXML(XMLNM_BATCH_ZJMAPINFO_ZHBS, sRespID );
        trim( sRespID );
        if( strlen( sRespID ) < 2 ) /* 判断转换标识是否为空 */
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_RESPNULL,MSG_BATCH_RESPNULL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
        /* 查询对应响应转换标识信息 */
        sprintf(sSqlStr, "SELECT *  FROM BATCH_MAPRESP WHERE mapid='%s' " , sRespID);
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
        iHostResp= 0;
        /* 把主机响应码信息放入数组中 */
        memset( &sdb_batch_mapresp, 0x00, sizeof( BATCH_MAPRESP ) );
        while( ( iRet = DBFetch(cur, SD_BATCH_MAPRESP, NUMELE(SD_BATCH_MAPRESP), &sdb_batch_mapresp, sErrmsg ) ) > 0 )
        {
            if( iHostResp > BATCH_MAX_RESP )
            {
                fpub_SetMsg(lXmlhandle,MID_SYS_FAIL,"响应码转换信息数超过系统限制");
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                DCIFreeCursor(cur);
                return COMPRET_FAIL;
            }

            strcpy( sResp_S, sdb_batch_mapresp.resp_s );
            trim( sResp_S );
            strcpy( sResp_D, sdb_batch_mapresp.resp_d );
            trim( sResp_D );
            strcpy( sMsg_D, sdb_batch_mapresp.msg_d );
            trim( sMsg_D );
            strcpy( sResp_Bz, sdb_batch_mapresp.bz );
            trim( sResp_Bz );

            if( strlen( sMsg_D ) > 0 )
            {
                iHostXyxxFlag = 1;
            }
            memset( ssResp_S[iHostResp], 0x00, sizeof( ssResp_S[iHostResp] ) );
            memset( ssResp_D[iHostResp], 0x00, sizeof( ssResp_D[iHostResp] ) );
            memset( ssMsg_D[iHostResp], 0x00, sizeof( ssMsg_D[iHostResp] ) );
            strcpy( ssResp_S[iHostResp], sResp_S ); 
            strcpy( ssResp_D[iHostResp], sResp_D ); 
            strcpy( ssMsg_D[iHostResp], sMsg_D ); 
            /* 默认转换标识 */
            if( sResp_Bz[0] == '0' )
            {
                strcpy( ssDFTMsg_D, sMsg_D ); 
                strcpy( ssDFTResp_D, sResp_D); 
            }
            iHostResp ++;
            memset( sResp_S, 0x00, sizeof( sResp_S ) );
            memset( sResp_D, 0x00, sizeof( sResp_D ) );
            memset( sMsg_D, 0x00, sizeof( sMsg_D ) );
            memset( sResp_Bz, 0x00, sizeof( sResp_Bz ) );
            memset( &sdb_batch_mapresp, 0x00, sizeof( BATCH_MAPRESP ) );
        }
        DCIFreeCursor(cur);
        if( iRet < 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPSTATUS_FAIL;
        }
    }

    /* 获取第三方响应码映射信息 */
    /* 转换标志 */
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_ZHBZ,sBuf);
    trim( sBuf );
    if( sBuf[0] == '0' ) /* 0-需要转换 */
    {
        /* 获取转换标识 */
        memset( sRespID, 0x00, sizeof( sRespID ) );
        COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_ZHBS, sRespID );
        trim(  sRespID );
        if( strlen( sRespID ) < 2 ) /* 判断转换标识是否为空 */
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_RESPNULL,MSG_BATCH_RESPNULL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
        sprintf(sSqlStr, "SELECT *  FROM BATCH_MAPRESP WHERE mapid='%s' " , sRespID);
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

        memset( &sdb_batch_mapresp, 0x00, sizeof( BATCH_MAPRESP ) );
        iDsfResp = 0;
        /* 把第三方响应码信息放入数组中 */
        while( ( iRet = DBFetch(cur, SD_BATCH_MAPRESP, NUMELE(SD_BATCH_MAPRESP), &sdb_batch_mapresp, sErrmsg ) ) > 0 )
        {
            if( iDsfResp > BATCH_MAX_RESP )
            {
                fpub_SetMsg(lXmlhandle,MID_SYS_FAIL,"响应码转换信息数超过系统限制");
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            strcpy( sResp_S, sdb_batch_mapresp.resp_s );
            trim( sResp_S );
            strcpy( sResp_D, sdb_batch_mapresp.resp_d );
            trim( sResp_D );
            strcpy( sMsg_D, sdb_batch_mapresp.msg_d );
            trim( sMsg_D );
            strcpy( sResp_Bz, sdb_batch_mapresp.bz );
            trim( sResp_Bz );

            memset( ssDsfResp_S[iDsfResp], 0x00, sizeof( ssDsfResp_S[iDsfResp] ) );
            memset( ssDsfResp_D[iDsfResp], 0x00, sizeof( ssDsfResp_D[iDsfResp] ) );
            memset( ssDsfMsg_D[iDsfResp], 0x00, sizeof( ssDsfMsg_D[iDsfResp] ) );
            strcpy( ssDsfResp_S[iDsfResp], sResp_S ); 
            strcpy( ssDsfResp_D[iDsfResp], sResp_D ); 
            strcpy( ssDsfMsg_D[iDsfResp], sMsg_D ); 

            if( strlen( sMsg_D ) > 0 )
            {
                iDsfXyxxFlag = 1;
            }
            /* 默认转换标识 */
            if( sResp_Bz[0] == '0' )
            {
                strcpy( ssDFTDsfMsg_D, sMsg_D ); 
                strcpy( ssDFTDsfResp_D, sResp_D); 
            }
            iDsfResp ++;
            memset( &sdb_batch_mapresp, 0x00, sizeof( BATCH_MAPRESP ) );
        }
        DCIFreeCursor(cur);
        if( iRet < 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return MID_SYS_FAIL;
        }
    }

    /* 获取更新需要字段(更新条件和更新内容字段名) */
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    sprintf(sSqlStr, "SELECT * FROM BATCH_FILEMAP WHERE mapid='%s' AND ( thgxbz='1' OR thgxbz='2') ORDER BY thgxbz, columnsn" , sMapID );
    if ((cur = DCIDeclareCursor( sSqlStr, DCI_STMT_LOCATOR)) == -1)
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
    memset(&sdb_batch_filemap, 0, sizeof(sdb_batch_filemap));
    iCount=0;iCount2=0;
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    memset( sSqlUpd, 0x00, sizeof( sSqlUpd ) );
    sprintf( sSqlUpd, "UPDATE %s SET clzt='1', ", sTableName );
    strcpy( sSqlStr, "SELECT ");
    updFlag = 0;
    while( ( iRet = DBFetch(cur, SD_BATCH_FILEMAP, NUMELE(SD_BATCH_FILEMAP), &sdb_batch_filemap, sErrmsg ) ) > 0 )
    {
        iCount++;
        iCount2++;
        memset( sBuf, 0x00, sizeof( sBuf ) );

        /* 在第二个字段前加 , */
        if( iCount > 1 )
            strcat( sSqlStr,  ",");

        trim( sdb_batch_filemap.columnid );
        trim( sdb_batch_filemap.thgxbz );

        /* 记录库表字段在主机返回文件位置 */
        pos[iCount2] = sdb_batch_filemap.zjjgwz ;
        if( sdb_batch_filemap.thgxbz[0] =='2' ) /* 更新条件 */
        {
            if(  updFlag == 0 ) /* 第一个更新条件 */
            {
                /* 在第一个更新条件前面，增加主机响应码转换 */
                if( iHostResp > 0 )  /* 需要进行主机响应转换 */
                {
                    iHostValPos = iCount; /* 主机转换位置(在所有字段中位置) */
                    /* 转换主机响应信息---成功标志转换 */
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    sprintf( sBuf, " ,cgbz=:v%d" , iCount );
                    strcat( sSqlUpd, sBuf );
                    if( iHostXyxxFlag == 1 )  /* modified by yangdong 需要转换主机响应信息 */
                    {
                        iCount ++;
                        memset( sBuf, 0x00, sizeof( sBuf ) );
                        sprintf( sBuf, " ,xyxx=:v%d" , iCount );
                        strcat( sSqlUpd, sBuf );
            
                        /* 描述字段 */
                        strcat( sSqlStr,  "cgbz, xyxx," );
                    }
                    else
                    {
                        /* 描述字段 */
                        strcat( sSqlStr,  "cgbz, " );
                    }
                }
                /* 增加第三方响应码转换 */
                if( iDsfResp > 0 )
                {
                    if( iHostResp > 0 ) /*  前面已有主机响应码转换时 */
                        iCount ++;
                    iDsfValPos = iCount;  /* 第三方响应码转换位置(在所有字段中位置) */
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    sprintf( sBuf, " ,dsfxym=:v%d" , iCount );
                    strcat( sSqlUpd, sBuf );
                    if( iDsfXyxxFlag == 1 )  /* modified by yangdong 需要转换主机响应信息 */
                    {
                        iCount ++;
                        memset( sBuf, 0x00, sizeof( sBuf ) );
                        sprintf( sBuf, " ,dsfxyxx=:v%d" , iCount );
                        strcat( sSqlUpd, sBuf );
                        /* 描述字段 */
                        strcat( sSqlStr,  " dsfxym, dsfxyxx," );
                    }
                    else
                    {
                        /* 描述字段 */
                        strcat( sSqlStr,  " dsfxym ," );
                    }
                }

                if( ( iDsfResp > 0 )  ||  ( iHostResp > 0 ) )
                    iCount ++;

                /* 追加WHERE 条件 */
                memset(sBuf, 0x00, sizeof(sBuf));
                if ( strcmp(sdb_batch_filemap.columnid, "lsxh") == 0)
                {
                    sprintf( sBuf, " WHERE pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch  );
                    iUniqueKey=1;
                }else
                {
                    sprintf( sBuf, " WHERE 1=1  " );
                    iUniqueKey=0;
                }
                
                strcat( sSqlUpd, sBuf );
            }
            updFlag ++;
            /*  需求201702140361,去掉trim,提高效率
            if ( strcmp(sdb_batch_filemap.columnid, "lsxh") == 0)
            {
                sprintf( sBuf, " AND %s =:v%d" , sdb_batch_filemap.columnid, iCount );
            }else
            {
                sprintf( sBuf, " AND trim(%s) =:v%d" , sdb_batch_filemap.columnid, iCount );
            }
            */
            sprintf( sBuf, " AND %s =:v%d" , sdb_batch_filemap.columnid, iCount );
        }
        else if( sdb_batch_filemap.thgxbz[0] == '1' ) /* 更新内容 */
        {
            valFlag ++;
            if( valFlag == 1 )
                sprintf( sBuf, " %s=:v%d" , sdb_batch_filemap.columnid, iCount );
            else
                sprintf( sBuf, " ,%s=:v%d" , sdb_batch_filemap.columnid, iCount );

            /* 记录响应码位置 */
            if( memcmp(  sdb_batch_filemap.columnid,"xym", 3 ) == 0 ||
                memcmp(  sdb_batch_filemap.columnid,"XYM", 3 ) == 0 )
                iPosXym = iCount;
        }
        strcat( sSqlUpd, sBuf );
        strcat( sSqlStr,  sdb_batch_filemap.columnid );
        memset(&sdb_batch_filemap, 0, sizeof(sdb_batch_filemap));
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        LOG(LM_STD,Fmtmsg(MSG_SQL_ERROR),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }

    if( updFlag == 0 || valFlag == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_NOCONFIG,MSG_BATCH_SJTH_NOCONFIG);
        LOG(LM_STD,Fmtmsg(MSG_BATCH_SJTH_NOCONFIG),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    if ( iUniqueKey == 0)
    {/*更新条件不是唯一索引 0-不是 */
        memset(sBuf, 0x00, sizeof(sBuf));
        sprintf( sBuf, " AND  pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch  );
        strcat( sSqlUpd, sBuf );
    }

    memset( sBuf, 0x00, sizeof( sBuf ) );
    sprintf( sBuf, " FROM %s WHERE 1=2" , sTableName );
    strcat( sSqlStr, sBuf );

    if( strlen( sSqlUpd ) > 2048 || strlen( sSqlStr ) > 2048 )
    {
        LOG(LM_STD,Fmtmsg("SQLEN[%d][%d]超过限制2048", strlen( sSqlStr ) , strlen( sSqlUpd ) ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("UPDATE SQL[%s]", sSqlUpd ),"INFO")
    LOG(LM_STD,Fmtmsg("SELECT SQL[%s]", sSqlStr ),"INFO")


    /* 文件明细分类映射链表初始化 */
    iResult = fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_DETAIL,\
                                           &t_fileDetailSortList);
    if( iResult <= 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 文件明细分类映射链表初始化失败,[%s][%d]",\
                           sFileID,iResult ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                           Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    memset( &thisSort, 0, sizeof(BATCH_FILESORT) );
    /* 只取第一个明细分类信息 */
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* 文件列信息链表初始化 */
    iResult =fprv_initFileColumn(sFileID,&t_fileColumnList);
    if ( iResult <= 0)
    {
        LOG(LM_STD,Fmtmsg("BATCH: 文件列信息链表初始化失败,[%s]",sFileID),"ERROR");
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
                    Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 获取文件总行数 rows */
    /* 20110825 所有类型文件都获取行数 */
    /* 打开来盘文件 */
    if((fp1 = fopen(sFileName, "r")) == NULL)
    {
        batch_detailsortlistFree();
        batch_columnlistFree();
        LOG(LM_STD,Fmtmsg("BATCH: 打开主机提回文件[%s]失败",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    iTotalRows=0;
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, fp1 ) != NULL )
    {
        iTotalRows++ ;
    }
    /* 去除最后一行的回车换行,若有多个换行则无法解析 */
    if( 10 == linebuf[0] || 13 == linebuf[0] )
    {
        iTotalRows-- ;
    }
    LOG(LM_DEBUG,Fmtmsg("BATCH: 文件总行数[%d]", iTotalRows),"DEBUG");
    fclose(fp1);

    /*  打开主机返回文件处理 */
    index = 0;
    srcfp =fopen( sFileName, "r" );
    if ( srcfp == NULL )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 打开主机返回文件处理失败,[%s]",sFileName),"ERROR");
        batch_detailsortlistFree();
        batch_columnlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 汇总分类信息初始化 */
    /* 01 单明细 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
    if( strcmp( sFileType, "01" )  != 0 )
    {
        iTSortCount=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_TOTAL,\
                                          &t_fileTotalSortList);
        if( iTSortCount <= 0 )
        {
            fclose( srcfp );
            batch_detailsortlistFree();
            batch_columnlistFree();
            LOG(LM_STD,Fmtmsg("BATCH: 文件汇总分类映射链表初始化,[%s]",sFileID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                                   Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG,Fmtmsg("BATCH: 汇总记录数[%d]", iTSortCount ),"DEBUG")
    }
    /* 处理开头可能的汇总信息  */
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
            if( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
            {
                index ++;
                iResult = prv_sjth_totalProc(lXmlhandle,linebuf, &thisSortT, &dTotalAmt, &iTotalCount ,t_fileTotalSortList,t_fileColumnList);
                if( iResult != 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 汇总信息处理失败,[%s],[%d],[%s]",linebuf,\
                        thisSortT.fileclasssn,thisSortT.classname),"ERROR")
                    batch_totalsortlistFree();
                    batch_detailsortlistFree();
                    batch_columnlistFree();
                    fclose(srcfp);
                    fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_PROC,MSG_BATCH_SJTH_PROC);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
            iClassPre = thisSortT.fileclasssn;
        }
    }

    /* 计算最后一个明细信息的序号 */
    /* 01 单明细 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
   
    if( strcmp( sFileType,"01" ) == 0 || strcmp( sFileType,"02" ) == 0  )
        iDetailEndRow = iTotalRows;               /**/
    if( strcmp( sFileType,"03" ) == 0 )
        iDetailEndRow = iTotalRows - iTSortCount ; /* 减去汇总行数，为实际明细记录数最大序号 */
    if( strcmp( sFileType,"04" ) == 0 )
        iDetailEndRow = iTotalRows -iTSortCount + iClassPre ;
    /* 减去结尾汇总记录数，为实际明细记录数最大序号 */
    LOG(LM_DEBUG,Fmtmsg("BATCH: 明细尾记录行号[%d]", iDetailEndRow ),"DEBUG")

    /* 获取更新语句所需字段信息 */
    cur = DCIDeclareCursor(sSqlStr, 0);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    DCIExecute(cur);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    iAllcount = DCINumCols(cur);                        /* 取字段数 */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    pos[0] = iAllcount;

    sdata = calloc ( iAllcount, sizeof(void *));
    if ( sdata == NULL )
    {
        LOG(LM_STD,Fmtmsg("分配内存操作失败!" ),"ERROR")
        DCIFreeCursor(cur);
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }

    iflag = 0;
    for (iCount = 0;iCount < iAllcount ;iCount++)
    {
        iType[iCount] = DCIColType(cur, iCount);     /* 取字段类型 */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
            iflag = -22;
            break;
        }
        iSize[iCount] = DCIColSize(cur, iCount);     /* 取字段大小 */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
            iflag = -23;
            break;
        }

        iScale[iCount] = DCIColScale(cur, iCount);    /* 取字段精度 */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
            iflag = -24;
            break;
        }

        switch ( iType[iCount] )
        {
            case DCIT_INTEGER:    /* INTEGER */
                sdata[iCount] = calloc(1, sizeof(int));
                if ( sdata[iCount] == NULL )
                {
                    iflag = -25;
                    break;
                }
                iSize[iCount] = sizeof(int);
                break;
            case DCIT_NUMERIC:    /* numeric */
                iType[iCount]=DCIT_DOUBLE;
            case DCIT_DOUBLE:    /* double */            
                sdata[iCount] = calloc(1, sizeof(double));
                if ( sdata[iCount] == NULL )
                {
                    iflag = -26;
                    break;
                }
                iSize[iCount] = sizeof(double);                
                break;
            case DCIT_DATE:
                sdata[iCount] = calloc(1, sizeof(DCIDate));
                if ( sdata[iCount] == NULL )
                {
                    iflag = -27;
                    break;
                }
                break;
           case DCIT_CHAR:
           case DCIT_VARCHAR:
                  iSize[iCount]++; /*char类型分配内存字段长度应该加1*/ 
                  sdata[iCount] = calloc(iSize[iCount], sizeof(char));
                  if ( sdata[iCount] == NULL )
                  {
                     iflag = -28;
                     break;
                  }
                  break;
            default:
                sdata[iCount] = calloc(iSize[iCount], sizeof(char));
                if ( sdata[iCount] == NULL )
                {
                    iflag = -29;
                    break;
                }
                break;
       }
    }
    DCIFreeCursor(cur);

    if( iflag < 0 )
    {
        prv_free_data( sdata, iAllcount );
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if ((cur = DCIDeclareCursor(sSqlUpd, DCI_STMT_LOCATOR)) == -1)
    {
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fclose(srcfp);
        prv_free_data( sdata, iAllcount );
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    for (iCount = 0;iCount < iAllcount ;iCount++)
    {
        if( iType[iCount] == DCIT_NUMERIC || iType[iCount] == DCIT_INTEGER ||
                         iType[iCount] ==  DCIT_DOUBLE || iType[iCount] == DCIT_FLOAT  )
        {
            if( iScale[iCount] > 0 )
            {
                DCIBindPara( cur, iCount, sdata[iCount], iSize[iCount], DCIT_DOUBLE );
            }
            else
            {
                DCIBindPara( cur, iCount, sdata[iCount], sizeof(int), DCIT_INTEGER );
            }
        }
        else /* 做字符型处理 */
        {
            DCIBindPara( cur, iCount, sdata[iCount], iSize[iCount], iType[iCount]);
        }

        if ( DCIERR )
        {
            batch_totalsortlistFree();
            batch_detailsortlistFree();
            batch_columnlistFree();
            fclose(srcfp);
            DCIFreeCursor(cur);
            prv_free_data( sdata, iAllcount );
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
       }
    }

    /* 开始处理明细 */
    memset(linebuf, 0, sizeof(linebuf));
    iDetailCount = 0;
    /* for cal time cast */
    ftime(&starttime);
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        index ++;
        /* 过滤空行  */
        if ( 0 == linebuf[0] || 13 == linebuf[0] )
        {
            continue;
        }

        /*  判断是否到最后一行明细  */
        if( index > iDetailEndRow )
        {
            index --;
            break;
        }
        iDetailCount ++;  /* 明细行数 */

        memset(sBuf, 0, sizeof(sBuf));

        iCount = 0;
        iAbort = 0;
        iFileValPos = iCount+1; /* 先处理文件中获取需要更新信息 */
        /* iAllcount 为实际需要处理字段数 */
        while ( iCount < iAllcount )
        {
            if( iCount+1 == iHostValPos ) /* 需要处理的主机响应码的字段位置到了*/
            {
                iPos = -1;
				iResult = prv_resp_conv( ssResp_S,iHostResp, sResp_S, &iPos);
				if( iResult < 0 ) /* 转换失败，取默认值 */
                {
                    pstrcopy(sdata[iCount], ssDFTResp_D, iSize[iCount]); 
                }else
                {
                    pstrcopy(sdata[iCount], ssResp_D[iPos], iSize[iCount]); 
                }
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: 绑定字段[%d] 值为[%s], size[%d] type[%d]", \
         iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                if( iHostXyxxFlag == 1 )  /* modified by yangdong 需要转换主机响应信息 */
                {
                    iCount  ++;
                    /* 处理响应信息 */
                    if( iResult < 0 )  /* 转换失败，取默认值 */
                    {
                        strcpy( sdata[iCount], ssDFTMsg_D ); 
                    }
                    else 
                        strcpy( sdata[iCount], ssMsg_D[iPos] ); 
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: 绑定字段[%d] 值为[%s], size[%d] type[%d]", iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                }
            }
            else if( iCount+1 == iDsfValPos ) /* 需要处理的第三方响应码的字段位置到了*/
            {
                iPos = -1;
                iResult = prv_resp_conv( ssDsfResp_S,iDsfResp, sResp_S, &iPos );
                /* 处理响应码 */
                if( iResult < 0 )  /* 转换失败，取默认值 */
                    strcpy( sdata[iCount], ssDFTDsfResp_D ); 
                else
                    strcpy( sdata[iCount], ssDsfResp_D[iPos] ); 
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: 绑定字段[%d] 值为[%s], size[%d] type[%d]", iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                if( iDsfXyxxFlag == 1 )  /* modified by yangdong 需要转换主机响应信息 */
                {
                    iCount  ++;
                    /* 处理响应信息 */
                    if( iResult < 0 )  /* 转换失败，取默认值 */
                        strcpy( sdata[iCount], ssDFTDsfMsg_D ); 
                    else
                        strcpy( sdata[iCount], ssDsfMsg_D[iPos] ); 
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: 绑定字段[%d] 值为[%s], size[%d] type[%d]", iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                }
            }
            else /*  从文件中获取需要处理信息 */
            {
                /* 处理明细：获取更新字段值，更新条件 */
                memset(sBuf, 0x00, sizeof(sBuf));
                iResult = prv_sjth_detailProc(lXmlhandle,linebuf,pos[iFileValPos], sBuf,&thisSort,&dDetailAmt,t_fileColumnList);
                if( iResult < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息处理失败,pos[%d]=[%d],[%d],[%s]: [%d],[%s]",\
                        iFileValPos,pos[iFileValPos],index,linebuf,thisSort.fileclasssn,thisSort.classname),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
                    iAbort = -3;
                    break;
                }
                /* 提回更新时，trim字段 */
                trim( sBuf );
                
                if( iType[iCount] == DCIT_CHAR || iType[iCount] == DCIT_VARCHAR||
                    iType[iCount] == DCIT_DATE || iType[iCount] == DCIT_CLOB )
                {
                    if (strlen(sBuf) > iSize[iCount]-1)
                    {
                        memcpy(sdata[iCount], sBuf, iSize[iCount]-1);
                        LOG(LM_STD,Fmtmsg("BATCH: 数据[%s]超长,%d位后字段被自动截取", sBuf, iCount ),"ERROR")
                    }
                    else
                        strcpy( sdata[iCount], sBuf );  /* sBuf已做类型处理 */
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: 绑定字段[%d] 值为[%s], size[%d] type[%d] scale[%d]", \
                          iCount, sdata[iCount], iSize[iCount], iType[iCount], iScale[iCount] ),"INFO")
*/
                }
                else if( iType[iCount] == DCIT_NUMERIC || iType[iCount] == DCIT_INTEGER ||
                         iType[iCount] ==  DCIT_DOUBLE || iType[iCount] == DCIT_FLOAT  )
                {
                    if( iScale[iCount] > 0 )
                    {
                        dDouble = atof( sBuf);
                        *(double *)sdata[iCount] = dDouble;
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: 绑定字段[%d] 值为[%f], size[%d] type[%d] scale[%d]", \
                          iCount, *(double *)sdata[iCount], iSize[iCount], iType[iCount], iScale[iCount] ),"INFO")
*/
                    }
                    else
                    {
                        iInt = atoi( sBuf );
                        *(int *)sdata[iCount] = iInt;
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: 绑定字段[%d] 值为[%d], size[%d] type[%d] scale[%d]", \
                          iCount, *(int *)sdata[iCount] , iSize[iCount], iType[iCount], iScale[iCount] ),"INFO")
*/
                    }
                }

                /* 响应码获取 */
                if( iCount+1 == iPosXym ) 
                {
                    strcpy( sResp_S, sBuf );
/*
LOG(LM_DEBUG,Fmtmsg("xym[%s] ", sResp_S ),"INFO");
*/
                }

                iFileValPos ++;
            }
            iCount  ++;
        }

        if ( iAbort == 0  )
        {
            iRet = DCIExecute(cur);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息处理ret[%d] sqlerr[%s] 明细行数[%d]",\
                    iRet, DCILastError(), iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            }else if ( iRet == 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息处理ret[%d] 更新记录数为零条 明细行数[%d]",\
                    iRet, iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_UPDZERO,MSG_BATCH_SJTH_UPDZERO);
            }else if ( iRet > 1 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息处理ret[%d] 更新记录数大于壹条 明细行数[%d]",\
                    iRet, iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_UPDMULT,MSG_BATCH_SJTH_UPDMULT);
            }
            if ( iRet != 1 )
            {
                /* added by yangdong 20141204 增加出错信息，帮助排错 */
                for (iCount = 0;iCount < iAllcount ;iCount++)
                {
                    if( iType[iCount] == DCIT_NUMERIC || iType[iCount] == DCIT_INTEGER ||
                         iType[iCount] ==  DCIT_DOUBLE || iType[iCount] == DCIT_FLOAT  )
                    {
                        if( iScale[iCount] > 0 )
                        {
                            LOG(LM_STD,Fmtmsg("BATCH: v%d val[%f] ",iCount+1, *( double* )sdata[iCount]  ),"ERROR");
                        }
                        else
                        {
                            LOG(LM_STD,Fmtmsg("BATCH: v%d val[%d]",iCount+1, *( int* )sdata[iCount] ),"ERROR");
                        }
                    }
                    else
                    {
                        LOG(LM_STD,Fmtmsg("BATCH: v%d val[%d][%s] ",iCount+1, iType[iCount],  ( char* )sdata[iCount]  ),"ERROR");
                    }
                }
                iAbort = -21;
                break;
            }
            /* 定量提交事务，减轻系统压力 */
            if( ( iDetailCount % 5000 ) == 0 )
            {
                ftime(&endtime);
                LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息更新处理[%d],cast[%ld]ms", iDetailCount,\
                (endtime.time-starttime.time)*1000+endtime.millitm-starttime.millitm ),"DEBUG");
                if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
                {
                    /*if ( sql_CommitTrans() !=MID_SYS_SUCC )*/
                    if(DCICommit() != 0)
                    {
                        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                        /*sql_RollbackTrans();*/
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                        iAbort = -22;
                        break;
                    }
                }
                ftime(&starttime);
            }
        }
        else
        {
            LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息处理[%d]",iAbort ),"INFO");
            break;
        }

        memset(linebuf, 0, sizeof(linebuf));
    }

    /*if ( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        sql_RollbackTrans();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPSTATUS_FAIL ;
    }

    DCIFreeCursor(cur);
    prv_free_data( sdata, iAllcount );
LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细文件处理总数[%d] 总金额[%.2f]",iDetailCount, dDetailAmt ),"INFO");
    if ( iAbort == 0  )
    {
        /* 处理尾部汇总信息 */
        /* 01 单明细 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
        if( ( strcmp( sFileType, "03" ) == 0 ||  strcmp( sFileType, "04" ) == 0 ) && ! iAbort )
        {
            ii = 0;
            /* 配置保证分类信息顺序 */
            for( pfileTotalSortIter = i_list_begin(t_fileTotalSortList);
                  pfileTotalSortIter != i_list_end(t_fileTotalSortList);
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
                    ;
                }
                else
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 取汇总记录信息失败"),"ERROR")
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_TOTAL,MSG_BATCH_PROC_TOTAL);
                    iAbort = -24;
                    break;
                }
    
                iResult = prv_sjth_totalProc(lXmlhandle,linebuf, &thisSortT, &dTotalAmt,&iTotalCount ,t_fileTotalSortList,t_fileColumnList);
                if( iResult != 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 汇总信息处理失败,[%s],[%d],[%s]",\
                        linebuf,thisSortT.fileclasssn,thisSortT.classname),"ERROR")
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_TOTAL,MSG_BATCH_PROC_TOTAL);
                    iAbort = -25;
                    break;
                }
    
                ii++;
            }
        }
    }
    
    fclose( srcfp );
    /* 释放链表资源 */
    batch_totalsortlistFree();
    batch_detailsortlistFree();
    batch_columnlistFree();
    
    /* 处理异常 */
    if ( iAbort != 0  )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 提回文件更新处理错误: [%d]",iAbort),"ERROR");
        /* 响应信息 */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPSTATUS_FAIL ;
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: 文件汇总记录数[%d] 汇总总金额[%.2f]", iTotalCount, dTotalAmt),"DEBUG")

    if( dTotalAmt > 0.001 ) /* 如果有汇总金额信息 */
    {
        /* 判断汇总记录和明细是否匹配  */
        if( ( dTotalAmt - dDetailAmt ) > 0.001 || ( dDetailAmt - dTotalAmt ) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 提回文件汇总金额[%.2f]明细合计金额[%.2f]",\
                                dTotalAmt, dDetailAmt),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_ZJE, MSG_BATCH_SJTH_ZJE );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPSTATUS_FAIL ;
        }
    }
    if( iTotalCount > 1 ) /* 如果有汇总笔数信息 */
    {
        /* 判断汇总记录和明细是否匹配  */
        if( iTotalCount != iDetailCount )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 提回文件汇总笔数[%d]明细合计笔数[%d]",\
                                iTotalCount , iDetailCount),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_ZBS, MSG_BATCH_SJTH_ZBS );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPSTATUS_FAIL ;
        }
    }

    /*if ( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        sql_RollbackTrans();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPSTATUS_FAIL ;
    }

    /* added by yangdong 20130609 增加响应码转换范围 1：只转换审核失败信息 */
    COMP_SOFTSETXML( XMLNM_BATCH_SJHP_CVTRESP, "1" );

    /* added by yangdong 20130613 增加处理，如果核心不返回实际校验金额，则将实际金额置为0.00 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_HOST_AMT_FLAG,sBuf);
    if( sBuf[0] == '1' )  /* 1-不返回 0-返回（默认） ( 不设置本参数则不处理 ) */
    {
        memset( sSqlUpd, 0x00, sizeof( sSqlUpd ) );
        memset( sBuf, 0x00, sizeof( sBuf ) );
        COMP_SOFTGETXML( XMLNM_BATCH_SJTH_ZJXH,sBuf);
        /* 将成功明细的实际金额置为交易金额 */
        sprintf( sSqlUpd, "UPDATE %s SET sjje=jyje WHERE pkrq='%s' AND ptpch='%s' AND wjxh=%d AND cgbz='0' ", \
            sTableName, sPkrq, sPtpch,  atoi( sBuf ) );
        
        /*sql_BeginTrans();  用DCIBegin 代替 2015-1-7 by chenxm*/
        DCIBegin();
        iRet = DCIExecuteDirect( sSqlUpd );
        if( iRet < 0  )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            /*sql_RollbackTrans();*/
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_PLRW,MSG_BATCH_UPD_PLRW );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
        if(DCICommit() != 0)
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /* end of add */

    /*根据参数删除主机响应文件*/
    if ( sHostFileFlg[0] == '1' )
    {/*需要删除与主机交互的文件*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/batch/sjth/wjxh", sBuf)
        memset( sNode, 0x00, sizeof( sNode ) );
        LOG(LM_STD,Fmtmsg("BATCH: 数据提回步点,%s-删除与主机交互的响应文件[%d][%s]",\
            sHostFileFlg,atoi(sBuf), sFileName ),"INFO");
        unlink( sFileName );
    }
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_SJTH_SUM
组件名称:BATCH_SJTH_SUM
组件功能:统计数据回盘后的成功失败信息
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
使用限制:
程 序 员:
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_SJTH_SUM(HXMLTREE lXmlhandle)
{
    int  iParas,iResult;
    char sBuf[128];
    char sTableName[50+1];
    char sCondStr[256];
    char sPkrq[8+1];
    char sPtpch[8+1];
    int  iTotalNum=0;
    double dTotalAmt=0.00;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    /* 明细表名 */
    memset(sBuf,0,sizeof(sBuf));
    memset(sTableName,0,sizeof(sTableName));
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf);
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    /* 批扣日期 */
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* 平台批次号 */
    memset(sBuf,0,sizeof(sBuf));
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf );
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    iTotalNum = 0;
    dTotalAmt = 0.00;
    sprintf( sCondStr, " pkrq='%s' AND ptpch='%s' AND ( cgbz='0' OR cgbz='1' ) ", sPkrq, sPtpch );
    iResult=SumWithCondSql( sCondStr, sTableName, "sjje", &iTotalNum, &dTotalAmt );
    if( iResult < 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC,iResult));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 笔数 */
    COMP_SOFTSETXML( XMLNM_BATCH_CGZBS, itoa( iTotalNum ) );
    /* 交易金额 */
    sprintf( sBuf, "%.2f", dTotalAmt );
    COMP_SOFTSETXML(  XMLNM_BATCH_CGZJE, sBuf );
    LOG(LM_DEBUG,Fmtmsg("BATCH:数据提回,成功总笔数[%d],成功总金额[%.2f]",iTotalNum,dTotalAmt),"DEBUG")

    iTotalNum = 0;
    dTotalAmt = 0.00;
    sprintf( sCondStr, " pkrq='%s' AND ptpch='%s' AND ( cgbz != '0' AND cgbz != '1' ) ", sPkrq, sPtpch );
    iResult=SumWithCondSql( sCondStr, sTableName, "jyje", &iTotalNum, &dTotalAmt );
    if( iResult < 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC,iResult));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 笔数 */
    COMP_SOFTSETXML( XMLNM_BATCH_SBZBS, itoa( iTotalNum ) );
    /* 交易金额 */
    sprintf( sBuf, "%.2f", dTotalAmt );
    COMP_SOFTSETXML(  XMLNM_BATCH_SBZJE, sBuf );

    LOG(LM_DEBUG,Fmtmsg("BATCH:数据提回,失败总笔数[%d],失败总金额[%.2f]",iTotalNum,dTotalAmt),"DEBUG")

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

