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
/******************************************************************************
组件名称: SAGENT_WIAMP_CHECK
组件功能: 中间业务与卡券平台对账
处理说明：
组件参数:
序号 参数名称         资源类别   缺省值         是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
 
项 目 组:
程 序 员: zhandongdong
发布日期:2018年08月
修改日期:
******************************************************************************/
IRESULT SAGENT_WIAMP_CHECK(HXMLTREE lXmlhandle)
{
    COUPON_WIAMP_DZLSB sdb_coupon_wiamp_dzlsb;
    COUPON_ZJYW_DZLSB  sdb_coupon_zjyw_dzlsb;
    COUPON_DZBPB       sdb_coupon_dzbpb;
    COUPON_ZJYW_RZZT   sdb_coupon_zjyw_rzzt;
        
    char sRunCpdmSql[512];
    char sDzrq[8+1];
    char sPtrq[8+1];
    char sBuf[256];
    int   iParas,i;
    int   iCount = 0;
    int   iFlag = 0;  /* 0 对账平 !0 对账不平 */
    int   iRet =-1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);
 
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*组件参数检查*/
    COMP_PARACOUNTCHK(2)
    
    /*对账日期*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"对账日期")
    trim(sBuf);
    memset(sDzrq,0,sizeof(sDzrq));
    memcpy(sDzrq,sBuf,sizeof(sDzrq)-1);
    /*平台日期*/
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"平台日期")
    trim(sBuf);
    memset(sPtrq,0,sizeof(sPtrq));
    memcpy(sPtrq,sBuf,sizeof(sPtrq)-1);

    iRet = DCIBegin();
    if( iRet != 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
        
    /*卡券平台有,中间业务无的记录--BEG*/
    iCount = 0;
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    sprintf(sRunCpdmSql, "SELECT * FROM coupon_wiamp_dzlsb WHERE dzrq='%s' AND orderstatus='1'AND trim(changeorderno) NOT IN \
    (SELECT DISTINCT trim(changeorderno) FROM coupon_zjyw_dzlsb WHERE dzrq='%s' AND ORDERSTATUS='1')", sDzrq,sDzrq);
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
    memset(&sdb_coupon_wiamp_dzlsb, 0, sizeof(sdb_coupon_wiamp_dzlsb));
    while( ( iRet = DBFetch(cur, SD_COUPON_WIAMP_DZLSB, NUMELE(SD_COUPON_WIAMP_DZLSB), &sdb_coupon_wiamp_dzlsb, sErrmsg ) ) > 0 )
    {
        iFlag ++; /*表明有不平的记录*/
        /*登记不平流水表*/
        memset(&sdb_coupon_dzbpb, 0, sizeof(sdb_coupon_dzbpb));
        memcpy(sdb_coupon_dzbpb.dzrq,sDzrq,sizeof(sdb_coupon_dzbpb.dzrq)-1);
        trim( sdb_coupon_dzbpb.dzrq);
        memcpy(sdb_coupon_dzbpb.ptrq,sPtrq,sizeof(sdb_coupon_dzbpb.ptrq)-1);
        trim( sdb_coupon_dzbpb.ptrq);
        memcpy(sdb_coupon_dzbpb.changeorderno,sdb_coupon_wiamp_dzlsb.changeorderno,sizeof(sdb_coupon_dzbpb.changeorderno)-1);
        trim( sdb_coupon_dzbpb.changeorderno);
        memcpy(sdb_coupon_dzbpb.weiorderno,sdb_coupon_wiamp_dzlsb.weiorderno,sizeof(sdb_coupon_dzbpb.weiorderno)-1);
        trim( sdb_coupon_dzbpb.weiorderno);
        memcpy(sdb_coupon_dzbpb.couponno,sdb_coupon_wiamp_dzlsb.couponno,sizeof(sdb_coupon_dzbpb.couponno)-1);
        trim( sdb_coupon_dzbpb.couponno);
        memcpy(sdb_coupon_dzbpb.status,"1",1); /*卡券平台多*/
        sdb_coupon_dzbpb.wiamp_ordernum=sdb_coupon_wiamp_dzlsb.couponnum;
        sdb_coupon_dzbpb.zjyw_ordernum=0;
        
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
        Fmtmsg("对账不平,卡券平台多：对账日期[%s] 换购订单号[%s] ",sDzrq, sdb_coupon_dzbpb.changeorderno),"INFO");
        /*登记对账不平表*/
        iRet = DBInsert("coupon_dzbpb", SD_COUPON_DZBPB, NUMELE(SD_COUPON_DZBPB), &sdb_coupon_dzbpb, sErrmsg);
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
        iFlag++;
    }
    DCIFreeCursor(cur);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("卡券平台有,中间业务无-笔数[%d]", iCount ),"INFO");
    /*卡券平台有,中间业务无的记录--END*/


    /* 卡券平台无,中间业务有的记录 --BEG*/
    iCount = 0;
    memset(sRunCpdmSql, 0, sizeof(sRunCpdmSql));
    sprintf(sRunCpdmSql, "SELECT * FROM coupon_zjyw_dzlsb WHERE dzrq='%s' AND orderstatus='1' AND trim(changeorderno) NOT IN\
        (SELECT DISTINCT trim(changeorderno) FROM coupon_wiamp_dzlsb WHERE dzrq='%s' AND orderstatus='1' )",sDzrq, sDzrq);
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
    
    memset(&sdb_coupon_zjyw_dzlsb, 0, sizeof(sdb_coupon_zjyw_dzlsb));
    while( ( iRet = DBFetch(cur, SD_COUPON_ZJYW_DZLSB, NUMELE(SD_COUPON_ZJYW_DZLSB), &sdb_coupon_zjyw_dzlsb, sErrmsg ) ) > 0 )
    {
        /*登记不平流水表*/
        memset(&sdb_coupon_dzbpb, 0, sizeof(sdb_coupon_dzbpb));
        memset(&sdb_coupon_dzbpb, 0, sizeof(sdb_coupon_dzbpb));
        memcpy(sdb_coupon_dzbpb.dzrq,sDzrq,sizeof(sdb_coupon_dzbpb.dzrq)-1);
        trim( sdb_coupon_dzbpb.dzrq);
        memcpy(sdb_coupon_dzbpb.ptrq,sPtrq,sizeof(sdb_coupon_dzbpb.ptrq)-1);
        trim( sdb_coupon_dzbpb.ptrq);
        memcpy(sdb_coupon_dzbpb.changeorderno,sdb_coupon_zjyw_dzlsb.changeorderno,sizeof(sdb_coupon_dzbpb.changeorderno)-1);
        trim( sdb_coupon_dzbpb.changeorderno);
        memcpy(sdb_coupon_dzbpb.weiorderno,sdb_coupon_zjyw_dzlsb.weiorderno,sizeof(sdb_coupon_dzbpb.weiorderno)-1);
        trim( sdb_coupon_dzbpb.weiorderno);
        memcpy(sdb_coupon_dzbpb.couponno,sdb_coupon_zjyw_dzlsb.couponno,sizeof(sdb_coupon_dzbpb.couponno)-1);
        trim( sdb_coupon_dzbpb.couponno);
        memcpy(sdb_coupon_dzbpb.status,"2",1); /*中间业务多*/
        sdb_coupon_dzbpb.wiamp_ordernum=0;
        sdb_coupon_dzbpb.zjyw_ordernum=sdb_coupon_zjyw_dzlsb.couponnum;

        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,\
        Fmtmsg("对账不平,中间业务多：对账日期[%s] 换购订单号[%s] ",sDzrq, sdb_coupon_dzbpb.changeorderno),"INFO");   
        iRet = DBInsert("coupon_dzbpb", SD_COUPON_DZBPB, NUMELE(SD_COUPON_DZBPB), &sdb_coupon_dzbpb, sErrmsg);
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
        iFlag++;

    }
    DCIFreeCursor(cur);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("卡券平台无中间业务有笔数[%d]", iCount ),"INFO");
    /*主机无,平台有记录 --END*/      
    
    /*数量不一致的情况不检查了*/
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("数量不一致的情况不检查了"),"INFO");
    
    /**更新日终状态表**/
    memset( sRunCpdmSql, 0x00, sizeof( sRunCpdmSql ) );
    if( iFlag == 0 )
    {
          /* 对账状态 0 平*/
        sprintf(sRunCpdmSql, "UPDATE coupon_zjyw_rzzt SET  status='0' WHERE dzrq='%s' AND ptrq='%s'", sDzrq,sPtrq);
    }
    else
    {
          /* 对账状态 1 不平*/
        sprintf(sRunCpdmSql, "UPDATE coupon_zjyw_rzzt SET  status='1' WHERE dzrq='%s' AND ptrq='%s'", sDzrq,sPtrq);
    }
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("sRunCpdmSql=[%s]",sRunCpdmSql),"INFO");
    iRet = DCIExecuteDirect( sRunCpdmSql );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC; 
}

