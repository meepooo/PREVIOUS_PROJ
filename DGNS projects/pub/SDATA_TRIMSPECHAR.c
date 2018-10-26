/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:DATA_DEC_DATE.c
�ļ�����:
�� Ŀ ��:
�� �� Ա:[]
����ʱ��:2015-7-31 18:33:21[Gen]
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

#define MAX_SIZE 256
#include "gaps_head.h"
/*
   ע��������Ϊ����⹫������,�����ڷ���״̬����ʾ�ڲ��汾��Ϣ
       �����������£�ÿ�θ��¾�Ӧ�޸İ汾�š�������Ӧ��Ϣ
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
	     "<soname>DATA_DEC_DATE.so</soname>"
	     "<sosrcname>DATA_DEC_DATE.c</sosrcname>"
	     "<sonote></sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-31 18:33:21\" programer=\"[����ΰ]\" filesize=\"FILE\">��ʼ������</rec>"
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





char* TrimSpeChar(char c,char *sData)
{
	int i = 0;
	int j = 0;
	
	if ( NULL == sData)
	{
		return NULL;	
	}
	
	while( '\0' != *(sData+i))
	{
		if (c != *(sData+i)&& ' ' != *(sData+i))
		{
			*(sData+j) = *(sData+i);
			i++;
			j++;	
		}
		else
		{
			i++;
		}		
	
	}

	*(sData+j)='\0';

	return sData;
}

/************************************************************************
��̬�����������
�����������:DATA_DEC_DATE
�������:DATA_DEC_DATE
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
	1         ����      para1               ICXP����                                          0         Ԫ����=�ַ���ֵ��ʽ
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
�޸�����:/2015-7-31 18:33:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT SDATA_TRIMSPECHAR(HXMLTREE lXmlhandle)
{
  char para1[30];

  char	sPath[MAX_SIZE];
  char	sData[MAX_SIZE];
  char	cTrimChar;
  int	iParas;
  int	i;

  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	iParas=fpub_GetPARAcount(lXmlhandle);
	
	/*XXX����ʧ��*/
  if ( iParas <	2 )
  {
    LOG(LM_STD, Fmtmsg("  -->����ʧ��:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }	


	COMP_GETPARSEPARAS(1,sData,"0-�ɹ�,1-ʧ��");
	cTrimChar = atoi(sData);

	if('\0' == cTrimChar)
	{
		LOG(LM_STD, Fmtmsg("  -->����1����:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
	}
			
	for(i=2;i<=iParas;i++)
	{
		memset(sPath,0x00,sizeof(sPath));
		memset(sData,0x00,sizeof(sData));
		
		COMP_GETPARSEPARAS(i, sPath, "��ֵ����ʽ");
		
		LOG(LM_STD, Fmtmsg("sPath[%s]��ֵ", sPath), "");		
		xml_GetElement(lXmlhandle, sPath, sData,sizeof(sData));
		LOG(LM_STD, Fmtmsg("sData[%s]��ֵ", sData), "");	
		alltrim(sData);
		TrimSpeChar(cTrimChar,sData);
		LOG(LM_STD, Fmtmsg("ȥ[%c]sData[%s]��ֵ", cTrimChar,sData), "");	
		xml_SetElement(lXmlhandle, sPath, alltrim(sData)); 
	}	


#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}


