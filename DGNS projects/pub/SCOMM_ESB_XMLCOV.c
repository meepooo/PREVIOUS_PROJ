/***********************************************************************
 * 版权所有:恒生电子股份有限公司
 * 项目名称:台州银行中间业务平台
 * 版    本:V1.00
 * 操作系统:
 * 文 件 名:SCOMM_ESB_XMLCOV.c
 * 文件描述:台州银行中间业务
 * 项 目 组:
 * 程 序 员:[ZFF]
 * 创建时间:2013-1-24 18:37:39
 * 修    订:
 * 修改时间:
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
 * 动态组件函数定义
 * 组件函数名称:SCOMM_ESB_XMLCOV
 * 组件名称:台州银行XML报文转换
 * 组件功能:
 * 组件参数列表：
 * 序号  参数类型  参数名称     资源类别    缺省值        可空      参数说明
 * 1     文件名称
 * 组件结果状态:
 * 结果状态码          结果说明
 * -9999               缺省
 * 0                   成功
 * 日志信息:
 * 日志级别            日志宏
 * 响应信息:
 * 内部响应码          内部响应信息
 * 主要操作元素:
 * 元素路径            操作
 * 主要操作库表:
 * 表名                操作
 * 使用限制:
 * 项 目 组:
 * 程 序 员:zhouff
 * 发布日期:2013-1-24 18:39:13
 * 修改日期:
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
                p1= p1 + len + 2;   /* 增加 "">" 长度 */
                memset(value,0,sizeof(value));
                len=getvalue(p1,value);   /* 获取到 "</field>"前长度 */
                /*fprintf(stderr,"获取[%ld]字段[%s]值[%s],长度[%ld]\n",id-1,name[id-1],value,len);*/
                if(len > 0) /* 后面跟着是field */
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
/*ESBtoHS使用*/
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
/*ESBtoHS使用*/
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

/*HStoESB使用*/
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
/*HStoESB使用*/
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

/*HStoESB使用*/
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
//	LOG(LM_DEBUG,Fmtmsg("配置文件错[%s]",sFileName),"DEBUG");
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
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif

    COMP_PARACOUNTCHK(1);

    /* 获取模式 */
    memset(s_ms,0x00,sizeof(s_ms));
    COMP_GETPARSEPARAS(1,s_ms,"模式")
    trim(s_ms);

    /* 判断模式是否为空 */
    if(strlen(s_ms) ==0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        /*fpub_SetMsg(lXmlhandle,atol(BS_ERR_NOBLANK),Fmtmsg("模式不能为空!"));*/
        LOGRET(-1,LM_STD,Fmtmsg("模式不能为空!"),"ERR");
    }

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
        LOG(LM_DEBUG,Fmtmsg("分配内存失败"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("分配内存失败"),"ERR");
    }
    memset( instr, 0x00, iLen + 1 );
    if(xml_GetBinElement(lXmlhandle,"/commbuf",instr,iLen +1 ) < 0)
    {
        LOG(LM_DEBUG,Fmtmsg("取值报文失败"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("取值报文失败"),"ERR");
    }
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
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("报文不能为空!"),"ERR");
    }

    memset(outstr,0x00,sizeof(outstr));

    if(s_ms[0] == '0')
    {
        iRet=ESBtoHS(instr,outstr);
        /*LOG(LM_DEBUG,Fmtmsg("转换后报文[%s]",outstr),"DEBUG");*/
    }
    else if(s_ms[0] == '1')
    {
        iRet=HStoESB(instr,outstr);
        /*
 	 LOG(LM_DEBUG,Fmtmsg("转换后报文[%s]",outstr),"DEBUG");
         fp=fopen("/home/gapsv4/test/result.xml","a+");
         fprintf(fp,"%s\n",outstr);
         fclose(fp);
	*/
    }
    else
    {
        /*LOG(LM_DEBUG,Fmtmsg("模式错误【%s】",s_ms),"DEBUG");*/
        free(instr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       
        LOGRET(-1,LM_STD,Fmtmsg("模式错误【%s】",s_ms),"ERR");
    }

    if(iRet)
    {
        /*LOG(LM_DEBUG,"报文转换失败","ERROR");*/
        free(instr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("报文转换失败"),"ERR");
    }
    free(instr);
    /*COMP_SOFTSETXML("/commbuf",outstr);*/
    if(xml_SetBinElement(lXmlhandle,"/commbuf",outstr,strlen(outstr)) < 0)
    {
        /*LOG(LM_DEBUG,Fmtmsg("赋值报文失败"),"ERROR");*/
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("赋值报文失败"),"ERR");
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
