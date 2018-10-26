/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V4.1.0.1
����ϵͳ:AIX+ORACLE
�ļ�����:APP_PUB.c
�ļ�����:ͨ��Ӧ��ƽ̨�������
�� Ŀ ��:
�� �� Ա: YangDong
��������: 
�� �� Ա: SC 
�޸�����: 20111101
��    ��:  Agent2.1����

�� �� Ա: YangDong
�޸�����: 20111228
��    ��: �������SApp_DynExecSql(��ִ̬��sql���ṩ����ѡ��)
                  SApp_GetPara(���ݲ�����ֵ����ʼ����Ӧ����)
�� �� Ա: YangDong
�޸�����: 20130131
��    ��: ���ݲ������������ȡ��չ������ش���, select *��Ϊ��ȡcsmc��csz.

�� �� Ա: YangDong
�޸�����: 20140828
��    ��: dci����
*********************************************************************/

#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>APP_PUB.so</soname>\
        <sosrcname>APP_PUB.c</sosrcname>\
        <sonote>APPͨ���������</sonote>\
        <version>\
        <rec ver=\"2.0.0.1\" modify=\"2010-4-1  15:08\" programer=\"YangDong\" filesize=\"1309408\">HS-AgentV2.0����</rec>\
        <rec ver=\"2.1.0.1\" modify=\"2011-11-01 10:08\" programer=\"S..C..\"   filesize=\"1309408\">HS-AgentV2.1����</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2011-12-28 10:08\" programer=\"YangDong\" filesize=\"1309408\">����SApp_DynExecSql SApp_GetPara���</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-8-28 10:08\" programer=\"YangDong\" filesize=\"1309408\">DCI����</rec>\
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

char sSql1[512+1];

/*˽�к�������SApp_GetInfo���ã���ȡ������Ϣ����󱣴���XML����*/
IRESULT GetJYXX(HXMLTREE lXmlhandle, char *Jydm, char *CtrlFlag)
{
    char sJydm[16+1]={0};
    char sbuf[255]={0};
    char sPkey[40+1]={0};
    APP_JYXX sdb_app_jyxx;
    APP_KZSX sdb_app_kzsx;
    char sXmlnode[256]={0};
    char sXmlBuf[512]={0};
    char sCtrlFlag[2]={0};
    int  iRet = -1;
    CURSOR cur;
    char sErrmsg[512];

    memset(&sdb_app_kzsx,0,sizeof(sdb_app_kzsx));
    memset(&sdb_app_jyxx,0,sizeof(sdb_app_jyxx));

    memset(sbuf,0,sizeof(sbuf));
    memset(sJydm,0,sizeof(sJydm));
    memset(sCtrlFlag,0,sizeof(sCtrlFlag));

    strcpy(sJydm,Jydm);
    strcpy(sCtrlFlag,CtrlFlag);

     LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("��ȡ������ϢGetJYXX[%s]",sJydm ),"DEBUG");

    /* ������Ϣ��ȡ --B */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_jyxx WHERE  jydm = '%s'" ,sJydm );
    iRet = fprv_SelToStruct( sSql1, SD_APP_JYXX, NUMELE(SD_APP_JYXX), &sdb_app_jyxx );
    if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡ������Ϣ[%s]����",sJydm),"ERROR");
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴˽�����Ϣ[%s]",sJydm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ���������Ϣ */
    if ( sCtrlFlag[0] == '0' && sdb_app_jyxx.qtbz[0] != '0' ) /* ��ͣ��ʶ0 Ϊ���� */
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg( " ����[%s] ״̬[%s]", sJydm, sdb_app_jyxx.qtbz ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYXX_GB,MSG_APP_JYXX_GB);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* �����������Ϣ */
    else
    {
        COMP_SOFTSETXML(XMLNM_APP_JYXX_JYDM   , trim(sdb_app_jyxx.jydm));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_JYMC   , trim(sdb_app_jyxx.jymc));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_YYBS   , trim(sdb_app_jyxx.yybs));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_JYLX   , trim(sdb_app_jyxx.jylx));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_LSJLBZ , trim(sdb_app_jyxx.lsjlbz));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_RZBZ   , trim(sdb_app_jyxx.rzbz));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_BBBZ   , trim(sdb_app_jyxx.bbbz));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_CPXG   , trim(sdb_app_jyxx.cpxg));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_EXTFLD1, trim(sdb_app_jyxx.extfld1));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_EXTFLD2, trim(sdb_app_jyxx.extfld2));
        COMP_SOFTSETXML(XMLNM_APP_JYXX_QTBZ   , trim(sdb_app_jyxx.qtbz));
    }
    /* ������չ���Ի�ȡ */
    memset(sPkey, 0, sizeof(sPkey));
    memset(sSql1, 0, sizeof(sSql1));
    sprintf(sPkey, "jyxx_%s", sJydm);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);

        /* ����·�� */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_JYXX_KZSX_PATH,sdb_app_kzsx.csmc);

        /* ����ֵ(֧�ֽ����ַ�������) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "������չ����ʧ��" ),"ERROR");
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    DCIFreeCursor(cur);

    return 0;
}

/*˽�к�������SApp_GetInfo���ã���ȡ������Ϣ����󱣴���XML����*/
IRESULT GetQDXX(HXMLTREE lXmlhandle, char *Qdbs, char *CtrlFlag)
{
    char sQdbs[3+1];
    char sbuf[255];
    char sPkey[40+1];
    APP_QDXX sdb_app_qdxx;
    APP_KZSX sdb_app_kzsx;
    CURSOR cur;
    char sErrmsg[512];

    int  iParas;
    char sXmlnode[256];
    char sXmlBuf[512];
    char sOrgLevel[30];
    char sCtrlFlag[2];
    char sLsblts[128],sPdblts[128];
    int  iRet;
    char sSystime[6+1];
    char sJylx[1+1];

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_app_qdxx,0,sizeof(sdb_app_qdxx));
    memset(&sdb_app_kzsx,0,sizeof(sdb_app_kzsx));

    memset(sbuf,0,sizeof(sbuf));
    memset(sQdbs,0,sizeof(sQdbs));
    memset(sCtrlFlag,0,sizeof(sCtrlFlag));

    strcpy(sQdbs,Qdbs);
    strcpy(sCtrlFlag,CtrlFlag);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
        Fmtmsg("��ȡ������ϢGetQDXX[%s]", sQdbs ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_qdxx WHERE  qdbs ='%s'", sQdbs );
    iRet = fprv_SelToStruct( sSql1, SD_APP_QDXX, NUMELE(SD_APP_QDXX), &sdb_app_qdxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡ������Ϣ[%s]����",sQdbs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴�������Ϣ[%s]",sQdbs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_QDXX_NOTFOUND,MSG_APP_QDXX_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ���������Ϣ */
    if ( sCtrlFlag[0] == '0' ) /* ����״̬0 ���� 20130923 ɾ�������� && sdb_app_qdxx.qdzt[0] != '0'  */
    {
        if( sdb_app_qdxx.qdzt[0] != '0' )  /* �������״̬ */
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                 Fmtmsg( " ����[%s] ״̬[%s]", trim( sdb_app_qdxx.qdmc ), sdb_app_qdxx.qdzt ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_QDXX_GB,MSG_APP_QDXX_GB);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* ���ʱ����� */
        if( sdb_app_qdxx.sjkzbz[0] == '0' )
        {
            COMP_HARDGETXML( XMLNM_SYSTIME,sSystime);
            if( ( atoi(sSystime) < atoi( sdb_app_qdxx.qssj ) ) || \
                     ( atoi(sSystime) > atoi(sdb_app_qdxx.jssj) ) )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX_SJ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX_SJ,MSG_APP_CPQDGX_SJ);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
        if( sdb_app_qdxx.czbz[0] == '1' )  /* �������������ף���齻������ */
        {
            COMP_HARDGETXML( XMLNM_APP_JYXX_JYLX ,sJylx );
            if( sJylx[0] == '1' )  /* ������ */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX_CZ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX_CZ,MSG_APP_CPQDGX_CZ);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }

    COMP_SOFTSETXML(XMLNM_APP_QDXX_QDBS    , trim(sdb_app_qdxx.qdbs));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_QDMC    , trim(sdb_app_qdxx.qdmc));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_QDSM    , trim(sdb_app_qdxx.qdsm));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_SJKZBZ  , trim(sdb_app_qdxx.sjkzbz));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_QSSJ    , trim(sdb_app_qdxx.qssj));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_JSSJ    , trim(sdb_app_qdxx.jssj));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_CZBZ    , trim(sdb_app_qdxx.czbz));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_ZDCZBZ  , trim(sdb_app_qdxx.zdczbz));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_EXTFLD1 , trim(sdb_app_qdxx.extfld1));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_EXTFLD2 , trim(sdb_app_qdxx.extfld2));
    COMP_SOFTSETXML(XMLNM_APP_QDXX_QDZT    , trim(sdb_app_qdxx.qdzt));

    /* ������չ������Ϣ */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "qdxx_%s", sQdbs);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);
        /* ����·�� */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_QDXX_KZSX_PATH,sdb_app_kzsx.csmc);

        /* ����ֵ(֧�ֽ����ַ�������) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "������չ����ʧ��" ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*˽�к�������SApp_GetInfo���ã���ȡ������Ϣ����󱣴���XML����*/
IRESULT GetJGXX(HXMLTREE lXmlhandle, char *Jgdm, char *CtrlFlag)
{
    char sJgdm[16+1]={0};
    char sbuf[255]={0};
    char sPkey[40+1]={0};
    char sOrg_id[16+1]={0};
    char sAbove_org_id[16+1]={0};
    char sAboveOrgTmp[16+1]={0};
    T_ORG    sdb_t_org;
    int  iParas;
    char sXmlnode[256];
    char sXmlBuf[512];
    char sOrgLevel[30];
    char sCtrlFlag[2];
    char sLsblts[128],sPdblts[128];
    int i;
    char sSystime[6+1];
    char sJylx[1+1];
    int iRet = -1;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_t_org,0,sizeof(sdb_t_org));

    memset(sbuf,0,sizeof(sbuf));
    memset(sJgdm,0,sizeof(sJgdm));
    memset(sCtrlFlag,0,sizeof(sCtrlFlag));

    strcpy(sJgdm,Jgdm);
    strcpy(sCtrlFlag,CtrlFlag);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
        Fmtmsg("��ȡ������ϢGetJGXX[%s]",sJgdm ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM t_org WHERE  org_id ='%s'", sJgdm );
    iRet = fprv_SelToStruct( sSql1, SD_T_ORG, NUMELE(SD_T_ORG), &sdb_t_org);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡ������Ϣ[%s]����",sJgdm),"ERROR");
        /*DCIRollback(); deleted by chenmx 2015-1-7*/
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,Fmtmsg("����������������Ϣ,[%s]",sJgdm));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML(XMLNM_APP_JGXX_ORG_ID      , trim(sdb_t_org.org_id));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_ORG_NAME    , trim(sdb_t_org.org_name));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_ORG_DESC    , trim(sdb_t_org.org_desc));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_ABOVE_ORG_ID, trim(sdb_t_org.above_org_id));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_INNER_ORG_ID, trim(sdb_t_org.inner_org_id));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_ORG_LEVEL   , sdb_t_org.org_level );
    COMP_SOFTSETXML(XMLNM_APP_JGXX_ORG_ADRESS  , trim(sdb_t_org.org_adress));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_ORG_TYPE    , trim(sdb_t_org.org_type));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_TEL         , trim(sdb_t_org.tel));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_EMAIL       , trim(sdb_t_org.email));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_BAK1        , trim(sdb_t_org.bak1));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_BAK2        , trim(sdb_t_org.bak2));
    COMP_SOFTSETXML(XMLNM_APP_JGXX_BAK3        , trim(sdb_t_org.bak3));

    /* ��ȡ�ϼ�������Ϣ */
    pstrcopy(sAboveOrgTmp,sdb_t_org.above_org_id,sizeof(sAboveOrgTmp));
    /* added 20090716 by yangdong ������һ�� */
    sprintf( sXmlnode, "%s%d",XMLNM_APP_JGXX_ORG_ID, atoi( sdb_t_org.org_level ) );
    COMP_SOFTSETXML( sXmlnode, sdb_t_org.org_id );
    /* end */

    for (i= atoi( sdb_t_org.org_level ) ;i>0;i--)
    {
        memset(sAbove_org_id,0,sizeof(sAbove_org_id));
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT org_id,above_org_id FROM t_org WHERE  org_id = '%s'",sAboveOrgTmp );
        iRet = DBSelectToMultiVarChar(  sErrmsg, sSql1, sOrg_id , sAbove_org_id );
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡ�ϼ�������Ϣ[%s]����",sAboveOrgTmp),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                Fmtmsg("  �������������ϼ�������Ϣ[%s]",sAboveOrgTmp),"ERROR");
            fpub_SetMsg(lXmlhandle, MID_APP_SJJG_NOTFOUND, MSG_APP_SJJG_NOTFOUND );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        memset(sAboveOrgTmp,0,sizeof(sAboveOrgTmp));
        pstrcopy(sAboveOrgTmp,sAbove_org_id,sizeof(sAboveOrgTmp));
        sprintf( sXmlnode, "%s%d",XMLNM_APP_JGXX_ORG_ID, i-1 );
        COMP_SOFTSETXML( sXmlnode, sOrg_id );
    }
    return 0;
}

/*˽�к�������SApp_GetInfo���ã���ȡӦ����Ϣ����󱣴���XML����*/
IRESULT GetYYXX(HXMLTREE lXmlhandle, char *Yybs, char *CtrlFlag)
{
    char sYybs[8+1]={0};
    char sbuf[255]={0};
    char sOrg_id[16+1]={0};
    char sAbove_org_id[16+1]={0};
    char sAboveOrgTmp[16+1]={0};
    char sPkey[40+1]={0};
    APP_YYXX sdb_app_yyxx;
    char sCtrlFlag[2]={0};
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_app_yyxx,0,sizeof(sdb_app_yyxx));

    memset(sbuf,0,sizeof(sbuf));
    memset(sYybs,0,sizeof(sYybs));
    memset(sCtrlFlag,0,sizeof(sCtrlFlag));

    strcpy(sYybs,Yybs);
    strcpy(sCtrlFlag,CtrlFlag);

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_yyxx WHERE  yybs ='%s'", sYybs );
    iRet = fprv_SelToStruct( sSql1, SD_APP_YYXX, NUMELE(SD_APP_YYXX), &sdb_app_yyxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡӦ����Ϣ[%s]����",sYybs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴�Ӧ����Ϣ[%s]",sYybs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_YYXX_NOTFOUND,MSG_APP_YYXX_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ���������Ϣ */
    if ( sCtrlFlag[0] == '0' && sdb_app_yyxx.yyzt[0] != '0' ) /* Ӧ��״̬0 ���� */
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_YYXX_GB),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_YYXX_GB,MSG_APP_YYXX_GB);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* �����������Ϣ */
    else
    {
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYBS     , trim(sdb_app_yyxx.yybs));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYMC     , trim(sdb_app_yyxx.yymc));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYKFKSRQ , trim(sdb_app_yyxx.yykfksrq));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYKFJSRQ , trim(sdb_app_yyxx.yykfjsrq));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYFBRQ   , trim(sdb_app_yyxx.yyfbrq));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYBBH    , trim(sdb_app_yyxx.yybbh));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YHH      , trim(sdb_app_yyxx.yhh));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_SQH      , trim(sdb_app_yyxx.sqh));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYKFJL   , trim(sdb_app_yyxx.yykfjl));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYZBJL   , trim(sdb_app_yyxx.yyzbjl));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_YYZT     , trim(sdb_app_yyxx.yyzt));
        COMP_SOFTSETXML(XMLNM_APP_YYXX_EXTFLD   , trim(sdb_app_yyxx.extfld));
    }
    return 0;
}

