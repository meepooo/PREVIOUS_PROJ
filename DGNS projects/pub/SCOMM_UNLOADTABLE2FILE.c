/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V1.0.00
  ����ϵͳ:LIUNX64
  �ļ�����:SCOMM_UNLOADTABLE2FILE.c
  �ļ�����:GAPS���Ի��������
  �� Ŀ ��:
  �� �� Ա:llh
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
             "<soname>SCOMM_UNLOADTABLE2FILE.so</soname>"
             "<sosrcname>SCOMM_UNLOADTABLE2FILE.c</sosrcname>"
             "<sonote>���Ի��������</sonote>"
             "<version>"
               "<rec ver=\"1.0.00\" modify=\"2018-01-22 17:18:33\" programer=\"[���麣]\" filesize=\"FILE\">��ʼ������</rec>"
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
  �����������: SCOMM_UNLOADTABLE2FILE
  �������: ��ȫ����SQL��ѯ���ݵ�ָ���ļ�

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
  �� �� Ա: llh
  ��������: 2018��01��22��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: pwd /sys/shelloutput 
 ************************************************************************/
IRESULT SCOMM_UNLOADTABLE2FILE(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[512+1];
    char sFilestr[1024+1];
    char sPathfilename[256+1];
    char sCmdsql[1024+1];
    char sDelim[2+1];
    char sOutnode[100+1];
    char sQuerynum[10+1];
    FILE* fp = NULL;
    int iRet = 0;
    int iNum = 0;
    int i = 0;
    int iQuerynum = 0;
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle); 
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)

    COMP_PARACOUNTCHKMIN(5);
    memset(sBuf,0x00,sizeof(sBuf));
    memset(sFilestr,0x00,sizeof(sFilestr));
    memset(sPathfilename,0x00,sizeof(sPathfilename));
    memset(sCmdsql,0x00,sizeof(sCmdsql));
    memset(sDelim,0x00,sizeof(sDelim));
    memset(sOutnode,0x00,sizeof(sOutnode));
    memset(sQuerynum,0x00,sizeof(sQuerynum));
    
    COMP_GETPARSEPARAS(1, sPathfilename, "�����ļ��洢·��");
    LOG(LM_DEBUG,Fmtmsg("sPathfilename=[%s]",sPathfilename),"DEBUG");
    COMP_GETPARSEPARAS(2, sCmdsql, "SQL��ѯ���");
    COMP_GETPARSEPARAS(3, sDelim, "�����ļ��еķָ���");
    COMP_GETPARSEPARAS(4, sOutnode, "������¼��������");
    COMP_GETPARSEPARAS(5, sQuerynum, "��ѯSQL��ֵ��Ŀ");
    trim(sPathfilename);
    trim(sCmdsql);
    trim(sDelim);
    trim(sOutnode);
    trim(sQuerynum);
    
    fp = fopen(sPathfilename, "w");
    if(fp == NULL)
    {
      LOG(LM_STD, "���ļ�ʧ��", "ERROR");
      fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL;
    }
    
    if ((cur = DCIDeclareCursor(sCmdsql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fclose(fp);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fclose(fp);
        return COMPRET_FAIL;
    }
    
    iQuerynum=atoi(sQuerynum);
    while( ( iRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0) ) > 0 )
    {
        iNum++;
        memset(sFilestr,0x00,sizeof(sFilestr));
        for(i=0;i<iQuerynum;i++)
        {
            LOG(LM_DEBUG,Fmtmsg("i=[%d]",i),"DEBUG");
            memset(sBuf,0x00,sizeof(sBuf));
            sprintf(sBuf, "%s", DCIFieldAsString( cur, i  ) );
            LOG(LM_DEBUG,Fmtmsg("sBuf=[%s]",sBuf),"DEBUG");
            strcat(sFilestr,sBuf);
            strcat(sFilestr,sDelim);
            LOG(LM_DEBUG,Fmtmsg("sFilestr=[%s]",sFilestr),"DEBUG");
        }
        strcat(sFilestr,"\n");
        LOG(LM_DEBUG,Fmtmsg("sFilestr=[%s]",sFilestr),"DEBUG");
        iRet = fwrite(sFilestr,strlen(sFilestr),1,fp);
        iRet = fflush(fp);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("д�ļ�ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fclose(fp);
            return COMPRET_FAIL;
        }
        
    }
          
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

