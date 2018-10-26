/***********************************************************************
 * 动态组件函数定义
 * 组件函数名称:DATA_DELNUMNODE
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

#define MAX_LENGTH 5120000

IRESULT DATA_DELNUMNODE(HXMLTREE lXmlhandle)
{
//    char outstr[MAX_LENGTH + 1];
    char *instr;
    char *outstr;
    int iParas,iRet;
    int iLen;
    FILE *fp;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif

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

    outstr = ( char *) malloc( iLen + 1 ) ;
    if( instr == NULL )
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("分配内存失败"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("分配内存失败"),"ERR");
    }

    iRet=CreateXml(instr,outstr);
    if(iRet)
    {
        /*LOG(LM_DEBUG,"报文转换失败","ERROR");*/
        free(instr);
    	free(outstr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("报文转换失败"),"ERR");
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

int check_num( char *pin)
{
	int i=0 ;
    int len=strlen(pin);

    for ( i=0; i<len; i++ )
    {
        if ( pin[i] < '0' || pin [i] > '9' )
                return 0 ;
    }
    return 1 ;
}
int CreateXml(char *pin ,char *out)
{
    char node[255],value[1024*10];
    int i=0,j=0;
    int len=0;
    int iRet=0;

    for( ; *pin !=0 ; )
    {
        if(*pin == '<' && *(pin+1) != '?')
        {
            memset(node,0,sizeof(node));
            len= getnode(pin,node);
            if(node[0]=='/')
            {
                iRet = check_num(node+1) ;
                if( iRet == 1 )
                {
                     pin+=len;
                }
		else
		{   
		    out[j] = *pin;
		    j++ ;
                    pin++;
		}
            }
            else if( iRet = check_num(node) )
            {
		pin+=len;
            }   
            else
            {   
		out[j]=*pin;
		j++ ;
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
    out[j] = 0 ;
    return 0;
}
int getnode(char *sSrc,char *node)
{
    char *p;
    int i=0,k=0;
    int flag=0;
    char snode[1024];

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
	    {
		k ++ ;
                break;
	    }
            snode[i] = *p;
            i++;
            continue;
        }
    }
    snode[i] = 0;
    strcpy(node,snode);
    return k;
}
