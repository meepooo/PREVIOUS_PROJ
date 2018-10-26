/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V4.1.0.1
操作系统:
文件名称:APP_YWGL.c
文件描述:业务管理类组件函数，包括日终归档清理，交易启停，日切等。
项 目 组:
程 序 员: YangDong 聂瑞
发布日期: 20090624
修    订: SC
修改日期: 20110905
修改内容：添加SApp_SysShell组件，供调用shell命令运行，目前对system返回值判断有问题，执行成功也返回-1
修    订: YangDong

修改日期: 20140915
修改内容：dci改造
*********************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
/*#include <unistd.h>
#include <fcntl.h>*/

#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
    <root>\
    <soname>APP_YWGL.so</soname>\
    <sosrcname>APP_YWGL.c</sosrcname>\
    <sonote>业务管理通用组件集合</sonote>\
    <version>\
    <rec ver=\"2.0.0.1\" modify=\"2010-4-1  15:08\" programer=\"YangDong\" filesize=\"1309408\">HS-AgentV2.0整理</rec>\
    <rec ver=\"2.1.0.1\" modify=\"2011-11-01 10:08\" programer=\"S..C..\"   filesize=\"1309408\">HS-AgentV2.1改造</rec>\
    <rec ver=\"4.1.0.1\" modify=\"2014-9-15 10:08\" programer=\"YangDong\"  filesize=\"1309408\">DCI改造</rec>\
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


/* 私有函数，判断是否为闰年，是则返回1，不是返回0 */
IRESULT isLeapYear(int i)
{
    if (i%100 != 0 && i%4 == 0)
        return 1;
    if ( i%100 == 0 && i%400 == 0)
        return 1;
    return 0;
}

/* 私有函数，取当前日期的下一天 */
IRESULT GetSysNextDate(char * sNextDate)
{
    char sCurDate[9]={0};
    char sYear[5]={0};
    char sMon[3]={0};
    char sDay[3]={0};
    int  iYear=0;
    int  iMon=0;
    int  iDay=0;
    int  monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    sprintf(sCurDate, "%s", GetFmtSysDate("%Y%m%d"));
    LOG(LM_DEBUG,Fmtmsg("获取系统日期[%s]",sCurDate),"DEBUG");
    memcpy(sYear, sCurDate, 4);
    memcpy(sMon,  sCurDate+4, 2);
    memcpy(sDay,  sCurDate+6, 2);
    iYear = atoi(sYear);
    iMon  = atoi(sMon);
    iDay  = atoi(sDay);
    /* 闰年2月份在28天的基础上增加1天 */
    monthday[1] += isLeapYear(iYear);
    iDay ++;
    if(iDay > monthday[iMon-1])
    {
        iDay = 1;
        iMon ++;
        if(iMon == 13)
        {
            iMon = 1;
            iYear ++;
        }
    }
    sprintf(sNextDate,"%4d%02d%02d", iYear, iMon, iDay);
    LOG(LM_DEBUG,Fmtmsg("获取第二天日期[%s]",sNextDate),"DEBUG");
    return 0;
}