/*˽�к�������SApp_GetInfo���ã���ȡ��λ��ƷЭ����Ϣ����󱣴���XML����*/
IRESULT GetDWCPXY(HXMLTREE lXmlhandle, char *Ywbh, char *CtrlFlag)
{
    char sYwbh[16+1]={0};
    char sbuf[255]={0};
    char sZhzded[20+1]={0};
    char sPkey[40+1]={0};
    APP_DWCPXY sdb_app_dwcpxy;
    APP_KZSX   sdb_app_kzsx;
    char sXmlnode[256]={0};
    char sXmlBuf[512]={0};
    char sCtrlFlag[2]={0};
    char sJyrq[8+1];
    int  iRet = -1;
    char sErrmsg[512];
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_app_dwcpxy,0,sizeof(sdb_app_dwcpxy));
    memset(&sdb_app_kzsx,0,sizeof(sdb_app_kzsx));

    memset(sbuf,0,sizeof(sbuf));
    memset(sYwbh,0,sizeof(sYwbh));
    memset(sCtrlFlag,0,sizeof(sCtrlFlag));

    strcpy(sYwbh,Ywbh);
    strcpy(sCtrlFlag,CtrlFlag);

    LOG(LM_DEBUG,Fmtmsg("��ȡ��λ��ƷЭ����ϢGetDWCPXY[%s]",sYwbh ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_dwcpxy WHERE  ywbh ='%s'", sYwbh );
    iRet = fprv_SelToStruct( sSql1, SD_APP_DWCPXY, NUMELE(SD_APP_DWCPXY), &sdb_app_dwcpxy);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡ��λ��ƷЭ����Ϣ[%s]����",sYwbh),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴˵�λ��ƷЭ����Ϣ[%s]",sYwbh),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_YWBH_NOTFOUND,MSG_APP_YWBH_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ���������Ϣ */
    if ( sCtrlFlag[0] == '0' )
    {
        if( sdb_app_dwcpxy.qyzt[0] != '0' )
        {
            fpub_SetMsg(lXmlhandle,MID_APP_CPXX_ZT,MSG_APP_CPXX_ZT);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
#if 0
/* mod 20171124 �����Ե�λǩԼ��Ч�ڲ������жϣ������ѯʱ���ʧЧ��λ������ʾ */
        /* added by yangdong 20111028 ���Ӷ���Ч���ڣ�ʧЧ�����ж�,����δ�������ж� */
        trim( sdb_app_dwcpxy.hyksrq );
        if( strlen( sdb_app_dwcpxy.hyksrq ) == 8 )
        {
            memset( sJyrq, 0x00, sizeof( sJyrq ) );
            COMP_SOFTGETXML( XMLNM_ZWRQ, sJyrq );
            if( atoi( sJyrq ) < atoi( sdb_app_dwcpxy.hyksrq ) ) /* ��δ��Ч */
            {
                fpub_SetMsg(lXmlhandle,MID_APP_DWCPXY_HYKSRQ,\
                    Fmtmsg(MSG_APP_DWCPXY_HYKSRQ, sdb_app_dwcpxy.hyksrq));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
        trim( sdb_app_dwcpxy.hyjsrq );
        if( strlen( sdb_app_dwcpxy.hyjsrq ) == 8 )
        {
            memset( sJyrq, 0x00, sizeof( sJyrq ) );
            COMP_SOFTGETXML( XMLNM_ZWRQ, sJyrq );
            if( atoi( sJyrq ) >= atoi( sdb_app_dwcpxy.hyjsrq ) ) /* ��ʧЧ */
            {
                fpub_SetMsg(lXmlhandle,MID_APP_DWCPXY_HYJSRQ,\
                    Fmtmsg(MSG_APP_DWCPXY_HYJSRQ, sdb_app_dwcpxy.hyjsrq));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
        /* end of add */
#endif
    }
    trim(sdb_app_dwcpxy.dwbh);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DWBH   , sdb_app_dwcpxy.dwbh);
    trim(sdb_app_dwcpxy.cpdm);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_CPDM   , sdb_app_dwcpxy.cpdm);
    trim(sdb_app_dwcpxy.ywbh);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_YWBH   , sdb_app_dwcpxy.ywbh);
    trim(sdb_app_dwcpxy.ywmc);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_YWMC   , sdb_app_dwcpxy.ywmc);
    trim(sdb_app_dwcpxy.xybh);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_XYBH   , sdb_app_dwcpxy.xybh);
    trim(sdb_app_dwcpxy.yhdm);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_YHDM   , sdb_app_dwcpxy.yhdm);
    trim(sdb_app_dwcpxy.ljbs);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_LJBS   , sdb_app_dwcpxy.ljbs);
    trim(sdb_app_dwcpxy.zhlx);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_ZHLX   , sdb_app_dwcpxy.zhlx);
    
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_SFBZ,    trim(sdb_app_dwcpxy.sfbz));/*�ո���ʶ*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DSZH   , trim(sdb_app_dwcpxy.dszh));/*�����˻�*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DSZHMC   , trim(sdb_app_dwcpxy.dszhmc));/*�����˻�����*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DFZH   , trim(sdb_app_dwcpxy.dfzh));/*�����˻�*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DFZHMC   , trim(sdb_app_dwcpxy.dfzhmc));/*�����˻�����*/
    
    trim(sdb_app_dwcpxy.khjl);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_KHJL   , sdb_app_dwcpxy.khjl);
    trim(sdb_app_dwcpxy.lxr);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_LXR    , sdb_app_dwcpxy.lxr);
    trim(sdb_app_dwcpxy.email);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_EMAIL  , sdb_app_dwcpxy.email);
    trim(sdb_app_dwcpxy.lxdh);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_LXDH   , sdb_app_dwcpxy.lxdh);
    trim(sdb_app_dwcpxy.hyksrq);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_HYKSRQ , sdb_app_dwcpxy.hyksrq);
    trim(sdb_app_dwcpxy.hyjsrq);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_HYJSRQ , sdb_app_dwcpxy.hyjsrq);
    trim(sdb_app_dwcpxy.bljg);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_BLJG   , sdb_app_dwcpxy.bljg);
    trim(sdb_app_dwcpxy.blgy);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_BLGY   , sdb_app_dwcpxy.blgy);
    trim(sdb_app_dwcpxy.blrq);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_BLRQ   , sdb_app_dwcpxy.blrq);
    memset(sZhzded,0x00,sizeof(sZhzded));
    sprintf(sZhzded,"%f",sdb_app_dwcpxy.zhzded);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_ZHZDED , sZhzded);
    trim(sdb_app_dwcpxy.extfld1);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_EXTFLD1 ,sdb_app_dwcpxy.extfld1);
    trim(sdb_app_dwcpxy.extfld2);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_EXTFLD2 ,sdb_app_dwcpxy.extfld2);
    trim(sdb_app_dwcpxy.qyzt);
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_QYZT   , sdb_app_dwcpxy.qyzt);

    /* ��λ��ƷЭ����չ������Ϣ */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "dwcpxy_%s", sYwbh);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);

        /* ����·�� */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_DWCPXY_KZSX_PATH,sdb_app_kzsx.csmc);

        /* ����ֵ(֧�ֽ����ַ�������) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "������չ����ʧ��" ),"ERROR");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    return 0;
}

/*˽�к�������SApp_GetInfo���ã���ȡͨѶ��Ϣ����󱣴���XML����*/
IRESULT GetTXXX(HXMLTREE lXmlhandle, char *Txdm, char *CtrlFlag)
{
    char sTxdm[21]={0};
    char sbuf[255]={0};
    char sPkey[40+1]={0};
    APP_TXAQXX sdb_app_txaqxx;
    APP_KZSX   sdb_app_kzsx;
    char sXmlnode[256]={0};
    char sXmlBuf[512]={0};
    char sOrgLevel[30]={0};
    char sCtrlFlag[2]={0};
    int  iRet = -1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_app_txaqxx,0,sizeof(sdb_app_txaqxx));
    memset(&sdb_app_kzsx,0,sizeof(sdb_app_kzsx));

    memset(sbuf,0,sizeof(sbuf));
    memset(sTxdm,0,sizeof(sTxdm));
    memset(sCtrlFlag,0,sizeof(sCtrlFlag));

    strcpy(sTxdm,Txdm);
    strcpy(sCtrlFlag,CtrlFlag);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
        Fmtmsg("��ȡͨѶ��ϢGetTXXX[%s]",sTxdm ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_txaqxx WHERE  ljbs ='%s'", sTxdm );
    iRet = fprv_SelToStruct( sSql1, SD_APP_TXAQXX, NUMELE(SD_APP_TXAQXX), &sdb_app_txaqxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡͨѶ��Ϣ[%s]����",sTxdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴�ͨѶ��Ϣ[%s]",sTxdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ͨѶ״̬ 0���� 1ǩ�� 2ǩ�� 9��Ч */
    if ( sCtrlFlag[0] == '0' && ( sdb_app_txaqxx.txzt[0] != '0' &&  sdb_app_txaqxx.txzt[0] != '2'  ) )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("  ͨѶ״̬ [%s]", sdb_app_txaqxx.txzt ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_TXAQXX_WX, MSG_APP_TXAQXX_WX );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*��ȡ�������ݽ��д���*/
    trim(sdb_app_txaqxx.ljbs);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJBS     , sdb_app_txaqxx.ljbs);
    trim(sdb_app_txaqxx.ljmc);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJMC     , sdb_app_txaqxx.ljmc);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJLX     , sdb_app_txaqxx.ljlx);
    trim(sdb_app_txaqxx.dwbh);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_DWBH     , sdb_app_txaqxx.dwbh);
    trim(sdb_app_txaqxx.qdkz);/* ǩ������ */
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_QDKZ     , sdb_app_txaqxx.qdkz);
    trim(sdb_app_txaqxx.txms);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_TXMS     , sdb_app_txaqxx.txms);
    trim(sdb_app_txaqxx.txdz);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_TXDZ     , sdb_app_txaqxx.txdz);
    trim(sdb_app_txaqxx.txdk);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_TXDK     , sdb_app_txaqxx.txdk);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FSCS     , itoa(sdb_app_txaqxx.fscs));
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_JSCS     , itoa(sdb_app_txaqxx.jscs));
    trim(sdb_app_txaqxx.ljjgh);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJJGH    , sdb_app_txaqxx.ljjgh);
    trim(sdb_app_txaqxx.ljgyh);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJGYH    , sdb_app_txaqxx.ljgyh);
    trim(sdb_app_txaqxx.ljzdh);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJZDH    , sdb_app_txaqxx.ljzdh);

    trim(sdb_app_txaqxx.key1);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_KEY1   , sdb_app_txaqxx.key1);
    trim(sdb_app_txaqxx.key2);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_KEY2   , sdb_app_txaqxx.key2);
    trim(sdb_app_txaqxx.key3);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_KEY3  , sdb_app_txaqxx.key3);

    trim(sdb_app_txaqxx.ftpdz);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPDZ, sdb_app_txaqxx.ftpdz);
    trim(sdb_app_txaqxx.ftpyh);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPYH, sdb_app_txaqxx.ftpyh);
    trim(sdb_app_txaqxx.ftpmm);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPMM, sdb_app_txaqxx.ftpmm);
    trim(sdb_app_txaqxx.ftpgzfs);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPGZFS, sdb_app_txaqxx.ftpgzfs);
    trim(sdb_app_txaqxx.ftpcsfs);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPCSFS, sdb_app_txaqxx.ftpcsfs);
    trim(sdb_app_txaqxx.ftpzdms);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPZDMS, sdb_app_txaqxx.ftpzdms);
    trim(sdb_app_txaqxx.ftpdflj);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPDFLJ, sdb_app_txaqxx.ftpdflj);
    trim(sdb_app_txaqxx.ftpbdlj);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_FTPBDLJ, sdb_app_txaqxx.ftpbdlj);

    trim(sdb_app_txaqxx.extfld1);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_EXTFLD1  , sdb_app_txaqxx.extfld1);
    trim(sdb_app_txaqxx.extfld2);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_EXTFLD2  , sdb_app_txaqxx.extfld2);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_TXZT     , sdb_app_txaqxx.txzt);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_QDZT     , sdb_app_txaqxx.qdzt);

    /* ͨѶ��չ������Ϣ */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "txxx_%s", sTxdm);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);
        /* ����·�� */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_TXAQXX_PATH,sdb_app_kzsx.csmc);

        /* ����ֵ(֧�ֽ����ַ�������) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "������չ����ʧ��" ),"ERROR");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*˽�к�������SApp_GetInfo���ã���ȡ��λ��Ϣ����󱣴���XML����*/
IRESULT GetDWXX(HXMLTREE lXmlhandle, char *Dwbh, char *CtrlFlag)
{
    char sDwbh[16+1]={0};
    char sOrg_id[16+1]={0};
    char sAbove_org_id[16+1]={0};
    char sAboveOrgTmp[16+1];
    char sPkey[40+1]={0};
    APP_DWXX sdb_app_dwxx;
    APP_KZSX sdb_app_kzsx;
    char sXmlnode[256]={0};
    char sbuf[255]={0};
    char sXmlBuf[512]={0};
    char sOrgLevel[30]={0};
    char sCtrlFlag[2]={0};
    int  iRet = -1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_app_dwxx,0,sizeof(sdb_app_dwxx));
    memset(&sdb_app_kzsx,0,sizeof(sdb_app_kzsx));

    memset(sbuf,0,sizeof(sbuf));
    memset(sDwbh,0,sizeof(sDwbh));
    memset(sCtrlFlag,0,sizeof(sCtrlFlag));

    strcpy(sDwbh,Dwbh);
    strcpy(sCtrlFlag,CtrlFlag);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,\
        Fmtmsg("��ȡ��λ��ϢGetDWXX[%s]",sDwbh ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_dwxx WHERE  dwbh='%s'", sDwbh );
    iRet = fprv_SelToStruct( sSql1, SD_APP_DWXX, NUMELE(SD_APP_DWXX), &sdb_app_dwxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡ��λ��Ϣ[%s]����",sDwbh),"ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴˵�λ��Ϣ[%s]",sDwbh),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_DWXX_NOTFOUND,MSG_APP_DWXX_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    trim( sdb_app_dwxx.dwbh );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWBH ,    sdb_app_dwxx.dwbh );
    trim( sdb_app_dwxx.dwmc );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWMC ,    sdb_app_dwxx.dwmc );
    
    trim( sdb_app_dwxx.dwzjlx );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWZJLX ,    sdb_app_dwxx.dwzjlx );
    trim( sdb_app_dwxx.dwzjhm );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWZJHM ,    sdb_app_dwxx.dwzjhm );
    trim( sdb_app_dwxx.dwlxr );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWLXR ,    sdb_app_dwxx.dwlxr );
    trim( sdb_app_dwxx.dwlxrdh );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWLXRDH ,    sdb_app_dwxx.dwlxrdh );
    
    trim( sdb_app_dwxx.dwdz );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWDZ ,    sdb_app_dwxx.dwdz );
    trim( sdb_app_dwxx.dwemail );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_DWEMAIL ,    sdb_app_dwxx.dwemail );
    trim( sdb_app_dwxx.extfld1 );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_EXTFLD1 ,    sdb_app_dwxx.extfld1 );
    trim( sdb_app_dwxx.extfld2 );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_EXTFLD2 ,    sdb_app_dwxx.extfld2 );
    trim( sdb_app_dwxx.zt );
    COMP_SOFTSETXML( XMLNM_APP_DWXX_ZT ,    sdb_app_dwxx.zt );

    /* ��չ���� */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "dwxx_%s", sDwbh);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);

        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_DWXX_KZSX_PATH,sdb_app_kzsx.csmc);

        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "������չ����ʧ��" ),"ERROR");
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*˽�к�������SApp_GetInfo���ã���ȡ��Ʒ��Ϣ����󱣴���XML����*/
IRESULT GetCPXX(HXMLTREE lXmlhandle, char *Cpdm, char *CtrlFlag)
{
    char sCpdm[16+1]={0};
    char sbuf[255]={0};
    char sLsblts[128]={0};
    char sPdblts[128]={0};
    char sPkey[40+1]={0};
    APP_CPXX sdb_app_cpxx;
    APP_KZSX sdb_app_kzsx;
    char sXmlnode[256]={0};
    char sXmlBuf[512]={0};
    char sCtrlFlag[2]={0};
    int iRet = -1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    memset(&sdb_app_cpxx,0,sizeof(sdb_app_cpxx));
    memset(&sdb_app_kzsx,0,sizeof(sdb_app_kzsx));

    strcpy(sCpdm,Cpdm);
    strcpy(sCtrlFlag,CtrlFlag);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("��ȡ��Ʒ��Ϣ[%s]",sCpdm),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_cpxx WHERE  cpdm='%s'", sCpdm ) ;
    iRet = fprv_SelToStruct( sSql1, SD_APP_CPXX, NUMELE(SD_APP_CPXX), &sdb_app_cpxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡ��Ʒ��Ϣ[%s]����",sCpdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴˲�Ʒ��Ϣ[%s]",sCpdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_CPDM_NOTFOUND,MSG_APP_CPDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ���������Ϣ */
    if ( sCtrlFlag[0] == '0' && sdb_app_cpxx.cpzt[0] != '0' )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_CPXX_ZT,MSG_APP_CPXX_ZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    COMP_SOFTSETXML(XMLNM_APP_CPXX_CPDM   , trim(sdb_app_cpxx.cpdm));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_CPMC   , trim(sdb_app_cpxx.cpmc));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_YYBS   , trim(sdb_app_cpxx.yybs));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_ZBJG   , trim(sdb_app_cpxx.zbjg));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_ZBGY   , trim(sdb_app_cpxx.zbgy));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_KHJL   , trim(sdb_app_cpxx.khjl));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_YWRQLX , trim(sdb_app_cpxx.ywrqlx));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_QDKZBZ , trim(sdb_app_cpxx.qdkzbz));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_JGKZCS , trim(sdb_app_cpxx.jgkzcs));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_SXFBZ  , trim(sdb_app_cpxx.sxfbz));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_SFQYBZ , trim(sdb_app_cpxx.sfqybz));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_XYXLJZ , trim(sdb_app_cpxx.xyxljz));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_DZMS   , trim(sdb_app_cpxx.dzms));

    sprintf(sLsblts, "%d", sdb_app_cpxx.lsblts);
    COMP_SOFTSETXML(XMLNM_APP_CPXX_LSBLTS , sLsblts);
    sprintf(sPdblts, "%d", sdb_app_cpxx.pdblts);
    COMP_SOFTSETXML(XMLNM_APP_CPXX_PDBLCS , sPdblts);

    COMP_SOFTSETXML(XMLNM_APP_CPXX_JYFS   , trim(sdb_app_cpxx.jyfs));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_EXTFLD1, trim(sdb_app_cpxx.extfld1));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_EXTFLD2, trim(sdb_app_cpxx.extfld2));
    COMP_SOFTSETXML(XMLNM_APP_CPXX_CPZT   , trim(sdb_app_cpxx.cpzt));
    
    /*add by SC 20110530,��Ʒ��Ϣ��ģ���޸�*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_QYMS,    trim(sdb_app_cpxx.qyms));/*ǩԼģʽ*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_JZSX,    trim(sdb_app_cpxx.jzsx));/*����˳��*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_KKFS,    trim(sdb_app_cpxx.kkfs));/*�ۿʽ*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_ZJYYH,   trim(sdb_app_cpxx.zjyyh));/*����Ӧ�ú�*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_ZJZYYH,  trim(sdb_app_cpxx.zjzyyh));/*������Ӧ�ú�*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_RZMS,    trim(sdb_app_cpxx.rzms));/*��־ģʽ*/

    /* ��Ʒ��չ������Ϣ */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "cpxx_%s", sCpdm);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);

        /* ����·�� */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_CPXX_KZSX_PATH,sdb_app_kzsx.csmc);

        /* ����ֵ(֧�ֽ����ַ�������) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "������չ����ʧ��" ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*˽�к�������ȡ��Ʒ���׷�����Ϣ����󱣴��ڽṹ����*/
