/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V4.1.0.1
操作系统:AIX+ORACLE
文件名称:APP_PUB.c
文件描述:通用应用平台组件集合
项 目 组:
程 序 员: YangDong
发布日期: 
程 序 员: SC 
修改日期: 20111101
修    订:  Agent2.1改造

程 序 员: YangDong
修改日期: 20111228
修    订: 增加组件SApp_DynExecSql(动态执行sql，提供事务选择)
                  SApp_GetPara(根据参数键值，初始化对应参数)
程 序 员: YangDong
修改日期: 20130131
修    订: 根据测试意见，将获取扩展属性相关代码, select *改为获取csmc和csz.

程 序 员: YangDong
修改日期: 20140828
修    订: dci改造
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
        <sonote>APP通用组件集合</sonote>\
        <version>\
        <rec ver=\"2.0.0.1\" modify=\"2010-4-1  15:08\" programer=\"YangDong\" filesize=\"1309408\">HS-AgentV2.0整理</rec>\
        <rec ver=\"2.1.0.1\" modify=\"2011-11-01 10:08\" programer=\"S..C..\"   filesize=\"1309408\">HS-AgentV2.1改造</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2011-12-28 10:08\" programer=\"YangDong\" filesize=\"1309408\">增加SApp_DynExecSql SApp_GetPara组件</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-8-28 10:08\" programer=\"YangDong\" filesize=\"1309408\">DCI改造</rec>\
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

char sSql1[512+1];

/*私有函数，供SApp_GetInfo调用，获取交易信息，最后保存在XML树中*/
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

     LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("获取交易信息GetJYXX[%s]",sJydm ),"DEBUG");

    /* 交易信息获取 --B */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_jyxx WHERE  jydm = '%s'" ,sJydm );
    iRet = fprv_SelToStruct( sSql1, SD_APP_JYXX, NUMELE(SD_APP_JYXX), &sdb_app_jyxx );
    if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取交易信息[%s]出错",sJydm),"ERROR");
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此交易信息[%s]",sJydm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 控制输出信息 */
    if ( sCtrlFlag[0] == '0' && sdb_app_jyxx.qtbz[0] != '0' ) /* 启停标识0 为启动 */
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg( " 交易[%s] 状态[%s]", sJydm, sdb_app_jyxx.qtbz ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYXX_GB,MSG_APP_JYXX_GB);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 不控制输出信息 */
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
    /* 交易扩展属性获取 */
    memset(sPkey, 0, sizeof(sPkey));
    memset(sSql1, 0, sizeof(sSql1));
    sprintf(sPkey, "jyxx_%s", sJydm);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);

        /* 参数路径 */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_JYXX_KZSX_PATH,sdb_app_kzsx.csmc);

        /* 参数值(支持解析字符串配置) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "解析扩展参数失败" ),"ERROR");
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    DCIFreeCursor(cur);

    return 0;
}

/*私有函数，供SApp_GetInfo调用，获取渠道信息，最后保存在XML树中*/
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
        Fmtmsg("获取渠道信息GetQDXX[%s]", sQdbs ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_qdxx WHERE  qdbs ='%s'", sQdbs );
    iRet = fprv_SelToStruct( sSql1, SD_APP_QDXX, NUMELE(SD_APP_QDXX), &sdb_app_qdxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取渠道信息[%s]出错",sQdbs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此渠道信息[%s]",sQdbs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_QDXX_NOTFOUND,MSG_APP_QDXX_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 控制输出信息 */
    if ( sCtrlFlag[0] == '0' ) /* 渠道状态0 正常 20130923 删除条件： && sdb_app_qdxx.qdzt[0] != '0'  */
    {
        if( sdb_app_qdxx.qdzt[0] != '0' )  /* 检查渠道状态 */
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                 Fmtmsg( " 渠道[%s] 状态[%s]", trim( sdb_app_qdxx.qdmc ), sdb_app_qdxx.qdzt ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_QDXX_GB,MSG_APP_QDXX_GB);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* 检查时间控制 */
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
        if( sdb_app_qdxx.czbz[0] == '1' )  /* 渠道不允许反交易，检查交易类型 */
        {
            COMP_HARDGETXML( XMLNM_APP_JYXX_JYLX ,sJylx );
            if( sJylx[0] == '1' )  /* 反交易 */
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

    /* 渠道扩展属性信息 */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "qdxx_%s", sQdbs);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);
        /* 参数路径 */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_QDXX_KZSX_PATH,sdb_app_kzsx.csmc);

        /* 参数值(支持解析字符串配置) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "解析扩展参数失败" ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*私有函数，供SApp_GetInfo调用，获取机构信息，最后保存在XML树中*/
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
        Fmtmsg("获取机构信息GetJGXX[%s]",sJgdm ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM t_org WHERE  org_id ='%s'", sJgdm );
    iRet = fprv_SelToStruct( sSql1, SD_T_ORG, NUMELE(SD_T_ORG), &sdb_t_org);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取机构信息[%s]出错",sJgdm),"ERROR");
        /*DCIRollback(); deleted by chenmx 2015-1-7*/
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,Fmtmsg("无满足条件机构信息,[%s]",sJgdm));
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

    /* 获取上级机构信息 */
    pstrcopy(sAboveOrgTmp,sdb_t_org.above_org_id,sizeof(sAboveOrgTmp));
    /* added 20090716 by yangdong 到机构一级 */
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
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取上级机构信息[%s]出错",sAboveOrgTmp),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                Fmtmsg("  无满足条件的上级机构信息[%s]",sAboveOrgTmp),"ERROR");
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

/*私有函数，供SApp_GetInfo调用，获取应用信息，最后保存在XML树中*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取应用信息[%s]出错",sYybs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此应用信息[%s]",sYybs),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_YYXX_NOTFOUND,MSG_APP_YYXX_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 控制输出信息 */
    if ( sCtrlFlag[0] == '0' && sdb_app_yyxx.yyzt[0] != '0' ) /* 应用状态0 正常 */
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_YYXX_GB),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_YYXX_GB,MSG_APP_YYXX_GB);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 不控制输出信息 */
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

