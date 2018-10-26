/***********************************************************************
 * ��Ȩ����:�������ӹɷ����޹�˾
 * ��Ŀ����:̨�������м�ҵ��ƽ̨
 * ��    ��:V1.00
 * ����ϵͳ:
 * �� �� ��:SCOMM_GACK_XMLCOV.c
 * �ļ�����:̨�������м�ҵ��
 * �� Ŀ ��:
 * �� �� Ա:[ZFF]
 * ����ʱ��:2013-1-24 18:37:39
 * ��    ��:
 * �޸�ʱ��:
 * ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"

#define MAX_LENGTH 5120000


/***********************************************************************
 * ��̬�����������
 * �����������:SCOMM_GACK_XMLCOV
 * �������:̨������XML����ת��
 * �������:
 * ��������б�
 * ���  ��������  ��������     ��Դ���    ȱʡֵ        �ɿ�      ����˵��
 * 1     �ļ�����
 * ������״̬:
 * ���״̬��          ���˵��
 * -9999               ȱʡ
 * 0                   �ɹ�
 * ��־��Ϣ:
 * ��־����                                                                              ��־��
 * ��Ӧ��Ϣ:
 * �ڲ���Ӧ��                                                                           �ڲ���Ӧ��Ϣ
 * ��Ҫ����Ԫ��:
 * Ԫ��·��                                                                               ����
 * ��Ҫ�������:
 * ����                                                                               ����
 * ʹ������:
 * �� Ŀ ��:
 * �� �� Ա:zhouff
 * ��������:2013-1-24 18:39:13
 * �޸�����:
 ************************************************************************/

char name[200][100];
char node[255];
char sValue[255];

int id=0;

int GACKtoHS(char *in ,char *out)
{
    char *p1,*p2;
    int len=0;
    char *p3=NULL;
    char *p4=NULL;
    char sTmp[255];

    len = strlen(sValue) ;

    memset(sTmp, 0, sizeof(sTmp)) ;
    sprintf(sTmp, "<%s", node) ;
    p1=strstr(in, sTmp) ;
    memset(sTmp, 0, sizeof(sTmp)) ;
    sprintf(sTmp, "%s=\"", sValue) ;
    p2=strstr(p1, sTmp) ;
    p3=strstr(p2+len+2, "\"") ;

    memcpy(out, p2+6, p3-p2-6);

    return 0;
}
/*GACKtoHSʹ��*/
int getname(char *sSrc,char *rest)
{
    char *p;
    int i=0,k=0;
    int flag=0;
    char sname[100];

    p = sSrc;
    for(;*p!=0;p++,k++)
    {
        if((!flag)&&(*p=='"'))
        {
            flag=1;
            continue;
        }
        if(flag == 1)
        {
            if(*p == '"')
            {
                flag=2;
                continue;
                /*break;*/
            }
            sname[i]=*p;
            i++;
            continue;
        }
        if(flag == 2)
        {
            if(*p!='>')
            {
                sname[i]=*p;
                i++;
                continue;
            }
            else
            {
                k--;
                break;
            }
        }
    }
    sname[i]=0;
    strcpy(rest,sname);
    return k;
}
/*GACKtoHSʹ��*/
int getvalue(char *sSrc,char *value)
{
    char *p;
    int i = 0,k = 0;
    int flag = 0;
    char sname[1024];

    memset(sname,0,sizeof(sname));
    p = sSrc;
    for( ; *p!=0;p++,k++)
    {
        if((flag == 0)&&(*p == '<'))
        {
            flag = 1;
            continue;
        }

        if(flag == 1)
        {
            if(memcmp(p,"field",5) == 0)
            {
                flag = 2;
                continue;
            }
            else
            {
                flag = 0;
                break;
            }
            continue;
        }

        if(flag == 2)
        {
            if(*p == '/')
            {
                flag = 3;
                break;
            }
            if(*p == '>')
            {
                flag = 3;
            }
            continue;
        }

        if(flag == 3)
        {
            if(*p == '<')
            {
                break;
            }
            sname[i] = *p;
            i++;
            continue;
        }
    }
    sname[i] = 0;
    strcpy(value,sname);
    if(flag != 3)
    {
        k=0;
    }
    return k;
}

/*HStoGACKʹ��*/
int getnode(char *sSrc,char *node)
{
    char *p;
    int i=0,k=0;
    int flag=0;
    char *snode=NULL;

		snode=malloc(strlen(sSrc));
    memset(snode,0,sizeof(snode));
    p = sSrc;
    for( ; ;p++,k++)
    {
        if((flag == 0)&&(*p == '<'))
        {
            flag = 1;
            continue;
        }
        if(flag == 1)
        {
            if(*p == '>')
                break;
            snode[i] = *p;
            i++;
            continue;
        }
    }
    snode[i] = 0;
    strcpy(node,snode);
    free(snode);
    snode=NULL;
    return k;
}
/*HStoGACKʹ��*/
int getnodevalue(char *sSrc,char *value)
{
    char *p;
    int i=0,k=0;
    int flag=0;
    char *snode=NULL;
		
		snode=malloc(strlen(sSrc));
    memset(snode,0,sizeof(snode));
    p = sSrc;
    for(;*p!=0;p++,k++)
    {
        if(*p=='<')
        {
            break;
        }
        snode[i]=*p;
        i++;
    }
    snode[i]=0;
    strcpy(value,snode);
    free(snode);
    snode=NULL;
    return k;
}

