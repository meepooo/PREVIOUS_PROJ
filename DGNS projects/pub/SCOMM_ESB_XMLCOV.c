/***********************************************************************
 * ��Ȩ����:�������ӹɷ����޹�˾
 * ��Ŀ����:̨�������м�ҵ��ƽ̨
 * ��    ��:V1.00
 * ����ϵͳ:
 * �� �� ��:SCOMM_ESB_XMLCOV.c
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
#define ESB_CFGNUM 2048
#define INI_FILENAME "esb_field.cfg"


/***********************************************************************
 * ��̬�����������
 * �����������:SCOMM_ESB_XMLCOV
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
 * ��־����            ��־��
 * ��Ӧ��Ϣ:
 * �ڲ���Ӧ��          �ڲ���Ӧ��Ϣ
 * ��Ҫ����Ԫ��:
 * Ԫ��·��            ����
 * ��Ҫ�������:
 * ����                ����
 * ʹ������:
 * �� Ŀ ��:
 * �� �� Ա:zhouff
 * ��������:2013-1-24 18:39:13
 * �޸�����:
 ************************************************************************/

char name[200][100];

int id=0;

struct esbxml
{
    int xh;
    char node[30];
    char stype[20];
    char slength[20];
    char sscale[20];
    char spin[10];
};

struct esbxml *esbcfgptr, esbcfg[ESB_CFGNUM], esbtran[ESB_CFGNUM];
int trannum=0 ;

int ESBtoHS(char *in ,char *out)
{
    char value[1024];
    char *p1,*p2;
    int i=0,j=0;
    int len=0;

    p1=in;

    for( ; *p1!=0 ; )
    {
        if(strlen(p1)>=5)
        {
            if(memcmp(p1,"<data",5) == 0)
            {
                len = getname(p1,name[id]);
                strcat(out,"<");
                j++;
                strcat(out,name[id]);
                j = j + strlen(name[id]);
                strcat(out,">");
                j++;
                id++;
                p1= p1 + len + 2;   /* ���� "">" ���� */
                memset(value,0,sizeof(value));
                len=getvalue(p1,value);   /* ��ȡ�� "</field>"ǰ���� */
                /*fprintf(stderr,"��ȡ[%ld]�ֶ�[%s]ֵ[%s],����[%ld]\n",id-1,name[id-1],value,len);*/
                if(len > 0) /* ���������field */
                {
                    strcat(out,value);
                    j=j+strlen(value);
                    p1=p1+len+8;
                    while((*p1 != '<') && (*p1 != 0))
                    {
                        p1++;
                    }
                }/*
                else
                {
                    out[j]='\n';
                    j++;
                }*/
            }
            else if(memcmp(p1,"</data",6) == 0)
            {
                strcat(out,"</");
                j=j+2;
                id--;
                strcat(out,name[id]);
                j=j+strlen(name[id]);
                strcat(out,">");
                j=j+1;
                /*strcat(out,">\n");
 *                 j=j+2;*/
                p1=p1+7;
            }
            else
            {
                /*if( *p1==10 || *p1==13)
 *                 ;
 *                                 else
 *                                                 {
 *                                                                     out[j]=*p1;
 *                                                                                         j++;
 *                                                                                                         }
 *                                                                                                                         p1++;*/
                if(*p1==10 || *p1==13)
                ;
                else if(*p1 == '>' && *(p1-1) == '?')
                {
                    out[j]=*p1;
                    j++;
                    out[j]='\n';
                    j++;
                }
                else
                {
                    out[j]=*p1;
                    j++;
                }
                p1++;
            }
        }
        else
        {
            out[j]=*p1;
            j++;
            p1++;
        }
    }
    return 0;
}
/*ESBtoHSʹ��*/
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
/*ESBtoHSʹ��*/
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

