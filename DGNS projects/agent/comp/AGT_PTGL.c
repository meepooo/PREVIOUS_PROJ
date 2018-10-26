/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V4.1.0.1
操作系统:
文件名称:AGT_PUB.c
文件描述:代理业务平台管理类处理组件集合
项 目 组:
程 序 员:nierui
发布日期:2009年7月24日
修改日期: 20110711
修订内容: 更改日志输出方式
程 序 员:YangDong
修改日期: 20140918
修订内容: DCI改造
*********************************************************************/

#include "gaps_head.h"
#include "../incl/agent_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
          <root>\
          <soname>AGT_PTGL.so</soname>\
          <sosrcname>AGT_PTGL.c</sosrcname>\
          <sonote>AGENT平台管理组件集合</sonote>\
          <version>\
          <rec ver=\"2.0.1.1\" modify=\"2010-4-1 15:08\" programer=\"NieRui\" filesize=\"1104980\">HS-AgentV2.0整理</rec>\
          <rec ver=\"2.1.0.1\" modify=\"2011-11-1 13:08\" programer=\"S..C\" filesize=\"1129574\">HS-AgentV2.1改造</rec>\
          <rec ver=\"4.1.0.1\" modify=\"2014-09-18 13:08\" programer=\"YangDong\" filesize=\"1129574\">DCI改造</rec>\
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