/*私有函数，供SApp_GetInfo调用，获取单位产品协议信息，最后保存在XML树中*/
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

    LOG(LM_DEBUG,Fmtmsg("获取单位产品协议信息GetDWCPXY[%s]",sYwbh ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_dwcpxy WHERE  ywbh ='%s'", sYwbh );
    iRet = fprv_SelToStruct( sSql1, SD_APP_DWCPXY, NUMELE(SD_APP_DWCPXY), &sdb_app_dwcpxy);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取单位产品协议信息[%s]出错",sYwbh),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此单位产品协议信息[%s]",sYwbh),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_YWBH_NOTFOUND,MSG_APP_YWBH_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 控制输出信息 */
    if ( sCtrlFlag[0] == '0' )
    {
        if( sdb_app_dwcpxy.qyzt[0] != '0' )
        {
            fpub_SetMsg(lXmlhandle,MID_APP_CPXX_ZT,MSG_APP_CPXX_ZT);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
#if 0
/* mod 20171124 批量对单位签约有效期不进行判断，柜面查询时会对失效单位进行提示 */
        /* added by yangdong 20111028 增加对生效日期，失效日期判断,日期未配置则不判断 */
        trim( sdb_app_dwcpxy.hyksrq );
        if( strlen( sdb_app_dwcpxy.hyksrq ) == 8 )
        {
            memset( sJyrq, 0x00, sizeof( sJyrq ) );
            COMP_SOFTGETXML( XMLNM_ZWRQ, sJyrq );
            if( atoi( sJyrq ) < atoi( sdb_app_dwcpxy.hyksrq ) ) /* 尚未生效 */
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
            if( atoi( sJyrq ) >= atoi( sdb_app_dwcpxy.hyjsrq ) ) /* 已失效 */
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
    
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_SFBZ,    trim(sdb_app_dwcpxy.sfbz));/*收付标识*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DSZH   , trim(sdb_app_dwcpxy.dszh));/*代收账户*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DSZHMC   , trim(sdb_app_dwcpxy.dszhmc));/*代收账户名称*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DFZH   , trim(sdb_app_dwcpxy.dfzh));/*代收账户*/
    COMP_SOFTSETXML(XMLNM_APP_DWCPXY_DFZHMC   , trim(sdb_app_dwcpxy.dfzhmc));/*代收账户名称*/
    
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

    /* 单位产品协议扩展属性信息 */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "dwcpxy_%s", sYwbh);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);

        /* 参数路径 */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_DWCPXY_KZSX_PATH,sdb_app_kzsx.csmc);

        /* 参数值(支持解析字符串配置) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "解析扩展参数失败" ),"ERROR");
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    return 0;
}

/*私有函数，供SApp_GetInfo调用，获取通讯信息，最后保存在XML树中*/
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
        Fmtmsg("获取通讯信息GetTXXX[%s]",sTxdm ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_txaqxx WHERE  ljbs ='%s'", sTxdm );
    iRet = fprv_SelToStruct( sSql1, SD_APP_TXAQXX, NUMELE(SD_APP_TXAQXX), &sdb_app_txaqxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取通讯信息[%s]出错",sTxdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此通讯信息[%s]",sTxdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 通讯状态 0正常 1签退 2签到 9无效 */
    if ( sCtrlFlag[0] == '0' && ( sdb_app_txaqxx.txzt[0] != '0' &&  sdb_app_txaqxx.txzt[0] != '2'  ) )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("  通讯状态 [%s]", sdb_app_txaqxx.txzt ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_TXAQXX_WX, MSG_APP_TXAQXX_WX );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*对取出的数据进行处理*/
    trim(sdb_app_txaqxx.ljbs);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJBS     , sdb_app_txaqxx.ljbs);
    trim(sdb_app_txaqxx.ljmc);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJMC     , sdb_app_txaqxx.ljmc);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_LJLX     , sdb_app_txaqxx.ljlx);
    trim(sdb_app_txaqxx.dwbh);
    COMP_SOFTSETXML(XMLNM_APP_TXAQXX_DWBH     , sdb_app_txaqxx.dwbh);
    trim(sdb_app_txaqxx.qdkz);/* 签到控制 */
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

    /* 通讯扩展属性信息 */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "txxx_%s", sTxdm);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);
        /* 参数路径 */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_TXAQXX_PATH,sdb_app_kzsx.csmc);

        /* 参数值(支持解析字符串配置) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "解析扩展参数失败" ),"ERROR");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*私有函数，供SApp_GetInfo调用，获取单位信息，最后保存在XML树中*/
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
        Fmtmsg("获取单位信息GetDWXX[%s]",sDwbh ),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_dwxx WHERE  dwbh='%s'", sDwbh );
    iRet = fprv_SelToStruct( sSql1, SD_APP_DWXX, NUMELE(SD_APP_DWXX), &sdb_app_dwxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取单位信息[%s]出错",sDwbh),"ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此单位信息[%s]",sDwbh),"ERROR");
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

    /* 扩展属性 */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "dwxx_%s", sDwbh);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "解析扩展参数失败" ),"ERROR");
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*私有函数，供SApp_GetInfo调用，获取产品信息，最后保存在XML树中*/
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

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("获取产品信息[%s]",sCpdm),"DEBUG");

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM app_cpxx WHERE  cpdm='%s'", sCpdm ) ;
    iRet = fprv_SelToStruct( sSql1, SD_APP_CPXX, NUMELE(SD_APP_CPXX), &sdb_app_cpxx );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取产品信息[%s]出错",sCpdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此产品信息[%s]",sCpdm),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_CPDM_NOTFOUND,MSG_APP_CPDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 控制输出信息 */
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
    
    /*add by SC 20110530,产品信息表模型修改*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_QYMS,    trim(sdb_app_cpxx.qyms));/*签约模式*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_JZSX,    trim(sdb_app_cpxx.jzsx));/*记账顺序*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_KKFS,    trim(sdb_app_cpxx.kkfs));/*扣款方式*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_ZJYYH,   trim(sdb_app_cpxx.zjyyh));/*主机应用号*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_ZJZYYH,  trim(sdb_app_cpxx.zjzyyh));/*主机子应用号*/
    COMP_SOFTSETXML(XMLNM_APP_CPXX_RZMS,    trim(sdb_app_cpxx.rzms));/*日志模式*/

    /* 产品扩展属性信息 */
    memset(sPkey, 0, sizeof(sPkey));
    sprintf(sPkey, "cpxx_%s", sCpdm);
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_kzsx WHERE pkey = '%s'", sPkey );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    while( ( iRet = DBFetch(cur, SD_APP_KZSX, NUMELE(SD_APP_KZSX), &sdb_app_kzsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_kzsx.csmc);
        trim(sdb_app_kzsx.csz);

        /* 参数路径 */
        memset(sXmlnode, 0, sizeof(sXmlnode));
        sprintf(sXmlnode,"%s/%s",XMLNM_APP_CPXX_KZSX_PATH,sdb_app_kzsx.csmc);

        /* 参数值(支持解析字符串配置) */
        strncpy(sXmlBuf, sdb_app_kzsx.csz, sizeof(sXmlBuf)-1);
        if (xml_RelParseXMLString(lXmlhandle,sXmlBuf,sizeof(sXmlBuf))==FAIL)
        {
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg( "解析扩展参数失败" ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        trim(sXmlBuf);
        COMP_SOFTSETXML(sXmlnode   , sXmlBuf   );
        memset(&sdb_app_kzsx,0,sizeof(APP_KZSX));
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    return 0;
}

/*私有函数，获取产品交易服务信息，最后保存在结构体中*/
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
    /* 先判断产品交易服务信息是否满足要求 */
    snprintf( sSql1, sizeof( sSql1 ), "SELECT  * FROM app_cpjyfw WHERE  cpdm ='%s' AND jydm='%s'", sCpdm, sJydm );
    iRet = fprv_SelToStruct( sSql1, SD_APP_CPJYFW, NUMELE(SD_APP_CPJYFW), &sdb_app_cpjyfw);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取产品交易服务信息出错", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
            Fmtmsg("  产品[%s]交易服务[%s]关系不存在", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 交易时间控制标志 0控制 1不控制 */
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

    /* 限额控制 */
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
    /* -------------产品客户签约关系控制 开始----------------*/
    if(0 == memcmp(sdb_app_cpjyfw.qykzbz,"0",1) ) /* 0控制 1 不控制 */
    {
        if( strlen( sYhh ) <= 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* 按 用户号+产品代码 查询 */

        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT  * FROM app_khcpqy\
             WHERE  cpdm ='%s' AND yhh1 ='%s'",sCpdm, sYhh );
        iRet = fprv_SelToStruct( sSql1, SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取签约信息[%s]出错",sYhh),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取签约信息[%s]失败",sYhh),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND,MSG_APP_QY_NOTFOUND );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        trim( sdb_app_khcpqy.qyzt );
        if( sdb_app_khcpqy.qyzt[0] != '0' ) /*0正常 1撤消*/
        {
            fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY,MSG_APP_KHCPQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* 签约开通渠道检查 */
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

/*私有函数，获取产品交易柜员权限，最后保存在结构体中*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取产品交易柜员控制信息出错", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
            Fmtmsg("产品[%s]交易[%s]未配置柜员级别权限控制信息", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_cpjygykz, &sdb_app_cpjygykz, sizeof(sdb_app_cpjygykz));
    return 0;
}
/*私有函数，获取产品交易柜员额度，最后保存在结构体中*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取产品交易柜员额度信息出错", "ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
            Fmtmsg("产品[%s]交易[%s]未配置柜员级别额度控制信息", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_cpjygyed, &sdb_app_cpjygyed, sizeof(sdb_app_cpjygyed));
    return 0;
}

/*私有函数，获取产品交易机构额度，最后保存在结构体中*/
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
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取产品交易机构额度信息出错", "ERROR");
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
              Fmtmsg("产品[%s]交易[%s]未配置机构级别额度控制信息", sCpdm, sJydm ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_cpjyjged, &sdb_app_cpjyjged, sizeof(sdb_app_cpjyjged));
    return 0;
}

/*私有函数，获取交易柜员信息，最后保存在XML树中*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取柜员信息出错", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("未配置柜员信息[%s][%s]或状态不正常",sJgbh, sGyh ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_GY_NOTFOUND,MSG_APP_GY_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    memcpy( app_gyxx, &sdb_app_gyxx, sizeof(sdb_app_gyxx));
    return 0;
}

/*私有函数，获取交易柜员日、月累计金额,type 1:当日， 2:当月，出参：Ljje*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取柜员累计交易金额信息出错", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    *Ljje = atof( sBuf );
    return 0;
}

/*私有函数，获取交易机构日、月累计金额,type 1:当日， 2:当月，出参：Ljje*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取机构累计交易金额信息出错", "ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    *Ljje = atof( sBuf );
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("机构累计金额[%.2f]", *Ljje ),"DEBUG");
    return 0;
}


/************************************************************************
函数名称:AuthCtrl
名称:AuthCtrl
功能:产品交易权限控制
参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组:
程 序 员: SC
发布日期: 2011-6-1
修改日期:
参数使用示例:
************************************************************************/
IRESULT AuthCtrl(HXMLTREE lXmlhandle, APP_CPJYFW *app_cpjyfw)
{
    char sCpdm[16+1]={0};    /* 产品代码 */
    char sJydm[16+1]={0};     /* 交易代码 */
    char sJygy[16+1]={0};    /* 交易柜员 */
    char sJyjg[16+1]={0};    /* 交易机构 */
    char sJyls[16+1]={0};    /* 交易流水 */
    char sPtrq[8+1]={0};     /* 平台日期 */
    char sQxkz[8+1]={0};      /* 权限控制标志 */
    char sGyjb[8+1]={0};      /* 柜员级别 */
    char sGygw[8+1]={0};      /* 柜员岗位 */
    char sSqGyjb[8+1]={0};    /* 授权柜员级别 */
    char sSqGygw[8+1]={0};    /* 授权柜员岗位 */

    double dGylj = 0.00;  /* 柜员累计金额 */
    double dJglj = 0.00;  /* 机构累计金额 */
    double dJyje = 0.00;  /* 交易金额 */
    char sJybz[3+1]={0};     /* 交易币种 */
    char sSqgy[16+1]={0};    /* 授权柜员 */
    char sSqjg[16+1]={0};    /* 授权柜员机构 */
    char sYhh[32+1]={0};
    char sJgjb[16+1]={0};
    APP_CPJYFW sdb_app_cpjyfw; /* 产品权限控制信息 */
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
    /* 以下变量标志交易额度有没有取过结构体，取过后标志为1，不用反复去取 */
    int  iJygyed1 = 0;
    int  iJygyed9 = 0;
    int  iJyjged1 = 0;
    int  iJyjged9 = 0;
    int  iSqgyxx  = 0;

    int  iSqgyed = 0;/* 柜员额度授权权限判断，判断通过后标志为1，不用反复去判断 */
    int  iSqjged = 0;/* 机构额度授权权限判断，判断通过后标志为1，不用反复去判断 */
    APP_CPJYGYED sdb_app_cpjygyed;
    APP_CPJYJGED sdb_app_cpjyjged;

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,"组件[AuthCtrl]执行开始","DEBUG");

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

    /* 检查交易柜员权限是否满足条件 */
    if( sdb_app_cpjyfw.qxkz[0] == '0' )  /* 柜员交易权限控制 */
    {
        memset( &sdb_app_cpjygykz, 0x00, sizeof( sdb_app_cpjygykz ) );
        iRet = GetCPJYGYKZ(lXmlhandle, &sdb_app_cpjygykz, sCpdm, sJydm);
        if( iRet )
            return iRet;

        if( atoi( sGyjb )  < atoi( sdb_app_cpjygykz.gyjb ) )  /* 柜员级别不够 */
        {
            if (sdb_app_cpjygykz.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]柜员级别不够,超限拒绝",sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_JBBZ,MSG_APP_CPJYGY_JBBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]授权柜员级别不够[%s]", sCpdm, sJydm, sGyjb ),"ERROR");
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
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygykz.sqgyjb ) )  /* 授权柜员级别不够 */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]授权柜员级别不够[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_JBBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQJBBZ, sdb_app_cpjygykz.sqgyjb ));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }
    if( sdb_app_cpjyfw.qxkz[1] == '0' )  /* 柜员单笔额度控制  */
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
                    Fmtmsg("产品[%s]交易[%s]柜员额度不够,超限拒绝",sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]额度授权柜员级别不够[%s]", sCpdm, sJydm, sGyjb ),"ERROR");
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
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygyed.sqgyjb ) )  /* 授权柜员级别不够 */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]额度授权柜员级别不够[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqgyed = 1;/*授权柜员额度判断通过*/
        }
    }
    if( sdb_app_cpjyfw.qxkz[2] == '0' && iSqgyed == 0 )  /* 柜员日累计额度控制  */
    {
        /* 统计当天柜员累计额度 */
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
             Fmtmsg("当日柜员累计[%.2f]交易金额[%.2f]柜员日累计额度[%.2f]", \
             dGylj, dJyje, sdb_app_cpjygyed.rljed ),"DEBUG");
        if( ( dGylj + dJyje - sdb_app_cpjygyed.rljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]柜员日累计额度不够,超限拒绝", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]柜员日累计授权柜员级别不够[%s]", sCpdm, sJydm, sGyjb ),"ERROR");
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
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygyed.sqgyjb ) )  /* 授权柜员级别不够 */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]柜员日累计授权柜员级别不够[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqgyed = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[3] == '0' && iSqgyed == 0 )  /* 柜员月累计额度控制  */
    {
        /* 统计当月柜员累计额度 */
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
            Fmtmsg("当月柜员累计[%.2f]交易金额[%.2f]柜员月累计额度[%.2f]",\
            dGylj, dJyje, sdb_app_cpjygyed.yljed ),"DEBUG");

        if( ( dGylj + dJyje - sdb_app_cpjygyed.yljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]柜员月累计额度不够,超限拒绝", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,MSG_APP_CPJYGY_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]柜员月累计授权柜员级别不够[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
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
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjygyed.sqgyjb ) )  /* 授权柜员级别不够 */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]柜员月累计授权柜员级别不够[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYGY_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYGY_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqgyed = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[4] == '0' )  /* 机构单笔额度控制  */
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
            Fmtmsg("机构单笔额度[%.2f]日额度[%.2f]月累计额度[%.2f]", \
            sdb_app_cpjyjged.dbed, sdb_app_cpjyjged.rljed, sdb_app_cpjyjged.yljed ),"DEBUG");
        /* 交易金额超过限制 */
        if( ( dJyje - sdb_app_cpjyjged.dbed ) > 0.01 )
        {
            if (sdb_app_cpjyjged.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]机构单笔额度不够,超限拒绝", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("产品[%s]交易[%s]机构单笔额度授权柜员级别不够[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
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
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjyjged.sqgyjb ) )  /* 授权柜员级别不够 */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("产品[%s]交易[%s]机构单笔额度授权柜员级别不够[%s]", \
                     sCpdm, sJydm, sGyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,\
                      Fmtmsg(MSG_APP_CPJYJG_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        iSqjged = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[5] == '0' && iSqjged == 0 )  /* 机构日累计额度控制 */
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
        /* 统计当天机构累计额度 */
        dJglj=0;
        iRet = GetJGLJJE(lXmlhandle, sJyjg, sCpdm, sPtrq, 1, &dJglj);
        if ( iRet )
            return iRet;
        if( ( dJglj + dJyje - sdb_app_cpjyjged.rljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]机构日累计额度不够,超限拒绝", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("产品[%s]交易[%s]机构日累计额度授权柜员级别不够[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
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
            if( atoi( sdb_app_gyxx_sq.gyjb )  < atoi( sdb_app_cpjyjged.sqgyjb ) )  /* 授权柜员级别不够 */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]机构日累计额度授权柜员级别不够[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ, \
                    Fmtmsg(MSG_APP_CPJYJG_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            iSqjged = 1;
        }
    }
    if( sdb_app_cpjyfw.qxkz[6] == '0' && iSqjged == 0 )  /* 机构月累计额度控制 */
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
        /* 统计当月机构累计额度 */
        dJglj=0;
        iRet = GetJGLJJE(lXmlhandle, sJyjg, sCpdm, sPtrq, 2, &dJglj);
        if ( iRet )
            return iRet;
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("机构累计金额[%.2f]", \
        sdb_app_cpjyjged.dbed, sdb_app_cpjyjged.rljed, sdb_app_cpjyjged.yljed ),"DEBUG");
        if( ( dJglj + dJyje - sdb_app_cpjyjged.yljed ) > 0.01 )
        {
            if (sdb_app_cpjygyed.cxcl[0] == '0')
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                Fmtmsg("产品[%s]交易[%s]机构月累计额度不够,超限拒绝", sCpdm, sJydm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,MSG_APP_CPJYJG_EDBZ );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if(strlen(sSqgy) == 0)
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                     Fmtmsg("产品[%s]交易[%s]机构月累计额度授权柜员级别不够[%s]",sCpdm, sJydm, sGyjb ),"ERROR");
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
            if( atoi( sdb_app_gyxx_sq.gyjb )  <= atoi( sdb_app_cpjyjged.sqgyjb ) )  /* 授权柜员级别不够 */
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                    Fmtmsg("产品[%s]交易[%s]机构月累计额度授权柜员级别不够[%s]", \
                    sCpdm, sJydm, sdb_app_cpjygykz.sqgyjb ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJYJG_EDBZ,\
                    Fmtmsg(MSG_APP_CPJYJG_SQEDBZ, sdb_app_cpjygykz.sqgyjb));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            iSqjged = 1;
        }
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,"组件[AuthCtrl]执行结束","DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_Init
组件名称:App_Init
组件功能:中间业务平台2.0参数初始化
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   系统初始化     416-解析字符串            N    0 需要初始化 1不需要初始化

  2   1-输入   渠道标识       416-解析字符串            Y    若为空则不需要初始化该渠道参数

  3   1-输入   应用标识       416-解析字符串            Y    若为空则不需要初始化该应用参数

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:
参数使用示例:
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
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3)

    memset(sbuf,0,sizeof(sbuf));
    memset(sSYSInit,0,sizeof(sSYSInit));
    COMP_GETPARSEPARAS(1,sbuf,"系统初始化")
    pstrcopy(sSYSInit,sbuf,sizeof(sSYSInit));

    memset(sbuf,0,sizeof(sbuf));
    memset(sChannelId,0,sizeof(sChannelId));
    COMP_GETPARSEPARAS(2,sbuf,"渠道标识")
    pstrcopy(sChannelId,sbuf,sizeof(sChannelId));

    memset(sbuf,0,sizeof(sbuf));
    memset(sAppId,0,sizeof(sAppId));
    COMP_GETPARSEPARAS(3,sbuf,"应用标识")
    pstrcopy(sAppId,sbuf,sizeof(sAppId));

    memset( stmp2 , 0x00, sizeof( stmp2 ) );
    memset( sbuf , 0x00, sizeof( sbuf ) );

    /* 系统参数，自动加载 */
    if( sSYSInit[0] =='0')
    {
        iflag = 1;
        sprintf(  sbuf, " SELECT * FROM app_cskz WHERE  (cslx='0' AND jzlx='0') " );
    }
    else
    {
        sprintf(  sbuf, " SELECT * FROM app_cskz WHERE   " );
    }

    if( strlen( sChannelId ) > 0 )  /* 输入渠道标识，加载该渠道自动加载参数 */
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
    else if( strlen( sAppId ) > 0 )    /* 输入应用标识，加载该应用自动加载参数 */
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

    /* added by yangdong 20090825 未传入初始化条件 */
    if( iflag == 0 ) 
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("参数初始化条件为空"),"INFO");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    /* end of add */

    if ((cur = DCIDeclareCursor(sbuf, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_cskz,0,sizeof(sdb_app_cskz));
    while( ( iRet = DBFetch(cur, SD_APP_CSKZ, NUMELE(SD_APP_CSKZ), &sdb_app_cskz, sErrmsg ) ) > 0 )
    {
        /*对取出的数据进行处理*/
        trim(sdb_app_cskz.jdz);
        trim(sdb_app_cskz.jdm);
        COMP_HARDSETXML(sdb_app_cskz.jdm,sdb_app_cskz.jdz);
        memset(&sdb_app_cskz,0,sizeof(sdb_app_cskz));
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    DCIFreeCursor(cur);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_GetInfo
组件名称:App_GetInfo
组件功能:应用取基本信息
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   交易信息       416-解析字符串            Y    交易信息
  2   1-输入   渠道标识       416-解析字符串            Y    渠道标识
  3   1-输入   机构代码       416-解析字符串            Y    机构代码
  4   1-输入   应用标识       416-解析字符串            Y    应用标识
  5   1-输入   产品代码       416-解析字符串            Y    产品代码
  6   1-输入   联机标识       416-解析字符串            Y    联机标识
  7   1-输入   单位编号       416-解析字符串            Y    单位编号
  8   1-输入   输出控制       416-解析字符串            Y    输出控制   0控制 1不控制

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:
参数使用示例:
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
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(8)

    /* 控制为0则出错不输出信息,否则不做校验输出信息*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(8,sbuf,"控制标志");
    pstrcopy(sCtrlFlag,sbuf,sizeof(sCtrlFlag));

    /* 单位产品协议信息获取 (有扩展属性) */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(1,sbuf,"业务编号");
    pstrcopy(sYwbh,sbuf,sizeof(sYwbh));
    trim(sYwbh);
    if( strlen(sYwbh) > 0)
    {
        iRet = GetDWCPXY(lXmlhandle, sYwbh, sCtrlFlag);
        if (iRet != 0)
            return iRet;

        /* 单位产品协议取成功以后，产品信息获取 (有扩展属性) */
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

    /* 交易信息获取 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(2,sbuf,"交易代码")
    pstrcopy(sJydm,sbuf,sizeof(sJydm));
    trim(sJydm);
    if( strlen(sJydm) > 0)
    {
        iRet = GetJYXX(lXmlhandle, sJydm, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* 渠道信息获取 (有扩展属性)--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(3,sbuf,"渠道标识")
    pstrcopy(sQdbs,sbuf,sizeof(sQdbs));
    trim(sQdbs);
    if( strlen(sQdbs) > 0)
    {
        iRet = GetQDXX(lXmlhandle, sQdbs, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* 机构信息获取 (无扩展属性)--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(4,sbuf,"机构代码")
    pstrcopy(sJgdm,sbuf,sizeof(sJgdm));
    trim(sJgdm);
    if( strlen(sJgdm) > 0)
    {
        iRet = GetJGXX(lXmlhandle, sJgdm, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* 应用信息获取 (无扩展属性)--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(5,sbuf,"应用标识")
    pstrcopy(sYybs,sbuf,sizeof(sYybs));
    trim(sYybs);
    if( strlen(sYybs) > 0)
    {
        iRet = GetYYXX(lXmlhandle, sYybs, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* 单位信息获取--B */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(6,sbuf,"单位编号")
    pstrcopy(sDwbh,sbuf,sizeof(sDwbh));
    trim(sDwbh);
    if( strlen(sDwbh) > 0)
    {
        iRet = GetDWXX(lXmlhandle, sDwbh, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    /* 联机标识信息获取 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(7,sbuf,"联机标识")
    pstrcopy(sTxdm,sbuf,sizeof(sTxdm));
    trim(sTxdm);
    if( strlen(sTxdm) > 0)
    {
        iRet = GetTXXX(lXmlhandle, sTxdm, sCtrlFlag);
        if (iRet != 0)
            return iRet;
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_CPCtrl
组件名称:App_CPCtrl
组件功能:产品关系控制
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   产品代码       416-解析字符串            N    产品代码
  2   1-输入   交易金额       416-解析字符串            Y    交易金额
  3   1-输入   客户编号       416-解析字符串            Y    客户编号

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组:
程 序 员: YangDong
发布日期: 2009-6-22
修改日期:
参数使用示例:

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

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3)
    memset(sbuf,0,sizeof(sbuf));
    memset( sCpdm, 0x00, sizeof( sCpdm ) );
    COMP_GETPARSEPARAS(1,sbuf,"产品代码")
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));

    memset(sbuf,0,sizeof(sbuf));
    memset( sJyje, 0x00, sizeof( sJyje ) );
    COMP_GETPARSEPARAS(2,sbuf,"交易金额")
    pstrcopy(sJyje,sbuf,sizeof(sJyje));

    memset(sbuf,0,sizeof(sbuf));
    memset( sYhh, 0x00, sizeof( sYhh ) );
    COMP_GETPARSEPARAS(3,sbuf,"用户号")
    pstrcopy(sYhh,sbuf,sizeof(sYhh));

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
             Fmtmsg("APP:产品代码[%s],交易金额[%s],用户号[%s] ",sCpdm,sJyje,sYhh ),"DEBUG");

    memset(&sdb_app_cpxx2,0,sizeof(APP_CPXX));
    memset(&sdb_app_jyxx2,0,sizeof(APP_JYXX));
    memset(&sdb_app_cpqdgx,0,sizeof(APP_CPQDGX));
    memset(&sdb_app_cpjggx,0,sizeof(APP_CPJGGX));
    memset(&sdb_app_cpjyfw,0,sizeof(APP_CPJYFW));
    memset(&sdb_app_khcpqy,0,sizeof(APP_KHCPQY));

    /* -------------产品基本信息获取 开始----------------*/
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
    COMP_SOFTGETXML(XMLNM_APP_CPXX_QYMS   , sdb_app_cpxx2.qyms);/*签约模式*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_KKFS   , sdb_app_cpxx2.kkfs);/*扣款方式*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_ZJYYH  , sdb_app_cpxx2.zjyyh);/*主机应用号*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_ZJZYYH , sdb_app_cpxx2.zjzyyh);/*主机子应用号*/
    COMP_SOFTGETXML(XMLNM_APP_CPXX_RZMS   , sdb_app_cpxx2.rzms);/*日志模式*/

    if( strlen( sdb_app_cpxx2.cpdm ) <= 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_CPDM_NULL,MSG_APP_CPDM_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* -------------产品基本信息获取 结束----------------*/

    /* 产品交易关系检查 */
    COMP_SOFTGETXML(XMLNM_APP_JYXX_CPXG,  sdb_app_jyxx2.cpxg);
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYDM,  sdb_app_jyxx2.jydm);
    trim( sdb_app_jyxx2.cpxg );
    if( sdb_app_jyxx2.cpxg[0] == '0' )  /* 交易服务和产品相关 */
    {
        memset( sbuf, 0x00, sizeof( sbuf ) );
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpjyfw\
            WHERE  cpdm ='%s' AND jydm='%s'",sCpdm,sdb_app_jyxx2.jydm );
        iRet = fprv_SelToStruct( sSql1, SD_APP_CPJYFW, NUMELE(SD_APP_CPJYFW), &sdb_app_cpjyfw );
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取产品交易服务信息出错", "ERROR");
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
            /* 交易时间控制标志 0控制 1不控制 */
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
    
            /* 限额控制 */
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

            /* -------------产品客户签约关系控制 开始----------------*/
            if(0 == memcmp(sdb_app_cpjyfw.qykzbz,"0",1) ) /* 0控制 1 不控制 */
            {
                if( strlen( sYhh ) <= 0 )
                {
                    fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                /* 按 用户号+产品代码 查询 */
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ), "SQL SELECT  * FROM app_khcpqy\
                    WHERE  cpdm ='%s' and yhh1 ='%s'",sdb_app_cpxx2.cpdm, sYhh );
                iRet = fprv_SelToStruct( sSql1, SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy);
                if( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取签约信息出错", "ERROR");
                    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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
                if( sdb_app_khcpqy.qyzt[0] != '0' ) /*0正常 1撤消*/
                {
                    fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY,MSG_APP_KHCPQY);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                /* 签约开通渠道检查 */
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
            /* -------------产品客户签约关系控制 结束----------------*/
            /* 产品权限检查控制 */
            /* added by yangdong 20111028 只有权限控制不全为1时才需要 */
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
        /* -------产品渠道关系控制(控制粒度到产品一级，该产品所有调用交易遵循统一规则) 开始----------*/
        if( 0 == memcmp(sdb_app_cpxx2.qdkzbz,"0",1) ) /* 0控制  1不控制 */
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
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( iRet == 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                      Fmtmsg("  无满足条件产品[%s]渠道[%s]信息", sCpdm, sQdbs ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX,MSG_APP_CPQDGX);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* 先判断状态 */
            if( sdb_app_cpqdgx.zt[0] !='0' ) /*0允许 1不允许*/
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX,MSG_APP_CPQDGX);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            /* 产品渠道时间控制 --B*/
            if( 0 == memcmp(sdb_app_cpqdgx.sjkzbz,"0",1) ) /*0控制 1不控制*/
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

            /* 产品渠道限额控制 --B*/
            if( 0 == memcmp(sdb_app_cpqdgx.xekzbz,"0",1) ) /*0控制 1不控制*/
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

            /* 如果是反交易，进行产品渠道冲正控制 --B*/
            COMP_HARDGETXML(XMLNM_APP_JYXX_JYLX,sdb_app_jyxx2.jylx);
            if( 0 == memcmp(sdb_app_jyxx2.jylx,"1",1) ) /*0正交易 1反交易 9其他*/
            {
                memset( sQdcz, 0x00, sizeof( sQdcz ) );
                COMP_HARDGETXML( XMLNM_APP_QDXX_CZBZ,sQdcz );
                trim( sQdcz );
                /* 先判断渠道是否允许冲正，然后判断产品渠道关系是否允许冲正 */
                if( ( 0 == memcmp( sQdcz, "1",1) ) || \
                          0  == memcmp(sdb_app_cpqdgx.czbz,"1",1) ) /* 0允许 1不允许*/
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

        /* -------------产品机构关系控制 开始----------------*/
        if(0 != memcmp(sdb_app_cpxx2.jgkzcs,"0",1) )
        {
            memset(sXmlnode,0,sizeof(sXmlnode));
            /* 根据机构控制级别，获取上级机构编号 */
            sprintf( sXmlnode, "/app/org/org_id%d", atol(sdb_app_cpxx2.jgkzcs) );
            memset(sJgbh,0,sizeof(sJgbh));
            COMP_SOFTGETXML(sXmlnode,sJgbh);
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpjggx\
                 WHERE  cpdm = '%s' and jgbh = '%s'",sdb_app_cpxx2.cpdm, sJgbh );
            iRet = fprv_SelToStruct( sSql1, SD_APP_CPJGGX, NUMELE(SD_APP_CPJGGX), &sdb_app_cpjggx);
            if( iRet < 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取产品交易服务信息出错", "ERROR");
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if( iRet == 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,\
                           Fmtmsg("  无满足条件产品[%s]机构[%s]信息,控制参数[%s]",\
                           sCpdm,sJgbh,sdb_app_cpxx2.jgkzcs ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,Fmtmsg("无满足条件产品机构信息"));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* 先判断状态 */
            if( 0 == memcmp(sdb_app_cpjggx.zt,"1",1) ) /*0允许 1不允许*/
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPJGGX),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_APP_CPJGGX,MSG_APP_CPJGGX);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            /* 产品机构时间控制 --B*/
            if( 0 == memcmp(sdb_app_cpjggx.sjkzbz,"0",1) )  /*0控制 1不控制*/
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
        /* -------------产品通讯信息由接出层调用公共组件获取----------------*/
    }

    /* -------------业务日期/业务流水生成 开始----------------*/
    if( atoi(sdb_app_cpxx2.ywrqlx) == 1) /*1公共 2私有*/
    {
        memset(stmp2,0,sizeof(stmp2));

        COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ,stmp2);
        /*业务日期为空,则赋值 */
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
        /* 生成私有流水号与帐务日期 --B*/
        /* 以产品代码做键值 */
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
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}


/************************************************************************
动态组件函数定义
组件函数名称: SApp_InsSerial
组件名称:     SApp_InsSerial
组件功能:     预记平台公共流水
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员: YangDong
发布日期:
修改日期: 20090623
参数使用示例:
************************************************************************/
IRESULT SApp_InsSerial(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    APP_DRLS sdb_app_drls;
    char sSystime[6+1];
    char sBuf[256];
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    memset( &sdb_app_drls, 0x00, sizeof( sdb_app_drls ) );

    /*平台日期*/
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
    
    /*平台时间*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_SYSTIME,sBuf);
    pstrcopy(sdb_app_drls.ptsj,sBuf,sizeof(sdb_app_drls.ptsj));
    
    /*平台流水号*/
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
    
    /*原平台流水号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YPTLSH,sBuf);
    sdb_app_drls.yptls = atoi(sBuf);
    
    /*交易机构*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJG,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.jyjg,sBuf,sizeof(sdb_app_drls.jyjg));
    
    /*交易柜员*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYGY,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.jygy,sBuf,sizeof(sdb_app_drls.jygy));
    
    /*渠道标识*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_QDBS,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.qdbs,sBuf,sizeof(sdb_app_drls.qdbs));
    
    /*终端设备编号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_ZDSBBH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.zdsbbh,sBuf,sizeof(sdb_app_drls.zdsbbh));
    
    /*应用标识*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YYBS,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.yybs,sBuf,sizeof(sdb_app_drls.yybs));
    
    /* 产品代码 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.cpdm,sBuf,sizeof(sdb_app_drls.cpdm ));
    
    /*业务编号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YWBH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.ywbh,sBuf,sizeof(sdb_app_drls.ywbh));
    
    /*入账标志*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    /* COMP_SOFTGETXML(XMLNM_APP_REQ_RZBZ,sBuf); */
    COMP_SOFTGETXML(XMLNM_APP_JYXX_RZBZ,sBuf); 
    pstrcopy(sdb_app_drls.rzbz,sBuf,sizeof(sdb_app_drls.rzbz));
    
    /*交易代码*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    /*
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYDM,sBuf);
    */
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYDM,sBuf); 
    trim(sBuf);
    pstrcopy(sdb_app_drls.jydm,sBuf,sizeof(sdb_app_drls.jydm));
    
    /*用户编号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YHBH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.yhbh,sBuf,sizeof(sdb_app_drls.yhbh));
    
    /*现转标志*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_XZBZ,sBuf);
    pstrcopy(sdb_app_drls.xzbz,sBuf,sizeof(sdb_app_drls.xzbz));
    
    /*借贷标志*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JDBZ,sBuf);
    pstrcopy(sdb_app_drls.jdbz,sBuf,sizeof(sdb_app_drls.jdbz));
    
    /*银行帐号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YHZH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.yhzh,sBuf,sizeof(sdb_app_drls.yhzh));
    
    /*added by yr 20120918 账户类型*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_ZHLX,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.zhlx,sBuf,sizeof(sdb_app_drls.zhlx));
    
    /*对方帐号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_DFZH,sBuf);
    trim(sBuf);
    pstrcopy(sdb_app_drls.dfzh,sBuf,sizeof(sdb_app_drls.dfzh));
    
    /*交易金额*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJE,sBuf);
    sdb_app_drls.jyje = atof(sBuf);
    
    /*手续费*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_SXF,sBuf);
    sdb_app_drls.sxf = atof(sBuf);
    
    /*批次编号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_PCBH,sBuf);
    sdb_app_drls.pcbh = atof(sBuf);
    
    /*交易状态*/
    strcpy(sdb_app_drls.jyzt,"9");
    
    /*交易响应码*/
    strcpy(sdb_app_drls.jyxym, "99999");
    
    /*扩展1*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_EXTFLD1,sBuf);
    trim(sBuf);
    if ( strlen(sBuf)<=0)
        strcpy(sdb_app_drls.extfld1," ");
    else
        pstrcopy(sdb_app_drls.extfld1,sBuf,sizeof(sdb_app_drls.extfld1));
    
    /*扩展2*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback(); /*add by chenxm 2015-1-7*/
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("数据异常：插入数据库语句失败[%s]", sErrmsg ),fpub_GetCompname(lXmlhandle))
    }

    DCICommit();

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SApp_UpdSerial
组件名称:     SApp_UpdSerial
组件功能:     更新平台公共流水
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   交易状态        416-解析字符串        N    0 成功 1 失败

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员: YangDong
发布日期:
修改日期: 20090623
参数使用示例:

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

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_GETPARSEPARAS(1,sBuf,"交易状态")
    pstrcopy(sJyzt, sBuf,sizeof(sJyzt));

    /*平台日期*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    pstrcopy(sPtrq, sBuf,sizeof(sPtrq));

    /*平台流水号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sBuf);
    iPtls = atoi(sBuf);

    /*交易类型*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYLX,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.jylx, sBuf,sizeof( sdb_app_drls.jylx ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " jylx='%s',", sdb_app_drls.jylx );
        iStrLen = strlen( sSet );
    }

    /* 入账标志 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_JYXX_RZBZ,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.rzbz, sBuf,sizeof( sdb_app_drls.rzbz ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " rzbz='%s',", sdb_app_drls.rzbz );
        iStrLen = strlen( sSet );
    }

    /*原平台流水号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_YPTLSH,sBuf);
    iYptls = atoi(sBuf);
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " yptls=%d,", iYptls );
        iStrLen = strlen( sSet );
    }

    /*产品代码*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.cpdm, sBuf,sizeof( sdb_app_drls.cpdm ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " cpdm='%s',", sdb_app_drls.cpdm  );
        iStrLen = strlen( sSet );
    }

    /*对方帐号*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_DFZH,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.dfzh, sBuf,sizeof( sdb_app_drls.dfzh ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " dfzh='%s',", sdb_app_drls.dfzh );
        iStrLen = strlen( sSet );
    }

    /*交易金额*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_REQ_JYJE,sBuf);
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " jyje=%.2f,", atof( sBuf ) );
        iStrLen = strlen( sSet );
    }

    /*手续费*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_APP_SXF_SXF,sBuf);
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " sxf=%.2f,", atof( sBuf ) );
        iStrLen = strlen( sSet );
    }

    /*交易响应码*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_RESPCODE,sBuf);
    trim(sBuf);
    pstrcopy( sdb_app_drls.jyxym, sBuf,sizeof( sdb_app_drls.jyxym ));
    if( strlen( sBuf ) > 0 )
    {
        sprintf( sSet+iStrLen, " jyxym ='%s',", sdb_app_drls.jyxym );
        iStrLen = strlen( sSet );
    }

    /*交易响应信息*/
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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

    /* 冲正交易成功后，修改原交易状态 为7 已冲正 */
    if( sJylx[0] == '1' && sJyzt[0] == '0' )  /* 成功的反交易 */
    {
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), " UPDATE app_drls SET jyzt='7' WHERE ptrq='%s' AND ptls=%d ",\
                             sPtrq, iYptls );
        iRet = DCIExecuteDirect( sSql1 );
        if( iRet < 1 )
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    if (DCICommit() != 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("数据异常：提交事务失败[%s]", DCILastError()), fpub_GetCompname(lXmlhandle))
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SApp_CPCtrl_Reversal
组件名称: App_CPCtrl_Reversal
组件功能: 冲正交易的产品关系控制
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   产品代码       416-解析字符串            N    产品代码            
  1   1-输入   渠道标识       416-解析字符串            N    渠道标识

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员: YangDong
发布日期: 2009-7-20
修改日期:
参数使用示例:

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

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(2)

    memset(sbuf,0,sizeof(sbuf));
    memset( sCpdm, 0x00, sizeof( sCpdm ) );
    COMP_GETPARSEPARAS(1,sbuf,"产品代码")
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));

    /* 产品代码获取方式更改 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM, sbuf);
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));
    trim(sCpdm);
    
    memset(sbuf,0,sizeof(sbuf));
    memset( sQdbs, 0x00, sizeof( sQdbs ) );
    COMP_GETPARSEPARAS(2,sbuf,"渠道标识")
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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
    if( sQdkz[0] == '1' )   /* 不控制 */
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }

    /* 渠道是否允许自动冲正 */
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
    /* 判断产品渠道关系是否允许冲正 */

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT zdczbz FROM app_cpqdgx WHERE  qdbs = '%s' AND cpdm ='%s'",sQdbs, sCpdm );
    iRet = DBSelectToVarChar(sErrmsg, sQdcz, sSql1);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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
          0  == memcmp( sQdCpcz,"1",1) ) /* 0允许 1不允许*/
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_CPQDGX_CZ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_CPQDGX_CZ,MSG_APP_CPQDGX_CZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}