int HStoESB(char *pin ,char *out)
{
    char node[255];
    char nodevalue[255];
    char *value=NULL;
    char *ptr=NULL;
    int i=0,j=0;
    int len=0;
    int flag=0;
    int iNum=0;

    char ESBstring[15][20]={"service", "sys-header", "array", "struct", "app-header", "local-header", "body", "/service", "/sys-header", "/array", "/struct", "/app-header", "/local-header", "/body"};

    for( ; *pin !=0 ; )
    {
	flag = 0 ;
/*
printf(":%ld:%s\n", __LINE__, out) ;
printf("zzz:j=%ld,pin=%ld,%c--node=%s\n", j,*pin,*pin,node) ;
*/
        if(*pin == '<' && *(pin+1) != '?')
        {
//sleep(1);
            memset(node,0,sizeof(node));
            len= getnode(pin,node);

	    for (i=0; i<14; i++)
	    {
                if(memcmp(pin+1,ESBstring[i],len=strlen(ESBstring[i]))== 0)
		{
		    memcpy(out+j, pin, len+2) ;
		    j = j+len+2;
		    pin=pin+len+2;
		    flag = 1 ;
		    break ;
		}
	    }

	    if ( flag == 1 )
	    {
		continue ;
	    }

	    if ( *(pin+1) == '/' )
	    {
	    	iNum = findEsbXml(node+1, esbcfgptr, 0) ;
//printf(":%ld:%s---%ld\n", __LINE__, node+1, iNum) ;
		if ( iNum > 0 )
		{
		    memcpy(out+j, "</field>", 8);
		    j = j + 8 ;
		}

		memcpy(out+j, "</data>", 7);
		pin = pin + strlen(node) + 2 ;
		j = j + 7 ;
		continue ;
	    }

	    iNum = findEsbXml(node, esbcfgptr, 0) ;
	    if ( iNum <= 0 )
	    {
		sprintf(out+j, "<data name=\"%s\">", node);
		len = strlen(node) ;
		j = j + len + 14 ;
		pin = pin + len + 2 ;
		continue ;
	    }
	    else
	    {
		memset(nodevalue, 0, sizeof(nodevalue)) ;
		sprintf(nodevalue, "<data name=\"%s\"><field type=\"%s\" length=\"%s\" scale=\"%s\" pin=\"%s\">",
		    node, esbcfg[iNum].stype, esbcfg[iNum].slength,
		    esbcfg[iNum].sscale, esbcfg[iNum].spin);
		len = strlen(nodevalue) ;
		memcpy(out+j,nodevalue,len);    
		pin = pin + strlen(node) + 2 ;
		j = j + len ;

		ptr = strstr(pin, "<") ;
		len = ptr - pin ;
		if ((0 == strncmp(esbcfg[iNum].stype,"int",sizeof("int")) || 0 == strncmp(esbcfg[iNum].stype,"double",sizeof("double"))))
		{
		    if ( len == 0 )
		    {
			memcpy(out+j, "0", 1) ;
			pin = ptr ;
			j ++ ;
		    }
		}
		continue ;

	    }

	    memcpy(out+j,pin,len);    
	    pin = pin + len ;
	    j = j + len ;
        }
        else
        {
		out[j] = *pin ;
		j ++ ;
		pin ++ ;
        }
    }
    return 0;
}

/*HStoESBʹ��*/
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
/*HStoESBʹ��*/
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

/*HStoESBʹ��*/
int processnode(char *node, char *nodestart, char *nodeend)
{
    int iRet, iNum;
    char sValue[255];
    char stype[20],slength[20],sscale[20],spin[10];

    sValue[0] = 0 ;
    iNum = findEsbXml(node, esbcfgptr, 0) ;
    if ( iNum <= 0 )
    {
	sprintf(nodestart, "<data name=\"%s\">", node);
	memcpy(nodeend, "</data>", 7);
        return 0;
    }

/*
    if (0 == strlen(alltrim(nodevalue))&&(0 == strncmp(stype,"int",sizeof("int"))||0 == strncmp(stype,"double",sizeof("double"))))
    {
	sValue[0] = '0' ;
	sValue[1] = 0 ;
    }
*/

    sprintf(nodestart, "<data name=\"%s\"><field type=\"%s\" length=\"%s\" scale=\"%s\" pin=\"%s\">",
	esbcfg[iNum].node, esbcfg[iNum].stype, esbcfg[iNum].slength,
	esbcfg[iNum].sscale, esbcfg[iNum].spin);
    memcpy(nodeend,"</field></data>",15);    

    return 0;
}

int findEsbXml(char *node, struct esbxml *esbcfgptr, int flag)
{
    int iRet,i;
    char *ptr=NULL;

    esbcfgptr = esbcfg ;
    for(i=0; i<ESB_CFGNUM; i++,esbcfgptr++)
    {
	if (0==strcmp(node, esbcfgptr->node))
	{
//	    LOG(LM_DEBUG,Fmtmsg("esbcfgptr[%ld][%s][%s][%s][%s][%s]",esbcfgptr->xh,esbcfgptr->node,esbcfgptr->stype,esbcfgptr->slength,esbcfgptr->sscale,esbcfgptr->spin),"DEBUG");
	    return esbcfgptr->xh ;
	}
    }

    if ( 1==flag )
	return 0 ;

    esbcfgptr = esbcfg ;
    for(i=0; i<ESB_CFGNUM; i++,esbcfgptr++)
    {
	ptr=strstr(esbcfgptr->node, node) ;
	if ( ptr!=NULL && memcmp(ptr, node, strlen(ptr))==0 )
	{
//	    LOG(LM_DEBUG,Fmtmsg("esbcfgptr[%ld][%s][%s][%s][%s][%s]",esbcfgptr->xh,esbcfgptr->node,esbcfgptr->stype,esbcfgptr->slength,esbcfgptr->sscale,esbcfgptr->spin),"DEBUG");
	    return esbcfgptr->xh ;
	}
    }

    return 0 ;

/*
    int iRet,i;

    esbcfgptr = esbtran ;
    esbcfgptr++ ;
    for(i=1; i<ESB_CFGNUM && esbcfgptr->xh>0; i++,esbcfgptr++)
    {
	if (0==strcmp(node, esbcfgptr->node))
	{
//	    LOG(LM_DEBUG,Fmtmsg("esbcfgptr[%ld][%s][%s][%s][%s][%s]",esbcfgptr->xh,esbcfgptr->node,esbcfgptr->stype,esbcfgptr->slength,esbcfgptr->sscale,esbcfgptr->spin),"DEBUG");
	    return esbcfgptr->xh ;
	}
    }

    esbcfgptr = esbcfg ;
    esbcfgptr++ ;
    for(i=1; i<ESB_CFGNUM && esbcfgptr->xh>0; i++,esbcfgptr++)
    {
	if (0==strcmp(node, esbcfgptr->node))
	{
//	    LOG(LM_DEBUG,Fmtmsg("esbcfgptr[%ld][%s][%s][%s][%s][%s]",esbcfgptr->xh,esbcfgptr->node,esbcfgptr->stype,esbcfgptr->slength,esbcfgptr->sscale,esbcfgptr->spin),"DEBUG");
		esbtran[i].xh=esbcfgptr->xh;
	    strcpy(esbtran[i].node, esbcfgptr->node);
	    strcpy(esbtran[i].stype, esbcfgptr->stype);
	    strcpy(esbtran[i].slength, esbcfgptr->slength);
	    strcpy(esbtran[i].sscale, esbcfgptr->sscale);
	    strcpy(esbtran[i].spin, esbcfgptr->spin);
	    return esbcfgptr->xh ;
	}
    }

    return 0 ;
*/
}

