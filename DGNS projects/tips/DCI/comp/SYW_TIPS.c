/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V3.0.00
����ϵͳ:AIX5.3
�ļ�����:SYW_TIPS.ec
�ļ�����:TIPS���������
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:Tuql
��������:
��    ��:
�޸�����:  
*********************************************************************/
/*
����˵��:

����˵��
�����������                 �������                      ��������  ����Ա �޸����� �޸���

*/

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h> 
#include <stdlib.h>
#include <unistd.h> 
#include "gaps_head.h"
/* mod dci 20141103    
EXEC SQL INCLUDE  "gaps_head.eh";
EXEC SQL INCLUDE  "../eh/tips_bwdj.eh"; ���ĵǼǱ� 
EXEC SQL INCLUDE  "../eh/tips_sjgxhz.eh"; ���ݸ��»��ܱ� 
EXEC SQL INCLUDE  "../eh/tips_taxcodeinfo.eh"; ���ջ��ش���� 
EXEC SQL INCLUDE  "../eh/tips_bankcodeinfo.eh"; �������д���� 
EXEC SQL INCLUDE  "../eh/tips_nodecodeinfo.eh"; �ڵ����� 
EXEC SQL INCLUDE  "../eh/tips_trecodeinfo.eh"; �������� 
EXEC SQL INCLUDE  "../eh/tips_budgetsubject.eh"; Ԥ���Ŀ����� 
EXEC SQL INCLUDE  "../eh/tips_returnreason.eh"; �˿�ԭ������ 
EXEC SQL INCLUDE  "../eh/tips_correctreason.eh"; ����ԭ������ 
EXEC SQL INCLUDE  "../eh/tips_taxtypeinfo.eh"; ˰�ִ���� 
EXEC SQL INCLUDE  "../eh/tips_taxsubject.eh"; ˰Ŀ����� 
EXEC SQL INCLUDE  "../eh/tips_zygsbw.eh"; ���ɸ�ʽ���� 
EXEC SQL INCLUDE  "../eh/tips_9120.eh"; ���ĵǼǱ� add by tuql 20091022
EXEC SQL INCLUDE  "../eh/tips_yxcs.eh"; ���ĵǼǱ� add by tuql 20091022
EXEC SQL INCLUDE  "../eh/tips_xibhxmx.eh"; ������ϸ�� add by wangw 20120802
*/

/* add dci 20141103 */
#include "../eh/tips_bwdj.h"/* ���ĵǼǱ� */
#include "../eh/tips_sjgxhz.h"/* ���ݸ��»��ܱ� */
#include "../eh/tips_taxcodeinfo.h"/* ���ջ��ش���� */
#include "../eh/tips_bankcodeinfo.h"/* �������д���� */
#include "../eh/tips_nodecodeinfo.h"/* �ڵ����� */
#include "../eh/tips_trecodeinfo.h"/* �������� */
#include "../eh/tips_budgetsubject.h"/* Ԥ���Ŀ����� */
#include "../eh/tips_returnreason.h"/* �˿�ԭ������ */
#include "../eh/tips_correctreason.h"/* ����ԭ������ */
#include "../eh/tips_taxtypeinfo.h"/* ˰�ִ���� */
#include "../eh/tips_taxsubject.h"/* ˰Ŀ����� */
#include "../eh/tips_zygsbw.h"/* ���ɸ�ʽ���� */
#include "../eh/tips_9120.h"/* ���ĵǼǱ� add by tuql 20091022 */
#include "../eh/tips_yxcs.h"/* ���ĵǼǱ� add by tuql 20091022 */
#include "../eh/tips_xibhxmx.h" /* ������ϸ�� add by wangw 20120802*/
/* end add dci 20141103 */

#define    LEN_COMM                64000                   /*ͨѶ����������*/
#define TIPS_MAX_PKG       8192000 /* 20150512��Ϊ��̬���� 8M�������� */   /*ͨѶ������󳤶�*/
#define XML_TMPNODE     "/systmp"   /*ϵͳ�õ�XML·��*/

#define XML_TMPNODE     "/systmp"   /*ϵͳ�õ�XML·��*/

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )
             
