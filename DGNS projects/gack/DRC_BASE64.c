/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:DRC_BASE64.c
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
�����������:DRC_BASE64
�������:DRC_BASE64
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
IRESULT DRC_BASE64(HXMLTREE lXmlhandle)
{
	int	nRet = -1;
	int	nLenDes = -1;
	int	nLenBase64 = -1;
	char	sSrcData[1024] ;
	char	sDesData[1024] ;
	char	sFlag[10] ;
	char	*pTemp = NULL;

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
	memset(sFlag,0x00,sizeof(sFlag));
	COMP_GETPARSEPARAS(1, sFlag, "��ֵ����ʽ");
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("flag[%s]", sFlag), __func__)
#endif	
	/*��ȡ�������:Դ�ļ�·��*/
	memset(sSrcData,0x00,sizeof(sSrcData));
	COMP_GETPARSEPARAS(2, sSrcData, "��ֵ����ʽ");
	LOG(LM_DEBUG, Fmtmsg("SrcData[%s]", sSrcData), __func__)

	/*��ȡ�������:Ŀ���ļ�·��*/
	memset(sDesData,0x00,sizeof(sDesData));
	COMP_GETPARSEPARAS(3, sDesData, "��ֵ����ʽ");
	LOG(LM_DEBUG, Fmtmsg("DestData[%s]", sDesData), __func__)

	nLenDes = strlen(sSrcData) ;

	if ( sFlag[0] == '0' )
	{	
		/*BASE64����*/
		pTemp=base64_encode(sSrcData,nLenDes,&nLenBase64);
		if( NULL == pTemp)
		{
			LOG(LM_DEBUG, Fmtmsg("BASE64���ܴ���"), __func__)
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
	}	
	if ( sFlag[0] == '1' )
	{	
		/*BASE64����*/
		pTemp=base64_decode(sSrcData,nLenDes,&nLenBase64);
		if( NULL == pTemp)
		{
			LOG(LM_DEBUG, Fmtmsg("BASE64�������"), __func__)
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
	}	

	LOG(LM_DEBUG, Fmtmsg("pTemp[%s][%ld]", pTemp, strlen(pTemp)), __func__)

//	if(xml_SetBinElement(lXmlhandle,sDesData,pTemp,strlen(pTemp)) < 0)
//	if (xml_SetElement(lXmlhandle, sDesData, pTemp) == -1)
	if(xml_SetElement(lXmlhandle, sDesData, pTemp)<0)
	{
		/*LOG(LM_DEBUG,Fmtmsg("��ֵ����ʧ��"),"ERROR");*/
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(-1,LM_STD,Fmtmsg("��ֵ����ʧ��"),"ERR");
	}

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
