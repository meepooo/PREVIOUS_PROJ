/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V3.0.00
操作系统:AIX5.3
文件名称:SYW_TIPS_ONLINE_DRC.c
文件描述:TIPS单笔实时交易
项 目 组:TIPS专用前置产品组
程 序 员:sunpj
发布日期:
修    订:
修改日期:
*********************************************************************/

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include "gaps_head.h"

#include "../../eh/tips_drls.h"/* 当日流水表 */
#include "../../eh/DRC/tips_wtgxdj_drc.h"/* 委托关系登记 */
#include "../../eh/DRC/tips_wtgxdjlsls_drc.h"/* 委托关系登记历史流水 */
#include "../../eh/DRC/tips_taxtypemx_drc.h"/* 税种明细表 */
#include "../../eh/DRC/tips_taxsubjectlist_drc.h"/* 税目明细表 */


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_AddSFXY_DRC
组件名称: 签约三方协议
组件功能: 
  签约三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：
   前提条件：建立、删除前、完成对账号上送主机的校验
        1 建立
          征收机关校验
          查询征收机关、纳税人账号、支付行行号记录是否存在。
            存在->判断协议书号是否和前台传送的一致，
                     一致，修改委托关系状态->0，返回成功
                     不一致,交易失败，征收机关、纳税人账号、支付行行号对应关系已存在。                                                      
            不存在，继续
          查询协议书号在数据库中是否已存在、
            存在->交易失败,协议书对应的征收机关、纳税人账号、支付行行号记录不符。 
            不存在->新增三方协议。

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记    tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: sunpj
发布日期: 2017年3月15日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_AddSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sProtocolNo[60+1];/* 协议书号 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sPayAcct[32+1];/* 付款账号 */
    char sPayBkCode[12+1];/* 付款行行号 */
    char sPayOpBkCode[12+1];/* 付款开户行号 */
    char sYzbz_tmp[1+1];
    SDB_TIPS_WTGXDJ stWtgxdj;
    SDB_TIPS_WTGXDJ stWtgxdj1;
    int iCount;

    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    
    char sSql1[512];  /*DCI 执行sql语句*/
    char sErrmsg[256]; /*DCI 执行sql语句返回错误信息*/ 
    int iRet=0;

    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "付款行行号")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("签约三方协议开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s],付款行行号[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT count(*) FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);         
    iRet = DBSelectToVar( sErrmsg, &iCount, sSql1) ; 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
        fpub_GetCompname(lXmlhandle))
    }
    if ( iCount > 0 )
    {
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof(sSql1), "SELECT yzbz FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);         
        iRet = DBSelectToVar( sErrmsg, &sYzbz_tmp, sSql1) ;             
        trim(sYzbz_tmp); 
        if( strcmp(sYzbz_tmp,"2")==0 )
        {
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            snprintf( sSql1, sizeof(sSql1), "delete FROM tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
            iRet = DCIExecuteDirect(sSql1);
            if ( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
                fpub_SetMsg(lXmlhandle, 24319, "删除三方协议失败");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除三方协议失败"),
                fpub_GetCompname(lXmlhandle))
            }
        }
        else
        {
            fpub_SetMsg(lXmlhandle, 24325, "三方协议已存在,签约失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议已存在,签约失败"),
            fpub_GetCompname(lXmlhandle))        
        }
    }
    
    /*协议书号未曾使用,开始增加三方协议*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(&stWtgxdj,0,sizeof(stWtgxdj));

    /* 生成银行协议书序号 */
    iRet = 0;
    memset(sBankProNo,0x00,sizeof(sBankProNo));
    iRet = prv_tips_genxh2(1,sBuf,sBankProNo);
    if (iRet < 0)
    {
        fpub_SetMsg(lXmlhandle, 24326, "生成银行内部协议号失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("生成银行内部协议号失败"),
            fpub_GetCompname(lXmlhandle)) 
    }
    trim(sBankProNo);
    COMP_SOFTSETXML("/tips/BANKProtocolNo",sBankProNo)
    
    memset(&stWtgxdj,0,sizeof(stWtgxdj));

    /*银行协议书号*/
    pstrcopy(stWtgxdj.bankprotocolno,sBankProNo,sizeof(stWtgxdj.bankprotocolno));

    /*委托关系状态*/ 
    stWtgxdj.wtgxzt[0]='0';

    /*协议书号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/ProtocolNo",sBuf)
    pstrcopy(stWtgxdj.protocolno, sBuf, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "协议书号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("协议书号不能为空"),
            fpub_GetCompname(lXmlhandle))        
    }

    /*征收机关代码*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode",sBuf)
    pstrcopy(stWtgxdj.taxorgcode, sBuf, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "征收机关代码不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_taxcodeinfo WHERE taxorgcode='%s'",sTaxOrgCode);         
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24321, "查询征收机关代码失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询征收机关代码失败"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "征收机关代码不存在");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码不存在"),
            fpub_GetCompname(lXmlhandle))        
    }
    
    /*纳税人编码*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人编码不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人编码不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*纳税人名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
     if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人名称不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人名称不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
   /*缴款单位名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
     if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "缴款单位名称不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("缴款单位名称不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* 付款行行号*/
    pstrcopy(stWtgxdj.paybkcode, sPayBkCode, sizeof(stWtgxdj.paybkcode));
    if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款行行号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* 付款帐户*/ 
    pstrcopy(stWtgxdj.payacct, sPayAcct, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款帐户不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款帐户不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*客户代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));

    /*关系登记日期*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/gxdjrq",sBuf)
    pstrcopy(stWtgxdj.gxdjrq, sBuf, sizeof(stWtgxdj.gxdjrq));
    
    /*登记流水号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.djlsh, sBuf, sizeof(stWtgxdj.djlsh));

    /*机构代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.djjgdh, sBuf, sizeof(stWtgxdj.djjgdh));

    /*地区代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.djdqdh, sBuf, sizeof(stWtgxdj.djdqdh));

    /*交易柜员*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.djjygy, sBuf, sizeof(stWtgxdj.djjygy));

    /*终端代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.djzddh, sBuf, sizeof(stWtgxdj.djzddh));

    /*扩展标志*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* 帐户类型 */  
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[0]='0'; 
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* 钞汇标志 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }else
    {
        stWtgxdj.kzbz[1]='0';
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* 卡折标志 P：账户 C：卡 默认是账户P*/
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[2]='P'; 
    }
    strcat(stWtgxdj.kzbz, "00000");
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s],kzbz[%s]", 
    sProtocolNo, sTaxOrgCode, sPayAcct, stWtgxdj.kzbz),fpub_GetCompname(lXmlhandle))    

    /*验证标志*/
    stWtgxdj.yzbz[0]='0';

    /*客户号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/khh",sBuf);
    pstrcopy(stWtgxdj.khh,sBuf,sizeof(stWtgxdj.khh)); 

    /*付款开户行机构号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 

    /*备注--开户行机构号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    
    /*付款开户行行号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode",sBuf);
    pstrcopy(stWtgxdj.payopbkcode,sBuf,sizeof(stWtgxdj.payopbkcode));
    if(strlen(stWtgxdj.payopbkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款开户行行号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款开户行行号不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }

    /*备注*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bz",sBuf);
    pstrcopy(stWtgxdj.bz,sBuf,sizeof(stWtgxdj.bz));

    /*账号2*//*修改by liurj add 20180713*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct2",sBuf);
    pstrcopy(stWtgxdj.payacct2,sBuf,sizeof(stWtgxdj.payacct2));
    /*pstrcopy(stWtgxdj.payacct2, stWtgxdj.payacct, sizeof(stWtgxdj.payacct2));*/

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdj", SD_TIPS_WTGXDJ, NUMELE(SD_TIPS_WTGXDJ), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(lXmlhandle, 24327, "新增三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("新增三方协议失败"),
        fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "签约三方协议成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("签约三方协议成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdSFXY_DRC