/************************************************************************
动态组件函数定义
组件函数名称: SApp_GetYwrq
组件名称: sApp_GetYwrq
组件功能: 获取业务日期，流水号
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   产品代码       416-解析字符串            N    产品代码            

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员: YangDong
发布日期: 2009-7-20
修改日期:
参数使用示例:

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

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)

    memset(sbuf,0,sizeof(sbuf));
    memset( sCpdm, 0x00, sizeof( sCpdm ) );
    COMP_GETPARSEPARAS(1,sbuf,"产品代码")
    pstrcopy(sCpdm,sbuf,sizeof(sCpdm));
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT ywrqlx FROM app_cpxx WHERE  cpdm = '%s'",sCpdm );
    iRet = DBSelectToVarChar(sErrmsg, sRqlx, sSql1);
    if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, "获取产品交易服务信息出错", "ERROR");
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

    /* -------------业务日期/业务流水生成 开始----------------*/
    if( atoi( sRqlx) == 1) /*1公共 2私有*/
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
        /* 生成私有流水号与帐务日期 --B*/
        /* 以产品代码做键值 */
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
    /* -------------业务日期/业务流水生成 结束----------------*/

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_Enmu
组件名称:SApp_Enmu
组件功能:中间业务平台2.0 多重枚举组件
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明
  1   1-输入   枚举ID     416-解析字符串            N   枚举ID

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员: duyj
发布日期:
修改日期:
参数使用示例:
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
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    COMP_PARACOUNTCHKMIN(1)
    
    memset(sbuf,0,sizeof(sbuf));
    memset(smjid,0,sizeof(smjid));
    COMP_GETPARSEPARAS(1,sbuf,"枚举ID")
    pstrcopy(smjid,sbuf,sizeof(smjid));
  
    memset( sbuf , 0x00, sizeof( sbuf ) );
    sprintf( sbuf , "SELECT * FROM app_mjsj WHERE mjid='%s' ",smjid);
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * from APP_MJSX WHERE mjid = '%s' and sxlx = '1' order by sxxh",smjid );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
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

    memset(&sdb_app_mjsx,0,sizeof(APP_MJSX));
    while( ( iRet = DBFetch(cur, SD_APP_MJSX, NUMELE(SD_APP_MJSX), &sdb_app_mjsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_mjsx.mjsm); /*枚举说明*/
        trim(sdb_app_mjsx.sxlx); /*属性类型 1条件 2结果*/
        trim(sdb_app_mjsx.sxxh); /*属性序号*/
        trim(sdb_app_mjsx.sxmc); /*属性名称*/
        trim(sdb_app_mjsx.sxnr); /*属性内容位置*/
        trim(sdb_app_mjsx.sxsm); /*属性说明*/

        /* 参数值(支持解析字符串配置) */
        memset(sXmlBuf,0,sizeof(sXmlBuf));
        COMP_SOFTGETXML(sdb_app_mjsx.sxnr,sXmlBuf);
        trim(sXmlBuf);
        sprintf( sbuf, "%s AND ( req%d = '%s' ) ",sbuf,atoi(sdb_app_mjsx.sxxh), sXmlBuf);

        memset(&sdb_app_mjsx,0,sizeof(sdb_app_mjsx));
    }
    
    if ( iRet < 0 )    
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }  
          
    DCIFreeCursor(cur);

    /*取值*/
    if ((cur = DCIDeclareCursor(sbuf, DCI_STMT_LOCATOR)) == -1)
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
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("获取枚举信息[%s]出错",sSql1),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此枚举信息[%s]",sSql1),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_APP_JYDM_NOTFOUND,MSG_APP_JYDM_NOTFOUND );
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    } 
    DCIFreeCursor(cur);

    /*赋值*/
    memset(sSql1, 0, sizeof(sSql1));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM APP_MJSX WHERE mjid ='%s' and  sxlx='2' order by sxxh",smjid );
    memset(&sdb_app_mjsx,0,sizeof(sdb_app_mjsx));
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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
    while( ( iRet = DBFetch(cur, SD_APP_MJSX, NUMELE(SD_APP_MJSX), &sdb_app_mjsx, sErrmsg ) ) > 0 )
    {
        trim(sdb_app_mjsx.mjsm); /*枚举说明*/
        trim(sdb_app_mjsx.sxlx); /*属性类型 1条件 2结果*/
        trim(sdb_app_mjsx.sxxh); /*属性序号*/
        trim(sdb_app_mjsx.sxmc); /*属性名称*/
        trim(sdb_app_mjsx.sxnr); /*属性内容位置*/
        trim(sdb_app_mjsx.sxsm); /*属性说明*/
        
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
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }        
    DCIFreeCursor(cur);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SApp_CheckNull
