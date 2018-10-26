/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.0)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_CHECK.c
文件描述:BATCH校验函数组件集合
项 目 组:中间业务平台AGENT2.1产品组
程 序 员:chensy YangDong
发布日期:2011年8月1日

程 序 员:YangDong
修改日期:20141018
修改说明:DCI改造
*********************************************************************/
#include "gaps_head.h"
/*#include "DCI.h"*/
#include "batch_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"

#define SOCOMPVERSION "V2.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_CHECK.so</soname>\
        <sosrcname>BAT_CHECK.c</sosrcname>\
        <sonote>BATCH校验函数组件集合</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"Chensy YangDong\" filesize=\"1128297\">HS-AgentV2.1整理</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1128297\">DCI改造</rec>\
        </version>\
        </root>";
    printf("\n================动态组件基本信息================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" 取详细信息失败...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" 请查看详细信息...\n");
    
    return 0;
}
int iLrzbs,iLpwjzbs,iHZbs;
int iAuditingSn;
double dLrzje=0.00,dLpwjzje=0.00,fHZje=0.00;
char sZbs[16];
char sPtpch[8+1],sPkrq[8+1],sYwbm[50+1];
char sDsql[512]; 
char sSql1[1024]; 
char sLname[64+1],sLen[6+1];
char sCpdm[16+1];
char sShbs[50+1]; 
char sErrmsg[512]; 

