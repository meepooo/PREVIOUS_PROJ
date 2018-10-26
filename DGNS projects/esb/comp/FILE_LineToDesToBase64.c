/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:FILE_LineToDesToBase64.c
�ļ�����:
�� Ŀ ��:
�� �� Ա:fuyw
����ʱ��:2016/8/18
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
#include "DRC_des.h"
#include "base64.h"

/************************************************************************
��̬����������� ���ļ�ÿһ������3DES��������BASE64����
�����������:FILE_LineToDesToBase64
�������:FILE_LineToDesToBase64
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
	1         ����      para1               XML�����ַ���       NULL                          ���ɿ�    3Des��key
	2         ����      para2               XML�����ַ���       NULL                          ���ɿ�    Դ�ļ�·��
	3         ����      para3               XML�����ַ���       NULL                          ���ɿ�    Ŀ���ļ�·��

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
�޸�����:/2016/8/17
����ʹ��ʾ��:
************************************************************************/
IRESULT FILE_LineToDesToBase64(HXMLTREE lXmlhandle)
{
	int	nRet = -1;
	int	nLenDes = -1;
	int	nLenBase64 = -1;
	char	sSrcFile[1024] = {0x00};
	char	sDestFile[1024] = {0x00};
	char	sSrc[8128] = {0x00};
	char	sDest[8128] = {0x00};
	char	sKey[256] = {0x00};
	char	*pTemp = NULL;
	FILE	*fpSrc = NULL;
	FILE	*fpDest = NULL;

	fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	
	/*�жϲ�������*/
	nRet=fpub_GetPARAcount(lXmlhandle);
	if (nRet != 3)
	{
		LOG(LM_STD, Fmtmsg("  -->����ʧ��:���������������"), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}	
	
	/*��ȡ�������:Des��key*/
	memset(sKey,0x00,sizeof(sKey));
	COMP_GETPARSEPARAS(1, sKey, "��ֵ����ʽ");
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("key[%s]", sKey), __func__)
#endif	
	/*��ȡ�������:Դ�ļ�·��*/
	memset(sSrcFile,0x00,sizeof(sSrcFile));
	COMP_GETPARSEPARAS(2, sSrcFile, "��ֵ����ʽ");
	LOG(LM_DEBUG, Fmtmsg("SrcFile[%s]", sSrcFile), __func__)

	/*��ȡ�������:Ŀ���ļ�·��*/
	memset(sDestFile,0x00,sizeof(sDestFile));
	COMP_GETPARSEPARAS(3, sDestFile, "��ֵ����ʽ");
	LOG(LM_DEBUG, Fmtmsg("DestFile[%s]", sDestFile), __func__)

	chdir(getenv("HOME"));
	/*��Դ�ļ�*/
	fpSrc=fopen(sSrcFile,"r");
	if(NULL == fpSrc)
	{
		LOG(LM_DEBUG, Fmtmsg("��%s�ļ�����",sSrcFile), __func__)
		goto err;
	}
	/*��Ŀ���ļ�*/
	fpDest=fopen(sDestFile,"w");
	if(NULL == fpDest)
	{
		LOG(LM_DEBUG, Fmtmsg("��%s�ļ�����",sDestFile), __func__)
		goto err;
	}
	

	while (NULL != fgets(sSrc,sizeof(sSrc),fpSrc))
	{	
		/*ȥ�����һλ���з�*/
		*(sSrc+strlen(sSrc)-1)=0;
		
		/*DES����*/
		nRet = DRC_encryptdes(sDest,&nLenDes,sSrc,strlen(sSrc),sKey);
		if( nRet <0 || nLenDes>sizeof(sDest) )
		{
			LOG(LM_DEBUG, Fmtmsg("DES���ܴ���[%d][%ld]",nRet,nLenDes), __func__)
			goto err;
		}
		
		/*BASE64����*/
		pTemp=base64_encode(sDest,nLenDes,&nLenBase64);
		if( NULL == pTemp)
		{
			LOG(LM_DEBUG, Fmtmsg("BASE64���ܴ���"), __func__)
			goto err;

		}
		fprintf(fpDest,"%s\r\n",pTemp);

		if(NULL != pTemp)
		{
			free(pTemp);
			pTemp = NULL;
		}

		memset(sSrc,0x00,sizeof(sSrc));
		memset(sDest,0x00,sizeof(sDest));
		nLenDes = 0;
	}	

succ:
	if(NULL != fpSrc)
	{
		fclose(fpSrc);
		fpSrc = NULL;
	}

	if(NULL != fpDest)
	{
		fclose(fpDest);
		fpDest = NULL;
	}
fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
#ifdef DEBUG
	  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	return 0;


err:
	if(NULL != fpSrc)
	{
		fclose(fpSrc);
		fpSrc = NULL;
	}

	if(NULL != fpDest)
	{
		fclose(fpDest);
		fpDest = NULL;
	}

	LOG(LM_STD, Fmtmsg("���[%s]ִ��ʧ��", fpub_GetCompname(lXmlhandle)), __func__)
	fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	return COMPRET_FAIL;
}