组件名称:     SApp_CheckNull
组件功能:     判断某个XML元素值是否为空，包括空格
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员: sc
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SApp_CheckNull(HXMLTREE lXmlhandle)
{
    char sbuf[256];
    int  iParas = 0;
    fpub_InitSoComp(lXmlhandle);
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    COMP_PARACOUNTCHKMIN(1)

    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(1,sbuf,"XML节点名")
    trim( sbuf );

    if( strlen( sbuf ) == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
            Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    else
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG,\
            Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
        /* modify by yr 20120910 失败返回改为1 */
        /*
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
        */
        fpub_SetCompStatus(lXmlhandle,1);
        return 0;
    }
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_UpdQDZT
组件名称:SApp_UpdQDZT
组件功能:更新通讯安全信息表操作
         根据签到签退交易更新签到状态标志
组件参数:
 序号 参数类型  参数名称         资源类别         缺省值  可空  参数说明

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: 
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SApp_UpdQDZT(HXMLTREE lXmlhandle)
{
    char sQdzt[1+1]={0};   /* 1签退  2签到 */
    char sLjbs[8+1]={0};
    char sbuf[255];
    int  iParas = 0;
    int  iRet = -1;
 
    fpub_InitSoComp(lXmlhandle);
    COMP_PARACOUNTCHKMIN(2)

    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(1,sbuf,"联机标识");
    pstrcopy(sLjbs,sbuf,sizeof(sLjbs));
    trim(sLjbs);

    memset(sbuf,0,sizeof(sbuf));
    COMP_GETPARSEPARAS(2,sbuf,"签到状态");
    pstrcopy(sQdzt,sbuf,sizeof(sQdzt));
    trim(sQdzt);

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
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
               Fmtmsg("更新签退签到状态失败, sql[%s],[%s]", sSql1, DCILastError()),"ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_APP_TXAQXX_SB, MSG_APP_TXAQXX_SB);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCICommit() == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("数据异常：提交事务失败[%s]", DCILastError()), fpub_GetCompname(lXmlhandle))
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
    return 0; 
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_DynExecSql
组件名称:SApp_DynExecSql
组件功能:
组件参数:
 序号 参数类型  参数名称         资源类别         缺省值  可空  参数说明
组件结果状态:
  结果状态码         结果说明
  缺省
日志信息:
  日志级别           日志宏
响应信息:
  内部响应码         内部响应信息
主要操作元素:
  元素路径          操作
主要操作库表:
  表名              操作
使用限制:
项 目 组: 
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SApp_DynExecSql(HXMLTREE lXmlhandle)
{
    char sSql[1024];
    int  i,iParas;
    char  sCommitFlag[1+1];
    char  sTransFlag[1+1];
    int   iRet;

    fpub_InitSoComp(lXmlhandle);
  
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    COMP_PARACOUNTCHKMIN(3)

    /* by yr 20120918 增加初始化 */
    memset( sSql, 0, sizeof( sSql ));
    memset( sTransFlag, 0, sizeof( sTransFlag ));
    memset( sCommitFlag, 0, sizeof( sCommitFlag ));
        
    COMP_GETPARSEPARAS( 1,sSql,"查询语句")
    LOG(LM_STD,Fmtmsg("组件执行SQL[%s]", sSql ),"INFO")  
    
    COMP_GETPARSEPARAS( 2,sTransFlag,"启动事务标志")  /* 1 不起事务， 0 默认起事务 */
    LOG(LM_STD,Fmtmsg("sTransFlag[%s]", sTransFlag),"INFO") 
    
    COMP_GETPARSEPARAS( 3,sCommitFlag,"提交事务标志") /* 1 不提交事务 0 默认提交 */
    LOG(LM_STD,Fmtmsg("sCommitFlag[%s]", sCommitFlag),"INFO")

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行SQL[%s]",fpub_GetCompname(lXmlhandle),sSql),"DEBUG")  

    if( sTransFlag[0] != '1' )
    {
        if( DCIBegin() != 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    if( iRet = DCIExecuteDirect( sSql ) < 0 )
    {
        LOG(LM_STD,Fmtmsg("执行SQL[%s]失败",sSql ),"ERROR")  
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
        return COMPRET_FAIL;
    }

    if( sCommitFlag[0] != '1' ) /* 提交标志不为 不提交 */
    {
        /* 提交事务 */
        if (DCICommit() != 0)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            LOGRET(-1, LM_STD, Fmtmsg("数据异常：提交事务失败[%s]", DCILastError()), fpub_GetCompname(lXmlhandle))
        }
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

  return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_GetPara
组件名称:SApp_GetPara
组件功能:根据参数键值，获取参数
组件参数:
 序号 参数类型  参数名称         资源类别         缺省值  可空  参数说明
组件结果状态:
  结果状态码         结果说明
  缺省
日志信息:
  日志级别           日志宏
响应信息:
  内部响应码         内部响应信息
主要操作元素:
  元素路径          操作
主要操作库表:
  表名              操作
使用限制:
项 目 组: 
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SApp_GetPara(HXMLTREE lXmlhandle)
{
    APP_CSKZ sdb_app_cskz;
    char sPkey[40+1];
    int  i,iParas;
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);
  
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")   

    COMP_PARACOUNTCHKMIN(1)

    memset( sPkey, 0x00, sizeof( sPkey ) );
    COMP_GETPARSEPARAS( 1,sPkey,"参数键值")

    memset(&sdb_app_cskz,0,sizeof(sdb_app_cskz));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cskz WHERE  csjz = '%s'",sPkey );
    iRet = fprv_SelToStruct( sSql1, SD_APP_CSKZ, NUMELE(SD_APP_CSKZ), &sdb_app_cskz );
    if ( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        LOG(LM_STD,Fmtmsg("获取参数[%s]失败", sPkey ),"ERROR")  
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg("无此参数信息[%s]",sPkey),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*对取出的数据进行处理*/
    trim(sdb_app_cskz.jdz);
    trim(sdb_app_cskz.jdm);
    COMP_HARDSETXML(sdb_app_cskz.jdm,sdb_app_cskz.jdz);

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_GetSeries
组件名称:SApp_GetSeries
组件功能:根据键值，获取序列当前值
组件参数:
 序号 参数类型  参数名称         资源类别         缺省值  可空  参数说明
组件结果状态:
  结果状态码         结果说明
  缺省
日志信息:
  日志级别           日志宏
响应信息:
  内部响应码         内部响应信息
主要操作元素:
  元素路径          操作
主要操作库表:
  表名              操作
使用限制:
项 目 组: 
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SApp_GetSeries(HXMLTREE lXmlhandle)
{
    char sPkey[40+1];
    int  i,iParas;
    long lSeries = 0;
    char sBuf[32];
    char sNode[64+1];
    
    fpub_InitSoComp(lXmlhandle);
  
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    COMP_PARACOUNTCHKMIN(2)

    memset( sPkey, 0x00, sizeof( sPkey ) );
    COMP_GETPARSEPARAS( 1,sPkey,"参数键值")

    memset( sNode, 0x00, sizeof( sNode) );
    COMP_GETPARSEPARAS( 2,sNode,"xml节点名")

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

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}