IRESULT GetKHCPQYXX(HXMLTREE lXmlhandle, char *Cpdm, char *Jydm, char *Jyje, char*Yhh)
{
    char sCpdm[16+1]={0};
    char sJydm[16+1]={0};
    char sYhh[32+1]={0};
    APP_CPJYFW sdb_app_cpjyfw;
    APP_KHCPQY sdb_app_khcpqy;

    char sSystime[6+1]={0};
    char sZhzded[128]={0};
    char *pstr1;
    char sQdbs[3+1]={0};
    double dJyje=0.00;
    int iRet = -1;
    CURSOR cur;
    char sErrmsg[512];

    memset(&sdb_app_cpjyfw,0,sizeof(APP_CPJYFW));
    memset(&sdb_app_khcpqy,0,sizeof(APP_KHCPQY));
    strcpy(sCpdm,Cpdm);
    strcpy(sJydm,Jydm);
    strcpy(sYhh, Yhh);

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    /* ���жϲ�Ʒ���׷�����Ϣ�Ƿ�����Ҫ�� */
    snprintf( sSql1, sizeof( sSql1 ), "SELECT  * FROM app_cpjyfw WHERE  cpdm ='%s' AND jydm='%s'", sCpdm, sJydm );
    iRet = fprv_SelToStruct( sSql1, SD_APP_CPJYFW, NUMELE(SD_APP_CPJYFW), &sdb_app_cpjyfw);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ʒ���׷�����Ϣ����", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
            Fmtmsg("  ��Ʒ[%s]���׷���[%s]��ϵ������", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ����ʱ����Ʊ�־ 0���� 1������ */
    if( 0 == memcmp(sdb_app_cpjyfw.sjkzbz,"0",1) )
    {
        COMP_HARDGETXML(XMLNM_SYSTIME,sSystime);
        if( ( atoi(sSystime) < atoi(sdb_app_cpjyfw.qssj) ) || 
            ( atoi(sSystime) > atoi(sdb_app_cpjyfw.jssj) ) )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJYFW_SJ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_CPJYFW_SJ,MSG_APP_CPJYFW_SJ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /* �޶���� */
    if( 0 == memcmp(sdb_app_cpjyfw.xekzbz,"0",1) )
    {
        if( strlen(Jyje) <= 0)
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJYFW_JYJE),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_CPJYFW_JYJE,MSG_APP_CPJYFW_JYJE);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        dJyje=atof(Jyje);
        if( (dJyje<sdb_app_cpjyfw.zxxe) || (dJyje>sdb_app_cpjyfw.zdxe) )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJYFW_JYXE),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_CPJYFW_JYXE,MSG_APP_CPJYFW_JYXE);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /* -------------��Ʒ�ͻ�ǩԼ��ϵ���� ��ʼ----------------*/
    if(0 == memcmp(sdb_app_cpjyfw.qykzbz,"0",1) ) /* 0���� 1 ������ */
    {
        if( strlen( sYhh ) <= 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* �� �û���+��Ʒ���� ��ѯ */

        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT  * FROM app_khcpqy\
             WHERE  cpdm ='%s' AND yhh1 ='%s'",sCpdm, sYhh );
        iRet = fprv_SelToStruct( sSql1, SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡǩԼ��Ϣ[%s]����",sYhh),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡǩԼ��Ϣ[%s]ʧ��",sYhh),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND,MSG_APP_QY_NOTFOUND );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        trim( sdb_app_khcpqy.qyzt );
        if( sdb_app_khcpqy.qyzt[0] != '0' ) /*0���� 1����*/
        {
            fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY,MSG_APP_KHCPQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* ǩԼ��ͨ������� */
        COMP_HARDGETXML(XMLNM_APP_QDXX_QDBS,sQdbs);
        if ( ( (pstr1=strstr(sdb_app_khcpqy.ktqd,sQdbs)) == NULL ) &&
               (0 != memcmp(sdb_app_khcpqy.ktqd,"ALL",3) ) )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_KHCPQY_KTQD),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY_KTQD,MSG_APP_KHCPQY_KTQD);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        trim(sdb_app_khcpqy.xybh);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_XYBH   ,sdb_app_khcpqy.xybh);
        trim(sdb_app_khcpqy.cpdm);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_CPDM   ,sdb_app_khcpqy.cpdm);
        trim(sdb_app_khcpqy.ywbh);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YWBH   ,sdb_app_khcpqy.ywbh);
        trim(sdb_app_khcpqy.zhlx);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZHLX   ,sdb_app_khcpqy.zhlx);
        trim(sdb_app_khcpqy.qyzh);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_QYZH   ,sdb_app_khcpqy.qyzh);
        trim(sdb_app_khcpqy.zhhm);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZHHM   ,sdb_app_khcpqy.zhhm);
        trim(sdb_app_khcpqy.zjlx);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZJLX   ,sdb_app_khcpqy.zjlx);
        trim(sdb_app_khcpqy.zjhm);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZJHM   ,sdb_app_khcpqy.zjhm);
        trim(sdb_app_khcpqy.qylx);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_QYLX   ,sdb_app_khcpqy.qylx);
        trim(sdb_app_khcpqy.khjl);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_KHJL   ,sdb_app_khcpqy.khjl);
        trim(sdb_app_khcpqy.hyksrq);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_HYKSRQ ,sdb_app_khcpqy.hyksrq);
        trim(sdb_app_khcpqy.hyjsrq);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_HYJSRQ ,sdb_app_khcpqy.hyjsrq);
        trim(sdb_app_khcpqy.ktqd);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_KTQD   ,sdb_app_khcpqy.ktqd);
        trim(sdb_app_khcpqy.bljg);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_BLJG   ,sdb_app_khcpqy.bljg);
        trim(sdb_app_khcpqy.blgy);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_BLGY   ,sdb_app_khcpqy.blgy);
        trim(sdb_app_khcpqy.blrq);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_BLRQ   ,sdb_app_khcpqy.blrq);
        trim(sdb_app_khcpqy.yhh1);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YHH1   ,sdb_app_khcpqy.yhh1);
        trim(sdb_app_khcpqy.yhh2);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YHH2   ,sdb_app_khcpqy.yhh2);
        trim(sdb_app_khcpqy.yhh3);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YHH3   ,sdb_app_khcpqy.yhh3);
        trim(sdb_app_khcpqy.dxtzbz);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_DXTZBZ ,sdb_app_khcpqy.dxtzbz);

        memset(sZhzded,0,sizeof(sZhzded));
        sprintf(sZhzded,"%f",sdb_app_khcpqy.zhzded);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZHZDED ,sZhzded );
        trim(sdb_app_khcpqy.extfld1);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_EXTFLD1,sdb_app_khcpqy.extfld1);
        trim(sdb_app_khcpqy.extfld2);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_EXTFLD2,sdb_app_khcpqy.extfld2);
        trim(sdb_app_khcpqy.extfld3);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_EXTFLD3,sdb_app_khcpqy.extfld3);
        trim(sdb_app_khcpqy.qyzt);
        COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_QYZT   ,sdb_app_khcpqy.qyzt);
    }
    return 0;
}

/*˽�к�������ȡ��Ʒ���׹�ԱȨ�ޣ���󱣴��ڽṹ����*/
IRESULT GetCPJYGYKZ(HXMLTREE lXmlhandle, APP_CPJYGYKZ *app_cpjygykz, char *Cpdm, char *Jydm)
{
    char sCpdm[16+1]={0};
    int iRet = -1;
    char sJydm[16+1]={0};
    APP_CPJYGYKZ sdb_app_cpjygykz;
    memset(&sdb_app_cpjygykz,0x00,sizeof(sdb_app_cpjygykz));
    strcpy(sCpdm,Cpdm);
    strcpy(sJydm,Jydm);
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("Cpdm=[%s]sJydm=[%s]GetCPJYGYKZ",sCpdm,sJydm),"DEBUG");
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_cpjygykz WHERE cpdm='%s' AND jydm='%s'",sCpdm, sJydm );
    iRet = fprv_SelToStruct( sSql1, SD_APP_CPJYGYKZ, NUMELE(SD_APP_CPJYGYKZ), &sdb_app_cpjygykz);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ʒ���׹�Ա������Ϣ����", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
            Fmtmsg("��Ʒ[%s]����[%s]δ���ù�Ա����Ȩ�޿�����Ϣ", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_cpjygykz, &sdb_app_cpjygykz, sizeof(sdb_app_cpjygykz));
    return 0;
}
/*˽�к�������ȡ��Ʒ���׹�Ա��ȣ���󱣴��ڽṹ����*/
IRESULT GetCPJYGYED(HXMLTREE lXmlhandle, APP_CPJYGYED *app_cpjygyed, char *Cpdm, char *Jydm, char *Gyjb)
{
    char sCpdm[16+1]={0};
    char sJydm[16+1]={0};
    char sGyjb[2+1]={0};
    int  iRet = -1;
    APP_CPJYGYED sdb_app_cpjygyed;
    memset(&sdb_app_cpjygyed,0x00,sizeof(sdb_app_cpjygyed));
    strcpy(sCpdm,Cpdm);
    strcpy(sJydm,Jydm);
    strcpy(sGyjb,Gyjb);
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("Cpdm=[%s]sJydm=[%s]sGyjb=[%s]",sCpdm,sJydm,sGyjb),"DEBUG");
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_cpjygyed WHERE \
        cpdm='%s'AND jydm='%s' AND gyjb='%s' AND jybz='CNY' ",sCpdm, sJydm, sGyjb );
    iRet = fprv_SelToStruct( sSql1, SD_APP_CPJYGYED, NUMELE(SD_APP_CPJYGYED), &sdb_app_cpjygyed);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ʒ���׹�Ա�����Ϣ����", "ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
            Fmtmsg("��Ʒ[%s]����[%s]δ���ù�Ա�����ȿ�����Ϣ", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_cpjygyed, &sdb_app_cpjygyed, sizeof(sdb_app_cpjygyed));
    return 0;
}

/*˽�к�������ȡ��Ʒ���׻�����ȣ���󱣴��ڽṹ����*/
IRESULT GetCPJYJGED(HXMLTREE lXmlhandle, APP_CPJYJGED *app_cpjyjged, char *Cpdm, char *Jydm, char *Jgjb)
{
    int iRet = -1;
    char sCpdm[16+1]={0};
    char sJydm[16+1]={0};
    char sJgjb[16+1]={0};
    APP_CPJYJGED sdb_app_cpjyjged;
    memset(&sdb_app_cpjyjged,0x00,sizeof(sdb_app_cpjyjged));
    strcpy(sCpdm,Cpdm);
    strcpy(sJydm,Jydm);
    strcpy(sJgjb,Jgjb);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
        Fmtmsg("Cpdm=[%s]sJydm=[%s]jgjb[%s]GetCPJYJGED",sCpdm,sJydm,sJgjb),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpjyjged \
        WHERE cpdm='%s' AND jydm='%s' AND jgjb='%s' AND jybz='CNY'", sCpdm, sJydm, sJgjb );
    iRet = fprv_SelToStruct( sSql1, SD_APP_CPJYJGED, NUMELE(SD_APP_CPJYJGED), &sdb_app_cpjyjged);
    if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ʒ���׻��������Ϣ����", "ERROR");
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
              Fmtmsg("��Ʒ[%s]����[%s]δ���û��������ȿ�����Ϣ", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_cpjyjged, &sdb_app_cpjyjged, sizeof(sdb_app_cpjyjged));
    return 0;
}

