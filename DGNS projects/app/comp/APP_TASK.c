/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:APP_TASK.c
�ļ�����:�����ദ���������
�� Ŀ ��:
�� �� Ա:wuyp@hundsun.com
��������:2008��12��01��
��    ��:
�޸�����: 20110711
          ������־��¼��ʽ
�޸�����: 20140915
          DCI����
*********************************************************************/
#include <math.h>
#include <dlfcn.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>APP_TASK.so</soname>\
        <sosrcname>APP_TASK.c</sosrcname>\
        <sonote>�����������</sonote>\
        <version>\
        <rec ver=\"2.0.1.1\" modify=\"2010-4-1  15:08\" programer=\"Wuyp\" filesize=\"1080632\">HS-AgentV2.0����</rec>\
        <rec ver=\"2.1.0.1\" modify=\"2011-11-01 10:34\" programer=\"S..C\" filesize=\"1080632\">HS-AgentV2.1����</rec>\
        <rec ver=\"4.1.0.1\" modify=\"2014-9-15 10:34\" programer=\"YangDong\" filesize=\"1080632\">DCI����</rec>\
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

/***********************************************************************
��  �ܣ���XML��Ϊ����Դ,INSERT ���ݿ��[app_rwjkb]����
��  ����
    HXMLTREE lXmlhandle    �����XML���
����ֵ��
      0    �����ɹ�
     -1    ���ݿ����ʧ��
     -2    �����ܾ�:����У��ʧ��
     -3    �����������ļ�¼(����ʱ)
     -9    ���ݿ����ʧ��,�ύ����ʧ��
������Ϣ��
   ����������:����ҵ������ˮ��
   ����ʱ��:2008-12-04 17:09:32 [By GenFromWorkSpace_DB]
   ˵����Ϣ:
************************************************************************/
int SApp_RecordTASK(HXMLTREE lXmlhandle)
{
    APP_RWJKB sdb_app_rwjkb;
    static struct timeb  timetp;
    char sbuf[255];
    char sSysDate[8+1];
    char sSysTime[6+1];
    int  imillitm=0;
    int iRet = -1;
    char sErrmsg[512];
   
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
   
    memset(&sdb_app_rwjkb,0,sizeof(APP_RWJKB));

    /*Ӧ�ñ�ʶ(Ĭ�ϴ���ҵ��)*/
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_YYBS,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.yybs,sbuf,sizeof(sdb_app_rwjkb.yybs));
    
    /*Ӧ������(Ĭ�ϴ���ҵ��)*/
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_YYMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.yymc,sbuf,sizeof(sdb_app_rwjkb.yymc));
    
    /* ��Ʒ���� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_CPDM,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.cpdm,sbuf,sizeof(sdb_app_rwjkb.cpdm));
    
    /* ��Ʒ���� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_RWKZB_CPMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.cpmc,sbuf,sizeof(sdb_app_rwjkb.cpmc));
    
    /* �������� */
    memset(sbuf,0,sizeof(sbuf));
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_RWMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.rwmc,sbuf,sizeof(sdb_app_rwjkb.rwmc));
    
    /*���״���*/
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYDM,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jydm,sbuf,sizeof(sdb_app_rwjkb.jydm));
    
    /*��������*/
    COMP_SOFTGETXML(XMLNM_APP_JYXX_JYMC,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jymc,sbuf,sizeof(sdb_app_rwjkb.jymc)); 
   
    /*ƽ̨����*/
    COMP_SOFTGETXML(XMLNM_ZWRQ,sbuf);
    if ( 0 == sbuf[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->�����ܾ�:�ֶ�[ptrq]Ϊnot null,��Ӧ��ֵ[/pub/zwrq]Ϊ��,����!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_TASK_ZWRQ_NULL,MSG_TASK_ZWRQ_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    pstrcopy(sdb_app_rwjkb.ptrq,sbuf,sizeof(sdb_app_rwjkb.ptrq));
    
    /*ƽ̨��ˮ��*/
    COMP_SOFTGETXML(XMLNM_ZHQZLSH,sbuf);
    if ( 0 == sbuf[0] ) 
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->�����ܾ�:�ֶ�[ptls]Ϊnot null,��Ӧ��ֵ[/pub/zhqzlsh]Ϊ��,����!"),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_TASK_PTLS_NULL,MSG_TASK_PTLS_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    sdb_app_rwjkb.ptls = atoi(sbuf);
    
    /*���׻���*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_JYJG,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jyjg,sbuf,sizeof(sdb_app_rwjkb.jyjg));
    
    /*���׹�Ա*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_JYGY,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jygy,sbuf,sizeof(sdb_app_rwjkb.jygy));
    
    /*������ʶ*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_QDBS,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.qdbs,sbuf,sizeof(sdb_app_rwjkb.qdbs));
   
    /* ����ִ��ʱ�� --B*/
    ftime(&timetp);
    memset(sbuf, 0, sizeof(sbuf));
    COMP_SOFTGETXML("/sys/systime_stamp",sbuf)
    if (sbuf[0] !=0 )
    {
        sprintf(sbuf,"%ld",timetp.time*1000+timetp.millitm-atol(sbuf));
        COMP_SOFTSETXML(XMLNM_APP_TRANSTIME,sbuf);
    }
    /* ����ִ��ʱ�� --E*/
   
    /*��ʼʱ���*/
    fprv_gettimeStamp(sSysDate,sSysTime,sbuf);
    pstrcopy(sdb_app_rwjkb.kssj,sbuf,sizeof(sdb_app_rwjkb.kssj));
    
    /*����ʱ���*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_JSSJ,sbuf);
    trim(sbuf);
    pstrcopy(sdb_app_rwjkb.jssj,sbuf,sizeof(sdb_app_rwjkb.jssj));
    
    /*ִ��ʱ��*/
    COMP_SOFTGETXML(XMLNM_APP_TRANSTIME,sbuf);
    trim(sbuf);
    sdb_app_rwjkb.yxsj=atoi(sbuf);
   
    /*ִ�д���*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_ZXCS,sbuf);
    sdb_app_rwjkb.zxcs = atoi(sbuf);
    
    /*������Ӧ��*/
    COMP_SOFTGETXML(XMLNM_RESPCODE,sbuf);
    pstrcopy(sdb_app_rwjkb.xym, sbuf,sizeof(sdb_app_rwjkb.xym));
     
    /*������Ӧ��*/
    COMP_SOFTGETXML(XMLNM_RESPMSG,sbuf);
    pstrcopy(sdb_app_rwjkb.xyxx, sbuf,sizeof(sdb_app_rwjkb.xyxx));
      
    /* ִ��״̬ */
    if ( strcmp(sdb_app_rwjkb.xym, "00000") == 0)
        strcpy(sdb_app_rwjkb.zxzt, "0");
    else
        strcpy(sdb_app_rwjkb.zxzt, "1");
        
    /*��չ1*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_EXTFLD1,sbuf);
    trim(sbuf);
    if ( strlen(sbuf)<=0)
        strcpy(sdb_app_rwjkb.extfld1," ");
    else
        pstrcopy(sdb_app_rwjkb.extfld1,sbuf,sizeof(sdb_app_rwjkb.extfld1));
    
    /*��չ2*/
    COMP_SOFTGETXML(XMLNM_APP_RWJKB_EXTFLD2,sbuf);
    trim(sbuf);
    if ( strlen(sbuf)<=0)
        strcpy(sdb_app_rwjkb.extfld2," ");
    else
        pstrcopy(sdb_app_rwjkb.extfld2,sbuf,sizeof(sdb_app_rwjkb.extfld2));
           
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    iRet = DBInsert("app_rwjkb", SD_APP_RWJKB, NUMELE(SD_APP_RWJKB), &sdb_app_rwjkb, sErrmsg);
    if ( iRet < 0 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->���ݿ����ʧ��,[%s]",DCILastError()),"ERROR");
        DCIRollback();
        fpub_SetMsg(lXmlhandle,MID_SQL_INSERT,MSG_SQL_INSERT );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
   
    /*�ύ����*/
    if ( DCICommit() == -1 )
    {
        LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_STD,Fmtmsg("  -->���ݿ����ʧ��,[%s]",DCILastError()),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_INSERT,MSG_SQL_INSERT );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    LOG_Ctrl(lXmlhandle, __FILE__, __LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;  
}