/************************************************************************
动态组件函数定义
组件函数名称:BATCH_CHECKALLNUM
组件名称:BATCH_CHECKALLNUM
组件功能: 批量业务校验总笔数总金额
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
  
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT BATCH_CHECKALLNUM(HXMLTREE lXmlhandle)
{
    char sBuf[128];
    char sMsg[60];
    /*int iResult = -1;*/
    char sFileFmt[2+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", "BATCH_CHECKALLNUM"),"DEBUG");

    memset(sBuf,0,sizeof(sBuf));
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf)
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    if(strlen(sPtpch)<=0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        LOG(LM_DEBUG,Fmtmsg("平台批次号不能为空"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf)
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbm,0,sizeof(sYwbm));
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf)
    pstrcopy(sYwbm,sBuf,sizeof(sYwbm));
    
    /* 取外部文件登记总笔数 总金额*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS,sBuf)
    iLrzbs=atoi(sBuf);
    if( iLrzbs > 0 )
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZJE,sBuf)
        dLrzje=atof(sBuf);
    }
    
    /* 取来盘文件汇总记录里的总笔数 总金额*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_HZ_ZBS,sBuf)
    iLpwjzbs=atoi(sBuf);
    if( iLpwjzbs > 0 )
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_HZ_ZJE,sBuf)
        dLpwjzje=atof(sBuf);
    }
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_MX_ZBS,sBuf)
    iHZbs=atoi(sBuf);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_MX_ZJE,sBuf)
    fHZje=atof(sBuf);
                            
    if( iLrzbs > 0 )
    {
        /* 总笔数不符 */
        if( abs(iHZbs - iLrzbs) > 0 )        
        {
            LOG(LM_STD,Fmtmsg("BATCH: 录入总笔数[%d]与明细[%d]不符",\
                               iLrzbs,iHZbs),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZBS_MXZBS,\
                        Fmtmsg(MSG_BATCH_LRZBS_MXZBS,iLrzbs,iHZbs));        
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -3;
        }
        /* 总金额不符 */
        if( fabs(fHZje - dLrzje) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 录入总金额[%f]与明细总金额[%f]不符",\
                               dLrzje,fHZje),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_LRZJE_MXZJE,\
                             Fmtmsg(MSG_BATCH_LRZJE_MXZJE,dLrzje,fHZje));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -4;
        }
    }

    memset(sBuf,0,sizeof(sBuf));
    memset(sFileFmt,0,sizeof(sFileFmt));
    COMP_SOFTGETXML(XMLNM_BATCH_WJLX_FILEFMT,sBuf)
    pstrcopy(sFileFmt,sBuf,sizeof(sFileFmt));
    /* 文件类型 02 汇总＋单明细 03 单明细＋汇总 04 汇总＋单明细＋汇总 */
    if( memcmp( sFileFmt,"01", 2 ) != 0 )
    /* 20111108 如果非单明细格式，调用总金额总笔数校验时,必须进行判断
    if( iLpwjzbs > 0 )
    */
    {
        if( abs(iHZbs - iLpwjzbs) > 0 )        
        {
            LOG(LM_STD,Fmtmsg("BATCH: 来盘文件汇总信息总笔数[%d]\
                与明细总笔数[%d]不符",iLpwjzbs,iHZbs),"INFO");
            /* modified by yangdong 20121122 总金额总比数失败信息合并
            fpub_SetMsg(lXmlhandle,MID_BATCH_WJZBS_MXZBS,\
                         Fmtmsg(MSG_BATCH_WJZBS_MXZBS,iLpwjzbs,iHZbs));        
            */
            fpub_SetMsg(lXmlhandle,MID_BATCH_WJZBS_MXZBS, Fmtmsg(MSG_BATCH_WJZBS_MXZBS,iLpwjzbs,iHZbs) );        
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -3;
        }
        /* 总金额不符 */
        if( fabs(fHZje - dLpwjzje) > 0.001 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 来盘文件汇总信息总金额[%.2f]与明细总金额[%.2f]不符",\
                dLpwjzje,fHZje),"INFO");
            fpub_SetMsg(lXmlhandle,MID_BATCH_WJZJE_MXZJE,Fmtmsg(MSG_BATCH_WJZJE_MXZJE,dLpwjzje,fHZje));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -4;
        }
    }
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", "BATCH_CHECKALLNUM"), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: BATCH_CHECKLEN
组件名称: BATCH_CHECKLEN
组件功能: 批量业务校验列内容长度
组件参数:
序号 参数类型    参数名称     资源类别         缺省值    可空    参数说明        
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT BATCH_CHECKLEN(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int iResult = -1;
    int iRet=-1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");
        
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDISN,sBuf)/*取函数序号*/
    iAuditingSn=atoi(sBuf);
    
    memset(sShbs,0,sizeof(sShbs));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDIID,sBuf)/*取审核标识*/
    trim(sBuf);
    pstrcopy(sShbs,sBuf,sizeof(sShbs));

    memset(sPtpch,0,sizeof(sPtpch));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf)/*取批次号*/
    trim(sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
    memset(sPkrq,0,sizeof(sPkrq));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ ,sBuf)/*取批扣日期*/
    trim(sBuf);
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    /* 参数一 取列标识 */
    memset( sLname, 0x00, sizeof( sLname ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT funcpara FROM BATCH_AUDITINGCFG\
        WHERE auditingid='%s' AND auditingsn='%d' AND funcparasn=1 ", sShbs, iAuditingSn );
    iRet = DBSelectToVarChar(sErrmsg, sLname, sSql1);
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_SHGZPZ,MSG_BATCH_SEL_SHGZPZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;

    }
    trim(sLname);

    /* 参数二 审核长度 */
    memset( sLen, 0x00,sizeof( sLen ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT funcpara FROM BATCH_AUDITINGCFG\
        WHERE auditingid='%s' AND auditingsn='%d' AND funcparasn=2 ", sShbs, iAuditingSn );
    iRet = DBSelectToVarChar(sErrmsg, sLen, sSql1);
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_SHGZPZ,MSG_BATCH_SEL_SHGZPZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    trim(sLen);

    DCIBegin();
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf);
    pstrcopy(sYwbm,sBuf,sizeof(sYwbm));
    memset(sDsql,0,sizeof(sDsql));
    snprintf(sDsql, sizeof( sDsql ), "UPDATE %s \
        SET shzt='1', clzt='1', cgbz='2', xym='3', xyxx='长度不符'\
        WHERE pkrq='%s' AND ptpch='%s' AND LENGTH( trim( %s ) ) NOT IN ( %s )",\
        sYwbm,sPkrq,sPtpch,sLname,sLen);

    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("SQLEERR,sql[%s]sqlerr[%s]ret[%d]",sDsql, DCILastError(), iRet ),"ERROR");
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    LOG(LM_STD, Fmtmsg("长度不符记录[%d]笔,sDsql[%s] iRet[%d]\n", iResult,sDsql, iRet), "DEBUG")
    
    memset(sDsql,0,sizeof(sDsql));
    snprintf(sDsql, sizeof( sDsql ), "UPDATE %s SET shzt='0' \
        WHERE pkrq='%s' AND ptpch='%s' AND LENGTH( trim( %s) ) in (%s)",\
        sYwbm,sPkrq,sPtpch,sLname,sLen);
    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("SQLEERR,sql[%s]sqlerr[%s]ret[%d]",sDsql, DCILastError(), iRet ),"ERROR");
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    LOG(LM_DEBUG, Fmtmsg("长度相符记录[%d]笔[%s] iRet [%d]\n", iResult, sDsql, iRet ), "DEBUG")
    
    /* add by yr 20120919 */
    /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: BATCH_CHECKSIGN