/*˽�к�������ȡ���׹�Ա��Ϣ����󱣴���XML����*/
IRESULT GetGYXX(HXMLTREE lXmlhandle, APP_GYXX *app_gyxx, char *Gyh, char *Jgbh)
{
    int iRet = -1;
    char sGyh[16+1]={0};
    char sJgbh[16+1]={0};
    APP_GYXX sdb_app_gyxx;
    memset(&sdb_app_gyxx,0x00,sizeof(sdb_app_gyxx));
    strcpy(sGyh,Gyh);
    strcpy(sJgbh,Jgbh);

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_gyxx WHERE gyh='%s' AND jgbh='%s' AND zt='0'",sGyh,sJgbh );
    iRet = fprv_SelToStruct( sSql1, SD_APP_GYXX, NUMELE(SD_APP_GYXX), &sdb_app_gyxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ա��Ϣ����", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("δ���ù�Ա��Ϣ[%s][%s]��״̬������",sJgbh, sGyh ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_GY_NOTFOUND,MSG_APP_GY_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_gyxx, &sdb_app_gyxx, sizeof(sdb_app_gyxx));
    return 0;
}

/*˽�к�������ȡ���׹�Ա�ա����ۼƽ��,type 1:���գ� 2:���£����Σ�Ljje*/
IRESULT GetGYLJJE(HXMLTREE lXmlhandle, char *Gyh, char *Jgbh, char *Cpdm, char *Date, int type, double *Ljje)
{
    char sGyh[16+1]={0};
    char sJgbh[16+1]={0};
    char sDate[8+1]={0};
    char sEdate[8+1]={0};
    char sCpdm[16+1]={0};
    char sBuf[128+1]={0};
    char sErrmsg[512];
    double dLjje=0;
    int iRet = -1;

    strcpy(sGyh, Gyh);
    strcpy(sJgbh, Jgbh);
    strcpy(sDate, Date);
    strcpy(sEdate, Date);
    strcpy(sCpdm, Cpdm);

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    if (type == 1)
    {
        snprintf( sSql1, sizeof( sSql1 ),"SELECT NVL(sum(jyje),0.00) FROM app_drls\
            WHERE jygy='%s' AND jyjg='%s' AND cpdm='%s' AND jylx='0' AND \
                  rzbz='0' AND jyzt='0' AND ptrq='%s'", sGyh, sJgbh, sCpdm, sDate );
    }
    else if (type == 2)
    {
        memcpy(sDate+6,"01",2);
        memcpy(sEdate+6,"31",2);

        snprintf( sSql1, sizeof( sSql1 ),"SELECT NVL(sum(jyje),0.00) FROM app_drls\
            WHERE jygy = :sGyh AND jyjg=:sJgbh AND cpdm=:sCpdm AND jylx='0'\
            AND rzbz='0' AND jyzt='0' AND ptrq>='%s' AND ptrq<='%s'", sGyh, sJgbh, sCpdm, sDate, sEdate);
    }
    else
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset( sBuf, 0x00, sizeof( sBuf ) );
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ա�ۼƽ��׽����Ϣ����", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    *Ljje = atof( sBuf );
    return 0;
}

/*˽�к�������ȡ���׻����ա����ۼƽ��,type 1:���գ� 2:���£����Σ�Ljje*/
IRESULT GetJGLJJE(HXMLTREE lXmlhandle, char *Jyjg, char *Cpdm, char *Date, int type, double *Ljje)
{
    char sJyjg[16+1]={0};
    char sDate[8+1]={0};
    char sEdate[8+1]={0};
    char sCpdm[16+1]={0};
    double dLjje=0;
    char sBuf[128+1]={0};
    char sErrmsg[512];
    int iRet = -1;

    strcpy(sJyjg, Jyjg);
    strcpy(sDate, Date);
    strcpy(sEdate, Date);
    strcpy(sCpdm, Cpdm);

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    if (type == 1)
    {
        snprintf( sSql1, sizeof( sSql1 ), "SELECT NVL(sum(jyje),0.00) FROM app_drls\
            WHERE jyjg = '%s' AND cpdm='%s' AND jylx='0' AND rzbz='0'\
            AND rzbz='0' AND jyzt='0' AND ptrq=='%s'", sJyjg , sCpdm, sDate );
    }
    else if (type == 2)
    {
        memcpy(sDate+6,"01",2);
        memcpy(sEdate+6,"31",2);
        snprintf( sSql1, sizeof( sSql1 ), "SELECT NVL(sum(jyje),0.00) FROM app_drls\
            WHERE jyjg = '%s' AND cpdm='%s' AND jylx='0' AND rzbz='0'\
            AND rzbz='0' AND jyzt='0' AND ptrq>='%s' AND ptrq<='%s'", sJyjg , sCpdm, sDate, sEdate);
    }
    else
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ�����ۼƽ��׽����Ϣ����", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    *Ljje = atof( sBuf );
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("�����ۼƽ��[%.2f]", *Ljje ),"DEBUG");
    return 0;
}