/************************************************************************
��̬����������� ���ļ�ÿһ������3DES��������BASE64����
�����������:FILE_Base64ToDesToLine
�������:FILE_Base64ToDesToLine
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
	1         ����      para1               XML�����ַ���       NULL                          ���ɿ�    3Des��key
	2         ����      para2               XML�����ַ���       NULL                          ���ɿ�    Դ�ļ�·��
	3         ����      para3               XML�����ַ���       NULL                          ���ɿ�    Ŀ���ļ�·��


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
�޸�����:/2016/8/17
����ʹ��ʾ��:
************************************************************************/
IRESULT FILE_Base64ToDesToLine(HXMLTREE lXmlhandle)
{
	int	nRet = -1;
	int	nLenTemp = -1;
	int	nLenDes = -1;
	int	nLenBase64 = -1;
	char	sSrcFile[1024] = {0x00};
	char	sDestFile[1024] = {0x00};
	char	sSrc[8128] = {0x00};
	char	sDest[8128] = {0x00};
	char	sKey[256] = {0x00};
	char	*pTemp = NULL;
	FILE	*fpSrc = NULL;
	FILE	*fpDest = NULL;
	
	fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	
	/*�жϲ�������*/
	nRet=fpub_GetPARAcount(lXmlhandle);
	if (nRet != 3)
	{
		LOG(LM_STD, Fmtmsg("  -->����ʧ��:���������������"), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}	
	
	/*��ȡ�������:3Des��key*/
	memset(sKey,0x00,sizeof(sKey));
	COMP_GETPARSEPARAS(1, sKey, "��ֵ����ʽ");
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("key[%s]", sKey), __func__)
#endif	
	/*��ȡ�������:Դ�ļ�·��*/
	memset(sSrcFile,0x00,sizeof(sSrcFile));
	COMP_GETPARSEPARAS(2, sSrcFile, "��ֵ����ʽ");
	LOG(LM_DEBUG, Fmtmsg("SrcFile[%s]", sSrcFile), __func__)

	/*��ȡ�������:Ŀ���ļ�·��*/
	memset(sDestFile,0x00,sizeof(sDestFile));
	COMP_GETPARSEPARAS(3, sDestFile, "��ֵ����ʽ");
	LOG(LM_DEBUG, Fmtmsg("DestFile[%s]", sDestFile), __func__)

	chdir(getenv("HOME"));
	/*��Դ�ļ�*/
	fpSrc=fopen(sSrcFile,"r");
	if(NULL == fpSrc)
	{
		LOG(LM_DEBUG, Fmtmsg("��%s�ļ�����",sSrcFile), __func__)
		goto err;
	}
	/*��Ŀ���ļ�*/
	fpDest=fopen(sDestFile,"w");
	if(NULL == fpDest)
	{
		LOG(LM_DEBUG, Fmtmsg("��%s�ļ�����",sDestFile), __func__)
		goto err;
	}
	

	while (NULL != fgets(sSrc,sizeof(sSrc),fpSrc))
	{	
		nLenTemp = strlen(sSrc);
		/*ȥ�����һλ���з�*/
		*(sSrc+nLenTemp-1)=0;
		/*ȥ������λ�س���*/
		if( '\r' == *(sSrc+nLenTemp-2) ) *(sSrc+nLenTemp-2)=0;
		
		/*BASE64����*/
		pTemp=base64_decode(sSrc,strlen(sSrc),&nLenBase64);
		if( NULL == pTemp)
		{
			LOG(LM_DEBUG, Fmtmsg("BASE64���ܴ���"), __func__)
			goto err;
		}

		
		/*DES����*/
		nRet=DRC_decryptdes(sDest, &nLenDes, pTemp,nLenBase64, sKey);
		if ( nRet <0 || nLenBase64>sizeof(sDest) )
		{
			LOG(LM_DEBUG, Fmtmsg("DES���ܴ���[%d][%ld]",nRet,nLenDes), __func__)
			goto err;
		}

		fprintf(fpDest,"%s\n",sDest);

		if(NULL != pTemp)
		{
			free(pTemp);
			pTemp = NULL;
		}

		memset(sSrc,0x00,sizeof(sSrc));
		memset(sDest,0x00,sizeof(sDest));
		nLenBase64 = 0;
	}	

succ:
	if(NULL != fpSrc)
	{
		fclose(fpSrc);
		fpSrc = NULL;
	}

	if(NULL != fpDest)
	{
		fclose(fpDest);
		fpDest = NULL;
	}
fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	return 0;


err:
	if(NULL != fpSrc)
	{
		fclose(fpSrc);
		fpSrc = NULL;
	}

	if(NULL != fpDest)
	{
		fclose(fpDest);
		fpDest = NULL;
	}

	LOG(LM_STD, Fmtmsg("���[%s]ִ��ʧ��", fpub_GetCompname(lXmlhandle)), __func__)
	fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	return COMPRET_FAIL;
}





/*
   ע��������Ϊ����⹫������,�����ڷ���״̬����ʾ�ڲ��汾��Ϣ
       �����������£�ÿ�θ��¾�Ӧ�޸İ汾�š�������Ӧ��Ϣ
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
	     "<soname>FILE_LineToDesToBase64.so</soname>"
	     "<sosrcname>FILE_LineToDesToBase64.c</sosrcname>"
	     "<sonote></sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-31 18:33:21\" programer=\"[fuyw]\" filesize=\"FILE\">��ʼ������</rec>"
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
