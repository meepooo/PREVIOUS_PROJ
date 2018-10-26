/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.1)
版    本:V4.1.0.1
操作系统:
文件名称:BAT_CTRL.c
文件描述:批量业务处理控制类组件集
程 序 员:chensy YangDong
发布日期:2011-08-01
程 序 员:YangDong
修改日期:20141018
修改说明:DCI改造
 *********************************************************************/
#include <dlfcn.h>
#include "gaps_head.h"
/*#include "DCI.h"*/
#include "batch_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_CTRL.so</soname>\
        <sosrcname>BAT_CTRL.c</sosrcname>\
        <sonote>BATCH流程控制组件集合</sonote>\
        <version>\
        <rec ver=\"2.1.0.1\" modify=\"2011-8-1 15:08\" programer=\"Chensy YangDong\" filesize=\"1266963\">HS-AgentV2.1整理</rec>\
        <rec ver=\"2.1.0.2\" modify=\"2014-10-18 15:08\" programer=\"YangDong\" filesize=\"1266963\">DCI改造</rec>\
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

/***************************************************************************
动态组件函数定义
组件函数名称:SBATCH_TASKCTRL
组件名称:BATCH_TASKCTRL
组件功能:批量业务任务控制 
组件参数:
序号 参数类型  参数名称          资源类别      缺省值     可空       参数说明
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
****************************************************************************/
IRESULT SBATCH_TASKCTRL(HXMLTREE lXmlhandle)
{
    char sBuf[128];
    char sYwbh[16+1];
    char sPkrq[8+1];
    char sSql1[1024];
    char sErrmsg[512];
    int  DB_iTaskRun;
    int  iParas;
    int  iBusiMax = 0 ;
    int  iRunctlMax = 0;
    int iRet = -1;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3);
    
    memset(sBuf,0,sizeof(sBuf));
    memset(sYwbh,0,sizeof(sYwbh));
    COMP_GETPARSEPARAS(1,sBuf,"业务编号");
    if( 0 == sBuf[0] ) 
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_YWBH_NULL,MSG_BATCH_YWBH_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sYwbh,sBuf,sizeof(sYwbh));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"批量应用任务最大总数");
    iBusiMax = atoi( sBuf );
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"本业务编号任务最大总数")
    iRunctlMax = atoi( sBuf );
    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sPkrq); /* 批扣日期 */
    
    /* 校验应用任务总数(控制) */
    DB_iTaskRun=0; 
    if( iBusiMax > 0 )
    {
        LOG(LM_DEBUG,Fmtmsg("批量业务总任务控制[%d]", iBusiMax),"DEBUG");
        memset( sBuf, 0x00, sizeof( sBuf ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_plrw\
        				WHERE   pkrq='%s' AND rwzt = '9'", sPkrq );
        iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
        if( iRet < 0 )        
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        DB_iTaskRun = atoi( sBuf );

        /* added by yangdong 20151202 如果不是任务发起，则需要+1
           因为自动任务或者单步触发的时候，并没有插入任务或者更改任务状态 */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_JYDM,sBuf); 
        trim( sBuf );
        if( strcmp( sBuf,"910002" ) != 0 &&  strcmp ( sBuf, "910020" ) != 0 )
            DB_iTaskRun ++;
        /* end of add */

        if( DB_iTaskRun > iBusiMax )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 批量业务运行任务总数超限,允许任务数[%d],\
            						运行任务数[%d]",iBusiMax,DB_iTaskRun),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_BUSITASKOVER,MSG_BATCH_BUSITASKOVER);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    /* 校验业务编号任务总数 */ 
    DB_iTaskRun=0; 
    if( iRunctlMax > 0 )
    {
        LOG(LM_DEBUG,Fmtmsg("批量业务业务[%s]任务控制[%d]", sYwbh, iRunctlMax ),"DEBUG");

        memset( sBuf, 0x00, sizeof( sBuf ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT count(*) FROM batch_plrw\
        				WHERE  ywbh='%s' AND pkrq='%s' AND rwzt = '9' ", sYwbh, sPkrq );
        iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
        if( iRet < 0 )        
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        DB_iTaskRun = atoi( sBuf );

        /* added by yangdong 20151202 如果不是任务发起，则需要 +1
           因为自动任务或者单步触发的时候，并没有插入任务或者更改任务状态 */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_REQ_JYDM,sBuf); 
        trim( sBuf );

        if( strcmp( sBuf,"910002" ) != 0 &&  strcmp ( sBuf, "910020" ) != 0 )
            DB_iTaskRun ++;
        /* end of add */

        if( DB_iTaskRun > iRunctlMax )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 批量任务总数超限,\
            						允许数[%d],运行数[%d]",iRunctlMax,DB_iTaskRun),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_PRODUCTTASKOVER,\
            						Fmtmsg(MSG_BATCH_PRODUCTTASKOVER,sYwbh));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/* 释放链表资源 */
void prv_FlowListFree()
{                         
    if( t_flowList )
    {
        i_list_delete(&t_flowList);
    }
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_RUNCTRL
组件名称:BATCH_RUNCTRL
组件功能: 批量业务流程执行总控
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
1   1-输入   流程标识       416-解析字符串            Y    流程标识 
使用限制:
优化处理,总控一开始即把流程步点导入内存链表处理,这样外部休眠
不会影响的数据库游标资源(使用双向链表处理),需要外部
设置中断或退出处理流程循环
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_RUNCTRL(HXMLTREE lXmlhandle)
{
    int iStepCount,iFlag=0,iAttribCount,jflag;
    int iParas;
    char sXmlNode[128];
    char sStepFlow[128];
    char sAttribvalue[128];
    char sBuf[128];
    int  iBdcgbz,ret;
    char flowStatus[11];
    char sStepSN[2];
    char sStepNM[8];
    char sFlowID[51];
    char DB_sStepID[51];
    char sErrmsg[512];
    char sSql1[1024];
    CURSOR cur;
    int  iClcs;         /* 步点处理次数 */
    BATCH_STEPCFG sdb_batch_stepcfg;
    int iRet = -1;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1);
    memset(sBuf,0,sizeof(sBuf));
    memset(sFlowID,0,sizeof(sFlowID));
    COMP_GETPARSEPARAS(1,sBuf,"流程标识");
    pstrcopy(sFlowID,sBuf,sizeof(sFlowID));
    
    /* 初始化流程到流程链表 */
    trim(sFlowID);
    iStepCount=fprv_initBatchFlow(lXmlhandle, sFlowID, &t_flowList);
    if( iStepCount <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:无对应流程[%s]配置信息",sFlowID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,\
            MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /* 流程步点循环处理开始 */
    for( pflowIter = i_list_begin(t_flowList); 
        pflowIter!= i_list_end(t_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {
        
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        /* modified by guoliang 20130506 */
        strncpy(DB_sStepID, pFlowcfg->stepid, sizeof(DB_sStepID)-1);
        /* end */                
        memset(sStepNM, 0, sizeof(sStepNM));
        
        /* 设置流程配置全局节点    */
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWID,pFlowcfg->flowid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWNAME,pFlowcfg->flowname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWSN,itoa(pFlowcfg->flowsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPID,DB_sStepID);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD1,pFlowcfg->extfld1);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD2,pFlowcfg->extfld2);
        
        /*add by tuql 20150521 支持集群和任务嵌套  BEGIN*/
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPSN,itoa(pFlowcfg->stepsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPNAME,pFlowcfg->stepname);
        /*add by tuql 20150521 支持集群和任务嵌套  BEGIN*/
        ret = fprv_enumStepID(pFlowcfg->stepid, sStepNM);
        if( ret != 0 )
        {
            prv_FlowListFree();
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL); 
            return COMPRET_FAIL;
        }
        
        LOG(LM_STD,Fmtmsg("BATCH: 批量运行总控-流程[%s],步点标识[%s],步点序号[%s],步点名称[%s]始",\
            sFlowID,DB_sStepID, itoa(pFlowcfg->flowsn) , sStepNM),"INFO");
        COMP_SOFTSETXML(XMLNM_BATCH_STEPSN,itoa(pFlowcfg->flowsn) );
        COMP_SOFTSETXML(XMLNM_BATCH_STEPID,DB_sStepID );
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_stepcfg WHERE \
            flowid='%s' AND stepid='%s'", sFlowID, DB_sStepID );
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            prv_FlowListFree();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            prv_FlowListFree();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        
        /* 获取流程步点属性  */
        for ( iAttribCount=0, jflag=0 ; ;iAttribCount++)
        {
            memset(&sdb_batch_stepcfg,0,sizeof(sdb_batch_stepcfg));
            if( ( iRet = DBFetch(cur, SD_BATCH_STEPCFG, NUMELE(SD_BATCH_STEPCFG), &sdb_batch_stepcfg, sErrmsg ) ) <= 0 )
            {
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 获取流程步点属性处理失败,[%s]", DCILastError() ),"ERROR");
                    jflag = -1;
                }
                break;
            }
        
            memset(sXmlNode,0,sizeof(sXmlNode));
            trim(DB_sStepID);
            trim(sdb_batch_stepcfg.attribid);
            trim(sdb_batch_stepcfg.attribvalue );
            snprintf(sXmlNode,sizeof( sXmlNode ),\
                "/batch/%s/%s",DB_sStepID,sdb_batch_stepcfg.attribid);
            
            /* added by yangdong 20121316  增加属性对xml节点支持 */
            /* modified by yangdong 20130618 sdb_batch_stepcfg.attribvalue 可能无法存放解析后字符串长度 
            if(xml_ParseXMLString(lXmlhandle,sdb_batch_stepcfg.attribvalue,sizeof(sdb_batch_stepcfg.attribvalue))==FAIL)
             */
            memset( sAttribvalue ,0,sizeof( sAttribvalue ));
            strcpy( sAttribvalue, sdb_batch_stepcfg.attribvalue );
            if(xml_ParseXMLString(lXmlhandle, sAttribvalue, sizeof( sAttribvalue ))==FAIL)
            {
                LOG(LM_STD,Fmtmsg("BATCH: 获取流程步点属性处理失败,[%s]", sAttribvalue ),"ERROR");
                jflag = -2 ;
                break;
            }
            
            COMP_SOFTSETXML(sXmlNode, sAttribvalue );
            LOG(LM_DEBUG,Fmtmsg("  -->单步总控处理属性[%s][%s], val[%s]", sXmlNode, sdb_batch_stepcfg.attribid, sAttribvalue ),"DEBUG");
            /* end of mod 20130618 */
        }
        DCIFreeCursor(cur);
        LOG(LM_DEBUG,Fmtmsg("处理属性数[%d], flowid[%s], stepid[%s]",\
            iAttribCount,sFlowID,DB_sStepID),"DEBUG");
        if(jflag < 0) 
        {
            prv_FlowListFree();
            LOG(LM_STD,Fmtmsg("BATCH: 获取流程步点属性处理失败,[%d]",jflag),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        /* 调用单个步点流程处理 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        memset(sStepFlow,0,sizeof(sStepFlow));
        snprintf(sXmlNode,sizeof( sXmlNode ),\
            "/batch/%s/%s",DB_sStepID,BATCH_ATTRIBUTE_CLLCM);
        COMP_SOFTGETXML(sXmlNode,sStepFlow);
        
        LOG(LM_STD,Fmtmsg("调用[%s]步点,[%s]流程开始<--",DB_sStepID,sStepFlow),"INFO");
        trim(sStepFlow);
        if( fpub_CallFlow(lXmlhandle,sStepFlow) != MID_SYS_SUCC)
        {
            iFlag=-2 ;
            COMP_SOFTGETXML(XMLNM_RESPCODE,flowStatus);
            LOG(LM_STD,Fmtmsg("BATCH: 调用[%s]流程失败,返回状态[%s]",\
                sStepFlow,flowStatus),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,\
                Fmtmsg(MSG_BATCH_EXEC_FLOW,sStepFlow));
            break;
        }
        
        memset(sBuf,0,sizeof(sBuf));
        /* 外部必须赋值 0成功、1失败、2返回 */
        COMP_SOFTGETXML(XMLNM_BATCH_BDCGBZ,sBuf);
        LOG(LM_STD,Fmtmsg("<<<<<<调用[%s]步点,[%s]流程结束[%s]>>>>>>",DB_sStepID,sStepFlow, sBuf),"INFO");
        iBdcgbz=atoi(sBuf);
        ret=fprv_isZero(sBuf);
        if( ret == 0 )
        {
            continue;        
        }
        else if( iBdcgbz == 1 ) /* 处理失败 */
        {    
            iFlag=-2 ;
            break;
        }
        else if( iBdcgbz == 2 ) /* 返回处理 - 结束循环*/
        {
            iFlag=1;        
            break;
        }
        /* by yr 20120927 */
        else if( iBdcgbz == 3 ) /* 等待处理 - 结束循环*/
        {
            iFlag=1;        
            break;
        }
        /* end */
        else
        {
            LOG(LM_STD,Fmtmsg("BATCH: 步点成功标志非法[%s]",sBuf),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);        
            fpub_SetMsg(lXmlhandle,MID_BATCH_BDCGBZ_FF,Fmtmsg(MSG_BATCH_BDCGBZ_FF,sBuf));
            iFlag = -1;
            break;
        }
    }
    prv_FlowListFree();
    LOG(LM_STD,Fmtmsg("BATCH: 批量运行总控-流程[%s],处理步点数[%d]--结束",sFlowID,iStepCount),"INFO");
    if(iFlag < 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/* 释放链表资源 */
void prv_StepListFree()
{                   
    if( t_step_flowList )
    {
        i_list_delete(&t_step_flowList);
    }
}
/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_STEPCTRL
组件名称:BATCH_STEPCTRL
组件功能: 批量业务步点触发控制
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
1   1-输入   流程标识              416XML解析字符串     *         N     
2   1-输入   当前操作步点          416XML解析字符串     *         N   
3   1-输入   是否为断点            416XML解析字符串     *         N     
4   1-输入   执行后续步点标志      416XML解析字符串     *         N   
输出：  
0   成功
-1  失败
-2  可以重复执行
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_STEPCTRL(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    int  iSetpCount,iflag=0,iAttribCount;
    int  iParas,iStepFlag=0;
    char sXmlNode[128];
    char sStepFlow[128];
    char sBuf[255];
    char sAttribvalue[128];
    char sCurrentStep[51];
    int  iBreakPoint,iNextFlag,iBdcgbz,iRet;
    char flowStatus[10+1];
    char sStepSN[1+1];
    char sStepNM[16+1];
    int  iCurStep;
    char sStepNum[1+1];
    char sNextStepID[100];
    char sFlowID[51];
    char DB_sStepID[51];
    char sBdzt[1+1];    /* 步点状态 */
    char sRwzt[1+1];    /* 任务状态 */
    char sSql1[1024];
    char sErrmsg[512];
    CURSOR cur;
    BATCH_STEPCFG sdb_batch_stepcfg;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(4);
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"流程标识");
    pstrcopy(sFlowID,sBuf,sizeof(sFlowID));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"当前操作步点")
    pstrcopy(sStepSN,sBuf,sizeof(sStepSN));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"是否是断点") /* 1 断点 2其他 */
    iBreakPoint=atoi(sBuf);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(4,sBuf,"执行后续步点标志") /*(0执行，1不执行)*/
    iNextFlag=atoi(sBuf);
    
    memset(sCurrentStep, 0, sizeof(sCurrentStep));
    memset(sStepNM, 0, sizeof(sStepNM));
    
    /* 枚举步点信息 */
    fprv_enumStepSN(sStepSN,sCurrentStep,sStepNM);
    iCurStep = atoi(sStepSN);
    trim(sFlowID);
    
    /* 初始化流程到流程链表 --B*/
    iSetpCount=fprv_initStepFlow(sFlowID,&t_step_flowList,iCurStep );
    if ( iSetpCount <=0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 初始化流程到流程链表 --E*/
    
    /*  调用前赋值 0 成功，避免空流程，成功标志未赋值情况  */
    COMP_SOFTSETXML( XMLNM_BATCH_BDCGBZ,"0" );

    /* 流程步点循环处理开始 --B*/
    for( pflowIter = i_list_begin(t_step_flowList); 
        pflowIter!= i_list_end(t_step_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        /* modified by guoliang 20130506 */
        strncpy(DB_sStepID, pFlowcfg->stepid, sizeof(DB_sStepID)-1);
        /* end */
        trim(DB_sStepID);
        if ( iStepFlag == 0)
        {
            /*  查找需要运行的步点 */
            if ( 0 != memcmp(sCurrentStep,DB_sStepID,strlen(sCurrentStep) ) )
            {
                continue; 
            }
            iStepFlag=1; 
            
            /* 判断是否已触发断点,返回,失败,等待的任务 */
            memset( sBdzt, 0, sizeof( sBdzt ));
            memset( sRwzt, 0, sizeof( sRwzt ));
            
            iRet = prv_Proc( lXmlhandle, sCurrentStep, iBreakPoint,sBdzt, sRwzt );
            if( iRet<0 )
            {
                prv_StepListFree();
                return COMPSTATUS_FAIL;
            }
            
            /* 断点和返回 */
            if ( iBreakPoint == 1 ) 
            {
                /* modify by yr 20120827  */    
                /* 此步点状态为返回,则处理下一个步点 */
                if( sBdzt[0] == '3'  ||  sRwzt[0] == '3' )
                    continue;
                
                /* 获取报文中请求的处理时间 */
                iRet=fprv_enumNextStepID( sFlowID, sCurrentStep, "",sNextStepID);
                if( iRet != 0 )
                {
                    prv_StepListFree();
                    fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return -2;
                }
                
                /* 此处步点状态为断点,如果在处理时间内则从下一个步点开始执行,如果不是就退出 */
                iRet=prv_clsj( lXmlhandle, sNextStepID );
                if ( iRet<0 )
                { 
                    /* 步点状态 */
                    prv_StepListFree();
                    return COMPSTATUS_FAIL;
                }
                /* end */  
                continue;
            }
            /* add by yr 20120925  失败,等待 */
            if ( iBreakPoint==2 )
            {
                /* 此步点状态为等待,则判断开始处理时间继续执行此步点 */
                if( sBdzt[0] == '4'  ||  sRwzt[0] == '9' )
                { 
                    iRet=prv_clsj( lXmlhandle, sCurrentStep );
                    if ( iRet<0 )
                    { 
                        prv_StepListFree();
                        return COMPSTATUS_FAIL;
                    }
                    COMP_SOFTSETXML( "/batch/req/sjtjflag","1"); 
                }
                /* 单步操作，则直接开始重复运行该步点 */
            }
            /* end */
        }
        
        memset(sStepNM, 0, sizeof(sStepNM));
        memset(sStepSN, 0, sizeof(sStepSN));
        
        /* 设置流程配置全局节点  --B*/
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWID,pFlowcfg->flowid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWNAME,pFlowcfg->flowname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWSN,itoa(pFlowcfg->flowsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPID,DB_sStepID);
        fprv_enumStepID(pFlowcfg->stepid, sStepNM);
        
        LOG(LM_STD,Fmtmsg("STEP: 单步运行总控-流程[%s],步点标识[%s],步点名称[%s]--开始",\
            sFlowID,DB_sStepID,sStepNM),"INFO");
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPSN,sStepSN);
        COMP_SOFTSETXML(XMLNM_BATCH_STEPSN,sStepSN);
        COMP_SOFTSETXML(XMLNM_BATCH_STEPID,DB_sStepID);
        
        /* 获取流程步点属性 --B */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_stepcfg \
            WHERE flowid='%s' AND stepid='%s'", sFlowID, DB_sStepID );
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            prv_StepListFree();
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        if (DCIExecute(cur) == -1)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
            DCIFreeCursor(cur);
            prv_StepListFree();
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            return COMPRET_FAIL;
        }
        
        for (iAttribCount=0; ;iAttribCount++)
        {
            memset(&sdb_batch_stepcfg,0,sizeof(sdb_batch_stepcfg));
            if( ( iRet = DBFetch(cur, SD_BATCH_STEPCFG, NUMELE(SD_BATCH_STEPCFG), &sdb_batch_stepcfg, sErrmsg ) ) < 0 )
            { 
                prv_StepListFree();
                fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if ( iRet == 0 )
                	break;
            
            memset(sXmlNode,0,sizeof(sXmlNode));
            trim(DB_sStepID);
            trim(sdb_batch_stepcfg.attribid);
            sprintf(sXmlNode,"/batch/%s/%s",DB_sStepID,sdb_batch_stepcfg.attribid);
            
            /* added by yangdong 20121316  增加属性对xml节点支持 */
            /* modified by yangdong 20130618 sdb_batch_stepcfg.attribvalue 可能无法存放解析后字符串长度 
            	 if(xml_ParseXMLString(lXmlhandle,sdb_batch_stepcfg.attribvalue,sizeof(sdb_batch_stepcfg.attribvalue))==FAIL)
             */
            memset( sAttribvalue ,0,sizeof( sAttribvalue ));
            strcpy( sAttribvalue, sdb_batch_stepcfg.attribvalue );
            if(xml_ParseXMLString(lXmlhandle, sAttribvalue, sizeof( sAttribvalue ))==FAIL)
            { 
                prv_StepListFree();
                fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            
            COMP_SOFTSETXML(sXmlNode, sAttribvalue );
            LOG(LM_DEBUG,Fmtmsg("  -->单步总控处理属性[%s][%s], val[%s]", sXmlNode, sdb_batch_stepcfg.attribid, sAttribvalue ),"DEBUG");
            /* end of mod 20130618 */
        }
        DCIFreeCursor(cur);
        
        LOG(LM_STD,Fmtmsg("  -->单步总控处理属性数[%d], flowid[%s], stepid[%s]",\
            iAttribCount,sFlowID,DB_sStepID),"INFO");
        
        memset(sXmlNode,0,sizeof(sXmlNode));
        trim(DB_sStepID);
        sprintf(sXmlNode,"/batch/%s/%s",DB_sStepID,BATCH_ATTRIBUTE_CLLCM);
        memset(sStepFlow,0,sizeof(sStepFlow));
        COMP_SOFTGETXML(sXmlNode,sStepFlow);
        /* 默认流程 */
        if ( 0 == sStepFlow[0])
        {
            sprintf(sStepFlow,"flow_batch_step_%s",DB_sStepID);      
        }
        
        LOG(LM_STD,Fmtmsg("   -->单步调用[%s]步点,[%s]流程开始<--     ",DB_sStepID,sStepFlow),"INFO")
        
        /* 调用单个步点流程处理 --B*/
        trim(sStepFlow);
        if(fpub_CallFlow(lXmlhandle,sStepFlow)!=MID_SYS_SUCC)
        {
            prv_StepListFree();
            LOG(LM_STD,Fmtmsg("BATCH: 调用[%s]流程失败",sStepFlow ),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,Fmtmsg(MSG_BATCH_EXEC_FLOW,sStepFlow));
            return COMPRET_FAIL ;
        }
        LOG(LM_STD,Fmtmsg("<<<<<<单步调用[%s]步点,[%s]流程结束>>>>>>",DB_sStepID,sStepFlow),"INFO");
        
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_BDCGBZ,sBuf); /*0成功、1失败、2返回*/
        iBdcgbz=atoi(sBuf);
        iRet=fprv_isZero(sBuf);
        if ( iRet == 0 )
        {
            if ( iNextFlag == 1) 
            {
                /*  不执行下一步 */
                break;    
            }
            continue;    
        }
        else if ( iBdcgbz == 1 )
        {  
            /* 步点成功标志： 失败 */
            iflag=-2 ;
            break;
        }
        else if ( iBdcgbz == 2 )
        {
            /* 步点成功标志： 返回  */
            iflag=1;    
            break;
        }
        /* by yr 20120927 */
        else if( iBdcgbz == 3 ) /* 等待处理 - 结束循环*/
        {
            iflag=1;        
            break;
        }
        /* end */
        else
        {
            iflag = -3;
            LOG(LM_STD,Fmtmsg("BATCH: 步点成功标志非法[%s]",sBuf),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_BDCGBZ_FF,Fmtmsg(MSG_BATCH_BDCGBZ_FF,sBuf));
        }
    } /* 流程循环结束 */
    prv_StepListFree();
    LOG(LM_STD,Fmtmsg("BATCH: 批量运行总控-流程[%s],处理步点数[%d]--结束",sFlowID,iSetpCount),"INFO");
    if (iflag < 0) 
    {
        LOG(LM_STD,Fmtmsg("  -->流程[%s],步点[%s]执行失败,[%d]",sFlowID,DB_sStepID,iBdcgbz),"ERROR");
        return COMPRET_FAIL;
    }           
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_BREAK_CTRL
组件名称:BATCH_BREAK_CTRL
组件功能: 批量业务断点设置
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
1    1-输入   步点响应码  416XML解析字符串           N
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_BREAK_CTRL(HXMLTREE lXmlhandle)
{
    char    sStepID[21];
    char    sStepSN[2];
    char    sStepStatus[2];
    char    sTaskStatus[2];
    char  sBreak[1+1];
    char  sBuf[256];
    char  xmlNode[256]; 
    int   i,iParas;
    int   ret;
    int   iDDFlag = -1;     /* 断点标志 */
    int   /*iDdsj_ms=0,*/ iDdsj=0;
    char  sNextStepID[100];
    char  sAstStep[2+1];
    char  sFinalStep[100];
    char  sKsclsj[6+1];
    char  sFlowSn[2+1];
    char sFlowID[51];
    /*int   iAuto=60;    自动轮训间隔时间 60 为单位 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")

    /* 步点是否成功标识 --B*/
#if 0
    不在判断步点成功标志,SBATCH_BREAK_CTRL只在成功流程中
    COMP_HARDGETXML( XMLNM_RESPCODE, sBuf );
    pstrcopy(respCode,sBuf,sizeof(respCode));
    ret=fprv_isZero(respCode);
    if ( ret != 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
#endif
        return COMPRET_FAIL;  
    }
#endif

    /* 获取当前步点断点属性 */
    memset(sBreak, 0, sizeof(sBreak));
    memset(sStepID, 0, sizeof(sStepID));
    COMP_HARDGETXML(XMLNM_BATCH_FLOWCFG_STEPID ,sStepID);
    trim(sStepID);
    if ( strlen(sStepID) <=0 )
    {
        LOG(LM_STD, Fmtmsg("获取步点属性: 当前步点不存在[%s]=[%s]",\
            XMLNM_BATCH_FLOWCFG_STEPID,sStepID), "ERROR");
        return COMPRET_FAIL;
    }
    memset(sFlowSn, 0, sizeof(sFlowSn));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_FLOWCFG_FLOWSN , sBuf);
    pstrcopy(sFlowSn, sBuf, sizeof(sFlowSn));
    /* added by yangdong 20121115 获取当前流程标识，用于获取下一步点 */
    memset(sFlowID, 0, sizeof(sFlowID));
    COMP_HARDGETXML(XMLNM_BATCH_RUNCTRL_FLOWID,sFlowID);
    trim(sFlowID);
    
    memset(xmlNode, 0, sizeof(xmlNode));
    snprintf(xmlNode, sizeof(xmlNode), "/batch/%s/%s",\
        sStepID, BATCH_ATTRIBUTE_DDBZ );
    COMP_SOFTGETXML(xmlNode,sBuf);
    trim( sBuf );
    snprintf( sBreak, sizeof( sBreak ), "%s", sBuf );

/*
          任务    步点   成功标志
    断点：3返回   2断点  2返回
    返回：3返回   3返回  2返回
    其他：9处理   1结束  0成功
*/    
    if ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK ) /* 断点 */
    {
        /* 任务状态 */
        strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RETURN );
        /* 步点状态 */
        strcpy( sStepStatus, BATCH_STEP_STATUS_S_BREAK );
        /* modified by yangdong 20121105 设置状态为返回，断点由自动任务触发 */
        /* 
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
         */
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_RETURN);
    }
    else if ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_RETURN ) /* 返回 */
    {
        /* 任务状态 */
        strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RETURN );
        /* 步点状态 */
        strcpy( sStepStatus, BATCH_STEP_STATUS_S_RETURN );
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_RETURN);
    }
    /* 默认属性-无断点 */
    else
    {
        /* 任务状态 */
        strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RUNNING );
        /* 步点状态 */
        strcpy( sStepStatus, BATCH_STEP_STATUS_S_END );
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
    }

    /*  步点名，步点id转换  */
    ret = fprv_enumStepNum( sStepID, sStepSN );
    if( ret != 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* added by yangdong 20121115 获取下一步点 */
    /* 判断是否最后一个步点 */
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_FINAL_STEP, sBuf );
    pstrcopy(sFinalStep,sBuf,sizeof(sFinalStep));
    trim( sFinalStep );

    if( strcmp( sStepID , sFinalStep ) != 0 )  /* 当前步点不是最后一个步点 */
    {
        /* 获取下一个步点 */
        memset(sNextStepID, 0x00, sizeof(sNextStepID));
        ret=fprv_enumNextStepID( sFlowID, sStepID, sFlowSn, sNextStepID);
        if( ret != 0 )
        {
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -2;
        }
      
        /* 数据提交步点的特殊处理 */
        /* 如果请求交易上送数据提交时间，以上送时间时间为准，否则查询步点属性，否则判断日间夜间属性*/
        if( strcmp( sNextStepID , BATCH_STEPNM_SJTJ ) == 0 )
        {
            /* 获取报文中请求的处理时间 */
            COMP_SOFTGETXML( XMLNM_BATCH_SJTJ_TIME, sBuf );
            trim( sBuf );
            if( strlen( sBuf ) == 6 ) /* 判断是否合法的数据提交处理时间 */
            {
                pstrcopy(sKsclsj,sBuf,sizeof(sKsclsj));
                iDDFlag = 1;
            }
            else                      /* 判断是否夜间批量 */
            {
                /* 取交易方式 */
                COMP_SOFTGETXML( XMLNM_APP_CPXX_JYFS, sBuf );
                trim( sBuf );
                if( sBuf[0] == '4' || sBuf[0] == '7' ) /* 交易方式: 4-夜间批量  7-联机及夜间批量 */
                {
                    /* 获取夜间批量处理时间 */
                    COMP_SOFTGETXML( XMLNM_BATCH_NIGHT_TIME, sBuf );
                    trim( sBuf );
                    if( strlen( sBuf ) == 6 ) /* 判断是否合法的数据提交处理时间 */
                    {
                        pstrcopy(sKsclsj,sBuf,sizeof(sKsclsj));
                        iDDFlag = 1;
                    }else
                    {
                        /* 获取夜间批量处理时间 */
                        COMP_SOFTGETXML( "/batch/sjtj/ksclsj", sBuf );
                        trim( sBuf );
                        if( strlen( sBuf ) == 6 ) /* 判断是否合法的数据提交处理时间 */
                        {
                            pstrcopy(sKsclsj,sBuf,sizeof(sKsclsj));
                            iDDFlag = 1;
                        }
                    }
                }
            }
            if( iDDFlag == 1 )
            {
                /* 强制设置断点标志 */
                sBreak[0] = BATCH_ATTRIBUTE_DDBZ_BREAK ;
                /* 任务状态 */
                strcpy( sTaskStatus, BATCH_TASK_STATUS_S_RETURN );
                /* 步点状态 */
                strcpy( sStepStatus, BATCH_STEP_STATUS_S_BREAK );
                COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_RETURN);
            }
        }
        if( ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK ) && ( iDDFlag != 1 ) ) /* 断点处理 */
        {
            /* add by yr 20120921 取开始处理时间 */
            /* 取断点时间 */
            memset(xmlNode, 0, sizeof(xmlNode));
            snprintf(xmlNode, sizeof(xmlNode), "/batch/%s/ddsj",sStepID );
            COMP_SOFTGETXML(xmlNode,sBuf);
            trim( sBuf );
            iDdsj= atoi( sBuf );
            /* 断点时间不能大于系统最长断点时间，默认24小时86400秒 */
            if( iDdsj > BATCH_MAX_BREAK_SECONDS )
                iDdsj = BATCH_MAX_BREAK_SECONDS;
            
            memset( sKsclsj, 0x00, sizeof( sKsclsj ) );
            prv_GetKsclsj( lXmlhandle, sNextStepID, iDdsj, sKsclsj );
        }
    }
    /*mod by tuql 20160606 begin
     * 需求单:201606060219
     */
    DCIBegin();
    memset(sAstStep, 0x00, sizeof(sAstStep));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sAstStep)
    if ( strcmp(sAstStep, BATCH_STEP_ASTSTEP_WRET) == 0 ||
         strcmp(sAstStep, BATCH_STEP_ASTSTEP_RETURN) == 0 
        )
    {/*任务嵌套--待返回*/
        /* 已在流程更新步点 */
    }else
    {/*其他情况需更新*/
        if( fprv_batch_upd_plrw( lXmlhandle, sStepSN, sAstStep, sStepStatus, sTaskStatus, sBreak, sKsclsj ) != 0 )
        {
            DCIRollback();/*add by tuql 20160606 需求单:201606060219 */
            return COMPSTATUS_FAIL;
        }
    }

    if( fprv_batch_upd_plrwbd( lXmlhandle, sStepStatus, sStepSN ) != 0 )
    {
        DCIRollback();/*add by tuql 20160606 需求单:201606060219 */
        return COMPSTATUS_FAIL;
    } 

    /* 不管是否断点，保存当前节点信息 */
    if( fprv_export_break( lXmlhandle ) != 0 )
    {
        DCIRollback();/*add by tuql 20160606 需求单:201606060219 */
        return COMPSTATUS_FAIL;
    }
    DCICommit();/*add by tuql 20160606 需求单:201606060219 */
    if( ( sBreak[0] == BATCH_ATTRIBUTE_DDBZ_BREAK ) && ( iDDFlag != 1 ) ) /* 断点处理 */
    {       
        /* modified by yangd 20121105 断点时间小于自动任务轮训时间，直接处理 */
        if ( iDdsj <= BATCH_MIN_BREAK_AUTO )
        {
            sleep( iDdsj );
            ret = prv_BreakProc( lXmlhandle, sStepID  );
            if( ret < 0 )  /* 操作失败 或已触发断点 */
            {
                return COMPSTATUS_FAIL;
            }
            
            strcpy( sStepStatus, BATCH_STEP_STATUS_S_END );
            COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
            
            DCIBegin();/*add by tuql 20160606 需求单:201606060219 */
            if( fprv_batch_upd_plrw( lXmlhandle, sStepSN, sAstStep, sStepStatus, sTaskStatus, sBreak, sKsclsj ) != 0 )
            {
                DCIRollback();/*add by tuql 20160606 需求单:201606060219 */
                return COMPSTATUS_FAIL;
            }
            if( fprv_batch_upd_plrwbd2( lXmlhandle, sStepStatus, sStepSN ) != 0 )
            {
                DCIRollback();/*add by tuql 20160606 需求单:201606060219 */
                return COMPSTATUS_FAIL;
            }
            DCICommit();/*add by tuql 20160606 需求单:201606060219 */
        }
    }
    
    fpub_SetCompStatus(lXmlhandle, COMPRET_SUCC );

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return COMPRET_SUCC;  
}

