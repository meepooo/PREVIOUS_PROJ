/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(BATCH2.0)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_PQUERY.c
�ļ�����:���ո���ҳ��ѯ�������
�� Ŀ ��:
�� �� Ա:yd@hundsun.com
��������:2012��7��22��

�� �� Ա:yd@hundsun.com
��������:2013��3��8��
�޸�����:��չ��ϸ��ѯ����

�� �� Ա:yd@hundsun.com
��������:2013��6��1��
�޸�����:�޸�����״̬��ѯ,����ʧ������û�еǼ��ļ���Ϣ���

�� �� Ա:YangDong
�޸�����:20141018
�޸�˵��:DCI����
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
        <sonote>BATCH����ҵ����ϸ��ҳ��ѯ</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2012-7-1 15:08\" programer=\"YangDong\" filesize=\"1591618\">HS-AgentV2.1����</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2013-3-8 15:08\" programer=\"YangDong\" filesize=\"1591618\">��չ��ϸ��ѯ����</rec>\
        <rec ver=\"2.1.0.3\" modify=\"2013-6-1 15:08\" programer=\"YangDong\" filesize=\"1591618\">�޸�����״̬��ѯ,����ʧ������û�еǼ��ļ���Ϣ���</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1591618\">DCI����</rec>\
        </version>\
        </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" ��鿴��ϸ��Ϣ...\n");
    return 0;
}

