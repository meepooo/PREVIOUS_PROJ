/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_SJRK.c
�ļ�����: ����ҵ�����ļ�ӳ��-������⴦��ת�������
�� Ŀ ��:�м�ҵ��ƽ̨��Ŀ��
�� �� Ա:YangDong
�޸�����:2011-8-1

�� �� Ա:YangDong
�޸�����:2014-10-18
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
        <sonote>BATCH��������������</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"YangDong\" filesize=\"1128297\">HS-AgentV2.1����</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1128297\">DCI����</rec>\
        <rec ver=\"4.1.0.2\" modify=\"2016-08-10 13:08\" programer=\"Tuql\" filesize=\"1128297\">���Ӷ�����������ַ��ļ��</rec>\
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

IRESULT sql_LoadFromFile_b(char* sFilename, char *sTname, char cDiv, char cEscape, long *lResult);

/*
 * ��ȡ�ļ���������Ϣ
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
            /* �ҵ���������(��Դ�ļ�λ��=�����) */
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

/* ���ܴ��� */
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

    /* �����β�Ļ��лس� */
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
    /* ȡ���ܷ������������Ϣ���д��� */
    for( pfileColumnIter = i_list_begin(t_fileColumnList); 
                 pfileColumnIter!= i_list_end(t_fileColumnList); 
                     pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        memset(sTmpStr, 0, sizeof(sTmpStr));          
        if( pFileSort->fileclasssn == gSFileColumn->fileclasssn ) /* ֻ������ܷ��� */
        {
            iLineField ++;
            switch( pFileSort->columnflag[0] )
            {
                case BATCH_FILESORT_COLUNM_FIX:    /* ���� */
                    memcpy(sTmpStr, lineBuf+gSFileColumn->offset-1,gSFileColumn->columnlen);
                    break;
                case BATCH_FILESORT_COLUNM_SPLIT_TAIL: /* ȥβ�ָ��� */

                case BATCH_FILESORT_COLUNM_SPLIT: /* �ָ��� */
                    trim(pFileSort->columnsprtr);
                    if( pFileSort->columnsprtr[0] == 0 )
                    {
                        fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
                            Fmtmsg("BATCH: �Ƿ��ָ���[%s]", pFileSort->columnsprtr) );
                        LOG(LM_STD,Fmtmsg("BATCH: �Ƿ��ָ���[%s]", pFileSort->columnsprtr ),"ERROR")
                        return -1;
                    }
                    
                    fprv_getSubStr(lineBuf, gSFileColumn->columnsn, pFileSort->columnsprtr, sTmpStr);
                    break;
                default:  
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
                            Fmtmsg("BATCH: �зָ��ʶ�Ƿ�[%s]", pFileSort->columnflag) );
                    LOG(LM_STD,Fmtmsg("BATCH: �зָ��ʶ�Ƿ�[%s]", pFileSort->columnflag),"ERROR")
                    count=-1;
                    return count;
            }

            if( gSFileColumn->izoom != 0 )  /* �����ƫ��,����ƫ�ƺ���ֵ */
            {
                dTmp=atof(sTmpStr)*pow(10,-gSFileColumn->izoom);
                if( gSFileColumn->iprecision < 1 )
                    gSFileColumn->iprecision = 2;  /* Ĭ��С������2 */
                sprintf(sFmt,"%%.%df",gSFileColumn->iprecision);
                snprintf(sTmpStr, sizeof( sTmpStr ), sFmt,dTmp);
            }
             /* ��������ַ� */
            if ( gSFileColumn->ifiller > 0 && gSFileColumn->columnlen > 0 )  
            {
                memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
                strcpy( tmpBuf, sTmpStr );
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
                    memset( sTmpStr, 0x00, sizeof( sTmpStr ) );
                    memcpy( sTmpStr, tmpBuf+position, gSFileColumn->columnlen - position );
                    sTmpStr[ gSFileColumn->columnlen -  position] = '\0';
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
                    memset( sTmpStr, 0x00, sizeof( sTmpStr ) );
                    memcpy( sTmpStr, tmpBuf, position );
                    sTmpStr[position] = '\0';
                }
                else /* �����ö��뷽ʽ */
                {
                    j = 0;
                    for( i = 0; i<= gSFileColumn->columnlen; i++ )
                    {
                         /* ���ҷ�����ַ� */
                         if( tmpBuf[i] != gSFileColumn->ifiller )
                         {
                             sTmpStr[j++]= tmpBuf[i] ; 
                         }
                    } 
                    sTmpStr[j] = '\0';
                }
            }

            /* ���������� */
            if( ( 0 != gSFileColumn->lsx[0] ) && strlen(gSFileColumn->lsx) ) 
            {
                if( strcmp(gSFileColumn->lsx,BATCH_FILECOLUMN_LSX_SETXML) == 0) /* �����ԣ�����xml*/
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
                else if( strcmp(gSFileColumn->lsx, BATCH_FILECOLUMN_LSX_ZBS) == 0) /* �����ԣ��ܱ��� */
                {
                    COMP_SOFTSETXML(XMLNM_BATCH_HZ_ZBS,sTmpStr);        
                    LOG(LM_STD,Fmtmsg("BATCH: �����ļ��ܱ���[%s]",sTmpStr),"INFO")
                }
                else if( strcmp(gSFileColumn->lsx, BATCH_FILECOLUMN_LSX_ZJE) == 0) /* �����ԣ��ܽ�� */
                {
                    if ( strlen(sTmpStr) >= 15)
                    {
                        fpub_SetMsg(lXmlhandle,MID_BATCH_SJRK_SUMAMT,Fmtmsg(MSG_BATCH_SJRK_SUMAMT) );
                        LOG(LM_STD,Fmtmsg("BATCH: �ļ�����ʧ��(���ܽ���)[%s]",sTmpStr),"ERROR")
                        count=-2;
                        return count; 
                    }
                    COMP_SOFTSETXML(XMLNM_BATCH_HZ_ZJE,sTmpStr);        
                    LOG(LM_STD,Fmtmsg("BATCH: �����ļ��ܽ��[%s]",sTmpStr),"INFO")
                }
                else if( strcmp(gSFileColumn->lsx, BATCH_FILECOLUMN_LSX_SHPCH ) == 0) /* ������ �̻����κ� */
                {
                    COMP_SOFTSETXML(XMLNM_BATCH_REQ_SHPCH,sTmpStr);        
                    LOG(LM_STD,Fmtmsg("BATCH: �����ļ��̻����κ�[%s]",sTmpStr),"INFO")
                }
                else
                {
                    fpub_SetMsg(lXmlhandle,MID_BATCH_PROCLINE_NOTNULL,
                            Fmtmsg("BATCH: �����ԷǷ�[%s]", gSFileColumn->lsx) );
                    LOG(LM_STD,Fmtmsg("BATCH: �����ԷǷ�[%s]",gSFileColumn->lsx),"ERROR")
                    count=-2;
                    return count;         
                }
            }           
            /* ����ǿ� */
            if ( gSFileColumn->isid[0] == '1' && sTmpStr[0] == '\0')
            {
                LOG(LM_STD,Fmtmsg("BATCH: ���ܵ�[%d-%s]����ǿ�Ϊ��[%s]",
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
        LOG(LM_STD,Fmtmsg("BATCH: ��������������,����%d��,ʵ��%d��,[%s]",
            iLineField, iSplitLine, lineBuf),"ERROR")
        count=-2;
        return count;
    }
    
    return count;
}

/* ��ϸ����(���ñ�֤ע�����ӳ��������һ����) */
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
    /* Ĭ�� �����32��,ÿ���ֶ��128���ַ� */
    char sss[ BATCH_MAX_FILE_COL_NUM ][ BATCH_MAX_FILE_COL_LEN ];
    char *p=&sss[0][0];

    BATCH_FILECOLUMN thisColumn;

    /* �����β�Ļ��лس� */
    iLen = strlen( inBuf );
    if( inBuf[iLen-1] == 10 || inBuf[iLen-1] == 13    )
        inBuf[iLen-1] = '\0';
    if( inBuf[iLen-2] == 10 || inBuf[iLen-2] == 13    )
        inBuf[iLen-2] = '\0';

    /*�ȶ���ϸ���������,Ҫ���������ȫ����һ��*/
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

    /* ȡ���ܷ������������Ϣ���д��� */
    for( pfileColumnIter = i_list_begin(t_fileColumnList); 
                 pfileColumnIter!= i_list_end(t_fileColumnList); 
                     pfileColumnIter = i_list_iter_next(pfileColumnIter) )
    {
        gSFileColumn = (BATCH_FILECOLUMN *)(pfileColumnIter->data);
        memset(sTmpStr, 0, sizeof(sTmpStr));          
        if( pFileSort->fileclasssn == gSFileColumn->fileclasssn ) /* ֻ������ϸ���� */
        {
            iLineField ++;
        }
    }
    if (iSplitLine>0 && iLineField != iSplitLine && sCheckFlag[0]=='1')
    {
        LOG(LM_STD,Fmtmsg("BATCH: ��ϸ����������,����%d��,ʵ��%d��,[%s]",
            iLineField, iSplitLine, inBuf),"ERROR")
        iIsDetailCnts = iSplitLine;
    }
    
    /* �ָ���ģʽ���Ȱ��ļ�������ȫ����������ʱ��������� */   
    if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT ||
        pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL ) /* ȥβ�ָ��� */
    {
        memset( &sss, 0x00, BATCH_MAX_FILE_COL_NUM * BATCH_MAX_FILE_COL_LEN);
        trim( pFileSort->columnsprtr );
        if( pFileSort->columnsprtr[0] == 0 )
        {
           LOG(LM_STD,Fmtmsg("BATCH: �Ƿ��ָ���[%s]", pFileSort->columnsprtr ),"ERROR")
           return -1; 
        }
        fprv_GetAllSubstr( p, inBuf, pFileSort->columnsprtr, &iTmp );
    }

    /* �ļ�ӳ����� */
    for( pfileMapIter = i_list_begin(t_fileMapList); 
             pfileMapIter != i_list_end(t_fileMapList); 
             pfileMapIter = i_list_iter_next(pfileMapIter) )
    { 
        /* ȡ �ļ�ӳ������ ��ӳ����Ϣ */
        gSFileMap = (BATCH_FILEMAP *)(pfileMapIter->data);
        memset(fldCont, 0, sizeof(fldCont));
/*
LOG(LM_DEBUG,Fmtmsg("columnid[%s] ", gSFileMap->columnid),"INFO");
LOG(LM_DEBUG,Fmtmsg("lylx[%s] ", gSFileMap->lylx ),"INFO");
*/
        switch( gSFileMap->lylx[0] )
        {
            case BATCH_FILEMAP_LYLX_FILE:    /* �����ļ� */
                /* ��ȡ����Ϣ */
                memset(&thisColumn, 0, sizeof(thisColumn));
                ret=getFileColumn(&thisColumn,gSFileMap,pFileSort);
                if( ret <= 0)
                {
                    LOG(LM_STD,Fmtmsg("BATCH: �޶�Ӧ������Ϣ[%s]",gSFileMap->lywz),"ERROR")
                    return -6;
                }
                trim(thisColumn.lsx);
                trim(thisColumn.fldref);
                if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_FIX )          /* ���� */
                {
                    memset(itemBuf,0,sizeof(itemBuf));
                    memcpy(itemBuf,inBuf+thisColumn.offset-1,thisColumn.columnlen);
                    if( thisColumn.izoom != 0 )
                    {
                        dTmp=atof(itemBuf)*pow(10,-thisColumn.izoom);
                                               
                        if( thisColumn.iprecision < 1 )
                            thisColumn.iprecision = 2;  /* Ĭ��С������2 */
                        sprintf(sFmt,"%%.%df",thisColumn.iprecision);
                        snprintf(itemBuf,sizeof( itemBuf ),sFmt,dTmp);
                    }
                }
                else if( pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT ||    /* �ָ�� */
                         pFileSort->columnflag[0] == BATCH_FILESORT_COLUNM_SPLIT_TAIL ) /* ȥβ�ָ��� */
                {
                    memset(itemBuf,0,sizeof(itemBuf));
                    snprintf( itemBuf, sizeof( itemBuf ), "%s", sss[atoi(gSFileMap->lywz) - 1 ]);
                    if( thisColumn.izoom != 0 ) /* ��ƫ�ƣ���Ҫ���� */
                    {                            
                        dTmp=atof(itemBuf)*pow(10,-thisColumn.izoom);
                        memset(sFmt,0,sizeof(sFmt));
                        if( thisColumn.iprecision < 1 )
                            thisColumn.iprecision = 2;  /* Ĭ��С������2 */
                        sprintf(sFmt,"%%.%df",thisColumn.iprecision);
                        memset(itemBuf, 0,sizeof(itemBuf));
                        snprintf(itemBuf, sizeof( itemBuf ), sFmt,dTmp);
                    }
                    /* �ָ���ģʽ���������ֶγ��ȣ�ҲҪ�жϳ��ȡ������ַ�������ȡ */
                    if( thisColumn.columnlen > 0 )
                    {
                        itemBuf[thisColumn.columnlen] = '\0';
                    }
                }
                else
                {
                    LOG(LM_STD,Fmtmsg("BATCH: �зָ��ʶ�Ƿ�[%s]",pFileSort->columnflag),"ERROR")
                    return -1;
                }

                /* ��������ַ� */
                if ( thisColumn.ifiller > 0 && thisColumn.columnlen > 0 )  
                {
                    memset( tmpBuf, 0x00, sizeof( tmpBuf ) );
                    strcpy( tmpBuf, itemBuf );
                    position = thisColumn.columnlen; 
                    if ( thisColumn.regular[0] == 'R' )   /* �Ҷ��� */
                    {
                        for( i = 0; i<= thisColumn.columnlen; i++ )
                        {
                             /* ������Ч�ַ���ʼλ�� */
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
                    else if ( thisColumn.regular[0] == 'L' )   /* ����� */
                    {
                        for( i = 0; i<= thisColumn.columnlen; i++ )
                        {
                             /* ��������ַ���ʼλ�� */
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
                    else /* �����ö��뷽ʽ */
                    {
                        j = 0;
                        for( i = 0; i<= thisColumn.columnlen; i++ )
                        {
                             /* ���ҷ�����ַ� */
                             if( tmpBuf[i] != thisColumn.ifiller )
                             {
                                 itemBuf[j++]= tmpBuf[i] ; 
                             }
                        } 
                        itemBuf[j] = '\0';
                    }
                }

                snprintf(fldCont, sizeof( fldCont ),"%s^",itemBuf);
                if( strcmp(thisColumn.lsx,BATCH_FILECOLUMN_LSX_SETXML) == 0) /* �����ԣ�set XML */
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
                else if( strcmp(thisColumn.lsx,BATCH_FILECOLUMN_LSX_ADD) == 0)  /* �����ԣ����׽���ۼ�  */
                {
                    dTmp=atof(itemBuf); 
                    *dTotal+=dTmp;         
                }
                else if( strcmp(thisColumn.lsx,BATCH_FILECOLUMN_LSX_SUB) == 0) /* �����ԣ����׽���ۼ� */
                {
                    dTmp=atof(itemBuf); 
                    *dTotal-=dTmp;         
                }
                trim(itemBuf);                
                /*���Ӷ���ǿ�Ϊ���ж�*/
                if (thisColumn.isid[0] == '1' && itemBuf[0] == '\0')
                {/*����ǿ�Ϊ��,��������Ӧ�롢��Ӧ��Ϣ���ɹ���־*/
                    iIsId = atoi(gSFileMap->lywz);
                    memset(sIsIdFildName, 0x00, sizeof(sIsIdFildName));
                    pstrcopy(sIsIdFildName, thisColumn.columnid, sizeof(sIsIdFildName));
                }

                /*add by tuql 20160810 ���Ӷ�����������ַ��ļ�� begin*/
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
                            LOG(LM_STD,Fmtmsg("888887799-->���а��������ַ�[%d-%s][%d-%s]",iIsId2, sIsIdFildName,iSpeChar,sTmpStr),"ERROR");
                    
                            break;
                        }
                    }
                }

                break;

            case BATCH_FILEMAP_LYLX_XML:    /* XML��ȡ */
                trim(gSFileMap->lywz);
                memset(itemBuf, 0, sizeof(itemBuf));
                COMP_SOFTGETXML(gSFileMap->lywz,itemBuf);
                trim(itemBuf);
                snprintf(fldCont, sizeof( fldCont), "%s^",itemBuf);
                break;
                
            case BATCH_FILEMAP_LYLX_SEQ:    /* ��ˮ���  */
                snprintf(fldCont, sizeof( fldCont ),  "%d^",cycNum);
                break;
            
            case BATCH_FILEMAP_LYLX_CONST:    /* ���� */
                trim(gSFileMap->lywz);
                snprintf(fldCont, sizeof( fldCont ),  "%s^",gSFileMap->lywz);
                break;
                
            case BATCH_FILEMAP_LYLX_WJSEQ:   /* �ļ���� */
                snprintf(fldCont, sizeof( fldCont ),  "%d^",iWjxh );
                break;

            case BATCH_FILEMAP_LYLX_ZHQZLSH:    /* �ۺ�ǰ����ˮ�� */
                /* ��������ˮ��  */
                ret =fpub_ExGenLSerialno(lXmlhandle, XMLNM_ZHQZLSH , 1 );
                if( ret != MID_SYS_SUCC )
                {
                    LOG(LM_STD,Fmtmsg("�����µ��ۺ�ǰ����ˮ��ʧ�ܣ�ret[%d]",ret),"ERROR");
                    return -2;
                }
                COMP_SOFTGETXML( XMLNM_ZHQZLSH, itemBuf )
                snprintf(fldCont, sizeof( fldCont), "%s^",itemBuf);
                break;

            default:
                snprintf(fldCont, sizeof( fldCont ),  "%s^","");
                break;
        }

        /* �������(�ⲿҪ��֤�������) */
        if ( strcmp(gSFileMap->columnid, "clzt") == 0 )
        {/*�����־*/
            if ( iIsId > 0 || iIsDetailCnts > 0 || iSpeChar > 0)
            {   
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^","1");
            }
        }
        if ( strcmp(gSFileMap->columnid, "cgbz") == 0 )
        {/*�ɹ���־*/
            if ( iIsId > 0 || iIsDetailCnts > 0 || iSpeChar > 0)
            {
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^",BATCH_CGBZ_S_FAIL);
            }
            
        }
        if ( strcmp(gSFileMap->columnid, "xym") == 0 )
        {/*��Ӧ��*/
            if ( iIsId > 0 || iIsDetailCnts > 0 || iSpeChar > 0)
            {
                memset(fldCont, 0x00, sizeof(fldCont));
                snprintf(fldCont, sizeof( fldCont ),  "%s^",itoa(MID_BATCH_PROCLINE_NOTNULL));
            }
        }
        if ( strcmp(gSFileMap->columnid, "xyxx") == 0 )
        {/*��Ӧ��Ϣ*/
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

/*add by tuql 20160711 �����ֹ�¼��������ϸ�Ĵ���*/
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return -1;
    }
    /* ����ʵ���ܱ��� */
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZBS, sLrzbs);
    iHZbs=atoi(sLrzbs);
    /* ����ʵ���ܽ�� */
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZJE, sLrzje);
    if (sLrzje[0] == '\0') sLrzje[0]='0';
    dHZje=atof(sLrzje);
    LOG(LM_STD,Fmtmsg("BATCH: �ֹ���� ʵ���ܱ���[%s]ʵ���ܽ��[%s]", sLrzbs,sLrzje),"INFO")
    
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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
        /* �ܱ������� */
        if( abs(iHZbs - iLrzbs) > 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ¼���ܱ���[%d]����ϸ[%d]����",iLrzbs,iHZbs),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZBS_MXZBS,Fmtmsg(MSG_BATCH_LRZBS_MXZBS,iLrzbs,iHZbs));        
            return -3;
        }
        /* �ܽ��� */
        if( fabs(dHZje - dLrzje) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ¼���ܽ��[%f]����ϸ�ܽ��[%f]����",dLrzje,dHZje),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZJE_MXZJE,Fmtmsg(MSG_BATCH_LRZJE_MXZJE,dLrzje,dHZje));
            return -4;
        }
    }

    return 0;
}
/************************************************************************
��̬�����������
�����������:SBATCH_SJRK
�������:BATCH_SJRK
�������: 
�������:
 ��� ��������    ��������                 ��Դ���         ȱʡֵ    �ɿ�    ����˵��        
    1     1-����     �ļ���            416XML�����ַ���    *            N        
    2     1-����     �ļ���ʶ        416XML�����ַ���    *            N        
    3     1-����     ӳ���ʶ        416XML�����ַ���    *            N        
    4     1-����     ҵ�����        416XML�����ַ���    *            N        
 
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
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
 
    int iClassPre = 0;    /* ��һ������� */
    int  iRearClass = 1;
    int ii =0, index = 0;
    int iWjxh = 1;
    int lPgNum = 0;    /* ÿ�����ļ�����¼�� */
    int iFileLen = 0;  /*�ļ����ݳ���*/
    char sSjhqfs[1+1];/*���ݻ�ȡ��ʽ*/
    
    fpub_InitSoComp(lXmlhandle);

    memset(sSjhqfs, 0x00, sizeof(sSjhqfs));
    COMP_SOFTGETXML(XMLNM_BATCH_HQSJ_HQSJFS,sSjhqfs)
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ,hqsjfs01=[%s]",fpub_GetCompname(lXmlhandle), sSjhqfs),"DEBUG");
    
    COMP_PARACOUNTCHKMIN(6)
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�ļ���")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJM_NULL,MSG_BATCH_WJM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileName,sBuf,sizeof(sFileName));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�ļ���ʶ")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJBS_NULL,MSG_BATCH_WJBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileId,sBuf,sizeof(sFileId));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"ӳ���ʶ")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YSBS_NULL,MSG_BATCH_YSBS_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sMapId,sBuf,sizeof(sMapId));
    
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
    COMP_GETPARSEPARAS(5,sBuf,"�ļ�����")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJLX_NULL,MSG_BATCH_WJLX_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sFileType,sBuf,sizeof(sFileType));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(6,sBuf,"�����ļ���¼������")
    lPgNum = atol( sBuf );
    
    /*add by tuql 2060711 ��Ϊ������ϸΪ�ֹ�¼�룬��ֱ���жϼ�¼����¼����*/
    if (strcmp(sSjhqfs,BATCH_ATTRIBUTE_HQSJFS_SGLR)== 0)
    {/*�ֹ�¼��*/
        iRet=batch_sjct_sglr(lXmlhandle, sTableName);
        if (iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("�ֹ�������ϸ�ܱ����ܽ������[%d]", iRet), fpub_GetCompname(lXmlhandle));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return iRet;
        }
        LOG(LM_STD,Fmtmsg("�ֹ�¼����ϸ,ִ�н���"),fpub_GetCompname(lXmlhandle));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }

    /*�ļ���ʽ*/
    memset(sFileTypeReal, 0x00, sizeof(sFileTypeReal));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILETYPE, sFileTypeReal)
    /*�ļ������ʽ*/
    memset(sCodeFmt, 0x00, sizeof(sCodeFmt));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_CODEFMT, sCodeFmt)

    LOG(LM_STD,Fmtmsg("BATCH: �ļ���[%s] ", sFileName),"INFO")

    LOG(LM_STD,Fmtmsg("BATCH: �ļ�����[%s] �ļ���ʽ[%s] �����ʽ[%s]", 
        sFileTypeReal, sFileType, sCodeFmt ),"INFO")
    if( sFileName[0] == '~' )  /* ~����HOMEĿ¼ */
    {
         sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName+2 ); 
         strcpy( sFileName, sBuf );
         LOG(LM_DEBUG,Fmtmsg("BATCH: �ļ���[%s] ", sFileName ),"DEBUG")
    }
    else if( sFileName[0] != '/') /* ���·��ʱ */
    {
         sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName ); 
         strcpy( sFileName, sBuf );
         LOG(LM_DEBUG,Fmtmsg("BATCH: �ļ���[%s] ", sFileName ),"DEBUG")
    }
