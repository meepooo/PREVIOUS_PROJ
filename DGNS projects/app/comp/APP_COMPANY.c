/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:中间业务平台项目
版    本:V4.1.0.1
操作系统:
文件名称:APP_COMPANY.c
文件描述:业务单位签约
项 目 组:
程 序 员:YangDong
发布日期:2014年7月10日
程 序 员:YangDong
发布日期:2015年9月15日
*********************************************************************/
#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"
#define SOCOMPBUILDNO BUILDDATETIME

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>APP_COMPANY.so</soname>\
        <sosrcname>APP_COMPAY.c</sosrcname>\
        <sonote>APP单位产品签约管理</sonote>\
        <version>\
        <rec ver=\"2.1.0.3\" modify=\"2014-7-10 15:08\" programer=\"YangDong\" filesize=\"1591618\">单位产品签约管理</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-9-15 15:08\" programer=\"YangDong\" filesize=\"1591618\">DCI改造</rec>\
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

APP_DWCPXY sdb_app_dwcpxy;
APP_DWXX sdb_app_dwxx;
APP_DW_CPXY sdb_app_dw_cpxy;
char sSql[1024+1];  
char sSql2[1024+1];
    
/**********************************************************************
组件函数: SAPP_ADDDWXY
组件名称: 新增单位协议
组件参数：
输入参数：
输出参数：
处理说明: 
*************************************************************************/
IRESULT SAPP_AddDwxy(HXMLTREE lXmlhandle)
{
    int  i,iParas;
    int  iDwbh;
    char sYwbh[16+1];
    char sDwbh[16+1];
    char sBuf[512+1];
    char sTmp[128+1];
    char sWhsj[14+1];
    fpub_InitSoComp(lXmlhandle);
    int iRet = -1;
    char sErrmsg[512];
                      
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")  
       
    /*组件参数检查*/
    COMP_PARACOUNTCHKMIN(2)

    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) );
    memset( &sdb_app_dwxx, 0x00, sizeof( sdb_app_dwxx ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"产品代码") 
    trim(sBuf);
    strncpy( sdb_app_dwcpxy.cpdm, sBuf, sizeof( sdb_app_dwcpxy.cpdm ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"收付标志")
    trim(sBuf);
    pstrcopy( sdb_app_dwcpxy.sfbz, sBuf, sizeof( sdb_app_dwcpxy.sfbz ) );

    LOG(LM_DEBUG,Fmtmsg("产品代码[%s]",sdb_app_dwcpxy.cpdm ),"DEBUG")  

    /* 单位编号、业务编号 */
    COMP_SOFTGETXML(  XMLNM_APP_REQ_DWBH, sDwbh );
    COMP_SOFTGETXML(  XMLNM_APP_REQ_YWBH, sYwbh );
    trim( sDwbh );
    trim( sYwbh );
    
    /* 获取上送单位签约相关信息 */
    /* 交易机构、柜员 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_JYJG, sBuf);
    pstrcopy( sdb_app_dwcpxy.bljg, sBuf, sizeof( sdb_app_dwcpxy.bljg ) );
    pstrcopy( sdb_app_dwcpxy.whjg, sBuf, sizeof( sdb_app_dwcpxy.bljg ) );

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_JYGY, sBuf);
    pstrcopy( sdb_app_dwcpxy.blgy, sBuf, sizeof( sdb_app_dwcpxy.blgy ) );
    pstrcopy( sdb_app_dwcpxy.whgy, sBuf, sizeof( sdb_app_dwcpxy.blgy ) );

    /* 办理日期 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_ZWRQ, sBuf);
    pstrcopy( sdb_app_dwcpxy.blrq, sBuf, sizeof( sdb_app_dwcpxy.blrq ) );

    /* 维护时间 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_SYSTIME, sBuf);
    snprintf( sWhsj, sizeof( sWhsj ), "%s%s", sdb_app_dwcpxy.blrq, sBuf );
    pstrcopy( sdb_app_dwcpxy.whsj, sWhsj, sizeof( sWhsj ) );
    pstrcopy( sdb_app_dwxx.whsj, sWhsj, sizeof( sWhsj ) );
 
    /* 合同编号 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_XYBH, sBuf);
    pstrcopy( sdb_app_dwcpxy.xybh, sBuf, sizeof( sdb_app_dwcpxy.xybh ) );

    /* 业务名称为空 - 使用单位名称+产品名称 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_YWMC, sBuf);
    strlen( sBuf );
    if( strlen( sBuf ) < 2 )
    {
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWMC, sBuf);
        memset(sTmp, 0, sizeof(sTmp));
        COMP_SOFTGETXML( XMLNM_APP_CPXX_CPMC, sTmp);
        snprintf( sdb_app_dwcpxy.ywmc, sizeof( sdb_app_dwcpxy.ywmc ) ,"%s%s",sBuf,sTmp );
    }
    else
        pstrcopy( sdb_app_dwcpxy.ywmc, sBuf, sizeof( sdb_app_dwcpxy.ywmc ) );

    /* 银行代码 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_YHDM, sBuf);
    pstrcopy( sdb_app_dwcpxy.yhdm, sBuf, sizeof( sdb_app_dwcpxy.yhdm ) );

    /* 账户类型 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_ZHLX, sBuf);
    pstrcopy( sdb_app_dwcpxy.zhlx, sBuf, sizeof( sdb_app_dwcpxy.zhlx ) );

    /* 代收账号 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.dszh, sBuf, sizeof( sdb_app_dwcpxy.dszh ) );

    /* 代收户名称 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.dszhmc, sBuf, sizeof( sdb_app_dwcpxy.dszhmc ) );

    /* 代付账号 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.dfzh, sBuf, sizeof( sdb_app_dwcpxy.dfzh ) );

    /* 代付户名称 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.dfzhmc, sBuf, sizeof( sdb_app_dwcpxy.dfzhmc ) );

    /* 客户经理名称 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_KHJL, sBuf);
    pstrcopy( sdb_app_dwcpxy.khjl, sBuf, sizeof( sdb_app_dwcpxy.khjl ) );

    /* 合约开始日期 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_HYKSRQ, sBuf);
    /* 为空则默认为当天 */
    if( strlen( sBuf ) < 1 )
        strcpy( sdb_app_dwcpxy.hyksrq, sdb_app_dwcpxy.blrq );
    else
        pstrcopy( sdb_app_dwcpxy.hyksrq, sBuf, sizeof( sdb_app_dwcpxy.hyksrq ) );

    /* 合约结束日期 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_HYJSRQ, sBuf);
    /* 为空则默认为一个较大日期 
    if( strlen( sBuf ) < 1 )
        strcpy( sdb_app_dwcpxy.hyjsrq, "20500101");
    else */
        pstrcopy( sdb_app_dwcpxy.hyjsrq, sBuf, sizeof( sdb_app_dwcpxy.hyjsrq ) );

    /* 账户最低额度 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_ZDED, sBuf);
    sdb_app_dwcpxy.zhzded = atof(  sBuf );

    /* 内部过渡户 放入扩展字段1 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.extfld1, sBuf, sizeof( sdb_app_dwcpxy.extfld1 ) );

    /* 是否需要校验签约关系，放入扩展字段2 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_JYQY, sBuf);
    pstrcopy( sdb_app_dwcpxy.extfld2, sBuf, sizeof( sdb_app_dwcpxy.extfld2 ) );

    /*  单位名称 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWMC, sBuf);
    pstrcopy( sdb_app_dwxx.dwmc, sBuf, sizeof( sdb_app_dwxx.dwmc ) );

    /*  单位证件类型 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWZJLX, sBuf);
    pstrcopy( sdb_app_dwxx.dwzjlx, sBuf, sizeof( sdb_app_dwxx.dwzjlx ) );

    /*  单位证件号码 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWZJHM, sBuf);
    pstrcopy( sdb_app_dwxx.dwzjhm, sBuf, sizeof( sdb_app_dwxx.dwzjhm ) );

    /* 单位联系人名称 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXR , sBuf);
    pstrcopy( sdb_app_dwxx.dwlxr, sBuf, sizeof( sdb_app_dwxx.dwlxr ) );
    pstrcopy( sdb_app_dwcpxy.lxr, sBuf, sizeof( sdb_app_dwcpxy.lxr ) );

    /* 单位联系人电话 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXRDH, sBuf);
    pstrcopy( sdb_app_dwxx.dwlxrdh, sBuf, sizeof( sdb_app_dwxx.dwlxrdh ) );
    pstrcopy( sdb_app_dwcpxy.lxdh, sBuf, sizeof( sdb_app_dwcpxy.lxdh ) );

    /* 单位联系地址 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWDZ, sBuf);
    pstrcopy( sdb_app_dwxx.dwdz, sBuf, sizeof( sdb_app_dwxx.dwdz ) );

    /* 单位联系email*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DWEMAIL, sBuf);
    pstrcopy( sdb_app_dwxx.dwemail, sBuf, sizeof( sdb_app_dwxx.dwemail ) );

    /* 扩展字段1 存放内部客户号 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBKHH, sBuf);
    pstrcopy( sdb_app_dwxx.extfld1, sBuf, sizeof( sdb_app_dwxx.extfld1 ) );

    /* 扩展字段2*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_EXTFLD2, sBuf);
    pstrcopy( sdb_app_dwxx.extfld2, sBuf, sizeof( sdb_app_dwxx.extfld2 ) );

    /* 如果上送业务编号，则直接使用(规定如果业务编号外部生成，则单位编号也外部生成) */
    if( strlen( sYwbh ) > 0 )
    {
        strcpy( sdb_app_dwcpxy.ywbh, sYwbh ) ;
        strcpy( sdb_app_dwcpxy.dwbh, sDwbh ) ;
        strcpy( sdb_app_dwxx.dwbh, sDwbh ) ;
    }
    else
    {
        /* 从序列获取单位序号*/
        if( fprv_getSeqno( "K_DWBH", &iDwbh ) < 0 )
        {
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        } 

        /* 生成业务编号 :产品代码＋单位序号 */
        snprintf( sdb_app_dwcpxy.ywbh, sizeof( sdb_app_dwcpxy.ywbh ) , "%s%06d", sdb_app_dwcpxy.cpdm, iDwbh ) ;
        strcpy( sdb_app_dwcpxy.dwbh, sdb_app_dwcpxy.ywbh ) ;
        /* 单位编号同业务编号 */
        strcpy( sdb_app_dwxx.dwbh, sdb_app_dwcpxy.ywbh ) ;
    }

    LOG(LM_DEBUG,Fmtmsg("业务编号[%s]",sdb_app_dwcpxy.ywbh ),"DEBUG")  

	/* add by sunpj 2016-11-11 beg*/

    /* 服务热线*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_FWRX, sBuf);
    pstrcopy( sdb_app_dwcpxy.fwrx, sBuf, sizeof( sdb_app_dwcpxy.fwrx ) );

	/* 缴费编号显示名称*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_JFBHXSMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.jfbhxsmc, sBuf, sizeof( sdb_app_dwcpxy.jfbhxsmc ) );

	/* 客户号*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_KHH, sBuf);
    pstrcopy( sdb_app_dwcpxy.khh, sBuf, sizeof( sdb_app_dwcpxy.khh ) );

	/* 内部户账号名称*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.nbhzhmc, sBuf, sizeof( sdb_app_dwcpxy.nbhzhmc ) );

	/* 内部户账号*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.nbhzh, sBuf, sizeof( sdb_app_dwcpxy.nbhzh ) );

	/* 手续费内部户账号名称*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZHMC, sBuf);
    pstrcopy( sdb_app_dwcpxy.sxfnbhzhmc, sBuf, sizeof( sdb_app_dwcpxy.sxfnbhzhmc ) );

	/* 手续费内部户账号*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZH, sBuf);
    pstrcopy( sdb_app_dwcpxy.sxfnbhzh, sBuf, sizeof( sdb_app_dwcpxy.sxfnbhzh ) );

	/* 上传方式*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_SCFS, sBuf);
    pstrcopy( sdb_app_dwcpxy.scfs, sBuf, sizeof( sdb_app_dwcpxy.scfs ) );

	/* 审核状态*/
    pstrcopy( sdb_app_dwcpxy.shzt, "9", sizeof( sdb_app_dwcpxy.shzt ) );

	/* add by sunpj 2016-11-11 end*/

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 登记单位信息  单位信息不判断重复 */
    sdb_app_dwxx.zt[0] = '0';

    iRet = DBInsert("app_dwxx", SD_APP_DWXX, NUMELE(SD_APP_DWXX), &sdb_app_dwxx, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        DCIRollback();
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 登记单位产品协议信息 */
    sdb_app_dwcpxy.qyzt[0] = '0';

    iRet = DBInsert("app_dwcpxy", SD_APP_DWCPXY, NUMELE(SD_APP_DWCPXY), &sdb_app_dwcpxy, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    if( DCICommit() != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 业务编号 */
    COMP_HARDSETXML( XMLNM_APP_RESP_YWBH, sdb_app_dwcpxy.ywbh  );
    /* 单位编号 */
    COMP_HARDSETXML( XMLNM_APP_RESP_DWBH, sdb_app_dwcpxy.dwbh  );
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}


/**********************************************************************
组件函数: SAPP_MODDWXY
组件名称: 修改单位协议
组件参数：
输入参数：
输出参数：
处理说明: 
*************************************************************************/
IRESULT SAPP_ModDwxy(HXMLTREE lXmlhandle)
{
    int  i,iParas;
    int  iDwbh;
    char sYwbh[16+1];
    char sJybz[1+1];
    char sBuf[512+1];
    char sTmp[128+1];
    char sWhsj[14+1];
    int  iFlag = 0;     /* 单位产品协议修改标志 */
    int  iFlag2 = 0;    /* 单位信息修改标志 */
    int iRet = -1;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
                      
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")   
       
    /*组件参数检查*/
    COMP_PARACOUNTCHKMIN(3)

    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) ) ;

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"业务编号") 
    trim(sBuf);
    strncpy( sdb_app_dwcpxy.ywbh, sBuf, sizeof( sdb_app_dwcpxy.ywbh ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"单位编号") 
    trim(sBuf);
    strncpy( sdb_app_dwcpxy.dwbh, sBuf, sizeof( sdb_app_dwcpxy.dwbh ) );
    
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"交易标志")   /* 1-维护  2-解约 */
    trim(sBuf);
    strncpy( sJybz, sBuf, sizeof( sJybz ) );

    /* 交易机构、柜员 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_JYJG  , sBuf);
    pstrcopy( sdb_app_dwcpxy.bljg, sBuf, sizeof( sdb_app_dwcpxy.bljg ) );

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_JYGY, sBuf);
    pstrcopy( sdb_app_dwcpxy.blgy, sBuf, sizeof( sdb_app_dwcpxy.blgy ) );

    /* 办理日期 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_ZWRQ, sBuf);
    pstrcopy( sdb_app_dwcpxy.blrq, sBuf, sizeof( sdb_app_dwcpxy.blrq ) );

    /* 维护时间 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_SYSTIME, sBuf);
    snprintf( sWhsj, sizeof( sWhsj ), "%s%s", sdb_app_dwcpxy.blrq, sBuf );

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    /* 更新办理柜员信息 */
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sSql2, 0x00, sizeof( sSql2 ) );
	/*modify by llh 20180704 更新维护机构、柜员、时间,不是办理机构、柜员、时间*/
/*    sprintf( sSql, "UPDATE app_dwcpxy SET bljg='%s',blgy='%s',blrq='%s' ",\
        sdb_app_dwcpxy.bljg, sdb_app_dwcpxy.blgy,sdb_app_dwcpxy.blrq  );
*/
    sprintf( sSql, "UPDATE app_dwcpxy SET whjg='%s',whgy='%s',whsj='%s' ",\
        sdb_app_dwcpxy.bljg, sdb_app_dwcpxy.blgy,sWhsj );
	/*modify by llh 20180704 更新维护机构、柜员、时间,不是办理机构、柜员、时间*/

    sprintf( sSql2, "UPDATE app_dwxx SET whjg='%s',whgy='%s',whsj='%s' ",\
        sdb_app_dwcpxy.bljg, sdb_app_dwcpxy.blgy,sWhsj );

    /* 修改单位产品协议信息 */
    if( sJybz[0] == '2' ) /* 解约 */
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, ", qyzt='1', shzt='9'" );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }
    else
    {
        /* 代收账号 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DSZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dszh='%s' " , sBuf );
            strcat( sSql, sTmp ) ;
            iFlag = 1;
        }
        
        /* 代收账号名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DSZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dszhmc='%s' " , sBuf );
            strcat( sSql, sTmp ) ;
            iFlag = 1;
        }
   
        /* 代付账号 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DFZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dfzh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* 代付账号名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DFZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dfzhmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* 业务名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_YWMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", ywmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* 合约结束日期 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_HYJSRQ, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", hyjsrq='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
   
        /* 内部过渡户 放入扩展字段1 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", extfld1='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        
        /* 是否需要校验签约关系，放入扩展字段2 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_QYJY, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", extfld2='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		/* add by sunpj 2016-11-11 beg*/
		        
	    /* 服务热线 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_FWRX, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", fwrx='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* 产品代码 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_CPDM, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", cpdm='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* 缴费编号显示名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_JFBHXSMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", jfbhxsmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* 内部户账号名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", nbhzhmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* 内部户账号 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBHZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", nbhzh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* 手续费内部户账号名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZHMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", sxfnbhzhmc='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

	    /* 手续费内部户账号 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_SXFNBHZH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", sxfnbhzh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		/* 客户号 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_KHH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", khh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		/* 上传方式 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_SCFS, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", scfs='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }

		if (1 == iFlag)
		{
			memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", shzt='%s' " , "9" );
            strcat( sSql, sTmp ); 
		}

		/* add by sunpj 2016-11-11 end*/
		
		/* add by llh 20181022 beg*/
		/* 合约开始日期 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_HYKSRQ, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", hyksrq='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
        /* 协议编号 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_XYBH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", xybh='%s' " , sBuf );
            strcat( sSql, sTmp ); 
            iFlag = 1;
        }
		/* add by llh 20181022 end*/
        
        /*  修改单位信息 */
        /*  单位名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWMC, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwmc='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* 单位联系人名称 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXR, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwlxr='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* 单位联系人电话 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWLXRDH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwlxrdh='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* 单位联系地址 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWDZ, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwdz='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* 单位联系email*/
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_DWEMAIL, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", dwemail='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        /* 扩展字段1 存放内部客户号 */
        memset(sBuf, 0, sizeof(sBuf));
        COMP_SOFTGETXML( XMLNM_APP_REQ_NBKHH, sBuf);
        if( strlen( sBuf ) > 1 )
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, ", extfld1='%s' " , sBuf );
            strcat( sSql2, sTmp ) ;
            iFlag2 = 1;
        }
        
        if( iFlag == 0 && iFlag2 == 0 )
        {
            LOG(LM_STD,Fmtmsg("没有信息需要修改"),"INFO")  
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
            return COMPRET_SUCC;
        }
    }
   
    if( iFlag == 1 )  /* 更新单位产品协议 */
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " WHERE ywbh='%s'", sdb_app_dwcpxy.ywbh );
        strcat( sSql, sTmp ) ;
        /* 判断是否超长*/
        if( strlen( sSql ) > sizeof( sSql ) )
        {
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            DCIRollback();
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }

        iRet = DCIExecuteDirect( sSql );
        if ( iRet < 1 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s][%d][%s]",DCILastError(),iRet,sSql),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
    }
    if( iFlag2 == 1 )  /* 更新单位信息 */
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " WHERE dwbh='%s'", sdb_app_dwcpxy.dwbh );
        strcat( sSql2, sTmp ) ;
        /* 判断是否超长*/
        if( strlen( sSql2 ) > sizeof( sSql2 ) )
        {
            LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->sSql[%s]",sSql2),"ERROR");
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }

        iRet = DCIExecuteDirect( sSql2 );
        if ( iRet < 1 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s][%d][%s]",DCILastError(),iRet,sSql),"ERROR")
            DCIRollback();
            fpub_SetMsg(lXmlhandle,MID_CUSTOM_UPD_KHQY,MSG_CUSTOM_UPD_KHQY);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return -1;
        }
    } 

    if( DCICommit() != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError()),"ERROR")
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}

