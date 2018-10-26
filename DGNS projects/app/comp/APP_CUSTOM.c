/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V4.1.0.1
操作系统:
文件名称:
文件描述:通用应用平台组件集合
项 目 组:
程 序 员: CHENSY 
发布日期:
修    订: 杨东
修改日期: 20090708

修改日期: 20111222
修    订: 杨东
修订内容: 签约修改判断

修改日期: 20130220
修    订: 杨东
修订内容: 签约模式增加 4-业务编号+用户号 
          修改签约模式 2-产品代码+用户号 为默认
          增加查询条件

修改日期: 20140910
修    订: 杨东
修订内容: DCI改造
*********************************************************************/
#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
       <root>\
       <soname>APP_CUSTOM.so</soname>\
       <sosrcname>APP_CUSTOM.c</sosrcname>\
       <sonote>客户签约通用组件集合</sonote>\
       <version>\
       <rec ver=\"2.0.1.1\" modify=\"2010-4-1 10:08\" programer=\"YangDong\" filesize=\"1244135\">HS-AgentV2.0整理</rec>\
       <rec ver=\"2.1.0.1\" modify=\"2011-11-01  10:50\" programer=\"S..C\" filesize=\"1462110\">HS-AgentV2.1改造</rec>\
       <rec ver=\"2.1.0.2\" modify=\"2011-12-22  10:50\" programer=\"S..C\" filesize=\"1462110\">HS-AgentV2.1改造</rec>\
       <rec ver=\"2.1.0.3\" modify=\"2013-02-20  10:50\" programer=\"YangDong\" filesize=\"1462110\">增加签约模式,扩充查询条件</rec>\
       <rec ver=\"4.1.0.1\" modify=\"2014-09-10  10:50\" programer=\"YangDong\" filesize=\"1462110\">DCI改造</rec>\
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