/************************************************************************
��̬�����������
�����������: SYW_TIPS_MMTIME
�������: ȡʱ�����
�������: 
  ȡʱ�����
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: 
��������: 2014��09��22��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/             
IRESULT SYW_TIPS_MMTIME(HXMLTREE lXmlhandle)
{
	int iReturn = COMPRET_SUCC;
	int iReturnStatus = COMPSTATUS_SUCC;
	
	char szBuf[255];
	char szBuf1[255];
	char pMMTime[255];
	struct timeval tv; 
	long lMMTime;
	
  
	memset(szBuf, 0, sizeof(szBuf));
	memset(szBuf1, 0, sizeof(szBuf1));
	memset(pMMTime, 0, sizeof(pMMTime));
		
	fpub_InitSoComp( lXmlhandle );

	LOG( LM_DEBUG, Fmtmsg( "-------------------[%s]", fpub_GetCompname( lXmlhandle ) ), "INFO" );
	LOG( LM_DEBUG, Fmtmsg( "���[%s]��ʼִ��", fpub_GetCompname( lXmlhandle ) ), "INFO" );	

	COMP_GETPARSEPARAS(1, pMMTime, "��ȷʱ��");

	/*�������ɺ���*/
	
	gettimeofday(&tv,NULL);    
  lMMTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;  
  LOG( LM_DEBUG, Fmtmsg( "��ȷʱ��[%3ld]",  lMMTime), "INFO" ); 
  
  sprintf(szBuf1,"%ld",lMMTime);
  LOG( LM_DEBUG, Fmtmsg( "��ȷʱ��[%s]",  szBuf1), "INFO" ); 
  
  strncpy(szBuf,szBuf1+(strlen(szBuf1)-3),3);
  
	LOG( LM_DEBUG, Fmtmsg( "��ȷʱ��[%s]",  szBuf), "INFO" ); 
	COMP_HARDSETXML(pMMTime, szBuf);
	LOG( LM_DEBUG, Fmtmsg( "��ȷʱ��[%s]",  pMMTime), "INFO" );

	fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
	LOG( LM_DEBUG, Fmtmsg( "���[%s]����ִ��", fpub_GetCompname( lXmlhandle ) ), "INFO" );
	return COMPRET_SUCC;	
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_COMM
�������: ��TIPSת����ͨѶ
�������: 
  ��TIPSת����ͨѶ
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_COMM(HXMLTREE lXmlhandle)
{
    int iParas;
    /*char sBuffer[TIPS_MAX_PKG]; 20150512 ��Ϊ��̬���� */
    char *pBuffer = NULL;
    char sIp[50];
    char sTxms[1+1];/* ͨѶģʽ1,2,3 3-��Ӧ�� */
    char sTmpBuf[254];
    char sBuf[254];
    char sXym[5+1];
    char sXyxx[60+1];
    char commbuf1[TIPS_MAX_PKG];
    
    int  iSock = -1;
    int  iPort;
    int  iTime;
    int  iRet;
    int  iLen;
    int  iSize;
    char syncbuf[3]={"\x02\x00\x00"};
    
    char sJydm[4+1];/* ���״��� */
    char sMode[1+1];/* ģʽ, 1-put 2-get */
    char sPutMode[1+1];/* putģʽ getʱ��ʹ�� 1-������ʽput 2-����Ӧ��ʽput */
    char sMsgID[56];/* ������Ϣ��CorrelId ����Ӧģʽ����ʱʹ�� */
    char sXh[30];/* ��� */
    char sQmgr[60];/* ���й����� */
    char sRespQueue[60];/* Ӧ������� */
    char sCssj[30];/* ��ʱʱ�� */
    char sFileName[256];/* �ļ��� */

    fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
    #endif 
  
    /*��ȡ�������  --S*/
    COMP_PARACOUNTCHK(4)

    /*IP*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sIp, 0x00, sizeof(sIp));
    COMP_GETPARSEPARAS(1, sBuf, "IP��ַ")
    pstrcopy(sIp, sBuf, sizeof(sIp));
    trim(sIp);
    /*PORT*/
    memset(sBuf, 0x00, sizeof(sBuf));
    iPort = 0 ;
    COMP_GETPARSEPARAS(2, sBuf, "PORT")
    iPort = atoi(sBuf);
    /*TIMOUT*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "��ʱʱ��")
    if (sBuf[0] != '\0')
      iTime = atoi(sBuf);
    else
      iTime = 60;
    /*ͨѶģʽ*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTxms, 0x00, sizeof(sTxms));
    COMP_GETPARSEPARAS(4, sBuf, "ͨѶģʽ")
    pstrcopy(sTxms, sBuf, sizeof(sTxms));
    trim(sTxms);
    
    LOG(LM_STD,Fmtmsg("ͨѶ����IP��ַ[%s] PORT[%d], ��ʱʱ��[%d]",sIp, iPort, iTime), fpub_GetCompname(lXmlhandle))
    
    /* ȡͨѶ������ */
    /* 20150512 �޸�Ϊ��̬��ȡ */
   /*memset(sBuffer, 0x00, sizeof(sBuffer));*/
    iSize = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iSize < 0)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ���ĳ���ʧ��",fpub_GetCompname(lXmlhandle));
	  }
	  iSize = iSize +1;
	  pBuffer = malloc(iSize);
	  if(NULL == pBuffer)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("mallocʧ��[%s]",strerror(errno)),fpub_GetCompname(lXmlhandle));
	  }	
	  memset(pBuffer, 0, iSize);
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, "/commbuf", pBuffer, iSize)) == FAIL )
    {
    	  free(pBuffer);
        fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
    }
    /* end 20150512 �޸�Ϊ��̬��ȡ */
	/* ͨѶ���� */
    itcp_sethead(0);
    itcp_setenv( iPort, &iSock);
    itcp_setsync(3,syncbuf);
    itcp_setmaxlen(1024); 
  
    iRet = itcp_call(sIp);
    if (iRet != 0)
    {
		fpub_SetMsg(lXmlhandle, 24106, "��tipsת��������ʧ��");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"����ʧ��",fpub_GetCompname(lXmlhandle));
    }
	
	/* 20150512 mmapδ�ͷ�core�޸�
	memset(commbuf1,0x00, sizeof(commbuf1));
	memcpy(commbuf1, sBuffer, iLen); 
	iRet=itcp_send(commbuf1,iLen,iTime);
	LOG(LM_STD,Fmtmsg("commbuf1[%s]", commbuf1),"itcp_send");
	*/
	
	iRet=itcp_send(pBuffer,iLen,iTime);
	LOG(LM_STD,Fmtmsg("pBuffer[%s]", pBuffer),"itcp_send");
	if (iRet<0)
	{
		itcp_clear();
		fpub_SetMsg(lXmlhandle, 24107, "��tipsת������������ʧ��");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"��tipsת������������ʧ��",fpub_GetCompname(lXmlhandle));
	}
	
    /*������Ч����*/
	/* 20150512 �޸� 
	memset(sBuffer, 0x00, sizeof(sBuffer));
	iRet=itcp_recv(sBuffer,sizeof(sBuffer),iTime);
	trim(sBuffer);
	LOG(LM_STD,Fmtmsg("sBuffer1[%s]", sBuffer),"itcp_recv");
	end 20150512 */
	memset(commbuf1,0x00, sizeof(commbuf1));
	iRet=itcp_recv(commbuf1,sizeof(commbuf1),iTime);
	trim(commbuf1);
	LOG(LM_STD,Fmtmsg("���ձ��ĳ���[%d][%s]", strlen(commbuf1),commbuf1),"itcp_recv");
	
	if (iRet<0)
	{
        itcp_clear();
		fpub_SetMsg(lXmlhandle, 24108, "��tipsת������������ʧ��");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"��tipsת������������ʧ��",fpub_GetCompname(lXmlhandle));
	}
	itcp_clear();
	/* 20150512 
	if (( iRet = xml_RelSetBinElement(lXmlhandle,"/commbuf",sBuffer,strlen(sBuffer))) == FAIL)*/
	if (( iRet = xml_RelSetBinElement(lXmlhandle,"/commbuf",commbuf1,strlen(commbuf1))) == FAIL)
	{
		fpub_SetMsg(lXmlhandle, 24109, "��дͨѶ������ʧ��");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"��дͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
	}
        
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;    

}   

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitPKGHEAD
�������: ��ʼ������ͷ������
�������: 
  ��ʼ������ͷ������
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
�������׵ǼǱ�	tips_nbcsb

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPKGHEAD(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sDqzt[1+1];/* ��ǰ״̬ */
         char sQdqt[1+1];/* ǩ��ǩ�� */
         char sVer[10+1];/* �汾�� */
         char sSrc[12+1];/* ����ڵ���� */
         char sDes[12+1];/* ���սڵ���� */
         char sWorkDate[8+1];/* �������� */
         char sMsgNo[4+1];/* ���ı�� */
         int iCount;
    /*EXEC SQL END   DECLARE SECTION;*/
    
    char sBuf[256];
    char sMsgID[20+1];/* ���ı�ʶ�� */
    char sMsgRef[20+1];/* ���Ĳο��� */
    
    int iRet=0;
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif 
    
    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgNo, 0x00, sizeof(sMsgNo));
    COMP_GETPARSEPARAS(1, sBuf, "���ı��")
    pstrcopy( sMsgNo, sBuf, sizeof(sMsgNo));
    trim(sMsgNo);            

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgID, 0x00, sizeof(sMsgID));
    COMP_GETPARSEPARAS(2, sBuf, "���ı�ʶ��")
    pstrcopy( sMsgID, sBuf, sizeof(sMsgID));
    trim(sMsgID); 

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgRef, 0x00, sizeof(sMsgRef));
    COMP_GETPARSEPARAS(3, sBuf, "���Ĳο���")
    pstrcopy( sMsgRef, sBuf, sizeof(sMsgRef));
    trim(sMsgRef); 

    LOG(LM_STD,Fmtmsg("��ʼ������ͷ�����ʼ ���ı��[%s],���ı�ʶ��[%s],���Ĳο���[%s]", 
        sMsgNo, sMsgID, sMsgRef), fpub_GetCompname(lXmlhandle));
    
    /* ��ѯ�ڲ������� */
    memset(sWorkDate, 0x00, sizeof(sWorkDate));
    memset(sVer, 0x00, sizeof(sVer));
    memset(sSrc, 0x00, sizeof(sSrc));
    memset(sDes, 0x00, sizeof(sDes));
    memset(sDqzt, 0x00, sizeof(sDqzt));
    memset(sQdqt, 0x00, sizeof(sQdqt));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT workdate, ver, src, des, dqzt, qdqt FROM tips_nbcsb WHERE 1=1");     
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sWorkDate, &sVer, &sSrc, &sDes, &sDqzt, &sQdqt);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("��ѯ�ڲ�������ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�ڲ�������ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
        
    }
    /* end add dci 20141103 */
    

    /* mod dci 20141103
    EXEC SQL SELECT workdate, ver, src, des, dqzt, qdqt 
         INTO :sWorkDate, :sVer, :sSrc, :sDes, :sDqzt, :sQdqt
         FROM tips_nbcsb
         WHERE 1=1;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("��ѯ�ڲ�������ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�ڲ�������ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    trim(sWorkDate);trim(sVer);trim(sQdqt);
    trim(sSrc);trim(sDes);trim(sDqzt);
    LOG(LM_STD,Fmtmsg("��ǰ״̬[%s],��������[%s],�汾��[%s],����ڵ����[%s],���սڵ����[%s]", 
        sDqzt, sWorkDate, sVer, sSrc, sDes), fpub_GetCompname(lXmlhandle));
    
    /* ����ǰ״̬��Ϊ0-������8-���л�0-ǩ��,�򲻳������׵�TIPS��,
     * �����Ӳ��Լ�ǩ��������
     */
    /*  
    if (   ( sDqzt[0] =='1' || sDqzt[0] =='2' || sDqzt[0] =='3' || sQdqt[0] != '0' )
        && ( !( strncmp(sMsgNo, "9005", 4)==0 || strncmp(sMsgNo, "9006", 4)==0 ) )
        )
    {
        iCount = 0;
        EXEC SQL SELECT COUNT(*) INTO :iCount
             FROM tips_bwsxwh
             WHERE msgno = :sMsgNo;
               AND ssdl = 'O';
        if ( SQLERR )
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
            fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("��ѯ�������Ա�ʧ��"));
            LOG(LM_STD,Fmtmsg("��ѯ�������Ա�ʧ��"), fpub_GetCompname(lXmlhandle));        
            return COMPRET_FAIL; 	
        }
        if ( iCount > 0 )
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
            fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("δ��TIPSϵͳǩ����TIPSϵͳ������ά���ڣ�"));
            LOG(LM_STD,Fmtmsg("δ��TIPSϵͳǩ����TIPSϵͳ������ά���ڣ�"), fpub_GetCompname(lXmlhandle));        
            return COMPRET_FAIL;            
        }    
    }    
     */   
    /* ���ñ���ͷ������ */
    COMP_HARDSETXML("/CFX/HEAD/VER", sVer)/* �汾�� */
    COMP_HARDSETXML("/CFX/HEAD/SRC", sSrc)/* ����ڵ���� */
    COMP_HARDSETXML("/CFX/HEAD/DES", sDes)/* ���սڵ���� */    
    COMP_HARDSETXML("/CFX/HEAD/APP", "TIPS")/* Ӧ������ */
    COMP_HARDSETXML("/CFX/HEAD/MsgNo", sMsgNo)/* ���ı�� */
    COMP_HARDSETXML("/CFX/HEAD/MsgID", sMsgID)/* ���ı�ʶ�� */
    COMP_HARDSETXML("/CFX/HEAD/MsgRef", sMsgRef)/* ���Ĳο��� */
    COMP_HARDSETXML("/CFX/HEAD/WorkDate", sWorkDate)/* �������� */
    COMP_HARDSETXML("/CFX/HEAD/Reserve", "")/* Ԥ���ֶ� */    

    LOG(LM_STD,Fmtmsg("��ʼ������ͷ���������"), fpub_GetCompname(lXmlhandle));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;     
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitBWDJ
�������: ��ʼ�����ĵǼǱ�
�������: 
  ��ʼ�����ĵǼǱ�
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
���ĵǼǱ�	tips_bwdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��13��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitBWDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; mod dci 20141103 */ 		
			SDB_TIPS_BWDJ  stBwdj;
    /* EXEC SQL BEGIN DECLARE SECTION;  mod dci 20141103 */ 
		
		
    
    char sBuf[256];
    char sBwdjbz[1+1];
    char sNode[64];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif 

    memset(&stBwdj, 0x00, sizeof(stBwdj));
    /* 4.���ı�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/MsgNo", sBuf)
    pstrcopy(stBwdj.msgno, sBuf, sizeof(stBwdj.msgno));           
    if (!(   strncmp(stBwdj.msgno, "3102", 4)==0 
           ||strncmp(stBwdj.msgno, "2102", 4)==0
           ||strncmp(stBwdj.msgno, "1123", 4)==0
        ))
    {
        fpub_SetMsg(lXmlhandle, 0, "���Ǳ�����ˮ,�Ǽǳɹ�");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("���Ǳ��ĵǼ�,�ɹ��˳�"),
            fpub_GetCompname(lXmlhandle))        
    }    

    /* ȡ���ĵǼǸ�ֵ��Ϣ */
    /* 1.����������� */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/SendOrgCode", sBuf)
    pstrcopy(stBwdj.sendorgcode, sBuf, sizeof(stBwdj.sendorgcode));
    /* 2.ί������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/EntrustDate", sBuf)
    pstrcopy(stBwdj.entrustdate, sBuf, sizeof(stBwdj.entrustdate));
    /* 3.����ˮ�� */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/PackNo", sBuf)
    pstrcopy(stBwdj.packno, sBuf, sizeof(stBwdj.packno));
    /* 5.�������� */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/bwlx", sBuf)
    pstrcopy(stBwdj.bwlx, sBuf, sizeof(stBwdj.bwlx));
    /* 6.�������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/PayBkCode", sBuf)
    pstrcopy(stBwdj.paybkcode, sBuf, sizeof(stBwdj.paybkcode));
    /* 7.�����ļ��� */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/bwwjm", sBuf)
    pstrcopy(stBwdj.bwwjm, sBuf, sizeof(stBwdj.bwwjm));
    /* 8.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zwrq", sBuf)
    pstrcopy(stBwdj.zwrq, sBuf, sizeof(stBwdj.zwrq));    
    /* 9.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/clsj", sBuf)
    pstrcopy(stBwdj.clsj, sBuf, sizeof(stBwdj.clsj));
    /* 10.�ۺ�ǰ����ˮ�� */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zhqzlsh", sBuf)
    pstrcopy(stBwdj.zhqzlsh, sBuf, sizeof(stBwdj.zhqzlsh));
    /* 11.��ǰ״̬ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/dqzt", sBuf)
    pstrcopy(stBwdj.dqzt, sBuf, sizeof(stBwdj.dqzt));
    /* 12.�������� */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/WorkDate", sBuf)
    pstrcopy(stBwdj.workdate, sBuf, sizeof(stBwdj.workdate));
    /* 13.�ܱ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/allnum", sBuf)
    stBwdj.allnum=atoi(sBuf); 
    /* 14.�ܽ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/allamt", sBuf)
    stBwdj.allamt=atof(sBuf);
    /* 15.�ɹ����� */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/succnum", sBuf)
    stBwdj.succnum = atoi(sBuf);
    /* 16.�ɹ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/succamt", sBuf)
    stBwdj.succamt=atof(sBuf);
    /* 16.ֹ������ */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zfbs", sBuf)
    stBwdj.zfbs = atoi(sBuf);
    /* 17.ֹ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zfje", sBuf)
    stBwdj.zfje=atof(sBuf); 
    /* 24.������� */
    stBwdj.clcs=1;

		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_bwdj", SD_TIPS_BWDJ, NUMELE(SD_TIPS_BWDJ), &stBwdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
			fpub_SetMsg(lXmlhandle, 24103, "��ʼ�����ĵǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitBWDJ��ʼ�����ĵǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;   
    }

		/* end add dci 20141103 */
		
		/* mod dci 20141103 
    EXEC SQL INSERT INTO tips_bwdj  VALUES (:stBwdj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24103, "��ʼ�����ĵǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitBWDJ��ʼ�����ĵǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	    
    */
    
    fpub_SetMsg(lXmlhandle, 0, "��ʼ�����ĵǼǱ�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC; 
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_GetCOMMPARAS
�������: ��ȡ��tipsͨѶ�ĸ�����
�������: 
  ��ȡ��tipsͨѶ�Ĳ���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
���ĵǼǱ�	tips_bwdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��13��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_GetCOMMPARAS(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sMsgNo[4+1];/* ���ı�� */
         char sBwlx[4+1];/* �������� */
         char sBwms[1+1];/* ����ģʽ */
         char sYwhz[4+1];/* ҵ���ִ */
         char sSsdl[1+1];/* �������� */
         char sBwppjz[3+1];/* ����ƥ����� */
    /*EXEC SQL END   DECLARE SECTION;*/
    
    char sBuf[256];
    char sQmgr[60];/* ���й����� */
    char sQmgrPath[60];/* ���й�������� */
    char sReqQueue[60];/* ��������� */
    char sReqQueuePath[60];/* ������������ */
    char sRespQueue[60];/* Ӧ������� */
    char sRespQueuePath[60];/* Ӧ���������� */
    char sBwmsPath[60+1];/* ����ģʽ·�� */
    int  iBwppjz = 2 ;/* ����ƥ����� 2-���Ĳο���*/
    int  iXxscq = -1 ;/* ��Ϣ������ */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    LOG(LM_STD,Fmtmsg("��ȡ��tipsͨѶ�ĸ�������ʼ..."), fpub_GetCompname(lXmlhandle))
    
    COMP_PARACOUNTCHK(5);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgNo, 0x00, sizeof(sMsgNo));
    COMP_GETPARSEPARAS(1, sBuf, "���ı��")
    pstrcopy( sMsgNo, sBuf, sizeof(sMsgNo));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQmgrPath, 0x00, sizeof(sQmgrPath));
    COMP_GETPARAS(2, sBuf, "���й��������")
    pstrcopy( sQmgrPath, sBuf, sizeof(sQmgrPath)); 
    trim(sQmgrPath);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sReqQueuePath, 0x00, sizeof(sReqQueuePath));
    COMP_GETPARAS(3, sBuf, "������������")
    pstrcopy( sReqQueuePath, sBuf, sizeof(sReqQueuePath)); 
    trim(sReqQueuePath);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRespQueuePath, 0x00, sizeof(sRespQueuePath));
    COMP_GETPARAS(4, sBuf, "Ӧ����������")
    pstrcopy( sRespQueuePath, sBuf, sizeof(sRespQueuePath));
    trim(sRespQueuePath);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sBwmsPath, 0x00, sizeof(sBwmsPath));
    COMP_GETPARAS(5, sBuf, "����ģʽ���")
    pstrcopy( sBwmsPath, sBuf, sizeof(sBwmsPath));
    trim(sBwmsPath);
        
    LOG(LM_STD,Fmtmsg("���ı��[%s]...", sMsgNo), fpub_GetCompname(lXmlhandle))
    
    /* �ӱ�������ά�����л�ȡ�������͡�����ģʽ�������������ʵ���Ϣ */
    memset(sBwlx, 0x00, sizeof(sBwlx));
    memset(sBwms, 0x00, sizeof(sBwms));
    memset(sYwhz, 0x00, sizeof(sYwhz));
    memset(sSsdl, 0x00, sizeof(sSsdl));
    memset(sBwppjz, 0x00, sizeof(sBwppjz));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT bwlx, bwms, ywhz, ssdl, bwppjz FROM tips_bwsxwh \
			WHERE msgno='%s'",sMsgNo);     
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sBwlx, &sBwms, &sYwhz, &sSsdl, &sBwppjz);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24104, "��ѯ��������ά����ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS��ѯ��������ά����ʧ��"),
            fpub_GetCompname(lXmlhandle))	
        
    }
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24104, "�ڱ���δ�ҵ���Ӧ�ı��ı��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS�ڱ���δ�ҵ���Ӧ�ı��ı��"),
            fpub_GetCompname(lXmlhandle))	
        
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT bwlx, bwms, ywhz, ssdl, bwppjz
         INTO :sBwlx, :sBwms, :sYwhz, :sSsdl, :sBwppjz 
         FROM tips_bwsxwh
         WHERE msgno = :sMsgNo;            
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24104, "��ѯ��������ά����ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS��ѯ��������ά����ʧ��"),
            fpub_GetCompname(lXmlhandle))	
    }
    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetMsg(lXmlhandle, 24104, "�ڱ���δ�ҵ���Ӧ�ı��ı��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS�ڱ���δ�ҵ���Ӧ�ı��ı��"),
            fpub_GetCompname(lXmlhandle))	
    } 
    */
       
    /* �ӻ���������ƴ����ɶ��й����� */
    memset(sQmgr, 0x00, sizeof(sQmgr));
    snprintf(sQmgr, sizeof(sQmgr), "%s%s%s", getenv("QMGRPREFIX"), getenv("EXTNODECODE"), getenv("RESERVENO"));
    trim(sQmgr);
    
    /* ƴ������Ӧ������� */
    memset(sReqQueue, 0x00, sizeof(sReqQueue));
    memset(sRespQueue, 0x00, sizeof(sRespQueue));
    if ( sSsdl[0]=='O') /* ����ʵʱ */
    {
        snprintf(sReqQueue, sizeof(sReqQueue), "PBC.EXT.%s.IN", "ONLINE"); 
        memset(sBuf, 0x00, sizeof(sBuf));
        /*COMP_SOFTGETXML("/tips/HEAD/MsgNo", sBuf)*/
        COMP_SOFTGETXML("/tipso/MsgNo", sBuf)
        trim(sBuf);
        LOG(LM_DEBUG,Fmtmsg("MsgNo[%s]...",sBuf),"INFO")      
        if (strcmp(sBuf, "9120") == 0 )
        {
            snprintf(sReqQueue, sizeof(sReqQueue), "%s", "TIPS.INTERNAL.RESP");
        }
    }else
    {
       snprintf(sReqQueue, sizeof(sReqQueue), "PBC.EXT.%s.IN", "BATCH");  
    }        
    if (sBwms[0]=='1' || sBwms[0]=='4')/* ��ʵʱ��ִ */
    {
        snprintf(sRespQueue, sizeof(sRespQueue), "PBC.%s.ONLINE.OUT", getenv("EXTNODECODE")); 
        iXxscq = 10000 ;/* ��Ϣ������ */
        iBwppjz = 1 ; /* ����ƥ����� 1-MQ��ϢID */      
    }else
    {
        snprintf(sRespQueue, sizeof(sRespQueue), "TIPS.INTERNAL.RESP");
    }
    trim(sReqQueue);
    trim(sRespQueue);       
    
    /* mod by tuql 20090909 ��COMP_SOFTSETXML�ĳ�COMP_HARDSETXML */
    COMP_HARDSETXML(sQmgrPath, sQmgr) 
    COMP_HARDSETXML(sReqQueuePath, sReqQueue)  
    COMP_HARDSETXML(sRespQueuePath, sRespQueue)
    COMP_HARDSETXML(sBwmsPath, sBwms)
    
    memset(sBuf, 0x00, sizeof(sBuf)); 
    sprintf(sBuf, "%d", iBwppjz);
    COMP_HARDSETXML("/tipso/bwppjz", sBuf)/* ����ƥ����� */

    memset(sBuf, 0x00, sizeof(sBuf)); 
    sprintf(sBuf, "%d", iXxscq);
    COMP_HARDSETXML("/tipso/xxscq", sBuf)/* ��Ϣ������ */

    LOG(LM_STD,Fmtmsg("��ȡ��tipsͨѶ�ĸ���������...."),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;               
}    

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA
��������: ���¹�������
��������: 
  ���¹�������
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
���ݸ��»��ܱ�	tips_sjgxhz

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA(HXMLTREE lXmlhandle, char *sZwrq, int iZhqzlsh, char *sWorkDate, char *sUpdateBatch)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_SJGXHZ stSjgxhz;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_SJGXHZ stSjgxhz;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);
    
    memset(&stSjgxhz, 0x00, sizeof(stSjgxhz));
    pstrcopy(stSjgxhz.zwrq, sZwrq, sizeof(stSjgxhz.zwrq));
    stSjgxhz.zhqzlsh = iZhqzlsh;
    pstrcopy(stSjgxhz.workdate, sWorkDate, sizeof(sWorkDate));
    pstrcopy(stSjgxhz.updatebatch, sUpdateBatch, sizeof(stSjgxhz.updatebatch));
            
    /*ȡ���ջ��ظ�������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_101 = 0;
    else
     	stSjgxhz.num_101 = atoi(sBuf);
    /*ȡ���ջ��ظ��³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num101succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_101_succ = 0;
    else
     	stSjgxhz.num_101_succ = atoi(sBuf);
    /*ȡ�������и�������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BankCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	stSjgxhz.num_102 = 0;
    else
      	stSjgxhz.num_102 = atoi(sBuf);
    /*ȡ�������и��³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num102succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_102_succ = 0;
    else
      	stSjgxhz.num_102_succ = atoi(sBuf);   
    /*ȡ�ڵ��������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/NodeCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_103 = 0;
    else
      	stSjgxhz.num_103 = atoi(sBuf);
    /*ȡ�ڵ���³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num103succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_103_succ = 0;
    else
     	stSjgxhz.num_103_succ = atoi(sBuf);     	
    /*ȡ�����������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TreCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_104 = 0;
    else
         stSjgxhz.num_104 = atoi(sBuf);
    /*ȡ������³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num104succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_104_succ = 0;
    else
         stSjgxhz.num_104_succ = atoi(sBuf);   	
     /*ȡԤ���Ŀ��������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BudgetSubjectCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_105 = 0;
    else
      	stSjgxhz.num_105 = atoi(sBuf);
     /*ȡԤ���Ŀ���³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num105succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_105_succ = 0;
    else
     	stSjgxhz.num_105_succ = atoi(sBuf);
    /*ȡ�˿�ԭ���������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/ReturnReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_106 = 0;
    else
     	stSjgxhz.num_106 = atoi(sBuf);
    /*ȡ�˿�ԭ����³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num106succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_106_succ = 0;
    else
     	stSjgxhz.num_106_succ = atoi(sBuf);   
    /*ȡ����ԭ���������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/CorrectReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_107 = 0;
    else
      	stSjgxhz.num_107 = atoi(sBuf);
    /*ȡ����ԭ����³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num107succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_107_succ = 0;
    else
      	stSjgxhz.num_107_succ = atoi(sBuf);   
    /*ȡ˰�ִ����������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxTypeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_108 = 0;
    else
         stSjgxhz.num_108 = atoi(sBuf);
    /*ȡ˰�ִ�����³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num108succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_108_succ = 0;
    else
         stSjgxhz.num_108_succ = atoi(sBuf);   
    /*ȡ˰Ŀ�����������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxSubjectInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_109 = 0;
    else
        stSjgxhz.num_109 = atoi(sBuf);
    /*ȡ˰Ŀ������³ɹ�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num109succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_109_succ = 0;
    else
         stSjgxhz.num_109_succ = atoi(sBuf);
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_sjgxhz", SD_TIPS_SJGXHZ, NUMELE(SD_TIPS_SJGXHZ), &stSjgxhz, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
			fpub_SetMsg(lXmlhandle, 24456, "�������ݸ��»�����Ϣʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("UpdPUBDATA�������ݸ��»�����Ϣʧ��"),
             fpub_GetCompname(lXmlhandle))
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL INSERT INTO tips_sjgxhz VALUES(:stSjgxhz);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24456, "�������ݸ��»�����Ϣʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("UpdPUBDATA�������ݸ��»�����Ϣʧ��"),
             fpub_GetCompname(lXmlhandle))
    }
    */
    
    fpub_SetMsg(lXmlhandle, 0, "���¹������ݴ������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   
}
/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_Tax
��������: ���¹�������-���ջ��ش���
��������: 
  ���¹�������-���ջ��ش���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
