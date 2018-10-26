/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V1.0.00
  ����ϵͳ:LIUNX64
  �ļ�����:CUSTOM_PUBLIC_DRC.c
  �ļ�����:GAPS���Ի��������
  �� Ŀ ��:
  �� �� Ա:liurj
  ��������:
  ��    ��:
  �޸�����:  
 *********************************************************************/

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.00"
#define MAX_RES_BUF_SIZE 5*1024

#include "gaps_head.h"
#include <string.h>

/*
   ע��������Ϊ����⹫������,�����ڷ���״̬����ʾ�ڲ��汾��Ϣ
       �����������£�ÿ�θ��¾�Ӧ�޸İ汾�š�������Ӧ��Ϣ
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
             "<soname>CUSTOM_PUBLIC_DRC.so</soname>"
             "<sosrcname>CUSTOM_PUBLIC_DRC.c</sosrcname>"
             "<sonote>���Ի��������</sonote>"
             "<version>"
               "<rec ver=\"1.0.00\" modify=\"2018-01-22 17:18:33\" programer=\"[�����]\" filesize=\"FILE\">��ʼ������</rec>"
             "</version>"
     "</root>";
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
  �����������: SYS_CUSTOM_SHELLOUTPUT
  �������: ִ��shell���ȡ������

  �������: 
  ִ��shell���ȡ������
  �������: 
  ��� ��������        ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��
  1    SHELL����       XML�����ַ���           ����Ϊ��  ��Ҫִ�е�SHELL����
  2    �������ڵ�    XML�����ַ���           ����Ϊ��  ִ��SHELL����������Ļ�Ľ��������ĳ�ڵ�

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����
  ��

  �� Ŀ ��: 
  �� �� Ա: liurj
  ��������: 2018��01��22��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: pwd /sys/shelloutput 
 ************************************************************************/
IRESULT SYS_CUSTOM_SHELLOUTPUT(HXMLTREE lXmlhandle)
{
    int iParas;
    char sCmd[256] = {0};     //SHELL����
    char sOutput[256] = {0};  //SHELL����Ľ�����浽�ýڵ�
    char sLine[1024] = {0};   //shell����Ľ����ÿһ��
    char* pRes = NULL;        //shell�����������
    FILE* fp = NULL;
    int iOffset = 0;
    int iLen = 0;
 
    fpub_InitSoComp(lXmlhandle); 
    
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  

    COMP_PARACOUNTCHKMIN(2);
    COMP_GETPARSEPARAS(1, sCmd, "SHELL����");
    COMP_GETPARSEPARAS(2, sOutput, "�����������Ľڵ�");
    
    pRes = (char *)malloc(sizeof(char) * MAX_RES_BUF_SIZE);
    if(pRes == NULL)
    {
      LOG(LM_STD, "malloc�����ڴ�ʧ��", __func__);     
      fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("�����ڴ�ʧ�ܣ�δִ��SHELL����"));
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);    
      return COMPRET_FAIL;
    }
    
    memset(pRes, 0, MAX_RES_BUF_SIZE);  	
    fp = popen(sCmd, "r");
    if(fp == NULL)
    {
      LOG(LM_STD, "��ȡSHELL������ʧ��", "ERROR");
      fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL;
    }
      	  	
    while(fgets(sLine, sizeof(sLine), fp) != NULL)
    {
      iLen = strlen(sLine);
      if(iOffset + iLen < MAX_RES_BUF_SIZE)
      {
        pstrcopy(pRes+iOffset, sLine, MAX_RES_BUF_SIZE-iOffset);
        memset(sLine, 0, sizeof(sLine));
        iOffset += iLen;
      }
      else
      {
        pRes[iOffset] = '\0';
        if(fp != NULL)
        {
          pclose(fp);
          fp = NULL;
        }
        COMP_SOFTSETXML(sOutput,pRes);
        LOG(LM_STD, "������ڴ治���Ա���SHELL����Ľ����ֻ�����˲��ݽ��", "ERROR");
        fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        free(pRes);
        pRes = NULL;
        return COMPRET_FAIL;			}
    }

    if(fp != NULL)
    {
      pclose(fp);
      fp = NULL;
    }

    if(pRes[iOffset-1] =='\n')
    {
      pRes[iOffset-1] = '\0';
    }

    COMP_SOFTSETXML(sOutput,pRes);
    free(pRes);
    pRes = NULL;
    LOG(LM_STD, "��ȡshellִ�н���ɹ�", "INFO");
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