#if 0  
    sprintf( sBuf, "%s/%s" ,getenv("HOME"), sFileName ); 
    strcpy( sFileName, sBuf );
    LOG(LM_DEBUG,Fmtmsg("BATCH: �ļ���[%s] ", sFileName ),"DEBUG")
#endif 
    
    if ( sFileTypeReal[0] == '0')
    {/*0-�ı���ʽ,����Ҫת��*/
        if ( sCodeFmt[0] == '1')
        {/*1-UTF-8��ʽ*/
            iRet=fpub_convFileFmt(sFileName, &iFileLen, 2);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: �ļ������ʽ[%s]ת��ʧ��[%d] ", "UTF-8", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "UTF-8"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }else if ( sCodeFmt[0] == '2')
        {/*2-BASE64��ʽ*/
            iRet=fpub_convFileFmt(sFileName, &iFileLen, 4);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: �ļ������ʽ[%s]ת��ʧ��[%d] ", "BASE64", iRet ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_BATCH_WJGS_CONV,Fmtmsg(MSG_BATCH_WJGS_CONV, "BASE64"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;  
            }
        }
    }
    
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
    
    /* ����ԭ������Ϣ(�����ظ����������) */ 
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_DEL_YWMX,\
            Fmtmsg(MSG_BATCH_DEL_YWMX,-1));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;        
    }
    
    /* ������ʱ�ļ������ڵ������ݿ���ϸ�� */
    memset(sTmpFilePath, 0x00, sizeof(sTmpFilePath));
    iRet = fprv_getBatchFilePath(lXmlhandle,sTmpFilePath, sizeof(sTmpFilePath));
    LOG(LM_STD,Fmtmsg("fprv_getBatchFilePath[%d][%s]",iRet, sTmpFilePath ),"ERROR")
    memset(sTmpFileName, 0, sizeof(sTmpFileName));
    snprintf(sTmpFileName, sizeof( sTmpFileName ),\
        "%s/batch_sjrk_tmp%s.%ld", sTmpFilePath, sPkrq,getpid());
    
    /* ����ϸ���߶���ܶ���ϸ��ʽ������Ҫ�ļ����ܷ���ӳ�������ʼ�� --ԭע��*/
    /* ����ϸ��ʽ������Ҫ�ļ����ܷ���ӳ�������ʼ�� */
    if( strcmp( sFileType,"01" ) != 0 )
    {
        iTSortCount=fprv_initFileSort(sFileId,BATCH_FILESORT_TYPE_S_TOTAL,&t_fileTotalSortList);
        if( iTSortCount <= 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: �ļ����ܷ���ӳ�������ʼ��ʧ��,[%s][%d]",\
                               sFileId,iTSortCount),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                         Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileId));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /* �ļ���ϸ����ӳ�������ʼ�� */
    iResult =fprv_initFileSort(sFileId,BATCH_FILESORT_TYPE_S_DETAIL, &t_fileDetailSortList);
    if( iResult != 1 )  /* ��ϸ�������ҽ���һ�� */
    {
        LOG(LM_STD,Fmtmsg("BATCH: �ļ���ϸ����ӳ�������ʼ��ʧ��,[%s][%d]",\
                           sFileId,iResult ),"ERROR")
        batch_totalsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILESORT_LISTFAIL,\
                          Fmtmsg(MSG_BATCH_FILESORT_LISTFAIL,sFileId));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ȡ��ϸ������Ϣ ��������ȡ��һ��������Ϣ */
    memset(&thisSort, 0, sizeof(BATCH_FILESORT));
    pfileDetailSortIter = i_list_begin(t_fileDetailSortList);
    memcpy( &thisSort,(BATCH_FILESORT *)(pfileDetailSortIter->data),sizeof(BATCH_FILESORT));

    /* �ļ�����Ϣ�����ʼ�� */
    iResult=fprv_initFileColumn(sFileId,&t_fileColumnList);
    if( iResult <= 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:�ļ�����Ϣ�����ʼ��[%s]",sFileId),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        fpub_SetMsg(lXmlhandle,MID_BATCH_FILECOLUMN_LISTFAIL,\
            Fmtmsg(MSG_BATCH_FILECOLUMN_LISTFAIL,sFileId));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* �ļ�ӳ����Ϣ�����ʼ�� */
    iResult=fprv_initFileMap(sMapId,BATCH_STEPNM_SJRK,&t_fileMapList);
    if( iResult <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: �ļ�ӳ����Ϣ�����ʼ��,[%s],[%s]",\
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

    /* ��ȡ�ļ������� rows */
    /* 01 ����ϸ 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
    /* 20110825 �����ļ�����ȡ���� 
    if( strcmp( sFileType,"03" ) == 0 || strcmp( sFileType,"04" ) == 0  ) 
    {
    */
        /* �������ļ� */
        if((fp1 = fopen(sFileName, "r")) == NULL)
        {
            batch_totalsortlistFree();
            batch_detailsortlistFree();
            batch_columnlistFree();
            batch_maplistFree();
            LOG(LM_STD,Fmtmsg("BATCH: �������ļ�[%s]ʧ��",sFileName),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        iTotalRows=0;
        while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, fp1 ) != NULL )
        {
            iTotalRows++ ;

            /*ȥ���س�����,���Դ������س����е� modified by chenxm 20141212*/
            if( 10 == linebuf[0] || 13 == linebuf[0] )
            iTotalRows-- ;
        }
        /* ȥ�����һ�еĻس�����,���ж���������޷����� (noted by chenxm 20141212)*/
        /*if( 10 == linebuf[0] || 13 == linebuf[0] )
        {
            iTotalRows-- ;
        }*/
        LOG(LM_STD,Fmtmsg("BATCH: �ļ�������[%d]", iTotalRows ),"INFO")

        fclose(fp1);
/* 20110825 �����ļ�����ȡ���� 
    }
*/

    /* �������ļ����� */
    if( ( srcfp = fopen( sFileName, "r" ) ) == NULL )
    {
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        LOG(LM_STD,Fmtmsg("BATCH: �������ļ�[%s]ʧ��",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ����ͷ�Ļ�����Ϣ */
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
            iClassPre++;
            if( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
            {
                totalcount++;
                iResult =totalProc(lXmlhandle, linebuf, &thisSortT);
                if( iResult != 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ������Ϣ����ʧ��,[%s],[%d],[%s]",
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

    /* 01 ����ϸ 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
    if( strcmp( sFileType,"03" ) == 0 ) 
        iTotalRows -= iTSortCount ; /* ��ȥ����������Ϊʵ����ϸ��¼�������� */
    else if( strcmp( sFileType,"04" ) == 0 ) 
        iTotalRows = iTotalRows -iTSortCount ; 
        /* ��ȥ��β���ܼ�¼����Ϊʵ����ϸ��¼�������� */
    else if ( strcmp( sFileType,"02" ) == 0 )
        iTotalRows -= 1 ;
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS, sBuf);
    iBatchReqZbs = atoi(sBuf);
    LOG(LM_STD,Fmtmsg("BATCH: �ļ���ϸ��β��, iBatchReqZbs[%d],iTotalRows[%d],iTSortCount[%d],iClassPre[%d]", 
        iBatchReqZbs,iTotalRows,iTSortCount, iClassPre ),"INFO")
    if ( iBatchReqZbs > 0 && iBatchReqZbs != iTotalRows)
    {
        LOG(LM_STD,Fmtmsg("BATCH: �����ļ�������,��ϸ��¼ȱ��[%d]��", iBatchReqZbs - iTotalRows),"ERROR")
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
        LOG(LM_STD,Fmtmsg("BATCH: ���ļ�[%s]ʧ��",sTmpFileName),"ERROR")
        batch_totalsortlistFree();
        batch_detailsortlistFree();
        batch_columnlistFree();
        batch_maplistFree();
        fclose(srcfp);
        fpub_SetMsg(lXmlhandle,MID_BATCH_OPENFILE,MSG_BATCH_OPENFILE);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ��ʼ������ϸ��Ϣ */
    index = 0;
    memset(linebuf, 0, sizeof(linebuf));
    while( fgets( linebuf, BATCH_MAX_FILELINE_BYTE, srcfp ) != NULL )
    {
        index ++;
        /* ����Ч��Ϣ ����*/
        if( strlen( linebuf ) < 3 )
        {
            continue;
        }

        detailcount++;
        /*  rowsΪ�ļ������� */
        if( index > iTotalRows && (strcmp( sFileType,"03" ) == 0 || strcmp( sFileType,"04" ) == 0)) 
        {
            detailcount --;
            break; /* ֻ�� TYPE��03 04 �ĲŻ��ߵ����� */
        }
        memset(outbuf, 0, sizeof(outbuf));

        /* ���������ļ���¼������ӳ�䣬����ɿ��Ե������ݿ����ַ��� */
        length = detailProc(lXmlhandle,detailcount,iWjxh,linebuf,&dTotal,outbuf,&thisSort);
        if( length < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH:��ϸ��Ϣ����ʧ��[%s]",linebuf),"ERROR")
            iAbort = 6;
            break;
        }
        outbuf[length] = '\n';
        iResult = fwrite( outbuf, length + 1, 1, tmpfp );
        if( iResult < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: �ļ�д��ʧ��,[%d],[%s]",\
                            errno,strerror(errno)),"ERROR")
            iAbort=7;
            break;
        }
        memset(linebuf, 0, sizeof(linebuf));
        /* �����ļ���� */
        if( ( lPgNum > 0 ) && ( ( detailcount % lPgNum ) == 0 ) )
           iWjxh ++;
        
    }
    /* ����β��������Ϣ */  
    /* 01 ����ϸ 02 ���ܣ�����ϸ 03 ����ϸ������ 04 ���ܣ�����ϸ������ */
    if( ( strcmp( sFileType, "03" ) == 0 ||  strcmp( sFileType, "04" ) == 0 ) && ! iAbort )
    {
        ii = 0;
        /* ���ñ�֤������Ϣ˳�� */
        for( pfileTotalSortIter = i_list_begin(t_fileTotalSortList);
              pfileTotalSortIter!= i_list_end(t_fileTotalSortList);
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
                totalcount++;
            }
            else
            {
                LOG(LM_STD,Fmtmsg("BATCH: ȡ���ܼ�¼��Ϣʧ��"),"ERROR")
                iAbort = -1;
                break;
            }
          
            iResult =totalProc(lXmlhandle, linebuf, &thisSortT);
            if( iResult != 0 )
            {
                LOG(LM_STD,Fmtmsg("BATCH: ������Ϣ����ʧ��,[%s],[%d],[%s]",
                linebuf,thisSortT.fileclasssn,thisSortT.classname),"ERROR")
                iAbort = iResult;
                break;
            }

            ii++;
        }
    }

    fclose(tmpfp);
    fclose(srcfp);
    /* �ͷ�������Դ */
    batch_totalsortlistFree();
    batch_detailsortlistFree();
    batch_columnlistFree();
    batch_maplistFree();
    
    /* �����쳣 */
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
    LOG(LM_DEBUG,Fmtmsg("BATCH: ��ϸ�ļ��������,�����¼����: [%d]",detailcount),"DEBUG");
    if( detailcount == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: �����ļ�[%s]��ϸ��¼Ϊ��",sFileName),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_LPWJ_NULL,MSG_BATCH_LPWJ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPRET_FAIL;
    }
    /*����ʱ�ļ����ݵ��뱾����ϸ��*/
    /* modified by yangdong 20111020 �\��ASCII��5C��ͷ�����ǡ�\���� ת���ַ�����
    if(sql_LoadFromFile(sTmpFileName,sTableName,'^','\\',&lRCount) != 0 )
    */
    int iii = 1;
    /* modified  by yangdong ʹ�÷ֲ��ύ��load���� 
    if(sql_LoadFromFile(sTmpFileName,sTableName,'^',iii,&lRCount) != 0 )
    */
    /* modified by guoliang 20130412 ���ݲ�ͬ����Ӧ�����ò�ͬ����Ӧ��Ϣ */
    iRet = sql_LoadFromFile_b(sTmpFileName,sTableName,'^',iii,&lRCount);
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: ���ļ�[%s]���ݵ��뱾����ϸ��[%s]ʧ��[%d],������[%d]",\
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
    /*  add by yr 20120814 ����commit */
    if( DCICommit() == -1 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*   end add */

    /* ɾ����ʱ�ļ� */
    unlink(sTmpFileName);

    /* ����ʵ���ܱ��� */
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZBS,itoa(detailcount));
    /* ����ʵ���ܽ�� */
    memset(sBuf,0,sizeof(sBuf));
    sprintf(sBuf,"%.2f",dTotal);
    COMP_SOFTSETXML(XMLNM_BATCH_MX_ZJE,sBuf);
    LOG(LM_STD,Fmtmsg("BATCH: ��� ʵ���ܱ���[%s]ʵ���ܽ��[%s]",itoa(detailcount),sBuf),"INFO")

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��������:
IRESULT sql_LoadFromFile(char* sFilename,char *sTname,
                         char cDiv,char cEscape,long *lResult)
��������:
��ָ��Load��ʽ�ļ�����ȡ��¼���뵽ָ�����ݿ��
�������:
         char *sFilename       �����ļ���(ȫ·��)
         char *sTname          ����
         char cDiv             �ָ���      ȱʡΪ'|'
         char cEscape          ת���ַ�    ȱʡΪ'\'
         long *lResult         �����¼����(���)
��    ��:
         �ɹ�
           MID_SYS_SUCC
         ʧ��
           MID_SYS_INVALID
           MID_SYS_OPENFILE
 
           MID_SQL_PREPARE
           MID_SQL_DESCRIBE
 
           MID_SQL_ALLOCDESCPT
           MID_SQL_SETDESCPT
��    ��:
�� Ŀ ��:�м�ҵ���Ʒ�з���
�� �� Ա:Stony.Z,Tianhc,Shining
��������:2000��01��01��
�޸�����:2002��04��01��
�޸�����:2009��01��09��
��:
   �ɵĴ���ֻ������INFORMIX,����ORACLE������;
   ���ORACLE�Ĵ������select_lda=sqlald()����ORACLE������ṹ,���̲�����,���ڴ�й¶!
   �ʲο�fpub_InsertTableFromXML������д
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
 

    LOG(LM_DEBUG, Fmtmsg("��̬�������ݿ�ʼ,���ļ�[%s]->��[%s]", sFilename, sTname),"DEBUG")

#ifdef TIMEDEBUG
    ftime(&starttime);
#endif

    memset( sDbType, 0x00, sizeof( sDbType ) );
    sprintf(sDbType, "%s", getenv("DB"));
    trim( sDbType );

    *lResult = 0;
    if ( !*sFilename || !*sTname )
    {
        LOG(LM_STD,Fmtmsg("�ļ���[%s] ����[%s]", sFilename, sTname ),"ERROR")
        return    MID_SYS_INVALID;
    }
    /* ���ļ� */
    if ( cDiv == 0 )
        cDiv = '|';
    if ( cEscape == 0 )
        cEscape = '\\';
 
    if ( (fpLoadfile = fopen(sFilename, "r")) == NULL )
    {
        LOG(LM_STD,Fmtmsg("�ļ�[%s] ��ʧ��", sFilename ),"ERROR")
        return MID_SYS_OPENFILE;
    }
 
    /* ��ȡ��ṹ */
    sprintf(sSqlstr, "select * from %s where 1=2", sTname);
    cur = DCIDeclareCursor(sSqlstr, 0);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
        fclose(fpLoadfile);
        return MID_SQL_DECLARE;
    }
    DCIExecute(cur);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fclose(fpLoadfile);
        return MID_SQL_EXECUTE;
    }
    numCols = DCINumCols(cur);                        /* ȡ�ֶ��� */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fclose(fpLoadfile);
        return MID_SQL_EXECUTE;
    }
 
    /*���ɶ�̬SQL���*/
    memset(sSqlstr, 0 , sizeof(sSqlstr));
    memset(sValstr, 0 , sizeof(sValstr));
    sprintf(sSqlstr, "insert into %s (", sTname);
    sprintf(sValstr, " ) values ( ");
 
    for (iCnt = 0, iflag = 0; iCnt < numCols;iCnt++)
    {
        memset(sFldname, 0, sizeof(sFldname));
        DCIColName(cur, iCnt, sFldname, sizeof(sFldname));     /* ȡ�ֶ��� */
        if ( DCIERR )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
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
 
    cur_ins = DCIDeclareCursor(sSqlstr, 0);    /* ��insert���α� */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
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
    /*�������ļ����ݲ���ñ���*/
    iflag = 0;
    /*bind*/
    for (iCnt = 0;iCnt < numCols;iCnt++)
    {
            iType[iCnt] = DCIColType(cur, iCnt);     /* ȡ�ֶ����� */
            if ( DCIERR )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
                iflag = -22;
                break;
            }
            iSize[iCnt] = DCIColSize(cur, iCnt);     /* ȡ�ֶδ�С */
            if ( DCIERR )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
                iflag = -23;
                break;
            }
            iScale[iCnt] = DCIColScale(cur, iCnt);    /* ȡ�ֶξ��� */
            if ( DCIERR )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
                iflag = 24;
                break;
            }
/*LOG(LM_STD, Fmtmsg("iType=%d isize=%d",iType[iCnt] , iSize[iCnt]), __func__);*/
            
            /*���ö�̬SQL�������*/
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
            iSize[iCnt]++; /*char���ͷ����ڴ��ֶγ���Ӧ�ü�1*/ 
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
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
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
            
            /*����Կ��е���������    by shining 2013-01-28 13:21:14*/
            if ((strlen(trim(sLbuffer0))==0)||(sLbuffer0[0] == '\n'))
                continue;
            /*end */
            
            /*���ݷָ�����ת���ַ����л�����ȡ�ֶε�ֵ*/
            for (iCnt = 0;iCnt < numCols;iCnt++)
            {
             
                memset(sTmp, 0x00, sizeof(sTmp));
                if ( fpvt_GetListbyDiv(sLbuffer, iCnt + 1, sTmp, cDiv, cEscape) < 0 )
                {/*�Ҳ���ָ����*/
                    iflag = -21;
                    break;
                }
              /*LOG(LM_STD, Fmtmsg("-----%d----[%s]",iCnt, sTmp), __func__);*/
                /*���ö�̬SQL�������*/
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
                          /* modified by yangdong 20151125 ��coredump
                          LOG(LM_STD,Fmtmsg("BATCH: ���ݵ�%d��[%s]����,%sλ���ֶα��Զ���ȡ",iCnt, sTmp, iSize[iCnt]-1 ),"ERROR")
                          */
                          LOG(LM_STD,Fmtmsg("BATCH: ���ݵ�[%d]��[%s]�������峤��[%d]",iCnt, sTmp, iSize[iCnt]-1 ),"ERROR")
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
            DCIERRLOG(LM_STD, Fmtmsg("Execute SQLʧ��[%s]", DCILastError() ), __func__);
            if ( DCIERR )
            {
                /* modified by guoliang 20130412 �жϳ�����Ϣ */
                memset(sSqlErrMsg, 0x00, sizeof(sSqlErrMsg));
               strncpy(sSqlErrMsg, DCILastError(), sizeof(sSqlErrMsg)-1);
               if( (strstr(sSqlErrMsg, "ORA-01400")) != NULL)
                    iflag = -41;
               else
                    iflag = -32;
               break;
               /* end */
            }

            /* added by yangdong 20130131 �ֲ��ύ */
            if( ( (*lResult)  % 5000 ) == 0 )
            {
                ftime(&endtime);
                LOG(LM_DEBUG,Fmtmsg("BATCH: ���[%d],cast[%ld]ms", *lResult,\
                (endtime.time-starttime.time)*1000+endtime.millitm-starttime.millitm ),"DEBUG");

                if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
                {
                    if ( sql_CommitTrans() !=MID_SYS_SUCC )
                    {
                        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                        sql_RollbackTrans();
                        iflag= -33;
                        break;
                    }
                }
                ftime(&starttime);
            }
        }
        /*�������,free sdata()*/
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
    LOG(LM_DEBUG, Fmtmsg("��̬����� usendtime[%ld]",\
         (endtime.time - starttime.time)*1000 + endtime.millitm - starttime.millitm), "DEBUG")
#endif
    if (iflag < 0)
    {
        LOG(LM_STD, Fmtmsg("��̬�����[%s]ʧ��, iflag=[%d], rows=[%d]", sTname, iflag, *lResult), "ERROR")
        return iflag;
    }
 
    LOG(LM_STD, Fmtmsg("��̬�����[%s]�ɹ�����,��[%d]��", sTname, *lResult), "DEBUG")
 
    return MID_SYS_SUCC;
}
