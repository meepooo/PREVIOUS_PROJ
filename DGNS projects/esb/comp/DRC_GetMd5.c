/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:DATA_GetMd5.c
�ļ�����:
�� Ŀ ��:
�� �� Ա:����ΰ
����ʱ��:2016/8/24
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
#include "DRC_esb_md5.h"
/************************************************************************
��̬����������� ��ȡ�ַ��������ļ���MD5ֵ
�����������:DATA_GetMd5
�������:DATA_GetMd5
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
	1         ����      para1               XML�����ַ���       NULL                          �ɿ�      ����Դ���� 1�ļ� �����ַ���
	2         ����      para2               XML�����ַ���       NULL                          ���ɿ�    ����Դ 
	3         ����      para3               XML�����ַ���       NULL                          ���ɿ�    ���MD5��XML·��


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
�޸�����:2016/8/24
����ʹ��ʾ��:
************************************************************************/
IRESULT DATA_GetMd5(HXMLTREE lXmlhandle)
{
	int	nParas = -1;
	int	nFlag = -1;

	char sTemp[1024] = {0x00};
	char sMd5[1024] = {0x00};
	char sPath[1024] = {0x00};


	fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	nParas=fpub_GetPARAcount(lXmlhandle);
	
	/*�жϲ�������*/
	if (nParas != 3)
	{
		LOG(LM_STD, Fmtmsg("  -->����ʧ��:���������������"), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}	
	
	chdir(getenv("HOME"));

	/*��ȡ�������:��������*/
	memset(sTemp,0x00,sizeof(sTemp));
	COMP_GETPARSEPARAS(1, sTemp, "��ֵ����ʽ");
	nFlag = atoi(sTemp);
	LOG(LM_DEBUG, Fmtmsg("nFlag[%d]", nFlag), __func__)

	/*��ȡ�������:����Դ*/
	memset(sTemp,0x00,sizeof(sTemp));
	COMP_GETPARSEPARAS(2, sTemp, "��ֵ����ʽ");
	LOG(LM_DEBUG, Fmtmsg("����Դ[%s]", sTemp), __func__)
	
	/*��ȡ�������:�����XML·��*/
	memset(sPath,0x00,sizeof(sPath));
	COMP_GETPARSEPARAS(3, sPath, "��ֵ����ʽ");

	

	memset(sMd5,0x00,sizeof(sMd5));
	if(1 == nFlag)
	{
		DRC_getMd5File(sTemp,sMd5);
		
	}
	else
	{
		DRC_getMd5Str(sTemp,strlen(sTemp),sMd5);
	}

	xml_SetElement(lXmlhandle,sPath, alltrim(sMd5)); 


fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	return 0;
}



/*
   ע��������Ϊ����⹫������,�����ڷ���״̬����ʾ�ڲ��汾��Ϣ
       �����������£�ÿ�θ��¾�Ӧ�޸İ汾�š�������Ӧ��Ϣ
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
	     "<soname>FILE_LineTo3DesToBase64.so</soname>"
	     "<sosrcname>FILE_LineTo3DesToBase64.c</sosrcname>"
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
