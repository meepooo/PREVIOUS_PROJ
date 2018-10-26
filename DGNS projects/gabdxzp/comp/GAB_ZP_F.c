/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:恒生电信诈骗前置系统
版    本:V2.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE\INFORMIX\DB2
文件名称:GAB_ZP_F.c
文件描述:恒生电信诈骗前置系统 管理类模块业务表
项 目 组:
程 序 员:
发布日期:2016-01-18
修    订:
修改日期:
*********************************************************************/
/*  
修改记录
修改日期:
修改内容:
修改人:
*/
#include "gabdxzp_head.h"
#include "gabdxzp_alltables.h"
#include <iconv.h>
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_XDXX_Req(HXMLTREE lXmlhandle, GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
 函数功能:  获取公安部电信诈骗下达信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_XDXX_Req(HXMLTREE lXmlhandle, GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    char sOldDateTime[14+1];
    char sNewDateTime[14+1];
    char sSql[256];
    int  iDdMins=0;
    GAB_DXZP_DUAL st_gab_dxzp_dual;

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_APPLICATIONID,pst_gab_dxzp_xdxx->ywsqbh,"业务申请编号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYBM,pst_gab_dxzp_xdxx->jybm,"交易类型编码");
    
    /*消息流转模式*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_XXLZMS,pst_gab_dxzp_xdxx->xxlzms,"消息流转模式");
    pst_gab_dxzp_xdxx->xxlzms[1]=pst_gab_dxzp_xdxx->xxlzms[0];
    pst_gab_dxzp_xdxx->xxlzms[0]='0';
    /*发起机构代码*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_MESSAGEFROM,pst_gab_dxzp_xdxx->fsjgbm,"发起机构代码");
    if (pst_gab_dxzp_xdxx->fsjgbm[0] == '\0')
    {
        strcpy(pst_gab_dxzp_xdxx->fsjgbm, "mps");
    }
    COMP_SOFTSETXML("/gabdxzp/FSJGBM", pst_gab_dxzp_xdxx->fsjgbm)
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CSBWLSH,pst_gab_dxzp_xdxx->csbwlsh,"传输报文流水号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_GAAPPLICATIONID,pst_gab_dxzp_xdxx->gaywsqbh,"公安业务申请编号");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQJGDM,pst_gab_dxzp_xdxx->sqjgdm,"申请机构编码");
    /*目标机构代码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->mbjgdm);
     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXZTLB,pst_gab_dxzp_xdxx->cxztlb,"查控主体类别");
    
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWLX,pst_gab_dxzp_xdxx->ywlx,"业务类型");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ywlx); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JJCD,pst_gab_dxzp_xdxx->jjcd,"紧急程度");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_AJBH,pst_gab_dxzp_xdxx->ajbh,"案件编号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_AJLX,pst_gab_dxzp_xdxx->ajlx,"案件类型");

    /*案件事由*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ajsy);
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_AJSY,pst_gab_dxzp_xdxx->ajsy,"案件事由");
    if('\0' == pst_gab_dxzp_xdxx->ajsy[0])
    	{
    		GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ajsy);
    	}
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_AJSM,pst_gab_dxzp_xdxx->ajsm,"案件说明");
 
    /*发送请求给目标机构时的系统日期时间*/
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQSJ, sBuf,"申请时间");
    pstrcopy(pst_gab_dxzp_xdxx->sqrq,sBuf,sizeof(pst_gab_dxzp_xdxx->sqrq));
    
    /*发送请求给目标机构时的系统日期时间*/
    pstrcopy(pst_gab_dxzp_xdxx->sqsj,sBuf+8,sizeof(pst_gab_dxzp_xdxx->sqsj));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQJGBM,pst_gab_dxzp_xdxx->sqjgbm,"申请机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQJGMC,pst_gab_dxzp_xdxx->sqjgmc,"申请机构名称");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRXM,pst_gab_dxzp_xdxx->jbrxm,"经办人姓名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRZJLX,pst_gab_dxzp_xdxx->jbrzjlx,"经办人证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRZJHM,pst_gab_dxzp_xdxx->jbrzjhm,"经办人证件号"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRDH,pst_gab_dxzp_xdxx->jbrdh,"经办人电话"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXRXM,pst_gab_dxzp_xdxx->xcrxm,"协查人姓名"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_XCRZJLX,pst_gab_dxzp_xdxx->xcrzjlx,"协查人证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_XCRZJHM,pst_gab_dxzp_xdxx->xcrzjhm,"协查人证件号");
   
     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_xdxx->ywrq,"业务日期");
    
    /*业务流水号*/
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"业务流水号");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("登记下达信息表->sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "获取业务流水号");
    snprintf(pst_gab_dxzp_xdxx->ywlsh, sizeof(pst_gab_dxzp_xdxx->ywlsh), 
        "08%ld", st_gab_dxzp_dual.nextval);
    /*经办机构*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_XNJG,pst_gab_dxzp_xdxx->jbjg,"虚拟机构");
    /*经办柜员*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_XNGY,pst_gab_dxzp_xdxx->jbgy,"虚拟柜员");
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBXM,pst_gab_dxzp_xdxx->jbxm,"银行经办姓名");
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBDH,pst_gab_dxzp_xdxx->jbdh,"银行经办电话");
    
    
    
    /*任务数量*/
    pst_gab_dxzp_xdxx->rwsl=1;
    
    /*结果反馈限定时间*/
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定时间");
    if (sBuf[0] == '\0')
    {
        strcpy(sBuf,"24");
    }
    pst_gab_dxzp_xdxx->jgfkxdsj=atoi(sBuf);
    /*反馈限定日期*/
    memset(sOldDateTime, 0x00, sizeof(sOldDateTime));
    memset(sNewDateTime, 0x00, sizeof(sNewDateTime));
    snprintf(sOldDateTime, sizeof(sOldDateTime), "%s%s", 
        pst_gab_dxzp_xdxx->sqrq, pst_gab_dxzp_xdxx->sqsj);
    iRet = ffunc_gabdxzp_getMoveHours(lXmlhandle, sOldDateTime, pst_gab_dxzp_xdxx->jgfkxdsj, sNewDateTime, sizeof(sNewDateTime));
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkxdrq, sNewDateTime)
    /*反馈限定时间*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkxdsj, sNewDateTime+8)
    /*反馈兜底日期*/
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_DDMIN,sBuf,"兜底提前N分钟");
    if ( sBuf[0] == '\0')
    {
        strcpy(sBuf, "15");
    }
    iDdMins = atoi(sBuf);
    memset(sOldDateTime, 0x00, sizeof(sOldDateTime));
    GAB_DXZP_PSTRCOPY(sOldDateTime, sNewDateTime);
    memset(sNewDateTime, 0x00, sizeof(sNewDateTime));
    iRet = ffunc_gabdxzp_getMoveMins(lXmlhandle, sOldDateTime, iDdMins, sNewDateTime, sizeof(sNewDateTime));
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkddrq, sNewDateTime)
    LOG(LM_STD, Fmtmsg("登记下达信息表->sOldDateTime[%s] - iDdMins[%d] = sNewDateTime[%s]", 
        sOldDateTime, iDdMins, sNewDateTime), fpub_GetCompname(lXmlhandle));
    /*反馈兜底时间*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkddsj, sNewDateTime+8)
    /*手自处理标志*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->szclbz);
    
    /*处理日期*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->clrq);
    /*处理时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->clsj);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_xdxx->zwrq,"账务日期");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSTIME,pst_gab_dxzp_xdxx->systime,"gaps系统时间");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_ZHQZLSH,pst_gab_dxzp_xdxx->zhqzlsh,"gaps流水号");
    
    /*请求单状态 12或20-落地成功*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->qqdzt, "20");
    /*业务应答码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ywydm);
    /*业务应答信息*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ywydxx);
    /*执行结果*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->zxjg, "9");
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->respmsg);
    /*主机日期*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->zjrq);
    /*主机流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->zjlsh);
    /*轮询日期*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->lxrq);
    /*轮询批次号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->lxpch);
    /*批次序号*/
    pst_gab_dxzp_xdxx->pcxh=0;
    
    /*提交核心次数*/
    pst_gab_dxzp_xdxx->tjhxcs=0;
    /*反馈前置次数*/
    pst_gab_dxzp_xdxx->fkqzcs=0;
    /*备用11*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->by11);
    /*备用12*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->by12);
    /*备用13*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->by13);
    
    return 0;
}

/*****************************************************
 函数名称:  ffunc_gabdxzp_getXml_945100_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
 函数功能:  获取公安部电信诈骗止付报文请求信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945100_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jjzf->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_jjzf->rwxh=1;
    /*原业务申请编号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->yywsqbh);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SFBLC,pst_gab_dxzp_jjzf->sfblc,"是否补流程");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_YJBSQBH,pst_gab_dxzp_jjzf->yjbsqbh,"原举报申请编号");
    /*卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->kh);
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZHYH,pst_gab_dxzp_jjzf->zczhyh,"转出账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZHYHMC,pst_gab_dxzp_jjzf->zczhyhmc,"转出账户银行名称");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZHM,pst_gab_dxzp_jjzf->zczhm,"转出账户名");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZH,pst_gab_dxzp_jjzf->zczh,"转出账卡号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_jjzf->bz,"币种");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZCJE, pst_gab_dxzp_jjzf->zcje, "转出金额");
    memset(sBuf,0x00,sizeof(sBuf));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZCSJ,sBuf,"转出时间");
    /*转出日期*/
    strncpy(pst_gab_dxzp_jjzf->zcrq,sBuf,8);
    /*转出时间*/
    strncpy(pst_gab_dxzp_jjzf->zcsj,sBuf+8,6);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jjzf->khyh,"止付账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jjzf->khyhmc,"止付账户所属银行名称");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jjzf->zhlb,"止付账号类别");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jjzf->zhmc,"止付账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_jjzf->zh,"止付账卡号");
    /*止付到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->dqr);
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_jjzf->dqr,"止付到期日");
    
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定时间");
    pst_gab_dxzp_jjzf->jgfksj=atoi(sBuf);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFQSSJ,pst_gab_dxzp_jjzf->zfqssj,"止付起始时间");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJSSJ,pst_gab_dxzp_jjzf->zfjssj,"止付结束时间");
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjg);
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respmsg);
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqssj);
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjssj);
    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fkjgmc);
    /*账户余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zhye);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jjzf->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_jjzf->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by3);
    return 0;
}

/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945101_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
 函数功能:  获取公安部电信诈骗止付解除报文请求信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945101_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jjzf->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_jjzf->rwxh=1;
    /*原业务申请编号*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_jjzf->yywsqbh,"原业务申请编号");
 
    /*卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->kh);
    
    /*转出账户所属银行机构编码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyh);
    /*转出账户银行名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyhmc);
    /*转出账户名*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhm);
    /*转出账卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczh);
    /*币种*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->bz);
    /*转出金额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcje);

    /*转出日期*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcrq);
    /*转出时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcsj);
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jjzf->khyh,"止付账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jjzf->khyhmc,"止付账户所属银行名称");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jjzf->zhlb,"止付账号类别");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jjzf->zhmc,"止付账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_jjzf->zh,"止付账卡号");
    /*止付到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->dqr);
    /*结果反馈限定时间*/
    pst_gab_dxzp_jjzf->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->jgfksj);
    /*止付解除时间(yyyyMMddHHmmss)*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_jjzf->zfqssj,"止付解除时间");
 
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjg);
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respmsg);
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqssj);
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjssj);
    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fkjgmc);
    /*账户余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zhye);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jjzf->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_jjzf->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by3);
    return 0;
}




/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945102_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
 函数功能:  获取公安部电信诈骗止付延期报文请求信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945102_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jjzf->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_jjzf->rwxh=1;
    /*原业务申请编号*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_jjzf->yywsqbh,"原业务申请编号");
 
    /*卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->kh);
    
    /*转出账户所属银行机构编码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyh);
    /*转出账户银行名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyhmc);
    /*转出账户名*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhm);
    /*转出账卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczh);
    /*币种*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->bz);
    /*转出金额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcje);

    /*转出日期*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcrq);
    /*转出时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcsj);
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jjzf->khyh,"止付账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jjzf->khyhmc,"止付账户所属银行名称");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jjzf->zhlb,"止付账号类别");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jjzf->zhmc,"止付账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_jjzf->zh,"止付账卡号");
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_jjzf->dqr,"止付到期日");
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->dqr);
    /*结果反馈限定时间*/
    pst_gab_dxzp_jjzf->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->jgfksj);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFYQQSSJ,pst_gab_dxzp_jjzf->zfqssj,"止付起始时间");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_jjzf->zfjssj,"止付结束时间");
 
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjg);
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respmsg);
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqssj);
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjssj);
    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fkjgmc);
    /*账户余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zhye);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jjzf->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_jjzf->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by3);
    return 0;
}



/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945103_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
 函数功能:  获取公安部电信诈骗冻结报文请求信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945103_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_djxj->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_djxj->rwxh=1;
    /*原业务申请编号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->yywsqbh);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_djxj->khyh,"冻结账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_djxj->khyhmc,"冻结账户所属银行名称");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_djxj->zhlb,"冻结账号类别"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_djxj->zhmc,"冻结账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_djxj->zh,"冻结账卡号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJLX,pst_gab_dxzp_djxj->zjlx,"冻结账户证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJHM,pst_gab_dxzp_djxj->zjhm,"冻结账号证件号码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DJFS,pst_gab_dxzp_djxj->djfs,"冻结方式"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_djxj->bz,"币种"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JE,pst_gab_dxzp_djxj->je,"金额"); 
    /*冻结到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->dqr);
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_djxj->dqr,"冻结到期日"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DJQSSJ,pst_gab_dxzp_djxj->djqssj,"冻结起始时间"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJSSJ,pst_gab_dxzp_djxj->djjssj,"冻结结束时间"); 
    
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定时间"); 
    pst_gab_dxzp_djxj->jgfksj=atoi(sBuf);
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjg);
    
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respcode);
    
    /*错误原因*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respmsg);
    
    /*卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->kh);
    
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqssj);
    /*执行结束日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjsrq);
    *//*执行结束时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjssj);
    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fkjgmc);
    /*执行冻结金额*/   
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djje);
    /*账户余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhye);
    /*在先冻结金额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjje);
    /*在先冻结到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjrq); 
    /*账户可用余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhkyye); 
    /*在先冻结机关*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjjg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_djxj->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_djxj->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by3);
    return 0;
}






/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945104_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
 函数功能:  获取公安部电信诈骗冻结解除报文请求信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945104_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_djxj->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_djxj->rwxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_djxj->yywsqbh,"原业务申请编号");
 
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_djxj->khyh,"冻结账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_djxj->khyhmc,"冻结账户所属银行名称");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_djxj->zhlb,"冻结账号类别"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_djxj->zhmc,"冻结账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_djxj->zh,"冻结账卡号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJLX,pst_gab_dxzp_djxj->zjlx,"冻结账户证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJHM,pst_gab_dxzp_djxj->zjhm,"冻结账号证件号码");
    /*冻结方式*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djfs); 
    /*币种*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->bz); 
    /*金额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->je); 
    /*冻结到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->dqr);
    /*结果反馈限定时间*/
    pst_gab_dxzp_djxj->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->jgfksj);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_djxj->djqssj,"冻结解除时间(yyyyMMddHHmmss)");
   
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjg);
    
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respcode);
    
    /*错误原因*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respmsg);
    
    /*卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->kh);
    
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqssj);
    /*执行结束日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjsrq);
    *//*执行结束时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjssj);
    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fkjgmc);
    /*执行冻结金额*/   
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djje);
    /*账户余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhye);
    /*在先冻结金额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjje);
    /*在先冻结到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjrq); 
    /*账户可用余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhkyye); 
    /*在先冻结机关*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjjg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_djxj->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_djxj->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by3);
    return 0;
}



/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945105_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
 函数功能:  获取公安部电信诈骗冻结延期报文请求信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945105_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_djxj->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_djxj->rwxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_djxj->yywsqbh,"原业务申请编号");
 
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_djxj->khyh,"冻结账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_djxj->khyhmc,"冻结账户所属银行名称");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_djxj->zhlb,"冻结账号类别"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_djxj->zhmc,"冻结账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_djxj->zh,"冻结账卡号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJLX,pst_gab_dxzp_djxj->zjlx,"冻结账户证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJHM,pst_gab_dxzp_djxj->zjhm,"冻结账号证件号码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DJFS,pst_gab_dxzp_djxj->djfs,"冻结方式");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_djxj->bz,"币种");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JE,pst_gab_dxzp_djxj->je,"金额");
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_djxj->dqr,"冻结到期日");
    /*冻结到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->dqr);
    /*结果反馈限定时间*/
    pst_gab_dxzp_djxj->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->jgfksj);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFYQQSSJ,pst_gab_dxzp_djxj->djqssj,"冻结起始时间");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_djxj->djjssj,"冻结结束时间");
    
   
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjg);
    
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respcode);
    
    /*错误原因*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respmsg);
    
    /*卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->kh);
    
    /*执行起始日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqsrq);
    *//*执行起始时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqssj);
    /*执行结束日期
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjsrq);
    *//*执行结束时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjssj);
    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fkjgmc);
    /*执行冻结金额*/   
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djje);
    /*账户余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhye);
    /*在先冻结金额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjje);
    /*在先冻结到期日*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjrq); 
    /*账户可用余额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhkyye); 
    /*在先冻结机关*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjjg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_djxj->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_djxj->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by3);
    return 0;
}


/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945106_Req(HXMLTREE lXmlhandle, GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
 函数功能:  获取公安部电信诈骗账户交易明细查询报文请求信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945106_Req(HXMLTREE lXmlhandle, GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jymx->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_jymx->rwxh=1;
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jymx->khyh,"查询账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jymx->khyhmc,"查询账户所属银行名称"); 
    /*查询账号类别*/
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jymx->zhlb,"查询账号类别"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jymx->zhmc,"查询账户名");  
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_jymx->zh,"查询账卡号");  
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXNR,pst_gab_dxzp_jymx->cxnr,"查询内容");      
      
   
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXQSSJ,sBuf,"查询起始时间");
    trim(sBuf);
    strncpy( pst_gab_dxzp_jymx->cxqsrq,sBuf,8); 
    strncpy( pst_gab_dxzp_jymx->cxqssj,sBuf+8,6);
    
   
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXJZSJ,sBuf,"查询截止时间");
    trim(sBuf);
    strncpy(pst_gab_dxzp_jymx->cxjzrq,sBuf,8); 
    strncpy(pst_gab_dxzp_jymx->cxjzsj,sBuf+8,6);
   
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定时间"); 
    pst_gab_dxzp_jymx->jgfksj=atoi(sBuf);
        
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->zxjg);    
        
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->respcode);
    
    /*错误原因*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->respmsg);
    /*反馈说明*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->fksm);
    /*反馈机构名称*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->fkjgmc);
     
     
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jymx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_jymx->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->by3);
    return 0;
}




/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945107_Req(HXMLTREE lXmlhandle, GAB_DXZP_SRL_ZTCX *pst_gab_dxzp_ztcx)
 函数功能:  记录电信诈骗主体查询相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945107_Req(HXMLTREE lXmlhandle, GAB_DXZP_ZTCX *pst_gab_dxzp_ztcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_ztcx->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_ztcx->rwxh=1;
 
       
 
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_ztcx->khyh,"查询账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_ztcx->khyhmc,"查询账户所属银行名称");
    
    /*查询账号类别*/
  
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_ztcx->zhlb,"查询账号类别"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_ztcx->zhmc,"查询账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_ztcx->zh,"查询账卡号");
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定时间");
    pst_gab_dxzp_ztcx->jgfksj=atoi(sBuf);
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->zxjg);
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->respmsg);

    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_ztcx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_ztcx->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->by3);
    
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945108_Req(HXMLTREE lXmlhandle,  GAB_DXZP_DTCX  *pst_gab_dxzp_dtcx)
 函数功能:  记录电信诈骗动态查询相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945108_Req(HXMLTREE lXmlhandle, GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_dtcx->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_dtcx->rwxh=1;
    
    /*原业务申请编号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->yywsqbh);
    /*卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->kh);
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_dtcx->bz,"币种");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_dtcx->khyh,"查询账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_dtcx->khyhmc,"查询账户所属银行名称");
    /*查询账号类别*/

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_dtcx->zhlb,"查询账号类别"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_dtcx->zhmc,"查询账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_dtcx->zh,"查询账卡号");

   /*动态命令*/
 	  //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->dtml);
    strcpy(pst_gab_dxzp_dtcx->dtml,"1");
    /*执行起始日期*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZXQSSJ,pst_gab_dxzp_dtcx->zxqsrq,"执行起始日期");
    /*执行截止日期*/
  
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZXJZSJ,pst_gab_dxzp_dtcx->zxjzrq,"执行截止日期");
    
    /*动态查询起始时间*/

    sprintf(pst_gab_dxzp_dtcx->dtcxqssj,"%s%s",GetSysDate(),GetSysTime()); 
    
    /*动态查询截止时间*/
    strcpy(pst_gab_dxzp_dtcx->dtcxjzsj,pst_gab_dxzp_dtcx->dtcxqssj);
       
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定期限");
    pst_gab_dxzp_dtcx->jgfksj = atof(sBuf);
	  
	  /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->zxjg);
    
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respmsg);

    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtcx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_dtcx->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by3);
    
    return 0;
    
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945109_Req(HXMLTREE lXmlhandle,  GAB_DXZP_DTCX  *pst_gab_dxzp_dtcx)
 函数功能:  电信诈骗账户动态查询解除报文动态信息 
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945109_Req(HXMLTREE lXmlhandle, GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_dtcx->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_dtcx->rwxh=1;
    
    /*明天需反馈*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_dtcx->yywsqbh,"原业务申请编号");
    
    /*卡号*/
 	  GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->kh);
 	  /*币种*/
 	  GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->bz);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_dtcx->khyh,"查询账户所属银行机构编码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_dtcx->khyhmc,"查询账户所属银行名称");
    /*查询账号类别*/

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_dtcx->zhlb,"查询账号类别"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_dtcx->zhmc,"查询账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_dtcx->zh,"查询账卡号");
    
    
    /*动态命令*/
 	  //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->dtml);
 	  strcpy(pst_gab_dxzp_dtcx->dtml,"0");
 	  
 	  /*动态查询解除生效时间*/
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZXJZSJ,pst_gab_dxzp_dtcx->zxqsrq,"动态查询解除生效时间");
   
   	GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->zxjzrq);
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定期限");
    pst_gab_dxzp_dtcx->jgfksj = atof(sBuf);
    /*执行结果*/
  	GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->zxjg);
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respmsg);

    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtcx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_dtcx->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by3);
   
   
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945110_Req(HXMLTREE lXmlhandle,  GAB_DXZP_QHCX *pst_gab_dxzp_qhcx
)
 函数功能:  记录电信诈骗全户查询相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945110_Req(HXMLTREE lXmlhandle, GAB_DXZP_QHCX *pst_gab_dxzp_qhcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_qhcx->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_qhcx->rwxh=1;
   
    /*查询账号类别*/

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_qhcx->zhlb,"查询账号类别"); 
       
 	
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXZJLX,pst_gab_dxzp_qhcx->cxzjlx,"查询证照类型代码");
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXZJHM,pst_gab_dxzp_qhcx->cxzjhm,"查询证照号码");
 	  GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_QHCX_DXZP_ZHMC,pst_gab_dxzp_qhcx->zhmc,"查询主体名称");
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXNR,pst_gab_dxzp_qhcx->cxnr,"查询内容");
   
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"结果反馈限定期限");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BANKNAME,pst_gab_dxzp_qhcx->bankname,"查询银行名称");
 	  
    pst_gab_dxzp_qhcx->jgfksj = atof(sBuf);
    
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->zxjg);
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->respmsg);

    /*反馈说明*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->fksm);
    /*反馈机构名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx->zwrq,"gaps日期");

    /*gaps时间*/
    strcpy(pst_gab_dxzp_qhcx->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->by3);
    

    return 0;
}
/*****************************************************
   函数名称:  int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, const char* szPath, const char* nodeAttr, char* szValue, unsigned int size, int iFlag)
   函数功能:  获取XML节点值,若字符串节点为空则赋'-';若金额数字型节点为空则赋0
   函数参数:  lXmlhandle  XML树操作句柄
              Path  节点路径
              nodeAttr 节点属性 0-字符串, 1-金额，数字等
              szValue 节点值存放字符串
              size  存放值的空间大小
              iFlag 节点是否必须存在 GAB_DXZP_XML_NULL GAB_DXZP_XML_NOTNULL
             
   函数返回:  >0: 节点值的实际长度
              -1:输入参数为空或输出变量为NULL
              -2:不为空的XML节点不存在
              -3:其他原因失败

   函数说明:  
            
   修改说明:  
*****************************************************/
int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, char* psPath, char* psNodeAttr, char* psValue, unsigned int size, int iFlag)
{
    int  iRet = 0;
    char sBuf[1024];
    int  iNodeValueLen = 0;
    char* psNodeValue = NULL;
    
    if ( psValue == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]的目标变量为NULL!", MSG_GAB_DXZP_XMLOP, psPath),"")
        return -1;
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iNodeValueLen = sizeof(sBuf);
    if ( iNodeValueLen > size )
    {
        psNodeValue = sBuf;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
        pstrcopy(psValue, psNodeValue, size);
    }else
    {
        iNodeValueLen = size;
        psNodeValue = psValue ;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
    }
    psNodeValue = NULL;
    if( iRet == FAIL && XML_NODE_NOTNULL == iFlag )
    {        
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]不存在[%d]!", MSG_GAB_DXZP_XMLOP, psPath, iRet),"") 
        return -2;
    }
    
    if( (psValue[0] == '\0') && (XML_NODE_NOTNULL == iFlag) )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]值为空!", MSG_GAB_DXZP_XMLOP, psPath),"")
        return -2;
    }    
    trim(psValue);       
    return strlen(psValue);
}




