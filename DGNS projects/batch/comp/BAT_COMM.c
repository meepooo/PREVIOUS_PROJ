/********************************************************************
版权所有:恒生电子股份有限公司（杭州）
项目名称:中间业务平台项目(AGENT2.0)
版    本:V2.0
操作系统:AIX5.3+ORA10G+HSXP
文件名称:BATCH_COMM.c
文件描述: 
项 目 组:中间业务平台项目组
程 序 员:chensy
发布日期:
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <math.h>
#include "gaps_head.h"
#include "server.h"

#define  HEAD_NO   1
#define  MAX_LEN   8192
#define  SENDREC   10
#define  RepeatNum 5

/************************************************************************
动态组件函数定义
组件函数名称:SBATCH_WEB_TCP
组件名称:BATCH_WEB_TCP
组件功能: 批量业务web接触tcp通讯
组件参数:
 序号 参数类型  参数名称         资源类别     缺省值  可空  参数说明    
  1   1-输入   通讯缓冲节点名  416XML解析字符串  *      N    
  2   1-输入   IP地址      416XML解析字符串  *      N
  3   1-输入   端口        416XML解析字符串  *      N
  4   1-输入   超时时间     416XML解析字符串  *      N
     
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/

IRESULT SBATCH_WEB_TCP(HXMLTREE lXmlhandle)
{
    int  iSock = -1,iPort, iTime, iRet, len;
    char sTmp[MAX_LEN];
    char sPkgLen[10];
    char sBuffer[MAX_LEN];
    char sCommBufName[100];
    char syncbuf[4]={"\x02\x00\x00"};
    char sIp[17], sTime[10];
    
    fpub_InitSoComp(lXmlhandle);
      
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")   
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "通讯缓冲节点名")
    pstrcopy( sCommBufName, sTmp, sizeof(sCommBufName) ); 
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "IP地址")
    pstrcopy( sIp, sTmp, sizeof(sIp) ); 
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(3, sTmp, "端口")
    iPort=atoi(sTmp); 
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "超时时间")
    pstrcopy( sTime, sTmp, sizeof(sTime) ); 
    
    LOG(LM_DEBUG,Fmtmsg("BATCH: TAMC服务IP=[%s] PORT=[%d] TIMEOUT=[%s]", sIp, iPort, sTime),"INFO")
    
    /*取请求报文内容*/
    memset(sBuffer, 0, sizeof(sBuffer));
    if (( len= xml_RelGetBinElement( lXmlhandle, sCommBufName, sBuffer, sizeof(sBuffer))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelGetBinElement错误！!!!!!!!"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"执行xml_RelGetBinElement错误！!!!!!!!!!","ERROR");
    }
          
    /*与主机建立连接*/
    itcp_sethead(0);
    itcp_setenv( iPort , &iSock);
    itcp_setsync(3,syncbuf);
    itcp_setmaxlen(8192); 
    
    if ( itcp_calln(sIp,3) <0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"请求连接TAMC失败"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"请求连接TAMC失败","ERROR");
    }
      
    LOG(LM_DEBUG,Fmtmsg("BATCH: 发送TAMC服务报文[%s][%d]", sBuffer, len ),"DEBUG")
    
    /*发送请求报文*/
    iRet=itcp_send(sBuffer,len,iTime);
    
    if (iRet<0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"发送TAMC失败"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"发送TAMC失败","ERROR");
    }
     /*接收应答包长*/
    memset(sBuffer, 0, sizeof(sBuffer));
    iRet=itcp_recv(sBuffer, sizeof(sBuffer), iTime);
    if (iRet < 0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"接收TAMC包体失败"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"接收TAMC包体失败","ERROR");
    }
    len = strlen( sBuffer );
    LOG(LM_DEBUG,Fmtmsg("BATCH: 接收TAMC服务报文[%s][%d]", sBuffer, len ),"DEBUG")
    if ( (len= xml_RelSetBinElement ( lXmlhandle, XMLNM_COMMBUF, sBuffer, len)) == FAIL )
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,"执行xml_RelSetBinElement错误！"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"执行xml_RelSetBinElement错误！","ERROR");  
    }
    
    itcp_clear(); 
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")  
    
    return COMPRET_SUCC;
}




