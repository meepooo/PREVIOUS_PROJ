/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V2.0
����ϵͳ:AIX5.3+ORA10G+HSXP
�ļ�����:BATCH_COMM.c
�ļ�����: 
�� Ŀ ��:�м�ҵ��ƽ̨��Ŀ��
�� �� Ա:chensy
��������:
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
��̬�����������
�����������:SBATCH_WEB_TCP
�������:BATCH_WEB_TCP
�������: ����ҵ��web�Ӵ�tcpͨѶ
�������:
 ��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
  1   1-����   ͨѶ����ڵ���  416XML�����ַ���  *      N    
  2   1-����   IP��ַ      416XML�����ַ���  *      N
  3   1-����   �˿�        416XML�����ַ���  *      N
  4   1-����   ��ʱʱ��     416XML�����ַ���  *      N
     
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
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
      
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")   
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(1, sTmp, "ͨѶ����ڵ���")
    pstrcopy( sCommBufName, sTmp, sizeof(sCommBufName) ); 
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(2, sTmp, "IP��ַ")
    pstrcopy( sIp, sTmp, sizeof(sIp) ); 
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(3, sTmp, "�˿�")
    iPort=atoi(sTmp); 
    
    memset(sTmp,0,sizeof(sTmp));
    COMP_GETPARSEPARAS(4, sTmp, "��ʱʱ��")
    pstrcopy( sTime, sTmp, sizeof(sTime) ); 
    
    LOG(LM_DEBUG,Fmtmsg("BATCH: TAMC����IP=[%s] PORT=[%d] TIMEOUT=[%s]", sIp, iPort, sTime),"INFO")
    
    /*ȡ����������*/
    memset(sBuffer, 0, sizeof(sBuffer));
    if (( len= xml_RelGetBinElement( lXmlhandle, sCommBufName, sBuffer, sizeof(sBuffer))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"ִ��xml_RelGetBinElement����!!!!!!!"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"ִ��xml_RelGetBinElement����!!!!!!!!!","ERROR");
    }
          
    /*��������������*/
    itcp_sethead(0);
    itcp_setenv( iPort , &iSock);
    itcp_setsync(3,syncbuf);
    itcp_setmaxlen(8192); 
    
    if ( itcp_calln(sIp,3) <0 )
    {
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"��������TAMCʧ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"��������TAMCʧ��","ERROR");
    }
      
    LOG(LM_DEBUG,Fmtmsg("BATCH: ����TAMC������[%s][%d]", sBuffer, len ),"DEBUG")
    
    /*����������*/
    iRet=itcp_send(sBuffer,len,iTime);
    
    if (iRet<0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"����TAMCʧ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"����TAMCʧ��","ERROR");
    }
     /*����Ӧ�����*/
    memset(sBuffer, 0, sizeof(sBuffer));
    iRet=itcp_recv(sBuffer, sizeof(sBuffer), iTime);
    if (iRet < 0)
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,"����TAMC����ʧ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"����TAMC����ʧ��","ERROR");
    }
    len = strlen( sBuffer );
    LOG(LM_DEBUG,Fmtmsg("BATCH: ����TAMC������[%s][%d]", sBuffer, len ),"DEBUG")
    if ( (len= xml_RelSetBinElement ( lXmlhandle, XMLNM_COMMBUF, sBuffer, len)) == FAIL )
    {
        itcp_clear();
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,"ִ��xml_RelSetBinElement����"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,"ִ��xml_RelSetBinElement����","ERROR");  
    }
    
    itcp_clear(); 
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")  
    
    return COMPRET_SUCC;
}




