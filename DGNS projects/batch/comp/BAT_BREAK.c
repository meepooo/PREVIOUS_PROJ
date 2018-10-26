/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.1)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:BAT_UPD_BREAKDATE.c
�ļ�����:����breakdate�����
�� �� Ա:TUQL
��������:2016-06-04
�� �� Ա:
�޸�����:
�޸�˵��:
 *********************************************************************/
#include <dlfcn.h>
#include "gaps_head.h"
/*#include "DCI.h"*/
#include "batch_head.h"
#include "app_macro.h"
#include "app_xmlmacro.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
        <root>\
        <soname>BAT_CTRL.so</soname>\
        <sosrcname>BAT_CTRL.c</sosrcname>\
        <sonote>����breakdate�����</sonote>\
        <version>\
        <rec ver=\"4.1.0.1\" modify=\"2016-6-4 15:08\" programer=\"TUQL\" filesize=\"1266963\">HS-AgentV2.1����</rec>\
        </version>\
        </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if(strlen(sversion) >= isize)
    {
        printf(" ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" ��鿴��ϸ��Ϣ...\n");
    return 0;
}
/************************************************************************
��̬�����������
�����������:SBATCH_UPD_BREAKDATA
�������:SBATCH_UPD_BREAKDATA
�������: ����ҵ�����BREAKDATA
�������:
��� ��������  ��������         ��Դ���     ȱʡֵ  �ɿ�  ����˵��    
1    1-����   ������Ӧ��  416XML�����ַ���           N
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SBATCH_UPD_BREAKDATA(HXMLTREE lXmlhandle)
{
    
    DCIBegin();
    /* �����Ƿ�ϵ㣬���浱ǰ�ڵ���Ϣ */
    if( fprv_export_break( lXmlhandle ) != 0 )
    {
        DCIRollback();
        return COMPSTATUS_FAIL;
    }
    DCICommit();
    fpub_SetCompStatus(lXmlhandle, COMPRET_SUCC );

    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")

    return COMPRET_SUCC;  
}
    