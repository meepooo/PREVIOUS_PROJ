/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:中间业务平台项目
版    本:V4.1.0.1
操作系统:AIX5.3
文件名称:APP_COMPEX.c
文件描述:公共扩展组件集合
项 目 组:
程 序 员:YangDong 
发布日期:
修    订: 
*********************************************************************/
#include "gaps_head.h"
#include "../incl/app_head.h"


#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
      <root>\
      <soname>APP_GETGYGW.so</soname>\
      <sosrcname>APP_COMPEX.c</sosrcname>\
      <sonote>公共扩展组件集合</sonote>\
      <version>\
      <rec ver=\"4.1.0.1\" modify=\"2014-06-17 10:40\" programer=\"YD\" filesize=\"1059174\">HS-AgentV2.1改造</rec>\
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

/************************************************************************
动态组件函数定义
组件函数名称: SDATA_MSetValue_ex
组件名称: 多元素赋值组件(支持左边变量)
组件功能: 
  为多个指定XML元素进行解析式字符赋值
组件参数: 
  序号 参数名称     资源类别     缺省值   是否可空  参数说明
  1    赋值方式     数值字符串        0   否        赋值的方式   '0' 普通字符串 '1' 二进制
  2    字符赋值公式 XML解析字符串                   元素名(支持变量)=字符赋值公式

组件结果状态: 
  结果状态码         结果说明
  缺省

日志信息: 
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息
  
项 目 组: 中间业务产品研发组
程 序 员: 
发布日期: 2014年06月17日
参数使用示例: 
************************************************************************/
IRESULT SDATA_MSetValue_ex(HXMLTREE lXmlhandle)
{
    int i,iParas;
    char  sEname[LEN_TRC_FCOMPPARACFG_PARACONT];
    char  sCont[LEN_TRC_FCOMPPARACFG_PARACONT];
    char  sMode[LEN_TRC_FCOMPPARACFG_PARACONT];
    char  sParsedCont[MAX_FLD];
    char  sParsedCont2[MAX_FLD];
    char *p;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")   

    /*获取组件参数  --S*/
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARAS(1,sMode,"赋值方式")
    /*获取组件参数  --E*/

    for ( i=2;i<=iParas;i++ )
    {
        COMP_GETPARAS(i,sCont,"字符赋值公式")
    
        if ( (p = strchr(sCont,'=')) == NULL )
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);        
            LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg(MSG_SYS_DATAEXPERR,sCont),"SDATA_MSetValue")
        }
        *p=0;
        strcpy(sEname,sCont);
        /* 支持节点名解析 */
        if (xml_RelParseXMLString(lXmlhandle,sEname ,sizeof(sEname))==FAIL)
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_XMLPARSE,sParsedCont,GETXMLERR), "SDATA_MSetValue")
        }
     
        memset(sParsedCont,0,sizeof(sParsedCont));
        memcpy(sParsedCont,p+1,strlen(p+1));
        if (xml_RelParseXMLString(lXmlhandle,sParsedCont,sizeof(sParsedCont))==FAIL)
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_XMLPARSE,sParsedCont,GETXMLERR), "SDATA_MSetValue")
        }
        if ( strcmp(sEname+strlen(sEname)-2,"mm") )
            LOG(LM_WARNING,Fmtmsg("%s=[%s]",sEname,sParsedCont),"")    
        else
        {
            strcpy(sParsedCont2,sParsedCont);
            memset(sParsedCont2,'*',strlen(sParsedCont));
            LOG(LM_WARNING,Fmtmsg("%s=[%s]",sEname,sParsedCont2),"")    
        }
        if ( sMode[0] == '1' )
        {
            if ( (xml_SetBinElement(lXmlhandle,sEname,sParsedCont,strlen(sParsedCont)))==FAIL)
            {
                LOG(LM_DEBUG,Fmtmsg(MSG_SYS_XMLBINSET,sEname,GETXMLERR), "SDATA_MSetValue")
                fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);  
                LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg(MSG_SYS_COMPGETPARA,1),"SDATA_MSetValue")      
            }
        }
        else
            COMP_HARDSETXML(sEname,sParsedCont)
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
  
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"")  
  
    return COMPRET_SUCC;
}
