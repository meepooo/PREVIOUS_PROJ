/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT4.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_RWQT.ec
�ļ�����:Ƕ���ڲ�����ҵ�����������BAT_SJTJ.c��BAT_SJTH.c����
�� �� Ա:������
��������:20150520

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
        <soname>BAT_RWQT.so</soname>\
        <sosrcname>BAT_RWQT.c</sosrcname>\
        <sonote>BATCH����Ƕ���������</sonote>\
        <version>\
        <rec ver=\"4.1.0.1\" modify=\"2015-05-20 09:00\" programer=\"TUQL\" filesize=\"1238198\">����</rec>\
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
�����������:SBATCH_RWQT_ACCEPT
�������:SBATCH_RWQT_ACCEPT
�������: ��������Ƕ������ǰ����
�������:
 ��� ��������  ��������      ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����    �����ļ���    416XML�����ַ���  *      N      
  2   1-����    �ļ���ʶ      416XML�����ַ���  *      N    
  3   1-����    ӳ���ʶ      416XML�����ַ���  *      N    
  4   1-����    ҵ�����      416XML�����ַ���  *      N    
ʹ������:����ϸ�ļ���ʽ
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_RWQT_ACCEPT(HXMLTREE lXmlhandle)
{
    char sMapID[40+1];
    char sYwbh[16+1];
    char sColID[32+1];
    char sFileID[32+1];
    char sSqlStr[4096];
    /* int iWjxh = 0;     �ļ���� */
    int iZjszwz = 0;   /*��������λ�� */

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
    char sQtWjdc[256];
    char sColStr[2048];  /* �ύ��̨ӳ���ֶ� */
    int  lPgNum = 0;    /* ÿ�����ļ�����¼�� */
    /*long lLsxh = 0;      ��ˮ��� */
    int  iFileCount = 1;    /* �ļ��� */
    int  iFileNum = 0;      /* �ļ��ڼ�¼�� */
    int  iTotalNum= 0;      /* �����μ�¼�� */
    double dFileAmt= 0;     /* �ļ����ܽ�� */
    double dTotalAmt = 0;   /* �������ܽ�� */

    CURSOR cur;
    char sErrmsg[512];
    int iRet = -1;

    int  iLsxh = 0;
    int  iPos = 0;

    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    BATCH_FILEMAP  sdb_batch_filemap;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(5)

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

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(5,sBuf,"�����ļ���¼������")
    lPgNum = atol( sBuf );

    /* �������� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* ƽ̨���κ� */
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
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

    LOG(LM_DEBUG,Fmtmsg("BATCH: �ļ�����[%s]�������ļ���¼������[%d]", sFileType, lPgNum ),"DEBUG");

    /* �����ļ����ʱ����Ҫ�����ظ��ύ��� */
    /* ������ظ��ύ,��ֻ�ύ���ͺ���ʧ�ܵ��ļ� */
    /* �ļ��Ѿ�����,����д�ļ�,Ϊ�ļ��������ļ���ʼ��Ÿ�ֵ */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_SJTJ_SUBMIITED_WJXH, sBuf );
    if( atoi( sBuf ) >= 1 )
    {
        /* �ļ��Ѿ��ύ��,�������ύ,���ύʧ�ܵ��ļ���ſ�ʼ�ύ */
        LOG(LM_STD,Fmtmsg("�����ύ����,���ļ����[%s]�Ժ�ʼ", sBuf ),"INFO")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        /* �������ļ���ֱ�ӵ����������۽��� */
        return 0;
    }
    else
    {
        COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_SUBMIITED_WJXH, "0"  );
    }

    /* �ļ������� */
    /* �����ļ�����λ�� 
    snprintf( sFilePath, sizeof( sFilePath ),\
        "%s/batch/zjwj", getenv("GAPSFILEDIR") );
    */
    memset(sFilePath, 0x00, sizeof(sFilePath));
    iRet = fprv_getBatchFilePath(lXmlhandle,sFilePath, sizeof(sFilePath));
    iRet = xml_DelElement( lXmlhandle, "/batch/sjtj/wjxx" );
    /* �ļ���ţ���1��ʼ */
    COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_WJXH , itoa( iFileCount ) );
    LOG(LM_DEBUG,Fmtmsg("iFileCount:[%d]", iFileCount ),"DEBUG");
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_BATCH_STEPINFO_DQBD, sBuf);
    
    if( strlen( sFileBasicName ) < 1 ) 
    {
        if( lPgNum > 0 )  /* �ļ���Ҫ��� */
            snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                        "rwqt_%s_%s_%s_%d_%s.req", sYwbh, sPkrq, sPtpch, iFileCount, sBuf );
        else /* �ļ�����Ҫ��� */
            snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                "rwqt_%s_%s_%s_%s.req", sYwbh, sPkrq, sPtpch, sBuf );
    }
    LOG(LM_DEBUG,Fmtmsg("sFileParsedName:[%s]", sFileParsedName ),"DEBUG");
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
    
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_WJLJ, sFilePath);
    
    memset( sSqlStr,0x00, sizeof( sSqlStr ) );
    snprintf( sSqlStr, sizeof( sSqlStr ), "SELECT * FROM  batch_filemap\
        WHERE mapid='%s' AND zjszwz > 0 ORDER BY zjszwz",sMapID );
    LOG(LM_DEBUG,Fmtmsg("sqlStr:[%s]", sSqlStr ),"DEBUG");
    if ((cur = DCIDeclareCursor(sSqlStr, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* �ļ���������λ�� */
    memset(sColStr,0,sizeof(sColStr));
    memset( &sdb_batch_filemap, 0x00, sizeof( BATCH_FILEMAP ) );
    iPos = 0;
    while( ( iRet = DBFetch(cur, SD_BATCH_FILEMAP, NUMELE(SD_BATCH_FILEMAP), &sdb_batch_filemap, sErrmsg ) ) > 0 )
    {
        iPos ++;
        memset( sColID, 0x00, sizeof( sColID ) );
        /*iZjszwz = sdb_batch_filemap.zjszwz;*/
        strcpy( sColID, sdb_batch_filemap.columnid );
        /* ��select�ֶ�����ӿ�ֵ����֤�����ļ��ֶ������ļ�����ƥ�� */
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* ȥ���һ�� , */
    sColStr[strlen( sColStr ) - 1 ] = '\0';
    
    /* ��ϸ�ύ��־ */
    memset( sGetFlag, 0x00, sizeof( sGetFlag ) );
    /* mod by yangdong 20130305 bug
    COMP_SOFTSETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );
    */
    COMP_SOFTGETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );

    LOG(LM_DEBUG,Fmtmsg("BATCH: �ύ��־[%s]", sGetFlag ),"DEBUG");

    /* ��װ��ѯ������� */
    memset(sQtWjdc, 0x00, sizeof(sQtWjdc));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPCFG_RWQT_QTWJDC, sQtWjdc)
    LOG(LM_DEBUG,Fmtmsg("BATCH: Ƕ���ļ�����Where [%s]", sQtWjdc ),"DEBUG");
    /*  clzt:9 δ���� cgbz:0 �ɹ���1 ���ֳɹ�  ���״̬ 1 ���ʧ��  */
    if(0 == memcmp(sGetFlag, BATCH_MXTJBZ_NONPROC_FAIL ,1 ))  /* �ύδ�������ʧ����ϸ */
    {
        snprintf(sCondStr, sizeof( sCondStr ), "ywbh='%s' \
            AND (clzt='9' OR ( cgbz<>'0' AND cgbz <> '1' ) ) AND %s ", sYwbh, StrReplace(sQtWjdc, "#", "'"));
    }
    else /* �ύ������δ������ϸ */
    {
        snprintf(sCondStr, sizeof( sCondStr ),"pkrq='%s' AND ptpch='%s' \
            and %s ", sPkrq, sPtpch, StrReplace(sQtWjdc, "#", "'") ); 
    }

    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );

    /* modified by yangdong 20130201 ��gaps4.1�У����ܻ�����oracle��-600��
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT lsxh as pnxh,%s FROM %s WHERE %s ORDER BY lsxh"\
                      ,sColStr, sTableName, sCondStr );
    */
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT trim(lsxh) as pnxh,%s FROM %s WHERE %s ORDER BY lsxh", \
        sColStr, sTableName, sCondStr );
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_BATCH_STEPINFO_DQBD, sBuf);
    /* ��������ʱ�ļ� */
    memset(sTmpFileName,0,sizeof(sTmpFileName));
    snprintf(sTmpFileName, sizeof( sTmpFileName), \
        "%s/tmp/batch_rwqt_tmp%s.%s.%s", getenv("HOME"), sPkrq, sPtpch, sBuf );
    if( sql_UnloadToFile(sTmpFileName,sSqlStr,'^','\\',&lRCount)!= MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�����ļ�����ʧ��,[%s]",sSqlStr),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_GENFILE,MSG_BATCH_SJTJ_GENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if( lRCount == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:��¼��Ϊ�㣬�����ύ�ⲿ����Ƕ�״���"),"WARNING");
        /*fpub_SetMsg(lXmlhandle,BATCH_REPSCODE_SUCC,"BATCH:��¼��Ϊ�㣬�����ύ�ڲ�����Ƕ�״���");*/
        COMP_SOFTSETXML(XMLNM_RESPCODE, BATCH_REPSCODE_SUCC)
        COMP_SOFTSETXML(XMLNM_RESPMSG, "BATCH:��¼��Ϊ�㣬�����ύ�ⲿ����Ƕ�״���")
        /* ���ñ������ύ�����ļ��� */
        COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_WJS,"0" );
        /* ���ñ������ܱ��� */
        COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZBS,"0");
        /* ���ñ������ܽ�� */
        COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZJE,"0.00");
    
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
    /* ������ܵĻ�����Ϣ */
    /* �ļ�����֣�ֱ�Ӵ��� */
    if( lPgNum <= 0 )
    {
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
    }
    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ϸ����ʼ"),"DEBUG");
    /* ������ϸ��Ϣ */
    dFileAmt = 0.00;
    iFileNum = 0;
    iTotalNum = 0;
    dTotalAmt = 0.00;
    memset(linebuf, 0, sizeof(linebuf));
    iAbort = 0;
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        /* ���˿���  */
        if( 0 == linebuf[0] || 13 == linebuf[0] )
        {
            continue;
        }
                
        /* �ļ��ڼ�¼�� */
        iFileNum++;

        /* �������ã�������ϸ��Ϣ */
        memset(outbuf, 0, sizeof(outbuf));
        iResult = detailProc_write(lXmlhandle,&iLsxh, linebuf,&dFileAmt,outbuf,&thisSort,t_fileColumnList);
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��ϸ��Ϣ����ʧ��,[%s]", linebuf),"ERROR");
            iAbort=4;
            break;
        }

        /* ��ϸ�����¼���� */
        iTotalNum ++;
        /* ���һ������ */
        length = strlen( outbuf );
        outbuf[ length ] = '\n';
        /* д���ύ�����ļ� 
        LOG(LM_STD,Fmtmsg("BATCH: �����ļ�д��[%d][%d][%s]",\
                iFileNum,length,outbuf),"ERROR");*/
        iResult = fwrite( outbuf, length + 1, 1, hostfp);
        if( iResult < 0)
        {
            LOG(LM_STD,Fmtmsg("BATCH: �ļ�д��ʧ��,[%d],[%d],[%s]",\
                iResult,errno,strerror(errno)),"ERROR");
            iAbort=7;
            break;
        }
        /* �ж��Ƿ���Ҫ����ļ� */
        if( ( lPgNum > 0 ) && ( ( iLsxh% lPgNum ) == 0 ) )
        {
            /* �����ں󣬴��������Ϣ */
            if( strcmp( sFileType,"03" ) == 0 || /* 03 ����ϸ������ */
                strcmp( sFileType,"04" ) == 0 )  /* 04 ���ܣ�����ϸ������ */

            {
                /* ֱ����ĩβ��ӻ�����Ϣ */
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
            if( strcmp( sFileType,"02" ) == 0 || /* 02 ���ܣ�����ϸ */
                strcmp( sFileType,"04" ) == 0 )  /* ���ܣ�����ϸ������ */
            {
                /* ������ǰ�����������Ϣ, ��Ҫ��д�ļ��������ܼ�¼�����ļ�ͷ */
                /* ��д��һ����ʱ�ļ� */
                snprintf( sTmpFileFullName, sizeof( sFileFullName ), "%s.tmp",sFileFullName );
                hostfp = fopen( sTmpFileFullName, "w+");
                if( hostfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ���ļ�����ʧ��,[%s]",sTmpFileFullName),"ERROR");
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
                /* ����ϸ�ļ���ӵ����ļ����� */
                tmpfp = fopen( sFileFullName,"r+" );
                if( tmpfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ���ļ�����ʧ��,[%s]",sFileFullName),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                    iAbort=6;
                    break;
                }
                memset( sBuf, 0x00, sizeof( sBuf ) );
                /* ����ϸ�ļ�����д�뵽���ļ��Ļ��ܼ�¼֮�� */
                while( fgets( sBuf, BATCH_MAX_FILELINE_BYTE, tmpfp ) != NULL )
                {
                    fprintf( hostfp, "%s", sBuf );
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                }
                fclose( tmpfp );
                fclose( hostfp );

                /* ɾ����ϸ�ļ��������ļ�����Ϊͬ���ļ� */
                unlink( sFileFullName );
                iResult = rename( sTmpFileFullName, sFileFullName );
                if( iResult != 0 )
                {
                    iAbort=7;
                    break;
                }
            }

            /* �������ʱ�Ѳ����Ӧ��¼���ļ���� */
            /* �ļ��� */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjmc", iFileCount );
            COMP_SOFTSETXML(  sNode , sFileParsedName);
            /* �ļ�ȫ�� */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", iFileCount );
            COMP_SOFTSETXML(  sNode ,sFileFullName );
            /* �ļ��ڱ��� */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iFileCount );
            COMP_SOFTSETXML(  sNode , itoa( iFileNum ) );
             /* �ļ��ڽ��׽�� */
            memset( sNode, 0x00, sizeof( sNode ) );
            sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iFileCount );
            sprintf( sBuf, "%.2f", dFileAmt );
            COMP_SOFTSETXML(  sNode , sBuf );

            /* ����һ���ļ� */
            /* �ļ����� */
            iFileCount ++;

            COMP_SOFTSETXML( XMLNM_BATCH_SJTJ_WJXH , itoa( iFileCount ) );
        
            if( strlen( sFileBasicName ) < 1 ) 
            {
                /* �ļ���Ĭ�ϣ�����Ƕ��+ҵ���ţ��������ڣ����κ�+�ļ����.req */
    			memset(sBuf, 0x00, sizeof(sBuf));
    			COMP_SOFTGETXML( XMLNM_BATCH_STEPINFO_DQBD, sBuf);
                snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                    "rwqt_%s_%s_%s_%d_%s.req", sYwbh, sPkrq, sPtpch, iFileCount, sBuf );
            }
        
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

            if( ( hostfp = fopen( sFileFullName, "w" ) ) == NULL )
            {
                LOG(LM_STD,Fmtmsg("���ļ�ʧ��,file=[%s],error=[%s]",\
                    sFileFullName,strerror(errno)),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* ��ϸ�����ܽ�� */
            dTotalAmt += dFileAmt;
            /* ���ļ���¼�����ܽ���0 */
            iFileNum = 0;
            dFileAmt = 0.00;

        }

        memset(linebuf, 0, sizeof(linebuf));
    }

    fclose( srcfp );

    if( iFileNum > 0  && iAbort == 0  )  /* �����һ���ļ��޼�¼(���ļ�),�򲻻��ύ���� */
    {
        if( lPgNum > 0 )
        {
            /* �����ļ���֣������Ҫ����ͷ�ϵĻ��ܼ�¼ */
            if( strcmp( sFileType,"02" ) == 0 || /* 02 ���ܣ�����ϸ */
                strcmp( sFileType,"04" ) == 0 )  /* ���ܣ�����ϸ������ */
            {
                fclose( hostfp );
                /* ������ǰ�����������Ϣ, ��Ҫ��д�ļ��������ܼ�¼�����ļ�ͷ */
                /* ��д��һ����ʱ�ļ� */
                snprintf( sTmpFileFullName, sizeof( sFileFullName ), "%s.tmp",sFileFullName );
                hostfp = fopen( sTmpFileFullName, "w+");
                if( hostfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ���ļ�����ʧ��,[%s]",sTmpFileFullName),"ERROR");
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
                /* ����ϸ�ļ���ӵ����ļ����� */
                tmpfp = fopen( sFileFullName,"r" );
                if( tmpfp == NULL )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ���ļ�����ʧ��,[%s]",sFileFullName),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
                    iAbort=6;
                }
                while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, tmpfp ) != NULL )
                {
                   fprintf( hostfp, "%s", linebuf );
                }
                fclose( tmpfp );
                /* ɾ����ϸ�ļ��������ļ�����Ϊͬ���ļ� */
                unlink( sFileFullName );
                iResult = rename( sTmpFileFullName, sFileFullName );
                if( iResult != 0 )
                {
                    fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                    iAbort=11;
                }
            }
        }

        /* ���������Ϣ */
        if( strcmp( sFileType,"03" ) == 0 ||  /*  ��ϸ �� ���� ��ʽ */
            strcmp( sFileType,"04" ) == 0 )   /*  ���ܣ���ϸ�����ܸ�ʽ */
        {
            /* ���ñ�֤�ļ�������� */

            iResult = totalProc_write(lXmlhandle,iFileNum,dFileAmt,hostfp, BATCH_TOTAL_TAIL,sFileType,t_fileTotalSortList,t_fileColumnList);
            if( iResult < 0)
            {
                fpub_SetMsg(lXmlhandle,MID_BATCH_TOTALPROC,\
                          Fmtmsg(MSG_BATCH_TOTALPROC, iResult ));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                iAbort=12;
            }
        }

        /* �ļ��� */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjmc", iFileCount );
        COMP_SOFTSETXML(  sNode, sFileParsedName );
        /* �ļ�ȫ�� */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", iFileCount );
        COMP_SOFTSETXML(  sNode, sFileFullName );
        /* �ļ��ڱ��� */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnbs", iFileCount );
        COMP_SOFTSETXML(  sNode , itoa( iFileNum) );
        /* �ļ��ڽ��׽�� */
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjnzje", iFileCount );
        sprintf( sBuf, "%.2f", dFileAmt );
        COMP_SOFTSETXML(  sNode , sBuf );
        /* ��ϸ�����ܽ�� */
        dTotalAmt += dFileAmt;
    }
    else /* ���ļ���ɾ�� */
    {
        iFileCount --;
        LOG(LM_STD,Fmtmsg("BATCH: �����ύ�ļ��������: [%d]",iAbort),"ERROR");
        unlink( sFileFullName );
    }

    /* linux���ظ�fclose��coredump */
