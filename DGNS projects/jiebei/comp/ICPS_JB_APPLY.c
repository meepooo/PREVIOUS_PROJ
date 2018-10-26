/********************************************************************
 版权所有:恒生电子股份有限公司（杭州）
 项目名称:
 版    本:V2.1.0.1
 操作系统:
 文件名称:ICPS_JB_APPLY.c
 文件描述:东莞农商借呗授信模块组件
 程 序 员:
 发布日期:2015-9-29
 程 序 员:
 修改日期:
 修改说明:
 *********************************************************************/
#include "../incl/ICPS_JB_HEAD.h"


/*****************************************************
   函数名称:  int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, const char* szPath, const char* nodeAttr, char* szValue, unsigned int size, int iFlag)
   函数功能:  获取XML节点值,若字符串节点为空则赋'-';若金额数字型节点为空则赋0
   函数参数:  lXmlhandle  XML树操作句柄
              Path  节点路径
              nodeAttr 节点属性 0-字符串, 1-金额，数字等
              szValue 节点值存放字符串
              size  存放值的空间大小
              iFlag 节点是否必须存在 ICPS_JB_XML_NULL ICPS_JB_XML_NOTNULL
             
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
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_XMLOP, Fmtmsg(MSG_ICPS_JB_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]的目标变量为NULL!", MSG_ICPS_JB_XMLOP, psPath),"")
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
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_XMLOP, Fmtmsg(MSG_ICPS_JB_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]不存在[%d]!", MSG_ICPS_JB_XMLOP, psPath, iRet),"") 
        return -2;
    }
    
    if( (psValue[0] == '\0') && (XML_NODE_NOTNULL == iFlag) )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_XMLOP, Fmtmsg(MSG_ICPS_JB_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!节点[%s]值为空!", MSG_ICPS_JB_XMLOP, psPath),"")
        return -2;
    }    
    trim(psValue);       
    return strlen(psValue);
}

/*****************************************************
   函数名称:  fdbop_ins_icps_jb_applyinfo
   函数功能:  登记授信申请表
   函数参数:  *pst_icps_jb_applyinfo   授信请求单信息表

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_icps_jb_applyinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_APPLYINFO *pst_icps_jb_applyinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_applyinfo", SD_ICPS_JB_APPLYINFO, NUMELE(SD_ICPS_JB_APPLYINFO), pst_icps_jb_applyinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记授信申请单表失败失败,reqmsgid[%s]", 
            pst_icps_jb_applyinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   函数名称:  fdbop_ins_icps_jb_zminfo
   函数功能:  登记申请人芝麻信息
   函数参数:  *pst_icps_jb_zminfo   申请人芝麻信息

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_icps_jb_zminfo(HXMLTREE lXmlhandle,ST_ICPS_JB_ZMINFO *pst_icps_jb_zminfo,char *sMap)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));

    iRet = DBInsertBLOB("icps_jb_zminfo",SD_ICPS_JB_ZMINFO, NUMELE(SD_ICPS_JB_ZMINFO), pst_icps_jb_zminfo, sErrmsg,sMap, strlen(sMap));

    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记申请人芝麻信息失败,reqmsgid[%s]", 
            pst_icps_jb_zminfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   函数名称:  fdbop_ins_icps_jb_resultinfo
   函数功能:  登记终审确认请求单信息
   函数参数:  *pst_icps_jb_resultinfo   终审确认请求单信息

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_icps_jb_resultinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_RESULTINFO *pst_icps_jb_resultinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_resultinfo", SD_ICPS_JB_RESULTINFO, NUMELE(SD_ICPS_JB_RESULTINFO), pst_icps_jb_resultinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记终审确认请求单信息失败,reqmsgid[%s]", 
            pst_icps_jb_resultinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   函数名称:  fdbop_ins_icps_jb_extinfo
   函数功能:  登记终审反馈银行信息
   函数参数:  *pst_icps_jb_extinfo   终审反馈银行信息

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_icps_jb_extinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_EXTINFO *pst_icps_jb_extinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_extinfo", SD_ICPS_JB_EXTINFO, NUMELE(SD_ICPS_JB_EXTINFO), pst_icps_jb_extinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记终审反馈银行信息失败,reqmsgid[%s]", 
            pst_icps_jb_extinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   函数名称:  fdbop_ins_icps_jb_bankinfo
   函数功能:  登记申请人银行数据
   函数参数:  *pst_icps_jb_bankinfo  申请人银行数据

   函数返回:  0   :成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_ins_icps_jb_bankinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_BANKINFO *pst_icps_jb_bankinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_bankinfo", SD_ICPS_JB_BANKINFO, NUMELE(SD_ICPS_JB_BANKINFO), pst_icps_jb_bankinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("登记申请人银行数据失败,reqmsgid[%s]", 
            pst_icps_jb_bankinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   函数名称:  fdbop_upd_icps_jb_applyinfo_702513
   函数功能:  更新蚂蚁借呗-授信请求单信息表---行内初审
   函数参数:  *pst_icps_jb_applyinfo  蚂蚁借呗-授信请求单信息表

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_icps_jb_applyinfo_702513(HXMLTREE lXmlhandle,ST_ICPS_JB_APPLYINFO *pst_icps_jb_applyinfo)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_applyinfo set applystat='%s',reqdate='%s',reqtime1='%s',isadmit='%s', \
            creditamt='%s',creditrate='%s',refusecode='%s',refusemsg='%s'  \
            where reqmsgid='%s' and applyno='%s' ", 
        pst_icps_jb_applyinfo->applystat,pst_icps_jb_applyinfo->reqdate,pst_icps_jb_applyinfo->reqtime1,
        pst_icps_jb_applyinfo->isadmit, pst_icps_jb_applyinfo->creditamt,
        pst_icps_jb_applyinfo->creditrate,pst_icps_jb_applyinfo->refusecode,pst_icps_jb_applyinfo->refusemsg,
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_applyinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "库表相关操作失败");
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新授信请求单信息表--行内初审失败,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "未找到相关记录");
        LOGRET( ICPS_JB_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到授信请求单信息表相关记录,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   函数名称:  fdbop_upd_icps_jb_applyinfo_702514
   函数功能:  更新蚂蚁借呗-授信请求单信息表---蚂蚁初审返回
   函数参数:  *pst_icps_jb_applyinfo  蚂蚁借呗-授信请求单信息表

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_icps_jb_applyinfo_702514(HXMLTREE lXmlhandle,ST_ICPS_JB_APPLYINFO *pst_icps_jb_applyinfo)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_applyinfo set respcode='%s',respmsg='%s',resultstat='%s', \
            retry='%s',respdate='%s',resptime='%s' where reqmsgid='%s' and applyno='%s' ", 
        pst_icps_jb_applyinfo->respcode,pst_icps_jb_applyinfo->respmsg,pst_icps_jb_applyinfo->resultstat,pst_icps_jb_applyinfo->retry,
        pst_icps_jb_applyinfo->respdate,pst_icps_jb_applyinfo->resptime,pst_icps_jb_applyinfo->reqmsgid,
        pst_icps_jb_applyinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_applyinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "库表相关操作失败");
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("更新授信请求单信息表失败,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "未找到相关记录");
        LOGRET( ICPS_JB_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("未找到授信请求单信息表相关记录,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   函数名称:  fdbop_upd_icps_jb_resultinfo
   函数功能:  更新蚂蚁借呗-终审确认请求单信息表
   函数参数:  *pst_icps_jb_resultinfo  蚂蚁借呗-终审确认请求单信息表

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_icps_jb_resultinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_RESULTINFO *pst_icps_jb_resultinfo)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_resultinfo set resultcode='%s',resultmsg='%s',isadmit='%s',admitmsg='%s' where applyno='%s' ", 
        pst_icps_jb_resultinfo->resultcode,pst_icps_jb_resultinfo->resultmsg,pst_icps_jb_resultinfo->isadmit,
        pst_icps_jb_resultinfo->admitmsg,pst_icps_jb_resultinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_resultinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "库表相关操作失败");
        LOGRET( -12, LM_STD, Fmtmsg("更新终审确认请求单信息表失败,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "未找到相关记录");
        LOGRET( 1403, LM_STD, Fmtmsg("未找到终审人确认请求单信息表相关记录,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_upd_icps_jb_bankinfo
   函数功能:  更新蚂蚁借呗-银行初审数据
   函数参数:  *pst_icps_jb_bankinfo  蚂蚁借呗-银行初审数据

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_upd_icps_jb_bankinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_RESULTINFO *pst_icps_jb_resultinfo, char *Condition)
{
    int iRet = -1;
    char sSql[512];
    char sErrmsg[512];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_resultinfo set resultcode='%s',resultmsg='%s',isadmit='%s',admitmsg='%s' where reqmsgid='%s' and applyno='%s' ", 
        pst_icps_jb_resultinfo->resultcode,pst_icps_jb_resultinfo->resultmsg,pst_icps_jb_resultinfo->isadmit,
        pst_icps_jb_resultinfo->admitmsg,pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_resultinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "库表相关操作失败");
        LOGRET( -12, LM_STD, Fmtmsg("更新终审确认请求单信息表失败,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "未找到相关记录");
        LOGRET( 1403, LM_STD, Fmtmsg("未找到终审人确认请求单信息表相关记录,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   函数名称:  fdbop_sel_icps_jb_idcode2addr
   函数功能:  查询蚂蚁借呗-身份证地区码转换数据
   函数参数:  *pst_icps_jb_idcode2addr 身份证地区码转换结构

   函数返回:  0   :更新成功
              1   :未找到
              其他:失败

   函数说明:  

   修改说明:  
*****************************************************/
int fdbop_sel_icps_jb_idcode2addr(HXMLTREE lXmlhandle,ST_ICPS_JB_IDCODE2ADDR *pst_icps_jb_idcode2addr)
{
    int iRet = -1;
    char sSql[512];
    char sErrmsg[512];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    
    snprintf(sSql, sizeof(sSql), "select shrtnm,fullnm,upcode,lvl from icps_jb_idcode2addr where id6code='%s' ", pst_icps_jb_idcode2addr->id6code);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_idcode2addr.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DBSelectToMultiVar(sErrmsg, sSql, pst_icps_jb_idcode2addr->shrtnm,pst_icps_jb_idcode2addr->fullnm,pst_icps_jb_idcode2addr->upcode,
            pst_icps_jb_idcode2addr->lvl);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "库表相关操作失败");
        LOGRET( -12, LM_STD, Fmtmsg("查询蚂蚁借呗身份证地区码转换数据失败,id6code[%s]", pst_icps_jb_idcode2addr->id6code),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "未找到相关记录");
        LOGRET( 1403, LM_STD, Fmtmsg("未找到身份证地区码转换表相关记录,id6code[%s]", pst_icps_jb_idcode2addr->id6code),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/****************************************************************************** 
函数名称∶DBInsertBLOB 
函数功能∶根据条件用一个结构数据更新表 
输入参数∶tb -- 表名 
desc_arr -- 结构描述信息 
desc_num -- 结构描述长度 
pstru -- 数据指针 
sblob -- BLOB字段内容 
int ilen -- BLOB长度 

输出参数∶errmsg -- 错误信息 
返 回 值∶>= 0 -- 成功 影响的行数 
其他 -- 失败 

说明BLOB字段表结构可以定义成int型 
******************************************************************************/ 
int DBInsertBLOB(const char* tb, FLD_DESC desc_arr[], int desc_num, void *pstru, char *errmsg, char *sblob, int ilen) 
{ 
    int i, n; 
    int rowcount; 
    char *stmt, *p=NULL; 
    CURSOR cur; 
    FLD_DESC *pdesc; 
    
    if (desc_num <= 0 || pstru == NULL) 
        return 0; 
    
    stmt = (char *)calloc(1, (MAX_SYM_LEN + 3) * desc_num * 2 + strlen(tb) + 100); 
    if (stmt == NULL) 
    { 
        if (errmsg) 
        sprintf(errmsg, "内存分配错误"); 
        return -1; 
    }
    memset( &pdesc, 0x00, sizeof(pdesc));
    pdesc = desc_arr; 
    
    n = sprintf(stmt, "insert into %s ( %s ", tb, pdesc->name); 
    pdesc++; 

    for (i = 1, p = stmt + n; i < desc_num-1; i++, pdesc++) 
    { 
        n = sprintf(p, ", %s", pdesc->name); 
        p += n; 
    }

    if (ilen <= 0 )
    { 
        strcat(p, ") values ("); 
        p = p+10;
    }
    else
    {
        n = sprintf(p, ", %s", pdesc->name);
        p += n;
        strcat(p, ") values (");
        p = p+10;
    }
    memset( &pdesc, 0x00, sizeof(pdesc));
    pdesc = desc_arr;
    n = sprintf(p, ":%s ", pdesc->name);
    pdesc++; 

    for (i = 1, p += n; i < desc_num-1; i++, pdesc++) 
    { 
        n = sprintf(p, ", :%s", pdesc->name); 
        p += n; 
    }

    if (ilen <= 0 )
    { 
        strcat(p, ")"); 
    }
    else
    {
        n = sprintf(p, ", :%s", pdesc->name);
        strcat(p, ")");
    }

    
    cur = DCIDeclareCursor(stmt, DCI_STMT_LOCATOR); 
    if (cur == INVALID_CURSOR) 
    { 
        if (errmsg) 
        strcpy(errmsg, DCILastError()); 
        free(stmt); 
        return -2; 
    } 
    free(stmt); 
    
    for (i = 0, pdesc = desc_arr; i < desc_num-1; i++, pdesc++) 
    { 
        int datatype; 
        int datalen; 
        double dv; 
        char dvbuf[64]; 
    
        char *pval = (char *)pstru + pdesc->offset; 
        switch (pdesc->type) 
        { 
            case TT_CHAR: 
            case TT_STRING: 
            datatype = DCIT_CHAR; 
            #ifdef DB_MYSQL 
                datalen = MAX(strlen(pval), pdesc->extlen); 
            #else 
                datalen = MAX(strlen(pval)+1, pdesc->extlen); 
            #endif 
            break; 
        
            case TT_SHORT: 
            datatype = DCIT_INTEGER; 
            datalen = sizeof(short); 
            break; 
            
            case TT_LONG: 
            if ( sizeof(long) == sizeof(int )) 
            { 
                datatype = DCIT_INTEGER; 
                datalen = sizeof(int); 
                /* 兼容32位下大数的插入 */ 
            if(pdesc->maxlen == 8) 
            { 
                datatype = DCIT_LONG; 
                datalen = sizeof(long long); 
            } 
            } 
            else 
            { 
                datatype = DCIT_LONG; 
                datalen = sizeof(long); 
                /* 对64位下int型数据处理 */ 
                if(pdesc->maxlen == 4) 
                { 
                    datatype = DCIT_INTEGER; 
                    datalen = sizeof(int); 
                } 
            } 
            break; 
            
            case TT_DOUBLE: 
                datatype = DCIT_DOUBLE; 
                datalen = sizeof(double); 
                if (pdesc->extlen > 0) 
                { 
                snprintf(dvbuf, sizeof(dvbuf), "%.*lf", pdesc->extlen, *(double *)pval); 
                dv = atof(dvbuf); 
                memcpy(pval, &dv, sizeof(double)); 
                } 
                break; 
            
            default: 
                if (errmsg) 
                strcpy(errmsg, "未知的字段类型"); 
                DCIFreeCursor(cur); 
                return -3; 
        } 
    
        if (DCIBindPara(cur, i, pval, datalen, datatype) == -1) 
        { 
            if (errmsg) 
            strcpy(errmsg, DCILastError()); 
            PRINTF("pos = %d\n", i); 
            DCIFreeCursor(cur); 
            return -4; 
        } 
    } 
    /*绑定BLOB字段*/ 
    if (ilen > 0)
    {
        if (DCIBindPara(cur, i, sblob, ilen, DCIT_BLOB) != 0) 
        { 
            if (errmsg) 
            strcpy(errmsg, DCILastError()); 
            PRINTF("pos = %d\n", i); 
            DCIFreeCursor(cur); 
            return -5; 
        }
    } 

    rowcount = DCIExecute(cur); 
    if (rowcount == -1) 
    { 
        if (errmsg) 
        strcpy(errmsg, DCILastError()); 
        DCIFreeCursor(cur); 
        return -6; 
    } 
    
    DCIFreeCursor(cur); 
    return rowcount; 
} 
/************************************************************************
动态组件函数定义
组件函数名称:ICPS_JB_INSERT_REQ
组件名称:ICPS_JB_INSERT_REQ
组件功能: 蚂蚁借呗接入记录登记
组件参数列表：
    序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
    结果状态码          结果说明
    -9999               缺省
    0                   成功
************************************************************************/
IRESULT ICPS_JB_INSERT_REQ(HXMLTREE lXmlhandle)
{
    int    iParas;    
    int    iRet=0;    
    int    iRet1 = 0;
    int    iLen = 0;
    int    iNum=0;
    int    iNum1=0;
    int    i=0;
    char   trace_code[10]={0};
    char   stmp[512]={0};
    char   stmp1[2+1]={0} ;
    char   ptrq[8+1]={0};
    char   ptlsh[10+1]={0};
    char   sSql[512]={0};
    char   sMapbuf[10240+1]={0};
    CURSOR cur;
    
    
    ST_ICPS_JB_APPLYINFO applyinfo; /*授信请求信息 */
    ST_ICPS_JB_ZMINFO zminfo; /*授信请求信息--芝麻信息 */
    ST_ICPS_JB_EXTINFO extinfo; /*终审结果信息 */
    ST_ICPS_JB_RESULTINFO resultinfo;  /*终审请求信息 */
    ST_ICPS_JB_BANKINFO bankinfo;  /*银行返回数据 */
    ST_ICPS_JB_IDCODE2ADDR code2addr; /*身份证地区码转换 add 20171128 yj */
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("蚂蚁借呗登记入库处理组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "")

    /*初始化*/                               
    memset(&applyinfo, 0x00, sizeof(applyinfo));
    memset(&zminfo, 0x00, sizeof(zminfo));
    memset(&extinfo, 0x00, sizeof(extinfo));
    memset(&resultinfo, 0x00, sizeof(resultinfo));
    memset(&code2addr, 0x00, sizeof(code2addr)); /* add 20171128 yj */
    
    /*获取请求信息 */
    memset(stmp,0x00,sizeof(stmp));
    memset(trace_code,0x00,sizeof(trace_code));
    COMP_SOFTGETXML("/pub/jydm", trace_code); /*交易代码 */
     /*平台日期+平台流水号*/
    memset(ptrq,0x00,sizeof(ptrq));
    memset(ptlsh,0x00,sizeof(ptlsh));
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTRQ,ptrq);
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTLSH,ptlsh); 
    DCIBegin();   /**开始事务**/
    if (0 == strcmp(trace_code,"702511"))  /*借呗发送初审申请请求登记*/
    {
        ICPS_JB_PSTRCOPY(applyinfo.ptrq,ptrq);
        ICPS_JB_PSTRCOPY(applyinfo.ptlsh,ptlsh);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_VERSION,applyinfo.version,"版本号");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_APPID,applyinfo.appid,"系统标识");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_FUNCTION,applyinfo.function,"交易编码");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_REQTIMEZONE,applyinfo.reqtimezone,"发送方所在时区");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_REQTIME,applyinfo.reqtime,"报文发起时间");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_REQMSGID,applyinfo.reqmsgid,"请求报文唯一标示");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_SIGNTYPE,applyinfo.signtype,"签名算法类型");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_INPUTCHARSET,applyinfo.inputcharset,"报文字符编码");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_RESERVE,applyinfo.reserve,"预留域");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_APPLYNO,applyinfo.applyno,"申请单号");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CERTTYPE,applyinfo.certtype,"证件类型");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CERTNO,applyinfo.certno,"证件号码");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CERTVALIDENDDATE,applyinfo.certvalidenddate,"证件有效期");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_NAME,applyinfo.name,"姓名");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CUSTOMERNO,applyinfo.customerno,"客户编号");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CUSTOMERNO,applyinfo.creditno,"授信编号");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_MOBILENO,applyinfo.mobileno,"手机号");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_OCCUPATION,applyinfo.occupation,"职业");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_ADDRESS,applyinfo.address,"详细地址"); /* sos mod 20171130 */
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CITY,applyinfo.city,"城市");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_PROV,applyinfo.prov,"省份");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_AREA,applyinfo.area,"地区");
		ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_REQTRACENO,applyinfo.reqtraceno,"向小微平台请求流水号");
        /**** add bgn 20171128 yj ****/
		LOG(LM_STD, Fmtmsg("zhandd", fpub_GetCompname(lXmlhandle)), "")
        if(strlen(applyinfo.address) == 0)
        {
            strncpy(code2addr.id6code,applyinfo.certno,6);
            iRet1 = fdbop_sel_icps_jb_idcode2addr(lXmlhandle,&code2addr);
            strcpy(applyinfo.address, code2addr.fullnm);
        }
        /**** add end 20171128 yj ****/
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_ZMAUTHFLAG,applyinfo.zmauthflag,"芝麻授权成功表示");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_HASJBADMIT,applyinfo.hasjbadmit,"是否之前就有借呗额度");
        ICPS_JB_PSTRCOPY(applyinfo.applystat,"9");
        ICPS_JB_PSTRCOPY(applyinfo.resultstat,"9");
        ICPS_JB_PSTRCOPY(applyinfo.retry,"Y");
        ICPS_JB_PSTRCOPY(applyinfo.reqcode,"00000");
        ICPS_JB_PSTRCOPY(applyinfo.reqmsg,"接收成功");
        
        
        /****************登记库表 icps_jb_applyinfo  ********************/ 
        memset(sSql, 0x00, sizeof(sSql));
        snprintf(sSql, sizeof(sSql), "select count(*) from icps_jb_applyinfo where  applyno='%s'",applyinfo.applyno);
        LOG(LM_STD,Fmtmsg("查询是否需要幂等返回->sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));

        if ((iRet1 =sql_CountSql(sSql)) < 1)
        {    
    
            LOG(LM_STD, Fmtmsg("开始登记蚂蚁借呗-授信请求单表【icps_jb_applyinfo】！[%s]", fpub_GetCompname(lXmlhandle)), "");
            iRet1 = fdbop_ins_icps_jb_applyinfo(lXmlhandle,&applyinfo);
            if(iRet1<0)
            {
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return -1;
            }
            LOG(LM_STD, Fmtmsg("登记蚂蚁借呗-授信请求单表【icps_jb_applyinfo】成功！[%s]", fpub_GetCompname(lXmlhandle)), "");
                
            /*判断是否有芝麻信息*/
            if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_ZM_INFO)) > 0)
            {
                ICPS_JB_PSTRCOPY(zminfo.ptrq,ptrq);
                ICPS_JB_PSTRCOPY(zminfo.ptlsh,ptlsh);
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,zminfo.reqmsgid,"请求报文唯一标示");
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,zminfo.applyno,"申请单号");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_COMPANY_NAME,zminfo.company_name,"所在公司");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_OCCUPATION,zminfo.occupation,"职业类型");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_HAVE_CAR_FLAG,zminfo.have_car_flag,"是否有车");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_HAVE_FANG_FLAG,zminfo.have_fang_flag,"是否有房");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_AUTH_FIN_LAST_1M_CNT,zminfo.auth_fin_last_1mcnt,"最近一个月主动查询金融机构数");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_AUTH_FIN_LAST_3M_CNT,zminfo.auth_fin_last_3mcnt,"最近三个月主动查询金融机构数");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_AUTH_FIN_LAST_6M_CNT,zminfo.auth_fin_last_6mcnt,"最近六个月主动查询金融机构数");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_OVD_ORDER_CNT_6M,zminfo.ovd_order_cnt_6m,"最近六个月逾期总笔数");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_OVD_ORDER_AMT_6M,zminfo.ovd_order_amt_6m,"最近六个月逾期总金额");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_MOBILE_FIXED_DAYS,zminfo.mobile_fixed_days,"手机号稳定天数");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_ADR_STABILITY_DAYS,zminfo.adr_stability_days,"地址稳定天数");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_LAST_6M_AVG_ASSET_TOTAL,zminfo.last6mavgassettotal,"最近六个月流动资产日均值");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_TOT_PAY_AMT_6M,zminfo.tot_pay_amt_6m,"最近六个月支付总金额");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_XFDC_INDEX,zminfo.xfdc_index,"消费档次");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_POSITIVE_BIZ_CNT_1Y,zminfo.positive_biz_cnt_1y,"最近一年履约场景数");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_CREDITSCORE_SUCCESS,zminfo.creditscore_success,"芝麻信用评分-成功标志");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_CREDITSCORE_BIZ_NO,zminfo.creditscore_biz_no,"芝麻信用评分-bizno");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_CREDITSCORE_ZM_SCORE,zminfo.creditscore_zmscore,"芝麻信用评分-芝麻分");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_WATCHLISTII_SUCCESS,zminfo.watchlistii_success,"芝麻行业关注名单-成功标志");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_WATCHLISTII_BIZ_NO,zminfo.watchlistii_biz_no,"芝麻行业关注名单-bizno");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_WATCHLISTII_IS_MATCHED,zminfo.watchlistii_matched,"芝麻行业关注名单-是否关注");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_IVS_SUCCESS,zminfo.ivs_success,"芝麻欺诈关注清单-成功标志");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_IVS_HIT,zminfo.ivs_hit,"芝麻欺诈关注清单-是否击中");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_IVS_BIZ_NO,zminfo.ivs_biz_no,"芝麻欺诈关注清单-bizno");
                
                if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_PBOC_INFO)) > 0)
                {
                    memset(sMapbuf,0x00,sizeof(sMapbuf));
                    if((iLen=xml_ExportXMLString(lXmlhandle,sMapbuf,sizeof(sMapbuf),XMLNM_ICPS_JB_PBOC_INFO,1))==FAIL)
                    {
                        fpub_SetMsg(lXmlhandle,MID_ICPS_JB_XMLOP,Fmtmsg(MSG_ICPS_JB_XMLOP,iLen,GETXMLERR));
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        DCIFreeCursor(cur);
                        return COMPRET_FAIL;
                    }
                    LOG(LM_DEBUG,Fmtmsg("export len[%d]", iLen ),"INFO")
                }
                        
                LOG(LM_STD, Fmtmsg("开始登记蚂蚁借呗-申请人芝麻信息表【icps_jb_zminfo】！[%s]", fpub_GetCompname(lXmlhandle)), "");
                /****************登记库表 icps_jb_zminfo  ********************/ 
                iRet1 = fdbop_ins_icps_jb_zminfo(lXmlhandle,&zminfo,sMapbuf);
                if(iRet1<0)
                {
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback;
                    return -1;
                }
                LOG(LM_STD, Fmtmsg("登记蚂蚁借呗-申请人芝麻信息表【icps_jb_zminfo】成功！[%s]", fpub_GetCompname(lXmlhandle)), "");

            }
            /*判断是否有扩展信息---请求报文的扩展信息已经并入到icps_jb_applyinfo表
            if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_EXT_INFO)) > 0)
            {
            }
            *******************/
        }
        else
        {
            LOG(LM_STD, Fmtmsg("【icps_jb_applyinfo】数据已存在，无需重复入库！[%s]", fpub_GetCompname(lXmlhandle)), "");
			/*更新小微平台授信请求流水号*/
        }
    }
    else if (0 == strcmp(trace_code,"702515"))  /*借呗发送终审确认*/
    {
        ICPS_JB_PSTRCOPY(resultinfo.ptrq,ptrq);
        ICPS_JB_PSTRCOPY(resultinfo.ptlsh,ptlsh);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_VERSION,resultinfo.version,"版本号");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_APPID,resultinfo.appid,"系统标识");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_FUNCTION,resultinfo.function,"交易编码");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_REQTIMEZONE,resultinfo.reqtimezone,"发送方所在时区");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_REQTIME,resultinfo.reqtime,"报文发起时间");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_REQMSGID,resultinfo.reqmsgid,"请求报文唯一标示");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_SIGNTYPE,resultinfo.signtype,"签名算法类型");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_INPUTCHARSET,resultinfo.inputcharset,"报文字符编码");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_RESERVE,resultinfo.reserve,"预留域");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_APPLYNO,resultinfo.applyno,"申请单号");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_CERTTYPE,resultinfo.certtype,"证件类型");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_CERTNO,resultinfo.certno,"证件号码");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_NAME,resultinfo.name,"姓名");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_PLATFORMACCESS,resultinfo.platformaccess,"本次审批结果，是否通过");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_PLATFORMREFUSEREASON,resultinfo.platformrefusereaso,"本次审批结果，是否通过");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_PLATFORMADMIT,resultinfo.platformadmit,"如果通过，则输出审批额度");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_PLATFORMRATE,resultinfo.platformrate,"如果通过，则输出审批基础利率");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_RISKRATING,resultinfo.riskrating,"风险评级");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_SOLVENCYRATINGS,resultinfo.solvencyratings,"偿债能力评级");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_CHANGERESULTREASON,resultinfo.changeresultreason,"额度、定价变更原因");
        /****************登记库表 icps_jb_resultinfo  ********************/ 
        memset(sSql, 0x00, sizeof(sSql));
        snprintf(sSql, sizeof(sSql), "select * from icps_jb_resultinfo where applyno='%s'",resultinfo.applyno);
        LOG(LM_STD,Fmtmsg("查询是否需要幂等返回->sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));

        if ((iRet1 =sql_CountSql(sSql)) < 1)
        {    
            LOG(LM_STD, Fmtmsg("开始登记蚂蚁借呗-终审确认请求单表【icps_jb_resultinfo】！[%s]", fpub_GetCompname(lXmlhandle)), "");
            iRet1 = fdbop_ins_icps_jb_resultinfo(lXmlhandle,&resultinfo);
            if(iRet1<0)
            {
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return -1;
            }
            LOG(LM_STD, Fmtmsg("登记蚂蚁借呗-终审确认请求单表【icps_jb_resultinfo】成功！[%s]", fpub_GetCompname(lXmlhandle)), "");
            /*判断是否有审批结果扩展信息*/
            if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_EXT_INFO)) > 0)
            {
                ICPS_JB_PSTRCOPY(extinfo.ptrq,ptrq);
                ICPS_JB_PSTRCOPY(extinfo.ptlsh,ptlsh);
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,extinfo.reqmsgid,"请求报文唯一标示");
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,extinfo.applyno,"申请单号");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_ISPLATADM,extinfo.isplatadm,"平台贷是否准入");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_PLATUNADMREASON,extinfo.platunadmreason,"平台贷不准入原因");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_PLATCREDITAMT,extinfo.platcreditamt,"平台贷授信额度");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_ISJBPRECREDITCUST,extinfo.isjbprecreditcust,"是否借呗预授信客户");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_LOANRATE,extinfo.loanrate,"基础利率");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_PERIOD,extinfo.period,"产品期限");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_REPAYTYPE,extinfo.repaytype,"还款方式");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_RISKLEVEL,extinfo.risklevel,"风险评级");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_REPAYABILITYLVL,extinfo.repayabilitylvl,"偿债能力评级");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_CHANGEREASON,extinfo.changereason,"各种原因结合");
                /****************登记库表 icps_jb_extinfo  ********************/ 
                LOG(LM_STD, Fmtmsg("开始登记蚂蚁借呗-终审银行结果信息表【icps_jb_extinfo】！[%s]", fpub_GetCompname(lXmlhandle)), "");
                iRet1 = fdbop_ins_icps_jb_extinfo(lXmlhandle,&extinfo);
                if(iRet1<0)
                {
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback;
                    return -1;
                }
                LOG(LM_STD, Fmtmsg("登记蚂蚁借呗-终审银行结果信息表【icps_jb_extinfo】成功！[%s]", fpub_GetCompname(lXmlhandle)), "");
            }
        }
        else
        {
            LOG(LM_STD, Fmtmsg("【icps_jb_resultinfo】数据已存在，无需重复入库！[%s]", fpub_GetCompname(lXmlhandle)), "");
        }

    }

    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

    return 0;

}
/************************************************************************
动态组件函数定义
组件函数名称:ICPS_JB_UPDATE_REQ
组件名称:ICPS_JB_UPDATE_REQ
组件功能: 蚂蚁借呗接入记录更新
组件参数列表：
    序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
    结果状态码          结果说明
    -9999               缺省
    0                   成功

************************************************************************/
IRESULT ICPS_JB_UPDATE_REQ(HXMLTREE lXmlhandle)
{
    int    iParas;    
    int    iRet=0;    
    int    iRet1 = 0;
    int    iNum=0;
    int    iNum1=0;
    char   stmp[512];
    char   ptrq[8+1];
    char   ptlsh[10+1];
    char   systime[6+1];
    char   jydm[12+1];
    
    
    ST_ICPS_JB_APPLYINFO applyinfo; /*授信请求信息 */
    ST_ICPS_JB_RESULTINFO resultinfo;  /*终审请求信息 */
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("蚂蚁借呗更新处理组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "")
    
    DCIBegin();   /**开始事务**/
    memset(jydm,0x00,sizeof(jydm));
    COMP_SOFTGETXML("/pub/jydm", jydm); /*交易代码 */
    /*平台日期+平台流水号*/
    memset(ptrq,0x00,sizeof(ptrq));
    memset(ptlsh,0x00,sizeof(ptlsh));
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTRQ,ptrq);
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTLSH,ptlsh);
    /*时间*/
    memset(systime,0x00,sizeof(systime));
    memset(stmp,0x00,sizeof(stmp));
    COMP_SOFTGETXML(XMLNM_ICPS_JB_SYSTIME,stmp);      
    memcpy(systime,stmp,sizeof(systime)-1);
    
    if (0 == strcmp(jydm,"702513")) /*银行内部初审及数据入库*/
    {
        memset(&applyinfo,0x00,sizeof(applyinfo));
        ICPS_JB_PSTRCOPY(applyinfo.reqdate,ptrq);
        ICPS_JB_PSTRCOPY(applyinfo.reqtime1,systime);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,applyinfo.reqmsgid,"请求报文唯一标示");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,applyinfo.applyno,"申请单号");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_ISADMIT,applyinfo.isadmit,"是否推荐准入");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CREDITNO,applyinfo.creditno,"授信编号");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CREDITAMT,applyinfo.creditamt,"推荐准入时，推荐的额度");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CREDITRATE,applyinfo.creditrate,"推荐准入时，推荐的利率");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_REFUSECODE,applyinfo.refusecode,"推荐拒绝时，拒绝码");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_REFUSEMSG,applyinfo.refusemsg,"推荐拒绝时，拒绝原因");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_APPLYSTAT,applyinfo.applystat,"授信请求单状态");
        LOG(LM_STD, Fmtmsg("开始更新蚂蚁借呗-授信请求信息表【icps_jb_applyinfo】！[%s]", fpub_GetCompname(lXmlhandle)), "");
        iRet =fdbop_upd_icps_jb_applyinfo_702513(lXmlhandle,&applyinfo);
        if(iRet<0)
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_STD, Fmtmsg("更新蚂蚁借呗-授信请求信息表-行内初审【icps_jb_applyinfo】成功！[%s]", fpub_GetCompname(lXmlhandle)), "");
    }
    else if (0 == strcmp(jydm,"702514")) /*银行发送授信结果*/
    {
        memset(&applyinfo,0x00,sizeof(applyinfo));
        ICPS_JB_PSTRCOPY(applyinfo.respdate,ptrq);
        ICPS_JB_PSTRCOPY(applyinfo.resptime,systime);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,applyinfo.reqmsgid,"请求报文唯一标示");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,applyinfo.applyno,"申请单号");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESPCODE,applyinfo.respcode,"返回响应码");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESPMSG,applyinfo.respmsg,"返回响应信息");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_RETRY,applyinfo.retry,"是否需要重试");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_RESULTSTAT,applyinfo.resultstat,"初审返回状态码");
        LOG(LM_STD, Fmtmsg("开始更新蚂蚁借呗-授信请求信息表-蚂蚁初审返回【icps_jb_applyinfo】！[%s]", fpub_GetCompname(lXmlhandle)), "");
        iRet =fdbop_upd_icps_jb_applyinfo_702514(lXmlhandle,&applyinfo);
        if(iRet<0)
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_STD, Fmtmsg("更新蚂蚁借呗-授信请求信息表【icps_jb_applyinfo】成功！[%s]", fpub_GetCompname(lXmlhandle)), "");
    }
    else if (0 == strcmp(jydm,"702515")) /*借呗发送终审确认*/
    {
        memset(&resultinfo,0x00,sizeof(resultinfo));
        ICPS_JB_PSTRCOPY(resultinfo.ptrq,ptrq);
        ICPS_JB_PSTRCOPY(resultinfo.ptlsh,ptlsh);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,resultinfo.reqmsgid,"请求报文唯一标示");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,resultinfo.applyno,"申请单号");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESPCODE,resultinfo.resultcode,"响应码");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESPMSG,resultinfo.resultmsg,"响应描述");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_ISADMIT,resultinfo.isadmit,"是否推荐准入");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_ADMITMSG,resultinfo.admitmsg,"准入原因");
        iRet =fdbop_upd_icps_jb_resultinfo(lXmlhandle,&resultinfo);
        LOG(LM_STD, Fmtmsg("开始更新蚂蚁借呗-授信请求信息表【icps_jb_applyinfo】！[%s]", fpub_GetCompname(lXmlhandle)), "");
        iRet =fdbop_upd_icps_jb_resultinfo(lXmlhandle,&resultinfo);
        if(iRet<0)
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_STD, Fmtmsg("更新蚂蚁借呗-授信请求信息表【icps_jb_applyinfo】成功！[%s]", fpub_GetCompname(lXmlhandle)), "");
    }
    
    DCICommit();
    
    LOG(LM_STD, Fmtmsg("蚂蚁借呗更新处理组件[%s]执行成功", fpub_GetCompname(lXmlhandle)), "")
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

    return 0;

}