/************************************************************************
��������:AuthCtrl
����:AuthCtrl
����:��Ʒ����Ȩ�޿���
����:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��:
�� �� Ա: SC
��������: 2011-6-1
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT AuthCtrl(HXMLTREE lXmlhandle, APP_CPJYFW *app_cpjyfw)
{
    char sCpdm[16+1]={0};    /* ��Ʒ���� */
    char sJydm[16+1]={0};     /* ���״��� */
    char sJygy[16+1]={0};    /* ���׹�Ա */
    char sJyjg[16+1]={0};    /* ���׻��� */
    char sJyls[16+1]={0};    /* ������ˮ */
    char sPtrq[8+1]={0};     /* ƽ̨���� */
    char sQxkz[8+1]={0};      /* Ȩ�޿��Ʊ�־ */
    char sGyjb[8+1]={0};      /* ��Ա���� */
    char sGygw[8+1]={0};      /* ��Ա��λ */
    char sSqGyjb[8+1]={0};    /* ��Ȩ��Ա���� */
    char sSqGygw[8+1]={0};    /* ��Ȩ��Ա��λ */

    double dGylj = 0.00;  /* ��Ա�ۼƽ�� */
    double dJglj = 0.00;  /* �����ۼƽ�� */
    double dJyje = 0.00;  /* ���׽�� */
    char sJybz[3+1]={0};     /* ���ױ��� */
    char sSqgy[16+1]={0};    /* ��Ȩ��Ա */
    char sSqjg[16+1]={0};    /* ��Ȩ��Ա���� */
    char sYhh[32+1]={0};
    char sJgjb[16+1]={0};
    APP_CPJYFW sdb_app_cpjyfw; /* ��ƷȨ�޿�����Ϣ */
    APP_CPJYGYKZ sdb_app_cpjygykz;
    APP_CPJYGYED sdb_app_cpjygyed1;
    APP_CPJYJGED sdb_app_cpjyjged1;
    APP_CPJYGYED sdb_app_cpjygyed9;
    APP_CPJYJGED sdb_app_cpjyjged9;
    APP_GYXX sdb_app_gyxx_sq;
    APP_GYXX sdb_app_gyxx;

    char sbuf[256];
    int  iRet = 0;
    int  iFlag = 0;
    int  iParas;
    char sSystime[6+1];
    /* ���±�����־���׶����û��ȡ���ṹ�壬ȡ�����־Ϊ1�����÷���ȥȡ */
    int  iJygyed1 = 0;
    int  iJygyed9 = 0;
    int  iJyjged1 = 0;
    int  iJyjged9 = 0;
    int  iSqgyxx  = 0;

    int  iSqgyed = 0;/* ��Ա�����ȨȨ���жϣ��ж�ͨ�����־Ϊ1�����÷���ȥ�ж� */
    int  iSqjged = 0;/* ���������ȨȨ���жϣ��ж�ͨ�����־Ϊ1�����÷���ȥ�ж� */
    APP_CPJYGYED sdb_app_cpjygyed;
    APP_CPJYJGED sdb_app_cpjyjged;

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,"���[AuthCtrl]ִ�п�ʼ","DEBUG");

    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM,  sCpdm );
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYDM,  sJydm );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJG ,  sJyjg );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYGY ,  sJygy );
    COMP_SOFTGETXML(XMLNM_APP_YYXX_YHH,   sYhh );

    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJE,  sbuf );
    dJyje = atof( sbuf );

    COMP_HARDGETXML(XMLNM_ZWRQ, sPtrq );

    memset(&sdb_app_cpjyfw, 0x00, sizeof(sdb_app_cpjyfw));
    memcpy(&sdb_app_cpjyfw, app_cpjyfw, sizeof(sdb_app_cpjyfw));

    memset( &sdb_app_gyxx, 0x00, sizeof(sdb_app_gyxx));
    iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx, sJygy, sJyjg);
    if( iRet )
        return iRet;

    COMP_SOFTGETXML(XMLNM_APP_JGXX_ORG_LEVEL,  sJgjb );
    strcpy(sGyjb, trim(sdb_app_gyxx.gyjb));

    memset(sSqgy, 0x00, sizeof(sSqgy));
    COMP_SOFTGETXML(XMLNM_APP_REQ_SQGY,  sSqgy );
    memset(sSqjg, 0x00, sizeof(sSqjg));
    COMP_SOFTGETXML(XMLNM_APP_REQ_SQJG,  sSqjg );
    if(strlen(sSqjg)==0)
        strcpy(sSqjg ,sJyjg);

    /* ��齻�׹�ԱȨ���Ƿ��������� */
    if( sdb_app_cpjyfw.qxkz[0] == '0' )  /* ��Ա����Ȩ�޿��� */
    {
        memset( &sdb_app_cpjygykz, 0x00, sizeof( sdb_app_cpjygykz ) );
        iRet = GetCPJYGYKZ(lXmlhandle, &sdb_app_cpjygykz, sCpdm, sJydm);
        if( iRet )
            return iRet;

        if( atoi( sGyjb )  < atoi( sdb_app_cpjygykz.gyjb ) )  /* ��Ա���𲻹� */
        {
            if (sdb_app_cpjygykz.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա���𲻹�,���޾ܾ�",sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_JBBZ,MSG_APP_CPJYGY_JBBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ȩ��Ա���𲻹�[%s]", sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_JBBZ,MSG_APP_CPJYGY_JBBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( !iSqgyxx )
            {
                memset( &sdb_app_gyxx_sq, 0x00, sizeof(sdb_app_gyxx_sq));
                iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx_sq, sSqgy, sSqjg);
                if( iRet )
                    return iRet;
                iSqgyxx = 1;
            }
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygykz.sqgyjb ) )  /* ��Ȩ��Ա���𲻹� */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ȩ��Ա���𲻹�[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_JBBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQJBBZ, sdb_app_cpjygykz.sqgyjb ));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }
    if( sdb_app_cpjyfw.qxkz[1] == '0' )  /* ��Ա���ʶ�ȿ���  */
    {
        if( sdb_app_cpjyfw.gyedkzfs[0] == '0')
        {
            if (!iJygyed1)
            {
                memset( &sdb_app_cpjygyed1, 0x00, sizeof( sdb_app_cpjygyed1 ) );
                iRet = GetCPJYGYED(lXmlhandle, &sdb_app_cpjygyed1, sCpdm, sJydm, sGyjb);
                if( iRet )
                    return iRet;
                iJygyed1 = 1;
            }
            memset( &sdb_app_cpjygyed, 0x00, sizeof( sdb_app_cpjygyed ) );
            memcpy( &sdb_app_cpjygyed, &sdb_app_cpjygyed1, sizeof(sdb_app_cpjygyed));
        }
        else if( sdb_app_cpjyfw.gyedkzfs[0] == '9')
        {
            if (!iJygyed9)
            {
                memset( &sdb_app_cpjygyed9, 0x00, sizeof( sdb_app_cpjygyed9 ) );
                iRet = GetCPJYGYED(lXmlhandle, &sdb_app_cpjygyed1, sCpdm, sJydm, "AA");
                if( iRet )
                    return iRet;
                iJygyed9 = 1;
            }
            memset( &sdb_app_cpjygyed, 0x00, sizeof( sdb_app_cpjygyed ) );
            memcpy( &sdb_app_cpjygyed, &sdb_app_cpjygyed9, sizeof(sdb_app_cpjygyed));
        }

        if( ( dJyje - sdb_app_cpjygyed.dbed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա��Ȳ���,���޾ܾ�",sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]�����Ȩ��Ա���𲻹�[%s]", sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( !iSqgyxx )
            {
                memset( &sdb_app_gyxx_sq, 0x00, sizeof(sdb_app_gyxx_sq));
                iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx_sq, sSqgy, sSqjg);
                if( iRet )
                    return iRet;
                iSqgyxx = 1;
            }
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygyed.sqgyjb ) )  /* ��Ȩ��Ա���𲻹� */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]�����Ȩ��Ա���𲻹�[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqgyed = 1;/*��Ȩ��Ա����ж�ͨ��*/
        }
    }
    if( sdb_app_cpjyfw.qxkz[2] == '0' && iSqgyed == 0 )  /* ��Ա���ۼƶ�ȿ���  */
    {
        /* ͳ�Ƶ����Ա�ۼƶ�� */
        dGylj=0;
        iRet = GetGYLJJE(lXmlhandle, sJygy, sJyjg, sCpdm, sPtrq, 1, &dGylj);
        if ( iRet )
            return iRet;
        if( sdb_app_cpjyfw.gyedkzfs[0] == '0')
        {
            if (!iJygyed1)
            {
                memset( &sdb_app_cpjygyed1, 0x00, sizeof( sdb_app_cpjygyed1 ) );
                iRet = GetCPJYGYED(lXmlhandle, &sdb_app_cpjygyed1, sCpdm, sJydm, sGyjb);
                if( iRet )
                    return iRet;
                iJygyed1 = 1;
            }
            memset( &sdb_app_cpjygyed, 0x00, sizeof( sdb_app_cpjygyed ) );
            memcpy( &sdb_app_cpjygyed, &sdb_app_cpjygyed1, sizeof(sdb_app_cpjygyed));
        }
        else if( sdb_app_cpjyfw.gyedkzfs[0] == '9')
        {
            if (!iJygyed9)
            {
                memset( &sdb_app_cpjygyed9, 0x00, sizeof( sdb_app_cpjygyed9 ) );
                iRet = GetCPJYGYED(lXmlhandle, &sdb_app_cpjygyed1, sCpdm, sJydm, "AA");
                if( iRet )
                    return iRet;
                iJygyed9 = 1;
            }
            memset( &sdb_app_cpjygyed, 0x00, sizeof( sdb_app_cpjygyed ) );
            memcpy( &sdb_app_cpjygyed, &sdb_app_cpjygyed9, sizeof(sdb_app_cpjygyed));
        }
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
             Fmtmsg("���չ�Ա�ۼ�[%.2f]���׽��[%.2f]��Ա���ۼƶ��[%.2f]", \
             dGylj, dJyje, sdb_app_cpjygyed.rljed ),"DEBUG");
        if( ( dGylj + dJyje - sdb_app_cpjygyed.rljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա���ۼƶ�Ȳ���,���޾ܾ�", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա���ۼ���Ȩ��Ա���𲻹�[%s]", sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( !iSqgyxx )
            {
                memset( &sdb_app_gyxx_sq, 0x00, sizeof(sdb_app_gyxx_sq));
                iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx_sq, sSqgy, sSqjg);
                if( iRet )
                    return iRet;
                iSqgyxx = 1;
            }
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygyed.sqgyjb ) )  /* ��Ȩ��Ա���𲻹� */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա���ۼ���Ȩ��Ա���𲻹�[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqgyed = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[3] == '0' && iSqgyed == 0 )  /* ��Ա���ۼƶ�ȿ���  */
    {
        /* ͳ�Ƶ��¹�Ա�ۼƶ�� */
        dGylj=0;
        iRet = GetGYLJJE(lXmlhandle, sJygy, sJyjg, sCpdm, sPtrq, 2, &dGylj);
        if ( iRet )
            return iRet;
        if( sdb_app_cpjyfw.gyedkzfs[0] == '0')
        {
            if (!iJygyed1)
            {
                memset( &sdb_app_cpjygyed1, 0x00, sizeof( sdb_app_cpjygyed1 ) );
                iRet = GetCPJYGYED(lXmlhandle, &sdb_app_cpjygyed1, sCpdm, sJydm, sGyjb);
                if( iRet )
                    return iRet;
                iJygyed1 = 1;
            }
            memset( &sdb_app_cpjygyed, 0x00, sizeof( sdb_app_cpjygyed ) );
            memcpy( &sdb_app_cpjygyed, &sdb_app_cpjygyed1, sizeof(sdb_app_cpjygyed));
        }
        else if( sdb_app_cpjyfw.gyedkzfs[0] == '9')
        {
            if (!iJygyed9)
            {
                memset( &sdb_app_cpjygyed9, 0x00, sizeof( sdb_app_cpjygyed9 ) );
                iRet = GetCPJYGYED(lXmlhandle, &sdb_app_cpjygyed1, sCpdm, sJydm, "AA");
                if( iRet )
                    return iRet;
                iJygyed9 = 1;
            }
            memset( &sdb_app_cpjygyed, 0x00, sizeof( sdb_app_cpjygyed ) );
            memcpy( &sdb_app_cpjygyed, &sdb_app_cpjygyed9, sizeof(sdb_app_cpjygyed));
        }

        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
            Fmtmsg("���¹�Ա�ۼ�[%.2f]���׽��[%.2f]��Ա���ۼƶ��[%.2f]",\
            dGylj, dJyje, sdb_app_cpjygyed.yljed ),"DEBUG");

        if( ( dGylj + dJyje - sdb_app_cpjygyed.yljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա���ۼƶ�Ȳ���,���޾ܾ�", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա���ۼ���Ȩ��Ա���𲻹�[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( !iSqgyxx )
            {
                memset( &sdb_app_gyxx_sq, 0x00, sizeof(sdb_app_gyxx_sq));
                iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx_sq, sSqgy, sSqjg);
                if( iRet )
                    return iRet;
                iSqgyxx = 1;
            }
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygyed.sqgyjb ) )  /* ��Ȩ��Ա���𲻹� */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]��Ա���ۼ���Ȩ��Ա���𲻹�[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqgyed = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[4] == '0' )  /* �������ʶ�ȿ���  */
    {
        if( sdb_app_cpjyfw.jgedkzfs[0] == '0')
        {
            if ( !iJyjged1 )
            {
                memset( &sdb_app_cpjyjged1, 0x00, sizeof( sdb_app_cpjyjged1 ) );
                iRet = GetCPJYJGED(lXmlhandle, &sdb_app_cpjyjged1, sCpdm, sJydm, sJgjb);
                if( iRet )
                    return iRet;
                iJyjged1 = 1;
            }
            memset( &sdb_app_cpjyjged, 0x00, sizeof( sdb_app_cpjyjged ) );
            memcpy( &sdb_app_cpjyjged, &sdb_app_cpjyjged1, sizeof(sdb_app_cpjyjged));
        }
        else if( sdb_app_cpjyfw.jgedkzfs[0] == '9')
        {
            if ( !iJyjged9 )
            {
                memset( &sdb_app_cpjyjged9, 0x00, sizeof( sdb_app_cpjyjged9 ) );
                iRet = GetCPJYJGED(lXmlhandle, &sdb_app_cpjyjged9, sCpdm, sJydm, "AA");
                if( iRet )
                    return iRet;
                iJyjged9 = 1;
            }
            memset( &sdb_app_cpjyjged, 0x00, sizeof( sdb_app_cpjyjged ) );
            memcpy( &sdb_app_cpjyjged, &sdb_app_cpjyjged9, sizeof(sdb_app_cpjyjged));
        }
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
            Fmtmsg("�������ʶ��[%.2f]�ն��[%.2f]���ۼƶ��[%.2f]", \
            sdb_app_cpjyjged.dbed, sdb_app_cpjyjged.rljed, sdb_app_cpjyjged.yljed ),"DEBUG");
        /* ���׽������� */
        if( ( dJyje - sdb_app_cpjyjged.dbed ) > 0.01 )
        {
            if (sdb_app_cpjyjged.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]�������ʶ�Ȳ���,���޾ܾ�", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("��Ʒ[%s]����[%s]�������ʶ����Ȩ��Ա���𲻹�[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( !iSqgyxx )
            {
                memset( &sdb_app_gyxx_sq, 0x00, sizeof(sdb_app_gyxx_sq));
                iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx_sq, sSqgy, sSqjg);
                if( iRet )
                    return iRet;
                iSqgyxx = 1;
            }
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjyjged.sqgyjb ) )  /* ��Ȩ��Ա���𲻹� */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("��Ʒ[%s]����[%s]�������ʶ����Ȩ��Ա���𲻹�[%s]", \
                     sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,\
                      Fmtmsg(MSG_APP_CPJYJG_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqjged = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[5] == '0' && iSqjged == 0 )  /* �������ۼƶ�ȿ��� */
    {
        if( sdb_app_cpjyfw.jgedkzfs[0] == '0')
        {
            if ( !iJyjged1 )
            {
                memset( &sdb_app_cpjyjged1, 0x00, sizeof( sdb_app_cpjyjged1 ) );
                iRet = GetCPJYJGED(lXmlhandle, &sdb_app_cpjyjged1, sCpdm, sJydm, sJgjb);
                if( iRet )
                    return iRet;
                iJyjged1 = 1;
            }
            memset( &sdb_app_cpjyjged, 0x00, sizeof( sdb_app_cpjyjged ) );
            memcpy( &sdb_app_cpjyjged, &sdb_app_cpjyjged1, sizeof(sdb_app_cpjyjged));
        }
        else if( sdb_app_cpjyfw.jgedkzfs[0] == '9')
        {
            if ( !iJyjged9 )
            {
                memset( &sdb_app_cpjyjged9, 0x00, sizeof( sdb_app_cpjyjged9 ) );
                iRet = GetCPJYJGED(lXmlhandle, &sdb_app_cpjyjged9, sCpdm, sJydm, "AA");
                if( iRet )
                    return iRet;
                iJyjged9 = 1;
            }
            memset( &sdb_app_cpjyjged, 0x00, sizeof( sdb_app_cpjyjged ) );
            memcpy( &sdb_app_cpjyjged, &sdb_app_cpjyjged9, sizeof(sdb_app_cpjyjged));
        }
        /* ͳ�Ƶ�������ۼƶ�� */
        dJglj=0;
        iRet = GetJGLJJE(lXmlhandle, sJyjg, sCpdm, sPtrq, 1, &dJglj);
        if ( iRet )
            return iRet;
        if( ( dJglj + dJyje - sdb_app_cpjyjged.rljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]�������ۼƶ�Ȳ���,���޾ܾ�", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("��Ʒ[%s]����[%s]�������ۼƶ����Ȩ��Ա���𲻹�[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( !iSqgyxx )
            {
                memset( &sdb_app_gyxx_sq, 0x00, sizeof(sdb_app_gyxx_sq));
                iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx_sq, sSqgy, sSqjg);
                if( iRet )
                    return iRet;
                iSqgyxx = 1;
            }
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjyjged.sqgyjb ) )  /* ��Ȩ��Ա���𲻹� */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]�������ۼƶ����Ȩ��Ա���𲻹�[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ, \
                    Fmtmsg(MSG_APP_CPJYJG_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            iSqjged = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[6] == '0' && iSqjged == 0 )  /* �������ۼƶ�ȿ��� */
    {
        if( sdb_app_cpjyfw.jgedkzfs[0] == '0')
        {
            if ( !iJyjged1 )
            {
                memset( &sdb_app_cpjyjged1, 0x00, sizeof( sdb_app_cpjyjged1 ) );
                iRet = GetCPJYJGED(lXmlhandle, &sdb_app_cpjyjged1, sCpdm, sJydm, sJgjb);
                if( iRet )
                    return iRet;
                iJyjged1 = 1;
            }
            memset( &sdb_app_cpjyjged, 0x00, sizeof( sdb_app_cpjyjged ) );
            memcpy( &sdb_app_cpjyjged, &sdb_app_cpjyjged1, sizeof(sdb_app_cpjyjged));
        }
        else if( sdb_app_cpjyfw.jgedkzfs[0] == '9')
        {
            if ( !iJyjged9 )
            {
                memset( &sdb_app_cpjyjged9, 0x00, sizeof( sdb_app_cpjyjged9 ) );
                iRet = GetCPJYJGED(lXmlhandle, &sdb_app_cpjyjged9, sCpdm, sJydm, "AA");
                if( iRet )
                    return iRet;
                iJyjged9 = 1;
            }
            memset( &sdb_app_cpjyjged, 0x00, sizeof( sdb_app_cpjyjged ) );
            memcpy( &sdb_app_cpjyjged, &sdb_app_cpjyjged9, sizeof(sdb_app_cpjyjged));
        }
        /* ͳ�Ƶ��»����ۼƶ�� */
        dJglj=0;
        iRet = GetJGLJJE(lXmlhandle, sJyjg, sCpdm, sPtrq, 2, &dJglj);
        if ( iRet )
            return iRet;
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("�����ۼƽ��[%.2f]", \
        sdb_app_cpjyjged.dbed, sdb_app_cpjyjged.rljed, sdb_app_cpjyjged.yljed ),"DEBUG");
        if( ( dJglj + dJyje - sdb_app_cpjyjged.yljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                Fmtmsg("��Ʒ[%s]����[%s]�������ۼƶ�Ȳ���,���޾ܾ�", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("��Ʒ[%s]����[%s]�������ۼƶ����Ȩ��Ա���𲻹�[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( !iSqgyxx )
            {
                memset( &sdb_app_gyxx_sq, 0x00, sizeof(sdb_app_gyxx_sq));
                iRet = GetGYXX( lXmlhandle, &sdb_app_gyxx_sq, sSqgy, sSqjg);
                if( iRet )
                    return iRet;
                iSqgyxx = 1;
            }
            if( atoi( sdb_app_gyxx_sq.gyjb )  <= atoi( sdb_app_cpjyjged.sqgyjb ) )  /* ��Ȩ��Ա���𲻹� */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("��Ʒ[%s]����[%s]�������ۼƶ����Ȩ��Ա���𲻹�[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYJG_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            iSqjged = 1;
        }
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,"���[AuthCtrl]ִ�н���","DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SApp_Init
�������:App_Init
�������:�м�ҵ��ƽ̨2.0������ʼ��
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ϵͳ��ʼ��     416-�����ַ���            N    0 ��Ҫ��ʼ�� 1����Ҫ��ʼ��

  2   1-����   ������ʶ       416-�����ַ���            Y    ��Ϊ������Ҫ��ʼ������������

  3   1-����   Ӧ�ñ�ʶ       416-�����ַ���            Y    ��Ϊ������Ҫ��ʼ����Ӧ�ò���

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_Init(HXMLTREE lXmlhandle)
{
    APP_CSKZ sdb_app_cskz;
    char sSYSInit[1+1]={0};
    char sChannelId[3+1]={0};
    char sAppId[8+1]={0};
    char sbuf[255]={0};
    int  i,iflag=0;
    char sInitType[1+1];
    int  iParas;
    char stmp2[256];
    char sPrefix[10+1];
    int  iserial;
    char sErrmsg[512];
    CURSOR cur;
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3)

    memset(sbuf,0,sizeof(sbuf));
    memset(sSYSInit,0,sizeof(sSYSInit));
    COMP_GETPARSEPARAS(1,sbuf,"ϵͳ��ʼ��")
    pstrcopy(sSYSInit,sbuf,sizeof(sSYSInit));

    memset(sbuf,0,sizeof(sbuf));
    memset(sChannelId,0,sizeof(sChannelId));
    COMP_GETPARSEPARAS(2,sbuf,"������ʶ")
    pstrcopy(sChannelId,sbuf,sizeof(sChannelId));

    memset(sbuf,0,sizeof(sbuf));
    memset(sAppId,0,sizeof(sAppId));
    COMP_GETPARSEPARAS(3,sbuf,"Ӧ�ñ�ʶ")
    pstrcopy(sAppId,sbuf,sizeof(sAppId));

    memset( stmp2 , 0x00, sizeof( stmp2 ) );
    memset( sbuf , 0x00, sizeof( sbuf ) );

    /* ϵͳ�������Զ����� */
    if( sSYSInit[0] =='0')
    {
        iflag = 1;
        sprintf(  sbuf, " SELECT * FROM app_cskz WHERE  (cslx='0' AND jzlx='0') " );
    }
    else
    {
        sprintf(  sbuf, " SELECT * FROM app_cskz WHERE   " );
    }

    if( strlen( sChannelId ) > 0 )  /* ����������ʶ�����ظ������Զ����ز��� */
    {
        memset( stmp2 , 0x00, sizeof( stmp2 ) );
        if(iflag == 1)
        {
            sprintf( stmp2," OR ( cslx='1' AND cstj='%s' AND jzlx='0' ) " ,sChannelId );
        }
        else
        {
            sprintf( stmp2," (cslx='1' AND cstj='%s' AND jzlx='0') " , sChannelId );
        }
        strcat( sbuf, stmp2 );
        iflag = 1;
    }
    else if( strlen( sAppId ) > 0 )    /* ����Ӧ�ñ�ʶ�����ظ�Ӧ���Զ����ز��� */
    {
        memset( stmp2 , 0x00, sizeof( stmp2 ) );
        if(iflag == 1)
        {
            sprintf( stmp2, " OR( cslx ='2'  AND cstj='%s' AND jzlx='0' ) ", sAppId );
        }
        else
            sprintf( stmp2, " ( cslx ='2'  AND cstj='%s' AND jzlx='0' ) ", sAppId );
        strcat( sbuf, stmp2 );
        iflag = 1;
    }

    /* added by yangdong 20090825 δ�����ʼ������ */
    if( iflag == 0 ) 
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("������ʼ������Ϊ��"),"INFO");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    /* end of add */

    if ((cur = DCIDeclareCursor(sbuf, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_cskz,0,sizeof(sdb_app_cskz));
    while( ( iRet = DBFetch(cur, SD_APP_CSKZ, NUMELE(SD_APP_CSKZ), &sdb_app_cskz, sErrmsg ) ) > 0 )
    {
        /*��ȡ�������ݽ��д���*/
        trim(sdb_app_cskz.jdz);
        trim(sdb_app_cskz.jdm);
        COMP_HARDSETXML(sdb_app_cskz.jdm,sdb_app_cskz.jdz);
        memset(&sdb_app_cskz,0,sizeof(sdb_app_cskz));
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

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SApp_GetInfo
�������:App_GetInfo
�������:Ӧ��ȡ������Ϣ
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ������Ϣ       416-�����ַ���            Y    ������Ϣ
  2   1-����   ������ʶ       416-�����ַ���            Y    ������ʶ
  3   1-����   ��������       416-�����ַ���            Y    ��������
  4   1-����   Ӧ�ñ�ʶ       416-�����ַ���            Y    Ӧ�ñ�ʶ
  5   1-����   ��Ʒ����       416-�����ַ���            Y    ��Ʒ����
  6   1-����   ������ʶ       416-�����ַ���            Y    ������ʶ
  7   1-����   ��λ���       416-�����ַ���            Y    ��λ���
  8   1-����   �������       416-�����ַ���            Y    �������   0���� 1������

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_GetInfo(HXMLTREE lXmlhandle)
{
    char sYybs[8+1]={0};
    char sQdbs[3+1]={0};
    char sJgdm[16+1]={0};
    char sJydm[16+1]={0};
    char sYwbh[16+1]={0};
    char sDwbh[16+1]={0};
    char sTxdm[21]={0};
    char sCpdm[16+1]={0};
    char sbuf[255]={0};
    char sCtrlFlag[2]={0};
    int  iRet = 0;
    int  iParas = 0;

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(8)

    /* ����Ϊ0����������Ϣ,������У�������Ϣ*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(8,sbuf,"���Ʊ�־");
    pstrcopy(sCtrlFlag,sbuf,sizeof(sCtrlFlag));

    /* ��λ��ƷЭ����Ϣ��ȡ (����չ����) */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(1,sbuf,"ҵ����");
    pstrcopy(sYwbh,sbuf,sizeof(sYwbh));
    trim(sYwbh);
    if( strlen(sYwbh) > 0)
    {
        iRet = GetDWCPXY(lXmlhandle, sYwbh, sCtrlFlag);
        if (iRet != 0)
            return iRet;

        /* ��λ��ƷЭ��ȡ�ɹ��Ժ󣬲�Ʒ��Ϣ��ȡ (����չ����) */
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_DWCPXY_CPDM, sbuf);
        pstrcopy(sCpdm,sbuf,sizeof(sCpdm));
        trim(sCpdm);
        if( strlen(sCpdm) > 0)
        {
            iRet = GetCPXX(lXmlhandle, sCpdm, sCtrlFlag);
            if (iRet != 0)
                return iRet;
        }
    }

    /* ������Ϣ��ȡ */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(2,sbuf,"���״���")
    pstrcopy(sJydm,sbuf,sizeof(sJydm));
    trim(sJydm);
    if( strlen(sJydm) > 0)
    {
        iRet = GetJYXX(lXmlhandle, sJydm, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* ������Ϣ��ȡ (����չ����)--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(3,sbuf,"������ʶ")
    pstrcopy(sQdbs,sbuf,sizeof(sQdbs));
    trim(sQdbs);
    if( strlen(sQdbs) > 0)
    {
        iRet = GetQDXX(lXmlhandle, sQdbs, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* ������Ϣ��ȡ (����չ����)--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(4,sbuf,"��������")
    pstrcopy(sJgdm,sbuf,sizeof(sJgdm));
    trim(sJgdm);
    if( strlen(sJgdm) > 0)
    {
        iRet = GetJGXX(lXmlhandle, sJgdm, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* Ӧ����Ϣ��ȡ (����չ����)--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(5,sbuf,"Ӧ�ñ�ʶ")
    pstrcopy(sYybs,sbuf,sizeof(sYybs));
    trim(sYybs);
    if( strlen(sYybs) > 0)
    {
        iRet = GetYYXX(lXmlhandle, sYybs, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* ��λ��Ϣ��ȡ--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(6,sbuf,"��λ���")
    pstrcopy(sDwbh,sbuf,sizeof(sDwbh));
    trim(sDwbh);
    if( strlen(sDwbh) > 0)
    {
        iRet = GetDWXX(lXmlhandle, sDwbh, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* ������ʶ��Ϣ��ȡ */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(7,sbuf,"������ʶ")
    pstrcopy(sTxdm,sbuf,sizeof(sTxdm));
    trim(sTxdm);
    if( strlen(sTxdm) > 0)
    {
        iRet = GetTXXX(lXmlhandle, sTxdm, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SApp_CPCtrl
�������:App_CPCtrl
�������:��Ʒ��ϵ����
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ��Ʒ����       416-�����ַ���            N    ��Ʒ����
  2   1-����   ���׽��       416-�����ַ���            Y    ���׽��
  3   1-����   �ͻ����       416-�����ַ���            Y    �ͻ����

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��:
�� �� Ա: YangDong
��������: 2009-6-22
�޸�����:
����ʹ��ʾ��:

************************************************************************/
IRESULT SApp_CPCtrl(HXMLTREE lXmlhandle)
{
    char sCpdm[16+1]={0};
    char sJyje[30]={0};
    char sYhh[32+1]={0};
    APP_CPXX sdb_app_cpxx2;
    APP_JYXX sdb_app_jyxx2;
    APP_CPQDGX sdb_app_cpqdgx;
    APP_CPJGGX sdb_app_cpjggx;
    APP_CPJYFW sdb_app_cpjyfw;
    APP_KHCPQY sdb_app_khcpqy;
    APP_KZSX   sdb_app_kzsx;
    char sJgbh[16+1]={0};
    char sQdbs[3+1]={0};
    char sPkey[40+1]={0};
    char sbuf[256]={0};
    char sQdcz[1+1]={0};

    int  iParas=0;
    char stmp2[256]={0};
    char sSystime[6+1]={0};
    int iZj=0,iLj=0,i,iflag;
    char sXmlnode[128]={0};
    char sXmlBuf[512]={0};
    char sZxxe[128]={0};
    char sZdxe[128]={0};
    char sLsblts[128]={0};
    char sPdblts[128]={0};
    double dJyje=0.00;
    char *pstr1;
    char sZhzded[128]={0};
    char sCch[2+1]={0};
    int  iserial=0;
    int  iRet=0;

    char sFscs[30]={0};
    char sJscs[30]={0};

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3)
    memset(sbuf,0,sizeof(sbuf));
    memset( sCpdm, 0x00, sizeof( sCpdm ) );
    COMP_GETPARSEPARAS(1,sbuf,"��Ʒ����")
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));

    memset(sbuf,0,sizeof(sbuf));
    memset( sJyje, 0x00, sizeof( sJyje ) );
    COMP_GETPARSEPARAS(2,sbuf,"���׽��")
    pstrcopy(sJyje,sbuf,sizeof(sJyje));

    memset(sbuf,0,sizeof(sbuf));
    memset( sYhh, 0x00, sizeof( sYhh ) );
    COMP_GETPARSEPARAS(3,sbuf,"�û���")
    pstrcopy(sYhh,sbuf,sizeof(sYhh));

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
             Fmtmsg("APP:��Ʒ����[%s],���׽��[%s],�û���[%s] ",sCpdm,sJyje,sYhh ),"DEBUG");

    memset(&sdb_app_cpxx2,0,sizeof(APP_CPXX));
    memset(&sdb_app_jyxx2,0,sizeof(APP_JYXX));
    memset(&sdb_app_cpqdgx,0,sizeof(APP_CPQDGX));
    memset(&sdb_app_cpjggx,0,sizeof(APP_CPJGGX));
    memset(&sdb_app_cpjyfw,0,sizeof(APP_CPJYFW));
    memset(&sdb_app_khcpqy,0,sizeof(APP_KHCPQY));

    /* -------------��Ʒ������Ϣ��ȡ ��ʼ----------------*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM   , sdb_app_cpxx2.cpdm);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPMC   , sdb_app_cpxx2.cpmc);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG   , sdb_app_cpxx2.zbjg);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY   , sdb_app_cpxx2.zbgy);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_KHJL   , sdb_app_cpxx2.khjl);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQLX , sdb_app_cpxx2.ywrqlx);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_QDKZBZ , sdb_app_cpxx2.qdkzbz);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_JGKZCS , sdb_app_cpxx2.jgkzcs);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_SXFBZ  , sdb_app_cpxx2.sxfbz);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_SFQYBZ , sdb_app_cpxx2.sfqybz);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_XYXLJZ , sdb_app_cpxx2.xyxljz);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_DZMS   , sdb_app_cpxx2.dzms);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_LSBLTS , sLsblts);
    sdb_app_cpxx2.lsblts = atoi(sLsblts);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_PDBLCS , sPdblts);
    sdb_app_cpxx2.pdblts = atoi(sPdblts);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_JYFS   , sdb_app_cpxx2.jyfs);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_EXTFLD1, sdb_app_cpxx2.extfld1);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_EXTFLD2, sdb_app_cpxx2.extfld2);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPZT   , sdb_app_cpxx2.cpzt);
    COMP_SOFTGETXML(XMLNM_APP_CPXX_QYMS   , sdb_app_cpxx2.qyms);/*ǩԼģʽ*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_KKFS   , sdb_app_cpxx2.kkfs);/*�ۿʽ*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_ZJYYH  , sdb_app_cpxx2.zjyyh);/*����Ӧ�ú�*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_ZJZYYH , sdb_app_cpxx2.zjzyyh);/*������Ӧ�ú�*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_RZMS   , sdb_app_cpxx2.rzms);/*��־ģʽ*/

    if( strlen( sdb_app_cpxx2.cpdm ) <= 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_CPDM_NULL,MSG_APP_CPDM_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* -------------��Ʒ������Ϣ��ȡ ����----------------*/

    /* ��Ʒ���׹�ϵ��� */
    COMP_SOFTGETXML(XMLNM_APP_JYXX_CPXG,  sdb_app_jyxx2.cpxg);
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYDM,  sdb_app_jyxx2.jydm);
    trim( sdb_app_jyxx2.cpxg );
    if( sdb_app_jyxx2.cpxg[0] == '0' )  /* ���׷���Ͳ�Ʒ��� */
    {
        memset( sbuf, 0x00, sizeof( sbuf ) );
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpjyfw\
            WHERE  cpdm ='%s' AND jydm='%s'",sCpdm,sdb_app_jyxx2.jydm );
        iRet = fprv_SelToStruct( sSql1, SD_APP_CPJYFW, NUMELE(SD_APP_CPJYFW), &sdb_app_cpjyfw );
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ʒ���׷�����Ϣ����", "ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet != 0 )
        {
            if ( sdb_app_cpjyfw.qtbz[0] != '0' )
            {
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYFW_STOP,MSG_APP_CPJYFW_STOP);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* ����ʱ����Ʊ�־ 0���� 1������ */
            if( 0 == memcmp(sdb_app_cpjyfw.sjkzbz,"0",1) )
            {
                COMP_HARDGETXML(XMLNM_SYSTIME,sSystime);
                if( ( atoi(sSystime) < atoi(sdb_app_cpjyfw.qssj) ) || 
                    ( atoi(sSystime) > atoi(sdb_app_cpjyfw.jssj) ) )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJYFW_SJ),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_CPJYFW_SJ,MSG_APP_CPJYFW_SJ);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
    
            /* �޶���� */
            if( 0 == memcmp(sdb_app_cpjyfw.xekzbz,"0",1) )
            {
                if( strlen(sJyje) <= 0)
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJYFW_JYJE),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_CPJYFW_JYJE,MSG_APP_CPJYFW_JYJE);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                dJyje=atof(sJyje);
                if( (dJyje<sdb_app_cpjyfw.zxxe) || (dJyje>sdb_app_cpjyfw.zdxe) )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJYFW_JYXE),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_CPJYFW_JYXE,MSG_APP_CPJYFW_JYXE);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }

            /* -------------��Ʒ�ͻ�ǩԼ��ϵ���� ��ʼ----------------*/
            if(0 == memcmp(sdb_app_cpjyfw.qykzbz,"0",1) ) /* 0���� 1 ������ */
            {
                if( strlen( sYhh ) <= 0 )
                {
                    fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                /* �� �û���+��Ʒ���� ��ѯ */
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ), "SQL SELECT  * FROM app_khcpqy\
                    WHERE  cpdm ='%s' and yhh1 ='%s'",sdb_app_cpxx2.cpdm, sYhh );
                iRet = fprv_SelToStruct( sSql1, SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy);
                if( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡǩԼ��Ϣ����", "ERROR");
                    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                    fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                if( iRet == 0 )
                {
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND,MSG_APP_QY_NOTFOUND );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }

                trim( sdb_app_khcpqy.qyzt );
                if( sdb_app_khcpqy.qyzt[0] != '0' ) /*0���� 1����*/
                {
                    fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY,MSG_APP_KHCPQY);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                /* ǩԼ��ͨ������� */
                COMP_HARDGETXML(XMLNM_APP_QDXX_QDBS,sQdbs);
                if ( ( (pstr1=strstr(sdb_app_khcpqy.ktqd,sQdbs)) == NULL ) &&
                        (0 != memcmp(sdb_app_khcpqy.ktqd,"ALL",3) ) )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_KHCPQY_KTQD),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY_KTQD,MSG_APP_KHCPQY_KTQD);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_XYBH   ,sdb_app_khcpqy.xybh   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_CPDM   ,sdb_app_khcpqy.cpdm   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YWBH   ,sdb_app_khcpqy.ywbh   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZHLX   ,sdb_app_khcpqy.zhlx   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_QYZH   ,sdb_app_khcpqy.qyzh   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZHHM   ,sdb_app_khcpqy.zhhm   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZJLX   ,sdb_app_khcpqy.zjlx   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZJHM   ,sdb_app_khcpqy.zjhm   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_QYLX   ,sdb_app_khcpqy.qylx   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_KHJL   ,sdb_app_khcpqy.khjl   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_HYKSRQ ,sdb_app_khcpqy.hyksrq );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_HYJSRQ ,sdb_app_khcpqy.hyjsrq );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_KTQD   ,sdb_app_khcpqy.ktqd   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_BLJG   ,sdb_app_khcpqy.bljg   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_BLGY   ,sdb_app_khcpqy.blgy   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_BLRQ   ,sdb_app_khcpqy.blrq   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YHH1   ,sdb_app_khcpqy.yhh1   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YHH2   ,sdb_app_khcpqy.yhh2   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_YHH3   ,sdb_app_khcpqy.yhh3   );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_DXTZBZ ,sdb_app_khcpqy.dxtzbz );
    
                memset(sZhzded,0,sizeof(sZhzded));
                sprintf(sZhzded,"%f",sdb_app_khcpqy.zhzded);
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_ZHZDED ,sZhzded );
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_EXTFLD1,sdb_app_khcpqy.extfld1);
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_EXTFLD2,sdb_app_khcpqy.extfld2);
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_EXTFLD3,sdb_app_khcpqy.extfld3);
                COMP_SOFTSETXML(XMLNM_APP_KHCPQYXX_QYZT   ,sdb_app_khcpqy.qyzt   );
            }
            /* -------------��Ʒ�ͻ�ǩԼ��ϵ���� ����----------------*/
            /* ��ƷȨ�޼����� */
            /* added by yangdong 20111028 ֻ��Ȩ�޿��Ʋ�ȫΪ1ʱ����Ҫ */
            if( memcmp( sdb_app_cpjyfw.qxkz , "11111111", 8 ) != 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("qxkzbz[%s]",sdb_app_cpjyfw.qxkz ),"INFO");
                iRet = AuthCtrl(lXmlhandle, &sdb_app_cpjyfw);
                if (iRet)
                {
                    return iRet;
                }
            }
        }
        /* -------��Ʒ������ϵ����(�������ȵ���Ʒһ�����ò�Ʒ���е��ý�����ѭͳһ����) ��ʼ----------*/
        if( 0 == memcmp(sdb_app_cpxx2.qdkzbz,"0",1) ) /* 0����  1������ */
        {
            COMP_HARDGETXML(XMLNM_APP_QDXX_QDBS,sQdbs);
            trim(sdb_app_cpxx2.cpdm);
            trim(sQdbs);
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpqdgx WHERE \
                cpdm ='%s' and qdbs = '%s' AND zt='0'", sCpdm, sQdbs );
            iRet = fprv_SelToStruct( sSql1, SD_APP_CPQDGX, NUMELE(SD_APP_CPQDGX), &sdb_app_cpqdgx );
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( iRet == 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                      Fmtmsg("  ������������Ʒ[%s]����[%s]��Ϣ", sCpdm, sQdbs ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX,MSG_APP_CPQDGX);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* ���ж�״̬ */
            if( sdb_app_cpqdgx.zt[0] !='0' ) /*0���� 1������*/
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX,MSG_APP_CPQDGX);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            /* ��Ʒ����ʱ����� --B*/
            if( 0 == memcmp(sdb_app_cpqdgx.sjkzbz,"0",1) ) /*0���� 1������*/
            {
                COMP_HARDGETXML( XMLNM_SYSTIME,sSystime);
                if( ( atoi(sSystime) < atoi(sdb_app_cpqdgx.qssj) ) || \
                          ( atoi(sSystime) > atoi(sdb_app_cpqdgx.jssj) ) )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX_SJ),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX_SJ,MSG_APP_CPQDGX_SJ);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }

            /* ��Ʒ�����޶���� --B*/
            if( 0 == memcmp(sdb_app_cpqdgx.xekzbz,"0",1) ) /*0���� 1������*/
            {
                dJyje=atof(sJyje);
                if( (dJyje<sdb_app_cpqdgx.zxxe) || (dJyje>sdb_app_cpqdgx.zdxe) )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX_JYXE),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX_JYXE,MSG_APP_CPQDGX_JYXE);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }

            /* ����Ƿ����ף����в�Ʒ������������ --B*/
            COMP_HARDGETXML(XMLNM_APP_JYXX_JYLX,sdb_app_jyxx2.jylx);
            if( 0 == memcmp(sdb_app_jyxx2.jylx,"1",1) ) /*0������ 1������ 9����*/
            {
                memset( sQdcz, 0x00, sizeof( sQdcz ) );
                COMP_HARDGETXML( XMLNM_APP_QDXX_CZBZ,sQdcz );
                trim( sQdcz );
                /* ���ж������Ƿ����������Ȼ���жϲ�Ʒ������ϵ�Ƿ�������� */
                if( ( 0 == memcmp( sQdcz, "1",1) ) || \
                          0  == memcmp(sdb_app_cpqdgx.czbz,"1",1) ) /* 0���� 1������*/
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX_CZ),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX_CZ,MSG_APP_CPQDGX_CZ);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }

            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_CPDM   ,sdb_app_cpqdgx.cpdm   );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_QDBS   ,sdb_app_cpqdgx.qdbs   );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_SJKZBZ ,sdb_app_cpqdgx.sjkzbz );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_QSSJ   ,sdb_app_cpqdgx.qssj   );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_JSSJ   ,sdb_app_cpqdgx.jssj   );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_XEKZBZ ,sdb_app_cpqdgx.xekzbz );
            memset(sZxxe,0,sizeof(sZxxe));
            sprintf(sZxxe,"%f",sdb_app_cpqdgx.zxxe);
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_ZXXE   ,sZxxe   );

            memset(sZdxe,0,sizeof(sZdxe));
            sprintf(sZdxe,"%f",sdb_app_cpqdgx.zdxe);
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_ZDXE   ,sZdxe   );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_CZBZ   ,sdb_app_cpqdgx.czbz   );
            /*added by yangdong 20130221 */
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_ZDCZBZ   ,sdb_app_cpqdgx.zdczbz   );
            /*end of add*/
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_FPBCBZ ,sdb_app_cpqdgx.fpbcbz );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_FPCSFS ,sdb_app_cpqdgx.fpcsfs );
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_EXTFLD1,sdb_app_cpqdgx.extfld1);
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_EXTFLD2,sdb_app_cpqdgx.extfld2);
            COMP_SOFTSETXML(XMLNM_APP_CPQDGX_ZT     ,sdb_app_cpqdgx.zt     );
        }

        /* -------------��Ʒ������ϵ���� ��ʼ----------------*/
        if(0 != memcmp(sdb_app_cpxx2.jgkzcs,"0",1) )
        {
            memset(sXmlnode,0,sizeof(sXmlnode));
            /* ���ݻ������Ƽ��𣬻�ȡ�ϼ�������� */
            sprintf( sXmlnode, "/app/org/org_id%d", atol(sdb_app_cpxx2.jgkzcs) );
            memset(sJgbh,0,sizeof(sJgbh));
            COMP_SOFTGETXML(sXmlnode,sJgbh);
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpjggx\
                 WHERE  cpdm = '%s' and jgbh = '%s'",sdb_app_cpxx2.cpdm, sJgbh );
            iRet = fprv_SelToStruct( sSql1, SD_APP_CPJGGX, NUMELE(SD_APP_CPJGGX), &sdb_app_cpjggx);
            if( iRet < 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ʒ���׷�����Ϣ����", "ERROR");
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if( iRet == 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                           Fmtmsg("  ������������Ʒ[%s]����[%s]��Ϣ,���Ʋ���[%s]",\
                           sCpdm,sJgbh,sdb_app_cpxx2.jgkzcs ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,Fmtmsg("������������Ʒ������Ϣ"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* ���ж�״̬ */
            if( 0 == memcmp(sdb_app_cpjggx.zt,"1",1) ) /*0���� 1������*/
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJGGX),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJGGX,MSG_APP_CPJGGX);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            /* ��Ʒ����ʱ����� --B*/
            if( 0 == memcmp(sdb_app_cpjggx.sjkzbz,"0",1) )  /*0���� 1������*/
            {
                COMP_HARDGETXML(XMLNM_SYSTIME,sSystime);
                if( ( atoi(sSystime) < atoi(sdb_app_cpjggx.qssj) ) || \
                             ( atoi(sSystime) > atoi(sdb_app_cpjggx.jssj) ) )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJGGX_SJ),"ERROR");
                    fpub_SetMsg(lXmlhandle,MID_APP_CPJGGX_SJ,MSG_APP_CPJGGX_SJ);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_CPDM   ,sdb_app_cpjggx.cpdm   );
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_JGBH   ,sdb_app_cpjggx.jgbh   );
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_SJKZBZ ,sdb_app_cpjggx.sjkzbz );
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_QSSJ   ,sdb_app_cpjggx.qssj   );
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_JSSJ   ,sdb_app_cpjggx.jssj   );
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_EXTFLD1,sdb_app_cpjggx.extfld1);
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_EXTFLD2,sdb_app_cpjggx.extfld2);
            COMP_SOFTSETXML(XMLNM_APP_CPJGGX_ZT     ,sdb_app_cpjggx.zt     );
        }
        /* -------------��ƷͨѶ��Ϣ�ɽӳ�����ù��������ȡ----------------*/
    }

    /* -------------ҵ������/ҵ����ˮ���� ��ʼ----------------*/
    if( atoi(sdb_app_cpxx2.ywrqlx) == 1) /*1���� 2˽��*/
    {
        memset(stmp2,0,sizeof(stmp2));

        COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ,stmp2);
        /*ҵ������Ϊ��,��ֵ */
        if ( strlen(stmp2) <=0 )
        {
            memset(stmp2,0,sizeof(stmp2));
            COMP_HARDGETXML(XMLNM_ZWRQ,stmp2);
            COMP_HARDSETXML(XMLNM_APP_CPXX_YWRQ,stmp2);
        }

        memset(stmp2,0,sizeof(stmp2));
        COMP_HARDGETXML(XMLNM_ZHQZLSH,stmp2);
        COMP_HARDSETXML(XMLNM_APP_CPXX_YWLSH,stmp2);
    }
    else if( atoi(sdb_app_cpxx2.ywrqlx) == 2)
    {
        /* ����˽����ˮ������������ --B*/
        /* �Բ�Ʒ��������ֵ */
        sprintf( sPkey , "%s" , sdb_app_cpxx2.cpdm );
        trim( sPkey );
        memset(stmp2,0,sizeof(stmp2));
        memset(sCch,0,sizeof(sCch));
        if ( fprv_getPrivate(sPkey, &iserial, sCch, stmp2) < 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPXX_PRVLSH,sdb_app_cpxx2.cpdm),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_CPXX_PRVLSH,Fmtmsg(MSG_APP_CPXX_PRVLSH,sdb_app_cpxx2.cpdm));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        COMP_HARDSETXML(XMLNM_APP_CPXX_YWRQ, stmp2);
        COMP_HARDSETXML(XMLNM_APP_CPXX_CCH,  sCch );
        memset(stmp2,0,sizeof(stmp2));
        sprintf(stmp2, "%d", iserial);

        COMP_HARDSETXML(XMLNM_APP_CPXX_YWLSH, stmp2);
    }
    else
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPXX_ZWRQLX),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_CPXX_ZWRQLX,MSG_APP_CPXX_ZWRQLX);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}


