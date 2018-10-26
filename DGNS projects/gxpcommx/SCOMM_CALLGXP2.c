/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V3.2
操作系统:AIX5.3+DB2V8.1+HSXP
文件名称:SCOMM_CALLGXP.sqc
文件描述:代理业务平台GXP通讯组件集合
项 目 组:代理业务平台项目组
程 序 员:wuyp@hundsun.com
发布日期:2009年01月09日
修    订:
修改日期:
*********************************************************************/
#include <stdio.h>
#include <math.h>
#include <dlfcn.h>
#include <string.h>
#include "gaps_head.h"
#include "gxp_cli.h"

#define  DEBUG 1
#define  HEAD_NO   1
#define  MAX_PKG_LEN   100*1024

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "4.0.03"

int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
     <root>\
        <soname>SCOMM_CALLGXP.so</soname>\
        <sosrcname>SCOMM_CALLGXP.c</sosrcname>\
        <sonote>GXP通讯组件集合</sonote>\
        <version>\
          <rec ver=\"4.0.02\" modify=\"2009-6-11 10:43\" programer=\"Wangt Chendh\" filesize=\"70096\">整理为ASPKV4环境GXP通讯组件</rec>\
          <rec ver=\"4.0.03\" modify=\"2012-6-14 11:36\" programer=\"pancj\" filesize=\"6839\">超时处理记录日志时，添加超时时间</rec>\
        </version>\
     </root>";
  printf("\n================动态组件基本信息================\n");
  printf("SOCOMPBUILDNO:%s\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s\n",SOCOMPVERSION);
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

/**********************************************************
组件函数: SCOMM_CALLGXP2
组件名称: 与外联GXP报文通讯处理
组件参数：
   序号   参数名称               资源类别               缺省值      是否可空   参数说明
   1         服务器IP地址         416-解析字符串      127.0.0.1   否            服务器IP地址
   2         服务器PORT            416-解析字符串      9000         否            服务器PORT
   3         超时时间               416-解析字符串      60            否            超时时间
   4         通讯包缓存节点名   XML结构定义            /commbuf   否            通讯包缓存节点名
组件结果状态:
  结果状态码         结果说明
  -9999              缺省
  0                  成功
  1                  发送失败
  2                  接收失败
处理说明：
**********************************************************/
IRESULT SCOMM_CALLGXP2(HXMLTREE lXmlhandle)
{
    int  iSock = -1,iPort, iTime, iRet, len;
    char sIp[50], sPort[50], sTime[50] ;
    char sTmp[255];
    char *sBuffer=NULL;
    char sCommBufName[100],tmpbuf[10];
    int  iParas;
    int  ilen = 0;
    int  i=0,iflag=0;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_STD,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif

    COMP_PARACOUNTCHK(4)

    /*参数1*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sIp,0,sizeof(sIp));
    COMP_GETPARSEPARAS(1, sTmp, "服务器地址")
    trim(sTmp);
    sprintf(sIp,"%s",sTmp);

    /*参数2*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sPort,0,sizeof(sPort));
    COMP_GETPARSEPARAS(2, sTmp, "服务器端口")
    trim(sTmp);
    sprintf( sPort, "%s",sTmp );
    iPort = atoi(sPort);

    /*参数3*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sTime,0,sizeof(sTime));
    COMP_GETPARSEPARAS(3, sTmp, "超时时间")
    trim(sTmp);
    sprintf(sTime,"%s",sTmp);
    iTime = atoi(sTime);
    if ( iTime <=1 )
            iTime = 30;

    /*参数4*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sCommBufName,0,sizeof(sCommBufName));
    COMP_GETPARSEPARAS(4, sTmp, "通讯报文")
    trim(sTmp);
    sprintf(sCommBufName,"%s",sTmp);

#ifdef  DEBUG
    LOG(LM_DEBUG,Fmtmsg("正在与GXP后台通讯：IP=[%s] PORT=[%s] TIMEOUT=[%s]", sIp, sPort, sTime),"")
#endif

    /*取请求报文内容*/
    ilen =xml_GetElementLen( lXmlhandle,sCommBufName);
#ifdef  DEBUG
    LOG(LM_DEBUG,Fmtmsg("COMMBUF -->[%d]", ilen),"")
#endif    

    ilen = ilen +10;
    sBuffer = malloc (ilen);
    if(sBuffer == NULL)
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"分配内存空间失败！"));
        fpub_SetCompStatus(lXmlhandle,1);
         LOGRET(1,LM_STD,"分配内存空间失败","");
    }

/*    memset(sBuffer, 0, ilen); */
    if (( len= xml_RelGetBinElement( lXmlhandle, sCommBufName, sBuffer+8, ilen-10)) == FAIL )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelGetBinElement错误！!!!!!!!"));
        fpub_SetCompStatus(lXmlhandle,1);
        free(sBuffer);
        LOGRET(1,LM_STD,"执行xml_RelGetBinElement错误！!!!!!!!!!","");
        return 1;
    }
    memset(tmpbuf,0x00,sizeof(tmpbuf));
    sprintf(tmpbuf,"%08d",len);
    memcpy(sBuffer,tmpbuf,8);
    *(sBuffer+len+8)='\0';
    
    /*发送请求报文*/