/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_SBXX_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)

 函数功能:  记录电信诈骗上报信息表相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_SBXX_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    char sSql[256];

    GAB_DXZP_DUAL st_gab_dxzp_dual;
   
    /*传输报文流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->csbwlsh);
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sbxx->jybm,"交易编码");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_SBPCH,sBuf,"请求单标识");
    if('\0'==sBuf[0] || 0 == strcmp(sBuf," "))
    	{
        GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sbxx->sbpch,"请求单标识");
      }
     else
     	{
     		trim(sBuf);
     		strcpy(pst_gab_dxzp_sbxx->sbpch,sBuf);
     	}
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sbxx->ywsqbh,"上报批次号");
    /*申请机构代码*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_DXZP_YHJGID,pst_gab_dxzp_sbxx->sqjgdm,"申请机构代码");
    
   
    /*目标机构代码*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_DXZP_QSJGID,pst_gab_dxzp_sbxx->mbjgdm,"目标机构代码");

    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sbxx->ywlx,"业务类型");
  
    /*事件描述*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->sjms);
    /*上报机构代码*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_DXZP_YHJGID,pst_gab_dxzp_sbxx->sbjgdm,"上报机构代码");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_SBJGMC,pst_gab_dxzp_sbxx->sbjgmc,"上报机构名称");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JBRXM,pst_gab_dxzp_sbxx->jbrxm,"经办人姓名");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JBRDH,pst_gab_dxzp_sbxx->jbrdh,"经办人电话");
    if('\0'== pst_gab_dxzp_sbxx->jbrxm[0] || 0 == strcmp(pst_gab_dxzp_sbxx->jbrxm," ") )
    	{
    		GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JBXM,pst_gab_dxzp_sbxx->jbrxm,"经办人姓名");
      }
    if('\0'== pst_gab_dxzp_sbxx->jbrdh[0] || 0 == strcmp(pst_gab_dxzp_sbxx->jbrdh," ") )
    	{
    		GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JBDH,pst_gab_dxzp_sbxx->jbrdh,"经办人电话");
      }
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sbxx->ywrq,"业务日期");
    
    /*业务流水号*/
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"业务流水号");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("登记下达信息表->sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "获取业务流水号");
    snprintf(pst_gab_dxzp_sbxx->ywlsh, sizeof(pst_gab_dxzp_sbxx->ywlsh), 
        "08%ld", st_gab_dxzp_dual.nextval);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JYJG,pst_gab_dxzp_sbxx->jbjg,"经办机构");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JYGY,pst_gab_dxzp_sbxx->jbgy,"经办柜员");
    /*处理日期*/
    strncpy(pst_gab_dxzp_sbxx->clrq,pst_gab_dxzp_sbxx->ywrq,8);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSTIME,pst_gab_dxzp_sbxx->clsj,"处理时间");
    /*上报记录数*/
    memset(sBuf,0x00,sizeof(sBuf));
    pst_gab_dxzp_sbxx->sbjls=1;
    /*上报结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->sbjg);
    /*响应码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->respcode);
    /*响应信息*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->respmsg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sbxx->zwrq,"gaps日期");
    

    /*gaps时间*/
    strcpy(pst_gab_dxzp_sbxx->systime,GetSysTime());
    
    GAB_DXZP_GETXMLSTR_NOTNULL("/pub/zhqzlsh",pst_gab_dxzp_sbxx->zhqzlsh,"gaps流水号");
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->by3);
    

    return 0;
}