/************************************************************************
��̬�����������
�����������: SApp_InsSerial
�������:     SApp_InsSerial
�������:     Ԥ��ƽ̨������ˮ
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա: YangDong
��������:
�޸�����: 20090623
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_InsSerial(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    APP_DRLS sdb_app_drls;
    char sSystime[6+1];
    char sBuf[256];
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    memset( &sdb_app_drls, 0x00, sizeof( sdb_app_drls ) );

    /*ƽ̨����*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    if ( 0 == sBuf[0] ) 
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_PTRQ_NULL),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_PTRQ_NULL,MSG_APP_PTRQ_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_app_drls.ptrq,sBuf,sizeof(sdb_app_drls.ptrq));
    
    /*ƽ̨ʱ��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_SYSTIME,sBuf);
    pstrcopy(sdb_app_drls.ptsj,sBuf,sizeof(sdb_app_drls.ptsj));
    
    /*ƽ̨��ˮ��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sBuf);
    if ( 0 == sBuf[0] ) 
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_PTLS_NULL),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_PTLS_NULL,MSG_APP_PTLS_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    sdb_app_drls.ptls = atoi(sBuf);
    
    /*ԭƽ̨��ˮ��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YPTLSH,sBuf);
    sdb_app_drls.yptls = atoi(sBuf);
    
    /*���׻���*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJG,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.jyjg,sBuf,sizeof(sdb_app_drls.jyjg));
    
    /*���׹�Ա*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYGY,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.jygy,sBuf,sizeof(sdb_app_drls.jygy));
    
    /*������ʶ*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_QDBS,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.qdbs,sBuf,sizeof(sdb_app_drls.qdbs));
    
    /*�ն��豸���*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_ZDSBBH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.zdsbbh,sBuf,sizeof(sdb_app_drls.zdsbbh));
    
    /*Ӧ�ñ�ʶ*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YYBS,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.yybs,sBuf,sizeof(sdb_app_drls.yybs));
    
    /* ��Ʒ���� */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.cpdm,sBuf,sizeof(sdb_app_drls.cpdm ));
    
    /*ҵ����*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YWBH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.ywbh,sBuf,sizeof(sdb_app_drls.ywbh));
    
    /*���˱�־*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    /* COMP_SOFTGETXML(XMLNM_APP_REQ_RZBZ,sBuf); */
    COMP_SOFTGETXML(XMLNM_APP_JYXX_RZBZ,sBuf); 
    pstrcopy(sdb_app_drls.rzbz,sBuf,sizeof(sdb_app_drls.rzbz));
    
    /*���״���*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    /*
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYDM,sBuf);
    */
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYDM,sBuf); 
    trim(sBuf);
    pstrcopy(sdb_app_drls.jydm,sBuf,sizeof(sdb_app_drls.jydm));
    
    /*�û����*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YHBH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.yhbh,sBuf,sizeof(sdb_app_drls.yhbh));
    
    /*��ת��־*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_XZBZ,sBuf);
    pstrcopy(sdb_app_drls.xzbz,sBuf,sizeof(sdb_app_drls.xzbz));
    
    /*�����־*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JDBZ,sBuf);
    pstrcopy(sdb_app_drls.jdbz,sBuf,sizeof(sdb_app_drls.jdbz));
    
    /*�����ʺ�*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YHZH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.yhzh,sBuf,sizeof(sdb_app_drls.yhzh));
    
    /*added by yr 20120918 �˻�����*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_ZHLX,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.zhlx,sBuf,sizeof(sdb_app_drls.zhlx));
    
    /*�Է��ʺ�*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_DFZH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.dfzh,sBuf,sizeof(sdb_app_drls.dfzh));
    
    /*���׽��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJE,sBuf);
    sdb_app_drls.jyje = atof(sBuf);
    
    /*������*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_SXF,sBuf);
    sdb_app_drls.sxf = atof(sBuf);
    
    /*���α��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_PCBH,sBuf);
    sdb_app_drls.pcbh = atof(sBuf);
    
    /*����״̬*/
    strcpy(sdb_app_drls.jyzt,"9");
    
    /*������Ӧ��*/
    strcpy(sdb_app_drls.jyxym, "99999");
    
    /*��չ1*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_EXTFLD1,sBuf);
    trim(sBuf);
    if ( strlen(sBuf)<=0)
        strcpy(sdb_app_drls.extfld1," ");
    else
        pstrcopy(sdb_app_drls.extfld1,sBuf,sizeof(sdb_app_drls.extfld1));
    
    /*��չ2*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_EXTFLD2,sBuf);
    trim(sBuf);
    if ( strlen(sBuf)<=0)
        strcpy(sdb_app_drls.extfld2," ");
    else
        pstrcopy(sdb_app_drls.extfld2,sBuf,sizeof(sdb_app_drls.extfld2));
    
    DCIBegin(); /*add by chenxm 2015-1-7*/

    iRet = DBInsert("app_drls", SD_APP_DRLS, NUMELE(SD_APP_DRLS), &sdb_app_drls, sErrmsg);
    if( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback(); /*add by chenxm 2015-1-7*/
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("�����쳣���������ݿ����ʧ��[%s]", sErrmsg ),fpub_GetCompname(lXmlhandle))
    }

    DCICommit();

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������: SApp_UpdSerial
�������:     SApp_UpdSerial
�������:     ����ƽ̨������ˮ
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ����״̬        416-�����ַ���        N    0 �ɹ� 1 ʧ��

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա: YangDong
��������:
�޸�����: 20090623
����ʹ��ʾ��:

