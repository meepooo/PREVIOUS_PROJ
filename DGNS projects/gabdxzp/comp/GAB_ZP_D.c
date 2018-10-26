/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:恒生电信诈骗前置系统
版    本:V2.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE\INFORMIX\DB2
文件名称:GAB_ZP_D.c
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



/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_djxj
   函数功能:  查询电信诈骗冻结续解表
   函数参数:  *pst_gab_dxzp_djxj  电信诈骗冻结续解表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_djxj(HXMLTREE lXmlhandle,GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_djxj where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DJXJ, NUMELE(SD_GAB_DXZP_DJXJ), pst_gab_dxzp_djxj );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗冻结续解表失败,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗冻结续解表相关记录,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_djxj
   函数功能:  登记电信诈骗冻结续解表
   函数参数:  *pst_gab_dxzp_djxj  电信诈骗冻结续解表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_djxj(HXMLTREE lXmlhandle,GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_djxj", SD_GAB_DXZP_DJXJ, NUMELE(SD_GAB_DXZP_DJXJ), pst_gab_dxzp_djxj, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗冻结续解表失败,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}



/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_sajb
   函数功能:  查询电信诈骗涉案举报表
   函数参数:  *pst_gab_dxzp_sajb  电信诈骗涉案举报表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_sajb(HXMLTREE lXmlhandle,GAB_DXZP_SAJB *pst_gab_dxzp_sajb)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sajb where csbwlsh='%s'", pst_gab_dxzp_sajb->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SAJB, NUMELE(SD_GAB_DXZP_SAJB), pst_gab_dxzp_sajb );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗涉案举报表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sajb->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗涉案举报表相关记录,csbwlsh[%s]", 
           pst_gab_dxzp_sajb->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_sajb
   函数功能:  登记电信诈骗涉案举报表
   函数参数:  *pst_gab_dxzp_sajb  电信诈骗涉案举报表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_sajb(HXMLTREE lXmlhandle,GAB_DXZP_SAJB *pst_gab_dxzp_sajb)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sajb", SD_GAB_DXZP_SAJB, NUMELE(SD_GAB_DXZP_SAJB), pst_gab_dxzp_sajb, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗涉案举报表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sajb->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}





/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_sazh
   函数功能:  查询电信诈骗涉案账户表
   函数参数:  *pst_gab_dxzp_sazh  电信诈骗涉案账户表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_sazh(HXMLTREE lXmlhandle,GAB_DXZP_SAZH *pst_gab_dxzp_sazh)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sazh where csbwlsh='%s'", pst_gab_dxzp_sazh->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SAZH, NUMELE(SD_GAB_DXZP_SAZH), pst_gab_dxzp_sazh );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗涉案账户表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sazh->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗涉案账户表相关记录,csbwlsh[%s]", 
            pst_gab_dxzp_sazh->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_sazh
   函数功能:  登记电信诈骗涉案账户表
   函数参数:  *pst_gab_dxzp_sazh  电信诈骗涉案账户表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_sazh(HXMLTREE lXmlhandle,GAB_DXZP_SAZH *pst_gab_dxzp_sazh)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sazh", SD_GAB_DXZP_SAZH, NUMELE(SD_GAB_DXZP_SAZH), pst_gab_dxzp_sazh, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗涉案账户表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sazh->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_sbxx
   函数功能:  电信诈骗上报信息表
   函数参数:  *pst_gab_dxzp_sbxx  电信诈骗上报信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_sbxx(HXMLTREE lXmlhandle,GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sbxx where csbwlsh='%s'", pst_gab_dxzp_sbxx->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SBXX, NUMELE(SD_GAB_DXZP_SBXX), pst_gab_dxzp_sbxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗上报信息表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sbxx->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗上报信息表相关记录,csbwlsh[%s]", 
            pst_gab_dxzp_sbxx->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_sbxx
   函数功能:  电信诈骗上报信息表
   函数参数:  *pst_gab_dxzp_sbxx 电信诈骗上报信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_sbxx(HXMLTREE lXmlhandle,GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sbxx", SD_GAB_DXZP_SBXX, NUMELE(SD_GAB_DXZP_SBXX), pst_gab_dxzp_sbxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("电信诈骗上报信息表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sbxx->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_sfsa
   函数功能:  查询电信诈骗身份涉案表
   函数参数:  *pst_gab_dxzp_sfsa  电信诈骗身份涉案表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_sfsa(HXMLTREE lXmlhandle,GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sfsa where csbwlsh='%s'", pst_gab_dxzp_sfsa->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SFSA, NUMELE(SD_GAB_DXZP_SFSA), pst_gab_dxzp_sfsa );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗身份涉案表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sfsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗身份涉案表相关记录,csbwlsh[%s]", 
            pst_gab_dxzp_sfsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_sfsa
   函数功能:  电信诈骗身份涉案表
   函数参数:  *pst_gab_dxzp_sfsa  电信诈骗身份涉案表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_sfsa(HXMLTREE lXmlhandle,GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sfsa", SD_GAB_DXZP_SFSA, NUMELE(SD_GAB_DXZP_SFSA), pst_gab_dxzp_sfsa, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗身份涉案表失败,csbwlsh[%s]", 
            pst_gab_dxzp_sfsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}



/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_xdxx
   函数功能:  查询电信诈骗下达信息表
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_xdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_xdxx where ywsqbh='%s'", pst_gab_dxzp_xdxx->ywsqbh);
   
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_XDXX, NUMELE(SD_GAB_DXZP_XDXX), pst_gab_dxzp_xdxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗下达信息表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_xdxx
   函数功能:  登记电信诈骗下达信息表
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_xdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_xdxx", SD_GAB_DXZP_XDXX, NUMELE(SD_GAB_DXZP_XDXX), pst_gab_dxzp_xdxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}

/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_xdxx
   函数功能:  更新电信诈骗下达信息表
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set zxjg='%s', respcode='%s', respmsg='%s', qqdzt='%s' where ywsqbh='%s'", 
        pst_gab_dxzp_xdxx->zxjg, pst_gab_dxzp_xdxx->respcode, 
        pst_gab_dxzp_xdxx->respmsg,pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->ywsqbh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗下达信息表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_xdxx_aftCallHost
   函数功能:  更新电信诈骗下达信息表
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_aftCallHost(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *pOriQqdZt)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    /*alter clrq,clsj by liukq 20160328 20160330 tjhxcs+1 add ywydm,ywydxx 20160408 BEGIN*/
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set zxjg='%s', respcode='%s', respmsg='%s', zjrq='%s', zjlsh='%s', sbpch='%s', qqdzt='%s',clrq='%s',clsj='%s',tjhxcs=tjhxcs+1,ywydm='%s',ywydxx='%s'", 
        pst_gab_dxzp_xdxx->zxjg, pst_gab_dxzp_xdxx->respcode, 
        pst_gab_dxzp_xdxx->respmsg,
        pst_gab_dxzp_xdxx->zjrq, pst_gab_dxzp_xdxx->zjlsh,
        pst_gab_dxzp_xdxx->sbpch, pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->clrq, pst_gab_dxzp_xdxx->clsj,pst_gab_dxzp_xdxx->ywydm,pst_gab_dxzp_xdxx->ywydxx);
  
    if( '\0' != pst_gab_dxzp_xdxx->dzxh[0] || 0 != strlen(pst_gab_dxzp_xdxx->dzxh) )
    	{
    		sprintf(sSql,"%s,dzxh ='%s'",sSql,pst_gab_dxzp_xdxx->dzxh);
    	}
    
    sprintf(sSql,"%s  where ywsqbh='%s' and qqdzt='%s'",sSql, pst_gab_dxzp_xdxx->ywsqbh, pOriQqdZt);
    /*alter by liukq 20160328 END*/
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗下达信息表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_busi
   函数功能:  更新电信诈骗分表信息
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_busi(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *psTableName)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_%s set zxjg='%s', respcode='%s', respmsg='%s' where ywsqbh='%s' and rwxh=1", 
        psTableName,
        pst_gab_dxzp_xdxx->zxjg, pst_gab_dxzp_xdxx->respcode, pst_gab_dxzp_xdxx->respmsg,
        pst_gab_dxzp_xdxx->ywsqbh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_%s.sql[%s]", psTableName, sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗下达信息表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_xdxx_qqdzt
   函数功能:  更新电信诈骗下达信息表请求单状态
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_qqdzt(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *psOriQqdZt)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set qqdzt='%s' where ywsqbh='%s' and qqdzt='%s'", 
        pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->ywsqbh, psOriQqdZt);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗下达信息表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_xdxx_ywlsh
   函数功能:  更新电信诈骗下达信息表请求单状态
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_ywlsh(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *psOriQqdZt)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set ywrq='%s', ywlsh='%s', qqdzt='%s' where ywsqbh='%s' and qqdzt='%s'", 
        pst_gab_dxzp_xdxx->ywrq,pst_gab_dxzp_xdxx->ywlsh,
        pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->ywsqbh, psOriQqdZt);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗下达信息表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_yckk
   函数功能:  查询电信诈骗异常开卡表
   函数参数:  *pst_gab_dxzp_yckk  电信诈骗异常开卡表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_yckk(HXMLTREE lXmlhandle,GAB_DXZP_YCKK *pst_gab_dxzp_yckk)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_yckk where csbwlsh='%s'", pst_gab_dxzp_yckk->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_YCKK, NUMELE(SD_GAB_DXZP_YCKK), pst_gab_dxzp_yckk );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗异常开卡表失败,csbwlsh[%s]", 
            pst_gab_dxzp_yckk->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗异常开卡表相关记录,csbwlsh[%s]", 
            pst_gab_dxzp_yckk->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_yckk
   函数功能:  登记电信诈骗异常开卡表
   函数参数:  *pst_gab_dxzp_yckk  电信诈骗异常开卡表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_yckk(HXMLTREE lXmlhandle,GAB_DXZP_YCKK *pst_gab_dxzp_yckk)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_yckk", SD_GAB_DXZP_YCKK, NUMELE(SD_GAB_DXZP_YCKK), pst_gab_dxzp_yckk, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗异常开卡表失败,csbwlsh[%s]", 
            pst_gab_dxzp_yckk->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_ycsj
   函数功能:  查询电信诈骗异常事件表
   函数参数:  *pst_gab_dxzp_ycsj  电信诈骗异常事件表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_ycsj(HXMLTREE lXmlhandle,GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_ycsj where csbwlsh='%s'", pst_gab_dxzp_ycsj->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_YCSJ, NUMELE(SD_GAB_DXZP_YCSJ), pst_gab_dxzp_ycsj );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗异常事件表失败,csbwlsh[%s]", 
            pst_gab_dxzp_ycsj->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗异常事件表相关记录,csbwlsh[%s]", 
            pst_gab_dxzp_ycsj->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_ycsj
   函数功能:  登记电信诈骗异常事件表
   函数参数:  *pst_gab_dxzp_ycsj  电信诈骗异常事件表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_ycsj(HXMLTREE lXmlhandle,GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_ycsj", SD_GAB_DXZP_YCSJ, NUMELE(SD_GAB_DXZP_YCSJ), pst_gab_dxzp_ycsj, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗异常事件表失败,csbwlsh[%s]", 
            pst_gab_dxzp_ycsj->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_zhsa
   函数功能:  查询电信诈骗账户涉案表
   函数参数:  *pst_gab_dxzp_zhsa 电信诈骗账户涉案表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_zhsa(HXMLTREE lXmlhandle,GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_zhsa where csbwlsh='%s'", pst_gab_dxzp_zhsa->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZHSA, NUMELE(SD_GAB_DXZP_ZHSA), pst_gab_dxzp_zhsa );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗账户涉案表失败,csbwlsh[%s]", 
            pst_gab_dxzp_zhsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗账户涉案表相关记录,csbwlsh[%s]", 
            pst_gab_dxzp_zhsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_zhsa
   函数功能:  登记电信诈骗账户涉案表
   函数参数:  *pst_gab_dxzp_zhsa  电信诈骗账户涉案表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_zhsa(HXMLTREE lXmlhandle,GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_zhsa", SD_GAB_DXZP_ZHSA, NUMELE(SD_GAB_DXZP_ZHSA), pst_gab_dxzp_zhsa, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗账户涉案表失败,csbwlsh[%s]", 
            pst_gab_dxzp_zhsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}




/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_ztcx
   函数功能:  查询电信诈骗主体查询表
   函数参数:  *pst_gab_dxzp_ztcx  电信诈骗主体查询表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_ztcx(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX *pst_gab_dxzp_ztcx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_ztcx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZTCX, NUMELE(SD_GAB_DXZP_ZTCX), pst_gab_dxzp_ztcx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗主体查询表失败,ywsqbh[%s],rwxh=[%d]", 
            pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗主体查询表相关记录,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_ztcx
   函数功能:  登记电信诈骗主体查询表
   函数参数:  *pst_gab_dxzp_ztcx  电信诈骗主体查询表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_ztcx(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX *pst_gab_dxzp_ztcx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_ztcx", SD_GAB_DXZP_ZTCX, NUMELE(SD_GAB_DXZP_ZTCX), pst_gab_dxzp_ztcx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗主体查询表失败,ywsqbh[%s],rwxh=[%d]", 
            pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_dtcx
   函数功能:  查询电信诈骗动态查询表
   函数参数:  *pst_gab_dxzp_dtcx  电信诈骗动态查询表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_dtcx(HXMLTREE lXmlhandle,GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_dtcx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DTCX, NUMELE(SD_GAB_DXZP_DTCX), pst_gab_dxzp_dtcx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗动态查询表失败,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗动态查询表相关记录,ywsqbh[%s],rwxh[%d]", 
           pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_dtcx
   函数功能:  登记电信诈骗动态查询表
   函数参数:  *pst_gab_dxzp_dtcx  电信诈骗动态查询表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_dtcx(HXMLTREE lXmlhandle,GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_dtcx", SD_GAB_DXZP_DTCX, NUMELE(SD_GAB_DXZP_DTCX), pst_gab_dxzp_dtcx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗动态查询表失败,ywsqbh[%s],rwxh[%d]", 
           pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}

/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_dtcx_qzsj
   函数功能:  更新电信诈骗动态查询表动态查询起止时间
   函数参数:  *fdbop_upd_gab_dxzp_dtcx  电信诈骗下达信息表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_dtcx_qzsj(HXMLTREE lXmlhandle,GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_dtcx set dtcxqssj='%s',dtcxjzsj='%s' where ywsqbh='%s' and rwxh=%d", 
        pst_gab_dxzp_dtcx->dtcxqssj,pst_gab_dxzp_dtcx->dtcxjzsj,
        pst_gab_dxzp_dtcx->ywsqbh, pst_gab_dxzp_dtcx->rwxh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_dtcx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗动态查询表失败,ywsqbh[%s]", 
            pst_gab_dxzp_dtcx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗动态查询表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_dtcx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_jjzf
   函数功能:  查询电信诈骗止付解止表
   函数参数:  *pst_gab_dxzp_jjzf 电信诈骗止付解止表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_jjzf(HXMLTREE lXmlhandle,GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_jjzf where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_JJZF, NUMELE(SD_GAB_DXZP_JJZF), pst_gab_dxzp_jjzf );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗止付解止表失败,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗止付解止表相关记录,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_jjzf
   函数功能:  登记电信诈骗止付解止表
   函数参数:  *pst_gab_dxzp_jjzf  电信诈骗止付解止表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_jjzf(HXMLTREE lXmlhandle,GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_jjzf", SD_GAB_DXZP_JJZF, NUMELE(SD_GAB_DXZP_JJZF), pst_gab_dxzp_jjzf, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗止付解止表失败,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}

/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_jjzf
   函数功能:  更新电信诈骗止付解止表
   函数参数:  *pst_gab_dxzp_jjzf  电信诈骗止付解止表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_jjzf(HXMLTREE lXmlhandle,GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_jjzf set zxjg='%s', respcode='%s', respmsg='%s', zxqssj='%s', zxjssj='%s', fksm='%s', fkjgmc='%s' where ywsqbh='%s'", 
        pst_gab_dxzp_jjzf->zxjg, pst_gab_dxzp_jjzf->respcode, 
        pst_gab_dxzp_jjzf->respmsg,
        pst_gab_dxzp_jjzf->zxqssj,
        pst_gab_dxzp_jjzf->zxjssj,
        pst_gab_dxzp_jjzf->ywsqbh, pst_gab_dxzp_jjzf->rwxh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_jjzf.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗止付解止表失败,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗止付解止表相关记录,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_jymx
   函数功能:  查询电信诈骗交易明细表
   函数参数:  *pst_gab_dxzp_jymx  电信诈骗交易明细表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_jymx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_jymx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_JYMX, NUMELE(SD_GAB_DXZP_JYMX), pst_gab_dxzp_jymx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗交易明细表失败,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗交易明细表相关记录,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_jymx
   函数功能:  登记电信诈骗交易明细表
   函数参数:  *pst_gab_dxzp_jymx  电信诈骗交易明细表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_jymx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_jymx", SD_GAB_DXZP_JYMX, NUMELE(SD_GAB_DXZP_JYMX), pst_gab_dxzp_jymx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗交易明细表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}




/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_qhcx
   函数功能:  查询电信诈骗全户查询表
   函数参数:  *pst_gab_dxzp_qhcx  电信诈骗全户查询表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX *pst_gab_dxzp_qhcx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX, NUMELE(SD_GAB_DXZP_QHCX), pst_gab_dxzp_qhcx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗全户查询表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗全户查询表相关记录,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_qhcx
   函数功能:  登记电信诈骗全户查询表
   函数参数:  *pst_gab_dxzp_qhcx 电信诈骗全户查询表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX *pst_gab_dxzp_qhcx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx", SD_GAB_DXZP_QHCX, NUMELE(SD_GAB_DXZP_QHCX), pst_gab_dxzp_qhcx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗全户查询表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}




/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_zhxx_zhjyxx
   函数功能:  查询电信诈骗 账户信息_账号交易信息
   函数参数:  *pst_gab_dxzp_zhxx_zhjyxx  电信诈骗账户信息_账号交易信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_zhxx_zhjyxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_zhxx_zhjyxx where ywsqbh='%s' and rwxh=%d and zhjyxh='%s'", pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZHXX_ZHJYXX, NUMELE(SD_GAB_DXZP_ZHXX_ZHJYXX), pst_gab_dxzp_zhxx_zhjyxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗账户信息_账号交易信息表失败,ywsqbh[%s],rwxh[%d],zhjyxh[%s]", 
             pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗账户信息_账号交易信息表相关记录,ywsqbh[%s],rwxh[%d],zhjyxh[%s]", 
             pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_zhxx_zhjyxx
   函数功能:  登记电信诈骗账户信息_账号交易信息表
   函数参数:  *pst_gab_dxzp_zhxx_zhjyxx 电信诈骗账户信息_账号交易信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_zhxx_zhjyxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_zhxx_zhjyxx", SD_GAB_DXZP_ZHXX_ZHJYXX, NUMELE(SD_GAB_DXZP_ZHXX_ZHJYXX), pst_gab_dxzp_zhxx_zhjyxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗账户信息_账号交易信息表失败,ywsqbh[%s],rwxh[%d],zhjyxh[%s]", 
             pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}














/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_zhjbxx_zhxx
   函数功能:  查询电信诈骗 账户基本信息_账号信息
   函数参数:  *pst_gab_dxzp_zhjbxx_zhxx  电信诈骗账户基本信息_账号信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_zhjbxx_zhxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_zhjbxx_zhxx where ywsqbh='%s' and rwxh=%d and zhxh='%s'", pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZHJBXX_ZHXX, NUMELE(SD_GAB_DXZP_ZHJBXX_ZHXX), pst_gab_dxzp_zhjbxx_zhxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗账户基本信息_账号信息表失败,ywsqbh[%s],rwxh[%d],zhxh[%s]", 
             pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗账户基本信息_账号信息表相关记录,ywsqbh[%s],rwxh[%d],zhxh[%s]", 
             pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_zhjbxx_zhxx
   函数功能:  登记电信诈骗账户基本信息_账号信息表
   函数参数:  *pst_gab_dxzp_zhjbxx_zhxx 电信诈骗账户基本信息_账号信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_zhjbxx_zhxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_zhjbxx_zhxx", SD_GAB_DXZP_ZHJBXX_ZHXX, NUMELE(SD_GAB_DXZP_ZHJBXX_ZHXX), pst_gab_dxzp_zhjbxx_zhxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗账户基本信息_账号信息表失败,ywsqbh[%s],rwxh[%d],zhxh[%s]", 
             pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}













/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_jymx_zhjbxx
   函数功能:  查询电信诈骗 交易明细_账户基本信息
   函数参数:  *pst_gab_dxzp_jymx_zhjbxx  电信诈骗交易明细_账户基本信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_jymx_zhjbxx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_jymx_zhjbxx where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_JYMX_ZHJBXX, NUMELE(SD_GAB_DXZP_JYMX_ZHJBXX), pst_gab_dxzp_jymx_zhjbxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗交易明细_账户基本信息表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗交易明细_账户基本信息表相关记录,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_jymx_zhjbxx
   函数功能:  登记电信诈骗账户交易明细_账户基本信息表
   函数参数:  *pst_gab_dxzp_jymx_zhjbxx 电信诈骗交易明细_账户基本信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_jymx_zhjbxx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_jymx_zhjbxx", SD_GAB_DXZP_JYMX_ZHJBXX, NUMELE(SD_GAB_DXZP_JYMX_ZHJBXX), pst_gab_dxzp_jymx_zhjbxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗交易明细_账户基本信息表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


















/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_qhcx_sfqzxx
   函数功能:  查询电信诈骗 全户查询_司法强制信息
   函数参数:  *pst_gab_dxzp_qhcx_sfqzxx  电信诈骗全户查询_司法强制信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx_sfqzxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx_sfqzxx where ywsqbh='%s' and rwxh=%d and csxh='%s'", pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX_SFQZXX, NUMELE(SD_GAB_DXZP_QHCX_SFQZXX), pst_gab_dxzp_qhcx_sfqzxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗全户查询_司法强制信息表失败,ywsqbh[%s],rwxh[%d],csxh[%s]", 
             pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗全户查询_司法强制信息表相关记录,ywsqbh[%s],rwxh[%d],csxh[%s]", 
             pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_qhcx_sfqzxx
   函数功能:  登记电信诈骗全户查询_司法强制信息表
   函数参数:  *pst_gab_dxzp_qhcx_sfqzxx 电信诈骗全户查询_司法强制信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx_sfqzxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx_sfqzxx", SD_GAB_DXZP_QHCX_SFQZXX, NUMELE(SD_GAB_DXZP_QHCX_SFQZXX), pst_gab_dxzp_qhcx_sfqzxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗全户查询_司法强制信息表失败,ywsqbh[%s],rwxh[%d],csxh[%s]", 
             pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}











/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_qhcx_zzhxx
   函数功能:  查询电信诈骗 全户查询_子账号信息
   函数参数:  *pst_gab_dxzp_qhcx_zzhxx  电信诈骗全户查询_子账号信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx_zzhxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_ZZHXX *pst_gab_dxzp_qhcx_zzhxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx_zzhxx where ywsqbh='%s' and rwxh=%d and zzhxh='%s'", pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX_ZZHXX, NUMELE(SD_GAB_DXZP_QHCX_ZZHXX), pst_gab_dxzp_qhcx_zzhxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗全户查询_子账号信息表失败,ywsqbh[%s],rwxh[%d],zzhxh[%s]", 
             pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗全户查询_子账号信息表相关记录,ywsqbh[%s],rwxh[%d],zzhxh[%s]", 
             pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_qhcx_zzhxx
   函数功能:  登记电信诈骗全户查询_司法强制信息表
   函数参数:  *pst_gab_dxzp_qhcx_zzhxx 电信诈骗全户查询_司法强制信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx_zzhxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_ZZHXX *pst_gab_dxzp_qhcx_zzhxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx_zzhxx", SD_GAB_DXZP_QHCX_ZZHXX, NUMELE(SD_GAB_DXZP_QHCX_ZZHXX), pst_gab_dxzp_qhcx_zzhxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗全户查询_子账号信息表失败,ywsqbh[%s],rwxh[%d],zzhxh[%s]", 
             pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}



















/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_qhcx_qlxx
   函数功能:  查询电信诈骗 全户查询_权利人信息
   函数参数:  *pst_gab_dxzp_qhcx_qlxx  电信诈骗全户查询_权利人信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx_qlxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx_qlxx where ywsqbh='%s' and rwxh=%d and xh='%s'", pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX_QLXX, NUMELE(SD_GAB_DXZP_QHCX_QLXX), pst_gab_dxzp_qhcx_qlxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗全户查询_权利人信息表失败,ywsqbh[%s],rwxh[%d],xh[%s]", 
             pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗全户查询_权利人信息表相关记录,ywsqbh[%s],rwxh[%d],xh[%s]", 
             pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_qhcx_qlxx
   函数功能:  登记电信诈骗全户查询_权利人信息表
   函数参数:  *pst_gab_dxzp_qhcx_qlxx 电信诈骗全户查询_权利人信息表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx_qlxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx_qlxx", SD_GAB_DXZP_QHCX_QLXX, NUMELE(SD_GAB_DXZP_QHCX_QLXX), pst_gab_dxzp_qhcx_qlxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗全户查询_权利人信息表失败,ywsqbh[%s],rwxh[%d],xh[%s]", 
             pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}





















/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_dtcx_resp
   函数功能:  查询电信诈骗 动态查询响应
   函数参数:  *pst_gab_dxzp_dtcx_resp  电信诈骗动态查询响应表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_dtcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_dtcx_resp where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DTCX_RESP, NUMELE(SD_GAB_DXZP_DTCX_RESP), pst_gab_dxzp_dtcx_resp );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗动态查询响应表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗动态查询响应表相关记录,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_dtcx_resp
   函数功能:  登记电信诈骗动态查询响应
   函数参数:  *pst_gab_dxzp_dtcx_resp 电信诈骗动态查询响应表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_dtcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_dtcx_resp", SD_GAB_DXZP_DTCX_RESP, NUMELE(SD_GAB_DXZP_DTCX_RESP), pst_gab_dxzp_dtcx_resp, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗电信诈骗动态查询响应表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


















/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_dtjc_resp
   函数功能:  查询电信诈骗动态解除响应
   函数参数:  *pst_gab_dxzp_dtjc_resp  电信诈骗动态解除响应表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_dtjc_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_dtjc_resp where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DTJC_RESP, NUMELE(SD_GAB_DXZP_DTJC_RESP), pst_gab_dxzp_dtjc_resp );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗动态解除响应表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗动态解除响应表相关记录,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_dtjc_resp
   函数功能:  登记电信诈骗动态查询响应
   函数参数:  *pst_gab_dxzp_dtjc_resp 电信诈骗动态查询响应表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_dtjc_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_dtjc_resp", SD_GAB_DXZP_DTJC_RESP, NUMELE(SD_GAB_DXZP_DTJC_RESP), pst_gab_dxzp_dtjc_resp, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗动态解除响应表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}












/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_smjfj
   函数功能:  查询电信诈骗扫描件附件表
   函数参数:  *pst_gab_dxzp_smjfj  电信诈骗扫描件附件表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_smjfj(HXMLTREE lXmlhandle,GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_smjfj where ywsqbh='%s' and xh=%d ", pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SMJFJ, NUMELE(SD_GAB_DXZP_SMJFJ), pst_gab_dxzp_smjfj );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗扫描件附件表失败,ywsqbh[%s],xh[%d]", 
             pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗扫描件附件表相关记录,ywsqbh[%s],xh[%d]", 
             pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_smjfj
   函数功能:  登记电信诈骗扫描件附件表
   函数参数:  *pst_gab_dxzp_smjfj 电信诈骗扫描件附件表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_smjfj(HXMLTREE lXmlhandle,GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_smjfj", SD_GAB_DXZP_SMJFJ, NUMELE(SD_GAB_DXZP_SMJFJ), pst_gab_dxzp_smjfj, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗扫描件附件表失败,ywsqbh[%s],xh[%d]", 
             pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}















/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_ztcx_resp
   函数功能:  查询电信诈骗持卡主体查询响应
   函数参数:  *pst_gab_dxzp_ztcx_resp  电信诈骗持卡主体查询响应表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_ztcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_ztcx_resp where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZTCX_RESP, NUMELE(SD_GAB_DXZP_ZTCX_RESP), pst_gab_dxzp_ztcx_resp );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗持卡主体查询响应表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗持卡主体查询响应表相关记录,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_ztcx_resp
   函数功能:  登记电信诈骗持卡主体查询响应
   函数参数:  *pst_gab_dxzp_ztcx_resp 电信诈骗持卡主体查询响应结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_ztcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_ztcx_resp", SD_GAB_DXZP_ZTCX_RESP, NUMELE(SD_GAB_DXZP_ZTCX_RESP), pst_gab_dxzp_ztcx_resp, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗持卡主体查询响应表失败,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   函数名称:  fdbop_qry_dual
   函数功能:  查询业务流水号
   函数参数:  *pst_gab_dual  电信诈骗业务流水号结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_dual(HXMLTREE lXmlhandle,GAB_DXZP_DUAL *pst_gab_dxzp_dual, char *psDualName)
{
    int iRet = -1;
    char sDbType[6+1];
    char sSql[256];
    
    memset(sDbType, 0x00, sizeof(sDbType));
    snprintf(sDbType, sizeof(sDbType), "%s", getenv("DB"));
    if (sDbType[0] == '\0')
    {
        GAB_DXZP_PSTRCOPY(sDbType, "ORA")
    }
    memset(sSql, 0x00, sizeof(sSql));
    if (strncmp(sDbType, "ORA", 3) == 0 )
    {
        snprintf(sSql, sizeof(sSql), "select %s.nextval as ID from dual", psDualName);
    }else if (strncmp(sDbType, "DB2", 3) == 0 )
    {
        snprintf(sSql, sizeof(sSql), "select nextval for %s as ID from SYSIBM.SYSDUMMY1", psDualName);
    }else
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, "暂不支持除ORACLE/DB2以外的数据库");
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("暂不支持除ORACLE/DB2以外的数据库"),fpub_GetCompname(lXmlhandle));
    }
    LOG(LM_DEBUG, Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DUAL, NUMELE(SD_GAB_DXZP_DUAL), pst_gab_dxzp_dual );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗业务流水号失败"),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗业务流水号表相关记录"),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}













