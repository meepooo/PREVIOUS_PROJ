/***********************************************************************
 * ��Ȩ����:�������ӹɷ����޹�˾
 * ��Ŀ����:̨�������м�ҵ��ƽ̨
 * ��    ��:V1.00
 * ����ϵͳ:
 * �� �� ��:SDATA_Datacasecmp.c
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
 * �����������:SDATA_Datacasecmp
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

IRESULT SDATA_Datacasecmp(HXMLTREE lXmlhandle)
{
    char outstr[MAX_LENGTH + 1];
    char *instr;
    char s_ms[1+1];
    char srcdata[2048] ;
    char decdata[2048] ;
    int iParas,iRet=0;
    int iLen;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif

    COMP_PARACOUNTCHK(3);

    /* ��ȡģʽ */
    memset(s_ms,0x00,sizeof(s_ms));
    COMP_GETPARSEPARAS(1,s_ms,"ģʽ")
    trim(s_ms);

    memset(srcdata,0x00,sizeof(srcdata));
    COMP_GETPARSEPARAS(2,srcdata,"Դ����")
    trim(srcdata);

    memset(decdata,0x00,sizeof(decdata));
    COMP_GETPARSEPARAS(3,decdata,"�Ƚ�����")
    trim(decdata);

    /* �ж�ģʽ�Ƿ�Ϊ�� */
    if(strlen(s_ms) ==0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        /*fpub_SetMsg(lXmlhandle,atol(BS_ERR_NOBLANK),Fmtmsg("ģʽ����Ϊ��!"));*/
        LOGRET(-1,LM_STD,Fmtmsg("ģʽ����Ϊ��!"),"ERR");
    }

    LOG(LM_DEBUG,Fmtmsg("ģʽ[%s]Դ����[%s]�Ƚ�����[%s]", s_ms, srcdata, decdata),"DEBUG");

    iRet = strcasecmp(srcdata, decdata) ;
    LOG(LM_DEBUG,Fmtmsg("[%d]ģʽ[%s]Դ����[%s]�Ƚ�����[%s]", iRet, s_ms, srcdata, decdata),"DEBUG");

    if ( iRet==0 )
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return 0;
    }
    else if ( iRet>0 )
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	return 1;
    }
    else if ( iRet<0 )
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	return 2;
    }
    else
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	return COMPRET_FAIL;
    }
}
