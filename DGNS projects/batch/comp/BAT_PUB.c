/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_PUB.c
文件描述: 批量处理公共类组件集
程 序 员:chensy YangDong
发布日期:2001-08-01

程 序 员:YangDong
修改日期:20141018
修改说明:DCI改造
*********************************************************************/
#include "gaps_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"
#include "batch_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_PUB.so</soname>\
        <sosrcname>BAT_PUB.c</sosrcname>\
        <sonote>BATCH通用组件集合</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"Chensy YangDong\" filesize=\"1438053\">HS-AgentV2.1整理</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2012-7-1 15:08\" programer=\"YangDong\" filesize=\"1438053\">升级</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1438053\">DCI改造</rec>\
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
batchlong  lvr;

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_REGFILE
组件名称:BATCH_REGFILE
组件功能: 批量业务外部文件登记
组件参数:
 序号 参数类型  参数名称   资源类别     缺省值  可空  参数说明    
 1   1-输入   录入方式     416-解析字符串       Y   1：主动录入，2：被动录入 
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_REGFILE(HXMLTREE lXmlhandle)
{
    int  iParas;
    int  iRet=-1;
    char sErrmsg[512];
    char sSql1[1024];
    char sFlowId[51];
    char sBuf[255];
    char sJyfs[1+1];
    char sTjsj[8+1];
    char sTjrq[8+1];
    int  i = 0;
    int iPcCount=0;
    CURSOR cur;
    /*int  j = 0;*/
    BATCH_WBWJDJ sdb_batch_wbwjdj;

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    /*指定数据提交时间只能是夜间批量*/
    memset(sTjrq, 0x00, sizeof(sTjrq));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_DATE, sTjrq)
    memset(sTjsj, 0x00, sizeof(sTjsj));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_TIME, sTjsj)
    if (sTjrq[0] != '\0' || sTjsj[0] != '\0')
    {
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sJyfs, 0x00, sizeof(sJyfs));
        COMP_SOFTGETXML("/app/cpxx/jyfs", sBuf)
        if ( sBuf[0] == '\0')
        {
            sBuf[0] = '2';/*2-批量*/
        }
        sJyfs[0] = sBuf[0];
        LOG(LM_STD,Fmtmsg("提交日期时间[%s,%s],交易方式[%s]",
            sTjrq, sTjsj, sJyfs),fpub_GetCompname(lXmlhandle))
        if ( sJyfs[0] != '4'  && sJyfs[0] != '7')
        {/*夜间批量*/
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,MSG_BATCH_SJTJ_NIGHT,"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SJTJ_NIGHT,MSG_BATCH_SJTJ_NIGHT );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    

    memset(&sdb_batch_wbwjdj,0,sizeof(sdb_batch_wbwjdj));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "%s", "INSERT INTO batch_wbwjdj (\
        djrq, djlsh, djsj, ywbh, djjg, djgy, shpch, pkrq, ptpch, lpwjlj, lpwjm, zbs,\
        zje, threadno, taskmode, pczt, shzt, note, extfld1, extfld2, extfld3)\
        VALUES( :v1, :v2, :v3, :v4, :v5, :v6, :v7, :V8, :v9, :v10, :v11, \
        :v12, :v13, :v14, :v15, :v16, :v17, :V18, :v19, :v20, :v21 ) ");

    if ( (cur = DCIDeclareCursor( sSql1, 0)) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("数据库操作失败[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    i = 0;
    if (DCIBindPara(cur, 0, sdb_batch_wbwjdj.djrq,  sizeof( sdb_batch_wbwjdj.djrq ), DCIT_VARCHAR) != 0)
        i++;
    if (DCIBindPara(cur, 1, &sdb_batch_wbwjdj.djlsh,  sizeof( sdb_batch_wbwjdj.djlsh), DCIT_INTEGER ) != 0)
        i++;
    if (DCIBindPara(cur, 2, sdb_batch_wbwjdj.djsj,  sizeof( sdb_batch_wbwjdj.djsj), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 3, sdb_batch_wbwjdj.ywbh,  sizeof( sdb_batch_wbwjdj.ywbh), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 4, sdb_batch_wbwjdj.djjg,  sizeof( sdb_batch_wbwjdj.djjg), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 5, sdb_batch_wbwjdj.djgy,  sizeof( sdb_batch_wbwjdj.djgy), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 6, sdb_batch_wbwjdj.shpch,  sizeof( sdb_batch_wbwjdj.shpch), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 7, sdb_batch_wbwjdj.pkrq,  sizeof( sdb_batch_wbwjdj.pkrq), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 8, sdb_batch_wbwjdj.ptpch,  sizeof( sdb_batch_wbwjdj.ptpch), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 9, sdb_batch_wbwjdj.lpwjlj,  sizeof( sdb_batch_wbwjdj.lpwjlj), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 10, sdb_batch_wbwjdj.lpwjm,  sizeof( sdb_batch_wbwjdj.lpwjm), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 11, sdb_batch_wbwjdj.zbs,  sizeof( sdb_batch_wbwjdj.zbs), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 12, &sdb_batch_wbwjdj.zje,  sizeof( sdb_batch_wbwjdj.zje), DCIT_DOUBLE ) != 0)
        i++;
    if (DCIBindPara(cur, 13, &sdb_batch_wbwjdj.threadno,  sizeof( sdb_batch_wbwjdj.threadno), DCIT_INTEGER ) != 0)
        i++;
    if (DCIBindPara(cur, 14, sdb_batch_wbwjdj.taskmode,  sizeof( sdb_batch_wbwjdj.taskmode), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 15, sdb_batch_wbwjdj.pczt,  sizeof( sdb_batch_wbwjdj.pczt), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 16, sdb_batch_wbwjdj.shzt,  sizeof( sdb_batch_wbwjdj.shzt), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 17, sdb_batch_wbwjdj.note,  sizeof( sdb_batch_wbwjdj.note), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 18, sdb_batch_wbwjdj.extfld1,  sizeof( sdb_batch_wbwjdj.extfld1), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 19, sdb_batch_wbwjdj.extfld2,  sizeof( sdb_batch_wbwjdj.extfld2), DCIT_VARCHAR ) != 0)
        i++;
    if (DCIBindPara(cur, 20, sdb_batch_wbwjdj.extfld3,  sizeof( sdb_batch_wbwjdj.extfld3), DCIT_VARCHAR ) != 0)
        i++;

    if( i > 0 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("数据库操作失败[%s]",DCILastError()),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*帐务日期(产品日期)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    if( 0 == sBuf[0] ) 
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_DJRQ_NULL,MSG_BATCH_DJRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_wbwjdj.djrq,sBuf,sizeof(sdb_batch_wbwjdj.djrq));
    COMP_SOFTSETXML( XMLNM_BATCH_WBWJDJ_DJRQ, sdb_batch_wbwjdj.djrq );

    /* 来盘文件路径 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LOCALPATH,sBuf);
    pstrcopy(sdb_batch_wbwjdj.lpwjlj,sBuf,sizeof(sdb_batch_wbwjdj.lpwjlj));
    
    /* 来盘文件名 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LPWJM,sBuf);
    if( 0 == sBuf[0] )
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_LPWJM_NULL,MSG_BATCH_LPWJM_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    } 
    pstrcopy(sdb_batch_wbwjdj.lpwjm,sBuf,sizeof(sdb_batch_wbwjdj.lpwjm));

    LOG(LM_STD,Fmtmsg("BATCH: 来盘文件名[%s]",sdb_batch_wbwjdj.lpwjm),"INFO")

    /*任务模式*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_TASKMODE,sBuf);
    pstrcopy(sdb_batch_wbwjdj.shpch,sBuf,sizeof(sdb_batch_wbwjdj.shpch));
    /* 业务编号 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_wbwjdj.ywbh,sBuf,sizeof(sdb_batch_wbwjdj.ywbh));
    /* added by yangdong 20120422 增加商户批次号记录 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_SHPCH,sBuf);
    pstrcopy(sdb_batch_wbwjdj.shpch,sBuf,sizeof(sdb_batch_wbwjdj.shpch));
    if (sdb_batch_wbwjdj.shpch[0] != '\0')
    {/*商户批次号不为空时需堵重*/
        memset(sSql1, 0x00, sizeof(sSql1));
        snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_wbwjdj \
            WHERE ywbh ='%s' AND shpch='%s' AND pczt <> 'X' AND pczt <> 'C'",\
            sdb_batch_wbwjdj.ywbh, sdb_batch_wbwjdj.shpch );
        memset(sBuf,0,sizeof(sBuf));
        iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
        if( iRet < 0 )
        {
            DCIFreeCursor(cur);
            LOG(LM_STD,Fmtmsg("BATCH: sqlerr[%s] shpch[%s]",\
                        DCILastError(), sdb_batch_wbwjdj.shpch ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        iPcCount=atoi( sBuf );
        if( iPcCount > 0 )
        {
            DCIFreeCursor(cur);
            LOG(LM_STD,Fmtmsg("BATCH: count[%d] lpwjm[%s]",\
                        iPcCount, sdb_batch_wbwjdj.lpwjm ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_SHPCH,MSG_BATCH_SHPCH);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    /* 不允许同名文件出现，失败必须从tamc单步处理 */
    /* 允许已撤销任务同名 20120517 mod by yangdong */
    memset(sBuf,0,sizeof(sBuf));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_wbwjdj \
        WHERE ywbh ='%s' AND lpwjm='%s' AND pczt <> 'X' AND pczt <> 'C'",\
        sdb_batch_wbwjdj.ywbh, sdb_batch_wbwjdj.lpwjm );

    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
    if( iRet < 0 )
    {
        DCIFreeCursor(cur);
        LOG(LM_STD,Fmtmsg("BATCH: sqlerr[%s] lpwjm[%s]",\
                    DCILastError(), sdb_batch_wbwjdj.lpwjm ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iPcCount=atoi( sBuf );

    if( iPcCount > 0 )
    {
        DCIFreeCursor(cur);
        LOG(LM_STD,Fmtmsg("BATCH: count[%d] lpwjm[%s]",\
                    iPcCount, sdb_batch_wbwjdj.lpwjm ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SHPCH,MSG_BATCH_WJDJ_EXIST);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }             
    
    /* 审核标志 0：需要审核外部文件，1：不需要审核外部文件 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_SHBZ,sBuf);
    if( '0' == sBuf[0] ) 
    {
        sdb_batch_wbwjdj.shzt[0] = WBWJDJ_SHZT_NO;
        sdb_batch_wbwjdj.shzt[1] = 0;
    }
    else   /* 默认 1 ：不需要审核外部文件 */
    {
        sdb_batch_wbwjdj.shzt[0] = WBWJDJ_SHZT_YES;
        sdb_batch_wbwjdj.shzt[1] = 0;
    }
    
    /* 登记机构(默认主办机构) */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJJG,sBuf);
    if( 0 == sBuf[0] ) 
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG,sBuf);
        if( 0 == sBuf[0] ) 
        {/*cpxx表的主办机构也为空*/
            fpub_SetMsg(lXmlhandle,MID_BATCH_JYJGNULL,MSG_BATCH_JYJGNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    pstrcopy(sdb_batch_wbwjdj.djjg,sBuf,sizeof(sdb_batch_wbwjdj.djjg));
    
    /* 登记柜员(默认主办柜员) */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJGY,sBuf);
    if( 0 == sBuf[0] ) 
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY,sBuf);
    }
    pstrcopy(sdb_batch_wbwjdj.djgy,sBuf,sizeof(sdb_batch_wbwjdj.djgy));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS,sBuf);
    if (sBuf[0] == '\0')
        sBuf[0] = '0';
    pstrcopy(sdb_batch_wbwjdj.zbs,sBuf,sizeof(sdb_batch_wbwjdj.zbs));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZJE,sBuf);
    sdb_batch_wbwjdj.zje=atof(sBuf);

    /*综合前置流水号(产品流水号)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_DJLSH_NULL,MSG_BATCH_DJLSH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    COMP_SOFTSETXML( XMLNM_BATCH_WBWJDJ_DJLSH, sBuf);
    sdb_batch_wbwjdj.djlsh=atol(sBuf);
    
    /*系统时间*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_SYSTIME,sBuf);
    pstrcopy(sdb_batch_wbwjdj.djsj,sBuf,sizeof(sdb_batch_wbwjdj.djsj));
    
    /*平台批次号 - 登记时为空*/
    pstrcopy(sdb_batch_wbwjdj.ptpch," ",sizeof(sdb_batch_wbwjdj.ptpch));
    
    /*回盘文件名 - 登记时为空*/

    /*批次状态 - 登记时为就绪*/
    sdb_batch_wbwjdj.pczt[0] = WBWJDJ_ZT_READY;
    sdb_batch_wbwjdj.pczt[1] = 0;
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_TASKMODE,sBuf);
    if( '\0' == sBuf[0] )
    {
        /* 任务开始模式默认为自动 */
        sdb_batch_wbwjdj.taskmode[0] = '1';
    }
    else
    {
        sdb_batch_wbwjdj.taskmode[0] = sBuf[0];
    }
    
    sdb_batch_wbwjdj.threadno=1; /* 默认线程数为一 */
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_NOTE,sBuf);
    pstrcopy(sdb_batch_wbwjdj.note,sBuf,sizeof(sdb_batch_wbwjdj.note));
    
    /*扩展字段一 - */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD1,sBuf);
    pstrcopy(sdb_batch_wbwjdj.extfld1,sBuf,sizeof(sdb_batch_wbwjdj.extfld1));
    
    /*扩展字段二 - */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD2,sBuf);
    pstrcopy(sdb_batch_wbwjdj.extfld2,sBuf,sizeof(sdb_batch_wbwjdj.extfld2));

    /*扩展字段三 - */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_EXTFLD3,sBuf);
    pstrcopy(sdb_batch_wbwjdj.extfld3,sBuf,sizeof(sdb_batch_wbwjdj.extfld3));

    /*sql_BeginTrans(); 用DCIBegin代替 2015-1-7 by chenxm*/
    DCIBegin();

    iRet = DCIExecute(cur);
    if ( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("登记失败,sqlerr=[%s]",DCILastError()),"ERROR");
        DCIRollback();
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_INS_WBWJDJ,MSG_BATCH_INS_WBWJDJ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*if( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if( DCICommit() != 0)
    {
        DCIFreeCursor(cur);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_PRETRTMNTFILE
组件名称:BATCH_PRETRTMNTFILE
组件功能: 批量业务外部文件信息预处理
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_PRETRTMNTFILE(HXMLTREE lXmlhandle)
{
    int    iParas;
    int    iFlag=0;
    int i,iCount;
    char sBuf[255];
    char itemBuf[128];
    char calcBuf[20+1];
    char sFixBuf[54+1];
    char sLpwjm[128+1];
    char sPkey[40+1];
/* modified by yangdong 20150918 dci改造，兼容64位
    long iSeqno=0;
*/
    int  iSeqno=0;

    char sEname[512+1];
    char sPczt[1+1];
    char sDjrq[8+1];
    int /*iCheckFlag=0,*/ret;
    char *pstr1,*pstr2;
    char sSql1[1024];
    char sErrmsg[512];
    int  iRet=-1;
    int iLen=0;
    int iDjlsh=0;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
      
    COMP_PARACOUNTCHKMIN(2)
  
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"登记日期")
    trim(sBuf);
    pstrcopy(sDjrq,sBuf,sizeof(sDjrq));
  
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"登记流水")
    iDjlsh=atol(sBuf);
    
    /* modified by yangdong 20111202 */
    if( strlen( sDjrq ) == 8 )
    {
        /* 获取外部文件信息 --B*/
        snprintf( sSql1, sizeof( sSql1 ), "SELECT LPWJM, PCZT FROM BATCH_WBWJDJ\
            WHERE  djrq='%s' AND djlsh=%d",sDjrq, iDjlsh );
        iRet = DBSelectToMultiVar( sErrmsg, sSql1, sLpwjm, sPczt ) ;
        if ( iRet < 0 )  
        {
            LOG(LM_STD,Fmtmsg("BATCH: 获取外部文件信息错误,[%s],[%d],sqlerr[%s]",sDjrq,iDjlsh,DCILastError()),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }  
    
        /* 校验状态 */
        switch(sPczt[0])
        {
            case WBWJDJ_ZT_PRE: /* 正在上传 */
                 iFlag=-1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_PRE,MSG_BATCH_WBWJDJ_PRE);
                 break;
            case WBWJDJ_ZT_READY: /* 就绪 */
                 iFlag=0;
                 break;
            case WBWJDJ_ZT_RUNNING: /* 正在处理 */
                 iFlag=1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_RUNNING,MSG_BATCH_WBWJDJ_RUNNING);
                 break;
            case WBWJDJ_ZT_SUCC: /* 已返回 */
                 iFlag=1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_SUCC,MSG_BATCH_WBWJDJ_SUCC);
                 break;
            case WBWJDJ_ZT_CX:  /* 已撤销 */
                 iFlag=1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_CX,MSG_BATCH_WBWJDJ_CX);
                 break;
            default:  /* 其他 */
                 iFlag=-1;
                 fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_UNKNOWN,\
                             Fmtmsg(MSG_BATCH_WBWJDJ_UNKNOWN, sPczt ));
                 break;
        }
        /* 文件状态错误 */
        if ( iFlag )
        {
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    else
    {
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_LPWJM,sBuf);
        pstrcopy( sLpwjm,sBuf,sizeof( sLpwjm));
    }

    LOG(LM_DEBUG,Fmtmsg("BATCH: 来盘文件名称解析,[%s]=>",sLpwjm),"DEBUG")

    /* 先解析XML变量 */
    if(xml_ParseXMLString(lXmlhandle,sLpwjm,sizeof(sLpwjm))==FAIL)
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,\
            Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 序列生成 */
    iCount=fprv_getDelimitCount(sLpwjm, "{SN(");
    for(i=0; i<iCount; i++)
    {
        /* 获取KEY
        strncpy(sEname,sLpwjm,sizeof(sEname)-1);
        memset(itemBuf, 0, sizeof(itemBuf));
        fprv_getSubStr(sEname,    1, "{SN(", itemBuf);
        memset(sPkey, 0, sizeof(sPkey));
        fprv_getSubStr(itemBuf, 0, ")}", sPkey);
        memset(sFixBuf, 0, sizeof(sFixBuf));
        snprintf(sFixBuf, sizeof( sFixBuf ),"{SN(%s)}",sPkey );
        */
        strncpy(sEname,sLpwjm,sizeof(sEname)-1);
        pstr1 = strstr(sEname,"{SN(");
        if ( !pstr1 )
            continue;
        pstr2 = strstr( pstr1,")}");
        if ( !pstr2 )
            continue;
        iLen = strlen(pstr1) - strlen(pstr2) -4 ;
        memset(sPkey, 0x00, sizeof(sPkey));
        memcpy(sPkey,pstr1+4,iLen);
        memset(sFixBuf, 0, sizeof(sFixBuf));
        snprintf(sFixBuf, sizeof( sFixBuf ),"{SN(%s)}",sPkey );
        LOG(LM_DEBUG,Fmtmsg("BATCH: 来盘文件名称解析,[%d][%s]=>[%s]",
            i, sLpwjm, sPkey),"DEBUG")
        /* 生成序列 */
        fprv_getSeqno(sPkey, &iSeqno);
        memset(calcBuf, 0, sizeof(calcBuf));
        snprintf(calcBuf, sizeof( calcBuf ), "%d", iSeqno);
        StrReplace(sLpwjm, sFixBuf, calcBuf);
    }
    LOG(LM_DEBUG,Fmtmsg("BATCH: 解析来盘文件名输出[%s]",sLpwjm),"DEBUG")
    COMP_SOFTSETXML( XMLNM_BATCH_REQ_LPWJM,sLpwjm );             

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_BREAK_RECOVER
组件名称:    BATCH_BREAK_RECOVER
组件功能: 断点数据恢复
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
  1   1-输入    批扣日期      416XML解析字符串  *      N    
  2   2-输入    平台批次号    416XML解析字符串  *      N   
