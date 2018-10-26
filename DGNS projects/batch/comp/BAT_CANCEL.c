/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.1)
��    ��:V2.1.0.1
����ϵͳ:AIX5.3+ORACLE+HSXP
�ļ�����:BAT_CANCEL.ec
�ļ�����:���������ύ���Ĵ���
�� �� Ա:YangDong
��������:20140715
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
        <sonote>BATCH���ݳ��������������</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2014-7-15 15:08\" programer=\"YangDong\" filesize=\"1238198\">HS-AgentV2.1����</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2014-11-13 13:08\" programer=\"Chenxm\" filesize=\"1238198\">DCI����</rec>\
        </version>\
        </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" -->ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" -->��鿴��ϸ��Ϣ...\n");
    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_PLCZ_SJTJ
�������:BATCH_PLCZ_SJTJ
�������: ����ҵ�����������ύ�ļ�
�������:
 ��� ��������  ��������      ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����    �����ļ���    416XML�����ַ���  *      N      
  2   1-����    �ļ���ʶ      416XML�����ַ���  *      N    
  3   1-����    ӳ���ʶ      416XML�����ַ���  *      N    
  4   1-����    ҵ�����      416XML�����ַ���  *      N    
  5   1-����    �ļ����      416XML�����ַ���  *      N    
ʹ������:����ϸ�ļ���ʽ
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_PLCZ_SJTJ(HXMLTREE lXmlhandle)
{
    /*EXEC SQL BEGIN DECLARE SECTION; */
        char sMapID[40+1];
        char sYwbh[16+1];
        char sColID[32+1];
        char sFileID[32+1];
        char sSqlStr[1024];
        int iWjxh = 0;     /* �ļ���� */
        /*int iZjszwz = 0;    ��������λ�� */
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
    char sColStr[256];  /* �ύ��̨ӳ���ֶ� */
    /*long lLsxh = 0;      ��ˮ��� */
    /*int  iFileCount = 1;     �ļ��� */
    int  iFileNum = 0;      /* �ļ��ڼ�¼�� */
    int  iTotalNum= 0;      /* �����μ�¼�� */
    double dFileAmt= 0;     /* �ļ����ܽ�� */
    double dTotalAmt = 0;   /* �������ܽ�� */

    int  iLsxh = 0;
    int  iPos = 0;
    int iRet = -1;

    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    BATCH_FILEMAP batch_filemap;
    CURSOR cur;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(7)

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�����ļ���")
    pstrcopy(sFileBasicName,sBuf,sizeof(sFileBasicName)); 
    memset(sBuf,0,sizeof(sBuf));

    COMP_GETPARSEPARAS(2,sBuf,"�ļ���ʶ")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJBS_NULL,MSG_BATCH_WJBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileID,sBuf,sizeof(sFileID));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"ӳ���ʶ")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YSBS_NULL,MSG_BATCH_YSBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sMapID,sBuf,sizeof(sMapID));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"ҵ�����")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBM_NULL,MSG_BATCH_YWBM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    /* �������� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(5,sBuf,"ԭ��������")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* ƽ̨���κ� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(6,sBuf,"ԭƽ̨���κ�")
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    /* �ļ���� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(7,sBuf,"�ļ����")
    iWjxh = atoi( sBuf );
    if( iWjxh == 0 )  /* �ļ����Ĭ��1 */
    {
        iWjxh = 1;
    }
    COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_SUBMIITED_WJXH, itoa( iWjxh ) );
    
    /* ҵ���� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sYwbh,sBuf,sizeof(sYwbh));

    /* �ļ����� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILEFMT,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJLX_NULL,MSG_BATCH_WJLX_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sFileType,sBuf,sizeof(sFileType));

    /* �ļ������� */
    /* �����ļ�����λ�� */
    snprintf( sFilePath, sizeof( sFilePath ),\
        "%s/batch/zjwj", getenv("GAPSFILEDIR") );

    snprintf( sFileParsedName,sizeof( sFileParsedName ),\
        "%s_%s_%s_%d.req", sYwbh, sPkrq, sPtpch, iWjxh );

    /* �������������ļ���( ������Ϣ���Դ�xml�ڵ��� ) */
    if( strlen( sFileBasicName ) > 2 )
    {
        /* �����ļ������� */
        pstrcopy( sFileBakName, sFileBasicName, sizeof(sFileBasicName)); 
        LOG(LM_DEBUG,Fmtmsg("BATCH: �����ļ����ƽ���,[%s]=>",sFileBasicName),"DEBUG")
        /* �Ƚ���XML���� */
        if(xml_ParseXMLString(lXmlhandle,sFileBasicName,sizeof(sFileBasicName))==FAIL)
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,\
                Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* �������ļ��� */
        strcpy( sFileParsedName, sFileBasicName );
        /* �ָ��ļ������� */
        pstrcopy( sFileBasicName, sFileBakName, sizeof(sFileBasicName)); 
    }
    /* �ļ�ȫ�� */
    snprintf( sFileFullName, sizeof( sFileFullName ),\
                     "%s/%s",sFilePath, sFileParsedName );

    /*add by chenxm 20141113DCI���칤��*/
    memset(sSql, 0x00, sizeof(sSql));
    sprintf(sSql, "SELECT batch_filemap.columnid, batch_filemap.zjszwz FROM  batch_filemap "
        "WHERE mapid = '%s' AND zjszwz > 0 ORDER BY zjszwz", sMapID);
    if ((cur = DCIDeclareCursor( sSql, DCI_STMT_LOCATOR)) == -1)	
    {
        LOG(LM_STD,Fmtmsg("���ݿ���α����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("ִ���α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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

    /* �ļ���������λ�� */
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
                LOG(LM_STD,Fmtmsg("��ѯ���ݿ�ʧ��[%d][%s]",iRet,sSql),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPSTATUS_FAIL;
            }
    }
    /*EXEC SQL CLOSE cur_col_str; */
    DCIFreeCursor(cur);
    /* ȥ���һ�� , */
    sColStr[strlen( sColStr ) - 1 ] = '\0';
    
    /* ��ϸ�ύ��־ */
    memset( sGetFlag, 0x00, sizeof( sGetFlag ) );
    COMP_SOFTGETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );

    /* ��װ��ѯ������� */
    /*  cgbz:0 �ɹ���1 ���ֳɹ� */
    snprintf(sCondStr, sizeof( sCondStr ),"pkrq='%s' AND ptpch='%s' AND wjxh='%d' AND cgbz='0' OR cgbz='1' ", sPkrq, sPtpch, iWjxh ); 

    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT trim(lsxh) as pnxh,%s FROM %s WHERE %s ORDER BY lsxh"\
        ,sColStr, sTableName, sCondStr );

    /* ��������ʱ�ļ� */
    memset(sTmpFileName,0,sizeof(sTmpFileName));
    snprintf(sTmpFileName, sizeof( sTmpFileName), \
        "%s/tmp/batch_sjtj_tmp%s.%s", getenv("HOME"), sPkrq, sPtpch );
    if( sql_UnloadToFile(sTmpFileName,sSqlStr,'^','\\',&lRCount)!= MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�����ļ�����ʧ��,[%s]",sSqlStr),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_GENFILE,MSG_BATCH_SJTJ_GENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if( lRCount == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�����[%d]����Ҫ�ύ���Ĵ�����ϸ",iWjxh),"INFO");
        /* �ļ��ڱ��� */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iWjxh );
        COMP_SOFTSETXML(  sNode , "0" );
        /* �ļ��ڽ��׽�� */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iWjxh );
        COMP_SOFTSETXML(  sNode , "0.00");
        
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")
        
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }

    /* �򿪵����ļ����� */
    if((srcfp = fopen(sTmpFileName, "r")) == NULL)
    {
        LOG(LM_STD,Fmtmsg("BATCH: ���ļ�����ʧ��,[%s]",sTmpFileName),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* �����ļ�����ʼ */
    if((hostfp = fopen(sFileFullName, "w")) == NULL)
    {
        fclose( srcfp );
        LOG(LM_STD,Fmtmsg("BATCH: ���ļ�����ʧ��,[%s]",sFileFullName),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* �ļ�����Ϣ�����ʼ�� */
    iResult =fprv_initFileColumn(sFileID,&t_fileColumnList );
    if( iResult <= 0 )
    {
        fclose( srcfp );
        fclose( hostfp );
        LOG(LM_STD,Fmtmsg("BATCH: �ļ�����Ϣ�����ʼ��ʧ��,[%s]",sFileID),"ERROR");
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
            Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ��ϸ������Ϣ�����ʼ�� */
    iResult =fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_DETAIL,&t_fileDetailSortList);
    if( iResult != 1 )  /* ֻ֧�ֵ�����ϸ���� */
    {
        LOG(LM_STD,Fmtmsg("BATCH: �ļ���ϸ����[%s]ӳ�������ʼ��ʧ��,������[%d]",\
            sFileID, iResult ),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        fclose( srcfp );
        fclose( hostfp );
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ȡ��ϸ������Ϣ */
    memset(&thisSort, 0, sizeof(BATCH_FILESORT));
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* ����ϸ����Ҫ�ļ����ܷ���ӳ�������ʼ�� */
    if( strcmp( sFileType,"01" ) != 0 )
    {
        iTSortCount=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_TOTAL,&t_fileTotalSortList);
        if( iTSortCount <= 0  )
        {
            fclose( srcfp );
            fclose( hostfp );
            batch_totalsortlistFree();
            batch_detailsortlistFree();
            LOG(LM_STD,Fmtmsg("BATCH: �ļ����ܷ���ӳ�������ʼ��,[%s]",sFileID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    if( strcmp( sFileType,"02" ) == 0 ||   /* �����ܵ���ϸ */
        strcmp( sFileType,"04" ) == 0 )    /* �����ܵ���ϸ�ӻ��� */
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
        /* �������ܷ��࣬һ�����ܷ��ദ��һ�м�¼,��Ҫ���ñ�֤���ܷ����˳��ƥ���ļ� */
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

    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ϸ����ʼ"),"DEBUG");
    /* ������ϸ��Ϣ */
    dFileAmt = 0.00;
    iFileNum = 0;
    iTotalNum = 0;
    dTotalAmt = 0.00;
    memset(lineBuf, 0, sizeof(lineBuf));
    iAbort = 0;
    while( fgets( lineBuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        /* ���˿���  */
        if( 0 == lineBuf[0] || 13 == lineBuf[0] )
        {
            continue;
        }
                
        /* �ļ��ڼ�¼�� */
        iFileNum++;

        /* �������ã�������ϸ��Ϣ */
        memset(outbuf, 0, sizeof(outbuf));
        iResult = detailProc_write(lXmlhandle,&iLsxh, lineBuf,&dFileAmt,outbuf,&thisSort,t_fileColumnList);
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��ϸ��Ϣ����ʧ��,[%s]", lineBuf),"ERROR");
            iAbort=4;
            break;
        }

        /* ��ϸ�����¼���� */
        iTotalNum ++;
        /* ��ϸ�����ܽ�� */
        dTotalAmt += dFileAmt;

        /* ���һ������ */
        length = strlen( outbuf );
        outbuf[ length ] = '\n';
        /* д���ύ�����ļ� */
        iResult = fwrite( outbuf, length + 1, 1, hostfp);
        if( iResult < 0)
        {
            LOG(LM_STD,Fmtmsg("BATCH: �ļ�д��ʧ��,[%d],[%d],[%s]",\
                       iResult,errno,strerror(errno)),"ERROR");
            iAbort=7;
            break;
        }
    }

    fclose( srcfp );
    
    /* �ļ��� */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjmc", iWjxh );
    COMP_SOFTSETXML(  sNode, sFileParsedName );
    /* �ļ�ȫ�� */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", iWjxh );
    COMP_SOFTSETXML(  sNode, sFileFullName );
    /* �ļ��ڱ��� */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iWjxh );
    COMP_SOFTSETXML(  sNode , itoa( iFileNum) );
    /* �ļ��ڽ��׽�� */
    memset( sNode, 0x00, sizeof( sNode ) );
    sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iWjxh );
    sprintf( sBuf, "%.2f", dFileAmt );
    COMP_SOFTSETXML(  sNode , sBuf );

    /* linux���ظ�fclose��coredump */
#ifdef _OS_LINUX__
    if( hostfp->_fileno >= 0 )
#endif
    fclose( hostfp );

    unlink(sTmpFileName);

    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_totalsortlistFree();

    /* �����쳣 */
    if( iAbort )
    {
        LOG(LM_STD,Fmtmsg("BATCH: �����ύ�ļ��������: [%d]",iAbort),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_GENFILE,MSG_BATCH_SJTJ_GENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_PLCZ_SJTH
�������:BATCH_PLCZ_SJTH
�������: ����ҵ��������ش���
�������:
 ��� ��������  ��������      ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����    �����ļ���    416XML�����ַ���  *      N      
  2   1-����    �ļ���ʶ      416XML�����ַ���  *      N    
  3   1-����    ӳ���ʶ      416XML�����ַ���  *      N    
  4   1-����    ҵ�����      416XML�����ַ���  *      N    
  5   1-����    �ļ����      416XML�����ַ���  *      N    
ʹ������:����ϸ�ļ���ʽ
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_PLCZ_SJTH(HXMLTREE lXmlhandle)
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
        char sXym[10+1];
        char sSplit[10+1];
        char sSql[1024];
        /*int iWjxh = 0;      �ļ���� */
        /*int iZjszwz = 0;    ��������λ�� */
    /*EXEC SQL END   DECLARE SECTION; */
    int  iParas,iResult;
    char sBuf[256];
    char lineBuf[BATCH_MAX_FILELINE_BYTE];
    char sTableName[40+1];
    char sFileName[128];
    char sPkrq[8+1];
    char sPtpch[8+1];
    FILE *hostfp;
    long lLsxh = 0;     /* ��ˮ��� */
    int iRet = -1;

    /*int  iLsxh = 0;*/
    /*int  iPos = 0;*/

    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(4)

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�����ļ���")
    pstrcopy(sFileName,sBuf,sizeof(sFileName)); 

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ҵ�����")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBM_NULL,MSG_BATCH_YWBM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"��������")
    /* �������� */
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* ƽ̨���κ� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"ƽ̨���κ�")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    if(( hostfp = fopen(sFileName, "r+")) == NULL)
    {
        LOG(LM_STD,Fmtmsg("BATCH: �����������ļ�[%s]ʧ��",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*add by chenxm 20141113 DCI���칤��*/
    iRet = DCIBegin();
    if(iRet != 0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }/* add end */

    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ϸ����ʼ"),"DEBUG");
    /* ������ϸ��Ϣ */
    memset(lineBuf, 0, sizeof(lineBuf));
    memset( sSplit, 0x00, sizeof( sSplit ) );
    strcpy( sSplit, "124" );
    while( fgets( lineBuf, BATCH_MAX_FILELINE_BYTE, hostfp ) != NULL )
    {
        /* ���˿���  */
        if( 0 == lineBuf[0] || 13 == lineBuf[0] )
        {
            continue;
        }
                
        /* �ļ��ڼ�¼�� */

        /* ���|������|Ӣ����|���׽��|�Ա�|֤������|֤������|����|ƾ֤����|��ַ|��ϵ�绰|��Ʒ����|����|��ƾ֤��|�������|����|������|��������|������ */
        memset( sBuf , 0x00, sizeof( sBuf ) );
        /* ��� */
        fprv_getSubStr(lineBuf, 1, sSplit, sBuf);
        lLsxh = atol( sBuf );

        /* ������ */
        memset( sBuf , 0x00, sizeof( sBuf ) );
        fprv_getSubStr(lineBuf, 17, sSplit, sBuf);
        pstrcopy(sXym,sBuf,sizeof(sXym)); 
        trim( sXym );

        /* �ж��Ƿ�ɹ� */
        if( strcmp( sXym,"00000" ) == 0 )
        {
            /* �����ɹ�����ԭ���ζ�Ӧ��ϸ��Ϣ��Ϊ�ѳ��� */
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf( sSql,"UPDATE %s SET cgbz='7' WHERE pkrq='%s' and ptpch='%s' and lsxh=%ld ", sTableName, sPkrq, sPtpch, lLsxh );
            iRet = DCIExecuteDirect(sSql);
            /*if ( sql_DynExec(sSql,&iResult)!=0 || iResult <=0 )*/
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("BATCH: ����ļ���ϸ��Ϣ����ʧ��,[%d],[%s]: [%d][%s]",\
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��!,sqlcode[%d]",sqlca.sqlcode),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_FAIL,Fmtmsg(MSG_SQL_FAIL,sqlca.sqlcode));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }*/

    fclose( hostfp );

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