/* 释放链表资源 */
void batch_auditinglistFree()
{                        
    if( t_auditingList )
    {
        i_list_delete(&t_auditingList);
    }
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_CHECKRULES
组件名称:BATCH_CHECKRULES
组件功能: 批量业务校验规则控制
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_CHECKRULES(HXMLTREE lXmlhandle)
{
    char sBuf[256+1],sShbs[50+1],sFlowname[128],sPath[128+1];
    int iRet,i,iFlag;
    int iAudiCount=0;
    IRESULT (*func)(HXMLTREE);
    void *dhl=NULL;
    char sFuncID[50+1];    
    char sFuncname[50+1],sDllname[32+1]; 
    char sSql1[1024];
    char sErrmsg[512];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");

    memset(sFuncname,0,sizeof(sFuncname));
    memset(sDllname,0,sizeof(sDllname));
    memset(sShbs,0,sizeof(sShbs));
    memset(sPath,0,sizeof(sPath));
    memset(sFlowname,0,sizeof(sFlowname));
    
    /* 取步点审核标识属性 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_BATCH_SJSH_SHBS, sBuf );
    trim(sBuf);
    pstrcopy(sShbs,sBuf,sizeof(sShbs));
    
    /* 不需要审核 */
    if( strlen(sShbs) <= 1 )
    {
        LOG(LM_STD, Fmtmsg("BATCH: 数据审核->该业务不需要审核[%s]\n",sShbs),"INFO");
        /* 设置成功标识 */
        fpub_SetMsg(lXmlhandle,MID_SYS_SUCC,MSG_SYS_SUCC);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)), "DEBUG");
