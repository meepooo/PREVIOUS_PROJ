/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:DATA_STRREPLACE.c
�ļ�����:
�� Ŀ ��:
�� �� Ա:[����ΰ]
����ʱ��:2015-7-28 17:18:33[Gen]
��    ��:
�޸�ʱ��:
****************************************************************************/
/****************************************************************************
�޸ļ�¼
�޸�����:
�� �� ��:
�޸�����:
****************************************************************************/
#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

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
	     "<soname>DATA_STRREPLACE.so</soname>"
	     "<sosrcname>DATA_STRREPLACE.c</sosrcname>"
	     "<sonote>�ַ����滻</sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-28 17:18:33\" programer=\"[����ΰ]\" filesize=\"FILE\">��ʼ������</rec>"
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


int nAnalysisString(char *sSrc,char *sDesc1,char *sDesc2)
{
	int nRet = -1;	
	
	char *pTemp  = NULL;
	
	pTemp = strchr(sSrc, '|');

	if( NULL == pTemp )
	{
		return -1;	
	}
		
	strncpy(sDesc1,sSrc,pTemp-sSrc);
	strcpy(sDesc2,pTemp+1);
	
	return nRet;
}
















/************************************************************************
��̬�����������
�����������:DATA_STRREPLACE
�������:DATA_STRREPLACE
�������:�ַ����滻
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2015-7-28 17:18:33(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT DATA_STRREPLACE(HXMLTREE lXmlhandle)
{
  
  char sBufSrc[102400];
  char sSrc[128];
  char sDesc[128];
	char sBufDesc[102400];
  int  iParas;
  int	i = -1;

  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	iParas=fpub_GetPARAcount(lXmlhandle); 
	LOG(LM_STD,Fmtmsg("count(iParas)=[%d]",iParas),__func__);
	
	for(i = 1;i<= iParas;i++)
	{		
		memset(sBufSrc,0x00,sizeof(sBufSrc));
		memset(sSrc,0x00,sizeof(sSrc));
		memset(sDesc,0x00,sizeof(sDesc));
		
		COMP_GETPARSEPARAS(i,sBufSrc,"0-�ɹ���1-ʧ��");
		nAnalysisString(sBufSrc,sSrc,sDesc);
		LOG(LM_STD,Fmtmsg("SRC[%s],DESC[%s]",sSrc,sDesc),__func__);
		
		
		COMP_GETSOFTXML("/commbuf",sBufSrc);
		LOG(LM_STD,Fmtmsg("sBufSrc[%s]",sBufSrc),__func__);

	}
	


  /*XXX����ʧ��
  if ( 2 > 1 )
  {
    LOG(LM_STD, Fmtmsg("  -->����ʧ��:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }	
	*/
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}