使用限制:
       调用本组件之前，需要保存/batch节点下需要保存的信息，原来的/batch
结构会被保存的数据覆盖
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_BREAK_RECOVER(HXMLTREE lXmlhandle)
{
    char sBuf[128];
    int  iParas;
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sSql1[1024];
    int  iRet=-1;
    CURSOR cur;
    BATCH_WBWJDJ sdb_batch_wbwjdj;
    BATCH_PLRW   sdb_batch_plrw;

    COMP_PARACOUNTCHKMIN(2)
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_GETPARSEPARAS(1,sBuf,"批扣日期")
    trim(sBuf);
    /* added by yangdong 20151125 增加非空判断 */
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_GETPARSEPARAS(2,sBuf,"平台批次号")
    trim(sBuf);
    /* added by yangdong 20151125 增加非空判断 */
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEUBG")

    /* 获取外部文件信息 --B*/
    memset(&sdb_batch_wbwjdj,0,sizeof(BATCH_WBWJDJ));
    memset(&lvr,0,sizeof(lvr));

    /*
    snprintf( sSql1, sizeof( sSql1 ), "SELECT PCZT, breakdata, SHZT FROM BATCH_WBWJDJ\
    */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT breakdata FROM BATCH_WBWJDJ\
        WHERE pkrq = '%s' AND ptpch = '%s'", sPkrq, sPtpch );
    if ((cur = DCIDeclareCursor( sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("数据库操作失败[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("数据库操作失败[%s]",DCILastError()),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0);
    /* modified by yangdong 20151125 增加判断是否返回数据，否则为空的时候下一段代码会coredump 
    if( iRet == -1 )
    */
    if( iRet == -1 || iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH: 获取外部文件信息失败,pkrq[%s]ptpch[%s],sql[%s],\
                           SQLERR=[%s] [%d]", sPkrq, sPtpch, sSql1, DCILastError(), iRet ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

/*
    strncpy( sdb_batch_wbwjdj.pczt, DCIFieldAsString(cur, 0 ), sizeof( sdb_batch_wbwjdj.pczt ) );
    lvr.length = DCIFieldAsBlob(cur, 1, lvr.data, BATCH_MAX_XML );
    strncpy( sdb_batch_wbwjdj.shzt, DCIFieldAsString(cur, 2 ), sizeof( sdb_batch_wbwjdj.shzt ) );
*/

    lvr.length = DCIFieldAsBlob(cur, 0, lvr.data, BATCH_MAX_XML );

    DCIFreeCursor(cur);

    LOG(LM_DEBUG,Fmtmsg("BATCH: 获取外部文件信息[%d][%s]",lvr.length, lvr.data ),"INFO");

    if( lvr.length <= 0  )        
    {
        LOG(LM_STD,Fmtmsg("BATCH: 获取外部文件信息失败,plrwkdy=[%s%s]bufsize[%d][%s]pczt[%s]shzt[%s]",\
               sPkrq,sPtpch, lvr.length, lvr.data ,sdb_batch_wbwjdj.pczt, sdb_batch_wbwjdj.shzt),"ERROR");
        /* 20110710 不设置响应码，允许未登记buf
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WBWJDJ,MSG_BATCH_SEL_WBWJDJ);
        */
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }                

    /* 断点数据恢复 */

    /* 直接删除/batch节点下所有值 */
    if( xml_DelElement ( lXmlhandle, XMLNM_BATCH ) == -1 )
    {
        LOG(LM_STD,Fmtmsg("删除batch节点失败"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_XMLIMPORT,\
                   Fmtmsg(MSG_BATCH_XMLIMPORT,GETXMLERR));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 恢复保存的节点信息 */
    lvr.data[lvr.length] = '\0';
    if (xml_ImportXMLString(lXmlhandle, lvr.data, "/", 0 ) == -1)
    {
        LOG(LM_STD,Fmtmsg("恢复导入保存节点信息失败"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_XMLIMPORT,\
                    Fmtmsg(MSG_BATCH_XMLIMPORT,GETXMLERR));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    DCIFreeCursor(cur);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_GETINFO
组件名称:BATCH_GETINFO
组件功能: 批量业务获取业务信息
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
  1   1-输入    业务编号      416XML解析字符串  *      N    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_GETINFO(HXMLTREE lXmlhandle)
{
    int    iParas;
    char sBuf[255];
    char sCpdm[16+1];
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_RUNCTRL sdb_batch_runctrl;
    BATCH_MAPINFO sdb_batch_mapinfo_zj;
    BATCH_MAPINFO sdb_batch_mapinfo_ww;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sCpdm,0,sizeof(sCpdm));
    COMP_GETPARSEPARAS(1,sBuf,"批量产品代码")
    trim(sBuf);
    if( 0 == sBuf[0] )
    { 
            /* by yr 20121023 返回错误 */
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;      
    }
    pstrcopy(sCpdm,sBuf,sizeof(sCpdm));
    trim(sCpdm);

    LOG(LM_DEBUG,Fmtmsg("产品代码[%s]",sCpdm),"DEBUG")
    
    /* 获取运行控制参数 */
    memset(&sdb_batch_runctrl, 0, sizeof(BATCH_RUNCTRL));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_runctrl WHERE cpdm='%s'", sCpdm );
    iRet = fprv_SelToStruct( sSql1, SD_BATCH_RUNCTRL, NUMELE(SD_BATCH_RUNCTRL), &sdb_batch_runctrl);
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_RUNCTR,MSG_BATCH_SEL_RUNCTR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    trim(sdb_batch_runctrl.cpdm);
    trim(sdb_batch_runctrl.flowid);
    trim(sdb_batch_runctrl.maxtask);
    trim(sdb_batch_runctrl.maxthread);
    trim(sdb_batch_runctrl.zjysbs);
    trim(sdb_batch_runctrl.wwysbs);
    trim(sdb_batch_runctrl.shbz);
    trim(sdb_batch_runctrl.taskmode);
    trim(sdb_batch_runctrl.taskpri);
    trim(sdb_batch_runctrl.extfld1);
    
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_CPDM,     sdb_batch_runctrl.cpdm)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_FLOWID, sdb_batch_runctrl.flowid)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_MAXTASK,    sdb_batch_runctrl.maxtask)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_MAXTHREAD,sdb_batch_runctrl.maxthread)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_ZJYSBS,     sdb_batch_runctrl.zjysbs)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_WWYSBS,     sdb_batch_runctrl.wwysbs)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_SHBZ ,sdb_batch_runctrl.shbz)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_TASKMODE, sdb_batch_runctrl.taskmode)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_TASKPRI, sdb_batch_runctrl.taskpri)
    COMP_HARDSETXML(XMLNM_BATCH_RUNCTRL_EXTFLD1,sdb_batch_runctrl.extfld1)
    
    /* 获取批量业务主机映射信息 */
    if( strlen( sdb_batch_runctrl.zjysbs ) > 1 )
    {
        memset(&sdb_batch_mapinfo_zj, 0, sizeof(sdb_batch_mapinfo_zj));

        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM BATCH_MAPINFO WHERE mapid='%s' AND maptype = '1'", sdb_batch_runctrl.zjysbs );
        iRet = fprv_SelToStruct( sSql1, SD_BATCH_MAPINFO, NUMELE(SD_BATCH_MAPINFO), &sdb_batch_mapinfo_zj );
        if( iRet <= 0 )
        {
            LOG(LM_STD,Fmtmsg("主机文件映射标识[%s]未找到", sdb_batch_runctrl.zjysbs ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_MAPINFO,MSG_BATCH_SEL_MAPINFO);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        trim(sdb_batch_mapinfo_zj.mapid);
        trim(sdb_batch_mapinfo_zj.ywbm);
        trim(sdb_batch_mapinfo_zj.tjwjbs);
        trim(sdb_batch_mapinfo_zj.thwjbs);
        trim(sdb_batch_mapinfo_zj.zhbz);
        trim(sdb_batch_mapinfo_zj.zhbs);
        
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_MAPID     ,sdb_batch_mapinfo_zj.mapid)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_YWBM      ,sdb_batch_mapinfo_zj.ywbm)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_TJWJBS    ,sdb_batch_mapinfo_zj.tjwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_THWJBS    ,sdb_batch_mapinfo_zj.thwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_JLSXZ     ,itoa( sdb_batch_mapinfo_zj.jlsxz) );
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_ZHBZ      ,sdb_batch_mapinfo_zj.zhbz)
        COMP_HARDSETXML(XMLNM_BATCH_ZJMAPINFO_ZHBS      ,sdb_batch_mapinfo_zj.zhbs)
    }

    /* 获取批量业务外围映射信息 */
    if( strlen( sdb_batch_runctrl.wwysbs ) > 1 )
    {
        memset(&sdb_batch_mapinfo_ww, 0, sizeof(sdb_batch_mapinfo_ww));
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM BATCH_MAPINFO WHERE mapid='%s' AND maptype = '0'", sdb_batch_runctrl.wwysbs );
        iRet = fprv_SelToStruct( sSql1, SD_BATCH_MAPINFO, NUMELE(SD_BATCH_MAPINFO), &sdb_batch_mapinfo_ww );
        if( iRet <= 0 )
        {
            LOG(LM_STD,Fmtmsg("外围文件映射标识[%s]未找到", sdb_batch_runctrl.wwysbs ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_MAPINFO,MSG_BATCH_SEL_MAPINFO);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        trim(sdb_batch_mapinfo_ww.mapid);
        trim(sdb_batch_mapinfo_ww.ywbm);
        trim(sdb_batch_mapinfo_ww.lpwjbs);
        trim(sdb_batch_mapinfo_ww.hpwjbs);
        trim(sdb_batch_mapinfo_ww.zhbz);
        trim(sdb_batch_mapinfo_ww.zhbs);
        
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_MAPID     ,sdb_batch_mapinfo_ww.mapid)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_YWBM      ,sdb_batch_mapinfo_ww.ywbm);
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_LPWJBS    ,sdb_batch_mapinfo_ww.lpwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_HPWJBS    ,sdb_batch_mapinfo_ww.hpwjbs)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_ZHBZ      ,sdb_batch_mapinfo_ww.zhbz)
        COMP_HARDSETXML(XMLNM_BATCH_WWMAPINFO_ZHBS      ,sdb_batch_mapinfo_ww.zhbs)
    }

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_INS_PLRW
组件名称:BATCH_INS_PLRW
组件功能: 批量业务任务信息登记
组件参数:
 序号 参数类型    参数名称                 资源类别         缺省值    可空    参数说明        
    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_INS_PLRW(HXMLTREE lXmlhandle)
{
    char sBuf[255];
    char sClrq[8+1];
    char sBusiMon[32+1];
    char sPlrwKey[24+1];
    char sErrmsg[512];
    int iRet=-1;
    int    iParas;
/* modified by yangdong 20150918 dci改造，兼容64位
    long iseqno=0;
*/
    int iseqno=0;

    BATCH_PLRW sdb_batch_plrw;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")

    memset(&sdb_batch_plrw,0,sizeof(sdb_batch_plrw));
    
    /* 业务编号 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_YWBH,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_plrw.ywbh,sBuf,sizeof(sdb_batch_plrw.ywbh));
    
    /*批扣日期(产品日期)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf);
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_batch_plrw.pkrq,sBuf,sizeof(sdb_batch_plrw.pkrq));
    /*取平台批次号*/
    if( fprv_getSeqno2(BATCH_PTPCH_XLJZ, &iseqno) < 0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    sprintf(sdb_batch_plrw.ptpch,"%ld",iseqno);
    trim(sdb_batch_plrw.ptpch);
    COMP_SOFTSETXML(XMLNM_BATCH_PTPCH,sdb_batch_plrw.ptpch);

    memset(sPlrwKey, 0x00, sizeof(sPlrwKey));
    snprintf(sPlrwKey, sizeof(sPlrwKey), "%s%s", sdb_batch_plrw.pkrq,sdb_batch_plrw.ptpch);
    COMP_SOFTSETXML(XMLNM_BATCH_PLRWKEY, sPlrwKey);
    /* 任务优先级 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_TASKPRI,sBuf);
    if (sBuf[0] == '\0')
    {/*接口中优先级为空，则取运行控制表中的优先级*/
        COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_TASKPRI,sBuf);
        if (sBuf[0] == '\0')
        {
            sBuf[0] = '0';/*低级*/
        }
    }
    pstrcopy(sdb_batch_plrw.taskpri,sBuf,sizeof(sdb_batch_plrw.taskpri));
    COMP_SOFTSETXML(XMLNM_BATCH_TASKPRI, sdb_batch_plrw.taskpri)
        
    /*商户批次号(外部文件登记获取)*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_SHPCH,sBuf);
    pstrcopy(sdb_batch_plrw.shpch,sBuf,sizeof(sdb_batch_plrw.shpch));

    /*单位编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_DWCPXY_DWBH,sBuf);
    pstrcopy(sdb_batch_plrw.dwbh,sBuf,sizeof(sdb_batch_plrw.dwbh));

    /*提交日期*/
    sprintf(sdb_batch_plrw.tjrq,"%s",GetSysDate());
    /*提交时间*/
    sprintf(sdb_batch_plrw.tjsj,"%s",GetSysTime()); 
    /*处理日期*/
    pstrcopy(sdb_batch_plrw.clrq," ",sizeof(sdb_batch_plrw.clrq));
    memset( sClrq, 0x00, sizeof( sClrq ) );
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_SJTJ_DATE,sBuf);
    pstrcopy(sClrq,sBuf,sizeof(sClrq));
    if( strlen( sClrq ) < 4 )  /* 如果未输入合法处理日期，默认取当前日期 */
    {
        pstrcopy(sdb_batch_plrw.clrq,sdb_batch_plrw.pkrq, sizeof(sdb_batch_plrw.clrq));
    }
    else
    {
        pstrcopy(sdb_batch_plrw.clrq, sClrq, sizeof(sdb_batch_plrw.clrq));
    }
    /*处理时间*/
    pstrcopy(sdb_batch_plrw.clsj," ",sizeof(sdb_batch_plrw.clsj));
    /*总金额*/
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZJE,sBuf);
    sdb_batch_plrw.zje = atof(sBuf);
    /*总笔数*/
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_ZBS,sBuf);
    sdb_batch_plrw.zbs = atoi (sBuf);
    /*实际总金额*/
    sdb_batch_plrw.sjzje = 0.00;
    /*实际总笔数*/
    sdb_batch_plrw.sjzbs = 0;
    /*成功总金额*/
    sdb_batch_plrw.cgzje = 0.00;
    /*成功总笔数*/
    sdb_batch_plrw.cgzbs = 0;
    /*失败总金额*/
    sdb_batch_plrw.sbzje = 0.00;
    /*失败总笔数*/
    sdb_batch_plrw.sbzbs = 0;
    /*手续费金额*/
    sdb_batch_plrw.sxfje = 0.00;
    /*新开户笔数*/
    sdb_batch_plrw.xkhbs = 0;
    /*新开户金额*/
    sdb_batch_plrw.xkhje = 0.00;
    /*商户来盘文件名*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_LPWJM,sBuf);
    pstrcopy(sdb_batch_plrw.lpwjm,sBuf,sizeof(sdb_batch_plrw.lpwjm));
    /*上传主机文件名*/
    pstrcopy(sdb_batch_plrw.sczjwjm," ",sizeof(sdb_batch_plrw.sczjwjm));
    /*主机回复文件名*/
    pstrcopy(sdb_batch_plrw.zjhfwjm," ",sizeof(sdb_batch_plrw.zjhfwjm));

    /*回复商户成功文件名*/
    pstrcopy(sdb_batch_plrw.shcgwjm," ",sizeof(sdb_batch_plrw.shsbwjm));
    /*回复商户失败文件名*/
    pstrcopy(sdb_batch_plrw.shsbwjm," ",sizeof(sdb_batch_plrw.shsbwjm));
    /*操作步点*/
    pstrcopy(sdb_batch_plrw.dqbd,"0",sizeof(sdb_batch_plrw.dqbd));
    /*辅助步点*/
    pstrcopy(sdb_batch_plrw.fzbd,"00",sizeof(sdb_batch_plrw.fzbd));
    /*步点状态 - */
    pstrcopy(sdb_batch_plrw.bdzt,"9",sizeof(sdb_batch_plrw.bdzt));
    /*任务状态 - 在处理*/
    pstrcopy(sdb_batch_plrw.rwzt,"9",sizeof(sdb_batch_plrw.rwzt));
    /*响应代码*/
    pstrcopy(sdb_batch_plrw.xydm," ",sizeof(sdb_batch_plrw.xydm));
    /*响应信息*/
    pstrcopy(sdb_batch_plrw.xyxx," ",sizeof(sdb_batch_plrw.xyxx));
    /*嵌套批扣日期*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QTPKRQ,sBuf);
    pstrcopy(sdb_batch_plrw.qtpkrq,sBuf,sizeof(sdb_batch_plrw.qtpkrq));
    /*嵌套平台批次号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_QTPTPCH,sBuf);
    pstrcopy(sdb_batch_plrw.qtptpch,sBuf,sizeof(sdb_batch_plrw.qtptpch));
    if (sdb_batch_plrw.qtptpch[0] != '\0')
    {/*被嵌套*/
        sdb_batch_plrw.qtbz[0] = '2';
    }else
    {
        sdb_batch_plrw.qtbz[0] = '0';
    }
    COMP_SOFTSETXML(XMLNM_BATCH_REQ_QTBZ, sdb_batch_plrw.qtbz)
    /*sql_BeginTrans(); 用DCIBegin代替 2015-1-7 by chenxm*/
    DCIBegin();

    iRet = DBInsert("batch_plrw", SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg);
    if( iRet < 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRW,MSG_BATCH_INS_PLRW);
        return COMPRET_FAIL;
    }

    /*if( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_DQBD, sdb_batch_plrw.dqbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_FZBD, sdb_batch_plrw.fzbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_BDZT, sdb_batch_plrw.bdzt)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_RWZT, sdb_batch_plrw.rwzt)

    /*写批量任务业务监控*/
    memset(sBusiMon, 0x00, sizeof(sBusiMon));
    COMP_SOFTGETXML(XMLNM_BATCH_MON_NORM, sBusiMon)
    if ( sBusiMon[0] == '\0')
    {
        pstrcopy(sBusiMon, BATCH_MON_NORM, sizeof(sBusiMon));
    }
    prv_batch_busimon(lXmlhandle, sBusiMon);

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_UPD_FILE
组件名称:BATCH_UPD_FILE
组件功能: 批量业务外部文件信息更新
组件参数:
 序号 参数类型  参数名称  资源类别     缺省值  可空  参数说明    