#ifdef _OS_LINUX__
    if( hostfp->_fileno >= 0 )
#endif
    fclose( hostfp );

    unlink(sTmpFileName);

    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_totalsortlistFree();

    /* �����ļ��ڼ�¼�Ĵ���״̬ 
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
LOG(LM_DEBUG,Fmtmsg("������ϸ��ˮ��:begin"),"ERROR");
    snprintf(sSqlStr,sizeof(sSqlStr),"UPDATE %s SET clzt='1' \
                  WHERE pkrq='%s' AND ptpch='%s' ",\
                  sTableName, sPkrq, sPtpch);
    if( sql_DynExec(sSqlStr,&iResult)!=0 && iResult <=0 )
    {
        LOG(LM_STD,Fmtmsg("������ϸ��ˮ��ʧ��:[%s], [%d]",\
                                sSqlStr, sqlca.sqlcode),"ERROR");
        iAbort = -9;
    }
LOG(LM_DEBUG,Fmtmsg("������ϸ��ˮ��:end"),"ERROR");
    */

    /* �����쳣 */
    if( iAbort )
    {
        LOG(LM_STD,Fmtmsg("BATCH: �����ύ�ļ��������: [%d]",iAbort),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_GENFILE,MSG_BATCH_SJTJ_GENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;
    }

    /* ���ñ������ύ�����ļ��� */
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_WJS,itoa(iFileCount));
    /* ���ñ������ܱ��� */
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZBS,itoa(iTotalNum));
    /* ���ñ������ܽ�� */
    memset(sBuf,0,sizeof(sBuf));
    sprintf(sBuf,"%.2f",dTotalAmt);
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_ZJE,sBuf );
    
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

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_RWQT_WAIT
�������: SBATCH_RWQT_WAIT
�������: ��������Ƕ���ύ�ļ���ȴ�ʱ��
�������:
 ��� ��������  ��������      ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_RWQT_WAIT(HXMLTREE lXmlhandle)
{
    int  iParas,iResult;
    char sBuf[128];
    /* int  iFileNum = 0;      �ļ��ڼ�¼�� */
    int  iFirmTime = 0;     /* �̶��ϵ�ʱ�� */
    int  iFloatTime= 0;     /* �����ϵ�ʱ�� */
    int  iTotal = 0;
    int  iFileRec = 0;      /* �ļ���¼�� */
    int  iMAXHOSTWAIT = 0;  /* ��ȴ�ʱ�� */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�ļ��ڼ�¼��")
    iFileRec = atoi( sBuf );
    
    /* �̶��ϵ�ʱ��  */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_GDDDSJ,sBuf);
    iFirmTime = atoi( sBuf );
    /* �����ϵ�ʱ�� */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_FDDDSJ,sBuf);
    iFloatTime = atoi( sBuf );
    /* ��ȴ�ʱ��  */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_BATCH_MAXHOSTWAIT,sBuf);
    iMAXHOSTWAIT = atoi( sBuf );

    /* �ύ�����ж�ʱ�� = �̶��ϵ�ʱ�� + �ļ���¼��/1000 * �����ϵ�ʱ�� */
    iTotal = iFirmTime + iFileRec / 1000 * iFloatTime ;
   
    /* ������ȴ�ʱ�� */
    if( iMAXHOSTWAIT > 1 && iTotal > iMAXHOSTWAIT )
        iTotal = iMAXHOSTWAIT;
        
    COMP_SOFTSETXML(XMLNM_BATCH_SJTJ_WAIT,itoa( iTotal ) );

    LOG(LM_DEBUG,Fmtmsg("firm[%d] float[%d] ret[%d] �ύ�ȴ�ʱ��[%d]",\
        iFirmTime, iFloatTime, iFileRec, iTotal ),"DEBUG")
                  
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:BATCH_RWQT_TIME_CTRL
�������: BATCH_RWQT_TIME_CTRL
�������: ��������Ƕ��ҹ��������ʼʱ����ж�
�������:
 ��� ��������  ��������      ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/