char sSql1[512];
/******************************************************************************
组件名称: SAGENT_CHECK_DETAIL
组件功能:代收付应用与主机明细对账
处理说明：处理的原则,以主机明细为准,有不平时登记对账不平表。同时修改当日流
          水表对账标志。
   
组件参数:
序号 参数名称         资源类别   缺省值         是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
 
项 目 组: 中间业务产品研发组
程 序 员:nierui
发布日期:2009年2月
修改日期:2009年7月
******************************************************************************/
IRESULT SAGENT_CHECK_DETAIL(HXMLTREE lXmlhandle)
{
    AGENT_DZLSB sdb_agent_dzlsb;
    AGENT_DRLS sdb_agent_drls;
    AGENT_DZBPB sdb_agent_dzbpb;
        
    char sRunCpdmSql[512];
    char sDelSsql[512];
    char sDzrq[8+1];
    char sYwbh[16+1];
    char sJyzt[1+1];  /* 交易状态 */
    char  sBuf[256];
    char  sSqlCond[256];
    char  sAdjust[2];     /* 调整标志 */
    int   iParas,i;
    int   iCount = 0;
    int   iFlag = 0;      /* 0 对账平 1 对账不平 */
    int iRet =-1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
 
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*组件参数检查*/
    COMP_PARACOUNTCHK(3)
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"对账日期")
    trim(sBuf);
    memset(sDzrq,0,sizeof(sDzrq));
    memcpy(sDzrq,sBuf,sizeof(sDzrq)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"业务编号")
    trim(sBuf);
    memset(sYwbh,0,sizeof(sYwbh));
    strncpy(sYwbh, sBuf, sizeof(sYwbh)-1);

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"调整标志" );
    trim(sBuf);
    memset( sAdjust, 0, sizeof( sAdjust ) );
    strncpy(sAdjust, sBuf, sizeof(sAdjust)-1);
    
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    memset( sSqlCond, 0, sizeof( sSqlCond ) );
    trim( sYwbh );
    if( strlen(sYwbh) > 0 )
    {
        sprintf( sSqlCond," AND trim( ywbh )='%s'",sYwbh);
    }

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sDelSsql, 0, sizeof( sDelSsql ) );
    /* 20130111  只删除主机对账不平，并且未处理记录
    sprintf(sDelSsql, "delete from AGENT_DZBPB where dzrq='%s' %s", sDzrq,sSqlCond);
    */
    sprintf(sDelSsql, "delete from AGENT_DZBPB where dzrq='%s' AND lslx='1' AND clzt='0' %s", sDzrq,sSqlCond);
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 初始化对账状态为0 未对账 added by yangdong 20090807 */
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='0' WHERE ptrq='%s'  %s ", sDzrq, sSqlCond );
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end of add */
            
    /*主机有,平台无的记录--B*/
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    sprintf(sRunCpdmSql, "SELECT * FROM agent_dzlsb WHERE ptrq='%s' AND jyzt='0'  %s AND \
        ptls NOT IN (SELECT DISTINCT ptls FROM agent_drls WHERE ptrq='%s' %s AND jyzt='0')", \
        sDzrq,sSqlCond,sDzrq,sSqlCond);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"INFO");
    /*取主机有,平台无的流水*/
    if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
    while( ( iRet = DBFetch(cur, SD_AGENT_DZLSB, NUMELE(SD_AGENT_DZLSB), &sdb_agent_dzlsb, sErrmsg ) ) > 0 )
    {
        iFlag ++;
        /*登记不平流水表*/
        memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
        memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
        memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_dzlsb.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
        sdb_agent_dzbpb.ptls = sdb_agent_dzlsb.ptls;
        trim( sdb_agent_dzlsb.zjrq);
        memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_dzlsb.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
        trim( sdb_agent_dzlsb.zjls);
        memcpy(sdb_agent_dzbpb.zjls,sdb_agent_dzlsb.zjls,sizeof(sdb_agent_dzbpb.zjls)-1);
        trim( sdb_agent_dzlsb.jyjg);
        memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_dzlsb.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
        trim( sdb_agent_dzlsb.jygy);
        memcpy(sdb_agent_dzbpb.jygy,sdb_agent_dzlsb.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
        trim( sdb_agent_dzlsb.jybz);
        memcpy(sdb_agent_dzbpb.jybz,sdb_agent_dzlsb.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
        trim( sdb_agent_dzlsb.ywbh);
        memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_dzlsb.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
        trim( sdb_agent_dzlsb.xzbz);
        memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_dzlsb.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
        trim( sdb_agent_dzlsb.jdbz);
        memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_dzlsb.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
        sdb_agent_dzbpb.jyje=sdb_agent_dzlsb.jyje;
        sdb_agent_dzbpb.ptjyje=0.00;
        trim( sdb_agent_dzlsb.jfzh);
        memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_dzlsb.jfzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        trim( sdb_agent_dzlsb.jffzh);
        memcpy(sdb_agent_dzbpb.jffzh,sdb_agent_dzlsb.jffzh,sizeof(sdb_agent_dzbpb.jffzh)-1);
        trim( sdb_agent_dzlsb.dfzh);
        memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_dzlsb.dfzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
        trim( sdb_agent_dzlsb.dffzh);
        memcpy(sdb_agent_dzbpb.dffzh,sdb_agent_dzlsb.dffzh,sizeof(sdb_agent_dzbpb.dffzh)-1);
        memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* 流水类型 1主机对账 */
        memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* 处理状态 0未处理 */
        memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_dzlsb.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
        memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_dzlsb.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
        memcpy(sdb_agent_dzbpb.extfld3,sdb_agent_dzlsb.extfld3,sizeof(sdb_agent_dzbpb.extfld3)-1);
        memcpy(sdb_agent_dzbpb.dzbz,"3",sizeof(sdb_agent_dzbpb.dzbz)-1);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
           Fmtmsg("对账不平,主机多：主机日期[%s] 主机流水[%s] 平台日期[%s] 平台流水[%d]",\
           sDzrq, sdb_agent_dzbpb.zjls, sDzrq, sdb_agent_dzbpb.ptls),"INFO");
        /*登记对账不平表*/
        iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        /*  added by yangdong 20090807 */
        memset( sJyzt, 0x00, sizeof( sJyzt ) );
        if( sAdjust[0] == '0' )  /* 根据主机流水调整平台流水状态 */
        {
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof( sSql1 ), "SELECT jyzt FROM AGENT_DRLS WHERE ptrq='%s' AND ptls = %d", sDzrq,sdb_agent_dzlsb.ptls );
            iRet = DBSelectToVarChar(sErrmsg, sJyzt, sSql1);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if( iRet == 0 )  /* 平台无记录  在预计流水的情况下，不应该出现，除非主机返回对账流水错误 */
            {
                 LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机有平台无记录 zjrq[%s] zjls[%s]", \
                         sDzrq, sdb_agent_dzlsb.zjls ),"INFO");
            }
            /* 主机成功平台失败，则调整平台状态为成功 */
            else 
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls set jyzt='0',zjdzbz='3' \
                       WHERE ptrq ='%s' AND ptls =%d ",sDzrq, sdb_agent_dzlsb.ptls);
                iRet = DCIExecuteDirect( sSql1 ); 
                if(iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
               LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg(\
                       "主机有, 平台日期[%s] 平台流水[%d] 原状态[%s] 调整为成功", \
                       sDzrq, sdb_agent_dzlsb.ptls, sJyzt),"INFO");
            }
        }
        /*  end of add  */

        iCount ++;
    }
    DCIFreeCursor(cur);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机有平台无笔数[%d]", iCount ),"INFO");
    iCount = 0;
    /* 主机有,平台无记录 --E*/
    
    /* 主机无,平台有记录 --B*/
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    sprintf(sRunCpdmSql, " SELECT * \
                           FROM agent_drls WHERE ptrq='%s' %s AND jyzt='0' \
                           AND jydm in ('920301','920302','920303','920304')\
                           AND ptls NOT IN (SELECT DISTINCT ptls  \
                           FROM agent_dzlsb WHERE ptrq='%s' AND jyzt='0' )",sDzrq, sSqlCond, sDzrq);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
    if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
    while( ( iRet = DBFetch(cur, SD_AGENT_DRLS, NUMELE(SD_AGENT_DRLS), &sdb_agent_drls, sErrmsg ) ) > 0 )
    {
        iFlag ++;
        /*登记不平流水表*/
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
            Fmtmsg("对账不平，平台多：平台日期=[%s],平台流水=[%d]",\
            sdb_agent_drls.ptrq,sdb_agent_drls.ptls),"INFO");
        memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));

        memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
        memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_drls.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
        sdb_agent_dzbpb.ptls = sdb_agent_drls.ptls;
        memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_drls.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
        memcpy(sdb_agent_dzbpb.zjls,sdb_agent_drls.zjlsh,sizeof(sdb_agent_dzbpb.zjls)-1);
        memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_drls.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
        memcpy(sdb_agent_dzbpb.jygy,sdb_agent_drls.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
        memcpy(sdb_agent_dzbpb.jybz,sdb_agent_drls.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
        memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_drls.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
        memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_drls.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
        memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_drls.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
        sdb_agent_dzbpb.ptjyje=sdb_agent_drls.jyje;
        sdb_agent_dzbpb.jyje=0.00;
        if( sdb_agent_drls.jdbz[0]='D' )
        {
            memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        }
        else
        {
            memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        }
        memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* 流水类型 1主机对账 */
        memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* 处理状态 0未处理 */
        memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_drls.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
        memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_drls.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
        memcpy(sdb_agent_dzbpb.extfld3,sdb_agent_drls.extfld3,sizeof(sdb_agent_dzbpb.extfld3)-1);
        memcpy(sdb_agent_dzbpb.dzbz,"2",sizeof(sdb_agent_dzbpb.dzbz)-1);
        
        /*登记对账不平表*/
        iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        /*  added by yangdong 20090807 */
        if( sAdjust[0] == '0' )  /* 主机无 ，平台有 ，调整平台状态为 失败 */
        {
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1', zjdzbz='2' \
                WHERE ptrq ='%s' AND ptls =%d ",sDzrq, sdb_agent_drls.ptls);
            iRet = DCIExecuteDirect( sSql1 ); 
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机无平台有 ptrq[%s] ptls[%d] 调整为失败 ", \
                                     sDzrq, sdb_agent_drls.ptls ),"INFO");
        }
        /*  end of add  */

        iCount ++;
    }
    DCIFreeCursor(cur);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机无平台有笔数[%d]", iCount ),"INFO");
    /*主机无,平台有记录 --E*/

    /* 更新对账状态 added by yangdong 20090807 */
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='1' \
        WHERE ( ptrq='%s' ) %s AND zjdzbz = '0' ", sDzrq, sSqlCond );
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end */
   
    if( iFlag == 0 )
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "0" );  /* 主机对账状态 0 平 */
    }
    else
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "1" );  /* 主机对账状态 1 不平 */
    }
    
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}