组件名称: BATCH_CHECKSIGN
组件功能: 批量业务校验列签约关系
组件参数:
序号 参数类型    参数名称    资源类别         缺省值    可空    参数说明        
    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT BATCH_CHECKSIGN(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    /*int iResult = -1;*/
    int  iRet = -1;
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");
        
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDISN,sBuf)/*取函数序号*/
    iAuditingSn=atoi(sBuf);
    
    memset(sShbs,0,sizeof(sShbs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_AUDITING_AUDIID,sBuf)/*取审核标识*/
    trim(sBuf);
    pstrcopy(sShbs,sBuf,sizeof(sShbs));
    
    memset(sPtpch,0,sizeof(sPtpch));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf)/*取批次号*/
    trim(sBuf);
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
    memset(sPkrq,0,sizeof(sPkrq));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ ,sBuf)/*取批扣日期*/
    trim(sBuf);
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));

    /* 参数一 用户号字段名 */
    memset( sLname, 0x00, sizeof( sLname ) );

    snprintf( sSql1, sizeof( sSql1 ), "SELECT funcpara FROM BATCH_AUDITINGCFG\
         WHERE auditingid='%s' AND auditingsn='%d' AND funcparasn=1 ", sShbs, iAuditingSn );
    iRet = DBSelectToVarChar(sErrmsg, sLname, sSql1);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_SHGZPZ,MSG_BATCH_SEL_SHGZPZ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    trim(sLname);
    if( iRet == 0 || ( strlen( sLname ) < 1 ) )
        strcpy( sLname,"yhh1" );  /*  默认用户号存放在yhh1字段中 */
   
    /*  取业务表名 */
    memset(sBuf,0,sizeof(sBuf));
    memset( sYwbm, 0x00, sizeof( sYwbm ) );
    COMP_SOFTGETXML(XMLNM_BATCH_WWMAPINFO_YWBM,sBuf);
    pstrcopy(sYwbm,sBuf,sizeof(sYwbm));
    /*  取产品代码 */
    memset(sBuf,0,sizeof(sBuf));
    memset(sCpdm,0,sizeof(sCpdm));
    COMP_SOFTGETXML(XMLNM_APP_DWCPXY_CPDM,sBuf);
    pstrcopy(sCpdm,sBuf,sizeof(sCpdm));

    DCIBegin();
    memset(sDsql,0,sizeof(sDsql));
    /* modified by yangdong 20120827 增加trim  */
    snprintf(sDsql, sizeof( sDsql ), "UPDATE %s SET shzt='1', clzt='1',\
        cgbz='2', xym='NOSIGN', xyxx='签约关系不存在或已失效' \
        WHERE pkrq='%s' AND ptpch='%s' AND trim(%s) NOT IN \
        ( SELECT yhh1 FROM app_khcpqy WHERE cpdm='%s' AND qyzt='0' )",\
        sYwbm, sPkrq, sPtpch, sLname, sCpdm );
    LOG(LM_STD,Fmtmsg("执行SQL[%s]", sDsql ),"INFO")             
/* modified by yangdong 20130809 sql_DynExec 不返回sqlcode
    if( sql_DynExec(sDsql,&iResult) !=0 && !SQLNOTFOUND  )
*/
    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0  )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    memset(sDsql,0,sizeof(sDsql));

    /* modified by yangdong 20120827 增加trim  */
    snprintf( sDsql, sizeof( sDsql ), "UPDATE %s SET shzt='0' \
        WHERE pkrq='%s' AND ptpch='%s' AND trim(%s) IN \
        ( SELECT yhh1 FROM app_khcpqy WHERE cpdm='%s' AND qyzt='0' )",\
        sYwbm, sPkrq, sPtpch, sLname, sCpdm );
    LOG(LM_STD,Fmtmsg("执行SQL[%s]", sDsql ),"INFO")       
/* modified by yangdong 20130809 sql_DynExec 不返回sqlcode
    if( sql_DynExec(sDsql,&iResult) !=0  && !SQLNOTFOUND )
*/
    iRet = DCIExecuteDirect( sDsql );
    if( iRet < 0  )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        /*sql_RollbackTrans();*/
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_SHZT,MSG_BATCH_UPD_SHZT);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    
    /* add by yr 20120919 */
    /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