************************************************************************/
IRESULT SApp_UpdSerial(HXMLTREE lXmlhandle)
{
    char sPtrq[8+1];
    char sJylx[1+1];
    char sJyzt[1+1];
    int  iPtls;
    int  iYptls;
    char sSet[2048];
    char sSql[2304];
    char sBuf[256];
    APP_DRLS sdb_app_drls;

    char sErrmsg[512];
    int  iRet = -1;
    int  iStrLen = 0;
    int  iParas;

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_GETPARSEPARAS(1,sBuf,"����״̬")
    pstrcopy(sJyzt, sBuf,sizeof(sJyzt));

    /*ƽ̨����*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    pstrcopy(sPtrq, sBuf,sizeof(sPtrq));

    /*ƽ̨��ˮ��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sBuf);
    iPtls = atoi(sBuf);

    /*��������*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYLX,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.jylx, sBuf,sizeof( sdb_app_drls.jylx ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " jylx='%s',", sdb_app_drls.jylx );
        iStrLen = strlen( sSet );
    }

    /* ���˱�־ */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_JYXX_RZBZ,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.rzbz, sBuf,sizeof( sdb_app_drls.rzbz ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " rzbz='%s',", sdb_app_drls.rzbz );
        iStrLen = strlen( sSet );
    }

    /*ԭƽ̨��ˮ��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YPTLSH,sBuf);
    iYptls = atoi(sBuf);
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " yptls=%d,", iYptls );
        iStrLen = strlen( sSet );
    }

    /*��Ʒ����*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.cpdm, sBuf,sizeof( sdb_app_drls.cpdm ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " cpdm='%s',", sdb_app_drls.cpdm  );
        iStrLen = strlen( sSet );
    }

    /*�Է��ʺ�*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_DFZH,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.dfzh, sBuf,sizeof( sdb_app_drls.dfzh ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " dfzh='%s',", sdb_app_drls.dfzh );
        iStrLen = strlen( sSet );
    }

    /*���׽��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJE,sBuf);
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " jyje=%.2f,", atof( sBuf ) );
        iStrLen = strlen( sSet );
    }

    /*������*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_SXF_SXF,sBuf);
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " sxf=%.2f,", atof( sBuf ) );
        iStrLen = strlen( sSet );
    }

    /*������Ӧ��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_RESPCODE,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.jyxym, sBuf,sizeof( sdb_app_drls.jyxym ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " jyxym ='%s',", sdb_app_drls.jyxym );
        iStrLen = strlen( sSet );
    }

    /*������Ӧ��Ϣ*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_RESPMSG,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.jyxyxx, sBuf,sizeof( sdb_app_drls.jyxyxx ) -1 );
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " jyxyxx ='%s ',", sdb_app_drls.jyxyxx );
        iStrLen = strlen( sSet );
    }

    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_EXTFLD1,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.extfld1, sBuf,sizeof( sdb_app_drls.extfld1 ) -3 );
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " extfld1='%s  ',", sdb_app_drls.extfld1 );
        iStrLen = strlen( sSet );
    }
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_EXTFLD2,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.extfld2, sBuf,sizeof( sdb_app_drls.extfld2 ) -3 );
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " extfld2='%s  ',", sdb_app_drls.extfld2 );
        iStrLen = strlen( sSet );
    }

    sprintf( sSet+iStrLen, " jyzt='%s'", sJyzt );

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), " UPDATE app_drls SET %s WHERE ptrq='%s' AND ptls=%d",\
                             sSet, sPtrq, iPtls );
    iRet = DCIExecuteDirect( sSql1 );
    if( iRet < 0 )
    {
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* �������׳ɹ����޸�ԭ����״̬ Ϊ7 �ѳ��� */
    if( sJylx[0] == '1' && sJyzt[0] == '0' )  /* �ɹ��ķ����� */
    {
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), " UPDATE app_drls SET jyzt='7' WHERE ptrq='%s' AND ptls=%d ",\
                             sPtrq, iYptls );
        iRet = DCIExecuteDirect( sSql1 );
        if( iRet < 1 )
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    if (DCICommit() != 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("�����쳣���ύ����ʧ��[%s]", DCILastError()), fpub_GetCompname(lXmlhandle))
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������: SApp_CPCtrl_Reversal
�������: App_CPCtrl_Reversal
�������: �������׵Ĳ�Ʒ��ϵ����
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ��Ʒ����       416-�����ַ���            N    ��Ʒ����            
  1   1-����   ������ʶ       416-�����ַ���            N    ������ʶ

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա: YangDong
��������: 2009-7-20
�޸�����:
����ʹ��ʾ��:

************************************************************************/
IRESULT SApp_CPCtrl_Reversal(HXMLTREE lXmlhandle)
{
    char sCpdm[16+1];
    char sQdkz[1+1];
    char sQdbs[3+1];
    char sQdcz[1+1];
    char sQdCpcz[1+1];
    char sErrmsg[512];
    char sbuf[256];
    int  iParas;
    int  iRet =-1;  
 
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(2)

    memset(sbuf,0,sizeof(sbuf));
    memset( sCpdm, 0x00, sizeof( sCpdm ) );
    COMP_GETPARSEPARAS(1,sbuf,"��Ʒ����")
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));

    /* ��Ʒ�����ȡ��ʽ���� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM, sbuf);
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));
    trim(sCpdm);
    
    memset(sbuf,0,sizeof(sbuf));
    memset( sQdbs, 0x00, sizeof( sQdbs ) );
    COMP_GETPARSEPARAS(2,sbuf,"������ʶ")
    pstrcopy(sQdbs,sbuf,sizeof(sQdbs));
   
    if( strlen( sCpdm ) <= 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_CPDM_NULL,MSG_APP_CPDM_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT qdkzbz FROM app_cpxx WHERE  cpdm = '%s'", sCpdm );
    iRet = DBSelectToVarChar(sErrmsg, sQdkz, sSql1);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_CPDM_NOTFOUND,MSG_APP_CPDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    trim( sQdkz );
    if( sQdkz[0] == '1' )   /* ������ */
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }

    /* �����Ƿ������Զ����� */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT zdczbz FROM app_qdxx WHERE  qdbs='%s'", sQdbs );
    iRet = DBSelectToVarChar(sErrmsg, sQdcz, sSql1);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }        
    
    if( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_QDBS_NOTFOUND , MSG_APP_QDBS_NOTFOUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    
    /* �жϲ�Ʒ������ϵ�Ƿ�������� */

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT zdczbz FROM app_cpqdgx WHERE  qdbs = '%s' AND cpdm ='%s'",sQdbs, sCpdm );
    iRet = DBSelectToVarChar(sErrmsg, sQdcz, sSql1);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }        
    if( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX , MSG_APP_CPQDGX );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    

    if( ( 0 == memcmp( sQdcz, "1",1) ) || \
          0  == memcmp( sQdCpcz,"1",1) ) /* 0���� 1������*/
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX_CZ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX_CZ,MSG_APP_CPQDGX_CZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}