/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945111_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAJB *pst_gab_dxzp_sajb)

 函数功能:  记录电信诈骗案件举报相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945111_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAJB *pst_gab_dxzp_sajb)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sajb->sbpch,"上报批次号");
    pst_gab_dxzp_sajb->sbpcxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sajb->jybm,"交易编码");
    /*传输报文流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->csbwlsh);
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sajb->ywsqbh,"请求单标识");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JSJGID,pst_gab_dxzp_sajb->jsjgid,"接收机构ID");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_TGJGBM,pst_gab_dxzp_sajb->tgjgbm,"接收机构ID");
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sajb->ywlx,"业务类型");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SHRXM,pst_gab_dxzp_sajb->shrxm,"受害人姓名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SHRLXDH,pst_gab_dxzp_sajb->shrlxdh,"受害人联系电话");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_sajb->zjlx,"证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_sajb->zjhm,"证件号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJMS,pst_gab_dxzp_sajb->sjms,"事件描述");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_AJJBLX,pst_gab_dxzp_sajb->ajjblx,"案件举报类型");
    
    /*主机日期*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_ZJRQ,pst_gab_dxzp_sajb->zjrq,"主机日期");
    /*主机流水号*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_ZJLSH,pst_gab_dxzp_sajb->zjlsh,"主机流水号");
    /*冻止序号*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_DZXH,pst_gab_dxzp_sajb->dzxh,"冻止序号");
    /*影像标志*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YXBZ,pst_gab_dxzp_sajb->yxbz,"影像标志");
    /*请求单状态*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->qqdzt);
    /*执行结果*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->zxjg);
    /*错误码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->respcode);
    /*错误原因*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->respmsg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sajb->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_sajb->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->by3);
    

    return 0;
}


/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945112_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCKK *pst_gab_dxzp_yckk)

 函数功能:  记录电信诈骗异常开卡记录相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945112_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCKK *pst_gab_dxzp_yckk)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_yckk->sbpch,"上报批次号");
    pst_gab_dxzp_yckk->sbpcxh=1;
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_yckk->jybm,"交易编码");
    
   /*传输报文流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->csbwlsh);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_yckk->ywsqbh,"请求单标识");
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_yckk->ywlx,"业务类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJTZM,pst_gab_dxzp_yckk->sjtzm,"事件特征码");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YYWSQBH,pst_gab_dxzp_yckk->yywsqbh,"原上报编号");
   
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_yckk->zjlx,"证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_yckk->zjhm,"证件号");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_XM,pst_gab_dxzp_yckk->xm,"姓名");
    
    /*账卡号*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->zh);
    /*开卡时间*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->kksj);
    /*开卡地点*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->kkdd);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_yckk->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_yckk->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->by3);
    

    return 0;
}


/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945113_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAZH *pst_gab_dxzp_sazh)

 函数功能:  记录电信诈骗涉案账户记录相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945113_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAZH *pst_gab_dxzp_sazh)
{
    int  iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sazh->sbpch,"上报批次号");
    pst_gab_dxzp_sazh->sbpcxh=1;
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sazh->jybm,"交易编码");
    /*传输报文流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->csbwlsh);
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sazh->ywsqbh,"请求单标识");
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sazh->ywlx,"业务类型");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->ywlx);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJTZM,pst_gab_dxzp_sazh->sjtzm,"事件特征码");
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YYWSQBH,pst_gab_dxzp_sazh->yywsqbh,"原上报编号");
    
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZH,pst_gab_dxzp_sazh->zh,"证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZHM,pst_gab_dxzp_sazh->zhm,"账户名");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_sazh->zjlx,"证件类型");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_sazh->zjhm,"证件号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_LXDH,pst_gab_dxzp_sazh->lxdh,"联系电话");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_TXDZ,pst_gab_dxzp_sazh->txdz,"通讯地址");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YZBM,pst_gab_dxzp_sazh->yzbm,"邮政编码");
   
    /*账户类型*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->zhlx);
    /*账户状态*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->zhzt);
    /*开户日期*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->khrq);
    /*销户日期*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->xhrq);
    /*开卡地点*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->kkdd);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sazh->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_sazh->systime,GetSysTime());
    
    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->by3);
    

    return 0;
}

/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945114_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)

 函数功能:  记录电信诈骗异常事件记录相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945114_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_ycsj->sbpch,"上报批次号");
    pst_gab_dxzp_ycsj->sbpcxh=1;
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_ycsj->jybm,"交易编码");
    /*传输报文流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->csbwlsh);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_ycsj->ywsqbh,"请求单标识");
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_ycsj->ywlx,"业务类型");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ywlx);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJTZM,pst_gab_dxzp_ycsj->sjtzm,"事件特征码");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YYWSQBH,pst_gab_dxzp_ycsj->yywsqbh,"原上报编号");
    
    
    /*交易流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jylsh);
    /*交易时间*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jysj);
    /*交易类型*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jylx);
    /*币种*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->bz);
    /*交易金额*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->je);
    /*转出账户所属银行机构编码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zcyhjg);
    /*转出账户所属银行名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zcyhmc);
    /*转出账户名*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zczhhm);
    /*转出账卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zczh);
    /*交易对端账户所属银行机构编码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddyhjg);
    /*交易对端账户所属银行名称*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddyhmc);
    /*交易对端账户名*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddzhm);
    /*交易对端账卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddzh);
    /*ip地址*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ipdz);
    /*mac地址*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->mac);
    /*设备ID*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->sbid);
    /*交易地点*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jydd);
    /*备注*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->beiz);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_ycsj->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_ycsj->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->by3);
    

    return 0;
}

/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945115_Req(HXMLTREE lXmlhandle,  GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)

 函数功能:  记录电信诈骗账户涉案记录相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945115_Req(HXMLTREE lXmlhandle,  GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_zhsa->jybm,"交易编码");
    
    /*传输报文流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->csbwlsh);
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_zhsa->ywsqbh,"请求单标识");
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_zhsa->ywlx,"业务类型");
    iRet = xml_ElementExist(lXmlhandle, "/gabdxzp/yhkh2");
    if(1 == iRet)
    {
    	strncpy(pst_gab_dxzp_zhsa->ywlx,"0503",4);
    }
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->ywlx);
    /*银行卡号*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YHKH,pst_gab_dxzp_zhsa->zh,"银行卡号");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->zh);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZHM,pst_gab_dxzp_zhsa->zhm,"账户名");
    /*银行卡号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->zt);

    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhsa->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_zhsa->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->by3);
    

    return 0;
}


/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_945116_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)

 函数功能:  记录电信诈骗身份涉案记录相关信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_945116_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sfsa->jybm,"交易编码");
    
    /*传输报文流水号*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->csbwlsh);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sfsa->ywsqbh,"请求单标识");
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sfsa->ywlx,"业务类型");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_sfsa->zjlx,"证件类型");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_sfsa->zjhm,"证件号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJSYRXM,pst_gab_dxzp_sfsa->zhhm,"证件所有人姓名");
    
    /*状态*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->zt);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sfsa->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_sfsa->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->by3);
    

    return 0;
}













/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_ZHXX_ZHJYXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx,int i,int j)

 函数功能:  记录电信诈骗账户信息_账号交易信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_ZHXX_ZHJYXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx,int i,int j)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_YWSQBH,pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,"请求单编号");
    
    /*任务序号*/
    pst_gab_dxzp_zhxx_zhjyxx->rwxh=1;
    /*账户序号*/
    strcpy(pst_gab_dxzp_zhxx_zhjyxx->zhxh,"1");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_ZHJYXH,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh,"账号交易序号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYLX,pst_gab_dxzp_zhxx_zhjyxx->jylx,"交易类型");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYYE,pst_gab_dxzp_zhxx_zhjyxx->jyye,"交易余额");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYSJ,pst_gab_dxzp_zhxx_zhjyxx->jysj,"交易时间");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYLSH,pst_gab_dxzp_zhxx_zhjyxx->jylsh,"交易流水号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFMC,pst_gab_dxzp_zhxx_zhjyxx->jydfmc,"交易对方名称");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFZH,pst_gab_dxzp_zhxx_zhjyxx->jydfzh,"交易对方账号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFZJHM,pst_gab_dxzp_zhxx_zhjyxx->jydfzjhm,"交易对方证件号码");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFZHKHH,pst_gab_dxzp_zhxx_zhjyxx->jydfzhkhh,"交易对方账号开户行");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYZY,pst_gab_dxzp_zhxx_zhjyxx->jyzy,"交易摘要");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYWDMC,pst_gab_dxzp_zhxx_zhjyxx->jywdmc,"交易网点名称");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYWDDM,pst_gab_dxzp_zhxx_zhjyxx->jywddm,"交易网点代码");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_RZH,pst_gab_dxzp_zhxx_zhjyxx->rzh,"日志号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_CPH,pst_gab_dxzp_zhxx_zhjyxx->cph,"传票号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_PZZL,pst_gab_dxzp_zhxx_zhjyxx->pzzl,"凭证种类");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_PZH,pst_gab_dxzp_zhxx_zhjyxx->pzh,"凭证号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_XJBZ,pst_gab_dxzp_zhxx_zhjyxx->xjbz,"现金标志");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_ZDH,pst_gab_dxzp_zhxx_zhjyxx->zdh,"终端号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYSFCG,pst_gab_dxzp_zhxx_zhjyxx->jysfcg,"交易是否成功");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYFSD,pst_gab_dxzp_zhxx_zhjyxx->jyfsd,"交易发生地");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_SHMC,pst_gab_dxzp_zhxx_zhjyxx->shmc,"商户名称");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_SHH,pst_gab_dxzp_zhxx_zhjyxx->shh,"商户号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_IP,pst_gab_dxzp_zhxx_zhjyxx->ip,"ip地址");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_MAC,pst_gab_dxzp_zhxx_zhjyxx->mac,"mac地址");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYGYH,pst_gab_dxzp_zhxx_zhjyxx->jygyh,"交易柜员号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_BEIZ,pst_gab_dxzp_zhxx_zhjyxx->beiz,"备注");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JDBZ,pst_gab_dxzp_zhxx_zhjyxx->jdbz,"借贷标志");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_BZ,pst_gab_dxzp_zhxx_zhjyxx->bz,"币种");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYJE,pst_gab_dxzp_zhxx_zhjyxx->jyje,"交易金额");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhxx_zhjyxx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_zhxx_zhjyxx->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhxx_zhjyxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhxx_zhjyxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhxx_zhjyxx->by3);
    

    return 0;
}