IRESULT SBATCH_RWQT_TIME_CTRL(HXMLTREE lXmlhandle)
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
    /* ��������ִ�е�,���ػ����̽��д��� */
    if ( ret==-1 )
    { 
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_WAIT);
        fpub_SetMsg(lXmlhandle,MID_BATCH_TIMEERR,MSG_BATCH_TIMEERR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL );
        return COMPSTATUS_FAIL;
    }
    if( ret==-2 )
    {   /* ʧ��,����������ִ�� */
        fpub_SetMsg(lXmlhandle,MID_BATCH_TIME_SETERR,MSG_BATCH_TIME_SETERR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;              
}

/* ��Ӧ��ת��,����ת������Ӧ������Ӧ�������е�λ�� */
/* ����˵��
sResp:��Ӧ������
iResoCount:��Ӧ������
sResp_S������ԭ��Ӧ��
iPos�����Ŀ����Ӧ��Ϣλ��
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


/* ���ܴ��� */
int prv_rwqt_totalProc(HXMLTREE lXmlhandle, char *lineBuf, 
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

    LOG(LM_DEBUG,Fmtmsg("BATCH: ������Ϣ����[%s]: ",lineBuf ),"DEBUG")

    /*trim�س����з�*/
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
                 case BATCH_FILESORT_COLUNM_FIX:  /* ���� */
                     memcpy(itemBuf, lineBuf+gSFileColumn->offset-1,gSFileColumn->columnlen);
                     break; 
                 case BATCH_FILESORT_COLUNM_SPLIT_TAIL:/* ȥβ�ָ��� */

                 case BATCH_FILESORT_COLUNM_SPLIT:/* �ָ��� */
                     fprv_getSubStr(lineBuf, gSFileColumn->columnsn, pFileSort->columnsprtr, itemBuf);
                     break; 
                 default:
                     break; /* Ĭ�ϲ����� */
             }

             /* 20121105 added by yangdong  ���ӻ�����Ϣ�����ݸ�ʽ���� */
            if( gSFileColumn->izoom != 0 )  /* �����ƫ��,����ƫ�ƺ���ֵ */
            {
                dTmp=atof(itemBuf)*pow(10,-gSFileColumn->izoom);
                if( gSFileColumn->iprecision < 1 )
                    gSFileColumn->iprecision = 2;  /* Ĭ��С������2 */
                sprintf(sFmt,"%%.%df",gSFileColumn->iprecision);
                snprintf(itemBuf, sizeof( itemBuf ), sFmt,dTmp);
            }
             /* ��������ַ� */
            if ( gSFileColumn->ifiller > 0 && gSFileColumn->columnlen > 0 )  
            {
                memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
                strcpy( tmpBuf, itemBuf );
                position = gSFileColumn->columnlen; 
                if ( gSFileColumn->regular[0] == 'R' )   /* �Ҷ��� */
                {
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* ������Ч�ַ���ʼλ�� */
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
                else if ( gSFileColumn->regular[0] == 'L' )   /* ����� */
                {
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* ��������ַ���ʼλ�� */
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
                else /* �����ö��뷽ʽ */
                {
                    j = 0;
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* ���ҷ�����ַ� */
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
             if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_SETXML) == 0) /* �����ԣ�����xml*/
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
             else if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_ZJE) == 0) /* �����ԣ��ܽ��*/
             {
                 *dTotalAmt = atof( itemBuf );
             }
             else if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_ZBS ) == 0) /* �����ԣ��ܱ���*/
             {
                 *iTotalCount = atoi( itemBuf );
             }
             count=0;
        }
    }
    return count;
}

