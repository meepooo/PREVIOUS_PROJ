/***********************************************************************
 * ��̬�����������
 * �����������:GACK_DATADEAL
 * �������: ɾ�������ֽڵ�
 * �������:
 * ��������б�
 * ���  ��������  ��������     ��Դ���    ȱʡֵ        �ɿ�      ����˵��
 * 1     �ļ�����
 * ������״̬:
 * ���״̬��          ���˵��
 * -9999               ȱʡ
 * 0                   �ɹ�
 * ��־��Ϣ:
 * ��־����                          ��־��
 * ��Ӧ��Ϣ:
 * �ڲ���Ӧ��               �ڲ���Ӧ��Ϣ
 * ��Ҫ����Ԫ��:
 * Ԫ��·��                   ����
 * ��Ҫ�������:
 * ����                   ����
 * ʹ������:
 * �� Ŀ ��:
 * �� �� Ա:zhouff
 * ��������:2013-1-24 18:39:13
 * �޸�����:
 * ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"

#define MAX_LENGTH 2048000

IRESULT GACK_DATADEAL(HXMLTREE lXmlhandle)
{
//    char outstr[MAX_LENGTH + 1];
    char *instr;
    char *outstr;
    int iParas,iRet;
    int iLen;
    FILE *fp;
    char s_ms[10];
    char sFileName[256];
    char sXmlNode[256];
    char sFileContent[MAX_LENGTH];
    char outdata[MAX_LENGTH];
    char *pTemp=NULL ;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif

    /* ��ȡģʽ */
    memset(s_ms,0x00,sizeof(s_ms));
    COMP_GETPARSEPARAS(1,s_ms,"ģʽ")
    trim(s_ms);

    memset(sFileName,0x00,sizeof(sFileName));
    COMP_GETPARSEPARAS(2,sFileName,"�ļ���")
    trim(sFileName);

    memset(sXmlNode,0x00,sizeof(sXmlNode));
    COMP_GETPARSEPARAS(3,sXmlNode,"XML�ڵ���")
    trim(sXmlNode);

    iLen= xml_GetBinElementLen( lXmlhandle, "/commbuf") ;
    if(iLen < 0 )
    {
        LOG(LM_DEBUG,Fmtmsg("ȡͨѶ���ĳ���ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("ȡͨѶ���ĳ���ʧ��"),"ERR");
    }
    LOG(LM_DEBUG,Fmtmsg("���ĳ���[%ld]",iLen),"DEBUG");
    instr = ( char *) malloc( iLen + 1 ) ;
    if( instr == NULL )
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("�����ڴ�ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("�����ڴ�ʧ��"),"ERR");
    }
    memset( instr, 0x00, iLen + 1 );
    if(xml_GetBinElement(lXmlhandle,"/commbuf",instr,iLen +1 ) < 0)
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("ȡֵ����ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("ȡֵ����ʧ��"),"ERR");
    }
    *(instr+iLen) = 0 ;
    if( 0 )
    {
         fp=fopen("/home/hsgaps/log/pkg.txt","wt");
         fprintf(fp,"%s\n",instr);
         fclose(fp);
         LOG(LM_DEBUG,Fmtmsg("ת��ǰ����[%s]",instr),"DEBUG");
    }
     /* �жϱ����Ƿ�Ϊ�� */
    if(strlen(instr) ==0)
    {
        free(instr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("���Ĳ���Ϊ��!"),"ERR");
    }

    outstr = ( char *) malloc( MAX_LENGTH ) ;
    if( instr == NULL )
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("�����ڴ�ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("�����ڴ�ʧ��"),"ERR");
    }

    if ((fp = fopen(sFileName, "rb")) == NULL)
    {
	free(instr);
	free(outstr);
	LOG(LM_DEBUG,Fmtmsg("���ļ�ʧ��"),"ERROR");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	LOGRET(-1,LM_STD,Fmtmsg("���ļ�ʧ��"),"ERR");
	return -1;
    }

    memset(sFileContent, 0, sizeof(sFileContent)) ;
    iLen = fread(sFileContent, 1, MAX_LENGTH+1, fp) ;

/*
    while ((readLen = fread(fileCont,sizeof(char),1024,in_stream))>0)
    {
        ret = DRC_decrypt3des(dest,&outlen,fileCont,readLen,keyPasswd);
        if (ret < 0)
        {
            LOG(LM_STD,Fmtmsg("���[%s] decrypt3des exec error",fpub_GetCompname(lXmlhandle)),__func__)
            fclose(in_stream);
            fclose(out_stream);
            return ret;
        }

        len2 = fwrite(dest,sizeof(char),outlen,out_stream);
        fflush(out_stream);
    }
*/

    fclose(fp) ;

    if ( strcmp(s_ms, "1")==0 )
    {

/*
	strcpy(sFileContent, "12345678") ;
	iLen = 8 ;
	memset(outdata, 0, sizeof(outdata)) ;
LOG(LM_DEBUG,Fmtmsg("AAA[%s][%ld][%s]", sFileContent, iLen, outdata),"")
	if (DRC_convert("GB18030","UTF-8", sFileContent, iLen, outdata, &iRet) !=0)
	{
LOG(LM_DEBUG,Fmtmsg("AAA[%s][%ld][%s]", sFileContent, iLen, outdata),"")
	    LOG(LM_DEBUG, Fmtmsg("BASE64���ܴ���"), __func__)
	    free(instr);
	    free(outstr);
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
	}
LOG(LM_DEBUG,Fmtmsg("AAAAAAAAAAAAAAAAAAAAAAAAAA[%ld][%ld]ִ�п�ʼ", iLen, iRet),"")
	iLen = strlen(outdata) ;
LOG(LM_DEBUG,Fmtmsg("AAA[%s][%ld][%s]", sFileContent, iLen, outdata),"")
*/

	/*BASE64����*/
	pTemp=base64_encode(sFileContent,iLen,&iRet);
	//pTemp=base64_encode(outdata,iLen,&iRet);
	//pTemp=base64_encode("12345678",8,&iRet);
	if( NULL == pTemp)
	{
	    LOG(LM_DEBUG, Fmtmsg("BASE64���ܴ���"), __func__)
	    free(instr);
	    free(outstr);
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
	}

	iRet=CreateXml(instr,outstr,pTemp,sXmlNode);
	if(iRet)
	{
            LOG(LM_DEBUG,"����ת��ʧ��","ERROR");
	    free(instr);
	    free(outstr);
	    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
	}
    }
    else
    {
    	free(outstr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("��֧�ִ�ģʽ"),"ERR");
	return -1;
    }

    free(instr);
    /*COMP_SOFTSETXML("/commbuf",outstr);*/
    if(xml_SetBinElement(lXmlhandle,"/commbuf",outstr,strlen(outstr)) < 0)
    {
        /*LOG(LM_DEBUG,Fmtmsg("��ֵ����ʧ��"),"ERROR");*/
    	free(outstr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("��ֵ����ʧ��"),"ERR");
    }
    free(outstr);

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

int CreateXml(char *pin ,char *out, char *sFileContent, char *sXml)
{
    char *ptr1=NULL;
    char *ptr2=NULL;
    char sXml1[256] ;
    char sXml2[256] ;
    int iLen=0 ;
    int iSize=0 ;

    memset(sXml1, 0, sizeof(sXml1)) ;
    memset(sXml2, 0, sizeof(sXml2)) ;

    sprintf(sXml1, "<%s", sXml) ;
    if ((ptr1 = strstr(pin, sXml1)) == NULL )
	return -1 ;

    iLen = ptr1 - pin ;
    memcpy(out+iSize, pin, iLen) ;
    iSize += iLen ;

    pin = ptr1 ;
    if ((ptr1 = strstr(pin, ">")) == NULL )
	return -1 ;

    iLen = ptr1 - pin + 1;
    memcpy(out+iSize, pin, iLen) ;
    iSize += iLen ;
    iLen = strlen(sFileContent) ;
    memcpy(out+iSize, sFileContent, iLen);
    iSize += iLen ;

    sprintf(sXml2, "</%s", sXml) ;
    if ((ptr2 = strstr(pin, sXml2)) == NULL )
	return -1 ;

    iLen = ptr1 - pin ;
    memcpy(out+iSize, ptr2, iLen) ;
    iSize += iLen ;

    return 0;
}