/************************************************************************
动态组件函数定义
组件函数名称:SApp_InsCUSTOM
组件名称:SApp_InsCUSTOM
组件功能:登记公共签约关系表操作
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
int SApp_InsCUSTOM(HXMLTREE lXmlhandle)
{
    APP_KHXX sdb_app_khxx;
    APP_KHCPQY sdb_app_khcpqy;
    char sPkey[20+1];
    char sSignStat[1+1];  /* 签约状态 */
    char sXybh[16+1];     /* 协议编号 */
    char sRunKhxxSql[512];
    char sSetKhxxSql[2048];
    char sRunQyxxSql[512];
    char sWhere[512];
    char sErrmsg[512];
    int iCount;
    
    int  i,iResult=0;
    long iseqno=0;
    char sbuf[255];
    char sSignType[2];
    int  iSqlKhxxlen=0;
    int  iSqlQyxxlen=0;
    int  iRet = -1;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    memset(&sdb_app_khcpqy,0,sizeof(sdb_app_khcpqy));
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJLX, sbuf );
    pstrcopy( sdb_app_khcpqy.zjlx, sbuf,sizeof( sdb_app_khcpqy.zjlx ) );
    if ( 0 == sdb_app_khcpqy.zjlx[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->操作拒绝:证件类型不允许为空!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJLX_ISNULL,MSG_CUSTOM_ZJLX_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJHM, sbuf);
    pstrcopy( sdb_app_khcpqy.zjhm, sbuf,sizeof( sdb_app_khcpqy.zjhm ) );
    if ( 0 ==  sdb_app_khcpqy.zjhm[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->操作拒绝:证件号码不允许为空!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJHM_ISNULL,MSG_CUSTOM_ZJHM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    /* ---------- 判断客户是否已签约 begin ---------- */
    /* 产品代码 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CPDM , sbuf );
    pstrcopy( sdb_app_khcpqy.cpdm, sbuf,sizeof( sdb_app_khcpqy.cpdm ) );
    if ( 0 == sdb_app_khcpqy.cpdm[0])
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;    
    }
    trim(sdb_app_khcpqy.cpdm);
      
    /* 用户号 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1 , sbuf );
    pstrcopy( sdb_app_khcpqy.yhh1, sbuf,sizeof( sdb_app_khcpqy.yhh1 ) );
    trim(sdb_app_khcpqy.yhh1);
    
    /* 银行帐号 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH , sbuf );
    pstrcopy( sdb_app_khcpqy.qyzh, sbuf,sizeof( sdb_app_khcpqy.qyzh ) );
    trim(sdb_app_khcpqy.qyzh);

    /*第三方账号*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD1,sbuf );
    pstrcopy( sdb_app_khcpqy.extfld1,sbuf,sizeof( sdb_app_khcpqy.extfld1));
    trim(sdb_app_khcpqy.extfld1);

    /*终端号信息*/
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD2,sbuf );
    pstrcopy( sdb_app_khcpqy.extfld2,sbuf,sizeof( sdb_app_khcpqy.extfld2));
    trim(sdb_app_khcpqy.extfld2);
    
    /* 主机客户编号 */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJKHBH  , sbuf );
    pstrcopy( sdb_app_khxx.zjkhbh, sbuf,sizeof( sdb_app_khxx.zjkhbh ) );
    trim(sdb_app_khxx.zjkhbh);
    
    /* 系统支持签约模式 */
    memset(sSignType, 0, sizeof(sSignType));
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML( XMLNM_APP_CPXX_QYMS, sbuf );
    pstrcopy( sSignType, sbuf,sizeof( sSignType ) );
    trim(sSignType);
    
    iCount=0;
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("签约处理：产品代码[%s], 帐号[%s], 用户号[%s]",\
        sdb_app_khcpqy.cpdm, sdb_app_khcpqy.qyzh, sdb_app_khcpqy.yhh1),"DEBUG");
    
    memset( sSignStat, 0x00, sizeof( sSignStat ) );
    memset( sXybh, 0x00, sizeof( sXybh ) );
    memset( sWhere, 0x00, sizeof( sWhere ) );
    memset( sRunQyxxSql, 0x00, sizeof( sRunQyxxSql ) );
    memset( sSql1, 0x00, sizeof( sSql1 ) );

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("签约状态[%s],签约模式[%s]",sSignStat,sSignType),"DEBUG");
    /* 产品代码+银行帐号唯一 */
    if ( sSignType[0] == '1' )
    {
        /* 银行帐号不能为空 */
        if ( 0 == sdb_app_khcpqy.qyzh[0] )
        {
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        snprintf( sWhere, sizeof( sWhere ), "WHERE qyzh = '%s' AND  cpdm = '%s' ", \
                       sdb_app_khcpqy.qyzh, sdb_app_khcpqy.cpdm );
            
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE qyzh = '%s' AND cpdm ='%s'",\
                    sdb_app_khcpqy.qyzh , sdb_app_khcpqy.cpdm);
    }
    else /* 产品代码+银行帐号+用户编号唯一 签约类型3 */
    if ( sSignType[0] == '3' )
    {
        /* 银行帐号不能为空 */
        if ( 0 == sdb_app_khcpqy.qyzh[0] )
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }

        /* 用户编号不能为空 */
        if ( 0 == sdb_app_khcpqy.yhh1[0] )
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        snprintf( sWhere, sizeof( sWhere ), "WHERE yhh1= '%s' AND qyzh = '%s'  AND cpdm = '%s' ",\
                      sdb_app_khcpqy.yhh1,sdb_app_khcpqy.qyzh, sdb_app_khcpqy.cpdm );

        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE qyzh = '%s' AND yhh1 = '%s' AND cpdm ='%s'",\
                    sdb_app_khcpqy.qyzh ,sdb_app_khcpqy.yhh1 ,sdb_app_khcpqy.cpdm);
    }
    /* added by yangdong 20130220 需求单编号201302200005  增加签约控制模式  */
    else /* 业务编号+用户编号唯一 */
    if ( sSignType[0] == '4' )
    {
        /* 用户编号不能为空 */
        if ( 0 == sdb_app_khcpqy.yhh1[0] )
        {
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        snprintf( sWhere, sizeof( sWhere ), "WHERE yhh1= '%s'  AND ywbh = '%s' ",\
                                   sdb_app_khcpqy.yhh1, sdb_app_khcpqy.ywbh );

        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE yhh1 = '%s' AND ywbh='%s'",sdb_app_khcpqy.yhh1 ,sdb_app_khcpqy.ywbh );
    }
    else
    /* 产品代码+用户编号唯一  默认值*/
    {
        /* 用户编号不能为空 */
        if ( 0 == sdb_app_khcpqy.yhh1[0] )
        {
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        snprintf( sWhere,sizeof( sWhere ), "WHERE yhh1= '%s'  AND cpdm = '%s' ",\
                                   sdb_app_khcpqy.yhh1, sdb_app_khcpqy.cpdm );

        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy \
                    WHERE yhh1 = '%s' AND cpdm='%s'",sdb_app_khcpqy.yhh1 ,sdb_app_khcpqy.cpdm);
    }

    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sSignStat, sXybh ) ;
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 未签约或者签约状态不正常(客户信息处理,签约处理) */
    if (  iRet < 1 || sSignStat[0] != '0'  )        
    {
        DCIBegin();
        if( sSignStat[0] != '0' )  /* 签约状态不正常，则删除记录后重新插入签约表 */
        {
            memset( sRunQyxxSql, 0x00, sizeof( sRunQyxxSql ) );
            sprintf( sRunQyxxSql, " DELETE app_khcpqy %s", sWhere );
            iRet = DCIExecuteDirect( sRunQyxxSql );
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
        }

        /* ---------- 判断客户基本信息表中是否存在相应记录 begin ---------- */
        memset(&sdb_app_khxx,0,sizeof(sdb_app_khxx));
        /* 获取客户编号 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT khbh FROM app_khxx \
            WHERE zjlx ='%s' and zjhm ='%s'", sdb_app_khcpqy.zjlx ,sdb_app_khcpqy.zjhm );
        iRet = DBSelectToMultiVar( sErrmsg, sSql1,sdb_app_khcpqy.khbh) ;
        if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* 不存在则登记客户信息表 */    
        if ( iRet == 0 )
        {
            /* 生成客户编号 */
            if ( fprv_getSeqno("K_KHBH", &iseqno) < 0)
            {
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("-->生成客户编号编号失败,pkey=[%s],xybh=[%d]",\
                    "K_KHBH",iseqno),"ERROR");
                DCIRollback();
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_XYBH,Fmtmsg(MSG_CUSTOM_XYBH));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;
            }
            memset(sdb_app_khxx.khbh, 0, sizeof(sdb_app_khxx.khbh));
            sprintf(sdb_app_khxx.khbh, "%d",iseqno);
            sprintf(sdb_app_khcpqy.khbh, "%d",iseqno);
            trim(sdb_app_khxx.khbh);
            trim(sdb_app_khcpqy.khbh);
            if ( 0 == sdb_app_khxx.khbh[0] ) 
            {
                DCIRollback();
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->操作拒绝:客户编号不允许为空!"),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_KHBH_ISNULL,MSG_CUSTOM_KHBH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;
            }
            /* 客户名称 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_KHXM   ,sbuf  );
            pstrcopy( sdb_app_khxx.khxm, sbuf,sizeof( sdb_app_khxx.khxm ) );
            /* 英文名称 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YWXM   ,sbuf );
            pstrcopy( sdb_app_khxx.ywxm, sbuf,sizeof( sdb_app_khxx.ywxm ) );
            /* 别名 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_BM , sbuf );
            pstrcopy( sdb_app_khxx.bm, sbuf,sizeof( sdb_app_khxx.bm ) );
            /* 客户类型 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_KHLX   ,sbuf  );
            pstrcopy( sdb_app_khxx.khlx, sbuf,sizeof( sdb_app_khxx.khlx ) );
            /* 主机客户编号 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZJKHBH ,sbuf );
            pstrcopy( sdb_app_khxx.zjkhbh, sbuf,sizeof( sdb_app_khxx.zjkhbh ) );
            /* 证件类型 */
            memcpy( sdb_app_khxx.zjlx,sdb_app_khcpqy.zjlx ,sizeof(sdb_app_khxx.zjlx)   );
            /* 证件号码 */
            memcpy( sdb_app_khxx.zjhm,sdb_app_khcpqy.zjhm ,sizeof(sdb_app_khxx.zjhm)   );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_CSNY   ,sbuf  );
            pstrcopy( sdb_app_khxx.csny, sbuf,sizeof( sdb_app_khxx.csny ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SEX  ,sbuf  );
            pstrcopy( sdb_app_khxx.sex, sbuf,sizeof( sdb_app_khxx.sex ) );
            /* 默认国籍 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GJ  ,sbuf   );
            pstrcopy( sdb_app_khxx.gj, sbuf,sizeof( sdb_app_khxx.gj ) );
            trim(sdb_app_khxx.gj);
            if ( strlen(sdb_app_khxx.gj) <=0 )
            {
                strcpy(sdb_app_khxx.gj, "CHN");
            }
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HK     ,sbuf  );
            pstrcopy( sdb_app_khxx.hk, sbuf,sizeof( sdb_app_khxx.hk ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HYZK   ,sbuf  );
            pstrcopy( sdb_app_khxx.hyzk, sbuf,sizeof( sdb_app_khxx.hyzk ) );
            /* 默认婚姻状况 */
            trim(sdb_app_khxx.hyzk);
            if ( strlen(sdb_app_khxx.hyzk) <=0 )
            {
                strcpy(sdb_app_khxx.hyzk, "9");
            }
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_JYCD   ,sbuf  );
            pstrcopy( sdb_app_khxx.jycd, sbuf,sizeof( sdb_app_khxx.jycd ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZY     ,sbuf  );
            pstrcopy( sdb_app_khxx.zy, sbuf,sizeof( sdb_app_khxx.zy ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZW     ,sbuf   );
            pstrcopy( sdb_app_khxx.zw, sbuf,sizeof( sdb_app_khxx.zw ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SRQK   ,sbuf   );
            sdb_app_khxx.srqk=atof(sbuf);
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDZ   ,sbuf  );
            pstrcopy( sdb_app_khxx.gsdz, sbuf,sizeof( sdb_app_khxx.gsdz ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSYB   ,sbuf  );
            pstrcopy( sdb_app_khxx.gsyb, sbuf,sizeof( sdb_app_khxx.gsyb ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDH   ,sbuf  );
            pstrcopy( sdb_app_khxx.gsdh, sbuf,sizeof( sdb_app_khxx.gsdh ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDZ   ,sbuf );
            pstrcopy( sdb_app_khxx.zzdz, sbuf,sizeof( sdb_app_khxx.zzdz ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZYB   ,sbuf  );
            pstrcopy( sdb_app_khxx.zzyb, sbuf,sizeof( sdb_app_khxx.zzyb ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDH   ,sbuf  );
            pstrcopy( sdb_app_khxx.zzdh, sbuf,sizeof( sdb_app_khxx.zzdh ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YJDZLX ,sbuf );
            pstrcopy( sdb_app_khxx.yjdzlx, sbuf,sizeof( sdb_app_khxx.yjdzlx ) );
            /* 默认邮寄地址类型 */
            trim(sdb_app_khxx.yjdzlx);
            if ( strlen(sdb_app_khxx.yjdzlx) <=0 )
            {
                strcpy(sdb_app_khxx.yjdzlx, "0");
            }
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SJHM   ,sbuf  );
            pstrcopy( sdb_app_khxx.sjhm, sbuf,sizeof( sdb_app_khxx.sjhm ) );
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_Email  ,sbuf );
            pstrcopy( sdb_app_khxx.memail, sbuf,sizeof( sdb_app_khxx.memail ) );
            strcpy(sdb_app_khxx.bz,"0");
            
            iRet = DBInsert("app_khxx", SD_APP_KHXX, NUMELE(SD_APP_KHXX), &sdb_app_khxx, sErrmsg);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg(" khbh[%s] zjlx[%s] zjhm[%s]",\
                    sdb_app_khcpqy.khbh, sdb_app_khcpqy.zjlx, sdb_app_khcpqy.zjhm ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_INS_KHXX,Fmtmsg(MSG_CUSTOM_INS_KHXX));
                DCIRollback();
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPSTATUS_FAIL;
            }
        }
        /* 存在则更新客户信息表 */
        else
        {          
            /* by yr 20120830 */
            trim(sdb_app_khcpqy.khbh);
              
            iSqlKhxxlen=0;
            memset(sSetKhxxSql,0,sizeof(sSetKhxxSql));
            /* 客户标志 */
            sprintf(sSetKhxxSql+iSqlKhxxlen, "  bz='%s'","0");
            iSqlKhxxlen=strlen(sSetKhxxSql);
                  
            memset(&sdb_app_khxx, 0, sizeof(sdb_app_khxx));
            /* 客户姓名 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_KHXM  ,sbuf  );
            pstrcopy( sdb_app_khxx.khxm, sbuf,sizeof( sdb_app_khxx.khxm ) );
            trim(sdb_app_khxx.khxm);
            if ( strlen(sdb_app_khxx.khxm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,khxm='%s'",sdb_app_khxx.khxm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 英文名称 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YWXM   ,sbuf   );
            pstrcopy( sdb_app_khxx.ywxm, sbuf, sizeof( sdb_app_khxx.ywxm ) );
            trim(sdb_app_khxx.ywxm);
            if ( strlen(sdb_app_khxx.ywxm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,ywxm='%s'",sdb_app_khxx.ywxm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 别名 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_BM ,sbuf  );
            pstrcopy( sdb_app_khxx.bm, sbuf, sizeof( sdb_app_khxx.bm ) );
            trim(sdb_app_khxx.bm);
            if ( strlen(sdb_app_khxx.bm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,bm='%s'",sdb_app_khxx.bm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 主机客户编号 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZJKHBH ,sbuf );
            pstrcopy( sdb_app_khxx.zjkhbh, sbuf, sizeof( sdb_app_khxx.zjkhbh ) );
            trim(sdb_app_khxx.zjkhbh);
            if ( strlen(sdb_app_khxx.zjkhbh) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zjkhbh='%s'",sdb_app_khxx.zjkhbh);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 出生年月 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_CSNY ,sbuf  );
            pstrcopy( sdb_app_khxx.csny, sbuf, sizeof( sdb_app_khxx.csny ) );
            trim(sdb_app_khxx.csny);
            if ( strlen(sdb_app_khxx.csny) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,csny='%s'",sdb_app_khxx.csny);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 性别 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SEX , sbuf );
            pstrcopy( sdb_app_khxx.sex, sbuf, sizeof( sdb_app_khxx.sex ) );
            trim(sdb_app_khxx.sex);
            if ( strlen(sdb_app_khxx.sex) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,sex='%s'",sdb_app_khxx.sex);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 国籍 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GJ , sbuf  );
            pstrcopy( sdb_app_khxx.gj, sbuf, sizeof( sdb_app_khxx.gj ) );
            trim(sdb_app_khxx.gj);
            if ( strlen(sdb_app_khxx.gj) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gj='%s'",sdb_app_khxx.gj);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 户口 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HK  , sbuf );
            pstrcopy( sdb_app_khxx.hk, sbuf, sizeof( sdb_app_khxx.hk ) );
            trim(sdb_app_khxx.hk);
            if ( strlen(sdb_app_khxx.hk) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,hk='%s'",sdb_app_khxx.hk);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 婚姻状况 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_HYZK   ,sbuf  );
            pstrcopy( sdb_app_khxx.hyzk, sbuf, sizeof( sdb_app_khxx.hyzk ) );
            trim(sdb_app_khxx.hyzk);
            if ( strlen(sdb_app_khxx.hyzk) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,hyzk='%s'",sdb_app_khxx.hyzk);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 教育程度 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_JYCD   ,sbuf  );
            pstrcopy( sdb_app_khxx.jycd, sbuf, sizeof( sdb_app_khxx.jycd ) );
            trim(sdb_app_khxx.jycd);
            if ( strlen(sdb_app_khxx.jycd) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,jycd='%s'",sdb_app_khxx.jycd);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 职业 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZY , sbuf );
            pstrcopy( sdb_app_khxx.zy, sbuf, sizeof( sdb_app_khxx.zy ) );
            trim(sdb_app_khxx.zy);
            if ( strlen(sdb_app_khxx.zy) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zy='%s'",sdb_app_khxx.zy);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 职务 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZW  ,sbuf );
            pstrcopy( sdb_app_khxx.zw, sbuf, sizeof( sdb_app_khxx.zw ) );
            trim(sdb_app_khxx.zw);
            if ( strlen(sdb_app_khxx.zw) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zw='%s'",sdb_app_khxx.zw);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 收入情况年 */
            memset(sbuf, 0, sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SRQK   ,sbuf   );
            trim(sbuf);
            if ( strlen(sbuf) >0 )
            {
                sdb_app_khxx.srqk=atof(sbuf);
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,srqk=%15.2f",sdb_app_khxx.srqk);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 公司地址 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDZ   ,sbuf );
            pstrcopy( sdb_app_khxx.gsdz, sbuf, sizeof( sdb_app_khxx.gsdz ) );
            trim(sdb_app_khxx.gsdz);
            if ( strlen(sdb_app_khxx.gsdz) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gsdz='%s'",sdb_app_khxx.gsdz);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 公司邮编 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSYB , sbuf  );
            pstrcopy( sdb_app_khxx.gsyb, sbuf, sizeof( sdb_app_khxx.gsyb ) );
            trim(sdb_app_khxx.gsyb);
            if ( strlen(sdb_app_khxx.gsyb) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gsyb='%s'",sdb_app_khxx.gsyb);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 公司电话 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_GSDH   , sbuf );
            pstrcopy( sdb_app_khxx.gsdh, sbuf, sizeof( sdb_app_khxx.gsdh ) );
            trim(sdb_app_khxx.gsdh);
            if ( strlen(sdb_app_khxx.gsdh) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,gsdh='%s'",sdb_app_khxx.gsdh);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 住宅地址 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDZ  ,sbuf );
            pstrcopy( sdb_app_khxx.zzdz, sbuf, sizeof( sdb_app_khxx.zzdz ) );
            trim(sdb_app_khxx.zzdz);
            if ( strlen(sdb_app_khxx.zzdz) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zzdz='%s'",sdb_app_khxx.zzdz);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 住宅邮编 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZYB   ,sbuf  );
            pstrcopy( sdb_app_khxx.zzyb, sbuf, sizeof( sdb_app_khxx.zzyb ) );
            trim(sdb_app_khxx.zzyb);
            if ( strlen(sdb_app_khxx.zzyb) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zzyb='%s'",sdb_app_khxx.zzyb);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 住宅电话 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_ZZDH  , sbuf );
            pstrcopy( sdb_app_khxx.zzdh, sbuf, sizeof( sdb_app_khxx.zzdh ) );
            trim(sdb_app_khxx.zzdh);
            if ( strlen(sdb_app_khxx.zzdh) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,zzdh='%s'",sdb_app_khxx.zzdh);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 邮寄类型 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_YJDZLX ,sbuf );
            pstrcopy( sdb_app_khxx.yjdzlx, sbuf, sizeof( sdb_app_khxx.yjdzlx ) );
            trim(sdb_app_khxx.yjdzlx);
            if ( strlen(sdb_app_khxx.yjdzlx) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,yjdzlx='%s'",sdb_app_khxx.yjdzlx);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 手机号码 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_SJHM   , sbuf  );
            pstrcopy( sdb_app_khxx.sjhm, sbuf, sizeof( sdb_app_khxx.sjhm ) );
            trim(sdb_app_khxx.sjhm);
            if ( strlen(sdb_app_khxx.sjhm) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,sjhm='%s'",sdb_app_khxx.sjhm);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 电子邮件 */
            memset(sbuf,0,sizeof(sbuf));
            COMP_SOFTGETXML( XMLNM_APP_CUSTOM_Email  , sbuf  );
            pstrcopy( sdb_app_khxx.memail, sbuf, sizeof( sdb_app_khxx.memail ) );
            trim(sdb_app_khxx.memail);
            if ( strlen(sdb_app_khxx.memail) > 0 )
            {
                sprintf(sSetKhxxSql+iSqlKhxxlen, " ,memail='%s'",sdb_app_khxx.memail);
                iSqlKhxxlen=strlen(sSetKhxxSql);
            }
            /* 更新记录 --B*/
            memset(sRunKhxxSql, 0, sizeof(sRunKhxxSql));
            snprintf(sRunKhxxSql,sizeof(sRunKhxxSql),"update app_khxx set %s where zjlx ='%s' and zjhm ='%s'",\
                                     sSetKhxxSql, sdb_app_khcpqy.zjlx, sdb_app_khcpqy.zjhm );
            iRet = DCIExecuteDirect( sRunKhxxSql );
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->操作拒绝:更新客户信息失败 证件类型[%s],\
                    证件号码[%s]\n[%s],[%s]",sdb_app_khcpqy.zjlx,sdb_app_khcpqy.zjhm, sRunKhxxSql, DCILastError() ),"ERROR");
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_KHBH_EQUAL,MSG_CUSTOM_KHBH_EQUAL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;
            }
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("签约处理：更新客户信息[%s]",sRunKhxxSql),"DEBUG");
            /* 更新记录 --E*/
         }
        /* ---------- 判断客户基本信息表中是否存在相应记录 end   ---------- */
        
        /* 生成协议序列值 --B*/
        memset(sPkey, 0, sizeof(sPkey));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_PKEY, sPkey);
        trim(sPkey);
        if ( fprv_getSeqno(sPkey, &iseqno) < 0)
        {
            DCIRollback();
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->生成协议编号失败,pkey=[%s],xybh=[%d]",sPkey,iseqno),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_XYBH,Fmtmsg(MSG_CUSTOM_XYBH));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        COMP_HARDSETXML(XMLNM_APP_CUSTOM_XYXH, itoa(iseqno));
        /* 生成协议序列值 --E*/
        
        COMP_SOFTGETXML( XMLNM_APP_CUSTOM_XYXH   ,sdb_app_khcpqy.xybh   );
        trim(sdb_app_khcpqy.xybh);
        
        /* 业务编号 */    
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH     , sdb_app_khcpqy.ywbh     );
        trim(sdb_app_khcpqy.ywbh);
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHLX     , sdb_app_khcpqy.zhlx     );
        /*
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH     , sdb_app_khcpqy.qyzh     );
        */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHHM     , sdb_app_khcpqy.zhhm     );
        trim(sdb_app_khcpqy.zhhm);
        if ( strlen(sdb_app_khcpqy.zhhm) <=0 )
        {
            trim(sdb_app_khxx.khxm);
            strcpy(sdb_app_khcpqy.zhhm, sdb_app_khxx.khxm);
        }
        /* 默认签约类型 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYLX     , sdb_app_khcpqy.qylx     );
        trim( sdb_app_khcpqy.qylx );
        if ( strlen(sdb_app_khcpqy.qylx) <= 0)
            strcpy(sdb_app_khcpqy.qylx, "0");
                
        /* 默认客户经理 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJL     , sdb_app_khcpqy.khjl     );
        trim(sdb_app_khcpqy.khjl);
        if ( strlen(sdb_app_khcpqy.khjl) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_KHJL     , sdb_app_khcpqy.khjl     );
        }
        /* 合约开始日期 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYKSRQ   , sdb_app_khcpqy.hyksrq   );
        trim(sdb_app_khcpqy.hyksrq);
        if ( strlen(sdb_app_khcpqy.hyksrq) <= 0)
        {
            sprintf(sdb_app_khcpqy.hyksrq, "%s", GetSysDate());
        }
        /* 合约结束日期 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYJSRQ   , sdb_app_khcpqy.hyjsrq   );
        /* 默认开通渠道 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KTQD     , sdb_app_khcpqy.ktqd     );
        if ( strlen(sdb_app_khcpqy.ktqd) <=0 )
        {
            /* 默认开通渠道 ALL */
            sprintf(sdb_app_khcpqy.ktqd,"ALL");
        }
        
        /* 默认主办机构 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG     , sdb_app_khcpqy.bljg     );
        trim(sdb_app_khcpqy.bljg);
        if ( strlen(sdb_app_khcpqy.bljg) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG     , sdb_app_khcpqy.bljg     );
        }
        
        /* 默认主办柜员 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY     , sdb_app_khcpqy.blgy     );
        trim(sdb_app_khcpqy.blgy);
        if ( strlen(sdb_app_khcpqy.blgy) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY     , sdb_app_khcpqy.blgy     );
        }
        
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ     , sdb_app_khcpqy.blrq     );
        /* 默认办理日期 */
        trim(sdb_app_khcpqy.blrq);
        if ( strlen(sdb_app_khcpqy.blrq) <=0 )
        {
              COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ     , sdb_app_khcpqy.blrq     );
        }
        /*
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1     , sdb_app_khcpqy.yhh1     );
        */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH2     , sdb_app_khcpqy.yhh2     );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH3     , sdb_app_khcpqy.yhh3     );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DXTZBZ   , sdb_app_khcpqy.dxtzbz   );
        /* 默认短信标志 */
        trim(sdb_app_khcpqy.dxtzbz);
        if ( strlen(sdb_app_khcpqy.dxtzbz) <=0 )
        {
                strcpy(sdb_app_khcpqy.dxtzbz, "0");
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHZDED   , sbuf   );
        sdb_app_khcpqy.zhzded=atof(sbuf);

        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJG, sdb_app_khcpqy.khjg );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHMC, sdb_app_khcpqy.yhmc );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHLX, sdb_app_khcpqy.yhlx );
    
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJLX, sdb_app_khcpqy.dlzjlx );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJHM, sdb_app_khcpqy.dlzjhm );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHYB, sdb_app_khcpqy.yhyb );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDH, sdb_app_khcpqy.yhdh );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDZ, sdb_app_khcpqy.yhdz );
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_JYBZ, sdb_app_khcpqy.jybz );
		memset( sbuf, 0x00, sizeof( sbuf ) );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZDXE, sbuf );
		sdb_app_khcpqy.kkzdxe = atof( sbuf );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZQ, sdb_app_khcpqy.kkzq );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YDKKRQ, sdb_app_khcpqy.ydkkrq );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZT, sdb_app_khcpqy.kkzt );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKRQ, sdb_app_khcpqy.kkrq );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD4  , sdb_app_khcpqy.extfld4  );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD5  , sdb_app_khcpqy.extfld5  );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD6  , sdb_app_khcpqy.extfld6  );
		memset( sbuf, 0x00, sizeof( sbuf ) );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD1  ,sbuf );
		pstrcopy( sdb_app_khcpqy.extfld1, sbuf,sizeof( sdb_app_khcpqy.extfld1 ) );	
		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s][%s]",sbuf,sdb_app_khcpqy.extfld1),"ERROR")
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD2  , sdb_app_khcpqy.extfld2  );
		COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD3  , sdb_app_khcpqy.extfld3  );
        strcpy(sdb_app_khcpqy.qyzt,"0");

        iRet = DBInsert("app_khcpqy", SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy, sErrmsg);
        if ( iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_INS_KHQY,Fmtmsg(MSG_CUSTOM_INS_KHQY));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("('%s','%s')",sdb_app_khcpqy.xybh,sdb_app_khcpqy.cpdm),"ERROR");
            return COMPRET_FAIL;
        }
        /* 提交事务 */
        if ( DCICommit() !=MID_SYS_SUCC )
        {
            fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    /* 已签约且状态正常报错返回 */
    else if( sSignStat[0] == '0' )
    {    
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_QY,MSG_CUSTOM_QY);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    COMP_SOFTSETXML(XMLNM_APP_CUSTOM_XYBH  , sdb_app_khcpqy.xybh );

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0; 
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_UpdCUSTOM
组件名称:SApp_UpdCUSTOM
组件功能:更新公共签约关系表操作
         修改客户信息 以证件类型和证件号码为据
         修改签约关系，以产品代码＋协议编号为据
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
IRESULT SApp_UpdCUSTOM(HXMLTREE lXmlhandle)
{
    char sModType[1+1];          /* 修改类型  0 全部[默认] 1 客户信息 2 签约信息 */
    char sStrSet[512],sStrSetSql[2048],sSql[2048];
    APP_KHCPQY sdb_app_khcpqy;
    int iResult;
    char sbuf[255];
	char sbuf1[255];
    char sStrSetKhxxSql[2048];
    int  iRet = -1;
    
    int iSetFlag=0;
    int iSetKhxxFlag=0;
    int iSqlLen=0;
    fpub_InitSoComp(lXmlhandle);
    memset(sbuf,0,sizeof(sbuf));
    
    COMP_SOFTGETXML( XMLNM_APP_CUSTOM_XGLX,sbuf ); /* 修改类型 */
    pstrcopy( sModType, sbuf,sizeof( sModType ) );
    memset(&sdb_app_khcpqy, 0x00, sizeof(sdb_app_khcpqy));

    if( sModType[0] != '1' )  /* 除非只修改客户信息，否则 获取签约信息 */
    {
        /* 扣款日期,扣款状态,证件类型,证件号码,帐户号码, 用户号,
           产品代码,业务编号,协议编号,客户编号不可以修改 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG, sdb_app_khcpqy.bljg     );
        trim(sdb_app_khcpqy.bljg);
        if ( strlen(sdb_app_khcpqy.bljg) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG, sdb_app_khcpqy.bljg     );
        }
        
        /* 默认主办柜员:产品主办柜员 */
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY, sdb_app_khcpqy.blgy     );
        trim(sdb_app_khcpqy.blgy);
        if ( strlen(sdb_app_khcpqy.blgy) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY, sdb_app_khcpqy.blgy     );
        }
        
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ     , sdb_app_khcpqy.blrq     );
        /* 默认办理日期 */
        trim(sdb_app_khcpqy.blrq);
        if ( strlen(sdb_app_khcpqy.blrq) <=0 )
        {
            COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ     , sdb_app_khcpqy.blrq     );
        }
    
        memset(sbuf,0,sizeof(sbuf));
        memset(sStrSetSql,0,sizeof(sStrSetSql));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHLX,sbuf);
        if (strlen(sbuf) > 0)
        {
             memset(sStrSet, 0, sizeof(sStrSet));
             sprintf(sStrSet, "zhlx ='%s',", sbuf);
             strcat(sStrSetSql,sStrSet);
             iSetFlag=1;
        }

        /* added by yangdong 20140915 技术上不限制修改 */
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH,sbuf);
        if( strlen(sbuf) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "qyzh ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1,sbuf);
        if( strlen(sbuf) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhh1 ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        /* end of add */
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHHM,sbuf);
        if( strlen(sbuf) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zhhm ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYLX,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "qylx ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJL,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khjl ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYKSRQ,sbuf);
        if( strlen( sbuf ) > 0 )
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hyksrq ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYJSRQ,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hyjsrq ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KTQD,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "ktqd ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH2,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhh2 ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH3,sbuf);
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhh3 ='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHJG, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khjg='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHMC, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhmc='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHLX, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhlx='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJLX, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "dlzjlx='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DLZJHM, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "dlzjhm='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHYB, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhyb='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDH, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhdh='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHDZ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yhdz='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_JYBZ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "jybz='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZDXE, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "kkzdxe=%.2f,", atof( sbuf ) );
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KKZQ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "kkzq='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YDKKRQ, sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "ydkkrq='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
		memset(sbuf1,0,sizeof(sbuf1));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD1  , sbuf );
	    pstrcopy(sbuf1, sbuf,sizeof( sdb_app_khcpqy.extfld1 ) );
        if (strlen(sbuf1) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld1='%s',", sbuf1);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD2  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld2='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD3  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld3='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD4  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld4='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD5  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld5='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_EXTFLD6  , sbuf );
        if (strlen(sbuf) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "extfld6='%s',", sbuf);
            strcat(sStrSetSql,sStrSet);
            iSetFlag=1;
        }
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_DXTZBZ,sbuf);
        if (strlen(sbuf) > 0)
        {
          memset(sStrSet, 0, sizeof(sStrSet));
          sprintf(sStrSet, "dxtzbz ='%s',", sbuf);
          strcat(sStrSetSql,sStrSet);
          iSetFlag=1;
        }
        
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZHZDED,sbuf);
        if (strlen(sbuf) > 0)
        {
          memset(sStrSet, 0, sizeof(sStrSet));
          sprintf(sStrSet, "zhzded =%.2f,", atof(sbuf) );
          strcat(sStrSetSql,sStrSet);
          iSetFlag=1;
        }
    }
    if( sModType[0] != '2' )  /* 获取客户信息 */
    {
        /*  客户编号，证件类型，证件号码,出生年月 不可修改 */
        memset( sStrSetKhxxSql,0,sizeof( sStrSetKhxxSql ));
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHXM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khxm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWXM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "ywxm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "bm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_KHLX,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "khlx='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJKHBH,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zjkhbh='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }

        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CSNY,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "csny='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_SEX,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "sex='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GJ,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gj='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HK,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hk='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_HYZK,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "hyzk='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_JYCD,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "jycd='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZY,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zy='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZW,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zw='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_SRQK,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "srqk=%15.2f,", atof(sbuf) );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GSDZ,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gsdz='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GSYB,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gsyb='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_GSDH,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "gsdh='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZZDZ,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zzdz='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZZYB,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zzyb='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZZDH,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "zzdh='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YJDZLX,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "yjdzlx='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_SJHM,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "sjhm='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_Email,sbuf);
        if (strlen( sbuf ) > 0)
        {
            memset(sStrSet, 0, sizeof(sStrSet));
            sprintf(sStrSet, "memail='%s',", sbuf );
            strcat(sStrSetKhxxSql,sStrSet);
            iSetKhxxFlag=1;
        }
    }

    /* modified by 杨东 20111222 判断放在前面来 */
    if ( 0 == iSetKhxxFlag &&  0 == iSetFlag  )
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_SET_ISNULL,MSG_CUSTOM_SET_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;    
    }

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 修改模式为 修改客户信息或者是同时修改客户信息和签约信息时 */
    if( sModType[0] != '2' && iSetKhxxFlag == 1 )  /* 除非只修改签约信息，否则修改客户信息 */
    {
        /* 按证件类型和证件号码 修改客户信息 */
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJLX,sbuf);
        if ( 0 == sbuf[0] ) 
        {
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJLX_ISNULL,MSG_CUSTOM_ZJLX_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        memcpy(sdb_app_khcpqy.zjlx,sbuf,sizeof(sdb_app_khcpqy.zjlx ));    
      
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJHM,sbuf);
        if ( 0 == sbuf[0] ) 
        {
             DCIRollback();
             fpub_SetMsg(lXmlhandle,MID_CUSTOM_ZJHM_ISNULL,MSG_CUSTOM_ZJHM_ISNULL);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return -1;    
        }
        memcpy(sdb_app_khcpqy.zjhm, sbuf,sizeof(sdb_app_khcpqy.zjhm ));    

        /* 去除最后一个, */
        iSqlLen = strlen( sStrSetKhxxSql );
        sStrSetKhxxSql[ iSqlLen - 1 ] = '\0';

        memset( sSql, 0x00, sizeof( sSql ) );
        snprintf(sSql,sizeof(sSql),"update app_khxx set %s where zjlx= '%s' AND zjhm='%s' "\
                               ,sStrSetKhxxSql, sdb_app_khcpqy.zjlx, sdb_app_khcpqy.zjhm );
        iRet = DCIExecuteDirect(  sSql );
        if ( iRet < 0 )
        {
            DCIRollback();
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
            return -1;
        }
    } 
    if( sModType[0] != '1' && iSetFlag == 1 )  
    /* 除非只修改客户信息，否则按产品代码和协议编号更新签约表  */
    {
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CPDM,sbuf);
        if ( 0 == sbuf[0] ) 
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        memcpy(sdb_app_khcpqy.cpdm,sbuf,sizeof(sdb_app_khcpqy.cpdm));    
    
        memset(sbuf,0,sizeof(sbuf));
        COMP_SOFTGETXML(XMLNM_APP_CUSTOM_XYBH,sbuf);
        if ( 0 == sbuf[0] ) 
        {
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_XYBH_ISNULL,MSG_CUSTOM_XYBH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        memcpy(sdb_app_khcpqy.xybh,sbuf,sizeof(sdb_app_khcpqy.xybh ));    

        memset( sSql, 0x00, sizeof( sSql ) );
        snprintf(sSql,sizeof(sSql),"UPDATE app_khcpqy SET %s bljg='%s',blgy='%s',blrq='%s'\
            WHERE cpdm= '%s' AND xybh='%s' " ,sStrSetSql, sdb_app_khcpqy.bljg,\
            sdb_app_khcpqy.blgy, sdb_app_khcpqy.blrq,sdb_app_khcpqy.cpdm, sdb_app_khcpqy.xybh );

        iRet = DCIExecuteDirect( sSql );
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIRollback();
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
            return -1;
        }
    }

    DCICommit();

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
    return 0; 
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_QuyCUSTOM
组件名称:SApp_QuyCUSTOM
组件功能:查询公共签约关系表操作
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
IRESULT SApp_QuyCUSTOM(HXMLTREE lXmlhandle)
{
    APP_KHCPQY sdb_app_khcpqy;
    APP_KHXX sdb_app_khxx;
    char ssql[1024];
    int  iMaxRecord = 0;
    char sStrWhere[1024],sStrWhereSql[1024],sTmp[1024];
    int iParas;
    char sbuf[255];
    int i, iflag;
    char sXmlnode[512];
    int  iSqllen=0;
    int  iRet = -1;
    char sErrmsg[512];
    CURSOR cur;
    
    char sRespNode[32];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /* 20090717 modified by yangdong 修改查询返回节点名 */
    memset( sRespNode, 0x00, sizeof( sRespNode ) );
    sprintf( sRespNode,"/app/custom/info" );
    
    memset(&sdb_app_khcpqy,0,sizeof(sdb_app_khcpqy));
    
    iSqllen=0;
    memset(sStrWhereSql,0,sizeof(sStrWhereSql));

    /* 签约查询最大记录数限制 */
    memset( sbuf, 0x00, sizeof( sbuf ) );
    COMP_SOFTGETXML( XMLNM_APP_CUSTOM_QYCXXZ, sbuf );
    iMaxRecord = atoi( sbuf );
    
    /* 只返回有效签约记录 */
    /* modifie by yangdong 20130220 运行按状态查询
    sprintf(sStrWhereSql, "  qyzt='0' AND rownum <= %s ", sbuf );
    */
    /*sprintf(sStrWhereSql, " rownum <= %s ", sbuf );
    iSqllen=strlen(sStrWhereSql);*/
    
    sprintf(sStrWhereSql, " 1=1 ");
    iSqllen=strlen(sStrWhereSql);

    /* 产品代码 */
    COMP_SOFTGETXML( XMLNM_APP_CUSTOM_CPDM, sdb_app_khcpqy.cpdm     );
    if ( strlen( sdb_app_khcpqy.cpdm ) > 0)
    {
        sprintf(sStrWhereSql+iSqllen, " and cpdm='%s'",sdb_app_khcpqy.cpdm);
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* 用户号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1     , sdb_app_khcpqy.yhh1     );
    trim(sdb_app_khcpqy.yhh1);
    if ( strlen(sdb_app_khcpqy.yhh1) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and yhh1='%s'",sdb_app_khcpqy.yhh1);
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* 银行帐号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH     , sdb_app_khcpqy.qyzh     );
    trim(sdb_app_khcpqy.qyzh);
    if ( strlen(sdb_app_khcpqy.qyzh) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and qyzh='%s'",sdb_app_khcpqy.qyzh);
        iSqllen=strlen(sStrWhereSql);
    }

    /* 证件类型 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJLX, sdb_app_khcpqy.zjlx );
    trim(sdb_app_khcpqy.zjlx );
    if ( strlen(sdb_app_khcpqy.zjlx) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and zjlx='%s'",sdb_app_khcpqy.zjlx);
        iSqllen=strlen(sStrWhereSql);
    }
    /* 证件号码 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_ZJHM, sdb_app_khcpqy.zjhm );
    trim(sdb_app_khcpqy.zjhm );
    if ( strlen(sdb_app_khcpqy.zjhm) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and zjhm='%s'",sdb_app_khcpqy.zjhm );
        iSqllen=strlen(sStrWhereSql);
    }

    /* added by yangdong 20130220 需求单编号 201302200006 ，增加模糊查询条件 办理机构、办理柜员、业务编号  */
    /* 办理机构 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG, sdb_app_khcpqy.bljg);
    trim(sdb_app_khcpqy.bljg);
    if ( strlen(sdb_app_khcpqy.bljg) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and bljg='%s'",sdb_app_khcpqy.bljg );
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* 办理柜员 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY, sdb_app_khcpqy.blgy);
    trim(sdb_app_khcpqy.blgy);
    if ( strlen(sdb_app_khcpqy.blgy) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and blgy='%s'",sdb_app_khcpqy.blgy );
        iSqllen=strlen(sStrWhereSql);
    }
    
    /* 修改[zff]20130507 start 增加查询条件:办理日期 */
    /* 办理日期 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ, sdb_app_khcpqy.blrq);
    trim(sdb_app_khcpqy.blrq);
    if ( strlen(sdb_app_khcpqy.blrq) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and blrq='%s'",sdb_app_khcpqy.blrq );
        iSqllen=strlen(sStrWhereSql);
    }
    /* 修改[zff]20130507 end */
    
    /* 业务编号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH, sdb_app_khcpqy.ywbh);
    trim(sdb_app_khcpqy.ywbh);
    if ( strlen(sdb_app_khcpqy.ywbh) >0 )
    {
        sprintf(sStrWhereSql+iSqllen, " and ywbh='%s'",sdb_app_khcpqy.ywbh);
        iSqllen=strlen(sStrWhereSql);
    }
    /* 签约状态 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZT, sdb_app_khcpqy.qyzt);
    trim(sdb_app_khcpqy.qyzt);
    if( sdb_app_khcpqy.qyzt[0] == '2' )
         /* 查询全部用户 */
        ;
    else if( sdb_app_khcpqy.qyzt[0] == '1' || sdb_app_khcpqy.qyzt[0] == '0' )
        sprintf(sStrWhereSql+iSqllen, " and qyzt='%s'",sdb_app_khcpqy.qyzt);
    else /* 默认查询返回正常签约用户 */
        sprintf(sStrWhereSql+iSqllen, " and qyzt='0'" );

    iSqllen=strlen(sStrWhereSql);
    /* end of add */
    
    memset(ssql,0,sizeof(ssql));
    /*sprintf(ssql,"SELECT * FROM app_khcpqy WHERE %s ORDER BY cpdm,xybh",sStrWhereSql);*/
    sprintf(ssql,"SELECT * FROM  app_khcpqy WHERE %s ORDER BY cpdm,xybh fetch first %s rows only",sStrWhereSql,sbuf);
    if ((cur = DCIDeclareCursor(ssql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
  
    for (i=0,iflag=0;;i++)
    {
        memset(&sdb_app_khcpqy,0,sizeof(sdb_app_khcpqy));    
        iRet = DBFetch(cur, SD_APP_KHCPQY, NUMELE(SD_APP_KHCPQY), &sdb_app_khcpqy, sErrmsg ) ;
        if( iRet < 0 )
        { 
            iflag = -1 ; 
            break;
        }
        if ( iRet == 0 )
            break;

        /*对取出的数据进行处理*/
        /* 协议编号 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/xybh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.xybh    );
        
        /* 产品代码 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/cpdm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.cpdm    );
        
        /* 业务编号 */
        trim(sdb_app_khcpqy.ywbh);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/ywbh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.ywbh    );
        
        /* 帐号类型 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zhlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zhlx    );
        
        /* 签约帐号 */
        trim(sdb_app_khcpqy.qyzh);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/qyzh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.qyzh    );
        
        /* 户名 */
        trim(sdb_app_khcpqy.zhhm);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zhhm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zhhm    );
        
        /* 证件类型 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zjlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zjlx    );
        
        /* 证件号码 */
        trim(sdb_app_khcpqy.zjhm);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zjhm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.zjhm    );
        
        /* 签约类型 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/qylx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.qylx    );
        
        /* 客户经理 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/khjl", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.khjl    );
        
        /* 合约开始日期 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/hyksrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.hyksrq    );
        
        /* 合约结束日期 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/hyjsrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.hyjsrq    );
        
        /* 开通渠道 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/ktqd", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.ktqd    );
        
        /* 办理机构 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/bljg", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.bljg    );
        
        /* 办理柜员 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/blgy", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.blgy    );
        
        /* 办理日期 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/blrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.blrq    );
        
        /* 用户编号1 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhh1", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhh1    );
        
        /* 用户编号2 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhh2", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhh2    );
        
        /* 用户编号3 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhh3", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhh3    );
        
        memset(&sdb_app_khxx, 0, sizeof(sdb_app_khxx));
        /* 获取客户信息 --B*/
        snprintf( sSql1, sizeof( sSql1 ),  "SELECT * FROM app_khxx \
            WHERE zjlx = '%s' AND zjhm ='%s'",sdb_app_khcpqy.zjlx,sdb_app_khcpqy.zjhm );
        if( iRet < 0 )
        {
            DCIFreeCursor(cur);
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* 获取客户信息 --B*/
        
        /* 电子邮件 */
        trim(sdb_app_khxx.memail);
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/email", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khxx.memail    );
        
        /* 短信标志 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/dxtzbz", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.dxtzbz    );
        
        /* 限额 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/zhzded", sRespNode, i+1 );
        memset(sbuf,0,sizeof(sbuf));
        sprintf( sbuf,"%f",sdb_app_khcpqy.zhzded);
        COMP_SOFTSETXML(sXmlnode     , sbuf    );
        
        /* 扩展字段1 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld1", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld1    );
        
        /* 扩展字段2 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld2", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld2    );
        
        /* 扩展字段3 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld3", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld3    );
  
        /* added by yangdong 20090708  */
        /* 开户机构 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/khjg", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.khjg );
        
        /* 用户名称  */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhmc", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhmc);
        
        /* 用户类型  */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhlx);
  
        /* 代理证件类型 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/dlzjlx", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.dlzjlx);
        
        /* 代理证件号码 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/dlzjhm", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.dlzjhm );
        
        /* 用户邮编 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhyb", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhyb );
        
        /* 用户电话 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhdh", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhdh );
        
        /* 用户地址 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/yhdz", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.yhdz );
        
        /* 交易币种 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/jybz", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.jybz );
        
        /* 扣款最大限额 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkzdxe", sRespNode, i+1 );
        memset( sbuf, 0x00, sizeof( sbuf ) );
        sprintf( sbuf, "%.2f", sdb_app_khcpqy.kkzdxe );
        COMP_SOFTSETXML(sXmlnode     , sbuf );
        
        /* 约定扣款日期 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/ydkkrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.ydkkrq );
        
        /* 扣款周期*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkzq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.kkzq);
        
        /* 扣款状态*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkzt", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.kkzt);
        
        /* 扣款日期*/
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/kkrq", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.kkrq );
  
        /* 扩展字段4 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld4", sRespNode, i+1 );
         COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld4 );
        
        /* 扩展字段5 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld5", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld5 );
        
        /* 扩展字段6 */
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/extfld6", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.extfld6 );
        /* end of add */
      
        memset(sXmlnode,0,sizeof(sXmlnode));
        sprintf( sXmlnode, "%s|%d/qyzt", sRespNode, i+1 );
        COMP_SOFTSETXML(sXmlnode     , sdb_app_khcpqy.qyzt    );
    }
    DCIFreeCursor(cur);
    if (iflag < 0)
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->交易拒绝:XX处理失败,iret[%d]",iflag),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,MSG_YW_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    if ( 0 == i )  /*记录没找到*/
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->记录没找到[%d]",i),"INFO");
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("ssql[%s]",ssql),"INFO");
        /* by yr 20120913 */
        fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND ,MSG_APP_QY_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML( XMLNM_APP_CUSTOM_COUNT, itoa( i ) );

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    return COMPSTATUS_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_DelCUSTOM
组件名称:SApp_DelCUSTOM
组件功能:删除公共签约关系表操作
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
IRESULT SApp_DelCUSTOM(HXMLTREE lXmlhandle)
{
    char sQyzh[32+1];
    char sCpdm[16+1];
    char sYhh[32+1];
    char sYwbh[16+1];
    char sBljg[16+1];
    char sBlgy[16+1];
    char sBlrq[8+1];
    char sSignType[2];   /* 签约模式 */
    char sSignStat[2];   /* 签约状态 */
    char sbuf[255];
    char sSql[1024],sStrWhere[1024];
    char sErrmsg[512];
    int iResult;
    int  iRet = -1;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"");
  
    memset(sSignType, 0, sizeof(sSignType));
    COMP_SOFTGETXML( XMLNM_APP_CPXX_QYMS, sSignType);
    trim(sSignType);
    
    /* 产品代码 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_CPDM     , sCpdm);
    if ( 0 == sCpdm[0])
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;    
    }
    trim(sCpdm);

    /* 业务编号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH     , sYwbh );
    trim(sYwbh);
    
    /* 用户号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1     , sYhh     );
    trim(sYhh);
    
    /* 银行帐号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH     , sQyzh     );
    trim(sQyzh);
    
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLJG     , sBljg     );
    trim(sBljg);
    if ( strlen(sBljg) <=0 )
    {
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBJG     , sBlrq     );
    }

    /* 默认主办柜员 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLGY     , sBlgy     );
    trim(sBlgy);
    if ( strlen(sBlgy) <=0 )
    {
        COMP_SOFTGETXML(XMLNM_APP_CPXX_ZBGY     , sBlgy     );
    }

    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_BLRQ     , sBlrq     );
    /* 默认办理日期 */
    trim(sBlrq);
    if ( strlen(sBlrq) <=0 )
    {
        COMP_SOFTGETXML(XMLNM_APP_CPXX_YWRQ     , sBlrq     );
    }
    
    memset(sStrWhere, 0, sizeof(sStrWhere));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    switch (atoi(sSignType))
    {
        case 1: /* 产品代码+银行帐号唯一 */
            if ( 0 == sQyzh[0] ) 
            {
                 fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
                 fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                 return -1;    
            }
            
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy \
                WHERE qyzh = '%s'and cpdm = '%s'", sQyzh, sCpdm );
            snprintf(sStrWhere, sizeof( sStrWhere ), "  cpdm = '%s' and qyzh = '%s' ", sCpdm,sQyzh);
            break;
            
        case 3 : /* 产品代码+银行帐号+用户编号唯一*/
            if ( 0 == sQyzh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            
            if ( 0 == sYhh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy WHERE \
                 yhh1 = '%s' AND qyzh = '%s'AND cpdm ='%s'",sYhh, sQyzh, sCpdm );
            
            snprintf(sStrWhere, sizeof( sStrWhere ), "  cpdm = '%s' and qyzh='%s' and yhh1 = '%s' ", sCpdm,sQyzh,sYhh);
            
            break;

        case 4 : /* 业务编号 +用户编号唯一 */
            if ( 0 == sYhh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy \
                         WHERE yhh1 = '%s' and ywbh = '%s' ",sYhh, sYwbh );
            memset(sStrWhere, 0, sizeof(sStrWhere));
            snprintf(sStrWhere, sizeof( sStrWhere ), "  ywbh = '%s' and yhh1 = '%s' ", sYwbh, sYhh);
            break;

        default : /* 产品代码+用户编号唯一 */
            if ( 0 == sYhh[0] ) 
            {
                fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return -1;    
            }
            snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt FROM app_khcpqy \
                         WHERE yhh1 = '%s' and cpdm = '%s' ",sYhh, sCpdm );
            snprintf(sStrWhere, sizeof( sStrWhere ), "  cpdm = '%s' and yhh1 = '%s' ", sCpdm,sYhh);
    }
    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sSignStat ) ;
    if( iRet < 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if ( iRet == 0 || sSignStat[0] == '1' )  /* 记录不存在或者已解约 */
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,\
            Fmtmsg("产品代码[%s],用户号[%s],银行帐号[%s],签约状态[%s]",sCpdm,sYhh, sQyzh,sSignStat),"INFO");
                  
        if( iRet == 0 )
            fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND,MSG_APP_QY_NOTFOUND );
        else
            fpub_SetMsg(lXmlhandle,MID_APP_KHCPQY,MSG_APP_KHCPQY);

        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
        return 0; 
    }
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 撤约处理 */
    memset(sSql,0,sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"update app_khcpqy set \
            qyzt = '1', bljg='%s',blgy='%s',blrq='%s'  where %s ",\
            sBljg, sBlgy, sBlrq , sStrWhere);
    iRet = DCIExecuteDirect( sSql );
    if(iRet<0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("  -->sSql[%s]",sSql),"debug2");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg(MSG_SYS_DBEXEC,sSql),"SDB_DynExecSql");
    }

    DCICommit();

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);   
    return 0; 
}


