/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT4.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_P2LJ.ec
文件描述:批量转联机批量业务组件
程 序 员:屠秋龙
发布日期:20161116

*********************************************************************/
#include "gaps_head.h"
#include "app_head.h"
#include "batch_head.h"
#include <sys/time.h>
#include <sys/timeb.h>

#define SOCOMPVERSION "V4.1.0.1"

static struct timeb starttime,endtime;

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_P2LJ.so</soname>\
        <sosrcname>BAT_P2LJ.c</sosrcname>\
        <sonote>BATCH批转联机组件集合</sonote>\
        <version>\
        <rec ver=\"4.1.0.1\" modify=\"2015-05-20 09:00\" programer=\"TUQL\" filesize=\"1238198\">初稿</rec>\
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

/************************************************************************
函数声明:
IRESULT fprv_sql_UnloadToBuffer(char *sBuffer,char *sSql,char cDiv,char cEscape,long *lResult)
函数功能:
  根据SQL查询结果集生成UNLOAD格式结果串
输入参数:
         char *sBuffer         数据字符串
         char *sSql            查询SQL语句
         char cDiv             分隔符      缺省为'|'
         char cEscape          转义字符    缺省为'\'
         long *lResult         插入记录条数(输出)
返    回:
         成功
           MID_SYS_SUCC
         失败
           MID_SYS_INVALID
           MID_SYS_OPENFILE
           MID_SYS_MEMALLOC

           MID_SQL_DESCRIBE
           MID_SQL_CUROPEN
           MID_SQL_CURFETCH

************************************************************************/
/*
 *根据字段的属性,取出该字段的内容.
 */
static int fprv_dyn_getdata_byattr(char* szDesdata,\
                                 int nDeslen,\
                                 int nType,\
                                 int nLen,\
                                 int nScale,\
                                 char* szSrcdata)
{
    char szTmpdata[4096];
    char sFmt[100];
    int  nDlen=0,nTmpdata=0;
    double dTmpdata=0.0;

    if ( nDeslen <= 0 || szDesdata == NULL )
        return -1;
    if ( nDeslen > sizeof(szTmpdata) )
        nDeslen = sizeof(szTmpdata);
    memset(szTmpdata,0,sizeof(szTmpdata));
    memset(sFmt,0,sizeof(sFmt));

    switch( nType )
    {
      case DCIT_INTEGER:        /* CS_INT_TYPE */
        nTmpdata = atoi(szSrcdata);
        sprintf(szTmpdata,"%d",nTmpdata);
        break;
      case DCIT_NUMERIC:  /* NUMERIC */
      case DCIT_DOUBLE:
        if ( nScale == 0 )
        {
          nTmpdata = atoi(szSrcdata);
          sprintf(szTmpdata,"%ld",nTmpdata);
        }
        else
        {
          sprintf(sFmt,"%%.%df",nScale);
          dTmpdata = atof(szSrcdata);
          sprintf(szTmpdata,sFmt,dTmpdata);
        }
        break;
      default:
        memcpy(szTmpdata,szSrcdata,nLen);
        break;
    }
    memset(szDesdata,' ',nDeslen);
    memcpy(szDesdata,szTmpdata,(nDeslen-1)<strlen(szTmpdata)?\
                                   (nDeslen-1):strlen(szTmpdata));
    szDesdata[nDeslen-1]=0;
    return 0;
}