#endif
        return COMPRET_SUCC;
    }

    /* 初始化审核配置表到配置链表 */
    trim(sShbs);
    iAudiCount=fprv_initAuditingfunc(sShbs,&t_auditingList);
    if( iAudiCount <=0 )
    {
        LOG(LM_STD, Fmtmsg("BATCH: 数据审核->审核函数不存在"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_AUDITING_NOFUND,\
            Fmtmsg(MSG_BATCH_AUDITING_NOFUND,sShbs));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 审核配置循环处理开始 */
    for( pauditingIter = i_list_begin(t_auditingList); 
        pauditingIter!= i_list_end(t_auditingList); 
        pauditingIter = i_list_iter_next(pauditingIter) )
    {
        
        pAuditingFunc = (BATCH_AUDITINGFUNC *)(pauditingIter->data); 
        trim(pAuditingFunc->funcid);
        trim(pAuditingFunc->auditingid);
        trim(pAuditingFunc->snote);
        
        memset(sFuncID, 0, sizeof(sFuncID));
        strncpy(sFuncID, pAuditingFunc->funcid, sizeof(sFuncID)-1);
        /* 设置数据节点  */
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_AUDIID,pAuditingFunc->auditingid);
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_AUDISN,itoa(pAuditingFunc->auditingsn));
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_FUNCID,pAuditingFunc->funcid);
        COMP_HARDSETXML(XMLNM_BATCH_AUDITING_SHSBBZ,pAuditingFunc->shsbbz);
        
        LOG(LM_DEBUG,Fmtmsg("BATCH: 数据审核校验函数ID[%s]",pAuditingFunc->funcid),"DEBUG");
        
        /* 获取校验函数注册 */
        snprintf( sSql1, sizeof( sSql1 ) , "SELECT funcrun,funcfile FROM BATCH_AUDITINGREG WHERE funcid='%s'", sFuncID );
        iRet = DBSelectToMultiVar( sErrmsg, sSql1, sFuncname, sDllname) ;
        if( iRet < 1 )
        {
            batch_auditinglistFree();
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_AUDITINGREG_NOFUND,\
                Fmtmsg(MSG_BATCH_AUDITINGREG_NOFUND,sFuncID));
            LOG(LM_STD,Fmtmsg("BATCH: 数据审核函数未找到[%s],请先登记!!!",\
                sFuncID),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        
        trim(sDllname);
        trim(sFuncname);
        memset(sPath, 0, sizeof(sPath));
        snprintf(sPath,sizeof(sPath), "%s/shlib/%s",getenv("HOME"),sDllname);
        LOG(LM_DEBUG,Fmtmsg("BATCH: 数据审核动态链接库[%s]",sPath),"DEBUG");
        dhl = dlopen(sPath, RTLD_LAZY);
        if( dhl== NULL)
        {
            batch_auditinglistFree();
            fpub_SetMsg(lXmlhandle,MID_BATCH_SO_OPEN,MSG_BATCH_SO_OPEN);
            LOG(LM_STD,Fmtmsg("BATCH: 数据审核打开动态链接库[%s]失败",\
                sDllname),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_DEBUG,Fmtmsg("BATCH:    数据审核函数[%s]",sFuncname),"DEBUG");
        func = (IRESULT(*)(HXMLTREE))dlsym(dhl,sFuncname);
        if(func == NULL )
        {
            batch_auditinglistFree();
            dlclose(dhl);
            if( dlerror() )
            {
                LOG(LM_STD,Fmtmsg("BATCH:关闭动态链接库[%s][%s]",\
                    sDllname,dlerror()),"ERROR")
            }
            fpub_SetMsg(lXmlhandle,MID_BATCH_HSRK_NOFUND,MSG_BATCH_HSRK_NOFUND);
            LOG(LM_STD,Fmtmsg("BATCH:数据审核,查找函数[%s]入口失败",\
                sFuncname),"ERROR");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        iRet=(*func)(lXmlhandle);
        #if 0
        if(iRet<0)
        {
            batch_auditinglistFree();
            dlclose(dhl);
            if( !dlerror() )
            {
                LOG(LM_STD,Fmtmsg("BATCH:关闭动态链接库[%s][%s]",\
                    sDllname,dlerror()),"ERROR");
                /* by yr 20121008 */
                fpub_SetMsg(lXmlhandle,MID_BATCH_JYHS_FAIL,MSG_BATCH_JYHS_FAIL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            }
            /* modified by yr at 20121008 让函数中的错误可以报出来 */
            /*
            	 fpub_SetMsg(lXmlhandle,MID_BATCH_JYHS_FAIL,MSG_BATCH_JYHS_FAIL);
             */
            LOG(LM_STD,Fmtmsg("BATCH:校验函数[%s]校验失败",sFuncname),"ERROR");
            /*
            	 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             */
            return -1; 
        }
        #endif
        if(iRet<0)
        {
            batch_auditinglistFree();
            dlclose(dhl);
            LOG(LM_STD,Fmtmsg("BATCH:校验函数[%s]校验失败",sFuncname),"ERROR");
            return -1; 
        }
        dlclose(dhl);
        if( dlerror() )
        {
            LOG(LM_STD,Fmtmsg("BATCH:关闭动态链接库[%s][%s]",\
                sDllname, dlerror() ), "ERROR")
        }
    }
    
    batch_auditinglistFree();
    LOG(LM_STD,Fmtmsg("处理审核函数个数[%d]",iAudiCount),"INFO");
    
    /* 设置成功标识 */
    fpub_SetMsg(lXmlhandle,MID_SYS_SUCC,MSG_SYS_SUCC);
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");

    return COMPRET_SUCC;
}

/***************************************************************************
	断点处理
 ****************************************************************************/
int  prv_BreakProc(HXMLTREE lXmlhandle, char* sStepID  )
{
    char sBuf[128];
    int  iRet;
    char sStepNum[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sSql1[1024];
    char sErrmsg[512];
    char sBdzt[1+1];    /* 步点状态 */
    char sRwzt[1+1];    /* 任务状态 */
    char sDqbdNew[1+1]; /* 当前实际步点 */
    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf); 
    pstrcopy( sPkrq,sBuf,sizeof( sPkrq ) );
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf); 
    pstrcopy( sPtpch,sBuf,sizeof( sPtpch ) );
    
    /* 获取当前任务状态 */
    snprintf( sSql1, sizeof( sSql1 ), "SELECT dqbd, bdzt, rwzt FROM batch_plrw\
        WHERE pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch );
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sDqbdNew, sBdzt, sRwzt  );
    if( iRet < 1 )        
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_PLRW,\
            Fmtmsg(MSG_BATCH_SEL_PLRW,-1));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 取步点号 */
    iRet = fprv_enumStepNum( sStepID, sStepNum );
    if( iRet != 0 )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    trim( sDqbdNew );
    trim( sStepNum );
    /* 比较当前步点名 */
    if( sStepNum[0] != sDqbdNew[0]  )
    {
        /* 步点不一致，步点任务已触发 */
        LOG(LM_STD,Fmtmsg("BATCH: 批量业务表步点不一致[%s][%s]",\
            sStepNum, sDqbdNew ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
        
    }
    /* modified by yangdong 20121116 rwzt可能为 返回状态
    if( (sBdzt[0] != '2' ) || (sRwzt[0] != '9'  ))
     */
    if( sBdzt[0] != '2' )
    {
        /* 状态不为断点，任务已触发 */
        LOG(LM_STD,Fmtmsg("BATCH: 批量业务状态[%s] 步点状态[%s]",sRwzt, sBdzt ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    return 0 ;
}

/***************************************************************************
当前运行处理
****************************************************************************/
int  prv_Proc(HXMLTREE lXmlhandle, char* sStepID, int iBreakPoint, char * sBdZt, char * sRwZt )
{
    char sBuf[128];
    int  iRet;
    char sStepNum[1+1];
    char sPkrq[8+1];
    char sPtpch[8+1];
    char sBdzt[1+1];    /* 步点状态 */
    char sRwzt[1+1];    /* 任务状态 */
    char sDqbdNew[1+1]; /* 当前实际步点 */
    char sErrmsg[512];
    char sSql1[1024];
    
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ,sBuf); 
    pstrcopy( sPkrq,sBuf,sizeof( sPkrq ) );
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH,sBuf); 
    pstrcopy( sPtpch,sBuf,sizeof( sPtpch ) );
    
    /* 获取当前任务状态 */
    snprintf( sSql1, sizeof( sSql1 ), "SELECT dqbd, bdzt, rwzt FROM batch_plrw\
        WHERE pkrq='%s' AND ptpch='%s' ", sPkrq, sPtpch );
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sDqbdNew, sBdzt, sRwzt  );
    if( iRet < 1 )        
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_PLRW,\
            Fmtmsg(MSG_BATCH_SEL_PLRW,-1));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 取步点号 */
    iRet = fprv_enumStepNum( sStepID, sStepNum );
    if( iRet != 0 )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    trim( sDqbdNew );
    trim( sStepNum );
    /* 比较当前步点名 */
    if( sStepNum[0] != sDqbdNew[0]  )
    {
        /* 步点不一致，步点任务已触发 */
        LOG(LM_STD,Fmtmsg("BATCH: 批量业务表步点不一致[%s][%s]",\
            sStepNum, sDqbdNew ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;    
    }
    if( iBreakPoint==1 )  /* 断点 */
    {
        if( ( sBdzt[0] != '2' && sBdzt[0] != '3' ) || ( sRwzt[0] != '9' && sRwzt[0] != '3' ))
        {
            /* 状态已经改变,任务已触发 */
            LOG(LM_STD,Fmtmsg("BATCH: 批量业务状态[%s] 步点状态[%s]",sRwzt, sBdzt ),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_BREAK_LAUNCHED,MSG_BATCH_BREAK_LAUNCHED );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    if( iBreakPoint==2 ) /* 其他 */
    {
        if( (  sBdzt[0] != '0' && sBdzt[0] != '4' ) || (sRwzt[0] != '0' && sRwzt[0] != '9' ))
        {
            /* mod by yangdong 20121108 成功重复操作时 */
            if(  sBdzt[0] == '1' && sRwzt[0] == '1' ) 
                ;
            else
            {
                /* 状态已经改变,任务已触发 */
                LOG(LM_STD,Fmtmsg("BATCH: 批量业务状态[%s] 步点状态[%s]",sRwzt, sBdzt ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_BATCH_LAUNCHED,MSG_BATCH_LAUNCHED );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }
    }
    strcpy( sBdZt, sBdzt );
    strcpy( sRwZt, sRwzt );
    
    return 0 ;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_AUTOTASK
组件名称: BATCH_AUTOTASK
组件功能: 批量业务自动任务触发控制(断点任务，失败任务处理)
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
1   1-输入   流程标识              416XML解析字符串     *         N     
2   1-输入   当前操作步点          416XML解析字符串     *         N   
3   1-输入   是否为断点            416XML解析字符串     *         N     
4   1-输入   执行后续步点标志      416XML解析字符串     *         N   
输出：  
0   成功
-1  失败
-2  可以重复执行
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_AUTOTASK(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    int  iSetpCount,/*iflag=0,*/iAttribCount;
    int  iParas/*,iStepFlag=0*/;
    char sBuf[255];
    char sSql[512];
    char sSql1[1024];
    char sPkrq[8+1];
    char sKsrq[8+1];  /* 开始日期，默认取当前日期前一天 */
    char sCurrTime[6+1];  /* 当前系统时间 */
    char sDqbd[1+1];    /* 当前步点 */
    char sBdzt[1+1];    /* 步点状态 */
    char sRwzt[1+1];    /* 任务状态 */
    char sDqbdNew[1+1]; /* 当前实际步点 */
    int  iBreakPoint,iRet;
    int  iClsbcs = 0;  /* 处理失败次数 */
    int  iSjtj = 0;    /* 数据提交任务数 */
    int  iInterval = 0;    /* 数据提交任务数 */
    int  iClcs;         /* 步点处理次数 */
    char sErrmsg[512];
    CURSOR cur;
    BATCH_PLRW sdb_batch_plrw;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(3);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"任务类型1 断点 2 失败任务 默认全部"); 
    iBreakPoint=atoi(sBuf);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"批扣日期"); 
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"开始日期"); 
    pstrcopy(sKsrq,sBuf,sizeof(sKsrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEP_FAIL,sBuf); /* 失败重试次数 */
    iClsbcs=atoi( sBuf );
    if( iClsbcs <= 0 )
        iClsbcs = BATCH_MAX_STEP_REPEAT; /* 默认失败最大次数，5 */
    
    /* 当前系统时间 */
    memset(sCurrTime,0,sizeof(sCurrTime));
    pstrcopy( sCurrTime, GetSysTime(), sizeof( sCurrTime ) );
    
    /* 查询需要处理的任务 */    
    memset( sSql, 0x00, sizeof( sSql ) );
    /* 步点状态 :  0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正 */ 
    if( iBreakPoint == 1 ) /* 断点任务 */
        snprintf(sSql,sizeof(sSql),"SELECT * FROM batch_plrw \
            WHERE  bdzt='2' AND clsj<='%s' AND rwzt='3' \
            AND pkrq>='%s'  and pkrq<='%s' ORDER BY taskpri desc", sCurrTime, sKsrq, sPkrq );
    else if( iBreakPoint == 2 )  /* 失败任务 */
        snprintf(sSql,sizeof(sSql),"SELECT * FROM batch_plrw \
            WHERE bdzt='0' AND rwzt='0' AND pkrq>='%s' AND pkrq<='%s' \
            ORDER BY taskpri desc", sKsrq, sPkrq );
    else  /* 失败或者断点任务 默认 */
        snprintf(sSql,sizeof(sSql),"SELECT * FROM batch_plrw \
            WHERE ( ( bdzt='0' AND rwzt='0' ) OR  ( bdzt='2' AND clsj<='%s'  AND rwzt='3' ) ) \
            AND pkrq>='%s' and pkrq<='%s' ORDER BY taskpri desc", sCurrTime, sKsrq, sPkrq );

    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    while( ( iRet = DBFetch(cur, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg ) ) > 0 )
    {
        /* 公共交易信息赋值 */
        trim( sdb_batch_plrw.ywbh );
        
        COMP_SOFTSETXML( "/batch/req/pkrq", sdb_batch_plrw.pkrq );
        COMP_SOFTSETXML( "/batch/req/ptpch", sdb_batch_plrw.ptpch );
        COMP_SOFTSETXML( "/batch/req/ywbh", sdb_batch_plrw.ywbh );
        COMP_SOFTSETXML( "/batch/req/dqbd", sdb_batch_plrw.dqbd );
        
        if( sBdzt[0] == '2' ) /* 断点任务，调用 910004 */
        {
            COMP_SOFTSETXML( "/batch/req/jydm", "910004" );
            if( sDqbd[0] == '2' )
            {
                /* 控制数据提交的间隔期间，即在一个扫描周期内，不要提交过多批量任务，
                	 主要用于控制夜间批量的时候，核心并发数的问题
                	 日间批量，一般不会在数据提交前设置断点 */
                if( iSjtj > 1 )
                {
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    COMP_SOFTGETXML( "/batch/sjtj/interval", sBuf );
                    iInterval = atoi( sBuf );
                    if( iInterval <= 0 )
                        iInterval = 3;
                    sleep( iInterval );
                }
                
                iSjtj ++;
                
                memset( sBuf, 0x00, sizeof( sBuf ) );
                COMP_SOFTGETXML( "/batch/sjtj/continue", sBuf );
                iInterval = atoi( sBuf );
                if( iInterval <= 0 )
                    iInterval = 5;
                if( iSjtj > iInterval )  /* 连续提交文件数超过5，等待下一轮询周期再处理 */
                {
                    LOG(LM_DEBUG,Fmtmsg("BATCH: 本次轮询已提交核心[%d]笔，等下次再处理",iSjtj ),"DEBUG")
                    continue;
                }
            }
        }
        else  /* 失败任务，分别调用对应单步操作交易 */
        {
            /* 失败任务，检查重复次数 */
            iClcs = 0;
            memset( sBuf, 0x00, sizeof( sBuf ) );
            snprintf( sSql1, sizeof( sSql1 ),"SELECT clcs FROM BATCH_plrwbd WHERE pkrq='%s'\
                AND ptpch='%s' AND czbd='%s'",sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd );
            iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql1);
            if( iRet <  1 )
            {
                LOG(LM_STD,Fmtmsg("sqlerr[%s] ptpch[%s] dqbd[%s]信息未找到!",DCILastError(), sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd ),"ERROR");
                continue;
            }
            iClcs = atoi( sBuf );
            /* 处理次数从0开始 */
            if( iClsbcs <= iClcs )
            {
                LOG(LM_DEBUG,Fmtmsg("BATCH: pkrq[%s]ptpch[%s]dqbd[%s]失败次数超限，不再处理",
                    sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd ),"DEBUG")
                continue;
            }
            /* 调用单步处理交易 */
            switch( sDqbd[0] )
            {
                case '0' :    /* 获取数据 */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910005" );
                    break;
                case '1' :    /* 数据入库 */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910006" );
                    break;
                case '2' :    /* 数据审核 */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910007" );
                    break;
                case '3' :    /* 数据提交 */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910008" );
                    break;
                case '4' :    /* 数据提回 */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910009" );
                    break;
                case '5' :    /* 数据回盘 */
                    COMP_SOFTSETXML( "/batch/req/jydm", "910010" );
                    break;
                default:
                    LOG(LM_STD,Fmtmsg("当前步点[%s],系统错", sDqbd ),"ERROR");
                    DCIFreeCursor(cur);
                    fpub_SetMsg(lXmlhandle,MID_BATCH_SEL_PLRWBD,MSG_BATCH_SEL_PLRWBD);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL ;
            }
        }
        
        /* 调用批量主流程 为了异步调用，从900016A调用flow_batch_main*/
        if(fpub_CallFlow(lXmlhandle,"flow_batch_910016A")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("BATCH: 调用批量主流程失败"),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,Fmtmsg(MSG_BATCH_EXEC_FLOW,"batch_flow_main"));
            return COMPRET_FAIL ;
        }
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_SCANTASK
组件名称: BATCH_SCANTASK
组件功能: 批量业务扫描
组件参数:
 参数说明    
输出：  
0   成功
-1  失败
-2  可以重复执行
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_SCANTASK(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    char hostid[30];
    char sSql[512];
    int  iSetpCount;
    /*int iflag=1;*/
    char sBuf[255];
    int iRet= -1;
    /*int iCount= -1;*/
    int iFlag = -1;
    BATCH_ZJXX	sdb_batch_zjxx;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    memset(hostid, 0x00, sizeof(hostid));
    sprintf(hostid, "%s", getenv("HOST_ID"));
    trim(hostid);
    LOG(LM_DEBUG,Fmtmsg("[%s]",hostid),"DEBUG")
    
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( &sdb_batch_zjxx, 0x00, sizeof( BATCH_ZJXX ) );
    sprintf(sSql, "SELECT hostid,flag,status FROM BATCH_ZJXX WHERE hostid ='%s'", hostid );
    
    LOG(LM_DEBUG,Fmtmsg("[%s]执行开始",sSql),"DEBUG")
    iRet = DBSelectToMultiVar(errmsg, sSql, sdb_batch_zjxx.hostid, &sdb_batch_zjxx.flag, sdb_batch_zjxx.status, NULL);
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        return COMPRET_FAIL;
    }
    
    DCIBegin();
    /*如果flag为0 则插入一条记录*/
    LOG(LM_DEBUG,Fmtmsg("主机名[%s]执行开始",sdb_batch_zjxx.hostid),"DEBUG")
    trim(sdb_batch_zjxx.hostid);
    if(strlen(sdb_batch_zjxx.hostid) == 0)	
    {
        memset( &sdb_batch_zjxx, 0x00, sizeof( BATCH_ZJXX ) );
        strcpy(sdb_batch_zjxx.hostid, hostid);
        sdb_batch_zjxx.flag = 1;
        strcpy(sdb_batch_zjxx.status, "0");
        
        iRet = DBInsert("batch_zjxx", SD_BATCH_ZJXX, NUMELE(SD_BATCH_ZJXX), &sdb_batch_zjxx, errmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d|%s]",iRet,DCILastError() ),"ERROR")
            /*		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRW,MSG_BATCH_INS_PLRW); */
            DCIRollback();
            return COMPRET_FAIL;
        }
    }
    
    /* 查询最大权限值 */
    memset( sSql, 0x00, sizeof( sSql ) );
    strcpy(sSql, "SELECT max(flag) FROM BATCH_ZJXX " );
    iRet = DBSelectToVar(errmsg, &iFlag, sSql);
    LOG(LM_DEBUG,Fmtmsg("[%d|%d]执行开始",iFlag,sdb_batch_zjxx.flag),"DEBUG")
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d|%s]",iRet, DCILastError() ),"ERROR")
        /*   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);*/
        return COMPRET_FAIL;
    }
    
    /* 判断最大权限值是否是自己 */
    if(sdb_batch_zjxx.flag != iFlag)
    {
        /* flag 加1,然后 exit*/
        sdb_batch_zjxx.flag = sdb_batch_zjxx.flag +1;
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = %d WHERE hostid = '%s'", sdb_batch_zjxx.flag, sdb_batch_zjxx.hostid);
        LOG(LM_DEBUG,Fmtmsg("[%s]执行开始",sSql),"DEBUG")
        iRet = DCIExecuteDirect(sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d|%s]",iRet, DCILastError() ),"ERROR")
            /*	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);*/
            DCIRollback();
            return COMPRET_FAIL;
        }
        
        /*fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);*/
        DCICommit();
        return COMPRET_SUCC;
    }
    
    /* flag 加1 执行扫描任务 */
    sdb_batch_zjxx.flag = sdb_batch_zjxx.flag +1;
    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = %d WHERE hostid = '%s'", sdb_batch_zjxx.flag, sdb_batch_zjxx.hostid );
    iRet = DCIExecuteDirect(sSql);
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d|%s]",iRet, DCILastError() ),"ERROR")
        /*	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);*/
        DCIRollback();
        return COMPRET_FAIL;
    
    }
    DCICommit();
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_SCANBATCH
组件名称: BATCH_SCANBATCH
组件功能: 批量业务扫描2
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    