1   1-输入   更新标志   解析字符串  *      N   1 更新平台批次号 2 更新批次状
2   2-输入   更新内容   解析字符串  *      N   
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_UPD_FILE(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    char sUpdContent[16+1];
    int iParas,iUpdFlag;
    int iResult,ret;
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_WBWJDJ sdb_batch_wbwjdj;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");
    
    COMP_PARACOUNTCHK(2)        /* 检查组件参数个数 */
    memset(sBuf,0,sizeof(sBuf));
    memset(&sdb_batch_wbwjdj,0,sizeof(sdb_batch_wbwjdj));
    COMP_GETPARSEPARAS(1, sBuf, "更新标志"); /*1 更新平台批次号 2 更新批次状态 */
    iUpdFlag=atoi(sBuf);
        
    memset(sBuf,0,sizeof(sBuf));
    memset(sUpdContent,0,sizeof(sUpdContent));
    COMP_GETPARSEPARAS(2, sBuf, "更新内容");
    pstrcopy(sUpdContent, sBuf, sizeof(sUpdContent));
    trim(sUpdContent);

    memset(sBuf,0,sizeof(sBuf));    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf);  /*批扣日期*/ 
    pstrcopy(sdb_batch_wbwjdj.pkrq,sBuf,sizeof(sdb_batch_wbwjdj.pkrq));
    if(strlen(sdb_batch_wbwjdj.pkrq)<=0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    

    /*sql_BeginTrans(); 用DCIBegin代替 2015-1-7 by chenxm*/
    DCIBegin();
        
    if( iUpdFlag ==1 )  /*  更新平台批次号 */
    {
        memset(sBuf,0,sizeof(sBuf));    
        COMP_SOFTGETXML(XMLNM_BATCH_WBWJDJ_DJRQ, sBuf);  /*登记日期*/ 
        pstrcopy(sdb_batch_wbwjdj.djrq,sBuf,sizeof(sdb_batch_wbwjdj.djrq));
        if(strlen(sdb_batch_wbwjdj.djrq)<=0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_DJRQ_NULL,MSG_BATCH_DJRQ_NULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }    
        memset(sBuf,0,sizeof(sBuf));                 
        COMP_SOFTGETXML(XMLNM_BATCH_WBWJDJ_DJLSH , sBuf); /*登记流水号*/    
        if(strlen(sBuf)<=0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_DJLSH_NULL,MSG_BATCH_DJLSH_NULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sdb_batch_wbwjdj.djlsh=atol(sBuf); 

        snprintf( sSql1, sizeof( sSql1 ), "UPDATE BATCH_WBWJDJ SET pkrq='%s', ptpch='%s', pczt = '3'\
            WHERE djrq='%s' AND djlsh=%d", sdb_batch_wbwjdj.pkrq, sUpdContent, sdb_batch_wbwjdj.djrq, sdb_batch_wbwjdj.djlsh);

        iRet = DCIExecuteDirect( sSql1 );
        if( iRet <= 0 )
        {
             LOG(LM_STD,Fmtmsg("数据库操作失败,sql[%s]err[%s]",sSql1, DCILastError() ),"ERROR")
             /*sql_RollbackTrans();*/
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_WBWJDJ,MSG_BATCH_UPD_WBWJDJ );
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
        }
    }
    else if( iUpdFlag == 2 ) /* 更新批次状态 */
    {
        memset(sBuf,0,sizeof(sBuf));    
        COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf); /*平台批次号*/ 
        pstrcopy(sdb_batch_wbwjdj.ptpch,sBuf,sizeof(sdb_batch_wbwjdj.ptpch));
        if(strlen(sdb_batch_wbwjdj.ptpch)<=0)
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }    
        snprintf( sSql1, sizeof( sSql1 ), "UPDATE BATCH_WBWJDJ SET pczt='%s' WHERE pkrq='%s' AND ptpch='%s'",\
            sUpdContent, sdb_batch_wbwjdj.pkrq, sdb_batch_wbwjdj.ptpch);\
        iRet = DCIExecuteDirect( sSql1 );
        if( iRet <= 0 )
        {
             LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s][%s]",DCILastError(),sSql1 ),"ERROR")
             /*sql_RollbackTrans();*/
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_PLRWBD, MSG_BATCH_UPD_PLRWBD );
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
        }
    }
    else
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_UPDFLAG_FF,MSG_BATCH_UPDFLAG_FF);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;            
    }    

    /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
        
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_UPD_PLRW
组件名称:BATCH_UPD_PLRW
组件功能: 
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
  1   1-输入   当前步点      416XML解析字符串     *         Y      
  1   1-输入   辅助步点      416XML解析字符串     *         N  
  1   1-输入   步点状态      416XML解析字符串     *         Y      
  1   1-输入   任务状态      416XML解析字符串     *         N      
  
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_UPD_PLRW(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int iParas;
    int iResult;
    char sStep[8+1];
    char sStepNew[8+1];
    char sStepStatus[8+1];
    char sTaskStatus[8+1];
    char sAstStep[2+1];
    char sTestFlag[2+1];
    char sBreak[1+1];
    char sClsj[6+1];

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");
    
    COMP_PARACOUNTCHK(4)        /* 检查组件参数个数 */
            
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "当前步点");
    trim(sBuf);
    pstrcopy( sStep, sBuf, sizeof( sStep ) );/*当前步点*/     
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sAstStep, 0x00, sizeof(sAstStep));
    COMP_GETPARSEPARAS(2, sBuf, "辅助步点");
    trim(sBuf);
    pstrcopy( sAstStep, sBuf, sizeof( sAstStep  ) );/*辅助步点*/  
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "步点状态");
    trim(sBuf);
    pstrcopy( sStepStatus, sBuf, sizeof( sStepStatus ) );/*步点状态*/    
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "任务状态");
    trim(sBuf);
    pstrcopy( sTaskStatus, sBuf, sizeof( sTaskStatus  ) );/*任务状态*/    
    
    memset(sBreak, 0x00, sizeof(sBreak));
    memset(sClsj, 0x00, sizeof(sClsj));
    if ( sStep[0] == BATCH_STEPSN_SJTJ)
    {
        COMP_SOFTGETXML("/batch/sjtj/ddbz", sBreak)
        if (sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK)
        {
            COMP_SOFTGETXML("/batch/sjtj/clsj", sClsj)
        }
    }
    LOG(LM_DEBUG, Fmtmsg("upd plrw sBreak=[%s],sClsj=[%s]", sBreak, sClsj), "DEBUG");
    /* modified by yangdong 20130219 增加开始处理时间 
    iResult = fprv_batch_upd_plrw( lXmlhandle,sStep,sStepStatus,sTaskStatus );
    */
    
    /*mod by tuql 20160606 begin
     * 需求单:201606060219
     */
    DCIBegin();
    iResult = fprv_batch_upd_plrw( lXmlhandle,sStep,sAstStep,sStepStatus,sTaskStatus,sBreak,sClsj );
    DCICommit();/*add by tuql 20160606 需求单:201606060219 */
    return iResult;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_INS_PLRWBD