IRESULT fprv_sql_UnloadToBuffer(char *sBuffer, int iLineLen, char *sSql,char cDiv,char cEscape,long *lResult)
{
    int k, iRet ;
    char sSqlstr[2048];
    int iSize=0;
    int iType=0;
    int iScale=0;
    int  iCnt=0;
    int  type=0,len=0;
    char sDesdata[1024];   /* 单个字节长度 */
    CURSOR cur;
    int numCols=0;
    int rc=0;
    char *sData=NULL;

    LOG(LM_STD,Fmtmsg("动态载出数据开始,根据查询[%s]->Buffer",sSql),"fprv_sql_UnloadToBuffer")

    if ( !sSql || !*sSql || !sBuffer || iLineLen < 1024 )
        LOGRET(MID_SYS_INVALID,LM_WARNING,MSG_SYS_INVALID,"fprv_sql_UnloadToBuffer")
    if ( cDiv == 0 )
        cDiv = '|';
    if ( cEscape == 0 )
        cEscape = '\\';
    *lResult = 0;

    cur=DCIDeclareCursor(sSql, 0);
    if ( cur == -1 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        return MID_SQL_DECLARE;
    }
    iRet = DCIExecute(cur);
    if ( iRet == -1 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        DCIFreeCursor(cur);
        return MID_SQL_EXECUTE;
    }
    numCols = DCINumCols(cur);            /* 取字段数 */
    if ( numCols == -1 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        DCIFreeCursor(cur);
        return MID_SQL_EXECUTE;
    }

    rc=DCIFetch(cur);
    if ( rc == -1 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        DCIFreeCursor(cur);
        return MID_SQL_CURFETCH;
    }
    else if ( rc==0 )
    {
        LOG(LM_STD,Fmtmsg("=========没有满足条件的记录========"),"fprv_sql_UnloadToBuffer")
        DCIFreeCursor(cur);
        return MID_SYS_SUCC;
    }

    while( rc > 0 )
    {
        (*lResult)++;
        iLineLen=0;
        for (iCnt=0;iCnt<numCols;iCnt++)
        {
            /*
            *从SELECT描述区中取第iCnt列字段的信息;
            */
            iType = DCIColType(cur, iCnt);   /* 取字段类型 */
            if ( iType == -1  )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
                DCIFreeCursor(cur);
                return MID_SQL_EXECUTE;
            }
        
            iSize = DCIColSize(cur, iCnt);   /* 取字段大小 */
            if ( iSize == -1 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
                DCIFreeCursor(cur);
                return MID_SQL_EXECUTE;
            }
        
            iScale = DCIColScale(cur, iCnt);  /* 取字段精度 */
            if ( iScale == -1  )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
                DCIFreeCursor(cur);
                return MID_SQL_EXECUTE;
            }
        
            /*
            *从描述区中取第nCnt列字段的信息;
            */
            sData = DCIFieldAsString(cur, iCnt);
            /*
            *根据属性调用域变量处理函数;
            */
            memset(sDesdata,0,sizeof(sDesdata));
            trim(sData);
            fprv_dyn_getdata_byattr(sDesdata,sizeof(sDesdata),iType,iSize,iScale,sData);
        
            trim(sDesdata);
            for ( k=0;k<strlen(sDesdata);k++ )
            {
                if( sDesdata[k]==cEscape || sDesdata[k]==cDiv || sDesdata[k]=='\n')
                /*转义字符'\'*/
                    sBuffer[iLineLen++]=cEscape;
                sBuffer[iLineLen++]=sDesdata[k];
            }
            sBuffer[iLineLen++]=cDiv;
        }
        sBuffer[iLineLen++]='\n';
        
        rc=DCIFetch(cur);
        if ( rc == -1  )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
            DCIFreeCursor(cur);
            return MID_SQL_CURFETCH;
        }
        else if ( rc==0 )
        {
            LOG(LM_STD,Fmtmsg("=========满足条件的记录已全部导出========"),"fprv_sql_UnloadToBuffer")
            break;
        }
    }

    DCIFreeCursor(cur);

    LOG(LM_STD,Fmtmsg("动态查询[%s]结果导出成功结束,[%ld][%s]",sSqlstr,*lResult,sBuffer),"fprv_sql_UnloadToBuffer")

    return MID_SYS_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_P2LJ_CONTROL