输出：  
0   成功
-1  失败
-2  可以重复执行
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_SCANBATCH(HXMLTREE lXmlhandle)
{
    char errmsg[256];
    char hostid[30];
    char sSql[512];
    int  iSetpCount;
    /*int iflag=0;*/
    char sBuf[255];
    int iRet= -1;
    int iCount= -1;
    /*int iFlag = -1;*/
    BATCH_ZJXX	sdb_batch_zjxx;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /* 检查自己是否存在 */
    memset( hostid, 0x00, sizeof(hostid) );
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( &sdb_batch_zjxx, 0x00, sizeof( sdb_batch_zjxx ) );
    
    sprintf( hostid, "%s", getenv("HOST_ID"));
    sprintf(sSql, "SELECT hostid, flag, status FROM BATCH_ZJXX WHERE hostid ='%s'", hostid );
    
    iRet = DBSelectToMultiVar(errmsg, sSql, sdb_batch_zjxx.hostid, &sdb_batch_zjxx.flag, sdb_batch_zjxx.status,NULL );
    if(iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    /*不存在主机信息,则插入一条*/
    DCIBegin();
    trim(sdb_batch_zjxx.hostid);
    if(strlen(sdb_batch_zjxx.hostid) == 0)	
    {
        strcpy(sdb_batch_zjxx.hostid, hostid);
        sdb_batch_zjxx.flag = 0;
        strcpy(sdb_batch_zjxx.status, "0");
        
        iRet = DBInsert("batch_zjxx", SD_BATCH_ZJXX, NUMELE(SD_BATCH_ZJXX), &sdb_batch_zjxx, errmsg);
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            /*	fpub_SetMsg(lXmlhandle,MID_BATCH_INS_PLRW,MSG_BATCH_INS_PLRW);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);*/
            DCIRollback();
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG,Fmtmsg("没有信息,插入一条[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
    }
    else
    {
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf(sSql, "UPDATE BATCH_ZJXX SET status='0' WHERE hostid ='%s'", hostid );
        iRet = DCIExecuteDirect(sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            /*	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);*/
            DCIRollback();
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG,Fmtmsg("已经存在,变更状态[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
    }
    
    /* 判断自己是否是主机,如是 更新其他主机的flag为0 */
    if( sdb_batch_zjxx.flag == 1 && !strcmp(sdb_batch_zjxx.status, "0") )
    {
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = 0 WHERE hostid !='%s' and flag = 1", hostid );
        iRet = DCIExecuteDirect(sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
            return COMPRET_FAIL;
        }
        /*	执行扫描工作 */
        LOG(LM_DEBUG,Fmtmsg("我是主机[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
    }
    else
    {
        /* 判断是否存在有活跃的主机 */
        LOG(LM_DEBUG,Fmtmsg("我不是主机,看是否存在主机[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
        memset( sSql, 0x00, sizeof( sSql ) );
        strcpy(sSql, "SELECT COUNT(*) FROM BATCH_ZJXX WHERE flag = 1 AND status = '0' " );
        iRet = DBSelectToVar(errmsg, &iCount, sSql);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
            return COMPRET_FAIL;
        }
        
        if(iCount == 0)
        {
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = 1 WHERE hostid ='%s'", hostid );
            LOG(LM_DEBUG,Fmtmsg("不存在主机,把我变成主机[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG")
        
            iRet = DCIExecuteDirect(sSql);
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
                DCIRollback();
                return COMPRET_FAIL;
            }
        }
        else
        {
            LOG(LM_DEBUG,Fmtmsg("改变其他死主机状态，同时把自己设置为主机[%s]",fpub_GetCompname(lXmlhandle)),"DEBUG");
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf(sSql, "UPDATE BATCH_ZJXX SET status = '1' WHERE flag = 1 AND hostid != '%s'", hostid );
            
            iRet = DCIExecuteDirect(sSql);
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
                DCIRollback();
                return COMPRET_FAIL;
            }
            
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf(sSql, "UPDATE BATCH_ZJXX SET flag = 1 WHERE hostid = '%s'", hostid );
            
            iRet = DCIExecuteDirect(sSql);
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                /*fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); */
                DCIRollback();
                return COMPRET_FAIL;
            }
        }
    }
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")
    
    DCICommit();
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    return COMPRET_SUCC;
}

/**************************************************************************
函数名称:  int func_queryPlrwbdRecord(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
函数功能:  查询批量任务步点信息表
函数参数:  lXmlhandle     XML句柄
           
函数返回:  0  :成功， -1 :失败
函数说明:
修改说明:
**************************************************************************/
int func_queryPlrwbdRecord(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_plrwbd where pkrq='%s' and ptpch='%s' and czbd='%s'",
        pstPlrwbd->pkrq, pstPlrwbd->ptpch, pstPlrwbd->czbd);
    LOG(LM_STD,Fmtmsg("查询批量任务步点信息记录SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_PLRWBD, NUMELE(SD_BATCH_PLRWBD), pstPlrwbd );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    return iRet;
}
/**************************************************************************
函数名称:  int func_queryFlowSn(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
函数功能:  查询批量任务步点信息表
函数参数:  lXmlhandle     XML句柄
           
函数返回:  0  :成功， -1 :失败
函数说明:
修改说明:
**************************************************************************/
int func_queryFlowSn(HXMLTREE lXmlhandle, BATCH_PLRWBD  *pstPlrwbd)
{
    char sSql[256];
    char sErrmsg[256];
    int iRet = -1;
    int iFlowSn=0;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select max(flowsn) from batch_plrwbd where pkrq='%s' and ptpch='%s' ",
        pstPlrwbd->pkrq, pstPlrwbd->ptpch);
    LOG(LM_STD,Fmtmsg("查询批量任务步点信息记录SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))

    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBSelectToVar(sErrmsg, &iFlowSn, sSql);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
LOG(LM_DEBUG,Fmtmsg("查询批量任务步点信息记录SQL,iFlowSn[%d]", iFlowSn),fpub_GetCompname(lXmlhandle))
    return iFlowSn;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_CONTROL
组件名称:SBATCH_CONTROL
组件功能: 批量业务流程执行总控
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    

使用限制:

程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_CONTROL(HXMLTREE lXmlhandle)
{
    int iStepCount=0,iFlag=0,iAttribCount,jflag;
    int iParas;
    char sXmlNode[128];
    char sStepFlow[128];
    char sAttribvalue[128];
    char sBuf[128];
    int  iBdcgbz,ret;
    char flowStatus[11];
    char sStepSN[2];
    char sStepNM[8];
    char sPkRq[8+1];/*批扣日期*/
    char sPtPch[8+1];/*平台批次号*/
    char sDqbd[2+1];/*当前步点*/
    char sBdzt[1+1];/*步点状态*/
    char sFzbd[2+1];/*辅助步点*/
    char sRwzt[1+1];/*任务状态*/
    char sFinalStep[4+1];/*最后步点*/
    char sFlowStep[4+1];
    int  iFlowSn = 0;
    int  iFinalFlowSn=0;
    int  iIsExe = 0;/*执行标志 0-未执行 1-已执行*/
    int iRet = -1;
    BATCH_PLRWBD sdb_plrwbd;
    BATCH_STEPCFG sdb_batch_stepcfg;
    char sErrmsg[512];
    char sSql1[1024];
    char sFlowID[51];
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle);

    memset(sPkRq, 0x00, sizeof(sPkRq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf)
    pstrcopy(sPkRq, sBuf, sizeof(sPkRq));
    
    memset(sPtPch, 0x00, sizeof(sPtPch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf)
    pstrcopy(sPtPch, sBuf, sizeof(sPtPch));
        
    LOG(LM_STD,Fmtmsg("批量业务运行总控执行开始...pkrq&ptpch[%s%s]",
        sPkRq, sPtPch),fpub_GetCompname(lXmlhandle));
    
    /* 初始化流程到流程链表 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFlowID, 0x00, sizeof(sFlowID));
    COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_FLOWID, sBuf)
    pstrcopy(sFlowID, sBuf, sizeof(sFlowID));
    trim(sFlowID);
    iRet=fprv_initBatchFlow(lXmlhandle, sFlowID, &t_flowList);
    if( iRet <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:无对应流程[%s]配置信息",sFlowID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*查询批量任务表*/
    memset(sDqbd, 0x00, sizeof(sDqbd));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sDqbd)
    memset(&sdb_plrwbd, 0x00, sizeof(sdb_plrwbd));
    pstrcopy(sdb_plrwbd.pkrq, sPkRq, sizeof(sdb_plrwbd.pkrq));
    pstrcopy(sdb_plrwbd.ptpch, sPtPch, sizeof(sdb_plrwbd.ptpch));
    pstrcopy(sdb_plrwbd.czbd, sDqbd, sizeof(sdb_plrwbd.czbd));
    iRet = func_queryPlrwbdRecord(lXmlhandle, &sdb_plrwbd);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("查询批量任务步点信息表失败[%d]", iRet),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("未找到批量任务步点信息表[%d],flowsn从plrwbd表取max(flowsn)+1", iRet),fpub_GetCompname(lXmlhandle))
        /*sdb_plrwbd.flowsn = 1; */
        iRet = func_queryFlowSn(lXmlhandle, &sdb_plrwbd);
        /* mod by tuql 20151230 在步点表中找不到时不报错直接+1 if ( iRet <= 0 ) */
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("查询批量任务步点信息表失败[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        sdb_plrwbd.flowsn = iRet + 1;
    }
    iFlowSn = sdb_plrwbd.flowsn;
    LOG(LM_STD,Fmtmsg("BATCH: 批量业务运行总控,dqbd=[%s],iFlowSn[%d]",
        sdb_plrwbd.czbd, iFlowSn ), fpub_GetCompname(lXmlhandle));
    /* 流程步点循环处理开始 */
    for( pflowIter = i_list_begin(t_flowList); 
        pflowIter!= i_list_end(t_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {
        /*取步点信息*/
        memset(sDqbd, 0x00, sizeof(sDqbd));
        memset(sBdzt, 0x00, sizeof(sBdzt));
        memset(sFzbd, 0x00, sizeof(sFzbd));
        memset(sRwzt, 0x00, sizeof(sRwzt));
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sDqbd)
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_BDZT, sBdzt)
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sFzbd)
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_RWZT, sRwzt)
        
        /*正确定位到预处理步点*/
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        trim(pFlowcfg->stepid);
        if ( iFlowSn > pFlowcfg->flowsn )
        {/*继续,直到定位对应步点*/
            LOG(LM_STD,Fmtmsg("(跳过1)BATCH: 批量业务运行总控[%s,%s],当前步点[%s],跳过步点[%d,%s],步点名称[%s]",\
                sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, 
                pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
            continue;
        }
        if ( ( sBdzt[0] == BATCH_STEP_STATUS_BREAK ||
               sBdzt[0] == BATCH_STEP_STATUS_END   ||
               sBdzt[0] == BATCH_STEP_STATUS_RETURN
              ) && iIsExe==0 
            )
        {/*本步点结束、断点、返回,切换到下一步点*/
            if ( atoi(sDqbd) > 7 && strcmp(sFzbd, BATCH_STEP_ASTSTEP_WRET) == 0 )
            {/*任务嵌套，辅助步点为10-待返回时本步点还未结束*/
                /*不做任何处理*/
            }else
            {
                LOG(LM_STD,Fmtmsg("(跳过2)BATCH: 批量业务运行总控[%s,%s],当前步点[%s],跳过步点[%d,%s],步点名称[%s]",\
                    sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, 
                    pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
                pflowIter = i_list_iter_next(pflowIter);
                pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
                trim(pFlowcfg->stepid);
                
            }
        }
        LOG(LM_STD,Fmtmsg("BATCH: 批量业务运行总控[%s%s],当前步点[%s],执行步点[%d,%s],步点名称[%s]",\
            sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
        memset(sFlowStep, 0x00, sizeof(sFlowStep));
        pstrcopy(sFlowStep, pFlowcfg->stepid, sizeof(sFlowStep));
        iFlowSn=pFlowcfg->flowsn;
        /*设置流程配置全局节点*/
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWID,pFlowcfg->flowid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWNAME,pFlowcfg->flowname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_FLOWSN,itoa(pFlowcfg->flowsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPID,pFlowcfg->stepid);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPSN,itoa(pFlowcfg->stepsn));
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_STEPNAME,pFlowcfg->stepname);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD1,pFlowcfg->extfld1);
        COMP_SOFTSETXML(XMLNM_BATCH_FLOWCFG_EXTFLD2,pFlowcfg->extfld2);
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM batch_stepcfg WHERE \
            flowid='%s' AND flowsn=%d AND stepid='%s'", 
            sFlowID, pFlowcfg->flowsn,pFlowcfg->stepid );
        if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
        {
            iFlag=-1 ;
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            break;
        }
        if (DCIExecute(cur) == -1)
        {
            iFlag=-2 ;
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            break;
        }
        
        /* 获取流程步点属性  */
        for ( iAttribCount=0, jflag=0 ; ;iAttribCount++)
        {
            memset(&sdb_batch_stepcfg,0,sizeof(sdb_batch_stepcfg));
            if( ( iRet = DBFetch(cur, SD_BATCH_STEPCFG, NUMELE(SD_BATCH_STEPCFG), &sdb_batch_stepcfg, sErrmsg ) ) <= 0 )
            {
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("BATCH: 获取流程步点属性处理失败,[%s]", DCILastError() ),"ERROR");
                    jflag = -1;
                }
                break;
            }
        
            memset(sXmlNode,0,sizeof(sXmlNode));
            trim(pFlowcfg->stepid);
            trim(sdb_batch_stepcfg.attribid);
            trim(sdb_batch_stepcfg.attribvalue );
            snprintf(sXmlNode,sizeof( sXmlNode ),\
                "/batch/%s/%s",pFlowcfg->stepid,sdb_batch_stepcfg.attribid);
            
            /* added by yangdong 20121316  增加属性对xml节点支持 */
            /* modified by yangdong 20130618 sdb_batch_stepcfg.attribvalue 可能无法存放解析后字符串长度 
            if(xml_ParseXMLString(lXmlhandle,sdb_batch_stepcfg.attribvalue,sizeof(sdb_batch_stepcfg.attribvalue))==FAIL)
             */
            memset( sAttribvalue ,0,sizeof( sAttribvalue ));
            strcpy( sAttribvalue, sdb_batch_stepcfg.attribvalue );
            if(xml_ParseXMLString(lXmlhandle, sAttribvalue, sizeof( sAttribvalue ))==FAIL)
            {
                LOG(LM_STD,Fmtmsg("BATCH: 获取流程步点属性处理失败,[%s]", sAttribvalue ),"ERROR");
                jflag = -2 ;
                break;
            }
            
            COMP_SOFTSETXML(sXmlNode, sAttribvalue );
            LOG(LM_DEBUG,Fmtmsg("  -->单步总控处理属性[%s][%s], val[%s]", sXmlNode, sdb_batch_stepcfg.attribid, sAttribvalue ),"DEBUG");
            /* end of mod 20130618 */
        }
        DCIFreeCursor(cur);
        LOG(LM_DEBUG,Fmtmsg("处理属性数[%d], flowid[%s], stepid[%s]",\
            iAttribCount,sFlowID,pFlowcfg->stepid),"DEBUG");
        if(jflag < 0) 
        {
            iFlag=jflag ;
            LOG(LM_STD,Fmtmsg("BATCH: 获取流程步点属性处理失败,[%d]",jflag),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_GET_STEPCFG,MSG_BATCH_GET_STEPCFG);
            break;
        }
        
        /* 调用单个步点流程处理 */
        memset(sXmlNode,0,sizeof(sXmlNode));
        memset(sStepFlow,0,sizeof(sStepFlow));
        snprintf(sXmlNode,sizeof( sXmlNode ),\
            "/batch/%s/%s",pFlowcfg->stepid,BATCH_ATTRIBUTE_CLLCM);
        COMP_SOFTGETXML(sXmlNode,sStepFlow);
        
        LOG(LM_STD,Fmtmsg("调用[%s]步点,[%s]流程开始<--",pFlowcfg->stepid,sStepFlow),"INFO");
        trim(sStepFlow);
        if( fpub_CallFlow(lXmlhandle,sStepFlow) != MID_SYS_SUCC)
        {
            iFlag=-3 ;
            COMP_SOFTGETXML(XMLNM_RESPCODE,flowStatus);
            LOG(LM_STD,Fmtmsg("BATCH: 调用[%s]流程失败,返回状态[%s]",\
                sStepFlow,flowStatus),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,\
                Fmtmsg(MSG_BATCH_EXEC_FLOW,sStepFlow));
            break;
        }
        iIsExe ++;
        iStepCount++;
        /* 外部必须赋值 0成功、1失败、2返回 */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_BATCH_BDCGBZ,sBuf);
        LOG(LM_STD,Fmtmsg("<<<<<<调用[%s]步点,[%s]流程结束[%s]>>>>>>",pFlowcfg->stepid,sStepFlow, sBuf),"INFO");
        iBdcgbz=atoi(sBuf);
        ret=fprv_isZero(sBuf);
        if( ret == 0 )
        {
            iFlag=0 ;
            continue;
        }
        else if( iBdcgbz == 1 ) /* 处理失败 */
        {    
            iFlag=-4 ;
            break;
        }
        else if( iBdcgbz == 2 ) /* 返回处理 - 结束循环*/
        {
            iFlag=2;        
            break;
        }
        /* by yr 20120927 */
        else if( iBdcgbz == 3 ) /* 等待处理 - 结束循环*/
        {
            iFlag=3;        
            break;
        }
        /* end */
        else
        {
            iFlag = -5;
            LOG(LM_STD,Fmtmsg("BATCH: 步点成功标志非法[%s]",sBuf),"ERROR");        
            fpub_SetMsg(lXmlhandle,MID_BATCH_BDCGBZ_FF,Fmtmsg(MSG_BATCH_BDCGBZ_FF,sBuf));
            break;
        }
    }
    prv_FlowListFree();
    LOG(LM_STD,Fmtmsg("BATCH: 批量运行总控-流程[%s],处理步点数[%d]--结束iFlag[%d]",
        sFlowID,iStepCount, iFlag),"INFO");
    if(iFlag < 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*获取本批量最后步点*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_FINAL_FLOWSN, sBuf );
    iFinalFlowSn = atoi(sBuf);

    if ( iFlowSn == iFinalFlowSn)
    {/*如最后一步为任务*/
        LOG(LM_DEBUG,Fmtmsg("已是最后步点，设置成功标志[%d][%d]",
            iFlowSn, iFinalFlowSn),fpub_GetCompname(lXmlhandle))
        memset( sBuf, 0x00, sizeof( sBuf ) );
        memset(sFinalStep, 0x00, sizeof(sFinalStep));
        COMP_SOFTGETXML( XMLNM_BATCH_FINAL_STEP, sBuf );
        pstrcopy(sFinalStep, sBuf, sizeof(sFinalStep));
        memset(sFzbd, 0x00, sizeof(sFzbd));
        COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sFzbd)
        COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_FAIL);
        if ( strcmp(sFinalStep, BATCH_STEPNM_RWQT) == 0 &&
             strcmp(sFzbd, BATCH_STEP_ASTSTEP_RETURN) == 0
            )
        {
            COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
        }else if ( strcmp(sFinalStep, BATCH_STEPNM_RWQT) != 0 )
        {
            COMP_SOFTSETXML(XMLNM_BATCH_BDCGBZ, BATCH_STEP_S_SUCC);
        }
    }  
    
    LOG(LM_STD,Fmtmsg("批量业务运行总控执行结束...pkrq&ptpch[%s%s],iFinal[%d-%s],[%d-%s],fzbd[%s]",
        sPkRq, sPtPch, iFinalFlowSn, sFinalStep, iFlowSn, sFlowStep, sFzbd),fpub_GetCompname(lXmlhandle));

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/**************************************************************************
函数名称:  int func_queryPlrwRecord(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
函数功能:  查询批量任务信息表
函数参数:  lXmlhandle     XML句柄
           
函数返回:  0  :成功， -1 :失败
函数说明:
修改说明:
**************************************************************************/
int func_queryPlrwRecord(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_plrw where pkrq='%s' and ptpch='%s'",
        pstPlrw->pkrq, pstPlrw->ptpch);
    LOG(LM_STD,Fmtmsg("查询批量任务信息记录SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), pstPlrw );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("未找到批量任务信息记录,pkrq[%s],ptpch[%s]",
            pstPlrw->pkrq, pstPlrw->ptpch),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "未找到批量任务信息记录");
        return COMPRET_FAIL;
    }

    return 0;
}

/**************************************************************************
函数名称:  int func_queryPlrwRecord2(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
函数功能:  查询批量任务信息表
函数参数:  lXmlhandle     XML句柄
           
函数返回:  0  :成功， -1 :失败
函数说明:
修改说明:
**************************************************************************/
int func_queryPlrwRecord2(HXMLTREE lXmlhandle, BATCH_PLRW  *pstPlrw)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_plrw where bqtpkrq='%s' and bqtptpch='%s'",
        pstPlrw->bqtpkrq, pstPlrw->bqtptpch);
    LOG(LM_STD,Fmtmsg("查询批量任务信息记录SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), pstPlrw );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    return iRet;
}

/**************************************************************************
函数名称:  int func_queryWbwjdjRecord(HXMLTREE lXmlhandle, BATCH_WBWJDJ  *pstWbwjdj)
函数功能:  查询外部文件登记表
函数参数:  lXmlhandle     XML句柄
           
函数返回:  0  :成功， -1 :失败
函数说明:
修改说明:
**************************************************************************/
int func_queryWbwjdjRecord(HXMLTREE lXmlhandle, BATCH_WBWJDJ  *pstWbwjdj)
{
    char sSql[256];
    int iRet = -1;
    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), " select * from batch_wbwjdj where pkrq='%s' and ptpch='%s'",
        pstWbwjdj->pkrq, pstWbwjdj->ptpch);
    LOG(LM_STD,Fmtmsg("查询外部文件登记记录SQL[%s]", sSql),fpub_GetCompname(lXmlhandle))
    
    iRet = fprv_SelToStruct( sSql, SD_BATCH_WBWJDJ, NUMELE(SD_BATCH_WBWJDJ), pstWbwjdj );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("未找到查询外部文件登记信息记录,pkrq[%s],ptpch[%s]",
            pstWbwjdj->pkrq, pstWbwjdj->ptpch),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, "未找到外部文件登记信息记录");
        return COMPRET_FAIL;
    }

    return 0;
}