/* ��ϸ���� */
int prv_rwqt_detailProc(HXMLTREE lXmlhandle,char *inBuf,int iPos, char *sSubItem,BATCH_FILESORT *pFileSort, double* dDetailAmt ,i_list_t *t_fileColumnList)
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

    /*trim�س����з�*/
    iLen = strlen( inBuf );
    if( inBuf[iLen-1] == 10 || inBuf[iLen-1] == 13 )
    {
        inBuf[iLen-1] = 0;
    }

    if( inBuf[iLen-2] == 10 ||  inBuf[iLen-2] == 13 )
    {
        inBuf[iLen-2] = 0;
    }
    
    /* ����ӳ���ϵ���������λ�����ļ�����Ϣ���ҵ���������Ϣ������ȡ��Ӧ��ֵ */
    iFound = 0;
    for( pfileColumnIter = i_list_begin(t_fileColumnList);
             pfileColumnIter!= i_list_end(t_fileColumnList);
                 pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = NULL; 
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        if( pFileSort->fileclasssn == gSFileColumn->fileclasssn &&  /* ��ϸ */
            gSFileColumn->columnsn == iPos ) /* ����� */
        {
            iFound = 1;
            break;
        }
    }
    if(  iFound != 1 ) /* �ļ���������Ϣδ��ȡ�� */
    {
        /*failed = -1;*/
        LOG(LM_STD,Fmtmsg("BATCH: MAP��columnid[%s]pos[%d] ������Ϣδ�ҵ�",   gSFileColumn->columnid, iPos ),"ERROR")
        LOG(LM_STD,Fmtmsg("BATCH: filesort_sn[%d] column_sn[%d] pos[%d]",\
            pFileSort->fileclasssn, gSFileColumn->fileclasssn,iPos ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_NOTFOUND,MSG_BATCH_FILECOLUMN_NOTFOUND);
        return -1;
    }

    memset(itemBuf, 0, sizeof(itemBuf));
    if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_FIX ) /* ���� */
    {
        memcpy(itemBuf,inBuf+gSFileColumn->offset-1,gSFileColumn->columnlen);
        trim(itemBuf);
    }
    else if ( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT || /* �ָ��*/
              pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL ) /* ȥβ�ָ��*/
    {
         fprv_getSubStr(inBuf, iPos, pFileSort->columnsprtr, itemBuf);
    }
    else /* ������֧�� */
    {
        /*failed=-2;*/
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_FF, MSG_BATCH_WJGS_FF );
        return -1;
    }    
    /* �������Ļ��лس��� */
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

    /* ��������ַ� */
    if ( gSFileColumn->ifiller > 0 )  
    {
        position = iLen ;
        memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
        strcpy( tmpBuf, itemBuf );
        if ( gSFileColumn->regular[0] == 'R' )   /* �Ҷ��� */
        {
            for( i = 0; i<= iLen; i++ )
            {
                 /* ������Ч�ַ���ʼλ�� */
                 if( tmpBuf[i] != gSFileColumn->ifiller )
                 {
                     position = i; 
                     break;
                 }
            } 
            memset( itemBuf, 0x00, sizeof( itemBuf ) );
            memcpy( itemBuf, tmpBuf+position, iLen - position );
        }
        else if ( gSFileColumn->regular[0] == 'L' )   /* ����� */
        {
            for( i = 0; i<= iLen; i++ )
            {
                 /* ��������ַ���ʼλ�� */
                 if( tmpBuf[i] == gSFileColumn->ifiller )
                 {
                     position = i; 
                     break;
                 }
            } 
            memset( itemBuf, 0x00, sizeof( itemBuf ) );
            memcpy( itemBuf, tmpBuf, position );
        }
        else /* �����ö��뷽ʽ */
        {
            j = 0;
            for( i = 0; i<= iLen; i++ )
            {
                 /* ���ҷ�����ַ� */
                 if( tmpBuf[i] != gSFileColumn->ifiller )
                 {
                     itemBuf[j++]= tmpBuf[i] ;
                 }
            }
            itemBuf[j] = '\0';
        }
    }

    /* ��������ƫ�� */
    if ( gSFileColumn->izoom != 0 )  
    {
        dVal = atof(itemBuf)*pow(10,-gSFileColumn->izoom);
        sprintf( sFmt,"%%.%df", gSFileColumn->iprecision );
        snprintf( itemBuf, sizeof( itemBuf ), sFmt, dVal );
    }

    if( strcmp( gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_ADD) == 0)/* ���׽���ۼ� */
    {
         *dDetailAmt += atof( itemBuf );
    }
    strcpy( sSubItem, itemBuf );
    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_RWQT_RETURN