���ջ��ش���	tips_taxcodeinfo

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Tax(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
				SDB_TIPS_TAXCODEINFO stTaxCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum101;
    int iNum101Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TAXCODEINFO stTaxCode;
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum101 = 0;
    else
     	iNum101 = atoi(sBuf);
    
    if ( iNum101 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-���ջ��ش���");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-���ջ��ش���,��[%d]��", iNum101),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ���ջ��ؽڵ���ϸ*/
    for(i = 1; i <= iNum101; i ++)
    {
   		memset(&stTaxCode, 0x00, sizeof(stTaxCode));
   		/*1.���ջ��ش���*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/TaxOrgCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.taxorgcode, sTmpBuf, sizeof(stTaxCode.taxorgcode));
   		/*2.���ջ�������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/TaxOrgName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.taxorgname, sTmpBuf, sizeof(stTaxCode.taxorgname));
   		/*3.���ջ�������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/TaxOrgType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.taxorgtype, sTmpBuf, sizeof(stTaxCode.taxorgtype));
   		/*4.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OrgLevel",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.orglevel, sTmpBuf, sizeof(stTaxCode.orglevel));
   		/*5.����������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/UpTreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.uptrecode, sTmpBuf, sizeof(stTaxCode.uptrecode));
   		/*6.�����ڵ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfNodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofnodecode, sTmpBuf, sizeof(stTaxCode.ofnodecode));
   		/*7.����ʡ�����ջ���*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfProvOrg",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofprovorg, sTmpBuf, sizeof(stTaxCode.ofprovorg));
   		/*8.�����м����ջ���*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfCityOrg",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofcityorg, sTmpBuf, sizeof(stTaxCode.ofcityorg));
   		/*9.�����ؼ����ջ���*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfCountyOrg",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofcountyorg, sTmpBuf, sizeof(stTaxCode.ofcountyorg));
   		/*10.��ַ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/Address",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.address, sTmpBuf, sizeof(stTaxCode.address));
   		/*11.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PostalCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.postalcode, sTmpBuf, sizeof(stTaxCode.postalcode));
   		/*12.��ϵ������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PeopleName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.peoplename, sTmpBuf, sizeof(stTaxCode.peoplename));
   		/*13.��ϵ������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PeoplePhone",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.peoplephone, sTmpBuf, sizeof(stTaxCode.peoplephone));
   		/*14.��ϵ���ֻ�*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PeopleMobile",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.peoplemobile, sTmpBuf, sizeof(stTaxCode.peoplemobile));
   		/*15.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/Email",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.email, sTmpBuf, sizeof(stTaxCode.email));
   		/*16.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.opersign, sTmpBuf, sizeof(stTaxCode.opersign));
   		/*17.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.effectdate, sTmpBuf, sizeof(stTaxCode.effectdate));
   		/*18.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.updatearea, sTmpBuf, sizeof(stTaxCode.updatearea));

   		switch(atoi(stTaxCode.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_taxcodeinfo", SD_TIPS_TAXCODEINFO, NUMELE(SD_TIPS_TAXCODEINFO), &stTaxCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
						fpub_SetMsg(lXmlhandle, 24457, "�������ջ��ش���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�������ջ��ش���ʧ��[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    		iNum101Succ ++;
   				/* end add dci 20141103 */   				

   				/* mod dci 20141103 
   				EXEC SQL INSERT INTO tips_taxcodeinfo VALUES(:stTaxCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24457, "�������ջ��ش���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�������ջ��ش���ʧ��[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    		iNum101Succ ++;
      		*/
   				break;
   				
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stTaxCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "taxorgcode ='%s'", stTaxCode.taxorgcode); 
    			iRet = DBUpdate("tips_taxcodeinfo", SD_TIPS_TAXCODEINFO, NUMELE(SD_TIPS_TAXCODEINFO), &stTaxCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24458, "�������ջ��ش���ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD,Fmtmsg("�������ջ��ش���ʧ��[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                fpub_GetCompname(lXmlhandle))
      		}else
      			iNum101Succ ++;  
    			/* end add dci 20141103 */  

   				/* mod dci 20141103 
   				EXEC SQL update tips_taxcodeinfo
   					 set taxorgname=:stTaxCode.taxorgname,
   						 taxorgtype=:stTaxCode.taxorgtype,
   						 uptrecode=:stTaxCode.uptrecode,
   						 orglevel=:stTaxCode.orglevel,
   						 ofnodecode=:stTaxCode.ofnodecode,
   						 ofprovorg=:stTaxCode.ofprovorg,
   						 ofcityorg=:stTaxCode.ofcityorg,
   						 ofcountyorg=:stTaxCode.ofcountyorg,
   						 address=:stTaxCode.address,
   						 postalcode=:stTaxCode.postalcode,
   						 peoplename=:stTaxCode.peoplename,
   						 peoplephone=:stTaxCode.peoplephone,
   						 peoplemobile=:stTaxCode.peoplemobile,
   						 email=:stTaxCode.email,
   						 opersign=:stTaxCode.opersign,
   						 effectdate=:stTaxCode.effectdate,
   						 updatearea=:stTaxCode.updatearea
   				   where taxorgcode=:stTaxCode.taxorgcode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24458, "�������ջ��ش���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�������ջ��ش���ʧ��[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    		iNum101Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_taxcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where taxorgcode ='%s'"  , stTaxCode.effectdate,stTaxCode.opersign, stTaxCode.taxorgcode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24459, "ע�����ջ��ش���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע�����ջ��ش���ʧ��[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum101Succ ++;
    
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103 
   				EXEC SQL UPDATE tips_taxcodeinfo
   					 SET  effectdate=:stTaxCode.effectdate,
   						  opersign=:stTaxCode.opersign
   					WHERE taxorgcode=:stTaxCode.taxorgcode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24459, "ע�����ջ��ش���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע�����ջ��ش���ʧ��[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum101Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum101Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num101succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[���ջ��ش���]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�������ջ��ش����������ɹ�����[%d]", iNum101Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_Bank
��������: ���¹�������-�������д���
��������: 
  ���¹�������-�������д���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�������д���	tips_bankcodeinfo

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Bank(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_BANKCODEINFO stBankCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum102;
    int iNum102Succ;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_BANKCODEINFO stBankCode;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("�����������д�������ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BankCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum102 = 0;
    else
     	iNum102 = atoi(sBuf);
    
    if ( iNum102 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-�������д���");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-�������д���,��[%d]��", iNum102),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ�������нڵ���ϸ*/
    for(i = 1; i <= iNum102; i ++)
    {
        memset(&stBankCode, 0x00, sizeof(stBankCode));
   		/*1.���������к�*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/ReckBankNo",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.reckbankno, sTmpBuf, sizeof(stBankCode.reckbankno));
   		/*2.������������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/GenBankName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.genbankname, sTmpBuf, sizeof(stBankCode.genbankname));
   		/*3.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/ReckonType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.reckontype, sTmpBuf, sizeof(stBankCode.reckontype));
   		/*4.�����ڵ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/OfNodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.ofnodecode, sTmpBuf, sizeof(stBankCode.ofnodecode));
   		/*5.��ַ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/Address",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.address, sTmpBuf, sizeof(stBankCode.address));
   		/*6.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PostalCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.postalcode, sTmpBuf, sizeof(stBankCode.postalcode));
   		/*7.��ϵ������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PeopleName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.peoplename, sTmpBuf, sizeof(stBankCode.peoplename));
   		/*8.��ϵ������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PeoplePhone",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.peoplephone, sTmpBuf, sizeof(stBankCode.peoplephone));   		
   		/*9.��ϵ���ֻ�*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PeopleMobile",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.peoplemobile, sTmpBuf, sizeof(stBankCode.peoplemobile)); 
   		/*10.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/Email",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.email, sTmpBuf, sizeof(stBankCode.email));
   		/*11.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.opersign, sTmpBuf, sizeof(stBankCode.opersign));
   		/*12.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.effectdate, sTmpBuf, sizeof(stBankCode.effectdate));
   		/*12.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.updatearea, sTmpBuf, sizeof(stBankCode.updatearea));
   		switch(atoi(stBankCode.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_bankcodeinfo", SD_TIPS_BANKCODEINFO, NUMELE(SD_TIPS_BANKCODEINFO), &stBankCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24460, "�����������д���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����������д���ʧ��[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_bankcodeinfo VALUES(:stBankCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24460, "�����������д���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����������д���ʧ��[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
      		*/
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stBankCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "reckbankno ='%s'", stBankCode.reckbankno); 
    			iRet = DBUpdate("tips_bankcodeinfo", SD_TIPS_BANKCODEINFO, NUMELE(SD_TIPS_BANKCODEINFO), &stBankCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24461, "�����������д���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����������д���ʧ��[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum102Succ ++;
      		/* end add dci 20141103 */
   				
   				/* mod dci 20141103
   				EXEC SQL update tips_bankcodeinfo
   					 set genbankname=:stBankCode.genbankname,
   						 reckontype=:stBankCode.reckontype,
   						 ofnodecode=:stBankCode.ofnodecode,
   						 address=:stBankCode.address,
   						 postalcode=:stBankCode.postalcode,
   						 peoplename=:stBankCode.peoplename,
   						 peoplephone=:stBankCode.peoplephone,
   						 peoplemobile=:stBankCode.peoplemobile,
   						 email=:stBankCode.email,
   						 opersign=:stBankCode.opersign,
   						 effectdate=:stBankCode.effectdate,
   						 updatearea=:stBankCode.updatearea
   				   where reckbankno=:stBankCode.reckbankno;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24461, "�����������д���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����������д���ʧ��[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_bankcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where reckbankno ='%s'" , stBankCode.effectdate,stBankCode.opersign,stBankCode.reckbankno);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24462, "ע���������д���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���������д���ʧ��[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
    
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103 
   				EXEC SQL UPDATE tips_bankcodeinfo
   					 SET  effectdate=:stBankCode.effectdate,
   						  opersign=:stBankCode.opersign
   					WHERE reckbankno=:stBankCode.reckbankno;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24462, "ע���������д���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���������д���ʧ��[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
   				*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum102Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num102succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[�������д���]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����������д����������ɹ�����[%d]", iNum102Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_Node
��������: ���¹�������-�ڵ����
��������: 
  ���¹�������-�ڵ����
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�ڵ����	tips_nodecodeinfo

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Node(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_NODECODEINFO stNodeCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum103;
    int iNum103Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_NODECODEINFO stNodeCode;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("���½ڵ��������ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/NodeCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum103 = 0;
    else
     	iNum103 = atoi(sBuf);
    
    if ( iNum103 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-�ڵ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-�ڵ����,��[%d]��", iNum103),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ�ڵ������ϸ*/
    for(i = 1; i <= iNum103; i ++)
    {
        memset(&stNodeCode, 0x00, sizeof(stNodeCode));
   		/*1.�ڵ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/NodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.nodecode, sTmpBuf, sizeof(stNodeCode.nodecode));
   		/*2.�ڵ�����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/NodeName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.nodename, sTmpBuf, sizeof(stNodeCode.nodename));
   		/*3.�ڵ���������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/OfNodeType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.ofnodetype, sTmpBuf, sizeof(stNodeCode.ofnodetype));
   		/*4.�ڵ���֤��־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/NodeDN",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.nodedn, sTmpBuf, sizeof(stNodeCode.nodedn));
   		/*5.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.opersign, sTmpBuf, sizeof(stNodeCode.opersign));
   		/*6.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.effectdate, sTmpBuf, sizeof(stNodeCode.effectdate));
   		/*7.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.updatearea, sTmpBuf, sizeof(stNodeCode.updatearea));
   		switch(atoi(stNodeCode.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_nodecodeinfo", SD_TIPS_NODECODEINFO, NUMELE(SD_TIPS_NODECODEINFO), &stNodeCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24463, "�����ڵ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����ڵ����ʧ��[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum103Succ ++;
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103 
   				EXEC SQL INSERT INTO tips_nodecodeinfo VALUES(:stNodeCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24463, "�����ڵ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����ڵ����ʧ��[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		*/
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stNodeCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "nodecode ='%s'", stNodeCode.nodecode); 
    			iRet = DBUpdate("tips_nodecodeinfo", SD_TIPS_NODECODEINFO, NUMELE(SD_TIPS_NODECODEINFO), &stNodeCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24464, "���½ڵ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("���½ڵ����ʧ��[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      			    
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103
   				EXEC SQL UPDATE tips_nodecodeinfo
   					 SET nodename=:stNodeCode.nodename,
   						 ofnodetype=:stNodeCode.ofnodetype,
   						 nodedn=:stNodeCode.nodedn,
   						 opersign=:stNodeCode.opersign,
   						 effectdate=:stNodeCode.effectdate,
   						 updatearea=:stNodeCode.updatearea
   				   WHERE nodecode=:stNodeCode.nodecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24464, "���½ڵ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("���½ڵ����ʧ��[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_nodecodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where nodecode ='%s'" , stNodeCode.effectdate,stNodeCode.opersign,stNodeCode.nodecode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24465, "ע���ڵ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���ڵ����ʧ��[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		/* end add dci 20141103 */
   				
   				/* mod dci 20141103   				
   				EXEC SQL UPDATE tips_nodecodeinfo
   					 SET  effectdate=:stNodeCode.effectdate,
   						  opersign=:stNodeCode.opersign
   					WHERE nodecode=:stNodeCode.nodecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24465, "ע���ڵ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���ڵ����ʧ��[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum103Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num103succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[�ڵ����]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���½ڵ�����������ɹ�����[%d]", iNum103Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_Tre
��������: ���¹�������-�������
��������: 
  ���¹�������-�������
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�ڵ����	tips_trecodeinfo

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Tre(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_TRECODEINFO stTreCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum104;
    int iNum104Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TRECODEINFO stTreCode;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("���¹����������ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TreCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum104 = 0;
    else
     	iNum104 = atoi(sBuf);
    
    if ( iNum104 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-�������");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-�������,��[%d]��", iNum104),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ���������ϸ*/
    for(i = 1; i <= iNum104; i ++)
    {
        memset(&stTreCode, 0x00, sizeof(stTreCode));
   		/*1.�������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/TreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.trecode, sTmpBuf, sizeof(stTreCode.trecode));
   		/*2.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/TreName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.trename, sTmpBuf, sizeof(stTreCode.trename));
   		/*3.���⼶��*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/TreLevel",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.trelevel, sTmpBuf, sizeof(stTreCode.trelevel));
   		/*4.֧���к�*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PayBankNo",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.paybankno, sTmpBuf, sizeof(stTreCode.paybankno));
   		/*5.����������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/ReckonTreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.reckontrecode, sTmpBuf, sizeof(stTreCode.reckontrecode));
   		/*6.����������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/UpTreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.uptrecode, sTmpBuf, sizeof(stTreCode.uptrecode));
   		/*7.�����ڵ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OfNodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofnodecode, sTmpBuf, sizeof(stTreCode.ofnodecode));
   		/*8.����ʡ�ֿ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OfProvTrea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofprovtrea, sTmpBuf, sizeof(stTreCode.ofprovtrea));
   		/*9.��������֧�����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OfCityTrea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofcitytrea, sTmpBuf, sizeof(stTreCode.ofcitytrea));
   		/*10.������֧�����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/ofCountyTrea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofcountytrea, sTmpBuf, sizeof(stTreCode.ofcountytrea));
   		/*11.��ַ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/Address",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.address, sTmpBuf, sizeof(stTreCode.address));
   		/*12.��������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PostalCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.postalcode, sTmpBuf, sizeof(stTreCode.postalcode));
   		/*13.��ϵ������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PeopleName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.peoplename, sTmpBuf, sizeof(stTreCode.peoplename));
   		/*14.��ϵ������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PeoplePhone",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.peoplephone, sTmpBuf, sizeof(stTreCode.peoplephone));
   		/*15.��ϵ���ֻ�*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PeopleMobile",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.peoplemobile, sTmpBuf, sizeof(stTreCode.peoplemobile));
   		/*16.Email*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/Email",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.email, sTmpBuf, sizeof(stTreCode.email));
   		/*17.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.opersign, sTmpBuf, sizeof(stTreCode.opersign));
   		/*18.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.effectdate, sTmpBuf, sizeof(stTreCode.effectdate));
   		/*19.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.updatearea, sTmpBuf, sizeof(stTreCode.updatearea));
   		switch(atoi(stTreCode.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_trecodeinfo", SD_TIPS_TRECODEINFO, NUMELE(SD_TIPS_TRECODEINFO), &stTreCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24466, "�����������ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD,Fmtmsg("�����������ʧ��[%d],trecode=[%s]", i, stTreCode.trecode),
                fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum104Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_trecodeinfo VALUES(:stTreCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24466, "�����������ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����������ʧ��[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum104Succ ++;
      		*/
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stTreCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "trecode ='%s'", stTreCode.trecode); 
    			iRet = DBUpdate("tips_trecodeinfo", SD_TIPS_TRECODEINFO, NUMELE(SD_TIPS_TRECODEINFO), &stTreCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24467, "���¹������ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("���¹������ʧ��[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum104Succ ++;
      		
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_trecodeinfo
   					 SET trename=:stTreCode.trename,
   					     trelevel=:stTreCode.trelevel,
   					     paybankno=:stTreCode.paybankno,
   					     reckontrecode=:stTreCode.reckontrecode,
   					     uptrecode=:stTreCode.uptrecode,
   					     ofprovtrea=:stTreCode.ofprovtrea,
   					     ofcitytrea=:stTreCode.ofcitytrea,
   					     ofcountytrea=:stTreCode.ofcountytrea,
   						 ofnodecode=:stTreCode.ofnodecode,
   						 address=:stTreCode.address,
   						 postalcode=:stTreCode.postalcode,
   						 peoplename=:stTreCode.peoplename,
   						 peoplephone=:stTreCode.peoplephone,
   						 peoplemobile=:stTreCode.peoplemobile,
   						 email=:stTreCode.email,
   						 opersign=:stTreCode.opersign,
   						 effectdate=:stTreCode.effectdate,
   						 updatearea=:stTreCode.updatearea
   				   WHERE trecode=:stTreCode.trecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24467, "���¹������ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("���¹������ʧ��[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum104Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_trecodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where trecode ='%s'" , stTreCode.effectdate,stTreCode.opersign,stTreCode.trecode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24468, "ע���������ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���������ʧ��[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum104Succ ++;
      		/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_trecodeinfo
   					 SET  effectdate=:stTreCode.effectdate,
   						  opersign=:stTreCode.opersign
   					WHERE trecode=:stTreCode.trecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24468, "ע���������ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���������ʧ��[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum104Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum104Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num104succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[�������]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���¹�������������ɹ�����[%d]", iNum104Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_Bud
��������: ���¹�������-Ԥ���Ŀ
��������: 
  ���¹�������-Ԥ���Ŀ
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
Ԥ���Ŀ	tips_budgetsubjec

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Bud(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_BUDGETSUBJECT stBudget;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum105;
    int iNum105Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_BUDGETSUBJECT stBudget;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("����Ԥ���Ŀ�����ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BudgetSubjectCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum105 = 0;
    else
     	iNum105 = atoi(sBuf);
    
    if ( iNum105 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-Ԥ���Ŀ");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-Ԥ���Ŀ,��[%d]��", iNum105),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡԤ���Ŀ��ϸ*/
    for(i = 1; i <= iNum105; i ++)
    {
        memset(&stBudget, 0x00, sizeof(stBudget));
   		/*1.Ԥ���Ŀ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/BudgetSubjectCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.budgetsubjectcode, sTmpBuf, sizeof(stBudget.budgetsubjectcode));
   		/*2.Ԥ���Ŀ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/BudgetSubjectName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.budgetsubjectname, sTmpBuf, sizeof(stBudget.budgetsubjectname));
   		/*3.��Ŀ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/SubjectType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.subjecttype, sTmpBuf, sizeof(stBudget.subjecttype));
   		/*4.��֧��־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/IESign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.iesign, sTmpBuf, sizeof(stBudget.iesign));
   		/*5.��Ŀ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/BudgetAttrib",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.budgetattrib, sTmpBuf, sizeof(stBudget.budgetattrib));
   		/*6.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.opersign, sTmpBuf, sizeof(stBudget.opersign));
   		/*7.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.effectdate, sTmpBuf, sizeof(stBudget.effectdate));
   		/*8.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.updatearea, sTmpBuf, sizeof(stBudget.updatearea));
   		switch(atoi(stBudget.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_budgetsubject", SD_TIPS_BUDGETSUBJECT, NUMELE(SD_TIPS_BUDGETSUBJECT), &stBudget, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24469, "����Ԥ���Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����Ԥ���Ŀ����ʧ��[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_budgetsubject VALUES(:stBudget);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24469, "����Ԥ���Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����Ԥ���Ŀ����ʧ��[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
      		*/
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stBudget.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "budgetsubjectcode ='%s' and subjecttype='%s' and iesign='%s'", \
		    		stBudget.budgetsubjectcode,stBudget.subjecttype,stBudget.iesign); 
    			iRet = DBUpdate("tips_budgetsubject", SD_TIPS_BUDGETSUBJECT, NUMELE(SD_TIPS_BUDGETSUBJECT), &stBudget, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24470, "����Ԥ���Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����Ԥ���Ŀ����ʧ��[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum105Succ ++;
					/* end add dci 20141103 */
					
					/* mod dci 20141103 
   				EXEC SQL UPDATE tips_budgetsubject
   					 SET budgetsubjectname=:stBudget.budgetsubjectname,
   						 budgetattrib=:stBudget.budgetattrib,
   						 opersign=:stBudget.opersign,
   						 effectdate=:stBudget.effectdate,
   						 updatearea=:stBudget.updatearea
   				   WHERE budgetsubjectcode=:stBudget.budgetsubjectcode
   				     AND subjecttype=:stBudget.subjecttype
   				     AND iesign=:stBudget.iesign;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24470, "����Ԥ���Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����Ԥ���Ŀ����ʧ��[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_bankcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where budgetsubjectcode ='%s' and subjecttype='%s' and iesign='%s'", \
		    		stBudget.effectdate,stBudget.opersign,stBudget.budgetsubjectcode,stBudget.subjecttype,stBudget.iesign);      			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24471, "ע��Ԥ���Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע��Ԥ���Ŀ����ʧ��[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum105Succ ++;
    
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_budgetsubject
   					 SET  effectdate=:stBudget.effectdate,
   						  opersign=:stBudget.opersign
   				   WHERE budgetsubjectcode=:stBudget.budgetsubjectcode
   				     AND subjecttype=:stBudget.subjecttype
   				     AND iesign=:stBudget.iesign;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24471, "ע��Ԥ���Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע��Ԥ���Ŀ����ʧ��[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum105Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num105succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[Ԥ���Ŀ����]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("����Ԥ���Ŀ�����������ɹ�����[%d]", iNum105Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_Rea
��������: ���¹�������-�˿�ԭ�����
��������: 
  ���¹�������-�˿�ԭ�����
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�ڵ����	tips_returnreason

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Rea(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_RETURNREASON stReturn;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum106;
    int iNum106Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_RETURNREASON stReturn;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("�����˿�ԭ���������ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/ReturnReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum106 = 0;
    else
     	iNum106 = atoi(sBuf);
    
    if ( iNum106 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-�˿�ԭ�����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-�˿�ԭ�����,��[%d]��", iNum106),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ�˿�ԭ�������ϸ*/
    for(i = 1; i <= iNum106; i ++)
    {
        memset(&stReturn, 0x00, sizeof(stReturn));
   		/*1.�˿�ԭ�����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/ReasonCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.reasoncode, sTmpBuf, sizeof(stReturn.reasoncode));
   		/*2.����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.description, sTmpBuf, sizeof(stReturn.description));
   		/*3.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.opersign, sTmpBuf, sizeof(stReturn.opersign));
   		/*4.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.effectdate, sTmpBuf, sizeof(stReturn.effectdate));
   		/*5.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.updatearea, sTmpBuf, sizeof(stReturn.updatearea));
   		switch(atoi(stReturn.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_returnreason", SD_TIPS_RETURNREASON, NUMELE(SD_TIPS_RETURNREASON), &stReturn, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24472, "�����˿�ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����˿�ԭ�����ʧ��[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_returnreason VALUES(:stReturn);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24472, "�����˿�ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����˿�ԭ�����ʧ��[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
      		*/	    
      			    
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stReturn.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "reasoncode ='%s'", stReturn.reasoncode); 
    			iRet = DBUpdate("tips_returnreason", SD_TIPS_RETURNREASON, NUMELE(SD_TIPS_RETURNREASON), &stReturn, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24473, "�����˿�ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����˿�ԭ�����ʧ��[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum106Succ ++;
      		
					/* end add dci 20141103 */
					
					/* mod dci 20141103 
   				EXEC SQL UPDATE tips_returnreason
   					 SET description=:stReturn.description,
   						 opersign=:stReturn.opersign,
   						 effectdate=:stReturn.effectdate,
   						 updatearea=:stReturn.updatearea
   				   WHERE reasoncode=:stReturn.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24473, "�����˿�ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("�����˿�ԭ�����ʧ��[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_returnreason \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where reasoncode ='%s'" , stReturn.effectdate,stReturn.opersign,stReturn.reasoncode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24474, "ע���˿�ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���˿�ԭ�����ʧ��[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum106Succ ++;
    
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_returnreason
   					 SET  effectdate=:stReturn.effectdate,
   						  opersign=:stReturn.opersign
   					WHERE reasoncode=:stReturn.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24474, "ע���˿�ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע���˿�ԭ�����ʧ��[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum106Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num106succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[�˿�ԭ�����]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����˿�ԭ������������ɹ�����[%d]", iNum106Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_Cor
��������: ���¹�������-����ԭ�����
��������: 
  ���¹�������-����ԭ�����
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�ڵ����	tips_corretreason

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Cor(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
					SDB_TIPS_CORRECTREASON stCorrect;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum107;
    int iNum107Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_CORRECTREASON stCorrect;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("���¸���ԭ���������ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/CorrectReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum107 = 0;
    else
     	iNum107 = atoi(sBuf);
    
    if ( iNum107 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-����ԭ�����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-����ԭ�����,��[%d]��", iNum107),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ����ԭ�������ϸ*/
    for(i = 1; i <= iNum107; i ++)
    {
        memset(&stCorrect, 0x00, sizeof(stCorrect));
   		/*1.����ԭ�����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/ReasonCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.reasoncode, sTmpBuf, sizeof(stCorrect.reasoncode));
   		/*2.����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.description, sTmpBuf, sizeof(stCorrect.description));
   		/*3.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.opersign, sTmpBuf, sizeof(stCorrect.opersign));
   		/*4.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.effectdate, sTmpBuf, sizeof(stCorrect.effectdate));
   		/*5.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.updatearea, sTmpBuf, sizeof(stCorrect.updatearea));
   		switch(atoi(stCorrect.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_correctreason", SD_TIPS_CORRECTREASON, NUMELE(SD_TIPS_CORRECTREASON), &stCorrect, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24475, "��������ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("��������ԭ�����ʧ��[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_correctreason VALUES(:stCorrect);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24475, "��������ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("��������ԭ�����ʧ��[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
      		*/
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stCorrect.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "reasoncode ='%s'", stCorrect.reasoncode); 
    			iRet = DBUpdate("tips_correctreason", SD_TIPS_CORRECTREASON, NUMELE(SD_TIPS_CORRECTREASON), &stCorrect, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24476, "���¸���ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("���¸���ԭ�����ʧ��[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum107Succ ++;
					/* end add dci 20141103 */
					
					/* mod dci 20141103 

   				EXEC SQL UPDATE tips_correctreason
   					 SET description=:stCorrect.description,
   						 opersign=:stCorrect.opersign,
   						 effectdate=:stCorrect.effectdate,
   						 updatearea=:stCorrect.updatearea
   				   WHERE reasoncode=:stCorrect.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24476, "���¸���ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("���¸���ԭ�����ʧ��[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_correctreason \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where reasoncode ='%s'" , stCorrect.effectdate,stCorrect.opersign,stCorrect.reasoncode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24477, "ע������ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע������ԭ�����ʧ��[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
    
   				/* end add dci 20141103 */
					
					/* mod dci 20141103
   				EXEC SQL UPDATE tips_correctreason
   					 SET  effectdate=:stCorrect.effectdate,
   						  opersign=:stCorrect.opersign
   					WHERE reasoncode=:stCorrect.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24477, "ע������ԭ�����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע������ԭ�����ʧ��[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum107Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num107succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[����ԭ�����]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���¸���ԭ������������ɹ�����[%d]", iNum107Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_TaxT
��������: ���¹�������-˰�ִ���
��������: 
  ���¹�������-˰�ִ���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
˰�ִ���	tips_taxtypeinfo

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_TaxT(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_TAXTYPEINFO stTaxType;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum108;
    int iNum108Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TAXTYPEINFO stTaxType;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("����˰�ִ�������ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxTypeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum108 = 0;
    else
     	iNum108 = atoi(sBuf);
    
    if ( iNum108 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-˰�ִ���");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-˰�ִ���,��[%d]��", iNum108),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ˰�ִ�����ϸ*/
    for(i = 1; i <= iNum108; i ++)
    {
        memset(&stTaxType, 0x00, sizeof(stTaxType));
   		/*1.˰�ִ���*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/TaxTypeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.taxtypecode, sTmpBuf, sizeof(stTaxType.taxtypecode));
   		/*2.���ջ�������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/TaxOrgType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.taxorgtype, sTmpBuf, sizeof(stTaxType.taxorgtype));
   		/*3.˰������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/TaxTypeName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.taxtypename, sTmpBuf, sizeof(stTaxType.taxtypename));
   		/*4.����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.description, sTmpBuf, sizeof(stTaxType.description));
   		/*5.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.opersign, sTmpBuf, sizeof(stTaxType.opersign));
   		/*6.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.effectdate, sTmpBuf, sizeof(stTaxType.effectdate));
   		/*7.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.updatearea, sTmpBuf, sizeof(stTaxType.updatearea));
   		switch(atoi(stTaxType.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_taxtypeinfo", SD_TIPS_TAXTYPEINFO, NUMELE(SD_TIPS_TAXTYPEINFO), &stTaxType, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24478, "����˰�ִ���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰�ִ���ʧ��[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_taxtypeinfo VALUES(:stTaxType);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24478, "����˰�ִ���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰�ִ���ʧ��[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
      		*/
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stTaxType.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "taxtypecode ='%s' and taxorgtype='%s'", stTaxType.taxtypecode,stTaxType.taxorgtype); 
    			iRet = DBUpdate("tips_taxtypeinfo", SD_TIPS_TAXTYPEINFO, NUMELE(SD_TIPS_TAXTYPEINFO), &stTaxType, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24479, "����˰�ִ���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰�ִ���ʧ��[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum108Succ ++;
      		
					/* end add dci 20141103 */
					
					/* mod dci 20141103 
   				EXEC SQL UPDATE tips_taxtypeinfo
   					 SET taxorgtype=:stTaxType.taxorgtype,
   					     taxtypename=:stTaxType.taxtypename,
   					     description=:stTaxType.description,
   						 opersign=:stTaxType.opersign,
   						 effectdate=:stTaxType.effectdate,
   						 updatearea=:stTaxType.updatearea
   				   WHERE taxtypecode=:stTaxType.taxtypecode
   				     AND taxorgtype=:stTaxType.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24479, "����˰�ִ���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰�ִ���ʧ��[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_bankcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where taxtypecode ='%s' and taxorgtype='%s'" ,\
    									stTaxType.effectdate,stTaxType.opersign,stTaxType.taxtypecode,stTaxType.taxorgtype);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24480, "ע��˰�ִ���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע��˰�ִ���ʧ��[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum108Succ ++;
    
   				/* end add dci 20141103 */
					
					/* mod dci 20141103
   				EXEC SQL UPDATE tips_taxtypeinfo
   					 SET  effectdate=:stTaxType.effectdate,
   						  opersign=:stTaxType.opersign
   					WHERE taxtypecode=:stTaxType.taxtypecode
   					  AND taxorgtype=:stTaxType.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24480, "ע��˰�ִ���ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע��˰�ִ���ʧ��[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum108Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num108succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[˰�ִ���]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("����˰�ִ����������ɹ�����[%d]", iNum108Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: prv_tips_UpdPUBDATA_TaxS
��������: ���¹�������-˰Ŀ����
��������: 
  ���¹�������-˰Ŀ����
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
˰Ŀ����	tips_taxsubject

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_TaxS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_TAXSUBJECT stTaxSubject;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum109;
    int iNum109Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TAXSUBJECT stTaxSubject;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("����˰Ŀ��������ݿ�ʼ"),fpub_GetCompname(lXmlhandle));
    iNum109Succ=0;
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxSubjectInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum109 = 0;
    else
     	iNum109 = atoi(sBuf);
    
    if ( iNum109 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "������¹�������-˰Ŀ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("������¹�������-˰Ŀ����,��[%d]��", iNum109),
            fpub_GetCompname(lXmlhandle))        
    }
    /*ȡ˰Ŀ������ϸ*/
    for(i = 1; i <= iNum109; i ++)
    {
        memset(&stTaxSubject, 0x00, sizeof(stTaxSubject));
   		/*1.˰Ŀ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/TaxSubjectCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.taxsubjectcode, sTmpBuf, sizeof(stTaxSubject.taxsubjectcode));
   		/*2.���ջ�������*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/TaxOrgType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.taxorgtype, sTmpBuf, sizeof(stTaxSubject.taxorgtype));
   		/*3.˰Ŀ����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/TaxSubjectName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.taxsubjectname, sTmpBuf, sizeof(stTaxSubject.taxsubjectname));
   		/*4.����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.description, sTmpBuf, sizeof(stTaxSubject.description));
   		/*5.������־*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.opersign, sTmpBuf, sizeof(stTaxSubject.opersign));
   		/*6.��Ч����*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.effectdate, sTmpBuf, sizeof(stTaxSubject.effectdate));
   		/*7.���·�Χ*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.updatearea, sTmpBuf, sizeof(stTaxSubject.updatearea));
   		switch(atoi(stTaxSubject.opersign))
   		{
   			case 1: /*����*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_taxsubject", SD_TIPS_TAXSUBJECT, NUMELE(SD_TIPS_TAXSUBJECT), &stTaxSubject, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24481, "����˰Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰Ŀ����ʧ��[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum109Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_taxsubject VALUES(:stTaxSubject);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24481, "����˰Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰Ŀ����ʧ��[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum109Succ ++;
      		*/
   				break;
   			case 2: /*�޸�*/
   				/*if(atol(GetSysDate()) <= atol(stTaxSubject.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "taxsubjectcode ='%s' and taxorgtype='%s'", \
		    		stTaxSubject.taxsubjectcode,stTaxSubject.taxorgtype); 
    			iRet = DBUpdate("tips_taxsubject", SD_TIPS_TAXSUBJECT, NUMELE(SD_TIPS_TAXSUBJECT), &stTaxSubject, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24482, "����˰Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰Ŀ����ʧ��[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum109Succ ++;
					/* end add dci 20141103 */
					
					/* mod dci 20141103 

   				EXEC SQL UPDATE tips_taxsubject
   					 SET taxorgtype=:stTaxSubject.taxorgtype,
   					     taxsubjectname=:stTaxSubject.taxsubjectname,
   					     description=:stTaxSubject.description,
   						 opersign=:stTaxSubject.opersign,
   						 effectdate=:stTaxSubject.effectdate,
   						 updatearea=:stTaxSubject.updatearea
   				   WHERE taxsubjectcode=:stTaxSubject.taxsubjectcode
   				     AND taxorgtype=:stTaxSubject.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24482, "����˰Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("����˰Ŀ����ʧ��[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum109Succ ++;
      		*/
   				break;
   			case 3: /*ע��*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_taxsubject \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where taxsubjectcode ='%s' and taxorgtype='%s'", \
		    		stTaxSubject.effectdate,stTaxSubject.opersign,stTaxSubject.taxsubjectcode,stTaxSubject.taxorgtype);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24483, "ע��˰Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע��˰Ŀ����ʧ��[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum109Succ ++;
    
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_taxsubject
   					 SET  effectdate=:stTaxSubject.effectdate,
   						  opersign=:stTaxSubject.opersign
   					WHERE taxsubjectcode=:stTaxSubject.taxsubjectcode
   					  AND taxorgtype=:stTaxSubject.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24483, "ע��˰Ŀ����ʧ��");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("ע��˰Ŀ����ʧ��[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum109Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum109Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num109succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "���¹�������[˰Ŀ����]�������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("����˰Ŀ�����������ɹ�����[%d]", iNum109Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdPUBDATA
�������: ���¹�������
�������: 
  ���¹�������
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
���ݸ��»��ܱ�	tips_sjgxhz

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdPUBDATA(HXMLTREE lXmlhandle)
{
    int iParas;
    char sZwrq[8+1];
    int  iZhqzlsh;
    char sWorkDate[8+1];
    char sUpdateBatch[8+1];    
    char sBuf[256];
    int iRet;
    
    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
    
    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( sZwrq, sBuf, sizeof(sZwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "�ۺ�ǰ����ˮ��")
    iZhqzlsh=atoi(sBuf);   

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sWorkDate, 0x00, sizeof(sWorkDate));
    COMP_GETPARSEPARAS(3, sBuf, "��������")
    pstrcopy( sWorkDate, sBuf, sizeof(sWorkDate));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sUpdateBatch, 0x00, sizeof(sUpdateBatch));
    COMP_GETPARSEPARAS(4, sBuf, "��������")
    pstrcopy( sUpdateBatch, sBuf, sizeof(sUpdateBatch));

    LOG(LM_STD,Fmtmsg("���¹������ݿ�ʼ����..."), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("��������[%s],ǰ����ˮ��[%d],��������[%s],��������[%s]...",
        sZwrq, iZhqzlsh, sWorkDate, sUpdateBatch), fpub_GetCompname(lXmlhandle))   
    
    /* �������ջ��ش��� */
    iRet = prv_tips_UpdPUBDATA_Tax(lXmlhandle);
    /* �����������д��� */
    iRet = prv_tips_UpdPUBDATA_Bank(lXmlhandle);   
    /* ���½ڵ���� */
    iRet = prv_tips_UpdPUBDATA_Node(lXmlhandle);
    /* ���¹������ */
    iRet = prv_tips_UpdPUBDATA_Tre(lXmlhandle);
    /* ����Ԥ���Ŀ���� */
    iRet = prv_tips_UpdPUBDATA_Bud(lXmlhandle);   
    /* �����˿�ԭ����� */
    iRet = prv_tips_UpdPUBDATA_Rea(lXmlhandle);
    /* ���¸���ԭ����� */
    iRet = prv_tips_UpdPUBDATA_Cor(lXmlhandle);
    /* ����˰�ִ��� */
    iRet = prv_tips_UpdPUBDATA_TaxT(lXmlhandle);
    /* ����˰Ŀ���� */
    iRet = prv_tips_UpdPUBDATA_TaxS(lXmlhandle);
    /* �Ǽ����ݸ��»��ܱ� */
    iRet = prv_tips_UpdPUBDATA(lXmlhandle, sZwrq, iZhqzlsh, sWorkDate, sUpdateBatch);
        
    fpub_SetMsg(lXmlhandle, 0, "���¹������ݴ������");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���¹������ݴ������..."), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;   
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitZYGSBW
�������: ��ʼ���ɸ�ʽ���ı�
�������: 
  ��ʼ���ɸ�ʽ���ı�
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
���ɸ�ʽ����	tips_zygsbw

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��19��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitZYGSBW(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_ZYGSBW stZygsbw;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[2050];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_ZYGSBW stZygsbw;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("��ʼ���ɸ�ʽ���ı����ݿ�ʼ����..."),fpub_GetCompname(lXmlhandle))

    memset(&stZygsbw, 0x00, sizeof(stZygsbw));
    COMP_PARACOUNTCHK(2);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    pstrcopy(stZygsbw.zwrq, sBuf, sizeof(stZygsbw.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�ۺ�ǰ����ˮ��")
    stZygsbw.zhqzlsh=atoi(sBuf);

    LOG(LM_STD,Fmtmsg("��������[%s],ǰ����ˮ��[%d]...", stZygsbw.zwrq, stZygsbw.zhqzlsh),fpub_GetCompname(lXmlhandle))

    /* 3.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stZygsbw.workdate, sBuf, sizeof(stZygsbw.workdate));
    /* 4.��Ϣ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MsgType", sBuf)
    pstrcopy(stZygsbw.msgtype, sBuf, sizeof(stZygsbw.msgtype));
    /* 5.Դ�ڵ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/SrcNodeCode", sBuf)
    pstrcopy(stZygsbw.srcnodecode, sBuf, sizeof(stZygsbw.srcnodecode));
    /* 6.Ŀ�Ľڵ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/DesNodeCode", sBuf)
    pstrcopy(stZygsbw.desnodecode, sBuf, sizeof(stZygsbw.desnodecode));    
    /* 7.����������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/SendOrgCode", sBuf)
    pstrcopy(stZygsbw.sendorgcode, sBuf, sizeof(stZygsbw.sendorgcode));
    /* 8.���ջ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/RcvOrgCode", sBuf)
    pstrcopy(stZygsbw.rcvorgcode, sBuf, sizeof(stZygsbw.rcvorgcode));      
    /* 9.�Ķ���־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ydbz", sBuf)
    pstrcopy(stZygsbw.ydbz, sBuf, sizeof(stZygsbw.ydbz));
    /* 10.���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Content", sBuf)
    pstrcopy(stZygsbw.content, sBuf, sizeof(stZygsbw.content));    
    /* 11.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stZygsbw.jyrq, sBuf, sizeof(stZygsbw.jyrq));
    /* 12.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stZygsbw.jysj, sBuf, sizeof(stZygsbw.jysj)); 
    /* 13.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh", sBuf)
    pstrcopy(stZygsbw.dqdh, sBuf, sizeof(stZygsbw.dqdh));
    /* 14.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jgdh", sBuf)
    pstrcopy(stZygsbw.jgdh, sBuf, sizeof(stZygsbw.jgdh));    
    /* 15.���׹�Ա */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stZygsbw.jygy, sBuf, sizeof(stZygsbw.jygy));
    /* 16.�ն˴��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stZygsbw.zddh, sBuf, sizeof(stZygsbw.zddh)); 
    /* 17.�����ֶ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/byzd", sBuf)
    pstrcopy(stZygsbw.byzd, sBuf, sizeof(stZygsbw.byzd));
		/* add dci 20141103 */
   	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_zygsbw", SD_TIPS_ZYGSBW, NUMELE(SD_TIPS_ZYGSBW), &stZygsbw, sErrmsg);
    if( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      	fpub_SetMsg(lXmlhandle, 24484, "��ʼ�����ɸ�ʽ���ı�����ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InitZYGSBW��ʼ�����ɸ�ʽ���ı�����ʧ��"),
          fpub_GetCompname(lXmlhandle))  
    }	 
   	/* end add dci 20141103 */
		
		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_zygsbw  VALUES (:stZygsbw);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24484, "��ʼ�����ɸ�ʽ���ı�����ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InitZYGSBW��ʼ�����ɸ�ʽ���ı�����ʧ��"),
            fpub_GetCompname(lXmlhandle))  
    }	 
    */   

    fpub_SetMsg(lXmlhandle, 0, "��ʼ�����ɸ�ʽ���ı����ݳɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("��ʼ�����ɸ�ʽ���ı����ݳɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;     
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_AddBEGIN
�������: ���ļ�ͷ��BEGIN
�������: 
  ���ļ�ͷ��BEGIN
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��03��4��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_AddBEGIN(HXMLTREE lXmlhandle)
{
    int iParas;
    char sOutFileName[255];
    FILE *Outfp;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1)
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(1,sOutFileName,"�ϲ����ļ���");
      
    /*�Ƚ������ļ�,У��*/
    Outfp = fopen(sOutFileName,"w+");
    if ( Outfp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24114, "���ļ�ͷ��BEGINʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ļ�ͷ��BEGINʧ��[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
     
    fprintf(Outfp,"BEGIN\n");       

    fclose(Outfp);
    fpub_SetMsg(lXmlhandle, 0, "�����ļ�ӦBEGIN�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����ļ�ӦBEGIN�ɹ�"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;
   
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_AddFileBEGIN
�������: ���ļ�ͷ��BEGIN
�������: 
  ���ļ�ͷ���ض��ַ���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: 
��������: 2014��09��03��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_AddFileBEGIN(HXMLTREE lXmlhandle)
{
    int iParas;
    char sOutFileName[255];
    char sBeginStr[255];
    FILE *Outfp;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1)
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(1,sOutFileName,"�ϲ����ļ���");
    COMP_PARACOUNTCHK(2)
    memset(sBeginStr, 0x00, sizeof(sBeginStr));
    COMP_GETPARSEPARAS(2,sBeginStr,"׷���ļ�ͷ���ַ���");
      
    /*�Ƚ������ļ�,У��*/
    Outfp = fopen(sOutFileName,"w+");
    if ( Outfp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24114, "���ļ�ͷ��ͷʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ļ�ͷ��ͷʧ��[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
    
    if ( strlen(sBeginStr) <=0 )
    {
         fpub_SetMsg(lXmlhandle, 24114, "׷���ַ���Ϊ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ļ�ͷ��ͷʧ��[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
     
    fprintf(Outfp,"%s\n",sBeginStr);       

    fclose(Outfp);
    fpub_SetMsg(lXmlhandle, 0, "�����ļ�ӦBEGIN�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����ļ�ӦBEGIN�ɹ�"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;
   
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_AddEND
�������: ���ļ�β��END
�������: 
  ���ļ�β��END
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��03��4��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_AddEND(HXMLTREE lXmlhandle)
{
    int iParas;
    char sOutFileName[255];
    FILE *Outfp;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1)
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(1,sOutFileName,"�ϲ����ļ���");
      
    /*�Ƚ������ļ�,У��*/
    Outfp = fopen(sOutFileName,"a+");
    if ( Outfp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24115, "���ļ�β��ENDʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ļ�β��ENDʧ��[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
     
    fprintf(Outfp,"END\n");       

    fclose(Outfp);
    fpub_SetMsg(lXmlhandle, 0, "���ļ�β��END�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���ļ�β��END�ɹ�"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;
   
}    
 
/************************************************************************
��̬�����������
�����������: SYW_TIPS_UniteTWOFILE
�������: �ϲ������ļ�
�������: 
  �ϲ������ļ�
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��03��4��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/    
IRESULT SYW_TIPS_UniteTWOFILE(HXMLTREE lXmlhandle)
{

    int iParas;
    char sDrFileName[255],sOutFileName[255];
    char sLine[1024];
    FILE *Drfp,*Outfp;
    int i;
    int iFlag;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(2)
    memset(sDrFileName, 0x00, sizeof(sDrFileName));    
    COMP_GETPARSEPARAS(1,sDrFileName,"���ļ���");
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(2,sOutFileName,"ĸ�ļ���");
    trim(sDrFileName);trim(sOutFileName);

    LOG(LM_STD,Fmtmsg("���ļ���[%s],ĸ�ļ���[%s]", sDrFileName, sOutFileName), fpub_GetCompname(lXmlhandle));
          
    /*�Ƚ�ĸ�ļ�,У��*/
    Outfp = fopen(sOutFileName,"a+");
    if ( Outfp == NULL )
    {
        fpub_SetMsg(lXmlhandle, 24116, "���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ļ�ʧ��[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
   
    /*�����ļ�,У��*/
    Drfp = fopen(sDrFileName,"r");
    if ( Drfp == NULL )
    {
   	    fclose(Outfp);
        fpub_SetMsg(lXmlhandle, 24116, "���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ļ�ʧ��[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
   
    /*�ļ��崦��,��������ˮ�ļ�����д��ϲ��ļ�*/
    for (iFlag=0,i=1; ;i++)
    {   	
        memset(sLine,0x00,sizeof(sLine)); 
        if (fgets(sLine,sizeof(sLine),Drfp)	== NULL)
            break;                   /*�ļ����� ����*/
        sLine[strlen(sLine)-1]=0;   /*ȥ�����һ�����з�*/       
        fprintf(Outfp,"%s\n",sLine);       
    }/*end for*/
    fclose(Drfp);
    fclose(Outfp);
   
    fpub_SetMsg(lXmlhandle, 0, "�ϲ��ļ��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�ϲ��ļ��ɹ�"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;   
}
    
/*��ͨѶ���������ݷ���ָ����XML�����*/
IRESULT STIPS_Hex2Asc(HXMLTREE lXmlhandle)
{
    char sSrcPara[50], spara[50], sBz[30];
    char sCommbuf[32000];  
    long lCommlen;
    int iParas;
    
    fpub_InitSoComp(lXmlhandle);
    COMP_PARACOUNTCHK(3);
    COMP_GETPARAS(1,sSrcPara,"ԴXML��");
    COMP_GETPARAS(2,spara,"Ŀ��XML��");
    COMP_GETPARSEPARAS(3,sBz,"��־0 BCD->ASC ��0 ASC->BCD");
    trim(sBz);
    if (sBz[0]=='0')
    {  
        if ( (lCommlen=xml_GetBinElement(lXmlhandle,sSrcPara,sCommbuf,sizeof(sCommbuf))) < 0 )
        {
            LOG(LM_STD,Fmtmsg(MSG_SYS_XMLGET,XMLNM_COMMBUF,GETXMLERR),"")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_XMLPARSE,spara,GETXMLERR),"")
        } 
        COMP_HARDSETXML(spara,sCommbuf);
    }
    else
    {
        COMP_HARDGETXML(sSrcPara,sCommbuf);
        if ( (lCommlen=xml_SetBinElement(lXmlhandle,spara,sCommbuf,strlen(sCommbuf))) < 0 ) //modefy by lrj 20180810
        {
            LOG(LM_STD,Fmtmsg(MSG_SYS_XMLGET,XMLNM_COMMBUF,GETXMLERR),"")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_XMLPARSE,spara,GETXMLERR),"")
        }   
    }
   
    fpub_SetCompStatus(lXmlhandle,COMPRET_SUCC);
    return COMPRET_SUCC;  	
}

/*�Ƚ�����1�Ƿ��������2
 *1-�� 0-��
 *��ϵͳ���(DATA_VarCompare)�����ã���д�����
 */
IRESULT STIPS_DateCompare(HXMLTREE lXmlhandle)
{
    char sBuf[256];
    char sDate1[8+1];
    char sDate2[8+1];
    char sDate1Year[4+1], sDate1Mon[2+1], sDate1Day[2+1]; 
    char sDate2Year[4+1], sDate2Mon[2+1], sDate2Day[2+1];  
    int iParas;
    int iResult = 0 ;/* ����һС�����ڶ�,�� */
    
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDate1, 0x00, sizeof(sDate1));
    COMP_GETPARSEPARAS(1,sBuf,"����1");
    pstrcopy(sDate1, sBuf, sizeof(sDate1));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDate2, 0x00, sizeof(sDate2));
    COMP_GETPARSEPARAS(2,sBuf,"����2");
    pstrcopy(sDate2, sBuf, sizeof(sDate2));
    
    LOG(LM_STD,Fmtmsg("�Ƚ�����1[%s]�Ƿ��������2[%s]��ʼ����", 
        sDate1, sDate2), fpub_GetCompname(lXmlhandle))
    
    /* �������ڷֱ�ŵ����Ե������ձ�����ȥ */
    memset(sDate1Year, 0x00, sizeof(sDate1Year));
    memset(sDate1Mon, 0x00, sizeof(sDate1Mon));
    memset(sDate1Day, 0x00, sizeof(sDate1Day));
    pstrcopy(sDate1Year, sDate1, sizeof(sDate1Year));
    pstrcopy(sDate1Mon, sDate1+4, sizeof(sDate1Mon));
    pstrcopy(sDate1Day, sDate1+4+2, sizeof(sDate1Day));
    LOG(LM_STD,Fmtmsg("����1-->year[%s],mon[%s],day[%s]", 
        sDate1Year, sDate1Mon, sDate1Day), fpub_GetCompname(lXmlhandle))
    memset(sDate2Year, 0x00, sizeof(sDate2Year));
    memset(sDate2Mon, 0x00, sizeof(sDate2Mon));
    memset(sDate2Day, 0x00, sizeof(sDate2Day));
    pstrcopy(sDate2Year, sDate2, sizeof(sDate2Year));
    pstrcopy(sDate2Mon, sDate2+4, sizeof(sDate2Mon));
    pstrcopy(sDate2Day, sDate2+4+2, sizeof(sDate2Day));    
    LOG(LM_STD,Fmtmsg("����2-->year[%s],mon[%s],day[%s]", 
        sDate2Year, sDate2Mon, sDate2Day), fpub_GetCompname(lXmlhandle))    
    /* ��ʼ�������ڱȽ� */
    if(atoi(sDate1Year) > atoi(sDate2Year))
    {
        iResult = 1 ;
    }else/* ������,�����·ݱȽ� */
    {
        if(atoi(sDate1Mon) > atoi(sDate2Mon))
        {
            iResult = 1 ;
        }else/* ���·���ȣ������շݱȽ� */
        {
            if(atoi(sDate1Day) > atoi(sDate2Day))
                 iResult = 1 ;
        }        
    }        

    fpub_SetCompStatus(lXmlhandle,iResult);
    return COMPRET_SUCC;  	
}

/******************************************************************************
��̬�����������
�����������: SYW_TIPS_FileToBuf
�������: ���ļ����ݵ��뵽commbuf
�������: 
          
�������: 
��� ��������         ��Դ���   ȱʡֵ         �Ƿ�ɿ�  ����˵��
 

������״̬: 
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ: 
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ
  
��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:
          
�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա: tuql
��������: 2009��04��29��
�޸�����: 
����ʹ��ʾ��: 
******************************************************************************/ 
IRESULT SYW_TIPS_FileToBuf(HXMLTREE lXmlhandle)
{ 
   
    int iParas,iRet,ilen2;
    char sfile[256];
    char *sbuf;
    char snode[30];
    FILE *fp;
    struct stat struStat;
    char *pstr;/* add by tuql 20090831 */
    int ilen=0;/* add by tuql 20090831 */
    char sBaseNode[256];
       
    fpub_InitSoComp(lXmlhandle);

    memset(sfile, 0x00, sizeof(sfile));
    COMP_GETPARSEPARAS(1,sfile,"�����ļ�·��");
    trim(sfile);
    memset(sBaseNode, 0x00, sizeof(sBaseNode));
    COMP_GETPARSEPARAS(2,sBaseNode,"��׼���");
    trim(sBaseNode);
    if (sBaseNode[0]=='\0')
    {
        snprintf(sBaseNode, sizeof(sBaseNode), "%s", "/commbuf");
    }    

    LOG(LM_STD,Fmtmsg("���ļ�����XML��ִ�п�ʼ,basenode[%s]file=[%s]", 
        sBaseNode,sfile),fpub_GetCompname(lXmlhandle))

    if((fp=fopen(sfile,"r"))==NULL)
    {
    	LOG(LM_STD,Fmtmsg(" ����ļ�ʧ��[%s]", strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" ����ļ�ʧ��"));
        fpub_SetCompStatus(lXmlhandle,-1);
        return -1;
    }
    fstat(fileno(fp), &struStat);
    ilen = struStat.st_size;
    ilen2 = ilen * 1.5;
    if((sbuf=malloc(ilen2))==NULL)
    {
        fclose(fp);
        LOG(LM_STD,Fmtmsg(" ��̬�����ڴ�ʧ��[%s]",sfile),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" ��̬�����ڴ�ʧ��"));
        fpub_SetCompStatus(lXmlhandle,-1);
        return -1;          	 	  	
    }	
    fread(sbuf,ilen,1,fp);
    fclose(fp);
    sbuf[ilen]=0; 
      
    /* ������ǩ��ȥ��  add by tuql 20090831 
    pstr = strstr(sbuf,"<!--");
    if (pstr != NULL )
    {
       *pstr = 0;
    }*/
    /*sbuf[strlen(sbuf)-1]=0;*/	   
    /*д��ͨѶ������*/
    iRet = 0;
    if ( (iRet= xml_RelSetBinElement ( lXmlhandle, sBaseNode, sbuf, ilen)) <0 )
    {
        free(sbuf);
        LOG(LM_STD,Fmtmsg("����XML�������ʧ��,ret[%d]",iRet),"ERROR");	
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("����XML�������ʧ��"));
        fpub_SetCompStatus(lXmlhandle,-1);
        return -1;
    }
    free(sbuf);
   
    #ifdef DEBUG
          LOG(LM_DEBUG,Fmtmsg("���������ݵ����ļ����[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
      
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: STIPS_ImpFromBuf
�������: ��COMMBUF�е���XML���
�������: 
  ��COMMBUF�е����ݵ���
  ����Ϊ  XML ������
�������: 
  ��� ��������     ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��
1 NODE         �����      ��   ��      COMMBUF��NODE����һ��Ϊ/COMMBUF
2 ����·��     XML�ڵ�     ��   ��      XML������ŵĻ�׼�ڵ�
3 ���뷽ʽ     �ַ���      1    ��      ���Ƿ�ʽ:  1-���Ƿ�ʽ, 0-�����Ƿ�ʽ(����)
4 �Ƿ��ʽ��                            0-������, 1-XML 2.0->1.0ת��(��д)


������״̬: 
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ: 
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

  
�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա: �м�ҵ���Ʒ��չ���з���
��������: 2000��01��01��
�޸�����: 2005-11-23 21:12
����ʹ��ʾ��: 
************************************************************************/
IRESULT STIPS_ImpFromBuf(HXMLTREE lXmlhandle) 
{
  char snode[100],dest[50],smode[20],sroot[20];
  int mode ,ret, iParas;
  char sxmlpath[50],stwo[20];
  char *buf;
  int ilen;  
  
  fpub_InitSoComp(lXmlhandle);
  COMP_PARACOUNTCHKMIN(4)
  COMP_GETPARSEPARAS(1,snode,   "COMMBUFNODE");
  COMP_GETPARSEPARAS(2,dest,    "����·��");
  COMP_GETPARSEPARAS(3,smode,   "���뷽ʽ");
  COMP_GETPARSEPARAS(4,stwo,    "�Ƿ���и�ʽ������");  /*��<node1/>==><node1></node1>*/
  mode=atoi(smode);
  
  /*ȡ�ڵ����ݳ���*/
  ilen=xml_GetElementLen(lXmlhandle,snode);
  if (ilen <= 0)
  {
  	  LOG(LM_STD,Fmtmsg("  -->XML IMP ERR, node[%s]�����ڻ�����Ϊ��",snode),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" XML����ʧ��,Դ��������Ϊ��"));
      fpub_SetCompStatus(lXmlhandle,-1);
      return -1;
  }		
  ilen = ilen / 2 ;       /*HEX��ʽ*/
  ilen = ilen *1.5;
  if((buf=malloc(ilen))==NULL)
  {
    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML����ʧ��,�쳣1"));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    LOGRET(-1,LM_STD,
           Fmtmsg("malloc err,len[%d]",ilen),fpub_GetCompname(lXmlhandle)) 
    return -1; 	  	
  }
  if((ret=xml_GetBinElement(lXmlhandle,snode,buf,ilen))== FAIL)
  {
    free(buf);
    LOG(LM_DEBUG,Fmtmsg(MSG_SYS_XMLBINGET,snode,GETXMLERR),"ERROR");
    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" XML����ʧ��,��ȡ����ʧ��"));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    return -1;
  }
  buf[ret]=0;   
  if (strcmp(stwo,"1")==0) 
  {
     ret=xml_Conv2to1(buf,ilen);
  }
  ret=xml_ElementExist( lXmlhandle, XML_TMPNODE );
  if (ret==1)
  {
    LOG(LM_DEBUG,Fmtmsg("XML_IMPFROM Warning:ϵͳ��ʱ�ڵ�[%s]�Ѵ���,����ɾ��!!",XML_TMPNODE),"");
    if ( xml_DelElement( lXmlhandle,XML_TMPNODE)==-1 ) 
    {
       free(buf);
       fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML����ʧ��,�����쳣"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       LOG(LM_STD,Fmtmsg("ɾ����ʱ�������!,ret[%d]",-9),"");
       return -9;   
    }
  }
  COMP_SOFTSETXML(XML_TMPNODE,"");	
  if (xml_ImportXMLString( lXmlhandle, buf, XML_TMPNODE, 0 )==-1)
  {
     free(buf);
     /* 
     LOG(LM_STD,Fmtmsg("XMLERR[%s],ilen[%d],buf[%-100.100s]",
         xml_StringError(xml_GetLastError()),ilen,buf),"ERROR");
         */
     xml_DelElement( lXmlhandle,XML_TMPNODE); /*ɾ�����ɹ���Ӱ����*/
     fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML����ʧ��,�����ʽ�Ƿ���ȷ"));
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     LOG(LM_STD,Fmtmsg("��BUF����XMLʧ��,����XML��ʽ�Ƿ���ȷ!"),"ERROR");
     return -8; 
  }
  free(buf);
  LOG(LM_DEBUG,Fmtmsg("  -->5�������ݳ���[%d]",ilen),"DEBUG");
  /*�ڴ˻�ȡ�������*/
  if (xml_GetChildElementName(lXmlhandle,XML_TMPNODE,1,sroot,sizeof(sroot)) < 0)
  {
     fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML����ʧ��,�쳣3"));
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     LOG(LM_STD,Fmtmsg("���ļ�����XMLʧ��,����XML������Ƿ���ȷ!"),"");
     return -9; 
  }	
  sprintf(sxmlpath,"%s/%s",XML_TMPNODE,sroot);
  ret=xml_ElementExist( lXmlhandle, dest );
  if (ret!=1)
  {
    COMP_HARDSETXML(dest,"");	
  }	
  /*���뷽ʽΪ1-����ʱ,ֱ�Ӳ���node move��ʽ*/
/*  xml_NodeMove ������BUG,���ڲ�����,ֹͣʹ��,���ڽϴ��XML��,move��ʽЧ�ʺܸ�
    Tianhc 2006-3-19 15:05
  if (mode == 1 )
  {
  	  if (xml_NodeMove( lXmlhandle,dest,sxmlpath) < 0 )
      {
         xml_DelElement( lXmlhandle,XML_TMPNODE); 
		     fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML����ʧ��,�쳣4"));
		     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		     LOG(LM_STD,Fmtmsg("XML����ʧ��,xml_NodeMove err!"),"ERROR");
		     return -10; 
      }		
      xml_DelElement( lXmlhandle,XML_TMPNODE); 
		  fpub_SetCompStatus(lXmlhandle,0);
		  LOG(LM_STD,Fmtmsg("  -->��BUF����XML�ɹ�,node[%s]=>[%s],[%s]",snode,dest,sroot),"MOVE");  
		  return 0;
  }
*/  	
  ret=xml_XCopy(lXmlhandle, sxmlpath, dest, mode);
  xml_DelElement( lXmlhandle,XML_TMPNODE); /*ɾ�����ɹ���Ӱ����*/
  if (ret<0)
  {
    LOG(LM_STD,Fmtmsg("��BUF����XMLʧ��, ret[%d],note[%s]",ret,snode),"ERROR");	
    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML����ʧ��,���ݴ���ʧ��"));
    fpub_SetCompStatus(lXmlhandle,-1);
    return -1;
  }	
  fpub_SetCompStatus(lXmlhandle,0);
  LOG(LM_STD,Fmtmsg("  -->��BUF����XML�ɹ�,node[%s]=>[%s],ret[%d]",snode,dest,ret),"XCOPY");  
  return 0;
}	

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitYXCS
�������: �Ǽ����в�����
�������: 
  �Ǽ����в�����
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
���ɸ�ʽ����	tips_yxcs

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��10��22��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitYXCS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_YXCS stYxcs;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[128];
    int iTypeList=0;/* ����������Ϣ���� */
    int iDetailList=0;/* ������ϸ��Ϣ���� */
    char sTypeList[128];/* ����������Ϣ�ڵ�·�� */
    char sDetailList[128];/* ������ϸ��Ϣ�ڵ�·�� */
    char sParaNode[128];/* ĳ���ڵ�·�� */
    char sRootNode[32];/* ���ڵ� */
    int i,j,iFlag1,iFlag2;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_YXCS stYxcs;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("�Ǽ����в��������ݿ�ʼ����..."),fpub_GetCompname(lXmlhandle))

    memset(&stYxcs, 0x00, sizeof(stYxcs));
    COMP_PARACOUNTCHK(3);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    pstrcopy(stYxcs.zwrq, sBuf, sizeof(stYxcs.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�ۺ�ǰ����ˮ��")
    stYxcs.zhqzlsh=atoi(sBuf);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRootNode, 0x00, sizeof(sRootNode));
    COMP_GETPARAS(3,sBuf,"���ڵ�")
    pstrcopy(sRootNode, sBuf, sizeof(sRootNode));
    trim(sRootNode);

    LOG(LM_STD,Fmtmsg("��������[%s],ǰ����ˮ��[%d],���ڵ�[%s]...", 
        stYxcs.zwrq, stYxcs.zhqzlsh, sRootNode),fpub_GetCompname(lXmlhandle))

    /* 3.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stYxcs.workdate, sBuf, sizeof(stYxcs.workdate));
        
    /* ��ȡ����������Ϣ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    iTypeList=0;
    snprintf(sBuf, sizeof(sBuf), "%s/%s", sRootNode, "ParamTypeList9106");
    trim(sBuf);
    if ((iTypeList=xml_ElementCount(lXmlhandle,sBuf))==-1)
    { 
        LOG(LM_DEBUG,Fmtmsg("���[%s]:%s:[%s]",fpub_GetCompname(lXmlhandle),"��ȡ����������Ϣ����ʧ�ܣ�",sBuf),fpub_GetCompname(lXmlhandle))  
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,
            Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)),
           fpub_GetCompname(lXmlhandle))
    }
    for  (i=1,iFlag1=0; i<=iTypeList; i++ )
    {   
        memset(sTypeList, 0x00, sizeof(sTypeList));
        snprintf(sTypeList, sizeof(sTypeList),"%s/%s|%d", sRootNode, "ParamTypeList9106", i);
        memset(stYxcs.paramtypeno, 0x00, sizeof(stYxcs.paramtypeno));
        memset(stYxcs.paramdescrip, 0x00, sizeof(stYxcs.paramdescrip));
        
        /* 4.�������ͱ�� */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sParaNode, 0x00, sizeof(sParaNode));
        snprintf(sParaNode, sizeof(sParaNode), "%s/ParamTypeNo", sTypeList);
        COMP_SOFTGETXML(sParaNode, sBuf)
        pstrcopy(stYxcs.paramtypeno, sBuf, sizeof(stYxcs.paramtypeno));
        trim(stYxcs.paramtypeno);
        /* 5.������������ */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sParaNode, 0x00, sizeof(sParaNode));
        snprintf(sParaNode, sizeof(sParaNode), "%s/Description", sTypeList);
        COMP_SOFTGETXML(sParaNode, sBuf)
        pstrcopy(stYxcs.paramdescrip, sBuf, sizeof(stYxcs.paramdescrip));
        trim(stYxcs.paramdescrip);        
        /* ��ȡ������ϸ��Ϣ���� */
        memset(sBuf, 0x00, sizeof(sBuf));
        iDetailList=0;
        snprintf(sBuf, sizeof(sBuf), "%s/%s", sTypeList, "ParamList9106");
        trim(sBuf);
        if ((iDetailList=xml_ElementCount(lXmlhandle,sBuf))==-1)
        { 
            LOG(LM_DEBUG,Fmtmsg("���[%s]:%s:[%s]",fpub_GetCompname(lXmlhandle),"��ȡ������ϸ��Ϣ����ʧ�ܣ�", sBuf),fpub_GetCompname(lXmlhandle))  
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,
                Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)),
                fpub_GetCompname(lXmlhandle))
        }
        
        for (j=1,iFlag2=0; j<=iDetailList; j++ )
        {
            memset(sDetailList, 0x00, sizeof(sDetailList));
            snprintf(sDetailList, sizeof(sDetailList),"%s/%s|%d", sTypeList, "ParamList9106", j);
            memset(stYxcs.detailno, 0x00, sizeof(stYxcs.detailno));
            memset(stYxcs.detaildescri, 0x00, sizeof(stYxcs.detaildescri));
            memset(stYxcs.detailvalue, 0x00, sizeof(stYxcs.detailvalue));
        
            /* 6.��ϸ��� */
            memset(sBuf, 0x00, sizeof(sBuf));
            memset(sParaNode, 0x00, sizeof(sParaNode));
            snprintf(sParaNode, sizeof(sParaNode), "%s/DetailNo", sDetailList);
            COMP_SOFTGETXML(sParaNode, sBuf)
            pstrcopy(stYxcs.detailno, sBuf, sizeof(stYxcs.detailno));
            trim(stYxcs.detailno);
            /* 7.��ϸ������� */
            memset(sBuf, 0x00, sizeof(sBuf));
            memset(sParaNode, 0x00, sizeof(sParaNode));
            snprintf(sParaNode, sizeof(sParaNode), "%s/Description", sDetailList);
            COMP_SOFTGETXML(sParaNode, sBuf)
            pstrcopy(stYxcs.detaildescri, sBuf, sizeof(stYxcs.detaildescri));
            trim(stYxcs.detaildescri);
            /* 8.��ϸ���ȡֵ */
            memset(sBuf, 0x00, sizeof(sBuf));
            memset(sParaNode, 0x00, sizeof(sParaNode));
            snprintf(sParaNode, sizeof(sParaNode), "%s/ParamValue", sDetailList);
            COMP_SOFTGETXML(sParaNode, sBuf)
            pstrcopy(stYxcs.detailvalue, sBuf, sizeof(stYxcs.detailvalue));
            trim(stYxcs.detailvalue);                        
						
						/* add dci 20141103 */
   					memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_yxcs", SD_TIPS_YXCS, NUMELE(SD_TIPS_YXCS), &stYxcs, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      				fpub_SetMsg(lXmlhandle, 24484, "�Ǽ����в���������ʧ��");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�Ǽ����в���������ʧ��,�������ͱ��[%s],��ϸ���[%s]", 
                    stYxcs.paramtypeno, stYxcs.detailno),fpub_GetCompname(lXmlhandle))  
            }
   					/* end add dci 20141103 */

						/* mod dci 20141103
            EXEC SQL INSERT INTO tips_yxcs  VALUES (:stYxcs);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
            if ( SQLERR )
            {    	
                fpub_SetMsg(lXmlhandle, 24484, "�Ǽ����в���������ʧ��");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�Ǽ����в���������ʧ��,�������ͱ��[%s],��ϸ���[%s]", 
                    stYxcs.paramtypeno, stYxcs.detailno),fpub_GetCompname(lXmlhandle))  
            }
            */
        }        
    }

    fpub_SetMsg(lXmlhandle, 0, "�Ǽ����в��������ݳɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�Ǽ����в��������ݳɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;     
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_Init9120
�������: �Ǽ�9120ͨ��Ӧ���
�������: 
  �Ǽ�9120ͨ��Ӧ���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
���ɸ�ʽ����	tips_9120

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��10��23��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_Init9120(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_9120 st9120;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[2048];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_9120 st9120;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("�Ǽ�9120ͨ��Ӧ������ݿ�ʼ����..."),fpub_GetCompname(lXmlhandle))

    memset(&st9120, 0x00, sizeof(st9120));
    COMP_PARACOUNTCHK(2);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    pstrcopy(st9120.zwrq, sBuf, sizeof(st9120.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�ۺ�ǰ����ˮ��")
    st9120.zhqzlsh=atoi(sBuf);
    
    /* 3.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(st9120.workdate, sBuf, sizeof(st9120.workdate));    
    
    /* 4.Ӧ��ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ydsj", sBuf)
    pstrcopy(st9120.systime, sBuf, sizeof(st9120.systime));       

    /* 5.ԭ���ı�ʶ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriMsgID", sBuf)
    pstrcopy(st9120.orimsgid, sBuf, sizeof(st9120.orimsgid));    
    
    /* 6.ԭ���ı�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriMsgNo", sBuf)
    pstrcopy(st9120.orimsgno, sBuf, sizeof(st9120.orimsgno)); 

    /* 7.������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Result", sBuf)
    pstrcopy(st9120.result, sBuf, sizeof(st9120.result));       

    /* 8.���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AddWord", sBuf)
    pstrcopy(st9120.addword, sBuf, sizeof(st9120.addword));    
    
    /* 9.��ϸ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Information", sBuf)
    pstrcopy(st9120.information, sBuf, sizeof(st9120.information));

		/* add dci 20141103 */
   	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_9120", SD_TIPS_9120, NUMELE(SD_TIPS_9120), &st9120, sErrmsg);
   	if( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      	fpub_SetMsg(lXmlhandle, 24484, "�Ǽ�9120ͨ��Ӧ���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�Ǽ�9120ͨ��Ӧ���ʧ��"),fpub_GetCompname(lXmlhandle))  
    }
   	/* end add dci 20141103 */

		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_9120  VALUES (:st9120);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24484, "�Ǽ�9120ͨ��Ӧ���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�Ǽ�9120ͨ��Ӧ���ʧ��"),fpub_GetCompname(lXmlhandle))  
    } 
    */      
            
    fpub_SetMsg(lXmlhandle, 0, "�Ǽ�9120ͨ��Ӧ���ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�Ǽ�9120ͨ��Ӧ���ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC; 
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InsHxmx
�������: �ǼǺ��Ķ�����ϸ��
�������: 
  �ǼǺ��Ķ�����ϸ��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
���ĵǼǱ�	tips_xibhxmx

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: wangw
��������: 2012��08��02��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_XIB_InsHxmx(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_XIBHXMX  stHxmx;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sBwdjbz[1+1];
    char sNode[64];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_XIBHXMX  stHxmx;
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif 

    memset(&stHxmx, 0x00, sizeof(stHxmx));
    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzrq", sBuf)
    pstrcopy(stHxmx.zwrq, sBuf, sizeof(stHxmx.zwrq));           

    /* �ͻ����� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/khmc", sBuf)
    pstrcopy(stHxmx.khmc, sBuf, sizeof(stHxmx.khmc));           

    /* �ͻ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/khbh", sBuf)
    pstrcopy(stHxmx.khbh, sBuf, sizeof(stHxmx.khbh));           

    /* ��˰�˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/kszh", sBuf)
    pstrcopy(stHxmx.khzh, sBuf, sizeof(stHxmx.khzh));           

    /* ���׽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/jyje", sBuf)
    stHxmx.jyje = atof(sBuf);           

    /* ˰Ʊ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/sprq", sBuf)
    pstrcopy(stHxmx.sprq, sBuf, sizeof(stHxmx.sprq));           

    /* ���ļ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/hxjzrq", sBuf)
    pstrcopy(stHxmx.hxrq, sBuf, sizeof(stHxmx.hxrq));           

    /* ���ĳ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/hxcxrq", sBuf)
    pstrcopy(stHxmx.hxcxrq, sBuf, sizeof(stHxmx.hxcxrq));           

    /* ժҪ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/zy", sBuf)
    pstrcopy(stHxmx.zy, sBuf, sizeof(stHxmx.zy));           

    /* ״̬ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/zt", sBuf)
    pstrcopy(stHxmx.status, sBuf, sizeof(stHxmx.status));           

    /* ��ע */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/bz", sBuf)
    pstrcopy(stHxmx.bz, sBuf, sizeof(stHxmx.bz));           

    /* ״̬�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/ztm", sBuf)
    pstrcopy(stHxmx.ztm, sBuf, sizeof(stHxmx.ztm));           

    /* ������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/hxlsh", sBuf)
    pstrcopy(stHxmx.dzlsh, sBuf, sizeof(stHxmx.dzlsh));           
    /* �������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/jgdh", sBuf)
    pstrcopy(stHxmx.jgdh, sBuf, sizeof(stHxmx.jgdh));           

    /* ���˱�־ */
    pstrcopy(stHxmx.dzbz, "0", sizeof(stHxmx.dzbz));           

		/* add dci 20141103 */
   	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_xibhxmx", SD_TIPS_XIBHXMX, NUMELE(SD_TIPS_XIBHXMX), &stHxmx, sErrmsg);
    if( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      	fpub_SetMsg(lXmlhandle, 24103, "�ǼǺ�����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�ǼǺ�����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	
    /* end add dci 20141103 */

		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_xibhxmx VALUES (:stHxmx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24103, "�ǼǺ�����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("�ǼǺ�����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	
    */
        
    fpub_SetMsg(lXmlhandle, 0, "�ǼǺ�����ϸ��ʧ��");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC; 
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_DelStr
�������: ȥ���ַ���ͷβ�ַ�
�������: 
  ȥ���ַ���ͷβ�ַ�
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: wangw
��������: 2012��08��1��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_DelStr(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[1024*100],sBuf1[1024*100];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(2)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�����ַ���");
    memset(sNode, 0x00, sizeof(sNode));
    COMP_GETPARSEPARAS(2,sNode,"��Žڵ�");
    
    trim(sBuf);
      
    memset(sBuf1, 0x00, sizeof(sBuf1));
    memcpy(sBuf1,sBuf+1,strlen(sBuf)-2);
    
    COMP_SOFTSETXML(sNode, sBuf1)
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;  
}    

/*************************************************************************
 * ��������: set_xml
 * ��������: ����xml����ֵ, ��s�ܽ�ȡlen������Ϊxml����ֵ(len=0, ȡ��'\0')
 * �������: lXmlhandle - xml�����
 *           xmlnode - xml�����
 *           s - �ַ���
 *           len - ����
 *           type - ��ʽ(0: ascii, 1: bin)
 * �������: ��
 * ����ֵ: -99 �ڴ治��
 *         -1  ����ֵʧ��
 *         0   �ɹ�
 * ��������: 2009-07-08
 * �޸�����: 2009-07-08
 * ����Ա: renyh
 *
*************************************************************************/
int set_xml(HXMLTREE lXmlhandle, const char *xmlnode, const char *s, int len, int type)
{
    char *sval;
	int ret = 0;

    if (len == 0)
		len = strlen(s);
    sval = (char *)malloc(len+1);
	if (sval == NULL)
		return -99;
    memset(sval, 0, len+1);
    strncpy(sval, s, len);
	if (type == 0)
		ret = xml_SetElement(lXmlhandle, xmlnode, sval);
	else if (type == 1)
		ret = xml_SetBinElement(lXmlhandle, xmlnode, sval, len);
    free(sval);
    
    return ret;
}

int handle_express(HXMLTREE lXmlhandle, const char *sexp, int type)
{
	int ret = 0;
	char sStart[10], sLen[10];
	char *sXmlNode, *sValue;
	const char *s;
    char *sTmp;
	int flag = 0x00;
	int node_len, len = strlen(sexp);
	int iStart = 1, iLen = 0;
	int i;

	s = strchr(sexp, '=');
	if (s == NULL)
		return ret;
	node_len = (int)(s - sexp);

	sXmlNode = (char *)malloc(node_len+1);
	if (sXmlNode == NULL)
		return -99;
	sValue = (char *)malloc(len-node_len+1);
	if (sValue == NULL)
	{
		free(sXmlNode);
		return -99;
	}
	memset(sXmlNode, 0, node_len+1);
	memset(sValue, 0, len-node_len+1);
	memset(sStart, 0, sizeof(sStart));
	memset(sLen, 0, sizeof(sLen));
	i = 0;
	for (s = sexp; *s != '\0'; s++)
	{
		switch(flag)
		{
		case 0x00:
			if (*s == '=')
			{
				flag = 0x10;
				i = 0;
			}
			else
				*(sXmlNode+i++) = *s;
			break;
		case 0x10:
			if (*s == '#')
			{
				flag = 0x11;
				i = 0;
			}
			else
				*(sValue+i++) = *s;
			break;
		case 0x11:
			if (*s == ',')
			{
				flag = 0x12;
				i = 0;
			}
			else if (i < sizeof(sStart)-1)
				*(sStart+i++) = *s;
			break;
		case 0x12:
			if (i < sizeof(sLen)-1)
				*(sLen+i++) = *s;
			break;
		default:
			break;
		}
	}

	iStart = atoi(sStart);
	iLen = atoi(sLen);

	if (iStart == 0)
		iStart = 1;

	LOG(LM_STD, Fmtmsg("xml node: [%s]", sXmlNode), "");
	LOG(LM_STD, Fmtmsg("xml value: [%s]", sValue), "");
	LOG(LM_STD, Fmtmsg("start: [%d]", iStart), "");
	LOG(LM_STD, Fmtmsg("len: [%d]", iLen), "");

	ret = set_xml(lXmlhandle, sXmlNode, sValue+iStart-1, iLen, type);
	free(sXmlNode);
	free(sValue);
	return ret;
}

/**********************************************************************
��̬�����������
�����������:DATA_MEnSetValue
�������: DATA_MEnSetValue, ��ǿ������xml���ֵ
�������: ��ǿ������xml���ֵ
�������:
��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��


������״̬:
  ���״̬��         ���˵��
�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա: �м�ҵ���Ʒ��չ���з��� 
��������: 2009��07��20�� 
�޸�����: 2009��07��20��
����ʹ��ʾ��:
************************************************************************/
IRESULT DATA_MEnSetValue(HXMLTREE lXmlhandle)
{
    char sBuf[81920];
    int iFlag;           /* 0-ascii, 1-bin  */
    int iParaCount,i;

    int iRet=0; 
	int iStatus= COMPSTATUS_SUCC;
	int iResult = COMPRET_SUCC;


    fpub_InitSoComp(lXmlhandle);

#ifdef _DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"");
#endif

    iParaCount = fpub_GetPARAcount(lXmlhandle);
 
    memset(sBuf,'\0',sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��ֵ��ʽ");
    iFlag = atoi(sBuf);
   
    for ( i = 1; i < iParaCount; i++ )
    { 
        memset(sBuf,'\0',sizeof(sBuf));
        COMP_GETPARSEPARAS(i+1, sBuf, "��ֵ����ʽ");
        trim(sBuf);
		LOG(LM_STD, Fmtmsg("���ʽ[%s]��ֵ", sBuf), "");
		iRet = handle_express(lXmlhandle, sBuf, iFlag);
		
		if (iRet == -99)
		{
			LOG(LM_STD, Fmtmsg("���ʽ[%s]��ֵʧ��, �ڴ治��!", sBuf), "");
		}
		else if (iRet == -1)
		{
			LOG(LM_STD, Fmtmsg("���ʽ[%s]��ֵʧ��", sBuf), "");
		}
		
    }

#ifdef _DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"");
#endif

    fpub_SetCompStatus(lXmlhandle, iStatus);
    return iResult;
}


/************************************************************************
��̬�����������
�����������: SYW_TIPS_SZQM
�������: ��TIPSͨѶ�������ǩ��
�������: 
  ��TIPSͨѶ�������ǩ��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: LIUY
��������: 2011��11��09��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_SZQM(HXMLTREE lXmlhandle)
{
	 	int iParas;
   	char sBuf[254];
   	/*char sReqbuf[TIPS_MAX_PKG]; 20150512 8M��Ϊ64000 */
   	char sReqbuf[LEN_COMM];
   	/* end 20150512 */
   	char sTxms[1+1];/* ͨѶģʽ1,2,3 3-��Ӧ�� */
   	char stranscode[30],smode[10],sputmode[10],smsgid[100],slsh[30],sqm_name[50];
   	char squeue[50],sexpir_time[30],sfile[100],sRcombuf[20],sRespbuf[50];
   	FILE *fp1;
   	char *commbuf;
   	int iret=0,messlen=0,ilen=0,iRet=0,iLen=0;
   	caddr_t pUpfileHead;
   	struct stat struStat;
   	char recvcommbuf[4096000]; /*�ȶ�1M��С*/   
   	
   	LOG( LM_DEBUG, Fmtmsg( "���[%s]��ʼִ��", fpub_GetCompname( lXmlhandle ) ), "INFO" ); 
     	  
   	memset(sBuf, 0x00, sizeof(sBuf));
    memset(sReqbuf, 0x00, sizeof(sReqbuf));
    memset(sTxms, 0x00, sizeof(sTxms));  
    memset(smode, 0x00, sizeof(smode));
    memset(sputmode, 0x00, sizeof(sputmode));
    memset(smsgid, 0x00, sizeof(smsgid));
    memset(slsh, 0x00, sizeof(slsh));
    memset(sqm_name, 0x00, sizeof(sqm_name));
    memset(squeue, 0x00, sizeof(squeue));  
    memset(sfile, 0x00, sizeof(sfile));
    memset(sRcombuf, 0x00, sizeof(sRcombuf));
    memset(recvcommbuf, 0x00, sizeof(recvcommbuf));
    memset(sexpir_time, 0x00, sizeof(sexpir_time));
    memset(stranscode, 0x00, sizeof(stranscode));
   	       	
   	fpub_InitSoComp(lXmlhandle);
   	
   	/*��ȡ�������  --S*/
   	COMP_PARACOUNTCHK(3)
   	
   	/*sReqbuf*/
   	memset(sBuf, 0x00, sizeof(sBuf));
   	memset(sReqbuf, 0x00, sizeof(sReqbuf));
   	COMP_GETPARSEPARAS(1, sBuf, "����sReqbuf")
   	pstrcopy(sRcombuf, sBuf, sizeof(sRcombuf));
   	trim(sRcombuf);
   	
   	/*ͨѶģʽ*/
   	memset(sBuf, 0x00, sizeof(sBuf));
   	memset(sTxms, 0x00, sizeof(sTxms));
   	COMP_GETPARSEPARAS(2, sBuf, "ͨѶģʽ")
   	pstrcopy(sTxms, sBuf, sizeof(sTxms));
   	trim(sTxms);
   	
   	/*���ر��Ľڵ�*/
   	memset(sBuf, 0x00, sizeof(sBuf));
   	memset(sRespbuf, 0x00, sizeof(sRespbuf));
   	COMP_GETPARSEPARAS(3, sBuf, "���ر��Ľڵ�")
   	pstrcopy(sRespbuf, sBuf, sizeof(sRespbuf));
   	trim(sRespbuf);
   	
   	LOG(LM_STD,Fmtmsg("-[%s]-[%s]-[%s]-",sRcombuf,sTxms,sRespbuf),"INFO");
   	
	 	if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
   	{
   	    fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
   	    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	    LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
   	    return COMPSTATUS_FAIL;
   	}
   	
   	LOG(LM_STD,Fmtmsg("ͨѶ��������sReqbuf[%s]\n ͨѶģʽ[%s]",sReqbuf, sTxms), fpub_GetCompname(lXmlhandle))
   	
   	GetListbyDiv(sReqbuf,1,stranscode,  '|','\\');     /*��1���ֶ�Ϊ���״���*/
   	GetListbyDiv(sReqbuf,2,smode,       '|','\\');     /*��2���ֶ�Ϊģʽ 1 ����put 2 ����get*/
   	GetListbyDiv(sReqbuf,3,sputmode,    '|','\\');     /*��3���ֶ�Ϊputģʽ getʱ��ʹ��  1 ������ʽput 2 ����Ӧ��ʽput*/   
   	GetListbyDiv(sReqbuf,4,smsgid,      '|','\\');     /*��4���ֶ�Ϊ��ϢID msgid */ 
   	GetListbyDiv(sReqbuf,5,slsh,        '|','\\');     /*��5���ֶ�Ϊ��ˮ��*/
   	GetListbyDiv(sReqbuf,6,sqm_name,    '|','\\');     /*��6���ֶ�ΪMQ��������*/
   	GetListbyDiv(sReqbuf,7,squeue,      '|','\\');     /*��7���ֶ�Ϊ������*/
   	GetListbyDiv(sReqbuf,8,sexpir_time, '|','\\');     /*��8���ֶ�Ϊ������-���� ��ʱ-����*/
   	iret=GetListbyDiv(sReqbuf,9,sfile,'|','\\');       /*��9���ֶ�Ϊ���ݰ��ļ���*/
   	if (iret<0)
   	{
   	   LOG(LM_STD,Fmtmsg("���ݸ�ʽ�Ƿ�,ȡ��������ʧ��,����"),"ERROR");
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}
   	LOG(LM_STD,Fmtmsg("stranscode[%s],smode[%s],sputmode[%s],smsgid[%s],slsh[%s],sqm_name[%s],squeue[%s],sexpir_time[%s],sfile[%s]",
   	  stranscode,smode,sputmode,smsgid,slsh,sqm_name,squeue,sexpir_time,sfile), fpub_GetCompname(lXmlhandle))
   	trim(sfile);
   	
   	/*���ļ�,�������ݵ�commbuf*/
   	fp1=fopen(sfile,"r");
   	if (fp1==NULL)
   	{
  		  LOG(LM_STD,Fmtmsg("��pkg�ļ�ʧ��"),"ERROR");
   	   fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" ���ļ�ʧ��"));
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}		
   	fstat(fileno(fp1), &struStat);
   	ilen = struStat.st_size;
   	if ((pUpfileHead = mmap(NULL, (size_t)ilen, PROT_READ, MAP_SHARED, fileno(fp1), (off_t)0)) == (caddr_t) - 1)
   	{
   	   munmap(fp1, (size_t)struStat.st_size);
   	   fclose(fp1);
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}
   	commbuf = pUpfileHead;
   	   	
   	memset(recvcommbuf,0,sizeof(recvcommbuf));
   	pstrcopy(recvcommbuf,commbuf,sizeof(recvcommbuf));
   	LOG(LM_STD,Fmtmsg("  -->recvcommbuf[%s]",recvcommbuf),"INFO");
   	
   	/*����ca��*/
   	iret = prv_genca(recvcommbuf,sizeof(recvcommbuf));
   	if (iret < 0)
   	{
   		  LOG(LM_STD,Fmtmsg("  -->����caʧ��!iret[%d]",iret),"ERROR");
   	   munmap(pUpfileHead, (size_t)struStat.st_size);
   	   fclose(fp1);
   		  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   		  return COMPSTATUS_FAIL;
   	}
   	LOG(LM_STD,Fmtmsg("  -->recvcommbuf1[%s]",recvcommbuf),"INFO");
   	if(strcmp(sputmode,"2")==0)
   	{
   		  strcat(smsgid,recvcommbuf);
   		  memset(recvcommbuf,0,sizeof(recvcommbuf));
   		  strcpy(recvcommbuf,smsgid);
   	}
   	
   	messlen = strlen(recvcommbuf);  
   	LOG(LM_STD,Fmtmsg("  -->genca��Buf![%d]sendcommbuf[%s][%d]",iret,recvcommbuf,messlen),"INFO"); 
   	
   	/*�������Ҳ���ͷ� 20150512���� */
    munmap(pUpfileHead, (size_t)struStat.st_size);       
   	fclose(fp1); 
    
		if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,recvcommbuf,strlen(recvcommbuf))) == FAIL)
		{
			fpub_SetMsg(lXmlhandle, 24109, "��дͨѶ������ʧ��");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"��дͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
			return COMPSTATUS_FAIL;
		}
  	      
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;  

} 

/************************************************************************
��̬�����������
�����������: SYW_TIPS_UnSZQM
�������: TIPSͨѶ����ǩ����֤
�������: 
  TIPSͨѶ����ǩ����֤
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: LIUY
��������: 2011��11��09��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UnSZQM(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[254];
    char sRcombuf[50],sTxms[10],sRespbuf[50];
    /*char sReqbuf[TIPS_MAX_PKG]; 20150512 ��Ϊ��̬���� */
    int iSize = 0;
    /*char *sReqbuf = NULL;*/
    char sReqbuf[4096000];
    /* end 20150512 */
    
    char *pstr;
    char stranscode[30],slsh[30],sfile2[100],gsCommbuf[254];
    int irecvlen,iRet,iLen,iret;
    FILE *fp1;
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRcombuf, 0x00, sizeof(sRcombuf));
    memset(sTxms, 0x00, sizeof(sTxms));
    memset(sRespbuf, 0x00, sizeof(sRespbuf));
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf)); 20150512 */
    memset(stranscode, 0x00, sizeof(stranscode));
    memset(slsh, 0x00, sizeof(slsh));
    memset(sfile2, 0x00, sizeof(sfile2));
    memset(gsCommbuf, 0x00, sizeof(gsCommbuf));

    fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
    #endif 
  
    /*��ȡ�������  --S*/
    COMP_PARACOUNTCHK(3)

    /*sReqbuf*/
    memset(sBuf, 0x00, sizeof(sBuf));
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf)); 20150512 */
    COMP_GETPARSEPARAS(1, sBuf, "����sReqbuf")
    pstrcopy(sRcombuf, sBuf, sizeof(sRcombuf));
    trim(sRcombuf);

    /*ͨѶģʽ*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTxms, 0x00, sizeof(sTxms));
    COMP_GETPARSEPARAS(2, sBuf, "ͨѶģʽ")
    pstrcopy(sTxms, sBuf, sizeof(sTxms));
    trim(sTxms);
    
    /*���ر��Ľڵ�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRespbuf, 0x00, sizeof(sRespbuf));
    COMP_GETPARSEPARAS(3, sBuf, "���ر��Ľڵ�")
    pstrcopy(sRespbuf, sBuf, sizeof(sRespbuf));
    trim(sRespbuf);
    
    if(strcmp(sTxms,"02")==0)
    {
    	  memset(gsCommbuf, 0x00, sizeof(gsCommbuf));
    	  sprintf(gsCommbuf,"%s|%s|02|%s|%s|%s|","","","","����MQʧ��","");
    		if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,gsCommbuf,strlen(gsCommbuf))) == FAIL)
	      {
		      fpub_SetMsg(lXmlhandle, 24109, "��дͨѶ������ʧ��");
		      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		      LOGRET(COMPRET_FAIL,LM_STD,"��дͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
		      return COMPSTATUS_FAIL;
	      }
	       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
         return COMPRET_SUCC;
    }
    
    /* 20150512 ��Ϊ��̬���� */
    /*
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    */
    
    iSize = xml_GetBinElementLen(lXmlhandle, sRcombuf);
    if (iSize < 0)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ���ĳ���ʧ��",fpub_GetCompname(lXmlhandle));
	  }
	  iSize = iSize +1;
	  /*sReqbuf = malloc(iSize);*/
	  
	  if(NULL == sReqbuf)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("mallocʧ��[%s]",strerror(errno)),fpub_GetCompname(lXmlhandle));
	  }	
	  memset(sReqbuf, 0, iSize);
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, iSize)) == FAIL )
    {
    	  free(sReqbuf);
        fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    /* end 20150512 */    
    
    /* 20150815 test 
    /*���ļ�,�������ݵ�commbuf
    char *commbuf;
   	
   	char recvcommbuf[4096000]; /*�ȶ�1M��С
    int ilen;
    caddr_t pUpfileHead;
   	struct stat struStat;
   	fp1=fopen("/home/gaps/file/tips/pkg/test","r");
   	if (fp1==NULL)
   	{
  		  LOG(LM_STD,Fmtmsg("��pkg�ļ�ʧ��"),"ERROR");
   	   fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" ���ļ�ʧ��"));
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}		
   	
   	fstat(fileno(fp1), &struStat);
   	ilen = struStat.st_size;
   	
   	if ((pUpfileHead = mmap(NULL, (size_t)ilen, PROT_READ, MAP_SHARED, fileno(fp1), (off_t)0)) == (caddr_t) - 1)
   	{
   	   munmap(fp1, (size_t)struStat.st_size);
   	   fclose(fp1);
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}
   	commbuf = pUpfileHead;
   	   	
   	memset(sReqbuf,0,sizeof(sReqbuf));
   	pstrcopy(sReqbuf,commbuf,sizeof(sReqbuf));
   	LOG(LM_STD,Fmtmsg("  -->sReqbuf[%s]",sReqbuf),"INFO");
   	
   	munmap(pUpfileHead, (size_t)struStat.st_size);       
   	fclose(fp1);    
     end test */
    
    LOG(LM_STD,Fmtmsg("ͨѶ��������sReqbuf[%s]\n ͨѶģʽ��Ӧ��[%s]",sReqbuf, sTxms),"INFO")
    
   /*У��ca */
   iret = prv_checkca(sReqbuf,sizeof(sReqbuf));
   if (iret < 0)
   {
     LOG(LM_STD,Fmtmsg("  -->У��caʧ��!iret[%d]",iret),"ERROR");
     fpub_SetMsg(lXmlhandle, 24105, "  -->У��caʧ��!");
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     return COMPSTATUS_FAIL;
   }
   LOG(LM_STD,Fmtmsg("  -->У��ca�ɹ�!iret[%d]",iret),"INFO");
   
   pstr = strstr(sReqbuf,"<!--");
   if (pstr != NULL )
   {
   	   *pstr = 0; 
   }
   LOG(LM_STD,Fmtmsg("  -->У��ca�ɹ���-----sReqbuf[%s]",sReqbuf),"INFO");
   memset(stranscode, 0x00, sizeof(stranscode));
   COMP_SOFTGETXML("/tipso/req/jydm", stranscode)
   memset(slsh, 0x00, sizeof(slsh));
   COMP_SOFTGETXML("/tipso/req/xh", slsh)
    
	 /*���ճɹ�,д��Ӧ��*/
	 memset(sfile2, 0x00, sizeof(sfile2));
	 snprintf(sfile2, sizeof(sfile2),"%s/file/tips/pkg/%s_%s_resp",getenv("HOME"),stranscode,slsh);
	 fp1=fopen(sfile2,"w");
	 if (fp1 == NULL )
	 {
	     fpub_SetMsg(lXmlhandle, 24105, "  -->gen resppkgfile fail!");
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPSTATUS_FAIL;
	 }		
	 irecvlen = strlen(sReqbuf);
	 fwrite(sReqbuf,irecvlen,1,fp1);
	 fclose(fp1);
	 memset(gsCommbuf, 0x00, sizeof(gsCommbuf));
   sprintf(gsCommbuf,"%s|%s|00|%s|%s|%s|",stranscode,slsh,sfile2,"У������ǩ���ɹ�","");
    
	if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,gsCommbuf,strlen(gsCommbuf))) == FAIL)
	{
		fpub_SetMsg(lXmlhandle, 24109, "��дͨѶ������ʧ��");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"��дͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
		return COMPSTATUS_FAIL;
	}
        
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   

} 