/*********************************************************************
动态组件函数定义
组件函数名称:SApp_SysInitDate
组件名称:SApp_SysInitDate
组件功能:平台日切
组件参数:
 序号 参数类型  参数名称    资源类别    缺省值  可空  参数说明
  1   1-输入    日切日期  416-解析字符串  N     日切后日期

组件结果状态:
  结果状态码         结果说明
  缺省

项 目 组: 
程 序 员: 
发布日期:
*********************************************************************/
IRESULT SApp_SysInitDate(HXMLTREE lXmlhandle)
{
    char sNextDate[8+1];
    char sDate[8+1];
    int  iZhqzlsh=0;
    char sSql[256];
    char sBuf[256];
    int  iParas;
    
    /*add by SC 20120925 修改GAPS流水切换后，共享内存内流水号需要更新到数据库表*/
    char sLshStep[10];
    char sMaxLsh[15];
    int  iLshStep=0;
    int  iMaxLsh=0;
    /*add by SC 20120925 end*/
    
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)
  
    memset( sBuf, 0x00, sizeof( sBuf ) );
    memset( sNextDate, 0x00, sizeof( sNextDate ) );
    COMP_GETPARSEPARAS( 1, sBuf, "日切日期" )
    pstrcopy( sNextDate, sBuf, sizeof( sNextDate ) );
    if (strlen(sNextDate) == 0)
    {
        GetSysNextDate( sNextDate );
    }
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sDate, 0x00, sizeof( sDate ) );
    
    /* 获取当前帐务日期，判断，若果相等，表示已经日切，直接返回 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZWRQ, sBuf);
    strcpy( sDate, sBuf );
    
    if( memcmp( sDate, sNextDate , 8 ) == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" 系统日期[%s],已经日切 ",sDate ),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    
    memset( sSql, 0x00, sizeof( sSql ) );

    /* 流水号重置标志 */
    COMP_SOFTGETXML( XMLNM_APP_LSH_RETURN, sBuf);
    trim(sBuf);
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" 重置流水号标志[%s] ", sBuf ),"INFO");
    if( sBuf[0] == '0' ) /* 0 重置 */
    {
        /* 业务起始流水获取 */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CSKZ_ZXLSH, sBuf);
        trim(sBuf);
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" 最小流水号[%s] ", sBuf ),"INFO");
        iZhqzlsh = atoi(sBuf);
        if( iZhqzlsh == 0 )  /* 未设置最小流水号 */
        {
            iZhqzlsh = 1;   /* 默认1 */
        } 
    }
    else /* 不重置流水号 20120925 增加对不归零流水号处理 */
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_ZHQZLSH, sBuf);
        iZhqzlsh = atoi(sBuf);
        
        if ( ExGetCfgItem("gaps.ini", "RESOURCE", "SERIALNOSTEP", sLshStep, sizeof( sLshStep ) ) != 0 ) 
        {
            LOG( LM_STD,Fmtmsg("gaps.ini文件错误!sLshStep=[%s]", sLshStep ),"WORN" )
            iLshStep = 100;
        }
        else
            iLshStep=atoi(sLshStep);
  
        if ( ExGetCfgItem("gaps.ini", "RESOURCE", "SERIALMAX", sMaxLsh, sizeof( sMaxLsh ) ) != 0 ) 
        {
            LOG( LM_STD,Fmtmsg("gaps.ini文件错误!sMaxLsh=[%s]", sMaxLsh ),"WORN" )
            iMaxLsh = 99999999;
        }
        else
            iMaxLsh=atoi(sMaxLsh);
        
        /* 避免流水号重复，并超出最大值范围 */
        iZhqzlsh += iLshStep;
        if (iZhqzlsh >= iMaxLsh)
        {
            memset(sBuf,0,sizeof(sBuf));
            COMP_SOFTGETXML(XMLNM_APP_CSKZ_ZXLSH, sBuf);
            trim(sBuf);
            iZhqzlsh = atoi(sBuf);
            if( iZhqzlsh == 0)  /* 未设置最小流水号 */
            {
                iZhqzlsh = 1;   /* 默认1 */
            }
        }
    }

    sprintf(sBuf, "%d", iZhqzlsh);
    /* 更新系统参数文件syspara.ini */
    fpub_WriteSysPara(FILE_SYSPARA, "zwrq", sNextDate);
    fpub_WriteSysPara(FILE_SYSPARA, "zhqzlsh", sBuf );
    fpub_WriteSysPara(FILE_SYSPARA, "pch", "1" );
    /* 刷新SPA */

    /* modified by yangdong 20090921 */
    iParas = 0;
    iParas = system("initGSA rp -y >/dev/null 2>&1");
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"DEBUG");
    /*
    if( ( ! WIFEXITED( iParas ) ) || ( WEXITSTATUS( iParas ) != 0 ) )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"");
        fpub_SetMsg(lXmlhandle, MID_SYS_RMAREFRESHRES, Fmtmsg( MSG_SYS_RMAREFRESHRES,"",0 )  );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    */
    /* end of mod */

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/********************************************************************
组件函数名称: SApp_Archive
组件名称: 数据归档
组件功能:日终数据归档处理
     
组件参数:
序号 参数名称   资源类别   缺省值    是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
 
项 目 组: 
程 序 员:
发布日期: 2009年2月
修改日期:
*********************************************************************/
IRESULT SApp_Archive(HXMLTREE lXmlhandle)
{
    char     sYybs[3+1],sYymc[40+1];
    char    sGdrq[8+1],sGdqsrq[8+1];
    char    sColKey[32],sColValue[64];
    char    sRunSql[1024],sWhsql[512];
    char    sCurSql[1024],sHisSql[1024];
    char    sTmpSql[512];
    int     iCount,iHisCount;
    int     iLsts;
    APP_RZPZ sdb_app_rzpz;
  
    int    iParas;
    int iRet,iTjs,iColVaue;
    int i,iResult;
    int  iFail = 0;
    char    sBuf[256];
    char    sSrcDir[128],sDesDir[128];
    char    sType[1+1],sColName[32+1];
    char    sLopper[4+1],sOP[6+1];
    char    sCmd[512];
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");    
    /*组件参数检查*/
    COMP_PARACOUNTCHK(2)
            
    /*获取组件参数*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"应用标识");
    trim(sBuf);
    memset(sYybs,0,sizeof(sYybs));
    memcpy(sYybs,sBuf,sizeof(sYybs));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"归档日期");
    trim(sBuf);
    memset(sGdrq,0,sizeof(sGdrq));
    memcpy(sGdrq,sBuf,sizeof(sGdrq));
    
    memset(sBuf,0,sizeof(sBuf));        /*应用名称*/
    COMP_SOFTGETXML(XMLNM_APP_YYXX_YYMC,sBuf);
    memset(sYymc,0,sizeof(sYymc));
    memcpy(sYymc,sBuf,sizeof(sYymc));
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("yybs=[%s],yymc=[%s],gdrq=[%s]",sYybs,sYymc,sGdrq),"DEBUG");
    
    /*定义日终配置表游标*/
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_rzpz WHERE ssyy='%s'AND czlx='1'",sYybs );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
     
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("声明日终配置表游标错误,[%s]",DCILastError()),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
  
    while(1)
    {
        /*取日志配置表需要归档的对象*/
        memset(&sdb_app_rzpz,0,sizeof(sdb_app_rzpz));
        iRet = DBFetch(cur, SD_APP_RZPZ, NUMELE(SD_APP_RZPZ), &sdb_app_rzpz, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        trim(sdb_app_rzpz.dxlx);
        trim(sdb_app_rzpz.czdx1);
        trim(sdb_app_rzpz.czdx2);
        trim(sdb_app_rzpz.cztj);
            
        if( strncmp(sdb_app_rzpz.dxlx,"1",1)==0 )        /*数据库归档*/
        {
            /*组织归档的SQL*/
            memset(sRunSql,0,sizeof(sRunSql));
            sprintf(sRunSql, "INSERT INTO %s SELECT * FROM %s WHERE 1=1 ",\
                sdb_app_rzpz.czdx2,sdb_app_rzpz.czdx1);
        
            /*统计当日表满足条件的记录数*/
            memset(sCurSql,0,sizeof(sCurSql));
            sprintf(sCurSql, "SELECT count(*) FROM %s WHERE 1=1 ",sdb_app_rzpz.czdx1);
            /*统计历史表导入成功的记录数*/
            memset(sHisSql,0,sizeof(sHisSql));
            sprintf(sHisSql, "SELECT count(*) FROM %s WHERE 1=1 ", sdb_app_rzpz.czdx2);
        
        
            /*统计条件个数*/
            iTjs = 0;
            iTjs = fprv_countchar(sdb_app_rzpz.cztj,'|');
        
            /*取条件语句*/
            for(i=0;i<iTjs;i++)
            {
                memset(sTmpSql,0,sizeof(sTmpSql));
                fprv_getSubItem(sdb_app_rzpz.cztj,i,"|",sTmpSql);
            
                /*单个SQL条件*/
                memset(sType,0,sizeof(sType));
                memset(sColName,0,sizeof(sColName));
                memset(sLopper,0,sizeof(sLopper));
                memset(sColKey,0,sizeof(sColKey));
                memset(sOP,0,sizeof(sOP));
                fprv_getSubItem(sTmpSql,0,";",sType);
                fprv_getSubItem(sTmpSql,1,";",sColName);
            
                fprv_getSubItem(sTmpSql,2,";",sLopper);
                fprv_getSubItem(sTmpSql,3,";",sColKey);
            
                if(i < iTjs-1)
                {
                    fprv_getSubItem(sTmpSql,4,";",sOP);
                }
            
                /*查询参数控制表*/
                trim(sColKey);
                /* 20111010 modified by yangdong 增加对非键值任务处理 */
                if( sColKey[0] == 'K' )
                { 
                    memset(sColValue,0,sizeof(sColValue));
                    snprintf( sSql1, sizeof( sSql1 ),"SELECT jdz FROM app_cskz WHERE csjz='%s'",sColKey );
                    iRet = DBSelectToVarChar( sErrmsg,  sColValue, sSql1 );
                    if ( iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("查询参数控制表失败,[%s]", DCILastError() ),"ERROR");
                        DCIRollback();
                        DCIFreeCursor(cur); 
                        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    if ( iRet == 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("对应参数键值不存在,csjz=[%s]",sColKey),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_APP_SJGD_NOFUND,MSG_APP_SJGD_NOFUND);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                }
                else
                {
                     snprintf( sColValue, sizeof( sColValue ), "%s", sColKey );
                }
                trim(sColValue);
            
                if( i==0 )  /*第一个条件为保留天数*/
                {
                    iLsts = 0;
                    iColVaue = atoi(sColValue);
                    iLsts = 0 - iColVaue;
                
                    /*计算日期*/
                    iRet = 0;
                    memset(sGdqsrq,0,sizeof(sGdqsrq));
                    iRet=fprv_dateOffSet(sGdrq,iLsts);
                    sprintf(sGdqsrq, "%d", iRet);

                    memset(sWhsql,0,sizeof(sWhsql));
                    /* modified by yangdong 20111010 
                    sprintf(sWhsql, "AND %s='%s' %s", sColName,sGdqsrq,sOP);
                    */
                    sprintf(sWhsql, "AND %s<='%s' %s", sColName,sGdqsrq,sOP);
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                }
                else
                {
                    memset(sWhsql,0,sizeof(sWhsql));
                    if( strncmp(sType,"D",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%.2f%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else if( strncmp(sType,"I",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%d%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else
                        sprintf(sWhsql, " %s%s'%s'%s ", sColName,sLopper,sColValue,sOP);
                    
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                }
            }
        
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sRunSql=[%s]",sRunSql),"DEBUG");
        
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sCurSql=[%s]",sCurSql),"DEBUG");

            /*统计当前表满足归档条件的记录数*/
           iRet = DBSelectToVar( sErrmsg, &iCount, sCurSql) ;
           if( iRet < 0 )
           {
               LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
               DCIFreeCursor(cur);
               DCIRollback();
               fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
               fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
               return COMPRET_FAIL;
           }
        
            if( iCount==0 )  /*当日流水表无满足条件的记录*/
            {
                continue;
            }
            else
            {
                /*执行归档操作*/
                iResult = 0;
                iRet = DCIExecuteDirect( sRunSql );
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                        Fmtmsg("归档失败[%d],归档源=[%s],目的=[%s]",\
                        DCILastErrno(), sdb_app_rzpz.czdx1,sdb_app_rzpz.czdx2),"ERROR");

                    /* 归档失败，可以判断是否重复归档 */
                    /*统计历史表满足归档条件的记录数*/
                    memset( sRunSql, 0x00, sizeof( sRunSql ) );
                    sprintf(sRunSql, "SELECT count(*) FROM %s WHERE 1=1 %s ",sdb_app_rzpz.czdx1, sWhsql);
                    iRet = DBSelectToVar( sErrmsg, &iHisCount, sRunSql) ;
                    if( iRet < 0 )
                    {
                        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                        return COMPRET_FAIL;
                    }
                    if( iHisCount >= iCount )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("重复归档[%d][%d]",iHisCount,iCount),"DEBUG");
                        continue;
                    }

                    iFail ++;
                }
            }
        }
        else        /*文件归档*/
        {
            memset(sSrcDir,0,sizeof(sSrcDir));
            memset(sDesDir,0,sizeof(sDesDir));
            sprintf(sSrcDir, "%s/%s", getenv("HOME"),sdb_app_rzpz.czdx1);
            sprintf(sDesDir, "%s/%s", getenv("HOME"),sdb_app_rzpz.czdx2);
        
            memset(sCmd,0,sizeof(sCmd));        /*文件进行归档*/
            sprintf(sCmd, "cp %s* %s.", sSrcDir,sDesDir);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sCmd=[%s]",sCmd),"DEBUG");

            iParas = 0;
            iParas = system( sCmd );
            if ( iParas != 0 )
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"DEBUG");
            /*
            if( ( ! WIFEXITED( iParas ) ) || ( WEXITSTATUS( iParas ) != 0 ) )
            {
                fpub_SetMsg(lXmlhandle, MID_SYS_RMAREFRESHRES, Fmtmsg( MSG_SYS_RMAREFRESHRES,"",0 )  );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            */
            /* end of mod */
        }
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    DCIFreeCursor(cur);

    DCICommit();

    if( iFail > 0  )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_SJGD_GDERR,Fmtmsg("[%d]张表归档失败",iFail ) );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* end of add */
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/********************************************************************
组件函数名称: SApp_Clean
组件名称: 数据清理
组件功能:日终数据清理处理
     
组件参数:
序号 参数名称   资源类别   缺省值    是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
 
项 目 组: 
程 序 员:
发布日期: 2009年6月
修改日期:
*********************************************************************/
IRESULT SApp_Clean(HXMLTREE lXmlhandle)
{
    char    sYybs[3+1],sYymc[40+1];
    char    sQlrq[8+1],sQlqsrq[8+1];
    char    sColKey[32],sColValue[64];
    char    sRunSql[1024],sWhsql[512];
    char    sCurSql[1024],sHisSql[1024];
    char    sTmpSql[512],sHisTable[128], sDateSql[1024];
    char    sMinDate[10+1];
    int     iCount,iHisCount;
    int     iLsts,iFlag;
    APP_RZPZ sdb_app_rzpz;
    int  iRet = -1;
    CURSOR cur;
    char sErrmsg[512];
    int iParas;
    int iTjs,iColVaue;
    int i,iResult;
    char    sBuf[256];
    char    sSrcDir[128],sCmd[512];
    char    sType[1+1],sColName[32+1];
    char    sLopper[4+1],sOP[6+1];
    char    sDateCol[16+1];  /* 日期字段名 */

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    /*组件参数检查*/
    COMP_PARACOUNTCHK(2)
            
    /*获取组件参数*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"应用标识");
    trim(sBuf);
    memset(sYybs,0,sizeof(sYybs));
    memcpy(sYybs,sBuf,sizeof(sYybs));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"清理日期");
    trim(sBuf);
    memset(sQlrq,0,sizeof(sQlrq));
    memcpy(sQlrq,sBuf,sizeof(sQlrq));
    
    memset(sBuf,0,sizeof(sBuf));        /*应用名称*/
    COMP_SOFTGETXML(XMLNM_APP_YYXX_YYMC,sBuf);
    memset(sYymc,0,sizeof(sYymc));
    memcpy(sYymc,sBuf,sizeof(sYymc));
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,\
        Fmtmsg("yybs=[%s],yymc=[%s],qlrq=[%s]",sYybs,sYymc,sQlrq),"DEBUG");
    
    /*定义日终配置表游标*/
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_rzpz WHERE ssyy='%s'AND czlx='2'",sYybs );
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
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("声明日终配置表游标错误,[%s]",DCILastError()),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    while(1)
    {
        /*取日志配置表需要归档的对象*/
        memset(&sdb_app_rzpz,0,sizeof(sdb_app_rzpz));
        iRet = DBFetch(cur, SD_APP_RZPZ, NUMELE(SD_APP_RZPZ), &sdb_app_rzpz, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }

        trim(sdb_app_rzpz.dxlx);
        trim(sdb_app_rzpz.czdx1);
        trim(sdb_app_rzpz.cztj);
    
        if( strncmp(sdb_app_rzpz.dxlx,"1",1)==0 )        /*数据库表清理*/
        {
            /*组织清理的SQL*/
            memset(sRunSql,0,sizeof(sRunSql));
            trim(sdb_app_rzpz.czdx1);
            sprintf(sRunSql, "DELETE FROM %s WHERE 1=1 ",sdb_app_rzpz.czdx1);
        
            /*查询清理表对应的历史表*/
            iFlag = 0;
            memset(sHisTable,0,sizeof(sHisTable));
            snprintf( sSql1, sizeof( sSql1 ), "SELECT czdx2 FROM app_rzpz\
                WHERE ssyy='%s'AND czlx='1' AND dxlx='1' AND czdx1='%s'", sYybs, sdb_app_rzpz.czdx1);
            iRet = DBSelectToMultiVar( sErrmsg, sSql1, sHisTable ) ;
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                DCIFreeCursor(cur);
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }

            if ( iRet == 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("未查询到对应的历史表,直接清理"),"DEBUG");
                iFlag = 1;
            }
            memset(sCurSql,0,sizeof(sCurSql));
            sprintf(sCurSql, "SELECT COUNT(*) FROM %s WHERE 1=1 ",sdb_app_rzpz.czdx1);
            memset(sHisSql,0,sizeof(sHisSql));
            sprintf(sHisSql, "SELECT COUNT(*) FROM %s WHERE 1=1 ",sHisTable);
        
            /*统计条件个数*/
            iTjs = 0;
            iTjs = fprv_countchar(sdb_app_rzpz.cztj,'|');
            /*取条件语句*/
            for(i=0;i<iTjs;i++)
            {
                memset(sTmpSql,0,sizeof(sTmpSql));
                fprv_getSubItem(sdb_app_rzpz.cztj,i,"|",sTmpSql);
            
                /*单个SQL条件*/
                memset(sType,0,sizeof(sType));
                memset(sColName,0,sizeof(sColName));
                memset(sLopper,0,sizeof(sLopper));
                memset(sColKey,0,sizeof(sColKey));
                memset(sOP,0,sizeof(sOP));
                fprv_getSubItem(sTmpSql,0,";",sType);
                fprv_getSubItem(sTmpSql,1,";",sColName);
                fprv_getSubItem(sTmpSql,2,";",sLopper);
                fprv_getSubItem(sTmpSql,3,";",sColKey);
            
                if(i < iTjs-1)
                {
                    fprv_getSubItem(sTmpSql,4,";",sOP);
                }
            
                /*查询参数控制表*/
                trim(sColKey);
                /* 20111010 modified by yangdong 增加对非键值任务处理 */
                if( sColKey[0] == 'K' )
                { 
                    memset(sColValue,0,sizeof(sColValue));
/* for test
                    snprintf( sSql1, sizeof( sSql1 ),"SELECT jdz FROM app_cskz WHERE csjz='%s'",sColKey );
*/
                    snprintf( sSql1, sizeof( sSql1 ),"SELECT 111 jdz FROM app_cskz WHERE csjz='%s'",sColKey );
                    iRet = DBSelectToVarChar( sErrmsg,  sColValue, sSql1 );

                    if ( iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                Fmtmsg("查询参数控制表失败,[%s]",DCILastError() ),"ERROR");
                        DCIRollback();
                        DCIFreeCursor(cur);
                        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    if ( iRet == 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("对应参数键值不存在,csjz=[%s]",sColKey),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_APP_SJGD_NOFUND,MSG_APP_SJGD_NOFUND);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                }
                else
                {
                     snprintf( sColValue, sizeof( sColValue ), "%s", sColKey );
                }
                trim(sColValue);
            
                if( i==0 )  /*第一个条件为保留天数*/
                {
                    iLsts = 0;
                    iColVaue = atoi(sColValue);
                    iLsts = 0 - iColVaue;
                
                    /*计算日期*/
                    iRet = 0;
                    memset(sQlqsrq,0,sizeof(sQlqsrq));
                    iRet=fprv_dateOffSet(sQlrq,iLsts);
                    sprintf(sQlqsrq, "%d", iRet);
                
                    memset(sWhsql,0,sizeof(sWhsql));
                    /* modified by yangdong 20111010 
                    sprintf(sWhsql, "AND %s='%s' %s", sColName,sGdqsrq,sOP);
                    */
                    sprintf(sWhsql, "AND %s<='%s' %s", sColName,sQlqsrq,sOP);
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                    memset(sDateSql,0,sizeof(sDateSql));
                    sprintf(sDateSql, "SELECT min(%s) FROM %s WHERE 1=1 %s ",\
                            sColName, sdb_app_rzpz.czdx1,sWhsql );
                    snprintf( sDateCol,  sizeof( sDateCol ), "%s", sColName );
                }
                else
                {
                    memset(sWhsql,0,sizeof(sWhsql));
                    if( strncmp(sType,"D",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%.2f%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else if( strncmp(sType,"I",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%d%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else
                        sprintf(sWhsql, " %s%s'%s'%s ", sColName,sLopper,sColValue,sOP);
                    
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                    strcat(sDateSql,sWhsql);
                }
            }
        
            if( iFlag==0 )
            {
                /*获取最早记录日期*/
                iRet = DBSelectToVarChar(sErrmsg, sMinDate, sDateSql);
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                           Fmtmsg("获取最小日期失败,[%s]",DCILastError()),"ERROR");
                    DCIFreeCursor(cur);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                iCount = 0;

                trim( sMinDate );
                if( strlen( sMinDate)  > 1 )
                {
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    sprintf( sBuf, " AND %s >= '%s'", sDateCol, sMinDate );
                    strcat ( sCurSql , sBuf );
                    strcat ( sHisSql , sBuf );
                }
                /*统计当前表记录数*/
                iCount = 0;
                iRet = DBSelectToVar(sErrmsg, &iCount , sCurSql );
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                           Fmtmsg("统计当前表记录数失败,[%s]",DCILastError() ),"ERROR");
                    DCIFreeCursor(cur);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }

                if( iCount > 0 )  /* 需清理记录 */
                {
                    /*统计历史表归档成功的记录数*/
                    iHisCount = 0;
                    iRet = DBSelectToVar(sErrmsg, &iHisCount , sHisSql);
                    if ( iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                             Fmtmsg("统计历史表记录数失败,[%s]",DCILastError()),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    /*比较当前表与历史表的记录数*/
                    if( iCount > iHisCount )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("未做归档,不能清理.iCount=[%d],iHisCount=[%d]",iCount,iHisCount),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_APP_SJQL_NOTGD,\
                                  Fmtmsg(MSG_APP_SJQL_NOTGD,sdb_app_rzpz.czdx1));
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    else
                    {
                        /*执行清理操作*/
                        iResult = 0;
                        iRet = 0;
                        iRet = DCIExecuteDirect( sRunSql );
                        if ( iRet < 0 )
                        {
                            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("清理[%s]失败,[%s],iRet=[%d]",\
                                 sdb_app_rzpz.czdx1,DCILastError() ,iRet),"ERROR");
                            DCIFreeCursor(cur);
                            DCIRollback();
                            fpub_SetMsg(lXmlhandle,MID_APP_SJQL_QLERR,MSG_APP_SJQL_QLERR);
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                    }
                }
            }
            else
            {
                /*执行清理操作*/
                iResult = 0;
                iRet = 0;
                iRet = DCIExecuteDirect( sRunSql );
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("清理[%s]失败,[%s],iRet=[%d]",\
                                 sdb_app_rzpz.czdx1,DCILastError() ,iRet),"ERROR");
                    DCIFreeCursor(cur);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle,MID_APP_SJQL_QLERR,MSG_APP_SJQL_QLERR);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
        }
        else        /*文件清理*/
        {
            memset(sSrcDir,0,sizeof(sSrcDir));
            trim(sdb_app_rzpz.czdx1);
            sprintf(sSrcDir, "%s/%s", getenv("HOME"),sdb_app_rzpz.czdx1);
            memset(sCmd,0,sizeof(sCmd));        /*文件进行清理*/
            /* modified by yangdong 20090921 */
            /*
            sprintf(sCmd, "rm -rf %s*", sSrcDir);
            system(sCmd);
            */

            iParas = 0;
            sprintf(sCmd, "rm -f %s*", sSrcDir);
            iParas = system( sCmd );
            if( iParas != 0 )
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"DEBUG");
            /* 
            if( ( ! WIFEXITED( iParas ) ) || ( WEXITSTATUS( iParas ) != 0 ) )
            {
                fpub_SetMsg(lXmlhandle, MID_SYS_RMAREFRESHRES, Fmtmsg( MSG_SYS_RMAREFRESHRES,"",0 )  );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            */
            /* end of mod */
        }
    }
    DCIFreeCursor(cur);
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/********************************************************************
组件函数名称: SApp_DataBackup
组件名称: 数据备份
组件功能: 日终数据备份处理
     
组件参数:
序号 参数名称   资源类别   缺省值    是否可空  参数说明
1    应用标识                           N


组件结果状态:
  结果状态码         结果说明
 
项 目 组: 
程 序 员: YangDong 
发布日期: 2009年6月
修改日期:
*********************************************************************/
IRESULT SApp_DataBackup(HXMLTREE lXmlhandle)
{
    char sYybs[8+1];
    char sTable[48+1];
    char sSql[2048];
    char sBackDir[128];
    APP_RZPZ sdb_app_rzpz;
  
    int    iParas;
    char    sBuf[256];
    char    sFullFileName[256];
    /* 20120203 modified by yangdong 变量长度调整
    char    sTmp[32];
    */
    char    sTmp[128];
    char    sCmd[512];
    long   lResult;
    int  iRet = -1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*组件参数检查*/
    COMP_PARACOUNTCHK(1)
            
    /*获取组件参数*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"应用标识");
    trim(sBuf);
    memset(sYybs,0,sizeof(sYybs));
    memcpy(sYybs,sBuf,sizeof(sYybs));
    
    /* 取平台日期和交易流水,拼文件名时使用 */
    memset( sTmp, 0, sizeof( sTmp ) );
    COMP_HARDGETXML( "/pub/zwrq", sTmp )
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML( "/pub/zhqzlsh", sBuf )
    strcat( sTmp, sBuf );
    trim( sTmp );
    
    /* 备份文件路径 */ 
    snprintf( sSql1, sizeof( sSql1 ), "SELECT jdz FROM APP_CSKZ WHERE csjz='K_APP_BACKDIR'" );
    iRet = DBSelectToVarChar(sErrmsg, sBackDir, sSql1);
    if ( iRet < 0 )  
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )  /* 默认存放在$HOME/file下 */   
    { 
        memset( sBackDir, 0x00, sizeof( sBackDir ) );
        memset(sBuf,0,sizeof(sBuf));
        sprintf( sBackDir, "%s/file/backup", getenv( "HOME" ) );
    }        
    trim( sBackDir );

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" 开始备份应用[%s] 备份路径[%s] ", sYybs, sBackDir ),"INFO" );
    
    /* 查询所有需要备份的库表 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_rzpz WHERE ssyy='%s'AND czlx='1' AND dxlx='1'",sYybs );
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
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("声明日终配置表游标错误,[%s]",DCILastError()),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    while(1)
    {
        memset( &sdb_app_rzpz, 0x00, sizeof( sdb_app_rzpz ) );
        /*取日志配置表需要归档的对象*/
        iRet = DBFetch(cur, SD_APP_RZPZ, NUMELE(SD_APP_RZPZ), &sdb_app_rzpz, sErrmsg );
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            /*DCIRollback(); deleted by chenxm 2015-1-7*/
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            break;
        }
        /* 备份文件名 库表名_平台日期_流水号 */
        memset( sSql, 0x00, sizeof( sSql ) );
        memset( sFullFileName, 0x00, sizeof( sFullFileName ) );
        sprintf( sSql, "SELECT * FROM %s WHERE 1=1", sTable );
        trim( sTable );
        sprintf( sFullFileName, "%s/%s_%s", sBackDir, sTable, sTmp );
        iRet=sql_UnloadToFile( sFullFileName,sSql,'|','\\', &lResult);
        if ( iRet != MID_SYS_SUCC )
        {
            DCIFreeCursor(cur);
            fpub_SetMsg(lXmlhandle,MID_APP_BACKUP_FAIL, MSG_APP_BACKUP_FAIL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("表[%s] 成功备份到文件[%s]", sTable, sFullFileName ),"INFO" );
    }
    DCIFreeCursor(cur);

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/********************************************************************
组件函数名称: SApp_DataRecover
组件名称: 数据恢复?组件功能: 
     
组件参数:
序号 参数名称   资源类别   缺省值    是否可空  参数说明
1    应用标识                           N


组件结果状态:
  结果状态码         结果说明
 
项 目 组: 
程 序 员: YangDong
发布日期: 2009年6月
修改日期:
*********************************************************************/
IRESULT SApp_DataRecover(HXMLTREE lXmlhandle)
{
    char sBuf[256];
    char sTable[256];
    char sFullFileName[256];
    int  iParas;
    int  iRet;
    long lResult;

    /*组件参数检查*/
    COMP_PARACOUNTCHK(2)
            
    /*获取组件参数*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"待恢复表名");
    trim(sBuf);
    memset(sTable,0,sizeof(sTable));
    memcpy(sTable,sBuf,sizeof(sTable));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"备份数据文件名");
    trim(sBuf);
    memset(sFullFileName,0,sizeof(sFullFileName));
    memcpy(sFullFileName,sBuf,sizeof(sFullFileName));
    
    if( iRet=sql_LoadFromFile( sFullFileName, sTable, '|', '\\', &lResult) != MID_SYS_SUCC )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("恢复失败,[%s]",DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_RECOVER_FAIL, MSG_APP_RECOVER_FAIL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/*********************************************************************
动态组件函数定义
组件函数名称:SApp_SysShell
组件名称:SApp_SysShell
组件功能:Shell命令运行调用
组件参数:
 序号 参数类型  参数名称    资源类别    缺省值  可空  参数说明
  1   1-输入    SHELL命令  416-解析字符串  N     具体命令字符串

组件结果状态:
  结果状态码         结果说明
  缺省

项 目 组: 
程 序 员: 
发布日期:
*********************************************************************/
IRESULT SApp_SysShell(HXMLTREE lXmlhandle)
{
    char sBuf[512];
    char sDate[9];
    char sTime[7];
    char sFileName[100];
    char sShellFile[100];
    char sShell[1024];
    char sResp[512];
    int  iParas;
    FILE *fp1,*fp2;
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)

    memset( sBuf, 0x00, sizeof( sBuf ) );
    memset( sShell, 0x00, sizeof( sShell ) );
    memset( sFileName, 0x00, sizeof( sFileName ) );
    memset( sDate, 0x00, sizeof( sDate ) );
    memset( sTime, 0x00, sizeof( sTime ) );
    memset( sResp, 0x00, sizeof( sResp ) );
    COMP_GETPARSEPARAS( 1, sShell, "SHELL命令行" )
    if (strlen(sShell) == 0)
    {
        fpub_SetMsg(lXmlhandle, MID_APP_SHELL_NULL, MSG_APP_SHELL_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*平台日期*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    pstrcopy( sDate, sBuf, sizeof( sDate ) );
    if ( 0 == sDate[0] ) 
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_PTRQ_NULL),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_PTRQ_NULL,MSG_APP_PTRQ_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*平台时间*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_SYSTIME, sBuf);
    pstrcopy( sTime, sBuf, sizeof( sTime ) );

    /* modify by yr 20121018 */
    sprintf(sFileName, "%s/tmp/shell_%s_%s.log", getenv("HOME"), sDate, sTime);
    sprintf(sShellFile, "%s/tmp/shell.sh", getenv("HOME"));
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, Fmtmsg("运行shell--[%s] > [%s] 2>&1", sShell, sFileName),"INFO");
    
    fp1 = NULL;
    fp2 = NULL;
    fp1 = fopen(sShellFile, "w+");
    if ( fp1 == NULL )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("打开文件失败shell.sh,error=[%s]",strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("打开文件失败"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    iParas=chmod(sShellFile, 0777);
    /*iParas=chmod(sShellFile, S_IXUSR);
    iParas=chmod(sShellFile, S_IXGRP);
    iParas=chmod(sShellFile, S_IRUSR); 
    iParas=chmod(sShellFile, S_IWUSR);
    iParas=chmod(sShellFile, S_IXUSR);
    iParas=chmod(sShellFile, S_IRGRP);
    iParas=chmod(sShellFile, S_IWGRP);
    iParas=chmod(sShellFile, S_IXGRP);
    iParas=chmod(sShellFile, S_IROTH);
    iParas=chmod(sShellFile, S_IWOTH);
    iParas=chmod(sShellFile, S_IXOTH);*/
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, Fmtmsg("[%d]chmod[%d]errno",iParas,errno),"INFO");
    
    fprintf(fp1, "cd $HOME/file/shell/ \n");
    fprintf(fp1, "%s >%s 2>&1 \n", sShell, sFileName);
    fclose(fp1);
    iParas=0;
    iParas=system(sShellFile);
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG, Fmtmsg("[%d]iParas",iParas),"DEBUG");

    fp2 = fopen(sFileName, "rt");
    if ( fp2 == NULL )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("生成结果文件失败file=[%s],error=[%s]",sFileName,strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("打开文件失败"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    fread(sResp, sizeof(sResp)-1, 1, fp2);
    trim(sResp);
    fclose(fp2);
    /*if( iParas == -1 || iParas == 127 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG, "SHELL运行失败", "ERR");
        fpub_SetMsg(lXmlhandle, MID_APP_SHELL_SB, MSG_APP_SHELL_SB );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }*/
    COMP_HARDSETXML( XMLNM_APP_RESP_RESPMSG, sResp );
    COMP_HARDSETXML( XMLNM_APP_RESP_WJMC, sFileName );

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