/************************************************************************
动态组件函数定义
组件函数名称:SApp_SerchCUS
组件名称:SApp_SerchCUS
组件功能:查询公共签约关系表信息是否存在
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
int SApp_SerchCUS(HXMLTREE lXmlhandle)
{
    char   sCpdm[16+1]={0};    /*产品代码*/
    char   sQyzh[32+1]={0};   /*签约账户*/
    char   sYhh[32+1]={0};    /*用户号*/
    char   sYwbh[16+1]={0};    /*业务编号*/
    char   sSignType[2]={0};  /*签约类型*/
    char   sXybh[20+1]={0};   /*协议编号*/
    char   sQyzt[1+1]={0};    /*签约状态*/
    char sErrmsg[512];
    int iRet = -1;

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"");
    /* ---------- 判断客户是否已签约 begin ---------- */
    
    /* 产品代码 */
    COMP_SOFTGETXML(XMLNM_APP_CPXX_CPDM , sCpdm );
    trim(sCpdm);
    if ( 0 == sCpdm[0])
    {
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_CPDM_ISNULL,MSG_CUSTOM_CPDM_ISNULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return -1;
    }
    /* 业务编号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YWBH , sYwbh );
    trim(sYwbh);

    /* 用户号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_YHH1 , sYhh );
    trim(sYhh);
    
    /* 银行帐号 */
    COMP_SOFTGETXML(XMLNM_APP_CUSTOM_QYZH , sQyzh );
    trim(sQyzh);
    
    /* 系统支持签约模式 */
    memset(sSignType, 0, sizeof(sSignType));
    COMP_SOFTGETXML( XMLNM_APP_CPXX_QYMS, sSignType );
    trim(sSignType);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("签约关系：产品代码[%s], 帐号[%s], 用户号[%s], 业务编号 [%s], 签约方式 [%s]", \
        sCpdm, sQyzh, sYhh, sYwbh, sSignType),"INFO");
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    /* 产品代码+银行帐号唯一 */
    if ( sSignType[0] == '1' )
    {
        /* 银行帐号不能为空 */
        if ( 0 == sQyzh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            qyzh='%s' AND cpdm='%s'",sQyzh, sCpdm );
    }
    else
    /* 产品代码+银行帐号+用户编号唯一 签约类型3 为默认值 */
    if ( sSignType[0] == '3' )
    {
        /* 银行帐号不能为空 */
        if ( 0 == sQyzh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHZH_ISNULL,MSG_CUSTOM_YHZH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;    
        }
        /* 用户编号不能为空 */
        if ( 0 == sYhh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            qyzh='%s' AND yhh1='%s'  AND cpdm='%s'",sQyzh, sYhh, sCpdm );
    }

    else
    /* 业务编号+用户编号唯一 */
    if ( sSignType[0] == '4' )
    {
        /* 用户编号不能为空 */
        if ( 0 == sYhh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
		/*modefied by llh 20181012 begin*/
        /*snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            yhh1='%s'  AND ywbh='%s'",sQyzh, sYhh);*/
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            yhh1='%s'  AND ywbh='%s'", sYhh, sYwbh);
		/*modefied by llh 20181012 end */
    }

    else
    /* 产品代码+用户编号唯一 */
    {
        /* 用户编号不能为空 */
        if ( 0 == sYhh[0] )
        {
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_YHH_ISNULL,MSG_CUSTOM_YHH_ISNULL);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
        snprintf( sSql1, sizeof( sSql1 ), "SELECT qyzt,xybh FROM app_khcpqy WHERE\
            yhh1='%s'  AND cpdm='%s'", sQyzh, sCpdm );
    }

    iRet = DBSelectToMultiVar( sErrmsg, sSql1, sQyzt, sXybh ) ;
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )  /* 记录不存在 */
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("产品代码[%s],客户号[%s],签约状态[%s]",sCpdm,sYhh,sQyzt),"INFO");
        fpub_SetMsg(lXmlhandle,MID_APP_QY_NOTFOUND,MSG_APP_QY_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    if( sQyzt[0] == '0' )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("产品代码[%s],客户号[%s],签约状态[%s]",sCpdm,sYhh,sQyzt),"INFO");
        fpub_SetMsg(lXmlhandle,MID_CUSTOM_QY,MSG_CUSTOM_QY);
        fpub_SetCompStatus(lXmlhandle, 1);/* 客户已签约 */
        return COMPRET_FAIL;
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"");
    fpub_SetMsg(lXmlhandle,MID_CUSTOM_QY,"客户签约关系不存在");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