/******************************************************************************
组件名称: SAgent_PreBptz
组件功能:代收付应用主机不平调账预处理
处理说明:组织查询对账不平表SQL 的where条件
   
组件参数:
序号 参数名称         资源类别   缺省值         是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
 
项 目 组: 中间业务产品研发组
程 序 员:nierui
发布日期:2009年7月
修改日期:
******************************************************************************/
IRESULT SAgent_PreBptz(HXMLTREE lXmlhandle)
{
    int   iYptlsh;
    char  sPtrq[8+1],sYzjlsh[16+1];
    char  sZjrq[10+1];
    char  sSqlCond[256],sYptlsh[8+1];
    char  sBuf[256],sXmlNode[128];
    int   iParas,i;

    fpub_InitSoComp(lXmlhandle);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
      
    /*组件参数检查*/
    COMP_PARACOUNTCHK(5)
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"平台日期")
    trim(sBuf);
    memset(sPtrq,0,sizeof(sPtrq));
    memcpy(sPtrq,sBuf,sizeof(sPtrq)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"原平台流水号")
    trim(sBuf);
    memset(sYptlsh,0,sizeof(sYptlsh));
    strncpy(sYptlsh, sBuf, sizeof(sYptlsh)-1);
    iYptlsh = atoi(sYptlsh);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"原主机流水号")
    trim(sBuf);
    memset(sYzjlsh,0,sizeof(sYzjlsh));
    strncpy(sYzjlsh, sBuf, sizeof(sYzjlsh)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"主机日期")
    trim(sBuf);
    memset(sZjrq,0,sizeof(sZjrq));
    strncpy(sZjrq, sBuf, sizeof(sZjrq)-1);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARAS(5,sBuf,"输出SQL")
    trim(sBuf);
    memset(sXmlNode,0,sizeof(sXmlNode));
    memcpy(sXmlNode,sBuf,sizeof(sXmlNode)-1);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("zjrq=[%s] zjls=[%s] ptrq=[%s] ptls=[%d]",sZjrq, sYzjlsh, sPtrq, iYptlsh ),"DEBUG");
    
    memset(sSqlCond,0,sizeof(sSqlCond));
    /* 传入主机日期和主机流水号，按主机流水做条件 */
    if( ( strlen(sZjrq) == 8 ) && ( strlen( sYzjlsh ) > 0 ) )
    {
        sprintf(sSqlCond, " WHERE  zjrq='%s' AND zjls='%s'", sZjrq, sYzjlsh );
    }
    else
    {
        if( strlen( sPtrq ) != 8 || iYptlsh <= 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_AGENT_SERIAL_NOTFOUND ,MSG_AGENT_SERIAL_NOTFOUND );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sprintf(sSqlCond, " WHERE  ptrq='%s' AND ptls=%d", sPtrq, iYptlsh );
      
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("sSqlCond=[%s]",sSqlCond),"DEBUG");
      
    COMP_HARDSETXML(sXmlNode,sSqlCond);
      
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}

