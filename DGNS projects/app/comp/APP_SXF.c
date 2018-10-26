/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:恒生中间业务平台项目V2.0)
版    本:V4.1.0.1
系统环境:
文件名称:APP_SXF.c
文件描述:手续费模块
项 目 组:
程 序 员:YangDong
发布日期:
修    订:
修改日期: 20110711
          修改手续费计算，根据扣减方式对手续费进行的处理
          修改日志打印模式
修改日期: 20140918
          DCI改造
*********************************************************************/
#include "gaps_head.h"
#include "../incl/app_head.h"

double min(double a,double b)
{
    return a <= b?a:b;
}

double max(double a,double b)
{
    return a >= b?a:b;
}

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
      <root>\
      <soname>APP_SXF.so</soname>\
      <sosrcname>APP_SXF.c</sosrcname>\
      <sonote>手续费管理组件集合</sonote>\
      <version>\
      <rec ver=\"2.0.1.1\" modify=\"2010-4-1  15:08\" programer=\"YangDong\" filesize=\"1120946\">HS-AgentV2.0整理</rec>\
      <rec ver=\"2.1.0.1\" modify=\"2011-11-01  9:28\" programer=\"S..C..\" filesize=\"1120946\">AgentV2.1改造</rec>\
      <rec ver=\"4.1.0.1\" modify=\"2014-09-18  9:28\" programer=\"YangDong\" filesize=\"1120946\">DCI改造</rec>\
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
/************************************************************************
动态组件函数定义
组件函数名称:SApp_ChargeJrnl
组件名称:SApp_ChargeJrnl
组件功能:手续费记入流水
组件参数:
 序号 参数类型  参数名称       资源类别       缺省值            可空  参数说明


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
修改日期:
参数使用示例:
************************************************************************/
IRESULT SApp_ChargeJrnl(HXMLTREE lXmlhandle)
{
    APP_SXFLS sdb_app_sxfls;   
    char sSql[255];
    int iRet = -1;
    char sErrmsg[512];

    int  iParas;
    char sBuf[255];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");

    memset(&sdb_app_sxfls,0,sizeof(sdb_app_sxfls));

    /*取平台日期*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_PTRQ,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.ptrq,sBuf,sizeof(sdb_app_sxfls.ptrq));
    
    /*取平台流水号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_PTLS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.ptls,sBuf,sizeof(sdb_app_sxfls.ptls));
    
    /*取费率标识*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_FLBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.flbs,sBuf,sizeof(sdb_app_sxfls.flbs ));
    
    /*取应用标识*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_YYBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.yybs,sBuf,sizeof(sdb_app_sxfls.yybs ));
    
    /*取渠道标识*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_QDBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.qdbs,sBuf,sizeof(sdb_app_sxfls.qdbs ));
    
    /*取产品代码*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_CPDM,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.cpdm,sBuf,sizeof(sdb_app_sxfls.cpdm));
    
    /*取业务编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_YWBH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.ywbh,sBuf,sizeof(sdb_app_sxfls.ywbh));
    
    /*取机构标识*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JGBS,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jgbs,sBuf,sizeof(sdb_app_sxfls.jgbs));
    
    /*取客户类型*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_KHLX,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.khlx,sBuf,sizeof(sdb_app_sxfls.khlx));
    
    /*取客户编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_KHBH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.khbh,sBuf,sizeof(sdb_app_sxfls.khbh));
    
    /*取客户号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_YHH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.yhh,sBuf,sizeof(sdb_app_sxfls.yhh ));
    
    /*取单位编号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_DWBH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.dwbh,sBuf,sizeof(sdb_app_sxfls.dwbh));
    
    /*取原交易流水号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYLSH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jylsh,sBuf,sizeof(sdb_app_sxfls.jylsh));
    
    /*取交易日期*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYRQ,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jyrq,sBuf,sizeof(sdb_app_sxfls.jyrq));
    
    /*取交易机构*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJG,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jyjg,sBuf,sizeof(sdb_app_sxfls.jyjg));
    
    /*取交易柜员*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYGY,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jygy,sBuf,sizeof(sdb_app_sxfls.jygy));
    
    /*取交易类型*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYLX,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jylx,sBuf,sizeof(sdb_app_sxfls.jylx));
    
    /*取交易金额*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJE,sBuf);
    trim(sBuf);
    sdb_app_sxfls.jyje = atof(sBuf);
    
    /*取交易笔数*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYBS,sBuf);
    trim(sBuf);
    /* modified by yangdong 20090328
    交易笔数默认为一笔
    sdb_app_sxfls.jybs = atof(sBuf);
    */
    if( atoi( sBuf ) > 0 )
        sdb_app_sxfls.jybs = atoi(sBuf);
    else
        sdb_app_sxfls.jybs = 1;
    /* end */

    /*取手续费*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SXF,sBuf);
    trim(sBuf);
    sdb_app_sxfls.sxfje = atof(sBuf);
    
    /*取收费流水号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFLSH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.sfls,sBuf,sizeof(sdb_app_sxfls.sfls));
    
    /*取借方帐号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JFZH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.jfzh,sBuf,sizeof(sdb_app_sxfls.jfzh));
    
    /*取贷方帐号*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_DFZH,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.dfzh,sBuf,sizeof(sdb_app_sxfls.dfzh));
    
    /*取系统内外标志*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_XTNWBZ,sBuf);
    trim(sBuf);
    memcpy(sdb_app_sxfls.xtnbz,sBuf,sizeof(sdb_app_sxfls.xtnbz));
    
    /* 收费柜员*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFJYGY,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfjygy,sBuf,sizeof( sdb_app_sxfls.sfjygy ) );
    
    /* 收费机构*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFJYJG,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfjyjg,sBuf,sizeof( sdb_app_sxfls.sfjyjg ) );
    
    /* 收费日期 */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFRQ,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfrq,sBuf,sizeof( sdb_app_sxfls.sfrq ) );
    
    /* 收费状态*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_SFZT,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.sfzt,sBuf,sizeof( sdb_app_sxfls.sfzt ) );

    /* 附加字段1*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_EXTFLD1,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.extfld1,sBuf,sizeof( sdb_app_sxfls.extfld1 ) );
    
    /* 附加字段2*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_EXTFLD2,sBuf);
    trim(sBuf);
    memcpy( sdb_app_sxfls.extfld2,sBuf,sizeof( sdb_app_sxfls.extfld2 ) );

    /* 流水状态初始值 0 正常 */
    sdb_app_sxfls.lszt[0] = '0' ;

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
  
    iRet = DBInsert("app_sxfls", SD_APP_SXFLS, NUMELE(SD_APP_SXFLS), &sdb_app_sxfls, sErrmsg);
    if( iRet < 0)
    {   /*插入流水失败*/
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("数据异常：插入数据库语句失败[%s]", sErrmsg ),
        fpub_GetCompname(lXmlhandle))
    }

    if (DCICommit() != 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        LOGRET(-1, LM_STD, Fmtmsg("数据异常：提交事务失败[%s]", DCILastError()),
        fpub_GetCompname(lXmlhandle))
    }
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;  
}
/************************************************************************
动态组件函数定义
组件函数名称:SApp_ChargeCal
组件名称:SApp_ChargeCal
组件功能:手续费计算
组件参数:无(根据手续费计算交易接口文档赋值)

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

使用限制:控制条件根据手续费控制表的控制属性名在/app/sxf/节点下获取。
         如控制属性 jffs，则从/app/sxf/jffs下取值。
项 目 组: 
程 序 员: YangDong
发布日期: 2009年6月21日
修改日期:
参数使用示例:
************************************************************************/
IRESULT SApp_ChargeCal(HXMLTREE lXmlhandle)
{
    /* 交易信息 */
    char sCpdm[16+1];                           /*产品代码*/
    char sQdbs[8+1];                            /*渠道标识*/
    char sJyje[17+1];                           /*交易金额*/
    double dJyje = 0.00;                        /*交易金额*/
    char sJybs[10+1];                           /*交易笔数*/
    int iJybs = 0;                              /*交易笔数*/
    char sJyrq[8+1];                            /*交易日期*/
    char sJsfs[1+1];                            /*计算方式*/                                      
    char sFlbs[32+1];                           /*费率标识*/
    char sKzsx[64];                             /*控制属性*/
    char sQss[16];                              /*起始参数*/
    char sJss[16];                              /*结束参数*/
    /* 手续费费率信息 */
    APP_SXFFL  sdb_app_sxffl;
    APP_CPSXFKZ  sdb_app_cpsxfkz;
    char sJslx[1+1];
    double dJscs = 0.00;                          /* 计算参数 */
    double dKjcs = 0.00;                          /* 扣减参数 */
    /* 通用控制条件 */
    char sCommon[16+1];
    int  iCommon = 0;

    char sErrmsg[512];
    char sSql[1024];
    char sBuf[255];
    char sCond[512];
    char sTmpCond[64];
    char sTmp[256];
	char sDftFlg[2];                             /* add by sunpj 2016-11-14 */
    int  iCount = 0;
    CURSOR cur;
    CURSOR cur2;
    int iRet = -1;

    double charge_amt = 0.00;                     /* 手续费   */
    double tmp_amt = 0.00;
    int    count = 0;
    
    fpub_InitSoComp(lXmlhandle);
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    /*取产品代码*/
    memset(sCpdm,0,sizeof(sCpdm));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_CPDM,sBuf);
    trim(sBuf);
    memcpy(sCpdm,sBuf,sizeof(sCpdm));

    /*取交易金额*/
    memset(sJyje,0,sizeof(sJyje));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJE,sBuf);
    trim(sBuf);
    memcpy(sJyje,sBuf,sizeof(sJyje) );
    dJyje=atof(sJyje);
    
    /*取交易笔数*/
    memset(sJybs,0,sizeof(sJybs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYBS,sBuf);
    trim(sBuf);
    memcpy(sJybs,sBuf,sizeof(sJybs) );
    iJybs = atoi( sJybs );

    /*取交易日期*/
    memset(sJyrq,0,sizeof(sJyrq));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYRQ,sBuf);
    trim(sBuf);
    memcpy(sJyrq,sBuf,sizeof(sJyrq));

    /* 取计算方式 */
    memset(sJsfs,0,sizeof(sJsfs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_JSFS,sBuf);
    trim(sBuf);
    memcpy(sJsfs,sBuf,sizeof(sJsfs) );

    /*取费率标识*/
    memset(sFlbs,0,sizeof(sFlbs));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_FLBS,sBuf);
    trim(sBuf);
    memcpy(sFlbs,sBuf,sizeof(sFlbs));

    /* add by sunpj 2016-11-14 beg*/

	/*取默认标志*/
    memset(sDftFlg,0,sizeof(sDftFlg));
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_APP_SXF_MRBZ,sBuf);
    trim(sBuf);
    memcpy(sDftFlg,sBuf,sizeof(sDftFlg));

	/* add by sunpj 2016-11-14 end*/

    /* 如计算方式为1表示直接按输入费率标识计算 */
    if( sJsfs[0] == '1' && strlen( sFlbs ) > 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("传入费率标识=[%s]",sFlbs ),"INFO");
    }
    /* 默认计算方式为0则查询费率控制表，确定费率标识 */
    else
    {
        memset( sFlbs, 0x00, sizeof( sFlbs ) );
        memset( sSql, 0x00, sizeof( sSql ) );
        memset( sCond, 0x00, sizeof( sCond ) );
        /* 取产品控制属性 */
         
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_cpsxfkz \
            WHERE cpdm ='%s' ORDER BY xh ASC",sCpdm );
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
        count = 0;

        while( 1 )
        {
            memset( sBuf, 0x00, sizeof( sBuf ) ) ;
            /* 获取控制属性名 */
            iRet = DBFetch(cur, SD_APP_CPSXFKZ, NUMELE(SD_APP_CPSXFKZ), &sdb_app_cpsxfkz, sErrmsg );
            if(iRet < 0)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIFreeCursor(cur);
                fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            if( iRet == 0 )
                break;
            count ++;
            if( count > 10 ) /* 最多10个控制属性 */
            {
                DCIFreeCursor(cur);
                fpub_SetMsg( lXmlhandle, MID_CHARGE_CAL_KZSX_ERR, MSG_CHARGE_CAL_KZSX_ERR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            /* 获取控制属性值 */
			memcpy(sBuf, sdb_app_cpsxfkz.kzsx, sizeof(sdb_app_cpsxfkz.kzsx));/* add by sunpj 2016-11-14 */
            trim( sBuf );
            memset( sTmp, 0x00, sizeof( sTmp ) );
            /* 20110929 modiefied by yangdong */
            if( sBuf[0] != '/' )
                sprintf( sTmp, "/app/sxf/%s",sBuf ); 
            else
                sprintf( sTmp, "%s",sBuf ); 
            /* end of mod */
            trim( sTmp );
            COMP_SOFTGETXML( sTmp, sKzsx);   /* 如果控制条件未从交易传入，为空值 */
            trim( sKzsx );

            /* 判断是否有通用属性ALL */
            /* modified by yang dong 20111009 */
            if( iCommon == 0 )  /* 已有通用属性则不再判断，管理台控制只有一个ALL属性  */
            {
                memset( sSql, 0x00, sizeof( sSql ) );
                memset( sTmp , 0x00, sizeof( sTmp ) );
                sprintf( sSql, "SELECT count(*) FROM app_cpsxfgx WHERE cpdm='%s'\
                    AND kztj%d='ALL' AND qyrq<='%s' AND sxrq >'%s'", \
                    sCpdm, count, sJyrq, sJyrq );
                iRet = DBSelectToVar(sErrmsg, &iCount, sSql);  
                if( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("sqlerr=[%s]", DCILastError() ),"ERROR");
                    DCIFreeCursor(cur);
                    fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            
                /*  找不到满足特定控制条件的，使用通用控制条件 ALL
                    维护费率控制关系时，应该控制最多维护一个ALL属性
                    否则将无法准确定位费率 */
                 
                if( iCount >= 1)  /* 控制属性中有ALL通用属性，保存控制条件值最后计算 */
                {
                    if( iCommon > 0 )/* 已经有一个通用控制属性，报错 */
                    {
                        DCIFreeCursor(cur);
                        fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FLBS_COMMON,MSG_CHARGE_CAL_FLBS_COMMON );
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    memset( sCommon, 0x00, sizeof( sCommon ) );
                    strcpy( sCommon, sKzsx );  
                    iCommon = count;
                    /* 20111009 modified by yangdong 
                    break;
                    */
                    continue;
                }
            }
            if( count == 1 )
                sprintf( sCond, " AND kztj1='%s' ", sKzsx );
            else
            {
                memset( sTmpCond , 0x00, sizeof( sTmpCond ) );
                sprintf( sTmpCond, " AND kztj%d='%s' ", count, sKzsx);
                strcat( sCond, sTmpCond );
            }
            /* DCIFreeCursor(cur); */ /* delete by sunpj 2016-11-14 */
        }

        DCIFreeCursor(cur);

        if( iCommon > 0 ) /* 通用属性控制处理。只允许最多一个通用属性 */
        {
            memset( sSql, 0x00, sizeof( sSql ) );
            sprintf( sSql," SELECT count(*) FROM APP_CPSXFGX \
                WHERE cpdm='%s' %s AND kztj%d='%s'  AND qyrq <='%s' AND sxrq >'%s' ",\
                sCpdm, sCond, iCommon, sCommon, sJyrq, sJyrq );
            iRet = DBSelectToVar(sErrmsg, &iCount, sSql); 
            if( iRet <= 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                         Fmtmsg("sqlerr=[%s]", DCILastError()),"ERROR");
                fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }

            memset( sTmp, 0x00, sizeof( sTmp ) );
            if( iCount == 0 ) /* 未找到精确匹配值，置为通用属性ALL */
            {
                 sprintf( sTmp, " AND kztj%d='ALL' ", iCommon );
                 strcat( sCond, sTmp );
            }
            else   /* 否则精确匹配控制条件 */
            {
                 sprintf( sTmp, " AND kztj%d='%s' ", iCommon,  sCommon );
                 strcat( sCond, sTmp );
            }
        }
        /* 根据上述控制查询费率 */
        memset( sSql, 0x00, sizeof( sSql ) );
        sprintf( sSql," SELECT flbs FROM APP_CPSXFGX \
                           WHERE cpdm='%s' %s AND qyrq <='%s' AND sxrq >'%s' ", sCpdm, sCond,sJyrq, sJyrq );
		/* modify by sunpj 2016-11-14 */
        /* iRet = DBSelectToVarChar(sErrmsg, sFlbs, sSql1); */
		iRet = DBSelectToVarChar(sErrmsg, sFlbs, sSql);
        /*没有记录则出错返回*/
        if( iRet == 0 )
        {
		    if (0 == strcmp(sDftFlg, "Y")) /* add by sunpj 2016-11-14 */
		    {
				/*取默认费率*/
				memset(sFlbs,0,sizeof(sFlbs));
				COMP_SOFTGETXML(XMLNM_APP_SXF_MRFL,sFlbs);
		    }
		    else
		    {
                fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FLBS_NOTFOUND ,MSG_CHARGE_CAL_FLBS_NOTFOUND );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
		    }
        }
        else if( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("sqlerr=[%s]", DCILastError() ),"ERROR");
            fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
    }
    trim( sFlbs );
    /* 根据费率标识，查询费率信息 ,只取第一条记录 */
    memset( sSql, 0x00, sizeof( sSql ) );
	/* modify by sunpj 2016-11-14 */
    /* snprintf( sSql, sizeof( sSql ), "SELECT * FROM APP_SXFFL WHERE flbs='%s' AND ROWNUM <= 1 ", sFlbs ); */
    snprintf( sSql, sizeof( sSql ), "SELECT * FROM APP_SXFFL WHERE flbs='%s' FETCH FIRST 1 ROWS ONLY ", sFlbs );   
    iRet = fprv_SelToStruct( sSql, SD_APP_SXFFL, NUMELE(SD_APP_SXFFL), &sdb_app_sxffl); 
    if( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FL_NOTFOUND ,MSG_CHARGE_CAL_FL_NOTFOUND );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    else if( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                      Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
        fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    dKjcs = sdb_app_sxffl.kjcs;
    if( sdb_app_sxffl.fdbz[0] == '0')  /* 固定费率 */
    {
        dJscs = sdb_app_sxffl.jscs;
        
        if( sdb_app_sxffl.jslx[0] == '1') /*计算参数类型为金额*/
        {
            charge_amt = iJybs * dJscs;
        }
        else if( sdb_app_sxffl.jslx[0] == '2' )/*计算参数类型为百分比*/
        {
            if( sdb_app_sxffl.nwkbz[0] == '1')   /*扣款方式为内扣*/
            {
                tmp_amt = 0.00;
                tmp_amt = dJyje/( 1 + ( dJscs/100 ) );
                charge_amt = dJyje - tmp_amt;
            }
            else                  /* 默认外扣 */
            {
                charge_amt = dJyje * dJscs/100 ;
            }
        }
        else      /* 计算参数类型错 */
        {
            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        /* delete by sc 扣减参数统一后面处理，需要根据kjbz来进行判断 */
        /*charge_amt =  charge_amt - dKjcs ;*/  /* 减去扣减参数 */
        /* delete end */
    }
    else if( sdb_app_sxffl.fdbz[0] == '1')    /* 浮动费率 */
    {
        if( sdb_app_sxffl.nwkbz[0] == '1' )  /* 浮动费率时不允许内扣 */
        {
            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FD1_ERR ,MSG_CHARGE_CAL_FD1_ERR  );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }

        dJscs = 0.00;
        /*dKjcs = 0.00;*/
      
        if(sdb_app_sxffl.ljbz[0] == '0')   /*不累加 */
        {
            if( sdb_app_sxffl.fdlx[0] == '2')   /* 按交易金额浮动 */
            {
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                if( sdb_app_sxffl.bhbz[0] == '1')   /*包含上限*/
                {
                    snprintf( sSql1, sizeof( sSql ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND  %d >= qss AND %d < jss )",sFlbs, dJyje, dJyje );
                }
                else if(sdb_app_sxffl.bhbz[0] == '0')/*包含下限*/
                {
                    snprintf( sSql1, sizeof( sSql ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND ( %f > qss AND %f <= jss )",sFlbs, dJyje, dJyje );
                }
                else   /* 包含标志错 */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FDBH_ERR , MSG_CHARGE_CAL_FDBH_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                iRet = DBSelectToMultiVar( sErrmsg, sSql1, sJslx, &dJscs ) ; 
                if( iRet == 0 )  /* 未找到费率信息 */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FL_NOTFOUND , MSG_CHARGE_CAL_FL_NOTFOUND  );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                else if( iRet == 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                    fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }

                if( sJslx[0] == '1')  /* 参数类型为金额 */
                    charge_amt = dJscs * iJybs;
                else if( sJslx[0] == '2')  /* 参数为百分比 */            
                    charge_amt = dJscs * dJyje/100 ;
                else
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }

            else if( sdb_app_sxffl.fdlx[0] == '1')   /*按交易笔数动 */
            {
                if( sdb_app_sxffl.bhbz[0] == '1')   /*包含上限*/
                {
                    snprintf( sSql1, sizeof( sSql1 ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND ( %d >= qss AND %d < jss ) ", sFlbs, iJybs, iJybs );
                }
                else if(sdb_app_sxffl.bhbz[0] == '0')/*包含下限*/
                {
                    snprintf( sSql1, sizeof( sSql1 ), "SELECT jslx, jscs FROM app_sxffl \
                             WHERE flbs='%s' AND ( %d > qss AND %d <= jss ) ", sFlbs, iJybs, iJybs );
                }
                else /* 浮动包含标志错 */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FDBH_ERR , MSG_CHARGE_CAL_FDBH_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
         
                iRet = DBSelectToMultiVar( sErrmsg, sSql1, sJslx, &dJscs ) ; 
                if( iRet == 0 ) /* 未找到费率信息 */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_FL_NOTFOUND , MSG_CHARGE_CAL_FL_NOTFOUND  );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                else if(iRet < 0)
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                    fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }

                if( sJslx[0] == '1')  /*  计算参数为金额 */
                    charge_amt = dJscs * iJybs;
                else if( sJslx[0] == '2')  /*  计算参数为百分比 */
                    charge_amt = dJscs * dJyje / 100 ;
                else /* 计算参数类型错 */
                {
                    fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
            else /* 只支持按金额浮动或者笔数浮动 */
            {
                fpub_SetMsg(lXmlhandle, MID_CHARGE_CAL_FDTJ_ERR, MSG_CHARGE_CAL_FDTJ_ERR );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            /* 扣减扣减参数 */
            /* delete by sc 扣减参数统一后面处理，需要根据kjbz来进行判断 */
            /*charge_amt -= dKjcs ;*/
        }
        else if( sdb_app_sxffl.ljbz[0] == '1' )   /* 累加 */
        {
            /* 查询所有费率段 按起始参数升序排列 */
            snprintf( sSql1, sizeof( sSql1 ), " SELECT  * FROM app_sxffl\
                       WHERE flbs = '%s' ORDER by qss ASC ",sFlbs );
            if ((cur2 = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }
            if (DCIExecute(cur2) == -1)
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIFreeCursor(cur);
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }

            if( sdb_app_sxffl.fdlx[0] == '2')   /* 按交易金额浮动 */
            {
                while( 1 )
                {
                    memset( sQss , 0x00, sizeof( sQss ) );
                    memset( sJss , 0x00, sizeof( sJss ) );
                    dJscs = 0.00;
                    /*dKjcs = 0.00;*/

                    iRet = DBFetch(cur2, SD_APP_SXFFL, NUMELE(SD_APP_SXFFL), &sdb_app_sxffl, sErrmsg );
                    if( iRet == 0 )
                    {
                        /* 此时应该有金额达到配置的结束参数下限，有部分交易金额未计算手续费 */
                        break;
                    }
                    else if(iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                        DCIFreeCursor(cur2);
                        fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    strcpy( sJslx, sdb_app_sxffl.jslx );
                    strcpy( sQss, sdb_app_sxffl.qss );
                    strcpy( sJss, sdb_app_sxffl.jss );
                    dJscs = sdb_app_sxffl.jscs ;

                    if( dJyje > atof( sJss ) )
                    { 
                        if( sJslx[0] == '2')  /* 参数为百分比 */            
                        {
                            charge_amt += ( atof( sJss ) - atof( sQss ) ) *  dJscs / 100 ;
                        }
                        else    /* 按金额浮动累进的，不允许按交易笔数计算，即参数不能为金额 */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc 扣减参数统一后面处理，需要根据kjbz来进行判断 */
                        /*charge_amt -= dKjcs;*/
                    }
                    else /*  交易金额小于等于结束参数，退出循环,最后一次计算 */
                    {
                        if( sJslx[0] == '2')  /* 参数为百分比 */            
                        {
                            charge_amt += ( dJyje - atof( sQss ) ) *  dJscs / 100 ;
                        }
                        else    /* 按金额浮动累进的，不允许按交易笔数计算，即参数不能为金额 */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc 扣减参数统一后面处理，需要根据kjbz来进行判断 */
                        /*charge_amt -= dKjcs;*/
                        break;  /* 计算结束，跳出循环 */
                    }

                }
            }
            else if( sdb_app_sxffl.fdlx[0] == '1')   /*按交易笔数浮动 */
            {
                while( 1 )
                {
                    memset( sQss , 0x00, sizeof( sQss ) );
                    memset( sJss , 0x00, sizeof( sJss ) );
                    dJscs = 0.00;
                    /*dKjcs = 0.00;*/
                    iRet = DBFetch(cur2, SD_APP_SXFFL, NUMELE(SD_APP_SXFFL), &sdb_app_sxffl, sErrmsg );
                    if( iRet == 0 )
                    {
                        /* 此时应该有金额达到配置的结束参数下限，有部分交易金额未计算手续费 */
                        break;
                    }
                    else if(iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                               Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
                        DCIFreeCursor(cur2);
                        fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    strcpy( sJslx, sdb_app_sxffl.jslx );
                    strcpy( sQss, sdb_app_sxffl.qss );
                    strcpy( sJss, sdb_app_sxffl.jss );
                    dJscs = sdb_app_sxffl.jscs ;

                    if( iJybs > atoi( sJss ) )
                    { 
                        if( sJslx[0] == '1')       /* 参数类型为金额 */
                        {
                            charge_amt += ( atoi( sJss ) - atoi( sQss ) ) * dJscs ;
                        }
                        else    /* 按交易笔数浮动累进的，不允许按交易金额计算，即参数不能为百分比 */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc 扣减参数统一后面处理，需要根据kjbz来进行判断 */
                        /*charge_amt -= dKjcs;*/
                    }
                    else
                    {
                        if( sJslx[0] == '1')       /* 参数类型为金额 */
                        {
                            charge_amt += ( iJybs - atoi( sQss ) ) * dJscs ;
                        }
                        else    /* 按交易笔数浮动累进的，不允许按交易金额计算，即参数不能为百分比 */
                        {
                            DCIFreeCursor(cur2);
                            fpub_SetMsg(lXmlhandle,MID_CHARGE_CAL_CSLX_ERR ,MSG_CHARGE_CAL_CSLX_ERR );
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                        /* delete by sc 扣减参数统一后面处理，需要根据kjbz来进行判断 */
                        /*charge_amt -= dKjcs;*/
                        break;  /* 计算结束，跳出循环 */
                    }
                }
            }
           else
           {
               DCIFreeCursor(cur2);
               fpub_SetMsg(lXmlhandle, MID_CHARGE_CAL_LJBZ_ERR, MSG_CHARGE_CAL_LJBZ_ERR );
               fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
               return COMPRET_FAIL;
           }
           DCIFreeCursor(cur2);
       }
       else
       {
           fpub_SetMsg(lXmlhandle, MID_CHARGE_CAL_FDLX_ERR, MSG_CHARGE_CAL_FDLX_ERR );
           fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
           return COMPRET_FAIL;
       }
    }
      /* add by SC 20110607 手续费扣减计算 */
      if( sdb_app_sxffl.kjbz[0] == '2' )/* 手续费扣减,2:百分比,1:金额,0:无 */
    {
        charge_amt = charge_amt * ( 1 -  dKjcs / 100 );
    }
    else if( sdb_app_sxffl.kjbz[0] == '1' )
    {
        charge_amt = charge_amt - dKjcs;
    }
      /* add by SC ---end */

    if(sdb_app_sxffl.sxxkz[0] == '0') /* 上下限控制 */
    {
        /*  20090716 modified by yangdong 上下限金额判断错误
        charge_amt = max( sdb_app_sxffl.sxje, min( charge_amt, sdb_app_sxffl.xxje ) );
        */
        charge_amt = max( sdb_app_sxffl.xxje, min( charge_amt, sdb_app_sxffl.sxje ) );
    }
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("手续费=[%.2f]",charge_amt),"DEBUG");

    /* 将手续费写入响应XML节点 */
    memset(sTmp,0,sizeof(sTmp));
    sprintf(sTmp,"%.2f",charge_amt);
    COMP_HARDSETXML(XMLNM_APP_SXF_SXF,sTmp );

    /* 将费率标识写入响应XML节点 */
    COMP_HARDSETXML(XMLNM_APP_SXF_FLBS,sFlbs);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称:SApp_ChargeReport
组件名称:SApp_ChargeReport
组件功能:手续费基础报表 
组件参数:
 序号 参数类型  参数名称       资源类别       缺省值            可空  参数说明
   1    int     pg_num                                           yes  每页行数 
   2    char    report_type                                      no   报表类型


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
修改日期:2009年2月5日
参数使用示例:
************************************************************************/
IRESULT SApp_ChargeReport(HXMLTREE lXmlhandle)
{
    APP_SXFLS sSxfls;
    char sQdbs[8+1];                            /*渠道标识*/
    char sCpdm[16+1];                            /*产品代码*/
    char sJyjg[16+1];                           /*交易机构*/ 
    char sYybs[32+1];                           /*应用标识*/
    char sQsrq[8+1];                            /*起始日期*/
    char sJsrq[8+1];                            /*结束日期*/
    char sSql[1024];                            /**/
    int  iParas;
    char sFile[128];
    char sBuf[256];
    char sTmpBuf[256];
    int  iPage_num;
    int  iReport_type;
    int  iCount = 0;
    FILE * fp;
    char sErrmsg[512];
    int iRet = -1;
    CURSOR cur;
  
    fpub_InitSoComp(lXmlhandle);
  
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    COMP_PARACOUNTCHKMIN(2)
    memset( sBuf,0,sizeof(sBuf) );
    COMP_GETPARSEPARAS(1,sBuf,"每页行数")
    iPage_num = atoi( sBuf );
    if( iPage_num == 0 )
        iPage_num = 35;  /* 默认35行每页 */
    COMP_GETPARSEPARAS(2,sBuf, "报表类型");
    iReport_type = atoi( sBuf );

    memset( sFile, 0, sizeof( sFile ) );
    memset( sCpdm, 0, sizeof( sCpdm ) );
    memset( sJyjg, 0, sizeof( sJyjg ) );
    memset( sQdbs, 0, sizeof( sQdbs ) );
    memset( sYybs, 0, sizeof( sYybs ) );
    memset( sQsrq, 0, sizeof( sQsrq ) );
    memset( sJsrq, 0, sizeof( sJsrq ) );
    memset( sBuf, 0, sizeof( sBuf ) );
    memset( sTmpBuf, 0, sizeof( sTmpBuf ) );

    /* 产品代码 */
    COMP_SOFTGETXML(XMLNM_APP_SXF_CPDM, sBuf);
    trim( sBuf );
    memcpy( sCpdm,  sBuf,  sizeof( sCpdm ) );
  
    /* 渠道标识 */
    COMP_SOFTGETXML(XMLNM_APP_SXF_QDBS, sBuf);
    trim( sBuf );
    memcpy( sQdbs,  sBuf,  sizeof( sQdbs ) );
  
    /* 交易机构 */
    COMP_SOFTGETXML(XMLNM_APP_SXF_JYJG, sBuf);
    trim( sBuf );
    memcpy( sJyjg,  sBuf,  sizeof( sJyjg ) );

    /* 起始日期 */
    COMP_SOFTGETXML(XMLNM_APP_SXF_QSRQ, sBuf);
    trim( sBuf );
    memcpy( sQsrq,  sBuf,  sizeof( sQsrq ) );
  
    /* 结束日期 */
    COMP_SOFTGETXML(XMLNM_APP_SXF_JSRQ, sBuf);
    trim( sBuf );
    memcpy( sJsrq,  sBuf,  sizeof( sJsrq ) );

    memset( sSql, 0, sizeof(sSql) );
    if( iReport_type == 0 )  /* 明细报表 */
    {
        sprintf(sSql, " SELECT * FROM app_sxfls WHERE 1=1 " );
    }
    else{
        sprintf(sSql, " SELECT  cpdm, qdbs,jyjg, NVL(sum(jyje),0.00),NVL(sum(jybs),0),NVL(sum(sxfje),0.00 )  FROM app_sxfls WHERE 1=1 " );
    }
    if( strlen( sCpdm ) > 0 )
    {
         sprintf( sTmpBuf, "and cpdm='%s' ", sCpdm );
         strcat( sSql, sTmpBuf );
    }
    if( strlen( sQdbs ) > 0 )
    {
         sprintf( sTmpBuf, "and qdbs='%s' ", sQdbs );
         strcat( sSql, sTmpBuf );
    }
    if( strlen( sJyjg ) > 0 ) 
    {
        sprintf( sTmpBuf, "and jyjg='%s' ", sJyjg );
        strcat( sSql, sTmpBuf );
    }
    if( strlen( sQsrq ) > 0 )
    {
         sprintf( sTmpBuf, "and jyrq>='%s' ", sQsrq );
         strcat( sSql, sTmpBuf );
    }
    if( strlen( sJsrq ) > 0 )
    {
         sprintf( sTmpBuf, "and jyrq<='%s' ", sJsrq );
         strcat( sSql, sTmpBuf );
    }
   
    if( iReport_type == 0 )  /* 明细报表 */
    {
        strcat( sSql ," ORDER BY ptrq,cpdm,qdbs,jyjg " );
    }
    else if( iReport_type == 1 )  /* 统计报表 */
    {
         strcat(sSql, "  GROUP BY cpdm,qdbs,jyjg " );
    }
    else
    {
        fpub_SetMsg(lXmlhandle,MID_CHARGE_RPTTYPE_ERR,MSG_CHARGE_RPTTYPE_ERR );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sql str[%s]",sSql ),"DEBUG");
  
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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

    memset( sBuf, 0, sizeof( sBuf ) );
    COMP_SOFTGETXML("/pub/zhqzlsh",sBuf);
    snprintf( sFile,sizeof( sFile ),"%s/file/charge_report%s%s%s",getenv( "HOME" ), sCpdm,sJyjg,sBuf );
    if( ( fp = ( fopen( sFile,"w+" ) ) ) == NULL )
    {
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" 打开文件失败,file[%s],error[%s]",sFile,strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("打开文件失败"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    fprintf( fp, "\n\n" );
    if( iReport_type == 0 )
    {
        fprintf( fp,"                                    手续费明细报表   \n\n" );
        fprintf( fp," 起止日期 %8s - %8s                  \n", sQsrq, sJsrq ); 
        fprintf( fp,"┌--------┬--------┬----------------┬--------┬----------------┬--------┬----------------┐\n");
        fprintf( fp,"|产品代码|渠道标识|    交易机构    |交易日期|    交易金额    |交易笔数|    手续费      | \n");
    }
    else
    {
        fprintf( fp,"                                  手续费统计报表   \n" );
        fprintf( fp," 起止日期 %8s - %8s                  \n", sQsrq, sJsrq ); 
        fprintf( fp,"┌--------┬--------┬----------------┬----------------┬--------┬----------------┐\n");
        fprintf( fp,"|产品代码|渠道标识|   交易机构     |   交易金额     |交易笔数|   手续费合计   |\n" );
    }
    

    while( 1 ) 
    {
        memset( &sSxfls, 0 , sizeof( sSxfls ) ); 
        if( iReport_type == 0 ){
            iRet = DBFetch(cur, SD_APP_SXFLS, NUMELE(SD_APP_SXFLS), &sSxfls, sErrmsg ); 
        }
        else{
            iRet = DBSelectToMultiVar( sErrmsg, sSql, sSxfls.cpdm, sSxfls.qdbs, sSxfls.jyjg, sSxfls.jyje, sSxfls.jybs, sSxfls.sxfje );
        }
        if( iRet < 0 )      
        {
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("sqlerr=[%s]",DCILastError()),"ERROR");
            fclose( fp );
            DCIFreeCursor(cur);
            fpub_SetMsg( lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if( iRet == 0 )
            break;
        if(  iCount != 0 &&( iCount % iPage_num ) == 0 ) /* 换页控制 */
        {
            if( iReport_type == 0 )
            {
                fprintf( fp,"└--------┴--------┴----------------┴--------┴----------------┴--------┴----------------┘ \n " );
                fprintf( fp,"                                                                                                         第 %3d 页 " , iCount/iPage_num );
                fprintf( fp,"\f" );
                fprintf( fp,"┌--------┬--------┬----------------┬--------┬----------------┬--------┬----------------┐\n");
                fprintf( fp,"|产品代码|渠道标识|      机构标识  |交易日期|    交易金额    |交易笔数|    手续费      | \n");
            }
            else
            {
                fprintf( fp,"└--------┴--------┴----------------┴----------------┴--------┴----------------┘ \n  " );
                fprintf( fp,"                                                                                                         第 %3d 页 " , iCount/iPage_num );
                fprintf( fp,"\f" );
                fprintf( fp,"┌--------┬--------┬----------------┬----------------┬--------┬----------------┐\n");
                fprintf( fp,"|产品代码|渠道标识|    机构标识    |   交易金额     |交易笔数|   手续费合计   |\n" );
            }
        }

        if( iReport_type == 0 )
        {
            fprintf( fp, "├--------┼--------┼----------------┼--------┼----------------┼--------┼----------------┤\n");

            fprintf( fp, "|%8s|%8s|%16s|%8s|%16.2f|%8d|%16.2f|  \n",\
                 trim( sSxfls.cpdm ), trim( sSxfls.qdbs ), trim( sSxfls.jyjg ), \
                     trim( sSxfls.jyrq ), sSxfls.jyje, sSxfls.jybs, sSxfls.sxfje );
        }
        else
        {
            fprintf( fp, "├--------┼--------┼----------------┼----------------┼--------┼----------------┤\n");
            fprintf( fp, "|%8s|%8s|%16s|%16.2f|%8d|%16.2f|  \n",\
                 trim( sSxfls.cpdm ), trim( sSxfls.qdbs ), trim( sSxfls.jyjg ), \
                                        sSxfls.jyje,sSxfls.jybs, sSxfls.sxfje );
        }
        iCount ++;
    }
    if( iReport_type == 0 )
        fprintf( fp,"└--------┴--------┴----------------┴--------┴----------------┴--------┴----------------┘ \n " );
    else
        fprintf( fp,"└--------┴--------┴----------------┴----------------┴--------┴----------------┘ \n  " );
    fprintf( fp,"                                                                  第 %3d 页  \n  " , iCount/iPage_num + 1 );
    fclose( fp );
    DCIFreeCursor(cur);

    /* 输出报表文件名 */
    COMP_HARDSETXML(XMLNM_APP_SXF_BBWJMC, sFile );

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG");
  
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return 0;
}
