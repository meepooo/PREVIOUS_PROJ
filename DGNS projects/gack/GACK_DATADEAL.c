/***********************************************************************
 * 动态组件函数定义
 * 组件函数名称:GACK_DATADEAL
 * 组件名称: 删除纯数字节点
 * 组件功能:
 * 组件参数列表：
 * 序号  参数类型  参数名称     资源类别    缺省值        可空      参数说明
 * 1     文件名称
 * 组件结果状态:
 * 结果状态码          结果说明
 * -9999               缺省
 * 0                   成功
 * 日志信息:
 * 日志级别                          日志宏
 * 响应信息:
 * 内部响应码               内部响应信息
 * 主要操作元素:
 * 元素路径                   操作
 * 主要操作库表:
 * 表名                   操作
 * 使用限制:
 * 项 目 组:
 * 程 序 员:zhouff
 * 发布日期:2013-1-24 18:39:13
 * 修改日期:
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
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif

    /* 获取模式 */
    memset(s_ms,0x00,sizeof(s_ms));
    COMP_GETPARSEPARAS(1,s_ms,"模式")
    trim(s_ms);

    memset(sFileName,0x00,sizeof(sFileName));
    COMP_GETPARSEPARAS(2,sFileName,"文件名")
    trim(sFileName);

    memset(sXmlNode,0x00,sizeof(sXmlNode));
    COMP_GETPARSEPARAS(3,sXmlNode,"XML节点名")
    trim(sXmlNode);

    iLen= xml_GetBinElementLen( lXmlhandle, "/commbuf") ;
    if(iLen < 0 )
    {
        LOG(LM_DEBUG,Fmtmsg("取通讯报文长度失败"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("取通讯报文长度失败"),"ERR");
    }
    LOG(LM_DEBUG,Fmtmsg("报文长度[%ld]",iLen),"DEBUG");
    instr = ( char *) malloc( iLen + 1 ) ;
    if( instr == NULL )
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("分配内存失败"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("分配内存失败"),"ERR");
    }
    memset( instr, 0x00, iLen + 1 );
    if(xml_GetBinElement(lXmlhandle,"/commbuf",instr,iLen +1 ) < 0)
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("取值报文失败"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("取值报文失败"),"ERR");
    }
    *(instr+iLen) = 0 ;
    if( 0 )
    {
         fp=fopen("/home/hsgaps/log/pkg.txt","wt");
         fprintf(fp,"%s\n",instr);
         fclose(fp);
         LOG(LM_DEBUG,Fmtmsg("转换前报文[%s]",instr),"DEBUG");
    }
     /* 判断报文是否为空 */
    if(strlen(instr) ==0)
    {
        free(instr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("报文不能为空!"),"ERR");
    }

    outstr = ( char *) malloc( MAX_LENGTH ) ;
    if( instr == NULL )
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("分配内存失败"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("分配内存失败"),"ERR");
    }

    if ((fp = fopen(sFileName, "rb")) == NULL)
    {
	free(instr);
	free(outstr);
	LOG(LM_DEBUG,Fmtmsg("打开文件失败"),"ERROR");
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	LOGRET(-1,LM_STD,Fmtmsg("打开文件失败"),"ERR");
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
            LOG(LM_STD,Fmtmsg("组件[%s] decrypt3des exec error",fpub_GetCompname(lXmlhandle)),__func__)
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
	    LOG(LM_DEBUG, Fmtmsg("BASE64加密错误"), __func__)
	    free(instr);
	    free(outstr);
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
	}
LOG(LM_DEBUG,Fmtmsg("AAAAAAAAAAAAAAAAAAAAAAAAAA[%ld][%ld]执行开始", iLen, iRet),"")
	iLen = strlen(outdata) ;
LOG(LM_DEBUG,Fmtmsg("AAA[%s][%ld][%s]", sFileContent, iLen, outdata),"")
*/

	/*BASE64加密*/
	pTemp=base64_encode(sFileContent,iLen,&iRet);
	//pTemp=base64_encode(outdata,iLen,&iRet);
	//pTemp=base64_encode("12345678",8,&iRet);
	if( NULL == pTemp)
	{
	    LOG(LM_DEBUG, Fmtmsg("BASE64加密错误"), __func__)
	    free(instr);
	    free(outstr);
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
	}

	iRet=CreateXml(instr,outstr,pTemp,sXmlNode);
	if(iRet)
	{
            LOG(LM_DEBUG,"报文转换失败","ERROR");
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
        LOGRET(-1,LM_STD,Fmtmsg("不支持此模式"),"ERR");
	return -1;
    }

    free(instr);
    /*COMP_SOFTSETXML("/commbuf",outstr);*/
    if(xml_SetBinElement(lXmlhandle,"/commbuf",outstr,strlen(outstr)) < 0)
    {
        /*LOG(LM_DEBUG,Fmtmsg("赋值报文失败"),"ERROR");*/
    	free(outstr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("赋值报文失败"),"ERR");
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