int HStoGACK(char *pin ,char *out)
{
    char *p=NULL;
    char sNode[255];
    char sTmp[255];
    int ilen1=0;
    int ilen2=0;
    int ilen3=0;

    memset(sNode,0,sizeof(sNode));
    memset(sTmp, 0, sizeof(sTmp)) ;

    sprintf(sNode, "<%s>", node) ;

    p=strstr(pin, sNode);
    sprintf(sTmp, "<%s %s>", node, sValue) ;

    ilen1=p-pin;
    ilen2=strlen(sTmp);
    ilen3=strlen(node);
    memcpy(out, pin, ilen1);
    memcpy(out+ilen1, sTmp, ilen2);
    strcpy(out+ilen1+ilen2, p+ilen3+2 );

    return 0;
/*
    char sNode[255];
    char sTmp[255];
    int i=0,j=0;
    int len=0;

    for( ; *pin !=0 ; )
    {
        if(*pin == '<' && *(pin+1) != '?')
        {
	    memset(sNode,0,sizeof(sNode));
            len= getnode(pin,sNode);
            if(strcmp(sNode,node)==0)
            {
		memset(sTmp, 0, sizeof(sTmp)) ;
		sprintf(sTmp, "<%s %s", node, sValue) ;
		strcat(out, sTmp) ;
		len= strlen(sNode);
                pin = pin + len + 1;
		j += strlen(sTmp) ;
            }
            else
            {
                out[j] = *pin;
                j++;
                pin++;
            }
        }
        else
        {
            out[j] = *pin;
            j++;
            pin++;
        }
    }
    return 0;
*/
}