�������:SBATCH_RWQT_RETURN
�������: ��������Ƕ�׷��غ���
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
    1   1-����    �����ļ���    416XML�����ַ���  *      N      
    2   1-����    ҵ�����      416XML�����ַ���  *      N    
    3   1-����    ӳ���ʶ      416XML�����ַ���  *      N    
    4   1-����    �ļ���ʶ      416XML�����ַ���  *      N      
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_RWQT_RETURN(HXMLTREE lXmlhandle)
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
    char sFileName[256]; /* ���������ļ�ȫ��(��·��) */
    char sFileID[40+1];
    char sMapID[40+1];   /* ӳ���ʶ */
    int  iTSortCount=0;
    char sRespID[40+1];  /* ��Ӧ��ת����ʶ */
    int  i,iAbort=0;
    char sPtpch[8+1];
    char sPkrq[8+1];
    char sNode[32+1];
    FILE *srcfp;
    FILE *fp1;
    char sFileType[2+1];
    int  iTotalCount = 0;    /* ������Ϣ�ܱ��� */     
    int  iTotalRows = 0;
    int  iDetailEndRow= 0;   /* ��ϸ���һ���к� */
    double dTotalAmt = 0.00;  /* ������Ϣ�ܽ�� */
    double dDetailAmt = 0.00; /* ��ϸ�ܽ�� */
    int  iClassPre = 0;       /* ��һ������� */
    int  iRearClass = 1;
    int  ii = 0, index = 0;
    int  iDetailCount = 0;
    int  updFlag = 0;
    int  valFlag = 0;
    int  iUniqueKey=1;/*����������Ψһ���� 1-��*/
    int  pos[BATCH_MAX_TABLEREG_NUM];            /* ����ӳ���У�����ֶ������������ļ��е�λ��*/

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
    int iHostXyxxFlag = 0;   /* ������Ӧ��Ϣת����־*/
    int iDsfXyxxFlag = 0;   /* ��������Ӧ��Ϣת����־*/

    char ssResp_S[BATCH_MAX_RESP][10+1];  /*������Ӧ�룭Դ */
    char ssResp_D[BATCH_MAX_RESP][20+1];  /*������Ӧ�룭Ŀ�� */ 
    char ssMsg_D[BATCH_MAX_RESP][40+1];   /*������Ӧ��Ϣ */
    char ssDFTResp_D[20+1]; 
    char ssDFTMsg_D[40+1]; 
    char sHostFileFlg[1+1];/*������������־*/
    char ssDsfResp_S[BATCH_MAX_RESP][10+1];  /*������Ӧ�룭Դ */
    char ssDsfResp_D[BATCH_MAX_RESP][20+1];  /*��������Ӧ�룭Ŀ�� */
    char ssDsfMsg_D[BATCH_MAX_RESP][40+1];   /*��������Ӧ��Ϣ */
    char ssDFTDsfResp_D[20+1];               /*Ĭ����Ӧ��*/
    char ssDFTDsfMsg_D[40+1];                /*Ĭ����Ӧ��Ϣ*/
    int  iPosXym = 0;                        /*��Ӧ���ڸ�������г���λ��*/
    int  iPos = 0;                           /*��Ӧ������Ӧ��Ϣ������λ��*/
    int  iHostValPos = 0;
    int  iDsfValPos  = 0;
    int  iFileValPos = 0;                     /*������Ϣ�ڻ����ļ�λ��*/
    
    BATCH_FILESORT thisSort;
    BATCH_FILESORT thisSortT;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")

    COMP_PARACOUNTCHKMIN(5)
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�ļ���")
    pstrcopy(sFileName,sBuf,sizeof(sFileName));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�ļ���ʶ")
    pstrcopy(sFileID,sBuf,sizeof(sFileID));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"ӳ���ʶ")
    pstrcopy(sMapID,sBuf,sizeof(sMapID));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"ע�����")
    pstrcopy(sTableName,sBuf,sizeof(sTableName));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(5,sBuf,"�ļ�����")
    pstrcopy(sFileType,sBuf,sizeof(sFileType));
    
    /* �������� */
    memset(sPkrq, 0, sizeof( sPkrq ) );
    COMP_SOFTGETXML( XMLNM_BATCH_PKRQ, sPkrq );
    trim(sPkrq);
    
    /* ƽ̨���κ� */
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sPtpch);
    trim(sPtpch);

    /*���ݲ���ɾ���������������ļ�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sHostFileFlg, 0x00, sizeof(sHostFileFlg));
    COMP_SOFTGETXML(XMLNM_BATCH_HOSTFILE, sBuf);
    sHostFileFlg[0] = sBuf[0];
    if ( sHostFileFlg[0] == '1' )
    {/*��Ҫɾ���������������ļ�*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/batch/sjth/wjxh", sBuf)
        memset( sNode, 0x00, sizeof( sNode ) );
        sprintf( sNode, "/batch/sjtj/wjxx|%d/wjqm", atoi(sBuf) );
        memset(sFileFullName, 0x00, sizeof(sFileFullName));
        COMP_SOFTGETXML(  sNode, sFileFullName );
        LOG(LM_STD,Fmtmsg("BATCH: ������ز���,%s-ɾ�������������������ļ�[%d][%s]",\
            sHostFileFlg,atoi(sBuf), sFileFullName ),"INFO");
        unlink( sFileFullName );
    }

    LOG(LM_STD,Fmtmsg("BATCH: file[%s],type[%s]table[%s]map[%s]",\
        sFileName, sFileType, sTableName, sMapID ),"INFO");

    memset( sDbType, 0x00, sizeof( sDbType ) );
    sprintf(sDbType, "%s", getenv("DB"));
    trim( sDbType );

    /* added by yangdong 20130312 Ĭ����Ӧ��Ϣ��ʼ�� */
    memset( ssDFTResp_D, 0x00, sizeof( ssDFTResp_D ) );
    memset( ssDFTMsg_D, 0x00, sizeof( ssDFTMsg_D ) );
    memset( ssDFTDsfResp_D, 0x00, sizeof( ssDFTDsfResp_D ) );
    memset( ssDFTDsfMsg_D, 0x00, sizeof( ssDFTDsfMsg_D ) );

    /* ��ȡ������Ӧ��ӳ����Ϣ */
    /* ת����־ */
    COMP_SOFTGETXML(XMLNM_BATCH_ZJMAPINFO_ZHBZ,sBuf);
    trim( sBuf );
    if( sBuf[0] == '0' ) /* 0-��Ҫת�� */
    {
        /* ��ȡת����ʶ */
        memset( sRespID, 0x00, sizeof( sRespID ) );
        COMP_SOFTGETXML(XMLNM_BATCH_ZJMAPINFO_ZHBS, sRespID );
        trim( sRespID );
        if( strlen( sRespID ) < 2 ) /* �ж�ת����ʶ�Ƿ�Ϊ�� */
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_RESPNULL,MSG_BATCH_RESPNULL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
        /* ��ѯ��Ӧ��Ӧת����ʶ��Ϣ */
        sprintf(sSqlStr, "SELECT *  FROM BATCH_MAPRESP WHERE mapid='%s' " , sRespID);
        if ((cur = DCIDeclareCursor(sSqlStr, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        iHostResp= 0;
        /* ��������Ӧ����Ϣ���������� */
        memset( &sdb_batch_mapresp, 0x00, sizeof( BATCH_MAPRESP ) );
        while( ( iRet = DBFetch(cur, SD_BATCH_MAPRESP, NUMELE(SD_BATCH_MAPRESP), &sdb_batch_mapresp, sErrmsg ) ) > 0 )
        {
            if( iHostResp > BATCH_MAX_RESP )
            {
                fpub_SetMsg(lXmlhandle,MID_SYS_FAIL,"��Ӧ��ת����Ϣ������ϵͳ����");
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
            /* Ĭ��ת����ʶ */
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

    /* ��ȡ��������Ӧ��ӳ����Ϣ */
    /* ת����־ */
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_ZHBZ,sBuf);
    trim( sBuf );
    if( sBuf[0] == '0' ) /* 0-��Ҫת�� */
    {
        /* ��ȡת����ʶ */
        memset( sRespID, 0x00, sizeof( sRespID ) );
        COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_ZHBS, sRespID );
        trim(  sRespID );
        if( strlen( sRespID ) < 2 ) /* �ж�ת����ʶ�Ƿ�Ϊ�� */
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_RESPNULL,MSG_BATCH_RESPNULL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
        sprintf(sSqlStr, "SELECT *  FROM BATCH_MAPRESP WHERE mapid='%s' " , sRespID);
        if ((cur = DCIDeclareCursor(sSqlStr, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }

        memset( &sdb_batch_mapresp, 0x00, sizeof( BATCH_MAPRESP ) );
        iDsfResp = 0;
        /* �ѵ�������Ӧ����Ϣ���������� */
        while( ( iRet = DBFetch(cur, SD_BATCH_MAPRESP, NUMELE(SD_BATCH_MAPRESP), &sdb_batch_mapresp, sErrmsg ) ) > 0 )
        {
            if( iDsfResp > BATCH_MAX_RESP )
            {
                fpub_SetMsg(lXmlhandle,MID_SYS_FAIL,"��Ӧ��ת����Ϣ������ϵͳ����");
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
            /* Ĭ��ת����ʶ */
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
    /* ��ȡ������Ҫ�ֶ�(���������͸��������ֶ���) */
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    sprintf(sSqlStr, "SELECT * FROM BATCH_FILEMAP WHERE mapid='%s' AND ( thgxbz='1' OR thgxbz='2') ORDER BY thgxbz, columnsn" , sMapID );
    if ((cur = DCIDeclareCursor( sSqlStr, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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

        /* �ڵڶ����ֶ�ǰ�� , */
        if( iCount > 1 )
            strcat( sSqlStr,  ",");

        trim( sdb_batch_filemap.columnid );
        trim( sdb_batch_filemap.thgxbz );

        /* ��¼����ֶ������������ļ�λ�� */
        pos[iCount2] = sdb_batch_filemap.zjjgwz ;
        if( sdb_batch_filemap.thgxbz[0] =='2' ) /* �������� */
        {
            if(  updFlag == 0 ) /* ��һ���������� */
            {
                /* �ڵ�һ����������ǰ�棬����������Ӧ��ת�� */
                if( iHostResp > 0 )  /* ��Ҫ����������Ӧת�� */
                {
                    iHostValPos = iCount; /* ����ת��λ��(�������ֶ���λ��) */
                    /* ת��������Ӧ��Ϣ---�ɹ���־ת�� */
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    sprintf( sBuf, " ,cgbz=:v%d" , iCount );
                    strcat( sSqlUpd, sBuf );
                    if( iHostXyxxFlag == 1 )  /* modified by yangdong ��Ҫת��������Ӧ��Ϣ */
                    {
                        iCount ++;
                        memset( sBuf, 0x00, sizeof( sBuf ) );
                        sprintf( sBuf, " ,xyxx=:v%d" , iCount );
                        strcat( sSqlUpd, sBuf );
            
                        /* �����ֶ� */
                        strcat( sSqlStr,  "cgbz, xyxx," );
                    }
                    else
                    {
                        /* �����ֶ� */
                        strcat( sSqlStr,  "cgbz, " );
                    }
                }
                /* ���ӵ�������Ӧ��ת�� */
                if( iDsfResp > 0 )
                {
                    if( iHostResp > 0 ) /*  ǰ������������Ӧ��ת��ʱ */
                        iCount ++;
                    iDsfValPos = iCount;  /* ��������Ӧ��ת��λ��(�������ֶ���λ��) */
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    sprintf( sBuf, " ,dsfxym=:v%d" , iCount );
                    strcat( sSqlUpd, sBuf );
                    if( iDsfXyxxFlag == 1 )  /* modified by yangdong ��Ҫת��������Ӧ��Ϣ */
                    {
                        iCount ++;
                        memset( sBuf, 0x00, sizeof( sBuf ) );
                        sprintf( sBuf, " ,dsfxyxx=:v%d" , iCount );
                        strcat( sSqlUpd, sBuf );
                        /* �����ֶ� */
                        strcat( sSqlStr,  " dsfxym, dsfxyxx," );
                    }
                    else
                    {
                        /* �����ֶ� */
                        strcat( sSqlStr,  " dsfxym ," );
                    }
                }

                if( ( iDsfResp > 0 )  ||  ( iHostResp > 0 ) )
                    iCount ++;

                /* ׷��WHERE ���� */
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
            if ( strcmp(sdb_batch_filemap.columnid, "lsxh") == 0)
            {
                sprintf( sBuf, " AND %s =:v%d" , sdb_batch_filemap.columnid, iCount );
            }else
            {
                sprintf( sBuf, " AND trim(%s) =:v%d" , sdb_batch_filemap.columnid, iCount );
            }
            
        }
        else if( sdb_batch_filemap.thgxbz[0] == '1' ) /* �������� */
        {
            valFlag ++;
            if( valFlag == 1 )
                sprintf( sBuf, " %s=:v%d" , sdb_batch_filemap.columnid, iCount );
            else
                sprintf( sBuf, " ,%s=:v%d" , sdb_batch_filemap.columnid, iCount );

            /* ��¼��Ӧ��λ�� */
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
    {/*������������Ψһ���� 0-���� */
        memset(sBuf, 0x00, sizeof(sBuf));
        sprintf( sBuf, " AND  pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch  );
        strcat( sSqlUpd, sBuf );
    }

    memset( sBuf, 0x00, sizeof( sBuf ) );
    sprintf( sBuf, " FROM %s WHERE 1=2" , sTableName );
    strcat( sSqlStr, sBuf );

    if( strlen( sSqlUpd ) > 2048 || strlen( sSqlStr ) > 2048 )
    {
        LOG(LM_STD,Fmtmsg("SQLEN[%d][%d]��������2048", strlen( sSqlStr ) , strlen( sSqlUpd ) ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("UPDATE SQL[%s]", sSqlUpd ),"INFO")
    LOG(LM_STD,Fmtmsg("SELECT SQL[%s]", sSqlStr ),"INFO")


    /* �ļ���ϸ����ӳ�������ʼ�� */
    iResult = fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_DETAIL,&t_fileDetailSortList);
    if( iResult <= 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: �ļ���ϸ����ӳ�������ʼ��ʧ��,[%s][%d]",\
                           sFileID,iResult ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                           Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    memset( &thisSort, 0, sizeof(BATCH_FILESORT) );
    /* ֻȡ��һ����ϸ������Ϣ */
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* �ļ�����Ϣ�����ʼ�� */
    iResult =fprv_initFileColumn(sFileID,&t_fileColumnList);
    if ( iResult <= 0)
    {
        LOG(LM_STD,Fmtmsg("BATCH: �ļ�����Ϣ�����ʼ��ʧ��,[%s]",sFileID),"ERROR");
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
                    Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ��ȡ�ļ������� rows */
    /* 20110825 ���������ļ�����ȡ���� */
    /* �������ļ� */
    if((fp1 = fopen(sFileName, "r")) == NULL)
    {
        batch_detailsortlistFree();
        batch_columnlistFree();
        LOG(LM_STD,Fmtmsg("BATCH: ����������ļ�[%s]ʧ��",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    iTotalRows=0;
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, fp1 ) != NULL )
    {
        iTotalRows++ ;
    }
    /* ȥ�����һ�еĻس�����,���ж���������޷����� */
    if( 10 == linebuf[0] || 13 == linebuf[0] )
    {
        iTotalRows-- ;
    }
    LOG(LM_DEBUG,Fmtmsg("BATCH: �ļ�������[%d]", iTotalRows),"DEBUG");
    fclose(fp1);

    /*  �����������ļ����� */
    index = 0;
    srcfp =fopen( sFileName, "r" );
    if ( srcfp == NULL )
    {
        LOG(LM_STD,Fmtmsg("BATCH: �����������ļ�����ʧ��,[%s]",sFileName),"ERROR");
        batch_detailsortlistFree();
        batch_columnlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* ���ܷ�����Ϣ��ʼ�� */
    /* 01 ����ϸ 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
    if( strcmp( sFileType, "01" )  != 0 )
    {
        iTSortCount=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_TOTAL,\
                                          &t_fileTotalSortList);
        if( iTSortCount <= 0 )
        {
            fclose( srcfp );
            batch_detailsortlistFree();
            batch_columnlistFree();
            LOG(LM_STD,Fmtmsg("BATCH: �ļ����ܷ���ӳ�������ʼ��,[%s]",sFileID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                                   Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG,Fmtmsg("BATCH: ���ܼ�¼��[%d]", iTSortCount ),"DEBUG")
    }
    /* ����ͷ���ܵĻ�����Ϣ  */
    /* 01 ����ϸ 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
    if( strcmp( sFileType,"02" ) == 0 || strcmp( sFileType,"04" ) == 0 )
    {
        /* �������ܷ��࣬һ�����ܷ��ദ��һ�м�¼,
           ��Ҫ���ñ�֤���ܷ����˳��ƥ���ļ� */
        iClassPre= 0;  /* ��һ������� */
        for( pfileTotalSortIter = i_list_begin(t_fileTotalSortList);
              pfileTotalSortIter!= i_list_end(t_fileTotalSortList);
                  pfileTotalSortIter = i_list_iter_next(pfileTotalSortIter) )
        {
            /* ȡ���ܷ�����Ϣ */
            memset(&thisSortT, 0, sizeof(BATCH_FILESORT));
            memcpy( &thisSortT,(BATCH_FILESORT *)(pfileTotalSortIter->data),sizeof(BATCH_FILESORT));
            if( strcmp( sFileType,"04" ) == 0 && ( thisSortT.fileclasssn - iClassPre ) > 1 )
            {
                 iRearClass = thisSortT.fileclasssn ; /* β�����ܷ���ķ������ */
                 break;  /* ��ǰ���������Ծ��˵���м�����ϸ���࣬�˳� */
            }
            if( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
            {
                index ++;
                iResult = prv_rwqt_totalProc(lXmlhandle,linebuf, &thisSortT, &dTotalAmt, &iTotalCount ,t_fileTotalSortList,t_fileColumnList);
                if( iResult != 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ������Ϣ����ʧ��,[%s],[%d],[%s]",linebuf,\
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

    /* �������һ����ϸ��Ϣ����� */
    /* 01 ����ϸ 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
   
    if( strcmp( sFileType,"01" ) == 0 || strcmp( sFileType,"02" ) == 0  )
        iDetailEndRow = iTotalRows;               /**/
    if( strcmp( sFileType,"03" ) == 0 )
        iDetailEndRow = iTotalRows - iTSortCount ; /* ��ȥ����������Ϊʵ����ϸ��¼�������� */
    if( strcmp( sFileType,"04" ) == 0 )
        iDetailEndRow = iTotalRows -iTSortCount + iClassPre ;
    /* ��ȥ��β���ܼ�¼����Ϊʵ����ϸ��¼�������� */
    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ϸβ��¼�к�[%d]", iDetailEndRow ),"DEBUG")

    /* ��ȡ������������ֶ���Ϣ */
    cur = DCIDeclareCursor(sSqlStr, 0);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    iAllcount = DCINumCols(cur);                        /* ȡ�ֶ��� */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
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
        LOG(LM_STD,Fmtmsg("�����ڴ����ʧ��!" ),"ERROR")
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
        iType[iCount] = DCIColType(cur, iCount);     /* ȡ�ֶ����� */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
            iflag = -22;
            break;
        }
        iSize[iCount] = DCIColSize(cur, iCount);     /* ȡ�ֶδ�С */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
            iflag = -23;
            break;
        }

        iScale[iCount] = DCIColScale(cur, iCount);    /* ȡ�ֶξ��� */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
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
                  iSize[iCount]++; /*char���ͷ����ڴ��ֶγ���Ӧ�ü�1*/ 
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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
        else /* ���ַ��ʹ��� */
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
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
       }
    }

    /* ��ʼ������ϸ */
    memset(linebuf, 0, sizeof(linebuf));
    iDetailCount = 0;
    /* for cal time cast */
    ftime(&starttime);
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        index ++;
        /* ���˿���  */
        if ( 0 == linebuf[0] || 13 == linebuf[0] )
        {
            continue;
        }

        /*  �ж��Ƿ����һ����ϸ  */
        if( index > iDetailEndRow )
        {
            index --;
            break;
        }
        iDetailCount ++;  /* ��ϸ���� */

        memset(sBuf, 0, sizeof(sBuf));

        iCount = 0;
        iAbort = 0;
        iFileValPos = iCount+1; /* �ȴ����ļ��л�ȡ��Ҫ������Ϣ */
        /* iAllcount Ϊʵ����Ҫ�����ֶ��� */
        while ( iCount < iAllcount )
        {
            if( iCount+1 == iHostValPos ) /* ��Ҫ�����������Ӧ����ֶ�λ�õ���*/
            {
                iPos = -1;
				iResult = prv_resp_conv( ssResp_S,iHostResp, sResp_S, &iPos);
				if( iResult < 0 ) /* ת��ʧ�ܣ�ȡĬ��ֵ */
                {
                    pstrcopy(sdata[iCount], ssDFTResp_D, iSize[iCount]); 
                }else
                {
                    pstrcopy(sdata[iCount], ssResp_D[iPos], iSize[iCount]); 
                }
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: ���ֶ�[%d] ֵΪ[%s], size[%d] type[%d]", \
         iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                if( iHostXyxxFlag == 1 )  /* modified by yangdong ��Ҫת��������Ӧ��Ϣ */
                {
                    iCount  ++;
                    /* ������Ӧ��Ϣ */
                    if( iResult < 0 )  /* ת��ʧ�ܣ�ȡĬ��ֵ */
                    {
                        strcpy( sdata[iCount], ssDFTMsg_D ); 
                    }
                    else 
                        strcpy( sdata[iCount], ssMsg_D[iPos] ); 
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: ���ֶ�[%d] ֵΪ[%s], size[%d] type[%d]", iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                }
            }
            else if( iCount+1 == iDsfValPos ) /* ��Ҫ����ĵ�������Ӧ����ֶ�λ�õ���*/
            {
                iPos = -1;
                iResult = prv_resp_conv( ssDsfResp_S,iDsfResp, sResp_S, &iPos );
                /* ������Ӧ�� */
                if( iResult < 0 )  /* ת��ʧ�ܣ�ȡĬ��ֵ */
                    strcpy( sdata[iCount], ssDFTDsfResp_D ); 
                else
                    strcpy( sdata[iCount], ssDsfResp_D[iPos] ); 
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: ���ֶ�[%d] ֵΪ[%s], size[%d] type[%d]", iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                if( iDsfXyxxFlag == 1 )  /* modified by yangdong ��Ҫת��������Ӧ��Ϣ */
                {
                    iCount  ++;
                    /* ������Ӧ��Ϣ */
                    if( iResult < 0 )  /* ת��ʧ�ܣ�ȡĬ��ֵ */
                        strcpy( sdata[iCount], ssDFTDsfMsg_D ); 
                    else
                        strcpy( sdata[iCount], ssDsfMsg_D[iPos] ); 
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: ���ֶ�[%d] ֵΪ[%s], size[%d] type[%d]", iCount, sdata[iCount], iSize[iCount], iType[iCount] ),"INFO")
*/
                }
            }
            else /*  ���ļ��л�ȡ��Ҫ������Ϣ */
            {
                /* ������ϸ����ȡ�����ֶ�ֵ���������� */
                memset(sBuf, 0x00, sizeof(sBuf));
                iResult = prv_rwqt_detailProc(lXmlhandle,linebuf,pos[iFileValPos], sBuf,&thisSort,&dDetailAmt,t_fileColumnList);
                if( iResult < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ����ļ���ϸ��Ϣ����ʧ��,pos[%d]=[%d],[%d],[%s]: [%d],[%s]",\
                        iFileValPos,pos[iFileValPos],index,linebuf,thisSort.fileclasssn,thisSort.classname),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_DETAIL,MSG_BATCH_PROC_DETAIL );
                    iAbort = -3;
                    break;
                }
                /* ��ظ���ʱ��trim�ֶ� */
                trim( sBuf );

                if( iType[iCount] == DCIT_CHAR || iType[iCount] == DCIT_VARCHAR||
                    iType[iCount] == DCIT_DATE || iType[iCount] == DCIT_CLOB )
                {
                    if (strlen(sBuf) > iSize[iCount]-1)
                    {
                        memcpy(sdata[iCount], sBuf, iSize[iCount]-1);
                        LOG(LM_STD,Fmtmsg("BATCH: ����[%s]����,%dλ���ֶα��Զ���ȡ", sBuf, iCount ),"ERROR")
                    }
                    else
                        strcpy( sdata[iCount], sBuf );  /* sBuf�������ʹ��� */
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: ���ֶ�[%d] ֵΪ[%s], size[%d] type[%d] scale[%d]", \
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
LOG(LM_DEBUG,Fmtmsg("BATCH: ���ֶ�[%d] ֵΪ[%f], size[%d] type[%d] scale[%d]", \
                          iCount, *(double *)sdata[iCount], iSize[iCount], iType[iCount], iScale[iCount] ),"INFO")
*/
                    }
                    else
                    {
                        iInt = atoi( sBuf );
                        *(int *)sdata[iCount] = iInt;
/*
LOG(LM_DEBUG,Fmtmsg("BATCH: ���ֶ�[%d] ֵΪ[%d], size[%d] type[%d] scale[%d]", \
                          iCount, *(int *)sdata[iCount] , iSize[iCount], iType[iCount], iScale[iCount] ),"INFO")
*/
                    }
                }

                /* ��Ӧ���ȡ */
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
                LOG(LM_STD,Fmtmsg("BATCH: ��ر�Ƕ���ļ���ϸ��Ϣ����ret[%d] sqlerr[%s] ��ϸ����[%d]",\
                    iRet, DCILastError(), iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            }else if ( iRet == 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: ��ر�Ƕ���ļ���ϸ��Ϣ����ret[%d] ���¼�¼��Ϊ���� ��ϸ����[%d]",\
                    iRet, iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_UPDZERO,MSG_BATCH_SJTH_UPDZERO);
            }else if ( iRet > 1 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: ��ر�Ƕ���ļ���ϸ��Ϣ����ret[%d] ���¼�¼������Ҽ�� ��ϸ����[%d]",\
                    iRet, iDetailCount ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_UPDMULT,MSG_BATCH_SJTH_UPDMULT);
            }
            if ( iRet != 1 )
            {
                /* added by yangdong 20141204 ���ӳ�����Ϣ�������Ŵ� */
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
            /* �����ύ���񣬼���ϵͳѹ�� */
            if( ( iDetailCount % 5000 ) == 0 )
            {
                ftime(&endtime);
                LOG(LM_STD,Fmtmsg("BATCH: ��ر�Ƕ���ļ���ϸ��Ϣ���´���[%d],cast[%ld]ms", iDetailCount,\
                (endtime.time-starttime.time)*1000+endtime.millitm-starttime.millitm ),"DEBUG");
                if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
                {
                    /*if ( sql_CommitTrans() !=MID_SYS_SUCC )*/
                    if(DCICommit() != 0)
                    {
                        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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
            LOG(LM_STD,Fmtmsg("BATCH: ����ļ���ϸ��Ϣ����[%d]",iAbort ),"INFO");
            break;
        }

        memset(linebuf, 0, sizeof(linebuf));
    }

    /*if ( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        sql_RollbackTrans();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPSTATUS_FAIL ;
    }

    DCIFreeCursor(cur);
    prv_free_data( sdata, iAllcount );
LOG(LM_STD,Fmtmsg("BATCH: ��ر�Ƕ���ļ���ϸ�ļ���������[%d] �ܽ��[%.2f]",iDetailCount, dDetailAmt ),"INFO");
    if ( iAbort == 0  )
    {
        /* ����β��������Ϣ */
        /* 01 ����ϸ 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
        if( ( strcmp( sFileType, "03" ) == 0 ||  strcmp( sFileType, "04" ) == 0 ) && ! iAbort )
        {
            ii = 0;
            /* ���ñ�֤������Ϣ˳�� */
            for( pfileTotalSortIter = i_list_begin(t_fileTotalSortList);
                  pfileTotalSortIter != i_list_end(t_fileTotalSortList);
                  pfileTotalSortIter = i_list_iter_next(pfileTotalSortIter) )
            {
                /* ȡ���ܷ�����Ϣ */
                memset(&thisSortT, 0, sizeof(BATCH_FILESORT));
                memcpy( &thisSortT,(BATCH_FILESORT *)(pfileTotalSortIter->data),sizeof(BATCH_FILESORT));
                if( ( strcmp( sFileType, "04" ) == 0 ) && ( thisSortT.fileclasssn < iRearClass ) )
                {
                    continue;  /* ͷ�����ܷ�����Ϣ���� */
                }
                if( ii == 0 )
                    ;  /* ��һ����Ϣ�Ѿ������linebuf�� */
                else if(  fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
                {
                    ;
                }
                else
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ȡ���ܼ�¼��Ϣʧ��"),"ERROR")
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROC_TOTAL,MSG_BATCH_PROC_TOTAL);
                    iAbort = -24;
                    break;
                }
    
                iResult = prv_rwqt_totalProc(lXmlhandle,linebuf, &thisSortT, &dTotalAmt,&iTotalCount ,t_fileTotalSortList,t_fileColumnList);
                if( iResult != 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ������Ϣ����ʧ��,[%s],[%d],[%s]",\
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
    /* �ͷ�������Դ */
    batch_totalsortlistFree();
    batch_detailsortlistFree();
    batch_columnlistFree();
    
    /* �����쳣 */
    if ( iAbort != 0  )
    {
        LOG(LM_STD,Fmtmsg("BATCH: ����ļ����´������: [%d]",iAbort),"ERROR");
        /* ��Ӧ��Ϣ */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPSTATUS_FAIL ;
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: �ļ����ܼ�¼��[%d] �����ܽ��[%.2f]", iTotalCount, dTotalAmt),"DEBUG")

    if( dTotalAmt > 0.001 ) /* ����л��ܽ����Ϣ */
    {
        /* �жϻ��ܼ�¼����ϸ�Ƿ�ƥ��  */
        if( ( dTotalAmt - dDetailAmt ) > 0.001 || ( dDetailAmt - dTotalAmt ) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ����ļ����ܽ��[%.2f]��ϸ�ϼƽ��[%.2f]",\
                                dTotalAmt, dDetailAmt),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_ZJE, MSG_BATCH_SJTH_ZJE );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPSTATUS_FAIL ;
        }
    }
    if( iTotalCount > 1 ) /* ����л��ܱ�����Ϣ */
    {
        /* �жϻ��ܼ�¼����ϸ�Ƿ�ƥ��  */
        if( iTotalCount != iDetailCount )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ����ļ����ܱ���[%d]��ϸ�ϼƱ���[%d]",\
                                iTotalCount , iDetailCount),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SJTH_ZBS, MSG_BATCH_SJTH_ZBS );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPSTATUS_FAIL ;
        }
    }

    /*if ( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        sql_RollbackTrans();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPSTATUS_FAIL ;
    }

    /* added by yangdong 20130609 ������Ӧ��ת����Χ 1��ֻת�����ʧ����Ϣ */
    COMP_SOFTSETXML( XMLNM_BATCH_SJHP_CVTRESP, "1" );

    /* added by yangdong 20130613 ���Ӵ���������Ĳ�����ʵ��У�����ʵ�ʽ����Ϊ0.00 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_HOST_AMT_FLAG,sBuf);
    if( sBuf[0] == '1' )  /* 1-������ 0-���أ�Ĭ�ϣ� ( �����ñ������򲻴��� ) */
    {
        memset( sSqlUpd, 0x00, sizeof( sSqlUpd ) );
        memset( sBuf, 0x00, sizeof( sBuf ) );
        COMP_SOFTGETXML( XMLNM_BATCH_SJTH_ZJXH,sBuf);
        /* ���ɹ���ϸ��ʵ�ʽ����Ϊ���׽�� */
        sprintf( sSqlUpd, "UPDATE %s SET sjje=jyje WHERE pkrq='%s' AND ptpch='%s' AND wjxh=%d AND cgbz='0' ", \
            sTableName, sPkrq, sPtpch,  atoi( sBuf ) );
        
        /*sql_BeginTrans();  ��DCIBegin ���� 2015-1-7 by chenxm*/
        DCIBegin();
        iRet = DCIExecuteDirect( sSqlUpd );
        if( iRet < 0  )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /* end of add */

    /*���ݲ���ɾ��������Ӧ�ļ�*/
    if ( sHostFileFlg[0] == '1' )
    {/*��Ҫɾ���������������ļ�*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/batch/sjth/wjxh", sBuf)
        memset( sNode, 0x00, sizeof( sNode ) );
        LOG(LM_STD,Fmtmsg("BATCH: ������ز���,%s-ɾ����������������Ӧ�ļ�[%d][%s]",\
            sHostFileFlg,atoi(sBuf), sFileName ),"INFO");
        unlink( sFileName );
    }
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_RWQT_SUM
�������:SBATCH_RWQT_SUM
�������:ͳ������Ƕ�׳ɹ�ʧ����Ϣ
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
ʹ������:
�� �� Ա:
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_RWQT_SUM(HXMLTREE lXmlhandle)
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

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")

    /* ��ϸ���� */
    memset(sBuf,0,sizeof(sBuf));
    memset(sTableName,0,sizeof(sTableName));
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf);
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    /* �������� */
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* ƽ̨���κ� */
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

    /* ���� */
    COMP_SOFTSETXML( XMLNM_BATCH_CGZBS, itoa( iTotalNum ) );
    /* ���׽�� */
    sprintf( sBuf, "%.2f", dTotalAmt );
    COMP_SOFTSETXML(  XMLNM_BATCH_CGZJE, sBuf );
    LOG(LM_DEBUG,Fmtmsg("BATCH:�������,�ɹ��ܱ���[%d],�ɹ��ܽ��[%.2f]",iTotalNum,dTotalAmt),"DEBUG")

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

    /* ���� */
    COMP_SOFTSETXML( XMLNM_BATCH_SBZBS, itoa( iTotalNum ) );
    /* ���׽�� */
    sprintf( sBuf, "%.2f", dTotalAmt );
    COMP_SOFTSETXML(  XMLNM_BATCH_SBZJE, sBuf );

    LOG(LM_DEBUG,Fmtmsg("BATCH:�������,ʧ���ܱ���[%d],ʧ���ܽ��[%.2f]",iTotalNum,dTotalAmt),"DEBUG")

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