组件名称: 修改三方协议
组件功能: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：
   前提条件：建立、删除前、完成对账号上送主机的校验        1 建立

          查询协议书号在数据库中是否已存在、
            存在->验证协议书对应的征收机关、纳税人账号、支付行行号记录是否相符，不符的交易失败，符合的更新。 
            不存在->交易失败

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记    tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: sunpj
发布日期: 2017年3月15日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sProtocolNo[60+1];/* 协议书号 */
    char sProtocolno_tmp[60+1];/* 协议书号 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sPayAcct[32+1];/* 付款账号 */
    char sPayBkCode[12+1];/* 付款行行号 */
    char sPayOpBkCode[12+1];/* 付款行行号 */
    SDB_TIPS_WTGXDJ stWtgxdj;
    SDB_TIPS_WTGXDJ stWtgxdj1;
    int iCount;
    
    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    int iret;
    
    char sSql1[1024];  /*DCI 执行sql语句*/
    char sErrmsg[256]; /*DCI 执行sql语句返回错误信息*/ 
    int iRet=0;
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
           
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "付款行行号")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("签约三方协议开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s],付款行行号[%s]", 
    sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))
    
    memset(&stWtgxdj1, 0x00, sizeof(stWtgxdj1));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select yzbz from tips_wtgxdj where protocolno='%s' ",sProtocolNo);         
    iRet = DBSelectToVar(sErrmsg, &stWtgxdj1.yzbz, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
        fpub_GetCompname(lXmlhandle))   
    }
    if( iRet == 0)
    {
        fpub_SetMsg(lXmlhandle, 24325, "三方协议不存在,请用签约交易");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议不存在,请用签约交易"),
        fpub_GetCompname(lXmlhandle))        
    }

    LOG(LM_STD,Fmtmsg("验证标志[%s]...",stWtgxdj1.yzbz),fpub_GetCompname(lXmlhandle))
    if( !(strcmp(stWtgxdj1.yzbz,"1")) )
    {
        fpub_SetMsg(lXmlhandle, 24327, "该三方协议已验证，不能修改");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("该三方协议已验证，不能修改"),
        fpub_GetCompname(lXmlhandle))
    }
    
    /*开始修改三方协议*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    iret = 0;
    
    memset(&stWtgxdj,0,sizeof(stWtgxdj));
      

    /*委托关系状态*/ 
    stWtgxdj.wtgxzt[0]='0';
    
    /*协议书号*/
    pstrcopy(stWtgxdj.protocolno, sProtocolNo, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "协议书号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("协议书号不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*征收机关代码*/
    pstrcopy(stWtgxdj.taxorgcode, sTaxOrgCode, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "征收机关代码不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_taxcodeinfo WHERE taxorgcode='%s'",sTaxOrgCode);         
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24321, "查询征收机关代码失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询征收机关代码失败"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "征收机关代码不存在");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("征收机关代码不存在"),
            fpub_GetCompname(lXmlhandle))        
    }
    
   /*纳税人编码*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人编码不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人编码不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*纳税人名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
    if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "纳税人名称不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("纳税人名称不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*缴款单位名称*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
    if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "缴款单位名称不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("缴款单位名称不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* 付款行行号*/
    pstrcopy(stWtgxdj.paybkcode, sPayBkCode, sizeof(stWtgxdj.paybkcode));
    if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款行行号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款行行号不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /* 付款帐户*/ 
    pstrcopy(stWtgxdj.payacct, sPayAcct, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款帐户不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款帐户不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*客户代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));
    
    /*关系修改日期*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/xgrq",sBuf)
    pstrcopy(stWtgxdj.xgrq, sBuf, sizeof(stWtgxdj.xgrq));
    
    /*修改流水号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.xglsh, sBuf, sizeof(stWtgxdj.xglsh));
    
    /*修改机构代号*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.xgjgdh, sBuf, sizeof(stWtgxdj.xgjgdh));
    
    /*修改地区代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.xgdqdh, sBuf, sizeof(stWtgxdj.xgdqdh));
    
    /*修改交易柜员*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.xgjygy, sBuf, sizeof(stWtgxdj.xgjygy));
    
    /*修改终端代号*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.xgzddh, sBuf, sizeof(stWtgxdj.xgzddh));
    
    /*扩展标志*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* 帐户类型 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[0]='0'; 
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* 钞汇标志 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[1]='0';
    }
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* 卡折标志 add 20140901 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }
    else
    {
        stWtgxdj.kzbz[2]='C'; 
    }
    strcat(stWtgxdj.kzbz, "00000");   
    
    /*付款开户行行号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode",sBuf);
    pstrcopy(stWtgxdj.payopbkcode, sBuf, sizeof(stWtgxdj.payopbkcode));
    if(strlen(stWtgxdj.payopbkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "付款开户行行号不能为空");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("付款开户行行号不能为空"),
        fpub_GetCompname(lXmlhandle))        
    }
    
    /*付款开户行机构号*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 
    
    /*备注--开户行机构号 */
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    
    /*备注*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bz",sBuf);
    pstrcopy(stWtgxdj.bz,sBuf,sizeof(stWtgxdj.bz));

    /*账号2*//*修改by liurj add 20180713*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct2",sBuf);
    pstrcopy(stWtgxdj.payacct2,sBuf,sizeof(stWtgxdj.payacct2));
    /*pstrcopy(stWtgxdj.payacct2, stWtgxdj.payacct, sizeof(stWtgxdj.payacct2));*/
    
    /*更新三方协议*/
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj  \
                set payacct='%s'    \
                    ,payopbkcode='%s'\
                    ,taxpayname='%s' \
                    ,handorgname='%s'\
                    ,byzd='%s'       \
                    ,khh='%s'        \
                    ,xgrq='%s'       \
                    ,xglsh='%s'      \
                    ,xgdqdh='%s'     \
                    ,xgjgdh='%s'     \
                    ,xgjygy='%s'     \
                    ,xgzddh='%s'     \
                    ,opbankno='%s'   \
                    ,bz='%s'         \
                    ,payacct2='%s'   \
                where protocolno='%s'" \
              ,stWtgxdj.payacct      \
              ,stWtgxdj.payopbkcode  \
              ,stWtgxdj.taxpayname   \
              ,stWtgxdj.handorgname  \
              ,stWtgxdj.byzd         \
              ,stWtgxdj.khh          \
              ,stWtgxdj.xgrq         \
              ,stWtgxdj.xglsh        \
              ,stWtgxdj.xgdqdh       \
              ,stWtgxdj.xgjgdh       \
              ,stWtgxdj.xgjygy       \
              ,stWtgxdj.xgzddh       \
              ,stWtgxdj.opbankno     \
              ,stWtgxdj.bz           \
              ,stWtgxdj.payacct2     \
              ,sProtocolNo);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))                   
    iRet = DCIExecuteDirect(sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24327, "修改三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("修改三方协议失败"),
        fpub_GetCompname(lXmlhandle))
    }
    iRet =DCICommit();
    
    fpub_SetMsg(lXmlhandle, 0, "修改三方协议成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("修改三方协议成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_DelSFXY_DRC
组件名称: 撤销三方协议
组件功能: 
  撤销三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：
   前提条件：建立、删除前、完成对账号上送主机的校验
        
        删除
          根据协议书号、查询三方协议内容
             校验三方协议字段：征收机关代号、纳税人账号、支付行行号是否和前台传送的一致
             更新协议书的委托关系状态-->1,返回成功。

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记    tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: sunpj
发布日期: 2017年03月25日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_DelSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sProtocolNo[60+1];/* 协议书号 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sPayAcct[32+1];/* 付款账号 */
    SDB_TIPS_WTGXDJ stWtgxdj;
    SDB_TIPS_WTGXDJ stWtgxdj1;

    char sBuf[256];
    
    char sSql1[512];  /*DCI 执行sql语句*/
    char sErrmsg[256]; /*DCI 执行sql语句返回错误信息*/ 
    int iRet=0;
    
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);

    LOG(LM_STD,Fmtmsg("撤销三方协议开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],征收机关代码[%s],付款账号[%s]", 
    sProtocolNo, sTaxOrgCode, sPayAcct),fpub_GetCompname(lXmlhandle))
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    memset( &stWtgxdj, 0x00, sizeof( &stWtgxdj ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT PROTOCOLNO, TAXORGCODE, PAYBKCODE, PAYACCT, BANKPROTOCOLNO, TAXPAYCODE, \
            PAYOPBKCODE, TAXPAYNAME, HANDORGNAME, KHH, WTGXZT, GXDJRQ, DJLSH, DJDQDH, DJJGDH, DJJYGY, DJZDDH, XGRQ, \
            XGLSH, XGDQDH, XGJGDH, XGJYGY, XGZDDH, KZBZ, YZBZ, BYZD, OPBANKNO, BZ, PAYACCT2, YZXGRQ \
            FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))  
         
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stWtgxdj.protocolno,&stWtgxdj.taxorgcode,\
    &stWtgxdj.paybkcode,&stWtgxdj.payacct,&stWtgxdj.bankprotocolno,&stWtgxdj.taxpaycode,&stWtgxdj.payopbkcode,\
    &stWtgxdj.taxpayname,&stWtgxdj.handorgname,&stWtgxdj.khh,&stWtgxdj.wtgxzt,&stWtgxdj.gxdjrq,&stWtgxdj.djlsh,\
    &stWtgxdj.djdqdh,&stWtgxdj.djjgdh,&stWtgxdj.djjygy,&stWtgxdj.djzddh,&stWtgxdj.xgrq,&stWtgxdj.xglsh,\
    &stWtgxdj.xgdqdh,&stWtgxdj.xgjgdh,&stWtgxdj.xgjygy,&stWtgxdj.xgzddh,&stWtgxdj.kzbz,&stWtgxdj.yzbz,\
    &stWtgxdj.byzd,&stWtgxdj.opbankno,&stWtgxdj.bz,&stWtgxdj.payacct2,&stWtgxdj.yzxgrq);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        fpub_SetMsg(lXmlhandle, 24316, "查询委托关系登记信息失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记信息失败"),
        fpub_GetCompname(lXmlhandle))
        
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24317, "委托关系未建立");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("委托关系未建立"),
        fpub_GetCompname(lXmlhandle))    
    }
    
    /*修改流水号 */
    COMP_SOFTGETXML("/pub/zhqzlsh",stWtgxdj.xglsh);
    
    /*修改日期 */
    COMP_SOFTGETXML("/sys/sysdate",stWtgxdj.xgrq);
    
    /*修改机构代号 */
    COMP_SOFTGETXML("/pub/jgdh",stWtgxdj.xgjgdh);
    
    /*修改地区代号 */
    COMP_SOFTGETXML("/pub/dqdh",stWtgxdj.xgdqdh);
    
    /*修改交易柜员 */
    COMP_SOFTGETXML("/pub/jygy",stWtgxdj.xgjygy);
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdjlsls", SD_TIPS_WTGXDJLSLS, NUMELE(SD_TIPS_WTGXDJLSLS), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, 24318, "插入历史委托记录失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入历史委托记录失败"),
        fpub_GetCompname(lXmlhandle))
    }
    
    /* ADD DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "delete FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
    iRet = DCIExecuteDirect(sSql1);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 24319, "删除三方协议失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("删除三方协议失败"),
        fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "删除三方协议成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("删除三方协议成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitPZSJ_DB_DRC
组件名称: 登记凭证数据信息(单笔)
组件功能: 
  登记凭证数据信息(单笔)
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

操作步骤：


组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
当日流水表    tips_drls
税种明细表    tips_taxtypemx
税目明细表    tips_taxsubjectlist

项 目 组: TIPS专用前置产品组
程 序 员: sunpj
发布日期: 2017年3月29日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPZSJ_DB_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    SDB_TIPS_DRLS stDrls;
    SDB_TIPS_TAXTYPEMX stTaxtypemx;
    SDB_TIPS_TAXSUBJECTLIST stTaxsubjectlist;
    char sZwrq[8+1];/* 账务日期 */
    int iZhqzlsh;
    
    char sBuf[256];
    char sRoot[256];
    int  iCount=0,i,j;
    char sXmlNodePath[200];
    char sTaxInfoPath[200];
    char sPayment3102[10240];
    int iret;
    FILE *fp;
    
    char sSql1[512]; 
    char sErrmsg[256];
    int iRet=0;
    
    char sProtocolno[61];
    char sSpxx[41];
    
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "账务日期")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "综合前置流水号")
    iZhqzlsh = atoi(sBuf);

    LOG(LM_STD,Fmtmsg("登记凭证数据信息(单笔)开始处理..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("账务日期[%s],综合前置流水号[%d]", 
        sZwrq, iZhqzlsh),fpub_GetCompname(lXmlhandle))
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    memset( &stDrls, 0x00, sizeof( &stDrls ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_drls where zwrq='%s' and zhqzlsh=%d",sZwrq,iZhqzlsh); 
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))    
       
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,
                               &stDrls.zwrq         ,
                               &stDrls.zhqzlsh      ,
                               &stDrls.jyqd         ,
                               &stDrls.workdate     ,
                               &stDrls.entrustdate  ,
                               &stDrls.taxorgcode   ,
                               &stDrls.trano        ,
                               &stDrls.msgno        ,
                               &stDrls.entrustdate2 ,
                               &stDrls.trano2       ,
                               &stDrls.zhqzlsh2     ,
                               &stDrls.chkdate      ,
                               &stDrls.chkacctord   ,
                               &stDrls.handletype   ,
                               &stDrls.trecode      ,
                               &stDrls.payeebankno  ,
                               &stDrls.payeeorgcode ,
                               &stDrls.payeeacct    ,
                               &stDrls.payeename    ,
                               &stDrls.paybkcode    ,
                               &stDrls.payopbkcode  ,
                               &stDrls.protocolno   ,
                               &stDrls.payacct      ,
                               &stDrls.handorgname  ,
                               &stDrls.dfzh         ,
                               &stDrls.jyje         ,
                               &stDrls.taxvouno     ,
                               &stDrls.dqdh         ,
                               &stDrls.jgdh         ,
                               &stDrls.jygy         ,
                               &stDrls.zddh         ,
                               &stDrls.jyrq         ,
                               &stDrls.jysj         ,
                               &stDrls.zjrq         ,
                               &stDrls.zjsj         ,
                               &stDrls.zjlsh        ,
                               &stDrls.zjxym        ,
                               &stDrls.zjxyxx       ,
                               &stDrls.sxf          ,
                               &stDrls.zhye         ,
                               &stDrls.xym          ,
                               &stDrls.xyxx         ,
                               &stDrls.jyzt         ,
                               &stDrls.dzbz         ,
                               &stDrls.qsbz         ,
                               &stDrls.kzbz         ,
                               &stDrls.taxpaycode   ,
                               &stDrls.taxpayname   ,
                               &stDrls.spxx         ,
                               &stDrls.byzd          );
        
    LOG(LM_STD,Fmtmsg("ZWRQ         [%s]",stDrls.zwrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH      [%d]",stDrls.zhqzlsh     ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYQD         [%s]",stDrls.jyqd        ),"INFO") 
    LOG(LM_STD,Fmtmsg("WORKDATE     [%s]",stDrls.workdate    ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE  [%s]",stDrls.entrustdate ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXORGCODE   [%s]",stDrls.taxorgcode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO        [%s]",stDrls.trano       ),"INFO") 
    LOG(LM_STD,Fmtmsg("MSGNO        [%s]",stDrls.msgno       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE2 [%s]",stDrls.entrustdate2),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO2       [%s]",stDrls.trano2      ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH2     [%d]",stDrls.zhqzlsh2    ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKDATE      [%s]",stDrls.chkdate     ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKACCTORD   [%s]",stDrls.chkacctord  ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDLETYPE   [%s]",stDrls.handletype  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRECODE      [%s]",stDrls.trecode     ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEBANKNO  [%s]",stDrls.payeebankno ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEORGCODE [%s]",stDrls.payeeorgcode),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEACCT    [%s]",stDrls.payeeacct   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEENAME    [%s]",stDrls.payeename   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYBKCODE    [%s]",stDrls.paybkcode   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYOPBKCODE  [%s]",stDrls.payopbkcode ),"INFO") 
    LOG(LM_STD,Fmtmsg("PROTOCOLNO   [%s]",stDrls.protocolno  ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYACCT      [%s]",stDrls.payacct     ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDORGNAME  [%s]",stDrls.handorgname ),"INFO") 
    LOG(LM_STD,Fmtmsg("DFZH         [%s]",stDrls.dfzh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYJE         [%f]",stDrls.jyje        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXVOUNO     [%s]",stDrls.taxvouno    ),"INFO") 
    LOG(LM_STD,Fmtmsg("DQDH         [%s]",stDrls.dqdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JGDH         [%s]",stDrls.jgdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYGY         [%s]",stDrls.jygy        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZDDH         [%s]",stDrls.zddh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYRQ         [%s]",stDrls.jyrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYSJ         [%s]",stDrls.jysj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJRQ         [%s]",stDrls.zjrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJSJ         [%s]",stDrls.zjsj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJLSH        [%s]",stDrls.zjlsh       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYM        [%s]",stDrls.zjxym       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYXX       [%s]",stDrls.zjxyxx      ),"INFO") 
    LOG(LM_STD,Fmtmsg("SXF          [%f]",stDrls.sxf         ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHYE         [%f]",stDrls.zhye        ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYM          [%s]",stDrls.xym         ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYXX         [%s]",stDrls.xyxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYZT         [%s]",stDrls.jyzt        ),"INFO") 
    LOG(LM_STD,Fmtmsg("DZBZ         [%s]",stDrls.dzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("QSBZ         [%s]",stDrls.qsbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("KZBZ         [%s]",stDrls.kzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYCODE   [%s]",stDrls.taxpaycode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYNAME   [%s]",stDrls.taxpayname  ),"INFO") 
    LOG(LM_STD,Fmtmsg("SPXX         [%s]",stDrls.spxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("BYZD         [%s]",stDrls.byzd        ),"INFO") 
    
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24201, "查询当日流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("查询当日流水表失败"), fpub_GetCompname(lXmlhandle))    
         return COMPRET_FAIL ;        
    }
    
    /* 税票信息 */
    memset(sPayment3102, 0x00, sizeof(sPayment3102));
    memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
    if (strcmp(stDrls.msgno, "3001") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment3001");   
    
        if ( (iret=xml_ExportXMLString(lXmlhandle,sPayment3102,sizeof(sPayment3102),sXmlNodePath,1 )) == -1 )
        {
             fpub_SetMsg(lXmlhandle, 24211, "获取税票信息失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("获取税票信息失败[%s]", sXmlNodePath), fpub_GetCompname(lXmlhandle))    
             return COMPRET_FAIL ;        
        }
        /* 把税票信息存放到文件中去 */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));/* 存放的文件名 */
        snprintf(sXmlNodePath, sizeof(sXmlNodePath), "spxx_%s_%d",sZwrq, iZhqzlsh);
        trim(sXmlNodePath);
        snprintf(sTaxInfoPath, sizeof(sTaxInfoPath), "%s/file/tips/spxx/%s", getenv("HOME"), sXmlNodePath);
        fp = fopen(sTaxInfoPath, "w+");
        if ( fp==NULL )
        {
             fpub_SetMsg(lXmlhandle, 24212, "打开税票信息文件失败");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("打开税票信息文件失败"), fpub_GetCompname(lXmlhandle))    
             return COMPRET_FAIL ;        
        }
        fprintf(fp, "%s\n", sPayment3102); 
        if (NULL != fp)
        {
            fclose(fp);
            fp = NULL;
        }
        
        pstrcopy(stDrls.spxx, sXmlNodePath, sizeof(stDrls.spxx));        
        COMP_SOFTSETXML("/tips/spxx", sXmlNodePath)

        /*明细条数*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/MSG/Payment3001/TaxTypeNum",sBuf)
        iCount=atoi(sBuf);
       
        /*循环取税种明细信息*/
        for(i=1; i<=iCount; i++)
        {
            
            memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
            pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
			sprintf(stTaxtypemx.jylsh, "%d", stDrls.zhqzlsh);
            pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));
            LOG(LM_STD,Fmtmsg("jyrq[%s]",stTaxtypemx.jyrq),fpub_GetCompname(lXmlhandle))
            LOG(LM_STD,Fmtmsg("jylsh[%s]",stTaxtypemx.jylsh),fpub_GetCompname(lXmlhandle))

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment3001/TaxTypeList3001|%d/ProjectId",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeName",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));         
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxStartDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxEndDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeAmt",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            stTaxtypemx.taxtypeamt = atof(sBuf);
            
            LOG(LM_STD,Fmtmsg("i[%d],jyrq[%s],jylsh[%s],projectid[%s]",i,stTaxtypemx.jyrq,stTaxtypemx.jylsh,stTaxtypemx.projectid),"INFO") 
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                
                fpub_SetMsg(lXmlhandle, 24327, "插入税种明细表失败");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入税种明细表失败"),fpub_GetCompname(lXmlhandle))
            }
        }
        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
        snprintf( sSql1, sizeof(sSql1), "update tips_drls set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);         
        LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
        iRet = DCIExecuteDirect(sSql1);     
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
            
            fpub_SetMsg(lXmlhandle, 24201, "更新当日流水表失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))    
            return COMPRET_FAIL ;        
        }
        
    }
    else if (strcmp(stDrls.msgno, "1008") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment1008");  
        
        /*明细条数*/
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/tips/MSG/Payment1008/TaxTypeNum",sBuf)
        iCount=atoi(sBuf);
       
        /*循环取税种明细信息*/
        for(i=1; i<=iCount; i++)
        {
            LOG(LM_STD,Fmtmsg("插入税种明细表开始..."),fpub_GetCompname(lXmlhandle))
            memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
            pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
			sprintf(stTaxtypemx.jylsh, "%d", stDrls.zhqzlsh);
            pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/ProjectId",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/BudgetSubjectCode",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.budgetsubjectcode, sBuf, sizeof(stTaxtypemx.budgetsubjectcode));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/LimitDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.limitdate, sBuf, sizeof(stTaxtypemx.limitdate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeName",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/BudgetLevelCode",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.budgetlevelcode, sBuf, sizeof(stTaxtypemx.budgetlevelcode));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/BudgetLevelName",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.budgetlevelname, sBuf, sizeof(stTaxtypemx.budgetlevelname));

            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxStartDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxEndDate",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/ViceSign",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.vicesign, sBuf, sizeof(stTaxtypemx.vicesign));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxType",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.taxtype, sBuf, sizeof(stTaxtypemx.taxtype));
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeAmt",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            stTaxtypemx.taxtypeamt = atof(sBuf);
            
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/DetailNum",i);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            pstrcopy(stTaxtypemx.detailnum, sBuf, sizeof(stTaxtypemx.detailnum));
            
            memset( sSql1, 0x00, sizeof( sSql1 ) );
            iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                
                fpub_SetMsg(lXmlhandle, 24327, "插入税种明细表失败");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入税种明细表失败"),
                fpub_GetCompname(lXmlhandle))
            }
            
            LOG(LM_STD,Fmtmsg("插入税种明细表结束..."),fpub_GetCompname(lXmlhandle))
            
            for (j = 0; j < atol(stTaxtypemx.detailnum); j++)
            {
                LOG(LM_STD,Fmtmsg("插入税目明细表开始..."),fpub_GetCompname(lXmlhandle))
                memset(&stTaxsubjectlist, 0x00, sizeof(stTaxsubjectlist));
                pstrcopy(stTaxsubjectlist.jyrq, stDrls.zwrq, sizeof(stTaxsubjectlist.jyrq));
				sprintf(stTaxsubjectlist.jylsh, "%d", stDrls.zhqzlsh);
                pstrcopy(stTaxsubjectlist.projectid, stTaxtypemx.projectid, sizeof(stTaxsubjectlist.projectid));

                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/DetailNo",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.detailno, sBuf, sizeof(stTaxsubjectlist.detailno));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxSubjectCode",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.taxsubjectcode, sBuf, sizeof(stTaxsubjectlist.taxsubjectcode));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxSubjectName",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.taxsubjectname, sBuf, sizeof(stTaxsubjectlist.taxsubjectname));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxNumber",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                pstrcopy(stTaxsubjectlist.taxnumber, sBuf, sizeof(stTaxsubjectlist.taxnumber));
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.taxamt = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/TaxRate",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.taxrate = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/ExpTaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.exptaxamt = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/DiscountTaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.discounttaxamt = atof(sBuf);
                
                memset(sRoot, 0x00, sizeof(sRoot));
                memset(sBuf, 0x00, sizeof(sBuf));
                snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxSubjectList1008|%d/FactTaxAmt",i,j);
                COMP_SOFTGETXML(sRoot,sBuf)
                trim(sBuf);
                stTaxsubjectlist.facttaxamt = atof(sBuf);
                
                memset( sSql1, 0x00, sizeof( sSql1 ) );
                iRet = DBInsert("tips_taxsubjectlist", SD_TIPS_TAXSUBJECTLIST, NUMELE(SD_TIPS_TAXSUBJECTLIST), &stTaxsubjectlist, sErrmsg);
                if( iRet < 0 )
                {
                    LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
                    
                    fpub_SetMsg(lXmlhandle, 24327, "插入税目明细表失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("插入税目明细表失败"),
                    fpub_GetCompname(lXmlhandle))
                }
                
                LOG(LM_STD,Fmtmsg("插入税目明细表结束..."),fpub_GetCompname(lXmlhandle))
            }
        }
        
    }
    else
    {
        fpub_SetMsg(lXmlhandle, 24211, Fmtmsg("不支持此报文编号[%s]的实时凭证", stDrls.msgno));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("不支持此报文编号[%s]的实时凭证", stDrls.msgno), fpub_GetCompname(lXmlhandle))    
        return COMPRET_FAIL ;        
    }            
    
    /* 插入单笔凭证数据 */
    LOG(LM_STD,Fmtmsg("插入凭证数据开始"),fpub_GetCompname(lXmlhandle))       
    iret = prv_tips_InitPZSJ_db(lXmlhandle, stDrls);
    if ( iret < 0 )
    {
         fpub_SetMsg(lXmlhandle, 24213, "新增凭证信息失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("新增凭证信息失败[%d]", iret), fpub_GetCompname(lXmlhandle))    
         return COMPRET_FAIL ;        
    }
    LOG(LM_STD,Fmtmsg("插入凭证数据结束"),fpub_GetCompname(lXmlhandle))  
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_drls \
        set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                
    iRet = DCIExecuteDirect(sSql1);     
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24201, "更新当日流水表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))    
         return COMPRET_FAIL ;        
    }
    
    iRet =DCICommit();
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("更新当日流水表失败"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("更新当日流水表失败"), fpub_GetCompname(lXmlhandle))    
    }
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("登记凭证数据信息(单笔)处理结束"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;       
}


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_YzcxSFXY_DRC
组件名称: 验证与撤销三方协议
组件功能: 
  验证与撤销三方协议
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
委托关系登记    tips_wtgxdj