IRESULT SCOMM_GACK_XMLCOV(HXMLTREE lXmlhandle)
{
    char outstr[MAX_LENGTH + 1];
    char *instr;
    char s_ms[1+1];
    char sTmp[256] ;
    int iParas,iRet;
    int iLen;
    FILE *fp;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif

    COMP_PARACOUNTCHK(3);

    /* ��ȡģʽ */
    memset(s_ms,0x00,sizeof(s_ms));
    COMP_GETPARSEPARAS(1,s_ms,"ģʽ")
    trim(s_ms);

    memset(node,0x00,sizeof(node));
    COMP_GETPARSEPARAS(2,node,"�ڵ�")
    trim(node);

    memset(sValue,0x00,sizeof(sValue));
    COMP_GETPARSEPARAS(3,sValue,"ֵ")
    trim(sValue);

    /* �ж�ģʽ�Ƿ�Ϊ�� */
    if(strlen(s_ms) ==0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        /*fpub_SetMsg(lXmlhandle,atol(BS_ERR_NOBLANK),Fmtmsg("ģʽ����Ϊ��!"));*/
        LOGRET(-1,LM_STD,Fmtmsg("ģʽ����Ϊ��!"),"ERR");
    }

    LOG(LM_DEBUG,Fmtmsg("ģʽ[%s]�ڵ�[%s]ֵ[%s]", s_ms, node, sValue),"DEBUG");

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
        LOG(LM_DEBUG,Fmtmsg("�����ڴ�ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("�����ڴ�ʧ��"),"ERR");
    }
    memset( instr, 0x00, iLen + 1 );
    if(xml_GetBinElement(lXmlhandle,"/commbuf",instr,iLen +1 ) < 0)
    {
        LOG(LM_DEBUG,Fmtmsg("ȡֵ����ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("ȡֵ����ʧ��"),"ERR");
    }
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
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("���Ĳ���Ϊ��!"),"ERR");
    }

    memset(outstr,0x00,sizeof(outstr));

    if(s_ms[0] == '0')
    {
        iRet=HStoGACK(instr,outstr);
        /* LOG(LM_DEBUG,Fmtmsg("ת������[%s]",outstr),"DEBUG"); */
    }
    else if(s_ms[0] == '1')
    {
        iRet=GACKtoHS(instr,outstr);
        /*LOG(LM_DEBUG,Fmtmsg("ת������[%s]",outstr),"DEBUG");*/
    }
    else
    {
        /*LOG(LM_DEBUG,Fmtmsg("ģʽ����%s��",s_ms),"DEBUG");*/
        free(instr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       
        LOGRET(-1,LM_STD,Fmtmsg("ģʽ����%s��",s_ms),"ERR");
    }

    if(iRet)
    {
        /*LOG(LM_DEBUG,"����ת��ʧ��","ERROR");*/
        free(instr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("����ת��ʧ��"),"ERR");
    }
    free(instr);

    if(s_ms[0] == '1')
    {
	memset(sTmp, 0, sizeof(sTmp)) ;
	sprintf(sTmp, "/Response/%s/%s", node, sValue) ;
	xml_SetElement(lXmlhandle, sTmp, outstr);

	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return 0;
    }

    /*COMP_SOFTSETXML("/commbuf",outstr);*/
    if(xml_SetBinElement(lXmlhandle,"/commbuf",outstr,strlen(outstr)) < 0)
    {
        /*LOG(LM_DEBUG,Fmtmsg("��ֵ����ʧ��"),"ERROR");*/
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("��ֵ����ʧ��"),"ERR");
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

int IsGB(int cText)
{
    if(cText>0 && cText < 0xa1 )
    {
        return 0;
    }
    else
        return 1;
}

int getcdatavalue(char *sSrc,char *value)
{
    char *p1;
    char *p2;
    int i = 0,k = 0;
    int flag = 0;
    char sname[1024];

    p1 = strstr(sSrc, ">") ;
    p2 = strstr(p1, "<") ;

    memcpy(value, p1+1, (int)(p2-p1-1));
    return (int)(p2-p1-1);
}

int HSaddCDATA (char *in ,char *out)
{
    char value[1024];
    char *p1,*p2;
    int i=0,j=0;
    int len=0;
    int iIsGB=0;
    char sTmp[1024];

    p1=in;

    for( ; *p1!=0 ; )
    {
        if(strlen(p1)>=5)
        {
            if(memcmp(p1,"</RESULT",8) == 0)
            {
                strcat(out,"</RESULT>");
                j=j+9;
                p1=p1+9;
		break ;
            }
            else if(memcmp(p1,">",1) == 0)
            {
		iIsGB = 0 ;

		memset(value,0,sizeof(value));
		len=getcdatavalue(p1,value);
		if(len > 0)
		{
		    for(i=0;i<len;i++)
		    {
			iIsGB+=IsGB(value[i]);
		    }

		    if (iIsGB>0)
		    {
			memset(sTmp, 0, sizeof(sTmp)) ;
			sprintf(sTmp, "><![CDATA[%s]]>", value);
			strcat(out,sTmp);
			j=j+strlen(sTmp);
			p1=p1+strlen(value);
		    }
		    else
		    {
			out[j]=*p1;
			j++;
		    }
		}
		else
		{
		    out[j]=*p1;
		    j++;
		}
	    }
	    else
	    {
		out[j]=*p1;
		j++;
	    }
	}
	else
        {
            out[j]=*p1;
            j++;
        }
	p1++ ;
    }

    return 0;
}

IRESULT SCOMM_GACK_ADDCDATA(HXMLTREE lXmlhandle)
{
    char outstr[MAX_LENGTH + 1];
    char *instr;
    char s_ms[1+1];
    char sTmp[256] ;
    int iParas,iRet;
    int iLen;
    FILE *fp;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif

    COMP_PARACOUNTCHK(1);

    memset(sTmp,0x00,sizeof(sTmp));
    COMP_GETPARSEPARAS(1,sTmp,"�ļ���")
    trim(sTmp);

    LOG(LM_DEBUG,Fmtmsg("�ļ���[%s]", sTmp),"DEBUG");

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
        LOG(LM_DEBUG,Fmtmsg("�����ڴ�ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("�����ڴ�ʧ��"),"ERR");
    }
    memset( instr, 0x00, iLen + 1 );
    if(xml_GetBinElement(lXmlhandle,"/commbuf",instr,iLen +1 ) < 0)
    {
        LOG(LM_DEBUG,Fmtmsg("ȡֵ����ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("ȡֵ����ʧ��"),"ERR");
    }
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
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("���Ĳ���Ϊ��!"),"ERR");
    }

    memset(outstr,0x00,sizeof(outstr));

LOG(LM_DEBUG,Fmtmsg("����instr[%s]", instr),"DEBUG");
    iRet=HSaddCDATA(instr,outstr);
    if(iRet)
    {
        /*LOG(LM_DEBUG,"����ת��ʧ��","ERROR");*/
        free(instr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("����ת��ʧ��"),"ERR");
    }
    free(instr);
LOG(LM_DEBUG,Fmtmsg("����outstr[%s]", outstr),"DEBUG");

    if(fp=fopen(sTmp,"wr"))
    {
	fprintf(fp,"%s\n",outstr);
	fclose(fp);
    }

    /*COMP_SOFTSETXML("/commbuf",outstr);*/
/*
    if(xml_SetBinElement(lXmlhandle,"/commbuf",outstr,strlen(outstr)) < 0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("��ֵ����ʧ��"),"ERR");
    }
*/

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