/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_ZHJBXX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)

 函数功能:  记录电信诈骗账户账户基本信息_账号信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_ZHJBXX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_YWSQBH,pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,"请求单编号");
    
    /*任务序号*/
    pst_gab_dxzp_zhjbxx_zhxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHXH,pst_gab_dxzp_zhjbxx_zhxx->zhxh,"账户序号");
    //trim(sBuf);
    //pst_gab_dxzp_zhjbxx_zhxx->zhxh=atoi(sBuf);
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZH,pst_gab_dxzp_zhjbxx_zhxx->zh,"账号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHLX,pst_gab_dxzp_zhjbxx_zhxx->zhlx,"账户类型");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHZT,pst_gab_dxzp_zhjbxx_zhxx->zhzt,"账户状态");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_BZ,pst_gab_dxzp_zhjbxx_zhxx->bz,"币种");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_CHBZ,pst_gab_dxzp_zhjbxx_zhxx->chbz,"钞汇标志");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHYE,pst_gab_dxzp_zhjbxx_zhxx->zhye,"账户余额");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_KYYE,pst_gab_dxzp_zhjbxx_zhxx->kyye,"可用余额");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHJYSJ,pst_gab_dxzp_zhjbxx_zhxx->zhjysj,"最后交易时间");
 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhjbxx_zhxx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_zhjbxx_zhxx->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by3);
    

    return 0;
}











/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_QHCX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)

 函数功能:  记录电信诈骗账户账户基本信息_账号信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_ZHXX_YWSQBH,pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,"请求单编号");
    
    /*任务序号*/
    pst_gab_dxzp_zhjbxx_zhxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHXH,pst_gab_dxzp_zhjbxx_zhxx->zhxh,"账户序号");

    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZH,pst_gab_dxzp_zhjbxx_zhxx->zh,"账号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHLX,pst_gab_dxzp_zhjbxx_zhxx->zhlx,"账户类型");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHZT,pst_gab_dxzp_zhjbxx_zhxx->zhzt,"账户状态");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_BZ,pst_gab_dxzp_zhjbxx_zhxx->bz,"币种");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_CHBZ,pst_gab_dxzp_zhjbxx_zhxx->chbz,"钞汇标志");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHYE,pst_gab_dxzp_zhjbxx_zhxx->zhye,"账户余额");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_KYYE,pst_gab_dxzp_zhjbxx_zhxx->kyye,"可用余额");
    
 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhjbxx_zhxx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_zhjbxx_zhxx->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by3);
    

    return 0;
}
















/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_JYMX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)

 函数功能:  记录电信诈骗账户账户基本信息_账号信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_JYMX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_YWSQBH,pst_gab_dxzp_jymx_zhjbxx->ywsqbh,"请求单编号");
    
    /*任务序号*/
    pst_gab_dxzp_jymx_zhjbxx->rwxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_ZHM,pst_gab_dxzp_jymx_zhjbxx->zhm,"账户名");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KZH,pst_gab_dxzp_jymx_zhjbxx->kzh,"卡/折号");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KHWD,pst_gab_dxzp_jymx_zhjbxx->khwd,"开户网点");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KHWDDM,pst_gab_dxzp_jymx_zhjbxx->khwddm,"开户网点代码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KHRQ,pst_gab_dxzp_jymx_zhjbxx->khrq,"开户日期");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_XHRQ,pst_gab_dxzp_jymx_zhjbxx->xhrq,"销户日期");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_XHWD,pst_gab_dxzp_jymx_zhjbxx->xhwd,"销户网点");
    /*GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_ZHJYSJ,pst_gab_dxzp_jymx_zhjbxx->zhjysj,"最后交易时间");*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_BEIZ,pst_gab_dxzp_jymx_zhjbxx->beiz,"备注");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jymx_zhjbxx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_jymx_zhjbxx->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by3);
    

    return 0;
}













/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_QHCX_SFQZXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx,int i)

 函数功能:  记录电信诈骗全户查询_司法强制信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_SFQZXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_SFQZXX_YWSQBH,pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,"请求单编号");
    /*任务序号*/
    pst_gab_dxzp_qhcx_sfqzxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_CSXH,pst_gab_dxzp_qhcx_sfqzxx->csxh,"措施序号");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_ZH,pst_gab_dxzp_qhcx_sfqzxx->zh,"账号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_KH,pst_gab_dxzp_qhcx_sfqzxx->kh,"卡/折号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJKSR,pst_gab_dxzp_qhcx_sfqzxx->djksr,"冻结开始日");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJJZR,pst_gab_dxzp_qhcx_sfqzxx->djjzr,"冻结截止日");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJJGMC,pst_gab_dxzp_qhcx_sfqzxx->djjgmc,"冻结机关名称");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_BZ,pst_gab_dxzp_qhcx_sfqzxx->bz,"币种");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJJE,pst_gab_dxzp_qhcx_sfqzxx->djje,"冻结金额");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_BEIZ,pst_gab_dxzp_qhcx_sfqzxx->beiz,"备注");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJCSLX,pst_gab_dxzp_qhcx_sfqzxx->djcslx,"冻结措施类型");
    
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx_sfqzxx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_qhcx_sfqzxx->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_sfqzxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_sfqzxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_sfqzxx->by3);
    

    return 0;
}
