/******************************************************************************
组件名称: SAgent_InsDzbpb
组件功能:插入主机对账不平调账流水
处理说明:
   
组件参数:
序号 参数名称         资源类别   缺省值         是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
 
项 目 组: 中间业务产品研发组
程 序 员:nierui
发布日期:2009年7月
修改日期:
******************************************************************************/
IRESULT SAgent_InsDzbpb(HXMLTREE lXmlhandle)
{
    AGENT_DZBPB    sdb_agent_dzbpb;
    
    char sErrmsg[256];
    char  sbuf[256];
    int   iParas;
    int iRet =-1;

    fpub_InitSoComp(lXmlhandle);
  
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    memset(&sdb_agent_dzbpb,0,sizeof(sdb_agent_dzbpb));
    
    /*对账日期*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_DZRQ,sbuf);
    memcpy(sdb_agent_dzbpb.dzrq,sbuf,sizeof(sdb_agent_dzbpb.dzrq)-1);

    /*平台日期*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_ZWRQ,sbuf);
    memcpy(sdb_agent_dzbpb.ptrq,sbuf,sizeof(sdb_agent_dzbpb.ptrq)-1);
    
    /*平台流水号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sbuf);
    sdb_agent_dzbpb.ptls = atoi(sbuf);
    
    /*主机日期*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_ZJRQ,sbuf);
    memcpy(sdb_agent_dzbpb.zjrq,sbuf,sizeof(sdb_agent_dzbpb.zjrq)-1);
    
    /*主机流水号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_ZJLS,sbuf);
    trim( sbuf );
    memcpy(sdb_agent_dzbpb.zjls,sbuf,sizeof(sdb_agent_dzbpb.zjls)-1);
    
    /*交易机构*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYJG,sbuf);
    trim( sbuf );
    memcpy(sdb_agent_dzbpb.jyjg,sbuf,sizeof(sdb_agent_dzbpb.jyjg)-1);
    
    /*交易柜员*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYGY,sbuf);
    memcpy(sdb_agent_dzbpb.jygy,sbuf,sizeof(sdb_agent_dzbpb.jygy)-1);
    trim( sdb_agent_dzbpb.jygy);
    
    /*交易币种*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYBZ,sbuf);
    memcpy(sdb_agent_dzbpb.jybz,sbuf,sizeof(sdb_agent_dzbpb.jybz)-1);
    trim( sdb_agent_dzbpb.jybz);
    
    /*业务编号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_YWBH,sbuf);
    memcpy(sdb_agent_dzbpb.ywbh,sbuf,sizeof(sdb_agent_dzbpb.ywbh)-1);
    trim( sdb_agent_dzbpb.ywbh);
    
    /*现转标志*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_XZBZ,sbuf);
    memcpy(sdb_agent_dzbpb.xzbz,sbuf,sizeof(sdb_agent_dzbpb.xzbz)-1);
    trim( sdb_agent_dzbpb.xzbz);
    
    /*借贷标识*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JDBZ,sbuf);
    memcpy(sdb_agent_dzbpb.jdbz,sbuf,sizeof(sdb_agent_dzbpb.jdbz)-1);
    trim( sdb_agent_dzbpb.jdbz);
    
    /*交易金额*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JYJE,sbuf);
    sdb_agent_dzbpb.jyje = atof(sbuf);
    
    /*平台交易金额*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_PTJYJE,sbuf);
    sdb_agent_dzbpb.ptjyje = atof(sbuf);
    
    /*借方帐号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JFZH,sbuf);
    memcpy(sdb_agent_dzbpb.jfzh,sbuf,sizeof(sdb_agent_dzbpb.jfzh)-1);
    trim( sdb_agent_dzbpb.jfzh);
    
    /*借方分帐号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_JFFZH,sbuf);
    memcpy(sdb_agent_dzbpb.jffzh,sbuf,sizeof(sdb_agent_dzbpb.jffzh)-1);
    trim( sdb_agent_dzbpb.jffzh);
    
    /*贷方帐号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_DFZH,sbuf);
    memcpy(sdb_agent_dzbpb.dfzh,sbuf,sizeof(sdb_agent_dzbpb.dfzh)-1);
    trim( sdb_agent_dzbpb.dfzh);
    
    /*贷方分帐号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_DFFZH,sbuf);
    memcpy(sdb_agent_dzbpb.dffzh,sbuf,sizeof(sdb_agent_dzbpb.dffzh)-1);
    trim( sdb_agent_dzbpb.dffzh);
    
    /*业务流水号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_YWLSH,sbuf);
    memcpy(sdb_agent_dzbpb.ywlsh,sbuf,sizeof(sdb_agent_dzbpb.ywlsh)-1);
    trim( sdb_agent_dzbpb.ywlsh);
    
    /*业务日期*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_YWRQ,sbuf);
    memcpy(sdb_agent_dzbpb.ywrq,sbuf,sizeof(sdb_agent_dzbpb.ywrq)-1);
    
    /*扩展字段1*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_EXTFLD1,sbuf);
    memcpy(sdb_agent_dzbpb.extfld1,sbuf,sizeof(sdb_agent_dzbpb.extfld1)-1);
    
    /*扩展字段2*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_EXTFLD2,sbuf);
    memcpy(sdb_agent_dzbpb.extfld2,sbuf,sizeof(sdb_agent_dzbpb.extfld2)-1);
    
    /*扩展字段3*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_AGENT_DZBPB_EXTFLD3,sbuf);
    memcpy(sdb_agent_dzbpb.extfld3,sbuf,sizeof(sdb_agent_dzbpb.extfld3)-1);

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    /*登记对账不平表*/
    iRet = DBInsert("app_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    DCICommit();

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}


/******************************************************************************
组件名称: SAGENT_CHECK
组件功能:缴费平台与各个记账系统对账
处理说明：处理的原则,以主机明细为准,有不平时登记对账不平表。同时修改当日流
          水表对账标志。
   
组件参数:
序号 参数名称         资源类别   缺省值         是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
 
项 目 组:
程 序 员:fuyw13006
发布日期:2016年11月
修改日期:2016年11月
******************************************************************************/
IRESULT SAGENT_CHECK(HXMLTREE lXmlhandle)
{
    AGENT_DZLSB sdb_agent_dzlsb;
    AGENT_DRLS sdb_agent_drls;
    AGENT_DZBPB sdb_agent_dzbpb;
    APP_DWCPXY  sdb_app_dwcpxy;
        
    char sRunCpdmSql[512];
    char sDelSsql[512];
    char sDzrq[8+1];
    char sYwbh[16+1];
    char sJyzt[1+1];  /* 交易状态 */
    char sJzxt[2+1];  /* 记账系统 */
    char sBuf[256];
    char  sSqlCond[100];
    char  sSqlDzrq[100];
    char  sAdjust[2];  /* 调整标志 */
    int   iParas,i;
    int   iCount = 0;
    int   iFlag = 0;  /* 0 对账平 1 对账不平 */
    int   iRet =-1;
    int   iFlag_msg=0; /*是否发生调账(如果有调账需要发送短信通知),0-没有 1-有*/
    CURSOR cur;
    CURSOR cur1;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
 
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*组件参数检查*/
    COMP_PARACOUNTCHK(4)
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"对账日期")
    trim(sBuf);
    memset(sDzrq,0,sizeof(sDzrq));
    memcpy(sDzrq,sBuf,sizeof(sDzrq)-1);
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"业务编号")
    trim(sBuf);
    memset(sYwbh,0,sizeof(sYwbh));
    strncpy(sYwbh, sBuf, sizeof(sYwbh)-1);

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"调整标志" );
    trim(sBuf);
    memset( sAdjust, 0, sizeof( sAdjust ) );
    strncpy(sAdjust, sBuf, sizeof(sAdjust)-1);

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"记账系统" );
    trim(sBuf);
    memset( sJzxt, 0, sizeof( sJzxt ) );
    strncpy(sJzxt, sBuf, sizeof(sJzxt)-1);
    
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    memset( sSqlCond, 0, sizeof( sSqlCond ) );
    trim( sYwbh );
    if( strlen(sYwbh) > 0 )
    {
        sprintf( sSqlCond," AND trim( ywbh )='%s'",sYwbh);
    }
    
    /*不同系统以不同日期为准*/
    memset( sSqlDzrq, 0, sizeof( sSqlDzrq ) );
    switch(atoi(sJzxt))
    {
    case 1:/*核心*/
        sprintf( sSqlDzrq," ptrq='%s'",sDzrq);
        break;
    case 3:/*支付网关*/
        sprintf( sSqlDzrq," zjrq='%s'",sDzrq);
        break;
    case 5: /*电子账户*/
    sprintf( sSqlDzrq," ptrq='%s'",sDzrq);
    break;
    case 2:/*信贷中心*/
    case 4:/*第三方*/
    default:
        LOG(LM_STD,Fmtmsg("处理失败:对账系统错误[%s]",sJzxt ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sDelSsql, 0, sizeof( sDelSsql ) );
    sprintf(sDelSsql, "delete from AGENT_DZBPB where dzrq='%s' and EXTFLD2='%s' %s",sDzrq,sJzxt,sSqlCond);
    LOG(LM_STD,Fmtmsg("删除对账不平表[%s]",sDelSsql ),"INFO")

    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败[%s]",sDelSsql ),"ERROR")
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 初始化对账状态为0 未对账 added by yangdong 20090807 */
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='0' WHERE %s %s AND EXTFLD2='%s'AND ZJDZBZ<>9", sSqlDzrq, sSqlCond ,sJzxt);
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败[%s]",sDelSsql ),"ERROR")
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end of add */

    /*add by zhandongdong 20171012 更新当日流水表,将状态为'2'的按照电子账户对账文件为准进行更新*/
    if(atoi(sJzxt)==5)
    {
        /*电子帐户送过来的对账文件里面只包含有处理成功的记录*/
        /*如果对账文件包含处理中的记录的,更新为成功  AND jyzt='0'*/   
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='0' , zjdzbz='1'\
        WHERE %s %s  AND ZJDZBZ<>9 AND jyzt='2' AND extfld2='05' AND trim(zjlsh) IN\
        (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s AND extfld2='05' )",sSqlDzrq, sSqlCond, sSqlDzrq);
    
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        { 
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*如果对账文件不包含处理中的记录的,更新为失败*/ 
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1' , zjdzbz='1'\
        WHERE %s %s  AND ZJDZBZ<>9 AND jyzt='2' AND extfld2='05' AND trim(zjlsh) NOT IN\
        (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s AND extfld2='05')",sSqlDzrq, sSqlCond, sSqlDzrq);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        { 
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        /*更新缴费详情表,20-处理中的更新为(流水表-0 21-已缴) (流水表-1 90-初始)*/
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_jfxq set zt='90' where jfrq='%s' and jfls in\
        (select char(ptls) from agent_drls where ptrq='%s' and jyzt='1' and extfld2='05' )",sDzrq,sDzrq);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        { 
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_jfxq set zt='21' where jfrq='%s' and jfls in\
        (select char(ptls) from agent_drls where ptrq='%s' and jyzt='0' and extfld2='05' )",sDzrq,sDzrq);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sSql1),"INFO");
        iRet = DCIExecuteDirect( sSql1 ); 
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /*end by zhandongdong */
        
    /*主机有,平台无的记录--B*/
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    sprintf(sRunCpdmSql, "SELECT * FROM agent_dzlsb WHERE %s AND jyzt='0'  %s AND \
        trim(zjls) NOT IN (SELECT DISTINCT trim(zjlsh) FROM agent_drls WHERE %s %s AND jyzt='0')\
        AND EXTFLD2='%s'AND ZJDZBZ<>9",sSqlDzrq,sSqlCond,sSqlDzrq,sSqlCond,sJzxt);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"INFO");
    /*取主机有,平台无的流水*/
    if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
    while( ( iRet = DBFetch(cur, SD_AGENT_DZLSB, NUMELE(SD_AGENT_DZLSB), &sdb_agent_dzlsb, sErrmsg ) ) > 0 )
    {
        iFlag ++;
        /*登记不平流水表*/
        memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
        memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
        memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_dzlsb.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
        sdb_agent_dzbpb.ptls = sdb_agent_dzlsb.ptls;
        trim( sdb_agent_dzlsb.zjrq);
        memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_dzlsb.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
        trim( sdb_agent_dzlsb.zjls);
        memcpy(sdb_agent_dzbpb.zjls,sdb_agent_dzlsb.zjls,sizeof(sdb_agent_dzbpb.zjls)-1);
        trim( sdb_agent_dzlsb.jyjg);
        memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_dzlsb.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
        trim( sdb_agent_dzlsb.jygy);
        memcpy(sdb_agent_dzbpb.jygy,sdb_agent_dzlsb.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
        trim( sdb_agent_dzlsb.jybz);
        memcpy(sdb_agent_dzbpb.jybz,sdb_agent_dzlsb.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
        trim( sdb_agent_dzlsb.ywbh);
        memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_dzlsb.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
        trim( sdb_agent_dzlsb.xzbz);
        memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_dzlsb.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
        trim( sdb_agent_dzlsb.jdbz);
        memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_dzlsb.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
        sdb_agent_dzbpb.jyje=sdb_agent_dzlsb.jyje;
        sdb_agent_dzbpb.ptjyje=0.00;
        trim( sdb_agent_dzlsb.jfzh);
        memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_dzlsb.jfzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
        trim( sdb_agent_dzlsb.jffzh);
        memcpy(sdb_agent_dzbpb.jffzh,sdb_agent_dzlsb.jffzh,sizeof(sdb_agent_dzbpb.jffzh)-1);
        trim( sdb_agent_dzlsb.dfzh);
        memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_dzlsb.dfzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
        trim( sdb_agent_dzlsb.dffzh);
        memcpy(sdb_agent_dzbpb.dffzh,sdb_agent_dzlsb.dffzh,sizeof(sdb_agent_dzbpb.dffzh)-1);
        memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* 流水类型 1主机对账 */
        memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* 处理状态 0未处理 */
        memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_dzlsb.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
        memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_dzlsb.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
        memcpy(sdb_agent_dzbpb.extfld3,"1",1);
        memcpy(sdb_agent_dzbpb.dzbz,"3",1);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
           Fmtmsg("对账不平,主机多：主机日期[%s] 主机流水[%s] 业务日期[%s] 平台流水[%d]",\
           sDzrq, sdb_agent_dzbpb.zjls, sDzrq, sdb_agent_dzbpb.ptls),"INFO");
        /*登记对账不平表*/
        iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }

        iCount ++;
    }
    DCIFreeCursor(cur);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机有平台无笔数[%d]", iCount ),"INFO");
    iCount = 0;
    /* 主机有,平台无记录 --E*/
    
    /**mod by zhandongdong  电子账户对账以中间业务为准**/
    if(atoi(sJzxt)==5)
    {
        /* 电子账户无,平台有记录 --B*/
        memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
        sprintf(sRunCpdmSql, "SELECT * FROM agent_drls WHERE %s %s AND jyzt='0'\
             AND ZJDZBZ<>9 AND trim(zjlsh) NOT IN\
            (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s %s AND jyzt='0' )\
            AND extfld2='%s'",
            sSqlDzrq, sSqlCond, sSqlDzrq,sSqlCond, sJzxt);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
        if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
        while( ( iRet = DBFetch(cur, SD_AGENT_DRLS, NUMELE(SD_AGENT_DRLS), &sdb_agent_drls, sErrmsg ) ) > 0 )
        {
            /*add by 根据单位编号获取单位收款内部账号*/
            memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
            memset(&sdb_app_dwcpxy, 0, sizeof(sdb_app_dwcpxy));
            sprintf(sRunCpdmSql, "SELECT * FROM app_dwcpxy WHERE ywbh='%s'",sYwbh);
            
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
            if ((cur1 = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            if (DCIExecute(cur1) == -1)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIFreeCursor(cur1);
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            if(DBFetch(cur1, SD_APP_DWCPXY, NUMELE(SD_APP_DWCPXY), &sdb_app_dwcpxy, sErrmsg ) ==0)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                DCIRollback();
                DCIFreeCursor(cur1);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sdb_app_dwcpxy.nbhzh),"DEBUG");
            
            iFlag ++;
            /*登记不平流水表*/
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
                Fmtmsg("对账不平，平台多：业务日期=[%s],平台流水=[%d]",\
                sdb_agent_drls.ywrq,sdb_agent_drls.ptls),"INFO");
            memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
    
            memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
            memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_drls.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
            sdb_agent_dzbpb.ptls = sdb_agent_drls.ptls;
            memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_drls.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
            memcpy(sdb_agent_dzbpb.zjls,sdb_agent_drls.zjlsh,sizeof(sdb_agent_dzbpb.zjls)-1);
            memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_drls.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
            memcpy(sdb_agent_dzbpb.jygy,sdb_agent_drls.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
            memcpy(sdb_agent_dzbpb.jybz,sdb_agent_drls.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
            memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_drls.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
            memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_drls.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
            memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_drls.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
            sdb_agent_dzbpb.ptjyje=sdb_agent_drls.jyje;
            sdb_agent_dzbpb.jyje=0.00;
            if( sdb_agent_drls.jdbz[0]='D' )
            {
                memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
                memcpy(sdb_agent_dzbpb.jfzh,sdb_app_dwcpxy.nbhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
            }
            else
            {
                memcpy(sdb_agent_dzbpb.jfzh,sdb_app_dwcpxy.nbhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
                memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.dfzh)-1);
            }
            memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* 流水类型 1主机对账 */
            memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* 处理状态 0未处理 */
            memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_drls.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
            memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_drls.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
            memcpy(sdb_agent_dzbpb.extfld3,"1",1);
            memcpy(sdb_agent_dzbpb.dzbz,"2",1);
            
            /*不自动调账登才记对账不平表*/ 
            if( sAdjust[0] == '1' ) 
            {
                iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                    return COMPRET_FAIL;
                }
            }
            else if( sAdjust[0] == '0' )  /* 主机无 ，平台有 ，调整平台状态为 失败 */
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1', zjdzbz='1' \
                    WHERE %s AND ptls =%d  AND ZJDZBZ<>9",sSqlDzrq, sdb_agent_drls.ptls);
                iRet = DCIExecuteDirect( sSql1 ); 
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
    
                iFlag--;//调整后，对账结果与此无关
    
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机无平台有 ptrq[%s] ptls[%d] 调整为失败 ", \
                                         sDzrq, sdb_agent_drls.ptls ),"INFO");
            }
            iCount ++;
        }
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机无平台有笔数[%d]", iCount ),"INFO");
        /*电子账户无,平台有记录 --E*/     
    }
    else
    {
        /* 主机无,平台有记录 --B*/
        memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
        sprintf(sRunCpdmSql, "SELECT * FROM agent_drls WHERE %s %s AND jyzt='0'\
             AND ZJDZBZ<>9 AND trim(zjlsh) NOT IN\
            (SELECT DISTINCT trim(zjls) FROM agent_dzlsb WHERE %s AND jyzt='0' )\
            AND extfld2='%s'",
            sSqlDzrq, sSqlCond, sSqlDzrq,sJzxt);
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG, Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"DEBUG");
        if ((cur = DCIDeclareCursor( sRunCpdmSql, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        memset(&sdb_agent_dzlsb, 0, sizeof(sdb_agent_dzlsb));
        while( ( iRet = DBFetch(cur, SD_AGENT_DRLS, NUMELE(SD_AGENT_DRLS), &sdb_agent_drls, sErrmsg ) ) > 0 )
        {
            iFlag ++;
            /*登记不平流水表*/
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
                Fmtmsg("对账不平，平台多：业务日期=[%s],平台流水=[%d]",\
                sdb_agent_drls.ywrq,sdb_agent_drls.ptls),"INFO");
            memset(&sdb_agent_dzbpb, 0, sizeof(sdb_agent_dzbpb));
    
            memcpy(sdb_agent_dzbpb.dzrq,sDzrq,sizeof(sdb_agent_dzbpb.dzrq)-1);
            memcpy(sdb_agent_dzbpb.ptrq,sdb_agent_drls.ptrq,sizeof(sdb_agent_dzbpb.ptrq)-1);
            sdb_agent_dzbpb.ptls = sdb_agent_drls.ptls;
            memcpy(sdb_agent_dzbpb.zjrq,sdb_agent_drls.zjrq,sizeof(sdb_agent_dzbpb.zjrq)-1);
            memcpy(sdb_agent_dzbpb.zjls,sdb_agent_drls.zjlsh,sizeof(sdb_agent_dzbpb.zjls)-1);
            memcpy(sdb_agent_dzbpb.jyjg,sdb_agent_drls.jyjg,sizeof(sdb_agent_dzbpb.jyjg)-1);
            memcpy(sdb_agent_dzbpb.jygy,sdb_agent_drls.jygy,sizeof(sdb_agent_dzbpb.jygy)-1);
            memcpy(sdb_agent_dzbpb.jybz,sdb_agent_drls.jybz,sizeof(sdb_agent_dzbpb.jybz)-1);
            memcpy(sdb_agent_dzbpb.ywbh,sdb_agent_drls.ywbh,sizeof(sdb_agent_dzbpb.ywbh)-1);
            memcpy(sdb_agent_dzbpb.xzbz,sdb_agent_drls.xzbz,sizeof(sdb_agent_dzbpb.xzbz)-1);
            memcpy(sdb_agent_dzbpb.jdbz,sdb_agent_drls.jdbz,sizeof(sdb_agent_dzbpb.jdbz)-1);
            sdb_agent_dzbpb.ptjyje=sdb_agent_drls.jyje;
            sdb_agent_dzbpb.jyje=0.00;
            if( sdb_agent_drls.jdbz[0]='D' )
            {
                memcpy(sdb_agent_dzbpb.jfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
            }
            else
            {
                memcpy(sdb_agent_dzbpb.dfzh,sdb_agent_drls.yhzh,sizeof(sdb_agent_dzbpb.jfzh)-1);
            }
            memcpy(sdb_agent_dzbpb.lslx, "1", 1); /* 流水类型 1主机对账 */
            memcpy(sdb_agent_dzbpb.clzt, "0", 1); /* 处理状态 0未处理 */
            memcpy(sdb_agent_dzbpb.extfld1,sdb_agent_drls.extfld1,sizeof(sdb_agent_dzbpb.extfld1)-1);
            memcpy(sdb_agent_dzbpb.extfld2,sdb_agent_drls.extfld2,sizeof(sdb_agent_dzbpb.extfld2)-1);
            memcpy(sdb_agent_dzbpb.extfld3,"1",1);
            memcpy(sdb_agent_dzbpb.dzbz,"2",1);
            
            /*不自动调账登才记对账不平表*/ 
            if( sAdjust[0] == '1' ) 
            {
                iRet = DBInsert("agent_dzbpb", SD_AGENT_DZBPB, NUMELE(SD_AGENT_DZBPB), &sdb_agent_dzbpb, sErrmsg);
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                    return COMPRET_FAIL;
                }
            }
            else if( sAdjust[0] == '0' )  /* 主机无 ，平台有 ，调整平台流水状态为 失败 */
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                snprintf( sSql1, sizeof( sSql1 ),"UPDATE agent_drls SET jyzt='1', zjdzbz='1' \
                    WHERE %s AND ptls =%d  AND ZJDZBZ<>9",sSqlDzrq, sdb_agent_drls.ptls);
                iRet = DCIExecuteDirect( sSql1 ); 
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                    DCIRollback();
                    DCIFreeCursor(cur);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
    
                iFlag--;//调整后，对账结果与此无关
                iFlag_msg=1; /*发生调账*/
    
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机无平台有 ptrq[%s] ptls[%d] 调整为失败 ", \
                                         sDzrq, sdb_agent_drls.ptls ),"INFO");
            }
            iCount ++;
        }
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("主机无平台有笔数[%d]", iCount ),"INFO");
        /*主机无,平台有记录 --E*/      
    }
    
    memset( sDelSsql, 0x00, sizeof( sDelSsql ) );
    sprintf( sDelSsql,  "UPDATE agent_drls SET zjdzbz='1' \
        WHERE %s %s AND zjdzbz = '0' AND extfld2='%s' AND ZJDZBZ<>9", sSqlDzrq, sSqlCond, sJzxt );
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sDelSsql),"INFO");
    iRet = DCIExecuteDirect( sDelSsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    /* end */
    
    /*发送调账通知短信*/
    /*if(1) 测试用一下*/
    if(iFlag_msg==1) 
    {
        memset(sBuf,0x00,sizeof(sBuf));
        COMP_SOFTSETXML("/agent/dz_msg/dwbh", sYwbh)
        strncpy(sBuf,sYwbh,3);
        COMP_SOFTSETXML("/agent/dz_msg/cpdm", sBuf)
        COMP_SOFTSETXML("/agent/dz_msg/jzxt",sJzxt)
        if(fpub_CallFlow(lXmlhandle,"subflow_jfpt_700675_message")!=MID_SYS_SUCC )
        {
            LOG(LM_STD, Fmtmsg("调用短信提醒子流程失败"), fpub_GetCompname(lXmlhandle))
        }
    }
    
    if( iFlag == 0 )
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "0" )  /* 主机对账状态 0 平 */
    }
    else
    {
        COMP_HARDSETXML( XMLNM_AGENT_RESP_ZJDZZT, "1" )  /* 主机对账状态 1 不平 */
    }
    
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}