#ifdef  DEBUG
    LOG(LM_DEBUG,Fmtmsg("需要发送的报文数据包len=[%d]", len),"")
#endif

    /*与对方建立连接*/
    itcp_sethead(HEAD_NO);
    itcp_setenv( iPort , &iSock);
    itcp_setmaxlen(ilen);
    if ( itcp_calln(sIp,3) <0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"请求连接GXP后台失败"));
        fpub_SetCompStatus(lXmlhandle,1);
        free(sBuffer);
        LOGRET(1,LM_STD,"请求连接GXP后台失败","");
        return 1;
    }

    iRet=itcp_send(sBuffer,len+8,iTime);
    if (iRet<0)
    {
       itcp_clear();
       fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"发送GXP后台失败"));
       fpub_SetCompStatus(lXmlhandle,1);
       free(sBuffer);
       LOGRET(1,LM_STD,"发送GXP后台失败","");
       return 1;
    }
    if(sBuffer != NULL)
    {
       free(sBuffer);
       sBuffer=NULL;
    }  
    /*接收对方应答包头*/
    len=0;
    memset(tmpbuf,0,sizeof(tmpbuf));
    iRet=itcp_recv(tmpbuf, 8, iTime);
    if (iRet < 0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"接收GXP后台报文失败"));
        fpub_SetCompStatus(lXmlhandle,2);
        LOGRET(2,LM_STD,"接收GXP后台报文长度失败","");
        return 2;
    }
    len=atoi(tmpbuf);

    sBuffer = malloc (len+1);
    if(sBuffer == NULL)
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"分配内存空间失败！"));
        fpub_SetCompStatus(lXmlhandle,1);
        LOGRET(1,LM_STD,"分配内存空间失败","");
    }
     
   /* memset(sBuffer, 0, len+1);*/
    iRet=itcp_recv(sBuffer, len, iTime);
    if (iRet < 0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"接收GXP后台报文失败"));
        fpub_SetCompStatus(lXmlhandle,2);
        free(sBuffer);
        LOGRET(2,LM_STD,"接收GXP2后台报文内容失败","");
        return 2;
    }
    *(sBuffer+len)='\0';
#ifdef  DEBUG
    LOG(LM_DEBUG,Fmtmsg("接收到的报文数据包len=[%d]", len),"")
#endif

    if(xml_SetBinElement(lXmlhandle,sCommBufName,sBuffer,len)<0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelSetBinElement错误！"));
        fpub_SetCompStatus(lXmlhandle,2);
        free(sBuffer);
        LOGRET(2,LM_STD,"执行xml_RelSetBinElement错误！","");
        return 2;
    }
    if( sBuffer != NULL)
    {
        free(sBuffer);
        sBuffer = NULL;
    }
    itcp_clear();

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"")
#endif

    return COMPRET_SUCC;
}