组件名称:BATCH_INS_PLRWBD
组件功能: 批量业务任务步点信息登记
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
  1   1-输入   重复操作标志   416XML解析字符串     *   N   0允许 1不允许
  2   2-输入   操作步点       416XML解析字符串     *   N   
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_INS_PLRWBD(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int iParas;
    char xmlNode[512];
    char sCfczbz[1+1];
    char DB_sBdzt[1+1];
    /*int iUpdFlag=0;*/
    /* modified by yangdong 201201101 增加默认重复次数
    char    sCfcs[3];
    */
    int   iClcs=0;
    char  sSjcfczcs[3];
    char  sStepID[100];
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_PLRWBD sdb_batch_plrwbd;
    
    fpub_InitSoComp(lXmlhandle);
 
    COMP_PARACOUNTCHKMIN(2)
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"重复操作标志") /* 0允许 1不允许*/
    trim( sBuf );
    pstrcopy( sCfczbz, sBuf, sizeof( sCfczbz ) );
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"操作步点") 
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_CZBD_NULL,MSG_BATCH_CZBD_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;        
    }
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始,重复操作标志[%s],操作步点[%s]", 
        fpub_GetCompname(lXmlhandle), sCfczbz, sBuf), "DEBUG");
    memset(&sdb_batch_plrwbd,0,sizeof(sdb_batch_plrwbd));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_BDZT, sBuf)
    pstrcopy(sdb_batch_plrwbd.bdzt, sBuf, sizeof(sdb_batch_plrwbd.bdzt)); 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sBuf)
    pstrcopy(sdb_batch_plrwbd.czbd, sBuf, sizeof(sdb_batch_plrwbd.czbd)); 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sBuf)
    pstrcopy(sdb_batch_plrwbd.fzbd, sBuf, sizeof(sdb_batch_plrwbd.fzbd));
    
    /*批扣日期*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML(XMLNM_BATCH_PKRQ, sBuf);                        
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PKRQ_NULL,MSG_BATCH_PKRQ_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    
    pstrcopy(sdb_batch_plrwbd.pkrq,sBuf,sizeof(sdb_batch_plrwbd.pkrq));
    trim(sdb_batch_plrwbd.pkrq);
    
    /*批次号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML(XMLNM_BATCH_PTPCH , sBuf);                 
    pstrcopy(sdb_batch_plrwbd.ptpch,sBuf,sizeof(sdb_batch_plrwbd.ptpch));
    if(strlen(sdb_batch_plrwbd.ptpch)<=0)
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_PTPCH_NULL,MSG_BATCH_PTPCH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*strcpy( sdb_batch_plrwbd.bdzt, BATCH_STEP_STATUS_S_RUNNING );*/

    /*流程执行序号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML(XMLNM_BATCH_FLOWCFG_FLOWSN , sBuf);                 
    sdb_batch_plrwbd.flowsn = atoi(sBuf);
    /*处理机构*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJJG ,sBuf); 
    if( 0 == sBuf[0] ) 
    {/*交易机构为空*/
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG,sBuf);
        if( 0 == sBuf[0] ) 
        {/*cpxx表的主办机构也为空*/
            fpub_SetMsg(lXmlhandle,MID_BATCH_JYJGNULL,MSG_BATCH_JYJGNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    trim(sBuf);
    pstrcopy(sdb_batch_plrwbd.cljg,sBuf,sizeof(sdb_batch_plrwbd.cljg));
    
    /*处理柜员*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_DJGY ,sBuf);
    if( 0 == sBuf[0] ) 
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG,sBuf);
    }
    trim(sBuf);
    pstrcopy(sdb_batch_plrwbd.clgy,sBuf,sizeof(sdb_batch_plrwbd.clgy));
    /*处理开始日期*/ 
    sprintf(sdb_batch_plrwbd.clksrq,"%s",GetSysDate());                
    
    /*处理开始时间*/                
    sprintf(sdb_batch_plrwbd.clkssj,"%s",GetSysTime());        

    /* 检查步点状态表 */        
    memset(DB_sBdzt,0,sizeof(DB_sBdzt));
    memset(sBuf,0,sizeof(sBuf));
    iClcs=0;

    snprintf( sSql1, sizeof( sSql1 ),"SELECT bdzt,clcs FROM batch_plrwbd\
        WHERE  pkrq='%s' AND ptpch='%s' AND flowsn = %d AND czbd='%s' ",\
        sdb_batch_plrwbd.pkrq, sdb_batch_plrwbd.ptpch, 
        sdb_batch_plrwbd.flowsn,sdb_batch_plrwbd.czbd );
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, DB_sBdzt, sBuf );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    DCIBegin(); /*add by chenxm 2015-1-7*/
    iClcs = atoi( sBuf );

    /* 已经存在步点记录 */
    if( iRet > 0 )
    {
        /* 不能允许同时进行 
        if( DB_sBdzt[0] == '9' )
        {
            LOG(LM_STD,Fmtmsg("步点状态[%s],不允许重复操作", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CFCZ,MSG_BATCH_CFCZ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        else */
        if( DB_sBdzt[0] == 'C' || DB_sBdzt[0] == 'X' || 
            DB_sBdzt[0] == 'c' || DB_sBdzt[0] == 'x' )
        {
            LOG(LM_STD,Fmtmsg("步点状态[%s],不允许操作", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CANCELED,MSG_BATCH_CANCELED );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*  不允许重复操作，若步点状态不为操作失败，出错返回 */
        /* add by yr 20120927  */    
        /* modified by yangdong 20121101 
        if( sCfczbz[0] != '0' )
        */
        if( ( sCfczbz[0] != '0' ) && ( DB_sBdzt[0] != '0' ) )
        {
            LOG(LM_STD,Fmtmsg("步点状态[%s],不允许重复操作", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CFCZ,MSG_BATCH_CFCZ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* del by yangdong 20121101
        if( DB_sBdzt[0] != '0'  )
        {
            LOG(LM_STD,Fmtmsg("步点状态[%s],不允许重复操作", DB_sBdzt ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_CFCZ,MSG_BATCH_CFCZ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        */
        LOG(LM_STD,Fmtmsg("insert/update plrwbd [%s%s%s]",  
            sdb_batch_plrwbd.pkrq, sdb_batch_plrwbd.ptpch, sdb_batch_plrwbd.czbd),"INFO")
        /* 重复操作时，先更新步点状态为9  */
        snprintf( sSql1, sizeof( sSql1 ), "UPDATE batch_plrwbd SET bdzt = '9'\
            WHERE pkrq='%s' AND ptpch='%s' AND flowsn='%d' AND czbd='%s'",\
            sdb_batch_plrwbd.pkrq, sdb_batch_plrwbd.ptpch, 
            sdb_batch_plrwbd.flowsn, sdb_batch_plrwbd.czbd );
        iRet = DCIExecuteDirect( sSql1 );
        if( iRet < 1 )
        {
            /*sql_RollbackTrans();*/
            DCIRollback();
            LOG(LM_STD,Fmtmsg("步点[%s]更新状态失败", sdb_batch_plrwbd.czbd ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_UPD_PLRWBD,MSG_BATCH_UPD_PLRWBD);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
        if(DCICommit() != 0)
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
    }
    /* 不存在则登记 */
    else
    {
        iRet = DBInsert("batch_plrwbd", SD_BATCH_PLRWBD, NUMELE(SD_BATCH_PLRWBD), &sdb_batch_plrwbd, sErrmsg);
        if( iRet < 0 )
        {
            /*sql_RollbackTrans();*/
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRWBD,MSG_BATCH_INS_PLRWBD);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /*if( sql_CommitTrans() != MID_SYS_SUCC )*/
        if(DCICommit() != 0)
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_UPD_PLRWBD
组件名称:BATCH_UPD_PLRWBD
组件功能: 批量业务任务步点信息更新
组件参数:
 序号 参数类型  参数名称 资源类别     缺省值  可空  参数说明    
1   1-输入   步点状态   解析字符串     *   N   9在处理中  0中止 1结束2断点3返回4等待
2   2-输入   操作步点   解析字符串     *   N   0 获取数据 1 数据入库 2 数据审核 3 数据提交 4数据提回  5企业回盘
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_UPD_PLRWBD(HXMLTREE lXmlhandle)
{
   char sBuf[128+1];
   char sStep[8+1];
   char sStepStatus[8+1];
   int iParas;
   int iRet = -1;
    
   fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    COMP_PARACOUNTCHK(2)        
    
    memset( sStep, 0x00, sizeof( sStep ) );
    memset( sStepStatus, 0x00, sizeof( sStepStatus ) );
    /*步点状态*/ 
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "步点状态");
    trim(sBuf);
    pstrcopy(sStepStatus, sBuf, sizeof(sStepStatus));    
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "操作步点");
    if( 0 == sBuf[0] )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_CZBD_NULL,MSG_BATCH_CZBD_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;            
    }
    pstrcopy(sStep, sBuf, sizeof(sStep));    
    /*mod by tuql 20160606 begin
     * 需求单:201606060219
     */
    DCIBegin();
    iRet = fprv_batch_upd_plrwbd( lXmlhandle, sStepStatus, sStep );
    DCICommit();/*add by tuql 20160606 需求单:201606060219 */
    return iRet;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_GETFILETYPE
组件名称:BATCH_GETFILETYPE
组件功能: 批量业务获取文件类型信息
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
  1   1-输入   文件标识       416-解析字符串            N    文件标识              
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_GETFILETYPE(HXMLTREE lXmlhandle)
{
    int    iParas;
    char sBuf[255];
    char sFileId[50+1];
    char sSql1[1024];
    char sErrmsg[512];
    int iRet=-1;
    BATCH_FILETYPE sdb_batch_filetype;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    COMP_PARACOUNTCHKMIN(1)
    memset(sBuf,0,sizeof(sBuf));
    memset(sFileId,0,sizeof(sFileId));
    COMP_GETPARSEPARAS(1,sBuf,"文件标识")
    pstrcopy(sFileId,sBuf,sizeof(sFileId));
    
    if( sFileId[0] == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_WJBS_NULL,MSG_BATCH_WJBS_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    } 
    
    memset(&sdb_batch_filetype,0,sizeof(sdb_batch_filetype));
    
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM BATCH_FILETYPE WHERE fileid='%s'", sFileId );
    iRet = fprv_SelToStruct( sSql1, SD_BATCH_FILETYPE, NUMELE(SD_BATCH_FILETYPE), &sdb_batch_filetype); 
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("查询文件类型失败[%s]",sFileId),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_WJLX,MSG_BATCH_SEL_WJLX);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }                

    trim(sdb_batch_filetype.fileid);        
    trim(sdb_batch_filetype.filetype);    
    trim(sdb_batch_filetype.filefmt);  
    trim(sdb_batch_filetype.codefmt);    
    trim(sdb_batch_filetype.extfld1);    
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_FILEID    , sdb_batch_filetype.fileid)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_FILETYPE  , sdb_batch_filetype.filetype)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_FILEFMT   , sdb_batch_filetype.filefmt)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_CODEFMT   , sdb_batch_filetype.codefmt)
    COMP_SOFTSETXML(XMLNM_BATCH_WJLX_EXTFLD1   , sdb_batch_filetype.extfld1)
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_RESP
组件名称:BATCH_RESP
组件功能: 批量业务响应码转换 只转换审核失败明细
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
 1   1-输入   响应码资源名   416-解析字符串            Y    响应码资源名   
 2   1-输入   批扣日期       416-解析字符串            Y    批扣日期   
 3   1-输入   平台批次号     416-解析字符串            Y    平台批次号   
 4   1-输入   业务表名       416-解析字符串            Y    业务表名   
 5   1-输入   源响应码       416-解析字符串            Y    源响应码
 6   1-输入   目的响应码     416-解析字符串            Y    目的响应码
 7   1-输入   目的响应信息   416-解析字符串            Y    目的响应信息
 8   1-输入   转换范围       416-解析字符串            Y    转换范围
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_RESP(HXMLTREE lXmlhandle)
{
    char sBuf[255];
    char sDft[1+1];
    char sMsgD[20+1];
    char sDest[20+1];
    char sDestMsg[40+1];
    char sSource[10+1];
    char sResName[50+1];
    char sColumnS[20+1];
    char sColumnD[20+1];
    char sErrmsg[512];
    char sSql1[1024];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char DB_sTableName[50+1];
    char sFlag[1+1];
    int  iParas;
    int  i, iResult;
    int  iRet=-1;
    CURSOR cur;
    BATCH_MAPRESP sdb_batch_mapresp;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    COMP_PARACOUNTCHKMIN(7)
    memset(sBuf,0,sizeof(sBuf));
    memset(sResName,0,sizeof(sResName));
    COMP_GETPARSEPARAS(1,sBuf,"响应码资源名")
    pstrcopy(sResName,sBuf,sizeof(sResName));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPkrq,0,sizeof(sPkrq));
    COMP_GETPARSEPARAS(2,sBuf,"批扣日期")
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sPtpch,0,sizeof(sPtpch));
    COMP_GETPARSEPARAS(3,sBuf,"平台批次号")
    pstrcopy(sPtpch,sBuf,sizeof(sPtpch));
    
    memset(sBuf,0,sizeof(sBuf));
    memset(DB_sTableName,0,sizeof(DB_sTableName));
    COMP_GETPARSEPARAS(4,sBuf,"业务表名")
    pstrcopy(DB_sTableName,sBuf,sizeof(DB_sTableName));
  
    memset(sBuf,0,sizeof(sBuf));
    memset(sColumnS,0,sizeof(sColumnS));
    COMP_GETPARSEPARAS(5,sBuf,"来源字段名")
    pstrcopy(sColumnS,sBuf,sizeof(sColumnS));

    memset(sBuf,0,sizeof(sBuf));
    memset(sColumnD,0,sizeof(sColumnD));
    COMP_GETPARSEPARAS(6,sBuf,"目的响应码")
    pstrcopy(sColumnD,sBuf,sizeof(sColumnD));

    memset(sBuf,0,sizeof(sBuf));
    memset(sMsgD,0,sizeof(sMsgD));
    COMP_GETPARSEPARAS(7,sBuf,"目的响应信息")
    pstrcopy(sMsgD,sBuf,sizeof(sMsgD));

    memset(sBuf,0,sizeof(sBuf));
    memset(sFlag,0,sizeof(sFlag));
    COMP_GETPARSEPARAS(8,sBuf,"转换范围")
    pstrcopy(sFlag,sBuf,sizeof(sFlag));

    if( sColumnS[0] == '\0' )
       strcpy( sColumnS,"xym" );  /* 默认字段为xym */
    if( sColumnS[0] == '\0' )
       strcpy( sColumnD,"xym" );  /* 默认字段为xym */

    LOG(LM_DEBUG,Fmtmsg("BATCH:响应码转换资源名[%s] 源字段[%s]  目的字段[%s]", sResName, sColumnS, sColumnD),"DEBUG")
  
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ),"SELECT * FROM batch_mapresp WHERE mapid='%s'", sResName );
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
    
    DCIBegin();
    
    while( ( iRet = DBFetch(cur, SD_BATCH_MAPRESP, NUMELE(SD_BATCH_MAPRESP), &sdb_batch_mapresp, sErrmsg ) ) > 0 )
    {
        /*对取出的数据进行处理*/
        strcpy( sSource, sdb_batch_mapresp.resp_s ); 
        trim(sSource);

        strcpy( sDest, sdb_batch_mapresp.resp_d ); 
        trim(sDest);

        strcpy( sDestMsg, sdb_batch_mapresp.msg_d ); 
        trim(sDestMsg);

        sDft[0] = sdb_batch_mapresp.bz[0];

        memset(sSql1, 0, sizeof(sSql1));

        LOG(LM_DEBUG,Fmtmsg("BATCH:响应码转换 源值[%s] 目的值[%s] [%s]", sSource, sDest, sDestMsg ),"DEBUG")

        trim( sDestMsg ); 
        /* 判断是否需要转换响应信息  */
        if( strlen( sDestMsg ) > 0 )
        {
            /* 默认值处理 */
            if( sDft[0] == '0' )  /* 默认值 */
            {
                /* added by yangdong 20120508 增加对NULL的判断 */
                /* added by yangdong 20130609 只处理审核失败明细的情况判断 */
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s', %s='%s' \
                    WHERE pkrq='%s' AND ptpch='%s' AND \
                    ( trim(%s)='%s' OR ( trim(%s) NOT IN( SELECT trim( resp_s ) FROM batch_mapresp WHERE mapid='%s' ) ) \
                    OR ( %s IS NULL ) )",\
                    DB_sTableName, sColumnD, sDest, sMsgD, sDestMsg, sPkrq, sPtpch,\
                    sColumnS, sSource , sColumnS, sResName, sColumnS );
            }
            else
            {
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s', %s='%s' \
                    WHERE pkrq='%s' AND ptpch='%s' AND trim(%s)='%s'",\
                    DB_sTableName, sColumnD, sDest, sMsgD, sDestMsg, sPkrq, sPtpch, sColumnS, sSource );
            }
        }
        else
        {
            /* 默认值处理 */
            if( sDft[0] == '0' )  /* 默认值 */
            {
                /* added by yangdong 20120508 增加对NULL的判断 */
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s' \
                    WHERE pkrq='%s' AND ptpch='%s' AND \
                    ( trim(%s)='%s' OR ( trim(%s) NOT IN( SELECT trim( resp_s ) FROM batch_mapresp WHERE mapid='%s' ) ) \
                    OR ( %s IS NULL ) )",\
                    DB_sTableName, sColumnD, sDest, sPkrq, sPtpch, sColumnS, sSource , sColumnS, sResName, sColumnS );
            }
            else
            {
                snprintf(sSql1,sizeof(sSql1),"UPDATE %s SET %s='%s'  \
                    WHERE pkrq='%s' AND ptpch='%s' AND trim(%s)='%s'",\
                    DB_sTableName, sColumnD, sDest, sPkrq, sPtpch, sColumnS, sSource );
            }
        }

        /*只转换第三方响应码为NULL的记录*/
        strcat( sSql1, " AND dsfxym is NULL " );

        /* added by yangdong 20130609 增加转换范围判断 */
        /* 只转换审核失败明细 
        if( sFlag[0] == '1' ) 
        {
            strcat( sSql1, " AND shzt='0' " );           
        }*/

        iRet = DCIExecuteDirect(sSql1);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            /*sql_RollbackTrans();*/
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_BATCH_RESP_CONV,MSG_BATCH_RESP_CONV );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
            return COMPRET_FAIL;
        }
        LOG(LM_STD,Fmtmsg("update resp[%s][%d]", sSql1, iResult ),"INFO")
    }    
    DCIFreeCursor(cur);
    
    /* add by yr 20120926 */
    /*if( sql_CommitTrans() !=MID_SYS_SUCC )*/
    if(DCICommit() != 0)
    {
        DCIFreeCursor(cur);
        DCIRollback();
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* end */
    
    DCIFreeCursor(cur);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_EXPORT_BREAK
组件名称:BATCH_EXPORT_BREAK
组件功能: 批量业务断点数据导出保存
组件参数:
 序号 参数类型    参数名称                 资源类别         缺省值    可空    参数说明        
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_EXPORT_BREAK(HXMLTREE lXmlhandle)
{
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    DCIBegin();/*add by tuql 20160606 需求单:201606060219 */
    iRet = fprv_export_break( lXmlhandle );
    DCICommit();
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return iRet; 
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_TASK_CANCEL
组件名称:BATCH_TASK_CANCEL
组件功能: 批量业务任务取消
组件参数:
 序号 参数类型  参数名称         资源类别          缺省值           可空  参数说明    
  1   1-输入   业务编号      416XML解析字符串  [/batch/req/ywbh]      N    
  2   2-输入   登记日期      416XML解析字符串  [/batch/req/djrq]      N   
  2   3-输入   登记流水号    416XML解析字符串  [/batch/req/djlsh]     N   
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_TASK_CANCEL(HXMLTREE lXmlhandle)
{
    char sBuf[128+1];
    int  iParas,iFlag;
    int  iRet = -1;
    int  iDjlsh=0;
    char sErrmsg[512];
    char sSql1[1024];
    char sDjrq[8+1];
    char sYwbh[16+1];
    BATCH_WBWJDJ sdb_batch_wbwjdj;
    BATCH_PLRW sdb_batch_plrw;
 
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    
    COMP_PARACOUNTCHK(3)        /* 检查组件参数个数 */
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbh,0,sizeof(sYwbh));
    COMP_GETPARSEPARAS(1, sBuf, "业务编号"); 
    pstrcopy(sYwbh, sBuf, sizeof(sYwbh));
        
    memset(sBuf,0,sizeof(sBuf));
    memset(sDjrq,0,sizeof(sDjrq));
    COMP_GETPARSEPARAS(2, sBuf, "登记日期");
    pstrcopy(sDjrq, sBuf, sizeof(sDjrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "登记流水号");
    iDjlsh=atoi(sBuf);
    
    memset(&sdb_batch_wbwjdj,0,sizeof(sdb_batch_wbwjdj));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT pkrq, ptpch, pczt, lpwjm \
        FROM batch_wbwjdj WHERE djrq='%s' AND djlsh=%d", sDjrq, iDjlsh);
    iRet=DBSelectToMultiVar(sErrmsg,sSql1,sdb_batch_wbwjdj.pkrq,sdb_batch_wbwjdj.ptpch,sdb_batch_wbwjdj.pczt,sdb_batch_wbwjdj.lpwjm);
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("无满足条件的外部文件信息,[%s],[%d],sqlerr[%s]",\
            sDjrq,iDjlsh,DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_NOFUND,MSG_BATCH_WBWJDJ_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                
    }
    trim(sdb_batch_wbwjdj.ptpch);
    trim(sdb_batch_wbwjdj.pczt);
    trim(sdb_batch_wbwjdj.lpwjm);
    COMP_SOFTSETXML(XMLNM_BATCH_PKRQ, sdb_batch_wbwjdj.pkrq)
    COMP_SOFTSETXML(XMLNM_BATCH_PTPCH, sdb_batch_wbwjdj.ptpch)
    LOG(LM_DEBUG,Fmtmsg("BATCH: 获取外部文件信息,pczt[%s]", sdb_batch_wbwjdj.pczt ),"DEBUG");
    memset(sSql1, 0x00, sizeof(sSql1));
    snprintf( sSql1, sizeof( sSql1 ), "SELECT dqbd,fzbd,bdzt,rwzt FROM BATCH_PLRW\
        WHERE pkrq='%s' AND ptpch = '%s'",sdb_batch_wbwjdj.pkrq, sdb_batch_wbwjdj.ptpch );
    iRet=DBSelectToMultiVar( sErrmsg, sSql1,sdb_batch_plrw.dqbd,sdb_batch_plrw.fzbd,sdb_batch_plrw.bdzt,sdb_batch_plrw.rwzt );
    if( iRet < 1 )
    {
        LOG(LM_STD,Fmtmsg("无满足条件的批量任务信息,[%s],sqlerr[%s]",\
                   sdb_batch_wbwjdj.ptpch,DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_NOFUND,\
                           MSG_BATCH_WBWJDJ_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;                
    }
    trim(sdb_batch_plrw.dqbd);
    trim(sdb_batch_plrw.fzbd);
    trim(sdb_batch_plrw.bdzt);
    trim(sdb_batch_plrw.rwzt);
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_DQBD, sdb_batch_plrw.dqbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_FZBD, sdb_batch_plrw.fzbd)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_BDZT, sdb_batch_plrw.bdzt)
    COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_RWZT, sdb_batch_plrw.rwzt)

    switch(sdb_batch_wbwjdj.pczt[0])
    {
        case WBWJDJ_ZT_PRE: /* 正在上传 */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_PRE,Fmtmsg(MSG_BATCH_WBWJDJ_PRE,sdb_batch_wbwjdj.lpwjm));
            break;
        case WBWJDJ_ZT_READY: /* 就绪 */
            sql_BeginTrans();
            snprintf( sSql1, sizeof( sSql1 ),"UPDATE batch_wbwjdj SET pczt = 'X'\
                WHERE djrq='%s' AND djlsh=%d", sDjrq, iDjlsh );
            iRet = DCIExecuteDirect( sSql1 );
            if( iRet < 1 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }

            if( sql_CommitTrans() !=MID_SYS_SUCC )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            iFlag=1;
            break;
        
        /* modified by yangdong 20120424 处理失败允许撤销 */
        case WBWJDJ_ZT_FAIL: /* 处理失败 */
        case WBWJDJ_ZT_RUNNING: /* 正在处理 */
        /* modified by yangdong 20120424 状态判断
        步点为已提交核心成功，或者提交核心，但不是失败状态 不允许撤销
            if( atoi(sdb_batch_plrw.dqbd) < 4 )
        */
            if( atoi(sdb_batch_plrw.dqbd) > 3 ||
                ( atoi(sdb_batch_plrw.dqbd) == 3 && sdb_batch_plrw.bdzt[0] !='0' ) )
            {
                iFlag = -1;
                fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_RUNNING,\
                Fmtmsg(MSG_BATCH_WBWJDJ_RUNNING,sdb_batch_wbwjdj.lpwjm));
                break;        
            }
            iFlag=1;
            COMP_SOFTSETXML(XMLNM_BATCH_PLRW_DQBD,sdb_batch_plrw.dqbd)
            COMP_SOFTSETXML(XMLNM_BATCH_PKRQ,sdb_batch_plrw.pkrq)
            COMP_SOFTSETXML(XMLNM_BATCH_PTPCH,sdb_batch_wbwjdj.ptpch)
            COMP_SOFTSETXML(XMLNM_RESPMSG,"批量任务撤销成功")
            break;
        case WBWJDJ_ZT_SUCC: /* 已返回 */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_SUCC,\
                Fmtmsg(MSG_BATCH_WBWJDJ_SUCC,sdb_batch_wbwjdj.lpwjm));
            break;
        case WBWJDJ_ZT_CX: /* 已撤销 */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_CX,\
                Fmtmsg(MSG_BATCH_WBWJDJ_CX,sdb_batch_wbwjdj.lpwjm));
            break;
        default: /* 其他 */
            iFlag=-1;
            fpub_SetMsg(lXmlhandle,MID_BATCH_WBWJDJ_UNKNOWN,\
                 Fmtmsg(MSG_BATCH_WBWJDJ_UNKNOWN,sdb_batch_wbwjdj.lpwjm));
            break;
    }
    fpub_SetCompStatus(lXmlhandle,iFlag);

    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}
