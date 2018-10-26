/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V4.1.0.1
操作系统:
文件名称:APP_TASK.c
文件描述:任务类处理组件集合
项 目 组:
程 序 员:wuyp@hundsun.com
发布日期:2008年12月01日
修    订:
修改日期: 20110711
          更改日志记录方式
修改日期: 20140915
          DCI改造
*********************************************************************/
#include <math.h>
#include <dlfcn.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>APP_TASK.so</soname>\
        <sosrcname>APP_TASK.c</sosrcname>\
        <sonote>任务组件集合</sonote>\
        <version>\
        <rec ver=\"2.0.1.1\" modify=\"2010-4-1  15:08\" programer=\"Wuyp\" filesize=\"1080632\">HS-AgentV2.0整理</rec>\
        <rec ver=\"2.1.0.1\" modify=\"2011-11-01 10:34\" programer=\"S..C\" filesize=\"1080632\">HS-AgentV2.1改造</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-9-15 10:34\" programer=\"YangDong\" filesize=\"1080632\">DCI改造</rec>\
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

/***********************************************************************
功  能：以XML作为数据源,INSERT 数据库表[app_rwjkb]函数
参  数：
    HXMLTREE lXmlhandle    传入的XML句柄
返回值：
      0    操作成功
     -1    数据库操作失败
     -2    操作拒绝:数据校验失败
     -3    无满足条件的记录(更新时)
     -9    数据库操作失败,提交事务失败
其它信息：
   表中文名称:代理业务当日流水表
   发布时间:2008-12-04 17:09:32 [By GenFromWorkSpace_DB]
   说明信息:
************************************************************************/
int SApp_RecordTASK(HXMLTREE lXmlhandle)
{
    APP_RWJKB sdb_app_rwjkb;
    static struct timeb  timetp;
    char sbuf[255];
    char sSysDate[8+1];
    char sSysTime[6+1];
    int  imillitm=0;
    int iRet = -1;
    char sErrmsg[512];
   
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
   
    memset(&sdb_app_rwjkb,0,sizeof(APP_RWJKB));

    /*应用标识(默认代理业务)*/
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_YYBS,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.yybs,sbuf,sizeof(sdb_app_rwjkb.yybs));
    
    /*应用名称(默认代理业务)*/
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_YYMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.yymc,sbuf,sizeof(sdb_app_rwjkb.yymc));
    
    /* 产品代码 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_CPDM,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.cpdm,sbuf,sizeof(sdb_app_rwjkb.cpdm));
    
    /* 产品名称 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_CPMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.cpmc,sbuf,sizeof(sdb_app_rwjkb.cpmc));
    
    /* 任务名称 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_RWMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.rwmc,sbuf,sizeof(sdb_app_rwjkb.rwmc));
    
    /*交易代码*/
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYDM,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jydm,sbuf,sizeof(sdb_app_rwjkb.jydm));
    
    /*交易名称*/
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jymc,sbuf,sizeof(sdb_app_rwjkb.jymc)); 
   
    /*平台日期*/
    COMP_SOFTGETXML(XMLNM_ZWRQ,sbuf);
    if ( 0 == sbuf[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->操作拒绝:字段[ptrq]为not null,对应的值[/pub/zwrq]为空,请检查!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_TASK_ZWRQ_NULL,MSG_TASK_ZWRQ_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_app_rwjkb.ptrq,sbuf,sizeof(sdb_app_rwjkb.ptrq));
    
    /*平台流水号*/
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sbuf);
    if ( 0 == sbuf[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->操作拒绝:字段[ptls]为not null,对应的值[/pub/zhqzlsh]为空,请检查!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_TASK_PTLS_NULL,MSG_TASK_PTLS_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    sdb_app_rwjkb.ptls = atoi(sbuf);
    
    /*交易机构*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_JYJG,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jyjg,sbuf,sizeof(sdb_app_rwjkb.jyjg));
    
    /*交易柜员*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_JYGY,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jygy,sbuf,sizeof(sdb_app_rwjkb.jygy));
    
    /*渠道标识*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_QDBS,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.qdbs,sbuf,sizeof(sdb_app_rwjkb.qdbs));
   
    /* 交易执行时间 --B*/
    ftime(&timetp);
    memset(sbuf, 0, sizeof(sbuf));
    COMP_SOFTGETXML("/sys/systime_stamp",sbuf)
    if (sbuf[0] !=0 )
    {
        sprintf(sbuf,"%ld",timetp.time*1000+timetp.millitm-atol(sbuf));
        COMP_SOFTSETXML(XMLNM_APP_TRANSTIME,sbuf);
    }
    /* 交易执行时间 --E*/
   
    /*开始时间戳*/
    fprv_gettimeStamp(sSysDate,sSysTime,sbuf);
    pstrcopy(sdb_app_rwjkb.kssj,sbuf,sizeof(sdb_app_rwjkb.kssj));
    
    /*结束时间戳*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_JSSJ,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jssj,sbuf,sizeof(sdb_app_rwjkb.jssj));
    
    /*执行时间*/
    COMP_SOFTGETXML(XMLNM_APP_TRANSTIME,sbuf);
    trim(sbuf);
    sdb_app_rwjkb.yxsj=atoi(sbuf);
   
    /*执行次数*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_ZXCS,sbuf);
    sdb_app_rwjkb.zxcs = atoi(sbuf);
    
    /*交易响应码*/
    COMP_SOFTGETXML(XMLNM_RESPCODE,sbuf);
    pstrcopy(sdb_app_rwjkb.xym, sbuf,sizeof(sdb_app_rwjkb.xym));
     
    /*交易响应码*/
    COMP_SOFTGETXML(XMLNM_RESPMSG,sbuf);
    pstrcopy(sdb_app_rwjkb.xyxx, sbuf,sizeof(sdb_app_rwjkb.xyxx));
      
    /* 执行状态 */
    if ( strcmp(sdb_app_rwjkb.xym, "00000") == 0)
        strcpy(sdb_app_rwjkb.zxzt, "0");
    else
        strcpy(sdb_app_rwjkb.zxzt, "1");
        
    /*扩展1*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_EXTFLD1,sbuf);
    trim(sbuf);
    if ( strlen(sbuf)<=0)
        strcpy(sdb_app_rwjkb.extfld1," ");
    else
        pstrcopy(sdb_app_rwjkb.extfld1,sbuf,sizeof(sdb_app_rwjkb.extfld1));
    
    /*扩展2*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_EXTFLD2,sbuf);
    trim(sbuf);
    if ( strlen(sbuf)<=0)
        strcpy(sdb_app_rwjkb.extfld2," ");
    else
        pstrcopy(sdb_app_rwjkb.extfld2,sbuf,sizeof(sdb_app_rwjkb.extfld2));
           
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    iRet = DBInsert("app_rwjkb", SD_APP_RWJKB, NUMELE(SD_APP_RWJKB), &sdb_app_rwjkb, sErrmsg);
    if ( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->数据库操作失败,[%s]",DCILastError()),"ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_INSERT,MSG_SQL_INSERT );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
   
    /*提交事务*/
    if ( DCICommit() == -1 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->数据库操作失败,[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_INSERT,MSG_SQL_INSERT );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;  
}