/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_QHCX_ZZHXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCH_ZZHXX *pst_gab_dxzp_qhcx_zzhxx,int i)
 函数功能:  获取电信诈骗全户查询-子账号信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_ZZHXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCX_ZZHXX *pst_gab_dxzp_qhcx_zzhxx,int i,int j)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_ZZHXX_YWSQBH,pst_gab_dxzp_qhcx_zzhxx->ywsqbh,"业务申请编号");
    /*任务序号*/
    pst_gab_dxzp_qhcx_zzhxx->rwxh=i;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZZHXH,pst_gab_dxzp_qhcx_zzhxx->zzhxh,"子账户序号");
   
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZH,pst_gab_dxzp_qhcx_zzhxx->zh,"账（卡）号");
    
    /*业务类型*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZZHLB,pst_gab_dxzp_qhcx_zzhxx->zzhlb,"子账户类别");
    
    //GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZZHZH,pst_gab_dxzp_qhcx_zzhxx->zzhzh,"子账户账号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_BZ,pst_gab_dxzp_qhcx_zzhxx->bz,"币种");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_CHBZ,pst_gab_dxzp_qhcx_zzhxx->chbz,"钞汇标志");
        /*账户余额*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZHYE,pst_gab_dxzp_qhcx_zzhxx->zhye,"账户余额");
      /*账户状态*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZHZT,pst_gab_dxzp_qhcx_zzhxx->zhzt,"账户状态");
    /*可用余额*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_KYYE,pst_gab_dxzp_qhcx_zzhxx->kyye,"可用余额");
    /*最后交易时间*/
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZHJYSJ,pst_gab_dxzp_qhcx_zzhxx->zhjysj,"最后交易时间");

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx_zzhxx->zwrq,"gaps日期");
    
    /*gaps时间*/
   
    strcpy(pst_gab_dxzp_qhcx_zzhxx->systime,GetSysTime());
    
     /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_zzhxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_zzhxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_zzhxx->by3);
    
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_QHCX_QLXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx,int i)
 函数功能:  获取电信诈骗全户查询-子账号信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_QLXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_QLXX_YWSQBH,pst_gab_dxzp_qhcx_qlxx->ywsqbh,"业务申请编号");
    /*任务序号*/
    pst_gab_dxzp_qhcx_qlxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_XH,pst_gab_dxzp_qhcx_qlxx->xh,"序号");
    
 
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_ZH,pst_gab_dxzp_qhcx_qlxx->zh,"账号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_KH,pst_gab_dxzp_qhcx_qlxx->kh,"帐卡号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_ZJLX,pst_gab_dxzp_qhcx_qlxx->zjlx,"证件类型代码");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_ZJHM,pst_gab_dxzp_qhcx_qlxx->zjhm,"证件号码");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLLX,pst_gab_dxzp_qhcx_qlxx->qllx,"权利类型");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLRXM,pst_gab_dxzp_qhcx_qlxx->qlrxm,"权利人姓名");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLJE,pst_gab_dxzp_qhcx_qlxx->qlje,"权利金额");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLRTXDZ,pst_gab_dxzp_qhcx_qlxx->qlrtxdz,"权利人通讯地址");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLRLXFS,pst_gab_dxzp_qhcx_qlxx->qlrlxfs,"权利人联系方式");
  
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx_qlxx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_qhcx_qlxx->systime,GetSysTime());
   
    
     /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_qlxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_qlxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_qlxx->by3);
    
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_DTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp,int i)
 函数功能:  获取电信诈骗动态查询响应
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_DTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_SBPCH,pst_gab_dxzp_dtcx_resp->sbpch,"上报批次号");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SBPCXH,sBuf,"上报批次序号");
    trim(sBuf);
    pst_gab_dxzp_dtcx_resp->sbpcxh=atoi(sBuf);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_YWSQBH,pst_gab_dxzp_dtcx_resp->ywsqbh,"业务申请编号");
    /*任务序号*/
    //pst_gab_dxzp_dtcx_resp->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/dccs",sBuf,"任务序号");
    trim(sBuf);
    if('\0'==sBuf[0])
    	{
    	   pst_gab_dxzp_dtcx_resp->rwxh=1;
    	}
    else
    	{
    		 pst_gab_dxzp_dtcx_resp->rwxh=atoi(sBuf)+1;
    	}
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_ZHM,pst_gab_dxzp_dtcx_resp->zhm,"账户名");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_CXZH,pst_gab_dxzp_dtcx_resp->zh,"账号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYLX,pst_gab_dxzp_dtcx_resp->jylx,"交易类型");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JDBZ,pst_gab_dxzp_dtcx_resp->jdbz,"借贷标志");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_BZ,pst_gab_dxzp_dtcx_resp->bz,"币种");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYJE,pst_gab_dxzp_dtcx_resp->jyje,"交易金额");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYYE,pst_gab_dxzp_dtcx_resp->jyye,"交易余额");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYSJ,pst_gab_dxzp_dtcx_resp->jysj,"交易时间");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYLSH,pst_gab_dxzp_dtcx_resp->jylsh,"交易流水号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFMC,pst_gab_dxzp_dtcx_resp->jydfmc,"交易对方名称");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFZH,pst_gab_dxzp_dtcx_resp->jydfzh,"交易对方账号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFZJHM,pst_gab_dxzp_dtcx_resp->jydfzjhm,"交易对方证件号码");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFZHKHH,pst_gab_dxzp_dtcx_resp->jydfzhkhh,"交易对方账户开户行");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYZY,pst_gab_dxzp_dtcx_resp->jyzy,"交易摘要");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYWDMC,pst_gab_dxzp_dtcx_resp->jywdmc,"交易网点名称");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYWDDM,pst_gab_dxzp_dtcx_resp->jywddm,"交易网点代码");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_RZH,pst_gab_dxzp_dtcx_resp->rzh,"日志号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_CPH,pst_gab_dxzp_dtcx_resp->cph,"传票号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_PZZL,pst_gab_dxzp_dtcx_resp->pzzl,"凭证种类");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_PZH,pst_gab_dxzp_dtcx_resp->pzh,"凭证号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_XJBZ,pst_gab_dxzp_dtcx_resp->xjbz,"现金标志");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_ZDH,pst_gab_dxzp_dtcx_resp->zdh,"终端号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYSFCG,pst_gab_dxzp_dtcx_resp->jysfcg,"交易是否成功");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYFSD,pst_gab_dxzp_dtcx_resp->jyfsd,"交易发生地");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_MAC,pst_gab_dxzp_dtcx_resp->mac,"mac地址");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYGYH,pst_gab_dxzp_dtcx_resp->jygyh,"交易柜员号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_BEIZ,pst_gab_dxzp_dtcx_resp->beiz,"备注");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SHMC,pst_gab_dxzp_dtcx_resp->shmc,"商户名称");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SHH,pst_gab_dxzp_dtcx_resp->shh,"商户号");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_IP,pst_gab_dxzp_dtcx_resp->ip,"ip地址");

    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_FKJGMC,pst_gab_dxzp_dtcx_resp->fkjgmc,"反馈机构名称");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_FKSM,pst_gab_dxzp_dtcx_resp->fksm,"查询反馈说明");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtcx_resp->zwrq,"gaps日期");
    
    /*gaps时间*/
   strcpy(pst_gab_dxzp_dtcx_resp->systime,GetSysTime());
   
   
     /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx_resp->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx_resp->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx_resp->by3);
    
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_DTJC_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
 函数功能:  获取电信诈骗动态解除响应信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_DTJC_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTJC_RESP_YWSQBH,pst_gab_dxzp_dtjc_resp->ywsqbh,"业务申请编号");
    /*任务序号*/
    pst_gab_dxzp_dtjc_resp->rwxh=1;
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTJC_RESP_JCDTCXSM,pst_gab_dxzp_dtjc_resp->jcdtcxsm,"解除动态查询说明");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTJC_RESP_FKSM,pst_gab_dxzp_dtjc_resp->fksm,"反馈说明");


    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtjc_resp->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_dtjc_resp->systime,GetSysTime());
   
    
     /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtjc_resp->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtjc_resp->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtjc_resp->by3);
    
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_ZTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
 函数功能:  获取电信诈骗主体查询响应信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_ZTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_YWSQBH,pst_gab_dxzp_ztcx_resp->ywsqbh,"业务申请编号");
    /*任务序号*/
    pst_gab_dxzp_ztcx_resp->rwxh=1;
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FKJGMC,pst_gab_dxzp_ztcx_resp->fkjgmc,"反馈机构名称");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FKSM,pst_gab_dxzp_ztcx_resp->fksm,"查询反馈说明");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZJLX,pst_gab_dxzp_ztcx_resp->zjlx,"查询证件类型代码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZJHM,pst_gab_dxzp_ztcx_resp->zjhm,"查询证件号码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZTMC,pst_gab_dxzp_ztcx_resp->ztmc,"查询主体名称");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_LXSJ,pst_gab_dxzp_ztcx_resp->lxsj,"联系手机");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DBRXM,pst_gab_dxzp_ztcx_resp->dbrxm,"账/卡代办人姓名");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DBRZJLX,pst_gab_dxzp_ztcx_resp->dbrzjlx,"账/卡代办人证件类型");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DBRZJHM,pst_gab_dxzp_ztcx_resp->dbrzjhm,"账/卡代办人证件号码");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZZDZ,pst_gab_dxzp_ztcx_resp->zzdz,"住宅地址");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZZDH,pst_gab_dxzp_ztcx_resp->zzdh,"住宅电话");
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_GZDW,pst_gab_dxzp_ztcx_resp->gzdw,"工作单位");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DWDZ,pst_gab_dxzp_ztcx_resp->dwdz,"单位地址");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DWDH,pst_gab_dxzp_ztcx_resp->dwdh,"单位电话");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_YXDZ,pst_gab_dxzp_ztcx_resp->yxdz,"邮箱地址");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FRDB,pst_gab_dxzp_ztcx_resp->frdb,"法人代表");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FRDBZJLX,pst_gab_dxzp_ztcx_resp->frdbzjlx,"法人代表证件类型");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FRDBZJHM,pst_gab_dxzp_ztcx_resp->frdbzjhm,"法人代表证件号码");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_KHGSZZHM,pst_gab_dxzp_ztcx_resp->khgszzhm,"客户工商执照号码");

    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_GSNSH,pst_gab_dxzp_ztcx_resp->gsnsh,"国税纳税号");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DSNSH,pst_gab_dxzp_ztcx_resp->dsnsh,"地税纳税号");

  
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_ztcx_resp->zwrq,"gaps日期");
    
    /*gaps时间*/
   strcpy(pst_gab_dxzp_ztcx_resp->systime,GetSysTime());
   
    
     /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx_resp->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx_resp->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx_resp->by3);
    
    return 0;
}









