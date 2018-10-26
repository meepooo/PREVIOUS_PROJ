/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ
��    ��:V4.1.0.1
����ϵͳ:AIX5.3
�ļ�����:APP_COMPEX.c
�ļ�����:������չ�������
�� Ŀ ��:
�� �� Ա:YangDong 
��������:
��    ��: 
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
      <sonote>������չ�������</sonote>\
      <version>\
      <rec ver=\"4.1.0.1\" modify=\"2014-06-17 10:40\" programer=\"YD\" filesize=\"1059174\">HS-AgentV2.1����</rec>\
      </version>\
      </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if (strlen(sversion) >= isize)
    {
        printf(" -->ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" -->��鿴��ϸ��Ϣ...\n");
    return 0;
    
}

/************************************************************************
��̬�����������
�����������: SDATA_MSetValue_ex
�������: ��Ԫ�ظ�ֵ���(֧����߱���)
�������: 
  Ϊ���ָ��XMLԪ�ؽ��н���ʽ�ַ���ֵ
�������: 
  ��� ��������     ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��
  1    ��ֵ��ʽ     ��ֵ�ַ���        0   ��        ��ֵ�ķ�ʽ   '0' ��ͨ�ַ��� '1' ������
  2    �ַ���ֵ��ʽ XML�����ַ���                   Ԫ����(֧�ֱ���)=�ַ���ֵ��ʽ

������״̬: 
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ: 
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ
  
�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա: 
��������: 2014��06��17��
����ʹ��ʾ��: 
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

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")   

    /*��ȡ�������  --S*/
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARAS(1,sMode,"��ֵ��ʽ")
    /*��ȡ�������  --E*/

    for ( i=2;i<=iParas;i++ )
    {
        COMP_GETPARAS(i,sCont,"�ַ���ֵ��ʽ")
    
        if ( (p = strchr(sCont,'=')) == NULL )
        {
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC, Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);        
            LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg(MSG_SYS_DATAEXPERR,sCont),"SDATA_MSetValue")
        }
        *p=0;
        strcpy(sEname,sCont);
        /* ֧�ֽڵ������� */
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
  
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"")  
  
    return COMPRET_SUCC;
}