/**********************************************************
组件函数: SCOMM_CALLGXP3
组件名称: 与内联GXP报文通讯处理
组件参数：
   序号   参数名称               资源类别               缺省值      是否可空   参数说明
   1         服务器IP地址         416-解析字符串      127.0.0.1   否            服务器IP地址
   2         服务器PORT            416-解析字符串      9000         否            服务器PORT
   3         超时时间               416-解析字符串      60            否            超时时间
   4         通讯包缓存节点名   XML结构定义            /commbuf   否            通讯包缓存节点名
   5     通讯头            XML结构定义       /commbuf0 否        通讯头节点名
   6     通讯头长度        416-解析字符串      56            否            通讯头长度
组件结果状态:
  结果状态码         结果说明
  -9999              缺省
  0                  成功
  1                  发送失败
  2                  接收失败
处理说明：
**********************************************************/
IRESULT SCOMM_CALLGXP3(HXMLTREE lXmlhandle)
{
    int  iSock = -1,iPort, iTime, iRet, len;
    char sIp[17], sPort[10], sTime[10] ;
    char sTmp[255];
    char sBuffer[MAX_PKG_LEN],sPkg[MAX_PKG_LEN];
    char sPkgLen[8+1];
    char sCommBufName[100],sHeadName[100];
    int  iParas;
    int  i=0,iflag=0,iheadlen;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_STD,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif
    COMP_PARACOUNTCHK(6)

    /*参数1*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sIp,0,sizeof(sIp));
    COMP_GETPARSEPARAS(1, sTmp, "服务器地址")
    trim(sTmp);
    sprintf(sIp,"%s",sTmp);

    /*参数2*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sPort,0,sizeof(sPort));
    COMP_GETPARSEPARAS(2, sTmp, "服务器端口")
    trim(sTmp);
    sprintf( sPort, "%s",sTmp );
    iPort = atoi(sPort);

    /*参数3*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sTime,0,sizeof(sTime));
    COMP_GETPARSEPARAS(3, sTmp, "超时时间")
    trim(sTmp);
    sprintf(sTime,"%s",sTmp);
    iTime = atoi(sTime);
    if ( iTime <=1 )
       iTime = 30;

    /*参数4*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sCommBufName,0,sizeof(sCommBufName));
    COMP_GETPARSEPARAS(4, sTmp, "通讯报文")
    trim(sTmp);
    sprintf(sCommBufName,"%s",sTmp);

    /*参数5*/
    memset(sHeadName,0x00,sizeof(sHeadName));
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(5, sTmp, "通讯头报文")
    trim(sTmp);
    sprintf(sHeadName,"%s",sTmp);

    /*参数6*/
    memset(sTmp,0,sizeof(sTmp));
    memset(sTime,0,sizeof(sTime));
    COMP_GETPARSEPARAS(6, sTmp, "通讯头长度")
    trim(sTmp);
    iheadlen = atoi(sTmp);
    if ( iheadlen <0 )
       iheadlen = 0;

#ifdef  DEBUG
    LOG(LM_DEBUG,Fmtmsg("正在与GXP后台通讯：IP=[%s] PORT=[%s] TIMEOUT=[%d]", sIp, sPort, iTime),"")
#endif

    /*取请求通讯头报文内容*/
    memset(sBuffer, 0, sizeof(sBuffer));
    if (( len= xml_RelGetBinElement( lXmlhandle, sHeadName, sBuffer, sizeof(sBuffer))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelGetBinElement错误！!!!!!!!"));
        fpub_SetCompStatus(lXmlhandle,1);
        LOGRET(1,LM_STD,"执行xml_RelGetBinElement错误！!!!!!!!!!","");
        return 1;
    }

    memset(sPkg,0,sizeof(sPkg));
    memcpy(sPkg+8,sBuffer,iheadlen);
 
    /* 获取通讯报文 */
    memset(sBuffer, 0, sizeof(sBuffer));
    if (( len= xml_RelGetBinElement( lXmlhandle, sCommBufName, sBuffer, sizeof(sBuffer))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelGetBinElement错误！!!!!!!!"));
        fpub_SetCompStatus(lXmlhandle,1);
        LOGRET(1,LM_STD,"执行xml_RelGetBinElement错误！!!!!!!!!!","");
        return 1;
    }
    memcpy(sPkg+8+iheadlen,sBuffer,len);
    len=len+iheadlen;
    memset(sPkgLen,0,sizeof(sPkgLen));
    sprintf(sPkgLen,"%08d",len);
    memcpy(sPkg,sPkgLen,8);
    
    /*发送请求报文*/
#ifdef  DEBUG
    LOG(LM_DEBUG,Fmtmsg("需要发送的报文数据包len=[%d]", len),"")
#endif

    /*与对方建立连接*/
    itcp_sethead(HEAD_NO);
    itcp_setenv( iPort , &iSock);
    itcp_setmaxlen(MAX_PKG);

    if ( itcp_calln(sIp,3) <0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"请求连接GXP后台失败"));
        fpub_SetCompStatus(lXmlhandle,1);
        LOGRET(1,LM_STD,"请求连接GXP后台失败","");
        return 1;
    }

    iRet=itcp_send(sPkg,len+8,iTime);
    if (iRet<0)
    {
       itcp_clear();
       fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"发送GXP后台失败"));
       fpub_SetCompStatus(lXmlhandle,1);
       LOGRET(1,LM_STD,"发送GXP后台失败","");
       return 1;
    }
      
    /*接收对方应答包头*/
    len=0;
    memset(sPkg,0,sizeof(sPkg));
    memset(sPkgLen,0,sizeof(sPkgLen));
    iRet=itcp_recv(sPkgLen, 8, iTime);
    if (iRet < 0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"接收GXP后台报文失败"));
        fpub_SetCompStatus(lXmlhandle,2);
        LOGRET(2,LM_STD,"接收GXP后台报文长度失败","");
        return 2;
    }
    len=atoi(sPkgLen);
    iRet=itcp_recv(sPkg, len, iTime);
    if (iRet < 0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"接收GXP后台报文失败"));
        fpub_SetCompStatus(lXmlhandle,2);
        LOGRET(2,LM_STD,"接收GXP2后台报文内容失败","");
        return 2;
    }
#ifdef  DEBUG
    LOG(LM_DEBUG,Fmtmsg("接收到的报文数据包len=[%d]", len),"")
#endif
    memset(sBuffer,0,sizeof(sBuffer));
    memcpy(sBuffer,sPkg,iheadlen);
    len=len-iheadlen;

    if(xml_SetBinElement(lXmlhandle,sHeadName,sBuffer,iheadlen)<0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelSetBinElement错误！"));
        fpub_SetCompStatus(lXmlhandle,2);
        LOGRET(2,LM_STD,"执行xml_RelSetBinElement错误！","");
        return 2;
    }
    if(len > 0)
    {
        if(xml_SetBinElement(lXmlhandle,sCommBufName,sPkg+iheadlen,len)<0)
        {
            itcp_clear();
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelSetBinElement错误！"));
            fpub_SetCompStatus(lXmlhandle,2);
            LOGRET(2,LM_STD,"执行xml_RelSetBinElement错误！","");
            return 2;
         }
    }
    itcp_clear();

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"")
#endif

    return COMPRET_SUCC;
}