/**********************************************************************
组件函数: SAPP_QryDWXY
组件名称: 查询单位协议
组件参数：
输入参数：
输出参数：
处理说明: 
*************************************************************************/
IRESULT SAPP_QryDwxy(HXMLTREE lXmlhandle)
{
    int  i,iParas;
    char sYwbh[16+1];
    char sBuf[512+1];
    char sTmp[128+1];
    int  iFlag = 0; 
    int  returnFlag = 0; 
    int  iCount =0;
    char sXmlNode[64+1];
    char sBaseNode[64+1];
    char sInnerOrg[27+1];
    char sJgbh1[16+1]={0};  /* 上级机构 */
    char sJgbh2[16+1]={0};  /* 上上级机构 */
    char sJgbh3[16+1]={0};  /* 上上上级机构 */ 
    char sJgbh4[16+1]={0};  /* 上上上上级机构 */ 
    char sQryType[1+1];
    /* 查询类型 1交易权限 查询本机构允许操作业务(默认) 2查询本机构及下属机构办理的业务 3 查询上级机构签约业务 */

    int iRet = -1;
    char sErrmsg[512];
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle);
                      
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")   
       
    /*组件参数检查*/
    COMP_PARACOUNTCHKMIN(2)

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"查询标志")   /* 0-列表查询 1-详细信息查询 */
    trim(sBuf);
    returnFlag = atoi( sBuf ) ;

    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"返回节点名")   
    trim(sBuf);
    strncpy( sBaseNode, sBuf, sizeof( sBaseNode ) );

    memset( sSql, 0x00, sizeof( sSql ) );
    sprintf( sSql, "select a.*,b.*  from app_dwcpxy a, app_dwxx b  where a.dwbh=b.dwbh  " );

    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) ) ;
    memset( &sdb_app_dwxx, 0x00, sizeof( sdb_app_dwxx ) ) ;

    iFlag = 0;
    memset(sBuf, 0, sizeof(sBuf));
    /* 业务编号 */
    COMP_SOFTGETXML( XMLNM_APP_REQ_YWBH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.ywbh='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* 产品代码 */
    COMP_SOFTGETXML( XMLNM_APP_REQ_CPDM, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.cpdm='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* 查询机构、柜员 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_QXJG  , sBuf);
    if( strlen( sBuf ) > 1 )
    {
        /* added by yangdong 20141103 查询下级机构 */
        memset( sQryType, 0x00, sizeof( sQryType) );
        memset( sTmp, 0x00, sizeof( sTmp ) );
        COMP_SOFTGETXML( XMLNM_APP_REQ_QXLX, sTmp );
        pstrcopy( sQryType, sTmp, sizeof( sQryType ) );
        if( sQryType[0] == '2' ) /* 允许查询下级机构签约的业务 */
        {
            /* 获取内部机构号 根据交易机构获取 */
            memset( sInnerOrg, 0x00, sizeof( sInnerOrg ) );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_INNER_ORG_ID, sInnerOrg );

            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, "and a.bljg in ( select trim(org_id) from t_org where inner_org_id like '%s%%' )",  sInnerOrg );
            strcat( sSql, sTmp );
        }
        else if( sQryType[0] == '3' ) /* 允许查询上级机构签约的业务 */
        {
            /* 获取上级机构 根据交易机构获取 */
            memset( sJgbh1, 0x00, sizeof( sJgbh1 ) );
            memset( sJgbh2, 0x00, sizeof( sJgbh2 ) );
            memset( sJgbh3, 0x00, sizeof( sJgbh3 ) );
            memset( sJgbh4, 0x00, sizeof( sJgbh4 ) );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID1, sJgbh1 );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID2, sJgbh2 );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID3, sJgbh3 );
            COMP_SOFTGETXML( XMLNM_APP_JGXX_ORG_ID4, sJgbh4 );

            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, "and a.bljg in ( '%s','%s','%s','%s','%s' )", sBuf, sJgbh1, sJgbh2, sJgbh3, sJgbh4 );
            strcat( sSql, sTmp );
        }
        else
        {
            memset( sTmp, 0x00, sizeof( sTmp ) );
            sprintf( sTmp, "and a.bljg='%s'", sBuf );
            strcat( sSql, sTmp );
        }
        iFlag = 1;
    }

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML(  XMLNM_APP_REQ_QXGY, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.blgy='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* 代收账号 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, " and a.dszh='%s' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DSZHMC, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.dszhmc='%%%s%%' " , sBuf );
        strcat( sSql, sTmp ) ;
        iFlag = 1;
    }

    /* 代付账号 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.dfzh='%s' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    /* 代付账号名称 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_DFZHMC, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.dfzhmc like '%%%s%%' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    /* 内部过渡户 放入扩展字段1 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBZH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and a.extfld1='%s' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    /* 内部客户号 放入扩展字段1 */
    memset(sBuf, 0, sizeof(sBuf));
    COMP_SOFTGETXML( XMLNM_APP_REQ_NBKHH, sBuf);
    if( strlen( sBuf ) > 1 )
    {
        memset( sTmp, 0x00, sizeof( sTmp ) );
        sprintf( sTmp, "and b.extfld1='%s' " , sBuf );
        strcat( sSql, sTmp ); 
        iFlag = 1;
    }

    if( iFlag == 0 )
    {
        LOG(LM_STD,Fmtmsg("没有查询条件"),"INFO")  
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }

    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError()),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sql[%s] err[%s]", sSql, DCILastError()),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
 
    memset( &sdb_app_dwcpxy, 0x00, sizeof( sdb_app_dwcpxy ) );
    memset( &sdb_app_dwxx, 0x00, sizeof( sdb_app_dwxx ) );
    iCount=0;
    while( ( iRet = DBFetch(cur, SD_APP_DW_CPXY, NUMELE(SD_APP_DW_CPXY), &sdb_app_dw_cpxy, sErrmsg ) ) > 0 )
    {
        iCount++;
        /*对取出的数据进行处理*/
        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "%s/ywbh|%d/ywbh", sBaseNode, iCount );
        COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.ywbh );

        memset(sXmlNode,0,sizeof(sXmlNode));
        sprintf( sXmlNode, "%s/ywbh|%d/ywmc", sBaseNode, iCount );
        COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.ywmc );
       
        if( returnFlag == 1 )  /* 返回详细信息 */
        {
            if( iCount > 100 ) /* 返回记录数超过100，直接跳出循环 */
                continue;

            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwbh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwbh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/xybh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.xybh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dszh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dszh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dszhmc", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dszhmc);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dfzh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dfzh);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dfzhmc", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dfzhmc);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/lxr", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.lxr);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/lxdh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.lxdh );
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/email", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.email );
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/hyksrq", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.hyksrq);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/hyjsrq", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.hyjsrq);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/bljg", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.bljg);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/blgy", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.blgy);
    
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/sfbz", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.sfbz );
              
            /* 内部账号 */ 
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/nbzh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.extfld1 );

            /* 校验标志 */ 
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/jybz", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.extfld2 );

            /* 单位信息 */
            /* 单位名称 */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwmc", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwmc);
    
            /* 单位证件类型 */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwzjlx", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwzjlx);
    
            /* 单位证件号码 */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwzjhm", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwzjhm);

            /* 单位联系人 */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwlxr", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwlxr);

            /* 单位联系人电话 */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwlxrdh", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwlxrdh);

            /* 单位地址 */
            memset(sXmlNode,0,sizeof(sXmlNode));
            sprintf( sXmlNode, "%s/ywbh|%d/dwdz", sBaseNode, iCount );
            COMP_SOFTSETXML(sXmlNode, sdb_app_dw_cpxy.dwdz);
        }
        memset( &sdb_app_dw_cpxy, 0x00, sizeof( sdb_app_dw_cpxy ) );
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError()),"ERROR")
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    memset(sXmlNode,0,sizeof(sXmlNode));
    COMP_SOFTSETXML( XMLNM_APP_RESP_COUNT,itoa(iCount));

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  

    return COMPRET_SUCC;
}