/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_sbxx_plzt
   函数功能:  电信诈骗上报信息_批量状态表
   函数参数:  *pst_gab_dxzp_sbxx_plzt  电信诈骗上报信息_批量状态表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_sbxx_plzt(HXMLTREE lXmlhandle,GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sbxx_plzt where sbpch='%s' and sbpcxh=%d ", pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SBXX_PLZT, NUMELE(SD_GAB_DXZP_SBXX_PLZT), pst_gab_dxzp_sbxx_plzt );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗上报信息_批量状态表失败,sbpch[%s],sbpcxh[%d]", 
             pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗上报信息_批量状态表相关记录,sbpch[%s],sbpcxh[%d]", 
             pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_sbxx_plzt
   函数功能:  登记电信诈骗上报信息_批量状态表
   函数参数:  *pst_gab_dxzp_sbxx_plzt 电信诈骗上报信息_批量状态表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_sbxx_plzt(HXMLTREE lXmlhandle,GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sbxx_plzt", SD_GAB_DXZP_SBXX_PLZT, NUMELE(SD_GAB_DXZP_SBXX_PLZT), pst_gab_dxzp_sbxx_plzt, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗上报信息_批量状态表失败,sbpch[%s],sbpcxh[%d]", 
             pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}





/*****************************************************
   函数名称:  fdbop_qry_gab_dxzp_hhmd
   函数功能:  电信诈骗黑灰名单表
   函数参数:  *pst_gab_dxzp_hhmd  电信诈骗黑灰名单表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_qry_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_hhmd where mdjz='%s'", pst_gab_dxzp_hhmd->mdjz);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_HHMD, NUMELE(SD_GAB_DXZP_HHMD), pst_gab_dxzp_hhmd );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    LOG(LM_STD,Fmtmsg("sSql=[%s]",sSql),"DEBUG");
    return iRet;
}

/*****************************************************
   函数名称:  fdbop_ins_gab_dxzp_hhmd
   函数功能:  登记电信诈骗黑灰名单表
   函数参数:  *pst_gab_dxzp_hhmd 电信诈骗黑灰名单表结构体

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_hhmd", SD_GAB_DXZP_HHMD, NUMELE(SD_GAB_DXZP_HHMD), pst_gab_dxzp_hhmd, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记电信诈骗黑灰名单表失败,mdjz[%s]", 
            pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}






/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_hhmd
   函数功能:  更新电信诈骗黑灰名单表
   函数参数:  *pst_gab_dxzp_hhmd  电信诈骗黑灰名单表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_hhmd set mdlx='%s',mdly='%s',\
        ajlx='%s',xm='%s',mdjb='%s',gxrq='%s',gxsj='%s' where mdjz='%s'", 
        pst_gab_dxzp_hhmd->mdlx, pst_gab_dxzp_hhmd->mdly, pst_gab_dxzp_hhmd->ajlx,
        pst_gab_dxzp_hhmd->xm, pst_gab_dxzp_hhmd->mdjb, pst_gab_dxzp_hhmd->gxrq, pst_gab_dxzp_hhmd->gxsj,pst_gab_dxzp_hhmd->mdjz);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_hhmd.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗黑灰名单表失败,mdjz[%s]", 
           pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗黑灰名单表相关记录,mdjz[%s]", 
            pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}


/*****************************************************
   函数名称:  fdbop_del_gab_dxzp_hhmd
   函数功能:  删除电信诈骗黑灰名单表
   函数参数:  *pst_gab_dxzp_hhmd  电信诈骗黑灰名单表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_del_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "delete gab_dxzp_hhmd  where mdjz='%s'",pst_gab_dxzp_hhmd->mdjz);
   
    LOG(LM_STD, Fmtmsg("fdbop_del_gab_dxzp_hhmd.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("删除电信诈骗黑灰名单表失败,mdjz[%s]", 
           pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗黑灰名单表相关记录,mdjz[%s]", 
            pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}



/*****************************************************
   函数名称:  fdbop_upd_gab_dxzp_xdxx_qdxx
   函数功能:  更新电信诈骗渠道信息表
   函数参数:  *pst_gab_dxzp_xdxx  电信诈骗下达信息表结构体

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_qdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set jbjg='%s', jbgy='%s' where ywsqbh='%s'", 
        pst_gab_dxzp_xdxx->jbjg, pst_gab_dxzp_xdxx->jbgy, 
        pst_gab_dxzp_xdxx->ywsqbh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新电信诈骗下达信息表失败,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到查询电信诈骗下达信息表相关记录,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