/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_RULECHECK
组件名称:SBATCH_RULECHECK
组件功能: 批量业务流程规则检查
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    

使用限制:

程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_RULECHECK(HXMLTREE lXmlhandle)
{
    int iParas;
    char sPkRq[8+1];/*批扣日期*/
    char sPtPch[8+1];/*平台批次号*/
    char sDqbd[2+1];/*当前步点*/
    char sBdzt[1+1];/*步点状态*/
    char sFzbd[2+1];/*辅助步点*/
    char sRwzt[1+1];/*任务状态*/
    char sNextStep[1+1];/*下一步*/
    char sFinalStep[4+1];/*最后步点*/
    char sBuf[256];
    /*int  iFlowSn = 0;*/
    int iRet = -1;
    BATCH_PLRW sdb_plrw;
    BATCH_WBWJDJ sdb_wbwjdj;

    fpub_InitSoComp(lXmlhandle);

    memset(sPkRq, 0x00, sizeof(sPkRq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf)
    pstrcopy(sPkRq, sBuf, sizeof(sPkRq));
    
    memset(sPtPch, 0x00, sizeof(sPtPch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf)
    pstrcopy(sPtPch, sBuf, sizeof(sPtPch));

    memset(sNextStep, 0x00, sizeof(sNextStep));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_REQ_NEXTSTEP, sBuf)
    sNextStep[0] = sBuf[0];

    /*获取本批量最后步点*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML( XMLNM_BATCH_FINAL_FLOWSN, sBuf );
    pstrcopy(sFinalStep,sBuf,sizeof(sFinalStep));
    trim( sFinalStep );
        
    LOG(LM_STD,Fmtmsg("批量业务规则检查执行开始...pkrq[%s],ptpch[%s],nextstep[%s],finalstep[%s]",
        sPkRq, sPtPch, sNextStep, sFinalStep),fpub_GetCompname(lXmlhandle));  

    /*外部审核通过*/
    if (sNextStep[0] == '3' )
    {
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_DQBD, "0")/*获取数据*/
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_BDZT, BATCH_STEP_STATUS_S_WAIT)
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_FZBD, BATCH_STEP_ASTSTEP_INIT)
        COMP_SOFTSETXML(XMLNM_BATCH_STEPINFO_RWZT, BATCH_TASK_STATUS_S_PAUSE)
    }

    memset(sDqbd, 0x00, sizeof(sDqbd));
    memset(sBdzt, 0x00, sizeof(sBdzt));
    memset(sFzbd, 0x00, sizeof(sFzbd));
    memset(sRwzt, 0x00, sizeof(sRwzt));
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_DQBD, sDqbd)
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_BDZT, sBdzt)
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_FZBD, sFzbd)
    COMP_SOFTGETXML(XMLNM_BATCH_STEPINFO_RWZT, sRwzt)
    
    LOG(LM_STD,Fmtmsg("外围传入步点信息,dqbd[%s],bdzt[%s],fzbd[%s],rwzt[%s]",
        sDqbd, sBdzt, sFzbd, sRwzt),fpub_GetCompname(lXmlhandle))
    
    /*查询批量任务表*/
    memset(&sdb_plrw, 0x00, sizeof(sdb_plrw));
    pstrcopy(sdb_plrw.pkrq, sPkRq, sizeof(sdb_plrw.pkrq));
    pstrcopy(sdb_plrw.ptpch, sPtPch, sizeof(sdb_plrw.ptpch));
    iRet = func_queryPlrwRecord(lXmlhandle, &sdb_plrw);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("查询批量任务信息表失败[%d]", iRet),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("查询库表步点信息,dqbd[%s],bdzt[%s],fzbd[%s],rwzt[%s]",
        sdb_plrw.dqbd, sdb_plrw.bdzt, sdb_plrw.fzbd, sdb_plrw.rwzt),fpub_GetCompname(lXmlhandle))
    /*比较步点信息一致性*/
    if ( strcmp(sDqbd, sdb_plrw.dqbd) != 0 ||
         strcmp(sBdzt, sdb_plrw.bdzt) != 0 ||
         strcmp(sFzbd, sdb_plrw.fzbd) != 0 ||
         strcmp(sRwzt, sdb_plrw.rwzt) != 0 
        )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_STEPINFO),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_STEPINFO, MSG_BATCH_STEPINFO);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*步点状态为9-正在处理中的，先作等待，稍后发起*/
    if ( sBdzt[0] == BATCH_STEP_STATUS_RUNNING )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_PROCING),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_PROCING, MSG_BATCH_PROCING);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }    
    /*若为获取数据,则需先看一下是否需要外部文件审核*/
    if (sdb_plrw.dqbd[0] == BATCH_STEPSN_HQSJ)
    {
        memset(&sdb_wbwjdj, 0x00, sizeof(sdb_wbwjdj));
        pstrcopy(sdb_wbwjdj.pkrq, sPkRq, sizeof(sdb_wbwjdj.pkrq));
        pstrcopy(sdb_wbwjdj.ptpch, sPtPch, sizeof(sdb_wbwjdj.ptpch));
        iRet = func_queryWbwjdjRecord(lXmlhandle, &sdb_wbwjdj);
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("查询批量外部文件登记表失败[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG(LM_STD,Fmtmsg("当前为获取数据步点，判断是否需要外部文件审核[%s]", 
            sdb_wbwjdj.shzt),fpub_GetCompname(lXmlhandle))
        if (sdb_wbwjdj.shzt[0] != WBWJDJ_SHZT_YES )
        {
            LOG(LM_STD,Fmtmsg(MSG_BATCH_SH_WBWJDJ),fpub_GetCompname(lXmlhandle))
            fpub_SetMsg(lXmlhandle, MID_BATCH_SH_WBWJDJ, MSG_BATCH_SH_WBWJDJ);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    
    /*此任务已是撤销或冲正的,不允许再次发起*/
    if ( strcmp(sRwzt, BATCH_TASK_STATUS_S_CANCEL) == 0 ||
         strcmp(sRwzt, BATCH_TASK_STATUS_S_CORRECT) == 0 ||
         strcmp(sRwzt, BATCH_TASK_STATUS_S_TERM) == 0
        )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_CANCELED),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_CANCELED, MSG_BATCH_CANCELED);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*任务只有在某步点失败时才能直接回盘*/
    if (sNextStep[0] == '1' )
    {
        if (sdb_plrw.bdzt[0] != BATCH_STEP_STATUS_STOP )
        {
            LOG(LM_STD,Fmtmsg(MSG_BATCH_DIRRETURN),fpub_GetCompname(lXmlhandle))
            fpub_SetMsg(lXmlhandle, MID_BATCH_DIRRETURN, MSG_BATCH_DIRRETURN);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /*被嵌套任务不能直接终止*/
    if (sNextStep[0] == '2' )
    {
        /*查询批量任务表*/
        memset(&sdb_plrw, 0x00, sizeof(sdb_plrw));
        pstrcopy(sdb_plrw.bqtpkrq, sPkRq, sizeof(sdb_plrw.bqtpkrq));
        pstrcopy(sdb_plrw.bqtptpch, sPtPch, sizeof(sdb_plrw.bqtptpch));
        iRet = func_queryPlrwRecord2(lXmlhandle, &sdb_plrw);
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("查询批量任务信息表失败[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet > 0 )
        {/*能找到说明是被嵌套任务*/
            LOG(LM_STD,Fmtmsg("被嵌套任务不能被直接终止[%d]", iRet),fpub_GetCompname(lXmlhandle))
            fpub_SetMsg(lXmlhandle, MID_BATCH_DIRFORCE, MSG_BATCH_DIRFORCE);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }

    /*批量任务已正常终态，不允许再次发起
    if ( sDqbd[0] == BATCH_STEPSN_FINL && sBdzt[0] == BATCH_STEP_STATUS_END )
    */
    if ( strcmp(sFzbd, BATCH_STEP_ASTSTEP_END) == 0 )
    {
        LOG(LM_STD,Fmtmsg(MSG_BATCH_STEP_SUCC),fpub_GetCompname(lXmlhandle))
        fpub_SetMsg(lXmlhandle, MID_BATCH_STEP_SUCC, MSG_BATCH_STEP_SUCC);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    LOG(LM_STD,Fmtmsg("批量业务规则检查执行结束"),fpub_GetCompname(lXmlhandle))

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;      
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_AUTOTASK2
组件名称: BATCH_AUTOTASK2
组件功能: 批量业务自动任务触发控制(断点任务，失败任务处理)
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    

输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
int func_autotask2_assig(HXMLTREE lXmlhandle, int iDbTaskRun, char *psKsrq, char *psPkrq, char *psTaskPri, int *piProcCnt, int *piPriProcHighReal )
{
    int  iBusiMax = 0 ;
    int  iBusiProc = 0 ;/*能处理次数*/
    int  iPriProcHigh = 0;
    int  iPriProcHighReal=*piPriProcHighReal;
    int  iProcCnt = *piProcCnt;
    int  iClsbcs = 0;  /* 处理失败次数 */
    char iAbornAuto=1; /*批量任务异常处理0-不处理 1-处理(缺省)*/
    char sCurrTime[6+1];  /* 当前系统时间 */
    char sBuf[255];
    char sSql[512];
    char sZwrq[8+1];
    char sCljg[16+1];
    char sClgy[16+1];
    char sErrmsg[512];
    int iRet = -1;
    int iFlag = 0;
    int iClcs = 0;
    BATCH_PLRW sdb_batch_plrw;
    CURSOR cur;
    int iBreakPoint=0;/*任务类型*/
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_MAXTASKNUM, sBuf)
    iBusiMax = atoi( sBuf );

    /*本次触发次数=最大处理处理数 - 正在处理数 - 已触发次数*/
    iBusiProc = iBusiMax - iDbTaskRun - *piProcCnt;
    if ( psTaskPri[0] == BATCH_TASKPRI_LOWER && iBusiProc <= 0 )
    {/*0-低级或普通批量任务 */
        LOG(LM_STD,Fmtmsg("批量自动任务已触发完任务数[%d]", iBusiProc),"INFO");
        iFlag=1;
        return iFlag;
    }
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PRIHIGHPROC, sBuf)
    iPriProcHigh = atoi( sBuf );

    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_ABORNAUTO, sBuf)
    if ( sBuf[0] == '\0')
    { /*批量任务异常处理0-不处理 1-处理(缺省)*/
        sBuf[0] = '1';
    }
    iAbornAuto = atoi( sBuf );
    
    LOG(LM_STD,Fmtmsg("批量业务自动任务触发,taskpri[%s],maxtasknum[%d],dbRunTask[%d],iAbornAuto[%d]",
        psTaskPri, iBusiMax, iDbTaskRun, iAbornAuto),fpub_GetCompname(lXmlhandle));

    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_STEP_FAIL,sBuf); /* 失败重试次数 */
    iClsbcs=atoi( sBuf );
    if( iClsbcs <= 0 )
        iClsbcs = BATCH_MAX_STEP_REPEAT; /* 默认失败最大次数，5 */
    /*任务类型1 断点 2 失败任务 默认全部*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/systask/wjbz", sBuf)
    if (sBuf[0] == '\0')
    {
        sBuf[0]='0';
    }
    iBreakPoint=atoi(sBuf);
    /* 当前系统时间 */
    memset(sCurrTime,0,sizeof(sCurrTime));
    pstrcopy( sCurrTime, GetSysTime(), sizeof( sCurrTime ) );
    LOG(LM_STD,Fmtmsg("批量业务自动任务触发,clsbcs[%d],breakpoint[%d],currtime[%s]",
        iClsbcs, iBreakPoint, sCurrTime),fpub_GetCompname(lXmlhandle));

    /* 查询需要处理的中高级任务 */
    memset( sSql, 0x00, sizeof( sSql ) );
    /* 步点状态 :  0中止 1结束 2断点 3返回 4等待 9在处理中  X 撤销 C冲正 */
    if (iBreakPoint==1)
    {/*1-断点*/
        snprintf(sSql,sizeof(sSql),"SELECT a.* FROM batch_plrw a WHERE a.pkrq>='%s' AND a.pkrq<='%s' AND a.bdzt='2' AND a.rwzt='3' AND a.clsj<='%s' AND a.taskpri='%s'  ORDER BY a.pkrq , a.ptpch ", psKsrq, psPkrq, sCurrTime, psTaskPri ); 
    }else if (iBreakPoint==2)
    {/*2-失败*/
        snprintf(sSql,sizeof(sSql),"SELECT a.* FROM batch_plrw a WHERE a.pkrq>='%s' AND a.pkrq<='%s' AND a.bdzt='0' AND a.rwzt='0' AND a.taskpri='%s'  ORDER BY a.pkrq , a.ptpch ", psKsrq, psPkrq, psTaskPri ); 
    }else
    {/*0-缺省*/
        snprintf(sSql,sizeof(sSql),"SELECT a.* FROM batch_plrw a WHERE a.pkrq>='%s' AND a.pkrq<='%s' AND ( ( a.bdzt='0' AND a.rwzt='0') OR ( a.bdzt='4' AND a.rwzt='4' AND a.clsj<='%s') OR ( a.bdzt='2' AND a.rwzt='3' AND a.clsj<='%s' ) ) AND a.taskpri='%s'  ORDER BY a.pkrq , a.ptpch ", psKsrq, psPkrq, sCurrTime, sCurrTime, psTaskPri ); 
    }
    
    LOG(LM_STD,Fmtmsg("auto task sql:[%s]", sSql),"ERROR");
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(&sdb_batch_plrw, 0x00, sizeof(sdb_batch_plrw));
    while( ( iRet = DBFetch(cur, SD_BATCH_PLRW, NUMELE(SD_BATCH_PLRW), &sdb_batch_plrw, sErrmsg ) ) > 0 )
    {
        /*LOG(LM_STD,Fmtmsg("[%d] ? [%d],[%s],[%s]", 
            atoi(psPkrq) ,atoi(sdb_batch_plrw.clrq), sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch),"ERROR");
        */
        if ( atoi(psPkrq) < atoi(sdb_batch_plrw.clrq) )
        {
            LOG(LM_STD,Fmtmsg("跳过,批量自动任务[%s%s]未到达触发日期[%s]<[%s]", 
                sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, psPkrq, sdb_batch_plrw.clrq),"ERROR");
            continue;
        }
        
        if ( sdb_batch_plrw.taskpri[0] == BATCH_TASKPRI_LOWER )
        {/*0-低级或普通批量任务 */
            if ( iBusiProc <= 0 )
            {
                LOG(LM_STD,Fmtmsg("批量自动任务已触发完任务数[%d]", iBusiProc),"ERROR");
                iFlag=1;
                break;
            }
        }else
        {/*1,2-中高级或加急/特急批量任务 */
            if ( *piPriProcHighReal >= iPriProcHigh && iPriProcHigh > 0 )
            {
                LOG(LM_STD,Fmtmsg("批量中高级任务已达优先处理数[%d]>=[%d]", 
                    *piPriProcHighReal, iPriProcHigh),"ERROR");
                iFlag=2;
                break;
            }
            iPriProcHighReal ++;
        }
        /* 公共交易信息赋值 */
        trim( sdb_batch_plrw.pkrq );
        trim( sdb_batch_plrw.ptpch );
        trim( sdb_batch_plrw.ywbh );
        trim( sdb_batch_plrw.dqbd );
        
        if ( sdb_batch_plrw.bdzt[0] == '0' && iAbornAuto != 1 )
        {/*失败步点且不需自动处理,跳过*/
            continue;
        }
        
        memset(sSql, 0x00, sizeof(sSql));
        snprintf(sSql, sizeof(sSql), "select clcs,cljg,clgy from batch_plrwbd where pkrq='%s' and ptpch='%s' and czbd='%s'",
            sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd);
        iClcs = 0;
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sCljg, 0x00, sizeof(sCljg));
        memset(sClgy, 0x00, sizeof(sClgy));
        iRet = DBSelectToMultiVar(sErrmsg, sSql, &iClcs, sCljg, sClgy);
        /*iRet = DBSelectToVarChar(sErrmsg, sBuf,  sSql); */
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("BATCH: 数据库操作失败[%s]",DCILastError() ),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            iFlag = -1;
            break;
        }
        /*iClcs = atoi(sBuf);*/
        if ( iClcs >= iClsbcs )
        {/*处理次数已达最大,跳过*/
            continue;
        }
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_JYDM, "910031" );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_YWBH, sdb_batch_plrw.ywbh );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_PKRQ, sdb_batch_plrw.pkrq );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_PTPCH, sdb_batch_plrw.ptpch );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_NEXTSTEP, "0");/*0-断步续做*/
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_DQBD, sdb_batch_plrw.dqbd );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_BDZT, sdb_batch_plrw.bdzt );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_FZBD, sdb_batch_plrw.fzbd );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_RWZT, sdb_batch_plrw.rwzt );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_JYJG, sCljg );
        COMP_SOFTSETXML( XMLNM_BATCH_REQ_JYGY, sClgy );
        
        iBusiProc --;
        iProcCnt ++;
        LOG(LM_STD,Fmtmsg("[%d]批量任务[%s%s%s],优先级[%s],状态[%s,%s]将被调起处理", 
            iProcCnt, sdb_batch_plrw.pkrq, sdb_batch_plrw.ptpch, sdb_batch_plrw.dqbd, 
            sdb_batch_plrw.taskpri,sdb_batch_plrw.bdzt, sdb_batch_plrw.rwzt),"INFO");
        /* 调用批量主流程 为了异步调用，从900016A调用flow_batch_960031*/
        if(fpub_CallFlow(lXmlhandle,"flow_batch_910016A")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("BATCH: 调用批量业务主流程失败,flow_batch_910016A"),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_BATCH_EXEC_FLOW,Fmtmsg(MSG_BATCH_EXEC_FLOW,"flow_batch_910016A"));
            iFlag = -2;
            break;
        }
        memset(&sdb_batch_plrw, 0x00, sizeof(sdb_batch_plrw));
    }
    DCIFreeCursor(cur);
    if( iFlag < 0 )
    {
        LOG(LM_STD,Fmtmsg("批量自动任务循环触发任务失败,sqlerr[%d]",iFlag ),"ERROR");
        return iFlag;
    }
    *piProcCnt = iProcCnt;
    *piPriProcHighReal = iPriProcHighReal;
    return iFlag;    
}
IRESULT SBATCH_AUTOTASK2(HXMLTREE lXmlhandle)
{
    int  iSetpCount/*,iflag=0*/,iAttribCount;
    int  iParas/*,iStepFlag=0*/;
    char sBuf[255];
    char sPkrq[8+1];
    char sKsrq[8+1];  /* 开始日期，默认取当前日期前一天 */
    char sSql[512];
    char sErrmsg[512];
    /*int  iSjtj = 0;     数据提交任务数 */
    /*int  iInterval = 0;     数据提交任务数 */
    /*int  iRunctlMax = 0;*/
    int  iDbTaskRun = 0;
    int  iProcCnt = 0;
    int  iPriProcHighReal = 0;
    int  iRet = -1;


    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(2);
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"批扣日期"); 
    pstrcopy(sPkrq,sBuf,sizeof(sPkrq));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"开始日期");
    pstrcopy(sKsrq,sBuf,sizeof(sKsrq));

    /* 校验应用任务总数(控制) */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf( sSql, sizeof( sSql ), "SELECT count(pkrq) FROM batch_plrw WHERE  pkrq = '%s' and rwzt = '9' ", sPkrq );
    memset(sBuf, 0x00, sizeof(sBuf));
    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSql);
    if( iRet < 0 )        
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        		fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    iDbTaskRun = atoi( sBuf );
    
    /*高级任务优先处理*/
    iRet = func_autotask2_assig(lXmlhandle, iDbTaskRun, sKsrq, sPkrq, "2", &iProcCnt, &iPriProcHighReal);
    if( iRet < 0 )        
    {
        LOG(LM_STD,Fmtmsg("批量自动任务触发3-高级失败[%d]", iRet ),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*中级任务第二处理*/
    iRet = func_autotask2_assig(lXmlhandle, iDbTaskRun, sKsrq, sPkrq, "1", &iProcCnt, &iPriProcHighReal);
    if( iRet < 0 )        
    {
        LOG(LM_STD,Fmtmsg("批量自动任务触发2-中级失败[%d]", iRet ),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*低级任务最后处理*/
    iRet = func_autotask2_assig(lXmlhandle, iDbTaskRun, sKsrq, sPkrq, "0", &iProcCnt, &iPriProcHighReal);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("批量自动任务触发1-低级失败[%d]", iRet ),"ERROR")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_DEBUG,Fmtmsg("批量业务自动任务执行结束,共调起[%d]个批次",iProcCnt), fpub_GetCompname(lXmlhandle));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_GETFLOWSN
组件名称:SBATCH_GETFLOWSN
组件功能: 批量业务获取流程序号
组件参数:
序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    

使用限制:

程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT SBATCH_GETFLOWSN(HXMLTREE lXmlhandle)
{
    int /*iStepCount=0,*/iFlag=0,iAttribCount,jflag;
    int iParas;
    char sXmlNode[128];
    char sStepFlow[128];
    char sAttribvalue[128];
    char sBuf[128];
    int  iBdcgbz,ret;
    char flowStatus[11];
    char sStepSN[2];
    char sStepNm[8+1];
    char sFlowSnNode[64+1];
    char sPkRq[8+1];/*批扣日期*/
    char sPtPch[8+1];/*平台批次号*/
    char sDqbd[2+1];/*当前步点*/
    char sBdzt[1+1];/*步点状态*/
    char sFzbd[2+1];/*辅助步点*/
    char sRwzt[1+1];/*任务状态*/
    char sFinalStep[4+1];/*最后步点*/
    char sFlowID[51];
    int  iFlowSn = 0;
    /*int  iIsExe = 0;执行标志 0-未执行 1-已执行*/
    int iRet = -1;
    BATCH_PLRWBD sdb_plrwbd;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1)
  
    memset(sBuf,0,sizeof(sBuf));
    memset(sStepNm, 0x00, sizeof(sStepNm));
    COMP_GETPARSEPARAS(1,sBuf,"步点名称")
    trim(sBuf);
    pstrcopy(sStepNm,sBuf,sizeof(sStepNm));
  
    memset(sBuf,0,sizeof(sBuf));
    memset(sFlowSnNode, 0x00, sizeof(sFlowSnNode));
    COMP_GETPARSEPARAS(2,sBuf,"流程序号结点")
    trim(sBuf);
    pstrcopy(sFlowSnNode,sBuf,sizeof(sFlowSnNode));

    memset(sPkRq, 0x00, sizeof(sPkRq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PKRQ, sBuf)
    pstrcopy(sPkRq, sBuf, sizeof(sPkRq));
    
    memset(sPtPch, 0x00, sizeof(sPtPch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_BATCH_PTPCH, sBuf)
    pstrcopy(sPtPch, sBuf, sizeof(sPtPch));
    
    /* 初始化流程到流程链表 */
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFlowID, 0x00, sizeof(sFlowID));
    COMP_SOFTGETXML(XMLNM_BATCH_RUNCTRL_FLOWID, sBuf)
    pstrcopy(sFlowID, sBuf, sizeof(sFlowID));
    trim(sFlowID);
    LOG(LM_STD,Fmtmsg("批量业务获取流程序号执行开始...pkrq&ptpch[%s%s],FLOWID[%s]",
        sPkRq, sPtPch, sFlowID),fpub_GetCompname(lXmlhandle));
    iRet=fprv_initBatchFlow(lXmlhandle, sFlowID, &t_flowList);
    if( iRet <=0 )
    {
        LOG(LM_STD,Fmtmsg("BATCH:无对应流程[%s]配置信息",sFlowID),"ERROR")
            fpub_SetMsg(lXmlhandle,MID_BATCH_FLOWCFG_NOFUND,MSG_BATCH_FLOWCFG_NOFUND);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    iFlowSn = 1;
    /* 流程步点循环处理开始 */
    for( pflowIter = i_list_begin(t_flowList); 
        pflowIter!= i_list_end(t_flowList); 
        pflowIter = i_list_iter_next(pflowIter) )
    {        
        /*正确定位到预处理步点*/
        pFlowcfg = (BATCH_FLOWCFG *)(pflowIter->data);
        trim(pFlowcfg->stepid);
        if ( strcmp(pFlowcfg->stepid, sStepNm) != 0 )
        {/*继续,直到定位对应步点*/
            LOG(LM_STD,Fmtmsg("(跳过1)BATCH: 批量业务获取流程序号[%s,%s],当前步点[%s],跳过步点[%d,%s],步点名称[%s]",\
                sPkRq, sPtPch, pFlowcfg->flowsn, 
                pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
            continue;
        }
        iFlowSn = pFlowcfg->flowsn;
        LOG(LM_STD,Fmtmsg("BATCH: 批量业务获取流程序号[%s%s],当前步点[%s],执行步点[%d,%s],步点名称[%s]",\
            sPkRq, sPtPch, sDqbd, pFlowcfg->flowsn, pFlowcfg->stepid, pFlowcfg->stepname), fpub_GetCompname(lXmlhandle));
    }
    prv_FlowListFree();
    LOG(LM_STD,Fmtmsg("BATCH: 批量业务获取流程序号-流程[%s]--结束iFlag[%d]",
        sFlowID, iFlag),"INFO");
    if(iFlag < 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    COMP_SOFTSETXML(sFlowSnNode, itoa(iFlowSn))

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