/**********************************************************************
�������: SBATCH_PQUERY
�������: ֧����Χ�����ҳ��ѯ����,������ѭ�ӿ����
���������
���������
���������
����˵��: ֧����Χ��ҳ��ѯ����
          �������ã�
                    ��Χ�Ϸ�ʱ�������ϴ�Ӧ����Ϸ�ID.
                    ��Χ�·�ʱ�������ϴ�Ӧ����·�ID.          
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
    char sYhh1[32+1]; /* �û��� */
    char sCxbz[1+1];  /* ��ѯ��־ 0-��ǰ��Ĭ�ϣ� 1����ʷ�� */
    char sCgbz[1+1];  /* �ɹ���־ */
    char sXym[16+1];  /* ��Ӧ�� */
    char sCxzd1[16+1];/* ��չ��ѯ�ֶ�1 */
    char sCxzd2[16+1];/* ��չ��ѯ�ֶ�2 */
    char sCxzd3[16+1];/* ��չ��ѯ�ֶ�3 */
    char sCxtj1[32+1];/* ��չ��ѯ����1 */
    char sCxtj2[32+1];/* ��չ��ѯ����2 */
    char sCxtj3[32+1];/* ��չ��ѯ����3 */
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
                      
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG"); 
       
    /*����������*/
    COMP_PARACOUNTCHKMIN(3)
    
    memset(sBuf, 0, sizeof(sBuf));
    memset(querydirect, 0, sizeof(querydirect));
    COMP_GETPARSEPARAS(1,sBuf,"��ѯ����: 0�״�:1�Ϸ�:2�·�") 
    trim(sBuf);
    strncpy(querydirect, sBuf, sizeof(querydirect)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    memset(querynum, 0, sizeof(querynum));
    COMP_GETPARSEPARAS(2,sBuf,"����¼��")
    trim(sBuf);
    strncpy(querynum, sBuf, sizeof(querynum)-1);
    
    memset(queryoffset, 0, sizeof(queryoffset));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"�ϴβ�ѯID")
    trim(sBuf);
    strncpy(queryoffset, sBuf, sizeof(queryoffset)-1);
    
    memset(sFhgs, 0, sizeof(sFhgs));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"���ظ�ʽ " ); /*:1 �����ֶ���Ϣ��Ĭ�ϣ� 2 �����ֶ��� 3 �����ֶ���,�����ֶ�˵�� */
    trim(sBuf);
    strncpy(sFhgs, sBuf, sizeof(sFhgs)-1);

    iPageNum = atoi( querynum );
    if( iPageNum <= 0 )
        iPageNum = 20;  /* Ĭ��ÿ�β�ѯ����20�� */

    memset(sTable, 0, sizeof(sTable));
    COMP_HARDGETXML( "/batch/wwmapinfo/ywbm",sTable );
    memset(sYwbh, 0, sizeof(sYwbh));
    COMP_SOFTGETXML( "/batch/req/ywbh",sYwbh );

    /* ƽ̨���κ� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sPtpch, 0, sizeof(sPtpch));
    COMP_SOFTGETXML( "/batch/req/ptpch",sBuf);
    strncpy(sPtpch, sBuf, sizeof(sPtpch)-1);

    /* �̻����κ� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sShpch, 0, sizeof(sShpch));
    COMP_SOFTGETXML( "/batch/req/shpch",sBuf);
    strncpy(sShpch, sBuf, sizeof(sShpch)-1);

    /* �������� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sPkrq, 0, sizeof(sPkrq));
    COMP_SOFTGETXML( "/batch/req/pkrq",sBuf );
    strncpy(sPkrq, sBuf, sizeof(sPkrq)-1);

    /* �����˺� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sYhzh, 0, sizeof(sYhzh));
    COMP_SOFTGETXML( "/batch/req/yhzh",sBuf);
    strncpy(sYhzh, sBuf, sizeof(sYhzh)-1);

    /* �û���� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sYhh1, 0, sizeof(sYhh1));
    COMP_SOFTGETXML( "/batch/req/yhh1",sBuf);
    strncpy(sYhh1, sBuf, sizeof(sYhh1)-1);

    /* ��ѯ��־ 0-��ǰ��(Ĭ��) 1-��ʷ�� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sCxbz, 0, sizeof(sCxbz));
    COMP_SOFTGETXML( "/batch/req/cxbz",sBuf);
    strncpy(sCxbz, sBuf, sizeof(sCxbz)-1);

    /* �ɹ���־ */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sCgbz, 0, sizeof(sCgbz));
    COMP_SOFTGETXML( "/batch/req/cgbz",sBuf);
    strncpy(sCgbz, sBuf, sizeof(sCgbz)-1);
    
    /* ��Ӧ�� */
    memset(sBuf, 0, sizeof(sBuf));
    memset(sXym, 0, sizeof(sXym));
    COMP_SOFTGETXML( "/batch/req/xym",sBuf);
    strncpy(sXym, sBuf, sizeof(sXym)-1);

    /* ��չ�Ĳ�ѯ�ֶ����Ͳ�ѯ������ */
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

    /* ��ѯ��־ 1-��ʷ�� 0-��ǰ��Ĭ�ϣ� */
    if( sCxbz[0] == '1' )
    {
        /* �������� BATCH_��ͷ����ʷ����ΪBATCH_HIS��ͷ */
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

    /* ��չ��ѯ���� */
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

    /* ��չ��ѯ���� */
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

    /* ��չ��ѯ���� */
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
    if( querydirect[0] =='2' )       /* �·�  */
    {
        maxRowID = iPageNum + atoi(queryoffset);
        minRowID = atoi(queryoffset)+1;
    }
    else if( querydirect[0] =='1' )  /* �Ϸ�  */
    {
        maxRowID = atoi(queryoffset)-1;
        minRowID = maxRowID-iPageNum+1;
        if( minRowID < 0 )
            minRowID = 0;
    }
    else                            /* Ĭ���״β�ѯ */
    {
        /* �����¼���� */
        memset(countsql, 0, sizeof(countsql));
        sprintf(countsql, "SELECT COUNT(*) FROM %s %s ", sQuyTable, sCondSql );
        iRet = prv_CntSql( countsql, &iCount, errmsg);
        if( iRet == -1 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��ȡͳ����Ϣʧ��,sql[%s],\
                SQLERR=[%s] [%d]", sSql1, DCILastError(), iRet ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        LOG(LM_DEBUG,Fmtmsg("��¼����: [%ld]",iCount),"DEBUG");
        /* �޲�ѯ��¼ */
        if ( iCount <=0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: ��ȡͳ����Ϣʧ��,sql[%s]",  countsql ),"ERROR");
            fpub_SetMsg(lXmlhandle, MID_SQL_NOTFOUND, MSG_SQL_NOTFOUND );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        /* �ܼ�¼�� */
        COMP_HARDSETXML("/batch/resp/zbs",itoa(iCount));
        maxRowID = iPageNum;
        minRowID = 1;
    }
 
    /*�����ļ���*/
    memset( sLsh, 0x00, sizeof( sLsh ) );
    COMP_HARDGETXML( XMLNM_ZHQZLSH,sLsh );
    memset(sFileName, 0, sizeof(sFileName));
    memset(sFileFullName, 0, sizeof(sFileFullName));
    sprintf( sFileName,"batch_mxcx_%s%s.txt" , sYwbh,sLsh );
    COMP_HARDSETXML( "/batch/resp/wjmc", sFileName);
    sprintf( sFilePath,"%s/tmp" ,  getenv( "HOME" ) );
    COMP_HARDSETXML( "/batch/resp/wjlj", sFilePath);
    sprintf( sFileFullName, "%s/%s", sFilePath, sFileName );
    
    /*�����ҳ��ѯģʽ*/
    memset(sQrySql, 0, sizeof(sQrySql));

    /* ��ȡ��ҵ����ϸ���ֶ���Ϣ */
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
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("���ݿ����ʧ��[%s]",DCILastError()),"ERROR");
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
        /* �ֶ���Ϣ */
        if( sFhgs[0] != '1' &&  sFhgs[0] != '\0' &&  sFhgs[0] != ' ' )  /* �����ֶ���Ϣ */
        {
            if( sFhgs[0] == '2' || sFhgs[0] == '4' ) /* �����ֶ��� */
            {
                strcat( sFldList, sTableCol );  
                strcat( sFldList, "|");  
            }
            if( sFhgs[0] == '3' || sFhgs[0] == '4' ) /* �����ֶ��� */
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
        LOG(LM_STD,Fmtmsg("BATCH: ��ȡ�ⲿ�ļ���Ϣʧ��,sql[%s],\
            SQLERR=[%s] [%d]", sSql1, DCILastError(), iRet ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if( iCount < 1 )
    {
        LOG(LM_STD,Fmtmsg("����Ҫ��ѯ�����ֶ�����"),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_QUERY_COLERR,MSG_BATCH_QUERY_COLERR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ȥ�����һ��' */
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

    if( sFhgs[0] != '1' &&  sFhgs[0] !=  '\0' &&  sFhgs[0] != ' ' )  /* �����ֶ���Ϣ */
    {
        memset( sFileName2, 0x00, sizeof( sFileName2 ) );
        sprintf( sFileName2, "%s2", sFileName );
        COMP_HARDSETXML( "/batch/resp/wjmc", sFileName2);
        sprintf( sFileFullName2, "%s2", sFileFullName );
        if( ( fp = ( fopen( sFileFullName, "r" ) ) ) == NULL )
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_OPENFILE,"���ļ�ʧ��" );
            LOG(LM_STD,Fmtmsg("���ļ�[%s]ʧ��,err[%s]",sFileFullName, strerror(errno) ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if( ( fp2 = ( fopen( sFileFullName2, "w+" ) ) ) == NULL )
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_OPENFILE,"���ļ�ʧ��" );
            LOG(LM_STD,Fmtmsg("���ļ�[%s]ʧ��,err[%s]",sFileFullName2, strerror(errno) ),"ERROR");
            fclose( fp );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if( sFhgs[0] == '2' || sFhgs[0] == '4' ) /* �����ֶ��� */
        {
            fprintf( fp2, "%s", sFldList );
            fprintf( fp2, "\n" );
        }
        if( sFhgs[0] == '3' || sFhgs[0] == '4' ) /* �����ֶ�˵�� */
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

    /* ��ҳ�� */
    COMP_HARDSETXML( "/batch/resp/ynbs", itoa( lResult ) );
    /* �׼�¼ID */
    COMP_HARDSETXML("/batch/resp/firstid", itoa( minRowID ) );
    /* β��¼ID */
    COMP_HARDSETXML("/batch/resp/lastid", itoa( maxRowID ) );
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}

/**********************************************************************
�������: BATCH_STATUS_QUERY
�������: ����������������ѯ����״̬
���������
���������
���������
����˵��: 
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
                      
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")  
       
    /*��ѯ������ȡ*/

    /* ҵ���� */
    COMP_SOFTGETXML( "/batch/req/ywbh",sYwbh );
    /* ƽ̨���κ� */
    COMP_SOFTGETXML( "/batch/req/ptpch",sPtpch );
    /* �̻����κ� */
    COMP_SOFTGETXML( "/batch/req/shpch",sShpch );
    /* �������� */
    COMP_SOFTGETXML( "/batch/req/pkrq",sPkrq );
    /* ���ۿ�ʼ���� */
    COMP_SOFTGETXML( "/batch/req/pkrq_begin",sPkrq_b );
    /* ���۽������� */
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

    /* ��ѯ����������Ϣ */
    sprintf( sQuerySql,"SELECT * FROM batch_plrw %s", sCondSql );
    if ((cur = DCIDeclareCursor(sQuerySql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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
    memset( &sdb_batch_plrw,0,sizeof( sdb_batch_plrw ));
    i = 0;
    while( ( iRet = DBFetch(cur, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg ) ) > 0 )
    {
        i ++; 

        if ( i > 500 ) /* ������󷵻ؼ�¼����������Ӧ�ò����� */
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_NOTFOUND, "��ѯ���ؼ�¼���������ƣ������ѯ����" );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        /* �������� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pkrq", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.pkrq);

        /* ���κ� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ptpch", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.ptpch);

        /* �̻����κ�  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shpch", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.shpch);

        /* ҵ���� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ywbh", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.ywbh);

        /* ��λ���  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dwbh", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.dwbh);

        /* ʵ���ܽ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzje", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%.2f", sdb_batch_plrw.sjzje );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* ʵ���ܱ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzbs", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_plrw.sjzbs );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* �ɹ��ܽ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzje", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%.2f", sdb_batch_plrw.cgzje );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* �ɹ��ܱ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzbs", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_plrw.cgzbs );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* ʧ���ܽ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzje", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%.2f", sdb_batch_plrw.sbzje );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* ʧ���ܱ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzbs", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_plrw.sbzbs );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* �����ļ���  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/lpwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.lpwjm);

        /* �ɹ������ļ���(Ĭ��) */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shcgwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.shcgwjm);

        /* ʧ�ܻ����ļ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shsbwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.shsbwjm);

        /* ��ǰ���� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dqbd", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.dqbd);

        /* ����״̬  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/bdzt", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.bdzt);

        /* ����״̬ */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/rwzt", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.rwzt);

        /* ��Ӧ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xydm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.xydm );

        /* ��Ӧ��Ϣ */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xyxx", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_plrw.xyxx );

        /* ���ѷ����������񣬲������ⲿ�ļ���Ǽ���Ϣ */
        /* �Ǽ����� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djrq", i );
        COMP_SOFTSETXML(sXmlNode, " ");

        /* �Ǽ���ˮ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djlsh", i );
        COMP_SOFTSETXML(sXmlNode, " ");

        /* ����״̬ */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pczt", i );
        COMP_SOFTSETXML(sXmlNode, " ");

        /* ���״̬ */
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

    /* ��ѯδ�����������Ϣ */
    memset( sQuerySql, 0x00, sizeof( sQuerySql ) );
    sprintf( sQuerySql,"SELECT djrq,djlsh,shpch,ywbh,lpwjm,shzt, pczt\
        FROM batch_wbwjdj  a %s  AND ( ptpch IS NULL OR ptpch='' OR ptpch=' ')", sCondSql );
    if ((cur = DCIDeclareCursor(sQuerySql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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

        /* added by yangdong 20130601 δ�ύ����������Ϣ��ֵΪ�գ���ǰ��Ĳ�ѯ�ڵ㱣��һ�� */
        /* �������� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pkrq", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ���κ� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ptpch", i );
        COMP_SOFTSETXML(sXmlNode, "" );
        
        /* �̻����κ�  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shpch", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.shpch);

        /* ҵ���� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/ywbh", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.ywbh);

        /* ��λ���  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dwbh", i );
        COMP_SOFTSETXML(sXmlNode, "");

        /* ʵ���ܽ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzje", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ʵ���ܱ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sjzbs", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* �ɹ��ܽ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzje", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* �ɹ��ܱ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/cgzbs", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ʧ���ܽ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzje", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ʧ���ܱ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/sbzbs", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* �����ļ���  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/lpwjm", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.lpwjm);

        /* �ɹ������ļ���(Ĭ��) */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shcgwjm", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ʧ�ܻ����ļ��� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/shsbwjm", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ��ǰ���� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/dqbd", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ����״̬  */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/bdzt", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ����״̬ */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/rwzt", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ��Ӧ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xydm", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* ��Ӧ��Ϣ */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/xyxx", i );
        COMP_SOFTSETXML(sXmlNode, "" );

        /* �Ǽ����� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djrq", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.djrq);

        /* �Ǽ���ˮ�� */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/djlsh", i );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "%d", sdb_batch_wbwjdj.djlsh );
        COMP_SOFTSETXML(sXmlNode, sTmp );

        /* ����״̬ */
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "/batch/resp/result|%d/pczt", i );
        COMP_SOFTSETXML(sXmlNode, sdb_batch_wbwjdj.pczt);

        /* ���״̬ */
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

    LOG(LM_DEBUG,Fmtmsg("��¼����: [%ld] ��ѯ����[%s]",i, sCondSql ),"DEBUG");
    /* modified by yangdong 20130601 */
    COMP_HARDSETXML("/batch/resp/zbs",itoa(i));

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}