组件名称:SBATCH_P2LJ_CONTROL
组件功能: 批量任务批转联机分发处理
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
IRESULT SBATCH_P2LJ_CONTROL(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sMapID[40+1];
    char sYwbh[16+1];
    char sColID[32+1];
    char sFileID[32+1];
    char sSqlStr[4096];
    /* int iWjxh = 0;     文件序号 */
    int iZjszwz = 0;   /*主机上账位置 */
    char sPtPch[8+1],sGetFlag[1+1];
    char sBuf[1024];
    char sTableName[256];
    char sSubFlow[256];
    char sPkrq[8+1];
    char sQtWjdc[256];
    char sSql[1024];
    char sErrmsg[1024];
    int iCount=-1;
    int iProcs=-1;
    int lPgNum=0;
    int iRet =-1;
    int iFlag=-1;
    CURSOR cur;
    BATCH_P2LJ sdb_batch_p2lj;
    
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHKMIN(3)
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"业务表名")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBM_NULL,MSG_BATCH_YWBM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"主机并发记录数限制")
    if (sBuf[0] == '\0')
    {
        lPgNum=20;
    }else
        lPgNum = atol( sBuf );

    memset(sSubFlow,0,sizeof(sSubFlow));
    COMP_GETPARSEPARAS(3,sSubFlow,"并发子流程")

    /* 批扣日期 */
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sPkrq);
    if( 0 == sPkrq[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }

    /* 平台批次号 */
    memset(sPtPch, 0x00, sizeof(sPtPch));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf);
    pstrcopy(sPtPch,sBuf,sizeof(sPtPch));
    LOG(LM_STD,Fmtmsg("批转联机分发组件执行开始[%s%s],lPgNum[%ld],sSubFlow[%s]", 
        sPkrq, sPtPch, lPgNum, sSubFlow), fpub_GetCompname(lXmlhandle))

    /* 组装查询条件语句 */
    memset(sQtWjdc, 0x00, sizeof(sQtWjdc));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPCFG_RWQT_QTWJDC, sQtWjdc)
    
    memset(sSql, 0x00, sizeof(sSql));
    /* 暂定初始*/
    snprintf(sSql, sizeof(sSql), 
        "select lsxh,cgbz from %s where pkrq = '%s' and ptpch = '%s' and cgbz in ('9', '5') and %s order by lsxh",
        sTableName, sPkrq, sPtPch, StrReplace(sQtWjdc, "#", "'"));
    LOG(LM_STD,Fmtmsg("BATCH: 批转联机分发[%s]", sSql ),"DEBUG");
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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
    iProcs = DCINumRows(cur);
    if (iProcs < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    for (iCount=0; iCount < lPgNum ; iCount++ )
    {
        memset(&sdb_batch_p2lj,0,sizeof(sdb_batch_p2lj));
        iRet = DBFetch(cur, SD_BATCH_P2LJ, NUMELE(SD_BATCH_P2LJ), &sdb_batch_p2lj, sErrmsg );
        if ( iRet < 0 )
        {
            iFlag = iRet ;
            LOG(LM_STD,Fmtmsg("数据库操作游标失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            break;
        }
        if ( iRet == 0 )
        {
            iFlag = 0;
            LOG(LM_STD,Fmtmsg("数据已遍历完, 跳出循环！" ),"ERROR")
            break;
        }
        LOG(LM_STD,Fmtmsg("-[%d]--lsxh[%d],cfbz[%s]", iCount, sdb_batch_p2lj.lsxh, sdb_batch_p2lj.cgbz  ),"INFO")
        COMP_SOFTSETXML("/batch/sjtj/lsxh", itoa(sdb_batch_p2lj.lsxh))
        COMP_SOFTSETXML("/batch/sjtj/cgbz", sdb_batch_p2lj.cgbz)
        if (sdb_batch_p2lj.cgbz[0] == '9')
        {/*9-未处理,需核心记账*/
            COMP_SOFTSETXML("/batch/sjtj/instr", "hxjz")
        }else if (sdb_batch_p2lj.cgbz[0] == '5')
        {/*5-超时,需超时查证*/
            COMP_SOFTSETXML("/batch/sjtj/instr", "cscz")
        }else
        {
            continue;
        }
	    if( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
	    {
	    	LOG(LM_STD, Fmtmsg("[%d]调用分发子流程失败", iCount+1), fpub_GetCompname(lXmlhandle));
	    	continue;
	    }

    }
    DCIFreeCursor(cur);
    if ( iFlag < 0 )
    {
        LOG(LM_STD,Fmtmsg("分发有误[%d]",iFlag ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    LOG(LM_STD,Fmtmsg("批转联机分发结束,共分发[%d]笔", iCount), fpub_GetCompname(lXmlhandle))
    if ( iProcs == 0 )
    {/*本批次已没有需处理明细,则指向下一步点*/
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    }else if ( iProcs > 0 )
    {/*否则,说明还有未处理明细,步点各状态不变*/
        fpub_SetCompStatus(lXmlhandle, 1);
    }else
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    }

    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_P2LJ_PREPROC
组件名称:SBATCH_P2LJ_PREPROC
组件功能: 批量转联机前处理
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
IRESULT SBATCH_P2LJ_PREPROC(HXMLTREE lXmlhandle)
{
    char sMapID[40+1];
    char sYwbh[16+1];
    char sColID[32+1];
    char sFileID[32+1];
    char sSqlStr[4096];
    /* int iWjxh = 0;     文件序号 */
    int iZjszwz = 0;   /*主机上账位置 */

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
    char sPkrq[8+1], sLsxh[8+1],sCgbz[1+1];
    char sPtpch[8+1],sGetFlag[1+1];
    char sLine[1024],sColName[256],sColValue[512],sSjtjNodePath[512];
    int  iTSortCount=0;
    int  i,iAbort=0,length=0;
    long lRCount=0;
    FILE *hostfp;
    FILE *srcfp;
    FILE *tmpfp;
    char sCondStr[1024];
    char sQtWjdc[256];
    char sColStr[2048];  /* 提交后台映射字段 */
    int  lPgNum = 0;    /* 每主机文件最大记录数 */
    int  iCols=0;
    /*long lLsxh = 0;      流水序号 */
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
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* 平台批次号 */
    memset(sPtpch, 0x00, sizeof(sPtpch));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    /* 流水序号 */
    memset(sLsxh, 0x00, sizeof(sLsxh));
    COMP_SOFTGETXML("/batch/sjtj/lsxh",sLsxh);

    /* 成功标志 */
    memset(sCgbz, 0x00, sizeof(sCgbz));
    COMP_SOFTGETXML("/batch/sjtj/cgbz",sCgbz);
    
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

    LOG(LM_DEBUG,Fmtmsg("BATCH: 文件类型[%s]，主机文件记录数限制[%d]", sFileType, lPgNum ),"DEBUG");

    memset( sSqlStr,0x00, sizeof( sSqlStr ) );
    snprintf( sSqlStr, sizeof( sSqlStr ), "SELECT * FROM  batch_filemap\
        WHERE mapid='%s' AND zjszwz > 0 ORDER BY zjszwz",sMapID );
    LOG(LM_DEBUG,Fmtmsg("sqlStr:[%s]", sSqlStr ),"DEBUG");
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
        strcpy( sColID, sdb_batch_filemap.columnid );
        trim( sColID );
        strcat( sColStr, sColID );
        strcat( sColStr, "," );
        iCols++;
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
    COMP_SOFTGETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );
    LOG(LM_DEBUG,Fmtmsg("BATCH: 提交标志[%s]", sGetFlag ),"DEBUG");

    /*  clzt:9 未处理,cgbz:0 成功,1部分成功,2失败,5处理超时,8处理中 */
    snprintf(sCondStr, sizeof( sCondStr ),"pkrq='%s' AND ptpch='%s' AND lsxh='%s' ", sPkrq, sPtpch, sLsxh );
    
    /* 抢占更新本条明细记录 */
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "UPDATE %s SET cgbz='8' WHERE %s AND cgbz='%s'", 
        sTableName, sCondStr, sCgbz );
    LOG(LM_STD,Fmtmsg("BATCH: 批转联抢占sql[%s]", sSqlStr ),fpub_GetCompname(lXmlhandle));
    DCIBegin();
    iRet = DCIExecuteDirect( sSqlStr );
    if ( iRet < 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("更新批量明细表失败,sqlerr[%d][%s]",DCILastError() ),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCICommit();
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("未能成功抢占批转联明细记录[%s%s,%s,%s]或已处理!", sPkrq, sPtpch, sLsxh, sCgbz),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        COMP_SOFTSETXML(XMLNM_RESPCODE, BATCH_REPSCODE_SUCC)
        COMP_SOFTSETXML(XMLNM_RESPMSG, "BATCH:记录数为零,未能成功抢占批转联明细记录")
        return COMPRET_SUCC;
    }
    /*读取该明细记录*/
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT %s FROM %s WHERE %s ", sColStr, sTableName, sCondStr );
    LOG(LM_STD,Fmtmsg("BATCH: 批转联导出Sql [%s]", sSqlStr ),"STD");
    memset(sLine, 0x00, sizeof(sLine));
    iRet = fprv_sql_UnloadToBuffer(sLine, sizeof(sLine), sSqlStr,'|','\\',&lRCount );
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("批转联明细记录到Buffer失败[%d]", iRet),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "批转联明细记录到Buffer失败");
        return COMPRET_FAIL;
    }
    if( lRCount == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:记录数为零，无需提交内部任务嵌套处理"),"WARNING");
        /*fpub_SetMsg(lXmlhandle,BATCH_REPSCODE_SUCC,"BATCH:记录数为零，无需提交内部任务嵌套处理");*/
        COMP_SOFTSETXML(XMLNM_RESPCODE, BATCH_REPSCODE_SUCC)
        COMP_SOFTSETXML(XMLNM_RESPMSG, "BATCH:记录数为零，无需提交内部任务嵌套处理")
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
    for(i=1; i <= iCols; i++)
    {
        memset(sColName, 0x00, sizeof(sColName));
        memset(sColValue, 0x00, sizeof(sColValue));
        memset(sSjtjNodePath, 0x00, sizeof(sSjtjNodePath));
        GetListbyDiv(sColStr,i,sColName,',','\\');
        GetListbyDiv(sLine,i,sColValue,'|','\\');
        snprintf(sSjtjNodePath, sizeof(sSjtjNodePath), "/batch/sjtj/%s", sColName);
        COMP_SOFTSETXML(sSjtjNodePath, sColValue)
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPCFG_RWQT_BQTPCYT, sBuf);
    LOG(LM_STD,Fmtmsg("%s=[%s]",XMLNM_BATCH_STEPCFG_RWQT_BQTPCYT, sBuf),"DEBUG")
    if (sBuf[0] == '1')
    {
        COMP_HARDCOPYXML(XMLNM_BATCH_RUNCTRL_CPDM,XMLNM_BATCH_SJTJ_CPDM);
        COMP_HARDCOPYXML(XMLNM_BATCH_REQ_YWBH,XMLNM_BATCH_SJTJ_YWBH);
    }else
    {
        COMP_HARDCOPYXML(XMLNM_BATCH_STEPCFG_RWQT_BQTCPDM,XMLNM_BATCH_SJTJ_CPDM);
        COMP_HARDCOPYXML(XMLNM_BATCH_STEPCFG_RWQT_BQTYWBH,XMLNM_BATCH_SJTJ_YWBH);
    }

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_P2LJ_LASTPROC
组件名称:SBATCH_P2LJ_LASTPROC
组件功能: 批量转联机后处理
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
IRESULT SBATCH_P2LJ_LASTPROC(HXMLTREE lXmlhandle)
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
    char sPtpch[8+1],sLsxh[8+1];
    char sPkrq[8+1];
    char sNode[32+1];
    char sLine[1024],sColName[256],sColValue[512],sSjthNodePath[512];
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

    /* 流水序号 */
    memset(sLsxh,0,sizeof(sLsxh));
    COMP_SOFTGETXML("/batch/sjtj/lsxh",sLsxh);
    trim(sLsxh);

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
                    sprintf( sBuf, " WHERE pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch );
                    iUniqueKey=1;
                }else
                {
                    sprintf( sBuf, " WHERE 1=1  " );
                    iUniqueKey=0;
                }
                
                strcat( sSqlUpd, sBuf );
            }
            updFlag ++;
            if ( strcmp(sdb_batch_filemap.columnid, "lsxh") == 0)
            {
                sprintf( sBuf, " AND lsxh =%s" , sLsxh );
            }else
            {
                sprintf( sBuf, " AND trim(%s) =:v%d" , sdb_batch_filemap.columnid, iCount );
            }
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
            strcat( sSqlStr,  sdb_batch_filemap.columnid );
        }
        strcat( sSqlUpd, sBuf );
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

    /* 获取更新语句所需字段信息 */
    cur = DCIDeclareCursor(sSqlStr, 0);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    DCIExecute(cur);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    iAllcount = DCINumCols(cur);                        /* 取字段数 */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
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
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if ((cur = DCIDeclareCursor(sSqlUpd, DCI_STMT_LOCATOR)) == -1)
    {
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
            DCIFreeCursor(cur);
            prv_free_data( sdata, iAllcount );
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
       }
    }

    /* 开始处理明细 */
    iDetailCount = 0;
    /* for cal time cast */
    ftime(&starttime);
    /*while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )*/
    for (i=1; i < iAllcount; i++)
    {
        index ++;
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
                /* 处理明细：获取更新字段值，更新条件 
                memset(sBuf, 0x00, sizeof(sBuf));
                iResult = prv_rwqt_detailProc(lXmlhandle,linebuf,pos[iFileValPos], sBuf,&thisSort,&dDetailAmt,t_fileColumnList);
                if( iResult < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 提回文件明细信息处理失败,pos[%d]=[%d],[%d],[%s]: [%d],[%s]",\
                        iFileValPos,pos[iFileValPos],index,linebuf,thisSort.fileclasssn,thisSort.classname),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
                    iAbort = -3;
                    break;
                }*/
                memset(sColName, 0x00, sizeof(sColName));
                memset(sSjthNodePath, 0x00, sizeof(sSjthNodePath));
                memset(sBuf, 0x00, sizeof(sBuf));
                GetListbyDiv(sSqlStr,i,sColName,',','\\');
                snprintf(sSjthNodePath, sizeof(sSjthNodePath), "/batch/sjsj/resp/%s", sColName);
                COMP_SOFTGETXML(sSjthNodePath, sBuf)
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
                LOG(LM_STD,Fmtmsg("BATCH: 提回被嵌套文件明细信息处理ret[%d] sqlerr[%s] 明细行数[%d]",\
                    iRet, DCILastError(), iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            }else if ( iRet == 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 提回被嵌套文件明细信息处理ret[%d] 更新记录数为零条 明细行数[%d]",\
                    iRet, iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_UPDZERO,MSG_BATCH_SJTH_UPDZERO);
            }else if ( iRet > 1 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: 提回被嵌套文件明细信息处理ret[%d] 更新记录数大于壹条 明细行数[%d]",\
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
            DCICommit();
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

    /* 处理异常 */
    if ( iAbort != 0  )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 提回文件更新处理错误: [%d]",iAbort),"ERROR");
        /* 响应信息 */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPSTATUS_FAIL ;
    }

    /* 增加响应码转换范围 1：只转换审核失败信息 */
    COMP_SOFTSETXML( XMLNM_BATCH_SJHP_CVTRESP, "1" );

    /* 如果核心不返回实际校验金额，则将实际金额置为0.00 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_HOST_AMT_FLAG,sBuf);
    if( sBuf[0] == '1' )  /* 1-不返回 0-返回（默认） ( 不设置本参数则不处理 ) */
    {
        memset( sSqlUpd, 0x00, sizeof( sSqlUpd ) );
        memset( sBuf, 0x00, sizeof( sBuf ) );
        COMP_SOFTGETXML( XMLNM_BATCH_SJTH_ZJXH,sBuf);
        /* 将成功明细的实际金额置为交易金额 */
        sprintf( sSqlUpd, "UPDATE %s SET sjje=jyje WHERE pkrq='%s' AND ptpch='%s' AND lsxh=%s  ", \
            sTableName, sPkrq, sPtpch,  sLsxh );

        DCIBegin();
        iRet = DCIExecuteDirect( sSqlUpd );
        if( iRet < 0  )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_PLRW,MSG_BATCH_UPD_PLRW );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
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
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}