/************************************************************************
��̬�����������
�����������: SApp_GetYwrq
�������: sApp_GetYwrq
�������: ��ȡҵ�����ڣ���ˮ��
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ��Ʒ����       416-�����ַ���            N    ��Ʒ����            

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա: YangDong
��������: 2009-7-20
�޸�����:
����ʹ��ʾ��:

************************************************************************/
IRESULT SApp_GetYwrq(HXMLTREE lXmlhandle)
{
    char sCpdm[16+1];
    char sRqlx[1+1];
    char sErrmsg[512];
    char stmp[256];
    char sbuf[256];
    char sPkey[32+1];
    char sCch[16+1];
    int  iParas;
    int  iserial;
    int iRet = -1;
  
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)

    memset(sbuf,0,sizeof(sbuf));
    memset( sCpdm, 0x00, sizeof( sCpdm ) );
    COMP_GETPARSEPARAS(1,sbuf,"��Ʒ����")
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT ywrqlx FROM app_cpxx WHERE  cpdm = '%s'",sCpdm );
    iRet = DBSelectToVarChar(sErrmsg, sRqlx, sSql1);
    if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "��ȡ��Ʒ���׷�����Ϣ����", "ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_CPDM_NOTFOUND,MSG_APP_CPDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* -------------ҵ������/ҵ����ˮ���� ��ʼ----------------*/
    if( atoi( sRqlx) == 1) /*1���� 2˽��*/
    {
        memset(stmp,0,sizeof(stmp));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ,stmp);
        if ( strlen(stmp) <=0 )
        {
            memset(stmp,0,sizeof(stmp));
            COMP_HARDGETXML(XMLNM_ZWRQ,stmp);
            COMP_HARDSETXML(XMLNM_APP_CPXX_YWRQ,stmp);
                
            memset(stmp,0,sizeof(stmp));
            COMP_HARDGETXML(XMLNM_ZHQZLSH,stmp);
            COMP_HARDSETXML(XMLNM_APP_CPXX_YWLSH,stmp);
        }
    }
    else if( atoi(sRqlx) == 2)
    {
        /* ����˽����ˮ������������ --B*/
        /* �Բ�Ʒ��������ֵ */
        sprintf( sPkey , "%s" , sCpdm );
        trim( sPkey );
        memset( stmp,0,sizeof(stmp) );
        memset(sCch,0,sizeof(sCch));
        if ( fprv_getPrivate( sPkey, &iserial, sCch, stmp) < 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPXX_PRVLSH,sCpdm),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_CPXX_PRVLSH,Fmtmsg(MSG_APP_CPXX_PRVLSH,sCpdm));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        COMP_HARDSETXML(XMLNM_APP_CPXX_YWRQ, stmp);
        COMP_HARDSETXML(XMLNM_APP_CPXX_CCH,  sCch );
        memset(stmp,0,sizeof(stmp));
        sprintf(stmp, "%d", iserial);
        COMP_HARDSETXML(XMLNM_APP_CPXX_YWLSH, stmp);
    }
    else
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPXX_ZWRQLX),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_CPXX_ZWRQLX,MSG_APP_CPXX_ZWRQLX);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* -------------ҵ������/ҵ����ˮ���� ����----------------*/

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������:SApp_Enmu
�������:SApp_Enmu
�������:�м�ҵ��ƽ̨2.0 ����ö�����
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��
  1   1-����   ö��ID     416-�����ַ���            N   ö��ID

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա: duyj
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_Enmu(HXMLTREE lXmlhandle)
{
    char sbuf[512];
    APP_MJSX sdb_app_mjsx;
    APP_MJSJ sdb_app_mjsj;
    char smjid[16+1];
    int  i,iflag=0;
    int  iParas;
    char stmp2[256];
    char sXmlBuf[512];
    char sPrefix[10+1];
    int  iserial;
    char sErrmsg[512];
    CURSOR cur;
    int  iRet = -1;
    
    fpub_InitSoComp(lXmlhandle);
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    COMP_PARACOUNTCHKMIN(1)
    
    memset(sbuf,0,sizeof(sbuf));
    memset(smjid,0,sizeof(smjid));
    COMP_GETPARSEPARAS(1,sbuf,"ö��ID")
    pstrcopy(smjid,sbuf,sizeof(smjid));
  
    memset( sbuf , 0x00, sizeof( sbuf ) );
    sprintf( sbuf , "SELECT * FROM app_mjsj WHERE mjid='%s' ",smjid);
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * from APP_MJSX WHERE mjid = '%s' and sxlx = '1' order by sxxh",smjid );
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

    memset(&sdb_app_mjsx,0,sizeof(APP_MJSX));
    while( ( iRet = DBFetch(cur, SD_APP_MJSX, NUMELE(SD_APP_MJSX), &sdb_app_mjsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_mjsx.mjsm); /*ö��˵��*/
        trim(sdb_app_mjsx.sxlx); /*�������� 1���� 2���*/
        trim(sdb_app_mjsx.sxxh); /*�������*/
        trim(sdb_app_mjsx.sxmc); /*��������*/
        trim(sdb_app_mjsx.sxnr); /*��������λ��*/
        trim(sdb_app_mjsx.sxsm); /*����˵��*/

        /* ����ֵ(֧�ֽ����ַ�������) */
        memset(sXmlBuf,0,sizeof(sXmlBuf));
        COMP_SOFTGETXML(sdb_app_mjsx.sxnr,sXmlBuf);
        trim(sXmlBuf);
        sprintf( sbuf, "%s AND ( req%d = '%s' ) ",sbuf,atoi(sdb_app_mjsx.sxxh), sXmlBuf);

        memset(&sdb_app_mjsx,0,sizeof(sdb_app_mjsx));
    }
    
    if ( iRet < 0 )    
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }  
          
    DCIFreeCursor(cur);

    /*ȡֵ*/
    if ((cur = DCIDeclareCursor(sbuf, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_mjsj,0,sizeof(APP_MJSJ));
    iRet = DBFetch(cur, SD_APP_MJSJ, NUMELE(SD_APP_MJSJ), &sdb_app_mjsj, sErrmsg );
    if ( iRet == 0 )
    {
        memset(&sdb_app_mjsj,0,sizeof(sdb_app_mjsj));
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_mjsj WHERE mjid='%s' AND qsbz='0'", smjid );
        iRet = fprv_SelToStruct( sSql1, SD_APP_MJSJ, NUMELE(SD_APP_MJSJ), &sdb_app_mjsj);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("��ȡö����Ϣ[%s]����",sSql1),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴�ö����Ϣ[%s]",sSql1),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    } 
    DCIFreeCursor(cur);

    /*��ֵ*/
    memset(sSql1, 0, sizeof(sSql1));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM APP_MJSX WHERE mjid ='%s' and  sxlx='2' order by sxxh",smjid );
    memset(&sdb_app_mjsx,0,sizeof(sdb_app_mjsx));
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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
    while( ( iRet = DBFetch(cur, SD_APP_MJSX, NUMELE(SD_APP_MJSX), &sdb_app_mjsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_mjsx.mjsm); /*ö��˵��*/
        trim(sdb_app_mjsx.sxlx); /*�������� 1���� 2���*/
        trim(sdb_app_mjsx.sxxh); /*�������*/
        trim(sdb_app_mjsx.sxmc); /*��������*/
        trim(sdb_app_mjsx.sxnr); /*��������λ��*/
        trim(sdb_app_mjsx.sxsm); /*����˵��*/
        
        if(strlen(sdb_app_mjsx.sxnr)>0)
        {
            switch(atoi(sdb_app_mjsx.sxxh))
            {
                case 1:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp1   );
                    break;
                case 2:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp2   );
                    break;
                case 3:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp3   );
                    break;
                case 4:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp4   );
                    break;
                case 5:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp5   );
                    break;
                case 6:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp6   );
                    break;
                case 7:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp7   );
                    break;
                case 8:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp8   );
                    break;
                case 9:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp9   );
                    break;
                case 10:
                    COMP_SOFTSETXML(sdb_app_mjsx.sxnr   , sdb_app_mjsj.resp10   );
                    break;
                default :
                    break;
            }
        }
        memset(&sdb_app_mjsx,0,sizeof(sdb_app_mjsx));
    }
    if( iRet < 0 )    
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }        
    DCIFreeCursor(cur);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
��̬�����������
�����������: SApp_CheckNull
�������:     SApp_CheckNull
�������:     �ж�ĳ��XMLԪ��ֵ�Ƿ�Ϊ�գ������ո�
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա: sc
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_CheckNull(HXMLTREE lXmlhandle)
{
    char sbuf[256];
    int  iParas = 0;
    fpub_InitSoComp(lXmlhandle);
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    COMP_PARACOUNTCHKMIN(1)

    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(1,sbuf,"XML�ڵ���")
    trim( sbuf );

    if( strlen( sbuf ) == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
            Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    else
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
            Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
        /* modify by yr 20120910 ʧ�ܷ��ظ�Ϊ1 */
        /*
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
        */
        fpub_SetCompStatus(lXmlhandle,1);
        return 0;
    }
}

/************************************************************************
��̬�����������
�����������:SApp_UpdQDZT
�������:SApp_UpdQDZT
�������:����ͨѶ��ȫ��Ϣ�����
         ����ǩ��ǩ�˽��׸���ǩ��״̬��־
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_UpdQDZT(HXMLTREE lXmlhandle)
{
    char sQdzt[1+1]={0};   /* 1ǩ��  2ǩ�� */
    char sLjbs[8+1]={0};
    char sbuf[255];
    int  iParas = 0;
    int  iRet = -1;
 
    fpub_InitSoComp(lXmlhandle);
    COMP_PARACOUNTCHKMIN(2)

    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(1,sbuf,"������ʶ");
    pstrcopy(sLjbs,sbuf,sizeof(sLjbs));
    trim(sLjbs);

    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(2,sbuf,"ǩ��״̬");
    pstrcopy(sQdzt,sbuf,sizeof(sQdzt));
    trim(sQdzt);

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    memset(sSql1, 0, sizeof(sSql1));
    snprintf(sSql1,sizeof(sSql1),"UPDATE app_txaqxx SET qdzt='%s' WHERE ljbs ='%s'", sQdzt, sLjbs);
    iRet = DCIExecuteDirect( sSql1 );
    if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
               Fmtmsg("����ǩ��ǩ��״̬ʧ��, sql[%s],[%s]", sSql1, DCILastError()),"ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_APP_TXAQXX_SB, MSG_APP_TXAQXX_SB);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCICommit() == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("�����쳣���ύ����ʧ��[%s]", DCILastError()), fpub_GetCompname(lXmlhandle))
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
    return 0; 
}

/************************************************************************
��̬�����������
�����������:SApp_DynExecSql
�������:SApp_DynExecSql
�������:
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��
������״̬:
  ���״̬��         ���˵��
  ȱʡ
��־��Ϣ:
  ��־����           ��־��
��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ
��Ҫ����Ԫ��:
  Ԫ��·��          ����
��Ҫ�������:
  ����              ����
ʹ������:
�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_DynExecSql(HXMLTREE lXmlhandle)
{
    char sSql[1024];
    int  i,iParas;
    char  sCommitFlag[1+1];
    char  sTransFlag[1+1];
    int   iRet;

    fpub_InitSoComp(lXmlhandle);
  
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    COMP_PARACOUNTCHKMIN(3)

    /* by yr 20120918 ���ӳ�ʼ�� */
    memset( sSql, 0, sizeof( sSql ));
    memset( sTransFlag, 0, sizeof( sTransFlag ));
    memset( sCommitFlag, 0, sizeof( sCommitFlag ));
        
    COMP_GETPARSEPARAS( 1,sSql,"��ѯ���")
    LOG(LM_STD,Fmtmsg("���ִ��SQL[%s]", sSql ),"INFO")  
    
    COMP_GETPARSEPARAS( 2,sTransFlag,"���������־")  /* 1 �������� 0 Ĭ�������� */
    LOG(LM_STD,Fmtmsg("sTransFlag[%s]", sTransFlag),"INFO") 
    
    COMP_GETPARSEPARAS( 3,sCommitFlag,"�ύ�����־") /* 1 ���ύ���� 0 Ĭ���ύ */
    LOG(LM_STD,Fmtmsg("sCommitFlag[%s]", sCommitFlag),"INFO")

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ��SQL[%s]",fpub_GetCompname(lXmlhandle),sSql),"DEBUG")  

    if( sTransFlag[0] != '1' )
    {
        if( DCIBegin() != 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    if( iRet = DCIExecuteDirect( sSql ) < 0 )
    {
        LOG(LM_STD,Fmtmsg("ִ��SQL[%s]ʧ��",sSql ),"ERROR")  
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
        return COMPRET_FAIL;
    }

    if( sCommitFlag[0] != '1' ) /* �ύ��־��Ϊ ���ύ */
    {
        /* �ύ���� */
        if (DCICommit() != 0)
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            LOGRET(-1, LM_STD, Fmtmsg("�����쳣���ύ����ʧ��[%s]", DCILastError()), fpub_GetCompname(lXmlhandle))
        }
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

  return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SApp_GetPara
�������:SApp_GetPara
�������:���ݲ�����ֵ����ȡ����
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��
������״̬:
  ���״̬��         ���˵��
  ȱʡ
��־��Ϣ:
  ��־����           ��־��
��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ
��Ҫ����Ԫ��:
  Ԫ��·��          ����
��Ҫ�������:
  ����              ����
ʹ������:
�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_GetPara(HXMLTREE lXmlhandle)
{
    APP_CSKZ sdb_app_cskz;
    char sPkey[40+1];
    int  i,iParas;
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);
  
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")   

    COMP_PARACOUNTCHKMIN(1)

    memset( sPkey, 0x00, sizeof( sPkey ) );
    COMP_GETPARSEPARAS( 1,sPkey,"������ֵ")

    memset(&sdb_app_cskz,0,sizeof(sdb_app_cskz));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cskz WHERE  csjz = '%s'",sPkey );
    iRet = fprv_SelToStruct( sSql1, SD_APP_CSKZ, NUMELE(SD_APP_CSKZ), &sdb_app_cskz );
    if ( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG(LM_STD,Fmtmsg("��ȡ����[%s]ʧ��", sPkey ),"ERROR")  
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("�޴˲�����Ϣ[%s]",sPkey),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*��ȡ�������ݽ��д���*/
    trim(sdb_app_cskz.jdz);
    trim(sdb_app_cskz.jdm);
    COMP_HARDSETXML(sdb_app_cskz.jdm,sdb_app_cskz.jdz);

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:SApp_GetSeries
�������:SApp_GetSeries
�������:���ݼ�ֵ����ȡ���е�ǰֵ
�������:
 ��� ��������  ��������         ��Դ���         ȱʡֵ  �ɿ�  ����˵��
������״̬:
  ���״̬��         ���˵��
  ȱʡ
��־��Ϣ:
  ��־����           ��־��
��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ
��Ҫ����Ԫ��:
  Ԫ��·��          ����
��Ҫ�������:
  ����              ����
ʹ������:
�� Ŀ ��: 
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SApp_GetSeries(HXMLTREE lXmlhandle)
{
    char sPkey[40+1];
    int  i,iParas;
    long lSeries = 0;
    char sBuf[32];
    char sNode[64+1];
    
    fpub_InitSoComp(lXmlhandle);
  
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    COMP_PARACOUNTCHKMIN(2)

    memset( sPkey, 0x00, sizeof( sPkey ) );
    COMP_GETPARSEPARAS( 1,sPkey,"������ֵ")

    memset( sNode, 0x00, sizeof( sNode) );
    COMP_GETPARSEPARAS( 2,sNode,"xml�ڵ���")

    i = fprv_getSeqno( sPkey, &lSeries );
    if( i < 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_GENSEQ_FAIL,MSG_APP_GENSEQ_FAIL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memset( sBuf, 0x00, sizeof( sBuf ) );
    sprintf( sBuf, "%ld", lSeries );
    COMP_HARDSETXML( sNode, sBuf );

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}