项 目 组: TIPS专用前置产品组
程 序 员: sunpj
发布日期: 2017年04月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_YzcxSFXY_DRC(HXMLTREE lXmlhandle)
{
    int iParas;
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sPayBkCode[12+1];/* 付款行行号 */
    char sPayAcct[32+1];/* 付款账号 */
	char sPayAcct2[32+1];/* 协议账号 */
    char sProtocolNo[60+1];/* 协议书号 */
    char sProtocolNo_t[60+1];/* 协议书号 */
    char sHandOrgName_t[200+1];/* 缴款单位名称 */
    char sTaxPayCode_t[20+1];/* 纳税人编码 */
    char sWtgxzt[1+1];/* 委托关系状态 */
    char sBankProtocolNo[30+1];/* 银行内部协议号 */

    char sBuf[256];
    char sHandOrgName[200+1];/* 缴款单位名称 */
    char sTaxPayCode[20+1];/* 纳税人编码 */
    char sVCSign[1+1];/* 验证标志 */
	char sYzxgrq[8+1];/* 验证修改日期 */
	char sPayOpBkCode[12+1];/* 副清算行 */
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
    char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
    int iRet=0;
    
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(7);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1, sBuf, "征收机关代码")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(2, sBuf, "付款行行号")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "付款账号")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(4, sBuf, "协议书号")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
    COMP_GETPARSEPARAS(5, sBuf, "缴款单位名称")
    pstrcopy(sHandOrgName, sBuf, sizeof(sHandOrgName));
    trim(sHandOrgName);
    LOG(LM_STD,Fmtmsg("缴款单位名称_t[%s]", sHandOrgName), fpub_GetCompname(lXmlhandle))    
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    COMP_GETPARSEPARAS(6, sBuf, "纳税人编码")
    pstrcopy(sTaxPayCode, sBuf, sizeof(sTaxPayCode));
    trim(sTaxPayCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sVCSign, 0x00, sizeof(sVCSign));
    COMP_GETPARSEPARAS(7, sBuf, "验证标志")
    pstrcopy(sVCSign, sBuf, sizeof(sVCSign));
    trim(sVCSign);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sYzxgrq, 0x00, sizeof(sYzxgrq));
    COMP_SOFTGETXML("/tips/zwrq", sBuf);
    trim(sBuf);
    pstrcopy(sYzxgrq, sBuf, sizeof(sYzxgrq));
       
    LOG(LM_STD,Fmtmsg("验证撤销三方协议开始处理... 征收机关代码[%s],付款行行号[%s],付款账号[%s]", 
        sTaxOrgCode, sPayBkCode, sPayAcct), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("协议书号[%s],缴款单位名称[%s],纳税人编码[%s],验证标志[%s]", 
        sProtocolNo, sHandOrgName, sTaxPayCode, sVCSign), fpub_GetCompname(lXmlhandle))        

    /* 查询客户委托关系 */
    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sProtocolNo_t, 0x00, sizeof(sProtocolNo_t));
    memset(sHandOrgName_t, 0x00, sizeof(sHandOrgName_t));
    memset(sTaxPayCode_t, 0x00, sizeof(sTaxPayCode_t));
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT wtgxzt, protocolno, handorgname, taxpaycode, bankprotocolno, payacct2, payopbkcode FROM tips_wtgxdj\
        WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);         
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    iRet = DBSelectToMultiVar(sErrmsg, sSql1, &sWtgxzt, &sProtocolNo_t, &sHandOrgName_t, &sTaxPayCode_t, &sBankProtocolNo, &sPayAcct2, &sPayOpBkCode);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("查询委托关系登记表失败"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询委托关系登记表失败"), 
            fpub_GetCompname(lXmlhandle));    
        
    }
    if ( iRet == 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("三方协议未签约或征收机关代号、付款账号不符."));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议未签约或征收机关代号、付款账号不符."), 
            fpub_GetCompname(lXmlhandle));     
    }
    
    trim(sWtgxzt);
	trim(sProtocolNo_t);
    trim(sHandOrgName_t);
    trim(sTaxPayCode_t);
    LOG(LM_STD,Fmtmsg("协议书号_t[%s],缴款单位名称_t[%s],纳税人编码_t[%s]", 
        sProtocolNo_t, sHandOrgName_t, sTaxPayCode_t), fpub_GetCompname(lXmlhandle))    

    LOG(LM_STD,Fmtmsg("缴款单位名称_t[%s]", sHandOrgName_t), fpub_GetCompname(lXmlhandle))    

    /* 判断委托关系状态 */
    if ( sWtgxzt[0]=='1' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24348, Fmtmsg("三方协议被撤销"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议被撤销"), 
            fpub_GetCompname(lXmlhandle));         
    }        
    if ( sWtgxzt[0]=='2' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24349, Fmtmsg("三方协议被锁定"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议被锁定"), 
            fpub_GetCompname(lXmlhandle));         
    }
    if ( sWtgxzt[0]!='0' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24350, Fmtmsg("三方协议状态异常"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("三方协议状态异常"), 
            fpub_GetCompname(lXmlhandle));         
    }
    /* 判断协议书号是否一致 */
    if ( strcmp(sProtocolNo, sProtocolNo_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("协议书号不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("协议书号不一致"), 
            fpub_GetCompname(lXmlhandle));         
    }    
    /* 判断缴款单位名称是否一致 */
    if ( strcmp(sHandOrgName, sHandOrgName_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);    
        fpub_SetMsg(lXmlhandle, 24352, Fmtmsg("缴款单位名称不一致"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("缴款单位名称不一致"), 
            fpub_GetCompname(lXmlhandle));
    }
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    
    if (sVCSign[0]=='0')/* 验证 */
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='1',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
                         sYzxgrq, sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);        
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
        iRet = DCIExecuteDirect(sSql1);     
        if ( iRet < 0 || iRet == 0)/* add 20141215 iRet=0也认为更新不成功 */
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
            fpub_SetMsg(lXmlhandle, 24354, "更新委托关系登记表失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新委托关系登记表失败"),fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("三方协议验证通过"), fpub_GetCompname(lXmlhandle))
		COMP_SOFTSETXML("/tips/opeflag","1");
    }
    else
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='2',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
                       sYzxgrq, sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);         
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
        iRet = DCIExecuteDirect(sSql1);                 
        if ( iRet < 0 || iRet == 0)
        {
            LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
            fpub_SetMsg(lXmlhandle, 24354, "更新委托关系登记表失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("更新委托关系登记表失败"),fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("三方协议撤销通过"), fpub_GetCompname(lXmlhandle))
        COMP_SOFTSETXML("/tips/opeflag","3");
    }

	COMP_SOFTSETXML("/tips/inprotocol", sBankProtocolNo);
	COMP_SOFTSETXML("/tips/PayAcct2", sPayAcct2);
	COMP_SOFTSETXML("/tips/PayOpBkCode", sPayOpBkCode);
    
    fpub_SetMsg(lXmlhandle, 0, "三方协议验证与撤销处理成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("三方协议验证与撤销处理成功"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}
