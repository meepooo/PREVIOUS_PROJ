/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_SJCT.c
�ļ�����: ����ҵ�����ļ�ӳ��-�������ᴦ��ת�������
�� Ŀ ��:�м�ҵ��ƽ̨��Ŀ��
�� �� Ա:yangdong
��������:20110801
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
        <sonote>BATCH���������������</sonote>\
        <version>\
        <rec ver=\"4.1.0.1\" modify=\"2016-07-11 10:08\" programer=\"tuql\" filesize=\"1291580\">�����������</rec>\
        </version>\
        </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if (strlen(sversion) >= isize)
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
�����������:SBATCH_SJCT
�������:BATCH_SJCT
�������:��������
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
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
    int iFileLen = 0;  /*�ļ����ݳ���*/
    char sCondStr[256];   /* ���������ַ��� */
    char sColStr[1024];    /* �����ļ��������� */
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

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    COMP_PARACOUNTCHKMIN(6)
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sTableName,0,sizeof(sTableName));
    COMP_GETPARSEPARAS(1,sBuf,"ҵ�����")
    pstrcopy(sTableName,sBuf,sizeof(sTableName));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileBasicName,0,sizeof(sFileBasicName));
    COMP_GETPARSEPARAS(2,sBuf,"�����ļ���")
    pstrcopy(sFileBasicName ,sBuf,sizeof(sFileBasicName)); 
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sMapID,0,sizeof(sMapID));
    COMP_GETPARSEPARAS(3,sBuf,"ӳ���ʶ")
    pstrcopy(sMapID,sBuf,sizeof(sMapID));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileID,0,sizeof(sFileID));
    COMP_GETPARSEPARAS(4,sBuf,"�����ļ���ʶ")
    pstrcopy(sFileID,sBuf,sizeof(sFileID));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileType,0,sizeof(sFileType));
    COMP_GETPARSEPARAS(5,sBuf,"�����ļ�����")
    pstrcopy(sFileType,sBuf,sizeof(sFileType));

    memset(sBuf,0,sizeof(sBuf));
    memset(sGenFlag,0,sizeof(sGenFlag));
    COMP_GETPARSEPARAS(6,sBuf,"�����־")
    pstrcopy(sGenFlag,sBuf,sizeof(sGenFlag));
    
    /* �������� */
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YPKRQ,sPkrq);
    trim(sPkrq);

    /* ����ҵ���� */
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbh,0,sizeof(sYwbh));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    pstrcopy(sYwbh,sBuf,sizeof(sYwbh)); 
    
    /* ƽ̨���κ� */
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YPTPCH,sPtpch);
    trim(sPtpch);

    /* �����ļ�·��1  */
    memset(sFilePath,0,sizeof(sFilePath));
    COMP_SOFTGETXML( XMLNM_BATCH_REQ_LOCALPATH,sFilePath );
    trim(sFilePath);

    /* �����ļ�·��2  */
    memset(sFilePath2,0,sizeof(sFilePath2));
    COMP_SOFTGETXML( XMLNM_BATCH_SJHP_FILEDIR,sFilePath2 );
    trim(sFilePath2);

    LOG(LM_DEBUG,Fmtmsg("BATCH: �����־[%s] �ļ���ʶ[%s] �ļ���[%s] ԭ��������[%s] ԭ���κ�[%s]",\
        sGenFlag, sMapID, sFileBasicName, sPkrq, sPtpch  ),"DEBUG");

    /* �ļ���Ĭ�ϣ�ҵ���ţ��������ڣ����κ� */
    if( strlen( sFileBasicName ) < 1 )
    {
        if( sGenFlag[0] == '3' )  /* ʧ���ļ���Ĭ�ϼ�_f */
            snprintf( sFileBasicName, sizeof( sFileBasicName ),\
                "CT_%s_%s_%s_f", sYwbh, sPkrq, sPtpch );
        else 
            snprintf( sFileBasicName, sizeof( sFileBasicName ),\
               "CT_%s_%s_%s", sYwbh, sPkrq, sPtpch );
    }

    if( strlen( sGenFlag ) < 1 )
        strcpy( sGenFlag,"1" );  /* Ĭ�������־ 1 ����ȫ����ϸ  */

    /* ��װ�����ļ���Ҫ�����ַ��� */
    /* ����ӳ�����ã�ȡ��Ҫ������ֶ� */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM  batch_filemap\
        WHERE mapid ='%s' AND lylx='1' order by to_number(lywz) ",sMapID  );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    /* ȥ���һ�� , */
    sColStr[strlen( sColStr ) - 1 ] = '\0';
    /* ����Ƿ������ⲿ�ļ�ӳ�� */
    if( iTotalNum < 1 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJHP_PZNULL,MSG_BATCH_SJHP_PZNULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: colstr[%s] genflag[%s]", sColStr,sGenFlag ),"DEBUG");

    /* ����������װ */
    /* �����־     0 ����������ϸ
                    1 ������ȫ����ϸ
                    2 �����γɹ���ϸ
                    3 ������ʧ����ϸ
                    4 �ֱ����ɱ����ɹ�ʧ����ϸ */
    /* �ɹ���־ 0 �ɹ� 1 ���ֳɹ� 2 ʧ�� */
    memset(sSqlStr, 0, sizeof(sSqlStr));
    if( strcmp( sGenFlag, BATCH_ATTRIBUTE_MXHPBZ_SUCC ) == 0 ) /*�ɹ���ϸ*/
    {
        snprintf(sCondStr, sizeof( sCondStr ), " pkrq='%s' AND ptpch='%s' \
            AND ( cgbz='0' OR cgbz='1' ) ", sPkrq,sPtpch);        
    }
    else if( strcmp( sGenFlag, BATCH_ATTRIBUTE_MXHPBZ_FAIL ) == 0 ) /*ʧ����ϸ*/
    {
        snprintf(sCondStr,sizeof( sCondStr ), " pkrq='%s' AND ptpch='%s'\
            AND ( cgbz !='0' AND  cgbz != '1' ) ", sPkrq, sPtpch);        
    }
    else if( strcmp( sGenFlag, BATCH_ATTRIBUTE_MXHPBZ_ALLDATA ) == 0 ) /*ȫ��������ϸ*/
    {
        snprintf(sCondStr,sizeof( sCondStr ), " 1=1 ");        
    }
    else  /* Ĭ�����ɱ�����������ϸ */
    {
        snprintf(sCondStr, sizeof( sCondStr ),\
            " pkrq='%s' AND ptpch='%s'", sPkrq, sPtpch); 
    }
        
    /* �ļ����ܷ���ӳ�������ʼ�� */
    if( strcmp( sFileType,"01" ) != 0 )  /* �ǵ���ϸ */
    {
        iTSortCount=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_TOTAL,&t_fileTotalSortList );
        if ( iTSortCount <= 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH:���ܷ����ʼ��ʧ��,[%s]",sFileID),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /* �ļ���ϸ���������ʼ�� */
    iResult=fprv_initFileSort(sFileID,BATCH_FILESORT_TYPE_S_DETAIL, &t_fileDetailSortList);
    if ( iResult != 1 ) /* ֻ��һ����ϸ���� */
    {
        LOG(LM_STD,Fmtmsg("BATCH: ��ϸ�����ʼ��ʧ��,[%s] iResult[%d]",sFileID, iResult ),"ERROR");
        batch_totalsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
            Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ȡ��ϸ������Ϣ ��������ȡ��һ��������Ϣ���˳�����Ĭ��ֻ��һ����ϸ���� */
    memset(&thisSort, 0x00, sizeof(BATCH_FILESORT) );
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* �ļ�����Ϣ�����ʼ�� */
    iResult=fprv_initFileColumn(sFileID,&t_fileColumnList );
    if ( iResult <= 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: �ļ�����Ϣ��ʼ��ʧ��,[%s]",sFileID),"ERROR");
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
                               Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileID));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* �ļ�ӳ����Ϣ�����ʼ�� */
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

    /* �����ļ�������( ������Ϣ���Դ�xml�ڵ��� ) */
    if( strlen( sFileBasicName ) > 2 )
    {
        LOG(LM_DEBUG,Fmtmsg("BATCH: �����ļ����ƽ���,[%s]=>",sFileBasicName ),"DEBUG")
        /* �Ƚ���XML���� */
        if(xml_ParseXMLString(lXmlhandle,sFileBasicName,sizeof(sFileBasicName))==FAIL)
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,\
                Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ʼ���������ļ�[%s][%s]", sFilePath, sFileBasicName ),"DEBUG");
    /* �ļ�·������ */
    memset(sFileFullName, 0x00, sizeof(sFileFullName));
    if ( strlen(sFilePath) > 0 )
    {
        snprintf( sFileFullName, sizeof( sFileFullName ), "%s/%s",sFilePath, sFileBasicName );
    }else
    {
        if( sFilePath2[0] != '/' ) /* ���·����ȡĬ���ļ�·�� */
        {
            snprintf( sFileFullName, sizeof( sFileFullName ),\
                     "%s/%s/%s", getenv("HOME"), sFilePath2, sFileBasicName  );
        }
        else
        {
            snprintf( sFileFullName, sizeof( sFileFullName ), "%s/%s",sFilePath2, sFileBasicName );
        }
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ʼ���������ļ�[%s]type[%s]", sFileFullName,sFileType ),"DEBUG");

    /* ͳ�ƺ���ʵ�ʽ��׽�� */
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

    /* �����ļ�����ʼ */
    if((destfp = fopen(sFileFullName, "w")) == NULL)
    {
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        LOG(LM_STD,Fmtmsg("BATCH: ���ļ�[%s]ʧ��",sFileFullName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    /* ����ͷ�Ļ�����Ϣ */
    if( strcmp( sFileType,"02" ) == 0 ||   /* �����ܵ���ϸ */
        strcmp( sFileType,"04" ) == 0 )    /* ����ܵ���ϸ */
    {
        /* �������ܷ��࣬һ�����ܷ��ദ��һ�м�¼,��Ҫ���ñ�֤���ܷ����˳��ƥ���ļ� */
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

    /* ������Ҫ���������ļ� */
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT lsxh AS bat_pnxh, %s FROM %s WHERE %s \
        ORDER BY bat_pnxh",sColStr, sTableName, sCondStr );
    LOG(LM_DEBUG,Fmtmsg("BATCH: ��������[%s]", sSqlStr ),"DEBUG");
    memset(sTmpFileName,0,sizeof(sTmpFileName));
    snprintf(sTmpFileName, sizeof( sTmpFileName ),\
             "%s/tmp/batch_sjct_tmp%s.%s", getenv("HOME"), sPkrq, sPtpch );
    if( sql_UnloadToFile(sTmpFileName,sSqlStr,'^','\\',&lRCount)!=MID_SYS_SUCC )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�����ļ�����ʧ��,[%s]",sSqlStr),"ERROR");
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fclose( destfp );
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJHP_UNLOAD,MSG_BATCH_SJHP_UNLOAD );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* �򿪵����ļ����� */
    if((srcfp = fopen(sTmpFileName, "r")) == NULL)
    {
        LOG(LM_STD,Fmtmsg("BATCH: ���ļ�����ʧ��,[%s]",sTmpFileName),"ERROR");
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fclose( destfp );
        fpub_SetMsg(lXmlhandle,MID_BATCH_SJHP_UNLOAD,MSG_BATCH_SJHP_UNLOAD );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ������ϸ��Ϣ */
    index=0;
    dTotalAmt=0.00;
    memset(linebuf, 0, sizeof(linebuf));
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL    )
    {
        /* ����Ϣ���� */
        if( 13 == linebuf[0] || 10 == linebuf[0] || 0 == linebuf[0] )
        {
            continue;
        }

        index ++;
        memset(outbuf, 0, sizeof(outbuf));
        iResult=detailProc_write(lXmlhandle, &iLsxh, linebuf,&dTotalAmt,outbuf,&thisSort,t_fileColumnList);
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��ϸ��Ϣ����ʧ��,[%s] [%d] [%s]",\
                linebuf,index,thisSort.classname),"ERROR");
            iAbort=4;
            break;
        }
        length=strlen(outbuf);
        outbuf[length] = '\n';
        iResult=fwrite( outbuf, length+1, 1, destfp);
        if( iResult < 0)
        {
            LOG(LM_STD,Fmtmsg("BATCH: �ļ�д��ʧ��,[%d],[%d],[%s]",\
                iResult,index,strerror(errno)),"ERROR");
            iAbort=7;
            break;
        }

        memset(linebuf, 0x00, sizeof(linebuf));
    }

    /* �������Ļ�����Ϣ */
    if( strcmp( sFileType,"03" ) == 0 ||   /* �����ܵ���ϸ */
        strcmp( sFileType,"04" ) == 0 )    /* ����ܵ���ϸ */
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

    /* �ͷ�������Դ  */
    batch_totalsortlistFree();
    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_maplistFree();

    /* �����쳣 */
    if( iAbort )
    {
        LOG(LM_STD,Fmtmsg("BATCH: ���������ļ��������: [%d]",iAbort),"ERROR");
        unlink(sFileFullName);
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,MSG_SYS_COMPEXEC);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPSTATUS_FAIL;
    }

    /* �����ļ���Ϣ */
    /* �ļ��ڱ��� */
    COMP_SOFTSETXML( XMLNM_BATCH_REQ_ZBS, itoa( iTotalNum ) );
    /* �ļ��ڽ��׽�� */
    sprintf( sBuf, "%.2f", dTotalAmt );
    COMP_SOFTSETXML(  XMLNM_BATCH_REQ_ZJE, sBuf );

    LOG(LM_DEBUG,Fmtmsg("BATCH:��������,�ļ�����[%s],�ܱ���[%d],�ܽ��[%.2f]",\
        sFileBasicName,iTotalNum,dTotalAmt),"DEBUG")

    /*�ļ���ʽ*/
    memset(sFileTypeReal, 0x00, sizeof(sFileTypeReal));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILETYPE, sFileTypeReal)
    /*�ļ������ʽ*/
    memset(sCodeFmt, 0x00, sizeof(sCodeFmt));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_CODEFMT, sCodeFmt)
    LOG(LM_STD,Fmtmsg("BATCH: ��������ת�������ʽ,�ļ�����[%s] �ļ���ʽ[%s] �����ʽ[%s]", 
        sFileTypeReal, sFileType, sCodeFmt ),"INFO")
    if ( sFileTypeReal[0] == '0')
    {/*0-�ı���ʽ,����Ҫת��*/
        if ( sCodeFmt[0] == '1')
        {/*1-UTF-8��ʽ*/
            iRet=fpub_convFileFmt(sFileFullName, &iFileLen, 1);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: �ļ������ʽ[%s]ת��ʧ��[%d] ", "UTF-8", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "UTF-8"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }else if ( sCodeFmt[0] == '2')
        {/*2-BASE64��ʽ*/
            iRet=fpub_convFileFmt(sFileFullName, &iFileLen, 3);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: �ļ������ʽ[%s]ת��ʧ��[%d] ", "BASE64", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "BASE64"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }
    }

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