/************************************************************************
��̬�����������
�����������: SYW_TIPS_UNSZQM_TIPSJR
�������: TIPS��������ǩ����֤
�������: 
  TIPS��������ǩ����֤
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ��

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: LIUY
��������: 2011��11��09��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UNSZQM_TIPSJR(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[254];
    char sRcombuf[50],sRespbuf[50];
    /*char sReqbuf[TIPS_MAX_PKG]; 20150512 ��Ϊ��̬���� */
    int iSize = 0;
    char *pReqbuf = NULL;
    /* end 20150512 */
    char *pstr;
    char stranscode[30],slsh[30],sfile2[100],gsCommbuf[254];
    int irecvlen,iRet,iLen,iret;
    FILE *fp1;
    char *pmsgidstr,*pbuf;
    char msgidstr[100],szwrq[10],szhqzlsh[10];
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRcombuf, 0x00, sizeof(sRcombuf));
    memset(sRespbuf, 0x00, sizeof(sRespbuf)); 
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf));20150512*/
    memset(stranscode, 0x00, sizeof(stranscode));
    memset(slsh, 0x00, sizeof(slsh));
    memset(sfile2, 0x00, sizeof(sfile2));
    memset(msgidstr, 0x00, sizeof(msgidstr));
    memset(szwrq, 0x00, sizeof(szwrq));
    memset(szhqzlsh, 0x00, sizeof(szhqzlsh));

    fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
    #endif 
  
    /*��ȡ�������  --S*/
    COMP_PARACOUNTCHK(2)

    /*sReqbuf*/
    memset(sBuf, 0x00, sizeof(sBuf));
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf)); 20150512 */
    COMP_GETPARSEPARAS(1, sBuf, "����sReqbuf")
    pstrcopy(sRcombuf, sBuf, sizeof(sRcombuf));
    trim(sRcombuf);

    /*���ر��Ľڵ�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRespbuf, 0x00, sizeof(sRespbuf));
    COMP_GETPARSEPARAS(2, sBuf, "���ر��Ľڵ�")
    pstrcopy(sRespbuf, sBuf, sizeof(sRespbuf));
    trim(sRespbuf);
    
    /* 20150512 ��Ϊ��̬���� */
    /*
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    */
    
    iSize = xml_GetBinElementLen(lXmlhandle, sRcombuf);
    if (iSize < 0)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ���ĳ���ʧ��",fpub_GetCompname(lXmlhandle));
	  }
	  iSize = iSize +1;
	  pReqbuf = malloc(iSize);
	  if(NULL == pReqbuf)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("mallocʧ��[%s]",strerror(errno)),fpub_GetCompname(lXmlhandle));
	  }	
	  memset(pReqbuf, 0, iSize);
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, pReqbuf, iSize)) == FAIL )
    {
    	  free(pReqbuf); 
        fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    /* end 20150512 */

    pbuf=pReqbuf;
    memset(msgidstr, 0x00, sizeof(msgidstr));
    pmsgidstr = strstr(pbuf,"<?xml");
    if (pmsgidstr == NULL )
    {
   	  fpub_SetMsg(lXmlhandle, 24105, "  -->���ĸ�ʽ������!");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPSTATUS_FAIL;
    }
    else
    {
    	LOG(LM_STD,Fmtmsg("  -->pbuf[%s]",pbuf),"ERROR");
    	strncpy(msgidstr,pbuf,pmsgidstr-pbuf);
    	msgidstr[pmsgidstr-pbuf]='\0';
    }
   
   LOG(LM_STD,Fmtmsg("  -->msgidstr[%s],pmsgidstr-pbuf[%d]",msgidstr,pmsgidstr-pbuf),"ERROR");
   
   LOG(LM_STD,Fmtmsg("  -->pmsgidstr[%s]",pmsgidstr),"ERROR");
    
   /*У��ca*/
   iret = prv_checkca(pmsgidstr,sizeof(pmsgidstr));
   if (iret < 0)
   {
   	 LOG(LM_STD,Fmtmsg("  -->У��caʧ��!iret[%d]",iret),"ERROR");
     fpub_SetMsg(lXmlhandle, 24105, "  -->У��caʧ��!");
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     return COMPSTATUS_FAIL;
   }
   LOG(LM_STD,Fmtmsg("  -->У��ca�ɹ�!iret[%d]",iret),"INFO");
   /*ȥ��ע��*/
   pstr = strstr(pmsgidstr,"<!--");
   if (pstr != NULL )
   {
   	   *pstr = 0; 
   }
   LOG(LM_STD,Fmtmsg("  -->У��ca�ɹ���-----pmsgidstr[%s]",pmsgidstr),"ERROR");
    
   COMP_HARDGETXML(XMLNM_ZWRQ,szwrq);
   COMP_HARDGETXML(XMLNM_ZHQZLSH,szhqzlsh);
	 /*���ճɹ�,д��Ӧ��*/
	 memset(sfile2, 0x00, sizeof(sfile2));
	 snprintf(sfile2, sizeof(sfile2),"%s/tmp/tipsjr_%s_%s",getenv("HOME"),szwrq,szhqzlsh);
	 fp1=fopen(sfile2,"w");
	 if (fp1 == NULL )
	 {
	     fpub_SetMsg(lXmlhandle, 24105, "  -->gen resppkgfile fail!");
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPSTATUS_FAIL;
	 }		
	 irecvlen = strlen(pmsgidstr);
	 fwrite(pmsgidstr,irecvlen,1,fp1);
	 fclose(fp1);
   sprintf(gsCommbuf,"%s|%s",msgidstr,sfile2);
    
	if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,gsCommbuf,strlen(gsCommbuf))) == FAIL)
	{
		fpub_SetMsg(lXmlhandle, 24109, "��дͨѶ������ʧ��");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"��дͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
		return COMPSTATUS_FAIL;
	}
        
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   

}

              