int esb_putcfg(struct esbxml *esbcfgptr)
{
    int iRet,i;
    char sValue[255];
    FILE *fp;
    char *ptr;
    char sFileName[256];

    memset(sFileName, 0, sizeof(sFileName)) ;
    sprintf(sFileName, "%s/etc/%s", getenv("HOME"), INI_FILENAME);

    for (i=0; i<ESB_CFGNUM; i++)
    {
	esbcfg[i].xh=0;
	esbtran[i].xh=0;
    }

    if ((fp = fopen(sFileName, "rb")) == NULL)
    {
//	LOG(LM_DEBUG,Fmtmsg("�����ļ���[%s]",sFileName),"DEBUG");
	return -1;
    }

    memset(sValue, 0, sizeof(sValue));
    i = 0 ;
    while(fgets(sValue, 1024, fp) != NULL)
    {
        if ((ptr = strstr(sValue, "=")) == NULL )
		continue ;

	i++ ;
	esbcfgptr++ ;
	esbcfgptr->xh=i;
	memcpy(esbcfgptr->node, sValue, ptr-sValue) ;
	GetListbyDiv(ptr+1,1,esbcfgptr->stype,'|','\\');
	GetListbyDiv(ptr+1,2,esbcfgptr->slength,'|','\\');
	GetListbyDiv(ptr+1,3,esbcfgptr->sscale,'|','\\');
	GetListbyDiv(ptr+1,4,esbcfgptr->spin,'|','\\');
//	LOG(LM_DEBUG,Fmtmsg("esbcfgptr[%ld][%s][%s][%s][%s][%s]",esbcfgptr->xh,esbcfgptr->node,esbcfgptr->stype,esbcfgptr->slength,esbcfgptr->sscale,esbcfgptr->spin),"DEBUG");
    }

    fclose(fp);
    return 0;
}

IRESULT SCOMM_ESB_XMLCOV(HXMLTREE lXmlhandle)
{
    char outstr[MAX_LENGTH + 1];
    char *instr;
    char s_ms[1+1];
    int iParas,iRet;
    int iLen;
    FILE *fp;

    esbcfgptr = esbcfg ;
    esb_putcfg(esbcfgptr) ;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif

    COMP_PARACOUNTCHK(1);

    /* ��ȡģʽ */
    memset(s_ms,0x00,sizeof(s_ms));
    COMP_GETPARSEPARAS(1,s_ms,"ģʽ")
    trim(s_ms);

    /* �ж�ģʽ�Ƿ�Ϊ�� */
    if(strlen(s_ms) ==0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        /*fpub_SetMsg(lXmlhandle,atol(BS_ERR_NOBLANK),Fmtmsg("ģʽ����Ϊ��!"));*/
        LOGRET(-1,LM_STD,Fmtmsg("ģʽ����Ϊ��!"),"ERR");
    }

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
        iRet=ESBtoHS(instr,outstr);
        /*LOG(LM_DEBUG,Fmtmsg("ת������[%s]",outstr),"DEBUG");*/
    }
    else if(s_ms[0] == '1')
    {
        iRet=HStoESB(instr,outstr);
        /*
 	 LOG(LM_DEBUG,Fmtmsg("ת������[%s]",outstr),"DEBUG");
         fp=fopen("/home/gapsv4/test/result.xml","a+");
         fprintf(fp,"%s\n",outstr);
         fclose(fp);
	*/
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