/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_SMJFJ_Req(HXMLTREE lXmlhandle, GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
 函数功能:  获取电信诈骗扫描件附件信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_SMJFJ_Req(HXMLTREE lXmlhandle, GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_APPLICATIONID,pst_gab_dxzp_smjfj->ywsqbh,"业务申请编号");
    
    /*序号*/
    pst_gab_dxzp_smjfj->xh=1;
    /*文件名*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->wjm);
    /*文件大小*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->wjdx);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_smjfj->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_smjfj->systime,GetSysTime());
   
   
     /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->by3);
    
    return 0;
}










/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_SBXX_PLZT_Req(HXMLTREE lXmlhandle, GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt,int i)
 函数功能:  获取电信诈骗扫描件附件信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_SBXX_PLZT_Req(HXMLTREE lXmlhandle, GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_SBPCH,pst_gab_dxzp_sbxx_plzt->sbpch,"上报批次号");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SBPCXH,sBuf,"上报批次序号");
    trim(sBuf);
    pst_gab_dxzp_sbxx_plzt->sbpcxh=atoi(sBuf);
   
   
    /*上报交易代码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->sbjydm);
    /*上报状态*/
    strcpy(pst_gab_dxzp_sbxx_plzt->sbzt,"0");
    /*响应码*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->respcode);

    /*响应信息*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->respmsg);

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sbxx_plzt->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_sbxx_plzt->systime,GetSysTime());
   
   
     /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->by3);
    
    return 0;
}





/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_QHCX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx,int i)

 函数功能:  记录电信诈骗账户账户基本信息_账号信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_ZHJBXX_YWSQBH,pst_gab_dxzp_jymx_zhjbxx->ywsqbh,"业务申请编号");
    
    /*任务序号*/
    pst_gab_dxzp_jymx_zhjbxx->rwxh=i;
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_ZHM,pst_gab_dxzp_jymx_zhjbxx->zhm,"账户名");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KZH,pst_gab_dxzp_jymx_zhjbxx->kzh,"卡/折号");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KHWD,pst_gab_dxzp_jymx_zhjbxx->khwd,"开户网点");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KHWDDM,pst_gab_dxzp_jymx_zhjbxx->khwddm,"开户网点代码");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KHRQ,pst_gab_dxzp_jymx_zhjbxx->khrq,"开户日期");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_XHRQ,pst_gab_dxzp_jymx_zhjbxx->xhrq,"销户日期");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_XHWD,pst_gab_dxzp_jymx_zhjbxx->xhwd,"销户网点");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_BEIZ,pst_gab_dxzp_jymx_zhjbxx->beiz,"备注");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jymx_zhjbxx->zwrq,"gaps日期");
    
    /*gaps时间*/
    strcpy(pst_gab_dxzp_jymx_zhjbxx->systime,GetSysTime());
    

    /*备用1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by3);
    

    return 0;
}

















enum {
  LF = 0xA,
  CR = 0xD,
  NL = '\n',
  default_maxlen = 76,
  eq_sign = 100,
  pad_idx = 64
};

const char g_EncTable[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/=";

const int g_DecTable[] = {
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,62,-1,-1,-1,63,52,53,
        54,55,56,57,58,59,60,61,-1,-1,
        -1, eq_sign, -1,-1,-1, 0, 1, 2, 3, 4,
         5, 6, 7, 8, 9,10,11,12,13,14,
        15,16,17,18,19,20,21,22,23,24,
        25,-1,-1,-1,-1,-1,-1,26,27,28,
        29,30,31,32,33,34,35,36,37,38,
        39,40,41,42,43,44,45,46,47,48,
        49,50,51,-1
};

const int g_DecTableSz = sizeof(g_DecTable) / sizeof(char);

static int fpub_b64_encode(int _idx, unsigned char *ch, char **_out, int *pos, int maxlen)
{
  int pad_count = 3 - _idx;
  int i, len = 0;
  int idx[4];
  char *out = *_out;

  idx[0] = ch[0] >> 2;
  switch(pad_count)
  {
  case 0:
    idx[1] = (((ch[0] & 3) << 4) |  (ch[1] >> 4));
    idx[2] = ((ch[1] & 0xf) << 2) | (ch[2] >> 6);
    idx[3] = ch[2] & 0x3f;
    break;
  case 1:
    idx[1] = (((ch[0] & 3) << 4) |  (ch[1] >> 4));
    idx[2] = (ch[1] & 0xf) << 2 ;
    idx[3] = pad_idx;
    break;
  case 2:
    idx[1] = (ch[0] & 3) << 4;
    idx[2] = idx[3] = pad_idx;
    break;
  }
  for(i = 0; i < 4; ++i)
  {
    *out++ = g_EncTable[ idx[i] ];
    len++;
    ++(*pos);
    if (maxlen > 0 && *pos > maxlen) {
      *out++ = NL;
      len++;
      *pos = 1;
    }
  }
  *_out = out;
  return len;
}

char * fpub_base64_encode(char *src, int *size, int maxlen)
{
  unsigned char ch[3];
  char *_ret = NULL;
  char *r;
  int idx = 0;
  int len, i;
  int outsize = 0;
  int pos = 1;

  len = (*size) / 3 * 4 + 4;
  if (maxlen > 0)
    len += ((len / maxlen) + 1);
  _ret = (char *)malloc(len+1);
  if (_ret == NULL)
    return NULL;
  r = _ret;
  memset(r, 0, len+1);

  for(i = 0; i < *size; i++)
  {
    ch[idx++] = (unsigned char)src[i];
    if(idx < 3)
      continue;
    outsize += fpub_b64_encode(idx, ch, &r, &pos, maxlen);
    idx = 0;
  }
  if(idx > 0)
  {
    outsize += fpub_b64_encode(idx, ch, &r, &pos, maxlen);
  }
  *size = outsize;
  return _ret;
}

static int fpub_b64_decode(int idx, unsigned char *ch, char **_out)
{
  char *out = *_out;
  int len = 0;

  if(idx < 4)
  {
    switch(idx)
    {
    case 0:
    case 1:
      return len;
    case 2:
      ch[2] = ch[3] = eq_sign;
      break;
    case 3:
      ch[3] = eq_sign;
      break;
    }
  }
  *out++ = (ch[0] << 2 | ((ch[1] >> 4) & 0x3) );
  len++;
  if(ch[2] == eq_sign)
    return len;
  *out++ = (ch[1] << 4 | ((ch[2] >> 2) & 0xF) );
  len++;
  if(ch[3] == eq_sign)
    return len;
  *out++ = (ch[2] << 6 | ch[3]);
  len++;

  *_out = out;
  return len;
}

/*****************************************************
   函数名称:  char * fpub_base64_decode(char *src, int *size)
   函数功能:  base64转码
   函数参数:
       char *src    源串
       int  *size   目标串长度


   函数返回:   NULL 失败
              !NULL 成功


   函数说明:


   修改说明:
*****************************************************/
char * fpub_base64_decode(char *src, int *size)
{
     unsigned char c;
     char *_ret = NULL;
     char *r;
     unsigned char ch[4];
     int idx = 0;
     int len, i;
     int outsize = 0;

     len = (*size) / 4 * 3+1;
     _ret = (char *)malloc(len+1);
     if (_ret == NULL)
       return NULL;
     r = _ret;
     memset(r, 0, len+1);

     for(i = 0; i < *size; i++)
     {
       c = (unsigned char)src[i];
       if(c > g_DecTableSz || g_DecTable[c] == -1)
         continue;
       ch[idx++] = g_DecTable[c];
       if(idx < 4)
         continue;
       outsize += fpub_b64_decode(idx, ch, &r);
       idx = 0;
     }
     if(idx > 0)
       outsize += fpub_b64_decode(idx, ch, &r);
     *size = outsize;
     return _ret;
}
int convert(char *src, char *dest, char *input, size_t ilen, char *output, size_t *olen)
{
    char **pin = &input;
    char **pout = &output;
    iconv_t cd = iconv_open(dest, src);
    if (cd == (iconv_t)-1)
    {
        return -1;
    }
    if (iconv(cd, pin, &ilen, pout, olen))
    {
        iconv_close(cd);
        return -2;
    }
    iconv_close(cd);
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getMoveHours(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveHours, char *psNewDateTime, int iNewDateTime)

 函数功能:  计算偏移后日期时间
 函数参数:  lXmlhandle           XML句柄
            psOldDateTime        原日期时间
            iMoveHours           偏移小时数
            psNewDateTime        新日期时间

 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ReturnDate(char *currdate,int steps)
{
	time_t  now,time1;
	int retdate,ndays=0,n;
	struct tm *ptm,tm1;
	char yy[5],mm[3],dd[3];

	memset(yy,0,sizeof(yy));
	memset(mm,0,sizeof(mm));
	memset(dd,0,sizeof(dd));
	memcpy(yy,currdate,4);yy[4]=0;
	memcpy(mm,currdate+4,2);mm[2]=0;
	memcpy(dd,currdate+6,2);dd[2]=0;
	ndays=steps;

	time(&now);
	tm1 = *localtime(&now);
	tm1.tm_year = atoi(yy)-1900;
  	tm1.tm_mon = atoi(mm)-1;
  	tm1.tm_mday = atoi(dd);
	time1 = mktime(&tm1);

	n=(int)(difftime(time1,now)/(60*60*24));
	ndays+=n;
  	now += ndays * 3600 * 24;
  	if(ndays >0)
  		now -=3600;

  	ptm = localtime(&now);
  	retdate = (ptm->tm_year+1900) * 10000 + (ptm->tm_mon + 1) * 100 + ptm->tm_mday;
	return retdate;
}

int ffunc_gabdxzp_getMoveHours(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveHours, char *psNewDateTime, int iNewDateTime)
{
    int iHours=0;
    int iDays=0,iHour=0;
    char sOldDate[8+1];/*基准日期*/
    char sOldTime[6+1];/*基准小时*/
    char sHours[2+1];
    char sBuf[256];
    char sDesDate[8+1];
    char sDayTime[14+1];
    
    /*获取原基准日期和基准时间*/
    memset(sOldDate, 0x00, sizeof(sOldDate));
    pstrcopy(sOldDate, psOldDateTime, sizeof(sOldDate));
    memset(sOldTime, 0x00, sizeof(sOldTime));
    pstrcopy(sOldTime, psOldDateTime+8, sizeof(sOldTime));
    
    /*获取基准小时*/
    memset(sHours, 0x00, sizeof(sHours));
    strncpy(sHours, sOldTime, 2);
    /*计算偏移小时=基准小时 + 偏移小时数*/
    iHours = atoi(sHours) + iMoveHours;
    iDays = iHours / 24;
    /*计算多余小时=偏移小时 - N整天*/
    iHour = iMoveHours - ( iDays*24 );
    iHours = iHours - ( iDays*24 );
    /*计算偏移日期*/
	memset(sDesDate,0,sizeof(sDesDate));
	snprintf(sDesDate, sizeof(sDesDate), "%d",ReturnDate(sOldDate,iDays));
    /*计算偏移日期时间*/
    memset(psNewDateTime, 0x00, iNewDateTime);
    snprintf(psNewDateTime, iNewDateTime, "%s%02d%4s", sDesDate, iHours, sOldTime+2);
    
    return 0;
}
/*****************************************************
 函数名称:  int ffunc_gabdxzp_getMoveMins(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveHours, char *psNewDateTime, int iNewDateTime)

 函数功能:  计算提前日期分钟
 函数参数:  lXmlhandle           XML句柄
            psOldDateTime        原日期时间
            iMoveMins            提前分钟数
            psNewDateTime        新日期时间

 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getMoveMins(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveMins, char *psNewDateTime, int iNewDateTime)
{
    char sCurDate[8+1];
    char sCurTime[6+1];
    char sBuf[256];
    char sNewDate[8+1];
    char sCurMM[2+1];
    int iTimes=0;
    int iDays=0;
    int iHours=0;
    int iCurHours=0;
    int iAddHours=0;
    int iMins=0;
    int iCurMins=0;
    int iAddMins=0;

    memset(sCurDate, 0x00, sizeof(sCurDate));
    strncpy(sCurDate, psOldDateTime, sizeof(sCurDate)-1);
    memset(sCurTime, 0x00, sizeof(sCurTime));
    strncpy(sCurTime, psOldDateTime+8, sizeof(sCurTime)-1);
    iTimes = iMoveMins;
    /*截取当前小时和分钟*/
    memset(sBuf, 0x00, sizeof(sBuf));
    strncpy(sBuf, sCurTime, 2);
    iCurHours=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    strncpy(sBuf, sCurTime+2, 2);
    iCurMins=atoi(sBuf);
    /*计算提前天数*/
    iDays = iTimes / 1440;
    if ( iDays > 0 )
    {/*提前N天*/
        memset(sNewDate, 0x00, sizeof(sNewDate));
        iDays *= -1;
        snprintf(sNewDate, sizeof(sNewDate), "%d", ReturnDate(sCurDate,iDays));
        strncpy(sCurDate, sNewDate, sizeof(sCurDate)-1);
        iTimes += iDays * 1440;
        /*printf("应提前[%d]天后,iTime[%d]\n", iDays, iTimes);*/
    }
    /*计算提前小时数*/
    iHours = iTimes / 60;
    /*printf("iHours[%d] = iTimes[%d]/60;\n", iHours, iTimes);*/
    if ( iHours > 0 )
    {/*提前N小时*/
        iAddHours = iCurHours - iHours ;
        if ( iAddHours < 0 )
        {/*需要借一天*/
            memset(sNewDate, 0x00, sizeof(sNewDate));
            snprintf(sNewDate, sizeof(sNewDate), "%d", ReturnDate(sCurDate,-1));
            strncpy(sCurDate, sNewDate, sizeof(sCurDate)-1);
            iCurHours += iAddHours;
        }else
        {
            iCurHours = iAddHours;
        }
        /*printf("Now=[%s%02d%02d]\n", sCurDate, iCurHours, iCurMins);*/
        iTimes -= iHours * 60;
    }
    /*计算提前N分钟*/
    iAddMins = iCurMins - iTimes;
    if ( iAddMins < 0 )
    {/*需要借一小时*/
        iCurMins = iAddMins + 60;
        iCurHours -= 1;
        iAddHours = iCurHours;
        if ( iAddHours < 0 )
        {/*需要借一天*/
            memset(sNewDate, 0x00, sizeof(sNewDate));
            snprintf(sNewDate, sizeof(sNewDate), "%d", ReturnDate(sCurDate,-1));
            strncpy(sCurDate, sNewDate, sizeof(sCurDate)-1);
            /*alter iAddHours-->24 by liukq 20160428 BEGIN*/
            iCurHours += 24;
            /*alter by liukq 20160428 END*/
        }else
        {
            iCurHours = iAddHours;
        }
        /*printf("Now=[%s%02d%02d]\n", sCurDate, iCurHours, iCurMins);*/
    }else
    {
        iCurMins = iAddMins;
    }
    snprintf(psNewDateTime, iNewDateTime, "%s%02d%02d%s", sCurDate, iCurHours, iCurMins, sCurTime+4);
    return 0;
}