/************************************************************************
��̬�����������
�����������: SYW_TIPS_PREHXCOMM
�������: ����ͨѶ����Ԥ����
�������:
  ��TIPSת����ͨѶ
�������:
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2015��07��13��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT SYW_TIPS_PREHXCOMM(HXMLTREE lXmlhandle)
{
		int iParas;
		char sJydm[9];
		char sBuf[254];
		char sRcombuf[50];
		char sReqbuf[LEN_COMM];
		char sReqbuf1[LEN_COMM];
		int iRet,iLen;
		
		fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
    #endif

    /*��ȡ�������  --S*/
    COMP_PARACOUNTCHK(2)

		/* jydm */
		memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "jydm")
    memcpy(sJydm, sBuf, sizeof(sJydm));
    
    /* commbuf */
		memset(sBuf, 0x00, sizeof(sBuf));
		memset(sRcombuf, 0x00, sizeof(sRcombuf));
    COMP_GETPARSEPARAS(2, sBuf, "commbuf")
    memcpy(sRcombuf, sBuf, sizeof(sRcombuf));
    trim(sRcombuf);
    
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle, 24105, "��ȡͨѶ������ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"��ȡͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    } 

		LOG(LM_STD,Fmtmsg("Ԥ����ǰ��jydm[%s] commbuf[%s]",sJydm,sReqbuf), fpub_GetCompname(lXmlhandle))
		
		memset(sReqbuf1, 0x00, sizeof(sReqbuf1));
		sprintf(sReqbuf1,"%8.8s%s",sJydm,sReqbuf);
		
		LOG(LM_STD,Fmtmsg("Ԥ�����jydm[%s] commbuf[%s]",sJydm,sReqbuf1), fpub_GetCompname(lXmlhandle))
		
		if (( iRet = xml_RelSetBinElement(lXmlhandle, sRcombuf, sReqbuf1, strlen(sReqbuf1))) == FAIL)
		{
			fpub_SetMsg(lXmlhandle, 24109, "��дͨѶ������ʧ��");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"��дͨѶ������ʧ��",fpub_GetCompname(lXmlhandle));
			return COMPSTATUS_FAIL;
		}
        
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   

}
