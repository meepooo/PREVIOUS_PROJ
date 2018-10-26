/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_SJTJ.ec
�ļ�����:�ύ�����ļ�����
�� �� Ա:YangDong
��������:20110801

�� �� Ա:YangDong
�޸�����:20141018
�޸�˵��:DCI����

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
        <sonote>BATCH�����ύ�������</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"YangDong\" filesize=\"1238198\">HS-AgentV2.1����</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1238198\">DCI����</rec>\
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
�����������:SBATCH_SJTJ
�������:BATCH_SJTJ
�������: ����ҵ�����������ύ�ļ�
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
IRESULT SBATCH_SJTJ(HXMLTREE lXmlhandle)
{
    char sMapID[40+1];
    char sYwbh[16+1];
    char sColID[32+1];
    char sFileID[32+1];
    char sSqlStr[4096];
    char sSjtjExpWhere[256];
    /* int iWjxh = 0;     �ļ���� */
    /* int iZjszwz = 0;   ��������λ�� */

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
    char sColStr[2048];  /* �ύ��̨ӳ���ֶ� */
    int  lPgNum = 0;    /* ÿ�����ļ�����¼�� */
    /* long lLsxh = 0;     ��ˮ��� */
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
    
    /*�����ύ����WHERE����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSjtjExpWhere, 0x00, sizeof(sSjtjExpWhere));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_EXPWHERE, sBuf)
    if (sBuf[0] == '\0')
    {/*WHERE����Ϊ��,δ�����������*/
        snprintf(sSjtjExpWhere, sizeof(sSjtjExpWhere), "AND shzt !='1' AND clzt='9' ");
    }else
    {
        snprintf(sSjtjExpWhere, sizeof(sSjtjExpWhere), "%s", StrReplace(sBuf, "#", "'"));
    }
    
    LOG(LM_DEBUG,Fmtmsg("BATCH: �ļ�����[%s]�������ļ���¼������[%d],expwhere[%s]", 
        sFileType, lPgNum, sSjtjExpWhere ),"DEBUG");

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

    if( strlen( sFileBasicName ) < 1 ) 
    {
        if( lPgNum > 0 )  /* �ļ���Ҫ��� */
            snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                        "%s_%s_%s_%d.req", sYwbh, sPkrq, sPtpch, iFileCount );
        else /* �ļ�����Ҫ��� */
            snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                "%s_%s_%s.req", sYwbh, sPkrq, sPtpch );
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

    memset( sSqlStr,0x00, sizeof( sSqlStr ) );
    snprintf( sSqlStr, sizeof( sSqlStr ), "SELECT * FROM  batch_filemap\
        WHERE mapid='%s' AND zjszwz > 0 ORDER BY zjszwz",sMapID );

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
    /*  clzt:9 δ���� cgbz:0 �ɹ���1 ���ֳɹ�  ���״̬ 1 ���ʧ��  */
    if(0 == memcmp(sGetFlag, BATCH_MXTJBZ_NONPROC_FAIL ,1 ))  /* �ύδ�������ʧ����ϸ */
    {
        snprintf(sCondStr, sizeof( sCondStr ), "ywbh='%s' AND shzt !='1' \
            AND (clzt='9' OR ( cgbz<>'0' AND cgbz <> '1' ) ) ", sYwbh);
    }
    else /* �ύ������δ������ϸ */
    {
        snprintf(sCondStr, sizeof( sCondStr ),"pkrq='%s' AND ptpch='%s' %s ", sPkrq, sPtpch, sSjtjExpWhere ); 
    }

    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );

    /* modified by yangdong 20130201 ��gaps4.1�У����ܻ�����oracle��-600��
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT lsxh as pnxh,%s FROM %s WHERE %s ORDER BY lsxh"\
                      ,sColStr, sTableName, sCondStr );
    */
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT trim(lsxh) as pnxh,%s FROM %s WHERE %s ORDER BY lsxh", \
        sColStr, sTableName, sCondStr );

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
        LOG(LM_STD,Fmtmsg("BATCH:����Ҫ�ύ���Ĵ�����ϸ"),"WARNING");
        fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"BATCH:����Ҫ�ύ���Ĵ�����ϸ");
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
        LOG(LM_DEBUG,Fmtmsg("BATCH: �����ļ�д��[%d][%d][%s]",\
                iFileNum,length,outbuf),"ERROR");
        */
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
                /* �ļ���Ĭ�ϣ�ҵ���ţ��������ڣ����κ�+�ļ����.req */
                snprintf( sFileParsedName,sizeof( sFileParsedName ),\
                    "%s_%s_%s_%d.req", sYwbh, sPkrq, sPtpch, iFileCount );
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

    COMP_HARDCOPYXML(XMLNM_BATCH_RUNCTRL_CPDM,XMLNM_BATCH_SJTJ_CPDM);
    COMP_HARDCOPYXML(XMLNM_BATCH_REQ_YWBH,XMLNM_BATCH_SJTJ_YWBH);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:BATCH_SJTJ_WAIT
�������: BATCH_SJTJ_WAIT
�������: ����ҵ�������ύ�ļ���ȴ�ʱ��
�������:
 ��� ��������  ��������      ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT BATCH_SJTJ_WAIT(HXMLTREE lXmlhandle)
{
    int  iParas,iResult;
    char sBuf[128];
   /* int  iFileNum = 0;       �ļ��ڼ�¼�� */
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
�����������:BATCH_SJTJ_TIME_CTRL
�������: BATCH_SJTJ_TIME_CTRL
�������: ����ҵ�������ύҹ������ʼʱ����ж�
�������:
 ��� ��������  ��������      ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
ʹ������:
�� �� Ա: yerong
��������:
�޸�����:
����ʹ��ʾ��:
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
    /* ��������ִ�е�,���ػ����̽��д��� */
    if ( ret == -1 )
    { 
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_WAIT);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL );
        return COMPSTATUS_FAIL;
    }
    if( ret==-2 )
    {   /* ʧ��,����������ִ�� */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;              
}
