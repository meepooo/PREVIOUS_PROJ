/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT4.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_P2LJ.ec
�ļ�����:����ת��������ҵ�����
�� �� Ա:������
��������:20161116

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
        <sonote>BATCH��ת�����������</sonote>\
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

/************************************************************************
��������:
IRESULT fprv_sql_UnloadToBuffer(char *sBuffer,char *sSql,char cDiv,char cEscape,long *lResult)
��������:
  ����SQL��ѯ���������UNLOAD��ʽ�����
�������:
         char *sBuffer         �����ַ���
         char *sSql            ��ѯSQL���
         char cDiv             �ָ���      ȱʡΪ'|'
         char cEscape          ת���ַ�    ȱʡΪ'\'
         long *lResult         �����¼����(���)
��    ��:
         �ɹ�
           MID_SYS_SUCC
         ʧ��
           MID_SYS_INVALID
           MID_SYS_OPENFILE
           MID_SYS_MEMALLOC

           MID_SQL_DESCRIBE
           MID_SQL_CUROPEN
           MID_SQL_CURFETCH

************************************************************************/
/*
 *�����ֶε�����,ȡ�����ֶε�����.
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
    char sDesdata[1024];   /* �����ֽڳ��� */
    CURSOR cur;
    int numCols=0;
    int rc=0;
    char *sData=NULL;

    LOG(LM_STD,Fmtmsg("��̬�س����ݿ�ʼ,���ݲ�ѯ[%s]->Buffer",sSql),"fprv_sql_UnloadToBuffer")

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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        return MID_SQL_DECLARE;
    }
    iRet = DCIExecute(cur);
    if ( iRet == -1 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        DCIFreeCursor(cur);
        return MID_SQL_EXECUTE;
    }
    numCols = DCINumCols(cur);            /* ȡ�ֶ��� */
    if ( numCols == -1 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        DCIFreeCursor(cur);
        return MID_SQL_EXECUTE;
    }

    rc=DCIFetch(cur);
    if ( rc == -1 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
        DCIFreeCursor(cur);
        return MID_SQL_CURFETCH;
    }
    else if ( rc==0 )
    {
        LOG(LM_STD,Fmtmsg("=========û�����������ļ�¼========"),"fprv_sql_UnloadToBuffer")
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
            *��SELECT��������ȡ��iCnt���ֶε���Ϣ;
            */
            iType = DCIColType(cur, iCnt);   /* ȡ�ֶ����� */
            if ( iType == -1  )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
                DCIFreeCursor(cur);
                return MID_SQL_EXECUTE;
            }
        
            iSize = DCIColSize(cur, iCnt);   /* ȡ�ֶδ�С */
            if ( iSize == -1 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
                DCIFreeCursor(cur);
                return MID_SQL_EXECUTE;
            }
        
            iScale = DCIColScale(cur, iCnt);  /* ȡ�ֶξ��� */
            if ( iScale == -1  )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
                DCIFreeCursor(cur);
                return MID_SQL_EXECUTE;
            }
        
            /*
            *����������ȡ��nCnt���ֶε���Ϣ;
            */
            sData = DCIFieldAsString(cur, iCnt);
            /*
            *�������Ե��������������;
            */
            memset(sDesdata,0,sizeof(sDesdata));
            trim(sData);
            fprv_dyn_getdata_byattr(sDesdata,sizeof(sDesdata),iType,iSize,iScale,sData);
        
            trim(sDesdata);
            for ( k=0;k<strlen(sDesdata);k++ )
            {
                if( sDesdata[k]==cEscape || sDesdata[k]==cDiv || sDesdata[k]=='\n')
                /*ת���ַ�'\'*/
                    sBuffer[iLineLen++]=cEscape;
                sBuffer[iLineLen++]=sDesdata[k];
            }
            sBuffer[iLineLen++]=cDiv;
        }
        sBuffer[iLineLen++]='\n';
        
        rc=DCIFetch(cur);
        if ( rc == -1  )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"fprv_sql_UnloadToBuffer")
            DCIFreeCursor(cur);
            return MID_SQL_CURFETCH;
        }
        else if ( rc==0 )
        {
            LOG(LM_STD,Fmtmsg("=========���������ļ�¼��ȫ������========"),"fprv_sql_UnloadToBuffer")
            break;
        }
    }

    DCIFreeCursor(cur);

    LOG(LM_STD,Fmtmsg("��̬��ѯ[%s]��������ɹ�����,[%ld][%s]",sSqlstr,*lResult,sBuffer),"fprv_sql_UnloadToBuffer")

    return MID_SYS_SUCC;
}