/* dci 二层封装函数 */
/* 查询一条记录到结构体中 */
/*
功能: 查询，结果存入结构体
返回值:
    <0 失败
    =0 查无记录
    >0 查询成功
*/
int ffunc_dbop_selToStruct( const char* sSql, FLD_DESC desc_arr[], int desc_num, void* pdes)
{
    CURSOR cur;
    char szErrMsg[512];

    if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
    {
        LOG(LM_STD, Fmtmsg("传入参数空"), "WARNING");
        return -1;
    }
    cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
    if (cur == INVALID_CURSOR)
    {
        LOG(LM_STD, Fmtmsg("游标定义失败[%s]-[%s]",  DCILastError(), sSql), "ERROR");
        return -2;
    }
    if(DCIExecute(cur) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败[%s]", DCILastError() ), "ERROR");
        DCIFreeCursor(cur);
        return -3;
    }

    int rs = 0;
    if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
    {
        LOG(LM_STD, Fmtmsg("游标获取记录错误[%s]",  szErrMsg ), "ERROR");
        DCIFreeCursor(cur);
        return -4;
    }
    DCIFreeCursor(cur);  /*被遗漏过*/
    return rs;
}

/* dci 二层封装函数 */
/* 声明及执行游标 */
/*
功能: 声明及执行游标
返回值:
    <0 失败
    =0 成功
*/
int ffunc_dbop_dcrExecCursor(HXMLTREE lXmlhandle, const char* psSql, char *psCurSorName, CURSOR *cur)
{
    if ((*cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("打开%s游标失败", psCurSorName),fpub_GetCompname(lXmlhandle));
    }
    if (DCIExecute(*cur) == -1)
    {
        DCIFreeCursor(*cur);
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("执行%s游标失败", psCurSorName),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/* 释放游标 */
/*
功能: 释放游标
返回值:
    <0 失败
    =0 成功
*/
int ffunc_dbop_freeCursor(HXMLTREE lXmlhandle, char *psCurSorName, CURSOR *cur)
{
    if (DCIFreeCursor(*cur) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("释放%s游标失败", psCurSorName),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/*****************************************************
   函数名称:  int ffunc_file_crtLocalPath(HXMLTREE lXmlhandle, char* psFilePath)
   函数功能:  创建本地文件目录
   函数参数:  
              psFilePath   文件路径(绝对路径)                 
              
   函数返回:  正常: 0
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
int ffunc_file_crtLocalPath(HXMLTREE lXmlhandle, char* psFilePath)
{
	FILE *fp;
	char sFileName[256];
	int iRet = -1;
    
    if ( !psFilePath || psFilePath[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("文件路径输入参数不能为空" ));
        return -1;
    }
    
    memset(sFileName, 0x00, sizeof(sFileName));
    snprintf(sFileName, sizeof(sFileName), "%s/%s", psFilePath, "a.txt");
    iRet = access(sFileName, F_OK);
    if ( iRet != 0  )
    {
        /*创建文件路径*/
        iRet = mkdir(psFilePath, S_IRWXU+S_IRGRP+S_IWGRP+S_IROTH);
        if ( iRet != 0 )
        {
            fpub_SetMsg(lXmlhandle, 99002, Fmtmsg("文件操作失败[%s]", strerror(errno)));
            LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("文件操作失败[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        }
        /*创建a.txt文件*/
        fp = fopen(sFileName,"w");
        if ( fp == NULL )
        {	
            fpub_SetMsg(lXmlhandle, 99002, Fmtmsg("文件操作失败[%s]", strerror(errno)));
            LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("文件操作失败[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        }
        fclose(fp);
    }        
	return 0;		
}

/*****************************************************
   函数名称:  int ffunc_file_wrtFile(HXMLTREE lXmlhandle, char* psFilePath)
   函数功能:  创建本地文件目录
   函数参数:  
              psFilePath   文件路径(绝对路径)                 
              
   函数返回:  正常: 0
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
int ffunc_file_wrtFile(HXMLTREE lXmlhandle, char* psFileName, char *psFileConent, int iFileLen)
{
	FILE *fp;
	int iRet = -1;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("文件路径输入参数不能为空" ));
        return -1;
    }
    /*创建文件*/
    fp = fopen(psFileName,"w");
    if ( fp == NULL )
    {	
        fpub_SetMsg(lXmlhandle, 99002, Fmtmsg("文件操作失败[%s]", strerror(errno)));
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("文件操作失败[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle)); 
    }
    fwrite(psFileConent, iFileLen, 1, fp);
    fclose(fp);
    return 0;
}

/*****************************************************
   函数名称:  int ffunc_file_getFileName(HXMLTREE lXmlhandle, char* psAbsFileName, char* psFileName)
   函数功能:  从绝对路径文件中获取文件名称
   函数参数:  
              psAbsFileName   文件名称(绝对路径)  
              psFileName      文件名称               
              
   函数返回:  正常: 0
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
int ffunc_file_getFileName(HXMLTREE lXmlhandle, char* psAbsFileName, char* psFileName)
{
	char sFileName[256];
	int iRet = -1;
	int iAbsLen = 0;
	int iFound = 0;
	int i;
    
    if ( !psAbsFileName || psAbsFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("绝对文件名称不能为空" ));
        return -1;
    }
    
    iAbsLen = strlen(psAbsFileName);
    for ( i=iAbsLen; i>=0; i--)
    {
        if ( psAbsFileName[i] == '/')
        {
            iFound = 1;
            break;
        }
        continue;
    }
    if ( iFound == 1 && psFileName )
    {
        pstrcopy(psFileName, psAbsFileName + i + 1, iAbsLen - i);
    }
        
	return 0;		
}

/*****************************************************
   函数名称:  int ffunc_file_getFileSize(HXMLTREE lXmlhandle, char* psFileName, int* iFileSize)
   函数功能:  获取文件大小
   函数参数:  
              psFileName   文件名(绝对路径)
              iFileSize    文件大小
              
   函数返回:  正常: 0
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
int ffunc_file_getFileSize(HXMLTREE lXmlhandle, char* psFileName, int* iFileSize)
{
	FILE *fp;
    struct stat struStat;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("文件名不能为空" ));
        return -1;
    }
    
    fp = fopen(psFileName,"r");
    if ( fp == NULL )
    {	
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
    }
    fstat(fileno(fp), &struStat);
    
    *iFileSize = struStat.st_size;
    fclose(fp);
    
	return 0;		
}
/*****************************************************
   函数名称:  char* ffunc_file_getFileContents(HXMLTREE lXmlhandle)
   函数功能:  获取文件内容
   函数参数:  
              psFileName   文件名(绝对路径)
              iFileSize    文件大小                  
              
   函数返回:  正常: 文件内容指针,需在外部free
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
char*  ffunc_file_getFileContents(HXMLTREE lXmlhandle, char* psFileName, int *iFileSize)
{
    char *psFileContents = NULL;
    FILE *fp;
    caddr_t pUpfileHead;
    struct stat struStat;
    int iRet = -1;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("文件名不能为空" ));
        return NULL;
    }
    
    iRet = ffunc_file_getFileSize(lXmlhandle, psFileName, iFileSize);
    if ( iRet < 0 )
    {
        LOG(LM_STD, Fmtmsg("获取文件大小失败[%d]", iRet), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    psFileContents = (char *)malloc(*iFileSize+1);
    if (psFileContents == NULL)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    memset(psFileContents, 0x00, *iFileSize+1);
    
    fp = fopen(psFileName,"rb");
    if ( fp == NULL )
    {	
        free(psFileContents);psFileContents=NULL;
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    if ((pUpfileHead = mmap(NULL, (size_t)*iFileSize, PROT_READ, MAP_SHARED, fileno(fp), (off_t)0)) == (caddr_t) - 1)
    {
        free(psFileContents);psFileContents=NULL;
        munmap(pUpfileHead, (size_t)*iFileSize);
        fclose(fp);	
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, *iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }

    pstrcopy(psFileContents, pUpfileHead, *iFileSize+1);
    munmap(pUpfileHead, (size_t)*iFileSize);
    fclose(fp);
    
    return psFileContents;
}
/*****************************************************
   函数名称:  char* ffunc_file_getJPEGContents(HXMLTREE lXmlhandle)
   函数功能:  获取影像内容
   函数参数:  
              psFileName   文件名(绝对路径)
              iFileSize    文件大小                  
              
   函数返回:  正常: 文件内容指针,需在外部free
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
char*  ffunc_file_getJPEGContents(HXMLTREE lXmlhandle, char* psFileName, int *iFileSize)
{
    char *psFileContents = NULL;
    FILE *fp;
    struct stat struStat;
    char sFileCont[10240];
    int iRet = -1;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("文件名不能为空" ));
        return NULL;
    }
    
    iRet = ffunc_file_getFileSize(lXmlhandle, psFileName, iFileSize);
    if ( iRet < 0 )
    {
        LOG(LM_STD, Fmtmsg("获取文件大小失败[%d]", iRet), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    psFileContents = (char *)malloc(*iFileSize+1);
    if (psFileContents == NULL)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    memset(psFileContents, 0x00, *iFileSize+1);

    fp = fopen(psFileName,"rb");
    if ( fp == NULL )
    {	
        free(psFileContents);psFileContents=NULL;
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    } 
    iRet=fread(psFileContents,(size_t)*iFileSize,1 ,fp);
    LOG(LM_STD, Fmtmsg("1------[%d]-[%d]---", iRet, *iFileSize), fpub_GetCompname(lXmlhandle)); 
    /*if ( strlen(psFileContents) > 0)
    {
        free(psFileContents);psFileContents=NULL;
        LOG(LM_STD, Fmtmsg("1----[%s]------",strerror(errno)), fpub_GetCompname(lXmlhandle));
        fclose(fp);	
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, *iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }*/
LOG(LM_STD, Fmtmsg("2----------"), fpub_GetCompname(lXmlhandle));
    fclose(fp);
    
    return psFileContents;
}
/*****************************************************
   函数名称:  int ffunc_dxzp_945118_DTCX_hxqs(HXMLTREE lXmlhandle, char *sSql)
   函数功能:  动态查询核心取数
   函数参数:  
              sSql   动态查询语句              
              
   函数返回:  正常: 0
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
int ffunc_dxzp_945118_DTCX_hxqs(HXMLTREE lXmlhandle, char *psSql, char *psCurDateTime)
{
    int  iParas;
    char sBuf[256];
    char errmsg[256];
    char sOriQqdZt[2+1];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    GAB_DXZP_XDXX gab_dxzp_xdxx;
    GAB_DXZP_DTCX gab_dxzp_dtcx;
    
    /* 查询需要处理的任务 */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
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
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        if (gab_dxzp_autoproc.qqdzt[1] == '9' && gab_dxzp_autoproc.qqdzt[0] != '9')
        {/*正在处理中,取一条记录*/
            continue;
        }
        /*alter 22-->30 by liukq 20160426 BEGIN*/
        if (strcmp(gab_dxzp_autoproc.qqdzt, "30") == 0 ||
            strcmp(gab_dxzp_autoproc.qqdzt, "40") == 0 )
        {/*正在处理中,取一条记录*/
            continue;
        }
        /*alter by liukq 20160426 END*/
        memset(&gab_dxzp_dtcx, 0x00, sizeof(gab_dxzp_dtcx));
         /*add by liukq 20160324 BEGIN*/
        GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        gab_dxzp_dtcx.rwxh=1;
        iRet = fdbop_qry_gab_dxzp_dtcx(lXmlhandle,&gab_dxzp_dtcx);
        if ( iRet < 0 )
        {
            continue;
        }
        /*add by liukq 20160324 END*/
        if (strcmp(gab_dxzp_autoproc.qqdzt, "99") == 0 )
        {/*42--已上报前置数据后,需重置查询起始时间为上次查询截止时间*/
            GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.dtcxqssj, gab_dxzp_dtcx.dtcxjzsj)
        }
        memset(&gab_dxzp_xdxx, 0x00, sizeof(gab_dxzp_xdxx));
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
        GAB_DXZP_PSTRCOPY(sOriQqdZt, gab_dxzp_autoproc.qqdzt)
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.qqdzt, "20")
        iRet = fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &gab_dxzp_xdxx, sOriQqdZt);
        if ( iRet < 0 )
        {
            continue;
        }
        /*alter by liukq 20160324 BEGIN
        memset(&gab_dxzp_dtcx, 0x00, sizeof(gab_dxzp_dtcx));
        
        GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        gab_dxzp_dtcx.rwxh=1;
        alter by liukq 20160324 END*/
        GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.dtcxjzsj, psCurDateTime)
        iRet = fdbop_upd_gab_dxzp_dtcx_qzsj(lXmlhandle, &gab_dxzp_dtcx);
        DCICommit();
        if ( iRet < 0 )
        {
            continue;
        }
        /* 公共交易信息赋值 */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);/*业务申请编号*/
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_CLLX, "2");/*处理类型*/
        LOG(LM_STD,Fmtmsg("即将调用待处理业务流程flow_gabdxzp_945117处理,ywsqbh[%s],jjcd[%s],qqdzt[%s]",
            gab_dxzp_autoproc.ywsqbh, gab_dxzp_autoproc.jjcd, gab_dxzp_autoproc.qqdzt),"INFO");
        /* 调用待处理业务入口 */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945117")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("调用待处理业务流程flow_gabdxzp_945117[%s]失败",
                gab_dxzp_autoproc.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("执行待处理业务流程失败"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    LOG(LM_STD,Fmtmsg("电信诈骗动态查询核心取数,共处理[%d]条业务", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"电信诈骗动态查询核心取数执行结束");
    return COMPRET_SUCC;
}


/*****************************************************
   函数名称:  int ffunc_dxzp_945118_DTCX_fkqz(HXMLTREE lXmlhandle, char *sSql)
   函数功能:  动态查询反馈前置
   函数参数:  
              sSql   动态查询语句              
              
   函数返回:  正常: 0
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
int ffunc_dxzp_945118_DTCX_fkqz(HXMLTREE lXmlhandle, char *psSql, char *psCurDateTime)
{
    int  iParas;
    char sBuf[256];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    char sOriQqdZt[2+1];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    GAB_DXZP_XDXX gab_dxzp_xdxx;
    
    /* 查询需要处理的任务 */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
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
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
         
        if (gab_dxzp_autoproc.qqdzt[1] == '9'  )
        {/*正在处理中,取一条记录*/
            continue;
        }
        
        memset(&gab_dxzp_xdxx, 0x00, sizeof(gab_dxzp_xdxx));
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        iRet = fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &gab_dxzp_xdxx);
        if ( iRet < 0 )
        {
            continue;
        }
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);
        /* 公共交易信息赋值 */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBPCH, gab_dxzp_xdxx.sbpch);/*上报批次号*/
        LOG(LM_STD,Fmtmsg("即将调用待处理业务流程flow_gabdxzp_945122处理,sbpch[%s]",
            gab_dxzp_xdxx.sbpch),"INFO");
        /* 调用待处理业务入口 */
        if(fpub_CallFlow(lXmlhandle,"flow_gabdxzp_945122")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("调用批量信息上报业务流程flow_gabdxzp_945122[%s]失败",
                gab_dxzp_autoproc.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("调用批量信息上报业务流程失败"));
            return COMPRET_FAIL ;
        }
        memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
        GAB_DXZP_PSTRCOPY(sOriQqdZt, gab_dxzp_xdxx.qqdzt)
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.qqdzt, "99")
        iRet = fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &gab_dxzp_xdxx, sOriQqdZt);
        DCICommit();
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("电信诈骗动态查询反馈前置,共处理[%d]条业务", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"电信诈骗动态查询反馈前置执行结束");
    return COMPRET_SUCC;
}

