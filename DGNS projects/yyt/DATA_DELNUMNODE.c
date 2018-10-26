/***********************************************************************
 * ��̬�����������
 * �����������:DATA_DELNUMNODE
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
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif

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

    outstr = ( char *) malloc( iLen + 1 ) ;
    if( instr == NULL )
    {
        free(instr);
        LOG(LM_DEBUG,Fmtmsg("�����ڴ�ʧ��"),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("�����ڴ�ʧ��"),"ERR");
    }

    iRet=CreateXml(instr,outstr);
    if(iRet)
    {
        /*LOG(LM_DEBUG,"����ת��ʧ��","ERROR");*/
        free(instr);
    	free(outstr);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(-1,LM_STD,Fmtmsg("����ת��ʧ��"),"ERR");
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