/************************************************************************
��̬�����������
�����������:SBATCH_P2LJ_CONTROL
�������:SBATCH_P2LJ_CONTROL
�������: ����������ת�����ַ�����
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
IRESULT SBATCH_P2LJ_CONTROL(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sMapID[40+1];
    char sYwbh[16+1];
    char sColID[32+1];
    char sFileID[32+1];
    char sSqlStr[4096];
    /* int iWjxh = 0;     �ļ���� */
    int iZjszwz = 0;   /*��������λ�� */
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
    COMP_GETPARSEPARAS(1,sBuf,"ҵ�����")
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBM_NULL,MSG_BATCH_YWBM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sTableName,sBuf,sizeof(sTableName));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"����������¼������")
    if (sBuf[0] == '\0')
    {
        lPgNum=20;
    }else
        lPgNum = atol( sBuf );

    memset(sSubFlow,0,sizeof(sSubFlow));
    COMP_GETPARSEPARAS(3,sSubFlow,"����������")

    /* �������� */
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sPkrq);
    if( 0 == sPkrq[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }

    /* ƽ̨���κ� */
    memset(sPtPch, 0x00, sizeof(sPtPch));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf);
    pstrcopy(sPtPch,sBuf,sizeof(sPtPch));
    LOG(LM_STD,Fmtmsg("��ת�����ַ����ִ�п�ʼ[%s%s],lPgNum[%ld],sSubFlow[%s]", 
        sPkrq, sPtPch, lPgNum, sSubFlow), fpub_GetCompname(lXmlhandle))

    /* ��װ��ѯ������� */
    memset(sQtWjdc, 0x00, sizeof(sQtWjdc));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPCFG_RWQT_QTWJDC, sQtWjdc)
    
    memset(sSql, 0x00, sizeof(sSql));
    /* �ݶ���ʼ*/
    snprintf(sSql, sizeof(sSql), 
        "select lsxh,cgbz from %s where pkrq = '%s' and ptpch = '%s' and cgbz in ('9', '5') and %s order by lsxh",
        sTableName, sPkrq, sPtPch, StrReplace(sQtWjdc, "#", "'"));
    LOG(LM_STD,Fmtmsg("BATCH: ��ת�����ַ�[%s]", sSql ),"DEBUG");
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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
    iProcs = DCINumRows(cur);
    if (iProcs < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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
            LOG(LM_STD,Fmtmsg("���ݿ�����α�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            break;
        }
        if ( iRet == 0 )
        {
            iFlag = 0;
            LOG(LM_STD,Fmtmsg("�����ѱ�����, ����ѭ����" ),"ERROR")
            break;
        }
        LOG(LM_STD,Fmtmsg("-[%d]--lsxh[%d],cfbz[%s]", iCount, sdb_batch_p2lj.lsxh, sdb_batch_p2lj.cgbz  ),"INFO")
        COMP_SOFTSETXML("/batch/sjtj/lsxh", itoa(sdb_batch_p2lj.lsxh))
        COMP_SOFTSETXML("/batch/sjtj/cgbz", sdb_batch_p2lj.cgbz)
        if (sdb_batch_p2lj.cgbz[0] == '9')
        {/*9-δ����,����ļ���*/
            COMP_SOFTSETXML("/batch/sjtj/instr", "hxjz")
        }else if (sdb_batch_p2lj.cgbz[0] == '5')
        {/*5-��ʱ,�賬ʱ��֤*/
            COMP_SOFTSETXML("/batch/sjtj/instr", "cscz")
        }else
        {
            continue;
        }
	    if( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
	    {
	    	LOG(LM_STD, Fmtmsg("[%d]���÷ַ�������ʧ��", iCount+1), fpub_GetCompname(lXmlhandle));
	    	continue;
	    }

    }
    DCIFreeCursor(cur);
    if ( iFlag < 0 )
    {
        LOG(LM_STD,Fmtmsg("�ַ�����[%d]",iFlag ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    LOG(LM_STD,Fmtmsg("��ת�����ַ�����,���ַ�[%d]��", iCount), fpub_GetCompname(lXmlhandle))
    if ( iProcs == 0 )
    {/*��������û���账����ϸ,��ָ����һ����*/
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    }else if ( iProcs > 0 )
    {/*����,˵������δ������ϸ,�����״̬����*/
        fpub_SetCompStatus(lXmlhandle, 1);
    }else
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    }

    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_P2LJ_PREPROC
�������:SBATCH_P2LJ_PREPROC
�������: ����ת����ǰ����
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
IRESULT SBATCH_P2LJ_PREPROC(HXMLTREE lXmlhandle)
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
    char sColStr[2048];  /* �ύ��̨ӳ���ֶ� */
    int  lPgNum = 0;    /* ÿ�����ļ�����¼�� */
    int  iCols=0;
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
    memset(sPkrq, 0x00, sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                    
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* ƽ̨���κ� */
    memset(sPtpch, 0x00, sizeof(sPtpch));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    /* ��ˮ��� */
    memset(sLsxh, 0x00, sizeof(sLsxh));
    COMP_SOFTGETXML("/batch/sjtj/lsxh",sLsxh);

    /* �ɹ���־ */
    memset(sCgbz, 0x00, sizeof(sCgbz));
    COMP_SOFTGETXML("/batch/sjtj/cgbz",sCgbz);
    
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* ȥ���һ�� , */
    sColStr[strlen( sColStr ) - 1 ] = '\0';
    
    /* ��ϸ�ύ��־ */
    memset( sGetFlag, 0x00, sizeof( sGetFlag ) );
    COMP_SOFTGETXML( XMLNM_BATCH_MXTJBZ, sGetFlag );
    LOG(LM_DEBUG,Fmtmsg("BATCH: �ύ��־[%s]", sGetFlag ),"DEBUG");

    /*  clzt:9 δ����,cgbz:0 �ɹ�,1���ֳɹ�,2ʧ��,5����ʱ,8������ */
    snprintf(sCondStr, sizeof( sCondStr ),"pkrq='%s' AND ptpch='%s' AND lsxh='%s' ", sPkrq, sPtpch, sLsxh );
    
    /* ��ռ���±�����ϸ��¼ */
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "UPDATE %s SET cgbz='8' WHERE %s AND cgbz='%s'", 
        sTableName, sCondStr, sCgbz );
    LOG(LM_STD,Fmtmsg("BATCH: ��ת����ռsql[%s]", sSqlStr ),fpub_GetCompname(lXmlhandle));
    DCIBegin();
    iRet = DCIExecuteDirect( sSqlStr );
    if ( iRet < 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("����������ϸ��ʧ��,sqlerr[%d][%s]",DCILastError() ),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCICommit();
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("δ�ܳɹ���ռ��ת����ϸ��¼[%s%s,%s,%s]���Ѵ���!", sPkrq, sPtpch, sLsxh, sCgbz),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        COMP_SOFTSETXML(XMLNM_RESPCODE, BATCH_REPSCODE_SUCC)
        COMP_SOFTSETXML(XMLNM_RESPMSG, "BATCH:��¼��Ϊ��,δ�ܳɹ���ռ��ת����ϸ��¼")
        return COMPRET_SUCC;
    }
    /*��ȡ����ϸ��¼*/
    memset( sSqlStr, 0x00, sizeof( sSqlStr ) );
    snprintf(sSqlStr, sizeof( sSqlStr), "SELECT %s FROM %s WHERE %s ", sColStr, sTableName, sCondStr );
    LOG(LM_STD,Fmtmsg("BATCH: ��ת������Sql [%s]", sSqlStr ),"STD");
    memset(sLine, 0x00, sizeof(sLine));
    iRet = fprv_sql_UnloadToBuffer(sLine, sizeof(sLine), sSqlStr,'|','\\',&lRCount );
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("��ת����ϸ��¼��Bufferʧ��[%d]", iRet),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "��ת����ϸ��¼��Bufferʧ��");
        return COMPRET_FAIL;
    }
    if( lRCount == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:��¼��Ϊ�㣬�����ύ�ڲ�����Ƕ�״���"),"WARNING");
        /*fpub_SetMsg(lXmlhandle,BATCH_REPSCODE_SUCC,"BATCH:��¼��Ϊ�㣬�����ύ�ڲ�����Ƕ�״���");*/
        COMP_SOFTSETXML(XMLNM_RESPCODE, BATCH_REPSCODE_SUCC)
        COMP_SOFTSETXML(XMLNM_RESPMSG, "BATCH:��¼��Ϊ�㣬�����ύ�ڲ�����Ƕ�״���")
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

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SBATCH_P2LJ_LASTPROC
�������:SBATCH_P2LJ_LASTPROC
�������: ����ת��������
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
    char sFileName[256]; /* ���������ļ�ȫ��(��·��) */
    char sFileID[40+1];
    char sMapID[40+1];   /* ӳ���ʶ */
    int  iTSortCount=0;
    char sRespID[40+1];  /* ��Ӧ��ת����ʶ */
    int  i,iAbort=0;
    char sPtpch[8+1],sLsxh[8+1];
    char sPkrq[8+1];
    char sNode[32+1];
    char sLine[1024],sColName[256],sColValue[512],sSjthNodePath[512];
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

    /* ��ˮ��� */
    memset(sLsxh,0,sizeof(sLsxh));
    COMP_SOFTGETXML("/batch/sjtj/lsxh",sLsxh);
    trim(sLsxh);

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

    /* ��ȡ������������ֶ���Ϣ */
    cur = DCIDeclareCursor(sSqlStr, 0);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    DCIExecute(cur);
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPSTATUS_FAIL;
    }
    iAllcount = DCINumCols(cur);                        /* ȡ�ֶ��� */
    if ( DCIERR )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��![%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
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
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if ((cur = DCIDeclareCursor(sSqlUpd, DCI_STMT_LOCATOR)) == -1)
    {
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
            DCIFreeCursor(cur);
            prv_free_data( sdata, iAllcount );
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
       }
    }

    /* ��ʼ������ϸ */
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
                /* ������ϸ����ȡ�����ֶ�ֵ���������� 
                memset(sBuf, 0x00, sizeof(sBuf));
                iResult = prv_rwqt_detailProc(lXmlhandle,linebuf,pos[iFileValPos], sBuf,&thisSort,&dDetailAmt,t_fileColumnList);
                if( iResult < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: ����ļ���ϸ��Ϣ����ʧ��,pos[%d]=[%d],[%d],[%s]: [%d],[%s]",\
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
            DCICommit();
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

    /* �����쳣 */
    if ( iAbort != 0  )
    {
        LOG(LM_STD,Fmtmsg("BATCH: ����ļ����´������: [%d]",iAbort),"ERROR");
        /* ��Ӧ��Ϣ */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
        return COMPSTATUS_FAIL ;
    }

    /* ������Ӧ��ת����Χ 1��ֻת�����ʧ����Ϣ */
    COMP_SOFTSETXML( XMLNM_BATCH_SJHP_CVTRESP, "1" );

    /* ������Ĳ�����ʵ��У�����ʵ�ʽ����Ϊ0.00 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_HOST_AMT_FLAG,sBuf);
    if( sBuf[0] == '1' )  /* 1-������ 0-���أ�Ĭ�ϣ� ( �����ñ������򲻴��� ) */
    {
        memset( sSqlUpd, 0x00, sizeof( sSqlUpd ) );
        memset( sBuf, 0x00, sizeof( sBuf ) );
        COMP_SOFTGETXML( XMLNM_BATCH_SJTH_ZJXH,sBuf);
        /* ���ɹ���ϸ��ʵ�ʽ����Ϊ���׽�� */
        sprintf( sSqlUpd, "UPDATE %s SET sjje=jyje WHERE pkrq='%s' AND ptpch='%s' AND lsxh=%s  ", \
            sTableName, sPkrq, sPtpch,  sLsxh );

        DCIBegin();
        iRet = DCIExecuteDirect( sSqlUpd );
        if( iRet < 0  )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_PLRW,MSG_BATCH_UPD_PLRW );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
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
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}