/*****************************************************
   函数名称:  int ffunc_dxzp_DTCX_sstsfk(HXMLTREE lXmlhandle, char *sSql)
   函数功能:  动态查询反馈前置
   函数参数:  
              sSql   动态查询语句              
              
   函数返回:  正常: 0
              错误:

   函数说明:  

   修改说明:  
*****************************************************/
int ffunc_dxzp_DTCX_sstsfk(HXMLTREE lXmlhandle, char *psSql, char *psCurDateTime)
{
    int  iParas;
    char sBuf[256];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    char sOriQqdZt[2+1];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    GAB_DXZP_XDXX gab_dxzp_xdxx;
    
    /* 查询需要处理的任务 */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
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
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        memset(&gab_dxzp_xdxx, 0x00, sizeof(gab_dxzp_xdxx));
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        iRet = fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &gab_dxzp_xdxx);
        if ( iRet < 0 )
        {
            continue;
        }
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);
        /* 公共交易信息赋值 */
        LOG(LM_STD,Fmtmsg("即将调用动态查询实时反馈流程flow_gabdxzp_945108_2处理,sbpch[%s]",
            gab_dxzp_xdxx.sbpch),"INFO");
        /* 调用待处理业务入口 */
        if(fpub_CallFlow(lXmlhandle,"flow_gabdxzp_945108_2")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("调用批量信息上报业务流程flow_gabdxzp_945108_2[%s]失败",
                gab_dxzp_autoproc.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("调用批量信息上报业务流程失败"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("电信诈骗动态查询反馈前置,共处理[%d]条业务", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"电信诈骗动态查询反馈前置执行结束");
    return COMPRET_SUCC;
}



/*****************************************************
   函数名称:  int GetItemValueT(char *src, char *split, char *out, int index)
   函数功能:  动态查询反馈前置
   函数参数:  
                       
              
   函数返回:  

   函数说明:  

   修改说明:  
*****************************************************/


char *GetItemValueT(char *src, char *split, char *out, int index)
{
  char *p=NULL;
  int n = 0;
  int nFlag = 0; /* 0为初始值，1为半个汉字 */
  char srctmp[1+1];
  unsigned char uc;
  char *pStr=NULL;
  pStr = src;
  int indexflag = 0;
  
  /* 先找到第index个分隔符的位置 */
    while(indexflag < index)
    {
        while(*pStr != NULL)
          {
              uc = (unsigned char)*pStr;
            if (nFlag == 1)
            {
                /* 前一次为半个汉字，那么这次肯定要拷贝剩下的半个汉字 */
                nFlag = 0;
            }
            else
            {
                /* 前一次不为汉字的情况 */
                /* 判断这次的字符是否为半个汉字的情况 */
                if(uc >= 0x81 && uc <= 0xFE && nFlag == 0) /* 汉字的情况 */
                {
                    nFlag = 1;
                }
                else
                {
                    /* 这次也不为半个汉字的情况 */
                    if ((strncmp(pStr, split, strlen(split)) == 0))//第一个$出现
                	   {
                	   	pStr ++;
                	   	if ((strncmp(pStr, split, strlen(split)) == 0))//判断第二个是否为$符
                	   		{                                            //
                	   			 break;                                    
                	   		}                                            //
                	   	else                                           //若第二个不是$符
                	   		{                                            //
                	   			pStr --;                                   //指针指向前一个
                	   		}                                            //
                	   }
                }
            }
            
            *pStr ++;
          }
        indexflag++;
        *pStr ++;
    }
  
  /*LOG(LM_DEBUG,Fmtmsg("---pStr[%s]---", pStr),"INFO")*/
  while(*pStr != NULL){
        /* 可能包含汉字的情况 */
        /* 如果不增加处理，会出现“珅、弢”这种半个汉字的情况 */
        /*if ((strncmp(pStr, split, strlen(split)) == 0) && (index != 2))
            break;*/
        
        memset(srctmp, 0, sizeof(srctmp));
        strncpy(srctmp, pStr, 1);
        /*LOG(LM_DEBUG,Fmtmsg("srctmp[%s]  pStr[%s] [%d]", srctmp, pStr,nFlag),"INFO")*/
        
        uc = (unsigned char)*pStr;
        if (nFlag == 1)
        {
            /* 前一次为半个汉字，那么这次肯定要拷贝剩下的半个汉字 */
            nFlag = 0;
        }
        else
        {
            /* 前一次不为汉字的情况 */
            /* 判断这次的字符是否为半个汉字的情况 */
            if(uc >= 0x81 && uc <= 0xFE && nFlag == 0) /* 汉字的情况 */
            {
                nFlag = 1;
              
            }
            else
            {
                /* 这次也不为半个汉字的情况 */
                if ((strncmp(pStr, split, strlen(split)) == 0))//第一个$出现
                	{
                		pStr ++;//
                		if ((strncmp(pStr, split, strlen(split)) == 0))//判断第二个是否为$符
                			{                                            //
                				 break;                       
                			}                                            //
                		else                                           //若第二个不是$符
                			{                                            //
                				pStr --;                                   //指针指向前一个
                			}                                            //
                	}
                   
            }
        }

    
    
    out[n++] = *pStr ++;
  }
  
  /*LOG(LM_DEBUG,Fmtmsg("out【%s】", out),"INFO")*/
  out[n] = 0;
  return out;
}
















/*****************************************************
 函数名称:  int ffunc_gabdxzp_getXml_HHMD(HXMLTREE lXmlhandle, GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
 函数功能:  获取电信诈骗扫描件附件信息
 函数参数:  lXmlhandle           XML句柄


 函数返回:  0   :成功
 -1  :失败

 函数说明:

 修改说明:
 *****************************************************/
int ffunc_gabdxzp_getXml_HHMD(HXMLTREE lXmlhandle, GAB_DXZP_HHMD *pst_gab_dxzp_hhmd,char *sbuf)
{
    int iRet = -1;
    /*名单类型*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->mdlx, 0); 
		trim(pst_gab_dxzp_hhmd->mdlx);
		/*名单键值*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->mdjz, 1); 
		trim(pst_gab_dxzp_hhmd->mdjz); 
		
		/*名单来源*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->mdly, 3); 
		trim(pst_gab_dxzp_hhmd->mdly); 
		/*案件类型*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->ajlx, 4); 
		trim(pst_gab_dxzp_hhmd->ajlx); 
		/*姓名*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->xm, 5); 
		trim(pst_gab_dxzp_hhmd->xm); 
		/*名单级别*/
		GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->mdjb);
		/*更新日期*/
		strcpy(pst_gab_dxzp_hhmd->gxrq,GetSysDate());
		/*更新时间*/
		strcpy(pst_gab_dxzp_hhmd->gxsj,GetSysTime());
		/*备用1*/
		GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->by1);
    /*备用2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->by2);
    /*备用3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->by3);
        
    return 0;
}




/*****************************************************
   函数名称:  int ffunc_date_getNow()
   函数功能:  获取当前系统时间戳
   函数参数:     
       
              
              
   函数返回:  正常: 0    成功
              错误: < 0  出错

   函数说明:  
              获取当前系统时间戳
              
              snprintf(sBuf, sizeof(sBuf), "%s", ffunc_date_getNow());
   修改说明:  
*****************************************************/
char* ffunc_date_getNow()
{
    struct timeb tp;
    struct tm *tm;
    static char sTimeStamp[64];
    
    ftime(&tp);
    tm = localtime(&tp.time);
    memset(sTimeStamp, 0x00, sizeof(sTimeStamp));
    snprintf(sTimeStamp, sizeof(sTimeStamp), "%4d-%02d-%02d %02d:%02d:%02d.%.3d",
            1900+ tm->tm_year,
            1 + tm->tm_mon,
            tm->tm_mday,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec,
            tp.millitm
            );
    return sTimeStamp;
}
